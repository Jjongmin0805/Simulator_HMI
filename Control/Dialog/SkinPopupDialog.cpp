// SkinPopupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SkinPopupDialog.h"

#define MARGIN_BOX_X		12
#define MARGIN_BOX_Y		 7

/////////////////////////////////////////////////////////////////////////////
// CSkinPopupDialog

CSkinPopupDialog::CSkinPopupDialog( UINT nResourceID, CWnd* pParent /*=NULL*/ )
	: CDialog( nResourceID, pParent )
{
	//{{AFX_DATA_INIT(CShapeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_nClickedBox	= CLICKED_BOX_NONE;
	m_bTracking		= FALSE;
	m_cfBkMain		= g_gbl.GetRGB( IDX_RGB_MAIN_BACKGROUND );
	m_cfBkTitle     = g_gbl.GetRGB( IDX_RGB_FONT_WHITE );

	m_hBmpCapL		= NULL;
	m_hBmpCapM		= NULL;
	m_hBmpCapR		= NULL;
	m_hBmpFrmL		= NULL;
	m_hBmpFrmLB		= NULL;
	m_hBmpFrmB		= NULL;
	m_hBmpFrmR		= NULL;
	m_hBmpFrmRB		= NULL;
	m_hBmpExit		= NULL;
	m_hBmpBkMain	= NULL;
	m_hIcon			= NULL;
	m_pFontText     = NULL;

	m_nWidth		= 0;
	m_nHeight		= 0;

	memset( &m_sizeCapL,   0x00, sizeof(SIZE) );
	memset( &m_sizeCapM,   0x00, sizeof(SIZE) );
	memset( &m_sizeCapR,   0x00, sizeof(SIZE) );
	memset( &m_sizeFrmL,   0x00, sizeof(SIZE) );
	memset( &m_sizeFrmLB,  0x00, sizeof(SIZE) );
	memset( &m_sizeFrmB,   0x00, sizeof(SIZE) );
	memset( &m_sizeFrmRB,  0x00, sizeof(SIZE) );
	memset( &m_sizeFrmR,   0x00, sizeof(SIZE) );
	memset( &m_sizeExit,   0x00, sizeof(SIZE) );
	memset( &m_sizeBkMain, 0x00, sizeof(SIZE) );
}


CSkinPopupDialog::~CSkinPopupDialog()
{	
}


void CSkinPopupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSkinPopupDialog, CDialog)
	ON_WM_CREATE       ()
	ON_WM_DESTROY      ()	
	ON_WM_NCPAINT      ()
	ON_WM_NCACTIVATE   ()
	ON_WM_NCCALCSIZE   ()
	ON_WM_NCMOUSEMOVE  ()
	ON_WM_NCLBUTTONDOWN()	
	ON_WM_NCMOUSELEAVE ()
	ON_WM_PAINT        ()
	ON_WM_ERASEBKGND   ()
END_MESSAGE_MAP()


// CSkinPopupDialog message handlers

int CSkinPopupDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// �������� �ý��� �ڽ��� ǥ������ �ʱ� ���� ������ ��Ÿ���� ������	
	ModifyStyle( WS_SYSMENU, 0 );

	// �� ��Ʈ���� ������ ������ ���´�.
	m_sizeCapL		= g_gbl.GetBitmapSize( IDX_PNG_POPUP_CAPTION_LEFT	);
	m_sizeCapM		= g_gbl.GetBitmapSize( IDX_PNG_POPUP_CAPTION_CENTER );
	m_sizeCapR		= g_gbl.GetBitmapSize( IDX_PNG_POPUP_CAPTION_RIGHT  );	
	m_sizeFrmL	    = g_gbl.GetBitmapSize( IDX_PNG_POPUP_LEFT		    );
	m_sizeFrmLB	    = g_gbl.GetBitmapSize( IDX_PNG_POPUP_LEFT_BOTTOM    );
	m_sizeFrmB	    = g_gbl.GetBitmapSize( IDX_PNG_POPUP_BOTTOM	        );
	m_sizeFrmRB	    = g_gbl.GetBitmapSize( IDX_PNG_POPUP_RIGHT_BOTTOM   );
	m_sizeFrmR	    = g_gbl.GetBitmapSize( IDX_PNG_POPUP_RIGHT		    );
	m_sizeExit		= g_gbl.GetBitmapSize( IDX_PNG_BOX_EXIT				);

	// �� ��Ʈ���� �ڵ��� ���´�.
	m_hBmpCapL		= g_gbl.GetBitmap( IDX_PNG_POPUP_CAPTION_LEFT	);
	m_hBmpCapM		= g_gbl.GetBitmap( IDX_PNG_POPUP_CAPTION_CENTER );
	m_hBmpCapR		= g_gbl.GetBitmap( IDX_PNG_POPUP_CAPTION_RIGHT  );
	m_hBmpFrmL	    = g_gbl.GetBitmap( IDX_PNG_POPUP_LEFT		    );
	m_hBmpFrmLB	    = g_gbl.GetBitmap( IDX_PNG_POPUP_LEFT_BOTTOM    );
	m_hBmpFrmB	    = g_gbl.GetBitmap( IDX_PNG_POPUP_BOTTOM	        );
	m_hBmpFrmR	    = g_gbl.GetBitmap( IDX_PNG_POPUP_RIGHT          );
	m_hBmpFrmRB	    = g_gbl.GetBitmap( IDX_PNG_POPUP_RIGHT_BOTTOM   );	
	m_hBmpExit		= g_gbl.GetBitmap( IDX_PNG_BOX_EXIT				);

	// �� �������� �ڵ��� ���´�.
	m_hIcon			= g_gbl.GetIcon( IDX_ICON_SKIN, ICON24 );

	// ��Ʈ�̸��� ���� ��Ʈ������ �Ѵ�.
	CString strFontName = g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 22 );			// ����
	m_pFontText = SetFont( strFontName, 10, FALSE );
	
	// ������ ����, ���α��̰� ���õȰ�� �ش� ȭ�� ������� �ش�ũ��� �׷��ش�
	if( m_nWidth != 0 && m_nHeight != 0 )
	{
		MoveWindow( 0, 0, m_nWidth, m_nHeight );
		CenterWindow();
	}
	
	return 0;
}


void CSkinPopupDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here	
	if( m_pFontText )
	{
		delete m_pFontText;
		m_pFontText = NULL;
	}
}


void CSkinPopupDialog::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialog::OnNcPaint() for painting messages
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		DrawBitmap();
	}
}


BOOL CSkinPopupDialog::OnNcActivate(BOOL bActive)
{
	// TODO: Add your message handler code here and/or call default
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		DrawBitmap();
		return TRUE;
	}
	else
	{
		return CDialog::OnNcActivate(bActive);
	}
}


void CSkinPopupDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: Add your message handler code here and/or call default
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{		
		int revision = 0;
		
		// Recalculate top
		SIZE size = g_gbl.GetBitmapSize( IDX_PNG_POPUP_CAPTION_CENTER );		
		if( size.cy )
		{
			revision = size.cy - ( GetSystemMetrics( SM_CYCAPTION ) + GetSystemMetrics( SM_CYFRAME ) );
			lpncsp->rgrc[0].top += revision;
		}

		// Recalculate left
		size = g_gbl.GetBitmapSize( IDX_PNG_POPUP_LEFT );
		if( size.cx )
		{
			revision = size.cx - GetSystemMetrics( SM_CXFRAME );
			lpncsp->rgrc[0].left += revision;
		}

		// Recalculate right
		size = g_gbl.GetBitmapSize( IDX_PNG_POPUP_RIGHT );
		if( size.cx )
		{
			revision = size.cx - GetSystemMetrics( SM_CXFRAME );
			lpncsp->rgrc[0].right -= revision;
		}

		// Recalculate bottom
		size = g_gbl.GetBitmapSize( IDX_PNG_POPUP_BOTTOM );
		if( size.cy )
		{
			revision = size.cy - GetSystemMetrics( SM_CXFRAME );
			lpncsp->rgrc[0].bottom -= revision;
		}
	}

	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CSkinPopupDialog::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		if( !m_bTracking )
		{	
			// ���콺�� �����츦 ����� WM_NCMOUSELEAVE �̺�Ʈ�� �߻��ϵ��� ����
			m_bTracking = TRUE;
			TRACKMOUSEEVENT t = { sizeof(TRACKMOUSEEVENT), TME_NONCLIENT | TME_LEAVE, m_hWnd, 0 };
			::TrackMouseEvent( &t );					
		}

		if( m_nClickedBox != CLICKED_BOX_NONE )
			CDialog::OnNcMouseMove(nHitTest, point);
	
		CRect rc;
		GetWindowRect(&rc);

		CRect rcExit;
		int x = 0, y = 0;

		BOOL bZoomed = IsZoomed();				// ���� �����찡 �ִ�ȭ ��������..
		BOOL bIconic = IsIconic();				// ���� �����찡 �ּ�ȭ ��������..		

		y = rc.top + MARGIN_BOX_Y;

		rcExit.left = rc.right - MARGIN_BOX_X - m_sizeExit.cx;
		rcExit.top = y;
		rcExit.right = rcExit.left + m_sizeExit.cx;
		rcExit.bottom = rcExit.top + m_sizeExit.cy;
	
		m_hBmpExit = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT );
				
		if( rcExit.PtInRect( point ) )
		{
			m_hBmpExit = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT_OVER );
		}	

		DrawBitmap();
	}

	CDialog::OnNcMouseMove(nHitTest, point);
}

void CSkinPopupDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		CRect rc;
		GetWindowRect(&rc);

		CRect rcMinimize, rcMaximize, rcRestore, rcExit;
		int x = 0, y = 0;

		BOOL bZoomed = IsZoomed();				// ���� �����찡 �ִ�ȭ ��������..
		BOOL bIconic = IsIconic();				// ���� �����찡 �ּ�ȭ ��������..		

		y = rc.top + MARGIN_BOX_Y;

		rcExit.left = rc.right - MARGIN_BOX_X - m_sizeExit.cx;
		rcExit.top = y;
		rcExit.right = rcExit.left + m_sizeExit.cx;
		rcExit.bottom = rcExit.top + m_sizeExit.cy;	

		if( rcExit.PtInRect( point ) )
		{
			SetCapture();
			m_nClickedBox = CLICKED_BOX_EXIT;
			m_hBmpExit = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT_DOWN );

			DrawBitmap();
		}		
		else
		{
			m_nClickedBox = CLICKED_BOX_NONE;
		}
	}

	CDialog::OnNcLButtonDown(nHitTest, point);
}


void CSkinPopupDialog::OnNcMouseLeave()
{
	// �� ����� ����Ϸ��� Windows 2000 �̻��� �ʿ��մϴ�.
	// _WIN32_WINNT �� WINVER ��ȣ�� 0x0500���� ũ�ų� ���ƾ� �մϴ�.
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.	
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		m_bTracking = FALSE;

		if( m_nClickedBox == CLICKED_BOX_NONE )
		{			
			m_hBmpExit	  = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT );
			m_nClickedBox = CLICKED_BOX_NONE;

			DrawBitmap();
		}
	}

	CDialog::OnNcMouseLeave();
}


CFont * CSkinPopupDialog::SetFont( CString strFaceName, UINT nFontSize, BOOL bBold/*=FALSE*/ )
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


