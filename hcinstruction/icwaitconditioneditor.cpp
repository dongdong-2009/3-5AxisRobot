#include "icwaitconditioneditor.h"
#include "ui_icwaitconditioneditor.h"

ICWaitConditionEditor::ICWaitConditionEditor(QWidget *parent) :
    ICInstructionEditorBase(parent),
    ui(new Ui::ICWaitConditionEditor)
{
    ui->setupUi(this);
}

ICWaitConditionEditor::~ICWaitConditionEditor()
{
    delete ui;
}

void ICWaitConditionEditor::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QList<ICMoldItem> ICWaitConditionEditor::CreateCommandImpl() const
{
    QList<ICMoldItem> ret;
    ICMoldItem item;
    item.SetAction(ICMold::ACT_WaitMoldOpened);
    item.SetDVal(0);
    if(ui->moldOpenedCheckBox->isChecked())
    {
        item.SetSVal(1);
    }
    else if(ui->securityDoorCheckBox->isChecked())
    {
        item.SetSVal(2);
    }
    else if(ui->x043CheckBox->isChecked())
    {
        item.SetSVal(3);
    }
    else if(ui->x044CheckBox->isChecked())
    {
        item.SetSVal(4);
    }
    else if(ui->xclip1CheckBox->isChecked())
    {
        item.SetSVal(5);
    }
    else if(ui->xclip2CheckBox->isChecked())
    {
        item.SetSVal(6);
    }
    else if(ui->xclip3CheckBox->isChecked())
    {
        item.SetSVal(7);
    }
    else if(ui->xclip4CheckBox->isChecked())
    {
        item.SetSVal(8);
    }
    else if(ui->xclip5CheckBox->isChecked())
    {
        item.SetSVal(9);
    }
    else if(ui->xclip6CheckBox->isChecked())
    {
        item.SetSVal(10);
    }
    else if(ui->euejfCheckBox->isChecked())
    {
        item.SetSVal(11);
    }
    else if(ui->euejbCheckBox->isChecked())
    {
        item.SetSVal(12);
    }
    else if(ui->eucoreinCheckBox->isChecked())
    {
        item.SetSVal(13);
    }
    else if(ui->eucoreoutCheckBox->isChecked())
    {
        item.SetSVal(14);
    }
    else if(ui->x045CheckBox->isChecked())
    {
        item.SetSVal(17);
    }
    else if(ui->x046CheckBox->isChecked())
    {
        item.SetSVal(18);
    }
    else if(ui->x047CheckBox->isChecked())
    {
        item.SetSVal(19);
    }
    else if(ui->x026CheckBox->isChecked())
    {
        item.SetSVal(20);
    }
    else if(ui->x040CheckBox->isChecked())
    {
        item.SetSVal(21);
    }
    else if(ui->x023CheckBox->isChecked())
    {
        item.SetSVal(22);
    }
    else if(ui->x037CheckBox->isChecked())
    {
        item.SetSVal(23);
    }
    else if(ui->x017CheckBox->isChecked())
    {
        item.SetSVal(24);
    }
    else if(ui->x036CheckBox->isChecked())
    {
        item.SetSVal(25);
    }
    else if(ui->eucoreinCheckBox_2->isChecked())
    {
        item.SetSVal(15);
    }
    else if(ui->eucoreoutCheckBox_2->isChecked())
    {
        item.SetSVal(16);
    }
    else return ret;
    ret.append(item);
    return ret;
}
