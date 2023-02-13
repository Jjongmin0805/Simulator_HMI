#pragma once

#include "WorkPackagerV3_h.h"

class AFX_EXT_CLASS CAppDRMObjMng
{
public:
	static CAppDRMObjMng*																		InitInstance( void );
	static void																					Close( void );

protected:
	static CAppDRMObjMng*			m_pMngData;

//------------------------------------------------------------------------------------------------

public:
	CAppDRMObjMng( void );
	~CAppDRMObjMng( void );
	void																						SetLocalTest( bool bIsLocalTest );
	bool																						IsDRMConnectSuccess( void );
	HRESULT																						Initialization( void );
	int																							DoConversion( wchar_t *szSourcePath, wchar_t *szTargetPath );

protected:
	IWorkPackagerADK				*m_pPackager;
	bool							m_bLocalTest;
};

#define								theDRMMng													CAppDRMObjMng::InitInstance()
#define								theDRMConv_Init												theDRMMng->Initialization()
#define								theDRMConv_TestMode											theDRMMng->SetLocalTest( true )
#define								theDRMConv( a, b )											theDRMMng->DoConversion( a, b )