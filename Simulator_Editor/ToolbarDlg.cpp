// ToolbarDlg.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "ToolbarDlg.h"
#include "afxdialogex.h"


// CToolbarDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CToolbarDlg, CDialog)

CToolbarDlg::CToolbarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolbarDlg::IDD, pParent)
{
	m_ImgLogo														= NULL;
	m_rectImgLogo													= CRect(0,0,0,0);

	for( int i = 0; i < IDX_TOOLMENU_CNT; i++ )
	{
		for( int j = 0; j < 4; j++ )
			m_Icons[i][j]											= NULL;

		m_rectIcons[i]												= CRect(0,0,0,0);
	}
	
	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 3; j++ )
			m_TBSysIcons[i][j]										= NULL;

		m_rectTBSysIcons[i]											= CRect(0,0,0,0);
	}

	m_pFrameWnd														= NULL;
	m_nSelectIcon													= -1;
	m_nMoveIcon														= -1;
	m_nSysSelectIcon												= -1;
	m_nSysMoveIcon													= -1;
	m_bLButtonDown													= FALSE;

	m_wndMenuBarCtrl = NULL;
}

CToolbarDlg::~CToolbarDlg()
{
	if( m_wndMenuBarCtrl )
	{
		delete m_wndMenuBarCtrl;
		m_wndMenuBarCtrl																			= NULL;
	}
}

void CToolbarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolbarDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CToolbarDlg 메시지 처리기입니다.


BOOL CToolbarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadIcons();
	InitIcons();

	InitMenuBarCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CToolbarDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect														_rect, rect;
	GetClientRect( &_rect );
	dc.FillSolidRect( _rect, TOOLBAR_FRAME_COLOR );

	CPen														pen, *poldpen;
	CBrush														brush, *pOldBrush;

	pen.CreatePen( PS_SOLID, 1, TOOLBAR_BG_COLOR );
	poldpen														= (CPen*)dc.SelectObject( &pen );
	brush.CreateSolidBrush(	TOOLBAR_BG_COLOR);
	pOldBrush													= dc.SelectObject( &brush );

	rect														= _rect;
	rect.bottom -= TOOLBAR_BOTTOM_HEIGTH;
	dc.RoundRect( rect, CPoint(12,12) );

	dc.SelectObject( poldpen );
	pen.DeleteObject();
	dc.SelectObject( pOldBrush );
	brush.DeleteObject();


	pen.CreatePen( PS_SOLID, 1, TOOLBAR_BASE_COLOR );
	poldpen														= (CPen*)dc.SelectObject( &pen );
	brush.CreateSolidBrush(	TOOLBAR_BASE_COLOR);
	pOldBrush													= dc.SelectObject( &brush );

	rect.DeflateRect( m_rectImgLogo.Width(), 0 );
	dc.RoundRect( rect, CPoint(12,12) );

	dc.SelectObject( poldpen );
	pen.DeleteObject();
	dc.SelectObject( pOldBrush );
	brush.DeleteObject();

	//Title
	dc.SetBkMode( TRANSPARENT );
	dc.SetTextColor( TOOLBAR_TITLETEXT_COLOR );

	CFont font, *pOldFont;
	font.CreateFont( 22,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
		DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,VARIABLE_PITCH|FF_SWISS,L"맑은 고딕");
	pOldFont = dc.SelectObject( &font );

	dc.DrawText( _T("계통도"), CRect(_rect.left, _rect.top, _rect.right, _rect.top+TOOLBAR_TITLE_HEIGHT), DT_CENTER | DT_SINGLELINE | DT_VCENTER );

	//menu
	pen.CreatePen( PS_SOLID, 1, TOOLBAR_MENU_COLOR);
	poldpen														= (CPen*)dc.SelectObject( &pen );
	brush.CreateSolidBrush(TOOLBAR_MENU_COLOR);
	pOldBrush = dc.SelectObject(&brush);

	rect.top	= _rect.top + TOOLBAR_TITLE_HEIGHT;
	rect.bottom = rect.top + TOOLBAR_MENU_HEIGHT;

	dc.FillRect( rect, &brush );

	dc.SelectObject(poldpen);
	pen.DeleteObject();

	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	poldpen = (CPen*)dc.SelectObject(&pen);
	dc.MoveTo(rect.left, rect.top + 1);
	dc.LineTo(rect.right, rect.top + 1);
	dc.SelectObject(poldpen);
	pen.DeleteObject();

	pen.CreatePen(PS_SOLID, 1, RGB(124, 153, 135));
	poldpen = (CPen*)dc.SelectObject(&pen);
	dc.MoveTo(rect.left, rect.bottom);
	dc.LineTo(rect.right, rect.bottom);
	dc.SelectObject(poldpen);
	pen.DeleteObject();

	pen.CreatePen(PS_SOLID, 1, RGB(36, 84, 57));
	poldpen = (CPen*)dc.SelectObject(&pen);
	dc.MoveTo(rect.left, rect.bottom+1);
	dc.LineTo(rect.right, rect.bottom+1);
	dc.SelectObject(poldpen);
	pen.DeleteObject();

	dc.SelectObject(pOldBrush);
	brush.DeleteObject();
	dc.SelectObject(pOldFont);
	font.DeleteObject();

	DrawToolbar( &dc );
}

