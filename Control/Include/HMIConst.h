#pragma once
#ifndef __HMICONST_H__
#define __HMICONST_H__


/////////////////////////////////////////////////////////////////////////////
//  HCI MESSAGE DEFINE
/////////////////////////////////////////////////////////////////////////////
// log command
//	#define	HCI_LOG_COMMAND	 _T("HCI_LOG_COMMAND")	// + Project Name
//		#define LOG_WPARAM_LOGIN					0x0001			// 로그인
//		#define LOG_WPARAM_LOGOUT					0x0002			// 로그 아웃
//		#define LOG_WPARAM_LOGCHANGE				0x0003			// 로그 변경
//		#define LOG_WPARAM_LOGLIST					0x0004			// 로그 리스트
//		#define LOG_WPARAM_LOGIN_REQ				0x0005			// 로그성공 질의
//		#define LOG_WPARAM_LOGIN_RES				0x0006			// 로그성공 응답
//			#define LOG_LPARAM_OK						0x0001		//	성공			// lparam의 상위 4byte엔 결과를 넣고 하위엔 본 메세지를 넣는다.
//			#define LOG_LPARAM_FAIL						0x0000		// 실패
//			#define LOG_LPARAM_TIMEOUT					0x0002		// 타임아웃
//		#define LOG_WPARAM_FAIL_BDLFILE				0x0007			// 단선도 요청 실패
//// pdb command
//	#define	HCI_PDB_COMMAND	 _T("HCI_PDB_COMMAND")					// PDB 메세지
//		#define PDB_WPARAM_LIST_REQ				0x0001				// 리스트 요청
//			#define LOG_LPARAM_LIST_REQ_OK				0x0001		// 요청 성공
//			#define LOG_LPARAM_LIST_REQ_FAIL			0x0000		// 요청 실패
//			#define LOG_LPARAM_LIST_REQ_ALREADY			0x0002		// 이미 업데이트된 파일
//		
//		#define PDB_WPARAM_LIST_CNT				0x0002				// 전체 리스트 카운트
////		#define LOG_LPARAM_LIST_CNT					(0 ~ 100) lparam에 전체 PDB 카운터를 보내줌
//		#define PDB_WPARAM_LIST_DOWN			0x0003				// 다운중인 리스트 카운트
////		#define LOG_LPARAM_LIST_DOWN				(0 ~ 100) lparam에 전체 PDB 카운터중 몇번째 리스트 카운터
//		#define PDB_WPARAM_LIST_COMPLETE		0x0004				// PDB 다운 완료
//			#define LOG_LPARAM_LIST_COMPLETE_OK				0x0001	// 성공
//			#define LOG_LPARAM_LIST_COMPLETE_FAIL			0x0000	// 실패
//		#define PDB_WPARAM_LIST_PACKET			0x0005				// 파일내 패킷 카운트
//		#define PDB_WPARAM_LIST_CANCEL			0x0006				// PDB 동기화 취소
//		#define PDB_WPARAM_LIST_FINISH			0x0007				// PDB 동기화 완료, 화면 CLOSE
//
//// app command
	#define	HMI_APP_COMMAND	 _T("HMI_APP_COMMAND")					// 어플간 메세지
		#define APP_WPARAM_MAIN_TO_TOTAL		0x0001				// 계통도 -> 종합화면
		#define APP_WPARAM_MAIN_TO_LINE			0x0002				// 계통도 -> 단선도
		#define APP_WPARAM_LINE_TO_MAIN			0x0003				// 단선도 -> 계통도
		#define APP_WPARAM_TOTAL_TO_MAIN		0x0004				// 종합화면 -> 계통도
		#define APP_WPARAM_TOTAL_TO_LINE		0x0005				// 종합화면 -> 단선도
		#define APP_WPARAM_LINE_TO_TOTAL		0x0006				// 단선도 -> 종합화면
		#define APP_WPARAM_AL_TO_MAIN			0x0007				// 알람 -> 계통도
		#define APP_WPARAM_AL_TO_LINE			0x0008				// 알람 -> 단선도
			#define COMM_LPARAM_START					0x0001				// 시작
			#define COMM_LPARAM_STOP					0x0002				// 정지
			#define COMM_LPARAM_EXIT					0x0003				// 종료
			#define COMM_LPARAM_RUN						0x0004				// 실행
			#define	COMM_LPARAM_SCAN					0x0001				// SCAN CONNECTION
			#define COMM_LPARAM_CTRL					0x0002				// CTRL CONNECTION
			#define COMM_LPARAM_ASI						0x0003				// ASI  CONNECTION
			#define COMM_LPARAM_ALARM					0x0004				// ALARM CONNECTION
			#define COMM_LPARAM_LOADMEM					0x0010				// 메모리 로드 -> lparam의 상위 2byte엔 본 메세지를 넣고, 하위2byte엔 기타?정보.
