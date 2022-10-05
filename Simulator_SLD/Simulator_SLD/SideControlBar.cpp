// SideControlBar.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "SideControlBar.h"
#include "StyleDef.h"

void CSCBDockBar::DrawBorder()
{
	CWindowDC dc(this);
	CRect rectClient;
	GetClientRect(rectClient);

	CRect rect;
	GetWindowRect(rect);
	ScreenToClient(rect);
	rectClient.OffsetRect(-rect.left, -rect.top);
	dc.ExcludeClipRect(rectClient);


	// draw borders in non-client area
	rect.OffsetRect(-rect.left, -rect.top);

	DWORD dwStyle = m_dwStyle;
	if (!(dwStyle & CBRS_BORDER_ANY))
		return;

	// prepare for dark lines
	ASSERT(rect.top == 0 && rect.left == 0);
	CRect rect1, rect2;
	rect1 = rect;
	rect2 = rect;
	COLORREF clr = WND_BG_FRAME_COLOR;


	// draw dark line one pixel back/up
	if (dwStyle & CBRS_BORDER_3D)
	{
		rect1.right -= AFX_CX_BORDER;
		rect1.bottom -= AFX_CY_BORDER;
	}
	if (dwStyle & CBRS_BORDER_TOP)
		rect2.top += afxData.cyBorder2;
	if (dwStyle & CBRS_BORDER_BOTTOM)
		rect2.bottom -= afxData.cyBorder2;

	// draw left and top
	if (dwStyle & CBRS_BORDER_LEFT)
		dc.FillSolidRect(0, rect2.top, AFX_CX_BORDER, rect2.Height(), clr);
	if (dwStyle & CBRS_BORDER_TOP)
		dc.FillSolidRect(0, 0, rect.right, AFX_CY_BORDER, clr);

	// draw right and bottom
	if (dwStyle & CBRS_BORDER_RIGHT)
		dc.FillSolidRect(rect1.right, rect2.top, -AFX_CX_BORDER, rect2.Height(), clr);
	if (dwStyle & CBRS_BORDER_BOTTOM)
		dc.FillSolidRect(0, rect1.bottom, rect.right, -AFX_CY_BORDER, clr);


	if (dwStyle & CBRS_BORDER_3D)
	{
		// prepare for hilite lines
		clr = WND_BG_FRAME_COLOR;
		// draw left and top
		if (dwStyle & CBRS_BORDER_LEFT)
			dc.FillSolidRect(1, rect2.top, AFX_CX_BORDER, rect2.Height(), clr);
		if (dwStyle & CBRS_BORDER_TOP)
			dc.FillSolidRect(0, 1, rect.right, AFX_CY_BORDER, clr);

		// draw right and bottom
		if (dwStyle & CBRS_BORDER_RIGHT)
			dc.FillSolidRect(rect.right, rect2.top, -AFX_CX_BORDER, rect2.Height(), clr);
		if (dwStyle & CBRS_BORDER_BOTTOM)
			dc.FillSolidRect(0, rect.bottom, rect.right, -AFX_CY_BORDER, clr);
	}
}

// CSideControlBar

IMPLEMENT_DYNAMIC(CSideControlBar, CControlBar)

CSideControlBar::CSideControlBar() :
	m_szMin(26, 32)
	, m_szHorz(200, 200)
	, m_szVert(200, 200)
	, m_szFloat(200, 200)
	, m_bTracking(FALSE)
	, m_bKeepSize(FALSE)
	, m_bParentSizing(FALSE)
	, m_nEdgeXsize(5)
	, m_bDragContent(FALSE)
	, m_nDockBarID(0)
	, m_dwSCBSstyle(0)
	, m_szRestoreHorz(0)
	, m_szRestoreVert(0)
	, m_bControlShow(TRUE)
{
	m_pTabGroup1 = NULL;
	m_pTabGroup2 = NULL;
	m_pTabGroup3 = NULL;

	m_pTreeViewDlg = NULL;
	m_pGroup1CompDlg = NULL;
	m_pGroup1MeasDlg = NULL;
	m_pGroup1ApplDlg = NULL;
	m_pGroup2DlInfoDlg = NULL;
}

CSideControlBar::~CSideControlBar()
{
	if (m_pTabGroup1)																	delete m_pTabGroup1;
	m_pTabGroup1 = NULL;

	if (m_pTabGroup2)																	delete m_pTabGroup2;
	m_pTabGroup2 = NULL;

	if (m_pTabGroup3)																	delete m_pTabGroup3;
	m_pTabGroup3 = NULL;

	if (m_pTreeViewDlg)																	delete m_pTreeViewDlg;
	m_pTreeViewDlg = NULL;

	if (m_pGroup1CompDlg)																delete m_pGroup1CompDlg;
	m_pGroup1CompDlg = NULL;

	if (m_pGroup1MeasDlg)																delete m_pGroup1MeasDlg;
	m_pGroup1MeasDlg = NULL;

	if (m_pGroup1ApplDlg)																delete m_pGroup1ApplDlg;
	m_pGroup1ApplDlg = NULL;

	if (m_pGroup2DlInfoDlg)																delete m_pGroup2DlInfoDlg;
	m_pGroup2DlInfoDlg = NULL;
}


