#include "pch.h"
#include "PNOCtrl_SkinFrame_CTRL_Dialog.h"
#include "PNOCtrl_SkinMng.h"

// CPNOCtrl_SkinFrame_CTRL_Dialog

IMPLEMENT_DYNAMIC(CPNOCtrl_SkinFrame_CTRL_Dialog, CDialog)

CPNOCtrl_SkinFrame_CTRL_Dialog::CPNOCtrl_SkinFrame_CTRL_Dialog():	m_bCreated( FALSE ), m_unCaptionStyle( 0x00 ), m_bMoveWindow( FALSE )
														, m_dwMinWidth( 0 ), m_dwMinHeight( 0 ) 
														, m_nClickedBox( CLICKED_BOX_NONE ) 
														, m_bTracking( FALSE ) 
														, m_bDraging( FALSE ) 
														, m_bSizeCursor( FALSE ) 
														, m_bActive( FALSE ) 
														, m_cfText( RGB( 0, 0, 0 ) ) 
														, m_cfMask( RGB( 255, 0, 255 ) ) 
														, m_rectMin( 0, 0, 0, 0 ), m_rectMax( 0, 0, 0, 0 ), m_rectExit( 0, 0, 0, 0 )
														, m_unNcMouseClick( CLICKED_BOX_NONE )
														, m_bControlShow( TRUE )
														, m_bControlDlgStatus( TRUE )
{
	m_CtlColorBrush.CreateSolidBrush( thePNOCtrolskin->GetRGB( PNOCtrl_IDX_RGB_BACKGROUND ) );
	int		i( 0 );
	for( i = 0 ; i < PNOCtrl_IDX_SYSTEMICON_MAX ; i++ )
	{
		m_hBmpWindowCaption[ i ]			= NULL;
		m_sizeWindowCaption[ i ].cx			= 0x00;
		m_sizeWindowCaption[ i ].cy			= 0x00;
	}
}

CPNOCtrl_SkinFrame_CTRL_Dialog::~CPNOCtrl_SkinFrame_CTRL_Dialog()
{
}

BEGIN_MESSAGE_MAP(CPNOCtrl_SkinFrame_CTRL_Dialog, CDialog)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	ON_WM_NCCALCSIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_ENTERSIZEMOVE()
	ON_WM_EXITSIZEMOVE()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCMOUSELEAVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CPNOCtrl_SkinFrame_CTRL_Dialog 메시지 처리기입니다.

int CPNOCtrl_SkinFrame_CTRL_Dialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetskinIMGsize();
	m_hCMin							= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ];
	m_hCMax							= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ];
	m_hCExit						= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ];
	m_hWidth						= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_WIDTH_OFF ];
	m_hHeight						= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF ];
	m_bCreated						= TRUE;					// 초기 작업 완료

	return 0;
}

BOOL CPNOCtrl_SkinFrame_CTRL_Dialog::PreCreateWindow(CREATESTRUCT& cs)
{
	return CDialog::PreCreateWindow(cs);
}

void CPNOCtrl_SkinFrame_CTRL_Dialog::OnDestroy()
{
	CDialog::OnDestroy();
}

void CPNOCtrl_SkinFrame_CTRL_Dialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if( GetWindowLong( GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		CRect				rc;
		GetWindowRect( &rc );

		int width					= rc.Width()+1;
		int height					= rc.Height()+1;

		int					x( 0 ), y( 0 );
		int					round( 9 );
		CRgn				rgnA, rgnB;

		if( nType == SIZE_MAXIMIZED )
		{
			x						= PNOCtrl_MARGIN_MAXIMIZED;
			y						= PNOCtrl_MARGIN_MAXIMIZED;
			width					-= PNOCtrl_MARGIN_MAXIMIZED;
			height					-= PNOCtrl_MARGIN_MAXIMIZED;
		}

		// 전체 영역
		if( (HRGN)m_rgnWnd != NULL )
			m_rgnWnd.DeleteObject();
		m_rgnWnd.CreateRectRgn( x, y, width, height );

		// left-top잘라내기 영역 생성
		rgnA.CreateEllipticRgn( x, y, round, round );
		rgnB.CreateRectRgn( x, y, round / 2, round / 2 );
		rgnA.CombineRgn( &rgnB, &rgnA, RGN_DIFF );

		// left-top영역 잘라냄
		m_rgnWnd.CombineRgn( &m_rgnWnd, &rgnA, RGN_DIFF );
		rgnA.DeleteObject();
		rgnB.DeleteObject();

		// right-top잘라내기 영역 생성
		rgnA.CreateEllipticRgn( width-round, y, width, round );
		rgnB.CreateRectRgn( width-round / 2, y, width, round / 2 );
		rgnA.CombineRgn( &rgnB, &rgnA, RGN_DIFF );

		// right-top영역 잘라냄
		m_rgnWnd.CombineRgn( &m_rgnWnd, &rgnA, RGN_DIFF );
		rgnA.DeleteObject();
		rgnB.DeleteObject();

		// 적용함
		SetWindowRgn( (HRGN)m_rgnWnd, TRUE);
	}
}


