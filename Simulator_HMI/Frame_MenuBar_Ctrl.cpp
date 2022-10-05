// CFrame_MenuBar_Ctrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Frame_MenuBar_Ctrl.h"

CFrame_MenuBar_Ctrl*		g_pMenuCtrlBar	= NULL;
HHOOK						g_hMenuMsgHook = NULL;

// CFrame_MenuBar_Ctrl

IMPLEMENT_DYNAMIC(CFrame_MenuBar_Ctrl, CToolBarCtrl)

	CFrame_MenuBar_Ctrl::CFrame_MenuBar_Ctrl() :			m_colorBK( RGB( 70, 80, 100 ) )
													,		m_colorHot( RGB(193, 210, 238) )
													,		m_colorChecked( m_colorHot )
													,		m_colorSelected( m_colorChecked )
													,		m_colorLine( RGB(49, 106, 197) )
													,		m_nItemCount( 0 )
													,		m_nPressed( 0 )
													,		m_ptMouse( 0, 0 )
													,		m_DrawItemTrect( 999, 999, 0, 0 )
													,		m_nThisToolbarChildSysIdx( 0 )
{
	m_pThisMenu				= NULL;
}
CFrame_MenuBar_Ctrl::~CFrame_MenuBar_Ctrl()
{
	if( m_pThisMenu )
	{
		delete m_pThisMenu;
		m_pThisMenu = NULL;
	}
}


BEGIN_MESSAGE_MAP(CFrame_MenuBar_Ctrl, CToolBarCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CFrame_MenuBar_Ctrl::OnNMCustomdraw)
	ON_WM_LBUTTONDOWN()
	ON_WM_INITMENUPOPUP()
	ON_MESSAGE( MB_TRACKPOPUPMENU, OnPopupMenu )
	ON_WM_EXITMENULOOP()
	ON_WM_ENTERMENULOOP()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_REFLECT(NM_CLICK, &CFrame_MenuBar_Ctrl::OnNMClick)
// 	ON_COMMAND_RANGE(IDM_MENU_START, IDM_MENU_END, &CFrame_MenuBar_Ctrl::OnMenuClick)
// 	ON_UPDATE_COMMAND_UI_RANGE(ID_CADFILE_SAVE, ID_HELP_CONTENTS,  &CFrame_MenuBar_Ctrl::OnUpdateMenuClick)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CFrame_MenuBar_Ctrl 메시지 처리기입니다.

void CFrame_MenuBar_Ctrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	NMTBCUSTOMDRAW *pNMTbCustomData				= (NMTBCUSTOMDRAW *)pNMHDR;

	CDC					dc;
	dc.Attach( pNMTbCustomData->nmcd.hdc );

	switch( pNMTbCustomData->nmcd.dwDrawStage )
	{
		case CDDS_PREPAINT :		{
										*pResult = CDRF_NOTIFYITEMDRAW;
									}; break;
		case CDDS_ITEMPREPAINT:		{
										wchar_t			szRtData[ _MAX_PATH ];
										memset( szRtData, 0x00, sizeof( szRtData ) );
										GetString( (int)( pNMTbCustomData->nmcd.dwItemSpec ), szRtData, sizeof( szRtData ) );

// 										CString			szText;
// 										GetString( (int)( pNMTbCustomData->nmcd.dwItemSpec ), szText );
										ItemDraw( &dc, CRect( pNMTbCustomData->nmcd.rc ), pNMTbCustomData->nmcd.uItemState, szRtData );
										*pResult = CDRF_SKIPDEFAULT;
									}; break;
		case CDDS_ITEMPOSTPAINT:	{
										//
									}; break;
	}
	dc.Detach();

	//	*pResult = 0;
}

