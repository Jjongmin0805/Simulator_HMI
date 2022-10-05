#include "pch.h"
#include "PNOCtrl_SkinFrame_POP_Dialog.h"

// CPNOCtrl_SkinFrame_POP_Dialog

IMPLEMENT_DYNAMIC(CPNOCtrl_SkinFrame_POP_Dialog, CDialog)

CPNOCtrl_SkinFrame_POP_Dialog::CPNOCtrl_SkinFrame_POP_Dialog(UINT nIDTemp, CWnd* pParent /*=NULL*/) : CDialog(nIDTemp, pParent), 
	m_bCreated( FALSE ), m_unCaptionStyle( 0x00 ), m_bMoveWindow( FALSE )
	, m_dwMinWidth( 0 ), m_dwMinHeight( 0 ) 
	, m_nClickedBox( CLICKED_BOX_NONE ) 
	, m_bTracking( FALSE ) 
	, m_bDraging( FALSE ) 
	, m_bSizeCursor( FALSE ) 
	, m_bActive( FALSE ) 
	, m_cfText( thePNOCtrolskin->GetRGB(PNOCtrl_IDX_RGB_FONT_CAPTION) ) 
	, m_cfMask( thePNOCtrolskin->GetRGB(PNOCtrl_IDX_RGB_MASK) ) 
	, m_rectMin( 0, 0, 0, 0 ), m_rectMax( 0, 0, 0, 0 ), m_rectExit( 0, 0, 0, 0 )
	, m_unNcMouseClick( CLICKED_BOX_NONE )
{
	m_CtlColorBrush.CreateSolidBrush( thePNOCtrolskin->GetRGB( PNOCtrl_IDX_RGB_BACKGROUND ) );
	int		i( 0 );
	for( i = 0 ; i < PNOCtrl_IDX_SYSTEMICON_MAX ; i++ )
	{
		m_hBmpWindowCaption[ i ]			= NULL;
		m_sizeWindowCaption[ i ].cx			= 0x00;
		m_sizeWindowCaption[ i ].cy			= 0x00;
	}

	ReleaseCapture();
}

CPNOCtrl_SkinFrame_POP_Dialog::~CPNOCtrl_SkinFrame_POP_Dialog()
{
	for(UINT i=0; i<PNOCtrl_IDX_SYSTEMICON_MAX; i++)
	{
		if( m_hBmpWindowCaption[i] )
		{
			::DeleteObject(m_hBmpWindowCaption[i]);
			m_hBmpWindowCaption[i] = NULL;
		}
		::ZeroMemory(&m_hBmpWindowCaption[i], sizeof(BITMAP));
	}

	if( m_hCMin )
	{
		::DeleteObject(m_hCMin);
		m_hCMin = NULL;
	}
	::ZeroMemory(&m_hCMin, sizeof(BITMAP));

	if( m_hCMax )
	{
		::DeleteObject(m_hCMax);
		m_hCMax = NULL;
	}
	::ZeroMemory(&m_hCMax, sizeof(BITMAP));

	if( m_hCExit )
	{
		::DeleteObject(m_hCExit);
		m_hCExit = NULL;
	}
	::ZeroMemory(&m_hCExit, sizeof(BITMAP));

	m_FontBold.DeleteObject();
	m_FontNormal.DeleteObject();
}

BEGIN_MESSAGE_MAP(CPNOCtrl_SkinFrame_POP_Dialog, CDialog)
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
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CPNOCtrl_SkinFrame_POP_Dialog 메시지 처리기입니다.

int CPNOCtrl_SkinFrame_POP_Dialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetskinIMGsize();
	m_hCMin							= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ];
	m_hCMax							= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];
	m_hCExit						= m_hBmpWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ];

	m_bCreated						= TRUE;					// 초기 작업 완료

	m_FontBold.CreateFont(17,0,0,0,FW_BOLD,0,0,0,0,0,0,0,0,_T("맑은 고딕"));
	m_FontNormal.CreateFont(17,0,0,0,FW_NORMAL,0,0,0,0,0,0,0,0,_T("맑은 고딕"));

	return 0;
}

