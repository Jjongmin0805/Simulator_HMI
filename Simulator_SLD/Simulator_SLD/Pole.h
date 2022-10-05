#pragma once
#include <afx.h>
#include "../DPObject/DPoint.h"

class CPole : public CObject
{
public:
	CPole();
	virtual ~CPole();

	CString												m_szPoleNm;
	CDPoint												m_dPoint;
};

typedef CTypedPtrArray<CObArray, CPole*> CPoleArray;