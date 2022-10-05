#include "stdafx.h"
#include "ConfigXML.h"
#include <tlhelp32.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define DEF_START_X         _T("0")
#define DEF_START_Y         _T("0")
#define DEF_END_X           _T("1920")
#define DEF_END_Y           _T("1080")
#define DEF_ZOOM_VAL        _T("4")
#define DEF_DIAGRAM_X       _T("")
#define DEF_DIAGRAM_Y       _T("")
#define DEF_ZOOM_LEVEL      _T("4")
#define DEF_STEP_LEVEL      _T("2")
#define DEF_VIEW_TYPE       _T("53")
#define DEF_NAMEORINDEX     _T("7")
#define DEF_SELECT_PHASE    _T("1")
#define DEF_SELECT_VOLT     _T("1")
#define DEF_FI_MOVE         _T("0")
#define DEF_DL_LINK         _T("0")
#define DEF_LINE_VIEW       _T("1")
#define DEF_LINE_OPTION     _T("0")
#define DEF_LINK_COLOR      _T("16711935")
#define DEF_LOOP_COLOR      _T("8388736")
#define DEF_COLOR1          _T("128")
#define DEF_COLOR2          _T("32768")
#define DEF_COLOR3          _T("32896")
#define DEF_COLOR4          _T("8388736")
#define DEF_COLOR5          _T("8421376")
#define DEF_COLOR6          _T("12639424")
#define DEF_COLOR7          _T("65280")
#define DEF_COLOR8          _T("65535")
#define DEF_COLOR9          _T("16711935")
#define DEF_COLOR10         _T("16776960")
#define DEF_DEAD_COLOR      _T("192")
#define DEF_ALIVE_COLOR     _T("10377728")
#define DEF_ACMCOLUMN       _T("0")

CConfigXML::CConfigXML()
{
	//m_pTotalInfo_AlarmSetting = NULL;
}

CConfigXML::~CConfigXML()
{	
	//DeleteAlarmSetting();

	m_mapXmlList.RemoveAll();
}


BOOL CConfigXML::LangInfo()
{
	BOOL bRet = TRUE;
	CString	strLangPath = GetLangPath();
	
	bRet = OpenXML( strLangPath, m_xmlLang );
	return bRet;
}


