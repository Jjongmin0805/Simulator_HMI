#include "pch.h"
#include "PNOCtrl_SkinMng.h"

CPNOCtrl_SkinMng*			CPNOCtrl_SkinMng::pSingletonData = 0;

CPNOCtrl_SkinMng* CPNOCtrl_SkinMng::instance(void)
{
	if ( CPNOCtrl_SkinMng::pSingletonData == 0 )
	{
		CPNOCtrl_SkinMng::pSingletonData = new CPNOCtrl_SkinMng;

		CPNOCtrl_SkinMng::pSingletonData->LoadBitmaps();
		CPNOCtrl_SkinMng::pSingletonData->SetRGB(PNOCtrl_IDX_RGB_MASK, PNOCtrl_MAINFRAME_MASK);
		CPNOCtrl_SkinMng::pSingletonData->SetRGB(PNOCtrl_IDX_RGB_BACKGROUND, PNOCtrl_MAINFRAME_BACKGROUND);
		CPNOCtrl_SkinMng::pSingletonData->SetRGB(PNOCtrl_IDX_RGB_FONT, PNOCtrl_MAINFRAME_FONT);
		CPNOCtrl_SkinMng::pSingletonData->SetRGB(PNOCtrl_IDX_RGB_FONT_CAPTION, PNOCtrl_MAINFRAME_FONT_CAPTION);
		CPNOCtrl_SkinMng::pSingletonData->SetRGB(PNOCtrl_IDX_RGB_FONT_CAPTION_INACTIVE, PNOCtrl_MAINFRAME_FONT_CAPTION_INACTIVE);
		CPNOCtrl_SkinMng::pSingletonData->SetRGB(PNOCtrl_IDX_RGB_CONTROL_BORDER, PNOCtrl_MAINFRAME_CTRL_BORDER);

	} else {
		return CPNOCtrl_SkinMng::pSingletonData;
	}
	return CPNOCtrl_SkinMng::pSingletonData;

	return NULL;
}

CPNOCtrl_SkinMng::CPNOCtrl_SkinMng(void) : 
m_RectToolbarChildSysMin( 0, 0, 0, 0 ), m_RectToolbarChildSysMax( 0, 0, 0, 0 ), m_RectToolbarChildSysExit( 0, 0, 0, 0 )
{
	for( int i = 0 ; i < PNOCtrl_IDX_SYSTEMICON_MAX ; i++ )
	{
		m_infoBitmap[i].hBitmap			= NULL;
		::ZeroMemory(&m_infoBitmap[i].bitmap, sizeof(BITMAP));
	}

	for( int i = 0 ; i < PNOCtrl_IDX_FONT_MAX ; i++ )
		m_pFont[i]						= NULL;

	for( int i = 0 ; i < PNOCtrl_IDX_ICON_MAX ; i++ )
	{
		m_hIcon[i][0]					= NULL;
		m_hIcon[i][1]					= NULL;
		m_hIcon[i][2]					= NULL;
	}

	for( int i = 0 ; i < PNOCtrl_IDX_RGB_MAX ; i++ )
		m_cf[i]							= PNOCtrl_COLOR_BLACK;

	// SetLayeredWindowAttributes in User32.dll
	HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));
	SetLayeredWindowAttributes = (LPFounction)GetProcAddress(hUser32, "SetLayeredWindowAttributes");
}

CPNOCtrl_SkinMng::~CPNOCtrl_SkinMng(void)
{
	DeleteBitmaps();
	DeleteFonts();
	DeleteIcons();
}

void CPNOCtrl_SkinMng::DeleteBitmaps()
{
	for(UINT i=0; i<PNOCtrl_IDX_SYSTEMICON_MAX; i++)
	{
		if( m_infoBitmap[i].hBitmap )
		{
			::DeleteObject(m_infoBitmap[i].hBitmap);
			m_infoBitmap[i].hBitmap = NULL;
		}
		::ZeroMemory(&m_infoBitmap[i].bitmap, sizeof(BITMAP));
	}
}

void CPNOCtrl_SkinMng::DeleteFonts()
{
	for(UINT i=0; i<PNOCtrl_IDX_FONT_MAX; i++)
	{
		if( m_pFont[i] ) 
		{
			m_pFont[i]->DeleteObject();
			delete m_pFont[i];
			m_pFont[i] = NULL;
		}
	}
}

void CPNOCtrl_SkinMng::DeleteIcons()
{
	for(UINT i=0; i<PNOCtrl_IDX_ICON_MAX; i++)
	{
		for(UINT k=0; k<3; k++)
		{
			if( m_hIcon[i][k] )
			{
				::DestroyIcon(m_hIcon[i][k]);
				m_hIcon[i][k] = NULL;
			}
		}
	}
}

