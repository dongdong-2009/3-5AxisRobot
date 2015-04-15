#ifndef ICCONFIGSTRING_H
#define ICCONFIGSTRING_H

#include <QString>
#include <QMap>

#include "icalarmframe.h"
#include "icbuttongroup.h"
#include "iccombobox.h"
#include "iclineeditwithvirtualnumerickeypad.h"
#include <QCheckBox>


#define ICLogInit \
    QMap<QObject*, int>::iterator p = editorToConfigIDs_.begin();\
    ICLineEditWithVirtualNumericKeypad* le;\
    ICComboBox* cb;\
    QButtonGroup* bg;\
    QCheckBox* cbox;\
    while(p != editorToConfigIDs_.end())\
    {\
        le = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(p.key());\
        if(le != NULL)\
        {\
            connect(le, SIGNAL(textChanged(QString)), SLOT(OnConfigChanged(QString)));\
            ++p;\
            continue;\
        }\
        cb = qobject_cast<ICComboBox*>(p.key());\
        if(cb != NULL)\
        {\
            connect(cb, SIGNAL(currentIndexChanged(int)), SLOT(OnConfigChanged(int)));\
            ++p;\
            continue;\
        }\
        bg = qobject_cast<QButtonGroup*>(p.key());\
        if(bg != NULL)\
        {\
            ICButtonGroup* icbg = new ICButtonGroup(bg, bg->parent());\
            connect(icbg, SIGNAL(buttonClicked(int, int)), SLOT(OnConfigChanged(int, int)));\
            ++p;\
            continue;\
        }\
        cbox = qobject_cast<QCheckBox*>(p.key());\
        if(cbox != NULL)\
        {\
            connect(cbox, SIGNAL(toggled(bool)), SLOT(OnConfigChanged(bool)));\
            ++p;\
            continue;\
        }\
    }


#define ICLogFunctions(cl) \
    void cl::OnConfigChanged(QObject *w, const QString& newV, const QString& oldV)\
    {\
        ICAlarmFrame::Instance()->OnActionTriggered(editorToConfigIDs_.value(w, ICConfigString::kCS_Err),\
                                                    newV,\
                                                    oldV);\
    }\
    \
    void cl::OnConfigChanged(const QString &text)\
    {\
        ICLineEditWithVirtualNumericKeypad* edit = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(sender());\
        OnConfigChanged(edit, text, edit->LastValue());\
    }\
    \
    void cl::OnConfigChanged(int v, int ov)\
    {\
        ICButtonGroup* icbg = qobject_cast<ICButtonGroup*>(sender());\
        QButtonGroup* bg = icbg->ButtongGroup();\
        OnConfigChanged(bg, bg->button(v)->text(), bg->button(ov)->text());\
    }\
    \
    void cl::OnConfigChanged(int v)\
    {\
        ICComboBox* edit = qobject_cast<ICComboBox*>(sender());\
        OnConfigChanged(edit, edit->currentText(), edit->itemText(edit->LastValue()));\
    }\
\
    void cl::OnConfigChanged(bool b)\
    {\
        QCheckBox* edit = qobject_cast<QCheckBox*>(sender());\
        OnConfigChanged(edit, QString::number(b), QString::number(!b));\
    }


class ICConfigString
{
public:

    enum {
        kCS_Global_Speed,
        kCS_User_Changed,
        kCS_Mold_Changed,

        kCS_SIG_Fixture1,
        kCS_SIG_Fixture2,
        kCS_SIG_Fixture3,
        kCS_SIG_Fixture4,
        kCS_SIG_IMM_Stop,
        kCS_SIG_Z_Move_Pos,
        kCS_SIG_Origin,
        kCS_SIG_Y_Origin_Pos,
        kCS_SIG_Hor_Standby,
        kCS_SIG_CM_Limit,
        kCS_SIG_SEDoor,
        kCS_SIG_Press,
        kCS_SIG_Mid_Mold,
        kCS_SIG_EJE_Linked,
        kCS_SIG_Auto,

