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
	FC_TIMER				= 0x0001, //0.타이머체크 	
	FC_PS_REQ				= 0x1001, //1.포인트 선택 및 해제
	FC_CTRL_REQ				= 0x1002, //2.포인트 제어
	FC_AO_SET_REQ			= 0x1003, //3.설정 명령
	FC_EVENT_REQ			= 0x1004, //4.이벤트 계측
	FC_ALL_MEAS_REQ			= 0x1005, //5.전체 계측
	FC_BI_MEAS_REQ			= 0x1006, //6.Binary Input 계측 - BO는 서버에서 값을 주지 않는다 AI값을 사용하면 됨
	FC_AI_MEAS_REQ			= 0x1007, //7.Analog Input 계측
	FC_AO_MEAS_REQ			= 0x1008, //8.Analog Output 계측	
	FC_PI_MEAS_REQ			= 0x1009, //9.Coount 계측
	FC_WARM_RESTART			= 0x100A, //10.WARM RESTART
	FC_COLD_RESTART			= 0x100B, //11.Cold RESTART
	FC_SYNC_TIME			= 0x100C, //12.시각동기화
	FC_AI_LIMIT_REQ			= 0x100D, //13.Analog Point Limit 설정
	FC_TLQ_REQ				= 0x100E, //14.TLQ 설정 및 해제
	FC_UNSOL_REQ			= 0x100F, //15.Unsol Enable/Disable 설정
	FC_WAVE_LIST_REQ		= 0x1010, //파형리스트 요청
	FC_WAVE_FILE_REQ		= 0x1011, //파형파일 요청
	FC_OPR_DATA_REQ			= 0x1012, //운영정보 데이터 요청
	FC_OPR_SET_REQ			= 0x1013, //운영정보 설정 요청
	FC_LINE_STATUS			= 0xFFFF, //배전선로 구간정보 상태 (보류)
	FC_RTU_STATUS_REQ		= 0x1014, //설비 상태정보 요청
	FC_MANUAL_REQ		    = 0x1015, //설비 수동입력 요청

	FC_CTRL_VALID_RES		= 0x4001, //16.Control 유효성 검증 결과 응답
	FC_CTRL_RESULT_RES		= 0x4002, //Control 결과 응답(포린트 선택, 포인트제어 명령결과, Cold, Warm Restart, 시각동기화)
	FC_WAVE_LIST_RES		= 0x4003, //파형리스트 수신완료 응답
	FC_WAVE_FILE_RES		= 0x4004, //파형파일 수신완료 응답
	FC_OPR_DATA_RES			= 0x4005, //운영정보 데이터 수신완료 응답(운영정보 결과)
	FC_RTU_STATUS_RES		= 0x4006, //설비 상태정보 전송(사활선 정보도 같이 들어옴)

	FC_MSG_UPDATE			= 0xA001, //공지사항 업데이트 요청
	FC_CONTRUCT_UPDATE		= 0xA002, //작업관리 업데이트 요청
	FC_MEMO_UPDATE			= 0xA003, //메모관리 업데이트 요청
	FC_CONTROL_UPDATE		= 0xA004, //제어관리 업데이트 요청
	FC_DFD_UPDATE			= 0xA008, //DFD 판단 결과치 전송
	FC_DSR_UPDATE			= 0xA009,  //DSR 결과치 전송
	FC_EMERGENCY_MSG_UPDATE	= 0xA00A //긴급공지사항 업데이트 요청
};

#pragma pack(1)
//미들웨어 송신 패킷 헤더
typedef struct __stSendHeader__
{
	USHORT	usFcode;			//!< Function Code
	USHORT	usLength;			//!< 메시지 총길이
	UINT	uiTime;				//!< HMI 전송시간(__time32_t형식)
	UINT	uiSeqId;			//!< HMI에서 정의한 고유한 ID
	USHORT	usHmiId;			//!< 환경설정 파일에 정의된 HMI ID
	USHORT	usOperatorId;		//!< 사령원 ID
	USHORT	usProgId;			//!< 프로그램 ID
	USHORT	usCount;			//!< 레코드 개수
} ST_SENDHEADER, *LPST_SENDHEADER;

//미들웨어 비동기송신 패킷 헤더
typedef struct __stSendHeader2__
{
	USHORT	usFcode;			//!< Function Code
	USHORT	usLength;			//!< 메시지 총길이
	UINT	uiTime;				//!< HMI 전송시간(__time32_t형식)
	UINT	uiSeqId;			//!< HMI에서 정의한 고유한 ID
	USHORT	usHmiId;			//!< 환경설정 파일에 정의된 HMI ID	
	USHORT	usProgId;			//!< 프로그램 ID
	USHORT	usCount;			//!< 레코드 개수
} ST_SENDHEADER2, *LPST_SENDHEADER2;

