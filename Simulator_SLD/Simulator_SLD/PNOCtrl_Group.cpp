// PNOCtrl_Group.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "PNOCtrl_Group.h"

// CPNOCtrl_Group

IMPLEMENT_DYNAMIC(CPNOCtrl_Group, CWnd)

CPNOCtrl_Group::CPNOCtrl_Group() : m_nTabCnt( 0 )
{
	for( UINT i = 0; i < 3; i++ )
	{
		m_hBtmCaptionSkin[i] = NULL;
		::ZeroMemory(&m_BtmCaptionSkinInfor[i], sizeof(BITMAP));
	}

	for( UINT i = 0; i < 3; i++ )
	{
		m_hBtmOptSkin[i] = NULL;
	}
	::ZeroMemory(&m_hBtmOptSkinInfor, sizeof(BITMAP));

	m_hBtmSelectedTab = NULL;
	::ZeroMemory(&m_hBtmSelectedTabInfor, sizeof(BITMAP));

	m_hBtmUnSelectedTab = NULL;
	::ZeroMemory(&m_hBtmUnSelectedTabInfor, sizeof(BITMAP));

	for( int i = 0; i < 2; i++ )
	{
		m_hBtmOpt[i]																= NULL;
		m_rectOpt[i]																= CRect(0,0,0,0);
	}

	m_bTrackMouse																	= FALSE;
	m_nSetOption																	= GROUP_OPTION_NON;
}

CPNOCtrl_Group::~CPNOCtrl_Group()
{
	if( m_vecTabInfor.size() > 0 )
	{
		vector<CGroupTab_Infor*>::iterator											_iter;
		for( _iter = m_vecTabInfor.begin() ; _iter != m_vecTabInfor.end() ; ++_iter )
		{
			delete (*_iter);
		}
		m_vecTabInfor.clear();
	}

	for( UINT i = 0; i < 3; i++ )
	{
		if( m_hBtmCaptionSkin[i] )
		{
			::DeleteObject(m_hBtmCaptionSkin[i]);
			m_hBtmCaptionSkin[i] = NULL;
		}
		::ZeroMemory(&m_BtmCaptionSkinInfor[i], sizeof(BITMAP));
	}

	for( UINT i = 0; i < 6; i++ )
	{
		if( m_hBtmOptSkin[i] )
		{
			::DeleteObject(m_hBtmOptSkin[i]);
			m_hBtmOptSkin[i] = NULL;
		}
	}
	::ZeroMemory(&m_hBtmOptSkinInfor, sizeof(BITMAP));

	if( m_hBtmSelectedTab )
	{
		::DeleteObject(m_hBtmSelectedTab);
		m_hBtmSelectedTab = NULL;
	}
	::ZeroMemory(&m_hBtmSelectedTabInfor, sizeof(BITMAP));

	if( m_hBtmUnSelectedTab )
	{
		::DeleteObject(m_hBtmUnSelectedTab);
		m_hBtmUnSelectedTab = NULL;
	}
	::ZeroMemory(&m_hBtmUnSelectedTabInfor, sizeof(BITMAP));

	m_nSetOption																	= GROUP_OPTION_NON;
}


