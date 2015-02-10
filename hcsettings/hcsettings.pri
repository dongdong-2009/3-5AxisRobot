INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    #hcsettings/basicsettingsframe.h \
    hcsettings/axissettingsframe.h \
    hcsettings/ichcsettingsframe.h \
    hcsettings/ichcstackedsettingsframe.h \
    hcsettings/ichctimeframe.h \
    hcsettings/ichcdetectionframe.h \
    hcsettings/ichcproductsettingframe.h \
    hcsettings/ichcsystemsettingsframe.h \
    hcsettings/icmachineconfigpage.h \
    hcsettings/icadminpassworddialog.h \
    hcsettings/icstructdefineframe.h \
    hcsettings/icmachinestructpage.h \
    hcsettings/icmachinefigure.h

SOURCES += \
    #hcsettings/basicsettingsframe.cpp \
    hcsettings/axissettingsframe.cpp \
    hcsettings/ichcsettingsframe.cpp \
    hcsettings/ichcstackedsettingsframe.cpp \
    hcsettings/ichctimeframe.cpp \
    hcsettings/ichcdetectionframe.cpp \
    hcsettings/ichcproductsettingframe.cpp \
    hcsettings/ichcsystemsettingsframe.cpp \
    hcsettings/icmachineconfigpage.cpp \
    hcsettings/icadminpassworddialog.cpp \
    hcsettings/icstructdefineframe.cpp \
    hcsettings/icmachinestructpage.cpp \
    hcsettings/icmachinefigure.cpp

FORMS += \
    #hcsettings/basicsettingsframe.ui \
#    hcsettings/axissettingsframe.ui \
    hcsettings/ichcsettingsframe.ui \
#    hcsettings/ichcstackedsettingsframe.ui \
    hcsettings/ichctimeframe.ui \
#    hcsettings/ichcdetectionframe.ui \
#    hcsettings/ichcproductsettingframe.ui \
#    hcsettings/ichcsystemsettingsframe.ui \
    hcsettings/icmachineconfigpage.ui \
    hcsettings/icadminpassworddialog.ui \
#    hcsettings/icstructdefineframe.ui \
#    hcsettings/icmachinestructpage.ui \
    hcsettings/icmachinefigure.ui \
#    hcsettings/ichcsystemsettingsframe_5.ui
#    hcsettings/icstructdefineframe_5.ui \
#    hcsettings/ichcstackedsettingsframe_5.ui \
#    hcsettings/ichcdetectionfram_5.ui
#    hcsettings/icmachinestructpage_5.ui
    hcsettings/ichctimeframe_5.ui



contains(DEFINES, HC_SK_8){
FORMS += hcsettings/icstructdefineframe.ui \
    hcsettings/ichcstackedsettingsframe.ui \
    hcsettings/ichcdetectionframe.ui \
    hcsettings/ichcsystemsettingsframe.ui \
     hcsettings/icmachinestructpage.ui \
    hcsettings/axissettingsframe.ui \
hcsettings/ichcproductsettingframe.ui
}
contains(DEFINES, HC_SK_5){
FORMS += hcsettings/icstructdefineframe_5.ui \
    hcsettings/ichcstackedsettingsframe_5.ui \
    hcsettings/ichcdetectionframe_5.ui \
    hcsettings/ichcsystemsettingsframe_5.ui \
    hcsettings/icmachinestructpage_5.ui \
    hcsettings/axissettingsframe_5.ui \
hcsettings/ichcproductsettingframe_5.ui
}

RESOURCES += \
    resource.qrc
