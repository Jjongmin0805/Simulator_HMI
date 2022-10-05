#ifndef _DEFINE_H
#define _DEFINE_H

#pragma warning (disable: 4482)
#pragma warning (disable: 4996)
#pragma warning (disable: 4800)

// ��ũ���Լ� ����
#define _N(x)							_T(x)_T("\r\n")

// Config ���� ����
#define	LOG_NOTHING						0		// �αױ�� ����
#define	LOG_INFO						1		// INFO �α�
#define	LOG_FULL						2		// FULL �α�
#define ACM_NOT_USE						0		// ACM ������
#define ACM_USE							1		// ACM ���
#define LANGUAGE_KOR					0		// �ѱ��� ���
#define LANGUAGE_ENG					1		// ���� ���

// Login ���ϰ� ����
#define LOGIN_CANCEL					0		// �α��� ���
#define LOGIN_SUCCESS					1		// �α��� ����

// üũ�ڽ� ��������
#define CHECKBOX_NORMAL					0		// üũ�ڽ� üũ�ȵȻ���
#define CHECKBOX_CHECKED				1		// üũ�ڽ� üũ�Ȼ���
#define CHECKBOX_DISABLE				2		// üũ�ڽ� üũ���ϴ»���

// �˾�â ���ϰ� ����
#define POPUP_RET_CANCEL				0		// �˾�â ��� ���ϸ޼���
#define	POPUP_RET_INPUT					1		// �˾�â �Է� ���ϸ޼���
#define	POPUP_RET_MODIFY				2		// �˾�â ���� ���ϸ޼���
#define	POPUP_RET_DELETE				3		// �˾�â ���� ���ϸ޼���
#define	POPUP_RET_CONTROL				4		// �˾�â ���� ���ϸ޼���
#define	POPUP_RET_CONTROL_DATA_FAIL		5		// �˾�â ���� ����Ÿ��Ŷ �������ϸ޼���
#define	POPUP_RET_CONTROL_ACK_FAIL		6		// �˾�â ���� �������� �������ϸ޼���

// �������� �޼�������
#define HMI_MESSAGE_EMERGENCY			1		// ���
#define HMI_MESSAGE_NORMAL				2		// ����

// ��ɿ� ���Ѱ��� ASSIGNTYPE ����
#define OPR_ASSIGNTYPE_SUBGEO			0		// �����
#define OPR_ASSIGNTYPE_SUBSTA			1		// ������
#define OPR_ASSIGNTYPE_DL				2		// DL

// ���μ����� ��� �޼��� ����
#define PROCESS_END_MESSAGE				1		// ���μ��� ����޼���
#define PROCESS_USERCHG_MESSAGE			2		// �α��� ����ں��� �޼���
#define PROCESS_TOTAL_REFRESH_MSG	    3		// �������� RTU���� ���� �޼���
#define MOVE_MAIN_TO_LINE_MESSAGE		4		// ���뵵 - �ܼ��� �̵� �޽���
#define MOVE_MAIN_TO_TOTAL_MESSAGE		5		// ���뵵 - ����ȭ�� �̵� �޽���
#define MOVE_TOTAL_TO_MAIN_MESSAGE		6		// ����ȭ�� - ���뵵 �̵� �޽���
#define MOVE_TOTAL_TO_LINE_MESSAGE		7		// ����ȭ�� - �ܼ��� �̵� �޽���
#define MOVE_LINE_TO_MAIN_MESSAGE		8		// �ܼ��� - ���뵵 �̵� �޽���
#define MOVE_LINE_TO_TOTAL_MESSAGE		9		// �ܼ��� - ����ȭ�� �̵� �޽���
#define MOVE_MAIN_TO_CTRL_MESSAGE	   10		// ���뵵 - ����â �̵� �޽���
#define MOVE_TOTAL_TO_CTRL_MESSAGE	   11		// ����ȭ�� - ����â �̵� �޽���
#define MOVE_LINE_TO_CTRL_MESSAGE	   12		// �ܼ��� - ����â �̵� �޽���
#define MOVE_ACM_MESSAGE			   13		// ACM �̵� �޽���
#define PROCESS_PAUSE				   14		// ��� ���μ��� �ߴ�
#define PROCESS_RESTART				   15		// ��� ���μ��� ��⵿
#define BLINKING_STOP				   16		// ����â - ���뵵,�ܼ��� ���� ���� ������ ����
#define WAVE_SOUND_ONOFF_MESSAGE	   17		// �˶� �Ҹ� ����/�ѱ� ���� �޽���
#define PROCESS_LINE_REFRESH_MSG	   18		// �ܼ��� RTU���� ���� �޼���
#define UPDATA_RDB_ASSIGN_MESSAGE	   19		// Update RDB Assign

