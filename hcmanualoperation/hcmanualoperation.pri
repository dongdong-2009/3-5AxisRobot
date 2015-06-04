INCLUDEPATH += $$PWD

HEADERS += \
    hcmanualoperation/ichcmanualoperationpageframe.h \
    #hcmanualoperation/hcmanualalternateioframe.h \
    hcmanualoperation/hcmanualfixtureframe.h \
    hcmanualoperation/hcmanualsockerframe.h \
    #hcmanualoperation/hcpneumaticaxiscontrolframe.h \
    hcmanualoperation/hcservoarmcontrolframe.h \
    #hcmanualoperation/hcmanualfunctionframe.h \
    hcmanualoperation/hcmanualotherioframe.h \
    hcmanualoperation/hcmanualadjustframe.h \
    hcmanualoperation/hcmanualreservepage.h

SOURCES += \
    hcmanualoperation/ichcmanualoperationpageframe.cpp \
    #hcmanualoperation/hcmanualalternateioframe.cpp \
    hcmanualoperation/hcmanualfixtureframe.cpp \
    hcmanualoperation/hcmanualsockerframe.cpp \
    #hcmanualoperation/hcpneumaticaxiscontrolframe.cpp \
    hcmanualoperation/hcservoarmcontrolframe.cpp \
    #hcmanualoperation/hcmanualfunctionframe.cpp \
    hcmanualoperation/hcmanualotherioframe.cpp \
    hcmanualoperation/hcmanualadjustframe.cpp \
    hcmanualoperation/hcmanualreservepage.cpp

contains(DEFINES, HC_SK_8){
FORMS += \
    $$PWD/hcmanualadjustframe.ui \
    $$PWD/ichcmanualoperationpageframe.ui
}

contains(DEFINES, HC_SK_5){
FORMS += \
    $$PWD/hcmanualadjustframe_5.ui \
    $$PWD/ichcmanualoperationpageframe_5.ui
}

FORMS += \
    #hcmanualoperation/hcmanualalternateioframe.ui \
    hcmanualoperation/hcmanualfixtureframe.ui \
    hcmanualoperation/hcmanualsockerframe.ui \
    #hcmanualoperation/hcpneumaticaxiscontrolframe.ui \
    hcmanualoperation/hcservoarmcontrolframe.ui \
    #hcmanualoperation/hcmanualfunctionframe.ui \
    hcmanualoperation/hcmanualotherioframe.ui \
    hcmanualoperation/hcmanualreservepage.ui
