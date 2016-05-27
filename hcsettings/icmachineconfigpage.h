#ifndef ICMACHINECONFIGPAGE_H
#define ICMACHINECONFIGPAGE_H

#include <QWidget>
#include <QMap>

class ICLineEditWrapper;

namespace Ui {
class ICMachineConfigPage;
}

class ICMachineConfigPage : public QWidget
{
    Q_OBJECT

public:
    explicit ICMachineConfigPage(QWidget *parent = 0);
    ~ICMachineConfigPage();

protected:
    void changeEvent(QEvent *e);
    void hideEvent(QHideEvent *e);
    void showEvent(QShowEvent *e);

private:
    void UpdateAxisDefine_();
    void ShowWidgets_(QList<QWidget*>& widgets);
    void HideWidgets_(QList<QWidget*>& widgets);
    Ui::ICMachineConfigPage *ui;
    QList<ICLineEditWrapper*> wrappers_;

    int axisDefine_;
    QList<QList<QWidget*> > axisWidgets_;

private slots:
    void on_xADEdit_textChanged(const QString &arg1);

    void on_yADEdit_textChanged(const QString &arg1);

    void on_zADEdit_textChanged(const QString &arg1);

    void on_x2ADEdit_textChanged(const QString &arg1);

    void on_y2ADEdit_textChanged(const QString &arg1);

    void on_bADEdit_textChanged(const QString &arg1);

    void on_aADEdit_textChanged(const QString &arg1);

    void on_cADEdit_textChanged(const QString &arg1);

    void on_xADEdit_2_textChanged(const QString &arg1);

    void on_yADEdit_2_textChanged(const QString &arg1);

    void on_zADEdit_2_textChanged(const QString &arg1);

    void on_x2ADEdit_2_textChanged(const QString &arg1);

    void on_y2ADEdit_2_textChanged(const QString &arg1);

    void on_aADEdit_2_textChanged(const QString &arg1);

    void on_bADEdit_2_textChanged(const QString &arg1);

    void on_cADEdit_2_textChanged(const QString &arg1);

private slots:
    void OnConfigChanged(QObject* w, const QString& newV, const QString& oldV);
    void OnConfigChanged(const QString& text);
    void OnConfigChanged(int v);
    void OnConfigChanged(int v, int ov);
    void OnConfigChanged(bool b);
private:
    QMap<QObject*, int> editorToConfigIDs_;
};

#endif // ICMACHINECONFIGPAGE_H
