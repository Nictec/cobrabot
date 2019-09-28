#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <twitch.h>

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

private slots:
    void on_pushButton_clicked();
    void onChat();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
