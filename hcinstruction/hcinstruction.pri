INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/ichcinstructionpageframe.h \
    $$PWD/actionsettingframe.h \
    #$$PWD/ichcparametersframe.h \
    #$$PWD/routesettingdialog.h \
    $$PWD/ichcinjectionpage.h \
    $$PWD/ichcfixturepage.h \
    $$PWD/ichcconditionpage.h \
    $$PWD/icmold.h \
    $$PWD/icmacrosubroutine.h \
    $$PWD/icinstructparam.h \
    $$PWD/ichcprogrammonitorframe.h \
    #$$PWD/ichceditordialog.h \
    #$$PWD/icmacroparameditorframe.h \
    $$PWD/icautorunrevise.h \
    $$PWD/icinstructioneditorbase.h \
    $$PWD/icflagseditor.h \
    $$PWD/icpneumaticactionpage.h \
    $$PWD/icinstructmodifydialog.h \
    $$PWD/icwaitconditioneditor.h \
    $$PWD/icperipherypage.h \
    $$PWD/icperipheryparametereditor.h \
    $$PWD/iccutpage.h \
    $$PWD/icprogramselector.h \
    $$PWD/icstackeditor.h \
    $$PWD/icprogramguidepage.h \
    $$PWD/ichcotherpage.h \
    $$PWD/iccommenteditor.h \
    hcinstruction/iccurveeditor.h \
    hcinstruction/icsubmodifydialog.h

SOURCES += \
    $$PWD/ichcinstructionpageframe.cpp \
    $$PWD/actionsettingframe.cpp \
    #$$PWD/ichcparametersframe.cpp \
    #$$PWD/routesettingdialog.cpp \
    $$PWD/ichcinjectionpage.cpp \
    $$PWD/ichcfixturepage.cpp \
    $$PWD/ichcconditionpage.cpp \
    $$PWD/icmold.cpp \
    $$PWD/icmacrosubroutine.cpp \
    $$PWD/icinstructparam.cpp \
    $$PWD/ichcprogrammonitorframe.cpp \
    #$$PWD/ichceditordialog.cpp \
    #$$PWD/icmacroparameditorframe.cpp \
    $$PWD/icautorunrevise.cpp \
    $$PWD/icinstructioneditorbase.cpp \
    $$PWD/icflagseditor.cpp \
    $$PWD/icpneumaticactionpage.cpp \
    $$PWD/icinstructmodifydialog.cpp \
    $$PWD/icwaitconditioneditor.cpp \
    $$PWD/icperipherypage.cpp \
    $$PWD/icperipheryparametereditor.cpp \
    $$PWD/iccutpage.cpp \
    $$PWD/icprogramselector.cpp \
    $$PWD/icstackeditor.cpp \
    $$PWD/icprogramguidepage.cpp \
    $$PWD/ichcotherpage.cpp \
    $$PWD/iccommenteditor.cpp \
    hcinstruction/iccurveeditor.cpp \
    hcinstruction/icsubmodifydialog.cpp

FORMS += \
    $$PWD/icautorunrevise.ui \
    $$PWD/icinstructioneditorbase.ui \
    $$PWD/icflagseditor.ui \
    $$PWD/icperipherypage.ui \
    $$PWD/icprogramselector.ui \
    $$PWD/icstackeditor.ui \
    $$PWD/ichcotherpage.ui \
    $$PWD/iccommenteditor.ui \
    $$PWD/icinstructmodifydialog.ui \
    hcinstruction/iccurveeditor.ui \
    hcinstruction/icsubmodifydialog.ui




RESOURCES += \
    resource.qrc

contains(DEFINES, HC_SK_8){
FORMS += $$PWD/ichcinstructionpageframe.ui \
    $$PWD/icwaitconditioneditor.ui \
    $$PWD/icprogramguidepage.ui \
    $$PWD/icpneumaticactionpage.ui \
    $$PWD/icperipheryparametereditor.ui \
    $$PWD/ichcinjectionpage.ui \
    $$PWD/ichcfixturepage.ui \
    $$PWD/ichcconditionpage.ui \
    $$PWD/iccutpage.ui \
    $$PWD/actionsettingframe.ui \
    $$PWD/ichcprogrammonitorframe.ui
}
contains(DEFINES, HC_SK_5){
FORMS += $$PWD/ichcinstructionpageframe_5.ui \
    $$PWD/icwaitconditioneditor_5.ui \
    $$PWD/icprogramguidepage_5.ui \
    $$PWD/icpneumaticactionpage_5.ui \
    $$PWD/icperipheryparametereditor_5.ui \
    $$PWD/ichcinjectionpage_5.ui \
    $$PWD/ichcfixturepage_5.ui \
    $$PWD/ichcconditionpage_5.ui \
    $$PWD/iccutpage_5.ui \
    $$PWD/actionsettingframe_5.ui \
    $$PWD/ichcprogrammonitorframe_5.ui
}
