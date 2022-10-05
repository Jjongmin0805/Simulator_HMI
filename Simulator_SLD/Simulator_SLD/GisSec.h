#pragma once
#include <afx.h>
#include "Pole.h"

class CGisSec :	public CObject
{
public:
	CGisSec();
	virtual ~CGisSec();

	int														m_nDbID;
	int														m_nOverHead;	//0:가공, 1:지중
	CString													m_szCEQID;
	int														m_nNDID[2];

	CPoleArray												m_pPoleArr;

	void													Draw(CDC* BufferDC, int nSize, double dZoom, double pCenX, double pCenY, CPoint ptCen);
};

typedef CTypedPtrArray<CObArray, CGisSec*> CGisSecArray;