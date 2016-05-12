#include "iccaretipui.h"
#include "ui_iccaretipui.h"
#include <QLabel>
#include <QPushButton>
#include "icparameterssave.h"

ICCareTipUI::ICCareTipUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICCareTipUI)
{
    ui->setupUi(this);
    QStringList items;
    items<<tr("Item-1")<<tr("Item-2")<<tr("Item-3")
           <<tr("Item-4")<<tr("Item-5")<<tr("Item-6")<<tr("Item-7");
    ICParametersSave* ps = ICParametersSave::Instance();
    QDate currentDate = QDate::currentDate();
    for(int i = 0; i !=items.size(); ++i)
    {
        QPushButton* btn = new QPushButton(tr("Has Care"));
        hasCareBtns_.append(btn);
//        ui->careTable->setCellWidget(i, 3, cycleEditor);
        ui->careTable->setCellWidget(i, 4, btn);
        hasCareBtnToItemIndex_.insert(btn, i);
        QLabel* label = new QLabel(items.at(i));
        label->setWordWrap(true);
        ui->careTable->setCellWidget(i, 0, label);

        ui->careTable->item(i, 1)->setText(QString::number(currentDate.daysTo(ps->NextCycle(i))));
        ui->careTable->item(i, 2)->setText(ps->NextCycle(i).toString("yyyy/MM/dd"));
        ui->careTable->item(i, 3)->setText(QString::number(ps->CareCycle(i)));
        connect(btn, SIGNAL(clicked()),SLOT(OnHasCareBtnClicked()));
    }
//    ui->careTable->horizontalHeader()->setSet
    ui->careTable->resizeColumnsToContents();
    ui->careTable->resizeRowsToContents();
    ui->careTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
}

ICCareTipUI::~ICCareTipUI()
{
    delete ui;
}

void ICCareTipUI::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ICCareTipUI::OnHasCareBtnClicked()
{
    int index = hasCareBtnToItemIndex_.value(qobject_cast<QPushButton*>(sender()));
    ICParametersSave *ps = ICParametersSave::Instance();
    QDate next = QDate::currentDate().addDays(ps->CareCycle(index));
    ICParametersSave::Instance()->SetNextCycle(index, next);
    ui->careTable->item(index, 2)->setText(ps->NextCycle(index).toString("yyyy/MM/dd"));
    ui->careTable->item(index, 1)->setText(QString::number(ps->CareCycle(index)));
}
