#include "icstructdefineframe.h"
#include "ui_icstructdefineframe.h"

#include "iccommandprocessor.h"
#include "iccommands.h"
#include "icvirtualhost.h"
#include "icparameterssave.h"

#include <QVector>
#include <QMessageBox>
#include <QDebug>
#include "mainframe.h"
#include "icactioncommand.h"
#include "icvirtualkey.h"
#include <QHideEvent>

typedef union{
struct {
    unsigned    a1 : 4; //---1000b-代表板上第一个轴通道，1001b--代表第二个轴通道，。。。直到1111b---代表第八个轴通道，实际主板上面只能到1100b，即第5个轴
    unsigned    a2 : 4;
    unsigned    a3 : 4; //----不指定，则采用0，对当前五轴来说就是五个伺服应该是 ---1000b,1001b,1010b,1011b,1100b，即 8,9,10,11,12
    unsigned    a4 : 4;
    unsigned    a5 : 4;
    unsigned    a6 : 4;
    unsigned    a7 : 4;
    unsigned    a8 : 4;
}split;
struct {
    unsigned resv1 : 16;
    unsigned resv2 : 16;
}resv;
uint port;
}AXIS_MODIFY_DATA;

typedef union{
    struct {
        u_int16_t a1 : 3;
        u_int16_t a2 : 3;
        u_int16_t a3 : 3;
        u_int16_t a4 : 3;
        u_int16_t a5 : 3;
        u_int16_t resv : 1;
    }mode;
    u_int16_t allMode;
}AxisMode;



typedef union{
    struct {
        u_int16_t x : 2;
        u_int16_t y : 2;
        u_int16_t z : 2;
        u_int16_t p : 2;
        u_int16_t q : 2;
        u_int16_t a : 2;
        u_int16_t b : 2;
        u_int16_t c : 2;
    }b;
    u_int16_t combine;
}OriginStatus;

typedef union{
    struct {
        u_int32_t y0 : 1;
        u_int32_t y1 : 1;
        u_int32_t y2 : 1;
        u_int32_t y3 : 1;
        u_int32_t y4 : 1;
        u_int32_t y5 : 1;
        u_int32_t y6 : 1;
        u_int32_t y7 : 1;

        u_int32_t y10 : 1;
        u_int32_t y11 : 1;
        u_int32_t y12 : 1;
        u_int32_t y13 : 1;
        u_int32_t y14 : 1;
        u_int32_t y15 : 1;
        u_int32_t y16 : 1;
        u_int32_t y17 : 1;

        u_int32_t y20 : 1;
        u_int32_t y21 : 1;
        u_int32_t y22 : 1;
        u_int32_t y23 : 1;
        u_int32_t y24 : 1;
        u_int32_t y25 : 1;
        u_int32_t y26 : 1;
        u_int32_t y27 : 1;

        u_int32_t y30 : 1;
        u_int32_t y31 : 1;
        u_int32_t y32 : 1;
        u_int32_t y33 : 1;
        u_int32_t y34 : 1;
        u_int32_t y35 : 1;
        u_int32_t y36 : 1;
        u_int32_t y37 : 1;
    }b;
    u_int16_t combine16[2];
    u_int32_t combine32;
}OutputWay;

