#pragma once

#include "./Xml/Xml.h"

using namespace JWXml;

#define DNP_HEADPOINT_SIZE		50
#define MAININFOXML		0
#define TOTALINFOXML	1
#define LINEINFOXML		2
#define CONTROLINFOXML  3

struct CAL_INDEX
{
	int m_CEQ;
	int m_NO;

	CAL_INDEX(){}
	CAL_INDEX(int _CEQ, int _NO)
	{
		m_CEQ = _CEQ;
		m_NO = _NO;
	}
};
template<class T>
struct Comp2
{
		bool operator()(const T& t1, const T& t2) const
		{
			return ((t1.m_CEQ < t2.m_CEQ) || ((t1.m_CEQ == t2.m_CEQ) && (t1.m_NO < t2.m_NO))); //((t1.m_CEQ == t2.m_CEQ) && (t1.m_NO == t2.m_NO)));
		}
};
struct SECTION_INDEX
{
	int m_CEQ;

	SECTION_INDEX(){}
	SECTION_INDEX(int _CEQ)
	{
		m_CEQ = _CEQ;
	}
};
template<class T>
struct Comp_Sec
{
		bool operator()(const T& t1, const T& t2) const
		{
			return ((t1.m_CEQ < t2.m_CEQ) || ((t1.m_CEQ == t2.m_CEQ)));
		}
};
typedef struct __tagSectionList__
{
	int nCEQ;
	int nSwCEQ;
	int nREFCEQ;

}ST_SECTION_LIST, *PST_SECTION_LIST;

typedef struct __tagDnpHeadPoint__
{
	SHORT	index;
	CString type;
	CString	point_name;
	SHORT	size;

}DNP_HEAD_POINT, *PDNP_HEAD_POINT;

typedef struct POINT_LIST_INFO
{
	int				nSeq;				// 순번
	int				nTextColor;			// 선택된 Text 색상 번호
	int				nBGColor;			// 선택된 배경 색상 번호
	int				nWaveSet;			// 선택된 알람 소리 번호
	UINT			uImportant;			// 중요도 설정 여부
	CString			strPointInfo;		// 포인트 정보
	int				nPosition;			// BI, BO, AI, AO 각각의 Position
} ST_POINT_LIST;

typedef struct SWITCH_LIST_INFO
{
	int				nID;				// ID 번호
	int				nRTUMapID;			// RTU Map ID
	CString			strRTUType;			// RTU 종류명
	CObList			*pPointList;		// 포인트 목록 리스트
} ST_SWITCH_LIST;

typedef struct AE_FILTERING_SET_INFO
{
	BOOL			bIsSet;				// XML에 설정된 항목이 있는지 여부
	CTime			ctSTime;			// 시작시간
	CTime			ctETime;			// 종료시간
	BOOL			bContinue;			// continue 체크여부
	BOOL			bAckedAlarm;		// Ack된 알람 체크여부
	BOOL			bNonAckedAlarm;		// Non Ack 알람 체크여부
	int				nSSID;				// 변전소 ID
	int				nDLID;				// 변전소 ID
	int				nSelAE;				// 알람 / 이벤트 구분
	int				nImportance;		// 중요도 구분
	CString			strFilteringName;	// 필터링 이름
} ST_AE_FILTERING_SET;

class CConfigXML
{
public:
	CConfigXML(void);
	virtual ~CConfigXML(void);

public:
	typedef std::map<CAL_INDEX, int, Comp2<CAL_INDEX>> CALIndex;				//계산 포인트 접근을 위한 리스트
	CALIndex m_calIndex;								   //모든 계산 포인트 인덱스

	//typedef std::map<SECTION_INDEX, list< ST_SECTION_LIST * >::iterator,  Comp_Sec<int>> SecIndex; //사활선 참조 정보 맵			   
	//SecIndex m_SecIndex;

	//std::list< ST_SECTION_LIST * > SECList;	//사활선 참조 정보 리스트
public:
	CMap <CString, LPCTSTR ,CString, LPCTSTR  > m_mapXmlList;

