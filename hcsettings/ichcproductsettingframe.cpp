#include "ichcproductsettingframe.h"
#include "ui_ichcproductsettingframe.h"

#include "iclineeditwrapper.h"
#include "icmold.h"
#include "icvirtualhost.h"
#include "icvirtualkey.h"
#include "moldinformation.h"
#include "icparameterssave.h"

ICHCProductSettingFrame::ICHCProductSettingFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ICHCProductSettingFrame)
{
    ui->setupUi(this);
    buttongroup_ = new QButtonGroup ;
    InitCheckBox();
    ui->productLineEdit->setValidator(new QIntValidator(0, 65535, ui->productLineEdit));
    ui->alarmTimesEdit->setValidator(new QIntValidator(0, 65535, ui->alarmTimesEdit));
    ui->tryProductEdit->setValidator(new QIntValidator(0, 65535, ui->tryProductEdit));
    ui->samplingEdit->setValidator(new QIntValidator(0, 65535, ui->samplingEdit));
    ui->samplingEdit_3->setValidator(new QIntValidator(0, 65535, ui->samplingEdit_3));
    ui->waitTimeEdit->SetDecimalPlaces(1);
    ui->waitTimeEdit->setValidator(new QIntValidator(0, 32760, ui->waitTimeEdit));
    ICLineEditWrapper *wrapper = new ICLineEditWrapper(ui->productLineEdit,
                                                       ICMold::Product,
                                                       ICLineEditWrapper::Mold,
                                                       ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->tryProductEdit,
                                                       ICMold::TryProduct,
                                                       ICLineEditWrapper::Mold,
                                                       ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->samplingEdit,
                                                       ICMold::Sampling,
                                                       ICLineEditWrapper::Mold,
                                                       ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->waitTimeEdit,
                                    ICVirtualHost::SM_WaitMoldOpenLimit,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::OneFraction);
    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->alarmTimesEdit,
                                    ICVirtualHost::SM_ACCTIME,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);

//    int currentPos = ICMold::CurrentMold()->MoldParam(ICMold::PosMainDown);
//    if(currentPos > 1)
//    {
//        currentPos = 1;
//    }
//    buttongroup_->setId(ICVirtualHost::GlobalVirtualHost()->FixtureDefine());
    if(ICVirtualHost::GlobalVirtualHost()->FixtureDefine() == 0)
        ui->reversedCheckBox->click();
    if(ICVirtualHost::GlobalVirtualHost()->FixtureDefine() == 1)
        ui->positiveCheckBox->click();

    ui->getFailWay->setCurrentIndex(ICVirtualHost::GlobalVirtualHost()->GetFailAlarmWay());

    connect(ICMold::CurrentMold(),
            SIGNAL(MoldNumberParamChanged()),
            this,
            SLOT(OnMoldNumberParamChanged()));
    ui->countUnitBox->setCurrentIndex(ICMold::CurrentMold()->MoldParam(ICMold::CountUnit));

    mboxs_<<ui->mBox_1<<ui->mBox_2<<ui->mBox_3<<ui->mBox_4<<ui->mBox_5<<ui->mBox_6<<ui->mBox_7
            <<ui->mBox_8<<ui->mBox_9<<ui->mBox_10<<ui->mBox_11<<ui->mBox_12;

    pcEdits_<<ui->pc_1<<ui->pc_2<<ui->pc_3<<ui->pc_4<<ui->pc_5<<ui->pc_6<<ui->pc_7
            <<ui->pc_8<<ui->pc_9<<ui->pc_10<<ui->pc_11<<ui->pc_12;

    clearButtons_<<ui->clear_1<<ui->clear_2<<ui->clear_3<<ui->clear_4<<ui->clear_5<<ui->clear_6<<ui->clear_7
            <<ui->clear_8<<ui->clear_9<<ui->clear_10<<ui->clear_11<<ui->clear_12;

    for(int i = 0 ; i != mboxs_.size(); ++i)
    {
        connect(mboxs_.at(i),
                SIGNAL(currentIndexChanged(int)),
                SLOT(OnProductMoldNameChanged(int)));

        connect(pcEdits_.at(i),
                SIGNAL(textChanged (QString)),
                SLOT(OnProductCountChanged(QString)));
        connect(clearButtons_.at(i),
                SIGNAL(clicked()),
                SLOT(OnProductClearClicked()));
    }

}