ICStructDefineFrame::ICStructDefineFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICStructDefineFrame)
{
    ui->setupUi(this);
    ui->protDefineContainer->hide();
    buttongroup_ = new QButtonGroup ;

    ui->buttonGroupA->setId(ui->normalABox,0);
    ui->buttonGroupA->setId(ui->extentABox,1);
    ui->buttonGroupB->setId(ui->normalBBox,0);
    ui->buttonGroupB->setId(ui->extentBBox,1);
    ui->buttonGroupC->setId(ui->normalCBox,0);
    ui->buttonGroupC->setId(ui->extentCBox,1);
    ui->buttonGroupD->setId(ui->normalDBox,0);
    ui->buttonGroupD->setId(ui->extentDBox,1);
    ui->buttonGroupE->setId(ui->normalEBox,0);
    ui->buttonGroupE->setId(ui->extentEBox,1);
    ui->buttonGroupF->setId(ui->normalFBox,0);
    ui->buttonGroupF->setId(ui->extentFBox,1);
    ui->buttonGroupG->setId(ui->normalGBox,0);
    ui->buttonGroupG->setId(ui->extentGBox,1);
    ui->buttonGroupH->setId(ui->normalHBox,0);
    ui->buttonGroupH->setId(ui->extentHBox,1);
    if(ICParametersSave::Instance()->IsSingleArm())
    {
        ui->singleArmButton->setChecked(true);
        on_doubleArmButton_toggled(false);
    }
    else
    {
        ui->doubleArmButton->click();
    }
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    armStruct_ = host->SystemParameter(ICVirtualHost::SYS_Config_Signal).toUInt();
    ui->mainArmForwardLimitButton->setChecked(host->HasMainArmForwardLimit());
    ui->mainArmBackwardLimitButton->setChecked(host->HasMainArmBackwardLimit());
    ui->mainArmDownLimitButton->setChecked(host->HasMainArmDownLimit());

    ui->subArmForwardLimitButton->setChecked(host->HasSubArmForwardLimit());
    ui->subArmBackwardLimitButton->setChecked(host->HasSubArmBackwardLimit());
    ui->subArmDownLimitButton->setChecked(host->HasSubArmDownLimit());

    /*axis define*/
    boxToAxis_.insert(ui->x1Box, ICVirtualHost::ICAxis_AxisX1);
    boxToAxis_.insert(ui->y1Box, ICVirtualHost::ICAxis_AxisY1);
    boxToAxis_.insert(ui->x2Box, ICVirtualHost::ICAxis_AxisX2);
    boxToAxis_.insert(ui->y2Box, ICVirtualHost::ICAxis_AxisY2);
    boxToAxis_.insert(ui->zBox, ICVirtualHost::ICAxis_AxisZ);
    boxToAxis_.insert(ui->aBox, ICVirtualHost::ICAxis_AxisA);
    boxToAxis_.insert(ui->bBox, ICVirtualHost::ICAxis_AxisB);
    boxToAxis_.insert(ui->cBox, ICVirtualHost::ICAxis_AxisC);

    armDefineToIndex_.insert(ICVirtualHost::ICAxisDefine_None, 0);
    armDefineToIndex_.insert(ICVirtualHost::ICAxisDefine_Pneumatic, 1);
    armDefineToIndex_.insert(ICVirtualHost::ICAxisDefine_Servo, 2);
    indexToArmDefine_.insert(0, ICVirtualHost::ICAxisDefine_None);
    indexToArmDefine_.insert(1, ICVirtualHost::ICAxisDefine_Pneumatic);
    indexToArmDefine_.insert(2, ICVirtualHost::ICAxisDefine_Servo);

    QList<QComboBox*> boxs = ui->armDefineBox->findChildren<QComboBox*>();
    axisDefine_ = host->SystemParameter(ICVirtualHost::SYS_Config_Arm).toInt();
    for(int i = 0; i != boxs.size(); ++i)
    {
        boxs[i]->setCurrentIndex(armDefineToIndex_.value(host->AxisDefine(static_cast<ICVirtualHost::ICAxis>(boxToAxis_.value(boxs.at(i))))));
        connect(boxs[i],
                SIGNAL(currentIndexChanged(int)),
                SLOT(OnAxisDefineChanged(int)));
    }
    InitEscapeBox() ;
    buttongrouplist.append(ui->buttonGroupA);
    buttongrouplist.append(ui->buttonGroupB);
    buttongrouplist.append(ui->buttonGroupC);
    buttongrouplist.append(ui->buttonGroupD);
    buttongrouplist.append(ui->buttonGroupE);
    buttongrouplist.append(ui->buttonGroupF);
    buttongrouplist.append(ui->buttonGroupG);
    buttongrouplist.append(ui->buttonGroupH);

    buttonslist_.append(ui->buttonGroupA->buttons());
    buttonslist_.append(ui->buttonGroupB->buttons());
    buttonslist_.append(ui->buttonGroupC->buttons());
    buttonslist_.append(ui->buttonGroupD->buttons());
    buttonslist_.append(ui->buttonGroupE->buttons());
    buttonslist_.append(ui->buttonGroupF->buttons());
    buttonslist_.append(ui->buttonGroupG->buttons());
    buttonslist_.append(ui->buttonGroupH->buttons());

    for(int i = 0 ; i < buttongrouplist.size() ; ++i)
        outputDefineToNumber_.insert(buttongrouplist[i],i) ;


//    outputDefineToNumber_.insert(ui->outABox, 0);
//    outputDefineToNumber_.insert(ui->outBBox, 1);
//    outputDefineToNumber_.insert(ui->outCBox, 2);
//    outputDefineToNumber_.insert(ui->outDBox, 3);
//    outputDefineToNumber_.insert(ui->outEBox, 4);
//    outputDefineToNumber_.insert(ui->outFBox, 5);
//    outputDefineToNumber_.insert(ui->outGBox, 6);
//    outputDefineToNumber_.insert(ui->outHBox, 7);

//    numberToOutputDefine_.insert(0, ui->outABox);
//    numberToOutputDefine_.insert(1, ui->outBBox);
//    numberToOutputDefine_.insert(2, ui->outCBox);
//    numberToOutputDefine_.insert(3, ui->outDBox);
//    numberToOutputDefine_.insert(4, ui->outEBox);
//    numberToOutputDefine_.insert(5, ui->outFBox);
//    numberToOutputDefine_.insert(6, ui->outGBox);
//    numberToOutputDefine_.insert(7, ui->outHBox);
    outDefine_ = host->SystemParameter(ICVirtualHost::ICVirtualHost::SYS_Config_Out).toInt();
//    boxs = ui->outDefineBox->findChildren<QComboBox*>();
 //   boxs = ui->outDefineBox->findChildren<QButtonGroup*>();
    for(int i = 0; i != buttongrouplist.size(); ++i)
    {
//        boxs[i]->setCurrentIndex(host->PeripheryOutput(outputDefineToNumber_.value(boxs.at(i))));
        if(host->PeripheryOutput(outputDefineToNumber_.value(buttongrouplist.at(i))) == 0)
        {
            buttongrouplist.at(i)->button(0)->setChecked(true);
//            buttonslist_[i][0]->setChecked(true);//不能保证从容器中返回的成员是按顺序的，所以不能这样写，将会导致有些数据会变化
        }
        else if(host->PeripheryOutput(outputDefineToNumber_.value(buttongrouplist.at(i))) == 1)
        {
            buttongrouplist.at(i)->button(1)->setChecked(true);
//            buttonslist_[i][1]->setChecked(true);
        }

        buttongrouplist[i]->setExclusive(true);
        connect(buttongrouplist[i],
                SIGNAL(buttonClicked(int)),
                SLOT(OnOutputDefineChanged(int)));
    }

//    ui->fixtureSelectBox->setCurrentIndex(host->FixtureDefine());
  //  ui->escapeComboBox->setCurrentIndex(host->EscapeWay());
    if(host->EscapeWay() == 0)
        ui->useCheckBox->setChecked(true);
    if(host->EscapeWay() == 1)
        ui->noUseCheckBox->setChecked(true);
    if(ICParametersSave::Instance()->IsAdjustFunctionOn())
    {
        ui->adjUse->setChecked(true);
    }
    else
    {
        ui->adjNoUse->setChecked(true);
    }

//    AXIS_MODIFY_DATA data;
//    data.port = (host->SystemParameter(ICVirtualHost::SYS_Config_Resv1).toInt() << 16) |
//            (host->SystemParameter(ICVirtualHost::SYS_Config_Resv2).toInt());
//    ui->portX1->setCurrentIndex(data.split.a1 == 0 ? 0 : data.split.a1 - 7);
//    ui->portY1->setCurrentIndex(data.split.a2 == 0 ? 0 : data.split.a2 - 7);
//    ui->portZ->setCurrentIndex(data.split.a3 == 0 ? 0 : data.split.a3 - 7);
//    ui->portX2->setCurrentIndex(data.split.a4 == 0 ? 0 : data.split.a4 - 7);
//    ui->portY2->setCurrentIndex(data.split.a5 == 0 ? 0 : data.split.a5 - 7);
//    ui->portA->setCurrentIndex(data.split.a6 == 0 ? 0 : data.split.a6 - 7);
//    ui->portB->setCurrentIndex(data.split.a7 == 0 ? 0 : data.split.a7 - 7);
//    ui->portC->setCurrentIndex(data.split.a8 == 0 ? 0 : data.split.a8 - 7);
    AxisMode axisMode;
    axisMode.allMode = host->SystemParameter(ICVirtualHost::SYS_Config_Resv1).toInt();
//    ui->waitTime->SetThisIntToThisText(recycleMode.split.time);
//    ui->waitTime->SetDecimalPlaces(1);
//    ui->waitTime->setValidator(new QIntValidator(0, 100, this));
    ui->os1->setCurrentIndex(axisMode.mode.a1);
    ui->os2->setCurrentIndex(axisMode.mode.a2);
    ui->os3->setCurrentIndex(axisMode.mode.a3);
    ui->os4->setCurrentIndex(axisMode.mode.a4);
    ui->os5->setCurrentIndex(axisMode.mode.a5);
    ui->osGroupBox->setChecked(axisMode.mode.resv);

    OutputWay outWay;
    outWay.combine16[0] = host->SystemParameter(ICVirtualHost::ACT_C_Sec3).toUInt();
    outWay.combine16[1] = host->SystemParameter(ICVirtualHost::ACT_C_Sec4).toUInt();
    ui->y10Reset->setChecked(outWay.b.y0);
    ui->y11Reset->setChecked(outWay.b.y1);
    ui->y12Reset->setChecked(outWay.b.y2);
    ui->y13Reset->setChecked(outWay.b.y3);
    ui->y14Reset->setChecked(outWay.b.y4);
    ui->y15Reset->setChecked(outWay.b.y5);
    ui->y16Reset->setChecked(outWay.b.y6);
    ui->y17Reset->setChecked(outWay.b.y7);

    ui->y20Reset->setChecked(outWay.b.y10);
    ui->y21Reset->setChecked(outWay.b.y11);
    ui->y22Reset->setChecked(outWay.b.y12);
    ui->y23Reset->setChecked(outWay.b.y13);
    ui->y24Reset->setChecked(outWay.b.y14);
    ui->y25Reset->setChecked(outWay.b.y15);
    ui->y26Reset->setChecked(outWay.b.y16);
    ui->y27Reset->setChecked(outWay.b.y17);

    ui->y30Reset->setChecked(outWay.b.y20);
    ui->y31Reset->setChecked(outWay.b.y21);
    ui->y32Reset->setChecked(outWay.b.y22);
    ui->y33Reset->setChecked(outWay.b.y23);
    ui->y34Reset->setChecked(outWay.b.y24);
    ui->y35Reset->setChecked(outWay.b.y25);
    ui->y36Reset->setChecked(outWay.b.y26);
    ui->y37Reset->setChecked(outWay.b.y27);

    ui->y40Reset->setChecked(outWay.b.y30);
    ui->y41Reset->setChecked(outWay.b.y31);
    ui->y42Reset->setChecked(outWay.b.y32);
    ui->y43Reset->setChecked(outWay.b.y33);
    ui->y44Reset->setChecked(outWay.b.y34);
    ui->y45Reset->setChecked(outWay.b.y35);
    ui->y46Reset->setChecked(outWay.b.y36);
    ui->y47Reset->setChecked(outWay.b.y37);

    ui->y10Reset->hide();
    ui->y11Reset->hide();
//    ui->y12Reset->hide();
//    ui->y13Reset->hide();
//    ui->y14Reset->hide();
//    ui->y15Reset->hide();
    ui->y16Reset->hide();
//    ui->y17Reset->hide();

//    ui->y20Reset->hide();
    ui->y21Reset->hide();
//    ui->y22Reset->hide();
    ui->y23Reset->hide();
    ui->y24Reset->hide();
//    ui->y25Reset->hide();
    ui->y26Reset->hide();
    ui->y27Reset->hide();

    ui->y30Reset->hide();
//    ui->y31Reset->hide();
//    ui->y32Reset->hide();
    ui->y33Reset->hide();
//    ui->y34Reset->hide();
//    ui->y35Reset->hide();
//    ui->y36Reset->hide();
//    ui->y37Reset->hide();

    ui->y40Reset->hide();
    ui->y41Reset->hide();
    ui->y42Reset->hide();
    ui->y43Reset->hide();
    ui->y44Reset->hide();
    ui->y45Reset->hide();
    ui->y46Reset->hide();
    ui->y47Reset->hide();

    ui->fixtureDefineBox_2->hide();


    oldStyle = ui->oStartBtn->styleSheet();
    newStyle = "border-style: outset;border-width: 2px;border-radius: 6px;border-color: gray;background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(0, 255, 0, 255), stop:1 rgba(255, 255, 255, 255));padding-right: 6px;padding-left:6px;";
}

