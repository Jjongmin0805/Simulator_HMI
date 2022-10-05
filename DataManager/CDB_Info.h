#pragma once
#include <afx.h>
#include "Markup.h"

class AFX_EXT_CLASS CDB_Info :
	public CObject
{
public:
	CDB_Info();
	~CDB_Info();

	CString m_strProvider;
	CString m_strDataSource;
	CString m_strDBName;
	CString m_strUserID;
	CString m_strPassword;
	CString m_strServer;
	CString m_strPort;
	CString m_strFailover;

	void									Read_Config(CMarkup* pxml);
};

typedef CTypedPtrArray<CObArray, CDB_Info*> CDB_InfoArray;