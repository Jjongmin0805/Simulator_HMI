// SkinButton.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "SkinButton.h"

// CSkinButton

IMPLEMENT_DYNAMIC(CSkinButton, CButton)

CSkinButton::CSkinButton()
{
	m_bToolTip     = FALSE;
	m_bTracking    = FALSE;
	m_bHover       = FALSE;

	m_hBmpDefault  = NULL;
	m_hBmpDown     = NULL;
	m_hBmpOver     = NULL;
	m_pFont		   = NULL;
	m_pToolTipFont = NULL;
	m_cfText	   = g_gbl.GetRGB( IDX_RGB_FONT_BLACK );

	m_nWidth	   = 0;
	m_nHeight	   = 0;

	memset( &m_sizeDefault, 0x00, sizeof(SIZE) );
	memset( &m_sizeDown,    0x00, sizeof(SIZE) );
	memset( &m_sizeOver,    0x00, sizeof(SIZE) );
}

CSkinButton::~CSkinButton()
{
	if( m_hBmpDefault)
	{
		::DeleteObject( m_hBmpDefault );
		m_hBmpDefault = NULL;
	}

}


BEGIN_MESSAGE_MAP(CSkinButton, CButton)	
	ON_WM_MOUSEMOVE()
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave )
	ON_MESSAGE( WM_MOUSEHOVER, OnMouseHover )	
END_MESSAGE_MAP()

// CSkinButton 메시지 처리기입니다.

void CSkinButton::OnMouseMove( UINT nFlags, CPoint point )
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if( !m_bTracking )
	{
		TRACKMOUSEEVENT tme;

		tme.cbSize = sizeof(tme);
		tme.hwndTrack = this->m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}
	
	CButton::OnMouseMove( nFlags, point );
}


LRESULT CSkinButton::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	m_bTracking = FALSE;
	m_bHover    = FALSE;

	RedrawWindow();	
	return TRUE;
}


LRESULT CSkinButton::OnMouseHover( WPARAM wParam, LPARAM lParam )
{
	m_bHover = TRUE;

	RedrawWindow();
	return TRUE;
}


void CSkinButton::SetBitmapID( UINT uDefaultImage, UINT uDownImage, UINT uOverImage )
{
	//// 각 비트맵의 사이즈 정보를 얻어온다.
	//m_sizeDefault = g_gbl.GetBitmapSize( uDefaultImage );
	//m_sizeDown	  = g_gbl.GetBitmapSize( uDownImage    );
	//m_sizeOver	  = g_gbl.GetBitmapSize( uOverImage    );

	//// 각 비트맵의 핸들을 얻어온다.
	//m_hBmpDefault = g_gbl.GetBitmap( uDefaultImage );
	//m_hBmpDown    = g_gbl.GetBitmap( uDownImage	   );
	//m_hBmpOver	  = g_gbl.GetBitmap( uOverImage	   );


	CBitmap bmp[3];
	bmp[0].LoadMappedBitmap(uDefaultImage);
	bmp[1].LoadMappedBitmap(uDownImage);
	bmp[2].LoadMappedBitmap(uOverImage);
	//bmp[3].LoadMappedBitmap(uComboCenLImage);

	m_hBmpDefault = (HBITMAP)bmp[0].Detach();
	m_hBmpDown = (HBITMAP)bmp[1].Detach();
	m_hBmpOver = (HBITMAP)bmp[2].Detach();
	//m_hBmpComboCenL = (HBITMAP)bmp[3].Detach();

	bmp[0].DeleteObject();
	bmp[1].DeleteObject();
	bmp[2].DeleteObject();

	CSize size;
	BITMAP	bitmap;

	::ZeroMemory(&bitmap, sizeof(BITMAP));
	::GetObject(m_hBmpDefault, sizeof(BITMAP), &bitmap);
	size.cx = bitmap.bmWidth;
	size.cy = bitmap.bmHeight;
	m_sizeDefault = size;

	::ZeroMemory(&bitmap, sizeof(BITMAP));
	::GetObject(m_hBmpDown, sizeof(BITMAP), &bitmap);
	size.cx = bitmap.bmWidth;
	size.cy = bitmap.bmHeight;
	m_sizeDown = size;

	::ZeroMemory(&bitmap, sizeof(BITMAP));
	::GetObject(m_hBmpOver, sizeof(BITMAP), &bitmap);
	size.cx = bitmap.bmWidth;
	size.cy = bitmap.bmHeight;
	m_sizeOver = size;

}

