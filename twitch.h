#ifndef TWITCH_H
#define TWITCH_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

class Twitch : public QObject
{
    Q_OBJECT
public:
    explicit Twitch(QObject *parent = nullptr);
    QTcpSocket *connection;
    void loadBotConnection();
    void setBotConnection(QString username, QString password, QString channel);
    bool connectToServer(const QString &address, quint16 port);
    void login();
    void join();
    void sendMessage(QString msg);
    void enableCommands();
    void enableTags();
    void ban(QString username);
    void purge(QString username, int time);
    void remove(QString id);

private:
    void disconnectFromServer();

    QString username;
    QString password;
    QString channel;

signals:
    void connected();
    void loggedIn();
    void loginError(const QString &text);
    void disconnected();
    void chat();
    void error(QAbstractSocket::SocketError socketError);
};

#endif // TWITCH_H
