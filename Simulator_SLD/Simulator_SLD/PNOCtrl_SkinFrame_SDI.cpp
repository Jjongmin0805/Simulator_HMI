// PNOCtrl_SkinFrame_SDI.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "PNOCtrl_SkinFrame_SDI.h"
#include "SkinMng.h"

// CPNOCtrl_SkinFrame_SDI

IMPLEMENT_DYNCREATE(CPNOCtrl_SkinFrame_SDI, CFrameWnd)

CPNOCtrl_SkinFrame_SDI::CPNOCtrl_SkinFrame_SDI() :
	m_pOriWVMFSize( 0, 0 ), m_pWVMFSize( 0, 0 ), m_bCreated( FALSE )
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
{
	m_CtlColorBrush.CreateSolidBrush( theskin->GetRGB( IDX_RGB_BACKGROUND ) );
	int		i( 0 );
	for( i = 0 ; i < IDX_SYSTEMICON_MAX ; i++ )
	{
		m_hBmpWindowCaption[ i ]			= NULL;
		m_sizeWindowCaption[ i ].cx			= 0x00;
		m_sizeWindowCaption[ i ].cy			= 0x00;
	}
}

CPNOCtrl_SkinFrame_SDI::~CPNOCtrl_SkinFrame_SDI()
{
}


BEGIN_MESSAGE_MAP(CPNOCtrl_SkinFrame_SDI, CFrameWnd)
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


// CPNOCtrl_SkinFrame_SDI 메시지 처리기입니다.
int CPNOCtrl_SkinFrame_SDI::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect		_wndRect, _clientRect;
	GetClientRect( _clientRect );
	GetWindowRect( _wndRect );
	m_pOriWVMFSize.cx				= int( ( _wndRect.Width() - _clientRect.Width() ) / 2 ) - 3;
	m_pOriWVMFSize.cy				= m_pOriWVMFSize.cx;
	m_pWVMFSize						= m_pOriWVMFSize;

	SetskinIMGsize();
	m_hCMin							= m_hBmpWindowCaption[ IDX_CAPTION_MINIMIZE_OFF ];
	m_hCMax							= m_hBmpWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ];
	m_hCExit						= m_hBmpWindowCaption[ IDX_CAPTION_EXIT_OFF ];

	m_bCreated						= TRUE;					// 초기 작업 완료

	return 0;
}


BOOL CPNOCtrl_SkinFrame_SDI::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFrameWnd::PreCreateWindow(cs);
}

void CPNOCtrl_SkinFrame_SDI::OnDestroy()
{
	CFrameWnd::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CPNOCtrl_SkinFrame_SDI::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	//	제목 표시줄이 겹치므로인해 잠시 막음.
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		CRect rc;
		GetWindowRect(&rc);

		int width		= rc.Width()+1;
		int height		= rc.Height()+1;

		int x = 0, y = 0;
		int round = 9;
		CRgn rgnA, rgnB;

		if( nType == SIZE_MAXIMIZED )
		{
			x			= ( MARGIN_MAXIMIZED + m_pWVMFSize.cx - 1 );
			y			= ( MARGIN_MAXIMIZED + m_pWVMFSize.cy - 1 );
			width		-= ( MARGIN_MAXIMIZED + m_pWVMFSize.cx );
			height		-= ( MARGIN_MAXIMIZED + m_pWVMFSize.cy );
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
}

void CPNOCtrl_SkinFrame_SDI::OnPaint()
{
	CPaintDC dc(this);

	CRect rc;
	GetClientRect(&rc);
	dc.FillSolidRect( rc, theskin->GetRGB( IDX_RGB_BACKGROUND ) );
}


void CPNOCtrl_SkinFrame_SDI::OnNcPaint()
{
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		DrawFrame();
	}
}


BOOL CPNOCtrl_SkinFrame_SDI::OnNcActivate(BOOL bActive)
{
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
//		DrawFrame();
		return TRUE;
	}
	else
	{
		return CFrameWnd::OnNcActivate(bActive);
	}
}


