#ifndef ICSIMPLETEACHPAGE_H
#define ICSIMPLETEACHPAGE_H

#include <QWidget>

namespace Ui {
    class ICSimpleTeachPage;
}

class ICSimpleTeachPage : public QWidget
{
    Q_OBJECT

public:
    explicit ICSimpleTeachPage(QWidget *parent = 0);
    ~ICSimpleTeachPage();

private:
    Ui::ICSimpleTeachPage *ui;
};

#endif // ICSIMPLETEACHPAGE_H
