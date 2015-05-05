#ifndef ICPARAMETERRANGE_H
#define ICPARAMETERRANGE_H


#include <QValidator>
#include <QHash>

class ICAddrWrapper;
typedef QValidator ICRangeValidator;
typedef QHash<uint, ICRangeValidator* > ICParameterTypeToValidatorMap;
typedef QHash<const ICAddrWrapper*, uint> ICParameterToTypeMap;

class ICParameterRange
{
public:
    ICParameterRange();
    static void SetParametersRangeCache(const ICParameterTypeToValidatorMap& map) {configsRangeCache_ = map;}
    static void SetParameterLinkedMinValidator(const ICParameterToTypeMap& map) { addrToMinValidator_ = map;}
    static void SetParameterLinkedMaxValidator(const ICParameterToTypeMap& map) { addrToMaxValidator_ = map;}
    static ICRangeValidator* ConfigRangeValidator(uint type);
    static void UpdateConfigRangeValidator(uint type, double min, double max);
    static void UpdateConfigRangeValidator(const ICAddrWrapper* addr, double value);
    static void CreateConfigRangeValidator(uint type, ICRangeValidator* v) {configsRangeCache_.insert(type, v);}
    static void Free();
    template <typename GetParameterValueBaseOnAddr>
    static void SyncValidators(GetParameterValueBaseOnAddr func)
    {

        ICParameterToTypeMap::iterator p = addrToMaxValidator_.begin();
        while(p != addrToMaxValidator_.end())
        {
            UpdateConfigRangeValidator(p.key(), func(p.key()));
            ++p;
        }
        p = addrToMinValidator_.begin();
        while(p != addrToMinValidator_.end())
        {
            UpdateConfigRangeValidator(p.key(), func(p.key()));
            ++p;
        }
    }

private:
    static ICParameterTypeToValidatorMap configsRangeCache_;
    static ICParameterToTypeMap addrToMinValidator_;
    static ICParameterToTypeMap addrToMaxValidator_;
};

#endif // ICPARAMETERRANGE_H
