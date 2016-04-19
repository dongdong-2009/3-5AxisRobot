#include "icguidefixtureeditor.h"
#include "ui_icguidefixtureeditor.h"
#include "iccommandprocessor.h"
#include "icmold.h"
#include "icvirtualkey.h"

ICGuideFixtureEditor::ICGuideFixtureEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICGuideFixtureEditor),
    onPixmap_(":/resource/ledgreen(16).png"),
    offPixmap_(":/resource/ledgray(16).png")
{
    ui->setupUi(this);
    QPushButton *buttons = new QPushButton[ui->tableWidget->rowCount()];
    ioNames_<<tr("Fixture1  ")<<tr("Fixture2  ")<<tr("Fixture3  ")<<tr("Fixture4  ")
           <<tr("Sucker1   ")<<tr("Sucker2   ")
          <<tr("Sucker3   ")<<tr("Sucker4   ")
         <<tr("Sucker5   ")<<tr("Sucker6   ")
        <<tr("Sucker7   ")<<tr("Sucker8   ");
    onClipToOffClip_.insert(ICMold::ACTCLIP1ON, ICMold::ACTCLIP1OFF);
    onClipToOffClip_.insert(ICMold::ACTCLIP2ON, ICMold::ACTCLIP2OFF);
    onClipToOffClip_.insert(ICMold::ACTCLIP3ON, ICMold::ACTCLIP3OFF);
    onClipToOffClip_.insert(ICMold::ACTCLIP4ON, ICMold::ACTCLIP4OFF);
    onClipToOffClip_.insert(ICMold::ACTCLIP5ON, ICMold::ACTCLIP5OFF);
    onClipToOffClip_.insert(ICMold::ACTCLIP6ON, ICMold::ACTCLIP6OFF);
    onClipToOffClip_.insert(ICMold::ACT_AUX5, ICMold::ACT_AUX5 + 1000);
    onClipToOffClip_.insert(ICMold::ACT_AUX6, ICMold::ACT_AUX6 + 1000);
    onClipToOffClip_.insert(ICMold::ACT_AUX1, ICMold::ACT_AUX1 + 1000);
    onClipToOffClip_.insert(ICMold::ACT_AUX2, ICMold::ACT_AUX2 + 1000);
    onClipToOffClip_.insert(ICMold::ACT_AUX3, ICMold::ACT_AUX3 + 1000);
    onClipToOffClip_.insert(ICMold::ACT_AUX4, ICMold::ACT_AUX4 + 1000);
    offClipToOnClip_.insert(ICMold::ACTCLIP1OFF, ICMold::ACTCLIP1ON);
    offClipToOnClip_.insert(ICMold::ACTCLIP2OFF, ICMold::ACTCLIP2ON);
    offClipToOnClip_.insert(ICMold::ACTCLIP3OFF, ICMold::ACTCLIP3ON);
    offClipToOnClip_.insert(ICMold::ACTCLIP4OFF, ICMold::ACTCLIP4ON);
    offClipToOnClip_.insert(ICMold::ACTCLIP5OFF, ICMold::ACTCLIP5ON);
    offClipToOnClip_.insert(ICMold::ACTCLIP6OFF, ICMold::ACTCLIP6ON);
    offClipToOnClip_.insert(ICMold::ACT_AUX5 + 1000, ICMold::ACT_AUX5);
    offClipToOnClip_.insert(ICMold::ACT_AUX6 + 1000, ICMold::ACT_AUX6);
    offClipToOnClip_.insert(ICMold::ACT_AUX1 + 1000, ICMold::ACT_AUX1);
    offClipToOnClip_.insert(ICMold::ACT_AUX2 + 1000, ICMold::ACT_AUX2);
    offClipToOnClip_.insert(ICMold::ACT_AUX3 + 1000, ICMold::ACT_AUX3);
    offClipToOnClip_.insert(ICMold::ACT_AUX4 + 1000, ICMold::ACT_AUX4);

    QList<uint> initStatus;
    initStatus<<ICMold::ACTCLIP1OFF<<ICMold::ACTCLIP2OFF<<ICMold::ACTCLIP3OFF
                <<ICMold::ACTCLIP4OFF<<ICMold::ACTCLIP5OFF<<ICMold::ACTCLIP6OFF
                  <<(ICMold::ACT_AUX5 + 1000)<<(ICMold::ACT_AUX6 + 1000)<<(ICMold::ACT_AUX1 + 1000)
                    <<(ICMold::ACT_AUX2 + 1000)<<(ICMold::ACT_AUX3 + 1000)<<(ICMold::ACT_AUX4 + 1000);
    QPushButton * button;

    for(int i = 0; i != ui->tableWidget->rowCount(); ++i)
    {
        clipToRow_.insert(initStatus.at(i), i);
        clipToRow_.insert(offClipToOnClip_.value(initStatus.at(i)), i);
        button = buttons + i;
//        button->setMinimumWidth(100);
        button->setIcon(offPixmap_);
        button->setText(ioNames_.at(i));


        settingButtons_.append(button);
        ui->tableWidget->setCellWidget(i, 1, button);

        buttonToClip_.insert(button, initStatus.at(i));
        buttonSignalMapper_.setMapping(button, button);
        connect(button,
                SIGNAL(clicked()),
                &buttonSignalMapper_,
                SLOT(map()));
    }

    commandKeyMap_.insert(settingButtons_.at(0), qMakePair(static_cast<int>(IC::VKEY_CLIP1ON), static_cast<int>(IC::VKEY_CLIP1OFF)));
    commandKeyMap_.insert(settingButtons_.at(1), qMakePair(static_cast<int>(IC::VKEY_CLIP2ON), static_cast<int>(IC::VKEY_CLIP2OFF)));
    commandKeyMap_.insert(settingButtons_.at(2), qMakePair(static_cast<int>(IC::VKEY_CLIP3ON), static_cast<int>(IC::VKEY_CLIP3OFF)));
    commandKeyMap_.insert(settingButtons_.at(3), qMakePair(static_cast<int>(IC::VKEY_CLIP4ON), static_cast<int>(IC::VKEY_CLIP4OFF)));
    commandKeyMap_.insert(settingButtons_.at(4), qMakePair(static_cast<int>(IC::VKEY_CLIP5ON), static_cast<int>(IC::VKEY_CLIP5OFF)));
    commandKeyMap_.insert(settingButtons_.at(5), qMakePair(static_cast<int>(IC::VKEY_CLIP6ON), static_cast<int>(IC::VKEY_CLIP6OFF)));
    commandKeyMap_.insert(settingButtons_.at(6), qMakePair(static_cast<int>(IC::VKEY_RESERVE5_ON), static_cast<int>(IC::VKEY_RESERVE5_OFF)));
    commandKeyMap_.insert(settingButtons_.at(7), qMakePair(static_cast<int>(IC::VKEY_RESERVE6_ON), static_cast<int>(IC::VKEY_RESERVE6_OFF)));
    commandKeyMap_.insert(settingButtons_.at(8), qMakePair(static_cast<int>(IC::VKEY_RESERVE1_ON), static_cast<int>(IC::VKEY_RESERVE1_OFF)));
    commandKeyMap_.insert(settingButtons_.at(9), qMakePair(static_cast<int>(IC::VKEY_RESERVE2_ON), static_cast<int>(IC::VKEY_RESERVE2_OFF)));
    commandKeyMap_.insert(settingButtons_.at(10), qMakePair(static_cast<int>(IC::VKEY_RESERVE3_ON), static_cast<int>(IC::VKEY_RESERVE3_OFF)));
    commandKeyMap_.insert(settingButtons_.at(11), qMakePair(static_cast<int>(IC::VKEY_RESERVE4_ON), static_cast<int>(IC::VKEY_RESERVE4_OFF)));

    connect(&buttonSignalMapper_,
            SIGNAL(mapped(QWidget*)),
            this,
            SLOT(CommandButtonClicked(QWidget*)));
    ui->tableWidget->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->setColumnWidth(2, 150);
}

