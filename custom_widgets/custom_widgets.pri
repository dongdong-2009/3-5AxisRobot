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
    $$PWD/iclistwidget.h \
    $$PWD/ictablewidget.h \
    $$PWD/ictableview.h \
    $$PWD/icmessagebox.h \
    $$PWD/iccombobox.h \
    $$PWD/icpasswordmodifydialog.h \
    $$PWD/icplaintextedit.h \
    $$PWD/icinputmethodkeyboard.h \
    custom_widgets/icbuttongroup.h

SOURCES += \
    $$PWD/iclistwidget.cpp \
    $$PWD/ictablewidget.cpp \
    $$PWD/ictableview.cpp \
    $$PWD/icmessagebox.cpp \
    $$PWD/iccombobox.cpp \
    $$PWD/icpasswordmodifydialog.cpp \
    $$PWD/icplaintextedit.cpp \
    $$PWD/icinputmethodkeyboard.cpp \
    custom_widgets/icbuttongroup.cpp


contains(DEFINES, HC_SK_8){
FORMS += $$PWD/icinputmethodkeyboard.ui
}
contains(DEFINES, HC_SK_5){
FORMS += $$PWD/icinputmethodkeyboard_5.ui
}

FORMS += \
    $$PWD/icpasswordmodifydialog.ui