BEGIN_MESSAGE_MAP(CSideControlBar, CControlBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_CAPTURECHANGED()
	ON_WM_SETTINGCHANGE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	ON_WM_NCACTIVATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSELEAVE()
	ON_MESSAGE(WM_SIDECTRL_MSG, &CSideControlBar::OnSideControlBarMsg)
END_MESSAGE_MAP()



// CSideControlBar 메시지 처리기
BOOL CSideControlBar::Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, CSize sizeDefault, UINT nID, DWORD dwStyle)
{
	ASSERT_VALID(pParentWnd);
	ASSERT(!((dwStyle & CBRS_SIZE_FIXED) && (dwStyle & CBRS_SIZE_DYNAMIC)));

	m_dwStyle = dwStyle & CBRS_ALL;
	m_szHorz = m_szVert = m_szFloat = sizeDefault;
	CString wndclass = ::AfxRegisterWndClass(CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW), ::GetSysColorBrush(COLOR_BTNFACE), 0);
	dwStyle &= ~CBRS_ALL;
	dwStyle |= WS_CLIPCHILDREN;
	if (!CWnd::Create(wndclass, lpszWindowName, dwStyle, CRect(0, 0, 0, 0), pParentWnd, nID))
		return FALSE;

	return TRUE;
}

void CSideControlBar::OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL /*bDisableIfNoHndler*/)
{
}

CSize CSideControlBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	if (bStretch)
	{
		if (bHorz)
		{
			return CSize(32767, m_szHorz.cy);
		}
		else {
			return CSize(m_szVert.cx, 32767);
		}
	}

	CSCBDockBar*	pDockBar = (CSCBDockBar*)m_pDockBar;
	AFX_SIZEPARENTPARAMS layout;
	ZeroMemory(&layout, sizeof(AFX_SIZEPARENTPARAMS));
	layout.hDWP = pDockBar->m_bLayoutQuery ? NULL : ::BeginDeferWindowPos(1);
	RecalcDelayShow(&layout);
	if (layout.hDWP != NULL)
		::EndDeferWindowPos(layout.hDWP);

	CRect			_rect(pDockBar->m_rectLayout);
	if (_rect.IsRectEmpty())
	{
		m_pDockSite->GetClientRect(&_rect);
	}
	int				nLengthAvail = bHorz ? _rect.Width() + 2 : _rect.Height() - 2;

	if (IsVisible() && !IsFloating() && m_bParentSizing)
		if (NegoSpace(nLengthAvail, (bHorz != FALSE)))
			RecalcLayoutControlBar();

	m_bParentSizing = FALSE;

	CSize szRet = bHorz ? m_szHorz : m_szVert;
	szRet.cx = max(m_szMin.cx, szRet.cx);
	szRet.cy = max(m_szMin.cy, szRet.cy);

	return szRet;
}

CSize CSideControlBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	if (dwMode & (LM_HORZDOCK | LM_VERTDOCK))
	{
		if (nLength == -1)
			m_bParentSizing = TRUE;

		return CControlBar::CalcDynamicLayout(nLength, dwMode);
	}

	if (dwMode & LM_MRUWIDTH)		return m_szFloat;
	if (dwMode & LM_COMMIT)			return m_szFloat;

	((dwMode & LM_LENGTHY) ? m_szFloat.cy : m_szFloat.cx) = nLength;

	m_szFloat.cx = max(m_szFloat.cx, m_szMin.cx);
	m_szFloat.cy = max(m_szFloat.cy, m_szMin.cy);

	return m_szFloat;
}

BOOL CSideControlBar::DestroyWindow()
{
	return CControlBar::DestroyWindow();
}

UINT CSideControlBar::GetEdgeCode(int nEdge)
{
	if (nEdge == 0)			return HTLEFT;
	if (nEdge == 1)			return HTTOP;
	if (nEdge == 2)			return HTRIGHT;
	if (nEdge == 3)			return HTBOTTOM;

	return HTNOWHERE;
}

BOOL CSideControlBar::GetEdgeRect(CRect rcWnd, UINT nHitTest, CRect& rcEdge)
{
	rcEdge = rcWnd;
	if (m_dwSCBSstyle & SCBS_SHOWEDGES)
		rcEdge.DeflateRect(1, 1);
	BOOL					bHorz(IsHorzDocked());

	switch (nHitTest)
	{
	case HTLEFT: {
		if (!(m_dwSCBSstyle & SCBS_EDGELEFT)) return FALSE;
		rcEdge.right = rcEdge.left + m_nEdgeXsize;
		rcEdge.DeflateRect(0, bHorz ? m_nEdgeXsize : 0);
	}; break;
	case HTTOP: {
		if (!(m_dwSCBSstyle & SCBS_EDGETOP)) return FALSE;
		rcEdge.bottom = rcEdge.top + m_nEdgeXsize;
		rcEdge.DeflateRect(bHorz ? 0 : m_nEdgeXsize, 0);
	}; break;
	case HTRIGHT: {
		if (!(m_dwSCBSstyle & SCBS_EDGERIGHT)) return FALSE;
		rcEdge.left = rcEdge.right - m_nEdgeXsize;
		rcEdge.DeflateRect(0, bHorz ? m_nEdgeXsize : 0);
	}; break;
	case HTBOTTOM: {
		if (!(m_dwSCBSstyle & SCBS_EDGEBOTTOM)) return FALSE;
		rcEdge.top = rcEdge.bottom - m_nEdgeXsize;
		rcEdge.DeflateRect(bHorz ? 0 : m_nEdgeXsize, 0);
	}; break;
	default: {
		ASSERT(FALSE);
	}; break;
	}
	return TRUE;
}

