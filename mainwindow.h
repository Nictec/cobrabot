#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <twitch.h>
#include "modtools.h"
#include <QObject>
#include <QtWidgets>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <cobralink.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Twitch *twitchHandler;
    Modtools *modHandler;
    CobraLink *cobra;
    QJsonArray commands;

private slots:
    void on_pushButton_clicked();
    void onChat();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_save_profanity_response_clicked();

    void on_pushButton_5_clicked();

    void on_cmd_load_finished(QNetworkReply *reply);

    void on_pushButton_6_clicked();

public slots:
    void on_ban();
    void on_purge();
    void on_delete();
    void on_profanity_save();

private:
    Ui::MainWindow *ui;
    QDialog *profanityDialog;
    QLineEdit *profanityWord;
    QComboBox *profanityPunishment;

    void loadTable();
};

class BanButton : public QPushButton {
    Q_OBJECT
public:
    QString username;
};

class PurgeButton : public QPushButton {
    Q_OBJECT
public:
    QString username;
    int time;
};

class DeleteButton : public QPushButton {
    Q_OBJECT
public:
    QString mid;
};

#endif // MAINWINDOW_H
