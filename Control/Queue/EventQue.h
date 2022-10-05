// CirclarQue.h: interface for the CirclarQue class.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "Include/uPCGlobalC.h"
#include "../Control/Include/HMIFuncStruct.h"
#include "../Control/RDB/RDBMgr.h"

#ifndef _EVENTQUE_H
#define _EVENTQUE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BUFF_SIZE	20000

class CEventQue
{
public:

	EVENTDATA uPCNode[BUFF_SIZE];
	int m_iHead[HMI_APP_COUNT], m_iTail[HMI_APP_COUNT];
	CEventQue::CEventQue();
	CEventQue::~CEventQue();
	void Clear();
	int GetSize(int iApp);

	BOOL PutData(EVENTDATA *uPCData); //int aa); //
	BOOL GetData(EVENTDATA *puPCData, int iApp); //int *pAlarmData, int iApp); //
	void InitTail(int iApp);

	CRITICAL_SECTION		cs;					//!< Painting중 드로잉 버퍼 업데이트 방지
	void Lock() {::EnterCriticalSection(&cs);}
	void UnLock() {::LeaveCriticalSection(&cs);}
	void InitLock() {::InitializeCriticalSection(&cs);}
	void DeInitLock() {::DeleteCriticalSection(&cs);}
};
#endif