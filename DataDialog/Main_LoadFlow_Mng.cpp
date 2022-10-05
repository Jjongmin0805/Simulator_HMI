#include "pch.h"
#include "Main_LoadFlow_Mng.h"
#include "../include/PNOVR_Ctrl/Util_FileParsing_CSV.h"
#include "../DataManager/CDataManager.h"

CMain_LoadFlow_Mng::CMain_LoadFlow_Mng(void) : m_nLFFSeqValue( 30 ), m_nLFFSeqNow( 0 ), m_nLFFSeqIndex( 0 ), m_dPFRadial( 0.0 ), m_nLFSM_Index( 1 ), m_nLFSM_CaseId( 1 )
{
	m_hLFInfor																					= INVALID_HANDLE_VALUE;
	m_pLFInfor																					= NULL;
	m_hThread_LFAPPL																			= INVALID_HANDLE_VALUE;
	m_bThread_LFAPPL																			= false;
	m_szLoadProfilePath																			= thePNO_UTILmng->GetMyPath( _T("Scada_Data"), _T("scada_current.csv") ).c_str();
	m_pLoadFlowEditor																			= NULL;
}

CMain_LoadFlow_Mng::~CMain_LoadFlow_Mng(void)
{
	if( m_vecVMLFdata.size() > 0 )
	{
		for_each( m_vecVMLFdata.begin(), m_vecVMLFdata.end(), PNOVR_EraseObjData() );
		m_vecVMLFdata.clear();
	}

	CloseHandle( m_hLFInfor );
	m_hLFInfor																					= INVALID_HANDLE_VALUE;
	UnmapViewOfFile( m_pLFInfor );
	m_pLFInfor																					= NULL;
	CloseThread();
	
}

void CMain_LoadFlow_Mng::CloseThread()
{
	m_bThread_LFAPPL																			= false;
	if( m_hThread_LFAPPL != INVALID_HANDLE_VALUE )
	{
		if( WaitForSingleObject( m_hThread_LFAPPL, 500 )  == WAIT_TIMEOUT )
		{
			TerminateThread( m_hThread_LFAPPL, 1L );
		}
		CloseHandle( m_hThread_LFAPPL );
		m_hThread_LFAPPL																		= INVALID_HANDLE_VALUE;
	}
}

void CMain_LoadFlow_Mng::Loading( void )
{
	m_dPFRadial										= acos( 0.98 );
	LoadLFFInfor_CSVFile();
}

void CMain_LoadFlow_Mng::LoadingScada( void )
{
	SetFLData_ACMLoading();
	SetFLData_ScadaCSVFile();
	SetFLData_GenValue();
}

int CMain_LoadFlow_Mng::LoadLFFInfor_CSVFile()
{
	if( m_vecVMLFdata.size() > 0 )
	{
		for_each( m_vecVMLFdata.begin(), m_vecVMLFdata.end(), PNOVR_EraseObjData() );
		m_vecVMLFdata.clear();
	}

	CUtil_FileParsing_CSV							CSVFile( _T("Scada_Data"), _T("lffdata.csv") );
	if( !CSVFile.Loading() )
	{
		return 0;
	}

	CVMLFData*			pLFData						= NULL;

	int										i( 0 ), nCsvFileCnt( 0 );
	wchar_t*			sepData						= NULL, _devider[ 5 ] = { _T(",") }, szCSVvalue[ 32 ] = { _T("") };
	wchar_t*			next;
	_tstring			szTokString( _T("") );
	for( nCsvFileCnt = 0 ; nCsvFileCnt < CSVFile.GetSize() ; nCsvFileCnt++ )
	{
		szTokString									= CSVFile.GetData( nCsvFileCnt + 1 );
		if( szTokString == _T("") )
		{
			continue ;
		}

		sepData										= wcstok_s( (wchar_t*)szTokString.c_str(), _devider ,&next);

		i											= 0;
		pLFData										= new CVMLFData;
		memset( pLFData, 0x00, sizeof( CVMLFData ) );
		while( sepData )
		{
			if( i == 0 )
			{
				swprintf_s( pLFData->m_szSSName, _T("%s"), sepData );
			} else if( i == 1 )
			{
				swprintf_s( pLFData->m_szDLName, _T("%s"), sepData );
			} else if( i == 2 )
			{
				swprintf_s( pLFData->m_szGENName, _T("%s"), sepData );
			} else if( i == 3 )
			{
				pLFData->m_nType					= _wtoi( sepData );
			} else if( i >= 4 && i <= 100 )
			{
				pLFData->m_dLoadValue[ i - 4 ]		= _wtof( sepData );
			}

			i										+= 1;
			sepData									= wcstok_s( NULL, _devider,&next);
		}
		m_vecVMLFdata.push_back( pLFData );
	}

	return 0;
}


