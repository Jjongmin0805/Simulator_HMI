
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Simulator_HMI.h"

#include "MainFrm.h"

#include "../DataManager/CDataManager.h"
#include "../ViewManager/CView_Base.h"
//#include "../SB_Manager/CSB_Manager.h"

#include "../DataDialog/CPNOVR_Manager.h"
#include "../DataDialog/CApplOptDlg.h"
#include "../DataDialog/CUserInfoDlg.h"
#include "../DataDialog/CMTR_Info_Dlg.h"
#include "../DataDialog/CLine_Type_Dlg.h"
#include "../DataDialog/CLoadflow_Edit_Dlg.h"
#include "../DataDialog/CRelayMngDlg.h"
#include "../DataDialog/CKacim2OfficeDlg.h"

#include "../DisProtect/TCRcRegDlg.h"
#include "../DisProtect/TCRelayRegDlg.h"

#include "../ImportPwData/ImportSomasDlg.h"
#include "../DataDialog/CDataShareDlg.h"
#include "../DataDialog/CMemopsDlg.h"
#include "../Date_CSV_Files/CDate_Csv_File_Dlg.h"


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
	ON_WM_TIMER()
	ON_MESSAGE(SENDLOGMSG_PARAM, &CMainFrame::OnSendLogMsgParam)
	ON_WM_COPYDATA()
	ON_COMMAND(ID_RUNAPPLICATIONSTUDY_APPLICATIONTEST, &CMainFrame::OnRunapplicationstudyApplicationtest)
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);


}

CMainFrame::~CMainFrame()
{

	CDataManager* pDataMng = CDataManager::Instance();
	delete pDataMng;

	delete CPNOVR_Manager::Instance();

	CoUninitialize();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPNOCtrl_SkinFrame_SDI::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowText(_T("Simulator_hmi"));

	m_wndToolBar.Create(this, IDD_TOOLBAR_DLG, CBRS_TOP, IDD_TOOLBAR_DLG);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);

	m_ToolbarDlg.Create(IDD_TOOLBAR_DLG, &m_wndToolBar);
	m_ToolbarDlg.SetParentWnd(this);
	m_ToolbarDlg.ShowWindow(SW_SHOW);

 //	SetTimer( 101, 500, NULL );
	//CSB_Manager* pSBMng = CSB_Manager::Instance();
	//pSBMng->Read_SB_File();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( cs.hMenu != NULL )
	{
		::DestroyMenu( cs.hMenu );
		cs.hMenu = NULL;
	}
	cs.style &= ~FWS_ADDTOTITLE;

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

