#include "ichcotherpage.h"
#include "ui_ichcotherpage.h"

ICHCOtherPage::ICHCOtherPage(QWidget *parent) :
    ICInstructionEditorBase(parent),
    ui(new Ui::ICHCOtherPage)
{
    ui->setupUi(this);
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
    else if(ui->offsetSel->isChecked())
    {
        item.SetIFVal(8);
        item.SetSVal(ui->rpSel->isChecked()? 2 : 1);
        item.SetDVal(ui->offsetAxis->currentIndex());
    }
    else
        return ret;
    ret.append(item);
    return ret;
}