BOOL CPNOCtrl_SkinFrame_POP_Dialog::PreCreateWindow(CREATESTRUCT& cs)
{
	return CDialog::PreCreateWindow(cs);
}

void CPNOCtrl_SkinFrame_POP_Dialog::OnDestroy()
{
	CDialog::OnDestroy();
}

void CPNOCtrl_SkinFrame_POP_Dialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		CRect rc;
		GetWindowRect(&rc);

		int width		= rc.Width()+1;
		int height		= rc.Height()+1;

		int x = 0, y = 0;
		int round = 1;
		CRgn rgnA, rgnB;

		if( nType == SIZE_MAXIMIZED )
		{
			x			= PNOCtrl_MARGIN_MAXIMIZED;
			y			= PNOCtrl_MARGIN_MAXIMIZED;
			width		-= PNOCtrl_MARGIN_MAXIMIZED;
			height		-= PNOCtrl_MARGIN_MAXIMIZED;
		}

		// 전체 영역
		if( (HRGN)m_rgnWnd != NULL )
			m_rgnWnd.DeleteObject();
		m_rgnWnd.CreateRectRgn( x, y, width, height );

		// left-top잘라내기 영역 생성
		rgnA.CreateEllipticRgn(x, y, round, round);
		rgnB.CreateRectRgn(x, y, round/2, round/2);
		rgnA.CombineRgn(&rgnB, &rgnA, RGN_DIFF);

		// left-top영역 잘라냄
		m_rgnWnd.CombineRgn(&m_rgnWnd, &rgnA, RGN_DIFF);
		rgnA.DeleteObject();
		rgnB.DeleteObject();

		// right-top잘라내기 영역 생성
		rgnA.CreateEllipticRgn(width-round, y, width, round);
		rgnB.CreateRectRgn(width-round/2, y, width, round/2);
		rgnA.CombineRgn(&rgnB, &rgnA, RGN_DIFF);

		// right-top영역 잘라냄
		m_rgnWnd.CombineRgn(&m_rgnWnd, &rgnA, RGN_DIFF);
		rgnA.DeleteObject();
		rgnB.DeleteObject();

		// 적용함
		SetWindowRgn((HRGN)m_rgnWnd, TRUE);
	}

	if( IsZoomed() )
	{
		AfxGetApp()->GetMainWnd()->SendMessage( PNOCtrl_MAINFRAME_SENDMSG, (WPARAM)1L, (LPARAM)1L );
	} else if( IsIconic() )
	{
		AfxGetApp()->GetMainWnd()->SendMessage( PNOCtrl_MAINFRAME_SENDMSG, (WPARAM)1L, (LPARAM)2L );
	} else {
		AfxGetApp()->GetMainWnd()->SendMessage( PNOCtrl_MAINFRAME_SENDMSG, (WPARAM)1L, (LPARAM)0L );
	}
}


void CPNOCtrl_SkinFrame_POP_Dialog::OnPaint()
{
	CPaintDC dc(this);

	CRect rc, ctrRect;
	GetClientRect(&rc);
	dc.FillSolidRect( rc, thePNOCtrolskin->GetRGB( PNOCtrl_IDX_RGB_BACKGROUND ) );
}


void CPNOCtrl_SkinFrame_POP_Dialog::OnNcPaint()
{
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		DrawFrame();
	}
}


BOOL CPNOCtrl_SkinFrame_POP_Dialog::OnNcActivate(BOOL bActive)
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