//
//		#define APP_WPARAM_COM_TO_BLD			0x000B				// Comm -> 단선도
//		#define APP_WPARAM_COM_TO_BD			0x000C				// Comm -> 계통도
//			#define COMM_LPARAM_DOWN_OK					0x0001				// 단선도/계통도 다운OK   -> lparam의 상위 2byte엔 본 메세지를 넣고, 하위2byte엔 기타?정보.
//			#define COMM_LPARAM_DOWN_FAIL				0x0002				// 단선도/계통도 다운Fail
//			#define COMM_LPARAM_DOWNLOAD				0x0003				// 단선도/계통도 다운중			
//		#define APP_WPARAM_BD_TO_COM			0x000D				// 계통도->Comm 
//		#define APP_WPARAM_COM_TO_OPERATOR_LIST_OK		0x000E				// Comm -> 계통운영 파형 리스트 분석 OK
//		#define APP_WPARAM_COM_TO_OPERATOR_FILE_OK		0x000F				// Comm -> 계통운영 파형 파일 수신 OK
//		#define APP_WPARAM_COM_TO_MSG			0x0010				// Comm -> etc(메시지관련)
//			#define COMM_LPARAM_MSG_DOWN_OK				0x0001				// 
//			#define COMM_LPARAM_MSG_DOWN_FAIL			0x0002				// 
//		#define APP_WPARAM_DMC_TO_OPERATOR		0x0011				// DMC -> 계통운영	
//		#define APP_WPARAM_COM_TO_FAULT_VIEWER	0x0012				// COMM -> FAULT VIEWER (전시용)
//			#define COMM_LPARAM_MSG_REQ					0x0008
//			#define COMM_LPARAM_MSG_REV					0x0020
//			#define COMM_LPARAM_MSG_END					0x0040
//		#define APP_WPARAM_FD_TO_BDL			0x0013				// FD -> 단선도
//			#define FD_SET_LPARAM_CANCEL				0x0000
//			#define FD_SET_LPARAM_OK					0x0001
//
//			
//// global command
//	#define	HCI_GLOBAL_COMMAND	 _T("HCI_GLOBAL_COMMAND")			// 전체 메세지
//		#define GLOBAL_WPARAM_EXIT				0x0001				// 종료
//		#define GLOBAL_WPARAM_PROTECTION		0x0002				// 절체, 끊김
//			#define GLOBAL_LPARAM_PROTECTION_A			0x0001		// 본섭 절체
//			#define GLOBAL_LPARAM_PROTECTION_B			0x0002		// 백섭 절체
//			#define GLOBAL_LPARAM_PROTECTION_A_RECON	0x0003		// 본섭 재연결
//			#define GLOBAL_LPARAM_PROTECTION_B_RECON	0x0004		// 백섭 재연결
//			#define GLOBAL_LPARAM_PROTECTION_A_OK		0x0005		// 본섭 연결
//			#define GLOBAL_LPARAM_PROTECTION_B_OK		0x0006		// 백섭 연결
//			#define GLOBAL_LPARAM_PROTECTION_A_TIME		0x0007		// 본섭 타임아웃
//			#define GLOBAL_LPARAM_PROTECTION_B_TIME		0x0008		// 백섭 타임아웃
//			#define GLOBAL_LPARAM_PROTECTION_REQ		0x0009		// 절체 질의
//			#define GLOBAL_LPARAM_RE_OK					0x0010		// 재연결 성공
//
//		#define GLOBAL_WPARAM_RECONNACT			0x0003				// 재 연결
//		#define GLOBAL_WPARAM_CONNECT			0x0004				// 연결
//
//			#define GLOBAL_LPARAM_OK					0x0001	// 성공
//			#define GLOBAL_LPARAM_FAIL					0x0000	// 실패
//
//		#define GLOBAL_WPARAM_PROTECTION_CANCEL			0x0011		// 강제취소
//		#define GLOBAL_WPARAM_ENV_SAVE					0x0012		// 환경저장
//		#define GLOBAL_WPARAM_ENV_LOAD					0x0013		// 환경로드
//			#define GLOBAL_LPARAM_INDEX1				0x0001		// 1번인덱스
//			#define GLOBAL_LPARAM_INDEX2				0x0002		// 2번인덱스
//			#define GLOBAL_LPARAM_INDEX3				0x0003		// 3번인덱스
//
//		#define GLOBAL_WPARAM_ACMFILE					0x0015		// ACM 파일
//			#define GLOBAL_LPARAM_RES_DONE				0x0001		// SR 요청 성공
//			#define GLOBAL_LPARAM_RES_EQUIP_ERR			0x0002		// 설비에러
//			#define GLOBAL_LPARAM_RES_DL_ERR			0x0003		// D/L에러
//			#define GLOBAL_LPARAM_ACMFILE_REQ			0x0004		// 파일 다운로드 요청
//			#define GLOBAL_LPARAM_ACMFILE_REQ_OK		0x0005		// 파일 다운로드 OK
//			#define GLOBAL_LPARAM_ACMFILE_REQ_ERR		0x0006		// 파일 다운로드 fail
//			#define GLOBAL_LPARAM_ACMFILE_REQ_TIMEOUT	0x0007		// 파일 다운로드 타임아웃
//
//		#define GLOBAL_WPARAM_PDB_UPDATE				0x0016		// PDB 업데잇
//			#define GLOBAL_LPARAM_PDB_START				0x0001		// 업데잇 시작
//			#define GLOBAL_LPARAM_PDB_END				0x0002		// 업데잇 끝
//
//		#define	APP_WPARAM_EXIT							0x0017		// 어플종료
//			
//// acm command
//	#define	HCI_ACM_COMMAND	 _T("HCI_ACM_COMMAND")			// 전체 메세지
//		#define	HCI_ACM_COMMAND	 _T("HCI_ACM_COMMAND")			// 전체 메세지
		
	
/////////////////////////////////////////////////////////////////////////////
// HCI GLOBAL CONST 정의
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

	// HCI DIRECTORY 구조 정의
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
	

	// HCI PROGRAM MUTEX CONST 정의
	#define	APP_MUTEX_OBJECT_NAME_HCIENGINE				_T("KDNHCIEngineMutexCreated")			// MAIN ENGINE
	#define	APP_MUTEX_OBJECT_NAME_HCICOMM				_T("KDNHCICommMutexCreated")			// HCI 통신모듈
	#define	APP_MUTEX_OBJECT_NAME_HCIOPERATE			_T("KDNHCIOperateMutexCreated")			// 계통 운영
	#define	APP_MUTEX_OBJECT_NAME_HCIMANAGE				_T("KDNHCIManageMutexCreated")			// 계통 관리
	#define	APP_MUTEX_OBJECT_NAME_HCIALARMVIEW			_T("KDNHCIAlarmViewMutexCreated")		// ALARM MONITORING
	#define APP_MUTEX_OBJECT_NAME_HCIBLVIEW				_T("KDNHCIBLVIEWMutexCreated")			// 계통도
	#define APP_MUTEX_OBJECT_NAME_HCIDLVIEW				_T("KDNHCIDLViewMutexCreated")			// 단선도
	#define	APP_MUTEX_OBJECT_NAME_HCICOMMTESTER			_T("KDNHCICommTesterMutexCreated")		// MAIN ENGINE
	#define APP_MUTEX_OBJECT_NAME_HCISYSANALYSIS		_T("KDNHCISysAnalysisMutexCreated")     // 계통분석
	#define APP_MUTEX_OBJECT_NAME_HCIALARMSYNC			_T("KDNHCIAlarmSyncMutexCreated")		// Alarm 동기화
	#define APP_MUTEX_OBJECT_NAME_HCIDMC				_T("KDNHCIDMCMutexCreated")	// DMC
	#define APP_MUTEX_OBJECT_NAME_HCISYSHISTORY			_T("KDNHCISysHistoryMutexCreated")		// 계통이력
	#define APP_MUTEX_OBJECT_NAME_HCIMEMO				_T("KDNHCIMemoMutexCreated")			// 메모
	#define APP_MUTEX_OBJECT_NAME_HCIINITSRC			_T("KDNHCIInitSrcMutexCreated")			// 초기화면
	#define APP_MUTEX_OBJECT_NAME_HCISMARTAL			_T("KDNHCISmartAlarmMutexCreated")		// 스마트 알람
	#define APP_MUTEX_OBJECT_NAME_HCICOMPARE			_T("KDNHCICompareMutexCreated")		// 스마트 알람
	#define APP_MUTEX_OBJECT_NAME_HCISUMMERY			_T("KDNHCISummeyrMutexCreated")			// 초기화면(전시용)
	#define APP_MUTEX_OBJECT_NAME_HCISRPROG				_T("KDNHCISRProgMutexCreated")		// Fault Viwer(전시용)
	#define APP_MUTEX_OBJECT_NAME_HCIINIT				_T("KDNHCIInitMutexCreated")		// 초기화면(전시용)
	#define APP_MUTEX_OBJECT_NAME_HCIINIT2				_T("KDNHCIInit2MutexCreated")		// 초기화면2(전시용)
	#define APP_MUTEX_OBJECT_NAME_HCIBSVIEW				_T("KDNHCIBSVIEWMutexCreated")			// 사고기록재현

	// HCI SHARED MEMORY MUTEX CONST 정의
	#define SHARE_HMI_PROJECT							_T("HCI_SHARE_PROJECT")
	#define SHARE_HMI_PROJECT_MUTEX						_T("HCI_SHARE_PROJECT_MUTEX")
	#define SHARE_HMI_ENVVAR							_T("HCI_SHARE_ENVVAR")
	

	// HCI 개별 모듈 define 상수
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
	//	ENUM_TLQ_WO						= 0x00000800,	// [WO] 공사용개폐기(값은 FIX, 이름은 임시)
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