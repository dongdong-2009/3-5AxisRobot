#include "icparameterrange.h"
#include "icaddrwrapper.h"

#include <qmath.h>


ICParameterTypeToValidatorMap ICParameterRange::configsRangeCache_;
ICParameterToTypeMap ICParameterRange::addrToMinValidator_;
ICParameterToTypeMap ICParameterRange::addrToMaxValidator_;
ICParameterRange::ICParameterRange()
{
}

void ICParameterRange::Free()
{
    QHash<uint, ICRangeValidator* >::iterator p = configsRangeCache_.begin();
    while(p != configsRangeCache_.end())
    {
        delete p.value();
        p = configsRangeCache_.erase(p);
    }
}

void ICParameterRange::UpdateConfigRangeValidator(uint type, double min, double max)
{
    if(!configsRangeCache_.contains(type)) return;
    QDoubleValidator* dv = static_cast<QDoubleValidator*>(configsRangeCache_.value(type));
    if(dv != NULL)
    {
        dv->setBottom(min);
        dv->setTop(max);
        return;
    }
    QIntValidator* iv = static_cast<QIntValidator*>(configsRangeCache_.value(type));
    if(iv != NULL)
    {
        iv->setBottom(min);
        iv->setTop(max);
    }
}

void ICParameterRange::UpdateConfigRangeValidator(const ICAddrWrapper *addr, double value)
{
//    QMap<const ICAddrWrapper*, uint>::iterator p = addrToMaxValidator_.find(addr);
    value /= qPow(10, addr->Decimal());
    QList<uint> vs = addrToMaxValidator_.values(addr);
    for(int i = 0; i != vs.size(); ++i)
    {
        if(!configsRangeCache_.contains(vs.at(i))) continue;
        QDoubleValidator* dv = static_cast<QDoubleValidator*>(configsRangeCache_.value(vs.at(i)));
        if(dv != NULL)
        {
            dv->setTop(value);
//            ++p;
            continue;
        }
        QIntValidator* iv = static_cast<QIntValidator*>(configsRangeCache_.value(vs.at(i)));
        if(iv != NULL)
        {
            iv->setTop(value);
        }
    }

    vs  = addrToMinValidator_.values(addr);
    for(int i = 0; i != vs.size(); ++i)
    {
        if(!configsRangeCache_.contains(vs.at(i))) continue;
        QDoubleValidator* dv = static_cast<QDoubleValidator*>(configsRangeCache_.value(vs.at(i)));
        if(dv != NULL)
        {
            dv->setBottom(value);
//            ++p;
            continue;
        }
        QIntValidator* iv = static_cast<QIntValidator*>(configsRangeCache_.value(vs.at(i)));
        if(iv != NULL)
        {
            iv->setBottom(value);
        }
    }

}
