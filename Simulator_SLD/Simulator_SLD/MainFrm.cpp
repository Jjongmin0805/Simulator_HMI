
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Simulator_SLD.h"
#include "Simulator_SLDDoc.h"
#include "Simulator_SLDView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
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
	ON_MESSAGE(WM_MODIFY_MEASURE_MSG, &CMainFrame::OnModifyMeasFunc)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);

	m_nSLDMode = 0;
	m_nPhaseOpt = 0;
	m_bNameOpt = TRUE;
	m_nMeasValueOpt = 15;
	m_nMeasVoltUnit = 0;
	m_nCalcValueOpt = 7;
	m_nCalcVoltUnit = 0;

	m_nViewMode = SHOW_VIEWMODE_SINGLE;
	m_bAreaSetMode = FALSE;
	m_bShowSecInfo = FALSE;
	m_bShowVirtualDG = FALSE;

	m_nDLIdx = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPNOCtrl_SkinFrame_SDI::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndToolBar.Create(this, IDD_TOOLBAR_DLG, CBRS_TOP, IDD_TOOLBAR_DLG);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_ToolbarDlg.Create(IDD_TOOLBAR_DLG, &m_wndToolBar);
	m_ToolbarDlg.SetParentWnd(this);
	m_ToolbarDlg.ShowWindow(SW_SHOW);

	int		nWidth;
	nWidth = WND_WIDTH_FRAME_SIZE + (WND_BORDER_MARGIN * 2) + WND_THICKFRAME_MARGIN;

	if (!m_wndSideCtrl.Create(_T("Infor"), this, CSize(nWidth, 0), 0x1000, WS_CHILD | WS_VISIBLE))
	{
		TRACE0("Failed to create mybar\n");
		return -1;      // fail to create
	}

	EnableDocking(CBRS_ALIGN_LEFT);
	m_wndSideCtrl.EnableDocking(CBRS_ALIGN_LEFT);
	DockControlBar(&m_wndSideCtrl, AFX_IDW_DOCKBAR_LEFT);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (cs.hMenu != NULL)
	{
		::DestroyMenu(cs.hMenu);
		cs.hMenu = NULL;
	}
	cs.style &= ~FWS_ADDTOTITLE;

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기
void CMainFrame::OnDestroy()
{
	CPNOCtrl_SkinFrame_SDI::OnDestroy();
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	if (m_ToolbarDlg.GetSafeHwnd())
	{
		CRect rect;
		m_ToolbarDlg.GetClientRect(&rect);
		m_ToolbarDlg.MoveWindow(0, 0, cx, rect.Height());
	}

	CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
	if (pView)			pView->SetNaviPosition();

	CPNOCtrl_SkinFrame_SDI::OnSize(nType, cx, cy);
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

	CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
	if (pView)			pView->SetNaviPosition();
}