ICStructDefineFrame::~ICStructDefineFrame()
{
    delete ui;
}

void ICStructDefineFrame::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
     //  ui->retranslateUi(this);
       retranslateUi_();
        break;
    default:
        break;
    }
}

void ICStructDefineFrame::hideEvent(QHideEvent *e)
{
    icMainFrame->BlockOrignShow(false);
    ICCommandProcessor::Instance()->ExecuteHCCommand(IC::CMD_TurnStop, 0);
    ui->tabWidget->setCurrentIndex(0);
    QWidget::hideEvent(e);
}

void ICStructDefineFrame::timerEvent(QTimerEvent *)
{
    if(ui->tabWidget->currentIndex() != 4) return;
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    if(host->CurrentStatus() == ICVirtualHost::Origin)
    {
        ui->oStartBtn->setStyleSheet(newStyle);
        ui->oStartBtn->setText(tr("Origining"));
    }
    else
    {
        ui->oStartBtn->setStyleSheet(oldStyle);
        ui->oX1Btn->setStyleSheet(oldStyle);
        ui->oX2Btn->setStyleSheet(oldStyle);
        ui->oY1Btn->setStyleSheet(oldStyle);
        ui->oY2Btn->setStyleSheet(oldStyle);
        ui->oZBtn->setStyleSheet(oldStyle);
        ui->oABtn->setStyleSheet(oldStyle);
        ui->oBBtn->setStyleSheet(oldStyle);
        ui->oCBtn->setStyleSheet(oldStyle);
        ui->oStartBtn->setText(tr("Start"));
        return;
    }

    OriginStatus os;
    os.combine = host->HostStatus(ICVirtualHost::DbgX1).toUInt();
    if(os.b.x)
    {
        ui->oX1Btn->setStyleSheet(newStyle);
    }
    else
    {
        ui->oX1Btn->setStyleSheet(oldStyle);
    }

    if(os.b.y)
    {
        ui->oY1Btn->setStyleSheet(newStyle);
    }
    else
    {
        ui->oY1Btn->setStyleSheet(oldStyle);
    }

    if(os.b.z)
    {
        ui->oZBtn->setStyleSheet(newStyle);
    }
    else
    {
        ui->oZBtn->setStyleSheet(oldStyle);
    }

    if(os.b.p)
    {
        ui->oX2Btn->setStyleSheet(newStyle);
    }
    else
    {
        ui->oX2Btn->setStyleSheet(oldStyle);
    }

    if(os.b.q)
    {
        ui->oY2Btn->setStyleSheet(newStyle);
    }
    else
    {
        ui->oY2Btn->setStyleSheet(oldStyle);
    }

    if(os.b.a)
    {
        ui->oABtn->setStyleSheet(newStyle);
    }
    else
    {
        ui->oABtn->setStyleSheet(oldStyle);
    }

    if(os.b.b)
    {
        ui->oBBtn->setStyleSheet(newStyle);
    }
    else
    {
        ui->oBBtn->setStyleSheet(oldStyle);
    }

    if(os.b.c)
    {
        ui->oCBtn->setStyleSheet(newStyle);
    }
    else
    {
        ui->oCBtn->setStyleSheet(oldStyle);
    }

}

