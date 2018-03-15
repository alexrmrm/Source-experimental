/**
* @file CRegionBase.h
* @brief 
*/

#ifndef _INC_CREGIONBASE_H
#define _INC_CREGIONBASE_H

#include "../common/sphere_library/CSArray.h"
#include "../common/CRect.h"


class CRegionBase
{
	// A bunch of rectangles forming an area.
public:
	static const char *m_sClassName;
	CRect m_rectUnion;	// The union rectangle.
	CSTypedArray<CRect, const CRect&> m_Rects;
	bool IsRegionEmpty() const
	{
		return( m_rectUnion.IsRectEmpty());
	}
	void EmptyRegion()
	{
		m_rectUnion.SetRectEmpty();
		m_Rects.Empty();
	}
	size_t GetRegionRectCount() const;
	CRect & GetRegionRect(size_t i);
	const CRect & GetRegionRect(size_t i) const;
	virtual bool AddRegionRect( const CRect & rect );

	CPointBase GetRegionCorner( DIR_TYPE dir = DIR_QTY ) const;
	bool IsInside2d( const CPointBase & pt ) const;

	bool IsOverlapped( const CRect & rect ) const;
	bool IsInside( const CRect & rect ) const;

	bool IsInside( const CRegionBase * pRegionIsSmaller ) const;
	bool IsOverlapped( const CRegionBase * pRegionTest ) const;
	bool IsEqualRegion( const CRegionBase * pRegionTest ) const;

	CSector * GetSector( int i ) const	// get all the sectors that make up this rect.
	{
		return m_rectUnion.GetSector(i);
	}

public:
	CRegionBase();
	virtual ~CRegionBase() { };

private:
	CRegionBase(const CRegionBase& copy);
	CRegionBase& operator=(const CRegionBase& other);
};


#endif // _INC_CREGIONBASE_H
