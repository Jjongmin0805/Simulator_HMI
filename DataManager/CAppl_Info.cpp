#include "pch.h"
#include "CAppl_Info.h"


CAppl_Info::CAppl_Info()
{
	m_nID = -1;
	m_strName.Empty();
	m_nTimeOut = -1;
	m_nFalicontinue = -1;
}

CAppl_Info::~CAppl_Info()
{

}



void CAppl_Info::Read_Config(CMarkup* pxml)
{
	CString strTagName;
	CString strData[4];

	while (pxml->FindChildElem())
	{
		pxml->IntoElem();
		strTagName = pxml->GetTagName();
		strTagName.MakeLower();

		if (strTagName == _T("id"))
		{
			strData[0] = pxml->GetData();
		}
		else if (strTagName == _T("name"))
		{
			strData[1] = pxml->GetData();
		}
		else if (strTagName == _T("timeout"))
		{
			strData[2] = pxml->GetData();
		}
		else if (strTagName == _T("failcontinue"))
		{
			strData[3] = pxml->GetData();
		}
		pxml->OutOfElem();
	}

	m_nID = _wtoi(strData[0]);
	m_strName = strData[1];
	m_nTimeOut = _wtoi(strData[2]);
	m_nFalicontinue = _wtoi(strData[3]);
	

}