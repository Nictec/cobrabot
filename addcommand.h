#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include <QDialog>
#include "cobralink.h"

namespace Ui {
class AddCommand;
}

class AddCommand : public QDialog
{
    Q_OBJECT

public:
    explicit AddCommand(QWidget *parent = nullptr);
    ~AddCommand();

private slots:
    void on_script_chooser_clicked();

    void on_buttonBox_accepted();

private:
    Ui::AddCommand *ui;
    QString path;

signals:
    void jsonReady(bool active, QString command, int cost, bool mod, QString response, QString description);
};

#endif // ADDCOMMAND_H
