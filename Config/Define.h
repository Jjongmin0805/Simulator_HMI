#ifndef _DEFINE_H
#define _DEFINE_H

#pragma warning (disable: 4482)
#pragma warning (disable: 4996)
#pragma warning (disable: 4800)

// 매크로함수 정의
#define _N(x)							_T(x)_T("\r\n")

// Config 설정 정의
#define	LOG_NOTHING						0		// 로그기록 안함
#define	LOG_INFO						1		// INFO 로그
#define	LOG_FULL						2		// FULL 로그
#define ACM_NOT_USE						0		// ACM 사용안함
#define ACM_USE							1		// ACM 사용
#define LANGUAGE_KOR					0		// 한국어 사용
#define LANGUAGE_ENG					1		// 영어 사용

// Login 리턴값 정의
#define LOGIN_CANCEL					0		// 로그인 취소
#define LOGIN_SUCCESS					1		// 로그인 성공

// 체크박스 상태정의
#define CHECKBOX_NORMAL					0		// 체크박스 체크안된상태
#define CHECKBOX_CHECKED				1		// 체크박스 체크된상태
#define CHECKBOX_DISABLE				2		// 체크박스 체크못하는상태

// 팝업창 리턴값 정의
#define POPUP_RET_CANCEL				0		// 팝업창 취소 리턴메세지
#define	POPUP_RET_INPUT					1		// 팝업창 입력 리턴메세지
#define	POPUP_RET_MODIFY				2		// 팝업창 수정 리턴메세지
#define	POPUP_RET_DELETE				3		// 팝업창 삭제 리턴메세지
#define	POPUP_RET_CONTROL				4		// 팝업창 제어 리턴메세지
#define	POPUP_RET_CONTROL_DATA_FAIL		5		// 팝업창 제어 데이타패킷 에러리턴메세지
#define	POPUP_RET_CONTROL_ACK_FAIL		6		// 팝업창 제어 서버검증 에러리턴메세지

// 공지사항 메세지종류
#define HMI_MESSAGE_EMERGENCY			1		// 긴급
#define HMI_MESSAGE_NORMAL				2		// 보통

// 사령원 권한관리 ASSIGNTYPE 정의
#define OPR_ASSIGNTYPE_SUBGEO			0		// 사업소
#define OPR_ASSIGNTYPE_SUBSTA			1		// 변전소
#define OPR_ASSIGNTYPE_DL				2		// DL

// 프로세스간 통신 메세지 관련
#define PROCESS_END_MESSAGE				1		// 프로세스 종료메세지
#define PROCESS_USERCHG_MESSAGE			2		// 로그인 사용자변경 메세지
#define PROCESS_TOTAL_REFRESH_MSG	    3		// 종합정보 RTU정보 갱신 메세지
#define MOVE_MAIN_TO_LINE_MESSAGE		4		// 계통도 - 단선도 이동 메시지
#define MOVE_MAIN_TO_TOTAL_MESSAGE		5		// 계통도 - 종합화면 이동 메시지
#define MOVE_TOTAL_TO_MAIN_MESSAGE		6		// 종합화면 - 계통도 이동 메시지
#define MOVE_TOTAL_TO_LINE_MESSAGE		7		// 종합화면 - 단선도 이동 메시지
#define MOVE_LINE_TO_MAIN_MESSAGE		8		// 단선도 - 계통도 이동 메시지
#define MOVE_LINE_TO_TOTAL_MESSAGE		9		// 단선도 - 종합화면 이동 메시지
#define MOVE_MAIN_TO_CTRL_MESSAGE	   10		// 계통도 - 제어창 이동 메시지
#define MOVE_TOTAL_TO_CTRL_MESSAGE	   11		// 종합화면 - 제어창 이동 메시지
#define MOVE_LINE_TO_CTRL_MESSAGE	   12		// 단선도 - 제어창 이동 메시지
#define MOVE_ACM_MESSAGE			   13		// ACM 이동 메시지
#define PROCESS_PAUSE				   14		// 모든 프로세스 중단
#define PROCESS_RESTART				   15		// 모든 프로세스 재기동
#define BLINKING_STOP				   16		// 제어창 - 계통도,단선도 선택 설비 깜박임 제거
#define WAVE_SOUND_ONOFF_MESSAGE	   17		// 알람 소리 중지/켜기 변경 메시지
#define PROCESS_LINE_REFRESH_MSG	   18		// 단선도 RTU정보 갱신 메세지
#define UPDATA_RDB_ASSIGN_MESSAGE	   19		// Update RDB Assign