BOOL CConfigXML::XmlConfigInfo(int nType)
{
	
	CString strKey;
	CString strType;
	UINT nID ;

	CString strXPath,strMsg;	

	CXmlNode node;

	switch(nType)
	{
	case MAININFOXML:
		{
			//MAININFO-> CAP 정보
			for(nID =1; nID <= 3000; nID++)
			{
				strXPath.Format( _T("//PROGRAM/MAININFO/CAP[@ID='%04d']"),	 nID );

				node = m_xmlLang.SelectSingleNode( strXPath );


				if( node.IsNull() )
					continue;

				strMsg = node.GetValue();
				strMsg.Replace( _T("\\n"), _T("\n") );

				strKey.Format(_T("MAININFO_CAP_%04d"),nID);
				m_mapXmlList.SetAt(strKey,strMsg); 
			}


			//MAININFO-> MSG 정보
			for(nID =1; nID <= 3000; nID++)
			{
				strXPath.Format( _T("//PROGRAM/MAININFO/MSG[@ID='%04d']"),	 nID );

				node = m_xmlLang.SelectSingleNode( strXPath );


				if( node.IsNull() )
					continue;

				strMsg = node.GetValue();
				strMsg.Replace( _T("\\n"), _T("\n") );

				strKey.Format(_T("MAININFO_MSG_%04d"),nID);
				m_mapXmlList.SetAt(strKey,strMsg); 
			}
		}
		break;
	case TOTALINFOXML:
		{
			//TOTALINFO-> CAP 정보
			for(nID =1; nID <= 3000; nID++)
			{
				strXPath.Format( _T("//PROGRAM/TOTALINFO/CAP[@ID='%04d']"),	 nID );

				node = m_xmlLang.SelectSingleNode( strXPath );


				if( node.IsNull() )
					continue;

				strMsg = node.GetValue();
				strMsg.Replace( _T("\\n"), _T("\n") );

				strKey.Format(_T("TOTALINFO_CAP_%04d"),nID);
				m_mapXmlList.SetAt(strKey,strMsg); 
			}


			//TOTALINFO-> MSG 정보
			for(nID =1; nID <= 3000; nID++)
			{
				strXPath.Format( _T("//PROGRAM/TOTALINFO/MSG[@ID='%04d']"),	 nID );

				node = m_xmlLang.SelectSingleNode( strXPath );


				if( node.IsNull() )
					continue;

				strMsg = node.GetValue();
				strMsg.Replace( _T("\\n"), _T("\n") );

				strKey.Format(_T("TOTALINFO_MSG_%04d"),nID);
				m_mapXmlList.SetAt(strKey,strMsg); 
			}
		}
		break;
	case LINEINFOXML:
		{
			//LINEINFO-> CAP 정보
			for(nID =1; nID <= 3000; nID++)
			{
				strXPath.Format( _T("//PROGRAM/LINEINFO/CAP[@ID='%04d']"),	 nID );

				node = m_xmlLang.SelectSingleNode( strXPath );


				if( node.IsNull() )
					continue;

				strMsg = node.GetValue();
				strMsg.Replace( _T("\\n"), _T("\n") );

				strKey.Format(_T("LINEINFO_CAP_%04d"),nID);
				m_mapXmlList.SetAt(strKey,strMsg); 
			}


			//LINEINFO-> MSG 정보
			for(nID =1; nID <= 3000; nID++)
			{
				strXPath.Format( _T("//PROGRAM/LINEINFO/MSG[@ID='%04d']"),	 nID );

				node = m_xmlLang.SelectSingleNode( strXPath );


				if( node.IsNull() )
					continue;

				strMsg = node.GetValue();
				strMsg.Replace( _T("\\n"), _T("\n") );

				strKey.Format(_T("LINEINFO_MSG_%04d"),nID);
				m_mapXmlList.SetAt(strKey,strMsg); 
			}
		
		}
		break;
	case CONTROLINFOXML:
		{
			//CONTROLINFO-> CAP 정보
			for(nID =1; nID <= 3000; nID++)
			{
				strXPath.Format( _T("//PROGRAM/CONTROLINFO/CAP[@ID='%04d']"),	 nID );

				node = m_xmlLang.SelectSingleNode( strXPath );


				if( node.IsNull() )
					break;

				strMsg = node.GetValue();
				strMsg.Replace( _T("\\n"), _T("\n") );

				strKey.Format(_T("CONTROLINFO_CAP_%04d"),nID);
				m_mapXmlList.SetAt(strKey,strMsg); 
			}
			//CONTROLINFO-> MSG 정보
			for(nID =1; nID <=3000; nID++)
			{
				strXPath.Format( _T("//PROGRAM/CONTROLINFO/MSG[@ID='%04d']"),	 nID );

				node = m_xmlLang.SelectSingleNode( strXPath );


				if( node.IsNull() )
					break;

				strMsg = node.GetValue();
				strMsg.Replace( _T("\\n"), _T("\n") );

				strKey.Format(_T("CONTROLINFO_MSG_%04d"),nID);
				m_mapXmlList.SetAt(strKey,strMsg); 
			}

		}
		break;
	}

	//GLOBAL-> CAP 정보
	for(nID =1; nID <= 3000; nID++)
	{
		strXPath.Format( _T("//PROGRAM/GLOBAL/CAP[@ID='%04d']"),	 nID );

		node = m_xmlLang.SelectSingleNode( strXPath );


		if( node.IsNull() )
			break;

		strMsg = node.GetValue();
		strMsg.Replace( _T("\\n"), _T("\n") );

		strKey.Format(_T("GLOBAL_CAP_%04d"),nID);
		m_mapXmlList.SetAt(strKey,strMsg); 
	}


	//GLOBAL-> MSG 정보
	for(nID =1; nID <=3000; nID++)
	{
		strXPath.Format( _T("//PROGRAM/GLOBAL/MSG[@ID='%04d']"),	 nID );

		node = m_xmlLang.SelectSingleNode( strXPath );


		if( node.IsNull() )
			break;

		strMsg = node.GetValue();
		strMsg.Replace( _T("\\n"), _T("\n") );

		strKey.Format(_T("GLOBAL_MSG_%04d"),nID);
		m_mapXmlList.SetAt(strKey,strMsg); 
	}


	return true;
}
BOOL CConfigXML::IsOperator( CString strOP_NAME, CString strOP_NUM )
{
	CString strAttrMsg;
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/START_AXIS_X"), strOP_NAME, strOP_NUM );
	if(GetConfigMsg( strAttrMsg ) == _T(""))
		return false;

	return true;
}
void CConfigXML::UserInfo( CString strOP_NAME, CString strOP_NUM )
{
	BOOL bRet = TRUE;
	CString strConfigPath, strErrMsg, strAttrMsg;
	
	TCHAR tzFileName[ MAX_PATH ], tzDrive[ _MAX_DRIVE ], tzPath[ _MAX_DIR ], tzName[ _MAX_FNAME ], tzExt[ _MAX_EXT ];
	TCHAR tzTemp[ MAX_PATH ] = { 0, };

	GetModuleFileName( NULL, tzFileName, sizeof(tzFileName) );
	_tsplitpath_s( tzFileName, tzDrive, _MAX_DRIVE, tzPath, _MAX_DIR, tzName, _MAX_FNAME, tzExt, _MAX_EXT );

	m_strEXEPath.Format( _T("%s%s"), tzDrive, tzPath );	
	strConfigPath.Format( _T("%s%s"), m_strEXEPath, _T("config.xml") );
	
	bRet = OpenXML( strConfigPath, m_xmlConfig );
	if( !bRet )		return;

	if( !IsOperator( strOP_NAME, strOP_NUM ) ) 
	{
		SetDefaultOption( strOP_NAME, strOP_NUM );
	}

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/START_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_START_AXIS_X		 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/START_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_START_AXIS_Y		 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/END_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_END_AXIS_X			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/END_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_END_AXIS_Y			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ZOOM_VAL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_ZOOM_VAL			 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DIAGRAM_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_DIAGRAM_X			 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DIAGRAM_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_DIAGRAM_Y			 = GetConfigMsg( strAttrMsg );
	
	//계통도 뷰어 옵션 추가
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ZOOM_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_ZOOM_LEVEL		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/STEP_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_STEP_LEVEL		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/VIEW_TYPE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_TYPE					 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/NAME_OR_INDEX"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_NAMEORINDEX			 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/SELECT_PHASE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_SELECT_PHASE			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/SELECT_VOLT"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_SELECT_VOLT			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/FI_MOVE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_FI_MOVE				 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DL_LINK"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_DL_LINK				 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINE_VIEW"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_LINE_VIEW			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINE_OPTION"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_LINE_OPTION		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINK_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_LINK_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LOOP_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_LOOP_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR1				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR2				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR3				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR4				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR5				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR6				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR7				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR8				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR9"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR9				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR10"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR10			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DEAD_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_DEAD_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ALIVE_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_ALIVE_COLOR		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ACMCOLUMN"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_ACMCOLUMN			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/START_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_START_AXIS_X		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/START_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_START_AXIS_Y		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/END_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM);
	m_strCLIENT2_END_AXIS_X			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/END_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_END_AXIS_Y			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/CEQID"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_CEQID				 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/PSR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_PSR				 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[0]				= GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[1]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[2]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[3]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[4]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[5]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[6]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[7]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[0]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[1]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[2]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[3]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[4]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[5]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[6]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[7]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/START_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_START_AXIS_X		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/START_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_START_AXIS_Y		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/END_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_END_AXIS_X			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/END_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_END_AXIS_Y			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ZOOM_VAL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_ZOOM_VAL			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DIAGRAM_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_DIAGRAM_X			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DIAGRAM_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_DIAGRAM_Y			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/FOCUS_DL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_FOCUS_DL			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/OPEN_DL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_OPEN_DL			 = GetConfigMsg( strAttrMsg );

	//단선도 뷰어 옵션 추가
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ZOOM_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_ZOOM_LEVEL		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/STEP_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_STEP_LEVEL		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/VIEW_TYPE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_TYPE					 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/NAME_OR_INDEX"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_NAMEORINDEX			 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/SELECT_PHASE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_SELECT_PHASE			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/SELECT_VOLT"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_SELECT_VOLT			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/FI_MOVE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_FI_MOVE				 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DL_LINK"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_DL_LINK				 = GetConfigMsg( strAttrMsg );


	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINE_VIEW"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_LINE_VIEW			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINE_OPTION"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_LINE_OPTION		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINK_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_LINK_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LOOP_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_LOOP_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR1				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR2				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR3				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR4				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR5				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR6				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR7				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR8				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR9"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR9				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR10"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR10			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DEAD_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_DEAD_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ALIVE_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_ALIVE_COLOR		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ACMCOLUMN"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_ACMCOLUMN			= GetConfigMsg( strAttrMsg );

	m_strCONTROL_POSSIBLE_DPGRP	     = GetConfigMsg( _T("//HMI/CONTROL/POSSIBLE_DPGRP") );

	// 20140313 kylee : XML에서 알람셋팅 로드
	//LoadConfigAlarmSetting();

	// 20140410 kylee : XML에서 알람 필터링 셋팅 로드
	//LoadConfigAlarmEventFiltering();

	// 20140320 kylee : XML에서 마지막으로 선택된 Tree Item 로드
	m_strTOTALINFO_SYSTEMSTATE_LASTSELECTION		 = GetConfigMsg( _T("//HMI/LAST_SELECTION/SYSTEM_STATE/CURRENT_SELECTION") );
	//m_xmlConfig.Close();	
}
void CConfigXML::SetDefaultOption( CString strOP_NAME, CString strOP_NUM )
{
	CString  strAttrMsg;

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/START_AXIS_X"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_START_X );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/START_AXIS_Y"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_START_Y );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/END_AXIS_X"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_END_X );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/END_AXIS_Y"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_END_Y );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ZOOM_VAL"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_ZOOM_VAL );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DIAGRAM_X"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_DIAGRAM_X );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DIAGRAM_Y"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_DIAGRAM_Y );
	
	//계통도 뷰어 옵션 추가
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ZOOM_LEVEL"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_ZOOM_LEVEL );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/STEP_LEVEL"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_STEP_LEVEL );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/VIEW_TYPE"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_VIEW_TYPE );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/NAME_OR_INDEX"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_NAMEORINDEX );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/SELECT_PHASE"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_SELECT_PHASE );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/SELECT_VOLT"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_SELECT_VOLT );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/FI_MOVE"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_FI_MOVE );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DL_LINK"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_DL_LINK );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINE_VIEW"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_LINE_VIEW );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINE_OPTION"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_LINE_OPTION );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINK_COLOR"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_LINK_COLOR );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LOOP_COLOR"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_LOOP_COLOR );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR1"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR1 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR2"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR2 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR3"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR3 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR4"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR4 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR5"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR5 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR6"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR6 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR7"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR7 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR8"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR8 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR9"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR9 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR10"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR10 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DEAD_COLOR"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_DEAD_COLOR );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ALIVE_COLOR"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_ALIVE_COLOR );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ACMCOLUMN"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_ACMCOLUMN );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/START_AXIS_X"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_START_X );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/START_AXIS_Y"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_START_Y );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/END_AXIS_X"), strOP_NAME, strOP_NUM);
	SetConfigMsg( strAttrMsg,  DEF_END_X );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/END_AXIS_Y"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_END_X );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/CEQID"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/PSR"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND1"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND2"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg, _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND3"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg, _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND4"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND5"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND6"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND7"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND8"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR1"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR2"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR3"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR4"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR5"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR6"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR7"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR8"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/START_AXIS_X"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_START_X );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/START_AXIS_Y"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_START_Y );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/END_AXIS_X"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_START_X );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/END_AXIS_Y"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_END_X );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ZOOM_VAL"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_END_X );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DIAGRAM_X"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DIAGRAM_Y"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,   _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/FOCUS_DL"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,   _T("") );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/OPEN_DL"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,   _T("") );

	//단선도 뷰어 옵션 추가
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ZOOM_LEVEL"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_ZOOM_LEVEL );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/STEP_LEVEL"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_STEP_LEVEL );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/VIEW_TYPE"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_VIEW_TYPE );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/NAME_OR_INDEX"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_NAMEORINDEX );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/SELECT_PHASE"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_SELECT_PHASE );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/SELECT_VOLT"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_SELECT_VOLT );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/FI_MOVE"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_FI_MOVE);

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DL_LINK"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_DL_LINK );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINE_VIEW"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_LINE_VIEW );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINE_OPTION"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_LINE_OPTION );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINK_COLOR"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_LINK_COLOR );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LOOP_COLOR"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_LOOP_COLOR );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR1"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR1 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR2"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR2 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR3"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR3 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR4"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR4 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR5"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR5 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR6"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR6 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR7"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR7 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR8"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR8 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR9"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR9 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR10"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_COLOR10 );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DEAD_COLOR"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_DEAD_COLOR );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ALIVE_COLOR"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_ALIVE_COLOR );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ACMCOLUMN"), strOP_NAME, strOP_NUM );
	SetConfigMsg( strAttrMsg,  DEF_ACMCOLUMN );

}
BOOL CConfigXML::ConfigInfo()
{
	BOOL bRet = TRUE;
	CString strConfigPath, strErrMsg, strAttrMsg;
	
	TCHAR tzFileName[ MAX_PATH ], tzDrive[ _MAX_DRIVE ], tzPath[ _MAX_DIR ], tzName[ _MAX_FNAME ], tzExt[ _MAX_EXT ];
	TCHAR tzTemp[ MAX_PATH ] = { 0, };

	GetModuleFileName( NULL, tzFileName, sizeof(tzFileName) );
	_tsplitpath_s( tzFileName, tzDrive, _MAX_DRIVE, tzPath, _MAX_DIR, tzName, _MAX_FNAME, tzExt, _MAX_EXT );

	m_strEXEPath.Format( _T("%s%s"), tzDrive, tzPath );	
	strConfigPath.Format( _T("%s%s"), m_strEXEPath, _T("config.xml") );
	
	bRet = OpenXML( strConfigPath, m_xmlConfig );
	if( !bRet )		return bRet;

	m_strENGINE_PROJECT_TITLE		 = GetConfigMsg( _T("//HMI/ENGINE/PROJECT_TITLE") );
	m_strENGINE_LOG_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/LOG_PATH") );
	m_strENGINE_ACM_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/ACM_PATH") );
	m_strENGINE_WAVE_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/WAVE_PATH") );
	m_strENGINE_DRAW_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/DRAW_PATH") );
	m_strENGINE_EXCEL_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/EXCEL_PATH") );
	m_strENGINE_PNG_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/PNG_PATH") );
	m_strENGINE_SKIN_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/SKIN_PATH") );
	m_strENGINE_XML_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/XML_PATH") );
	m_strENGINE_SYM_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/SYM_PATH") );
	m_strENGINE_DAT_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/DAT_PATH") );
	m_strENGINE_CAP_PATH			 = GetConfigMsg( _T("//HMI/ENGINE/CAP_PATH") );
	m_strENGINE_DBLOAD_TYPE			 = GetConfigMsg(  _T("//HMI/ENGINE/DB_LOAD_TYPE") );

	m_strLOG_LOG_LEVEL				 = GetConfigMsg( _T("//HMI/LOG/LOG_LEVEL"));
	m_strACM_USE_ACM				 = GetConfigMsg( _T("//HMI/ACM/USE_ACM") );

	m_strMIDDLE_WARE_SCAN_INTERVAL   = GetConfigMsg( _T("//HMI/MIDDLE_WARE/SCAN_INTERVAL") );
	m_strMIDDLE_WARE_ASYN_INTERVAL   = GetConfigMsg( _T("//HMI/MIDDLE_WARE/ASYN_INTERVAL") );
	m_strMIDDLE_WARE_EVENT_INTERVAL  = GetConfigMsg( _T("//HMI/MIDDLE_WARE/EVENT_INTERVAL") );
	m_strMIDDLE_WARE_SYSTEM_INTERVAL = GetConfigMsg( _T("//HMI/MIDDLE_WARE/SYSTEM_INTERVAL") );
	m_strMIDDLE_WARE_CONTROL_INTERVAL= GetConfigMsg( _T("//HMI/MIDDLE_WARE/CONTROL_INTERVAL") );
	m_strMIDDLE_WARE_COMPUTER_NAME   = GetConfigMsg( _T("//HMI/MIDDLE_WARE/COMPUTER_NAME") );
	m_strMIDDLE_WARE_CLIENT_NAME1    = GetConfigMsg( _T("//HMI/MIDDLE_WARE/CLIENT_NAME1") );
	m_strMIDDLE_WARE_CLIENT_NAME2    = GetConfigMsg( _T("//HMI/MIDDLE_WARE/CLIENT_NAME2") );
	m_strMIDDLE_WARE_CLIENT_NAME3    = GetConfigMsg( _T("//HMI/MIDDLE_WARE/CLIENT_NAME3") );
	m_strMIDDLE_WARE_CLIENT_NAME4    = GetConfigMsg( _T("//HMI/MIDDLE_WARE/CLIENT_NAME4") );
	m_strMIDDLE_WARE_CLIENT_NAME5    = GetConfigMsg( _T("//HMI/MIDDLE_WARE/CLIENT_NAME5") );
	
	m_strDATABASE_DB_INTERVAL		 = GetConfigMsg( _T("//HMI/DATABASE/DB_INTERVAL") );
	m_strDATABASE_DB_SERVER1		 = GetConfigMsg( _T("//HMI/DATABASE/DB_SERVER1") );
	m_strDATABASE_DB_SERVER2		 = GetConfigMsg( _T("//HMI/DATABASE/DB_SERVER2") );
	m_strDATABASE_DB_PORT			 = GetConfigMsg( _T("//HMI/DATABASE/DB_PORT") );
	m_strDATABASE_DB_USER			 = GetConfigMsg( _T("//HMI/DATABASE/DB_USER") );
	m_strDATABASE_DB_PASSWORD		 = GetConfigDecode( _T("//HMI/DATABASE/DB_PASSWORD") );
	m_strDATABASE_DB_COMMON			 = GetConfigMsg( _T("//HMI/DATABASE/DB_COMMON") );
	m_strDATABASE_DB_OPER			 = GetConfigMsg( _T("//HMI/DATABASE/DB_OPER") );
	m_strDATABASE_DB_HISTORY		 = GetConfigMsg( _T("//HMI/DATABASE/DB_HISTORY") );
	
	m_strLANGUAGE_LANG_SET			 = GetConfigMsg( _T("//HMI/LANGUAGE/LANG_SET") );

	//마지막 로그인
	m_strOPERATOR_OP_ID				 = GetConfigMsg( _T("//HMI/OPERATOR/OP_ID") );
	m_strOPERATOR_OP_NUM			 = GetConfigMsg( _T("//HMI/OPERATOR/OP_NUM") );
	m_strOPERATOR_OP_NAME			 = GetConfigMsg( _T("//HMI/OPERATOR/OP_NAME") );
	m_strOPERATOR_OP_LOGIN			 = GetConfigMsg( _T("//HMI/OPERATOR/OP_LOGIN") );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/START_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_START_AXIS_X		 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/START_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_START_AXIS_Y		 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/END_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_END_AXIS_X			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/END_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_END_AXIS_Y			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ZOOM_VAL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_ZOOM_VAL			 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DIAGRAM_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_DIAGRAM_X			 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DIAGRAM_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_DIAGRAM_Y			 = GetConfigMsg( strAttrMsg );
	
	//계통도 뷰어 옵션 추가
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ZOOM_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_ZOOM_LEVEL		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/STEP_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_STEP_LEVEL		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/VIEW_TYPE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_TYPE					 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/NAME_OR_INDEX"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_NAMEORINDEX			 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/SELECT_PHASE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_SELECT_PHASE			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/SELECT_VOLT"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_SELECT_VOLT			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/FI_MOVE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_FI_MOVE				 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DL_LINK"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_DL_LINK				 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINE_VIEW"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_LINE_VIEW			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINE_OPTION"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_LINE_OPTION		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINK_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_LINK_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LOOP_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_LOOP_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR1				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR2				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR3				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR4				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR5				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR6				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR7				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR8				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR9"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR9				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR10"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_COLOR10			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DEAD_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_DEAD_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ALIVE_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_ALIVE_COLOR		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ACMCOLUMN"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT1_ACMCOLUMN			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/START_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_START_AXIS_X		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/START_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_START_AXIS_Y		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/END_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM);
	m_strCLIENT2_END_AXIS_X			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/END_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_END_AXIS_Y			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/CEQID"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_CEQID				 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/PSR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_PSR				 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[0]				= GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[1]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[2]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[3]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[4]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[5]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[6]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND[7]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[0]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[1]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[2]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[3]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[4]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[5]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[6]				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT2_RTREND_COLOR[7]				= GetConfigMsg( strAttrMsg );






	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/START_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_START_AXIS_X		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/START_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_START_AXIS_Y		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/END_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_END_AXIS_X			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/END_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_END_AXIS_Y			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ZOOM_VAL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_ZOOM_VAL			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DIAGRAM_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_DIAGRAM_X			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DIAGRAM_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_DIAGRAM_Y			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/FOCUS_DL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_FOCUS_DL			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/OPEN_DL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_OPEN_DL			 = GetConfigMsg( strAttrMsg );

	//단선도 뷰어 옵션 추가
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ZOOM_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_ZOOM_LEVEL		 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/STEP_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_STEP_LEVEL		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/VIEW_TYPE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_TYPE					 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/NAME_OR_INDEX"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_NAMEORINDEX			 = GetConfigMsg( strAttrMsg );
	
	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/SELECT_PHASE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_SELECT_PHASE			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/SELECT_VOLT"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_SELECT_VOLT			 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/FI_MOVE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_FI_MOVE				 = GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DL_LINK"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_DL_LINK				 = GetConfigMsg( strAttrMsg );


	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINE_VIEW"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_LINE_VIEW			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINE_OPTION"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_LINE_OPTION		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINK_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_LINK_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LOOP_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_LOOP_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR1				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR2				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR3				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR4				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR5				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR6				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR7				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR8				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR9"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR9				= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR10"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_COLOR10			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DEAD_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_DEAD_COLOR			= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ALIVE_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_ALIVE_COLOR		= GetConfigMsg( strAttrMsg );

	strAttrMsg.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ACMCOLUMN"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	m_strCLIENT3_ACMCOLUMN			= GetConfigMsg( strAttrMsg );
	//m_strVIEW_ZOOM_LEVEL			 = GetConfigMsg( _T("//HMI/VIEW/ZOOM_LEVEL") );
	//m_strVIEW_STEP_LEVEL			 = GetConfigMsg( _T("//HMI/VIEW/STEP_LEVEL") );

	//m_strVIEW_NAMEORINDEX			 = GetConfigMsg( _T("//HMI/VIEW/NAME_OR_INDEX") );
	//m_strVIEW_TYPE					 = GetConfigMsg( _T("//HMI/VIEW/VIEW_TYPE") );
	//m_strVIEW_SELECT_PHASE			 = GetConfigMsg( _T("//HMI/VIEW/SELECT_PHASE") );
	//m_strVIEW_SELECT_VOLT			 = GetConfigMsg( _T("//HMI/VIEW/SELECT_VOLT") );

	//m_strVIEW_FI_MOVE				 = GetConfigMsg( _T("//HMI/VIEW/FI_MOVE") );
	//m_strVIEW_DL_LINK				 = GetConfigMsg( _T("//HMI/VIEW/DL_LINK") );

	m_strCONTROL_POSSIBLE_DPGRP	     = GetConfigMsg( _T("//HMI/CONTROL/POSSIBLE_DPGRP") );

	// 20140313 kylee : XML에서 알람셋팅 로드
	//LoadConfigAlarmSetting();

	// 20140410 kylee : XML에서 알람 필터링 셋팅 로드
	//LoadConfigAlarmEventFiltering();

	// 20140320 kylee : XML에서 마지막으로 선택된 Tree Item 로드
	m_strTOTALINFO_SYSTEMSTATE_LASTSELECTION		 = GetConfigMsg( _T("//HMI/LAST_SELECTION/SYSTEM_STATE/CURRENT_SELECTION") );
	
	//DNP 포인트 로딩
	GetConfigDnp   ( _T("//HMI/UPC_HEAD_POINT/UPC_DNP/INDEX") );
	GetConfigManual( _T("//HMI/UPC_HEAD_POINT/UPC_MANUAL/INDEX") );
	GetConfigSys   ( _T("//HMI/UPC_HEAD_POINT/COMPUTERSTATUS/INDEX") );

	m_xmlConfig.Close();
	return bRet;
}

