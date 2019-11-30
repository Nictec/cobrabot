#ifndef COBRALINK_H
#define COBRALINK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDialog>
#include "botsetup.h"

class CobraLink : public QObject
{
    Q_OBJECT
public:
    explicit CobraLink(QObject *parent = nullptr);

    QDialog *window;
    bool verifyCredentials(QString botToken, QString streamerToken, QString cobraToken);

signals:

private slots:
    void authResponse(QNetworkReply *reply);

private:
    //auth check
    QNetworkAccessManager *authManager;
    QNetworkRequest authRequest;
    QJsonDocument authAnswer;
    QMap<QString, QString> *formData;
    bool success;
};

#endif // COBRALINK_H
