#pragma once
#ifndef __HMIFUNCSTRUCT_H__
#define __HMIFUNCSTRUCT_H__

#ifdef WIN64
#define DT_FLOAT	double
#else
#define	DT_FLOAT	float
#endif 

#ifndef __HMISTRUCT_H__
#include "HMIStruct.h"
#endif

enum ENUM_MW_FUNCCODE
{
	FC_TIMER				= 0x0001, //0.Ÿ�̸�üũ 	
	FC_PS_REQ				= 0x1001, //1.����Ʈ ���� �� ����
	FC_CTRL_REQ				= 0x1002, //2.����Ʈ ����
	FC_AO_SET_REQ			= 0x1003, //3.���� ���
	FC_EVENT_REQ			= 0x1004, //4.�̺�Ʈ ����
	FC_ALL_MEAS_REQ			= 0x1005, //5.��ü ����
	FC_BI_MEAS_REQ			= 0x1006, //6.Binary Input ���� - BO�� �������� ���� ���� �ʴ´� AI���� ����ϸ� ��
	FC_AI_MEAS_REQ			= 0x1007, //7.Analog Input ����
	FC_AO_MEAS_REQ			= 0x1008, //8.Analog Output ����	
	FC_PI_MEAS_REQ			= 0x1009, //9.Coount ����
	FC_WARM_RESTART			= 0x100A, //10.WARM RESTART
	FC_COLD_RESTART			= 0x100B, //11.Cold RESTART
	FC_SYNC_TIME			= 0x100C, //12.�ð�����ȭ
	FC_AI_LIMIT_REQ			= 0x100D, //13.Analog Point Limit ����
	FC_TLQ_REQ				= 0x100E, //14.TLQ ���� �� ����
	FC_UNSOL_REQ			= 0x100F, //15.Unsol Enable/Disable ����
	FC_WAVE_LIST_REQ		= 0x1010, //��������Ʈ ��û
	FC_WAVE_FILE_REQ		= 0x1011, //�������� ��û
	FC_OPR_DATA_REQ			= 0x1012, //����� ������ ��û
	FC_OPR_SET_REQ			= 0x1013, //����� ���� ��û
	FC_LINE_STATUS			= 0xFFFF, //�������� �������� ���� (����)
	FC_RTU_STATUS_REQ		= 0x1014, //���� �������� ��û
	FC_MANUAL_REQ		    = 0x1015, //���� �����Է� ��û

	FC_CTRL_VALID_RES		= 0x4001, //16.Control ��ȿ�� ���� ��� ����
	FC_CTRL_RESULT_RES		= 0x4002, //Control ��� ����(����Ʈ ����, ����Ʈ���� ��ɰ��, Cold, Warm Restart, �ð�����ȭ)
	FC_WAVE_LIST_RES		= 0x4003, //��������Ʈ ���ſϷ� ����
	FC_WAVE_FILE_RES		= 0x4004, //�������� ���ſϷ� ����
	FC_OPR_DATA_RES			= 0x4005, //����� ������ ���ſϷ� ����(����� ���)
	FC_RTU_STATUS_RES		= 0x4006, //���� �������� ����(��Ȱ�� ������ ���� ����)

	FC_MSG_UPDATE			= 0xA001, //�������� ������Ʈ ��û
	FC_CONTRUCT_UPDATE		= 0xA002, //�۾����� ������Ʈ ��û
	FC_MEMO_UPDATE			= 0xA003, //�޸���� ������Ʈ ��û
	FC_CONTROL_UPDATE		= 0xA004, //������� ������Ʈ ��û
	FC_DFD_UPDATE			= 0xA008, //DFD �Ǵ� ���ġ ����
	FC_DSR_UPDATE			= 0xA009,  //DSR ���ġ ����
	FC_EMERGENCY_MSG_UPDATE	= 0xA00A //��ް������� ������Ʈ ��û
};

#pragma pack(1)
//�̵���� �۽� ��Ŷ ���
typedef struct __stSendHeader__
{
	USHORT	usFcode;			//!< Function Code
	USHORT	usLength;			//!< �޽��� �ѱ���
	UINT	uiTime;				//!< HMI ���۽ð�(__time32_t����)
	UINT	uiSeqId;			//!< HMI���� ������ ������ ID
	USHORT	usHmiId;			//!< ȯ�漳�� ���Ͽ� ���ǵ� HMI ID
	USHORT	usOperatorId;		//!< ��ɿ� ID
	USHORT	usProgId;			//!< ���α׷� ID
	USHORT	usCount;			//!< ���ڵ� ����
} ST_SENDHEADER, *LPST_SENDHEADER;

