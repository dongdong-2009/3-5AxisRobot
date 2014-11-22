#include "icmssettingspage.h"
#include "ui_icmssettingspage.h"
#include "icvirtualhost.h"
#include "iclineeditwrapper.h"
#include <QHideEvent>

ICMSSettingsPage::ICMSSettingsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICMSSettingsPage)
{
    ui->setupUi(this);
    ICLineEditWrapper* wrapper = new ICLineEditWrapper(ui->msDistance,
                                                       ICVirtualHost::SM_PullPushDistance,
                                                       ICLineEditWrapper::System,
                                                       ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);
}

ICMSSettingsPage::~ICMSSettingsPage()
{
    qDeleteAll(wrappers_);
    delete ui;
}

void ICMSSettingsPage::changeEvent(QEvent *e)
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

void ICMSSettingsPage::hideEvent(QHideEvent *e)
{
    if(ICVirtualHost::GlobalVirtualHost()->IsParamChanged())
    {
        ICVirtualHost::GlobalVirtualHost()->SaveSystemConfig();
        ICVirtualHost::GlobalVirtualHost()->ReConfigure();
    }
    QWidget::hideEvent(e);
}
