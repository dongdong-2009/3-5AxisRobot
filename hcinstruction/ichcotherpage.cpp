#include "ichcotherpage.h"
#include "ui_ichcotherpage.h"

ICHCOtherPage::ICHCOtherPage(QWidget *parent) :
    ICInstructionEditorBase(parent),
    ui(new Ui::ICHCOtherPage)
{
    ui->setupUi(this);
    ui->limitEdit->setValidator(new QIntValidator(0, 65530, this));
    ui->limitEdit->SetDecimalPlaces(2);
}

ICHCOtherPage::~ICHCOtherPage()
{
    delete ui;
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
    if(ui->x037Button->isChecked())
    {
        item.SetIFVal(2);
    }
    if(ui->x023Button->isChecked())
    {
        item.SetIFVal(3);
    }
    if(ui->x043Button->isChecked())
    {
        item.SetIFVal(4);
    }
    if(ui->x044Button->isChecked())
    {
        item.SetIFVal(5);
    }
    if(ui->x016Button->isChecked())
    {
        item.SetIFVal(6);
    }
    if(ui->x017Button->isChecked())
    {
        item.SetIFVal(7);
    }
    if(ui->x036Button->isChecked())
    {
        item.SetIFVal(8);
    }
    item.SetDVal(ui->limitEdit->TransThisTextToThisInt());
    ret.append(item);
    return ret;
}
