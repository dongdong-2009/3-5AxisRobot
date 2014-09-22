#ifndef ICMSSETTINGSPAGE_H
#define ICMSSETTINGSPAGE_H

#include <QWidget>

namespace Ui {
class ICMSSettingsPage;
}

class ICMSSettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ICMSSettingsPage(QWidget *parent = 0);
    ~ICMSSettingsPage();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ICMSSettingsPage *ui;
};

#endif // ICMSSETTINGSPAGE_H