void CPNOCtrl_SkinFrame_SDI::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if( m_bCreated )
	{
		if( IsZoomed() )
		{
			m_pWVMFSize								= m_pOriWVMFSize;
		} else {
			m_pWVMFSize								= CSize( 0, 0 );
		}
		for( int i = 0 ; i <= IDX_SYSTEMICON_FRAME_RIGHT_BOTTOM ; i++ )
		{
			m_sizeWindowCaption[ i ].cx			= theskin->GetBitmapSize( i ).cx + m_pWVMFSize.cx;
			m_sizeWindowCaption[ i ].cy			= theskin->GetBitmapSize( i ).cy + m_pWVMFSize.cy;
		}
	}

	int				revision( 0 );
	SIZE			size = { 0, };

	if( ( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION ) )		//&& !IsZoomed()
	{
		int				nBorderMargin_X, nBorderMargin_Y;
		nBorderMargin_X = GetSystemMetrics(SM_CXFRAME) + 4;
		nBorderMargin_Y = GetSystemMetrics(SM_CYFRAME) + 4;

		size			= m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ];
		if( size.cy )
		{
			revision = size.cy - ( GetSystemMetrics( SM_CYCAPTION ) + nBorderMargin_Y);
			lpncsp->rgrc[0].top += revision;
		}

		size			= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_LEFT ];
		if( size.cx )
		{
			revision = size.cx - nBorderMargin_X;
			lpncsp->rgrc[0].left += revision;
		}

		size			= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT ];
		if( size.cx )
		{
			revision = size.cx - nBorderMargin_X;
			lpncsp->rgrc[0].right -= revision;
		}
		size			= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_BOTTOM ];
		if( size.cy )
		{
			revision = size.cy - nBorderMargin_Y;
			lpncsp->rgrc[0].bottom -= revision;
		}
	}

	if( !IsIconic() )
	{
		CRect rc( 0, 0, 0, 0 );
		GetWindowRect(&rc);
		int									x( 0 ), y( 0 );
		if( IsZoomed() )
		{
			y								= MARGIN_MAXIMIZED + m_pWVMFSize.cy;
			m_hCMax							= m_hBmpWindowCaption[ IDX_CAPTION_RESTORE_OFF ];
		} else {
			y								= 2;
			m_hCMax							= m_hBmpWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ];
		}

		m_rectExit.left						= rc.Width() - MARGIN_BOX - m_sizeWindowCaption[ IDX_CAPTION_EXIT_OFF ].cx;
		m_rectExit.top						= y;
		m_rectExit.right					= m_rectExit.left + m_sizeWindowCaption[ IDX_CAPTION_EXIT_OFF ].cx;
		m_rectExit.bottom					= m_rectExit.top + m_sizeWindowCaption[ IDX_CAPTION_EXIT_OFF ].cy;

		m_rectMax.left						= m_rectExit.left - m_sizeWindowCaption[ IDX_CAPTION_EXIT_OFF ].cx;
		m_rectMax.top						= y;
		m_rectMax.right						= m_rectMax.left + m_sizeWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ].cx;
		m_rectMax.bottom					= m_rectMax.top + m_sizeWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ].cy;

		m_rectMin.left						= m_rectMax.left - m_sizeWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ].cx;
		m_rectMin.top						= y;
		m_rectMin.right						= m_rectMin.left + m_sizeWindowCaption[ IDX_CAPTION_MINIMIZE_OFF ].cx;
		m_rectMin.bottom					= m_rectMin.top + m_sizeWindowCaption[ IDX_CAPTION_MINIMIZE_OFF ].cy;
	}

	CFrameWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}

// 최대화, 최소화의 크기를 지정.
void CPNOCtrl_SkinFrame_SDI::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}


void CPNOCtrl_SkinFrame_SDI::OnEnterSizeMove()
{
	if( !m_bDraging )
	{
		m_bDraging = TRUE;
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) ^ WS_EX_LAYERED);
		theskin->SetLayeredWindowAttributes(m_hWnd, 0, 176, LWA_ALPHA);
		::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}

	m_bTracking = FALSE;
	//	CFrameWnd::OnEnterSizeMove();
}


