#include "commands.h"
#include "QJsonArray"
#include "QJsonObject"

Commands::Commands(QObject *parent) : QObject(parent)
{

}

QString Commands::evaluate(QString message, QString viewer, bool isMod, QJsonArray list){
    if(message.startsWith("!")){
        QStringList args = message.split(" ");
        QString command = args[0];
        args.removeFirst();
        QJsonObject cmdData;
        foreach(const QJsonValue & v, list){
            if (v.toObject().value("cmd") == command){
                cmdData = v.toObject();
                break;
            }
        }

    } else {
        return message;
    }
}
