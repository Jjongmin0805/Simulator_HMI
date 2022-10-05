#include "stdafx.h"
#include "SkinProgressbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSkinProgressbar::CSkinProgressbar()
{
	// Default range of the control
	m_dwWidth  = 0;
	m_dwHeight = 0;
	m_nLower   = 0;
	m_nUpper   = 100;
	CalcRange();

	m_hBmpBar   = NULL;
	m_hBmpFrame = NULL;
	m_pFont		= NULL;

	memset( &m_sizeFrame, 0x00, sizeof(SIZE) );

	m_nPos		   = 0;			// Default position	
	m_nStep		   = 10;		// Default step	
	m_clrTextOnBar = g_gbl.GetRGB( IDX_RGB_FONT_BLACK );
}

CSkinProgressbar::~CSkinProgressbar()
{	
}

BEGIN_MESSAGE_MAP(CSkinProgressbar, CProgressCtrl)
	//{{AFX_MSG_MAP(CSkinProgressbar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CSkinProgressbar::SetBitmapID( UINT uFrameImage, UINT uBarImage )
{
	// 각 비트맵의 핸들을 얻어온다.
	m_hBmpFrame  = g_gbl.GetBitmap( uFrameImage );
	m_hBmpBar    = g_gbl.GetBitmap( uBarImage   );

	m_sizeFrame  = g_gbl.GetBitmapSize( uFrameImage );
	SIZE  sizBar = g_gbl.GetBitmapSize( uBarImage );

	// Bar는 몇등분 해서 진행할 것인지 셋팅	
	m_dwWidth  = (DWORD)sizBar.cx;
	m_dwHeight = (DWORD)sizBar.cy;

	return;
}


void CSkinProgressbar::OnPaint() 
{
	// If there is no bitmap loaded
	if( m_hBmpBar == NULL || m_hBmpFrame == NULL ) 
	{
		CProgressCtrl::OnPaint();
		return;
	}

	CRect		rcCtrl, rcFullCtrl;
	DWORD		dwStyle			= 0;
	BOOL		bVertical		= FALSE;
	float		f				= 0;
	int			nPercentage		= 0;
	HDC			hdcMem			= NULL;
	HDC			hdcTemp			= NULL;
	HBITMAP		hOldBitmap		= NULL;
	HBITMAP		hbmpTemp		= NULL;
	HBITMAP		hOldTempBitmap	= NULL;
	CPaintDC	dc(this);

	GetClientRect(rcCtrl);
	GetClientRect(rcFullCtrl);

	// Set Frame
	CDC *pDC = &dc;
	CDC MemDC;
	MemDC.CreateCompatibleDC( pDC );

	CBitmap *pBitmap = CBitmap::FromHandle( m_hBmpFrame );
	CBitmap* pOldBitmap = MemDC.SelectObject( pBitmap );

	BITMAP bmpFrame;
	pBitmap->GetBitmap( &bmpFrame );	
	dc.BitBlt( rcFullCtrl.left, rcFullCtrl.top, m_sizeFrame.cx, m_sizeFrame.cy, &MemDC, 0, 0, SRCCOPY );
	
	///////////////////////////// 가로 세로 스타일 검사

	dwStyle = GetStyle();
	bVertical = (dwStyle & PBS_VERTICAL) == PBS_VERTICAL;

	// Has border ?
	if ((dwStyle & WS_BORDER) == WS_BORDER)
	{
		CBrush brBtnShadow(RGB(0, 0, 0));
		dc.FrameRect(rcCtrl, &brBtnShadow);
		rcCtrl.DeflateRect(1, 1);
	} // if

	/////////////////////////////

	// Set Bar
	hdcMem = ::CreateCompatibleDC(dc.m_hDC);

	// Select bitmap
	hOldBitmap = (HBITMAP)::SelectObject(hdcMem, m_hBmpBar);

	// Create temporary DC & bitmap
	hdcTemp = ::CreateCompatibleDC(dc.m_hDC);

	hbmpTemp = ::CreateCompatibleBitmap(hdcMem, rcCtrl.Width(), rcCtrl.Height());
	hOldTempBitmap = (HBITMAP)::SelectObject(hdcTemp, hbmpTemp);

	///////////////////////////// % 와 Bar의 영역 계산

	// Calculate control's percentage to draw
	nPercentage = (int)((100.0/m_nRange)*(abs(m_nLower)+m_nPos));

	// Adjust rectangle to draw on screen
	if (bVertical)
	{
		f = ((float)(rcCtrl.Height())/100)*nPercentage;
		if ((rcCtrl.bottom - (int)f) < rcCtrl.top)
			rcCtrl.top += 1;
		else
			rcCtrl.top = rcCtrl.bottom - (int)f;
	} // if
	else
	{
		f = ((float)(rcCtrl.Width())/100)*nPercentage;
		if ((rcCtrl.left + (int)f) > rcCtrl.right)
			rcCtrl.right -= 1;
		else
			rcCtrl.right = rcCtrl.left + (int)f;
	} // else

	// Tile the bitmap into the temporary rectangle
	TileBitmap(hdcTemp, hdcMem, rcCtrl);

	/////////////////////////////

	// Copy from temporary DC to screen (only the percentage rectangle)
	if (rcCtrl.IsRectEmpty() == FALSE)
		::BitBlt(dc.m_hDC, rcCtrl.left, rcCtrl.top, rcCtrl.Width(), rcCtrl.Height(), hdcTemp, 0, 0, SRCCOPY);

	//Set Text
	GetClientRect(rcCtrl);	//제거하면 Bar위에 % Text 발생
	OnDrawText(&dc, nPercentage, rcCtrl, rcCtrl, bVertical);

	// Restore old selected bitmaps
	::SelectObject(hdcTemp, hOldTempBitmap);
	::SelectObject(hdcMem, hOldBitmap);
	MemDC.SelectObject( pOldBitmap );
	ReleaseDC( pDC );

} // End of OnPaint


