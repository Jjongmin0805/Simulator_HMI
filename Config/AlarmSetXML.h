#pragma once

#include "./Xml/Xml.h"
using namespace JWXml;

class CAlarmSetXML
{
public:
	CAlarmSetXML(void);
	virtual ~CAlarmSetXML(void);

public:
	CXml		m_xmlAlarmSet;						// CXml 멤버변수 : AlarmSet XML File
	CString		m_strEXEPath;						// Program Path
		
	CString		m_strCOLOR_SET_COLOR1;
	CString		m_strCOLOR_SET_COLOR2;
	CString		m_strCOLOR_SET_COLOR3;
	CString		m_strCOLOR_SET_COLOR4;
	CString		m_strCOLOR_SET_COLOR5;
	CString		m_strCOLOR_SET_COLOR6;
	CString		m_strCOLOR_SET_COLOR7;
	CString		m_strCOLOR_SET_COLOR8;
	CString		m_strCOLOR_SET_COLOR9;
	CString		m_strCOLOR_SET_COLOR10;
	CString		m_strCOLOR_SET_COLOR1_DESC;
	CString		m_strCOLOR_SET_COLOR2_DESC;
	CString		m_strCOLOR_SET_COLOR3_DESC;
	CString		m_strCOLOR_SET_COLOR4_DESC;
	CString		m_strCOLOR_SET_COLOR5_DESC;
	CString		m_strCOLOR_SET_COLOR6_DESC;
	CString		m_strCOLOR_SET_COLOR7_DESC;
	CString		m_strCOLOR_SET_COLOR8_DESC;
	CString		m_strCOLOR_SET_COLOR9_DESC;
	CString		m_strCOLOR_SET_COLOR10_DESC;

	CString		m_strWAVE_SET_WAVE1;
	CString		m_strWAVE_SET_WAVE2;
	CString		m_strWAVE_SET_WAVE3;
	CString		m_strWAVE_SET_WAVE4;
	CString		m_strWAVE_SET_WAVE5;
	CString		m_strWAVE_SET_WAVE6;
	CString		m_strWAVE_SET_WAVE7;
	CString		m_strWAVE_SET_WAVE8;
	CString		m_strWAVE_SET_WAVE9;
	CString		m_strWAVE_SET_WAVE10;
	CString		m_strWAVE_SET_WAVE11;
	CString		m_strWAVE_SET_WAVE12;
	CString		m_strWAVE_SET_WAVE13;
	CString		m_strWAVE_SET_WAVE14;
	CString		m_strWAVE_SET_WAVE15;
	CString		m_strWAVE_SET_WAVE16;
	CString		m_strWAVE_SET_WAVE17;
	CString		m_strWAVE_SET_WAVE18;
	CString		m_strWAVE_SET_WAVE19;
	CString		m_strWAVE_SET_WAVE20;
	CString		m_strWAVE_SET_WAVE21;
	CString		m_strWAVE_SET_WAVE22;
	CString		m_strWAVE_SET_WAVE23;
	CString		m_strWAVE_SET_WAVE24;
	CString		m_strWAVE_SET_WAVE25;
	CString		m_strWAVE_SET_WAVE26;
	CString		m_strWAVE_SET_WAVE27;
	CString		m_strWAVE_SET_WAVE28;

	CString		m_strWAVE_DURATION;

	CString		m_strCONTROL_POSSIBLE_DPGRP;

	CObList		*m_pTotalInfo_AlarmSetting;						// 20140312 kylee : 종합정보-알람설정 : 알람 설정 정보
	CString		m_strTOTALINFO_SYSTEMSTATE_LASTSELECTION;		// 20140325 kylee : 종합정보-계통현황 : 마지막 선택한 항목

	ST_AE_FILTERING_SET m_AE_FilteringSet[5];


public:	

	BOOL		AlarmSetInfo ();
	BOOL		OpenXML    ( CString strFilePath, CXml &xml );

	//알람설정분리
	BOOL		OpenAlarmSet();
	void		CloseAlarmSet();

	void		SaveFile();
	void		KillProcess   ( CString strProcessName );
	int			SplitByPattern( TCHAR *strSource, CString strSplitBy, CStringArray &arraySource, CString &strOrg );

	CString		GetConfigMsg   ( CString strXPath );
	CString     GetConfigAttr  ( CString strXPath, CString strAttr  );
	CString     GetConfigDecode( CString strXPath );

	void		SetConfigMsg   ( CString strXPath, CString strValue );
	void        SetConfigNode  ( CString strXPath, CString strValue );
	void		SetConfigEncode( CString strXPath, CString strValue );
	void		GetConfigDnp   ( CString strXPath );
	void		GetConfigManual( CString strXPath );
	void		GetConfigSys   ( CString strXPath );


	void		SetConfigAlarmSetting (CString strRTUType, int nRTUMapID, CString strPointInfo, int nPointPosition, CStringArray &strInsert);
	BOOL		GetConfigAlarmSetting (CString strRTUType, int nRTUMapID, CString strPointInfo, int nPointPosition, CStringArray &strReturn);

	void		SetConfigWaveDuration (int nDuration);

	void		SetAlarmSetting( CObList* pAlarmSetting )	{	m_pTotalInfo_AlarmSetting = pAlarmSetting;	}
	CObList*	GetAlarmSetting()							{	return m_pTotalInfo_AlarmSetting;			}
	BOOL		LoadConfigAlarmSetting();
	int			FindItem( CString strRTUType, int nRTUMapID, ST_SWITCH_LIST **stSwitchList, CString strPointInfo = _T(""), int nPointPosition = -1, ST_POINT_LIST **stPointList = NULL );
	void		DeleteAlarmSetting();

	void		SetAlarmSetList(CObList *alarmList);

};