BOOL CConfigXML::CALInfo()
{	
	BOOL bRet = TRUE;
	CString strConfigPath, strErrMsg, strAttrMsg;
	
	TCHAR tzFileName[ MAX_PATH ], tzDrive[ _MAX_DRIVE ], tzPath[ _MAX_DIR ], tzName[ _MAX_FNAME ], tzExt[ _MAX_EXT ];
	TCHAR tzTemp[ MAX_PATH ] = { 0, };

	GetModuleFileName( NULL, tzFileName, sizeof(tzFileName) );
	_tsplitpath_s( tzFileName, tzDrive, _MAX_DRIVE, tzPath, _MAX_DIR, tzName, _MAX_FNAME, tzExt, _MAX_EXT );

	m_strEXEPath.Format( _T("%s%s"), tzDrive, tzPath );	
	strConfigPath.Format( _T("%s%s\\%s"), m_strEXEPath, m_strENGINE_XML_PATH, _T("CAL_TABLE.xml") );
	
	bRet = OpenXML( strConfigPath, m_xmlCALInfo );
	if( !bRet )		return bRet;

	CXmlNodesPtr pNode = m_xmlCALInfo.SelectNodes(_T("//CALCULATION/CAL")); //20150731 jmkim "//SECTION/LINE"으로 되어 있어 XML을 불러오지 못함 - cal로 수정완료
	int nCount = pNode->GetCount();
	for(int n = 0; n < pNode->GetCount(); n++)
	{
		CXmlNodePtr pSubNode = pNode->GetItem(n);

		int nCEQID		= _ttoi(pSubNode->GetAttribute(_T("CEQ_ID"), _T("")));
		int nIndex		= _ttoi(pSubNode->GetAttribute(_T("NO"), _T("")));
		int nCALPoint   = _ttoi(pSubNode->GetAttribute(_T("CAL_ID"), _T("")));
		CAL_INDEX Inx   = CAL_INDEX(nCEQID, nIndex);
		if( nCEQID > 0 && nIndex > 0)
			m_calIndex.insert(make_pair(Inx, nCALPoint));
	}

	m_xmlCALInfo.Close();
	return bRet;
}
BOOL CConfigXML::SectionInfo()
{
	BOOL bRet = TRUE;
	//CString strConfigPath, strErrMsg, strAttrMsg;
	//
	//TCHAR tzFileName[ MAX_PATH ], tzDrive[ _MAX_DRIVE ], tzPath[ _MAX_DIR ], tzName[ _MAX_FNAME ], tzExt[ _MAX_EXT ];
	//TCHAR tzTemp[ MAX_PATH ] = { 0, };

	//GetModuleFileName( NULL, tzFileName, sizeof(tzFileName) );
	//_tsplitpath_s( tzFileName, tzDrive, _MAX_DRIVE, tzPath, _MAX_DIR, tzName, _MAX_FNAME, tzExt, _MAX_EXT );

	//m_strEXEPath.Format( _T("%s%s"), tzDrive, tzPath );	
	//strConfigPath.Format( _T("%s%s\\%s"), m_strEXEPath, m_strENGINE_XML_PATH, _T("LINE_TABLE.xml") );
	//
	//bRet = OpenXML( strConfigPath, m_xmlSectionInfo );
	//if( !bRet )		return bRet;

	//CXmlNodesPtr pNode = m_xmlSectionInfo.SelectNodes(_T("//CALCULATION/CAL"));
	//int nCount = pNode->GetCount();
	//for(int n = 0; n < pNode->GetCount(); n++)
	//{
	//	CXmlNodePtr pSubNode = pNode->GetItem(n);

	//	int nCEQID		= _ttoi(pSubNode->GetAttribute(_T("CEQ_ID"), _T("")));
	//	int nSWID		= _ttoi(pSubNode->GetAttribute(_T("SW_ID"), _T("")));
	//	int nRefID		= _ttoi(pSubNode->GetAttribute(_T("REF_ID"), _T("")));


	//	if( nCEQID > 0 )
	//	{
	//		ST_SECTION_LIST *section  = new ST_SECTION_LIST();
	//		section->nCEQ = nCEQID;
	//		section->nSwCEQ = nSWID;
	//		section->nREFCEQ = nRefID;
	//		SECList.insert(section);
	//	}
	//}

	//if(SECList.sizeof() > 0)
	//{
	//	list< ST_SECTION_LIST *>::iterator *s = SECList.begin();
	//	for(; s != SECList.end(); s++)
	//	{
	//		ST_SECTION_LIST *section  = (ST_SECTION_LIST*)(s);
	//		m_SecIndex.insert(std::make_pair(section->nCEQ, s);
	//	}
	//}
	
	//m_xmlSectionInfo.Close();
	return bRet;
}
CString CConfigXML::GetCalPoint( CString strXPath )
{
	CString strMsg;
	CXmlNode node = m_xmlCALInfo.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return strMsg;

	strMsg = node.GetValue();
	return strMsg;
}

