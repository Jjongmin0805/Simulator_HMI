#include "pch.h"
#include "SkinMng.h"

CSkinMng*			CSkinMng::pSingletonData = 0;

CSkinMng* CSkinMng::instance(void)
{
	if ( CSkinMng::pSingletonData == 0 )
	{
		CSkinMng::pSingletonData = new CSkinMng;
	} else {
		return CSkinMng::pSingletonData;
	}
	return CSkinMng::pSingletonData;

	return NULL;
}

CSkinMng::CSkinMng(void) : 
			m_RectToolbarChildSysMin( 0, 0, 0, 0 ), m_RectToolbarChildSysMax( 0, 0, 0, 0 ), m_RectToolbarChildSysExit( 0, 0, 0, 0 )
{
	for( int i = 0 ; i < IDX_SYSTEMICON_MAX ; i++ )
	{
		m_infoBitmap[i].hBitmap			= NULL;
		::ZeroMemory(&m_infoBitmap[i].bitmap, sizeof(BITMAP));
	}

	for( int i = 0 ; i < IDX_FONT_MAX ; i++ )
		m_pFont[i]						= NULL;

	for( int i = 0 ; i < IDX_ICON_MAX ; i++ )
	{
		m_hIcon[i][0]					= NULL;
		m_hIcon[i][1]					= NULL;
		m_hIcon[i][2]					= NULL;
	}

	for( int i = 0 ; i < IDX_RGB_MAX ; i++ )
		m_cf[i]							= RGB( 0, 0, 0 );

// SetLayeredWindowAttributes in User32.dll
	HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));
	SetLayeredWindowAttributes = (LPFounction)GetProcAddress(hUser32, "SetLayeredWindowAttributes");
}

CSkinMng::~CSkinMng(void)
{
	DeleteBitmaps();
	DeleteFonts();
	DeleteIcons();
}

void CSkinMng::DeleteBitmaps()
{
	for(UINT i=0; i<IDX_SYSTEMICON_MAX; i++)
	{
		if( m_infoBitmap[i].hBitmap )
		{
			::DeleteObject(m_infoBitmap[i].hBitmap);
			m_infoBitmap[i].hBitmap = NULL;
		}
		::ZeroMemory(&m_infoBitmap[i].bitmap, sizeof(BITMAP));
	}
}

void CSkinMng::DeleteFonts()
{
	for(UINT i=0; i<IDX_FONT_MAX; i++)
	{
		if( m_pFont[i] ) 
		{
			m_pFont[i]->DeleteObject();
			delete m_pFont[i];
			m_pFont[i] = NULL;
		}
	}
}

void CSkinMng::DeleteIcons()
{
	for(UINT i=0; i<IDX_ICON_MAX; i++)
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

CString CSkinMng::GetModulePath()
{
	CString sPath;
	GetModuleFileName( AfxGetApp()->m_hInstance, sPath.GetBuffer(MAX_PATH), MAX_PATH );
	sPath.ReleaseBuffer();

	int nPos = sPath.ReverseFind(_T('\\'));
	if( nPos != -1 )
		sPath = sPath.Left( nPos );

	return sPath;
}

void CSkinMng::LoadBitmaps()
{
	DeleteBitmaps();

	CString strFileName(_T(""));
	CString sModulePath = GetModulePath() + _T("\\");

	for( UINT i = 0 ; i < IDX_SYSTEMICON_MAX ; i++ )
	{
		strFileName = GetBitmapFileName(i);
		if( strFileName.IsEmpty() )
			continue;

		strFileName = sModulePath + strFileName;

		m_infoBitmap[i].hBitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), (LPCTSTR)strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION|LR_DEFAULTSIZE);

		::GetObject(m_infoBitmap[i].hBitmap, sizeof(BITMAP), &m_infoBitmap[i].bitmap);
	}
}