CString CPNOCtrl_SkinMng::GetModulePath()
{
	CString sPath;
	GetModuleFileName( AfxGetApp()->m_hInstance, sPath.GetBuffer(MAX_PATH), MAX_PATH );
	sPath.ReleaseBuffer();

	int nPos = sPath.ReverseFind(_T('\\'));
	if( nPos != -1 )
		sPath = sPath.Left( nPos );

	return sPath;
}

void CPNOCtrl_SkinMng::LoadBitmaps()
{
	DeleteBitmaps();

	CString strFileName(_T(""));
	CString sModulePath = GetModulePath() + _T("\\");
	for( UINT i = 0 ; i < PNOCtrl_IDX_SYSTEMICON_MAX ; i++ )
	{
		strFileName = GetBitmapFileName(i);
		if( strFileName.IsEmpty() )
			continue;

		strFileName = sModulePath + strFileName;

		m_infoBitmap[i].hBitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), (LPCTSTR)strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION|LR_DEFAULTSIZE);

		::GetObject(m_infoBitmap[i].hBitmap, sizeof(BITMAP), &m_infoBitmap[i].bitmap);
	}
}

CString CPNOCtrl_SkinMng::GetBitmapFileName(UINT nBitmapID)
{
	switch( nBitmapID )
	{
	case IDX_CTRL_SYSTEMICON_CAPTION_LEFT			:	return _T("skin\\Control\\Frm\\System_Caption_Left.pnoimg");				break;
	case IDX_CTRL_SYSTEMICON_CAPTION_CENTER			:	return _T("skin\\Control\\Frm\\System_Caption_Center.pnoimg");				break;
	case IDX_CTRL_SYSTEMICON_CAPTION_RIGHT			:	return _T("skin\\Control\\Frm\\System_Caption_Right.pnoimg");				break;
	case IDX_CTRL_SYSTEMICON_FRAME_LEFT				:	return _T("skin\\Control\\Frm\\System_Frame_Left.pnoimg");					break;
	case IDX_CTRL_SYSTEMICON_FRAME_LEFT_BOTTOM		:	return _T("skin\\Control\\Frm\\System_Frame_LeftBottom.pnoimg");			break;
	case IDX_CTRL_SYSTEMICON_FRAME_BOTTOM			:	return _T("skin\\Control\\Frm\\System_Frame_Bottom.pnoimg");				break;
	case IDX_CTRL_SYSTEMICON_FRAME_RIGHT			:	return _T("skin\\Control\\Frm\\System_Frame_Right.pnoimg");				break;
	case IDX_CTRL_SYSTEMICON_FRAME_RIGHT_BOTTOM		:	return _T("skin\\Control\\Frm\\System_Frame_RightBottom.pnoimg");			break;
	case IDX_CTRL_CAPTION_MINIMIZE_ON				:	return _T("");															break;
	case IDX_CTRL_CAPTION_MINIMIZE_OFF				:	return _T("");															break;
	case IDX_CTRL_CAPTION_MINIMIZE_DOWN				:	return _T("");															break;
	case IDX_CTRL_CAPTION_MAXIMIZE_ON				:	return _T("");															break;
	case IDX_CTRL_CAPTION_MAXIMIZE_OFF				:	return _T("");															break;
	case IDX_CTRL_CAPTION_MAXIMIZE_DOWN				:	return _T("");															break;
	case IDX_CTRL_CAPTION_EXIT_ON					:	return _T("skin\\Control\\Frm\\Caption_ICON_EXIT_Over.pnoimg");			break;
	case IDX_CTRL_CAPTION_EXIT_OFF					:	return _T("skin\\Control\\Frm\\Caption_ICON_EXIT_Off.pnoimg");				break;
	case IDX_CTRL_CAPTION_EXIT_DOWN					:	return _T("");															break;
	case IDX_CTRL_CAPTION_RESTORE_ON				:	return _T("");															break;
	case IDX_CTRL_CAPTION_RESTORE_OFF				:	return _T("");															break;
	case IDX_CTRL_CAPTION_RESTORE_DOWN				:	return _T("");															break;
	case IDX_CTRL_CAPTION_WIDTH_ON					:	return _T("skin\\Control\\Frm\\Caption_ICON_Width_On.pnoimg");				break;
	case IDX_CTRL_CAPTION_WIDTH_OFF					:	return _T("skin\\Control\\Frm\\Caption_ICON_Width_Off.pnoimg");			break;
	case IDX_CTRL_CAPTION_WIDTH_DOWN				:	return _T("skin\\Control\\Frm\\Caption_ICON_Width_Down.pnoimg");			break;
	case IDX_CTRL_CAPTION_HEIGHT_ON					:	return _T("skin\\Control\\Frm\\Caption_ICON_Height_On.pnoimg");			break;
	case IDX_CTRL_CAPTION_HEIGHT_OFF				:	return _T("skin\\Control\\Frm\\Caption_ICON_Height_Off.pnoimg");			break;
	case IDX_CTRL_CAPTION_HEIGHT_DOWN				:	return _T("skin\\Control\\Frm\\Caption_ICON_Height_Down.pnoimg");			break;

	case IDX_DLG_SYSTEMICON_CAPTION_LEFT			:	return _T("skin\\popup_dlg\\Frm\\System_Caption_Left.pnoimg");				break;
	case IDX_DLG_SYSTEMICON_CAPTION_CENTER			:	return _T("skin\\popup_dlg\\Frm\\System_Caption_Center.pnoimg");			break;
	case IDX_DLG_SYSTEMICON_CAPTION_RIGHT			:	return _T("skin\\popup_dlg\\Frm\\System_Caption_Right.pnoimg");			break;
	case IDX_DLG_SYSTEMICON_FRAME_LEFT				:	return _T("skin\\popup_dlg\\Frm\\System_Frame_Left.pnoimg");				break;
	case IDX_DLG_SYSTEMICON_FRAME_LEFT_BOTTOM		:	return _T("skin\\popup_dlg\\Frm\\System_Frame_LeftBottom.pnoimg");			break;
	case IDX_DLG_SYSTEMICON_FRAME_BOTTOM			:	return _T("skin\\popup_dlg\\Frm\\System_Frame_Bottom.pnoimg");				break;
	case IDX_DLG_SYSTEMICON_FRAME_RIGHT				:	return _T("skin\\popup_dlg\\Frm\\System_Frame_Right.pnoimg");				break;
	case IDX_DLG_SYSTEMICON_FRAME_RIGHT_BOTTOM		:	return _T("skin\\popup_dlg\\Frm\\System_Frame_RightBottom.pnoimg");		break;
	case IDX_DLG_CAPTION_SYSTEMICON_ON				:	return _T("");															break;
	case IDX_DLG_CAPTION_SYSTEMICON_OFF				:	return _T("");															break;
	case IDX_DLG_CAPTION_SYSTEMICON_DOWN			:	return _T("");															break;
	case IDX_DLG_CAPTION_MINIMIZE_ON				:	return _T("skin\\popup_dlg\\Frm\\Caption_Minimize_On.pnoimg");				break;
	case IDX_DLG_CAPTION_MINIMIZE_OFF				:	return _T("skin\\popup_dlg\\Frm\\Caption_Minimize_Off.pnoimg");			break;
	case IDX_DLG_CAPTION_MINIMIZE_DOWN				:	return _T("skin\\popup_dlg\\Frm\\Caption_Minimize_Down.pnoimg");			break;
	case IDX_DLG_CAPTION_MAXIMIZE_ON				:	return _T("skin\\popup_dlg\\Frm\\Caption_Maximize_On.pnoimg");				break;
	case IDX_DLG_CAPTION_MAXIMIZE_OFF				:	return _T("skin\\popup_dlg\\Frm\\Caption_Maximize_Off.pnoimg");			break;
	case IDX_DLG_CAPTION_MAXIMIZE_DOWN				:	return _T("skin\\popup_dlg\\Frm\\Caption_Maximize_Down.pnoimg");			break;
	case IDX_DLG_CAPTION_EXIT_ON					:	return _T("skin\\popup_dlg\\Frm\\Caption_Exit_On.pnoimg");					break;
	case IDX_DLG_CAPTION_EXIT_OFF					:	return _T("skin\\popup_dlg\\Frm\\Caption_Exit_Off.pnoimg");				break;
	case IDX_DLG_CAPTION_EXIT_DOWN					:	return _T("skin\\popup_dlg\\Frm\\Caption_Exit_Down.pnoimg");				break;
	case IDX_DLG_CAPTION_RESTORE_ON					:	return _T("skin\\popup_dlg\\Frm\\Caption_Restore_On.pnoimg");				break;
	case IDX_DLG_CAPTION_RESTORE_OFF				:	return _T("skin\\popup_dlg\\Frm\\Caption_Restore_Off.pnoimg");				break;
	case IDX_DLG_CAPTION_RESTORE_DOWN				:	return _T("skin\\popup_dlg\\Frm\\Caption_Restore_Down.pnoimg");			break;

	}
	return _T("");
}