// ��������� �޼��� ����
#define UM_POPUP_CEQINFO				WM_USER + 1
#define UM_LINEINFO_SUBSTATION_CLICK	WM_USER + 2
#define UM_LINEINFO_DL_DBCLICK			WM_USER + 3
#define UM_LINEINFO_FAULT_DBCLICK		WM_USER + 4
#define UM_LINEINFO_TIE_DBCLICK			WM_USER + 5
#define UM_TOTALINFO_TREE_CLICK			WM_USER + 6
#define UM_TOTALINFO_ALARM_ACK			WM_USER + 7
#define UM_LINEINFO_FI_ALARM			WM_USER + 8
#define UM_LINEINFO_FI_CLEAR			WM_USER + 9
#define UM_LINEINFO_RECOVERY_START		WM_USER + 10
#define UM_LINEINFO_RECOVERY_END		WM_USER + 11
#define UM_LINEINFO_OPEN_DL				WM_USER + 12
#define UM_LINEINFO_CHECK_FISTATUS		WM_USER + 13
#define UM_MAININFO_MOVE_SYMBOL			WM_USER + 14
#define UM_MAININFO_FI_INFO				WM_USER + 15
#define UM_LINEINFO_UPDATE_ACM_DL		WM_USER + 16
#define UM_TOTALINFO_SYMBOL_CLICK		WM_USER + 17
#define UM_SNAPSHOT						WM_USER + 18

// ���������� ���� �˾�â ����
#define TYPE_NOTHING					0		// Ÿ���� ���°��
#define TYPE_CEQ						1		// �����
#define TYPE_ACL						2		// ����
#define TYPE_ECR						3		// ���밡
#define TYPE_DRU						4		// �л�����

#define DWID_NOTHING				10000		// Ÿ���� ���°��
#define DWID_CEQ					20000		// �����
#define DWID_CEQ_SUB1				21000		// ����� �޸����
#define DWID_CEQ_SUB2				22000		// ����� �۾�����
#define DWID_ACL					30000		// ����
#define DWID_ECR					40000		// ���밡
#define DWID_DRU					50000		// �л�����

#define POPUP_INPUT						1		// �˾�â �Է�
#define POPUP_MODIFY					2		// �˾�â ����
#define POPUP_DELETE					3		// �˾�â ����

// PSRTYPE�� ����
#define PSRTYPE_ACL_SKY		    _T("PLSI_O")	// ���� (����)
#define PSRTYPE_ACL_UNDER		_T("PLSI_U")	// ���� (����)
#define PSRTYPE_ECR_ECR		    _T("ECR")		// ��м��밡
#define PSRTYPE_DRU_WT		    _T("WT")		// ǳ��
#define PSRTYPE_DRU_PVC			_T("PV")		// �¾籤
#define PSRTYPE_DRU_BATTERY	    _T("BS")		// ������������ġ
#define PSRTYPE_DRU_INVERTER    _T("PCS")		// �ι���
#define PSRTYPE_DRU_DIESEL		_T("DG")		// ����������
#define PSRTYPE_DRU_AIRCON		_T("ARC")		// ������
#define PSRTYPE_DRU_WATER		_T("WAT")		// �����
#define PSRTYPE_DRU_LOAD		_T("LDS")		// ���Ǻ���
#define PSRTYPE_SW_COMPOSITE	_T("SW_INC")	// ��ȸ�ΰ����(����)
#define PSRTYPE_STATCOM_BESS    _T("SVC")		// STATCOM-BESS

// ������ �ڵ�-���� ����
#define RTUMAP_MANUAL					1		// ���� RTUMAP	