void CPNOCtrl_SkinFrame_POP_Dialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	int				revision( 0 );
	SIZE			size									= { 0, };

	if( ( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION ) )
	{
		int				nBorderMargin_X, nBorderMargin_Y;
		nBorderMargin_X = GetSystemMetrics(SM_CXFRAME) + 4;
		nBorderMargin_Y = GetSystemMetrics(SM_CYFRAME) + 4;

		size												= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ];
		if( size.cy )
		{
			revision										= size.cy - ( GetSystemMetrics( SM_CYCAPTION ) + nBorderMargin_Y);
			lpncsp->rgrc[0].top								+= revision;
		}

		size												= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_LEFT ];
		if( size.cx )
		{
			revision										= size.cx - nBorderMargin_X;
			lpncsp->rgrc[0].left							+= revision;
		}

		size												= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT ];
		if( size.cx )
		{
			revision										= size.cx - nBorderMargin_X;
			lpncsp->rgrc[0].right							-= revision;
		}
		size												= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_BOTTOM ];
		if( size.cy )
		{
			revision										= size.cy - nBorderMargin_Y;
			lpncsp->rgrc[0].bottom							-= revision;
		}
	}

	// 	if( IsZoomed() )
	// 	{
	// 		CRect												pReSizeing( lpncsp->rgrc[0] );
	// 		pReSizeing.DeflateRect( 0, 5, 0, 0 );
	// 		lpncsp->rgrc[0]										= pReSizeing;
	// 	}

	if( !IsIconic() )
	{
		CRect _rect( 0, 0, 0, 0 );
		GetWindowRect( &_rect );
		int									x( 0 ), y( 0 );
		if( IsZoomed() )
		{
			y												= PNOCtrl_MARGIN_MAXIMIZED;
			m_hCMax											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
		} else {
			y												= 2;
			m_hCMax											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];
		}

		m_rectExit.left										= _rect.Width() - PNOCtrl_MARGIN_BOX - m_sizeWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ].cx;
		m_rectExit.top										= y;
		m_rectExit.right									= m_rectExit.left + m_sizeWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ].cx;
		m_rectExit.bottom									= m_rectExit.top + m_sizeWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ].cy;

		m_rectMax.left										= m_rectExit.left - m_sizeWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ].cx;
		m_rectMax.top										= y;
		m_rectMax.right										= m_rectMax.left + m_sizeWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ].cx;
		m_rectMax.bottom									= m_rectMax.top + m_sizeWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ].cy;

		m_rectMin.left										= m_rectMax.left - m_sizeWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ].cx;
		m_rectMin.top										= y;
		m_rectMin.right										= m_rectMin.left + m_sizeWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ].cx;
		m_rectMin.bottom									= m_rectMin.top + m_sizeWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ].cy;
	} else {
		m_hCMin												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];

		CRect _rect( 0, 0, 0, 0 );
		GetWindowRect( &_rect );
		int													y( 0 );
		y													= PNOCtrl_MARGIN_MAXIMIZED;
		m_rectExit.left										= _rect.Width() - PNOCtrl_MARGIN_BOX - m_sizeWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ].cx;
		m_rectExit.top										= y;
		m_rectExit.right									= m_rectExit.left + m_sizeWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ].cx;
		m_rectExit.bottom									= m_rectExit.top + m_sizeWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ].cy;

		m_rectMax.left										= m_rectExit.left - m_sizeWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ].cx;
		m_rectMax.top										= y;
		m_rectMax.right										= m_rectMax.left + m_sizeWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ].cx;
		m_rectMax.bottom									= m_rectMax.top + m_sizeWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ].cy;

		m_rectMin.left										= m_rectMax.left - m_sizeWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ].cx;
		m_rectMin.top										= y;
		m_rectMin.right										= m_rectMin.left + m_sizeWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ].cx;
		m_rectMin.bottom									= m_rectMin.top + m_sizeWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ].cy;
	}

	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}

// 최대화, 최소화의 크기를 지정.
void CPNOCtrl_SkinFrame_POP_Dialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CDialog::OnGetMinMaxInfo(lpMMI);
}


void CPNOCtrl_SkinFrame_POP_Dialog::OnEnterSizeMove()
{
	if( !m_bDraging )
	{
		m_bDraging = TRUE;
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) ^ WS_EX_LAYERED);
		thePNOCtrolskin->SetLayeredWindowAttributes(m_hWnd, 0, 176, LWA_ALPHA);
		::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}
	m_bTracking = FALSE;
	//	CDialog::OnEnterSizeMove();
}