CString CSkinMng::GetBitmapFileName(UINT nBitmapID)
{
	switch( nBitmapID )
	{
		case IDX_SYSTEMICON_CAPTION_LEFT				:	return _T("skin\\Frame\\System_Caption_Left.pnoimg");						break;
		case IDX_SYSTEMICON_CAPTION_CENTER				:	return _T("skin\\Frame\\System_Caption_Center.pnoimg");					break;
		case IDX_SYSTEMICON_CAPTION_RIGHT				:	return _T("skin\\Frame\\System_Caption_Right.pnoimg");						break;
		case IDX_SYSTEMICON_FRAME_LEFT					:	return _T("skin\\Frame\\System_Frame_Left.pnoimg");						break;
		case IDX_SYSTEMICON_FRAME_LEFT_BOTTOM			:	return _T("skin\\Frame\\System_Frame_LeftBottom.pnoimg");					break;
		case IDX_SYSTEMICON_FRAME_BOTTOM				:	return _T("skin\\Frame\\System_Frame_Bottom.pnoimg");						break;
		case IDX_SYSTEMICON_FRAME_RIGHT					:	return _T("skin\\Frame\\System_Frame_Right.pnoimg");						break;
		case IDX_SYSTEMICON_FRAME_RIGHT_BOTTOM			:	return _T("skin\\Frame\\System_Frame_RightBottom.pnoimg");					break;
		case IDX_CAPTION_MINIMIZE_ON					:	return _T("skin\\SystemBar\\Caption_Minimize_On.pnoimg");					break;
		case IDX_CAPTION_MINIMIZE_OFF					:	return _T("skin\\SystemBar\\Caption_Minimize_Off.pnoimg");					break;
		case IDX_CAPTION_MINIMIZE_DOWN					:	return _T("skin\\SystemBar\\Caption_Minimize_Down.pnoimg");				break;
		case IDX_CAPTION_MINIMIZE_DISABLE				:	return _T("skin\\SystemBar\\Caption_Minimize_Disable.pnoimg");				break;
		case IDX_CAPTION_MAXIMIZE_ON					:	return _T("skin\\SystemBar\\Caption_Maximize_On.pnoimg");					break;
		case IDX_CAPTION_MAXIMIZE_OFF					:	return _T("skin\\SystemBar\\Caption_Maximize_Off.pnoimg");					break;
		case IDX_CAPTION_MAXIMIZE_DOWN					:	return _T("skin\\SystemBar\\Caption_Maximize_Down.pnoimg");				break;
		case IDX_CAPTION_MAXIMIZE_DISABLE				:	return _T("skin\\SystemBar\\Caption_Maximize_Disable.pnoimg");				break;
		case IDX_CAPTION_EXIT_ON						:	return _T("skin\\SystemBar\\Caption_Exit_On.pnoimg");						break;
		case IDX_CAPTION_EXIT_OFF						:	return _T("skin\\SystemBar\\Caption_Exit_Off.pnoimg");						break;
		case IDX_CAPTION_EXIT_DOWN						:	return _T("skin\\SystemBar\\Caption_Exit_Down.pnoimg");					break;
		case IDX_CAPTION_EXIT_DISABLE					:	return _T("skin\\SystemBar\\Caption_Exit_Disable.pnoimg");					break;
		case IDX_CAPTION_RESTORE_ON						:	return _T("skin\\SystemBar\\Caption_Restore_On.pnoimg");					break;
		case IDX_CAPTION_RESTORE_OFF					:	return _T("skin\\SystemBar\\Caption_Restore_Off.pnoimg");					break;
		case IDX_CAPTION_RESTORE_DOWN					:	return _T("skin\\SystemBar\\Caption_Restore_Down.pnoimg");					break;
		case IDX_CAPTION_RESTORE_DISABLE				:	return _T("skin\\SystemBar\\Caption_Restore_Disable.pnoimg");				break;
	}
	return _T("");
}

void CSkinMng::LoadIcons()
{
	DeleteIcons();

	CString strFileName(_T(""));
	CString sModulePath = GetModulePath() + _T("\\");

	for(UINT i=0; i<IDX_ICON_MAX; i++)
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

CString CSkinMng::GetIconFileName(UINT nIconID)
{
	switch( nIconID )
	{
		case IDX_ICON_OK							:	return _T("skin\\ok.ico");						break;
	}
	return _T("");
}

SIZE CSkinMng::GetBitmapSize(UINT nBitmapID)
{
	SIZE size;
	if( nBitmapID >= IDX_SYSTEMICON_MAX )
	{
		size.cx=0;
		size.cy=0;
		return size;
	}

	size.cx = m_infoBitmap[nBitmapID].bitmap.bmWidth;
	size.cy = m_infoBitmap[nBitmapID].bitmap.bmHeight;

	return size;
}

HBITMAP CSkinMng::GetBitmap(UINT nBitmapID)
{
	if( nBitmapID >= IDX_SYSTEMICON_MAX )
		return NULL;

	return m_infoBitmap[nBitmapID].hBitmap;
}

HICON CSkinMng::GetIcon(UINT nIconID, UINT nType)
{
	if( nIconID >= IDX_ICON_MAX ||
		nType > ICON32 )
		return NULL;

	return m_hIcon[nIconID][nType];
}

void CSkinMng::SetRGB(UINT nRGBID, COLORREF cf)
{
	if( nRGBID >= IDX_RGB_MAX )
		return;

	m_cf[nRGBID] = cf;
}

COLORREF CSkinMng::GetRGB(UINT nRGBID)
{
	if( nRGBID >= IDX_RGB_MAX )
		return RGB(0,0,0);

	return m_cf[nRGBID];
}

CFont * CSkinMng::GetFont(UINT nFontID) 
{ 
	if( nFontID >= IDX_FONT_MAX )
		return NULL;

	return m_pFont[nFontID]; 
}

CFont * CSkinMng::SetFont(CWnd* pWnd, UINT nFontID, CString sFaceName, UINT nFontSize, BOOL bBold/*=FALSE*/)
{
	if( nFontID >= IDX_FONT_MAX )
		return NULL;

	CWnd *pMain = pWnd;
	if( !pMain )
		return NULL;	

	// Font Name
	LOGFONT logFont;
	ZeroMemory(&logFont,sizeof(logFont));
	_tcscpy( logFont.lfFaceName, sFaceName );

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

	pMain->SetFont(m_pFont[IDX_FONT_SMALL],true);

	return m_pFont[nFontID];
}

CSize CSkinMng::FormatText(CString& sText, CDC* pDC, int nWidth)
{
	CRect rect(0, 0, nWidth, 20);
	UINT uFlags = DT_CALCRECT | DT_SINGLELINE | DT_MODIFYSTRING | DT_END_ELLIPSIS;

	::DrawText(pDC->GetSafeHdc(), sText.GetBuffer(sText.GetLength() + 4), -1, rect, uFlags);
	sText.ReleaseBuffer();

	return pDC->GetTextExtent(sText);
}

COLORREF CSkinMng::Darker(COLORREF crBase, float fFactor)
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

COLORREF CSkinMng::Lighter(COLORREF crBase, float fFactor) 
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