	CXml		m_xmlLang;							// CXml 멤버변수 : Language XML File
	CXml		m_xmlConfig;						// CXml 멤버변수 : Config XML File
	CXml		m_xmlCALInfo;						// CXml 멤버변수 : 계산포인트 XML File
	CXml		m_xmlSectionInfo;					// CXml 멤버변수 : 사활선 참조 XML File
	CString		m_strEXEPath;						// MainInfoHMI.exe Prgram Path

	CString		m_strENGINE_PROJECT_TITLE;
	CString		m_strENGINE_LOG_PATH;
	CString		m_strENGINE_ACM_PATH;
	CString		m_strENGINE_WAVE_PATH;
	CString		m_strENGINE_DRAW_PATH;
	CString		m_strENGINE_EXCEL_PATH;
	CString		m_strENGINE_PNG_PATH;
	CString		m_strENGINE_SKIN_PATH;
	CString		m_strENGINE_XML_PATH;
	CString		m_strENGINE_SYM_PATH;
	CString		m_strENGINE_DAT_PATH;				// 파형목록, 파형파일 관련 폴더
	CString		m_strENGINE_CAP_PATH;				// 캡쳐 파일 저장
	CString		m_strENGINE_DBLOAD_TYPE;			// 공유메모리 로딩 타입 - 0: 정상 1: RDBViewer에서 로딩
	
	CString		m_strLOG_LOG_LEVEL;	
	CString		m_strACM_USE_ACM;
	
	CString		m_strMIDDLE_WARE_SCAN_INTERVAL;
	CString		m_strMIDDLE_WARE_ASYN_INTERVAL;
	CString		m_strMIDDLE_WARE_EVENT_INTERVAL;
	CString		m_strMIDDLE_WARE_SYSTEM_INTERVAL;
	CString		m_strMIDDLE_WARE_CONTROL_INTERVAL;
	CString		m_strMIDDLE_WARE_COMPUTER_NAME;
	CString		m_strMIDDLE_WARE_CLIENT_NAME1;
	CString		m_strMIDDLE_WARE_CLIENT_NAME2;
	CString		m_strMIDDLE_WARE_CLIENT_NAME3;
	CString		m_strMIDDLE_WARE_CLIENT_NAME4;
	CString		m_strMIDDLE_WARE_CLIENT_NAME5;
	
	CString		m_strDATABASE_DB_INTERVAL;
	CString		m_strDATABASE_DB_SERVER1;
	CString		m_strDATABASE_DB_SERVER2;
	CString		m_strDATABASE_DB_PORT;
	CString		m_strDATABASE_DB_USER;
	CString		m_strDATABASE_DB_PASSWORD;
	CString		m_strDATABASE_DB_COMMON;
	CString		m_strDATABASE_DB_OPER;
	CString		m_strDATABASE_DB_HISTORY;
	
	CString		m_strLANGUAGE_LANG_SET;	
	CString		m_strOPERATOR_OP_ID;
	CString		m_strOPERATOR_OP_NUM;
	CString		m_strOPERATOR_OP_NAME;
	CString		m_strOPERATOR_OP_LOGIN;