// �α׸޼��� ���μ����� �̸�����
#define MAININFO_HMI			_T("MAININFO_HMI")
#define TOTALINFO_HMI			_T("TOTALINFO_HMI")
#define LINEINFO_HMI			_T("LINEINFO_HMI")
#define CONTROLINFO_HMI			_T("CONTROLINFO_HMI")
#define GENUNITINFO_HMI			_T("GENUNITINFO_HMI")
#define RDBVIEWER_HMI			_T("RDBVIEWER_HMI")
#define DFD_DSR					_T("DFDDSR")

// ��� ���� ũ��
#define	HMI_COMM_BUFFER					4096

// �̵��������� ���� ���ξ�����
#define CON_PREFIX				_T("CON_")
#define MSG_PREFIX				_T("MSG_")
#define EVENT_PREFIX			_T("EVENT_")

#define DIAGRAM_NAME			_T("anja.mdg")
#define DIAGRAM_GEN_NAME		_T("anja_gen.mdg")

// DATA INSERT OR UPDATE
#define DATA_INSERT							1		// ����Ʈ��Ʈ�ѿ� DATA�� ó�� �ִ°��
#define DATA_UPDATE							2		// ����Ʈ��Ʈ�ѿ� DATA�� ������Ʈ �ϴ°��

// ���α׷� ID ����
#define PG_P001								1		// ���뵵
#define PG_P002								2		// ��������
#define PG_P003								3		// �ܼ���
#define PG_P004								4		// ����â
#define PG_P005								5		// ACM

// CONTROL TYPE ����
#define CONTROL_TYPE_BO						1		// BO ����
#define CONTROL_TYPE_AO						2		// AO ����
#define CONTROL_TYPE_TAG					3		// TAG ����
#define CONTROL_TYPE_MEASURE				4		// ������û
#define CONTROL_TYPE_BI						5		// BI ��������
#define CONTROL_TYPE_AI						6		// AI ��������
#define CONTROL_TYPE_PI						7		// COUNTER ��������
#define CONTROL_TYPE_FULL				   51		// ��ü ����
#define CONTROL_TYPE_EVENT				   52		// �̺�Ʈ ����
#define CONTROL_TYPE_MEASURE_BI			   53		// �������� ����
#define CONTROL_TYPE_MEASURE_AI			   54		// �������� ����
#define CONTROL_TYPE_MEASURE_AO			   55		// �������� ����
#define CONTROL_TYPE_MEASURE_COUNTER	   56		// ī���� ����
#define CONTROL_TYPE_UNSOL				   57		// UNSOL ����
#define CONTROL_TYPE_COLD_START			   58		// COLD START
#define CONTROL_TYPE_WARM_START			   59		// WARM START
#define CONTROL_TYPE_SYNC_START			   60		// �ð�����ȭ

// POINT TYPE ����
#define POINT_TYPE_BI						1		// BI POINT
#define POINT_TYPE_BO						2		// BO POINT
#define POINT_TYPE_AI						3		// AI POINT
#define POINT_TYPE_AO						4		// AO POINT
#define POINT_TYPE_COUNT					5		// COUNT POINT
#define POINT_TYPE_DEVICE					6		// DEVICE POINT
#define POINT_TYPE_CALC						7		// CALCULATION POINT

// PS LOCK ����
#define PS_UNLOCK							0		// LOCK ����
#define PS_LOCK								1		// LOCK ����
#define PS_DATA_TRANS						0		// PS DATA ������
#define PS_DATA_TRANS_FAIL					1		// PS DATA ���۽���
#define PS_DATA_TRANS_SUCCESS				2		// PS DATA ���ۼ���

// ���� DATA ����
#define CTL_DATA_TRANS						0		// ���� DATA ������
#define CTL_DATA_TRANS_FAIL					1		// ���� DATA ���۽���
#define CTL_DATA_TRANS_SUCCESS				2		// ���� DATA ���ۼ���

// ����â ����
#define HMI_POPUP_CONTROLINFO				1		// ����â �˾�
#define HMI_POPUP_CONTROLINFO_MANUAL		2		// �����Է� ����â �˾�

// FI �߻�����
#define FI_NONE								0		// FI ����
#define FI_OCCUR							1		// FI �߻�
#define FI_TYPE_TEMPOR						0		// FI �Ͻ�
#define FI_TYPE_MOMENT						1		// FI ����
#define FI_TYPE_ETC							2		// FI
#define FI_TYPE_LOCKOUT						3		// ���ƿ�

// ��������Ʈ-�������� ����� ����
#define WAVE_RESULT_OK						0		// ����
#define WAVE_RESULT_NOT_EXIST				1		// ����������������
#define WAVE_RESULT_FILE_BUSY				4		// ��������������
#define WAVE_RESULT_COMM_FAIL				5		// ��Ž���

// Ʈ���� PU( Per Unit)������ ���� ����ġ
#define BASE_VOLTAGE_VALUE				13200		// ���� ���а� 13.2 kV
#define BASE_CURRENT_VALUE				  100 		// ���� ������ 100 A
#define BASE_ACTIVE_POWER_VALUE			  100		// ���� ��ȿ���°� 100 kVA
#define BASE_REACTIVE_POWER_VALUE		  100		// ���� ��ȿ���°� 100 kVA

// TLQ ������
#define NORMAL					   0x00000000
#define CI						   0x00000001		// ���� ���� ���� �±�
#define	SI						   0x00000002		// ������ ��� ���� �±�
#define AI						   0x00000004		// �˶� ���� �±�
#define EI						   0x00000008		// �̺�Ʈ ���� �±�
#define CS						   0x00000010		// ������ �±�								   			  
#define MH						   0x00000020		// �ְ� ����ġ �±�
#define ML						   0x00000040		// ���� ����ġ �±�
#define HL						   0x00000080		// ����ġ �±�
#define LL						   0x00000100		// ����ġ �±�								   					
#define CP						   0x00000200		// ���� ������
#define PS						   0x00000400		// ����Ʈ ������
#define MU						   0x00000800		// ����� �������� �Է�
#define NU						   0x00001000		// ������Ʈ �ҷ�
#define ON						   0x00002000		// ������ ����
#define OFF						   0x00004000		// ����Ʈ OFFLINE

// �л����� ���� ����
#define	SINAN_PV_BESS_ESS				  702		// �ȱ� PV�ž��Ŀ�1��(ESS) CEQID
#define	SINAN_PV_BESS_PV				  703		// �ȱ� PV�ž��Ŀ�1��(PV) CEQID
#define	SINAN_STATCOM_BESS_SVC1			  670		// ��� �ž�ǳ��(SVC1) CEQID
#define	SINAN_STATCOM_BESS_SVC2			  671		// ��� �ž�ǳ��(SVC2) CEQID
#define	SINAN_STATCOM_BESS_ESS1			  672		// ��� �ž�ǳ��(ESS1) CEQID
#define	SINAN_STATCOM_BESS_ESS2			  673		// ��� �ž�ǳ��(ESS2) CEQID
#define	SINAN_LMGEMS_ESS				  682		// ���� EMS (ESS) CEQID
#define	SINAN_STATCOM_BEFORE_SWITCH		  210		// ��ȿ���� �������� �ž�ǳ�� �մ� ����ġ	//20141205 kylee
#define MAX_TIME_CNT					 1440		// X�� �ִ밪 24 * 60
#define	POPUP_MSG_KILL					 5000		// �˾�â 5���� �ڵ������	
#define	PVBESS_CHART_NUM					4		// PV-BESS���� íƮ����
#define	STCBESS_CHART_NUM					4		// STC-BESS���� íƮ����
#define	LMGEMS_CHART1_NUM					4		// ���� EMS���� íƮ1����
#define	LMGEMS_CHART2_NUM					3		// ���� EMS���� íƮ2����

typedef struct _tagTRENDMINMAX
{
	int min;		// �ּ�
	int max;		// �ִ�

}TRENDMINMAX, *PTRENDMINMAX;

// Ʈ����Ʈ�� �̹��� Ÿ��
typedef enum
{
	IMG_GGR   = 0,
	IMG_SGR   = 1,
	IMG_SS    = 2,
	IMG_VL    = 3,
	IMG_PTR   = 4,
	IMG_DL    = 5,
	IMG_CEQ   = 6,

} IMG_TYPE;