        kCS_PRD_Number,
        kCS_PRD_Wait_OM_Limit,
        kCS_PRD_Alarm_Time,
        kCS_PRD_Cycle_Time,
        kCS_PRD_Fixture_Define,
        kCS_PRD_Alarm_Occasion_When_Get_Fail,
        kCS_PRD_Transport_Count_Way,
        kCS_PRD_Save_Count,

        kCS_RUN_Tolerance,
        kCS_RUN_Distance_X1_X2,
        kCS_RUN_Acc_Time_X1,
        kCS_RUN_Acc_Time_Y1,
        kCS_RUN_Acc_Time_Z,
        kCS_RUN_Acc_Time_X2,
        kCS_RUN_Acc_Time_Y2,
        kCS_RUN_Acc_Time_A,
        kCS_RUN_Acc_Time_B,
        kCS_RUN_Acc_Time_C,
        kCS_RUN_Speed_Limit_X1,
        kCS_RUN_Speed_Limit_Y1,
        kCS_RUN_Speed_Limit_Z,
        kCS_RUN_Speed_Limit_X2,
        kCS_RUN_Speed_Limit_Y2,
        kCS_RUN_Speed_Limit_A,
        kCS_RUN_Speed_Limit_B,
        kCS_RUN_Speed_Limit_C,

        kCS_SECP_Inside_X_Min,
        kCS_SECP_Inside_X_Max,
        kCS_SECP_Outside_X_Min,
        kCS_SECP_Outside_X_Max,

        kCS_STRUCT_Axis_Define_X1,
        kCS_STRUCT_Axis_Define_Y1,
        kCS_STRUCT_Axis_Define_Z,
        kCS_STRUCT_Axis_Define_X2,
        kCS_STRUCT_Axis_Define_Y2,
        kCS_STRUCT_Axis_Define_A,
        kCS_STRUCT_Axis_Define_B,
        kCS_STRUCT_Axis_Define_C,

        kCS_STRUCT_Reserve_Define_Y017,
        kCS_STRUCT_Reserve_Define_Y022,
        kCS_STRUCT_Reserve_Define_Y031,
        kCS_STRUCT_Reserve_Define_Y032,
        kCS_STRUCT_Reserve_Define_Y035,
        kCS_STRUCT_Reserve_Define_Y036,
        kCS_STRUCT_Reserve_Define_R1,
        kCS_STRUCT_Reserve_Define_R2,
        kCS_STRUCT_Limit_Define_Arm_Num,
        kCS_STRUCT_Limit_Define_MArm_DW_Limit,
        kCS_STRUCT_Limit_Define_MArm_FW_Limit,
        kCS_STRUCT_Limit_Define_MArm_BW_Limit,
        kCS_STRUCT_Limit_Define_SArm_DW_Limit,
        kCS_STRUCT_Limit_Define_SArm_FW_Limit,
        kCS_STRUCT_Limit_Define_SArm_BW_Limit,
        kCS_STRUCT_Other_Define_Escape,
        kCS_STRUCT_Other_Define_Tune_bit,
        kCS_STRUCT_Other_Define_Inside_Position,
        kCS_STRUCT_Other_Define_Servo_Flex,

        kCS_Time_Ver1,
        kCS_Time_Hor1,
        kCS_Time_Ver2,
        kCS_Time_Hor2,
        kCS_Time_MArm_UP,
        kCS_Time_MArm_Dw,
        kCS_Time_MArm_FW,
        kCS_Time_MArm_BW,
        kCS_Time_Z_FW,
        kCS_Time_Z_BW,
        kCS_Time_SArm_UP,
        kCS_Time_SArm_DW,
        kCS_Time_SArm_FW,
        kCS_Time_SArm_BW,

        kCS_Err,

    };


    ICConfigString();

    static QString ConfigString(int configID);

};

#endif // ICCONFIGSTRING_H
