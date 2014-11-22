#ifndef ICMSSETTINGSPAGE_H
#define ICMSSETTINGSPAGE_H

#include <QWidget>

namespace Ui {
class ICMSSettingsPage;
}

class ICLineEditWrapper;

class ICMSSettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ICMSSettingsPage(QWidget *parent = 0);
    ~ICMSSettingsPage();

protected:
    void changeEvent(QEvent *e);
    void hideEvent(QHideEvent* e);

private:
    Ui::ICMSSettingsPage *ui;
    QList<ICLineEditWrapper*> wrappers_;
};

#endif // ICMSSETTINGSPAGE_H