void CMain_LoadFlow_Mng::SetFLData_ACMLoading()
{
	if( m_vecVMLFdata.size() > 0 )
	{
		for_each( m_vecVMLFdata.begin(), m_vecVMLFdata.end(), PNOVR_EraseObjData() );
		m_vecVMLFdata.clear();
	}

	wstring															szSSName( _T("") ), szDLName( _T("") ), szGENName( _T("") );
	vector<wstring>													vecSSString, vecDLString;
	vector<wstring>::iterator										_str_iter, _str_iter2;

	theDataMng->GetSSNames( &vecSSString );
	for( _str_iter = vecSSString.begin() ; _str_iter != vecSSString.end() ; ++_str_iter )
	{
		szSSName																	= (*_str_iter);

		vecDLString.clear();
		theDataMng->GetDLNames( szSSName, &vecDLString );
		for( _str_iter2 = vecDLString.begin() ; _str_iter2 != vecDLString.end() ; ++_str_iter2 )
		{
			szDLName																= (*_str_iter2);
			szGENName																= szDLName;

			CVMLFData*					pLFData										= new CVMLFData;
			swprintf_s( pLFData->m_szSSName, _T("%s"), szSSName.c_str() );
			swprintf_s( pLFData->m_szDLName, _T("%s"), szDLName.c_str() );
			swprintf_s( pLFData->m_szGENName, _T("%s"), szGENName.c_str() );
			pLFData->m_nType														= 1;
			m_vecVMLFdata.push_back( pLFData );
		}
	}

// 	int					i( 0 ), nIjIdx( 0 );
// 	for( i = 1 ; i <= (int)GETCOUNT( _T("gen_sta") ) ; i++ )
// 	{
// 		if( GETVALUE( int, _T("gen_sta"), _T("gen_type"), i ) == 3 )
// 		{
// 			nIjIdx																		= GETVALUE( int, _T("gen_sta"), _T("gen_ii_ij"), i );
// 			if( nIjIdx == 0 )															continue ;
// 
// 			szSSName																	= GETTEXT( _T("ss_sta"), _T("ss_nm"), GETVALUE( int, _T("mtr_sta"), _T("mtr_ii_ss"), GETVALUE( int, _T("dl_sta"), _T("dl_ii_mtr"), GETVALUE( int, _T("ij_sta"), _T("ij_ii_dl"), GETVALUE( int, _T("gen_sta"), _T("gen_ii_ij"), i ) ) ) ) );
// 			szDLName																	= GETTEXT( _T("dl_sta"), _T("dl_nm"), GETVALUE( int, _T("ij_sta"), _T("ij_ii_dl"), nIjIdx ) );
// 			szGENName																	= GETTEXT( _T("gen_sta"), _T("gen_nm"), i );
// 
// 			CVMLFData*					pLFData											= new CVMLFData;
// 			swprintf( pLFData->m_szSSName, _T("%s"), szSSName.c_str() );
// 			swprintf( pLFData->m_szDLName, _T("%s"), szDLName.c_str() );
// 			swprintf( pLFData->m_szGENName, _T("%s"), szGENName.c_str() );
// 			pLFData->m_nType															= 2;
// 			m_vecVMLFdata.push_back( pLFData );
// 		} else if( GETVALUE( int, _T("gen_sta"), _T("gen_type"), i ) == 1 )
// 		{
// 			szGENName																	= GETTEXT( _T("gen_sta"), _T("gen_nm"), i );
// 			CVMLFData*					pLFData											= new CVMLFData;
// 			swprintf( pLFData->m_szSSName, _T("%s"), szGENName.c_str() );
// 			swprintf( pLFData->m_szDLName, _T("%s"), szGENName.c_str() );
// 			swprintf( pLFData->m_szGENName, _T("%s"), szGENName.c_str() );
// 			pLFData->m_nType															= 3;
// 			m_vecVMLFdata.push_back( pLFData );
// 		}
// 	}
}

void CMain_LoadFlow_Mng::SetFLData_ScadaCSVFile()
{
	wstring				szSSname( _T("") ), szDLname( _T("") );
	double				dCurrent[ 24 ]				= { 0, }, dCalcuCurrent( 0.0 );
	CVMLFData*			pLFData						= NULL;

	wchar_t				szErrMsg[ 2048 ] = { 0, };
	int					i( 0 ), j( 0 ), nCsvFileCnt( 0 );
	wchar_t*			sepData						= NULL, _devider[ 5 ] = { _T(",") }, szCSVvalue[ 32 ] = { _T("") };
	wchar_t*			next;
	CUtil_FileParsing_CSV							CSVFile( m_szLoadProfilePath.GetBuffer() );
	if( !CSVFile.Loading() )
	{
		return ;
	}

	_tstring			szTokString( _T("") );
	for( nCsvFileCnt = 0 ; nCsvFileCnt < CSVFile.GetSize() ; nCsvFileCnt++ )
	{
		szTokString									= CSVFile.GetData( nCsvFileCnt + 1 );
		if( szTokString == _T("") )
		{
			continue ;
		}
		sepData										= wcstok_s( (wchar_t*)szTokString.c_str(), _devider ,&next);
		i											= 0;

		szSSname									= szDLname = _T("");
		memset( dCurrent, 0x00, sizeof( double ) * 24 );

		while( sepData )
		{
			if( i == 2 )
			{
				swprintf_s( szCSVvalue, _T("%s"), sepData );
				szSSname							= szCSVvalue;
			} else if( i == 3 )
			{
				swprintf_s( szCSVvalue, _T("%s"), sepData );
				szDLname							= szCSVvalue;
			} else if( i >= 6 && i <= 29 )
			{
				dCurrent[ i - 6 ]					= _wtof( sepData );
			}

			i										+= 1;
			sepData									= wcstok_s( NULL, _devider , &next);
		}

		pLFData										= GetLFData( szSSname, szDLname, szDLname, 1 );
		if( pLFData == NULL )
		{
			swprintf_s( szErrMsg, _T("Err : S/S(%s), D/L(%s) - Not Matched"), szSSname.c_str(), szDLname.c_str() );
			TRACE( szErrMsg );
			continue ;
		}

		for( j = 0 ; j < 23 ; j++ )
		{
			dCalcuCurrent							= dCurrent[ j + 1 ] - dCurrent[ j ];

			pLFData->m_dLoadValue[ j * 4 + 0 ]		= ( dCurrent[ j ] ) * 1000.0;
			pLFData->m_dLoadValue[ j * 4 + 1 ]		= ( dCurrent[ j ] + ( dCalcuCurrent * 0.25 ) ) * 1000.0;
			pLFData->m_dLoadValue[ j * 4 + 2 ]		= ( dCurrent[ j ] + ( dCalcuCurrent * 0.50 ) ) * 1000.0;
			pLFData->m_dLoadValue[ j * 4 + 3 ]		= ( dCurrent[ j ] + ( dCalcuCurrent * 0.75 ) ) * 1000.0;
		}
		dCalcuCurrent					= dCurrent[ 0 ] - dCurrent[ j ];
		pLFData->m_dLoadValue[ j * 4 + 0 ]			= ( dCurrent[ j ] ) * 1000.0;
		pLFData->m_dLoadValue[ j * 4 + 1 ]			= ( dCurrent[ j ] + ( dCalcuCurrent * 0.25 ) ) * 1000.0;
		pLFData->m_dLoadValue[ j * 4 + 2 ]			= ( dCurrent[ j ] + ( dCalcuCurrent * 0.50 ) ) * 1000.0;
		pLFData->m_dLoadValue[ j * 4 + 3 ]			= ( dCurrent[ j ] + ( dCalcuCurrent * 0.75 ) ) * 1000.0;
	}
}

