#include "pch.h"
#include "AppDRMObjMng.h"


#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}
MIDL_DEFINE_GUID( IID, IID_IWorkPackagerADK, 0xE5BA754C, 0xED4C, 0x4E88, 0xBD, 0x57, 0x0B, 0x80, 0x1C, 0x4C, 0x20, 0x98 );
MIDL_DEFINE_GUID( CLSID, CLSID_WorkPackagerADK, 0xA1F07262, 0xDF30, 0x4E93, 0x9E, 0x93, 0x63, 0xA3, 0xD5, 0x0C, 0x99, 0x1F );


CAppDRMObjMng* CAppDRMObjMng::m_pMngData														= 0x00;

CAppDRMObjMng* CAppDRMObjMng::InitInstance( void )
{
	if( CAppDRMObjMng::m_pMngData == 0x00 )
	{
		CAppDRMObjMng::m_pMngData																= new CAppDRMObjMng;
	}

	return CAppDRMObjMng::m_pMngData;
}

void CAppDRMObjMng::Close( void )
{
	if( CAppDRMObjMng::m_pMngData )
	{
		delete CAppDRMObjMng::m_pMngData;
		CAppDRMObjMng::m_pMngData																= 0x00;
	}
}

//------------------------------------------------------------------------------------------------

CAppDRMObjMng::CAppDRMObjMng( void ) : m_bLocalTest( false )
{
	m_pPackager																					= NULL;
}

CAppDRMObjMng::~CAppDRMObjMng( void )
{
	if( m_pPackager )
	{
		m_pPackager->Release();
	}
}

void CAppDRMObjMng::SetLocalTest( bool bIsLocalTest )
{
	m_bLocalTest																				= bIsLocalTest;
}

bool CAppDRMObjMng::IsDRMConnectSuccess( void )
{
	return ( m_pPackager == NULL ) ? false : true;
}

HRESULT CAppDRMObjMng::Initialization( void )
{
	HRESULT							hr( S_OK );
	if( ( hr = CoCreateInstance( CLSID_WorkPackagerADK, NULL, CLSCTX_INPROC_SERVER, IID_IWorkPackagerADK, ( LPVOID * )&m_pPackager ) ) != S_OK )
	{
		if( hr == 0x800401f0 )
		{
			CoInitialize( NULL );
		}
		if( ( hr = CoCreateInstance( CLSID_WorkPackagerADK, NULL, CLSCTX_INPROC_SERVER, IID_IWorkPackagerADK, ( LPVOID * )&m_pPackager ) ) != S_OK )
		{
			LOGOUT( "* Err : DRM Create Instance.( Ret : 0x%X )", hr );
			return hr;
		}
	}

	return hr;
}

int CAppDRMObjMng::DoConversion( wchar_t *szSourcePath, wchar_t *szTargetPath )
{
	int								nRet( 0 );
	if( m_pPackager == NULL )
	{
		LOGOUT( "* Err : Initialization was not successful." );
		return nRet;
	}

	HRESULT							hr( 0 );
	CPString						szDRMFSDHomeDir( theUtil->GetMyPath( "DRM", "fsdinit" ) );
	szDRMFSDHomeDir.MakeWideValue();
	BSTR							szDRM_HomeDir												= SysAllocString( szDRMFSDHomeDir.GetWideValue() );
	szDRMFSDHomeDir.Release();

	BSTR							szDRM_SourceFile											= SysAllocString( szSourcePath );
	BSTR							szDRM_TargetFile											= SysAllocString( szTargetPath );
	short							snRet_FileType( 0 );
	if( ( hr = m_pPackager->GetFileType( szDRM_SourceFile, &snRet_FileType ) ) != S_OK )
	{
		LOGOUT( "* Err : DRM File Checke.( File Type : %d, Path : %s )", hr, CPString( szSourcePath ).GetValue() );
		SysFreeString( szDRM_SourceFile );
		SysFreeString( szDRM_TargetFile );
		return nRet;
	}
	LOGOUT("* DRM : GetFileType [ %d ]", snRet_FileType);
	nRet																						= snRet_FileType;
	if( snRet_FileType != 103 )
	{
		LOGOUT( "* Err : 해당되는 암호화 파일이 아닙니다.( File Type : %d )", snRet_FileType );
		SysFreeString( szDRM_SourceFile );
		SysFreeString( szDRM_TargetFile );
		return nRet;
	}

	BSTR							szFileHeader;
	CPString						szDRM_FileHeader, szDRM_ServerID;
	if( ( hr = m_pPackager->GetFileHeader( szDRM_SourceFile, &szFileHeader ) ) != S_OK )
	{
		szDRM_ServerID																			= "0100000000001564";
	} else
	{
		USES_CONVERSION;
		szDRM_FileHeader																		= OLE2A( szFileHeader );
		szDRM_FileHeader.SetTok_Parse( ";", false );

		if( szDRM_FileHeader.GetTok_Count() > 16 )
		{
			szDRM_ServerID																		= szDRM_FileHeader.GetTok_At( szDRM_FileHeader.GetTok_Count() - 1 );
			LOGOUT("* DRM : ServerID [ %s ]", szDRM_ServerID);
			if( szDRM_ServerID != "0100000000001564" )
			{
				szDRM_ServerID																	= "0100000000001564";
			}
		}
	}

	szDRM_ServerID.MakeWideValue();
	BSTR							szDRM_ServerIDFsn											= SysAllocString( szDRM_ServerID.GetWideValue() );

	if( m_bLocalTest )
	{
		if( ( hr = m_pPackager->DoExtract( szDRM_HomeDir, szDRM_ServerIDFsn, szDRM_SourceFile, szDRM_TargetFile ) ) != S_OK )
		{
			LOGOUT( "* Err : Do DRM Extract failed. [ %d ]", hr );
			return -1;
		}
	} else {
		BSTR						szDRM_Purpose												= SysAllocString( L"VIEW" );
		if( ( hr = m_pPackager->DoExtract_c( szDRM_HomeDir, szDRM_ServerIDFsn, szDRM_SourceFile, szDRM_TargetFile, szDRM_Purpose ) ) != S_OK )
		{
			LOGOUT( "* Err : Do DRM Extract_c failed. [ %d ]", hr );
			SysFreeString( szDRM_Purpose );
			return -1;
		}
		SysFreeString( szDRM_Purpose );
	}

	szDRM_FileHeader.Release();
	szDRM_ServerID.Release();

	SysFreeString( szDRM_SourceFile );
	SysFreeString( szDRM_TargetFile );
	SysFreeString( szDRM_ServerIDFsn );

	CPString						szLogOut_SourFile( szSourcePath );
	CPString						szLogOut_TargFile( szTargetPath );
	LOGOUT( "DRM-File Conversion : [%s] -> [%s]", szLogOut_SourFile.GetValue(), szLogOut_TargFile.GetValue() );

	return nRet;
}
