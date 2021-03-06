
#include "CCPropsItem.h"
#include "../items/CItem.h"


lpctstr const CCPropsItem::_ptcPropertyKeys[PROPIT_QTY + 1] =
{
    #define ADD(a,b) b,
    #include "../../tables/CCPropsItem_props.tbl"
    #undef ADD
    nullptr
};
KeyTableDesc_s CCPropsItem::GetPropertyKeysData() const {
    return {_ptcPropertyKeys, (int)CountOf(_ptcPropertyKeys)};
}

CCPropsItem::CCPropsItem() : CComponentProps(COMP_PROPS_ITEM)
{
}

// If a CItem: subscribed in CItemBase::SetType and CItem::SetType
// If a CChar: subscribed in CCharBase::CCharBase and CChar::CChar
/*
bool CCPropsItem::CanSubscribe(const CObjBase* pObj) // static
{
    return (pObj->IsItem() || pObj->IsChar());
}
*/


lpctstr CCPropsItem::GetPropertyName(int iPropIndex) const
{
    ASSERT(iPropIndex < PROPIT_QTY);
    return _ptcPropertyKeys[iPropIndex];
}

bool CCPropsItem::IsPropertyStr(int iPropIndex) const
{
    /*
    switch (iPropIndex)
    {
        case 0:
            return true;
        default:
            return false;
    }
    */
    UNREFERENCED_PARAMETER(iPropIndex);
    return false;
}

bool CCPropsItem::GetPropertyNumPtr(int iPropIndex, PropertyValNum_t* piOutVal) const
{
    ADDTOCALLSTACK("CCPropsItem::GetPropertyNumPtr");
    ASSERT(!IsPropertyStr(iPropIndex));
    return BaseCont_GetPropertyNum(&_mPropsNum, iPropIndex, piOutVal);
}

bool CCPropsItem::GetPropertyStrPtr(int iPropIndex, CSString* psOutVal, bool fZero) const
{
    ADDTOCALLSTACK("CCPropsItem::GetPropertyStrPtr");
    ASSERT(IsPropertyStr(iPropIndex));
    return BaseCont_GetPropertyStr(&_mPropsStr, iPropIndex, psOutVal, fZero);
}

void CCPropsItem::SetPropertyNum(int iPropIndex, PropertyValNum_t iVal, CObjBase* pLinkedObj, bool fDeleteZero)
{
    ADDTOCALLSTACK("CCPropsItem::SetPropertyNum");
    ASSERT(!IsPropertyStr(iPropIndex));

    if (fDeleteZero && (iVal == 0))
        _mPropsNum.erase(iPropIndex);
    else
        _mPropsNum[iPropIndex] = iVal;

    if (!pLinkedObj)
        return;

    // Do stuff to the pLinkedObj
    pLinkedObj->UpdatePropertyFlag();
}

void CCPropsItem::SetPropertyStr(int iPropIndex, lpctstr ptcVal, CObjBase* pLinkedObj, bool fDeleteZero)
{
    ADDTOCALLSTACK("CCPropsItem::SetPropertyStr");
    ASSERT(ptcVal);
    ASSERT(IsPropertyStr(iPropIndex));

    if (fDeleteZero && (*ptcVal == '\0'))
        _mPropsStr.erase(iPropIndex);
    else
        _mPropsStr[iPropIndex] = ptcVal;

    if (!pLinkedObj)
        return;

    // Do stuff to the pLinkedObj
    pLinkedObj->UpdatePropertyFlag();
}

void CCPropsItem::DeletePropertyNum(int iPropIndex)
{
    ADDTOCALLSTACK("CCPropsItem::DeletePropertyNum");
    _mPropsNum.erase(iPropIndex);
}

void CCPropsItem::DeletePropertyStr(int iPropIndex)
{
    ADDTOCALLSTACK("CCPropsItem::DeletePropertyStr");
    _mPropsStr.erase(iPropIndex);
}

bool CCPropsItem::FindLoadPropVal(CScript & s, CObjBase* pLinkedObj, int iPropIndex, bool fPropStr)
{
    ADDTOCALLSTACK("CCPropsItem::FindLoadPropVal");
    if (!fPropStr && (*s.GetArgRaw() == '\0'))
    {
        DeletePropertyNum(iPropIndex);
        return true;
    }

    BaseProp_LoadPropVal(iPropIndex, fPropStr, s, pLinkedObj);
    return true;
}

bool CCPropsItem::FindWritePropVal(CSString & sVal, int iPropIndex, bool fPropStr) const
{
    ADDTOCALLSTACK("CCPropsItem::FindWritePropVal");

    return BaseProp_WritePropVal(iPropIndex, fPropStr, sVal);
}

void CCPropsItem::r_Write(CScript & s)
{
    ADDTOCALLSTACK("CCItemWeapon::r_Write");
    // r_Write isn't called by CItemBase/CCharBase, so we don't get base props saved
    BaseCont_Write_ContNum(&_mPropsNum, _ptcPropertyKeys, s);
    BaseCont_Write_ContStr(&_mPropsStr, _ptcPropertyKeys, s);
}

void CCPropsItem::Copy(const CComponentProps * target)
{
    ADDTOCALLSTACK("CCPropsItem::Copy");
    const CCPropsItem *pTarget = static_cast<const CCPropsItem*>(target);
    if (!pTarget)
        return;

    _mPropsNum = pTarget->_mPropsNum;
    _mPropsStr = pTarget->_mPropsStr;
}

void CCPropsItem::AddPropsTooltipData(CObjBase* pLinkedObj)
{
#define TOOLTIP_APPEND(t)   pLinkedObj->m_TooltipData.emplace_back(t)
#define ADDT(tooltipID)     TOOLTIP_APPEND(new CClientTooltip(tooltipID))
#define ADDTNUM(tooltipID)  TOOLTIP_APPEND(new CClientTooltip(tooltipID, iVal))
#define ADDTSTR(tooltipID)  TOOLTIP_APPEND(new CClientTooltip(tooltipID, ptcVal))

    /* Tooltips for "dynamic" properties (stored in the BaseConts: _mPropsNum and _mPropsStr) */
    
    // Numeric properties
    for (const BaseContNumPair_t& propPair : _mPropsNum)
    {
        int prop = propPair.first;
        PropertyValNum_t iVal = propPair.second;
        
        if (iVal == 0)
            continue;
        
        if (pLinkedObj->IsItem())
        {
            // Show tooltips for these props only if the linked obj is an item
            switch (prop)
            {
                case PROPIT_LAVAINFUSED: // Unimplemented
                    // Missing cliloc id
                    break;
                case PROPIT_PRIZED: // Unimplemented
                    // Missing cliloc id
                    break;
                case PROPIT_SHIPWRECKITEM: // Unimplemented
                    // Missing cliloc id
                    break;
                case PROPIT_UNLUCKY: // Unimplemented
                    // Missing cliloc id
                    break;
                case PROPIT_UNWIELDLY: // Unimplemented
                    // Missing cliloc id
                    break;
            }
            // End of Item-only tooltips
        }
    }
    // End of Numeric properties

/*    
    // String properties
    for (const BaseContStrPair_t& propPair : _mPropsStr)
    {
        int prop = propPair.first;
        lpctstr ptcVal = propPair.second.GetPtr();

        switch (prop)
        {
            default:
                break;
        }
    }
    // End of String properties
*/
}
