#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 클래스입니다.
#include <afxodlgs.h>       // MFC OLE 대화 상자 클래스입니다.
#include <afxdisp.h>        // MFC 자동화 클래스입니다.
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 데이터베이스 클래스입니다.
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO 데이터베이스 클래스입니다.
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <list>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <hash_map>
#include <hash_set>
#include <assert.h>
using namespace std;

//#include "../Include/CommonVerFile.h"

#ifdef _APPGOVERNOR_COM_VER_
#include "../PUSDT_PCommManager/CommonFile.h"
#include "../PUSDT_PCommManager/PSM_Util.h"
#else
#include "../include/PUSDT_PCommManager/CommonFile.h"
#include "../include/PUSDT_PCommManager/PSM_Util.h"
#endif

#ifdef _DEBUG
	#ifdef _APPGOVERNOR_COM_VER_
		#pragma comment( lib, "../Bin/x64/Debug/PUSDT_PCommManager.lib" )
	#else
		#pragma comment( lib, "../Lib/x64/Debug/PUSDT_PCommManager.lib" )
	#endif
#else
	#ifdef _APPGOVERNOR_COM_VER_
		#pragma comment( lib, "../Bin/x64/Release/PUSDT_PCommManager.lib" )
	#else
		#pragma comment( lib, "../Lib/x64/Release/PUSDT_PCommManager.lib" )
	#endif
#endif
