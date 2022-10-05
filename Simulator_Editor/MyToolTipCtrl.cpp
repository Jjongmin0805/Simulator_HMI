// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "pch.h"
#include "MyToolTipCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyToolTipCtrl

IMPLEMENT_DYNCREATE(CMyToolTipCtrl, CToolTipCtrl)

CMyToolTipCtrl::CMyToolTipCtrl()
{
	m_sizeImage				= CSize(0, 0);
	m_ptMargin				= CPoint(0, 0);
	m_ptLocation			= CPoint(-1, -1);
	m_nFixedWidthRegular	= 0;
	m_nFixedWidthWithImage	= 0;

	m_pFontLabelNormal.CreateFont(18,0,0,0,FW_NORMAL,FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, _T("맑은 고딕"));
	m_pFontLabelBold.CreateFont(18,0,0,0,FW_BOLD,FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, _T("맑은 고딕"));

	m_pFontDescNormal.CreateFont(15,0,0,0,FW_NORMAL,FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, _T("맑은 고딕"));
	m_pFontDescBold.CreateFont(15,0,0,0,FW_BOLD,FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, _T("맑은 고딕"));
}

CMyToolTipCtrl::~CMyToolTipCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyToolTipCtrl, CToolTipCtrl)
	//{{AFX_MSG_MAP(CMyToolTipCtrl)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyToolTipCtrl message handlers
int CMyToolTipCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CToolTipCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Override default parameters:
	m_hIcon = NULL;

	return 0;
}

void CMyToolTipCtrl::AddIcon(UINT nID)
{
	m_hIcon = (HICON) ::LoadImage (
		AfxGetResourceHandle (),
		MAKEINTRESOURCE (nID),
		IMAGE_ICON,
		afxGlobalData.m_sizeSmallIcon.cx,
		afxGlobalData.m_sizeSmallIcon.cy,
		LR_SHARED);

}

CSize CMyToolTipCtrl::GetIconSize ()
{
	if( !(m_hIcon && m_Params.m_bDrawIcon) )
		return CSize(0, 0);

	return afxGlobalData.m_sizeSmallIcon;
}

void CMyToolTipCtrl::SetFixedWidth(int nWidthRegular, int nWidthLargeImage)
{
	m_nFixedWidthRegular = nWidthRegular;
	m_nFixedWidthWithImage = nWidthLargeImage;
}

void CMyToolTipCtrl::SetParams(CMFCToolTipInfo* pParams)
{
	ASSERT_VALID(this);

	if (pParams == NULL)
	{
		CMFCToolTipInfo paramsDefault;
		m_Params = paramsDefault;
	}
	else
	{
		m_Params = *pParams;
	}
}

void CMyToolTipCtrl::SetDescription (const CString strDesrciption)
{
	m_strDescription.Format ( strDesrciption );
}

void CMyToolTipCtrl::SetLocation(CPoint pt)
{
	ASSERT_VALID(this);
	m_ptLocation = pt;
}

void CMyToolTipCtrl::OnFillBackground (CDC* pDC, CRect rect, COLORREF& /*clrFill*/, COLORREF& /*clrFillGradient*/)
{
	ASSERT_VALID (pDC);

	CDrawingManager dm (*pDC);

	dm.FillGradient2(rect, m_Params.m_clrFill, m_Params.m_clrFillGradient, m_Params.m_nGradientAngle == -1 ? 45 : m_Params.m_nGradientAngle);
}

void CMyToolTipCtrl::OnPaint()
{
	CPaintDC dcPaint(this); // device context for painting

	CMemDC memDC (dcPaint, this);
	CDC* pDC = &memDC.GetDC ();


	CRect		rect;

	GetClientRect( rect );
	CRect rectMargin;
	GetMargin(rectMargin);

	CRect rectText = rect;

	rectText.DeflateRect(rectMargin);
	rectText.DeflateRect(m_ptMargin.x, m_ptMargin.y);

	// Fill background:
	OnFillBackground(pDC, rect, m_Params.m_clrFill, m_Params.m_clrFillGradient);

	CPen penLine(PS_SOLID, 1, m_Params.m_clrBorder);
	CPen* pOldPen = pDC->SelectObject(&penLine);

	// Draw border:
	OnDrawBorder(pDC, rect, m_Params.m_clrBorder);

	// Draw icon:
	if (m_sizeImage != CSize(0, 0) && m_Params.m_bDrawIcon)
	{
		CRect rectImage = rectText;
		rectImage.right = rectImage.left + m_sizeImage.cx;
		rectImage.bottom = rectImage.top + m_sizeImage.cy;

		OnDrawIcon(pDC, rectImage);

		rectText.left += m_sizeImage.cx + m_ptMargin.x;
	}

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_Params.m_clrText);

	// Draw label:
	int nTextHeight = OnDrawLabel(pDC, rectText, FALSE).cy;

	// Draw separator + description:
	if (!m_strDescription.IsEmpty() && m_Params.m_bDrawDescription)
	{
		CRect rectDescr = rectText;
		rectDescr.top += nTextHeight + 3 * m_ptMargin.y / 2;

		if (m_Params.m_bDrawSeparator)
		{
			OnDrawSeparator(pDC, rectDescr.left, rectDescr.right, rectDescr.top - m_ptMargin.y / 2);
		}

		OnDrawDescription(pDC, rectDescr, FALSE);
	}

	pDC->SelectObject(pOldPen);
}

