#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatparser.h"
#include<QDebug>
#include <QLayout>
#include <QtAwesome.h>
#include <QSettings>
#include "botsetup.h"

void MainWindow::loadTable(){
    QString profSettings = QDir::currentPath() + "/config/profanity.ini";
    QSettings settingsProf(profSettings, QSettings::IniFormat);
    settingsProf.beginGroup("profanities");

    //set the profanities table
    for (int i = 0; i < this->modHandler->profanityKeys.length(); i++) {
        this->ui->profTable->insertRow(this->ui->profTable->rowCount());

        QTableWidgetItem *keyWidget = new QTableWidgetItem(this->modHandler->profanityKeys[i]);
        this->ui->profTable->setItem(this->ui->profTable->rowCount()-1, 0, keyWidget);

        int punishmentId = settingsProf.value(this->modHandler->profanityKeys[i]).toInt();
        QString punishment = "";
        if (punishmentId == 0){
            punishment = "Purge";
        } else if (punishmentId == 1){
            punishment = "Ban";
        } else {
            punishment = "Remove";
        }
        this->ui->profTable->setItem(this->ui->profTable->rowCount()-1, 1, new QTableWidgetItem(punishment));
    }
    this->ui->profTable->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //connect to the twitch irc server
    this->twitchHandler = new Twitch;
    this->twitchHandler->connectToServer("irc.chat.twitch.tv", 6667);
    this->twitchHandler->login();

    //load the modtool settings
    this->modHandler = new Modtools;

    //start the ui
    ui->setupUi(this);

    //check if the twitch.ini exists, if not open the setup dialog
    if (!QFileInfo::exists(QDir::currentPath() + "/config/twitch.ini")){
       BotSetup *bot = new BotSetup;
       bot->show();
    }

    //set the fields in the ui
    this->ui->capsPunish->setCurrentIndex(this->modHandler->capsPunishment);
    this->ui->capsMin->setValue(this->modHandler->maxCaps);
    this->ui->capsReply->setText(this->modHandler->capsReplyTemplate);

    this->ui->symPunish->setCurrentIndex(this->modHandler->symPunishment);
    this->ui->symMin->setValue(this->modHandler->maxSym);
    this->ui->symReply->setText(this->modHandler->symReplyTemplate);

    this->ui->profanityReply->setText(this->modHandler->profanityReplyTemplate);
    this->ui->profanityPunishment->setCurrentIndex(this->modHandler->profanityPunishment);

    this->loadTable();

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

    //text label constructor
    QLabel* label = new QLabel("Bot: "+ text);
    QListWidgetItem* item = new QListWidgetItem();
    this->ui->chatField->addItem(item);
    this->ui->chatField->setItemWidget(item, label);

    this->ui->ChatInput->clear();
}

//handle the ui events
void MainWindow::on_ban(){
    BanButton* clickedButton = qobject_cast<BanButton*>(sender());
    twitchHandler->ban(clickedButton->username);
}

void MainWindow::on_purge(){
    PurgeButton* clickedButton = qobject_cast<PurgeButton*>(sender());
    twitchHandler->purge(clickedButton->username, clickedButton->time);
}

void MainWindow::on_delete(){
    DeleteButton* clickedButton = qobject_cast<DeleteButton*>(sender());
    twitchHandler->remove(clickedButton->mid);
}

