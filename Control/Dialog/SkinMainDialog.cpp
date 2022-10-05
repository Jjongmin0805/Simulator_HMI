// SkinMainDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SkinMainDialog.h"

#define MARGIN_BOX_X			12
#define MARGIN_BOX_Y			 7
#define WINDOW_MIN_WIDTH	  1280		// 윈도우 최소 너비
#define WINDOW_MIN_HEIGHT	   800		// 윈도우 최소 높이

/////////////////////////////////////////////////////////////////////////////
// CSkinMainDialog

CSkinMainDialog::CSkinMainDialog( UINT nResourceID, CWnd* pParent /*=NULL*/ )
	: CDialog( nResourceID, pParent )
{
	//{{AFX_DATA_INIT(CShapeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_nClickedBox	= CLICKED_BOX_NONE;
	m_bTracking		= FALSE;
	m_cfBkMain		= g_gbl.GetRGB( IDX_RGB_MAIN_BACKGROUND );
	m_cfBkMenu		= g_gbl.GetRGB( IDX_RGB_MAIN_BACKGROUND );
	m_cfBkSepa      = g_gbl.GetRGB( IDX_RGB_FONT_GRAY2 );
	m_cfBkTab		= g_gbl.GetRGB( IDX_RGB_FONT_LITE_GRAY2 );

	m_hBmpCapL		= NULL;
	m_hBmpCapM		= NULL;
	m_hBmpCapR		= NULL;
	m_hBmpFrmL		= NULL;
	m_hBmpFrmLB		= NULL;
	m_hBmpFrmB		= NULL;
	m_hBmpFrmR		= NULL;
	m_hBmpFrmRB		= NULL;
	m_hBmpExit		= NULL;
	m_hBmpMin		= NULL;
	m_hBmpMax		= NULL;
	m_hBmpRes		= NULL;
	
	memset( &m_sizeCapL,     0x00, sizeof(SIZE) );
	memset( &m_sizeCapM,     0x00, sizeof(SIZE) );
	memset( &m_sizeCapR,     0x00, sizeof(SIZE) );
	memset( &m_sizeFrmL,     0x00, sizeof(SIZE) );
	memset( &m_sizeFrmLB,    0x00, sizeof(SIZE) );
	memset( &m_sizeFrmB,     0x00, sizeof(SIZE) );
	memset( &m_sizeFrmRB,    0x00, sizeof(SIZE) );
	memset( &m_sizeFrmR,     0x00, sizeof(SIZE) );	
	memset( &m_sizeMin,		 0x00, sizeof(SIZE) );
	memset( &m_sizeMax,		 0x00, sizeof(SIZE) );
	memset( &m_sizeRes,		 0x00, sizeof(SIZE) );
	memset( &m_sizeExit,	 0x00, sizeof(SIZE) );	
}


CSkinMainDialog::~CSkinMainDialog()
{	
}


void CSkinMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSkinMainDialog, CDialog)
	ON_WM_CREATE ()
	ON_WM_DESTROY()	
	ON_WM_NCPAINT()	
	ON_WM_NCACTIVATE()
	ON_WM_NCCALCSIZE()	
	ON_WM_PAINT()	
	ON_WM_GETMINMAXINFO()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()	
	ON_WM_NCMOUSELEAVE()	
	ON_WM_NCLBUTTONDBLCLK()
END_MESSAGE_MAP()


// CSkinMainDialog message handlers

void CSkinMainDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here	
}

void CSkinMainDialog::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialog::OnNcPaint() for painting messages

	if( GetWindowLong( GetSafeHwnd(), GWL_STYLE ) & WS_CAPTION )
	{	
		DrawBitmap();
	}

}


BOOL CSkinMainDialog::OnNcActivate(BOOL bActive)
{
	// TODO: Add your message handler code here and/or call default

	if( GetWindowLong( GetSafeHwnd(), GWL_STYLE ) & WS_CAPTION )
	{		
		DrawBitmap();
		return TRUE;
	}
	else
	{
		return CDialog::OnNcActivate(bActive);
	}

}

void CSkinMainDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: Add your message handler code here and/or call default
	if( GetWindowLong( GetSafeHwnd(), GWL_STYLE ) & WS_CAPTION )
	{		
		int revision = 0;
		
		// Recalculate top
		SIZE size = g_gbl.GetBitmapSize( IDX_PNG_CAPTION_CENTER );		
		if( size.cy )
		{
			revision = size.cy - ( GetSystemMetrics( SM_CYCAPTION ) + GetSystemMetrics( SM_CYFRAME ) );
			lpncsp->rgrc[0].top += revision;
		}

		// Recalculate left
		size = g_gbl.GetBitmapSize( IDX_PNG_FRAME_LEFT );
		if( size.cx )
		{
			revision = size.cx - GetSystemMetrics( SM_CXFRAME );
			lpncsp->rgrc[0].left += revision;
		}

		// Recalculate right
		size = g_gbl.GetBitmapSize( IDX_PNG_FRAME_RIGHT );
		if( size.cx )
		{
			revision = size.cx - GetSystemMetrics( SM_CXFRAME );
			lpncsp->rgrc[0].right -= revision;
		}

		// Recalculate bottom
		size = g_gbl.GetBitmapSize( IDX_PNG_FRAME_BOTTOM );
		if( size.cy )
		{
			revision = size.cy - GetSystemMetrics( SM_CXFRAME );
			lpncsp->rgrc[0].bottom -= revision;
		}
	}

	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CSkinMainDialog::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( GetWindowLong( GetSafeHwnd(), GWL_STYLE ) & WS_CAPTION )
	{
		if( !m_bTracking )
		{	
			// 마우스가 윈도우를 벗어나면 WM_NCMOUSELEAVE 이벤트가 발생하도록 설정
			m_bTracking = TRUE;
			TRACKMOUSEEVENT t = { sizeof(TRACKMOUSEEVENT), TME_NONCLIENT | TME_LEAVE, m_hWnd, 0 };
			::TrackMouseEvent( &t );					
		}

		if( m_nClickedBox != CLICKED_BOX_NONE )
			CDialog::OnNcMouseMove(nHitTest, point);
	
		CRect rc;
		GetWindowRect(&rc);

		CRect rcMinimize, rcMaximize, rcRestore, rcExit;
		int x = 0, y = 0;

		BOOL bZoomed = IsZoomed();				// 현재 윈도우가 최대화 상태인지..
		BOOL bIconic = IsIconic();				// 현재 윈도우가 최소화 상태인지..		

		y = rc.top + MARGIN_BOX_Y;

		rcExit.left = rc.right - MARGIN_BOX_X - m_sizeExit.cx;
		rcExit.top = y;
		rcExit.right = rcExit.left + m_sizeExit.cx;
		rcExit.bottom = rcExit.top + m_sizeExit.cy;

		rcMaximize.left = rcExit.left - m_sizeMax.cx;
		rcMaximize.top = y;
		rcMaximize.right = rcMaximize.left + m_sizeMax.cx;
		rcMaximize.bottom = rcMaximize.top + m_sizeMax.cy;

		rcRestore.left = rcExit.left - m_sizeRes.cx;
		rcRestore.top = y;
		rcRestore.right = rcRestore.left + m_sizeRes.cx;
		rcRestore.bottom = rcRestore.top + m_sizeRes.cy;

		rcMinimize.left = rcMaximize.left - m_sizeMin.cx;
		rcMinimize.top = y;
		rcMinimize.right = rcMinimize.left + m_sizeMin.cx;
		rcMinimize.bottom = rcMinimize.top + m_sizeMin.cy;

		m_hBmpMin  = g_gbl.GetBitmap( IDX_PNG_BOX_MINIMIZE );
		m_hBmpMax  = g_gbl.GetBitmap( IDX_PNG_BOX_MAXMIZE  );
		m_hBmpRes  = g_gbl.GetBitmap( IDX_PNG_BOX_RESTORE  );
		m_hBmpExit = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT     );
				
		if( rcExit.PtInRect( point ) )
		{
			m_hBmpExit = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT_OVER );
		}
		else if( rcMaximize.PtInRect( point ) )
		{
			if( bZoomed )
				m_hBmpRes = g_gbl.GetBitmap( IDX_PNG_BOX_RESTORE_OVER );
			else
				m_hBmpMax = g_gbl.GetBitmap( IDX_PNG_BOX_MAXMIZE_OVER );
		}
		else if( rcMinimize.PtInRect( point ) )
		{
			if( bIconic )
				m_hBmpRes = g_gbl.GetBitmap( IDX_PNG_BOX_RESTORE_OVER );
			else
				m_hBmpMin = g_gbl.GetBitmap( IDX_PNG_BOX_MINIMIZE_OVER );
		}

		DrawBitmap();
	}

	CDialog::OnNcMouseMove(nHitTest, point);
}

void CSkinMainDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( GetWindowLong( GetSafeHwnd(), GWL_STYLE ) & WS_CAPTION )
	{
		CRect rc;
		GetWindowRect(&rc);

		CRect rcMinimize, rcMaximize, rcRestore, rcExit;
		int x = 0, y = 0;

		BOOL bZoomed = IsZoomed();				// 현재 윈도우가 최대화 상태인지..
		BOOL bIconic = IsIconic();				// 현재 윈도우가 최소화 상태인지..		

		y = rc.top + MARGIN_BOX_Y;

		rcExit.left = rc.right - MARGIN_BOX_X - m_sizeExit.cx;
		rcExit.top = y;
		rcExit.right = rcExit.left + m_sizeExit.cx;
		rcExit.bottom = rcExit.top + m_sizeExit.cy;

		rcMaximize.left = rcExit.left - m_sizeMax.cx;
		rcMaximize.top = y;
		rcMaximize.right = rcMaximize.left + m_sizeMax.cx;
		rcMaximize.bottom = rcMaximize.top + m_sizeMax.cy;

		rcRestore.left = rcExit.left - m_sizeRes.cx;
		rcRestore.top = y;
		rcRestore.right = rcRestore.left + m_sizeRes.cx;
		rcRestore.bottom = rcRestore.top + m_sizeRes.cy;

		rcMinimize.left = rcMaximize.left - m_sizeMin.cx;
		rcMinimize.top = y;
		rcMinimize.right = rcMinimize.left + m_sizeMin.cx;
		rcMinimize.bottom = rcMinimize.top + m_sizeMin.cy;

		if( rcExit.PtInRect( point ) )
		{
			SetCapture();
			m_nClickedBox = CLICKED_BOX_EXIT;
			m_hBmpExit = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT_DOWN );

			DrawBitmap();
		}
		else if( rcMaximize.PtInRect( point ) )
		{
			SetCapture();	

			if( bZoomed )
			{
				m_hBmpRes = g_gbl.GetBitmap( IDX_PNG_BOX_RESTORE_DOWN );
				m_nClickedBox = CLICKED_BOX_RESTORE;
			}
			else
			{
				m_hBmpMax = g_gbl.GetBitmap( IDX_PNG_BOX_MAXMIZE_DOWN );
				m_nClickedBox = CLICKED_BOX_MAXIMIZE;
			}

			DrawBitmap();
		}
		else if( rcMinimize.PtInRect( point ) )
		{
			SetCapture();

			if( bIconic )
			{
				m_hBmpRes = g_gbl.GetBitmap( IDX_PNG_BOX_RESTORE_DOWN );
				m_nClickedBox = CLICKED_BOX_RESTORE;
			}
			else
			{
				m_hBmpMin = g_gbl.GetBitmap( IDX_PNG_BOX_MINIMIZE_DOWN );
				m_nClickedBox = CLICKED_BOX_MINIMIZE;
			}

			DrawBitmap();
		}
		else
		{
			m_nClickedBox = CLICKED_BOX_NONE;
		}
	}

	CDialog::OnNcLButtonDown(nHitTest, point);
}


