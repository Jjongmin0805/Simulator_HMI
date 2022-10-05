#pragma once
#include <afx.h>
#include "../DPObject/DPoint.h"
class CGisObj :	public CObject
{
public:
	CGisObj();
	virtual ~CGisObj();

	int														m_nDbID;
	int														m_nSwKindID;
	int														m_nKCIMType;
	CString													m_szLoc;
	CString													m_szLocNo;
	CString													m_szCEQID;
	BOOL													m_bStatus;
	int														m_nNDID[2];

	CRect													m_rectObj;

	CDPoint													m_pDPoint;
};

typedef CTypedPtrArray<CObArray, CGisObj*> CGisObjArray;