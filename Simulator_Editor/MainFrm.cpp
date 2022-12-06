
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Simulator_Editor.h"
#include "resource.h"
#include "Simulator_EditorView.h"

#include "MainFrm.h"

#include "../SB_Manager/CSB_Manager.h"
#include "../DND_Manager/CDND_Manager.h"
#include "../DND_Manager/CDND_Switch.h"
#include "../DataManager/CDataManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CPNOCtrl_SkinFrame_SDI)

BEGIN_MESSAGE_MAP(CMainFrame, CPNOCtrl_SkinFrame_SDI)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	ON_WM_NCCALCSIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_ENTERSIZEMOVE()
	ON_WM_EXITSIZEMOVE()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCMOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_MESSAGE(WM_TOOLBAR_MSG, OnToolbarMsg)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	m_pFindDlg = NULL;
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
//	theAppDataMng->CloseDB();
	theAppDataMng->DIsConnectKASIMData(0);
 	theAppDataMng->Close();
	theUtil->Close();
	delete thePNOCtrolskin;
	delete CDND_Manager::Instance();
	delete CSB_Manager::Instance();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (cs.hMenu != NULL)
	{
		::DestroyMenu(cs.hMenu);
		cs.hMenu = NULL;
	}
	cs.style &= ~FWS_ADDTOTITLE;

	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

// 	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME;
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
		;

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CPNOCtrl_SkinFrame_SDI::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CPNOCtrl_SkinFrame_SDI::Dump(dc);
}
#endif //_DEBUG

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPNOCtrl_SkinFrame_SDI::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBar.Create(this, IDD_TOOLBAR_DLG, CBRS_TOP, IDD_TOOLBAR_DLG);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);
//	DockControlBar(&m_wndToolBar);
	m_ToolbarDlg.Create(IDD_TOOLBAR_DLG, &m_wndToolBar);
	m_ToolbarDlg.SetParentWnd(this);
	m_ToolbarDlg.ShowWindow(SW_SHOW);

	if (!m_wndSetting_Single.Create(this, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_RIGHT))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndSetting_Single.EnableDocking(CBRS_ALIGN_RIGHT);
	m_wndSetting_Single.ShowWindow(SW_HIDE);

	if (!m_wndSetting_Text.Create(this, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_RIGHT))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndSetting_Text.EnableDocking(CBRS_ALIGN_RIGHT);
	m_wndSetting_Text.ShowWindow(SW_HIDE);

	if (!m_wndSetting_Connect.Create(this, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_RIGHT))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndSetting_Connect.EnableDocking(CBRS_ALIGN_RIGHT);
	m_wndSetting_Connect.ShowWindow(SW_HIDE);

	CSB_Manager* pSBMng = CSB_Manager::Instance();
	pSBMng->Read_SB_File();
	if (pSBMng->m_Array_SB.GetSize() == 0)
	{
		//OnToolbarMsg(0, 2);
		exit(0);
	}

	//김종민 - 입력 20210625 
	theAppDataMng->SetOnlineStudyMode(2);
	theAppDataMng->ConnectKASIMData(0, 2);
	//김종민 - 입력 20210625 
	return 0;
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CPNOCtrl_SkinFrame_SDI::OnSize(nType, cx, cy);

	if (m_ToolbarDlg.GetSafeHwnd())
	{
		CRect rect;
		m_ToolbarDlg.GetClientRect(&rect);
		m_ToolbarDlg.MoveWindow(0, 0, cx, rect.Height());
	}

}

void CMainFrame::OnDestroy()
{
	CPNOCtrl_SkinFrame_SDI::OnDestroy();
}


void CMainFrame::OnPaint()
{
	CPaintDC dc(this);
	CPNOCtrl_SkinFrame_SDI::OnPaint();
}

void CMainFrame::OnNcPaint()
{
	CPNOCtrl_SkinFrame_SDI::OnNcPaint();
} 

BOOL CMainFrame::OnNcActivate(BOOL bActive)
{
	CPNOCtrl_SkinFrame_SDI::OnNcActivate(bActive);
	return TRUE;
}

void CMainFrame::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	CPNOCtrl_SkinFrame_SDI::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 1655;
	lpMMI->ptMinTrackSize.y = 600;
	CPNOCtrl_SkinFrame_SDI::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnEnterSizeMove()
{
	CPNOCtrl_SkinFrame_SDI::OnEnterSizeMove();
}

void CMainFrame::OnExitSizeMove()
{
	CPNOCtrl_SkinFrame_SDI::OnExitSizeMove();
}

void CMainFrame::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPNOCtrl_SkinFrame_SDI::OnNcLButtonDblClk(nHitTest, point);
}

void CMainFrame::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	CPNOCtrl_SkinFrame_SDI::OnNcLButtonDown(nHitTest, point);
}

void CMainFrame::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	CPNOCtrl_SkinFrame_SDI::OnNcLButtonUp(nHitTest, point);
}

void CMainFrame::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	CPNOCtrl_SkinFrame_SDI::OnNcMouseMove(nHitTest, point);
}

