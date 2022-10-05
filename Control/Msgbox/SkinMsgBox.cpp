// SkinMsgBox.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SkinMsgBox.h"

// CSkinMsgBox 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSkinMsgBox, CSkinPopupDialog)

CSkinMsgBox::CSkinMsgBox( UINT nResourceID, CWnd* pParent /*=NULL*/ )
	: CSkinPopupDialog( nResourceID, pParent )
{
	m_nSelectBtn   =  0;	
	m_nRet		   =  0;
	m_nStep		   =  0;
	m_nSymbolID    = -1;
	m_nButtonType  = -1;
	m_bMsgBoxClose = TRUE;

	m_sstIcon	      = NULL;
	m_sstMsg	      = NULL;
	m_pFontMsg		  = NULL;
	m_pFontBtn		  = NULL;
	m_pFontBtnTooltip = NULL;
}

CSkinMsgBox::~CSkinMsgBox()
{
}

void CSkinMsgBox::DoDataExchange(CDataExchange* pDX)
{
	CSkinPopupDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSkinMsgBox, CSkinPopupDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CSkinMsgBox 메시지 처리기입니다.

int CSkinMsgBox::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( CSkinPopupDialog::OnCreate(lpCreateStruct) == -1 )
		return -1;	

	CString strFontName = g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 22 );			// 굴림
	CRect rect, rectStaticSymbol, rectStaticMsg, rectStaticBtnSection, rectBtn;
	SIZE szStaticSymbol, szStaticMsg;

	GetClientRect(rect);

	// Symbol size 구하기
	UINT uSymbolWidth = 0, uSymbolHeight = 0;
	SIZE szSymbol = g_gbl.GetBitmapSize( m_nSymbolID );
	uSymbolWidth  = szSymbol.cx;
	uSymbolHeight = szSymbol.cy;

	// Button size 구하기
	UINT uBtnWidth = 0, uBtnHeight = 0, uBtnSectionHeight = 0, uBtnMargin = 0;
	SIZE szBtn = g_gbl.GetBitmapSize( IDX_PNG_BTN_MSGBOX );
	uBtnWidth  = szBtn.cx;
	uBtnHeight = szBtn.cy;
	uBtnSectionHeight = uBtnHeight * 2;		// 버튼 영역 높이
	uBtnMargin = uBtnWidth / 2 + 10;		// 버튼 시작점간 여백
	
	// Symbol 생성
	rectStaticSymbol.left   = MARGIN_CONTROL;
	rectStaticSymbol.top    = ((rect.bottom - uBtnSectionHeight) - uSymbolHeight) / 2 + MARGIN_CONTROL * 2;
	rectStaticSymbol.right  = szStaticSymbol.cx	=	uSymbolWidth;
	rectStaticSymbol.bottom = rectStaticSymbol.top + uSymbolHeight;
	szStaticSymbol.cy       = uSymbolHeight;

	m_sstIcon = new CSkinStatic;
	m_sstIcon->SetSizeControl( szStaticSymbol );
	m_sstIcon->Create( _T(""), WS_CHILD | WS_VISIBLE | SS_CENTER, rectStaticSymbol, this );
	
	if( m_nSymbolID > -1 )
		m_sstIcon->SetBitmapID( m_nSymbolID );	

	// Message section 생성
	m_pFontMsg = SetFont( strFontName, 10 , FALSE );

	rectStaticMsg.left   = uSymbolWidth + MARGIN_CONTROL * 2;
	rectStaticMsg.right  = szStaticMsg.cx	=	rect.right - MARGIN_CONTROL;
	rectStaticMsg.bottom = szStaticMsg.cy	=	rect.bottom - uBtnHeight - MARGIN_CONTROL;	

	m_sstMsg = new CSkinStatic;
	m_sstMsg->SetSizeControl( szStaticMsg );
	m_sstMsg->Create( _T(""), WS_CHILD | WS_VISIBLE | SS_CENTER, rectStaticMsg, this );
	m_sstMsg->SetTextStyle( DT_LEFT, TRUE );
	m_sstMsg->SetTextFont( m_pFontMsg );
		
	m_sstMsg->SetText( m_strMessage );
	m_sstMsg->SetTextColor( g_gbl.GetRGB( IDX_RGB_FONT_BLACK ) );
		
	// Button 생성
	m_pFontBtn		  = SetFont( strFontName, 10 , FALSE );
	m_pFontBtnTooltip = SetFont( strFontName,  8 , FALSE );

	rectBtn.left   = rect.right / 2 - uBtnMargin * m_nSelectBtn;
	rectBtn.top    = rect.bottom - uBtnHeight - MARGIN_CONTROL;
	rectBtn.right  = rectBtn.left + uBtnWidth;
	rectBtn.bottom = rectBtn.top  + uBtnHeight;

	for( int nBtn = 0; nBtn < m_nSelectBtn; nBtn++ )
	{
		m_sbtnSelect[ nBtn ] = new CSkinButton;
		m_sbtnSelect[ nBtn ]->Create(_T("BTN_MSGBOX"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, rectBtn, this, DEFAULT_BUTTON_ID + nBtn );
		m_sbtnSelect[ nBtn ]->SetBitmapID( IDX_PNG_BTN_MSGBOX, IDX_PNG_BTN_MSGBOX_DOWN, IDX_PNG_BTN_MSGBOX_OVER );
		m_sbtnSelect[ nBtn ]->SetFont( m_pFontBtn, m_pFontBtnTooltip );
		m_sbtnSelect[ nBtn ]->SetButtonText( m_saBtnNames.GetAt( nBtn ) );

		rectBtn.left  += rect.right / 5 + MARGIN_CONTROL * 2;
		rectBtn.right += rect.right / 5 + MARGIN_CONTROL * 2;
	}

	if( m_bMsgBoxClose )
		SetTimer( 1, 1000, NULL );
	
	CenterWindow();	
	return 0;
}