void CSkinMainDialog::OnNcMouseLeave()
{
	// 이 기능을 사용하려면 Windows 2000 이상이 필요합니다.
	// _WIN32_WINNT 및 WINVER 기호는 0x0500보다 크거나 같아야 합니다.
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( GetWindowLong( GetSafeHwnd(), GWL_STYLE ) & WS_CAPTION )
	{
		m_bTracking = FALSE;

		if( m_nClickedBox == CLICKED_BOX_NONE )
		{
			m_hBmpMin  = g_gbl.GetBitmap( IDX_PNG_BOX_MINIMIZE );
			m_hBmpMax  = g_gbl.GetBitmap( IDX_PNG_BOX_MAXMIZE  );
			m_hBmpRes  = g_gbl.GetBitmap( IDX_PNG_BOX_RESTORE  );
			m_hBmpExit = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT     );
			m_nClickedBox  = CLICKED_BOX_NONE;

			DrawBitmap();
		}
	}

	CDialog::OnNcMouseLeave();
}


void CSkinMainDialog::DrawBitmap()
{
	if( !( GetWindowLong( GetSafeHwnd(), GWL_STYLE ) & WS_CAPTION ) )
		return;

	int x = 0, y = 0, x2 = 0, y2 = 0, cx = 0, cy = 0;
	CRect rc;
	GetWindowRect(&rc);	
	BOOL bZoomed = IsZoomed();

	//Non-Client 영역의 DC를 얻어온다.
	CWindowDC dc( this );	

	// 호환성 있는 메모리 DC를 생성(더블버퍼)
	CDC BufferDC, tmpDC;
	BufferDC.CreateCompatibleDC( &dc );
	tmpDC.CreateCompatibleDC( &dc );

	// 메모리 비트맵 선언
	CBitmap bmpBuffer, *pOldBitmap;
	HGDIOBJ hgdiobj;

	// 호환성 있는 메모리 비트맵 생성하여 메모리 DC에 설정
	bmpBuffer.CreateCompatibleBitmap( &dc, rc.Width(), rc.Height() );
	pOldBitmap = (CBitmap *)BufferDC.SelectObject( &bmpBuffer );

	// Left 캡션 비트맵을 메모리 DC로 전송
	x = 0;
	y = 0;
	cx = m_sizeCapL.cx;
	cy = m_sizeCapL.cy;
	hgdiobj = tmpDC.SelectObject( m_hBmpCapL );
	BufferDC.BitBlt( x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY );

	// Center 캡션 비트맵을 메모리 DC로 전송
	x += cx;
	cx = rc.Width() - m_sizeCapL.cx - m_sizeCapR.cx;
	cy = m_sizeCapM.cy;
	tmpDC.SelectObject( m_hBmpCapM );
	BufferDC.StretchBlt( x, y, cx, cy, &tmpDC, 0, 0, m_sizeCapM.cx, m_sizeCapM.cy, SRCCOPY );

	// Right 캡션 비트맵을 메모리 DC로 전송
	x += cx;
	cx = m_sizeCapR.cx;
	cy = m_sizeCapR.cy;
	tmpDC.SelectObject( m_hBmpCapR );
	BufferDC.BitBlt( x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY );

	// Left 보더 비트맵을 메모리 DC로 전송
	x = 0;
	y = m_sizeCapL.cy;
	cx = m_sizeFrmL.cx;
	cy = rc.Height() - m_sizeCapL.cy - m_sizeFrmB.cy;
	tmpDC.SelectObject( m_hBmpFrmL );
	BufferDC.StretchBlt( x, y, cx, cy, &tmpDC, 0, 0, m_sizeFrmL.cx, m_sizeFrmL.cy, SRCCOPY );

	// Left-Bottom 보더 비트맵을 메모리 DC로 전송
	y += cy;
	cx = m_sizeFrmLB.cx;
	cy = m_sizeFrmLB.cy;
	tmpDC.SelectObject( m_hBmpFrmLB );
	BufferDC.BitBlt( x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY );

	// Bottom 보더 비트맵을 메모리 DC로 전송
	x += cx;
	cx = rc.Width() - m_sizeFrmL.cx - m_sizeFrmR.cx;
	cy = m_sizeFrmB.cy;
	tmpDC.SelectObject( m_hBmpFrmB );
	BufferDC.StretchBlt( x, y, cx, cy, &tmpDC, 0, 0, m_sizeFrmB.cx, m_sizeFrmB.cy, SRCCOPY );	

	// Right 보더 비트맵을 메모리 DC로 전송
	x = rc.Width() - m_sizeFrmR.cx;
	y = m_sizeCapR.cy;
	cx = m_sizeFrmR.cx;
	cy = rc.Height() - m_sizeCapR.cy - m_sizeFrmRB.cy;
	tmpDC.SelectObject( m_hBmpFrmR );
	BufferDC.StretchBlt( x, y, cx, cy, &tmpDC, 0, 0, m_sizeFrmR.cx, m_sizeFrmR.cy, SRCCOPY );

	// Right-Bottom 보더 비트맵을 메모리 DC로 전송
	x = rc.Width() - m_sizeFrmRB.cx;
	y += cy;
	cx = m_sizeFrmRB.cx;
	cy = m_sizeFrmRB.cy;
	tmpDC.SelectObject( m_hBmpFrmRB );
	BufferDC.BitBlt( x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY );	

	// Exit Box 비트맵을 메모리 DC로 전송
	tmpDC.SelectObject( m_hBmpExit );
	x = rc.Width() - MARGIN_BOX_X - m_sizeExit.cx;
	y = MARGIN_BOX_Y;
	BufferDC.BitBlt( x, y, m_sizeExit.cx, m_sizeExit.cx, &tmpDC, 0, 0, SRCCOPY );

	if( !bZoomed )
	{
		// Maximize Box 비트맵을 메모리 DC로 전송
		tmpDC.SelectObject( m_hBmpMax );
		x = x - m_sizeMax.cx;			
		BufferDC.BitBlt( x, y, m_sizeMax.cx, m_sizeMax.cx, &tmpDC, 0, 0, SRCCOPY );
	}
	else
	{
		// Restore Box 비트맵을 메모리 DC로 전송
		tmpDC.SelectObject( m_hBmpRes );		
		x = x - m_sizeRes.cx;			
		BufferDC.BitBlt( x, y, m_sizeRes.cx, m_sizeRes.cx, &tmpDC, 0, 0, SRCCOPY );
	}

	// Minimize Box 비트맵을 메모리 DC로 전송
	tmpDC.SelectObject( m_hBmpMin );
	x = x - m_sizeMin.cx;
	BufferDC.BitBlt( x, y, m_sizeMin.cx, m_sizeMin.cx, &tmpDC, 0, 0, SRCCOPY );	

	// 메모리 DC 복원 삭제
	tmpDC.SelectObject( hgdiobj );
	tmpDC.DeleteDC();

	// 텍스트 배경모드를 설정(투명)
	BufferDC.SetBkMode( TRANSPARENT );

	// 문자열이 출력될 기준점의 자표 지정
	BufferDC.SetTextAlign( TA_LEFT | TA_TOP );	
		
	// 캡션타이틀을 메모리 DC에 출력
	BufferDC.SelectObject( g_gbl.GetFont( IDX_FONT_SIZE_10 ) );			// 윈도우 타이틀 폰트사이즈
	CSize font_size1 = BufferDC.GetTextExtent( m_strTitle );			
	BufferDC.SetTextColor( g_gbl.GetRGB( IDX_RGB_FONT_WHITE ) );
	BufferDC.TextOut( (rc.Width() / 2) - font_size1.cx / 2, 10, m_strTitle );

	// 로그인시간을 메모리 DC에 출력
	BufferDC.SelectObject( g_gbl.GetFont( IDX_FONT_SIZE_10 ) );			// 로그인표시 폰트사이즈
	CSize font_size2 = BufferDC.GetTextExtent( m_strLogIn );	
	BufferDC.TextOut( x - font_size2.cx - 20, 10, m_strLogIn );
	
	// 클라이언트 영역을 제거한다.
	x = m_sizeFrmL.cx;
	y = m_sizeCapM.cy;
	x2 = rc.Width () - m_sizeFrmR.cx;
	y2 = rc.Height() - m_sizeFrmB.cy;	
	dc.ExcludeClipRect( x, y, x2, y2 );

	// 메모리 DC에 그려진 비트맵을 화면으로 전송
	dc.BitBlt( 0, 0, rc.Width(), rc.Height(), &BufferDC, 0, 0, SRCCOPY );

	// 메모리 DC 복원 및 삭제
	BufferDC.SelectObject( pOldBitmap );
	BufferDC.DeleteDC();
}