void ICStructDefineFrame::retranslateUi_()
{
    this->setWindowTitle(tr("Form"));
    ui->signalDefineBox->setTitle(tr("Signal Define"));
    ui->singleArmButton->setText(tr("Single Arm"));
    ui->doubleArmButton->setText(tr("Double Arm"));
    ui->mainArmBox->setTitle(tr("Main Arm"));
    ui->mainArmDownLimitButton->setText(tr("Down Limit"));
    ui->mainArmBackwardLimitButton->setText(tr("Backword Limit"));
    ui->mainArmForwardLimitButton->setText(tr("Forward Limit"));
    ui->subArmBox->setTitle(tr("Sub Arm"));
    ui->subArmDownLimitButton->setText(tr("Down Limit"));
    ui->subArmBackwardLimitButton->setText(tr("Backword Limit"));
    ui->subArmForwardLimitButton->setText(tr("Forward Limit"));
    ui->armDefineBox->setTitle(tr("Arm Define"));
    ui->label_5->setText(tr("X1"));
    ui->x1Box->setItemText(0,tr("None"));
    ui->x1Box->setItemText(1,tr("Pneumatic"));
    ui->x1Box->setItemText(2,tr("Servo"));
    ui->label_14->setText(tr("C"));
    ui->y1Box->setItemText(0,tr("None"));
    ui->y1Box->setItemText(1,tr("Pneumatic"));
    ui->y1Box->setItemText(2,tr("Servo"));
    ui->label_13->setText(tr("Z"));
    ui->cBox->setItemText(0,tr("None"));
    ui->cBox->setItemText(1,tr("Pneumatic"));
    ui->cBox->setItemText(2,tr("Servo"));
    ui->label_15->setText(tr("A"));
    ui->aBox->setItemText(0,tr("None"));
    ui->aBox->setItemText(1,tr("Pneumatic"));
    ui->aBox->setItemText(2,tr("Servo"));
    ui->label_16->setText(tr("B"));
    ui->zBox->setItemText(0,tr("None"));
    ui->zBox->setItemText(1,tr("Pneumatic"));
    ui->zBox->setItemText(2,tr("Servo"));
    ui->label_7->setText(tr("Y1"));
    ui->bBox->setItemText(0,tr("None"));
    ui->bBox->setItemText(1,tr("Pneumatic"));
    ui->bBox->setItemText(2,tr("Servo"));
    ui->label_6->setText(tr("X2"));
    ui->x2Box->setItemText(0,tr("None"));
    ui->x2Box->setItemText(1,tr("Pneumatic"));
    ui->x2Box->setItemText(2,tr("Servo"));
    ui->label_12->setText(tr("Y2"));
    ui->y2Box->setItemText(0,tr("None"));
    ui->y2Box->setItemText(1,tr("Pneumatic"));
    ui->y2Box->setItemText(2,tr("Servo"));
    ui->outDefineBox->setTitle(tr("Out Define"));
    ui->label->setText(tr("1"));
//    ui->outABox->setItemText(0,tr("Normal"));
//    ui->outABox->setItemText(1,tr("Extent"));
//    ui->label_8->setText(tr("5"));
//    ui->outEBox->setItemText(0,tr("Normal"));
//    ui->outEBox->setItemText(1,tr("Extent"));
//    ui->label_2->setText(tr("2"));
//    ui->outBBox->setItemText(0,tr("Normal"));
//    ui->outBBox->setItemText(1,tr("Extent"));
//    ui->label_9->setText(tr("6"));
//    ui->outFBox->setItemText(0,tr("Normal"));
//    ui->outFBox->setItemText(1,tr("Extent"));
//    ui->label_3->setText(tr("3"));
//    ui->outCBox->setItemText(0,tr("Normal"));
//    ui->outCBox->setItemText(1,tr("Extent"));
//    ui->label_11->setText(tr("7"));
//    ui->outGBox->setItemText(0,tr("Normal"));
//    ui->outGBox->setItemText(1,tr("Extent"));
//    ui->label_4->setText(tr("4"));
//    ui->outDBox->setItemText(0,tr("Normal"));
//    ui->outDBox->setItemText(1,tr("Extent"));
//    ui->label_10->setText(tr("8"));
//    ui->outHBox->setItemText(0,tr("Normal"));
//    ui->outHBox->setItemText(1,tr("Extent"));
    ui->normalABox->setText(tr("Normal"));
    ui->extentABox->setText(tr("Extent"));
    ui->normalBBox->setText(tr("Normal"));
    ui->extentBBox->setText(tr("Extent"));
    ui->normalCBox->setText(tr("Normal"));
    ui->extentCBox->setText(tr("Extent"));
    ui->normalDBox->setText(tr("Normal"));
    ui->extentDBox->setText(tr("Extent"));
    ui->normalEBox->setText(tr("Normal"));
    ui->extentEBox->setText(tr("Extent"));
    ui->normalFBox->setText(tr("Normal"));
    ui->extentFBox->setText(tr("Extent"));
    ui->normalGBox->setText(tr("Normal"));
    ui->extentGBox->setText(tr("Extent"));
    ui->normalHBox->setText(tr("Normal"));
    ui->extentHBox->setText(tr("Extent"));
    ui->fixtureDefineBox_2->setTitle(tr("Other Define"));
    ui->label_18->setText(tr("Escape"));
//    ui->escapeComboBox->setItemText(0,tr("Use"));
//    ui->escapeComboBox->setItemText(1,tr("No Use"));
    ui->useCheckBox->setText(tr("Use"));
    ui->noUseCheckBox->setText(tr("No Use"));
    ui->saveButton->setText(tr("Save"));
}