void CToolbarDlg::LoadIcons(void)
{
	CString								sModulePath( _T("") );

	sModulePath.Format( _T("%s\\Skin\\Toolbar\\Editor\\logo.pnoimg"), GetModulePath() );
	if( _waccess( sModulePath, 06 ) != -1 )
	{
		m_ImgLogo = (HBITMAP)::LoadImage( ::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE );
		::GetObject( m_ImgLogo, sizeof(BITMAP), &m_ImgLogoInfor );
	}

	for( int i = 0; i < IDX_TOOLMENU_CNT; i++ )
	{
		sModulePath.Format( _T("%s\\Skin\\Toolbar\\Editor\\%d_Down.pnoimg"), GetModulePath(), i+1 );
		if( _waccess( sModulePath, 06 ) != -1 )
		{
			m_Icons[i][0] = (HBITMAP)::LoadImage( ::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE );
			::GetObject( m_Icons[i][0], sizeof(BITMAP), &m_IconsInfor[i][0] );
		}

		sModulePath.Format( _T("%s\\Skin\\Toolbar\\Editor\\%d_off.pnoimg"), GetModulePath(), i+1 );
		if( _waccess( sModulePath, 06 ) != -1 )
		{
			m_Icons[i][1] = (HBITMAP)::LoadImage( ::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE );
			::GetObject( m_Icons[i][1], sizeof(BITMAP), &m_IconsInfor[i][1] );
		}

		sModulePath.Format( _T("%s\\Skin\\Toolbar\\Editor\\%d_On.pnoimg"), GetModulePath(), i+1 );
		if( _waccess( sModulePath, 06 ) != -1 )
		{
			m_Icons[i][2] = (HBITMAP)::LoadImage( ::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE );
			::GetObject( m_Icons[i][2], sizeof(BITMAP), &m_IconsInfor[i][2] );
		}

		sModulePath.Format(_T("%s\\Skin\\Toolbar\\Editor\\%d_Disable.pnoimg"), GetModulePath(), i + 1);
		if (_waccess(sModulePath, 06) != -1)
		{
			m_Icons[i][3] = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
			::GetObject(m_Icons[i][3], sizeof(BITMAP), &m_IconsInfor[i][3]);
		}
		sModulePath.Format(_T("%s\\Skin\\Toolbar\\Editor\\%d_Down.pnoimg"), GetModulePath(), i + 1);
		if (_waccess(sModulePath, 06) != -1)
		{
			m_Icons[i][4] = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
			::GetObject(m_Icons[i][4], sizeof(BITMAP), &m_IconsInfor[i][4]);
		}
	}

	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 3; j++ )
		{
			sModulePath.Format( _T("%s\\Skin\\SystemMenu\\%s"), GetModulePath(), GetIconFileName(IDX_CAPTION_MINIMIZE_ON + (i*4)+j) );
			if( _waccess( sModulePath, 06 ) != -1 )
			{
				m_TBSysIcons[i][j] = (HBITMAP)::LoadImage( ::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE );
				::GetObject( m_TBSysIcons[i][j], sizeof(BITMAP), &m_TBSysIconsInfor[i][j] );
			}
		}
	}
}

