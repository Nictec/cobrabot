#include <QSettings>
#include <QDir>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QWebChannel>
#include <QDesktopServices>
#include "botsetup.h"
#include "ui_botsetup.h"
#include "cobralink.h"


WebPipe::WebPipe(int step){
    this->setupStep = step;
}

void WebPipe::tokenCallback(const QString *token){
    QString twitchSettings = QDir::currentPath() + "/config/twitch.ini";
    QSettings settings(twitchSettings, QSettings::IniFormat);
    if(this->setupStep == 1){
        settings.beginGroup("bot");
    } else {
        settings.beginGroup("streamer");
    }
    settings.setValue("password", token);
}

BotSetup::BotSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BotSetup)
{
    ui->setupUi(this);
}

BotSetup::~BotSetup()
{
    delete ui;
}

void BotSetup::on_generateButton_clicked()
{
    QString scope = "chat:edit+chat:read+channel:moderate+channel_editor+user_read";
    QDesktopServices::openUrl(QUrl("https://id.twitch.tv/oauth2/authorize?client_id=9k1gvkbdahrasual41n1cq6bvzpgkw&redirect_uri=http://localhost:5000/bot/oauth2/&response_type=token&scope=" + scope + "&force_verify=true"));
}

void BotSetup::on_saveButton_clicked()
{
    CobraLink *link = new CobraLink;
    bool result = link->verifyCredentials(this->ui->botToken->text(), this->ui->streamerToken->text(), this->ui->cobraToken->text());
    if (result) {
        this->close();
    } else {
        this->ui->errorLabel->setText("Error: one ore more of the tokens are wrong!");
    }
}

void BotSetup::setError(QString message){
    this->ui->errorLabel->setText(message);
}