void CPNOCtrl_SkinFrame_SDI::OnExitSizeMove()
{
	if( m_bDraging )
	{
		m_bDraging = FALSE;
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
		::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}
	m_bTracking = FALSE;
	//	CFrameWnd::OnExitSizeMove();
}


void CPNOCtrl_SkinFrame_SDI::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CFrameWnd::OnNcLButtonDblClk(nHitTest, point);
}


void CPNOCtrl_SkinFrame_SDI::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	BOOL			bReDraw( FALSE );
	CPoint			localPt( point );
	ScreenToClient( &localPt );

	if( IsZoomed() )	localPt.x		+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx - ( m_pWVMFSize.cx ) );
	else				localPt.x		+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx - ( m_pWVMFSize.cx ) - 4 );
	localPt.y		+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ].cy - ( m_pWVMFSize.cy ) + 2 );

	if( m_rectMin.PtInRect( localPt ) )
	{
		m_hCMin												= m_hBmpWindowCaption[ IDX_CAPTION_MINIMIZE_DOWN ];
		m_unNcMouseClick									= CLICKED_BOX_MINIMIZE;
		bReDraw												= TRUE;
	} else if( m_rectMax.PtInRect( localPt ) )
	{
		if( IsZoomed() )
		{
			m_hCMax											= m_hBmpWindowCaption[ IDX_CAPTION_RESTORE_DOWN ];
			m_unNcMouseClick								= CLICKED_BOX_RESTORE;
		} else {
			m_hCMax											= m_hBmpWindowCaption[ IDX_CAPTION_MAXIMIZE_DOWN ];
			m_unNcMouseClick								= CLICKED_BOX_MAXIMIZE;
		}
		bReDraw												= TRUE;
	} else if( m_rectExit.PtInRect( localPt ) )
	{
		m_hCExit											= m_hBmpWindowCaption[ IDX_CAPTION_EXIT_DOWN ];
		m_unNcMouseClick									= CLICKED_BOX_EXIT;
		bReDraw												= TRUE;
	}

	if( bReDraw )
	{
		SetCapture();
		DrawFrame();
		return ;
	}

	CFrameWnd::OnNcLButtonDown(nHitTest, point);
}


void CPNOCtrl_SkinFrame_SDI::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	if( m_unNcMouseClick != CLICKED_BOX_NONE )
		ReleaseCapture();

	CPoint			localPt( point );
	ScreenToClient( &localPt );

	if( IsZoomed() )	localPt.x							+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx - ( m_pWVMFSize.cx ) );
	else				localPt.x							+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx - ( m_pWVMFSize.cx ) - 4 );
	localPt.y												+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ].cy - ( m_pWVMFSize.cy ) + 2 );

	SetCheckLBtnUp( point );

	CFrameWnd::OnNcLButtonUp(nHitTest, point);
}


void CPNOCtrl_SkinFrame_SDI::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	if( !m_bTracking )
	{	// 마우스가 윈도우를 벗어나면 WM_NCMOUSELEAVE 이벤트가 발생하도록 설정
		m_bTracking							= TRUE;
		TRACKMOUSEEVENT t					= { sizeof( TRACKMOUSEEVENT ), TME_NONCLIENT | TME_LEAVE, m_hWnd, 0 };
		::TrackMouseEvent(&t);					
	}
	if( m_unNcMouseClick == CLICKED_BOX_NONE )
	{
		CPoint			localPt( point );
		ScreenToClient( &localPt );

		if( IsZoomed() )	localPt.x		+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx - ( m_pWVMFSize.cx ) );
		else				localPt.x		+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx - ( m_pWVMFSize.cx ) - 4 );
		localPt.y		+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ].cy - ( m_pWVMFSize.cy ) + 2 );

		if( m_rectMin.PtInRect( localPt ) )
		{
			m_hCMin								= m_hBmpWindowCaption[ IDX_CAPTION_MINIMIZE_ON ];
		} else {
			m_hCMin								= m_hBmpWindowCaption[ IDX_CAPTION_MINIMIZE_OFF ];
		}

		if( m_rectMax.PtInRect( localPt ) )
		{
			if( IsZoomed() )	m_hCMax			= m_hBmpWindowCaption[ IDX_CAPTION_RESTORE_ON ];
			else				m_hCMax			= m_hBmpWindowCaption[ IDX_CAPTION_MAXIMIZE_ON ];
		} else {
			if( IsZoomed() )	m_hCMax			= m_hBmpWindowCaption[ IDX_CAPTION_RESTORE_OFF ];
			else				m_hCMax			= m_hBmpWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ];
		}

		if( m_rectExit.PtInRect( localPt ) )
		{
			m_hCExit							= m_hBmpWindowCaption[ IDX_CAPTION_EXIT_ON ];
		} else {
			m_hCExit							= m_hBmpWindowCaption[ IDX_CAPTION_EXIT_OFF ];
		}
		DrawFrame();
	}

	CFrameWnd::OnNcMouseMove(nHitTest, point);
}