void CToolbarDlg::InitIcons(void)
{
	int															i( 0 );
	CRect														_rect( 0, 0, 0, 0 );
	GetWindowRect( &_rect );
	ScreenToClient( _rect );

	CRect														IconsRect( 0, 0, 0, 0 );
	IconsRect													= CRect( 0, 0, 0, 0 );

	IconsRect.left												= 0;
	IconsRect.top												= (_rect.bottom - m_ImgLogoInfor.bmHeight) / 2;
	IconsRect.right												= IconsRect.left + m_ImgLogoInfor.bmWidth;
	IconsRect.bottom											= IconsRect.top + m_ImgLogoInfor.bmHeight;
	m_rectImgLogo												= IconsRect;

	IconsRect.left												= IconsRect.right + 15;
	IconsRect.top												= ((_rect.bottom-TOOLBAR_BOTTOM_HEIGTH) + m_IconsInfor[0][0].bmHeight) / 2;
	IconsRect.right												= IconsRect.left + m_IconsInfor[0][0].bmWidth;
	IconsRect.bottom											= IconsRect.top + m_IconsInfor[0][0].bmHeight;
	m_rectIcons[0]												= IconsRect;
	for( int i = 1; i < IDX_TOOLMENU_CNT; i++ )
	{
		IconsRect.left											= m_rectIcons[i-1].right + TOOLMENU_GAP;
		IconsRect.top											= m_rectIcons[i-1].top;
		IconsRect.right											= IconsRect.left + m_IconsInfor[i][0].bmWidth;
		IconsRect.bottom										= IconsRect.top + m_IconsInfor[i][0].bmHeight;
		m_rectIcons[i]											= IconsRect;
	}

	IconsRect.left												= (_rect.right) - (m_TBSysIconsInfor[0][0].bmWidth + m_TBSysIconsInfor[1][0].bmWidth + m_TBSysIconsInfor[2][0].bmWidth);
	IconsRect.top												= _rect.top;
	IconsRect.right												= IconsRect.left + m_TBSysIconsInfor[0][0].bmWidth;
	IconsRect.bottom											= IconsRect.top + m_TBSysIconsInfor[0][0].bmWidth;
	m_rectTBSysIcons[0]											= IconsRect;
	for( int i = 1; i < 3; i++ )
	{
		IconsRect.left											= m_rectTBSysIcons[i-1].right;
		IconsRect.top											= m_rectTBSysIcons[i-1].top;
		IconsRect.right											= IconsRect.left + m_TBSysIconsInfor[i][0].bmWidth;
		IconsRect.bottom										= IconsRect.top + m_TBSysIconsInfor[i][0].bmWidth;
		m_rectTBSysIcons[i]										= IconsRect;
	}
	
	CClientDC dc(this);
	DrawToolbar(&dc);
}

void CToolbarDlg::SetSysIconsRect()
{
	int															i( 0 );
	CRect														_rect( 0, 0, 0, 0 );
	GetWindowRect( &_rect );
	ScreenToClient( _rect );

	CRect														IconsRect( 0, 0, 0, 0 );
	IconsRect													= CRect( 0, 0, 0, 0 );

	IconsRect.left												= (_rect.right-10) - (m_TBSysIconsInfor[0][0].bmWidth + m_TBSysIconsInfor[1][0].bmWidth + m_TBSysIconsInfor[2][0].bmWidth);
	IconsRect.top												= _rect.top;
	IconsRect.right												= IconsRect.left + m_TBSysIconsInfor[0][0].bmWidth;
	IconsRect.bottom											= IconsRect.top + m_TBSysIconsInfor[0][0].bmWidth;
	m_rectTBSysIcons[0]											= IconsRect;
	for( int i = 1; i < 3; i++ )
	{
		IconsRect.left											= m_rectTBSysIcons[i-1].right;
		IconsRect.top											= m_rectTBSysIcons[i-1].top;
		IconsRect.right											= IconsRect.left + m_TBSysIconsInfor[i][0].bmWidth;
		IconsRect.bottom										= IconsRect.top + m_TBSysIconsInfor[i][0].bmWidth;
		m_rectTBSysIcons[i]										= IconsRect;
	}

	CClientDC dc(this);
	DrawToolbar(&dc);
}

