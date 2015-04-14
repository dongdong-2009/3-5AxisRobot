#include "icconfigstring.h"
#include "icvirtualhost.h"
#include "icmold.h"

ICConfigString::ICConfigString()
{
}

QString ICConfigString::ConfigString(int configID)
{
    switch (configID) {
    case kCS_Global_Speed:
        return QT_TR_NOOP("Global Speed");
    case KCS_User_Changed:
        return QT_TR_NOOP("User Changed");
    case kCS_Mold_Changed:
        return QT_TR_NOOP("Mold Changed");
    default:
        return QObject::tr("No IMPL");
    }
}