BOOL CSideControlBar::NegoSpace(int nLengthAvail, BOOL bHorz)
{
	ASSERT(bHorz == IsHorzDocked());

	if (!IsVisible() || nLengthAvail <= 0)
	{
		CRect					rectBar(0, 0, 0, 0);
		GetWindowRect(&rectBar);
		nLengthAvail -= (bHorz ? rectBar.Width() - 2 : rectBar.Height() - 2);
	}

	int						nActualLength(0);
	int						nMinLength(2);
	int						nWidth(0);

	nActualLength += bHorz ? m_szHorz.cx - 2 : m_szVert.cy - 2;
	nMinLength += bHorz ? m_szMin.cx - 2 : m_szMin.cy - 2;
	nWidth = max(nWidth, bHorz ? m_szHorz.cy : m_szVert.cx);

	if (nMinLength > nLengthAvail)
	{
		return FALSE;
	}

	if (bHorz)
	{
		m_szHorz.cy = nWidth;
	}
	else {
		m_szVert.cx = nWidth;
	}

	if (nActualLength == nLengthAvail)
		return TRUE;

	int						nDelta(nLengthAvail - nActualLength);
	while (nDelta != 0)
	{
		int					nDeltaOld(nDelta);
		int					nLMin(bHorz ? m_szMin.cx : m_szMin.cy);
		int					nL(bHorz ? m_szHorz.cx : m_szVert.cy);

		if ((nL == nLMin) && (nDelta < 0) || m_bKeepSize)
			continue;

		int					nDelta2 = (nDelta == 0) ? 0 : ((nDelta < 0) ? -1 : 1);
		(bHorz ? m_szHorz.cx : m_szVert.cy) += nDelta2;
		nDelta -= nDelta2;
		if (nDelta == 0)				break;
		if ((nDeltaOld == nDelta) || (nDelta == 0))
			m_bKeepSize = FALSE;
	}

	return TRUE;
}

void CSideControlBar::StartTracking(UINT nHitTest)
{
	SetCapture();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);
	BOOL				bHorz = IsHorzDocked();
	m_szHorzVertOld = bHorz ? m_szHorz : m_szVert;
	CRect				_rect(0, 0, 0, 0);
	GetWindowRect(&_rect);
	CRect				rcEdge(0, 0, 0, 0);
	VERIFY(GetEdgeRect(_rect, nHitTest, rcEdge));
	m_ptEdgeOld = rcEdge.CenterPoint();
	m_unDocEdge = nHitTest;
	m_bTracking = TRUE;
	m_szMinTemp = m_szMin;

	if (!IsSideTracking())
	{
		m_pDockSite->RepositionBars(0, 0xFFFF, AFX_IDW_PANE_FIRST, reposQuery, &_rect, NULL, TRUE);
		m_szMaxTemp = m_szHorzVertOld + _rect.Size() - CSize(4, 4);
	}
	else {
		m_szMaxTemp = m_szHorzVertOld + (bHorz ? m_szHorz : m_szVert) - m_szMin;
	}

	OnTrackInvertTracker();
}

void CSideControlBar::StopTracking()
{
	OnTrackInvertTracker();
	m_bTracking = FALSE;
	ReleaseCapture();
	m_pDockSite->DelayRecalcLayout();
}

void CSideControlBar::OnTrackUpdateSize(CPoint& point)
{
	ASSERT(!IsFloating());

	CPoint						pt(point);
	ClientToScreen(&pt);
	CSize						szDelta(pt - m_ptEdgeOld);
	CSize						sizeNew(m_szHorzVertOld);
	switch (m_unDocEdge)
	{
	case HTLEFT:			sizeNew -= CSize(szDelta.cx, 0); break;
	case HTTOP:				sizeNew -= CSize(0, szDelta.cy); break;
	case HTRIGHT:			sizeNew += CSize(szDelta.cx, 0); break;
	case HTBOTTOM:			sizeNew += CSize(0, szDelta.cy); break;
	}
	sizeNew.cx = max(m_szMinTemp.cx, min(m_szMaxTemp.cx, sizeNew.cx));
	sizeNew.cy = max(m_szMinTemp.cy, min(m_szMaxTemp.cy, sizeNew.cy));

	BOOL						bHorz(IsHorzDocked());
	szDelta = sizeNew - (bHorz ? m_szHorz : m_szVert);
	if (szDelta == CSize(0, 0))			return;
	OnTrackInvertTracker();
	(bHorz ? m_szHorz : m_szVert) = sizeNew;

	if (!IsSideTracking())
	{
		(bHorz ? m_szHorz.cy : m_szVert.cx) = bHorz ? sizeNew.cy : sizeNew.cx;
	}
	else {
		(bHorz ? m_szHorz.cx : m_szVert.cy) -= bHorz ? szDelta.cx : szDelta.cy;
	}

	OnTrackInvertTracker();

	if (m_bDragContent)
		m_pDockSite->DelayRecalcLayout();
}

