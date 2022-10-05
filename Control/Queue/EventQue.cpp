
#include "stdafx.h"
#include "EventQue.h"

CEventQue::CEventQue()
{
	Clear();
	InitLock();
}
CEventQue::~CEventQue()
{
	DeInitLock();
	Clear();
}
void CEventQue::Clear()
{
	memset(uPCNode, 0, sizeof(EVENTDATA) *BUFF_SIZE);
	memset(m_iHead, 0, sizeof(int)*HMI_APP_COUNT);
	memset(m_iTail, 0, sizeof(int)*HMI_APP_COUNT);
}

int CEventQue::GetSize(int iApp)
{
	int nSize = 0;
	
	//queue�� Full�϶� Head�� Front�� �̵�
	nSize = m_iHead[HMI_QUEUE] - m_iTail[iApp];
	if(nSize < 0)
		nSize = BUFF_SIZE + nSize;

	return nSize;
}
BOOL CEventQue::PutData(EVENTDATA *uPCData) //int alarmData) /
{
Lock();
	EVENTDATA *data = new EVENTDATA;
	memcpy(data, uPCData, sizeof(EVENTDATA));
	//Head�� Queue�� �������� �� ���
	if((m_iHead[HMI_QUEUE]+1) > BUFF_SIZE)
	{
		m_iHead[0] = 0;
		//uPCNode[m_iHead[0]] = data;
		memcpy(&uPCNode[m_iHead[HMI_QUEUE]], data, sizeof(EVENTDATA));
	}
	else
	{
		memcpy(&uPCNode[m_iHead[HMI_QUEUE]++], data, sizeof(EVENTDATA));
		//uPCNode[m_iHead[0]++] = data;
		//CString result;
		//result.Format(_T("%d"),uPCNode[m_iHead[HMI_QUEUE]].pid);
		//TRACE("Input ��� : %s\r\n", result);
	}
	delete data;
UnLock();
	return TRUE;
}
BOOL CEventQue::GetData(EVENTDATA *puPCData, int iApp) //int *pAlarmData, int iApp) /
{

	//Tail�� ���� ��ġ���� ���
	if(GetSize(iApp) == 0) 	return FALSE;

	//������ �Է���ġ���� ���� ��ġ�� Ŭ ��� - ������ �Է��� ���� ���
	if(m_iHead[HMI_QUEUE] == m_iTail[iApp])
		return FALSE;
Lock();
	if((m_iTail[iApp]+1) > BUFF_SIZE)
	{
		//*puPCData = (char*)uPCNode[m_iTail[iApp]];
		memcpy(puPCData,&uPCNode[m_iTail[iApp]], sizeof(EVENTDATA));
		m_iTail[iApp] = 0;
	}
	else
	{
		//*puPCData = (char*)uPCNode[m_iTail[iApp]++];
		memcpy(puPCData, &uPCNode[m_iTail[iApp]], sizeof(EVENTDATA));
		m_iTail[iApp]++;

	}
UnLock();	
	return TRUE;
}
void CEventQue::InitTail(int iApp)
{
	m_iTail[iApp] = m_iHead[iApp];
}