void CFrame_MenuBar_Ctrl::ItemDraw( CDC *pDC, CRect rectDraw, UINT uState, CString szName )
{
// 	COLORREF				_pencolor( RGB( 255, 255, 255 ) ), _brushcolor( RGB( 255, 255, 255 ) );
// 	if( uState & CDIS_HOT)
// 	{
// 		pDC->SetTextColor( RGB( 0, 0, 0 ) );
// 		_pencolor								= m_colorLine;
// 		_brushcolor								= m_colorHot;
// 	} else if (uState & CDIS_CHECKED)
// 	{
// 		pDC->SetTextColor( RGB( 0, 0, 0 ) );
// 		_pencolor								= m_colorLine;
// 		_brushcolor								= m_colorHot;
// 	} else if (uState & CDIS_SELECTED) 
// 	{
// 		pDC->SetTextColor( RGB( 0, 0, 0 ) );
// 		_pencolor								= m_colorLine;
// 		_brushcolor								= m_colorHot;
// 	} else {
// 		pDC->SetTextColor( RGB( 255, 255, 255 ) );
// 		_pencolor								= m_colorBK;
// 		_brushcolor								= m_colorBK;
// 	}
// 	pDC->SetBkMode( TRANSPARENT );

// 	COLORREF				_pencolor( RGB( 0, 0, 0 ) ), _brushcolor( RGB( 255, 255, 255 ) );
// 	COLORREF				clrSet11( RGB(  81, 152, 114 ) ), clrSet12( RGB(  21,  62,  39 ) ), clrSet13( RGB( 195, 225, 210 ) );
// 	COLORREF				clrSet21( RGB(  81, 152, 114 ) ), clrSet22( RGB(  21,  62,  39 ) ), clrSet23( RGB(  60, 114,  85 ) );
// 	COLORREF				clrSet31( RGB( 255, 255, 255 ) ), clrSet32( RGB(  21,  62,  39 ) ), clrSet33( RGB(  60, 114,  85 ) );
// 	COLORREF				clrSet41( RGB(  81, 152, 114 ) ), clrSet42( RGB(  21,  62,  39 ) ), clrSet43( RGB(  21,  62,  39 ) );
	COLORREF				_pencolor( RGB( 0, 0, 0 ) ), _brushcolor( RGB( 255, 255, 255 ) );
	COLORREF				clrSet11( RGB(  81, 152, 114 ) ), clrSet12( RGB(  21,  62,  39 ) ), clrSet13( RGB(  26,  75,  48 ) );
	COLORREF				clrSet21( RGB(  81, 152, 114 ) ), clrSet22( RGB(  21,  62,  39 ) ), clrSet23( RGB(  60, 114,  85 ) );
	COLORREF				clrSet31( RGB( 255, 255, 255 ) ), clrSet32( RGB(  21,  62,  39 ) ), clrSet33( RGB(  60, 114,  85 ) );
	COLORREF				clrSet41( RGB(  81, 152, 114 ) ), clrSet42( RGB(  21,  62,  39 ) ), clrSet43( RGB(  21,  62,  39 ) );


	if( uState & CDIS_HOT)
	{
		pDC->SetTextColor( clrSet11 );
		_pencolor								= clrSet12;
		_brushcolor								= clrSet13;
	} else if (uState & CDIS_CHECKED)
	{
		pDC->SetTextColor( clrSet21 );
		_pencolor								= clrSet22;
		_brushcolor								= clrSet23;
	} else if (uState & CDIS_SELECTED) 
	{
		pDC->SetTextColor( clrSet31 );
		_pencolor								= clrSet32;
		_brushcolor								= clrSet33;
	} else {
		pDC->SetTextColor( clrSet41 );
		_pencolor								= clrSet42;
		_brushcolor								= clrSet43;
	}
	pDC->SetBkMode( TRANSPARENT );


	CPen					pen(PS_SOLID, 1, _pencolor );
	CPen*					pOldPen				= pDC->SelectObject( &pen );
	CBrush					brush( _brushcolor );
	CBrush*					pOldBr				= pDC->SelectObject( &brush );
	pDC->Rectangle( rectDraw );
	pDC->SelectObject( pOldBr );
	pDC->SelectObject( pOldPen );


// 	Gdiplus::Graphics			theGraphics( pDC->GetSafeHdc() );
// 	Gdiplus::Font				drawFont( _T("맑은 고딕"), 12, FontStyleRegular, UnitPixel );
// 	Gdiplus::SolidBrush			drawFontBrush( Color::White );
// 	Gdiplus::Pen				drawFontPen( Color::White );
// 	Gdiplus::StringFormat		drawFontFormat;
// 	drawFontFormat.SetAlignment( StringAlignmentNear );
// 	drawFontFormat.SetLineAlignment( StringAlignmentFar );
// 	Gdiplus::PointF			drawFontPostion( (REAL)rectDraw.left, (REAL)rectDraw.top );
// 	theGraphics.DrawString( szName, -1, &drawFont, drawFontPostion, &drawFontBrush );
// 	theGraphics.ReleaseHDC( pDC->GetSafeHdc() );

	CFont					font;
	font.CreateFont( 16, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕") );
	CFont*					pOldFont			= pDC->SelectObject( &font );
	pDC->DrawText( szName, rectDraw, DT_SINGLELINE | DT_VCENTER | DT_CENTER );
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
}

void CFrame_MenuBar_Ctrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	int						nTestItemId( HitTest( &point ) );
	if ( nTestItemId < 0 || nTestItemId >= m_nItemCount )
	{
		return;
	}

	m_nPressed = nTestItemId;
	TrackPopupMenu();
}