	CString		m_strCLIENT1_START_AXIS_X;
	CString		m_strCLIENT1_START_AXIS_Y;
	CString		m_strCLIENT1_END_AXIS_X;
	CString		m_strCLIENT1_END_AXIS_Y;
	CString		m_strCLIENT1_ZOOM_VAL;
	CString		m_strCLIENT1_DIAGRAM_X;
	CString		m_strCLIENT1_DIAGRAM_Y;
	CString		m_strCLIENT1_ZOOM_LEVEL;
	CString		m_strCLIENT1_STEP_LEVEL;
	CString     m_strCLIENT1_NAMEORINDEX;
	CString		m_strCLIENT1_TYPE;
	CString		m_strCLIENT1_SELECT_PHASE;
	CString		m_strCLIENT1_SELECT_VOLT;
	CString		m_strCLIENT1_FI_MOVE;
	CString		m_strCLIENT1_DL_LINK;
	CString		m_strCLIENT1_LINE_VIEW;
	CString		m_strCLIENT1_LINE_OPTION;
	CString		m_strCLIENT1_LINK_COLOR;
	CString		m_strCLIENT1_LOOP_COLOR;
	CString		m_strCLIENT1_COLOR1;
	CString		m_strCLIENT1_COLOR2;
	CString		m_strCLIENT1_COLOR3;
	CString		m_strCLIENT1_COLOR4;
	CString		m_strCLIENT1_COLOR5;
	CString		m_strCLIENT1_COLOR6;
	CString		m_strCLIENT1_COLOR7;
	CString		m_strCLIENT1_COLOR8;
	CString		m_strCLIENT1_COLOR9;
	CString		m_strCLIENT1_COLOR10;
	CString		m_strCLIENT1_DEAD_COLOR;
	CString		m_strCLIENT1_ALIVE_COLOR;
	CString		m_strCLIENT1_ACMCOLUMN;

	CString		m_strCLIENT2_START_AXIS_X;
	CString		m_strCLIENT2_START_AXIS_Y;
	CString		m_strCLIENT2_END_AXIS_X;
	CString		m_strCLIENT2_END_AXIS_Y;
	CString		m_strCLIENT2_CEQID;
	CString		m_strCLIENT2_PSR;

	CString		m_strCLIENT2_RTREND[8];
	CString		m_strCLIENT2_RTREND_COLOR[8];
	
	CString		m_strCLIENT3_START_AXIS_X;
	CString		m_strCLIENT3_START_AXIS_Y;
	CString		m_strCLIENT3_END_AXIS_X;
	CString		m_strCLIENT3_END_AXIS_Y;
	CString		m_strCLIENT3_ZOOM_VAL;
	CString		m_strCLIENT3_DIAGRAM_X;
	CString		m_strCLIENT3_DIAGRAM_Y;
	CString		m_strCLIENT3_FOCUS_DL;
	CString		m_strCLIENT3_OPEN_DL;
	CString		m_strCLIENT3_ZOOM_LEVEL;
	CString		m_strCLIENT3_STEP_LEVEL;
	CString     m_strCLIENT3_NAMEORINDEX;
	CString		m_strCLIENT3_TYPE;
	CString		m_strCLIENT3_SELECT_PHASE;
	CString		m_strCLIENT3_SELECT_VOLT;
	CString		m_strCLIENT3_FI_MOVE;
	CString		m_strCLIENT3_DL_LINK;
	CString		m_strCLIENT3_LINE_VIEW;
	CString		m_strCLIENT3_LINE_OPTION;
	CString		m_strCLIENT3_LINK_COLOR;
	CString		m_strCLIENT3_LOOP_COLOR;
	CString		m_strCLIENT3_COLOR1;
	CString		m_strCLIENT3_COLOR2;
	CString		m_strCLIENT3_COLOR3;
	CString		m_strCLIENT3_COLOR4;
	CString		m_strCLIENT3_COLOR5;
	CString		m_strCLIENT3_COLOR6;
	CString		m_strCLIENT3_COLOR7;
	CString		m_strCLIENT3_COLOR8;
	CString		m_strCLIENT3_COLOR9;
	CString		m_strCLIENT3_COLOR10;
	CString		m_strCLIENT3_DEAD_COLOR;
	CString		m_strCLIENT3_ALIVE_COLOR;
	CString		m_strCLIENT3_ACMCOLUMN;

	//CString		m_strVIEW_ZOOM_LEVEL;
	//CString		m_strVIEW_STEP_LEVEL;
	//CString		m_strVIEW_NAMEORINDEX;
	//CString		m_strVIEW_TYPE;
	//CString		m_strVIEW_SELECT_PHASE;
	//CString		m_strVIEW_SELECT_VOLT;
	//CString		m_strVIEW_FI_MOVE;
	//CString		m_strVIEW_DL_LINK;

	CString		m_strCONTROL_POSSIBLE_DPGRP;