ICGuideFixtureEditor::~ICGuideFixtureEditor()
{
    delete ui;
}

void ICGuideFixtureEditor::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        ioNames_<<tr("Fixture1  ")<<tr("Fixture2  ")<<tr("Fixture3  ")<<tr("Fixture4  ")
               <<tr("Sucker1   ")<<tr("Sucker2   ")
              <<tr("Sucker3   ")<<tr("Sucker4   ")
             <<tr("Sucker5   ")<<tr("Sucker6   ")
            <<tr("Sucker7   ")<<tr("Sucker8   ");
        for(int i = 0; i != settingButtons_.size(); ++i)
        {
            settingButtons_[i]->setText(ioNames_.at(i));
        }
        break;
    default:
        break;
    }
}

int ICGuideFixtureEditor::ShowEditor(const QList<QPair<int, bool> > &fixturesConfigs, bool isNoCheckMode)
{
    ui->tableWidget->setColumnHidden(2, isNoCheckMode);
    on_pushButton_clicked();
    QPair<int, bool> config;
    for(int i = 0; i < fixturesConfigs.size(); ++i)
    {
        config = fixturesConfigs.at(i);
        ui->tableWidget->item(config.first, 0)->setCheckState(Qt::Checked);
        ui->tableWidget->item(config.first, 2)->setCheckState(config.second ? Qt::Checked : Qt::Unchecked);
    }
    return this->exec();
}