void CSkinButton::SetBitmap( CString strDefaultImage, CString strDownImage, CString strOverImage )
{
	CImage cPngImage;
	CString sModulePath = g_gbl.GetModulePath() + _T("\\");
	CString strFileName;

	CSize size;
	BITMAP	bitmap;
	
	strFileName.Format(_T("%s\\%s"),sModulePath,strDefaultImage);
	cPngImage.Load( strFileName );
	m_hBmpDefault = cPngImage.Detach();
	::GetObject( m_hBmpDefault, sizeof(BITMAP), &bitmap );
	size.cx = bitmap.bmWidth;
	size.cy = bitmap.bmHeight;
	m_sizeDefault = size;

	::ZeroMemory(& bitmap, sizeof(BITMAP) );
	strFileName.Format(_T("%s\\%s"),sModulePath,strDownImage);
	cPngImage.Load( strFileName );
	m_hBmpDown = cPngImage.Detach();
	::GetObject( m_hBmpDown, sizeof(BITMAP), &bitmap );
	size.cx = bitmap.bmWidth;
	size.cy = bitmap.bmHeight;
	m_sizeDown = size;

	::ZeroMemory(& bitmap, sizeof(BITMAP) );
	strFileName.Format(_T("%s\\%s"),sModulePath,strOverImage);
	cPngImage.Load( strFileName );
	m_hBmpOver = cPngImage.Detach();
	::GetObject( m_hBmpOver, sizeof(BITMAP), &bitmap );
	size.cx = bitmap.bmWidth;
	size.cy = bitmap.bmHeight;
	m_sizeOver = size;

	::ZeroMemory(& bitmap, sizeof(BITMAP) );
	return;
}

void CSkinButton::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	CDC MemDC;
	MemDC.CreateCompatibleDC( pDC );

	CRect rect( lpDrawItemStruct->rcItem );
	CBitmap *pBitmap;
	SIZE     sizeBitmap;	
		
	if( lpDrawItemStruct->itemState & ODS_SELECTED )
	{
		pBitmap = CBitmap::FromHandle( m_hBmpDown );
		sizeBitmap = m_sizeDown;
	}
	else
	{
		if( m_bHover )
		{
			pBitmap = CBitmap::FromHandle( m_hBmpOver );
			sizeBitmap = m_sizeOver;
		}
		else
		{
			pBitmap = CBitmap::FromHandle( m_hBmpDefault );
			sizeBitmap = m_sizeDefault;
		}
	}	

	CBitmap* pOldBitmap = MemDC.SelectObject( pBitmap );	
	//pDC->BitBlt( 0, 0, sizeBitmap.cx, sizeBitmap.cy, &MemDC, 0, 0, SRCCOPY );
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, sizeBitmap.cx, sizeBitmap.cy, SRCCOPY);

	
	pDC->SetBkMode( TRANSPARENT );	
	pDC->SetTextColor( m_cfText );
	pDC->SelectObject( m_pFont );

	if( m_nWidth != 0 && m_nHeight != 0 )
		pDC->TextOut( rect.left + m_nWidth, rect.top + m_nHeight, m_strText );
	else
		pDC->DrawText( m_strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	
	MemDC.SelectObject( pOldBitmap );
	ReleaseDC( pDC );
}


void CSkinButton::SetButtonText ( CString strText, int nWidth, int nHeight )
{
	m_strText = strText;
	m_nWidth  = nWidth;
	m_nHeight = nHeight;
}


void CSkinButton::SetToolTipText( CString strText )
{
	m_bToolTip = TRUE;

	CRect rect;
	rect.left   = 0;
	rect.top    = 0;
	rect.right  = m_sizeDefault.cx;
	rect.bottom = m_sizeDefault.cy;
	
	m_ToolTip.Create( this, 0 );

	if( m_pToolTipFont )
	{
		(FromHandle(m_ToolTip))->SetFont( m_pToolTipFont );
	}

	m_ToolTip.AddTool( this, strText, &rect, 1 );
}


void CSkinButton::PreSubclassWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SetButtonStyle( GetButtonStyle() | BS_OWNERDRAW );		

	CButton::PreSubclassWindow();
}


BOOL CSkinButton::PreTranslateMessage( MSG* pMsg ) 
{
	// TODO: Add your specialized code here and/or call the base class

	if( m_bToolTip )
	{
		if( pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST )
		{
			m_ToolTip.RelayEvent(pMsg);
		}
	}
	
	return CButton::PreTranslateMessage( pMsg );
}