#ifndef __POWER_MANAGEMENT_SYSTEM_HMI_INTERFACE_H__
#define __POWER_MANAGEMENT_SYSTEM_HMI_INTERFACE_H__
#include "sys_defs.h"

#pragma pack(push, 1)

typedef struct tagHmiRecvHead
{
	DT_USHORT	usMsgCode;		// 메시지 코드
	DT_USHORT	usLength;		// 메시지 전체 크기

	DT_UINT		tmMsg;			// 메시지 송/수신 시각

	DT_UINT		nSeqId;			// 제어 ID	

	DT_USHORT	usSysId;		// 메시지 전송한 HMI ID
	DT_USHORT	usOperId;		// 운영자 ID
	DT_USHORT	usProgId;		// 메시지 전송한 프로그램 ID
	
	DT_USHORT	usCount;		// 데이터 레코드 개수.
} HmiRecvHead, HMIRECVHEAD, *LPHMIRECVHEAD;

typedef struct tagHmiSendHead
{
	DT_USHORT	usMsgCode;		// 메시지 코드
	DT_USHORT	usLength;		// 메시지 전체 크기

	DT_UINT		tmMsg;			// 메시지 송/수신 시각

	DT_UINT		nSeqId;			// 제어 ID	

	DT_USHORT	usSysId;		// 메시지 전송한 HMI ID
	DT_USHORT	usProgId;		// 메시지 전송한 프로그램 ID
	
	DT_USHORT	usCount;		// 데이터 레코드 개수.
} HmiSendHead, HMISENDHEAD, *LPHMISENDHEAD;


typedef struct tagHmiRcvPacket
{
	HmiRecvHead		packet_head;
	char*		   packet_data;
}HmiRcvPacket, HMIRCVPACKET, *LPHMIRCVPACKET;


typedef struct tagPointSelectCommand
{
	//DT_UINT		uiPid;			// 포인트 ID (ruid + index) 2014-02-13변경
	DT_UINT		uiRuId;
	DT_USHORT	usIdx;
	DT_USHORT	usTlq;			// 설정 TLQ
	DT_USHORT	usFlag;			// 1 = 설정, 0 = 해제
} Hmi_PointSel, HMI_POINTSEL, *LPHMI_POINTSEL;

typedef struct tagBinayOutCommand
{
	//DT_UINT		uiPid;			// 포인트 ID (ruid + index) 2014-02-13변경
	DT_UINT		uiRuId;
	DT_USHORT	usIdx;
	DT_BYTE		usval;			// 제어값
} Hmi_BoCommand, HMI_BOCOMMAND, *LPHMI_BOCOMMAND;

typedef struct tagAnalogOutCommand
{
	//DT_UINT		uiPid;			// 포인트 ID (ruid + index) 2014-02-13변경
	DT_UINT		uiRuId;
	DT_USHORT	usIdx;
	DT_FLOAT	fval;			// 제어값
} Hmi_Aocommand, HMI_AOCOMMAND, *LPHMI_APCOMMAND;

typedef struct tagRtuCommand
{
	DT_UINT		uiRuId;			// RemoteUnit ID
} Hmi_RtuCommand, HMI_RTUCOMMND, *LPHMI_RTUCOMMND; 

typedef struct tagLimitCommand
{
	DT_UINT		uiRuId;
	DT_USHORT	uiLimit;
	DT_FLOAT	fVal;
} Hmi_LimitCommand, HMI_LIMITCOMMAND, *LPHMI_LIMITCOMMAND ;

typedef struct tagControlResult
{
	DT_USHORT	usCode;
	DT_CHAR		szDesc[ERRORDESC_NAME_MAX_SZ];
} Hmi_ControlResult, HMI_CONTROLRESULT, *LPHMI_CONTROLRESULT;

typedef struct tagControlResultEx
{
	DT_USHORT	usCode;
} Hmi_ControlResultEx, HMI_CONTROLRESULTEX, *LPHMI_CONTROLRESULTEX;

typedef struct tagHmiUnsolCommand
{
	DT_UINT		uiRuId;
	DT_BYTE		byUnsol1;
	DT_BYTE		byUnsol2;
	DT_BYTE		byUnsol3;
} Hmi_UnsolCommand, HMI_UNSOLCOMMAND, *LPHMI_UNSOLCOMMAND;

typedef struct tagHmiWaveCommand
{
	DT_UINT		uiRuId;
	DT_CHAR		szFileName[WAVEFILE_NAME_MAX_SZ];
} Hmi_WaveCommand, HMI_WAVECOMMAND, *LPHMI_WAVECOMMAND;

typedef struct tagHmiWaveResult
{
	DT_USHORT	usCode;
	DT_CHAR		szFileName[WAVEFILE_NAME_MAX_SZ];
} Hmi_WaveResult, HMI_WAVERESULT, *LPHMI_WAVERESULT;

typedef struct tagHmiRtuConfig
{
	DT_UINT		uiRuId;//2014-02-07 조신연 추가
	DT_USHORT	usVal[32];
} Hmi_RtuConfig, HMI_RTUCONFIG, *LPHMI_RTUCONFIG;

typedef struct tagHmiLineStatus
{
	DT_UINT		uiCeqId;
	DT_BYTE		byState;
	DT_BYTE		byTieFlag;
} Hmi_LineStatus, HMI_LINESTATUS, *LPLINE_STATUS;


typedef struct tagHmiTlqSet
{
	//DT_UINT		uiPid;			// 포인트 ID (ruid + index) 2014-02-13변경
	DT_UINT		uiRuId;
	DT_USHORT	usIdx;
	DT_USHORT		usTlq;
	DT_USHORT		usSetVal;
} HmiTlqSet, HMITLQSET, *LPHMITLQSET;



#pragma pack(pop)
#endif	/* __POWER_MANAGEMENT_SYSTEM_HMI_INTERFACE_H__ */