BOOL CSkinMainDialog::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message ) 
{
	// TODO: Add your message handler code here and/or call default	

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


BOOL CSkinMainDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(	pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4 || pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN )
	{		
		return TRUE;
	}
	// None Client 영역에서 마우스 왼쪽 버튼이 떼어졌을 경우 NCLBUTTONUP이 이벤트가 더블클릭해야 발생하므로 LBUTTONUP에서 처리함
	else if( pMsg->message == WM_LBUTTONUP )			 
	{
		if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
		{
			CRect rc, rcExit, rcMaximize, rcMinimize;
			GetWindowRect(&rc);	

			int x = 0, y = 0;	
			y = rc.top + MARGIN_BOX_Y;

			rcExit.left = rc.right - MARGIN_BOX_X - m_sizeExit.cx;
			rcExit.top = y;
			rcExit.right = rcExit.left + m_sizeExit.cx;
			rcExit.bottom = rcExit.top + m_sizeExit.cy;

			rcMaximize.left = rcExit.left - m_sizeMax.cx;
			rcMaximize.top = y;
			rcMaximize.right = rcMaximize.left + m_sizeMax.cx;
			rcMaximize.bottom = rcMaximize.top + m_sizeMax.cy;

			rcMinimize.left = rcMaximize.left - m_sizeMin.cx;
			rcMinimize.top = y;
			rcMinimize.right = rcMinimize.left + m_sizeMin.cx;
			rcMinimize.bottom = rcMinimize.top + m_sizeMin.cy;

			if( m_nClickedBox != CLICKED_BOX_NONE )
					ReleaseCapture();

			if( rcExit.PtInRect(pMsg->pt) )
			{
				if( m_nClickedBox == CLICKED_BOX_EXIT )
				{
					PostMessage( WM_CLOSE, 0, 0 );
				}
			}
			else if( rcMaximize.PtInRect(pMsg->pt) )
			{
				if( m_nClickedBox == CLICKED_BOX_MAXIMIZE )
					ShowWindow( SW_MAXIMIZE );
				else
					ShowWindow( SW_RESTORE );				
			}
			else if( rcMinimize.PtInRect(pMsg->pt) )
			{
				if( m_nClickedBox == CLICKED_BOX_MINIMIZE )
					ShowWindow( SW_MINIMIZE );
				else
					ShowWindow( SW_RESTORE );
			}
			else
			{					
				m_hBmpMin  = g_gbl.GetBitmap( IDX_PNG_BOX_MINIMIZE );
				m_hBmpMax  = g_gbl.GetBitmap( IDX_PNG_BOX_MAXMIZE  );
				m_hBmpRes  = g_gbl.GetBitmap( IDX_PNG_BOX_RESTORE  );
				m_hBmpExit = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT	   );

				DrawBitmap();
			}

			m_nClickedBox = CLICKED_BOX_NONE;			
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


void CSkinMainDialog::OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI ) 
{
	// TODO: Add your message handler code here and/or call default		

	lpMMI->ptMinTrackSize.x = WINDOW_MIN_WIDTH;		// 윈도우 최소 너비 
	lpMMI->ptMinTrackSize.y = WINDOW_MIN_HEIGHT;	// 윈도우 최소 높이

#if 0
	/*--------------------------------------------------------------------------------------------
	아래 소스는 Main 모니터 화면의 작업 표시줄 유/무 따른 작업 영역의 사이즈를 얻어오는 API를 
	사용하여 윈도우 최대화시 적용할 위치/사이즈 정보를 설정합니다.
	하지만 듀얼 모니터를 사용한다면 아래의 API아닌 모니터별 작업 영역을 얻어오는 API를 사용해야 합니다.
	그리고 해당 윈도우의 위치에 따라 소속되는 모니터는 달라질 수 있습니다.
	이래 저래 처리해야할 게 많으므로 우리는 간단히 윈도우 생성시 호출되는 
	OnCreate에서 윈도우 스타일만 재수정하여 이 문제를 간단히 해결하겠습니다.
	--------------------------------------------------------------------------------------------*/
	CRect rc;	
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);	

	lpMMI->ptMaxPosition.x = -MARGIN_MAXIMIZED;					// 윈도우 최대화 시 X축 좌표
	lpMMI->ptMaxPosition.y = -MARGIN_MAXIMIZED;					// 윈도우 최대화 시 Y축 좌료
	lpMMI->ptMaxSize.x = rc.Width()+MARGIN_MAXIMIZED*2;			// 윈도우 최대화 시 너비
	lpMMI->ptMaxSize.y = rc.Height()+MARGIN_MAXIMIZED*2;		// 윈도우 최대화 시 높이
	lpMMI->ptMaxTrackSize.x = rc.Width()+MARGIN_MAXIMIZED*2;	// 윈도우 최대화 시 너비
	lpMMI->ptMaxTrackSize.y = rc.Height()+MARGIN_MAXIMIZED*2;	// 윈도우 최대화 시 높이
#endif

	CDialog::OnGetMinMaxInfo(lpMMI);
}


