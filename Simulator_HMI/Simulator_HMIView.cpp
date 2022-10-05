
// Simulator_HMIView.cpp : CSimulator_HMIView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CSimulator_HMIView ����/�Ҹ�

CSimulator_HMIView::CSimulator_HMIView()
{
	m_pMainView = NULL;

}

CSimulator_HMIView::~CSimulator_HMIView()
{
	
}

BOOL CSimulator_HMIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CSimulator_HMIView �׸���

void CSimulator_HMIView::OnDraw(CDC* /*pDC*/)
{
	CSimulator_HMIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
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


// CSimulator_HMIView ����

#ifdef _DEBUG
void CSimulator_HMIView::AssertValid() const
{
	CView::AssertValid();
}

void CSimulator_HMIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimulator_HMIDoc* CSimulator_HMIView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimulator_HMIDoc)));
	return (CSimulator_HMIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimulator_HMIView �޽��� ó����


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