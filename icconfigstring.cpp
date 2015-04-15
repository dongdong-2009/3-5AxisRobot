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
        default: return QT_TR_NOOP("No IMPL");
    }
}
//#AUTO GEN END