void CConfigXML::LogInfo( CString strProgram, CString strMsg, int nLogLevel, CString strStart )
{
	int  nLOG_LOG_LEVEL = _ttoi( m_strLOG_LOG_LEVEL );	
	
	if     ( nLOG_LOG_LEVEL == LOG_NOTHING )		return;
	else if( nLOG_LOG_LEVEL == LOG_INFO )
	{
		if( nLogLevel != LOG_INFO )		return;
	}
	else if( nLOG_LOG_LEVEL == LOG_FULL )
	{
		if( nLogLevel == LOG_NOTHING )		return;
	}

	BOOL bRet = TRUE;	
	WORD wd   = 0xFEFF;		// UNICODE 식별자

	
	CString strDir, strPath, strTag, strLog;
	CFile   file;

	try
	{
		COleDateTime cls_time_now = COleDateTime::GetCurrentTime();
		strDir.Format( _T("%s%s\\%s\\%s"), m_strEXEPath, m_strENGINE_LOG_PATH, strProgram, cls_time_now.Format( _T("%Y\\%m\\%d\\") ) );	
		
		::SHCreateDirectoryEx( NULL, strDir, NULL );
		
		if( strStart != _T("") )
			strPath.Format( _T("%s\\%s_%s_%s"), strDir, strProgram, strStart, cls_time_now.Format( _T("%Y%m%d_%HH.log") ) );
		else
			strPath.Format( _T("%s\\%s_%s"), strDir, strProgram, cls_time_now.Format( _T("%Y%m%d_%HH.log") ) );
		
		strTag .Format( _T("[%s] "), m_strOPERATOR_OP_NAME );
		strLog = cls_time_now.Format( _T("[%Y/%m/%d %H:%M:%S]") ) + strTag + strMsg + _N("");

		bRet = file.Open( strPath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone );
		if( !bRet ) return;

		file.Write( &wd, 2 );
		file.SeekToEnd();
		file.Write( strLog, strLog.GetLength() * sizeof( TCHAR ) );
		file.Close();
	}
	catch( CException* e )
	{
		if( bRet )	file.Close();
		e->Delete();
	}

	return;
}


BOOL CConfigXML::OpenXML( CString strFilePath, CXml &xml )
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


BOOL CConfigXML::OpenConfig()
{
	BOOL bRet = TRUE;

	CString strConfigPath;
	strConfigPath.Format( _T("%s%s"), m_strEXEPath, _T("config.xml") );
	
	bRet = OpenXML( strConfigPath, m_xmlConfig );
	return bRet;
}


void CConfigXML::CloseConfig()
{
	m_xmlConfig.Close();
}


void CConfigXML::SaveFile()
{
	CString strConfigPath;
	strConfigPath.Format( _T("%s%s"), m_strEXEPath, _T("config.xml") );
	m_xmlConfig.SaveWithFormatted( strConfigPath );
}


void CConfigXML::KillProcess( CString strProcessName )
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