//미들웨어 수신 패킷 헤더
typedef struct __stRecvHeader__
{
	USHORT	usFcode;			//!< Function Code
	USHORT	usLength;			//!< 메시지 총길이
	UINT	uiTime;				//!< HMI 전송시간(__time32_t형식)
	UINT	uiSeqId;			//!< HMI에서 정의한 고유한 ID
	USHORT	usHmiId;			//!< 환경설정 파일에 정의된 HMI ID
	//USHORT	usOperatorId;		//!< 사령원 ID
	USHORT	usProgId;			//!< 프로그램 ID
	USHORT	usCount;			//!< 레코드 개수
} ST_RECVHEADER, *LPST_RECVHEADER;

//1.포인트 선택 및 해제
//14. TLQ 설정 및 해제
typedef struct __stPS_REQ__
{
	UINT		uipid;			//PID
	USHORT		usPtType;		//!< 포인트 타입 - 송한민 이사 추가 2013-03-18
	USHORT		usIndex;		//Index ID
	USHORT		usSetTLQ;		//TLQ
	USHORT		usSetOrRel;		//설정(1), 해제(0)
} ST_PS_REQ, *LPST_PS_REQ;

typedef struct __stTLQ_REQ__
{
	UINT		uipid;			//PID
	USHORT		usPtType;		//!< 포인트 타입 - 송한민 이사 추가 2013-03-18
	USHORT		usIndex;		//Index ID
	USHORT		usSetTLQ;		//TLQ
	USHORT		usSetOrRel;		//설정(1), 해제(0)
} ST_TLQ_REQ, *LPST_TLQ_REQ;

//2.포인트 선택 및 해제
typedef struct __stCTRL_REQ__
{
	UINT		uipid;			//<!DMS서버에서 정의한 제어대상 포인트의 고유ID 없으면 0
	//USHORT		usPtType;		//!< 포인트 타입 - 송한민 이사 추가 2013-03-18
	USHORT		usIndex;		//Index ID
	UCHAR		ucCtrl_Val;		//<!제어할 상태값
} ST_CTRL_REQ, *LPST_CTRL_REQ;

//3.설정명령
typedef struct __stAO_SET_REQ__
{
	UINT		uipid;			//<!DMS서버에서 정의한 제어대상 포인트의 고유ID 없으면 0
	USHORT		uiIndex;		//Index ID
	FLOAT		fCtrl_Val;		//<!제어할 상태값
} ST_AO_SET_REQ, *LPST_AO_SET_REQ;

//4.이벤트계측
//5.전체계측
//6.Binary Input 계측
//7.Analog Input 계측
//8.Analog Output 계측
//9.COUNT 계측
//10. Warm Restart
//11. Cold Restart
//12. 시각동기화
typedef struct __stEVENT_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count 수량만큼 RUID 구성
} ST_EVENT_REQ, *LPST_EVENT_REQ;

typedef struct __stALLMEAS_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count 수량만큼 RUID 구성
} ST_ALLMEAS_REQ, *LPST_ALLMEAS_REQ;

typedef struct __stBIMEAS_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count 수량만큼 RUID 구성
} ST_BIMEAS_REQ, *LPST_BIMEAS_REQ;

typedef struct __stAIMEAS_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count 수량만큼 RUID 구성
} ST_AIMEAS_REQ, *LPST_AIMEAS_REQ;

typedef struct __stAOMEAS_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count 수량만큼 RUID 구성
} ST_AOMEAS_REQ, *LPST_AOMEAS_REQ;

typedef struct __stCOUNTMEAS_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count 수량만큼 RUID 구성
} ST_COUNTMEAS_REQ, *LPST_COUNTMEAS_REQ;

typedef struct __stWARM_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count 수량만큼 RUID 구성
} ST_WARM_REQ, *LPST_WARM_REQ;

typedef struct __stCOLD_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count 수량만큼 RUID 구성
} ST_COLD_REQ, *LPST_COLD_REQ;

typedef struct __stTIME_REQ__
{
	UINT		uiRuId;			//<!RTUDevice ID, Count 수량만큼 RUID 구성
} ST_TIME_REQ, *LPST_TIME_REQ;