void CMyToolTipCtrl::OnDrawBorder(CDC* pDC, CRect rect, COLORREF clrLine)
{
	ASSERT_VALID(pDC);

	if (!m_Params.m_bRoundedCorners)
	{
		pDC->Draw3dRect(rect, clrLine, clrLine);
		return;
	}

	const int nOffset = 2;

	pDC->MoveTo(rect.left + nOffset, rect.top);
	pDC->LineTo(rect.right - nOffset - 1, rect.top);

	pDC->LineTo(rect.right - 1, rect.top + nOffset);
	pDC->LineTo(rect.right - 1, rect.bottom - 1 - nOffset);

	pDC->LineTo(rect.right - nOffset - 1, rect.bottom - 1);
	pDC->LineTo(rect.left + nOffset, rect.bottom - 1);

	pDC->LineTo(rect.left, rect.bottom - 1 - nOffset);
	pDC->LineTo(rect.left, rect.top + nOffset);

	pDC->LineTo(rect.left + nOffset, rect.top);
}

BOOL CMyToolTipCtrl::OnDrawIcon (CDC* pDC, CRect rectImage)
{
	::DrawIconEx (pDC->GetSafeHdc (), rectImage.left, rectImage.top, m_hIcon, 0, 0, 0, NULL, DI_NORMAL);

	return TRUE;
}

CSize CMyToolTipCtrl::OnDrawLabel(CDC* pDC, CRect rect, BOOL bCalcOnly)
{
	ASSERT_VALID(pDC);

	CSize sizeText(0, 0);

	CString strText;
	GetWindowText(strText);

	strText.Replace(_T("\t"), _T("    "));

	BOOL bDrawDescr = m_Params.m_bDrawDescription && !m_strDescription.IsEmpty();

// 	CFont* pOldFont = (CFont*) pDC->SelectObject(m_Params.m_bBoldLabel && bDrawDescr ? &afxGlobalData.fontBold : &afxGlobalData.fontTooltip);
	CFont* pOldFont;
	if( m_Params.m_bBoldLabel )
		pOldFont = (CFont*) pDC->SelectObject(&m_pFontLabelBold);
	else
		pOldFont = (CFont*) pDC->SelectObject(&m_pFontLabelNormal);

	if (strText.Find(_T('\n')) >= 0) // Multi-line text
	{
		UINT nFormat = DT_NOPREFIX;
		if (bCalcOnly)
		{
			nFormat |= DT_CALCRECT;
		}

		int nHeight = pDC->DrawText(strText, rect, nFormat);
		sizeText = CSize(rect.Width(), nHeight);
	}
	else
	{
		if (bCalcOnly)
		{
			sizeText = pDC->GetTextExtent(strText);
		}
		else
		{
			UINT nFormat = DT_LEFT | DT_NOCLIP | DT_SINGLELINE;

			if (!bDrawDescr)
			{
				nFormat |= DT_VCENTER;
			}

			sizeText.cy = pDC->DrawText(strText, rect, nFormat);
			sizeText.cx = rect.Width();
		}
	}

	pDC->SelectObject(pOldFont);

	return sizeText;
}

CSize CMyToolTipCtrl::OnDrawDescription(CDC* pDC, CRect rect, BOOL bCalcOnly)
{
	ASSERT_VALID(pDC);

	CSize sizeText(0, 0);

	if (!m_Params.m_bDrawDescription)
	{
		return sizeText;
	}

// 	CFont* pOldFont = pDC->SelectObject(&afxGlobalData.fontTooltip);
	CFont* pOldFont;
// 	if( m_Params.m_bBoldLabel )
// 		pOldFont = (CFont*) pDC->SelectObject(&m_pFontDescBold);
// 	else
		pOldFont = (CFont*) pDC->SelectObject(&m_pFontDescNormal);

	int nFixedWidth = GetFixedWidth ();

	if (nFixedWidth > 0 && m_sizeImage.cx <= 32)
	{
		rect.right = rect.left + nFixedWidth;

		if (m_sizeImage.cx > 0 && m_Params.m_bDrawIcon)
		{
			rect.right -= m_sizeImage.cx + m_ptMargin.x;
		}
	}
	else
	{
		rect.right = rect.left + m_Params.m_nMaxDescrWidth;
	}

	UINT nFormat = DT_WORDBREAK;
	if (bCalcOnly)
	{
		nFormat |= DT_CALCRECT;
	}

	int nDescrHeight = 0;
	nDescrHeight = pDC->DrawText(m_strDescription, rect, nFormat);
	pDC->SelectObject(pOldFont);

	return CSize(rect.Width(), nDescrHeight);
}

