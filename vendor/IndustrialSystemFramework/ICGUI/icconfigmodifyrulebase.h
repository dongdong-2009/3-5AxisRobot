#ifndef ICCONFIGMODIFYRULEBASE_H
#define ICCONFIGMODIFYRULEBASE_H

#include "icaddrwrapper.h"
#include <QVariant>
#include "ICGUI_global.h"

class ICGUISHARED_EXPORT ICConfigModifyRuleBase
{
public:
    ICConfigModifyRuleBase();
    virtual ~ICConfigModifyRuleBase(){}

    bool Exec(const ICAddrWrapper* config, const QVariant &v)
    {
        if(DoesNeedToExec(config, v))
        {
            return ExecImpl(config, v);
        }
        return true;
    }

protected:
    virtual bool DoesNeedToExec(const ICAddrWrapper* config, const QVariant& v) = 0;
    virtual bool ExecImpl(const ICAddrWrapper* config, const QVariant& v) = 0;
};

#endif // ICCONFIGMODIFYRULEBASE_H
