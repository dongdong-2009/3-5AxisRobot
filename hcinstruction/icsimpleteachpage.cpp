#include "icsimpleteachpage.h"
#include "ui_icsimpleteachpage.h"

ICSimpleTeachPage::ICSimpleTeachPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICSimpleTeachPage)
{
    ui->setupUi(this);
}

ICSimpleTeachPage::~ICSimpleTeachPage()
{
    delete ui;
}
