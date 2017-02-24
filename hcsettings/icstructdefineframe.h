#ifndef ICSTRUCTDEFINEFRAME_H
#define ICSTRUCTDEFINEFRAME_H

#include <QWidget>
#include <QMap>
#include <QButtonGroup>

class QComboBox;
namespace Ui {
    class ICStructDefineFrame;
}

class ICStructDefineFrame : public QWidget
{
    Q_OBJECT

public:
    explicit ICStructDefineFrame(QWidget *parent = 0);
    ~ICStructDefineFrame();


protected:
    void changeEvent(QEvent *e);
signals:
    void StructChanged();

private slots:
    void on_saveButton_clicked();

    void on_doubleArmButton_toggled(bool checked);


    void on_mainArmDownLimitButton_toggled(bool checked);

    void on_mainArmBackwardLimitButton_toggled(bool checked);

    void on_mainArmForwardLimitButton_toggled(bool checked);

    void on_subArmDownLimitButton_toggled(bool checked);

    void on_subArmBackwardLimitButton_toggled(bool checked);

    void on_subArmForwardLimitButton_toggled(bool checked);
    void escapeBoxChange();

    void OnAxisDefineChanged(int index);
    void OnOutputDefineChanged(int index);

    void retranslateUi_();

    void on_adjUse_toggled(bool checked);
    void on_fixtureComboBox_currentIndexChanged(int index);

private:
    Ui::ICStructDefineFrame *ui;
    uint armStruct_;
    int axisDefine_;
    int outDefine_;
    QMap<int, int> armDefineToIndex_;
    QMap<QComboBox*, int> boxToAxis_;
    QMap<int, int> indexToArmDefine_;
    QMap<QButtonGroup*, int> outputDefineToNumber_;
    QList<QButtonGroup*>buttongrouplist ;
    QButtonGroup* buttongroup_ ;

    QList<QList<QAbstractButton*> >buttonslist_ ;
    void InitEscapeBox() ;

private slots:
    void OnConfigChanged(QObject* w, const QString& newV, const QString& oldV);
    void OnConfigChanged(const QString& text);
    void OnConfigChanged(int v);
    void OnConfigChanged(int v, int ov);
    void OnConfigChanged(bool b);
    void on_originButton_clicked();

private:
    QMap<QObject*, int> editorToConfigIDs_;

};

#endif // ICSTRUCTDEFINEFRAME_H