void CSideControlBar::OnTrackInvertTracker()
{
	ASSERT(m_bTracking);
	if (m_bDragContent)
		return;

	BOOL					bHorz = IsHorzDocked();
	CRect					_rect(0, 0, 0, 0), rectBar(0, 0, 0, 0), rectDock(0, 0, 0, 0), rectFrame(0, 0, 0, 0);
	GetWindowRect(rectBar);
	m_pDockBar->GetWindowRect(rectDock);
	m_pDockSite->GetWindowRect(rectFrame);
	VERIFY(GetEdgeRect(rectBar, m_unDocEdge, _rect));
	if (!IsSideTracking())
	{
		_rect = bHorz ? CRect(rectDock.left + 1, _rect.top, rectDock.right - 1, _rect.bottom) : CRect(_rect.left, rectDock.top + 1, _rect.right, rectDock.bottom - 1);
	}
	_rect.OffsetRect(-rectFrame.TopLeft());

	CSize						sizeNew(bHorz ? m_szHorz : m_szVert);
	CSize						sizeDelta(sizeNew - m_szHorzVertOld);
	if (m_nDockBarID == AFX_IDW_DOCKBAR_LEFT && m_unDocEdge == HTTOP ||
		m_nDockBarID == AFX_IDW_DOCKBAR_RIGHT && m_unDocEdge != HTBOTTOM ||
		m_nDockBarID == AFX_IDW_DOCKBAR_TOP && m_unDocEdge == HTLEFT ||
		m_nDockBarID == AFX_IDW_DOCKBAR_BOTTOM && m_unDocEdge != HTRIGHT)
		sizeDelta = -sizeDelta;
	_rect.OffsetRect(sizeDelta);
	CDC*					pDC = m_pDockSite->GetDCEx(NULL, DCX_WINDOW | DCX_CACHE | DCX_LOCKWINDOWUPDATE);
	CBrush*					pBrush = CDC::GetHalftoneBrush();
	CBrush*					pBrushOld = pDC->SelectObject(pBrush);
	pDC->PatBlt(_rect.left, _rect.top, _rect.Width(), _rect.Height(), PATINVERT);
	pDC->SelectObject(pBrushOld);
	m_pDockSite->ReleaseDC(pDC);
}

const BOOL CSideControlBar::IsFloating() const
{
	return (!IsHorzDocked() && !IsVertDocked());
}

const BOOL CSideControlBar::IsHorzDocked() const
{
	return(m_nDockBarID == AFX_IDW_DOCKBAR_TOP || m_nDockBarID == AFX_IDW_DOCKBAR_BOTTOM);
}

const BOOL CSideControlBar::IsVertDocked() const
{
	return(m_nDockBarID == AFX_IDW_DOCKBAR_LEFT || m_nDockBarID == AFX_IDW_DOCKBAR_RIGHT);
}

const BOOL CSideControlBar::IsSideTracking() const
{
	ASSERT(m_bTracking && !IsFloating());
	return (m_unDocEdge == HTLEFT || m_unDocEdge == HTRIGHT) ? IsHorzDocked() : IsVertDocked();
}

void CSideControlBar::Show()
{
	m_szHorz = m_szRestoreHorz;
	m_szVert = m_szRestoreVert;
	m_szRestoreHorz = m_szRestoreVert = CSize(0, 0);
	StartTracking(HTRIGHT);
	RecalcLayoutControlBar();
	StopTracking();
	m_bControlShow = TRUE;
}

void CSideControlBar::Hide()
{
	m_szRestoreHorz = m_szHorz;
	m_szRestoreVert = m_szVert;
	m_szHorz.cx = m_szVert.cx = m_szMin.cx;
	StartTracking(HTRIGHT);
	RecalcLayoutControlBar();
	StopTracking();
	m_bControlShow = FALSE;
}

void CSideControlBar::RecalcLayoutControlBar()
{
	BOOL					bHorz(IsHorzDocked());
	BOOL					bNeedRecalc(FALSE);
	int						nAlign(bHorz ? -2 : 0);

	CRect					_rect(0, 0, 0, 0), rectDock(0, 0, 0, 0);
	m_pDockBar->GetWindowRect(&rectDock);

	if (!IsVisible()) return;

	GetWindowRect(&_rect);
	_rect.OffsetRect(-rectDock.TopLeft());
	_rect = CRect(_rect.TopLeft(), bHorz ? m_szHorz : m_szVert);
	if ((bHorz ? _rect.left : _rect.top) != nAlign)
	{
		if (!bHorz)
			_rect.OffsetRect(0, nAlign - _rect.top - 2);
		else if (m_nDockBarID == AFX_IDW_DOCKBAR_TOP)
			_rect.OffsetRect(nAlign - _rect.left, -2);
		else
			_rect.OffsetRect(nAlign - _rect.left, 0);
		MoveWindow(_rect);
		bNeedRecalc = TRUE;
	}
	nAlign += (bHorz ? _rect.Width() : _rect.Height()) - 2;

	if (bNeedRecalc)
	{
		m_pDockSite->DelayRecalcLayout();
	}
}

void CSideControlBar::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
		return;

	ResizeGroup();
}

int CSideControlBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_bDragContent = FALSE;
	::SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &m_bDragContent, 0);

	CRect																				_rect(0,0,0,0);

	CreateGroup();

	_rect = m_pTabGroup1->GetInDrawScreenRect();
	CreateGroup_Tab1(_rect);
	m_pTabGroup1->SetTabView(1, m_pTreeViewDlg);
	m_pTabGroup1->SetTabFocus();

	_rect = m_pTabGroup2->GetInDrawScreenRect();
	CreateGroup_Tab2(_rect);
	m_pTabGroup2->SetTabView(1, m_pGroup1CompDlg);
