#include "pch.h"
#include "CView_History.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"

CView_History::CView_History()
{


	m_headerfont.DeleteObject();
	m_listfont.DeleteObject();

}

CView_History::~CView_History()
{
	m_headerfont.DeleteObject();
	m_listfont.DeleteObject();
}

void CView_History::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	Create_ListCtrl();
}


void CView_History::InitData()
{

}

BEGIN_MESSAGE_MAP(CView_History, CView_Base)
ON_WM_SIZE()
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CView_History::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);



	ListCtrl_MoveSize();
}


void CView_History::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);

	OnPrepareDC(&dc);
	Graphics						graphics(dc.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();
	//////////////////////////////////////////////////////////////////////
	pViewMng->DrawArea_List(&dc, graphics, m_rectList);

	pViewMng->DrawArea_Title(&dc, graphics, m_rectListTitle, _T("알람 및 이벤트 현황"));
	
}

BOOL CView_History::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);


	CBrush brushBG(RGB(210, 221, 212));
	pDC->FillRect(rect, &brushBG);


	return TRUE;

	return CView_Base::OnEraseBkgnd(pDC);
}

void CView_History::Create_ListCtrl()
{
	m_headerfont.CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect[2];
	rect[0] = CRect(10, 50, 350, 500);
	m_ctrList.Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_HISTORY_LIST_1);
	m_ctrList.InsertColumn(0, _T("Time"), HDF_LEFT, 163);
	m_ctrList.InsertColumn(1, _T("Message"), HDF_LEFT, 1727);
	m_ctrList.InsertColumn(2, _T("Message"), HDF_LEFT, 0);
	m_ctrList.ShowWindow(SW_SHOW);
	m_ctrList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList.m_HeaderCtrl.SetHeight(27);
	m_ctrList.m_HeaderCtrl.SetFlat();
	m_ctrList.m_HeaderCtrl.SetFlat();
	m_ctrList.m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList.m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList.m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList.SetBgColor(RGB(255, 255, 255));
	m_ctrList.SetUnderLine();
	m_ctrList.SetColorUnderLine(RGB(210, 210, 210));
//	m_ctrList.SetColorUnderLine(RGB(0, 0, 0));
	m_ctrList.SetTextFont(&m_listfont);
	m_ctrList.SetRowHeight(25);


}

void CView_History::ListCtrl_MoveSize()
{
	if (m_ctrList.GetSafeHwnd() == NULL)							return;

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	/////////////////////////////////////////////////////////////////////////// 하단 리스트 
	/////////////////////////////////////////////타이틀  
	m_rectListTitle = _rect;
	m_rectListTitle.right = m_rectListTitle.left + 162;
	m_rectListTitle.bottom = m_rectListTitle.top + 29;

	/////////////////////////////////////////////타이틀  

	/////////////////////////////////////////////리스트  
	CRect rectList;
	m_rectList = _rect;

	rectList = m_rectList;
	rectList.left -= 1;
	rectList.right += 1;
	rectList.top += 29;
	rectList.bottom = rectList.bottom - 1;
	m_ctrList.MoveWindow(rectList);
	/////////////////////////////////////////////리스트 

}


void CView_History::AddMessage(wchar_t* szMsg, COLORREF crText)
{
	int nCount = m_ctrList.GetItemCount();
	CTime t = CTime::GetCurrentTime();
	CString							stime(_T(""));
	stime = t.Format(L" [%Y/%m/%d %H:%M:%S]  ");
	m_ctrList.InsertItem(nCount, stime, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList.SetItemText(nCount, 1, szMsg , crText, RGB(255, 255, 255), HDF_LEFT);;

	m_ctrList.EnsureVisible(nCount,TRUE);

	m_ctrList.RedrawWindow();
}