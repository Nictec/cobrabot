#include "twitch.h"
#include <QSettings>
#include <QDir>
#include<QDebug>

Twitch::Twitch(QObject *parent) : QObject(parent)
{

}

void Twitch::loadBotConnection(){
     QString twitchSettings = QDir::currentPath() + "/config/twitch.ini";
     QSettings settings(twitchSettings, QSettings::IniFormat);
     settings.beginGroup("bot");
     this->username = settings.value("username").toString();
     this->password = settings.value("password").toString();
     this->channel = settings.value("channel").toString();
}

void Twitch::setBotConnection(QString username, QString password, QString channel){
    QString twitchSettings = QDir::currentPath() + "/config/twitch.ini";
    QSettings settings(twitchSettings, QSettings::IniFormat);
    settings.beginGroup("bot");
    settings.setValue("username", username);
    settings.setValue("password", password);
    settings.setValue("channel", channel);
}

bool Twitch::connectToServer(const QString &address, quint16 port){
    qInfo() << "connecting to: " << address << endl;
    this->connection = new QTcpSocket(this);
    this->connection->connectToHost(address, port);
    return connection->waitForConnected();
}

void Twitch::login(){
    this->loadBotConnection();
    if (connection->state() == QAbstractSocket::ConnectedState){
        QString pw = "PASS oauth:" + this->password + "\r\n";
        QString username = "NICK " + this->username + "\r\n";
        QString channel = ":" + this->username + "!" + this->username + "@" + this->username+ ".tmi.twitch.tv " + "JOIN #" + this->channel + "\r\n";
        std::string PASS = pw.toStdString();
        std::string NICK = username.toStdString();
        std::string JOIN = channel.toStdString();
        this->connection->write(PASS.c_str());
        this->connection->write(NICK.c_str());
        if (connection->waitForBytesWritten()){
            qInfo() << "login request sent!" << endl;

        }
    } else {
        qWarning() << "not connected to server!";
    }
}

void Twitch::join(){
    QString channel = "JOIN #" + this->channel + "\r\n";
    std::string JOIN= channel.toStdString();
    this->connection->write(JOIN.c_str());
    if (connection->waitForBytesWritten()){
        qInfo() << "JOIN request sent!" << endl;
    }
}

void Twitch::sendMessage(QString message){
    QString raw = "PRIVMSG #" + this->channel + " :" + message + "\r\n";
    std::string MSG = raw.toStdString();
    this->connection->write(MSG.c_str());
}

void Twitch::enableCommands(){
    QString request = "CAP REQ :twitch.tv/commands\r\n";
    std::string REQ = request.toStdString();
    this->connection->write(REQ.c_str());
    qInfo() << "command request sent!" << endl;
}

void Twitch::enableTags(){
    QString request = "CAP REQ :twitch.tv/tags\r\n";
    std::string REQ = request.toStdString();
    this->connection->write(REQ.c_str());
    qInfo() << "tags request sent!" << endl;
}

void Twitch::ban(QString username){
    this->sendMessage("/ban " + username);
}

void Twitch::purge(QString username, int time){
    this->sendMessage("/timeout " + username + " " + QString::number(time));
}

void Twitch::remove(QString id){
    this->sendMessage("/delete " + id);
}