void CPNOCtrl_SkinFrame_POP_Dialog::OnExitSizeMove()
{
	if( m_bDraging )
	{
		m_bDraging = FALSE;
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
		::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}
	m_bTracking = FALSE;
	//	CDialog::OnExitSizeMove();
}

void CPNOCtrl_SkinFrame_POP_Dialog::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	if( IsIconic() )
	{
		m_hCMin													= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ];
		DrawFrame();
	}

	CDialog::OnNcLButtonDblClk(nHitTest, point);
}

void CPNOCtrl_SkinFrame_POP_Dialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	BOOL			bReDraw( FALSE );
	CPoint			localPt( point );
	ScreenToClient( &localPt );

	if( !IsIconic() )
	{
		if( IsZoomed() )	localPt.x							+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx );
		else				localPt.x							+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx - 4 );
		localPt.y												+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cy + 2 );

		if( ( m_dwOrgStyle & WS_MINIMIZEBOX ) && ( m_rectMin.PtInRect( localPt ) ) )
		{
			m_hCMin												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_DOWN ];
			m_unNcMouseClick									= CLICKED_BOX_MINIMIZE;
			bReDraw												= TRUE;
		} else if( ( m_dwOrgStyle & WS_MAXIMIZEBOX ) && ( m_rectMax.PtInRect( localPt ) ) )
		{
			if( IsZoomed() )
			{
				m_hCMax											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_DOWN ];
				m_unNcMouseClick								= CLICKED_BOX_RESTORE;
			} else {
				m_hCMax											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_DOWN ];
				m_unNcMouseClick								= CLICKED_BOX_MAXIMIZE;
			}
			bReDraw												= TRUE;
		} else if( m_hCExit && ( m_rectExit.PtInRect( localPt ) ) )
		{
			m_hCExit											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_EXIT_DOWN ];
			m_unNcMouseClick									= CLICKED_BOX_EXIT;
			bReDraw												= TRUE;
		}
	} else {
		localPt.x												-= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx );
		if( ( m_dwOrgStyle & WS_MINIMIZEBOX ) && ( m_rectMin.PtInRect( localPt ) ) )
		{
			m_hCMin												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_DOWN ];
			m_unNcMouseClick									= CLICKED_BOX_MINIMIZE;
			bReDraw												= TRUE;
		} else if( ( m_dwOrgStyle & WS_MAXIMIZEBOX ) && ( m_rectMax.PtInRect( localPt ) ) )
		{
			m_hCMax												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_DOWN ];
			m_unNcMouseClick									= CLICKED_BOX_MAXIMIZE;
			bReDraw												= TRUE;
		} else if( m_hCExit && ( m_rectExit.PtInRect( localPt ) ) )
		{
			m_hCExit											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_EXIT_DOWN ];
			m_unNcMouseClick									= CLICKED_BOX_EXIT;
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

	CDialog::OnNcLButtonDown(nHitTest, point);
}


void CPNOCtrl_SkinFrame_POP_Dialog::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	if( m_unNcMouseClick != CLICKED_BOX_NONE )
		ReleaseCapture();

	CPoint			localPt( point );
	ScreenToClient( &localPt );

	if( !IsIconic() )
	{
		if( IsZoomed() )	localPt.x							+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx );
		else				localPt.x							+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx - 4 );
		localPt.y												+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cy + 2 );
	} else {
		localPt.x												-= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx );
	}

	SetCheckLBtnUp( point );

	CDialog::OnNcLButtonUp(nHitTest, point);
}


