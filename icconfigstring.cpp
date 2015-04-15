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
        case kCS_Err: return QT_TR_NOOP("kCS_Err");
        default: return QT_TR_NOOP("No IMPL");
    }
}
//#AUTO GEN END
