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

HostType = n

#DEFINES += HC_TEST
#DEFINES += Compatible6410
#DEFINES += HC_4F2S
#DEFINES += HC_10M
#DEFINES += X1_BAD_FUNC

DEFINES += HOST_TYPE='\\"$${HostType}\\"'

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

TRUNK_VERSION = 6.2.2
APP_VERSION = XS5
S_VERSION = $${APP_VERSION}_$${HostType}_$${TRUNK_VERSION}
contains(DEFINES, Compatible6410){
S_VERSION = $${S_VERSION}_cp6410
}
contains(DEFINES, HC_TEST){
S_VERSION = $${S_VERSION}_test
}
contains(DEFINES, HC_10M){
DEFINES += LENGTH_DEC=0
DEFINES += USE_DEC=1
S_VERSION = $${S_VERSION}_10M
}else{
DEFINES += LENGTH_DEC=1
DEFINES += USE_DEC=2
}

VERSTR = '\\"$${S_VERSION}\\"'
DEFINES += SHOW_VERSION=\"$${VERSTR}\"


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
    icbackupdialog.cpp \
    icconfigstring.cpp \
    iccaretipui.cpp
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
    icbackupdialog.h \
    icconfigstring.h \
    iccaretipui.h

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
    icbackupdialog.ui \
    iccaretipui.ui

equals(SK_SIZE, 8){
message("Define 8")
DEFINES += HC_SK_8
FORMS    += mainframe.ui
RESOURCES += backupfor8.qrc
}
equals(SK_SIZE ,5){
message("Define 5")
DEFINES += HC_SK_5
FORMS    += mainframe_5.ui
RESOURCES += backupfor5.qrc

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
    Multi-axisManipulatorSystem_pt.ts \
    Multi-axisManipulatorSystem_esp.ts \
    Multi-axisManipulatorSystem_nl.ts \
    Multi-axisManipulatorSystem_fr.ts \
    Multi-axisManipulatorSystem_kr.ts \
    Multi-axisManipulatorSystem_hk.ts \
    Multi-axisManipulatorSystem_it.ts \
    Multi-axisManipulatorSystem_pl.ts \
    Multi-axisManipulatorSystem_tr.ts


QMAKE_POST_LINK += "cp *.qm $$DESTDIR"
QMAKE_PRE_LINK += "lrelease $${TARGET}.pro"
#message($${UI_DIR})
system("python rename_ui.py $${UI_DIR}")
contains(QMAKE_CXX, g++){
#QMAKE_POST_LINK += "cp *.qm bin_debug"
}else{
#system("python rename_ui.py temp_$${SK_SIZE}")
unix:QMAKE_POST_LINK += " && arm-linux-gnueabihf-strip $$DESTDIR/$$TARGET"
unix:QMAKE_POST_LINK += " && HCbcrypt.sh -r $$DESTDIR/$$TARGET"
unix:QMAKE_POST_LINK += "&& chmod +x tools/make_target && tools/make_target $$PWD $$DESTDIR $${HostType} $${S_VERSION}"
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
others.files += $${configsPathBase}/*.qm
scripts.path = /usr/bin
scripts.files += $${configsPathBase}/$${SK_SIZE}RunApp/*
keymap.path = /home/root
keymap.files =$${configsPathBase}/$${SK_SIZE}-inch-qmap/*
testApp.path = /opt/Qt/apps
testApp.files += $${configsPathBase}/3a8HardwareTest-$${SK_SIZE}-inch
testApp.files += $${configsPathBase}/3A8HardwareTest.en_CH.qm
INSTALLS += target translations records subs sysconfig resource stylesheet others scripts keymap testApp
for(sh, scripts.files){
QMAKE_POST_LINK += " && chmod +x $${sh}"
}
message($$QMAKE_POST_LINK)
}
