INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include (icpagetag/icpagetag.pri)
include (icpageswitch/icpageswitch.pri)
include (systemstatusframe/systemstatusframe.pri)
include (icpagetab/icpagetab.pri)
include (iciomonitor/iciomonitor.pri)
include (icframe/icframe.pri)
#include (axisrunningstatus/axisrunningstatus.pri)
include (iccommunicationwidget/iccommunicationwidget.pri)
#include (iclabelwrapper/iclabelwrapper.pri)
include (lineeditwithvirtualnumerickeypad/lineeditwithvirtualnumerickeypad.pri)
include (lineeditwithvirtualkeyboard/lineeditwithvirtualkeyboard.pri)
include (cycletimeandfinished/cycletimeandfinished.pri)
include (programhead/programhead.pri)
#include (currentchildpagename/currentchildpagename.pri)
#include (icaxispositionlabelwrapper/icaxispositionlabelwrapper.pri)
include (ictwoselectioncomboboxwrapper/ictwoselectioncomboboxwrapper.pri)
include (iclineeditwrapper/iclineeditwrapper.pri)
include (iccommandkeywrapper/iccommandkeywrapper.pri)
include (iciopointwrapper/iciopointwrapper.pri)
include (icpictureview/icpictureview.pri)

HEADERS += \
    custom_widgets/ictableview.h \
    custom_widgets/ictablewidget.h \
    custom_widgets/icpasswordmodifydialog.h \
    custom_widgets/iccombobox.h

SOURCES += \
    custom_widgets/ictableview.cpp \
    custom_widgets/ictablewidget.cpp \
    custom_widgets/icpasswordmodifydialog.cpp \
    custom_widgets/iccombobox.cpp

FORMS += \
    custom_widgets/icpasswordmodifydialog.ui
