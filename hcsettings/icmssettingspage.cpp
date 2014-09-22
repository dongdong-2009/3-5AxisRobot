#include "icmssettingspage.h"
#include "ui_icmssettingspage.h"

ICMSSettingsPage::ICMSSettingsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICMSSettingsPage)
{
    ui->setupUi(this);
}

ICMSSettingsPage::~ICMSSettingsPage()
{
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