// 	m_pTabGroup2->SetTabView(2, m_pGroup1MeasDlg);
	m_pTabGroup2->SetTabView(2, m_pGroup1ApplDlg);
	m_pTabGroup2->SetTabFocus();

	_rect = m_pTabGroup3->GetInDrawScreenRect();
	CreateGroup_Tab3(_rect);
	m_pTabGroup3->SetTabView(1, m_pGroup2DlInfoDlg);
	m_pTabGroup3->SetTabFocus();

	AdjustLayout();

	return 0;
}

void CSideControlBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	CRect rcClient = lpncsp->rgrc[0];
	rcClient.DeflateRect(5, 5);

	m_dwSCBSstyle &= ~SCBS_EDGEALL;
	switch (m_nDockBarID)
	{
	case AFX_IDW_DOCKBAR_TOP: {
		m_dwSCBSstyle |= SCBS_EDGEBOTTOM;
	};	break;
	case AFX_IDW_DOCKBAR_BOTTOM: {
		m_dwSCBSstyle |= SCBS_EDGETOP;
	};	break;
	case AFX_IDW_DOCKBAR_LEFT: {
		m_dwSCBSstyle |= SCBS_EDGERIGHT;
	};	break;
	case AFX_IDW_DOCKBAR_RIGHT: {
		m_dwSCBSstyle |= SCBS_EDGELEFT;
	};	break;
	default:					break;
	}
}

LRESULT CSideControlBar::OnNcHitTest(CPoint point)
{
	if (IsFloating())
		return CControlBar::OnNcHitTest(point);

	CRect				rectBar(0, 0, 0, 0), rectEdge(0, 0, 0, 0);
	GetWindowRect(rectBar);

	for (int i = 0; i < 4; i++)
	{
		if (GetEdgeRect(rectBar, GetEdgeCode(i), rectEdge))
			if (rectEdge.PtInRect(point))
				return GetEdgeCode(i);
	}

	return HTCLIENT;
}

void CSideControlBar::OnCaptureChanged(CWnd *pWnd)
{
	if (m_bTracking && (pWnd != this))
		StopTracking();

	CControlBar::OnCaptureChanged(pWnd);
}

void CSideControlBar::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CControlBar::OnSettingChange(uFlags, lpszSection);

	m_bDragContent = FALSE;
	::SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &m_bDragContent, 0);
}

void CSideControlBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	if (m_bTracking)
		StopTracking();

	CControlBar::OnLButtonUp(nFlags, point);
}

void CSideControlBar::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bTracking)
		OnTrackUpdateSize(point);

	CControlBar::OnMouseMove(nFlags, point);
}

void CSideControlBar::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (IsFloating())
	{
		CControlBar::OnNcLButtonDown(nHitTest, point);
		return;
	}

	if (m_bTracking)
		return;

	if ((nHitTest >= HTSIZEFIRST) && (nHitTest <= HTSIZELAST))
		StartTracking(nHitTest);
}

void CSideControlBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);
}

void CSideControlBar::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CSideControlBar::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_bTracking)
		StopTracking();

	CControlBar::OnRButtonDown(nFlags, point);
}

void CSideControlBar::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	if (nHitTest == HTCLOSE)
		m_pDockSite->ShowControlBar(this, FALSE, FALSE);

	CControlBar::OnNcLButtonUp(nHitTest, point);
}

void CSideControlBar::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	lpwndpos->flags |= SWP_FRAMECHANGED;
	CControlBar::OnWindowPosChanging(lpwndpos);

	UINT nOldDockBarID = m_nDockBarID;
	m_nDockBarID = GetParent()->GetDlgCtrlID();

	if (!IsFloating())
	{
		if (lpwndpos->flags & SWP_SHOWWINDOW)
		{
			m_bKeepSize = TRUE;
		}
	}
}

void CSideControlBar::OnPaint()
{
	CPaintDC dc(this);

	if (m_pDockBar)
	{
		CSCBDockBar*	pDockBar = (CSCBDockBar*)m_pDockBar;
		pDockBar->DrawBorder();
	}
}

void CSideControlBar::OnSize(UINT nType, int cx, int cy)
{
	CControlBar::OnSize(nType, cx, cy);
	AdjustLayout();
}

BOOL CSideControlBar::OnNcActivate(BOOL bActive)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return CControlBar::OnNcActivate(bActive);
}

HBRUSH CSideControlBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CControlBar::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

BOOL CSideControlBar::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, WND_BG_FRAME_COLOR);
	return TRUE;
}

void CSideControlBar::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CControlBar::OnMouseLeave();
}

BOOL CSideControlBar::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR			hdr;
	LPNMTREEVIEW	ntv;
	HTREEITEM		hItem;
	int				nObjID;

	hdr = (LPNMHDR)lParam;
	ntv = (LPNMTREEVIEW)lParam;

// 	if (hdr->hwndFrom == m_wndViewTree[m_nTreeViewMode].m_hWnd)
// 	{
// 		if (m_wndViewTree[m_nTreeViewMode].GetCount() == 0)
// 			return CControlBar::OnNotify(wParam, lParam, pResult);
// 
// 		TV_HITTESTINFO hit_info;
// 		GetCursorPos(&hit_info.pt);
// 		::ScreenToClient(m_wndViewTree[m_nTreeViewMode].m_hWnd, &hit_info.pt);
// 		hItem = m_wndViewTree[m_nTreeViewMode].HitTest(&hit_info);
// 
// 		if (hItem == NULL)
// 			return CControlBar::OnNotify(wParam, lParam, pResult);
// 
// 		nObjID = m_wndViewTree[m_nTreeViewMode].GetItemData(hItem);
// 
// 		if (hdr->code == NM_CLICK)
// 			TreeClickEvent(nObjID);
// 		else if (hdr->code == NM_DBLCLK)
// 		{
// 			TreeDBClickEvent(nObjID);
// 
// 			if (nObjID > 0)
// 				m_wndLogList.AddLogList(m_wndViewTree[m_nTreeViewMode].GetItemText(hItem), nObjID);
// 		}
// 		else if (hdr->code == NM_RCLICK)
// 			TreeRBClickEvent(nObjID);
// 	}

	return CControlBar::OnNotify(wParam, lParam, pResult);
}

