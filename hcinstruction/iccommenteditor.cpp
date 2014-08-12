#include "iccommenteditor.h"
#include "ui_iccommenteditor.h"

ICCommentEditor::ICCommentEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICCommentEditor)
{
    ui->setupUi(this);
}

ICCommentEditor::~ICCommentEditor()
{
    delete ui;
}

void ICCommentEditor::changeEvent(QEvent *e)
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
