#ifndef CHATPARSER_H
#define CHATPARSER_H

#include <QObject>

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
    QString parse(QString raw);

private:
    PrivMessage parsePrivMessage(QString tags, QString message);

signals:

public slots:
};

#endif // CHATPARSER_H