LRESULT CMainFrame::OnToolbarMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)//system menu
	{
		switch (lParam)
		{
		case 0://최소화
			ShowWindow(SW_MINIMIZE);
			break;
		case 1://최대화
			if (IsZoomed())	ShowWindow(SW_RESTORE);
			else				ShowWindow(SW_MAXIMIZE);
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
// 		case 0://Home
// 		{
// 			CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
// 			if (pView)
// 			{
// 				pView->ToggleGisMode();
// 			}
// 			break;
// 		}
// 		case 1://Load
// 			AfxMessageBox(_T("Load"));
// 			break;
// 		case 2://Save
// 			AfxMessageBox(_T("Save"));
// 			break;
		case 0://전체보기
		{
			//AfxMessageBox(_T("전체보기"));
			CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
			if (pView)
			{
				int nDLIdx;
				nDLIdx = pView->SetSLDMode(SHOW_SLDMODE_ALL);
				if (nDLIdx)
				{
					pView->MakeSLD(nDLIdx);
					pView->MakeSLDBuffer(TRUE);
				}
			}
			break;
		}
		case 1://자동화모드
		{
			//AfxMessageBox(_T("자동화모드"));
			CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
			if (pView)
			{
				int nDLIdx;
				nDLIdx = pView->SetSLDMode(SHOW_SLDMODE_AUTO);
				if (nDLIdx)
				{
					pView->MakeSLD(nDLIdx);
					pView->MakeSLDBuffer(TRUE);
				}
			}
			break;
		}
		case 2://보호기기모드
		{
			//AfxMessageBox(_T("보호기기모드"));
			CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
			if (pView)
			{
				int nDLIdx;
				nDLIdx = pView->SetSLDMode(SHOW_SLDMODE_PROTECT);
				if (nDLIdx)
				{
					pView->MakeSLD(nDLIdx);
					pView->MakeSLDBuffer(TRUE);
				}
			}
			break;
		}
		case 3://단선도모드 -> 찾기
		{
			//AfxMessageBox(_T("단선도모드"));
// 			CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
// 			if (pView)
// 			{
// 				if (pView->m_nViewMode != SHOW_VIEWMODE_SINGLE)
// 				{
// 					m_nViewMode = SHOW_VIEWMODE_SINGLE;
// 					pView->ShowSLDView(m_nViewMode);
// 				}
// 			}
			CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
			if (pView)
			{
				pView->FindObject();
			}
			break;
		}
		case 4://GIS모드 -> 이미지저장
		{
			CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
			if (pView)
			{
				pView->PrintImage();
			}
			break;
		}
		case 5://기본배율
		{
			CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
			if (pView)
			{
				if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
				{
					pView->Zoom(0);
					pView->MakeSLDBuffer(TRUE);
				}
				else
				{
					pView->DefaultBaseMap();
				}
			}
			break;
		}
		case 6://설정
		{
			AfxMessageBox(_T("설정"));
			break;
		}
		case 7://다구간 설정
		{
			m_bAreaSetMode = !m_bAreaSetMode;
			
			//Toolbar상태 변경
			m_ToolbarDlg.SetBoundarCheckMode(m_bAreaSetMode);
			//

			if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
			{
				CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
				pView->ClearBoundaryCheck(TRUE);
				pView->MakeSLDBuffer(FALSE);
			}

// 			//모드해제시 초기화.
// 			if (!m_bAreaSetMode)
// 			{
// 				CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
// 				if (pView)
// 				{
// 					if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
// 					{
// 						pView->ClearBoundaryCheck();
// 						pView->MakeSLDBuffer(FALSE);
// 					}
// 					else
// 					{
// 						pView->DefaultBaseMap();
// 					}
// 				}
// 			}

			break;
		}
		case 8://선종보기모드
		{
			m_bShowSecInfo = !m_bShowSecInfo;

			//Toolbar상태 변경
			m_ToolbarDlg.SetShowSecMode(m_bShowSecInfo);
			CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
			if (pView)
			{
				pView->MakeSLDBuffer(FALSE);
			}
			//

			break;
		}
		case 9://가상DG보기
		{
			m_bShowVirtualDG = !m_bShowVirtualDG;

			//Toolbar상태 변경
			m_ToolbarDlg.SetShowVirtualDG(m_bShowVirtualDG);
			CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
			if (pView)
			{
				int nDLIdx;
				nDLIdx = pView->m_nDLIdx;
				if (nDLIdx)
				{
					pView->m_nDLIdx = 0;
					pView->MakeSLD(nDLIdx);
					pView->MakeSLDBuffer(TRUE);
				}
			}
			//

			break;
		}

		default:
			break;
		}
	}
	return S_OK;
}

void CMainFrame::InitTreeView()
{
	m_wndSideCtrl.InitTreeView();
}

void CMainFrame::TreeClickEvent(int nDLIdx)
{
	CString szMsg;
	szMsg.Format(_T("TreeClick:: Index(%d)"), nDLIdx);
	AfxMessageBox(szMsg);
}

void CMainFrame::TreeDBClickEvent(int nDLIdx)
{
	CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
	if (pView)
	{
		if (pView->m_bAction)	return;

		if (m_nViewMode == SHOW_VIEWMODE_GIS)
			pView->m_dZoomScale = pView->m_dStZoomScale;

		if (pView->m_nDLIdx != nDLIdx)
		{
			pView->MakeSLD(nDLIdx);
			pView->MakeSLDBuffer(TRUE);
		}

		if (m_nViewMode == SHOW_VIEWMODE_GIS)
		{
			pView->CalculationScale();//GIS배경을 기본배율 설정
			pView->ShiftMap();//그리기
		}
	}
}

void CMainFrame::TreeRBClickEvent(int nDLIdx)
{
	CString szMsg;
	szMsg.Format(_T("TreeRClick:: Index(%d)"), nDLIdx);
	AfxMessageBox(szMsg);
}

void CMainFrame::SetGroup1CompData(CNodeView* pNodeView, int nDLIdx)
{
	m_wndSideCtrl.SetGroup1CompData(pNodeView, nDLIdx);
}

void CMainFrame::SetGroup1MeasData(int nCompType, int nCompIdx)
{
	m_wndSideCtrl.SetGroup1MeasData(nCompType, nCompIdx);
}

void CMainFrame::SetGroup1ApplData(int nCompType, int nCompIdx)
{
	m_wndSideCtrl.SetGroup1ApplData(nCompType, nCompIdx);
}

void CMainFrame::ShowDLInfo()
{
	if( m_nDLIdx )
		m_wndSideCtrl.ShowDLInfo(m_nDLIdx);
}

LRESULT CMainFrame::OnModifyMeasFunc(WPARAM wParam, LPARAM lParam)
{
	CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();
	if (pView == NULL)																return FALSE;

	pView->ModifySLD((int)wParam);

	return S_OK;
}

BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	CSimulatorSLDView* pView = (CSimulatorSLDView*)GetActiveView();

	if (pCopyDataStruct->dwData == 1)// Application
	{
// 		if (pView)
// 		{
// 			pView->MakeSLDBuffer(FALSE);
// 			pView->Invalidate();
// 		}
	}
	else if (pCopyDataStruct->dwData == 2)// HMI
	{
		wchar_t									chReceiveData[2048] = { 0, };
		memcpy(chReceiveData, pCopyDataStruct->lpData, (int)(pCopyDataStruct->cbData));

		CString									szData;
		szData.Format(_T("%s"), chReceiveData);

		CString szMsg, szContent;
		CString szValue[3];

		int nCnt = 0;
		while (AfxExtractSubString(szMsg, szData, nCnt, _T(',')))
		{
			szValue[nCnt] = szMsg;
			nCnt++;
		}

		int nAppl_id, nOption;
		nAppl_id								= _wtoi(szValue[0]);
		nOption									=_wtoi(szValue[1]);
		szContent								= szValue[2];

		if (pView)
 		{
			if (nAppl_id == 999)//설비찾기
			{
				pView->FindNodePosition(nOption, FALSE);
			}
			else if (nAppl_id == 888 )//고장이력단선도보기
			{
				pView->m_nShowOption = 4;
				pView->FindNodePosition(nOption, FALSE);
			}
			else
			{
				pView->m_nShowOption = nOption;

				pView->MakeSLDBuffer(FALSE);
				pView->Invalidate();
			}
 		}
	}
	else if (pCopyDataStruct->dwData == 3)//DSR완료메시지
	{
// 		if (pView)
// 		{
// 			pView->MakeSLDBuffer(FALSE);
// 			pView->Invalidate();
// 
// 			pView->MakeFaultInfo();
// 			pView->MakeFaultArea();
// 			pView->MakeOutageInfo();
// 			pView->MakeOutageArea();
// 		}
	}
	else if (pCopyDataStruct->dwData == 4)//재구성완료메시지
	{
// 		if (pView)
// 		{
// 			pView->MakeDnrInfo();
// 			pView->MakeDnrArea();
// 		}
	}
	else if (pCopyDataStruct->dwData == 99)//개폐기조작(이동)메시지 -> 상태값이 SW_OPEN 또는 SW_CLOSE이면 조작, 아니면 이동.
	{
// 		BOOL												bReDrow(FALSE);
// 		int													nDLIdx(0), nSwIdx(0), nSwType(0), nStatus(-1), nTargetIdx;
// 		char												chReceiveData[1024] = { 0, };
// 		memcpy(chReceiveData, pCopyDataStruct->lpData, (int)(pCopyDataStruct->cbData));
// 
// 		CA2W												szMulti2Uni(chReceiveData);
// 		wstring												szData(szMulti2Uni);
// 
// 		wchar_t*											sepData;
// 		sepData = wcstok((wchar_t*)(szData.c_str()), _T(","));
// 		if (sepData)										nDLIdx = _wtoi(sepData);
// 		sepData = wcstok(NULL, L",");
// 		if (sepData)										nSwIdx = _wtoi(sepData);
// 		sepData = wcstok(NULL, L",");
// 		if (sepData)										nSwType = _wtoi(sepData);
// 		sepData = wcstok(NULL, L",");
// 		if (sepData)										nStatus = _wtoi(sepData);
// 
// 		if (nDLIdx == 0 || nSwIdx == 0 || nSwType == 0)	return TRUE;
// 		if (nStatus < 0)									return TRUE;
// 
// 		if (nSwType == 1)
// 		{
// 			if (nStatus == SW_OPEN || nStatus == SW_CLOSE)
// 			{
// 				PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_nwstat"), nSwIdx, nStatus);
// 				bReDrow = TRUE;
// 			}
// 
// 			nTargetIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), (int)nSwIdx);
// 		}
// 		else if (nSwType == 2)
// 		{
// 			if (nStatus == SW_OPEN || nStatus == SW_CLOSE)
// 			{
// 				PUTVALUE(_T("tisw_dyn_mea"), _T("tisw_nwstat"), nSwIdx, nStatus);
// 				bReDrow = TRUE;
// 			}
// 
// 			nTargetIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_ii_tnd"), (int)nSwIdx);
// 		}
// 		else
// 		{
// 			AfxMessageBox(_T("sw_type message error"));
// 			return TRUE;
// 		}
// 
// 		if (pView)
// 		{
// 			if (pView->GetDLIdx() != nDLIdx)				bReDrow = TRUE;
// 
// 			if (bReDrow)
// 			{
// 				pView->MakeSLD(nDLIdx);
// 				pView->MakeSLDBuffer(TRUE);
// 			}
// 
// 			pView->MoveFocusNodeView(nTargetIdx);
// 		}
	}

	return CPNOCtrl_SkinFrame_SDI::OnCopyData(pWnd, pCopyDataStruct);
}