void CToolbarDlg::DrawToolbar(CDC* pDC)
{
	if( !m_pFrameWnd )											return;

	int															i( 0 );
	CRect														_rect( 0, 0, 0, 0 );
	GetWindowRect( &_rect );
	ScreenToClient( _rect );
	CDC															tmpDC;
	tmpDC.CreateCompatibleDC( pDC );
	
	CBitmap														bmpBuffer, *pOldBitmap = NULL;
	HGDIOBJ														hgdiobj = NULL;
	
	bmpBuffer.CreateCompatibleBitmap( pDC, _rect.Width(), _rect.Height() );
	pOldBitmap													= (CBitmap *)pDC->SelectObject(&bmpBuffer);
	
	if( m_ImgLogo )
	{
		hgdiobj = tmpDC.SelectObject( m_ImgLogo );
		pDC->BitBlt( m_rectImgLogo.left, m_rectImgLogo.top, m_rectImgLogo.Width(), m_rectImgLogo.Height(), &tmpDC, 0, 0, SRCCOPY );
	}
	
	if( m_TBSysIcons[0] )
	{
		if( m_nSysSelectIcon == 0 )
		{
			hgdiobj = tmpDC.SelectObject( m_TBSysIcons[0][0] );
		}
		else
		{
			if(  m_nSysMoveIcon == 0 && !m_bLButtonDown )		hgdiobj = tmpDC.SelectObject( m_TBSysIcons[0][2] );
			else												hgdiobj = tmpDC.SelectObject( m_TBSysIcons[0][1] );
		}

		pDC->BitBlt( m_rectTBSysIcons[0].left, m_rectTBSysIcons[0].top, m_rectTBSysIcons[0].Width(), m_rectTBSysIcons[0].Height(), &tmpDC, 0, 0, SRCCOPY );
	}

	if( m_TBSysIcons[1] && m_TBSysIcons[3] )
	{
		if( m_nSysSelectIcon == 1 )
		{
			if( m_pFrameWnd->IsZoomed() )						hgdiobj = tmpDC.SelectObject( m_TBSysIcons[3][0] );
			else												hgdiobj = tmpDC.SelectObject( m_TBSysIcons[1][0] );
		}
		else
		{
			if(  m_nSysMoveIcon == 1 && !m_bLButtonDown )
			{
				if( m_pFrameWnd->IsZoomed() )					hgdiobj = tmpDC.SelectObject( m_TBSysIcons[3][2] );
				else											hgdiobj = tmpDC.SelectObject( m_TBSysIcons[1][2] );
			}
			else
			{
				if( m_pFrameWnd->IsZoomed() )					hgdiobj = tmpDC.SelectObject( m_TBSysIcons[3][1] );
				else											hgdiobj = tmpDC.SelectObject( m_TBSysIcons[1][1] );
			}
		}

		pDC->BitBlt( m_rectTBSysIcons[1].left, m_rectTBSysIcons[1].top, m_rectTBSysIcons[1].Width(), m_rectTBSysIcons[1].Height(), &tmpDC, 0, 0, SRCCOPY );
	}

	if( m_TBSysIcons[2] )
	{
		if( m_nSysSelectIcon == 2 )
		{
			hgdiobj = tmpDC.SelectObject( m_TBSysIcons[2][0] );
		}
		else
		{
			if(  m_nSysMoveIcon == 2 && !m_bLButtonDown )		hgdiobj = tmpDC.SelectObject( m_TBSysIcons[2][2] );
			else												hgdiobj = tmpDC.SelectObject( m_TBSysIcons[2][1] );
		}

		pDC->BitBlt( m_rectTBSysIcons[2].left, m_rectTBSysIcons[2].top, m_rectTBSysIcons[2].Width(), m_rectTBSysIcons[2].Height(), &tmpDC, 0, 0, SRCCOPY );
	}

	for( int i = 0; i < IDX_TOOLMENU_CNT; i++ )
	{
		if( m_Icons[i] )
		{
			if( i == m_nSelectIcon )
			{
				hgdiobj = tmpDC.SelectObject( m_Icons[i][0] );
			}
			else
			{
				if( i == m_nMoveIcon && !m_bLButtonDown )			hgdiobj = tmpDC.SelectObject( m_Icons[i][2] );
				else												hgdiobj = tmpDC.SelectObject( m_Icons[i][1] );
			}

			pDC->BitBlt( m_rectIcons[i].left, m_rectIcons[i].top, m_rectIcons[i].Width(), m_rectIcons[i].Height(), &tmpDC, 0, 0, SRCCOPY );
		}
	}

	tmpDC.SelectObject( hgdiobj );
	tmpDC.DeleteDC();
	
	pDC->BitBlt( 0, 0, _rect.Width(), _rect.Height(), pDC, 0, 0, SRCCOPY );
}