void CPNOCtrl_SkinFrame_SDI::OnNcMouseLeave()
{
	m_hCExit							= m_hBmpWindowCaption[ IDX_CAPTION_EXIT_OFF ];
	if( IsIconic() )	m_hCMax			= m_hBmpWindowCaption[ IDX_CAPTION_RESTORE_OFF ];
	else				m_hCMax			= m_hBmpWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ];
	m_hCMin								= m_hBmpWindowCaption[ IDX_CAPTION_MINIMIZE_OFF ];

	CFrameWnd::OnNcMouseLeave();
}


void CPNOCtrl_SkinFrame_SDI::OnLButtonUp(UINT nFlags, CPoint point)
{
	if( m_unNcMouseClick != CLICKED_BOX_NONE )
		ReleaseCapture();

	CPoint			localPt( point );

	if( IsZoomed() )	localPt.x							+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx - ( m_pWVMFSize.cx ) );
	else				localPt.x							+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx - ( m_pWVMFSize.cx ) - 4 );
	localPt.y												+= ( m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ].cy - ( m_pWVMFSize.cy ) + 2 );

	SetCheckLBtnUp( localPt );

	CFrameWnd::OnLButtonUp(nFlags, point);
}


void CPNOCtrl_SkinFrame_SDI::SetskinIMGsize()
{
	// 윈도우 스타일 저장
	m_dwOrgStyle = GetStyle();

	ModifyStyle( WS_SYSMENU, 0);	
	ModifyStyle(0, WS_THICKFRAME|WS_DLGFRAME);			// 기본적으로 리사이징 가능하도록 윈도우 스타일 수정

	// TODO:  Add your specialized creation code here
	m_cfText			= theskin->GetRGB(IDX_RGB_FONT_CAPTION);
	m_cfMask			= theskin->GetRGB(IDX_RGB_MASK);

	// 각 비트맵의 사이즈 정보를 얻어온다.
	for( int i = IDX_SYSTEMICON_CAPTION_LEFT ; i <= IDX_CAPTION_RESTORE_DISABLE ; i++ )
	{
		m_sizeWindowCaption[ i ].cx			= theskin->GetBitmapSize( i ).cx;
		m_sizeWindowCaption[ i ].cy			= theskin->GetBitmapSize( i ).cy;
		m_hBmpWindowCaption[ i ]			= theskin->GetBitmap( i );
	}

	//	m_hIcon				= theskin->GetIcon(IDX_ICON_MAIN,ICON32);
	m_hIcon				= NULL;
}