//�̵���� �񵿱�۽� ��Ŷ ���
typedef struct __stSendHeader2__
{
	USHORT	usFcode;			//!< Function Code
	USHORT	usLength;			//!< �޽��� �ѱ���
	UINT	uiTime;				//!< HMI ���۽ð�(__time32_t����)
	UINT	uiSeqId;			//!< HMI���� ������ ������ ID
	USHORT	usHmiId;			//!< ȯ�漳�� ���Ͽ� ���ǵ� HMI ID	
	USHORT	usProgId;			//!< ���α׷� ID
	USHORT	usCount;			//!< ���ڵ� ����
} ST_SENDHEADER2, *LPST_SENDHEADER2;

//�̵���� ���� ��Ŷ ���
typedef struct __stRecvHeader__
{
	USHORT	usFcode;			//!< Function Code
	USHORT	usLength;			//!< �޽��� �ѱ���
	UINT	uiTime;				//!< HMI ���۽ð�(__time32_t����)
	UINT	uiSeqId;			//!< HMI���� ������ ������ ID
	USHORT	usHmiId;			//!< ȯ�漳�� ���Ͽ� ���ǵ� HMI ID
	//USHORT	usOperatorId;		//!< ��ɿ� ID
	USHORT	usProgId;			//!< ���α׷� ID
	USHORT	usCount;			//!< ���ڵ� ����
} ST_RECVHEADER, *LPST_RECVHEADER;

//1.����Ʈ ���� �� ����
//14. TLQ ���� �� ����
typedef struct __stPS_REQ__
{
	UINT		uipid;			//PID
	USHORT		usPtType;		//!< ����Ʈ Ÿ�� - ���ѹ� �̻� �߰� 2013-03-18
	USHORT		usIndex;		//Index ID
	USHORT		usSetTLQ;		//TLQ
	USHORT		usSetOrRel;		//����(1), ����(0)
} ST_PS_REQ, *LPST_PS_REQ;

typedef struct __stTLQ_REQ__
{
	UINT		uipid;			//PID
	USHORT		usPtType;		//!< ����Ʈ Ÿ�� - ���ѹ� �̻� �߰� 2013-03-18
	USHORT		usIndex;		//Index ID
	USHORT		usSetTLQ;		//TLQ
	USHORT		usSetOrRel;		//����(1), ����(0)
} ST_TLQ_REQ, *LPST_TLQ_REQ;

//2.����Ʈ ���� �� ����
typedef struct __stCTRL_REQ__
{
	UINT		uipid;			//<!DMS�������� ������ ������ ����Ʈ�� ����ID ������ 0
	//USHORT		usPtType;		//!< ����Ʈ Ÿ�� - ���ѹ� �̻� �߰� 2013-03-18
	USHORT		usIndex;		//Index ID
	UCHAR		ucCtrl_Val;		//<!������ ���°�
} ST_CTRL_REQ, *LPST_CTRL_REQ;

//3.�������
typedef struct __stAO_SET_REQ__
{
	UINT		uipid;			//<!DMS�������� ������ ������ ����Ʈ�� ����ID ������ 0
	USHORT		uiIndex;		//Index ID
	FLOAT		fCtrl_Val;		//<!������ ���°�
} ST_AO_SET_REQ, *LPST_AO_SET_REQ;

//4.�̺�Ʈ����
//5.��ü����
//6.Binary Input ����
//7.Analog Input ����
//8.Analog Output ����
//9.COUNT ����
//10. Warm Restart
//11. Cold Restart
//12. �ð�����ȭ
typedef struct __stEVENT_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count ������ŭ RUID ����
} ST_EVENT_REQ, *LPST_EVENT_REQ;

typedef struct __stALLMEAS_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count ������ŭ RUID ����
} ST_ALLMEAS_REQ, *LPST_ALLMEAS_REQ;

typedef struct __stBIMEAS_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count ������ŭ RUID ����
} ST_BIMEAS_REQ, *LPST_BIMEAS_REQ;

typedef struct __stAIMEAS_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count ������ŭ RUID ����
} ST_AIMEAS_REQ, *LPST_AIMEAS_REQ;

typedef struct __stAOMEAS_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count ������ŭ RUID ����
} ST_AOMEAS_REQ, *LPST_AOMEAS_REQ;

typedef struct __stCOUNTMEAS_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count ������ŭ RUID ����
} ST_COUNTMEAS_REQ, *LPST_COUNTMEAS_REQ;

typedef struct __stWARM_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count ������ŭ RUID ����
} ST_WARM_REQ, *LPST_WARM_REQ;

typedef struct __stCOLD_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count ������ŭ RUID ����
} ST_COLD_REQ, *LPST_COLD_REQ;

typedef struct __stTIME_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count ������ŭ RUID ����
} ST_TIME_REQ, *LPST_TIME_REQ;

