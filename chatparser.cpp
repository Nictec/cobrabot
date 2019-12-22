#include "chatparser.h"
#include <QDebug>

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

QStringList ChatParser::parse(QString raw, Twitch *twitch){
    qInfo() << "pre parse";
    if (raw.startsWith("@")){
        qInfo() << "starts with @: " << raw;
        //split the message in the main parts
        QStringList msgList = raw.split(' ');
        QString tags = msgList[0];
        QString command = msgList[2];

        //parse all important message types
        if (command == "PRIVMSG"){
            QString message;
            for(int i = 0; i < msgList.length(); i++){
                if (i > 3){
                    message = message + " " + msgList[i];
                }
            }
            PrivMessage data = this->parsePrivMessage(tags, message);
            Modtools mod;
            QString baseMessage = data.message;
            data.message = mod.checkCaps(baseMessage, data.mod, data.username, data.id, twitch);
            data.message = mod.checkSymbols(baseMessage, data.mod, data.username, data.id, twitch);
            data.message = mod.checkProfanity(baseMessage, data.mod, data.username, data.id, twitch);
            qInfo() << "Parsing successfull";

            QString colored = "<font color=" + data.color + ">" + data.username + ": </font>" + data.message;
            QString msgId = data.id;
            QString username = data.username;
            QStringList resp;
            resp.append(colored);
            resp.append(msgId);
            resp.append(username);
            qInfo("post parse");
            return resp;
        } else if (command == "NOTICE") {
            QStringList resp;
            QString id = msgList[0].split("=")[1];
            if (id == "bad_unban_no_ban"){
               resp.append("Bot: Dieser User ist nicht gebannt!");
            } else if (id == "ban_success") {
                resp.append("Bot: Benutzer erfolgreich gebannt!");
            } else if (id == "timeout_success") {
                resp.append("Bot: Benutzer für 30 Sekunden in den Timeout versetzt!");
            } else if (id == "delete_message_success"){
                resp.append("Bot: Nachricht wurde entfernt!");
            }
            resp.append("ntc");
            resp.append("Bot");
            return resp;
        } else {
            return QStringList();
        }
    } else {
        qInfo() << "no parse";
        return QStringList();
    }
}

PrivMessage ChatParser::parsePrivMessage(QString tags, QString message){
    QStringList tagList = tags.split(";");
    return PrivMessage(getValue(tagList[0]), getValue(tagList[1]), getValue(tagList[2]), getValue(tagList[3]), getValue(tagList[6]), getValue(tagList[9]).toInt(), getValue(tagList[11]).toInt(), getValue(tagList[7]).toInt(), message.remove(0, 2));
}

QString ChatParser::profanityProtection(QString tags, QString message){
    bool mod = tags.split(";")[7].toInt();
    if (mod){
        return message;
    } else {
        //Caps Protection
    }
}
