#ifndef COMMANDS_H
#define COMMANDS_H

#include <QObject>

class Commands : public QObject
{
    Q_OBJECT
public:
    explicit Commands(QObject *parent = nullptr);
    QString evaluate(QString message, QString viewer, bool isMod, QJsonArray list);

signals:

};

#endif // COMMANDS_H