void CFrame_MenuBar_Ctrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// OnOK 처리하지 않기 위함.
//	CToolBarCtrl::OnLButtonDblClk(nFlags, point);
}

void CFrame_MenuBar_Ctrl::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	CToolBarCtrl::OnRButtonDblClk(nFlags, point);
}

void CFrame_MenuBar_Ctrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	CToolBarCtrl::OnRButtonDown(nFlags, point);
}

void CFrame_MenuBar_Ctrl::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	CToolBarCtrl::OnRButtonUp(nFlags, point);
}

void CFrame_MenuBar_Ctrl::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	CToolBarCtrl::OnMButtonDblClk(nFlags, point);
}


LRESULT CFrame_MenuBar_Ctrl::OnPopupMenu(WPARAM wParam, LPARAM lParam)
{
	if ( m_nPressed < 0 )
	{
		m_nPressed								= m_nItemCount - 1;
	}
	if ( m_nPressed >= m_nItemCount )
	{
		m_nPressed								= 0;
	}
	TrackPopupMenu();

	return 0;
}

void CFrame_MenuBar_Ctrl::OnExitMenuLoop(BOOL bIsTrackPopupMenu)
{
	GetOwner()->SendMessage( WM_EXITMENULOOP, (WPARAM)bIsTrackPopupMenu );
}

void CFrame_MenuBar_Ctrl::OnEnterMenuLoop(BOOL bIsTrackPopupMenu)
{
	GetOwner()->SendMessage( WM_ENTERMENULOOP, (WPARAM)bIsTrackPopupMenu );
}

void CFrame_MenuBar_Ctrl::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CToolBarCtrl::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	GetOwner()->SendMessage( WM_INITMENUPOPUP, (WPARAM)pPopupMenu->GetSafeHmenu(), MAKELONG( nIndex, bSysMenu ) );
}

LRESULT CFrame_MenuBar_Ctrl::MenuInputFilter( int nCode, WPARAM wParam, LPARAM lParam )
{
	MSG*					pMsg				= (MSG*)lParam;

	if( !g_pMenuCtrlBar || nCode != MSGF_MENU )
	{
		return CallNextHookEx( g_hMenuMsgHook, nCode, wParam, lParam );
	}

	if( g_pMenuCtrlBar->OnMenuInput( pMsg ) )
	{
		return TRUE;
	} else {
		return CallNextHookEx( g_hMenuMsgHook, nCode, wParam, lParam );
	}
}