CString CToolbarDlg::GetIconFileName(UINT nIconID)
{
	switch( nIconID )
	{
	case IDX_CAPTION_MINIMIZE_ON:									return _T("Caption_Minimize_Down.pnoimg");
	case IDX_CAPTION_MINIMIZE_OFF:									return _T("Caption_Minimize_Off.pnoimg");
	case IDX_CAPTION_MINIMIZE_DOWN:									return _T("Caption_Minimize_On.pnoimg");
	case IDX_CAPTION_MAXIMIZE_ON:									return _T("Caption_Maximize_Down.pnoimg");
	case IDX_CAPTION_MAXIMIZE_OFF:									return _T("Caption_Maximize_Off.pnoimg");
	case IDX_CAPTION_MAXIMIZE_DOWN:									return _T("Caption_Maximize_On.pnoimg");
	case IDX_CAPTION_EXIT_ON:										return _T("Caption_Exit_Down.pnoimg");
	case IDX_CAPTION_EXIT_OFF:										return _T("Caption_Exit_Off.pnoimg");
	case IDX_CAPTION_EXIT_DOWN:										return _T("Caption_Exit_On.pnoimg");
	case IDX_CAPTION_RESTORE_ON:									return _T("Caption_Restore_Down.pnoimg");
	case IDX_CAPTION_RESTORE_OFF:									return _T("Caption_Restore_Off.pnoimg");
	case IDX_CAPTION_RESTORE_DOWN:									return _T("Caption_Restore_On.pnoimg");
	}
	return _T("");
}

CString CToolbarDlg::GetModulePath(void)
{
	CString sPath;
	GetModuleFileName( AfxGetApp()->m_hInstance, sPath.GetBuffer(MAX_PATH), MAX_PATH );
	sPath.ReleaseBuffer();

	int nPos = sPath.ReverseFind(_T('\\'));
	if( nPos != -1 )
		sPath = sPath.Left( nPos );

	return sPath;
}


void CToolbarDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	SetSysIconsRect();
}

void CToolbarDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CRect														rectTitle;
	GetClientRect(&rectTitle);
	rectTitle.DeflateRect(m_rectImgLogo.Width(), 0);
	rectTitle.bottom = rectTitle.top + TOOLBAR_TITLE_HEIGHT;

	if (rectTitle.PtInRect(point))
	{
		CPoint pt = point;
		ClientToScreen(&pt);
		m_pFrameWnd->PostMessage(WM_NCLBUTTONDBLCLK, HTCAPTION, MAKELPARAM(pt.x, pt.y));
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CToolbarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect														rectTitle;
	GetClientRect(&rectTitle);
	rectTitle.DeflateRect(m_rectImgLogo.Width(), 0);
	rectTitle.bottom = rectTitle.top + TOOLBAR_TITLE_HEIGHT;
	
	if (rectTitle.PtInRect(point))
	{
		CPoint pt = point;
		ClientToScreen(&pt);
		m_pFrameWnd->PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pt.x, pt.y));
		CDialog::OnLButtonDown(nFlags, point);
		return;
	}


	m_bLButtonDown													= TRUE;
	SetCapture();

	m_nSysSelectIcon												= -1;
	for( int i = 0; i < 3; i++ )
	{
		if( m_rectTBSysIcons[i].PtInRect( point ) )
		{
			m_nSysSelectIcon										= i;
			break;
		}
	}

	m_nSelectIcon													= -1;
	for( int i = 0 ; i < IDX_TOOLMENU_CNT ; i++ )
	{
		if( m_rectIcons[i].PtInRect( point ) )
		{
			m_nSelectIcon											= i;
			break;
		}
	}

	if( (m_nSelectIcon != -1) || (m_nSysSelectIcon != -1) )
	{
		CClientDC			dc( this );
		DrawToolbar( &dc );
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CToolbarDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if( m_bLButtonDown )											return;

	BOOL															bReDraw(FALSE);
	int																nIconIdx;
	
	nIconIdx														= -1;
	for( int i = 0 ; i < 3 ; i++ )
	{
		if( m_rectTBSysIcons[i].PtInRect( point ) )
		{
			nIconIdx												= i;
			break;
		}
	}
	if( m_nSysMoveIcon != nIconIdx )
	{
		m_nSysMoveIcon												= nIconIdx;
		bReDraw														= TRUE;
	}

	nIconIdx														= -1;
	for( int i = 0 ; i < IDX_TOOLMENU_CNT ; i++ )
	{
		if( m_rectIcons[i].PtInRect( point ) )
		{
			nIconIdx												= i;
			break;
		}
	}
	if( m_nMoveIcon != nIconIdx )
	{
		m_nMoveIcon													= nIconIdx;
		bReDraw														= TRUE;
	}

	if( bReDraw )
	{
		CClientDC													dc( this );
		DrawToolbar(&dc);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CToolbarDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLButtonDown													= FALSE;
	ReleaseCapture();
	
	if( (m_nSelectIcon == -1) && (m_nSysSelectIcon == -1) )			return;

	int																nIconIdx;

	nIconIdx														= -1;
	for( int i = 0 ; i < IDX_TOOLMENU_CNT ; i++ )
	{
		if( m_rectTBSysIcons[i].PtInRect( point ) )
		{
			nIconIdx												= i;
			break;
		}
	}
	m_nSysMoveIcon = nIconIdx;
	if((nIconIdx != -1) && (nIconIdx == m_nSysSelectIcon))
	{
		m_pFrameWnd->SendMessage( WM_TOOLBAR_MSG, 0, nIconIdx );
		m_nSysMoveIcon = -1;
	}

	nIconIdx														= -1;
	for( int i = 0 ; i < IDX_TOOLMENU_CNT ; i++ )
	{
		if( m_rectIcons[i].PtInRect( point ) )
		{
			nIconIdx												= i;
			break;
		}
	}
	m_nMoveIcon														= nIconIdx;
	if((nIconIdx != -1) && (nIconIdx == m_nSelectIcon))				m_pFrameWnd->SendMessage( WM_TOOLBAR_MSG, 1, nIconIdx );

 	m_nSelectIcon													= -1;
 	m_nSysSelectIcon												= -1;

	CClientDC														dc( this );
	DrawToolbar(&dc);

	CDialog::OnLButtonUp(nFlags, point);
}


void CToolbarDlg::InitMenuBarCtrl()
{
	if( m_wndMenuBarCtrl )
	{
		delete m_wndMenuBarCtrl;
		m_wndMenuBarCtrl																			= NULL;
	}

	CMenu*		pThisMenu										= new CMenu;
	pThisMenu->LoadMenu( IDR_MAINFRAME );

	CRect		rectWindSize;
	rectWindSize.left = m_rectImgLogo.Width();
	rectWindSize.top = TOOLBAR_TITLE_HEIGHT + 2;
	rectWindSize.right = 410;
	rectWindSize.bottom = rectWindSize.top + TOOLBAR_MENU_HEIGHT - 2;

	m_wndMenuBarCtrl											= new CFrame_MenuBar_Ctrl;
	m_wndMenuBarCtrl->Create( WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | TBSTYLE_LIST | CCS_NODIVIDER | CCS_NORESIZE, rectWindSize, this, 13001 );
	m_wndMenuBarCtrl->LoadMenu( pThisMenu );
	m_wndMenuBarCtrl->ShowWindow( SW_SHOW );
}