// BI INDEX �ֿ� MEASURETYPEID
typedef enum
{
	OPNE_CLOSE				  =   1,		// ����/����
	LOCAL_REMOTE			  =   2,		// ����/����
	LOCK_UNLOCK				  =   3,		// ���/Ǯ��
	GAS_LOW					  =   4,		// �����з�����	
	FI_AUTO_A				  =   6,		// FI �ڵ�(A)	
	FI_AUTO_B				  =   7,		// FI �ڵ�(B)
	FI_AUTO_C				  =   8,		// FI �ڵ�(C)
	FI_AUTO_N				  =   9,		// FI �ڵ�(N)
	FI_MANUAL_A				  =  10,		// FI ����(A)
	FI_MANUAL_B				  =  11,		// FI ����(B)
	FI_MANUAL_C				  =  12,		// FI ����(C)
	FI_MANUAL_N				  =  13,		// FI ����(N)	
	LOSS_SOURCE_A			  =  14,		// ������ �ܼ����(A)
	LOSS_SOURCE_B			  =  15,		// ������ �ܼ����(B)
	LOSS_SOURCE_C			  =  16,		// ������ �ܼ����(C)
	LOSS_LOAD_A				  =  17,		// ������ �ܼ����(A)
	LOSS_LOAD_B				  =  18,		// ������ �ܼ����(B)
	LOSS_LOAD_C				  =  19,		// ������ �ܼ����(C)
	LOCK_BODY				  =  20,		// ��ü���	
	DOOR_OPEN				  =  21,		// ������
	BATTERY_DISCHARGE		  =  24,		// ������������	
	FI_A1					  = 100,		// FI ����(A)
	FI_B1					  = 101,		// FI ����(B)
	FI_C1					  = 102,		// FI ����(C)
	FI_N1					  = 103,		// FI ����(N)	
	FAULT_PERMANENT			  = 104,		// �Ͻð���
	FAULT_TEMPORARY			  = 105,		// ��������	
	RECLOSE_DISABLE			  = 118,		// ����ι���
	SEQUENCE_LOCK_OUT		  = 121,		// ���ƿ�
	LARGE_CURRENT_OPEN_FINISH = 122,		// ����������Ϸ�
	FI_A2					  = 123,		// ������� (A)
	FI_B2					  = 124,		// ������� (B)
	FI_C2					  = 125,		// ������� (C)
	FI_N2					  = 126,		// ������� (N)
	FI_SEF2					  = 180,		// ������� (SEF)

	OPNE_CLOSE_OCB			  = 1967,		// TDAS OCB ����/����

} BI_INDEX;

// BO INDEX �ֿ� MEASURETYPEID
typedef enum
{
	CLOSE_OPEN				  =  33,		// ����/����
	FI_RESET1				  =  36,		// FI RESET(����)
	FI_RESET2				  = 219,		// ������������
	FI_RESET3				  = 431,		// FI RESET

} BO_INDEX;

