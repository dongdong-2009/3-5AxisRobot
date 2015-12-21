#include "icsubmodifydialog.h"
#include "ui_icsubmodifydialog.h"

ICSubModifyDialog::ICSubModifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICSubModifyDialog)
{
    ui->setupUi(this);
    validator = new QIntValidator(0, 30000, this);


}

ICSubModifyDialog::~ICSubModifyDialog()
{
    delete ui;
}

void ICSubModifyDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

bool ICSubModifyDialog::ShowModifyItem(const ICMoldItem *item, ICMoldItem* ret, const QString &text)
{

    ui->currentMoldItemLabel->setText(text);

    ui->delayEdit->SetDecimalPlaces(2);
    ui->delayEdit->setValidator(validator);
//    ui->label->setText(tr("Delay Time:"));


    ui->delayEdit->SetThisIntToThisText(item->DVal());
    int isok = exec();
    if(isok == QDialog::Accepted)
    {

        ret->SetDVal(ui->delayEdit->TransThisTextToThisInt());
        return true;

    }
    return false;
}

void ICSubModifyDialog::on_okButton_clicked()
{
    this->accept();
}

void ICSubModifyDialog::on_cancelButton_clicked()
{
    this->reject();
}
