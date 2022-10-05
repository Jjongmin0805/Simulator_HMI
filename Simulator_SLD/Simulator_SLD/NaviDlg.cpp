// NaviDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "NaviDlg.h"
#include "afxdialogex.h"


// CNaviDlg 대화 상자

IMPLEMENT_DYNAMIC(CNaviDlg, CDialog)

CNaviDlg::CNaviDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_NAVI_DLG, pParent)
{
	m_bShowNavi = TRUE;
	m_bLButtonDown = FALSE;

	m_nViewMode = 0;

	m_dpCenter = NULL;
	m_pMap = NULL;

	ResetData();
}

CNaviDlg::~CNaviDlg()
{
	delete m_pMap;
}

void CNaviDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNaviDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CNaviDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNaviDlg::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


// CNaviDlg 메시지 처리기
BOOL CNaviDlg::Create(CWnd* pParent)
{
	m_pParentWnd = pParent;
	return CDialog::Create(IDD_NAVI_DLG, pParent);
}
void CNaviDlg::ResetData()
{
	m_dSLDRatioX = 1;
	m_dSLDRatioY = 1;

	m_rectView = CRect(0, 0, 0, 0);
	m_pNodeView = NULL;
	m_pBranchView = NULL;
}

BOOL CNaviDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	LoadIcons();

	CFile file;
	CString szPath;
	szPath.Format(_T("%s\\BaseMap\\areamap.mbb"), GetModulePath());
	if (!file.Open(szPath, CFile::modeRead)) return FALSE;
	m_pMap = new CIdxMap();
	CArchive ar(&file, CArchive::load);
	m_pMap->Serialize(ar);
	ar.Close();
	file.Close();

	return TRUE;
}

void CNaviDlg::LoadIcons(void)
{
	int																		i(0), j(0);
	CString																	sModulePath(_T(""));
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			m_Icons[i][j] = NULL;
			ZeroMemory(&(m_IconsInfor[i][j]), sizeof(BITMAP));

			CString															sModulePath(_T(""));
			if (j == 0)														sModulePath.Format(_T("%s\\Skin\\SLD\\Navigator\\%d_On.pnoimg"), GetModulePath(), i + 1);
			else if (j == 1)												sModulePath.Format(_T("%s\\Skin\\SLD\\Navigator\\%d_Down.pnoimg"), GetModulePath(), i + 1);
			else if (j == 2)												sModulePath.Format(_T("%s\\Skin\\SLD\\Navigator\\%d_Over.pnoimg"), GetModulePath(), i + 1);

			if (_waccess(sModulePath, 06) == -1)							continue;

			m_Icons[i][j] = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
			::GetObject(m_Icons[i][j], sizeof(BITMAP), &(m_IconsInfor[i][j]));
		}
	}

	InitIcons();
}

void CNaviDlg::DrawIcons(CDC* pDC)
{
	if (m_CtrlIcons.m_hCtrlIcon == NULL)
		return;

	int																		i(0);
	CRect																	_rect(0, 0, 0, 0);
	GetWindowRect(&_rect);
	ScreenToClient(_rect);

	CDC																		tmpDC;
	tmpDC.CreateCompatibleDC(pDC);

	CBitmap																	bmpBuffer, *pOldBitmap = NULL;
	bmpBuffer.CreateCompatibleBitmap(pDC, m_CtrlIcons.m_rect.Width(), m_CtrlIcons.m_rect.Height());
	pOldBitmap = (CBitmap *)pDC->SelectObject(&bmpBuffer);

	HGDIOBJ																	hgdiobj = NULL;
	hgdiobj = tmpDC.SelectObject(m_CtrlIcons.m_hCtrlIcon);

	pDC->BitBlt(m_CtrlIcons.m_rect.left, m_CtrlIcons.m_rect.top, m_CtrlIcons.m_rect.Width(), m_CtrlIcons.m_rect.Height(), &tmpDC, 0, 0, SRCCOPY);

	tmpDC.SelectObject(hgdiobj);
	tmpDC.DeleteDC();
}

void CNaviDlg::InitIcons(void)
{
	CRect																	TextMenuRect(0, 0, 0, 0);
	m_CtrlIcons.m_hCtrlIcon = m_Icons[m_bShowNavi][0];

	TextMenuRect.left = 0;
	TextMenuRect.top = 0;
	TextMenuRect.right = TextMenuRect.left + m_IconsInfor[m_bShowNavi][0].bmWidth;
	TextMenuRect.bottom = TextMenuRect.top + m_IconsInfor[m_bShowNavi][0].bmHeight;

	m_CtrlIcons.m_rect = TextMenuRect;

	CClientDC																dc(this);
	DrawIcons(&dc);
}

