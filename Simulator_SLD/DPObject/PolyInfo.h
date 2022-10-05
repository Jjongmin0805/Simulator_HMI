#pragma once
#include "afx.h"
#include "DPoint.h"

class AFX_EXT_CLASS CPolyInfo :
	public CObject
{
public:
	CPolyInfo(void);
	~CPolyInfo(void);

	int			m_nTogi;
	CDPArray	m_pPolyArr;
	void AddPoint(double dx, double dy);
	void Draw(CDC* pDC, double dzoom, CDPoint* pCen, CPoint ptCen);
protected:
	POINT* Relocation(double dzoom, CDPoint* pCen, CPoint ptCen);
};

typedef CTypedPtrArray<CObArray, CPolyInfo*> CPolyInfoArray;
