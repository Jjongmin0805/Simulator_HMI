#include "stdafx.h"
#include "AlarmSetXML.h"
#include <tlhelp32.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlarmSetXML::CAlarmSetXML()
{
	m_pTotalInfo_AlarmSetting = NULL;
}

CAlarmSetXML::~CAlarmSetXML()
{	
	DeleteAlarmSetting();
}

BOOL CAlarmSetXML::AlarmSetInfo()
{
	BOOL bRet = TRUE;
	CString strAlarmSetPath, strErrMsg, strAttrMsg;
	
	TCHAR tzFileName[ MAX_PATH ], tzDrive[ _MAX_DRIVE ], tzPath[ _MAX_DIR ], tzName[ _MAX_FNAME ], tzExt[ _MAX_EXT ];
	TCHAR tzTemp[ MAX_PATH ] = { 0, };

	GetModuleFileName( NULL, tzFileName, sizeof(tzFileName) );
	_tsplitpath_s( tzFileName, tzDrive, _MAX_DRIVE, tzPath, _MAX_DIR, tzName, _MAX_FNAME, tzExt, _MAX_EXT );

	m_strEXEPath.Format( _T("%s%s"), tzDrive, tzPath );	
	//알람설정파일분리
	strAlarmSetPath.Format( _T("%s%s"), m_strEXEPath, _T("alarmSet.xml") );
	
	bRet = OpenXML( strAlarmSetPath, m_xmlAlarmSet );
	if( !bRet )		return bRet;
	
	m_strCOLOR_SET_COLOR1            = GetConfigMsg ( _T("//HMI/COLOR_SET/COLOR1") );
	m_strCOLOR_SET_COLOR2            = GetConfigMsg ( _T("//HMI/COLOR_SET/COLOR2") );
	m_strCOLOR_SET_COLOR3            = GetConfigMsg ( _T("//HMI/COLOR_SET/COLOR3") );
	m_strCOLOR_SET_COLOR4            = GetConfigMsg ( _T("//HMI/COLOR_SET/COLOR4") );
	m_strCOLOR_SET_COLOR5            = GetConfigMsg ( _T("//HMI/COLOR_SET/COLOR5") );
	m_strCOLOR_SET_COLOR6            = GetConfigMsg ( _T("//HMI/COLOR_SET/COLOR6") );
	m_strCOLOR_SET_COLOR7            = GetConfigMsg ( _T("//HMI/COLOR_SET/COLOR7") );
	m_strCOLOR_SET_COLOR8            = GetConfigMsg ( _T("//HMI/COLOR_SET/COLOR8") );
	m_strCOLOR_SET_COLOR9            = GetConfigMsg ( _T("//HMI/COLOR_SET/COLOR9") );
	m_strCOLOR_SET_COLOR10			 = GetConfigMsg ( _T("//HMI/COLOR_SET/COLOR10") );
	m_strCOLOR_SET_COLOR1_DESC       = GetConfigAttr( _T("//HMI/COLOR_SET/COLOR1"),  _T("DESC") );
	m_strCOLOR_SET_COLOR2_DESC       = GetConfigAttr( _T("//HMI/COLOR_SET/COLOR2"),  _T("DESC") );
	m_strCOLOR_SET_COLOR3_DESC       = GetConfigAttr( _T("//HMI/COLOR_SET/COLOR3"),  _T("DESC") );
	m_strCOLOR_SET_COLOR4_DESC       = GetConfigAttr( _T("//HMI/COLOR_SET/COLOR4"),  _T("DESC") );
	m_strCOLOR_SET_COLOR5_DESC       = GetConfigAttr( _T("//HMI/COLOR_SET/COLOR5"),  _T("DESC") );
	m_strCOLOR_SET_COLOR6_DESC       = GetConfigAttr( _T("//HMI/COLOR_SET/COLOR6"),  _T("DESC") );
	m_strCOLOR_SET_COLOR7_DESC       = GetConfigAttr( _T("//HMI/COLOR_SET/COLOR7"),  _T("DESC") );
	m_strCOLOR_SET_COLOR8_DESC       = GetConfigAttr( _T("//HMI/COLOR_SET/COLOR8"),  _T("DESC") );
	m_strCOLOR_SET_COLOR9_DESC       = GetConfigAttr( _T("//HMI/COLOR_SET/COLOR9"),  _T("DESC") );
	m_strCOLOR_SET_COLOR10_DESC		 = GetConfigAttr( _T("//HMI/COLOR_SET/COLOR10"), _T("DESC") );
	
	m_strWAVE_SET_WAVE1              = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE1") );
	m_strWAVE_SET_WAVE2              = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE2") );
	m_strWAVE_SET_WAVE3              = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE3") );
	m_strWAVE_SET_WAVE4              = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE4") );
	m_strWAVE_SET_WAVE5              = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE5") );
	m_strWAVE_SET_WAVE6              = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE6") );
	m_strWAVE_SET_WAVE7              = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE7") );
	m_strWAVE_SET_WAVE8              = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE8") );
	m_strWAVE_SET_WAVE9              = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE9") );
	m_strWAVE_SET_WAVE10             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE10") );
	m_strWAVE_SET_WAVE11             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE11") );
	m_strWAVE_SET_WAVE12             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE12") );
	m_strWAVE_SET_WAVE13             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE13") );
	m_strWAVE_SET_WAVE14             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE14") );
	m_strWAVE_SET_WAVE15             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE15") );
	m_strWAVE_SET_WAVE16             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE16") );
	m_strWAVE_SET_WAVE17             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE17") );
	m_strWAVE_SET_WAVE18             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE18") );
	m_strWAVE_SET_WAVE19             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE19") );
	m_strWAVE_SET_WAVE20             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE20") );
	m_strWAVE_SET_WAVE21             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE21") );
	m_strWAVE_SET_WAVE22             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE22") );
	m_strWAVE_SET_WAVE23             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE23") );
	m_strWAVE_SET_WAVE24             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE24") );
	m_strWAVE_SET_WAVE25             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE25") );
	m_strWAVE_SET_WAVE26             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE26") );
	m_strWAVE_SET_WAVE27             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE27") );
	m_strWAVE_SET_WAVE28             = GetConfigMsg( _T("//HMI/WAVE_SET/WAVE28") );

	m_strWAVE_DURATION	             = GetConfigMsg( _T("//HMI/WAVE_DURATION/DURATION_SET") );

	// 20140313 kylee : XML에서 알람셋팅 로드
	LoadConfigAlarmSetting();

	m_xmlAlarmSet.Close();
	return bRet;
}