// 사용자정의 메세지 관련
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

// 설비종류에 따른 팝업창 구분
#define TYPE_NOTHING					0		// 타입이 없는경우
#define TYPE_CEQ						1		// 개폐기
#define TYPE_ACL						2		// 선로
#define TYPE_ECR						3		// 수용가
#define TYPE_DRU						4		// 분산전원

#define DWID_NOTHING				10000		// 타입이 없는경우
#define DWID_CEQ					20000		// 개폐기
#define DWID_CEQ_SUB1				21000		// 개폐기 메모관리
#define DWID_CEQ_SUB2				22000		// 개폐기 작업관리
#define DWID_ACL					30000		// 선로
#define DWID_ECR					40000		// 수용가
#define DWID_DRU					50000		// 분산전원

#define POPUP_INPUT						1		// 팝업창 입력
#define POPUP_MODIFY					2		// 팝업창 수정
#define POPUP_DELETE					3		// 팝업창 삭제

// PSRTYPE별 정의
#define PSRTYPE_ACL_SKY		    _T("PLSI_O")	// 선종 (가공)
#define PSRTYPE_ACL_UNDER		_T("PLSI_U")	// 선종 (지중)
#define PSRTYPE_ECR_ECR		    _T("ECR")		// 고압수용가
#define PSRTYPE_DRU_WT		    _T("WT")		// 풍력
#define PSRTYPE_DRU_PVC			_T("PV")		// 태양광
#define PSRTYPE_DRU_BATTERY	    _T("BS")		// 에너지저장장치
#define PSRTYPE_DRU_INVERTER    _T("PCS")		// 인버터
#define PSRTYPE_DRU_DIESEL		_T("DG")		// 디젤발전기
#define PSRTYPE_DRU_AIRCON		_T("ARC")		// 에어컨
#define PSRTYPE_DRU_WATER		_T("WAT")		// 상수도
#define PSRTYPE_DRU_LOAD		_T("LDS")		// 모의부하
#define PSRTYPE_SW_COMPOSITE	_T("SW_INC")	// 다회로개폐기(내부)
#define PSRTYPE_STATCOM_BESS    _T("SVC")		// STATCOM-BESS

// 맵으로 자동-수동 구분
#define RTUMAP_MANUAL					1		// 수동 RTUMAP	

// 로그메세지 프로세스별 이름정의
#define MAININFO_HMI			_T("MAININFO_HMI")
#define TOTALINFO_HMI			_T("TOTALINFO_HMI")
#define LINEINFO_HMI			_T("LINEINFO_HMI")
#define CONTROLINFO_HMI			_T("CONTROLINFO_HMI")
#define GENUNITINFO_HMI			_T("GENUNITINFO_HMI")
#define RDBVIEWER_HMI			_T("RDBVIEWER_HMI")
#define DFD_DSR					_T("DFDDSR")

// 통신 버퍼 크기
#define	HMI_COMM_BUFFER					4096

// 미들웨어통신을 위한 접두어정의
#define CON_PREFIX				_T("CON_")
#define MSG_PREFIX				_T("MSG_")
#define EVENT_PREFIX			_T("EVENT_")

#define DIAGRAM_NAME			_T("anja.mdg")
#define DIAGRAM_GEN_NAME		_T("anja_gen.mdg")

// DATA INSERT OR UPDATE
#define DATA_INSERT							1		// 리스트컨트롤에 DATA를 처음 넣는경우
#define DATA_UPDATE							2		// 리스트컨트롤에 DATA를 업데이트 하는경우

// 프로그램 ID 정의
#define PG_P001								1		// 계통도
#define PG_P002								2		// 종합정보
#define PG_P003								3		// 단선도
#define PG_P004								4		// 제어창
#define PG_P005								5		// ACM