void CPNOCtrl_SkinFrame_SDI::DrawFrame()
{
	if( !(GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION) )
		return;

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

	// Left 캡션 비트맵을 메모리 DC로 전송
	x					= m_pWVMFSize.cx;
	y					= m_pWVMFSize.cy;
	cx					= m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx - m_pWVMFSize.cx;
	cy					= m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cy - m_pWVMFSize.cy;
	hgdiobj				= tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Center 캡션 비트맵을 메모리 DC로 전송
	x					+= cx;
	cx					= rc.Width() - m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx - m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_RIGHT ].cx;
	cy					= m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ].cy - m_pWVMFSize.cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ].cx - m_pWVMFSize.cx, m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ].cy - m_pWVMFSize.cy, SRCCOPY);

	// Right 캡션 비트맵을 메모리 DC로 전송
	x					+= cx;
	cx					= m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_RIGHT ].cx - m_pWVMFSize.cx;
	cy					= m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_RIGHT ].cy - m_pWVMFSize.cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_SYSTEMICON_CAPTION_RIGHT ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Left 보더 비트맵을 메모리 DC로 전송
	x					= m_pWVMFSize.cx;
	y					= m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cy;
	cx					= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_LEFT ].cx - m_pWVMFSize.cx;
	cy					= rc.Height() - m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cy - m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_SYSTEMICON_FRAME_LEFT ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_LEFT ].cx - m_pWVMFSize.cx, m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_LEFT ].cy - m_pWVMFSize.cy, SRCCOPY);

	// Left-Bottom 보더 비트맵을 메모리 DC로 전송
	y					+= cy;
	cx					= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_LEFT_BOTTOM ].cx - m_pWVMFSize.cx;
	cy					= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_LEFT_BOTTOM ].cy - m_pWVMFSize.cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_SYSTEMICON_FRAME_LEFT_BOTTOM ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Bottom 보더 비트맵을 메모리 DC로 전송
	x					+= cx;
	cx					= rc.Width() - m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_LEFT ].cx - m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT ].cx;
	cy					= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_BOTTOM ].cy - m_pWVMFSize.cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_SYSTEMICON_FRAME_BOTTOM ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_BOTTOM ].cx - m_pWVMFSize.cx, m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_BOTTOM ].cy - m_pWVMFSize.cy, SRCCOPY);	

	// Right 보더 비트맵을 메모리 DC로 전송
	x					= rc.Width() - m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT ].cx;
	y					= m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_RIGHT ].cy;
	cx					= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT ].cx - m_pWVMFSize.cy;
	cy					= rc.Height() - m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_RIGHT ].cy - m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT ] );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT ].cx - m_pWVMFSize.cx, m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT ].cy - m_pWVMFSize.cy, SRCCOPY);

	// Right-Bottom 보더 비트맵을 메모리 DC로 전송
	x					= rc.Width()-m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cx;
	y					+= cy;
	cx					= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cx - m_pWVMFSize.cx;
	cy					= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT_BOTTOM ].cy - m_pWVMFSize.cy;
	tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT_BOTTOM ] );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);	

	// 텍스트 배경모드를 설정(투명)
	//	BufferDC.SetBkMode(TRANSPARENT);

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

		if( m_rectExit )
		{
			tmpDC.SelectObject( m_hCExit );
			BufferDC.BitBlt(m_rectExit.left, m_rectExit.top, m_rectExit.Width(), m_rectExit.Height(), &tmpDC, 0, 0, SRCCOPY);
		}

		CString str;
		GetWindowText( str );

		// Get bitmap size
		BITMAP csBitmapSize;
		int nRetValue			= ::GetObject( m_hBmpWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ], sizeof(csBitmapSize), &csBitmapSize );

		SIZE stSize;
		GetTextExtentPoint32(BufferDC.GetSafeHdc(), str, str.GetLength(), &stSize);

		//DWORD dwGapSize = (5 * 2 /*시스템 아이콘 좌우 여백*/);		// + 18/* 시스템 아이콘 폭*/;
		DWORD dwGapSize			= m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_LEFT ].cx;
		DWORD dwButtonSize		= rc.Width() - x;
		DWORD dwTitleSpace		= rc.Width() - dwGapSize - dwButtonSize - MARGIN_BOX;


		Gdiplus::Graphics			theGraphics( BufferDC );
		Gdiplus::Font				drawFont( _T("맑은 고딕"), 17, FontStyleBold, UnitPixel );
		Gdiplus::SolidBrush			drawFontBrush( Gdiplus::Color( 255, 1, 64, 153 ) );
		Gdiplus::Pen				drawFontPen( Color::Black );
		Gdiplus::StringFormat		drawFontFormat;
		drawFontFormat.SetAlignment( StringAlignmentNear );
		drawFontFormat.SetLineAlignment( StringAlignmentFar );
		if (dwTitleSpace > (DWORD)stSize.cx)
		{
			Gdiplus::PointF			drawFontPostion( (REAL)dwGapSize + 30, (REAL)( ((DWORD)( csBitmapSize.bmHeight + m_pWVMFSize.cy ) - BufferDC.GetTextExtent(str).cy) / 2 -2 ));
			theGraphics.DrawString( str, -1, &drawFont, drawFontPostion, &drawFontBrush );
			//			BufferDC.TextOut(dwGapSize, ((DWORD)csBitmapSize.bmHeight - BufferDC.GetTextExtent(str).cy) / 2, str);
		}
		else
		{
			TEXTMETRIC    stFontMetrics;
			BufferDC.GetOutputTextMetrics(&stFontMetrics);

			CStringA strNew, szConvData( CW2A( str.GetBuffer() ).m_psz );
			for (int i = szConvData.GetLength(); i > 0; i--)
			{
				if( IsDBCSLeadByteEx( 949, (BYTE)( szConvData.GetAt( i ) ) ) )		i--;		// 한글이면 한자 더 빼준다.
				strNew				= szConvData.Mid(0, i) + "...";

				if( (DWORD)BufferDC.GetTextExtent( CA2W( strNew.GetBuffer() ).m_psz ).cx < dwTitleSpace )
				{
					break;
				}
			}

			Gdiplus::PointF			drawFontPostion( (REAL)dwGapSize, (REAL)( ((DWORD)csBitmapSize.bmHeight - BufferDC.GetTextExtent(str).cy) / 2 ) + 3 );
			theGraphics.DrawString( ( CA2W( strNew.GetBuffer() ).m_psz ), -1, &drawFont, drawFontPostion, &drawFontBrush );
		}
		theGraphics.ReleaseHDC( BufferDC );

		// 클라이언트 영역을 제거한다.
		x							= m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_LEFT ].cx;
		y							= m_sizeWindowCaption[ IDX_SYSTEMICON_CAPTION_CENTER ].cy;
		x2							= rc.Width() - m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_RIGHT ].cx;
		y2							= rc.Height() - m_sizeWindowCaption[ IDX_SYSTEMICON_FRAME_BOTTOM ].cy;	
		dc.ExcludeClipRect(x, y, x2, y2);
	} else {
		tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CAPTION_EXIT_OFF ] );
		x							= rc.Width() - MARGIN_BOX - m_sizeWindowCaption[ IDX_CAPTION_EXIT_OFF ].cx;
		BufferDC.BitBlt(x, 0, m_sizeWindowCaption[ IDX_CAPTION_EXIT_OFF ].cx, m_sizeWindowCaption[ IDX_CAPTION_EXIT_OFF ].cy, &tmpDC, 0, 0, SRCCOPY);

		tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ] );
		x							= x - m_sizeWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ].cx;			
		BufferDC.BitBlt(x, 0, m_sizeWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ].cx, m_sizeWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ].cy, &tmpDC, 0, 0, SRCCOPY);

		tmpDC.SelectObject( m_hBmpWindowCaption[ IDX_CAPTION_MINIMIZE_OFF ] );
		x							= x - m_sizeWindowCaption[ IDX_CAPTION_MINIMIZE_OFF ].cx;		
		BufferDC.BitBlt(x, 0, m_sizeWindowCaption[ IDX_CAPTION_MINIMIZE_OFF ].cx, m_sizeWindowCaption[ IDX_CAPTION_MINIMIZE_OFF ].cy, &tmpDC, 0, 0, SRCCOPY);

		CString str;
		GetWindowText(str);

		if( str.GetLength() > 4 )
			str						= str.Left(4) + _T("...");

		//		BufferDC.TextOut(30, (rc.Height() - dc.GetTextExtent(str).cy) / 2, str);
	}
	// 메모리 DC 복원 삭제
	tmpDC.SelectObject(hgdiobj);
	tmpDC.DeleteDC();

	// 메모리 DC에 그려진 비트맵을 화면으로 전송	
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &BufferDC, 0, 0, SRCCOPY);

	// 메모리 DC 복원 및 삭제
	BufferDC.SelectObject(pOldBitmap1);
	BufferDC.DeleteDC();
}

