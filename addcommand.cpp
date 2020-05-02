#include "addcommand.h"
#include "ui_addcommand.h"
#include "cobralink.h"
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QJsonObject>

AddCommand::AddCommand(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCommand)
{
    ui->setupUi(this);
}

AddCommand::~AddCommand()
{
    delete ui;
}

void AddCommand::on_script_chooser_clicked()
{
     this->path = QFileDialog::getOpenFileName(this, "Import script", "ECMAScript (*.js)");
     this->ui->script_path->setText(this->path);
}

void AddCommand::on_buttonBox_accepted()
{
    QString filename = this->path.split("/").last();
    QString command = this->ui->command->text();
    QString response;
    int cost = this->ui->cost->text().toInt();
    QString description = this->ui->description->toPlainText();
    bool modOnly = this->ui->mod_only->isChecked();
    bool enabled = this->ui->mod_only->isChecked();
    if (this->path != ""){
        QFile::copy(this->path, QDir::currentPath() + "/scripts/" + filename);
        response = "script>> " + filename;
    } else {
        response = this->ui->response->toPlainText();
    }
    CobraLink cobra;
    QString settingsFile = QDir::currentPath() + "/config/twitch.ini";
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("CobraLink");
    QString token = settings.value("token").toString();
    cobra.addCommand(token, command, response, cost, description, modOnly, enabled);
    emit jsonReady(enabled, command, cost, modOnly, response, description);
}
