#ifndef CHATPARSER_H
#define CHATPARSER_H

#include <QObject>
#include "twitch.h"
#include "modtools.h"

class PrivMessage
{
public:
    QString badgeInfo;
    QString badges;
    QString color;
    QString username;
    QString id;
    bool subscriber;
    bool prime;
    bool mod;
    QString message;

    PrivMessage(QString badgeInfo, QString badges, QString color, QString username, QString id, bool subscriber, bool prime, bool mod, QString message);
};

class ChatParser : public QObject
{
    Q_OBJECT
public:
    explicit ChatParser(QObject *parent = nullptr);
    QStringList parse(QString raw, Twitch *twitch, QJsonArray commands);

private:
    PrivMessage parsePrivMessage(QString tags, QString message);
    QString profanityProtection(QString tags, QString message);

signals:

public slots:
};

#endif // CHATPARSER_H
