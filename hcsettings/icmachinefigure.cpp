#include "icmachinefigure.h"
#include "ui_icmachinefigure.h"
#include "icvirtualhost.h"
#include "iclineeditwrapper.h"
#include "icmessagebox.h"
#include "icconfigstring.h"

ICMachineFigure::ICMachineFigure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICMachineFigure)
{
    ui->setupUi(this);
//    ui->figure->resize(this->size());

    QIntValidator * validator = new QIntValidator(0, 65530, this);
    ui->xsec1->setValidator(validator);
    ui->xsec2->setValidator(validator);
    ui->xsec3->setValidator(validator);
    ui->xsec4->setValidator(validator);

    ui->xsec1->SetDecimalPlaces(1);
    ui->xsec2->SetDecimalPlaces(1);
    ui->xsec3->SetDecimalPlaces(1);
    ui->xsec4->SetDecimalPlaces(1);

    ICLineEditWrapper* wrapper = new ICLineEditWrapper(ui->xsec1,
                                                       ICVirtualHost::SM_X_SEC1,
                                                       ICLineEditWrapper::System,
                                                       ICLineEditWrapper::OneFraction);
    wrappers_.append(wrapper);
    wrapper = new ICLineEditWrapper(ui->xsec2,
                                    ICVirtualHost::SM_X_SEC2,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::OneFraction);
    wrappers_.append(wrapper);
    wrapper = new ICLineEditWrapper(ui->xsec3,
                                    ICVirtualHost::SM_X_SEC3,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::OneFraction);
    wrappers_.append(wrapper);
    wrapper = new ICLineEditWrapper(ui->xsec4,
                                    ICVirtualHost::SM_X_SEC4,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::OneFraction);
    wrappers_.append(wrapper);

    editorToConfigIDs_.insert(ui->xsec3, ICConfigString::kCS_SECP_Inside_X_Min);
    editorToConfigIDs_.insert(ui->xsec4, ICConfigString::kCS_SECP_Inside_X_Max);
    editorToConfigIDs_.insert(ui->xsec1, ICConfigString::kCS_SECP_Outside_X_Min);
    editorToConfigIDs_.insert(ui->xsec2, ICConfigString::kCS_SECP_Outside_X_Max);

    ICLogInit;
}

ICMachineFigure::~ICMachineFigure()
{
    qDeleteAll(wrappers_);
    delete ui;
}

void ICMachineFigure::changeEvent(QEvent *e)
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

void ICMachineFigure::showEvent(QShowEvent *e)
{
    ui->xmin->setText(QString("%1").arg(ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_X_InSafe).toUInt() / 10.0));
    ui->xmax->setText(QString("%1").arg(ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_X_OutSafe).toUInt() / 10.0));
    QWidget::showEvent(e);
}

void ICMachineFigure::hideEvent(QHideEvent *e)
{
    QWidget::hideEvent(e);
}

/***BUG#200**去掉save按钮，将保存步骤添加到icmachinefigure.cpp文件中hideEvent函数133行****/
//void ICMachineFigure::on_saveButton_clicked()
//{
//    ICVirtualHost::GlobalVirtualHost()->SaveSystemConfig();
//    ICMessageBox::ICWarning(this, tr("Tips"), tr("Save successfully!"));
//}

ICLogFunctions(ICMachineFigure)
