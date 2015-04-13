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
        return QObject::tr("Global Speed");
    case KCS_User_Changed:
        return QObject::tr("User Changed");
    default:
        return QObject::tr("No IMPL");
    }
}