void CPNOCtrl_SkinFrame_POP_Dialog::OnNcMouseMove(UINT nHitTest, CPoint point)
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
			if( IsZoomed() )	localPt.x						+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx );
			else				localPt.x						+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx - 4 );
			localPt.y											+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cy + 2 );

			if( m_rectMin.PtInRect( localPt ) )
			{
				m_hCMin											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_ON ];
			} else {
				m_hCMin											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ];
			}

			if( m_rectMax.PtInRect( localPt ) )
			{
				if( IsZoomed() )	m_hCMax						= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_ON ];
				else				m_hCMax						= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_ON ];
			} else {
				if( IsZoomed() )	m_hCMax						= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
				else				m_hCMax						= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];
			}

			if( m_rectExit.PtInRect( localPt ) )
			{
				m_hCExit										= m_hBmpWindowCaption[ IDX_DLG_CAPTION_EXIT_ON ];
			} else {
				m_hCExit										= m_hBmpWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ];
			}
		} else {
			localPt.x											-= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx );

			if( m_rectMin.PtInRect( localPt ) )
			{
				m_hCMin											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_ON ];
			} else {
				m_hCMin											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
			}

			if( m_rectMax.PtInRect( localPt ) )
			{
				m_hCMax											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_ON ];
			} else {
				m_hCMax											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];
			}

			if( m_rectExit.PtInRect( localPt ) )
			{
				m_hCExit										= m_hBmpWindowCaption[ IDX_DLG_CAPTION_EXIT_ON ];
			} else {
				m_hCExit										= m_hBmpWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ];
			}
		}
		DrawFrame();
	}

	CDialog::OnNcMouseMove(nHitTest, point);
}


void CPNOCtrl_SkinFrame_POP_Dialog::OnNcMouseLeave()
{
	m_hCExit												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ];
	m_hCMax													= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];
	m_hCMin													= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ];

	CDialog::OnNcMouseLeave();
}


void CPNOCtrl_SkinFrame_POP_Dialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	if( m_unNcMouseClick != CLICKED_BOX_NONE )
		ReleaseCapture();

	CPoint			localPt( point );

	if( !IsIconic() )
	{
		if( IsZoomed() )	localPt.x							+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx );
		else				localPt.x							+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx - 4 );
		localPt.y												+= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cy + 2 );
	} else {
		localPt.x												-= ( m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx );
	}

	SetCheckLBtnUp( localPt );

	CDialog::OnLButtonUp(nFlags, point);
}


void CPNOCtrl_SkinFrame_POP_Dialog::SetskinIMGsize()
{
	// 윈도우 스타일 저장
	m_dwOrgStyle = GetStyle();

	ModifyStyle( WS_SYSMENU, 0 );
// 	ModifyStyle( 0, WS_DLGFRAME | WS_BORDER );
	ModifyStyle(0, WS_THICKFRAME | WS_DLGFRAME);			// 기본적으로 리사이징 가능하도록 윈도우 스타일 수정

	m_cfText			= thePNOCtrolskin->GetRGB(PNOCtrl_IDX_RGB_FONT_CAPTION);
	m_cfMask			= thePNOCtrolskin->GetRGB(PNOCtrl_IDX_RGB_MASK);

	// 각 비트맵의 사이즈 정보를 얻어온다.
	for( int i = IDX_CTRL_SYSTEMICON_CAPTION_LEFT ; i < PNOCtrl_IDX_SYSTEMICON_MAX ; i++ )
	{
		m_sizeWindowCaption[ i ].cx			= thePNOCtrolskin->GetBitmapSize( i ).cx;
		m_sizeWindowCaption[ i ].cy			= thePNOCtrolskin->GetBitmapSize( i ).cy;
		m_hBmpWindowCaption[ i ]			= thePNOCtrolskin->GetBitmap( i );
	}

//	m_hIcon				= thePNOCtrolskin->GetIcon(IDX_ICON_MAIN,PNOCtrl_ICON32);
	m_hIcon				= NULL;
}

