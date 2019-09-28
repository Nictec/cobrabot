#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatparser.h"
#include<QDebug>
#include <QtWidgets>
#include <QLayout>
#include <QtAwesome.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //connect to the twitch irc server
    this->twitchHandler = new Twitch;
    this->twitchHandler->connectToServer("irc.chat.twitch.tv", 6667);
    this->twitchHandler->login();

    //start the ui
    ui->setupUi(this);

    //connect the receive signal to the receive slot
    connect(twitchHandler->connection, SIGNAL(readyRead()), this, SLOT(onChat()));

    //join the defined channel and enable twitch commands
    this->twitchHandler->join();
    this->twitchHandler->enableCommands();
    this->twitchHandler->enableTags();
    this->ui->chatField->addItem("Info: Verbindung erfolgreich");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString text = this->ui->ChatInput->text();
    this->twitchHandler->sendMessage(text);
    this->ui->ChatInput->clear();
}

void MainWindow::onChat(){
    QString readline = this->twitchHandler->connection->readAll();
    if (readline.startsWith("PING")){
        QString answer = "PONG :tmi.twitch.tv\r\n";
        std::string PONG = answer.toStdString();
        this->twitchHandler->connection->write(PONG.c_str());
    } else {
       ChatParser parser;
       QString message  = parser.parse(readline);
       if (message != ""){
           //load FontAwesome
           QtAwesome* awesome = new QtAwesome(qApp);
           awesome->initFontAwesome();

           //construct the chat line
           QListWidgetItem* item = new QListWidgetItem();
           QWidget* widget = new QWidget();

           //label constructors
           QLabel* ban = new QLabel();
           QLabel* purge = new QLabel();
           QLabel* del = new QLabel();

           //icon constructor
           QPixmap clock = awesome->icon(fa::clocko).pixmap(QSize(15, 15));
           QPixmap cross = awesome->icon(fa::ban).pixmap(QSize(15, 15));
           QPixmap trash = awesome->icon(fa::trash).pixmap(QSize(15, 15));

           //set the icons as the content of the labels
           purge->setPixmap(clock);
           purge->setStyleSheet("QLabel {margin-bottom: 15px}");
           ban->setPixmap(cross);
           ban->setStyleSheet("QLabel {margin-bottom: 15px}");
           del->setPixmap(trash);
           del->setStyleSheet("QLabel {margin-bottom: 15px}");

           //text label constructor
           QLabel* text = new QLabel(message);

           //layout constructor
           QHBoxLayout* widgetLayout = new QHBoxLayout();
           widgetLayout->setContentsMargins(0, 0, 0, 0);
           widgetLayout->setAlignment(Qt::Alignment(Qt::AlignLeft));
           widgetLayout->addWidget(ban, 0);
           widgetLayout->addWidget(purge, 0);
           widgetLayout->addWidget(del, 0);
           widgetLayout->addWidget(text, 0);
           widget->setLayout(widgetLayout);
           //add the layout to the item

           item->setSizeHint(widget->sizeHint());

           //add the item to the chat console
           this->ui->chatField->addItem(item);
           this->ui->chatField->setItemWidget(item, widget);
       }
    }
}
