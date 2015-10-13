#ifndef ICGUIDEFIXTUREEDITOR_H
#define ICGUIDEFIXTUREEDITOR_H

#include <QDialog>
#include <QMap>
#include <QSignalMapper>
class QAbstractButton;


namespace Ui {
class ICGuideFixtureEditor;
}

class ICGuideFixtureEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ICGuideFixtureEditor(QWidget *parent = 0);
    ~ICGuideFixtureEditor();

public slots:
    QList<QPair<int , bool> > GetConfigs() const;
    int ShowEditor(const QList<QPair<int , bool> >& fixturesConfigs );
    void CommandButtonClicked(QWidget* widget);
    QStringList SelectedNames() const;


protected:
    void changeEvent(QEvent *e);

private slots:
    void on_pushButton_clicked();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ICGuideFixtureEditor *ui;
    QStringList ioNames_;
    QVector<QAbstractButton*> settingButtons_;
    QMap<uint, uint> onClipToOffClip_;
    QMap<uint, uint> offClipToOnClip_;
    QMap<QAbstractButton*, uint> buttonToClip_;
    QMap<QAbstractButton*, QPair<int, int> > commandKeyMap_;
    QSignalMapper buttonSignalMapper_;
    QPixmap onPixmap_;
    QPixmap offPixmap_;
    QMap<int, int> clipToRow_;

};

#endif // ICGUIDEFIXTUREEDITOR_H
