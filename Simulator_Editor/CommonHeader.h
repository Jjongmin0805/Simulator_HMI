#pragma once

//////////////////////////////////////////////////////////////////////////
// Ctrl Infor
//////////////////////////////////////////////////////////////////////////

#define			START_USERMSG							150

#define			MAINFRAME_SENDMSG						( WM_USER + START_USERMSG )
#define			MAINFRAME_SENDDLGMSG					( WM_USER + START_USERMSG + 1 )
#define			MAINFRAME_SENDMENUMSG					( WM_USER + START_USERMSG + 2 )
#define			MAINFRAME_SENDfPRGINFOR					( WM_USER + START_USERMSG + 3 )
#define			MAINFRAME_SENDTABSEL					( WM_USER + START_USERMSG + 4 )
#define			SETCURRENT_SENDMSG						( WM_USER + START_USERMSG + 5 )

#define			MAINFRAMECOLOR							RGB( 20, 70, 120 )
#define			MAINFRAMESELECTCOLOR					RGB( 196, 196, 196 )
#define			MAINFRAMESELECTROUNTCOLOR				RGB( 151, 151, 151 )
#define			MAINFRAMETEXTCOLOR						RGB( 255, 255, 255 )
#define			COLOR_WHITE								RGB( 255, 255, 255 )
#define			COLOR_BLACK								RGB( 0, 0, 0 )

#define			MAINFRAMETOOLBAR_COMBOTITLE				_T("전압")
#define			MAINFRAMETOOLBAR_EDITTITLE				_T("V       전류 X")

#define			MAINFRAMETOOLBAR_TCIMAGECOUNT			18
#define			MAINFRAMETOOLBAR_ICONMAKECOLOR			RGB( 0, 0, 0 )
#define			MAINFRAMETOOLBAR_EDITWIDTH				75
#define			MAINFRAMETOOLBAR_EDITHEIGHT				20

#define			MAINFRAMETOOLBAR_FRAMEICONPOS_X			7
#define			MAINFRAMETOOLBAR_FRAMEICONPOS_Y			2

#define			MONITOR_CENTER							0x0001
#define			MONITOR_PART_MAX						0x0002
#define			MONITOR_CLIP							0x0000
#define			MONITOR_WORKAREA						0x0010
#define			MONITOR_AREA							0x0000

#define			MARGIN_BOX								10
#define			MARGIN_MAXIMIZED						2

static const	RGBTRIPLE	MAINFFRAMETOOLBAR_BGCOLOR	= {192, 192, 192};

struct EraseObjData
{
	template <typename _container> void operator()( _container* pObjdata )
	{
		if( pObjdata != NULL )
		{
			delete pObjdata;
			pObjdata = NULL;
		}
	}
};

enum FILEACCESSMODE {
	FILEACCESS_EXISTENCE_ONLY		= 0,
	FILEACCESS_WRITE_ONLY			= 2,
	FILEACCESS_READ_ONLY			= 4,
	FILEACCESS_READ_AND_WRITE		= 6
};

//////////////////////////////////////////////////////////////////////////
// Ctrl End
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// MainFrm Skin
//////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------
#define IDX_SYSTEMICON_CAPTION_LEFT					0
#define IDX_SYSTEMICON_CAPTION_CENTER				1
#define IDX_SYSTEMICON_CAPTION_RIGHT				2
#define IDX_SYSTEMICON_FRAME_LEFT					3
#define IDX_SYSTEMICON_FRAME_LEFT_BOTTOM			4
#define IDX_SYSTEMICON_FRAME_BOTTOM					5
#define IDX_SYSTEMICON_FRAME_RIGHT					6
#define IDX_SYSTEMICON_FRAME_RIGHT_BOTTOM			7
#define IDX_CAPTION_MINIMIZE_ON						8
#define IDX_CAPTION_MINIMIZE_OFF					9
#define IDX_CAPTION_MINIMIZE_DOWN					10
#define IDX_CAPTION_MINIMIZE_DISABLE				11
#define IDX_CAPTION_MAXIMIZE_ON						12
#define IDX_CAPTION_MAXIMIZE_OFF					13
#define IDX_CAPTION_MAXIMIZE_DOWN					14
#define IDX_CAPTION_MAXIMIZE_DISABLE				15
#define IDX_CAPTION_EXIT_ON							16
#define IDX_CAPTION_EXIT_OFF						17
#define IDX_CAPTION_EXIT_DOWN						18
#define IDX_CAPTION_EXIT_DISABLE					19
#define IDX_CAPTION_RESTORE_ON						20
#define IDX_CAPTION_RESTORE_OFF						21
#define IDX_CAPTION_RESTORE_DOWN					22
#define IDX_CAPTION_RESTORE_DISABLE					23
//
#define IDX_SYSTEMICON_MAX							24

//--------------------------------------------------------

#define CAPTION_SYSTEM								0x01
#define CAPTION_MIN									0x02
#define CAPTION_MAX									0x04
#define CAPTION_EXIT								0x08

//--------------------------------------------------------
#define IDX_ICON_OK									0
#define IDX_ICON_MAX								1
//--------------------------------------------------------
#define ICON16										0
#define ICON24										1
#define ICON32										2
//--------------------------------------------------------
#define IDX_FONT_SMALL								0
#define IDX_FONT_MEDIUM								1
#define IDX_FONT_LARGE								2
#define IDX_FONT_MAX								3
//--------------------------------------------------------
#define IDX_RGB_MASK								0
#define IDX_RGB_BACKGROUND							1
#define IDX_RGB_FONT								2
#define IDX_RGB_FONT_CAPTION						3
#define IDX_RGB_FONT_CAPTION_INACTIVE				4
#define IDX_RGB_CONTROL_BORDER						5
#define IDX_RGB_MAX									6

typedef BOOL ( WINAPI *LPFounction )( HWND hWnd, COLORREF _Color, BYTE bAlpha, DWORD dwFlags );

//typedef struct tagBITMAP_INFO
//{
//	HBITMAP hBitmap;
//	BITMAP	bitmap;
//} BITMAP_INFO;


//////////////////////////////////////////////////////////////////////////
// Skin End
//////////////////////////////////////////////////////////////////////////
