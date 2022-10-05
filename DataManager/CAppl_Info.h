#pragma once
#include <afx.h>
#include "Markup.h"

class AFX_EXT_CLASS CAppl_Info :
	public CObject
{
public:
	CAppl_Info();
	~CAppl_Info();

	int										m_nID;
	CString									m_strName;
	int										m_nTimeOut;
	int										m_nFalicontinue;

	
	void									Read_Config(CMarkup* pxml);
};

typedef CTypedPtrArray<CObArray, CAppl_Info*> CAppl_InfoArray;