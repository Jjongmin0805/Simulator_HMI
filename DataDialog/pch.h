// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"
#include <afxcontrolbars.h>

#endif //PCH_H

#include "../Control/Include/Common.h"


#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;



#include <oledb.h>
#include <atldbcli.h>//CSession용
#include <atldbsch.h>

#pragma warning( disable : 4995 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4985 )

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
#include <unordered_map>
using namespace std;

#define _APPGOVERNOR_COM_VER_

#include "../Include/PUSDT_PCommManager/CommonFile.h"
#include "../Include/PUSDT_PCommManager/PSM_Util.h"
#include "../Include/PUSDT_PCommManager/SAXMgr.h"
#include "../Include/PUSDT_PCommManager/FileMapObject.h"
#include "../Include/PUSDT_PCommManager/ObjMng.h"
#include "../Include/AppCDataManager/PAppDataObj_Common.h"
#include "../Include/AppCDataManager/PAppDataObjMng.h"
#include "../Include/DBContainer/CommonFile.h"
#include "../Include/DBContainer/DBContainer_Insatnce.h"
#include <afxcontrolbars.h>

#include "../include/PNOVR_Ctrl/CommonHeader.h"
#include "../include/PNOVR_Ctrl/Ctrl_Manager.h"
#include "../include/PNOVR_Ctrl/Util_Manager.h"

#include "../Include/ADMStoKCIM/CADMStoKCIMDlg.h"
//#include <afxcontrolbars.h>



#ifdef _DEBUG
#pragma comment( lib, "../Lib/x64/Debug/ADMStoKCIM.lib" )
#else
#pragma comment( lib, "../Lib/x64/Release/ADMStoKCIM.lib" )
#endif



#ifdef _DEBUG
#pragma comment( lib, "../Lib/x64/Debug/PUSDT_PCommManager.lib" )
#pragma comment( lib, "../Lib/x64/Debug/AppCDataManager.lib" )
#pragma comment( lib, "../lib/PNOVR_Ctrl/Debug/PNOVR_Ctrl.lib" )
#pragma comment( lib, "../Lib/x64/Debug/DBContainer.lib" )
#else
#pragma comment( lib, "../Lib/x64/Release/PUSDT_PCommManager.lib" )
#pragma comment( lib, "../Lib/x64/Release/AppCDataManager.lib" )
#pragma comment( lib, "../lib/PNOVR_Ctrl/Release/PNOVR_Ctrl.lib" )
#pragma comment( lib, "../Lib/x64/Release/DBContainer.lib" )

#endif