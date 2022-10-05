// SkinCheckbox.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "SkinCheckbox.h"

// CSkinCheckbox

IMPLEMENT_DYNAMIC(CSkinCheckbox, CButton)

CSkinCheckbox::CSkinCheckbox()
{
	m_hBmpChkDefault  = NULL;
	m_hBmpChkSelected = NULL;
	m_hBmpChkDisable  = NULL;
	m_uCheckStatus    = CHECKBOX_NORMAL;

	memset( &m_sizeChkDefault,  0x00, sizeof(SIZE) );
	memset( &m_sizeChkSelected, 0x00, sizeof(SIZE) );
	memset( &m_sizeChkDisable,  0x00, sizeof(SIZE) );

	m_pFont_Text = NULL;

	m_nItem = -1;
	m_nSubItem = -1;

	m_colorText = RGB(0, 0, 0);
	m_colorBg = RGB(255, 255, 255);
}

CSkinCheckbox::~CSkinCheckbox()
{
}


BEGIN_MESSAGE_MAP(CSkinCheckbox, CButton)
	ON_WM_LBUTTONUP ()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

// CSkinCheckbox 메시지 처리기입니다.

void CSkinCheckbox::OnLButtonUp(UINT nFlags, CPoint point)
{
	if( m_uCheckStatus == CHECKBOX_DISABLE )
	{
		CButton::OnLButtonUp( nFlags, point );
		return;
	}

	m_uCheckStatus = ( m_uCheckStatus + 1 ) % 2;

	if (m_nItem > -1)
	{
		GetParent()->SendMessage(WM_CHECKBOX2LIST_MSG, m_nItem, m_nSubItem);
	}
	
	CButton::OnLButtonUp( nFlags, point );
}


void CSkinCheckbox::OnMouseHover( UINT nFlags, CPoint point )
{
}


void CSkinCheckbox::OnMouseLeave()
{
}

void CSkinCheckbox::SetBitmapID( UINT uNormalImage, UINT uCheckImage, UINT uDiableImage )
{
	// 각 비트맵의 사이즈 정보를 얻어온다.
	//m_sizeChkDefault	= g_gbl.GetBitmapSize( uNormalImage );
	//m_sizeChkSelected	= g_gbl.GetBitmapSize( uCheckImage  );
	//m_sizeChkDisable	= g_gbl.GetBitmapSize( uDiableImage );

	//// 각 비트맵의 핸들을 얻어온다.
	//m_hBmpChkDefault	= g_gbl.GetBitmap( uNormalImage );
	//m_hBmpChkSelected   = g_gbl.GetBitmap( uCheckImage	);
	//m_hBmpChkDisable	= g_gbl.GetBitmap( uDiableImage	);

	CBitmap bmp[3];
	bmp[0].LoadMappedBitmap(uNormalImage);
	bmp[1].LoadMappedBitmap(uCheckImage);
	bmp[2].LoadMappedBitmap(uDiableImage);
	//bmp[3].LoadMappedBitmap(uComboCenLImage);

	m_hBmpChkDefault = (HBITMAP)bmp[0].Detach();
	m_hBmpChkSelected = (HBITMAP)bmp[1].Detach();
	m_hBmpChkDisable = (HBITMAP)bmp[2].Detach();
	//m_hBmpComboCenL = (HBITMAP)bmp[3].Detach();

	bmp[0].DeleteObject();
	bmp[1].DeleteObject();
	bmp[2].DeleteObject();
}


void CSkinCheckbox::PreSubclassWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SetButtonStyle( GetButtonStyle() | BS_OWNERDRAW );		

	CButton::PreSubclassWindow();
}


void CSkinCheckbox::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	CDC MemDC;
	MemDC.CreateCompatibleDC( pDC );

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));

	CRect r;
	GetClientRect(&r);


	CBrush brush;
	brush.CreateSolidBrush(m_colorBg);

	pDC->FillRect(r, &brush);

	
	CRect rect( lpDrawItemStruct->rcItem );
	CBitmap *pBitmap;
	BITMAP	bitmap;
	SIZE     sizeBitmap;
	sizeBitmap.cx = 0;
	sizeBitmap.cy = 0;

	if( m_uCheckStatus == CHECKBOX_DISABLE )
	{
		pBitmap = CBitmap::FromHandle( m_hBmpChkDisable );
		pBitmap->GetBitmap(&bitmap);
		sizeBitmap.cx = bitmap.bmWidth;
		sizeBitmap.cy = bitmap.bmHeight;
		pDC->SetTextColor(RGB(115, 115, 115));
	}
	else if( m_uCheckStatus == CHECKBOX_CHECKED )
	{
		pBitmap = CBitmap::FromHandle( m_hBmpChkSelected );
		//sizeBitmap = m_sizeChkSelected;
		pBitmap->GetBitmap(&bitmap);
		sizeBitmap.cx = bitmap.bmWidth;
		sizeBitmap.cy = bitmap.bmHeight;
		
	}
	else
	{
		pBitmap = CBitmap::FromHandle(m_hBmpChkDefault);
		//sizeBitmap = m_sizeChkDefault;
		pBitmap->GetBitmap(&bitmap);
		sizeBitmap.cx = bitmap.bmWidth;
		sizeBitmap.cy = bitmap.bmHeight;
	}
	r.left += sizeBitmap.cx +5;

	CFont* pFont = pDC->SelectObject(m_pFont_Text);

	pDC->SetTextColor(m_colorText);
	CString strName;
	GetWindowText(strName);
	pDC->DrawText(strName, r, DT_LEFT | DT_VCENTER);

	CBitmap* pOldBitmap = MemDC.SelectObject( pBitmap );	
	pDC->BitBlt( 0, 0, sizeBitmap.cx, sizeBitmap.cy, &MemDC, 0, 0, SRCCOPY );	

	pDC->SelectObject(pFont);


	MemDC.SelectObject( pOldBitmap );
	ReleaseDC( pDC );
}

