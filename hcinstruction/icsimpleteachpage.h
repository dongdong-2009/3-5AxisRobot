#ifndef ICSIMPLETEACHPAGE_H
#define ICSIMPLETEACHPAGE_H

#include <QWidget>
#include <QVariantList>
#include <QIntValidator>
#include "icguidefixtureeditor.h"
#include "icmold.h"

class QLabel;
class QPushButton;
class ICLineEditWithVirtualNumericKeypad;
class QGridLayout;


//struct PosData{
//    QVariantList pos;
//    FixtureConfigs fixtureConfis;
//};

namespace Ui {
    class ICSimpleTeachPage;
}

//struct ReleasePosUIWidgets{
//    QLabel* posName;
//    QPushButton* setInBtn;
//    ICLineEditWithVirtualNumericKeypad* x1PosEdit;
//    ICLineEditWithVirtualNumericKeypad* y1PosEdit;
//    ICLineEditWithVirtualNumericKeypad* zPosEdit;
//    ICLineEditWithVirtualNumericKeypad* x2PosEdit;
//    ICLineEditWithVirtualNumericKeypad* y2PosEdit;
//    QPushButton* fixureSel;
//    QLabel* fixtureInfo;

//};
union PosSpeedUIWidgets
{
    struct
    {
        QLabel* posName;
        ICLineEditWithVirtualNumericKeypad* x1SpeedEdit;
        ICLineEditWithVirtualNumericKeypad* y1SpeedEdit;
        ICLineEditWithVirtualNumericKeypad* zSpeedEdit;
        ICLineEditWithVirtualNumericKeypad* x2SpeedEdit;
        ICLineEditWithVirtualNumericKeypad* y2SpeedEdit;
    }b;
    QWidget* all[6];
};



class ICSimpleTeachPage : public QWidget
{
    Q_OBJECT

public:
    explicit ICSimpleTeachPage(QWidget *parent = 0);
    ~ICSimpleTeachPage();

protected:
    void changeEvent(QEvent *);
    void showEvent(QShowEvent *e);
//    void hideEvent(QHideEvent *e);

private slots:

    void on_posInsideBtn_toggled(bool checked);

    void on_posOutsideBtn_toggled(bool checked);

    void on_posOfCutBtn_toggled(bool checked);

    void on_mainArmEn_toggled(bool checked);

    void on_mainArmOutletEn_toggled(bool checked);

    void on_subArmEn_toggled(bool checked);

    void SetMainArmPosEnabled(bool en);
    void SetSubArmPosEnabled(bool en);
    void SetReleaseOutletEnabled(bool en);
    void SetReleaseProductEnabled(bool en);
    void SetCutOutletEnabled(bool en);

    void on_addProductPos_clicked();

    void on_modifyProductPos_clicked();

    void on_deleteProductPos_clicked();


    void on_addOutletPos_clicked();

    void on_modifyOutletPos_clicked();

    void on_deleteOutletPos_clicked();

    void on_addCut_clicked();

    void on_modifyCut_clicked();

    void on_deleteCut_clicked();


    void on_getProductFSel_clicked();

    void on_getOutletFSel_clicked();


    void on_releaseProductFSel_clicked();

    void on_releaseOutletFSel_clicked();

    void on_cutFSel_clicked();

    void on_cutOutletEn_toggled(bool checked);

    void on_saveBtn_clicked();

private:
    QString PosDataToString(const ReleasePosData& posData, bool noSubArm = false, const QString& dataName = "") const ;
    bool UsedMainArm() const;
    bool UsedSubArm() const;
    bool UsedReleaseOutlet() const;

    void AddPosHelper(QGridLayout* layout, QList<PosSpeedUIWidgets>& speedUI, const QString& posName, int defaultSpeed = 80);
    void DelPosHelper(int row, QGridLayout* layout, QList<PosSpeedUIWidgets>& speedUI, const QString& posName);
private:
    Ui::ICSimpleTeachPage *ui;
    QList<PosSpeedUIWidgets> releaseProductSpeedUI;
    QList<PosSpeedUIWidgets> releaseOutletSpeedUI;
    QList<PosSpeedUIWidgets> cutOutletSpeedUI;
    QIntValidator speedValidator_;
    QIntValidator posValidator_;
    QIntValidator delayValidator_;

    ICGuideFixtureEditor* fixtureSel_;


    FixtureConfigs releaseProductCFConfigs_;
    FixtureConfigs releaseOutletCFConfigs_;
    FixtureConfigs cutOutletCFConfigs_;

    SimpleTeachData* stData_;


};

#endif // ICSIMPLETEACHPAGE_H