void CPNOCtrl_SkinFrame_CTRL_Dialog::OnPaint()
{
	CPaintDC dc(this);

	CRect rc;
	GetClientRect(&rc);
	dc.FillSolidRect( rc, thePNOCtrolskin->GetRGB( PNOCtrl_IDX_RGB_BACKGROUND ) );
}


void CPNOCtrl_SkinFrame_CTRL_Dialog::OnNcPaint()
{
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		DrawFrame();
	}
}


BOOL CPNOCtrl_SkinFrame_CTRL_Dialog::OnNcActivate(BOOL bActive)
{
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		DrawFrame();
		return TRUE;
	}
	else
	{
		return CDialog::OnNcActivate(bActive);
	}
}


void CPNOCtrl_SkinFrame_CTRL_Dialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	int				revision( 0 ), nNCsize( 0 );
	SIZE			size									= { 0, };
	if( thePNOCtrolskin->GetSystemVersion() == SYSOS_WIN7 )
	{
		nNCsize												= 5;
	}

	if( ( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION ) )
	{
		size												= m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ];
		if( size.cy )
		{
			revision										= size.cy - ( GetSystemMetrics( SM_CYCAPTION ) + GetSystemMetrics( SM_CYFRAME ) );
			lpncsp->rgrc[0].top								+= revision;
			lpncsp->rgrc[0].top								+= nNCsize;
		}

		size												= m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_LEFT ];
		if( size.cx )
		{
			revision										= size.cx - GetSystemMetrics( SM_CXFRAME );
			lpncsp->rgrc[0].left								+= revision;
			lpncsp->rgrc[0].left								+= nNCsize;
		}

		size												= m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT ];
		if( size.cx )
		{
			revision										= size.cx - GetSystemMetrics( SM_CXFRAME );
			lpncsp->rgrc[0].right							-= revision;
			lpncsp->rgrc[0].right							-= nNCsize;
		}

		size												= m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_BOTTOM ];
		if( size.cy )
		{
			revision										= size.cy - GetSystemMetrics( SM_CYFRAME );
			lpncsp->rgrc[0].bottom							-= revision;
			lpncsp->rgrc[0].bottom							-= nNCsize;
		}
	}

	if( !IsIconic() )
	{
		CRect								_rect( 0, 0, 0, 0 );
		GetWindowRect( &_rect );
		int									x( 0 ), y( 0 );

		if( IsZoomed() )
		{
			y												= PNOCtrl_MARGIN_MAXIMIZED;
			m_hCMax											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_OFF ];
		} else {
			y												= 4;
			m_hCMax											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ];
		}

		m_rectExit.left										= _rect.Width() - PNOCtrl_MARGIN_BOX - m_sizeWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ].cx;
		m_rectExit.top										= y+2;
		m_rectExit.right									= m_rectExit.left + m_sizeWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ].cx;
		m_rectExit.bottom									= m_rectExit.top + m_sizeWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ].cy;

		m_rectMax.left										= m_rectExit.left - m_sizeWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ].cx;
		m_rectMax.top										= y;
		m_rectMax.right										= m_rectMax.left + m_sizeWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ].cx;
		m_rectMax.bottom									= m_rectMax.top + m_sizeWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ].cy;

		m_rectMin.left										= m_rectMax.left - m_sizeWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ].cx;
		m_rectMin.top										= y;
		m_rectMin.right										= m_rectMin.left + m_sizeWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ].cx;
		m_rectMin.bottom									= m_rectMin.top + m_sizeWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ].cy;

		m_rectWide.left										= m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx + PNOCtrl_MARGIN_MAXIMIZED;
		m_rectWide.top										= y+2;
		m_rectWide.right									= m_rectWide.left + m_sizeWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF ].cx;
		m_rectWide.bottom									= m_rectWide.top + m_sizeWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF ].cy;
	} else {
		m_hCMin												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_OFF ];

		CRect _rect( 0, 0, 0, 0 );
		GetWindowRect( &_rect );
		int									y( 0 );
		y													= PNOCtrl_MARGIN_MAXIMIZED;

		m_rectExit.left										= _rect.Width() - PNOCtrl_MARGIN_BOX - m_sizeWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ].cx;
		m_rectExit.top										= y;
		m_rectExit.right									= m_rectExit.left + m_sizeWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ].cx;
		m_rectExit.bottom									= m_rectExit.top + m_sizeWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ].cy;

		m_rectMax.left										= m_rectExit.left - m_sizeWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ].cx;
		m_rectMax.top										= y;
		m_rectMax.right										= m_rectMax.left + m_sizeWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ].cx;
		m_rectMax.bottom									= m_rectMax.top + m_sizeWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ].cy;

		m_rectMin.left										= m_rectMax.left - m_sizeWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ].cx;
		m_rectMin.top										= y;
		m_rectMin.right										= m_rectMin.left + m_sizeWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ].cx;
		m_rectMin.bottom									= m_rectMin.top + m_sizeWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ].cy;

		m_rectWide.left										= m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx + PNOCtrl_MARGIN_MAXIMIZED;
		m_rectWide.top										= y;
		m_rectWide.right									= m_rectWide.left + m_sizeWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF ].cx;
		m_rectWide.bottom									= m_rectWide.top + m_sizeWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF ].cy;
	}

	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}

