
// Simulator_HMIView.cpp : CSimulator_HMIView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Simulator_HMI.h"
#endif

#include "Simulator_HMIDoc.h"
#include "Simulator_HMIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimulator_HMIView

IMPLEMENT_DYNCREATE(CSimulator_HMIView, CView)

BEGIN_MESSAGE_MAP(CSimulator_HMIView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CSimulator_HMIView 생성/소멸

CSimulator_HMIView::CSimulator_HMIView()
{
	m_pMainView = NULL;

}

CSimulator_HMIView::~CSimulator_HMIView()
{
	
}

BOOL CSimulator_HMIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSimulator_HMIView 그리기

void CSimulator_HMIView::OnDraw(CDC* /*pDC*/)
{
	CSimulator_HMIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CSimulator_HMIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSimulator_HMIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSimulator_HMIView 진단

#ifdef _DEBUG
void CSimulator_HMIView::AssertValid() const
{
	CView::AssertValid();
}

void CSimulator_HMIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimulator_HMIDoc* CSimulator_HMIView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimulator_HMIDoc)));
	return (CSimulator_HMIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimulator_HMIView 메시지 처리기


void CSimulator_HMIView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED); 
}


void CSimulator_HMIView::CreateMainView()
{
	m_pMainView = new CMainView();
	m_pMainView->Create_Main(CRect(0, 0, 100, 100), this);
	m_pMainView->ShowWindow(SW_SHOW);
	
	ResizeDynamicLayout();
}

void CSimulator_HMIView::SetActive_View(int nViewID)
{
	m_pMainView->SetActive_View(nViewID);
}

void CSimulator_HMIView::InitData()
{
	m_pMainView->InitData();
}

void CSimulator_HMIView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CreateMainView();
}


void CSimulator_HMIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CRect							rect(0, 0, 0, 0);
	GetClientRect(&rect);
	//	rect.InflateRect(-50, -50);

	if (m_pMainView)
	{
		m_pMainView->MoveWindow(rect);
	}
}

void CSimulator_HMIView::AddMessage(wchar_t* szMsg, COLORREF crText)
{
	m_pMainView->AddMessage(szMsg, crText);
}

void CSimulator_HMIView::recv_Appl(int nAppl)
{
	m_pMainView->recv_Appl(nAppl);
}

void CSimulator_HMIView::recv_Init()
{
	m_pMainView->recv_Init();
}

void CSimulator_HMIView::recv_Wnd(CWndMsgData* pWndMsgData)
{
	m_pMainView->recv_Wnd(pWndMsgData);
}