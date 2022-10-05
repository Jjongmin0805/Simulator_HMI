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
	// ------ ���� ���� ------- //
	UPC_Export int SetDeplexStatus(unsigned int nStatus, int nType = 1);
	UPC_Export int SetExecuteStatus(unsigned int nStatus, int nType = 1);

	// UPC_Export void close(); // ���� ���� ����(����)
	UPC_Export int Init(int nType = 0); // ���� �ʱ�ȭ (���̹� ���� �ʱ�ȭ)
	UPC_Export	void unInit();

	UPC_Export int GetCurrentOrbId(int nType = 0);

	UPC_Export int GetServiceInfo(eServiceNo nServiceNo, uPCComData& uData, int nType = 0);
	UPC_Export int GetPointInfo(eServiceNo nServiceNo, const char* pNameOfPoint, uPCComData& uData, int nType = 0);

	UPC_Export int MsgPointClear(eServiceNo nServiceNo, const char* pNameOfPoint, int nType = 0);
	UPC_Export int MsgPointUsage(eServiceNo nServiceNo, const char* pNameOfPoint, bool bEnable = true, int nType = 0);
	UPC_Export int GetPointNameList(eServiceNo nServiceNo, uPCPointNames& pNames, int nType = 0);
			
	// ------ �̺�Ʈ ����Ʈ ���� ------- //
	UPC_Export int SendEventData(uPCComData& pData, int nType = 0); // �̺�Ʈ ����
	UPC_Export int RecvEventData(const char* pNameOfPoint, uPCComData& pData, int nType = 0); // �̺�Ʈ ����
	//UPC_Export int RecvEventData(const char* pNameOfPoint, uPCComData*& pData, int nType = 0); // �̺�Ʈ ����
	
	UPC_Export int SendEventData(const char* pNameOfPoint, uPCComData& pData, int nType = 0); // �̺�Ʈ ����
	UPC_Export int DeleteEventData(const char* pNameOfPoint, int nType = 0); // �̺�Ʈ ����


	// ------ �޽��� ����Ʈ ���� ------- //
	UPC_Export int RecvMsgData(const char* pNameOfPoint, uPCComData& pData, int nType = 0);
	//UPC_Export int RecvMsgData(const char* pNameOfPoint, uPCComData*& pData, int nType = 0);
	UPC_Export int SendMsgData(const char* pNameOfPoint, uPCComData& pData, int nType = 0);
	UPC_Export int TotalHmiSendMsgData(uPCComData& pData, int nType = 0);	

	// ------ ACM ����Ʈ ���� ------- //
	UPC_Export int RecvAcmData(const char* pNameOfPoint, uPCComData& pData, int nType = 0);
	//UPC_Export int RecvAcmData(const char* pNameOfPoint, uPCComData*& pData, int nType = 0);
	UPC_Export int SendAcmData(const char* pNameOfPoint, uPCComData& pData, int nType = 0);

	// ------ ������ Ÿ�� ���� ------- //
	UPC_Export int GetDataType(const char* pNameOfPoint, uPCDataType& pData, int nType = 0);
	UPC_Export int GetDataType(const char* pNameOfPoint, uPCDataType*& pData, int nType = 0);
	UPC_Export int SetDataType(const char* pNameOfPoint, uPCComData& pData);
	UPC_Export uPCDataType* GetDataType(const char* pNameOfType);

	// ------ ������ ����Ʈ ���� ------- //
	UPC_Export int GetDataPoint(const char* pNameOfPoint, uPCComData*& uData, int nType = 0);
	UPC_Export int GetDataPoint(const char* pNameOfPoint, uPCComData& uData, int nType = 0);
	UPC_Export int PutDataPoint(const char* pNameOfPoint, uPCComData& uData, int nType = 0);

	// 2013�� 12�� 24��
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

	
	
	// ------ ���� ����Ʈ ���� ------- //
	UPC_Export int RecvPacketData(const char* pNameOfPoint, uPCComData& pData, unsigned int& pHandle, int nTimeOut, int nType = 0);
	//UPC_Export int RecvPacketData(const char* pNameOfPoint, uPCComData*& pData, unsigned int& pHandle, int nTimeOut, int nType = 0);
	UPC_Export int SendPacketData(const char* pNameOfPoint, uPCComData& pData, unsigned int& pHandle, int nTimeOut, int nType = 0);
	UPC_Export int RecvControlData(const char* pNameOfPoint, uPCComData& pData, int nTimeOut, int nType = 0);
	//UPC_Export int RecvControlData(const char* pNameOfPoint, uPCComData*& pData, int nTimeOut, int nType = 0);
	UPC_Export int SendControlData(const char* pNameOfPoint, uPCComData& pData, int nTimeOut, int nType = 0);
	UPC_Export int RecvAckData(const char* pNameOfPoint, uPCComData& pData, unsigned int pHandle, int nTimeOut, int nType = 0);
	UPC_Export int RecvAckData(const char* pNameOfPoint, uPCComData*& pData, unsigned int pHandle, int nTimeOut, int nType = 0);
	UPC_Export int SendAckData(const char* pNameOfPoint, uPCComData& pData, unsigned int pHandle, int nTimeOut, int nType = 0);


	// ------ ���̺귯�� ���� ------- //
	UPC_Export int GetServerList(PowerCubeServerList& lstServer);
	UPC_Export int GetLibraryVer(int &major, int &minor);
	UPC_Export void GetBuildDate(char* szDate);

	UPC_Export int GetServerMode();

#if 1
	UPC_Export int ReStartService(int nType = 1);
	UPC_Export int ServiceInitial(eServiceNo nServiceNo, int nType = 1);
#endif
}