void ICStructDefineFrame::on_saveButton_clicked()
{
    OutputWay outWay;
    outWay.b.y0 = 0;
    outWay.b.y1 = 0;
    outWay.b.y2 = ui->y12Reset->isChecked();
    outWay.b.y3 = ui->y13Reset->isChecked();
    outWay.b.y4 = ui->y14Reset->isChecked();
    outWay.b.y5 = ui->y15Reset->isChecked();
    outWay.b.y6 = 0;
    outWay.b.y7 = ui->y17Reset->isChecked();

    outWay.b.y10 = ui->y20Reset->isChecked();
    outWay.b.y11 = 0;
    outWay.b.y12 = ui->y22Reset->isChecked();
    outWay.b.y13 = 0;
    outWay.b.y14 = 0;
    outWay.b.y15 = ui->y25Reset->isChecked();
    outWay.b.y16 = 0;
    outWay.b.y17 = 0;

    outWay.b.y20 = 0;
    outWay.b.y21 = ui->y31Reset->isChecked();
    outWay.b.y22 = ui->y32Reset->isChecked();
    outWay.b.y23 = 0;
    outWay.b.y24 = ui->y34Reset->isChecked();
    outWay.b.y25 = ui->y35Reset->isChecked();
    outWay.b.y26 = ui->y36Reset->isChecked();
    outWay.b.y27 = ui->y37Reset->isChecked();

    outWay.b.y30 = 0;
    outWay.b.y31 = 0;
    outWay.b.y32 = 0;
    outWay.b.y33 = 0;
    outWay.b.y34 = 0;
    outWay.b.y35 = 0;
    outWay.b.y36 = 0;
    outWay.b.y37 = 0;

    ICSetAxisConfigsCommand command;
    ICCommandProcessor* process = ICCommandProcessor::Instance();
    int sum = 0;
    QVector<uint> dataBuffer(7, 0);
    dataBuffer[0] = armStruct_;
    dataBuffer[1] = axisDefine_;
    dataBuffer[2] = outDefine_;
//    dataBuffer[3] = ICVirtualHost::GlobalVirtualHost()->FixtureDefineSwitch(ui->fixtureSelectBox->currentIndex());
    dataBuffer[3] = ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_Config_Fixture).toUInt();