//13. Analog Point limit 설정
typedef struct __stAI_LIMIT_REQ__
{
	UINT		uiRuId;			//<!DMS서버에서 정의한 제어대상 포인트의 고유ID 없으면 0
	USHORT		usIndex;		//Index ID
	USHORT		usLimitId;		//!< R_MAX, R_MIN, L_MAX, L_MIN
	FLOAT		fLimitValue;	//!< 설정 limit 값
} ST_AI_LIMIT_REQ, *LPST_AI_LIMIT_REQ;

//15. Unsol Enable/Disable 요청
typedef struct __stUNSOL_REQ__
{
	UINT		uiRuId;			//<! DMS서버에서 정의한 제어대상 포인트의 고유ID 없으면 0
	UCHAR		ucUnsol_c1;		//!< Class1 Enable=1 / Disable=0
	UCHAR		ucUnsol_c2;		//!< Class2 Enable=1 / Disable=0
	UCHAR		ucUnsol_c3;		//!< Class3 Enable=1 / Disable=0

} ST_UNSOL_REQ, *LPST_UNSOL_REQ;

//16. Control 검증 결과(서버 Validation 체크 결과)
//17. 제어명령 결과 전송
typedef struct __stRESULT_RES__
{
	USHORT		usErrorCode;			//<! 에러코드(RDB에 에러코드 테이블 생성)
	CHAR		Desc[32];			//!< 에러내용
} ST_RESULT_RES, *LPST_RESULT_RES;

//47. 파형리스트 요청
//48. 파형파일 요청
typedef struct __stWAVE_REQ__
{
	UINT		uiRuId;					//<! RTUDevice ID, Count 수량만큼 RUID 구성
	CHAR		szWaveName[16];			//!< WAVE_INFO, 파형파일이름
} ST_WAVE_REQ, *LPST_WAVE_REQ;

//49. 파형리스트 수신결과
//50. 파형파일 수신결과
typedef struct __stWAVE_RES__
{
	UINT		uiResultCode;			//<! RTUDevice ID, Count 수량만큼 RUID 구성
	CHAR		szWaveName[16];			//!< WAVE_INFO, 파형파일이름
} ST_WAVE_RES, *LPST_WAVE_RES;


//51. 운영정보데이터 요청
typedef struct __stOPR_DATA_REQ__
{
	UINT		uiRuId;						//<! RTUDevice ID, Count 수량만큼 RUID 구성
	CHAR		szConfigName[16];			//!< CONFIG_Name 설정 파일 이름
} ST_OPR_DATA_REQ, *LPST_OPR_DATA_REQ;

//52. 운영정보데이터 설정요청
typedef struct __stOPR_SET_REQ__
{
	UINT		uiRuId;						//<! RTUDevice ID, Count 수량만큼 RUID 구성
	BYTE		bySettingVlaue[64];			//!< 64byte(2 * 32Index) 값 설정
} ST_OPR_SET_REQ, *LPST_OPR_SET_REQ;

//56. 운영정보 데이터 수신 결과
typedef struct __stOPR_DATA_RES__
{
	USHORT		usResultCode;				//<!에러코드(RDB에 에러코드 테이블 생성)
} ST_OPR_DATA_RES, *LPST_OPR_DATA_RES;

//57. 배전선로 구간 상태정보
typedef struct __stLINE_STATUS_RES__
{
	UINT		nCeqId;					//<! 배전선로 CEQID
	UINT		nSTatus;				//<! 선로상태(1=사선, 2= 활선)
	UINT		nTie;					//!< 연계구간(1), 자기구간(0)
} ST_LINE_STATUS_RES, *LPST_LINE_STATUS_RES;

//58. 공지사항
//59. 작업관리
//60. 메모관리
typedef struct __stHMI_UPDATE_
{
	USHORT		usFcode;			//!< Function Code
	UINT		uiLength;			//!< 메시지 총길이
	__time32_t	uiTime;				//!< HMI 전송시간(__time32_t형식)
} ST_HMI_UPDATE, *LPST_HMI_UPDATE;

//62. 설비상태정보 요청
// 데이터 없음(명령만 정송)

//16. control 검증 결과
typedef struct __stCTRL_VALID_
{
	//UINT	uiSeqId;				//!< HMI에서 정의한 고유한 ID - 요청과 응답이 맞는 지 확인하는 데 사용(요청시 입력됨)
	USHORT	uiErrorCode;			//!< 에러 코드
	char	szErrDesc[32];			//!< 에러 내용
} ST_CTRL_VALID, *LPST_CTRL_VALID;