void CMain_LoadFlow_Mng::SetFLData_GenValue()
{
	CVMLFData*			pLFData						= NULL;
	vector<CVMLFData*>::iterator			_iter;
	int										i( 0 );
	for( _iter = m_vecVMLFdata.begin() ; _iter != m_vecVMLFdata.end() ; ++_iter )
	{
		if( (*_iter)->m_nType == 1 )
		{
			continue ;
		} else if( (*_iter)->m_nType == 2 )
		{
			for( i = 0 ; i < 96 ; i++ )
			{
				(*_iter)->m_dLoadValue[ i ]			= 0.0;
			}
		} else if( (*_iter)->m_nType == 3 )
		{
			for( i = 0 ; i < 96 ; i++ )
			{
				(*_iter)->m_dLoadValue[ i ]			= 100.0 * 1000.0;
			}
		}
	}
}

CVMLFData* CMain_LoadFlow_Mng::GetLFData( wstring szSSName, wstring szDLName, wstring szGENName, int nType )
{
	CVMLFData*			pLFData				= NULL;
	vector<CVMLFData*>::iterator				_iter;
	for( _iter = m_vecVMLFdata.begin() ; _iter != m_vecVMLFdata.end() ; ++_iter )
	{
		if( (*_iter)->m_szSSName == szSSName && (*_iter)->m_szDLName == szDLName && (*_iter)->m_szGENName == szGENName && (*_iter)->m_nType == nType )
		{
			return (*_iter);
		}
	}
	return NULL;
}

void CMain_LoadFlow_Mng::Create_VMLFInfor()
{
	int					nTotalSize( GetClassSize() + ( (int)m_vecVMLFdata.size() * sizeof( CVMLFData ) ) );
	int					nGetDataPos( 0 );

	char*				pRtBuff															= new char[ nTotalSize ];
	memset( pRtBuff, 0x00, nTotalSize );

	memcpy( pRtBuff, &nTotalSize, GetClassSize() );
	nGetDataPos																			= GetClassSize();
	for( int i = 0 ; i < (int)m_vecVMLFdata.size() ; i++ )
	{
		memcpy( pRtBuff + nGetDataPos, m_vecVMLFdata[ i ], sizeof( CVMLFData ) );
		nGetDataPos																		+= sizeof( CVMLFData );
	}

	CreateVMemory_LFInfor( nTotalSize, pRtBuff );

	delete [] pRtBuff;
	pRtBuff																				= NULL;

	if( m_vecVMLFdata.size() > 0 )
	{
		for_each( m_vecVMLFdata.begin(), m_vecVMLFdata.end(), PNOVR_EraseObjData() );
		m_vecVMLFdata.clear();
	}
}

void CMain_LoadFlow_Mng::Loading_VMLFInfor()
{
	if( m_vecVMLFdata.size() > 0 )
	{
		for_each( m_vecVMLFdata.begin(), m_vecVMLFdata.end(), PNOVR_EraseObjData() );
		m_vecVMLFdata.clear();
	}

	unsigned int		nLFDataSize( 0 );
	char*				pRtBuff															= NULL;

	pRtBuff																				= LoadVMemory_LFInfor( nLFDataSize );

	int					i( 0 ), j( 0 ), nGetDataPos( 0 ), nDataCount( 0 );
	for( i = 0 ; i < (int)( nLFDataSize / sizeof( CVMLFData ) ); i++ )
	{
		CVMLFData*					pLFData										= new CVMLFData;
		memcpy( pLFData, pRtBuff + nGetDataPos, sizeof( CVMLFData ) );
		m_vecVMLFdata.push_back( pLFData );

		nGetDataPos																		+= sizeof( CVMLFData );
	}
	delete [] pRtBuff;
	pRtBuff																				= NULL;
}

// void CMain_LoadFlow_Mng::CSVWrite_LFFInfor()
// {
// 	int					i( 0 );
// 	char				setData[ 4096 ]						= { 0, };
// 	FILE*				pCSVfile							= NULL;
// 	wstring				szWidePath( thePNO_FRMmng->GetMyPath( _T("Scada_Data"), _T("lffdata.csv") ) );
// 	string				szAnsiPath( CW2A( szWidePath.c_str() ).m_psz );
// 	if( ( pCSVfile = fopen( szAnsiPath.c_str(), "w" ) ) == NULL )
// 	{
// 		TRACE( "파일이 다른 프로세서가 사용중이거나 존재하지 않습니다.(File : %s)", szWidePath.c_str() );
// 		return ;
// 	}
// 	fputs( "S/S,D/L,Dev_Name,Type,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96\n", pCSVfile );
// 
// 	for( i = 0 ; i < (int)( m_vecVMLFdata.size() ) ; i++ )
// 	{
// 		ZeroMemory( setData, sizeof( setData ) );
// 		sprintf( setData, "%s,%s,%s,%d", CW2A( m_vecVMLFdata[ i ]->m_szSSName ).m_psz, CW2A( m_vecVMLFdata[ i ]->m_szDLName ).m_psz, CW2A( m_vecVMLFdata[ i ]->m_szGENName ).m_psz, m_vecVMLFdata[ i ]->m_nType );
// 		fputs( setData, pCSVfile );
// 		CSVWrite_LFFInfor_Current( pCSVfile, m_vecVMLFdata[ i ]->m_dLoadValue );
// 		fputs( "\n", pCSVfile );
// 	}
// 
// 	if( pCSVfile )
// 	{
// 		fclose( pCSVfile );
// 	}
// }

void CMain_LoadFlow_Mng::CSVWrite_LFFInfor_Current( FILE* pCSVfile, double* fData )
{
	int					i( 0 );
	char				setData[ 4096 ] = { 0, };

	ZeroMemory( setData, sizeof( setData ) );
	for( i = 0 ; i < 96 ; i++ )
	{
		sprintf_s( setData,	",%.02f", fData[ i ] );
		fputs( setData, pCSVfile );
	}
}

void CMain_LoadFlow_Mng::SetLFFSeqTimeValue( int nValue )
{
	m_nLFFSeqValue										= nValue;
	m_nLFFSeqNow										= m_nLFFSeqValue;
}

int CMain_LoadFlow_Mng::CheckLFFSchedule()
{
	--m_nLFFSeqNow;

	if( m_nLFFSeqNow <= 0 )
	{
		SetDLNode_load();
		m_nLFFSeqNow									= m_nLFFSeqValue;
		if( m_nLFFSeqIndex >= 95 )
		{
			m_nLFFSeqIndex								= 0;
		} else{
			++m_nLFFSeqIndex;
		}

		return 0;
	}
	return 1;
}

