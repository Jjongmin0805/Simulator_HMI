#pragma once

#include "uPCTypeDefC.h"

#ifndef UPC_Export
#ifdef UPC_DLL_EXPORTS
#define UPC_Export __declspec(dllexport)
#else
#define UPC_Export __declspec(dllimport)
#endif
#endif

class uPCComData;
class uPCDataType;

namespace uPCClientCom
{
	// ------ 공통 서비스 ------- //
	UPC_Export int SetDeplexStatus(unsigned int nStatus, int nType = 1);
	UPC_Export int SetExecuteStatus(unsigned int nStatus, int nType = 1);

	// UPC_Export void close(); // 서비스 접속 종료(삭제)
	UPC_Export int Init(int nType = 0); // 서비스 초기화 (네이밍 서비스 초기화)
	UPC_Export	void unInit();

	UPC_Export int GetCurrentOrbId(int nType = 0);

	UPC_Export int GetServiceInfo(eServiceNo nServiceNo, uPCComData& uData, int nType = 0);
	UPC_Export int GetPointInfo(eServiceNo nServiceNo, const char* pNameOfPoint, uPCComData& uData, int nType = 0);

	UPC_Export int MsgPointClear(eServiceNo nServiceNo, const char* pNameOfPoint, int nType = 0);
	UPC_Export int MsgPointUsage(eServiceNo nServiceNo, const char* pNameOfPoint, bool bEnable = true, int nType = 0);
	UPC_Export int GetPointNameList(eServiceNo nServiceNo, uPCPointNames& pNames, int nType = 0);
			
	// ------ 이벤트 포인트 서비스 ------- //
	UPC_Export int SendEventData(uPCComData& pData, int nType = 0); // 이벤트 전송
	UPC_Export int RecvEventData(const char* pNameOfPoint, uPCComData& pData, int nType = 0); // 이벤트 수신
	//UPC_Export int RecvEventData(const char* pNameOfPoint, uPCComData*& pData, int nType = 0); // 이벤트 수신
	
	UPC_Export int SendEventData(const char* pNameOfPoint, uPCComData& pData, int nType = 0); // 이벤트 전송
	UPC_Export int DeleteEventData(const char* pNameOfPoint, int nType = 0); // 이벤트 수신


	// ------ 메시지 포인트 서비스 ------- //
	UPC_Export int RecvMsgData(const char* pNameOfPoint, uPCComData& pData, int nType = 0);
	//UPC_Export int RecvMsgData(const char* pNameOfPoint, uPCComData*& pData, int nType = 0);
	UPC_Export int SendMsgData(const char* pNameOfPoint, uPCComData& pData, int nType = 0);
	UPC_Export int TotalHmiSendMsgData(uPCComData& pData, int nType = 0);	

	// ------ ACM 포인트 서비스 ------- //
	UPC_Export int RecvAcmData(const char* pNameOfPoint, uPCComData& pData, int nType = 0);
	//UPC_Export int RecvAcmData(const char* pNameOfPoint, uPCComData*& pData, int nType = 0);
	UPC_Export int SendAcmData(const char* pNameOfPoint, uPCComData& pData, int nType = 0);

	// ------ 데이터 타입 서비스 ------- //
	UPC_Export int GetDataType(const char* pNameOfPoint, uPCDataType& pData, int nType = 0);
	UPC_Export int GetDataType(const char* pNameOfPoint, uPCDataType*& pData, int nType = 0);
	UPC_Export int SetDataType(const char* pNameOfPoint, uPCComData& pData);
	UPC_Export uPCDataType* GetDataType(const char* pNameOfType);

	// ------ 데이터 포인트 서비스 ------- //
	UPC_Export int GetDataPoint(const char* pNameOfPoint, uPCComData*& uData, int nType = 0);
	UPC_Export int GetDataPoint(const char* pNameOfPoint, uPCComData& uData, int nType = 0);
	UPC_Export int PutDataPoint(const char* pNameOfPoint, uPCComData& uData, int nType = 0);

	// 2013년 12월 24일
	UPC_Export int PutDataPointOfUnitName(const char* pNameOfPoint, const char* pUnitName, uPCComData& uData, int nType = 0);
	UPC_Export int GetDataPointOfUnitName(const char* pNameOfPoint, const char* pUnitName, uPCComData& uData, int nType = 0);

	UPC_Export int PutDataPointOfUnitName(const char* pNameOfPoint, const char* pUnitName, unsigned int iValue, int nType = 0);
	UPC_Export int PutDataPointOfUnitName(const char* pNameOfPoint, const char* pUnitName, int uiValue, int nType = 0);
	UPC_Export int PutDataPointOfUnitName(const char* pNameOfPoint, const char* pUnitName, unsigned short usValue, int nType = 0);
	UPC_Export int PutDataPointOfUnitName(const char* pNameOfPoint, const char* pUnitName, short sValue, int nType = 0);
	UPC_Export int PutDataPointOfUnitName(const char* pNameOfPoint, const char* pUnitName, unsigned char usValue, int nType = 0);
	UPC_Export int PutDataPointOfUnitName(const char* pNameOfPoint, const char* pUnitName, char sValue, int nType = 0);
	UPC_Export int PutDataPointOfUnitName(const char* pNameOfPoint, const char* pUnitName, float fValue, int nType = 0);
	UPC_Export int PutDataPointOfUnitName(const char* pNameOfPoint, const char* pUnitName, double dfValue, int nType = 0);

	
	
	// ------ 제어 포인트 서비스 ------- //
	UPC_Export int RecvPacketData(const char* pNameOfPoint, uPCComData& pData, unsigned int& pHandle, int nTimeOut, int nType = 0);
	//UPC_Export int RecvPacketData(const char* pNameOfPoint, uPCComData*& pData, unsigned int& pHandle, int nTimeOut, int nType = 0);
	UPC_Export int SendPacketData(const char* pNameOfPoint, uPCComData& pData, unsigned int& pHandle, int nTimeOut, int nType = 0);
	UPC_Export int RecvControlData(const char* pNameOfPoint, uPCComData& pData, int nTimeOut, int nType = 0);
	//UPC_Export int RecvControlData(const char* pNameOfPoint, uPCComData*& pData, int nTimeOut, int nType = 0);
	UPC_Export int SendControlData(const char* pNameOfPoint, uPCComData& pData, int nTimeOut, int nType = 0);
	UPC_Export int RecvAckData(const char* pNameOfPoint, uPCComData& pData, unsigned int pHandle, int nTimeOut, int nType = 0);
	UPC_Export int RecvAckData(const char* pNameOfPoint, uPCComData*& pData, unsigned int pHandle, int nTimeOut, int nType = 0);
	UPC_Export int SendAckData(const char* pNameOfPoint, uPCComData& pData, unsigned int pHandle, int nTimeOut, int nType = 0);


	// ------ 라이브러리 정보 ------- //
	UPC_Export int GetServerList(PowerCubeServerList& lstServer);
	UPC_Export int GetLibraryVer(int &major, int &minor);
	UPC_Export void GetBuildDate(char* szDate);

	UPC_Export int GetServerMode();

#if 1
	UPC_Export int ReStartService(int nType = 1);
	UPC_Export int ServiceInitial(eServiceNo nServiceNo, int nType = 1);
#endif
}
