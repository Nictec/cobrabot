#ifndef MODTOOLS_H
#define MODTOOLS_H

#include <QObject>
#include <QSettings>
#include "twitch.h"

class Modtools : public QObject
{
    Q_OBJECT
public:
    //caps settings
    int capsPunishment;
    int maxCaps;
    QString capsReplyTemplate;

    //symbol settings
    int symPunishment;
    int maxSym;
    QString symReplyTemplate;

    //profanity list
    QStringList profanityKeys;

    explicit Modtools(QObject *parent = nullptr);

    void setCapsSettings(int punishment, int max, QString reply);
    void setSymSettings(int punishment, int max, QString reply);
    QString checkCaps(QString message, bool isMod, QString username, QString msgId, Twitch *twitch);
    QString checkSymbols(QString message, bool isMod, QString username, QString msgId, Twitch *twitch);
signals:

public slots:
};

#endif // MODTOOLS_H