ICHCProductSettingFrame::~ICHCProductSettingFrame()
{
    delete ui;
    qDeleteAll(wrappers_);
}

void ICHCProductSettingFrame::hideEvent(QHideEvent *e)
{
    qDebug("Product hide");
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    if(host->IsParamChanged())
    {
        ICSetAxisConfigsCommand command;
        ICCommandProcessor* process = ICCommandProcessor::Instance();
        int sum = 0;
        QVector<uint> dataBuffer(7, 0);
        dataBuffer[0] = host->SystemParameter(ICVirtualHost::SYS_Config_Signal).toUInt();
        dataBuffer[1] = host->SystemParameter(ICVirtualHost::SYS_Config_Arm).toUInt();
        dataBuffer[2] = host->SystemParameter(ICVirtualHost::SYS_Config_Out).toUInt();
        dataBuffer[3] = host->SystemParameter(ICVirtualHost::SYS_Config_Fixture).toUInt();
    //    dataBuffer[3] = ICVirtualHost::GlobalVirtualHost()->FixtureDefine();
        for(int i = 0; i != 6; ++i)
        {
            sum += dataBuffer.at(i);
        }
        sum = (-sum & 0XFFFF);
        dataBuffer[6] = sum;
        qDebug()<<sum;
        command.SetSlave(process->SlaveID());
        command.SetDataBuffer(dataBuffer);
        command.SetAxis(8);
    #ifndef Q_WS_X11
        if(process->ExecuteCommand(command).toBool())
    #endif
        {
            ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
            host->SetSystemParameter(ICVirtualHost::SYS_Config_Signal, dataBuffer.at(0));
            host->SetAxisDefine(dataBuffer.at(1));
            host->SetPeripheryOutput(dataBuffer.at(2));
            host->SetSystemParameter(ICVirtualHost::SYS_Config_Fixture, dataBuffer.at(3));
            host->SetSystemParameter(ICVirtualHost::SYS_Config_Resv1, dataBuffer.at(4));
            host->SetSystemParameter(ICVirtualHost::SYS_Config_Resv2, dataBuffer.at(5));
            host->SetSystemParameter(ICVirtualHost::SYS_Config_Xorsum, dataBuffer.at(6));
        }
        ICMold::CurrentMold()->SaveMoldParamsFile();
        ICVirtualHost::GlobalVirtualHost()->SaveSystemConfig();
        ICVirtualHost::GlobalVirtualHost()->ReConfigure();
    }
    QFrame::hideEvent(e);
}

void ICHCProductSettingFrame::changeEvent(QEvent *e)
{
    QFrame::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
    {
      // ui->retranslateUi();
        retranslateUi_();
    }
    break;
    default:
        break;
    }
}

