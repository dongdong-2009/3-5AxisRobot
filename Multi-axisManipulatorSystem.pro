# -------------------------------------------------
# Project created by QtCreator 2010-11-30T13:47:10
# -------------------------------------------------
TARGET = Multi-axisManipulatorSystem
TEMPLATE = app
QMAKE_CFLAGS += -std=c99

QT += sql

SK_SIZE = 5

OBJECTS_DIR = temp_$${SK_SIZE}
UI_DIR = temp_$${SK_SIZE}
MOC_DIR = temp_$${SK_SIZE}
RCC_DIR = temp_$${SK_SIZE}
DESTDIR = bin
CONFIG(debug, debug|release) {
#    LIBS += -lprofiler
DESTDIR = bin_debug
OBJECTS_DIR = temp_$${SK_SIZE}_d
UI_DIR = temp_$${SK_SIZE}_d
MOC_DIR = temp_$${SK_SIZE}_d
RCC_DIR = temp_$${SK_SIZE}_d
#LIBS += -L/vendor/icframework/libs_debug -liccore
}
#INCLUDEPATH += vendor/ICCustomWidgets/include
#INCLUDEPATH += vendor/IndustrialSystemFramework/include
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
    icfile.cpp \
    icbackupdialog.cpp
HEADERS += icaxispositionlabel.h \
    mainframe.h \
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
    icfile.h \
    icbackupdialog.h

FORMS    +=  \
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

equals(SK_SIZE, 8){
message("Define 8")
DEFINES += HC_SK_8
FORMS    += mainframe.ui
}
equals(SK_SIZE ,5){
message("Define 5")
DEFINES += HC_SK_5
FORMS    += mainframe_5.ui
}


#其他页面有修改则在pri文件中添加以下（分HC_SK_5和HC_SK_8）
#contains(DEFINES, HC_SK_8){
#HEADERS += mainframe.h
#SOURCES += mainframe.cpp
#FORMS += mainframe.ui
#}

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
    sysconfig/hintinfomation-ch \
    sysconfig/hintinfomation-en

QMAKE_POST_LINK += "cp *.qm $$DESTDIR"
CONFIG(debug, debug|release){
system("python rename_ui.py temp_$${SK_SIZE}_d")
#QMAKE_POST_LINK += "cp *.qm bin_debug"
}else{
system("python rename_ui.py temp_$${SK_SIZE}")
QMAKE_POST_LINK += "&& arm-linux-strip $$DESTDIR/$$TARGET && HCbcrypt.sh -r $$DESTDIR/$$TARGET"
QMAKE_POST_LINK += " && tools/make_target"
}