// 최대화, 최소화의 크기를 지정.
void CPNOCtrl_SkinFrame_CTRL_Dialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x			= 10;
	lpMMI->ptMinTrackSize.y			= 10;

	CDialog::OnGetMinMaxInfo(lpMMI);
}


void CPNOCtrl_SkinFrame_CTRL_Dialog::OnEnterSizeMove()
{
	if( !m_bDraging )
	{
		m_bDraging = TRUE;
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) ^ WS_EX_LAYERED);
		thePNOCtrolskin->SetLayeredWindowAttributes(m_hWnd, 0, 176, LWA_ALPHA);
		::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}
	m_bTracking = FALSE;
//	CMDIChildWnd::OnEnterSizeMove();
}


void CPNOCtrl_SkinFrame_CTRL_Dialog::OnExitSizeMove()
{
	if( m_bDraging )
	{
		m_bDraging = FALSE;
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
		::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}
	m_bTracking = FALSE;
//	CMDIChildWnd::OnExitSizeMove();
}

void CPNOCtrl_SkinFrame_CTRL_Dialog::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	if( IsIconic() )
	{
		m_hCMin													= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ];

		if(m_unCaptionStyle & PNOCtrl_CAPTION_EXIT)
		{
			m_hWidth												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_WIDTH_OFF ];
			m_hHeight												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF ];
		}
		DrawFrame();
	}

	CDialog::OnNcLButtonDblClk(nHitTest, point);
}

void CPNOCtrl_SkinFrame_CTRL_Dialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	BOOL			bReDraw( FALSE );
	CPoint			localPt( point );
	ScreenToClient( &localPt );

	if( !IsIconic() )
	{
		if( IsZoomed() )	localPt.x							+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
		else				localPt.x							+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
		localPt.y												+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cy );

		if( m_rectMin.PtInRect( localPt ) )
		{
			m_hCMin												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_DOWN ];
			m_unNcMouseClick									= CLICKED_BOX_MINIMIZE;
			bReDraw												= TRUE;
		} else if( m_rectMax.PtInRect( localPt ) )
		{
			if( IsZoomed() )
			{
				m_hCMax											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_DOWN ];
				m_unNcMouseClick								= CLICKED_BOX_RESTORE;
			} else {
				m_hCMax											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_DOWN ];
				m_unNcMouseClick								= CLICKED_BOX_MAXIMIZE;
			}
			bReDraw												= TRUE;
		} else if( m_rectExit.PtInRect( localPt ) )
		{
			m_hCExit											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_ON ];
			m_unNcMouseClick									= CLICKED_BOX_EXIT;
			bReDraw												= TRUE;
		} else if( m_rectWide.PtInRect( localPt ) )
		{
			m_hWidth											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_WIDTH_DOWN ];
			m_hHeight											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_DOWN ];
			m_unNcMouseClick									= CLICKED_BOX_WIDE;
			bReDraw												= TRUE;
		}
	} else {
		localPt.x												-= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
		if( m_rectMin.PtInRect( localPt ) )
		{
			m_hCMin												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_DOWN ];
			m_unNcMouseClick									= CLICKED_BOX_MINIMIZE;
			bReDraw												= TRUE;
		} else if( m_rectMax.PtInRect( localPt ) )
		{
			m_hCMax												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_DOWN ];
			m_unNcMouseClick									= CLICKED_BOX_MAXIMIZE;
			bReDraw												= TRUE;
		} else if( m_rectExit.PtInRect( localPt ) )
		{
			m_hCExit											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_ON ];
			m_unNcMouseClick									= CLICKED_BOX_EXIT;
			bReDraw												= TRUE;
		} else if( m_rectWide.PtInRect( localPt ) )
		{
			m_hWidth											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_WIDTH_OFF ];
			m_hHeight											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF ];
			m_unNcMouseClick									= CLICKED_BOX_WIDE;
			bReDraw												= TRUE;
		} else {
			return ;
		}
	}

	if( bReDraw )
	{
		SetCapture();
		DrawFrame();
		return ;
	}

	if( m_bMoveWindow )
	{
		CDialog::OnNcLButtonDown(nHitTest, point);
	}
}


