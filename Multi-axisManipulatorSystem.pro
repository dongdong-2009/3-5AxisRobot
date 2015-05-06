# -------------------------------------------------
# Project created by QtCreator 2010-11-30T13:47:10
# -------------------------------------------------
TARGET = Multi-axisManipulatorSystem
TEMPLATE = app
QMAKE_CFLAGS += -std=c99

QMAKE_CXX = ccache $${QMAKE_CXX}

suffix = $${member(QMAKE_CXX, 1)}
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

#CONFIG(debug, debug|release) {
##    LIBS += -lprofiler
#DESTDIR = bin_debug
#OBJECTS_DIR = temp_8_d
#UI_DIR = temp_8_d
#MOC_DIR = temp_8_d
#RCC_DIR = temp_8_d
#}
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
    ictimerpool.cpp \
    ichostcomparepage.cpp \
    icbackuputility.cpp \
    ictipswidget.cpp \
    icdataformatchecker.cpp \
    icprogramformatchecker.cpp \
    icconfigformatchecker.cpp \
    simulateknob.cpp
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
    ictimerpool.h \
    ichostcomparepage.h \
    icbackuputility.h \
    ictipswidget.h \
    icdataformatchecker.h \
    icprogramformatchecker.h \
    icconfigformatchecker.h \
    simulateknob.h \
    ICHacker.h

FORMS    +=  \
    #icalarmdescriptiondialog.ui \
    icorigindialog.ui \
    icreturnpage.ui \
    icscreensaver.ui \
    icactiondialog.ui \
    ichostcomparepage.ui \
    ictipswidget.ui \
    simulateknob.ui \


SK_SIZE = 8
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

include (categorypage/categorypage.pri)
include (custom_widgets/custom_widgets.pri)
include (function_settings/function_settings.pri)
#include (manual_operation/manual_operation.pri)
include (communication/communication.pri)

include (hcmanualoperation/hcmanualoperation.pri)
include (hcsettings/hcsettings.pri)
include (hcinstruction/hcinstruction.pri)
include (ickeyboard/ickeyboard.pri)
include (hcmaintains/hcmaintains.pri)

RESOURCES += \
    resource.qrc \
    initconfig.qrc

TRANSLATIONS += Multi-axisManipulatorSystem_ch.ts \
    Multi-axisManipulatorSystem_en.ts \
    Multi-axisManipulatorSystem_pt.ts \
    Multi-axisManipulatorSystem_ru.ts

OTHER_FILES += \
    sysconfig/alarminfomation-en \
    sysconfig/alarminfomation-ch \
    sysconfig/alarminfomation-pt \
    sysconfig/alarminfomation-ru \
    sysconfig/hintinfomation-ch \
    sysconfig/hintinfomation-en \
    sysconfig/hintinfomation-pt \
    sysconfig/hintinfomation-ru

QMAKE_POST_LINK += "cp *.qm $$DESTDIR"
system("python rename_ui.py temp_$${suffix}")
#QMAKE_POST_LINK += "cp *.qm bin_debug"
CONFIG(debug, debug|release){
}else{
#system("python rename_ui.py temp_8")
unix:QMAKE_POST_LINK += "&& arm-linux-strip $$DESTDIR/$$TARGET && HCbcrypt.sh -r $$DESTDIR/$$TARGET"
}