BOOL CAlarmSetXML::OpenXML( CString strFilePath, CXml &xml )
{
	CString strErrMsg;
	BOOL bRet = xml.IsFileExist( strFilePath );
	
	if( !bRet )
	{
		strErrMsg.Format( 
			_N("XML File is Not Exist. Check File Path!!") 
			_T("[File Path: %s]"), strFilePath
		);
		
		MessageBox( NULL, strErrMsg, _T("ERROR"), MB_OK | MB_ICONERROR );
	}
	else
	{
		bRet = xml.Open( strFilePath );

		if( !bRet )
		{
			strErrMsg.Format( 
				_N("XML File Open Failed!!") 
				_T("[File Path: %s]"), strFilePath
			);
		
			MessageBox( NULL, strErrMsg, _T("ERROR"), MB_OK | MB_ICONERROR );
		}
	}

	return bRet;
}


BOOL CAlarmSetXML::OpenAlarmSet()
{
	BOOL bRet = TRUE;

	CString strAlarmSetPath;
	strAlarmSetPath.Format( _T("%s%s"), m_strEXEPath, _T("alarmSet.xml") );
	
	bRet = OpenXML( strAlarmSetPath, m_xmlAlarmSet );
	return bRet;
}


void CAlarmSetXML::CloseAlarmSet()
{
	m_xmlAlarmSet.Close();
}

void CAlarmSetXML::SaveFile()
{
	CString strAlarmSetPath;
	strAlarmSetPath.Format( _T("%s%s"), m_strEXEPath, _T("alarmSet.xml") );
	m_xmlAlarmSet.SaveWithFormatted( strAlarmSetPath );
}