//17. 제어명령 결과 전송
typedef struct __stCTRL_RESULT_
{
	//UINT	uiSeqId;				//!< HMI에서 정의한 고유한 ID - 요청과 응답이 맞는 지 확인하는 데 사용(요청시 입력됨)
	USHORT	uiErrorCode;			//!< 에러 코드
	char	szErrDesc[32];			//!< 에러 내용
} ST_CTRL_RESULT, *LPST_CTRL_RESULT;

//41. 파형 리스트 결과 전송
typedef struct __stWAVE_LIST_
{
	//UINT	uiSeqId;				//!< HMI에서 정의한 고유한 ID - 요청과 응답이 맞는 지 확인하는 데 사용(요청시 입력됨)
	USHORT	uiResult;				//!< 0:OK, 1:Doesn't exist, 4:File Busy, 5:통신실패 
	char	szWaveList[16];			//!< 파일 리스트
} ST_WAVE_LIST, *LPST_WAVE_LIST;

//41. 파형 파일 결과 전송
typedef struct __stWAVE_FILE_
{
	//UINT	uiSeqId;				//!< HMI에서 정의한 고유한 ID - 요청과 응답이 맞는 지 확인하는 데 사용(요청시 입력됨)
	USHORT	uiResult;				//!< 0:OK, 1:Doesn't exist, 4:File Busy, 5:통신실패 
	char	szWaveFile[16];			//!< 파일명
} ST_WAVE_FILE, *LPST_WAVE_FILE;

//55. 운영정보 결과
typedef struct __stOPR_DATA_RESULT_
{
	//UINT	uiSeqId;				//!< HMI에서 정의한 고유한 ID - 요청과 응답이 맞는 지 확인하는 데 사용(요청시 입력됨)
	USHORT	uiResult;				//!< 0:OK, 1:Doesn't exist, 4:File Busy, 5:통신실패 
} ST_OPR_DATA_RESULT, *LPST_OPR_DATA_RESULT;

//61. 설비상태정보전송 : 사활/연계 정보
typedef struct __stRTU_STATUS_
{
	//UINT	uiSeqId;				//!< HMI에서 정의한 고유한 ID - 요청과 응답이 맞는 지 확인하는 데 사용(요청시 입력됨)
	UINT	uiCeqId;				//!< CEQID
	UCHAR	ucState;				//!< (1=Live, 2=Outage, 3=고장구간(추후))
	UINT	uiOnlineDL;				//!< 실시간 DL ID
	UCHAR	ucTieState;				//!< 연계구간(1), 자기구간(0)
	UCHAR	ucTieSwflag;			//!< 상시개방점(1), Other(0), 스위치인 경우에만
	
} ST_RTU_STATUS, *LPST_RTU_STATUS;

//62. 수동입력 요청
typedef struct __stMANUAL_REQ_
{	
	UINT	uiRuId;					//!< RTU ID
	USHORT	usPtType;				//!< 포인트 타입 BI(1),AI(3),PI(5)
	USHORT	usIndex;				//Index ID
	FLOAT	fSetValue;				//수동설정값
	
} ST_MANUAL_REQ, *LPST_MANUAL_REQ;

typedef struct _tagASYNCDATA
{
	ST_RECVHEADER stRecvHeader;
	BYTE	ucData[4096];

}ASYNCDATA, *PASYNCDATA;

///정의 확인 필요
typedef struct _tagEVENTDATA
{
	char	evtId[24];		//!< 이벤트 번호
	USHORT	evnet_code;		//!< 이벤트 코드
	INT		SoeTime;		//!< RTU 시각 SEC
	USHORT	SoeTime_ms;		//!< RTU 시각 ms
	INT		EvtTime;		//!< 서버 시각 SEC
	USHORT	EvtTime_ms;		//!< 서버 시각 ms
	INT		GGRID;			//!< 본부(지사)코드
	INT		SGRID;			//!< 지점(사업소)코드
	INT		SSID;			//!< 변전소 코드
	INT		DLID;			//!< DL ID
	INT		CEQID;			//!< CEQ ID
	INT		RUID;			//!< RTUDevice ID
	INT		PtType;			//!< 포인트 타입
	INT		PID;			//!< 포인트 번호
	USHORT	Index;			//!< DNP 인덱스 번호
	FLOAT	Value;			//!< 포인트 값
	FLOAT	OldValue;		//!< 이전 값
	BYTE	Alarm;			//!< Alarm 여부
	BYTE	Important;		//!< 중요 알람
	USHORT	Tlq;			//!< TLQ 값	
	char	message[128];	//!< 이벤트 정보

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