int CConfigXML::SplitByPattern( TCHAR *strSource, CString strSplitBy, CStringArray &arraySource, CString &strOrg )
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


CString CConfigXML::GetLangPath()
{	
/*
	switch( GetSystemDefaultLangID() )
	{
	// Korean
	case 0x0412:		
		strLangName = _T("KOR.xml");
		break;

	// English
	case 0x0409:
	default:		
		strLangName = _T("ENG.xml");
		break;
	}
*/	
	CString strLangName;
	int nVal = _ttoi( m_strLANGUAGE_LANG_SET );
	
	if( nVal == LANGUAGE_KOR )	strLangName.Format( _T("%s%s\\%s"), m_strEXEPath, m_strENGINE_XML_PATH, _T("KOR.xml") );
	else						strLangName.Format( _T("%s%s\\%s"), m_strEXEPath, m_strENGINE_XML_PATH, _T("ENG.xml") );

	return strLangName;
}


CString CConfigXML::GetLangMsg( CString strProgram, CString strType, UINT nID )
{
	CString strMsg, strXPath, strKey;	

	strKey.Format(_T("%s_%s_%04d"),strProgram,strType,nID);

	strMsg ="";
	m_mapXmlList.Lookup(strKey,strMsg);

	if(strMsg == "")
	{
		CString result;
		result.Format( _T("GetLangMsg Function Fail( MSG Empty ): %s") ,strKey);
		LogInfo( TOTALINFO_HMI, result, LOG_FULL );
	}



	/*strXPath.Format( _T("//PROGRAM/%s/%s[@ID='%04d']"),	strProgram,	strType, nID );

	CXmlNode node = m_xmlLang.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return strMsg;

	strMsg = node.GetValue();
	strMsg.Replace( _T("\\n"), _T("\n") );*/

	return strMsg;
}


CString CConfigXML::GetConfigMsg( CString strXPath )
{
	CString strMsg=_T("");
	CXmlNode node = m_xmlConfig.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return strMsg;

	strMsg = node.GetValue();
	return strMsg;
}


CString CConfigXML::GetConfigAttr( CString strXPath, CString strAttr )
{
	CString strMsg;
	CXmlNode node = m_xmlConfig.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return strMsg;

	strMsg = node.GetAttribute( strAttr, _T("") );
	return strMsg;
}

////DNP- 자동 HEAD POINT 로딩&
void CConfigXML::GetConfigDnp( CString strXPath )
{
	CString strMsg;
	CXmlNodesPtr pNode = m_xmlConfig.SelectNodes(strXPath);
	int nCount = pNode->GetCount();
	for(int n = 0; n < pNode->GetCount(); n++)
	{
		CXmlNodePtr pSubNode = pNode->GetItem(n);
		m_stDnpPoint[n].index		= _ttoi(pSubNode->GetAttribute(_T("ID"), _T("")));
		m_stDnpPoint[n].type		= pSubNode->GetAttribute(_T("TYPE"), _T(""));
		m_stDnpPoint[n].point_name  = pSubNode->GetAttribute(_T("UPC_NAME"), _T(""));
		m_stDnpPoint[n].size		= _ttoi(pSubNode->GetAttribute(_T("UPC_SIZE"), _T("")));  
	}
}
////DNP- MANUAL HEAD POINT 로딩
void CConfigXML::GetConfigManual( CString strXPath )
{
	CString strMsg;
	CXmlNodesPtr pNode = m_xmlConfig.SelectNodes(strXPath);
	int nCount = pNode->GetCount();
	for(int n = 0; n < pNode->GetCount(); n++)
	{
		CXmlNodePtr pSubNode = pNode->GetItem(n);
		m_stManualPoint[n].index		= _ttoi(pSubNode->GetAttribute(_T("ID"), _T("")));
		m_stManualPoint[n].type			= pSubNode->GetAttribute(_T("TYPE"), _T(""));
		m_stManualPoint[n].point_name	= pSubNode->GetAttribute(_T("UPC_NAME"), _T(""));
		m_stManualPoint[n].size			= _ttoi(pSubNode->GetAttribute(_T("UPC_SIZE"), _T("")));  
	}
}

////DNP- SYS HEAD POINT 로딩
void CConfigXML::GetConfigSys( CString strXPath )
{
	CString strMsg;
	CXmlNodesPtr pNode = m_xmlConfig.SelectNodes(strXPath);
	int nCount = pNode->GetCount();
	for(int n = 0; n < pNode->GetCount(); n++)
	{
		CXmlNodePtr pSubNode = pNode->GetItem(n);
		m_stSysPoint[n].index			= _ttoi(pSubNode->GetAttribute(_T("ID"), _T("")));
		m_stSysPoint[n].type			= pSubNode->GetAttribute(_T("TYPE"), _T(""));
		m_stSysPoint[n].point_name		= pSubNode->GetAttribute(_T("UPC_NAME"), _T(""));
		m_stSysPoint[n].size			= _ttoi(pSubNode->GetAttribute(_T("UPC_SIZE"), _T("")));  
	}
}

CString CConfigXML::GetConfigDecode( CString strXPath )
{
	CString strMsg;
	CXmlNode node = m_xmlConfig.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return strMsg;

	strMsg = node.GetValue();
	
	BYTE pBuff[ MAX_PATH ] = { 0, };
	LONG lSize = 0;
	BOOL bRet  = m_xmlConfig.Base64Decode( strMsg, pBuff, lSize );
	
	if( !bRet )
		return strMsg;
	
	CString strDecode( (LPCSTR)&pBuff, sizeof( pBuff ) );
	return strDecode;
}


CString CConfigXML::GetBuildTime()
{
	CString strRet, strDate, strYear, strMonth, strDay;
	strDate.Format( _T("%s"), _T(__DATE__) );
	
	int nYear  = 0;
	int nMonth = 0;
	int nDay   = 0;

	CStringArray arrDate;
	SplitByPattern( (TCHAR *)(LPCTSTR)strDate, _T(" "), arrDate, strDate );

	int i;
	for( i = 0; i < arrDate.GetCount(); i++ )
	{
		if     ( i == 0 )	{	strMonth = arrDate.GetAt( i );	nMonth = _ttoi( strMonth );		}
		else if( i == 1 )	{	strDay   = arrDate.GetAt( i );	nDay   = _ttoi( strDay );		}
		else if( i == 2 )	{	strYear  = arrDate.GetAt( i );	nYear  = _ttoi( strYear );		}
	}

	if     ( strMonth == _T("Jan") )	nMonth =  1;
	else if( strMonth == _T("Feb") )	nMonth =  2;
	else if( strMonth == _T("Mar") )	nMonth =  3;
	else if( strMonth == _T("Apr") )	nMonth =  4;
	else if( strMonth == _T("May") )	nMonth =  5;
	else if( strMonth == _T("Jun") )	nMonth =  6;
	else if( strMonth == _T("Jul") )	nMonth =  7;
	else if( strMonth == _T("Aug") )	nMonth =  8;
	else if( strMonth == _T("Sep") )	nMonth =  9;
	else if( strMonth == _T("Oct") )	nMonth = 10;
	else if( strMonth == _T("Nov") )	nMonth = 11;
	else if( strMonth == _T("Dec") )	nMonth = 12;

	strRet.Format( _T("%04d%02d%02d"), nYear, nMonth, nDay );
	return strRet;
}


void CConfigXML::SetConfigMsg( CString strXPath, CString strValue)
{	
	CXmlNode node = m_xmlConfig.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return;
	
	node.SetValue( strValue );
	
}
void CConfigXML::SetConfigMsgNewNode( CString strXPath, CString strValue)
{	
	
	CStringArray arrNodes;
	CString strNodeName;
	
	CXmlNode  Node = m_xmlConfig.GetRoot();	
	
	int i;
	int nRet = SplitByPattern( (TCHAR *)(LPCTSTR)strXPath, _T("/"), arrNodes, strXPath );
	
	CXmlNode  NodeChk;
	
	
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );
	
	CString strNodes,strTmp;
	if(NodeChk.IsNull())
	{
		for( i = 0; i < nRet; i++ )
		{
			strNodeName = arrNodes.GetAt( i );
			strTmp.Format(_T("%s/%s"),strNodes,strNodeName);

			NodeChk = m_xmlConfig.SelectSingleNode( strTmp );
			if( NodeChk.IsNull() )
			{
				if(i==1)
				{
					Node = m_xmlConfig.GetRoot()->NewChild( _T("USER") );
					Node.SetAttribute( _T("OP_NAME"), m_strOPERATOR_OP_NAME );
					Node.SetAttribute( _T("OP_NUM"),  m_strOPERATOR_OP_NUM );
				}
				Node = Node.NewChild( strNodeName );
			}
			else
				Node = NodeChk;
			
			strNodes = strTmp;
		}
	}
	
	Node.SetValue( strValue );
	

}

void CConfigXML::SetConfigNode( CString strXPath, CString strValue )
{
	CStringArray arrNodes;
	CString strNodeName;
	
	CXmlNode  Node = m_xmlConfig.GetRoot();	
	
	int i;
	int nRet = SplitByPattern( (TCHAR *)(LPCTSTR)strXPath, _T("/"), arrNodes, strXPath );
	
	for( i = 0; i < nRet; i++ )
	{
		strNodeName = arrNodes.GetAt( i );
		
		CXmlNode NewNode = m_xmlConfig.CreateNode( strNodeName );
		Node.AttachChild( NewNode );
		Node = NewNode;
	}

	Node.SetValue( strValue );	
}