// CONTROL TYPE 정의
#define CONTROL_TYPE_BO						1		// BO 제어
#define CONTROL_TYPE_AO						2		// AO 제어
#define CONTROL_TYPE_TAG					3		// TAG 설정
#define CONTROL_TYPE_MEASURE				4		// 계측요청
#define CONTROL_TYPE_BI						5		// BI 수동제어
#define CONTROL_TYPE_AI						6		// AI 수동제어
#define CONTROL_TYPE_PI						7		// COUNTER 수동제어
#define CONTROL_TYPE_FULL				   51		// 전체 계측
#define CONTROL_TYPE_EVENT				   52		// 이벤트 계측
#define CONTROL_TYPE_MEASURE_BI			   53		// 상태정보 계측
#define CONTROL_TYPE_MEASURE_AI			   54		// 계측정보 계측
#define CONTROL_TYPE_MEASURE_AO			   55		// 설정제어 계측
#define CONTROL_TYPE_MEASURE_COUNTER	   56		// 카운터 계측
#define CONTROL_TYPE_UNSOL				   57		// UNSOL 계측
#define CONTROL_TYPE_COLD_START			   58		// COLD START
#define CONTROL_TYPE_WARM_START			   59		// WARM START
#define CONTROL_TYPE_SYNC_START			   60		// 시각동기화

// POINT TYPE 정의
#define POINT_TYPE_BI						1		// BI POINT
#define POINT_TYPE_BO						2		// BO POINT
#define POINT_TYPE_AI						3		// AI POINT
#define POINT_TYPE_AO						4		// AO POINT
#define POINT_TYPE_COUNT					5		// COUNT POINT
#define POINT_TYPE_DEVICE					6		// DEVICE POINT
#define POINT_TYPE_CALC						7		// CALCULATION POINT

// PS LOCK 정의
#define PS_UNLOCK							0		// LOCK 해제
#define PS_LOCK								1		// LOCK 설정
#define PS_DATA_TRANS						0		// PS DATA 전송중
#define PS_DATA_TRANS_FAIL					1		// PS DATA 전송실패
#define PS_DATA_TRANS_SUCCESS				2		// PS DATA 전송성공

// 제어 DATA 정의
#define CTL_DATA_TRANS						0		// 제어 DATA 전송중
#define CTL_DATA_TRANS_FAIL					1		// 제어 DATA 전송실패
#define CTL_DATA_TRANS_SUCCESS				2		// 제어 DATA 전송성공

// 제어창 정의
#define HMI_POPUP_CONTROLINFO				1		// 제어창 팝업
#define HMI_POPUP_CONTROLINFO_MANUAL		2		// 수동입력 제어창 팝업

// FI 발생정보
#define FI_NONE								0		// FI 없음
#define FI_OCCUR							1		// FI 발생
#define FI_TYPE_TEMPOR						0		// FI 일시
#define FI_TYPE_MOMENT						1		// FI 순간
#define FI_TYPE_ETC							2		// FI
#define FI_TYPE_LOCKOUT						3		// 락아웃

// 파형리스트-파형파일 결과값 정의
#define WAVE_RESULT_OK						0		// 성공
#define WAVE_RESULT_NOT_EXIST				1		// 파일존재하지않음
#define WAVE_RESULT_FILE_BUSY				4		// 현재파일전송중
#define WAVE_RESULT_COMM_FAIL				5		// 통신실패

// 트랜드 PU( Per Unit)단위를 위한 기준치
#define BASE_VOLTAGE_VALUE				13200		// 기준 전압값 13.2 kV
#define BASE_CURRENT_VALUE				  100 		// 기준 전류값 100 A
#define BASE_ACTIVE_POWER_VALUE			  100		// 기준 유효전력값 100 kVA
#define BASE_REACTIVE_POWER_VALUE		  100		// 기준 무효전력값 100 kVA

// TLQ 값정의
#define NORMAL					   0x00000000
#define CI						   0x00000001		// 제어 금지 설정 태그
#define	SI						   0x00000002		// 데이터 취득 금지 태그
#define AI						   0x00000004		// 알람 금지 태그
#define EI						   0x00000008		// 이벤트 금지 태그
#define CS						   0x00000010		// 점검중 태그								   			  
#define MH						   0x00000020		// 최고 상한치 태그
#define ML						   0x00000040		// 최저 하한치 태그
#define HL						   0x00000080		// 상한치 태그
#define LL						   0x00000100		// 하한치 태그								   					
#define CP						   0x00000200		// 제어 진행중
#define PS						   0x00000400		// 포인트 선택중
#define MU						   0x00000800		// 공사용 개폐기수동 입력
#define NU						   0x00001000		// 업데이트 불량
#define ON						   0x00002000		// 비정상 상태
#define OFF						   0x00004000		// 포인트 OFFLINE