void CPNOCtrl_SkinFrame_CTRL_Dialog::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	if( m_unNcMouseClick != CLICKED_BOX_NONE )
		ReleaseCapture();

	CPoint			localPt( point );
	ScreenToClient( &localPt );

	if( !IsIconic() )
	{
		if( IsZoomed() )	localPt.x							+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
		else				localPt.x							+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
		localPt.y												+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cy );
	} else {
		localPt.x												-= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
	}

	SetCheckLBtnUp( point );

	CDialog::OnNcLButtonUp(nHitTest, point);
}


void CPNOCtrl_SkinFrame_CTRL_Dialog::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	if( !m_bTracking )
	{	// 마우스가 윈도우를 벗어나면 WM_NCMOUSELEAVE 이벤트가 발생하도록 설정
		m_bTracking = TRUE;
		TRACKMOUSEEVENT t = { sizeof( TRACKMOUSEEVENT ), TME_NONCLIENT | TME_LEAVE, m_hWnd, 0 };
		::TrackMouseEvent( &t );
	}

	if( m_unNcMouseClick == CLICKED_BOX_NONE )
	{
		CPoint			localPt( point );
		ScreenToClient( &localPt );

		if( !IsIconic() )
		{
			if( IsZoomed() )	localPt.x						+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
			else				localPt.x						+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
			localPt.y											+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cy );

			if( m_rectMin.PtInRect( localPt ) )
			{
				m_hCMin											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_ON ];
			} else {
				m_hCMin											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ];
			}

			if( m_rectMax.PtInRect( localPt ) )
			{
				if( IsZoomed() )	m_hCMax						= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_ON ];
				else				m_hCMax						= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_ON ];
			} else {
				if( IsZoomed() )	m_hCMax						= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_OFF ];
				else				m_hCMax						= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ];
			}

			if( m_rectExit.PtInRect( localPt ) )
			{
				m_hCExit										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_ON ];
			} else {
				m_hCExit										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ];
			}

			if( m_rectWide.PtInRect( localPt ) )
			{
				m_hWidth										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_WIDTH_ON ];
				m_hHeight										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_ON ];
			} else {
				m_hWidth										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_WIDTH_OFF ];
				m_hHeight										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF ];
			}
		} else {
			localPt.x											-= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );

			if( m_rectMin.PtInRect( localPt ) )
			{
				m_hCMin											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_ON ];
			} else {
				m_hCMin											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_OFF ];
			}

			if( m_rectMax.PtInRect( localPt ) )
			{
				m_hCMax											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_ON ];
			} else {
				m_hCMax											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ];
			}

			if( m_rectExit.PtInRect( localPt ) )
			{
				m_hCExit										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_ON ];
			} else {
				m_hCExit										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ];
			}

			if( m_rectWide.PtInRect( localPt ) )
			{
				m_hWidth										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_WIDTH_ON ];
				m_hHeight										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_ON ];
			} else {
				m_hWidth										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_WIDTH_OFF ];
				m_hHeight										= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF ];
			}
		}
		DrawFrame();
	}

	CDialog::OnNcMouseMove(nHitTest, point);
}


void CPNOCtrl_SkinFrame_CTRL_Dialog::OnNcMouseLeave()
{
	if( IsIconic() )
	{
		m_hCExit												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ];
		m_hCMax													= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ];
		m_hCMin													= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ];
	} else {
		m_hCExit												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ];
		m_hCMax													= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ];
		m_hCMin													= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ];
	}

	CDialog::OnNcMouseLeave();
}


void CPNOCtrl_SkinFrame_CTRL_Dialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	if( m_unNcMouseClick != CLICKED_BOX_NONE )
		ReleaseCapture();

	CPoint			localPt( point );

	if( !IsIconic() )
	{
		if( IsZoomed() )	localPt.x							+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
		else				localPt.x							+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
		localPt.y												+= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cy );
	} else {
		localPt.x												-= ( m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx );
	}

	SetCheckLBtnUp( localPt );

	CDialog::OnLButtonUp(nFlags, point);
}


