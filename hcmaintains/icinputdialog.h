#ifndef ICINPUTDIALOG_H
#define ICINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class ICInputDialog;
}

class ICInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ICInputDialog(QWidget *parent = 0);

    static QString getText ( QWidget * parent, const QString & title, const QString & label);
    void setLabelText ( const QString & text );
    QString	textValue () const;
    ~ICInputDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ICInputDialog *ui;
};

#endif // ICINPUTDIALOG_H