void CMain_LoadFlow_Mng::SetDLNode_load()
{
	wstring				szSSName( _T("") ), szDLName( _T("") ), szDevName( _T("") );
	int					nType( 0 );
	double				dLoadValue( 0.0 );
	CVMLFData*			pVMLFdata						= NULL;

	int					i( 0 );
	for( i = 0 ; i < (int)m_vecVMLFdata.size() ; i++ )
	{
		pVMLFdata										= m_vecVMLFdata[ i ];

		if( pVMLFdata->m_nType == 1 )
		{
			SetDLNode_load_CB( pVMLFdata->m_szSSName, pVMLFdata->m_szDLName, pVMLFdata->m_dLoadValue[ m_nLFFSeqIndex ] );
		} else if( pVMLFdata->m_nType == 2 )
		{
			SetDLNode_load_DG( pVMLFdata->m_szGENName, pVMLFdata->m_dLoadValue[ m_nLFFSeqIndex ] );
		} else if( pVMLFdata->m_nType == 3 )
		{
			SetDLNode_load_GENa( pVMLFdata->m_szGENName, pVMLFdata->m_dLoadValue[ m_nLFFSeqIndex ] );
		}
	}
	SetDGBeforeSWinit();
}

void CMain_LoadFlow_Mng::SetDLNode_load_CB( wstring szSSName, wstring szDLName, double dLoad )
{
	int					nDLIdx( -1 ), i( 0 );
	wstring				szAcmSSName( _T("") ), szAcmDLName( _T("") );
	int					nDLCount = theAppDataMng->GetTableMaxCount(_T("dl_sta"));

	for( i = 1 ; i <= (int)nDLCount ; i ++ )
	{
		szAcmSSName										= GETSTRING( _T("ss_sta"), _T("ss_nm"), GETVALUE( int, _T("mtr_sta"), _T("mtr_ii_ss"), GETVALUE( int, _T("dl_sta"), _T("dl_ii_mtr"), i ) ) );
		szAcmDLName										= GETSTRING( _T("dl_sta"), _T("dl_nm"), i );

		if( szAcmSSName == szSSName && szAcmDLName == szDLName )
		{
			nDLIdx										= i;
			break ;
		}
	}
	if( nDLIdx == 0 )									return ;

	int					nIjIdx( GETVALUE( int, _T("dl_sta"), _T("dl_hi_ij"), nDLIdx ) ), nLdIdx( -1 );
	double				dTotalDIV( 0.0 ), d3pLoad( 0.0 ), dPF( 0.95 );

	if( nIjIdx == 0 )									return ;

	if( dLoad == 0.0 )
	{
		while( nIjIdx > 0 )
		{
			if( GETVALUE( int, _T("ij_sta"), _T("ij_ii_equty"), nIjIdx ) == 6 )
			{
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_3pmeamw"), nIjIdx, (double)0.0);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_3pmeamwqc"), nIjIdx, (double)1);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_3pmeamvar"), nIjIdx, (double)0.0);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_3pmeamvarqc"), nIjIdx, (double)1);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pameamw"), nIjIdx, (double)0.0);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pameamwqc"), nIjIdx, (double)1);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pameamvar"), nIjIdx, (double)0.0);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pameamvarqc"), nIjIdx, (double)1);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pbmeamw"), nIjIdx, (double)0.0);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pbmeamwqc"), nIjIdx, (double)1);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pbmeamvar"), nIjIdx, (double)0.0);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pbmeamvarqc"), nIjIdx, (double)1);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pcmeamw"), nIjIdx, (double)0.0);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pcmeamwqc"), nIjIdx, (double)1);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pcmeamvar"), nIjIdx, (double)0.0);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_pcmeamvarqc"), nIjIdx, (double)1);
				PUTDOUBLE2VALUE(_T("ij_dyn_mea"), _T("ij_meaflag"), nIjIdx, (double)0);
				SetDLNode_load_LDdynDLPO( nIjIdx );
			}
			nIjIdx											= GETVALUE( int, _T("ij_sta"), _T("ij_si_dl"), nIjIdx );
		}
	} else {
		// ld_div 총 가중치 합계
		while( nIjIdx > 0 )
		{
			if( GETVALUE( int, _T("ij_sta"), _T("ij_ii_equty"), nIjIdx ) == 6 )
			{
				nLdIdx										= GETVALUE( int, _T("ij_sta"), _T("ij_ii_equ"), nIjIdx );
				if( nLdIdx == 0 )							continue ;

				dTotalDIV									+= GETVALUE( double, _T("ld_sta"), _T("ld_div"), nLdIdx );
			}
			nIjIdx											= GETVALUE( int, _T("ij_sta"), _T("ij_si_dl"), nIjIdx );
		}

		nIjIdx												= GETVALUE( int, _T("dl_sta"), _T("dl_hi_ij"), nDLIdx );
		while( nIjIdx > 0 )
		{
			if( GETVALUE( int, _T("ij_sta"), _T("ij_ii_equty"), nIjIdx ) == 6 )
			{
				nLdIdx										= GETVALUE( int, _T("ij_sta"), _T("ij_ii_equ"), nIjIdx );
				if( nLdIdx == 0 )							continue ;

				d3pLoad										= ( GETVALUE( double, _T("ld_sta"), _T("ld_div"), nLdIdx ) / dTotalDIV ) * ( dLoad / 1000.0 );

				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamw")		, nIjIdx, (double)d3pLoad );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamwqc")	, nIjIdx, (double)1 );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_3pmeamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamvarqc")	, nIjIdx, (double)1 );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamw")		, nIjIdx, (double)( d3pLoad * 0.33333333 ) );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamwqc")	, nIjIdx, (double)1 );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pameamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamvarqc")	, nIjIdx, (double)1 );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamw")		, nIjIdx, (double)( d3pLoad * 0.33333333 ) );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamwqc")	, nIjIdx, (double)1 );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pbmeamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamvarqc")	, nIjIdx, (double)1 );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamw")		, nIjIdx, (double)( d3pLoad * 0.33333333 ) );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamwqc")	, nIjIdx, (double)1 );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pcmeamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamvarqc")	, nIjIdx, (double)1 );
				PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_meaflag")		, nIjIdx, (double)0 );

				SetDLNode_load_LDdynDLPO( nIjIdx );
			}
			nIjIdx											= GETVALUE( int, _T("ij_sta"), _T("ij_si_dl"), nIjIdx );
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMain_LoadFlow_Mng::SetDGBeforeSWinit()
{
	int					i( 0 ), nIjIdx( 0 );
	int					nGndIdx( 0 ), nCBSWIdx( 0 ), nGbrIdx( 0 );
	int					nGenCount = theAppDataMng->GetTableRealCount(_T("gen_sta"));
	m_vecIJIDXs.clear();

	for( i = 1 ; i <= (int)nGenCount; i++ )
		{
		if( GETVALUE( int, _T("gen_sta"), _T("gen_type"), i ) == 2 || GETVALUE( int, _T("gen_sta"), _T("gen_type"), i ) == 3 )
		{
			nIjIdx											= GETVALUE( int, _T("gen_sta"), _T("gen_ii_ij"), i );
			if( nIjIdx == 0 )								continue ;
			nGndIdx											= GETVALUE( int, _T("ij_sta"), _T("ij_ii_gnd"), nIjIdx );
			if( nGndIdx == 0 )								continue ;

			if( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nGndIdx ) > 0 )
			{
				nGbrIdx										= GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nGndIdx );
			} else if( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nGndIdx ) > 0 )
			{
				nGbrIdx										= GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nGndIdx );
			}

			if( nGndIdx > 0 )
			{
				GetDowntreeGND( nGndIdx, 0 );
			}
		}
	}

	sort( m_vecIJIDXs.begin(), m_vecIJIDXs.end() );
	vector<int>::iterator					IJIndexUni		= unique( m_vecIJIDXs.begin(), m_vecIJIDXs.end() );
	if( IJIndexUni != m_vecIJIDXs.end() )
	{
		m_vecIJIDXs.erase( IJIndexUni, m_vecIJIDXs.end() );
	}


	if( m_vecIJIDXs.size() > 0 )
	{
		for( i = 0 ; i < (int)m_vecIJIDXs.size() ; i++ )
		{
			nIjIdx											= m_vecIJIDXs[ i ];
			if( nIjIdx < 1 )								continue ;

			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamw"), nIjIdx, (double)0.0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamwqc"), nIjIdx, (double)0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamvar"), nIjIdx, (double)0.0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamvarqc"), nIjIdx, (double)0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamw"), nIjIdx, (double)0.0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamwqc"), nIjIdx, (double)0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamvar"), nIjIdx, (double)0.0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamvarqc"), nIjIdx, (double)0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamw"), nIjIdx, (double)0.0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamwqc"), nIjIdx, (double)0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamvar"), nIjIdx, (double)0.0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamvarqc"), nIjIdx, (double)0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamw"), nIjIdx, (double)0.0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamwqc"), nIjIdx, (double)0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamvar"), nIjIdx, (double)0.0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamvarqc"), nIjIdx, (double)0 );
			PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_meaflag"), nIjIdx, (double)0 );
		}
	}
}