void CPNOCtrl_SkinFrame_CTRL_Dialog::SetskinIMGsize()
{
	// 윈도우 스타일 저장
	m_dwOrgStyle = GetStyle();

	ModifyStyle( WS_SYSMENU, 0 );
	ModifyStyle( 0, WS_DLGFRAME | WS_BORDER );
// 	ModifyStyle(0, WS_THICKFRAME | WS_DLGFRAME);			// 기본적으로 리사이징 가능하도록 윈도우 스타일 수정

	m_cfText			= thePNOCtrolskin->GetRGB(PNOCtrl_IDX_RGB_FONT_CAPTION);
	m_cfMask			= thePNOCtrolskin->GetRGB(PNOCtrl_IDX_RGB_MASK);

	//m_unCaptionStyle
	// 각 비트맵의 사이즈 정보를 얻어온다.
	BOOL				bImageGet( FALSE );
	for( int i = IDX_CTRL_SYSTEMICON_CAPTION_LEFT ; i < PNOCtrl_IDX_SYSTEMICON_MAX ; i++ )
	{
		bImageGet = FALSE;
		if( i >= IDX_CTRL_SYSTEMICON_CAPTION_LEFT && i <= IDX_CTRL_SYSTEMICON_FRAME_RIGHT_BOTTOM )
		{
			bImageGet	= TRUE;
		} else {
			if( m_unCaptionStyle & PNOCtrl_CAPTION_MIN )
			{
				if( i == IDX_CTRL_CAPTION_MINIMIZE_ON || i == IDX_CTRL_CAPTION_MINIMIZE_OFF || i == IDX_CTRL_CAPTION_MINIMIZE_DOWN )
					bImageGet	= TRUE;
			}
			if( m_unCaptionStyle & PNOCtrl_CAPTION_MAX )
			{
				if( i == IDX_CTRL_CAPTION_MAXIMIZE_ON || i == IDX_CTRL_CAPTION_MAXIMIZE_OFF || i == IDX_CTRL_CAPTION_MAXIMIZE_DOWN )
					bImageGet	= TRUE;
			}
			if( m_unCaptionStyle & PNOCtrl_CAPTION_EXIT )
			{
				if( i == IDX_CTRL_CAPTION_EXIT_ON || i == IDX_CTRL_CAPTION_EXIT_OFF || i == IDX_CTRL_CAPTION_EXIT_DOWN )
					bImageGet	= TRUE;
				else if( i == IDX_CTRL_CAPTION_WIDTH_ON || i == IDX_CTRL_CAPTION_WIDTH_OFF || i == IDX_CTRL_CAPTION_WIDTH_DOWN )
					bImageGet	= TRUE;
				else if( i == IDX_CTRL_CAPTION_HEIGHT_ON || i == IDX_CTRL_CAPTION_HEIGHT_OFF || i == IDX_CTRL_CAPTION_HEIGHT_DOWN )
					bImageGet	= TRUE;
			}
		}
		if( bImageGet )
		{
			m_sizeWindowCaption[ i ].cx			= thePNOCtrolskin->GetBitmapSize( i ).cx;
			m_sizeWindowCaption[ i ].cy			= thePNOCtrolskin->GetBitmapSize( i ).cy;
			m_hBmpWindowCaption[ i ]			= thePNOCtrolskin->GetBitmap( i );
		}
	}
	m_hIcon				= NULL;
}