// 분산전원 관련 정의
#define	SINAN_PV_BESS_ESS				  702		// 팔금 PV신안파워1차(ESS) CEQID
#define	SINAN_PV_BESS_PV				  703		// 팔금 PV신안파워1차(PV) CEQID
#define	SINAN_STATCOM_BESS_SVC1			  670		// 비금 신안풍력(SVC1) CEQID
#define	SINAN_STATCOM_BESS_SVC2			  671		// 비금 신안풍력(SVC2) CEQID
#define	SINAN_STATCOM_BESS_ESS1			  672		// 비금 신안풍력(ESS1) CEQID
#define	SINAN_STATCOM_BESS_ESS2			  673		// 비금 신안풍력(ESS2) CEQID
#define	SINAN_LMGEMS_ESS				  682		// 저압 EMS (ESS) CEQID
#define	SINAN_STATCOM_BEFORE_SWITCH		  210		// 유효전력 가져오는 신안풍력 앞단 스위치	//20141205 kylee
#define MAX_TIME_CNT					 1440		// X축 최대값 24 * 60
#define	POPUP_MSG_KILL					 5000		// 팝업창 5초후 자동사라짐	
#define	PVBESS_CHART_NUM					4		// PV-BESS관련 챠트개수
#define	STCBESS_CHART_NUM					4		// STC-BESS관련 챠트개수
#define	LMGEMS_CHART1_NUM					4		// 저압 EMS관련 챠트1개수
#define	LMGEMS_CHART2_NUM					3		// 저압 EMS관련 챠트2개수

typedef struct _tagTRENDMINMAX
{
	int min;		// 최소
	int max;		// 최대

}TRENDMINMAX, *PTRENDMINMAX;

// 트리컨트롤 이미지 타입
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

// BI INDEX 주요 MEASURETYPEID
typedef enum
{
	OPNE_CLOSE				  =   1,		// 닫힘/열림
	LOCAL_REMOTE			  =   2,		// 현장/원격
	LOCK_UNLOCK				  =   3,		// 잠금/풀림
	GAS_LOW					  =   4,		// 가스압력저하	
	FI_AUTO_A				  =   6,		// FI 자동(A)	
	FI_AUTO_B				  =   7,		// FI 자동(B)
	FI_AUTO_C				  =   8,		// FI 자동(C)
	FI_AUTO_N				  =   9,		// FI 자동(N)
	FI_MANUAL_A				  =  10,		// FI 수동(A)
	FI_MANUAL_B				  =  11,		// FI 수동(B)
	FI_MANUAL_C				  =  12,		// FI 수동(C)
	FI_MANUAL_N				  =  13,		// FI 수동(N)	
	LOSS_SOURCE_A			  =  14,		// 전원측 단선결상(A)
	LOSS_SOURCE_B			  =  15,		// 전원측 단선결상(B)
	LOSS_SOURCE_C			  =  16,		// 전원측 단선결상(C)
	LOSS_LOAD_A				  =  17,		// 부하측 단선결상(A)
	LOSS_LOAD_B				  =  18,		// 부하측 단선결상(B)
	LOSS_LOAD_C				  =  19,		// 부하측 단선결상(C)
	LOCK_BODY				  =  20,		// 본체잠금	
	DOOR_OPEN				  =  21,		// 문열림
	BATTERY_DISCHARGE		  =  24,		// 축전지과방전	
	FI_A1					  = 100,		// FI 검출(A)
	FI_B1					  = 101,		// FI 검출(B)
	FI_C1					  = 102,		// FI 검출(C)
	FI_N1					  = 103,		// FI 검출(N)	
	FAULT_PERMANENT			  = 104,		// 일시고장
	FAULT_TEMPORARY			  = 105,		// 순간고장	
	RECLOSE_DISABLE			  = 118,		// 재폐로방지
	SEQUENCE_LOCK_OUT		  = 121,		// 락아웃
	LARGE_CURRENT_OPEN_FINISH = 122,		// 대전류개방완료
	FI_A2					  = 123,		// 고장검출 (A)
	FI_B2					  = 124,		// 고장검출 (B)
	FI_C2					  = 125,		// 고장검출 (C)
	FI_N2					  = 126,		// 고장검출 (N)
	FI_SEF2					  = 180,		// 고장검출 (SEF)

	OPNE_CLOSE_OCB			  = 1967,		// TDAS OCB 닫힘/열림

} BI_INDEX;