QList<QPair<int , bool> > ICGuideFixtureEditor::GetConfigs() const
{
    QList<QPair<int , bool> > ret;
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        if(ui->tableWidget->item(i, 0)->checkState() == Qt::Checked)
        {
            ret.append(qMakePair(i, ui->tableWidget->item(i, 2)->checkState() == Qt::Checked));
        }
    }
    return ret;
}

void ICGuideFixtureEditor::on_pushButton_clicked()
{
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
//        if(ui->tableWidget->item(i, 0)->checkState() == Qt::Checked)
//        {
//            ret.append(qMakePair(i, ui->tableWidget->item(i, 2)->checkState() == Qt::Checked));
//        }
        ui->tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
        ui->tableWidget->item(i, 2)->setCheckState(Qt::Unchecked);
    }

}

void ICGuideFixtureEditor::CommandButtonClicked(QWidget *widget)
{
    QAbstractButton* button = qobject_cast<QAbstractButton*>(widget);
    Q_ASSERT_X(button != NULL, "ICHCFixturePage::CommandButtonClicked", "widget is null");
    int key;
    int currentClip = buttonToClip_.value(button);
    if(onClipToOffClip_.contains(currentClip))
    {
        key = commandKeyMap_.value(button).second;
        buttonToClip_.insert(button, onClipToOffClip_.value(currentClip));
        button->setIcon(offPixmap_);
    }
    else
    {
        key = commandKeyMap_.value(button).first;
        buttonToClip_.insert(button, offClipToOnClip_.value(currentClip));
        button->setIcon(onPixmap_);
    }
    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(key);
}

void ICGuideFixtureEditor::on_okButton_clicked()
{
    this->accept();
}

void ICGuideFixtureEditor::on_cancelButton_clicked()
{
    this->reject();
}

QStringList ICGuideFixtureEditor::SelectedNames() const
{
    QStringList ret;
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        if(ui->tableWidget->item(i, 0)->checkState() == Qt::Checked)
            ret.append(settingButtons_.at(i)->text());
//        ui->tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
//        ui->tableWidget->item(i, 2)->setCheckState(Qt::Unchecked);
    }
    return ret;
}

QStringList ICGuideFixtureEditor::SelectedNames(const QList<QPair<int, bool> > &fixturesConfigs) const
{
    QStringList ret;
    for(int i = 0; i < fixturesConfigs.size(); ++i)
    {
        if(fixturesConfigs.at(i).second)
            ret.append(QString(tr("%1[Check]")).arg(settingButtons_.at(fixturesConfigs.at(i).first)->text()));
        else
            ret.append(settingButtons_.at(fixturesConfigs.at(i).first)->text());
    }
    if(ret.isEmpty())
        ret.append(tr("None"));
    return ret;
}