// AI INDEX �ֿ� MEASURETYPEID
typedef enum
{	
	CURRENT_A				  =   38,		// ������(A)
	CURRENT_B				  =   39,		// ������(B)
	CURRENT_C				  =   40,		// ������(C)
	CURRENT_N				  =   41,		// ������(N)	
	VOLTAGE_A				  =   48,		// ������ ����(A)
	VOLTAGE_B				  =   49,		// ������ ����(B)
	VOLTAGE_C				  =   50,		// ������ ����(C)	
	FI_CURRENT_A			  =   51,		// �������� (A)
	FI_CURRENT_B			  =   52,		// �������� (B)
	FI_CURRENT_C			  =   53,		// �������� (C)
	FI_CURRENT_N			  =   54,		// �������� (N)
	VOLTAGE_LOAD_A			  =   55,		// ������ ����(A)
	VOLTAGE_LOAD_B			  =   56,		// ������ ����(B)
	VOLTAGE_LOAD_C			  =   57,		// ������ ����(C)
	VOLTAGE_A_87			  =   87,		// ����(A)
	VOLTAGE_B_88			  =   88,		// ����(B)
	VOLTAGE_C_89			  =   89,		// ����(C)
	ACTIVE_POWER_3P			  =  239,		// ��ȿ���� (3��)
	REACTIVE_POWER_3P		  =  240,		// ��ȿ���� (3��)
	FI_CURRENT_SEF			  =  252,		// �������� (SEF)
	ACTIVE_POWER_A			  =  424,		// ��ȿ���� (A)
	ACTIVE_POWER_B			  =  425,		// ��ȿ���� (B)
	ACTIVE_POWER_C			  =  426,		// ��ȿ���� (C)	
	REACTIVE_POWER_A		  =  427,		// ��ȿ���� (A)
	REACTIVE_POWER_B		  =  428,		// ��ȿ���� (B)
	REACTIVE_POWER_C		  =  429,		// ��ȿ���� (C)
	CURRENT_A_501			  =  501,		// ����(A)-�⺻�� RMS (�������)
	CURRENT_B_502			  =  502,		// ����(B)-�⺻�� RMS (�������)
	CURRENT_C_503			  =  503,		// ����(C)-�⺻�� RMS (�������)
	CURRENT_N_504			  =  504,		// ����(N)-�⺻�� RMS (�������)
	VOLTAGE_A_509			  =  509,		// ����(A)-�⺻�� RMS (�������)
	VOLTAGE_B_510			  =  510,		// ����(B)-�⺻�� RMS (�������)
	VOLTAGE_C_511			  =  511,		// ����(C)-�⺻�� RMS (�������)
	ACTIVE_POWER			  = 1138,		// ��ȿ����
	REACTIVE_POWER			  = 1139,		// ��ȿ����
	VOLTAGE_A_1424			  = 1424,		// ����1������(PriSrcV)-A
	CURRENT_A_1425			  = 1425,		// ����1������(PriLoadA)-A
	PRIW_A					  = 1429,		// ��ȿ����(PriW)-A
	PRIVAR_A				  = 1430,		// ��ȿ����(PriVAr)-A	
	VOLTAGE_B_1442			  = 1442,		// ����1������(PriSrcV)-B
	CURRENT_B_1443			  = 1443,		// ����1������(PriLoadA)-B
	PRIW_B					  = 1447,		// ��ȿ����(PriW)-B
	PRIVAR_B				  = 1448,		// ��ȿ����(PriVAr)-B
	VOLTAGE_C_1460			  = 1460,		// ����1������(PriSrcV)-C
	CURRENT_C_1461			  = 1461,		// ����1������(PriLoadA)-C	
	PRIW_C					  = 1465,		// ��ȿ����(PriW)-C
	PRIVAR_C				  = 1466,		// ��ȿ����(PriVAr)-C

} AI_INDEX;

#include <afxdisp.h>

// FLASH ���� Ŭ����
class CShockwaveFlash : public CWnd
{
protected:
	DECLARE_DYNCREATE( CShockwaveFlash )

public:
	void SetBackgroundColor( long nNewValue )
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper( 0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nNewValue );
	}

	void SetMovie( LPCTSTR lpszNewValue )
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper( 0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lpszNewValue );
	}

	void Play()
	{
		InvokeHelper( 0x70, DISPATCH_METHOD, VT_EMPTY, NULL, NULL );
	}

	void Stop()
	{
		InvokeHelper( 0x7e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL );
	}

	BOOL IsPlaying()
	{
		BOOL result;
		InvokeHelper( 0x81, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL );
		return result;
	}

	LONG CurrentFrame()
	{
		LONG result;
		InvokeHelper( 0x80, DISPATCH_METHOD, VT_I4, (void*)&result, NULL );
		return result;
	}

	LONG GetTotalFrames()
	{
		LONG result;
		InvokeHelper( 0x7c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL );
		return result;
	}

	void SetVariable( LPCTSTR name, LPCTSTR value )
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper( 0x97, DISPATCH_METHOD, VT_EMPTY, NULL, parms, name, value );
	}

	CString GetVariable( LPCTSTR name )
	{
		CString result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper( 0x98, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, name );
		return result;
	}
};

#endif // #ifndef _DEFINE_H