void CAlarmSetXML::KillProcess( CString strProcessName )
{
	HANDLE snapshot_handle = ::CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	
	if( INVALID_HANDLE_VALUE != snapshot_handle )
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof( PROCESSENTRY32 );

		if( Process32First( snapshot_handle, &pe ) )
		{
			do
			{
   				if( !_tcscmp( pe.szExeFile, (LPCTSTR)strProcessName ) )
				{
					HANDLE process_handle = OpenProcess( PROCESS_TERMINATE, FALSE, pe.th32ProcessID );
					
					if( INVALID_HANDLE_VALUE != process_handle )
					{      
						TerminateProcess( process_handle, 0 );
						CloseHandle( process_handle );
					}
				}

			} while( Process32Next( snapshot_handle, &pe ) );
		}

		CloseHandle( snapshot_handle );
		snapshot_handle = INVALID_HANDLE_VALUE;
	} 

	return;
}


int CAlarmSetXML::SplitByPattern( TCHAR *strSource, CString strSplitBy, CStringArray &arraySource, CString &strOrg )
{
	int nRet = 1;

	CString strTemp, strTemp2;
	TCHAR *str = NULL;
	TCHAR *next_token = NULL;
	
	str = _tcstok_s( strSource, strSplitBy, &next_token );
	
	strTemp.Format( _T("%s"), str );
	arraySource.Add( strTemp );
	strTemp2 += strTemp + strSplitBy;

	while( str != NULL )
	{
		str = _tcstok_s( NULL, strSplitBy, &next_token );
		if( str == NULL ) break;

		strTemp.Format( _T("%s"), str );
		arraySource.Add( strTemp );
		strTemp2 += strTemp + strSplitBy;
		nRet++;
	}

	strTemp2.Delete( strTemp2.GetLength() -1 );
	strOrg = strTemp2;

	return nRet;
}

CString CAlarmSetXML::GetConfigMsg( CString strXPath )
{
	CString strMsg;
	CXmlNode node = m_xmlAlarmSet.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return strMsg;

	strMsg = node.GetValue();
	return strMsg;
}


CString CAlarmSetXML::GetConfigAttr( CString strXPath, CString strAttr )
{
	CString strMsg;
	CXmlNode node = m_xmlAlarmSet.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return strMsg;

	strMsg = node.GetAttribute( strAttr, _T("") );
	return strMsg;
}

CString CAlarmSetXML::GetConfigDecode( CString strXPath )
{
	CString strMsg;
	CXmlNode node = m_xmlAlarmSet.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return strMsg;

	strMsg = node.GetValue();
	
	BYTE pBuff[ MAX_PATH ] = { 0, };
	LONG lSize = 0;
	BOOL bRet  = m_xmlAlarmSet.Base64Decode( strMsg, pBuff, lSize );
	
	if( !bRet )
		return strMsg;
	
	CString strDecode( (LPCSTR)&pBuff, sizeof( pBuff ) );
	return strDecode;
}

void CAlarmSetXML::SetConfigMsg( CString strXPath, CString strValue )
{	
	CXmlNode node = m_xmlAlarmSet.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return;

	node.SetValue( strValue );
}


void CAlarmSetXML::SetConfigNode( CString strXPath, CString strValue )
{
	CStringArray arrNodes;
	CString strNodeName;
	
	CXmlNode  Node = m_xmlAlarmSet.GetRoot();	
	
	int i;
	int nRet = SplitByPattern( (TCHAR *)(LPCTSTR)strXPath, _T("/"), arrNodes, strXPath );
	
	for( i = 0; i < nRet; i++ )
	{
		strNodeName = arrNodes.GetAt( i );
		
		CXmlNode NewNode = m_xmlAlarmSet.CreateNode( strNodeName );
		Node.AttachChild( NewNode );
		Node = NewNode;
	}

	Node.SetValue( strValue );	
}


void CAlarmSetXML::SetConfigEncode( CString strXPath, CString strValue )
{
	CXmlNode node = m_xmlAlarmSet.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return;

	CString strEncode;
	BYTE pBuff[ MAX_PATH ] = { 0, };
	WideCharToMultiByte( CP_ACP, 0, strValue, -1, (LPSTR)pBuff, MAX_PATH, NULL, NULL );
		
	strEncode = m_xmlAlarmSet.Base64Encode( pBuff, strValue.GetLength() );
	node.SetValue( strEncode );	
}