	DNP_HEAD_POINT	m_stDnpPoint[DNP_HEADPOINT_SIZE];
	DNP_HEAD_POINT	m_stManualPoint[DNP_HEADPOINT_SIZE];
	DNP_HEAD_POINT	m_stSysPoint[DNP_HEADPOINT_SIZE];

	//CObList		*m_pTotalInfo_AlarmSetting;						// 20140312 kylee : 종합정보-알람설정 : 알람 설정 정보
	CString		m_strTOTALINFO_SYSTEMSTATE_LASTSELECTION;		// 20140325 kylee : 종합정보-계통현황 : 마지막 선택한 항목

	ST_AE_FILTERING_SET m_AE_FilteringSet[5];


public:	
	BOOL		LangInfo   ();
	BOOL		ConfigInfo ();
	void		SetDefaultOption ( CString strOP_NAME, CString strOP_NUM );
	void		UserInfo( CString strOP_NAME, CString strOP_NUM );
	BOOL		IsOperator(CString strOP_NAME, CString strOP_NUM);
	BOOL		XmlConfigInfo (int nType); // 20150212 ohb korxml 정보
	BOOL		CALInfo	   ();
	BOOL		SectionInfo ();
	BOOL		OpenXML    ( CString strFilePath, CXml &xml );
	BOOL		OpenConfig ();
	void		CloseConfig();
	void		LogInfo ( CString strProgram, CString strMsg, int nLogLevel, CString strStart = _T("") );
	void		SaveFile();
	void		KillProcess   ( CString strProcessName );
	int			SplitByPattern( TCHAR *strSource, CString strSplitBy, CStringArray &arraySource, CString &strOrg );

	CString     GetLangPath    ();
	CString		GetLangMsg     ( CString strProgram, CString strType, UINT nID );
	CString     GetCalPoint    ( CString strXPath );
	CString		GetConfigMsg   ( CString strXPath );
	CString     GetConfigAttr  ( CString strXPath, CString strAttr  );
	CString     GetConfigDecode( CString strXPath );
	CString		GetBuildTime   ();
	void		SetConfigMsg   ( CString strXPath, CString strValue );
	void		SetConfigMsgNewNode( CString strXPath, CString strValue );//ohb 노드 없을시  노드 생성하여 값 셋팅
	void        SetConfigNode  ( CString strXPath, CString strValue );
	void		SetConfigEncode( CString strXPath, CString strValue );
	void		GetConfigDnp   ( CString strXPath );
	void		GetConfigManual( CString strXPath );
	void		GetConfigSys   ( CString strXPath );

	void		SetConfigUser1 ();
	void		SetConfigUser2 ();
	void		SetConfigUser3 ();
	void		SetConfigLogin ( int nStatus );
	void		SetTrendData   ( CString strFileName, int nSeries, int nSize, int pData[][MAX_TIME_CNT] );
	void		SaveTrendData  ( CString strFileName, int nSeries, int nSize, int pData[][MAX_TIME_CNT] );
	void		DelTrendData   ( CString strFileName, int nSeries, int nSize, int pData[][MAX_TIME_CNT] );

	//void		SetConfigAlarmSetting (CString strRTUType, int nRTUMapID, CString strPointInfo, int nPointPosition, CStringArray &strInsert);
	//BOOL		GetConfigAlarmSetting (CString strRTUType, int nRTUMapID, CString strPointInfo, int nPointPosition, CStringArray &strReturn);

	//void		SetConfigWaveDuration (int nDuration);

	//void		SetAlarmSetting( CObList* pAlarmSetting )	{	m_pTotalInfo_AlarmSetting = pAlarmSetting;	}
	//CObList*	GetAlarmSetting()							{	return m_pTotalInfo_AlarmSetting;			}
	//BOOL		LoadConfigAlarmSetting();

	void		SetConfigSystemStateSelectedItem(int nCEQID);
	BOOL		ChkTrendData( CString strFileName );	//20141207 kylee

	BOOL		ChkTrendListFile(CString strPath );	//20150128 ohb
};