void CConfigXML::SetConfigEncode( CString strXPath, CString strValue )
{
	CXmlNode node = m_xmlConfig.SelectSingleNode( strXPath );
	
	if( node.IsNull() )
		return;

	CString strEncode;
	BYTE pBuff[ MAX_PATH ] = { 0, };
	WideCharToMultiByte( CP_ACP, 0, strValue, -1, (LPSTR)pBuff, MAX_PATH, NULL, NULL );
		
	strEncode = m_xmlConfig.Base64Encode( pBuff, strValue.GetLength() );
	node.SetValue( strEncode );	
}


void CConfigXML::SetConfigUser1()
{
	if( !OpenConfig() )
		return;	
	
	CXmlNode Node, NodeChk;
	CString strXPath;	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );	
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );
	
	if( NodeChk.IsNull() )
	{
		Node = m_xmlConfig.GetRoot()->NewChild( _T("USER") );
		Node.SetAttribute( _T("OP_NAME"), m_strOPERATOR_OP_NAME );
		Node.SetAttribute( _T("OP_NUM"),  m_strOPERATOR_OP_NUM );
	}
	else
		Node = NodeChk;

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )
	{
		Node = Node.NewChild( _T("CLIENT1") );
	}
	else
		Node = NodeChk;

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/START_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("START_AXIS_X") )->SetValue( m_strCLIENT1_START_AXIS_X );
	else						SetConfigMsg( strXPath, m_strCLIENT1_START_AXIS_X );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/START_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("START_AXIS_Y") )->SetValue( m_strCLIENT1_START_AXIS_Y );
	else						SetConfigMsg( strXPath, m_strCLIENT1_START_AXIS_Y );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/END_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("END_AXIS_X") )->SetValue( m_strCLIENT1_END_AXIS_X );
	else						SetConfigMsg( strXPath, m_strCLIENT1_END_AXIS_X );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/END_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("END_AXIS_Y") )->SetValue( m_strCLIENT1_END_AXIS_Y );
	else						SetConfigMsg( strXPath, m_strCLIENT1_END_AXIS_Y );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ZOOM_VAL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("ZOOM_VAL") )->SetValue( m_strCLIENT1_ZOOM_VAL );
	else						SetConfigMsg( strXPath, m_strCLIENT1_ZOOM_VAL );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DIAGRAM_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("DIAGRAM_X") )->SetValue( m_strCLIENT1_DIAGRAM_X );
	else						SetConfigMsg( strXPath, m_strCLIENT1_DIAGRAM_X );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DIAGRAM_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("DIAGRAM_Y") )->SetValue( m_strCLIENT1_DIAGRAM_Y );
	else						SetConfigMsg( strXPath, m_strCLIENT1_DIAGRAM_Y );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ZOOM_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("ZOOM_LEVEL") )->SetValue( DEF_ZOOM_LEVEL ); m_strCLIENT1_ZOOM_LEVEL = DEF_ZOOM_LEVEL; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_ZOOM_LEVEL );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/STEP_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("STEP_LEVEL") )->SetValue( DEF_STEP_LEVEL ); m_strCLIENT1_STEP_LEVEL = DEF_STEP_LEVEL; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_STEP_LEVEL );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/VIEW_TYPE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("VIEW_TYPE") )->SetValue( DEF_VIEW_TYPE ); m_strCLIENT1_TYPE = DEF_VIEW_TYPE; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_TYPE );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/NAME_OR_INDEX"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("NAME_OR_INDEX") )->SetValue( DEF_NAMEORINDEX ); m_strCLIENT1_NAMEORINDEX = DEF_NAMEORINDEX; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_NAMEORINDEX );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/SELECT_PHASE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("SELECT_PHASE") )->SetValue( DEF_SELECT_PHASE ); m_strCLIENT1_SELECT_PHASE = DEF_SELECT_PHASE; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_SELECT_PHASE );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/SELECT_VOLT"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("SELECT_VOLT") )->SetValue( DEF_SELECT_VOLT ); m_strCLIENT1_SELECT_VOLT = DEF_SELECT_VOLT; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_SELECT_VOLT );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/FI_MOVE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("FI_MOVE") )->SetValue( DEF_FI_MOVE ); m_strCLIENT1_FI_MOVE = DEF_FI_MOVE; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_FI_MOVE );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DL_LINK"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("DL_LINK") )->SetValue( DEF_DL_LINK ); m_strCLIENT1_DL_LINK = DEF_DL_LINK; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_DL_LINK );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINE_VIEW"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("LINE_VIEW") )->SetValue( DEF_LINE_VIEW ); m_strCLIENT1_LINE_VIEW = DEF_LINE_VIEW; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_LINE_VIEW );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINE_OPTION"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("LINE_OPTION") )->SetValue( DEF_LINE_OPTION ); m_strCLIENT1_LINE_OPTION = DEF_LINE_OPTION; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_LINE_OPTION );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LINK_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("LINK_COLOR") )->SetValue( DEF_LINK_COLOR ); m_strCLIENT1_LINK_COLOR = DEF_LINK_COLOR; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_LINK_COLOR );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/LOOP_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("LOOP_COLOR") )->SetValue( DEF_LOOP_COLOR ); m_strCLIENT1_LOOP_COLOR = DEF_LOOP_COLOR; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_LOOP_COLOR );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR1") )->SetValue( DEF_COLOR1 ); m_strCLIENT1_COLOR1 = DEF_COLOR1; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_COLOR1 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR2") )->SetValue( DEF_COLOR2 );  m_strCLIENT1_COLOR2 = DEF_COLOR2; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_COLOR2 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR3") )->SetValue( DEF_COLOR3 );  m_strCLIENT1_COLOR3 = DEF_COLOR3; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_COLOR3 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR4") )->SetValue( DEF_COLOR4 );  m_strCLIENT1_COLOR4 = DEF_COLOR4; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_COLOR4 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR5") )->SetValue( DEF_COLOR5 );  m_strCLIENT1_COLOR5 = DEF_COLOR5; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_COLOR5 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR6") )->SetValue( DEF_COLOR6 ); m_strCLIENT1_COLOR6 = DEF_COLOR6; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_COLOR6 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR7") )->SetValue( DEF_COLOR7 );  m_strCLIENT1_COLOR7 = DEF_COLOR7; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_COLOR7 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR8") )->SetValue( DEF_COLOR8 );  m_strCLIENT1_COLOR8 = DEF_COLOR8; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_COLOR8 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR9"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR9") )->SetValue( DEF_COLOR9 );  m_strCLIENT1_COLOR9 = DEF_COLOR9; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_COLOR9 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/COLOR10"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR10") )->SetValue( DEF_COLOR10 );  m_strCLIENT1_COLOR10 = DEF_COLOR10; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_COLOR10 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/DEAD_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("DEAD_COLOR") )->SetValue( DEF_DEAD_COLOR );  m_strCLIENT1_DEAD_COLOR = DEF_DEAD_COLOR; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_DEAD_COLOR );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT1/ALIVE_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("ALIVE_COLOR") )->SetValue( DEF_ALIVE_COLOR ); m_strCLIENT1_ALIVE_COLOR = DEF_ALIVE_COLOR; }
	else						SetConfigMsg( strXPath, m_strCLIENT1_ALIVE_COLOR );

	SaveFile();
	CloseConfig();
}