void CPNOCtrl_SkinFrame_POP_Dialog::DrawFrame()
{
	if( !(GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION) )
		return;

// 	BeginWaitCursor();

	int x( 0 ), y( 0 ), x2( 0 ), y2( 0 ), cx( 0 ), cy( 0 );
	CRect				rc( 0, 0, 0, 0 );
	GetWindowRect( &rc );
	BOOL				bIconic = IsIconic();
	BOOL				bZoomed = IsZoomed();

	//Non-Client 영역의 DC를 얻어온다.
	CWindowDC			dc( this );	

	// 호환성 있는 메모리 DC를 생성(더블버퍼)
	CDC					BufferDC, tmpDC;
	BufferDC.CreateCompatibleDC(&dc);
	tmpDC.CreateCompatibleDC(&dc);

	// 메모리 비트맵 선언
	CBitmap				bmpBuffer, *pOldBitmap1;
	HGDIOBJ				hgdiobj;

	// 호환성 있는 메모리 비트맵 생성하여 메모리 DC에 설정
	bmpBuffer.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	pOldBitmap1			= (CBitmap *)BufferDC.SelectObject(&bmpBuffer);

	BufferDC.FillSolidRect( 0, 0, rc.Width(), rc.Height(), PNOCtrl_COLOR_FRAME );


	// Left 캡션 비트맵을 메모리 DC로 전송
	x					= 0;
	y					= 0;
	cx					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx;
	cy					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cy;
	hgdiobj				= tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Center 캡션 비트맵을 메모리 DC로 전송
	x					+= cx;
	cx					= rc.Width() - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_RIGHT ].cx;
	cy					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_CENTER ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_CENTER ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_CENTER ].cx, m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_CENTER ].cy, SRCCOPY);

	// Right 캡션 비트맵을 메모리 DC로 전송
	x					+= cx;
	cx					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_RIGHT ].cx;
	cy					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_RIGHT ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_RIGHT ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Left 보더 비트맵을 메모리 DC로 전송
	x					= 0;
	y					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cy;
	cx					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_LEFT ].cx;
	cy					= rc.Height() - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cy - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_LEFT ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_LEFT ].cx, m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_LEFT ].cy, SRCCOPY);

	// Left-Bottom 보더 비트맵을 메모리 DC로 전송
	y					+= cy;
	cx					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_LEFT_BOTTOM ].cx;
	cy					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_LEFT_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_LEFT_BOTTOM ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Bottom 보더 비트맵을 메모리 DC로 전송
	x					+= cx;
	cx					= rc.Width() - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_LEFT ].cx - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT ].cx;
	cy					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_BOTTOM ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_BOTTOM ].cx, m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_BOTTOM ].cy, SRCCOPY);

	// Right 보더 비트맵을 메모리 DC로 전송
	x					= rc.Width() - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT ].cx;
	y					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_RIGHT ].cy;
	cx					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT ].cx;
	cy					= rc.Height() - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_RIGHT ].cy - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT ].cx, m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT ].cy, SRCCOPY);

	// Right-Bottom 보더 비트맵을 메모리 DC로 전송
	x					= rc.Width()-m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cx;
	y					+= cy;
	cx					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cx;
	cy					= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT_BOTTOM ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);	

	// 텍스트 배경모드를 설정(투명)
	//	BufferDC.SetBkMode(TRANSPARENT);

	BITMAP csBitmapSize;
	int								nRetValue				= ::GetObject( m_hBmpWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ], sizeof(csBitmapSize), &csBitmapSize );
	DWORD							dwGapSize				= m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cx;

	Gdiplus::Graphics				theGraphics( BufferDC );
	Gdiplus::Font					drawFont( _T("맑은 고딕"), 14, FontStyleBold, UnitPixel );
	Gdiplus::SolidBrush				drawFontBrush( Gdiplus::Color( 255, 255, 255, 255 ) );
	Gdiplus::StringFormat			drawFontFormat;
	drawFontFormat.SetAlignment( StringAlignmentNear );
	drawFontFormat.SetLineAlignment( StringAlignmentFar );

	if( !bIconic )
	{
		if( m_hCMin && ( m_dwOrgStyle & WS_MINIMIZEBOX ) )
		{
			tmpDC.SelectObject( m_hCMin );
			BufferDC.BitBlt(m_rectMin.left, m_rectMin.top, m_rectMin.Width(), m_rectMin.Height(), &tmpDC, 0, 0, SRCCOPY);
		}

		if( m_hCMax && ( m_dwOrgStyle & WS_MAXIMIZEBOX ) )
		{
			tmpDC.SelectObject( m_hCMax );
			BufferDC.BitBlt(m_rectMax.left, m_rectMax.top, m_rectMax.Width(), m_rectMax.Height(), &tmpDC, 0, 0, SRCCOPY);
		}

		if( m_hCExit )
		{
			tmpDC.SelectObject( m_hCExit );
			BufferDC.BitBlt(m_rectExit.left, m_rectExit.top, m_rectExit.Width(), m_rectExit.Height(), &tmpDC, 0, 0, SRCCOPY);
		}

		CString str;
		GetWindowText( str );

		SIZE stSize;
		GetTextExtentPoint32(BufferDC.GetSafeHdc(), str, str.GetLength(), &stSize);

		//DWORD dwGapSize = (5 * 2 /*시스템 아이콘 좌우 여백*/);		// + 18/* 시스템 아이콘 폭*/;
		DWORD dwButtonSize = rc.Width() - x;
		DWORD dwTitleSpace = rc.Width() - dwGapSize - dwButtonSize - PNOCtrl_MARGIN_BOX;

		if (dwTitleSpace > (DWORD)stSize.cx)
		{
			Gdiplus::PointF			drawFontPostion( (REAL)dwGapSize, (REAL)( ((DWORD)( csBitmapSize.bmHeight ) - BufferDC.GetTextExtent(str).cy) / 2 ) );
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

			Gdiplus::PointF			drawFontPostion( (REAL)dwGapSize, (REAL)( ((DWORD)csBitmapSize.bmHeight - BufferDC.GetTextExtent(str).cy) / 2 ) );
			theGraphics.DrawString( strNew, -1, &drawFont, drawFontPostion, &drawFontBrush );
		}

		// 클라이언트 영역을 제거한다.
		x = m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_LEFT ].cx;
		y = m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_CAPTION_LEFT ].cy;
		x2 = rc.Width() - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_RIGHT ].cx;
		y2 = rc.Height() - m_sizeWindowCaption[ IDX_DLG_SYSTEMICON_FRAME_BOTTOM ].cy;	
		dc.ExcludeClipRect(x, y, x2, y2);
	} else {
		tmpDC.SelectObject( m_hCExit );
		//		x = rc.Width() - PNOCtrl_MARGIN_BOX - m_sizeWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ].cx;
		BufferDC.BitBlt( m_rectExit.left, m_rectExit.top, m_sizeWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ].cx, m_sizeWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ].cy, &tmpDC, 0, 0, SRCCOPY );

		tmpDC.SelectObject( m_hCMax );
		//		x = x - m_sizeWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ].cx;			
		BufferDC.BitBlt( m_rectMax.left, m_rectMax.top, m_sizeWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ].cx, m_sizeWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ].cy, &tmpDC, 0, 0, SRCCOPY );

		tmpDC.SelectObject( m_hCMin );
		//		x = x - m_sizeWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ].cx;		
		BufferDC.BitBlt( m_rectMin.left, m_rectMin.top, m_sizeWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ].cx, m_sizeWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ].cy, &tmpDC, 0, 0, SRCCOPY );

		CString str;
		GetWindowText( str );
		if( str.GetLength() > 9 )
			str = str.Left( 9 )  +  _T("...");

		Gdiplus::PointF			drawFontPostion( (REAL)dwGapSize, (REAL)( ((DWORD)( csBitmapSize.bmHeight ) - BufferDC.GetTextExtent(str).cy) / 2 ) );
		theGraphics.DrawString( str, -1, &drawFont, drawFontPostion, &drawFontBrush );
	}
	theGraphics.ReleaseHDC( BufferDC );

	tmpDC.SelectObject( hgdiobj );
	tmpDC.DeleteDC();

	dc.BitBlt( 0, 0, rc.Width(), rc.Height(), &BufferDC, 0, 0, SRCCOPY );

	BufferDC.SelectObject( pOldBitmap1 );
	BufferDC.DeleteDC();

