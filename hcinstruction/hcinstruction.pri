INCLUDEPATH += $$PWD

HEADERS += \
    hcinstruction/ichcinstructionpageframe.h \
    hcinstruction/actionsettingframe.h \
    #hcinstruction/ichcparametersframe.h \
    #hcinstruction/routesettingdialog.h \
    hcinstruction/ichcinjectionpage.h \
    hcinstruction/ichcfixturepage.h \
    hcinstruction/ichcconditionpage.h \
    hcinstruction/icmold.h \
    hcinstruction/icmacrosubroutine.h \
    hcinstruction/icinstructparam.h \
    hcinstruction/ichcprogrammonitorframe.h \
    #hcinstruction/ichceditordialog.h \
    #hcinstruction/icmacroparameditorframe.h \
    hcinstruction/icautorunrevise.h \
    hcinstruction/icinstructioneditorbase.h \
    hcinstruction/icflagseditor.h \
    hcinstruction/icpneumaticactionpage.h \
    hcinstruction/icinstructmodifydialog.h \
    hcinstruction/icwaitconditioneditor.h \
    hcinstruction/icperipherypage.h \
    hcinstruction/icperipheryparametereditor.h \
    hcinstruction/iccutpage.h \
    hcinstruction/icprogramselector.h \
    hcinstruction/icstackeditor.h \
    hcinstruction/icprogramguidepage.h \
    hcinstruction/ichcotherpage.h

SOURCES += \
    hcinstruction/ichcinstructionpageframe.cpp \
    hcinstruction/actionsettingframe.cpp \
    #hcinstruction/ichcparametersframe.cpp \
    #hcinstruction/routesettingdialog.cpp \
    hcinstruction/ichcinjectionpage.cpp \
    hcinstruction/ichcfixturepage.cpp \
    hcinstruction/ichcconditionpage.cpp \
    hcinstruction/icmold.cpp \
    hcinstruction/icmacrosubroutine.cpp \
    hcinstruction/icinstructparam.cpp \
    hcinstruction/ichcprogrammonitorframe.cpp \
    #hcinstruction/ichceditordialog.cpp \
    #hcinstruction/icmacroparameditorframe.cpp \
    hcinstruction/icautorunrevise.cpp \
    hcinstruction/icinstructioneditorbase.cpp \
    hcinstruction/icflagseditor.cpp \
    hcinstruction/icpneumaticactionpage.cpp \
    hcinstruction/icinstructmodifydialog.cpp \
    hcinstruction/icwaitconditioneditor.cpp \
    hcinstruction/icperipherypage.cpp \
    hcinstruction/icperipheryparametereditor.cpp \
    hcinstruction/iccutpage.cpp \
    hcinstruction/icprogramselector.cpp \
    hcinstruction/icstackeditor.cpp \
    hcinstruction/icprogramguidepage.cpp \
    hcinstruction/ichcotherpage.cpp

FORMS += \
#    hcinstruction/ichcinstructionpageframe.ui \
    #hcinstruction/ichcparametersframe.ui \
    #hcinstruction/routesettingdialog.ui \
#    hcinstruction/ichcinjectionpage.ui \
#    hcinstruction/actionsettingframe.ui \
#    hcinstruction/ichcfixturepage.ui \
#    hcinstruction/ichcconditionpage.ui \
#    hcinstruction/ichcprogrammonitorframe.ui \
    #hcinstruction/ichceditordialog.ui \
    #hcinstruction/icmacroparameditorframe.ui \
    hcinstruction/icautorunrevise.ui \
    hcinstruction/icinstructioneditorbase.ui \
    hcinstruction/icflagseditor.ui \
#    hcinstruction/icpneumaticactionpage.ui \
#    hcinstruction/icinstructmodifydialog.ui \
#    hcinstruction/icwaitconditioneditor.ui \
    hcinstruction/icperipherypage.ui \
#    hcinstruction/icperipheryparametereditor.ui \
#    hcinstruction/iccutpage.ui \
    hcinstruction/icprogramselector.ui \
    hcinstruction/icstackeditor.ui \
#    hcinstruction/icprogramguidepage.ui \
    hcinstruction/ichcotherpage.ui



#    hcinstruction/ichcinstructionpageframe_5.ui


contains(DEFINES, HC_SK_8){
FORMS += hcinstruction/ichcinstructionpageframe.ui \
    hcinstruction/icwaitconditioneditor.ui \
    hcinstruction/icprogramguidepage.ui \
    hcinstruction/icpneumaticactionpage.ui \
    hcinstruction/icperipheryparametereditor.ui \
    hcinstruction/ichcinjectionpage.ui \
    hcinstruction/ichcfixturepage.ui \
    hcinstruction/ichcconditionpage.ui \
    hcinstruction/iccutpage.ui \
    hcinstruction/actionsettingframe.ui \
    hcinstruction/ichcprogrammonitorframe.ui \
    hcinstruction/icinstructmodifydialog.ui
}
contains(DEFINES, HC_SK_5){
FORMS += hcinstruction/ichcinstructionpageframe_5.ui \
    hcinstruction/icwaitconditioneditor_5.ui \
    hcinstruction/icprogramguidepage_5.ui \
    hcinstruction/icpneumaticactionpage_5.ui \
    hcinstruction/icperipheryparametereditor_5.ui \
    hcinstruction/ichcinjectionpage_5.ui \
    hcinstruction/ichcfixturepage_5.ui \
    hcinstruction/ichcconditionpage_5.ui \
    hcinstruction/iccutpage_5.ui \
    hcinstruction/actionsettingframe_5.ui \
    hcinstruction/ichcprogrammonitorframe_5.ui \
    hcinstruction/icinstructmodifydialog_5.ui
}
