#pragma once

//////////////////////////////////////////////////////////////////////////
// Ctrl Infor
//////////////////////////////////////////////////////////////////////////

#define			PNOCtrl_START_USERMSG							150
#define			PNOCtrl_MAINFRAME_SENDMSG						( WM_USER + PNOCtrl_START_USERMSG )
#define			PNOCtrl_MAINFRAME_SENDDLGMSG					( WM_USER + PNOCtrl_START_USERMSG + 1 )
#define			PNOCtrl_MAINFRAME_SENDMENUMSG					( WM_USER + PNOCtrl_START_USERMSG + 2 )
#define			PNOCtrl_MAINFRAME_INPUTMSG						( WM_USER + PNOCtrl_START_USERMSG + 3 )

#define			PNOCtrl_MAINFRAME_MASK							RGB( 255,	0, 255 )
#define			PNOCtrl_MAINFRAME_BACKGROUND					RGB( 250, 250, 250 )
#define			PNOCtrl_MAINFRAME_FONT							RGB(  51,  51,  51 )
#define			PNOCtrl_MAINFRAME_FONT_CAPTION					RGB(  20,  70, 120 )
#define			PNOCtrl_MAINFRAME_FONT_CAPTION_INACTIVE			RGB( 153, 114,  48 )
#define			PNOCtrl_MAINFRAME_CTRL_BORDER					RGB( 204, 204, 204 )

#define			PNOCtrl_COLOR_WHITE								RGB( 255, 255, 255 )
#define			PNOCtrl_COLOR_BLACK								RGB(   0,   0,   0 )
#define			PNOCtrl_COLOR_FRAME								RGB( 227, 227, 227 )

#define			PNOCtrl_MAINFRAMETOOLBAR_IMAGECOUNT				25
#define			PNOCtrl_MAINFRAMETOOLBAR_ICONMAKECOLOR			RGB( 0, 0, 0 )
#define			PNOCtrl_MAINFRAMETOOLBAR_EDITWIDTH				75
#define			PNOCtrl_MAINFRAMETOOLBAR_EDITHEIGHT				20

#define			PNOCtrl_MAINFRAMETOOLBAR_FRAMEICONPOS_X			7
#define			PNOCtrl_MAINFRAMETOOLBAR_FRAMEICONPOS_Y			2

#define			PNOCtrl_MONITOR_CENTER							0x0001
#define			PNOCtrl_MONITOR_PART_MAX						0x0002
#define			PNOCtrl_MONITOR_CLIP							0x0000
#define			PNOCtrl_MONITOR_WORKAREA						0x0010
#define			PNOCtrl_MONITOR_AREA							0x0000

#define			PNOCtrl_MARGIN_BOX								10
#define			PNOCtrl_MARGIN_MAXIMIZED						2

struct PNOCtrl_EraseObjData
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

// static enum FILEACCESSMODE {
// 	FILEACCESS_EXISTENCE_ONLY		= 0,
// 	FILEACCESS_WRITE_ONLY			= 2,
// 	FILEACCESS_READ_ONLY			= 4,
// 	FILEACCESS_READ_AND_WRITE		= 6
// };