// 	EndWaitCursor();
}

void CPNOCtrl_SkinFrame_POP_Dialog::GetMonitorInforRect(CRect *pMonitorRect, UINT flags)
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

void CPNOCtrl_SkinFrame_POP_Dialog::SetCheckLBtnUp( CPoint point )
{
	m_hCExit													= m_hBmpWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ];

	if( !IsIconic() )
	{
		m_hCMin													= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ];
		if( IsZoomed() )										m_hCMax	= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
		else													m_hCMax	= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];

		if( m_rectMin.PtInRect( point ) && m_unNcMouseClick == CLICKED_BOX_MINIMIZE )
		{		
			ShowWindow( SW_MINIMIZE );

			m_hCMin												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
			m_hCMax												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];
		} else if( m_rectMax.PtInRect( point ) && ( m_unNcMouseClick == CLICKED_BOX_RESTORE || m_unNcMouseClick == CLICKED_BOX_MAXIMIZE ) )
		{
			if( m_unNcMouseClick == CLICKED_BOX_RESTORE )
			{
				ShowWindow( SW_RESTORE );
				m_hCMax											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];
			} else {
				ShowWindow( SW_MAXIMIZE );
				m_hCMax											= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
			}
		} else if( m_rectExit.PtInRect( point )  && m_unNcMouseClick == CLICKED_BOX_EXIT )
		{
			PostMessage(WM_CLOSE, 0, 0);
		}
		m_unNcMouseClick										= CLICKED_BOX_NONE;
	} else {
		m_hCMin													= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
		m_hCMax													= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];

		if( m_rectMin.PtInRect( point ) && m_unNcMouseClick == CLICKED_BOX_MINIMIZE )
		{		
			ShowWindow( SW_RESTORE );

			m_hCMin												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ];
			if( IsZoomed() )									m_hCMax	= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
			else												m_hCMax	= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];
		} else if( m_rectMax.PtInRect( point ) && ( m_unNcMouseClick == CLICKED_BOX_RESTORE || m_unNcMouseClick == CLICKED_BOX_MAXIMIZE ) )
		{
			ShowWindow( SW_MAXIMIZE );

			m_hCMin												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ];
			m_hCMax												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
		} else if( m_rectExit.PtInRect( point )  && m_unNcMouseClick == CLICKED_BOX_EXIT )
		{
			PostMessage(WM_CLOSE, 0, 0);
		}
		m_unNcMouseClick										= CLICKED_BOX_NONE;
	}
	DrawFrame();
}

