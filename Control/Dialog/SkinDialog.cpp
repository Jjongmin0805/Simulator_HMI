// SkinDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SkinDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CSkinDialog

CSkinDialog::CSkinDialog( UINT nResourceID, CWnd* pParent /*=NULL*/ )
	: CDialog( nResourceID, pParent )
{
	//{{AFX_DATA_INIT(CShapeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
		
	m_cfBkMain   = g_gbl.GetRGB( IDX_RGB_MAIN_BACKGROUND );
	m_hBmpBkMain = NULL;
	m_bMove      = FALSE;

	memset( &m_sizeBkMain, 0x00, sizeof(SIZE) );
}


CSkinDialog::~CSkinDialog()
{	
}


void CSkinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSkinDialog, CDialog)
	ON_WM_CREATE     ()
	ON_WM_DESTROY    ()	
	ON_WM_PAINT      ()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND ()	
END_MESSAGE_MAP()


// CSkinDialog message handlers

int CSkinDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// �������� �ý��� �ڽ��� ǥ������ �ʱ� ���� ������ ��Ÿ���� ������	
	ModifyStyle( WS_SYSMENU, 0 );

	// TODO:  Add your specialized creation code here
		
	return 0;
}


void CSkinDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here	
}


void CSkinDialog::SetBkColor( COLORREF clrBkColor )
{
	m_cfBkMain = clrBkColor;
}


void CSkinDialog::SetBkBitmap( UINT nBitmapID )
{
	m_sizeBkMain = g_gbl.GetBitmapSize( nBitmapID );
	m_hBmpBkMain = g_gbl.GetBitmap	  ( nBitmapID );
}


BOOL CSkinDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(	pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4 ||
		pMsg->wParam == VK_ESCAPE || pMsg->message == WM_NCLBUTTONDBLCLK || pMsg->wParam == VK_RETURN )
	{		
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


void CSkinDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages	

	if( !m_hBmpBkMain )
	{
		CRect rc;
		GetClientRect( &rc );
		dc.FillSolidRect( rc, m_cfBkMain );	
	}	
}


void CSkinDialog::OnLButtonDown( UINT nFlags, CPoint point )
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if( m_bMove )
		PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) );

	CDialog::OnLButtonDown( nFlags, point );
}


BOOL CSkinDialog::OnEraseBkgnd( CDC* pDC )
{
	if( m_hBmpBkMain )
	{
		CRect rect;
		GetClientRect( &rect );

		CDC MemDC;
		MemDC.CreateCompatibleDC( pDC );

		CBitmap *pBitmap = CBitmap::FromHandle( m_hBmpBkMain );
		CBitmap* pOldBitmap = MemDC.SelectObject( pBitmap );

		pDC->SetBkMode( TRANSPARENT );
		pDC->StretchBlt( 0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, m_sizeBkMain.cx, m_sizeBkMain.cy, SRCCOPY );		

		MemDC.SelectObject( pOldBitmap );
		ReleaseDC( pDC );
		return TRUE;	
	}

	return TRUE;
}