INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    #$$PWD/basicsettingsframe.h \
    $$PWD/axissettingsframe.h \
    $$PWD/ichcsettingsframe.h \
    $$PWD/ichcstackedsettingsframe.h \
    $$PWD/ichctimeframe.h \
    $$PWD/ichcmovementframe.h \
    $$PWD/ichcdetectionframe.h \
    $$PWD/ichcproductsettingframe.h \
    $$PWD/ichcsystemsettingsframe.h \
    $$PWD/icmachineconfigpage.h \
    $$PWD/icadminpassworddialog.h \
    $$PWD/icstructdefineframe.h \
    $$PWD/icmachinestructpage.h \
    $$PWD/icmachinefigure.h

SOURCES += \
    #$$PWD/basicsettingsframe.cpp \
    $$PWD/axissettingsframe.cpp \
    $$PWD/ichcsettingsframe.cpp \
    $$PWD/ichcstackedsettingsframe.cpp \
    $$PWD/ichctimeframe.cpp \
    $$PWD/ichcmovementframe.cpp \
    $$PWD/ichcdetectionframe.cpp \
    $$PWD/ichcproductsettingframe.cpp \
    $$PWD/ichcsystemsettingsframe.cpp \
    $$PWD/icmachineconfigpage.cpp \
    $$PWD/icadminpassworddialog.cpp \
    $$PWD/icstructdefineframe.cpp \
    $$PWD/icmachinestructpage.cpp \
    $$PWD/icmachinefigure.cpp

FORMS += \
    #$$PWD/basicsettingsframe.ui \
#    $$PWD/axissettingsframe.ui \
    $$PWD/ichcsettingsframe.ui \
#    $$PWD/ichcstackedsettingsframe.ui \
    $$PWD/ichctimeframe.ui \
    $$PWD/ichcmovementframe.ui \
#    $$PWD/ichcdetectionframe.ui \
#    $$PWD/ichcproductsettingframe.ui \
#    $$PWD/ichcsystemsettingsframe.ui \
    $$PWD/icmachineconfigpage.ui \
    $$PWD/icadminpassworddialog.ui \
#    $$PWD/icstructdefineframe.ui \
#    $$PWD/icmachinestructpage.ui \
    $$PWD/icmachinefigure.ui \
#    $$PWD/ichcsystemsettingsframe_5.ui
#    $$PWD/icstructdefineframe_5.ui \
#    $$PWD/ichcstackedsettingsframe_5.ui \
#    $$PWD/ichcdetectionfram_5.ui
#    $$PWD/icmachinestructpage_5.ui
    $$PWD/ichctimeframe.ui



contains(DEFINES, HC_SK_8){
FORMS += $$PWD/icstructdefineframe.ui \
    $$PWD/ichcstackedsettingsframe.ui \
    $$PWD/ichcdetectionframe.ui \
    $$PWD/ichcsystemsettingsframe.ui \
     $$PWD/icmachinestructpage.ui \
    $$PWD/axissettingsframe.ui \
$$PWD/ichcproductsettingframe.ui
}
contains(DEFINES, HC_SK_5){
FORMS += $$PWD/icstructdefineframe_5.ui \
    $$PWD/ichcstackedsettingsframe_5.ui \
    $$PWD/ichcdetectionframe_5.ui \
    $$PWD/ichcsystemsettingsframe_5.ui \
    $$PWD/icmachinestructpage_5.ui \
    $$PWD/axissettingsframe_5.ui \
$$PWD/ichcproductsettingframe_5.ui
}

RESOURCES += \
    resource.qrc