void CMyToolTipCtrl::OnDrawSeparator (CDC* pDC, int x1, int x2, int y)
{
	ASSERT_VALID (pDC);

	CDrawingManager dm (*pDC);
	CRect rect (x1, y, x2, y + 1);

	dm.FillGradient (rect, 
		RGB (111, 133, 181), RGB ( 65, 85, 125), FALSE);
}

int CMyToolTipCtrl::GetFixedWidth()
{
	ASSERT_VALID(this);

	if (m_sizeImage.cx <= (int)(afxGlobalData.GetRibbonImageScale() * 32))
	{
		return m_nFixedWidthRegular;
	}
	else
	{
		return m_nFixedWidthWithImage;
	}
}

void CMyToolTipCtrl::SetLayout()
{
	int nResult = 0;

	CPoint ptCursor;
	::GetCursorPos(&ptCursor);

	m_sizeImage = m_Params.m_bDrawIcon ? GetIconSize() : CSize(0, 0);
	m_ptMargin = m_Params.m_bRoundedCorners ? CPoint(6, 4) : CPoint(4, 2);

	CRect rectMargin;
	GetMargin(rectMargin);

	CRect rectText;
	GetClientRect(rectText);

	CClientDC dc(this);
	CSize sizeText = OnDrawLabel(&dc, rectText, TRUE);

	int cx = sizeText.cx;
	int cy = sizeText.cy;

	CSize sizeDescr(0, 0);

	if (!m_Params.m_bDrawDescription || m_strDescription.IsEmpty())
	{
		cy = max(cy, m_sizeImage.cy);
	}
	else
	{
		sizeDescr = OnDrawDescription(&dc, rectText, TRUE);

		cy += sizeDescr.cy + 2 * m_ptMargin.y;
		cx = max(cx, sizeDescr.cx);
		cy = max(cy, m_sizeImage.cy);
	}

	if (m_sizeImage.cx > 0 && m_Params.m_bDrawIcon)
	{
		cx += m_sizeImage.cx + m_ptMargin.x;
	}

	cx += 2 * m_ptMargin.x;
	cy += 2 * m_ptMargin.y;

	const int nFixedWidth = GetFixedWidth();
	if (nFixedWidth > 0 && sizeDescr != CSize(0, 0))
	{
		cx = max(cx, nFixedWidth);
	}

	CRect rectWindow;
	GetWindowRect(rectWindow);

	int x = rectWindow.left;
	int y = rectWindow.top;

	if (m_ptLocation != CPoint(-1, -1))
	{
		x = m_ptLocation.x;
		y = m_ptLocation.y;

		nResult = 1;
	}

	CRect rectScreen;

	MONITORINFO mi;
	mi.cbSize = sizeof(MONITORINFO);
	if (GetMonitorInfo(MonitorFromPoint(rectWindow.TopLeft(), MONITOR_DEFAULTTONEAREST), &mi))
	{
		rectScreen = mi.rcWork;
	}
	else
	{
		::SystemParametersInfo(SPI_GETWORKAREA, 0, &rectScreen, 0);
	}

	int nBottom = max(ptCursor.y + cy + ::GetSystemMetrics(SM_CYCURSOR), y + cy + 2);
	if (nBottom > rectScreen.bottom)
	{
		y = ptCursor.y - cy - 1;
		nResult = 1;
	}

	if (x + cx + 2 > rectScreen.right)
	{
		if (nResult == 1) // Y has been changed
		{
			x = ptCursor.x - cx - 1;
		}
		else
		{
			x = rectScreen.right - cx - 1;
			nResult = 1;
		}
	}

	if (nResult == 1)
	{
		SetWindowPos(NULL, x, y, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
	}
	else
	{
		SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	if (m_Params.m_bRoundedCorners)
	{
		CRgn rgn;
		rgn.CreateRoundRectRgn(0, 0, cx + 1, cy + 1, 4, 4);

		SetWindowRgn(rgn, FALSE);
	}
}

void CMyToolTipCtrl::Clear()
{
	m_strDescription.Empty();
	m_ptLocation = CPoint(-1, -1);
}

void CMyToolTipCtrl::Show()
{
	Activate( TRUE );
}

void CMyToolTipCtrl::Hide()
{
	Activate( FALSE );
}

BOOL CMyToolTipCtrl::OnEraseBkgnd(CDC* pDC)
{
	SetLayout();
	CRect rect;
	GetClientRect (rect);

	COLORREF clrDummy;
	OnFillBackground (pDC, rect, clrDummy, clrDummy);

	return TRUE;
}

BOOL CMyToolTipCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CToolTipCtrl::OnNotify(wParam, lParam, pResult);
}


BOOL CMyToolTipCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CToolTipCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}