//13. Analog Point limit ����
typedef struct __stAI_LIMIT_REQ__
{
	UINT		uiRuId;			//<!DMS�������� ������ ������ ����Ʈ�� ����ID ������ 0
	USHORT		usIndex;		//Index ID
	USHORT		usLimitId;		//!< R_MAX, R_MIN, L_MAX, L_MIN
	FLOAT		fLimitValue;	//!< ���� limit ��
} ST_AI_LIMIT_REQ, *LPST_AI_LIMIT_REQ;

//15. Unsol Enable/Disable ��û
typedef struct __stUNSOL_REQ__
{
	UINT		uiRuId;			//<! DMS�������� ������ ������ ����Ʈ�� ����ID ������ 0
	UCHAR		ucUnsol_c1;		//!< Class1 Enable=1 / Disable=0
	UCHAR		ucUnsol_c2;		//!< Class2 Enable=1 / Disable=0
	UCHAR		ucUnsol_c3;		//!< Class3 Enable=1 / Disable=0

} ST_UNSOL_REQ, *LPST_UNSOL_REQ;

//16. Control ���� ���(���� Validation üũ ���)
//17. ������ ��� ����
typedef struct __stRESULT_RES__
{
	USHORT		usErrorCode;			//<! �����ڵ�(RDB�� �����ڵ� ���̺� ����)
	CHAR		Desc[32];			//!< ��������
} ST_RESULT_RES, *LPST_RESULT_RES;

//47. ��������Ʈ ��û
//48. �������� ��û
typedef struct __stWAVE_REQ__
{
	UINT		uiRuId;					//<! RTUDevice ID, Count ������ŭ RUID ����
	CHAR		szWaveName[16];			//!< WAVE_INFO, ���������̸�
} ST_WAVE_REQ, *LPST_WAVE_REQ;

//49. ��������Ʈ ���Ű��
//50. �������� ���Ű��
typedef struct __stWAVE_RES__
{
	UINT		uiResultCode;			//<! RTUDevice ID, Count ������ŭ RUID ����
	CHAR		szWaveName[16];			//!< WAVE_INFO, ���������̸�
} ST_WAVE_RES, *LPST_WAVE_RES;


//51. ����������� ��û
typedef struct __stOPR_DATA_REQ__
{
	UINT		uiRuId;						//<! RTUDevice ID, Count ������ŭ RUID ����
	CHAR		szConfigName[16];			//!< CONFIG_Name ���� ���� �̸�
} ST_OPR_DATA_REQ, *LPST_OPR_DATA_REQ;

//52. ����������� ������û
typedef struct __stOPR_SET_REQ__
{
	UINT		uiRuId;						//<! RTUDevice ID, Count ������ŭ RUID ����
	BYTE		bySettingVlaue[64];			//!< 64byte(2 * 32Index) �� ����
} ST_OPR_SET_REQ, *LPST_OPR_SET_REQ;

//56. ����� ������ ���� ���
typedef struct __stOPR_DATA_RES__
{
	USHORT		usResultCode;				//<!�����ڵ�(RDB�� �����ڵ� ���̺� ����)
} ST_OPR_DATA_RES, *LPST_OPR_DATA_RES;

//57. �������� ���� ��������
typedef struct __stLINE_STATUS_RES__
{
	UINT		nCeqId;					//<! �������� CEQID
	UINT		nSTatus;				//<! ���λ���(1=�缱, 2= Ȱ��)
	UINT		nTie;					//!< ���豸��(1), �ڱⱸ��(0)
} ST_LINE_STATUS_RES, *LPST_LINE_STATUS_RES;

//58. ��������
//59. �۾�����
//60. �޸����
typedef struct __stHMI_UPDATE_
{
	USHORT		usFcode;			//!< Function Code
	UINT		uiLength;			//!< �޽��� �ѱ���
	__time32_t	uiTime;				//!< HMI ���۽ð�(__time32_t����)
} ST_HMI_UPDATE, *LPST_HMI_UPDATE;

//62. ����������� ��û
// ������ ����(��ɸ� ����)

//16. control ���� ���
typedef struct __stCTRL_VALID_
{
	//UINT	uiSeqId;				//!< HMI���� ������ ������ ID - ��û�� ������ �´� �� Ȯ���ϴ� �� ���(��û�� �Էµ�)
	USHORT	uiErrorCode;			//!< ���� �ڵ�
	char	szErrDesc[32];			//!< ���� ����
} ST_CTRL_VALID, *LPST_CTRL_VALID;

//17. ������ ��� ����
typedef struct __stCTRL_RESULT_
{
	//UINT	uiSeqId;				//!< HMI���� ������ ������ ID - ��û�� ������ �´� �� Ȯ���ϴ� �� ���(��û�� �Էµ�)
	USHORT	uiErrorCode;			//!< ���� �ڵ�
	char	szErrDesc[32];			//!< ���� ����
} ST_CTRL_RESULT, *LPST_CTRL_RESULT;

