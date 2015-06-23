#include "icinputdialog.h"
#include "ui_icinputdialog.h"

ICInputDialog::ICInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICInputDialog)
{
    ui->setupUi(this);
    ui->tipLabel->setScaledContents(true);
}

ICInputDialog::~ICInputDialog()
{
    delete ui;
}

void ICInputDialog::changeEvent(QEvent *e)
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

void ICInputDialog::setLabelText(const QString &text)
{
    ui->tipLabel->setText(text);
}

QString ICInputDialog::textValue() const
{
    return ui->lineEdit->text();
}

QString ICInputDialog::getText(QWidget *parent, const QString &title, const QString &label)
{
    ICInputDialog d(parent);
    d.setWindowTitle(title);
    d.setLabelText(label);
    d.exec();
    return d.textValue();
}