void CSkinProgressbar::TileBitmap( HDC hdcDest, HDC hdcSrc, CRect rect )
{
	int nHLoop  = 0;
	int nVLoop  = 0;
	int nHTiles = 0;
	int nVTiles = 0;

	// Calculate number of horizontal tiles
	nHTiles = (rect.Width() / m_dwWidth);
	if (rect.Width() % m_dwWidth != 0) nHTiles++;
	// Calculate number of vertical tiles
	nVTiles = (rect.Height() / m_dwHeight);
	if (rect.Height() % m_dwHeight != 0) nVTiles++;

	// Tile bitmap horizontally
	for (nHLoop = 0; nHLoop < nHTiles; nHLoop++)
	{
		// Tile bitmap vertically
		for (nVLoop = 0; nVLoop < nVTiles; nVLoop++)
		{
			::BitBlt(hdcDest, (nHLoop * m_dwWidth), (nVLoop * m_dwHeight), m_dwWidth, m_dwHeight, hdcSrc, 0, 0, SRCCOPY);
		} // for
	} // for
} // End of TileBitmap

void CSkinProgressbar::CalcRange()
{
	m_nRange = abs(m_nUpper - m_nLower);
	// Avoid divide by zero
	if (m_nRange == 0) m_nRange = 1;
} // End of CalcRange

void CSkinProgressbar::SetRange(int nLower, int nUpper)
{
	m_nLower = nLower;
	m_nUpper = nUpper;
	CalcRange();

	CProgressCtrl::SetRange(nLower, nUpper);
} // End of SetRange

int CSkinProgressbar::SetStep(int nStep)
{
	m_nStep = nStep;
	return CProgressCtrl::SetStep(nStep);
} // End Of SetStep

int CSkinProgressbar::SetPos(int nPos)
{
	// Bound checking
	if (nPos < m_nLower) nPos = m_nLower;
	if (nPos > m_nUpper) nPos = m_nUpper;

	m_nPos = nPos;
	return CProgressCtrl::SetPos(nPos);
} // End of SetPos

int CSkinProgressbar::StepIt()
{
	m_nPos += m_nStep;

	// Bound checking
	if (m_nPos > m_nUpper) 
	{
		m_nPos = m_nLower + (m_nPos - m_nUpper);

		GetParent()->Invalidate();
	}
	return CProgressCtrl::StepIt();
} // End of StepIt

void CSkinProgressbar::OnDrawText(CDC* pDC, int nPercentage, CRect rcCtrl, CRect rcProgress, BOOL bVertical)
{
	CString	strText;

	if( m_strText == _T("") )
		strText.Format( _T("%d%%"), nPercentage );
	else
		strText = m_strText;

	pDC->SelectObject( m_pFont );
	pDC->SetTextColor( m_clrTextOnBar );

	pDC->SetBkMode( TRANSPARENT );
	pDC->DrawText( strText, -1, rcProgress, DT_SINGLELINE | DT_VCENTER | DT_CENTER );
}