void CPNOCtrl_SkinFrame_POP_Dialog::ShowRestored()
{
	if( IsIconic() )
	{
		ShowWindow( SW_RESTORE );

		m_hCMin												= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MINIMIZE_OFF ];
		if( IsZoomed() )									m_hCMax	= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
		else												m_hCMax	= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];

		DrawFrame();
	}
}

void CPNOCtrl_SkinFrame_POP_Dialog::SetMiniMizeSysIcons()
{
	m_hCMin														= m_hBmpWindowCaption[ IDX_DLG_CAPTION_RESTORE_OFF ];
	m_hCMax														= m_hBmpWindowCaption[ IDX_DLG_CAPTION_MAXIMIZE_OFF ];
	m_hCExit													= m_hBmpWindowCaption[ IDX_DLG_CAPTION_EXIT_OFF ];
}

void CPNOCtrl_SkinFrame_POP_Dialog::ChildFrmReSize()
{
	if( IsIconic() )
	{
		ShowWindow( SW_HIDE );
		ShowWindow( SW_RESTORE );
		ShowWindow( SW_MINIMIZE );
		ShowWindow( SW_SHOW );
	}
}

HBRUSH CPNOCtrl_SkinFrame_POP_Dialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if( nCtlColor == CTLCOLOR_STATIC )
	{
		static CBrush s_brush(thePNOCtrolskin->GetRGB(PNOCtrl_IDX_RGB_BACKGROUND));
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(thePNOCtrolskin->GetRGB(PNOCtrl_IDX_RGB_FONT_CAPTION));
		pDC->SetBkColor(thePNOCtrolskin->GetRGB(PNOCtrl_IDX_RGB_BACKGROUND));
		return s_brush;
	}	
	return hbr;
}