//    dataBuffer[4]
//    AXIS_MODIFY_DATA data;
//    data.split.a1 = ui->portX1->currentIndex() == 0 ? 0 : ui->portX1->currentIndex() + 7;
//    data.split.a2 = ui->portY1->currentIndex() == 0 ? 0 : ui->portY1->currentIndex() + 7;
//    data.split.a3 = ui->portZ->currentIndex() == 0 ? 0 : ui->portZ->currentIndex() + 7;
//    data.split.a4 = ui->portX2->currentIndex() == 0 ? 0 : ui->portX2->currentIndex() + 7;
//    data.split.a5 = ui->portY2->currentIndex() == 0 ? 0 : ui->portY2->currentIndex() + 7;
//    data.split.a6 = ui->portA->currentIndex() == 0 ? 0 : ui->portA->currentIndex() + 7;
//    data.split.a7 = ui->portB->currentIndex() == 0 ? 0 : ui->portB->currentIndex() + 7;
//    data.split.a8 = ui->portC->currentIndex() == 0 ? 0 : ui->portC->currentIndex() + 7;
//    dataBuffer[4] = data.resv.resv1;
//    dataBuffer[5] = data.resv.resv2;
    AxisMode axisMode;
    axisMode.mode.a1 = ui->os1->currentIndex();
    axisMode.mode.a2 = ui->os2->currentIndex();
    axisMode.mode.a3 = ui->os3->currentIndex();
    axisMode.mode.a4 = ui->os4->currentIndex();
    axisMode.mode.a5 = ui->os5->currentIndex();
    axisMode.mode.resv = ui->osGroupBox->isChecked();
    dataBuffer[4] = axisMode.allMode;

