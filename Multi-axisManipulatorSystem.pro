# -------------------------------------------------
# Project created by QtCreator 2010-11-30T13:47:10
# -------------------------------------------------
TARGET = Multi-axisManipulatorSystem
TEMPLATE = app
QMAKE_CFLAGS += -std=c99

QMAKE_CXX = ccache $${QMAKE_CXX}
QMAKE_STRIP = $${member(QMAKE_CXX, 1)}
message($$QMAKE_STRIP)
QMAKE_STRIP = $${replace(QMAKE_STRIP, -g++, -strip)}
message($$QMAKE_STRIP)


QT += sql

SK_SIZE = 8

suffix = Size$${SK_SIZE}
CONFIG(debug, debug|release) {
suffix = $${suffix}_debug
}
else{
suffix = $${suffix}_release
}
DESTDIR = bin_$${suffix}
OBJECTS_DIR = temp_$${suffix}
UI_DIR = temp_$${suffix}
MOC_DIR = temp_$${suffix}
RCC_DIR = temp_$${suffix}

win32{INCLUDEPATH += ./}
SOURCES += main.cpp \
    mainframe.cpp \
    icaxispositionlabel.cpp \
    #icalarmdescriptiondialog.cpp \
    icsystemconfig.cpp \
    icparameterssave.cpp \
    icalarmstring.cpp \
    icsplashscreen.cpp \
    icorigindialog.cpp \
    icreturnpage.cpp \
    icscreensaver.cpp \
    icactiondialog.cpp \
    ichostcomparepage.cpp \
    icbackuputility.cpp \
    ictipswidget.cpp \
    icdataformatchecker.cpp \
    icprogramformatchecker.cpp \
    icconfigformatchecker.cpp \
    simulateknob.cpp \
    icrecaldialog.cpp \
    icbackupdialog.cpp \
    icfile.cpp
HEADERS += mainframe.h \
    icaxispositionlabel.h \
    #icalarmdescriptiondialog.h \
    icsystemconfig.h \
    icparameterssave.h \
    icalarmstring.h \
    icsplashscreen.h \
    icorigindialog.h \
    icreturnpage.h \
    icscreensaver.h \
    config.h \
    icactiondialog.h \
    ichostcomparepage.h \
    icbackuputility.h \
    ictipswidget.h \
    icdataformatchecker.h \
    icprogramformatchecker.h \
    icconfigformatchecker.h \
    simulateknob.h \
    icrecaldialog.h \
    icbackupdialog.h \
    icfile.h

FORMS    += mainframe.ui \
    #icalarmdescriptiondialog.ui \
    icorigindialog.ui \
    icreturnpage.ui \
    icscreensaver.ui \
    icactiondialog.ui \
    ichostcomparepage.ui \
    ictipswidget.ui \
    simulateknob.ui \
    icrecaldialog.ui \
    icbackupdialog.ui

include (./categorypage/categorypage.pri)
include (custom_widgets/custom_widgets.pri)
include (function_settings/function_settings.pri)
#include (manual_operation/manual_operation.pri)
include (communication/communication.pri)

include (hcmanualoperation/hcmanualoperation.pri)
include (hcsettings/hcsettings.pri)
include (hcinstruction/hcinstruction.pri)
include (ickeyboard/ickeyboard.pri)
include (hcmaintains/hcmaintains.pri)

include (vendor/IndustrialSystemFramework/ICUtility/ICUtility.pri)
include (vendor/IndustrialSystemFramework/ICGUI/ICGUI.pri)
include (vendor/ICCustomWidgets/icupdatepackmodel/icupdatepackmodel.pri)

RESOURCES += \
    resource.qrc \
    initconfig.qrc

TRANSLATIONS += Multi-axisManipulatorSystem_ch.ts \
    Multi-axisManipulatorSystem_en.ts

OTHER_FILES += \
    sysconfig/alarminfomation-en \
    sysconfig/alarminfomation-ch \
    sysconfig/hintinfomation-ch \
    sysconfig/hintinfomation-en

QMAKE_POST_LINK += "cp *.qm $$DESTDIR"
CONFIG(debug, debug|release){
#system("python rename_ui.py temp_8_d")
#QMAKE_POST_LINK += "cp *.qm bin_debug"
}else{
#system("python rename_ui.py temp_8")
QMAKE_POST_LINK += "&& arm-linux-strip $$DESTDIR/$$TARGET && HCbcrypt.sh -r $$DESTDIR/$$TARGET"
}

