#include "pch.h"
#include "CView_Base.h"
#include "CView_Manager.h"


IMPLEMENT_DYNAMIC(CView_Base, CView)

CView_Base::CView_Base()
{
	m_nViewState = -1; 
	m_nViewID = -1;

	m_bTimer = FALSE;

	m_nCompAppl_ID = -1;
	m_nRecvAppl_ID = -1;
}

CView_Base::~CView_Base()
{

}


BEGIN_MESSAGE_MAP(CView_Base, CView)
	ON_WM_ERASEBKGND()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

void CView_Base::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	SetVIewState();
	SetVIewID();
}


BOOL CView_Base::Create(const RECT& rect, CWnd* pParentWnd)
{
	return CView::Create(NULL, NULL, LBS_NOINTEGRALHEIGHT | WS_CHILD, rect, pParentWnd, 0);
}

void CView_Base::SetVIewState(int nStete)
{
	if (nStete == VIEW_STATE_HIDE)
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		ShowWindow(SW_SHOW);
	}

	m_nViewState = nStete;
}

BOOL CView_Base::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);


	CBrush brushBG(RGB(210, 221, 212));
	pDC->FillRect(rect, &brushBG);


	return TRUE;

	return CView::OnEraseBkgnd(pDC);
}


void CView_Base::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CView_Base::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CView::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
