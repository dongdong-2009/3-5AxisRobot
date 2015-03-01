#ifndef ICHACKER_H
#define ICHACKER_H

#ifndef Q_WS_QWS
#include <QWidgetList>
static void DeepSetWidgetToolStatus(QWidget* w)
{
    QWidgetList wl = w->findChildren<QWidget*>();
    for(int i = 0 ; i != wl.size(); ++i)
    {
        wl[i]->setToolTip(wl[i]->objectName());
        DeepSetWidgetToolStatus(wl[i]);
    }
}
#endif

#endif // ICHACKER_H