//41. ���� ����Ʈ ��� ����
typedef struct __stWAVE_LIST_
{
	//UINT	uiSeqId;				//!< HMI���� ������ ������ ID - ��û�� ������ �´� �� Ȯ���ϴ� �� ���(��û�� �Էµ�)
	USHORT	uiResult;				//!< 0:OK, 1:Doesn't exist, 4:File Busy, 5:��Ž��� 
	char	szWaveList[16];			//!< ���� ����Ʈ
} ST_WAVE_LIST, *LPST_WAVE_LIST;

//41. ���� ���� ��� ����
typedef struct __stWAVE_FILE_
{
	//UINT	uiSeqId;				//!< HMI���� ������ ������ ID - ��û�� ������ �´� �� Ȯ���ϴ� �� ���(��û�� �Էµ�)
	USHORT	uiResult;				//!< 0:OK, 1:Doesn't exist, 4:File Busy, 5:��Ž��� 
	char	szWaveFile[16];			//!< ���ϸ�
} ST_WAVE_FILE, *LPST_WAVE_FILE;

//55. ����� ���
typedef struct __stOPR_DATA_RESULT_
{
	//UINT	uiSeqId;				//!< HMI���� ������ ������ ID - ��û�� ������ �´� �� Ȯ���ϴ� �� ���(��û�� �Էµ�)
	USHORT	uiResult;				//!< 0:OK, 1:Doesn't exist, 4:File Busy, 5:��Ž��� 
} ST_OPR_DATA_RESULT, *LPST_OPR_DATA_RESULT;

//61. ��������������� : ��Ȱ/���� ����
typedef struct __stRTU_STATUS_
{
	//UINT	uiSeqId;				//!< HMI���� ������ ������ ID - ��û�� ������ �´� �� Ȯ���ϴ� �� ���(��û�� �Էµ�)
	UINT	uiCeqId;				//!< CEQID
	UCHAR	ucState;				//!< (1=Live, 2=Outage, 3=���屸��(����))
	UINT	uiOnlineDL;				//!< �ǽð� DL ID
	UCHAR	ucTieState;				//!< ���豸��(1), �ڱⱸ��(0)
	UCHAR	ucTieSwflag;			//!< ��ð�����(1), Other(0), ����ġ�� ��쿡��
	
} ST_RTU_STATUS, *LPST_RTU_STATUS;

//62. �����Է� ��û
typedef struct __stMANUAL_REQ_
{	
	UINT	uiRuId;					//!< RTU ID
	USHORT	usPtType;				//!< ����Ʈ Ÿ�� BI(1),AI(3),PI(5)
	USHORT	usIndex;				//Index ID
	FLOAT	fSetValue;				//����������
	
} ST_MANUAL_REQ, *LPST_MANUAL_REQ;

typedef struct _tagASYNCDATA
{
	ST_RECVHEADER stRecvHeader;
	BYTE	ucData[4096];

}ASYNCDATA, *PASYNCDATA;

///���� Ȯ�� �ʿ�
typedef struct _tagEVENTDATA
{
	char	evtId[24];		//!< �̺�Ʈ ��ȣ
	USHORT	evnet_code;		//!< �̺�Ʈ �ڵ�
	INT		SoeTime;		//!< RTU �ð� SEC
	USHORT	SoeTime_ms;		//!< RTU �ð� ms
	INT		EvtTime;		//!< ���� �ð� SEC
	USHORT	EvtTime_ms;		//!< ���� �ð� ms
	INT		GGRID;			//!< ����(����)�ڵ�
	INT		SGRID;			//!< ����(�����)�ڵ�
	INT		SSID;			//!< ������ �ڵ�
	INT		DLID;			//!< DL ID
	INT		CEQID;			//!< CEQ ID
	INT		RUID;			//!< RTUDevice ID
	INT		PtType;			//!< ����Ʈ Ÿ��
	INT		PID;			//!< ����Ʈ ��ȣ
	USHORT	Index;			//!< DNP �ε��� ��ȣ
	FLOAT	Value;			//!< ����Ʈ ��
	FLOAT	OldValue;		//!< ���� ��
	BYTE	Alarm;			//!< Alarm ����
	BYTE	Important;		//!< �߿� �˶�
	USHORT	Tlq;			//!< TLQ ��	
	char	message[128];	//!< �̺�Ʈ ����

}EVENTDATA, *PEVENTDATA;

typedef struct _tagVIEWEVENTDATA
{
	EVENTDATA	eventData;
	TCHAR		stationname[32];
	TCHAR		dlname[32];
	TCHAR		eqname[64];
	TCHAR		ptname[64];

}VIEWEVENTDATA, *PVIEWEVENTDATA;
#endif	// __HMIFUNCSTRUCT_H__