BOOL CMain_LoadFlow_Mng::AddInitIJIdx( int nGNDIdx )
{
	int					nIjIdx( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_ij"), nGNDIdx ) );

	vector<int>::iterator		_finditer			= find( m_vecIJIDXs.begin(), m_vecIJIDXs.end(), nIjIdx );
	if( _finditer != m_vecIJIDXs.end() )											return FALSE;

	if( nIjIdx > 0 )
	{
		while( nIjIdx > 0 )
		{
			if( GETVALUE( int, _T("ij_sta"), _T("ij_ii_equty"), nIjIdx ) == 6 )
			{
				m_vecIJIDXs.push_back( nIjIdx );
			}

			nIjIdx									= GETVALUE( int, _T("ij_sta"), _T("ij_si_gnd"), nIjIdx );
		}
	}

	return TRUE;
}

void CMain_LoadFlow_Mng::GetDowntreeGND( int nGNDIdx, int nGBRIdx )
{
	if( !AddInitIJIdx( nGNDIdx ) )
	{
		TRACE( _T("GetDowntreeCBSWs. Loop Check.\n") );
		return ;
	}

	int					nCBSWIdx( 1 ), nTISWIdx( 1 );

	// cbsw
	if( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx ) > 0 )
	{
		nCBSWIdx									= GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx );
		while( nCBSWIdx > 0 )
		{
			//
			GetDowntreeCBSWs( nGNDIdx, nCBSWIdx );
			//
			nCBSWIdx								= GETVALUE( int, _T("cbsw_sta"), _T("cbsw_si_fgnd"), nCBSWIdx );
		}
	}
	if( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx ) > 0 )
	{
		nCBSWIdx									= GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx );
		while( nCBSWIdx > 0 )
		{
			//
			GetDowntreeCBSWs( nGNDIdx, nCBSWIdx );
			//
			nCBSWIdx								= GETVALUE( int, _T("cbsw_sta"), _T("cbsw_si_tgnd"), nCBSWIdx );
		}
	}

	// tisw
	if( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx ) > 0 )
	{
		nTISWIdx									= GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx );
		while( nTISWIdx > 0 )
		{
			//
			GetDowntreeTISWs( nGNDIdx, nTISWIdx );
			//
			nTISWIdx								= GETVALUE( int, _T("tisw_sta"), _T("tisw_si_fgnd"), nTISWIdx );
		}
	}
	if( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx ) > 0 )
	{
		nTISWIdx									= GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx );
		while( nTISWIdx > 0 )
		{
			//
			GetDowntreeTISWs( nGNDIdx, nTISWIdx );
			//
			nTISWIdx								= GETVALUE( int, _T("tisw_sta"), _T("tisw_si_tgnd"), nTISWIdx );
		}
	}

	// gbr은 의미 없음
	int					nNextGbrIdx( 0 );
	if( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nGNDIdx ) > 0 && GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nGNDIdx ) != nGBRIdx )
	{
		nNextGbrIdx									= GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nGNDIdx );
	}
	GetDowntreeGBRs( nGNDIdx, nNextGbrIdx );

	if( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nGNDIdx ) > 0 && GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nGNDIdx ) != nGBRIdx )
	{
		nNextGbrIdx									= GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nGNDIdx );
	}
	GetDowntreeGBRs( nGNDIdx, nNextGbrIdx );
}