//    RecycleMode recycleMode;
//    recycleMode.split.mode = ui->recycleMode->currentIndex();
//    recycleMode.split.time = ui->waitTime->TransThisTextToThisInt();
    dataBuffer[5] = ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_Config_Resv2).toUInt();
    for(int i = 0; i != 6; ++i)
    {
        sum += dataBuffer.at(i);
    }
    sum = (-sum & 0XFFFF);
    dataBuffer[6] = sum;
    command.SetSlave(process->SlaveID());
    command.SetDataBuffer(dataBuffer);
    command.SetAxis(8);
#ifndef Q_WS_X11
    if(process->ExecuteCommand(command).toBool())
#endif
    {
        ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
        host->SetSystemParameter(ICVirtualHost::SYS_Config_Signal, armStruct_);
        host->SetAxisDefine(axisDefine_);
        host->SetPeripheryOutput(outDefine_);
        host->SetSystemParameter(ICVirtualHost::SYS_Config_Fixture, dataBuffer.at(3));
        host->SetSystemParameter(ICVirtualHost::SYS_Config_Resv1, dataBuffer.at(4));
        host->SetSystemParameter(ICVirtualHost::SYS_Config_Resv2, dataBuffer.at(5));
        host->SetSystemParameter(ICVirtualHost::SYS_Config_Xorsum, dataBuffer.at(6));

        host->SetSystemParameter(ICVirtualHost::ACT_C_Sec3, outWay.combine16[0]);
        host->SetSystemParameter(ICVirtualHost::ACT_C_Sec4, outWay.combine16[1]);
//        host->SystemParameter(ICVirtualHost::SYS_Function);
        host->SaveSystemConfig();
        QMessageBox::information(this, tr("Tips"), tr("Save Sucessfully!"));
        emit StructChanged();
        icMainFrame->UpdateAxisDefine_();
    }
    ICParametersSave::Instance()->SetSingleArm(ui->singleArmButton->isChecked());
    qDebug()<<"Struct = "<<armStruct_;
    qDebug()<<"Arm Define"<<axisDefine_;
}

void ICStructDefineFrame::on_doubleArmButton_toggled(bool checked)
{
    if(checked)
    {
        ui->subArmBox->setEnabled(true);
    }
    else
    {
        ui->subArmBox->setEnabled(false);
    }
//    checked ? armStruct_ &= 0xFEFF : armStruct_ |= 0x100;
}

