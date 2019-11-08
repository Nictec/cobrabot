#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //open the splashscreen
    QDialog *SplashScreen = new QDialog();
    SplashScreen->setWindowTitle("CobraBot is loading...");
    SplashScreen->resize(500, 500);

    QFormLayout form(SplashScreen);
    QLabel *notice = new QLabel("CobraBot is loading...");
    form.addRow(notice);
    SplashScreen->show();

    MainWindow w;
    w.setWindowTitle("CobraBot");

    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    SplashScreen->close();
    w.show();

    return a.exec();
}