void CPNOCtrl_SkinFrame_SDI::GetMonitorInforRect(CRect *pMonitorRect, UINT flags)
{
	HMONITOR				hMonitor				= NULL;
	MONITORINFO				tMonitorInfor			= { 0, };
	RECT					rtRECT					= { 0, };
	CSize					_rectsize( pMonitorRect->Width(), pMonitorRect->Height() );

	hMonitor										= MonitorFromRect(pMonitorRect, MONITOR_DEFAULTTONEAREST);
	tMonitorInfor.cbSize							= sizeof( tMonitorInfor );
	GetMonitorInfo(hMonitor, &tMonitorInfor );

	if (flags & MONITOR_WORKAREA)	rtRECT			= tMonitorInfor.rcWork;
	else							rtRECT			= tMonitorInfor.rcMonitor;

	if (flags & MONITOR_CENTER)
	{
		pMonitorRect->left							= rtRECT.left + ( rtRECT.right  - rtRECT.left - _rectsize.cx ) / 2;
		pMonitorRect->top							= rtRECT.top  + ( rtRECT.bottom - rtRECT.top  - _rectsize.cy ) / 2;
		pMonitorRect->right							= pMonitorRect->left + _rectsize.cx;
		pMonitorRect->bottom						= pMonitorRect->top  + _rectsize.cy;
	} else if( flags & MONITOR_PART_MAX ) {
		pMonitorRect->left							= rtRECT.left;
		pMonitorRect->top							= rtRECT.top;
		pMonitorRect->right							= rtRECT.right;
		pMonitorRect->bottom						= rtRECT.bottom;
	} else {
		pMonitorRect->left							= max(rtRECT.left, min( rtRECT.right - _rectsize.cx,  pMonitorRect->left ) );
		pMonitorRect->top							= max(rtRECT.top,  min( rtRECT.bottom - _rectsize.cy, pMonitorRect->top ) );
		pMonitorRect->right							= pMonitorRect->left + _rectsize.cx;
		pMonitorRect->bottom						= pMonitorRect->top  + _rectsize.cy;
	}
}

