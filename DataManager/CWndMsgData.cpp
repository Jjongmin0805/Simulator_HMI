#include "pch.h"
#include "CWndMsgData.h"


CWndMsgData::CWndMsgData()
{
	m_nAppl_id = -1;
	m_nOption = -1;
	m_nEquipType = -1;
	m_nIndex = -1;
	m_strData.Empty();
}

CWndMsgData::~CWndMsgData()
{

}

void CWndMsgData::SetData(CString strRecvData)
{
	CString strTok;
	CString strData[3];

	int nCnt = 0;
	while (AfxExtractSubString(strTok, strRecvData, nCnt, _T(',')))
	{
		strData[nCnt] = strTok;
		nCnt++;
	}

	m_nAppl_id = _wtoi(strData[0]);
	m_nOption = _wtoi(strData[1]);
	m_strData = strData[2];
}