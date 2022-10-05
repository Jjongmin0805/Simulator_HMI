#ifndef __POWER_MANAGEMENT_SYSTEM_HMI_INTERFACE_H__
#define __POWER_MANAGEMENT_SYSTEM_HMI_INTERFACE_H__
#include "sys_defs.h"

#pragma pack(push, 1)

typedef struct tagHmiRecvHead
{
	DT_USHORT	usMsgCode;		// �޽��� �ڵ�
	DT_USHORT	usLength;		// �޽��� ��ü ũ��

	DT_UINT		tmMsg;			// �޽��� ��/���� �ð�

	DT_UINT		nSeqId;			// ���� ID	

	DT_USHORT	usSysId;		// �޽��� ������ HMI ID
	DT_USHORT	usOperId;		// ��� ID
	DT_USHORT	usProgId;		// �޽��� ������ ���α׷� ID
	
	DT_USHORT	usCount;		// ������ ���ڵ� ����.
} HmiRecvHead, HMIRECVHEAD, *LPHMIRECVHEAD;

typedef struct tagHmiSendHead
{
	DT_USHORT	usMsgCode;		// �޽��� �ڵ�
	DT_USHORT	usLength;		// �޽��� ��ü ũ��

	DT_UINT		tmMsg;			// �޽��� ��/���� �ð�

	DT_UINT		nSeqId;			// ���� ID	

	DT_USHORT	usSysId;		// �޽��� ������ HMI ID
	DT_USHORT	usProgId;		// �޽��� ������ ���α׷� ID
	
	DT_USHORT	usCount;		// ������ ���ڵ� ����.
} HmiSendHead, HMISENDHEAD, *LPHMISENDHEAD;


typedef struct tagHmiRcvPacket
{
	HmiRecvHead		packet_head;
	char*		   packet_data;
}HmiRcvPacket, HMIRCVPACKET, *LPHMIRCVPACKET;


typedef struct tagPointSelectCommand
{
	//DT_UINT		uiPid;			// ����Ʈ ID (ruid + index) 2014-02-13����
	DT_UINT		uiRuId;
	DT_USHORT	usIdx;
	DT_USHORT	usTlq;			// ���� TLQ
	DT_USHORT	usFlag;			// 1 = ����, 0 = ����
} Hmi_PointSel, HMI_POINTSEL, *LPHMI_POINTSEL;

typedef struct tagBinayOutCommand
{
	//DT_UINT		uiPid;			// ����Ʈ ID (ruid + index) 2014-02-13����
	DT_UINT		uiRuId;
	DT_USHORT	usIdx;
	DT_BYTE		usval;			// ���
} Hmi_BoCommand, HMI_BOCOMMAND, *LPHMI_BOCOMMAND;

typedef struct tagAnalogOutCommand
{
	//DT_UINT		uiPid;			// ����Ʈ ID (ruid + index) 2014-02-13����
	DT_UINT		uiRuId;
	DT_USHORT	usIdx;
	DT_FLOAT	fval;			// ���
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
	DT_UINT		uiRuId;//2014-02-07 ���ſ� �߰�
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
	//DT_UINT		uiPid;			// ����Ʈ ID (ruid + index) 2014-02-13����
	DT_UINT		uiRuId;
	DT_USHORT	usIdx;
	DT_USHORT		usTlq;
	DT_USHORT		usSetVal;
} HmiTlqSet, HMITLQSET, *LPHMITLQSET;



#pragma pack(pop)
#endif	/* __POWER_MANAGEMENT_SYSTEM_HMI_INTERFACE_H__ */