void CPNOCtrl_SkinFrame_CTRL_Dialog::DrawFrame()
{
	if( !(GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION) )
		return;

	int x=0,y=0,x2=0,y2=0,cx=0,cy=0;
	CRect rc;
	GetWindowRect(&rc);
	BOOL bIconic = IsIconic();
	BOOL bZoomed = IsZoomed();

	//Non-Client 영역의 DC를 얻어온다.
	CWindowDC dc(this);	

	// 호환성 있는 메모리 DC를 생성(더블버퍼)
	CDC BufferDC, tmpDC;
	BufferDC.CreateCompatibleDC(&dc);
	tmpDC.CreateCompatibleDC(&dc);

	// 메모리 비트맵 선언
	CBitmap bmpBuffer, *pOldBitmap1;
	HGDIOBJ hgdiobj;

	// 호환성 있는 메모리 비트맵 생성하여 메모리 DC에 설정
	bmpBuffer.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	pOldBitmap1 = (CBitmap *)BufferDC.SelectObject(&bmpBuffer);

	BufferDC.FillSolidRect( 0, 0, rc.Width(), rc.Height(), RGB( 227, 227, 227 ) );


	// Left 캡션 비트맵을 메모리 DC로 전송
	x  = 0;
	y  = 0;
	cx = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx;
	cy = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cy;
	hgdiobj = tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Center 캡션 비트맵을 메모리 DC로 전송
	x += cx;
	cx = rc.Width() - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_RIGHT ].cx;
	cy = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_CENTER ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_CENTER ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_CENTER ].cx, m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_CENTER ].cy, SRCCOPY);

	// Right 캡션 비트맵을 메모리 DC로 전송
	x += cx;
	cx = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_RIGHT ].cx;
	cy = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_RIGHT ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_RIGHT ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Left 보더 비트맵을 메모리 DC로 전송
	x = 0;
	y = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cy;
	cx = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_LEFT ].cx;
	cy = rc.Height() - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cy - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_LEFT ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_LEFT ].cx, m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_LEFT ].cy, SRCCOPY);

	// Left-Bottom 보더 비트맵을 메모리 DC로 전송
	y += cy;
	cx = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_LEFT_BOTTOM ].cx;
	cy = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_LEFT_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_LEFT_BOTTOM ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Bottom 보더 비트맵을 메모리 DC로 전송
	x += cx;
	cx = rc.Width() - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_LEFT ].cx - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT ].cx;
	cy = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_BOTTOM ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_BOTTOM ].cx, m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_BOTTOM ].cy, SRCCOPY);

	// Right 보더 비트맵을 메모리 DC로 전송
	x = rc.Width() - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT ].cx;
	y = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_RIGHT ].cy;
	cx = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT ].cx;
	cy = rc.Height() - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_RIGHT ].cy - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT ].cx, m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT ].cy, SRCCOPY);

	// Right-Bottom 보더 비트맵을 메모리 DC로 전송
	x = rc.Width()-m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cx;
	y += cy;
	cx = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cx;
	cy = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT_BOTTOM ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);	

	// 텍스트 배경모드를 설정(투명)
	//	BufferDC.SetBkMode(TRANSPARENT);

	BITMAP csBitmapSize;
	int								nRetValue				= ::GetObject( m_hBmpWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ], sizeof(csBitmapSize), &csBitmapSize );
	DWORD							dwGapSize				= m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cx;

	Gdiplus::Graphics				theGraphics( BufferDC );
	Gdiplus::Font					drawFont( _T("맑은 고딕"), 12, FontStyleRegular, UnitPixel );
	Gdiplus::SolidBrush				drawFontBrush( Color::Black );
	Gdiplus::Pen					drawFontPen( Color::Black );
