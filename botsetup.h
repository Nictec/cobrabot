#ifndef BOTSETUP_H
#define BOTSETUP_H

#include <QDialog>
#include <twitch.h>

namespace Ui {
class BotSetup;
}

class BotSetup : public QDialog
{
    Q_OBJECT

public:
    explicit BotSetup(QWidget *parent = nullptr);
    ~BotSetup();
    QString BotToken;
    void setError(QString message);

private slots:

    void on_generateButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::BotSetup *ui;
};

class WebPipe : public QObject
{
    Q_OBJECT
public:
    WebPipe(int step);
    int setupStep;
public slots:
    void tokenCallback(const QString *token);
};

#endif // BOTSETUP_H