CString CSideControlBar::GetModulePath()
{
	CString sPath;
	GetModuleFileName(AfxGetApp()->m_hInstance, sPath.GetBuffer(MAX_PATH), MAX_PATH);
	sPath.ReleaseBuffer();

	int nPos = sPath.ReverseFind(_T('\\'));
	if (nPos != -1)
		sPath = sPath.Left(nPos);

	return sPath;
}

void CSideControlBar::CreateGroup()
{
	BOOL																				bRet;
	CRect																				_rect(0, 0, 0, 0), _clientrect(0, 0, 0, 0);
	GetClientRect(&_clientrect);
	_clientrect.MoveToXY(0, 0);

	_rect.left = 0;
	_rect.top = 0;
	_rect.right = WND_WIDTH_FRAME_SIZE;
	_rect.bottom = WND_GROUP1_FRAME_SIZE;
	m_pTabGroup1 = new CPNOCtrl_Group;
	bRet = m_pTabGroup1->Create(_rect, this);
	m_pTabGroup1->SetSkinInit1();
	m_pTabGroup1->SetSkinOption();
	m_pTabGroup1->AddTabInfor((LPWSTR)(LPCTSTR)_T(""), NULL);
	m_pTabGroup1->ShowWindow(SW_SHOW);

	_rect.left = 0;
	_rect.top = 0;
	_rect.right = WND_WIDTH_FRAME_SIZE;
	_rect.bottom = WND_GROUP2_FRAME_SIZE;
	m_pTabGroup2 = new CPNOCtrl_Group;
	bRet = m_pTabGroup2->Create(_rect, this);
	m_pTabGroup2->SetSkinInit2();
	m_pTabGroup2->AddTabInfor((LPWSTR)(LPCTSTR)_T("설비정보"), NULL);
// 	m_pTabGroup2->AddTabInfor((LPWSTR)(LPCTSTR)_T("계측정보"), NULL);
	m_pTabGroup2->AddTabInfor((LPWSTR)(LPCTSTR)_T("계통해석"), NULL);
	m_pTabGroup2->ShowWindow(SW_SHOW);

	_rect.left = 0;
	_rect.top = 0;
	_rect.right = WND_WIDTH_FRAME_SIZE;
	_rect.bottom = WND_GROUP3_FRAME_SIZE;
	m_pTabGroup3 = new CPNOCtrl_Group;
	bRet = m_pTabGroup3->Create(_rect, this);
	m_pTabGroup3->SetSkinInit2();
	m_pTabGroup3->AddTabInfor((LPWSTR)(LPCTSTR)_T("D/L요약"), NULL);
	// 	m_pTabGroup3->AddTabInfor( (LPWSTR)(LPCTSTR)_T("전압Profile"), NULL );
	// 	m_pTabGroup3->AddTabInfor( (LPWSTR)(LPCTSTR)_T("부하패턴"), NULL );
	m_pTabGroup3->ShowWindow(SW_SHOW);
}

void CSideControlBar::CreateGroup_Tab1(CRect _drawrect)
{
	m_pTreeViewDlg = new CTreeViewDlg;
	m_pTreeViewDlg->Create(IDD_TREEVIEW_DLG, m_pTabGroup1);
	m_pTreeViewDlg->MoveWindow(_drawrect);
	m_pTreeViewDlg->ShowWindow(SW_HIDE);
}
void CSideControlBar::CreateGroup_Tab2(CRect _drawrect)
{
	m_pGroup1CompDlg = new CGroup1CompDlg;
	m_pGroup1CompDlg->Create(IDD_GROUP1_COMP_DLG, m_pTabGroup2);
	m_pGroup1CompDlg->MoveWindow(_drawrect);
	m_pGroup1CompDlg->ShowWindow(SW_HIDE);

// 	m_pGroup1MeasDlg = new CGroup1MeasDlg;
// 	m_pGroup1MeasDlg->Create(IDD_GROUP1_MEAS_DLG, m_pTabGroup2);
// 	m_pGroup1MeasDlg->MoveWindow(_drawrect);
// 	m_pGroup1MeasDlg->ShowWindow(SW_HIDE);

	m_pGroup1ApplDlg = new CGroup1ApplDlg;
	m_pGroup1ApplDlg->Create(IDD_GROUP1_APPL_DLG, m_pTabGroup2);
	m_pGroup1ApplDlg->MoveWindow(_drawrect);
	m_pGroup1ApplDlg->ShowWindow(SW_HIDE);
}

void CSideControlBar::CreateGroup_Tab3(CRect _drawrect)
{
	m_pGroup2DlInfoDlg = new CGroup2DlInfoDlg;
	m_pGroup2DlInfoDlg->Create(IDD_GROUP2_DLINFO_DLG, m_pTabGroup3);
	m_pGroup2DlInfoDlg->MoveWindow(_drawrect);
	m_pGroup2DlInfoDlg->ShowWindow(SW_HIDE);
}

