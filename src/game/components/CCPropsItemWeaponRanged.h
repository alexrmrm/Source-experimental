/**
* @file CCPropsItemWeaponRanged.h
*
*/

#ifndef _INC_CCPROPSITEMWEAPONRANGED_H
#define _INC_CCPROPSITEMWEAPONRANGED_H

#include "../CComponentProps.h"

class CObjBase;


enum PROPIWEAPRNG_TYPE
{
    #define ADD(a,b) PROPIWEAPRNG_##a,
    #include "../../tables/CCPropsItemWeaponRanged_props.tbl"
    #undef ADD
    PROPIWEAPRNG_QTY
};

class CCPropsItemWeaponRanged : public CComponentProps
{
    static lpctstr const _ptcPropertyKeys[];

public:
    CCPropsItemWeaponRanged();
    virtual ~CCPropsItemWeaponRanged() = default;

    static bool CanSubscribe(const CItemBase* pItemBase);
    static bool CanSubscribe(const CItem* pItem);


    virtual lpctstr GetName() const override {
        return "ItemWeaponRanged";
    }
    virtual int GetPropsQty() const override {
        return PROPIWEAPRNG_QTY;
    }
    virtual KeyTableDesc_s GetPropertyKeysData() const override;
    virtual lpctstr GetPropertyName(int iPropIndex) const override;
    virtual bool IsPropertyStr(int iPropIndex) const override;
    virtual bool GetPropertyNumPtr(int iPropIndex, PropertyValNum_t* piOutVal) const override;
    virtual bool GetPropertyStrPtr(int iPropIndex, CSString *psOutVal, bool fZero = false) const override;
    virtual void SetPropertyNum(int iPropIndex, PropertyValNum_t iVal, CObjBase* pLinkedObj, bool fDeleteZero = false) override;
    virtual void SetPropertyStr(int iPropIndex, lpctstr ptcVal, CObjBase* pLinkedObj, bool fDeleteZero = false) override;
    virtual void DeletePropertyNum(int iPropIndex) override;
    virtual void DeletePropertyStr(int iPropIndex) override;

    virtual bool FindLoadPropVal(CScript & s, CObjBase* pLinkedObj, int iPropIndex, bool fPropStr) override; // Use pLinkedObj = nullptr if calling this from CItemBase or CCharBase
    virtual bool FindWritePropVal(CSString & sVal, int iPropIndex, bool fPropStr) const override;
    virtual void r_Write(CScript & s) override;
    virtual void Copy(const CComponentProps *target) override;

    virtual void AddPropsTooltipData(CObjBase* pLinkedObj) override;

private:
    BaseContNum_t _mPropsNum;
    BaseContStr_t _mPropsStr;
};


#endif //_INC_CCPROPSITEMWEAPONRANGED_H