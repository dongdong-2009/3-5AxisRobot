#include "ichcconditionpage.h"
#include "ui_ichcconditionpage.h"
#include "iccommandprocessor.h"
#include "icvirtualhost.h"

ICHCConditionPage::ICHCConditionPage(QWidget *parent) :
    ICInstructionEditorBase(parent),
    ui(new Ui::ICHCConditionPage)
{
    ui->setupUi(this);
//    ui->returnLineEdit->setValidator(new QIntValidator(-32767, 32767, this));
    buttonGroup = new QButtonGroup;
    onOffButtonGroup = new QButtonGroup;
    ui->subComboBox->setCurrentIndex(5);
    ui->subComboBox->setEnabled(false);
//    ui->returnLineEdit->setText("1");
    InitCheckPointBox();
    ui->moldCountEdit->setEnabled(false);
    ui->moldCountEdit->setValidator(new QIntValidator(0, 65530, this));
#ifdef HC_4F2S
    ui->sucker3Box->setText("X017");
    ui->sucker4Box->setText("X036");
#endif
}

ICHCConditionPage::~ICHCConditionPage()
{
    delete ui;
}

void ICHCConditionPage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
#ifdef HC_4F2S
    ui->sucker3Box->setText("X017");
    ui->sucker4Box->setText("X036");
#endif
        break;
    default:
        break;
    }
}

void ICHCConditionPage::SyncStatusImpl(const QList<ICMoldItem> &items)
{
    Q_UNUSED(items)
}


QList<ICMoldItem> ICHCConditionPage::CreateCommandImpl() const
{
    QList<ICMoldItem> ret;
    if(ui->flagSel->currentIndex() < 0)
        return ret;
    ICMoldItem item;
    item.SetAction(ICMold::ACTCHECKINPUT);
    item.SetPos(0);
    //////////////////////////////////////////////
    uint ifValTemp = buttonGroup->checkedId();
    ifValTemp &= 0xff7f;
    if(onOffButtonGroup->checkedId() == 0)
    {
        ifValTemp |= 1 << 7;
    }
    else if(onOffButtonGroup->checkedId() == 1)
    {
        ifValTemp |= 0 << 7;
    }
    item.SetIFVal(ifValTemp);
    ////////////////////////////////////////////////
    ifValTemp = buttonGroup->checkedId();
    ifValTemp &= 0xff7f;
    if(ifValTemp == 3)
    {
        item.SetSVal(7);
    }
    else if(ifValTemp == 4)
    {
        item.SetSVal(6);
    }
    else if(ifValTemp == 11)
    {
        item.SetIFPos(ui->moldCountEdit->TransThisTextToThisInt());
        item.SetSVal(ui->subComboBox->currentIndex());
    }
    else
    {
        item.SetSVal(ui->subComboBox->currentIndex());
    }
    QString flag = ui->flagSel->currentText();
    int l = flag.indexOf('[') + 1;
    int r = flag.indexOf(']');
    flag = flag.mid(l, r - l);
    item.SetFlag(flag.toInt());
    ret.append(item);
    return ret;
}

void ICHCConditionPage::InitCheckPointBox()
{
    buttonGroup->addButton(ui->defectiveProductsBox,0);
    buttonGroup->addButton(ui->x043checkBox,1);
    buttonGroup->addButton(ui->x044checkBox,2);
    buttonGroup->addButton(ui->tryProductBox,3);
    buttonGroup->addButton(ui->samplingBox,4);
    buttonGroup->addButton(ui->fixture1Box, 5);
    buttonGroup->addButton(ui->fixture2Box, 6);
    buttonGroup->addButton(ui->fixture3Box, 7);
    buttonGroup->addButton(ui->fixture4Box, 8);
    buttonGroup->addButton(ui->sucker1Box, 9);
    buttonGroup->addButton(ui->sucker2Box, 10);
    buttonGroup->addButton(ui->productCountBox, 11);
    buttonGroup->addButton(ui->sucker3Box, 12);
    buttonGroup->addButton(ui->sucker4Box, 13);
    buttonGroup->addButton(ui->x045checkBox, 14);
    buttonGroup->addButton(ui->x046checkBox, 15);
    buttonGroup->addButton(ui->x047checkBox, 16);
    buttonGroup->addButton(ui->x026checkBox, 17);
    buttonGroup->addButton(ui->x040checkBox, 18);
    buttonGroup->addButton(ui->x023checkBox, 19);
    buttonGroup->addButton(ui->x037checkBox, 20);

    onOffButtonGroup->addButton(ui->oncheckBox, 0);
    onOffButtonGroup->addButton(ui->offcheckBox, 1);


    QList<QAbstractButton*> buttons = buttonGroup->buttons();
    for(int i = 0; i != buttons.size(); ++i)
    {
        buttons[i]->setCheckable(true);
        connect(buttons[i],
                SIGNAL(clicked()),
                this,
                SLOT(BoxClicked()));
    }
    buttonGroup->setExclusive(true);
}

void ICHCConditionPage::BoxClicked()
{
    int temp = buttonGroup->checkedId();
    switch(temp)
    {
    case 0:
        ui->subComboBox->setCurrentIndex(5);
        ui->subComboBox->setEnabled(false);
        break;
    case 3:
        ui->subComboBox->setCurrentIndex(7);
        ui->subComboBox->setEnabled(false);
        break;
    case 4:
        ui->subComboBox->setCurrentIndex(6);
        ui->subComboBox->setEnabled(false);
        break;
    default:
        ui->subComboBox->setCurrentIndex(0);
        ui->subComboBox->setEnabled(true);
        break;
    }
}

void ICHCConditionPage::on_productCountBox_toggled(bool checked)
{
    ui->moldCountEdit->setEnabled(checked);
}

void ICHCConditionPage::ResetFlagSel(const QStringList &selList)
{
    ui->flagSel->clear();
    ui->flagSel->addItems(selList);
}