void CSideControlBar::ResizeGroup()
{
	if (!m_pTabGroup1)																	return;
	if (!m_pTabGroup2)																	return;
	if (!m_pTabGroup3)																	return;

	CRect																				_rect(0, 0, 0, 0), _clientrect(0, 0, 0, 0), _grouprect(0, 0, 0, 0), rect(0, 0, 0, 0);
	GetClientRect(&_clientrect);

	_clientrect.MoveToXY(0, 0);
	_rect = _clientrect;

	if (m_pTabGroup1)
	{
		m_pTabGroup1->GetWindowRect(&_grouprect);

		rect = _rect;
		rect.bottom = rect.top + _grouprect.Height();
		m_pTabGroup1->MoveWindow(rect);
		ResizeGroup_Tab1();

		_rect.top = rect.bottom;
	}

	if (m_pTabGroup2)
	{
		m_pTabGroup2->GetWindowRect(&_grouprect);

		rect = _rect;
		rect.bottom = rect.top + _grouprect.Height();
		m_pTabGroup2->MoveWindow(rect);
		ResizeGroup_Tab2();

		_rect.top = rect.bottom;
	}

	if (m_pTabGroup3)
	{
		m_pTabGroup3->GetWindowRect(&_grouprect);

		rect = _rect;
		rect.bottom = _clientrect.bottom;
		m_pTabGroup3->MoveWindow(rect);
		ResizeGroup_Tab3();
	}
}

void CSideControlBar::ResizeGroup_Tab1()
{
	m_pTreeViewDlg->MoveWindow(m_pTabGroup1->GetInDrawScreenRect());
}

void CSideControlBar::ResizeGroup_Tab2()
{
	m_pGroup1CompDlg->MoveWindow(m_pTabGroup2->GetInDrawScreenRect());
// 	m_pGroup1MeasDlg->MoveWindow(m_pTabGroup2->GetInDrawScreenRect());
	m_pGroup1ApplDlg->MoveWindow(m_pTabGroup2->GetInDrawScreenRect());
}

void CSideControlBar::ResizeGroup_Tab3()
{
	m_pGroup2DlInfoDlg->MoveWindow(m_pTabGroup3->GetInDrawScreenRect());
}

void CSideControlBar::InitTreeView()
{
	if (m_pTreeViewDlg == NULL)														return;
	m_pTreeViewDlg->RemoveTreeItem();

	int																				nSubsId, nMtrIdx, nCbIdx;
	CString																			szSubsName, szMtrName, szDLName;
	HTREEITEM																		hSubs, hMtr, hDL;

	int																				nCount(theAppDataMng->GetTableRealCount("ss_sta"));

	for (int i = 1; i <= nCount; i++)
	{
		nSubsId = (int)GETVALUE(unsigned long long, _T("ss_sta"), _T("ss_substationid"), i);

// 		if (nSubsId == 0)															continue;

		szSubsName = GETSTRING(_T("ss_sta"), _T("ss_nm"), i);
		hSubs = m_pTreeViewDlg->InsertTreeItem(GROUP_OPTION_MODE1, szSubsName, TREE_IMAGE_ROOT, TREE_IMAGE_ROOT_SEL, NULL, TREE_ITEM_INSERT_SORT);

		nMtrIdx = GETVALUE(int, _T("ss_sta"), _T("ss_hi_mtr"), i);
		while (nMtrIdx)
		{
			szMtrName = GETSTRING(_T("mtr_sta"), _T("mtr_nm"), nMtrIdx);
			hMtr = m_pTreeViewDlg->InsertTreeItem(GROUP_OPTION_MODE1, szMtrName, TREE_IMAGE_CHILD, TREE_IMAGE_CHILD_SEL, hSubs, TREE_ITEM_INSERT_SORT);

			nCbIdx = GETVALUE(int, _T("mtr_sta"), _T("mtr_hi_dl"), nMtrIdx);
			while (nCbIdx)
			{
				szDLName = GETSTRING(_T("dl_sta"), _T("dl_nm"), nCbIdx);
				hDL = m_pTreeViewDlg->InsertTreeItem(GROUP_OPTION_MODE1, szDLName, TREE_IMAGE_CHILD, TREE_IMAGE_CHILD_SEL, hMtr, TREE_ITEM_INSERT_SORT, nCbIdx);
				nCbIdx = GETVALUE(int, _T("dl_sta"), _T("dl_si_mtr"), nCbIdx);
			}
			nMtrIdx = GETVALUE(int, _T("mtr_sta"), _T("mtr_si_ss"), nMtrIdx);
		}
	}

	hSubs = m_pTreeViewDlg->InsertTreeItem(GROUP_OPTION_MODE2, _T("선로목록"), TREE_IMAGE_ROOT, TREE_IMAGE_ROOT_SEL, NULL, TREE_ITEM_INSERT_LAST);
	nCount = theAppDataMng->GetTableRealCount("dl_sta");
	for (int i = 1; i <= nCount; i++)
	{
		szDLName = GETSTRING(_T("dl_sta"), _T("dl_nm"), i);
		hDL = m_pTreeViewDlg->InsertTreeItem(GROUP_OPTION_MODE2, szDLName, TREE_IMAGE_CHILD, TREE_IMAGE_CHILD_SEL, hSubs, TREE_ITEM_INSERT_SORT, i);
	}
}