void CMainFrame::OnNcMouseLeave()
{
	CPNOCtrl_SkinFrame_SDI::OnNcMouseLeave();
}

void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	CPNOCtrl_SkinFrame_SDI::OnLButtonUp(nFlags, point);
}

void CMainFrame::OnMove(int x, int y)
{
	CPNOCtrl_SkinFrame_SDI::OnMove(x, y);

}

LRESULT CMainFrame::OnToolbarMsg(WPARAM wParam, LPARAM lParam)
{
	CDND_Manager* pDNDMng = CDND_Manager::Instance();
	CDND_Switch* pSwitch = (CDND_Switch*)pDNDMng;
	CSimulator_EditorView* pView = (CSimulator_EditorView*)GetActiveView();


	if (wParam == 0)//system menu
	{
		switch (lParam)
		{
		case 0://최소화
			ShowWindow(SW_MINIMIZE);
			break;
		case 1://최대화
			if (IsZoomed())	ShowWindow(SW_RESTORE);
			else			ShowWindow(SW_MAXIMIZE);
			break;
		case 2://프로그램종료
			PostMessage(WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
	}
	else if (wParam == 1)//메뉴
	{

  		switch (lParam)
		{
		case 0://Load
			break; //20220926 연구원 요청 비활성화
			pDNDMng->SVG_Delete(); //삭제?
			pDNDMng->SVG_LoadAs();
			//김종민 - 입력 20210625 
			pDNDMng->SVG_KASIM_Association(); //20210303
			pDNDMng->SVG_KASIM_Association_Index(); //20210303
			//
			//김종민 - 입력 20210625 
			((CSimulator_EditorView*)GetActiveView())->Reset();			
			break;
		case 1://Save
			pDNDMng->SVG_SaveAs();
			//theAppDataMng->WriteKASIMCSVFile(1, "", false, false, false, false);
			break;
		case 2://확대
			if (pView)
			{
				pView->Editor_View_Expansion();
			}
			//AfxMessageBox( _T("확대") );
			break;
		case 3://축소
			if (pView)
			{
				pView->Editor_View_Reduce();
			}
			//AfxMessageBox(_T("축소"));
			break;
		case 4://기기조작 명령서
			if (pView)
			{
				pView->FindObject(); 
			}
			//AfxMessageBox( _T("기기조작 명령서") );
			break;
		case 5://이미지 저장		
			if (pView)
			{
				pView->PrintImage();
			}
			break;
		default:
			break;
		}
	}
	return S_OK;
}

void CMainFrame::SettingWnd_Hide()
{
	m_wndSetting_Single.ShowWindow(SW_HIDE);
	m_wndSetting_Text.ShowWindow(SW_HIDE);
	m_wndSetting_Connect.ShowWindow(SW_HIDE);
	RecalcLayout();
	RedrawWindow();
}

void CMainFrame::SetSelect_DNDObject(CString strID)
{
	SettingWnd_Hide();

	if (strID.IsEmpty())
	{
		return;
	}
	CDND_Manager* pDNDMng = CDND_Manager::Instance();
	CDND_Object* pDNDObj = pDNDMng->GetDNDObject2ID(strID);

	//
	if(pDNDObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
	{
		if (pDNDObj->m_str_psrtype == "COMPSWITCH" || pDNDObj->m_str_psrtype == "TR")
		{
			if (pDNDObj->m_str_innertext == "")
			{
				return;
			}
			else
			{
				m_wndSetting_Single.SetSelect_DNDObject(pDNDObj);
				m_wndSetting_Single.ShowWindow(SW_SHOW);
			}
		}
		else
		{
			m_wndSetting_Single.SetSelect_DNDObject(pDNDObj);
			m_wndSetting_Single.ShowWindow(SW_SHOW);
		}

	}
	else if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
	{
		m_wndSetting_Connect.SetSelect_DNDObject(pDNDObj);
		m_wndSetting_Connect.ShowWindow(SW_SHOW);
	}
	else if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_TEXT)
	{
		m_wndSetting_Text.SetSelect_DNDObject(pDNDObj);
		m_wndSetting_Text.ShowWindow(SW_SHOW);
	}
	else /*if(pDNDObj->ObjectType_Get() == DND_OBJTYPE_MULTI_M
		|| pDNDObj->ObjectType_Get() == DND_OBJTYPE_BLOCK)*/
	{
		//20211007
		if (pDNDObj->m_str_psrtype == "COMPSWITCH" || pDNDObj->m_str_psrtype == "TR")
		{
			if (pDNDObj->m_str_innertext == "")
			{
				return;
			}
			else
			{
				m_wndSetting_Single.SetSelect_DNDObject(pDNDObj);
				m_wndSetting_Single.ShowWindow(SW_SHOW);
			}
		}
		else
		{
			m_wndSetting_Single.SetSelect_DNDObject(pDNDObj);
			m_wndSetting_Single.ShowWindow(SW_SHOW);
		}

	}
	
	RecalcLayout();
	RedrawWindow();
}

void CMainFrame::Redraw_View()
{
	GetActiveView()->RedrawWindow();
}