BOOL CFrame_MenuBar_Ctrl::LoadMenu( CMenu *pMenu )
{
	if( ! m_hWnd)								return FALSE;
	if( !pMenu )								return FALSE;
	if( m_pThisMenu )
	{
		delete m_pThisMenu;
		m_pThisMenu								= NULL;
	}

	m_pThisMenu									= pMenu;
	TBBUTTON				_TBbtn				= { 0 }; 
	ZeroMemory( &_TBbtn, sizeof( TBBUTTON ) );

	int						i( 0 ), nSzreturn( 0 );
	BOOL					bRet( FALSE );
	TCHAR					szText[ _MAX_PATH ] = { 0 };

	_TBbtn.fsState								= TBSTATE_ENABLED;
	_TBbtn.fsStyle								= TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE;

	m_nItemCount								= m_pThisMenu->GetMenuItemCount();
	SetBitmapSize( CSize( 0, 0 ) );

	for ( i = 0 ; i < m_nItemCount ; i++ )
	{
		ZeroMemory( szText, _MAX_PATH );

		MENUITEMINFO		_menuinfor			= { 0 };
		ZeroMemory( &_menuinfor, sizeof( MENUITEMINFO ) );
		_menuinfor.cbSize						= sizeof(MENUITEMINFO);
		_menuinfor.fMask						= MIIM_DATA | MIIM_TYPE;
		m_pThisMenu->GetMenuItemInfo( i, &_menuinfor, TRUE );
		m_pThisMenu->GetMenuString( i, szText, 80, MF_BYPOSITION );

		nSzreturn								= AddStrings(szText);
		_TBbtn.dwData							= NULL;
		_TBbtn.iString							= nSzreturn;
		_TBbtn.idCommand						= i;
		bRet									= AddButtons( 1, &_TBbtn );

		if(!bRet)								return FALSE;

		CRect			rectBtnItem;
		GetItemRect( i, rectBtnItem );
		m_DrawItemTrect = MaxMergeRect( m_DrawItemTrect, rectBtnItem );
	}

	return bRet;
}

CRect CFrame_MenuBar_Ctrl::MaxMergeRect( CRect firstRect, CRect secondRect )
{
	CRect				returnRect( 0, 0, 0, 0 );

	if( firstRect.left < secondRect.left )							returnRect.left		= 	firstRect.left;
	else															returnRect.left		= 	secondRect.left;

	if( firstRect.right > secondRect.right )						returnRect.right	= 	firstRect.right;
	else															returnRect.right	= 	secondRect.right;

	if( firstRect.top < secondRect.top )							returnRect.top		= 	firstRect.top;
	else															returnRect.top		= 	secondRect.top;

	if( firstRect.bottom > secondRect.bottom )						returnRect.bottom	= 	firstRect.bottom;
	else															returnRect.bottom	= 	secondRect.bottom;

	return returnRect;
}

void CFrame_MenuBar_Ctrl::TrackPopupMenu( void )
{
	CMenu*					pSubMenu			= m_pThisMenu->GetSubMenu( m_nPressed );
	if ( pSubMenu == NULL )						return ;

	PressButton( m_nPressed, TRUE );

	CRect					_rect( 0, 0, 0, 0 ), _screenrect( 0, 0, 0, 0 );
	GetItemRect( m_nPressed, &_rect );
	ClientToScreen( &_rect );
	GetDesktopWindow()->GetWindowRect( _screenrect );
	// 주화면에서만 사용할 경우
	//_rect.IntersectRect( _rect, _screenrect );

	TPMPARAMS				_TPparam			= { 0 };
	_TPparam.cbSize								= sizeof( TPMPARAMS );
	_TPparam.rcExclude							= _rect;
	g_pMenuCtrlBar								= this;
	g_hMenuMsgHook								= SetWindowsHookEx( WH_MSGFILTER, MenuInputFilter, NULL, GetCurrentThreadId() );

	TrackPopupMenuEx( pSubMenu->GetSafeHmenu(), TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_VERTICAL, _rect.left, _rect.bottom, m_hWnd, &_TPparam );
	PressButton( m_nPressed, FALSE );
	UnhookWindowsHookEx( g_hMenuMsgHook );
	g_hMenuMsgHook								= NULL;
	g_pMenuCtrlBar								= NULL;
}

