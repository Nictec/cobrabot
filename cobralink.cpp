#include "cobralink.h"
#include <QJsonObject>
#include <twitch.h>
#include <QNetworkReply>
#include <QMessageBox>

//slots
void CobraLink::authResponse(QNetworkReply *reply){
    if (reply->error()){
        qDebug() << reply->errorString();
        return;
    }
    QByteArray bytes = reply->readAll();
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    QJsonObject respObj = QJsonDocument::fromJson(bytes.data()).object();
    QMessageBox success;
    QMessageBox failure;
    //check the credentials

    if (respObj.toVariantMap()["bot_key"].toString() == this->formData->value("botToken") && respObj.toVariantMap()["streamer_key"].toString() == this->formData->value("streamerToken")){
        Twitch::setBotConnection(respObj.toVariantHash()["bot_name"].toString(), respObj.toVariantHash()["bot_key"].toString(), respObj.toVariantHash()["streamer_name"].toString(), respObj.toVariantHash()["streamer_name"].toString(), respObj.toVariantHash()["streamer_key"].toString(), respObj.toVariantHash()["cobra_key"].toString());
        success.setText("Success");
        success.setInformativeText("The config was sucessfully saved");
        success.setStandardButtons(QMessageBox::Ok);
        success.setDefaultButton(QMessageBox::Ok);
        success.exec();

    } else {
        success.setText("Error:");
        success.setInformativeText("One or more of the provided tokens was wrong! Please try again.");
        success.setStandardButtons(QMessageBox::Ok);
        success.setDefaultButton(QMessageBox::Ok);
        success.exec();
    }
}


CobraLink::CobraLink(QObject *parent) : QObject(parent)
{

    this->success = false;
    this->authManager = new QNetworkAccessManager();
    this->cmdManager = new QNetworkAccessManager();
    connect(this->authManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(authResponse(QNetworkReply*)));
}


//public methods
bool CobraLink::verifyCredentials(QString botToken, QString streamerToken, QString cobraToken){
    this->authRequest.setUrl(QUrl("http://localhost:5000/api/verify/"));
    this->authRequest.setRawHeader("Authentication", cobraToken.toUtf8());
    this->authManager->get(this->authRequest);

    this->formData = new QMap<QString, QString>;
    this->formData->insert("botToken", botToken);
    this->formData->insert("streamerToken", streamerToken);
    this->formData->insert("cobraToken", cobraToken);
    return true;
}

void CobraLink::getCommands(QString cobraToken){
    qInfo() << cobraToken;
    this->cmdRequest.setUrl(QUrl("http://localhost:5000/api/commands/"));
    this->cmdRequest.setRawHeader("Authentication", cobraToken.toUtf8());
    this->cmdManager->get(this->cmdRequest);
}
