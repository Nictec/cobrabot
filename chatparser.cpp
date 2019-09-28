#include "chatparser.h"

QString getValue(QString tag){
    return tag.split('=')[1];
}

PrivMessage::PrivMessage(QString badgeInfo, QString badges, QString color, QString username, QString id, bool subscriber, bool prime, bool mod, QString message){
    this->badgeInfo = badgeInfo;
    this->badges = badges;
    this->color = color;
    this->username = username;
    this->id = id;
    this->subscriber = subscriber;
    this->prime = prime;
    this->mod = mod;
    this->message = message;
}

ChatParser::ChatParser(QObject *parent) : QObject(parent)
{

}

QString ChatParser::parse(QString raw){
    if (raw.startsWith("@")){
        //split the message in the main parts
        QStringList msgList = raw.split(' ');
        QString tags = msgList[0];
        QString command = msgList[2];
        QString message = msgList[4].remove(0, 1);

        //parse all important message types
        if (command == "PRIVMSG"){
            PrivMessage data = this->parsePrivMessage(tags, message);
            return data.username + ": " + data.message;
        }
    } else {
        return "";
    }
}

PrivMessage ChatParser::parsePrivMessage(QString tags, QString message){
    QStringList tagList = tags.split(";");
    return PrivMessage(getValue(tagList[0]), getValue(tagList[1]), getValue(tagList[2]), getValue(tagList[3]), getValue(tagList[6]), getValue(tagList[9]).toInt(), getValue(tagList[11]).toInt(), getValue(tagList[7]).toInt(), message);
}
