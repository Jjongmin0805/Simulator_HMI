#include "pch.h"
#include "CDB_Info.h"


CDB_Info::CDB_Info()
{

}

CDB_Info::~CDB_Info()
{

}

void CDB_Info::Read_Config(CMarkup* pxml)
{
	CString strTagName;
	CString strData[8];

	while (pxml->FindChildElem())
	{
		pxml->IntoElem();
		strTagName = pxml->GetTagName();
		strTagName.MakeLower();

		if (strTagName == _T("provider"))
		{
			strData[0] = pxml->GetData();
		}
		else if (strTagName == _T("datasource"))
		{
			strData[1] = pxml->GetData();
		}
		else if (strTagName == _T("dbname"))
		{
			strData[2] = pxml->GetData();
		}
		else if (strTagName == _T("userid"))
		{
			strData[3] = pxml->GetData();
		}
		else if (strTagName == _T("userpassword"))
		{
			strData[4] = pxml->GetData();
		}
		else if (strTagName == _T("server"))
		{
			strData[5] = pxml->GetData();
		}
		else if (strTagName == _T("port"))
		{
			strData[6] = pxml->GetData();
		}
		else if (strTagName == _T("failover"))
		{
			strData[7] = pxml->GetData();
		}
		pxml->OutOfElem();
	}

	


	m_strProvider			 = strData[0];
	m_strDataSource			 = strData[1];
	m_strDBName				 = strData[2];
	m_strUserID				 = strData[3];
	m_strPassword			 = strData[4];
	m_strServer				 = strData[5];
	m_strPort				 = strData[6];
	m_strFailover			 = strData[7];

}