void CSkinPopupDialog::DrawBitmap()
{
	if( !( GetWindowLong( GetSafeHwnd(), GWL_STYLE ) & WS_CAPTION ) )
		return;

	int x = 0, y = 0, x2 = 0, y2 = 0, cx = 0, cy = 0;
	CRect rc;
	GetWindowRect( &rc );	

	//Non-Client ������ DC�� ���´�.
	CWindowDC dc( this );	

	// ȣȯ�� �ִ� �޸� DC�� ����(�������)
	CDC BufferDC, tmpDC;
	BufferDC.CreateCompatibleDC( &dc );
	tmpDC.CreateCompatibleDC( &dc );

	// �޸� ��Ʈ�� ����
	CBitmap bmpBuffer, *pOldBitmap;
	HGDIOBJ hgdiobj;

	// ȣȯ�� �ִ� �޸� ��Ʈ�� �����Ͽ� �޸� DC�� ����
	bmpBuffer.CreateCompatibleBitmap( &dc, rc.Width(), rc.Height() );
	pOldBitmap = (CBitmap *)BufferDC.SelectObject( &bmpBuffer );

	// Left ĸ�� ��Ʈ���� �޸� DC�� ����
	x = 0;
	y = 0;
	cx = m_sizeCapL.cx;
	cy = m_sizeCapL.cy;
	hgdiobj = tmpDC.SelectObject( m_hBmpCapL );
	BufferDC.BitBlt( x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY );

	// Center ĸ�� ��Ʈ���� �޸� DC�� ����
	x += cx;
	cx = rc.Width() - m_sizeCapL.cx - m_sizeCapR.cx;
	cy = m_sizeCapM.cy;
	tmpDC.SelectObject( m_hBmpCapM );
	BufferDC.StretchBlt( x, y, cx, cy, &tmpDC, 0, 0, m_sizeCapM.cx, m_sizeCapM.cy, SRCCOPY );

	// Right ĸ�� ��Ʈ���� �޸� DC�� ����
	x += cx;
	cx = m_sizeCapR.cx;
	cy = m_sizeCapR.cy;
	tmpDC.SelectObject( m_hBmpCapR );
	BufferDC.BitBlt( x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY );

	// Left ���� ��Ʈ���� �޸� DC�� ����
	x = 0;
	y = m_sizeCapL.cy;
	cx = m_sizeFrmL.cx;
	cy = rc.Height() - m_sizeCapL.cy - m_sizeFrmB.cy;
	tmpDC.SelectObject( m_hBmpFrmL );
	BufferDC.StretchBlt( x, y, cx, cy, &tmpDC, 0, 0, m_sizeFrmL.cx, m_sizeFrmL.cy, SRCCOPY );	
		
	// Left-Bottom ���� ��Ʈ���� �޸� DC�� ����
	y += cy;
	cx = m_sizeFrmLB.cx;
	cy = m_sizeFrmLB.cy;
	tmpDC.SelectObject( m_hBmpFrmLB );
	BufferDC.BitBlt( x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY );

	// Bottom ���� ��Ʈ���� �޸� DC�� ����
	x += cx;
	cx = rc.Width() - m_sizeFrmL.cx - m_sizeFrmR.cx;
	cy = m_sizeFrmB.cy;
	tmpDC.SelectObject( m_hBmpFrmB );
	BufferDC.StretchBlt( x, y, cx, cy, &tmpDC, 0, 0, m_sizeFrmB.cx, m_sizeFrmB.cy, SRCCOPY );	

	// Right ���� ��Ʈ���� �޸� DC�� ����
	x = rc.Width() - m_sizeFrmR.cx;
	y = m_sizeCapR.cy;
	cx = m_sizeFrmR.cx;
	cy = rc.Height() - m_sizeCapR.cy - m_sizeFrmRB.cy;
	tmpDC.SelectObject( m_hBmpFrmR );
	BufferDC.StretchBlt( x, y, cx, cy, &tmpDC, 0, 0, m_sizeFrmR.cx, m_sizeFrmR.cy, SRCCOPY );

	// Right-Bottom ���� ��Ʈ���� �޸� DC�� ����
	x = rc.Width() - m_sizeFrmRB.cx;
	y += cy;
	cx = m_sizeFrmRB.cx;
	cy = m_sizeFrmRB.cy;
	tmpDC.SelectObject( m_hBmpFrmRB );
	BufferDC.BitBlt( x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY );	

	// ĸ�� ������ ��Ʈ���� �޸� DC�� ����
	//::DrawIconEx( BufferDC.m_hDC, 8, 3, m_hIcon, 24, 24, 0, NULL, DI_NORMAL );

	// Close Box ��Ʈ���� �޸� DC�� ����
	tmpDC.SelectObject( m_hBmpExit );
	x = rc.Width() - MARGIN_BOX_X - m_sizeExit.cx;
	y = MARGIN_BOX_Y;
	BufferDC.BitBlt( x, y, m_sizeExit.cx, m_sizeExit.cx, &tmpDC, 0, 0, SRCCOPY );
	
	// �޸� DC ���� ����
	tmpDC.SelectObject( hgdiobj );
	tmpDC.DeleteDC();

	// �ؽ�Ʈ ����带 ����(����)
	BufferDC.SetBkMode( TRANSPARENT );	

	// ��Ʈ �� �ؽ�Ʈ�� ������� ����
	BufferDC.SelectObject( m_pFontText );
	BufferDC.SetTextColor( m_cfBkTitle );

	// ���ڿ��� ��µ� �������� ��ǥ ����
	BufferDC.SetTextAlign( TA_LEFT | TA_TOP );	
	CSize font_size = BufferDC.GetTextExtent( m_strTitle );

	// �ؽ�Ʈ�� �޸� DC�� ���	
	BufferDC.TextOut( (rc.Width() / 2) - font_size.cx / 2, 7, m_strTitle );

	// Ŭ���̾�Ʈ ������ �����Ѵ�.
	x = m_sizeFrmL.cx;
	y = m_sizeCapM.cy;
	x2 = rc.Width () - m_sizeFrmR.cx;
	y2 = rc.Height() - m_sizeFrmB.cy;	
	dc.ExcludeClipRect( x, y, x2, y2 );

	// �޸� DC�� �׷��� ��Ʈ���� ȭ������ ����
	dc.BitBlt( 0, 0, rc.Width(), rc.Height(), &BufferDC, 0, 0, SRCCOPY );
	
	// �޸� DC ���� �� ����	
	BufferDC.SelectObject( pOldBitmap );
	BufferDC.DeleteDC();
}


