#pragma once
#ifndef __HMICONST_H__
#define __HMICONST_H__


/////////////////////////////////////////////////////////////////////////////
//  HCI MESSAGE DEFINE
/////////////////////////////////////////////////////////////////////////////
// log command
//	#define	HCI_LOG_COMMAND	 _T("HCI_LOG_COMMAND")	// + Project Name
//		#define LOG_WPARAM_LOGIN					0x0001			// �α���
//		#define LOG_WPARAM_LOGOUT					0x0002			// �α� �ƿ�
//		#define LOG_WPARAM_LOGCHANGE				0x0003			// �α� ����
//		#define LOG_WPARAM_LOGLIST					0x0004			// �α� ����Ʈ
//		#define LOG_WPARAM_LOGIN_REQ				0x0005			// �α׼��� ����
//		#define LOG_WPARAM_LOGIN_RES				0x0006			// �α׼��� ����
//			#define LOG_LPARAM_OK						0x0001		//	����			// lparam�� ���� 4byte�� ����� �ְ� ������ �� �޼����� �ִ´�.
//			#define LOG_LPARAM_FAIL						0x0000		// ����
//			#define LOG_LPARAM_TIMEOUT					0x0002		// Ÿ�Ӿƿ�
//		#define LOG_WPARAM_FAIL_BDLFILE				0x0007			// �ܼ��� ��û ����
//// pdb command
//	#define	HCI_PDB_COMMAND	 _T("HCI_PDB_COMMAND")					// PDB �޼���
//		#define PDB_WPARAM_LIST_REQ				0x0001				// ����Ʈ ��û
//			#define LOG_LPARAM_LIST_REQ_OK				0x0001		// ��û ����
//			#define LOG_LPARAM_LIST_REQ_FAIL			0x0000		// ��û ����
//			#define LOG_LPARAM_LIST_REQ_ALREADY			0x0002		// �̹� ������Ʈ�� ����
//		
//		#define PDB_WPARAM_LIST_CNT				0x0002				// ��ü ����Ʈ ī��Ʈ
////		#define LOG_LPARAM_LIST_CNT					(0 ~ 100) lparam�� ��ü PDB ī���͸� ������
//		#define PDB_WPARAM_LIST_DOWN			0x0003				// �ٿ����� ����Ʈ ī��Ʈ
////		#define LOG_LPARAM_LIST_DOWN				(0 ~ 100) lparam�� ��ü PDB ī������ ���° ����Ʈ ī����
//		#define PDB_WPARAM_LIST_COMPLETE		0x0004				// PDB �ٿ� �Ϸ�
//			#define LOG_LPARAM_LIST_COMPLETE_OK				0x0001	// ����
//			#define LOG_LPARAM_LIST_COMPLETE_FAIL			0x0000	// ����
//		#define PDB_WPARAM_LIST_PACKET			0x0005				// ���ϳ� ��Ŷ ī��Ʈ
//		#define PDB_WPARAM_LIST_CANCEL			0x0006				// PDB ����ȭ ���
//		#define PDB_WPARAM_LIST_FINISH			0x0007				// PDB ����ȭ �Ϸ�, ȭ�� CLOSE
//
//// app command
	#define	HMI_APP_COMMAND	 _T("HMI_APP_COMMAND")					// ���ð� �޼���
		#define APP_WPARAM_MAIN_TO_TOTAL		0x0001				// ���뵵 -> ����ȭ��
		#define APP_WPARAM_MAIN_TO_LINE			0x0002				// ���뵵 -> �ܼ���
		#define APP_WPARAM_LINE_TO_MAIN			0x0003				// �ܼ��� -> ���뵵
		#define APP_WPARAM_TOTAL_TO_MAIN		0x0004				// ����ȭ�� -> ���뵵
		#define APP_WPARAM_TOTAL_TO_LINE		0x0005				// ����ȭ�� -> �ܼ���
		#define APP_WPARAM_LINE_TO_TOTAL		0x0006				// �ܼ��� -> ����ȭ��
		#define APP_WPARAM_AL_TO_MAIN			0x0007				// �˶� -> ���뵵
		#define APP_WPARAM_AL_TO_LINE			0x0008				// �˶� -> �ܼ���
			#define COMM_LPARAM_START					0x0001				// ����
			#define COMM_LPARAM_STOP					0x0002				// ����
			#define COMM_LPARAM_EXIT					0x0003				// ����
			#define COMM_LPARAM_RUN						0x0004				// ����
			#define	COMM_LPARAM_SCAN					0x0001				// SCAN CONNECTION
			#define COMM_LPARAM_CTRL					0x0002				// CTRL CONNECTION
			#define COMM_LPARAM_ASI						0x0003				// ASI  CONNECTION
			#define COMM_LPARAM_ALARM					0x0004				// ALARM CONNECTION
			#define COMM_LPARAM_LOADMEM					0x0010				// �޸� �ε� -> lparam�� ���� 2byte�� �� �޼����� �ְ�, ����2byte�� ��Ÿ?����.