//////////////////////////////////////////////////////////////////////////
// Ctrl End
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// Dialog Skin
//////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------
#define IDX_CTRL_SYSTEMICON_CAPTION_LEFT			0
#define IDX_CTRL_SYSTEMICON_CAPTION_CENTER			1
#define IDX_CTRL_SYSTEMICON_CAPTION_RIGHT			2
#define IDX_CTRL_SYSTEMICON_FRAME_LEFT				3
#define IDX_CTRL_SYSTEMICON_FRAME_LEFT_BOTTOM		4
#define IDX_CTRL_SYSTEMICON_FRAME_BOTTOM			5
#define IDX_CTRL_SYSTEMICON_FRAME_RIGHT				6
#define IDX_CTRL_SYSTEMICON_FRAME_RIGHT_BOTTOM		7
#define IDX_CTRL_CAPTION_MINIMIZE_ON				8
#define IDX_CTRL_CAPTION_MINIMIZE_OFF				9
#define IDX_CTRL_CAPTION_MINIMIZE_DOWN				10
#define IDX_CTRL_CAPTION_MAXIMIZE_ON				11
#define IDX_CTRL_CAPTION_MAXIMIZE_OFF				12
#define IDX_CTRL_CAPTION_MAXIMIZE_DOWN				13
#define IDX_CTRL_CAPTION_EXIT_ON					14
#define IDX_CTRL_CAPTION_EXIT_OFF					15
#define IDX_CTRL_CAPTION_EXIT_DOWN					16
#define IDX_CTRL_CAPTION_RESTORE_ON					17
#define IDX_CTRL_CAPTION_RESTORE_OFF				18
#define IDX_CTRL_CAPTION_RESTORE_DOWN				19
#define IDX_CTRL_CAPTION_WIDTH_ON					20
#define IDX_CTRL_CAPTION_WIDTH_OFF					21
#define IDX_CTRL_CAPTION_WIDTH_DOWN					22
#define IDX_CTRL_CAPTION_HEIGHT_ON					23
#define IDX_CTRL_CAPTION_HEIGHT_OFF					24
#define IDX_CTRL_CAPTION_HEIGHT_DOWN				25
//
#define IDX_CHILDICON_CAPTION_LEFT					25
#define IDX_CHILDICON_CAPTION_CENTER				26
#define IDX_CHILDICON_CAPTION_RIGHT					27
#define IDX_CHILDICON_FRAME_LEFT					28
#define IDX_CHILDICON_FRAME_LEFT_BOTTOM				29
#define IDX_CHILDICON_FRAME_BOTTOM					30
#define IDX_CHILDICON_FRAME_RIGHT					31
#define IDX_CHILDICON_FRAME_RIGHT_BOTTOM			32
#define IDX_CHILDCAPTION_MINIMIZE_ON				33
#define IDX_CHILDCAPTION_MINIMIZE_OFF				34
#define IDX_CHILDCAPTION_MINIMIZE_DOWN				35
#define IDX_CHILDCAPTION_EXIT_ON					36
#define IDX_CHILDCAPTION_EXIT_OFF					37
#define IDX_CHILDCAPTION_EXIT_DOWN					38
#define IDX_CHILDCAPTION_RESTORE_ON					39
#define IDX_CHILDCAPTION_RESTORE_OFF				40
#define IDX_CHILDCAPTION_RESTORE_DOWN				41
//
#define IDX_DLG_SYSTEMICON_CAPTION_LEFT				42
#define IDX_DLG_SYSTEMICON_CAPTION_CENTER			43
#define IDX_DLG_SYSTEMICON_CAPTION_RIGHT			44
#define IDX_DLG_SYSTEMICON_FRAME_LEFT				45
#define IDX_DLG_SYSTEMICON_FRAME_LEFT_BOTTOM		46
#define IDX_DLG_SYSTEMICON_FRAME_BOTTOM				47
#define IDX_DLG_SYSTEMICON_FRAME_RIGHT				48
#define IDX_DLG_SYSTEMICON_FRAME_RIGHT_BOTTOM		49
#define IDX_DLG_CAPTION_SYSTEMICON_ON				50
#define IDX_DLG_CAPTION_SYSTEMICON_OFF				51
#define IDX_DLG_CAPTION_SYSTEMICON_DOWN				52
#define IDX_DLG_CAPTION_MINIMIZE_ON					53
#define IDX_DLG_CAPTION_MINIMIZE_OFF				54
#define IDX_DLG_CAPTION_MINIMIZE_DOWN				55
#define IDX_DLG_CAPTION_MAXIMIZE_ON					56
#define IDX_DLG_CAPTION_MAXIMIZE_OFF				57
#define IDX_DLG_CAPTION_MAXIMIZE_DOWN				58
#define IDX_DLG_CAPTION_EXIT_ON						59
#define IDX_DLG_CAPTION_EXIT_OFF					60
#define IDX_DLG_CAPTION_EXIT_DOWN					61
#define IDX_DLG_CAPTION_RESTORE_ON					62
#define IDX_DLG_CAPTION_RESTORE_OFF					63
#define IDX_DLG_CAPTION_RESTORE_DOWN				64

#define PNOCtrl_IDX_SYSTEMICON_MAX					65

//--------------------------------------------------------

#define PNOCtrl_CAPTION_MIN							0x01
#define PNOCtrl_CAPTION_MAX							0x02
#define PNOCtrl_CAPTION_EXIT						0x04

//--------------------------------------------------------
#define PNOCtrl_IDX_ICON_OK							0
#define PNOCtrl_IDX_ICON_MAX						1
//--------------------------------------------------------
#define PNOCtrl_ICON16								0
#define PNOCtrl_ICON24								1
#define PNOCtrl_ICON32								2
//--------------------------------------------------------
#define PNOCtrl_IDX_FONT_SMALL						0
#define PNOCtrl_IDX_FONT_MEDIUM						1
#define PNOCtrl_IDX_FONT_LARGE						2
#define PNOCtrl_IDX_FONT_MAX						3
//--------------------------------------------------------
#define PNOCtrl_IDX_RGB_MASK						0
#define PNOCtrl_IDX_RGB_BACKGROUND					1
#define PNOCtrl_IDX_RGB_FONT						2
#define PNOCtrl_IDX_RGB_FONT_CAPTION				3
#define PNOCtrl_IDX_RGB_FONT_CAPTION_INACTIVE		4
#define PNOCtrl_IDX_RGB_CONTROL_BORDER				5
#define PNOCtrl_IDX_RGB_MAX							6

typedef BOOL ( WINAPI *LPFounction )( HWND hWnd, COLORREF _Color, BYTE bAlpha, DWORD dwFlags );

typedef struct PNOCtrl_tagBITMAP_INFO
{
	HBITMAP hBitmap;
	BITMAP	bitmap;
} PNOCtrl_BITMAP_INFO;


//////////////////////////////////////////////////////////////////////////
// Skin End
//////////////////////////////////////////////////////////////////////////