BOOL CSkinMsgBox::OnCommand( WPARAM wParam, LPARAM lParam )
{
	if( wParam >= DEFAULT_BUTTON_ID && wParam < DEFAULT_BUTTON_ID + (UINT)m_nSelectBtn )
	{
		for( int i = 0; i < m_nSelectBtn; i++ )
		{
			if( DEFAULT_BUTTON_ID + i == wParam )
			{
				switch( m_nButtonType )
				{
				case MB_OK:
					if(i == 0)
						m_nRet = IDOK;
					break;
				case MB_OKCANCEL:
					if(i == 0)
						m_nRet = IDOK;
					else if(i == 1)
						m_nRet = IDCANCEL;
					break;
				case MB_ABORTRETRYIGNORE:
					if(i == 0)
						m_nRet = IDABORT;
					else if(i == 1)
						m_nRet = IDRETRY;
					else if(i == 2)
						m_nRet = IDIGNORE;
					break;
				case MB_YESNOCANCEL:
					if(i == 0)
						m_nRet = IDYES;
					else if(i == 1)
						m_nRet = IDNO;
					else if(i == 2)
						m_nRet = IDCANCEL;
					break;
				case MB_YESNO:
					if(i == 0)
						m_nRet = IDYES;
					else if(i == 1)
						m_nRet = IDNO;
					break;
				case MB_RETRYCANCEL:
					if(i == 0)
						m_nRet = IDRETRY;
					else if(i == 1)
						m_nRet = IDCANCEL;
					break;
#if(WINVER >= 0x0500)
				case MB_CANCELTRYCONTINUE:
					if(i == 0)
						m_nRet = IDCANCEL;
					else if(i == 1)
						m_nRet = IDTRYAGAIN;
					else if(i == 2)
						m_nRet = IDCONTINUE;
					break;
#endif
				}
			}
		}

		PostMessage( WM_CLOSE, NULL, NULL );
	}

	return CSkinPopupDialog::OnCommand( wParam, lParam );
}


void CSkinMsgBox::OnDestroy()
{
	KillTimer( 1 );

	if( m_saBtnNames.GetCount() > 0 )
		m_saBtnNames.RemoveAll();

	if( m_sstIcon )
	{
		delete m_sstIcon;
		m_sstIcon = NULL;
	}

	if( m_sstMsg )
	{
		delete m_sstMsg;
		m_sstMsg = NULL;
	}

	if( m_pFontMsg )
	{
		delete m_pFontMsg;
		m_pFontMsg = NULL;
	}

	if( m_pFontBtn )
	{
		delete m_pFontBtn;
		m_pFontBtn = NULL;
	}

	if( m_pFontBtnTooltip )
	{
		delete m_pFontBtnTooltip;
		m_pFontBtnTooltip = NULL;
	}

	for( int i = 0; i < m_nSelectBtn; i++ )
	{
		if( m_sbtnSelect[ i ] != NULL )
			delete m_sbtnSelect[ i ];

		m_sbtnSelect[ i ] = NULL;
	}

	CSkinPopupDialog::OnDestroy();
}


