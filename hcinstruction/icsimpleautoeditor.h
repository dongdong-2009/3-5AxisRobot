#ifndef ICSIMPLEAUTOEDITOR_H
#define ICSIMPLEAUTOEDITOR_H

#include <QDialog>
#include "icmold.h"
#include <QIntValidator>

class QLabel;
class ICLineEditWithVirtualNumericKeypad;
class QIntValidator;
class QGridLayout;


namespace Ui {
class ICSimpleAutoEditor;
}

union PosDlyUIWidgets
{
    struct
    {
        QLabel* posName;
        ICLineEditWithVirtualNumericKeypad* x1DlyEdit;
        ICLineEditWithVirtualNumericKeypad* y1DlyEdit;
        ICLineEditWithVirtualNumericKeypad* zDlyEdit;
        ICLineEditWithVirtualNumericKeypad* x2DlyEdit;
        ICLineEditWithVirtualNumericKeypad* y2DlyEdit;
    }b;
    QWidget* all[6];
};

class ICSimpleAutoEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ICSimpleAutoEditor(QWidget *parent = 0);
    ~ICSimpleAutoEditor();

    void SetMainArmPosEnabled(bool en);
    void SetSubArmPosEnabled(bool en);
    void SetReleaseOutletEnabled(bool en);
    void SetReleaseProductEnabled(bool en);
    void SetCutOutletEnabled(bool en);
    QMap<int, int> GetModifiedDelays() const { return modifiedDelays;}
    void AddPosHelper(QGridLayout *layout, QList<PosDlyUIWidgets> &dlyUI, const QString& posName, int defaultDly = 0);

protected:
    void changeEvent(QEvent *e);
    void showEvent(QShowEvent *e);
    void keyPressEvent(QKeyEvent* e);

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    bool UsedMainArm() const { return stData_->usedMainArm || stData_->usedMainArmOutlet;}
    bool UsedSubArm() const { return stData_->usedSubArm;}
    bool UsedReleaseOutlet() const { return stData_->usedSubArm || stData_->usedMainArmOutlet;}

private:
    Ui::ICSimpleAutoEditor *ui;
    SimpleTeachData* stData_;

    QList<PosDlyUIWidgets> releaseProductDlyUI;
    QList<PosDlyUIWidgets> releaseOutletDlyUI;
    QList<PosDlyUIWidgets> cutOutletDlyUI;

    QIntValidator delayValidator_;

    QMap<int, int> modifiedDelays;

};

#endif // ICSIMPLEAUTOEDITOR_H