LRESULT CSideControlBar::OnSideControlBarMsg(WPARAM wparam, LPARAM lparam)
{
	if ((int)wparam == 1)//그룹1 메시지
	{
		int																				nTreeMode;
		nTreeMode = (int)lparam;

		m_pTreeViewDlg->ShowTree(nTreeMode);
	}
	return FALSE;
}

void CSideControlBar::SetGroup1CompData(CNodeView* pNodeView, int nDLIdx)
{
	if (m_pGroup1CompDlg == NULL)														return;
 	m_pGroup1CompDlg->SetData(pNodeView, nDLIdx);
}

void CSideControlBar::SetGroup1MeasData(int nCompType, int nCompIdx)
{
	if (m_pGroup1MeasDlg == NULL)														return;
 	m_pGroup1MeasDlg->SetData(nCompType, nCompIdx);
}

void CSideControlBar::SetGroup1ApplData(int nCompType, int nCompIdx)
{
	if (m_pGroup1ApplDlg == NULL)														return;
 	m_pGroup1ApplDlg->SetData(nCompType, nCompIdx);
}

void CSideControlBar::ShowDLInfo(int nDLIdx)
{
	if (nDLIdx <= 0)
	{
		CString																			szData;
		m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_LOAD_VAL, _T(""));
		m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_LOAD_VAL2, _T(""));
		m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_MW_VAL, _T(""));
		m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_LOSS_VAL, _T(""));
		m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_VOLT_VAL, _T(""));
		m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_VOLT_VAL2, _T(""));
		return;
	}

	int																				nBS(0), nSBS(0), nEBS(0);
	double																			dMaxVolt(0), dMinVolt(0), dValue(0);

	//////////////////////////////////////////////////////////////////////////
	//SBS찾기
	int																				nCbswIdx(0), nGNDIdx;
	int																				nSwIdx = 0;
	int																				nCount(theAppDataMng->GetTableRealCount(_T("cbsw_sta")));
	for (int nPos = 1; nPos <= nCount; nPos++)
	{
		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nPos) != 1)			continue;//CB가 아니면 패스...
		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), nPos) == nDLIdx)
		{
			nCbswIdx = nPos;
			break;
		}
	}

	if (nCbswIdx != 0)
	{
		nGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tgnd"), nCbswIdx);
		if (nGNDIdx != 0)
		{
			nSBS = GETVALUE(int, _T("gnd_dyn_ncpo"), _T("gnd_ii_bs"), nGNDIdx);
		}
	}
	//////////////////////////////////////////////////////////////////////////

	nBS = GETVALUE(int, _T("dl_dyn_ncpo"), _T("dl_hi_bs"), nDLIdx);
	while (nBS)
	{
		dValue = GETVALUE(double, _T("bs_dyn_rpfo"), _T("bs_parpfpukv"), nBS);
		if (dValue > dMaxVolt)
		{
			dMaxVolt = dValue;
		}
		if ((dValue < dMinVolt) || (dMinVolt == 0))
		{
			dMinVolt = dValue;
			nEBS = nBS;
		}
		nBS = GETVALUE(int, _T("bs_dyn_ncpo"), _T("bs_si_dl"), nBS);
	}
	CString																			szData;
	szData.Format(_T("%.3lf [MW]"), GETVALUE(double, _T("dl_dyn_rpfo"), _T("dl_3pldrpfmw"), nDLIdx));
	m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_LOAD_VAL, szData);

	szData.Format(_T("%.3lf [MVar]"), GETVALUE(double, _T("dl_dyn_rpfo"), _T("dl_3pldrpfmvar"), nDLIdx));
	m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_LOAD_VAL2, szData);

	szData.Format(_T("%.3lf [MW]"), GETVALUE(double, _T("dl_dyn_rpfo"), _T("dl_3pgenrpfmw"), nDLIdx));
	m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_MW_VAL, szData);

	szData.Format(_T("%.3lf [MW]"), GETVALUE(double, _T("dl_dyn_rpfo"), _T("dl_3plsrpfmw"), nDLIdx));
	m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_LOSS_VAL, szData);

	szData.Format(_T("(최대) %.3lf [p.u]"), dMaxVolt);
	m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_VOLT_VAL, szData);

	szData.Format(_T("(최소) %.3lf [p.u]"), dMinVolt);
	m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_VOLT_VAL2, szData);

	int nIjIdx, nijEquty, nDgIdx;
	double dSumGenCapa(0);
	nIjIdx = GETVALUE(int, _T("dl_sta"), _T("dl_hi_ij"), nDLIdx);
	while (nIjIdx)
	{
		if (GETVALUE(int, _T("ij_sta"), _T("ij_ii_equty"), nIjIdx) == 4)//GEN
		{
			nDgIdx = GETVALUE(int, _T("ij_sta"), _T("ij_ii_equ"), nIjIdx);
			if(GETVALUE(int, _T("gen_sta"), _T("gen_trexcl"), nDgIdx) != 3)//저압공용이 아닐때만 누적
				dSumGenCapa += GETVALUE(double, _T("gen_sta"), _T("gen_mwlmmx"), nDgIdx);
			else
			{
				int a;
				a = 1;
			}
		}

		nIjIdx = GETVALUE(int, _T("ij_sta"), _T("ij_si_dl"), nIjIdx);
	}

	szData.Format(_T("%.3lf [MW]"), dSumGenCapa);
	m_pGroup2DlInfoDlg->SetDlgItemText(IDC_GROUP2_1_STC_GEN_CAPA_VAL, szData);

}