// 	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME;
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
	if( m_ToolbarDlg.GetSafeHwnd() )
	{
		CRect rect;
		m_ToolbarDlg.GetClientRect( &rect );
		m_ToolbarDlg.MoveWindow( 0, 0, cx, rect.Height() );
	}

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
	lpMMI->ptMinTrackSize.x																		= 1655;
	lpMMI->ptMinTrackSize.y																		= 600;
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
	if( wParam == 0 )//system menu
	{
		switch( lParam )
		{
		case 0://최소화
			ShowWindow( SW_MINIMIZE );
			break;
		case 1://최대화
			if( IsZoomed() )	ShowWindow( SW_RESTORE );
			else				ShowWindow( SW_MAXIMIZE );
			break;
		case 2://프로그램종료
			PostMessage(WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
	}
	else if( wParam == 1 )//툴바
	{
		
		switch( lParam )
		{
		case 0://Home
			//AfxMessageBox( _T("Home") );
			m_pSimView->SetActive_View(VIEW_ID_HISTORY_LOG);
			break;
		case 1://MEM View
			m_pSimView->SetActive_View(VIEW_ID_EDITOR_MMDATA);
			break;
		case 2://조류계산
			m_pSimView->SetActive_View(VIEW_ID_LOADFLOW_RESULT);
			break;
		case 3://고장처리
			//m_pSimView->SetActive_View(VIEW_ID_DFD_RESULT);
			m_pSimView->SetActive_View(VIEW_ID_LF_HISTORY_RESULT);
			break;
		case 4://보호협조
			m_pSimView->SetActive_View(VIEW_ID_PCE_RESULT);
			break;
		case 5://DNR
			m_pSimView->SetActive_View(VIEW_ID_DNR_RESULT);
			break;
		case 6://분산형 전원 기술검토
			m_pSimView->SetActive_View(VIEW_ID_PDVR_RESULT);
			break;
		case 7://SOP
			m_pSimView->SetActive_View(VIEW_ID_SOP_RESULT);
			break;
		case 8://토폴로지 검토
			m_pSimView->SetActive_View(VIEW_ID_NCP_RESULT);
			break;
		case 9://고장 전류 계산
			m_pSimView->SetActive_View(VIEW_ID_SCA_RESULT);
			break;
		default:
			break;
		}
	}
	else if (wParam == 2)//메뉴
	{
		RunMenuMsg(lParam);
		/*switch (lParam)
		{
		case ID_RUNAPPLICATIONSTUDY_APPLICATIONTEST:
			OnRunapplicationstudyApplicationtest();
			break;
		default:
			break;
		}*/
	}

	return S_OK;
}

void CMainFrame::OnTimer( UINT_PTR nIDEvent )
{

	if (nIDEvent == 101)
	{
		m_pSimView->SetActive_View(VIEW_ID_HISTORY_LOG);
		m_pSimView->RedrawWindow();
		KillTimer(101);
		
		//AfxMessageBox( L"KASIM Loading and Create. long long time. start" );

		CoInitialize(NULL);
		CDataManager* pDataMng = CDataManager::Instance(TRUE);
		pDataMng->Read_DBInfo();
		pDataMng->Read_ApplInfo();
		
	//	
	//	pDataMng->GetTestKASIMData();
	//	pDataMng->PutTestKASIMData();

		pDataMng->LoadKASIM();
		pDataMng->SetRelayInfo2DB();
		pDataMng->Excute_Appl(_T("1"));


		m_pSimView->InitData();

		/*CString strFrmName;
		SetWindowText(_T("Simulator_hmi"));*/


		

	//	pDataMng->Excute_SLD();

		SENDLOGMSG(_T("KASIM Loading and Create. end"), SENDLOGMSG_COLOR_SUC);
		//AfxMessageBox(L"KASIM Loading and Create. end");
	}

	CPNOCtrl_SkinFrame_SDI::OnTimer( nIDEvent );
}

void	CMainFrame::SetSimView()
{
	m_pSimView = (CSimulator_HMIView*)GetActiveView();
}

LRESULT CMainFrame::OnSendLogMsgParam(WPARAM wParam, LPARAM lParam)
{
	
	if (m_pSimView)
	{
		m_pSimView->AddMessage((wchar_t*)wParam, (int)lParam);
	}

	return S_OK;
}

//==========================================================================================================================



BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	wchar_t									chReceiveData[2048] = { 0, };
	int nRecvWnd = pCopyDataStruct->dwData; ///////////// AppWRProject = 1 , SLD = 3 
	memcpy(chReceiveData, pCopyDataStruct->lpData, (int)(pCopyDataStruct->cbData));
	CString strLog;

	if (nRecvWnd == 1)
	{
		CString strRecvData,strTok;
		CString strData[2];
		CString strApplName[14] = { _T(""),_T("ncp"),_T("dle"),_T("dse"),_T("rpf")
								,_T("dfd") ,_T("dsr") ,_T("ap1") ,_T("pdvr") ,_T("dpvrdg")
								, _T("dnr") ,_T("sca") ,_T("pce"),_T("sop") };

		//////////////////// 응용프로그램 config 확인해야된다. 이거 처리해야된다

		int nAppl, nRst;

		strRecvData.Format(_T("%s"), chReceiveData);
		int nCnt = 0;
		while (AfxExtractSubString(strTok, strRecvData, nCnt, _T(',')))
		{
			strData[nCnt] = strTok;
			nCnt++;
		}

		nAppl = _wtof(strData[0]);
		nRst = _wtof(strData[1]);
		
		////////////////// 성공 여부 확인
		

		strLog.Format(_T("Application : Completed ( %s )"), strApplName[nAppl]);

		SENDLOGMSG((WPARAM)strLog.GetBuffer(), SENDLOGMSG_COLOR_NOR);

		m_pSimView->recv_Appl(nAppl);

		if (nAppl == 1)
		{
			if (theDataMng->GetExe_ViewID() == 0)
			{
				theDataMng->Excute_SLD();

				m_pSimView->InitData();
			}
				
		}
	}
	else if (nRecvWnd == 3)
	{
		CString strRecvData;
		strRecvData.Format(_T("%s"), chReceiveData);

		strLog.Format(_T("SLD : Recv - %s "), strRecvData);

		SENDLOGMSG((WPARAM)strLog.GetBuffer(), SENDLOGMSG_COLOR_NOR);

		CWndMsgData	WndMsgData;
		WndMsgData.SetData(strRecvData);
		m_pSimView->recv_Wnd(&WndMsgData);
	}

	
	return CPNOCtrl_SkinFrame_SDI::OnCopyData(pWnd, pCopyDataStruct);
}