void CPNOCtrl_SkinFrame_SDI::SetCheckLBtnUp( CPoint point )
{
	m_hCExit										= m_hBmpWindowCaption[ IDX_CAPTION_EXIT_OFF ];
	if( IsZoomed() )	m_hCMax						= m_hBmpWindowCaption[ IDX_CAPTION_RESTORE_OFF ];
	else				m_hCMax						= m_hBmpWindowCaption[ IDX_CAPTION_MAXIMIZE_OFF ];
	m_hCMin											= m_hBmpWindowCaption[ IDX_CAPTION_MINIMIZE_OFF ];

	if( m_rectMin.PtInRect( point ) && m_unNcMouseClick == CLICKED_BOX_MINIMIZE )
	{		
		m_hCMin										= m_hBmpWindowCaption[ IDX_CAPTION_MINIMIZE_ON ];
		ShowWindow( SW_MINIMIZE );
	} else if( m_rectMax.PtInRect( point ) && ( m_unNcMouseClick == CLICKED_BOX_RESTORE || m_unNcMouseClick == CLICKED_BOX_MAXIMIZE ) )
	{
		if( m_unNcMouseClick == CLICKED_BOX_RESTORE )
		{
			m_hCMax									= m_hBmpWindowCaption[ IDX_CAPTION_MAXIMIZE_ON ];
			ShowWindow( SW_RESTORE );
		} else {
			m_hCMax									= m_hBmpWindowCaption[ IDX_CAPTION_RESTORE_ON ];
			ShowWindow( SW_MAXIMIZE );
		}

	} else if( m_rectExit.PtInRect( point )  && m_unNcMouseClick == CLICKED_BOX_EXIT )
	{
		m_hCExit									= m_hBmpWindowCaption[ IDX_CAPTION_EXIT_ON ];
		PostMessage(WM_CLOSE, 0, 0);
	}
	m_unNcMouseClick								= CLICKED_BOX_NONE;
	DrawFrame();
}