//
//		#define APP_WPARAM_COM_TO_BLD			0x000B				// Comm -> �ܼ���
//		#define APP_WPARAM_COM_TO_BD			0x000C				// Comm -> ���뵵
//			#define COMM_LPARAM_DOWN_OK					0x0001				// �ܼ���/���뵵 �ٿ�OK   -> lparam�� ���� 2byte�� �� �޼����� �ְ�, ����2byte�� ��Ÿ?����.
//			#define COMM_LPARAM_DOWN_FAIL				0x0002				// �ܼ���/���뵵 �ٿ�Fail
//			#define COMM_LPARAM_DOWNLOAD				0x0003				// �ܼ���/���뵵 �ٿ���			
//		#define APP_WPARAM_BD_TO_COM			0x000D				// ���뵵->Comm 
//		#define APP_WPARAM_COM_TO_OPERATOR_LIST_OK		0x000E				// Comm -> ���� ���� ����Ʈ �м� OK
//		#define APP_WPARAM_COM_TO_OPERATOR_FILE_OK		0x000F				// Comm -> ���� ���� ���� ���� OK
//		#define APP_WPARAM_COM_TO_MSG			0x0010				// Comm -> etc(�޽�������)
//			#define COMM_LPARAM_MSG_DOWN_OK				0x0001				// 
//			#define COMM_LPARAM_MSG_DOWN_FAIL			0x0002				// 
//		#define APP_WPARAM_DMC_TO_OPERATOR		0x0011				// DMC -> ����	
//		#define APP_WPARAM_COM_TO_FAULT_VIEWER	0x0012				// COMM -> FAULT VIEWER (���ÿ�)
//			#define COMM_LPARAM_MSG_REQ					0x0008
//			#define COMM_LPARAM_MSG_REV					0x0020
//			#define COMM_LPARAM_MSG_END					0x0040
//		#define APP_WPARAM_FD_TO_BDL			0x0013				// FD -> �ܼ���
//			#define FD_SET_LPARAM_CANCEL				0x0000
//			#define FD_SET_LPARAM_OK					0x0001
//
//			
//// global command
//	#define	HCI_GLOBAL_COMMAND	 _T("HCI_GLOBAL_COMMAND")			// ��ü �޼���
//		#define GLOBAL_WPARAM_EXIT				0x0001				// ����
//		#define GLOBAL_WPARAM_PROTECTION		0x0002				// ��ü, ����
//			#define GLOBAL_LPARAM_PROTECTION_A			0x0001		// ���� ��ü
//			#define GLOBAL_LPARAM_PROTECTION_B			0x0002		// �鼷 ��ü
//			#define GLOBAL_LPARAM_PROTECTION_A_RECON	0x0003		// ���� �翬��
//			#define GLOBAL_LPARAM_PROTECTION_B_RECON	0x0004		// �鼷 �翬��
//			#define GLOBAL_LPARAM_PROTECTION_A_OK		0x0005		// ���� ����
//			#define GLOBAL_LPARAM_PROTECTION_B_OK		0x0006		// �鼷 ����
//			#define GLOBAL_LPARAM_PROTECTION_A_TIME		0x0007		// ���� Ÿ�Ӿƿ�
//			#define GLOBAL_LPARAM_PROTECTION_B_TIME		0x0008		// �鼷 Ÿ�Ӿƿ�
//			#define GLOBAL_LPARAM_PROTECTION_REQ		0x0009		// ��ü ����
//			#define GLOBAL_LPARAM_RE_OK					0x0010		// �翬�� ����
//
//		#define GLOBAL_WPARAM_RECONNACT			0x0003				// �� ����
//		#define GLOBAL_WPARAM_CONNECT			0x0004				// ����
//
//			#define GLOBAL_LPARAM_OK					0x0001	// ����
//			#define GLOBAL_LPARAM_FAIL					0x0000	// ����
//
//		#define GLOBAL_WPARAM_PROTECTION_CANCEL			0x0011		// �������
//		#define GLOBAL_WPARAM_ENV_SAVE					0x0012		// ȯ������
//		#define GLOBAL_WPARAM_ENV_LOAD					0x0013		// ȯ��ε�
//			#define GLOBAL_LPARAM_INDEX1				0x0001		// 1���ε���
//			#define GLOBAL_LPARAM_INDEX2				0x0002		// 2���ε���
//			#define GLOBAL_LPARAM_INDEX3				0x0003		// 3���ε���
//
//		#define GLOBAL_WPARAM_ACMFILE					0x0015		// ACM ����
//			#define GLOBAL_LPARAM_RES_DONE				0x0001		// SR ��û ����
//			#define GLOBAL_LPARAM_RES_EQUIP_ERR			0x0002		// ���񿡷�
//			#define GLOBAL_LPARAM_RES_DL_ERR			0x0003		// D/L����
//			#define GLOBAL_LPARAM_ACMFILE_REQ			0x0004		// ���� �ٿ�ε� ��û
//			#define GLOBAL_LPARAM_ACMFILE_REQ_OK		0x0005		// ���� �ٿ�ε� OK
//			#define GLOBAL_LPARAM_ACMFILE_REQ_ERR		0x0006		// ���� �ٿ�ε� fail
//			#define GLOBAL_LPARAM_ACMFILE_REQ_TIMEOUT	0x0007		// ���� �ٿ�ε� Ÿ�Ӿƿ�
//
//		#define GLOBAL_WPARAM_PDB_UPDATE				0x0016		// PDB ������
//			#define GLOBAL_LPARAM_PDB_START				0x0001		// ������ ����
//			#define GLOBAL_LPARAM_PDB_END				0x0002		// ������ ��
//
//		#define	APP_WPARAM_EXIT							0x0017		// ��������
//			
//// acm command
//	#define	HCI_ACM_COMMAND	 _T("HCI_ACM_COMMAND")			// ��ü �޼���
//		#define	HCI_ACM_COMMAND	 _T("HCI_ACM_COMMAND")			// ��ü �޼���
		
	
/////////////////////////////////////////////////////////////////////////////
// HCI GLOBAL CONST ����
/////////////////////////////////////////////////////////////////////////////	
	#define	HMI_FUNC_FAIL								0
	#define	HMI_FUNC_SUCC								1
	#define HMI_ALREADY_CONNECT							2
	#define HMI_CONNECT_FAIL							3
	#define	HMI_FUNC_CONTINUE							9
		
	#define LEN_HCI										32
	#define LEN_EVTID									32
	#define	LEN_UID										32
	#define	LEN_PWD										32
	#define	LEN_UNAME									16
	#define LEN_PDB_FNAME								64
	#define	LEN_MD5										36
	#define EVTID_SIZE									24
	#define	HMI_CONFIG									_T("Config.xml")
	
	// ERROR NUMBER
	#define	ERR_CONNECTION_CLOSE						0
	#define	ERR_NO_DATA									-1
	#define	ERR_RCV_INCOMPLETE							-2
	#define	ERR_NOT_CONTINUOUS_SEQUENCE					-3
	#define	ERR_INVALID_NODECODE						-4
	#define	ERR_SND_INCOMPLETE							-5
	#define	ERR_NO_ACKRECEIVE							-6

	#define COMMAND_START								1
	#define COMMAND_STOP								2
	#define COMMAND_RESUME								3
	#define COMMAND_PAUSE								4

	#define FUNC_FILTER_ALL 0x9999

	// HCI DIRECTORY ���� ����
	#define	DIR_LOGPATH									_T("LOG")
	#define	DIR_PDBPATH									_T("PDB")
	#define DIR_PDB_ASI_PATH							_T("ASI")
	#define DIR_PDB_SDMS_PATH							_T("SDMS")
	#define	DIR_DOWNPATH								_T("DOWN")
	#define DIR_DRAW_PATH								_T("DRAWING")
	#define DIR_WAVE_PATH								_T("WAVE")
	#define DIR_IMG_PATH								_T("IMG")
	#define DIR_DRAW_HCI_PATH							_T("HCI")
	#define DIR_DRAW_SYM_PATH							_T("SYMBOL")
	

	// HCI PROGRAM MUTEX CONST ����
	#define	APP_MUTEX_OBJECT_NAME_HCIENGINE				_T("KDNHCIEngineMutexCreated")			// MAIN ENGINE
	#define	APP_MUTEX_OBJECT_NAME_HCICOMM				_T("KDNHCICommMutexCreated")			// HCI ��Ÿ��
	#define	APP_MUTEX_OBJECT_NAME_HCIOPERATE			_T("KDNHCIOperateMutexCreated")			// ���� �
	#define	APP_MUTEX_OBJECT_NAME_HCIMANAGE				_T("KDNHCIManageMutexCreated")			// ���� ����
	#define	APP_MUTEX_OBJECT_NAME_HCIALARMVIEW			_T("KDNHCIAlarmViewMutexCreated")		// ALARM MONITORING
	#define APP_MUTEX_OBJECT_NAME_HCIBLVIEW				_T("KDNHCIBLVIEWMutexCreated")			// ���뵵
	#define APP_MUTEX_OBJECT_NAME_HCIDLVIEW				_T("KDNHCIDLViewMutexCreated")			// �ܼ���
	#define	APP_MUTEX_OBJECT_NAME_HCICOMMTESTER			_T("KDNHCICommTesterMutexCreated")		// MAIN ENGINE
	#define APP_MUTEX_OBJECT_NAME_HCISYSANALYSIS		_T("KDNHCISysAnalysisMutexCreated")     // ����м�
	#define APP_MUTEX_OBJECT_NAME_HCIALARMSYNC			_T("KDNHCIAlarmSyncMutexCreated")		// Alarm ����ȭ
	#define APP_MUTEX_OBJECT_NAME_HCIDMC				_T("KDNHCIDMCMutexCreated")	// DMC
	#define APP_MUTEX_OBJECT_NAME_HCISYSHISTORY			_T("KDNHCISysHistoryMutexCreated")		// �����̷�
	#define APP_MUTEX_OBJECT_NAME_HCIMEMO				_T("KDNHCIMemoMutexCreated")			// �޸�
	#define APP_MUTEX_OBJECT_NAME_HCIINITSRC			_T("KDNHCIInitSrcMutexCreated")			// �ʱ�ȭ��
	#define APP_MUTEX_OBJECT_NAME_HCISMARTAL			_T("KDNHCISmartAlarmMutexCreated")		// ����Ʈ �˶�
	#define APP_MUTEX_OBJECT_NAME_HCICOMPARE			_T("KDNHCICompareMutexCreated")		// ����Ʈ �˶�
	#define APP_MUTEX_OBJECT_NAME_HCISUMMERY			_T("KDNHCISummeyrMutexCreated")			// �ʱ�ȭ��(���ÿ�)
	#define APP_MUTEX_OBJECT_NAME_HCISRPROG				_T("KDNHCISRProgMutexCreated")		// Fault Viwer(���ÿ�)
	#define APP_MUTEX_OBJECT_NAME_HCIINIT				_T("KDNHCIInitMutexCreated")		// �ʱ�ȭ��(���ÿ�)
	#define APP_MUTEX_OBJECT_NAME_HCIINIT2				_T("KDNHCIInit2MutexCreated")		// �ʱ�ȭ��2(���ÿ�)
	#define APP_MUTEX_OBJECT_NAME_HCIBSVIEW				_T("KDNHCIBSVIEWMutexCreated")			// ���������

	// HCI SHARED MEMORY MUTEX CONST ����
	#define SHARE_HMI_PROJECT							_T("HCI_SHARE_PROJECT")
	#define SHARE_HMI_PROJECT_MUTEX						_T("HCI_SHARE_PROJECT_MUTEX")
	#define SHARE_HMI_ENVVAR							_T("HCI_SHARE_ENVVAR")
	

	// HCI ���� ��� define ���
	#define ENUM_APP_CODE_CNT	   4
	

	//enum ENUM_TLQ
	//{
	//	ENUM_TLQ_NORMAL					= 0x00000000,	// normal
	//	ENUM_TLQ_COE					= 0x00000001,	// [COE] component operator updated
	//	ENUM_TLQ_UAS					= 0x00000002,	// [UAS] using alternate data source(61850:source)
	//	ENUM_TLQ_BS						= 0x00000004,	// [BS] bad state estimator value(61850:suspect)
	//	ENUM_TLQ_QD						= 0x00000008,	// [QD] questionable quality of the data(61850:questionable)
	//	ENUM_TLQ_DC						= 0x00000010,	// [DC] drift correction not being performed(61850:oscillatory
	//	ENUM_TLQ_NU						= 0x00000020,	// [NU] point wasn't updated during last scan(61850:oldData)
	//	ENUM_TLQ_RL						= 0x00000040,	// [RL] reasonability limit exceeded(61850:outOfRange)
	//	ENUM_TLQ_ME						= 0x00000080,	// [ME] the value is operator entered
	//	ENUM_TLQ_AB						= 0x00000100,	// [AB] point is in a defined abnormal state
	//	ENUM_TLQ_RC						= 0x00000200,	// [RC] rate of change limit exceeded(61850:oscillatory)
	//	ENUM_TLQ_HL						= 0x00000400,	// [HL] high/low limit exceeded
	//	ENUM_TLQ_WO						= 0x00000800,	// [WO] ����밳���(���� FIX, �̸��� �ӽ�)
	//	ENUM_TLQ_CI						= 0x00001000,	// [CI] control inhibit tag
	//	ENUM_TLQ_AI						= 0x00002000,	// [AI] alarms inhibit tag
	//	ENUM_TLQ_EI						= 0x00004000,	// [EI] event inhibit tag
	//	ENUM_TLQ_SI						= 0x00008000,	// [SI] scan inhibit tag(61850:operatorBlocked)
	//	ENUM_TLQ_UA						= 0x00010000,	// [UA] alarms not completely acknowleded
	//	ENUM_TLQ_AE						= 0x00020000,	// [AE] an alarm exists
	//	ENUM_TLQ_PS						= 0x00100000,	// [PS] point is selected by dispatcher
	//	ENUM_TLQ_CIP					= 0x00200000,	// [CIP] control on point is in progress
	//	ENUM_TLQ_SQC					= 0x00400000	// [SQC] sequence control for point in progress
	//};
#endif