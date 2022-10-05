// CirclarQue.h: interface for the CirclarQue class.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "Include/uPCGlobalC.h"
#include "../Control/Include/HMIFuncStruct.h"
#include "../Control/RDB/RDBMgr.h"

#ifndef _ASYNCQUE_H
#define _ASYNCQUE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ASYN_BUFF_SIZE	5000

class CAsyncQue
{
public:

	ASYNCDATA uPCNode[ASYN_BUFF_SIZE];
	int m_iHead[HMI_APP_COUNT], m_iTail[HMI_APP_COUNT];
	CAsyncQue::CAsyncQue();
	CAsyncQue::~CAsyncQue();
	void Clear();
	int GetSize(int iApp);

	BOOL PutData(ASYNCDATA *uPCData); //int aa); //
	BOOL GetData(ASYNCDATA *puPCData, int iApp); //int *pAlarmData, int iApp); //

	CRITICAL_SECTION		cs;					//!< Painting중 드로잉 버퍼 업데이트 방지
	void Lock() {::EnterCriticalSection(&cs);}
	void UnLock() {::LeaveCriticalSection(&cs);}
	void InitLock() {::InitializeCriticalSection(&cs);}
	void DeInitLock() {::DeleteCriticalSection(&cs);}
};
#endif