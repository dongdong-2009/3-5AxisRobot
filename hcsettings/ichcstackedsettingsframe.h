#ifndef ICHCSTACKEDSETTINGSFRAME_H
#define ICHCSTACKEDSETTINGSFRAME_H

#include <QFrame>
#include <QMap>

namespace Ui {
    class ICHCStackedSettingsFrame;
}

class ICHCStackedSettingsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ICHCStackedSettingsFrame(QWidget *parent = 0);
    ~ICHCStackedSettingsFrame();

signals:
    void configChanged();
protected:
    void hideEvent(QHideEvent *e);
    void changeEvent(QEvent *e);

private:
    Ui::ICHCStackedSettingsFrame *ui;

private slots:
    void on_page0ToolButton_clicked();
    void on_page1ToolButton_clicked();
    void on_page2ToolButton_clicked();
    void on_page3ToolButton_clicked();
    void OnMoldNumberParamChanged();

    void on_xUnit_toggled(bool checked);

    void on_yUnit_toggled(bool checked);

    void on_zUnit_toggled(bool checked);

    void on_xRPStepLineEdit_textChanged(const QString &arg1);

    void on_yRPStepLineEdit_textChanged(const QString &arg1);

    void on_zRPStepLineEdit_textChanged(const QString &arg1);

private:
    void InitInterface();
    QList<int> GetCurrentStatus_() const;
    void SetStackStatus_(const QList<int> & status);
    void RefreshStackParams_(int group);
    int currentPage_;
private slots:
    void OnConfigChanged(QObject* w, const QString& newV, const QString& oldV);
    void OnConfigChanged(const QString& text);
    void OnConfigChanged(int v);
    void OnConfigChanged(int v, int ov);
    void OnConfigChanged(bool b);
    void on_okButton_clicked();

private:
    QMap<QObject*, int> editorToConfigIDs_;
};

#endif // ICHCSTACKEDSETTINGSFRAME_H
