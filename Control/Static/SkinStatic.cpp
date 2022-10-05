// SkinStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SkinStatic.h"

CSkinStatic::CSkinStatic(void)
{
	m_hBmpDefault  = NULL;
	m_hBmpCapL     = NULL;
	m_hBmpCapM     = NULL;
	m_hBmpCapR     = NULL;
	m_pFont		   = NULL;
	m_bBkgColor	   = FALSE;
	m_bCenter	   = FALSE;	
	m_cfText	   = g_gbl.GetRGB( IDX_RGB_FONT_BLACK );
	m_cfBackGround = g_gbl.GetRGB( IDX_RGB_MAIN_BACKGROUND );

	m_nWidth	   = 0;
	m_nHeight	   = 0;	
	m_dwStyle      = DT_CENTER | DT_VCENTER | DT_SINGLELINE;

	memset( &m_sizeDefault, 0x00, sizeof(SIZE) );
	memset( &m_sizeCapL,    0x00, sizeof(SIZE) );
	memset( &m_sizeCapM,    0x00, sizeof(SIZE) );
	memset( &m_sizeCapR,    0x00, sizeof(SIZE) );
	memset( &m_sizeStatic,  0x00, sizeof(SIZE) );
}


CSkinStatic::~CSkinStatic(void)
{
}

BEGIN_MESSAGE_MAP(CSkinStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CSkinStatic::SetTextStyle( DWORD dwStyle, BOOL bCenter )
{
	m_dwStyle = dwStyle;
	m_bCenter = bCenter;
}


void CSkinStatic::SetBkColor( COLORREF cfBackGround )
{
	m_cfBackGround = cfBackGround;
	m_bBkgColor    = TRUE;
}


void CSkinStatic::SetText( CString strText, int nWidth, int nHeight )
{
	m_strText = strText;
	m_nWidth  = nWidth;
	m_nHeight = nHeight;
}


void CSkinStatic::SetBitmapID( UINT uDefaultImage )
{
	// 각 비트맵의 사이즈 정보를 얻어온다.
	m_sizeDefault = g_gbl.GetBitmapSize( uDefaultImage );

	// 각 비트맵의 핸들을 얻어온다.
	m_hBmpDefault = g_gbl.GetBitmap( uDefaultImage );	
}


void CSkinStatic::SetBitmapID( UINT uCapLImage, UINT uCapMImage, UINT uCapRImage )
{
	// 각 비트맵의 사이즈 정보를 얻어온다.
	m_sizeCapL = g_gbl.GetBitmapSize( uCapLImage );
	m_sizeCapM = g_gbl.GetBitmapSize( uCapMImage );
	m_sizeCapR = g_gbl.GetBitmapSize( uCapRImage );

	// 각 비트맵의 핸들을 얻어온다.
	m_hBmpCapL = g_gbl.GetBitmap( uCapLImage );
	m_hBmpCapM = g_gbl.GetBitmap( uCapMImage );
	m_hBmpCapR = g_gbl.GetBitmap( uCapRImage );
}


void CSkinStatic::SetTextCenter( CDC *pDC, CString strText, DWORD dwStyle )
{
	CRect MsgRect, rc;
	RECT rect = { 0, 0, 0, 0 };
	int nStartX = 0, nStartY = 0, nMsgStartX = 0, nMsgStartY = 0;

	GetClientRect( &rc );
	pDC->DrawText( strText, &rect, dwStyle | DT_CALCRECT );

	nStartY    = rc.Height() / 2 - rect.bottom / 2;
	nMsgStartY = nStartY + rect.bottom; 

	MsgRect.SetRect( nStartX, nStartY, rc.right, nMsgStartY );
	pDC->DrawText( strText, (LPRECT)MsgRect, dwStyle | DT_END_ELLIPSIS | DT_WORD_ELLIPSIS );
}


void CSkinStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	rect.left   = 0;
	rect.top    = 0;
	rect.right  = m_sizeStatic.cx;
	rect.bottom = m_sizeStatic.cy;
	
	CDC *pDC = &dc;
	CDC MemDC;
	MemDC.CreateCompatibleDC( pDC );

	CBitmap *pBitmap    = NULL;
	CBitmap *pOldBitmap = NULL;

	// Bitmap이 1개이면 Bitmap 1개삽입
	if( m_hBmpDefault )
	{	
		pBitmap = CBitmap::FromHandle( m_hBmpDefault );
		pOldBitmap = MemDC.SelectObject( pBitmap );

		pDC->StretchBlt( 0, 0, m_sizeStatic.cx, m_sizeStatic.cy, &MemDC, 0, 0, m_sizeDefault.cx, m_sizeDefault.cy, SRCCOPY );
		MemDC.SelectObject( pOldBitmap );
	}
	// Bitmap이 3개이면 Bitmap 3개삽입
	else if( m_hBmpCapL && m_hBmpCapM && m_hBmpCapR )
	{
		int x = 0, y = 0, cx = 0, cy = 0;
		
		// 캡션 왼쪽 비트맵
		cx = m_sizeCapL.cx;
		cy = m_sizeCapL.cy;

		pBitmap = CBitmap::FromHandle( m_hBmpCapL );
		pOldBitmap = MemDC.SelectObject( pBitmap );

		pDC->BitBlt( x, y, cx, cy, &MemDC, 0, 0, SRCCOPY );

		// 캡션 중앙 비트맵
		x += cx;
		cx = m_sizeStatic.cx - m_sizeCapL.cx - m_sizeCapR.cx; 
		cy = m_sizeCapM.cy;

		pBitmap = CBitmap::FromHandle( m_hBmpCapM );
		MemDC.SelectObject( pBitmap );

		pDC->StretchBlt( x, y, cx, cy, &MemDC, 0, 0, m_sizeCapM.cx, m_sizeCapM.cy, SRCCOPY );

		// 캡션 오른쪽 비트맵
		x += cx;
		cx = m_sizeCapR.cx;
		cy = m_sizeCapR.cy;

		pBitmap = CBitmap::FromHandle( m_hBmpCapR );
		MemDC.SelectObject( pBitmap );

		pDC->BitBlt( x, y, cx, cy, &MemDC, 0, 0, SRCCOPY );
		MemDC.SelectObject( pOldBitmap );
	}
	//Bitmap이 Setting되지 않고 Background 색상이 Setting 되었으면 색상 삽입
	else if( m_bBkgColor )
	{
		CBrush pBrush;
		pBrush.CreateSolidBrush( m_cfBackGround );		
		pDC->FillRect( &rect, &pBrush );		
	}

	if( m_strText != _T("") )
	{
		pDC->SetBkMode( TRANSPARENT );
		pDC->SelectObject( m_pFont );
		pDC->SetTextColor( m_cfText );

		if( m_nWidth != 0 && m_nHeight != 0 )
			pDC->TextOut( rect.left + m_nWidth, rect.top + m_nHeight, m_strText );
		else
		{
			if( m_nHeight != 0 )
				rect.top += m_nHeight;
			
			if( !m_bCenter )	pDC->DrawText( m_strText, rect, m_dwStyle );
			else				SetTextCenter( pDC, m_strText, m_dwStyle  );
		}
	}

	ReleaseDC( pDC );
}