void CSkinMainDialog::OnTimer( UINT_PTR nIDEvent )
{
	CDialog::OnTimer( nIDEvent );
}


int CSkinMainDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 윈도우의 시스템 박스를 표시하지 않기 위해 윈도우 스타일을 수정함
	// 대신 Maximize 처리를 하기 위해 리소스에서는 시스템 관련 윈도우 스타일을 Enable 시켜야 함
	ModifyStyle( WS_SYSMENU, 0 );	
		
	// 각 비트맵의 사이즈 정보를 얻어온다.
	m_sizeCapL	= g_gbl.GetBitmapSize( IDX_PNG_CAPTION_LEFT	      );
	m_sizeCapM	= g_gbl.GetBitmapSize( IDX_PNG_CAPTION_CENTER	  );
	m_sizeCapR	= g_gbl.GetBitmapSize( IDX_PNG_CAPTION_RIGHT	  );
	m_sizeFrmL	= g_gbl.GetBitmapSize( IDX_PNG_FRAME_LEFT		  );
	m_sizeFrmLB	= g_gbl.GetBitmapSize( IDX_PNG_FRAME_LEFT_BOTTOM  );
	m_sizeFrmB	= g_gbl.GetBitmapSize( IDX_PNG_FRAME_BOTTOM	      );
	m_sizeFrmRB	= g_gbl.GetBitmapSize( IDX_PNG_FRAME_RIGHT_BOTTOM );
	m_sizeFrmR	= g_gbl.GetBitmapSize( IDX_PNG_FRAME_RIGHT		  );
	m_sizeMin	= g_gbl.GetBitmapSize( IDX_PNG_BOX_MINIMIZE		  );
	m_sizeMax	= g_gbl.GetBitmapSize( IDX_PNG_BOX_MAXMIZE		  );
	m_sizeRes	= g_gbl.GetBitmapSize( IDX_PNG_BOX_RESTORE		  );
	m_sizeExit	= g_gbl.GetBitmapSize( IDX_PNG_BOX_EXIT		      );
		
	// 각 비트맵의 핸들을 얻어온다.
	m_hBmpCapL	= g_gbl.GetBitmap( IDX_PNG_CAPTION_LEFT		  );
	m_hBmpCapM	= g_gbl.GetBitmap( IDX_PNG_CAPTION_CENTER	  );
	m_hBmpCapR	= g_gbl.GetBitmap( IDX_PNG_CAPTION_RIGHT	  );
	m_hBmpFrmL	= g_gbl.GetBitmap( IDX_PNG_FRAME_LEFT		  );
	m_hBmpFrmLB	= g_gbl.GetBitmap( IDX_PNG_FRAME_LEFT_BOTTOM  );
	m_hBmpFrmB	= g_gbl.GetBitmap( IDX_PNG_FRAME_BOTTOM	      );
	m_hBmpFrmR	= g_gbl.GetBitmap( IDX_PNG_FRAME_RIGHT        );
	m_hBmpFrmRB	= g_gbl.GetBitmap( IDX_PNG_FRAME_RIGHT_BOTTOM );	
	m_hBmpMin	= g_gbl.GetBitmap( IDX_PNG_BOX_MINIMIZE       );
	m_hBmpMax	= g_gbl.GetBitmap( IDX_PNG_BOX_MAXMIZE        );
	m_hBmpRes   = g_gbl.GetBitmap( IDX_PNG_BOX_RESTORE        );
	m_hBmpExit  = g_gbl.GetBitmap( IDX_PNG_BOX_EXIT           );	
		
	return 0;
}

void CSkinMainDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages	

	CRect rc, rcMenu, rcSepa, rcTab, rcMain;
	GetClientRect( &rc );

	rcMenu.left   = rc.left;
	rcMenu.top    = rc.top;
	rcMenu.right  = rc.right;
	rcMenu.bottom = rc.top + 36;

	rcSepa.left   = rc.left;
	rcSepa.top    = rcMenu.bottom;
	rcSepa.right  = rc.right;
	rcSepa.bottom = rcSepa.top + 2;	
	
	rcTab.left    = rc.left;
	rcTab.top     = rcSepa.bottom;
	rcTab.right   = rc.right;
	rcTab.bottom  = rcTab.top + 31;

	rcMain.left   = rc.left;
	rcMain.top	  = rcTab.bottom;
	rcMain.right  = rc.right;
	rcMain.bottom = rc.bottom;

	dc.FillSolidRect( rcMenu, m_cfBkMenu );
	dc.FillSolidRect( rcSepa, m_cfBkSepa );
	dc.FillSolidRect( rcTab,  m_cfBkTab  );
	dc.FillSolidRect( rcMain, m_cfBkMain );
}

void CSkinMainDialog::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	BOOL bZoomed = IsZoomed();
	
	// 최대화되어있는 경우 최소화시킨다
	if( bZoomed )
	{
		m_nClickedBox = CLICKED_BOX_MINIMIZE;
		ShowWindow( SW_MINIMIZE );
	}
	// 기타 최대화시킨다
	else
	{		
		m_nClickedBox = CLICKED_BOX_MAXIMIZE;
		ShowWindow( SW_MAXIMIZE );
	}	
}