void ICStructDefineFrame::on_mainArmDownLimitButton_toggled(bool checked)
{
//    ICVirtualHost::GlobalVirtualHost()->SetMainArmDownLimit(checked);
    checked ? armStruct_ |= 0x000C : armStruct_ &= 0xFFF7;
}

void ICStructDefineFrame::on_mainArmBackwardLimitButton_toggled(bool checked)
{
//    ICVirtualHost::GlobalVirtualHost()->SetMainArmBackwardLimit(checked);
    checked ? armStruct_ |= 0x0001 : armStruct_ &= 0xFFFE;
}

void ICStructDefineFrame::on_mainArmForwardLimitButton_toggled(bool checked)
{
//    ICVirtualHost::GlobalVirtualHost()->SetMainArmForwardLimit(checked);
    checked ? armStruct_ |= 0x0002 : armStruct_ &= 0xFFFD;
}

void ICStructDefineFrame::on_subArmDownLimitButton_toggled(bool checked)
{
//    ICVirtualHost::GlobalVirtualHost()->SetSubArmDownLimit(checked);
    checked ? armStruct_ |= 0x0300 : armStruct_ &= 0xFDFF;
}

void ICStructDefineFrame::on_subArmBackwardLimitButton_toggled(bool checked)
{
//    ICVirtualHost::GlobalVirtualHost()->SetSubArmBackwardLimit(checked);
    checked ? armStruct_ |= 0x0040 : armStruct_ &= 0xFFBF;
}

void ICStructDefineFrame::on_subArmForwardLimitButton_toggled(bool checked)
{
   checked ? armStruct_ |= 0x0080 : armStruct_ &= 0xFF7F;
}

void ICStructDefineFrame::OnAxisDefineChanged(int index)
{
    QComboBox* box = qobject_cast<QComboBox*>(sender());
    ICVirtualHost::GlobalVirtualHost()->CalAxisDefine(axisDefine_,
                                                      static_cast<ICVirtualHost::ICAxis>(boxToAxis_.value(box)),
                                                      static_cast<ICVirtualHost::ICAxisDefine>(indexToArmDefine_.value(index)));
}

void ICStructDefineFrame::OnOutputDefineChanged(int index)
{
    QButtonGroup* box = qobject_cast<QButtonGroup*>(sender());
    ICVirtualHost::GlobalVirtualHost()->CalPeripheryOutput(outDefine_,
                                                           outputDefineToNumber_.value(box),
                                                           index);
}


void ICStructDefineFrame::escapeBoxChange()
{
    ICVirtualHost::GlobalVirtualHost()->SetEscapeWay(buttongroup_->checkedId());
}

void ICStructDefineFrame::InitEscapeBox()
{
    ui->useCheckBox->hide();
    ui->noUseCheckBox->hide();
    ui->label_18->hide();
    buttongroup_->addButton(ui->useCheckBox,0);
    buttongroup_->addButton(ui->noUseCheckBox,1);
    QList<QAbstractButton*> buttons = buttongroup_->buttons();
    for(int i = 0; i != buttons.size(); ++i)
    {
        buttons[i]->setCheckable(true);
        connect(buttons.at(i),
                SIGNAL(clicked()),
                this,
                SLOT(escapeBoxChange()));
    }
    buttongroup_->setExclusive(true);
}

void ICStructDefineFrame::on_adjUse_toggled(bool checked)
{
    ICParametersSave::Instance()->SetAdjustFunction(checked);
}

void ICStructDefineFrame::on_oStartBtn_clicked()
{
    icMainFrame->BlockOrignShow(true);
    ICCommandProcessor::Instance()->ExecuteHCCommand(IC::CMD_TurnZero, 0);
}

void ICStructDefineFrame::on_oX1Btn_clicked()
{
    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_ORIGIN_X1);
}

void ICStructDefineFrame::on_oY1Btn_clicked()
{
    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_ORIGIN_Y1);
}

void ICStructDefineFrame::on_oZBtn_clicked()
{
    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_ORIGIN_Z);
}

void ICStructDefineFrame::on_oX2Btn_clicked()
{
    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_ORIGIN_X2);
}

void ICStructDefineFrame::on_oY2Btn_clicked()
{
    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_ORIGIN_Y2);
}

void ICStructDefineFrame::on_setOrigin_clicked()
{
    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_SET_ORIGIN);
}

void ICStructDefineFrame::on_tabWidget_currentChanged(int index)
{
    if(index == 4)
    {
        timerID_ = startTimer(50);
    }
    else
    {
        killTimer(timerID_);
    }
}
