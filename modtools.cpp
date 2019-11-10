#include "modtools.h"
#include <QDir>
#include <QDebug>
#include "mustache.h"
#include <ctype.h>

Modtools::Modtools(QObject *parent) : QObject(parent)
{
    //load the caps settings from file
    QString capsSettings = QDir::currentPath() + "/config/caps.ini";
    qInfo() << "Settings: " << capsSettings;
    QSettings settings(capsSettings, QSettings::IniFormat);
    this->capsPunishment = settings.value("punishment").toInt();
    this->maxCaps = settings.value("max_caps").toInt();
    this->capsReplyTemplate = settings.value("reply").toString();

    //load the sym settings from file
    QString symSettings = QDir::currentPath() + "/config/symbols.ini";
    qInfo() << "Settings: " << symSettings;
    QSettings settingsSym(symSettings, QSettings::IniFormat);
    this->symPunishment = settingsSym.value("punishment").toInt();
    this->maxSym = settingsSym.value("max_sym").toInt();
    this->symReplyTemplate = settingsSym.value("reply").toString();

    //load the profanity list
    QString profSettings = QDir::currentPath() + "/config/profanity.ini";
    QSettings settingsProf(profSettings, QSettings::IniFormat);
    settingsProf.beginGroup("profanities");
    this->profanityKeys = settingsProf.allKeys();

    //load the profanity settings
    settingsProf.endGroup();
    settingsProf.beginGroup("settings");
    this->profanityPunishment = settingsProf.value("punishment").toInt();
    this->profanityReplyTemplate = settingsProf.value("response").toString();
}

void Modtools::setCapsSettings(int punishment, int max, QString reply){
    //write to the ini file
    QString capsSettings = QDir::currentPath() + "/config/caps.ini";
    QSettings settings(capsSettings, QSettings::IniFormat);
    settings.setValue("punishment", punishment);
    settings.setValue("max_caps", max);
    settings.setValue("reply", reply);

    //set the settings in the object
    this->capsPunishment = punishment;
    this->maxCaps = max;
    this->capsReplyTemplate = reply;
}

void Modtools::setSymSettings(int punishment, int max, QString reply){
    //write to the ini file
    QString symSettings = QDir::currentPath() + "/config/symbols.ini";
    QSettings settingsSym(symSettings, QSettings::IniFormat);
    settingsSym.setValue("punishment", punishment);
    settingsSym.setValue("max_sym", max);
    settingsSym.setValue("reply", reply);

    //set the settings in the object
    this->symPunishment = punishment;
    this->maxSym = max;
    this->symReplyTemplate = reply;
}

QString Modtools::checkCaps(QString message, bool isMod, QString username, QString msgId, Twitch *twitch){
    if (isMod) {
        return message;
    } else {
        QStringList words = message.split(" ");
        int uppercase = 0;
        for(int i = 0; i < words.length(); i++){
            if (words[i].isUpper()){
                uppercase = uppercase + 1;
            }
        }
        if (uppercase >= this->maxCaps){
            qInfo() << "To many caps letters";
            if (this->capsPunishment == 0){
                twitch->purge(username, 30);
                twitch->remove(msgId);
            } else if(this->capsPunishment == 1){
                twitch->ban(username);
            } else {
                twitch->remove(msgId);
            }
            QVariantHash tmplData;
            tmplData["user"] = username;
            if (capsPunishment == 0){
                tmplData["punishment"] = "timeout";
            } else if (capsPunishment == 1){
                tmplData["punishment"] = "ban";
            } else {
                tmplData["punishment"] = "message removal";
            }

            Mustache::Renderer renderer;
            Mustache::QtVariantContext context(tmplData);
            QString resp = renderer.render(this->capsReplyTemplate, &context);

            twitch->sendMessage(resp);
            return resp;
        } else {
            return message;
        }
    }
}

QString Modtools::checkSymbols(QString message, bool isMod, QString username, QString msgId, Twitch *twitch){
    if (isMod){
        return message;
    } else {
        qInfo() << "To many symbols";
        //split the message in words
        QStringList words = message.split(" ");
        //split the words in letters
        QStringList letters;
        for (int i = 0; i < words.length(); i++){
            letters.append(words[i].split(""));
        }
        letters.removeAll(QString(""));
        letters.removeAll(QString("\r"));
        letters.removeAll(QString("\n"));
        qWarning() << letters;
        //check if the letter is alphabetical, else add to symbol number
        int symbols = 0;
        for (int i = 0; i < letters.length(); i++){
            if (!std::isalnum(letters[i].toStdString()[0])){
                symbols++;
            }
        }
        qInfo() << symbols;
        if (symbols >= this->maxSym){
            if (this->symPunishment == 0){
                twitch->purge(username, 30);
                twitch->remove(msgId);
            } else if(this->symPunishment == 1){
                twitch->ban(username);
            } else {
                twitch->remove(msgId);
            }
            QVariantHash tmplData;
            tmplData["user"] = username;
            if (symPunishment == 0){
                tmplData["punishment"] = "timeout";
            } else if (symPunishment == 1){
                tmplData["punishment"] = "ban";
            } else {
                tmplData["punishment"] = "message removal";
            }

            Mustache::Renderer renderer;
            Mustache::QtVariantContext context(tmplData);
            QString resp = renderer.render(this->symReplyTemplate, &context);

            twitch->sendMessage(resp);
            return resp;
        }else{
            return message;
        }
    }
}

QString Modtools::checkProfanity(QString message, bool isMod, QString username, QString msgId, Twitch *twitch){
    if (isMod){
        return message;
    } else {
        QString profSettings = QDir::currentPath() + "/config/profanity.ini";
        QSettings settingsProf(profSettings, QSettings::IniFormat);
        settingsProf.beginGroup("profanities");

        for (int i = 0; i < this->profanityKeys.length(); i++){
            if (message.indexOf(profanityKeys[i]) != -1) {
                int punishment = settingsProf.value(profanityKeys[i]).toInt();
                QVariantHash tmplData;
                tmplData["user"] = username;
                if (punishment == 0){
                    twitch->purge(username, 30);
                    tmplData["punishment"] = "timeout";
                } else if (punishment == 1){
                    twitch->ban(username);
                    tmplData["punishment"] = "ban";
                } else {
                    twitch->remove(msgId);
                    tmplData["punishment"] = "message removal";
                }
                //if a profanity is found break the loop
                Mustache::Renderer renderer;
                Mustache::QtVariantContext context(tmplData);
                QString resp = renderer.render(this->profanityReplyTemplate, &context);

                twitch->sendMessage(resp);
                return resp;
            }
        }
        return message;
    }
}
