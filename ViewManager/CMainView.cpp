// CMainView.cpp: 구현 파일
//

#include "pch.h"
#include "resource.h"
#include "CMainView.h"

#include "../DataManager/CDataManager.h"

#include "CView_History.h"
#include "CView_MMDB_Editor.h"

#include "CView_DFD_rst.h"
#include "CView_LF_rst.h"
#include "CView_PCE_rst.h"
#include "CView_PDVR_rst.h"
#include "CView_SOP_rst.h"
#include "CView_SCA_rst.h"
#include "CView_DNR_rst.h"
#include "CView_NCP_rst.h"
#include "CView_LFH_rst.h"


// CMainView

IMPLEMENT_DYNCREATE(CMainView, CFormView)

CMainView::CMainView()
	: CFormView(IDD_MAIN_VIEW)
{
	m_pHistoryView = NULL;
}

CMainView::~CMainView()
{

	//Clear_View();

}

void CMainView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMainView 진단

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainView 메시지 처리기


BOOL CMainView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	
	

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CMainView::Create_Main(const RECT& rect, CWnd* pParentWnd)
{
	return CMainView::Create(NULL, NULL, LBS_NOINTEGRALHEIGHT | WS_CHILD , rect, pParentWnd, IDD_MAIN_VIEW);
}

void CMainView::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	

	dc.Rectangle(rect);
}

void CMainView::Create_View()
{
	CRect						rectDummy(25, 25, 25, 25);

	m_pHistoryView = new CView_History();
	if (!m_pHistoryView->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_HISTORY_LOG, m_pHistoryView);
	m_pHistoryView->SetVIewState(VIEW_STATE_SHOW);

	CView_MMDB_Editor*			pEditor = new CView_MMDB_Editor();
	if (!pEditor->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_EDITOR_MMDATA, pEditor);

	CView_LF_rst*			pLF_rst = new CView_LF_rst();
	if (!pLF_rst->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_LOADFLOW_RESULT, pLF_rst);

	CView_DFD_rst*			pDFD_rst = new CView_DFD_rst();
	if (!pDFD_rst->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_DFD_RESULT, pDFD_rst);

	CView_PCE_rst*			pPCE_rst = new CView_PCE_rst();
	if (!pPCE_rst->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_PCE_RESULT, pPCE_rst);

	CView_PDVR_rst*			pPDVR_rst = new CView_PDVR_rst();
	if (!pPDVR_rst->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_PDVR_RESULT, pPDVR_rst);

	CView_SOP_rst*			pSOP_rst = new CView_SOP_rst();
	if (!pSOP_rst->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_SOP_RESULT, pSOP_rst);

	CView_SCA_rst*			pSCA_rst = new CView_SCA_rst();
	if (!pSCA_rst->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_SCA_RESULT, pSCA_rst);

	CView_DNR_rst*			pDNR_rst = new CView_DNR_rst();
	if (!pDNR_rst->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_DNR_RESULT, pDNR_rst);

	CView_NCP_rst*			pNCP_rst = new CView_NCP_rst();
	if (!pNCP_rst->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_NCP_RESULT, pNCP_rst);

	CView_LFH_rst*			pLFH_rst = new CView_LFH_rst();
	if (!pLFH_rst->Create(rectDummy, this))
	{
		// SENDLOGMSG(_T("* Err : NCP Application Result Window Create Fail"), RGB(225, 16, 16));
	}
	m_ViewMap.SetAt(VIEW_ID_LF_HISTORY_RESULT, pLFH_rst);
}

void CMainView::Clear_View()
{
	int nKey;
	CView_Base* pView;

	for (POSITION pos = m_ViewMap.GetStartPosition(); pos;)
	{
		m_ViewMap.GetNextAssoc(pos, nKey, pView);
		if(pView->GetSafeHwnd())
			delete pView;
	}

	m_ViewMap.RemoveAll();
}

void CMainView::SetActive_View(int nViewID)
{

	int nKey;
	CView_Base* pView;

	for (POSITION pos = m_ViewMap.GetStartPosition(); pos;)
	{
		m_ViewMap.GetNextAssoc(pos, nKey, pView);
		pView->SetVIewState(VIEW_STATE_HIDE) ;
	}

//	pView = NULL;
	
	
	if (m_ViewMap.Lookup(nViewID, pView))
	{
		pView->SetVIewState(VIEW_STATE_SHOW);
		pView->SetActiveWindow();
	}
	
	
}

void CMainView::InitData()
{
	int nKey;
	CView_Base* pView;

	for (POSITION pos = m_ViewMap.GetStartPosition(); pos;)
	{
		m_ViewMap.GetNextAssoc(pos, nKey, pView);
		pView->InitData();
	}

}


void CMainView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CRect							rect(0, 0, 0, 0);
	GetClientRect(&rect);
	/*rect.InflateRect(-1, -1);
	rect.top += 100 ;*/
	/////////////////
	int nKey;
	CView_Base* pView;

	for (POSITION pos = m_ViewMap.GetStartPosition(); pos;)
	{
		m_ViewMap.GetNextAssoc(pos, nKey, pView);
		pView->MoveWindow(rect);
	}
}


void CMainView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	Create_View();
}


void CMainView::AddMessage(wchar_t* szMsg, COLORREF crText)
{
	((CView_History*)m_pHistoryView)->AddMessage(szMsg, crText);
}

CView_Base* CMainView::GetActive_ApplView()
{
	int nKey;
	CView_Base* pView;

	for (POSITION pos = m_ViewMap.GetStartPosition(); pos;)
	{
		m_ViewMap.GetNextAssoc(pos, nKey, pView);

		if (pView->GetVIewState() == VIEW_STATE_SHOW)
			return pView;
		
	}

	return NULL;
}

void CMainView::recv_Appl(int nAppl)
{
	CView_Base* pView;

	pView = GetActive_ApplView();
	////////////// 실행시킨 View 넘겨줘야 되는다. 
	////////////// 

	if (pView)
	{
		pView->recv_Appl(nAppl);
		/*if (pView->GetVIewID() == VIEW_ID_PDVR_RESULT)
		{
			((CView_PDVR_rst*)pView)->recv_Appl(nAppl);
		}*/
	}
	
	
}

void CMainView::recv_Init()
{
	CDataManager* pDataMng = CDataManager::Instance();
	CView_Base* pView;
	int nKey;

	for (POSITION pos = m_ViewMap.GetStartPosition(); pos;)
	{
		m_ViewMap.GetNextAssoc(pos, nKey, pView);
		
		if (pView->GetVIewID() == pDataMng->GetExe_ViewID())
		{
			pView->recv_Init();
			break;
		}
			
	}

}

void CMainView::recv_Wnd(CWndMsgData* pWndMsgData)
{
	CView_Base* pView;

	pView = GetActive_ApplView();

	if (pView)
	{
		pView->recv_Wnd(pWndMsgData);
		/*if (pView->GetVIewID() == VIEW_ID_PDVR_RESULT)
		{
			((CView_PDVR_rst*)pView)->recv_Appl(nAppl);
		}*/
	}


}
