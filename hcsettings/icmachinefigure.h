#ifndef ICMACHINEFIGURE_H
#define ICMACHINEFIGURE_H

#include <QWidget>
#include <QMap>

class ICLineEditWrapper;

class QIntValidator;

namespace Ui {
class ICMachineFigure;
}

class ICMachineFigure : public QWidget
{
    Q_OBJECT
    
public:
    explicit ICMachineFigure(QWidget *parent = 0);
    ~ICMachineFigure();
    
protected:
    void changeEvent(QEvent *e);
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    
//private slots:
//    void on_saveButton_clicked();

private:
    Ui::ICMachineFigure *ui;
    QList<ICLineEditWrapper*> wrappers_;

private slots:
    void OnConfigChanged(QObject* w, const QString& newV, const QString& oldV);
    void OnConfigChanged(const QString& text);
    void OnConfigChanged(int v);
    void OnConfigChanged(int v, int ov);
    void OnConfigChanged(bool b);
private:
    QMap<QObject*, int> editorToConfigIDs_;
    QIntValidator * validator;
};

#endif // ICMACHINEFIGURE_H
