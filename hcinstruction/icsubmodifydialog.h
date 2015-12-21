#ifndef ICSUBMODIFYDIALOG_H
#define ICSUBMODIFYDIALOG_H

#include <QDialog>
#include <QIntValidator>

#include "icmold.h"


namespace Ui {
class ICSubModifyDialog;
}

class ICSubModifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ICSubModifyDialog(QWidget *parent = 0);
    ~ICSubModifyDialog();

    bool ShowModifyItem(const ICMoldItem* item, ICMoldItem* ret,const QString &text);


protected:
    void changeEvent(QEvent *e);

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ICSubModifyDialog *ui;
    QIntValidator* validator;

};

#endif // ICSUBMODIFYDIALOG_H
