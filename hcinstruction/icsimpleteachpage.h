#ifndef ICSIMPLETEACHPAGE_H
#define ICSIMPLETEACHPAGE_H

#include <QWidget>
#include <QVariantList>
#include <QIntValidator>

class QLabel;
class QPushButton;
class ICLineEditWithVirtualNumericKeypad;
class QGridLayout;

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

    void on_addProductPos_clicked();

    void on_modifyProductPos_clicked();

    void on_deleteProductPos_clicked();


    void on_addOutletPos_clicked();

    void on_modifyOutletPos_clicked();

    void on_deleteOutletPos_clicked();

    void on_addCut_clicked();

    void on_modifyCut_clicked();

    void on_deleteCut_clicked();


private:
    QString PosDataToString(const QVariantList& data, bool noSubArm = false, const QString& dataName = "") const ;
    bool UsedMainArm() const;
    bool UsedSubArm() const;

    void AddPosHelper(QGridLayout* layout, QList<PosSpeedUIWidgets>& speedUI, const QString& posName);
    void DelPosHelper(int row, QGridLayout* layout, QList<PosSpeedUIWidgets>& speedUI, const QString& posName);
private:
    Ui::ICSimpleTeachPage *ui;
    QList<QVariantList> releasePosModelData;
    QList<QVariantList> releaseOutletModelData;
    QList<QVariantList> cutOutletModelData;
    QList<PosSpeedUIWidgets> releaseProductSpeedUI;
    QList<PosSpeedUIWidgets> releaseOutletSpeedUI;
    QList<PosSpeedUIWidgets> cutOutletSpeedUI;
    QIntValidator speedValidator_;


};

#endif // ICSIMPLETEACHPAGE_H