void CSkinPopupDialog::SetBkBitmap( UINT nBitmapID )
{
	m_sizeBkMain = g_gbl.GetBitmapSize( nBitmapID );
	m_hBmpBkMain = g_gbl.GetBitmap	  ( nBitmapID );
}


BOOL CSkinPopupDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(	pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4 ||
		pMsg->wParam == VK_ESCAPE || pMsg->message == WM_NCLBUTTONDBLCLK || pMsg->wParam == VK_RETURN )
	{
		return TRUE;
	}
	// None Client �������� ���콺 ���� ��ư�� �������� ��� NCLBUTTONUP�� �̺�Ʈ�� ����Ŭ���ؾ� �߻��ϹǷ� LBUTTONUP���� ó����
	else if( pMsg->message == WM_LBUTTONUP )			 
	{	
		if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
		{
			CRect rc, rcExit;
			GetWindowRect(&rc);

			int x = 0, y = 0;			
			y = rc.top + MARGIN_BOX_Y;

			rcExit.left = rc.right - MARGIN_BOX_X - m_sizeExit.cx;
			rcExit.top = y;
			rcExit.right = rcExit.left + m_sizeExit.cx;
			rcExit.bottom = rcExit.top + m_sizeExit.cy;

			if( m_nClickedBox != CLICKED_BOX_NONE )
					ReleaseCapture();

			if( rcExit.PtInRect(pMsg->pt) )
			{
				if( m_nClickedBox == CLICKED_BOX_EXIT )
				{
					PostMessage( WM_CLOSE, 0, 0 );
				}
			}			
			else
			{				
				m_hBmpExit = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT );
				DrawBitmap();
			}

			m_nClickedBox = CLICKED_BOX_NONE;			
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CSkinPopupDialog::OnPaint()
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

	CDialog::OnPaint();
}


BOOL CSkinPopupDialog::OnEraseBkgnd( CDC* pDC )
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
		pDC->BitBlt( 0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY );

		MemDC.SelectObject( pOldBitmap );
		ReleaseDC( pDC );

		return TRUE;
	}

	return FALSE;
}