void ICHCProductSettingFrame::showEvent(QShowEvent *e)
{
    QStringList items = MoldInformation::Instance()->MoldNameList();
    items.prepend(tr("None"));
    QComboBox* tmp;
    for(int i = 0 ; i != mboxs_.size(); ++i)
    {
        tmp = qobject_cast<QComboBox*>(mboxs_[i]);
        tmp->clear();
        tmp->addItems(items);
    }
//    ui->mBox_1->clear();
//    ui->mBox_1->addItems(items);
//    ui->mBox_2->clear();
//    ui->mBox_2->addItems(items);
//    ui->mBox_3->clear();
//    ui->mBox_3->addItems(items);
//    ui->mBox_4->clear();
//    ui->mBox_4->addItems(items);
//    ui->mBox_5->clear();
//    ui->mBox_5->addItems(items);
//    ui->mBox_6->clear();
//    ui->mBox_6->addItems(items);
//    ui->mBox_7->clear();
//    ui->mBox_7->addItems(items);
//    ui->mBox_8->clear();
//    ui->mBox_8->addItems(items);
//    ui->mBox_9->clear();
//    ui->mBox_9->addItems(items);
//    ui->mBox_10->clear();
//    ui->mBox_10->addItems(items);
//    ui->mBox_11->clear();
//    ui->mBox_11->addItems(items);
//    ui->mBox_12->clear();
//    ui->mBox_12->addItems(items);
    QStringList autoProductList = ICParametersSave::Instance()->AutoMoldList();
    int toPad = (mboxs_.size() - autoProductList.size());
    for(int i = 0; i < toPad; ++i)
    {
        autoProductList.append("");
    }
    ui->mBox_1->setCurrentIndex(ui->mBox_1->findText(autoProductList.at(0)));
    ui->mBox_2->setCurrentIndex(ui->mBox_2->findText(autoProductList.at(1)));
    ui->mBox_3->setCurrentIndex(ui->mBox_3->findText(autoProductList.at(2)));
    ui->mBox_4->setCurrentIndex(ui->mBox_4->findText(autoProductList.at(3)));
    ui->mBox_5->setCurrentIndex(ui->mBox_5->findText(autoProductList.at(4)));
    ui->mBox_6->setCurrentIndex(ui->mBox_6->findText(autoProductList.at(5)));
    ui->mBox_7->setCurrentIndex(ui->mBox_7->findText(autoProductList.at(6)));
    ui->mBox_8->setCurrentIndex(ui->mBox_8->findText(autoProductList.at(7)));
    ui->mBox_9->setCurrentIndex(ui->mBox_9->findText(autoProductList.at(8)));
    ui->mBox_10->setCurrentIndex(ui->mBox_10->findText(autoProductList.at(9)));
    ui->mBox_11->setCurrentIndex(ui->mBox_11->findText(autoProductList.at(10)));
    ui->mBox_12->setCurrentIndex(ui->mBox_12->findText(autoProductList.at(11)));
    ui->autoProductGroupBox->blockSignals(true);
    ui->autoProductGroupBox->setChecked(ICParametersSave::Instance()->IsAutoProductEnabled());
    ui->autoProductGroupBox->blockSignals(false);
    ui->autoRecycle->setChecked(ICParametersSave::Instance()->IsAutoRecycleEnabled());
    QFrame::showEvent(e);
}

void ICHCProductSettingFrame::retranslateUi_()
{
    this->setWindowTitle(tr("Frame"));
    ui->label->setText(tr("Product"));
    ui->label_2->setText(tr("Wait Mold Opened Limit Time"));
    ui->label_4->setText(tr("s"));
    ui->productClearButton->setText(tr("Product Clear"));
    ui->label_7->setText(tr("TryProduct")); //试产模数
    ui->label_8->setText(tr("Sampling Interval"));
    ui->label_9->setText(tr("Bad Product"));
    ui->label_5->setText(tr("Alarm Times"));
    ui->label_6->setText(tr("Times"));
    ui->label_17->setText(tr("Fixture"));
//    ui->fixtureSelectBox->setItemText(0,tr("Reversed Phase"));
//    ui->fixtureSelectBox->setItemText(1,tr("Positive Phase"));
    ui->reversedCheckBox->setText(tr("Reversed Phase"));
    ui->positiveCheckBox->setText(tr("Positive Phase"));
    ui->getFailWay->setItemText(0, tr("Alarm When Up"));
    ui->getFailWay->setItemText(1, tr("Alarm Once"));
    ui->countUnitBox->setItemText(0, tr("All"));
    ui->countUnitBox->setItemText(1, tr("Good"));
    ui->countUnitBox->setItemText(2, tr("Stack-1"));
    ui->countUnitBox->setItemText(3, tr("Stack-2"));
    ui->countUnitBox->setItemText(4, tr("Stack-3"));
    ui->countUnitBox->setItemText(5, tr("Stack-4"));
    ui->label_18->setText(tr("Count Ways"));
    ui->label_10->setText(tr("Get Fail"));
}

void ICHCProductSettingFrame::OnMoldNumberParamChanged()
{
    for(int i = 0; i != wrappers_.size(); ++i)
    {
        wrappers_[i]->UpdateParam();
    }
    ui->countUnitBox->setCurrentIndex(ICMold::CurrentMold()->MoldParam(ICMold::CountUnit));
}

void ICHCProductSettingFrame::on_productClearButton_clicked()
{
    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_PRODUCT_CLEAR);
    ICVirtualHost::GlobalVirtualHost()->SetFinishProductCount(0);
}

void ICHCProductSettingFrame::FixtureBoxChange()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    host->SetSystemParameter(ICVirtualHost::SYS_Config_Fixture, host->FixtureDefineSwitch(buttongroup_->checkedId()));
}