void CConfigXML::SetConfigUser2()
{
	if( !OpenConfig() )
		return;

	CXmlNode Node, NodeChk;
	CString strXPath;	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );	
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );
	
	if( NodeChk.IsNull() )
	{
		Node = m_xmlConfig.GetRoot()->NewChild( _T("USER") );
		Node.SetAttribute( _T("OP_NAME"), m_strOPERATOR_OP_NAME );
		Node.SetAttribute( _T("OP_NUM"),  m_strOPERATOR_OP_NUM );
	}
	else
		Node = NodeChk;

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )
	{
		Node = Node.NewChild( _T("CLIENT2") );		
	}
	else
		Node = NodeChk;

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/START_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )
	{
		CXmlNode NodeNew = m_xmlConfig.CreateNode( _T("START_AXIS_X") );
		NodeNew.SetValue( m_strCLIENT2_START_AXIS_X );
		Node.AttachChild( NodeNew );
	}

	if( NodeChk.IsNull() )		Node.NewChild( _T("START_AXIS_X") )->SetValue( m_strCLIENT2_START_AXIS_X );
	else						SetConfigMsg( strXPath, m_strCLIENT2_START_AXIS_X );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/START_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("START_AXIS_Y") )->SetValue( m_strCLIENT2_START_AXIS_Y );
	else						SetConfigMsg( strXPath, m_strCLIENT2_START_AXIS_Y );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/END_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("END_AXIS_X") )->SetValue( m_strCLIENT2_END_AXIS_X );
	else						SetConfigMsg( strXPath, m_strCLIENT2_END_AXIS_X );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/END_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("END_AXIS_Y") )->SetValue( m_strCLIENT2_END_AXIS_Y );
	else						SetConfigMsg( strXPath, m_strCLIENT2_END_AXIS_Y );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/CEQID"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("CEQID") )->SetValue( m_strCLIENT2_CEQID );
	else						SetConfigMsg( strXPath, m_strCLIENT2_CEQID );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/PSR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("PSR") )->SetValue( m_strCLIENT2_PSR );
	else						SetConfigMsg( strXPath, m_strCLIENT2_PSR );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("REAL_TREND1") )->SetValue( m_strCLIENT2_RTREND[0] );
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND[0] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("REAL_TREND2") )->SetValue( m_strCLIENT2_RTREND[1] );
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND[1] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("REAL_TREND3") )->SetValue( m_strCLIENT2_RTREND[2] );
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND[2] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("REAL_TREND4") )->SetValue( m_strCLIENT2_RTREND[3] );
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND[3] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("REAL_TREND5") )->SetValue( m_strCLIENT2_RTREND[4] );
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND[4] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("REAL_TREND6") )->SetValue( m_strCLIENT2_RTREND[5] );
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND[5] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("REAL_TREND7") )->SetValue( m_strCLIENT2_RTREND[6] );
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND[6] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("REAL_TREND8") )->SetValue( m_strCLIENT2_RTREND[7] );
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND[7] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("REAL_TREND_COLOR1") )->SetValue( _T("0") ); m_strCLIENT2_RTREND_COLOR[0] = _T("0"); }
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND_COLOR[0] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("REAL_TREND_COLOR2") )->SetValue(  _T("1") ); m_strCLIENT2_RTREND_COLOR[0] = _T("1"); }
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND_COLOR[1] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("REAL_TREND_COLOR3") )->SetValue(  _T("2") ); m_strCLIENT2_RTREND_COLOR[0] = _T("2"); }
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND_COLOR[2] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("REAL_TREND_COLOR4") )->SetValue(  _T("3") ); m_strCLIENT2_RTREND_COLOR[0] = _T("3"); }
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND_COLOR[3] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("REAL_TREND_COLOR5") )->SetValue(  _T("4") ); m_strCLIENT2_RTREND_COLOR[0] = _T("4"); }
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND_COLOR[4] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("REAL_TREND_COLOR6") )->SetValue(  _T("5") ); m_strCLIENT2_RTREND_COLOR[0] = _T("5"); }
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND_COLOR[5] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("REAL_TREND_COLOR7") )->SetValue(  _T("6") ); m_strCLIENT2_RTREND_COLOR[0] = _T("6"); }
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND_COLOR[6] );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT2/REAL_TREND_COLOR8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("REAL_TREND_COLOR8") )->SetValue(  _T("7") ); m_strCLIENT2_RTREND_COLOR[0] = _T("7"); }
	else						SetConfigMsg( strXPath, m_strCLIENT2_RTREND_COLOR[7] );

	SaveFile();
	CloseConfig();
}


void CConfigXML::SetConfigUser3()
{
	if( !OpenConfig() )
		return;

	CXmlNode Node, NodeChk;
	CString strXPath;	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );	
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );
	
	if( NodeChk.IsNull() )
	{
		Node = m_xmlConfig.GetRoot()->NewChild( _T("USER") );
		Node.SetAttribute( _T("OP_NAME"), m_strOPERATOR_OP_NAME );
		Node.SetAttribute( _T("OP_NUM"),  m_strOPERATOR_OP_NUM );
	}
	else
		Node = NodeChk;

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )
	{
		Node = Node.NewChild( _T("CLIENT3") );
	}
	else
		Node = NodeChk;

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/START_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("START_AXIS_X") )->SetValue( m_strCLIENT3_START_AXIS_X );
	else						SetConfigMsg( strXPath, m_strCLIENT3_START_AXIS_X );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/START_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("START_AXIS_Y") )->SetValue( m_strCLIENT3_START_AXIS_Y );
	else						SetConfigMsg( strXPath, m_strCLIENT3_START_AXIS_Y );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/END_AXIS_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("END_AXIS_X") )->SetValue( m_strCLIENT3_END_AXIS_X );
	else						SetConfigMsg( strXPath, m_strCLIENT3_END_AXIS_X );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/END_AXIS_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("END_AXIS_Y") )->SetValue( m_strCLIENT3_END_AXIS_Y );
	else						SetConfigMsg( strXPath, m_strCLIENT3_END_AXIS_Y );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ZOOM_VAL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("ZOOM_VAL") )->SetValue( m_strCLIENT3_ZOOM_VAL );
	else						SetConfigMsg( strXPath, m_strCLIENT3_ZOOM_VAL );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DIAGRAM_X"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("DIAGRAM_X") )->SetValue( m_strCLIENT3_DIAGRAM_X );
	else						SetConfigMsg( strXPath, m_strCLIENT3_DIAGRAM_X );
	
	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DIAGRAM_Y"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("DIAGRAM_Y") )->SetValue( m_strCLIENT3_DIAGRAM_Y );
	else						SetConfigMsg( strXPath, m_strCLIENT3_DIAGRAM_Y );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/FOCUS_DL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("FOCUS_DL") )->SetValue( m_strCLIENT3_FOCUS_DL );
	else						SetConfigMsg( strXPath, m_strCLIENT3_FOCUS_DL );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/OPEN_DL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("OPEN_DL") )->SetValue( m_strCLIENT3_OPEN_DL );
	else						SetConfigMsg( strXPath, m_strCLIENT3_OPEN_DL );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ZOOM_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("ZOOM_LEVEL") )->SetValue( DEF_ZOOM_LEVEL ); m_strCLIENT3_ZOOM_LEVEL = DEF_ZOOM_LEVEL; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_ZOOM_LEVEL );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/STEP_LEVEL"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("STEP_LEVEL") )->SetValue( DEF_STEP_LEVEL ); m_strCLIENT3_STEP_LEVEL = DEF_STEP_LEVEL; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_STEP_LEVEL );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/VIEW_TYPE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("VIEW_TYPE") )->SetValue( DEF_VIEW_TYPE ); m_strCLIENT3_TYPE = DEF_VIEW_TYPE; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_TYPE );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/NAME_OR_INDEX"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("NAME_OR_INDEX") )->SetValue( DEF_NAMEORINDEX ); m_strCLIENT3_NAMEORINDEX = DEF_NAMEORINDEX; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_NAMEORINDEX );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/SELECT_PHASE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("SELECT_PHASE") )->SetValue( DEF_SELECT_PHASE ); m_strCLIENT3_SELECT_PHASE = DEF_SELECT_PHASE; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_SELECT_PHASE );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/SELECT_VOLT"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("SELECT_VOLT") )->SetValue( DEF_SELECT_VOLT ); m_strCLIENT3_SELECT_VOLT = DEF_SELECT_VOLT; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_SELECT_VOLT );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/FI_MOVE"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("FI_MOVE") )->SetValue( DEF_FI_MOVE ); m_strCLIENT3_FI_MOVE = DEF_FI_MOVE; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_FI_MOVE );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DL_LINK"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("DL_LINK") )->SetValue( DEF_DL_LINK ); m_strCLIENT3_DL_LINK = DEF_DL_LINK; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_DL_LINK );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINE_VIEW"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("LINE_VIEW") )->SetValue( DEF_LINE_VIEW ); m_strCLIENT3_LINE_VIEW = DEF_LINE_VIEW; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_LINE_VIEW );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINE_OPTION"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("LINE_OPTION") )->SetValue( DEF_LINE_OPTION ); m_strCLIENT3_LINE_OPTION = DEF_LINE_OPTION; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_LINE_OPTION );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LINK_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("LINK_COLOR") )->SetValue( DEF_LINK_COLOR ); m_strCLIENT3_LINK_COLOR = DEF_LINK_COLOR; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_LINK_COLOR );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/LOOP_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("LOOP_COLOR") )->SetValue( DEF_LOOP_COLOR ); m_strCLIENT3_LOOP_COLOR = DEF_LOOP_COLOR; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_LOOP_COLOR );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR1"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR1") )->SetValue( DEF_COLOR1 ); m_strCLIENT3_COLOR1 = DEF_COLOR1; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_COLOR1 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR2"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR2") )->SetValue( DEF_COLOR2 ); m_strCLIENT3_COLOR2 = DEF_COLOR2; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_COLOR2 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR3"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR3") )->SetValue( DEF_COLOR3 ); m_strCLIENT3_COLOR3 = DEF_COLOR3; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_COLOR3 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR4"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR4") )->SetValue( DEF_COLOR4 ); m_strCLIENT3_COLOR4 = DEF_COLOR4; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_COLOR4 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR5"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR5") )->SetValue( DEF_COLOR5 ); m_strCLIENT3_COLOR5 = DEF_COLOR5; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_COLOR5 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR6"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR6") )->SetValue( DEF_COLOR6 ); m_strCLIENT3_COLOR6 = DEF_COLOR6; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_COLOR6 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR7"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR7") )->SetValue( DEF_COLOR7 ); m_strCLIENT3_COLOR7 = DEF_COLOR7; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_COLOR7 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR8"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR8") )->SetValue( DEF_COLOR8 ); m_strCLIENT3_COLOR8 = DEF_COLOR8; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_COLOR8 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR9"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR9") )->SetValue( DEF_COLOR9 ); m_strCLIENT3_COLOR9 = DEF_COLOR9; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_COLOR9 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/COLOR10"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("COLOR10") )->SetValue( DEF_COLOR10 ); m_strCLIENT3_COLOR10 = DEF_COLOR10; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_COLOR10 );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/DEAD_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("DEAD_COLOR") )->SetValue( DEF_DEAD_COLOR ); m_strCLIENT3_DEAD_COLOR = DEF_DEAD_COLOR; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_DEAD_COLOR );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ALIVE_COLOR"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("ALIVE_COLOR") )->SetValue( DEF_ALIVE_COLOR ); m_strCLIENT3_ALIVE_COLOR = DEF_ALIVE_COLOR; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_ALIVE_COLOR );

	strXPath.Format( _T("//HMI/USER[@OP_NAME='%s'][@OP_NUM='%s']/CLIENT3/ACMCOLUMN"), m_strOPERATOR_OP_NAME, m_strOPERATOR_OP_NUM );
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		{ Node.NewChild( _T("ACMCOLUMN") )->SetValue( DEF_ACMCOLUMN ); m_strCLIENT3_ACMCOLUMN = DEF_ACMCOLUMN; }
	else						SetConfigMsg( strXPath, m_strCLIENT3_ACMCOLUMN );

	SaveFile();
	CloseConfig();
}


