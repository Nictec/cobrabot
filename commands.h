#ifndef COMMANDS_H
#define COMMANDS_H

#include <QObject>
#include "chatparser.h"

class Commands : public QObject
{
    Q_OBJECT
public:
    explicit Commands(QObject *parent = nullptr);
    QString evaluate(PrivMessage message, QJsonArray list, Twitch *twitch);

signals:

};

#endif // COMMANDS_H