void ICHCProductSettingFrame::InitCheckBox()
{
    buttongroup_->addButton(ui->reversedCheckBox,0);
    buttongroup_->addButton(ui->positiveCheckBox,1);

    QList<QAbstractButton*> buttons = buttongroup_->buttons();
    for(int i = 0; i != buttons.size(); ++i)
    {
        buttons[i]->setCheckable(true);
        connect(buttons.at(i),
                SIGNAL(clicked()),
                this,
                SLOT(FixtureBoxChange()));
    }
    buttongroup_->setExclusive(true);
}

void ICHCProductSettingFrame::on_countUnitBox_currentIndexChanged(int index)
{
    ICMold::CurrentMold()->SetMoldParam(ICMold::CountUnit, index);
}

void ICHCProductSettingFrame::on_getFailWay_activated(int index)
{
    ICVirtualHost::GlobalVirtualHost()->SetGetFailAlarmWay(index);
}

void ICHCProductSettingFrame::on_saveButton_clicked()
{
    QStringList ret;
    QComboBox* cb;
    for(int i = 0; i != mboxs_.size(); ++i)
    {
        cb = qobject_cast<QComboBox*>(mboxs_.at(i));
        ret.append(cb->currentText());
    }
//    ret.append(ui->mBox_1->currentText());
//    ret.append(ui->mBox_2->currentText());
//    ret.append(ui->mBox_3->currentText());
//    ret.append(ui->mBox_4->currentText());
//    ret.append(ui->mBox_5->currentText());
//    ret.append(ui->mBox_6->currentText());
//    ret.append(ui->mBox_7->currentText());
//    ret.append(ui->mBox_8->currentText());
    ICParametersSave::Instance()->SetAutoMoldList(ret);
    ICParametersSave::Instance()->SetAutoRecycleEnable(ui->autoRecycle->isChecked());
}

void ICHCProductSettingFrame::on_autoProductGroupBox_toggled(bool arg1)
{
    ICParametersSave::Instance()->SetAutoProductEnable(arg1);
}

void ICHCProductSettingFrame::OnProductMoldNameChanged(int index)
{
//    qDebug()<<text;
    if(index == 0) return;
    QComboBox* w = qobject_cast<QComboBox*>(sender());
    ICMold mold;
    if(!mold.ReadMoldFile(QString("./records/%1.act").arg(w->currentText()))) return;
    int row = 0;
    for(int i = 0; i != mboxs_.size(); ++i)
    {
        if(w == mboxs_.at(i))
        {
            row = i;
            break;
        }
    }
    ICLineEditWithVirtualNumericKeypad *e = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(pcEdits_.at(row));
    e->SetThisIntToThisText(mold.MoldParam(ICMold::Product));
//    mold.SaveMoldParamsFile();
}

void ICHCProductSettingFrame::OnProductCountChanged(const QString &text)
{
    ICLineEditWithVirtualNumericKeypad* w = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(sender());
    int row = 0;
    for(int i = 0; i != pcEdits_.size(); ++i)
    {
        if(w == pcEdits_.at(i))
        {
            row = i;
            break;
        }
    }
    ICMold mold;
    QComboBox* c = qobject_cast<QComboBox*>(mboxs_.at(row));
    if(!mold.ReadMoldFile(QString("./records/%1.act").arg(c->currentText()))) return;
    mold.SetMoldParam(ICMold::Product, text.toUInt());
    mold.SaveMoldParamsFile();
}

void ICHCProductSettingFrame::OnProductClearClicked()
{
    QWidget *w = qobject_cast<QWidget*>(sender());
    int row = 0;
    for(int i = 0; i != clearButtons_.size(); ++i)
    {
        if(w == clearButtons_.at(i))
        {
            row = i;
            break;
        }
    }
    ICLineEditWithVirtualNumericKeypad *e = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(pcEdits_.at(row));
    e->setText("0");
//    ICMold mold;
//    QComboBox* c = qobject_cast<QComboBox*>(mboxs_.at(row));
//    if(!mold.ReadMoldFile(QString("./records/%1.act").arg(c->currentText()))) return;
//    mold.SetMoldParam(0);
//    mold.SaveMoldParamsFile();
}