void CConfigXML::SetConfigLogin( int nStatus )
{
	if( !OpenConfig() )
		return;
	
	CString strXPath;	
	CString strOP_NUM, strOP_NAME;
	strXPath .Format( _T("//HMI/OPERATOR/OP_LOGIN") );
	m_strOPERATOR_OP_LOGIN.Format( _T("%d"), nStatus );

	SetConfigMsg( strXPath, m_strOPERATOR_OP_LOGIN );


	SaveFile();
	CloseConfig();
}


void CConfigXML::SetTrendData( CString strFileName, int nSeries, int nSize, int pData[][MAX_TIME_CNT] )
{
	if( pData == NULL )
		return;

	::CoInitialize( NULL );
	
	CXml xmlTrend;
	CXmlNode node;
	BOOL bRet = TRUE;

	CString strFilePath, strSeries, strXPath, strValue;
	strFilePath.Format( _T("%sXML\\%s"), m_strEXEPath, strFileName );
	
	bRet = OpenXML( strFilePath, xmlTrend );
	if( !bRet )		return;

	int i, j;
	for( i = 0; i < nSeries; i++ )
	{
		strSeries.Format( _T("SERIES%d"), i + 1 );
		
		for( j = 0; j < nSize; j++ )
		{
			strXPath.Format( _T("//PROGRAM/%s/%s[@ID='%04d']"),	strSeries, _T("TIME"), j + 1 );
			node = xmlTrend.SelectSingleNode( strXPath );

			if( node.IsNull() )
				return;

			strValue = node.GetValue();
			
			if( strValue == _T("N/A") )
				pData[ i ][ j ] = -9999;
			else
				pData[ i ][ j ] = _ttoi( strValue );
		}
	}

	xmlTrend.Close();
	::CoUninitialize();

	return;
}


void CConfigXML::SaveTrendData( CString strFileName, int nSeries, int nSize, int pData[][MAX_TIME_CNT] )
{
	if( pData == NULL )
		return;

	::CoInitialize( NULL );
	
	CXml xmlTrend;
	CXmlNode node;
	BOOL bRet = TRUE;

	CString strFilePath, strSeries, strXPath, strValue;
	strFilePath.Format( _T("%sXML\\%s"), m_strEXEPath, strFileName );
	
	bRet = OpenXML( strFilePath, xmlTrend );
	if( !bRet )		return;

	int i, j;
	for( i = 0; i < nSeries; i++ )
	{
		strSeries.Format( _T("SERIES%d"), i + 1 );
		
		for( j = 0; j < nSize; j++ )
		{
			strXPath.Format( _T("//PROGRAM/%s/%s[@ID='%04d']"),	strSeries, _T("TIME"), j + 1 );
			
			if( pData[ i ][ j ] == -9999 )	strValue.Format( _T("N/A") );
			else							strValue.Format( _T("%d"), pData[ i ][ j ] );
			
			node = xmlTrend.SelectSingleNode( strXPath );
			node.SetValue( strValue );
		}
	}

	xmlTrend.SaveWithFormatted( strFilePath );
	xmlTrend.Close();
	::CoUninitialize();

	return;
}


void CConfigXML::DelTrendData( CString strFileName, int nSeries, int nSize, int pData[][MAX_TIME_CNT] )
{
	::CoInitialize( NULL );
	
	CXml xmlTrend;
	CXmlNode node;
	BOOL bRet = TRUE;

	CString strFilePath, strSeries, strXPath, strValue;
	strFilePath.Format( _T("%sXML\\%s"), m_strEXEPath, strFileName );
	
	bRet = OpenXML( strFilePath, xmlTrend );
	if( !bRet )		return;

	int i, j;
	for( i = 0; i < nSeries; i++ )
	{
		strSeries.Format( _T("SERIES%d"), i + 1 );
		
		for( j = 0; j < nSize; j++ )
		{
			pData[ i ][ j ] = -9999;

			strXPath.Format( _T("//PROGRAM/%s/%s[@ID='%04d']"),	strSeries, _T("TIME"), j + 1 );
			strValue.Format( _T("N/A") );
			
			node = xmlTrend.SelectSingleNode( strXPath );
			node.SetValue( strValue );
		}
	}

	xmlTrend.SaveWithFormatted( strFilePath );
	xmlTrend.Close();
	::CoUninitialize();

	return;
}

// A¾COA¤º¸ E­¸eAC °eAeCoE² ¼±AACN ¾ÆAIAU AuAa

void CConfigXML::SetConfigSystemStateSelectedItem(int nCEQID)
{
	if( nCEQID < 0 )	
		return;
	
	if( !OpenConfig() )
		return;	

	CString strCEQID;
	strCEQID.Format( _T("%d"), nCEQID );
	CXmlNode Node, NodeChk;
	CString strXPath, strXPathDetail;	
	strXPath.Format( _T("//HMI/LAST_SELECTION") );	
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )
		Node = m_xmlConfig.GetRoot()->NewChild( _T("LAST_SELECTION") );
	else
		Node = NodeChk;


	strXPath.Format( _T("//HMI/LAST_SELECTION/SYSTEM_STATE") );	
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )
		Node = Node.NewChild( _T("SYSTEM_STATE") );
	else
		Node = NodeChk;


	strXPath.Format( _T("//HMI/LAST_SELECTION/SYSTEM_STATE/CURRENT_SELECTION") );	
	NodeChk = m_xmlConfig.SelectSingleNode( strXPath );

	if( NodeChk.IsNull() )		Node.NewChild( _T("CURRENT_SELECTION") )->SetValue( strCEQID );
	else						g_cfg.SetConfigMsg( strXPath,  strCEQID );

	SaveFile();
	CloseConfig();
}


//20141207
BOOL CConfigXML::ChkTrendData( CString strFileName )
{
	BOOL bRet = FALSE;

	CString strFilePath, strSeries, strXPath, strValue;
	strFilePath.Format( _T("%sXML\\%s"), m_strEXEPath, strFileName );

	HANDLE h_file = INVALID_HANDLE_VALUE;
	try
	{
		h_file = CreateFile( strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	catch(...)
	{
		h_file = INVALID_HANDLE_VALUE;
	}

	if(h_file != INVALID_HANDLE_VALUE)
	{
		FILETIME create_time, access_time, write_time;
		GetFileTime(h_file, &create_time, &access_time, &write_time);

		SYSTEMTIME write_system_time, write_local_time;
		FileTimeToSystemTime(&write_time, &write_system_time);

		SystemTimeToTzSpecificLocalTime(NULL, &write_system_time, &write_local_time);

		SYSTEMTIME st;
		GetLocalTime(&st);

		if( write_local_time.wYear == st.wYear && write_local_time.wMonth == st.wMonth && write_local_time.wDay == st.wDay )
			bRet = TRUE;
	}
	
	CloseHandle(h_file);

	return bRet;
}


//ohb 20150128
BOOL CConfigXML::ChkTrendListFile( CString strPath )
{
	BOOL bRet = FALSE;

	CString strFilePath, strSeries, strXPath, strValue;
	strFilePath.Format( _T("%s"), strPath );

	HANDLE h_file = INVALID_HANDLE_VALUE;
	try
	{
		h_file = CreateFile( strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	catch(...)
	{
		h_file = INVALID_HANDLE_VALUE;
	}

	if(h_file != INVALID_HANDLE_VALUE)
	{
		FILETIME create_time, access_time, write_time;
		GetFileTime(h_file, &create_time, &access_time, &write_time);

		SYSTEMTIME write_system_time, write_local_time;
		FileTimeToSystemTime(&write_time, &write_system_time);

		SystemTimeToTzSpecificLocalTime(NULL, &write_system_time, &write_local_time);

		SYSTEMTIME st;
		GetLocalTime(&st);

		if( write_local_time.wYear == st.wYear && write_local_time.wMonth == st.wMonth && write_local_time.wDay == st.wDay )
			bRet = TRUE;
	}
	
	CloseHandle(h_file);

	return bRet;
}