void CMain_LoadFlow_Mng::GetDowntreeGBRs( int nGNDIdx, int nNextGbrIdx )
{
	int					nNextGndIdx( 0 );

	while( nNextGbrIdx > 0 )
	{
		nNextGndIdx								= 0;
		if( GETVALUE( int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nNextGbrIdx ) == nGNDIdx )
		{
			nNextGndIdx							= GETVALUE( int, _T("gbr_sta"), _T("gbr_ii_tgnd"), nNextGbrIdx );
		} else if( GETVALUE( int, _T("gbr_sta"), _T("gbr_ii_tgnd"), nNextGbrIdx ) == nGNDIdx )
		{
			nNextGndIdx							= GETVALUE( int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nNextGbrIdx );
		}
		if( nNextGndIdx > 0 )
		{
			GetDowntreeGND( nNextGndIdx, nNextGbrIdx );
		}
		nNextGbrIdx								= GETVALUE( int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGbrIdx );
	}
}

void CMain_LoadFlow_Mng::GetDowntreeCBSWs( int nGNDIdx, int nCBSWIdx )
{
	int							nNextGndIdx( 0 );

	if( GETVALUE( int, _T("cbsw_sta"), _T("cbsw_type"), nCBSWIdx ) > 0 && GETVALUE( int, _T("cbsw_sta"), _T("cbsw_type"), nCBSWIdx ) < 4 )
	{
		return ;
	}
	if( GETVALUE( int, _T("cbsw_dyn_mea"), _T("cbsw_nwstat"), nCBSWIdx ) == 0 )
	{
		return ;
	}

	if( GETVALUE( int, _T("cbsw_sta"), _T("cbsw_ii_fgnd"), nCBSWIdx ) == nGNDIdx )
	{
		nNextGndIdx									= GETVALUE( int, _T("cbsw_sta"), _T("cbsw_ii_tgnd"), nCBSWIdx );
	} else if( GETVALUE( int, _T("cbsw_sta"), _T("cbsw_ii_tgnd"), nCBSWIdx ) == nGNDIdx )
	{
		nNextGndIdx									= GETVALUE( int, _T("cbsw_sta"), _T("cbsw_ii_fgnd"), nCBSWIdx );
	}
	if( nNextGndIdx == 0 )							return ;


	// gnd 처리

	GetDowntreeGND( nNextGndIdx, 0 );
}

void CMain_LoadFlow_Mng::GetDowntreeTISWs( int nGNDIdx, int nTISWIdx )
{
	int							nNextGndIdx( 0 );

	if( GETVALUE( int, _T("tisw_sta"), _T("tisw_type"), nTISWIdx ) > 0 && GETVALUE( int, _T("tisw_sta"), _T("tisw_type"), nTISWIdx ) < 4 )
	{
		return ;
	}
	if( GETVALUE( int, _T("tisw_dyn_mea"), _T("tisw_nwstat"), nTISWIdx ) == 0 )
	{
		return ;
	}

	if( GETVALUE( int, _T("tisw_sta"), _T("tisw_ii_fgnd"), nTISWIdx ) == nGNDIdx )
	{
		nNextGndIdx									= GETVALUE( int, _T("tisw_sta"), _T("tisw_ii_tgnd"), nTISWIdx );
	} else if( GETVALUE( int, _T("tisw_sta"), _T("tisw_ii_tgnd"), nTISWIdx ) == nGNDIdx )
	{
		nNextGndIdx									= GETVALUE( int, _T("tisw_sta"), _T("tisw_ii_fgnd"), nTISWIdx );
	}
	if( nNextGndIdx == 0 )							return ;

	GetDowntreeGND( nNextGndIdx, 0 );
}



//--

void CMain_LoadFlow_Mng::SetDLNode_load_DG( wstring szGenName, double dLoad )
{
	int					nGenIdx( -1 ), i( 0 );
	wstring				szAcmGenName( _T("") );
	int					nGenCount = theAppDataMng->GetTableRealCount(_T("gen_sta"));

	for( i = 1 ; i <= (int)nGenCount; i++ )
	{
		szAcmGenName															= GETSTRING( _T("gen_sta"), _T("gen_nm"), i );

		if( szAcmGenName == szGenName )
		{
			nGenIdx																= i;
			break ;
		}
	}

	if( nGenIdx == 0 )															return ;
	int					nIjIdx( GETVALUE( int, _T("gen_sta"), _T("gen_ii_ij"), nGenIdx ) ), nLdIdx( -1 );
	double				d3pLoad( 0.0 ), dPF( 0.95 );

	if( nIjIdx == 0 )															return ;
	d3pLoad																		= ( dLoad / 1000.0 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamw")		, nIjIdx, (double)d3pLoad );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamwqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_3pmeamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamvarqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamw")		, nIjIdx, (double)( d3pLoad * 0.33333333 ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamwqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pameamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamvarqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamw")		, nIjIdx, (double)( d3pLoad * 0.33333333 ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamwqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pbmeamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamvarqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamw")		, nIjIdx, (double)( d3pLoad * 0.33333333 ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamwqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pcmeamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamvarqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_meaflag")		, nIjIdx, (double)0 );
}

void CMain_LoadFlow_Mng::SetDLNode_load_GENa( wstring szGenName, double dLoad )
{
	int					nGenIdx( -1 ), i( 0 );
	wstring				szAcmGenName( _T("") );
	int					nGenCount = theAppDataMng->GetTableRealCount(_T("gen_sta"));

	for( i = 1 ; i <= (int)nGenCount; i++ )
	{
		szAcmGenName															= GETSTRING( _T("gen_sta"), _T("gen_nm"), i );

		if( szAcmGenName == szGenName )
		{
			nGenIdx																= i;
			break ;
		}
	}

	if( nGenIdx == -1 )															return ;
	int					nIjIdx( GETVALUE( int, _T("gen_sta"), _T("gen_ii_ij"), nGenIdx ) ), nLdIdx( -1 );
	double				d3pLoad( 0.0 ), dPF( 0.95 );

	if( nIjIdx == -1 )															return ;
	d3pLoad																		= ( dLoad / 1000.0 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamw")		, nIjIdx, (double)d3pLoad );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamwqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_3pmeamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_3pmeamvarqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamw")		, nIjIdx, (double)( d3pLoad * 0.33333333 ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamwqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pameamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pameamvarqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamw")		, nIjIdx, (double)( d3pLoad * 0.33333333 ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamwqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pbmeamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pbmeamvarqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamw")		, nIjIdx, (double)( d3pLoad * 0.33333333 ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamwqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamvar")	, nIjIdx, (double)( sin( m_dPFRadial ) * ( GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pcmeamw"), nIjIdx ) / cos( m_dPFRadial ) ) ) );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_pcmeamvarqc")	, nIjIdx, (double)1 );
	PUTDOUBLE2VALUE( _T("ij_dyn_mea"), _T("ij_meaflag")		, nIjIdx, (double)0 );
}