// BO INDEX 주요 MEASURETYPEID
typedef enum
{
	CLOSE_OPEN				  =  33,		// 닫힘/열림
	FI_RESET1				  =  36,		// FI RESET(수동)
	FI_RESET2				  = 219,		// 고장정보해제
	FI_RESET3				  = 431,		// FI RESET

} BO_INDEX;

// AI INDEX 주요 MEASURETYPEID
typedef enum
{	
	CURRENT_A				  =   38,		// 상전류(A)
	CURRENT_B				  =   39,		// 상전류(B)
	CURRENT_C				  =   40,		// 상전류(C)
	CURRENT_N				  =   41,		// 상전류(N)	
	VOLTAGE_A				  =   48,		// 전원측 전압(A)
	VOLTAGE_B				  =   49,		// 전원측 전압(B)
	VOLTAGE_C				  =   50,		// 전원측 전압(C)	
	FI_CURRENT_A			  =   51,		// 고장전류 (A)
	FI_CURRENT_B			  =   52,		// 고장전류 (B)
	FI_CURRENT_C			  =   53,		// 고장전류 (C)
	FI_CURRENT_N			  =   54,		// 고장전류 (N)
	VOLTAGE_LOAD_A			  =   55,		// 부하측 전압(A)
	VOLTAGE_LOAD_B			  =   56,		// 부하측 전압(B)
	VOLTAGE_LOAD_C			  =   57,		// 부하측 전압(C)
	VOLTAGE_A_87			  =   87,		// 전압(A)
	VOLTAGE_B_88			  =   88,		// 전압(B)
	VOLTAGE_C_89			  =   89,		// 전압(C)
	ACTIVE_POWER_3P			  =  239,		// 유효전력 (3상)
	REACTIVE_POWER_3P		  =  240,		// 무효전력 (3상)
	FI_CURRENT_SEF			  =  252,		// 고장전류 (SEF)
	ACTIVE_POWER_A			  =  424,		// 유효전력 (A)
	ACTIVE_POWER_B			  =  425,		// 유효전력 (B)
	ACTIVE_POWER_C			  =  426,		// 유효전력 (C)	
	REACTIVE_POWER_A		  =  427,		// 무효전력 (A)
	REACTIVE_POWER_B		  =  428,		// 무효전력 (B)
	REACTIVE_POWER_C		  =  429,		// 무효전력 (C)
	CURRENT_A_501			  =  501,		// 전류(A)-기본파 RMS (동기시점)
	CURRENT_B_502			  =  502,		// 전류(B)-기본파 RMS (동기시점)
	CURRENT_C_503			  =  503,		// 전류(C)-기본파 RMS (동기시점)
	CURRENT_N_504			  =  504,		// 전류(N)-기본파 RMS (동기시점)
	VOLTAGE_A_509			  =  509,		// 전압(A)-기본파 RMS (동기시점)
	VOLTAGE_B_510			  =  510,		// 전압(B)-기본파 RMS (동기시점)
	VOLTAGE_C_511			  =  511,		// 전압(C)-기본파 RMS (동기시점)
	ACTIVE_POWER			  = 1138,		// 유효전력
	REACTIVE_POWER			  = 1139,		// 무효전력
	VOLTAGE_A_1424			  = 1424,		// 전원1차전압(PriSrcV)-A
	CURRENT_A_1425			  = 1425,		// 부하1차전류(PriLoadA)-A
	PRIW_A					  = 1429,		// 유효전력(PriW)-A
	PRIVAR_A				  = 1430,		// 무효전력(PriVAr)-A	
	VOLTAGE_B_1442			  = 1442,		// 전원1차전압(PriSrcV)-B
	CURRENT_B_1443			  = 1443,		// 부하1차전류(PriLoadA)-B
	PRIW_B					  = 1447,		// 유효전력(PriW)-B
	PRIVAR_B				  = 1448,		// 무효전력(PriVAr)-B
	VOLTAGE_C_1460			  = 1460,		// 전원1차전압(PriSrcV)-C
	CURRENT_C_1461			  = 1461,		// 부하1차전류(PriLoadA)-C	
	PRIW_C					  = 1465,		// 유효전력(PriW)-C
	PRIVAR_C				  = 1466,		// 무효전력(PriVAr)-C

} AI_INDEX;

#include <afxdisp.h>

// FLASH 제어 클래스
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