void	CMainFrame::RunMenuMsg(int nMenuID)
{
	CDataManager* pDataMng = CDataManager::Instance();

	switch (nMenuID)
	{
	case ID_FILE_OPEN:
	{
		CDataManager::Instance()->KASIM_LoadAs(_T(""));
		break;
	}
	case ID_FILE_SAVE:
		CDataManager::Instance()->KASIM_SaveAs(_T(""));
		break;

	case ID_FILE_SAVE_AS:
		CDataManager::Instance()->KASIM_SaveAs(_T(""));
		break;
	case ID_SETTING_MTR:
	{
		CMTR_Info_Dlg Dlg;
		Dlg.DoModal();
		break;
	}
	case ID_SETTING_LINETYPE:
	{
		CLine_Type_Dlg Dlg;
		Dlg.DoModal();
		break;
	}
	case ID_SETTING_LOADFLOW:
	{
		CLoadflow_Edit_Dlg Dlg;
		Dlg.DoModal();
		break;
	}
	case ID_SETTING_RELAY:
	{
		CTCRelayRegDlg	Dlg(&pDataMng->m_Session_OD);
		Dlg.DoModal();
		break;
	}
	case ID_SETTING_RECLOSER:
	{
		CTCRcRegDlg Dlg(&pDataMng->m_Session_OD);
		Dlg.DoModal();
		break;
	}
	case ID_SETTING_APP:
	{
		//CApplOptDlg Dlg;
		CRelayMngDlg Dlg;
		Dlg.DoModal();
		break;
	}
	case ID_SETTING_USER:
	{
		CUserInfoDlg Dlg;
		Dlg.DoModal();
		break;
	}
	case ID_ADMS_SOMAS:
	{
		CImportSomasDlg Dlg;
		Dlg.DoModal();
		break;
	}
	case ID_ADMS_KACIM_CONVERT:
	{
		CKacim2OfficeDlg Dlg;
		Dlg.DoModal();
		break;
	}
	case ID_ADMS_SHARE:
	{
		CDataShareDlg Dlg;
		Dlg.DoModal();
		break;
	}
	case ID_ADMS_APPLINIT:
	{
		m_pSimView->recv_Init();
		break;
	}
	case ID_OCB_RELAY_IMPORT:
	{
		Excute_Import_OCB();
		break;
	}
	case ID_MEMOPS:
	{
		CMemopsDlg Dlg;
		Dlg.DoModal();
		break;
	}
	case ID_EQUIP_INSERT:
	{
		CDate_Csv_File_Dlg Dlg;
		Dlg.DoModal();
		break;
	}
	default:
		break;
	}
}

void CMainFrame::Excute_Import_OCB()
{
	CDataManager* pDataMng = CDataManager::Instance();
	CString strApplPath = pDataMng->MyPath();
	CString strParam = _T("");

	if (!ShellExecute(NULL, _T("open"), _T("FHS.exe"), strParam, strApplPath, TRUE))
	{
		SENDLOGMSG(_T("Simulator_SLD.exe : Fail"), SENDLOGMSG_COLOR_NOR);

		return ;
	}
}

void CMainFrame::OnRunapplicationstudyApplicationtest()
{


}

