#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 클래스입니다.
#include <afxodlgs.h>       // MFC OLE 대화 상자 클래스입니다.
#include <afxdisp.h>        // MFC 자동화 클래스입니다.
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 데이터베이스 클래스입니다.
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원


#include "Frame_MenuBar_Ctrl.h"
#include "CommonHeader.h"

#include <locale.h>
#pragma comment(lib, "UxTheme.lib")
#include <GdiPlus.h>
#pragma comment(lib,"gdiplus")
using namespace Gdiplus;

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <list>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <string>
#include <hash_map>
#include <hash_set>
#include <assert.h>
#include <unordered_map>
using namespace std;

#include <..\src\mfc\afximpl.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#define _APPGOVERNOR_COM_VER_

#include "../../Include/PUSDT_PCommManager/CommonFile.h"
#include "../../Include/PUSDT_PCommManager/PSM_Util.h"
#include "../../Include/PUSDT_PCommManager/SAXMgr.h"
#include "../../Include/PUSDT_PCommManager/FileMapObject.h"
#include "../../Include/PUSDT_PCommManager/ObjMng.h"
#include "../../Include/AppCDataManager/PAppDataObj_Common.h"
#include "../../Include/AppCDataManager/PAppDataObjMng.h"

#ifdef _DEBUG
#pragma comment( lib, "../../Lib/x64/Debug/PUSDT_PCommManager.lib" )
#pragma comment( lib, "../../Lib/x64/Debug/AppCDataManager.lib" )
#else
#pragma comment( lib, "../../Lib/x64/Release/PUSDT_PCommManager.lib" )
#pragma comment( lib, "../../Lib/x64/Release/AppCDataManager.lib" )

#endif


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