void CMain_LoadFlow_Mng::SetDLNode_load_LDdynDLPO( int nIjIdx )
{
	if( GETVALUE( int, _T("ij_sta"), _T("ij_ii_equ"), nIjIdx ) == 0 )								return ;

	int					nLDIdx( GETVALUE( int, _T("ij_sta"), _T("ij_ii_equ"), nIjIdx ) );

	CTime				_timer													= CTime::GetCurrentTime();
	wchar_t				szTime[ 32 ] = { 0, };
	swprintf_s( szTime, _T("%s"), _timer.Format( _T("%Y-%m-%d %H:%M:%S") ) );
	PUTDOUBLE2VALUE_AT( _T("ld_dyn_dlpo"), _T("ld_3pwdrecent"), nLDIdx, m_nLFFSeqIndex, GETVALUE( double, _T("ij_dyn_mea"), _T("ij_3pmeamw"), nIjIdx ) );
	PUTDOUBLE2VALUE_AT( _T("ld_dyn_dlpo"), _T("ld_3pwdrecent"), nLDIdx, m_nLFFSeqIndex, GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pameamw"), nIjIdx ) );
	PUTDOUBLE2VALUE_AT( _T("ld_dyn_dlpo"), _T("ld_3pwdrecent"), nLDIdx, m_nLFFSeqIndex, GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pbmeamw"), nIjIdx ) );
	PUTDOUBLE2VALUE_AT( _T("ld_dyn_dlpo"), _T("ld_3pwdrecent"), nLDIdx, m_nLFFSeqIndex, GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pcmeamw"), nIjIdx ) );
	PUTDOUBLE2VALUE_AT( _T("ld_dyn_dlpo"), _T("ld_3qwdrecent"), nLDIdx, m_nLFFSeqIndex, GETVALUE( double, _T("ij_dyn_mea"), _T("ij_3pmeamvar"), nIjIdx ) );
	PUTDOUBLE2VALUE_AT( _T("ld_dyn_dlpo"), _T("ld_3qwdrecent"), nLDIdx, m_nLFFSeqIndex, GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pameamvar"), nIjIdx ) );
	PUTDOUBLE2VALUE_AT( _T("ld_dyn_dlpo"), _T("ld_3qwdrecent"), nLDIdx, m_nLFFSeqIndex, GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pbmeamvar"), nIjIdx ) );
	PUTDOUBLE2VALUE_AT( _T("ld_dyn_dlpo"), _T("ld_3qwdrecent"), nLDIdx, m_nLFFSeqIndex, GETVALUE( double, _T("ij_dyn_mea"), _T("ij_pcmeamvar"), nIjIdx ) );
}


//////////////////////////////////////////////////////////////////////////
// mem set 추가
//////////////////////////////////////////////////////////////////////////

int CMain_LoadFlow_Mng::GetClassSize()
{
	return CLASSSIZEBUFF_SIZE;
}

void CMain_LoadFlow_Mng::CreateVMemory_LFInfor( int nSIze, char* pDataBuff )
{
	if( m_hLFInfor != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_hLFInfor );
	}
	if( m_pLFInfor != NULL )
	{
		UnmapViewOfFile( m_pLFInfor );
	}

	m_hLFInfor													= CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, nSIze, LFINFOR_VMNAME );
	if( m_hLFInfor == NULL || m_hLFInfor == INVALID_HANDLE_VALUE )
	{
		return ;
	}

	m_pLFInfor													= MapViewOfFile( m_hLFInfor, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, nSIze );
	if( m_pLFInfor == NULL )
	{
		CloseHandle( m_hLFInfor );
		return ;
	}

	memcpy( m_pLFInfor, pDataBuff, nSIze );
}

char* CMain_LoadFlow_Mng::LoadVMemory_LFInfor( unsigned int &nSize )
{
	HANDLE								hVMFile = INVALID_HANDLE_VALUE;
	LPVOID								pVMDATA = NULL;
	LONGLONG							nTempDataSize( 0 );
	unsigned int						nGetDataPos( 0 );
	char*								pSVDataBuff = NULL, *pGetDataBuff = NULL;

	hVMFile														= OpenFileMapping( FILE_MAP_READ, FALSE, LFINFOR_VMNAME );

	if( hVMFile == NULL || hVMFile == INVALID_HANDLE_VALUE )
	{
		TRACE( _T("Err : Load Flow File Data LoadVMemory OpenFileMapping Fail.\n") );
		return NULL;
	}
	pVMDATA														= MapViewOfFile( hVMFile, FILE_MAP_READ, 0, 0, 0 );
	if( pVMDATA == NULL )
	{
		TRACE( _T("Err : Load Flow File Data LoadVMemory MapViewOfFile Fail.\n") );
		if( hVMFile )
		{
			CloseHandle( hVMFile );
		}
		return NULL;
	}

	nGetDataPos													= CLASSSIZEBUFF_SIZE;
	memcpy( &nTempDataSize, pVMDATA, CLASSSIZEBUFF_SIZE );
	nSize														= (unsigned int)nTempDataSize;

	pSVDataBuff													= (char*)pVMDATA;
	pGetDataBuff												= new char[ nSize - CLASSSIZEBUFF_SIZE ];
	memcpy( pGetDataBuff, pSVDataBuff + CLASSSIZEBUFF_SIZE, nSize - CLASSSIZEBUFF_SIZE );

	UnmapViewOfFile( pVMDATA );
	CloseHandle( hVMFile );

	nSize														-= CLASSSIZEBUFF_SIZE;

	return pGetDataBuff;
}

void CMain_LoadFlow_Mng::WriteVMemory_LFInfor( int nSIze, char* pDataBuff )
{
	HANDLE								hVMFile					= OpenFileMapping( FILE_MAP_WRITE, FALSE, LFINFOR_VMNAME );
	if( hVMFile == NULL || hVMFile == INVALID_HANDLE_VALUE )
	{
		TRACE( _T("Err : Load Flow File Data WriteVMemory OpenFileMapping Fail.\n") );
		return ;
	}
	LPVOID								pVMDATA					= MapViewOfFile( hVMFile, FILE_MAP_WRITE, 0, 0, nSIze );
	if( pVMDATA == NULL )
	{
		TRACE( _T("Err : Load Flow File Data WriteVMemory MapViewOfFile Fail.\n") );
		CloseHandle( hVMFile );
		return ;
	}

	memcpy( pVMDATA, pDataBuff, nSIze );

	UnmapViewOfFile( pVMDATA );
	CloseHandle( hVMFile );
}

//////////////////////////////////////////////////////////////////////////
// Application Run Thread
//////////////////////////////////////////////////////////////////////////

void CMain_LoadFlow_Mng::Start_LoadFlow()
{
	if( !m_bThread_LFAPPL )
	{
		ThreadRun_LFAppl();
	}
}

void CMain_LoadFlow_Mng::Stop_LoadFlow()
{
	CloseThread();
	SetLoadFlowEditorMSG( 1, 2 );
	m_nLFFSeqNow																				= 0;
}


void CMain_LoadFlow_Mng::ThreadRun_LFAppl()
{
	SENDLOGMSG( _T("Load Flow Application Ready."), RGB( 225, 16, 225 ) );
	if( !IsLFApplReady() )
	{
		SENDLOGMSG( _T("Load Flow Application File Not Find."), RGB( 225, 16, 16 ) );
		return ;
	}
	SENDLOGMSG( _T("Load Flow Application Find... Success"), RGB( 16, 128, 16 ) );

	UINT											uiThreadId( 0 );
	m_hThread_LFAPPL																			= (HANDLE)_beginthreadex( NULL, 0, LFAppl_Process, this, CREATE_SUSPENDED, &uiThreadId );
	if( m_hThread_LFAPPL == NULL )
	{
		return ;
	}
	ResumeThread( m_hThread_LFAPPL );
}

UINT WINAPI CMain_LoadFlow_Mng::LFAppl_Process( LPVOID pParam )
{
	CMain_LoadFlow_Mng*								pLFMng										= (CMain_LoadFlow_Mng*)pParam;
	if( pLFMng == NULL )																		return 1L;
	pLFMng->SetThread_LFAppl( true );

	while( pLFMng->GetThread_LFAppl() )
	{
		if( pLFMng->CheckLFFSchedule() == 0 )
		{
			TRACE( _T("Run BGP Application."), RGB( 16, 128, 16 ) );
			if( pLFMng->RunProcess_LFAppl() )
			{
				pLFMng->SetLoadFlowEditorMSG( 1, 1 );
			}
		}
		Sleep( 10000 );			// 10초 마다 확인. 30번. 즉 5분후에 재가동
	}

	return 1L;
}

bool CMain_LoadFlow_Mng::IsLFApplReady()
{
	if( m_szLFFExeFileName == _T("") )
	{
		return false;
	}

	wchar_t											szExePath[ MAX_PATH ]					= { 0x00, };
	wchar_t											szLogMsg[ 512 ]							= { 0x00, };
	swprintf_s( szExePath, _T("%s"), thePNO_UTILmng->GetMyPath( m_szLFFExeFileName.GetBuffer(), _T("") ).c_str() );
	if( _waccess( szExePath, 06 ) == -1 )
	{
		swprintf_s( szLogMsg, _T("* Err : Application File Not Found.(Path = %s)"), szExePath );
		SENDLOGMSG( szLogMsg, RGB( 225, 122, 87 ) );
		return false;
	}
	return true;
}

bool CMain_LoadFlow_Mng::RunProcess_LFAppl()
{
	if( m_nLFSM_Index == 0 || m_nLFSM_CaseId == 0 )
	{
		return false;
	}

	if( m_szLFFExeFileName == _T("") )
	{
		return false;
	}

//	_tstring										szApplName( _T("BGP_App") );
	_tstring										szFilePath( thePNO_UTILmng->GetMyPath( _T(""), _T("") ) );
	wchar_t											szExePath[ MAX_PATH ]					= { 0x00, };
	wchar_t											szLogMsg[ 512 ]							= { 0x00, };

	// Process 삭제
	wchar_t											szApplFileName[ MAX_PATH ]				= { 0x00, };
	swprintf_s( szApplFileName, _T("%s"), m_szLFFExeFileName );
	thePNO_UTILmng->KillProcess( szApplFileName );

	// Process Run
	swprintf_s( szExePath, _T("%s%s"), szFilePath.c_str(), m_szLFFExeFileName );
	if( _waccess( szExePath, 06 ) == -1 )
	{
		swprintf_s( szLogMsg, _T("* Err : Application File Not Found.(Path = %s)"), szExePath );
		SENDLOGMSG( szLogMsg, RGB( 225, 122, 87 ) );
		return false;
	}

	/*wchar_t											szParameter[ MAX_PATH ]					= { 0x00, };
	swprintf( szParameter, _T("%s %d %d 2"), ACMDBNAME_SIMULBASE, m_nLFSM_Index, m_nLFSM_CaseId );
	if( !ShellExecute( NULL, _T("open"), szExePath, szParameter, szFilePath.c_str(), SW_SHOW ) )
	{
		TRACE( _T("* Err : Application Not Execution.(Path = %s, AppExe = %s)"), szFilePath.c_str(), szExePath );
		return false;
	}*/
	return true;
}

void CMain_LoadFlow_Mng::SetLFFExeFileName( CString szFileName )
{
	m_szLFFExeFileName																			= szFileName;
}

void CMain_LoadFlow_Mng::SetLoadFlowWnd( CWnd* pLoadFlowWnd )
{
	m_pLoadFlowEditor																			= pLoadFlowWnd;
}

void CMain_LoadFlow_Mng::SetLoadFlowEditorMSG( int nWPvalue, int nLPvalue )
{
	if( m_pLoadFlowEditor )
	{
		m_pLoadFlowEditor->SendMessage( SENDMSG_LOADFLOW, (WPARAM)nWPvalue, (LPARAM)nLPvalue );
	}
}