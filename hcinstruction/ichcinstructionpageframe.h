#ifndef ICHCINSTRUCTIONPAGEFRAME_H
#define ICHCINSTRUCTIONPAGEFRAME_H

#include <QFrame>

#include <QMap>
#include <QStackedLayout>

#include "icmold.h"
#include "icinstructmodifydialog.h"
#include "icbadproducteditor.h"

namespace Ui {
    class ICHCInstructionPageFrame;
}
class ActionSettingFrame;
class ICProgramGuidePage;
class ICHCConditionPage;
class QListWidgetItem;
class ICInstructionEditorBase;

class ICHCInstructionPageFrame : public QFrame
{
    Q_OBJECT

public:
    enum CurrentAction
    {
        None,
        Insert,
        Modify
    };

    explicit ICHCInstructionPageFrame(QWidget *parent = 0);
    ~ICHCInstructionPageFrame();

    int ValidFlag();
//    void LoadFileInfoButtonClicked(const QString & moldName);

protected:
    void hideEvent(QHideEvent *e);
    void showEvent(QShowEvent *e);
    void changeEvent(QEvent *);

public slots:
//    void SelectCurrentStep(int currentStep);
    void ShowServoAction(int key);

private slots:
    void on_deleteToolButton_clicked();
    void on_modifyToolButton_clicked();
    void on_insertToolButton_clicked();
//    void on_programSelectedComboBox_activated(QString );
    void OptionButtonClicked();
//    void LoadAllRecordFileInfo();

    void UpdateHostParam();

//    void NewFileCreated(const QString & moldName);
//    void DeleteFile(const QString & moldName);

    void on_commandButton_clicked();

    void on_upButton_clicked();

    void on_downButton_clicked();

    void OnProgramChanged(int index, QString name);

    void on_aPlusBtn_pressed();

    void on_aMinusBtn_pressed();
    void OnActionButtonReleased();
    void OnGuideFinished();

    void on_tryButton_clicked();

    void on_moldContentListWidget_itemPressed(QListWidgetItem *item);

    void OnBadProductSettingsChanged();
signals:
//    void JumpToProgramEditorPage();

private:
    void InitInterface();
    void InitSignal();
    void InitParameter();
    void FindIndex_(int currentIndex, int& groupItemIndex, int& topItemIndex, int& subItemIndex);
    void UpdateUIProgramList_();
    QStringList Flags();

//    void LoadProgram(const QString & moldName);
//    void LoadMacro(const QString & macroName);

//    void AddCommandStr(const QString & commandStr);

//    void LoadMoldFile(const QString & moldName);
    void CurrentMoldFileChanged(const QString & moldName);

    bool SaveCurrentEdit();

private:
    Ui::ICHCInstructionPageFrame *ui;
    ActionSettingFrame * actionPage_;
    ICInstructionEditorBase* injectionPage_;
    ICInstructionEditorBase * fixturePage_;
    ICHCConditionPage * conditionPage_;
    ICInstructionEditorBase * flagsPage_;
    ICInstructionEditorBase * pneumaticPage_;
    ICInstructionEditorBase * waitConditionPage_;
    ICInstructionEditorBase * peripheryPage_;
    ICInstructionEditorBase * cutPage_;
    ICInstructionEditorBase * programPage_;
    ICInstructionEditorBase * stackPage_;
    ICInstructionEditorBase * otherPage_;
    ICInstructionEditorBase * commentPage_;
    ICBadProductEditor * badProductEditor_;
    ICProgramGuidePage * guidePage_;
    ICInstructModifyDialog *modifyDialog_;

    QString recordPath_;
    CurrentAction currentAction_;

    QMap<QWidget *, QWidget *> optionButtonToPage_;

    QList<ICGroupMoldUIItem> programList_;
    int currentEdit_;
    bool isProgramChanged_;
    bool isModifyProgram_;
    QMap<QListWidgetItem*, ICMoldItem> viewItemToMoldItemMap_;
};

#endif // ICHCINSTRUCTIONPAGEFRAME_H
