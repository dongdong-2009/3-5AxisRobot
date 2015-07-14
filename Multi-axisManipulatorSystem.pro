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
    Multi-axisManipulatorSystem_en.ts \
Multi-axisManipulatorSystem_pt.ts

OTHER_FILES += \
    sysconfig/alarminfomation-en \
    sysconfig/alarminfomation-ch \
    sysconfig/alarminfomation-pt \
    sysconfig/hintinfomation-ch \
    sysconfig/hintinfomation-en \
    sysconfig/hintinfomation-pt \


QMAKE_POST_LINK += "cp *.qm $$DESTDIR"
QMAKE_PRE_LINK += "lrelease $${TARGET}.pro"
#message($${UI_DIR})
system("python rename_ui.py $${UI_DIR}")
contains(QMAKE_CXX, g++){
#QMAKE_POST_LINK += "cp *.qm bin_debug"
}else{
#system("python rename_ui.py temp_$${SK_SIZE}")
unix:QMAKE_POST_LINK += " && HCbcrypt.sh -r $$DESTDIR/$$TARGET"
unix:QMAKE_POST_LINK += "&& chmod +x tools/make_target && tools/make_target $$PWD $$DESTDIR"
target.path = /opt/Qt/apps
configsPathBase = tools/Reinstall
translations.path = $${target.path}
translations.files = *.qm
records.path = /opt/Qt/apps/records
records.files += $${configsPathBase}/$${SK_SIZE}records/*
subs.path = /opt/Qt/apps/subs
subs.files += $${configsPathBase}/subs/*
sysconfig.path = /opt/Qt/apps/sysconfig
sysconfig.files += $${configsPathBase}/$${SK_SIZE}sysconfig/*
resource.path = /opt/Qt/apps/resource
resource.files += $${configsPathBase}/$${SK_SIZE}resource/*
stylesheet.path = /opt/Qt/apps/stylesheet
stylesheet.files += $${configsPathBase}/stylesheet/*
others.path = /opt/Qt/apps
others.files += $${configsPathBase}/3-5AxisRobotDatabase
scripts.path = /usr/bin
scripts.files += $${configsPathBase}/*.sh
scripts.files += $${configsPathBase}/LedTest_335x
scripts.files += $${configsPathBase}/$${SK_SIZE}RunApp/*
keymap.path = /home/root
keymap.files =$${configsPathBase}/$${SK_SIZE}-inch-qmap/*
INSTALLS += target translations records subs sysconfig resource stylesheet others scripts keymap
for(sh, scripts.files){
QMAKE_POST_LINK += " && chmod +x $${sh}"
}
message($$QMAKE_POST_LINK)
}