// 	Gdiplus::StringFormat			drawFontFormat;
// 	drawFontFormat.SetAlignment( StringAlignmentNear );
// 	drawFontFormat.SetLineAlignment( StringAlignmentFar );

	if( !bIconic )
	{
		if( m_unCaptionStyle & PNOCtrl_CAPTION_EXIT )
		{
 			if( m_bControlDlgStatus )
			{
				tmpDC.SelectObject( m_hWidth );
				BufferDC.BitBlt(m_rectWide.left, m_rectWide.top, m_rectWide.Width(), m_rectWide.Height(), &tmpDC, 0, 0, SRCCOPY);
			}
			else
			{
				tmpDC.SelectObject( m_hHeight );
				BufferDC.BitBlt(m_rectWide.left, m_rectWide.top, m_rectWide.Width(), m_rectWide.Height(), &tmpDC, 0, 0, SRCCOPY);
			}
		}

		if( m_dwOrgStyle & WS_MINIMIZEBOX )
		{
			tmpDC.SelectObject( m_hCMin );
			BufferDC.BitBlt(m_rectMin.left, m_rectMin.top, m_rectMin.Width(), m_rectMin.Height(), &tmpDC, 0, 0, SRCCOPY);
		}

		if( m_dwOrgStyle & WS_MAXIMIZEBOX )
		{
			tmpDC.SelectObject( m_hCMax );
			BufferDC.BitBlt(m_rectMax.left, m_rectMax.top, m_rectMax.Width(), m_rectMax.Height(), &tmpDC, 0, 0, SRCCOPY);
		}

		tmpDC.SelectObject( m_hCExit );
		BufferDC.BitBlt(m_rectExit.left, m_rectExit.top, m_rectExit.Width(), m_rectExit.Height(), &tmpDC, 0, 0, SRCCOPY);

		CString str;
		GetWindowText( str );

		SIZE stSize;
		GetTextExtentPoint32(BufferDC.GetSafeHdc(), str, str.GetLength(), &stSize);

		//DWORD dwGapSize = (5 * 2 /*시스템 아이콘 좌우 여백*/);		// + 18/* 시스템 아이콘 폭*/;
		DWORD dwButtonSize = rc.Width() - x;
		DWORD dwTitleSpace = rc.Width() - dwGapSize - dwButtonSize - PNOCtrl_MARGIN_BOX;

		if (dwTitleSpace > (DWORD)stSize.cx)
		{
			Gdiplus::PointF			drawFontPostion( (REAL)dwGapSize, (REAL)( ((DWORD)( csBitmapSize.bmHeight ) - BufferDC.GetTextExtent(str).cy) / 2 ) + 3 );
			theGraphics.DrawString( str, -1, &drawFont, drawFontPostion, &drawFontBrush );
			//			BufferDC.TextOut(dwGapSize, ((DWORD)csBitmapSize.bmHeight - BufferDC.GetTextExtent(str).cy) / 2, str);
		}
		else
		{
			TEXTMETRIC    stFontMetrics;
			BufferDC.GetOutputTextMetrics(&stFontMetrics);

			CString strNew;
			for (int i = str.GetLength(); i > 0; i--)
			{
				if( IsDBCSLeadByteEx( 949, (BYTE)(LPCSTR)( str[i] ) ) )		i--;		// 한글이면 한자 더 빼준다.

				strNew = str.Mid(0, i) + _T("...");

				if ((DWORD)BufferDC.GetTextExtent(strNew).cx < dwTitleSpace)
				{
					break;
				}
			}

			Gdiplus::PointF			drawFontPostion( (REAL)dwGapSize, (REAL)( ((DWORD)csBitmapSize.bmHeight - BufferDC.GetTextExtent(str).cy) / 2 ) + 3 );
			theGraphics.DrawString( strNew, -1, &drawFont, drawFontPostion, &drawFontBrush );
		}

		// 클라이언트 영역을 제거한다.
		x = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_LEFT ].cx;
		y = m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_CAPTION_LEFT ].cy;
		x2 = rc.Width() - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_RIGHT ].cx;
		y2 = rc.Height() - m_sizeWindowCaption[ IDX_CTRL_SYSTEMICON_FRAME_BOTTOM ].cy;	
		dc.ExcludeClipRect(x, y, x2, y2);
	} else {
		tmpDC.SelectObject( m_hCExit );
		BufferDC.BitBlt( m_rectExit.left, m_rectExit.top, m_sizeWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ].cx, m_sizeWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ].cy, &tmpDC, 0, 0, SRCCOPY );

		tmpDC.SelectObject( m_hCMax );
		BufferDC.BitBlt( m_rectMax.left, m_rectMax.top, m_sizeWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ].cx, m_sizeWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ].cy, &tmpDC, 0, 0, SRCCOPY );

		tmpDC.SelectObject( m_hCMin );
		BufferDC.BitBlt( m_rectMin.left, m_rectMin.top, m_sizeWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ].cx, m_sizeWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ].cy, &tmpDC, 0, 0, SRCCOPY );

		CString str;
		GetWindowText( str );
		if( str.GetLength() > 9 )
			str = str.Left( 9 )  +  _T("...");

		Gdiplus::PointF			drawFontPostion( (REAL)dwGapSize, (REAL)( ((DWORD)( csBitmapSize.bmHeight ) - BufferDC.GetTextExtent(str).cy) / 2 ) + 3 );
		theGraphics.DrawString( str, -1, &drawFont, drawFontPostion, &drawFontBrush );
	}
	theGraphics.ReleaseHDC( BufferDC );

	tmpDC.SelectObject( hgdiobj );
	tmpDC.DeleteDC();

	dc.BitBlt( 0, 0, rc.Width(), rc.Height(), &BufferDC, 0, 0, SRCCOPY );

	BufferDC.SelectObject( pOldBitmap1 );
	BufferDC.DeleteDC();
}

