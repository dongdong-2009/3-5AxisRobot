#include "ichcotherpage.h"
#include "ui_ichcotherpage.h"

ICHCOtherPage::ICHCOtherPage(QWidget *parent) :
    ICInstructionEditorBase(parent),
    ui(new Ui::ICHCOtherPage)
{
    ui->setupUi(this);
    ui->widthEdit->SetDecimalPlaces(2);
    ui->widthEdit->setValidator(new QIntValidator(0, 10000, this));
    ui->speedEdit->SetDecimalPlaces(0);
    ui->speedEdit->setValidator(new QIntValidator(0, 100, this));
    ui->delayEdit->SetDecimalPlaces(2);
    ui->delayEdit->setValidator(new QIntValidator(0, 30000, this));
}

ICHCOtherPage::~ICHCOtherPage()
{
    delete ui;
}

void ICHCOtherPage::changeEvent(QEvent *e)
{
    ICInstructionEditorBase::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QList<ICMoldItem> ICHCOtherPage::CreateCommandImpl() const
{
    QList<ICMoldItem> ret;
    ICMoldItem item;
    item.SetAction(ICMold::ACT_OTHER);
    if(ui->clearButton->isChecked())
    {
        item.SetIFVal(1);
    }
    else if(ui->shakeGroup->isChecked())
    {
        item.SetAction(ICMold::ACT_Shake);
        item.SetActualPos(ui->widthEdit->TransThisTextToThisInt());
        item.SetSVal(ui->speedEdit->TransThisTextToThisInt());
        item.SetDVal(ui->delayEdit->TransThisTextToThisInt());
        item.SetBadProduct(ui->rPbox->isChecked());
        int ifv = item.IFPos();
        ifv |= ui->stEdit->TransThisTextToThisInt() << 8;
        ifv |= (ui->axisSel->currentIndex() + 1) << 12;
        item.SetIFPos(ifv);
    }
    else
        return ret;
    ret.append(item);
    return ret;
}