void CAlarmSetXML::SetConfigWaveDuration(int nDuration)
{
	if( !OpenAlarmSet() )
		return;

	CString strXPath;	
	strXPath .Format( _T("//HMI/WAVE_DURATION/DURATION_SET") );
	m_strWAVE_DURATION.Format( _T("%d"), nDuration );

	SetConfigMsg( strXPath, m_strWAVE_DURATION );

	SaveFile();
	CloseAlarmSet();
}

void CAlarmSetXML::SetConfigAlarmSetting(CString strRTUType, int nRTUMapID, CString strPointInfo, int nPointPosition, CStringArray &strInsert)
{
	if( !OpenAlarmSet() )
		return;	
	//신규 알람입력 XML 메모리에 입력 추가

	CXmlNode Node, NodeChk;
	CString strXPath, strXPathDetail;	
	strXPath.Format( _T("//HMI/ALARM") );	
	NodeChk = m_xmlAlarmSet.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )
	{
		Node = m_xmlAlarmSet.GetRoot()->NewChild( _T("ALARM") );
	}
	else
		Node = NodeChk;


	strXPath.Format( _T("//HMI/ALARM/ALARM_SET[@RTU_TYPE='%s'][@RTU_MAPID='%d'][@POINT_INFO='%s'][@POINT_POSITION='%d']"), strRTUType, nRTUMapID, strPointInfo, nPointPosition );	
	NodeChk = m_xmlAlarmSet.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )
	{
		Node = Node.NewChild( _T("ALARM_SET") );
		Node.SetAttribute( _T("RTU_TYPE"), strRTUType );
		Node.SetAttribute( _T("RTU_MAPID"), nRTUMapID );
		Node.SetAttribute( _T("POINT_INFO"),   strPointInfo );
		Node.SetAttribute( _T("POINT_POSITION"),   nPointPosition );
	}
	else
		Node = NodeChk;


	strXPathDetail.Format( _T("%s/TEXT_COLOR"), strXPath );
	NodeChk = m_xmlAlarmSet.SelectSingleNode( strXPathDetail );

	if( NodeChk.IsNull() )		Node.NewChild( _T("TEXT_COLOR") )->SetValue( strInsert[0] );
	else						g_ast.SetConfigMsg( strXPathDetail,  strInsert[0] );


	strXPathDetail.Format( _T("%s/BG_COLOR"), strXPath );
	NodeChk = m_xmlAlarmSet.SelectSingleNode( strXPathDetail );

	if( NodeChk.IsNull() )		Node.NewChild( _T("BG_COLOR") )->SetValue( strInsert[1] );
	else						g_ast.SetConfigMsg( strXPathDetail,  strInsert[1] );


	strXPathDetail.Format( _T("%s/WAVE_SET"), strXPath );
	NodeChk = m_xmlAlarmSet.SelectSingleNode( strXPathDetail );

	if( NodeChk.IsNull() )		Node.NewChild( _T("WAVE_SET") )->SetValue( strInsert[2] );
	else						g_ast.SetConfigMsg( strXPathDetail,  strInsert[2] );


	strXPathDetail.Format( _T("%s/IMPORTANT"), strXPath );
	NodeChk = m_xmlAlarmSet.SelectSingleNode( strXPathDetail );

	if( NodeChk.IsNull() )		Node.NewChild( _T("IMPORTANT") )->SetValue( strInsert[3] );
	else						g_ast.SetConfigMsg( strXPathDetail,  strInsert[3] );


	SaveFile();
	CloseAlarmSet();
}


// 종합정보 화면의 Alarm Setting내용 저장

BOOL CAlarmSetXML::GetConfigAlarmSetting(CString strRTUType, int nRTUMapID, CString strPointInfo, int nPointPosition, CStringArray &strReturn)
{
	if( !OpenAlarmSet() )
		return FALSE;	

	CString strXPath, strXPathDetail, strVal;	

	strXPath.Format( _T("//HMI/ALARM/ALARM_SET[@RTU_TYPE='%s'][@RTU_MAPID='%d'][@POINT_INFO='%s'][@POINT_POSITION='%d']"), strRTUType, nRTUMapID, strPointInfo, nPointPosition );	
	strXPathDetail.Format(_T("%s/TEXT_COLOR"), strXPath);
	strVal = GetConfigMsg( strXPathDetail );
	if( strVal == _T(""))
		return FALSE;
	strReturn.Add(strVal);

	strXPathDetail.Format(_T("%s/BG_COLOR"), strXPath);
	strVal = GetConfigMsg( strXPathDetail );
	if( strVal == _T(""))
		return FALSE;
	strReturn.Add(strVal);

	strXPathDetail.Format(_T("%s/WAVE_SET"), strXPath);
	strVal = GetConfigMsg( strXPathDetail );
	if( strVal == _T(""))
		return FALSE;
	strReturn.Add(strVal);

	strXPathDetail.Format(_T("%s/IMPORTANT"), strXPath);
	strVal = GetConfigMsg( strXPathDetail );
	if( strVal == _T(""))
		return FALSE;
	strReturn.Add(strVal);

	return TRUE;
}


