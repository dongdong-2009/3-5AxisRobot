#ifndef ICHCPRODUCTSETTINGFRAME_H
#define ICHCPRODUCTSETTINGFRAME_H

#include <QFrame>
#include <QList>
#include <QButtonGroup>
class ICLineEditWrapper;

namespace Ui {
    class ICHCProductSettingFrame;
}

class ICHCProductSettingFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ICHCProductSettingFrame(QWidget *parent = 0);
    ~ICHCProductSettingFrame();

protected:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    void changeEvent(QEvent *e);

private slots:
    void OnMoldNumberParamChanged();

    void on_productClearButton_clicked();

    void FixtureBoxChange();
    void retranslateUi_();

    void on_countUnitBox_currentIndexChanged(int index);

    void on_getFailWay_activated(int index);

    void on_saveButton_clicked();

    void on_autoProductGroupBox_toggled(bool arg1);

    void OnProductMoldNameChanged(int index);
    void OnProductCountChanged(const QString& text);
    void OnProductClearClicked();

private:
    Ui::ICHCProductSettingFrame *ui;
    QList<ICLineEditWrapper*> wrappers_;
    QButtonGroup* buttongroup_ ;
    void InitCheckBox();

    QWidgetList mboxs_;
    QWidgetList pcEdits_;
    QWidgetList clearButtons_;
};

#endif // ICHCPRODUCTSETTINGFRAME_H