void CSkinMsgBox::OnTimer( UINT_PTR nIDEvent )
{
	switch( nIDEvent )
	{
	case 1:
		{	m_nStep++;
			
			if( m_nStep == 5 )
				PostMessage( WM_CLOSE, 0, 0 );
		}
		break;

	default:
		break;
	}
}


CFont * CSkinMsgBox::SetFont( CString strFaceName, UINT nFontSize, BOOL bBold/*=FALSE*/ )
{	
	// Font Name
	LOGFONT logFont;
	ZeroMemory( &logFont, sizeof(logFont) );
	_tcscpy_s( logFont.lfFaceName, strFaceName );

	// Font Style
	logFont.lfItalic = FALSE;
	
	if( bBold )
		logFont.lfWeight = FW_BOLD;
	else
		logFont.lfWeight = FW_NORMAL;

	// Font Size
	HDC hdc = ::GetDC( m_hWnd );
	
	if( !hdc ) 
		logFont.lfHeight = nFontSize;
	else 
		logFont.lfHeight = -MulDiv( nFontSize, GetDeviceCaps( hdc, LOGPIXELSY ), 72 );
	
	::ReleaseDC( m_hWnd, hdc );

	// New Font
	CFont *pFont = new CFont;

	if( !pFont->CreateFontIndirect( &logFont ) )
	{
		delete pFont;
		pFont = NULL;
	}

	return pFont;
}


void CSkinMsgBox::SetMBStyle( UINT uIconType, UINT uButtonType )
{	
	if     ( uIconType == MB_ICONERROR       )		m_nSymbolID = IDX_PNG_STC_MSGBOX_ERROR;		// ICON: ERROR	
	else if( uIconType == MB_ICONWARNING     )		m_nSymbolID = IDX_PNG_STC_MSGBOX_WARNING;	// ICON: WARNING
	else if( uIconType == MB_ICONQUESTION    )		m_nSymbolID = IDX_PNG_STC_MSGBOX_QUESTION;	// ICON: QUESTION
	else if( uIconType == MB_ICONINFORMATION )		m_nSymbolID = IDX_PNG_STC_MSGBOX_INFO;		// ICON: INFORMATION
	else											m_nSymbolID = IDX_PNG_STC_MSGBOX_INFO;		// ICON: INFORMATION

	if( uButtonType == MB_RETRYCANCEL )
	{
		m_nSelectBtn = 2;
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 24 ) );		// 재시도
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 25 ) );		// 취소
	}
	else if( uButtonType == MB_YESNO )
	{
		m_nSelectBtn = 2;
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 26 ) );		// 예
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 27 ) );		// 아니오
	}
	else if( uButtonType == MB_YESNOCANCEL )
	{
		m_nSelectBtn = 3;
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 26 ) );		// 예
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 27 ) );		// 아니오
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 25 ) );		// 취소
	}
	else if( uButtonType == MB_ABORTRETRYIGNORE )
	{
		m_nSelectBtn = 3;
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 28 ) );		// 중지
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 24 ) );		// 재시도
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 29 ) );		// 무시
	}
	else if(uButtonType == MB_OKCANCEL)
	{
		m_nSelectBtn = 2;
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 30 ) );		// 확인
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 25 ) );		// 취소
	}
#if(WINVER >= 0x0500)
	else if(uButtonType == MB_CANCELTRYCONTINUE)
	{
		m_nSelectBtn = 3;
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 25 ) );		// 취소
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 24 ) );		// 재시도
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 31) );		// 계속	
	}
#endif
	else //	MB_OK
	{
		m_nSelectBtn = 1;
		m_saBtnNames.Add( g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 30 ) );		// 확인
	}

	m_nButtonType = uButtonType;
}