BOOL CAlarmSetXML::LoadConfigAlarmSetting()
{
	m_pTotalInfo_AlarmSetting = new CObList;

	CXmlNode Node, NodeChk;
	CString strXPath, strXPathDetail;	
	strXPath.Format( _T("//HMI/ALARM") );	
	NodeChk = m_xmlAlarmSet.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )
	{
		return FALSE;
	}
	else
		Node = NodeChk;

	CXmlNodesPtr NodePtr = Node.GetChildren();

	CString strRTUType, strPointInfo;
	int nRTUMapID, nPointPosition;
	CStringArray strReturn;

	for(LONG litem=0; litem<NodePtr->GetCount(); litem++)
	{
		CXmlNodePtr NodePtrChild = NodePtr->GetItem(litem);
		strRTUType = NodePtrChild->GetAttribute(_T("RTU_TYPE"), _T(""));
		nRTUMapID = NodePtrChild->GetAttribute(_T("RTU_MAPID"), -1);
		strPointInfo = NodePtrChild->GetAttribute(_T("POINT_INFO"), _T(""));
		nPointPosition = NodePtrChild->GetAttribute(_T("POINT_POSITION"), -1);

		if(GetConfigAlarmSetting(strRTUType, nRTUMapID, strPointInfo, nPointPosition, strReturn))
		{
			ST_POINT_LIST *stPointList = new ST_POINT_LIST;

			stPointList->nTextColor = _ttoi(strReturn[0]);
			stPointList->nBGColor = _ttoi(strReturn[1]);
			stPointList->nWaveSet = _ttoi(strReturn[2]);
			stPointList->uImportant = _ttoi(strReturn[3]);
			stPointList->strPointInfo = strPointInfo;
			stPointList->nPosition = nPointPosition;
			strReturn.RemoveAll();

			ST_SWITCH_LIST *stSwitchList = 0;//new ST_SWITCH_LIST;

			if( FindItem( strRTUType, nRTUMapID, &stSwitchList ) == 1 )
			{
				stSwitchList->pPointList->AddTail((CObject*)stPointList);
			}
			else
			{
				stSwitchList = new ST_SWITCH_LIST;
				stSwitchList->pPointList = new CObList;

				stSwitchList->nRTUMapID = nRTUMapID;
				stSwitchList->strRTUType = strRTUType;
				stSwitchList->pPointList->AddTail((CObject*)stPointList);
				m_pTotalInfo_AlarmSetting->AddTail((CObject*)stSwitchList);
			}
		}
	}

	return TRUE;
}


// XML의 정보중 RTUType (과 PointInfo)이 List에 등록되어 있는지 검사, 등록되어 있을때 해당 List 반환
int CAlarmSetXML::FindItem( CString strRTUType, int nRTUMapID, ST_SWITCH_LIST **stSwitchList, CString strPointInfo, int nPointPosition, ST_POINT_LIST **stPointList )
{
	int nRet = -1;
	POSITION posAL, posPL;

	for(int nALCnt=0; nALCnt<m_pTotalInfo_AlarmSetting->GetCount(); nALCnt++)
	{
		posAL = m_pTotalInfo_AlarmSetting->FindIndex(nALCnt);
		*stSwitchList = (ST_SWITCH_LIST*)m_pTotalInfo_AlarmSetting->GetAt(posAL);
		if((*stSwitchList)->strRTUType == strRTUType && (*stSwitchList)->nRTUMapID == nRTUMapID)
		{
			nRet = 1;

			if(strPointInfo == _T(""))	break;

			for(int nPLCnt=0; nPLCnt<(*stSwitchList)->pPointList->GetCount(); nPLCnt++)
			{
				posPL = (*stSwitchList)->pPointList->FindIndex(nPLCnt);
				*stPointList = (ST_POINT_LIST*)(*stSwitchList)->pPointList->GetAt(posPL);

				if((*stPointList)->strPointInfo == strPointInfo && (*stPointList)->nPosition == nPointPosition)
				{
					nRet = 2;
					break;
				}
			}
			if(nRet > 0)
				break;
		}
	}

	return nRet;
}


