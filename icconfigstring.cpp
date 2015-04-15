#include "icconfigstring.h"
#include "icvirtualhost.h"
#include "icmold.h"

ICConfigString::ICConfigString()
{
}

//#AUTO GEN BEGIN 
QString ICConfigString::ConfigString(int configID)
{
    switch (configID) 
    {
        case kCS_Global_Speed: return QT_TR_NOOP("kCS_Global_Speed");
        case kCS_User_Changed: return QT_TR_NOOP("kCS_User_Changed");
        case kCS_Mold_Changed: return QT_TR_NOOP("kCS_Mold_Changed");
        case kCS_SIG_Fixture1: return QT_TR_NOOP("kCS_SIG_Fixture1");
        case kCS_SIG_Fixture2: return QT_TR_NOOP("kCS_SIG_Fixture2");
        case kCS_SIG_Fixture3: return QT_TR_NOOP("kCS_SIG_Fixture3");
        case kCS_SIG_Fixture4: return QT_TR_NOOP("kCS_SIG_Fixture4");
        case kCS_SIG_IMM_Stop: return QT_TR_NOOP("kCS_SIG_IMM_Stop");
        case kCS_SIG_Z_Move_Pos: return QT_TR_NOOP("kCS_SIG_Z_Move_Pos");
        case kCS_SIG_Origin: return QT_TR_NOOP("kCS_SIG_Origin");
        case kCS_SIG_Y_Origin_Pos: return QT_TR_NOOP("kCS_SIG_Y_Origin_Pos");
        case kCS_SIG_Hor_Standby: return QT_TR_NOOP("kCS_SIG_Hor_Standby");
        case kCS_SIG_CM_Limit: return QT_TR_NOOP("kCS_SIG_CM_Limit");
        case kCS_SIG_SEDoor: return QT_TR_NOOP("kCS_SIG_SEDoor");
        case kCS_SIG_Press: return QT_TR_NOOP("kCS_SIG_Press");
        case kCS_SIG_Mid_Mold: return QT_TR_NOOP("kCS_SIG_Mid_Mold");
        case kCS_SIG_EJE_Linked: return QT_TR_NOOP("kCS_SIG_EJE_Linked");
        case kCS_SIG_Auto: return QT_TR_NOOP("kCS_SIG_Auto");
        case kCS_PRD_Number: return QT_TR_NOOP("kCS_PRD_Number");
        case kCS_PRD_Wait_OM_Limit: return QT_TR_NOOP("kCS_PRD_Wait_OM_Limit");
        case kCS_PRD_Alarm_Time: return QT_TR_NOOP("kCS_PRD_Alarm_Time");
        case kCS_PRD_Cycle_Time: return QT_TR_NOOP("kCS_PRD_Cycle_Time");
        case kCS_PRD_Fixture_Define: return QT_TR_NOOP("kCS_PRD_Fixture_Define");
        case kCS_PRD_Alarm_Occasion_When_Get_Fail: return QT_TR_NOOP("kCS_PRD_Alarm_Occasion_When_Get_Fail");
        case kCS_PRD_Transport_Count_Way: return QT_TR_NOOP("kCS_PRD_Transport_Count_Way");
        case kCS_PRD_Save_Count: return QT_TR_NOOP("kCS_PRD_Save_Count");
        case kCS_RUN_Tolerance: return QT_TR_NOOP("kCS_RUN_Tolerance");
        case kCS_RUN_Distance_X1_X2: return QT_TR_NOOP("kCS_RUN_Distance_X1_X2");
        case kCS_RUN_Acc_Time_X1: return QT_TR_NOOP("kCS_RUN_Acc_Time_X1");
        case kCS_RUN_Acc_Time_Y1: return QT_TR_NOOP("kCS_RUN_Acc_Time_Y1");
        case kCS_RUN_Acc_Time_Z: return QT_TR_NOOP("kCS_RUN_Acc_Time_Z");
        case kCS_RUN_Acc_Time_X2: return QT_TR_NOOP("kCS_RUN_Acc_Time_X2");
        case kCS_RUN_Acc_Time_Y2: return QT_TR_NOOP("kCS_RUN_Acc_Time_Y2");
        case kCS_RUN_Acc_Time_A: return QT_TR_NOOP("kCS_RUN_Acc_Time_A");
        case kCS_RUN_Acc_Time_B: return QT_TR_NOOP("kCS_RUN_Acc_Time_B");
        case kCS_RUN_Acc_Time_C: return QT_TR_NOOP("kCS_RUN_Acc_Time_C");
        case kCS_RUN_Speed_Limit_X1: return QT_TR_NOOP("kCS_RUN_Speed_Limit_X1");
        case kCS_RUN_Speed_Limit_Y1: return QT_TR_NOOP("kCS_RUN_Speed_Limit_Y1");
        case kCS_RUN_Speed_Limit_Z: return QT_TR_NOOP("kCS_RUN_Speed_Limit_Z");
        case kCS_RUN_Speed_Limit_X2: return QT_TR_NOOP("kCS_RUN_Speed_Limit_X2");
        case kCS_RUN_Speed_Limit_Y2: return QT_TR_NOOP("kCS_RUN_Speed_Limit_Y2");
        case kCS_RUN_Speed_Limit_A: return QT_TR_NOOP("kCS_RUN_Speed_Limit_A");
        case kCS_RUN_Speed_Limit_B: return QT_TR_NOOP("kCS_RUN_Speed_Limit_B");
        case kCS_RUN_Speed_Limit_C: return QT_TR_NOOP("kCS_RUN_Speed_Limit_C");
        case kCS_SECP_Inside_X_Min: return QT_TR_NOOP("kCS_SECP_Inside_X_Min");
        case kCS_SECP_Inside_X_Max: return QT_TR_NOOP("kCS_SECP_Inside_X_Max");
        case kCS_SECP_Outside_X_Min: return QT_TR_NOOP("kCS_SECP_Outside_X_Min");
        case kCS_SECP_Outside_X_Max: return QT_TR_NOOP("kCS_SECP_Outside_X_Max");
        case kCS_STRUCT_Axis_Define_X1: return QT_TR_NOOP("kCS_STRUCT_Axis_Define_X1");
        case kCS_STRUCT_Axis_Define_Y1: return QT_TR_NOOP("kCS_STRUCT_Axis_Define_Y1");
        case kCS_STRUCT_Axis_Define_Z: return QT_TR_NOOP("kCS_STRUCT_Axis_Define_Z");
        case kCS_STRUCT_Axis_Define_X2: return QT_TR_NOOP("kCS_STRUCT_Axis_Define_X2");
        case kCS_STRUCT_Axis_Define_Y2: return QT_TR_NOOP("kCS_STRUCT_Axis_Define_Y2");
        case kCS_STRUCT_Axis_Define_A: return QT_TR_NOOP("kCS_STRUCT_Axis_Define_A");
        case kCS_STRUCT_Axis_Define_B: return QT_TR_NOOP("kCS_STRUCT_Axis_Define_B");
        case kCS_STRUCT_Axis_Define_C: return QT_TR_NOOP("kCS_STRUCT_Axis_Define_C");
        case kCS_STRUCT_Reserve_Define_Y017: return QT_TR_NOOP("kCS_STRUCT_Reserve_Define_Y017");
        case kCS_STRUCT_Reserve_Define_Y022: return QT_TR_NOOP("kCS_STRUCT_Reserve_Define_Y022");
        case kCS_STRUCT_Reserve_Define_Y031: return QT_TR_NOOP("kCS_STRUCT_Reserve_Define_Y031");
        case kCS_STRUCT_Reserve_Define_Y032: return QT_TR_NOOP("kCS_STRUCT_Reserve_Define_Y032");
        case kCS_STRUCT_Reserve_Define_Y035: return QT_TR_NOOP("kCS_STRUCT_Reserve_Define_Y035");
        case kCS_STRUCT_Reserve_Define_Y036: return QT_TR_NOOP("kCS_STRUCT_Reserve_Define_Y036");
        case kCS_STRUCT_Reserve_Define_R1: return QT_TR_NOOP("kCS_STRUCT_Reserve_Define_R1");
        case kCS_STRUCT_Reserve_Define_R2: return QT_TR_NOOP("kCS_STRUCT_Reserve_Define_R2");
        case kCS_STRUCT_Limit_Define_Arm_Num: return QT_TR_NOOP("kCS_STRUCT_Limit_Define_Arm_Num");
        case kCS_STRUCT_Limit_Define_MArm_DW_Limit: return QT_TR_NOOP("kCS_STRUCT_Limit_Define_MArm_DW_Limit");
        case kCS_STRUCT_Limit_Define_MArm_FW_Limit: return QT_TR_NOOP("kCS_STRUCT_Limit_Define_MArm_FW_Limit");
        case kCS_STRUCT_Limit_Define_MArm_BW_Limit: return QT_TR_NOOP("kCS_STRUCT_Limit_Define_MArm_BW_Limit");
        case kCS_STRUCT_Limit_Define_SArm_DW_Limit: return QT_TR_NOOP("kCS_STRUCT_Limit_Define_SArm_DW_Limit");
        case kCS_STRUCT_Limit_Define_SArm_FW_Limit: return QT_TR_NOOP("kCS_STRUCT_Limit_Define_SArm_FW_Limit");
        case kCS_STRUCT_Limit_Define_SArm_BW_Limit: return QT_TR_NOOP("kCS_STRUCT_Limit_Define_SArm_BW_Limit");
        case kCS_STRUCT_Other_Define_Escape: return QT_TR_NOOP("kCS_STRUCT_Other_Define_Escape");
        case kCS_STRUCT_Other_Define_Tune_bit: return QT_TR_NOOP("kCS_STRUCT_Other_Define_Tune_bit");
        case kCS_STRUCT_Other_Define_Inside_Position: return QT_TR_NOOP("kCS_STRUCT_Other_Define_Inside_Position");
        case kCS_STRUCT_Other_Define_Servo_Flex: return QT_TR_NOOP("kCS_STRUCT_Other_Define_Servo_Flex");
        case kCS_TIME_Ver1: return QT_TR_NOOP("kCS_Time_Ver1");
        case kCS_TIME_Hor1: return QT_TR_NOOP("kCS_Time_Hor1");
        case kCS_TIME_Ver2: return QT_TR_NOOP("kCS_Time_Ver2");
        case kCS_TIME_Hor2: return QT_TR_NOOP("kCS_Time_Hor2");
        case kCS_TIME_MArm_UP: return QT_TR_NOOP("kCS_Time_MArm_UP");
        case kCS_TIME_MArm_Dw: return QT_TR_NOOP("kCS_Time_MArm_Dw");
        case kCS_TIME_MArm_FW: return QT_TR_NOOP("kCS_Time_MArm_FW");
        case kCS_TIME_MArm_BW: return QT_TR_NOOP("kCS_Time_MArm_BW");
        case kCS_TIME_Z_FW: return QT_TR_NOOP("kCS_Time_Z_FW");
        case kCS_TIME_Z_BW: return QT_TR_NOOP("kCS_Time_Z_BW");
        case kCS_TIME_SArm_UP: return QT_TR_NOOP("kCS_Time_SArm_UP");
        case kCS_TIME_SArm_DW: return QT_TR_NOOP("kCS_Time_SArm_DW");
        case kCS_TIME_SArm_FW: return QT_TR_NOOP("kCS_Time_SArm_FW");
        case kCS_TIME_SArm_BW: return QT_TR_NOOP("kCS_Time_SArm_BW");
        case kCS_Err: return QT_TR_NOOP("kCS_Err");
        default: return QT_TR_NOOP("No IMPL");
    }
}
//#AUTO GEN END