void CPNOCtrl_SkinMng::LoadIcons()
{
	DeleteIcons();

	CString strFileName(_T(""));
	CString sModulePath = GetModulePath() + _T("\\");

	for(UINT i=0; i<PNOCtrl_IDX_ICON_MAX; i++)
	{
		strFileName = GetIconFileName(i);
		if( strFileName.IsEmpty() )
			continue;

		strFileName = sModulePath + strFileName;

		m_hIcon[i][0] = (HICON)::LoadImage(::AfxGetInstanceHandle(), strFileName, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
		m_hIcon[i][1] = (HICON)::LoadImage(::AfxGetInstanceHandle(), strFileName, IMAGE_ICON, 24, 24, LR_LOADFROMFILE);
		m_hIcon[i][2] = (HICON)::LoadImage(::AfxGetInstanceHandle(), strFileName, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	}
}

CString CPNOCtrl_SkinMng::GetIconFileName(UINT nIconID)
{
	switch( nIconID )
	{
	case PNOCtrl_IDX_ICON_OK							:	return _T("skin\\ok.ico");						break;
	}
	return _T("");
}

SIZE CPNOCtrl_SkinMng::GetBitmapSize(UINT nBitmapID)
{
	SIZE size;
	if( nBitmapID >= PNOCtrl_IDX_SYSTEMICON_MAX )
	{
		size.cx=0;
		size.cy=0;
		return size;
	}

	size.cx = m_infoBitmap[nBitmapID].bitmap.bmWidth;
	size.cy = m_infoBitmap[nBitmapID].bitmap.bmHeight;

	return size;
}

HBITMAP CPNOCtrl_SkinMng::GetBitmap(UINT nBitmapID)
{
	if( nBitmapID >= PNOCtrl_IDX_SYSTEMICON_MAX )
		return NULL;

	return m_infoBitmap[nBitmapID].hBitmap;
}

HICON CPNOCtrl_SkinMng::GetIcon(UINT nIconID, UINT nType)
{
	if( nIconID >= PNOCtrl_IDX_ICON_MAX ||
		nType > PNOCtrl_ICON32 )
		return NULL;

	return m_hIcon[nIconID][nType];
}

void CPNOCtrl_SkinMng::SetRGB(UINT nRGBID, COLORREF cf)
{
	if( nRGBID >= PNOCtrl_IDX_RGB_MAX )
		return;

	m_cf[nRGBID] = cf;
}

COLORREF CPNOCtrl_SkinMng::GetRGB(UINT nRGBID)
{
	if( nRGBID >= PNOCtrl_IDX_RGB_MAX )
		return RGB(0,0,0);

	return m_cf[nRGBID];
}

CFont * CPNOCtrl_SkinMng::GetFont(UINT nFontID) 
{ 
	if( nFontID >= PNOCtrl_IDX_FONT_MAX )
		return NULL;

	return m_pFont[nFontID]; 
}

CFont * CPNOCtrl_SkinMng::SetFont(CWnd* pWnd, UINT nFontID, CString sFaceName, UINT nFontSize, BOOL bBold/*=FALSE*/)
{
	if( nFontID >= PNOCtrl_IDX_FONT_MAX )
		return NULL;

	CWnd *pMain = pWnd;
	if( !pMain )
		return NULL;	

	// Font Name
	LOGFONT logFont;
	ZeroMemory(&logFont,sizeof(logFont));
// 	_tcscpy( logFont.lfFaceName, sFaceName );
	wcscpy_s(logFont.lfFaceName, sFaceName);

	// Font Style
	logFont.lfItalic = FALSE;
	if( bBold )
		logFont.lfWeight = FW_BOLD;
	else
		logFont.lfWeight = FW_NORMAL;

	// Font Size
	HDC hdc = ::GetDC(pMain->m_hWnd);
	if( !hdc ) 
		logFont.lfHeight = nFontSize;
	else 
		logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	::ReleaseDC(pMain->m_hWnd, hdc);

	// New Font
	if( m_pFont[nFontID] ) 
	{
		m_pFont[nFontID]->DeleteObject();
		delete m_pFont[nFontID];
		m_pFont[nFontID] = NULL;
	}

	m_pFont[nFontID] = (CFont *)new CFont;	
	if( !m_pFont[nFontID]->CreateFontIndirect( &logFont ) )
	{
		delete m_pFont[nFontID];
		m_pFont[nFontID] = NULL;
	}

	pMain->SetFont(m_pFont[PNOCtrl_IDX_FONT_SMALL],true);

	return m_pFont[nFontID];
}

CSize CPNOCtrl_SkinMng::FormatText(CString& sText, CDC* pDC, int nWidth)
{
	CRect rect(0, 0, nWidth, 20);
	UINT uFlags = DT_CALCRECT | DT_SINGLELINE | DT_MODIFYSTRING | DT_END_ELLIPSIS;

	::DrawText(pDC->GetSafeHdc(), sText.GetBuffer(sText.GetLength() + 4), -1, rect, uFlags);
	sText.ReleaseBuffer();

	return pDC->GetTextExtent(sText);
}

COLORREF CPNOCtrl_SkinMng::Darker(COLORREF crBase, float fFactor)
{
	ASSERT (fFactor < 1.0f && fFactor > 0.0f);

	fFactor = min(fFactor, 1.0f);
	fFactor = max(fFactor, 0.0f);

	BYTE bRed, bBlue, bGreen;
	BYTE bRedShadow, bBlueShadow, bGreenShadow;

	bRed = GetRValue(crBase);
	bBlue = GetBValue(crBase);
	bGreen = GetGValue(crBase);

	bRedShadow = (BYTE)(bRed * fFactor);
	bBlueShadow = (BYTE)(bBlue * fFactor);
	bGreenShadow = (BYTE)(bGreen * fFactor);

	return RGB(bRedShadow, bGreenShadow, bBlueShadow);
}

COLORREF CPNOCtrl_SkinMng::Lighter(COLORREF crBase, float fFactor) 
{
	ASSERT (fFactor > 1.0f);

	fFactor = max(fFactor, 1.0f);

	BYTE bRed, bBlue, bGreen;
	BYTE bRedHilite, bBlueHilite, bGreenHilite;

	bRed = GetRValue(crBase);
	bBlue = GetBValue(crBase);
	bGreen = GetGValue(crBase);

	bRedHilite = (BYTE)min((int)(bRed * fFactor), 255);
	bBlueHilite = (BYTE)min((int)(bBlue * fFactor), 255);
	bGreenHilite = (BYTE)min((int)(bGreen * fFactor), 255);

	return RGB(bRedHilite, bGreenHilite, bBlueHilite);
}

UINT CPNOCtrl_SkinMng::GetSystemVersion()
{
	OSVERSIONINFOEX							osver;
	BOOL									bOsVersionInfoEx;
	UINT									uSystemVersion( SYSOS_ERROR );

	::ZeroMemory( &osver, sizeof( OSVERSIONINFOEX ) );
	osver.dwOSVersionInfoSize				= sizeof( OSVERSIONINFOEX );
	if( !( bOsVersionInfoEx = ::GetVersionEx( ( OSVERSIONINFO *)&osver ) ) )
	{
		osver.dwOSVersionInfoSize			= sizeof(OSVERSIONINFO);
		if( !GetVersionEx( ( OSVERSIONINFO * ) &osver ) ) 
		{
			return uSystemVersion;
		}
	}

	switch( osver.dwPlatformId )
	{
	case VER_PLATFORM_WIN32_NT :		{
		if(osver.dwMajorVersion <= 4)										uSystemVersion = SYSOS_WINNT;
		else if(osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)		uSystemVersion = SYSOS_WIN2K;
		else if(osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)		uSystemVersion = SYSOS_WINXP;
		else if(osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)		uSystemVersion = SYSOS_VISTA;
		else if(osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)		uSystemVersion = SYSOS_WIN7;
		else
			uSystemVersion = SYSOS_NEXTOS;
										}; break;
	case VER_PLATFORM_WIN32_WINDOWS:	{
		if(osver.dwMajorVersion == 4 && osver.dwMinorVersion == 0)
		{
			if(osver.szCSDVersion[1] == 'C' || osver.szCSDVersion[1] == 'B')
				uSystemVersion = SYSOS_WINOSR2;
			else
				uSystemVersion = SYSOS_WIN95;
		} 
		if(osver.dwMajorVersion == 4 && osver.dwMinorVersion == 10)
		{
			if(osver.szCSDVersion[1] == 'A')
				uSystemVersion = SYSOS_WIN98SE;
			else
				uSystemVersion = SYSOS_WIN98;
		} 
		if(osver.dwMajorVersion == 4 && osver.dwMinorVersion == 90)
		{
			uSystemVersion = SYSOS_WINME;
		} 
										}; break;
	case VER_PLATFORM_WIN32s :			{
		uSystemVersion = SYSOS_WIN32;
										}; break;
	}

	return uSystemVersion; 
}