BOOL CFrame_MenuBar_Ctrl::OnMenuInput( MSG* pMsg )
{
	BOOL bResult( FALSE );

	switch( pMsg->message )
	{
		case WM_MOUSEMOVE :		{
									CPoint		nowposition( SHORT( LOWORD( pMsg->lParam ) ), SHORT( HIWORD( pMsg->lParam ) ) );
									ScreenToClient( &nowposition );
									if( m_ptMouse == nowposition )								return TRUE;
									m_ptMouse	= nowposition;
									int nTestItemId( HitTest( &nowposition ) );
									if( nTestItemId >= 0 && nTestItemId < m_nItemCount && nTestItemId != m_nPressed )
									{
										PressButton( m_nPressed, FALSE );
										SendMessage( WM_CANCELMODE, 0, 0 );
										m_nPressed		= nTestItemId;
										PostMessage( MB_TRACKPOPUPMENU, 0, 0 );
										bResult			= TRUE;
									}
								}; break;
		case WM_LBUTTONDOWN :	{
									CPoint		nowposition( SHORT( LOWORD( pMsg->lParam ) ), SHORT( HIWORD( pMsg->lParam ) ) );
									ScreenToClient( &nowposition );
									int nTestItemId( HitTest( &nowposition ) );
									if( nTestItemId == m_nPressed )
									{
										PostMessage( WM_CANCELMODE, 0, 0 );
										bResult = TRUE;
									}
								}; break;
		case WM_KEYDOWN :		{
									TCHAR vkey	= (TCHAR)pMsg->wParam;
									if( vkey == VK_LEFT )
									{
										PressButton( m_nPressed, FALSE );
										m_nPressed--;
										PostMessage( WM_CANCELMODE, 0, 0 );
										PostMessage( MB_TRACKPOPUPMENU, 0, 0 );
										bResult = TRUE;
									} else if( vkey == VK_RIGHT )
									{
										PressButton( m_nPressed, FALSE );
										m_nPressed++;
										PostMessage( WM_CANCELMODE, 0, 0 );
										PostMessage( MB_TRACKPOPUPMENU, 0, 0 );
										bResult = TRUE;
									} else if( vkey == VK_ESCAPE )
									{
										PostMessage( WM_CANCELMODE, 0, 0 );
										bResult = TRUE;
									}
								}; break;
		case WM_MENUSELECT :	{
									GetOwner()->SendMessage( WM_MENUSELECT, pMsg->wParam, pMsg->lParam );
									bResult = TRUE;
								}; break;
		default:				{
			//
								}; break;
	}

	return bResult;
}



void CFrame_MenuBar_Ctrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint					ToolbarCheck( point + CPoint( 2, 0 ) );

	CToolBarCtrl::OnMouseMove(nFlags, point);
}

void CFrame_MenuBar_Ctrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCLICK pNMClick = reinterpret_cast<LPNMCLICK>(pNMHDR);

	BOOL					bReDraw( FALSE );
	CPoint					ToolbarCheck( CPoint( pNMClick->pt ) + CPoint( 2, 0 ) );

	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// 메뉴 실행시 이벤트 발생
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// void CFrame_MenuBar_Ctrl::OnMenuClick(UINT nID)
// {
// 	AfxGetApp()->GetMainWnd()->SendMessage( MAINFRAME_SENDMENUMSG, (WPARAM)nID, (LPARAM)0L );
// }

// void CFrame_MenuBar_Ctrl::OnUpdateMenuClick(CCmdUI* pCmdUI)
// {
// 	//
// }

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

BOOL CFrame_MenuBar_Ctrl::OnEraseBkgnd(CDC* pDC)
{
	CRect						thisRect( 0, 0, 0, 0 );
	GetClientRect( &thisRect );

	//pDC->FillSolidRect( thisRect, thePNO_FRMmng->GetMenuCtrlColor( 12 ) );
	pDC->FillSolidRect( thisRect, RGB( 255, 255, 255 ) );

	return TRUE;
	//	return CToolBarCtrl::OnEraseBkgnd(pDC);
}


BOOL CFrame_MenuBar_Ctrl::SetEnableMenu( int nMainIndex, int nSubIndex, UINT unID, BOOL bEnable )
{
	if( m_pThisMenu )
	{
		CMenu*					pSubMenu1														= m_pThisMenu->GetSubMenu( nMainIndex );
		if( pSubMenu1 )
		{
			if( nSubIndex > 0 )
			{
				CMenu*			pSubMenu2														= pSubMenu1->GetSubMenu( nSubIndex );
				if( pSubMenu2 )
				{
					int			nResult( pSubMenu2->EnableMenuItem( unID, ( bEnable ? MF_ENABLED : ( MF_DISABLED | MF_GRAYED ) ) ) );
					if( nResult == -1 )
					{
						return FALSE;
					}
					return TRUE;
				}
			} else {
				int			nResult( pSubMenu1->EnableMenuItem( unID, ( bEnable ? MF_ENABLED : ( MF_DISABLED | MF_GRAYED ) ) ) );
				if( nResult == -1 )
				{
					return FALSE;
				}
				return TRUE;
			}

		}
	}
	return FALSE;
}