// XML의 정보중 RTUType (과 PointInfo)이 List에 등록되어 있는지 검사, 등록되어 있을때 해당 List 반환
void CAlarmSetXML::DeleteAlarmSetting()
{
	if(m_pTotalInfo_AlarmSetting == NULL)	return;

	for(int nALCnt=0; nALCnt<m_pTotalInfo_AlarmSetting->GetCount(); nALCnt++)
	{
		POSITION posAL = m_pTotalInfo_AlarmSetting->FindIndex(nALCnt);
		ST_SWITCH_LIST *stSwitchList = (ST_SWITCH_LIST*)m_pTotalInfo_AlarmSetting->GetAt(posAL);
		
		if(stSwitchList)
		{
			for(int nPLCnt=0; nPLCnt < stSwitchList->pPointList->GetCount(); nPLCnt++)
			{
				POSITION posPL = stSwitchList->pPointList->FindIndex(nPLCnt);
				ST_POINT_LIST *stPL = (ST_POINT_LIST*)stSwitchList->pPointList->GetAt(posPL);
				if(stPL)
					delete stPL;
			}
			stSwitchList->pPointList->RemoveAll();
			delete stSwitchList->pPointList;
			delete stSwitchList;
		}
	}

	m_pTotalInfo_AlarmSetting->RemoveAll();
	if(m_pTotalInfo_AlarmSetting)
		delete m_pTotalInfo_AlarmSetting;
	m_pTotalInfo_AlarmSetting = NULL;
}

void CAlarmSetXML::SetAlarmSetList(CObList *alarmList)
{
	DeleteAlarmSetting();
		
	CObList *pAlarmSettingTmp = alarmList;
	if(pAlarmSettingTmp == NULL)	return;

	if(m_pTotalInfo_AlarmSetting == NULL)
		m_pTotalInfo_AlarmSetting = new CObList;

	for(int nALCnt=0; nALCnt<pAlarmSettingTmp->GetCount(); nALCnt++)
	{
		POSITION posAL = pAlarmSettingTmp->FindIndex(nALCnt);
		ST_SWITCH_LIST *stSwitchList = (ST_SWITCH_LIST*)pAlarmSettingTmp->GetAt(posAL);

		ST_SWITCH_LIST *stSwitchItem = new ST_SWITCH_LIST;
		stSwitchItem->pPointList = new CObList;

		stSwitchItem->nID = stSwitchList->nID;
		stSwitchItem->nRTUMapID = stSwitchList->nRTUMapID;
		stSwitchItem->strRTUType = stSwitchList->strRTUType;

		for(int nPLCnt=0; nPLCnt<stSwitchList->pPointList->GetCount(); nPLCnt++)
		{
			POSITION posPL = stSwitchList->pPointList->FindIndex(nPLCnt);
			ST_POINT_LIST *stPointList = (ST_POINT_LIST*)stSwitchList->pPointList->GetAt(posPL);

			ST_POINT_LIST *stPointItem= new ST_POINT_LIST;
			//memcpy(stPointItem, stPointList, sizeof(ST_POINT_LIST));
			stPointItem->nBGColor		= stPointList->nBGColor	;	 
			stPointItem->nPosition		= stPointList->nPosition;		
			stPointItem->nSeq			= stPointList->nSeq		;	
			stPointItem->nTextColor		= stPointList->nTextColor;		
			stPointItem->nWaveSet		= stPointList->nWaveSet		;
			stPointItem->strPointInfo.Format(stPointList->strPointInfo)	;
			stPointItem->uImportant		= stPointList->uImportant	;

			stSwitchItem->pPointList->AddTail((CObject*)stPointItem);
		}

		m_pTotalInfo_AlarmSetting->AddTail((CObject*)stSwitchItem);
	}
}