CString CNaviDlg::GetModulePath()
{
	CString																	sPath;
	GetModuleFileName(AfxGetApp()->m_hInstance, sPath.GetBuffer(MAX_PATH), MAX_PATH);
	sPath.ReleaseBuffer();

	int																		nPos;
	nPos = sPath.ReverseFind(_T('\\'));

	if (nPos > -1)
		sPath = sPath.Left(nPos);

	return sPath;
}

void CNaviDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect																	_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	CSize																	size;
	size.cx = _rect.Width();
	size.cy = _rect.Height();

	CDC																		memDC;
	CBitmap																	memBmp, *pOldBmp;
	memBmp.DeleteObject();
	memBmp.CreateCompatibleBitmap(&dc, size.cx, size.cy);
	memDC.CreateCompatibleDC(&dc);

	pOldBmp = memDC.SelectObject(&memBmp);
	memDC.FillSolidRect(0, 0, size.cx, size.cy, RGB(32, 42, 62));


	if (m_nViewMode == 0)
	{
		//Navi계통 그리기
		CPen																	Pen, *pOldPen;
		CBrush																	brush, *pOldbrush;
		Pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		pOldPen = (CPen*)memDC.SelectObject(&Pen);
		brush.CreateSolidBrush(RGB(255, 255, 0));
		pOldbrush = (CBrush*)memDC.SelectObject(&brush);

		if (m_pBranchView != NULL)												m_pBranchView->DrawNavi(&memDC, m_dSLDRatioX, m_dSLDRatioY);
		if (m_pNodeView != NULL)												m_pNodeView->DrawNavi(&memDC, m_dSLDRatioX, m_dSLDRatioY);

		memDC.SelectObject(pOldPen);
		Pen.DeleteObject();
		memDC.SelectObject(pOldbrush);
		brush.DeleteObject();
		//////////////////////////////////////////////////////////////////////////

		//배경그리기
		Graphics																graphics(memDC);
		Gdiplus::Region															_gdiTotRect(Gdiplus::Rect(0, 0, size.cx, size.cy)), _gdiSelRect(Gdiplus::Rect(m_rectView.left, m_rectView.top, m_rectView.Width(), m_rectView.Height()));

		Gdiplus::SolidBrush	_gdibrush(Gdiplus::Color(230, 21, 29, 43));
		_gdiTotRect.Xor(&_gdiSelRect);

		graphics.FillRegion(&_gdibrush, &_gdiTotRect);
		//////////////////////////////////////////////////////////////////////////
	}
	else
	{
		if (m_pMap && m_dpCenter)
		{
			m_pMap->DrawNavi(&memDC, _rect);

			CPoint ptCen = m_rectScreen.CenterPoint();
			CDPoint dpLT, dpRB;

			dpLT.dx = ((-ptCen.x - 0.5) / m_dScrZoom + m_dpCenter->dx);
			dpLT.dy = (m_dpCenter->dy - (-ptCen.y - 0.5) / m_dScrZoom);
			dpRB.dx = ((m_rectScreen.Width() - ptCen.x - 0.5) / m_dScrZoom + m_dpCenter->dx);
			dpRB.dy = (m_dpCenter->dy - (m_rectScreen.Height() - ptCen.y - 0.5) / m_dScrZoom);

			m_pMap->DrawNaviRect(&memDC, _rect, &dpLT, &dpRB);
// 			CRect rectNavi;
// 			rectNavi = m_pMap->GetNaviRect(_rect, &dpLT, &dpRB);
// 
// 			//배경그리기
// 			Graphics																graphics(memDC);
// 			Gdiplus::Region															_gdiTotRect(Gdiplus::Rect(0, 0, size.cx, size.cy)), _gdiSelRect(Gdiplus::Rect(rectNavi.left, rectNavi.top, rectNavi.Width(), rectNavi.Height()));
// 
// 			Gdiplus::SolidBrush	_gdibrush(Gdiplus::Color(230, 21, 29, 43));
// 			_gdiTotRect.Xor(&_gdiSelRect);
// 
// 			graphics.FillRegion(&_gdibrush, &_gdiTotRect);
		}
	}

	dc.BitBlt(0, 0, size.cx, size.cy, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();

	DrawIcons(&dc);
}

void CNaviDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLButtonDown = FALSE;

	if (m_CtrlIcons.m_rect.PtInRect(point))//버튼을 누르면
	{
		CClientDC															dc(this);
		m_CtrlIcons.m_hCtrlIcon = m_Icons[m_bShowNavi][1];
		DrawIcons(&dc);

		m_bLButtonDown = TRUE;

		SetCapture();
		return;
	}
	else//영역을 선택하면
	{
		if (m_nViewMode == 0)
		{
			CPoint																ptOffset;
			ptOffset.x = int((point.x - m_rectView.CenterPoint().x) / m_dSLDRatioX) * (-1);
			ptOffset.y = int((point.y - m_rectView.CenterPoint().y) / m_dSLDRatioY) * (-1);

			m_pParentWnd->SendMessage(WM_NAVIGATOR_MSG, (WPARAM)0, (LPARAM)&ptOffset);
		}
		else
		{
			CRect																_rect(0, 0, 0, 0);
			GetClientRect(&_rect);
			CDPoint* pDP;
			pDP = m_pMap->NaviLBtnDown(_rect, point);
			m_pParentWnd->SendMessage(WM_NAVIGATOR_MSG, (WPARAM)1, (LPARAM)pDP);
			delete pDP;
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CNaviDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bLButtonDown)													return CDialog::OnMouseMove(nFlags, point);

	if (m_CtrlIcons.m_rect.PtInRect(point))								m_CtrlIcons.m_hCtrlIcon = m_Icons[m_bShowNavi][2];
	else																m_CtrlIcons.m_hCtrlIcon = m_Icons[m_bShowNavi][0];


	CClientDC																dc(this);
	DrawIcons(&dc);

	TRACKMOUSEEVENT															tagMouseE;
	tagMouseE.cbSize = sizeof(TRACKMOUSEEVENT);
	tagMouseE.dwFlags = TME_HOVER | TME_LEAVE;
	tagMouseE.hwndTrack = m_hWnd;
	TrackMouseEvent(&tagMouseE);

	CDialog::OnMouseMove(nFlags, point);
}

void CNaviDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	m_bLButtonDown = FALSE;

	if (m_CtrlIcons.m_rect.PtInRect(point))
	{
		ShowNavi(!m_bShowNavi);
	}
	else
	{
		CClientDC															dc(this);
		m_CtrlIcons.m_hCtrlIcon = m_Icons[m_bShowNavi][0];
		DrawIcons(&dc);
	}

	CDialog::OnLButtonUp(nFlags, point);
}

CSize CNaviDlg::GetWindowSize()
{
	CSize																	sizeWnd(0, 0);
	if (m_bShowNavi)
	{
		sizeWnd.cx = DEFAULT_NAVIGATOR_SIZEX;
		sizeWnd.cy = DEFAULT_NAVIGATOR_SIZEY;
	}
	else
	{
		sizeWnd.cx = m_CtrlIcons.m_rect.Width();
		sizeWnd.cy = m_CtrlIcons.m_rect.Height();
	}

	return sizeWnd;
}

void CNaviDlg::OnBnClickedOk()
{
}

void CNaviDlg::OnBnClickedCancel()
{
}

BOOL CNaviDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CNaviDlg::OnMouseLeave()
{
	CClientDC																dc(this);
	m_CtrlIcons.m_hCtrlIcon = m_Icons[m_bShowNavi][0];
	DrawIcons(&dc);

	CDialog::OnMouseLeave();
}

void CNaviDlg::SetNaviSLDRatio(int nSDLSizeX, int nSLDSizeY)
{
	m_dSLDRatioX = (double)DEFAULT_NAVIGATOR_SIZEX / nSDLSizeX;
	m_dSLDRatioY = (double)DEFAULT_NAVIGATOR_SIZEY / nSLDSizeY;
}

void CNaviDlg::SetNaviRatio(CRect rectView)
{
	m_rectView.left = rectView.left * m_dSLDRatioX;
	m_rectView.top = rectView.top * m_dSLDRatioY;
	m_rectView.right = rectView.right * m_dSLDRatioX;
	m_rectView.bottom = rectView.bottom * m_dSLDRatioY;
}

void CNaviDlg::UpData(CNodeView* pNodeView, CBranchView* pBranchView)
{
	m_pNodeView = pNodeView;
	m_pBranchView = pBranchView;

	Invalidate();
}

void CNaviDlg::ShowNavi(BOOL bShow)
{
	m_bShowNavi = bShow;

	CClientDC																dc(this);
	m_CtrlIcons.m_hCtrlIcon = m_Icons[m_bShowNavi][2];
	DrawIcons(&dc);

	CSize																	sizeWnd;
	sizeWnd = GetWindowSize();

	CRect																	rectWnd;
	GetWindowRect(&rectWnd);

	MoveWindow(rectWnd.left, rectWnd.top, sizeWnd.cx, sizeWnd.cy);
}

void CNaviDlg::SetGISRectNavi(CRect rect, double dZoom, CDPoint* pCen)
{
	m_rectScreen = rect;
	m_dScrZoom = dZoom;
	m_dpCenter = pCen;
	Invalidate();
}
