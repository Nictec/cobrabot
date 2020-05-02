#include "commands.h"
#include "QJsonArray"
#include "QJsonObject"
#include "QRandomGenerator"
#include "mustache.h"
#include "QDebug"
#include <QJSEngine>
#include <QFile>
#include <QMessageBox>
#include <QDir>

Commands::Commands(QObject *parent) : QObject(parent)
{

}

QString Commands::evaluate(PrivMessage message, QJsonArray list, Twitch *twitch){
    qDebug() << "evaluating command, list:";
    qDebug() << list << endl;
    if(message.message.startsWith("!")){
        QStringList args = message.message.split(" ");
        QString command = args[0];
        args.removeFirst();
        QJsonObject cmdData;
        foreach(const QJsonValue & v, list){
            qDebug() << v.toObject().value("cmd").toString() << "  " << command.remove(QRegExp("[\\n\\t\\r]"));
            if (v.toObject().value("cmd").toString() == command.remove(QRegExp("[\\n\\t\\r]"))){
                cmdData = v.toObject();
                break;
            }
        }
        if (cmdData.value("response").toString().startsWith("script>>")){
            //load the script file
            QString filename = cmdData.value("response").toString().split(" ")[1];
            QFile scriptFile(QDir::currentPath() + "/scripts/" + filename);
            if (!scriptFile.open(QIODevice::ReadOnly)){
                QMessageBox messageBox;
                messageBox.critical(0,"Script Error","Could not load needed script file!");
                messageBox.setFixedSize(500,200);
            }
            QTextStream stream(&scriptFile);
            QString script = stream.readAll();
            scriptFile.close();
            //run the script file
            QJSEngine engine;
            QJSValue entrypoint = engine.evaluate(script, filename);
            QJSValue jsArray = engine.newArray(args.length());
            for (int i = 0; i<args.length(); i++){
                jsArray.setProperty(i, args[i]);
            }
            QJSValueList arguments;
            arguments << command << message.username << message.id << message.subscriber << message.mod << jsArray;
            QJSValue js_result = entrypoint.call(arguments);
            if (js_result.isError()){
                QMessageBox messageBox;
                messageBox.critical(0,"Script error", js_result.property("lineNumber").toString() + ":" + js_result.toString());
                messageBox.setFixedSize(500,200);
            }
            twitch->sendMessage(js_result.toString());
            return js_result.toString();
        } else {
            QVariantHash templateData;
            templateData["username"] = message.username;
            templateData["msg_id"] = message.id;
            templateData["is_subscriber"] = message.subscriber;
            templateData["is_mod"] = message.mod;
            templateData["random"] = QRandomGenerator::global()->bounded(0, 101);

            Mustache::Renderer renderer;
            Mustache::QtVariantContext context(templateData);
            QString resp = renderer.render(cmdData.value("response").toString(), &context);
            twitch->sendMessage(resp);
            return resp;
        }
    } else {
        return message.message;
    }
    return message.message;
}