void MainWindow::onChat(){
    QString readline = this->twitchHandler->connection->readAll();
    //qInfo() << readline;
    if (readline.startsWith("PING")){
        QString answer = "PONG :tmi.twitch.tv\r\n";
        std::string PONG = answer.toStdString();
        this->twitchHandler->connection->write(PONG.c_str());
    } else {
       ChatParser parser;
       QStringList message  = parser.parse(readline, twitchHandler);
       qInfo() << message;
       if (message.length() == 3){
           //load FontAwesome
           QtAwesome* awesome = new QtAwesome(qApp);
           awesome->initFontAwesome();

           //construct the chat line
           QListWidgetItem* item = new QListWidgetItem();
           QWidget* widget = new QWidget();

           //button constructors
           BanButton* ban = new BanButton();
           ban->username = message[2];

           PurgeButton* purge = new PurgeButton();
           purge->username = message[2];
           purge->time = 30;
           DeleteButton* del = new DeleteButton();
           del->mid = message[1];

           if (message[1] == "ntc"){
               ban->setEnabled(false);
               purge->setEnabled(false);
               del->setEnabled(false);
           }

           //connect the buttons to the slots
           connect(ban, SIGNAL(clicked()), this, SLOT(on_ban()));
           connect(purge, SIGNAL(clicked()), this, SLOT(on_purge()));
           connect(del, SIGNAL(clicked()), this, SLOT(on_delete()));

           //icon constructor
           QPixmap clock = awesome->icon(fa::clocko).pixmap(QSize(15, 15));
           QPixmap cross = awesome->icon(fa::ban).pixmap(QSize(15, 15));
           QPixmap trash = awesome->icon(fa::trash).pixmap(QSize(15, 15));

           //set the icons as the content of the labels
           purge->setIcon(clock);
           ban->setIcon(cross);
           del->setIcon(trash);

           //text label constructor
           QLabel* text = new QLabel(message[0]);

           //layout constructor
           QHBoxLayout* widgetLayout = new QHBoxLayout();
           widgetLayout->setContentsMargins(0, 0, 0, 0);
           widgetLayout->setAlignment(Qt::Alignment(Qt::AlignLeft));
           widgetLayout->addWidget(ban, 0);
           widgetLayout->addWidget(purge, 0);
           widgetLayout->addWidget(del, 0);
           widgetLayout->addWidget(text, 0);
           //add the layout to the item
           widget->setLayout(widgetLayout);
           item->setSizeHint(widget->sizeHint());

           //add the item to the chat console
           this->ui->chatField->addItem(item);
           this->ui->chatField->setItemWidget(item, widget);
       }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int punishment = this->ui->capsPunish->currentIndex();
    int min = this->ui->capsMin->value();
    QString reply = this->ui->capsReply->text();

    this->modHandler->setCapsSettings(punishment, min, reply);
}

void MainWindow::on_pushButton_3_clicked()
{
    int punishment = this->ui->symPunish->currentIndex();
    int min = this->ui->symMin->value();
    QString reply = this->ui->symReply->text();
    this->modHandler->setSymSettings(punishment, min, reply);
}

void MainWindow::on_pushButton_4_clicked()
{
    this->profanityDialog = new QDialog();
    this->profanityDialog->setWindowTitle("Add Profanity filter");
    this->profanityDialog->resize(500, 200);

    QFormLayout form(this->profanityDialog);
    QLabel *wordLabel = new QLabel;
    QLabel *punishLabel = new QLabel;
    this->profanityWord = new QLineEdit;
    this->profanityPunishment = new QComboBox;
    QPushButton *save = new QPushButton;

    this->profanityPunishment->addItem("Purge");
    this->profanityPunishment->addItem("Ban");
    this->profanityPunishment->addItem("Remove");
    save->setText("speichern");
    wordLabel->setText("Forbidden word:");
    punishLabel->setText("Punishment:");

    form.addRow(wordLabel);
    form.addRow(this->profanityWord);
    form.addRow(punishLabel);
    form.addRow(this->profanityPunishment);
    form.addRow(save);

    this->profanityDialog->show();

    connect(save, SIGNAL(clicked()), this, SLOT(on_profanity_save()));
}

void MainWindow::on_profanity_save(){
    QString word = this->profanityWord->text();
    int punishment = this->profanityPunishment->currentIndex();

    //write to the ini file
    QString capsSettings = QDir::currentPath() + "/config/profanity.ini";
    QSettings settings(capsSettings, QSettings::IniFormat);
    settings.beginGroup("profanities");

    settings.setValue(word, punishment);

    this->ui->profTable->insertRow(this->ui->profTable->rowCount());
    QTableWidgetItem *keyWidget = new QTableWidgetItem(word);
    this->ui->profTable->setItem(this->ui->profTable->rowCount()-1, 0, keyWidget);

    //add the new word to the table
    QString punishmentText;
    if (punishment == 0){
        punishmentText = "Purge";
    } else if (punishment == 1){
        punishmentText = "Ban";
    } else {
        punishmentText = "Remove";
    }
    this->ui->profTable->setItem(this->ui->profTable->rowCount()-1, 1, new QTableWidgetItem(punishmentText));

    this->profanityDialog->close();
}

void MainWindow::on_save_profanity_response_clicked()
{
    QString capsSettings = QDir::currentPath() + "/config/profanity.ini";
    QSettings settings(capsSettings, QSettings::IniFormat);
    settings.beginGroup("settings");

    settings.setValue("response", this->ui->profanityReply->text());
    settings.setValue("punishment", this->ui->profanityPunishment->currentIndex());

}

void MainWindow::on_pushButton_5_clicked()
{
    QString settingsFile = QDir::currentPath() + "/config/profanity.ini";
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("profanities");
    settings.remove("");
    settings.endGroup();
    this->ui->profTable->setRowCount(0);
}