BEGIN_MESSAGE_MAP(CPNOCtrl_Group, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()

// CPNOCtrl_Group 메시지 처리기입니다.


BOOL CPNOCtrl_Group::Create( const RECT& rect, CWnd* pParentWnd )
{
	m_pParentWnd																	= pParentWnd;
	CWnd* pWnd																		= this;

	return pWnd->Create( NULL, NULL, WS_CHILD | WS_VISIBLE, rect, pParentWnd, 0 );
}

void CPNOCtrl_Group::OnPaint()
{
	CPaintDC																		dc(this);
	CRect																			rect;
	GetClientRect( rect );

	CBrush																			brush( WND_BG_GROUP_COLOR );
	CBrush*																			pOldBrush;
	pOldBrush																		= dc.SelectObject( &brush );

	dc.FillRect( rect, &brush );
	dc.SelectObject( pOldBrush );

	DrawSkin( &dc );
}

BOOL CPNOCtrl_Group::OnEraseBkgnd(CDC* pDC)
{
// 	CRect rect;
// 	GetClientRect( rect );
// 
// 	CBrush brush( WND_BG_GROUP_COLOR );
// 	CBrush* pOldBrush = pDC->SelectObject( &brush );
// 
// 	pDC->PatBlt( rect.left, rect.top, rect.right, rect.bottom, PATCOPY );
// 	pDC->SelectObject( pOldBrush );

	return TRUE;
}

void CPNOCtrl_Group::SetSkinInit1()
{
	int				i(0);
	CString			sModulePath(_T(""));
	for (i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0: { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Style1\\Left.pnoimg"); };				break;
		case 1: { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Style1\\Center.pnoimg"); };				break;
		case 2: { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Style1\\Right.pnoimg"); };				break;
		}

		if (_waccess(sModulePath, FILEACCESS_READ_ONLY) == -1)					return;
		m_hBtmCaptionSkin[i] = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
		::GetObject(m_hBtmCaptionSkin[i], sizeof(BITMAP), &(m_BtmCaptionSkinInfor[i]));
	}

	sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Style1\\caption.pnoimg");
	if (_waccess(sModulePath, FILEACCESS_READ_ONLY) == -1)						return;
	m_hBtmSelectedTab = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	::GetObject(m_hBtmSelectedTab, sizeof(BITMAP), &(m_hBtmSelectedTabInfor));

	m_hBtmUnSelectedTab = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	::GetObject(m_hBtmUnSelectedTab, sizeof(BITMAP), &(m_hBtmUnSelectedTabInfor));
}

void CPNOCtrl_Group::SetSkinInit2()
{
	int				i( 0 );
	CString			sModulePath( _T("") );
	for( i = 0 ; i < 3 ; i++ )
	{
		switch( i )
		{
		case 0: { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Style2\\Left.pnoimg"); };				break;
		case 1: { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Style2\\Center.pnoimg"); };				break;
		case 2: { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Style2\\Right.pnoimg"); };				break;
		}
		
		if( _waccess( sModulePath, FILEACCESS_READ_ONLY ) == -1 )					return ;
		m_hBtmCaptionSkin[i]														= (HBITMAP)::LoadImage( ::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE );
		::GetObject( m_hBtmCaptionSkin[i], sizeof(BITMAP), &( m_BtmCaptionSkinInfor[i] ) );
	}

	sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Style2\\Seleced_Tab.pnoimg");
	if( _waccess( sModulePath, FILEACCESS_READ_ONLY ) == -1 )						return ;
	m_hBtmSelectedTab																= (HBITMAP)::LoadImage( ::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE );
	::GetObject( m_hBtmSelectedTab, sizeof(BITMAP), &( m_hBtmSelectedTabInfor ) );

	sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Style2\\Unseleced_Tab.pnoimg");
	if( _waccess( sModulePath, FILEACCESS_READ_ONLY ) == -1 )						return ;
	m_hBtmUnSelectedTab															= (HBITMAP)::LoadImage( ::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE );
	::GetObject( m_hBtmUnSelectedTab, sizeof(BITMAP), &( m_hBtmUnSelectedTabInfor ) );
}

void CPNOCtrl_Group::SetSkinOption()
{
	int																				i( 0 );
	CString																			sModulePath( _T("") );
	for( i = 0 ; i < 6 ; i++ )
	{
		switch( i )
		{
		case 0 : { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Option\\1_down.pnoimg"); };		break;
		case 1 : { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Option\\1_on.pnoimg"); };			break;
		case 2 : { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Option\\1_over.pnoimg"); };		break;
		case 3 : { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Option\\2_down.pnoimg"); };		break;
		case 4 : { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Option\\2_on.pnoimg"); };			break;
		case 5 : { sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Group\\Option\\2_over.pnoimg"); };		break;
		}

		if( _waccess( sModulePath, FILEACCESS_READ_ONLY ) == -1 )					return ;
		m_hBtmOptSkin[i]															= (HBITMAP)::LoadImage( ::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE );
	}
	::GetObject( m_hBtmOptSkin[0], sizeof(BITMAP), &( m_hBtmOptSkinInfor ) );
	
	SetOptionMode( GROUP_OPTION_MODE1 );

	m_rectOpt[0].left																= WND_WIDTH_FRAME_SIZE - ((m_hBtmOptSkinInfor.bmWidth+5) * 2);
	m_rectOpt[0].top																= (m_BtmCaptionSkinInfor[ 0 ].bmHeight - m_hBtmOptSkinInfor.bmHeight) / 2;
	m_rectOpt[0].right																= m_rectOpt[0].left + m_hBtmOptSkinInfor.bmWidth;
	m_rectOpt[0].bottom																= m_rectOpt[0].top + m_hBtmOptSkinInfor.bmHeight;

	m_rectOpt[1].left																= m_rectOpt[0].right + 5;
	m_rectOpt[1].top																= m_rectOpt[0].top;
	m_rectOpt[1].right																= m_rectOpt[1].left + m_hBtmOptSkinInfor.bmWidth;;
	m_rectOpt[1].bottom																= m_rectOpt[1].top + m_hBtmOptSkinInfor.bmHeight;;
}

void CPNOCtrl_Group::AddTabInfor( wstring szName, CWnd*	pView )
{
	CGroupTab_Infor*																pTabInfor;
	pTabInfor																		= new CGroupTab_Infor;

	if( m_vecTabInfor.size() == 0 )
	{
		pTabInfor->m_bSelected														= TRUE;
		pTabInfor->m_TapSize.left													= ( m_nTabCnt * m_hBtmSelectedTabInfor.bmWidth ) + 5 + ( m_nTabCnt * 3 );
		pTabInfor->m_TapSize.top													= m_BtmCaptionSkinInfor[ 0 ].bmHeight - m_hBtmSelectedTabInfor.bmHeight;
		pTabInfor->m_TapSize.right													= pTabInfor->m_TapSize.left + m_hBtmSelectedTabInfor.bmWidth;
		pTabInfor->m_TapSize.bottom													= pTabInfor->m_TapSize.top + m_hBtmSelectedTabInfor.bmHeight;
	} else {
		pTabInfor->m_bSelected														= FALSE;
		pTabInfor->m_TapSize.left													= ( m_nTabCnt * m_hBtmUnSelectedTabInfor.bmWidth ) + 5 + ( m_nTabCnt * 3 );
		pTabInfor->m_TapSize.top													= m_BtmCaptionSkinInfor[ 0 ].bmHeight - m_hBtmUnSelectedTabInfor.bmHeight;
		pTabInfor->m_TapSize.right													= pTabInfor->m_TapSize.left + m_hBtmUnSelectedTabInfor.bmWidth;
		pTabInfor->m_TapSize.bottom													= pTabInfor->m_TapSize.top + m_hBtmUnSelectedTabInfor.bmHeight;
	}
	
	pTabInfor->m_bMoveSelect														= FALSE;
	pTabInfor->m_szTabName															= szName;
	pTabInfor->m_pView																= pView;
	m_vecTabInfor.push_back( pTabInfor );

	++m_nTabCnt;
}

void CPNOCtrl_Group::DrawSkin( CDC* pDC, int nDrawIdx )
{
	CRect																			_rect( 0, 0, 0, 0 );
	GetClientRect( &_rect );

	CDC																				BufferDC, tmpDC;
	BufferDC.CreateCompatibleDC( pDC );
	tmpDC.CreateCompatibleDC( pDC );

	CBitmap																			bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap( pDC, _rect.Width(), _rect.Height() );
	CBitmap*																		pOldbmpBuffer;
	pOldbmpBuffer																	= (CBitmap *)BufferDC.SelectObject( &bmpBuffer );

	HGDIOBJ																			hGDIobj;
	int																				nPosX( 0 ), nPosY( 0 ), nCsX( 0 ), nCsY( 0 ), i( 0 );

	nPosX																			= 0;
	nPosY																			= 0;
	nCsX																			= m_BtmCaptionSkinInfor[ 0 ].bmWidth;
	nCsY																			= m_BtmCaptionSkinInfor[ 0 ].bmHeight;
	hGDIobj																			= tmpDC.SelectObject( m_hBtmCaptionSkin[ 0 ] );
	BufferDC.BitBlt( nPosX, nPosY, nCsX, nCsY, &tmpDC, 0, 0, SRCCOPY );

	nPosX																			+= nCsX;
	nPosY																			= nPosY;
	nCsX																			= _rect.Width() - ( m_BtmCaptionSkinInfor[ 0 ].bmWidth + m_BtmCaptionSkinInfor[ 2 ].bmWidth );
	nCsY																			= m_BtmCaptionSkinInfor[ 1 ].bmHeight;
	hGDIobj																			= tmpDC.SelectObject( m_hBtmCaptionSkin[ 1 ] );
	BufferDC.StretchBlt( nPosX, nPosY, nCsX, nCsY, &tmpDC, 0, 0, m_BtmCaptionSkinInfor[ 1 ].bmWidth, m_BtmCaptionSkinInfor[ 1 ].bmHeight, SRCCOPY );

	nPosX																			+= nCsX;
	nPosY																			= nPosY;
	nCsX																			= m_BtmCaptionSkinInfor[ 2 ].bmWidth;
	nCsY																			= m_BtmCaptionSkinInfor[ 2 ].bmHeight;
	hGDIobj																			= tmpDC.SelectObject( m_hBtmCaptionSkin[ 2 ] );
	BufferDC.BitBlt( nPosX, nPosY, nCsX, nCsY, &tmpDC, 0, 0, SRCCOPY );

	BufferDC.FillSolidRect( _rect.left, _rect.top + m_BtmCaptionSkinInfor[ 1 ].bmHeight, _rect.Width(), _rect.Height() - m_BtmCaptionSkinInfor[ 1 ].bmHeight, RGB( 255, 255, 255 ) );

	CRect																			rect;
	if( m_vecTabInfor.size() > 0 )
	{
		vector<CGroupTab_Infor*>::iterator											_iter;
		for( _iter = m_vecTabInfor.begin() ; _iter != m_vecTabInfor.end() ; ++_iter )
		{
			if( (*_iter)->m_bSelected )
			{
				BufferDC.SetTextColor( GROUP_FONT_COLOR_SEL );
				hGDIobj																= tmpDC.SelectObject( m_hBtmSelectedTab );
			} else {
				BufferDC.SetTextColor( GROUP_FONT_COLOR_NOR );
				hGDIobj																= tmpDC.SelectObject( m_hBtmUnSelectedTab );
			}
			BufferDC.BitBlt( (*_iter)->m_TapSize.left, (*_iter)->m_TapSize.top, (*_iter)->m_TapSize.Width(), (*_iter)->m_TapSize.Height(), &tmpDC, 0, 0, SRCCOPY );

			if( (*_iter)->m_bMoveSelect )
			{
				BufferDC.SetTextColor( GROUP_FONT_COLOR_OVER );
			}

			BufferDC.SetBkMode( TRANSPARENT );

			CFont																	font, *pOldFont;
			font.CreateFont( 18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕") );
			pOldFont																= BufferDC.SelectObject( &font );

			rect.SetRect((*_iter)->m_TapSize.left, (*_iter)->m_TapSize.top, (*_iter)->m_TapSize.right, (*_iter)->m_TapSize.bottom );
			BufferDC.DrawText( (*_iter)->m_szTabName.c_str(), rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER );
			BufferDC.SelectObject( pOldFont );
			font.DeleteObject();
		}
	}

	if( m_nSetOption != GROUP_OPTION_NON )
	{
		for( int i = 0; i < GROUP_OPTION_COUNT; i++ )
		{
			tmpDC.SelectObject( m_hBtmOpt[i] );
			BufferDC.BitBlt( m_rectOpt[i].left, m_rectOpt[i].top, m_rectOpt[i].Width(), m_rectOpt[i].Height(), &tmpDC, 0, 0, SRCCOPY);
		}
	}

	if( nDrawIdx == 0 )																pDC->BitBlt( 0, 0, _rect.Width(), m_BtmCaptionSkinInfor[ 1 ].bmHeight, &BufferDC, 0, 0, SRCCOPY );
	else if( nDrawIdx == 1 )														pDC->BitBlt( 0, 0, _rect.Width(), _rect.Height(), &BufferDC, 0, 0, SRCCOPY );

	tmpDC.SelectObject( hGDIobj );
	tmpDC.DeleteDC();

	BufferDC.SelectObject( pOldbmpBuffer );
	BufferDC.DeleteDC();
}

//////////////////////////////////////////////////////////////////////////

CString CPNOCtrl_Group::GetModulePath()
{
	CString																			sPath;
	GetModuleFileName( AfxGetApp()->m_hInstance, sPath.GetBuffer(MAX_PATH), MAX_PATH );
	sPath.ReleaseBuffer();

	int																				nPos;
	nPos																			= sPath.ReverseFind(_T('\\'));
	
	if( nPos != -1 )																sPath = sPath.Left( nPos );

	return sPath;
}

void CPNOCtrl_Group::OnMouseMove(UINT nFlags, CPoint point)
{
	if( m_vecTabInfor.size() > 0 )
	{
		ResetMoveSelect();

		vector<CGroupTab_Infor*>::iterator											_iter;
		for( _iter = m_vecTabInfor.begin() ; _iter != m_vecTabInfor.end() ; ++_iter )
		{
			if( (*_iter)->m_TapSize.PtInRect( point ) && (*_iter)->m_bSelected == FALSE )
			{
				(*_iter)->m_bMoveSelect												= TRUE;
				break;					
			}
		}
	}

	if( m_nSetOption != GROUP_OPTION_NON )
	{
		for( int i = 0; i < GROUP_OPTION_COUNT; i++ )
		{
			if( m_nSetOption == i )													continue;

			if( m_rectOpt[i].PtInRect(point) )
				m_hBtmOpt[i]														= m_hBtmOptSkin[(3*i) + OPTION_STATUS_OVER];
			else
				m_hBtmOpt[i]														= m_hBtmOptSkin[(3*i) + OPTION_STATUS_ON];
		}
	}

	CClientDC																		dc( this );
	DrawSkin( &dc );

	//////////////////////////////////////////////////////////////////////////
	if( !m_bTrackMouse )
	{
		TRACKMOUSEEVENT																MouseEvent;
		::ZeroMemory(&MouseEvent, sizeof(MouseEvent));

		MouseEvent.cbSize															= sizeof(MouseEvent);
		MouseEvent.dwFlags															= TME_LEAVE | TME_HOVER;
		MouseEvent.hwndTrack														= m_hWnd;
		MouseEvent.dwHoverTime														= 0;

		m_bTrackMouse																= TrackMouseEvent(&MouseEvent);
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CPNOCtrl_Group::ResetSelect()
{
	if( m_vecTabInfor.size() > 0 )
	{
		vector<CGroupTab_Infor*>::iterator											_iter;
		for( _iter = m_vecTabInfor.begin() ; _iter != m_vecTabInfor.end() ; ++_iter )
		{
			(*_iter)->m_bSelected													= FALSE;
		}
	}
}

void CPNOCtrl_Group::ResetMoveSelect()
{
	if( m_vecTabInfor.size() > 0 )
	{
		vector<CGroupTab_Infor*>::iterator											_iter;
		for( _iter = m_vecTabInfor.begin() ; _iter != m_vecTabInfor.end() ; ++_iter )
		{
			(*_iter)->m_bMoveSelect													= FALSE;
		}
	}
}

void CPNOCtrl_Group::ResetView()
{
	if( m_vecTabInfor.size() > 0 )
	{
		vector<CGroupTab_Infor*>::iterator											_iter;
		for( _iter = m_vecTabInfor.begin() ; _iter != m_vecTabInfor.end() ; ++_iter )
		{
			if( (*_iter)->m_pView )
			{
				(*_iter)->m_pView->ShowWindow( SW_HIDE );
			}
		}
	}
}

void CPNOCtrl_Group::SetTabView( int nTabIndex, CWnd* pView )
{
	if( nTabIndex <= 0 || nTabIndex > (int)m_vecTabInfor.size() )					return;

	CGroupTab_Infor*																pTabInfor;
	pTabInfor																		= m_vecTabInfor[ nTabIndex - 1 ];

	if( pTabInfor && !(pTabInfor->m_pView) )
	{
		pTabInfor->m_pView															= pView;
	}
} 

CRect CPNOCtrl_Group::GetInDrawScreenRect()
{
	CRect																			_rect( 0, 0, 0, 0 );
	GetClientRect( &_rect );
	_rect.top																		+= m_BtmCaptionSkinInfor[ 0 ].bmHeight;

	return _rect;
}

void CPNOCtrl_Group::SetTabFocus( int nTabIndex )
{
	if( nTabIndex <= 0 || nTabIndex > (int)m_vecTabInfor.size() )					return;

	CGroupTab_Infor*																pTabInfor;
	pTabInfor																		= m_vecTabInfor[ nTabIndex - 1 ];

	if( pTabInfor && pTabInfor->m_pView )
	{
		ResetSelect();
		ResetMoveSelect();
		ResetView();

		pTabInfor->m_bSelected														= TRUE;
		pTabInfor->m_bMoveSelect													= FALSE;

		CClientDC																	dc( this );
		DrawSkin( &dc, 1 );

		if( pTabInfor->m_pView )
		{
			pTabInfor->m_pView->ShowWindow( SW_SHOW );
			pTabInfor->m_pView->UpdateData();
		}
	}
}

int CPNOCtrl_Group::GetActiveSelect()
{
	int																				nSelect( 0 );
	if( m_vecTabInfor.size() > 0 )
	{
		vector<CGroupTab_Infor*>::iterator											_iter;
		for( nSelect = 1, _iter = m_vecTabInfor.begin() ; _iter != m_vecTabInfor.end() ; ++_iter, ++nSelect )
		{
			if( (*_iter)->m_bSelected )
			{
				return nSelect;
			}
		}
	}

	return 0;
}

void CPNOCtrl_Group::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( m_vecTabInfor.size() > 0 )
	{
		vector<CGroupTab_Infor*>::iterator											_iter;
		for( _iter = m_vecTabInfor.begin() ; _iter != m_vecTabInfor.end() ; ++_iter )
		{
			if( (*_iter)->m_TapSize.PtInRect( point ) && (*_iter)->m_bSelected == FALSE )
			{
				ResetSelect();
				ResetMoveSelect();
				ResetView();

				(*_iter)->m_bSelected												= TRUE;
				(*_iter)->m_bMoveSelect												= FALSE;

				CClientDC															dc( this );
				DrawSkin( &dc, 1 );

				if( (*_iter)->m_pView )
				{
					(*_iter)->m_pView->ShowWindow( SW_SHOW );
					(*_iter)->m_pView->UpdateData();
				}

				break;
			}
		}
	}

	if( m_nSetOption != GROUP_OPTION_NON )
	{
		int																			nSelectOpt;
		nSelectOpt																	= GROUP_OPTION_NON;

		for( int i = 0; i < GROUP_OPTION_COUNT; i++ )
		{
			if( m_rectOpt[i].PtInRect(point) )
				nSelectOpt															= i;
		}

		if( nSelectOpt == GROUP_OPTION_NON )										return;

		BOOL																		bRet;
		bRet																		= SetOptionMode( nSelectOpt );
		if( bRet )																	
			m_pParentWnd->SendMessage( WM_SIDECTRL_MSG, (WPARAM)1, (LPARAM)m_nSetOption );
	}

	CWnd::OnLButtonDown(nFlags, point);
}

BOOL CPNOCtrl_Group::SetOptionMode( int nOpt )
{
	if( nOpt == GROUP_OPTION_NON )													return FALSE;
	if( m_nSetOption == nOpt )														return FALSE;

	m_nSetOption																	= nOpt;
	for( int i = 0; i < GROUP_OPTION_COUNT; i++ )
	{
		if( m_nSetOption == i )														m_hBtmOpt[i] = m_hBtmOptSkin[(3*i) + OPTION_STATUS_DOWN];
		else																		m_hBtmOpt[i] = m_hBtmOptSkin[(3*i) + OPTION_STATUS_ON];
	}

	CClientDC																		dc( this );
	DrawSkin( &dc );

	return TRUE;
}

BOOL CPNOCtrl_Group::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
 	CWnd::OnNotify(wParam, lParam, pResult);
	LPNMTREEVIEW																	ntv;       
	ntv																				= (LPNMTREEVIEW)lParam;	

	m_pParentWnd->SendMessage(WM_NOTIFY, wParam, lParam);
	return TRUE;
}


void CPNOCtrl_Group::OnMouseLeave()
{
	m_bTrackMouse																	= FALSE;
	ResetMoveSelect();
	
	if( m_nSetOption != GROUP_OPTION_NON )
	{
		for( int i = 0; i < GROUP_OPTION_COUNT; i++ )
		{
			if( m_nSetOption == i )													continue;
			m_hBtmOpt[i]															= m_hBtmOptSkin[(3*i) + OPTION_STATUS_ON];
		}
	}

	CClientDC																		dc( this );
	DrawSkin( &dc );

	CWnd::OnMouseLeave();
}

void CPNOCtrl_Group::OnMouseHover(UINT nFlags, CPoint point)
{
	m_bTrackMouse																	= FALSE;
	CWnd::OnMouseHover(nFlags, point);
}