void CPNOCtrl_SkinFrame_CTRL_Dialog::GetMonitorInforRect(CRect *pMonitorRect, UINT flags)
{
	HMONITOR				hMonitor						= NULL;
	MONITORINFO				tMonitorInfor					= { 0, };
	RECT					rtRECT							= { 0, };
	CSize					_rectsize( pMonitorRect->Width(), pMonitorRect->Height() );

	hMonitor												= MonitorFromRect(pMonitorRect, MONITOR_DEFAULTTONEAREST);
	tMonitorInfor.cbSize									= sizeof( tMonitorInfor );
	GetMonitorInfo(hMonitor, &tMonitorInfor );

	if (flags & PNOCtrl_MONITOR_WORKAREA)	rtRECT					= tMonitorInfor.rcWork;
	else							rtRECT					= tMonitorInfor.rcMonitor;

	if (flags & PNOCtrl_MONITOR_CENTER)
	{
		pMonitorRect->left									= rtRECT.left + ( rtRECT.right  - rtRECT.left - _rectsize.cx ) / 2;
		pMonitorRect->top									= rtRECT.top  + ( rtRECT.bottom - rtRECT.top  - _rectsize.cy ) / 2;
		pMonitorRect->right									= pMonitorRect->left + _rectsize.cx;
		pMonitorRect->bottom								= pMonitorRect->top  + _rectsize.cy;
	} else if( flags & PNOCtrl_MONITOR_PART_MAX ) {
		pMonitorRect->left									= rtRECT.left;
		pMonitorRect->top									= rtRECT.top;
		pMonitorRect->right									= rtRECT.right;
		pMonitorRect->bottom								= rtRECT.bottom;
	} else {
		pMonitorRect->left									= max(rtRECT.left, min( rtRECT.right - _rectsize.cx,  pMonitorRect->left ) );
		pMonitorRect->top									= max(rtRECT.top,  min( rtRECT.bottom - _rectsize.cy, pMonitorRect->top ) );
		pMonitorRect->right									= pMonitorRect->left + _rectsize.cx;
		pMonitorRect->bottom								= pMonitorRect->top  + _rectsize.cy;
	}
}

void CPNOCtrl_SkinFrame_CTRL_Dialog::SetCheckLBtnUp( CPoint point )
{
	m_hCExit													= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ];
	m_hCMax														= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ];
	m_hCMin														= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ];
	m_hWidth													= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_WIDTH_OFF];
	m_hHeight													= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF];
	if( !IsIconic() )
	{
		if( m_rectWide.PtInRect( point ) && m_unNcMouseClick == CLICKED_BOX_WIDE )
		{		
			m_hWidth												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_WIDTH_OFF ];
			m_hHeight												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_HEIGHT_OFF ];
			AfxGetApp()->GetMainWnd()->SendMessage( PNOCtrl_MAINFRAME_SENDDLGMSG, 2L, 0L );
		} else if( m_rectMin.PtInRect( point ) && m_unNcMouseClick == CLICKED_BOX_MINIMIZE )
		{		
			m_hCMin												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_ON ];
			ShowWindow( SW_MINIMIZE );
		} else if( m_rectMax.PtInRect( point ) && ( m_unNcMouseClick == CLICKED_BOX_RESTORE || m_unNcMouseClick == CLICKED_BOX_MAXIMIZE ) )
		{
			if( m_unNcMouseClick == CLICKED_BOX_RESTORE )
			{
				m_hCMax											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_ON ];
				ShowWindow( SW_RESTORE );
			} else {
				m_hCMax											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_ON ];
				ShowWindow( SW_MAXIMIZE );
			}
		} else if( m_rectExit.PtInRect( point )  && m_unNcMouseClick == CLICKED_BOX_EXIT )
		{
			m_hCExit											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_ON ];
			AfxGetApp()->GetMainWnd()->SendMessage( PNOCtrl_MAINFRAME_SENDDLGMSG, 2L, 1L );
// 			PostMessage(WM_CLOSE, 0, 0);
		}
		m_unNcMouseClick										= CLICKED_BOX_NONE;
	} else {
		if( m_rectMin.PtInRect( point ) && m_unNcMouseClick == CLICKED_BOX_MINIMIZE )
		{		
			m_hCMin												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MINIMIZE_OFF ];
			ShowWindow( SW_RESTORE );
		} else if( m_rectMax.PtInRect( point ) && ( m_unNcMouseClick == CLICKED_BOX_RESTORE || m_unNcMouseClick == CLICKED_BOX_MAXIMIZE ) )
		{
			m_hCMax												= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_ON ];
			ShowWindow( SW_MAXIMIZE );
		} else if( m_rectExit.PtInRect( point )  && m_unNcMouseClick == CLICKED_BOX_EXIT )
		{
			m_hCExit											= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_ON ];
			PostMessage(WM_CLOSE, 0, 0);
		}
		m_unNcMouseClick										= CLICKED_BOX_NONE;
	}
	DrawFrame();
}

void CPNOCtrl_SkinFrame_CTRL_Dialog::SetMiniMizeSysIcons()
{
	m_hCMin														= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_RESTORE_OFF ];
	m_hCMax														= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_MAXIMIZE_OFF ];
	m_hCExit													= m_hBmpWindowCaption[ IDX_CTRL_CAPTION_EXIT_OFF ];
}

void CPNOCtrl_SkinFrame_CTRL_Dialog::ChildFrmReSize()
{
	if( IsIconic() )
	{
		ShowWindow( SW_HIDE );
		ShowWindow( SW_RESTORE );
		ShowWindow( SW_MINIMIZE );
		ShowWindow( SW_SHOW );
	}
}
