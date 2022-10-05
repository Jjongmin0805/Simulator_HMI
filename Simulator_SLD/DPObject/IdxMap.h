#pragma once
#include "afx.h"
#include "PolyInfo.h"

class AFX_EXT_CLASS CIdxMap :
	public CObject
{
public:
	CIdxMap(void);
	~CIdxMap(void);
	virtual void Serialize(CArchive& ar);

protected:
	CPolyInfoArray	m_pPolyArray;
	double m_dmaxx,m_dmaxy,m_dminx,m_dminy;
public:
	void DrawNavi(CDC* pDC, CRect rect);
	void DrawNaviRect(CDC* pDC, CRect rect, CDPoint* pLT, CDPoint* pRB);
	CDPoint* NaviLBtnDown(CRect rect, CPoint point);
	CRect GetNaviRect(CRect rect, CDPoint* pLT, CDPoint* pRB);

protected:
	POINT* Relocation(CPolyInfo* pInfo, double dzoom, CDPoint* pCen, CPoint ptCen);

};

