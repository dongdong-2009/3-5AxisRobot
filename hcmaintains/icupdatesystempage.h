#ifndef ICUpdateSystemPage_H
#define ICUpdateSystemPage_H

#include <QFrame>
#include <QTimer>
#include <QMap>
#include "icupdatepackmodel.h"
#include "icprogramheadframe.h"
#include "icupdatesystem.h"

namespace Ui {
    class ICUpdateSystemPage;
}

class QSettings;
class QPushButton;

class ICUpdateSystemPage : public QFrame {
    Q_OBJECT
public:
//    ICUpdateSystemPage(QWidget *parent = 0);
    static ICUpdateSystemPage * Instance(QWidget *parent = 0)
    {
        if(instance_ == NULL)
        {
            instance_ = new ICUpdateSystemPage(parent);
        }
        return instance_;
    }
    ~ICUpdateSystemPage();

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
signals:
//    void RegisterSucceed();
private:
    void InitInterface();

private:
    Ui::ICUpdateSystemPage *ui;
    static ICUpdateSystemPage * instance_;
    explicit ICUpdateSystemPage(QWidget *parent = 0);
    const QString updateIniPath_;
    QString updateHostPath_;
    QSettings *updateSettings_;
    QSettings *updateHostSettings_;
    QList<QPushButton*> restartBtns_;
    QMap<QWidget*, int> cycleEditorToItemIndex;
    QMap<QWidget*, int> restartBtnToItemIndex;

    QTimer timer_;
//    QTimer *refresh_restTimer;
    int status_;
    QDialog* updateDialog_;
//    QMap<int, int> hostStatusToStringMap_;
    bool connectHostFlag;

    QString fileName;
    ICUpdatePackModel* model_;
    ICUpdateSystem* updateSystem_;

    void updateHostButton();
    void writeHostButton();
    void rebootButton();
    void RestartAndUpdateTheProgram();
    bool CheckIsUsbAttached() const ;


private slots:
    void on_updateToolButton_clicked();
    void SystemUpdateStart();
    void RefreshUSBIniInfo();
    void QueryStatus();

    void on_connectHostButton_clicked();
    void on_updateLogoButton_clicked();
//    void on_registerBtn_clicked();
//    void RefreshRestTime();
    void on_updatePasswardButton_clicked();
    void on_scanPanel_clicked();
    void on_scanHost_clicked();

    void OnCycleEditorChanged(const QString& text);
    void OnRestartBtnClicked();

private slots:
    void OnConfigChanged(QObject* w, const QString& newV, const QString& oldV);
    void OnConfigChanged(const QString& text);
    void OnConfigChanged(int v);
    void OnConfigChanged(int v, int ov);
    void OnConfigChanged(bool b);
private:
    QMap<QObject*, int> editorToConfigIDs_;
};

//TODEBUG
//extern ICUpdateSystemPage *ICUpdateSystemPage;

#endif // ICUpdateSystemPage_H
