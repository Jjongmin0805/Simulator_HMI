

// Simulator_SLDView.cpp: CSimulatorSLDView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Simulator_SLD.h"
#endif

#include "MainFrm.h"
#include "Simulator_SLDDoc.h"
#include "Simulator_SLDView.h"

#include "FaultPosSetDlg.h"
#include "OutputFileOptDlg.h"

#include "VVMSetDlg.h"

#include "RelaySetDlg.h"
#include "RelcoserSetDlg.h"
#include "DgSetDlg.h"
#include "CustSetDlg.h"
#include "CEFISetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSimulatorSLDView

IMPLEMENT_DYNCREATE(CSimulatorSLDView, CView)

BEGIN_MESSAGE_MAP(CSimulatorSLDView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_MESSAGE(WM_FINDOBJ_MSG, &CSimulatorSLDView::OnFindObjPosition)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_SET_FAULT, &CSimulatorSLDView::OnSetFault)
	ON_MESSAGE(WM_NAVIGATOR_MSG, &CSimulatorSLDView::OnMovePosition)
	ON_MESSAGE(DFDFIGENERATOR_MSG, &CSimulatorSLDView::OnDfdGeneratorFunc)
	ON_UPDATE_COMMAND_UI(IDM_SET_FAULT, &CSimulatorSLDView::OnUpdateSetFault)
	ON_COMMAND(IDM_RESET_FAULT, &CSimulatorSLDView::OnResetFault)
	ON_UPDATE_COMMAND_UI(IDM_RESET_FAULT, &CSimulatorSLDView::OnUpdateResetFault)
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_FAULTPOS, &CSimulatorSLDView::OnMenuFaultpos)
	ON_COMMAND(ID_MENU_HIDE, &CSimulatorSLDView::OnMenuHide)
	ON_COMMAND(ID_MENU_PRINT_IMP, &CSimulatorSLDView::OnMenuPrintImp)
	ON_COMMAND(ID_MENU_PRDE_SET, &CSimulatorSLDView::OnMenuPrdeSet)
	ON_UPDATE_COMMAND_UI(ID_MENU_PRDE_SET, &CSimulatorSLDView::OnUpdateMenuPrdeSet)
	ON_COMMAND(IDM_VVM_SET, &CSimulatorSLDView::OnVvmSet)
END_MESSAGE_MAP()

// CSimulatorSLDView 생성/소멸

CSimulatorSLDView::CSimulatorSLDView() noexcept
{
	m_pNaviDlg = NULL;
	m_pSLDBuffer = NULL;
	m_pSLDBitmap = NULL;
	m_sizeMaxSLD = CSize(0, 0);
	m_sizeCurSLD = CSize(0, 0);
	m_ptPosition = CPoint(0, 0);
	m_bLButtonDown = FALSE;

	m_nDLIdx = 0;
	m_dStZoomScale = m_dZoomScale = 1;

	m_pNodeView = NULL;
	m_pBranchView = NULL;

	m_pTooltipNodeView = NULL;
	m_pTooltipBranchView = NULL;

	m_pSelectNodeView = NULL;
	m_pSelectBranchView = NULL;

	m_nSLDMode = SHOW_SLDMODE_ALL;
	m_nDeadLineDepthSet = 1;

	m_pFindDlg = NULL;

	m_pSetDfdDlg = NULL;

	m_pContextBranch = NULL;
	m_pFaultBranch = NULL;

	m_bAction = FALSE;

	m_nViewMode = SHOW_VIEWMODE_SINGLE;
	m_nGisMode = SHOW_GISMODE_SINGLE;

	m_dMinZoomScale = 0;
	m_szImgPath = _T(""); 
	m_pGISBuffer = NULL;
	m_pGISBitmap = NULL;
	m_nZoomLevel = 0;
	m_dZoom = 0;
	m_ptGisPosition = CPoint(0, 0);

	m_nShowOption = 0;

	m_nSLDStep = 0;
	m_nGISStep = 0;

	InitTooltip();

	m_bReverseColor = FALSE;
}

CSimulatorSLDView::~CSimulatorSLDView()
{
	DeleteSLDBuffer();
	DeleteGISBuffer();

	if (m_pNodeView)																delete m_pNodeView;
	m_pNodeView = NULL;

	if (m_pBranchView)																delete m_pBranchView;
	m_pBranchView = NULL;

	m_nDLIdx = 0;

	if (m_pNaviDlg)
	{
		delete m_pNaviDlg;
		m_pNaviDlg = NULL;
	}

	if (m_pFindDlg)
	{
		delete m_pFindDlg;
		m_pFindDlg = NULL;
	}

	if (m_pSetDfdDlg)
	{
		delete m_pSetDfdDlg;
		m_pSetDfdDlg = NULL;
	}

	for (int i = 0; i < m_pGisObjArr.GetSize(); i++)
		delete m_pGisObjArr.GetAt(i);
	m_pGisObjArr.RemoveAll();

	for (int i = 0; i < m_pGisSecArr.GetSize(); i++)
		delete m_pGisSecArr.GetAt(i);
	m_pGisSecArr.RemoveAll();

	theAppDataMng->DIsConnectKASIMData(0);
	theAppDataMng->Close();
	theUtil->Close();
}

BOOL CSimulatorSLDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

CString CSimulatorSLDView::GetModulePath()
{
	CString																			sPath;
	GetModuleFileName(AfxGetApp()->m_hInstance, sPath.GetBuffer(MAX_PATH), MAX_PATH);
	sPath.ReleaseBuffer();

	int																				nPos;
	nPos = sPath.ReverseFind(_T('\\'));
	if (nPos > -1)
		sPath = sPath.Left(nPos);

	return sPath;
}

int CSimulatorSLDView::SetSLDMode(int nMode)
{
	if (m_nSLDMode == nMode)					return 0;

	m_nSLDMode = nMode;
	return m_nDLIdx;
}

// CSimulatorSLDView 그리기
void CSimulatorSLDView::OnDraw(CDC* pDC)
{
	CSimulatorSLDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CRect _rect;
	GetClientRect(&_rect);

	// 호환성 있는 메모리 DC를 생성(더블버퍼)
	CDC					BufferDC, tmpDC;
	BufferDC.CreateCompatibleDC(pDC);
	tmpDC.CreateCompatibleDC(pDC);

	// 메모리 비트맵 선언
	CBitmap				bmpBuffer, *pOldBitmap;

	// 호환성 있는 메모리 비트맵 생성하여 메모리 DC에 설정
	bmpBuffer.CreateCompatibleBitmap(pDC, _rect.Width(), _rect.Height());
	pOldBitmap = (CBitmap *)BufferDC.SelectObject(&bmpBuffer);

	if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
	{
		double dRatio;
		dRatio = (double)m_nSLDStep / SIMULATION_SLD_STEP;
		
		int r, g, b;
		r = (int)(220 * dRatio);
		g = (int)(220 * dRatio);
		b = (int)(220 * dRatio);
		BufferDC.FillSolidRect(0, 0, _rect.Width(), _rect.Height(), RGB(r, g, b));
		//////////////////////////////////////////////////////////////////////////
		//여기서 BufferDC에 그리자
		if (m_pSLDBuffer)
		{
			BufferDC.BitBlt(0, 0, _rect.Width(), _rect.Height(), m_pSLDBuffer, -m_ptPosition.x, -m_ptPosition.y, SRCCOPY);
		}
		//
		//////////////////////////////////////////////////////////////////////////
	}
	else
	{
		BufferDC.FillSolidRect(0, 0, _rect.Width(), _rect.Height(), GISVIEW_BACKGROUND_COLOR);
		//////////////////////////////////////////////////////////////////////////
		//여기서 BufferDC에 그리자
		if (m_pGISBuffer)
		{
			BufferDC.BitBlt(-m_ptGisPosition.x, -m_ptGisPosition.y, _rect.Width(), _rect.Height(), m_pGISBuffer, 0, 0, SRCCOPY);
		}
		//
		//////////////////////////////////////////////////////////////////////////
	}

	int nLoofCBSize = m_nLoofCBIdArr.GetSize();
	if (nLoofCBSize)
	{
		CString															szData;
		CPen															pen, *poldpen;
		CBrush															brush, *poldbrush;
		CFont															font, *poldfont;

		pen.CreatePen(PS_SOLID, 1, RGB(255,255,0));
		poldpen															= BufferDC.SelectObject(&pen);

		brush.CreateSolidBrush(RGB(255, 0, 0));
		poldbrush														= BufferDC.SelectObject(&brush);

		font.CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
		poldfont														= pDC->SelectObject(&font);

		BufferDC.SetBkMode(TRANSPARENT);
		BufferDC.SetTextColor(RGB(255, 255, 255));

		int																nHeight(30);
		CRect															rArea;
		rArea.left														= 15;
		rArea.bottom													= (_rect.bottom - 15);
		rArea.right														= (rArea.left + 230);
		rArea.top														= (rArea.bottom - (nHeight * nLoofCBSize));

		BufferDC.RoundRect(rArea, CPoint(12, 12));

		rArea.left += 10;
		rArea.right -= 10;
		rArea.bottom = rArea.top + nHeight;
		for (int i = 0; i < nLoofCBSize; i++)
		{
			szData.Format(_T("선로간 루프 : %s"), m_szLoofCBNmArr.GetAt(i));
			BufferDC.DrawText(szData, rArea, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

			if (i != nLoofCBSize - 1)
			{
				BufferDC.MoveTo(rArea.left, rArea.bottom);
				BufferDC.LineTo(rArea.right, rArea.bottom);

				rArea.top += nHeight;
				rArea.bottom = rArea.top + nHeight;
			}
		}

		BufferDC.SetTextColor(DEFALUT_TEXT_COLOR);

		BufferDC.SelectObject(poldpen);
		pen.DeleteObject();

		BufferDC.SelectObject(poldbrush);
		brush.DeleteObject();

		BufferDC.SelectObject(poldfont);
		font.DeleteObject();
	}

	// 메모리 DC에 그려진 비트맵을 화면으로 전송	
	pDC->BitBlt(0, 0, _rect.Width(), _rect.Height(), &BufferDC, 0, 0, SRCCOPY);
	// 메모리 DC 복원 및 삭제
	BufferDC.SelectObject(pOldBitmap);
	BufferDC.DeleteDC();

	UpdateNavigator();
}

// CSimulatorSLDView 진단

#ifdef _DEBUG
void CSimulatorSLDView::AssertValid() const
{
	CView::AssertValid();
}

void CSimulatorSLDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimulatorSLDDoc* CSimulatorSLDView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimulatorSLDDoc)));
	return (CSimulatorSLDDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimulatorSLDView 메시지 처리기
BOOL CSimulatorSLDView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam == 70) && (GetKeyState(VK_CONTROL) < 0)) //Ctrl + F -> 객체찾기
			FindObject();
	}

	m_ToolTip.RelayEvent(pMsg);
	return CView::PreTranslateMessage(pMsg);
}

void CSimulatorSLDView::InitTooltip()
{
	m_ToolTip.Create(this); //. 생성
	m_ToolTip.Hide();

	CMFCToolTipInfo																	param;
	param.m_bBalloonTooltip = TRUE;
	param.m_bDrawIcon = TRUE;
	param.m_bDrawDescription = TRUE;
	param.m_bRoundedCorners = TRUE;
	param.m_bBoldLabel = TRUE;
	param.m_bDrawSeparator = TRUE;
	param.m_bVislManagerTheme = FALSE;
	param.m_nMaxDescrWidth = 500;
	param.m_nGradientAngle = 45;
	param.m_clrFill = (COLORREF)RGB(21, 48, 85);
	param.m_clrFillGradient = (COLORREF)RGB(14, 19, 34);
	param.m_clrText = (COLORREF)RGB(153, 193, 225);
	param.m_clrBorder = (COLORREF)RGB(3, 25, 43);

	m_ToolTip.SetParams(&param);
}

void CSimulatorSLDView::SetToolTip(CString szMessage)
{
	m_ToolTip.Hide();
	m_ToolTip.AddTool(this, szMessage, NULL, 0);
	m_ToolTip.Show();
}

CString CSimulatorSLDView::GetTooltipMsg(CNodeView* pNodeView)
{
	CString																			szMessage = _T("");
	CString																			szTemp;

	if (m_nViewMode == SHOW_VIEWMODE_SINGLE && !m_bAction)
	{
		if (pNodeView)
		{
			if (pNodeView->IsCBreaker())
			{
				szTemp.Format(_T(" 설비ID: %d \n"), pNodeView->m_nDbID);
				szMessage += szTemp;

				szTemp.Format(_T(" CEQID: %s \n"), pNodeView->m_szCEQID);
				szMessage += szTemp;

				szTemp.Format(_T(" 변전소명: %s \n"), pNodeView->m_szLocNo);
				szMessage += szTemp;

				szTemp.Format(_T(" 선로명: %s \n"), pNodeView->m_szLoc);
				szMessage += szTemp;

				szTemp.Format(_T(" 설비종류: %s \n"), _T("CB"));
				szMessage += szTemp;

				szTemp.Format(_T(" 설비상태: %s \n"), pNodeView->m_bStatus == SW_OPEN ? _T("개방") : _T("투입"));
				szMessage += szTemp;

				szTemp.Format(_T(" F-NODE: %d \n"), pNodeView->m_nNDID[0]);
				szMessage += szTemp;

				szTemp.Format(_T(" T-NODE: %d "), pNodeView->m_nNDID[1]);
				szMessage += szTemp;
			}
			else if (pNodeView->IsSwitch())
			{
				szTemp.Format(_T(" 설비ID: %d \n"), pNodeView->m_nDbID);
				szMessage += szTemp;

				szTemp.Format(_T(" CEQID: %s \n"), pNodeView->m_szCEQID);
				szMessage += szTemp;

				szTemp.Format(_T(" 전주번호: %s \n"), pNodeView->m_szLoc);
				szMessage += szTemp;

				szTemp.Format(_T(" 설비종류: %s \n"), pNodeView->GetKindName());
				szMessage += szTemp;

				szTemp.Format(_T(" 설비상태: %s \n"), pNodeView->m_bStatus == SW_OPEN ? _T("개방") : _T("투입"));
				szMessage += szTemp;

				szTemp.Format(_T(" F-NODE: %d \n"), pNodeView->m_nNDID[0]);
				szMessage += szTemp;

				szTemp.Format(_T(" T-NODE: %d "), pNodeView->m_nNDID[1]);
				szMessage += szTemp;
			}
			else if (pNodeView->m_nSwKindID == NDTYPE_BACKUP)
			{
				szTemp.Format(_T(" 설비ID: %d \n"), pNodeView->m_nDbID);
				szMessage += szTemp;

				szTemp.Format(_T(" 변전소명: %s \n"), pNodeView->m_szLocNo);
				szMessage += szTemp;

				szTemp.Format(_T(" 선로명: %s"), pNodeView->m_szLoc);
				szMessage += szTemp;
			}
			else
			{
				szTemp.Format(_T(" 설비ID: %d \n"), pNodeView->m_nDbID);
				szMessage += szTemp;

				if (!pNodeView->m_szCEQID.IsEmpty())
				{
					szTemp.Format(_T(" CEQID: %s \n"), pNodeView->m_szCEQID);
					szMessage += szTemp;
				}

				szTemp.Format(_T(" 전주번호: %s \n"), pNodeView->m_szLoc);
				szMessage += szTemp;

				szTemp.Format(_T(" 설비종류: %s \n"), pNodeView->GetKindName());
				szMessage += szTemp;

				if (pNodeView->m_nNDID[1] == 0)//DUMMY, SVR, GEN....등
				{
					szTemp.Format(_T(" NODE: %d "), pNodeView->m_nNDID[0]);
					szMessage += szTemp;
				}
				else
				{
					szTemp.Format(_T(" F-NODE: %d \n"), pNodeView->m_nNDID[0]);
					szMessage += szTemp;

					szTemp.Format(_T(" T-NODE: %d "), pNodeView->m_nNDID[1]);
					szMessage += szTemp;
				}
			}
		}
	}

	return szMessage;
}

CString CSimulatorSLDView::GetTooltipMsg(CBranchView* pBranchView)
{
	CString																			szMessage = _T("");
	CString																			szTemp;

	if (m_nViewMode == SHOW_VIEWMODE_SINGLE && !m_bAction )
	{
		if (pBranchView)
		{
			// 		CString																		szPhase(_T("")), szNeutral(_T(""));

			szTemp.Format(_T(" 구간ID: %d \n"), pBranchView->m_nDbID);
			szMessage += szTemp;

			szTemp.Format(_T(" CEQ ID: %s \n"), pBranchView->m_szCeqID);
			szMessage += szTemp;

			szTemp.Format(_T(" 전원측설비ID: %d \n"), pBranchView->m_nNode1);
			szMessage += szTemp;

			szTemp.Format(_T(" 부하측설비ID: %d \n"), pBranchView->m_nNode2);
			szMessage += szTemp;

			szTemp.Format(_T(" 정상_R: %.3lf \n"), pBranchView->m_dRp);
			szMessage += szTemp;

			szTemp.Format(_T(" 정상_X: %.3lf \n"), pBranchView->m_dXp);
			szMessage += szTemp;

			szTemp.Format(_T(" 영상_R: %.3lf \n"), pBranchView->m_dR0);
			szMessage += szTemp;

			szTemp.Format(_T(" 영상_X: %.3lf \n"), pBranchView->m_dX0);
			szMessage += szTemp;
		}
	}

	return szMessage;
}

void CSimulatorSLDView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
}

void CSimulatorSLDView::SetNaviPosition()
{
	if (m_pNaviDlg)
	{
		CRect																		rectWnd;
		GetWindowRect(&rectWnd);

		CSize																		sizeNavi;
		sizeNavi = m_pNaviDlg->GetWindowSize();

		m_pNaviDlg->MoveWindow(rectWnd.left + 5, rectWnd.top + 5, sizeNavi.cx, sizeNavi.cy);
	}
}

void CSimulatorSLDView::ShowNavi(BOOL bShow)
{
	if (m_pNaviDlg)																	m_pNaviDlg->ShowNavi(bShow);
}

int CSimulatorSLDView::IsShowNavi()
{
	if (m_pNaviDlg)																	return (int)m_pNaviDlg->IsShowNavi();
	else																			return 1;
}

void CSimulatorSLDView::UpdateNavigator()
{
	if (m_pNaviDlg == NULL)															return;
	m_pNaviDlg->SetViewMode(m_nViewMode);

	CRect																			rect;
	GetClientRect(&rect);

	if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
	{
		rect.OffsetRect(-m_ptPosition.x, -m_ptPosition.y);

		rect.left /= m_dZoomScale;
		rect.top /= m_dZoomScale;
		rect.right /= m_dZoomScale;
		rect.bottom /= m_dZoomScale;

		m_pNaviDlg->SetNaviRatio(rect);
		m_pNaviDlg->UpData(m_pNodeView, m_pBranchView);
	}
	else
	{
		m_pNaviDlg->SetGISRectNavi(rect, m_dZoom, &m_dpOfficeCenter_utm);
	}
}

void CSimulatorSLDView::MakeSLD(int nDLIdx)
{
	//선택된설비정보를 지운다.
	SetSelectDraw(NULL);

	//단선도 메모리 초기화
	DeleteSLDBuffer();//기존 단선도 버퍼를 지움.

	if (m_pNodeView)
	{
		delete m_pNodeView;
		m_pNodeView = NULL;
	}

	if (m_pBranchView)
	{
		delete m_pBranchView;
		m_pBranchView = NULL;
	}
	//////////////////////////////////////////////////////////////////////////
	m_dl = m_dt = 99999999;
	m_dr = m_db = 0;

	BOOL																			bShow(FALSE);
	if (nDLIdx != m_nDLIdx)															bShow = TRUE;

	m_nDLIdx = nDLIdx;

	int																				nSwIdx = 0;
	int																				nCount(theAppDataMng->GetTableRealCount(_T("cbsw_sta")));
	for (int nPos = 1; nPos <= nCount; nPos++)
	{
		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nPos) != 1)			continue;//CB가 아니면 패스...
		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), nPos) == m_nDLIdx)
		{
			nSwIdx = nPos;
			break;
		}
	}

	if (nSwIdx <= 0)
	{
		//DL목록이 있는데 CBSW에 CB정보가 없다?
		AfxMessageBox(_T("cbsw_sta에서 CB정보를 찾을수 없습니다!"));
		return;
	}

	m_nNodeID = 1;

	//CB NODE만들기
	m_pNodeView = new CNodeView();
	m_pNodeView->m_nDbID = m_nNodeID++;
	m_pNodeView->m_szLoc = GETSTRING(_T("cbsw_sta"), _T("cbsw_nm"), nSwIdx);
	m_pNodeView->m_nSwKindID = NDTYPE_SWITCH;
	m_pNodeView->m_nKCIMType = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nSwIdx);
	m_pNodeView->m_nCeqType = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_rtutype"), nSwIdx);
	m_pNodeView->m_bStatus = GetSwStatus(nSwIdx);
	m_pNodeView->m_szLocNo = _T("");
	m_pNodeView->m_nTongID = 0;
	m_pNodeView->m_nCaption = 0;
	m_pNodeView->m_szCEQID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("cbsw_sta"), _T("cbsw_ceqid"), nSwIdx));

	m_pNodeView->m_nFromND = -1;

	int																				nMTRIdx, nSSIdx;
	if (nDLIdx)
	{
		nMTRIdx = GETVALUE(int, _T("dl_sta"), _T("dl_ii_mtr"), nDLIdx);
		if (nMTRIdx)
		{
			nSSIdx = GETVALUE(int, _T("mtr_sta"), _T("mtr_ii_ss"), nMTRIdx);
			if (nSSIdx)
			{
				m_pNodeView->m_szLocNo = GETSTRING(_T("ss_sta"), _T("ss_nm"), nSSIdx);
			}
		}
	}
	//

	//사활선 구간 설정
	int																				nDeadLineDepth = 0;
	if (m_pNodeView->m_bStatus == SW_OPEN)
	{
		int nGND, nGBR;
		nGND = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tgnd"), nSwIdx);
		nGBR = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), (nGND));

		if (nGBR > 0)
		{
			if (IsFaultOperSw(nGND))
			{
				nDeadLineDepth = 1000;
			}
			else
			{
				if (!FindCB(-1, nGND))												nDeadLineDepth++;//사선
			}
		}
		else
		{
			return;
		}
	}
	//

	//BRANCH 메모리생성하고 시작.
	m_pBranchView = new CBranchView();

	nCount = theAppDataMng->GetTableRealCount(_T("br_sta"));
	m_pBRTrace = new BYTE[nCount];
	memset(m_pBRTrace, 0x00, sizeof(BYTE) * nCount);

	nCount = theAppDataMng->GetTableRealCount(_T("nd_sta"));
	m_pNDTrace = new BYTE[nCount];
	memset(m_pNDTrace, 0x00, sizeof(BYTE) * nCount);

	m_pNodeView->m_nNDID[0] = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nSwIdx);
	m_pNodeView->m_nNDID[1] = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nSwIdx);

	int																			nfromNDIdx;
	int																			nBRIdx;
	
	nfromNDIdx = m_pNodeView->m_nNDID[1];
	nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nfromNDIdx);
	if (nBRIdx == 0)
		nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nfromNDIdx);

// 	int																			nSnvIdx;
// 	nSnvIdx																		= GETVALUE(int, _T("nd_sta"), _T("nd_ii_snv"), m_pNodeView->m_nNDID[0]);
// 	if (nSnvIdx && GETVALUE(double, _T("snv_sta"), _T("snv_norkv"), nSnvIdx) <= 22.9)
// 	{
// 		nfromNDIdx = m_pNodeView->m_nNDID[0];
// 		nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), m_pNodeView->m_nNDID[0]);
// 		if (nBRIdx == 0)
// 			nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), m_pNodeView->m_nNDID[0]);
// 	}
// 	else
// 	{
// 		nfromNDIdx = m_pNodeView->m_nNDID[1];
// 		nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), m_pNodeView->m_nNDID[1]);
// 		if (nBRIdx == 0)
// 			nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), m_pNodeView->m_nNDID[1]);
// 	}

	m_nLoofCBIdArr.RemoveAll();
	m_szLoofCBNmArr.RemoveAll();
// 	m_nLoofCBIdArr.Add(m_pNodeView->m_nNDID[0]);
// 	m_szLoofCBNmArr.Add(_T("국촌/국촌"));
// 	m_nLoofCBIdArr.Add(m_pNodeView->m_nNDID[0]);
// 	m_szLoofCBNmArr.Add(_T("국촌/국촌"));
// 	m_nLoofCBIdArr.Add(m_pNodeView->m_nNDID[0]);
// 	m_szLoofCBNmArr.Add(_T("국촌/국촌"));

	m_pNDTrace[m_pNodeView->m_nNDID[0] - 1] = TRUE;
	m_pNDTrace[m_pNodeView->m_nNDID[1] - 1] = TRUE;
	MakeAllSLDRcv(nBRIdx, nfromNDIdx, m_pNodeView, m_pBranchView, nDeadLineDepth);

	delete[] m_pBRTrace;
	delete[] m_pNDTrace;


	CNodeView*																		pNode;
	while ((pNode = m_pNodeView->FindUnsetNode(1)) != NULL)
	{
		// 어느 노드로부터 말단의 가장 긴 분기가 가운데로 오도록 함
		pNode->SetLongestPathToCenter(pNode->GetLongestPathLength(m_pBranchView), 0, m_pBranchView);
	}

	// 	//4회로 초과분기가 있으면 대각으로 뻗는 5이상 분기에 가장 짧은 분기가 오도록 한다.
	m_pNodeView->SetShortestPathDiagonal(m_pBranchView);
	// 	//화면을 기준으로 왼쪽이 길면 오른쪽으로 위쪽이 길면 아래쪽으로 이동함(간선기준 하단 배치기준)->필요없어짐! 아래에서 한번에 처리함.
	// 	pNodeView->SetLongestPathToRightBottom(0, pBranchView);
	// 	// 꺽기 2 마지막부터 홀수번째에 해당되는 Center에서 좌우 비교 후 지그재그로 배치
	m_pNodeView->BreakNode(m_pBranchView);
	//방향에 따라 좌표를 생성함
	m_pNodeView->CalculateAxis(0, 0, 0, 0, 0, m_pBranchView, NULL);

	// 겹친 노드 처리
	while (m_pNodeView->CheckPosition(m_pNodeView, m_pBranchView))
	{
		m_pNodeView->CalculateAxis(0, 0, 0, 0, 0, m_pBranchView, NULL);
	}

	//////////////////////////////////////////////////////////////////////////
	//불필요하게 늘어난 구간 다시축소(보정용)-느리면 그냥 하지말자!
	if (m_pBranchView)
		CheckBranchView(m_pBranchView, m_pNodeView, m_pBranchView);
	//////////////////////////////////////////////////////////////////////////

	//다회로단자 및 백업표시 좌표조정
	m_pNodeView->SetPosition();

	//단선도좌표를 화면좌표로 변경. 
	int																				nMinX = m_pNodeView->GetMinAxisX();
	int																				nMinY = m_pNodeView->GetMinAxisY();
	m_pNodeView->ShiftPosition(abs(nMinX) + SLDVIEW_WIDTH_MARGIN, abs(nMinY) + SLDVIEW_HEIGHT_MARGIN);
	//////////////////////////////////////////////////////////////////////////

	//구간좌표생성
	m_pNodeView->SetBranchPosition(m_pBranchView);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//단선도 메모리버퍼를 최대확대크기로 한번 생성해 놓자( 메모리 버퍼를 만들때 시간이 걸려서 확대축소시 다시 만들지 말자 )
	//단선도의 전체 사이즈를 가져온다.
	double																			dZoomScale;
	dZoomScale = m_dZoomScale;
	m_dZoomScale = SLDVIEW_ZOOM_MAX;

	m_sizeMaxSLD.cx = GetMaxSizeX(FALSE);
	m_sizeMaxSLD.cy = GetMaxSizeY(FALSE);

	m_dZoomScale = dZoomScale;

	//단선도를 담아놓을 버퍼를 생성.
	CClientDC																		dc(this);
	m_pSLDBuffer = new CDC();

	//메모리 DC를 생성(더블버퍼용)
	m_pSLDBuffer->CreateCompatibleDC(&dc);

	// 메모리 비트맵 선언
	CBitmap bmpBuffer;

	// 호환성 있는 메모리 비트맵 생성하여 메모리 DC에 설정(메모리 버퍼사이즈는 단선도 최대사이즈로 한번만 생성)
	bmpBuffer.CreateCompatibleBitmap(&dc, m_sizeMaxSLD.cx, m_sizeMaxSLD.cy);
	m_pSLDBitmap = (CBitmap *)m_pSLDBuffer->SelectObject(&bmpBuffer);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	((CMainFrame *)AfxGetMainWnd())->SetSelectDLIdx(m_nDLIdx);
	if (bShow)
	{
		((CMainFrame *)AfxGetMainWnd())->ShowDLInfo();
	}
}

void CSimulatorSLDView::CheckBranchView(CBranchView* pTargetBranch, CNodeView* pNodeView, CBranchView* pBranchView)
{
	while (pTargetBranch->GetLengthDisp() > 1)
	{
		double																		dLength;
		dLength = pTargetBranch->GetLengthDisp();
		pTargetBranch->SetLengthDisp(dLength - 1);
		pNodeView->CalculateAxis(0, 0, 0, 0, 0, pBranchView, NULL);

		if (pNodeView->IsOverlapNode(pNodeView, pBranchView))
		{
			pTargetBranch->SetLengthDisp(dLength);
			pNodeView->CalculateAxis(0, 0, 0, 0, 0, pBranchView, NULL);
			break;
		}
	}

	if (pTargetBranch->m_pNext)
	{
		CheckBranchView(pTargetBranch->m_pNext, pNodeView, pBranchView);
	}
}
void CSimulatorSLDView::MakeSLDBuffer(BOOL bInit)
{
	if (m_nDLIdx <= 0)																return;
	if (m_pSLDBuffer == NULL)														return;

	//단선도의 현재 사이즈를 가져온다.
	m_sizeCurSLD.cx = GetMaxSizeX(FALSE);
	m_sizeCurSLD.cy = GetMaxSizeY(FALSE);

	//여기서 메모리DC에 단선도를 그린다.
	CPoint ptStart;
	ptStart = DrawSLD(m_pSLDBuffer, TRUE);//CB의 좌표를 넘겨받고 화면의 가운데로 배치하자.

	//화면좌표를 가져와서 단선로를 그릴 중심위치를 설정(CB의 위치)
	if (bInit)
	{
		CRect																		rect;
		GetClientRect(&rect);

		//화면이동 좌표를 초기화하고,
		m_ptPosition = CPoint(0, 0);

		//CB의 좌표를 200, Center.y에 맞춘다.
		ptStart.x *= m_dZoomScale;
		ptStart.y *= m_dZoomScale;

		SetShiftPosition(CPoint((200 - ptStart.x), (rect.CenterPoint().y - ptStart.y)));
	}
	m_ptPosition;
	if (m_pNaviDlg)																m_pNaviDlg->SetNaviSLDRatio(GetMaxSizeX(TRUE), GetMaxSizeY(TRUE));

	Invalidate();
}

void CSimulatorSLDView::SetSelectDraw(CNodeView* pSelectNodeView)
{
	if (m_pSelectNodeView != pSelectNodeView)
	{
		m_pSelectNodeView = pSelectNodeView;

		//////////////////////////////////////////////////////////////////////////
		if (m_pSelectNodeView && (m_pSelectNodeView->m_nSwKindID != NDTYPE_BACKUP))
		{
			int																		nBRIdx(0), nType(0);
			GetBRIdx(m_pSelectNodeView, nBRIdx, nType);

			((CMainFrame *)AfxGetMainWnd())->SetGroup1CompData(m_pSelectNodeView, m_nDLIdx);

			((CMainFrame *)AfxGetMainWnd())->SetGroup1MeasData(nType, nBRIdx);

			((CMainFrame *)AfxGetMainWnd())->SetGroup1ApplData(nType, nBRIdx);
		}
		else
		{
			((CMainFrame *)AfxGetMainWnd())->SetGroup1CompData(NULL, 0);

			((CMainFrame *)AfxGetMainWnd())->SetGroup1MeasData(0, 0);

			((CMainFrame *)AfxGetMainWnd())->SetGroup1ApplData(0, 0);
		}
		//////////////////////////////////////////////////////////////////////////

		MakeSLDBuffer(FALSE);
	}
}

BOOL CSimulatorSLDView::IsFaultDL(int nDLIdx)
{
	// 	return TRUE;
	// 	//////////////////////////////////////////////////////////////////////////

	int															nFaultDLIdx;
	int															nCount(theAppDataMng->GetTableRealCount(_T("fltinfo_dyn_fio")));
	for (int i = 1; i <= nCount; i++)
	{
		nFaultDLIdx = GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_ii_dl"), i);
		if (nFaultDLIdx == 0)									break;

		if (nFaultDLIdx == nDLIdx)
			return TRUE;
	}

	return FALSE;
}


int CSimulatorSLDView::IsFaultOperSw(int nNDIdx)
{
	int															nCbswIdx, nisocbsw_ii_cbsw;
	nCbswIdx = GetCbswIdx(nNDIdx);
	if (nCbswIdx == 0)	return 0;

	int															nCount(theAppDataMng->GetTableRealCount(_T("isocbsw_dyn_dfdo")));
	for (int i = 1; i <= nCount; i++)
	{
		nisocbsw_ii_cbsw = GETVALUE(int, _T("isocbsw_dyn_dfdo"), _T("isocbsw_ii_cbsw"), i);
		if (nisocbsw_ii_cbsw == 0)								break;

		if (nCbswIdx == nisocbsw_ii_cbsw)
			return GETVALUE(int, _T("isocbsw_dyn_dfdo"), _T("isocbsw_updn"), i);
	}

	nCount = theAppDataMng->GetTableRealCount(_T("fltinfo_dyn_fio"));
	for (int i = 1; i <= nCount; i++)
	{
		nisocbsw_ii_cbsw = GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_ii_cbsw"), i);
		if (nisocbsw_ii_cbsw == 0)								break;

		if (nCbswIdx == nisocbsw_ii_cbsw)
			return 1;
	}

	nCount = theAppDataMng->GetTableRealCount(_T("dsrseq_dyn_dsro"));
	for (int i = 1; i <= nCount; i++)
	{
		nisocbsw_ii_cbsw = GETVALUE(int, _T("dsrseq_dyn_dsro"), _T("dsrseq_ii_cbsw"), i);
		if (nisocbsw_ii_cbsw == 0)								break;

		if (nCbswIdx == nisocbsw_ii_cbsw)
		{
			int													nstatus;
			nstatus = GETVALUE(int, _T("dsrseq_dyn_dsro"), _T("dsrseq_before_state"), i);

			if (nstatus == 2)									return 3;//현재상태가 CLOSE이면 분할개폐기
		}
	}

	return 0;
}

int CSimulatorSLDView::IsDSROperSw(int nNDIdx)
{
	int															nCbswIdx, nisocbsw_ii_cbsw;
	nCbswIdx = GetCbswIdx(nNDIdx);

	int															nCount(theAppDataMng->GetTableRealCount(_T("dsrseq_dyn_dsro")));
	for (int i = 1; i <= nCount; i++)
	{
		nisocbsw_ii_cbsw = GETVALUE(int, _T("dsrseq_dyn_dsro"), _T("dsrseq_ii_cbsw"), i);
		if (nisocbsw_ii_cbsw == 0)								break;


		if (nCbswIdx == nisocbsw_ii_cbsw)
		{
			int													nstatus;
			nstatus = GETVALUE(int, _T("dsrseq_dyn_dsro"), _T("dsrseq_before_state"), i);

			if (nstatus == 1)									return TRUE;//현재상태가 OPEN이면 절체개폐기
		}
	}

	return 0;
}

int CSimulatorSLDView::GetCbswIdx(int nNDIdx)
{
	if (nNDIdx == 0)											return 0;

	int															nCbswIdx;
	nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
	if (nCbswIdx)												return nCbswIdx;

	nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);
	if (nCbswIdx)												return nCbswIdx;

	return 0;
}

void CSimulatorSLDView::DeleteSLDBuffer()
{
	if (m_pFaultBranch)															m_pFaultBranch = NULL;

	if (m_pSLDBuffer)
	{
		ClearBoundaryCheck(TRUE);

		m_pSLDBuffer->SelectObject(m_pSLDBitmap);
		m_pSLDBuffer->DeleteDC();

		delete m_pSLDBuffer;
		m_pSLDBuffer = NULL;
	}
}

void CSimulatorSLDView::DeleteGISBuffer()
{
	if (m_pGISBuffer)
	{
		m_pGISBuffer->SelectObject(m_pGISBitmap);
		m_pGISBuffer->DeleteDC();

		delete m_pGISBuffer;
		m_pGISBuffer = NULL;
	}
}

int CSimulatorSLDView::GetMaxSizeX(BOOL bDefaultSize)
{
	int																				nMax(0), nScale;
	if (m_pNodeView)																nMax = m_pNodeView->GetMaxAxisX();

	double																			dScale(1);
	if (!bDefaultSize)																dScale = m_dZoomScale;

	nScale = (int)(nMax*dScale) + SLDVIEW_WIDTH_MARGIN;//마진을 남김
	if (nScale > 30000)																nScale = 31000;
	return nScale;
}

int CSimulatorSLDView::GetMaxSizeY(BOOL bDefaultSize)
{
	int																				nMax(0), nScale;
	if (m_pNodeView)																nMax = m_pNodeView->GetMaxAxisY();

	double																			dScale(1);
	if (!bDefaultSize)																dScale = m_dZoomScale;

	nScale = (int)(nMax*dScale) + SLDVIEW_HEIGHT_MARGIN;//마진을 남김
	if (nScale > 17000)																nScale = 17000;
	return nScale;
}

CPoint CSimulatorSLDView::DrawSLD(CDC* BufferDC, BOOL bShow)
{
	double dRatio;
	dRatio = (double)m_nSLDStep / SIMULATION_SLD_STEP;

	int r, g, b;
	r = (int)(220 * dRatio);
	g = (int)(220 * dRatio);
	b = (int)(220 * dRatio);
	BufferDC->FillSolidRect(0, 0, m_sizeMaxSLD.cx, m_sizeMaxSLD.cy, RGB(r, g, b));

	if (m_pNodeView == NULL)														return CPoint(0, 0);

	BufferDC->SetTextAlign(TA_LEFT);
	BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
	BufferDC->SetBkMode(TRANSPARENT);

	BOOL																			bShowValue(TRUE);
	CFont																			font, *pOldfont;
	font.CreateFont(12, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("굴림체"));
	pOldfont = BufferDC->SelectObject(&font);

	BOOL bFirst(TRUE);
	CBranchView* pBrenchView;
	pBrenchView = m_pBranchView;
	while (pBrenchView)
	{
		pBrenchView->Draw(BufferDC, m_dZoomScale, m_nShowOption, bFirst, FALSE);

		bFirst = FALSE;
		pBrenchView = pBrenchView->m_pNext;
	}

	m_pNodeView->Draw(BufferDC, m_dZoomScale, m_nShowOption, FALSE);
	if (m_pSelectNodeView)
		m_pSelectNodeView->SetSelectDraw(BufferDC);
	BufferDC->SelectObject(pOldfont);
	font.DeleteObject();

	if (bShowValue && (((CMainFrame *)AfxGetApp()->GetMainWnd())->GetShowSecMode() == 0) )
	{
		m_pBranchView->DrawMeasData(BufferDC, m_dZoomScale);

		if (m_nShowOption == 4)
		{
			font.CreateFont(11, 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("굴림체"));
			pOldfont = BufferDC->SelectObject(&font);

			m_pNodeView->DrawFIFlag(BufferDC, m_dZoomScale);

			BufferDC->SelectObject(pOldfont);
			font.DeleteObject();
		}
	}


	return CPoint(m_pNodeView->m_nPosX, m_pNodeView->m_nPosY);//CB의 좌표를 넘김
}

void CSimulatorSLDView::SetShiftPosition(CPoint ptShift)
{
	m_ptPosition += ptShift;

	CRect																			_rect;
	GetClientRect(&_rect);

	if (m_ptPosition.x > _rect.CenterPoint().x - (SLDVIEW_WIDTH_MARGIN*m_dZoomScale))
		m_ptPosition.x = _rect.CenterPoint().x - (SLDVIEW_WIDTH_MARGIN*m_dZoomScale);
	if (m_ptPosition.y > _rect.CenterPoint().y - (SLDVIEW_HEIGHT_MARGIN*m_dZoomScale))
		m_ptPosition.y = _rect.CenterPoint().y - (SLDVIEW_HEIGHT_MARGIN*m_dZoomScale);

	if (m_sizeCurSLD.cx + m_ptPosition.x < _rect.CenterPoint().x + (SLDVIEW_WIDTH_MARGIN))
		m_ptPosition.x = _rect.CenterPoint().x + (SLDVIEW_WIDTH_MARGIN)-m_sizeCurSLD.cx;
	if (m_sizeCurSLD.cy + m_ptPosition.y < _rect.CenterPoint().y + (SLDVIEW_HEIGHT_MARGIN))
		m_ptPosition.y = _rect.CenterPoint().y + (SLDVIEW_HEIGHT_MARGIN)-m_sizeCurSLD.cy;
}

void CSimulatorSLDView::SetCenterPosition(CPoint ptCenter)
{
	CRect																			_rect;
	GetClientRect(&_rect);

	m_ptPosition.x = _rect.CenterPoint().x - ptCenter.x;
	m_ptPosition.y = _rect.CenterPoint().y - ptCenter.y;

	if (m_ptPosition.x > _rect.CenterPoint().x)									m_ptPosition.x = _rect.CenterPoint().x;
	if (m_ptPosition.y > _rect.CenterPoint().y)									m_ptPosition.y = _rect.CenterPoint().y;

	if (m_sizeCurSLD.cx + m_ptPosition.x < _rect.CenterPoint().x)					m_ptPosition.x = _rect.CenterPoint().x - m_sizeCurSLD.cx;
	if (m_sizeCurSLD.cy + m_ptPosition.y < _rect.CenterPoint().y)					m_ptPosition.y = _rect.CenterPoint().y - m_sizeCurSLD.cy;
}

BOOL CSimulatorSLDView::Zoom(int nMode)
{
	if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
	{
		if (nMode < 0)
		{
			if (m_dZoomScale <= SLDVIEW_ZOOM_MIN + 0.05)									return FALSE;
			m_dZoomScale -= 0.1;
		}
		else if (nMode > 0)
		{
			if (m_dZoomScale >= SLDVIEW_ZOOM_MAX - 0.05)									return FALSE;
			m_dZoomScale += 0.1;
		}
		else
		{
			if (m_dZoomScale == SLDVIEW_ZOOM_DEFAULT)										return FALSE;
			m_dZoomScale = 1;
		}
	}

	SetZoomMenuStatus();
	return TRUE;
}

void CSimulatorSLDView::SetZoomMenuStatus()
{
// 	if (m_dZoomScale >= SLDVIEW_ZOOM_MAX - 0.05)										((CMainFrame *)AfxGetMainWnd())->SetEnableMenu(5, FALSE);
// 	else																			((CMainFrame *)AfxGetMainWnd())->SetEnableMenu(5, TRUE);
// 
// 	if (m_dZoomScale <= SLDVIEW_ZOOM_MIN + 0.05)										((CMainFrame *)AfxGetMainWnd())->SetEnableMenu(6, FALSE);
// 	else																			((CMainFrame *)AfxGetMainWnd())->SetEnableMenu(6, TRUE);
// 
// 	if (m_dZoomScale >= SLDVIEW_ZOOM_DEFAULT - 0.05 && m_dZoomScale <= SLDVIEW_ZOOM_DEFAULT + 0.05)	((CMainFrame *)AfxGetMainWnd())->SetEnableMenu(7, FALSE);
// 	else																							((CMainFrame *)AfxGetMainWnd())->SetEnableMenu(7, TRUE);
}

BOOL CSimulatorSLDView::GetDirectPathRcv(CNodeView* pNodeView, int nTargetID, CNodeViewArray& pPathNodeView)
{
	if (pNodeView->m_bStatus == SW_OPEN)
		return FALSE;

	if (pNodeView->m_nDbID == nTargetID)
	{
		if (pNodeView->IsAuto())
			pPathNodeView.Add(pNodeView);

		return TRUE;
	}

	if (pNodeView->m_pCenter != NULL)
	{
		if (GetDirectPathRcv(pNodeView->m_pCenter, nTargetID, pPathNodeView))
		{
			if (pNodeView->IsAuto())
				pPathNodeView.InsertAt(0, pNodeView);

			return TRUE;
		}
	}
	if (pNodeView->m_pRight != NULL)
	{
		if (GetDirectPathRcv(pNodeView->m_pRight, nTargetID, pPathNodeView))
		{
			if (pNodeView->IsAuto())
				pPathNodeView.InsertAt(0, pNodeView);

			return TRUE;
		}
	}
	if (pNodeView->m_pLeft != NULL)
	{
		if (GetDirectPathRcv(pNodeView->m_pLeft, nTargetID, pPathNodeView))
		{
			if (pNodeView->IsAuto())
				pPathNodeView.InsertAt(0, pNodeView);

			return TRUE;
		}
	}
	if (pNodeView->m_pLeftTop != NULL)
	{
		if (GetDirectPathRcv(pNodeView->m_pLeftTop, nTargetID, pPathNodeView))
		{
			if (pNodeView->IsAuto())
				pPathNodeView.InsertAt(0, pNodeView);

			return TRUE;
		}
	}
	if (pNodeView->m_pRightBottom != NULL)
	{
		if (GetDirectPathRcv(pNodeView->m_pRightBottom, nTargetID, pPathNodeView))
		{
			if (pNodeView->IsAuto())
				pPathNodeView.InsertAt(0, pNodeView);

			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSimulatorSLDView::FindLoadSideRcv(CNodeView* pNodeView, CNodeViewArray& pLoadSideNodeView)
{
	if (pNodeView->m_bStatus == SW_OPEN)
		return FALSE;

	if (pNodeView->IsAuto())
	{
		pLoadSideNodeView.Add(pNodeView);
		return TRUE;
	}

	if (pNodeView->m_pCenter != NULL)												FindLoadSideRcv(pNodeView->m_pCenter, pLoadSideNodeView);
	if (pNodeView->m_pRight != NULL)												FindLoadSideRcv(pNodeView->m_pRight, pLoadSideNodeView);
	if (pNodeView->m_pLeft != NULL)													FindLoadSideRcv(pNodeView->m_pLeft, pLoadSideNodeView);
	if (pNodeView->m_pLeftTop != NULL)												FindLoadSideRcv(pNodeView->m_pLeftTop, pLoadSideNodeView);
	if (pNodeView->m_pRightBottom != NULL)											FindLoadSideRcv(pNodeView->m_pRightBottom, pLoadSideNodeView);

	return FALSE;
}

int	CSimulatorSLDView::GetTargetSwToGNode(int nGNDIdx, int& nType)
{
	nType = 0;
	int																				nCbswIdx(0);
	if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx) > 0)//cbsw와 연결된 노드.
	{
		if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0)			nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx);

		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCbswIdx) < 4)//자동화개폐기(CB, RC, SW)
		{
			nType = 1;
			return nCbswIdx;
		}
	}

	return 0;
}

LRESULT CSimulatorSLDView::OnDfdGeneratorFunc(WPARAM wParam, LPARAM lParam)
{
// 	if ((int)wParam == 99)//취소
// 	{
// 		ResetFault();
// 		MakeSLDBuffer(FALSE);
// 		delete m_pSetDfdDlg;
// 		m_pSetDfdDlg = NULL;
// 	}
// 	else if ((int)wParam == 1)//SCA
// 	{
// 		if ((int)lParam == 0)//미수행
// 		{
// 			Fault_Scenario();
// 		}
// 		else//수행
// 		{
// 
// 		}
// 	}
// 	else if ((int)wParam == 2)//DFD
// 	{
// 		if (m_pContextBranch)
// 		{
// 			if (m_pFaultBranch)													m_pFaultBranch->m_bFaultArea = FALSE;
// 
// 			m_pFaultBranch = m_pContextBranch;
// 			m_pFaultBranch->m_bFaultArea = TRUE;
// 		}
// 
// 		int																			nGBRIdx, nProtGNDIdx, nSCAExec(0), nFaType(0), nFiType(0), nNextCbswIndex(0);
// 		double																		dMinValue(0);
// 		nGBRIdx = m_pSetDfdDlg->m_nGBRIdx;
// 		nProtGNDIdx = m_pSetDfdDlg->m_nProtGNDIdx;
// 		nSCAExec = m_pSetDfdDlg->m_nSCAOption;
// 		nFaType = m_pSetDfdDlg->m_nFaultTypeOption;
// 		dMinValue = m_pSetDfdDlg->m_dMinFaultAmp;
// 		nFiType = m_pSetDfdDlg->m_nFaultKindOption;
// 
// 		int																			nDLIdx(0), nProtCbswIdx(0), nTargetIdx;
// 		for (int i = 1; i <= GETCOUNT(_T("fltinfo_dyn_fio")); i++)
// 		{
// 			if (_wtoi(GETTEXT(_T("fltinfo_dyn_fio"), _T("fltinfo_id"), i)) == 0)	break;
// 
// 			nDLIdx = GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_ii_dl"), i);
// 			// 			if( nDLIdx != m_nDLIdx )												continue;
// 
// 			nProtCbswIdx = GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_ii_cbsw"), i);
// 			PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_nwstat"), nProtCbswIdx, SW_OPEN);
// 
// 			if (((CMainFrame *)AfxGetMainWnd())->GetViewMode() == SLDVIEW_ALL_MODE)	nTargetIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nProtCbswIdx);
// 			else																		nTargetIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tgnd"), nProtCbswIdx);
// 
// 			MakeSLD(nDLIdx);
// 			MakeSLDBuffer(TRUE);
// 
// 			CNodeView*																pNodeView;
// 			pNodeView = m_pNodeView->GetSelectNodeView(nTargetIdx, -1);
// 			if (pNodeView)															MoveFocusNodeView(nTargetIdx);
// 
// 			break;
// 		}
// 
// 		HWND																		pAppServerWnd;
// 		pAppServerWnd = ::FindWindow(NULL, GetServerName());
// 		if (!pAppServerWnd)														return S_OK;
// 
// 		char																		szSendMsg[128] = { 0, };
// 		sprintf(szSendMsg, "APPLEXEMODE,DFD,%d,%d,%d,%d,%d,%d,%d", nGBRIdx, nProtGNDIdx, nSCAExec, nFaType, (int)dMinValue, nFiType, nNextCbswIndex);
// 
// 		COPYDATASTRUCT																_cds = { 0, };
// 		_cds.dwData = 2;
// 		_cds.cbData = (DWORD)sizeof(szSendMsg);
// 		_cds.lpData = (BYTE *)szSendMsg;
// 		::SendMessage(pAppServerWnd, WM_COPYDATA, (WPARAM)this, (LPARAM)&_cds);
// 
// 		delete m_pSetDfdDlg;
// 		m_pSetDfdDlg = NULL;
// 
// 		Invalidate();
// 	}

	return TRUE;
}

BOOL CSimulatorSLDView::ModifySLD(int nReDraw)
{
	if (m_nDLIdx <= 0)																return FALSE;
	if (m_pSelectNodeView == NULL)													return FALSE;

	int																				nTargetIdx(0);
	if (m_pSelectNodeView->m_nTongID)
	{//멀티이고, 멀티의 다음노드가 가상더미이다. 즉, 다회로 전원측이면
		if (m_pSelectNodeView->m_pCenter && m_pSelectNodeView->m_pCenter->m_nSwKindID == -1000)	nTargetIdx = m_pSelectNodeView->m_nNDID[0];//FND로 확인
		else																		nTargetIdx = m_pSelectNodeView->m_nNDID[1];//TND로 확인
	}
	else
	{
		if (m_pSelectNodeView->m_nNDID[1] == 0)										nTargetIdx = m_pSelectNodeView->m_nNDID[0];//NODE속성이면 ND로 확인
		else																		nTargetIdx = m_pSelectNodeView->m_nNDID[1];//BR속성이면 TND로 확인
	}

	if (nReDraw == 1)
	{
		MakeSLD(m_nDLIdx);
		MakeSLDBuffer(TRUE);//모드변경 후 다시 그림.
	}
	else
	{
		MakeSLDBuffer(FALSE);
	}
	if (nTargetIdx)																	MoveFocusNodeView(nTargetIdx);
	return TRUE;
}

void CSimulatorSLDView::GetBRIdx(CNodeView* pNodeView, int& nCompIdx, int& nType)
{
	int																				nNodeIdx(0);
	if (pNodeView->m_nTongID)
	{//멀티이고, 멀티의 다음노드가 가상더미이다. 즉, 다회로 전원측이면
		if (pNodeView->m_pCenter && pNodeView->m_pCenter->m_nSwKindID == -1000)		nNodeIdx = pNodeView->m_nNDID[0];//FND로 확인
		else																		nNodeIdx = pNodeView->m_nNDID[1];//TND로 확인
	}
	else
	{
		if (pNodeView->m_nNDID[1] == 0)												nNodeIdx = pNodeView->m_nNDID[0];//NODE속성이면 ND로 확인
		else																		nNodeIdx = pNodeView->m_nNDID[1];//BR속성이면 TND로 확인
	}

	GetComponentType(nNodeIdx, nCompIdx, nType);
	return;
}

void CSimulatorSLDView::GetComponentType(int nNDIdx, int& nCompIdx, int& nType)
{
	if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0 || GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx) > 0)//cbsw와 연결된 노드.
	{
		if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0)				nCompIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
		else																		nCompIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);

		nType = NDTYPE_SWITCH;
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), nNDIdx) > 0)//DG
	{
		nCompIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), nNDIdx);
		nType = NDTYPE_GEN;
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_shunteq"), nNDIdx) > 0)//SHUNTEQ
	{
		nCompIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_shunteq"), nNDIdx);
		nType = NDTYPE_SHUNTEQ;
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_svc"), nNDIdx) > 0)//SVC
	{
		nCompIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_svc"), nNDIdx);
		nType = NDTYPE_SVC;
	}
	else//br이랑만 연결되어 있음 - Dummy 또는 SVR 임
	{
		int																			nSVRIdx = 0;
		int																			nBRIdx;

		nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNDIdx);
		while (nBRIdx)
		{
			if (nBRIdx && GetBrType( nBRIdx ) == 2)
			{
				nSVRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
				break;
			}

			nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nBRIdx);
		}

		if (nSVRIdx == 0)
		{
			nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNDIdx);
			while (nBRIdx)
			{
				if (nBRIdx && GetBrType(nBRIdx) == 2)
				{
					nSVRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
					break;
				}
				nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nBRIdx);
			}
		}

		if (nSVRIdx)//SVR
		{
			nCompIdx = nSVRIdx;
			nType = NDTYPE_SVR;
		}
		else//Dummy
		{
			nCompIdx = nNDIdx;
			nType = NDTYPE_DUMMY;
		}
	}
}

void CSimulatorSLDView::FindObject()
{
	if (m_pFindDlg)																return;

	m_pFindDlg = new CFindObjDlg(this);
	m_pFindDlg->Create();
}

LRESULT CSimulatorSLDView::OnFindObjPosition(WPARAM wparam, LPARAM lparam)
{
	int																				nTargetIdx, nDlIdx;
	if ((int)wparam < 0)
	{
		delete m_pFindDlg;
		m_pFindDlg = NULL;

		return TRUE;
	}
	else if ((int)wparam == 0)//설비명칭 검색(찾을 설비의 NDIDX가 넘어옴)
	{
		int																			nCount(theAppDataMng->GetTableRealCount(_T("nd_sta")));
		if ((int)lparam > nCount)
		{
			CMessageDlg dlg(_T("알림"), MB_OK);
			dlg.SetMessage(_T("인덱스가 범위를 벗어났습니다."));
			dlg.DoModal();

			return FALSE;
		}

		nDlIdx = GETVALUE(int, _T("nd_dyn_ncpo"), _T("nd_ii_dl"), (int)lparam);
		if (nDlIdx <= 0)
		{
			CMessageDlg dlg(_T("알림"), MB_OK);
			dlg.SetMessage(_T("배전선로가 아닙니다."));
			dlg.DoModal();

			return FALSE;
		}

		nTargetIdx = (int)lparam;
	}
	else if ((int)wparam == 1)//(G)ND 인덱스 검색(단선도보기 모드에 따라 ND 또는 GND로 검색)
	{
		int																			nCount(theAppDataMng->GetTableRealCount(_T("nd_sta")));
		if ((int)lparam > nCount)
		{
			CMessageDlg dlg(_T("알림"), MB_OK);
			dlg.SetMessage(_T("인덱스가 범위를 벗어났습니다."));
			dlg.DoModal();

			return FALSE;
		}

		nDlIdx = GETVALUE(int, _T("nd_dyn_ncpo"), _T("nd_ii_dl"), (int)lparam);
		if (nDlIdx <= 0)
		{
			CMessageDlg dlg(_T("알림"), MB_OK);
			dlg.SetMessage(_T("배전선로가 아닙니다."));
			dlg.DoModal();

			return FALSE;
		}

		nTargetIdx = (int)lparam;

	}
	else if ((int)wparam == 2)//CBSW 인덱스 검색
	{
		int																			nCount(theAppDataMng->GetTableRealCount(_T("cbsw_sta")));
		if ((int)lparam > nCount)
		{
			CMessageDlg dlg(_T("알림"), MB_OK);
			dlg.SetMessage(_T("인덱스가 범위를 벗어났습니다."));
			dlg.DoModal();

			return FALSE;
		}

		nDlIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), (int)lparam);
		if (nDlIdx <= 0)
		{
			CMessageDlg dlg(_T("알림"), MB_OK);
			dlg.SetMessage(_T("배전선로가 아닙니다."));
			dlg.DoModal();

			return FALSE;
		}

		nTargetIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), (int)lparam);
	}
	else if ((int)wparam == 3)//TR 인덱스 검색
	{
		int																			nCount(theAppDataMng->GetTableRealCount(_T("tr_sta")));
		if ((int)lparam > nCount)
		{
			CMessageDlg dlg(_T("알림"), MB_OK);
			dlg.SetMessage(_T("인덱스가 범위를 벗어났습니다."));
			dlg.DoModal();

			return FALSE;
		}

		int																			nTrType;
		nTrType = GETVALUE(int, _T("tr_sta"), _T("tr_type"), (int)lparam);
		if (nTrType != 3)
		{
			CMessageDlg dlg(_T("알림"), MB_OK);
			dlg.SetMessage(_T("배전선로가 아닙니다."));
			dlg.DoModal();

			return FALSE;
		}

		nTargetIdx = GETVALUE(int, _T("tr_sta"), _T("tr_ii_tnd"), (int)lparam);
	}

	FindNodePosition(nTargetIdx, TRUE);

	return TRUE;
}

BOOL CSimulatorSLDView::FindNodePosition(int nTargetIdx, BOOL bShow)
{
	int nDlIdx;
	//찾을 대상 노드가 정해졌으니 해당 노드의 전원(CB)을 찾는다.
	nDlIdx = SearchDL(nTargetIdx, -1);

	//CB를 찾지 못하면 BR속성(CBSW, TISW, SVR)의 설비들의 경우 반대편 NODE도 탐색
	if (nDlIdx <= 0)
	{
		int																		nNextNDIdx;
		nNextNDIdx = GetToNDIdx(nTargetIdx);

		//노드(Dummy, Gen...등)설비는 nNextNDIdx == nTargetIdx. 즉, 할필요없음
		//BR(CBSW, TISW, SVR)설비는 nNextNDIdx != nTargetIdx. 이 경우에 반대편 노드도 CB를 찾아보자.
		if (nNextNDIdx != nTargetIdx)
			nDlIdx = SearchDL(nNextNDIdx, nTargetIdx);
	}

	//CB를 못찾으면 진행 못함.
	if (bShow && nDlIdx <= 0)
	{
		CMessageDlg dlg(_T("알림"), MB_OK);
		dlg.SetMessage(_T("해당 설비의 전원을 찾을 수 없습니다."));
		dlg.DoModal();

		return FALSE;
	}

	//찾은 CB가 현재 보고있는 CB가 아니면 해당선로의 단선도를 그린다.
	if (nDlIdx != m_nDLIdx)
	{
		MakeSLD(nDlIdx);
		MakeSLDBuffer(TRUE);//모드변경 후 다시 그림.
	}

	MoveFocusNodeView(nTargetIdx);

	return TRUE;
}

void CSimulatorSLDView::MoveFocusNodeView(int nTargetIdx)
{
	if (m_pNodeView == NULL)														return;

	//단선도에서 검색대상 NodeView를 찾는다.
	CNodeView*																		pTargetNode;
	pTargetNode = m_pNodeView->GetSelectNodeView(nTargetIdx, -1);

	if (pTargetNode == NULL)
	{
		//이럴수가 있네...상태정보를 조작하면 현재DL에서 다른DL로 넘어갈수가 있구만...(사선구간의 부하측을 투입하면 투입된설비는 타선로로 넘어감)
		//이때 다른DL 단선도를 보여주고 해당 설비를 찾아주는게 좋아보이지 않는다.
		//현재DL에서 설비정보를 변경했으니 현재 단선도를 유지하고, 정보를 수정한 설비를 안 찾는게 좋아보이네.
// 		AfxMessageBox( _T("이럴수가 있다고???") );
		return;
	}

	//찾은 NodeView의 위치로 화면을 이동한다.
	CPoint																			ptTarget;
	ptTarget.x = (pTargetNode->m_nPosX * m_dZoomScale);
	ptTarget.y = (pTargetNode->m_nPosY * m_dZoomScale);
	SetCenterPosition(ptTarget);

	//찾은 NodeView에 마킹을 한다.
	SetSelectDraw(pTargetNode);

	Invalidate();
}

void CSimulatorSLDView::MakeAllSLDRcv(int nBRIdx, int nFNDIdx, CNodeView* pnodeview, CBranchView* pbranchview, int nDeadLineDepth)
{
	if (nBRIdx == 0)																return;

	//이미 지나갔던 구간이면 다시 안간다.
	if (m_pBRTrace[nBRIdx - 1])														return;
	//구간 Trace 체크
	m_pBRTrace[nBRIdx - 1] = TRUE;

	if (GetBrType(nBRIdx) != 1)
	{
		//구간(선로)가 아닐수가 있나????
		return;
	}


	int																				nLNSECIdx(0), nOverHead, nLineTypeCd;
	CString																			szLNCeqID;

	nLNSECIdx																		= GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
	szLNCeqID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("lnsec_sta"), _T("lnsec_ceqid"), nLNSECIdx));

	if (((CMainFrame *)AfxGetApp()->GetMainWnd())->GetShowVirtualDG() == FALSE)
	{
		if (szLNCeqID.Left(6) == _T("999951"))//가상구간CEQID
			return;
	}

	nOverHead = GETVALUE(int, _T("lnsec_sta"), _T("lnsec_constype"), nLNSECIdx);

	CNodeView*																		pNewNodeView;
	int																				nTNDIdx, nNextNDIdx, nNextBRIdx, nRet;

	//구간의 다음 노드를 찾는다.
	if (GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx) == nFNDIdx)			nTNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_tnd"), nBRIdx);
	else																			nTNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx);

	//nTNDIdx를 그대로 사용하면 전체모드
	//자동화모드일때는 nTNDIdx가 대상설비인지 확인하고, 아니면 다음 대상노드의 FND를 찾아옴(축약구간에 대한 임피던스 및 부하, (긍장) 누적하면서...)
	double																			dLoad(0), dLength(0), dRp(0), dR0(0), dXp(0), dX0(0);

	if ( m_nSLDMode )
	{
		CIntArray																	nLnSecArr;
		nTNDIdx = GetNextNDIdxRcv(nTNDIdx, dLength, dLoad, dRp, dR0, dXp, dX0, nLnSecArr);

		//다음 노드가 없으면 끝.(일반모드의 경우는 가상더비를 생성하여 말단을 만든다) -> 이런경우는 없어야 맞지만 예외처리용.
		if (nTNDIdx == 0)															return;
	}

	BOOL																			bInternal(FALSE);
	//이미 지나갔던 설비이면 다시 안간다.
	//다음설비가 이미 지나갔던 설비이면 이 설비까지는 그리고 끝내야 함.
	//체크만 하고, 그린 후에 Return할 꺼임.
	if (m_pNDTrace[nTNDIdx - 1])														bInternal = TRUE;

	//설비 Trace 체크
	m_pNDTrace[nTNDIdx - 1] = TRUE;

	//구간의 부하측 설비 생성.
	pNewNodeView = new CNodeView();
	pNewNodeView->m_nDbID = m_nNodeID++;
	pNewNodeView->m_nNDID[0] = nTNDIdx;

	if (pnodeview->m_pCenter == NULL)												pnodeview->m_pCenter = pNewNodeView;
	else if (pnodeview->m_pRight == NULL)											pnodeview->m_pRight = pNewNodeView;
	else if (pnodeview->m_pLeft == NULL)											pnodeview->m_pLeft = pNewNodeView;
	else if (pnodeview->m_pLeftTop == NULL)											pnodeview->m_pLeftTop = pNewNodeView;
	else if (pnodeview->m_pRightBottom == NULL)										pnodeview->m_pRightBottom = pNewNodeView;
	else
	{//6회로 이상 분기는 처리불가함.
		CString szTmp;
		szTmp.Format(_T("Error : 1 => %d : %d"), pnodeview->m_nDbID, pNewNodeView->m_nDbID);
		AfxMessageBox(szTmp);

		delete pNewNodeView;
		return;

// 		CNodeView*																	pDummy;
// 		pDummy = new CNodeView();
// 		pDummy->m_nDbID = m_nNodeID++;
// 		pDummy->m_nSwKindID = -1000;
// 		pDummy->m_szLoc = _T("가상");
// 		pDummy->m_nTongID = pNewNodeView->m_nTongID;
// 		pDummy->m_pGISDPoint.dx = pNewNodeView->m_pGISDPoint.dx;
// 		pDummy->m_pGISDPoint.dy = pNewNodeView->m_pGISDPoint.dy;
// 		pDummy->m_nFromND = nTNDIdx;
// 
// 		pbranchview->Add(-1, pnodeview->m_nDbID, pDummy->m_nDbID, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, _T(""), nDeadLineDepth, TRUE);
// 
// 		pDummy->m_pCenter = pnodeview->m_pRightBottom;
// 		pDummy->m_pRight = pNewNodeView;
// 
// 		
// 		pnodeview->m_pRightBottom = pDummy;
	}

	//축약구간은 첫번째구간정보(CEQID, 지중/가공, 선종..등)를 대표정보로 하고, 임피던스, 부하, 긍장..등 현재구간의 정보를 누적함.
	//축약구간의 누적값은 위 다음 대상노드를 찾아올때 처리했음.

	nLineTypeCd = 0;//KCIM 선종타입정보없음
	dLoad += 0;//구간부하정보 확인해서 넣을것!
	dLength += 1;//KCIM 긍장정보없음(그냥 1km로...)
	dRp += GETVALUE(double, _T("br_sta"), _T("br_posr"), nBRIdx);
	dR0 += GETVALUE(double, _T("br_sta"), _T("br_zerr"), nBRIdx);
	dXp += GETVALUE(double, _T("br_sta"), _T("br_posx"), nBRIdx);
	dX0 += GETVALUE(double, _T("br_sta"), _T("br_zerx"), nBRIdx);

	//파라메타로 넘어온 구간의 전원측 설비와 위에서 생성한 부하측 설비를 연결하는 구간을 정보를 생성.
	int nBrFromNDIdx(0);
	nBrFromNDIdx = pnodeview->m_nNDID[1] == 0 ? pnodeview->m_nNDID[0] : pnodeview->m_nNDID[1];
	if (pbranchview->m_nNode1 == 0)
	{
		pbranchview->m_nDbID = nBRIdx;
		pbranchview->m_szCeqID = szLNCeqID;
		pbranchview->m_nOverHead = nOverHead;
		pbranchview->m_nNode1 = pnodeview->m_nDbID;
		pbranchview->m_nNode2 = pNewNodeView->m_nDbID;
		pbranchview->m_dLengthReal = dLength;
		pbranchview->m_dLengthDisp = 1;
		pbranchview->m_nLineTypeCd = nLineTypeCd;

		pbranchview->m_nNDID[0] = nBrFromNDIdx;
		pbranchview->m_nNDID[1] = pNewNodeView->m_nNDID[0];

		pbranchview->m_dLoad = dLoad;
		pbranchview->m_dRp = dRp;
		pbranchview->m_dR0 = dR0;
		pbranchview->m_dXp = dXp;
		pbranchview->m_dX0 = dX0;

		pbranchview->m_nDeadLineDepth = nDeadLineDepth;

// 		SetBranchPolePos(pbranchview, pnodeview, pNewNodeView);
	}
	else
	{
		CBranchView* pNewBranchView;
		pNewBranchView = pbranchview->Add(nBRIdx, pnodeview->m_nDbID, pNewNodeView->m_nDbID, nBrFromNDIdx, pNewNodeView->m_nNDID[0], dLength, nLineTypeCd, nOverHead, dLoad, dRp, dR0, dXp, dX0, szLNCeqID, nDeadLineDepth, TRUE);

// 		SetBranchPolePos(pNewBranchView, pnodeview, pNewNodeView);
	}

	//일반모드에서는 구간의 부하측노드가 없을경우 부하측에 가상노드를 하나만들고, 구간까지 생성한 후 종료.
	if (nTNDIdx <= 0)
	{//축약모드에서는 구간의 부하측노드가 없으면 구간을 안만들고 끝(즉, 축약모드에서는 들어올 일 없음)
		pNewNodeView->m_szLoc = _T("Virtual");
		pNewNodeView->m_nSwKindID = NDTYPE_DUMMY;
		pNewNodeView->m_bStatus = SW_CLOSE;
		return;
	}

	//nTNDIdx는 구간기준의 ToND -> 즉, 설비기준에서는 FND임
	//위에서 추가한 nTNDIdx 기준의 설비의 세부정보를 세팅하고, 설비기준에서의 TND(nNextNDIdx)로 변경.
	//DG, shunt, svc, Dummy등 토폴로지 기준 단일노드인 설비는 같은값이고, cbsw, tisw, svr 등은 설비기준 TND롤 변경
	//설비의 FND = 구간의 TND, 설비의 TND = 구간의 FND!!!!!!!!!!!!!!!!!!
	nNextNDIdx = SetNodeInfo(nTNDIdx, pNewNodeView);
	//찾은 설비가 CB이면 루프임. 그만하자
	if (pNewNodeView->m_nKCIMType == KCIMTYPE_CB)//
	{
		if (nDeadLineDepth == 0 && GetNDStatus(nNextNDIdx) == SW_CLOSE)//CB인데 branch가 사선이 아니고, CB가 닫혀있으면
		{
			CString szName, szSubst(_T(""));

			int																nDlIdx, nMTRIdx, nSSIdx;
			nDlIdx = GetCbswToNode(nTNDIdx);

			if (nDlIdx)
			{
				nMTRIdx = GETVALUE(int, _T("dl_sta"), _T("dl_ii_mtr"), nDlIdx);
				if (nMTRIdx)
				{
					nSSIdx = GETVALUE(int, _T("mtr_sta"), _T("mtr_ii_ss"), nMTRIdx);
					if (nSSIdx)
					{
						szSubst = GETSTRING(_T("ss_sta"), _T("ss_nm"), nSSIdx);
						szSubst.Replace(_T(" 변전소"), _T(""));
						szSubst.Replace(_T("변전소"), _T(""));
					}
				}
			}

			szName.Format(_T("%s/%s"), szSubst, pNewNodeView->m_szLoc);
			m_szLoofCBNmArr.Add(szName);
			m_nLoofCBIdArr.Add(pNewNodeView->m_nNDID[0]);

			return;
		}
	}
	// 	if( bInternal )																	pNewNodeView->m_szLocNo = _T("내부연계");

	//설비의 부하측 노드와 연결된 cbsw(tisw포함)의 갯수를 체크한다.
// 	int																				nConnectCount;
// 	nConnectCount = CheckConnectSw(nNextNDIdx);
// 
// 	//현재 설비(들어온쪽 설비)를 포함하여 2개이상 개폐기가 연결되어 있으면 멀티개폐기로 처리.
// 	//1개이하( 0:더미노드, gen, shunt...svr등, 1:단일개폐기) -> 어차피 동일로직이므로 뭐가되든 상관없다.
// 	//멀티개폐기 생성 및 토폴로지 진행을 위해 멀티를 구분하는 것임(다분기 더비는 br을 통해 진행하고, 멀티개폐기는 cbsw(tisw)를 통해 진행함) 
// 	if (nConnectCount >= 2) //다회로개폐기
	if( IsMultiSw(nNextNDIdx) )//CBSW의 멀티ID를 통해 멀티개폐기구분
	{
		//단선도 생성을 위해 설비의 타입을 지정.
		int																			nMultiType;
		if (pNewNodeView->m_nKCIMType == KCIMTYPE_TR)
		{
			nMultiType = NDTYPE_TR;
		}
		else if (pNewNodeView->m_nKCIMType == KCIMTYPE_ALTS)
		{
			nMultiType = NDTYPE_ALTS;
		}
		else
		{
			nMultiType = NDTYPE_MULTI;
		}

		//위에서 들어온 전원측 설비에 다회로 관련 설비정보를 추가 또는 변경함.
		int																			nPos(0);

		pNewNodeView->m_nNDID[1] = nNextNDIdx;//설비의 TND설정
		pNewNodeView->m_nSwKindID = nMultiType;//다회로타입설정

		//다회로의 가상더미 정보생성
		CString																		szLoc;
		szLoc = GETSTRING(_T("nd_sta"), _T("nd_nm"), nNextNDIdx);
		nPos = szLoc.ReverseFind('(');
		if (nPos > 0)																szLoc = szLoc.Left(nPos);

		nPos = szLoc.ReverseFind('_');
		if (nPos > 0)																szLoc = szLoc.Left(nPos);

		CNodeView*																	pDummy;
		pDummy = new CNodeView();
		pDummy->m_nDbID = m_nNodeID++;
		pDummy->m_nSwKindID = -1000;
		pDummy->m_szLoc = szLoc;
		pDummy->m_nTongID = pNewNodeView->m_nTongID;
		pDummy->m_pGISDPoint.dx = pNewNodeView->m_pGISDPoint.dx;
		pDummy->m_pGISDPoint.dy = pNewNodeView->m_pGISDPoint.dy;
		pDummy->m_nFromND = nTNDIdx;
		pDummy->m_nKCIMType = pNewNodeView->m_nKCIMType;
		pDummy->m_nCeqType = pNewNodeView->m_nCeqType;

		if (bInternal)																pDummy->m_szLoc += _T("(내부연계)");

		//전원측 설비와 가상더미를 연결하는 가상구간생성( KCIM에 BR정보가 있으면 그걸써야하나... )
		pbranchview->Add(-1, pNewNodeView->m_nDbID, pDummy->m_nDbID, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, _T(""), nDeadLineDepth, TRUE);

		//생성한 가상더미를 전원측 설비뒤에 연결
		pNewNodeView->m_pCenter = pDummy;

		//다회로 단자들을 찾아가면 생성한다.
		CNodeView*																	pSubNodeView[6] = { NULL, };
		int																			nSubSwIdx, nIndex(0);

		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNextNDIdx);
		while (nSubSwIdx)
		{
			if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nSubSwIdx) != nTNDIdx)
			{//다회로 전원측 cbsw가 아니면, 부하측단자~~~
				//부하측 단자설비를 추가하고 멀티가상더미 뒤로 연결.
				pSubNodeView[nIndex] = new CNodeView();
				pSubNodeView[nIndex]->m_nDbID = m_nNodeID++;
				pSubNodeView[nIndex]->m_nNDID[0] = nNextNDIdx;
				pSubNodeView[nIndex]->m_pGISDPoint.dx = pNewNodeView->m_pGISDPoint.dx;
				pSubNodeView[nIndex]->m_pGISDPoint.dy = pNewNodeView->m_pGISDPoint.dy;

				SetMultiCircuitInfo(nNextNDIdx, nSubSwIdx, nMultiType, pSubNodeView[nIndex]);
				// 				if( bInternal )														pSubNodeView[nIndex]->m_szLocNo = _T("내부연계");

				if (nMultiType == NDTYPE_ALTS)
				{
					pNewNodeView->m_nALTSCBSW										= pSubNodeView[nIndex]->m_nNDID[1];
					pSubNodeView[nIndex]->m_nALTSCBSW								= pNewNodeView->m_nNDID[0];
				}

				pbranchview->Add(-1, pDummy->m_nDbID, pSubNodeView[nIndex]->m_nDbID, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, _T(""), nDeadLineDepth, TRUE);

				if (pDummy->m_pCenter == NULL)										pDummy->m_pCenter = pSubNodeView[nIndex];
				else if (pDummy->m_pRight == NULL)									pDummy->m_pRight = pSubNodeView[nIndex];
				else if (pDummy->m_pLeft == NULL)									pDummy->m_pLeft = pSubNodeView[nIndex];
				else if (pDummy->m_pLeftTop == NULL)								pDummy->m_pLeftTop = pSubNodeView[nIndex];
				else if (pDummy->m_pRightBottom == NULL)							pDummy->m_pRightBottom = pSubNodeView[nIndex];

				nIndex++;
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fnd"), nSubSwIdx);
		}

		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNextNDIdx);
		while (nSubSwIdx)
		{
			if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nSubSwIdx) != nTNDIdx)
			{
				pSubNodeView[nIndex] = new CNodeView();
				pSubNodeView[nIndex]->m_nDbID = m_nNodeID++;
				pSubNodeView[nIndex]->m_nNDID[0] = nNextNDIdx;
				pSubNodeView[nIndex]->m_pGISDPoint.dx = pNewNodeView->m_pGISDPoint.dx;
				pSubNodeView[nIndex]->m_pGISDPoint.dy = pNewNodeView->m_pGISDPoint.dy;

				SetMultiCircuitInfo(nNextNDIdx, nSubSwIdx, nMultiType, pSubNodeView[nIndex]);
				// 				if( bInternal )														pSubNodeView[nIndex]->m_szLocNo = _T("내부연계");

				if (nMultiType == NDTYPE_ALTS)
				{
					pNewNodeView->m_nALTSCBSW = pSubNodeView[nIndex]->m_nNDID[1];
					pSubNodeView[nIndex]->m_nALTSCBSW = pNewNodeView->m_nNDID[0];
				}

				pbranchview->Add(-1, pDummy->m_nDbID, pSubNodeView[nIndex]->m_nDbID, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, _T(""), nDeadLineDepth, TRUE);

				if (pDummy->m_pCenter == NULL)										pDummy->m_pCenter = pSubNodeView[nIndex];
				else if (pDummy->m_pRight == NULL)									pDummy->m_pRight = pSubNodeView[nIndex];
				else if (pDummy->m_pLeft == NULL)									pDummy->m_pLeft = pSubNodeView[nIndex];
				else if (pDummy->m_pLeftTop == NULL)								pDummy->m_pLeftTop = pSubNodeView[nIndex];
				else if (pDummy->m_pRightBottom == NULL)							pDummy->m_pRightBottom = pSubNodeView[nIndex];

				nIndex++;
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tnd"), nSubSwIdx);
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//사선처리방법
		//1. 다회로 전원측이 OPEN이면 사선DEPTH를 +1 하고, 부하측 Close단자를 돌면서 BACKUP을 찾아놓는다.
		//2. 부하측 단자를 돌면서
		//3. 부하측 단자가 OPEN이면 사선DEPTH를 +1 하고, 단자의 BACKUP을 찾는다(BACKUP이 있으면 연결하고 다음~)
		//4. 부하측 단자가 CLOSE이면 1에서 BACKUP이 있으면 넘어가고,
		//5. 부하측 단자가 CLOSE이면 1에서 BACKUP이 없으면 사선DEPTH를 가지고 계속 진행한다.
		//6. 사선DEPTH가 설정DEPTH를 넘어가면 안감.
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		//설비의 FND로 상태값을 확인
		BOOL																		bFindMultiBF(FALSE);
		nRet = GetNDStatus(nTNDIdx);

		//다회로의 전원측이 OPEN이면 부하측 Close단자를 돌면서 BACKUP을 먼저 찾자.
		if (nRet == SW_OPEN)
		{
			nDeadLineDepth++;

			for (int i = 0; i < 6; i++)
			{
				if (pSubNodeView[i] == NULL)										continue;
				if (GetNDStatus(pSubNodeView[i]->m_nNDID[1]) == SW_OPEN)			continue;

				//BACKUP을 찾으면 BF를 연결한다.
				int																	nBfDlIdx;
				nBfDlIdx = FindBF(nBRIdx, pSubNodeView[i]->m_nNDID[1]);
				if (nBfDlIdx)
				{
					CNodeView*														pBackup;
					pBackup = new CNodeView();
					pBackup->m_nDbID = m_nNodeID++;
					pBackup->m_nSwKindID = NDTYPE_BACKUP;
					pBackup->m_szLoc = GETSTRING(_T("dl_sta"), _T("dl_nm"), nBfDlIdx);;
					pBackup->m_nTongID = 0;

					int																nMTRIdx, nSSIdx;
					if (nBfDlIdx)
					{
						nMTRIdx = GETVALUE(int, _T("dl_sta"), _T("dl_ii_mtr"), nBfDlIdx);
						if (nMTRIdx)
						{
							nSSIdx = GETVALUE(int, _T("mtr_sta"), _T("mtr_ii_ss"), nMTRIdx);
							if (nSSIdx)
							{
								pBackup->m_szLocNo = GETSTRING(_T("ss_sta"), _T("ss_nm"), nSSIdx);
							}
						}
					}

					if (nBfDlIdx == m_nDLIdx)//내부연계면
					{
						pNewNodeView->m_szLocNo = _T("내부연계");

						//연계포인트의 NODEIDX를 가지고 있자. 화면에서 연계NODE로의 이동을 위해서...
						pBackup->m_nNDID[0] = pNewNodeView->m_nNDID[0];
						pBackup->m_nNDID[1] = pNewNodeView->m_nDbID;
					}
					else
					{
						pNewNodeView->m_szLocNo = _T("외부연계");

						//백업선로의 DLIdx를 가지고 있자. 화면에서 연계선로로 이동을 위해
						pBackup->m_nNDID[0] = nBfDlIdx;
					}

					ASSERT(pSubNodeView[i]->m_pCenter == NULL);
					pSubNodeView[i]->m_pCenter = pBackup;
					pbranchview->Add(-1, pSubNodeView[i]->m_nDbID, pBackup->m_nDbID, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, _T(""), nDeadLineDepth, FALSE);

					bFindMultiBF = TRUE;
					break;
				}
			}
		}

		//생성된 단자부터 이후 계통을 탐색한다.
		for (int i = 0; i < 6; i++)
		{
			if (pSubNodeView[i] == NULL)											continue;

			int																		nDeadLineDepth2;
			nDeadLineDepth2 = nDeadLineDepth;

			//설비의 TND로 상태값을 확인
			if (GetNDStatus(pSubNodeView[i]->m_nNDID[1]) == SW_OPEN)
			{
				nDeadLineDepth2++;

				//부하측이 OPEN이면 BACKUP탐색
				//BACKUP을 찾으면 BF를 연결하고 끝.
				//BACKUP을 못찾으면 사선구간으로 다음 계속 진행.
				int																	nBfDlIdx;
				nBfDlIdx = FindBF(nBRIdx, pSubNodeView[i]->m_nNDID[1]);
				if (nBfDlIdx)
				{
					CNodeView*														pBackup;
					pBackup = new CNodeView();
					pBackup->m_nDbID = m_nNodeID++;
					pBackup->m_nSwKindID = NDTYPE_BACKUP;
					pBackup->m_szLoc = GETSTRING(_T("dl_sta"), _T("dl_nm"), nBfDlIdx);;
					pBackup->m_nTongID = 0;

					int																nMTRIdx, nSSIdx;
					if (nBfDlIdx)
					{
						nMTRIdx = GETVALUE(int, _T("dl_sta"), _T("dl_ii_mtr"), nBfDlIdx);
						if (nMTRIdx)
						{
							nSSIdx = GETVALUE(int, _T("mtr_sta"), _T("mtr_ii_ss"), nMTRIdx);
							if (nSSIdx)
							{
								pBackup->m_szLocNo = GETSTRING(_T("ss_sta"), _T("ss_nm"), nSSIdx);
							}
						}
					}

					if (nBfDlIdx == m_nDLIdx)//내부연계면
					{
						pSubNodeView[i]->m_szLocNo = _T("내부연계");

						//연계포인트의 NODEIDX를 가지고 있자. 화면에서 연계NODE로의 이동을 위해서...
						pBackup->m_nNDID[0] = pSubNodeView[i]->m_nNDID[1];
						pBackup->m_nNDID[1] = pSubNodeView[i]->m_nDbID;
					}
					else
					{
						pSubNodeView[i]->m_szLocNo = _T("외부연계");

						//백업선로의 DLIdx를 가지고 있자. 화면에서 연계선로로 이동을 위해
						pBackup->m_nNDID[0] = nBfDlIdx;
					}

					ASSERT(pSubNodeView[i]->m_pCenter == NULL);
					pSubNodeView[i]->m_pCenter = pBackup;
					pbranchview->Add(-1, pSubNodeView[i]->m_nDbID, pBackup->m_nDbID, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, _T(""), nDeadLineDepth2, FALSE);
					continue;
				}
			}
			else
			{
				//부하측이 Close이면
				if (bFindMultiBF)													continue;
			}

			//위에서 내부연계로 판단되었으면 설비는 다 그리고 탐색은 하지말자;
			//수정-20190719 내부연계여도 그냥 가자! 어차피 BR TRACE를 하니까 지나갔던 구간이면 다음에 튕겨짐.
// 			if( bInternal )															continue;

			if (nDeadLineDepth2 > m_nDeadLineDepthSet)								continue;

			//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
			nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), pSubNodeView[i]->m_nNDID[1]);
			while (nNextBRIdx)
			{
				//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
				if ((GetBrType( nNextBRIdx ) == 1) && (m_pBRTrace[nNextBRIdx - 1] == FALSE))
					MakeAllSLDRcv(nNextBRIdx, pSubNodeView[i]->m_nNDID[1], pSubNodeView[i], pbranchview, nDeadLineDepth2);
				nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
			}

			nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), pSubNodeView[i]->m_nNDID[1]);
			while (nNextBRIdx)
			{
				//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
				if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace[nNextBRIdx - 1] == FALSE))
					MakeAllSLDRcv(nNextBRIdx, pSubNodeView[i]->m_nNDID[1], pSubNodeView[i], pbranchview, nDeadLineDepth2);
				nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
			}
		}

		if (nMultiType == NDTYPE_ALTS)
		{
			//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
			nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNextNDIdx);
			while (nNextBRIdx)
			{
				if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace[nNextBRIdx - 1] == FALSE))
					MakeAllSLDRcv(nNextBRIdx, nNextNDIdx, pDummy, pbranchview, nDeadLineDepth);
				nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
			}

			//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
			nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNextNDIdx);
			while (nNextBRIdx)
			{
				if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace[nNextBRIdx - 1] == FALSE))
					MakeAllSLDRcv(nNextBRIdx, nNextNDIdx, pDummy, pbranchview, nDeadLineDepth);
				nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
			}
		}
	}
	else
	{
		if (bInternal)																pNewNodeView->m_szLoc += _T("(내부연계)");

		//설비의 FND로 상태값을 확인
		if (GetNDStatus(nNextNDIdx) == SW_OPEN)
		{
			nDeadLineDepth++;

			//OPEN이면 BACKUP탐색
			//BACKUP을 찾으면 BF를 연결하고 끝.
			//BACKUP을 못찾으면 사선구간으로 다음 계속 진행.
			int																		nBfDlIdx;
			nBfDlIdx = FindBF(nBRIdx, nNextNDIdx);
			if (nBfDlIdx)
			{
				CNodeView*															pBackup;
				pBackup = new CNodeView();
				pBackup->m_nDbID = m_nNodeID++;
				pBackup->m_nSwKindID = NDTYPE_BACKUP;
				pBackup->m_szLoc = GETSTRING(_T("dl_sta"), _T("dl_nm"), nBfDlIdx);;
				pBackup->m_nTongID = 0;

				int																	nMTRIdx, nSSIdx;
				if (nBfDlIdx)
				{
					nMTRIdx = GETVALUE(int, _T("dl_sta"), _T("dl_ii_mtr"), nBfDlIdx);
					if (nMTRIdx)
					{
						nSSIdx = GETVALUE(int, _T("mtr_sta"), _T("mtr_ii_ss"), nMTRIdx);
						if (nSSIdx)
						{
							pBackup->m_szLocNo = GETSTRING(_T("ss_sta"), _T("ss_nm"), nSSIdx);
						}
					}
				}

				if (nBfDlIdx == m_nDLIdx)//내부연계면
				{
					pNewNodeView->m_szLocNo = _T("내부연계");

					//연계포인트의 NODEIDX를 가지고 있자. 화면에서 연계NODE로의 이동을 위해서...
					pBackup->m_nNDID[0] = nNextNDIdx;
					pBackup->m_nNDID[1] = pNewNodeView->m_nDbID;
				}
				else
				{
					pNewNodeView->m_szLocNo = _T("외부연계");

					//백업선로의 DLIdx를 가지고 있자. 화면에서 연계선로로 이동을 위해
					pBackup->m_nNDID[0] = nBfDlIdx;
				}

				ASSERT(pNewNodeView->m_pCenter == NULL);
				pNewNodeView->m_pCenter = pBackup;
				pbranchview->Add(-1, pNewNodeView->m_nDbID, pBackup->m_nDbID, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, _T(""), nDeadLineDepth, FALSE);

				return;
			}
		}

		//위에서 내부연계로 판단되었으면 설비는 다 그리고 여기서 끝내자;
		//수정-20190719 내부연계여도 그냥 가자! 어차피 BR TRACE를 하니까 지나갔던 구간이면 다음에 튕겨짐.
// 		if( bInternal )																return;

		//사선DEPTH 설정보다 작을때만 진행하고, 크거나 같으면 그만!
		if (nDeadLineDepth > m_nDeadLineDepthSet)									return;

		//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNextNDIdx);
		while (nNextBRIdx)
		{
			if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace[nNextBRIdx - 1] == FALSE))
				MakeAllSLDRcv(nNextBRIdx, nNextNDIdx, pNewNodeView, pbranchview, nDeadLineDepth);
			nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
		}

		//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNextNDIdx);
		while (nNextBRIdx)
		{
			if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace[nNextBRIdx - 1] == FALSE))
				MakeAllSLDRcv(nNextBRIdx, nNextNDIdx, pNewNodeView, pbranchview, nDeadLineDepth);
			nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
		}
	}

	return;
}

int CSimulatorSLDView::SetNodeInfo(int nNDIdx, CNodeView* pNewNodeView)
{
	int																				nNextNodeIdx;
	CString																			szData;
	unsigned long long																lValue;
	if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0 || GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx) > 0)//cbsw와 연결된 노드.
	{
		int																			nCbswIdx;
		if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0)				nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);

		pNewNodeView->m_szLoc														= GETSTRING(_T("cbsw_sta"), _T("cbsw_nm"), nCbswIdx);
		pNewNodeView->m_szCEQID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("cbsw_sta"), _T("cbsw_ceqid"), nCbswIdx));
		pNewNodeView->m_nKCIMType													= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCbswIdx);
		pNewNodeView->m_nCeqType													= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_rtutype"), nCbswIdx);
		pNewNodeView->m_bStatus														= GetSwStatus(nCbswIdx);
		pNewNodeView->m_szLocNo														= _T("");

		lValue = GETVALUE(unsigned long long, _T("cbsw_sta"), _T("cbsw_multisw_id"), nCbswIdx);
		if (lValue > 0)
		{
			szData.Format(_T("%llu"), lValue);
			pNewNodeView->m_nTongID = _wtoi(szData.Right(8));
		}
		else
		{
			pNewNodeView->m_nTongID = 0;
		}

		pNewNodeView->m_nCaption													= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_multicir_number"), nCbswIdx);

		pNewNodeView->m_nSwKindID													= NDTYPE_SWITCH;

		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nCbswIdx) == nNDIdx)	nNextNodeIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nCbswIdx);
		else																		nNextNodeIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nCbswIdx);
		pNewNodeView->m_nNDID[1] = nNextNodeIdx;

		m_pNDTrace[nNextNodeIdx - 1] = TRUE;

	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), nNDIdx) > 0)//DG
	{
		int																			nGenIdx, nGenType;
		nGenIdx																		= GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), nNDIdx);

		pNewNodeView->m_szLoc														= GETSTRING(_T("gen_sta"), _T("gen_nm"), nGenIdx);
		pNewNodeView->m_szCEQID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("gen_sta"), _T("gen_ceqid"), nGenIdx));
		pNewNodeView->m_nKCIMType													= 0;//
		nGenType																	= GETVALUE(int, _T("gen_sta"), _T("gen_type"), nGenIdx);
		pNewNodeView->m_bStatus														= SW_CLOSE;//GETVALUE( int, _T("gen_dyn_mea"), _T("cbsw_nwstat"), nGenIdx );
		pNewNodeView->m_szLocNo														= _T("");
		pNewNodeView->m_nTongID														= 0;
		pNewNodeView->m_nCaption													= 0;

		if (nGenType == 3 )															pNewNodeView->m_nSwKindID = NDTYPE_ESS;
		else																		pNewNodeView->m_nSwKindID = NDTYPE_GEN;

		nNextNodeIdx = nNDIdx;
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_shunteq"), nNDIdx) > 0)//SHUNTEQ
	{
		int																			nShuntEQIdx;
		nShuntEQIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_shunteq"), nNDIdx);

		pNewNodeView->m_szLoc														= GETSTRING(_T("shunteq_sta"), _T("shunteq_nm"), nShuntEQIdx);
		pNewNodeView->m_szCEQID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("shunteq_sta"), _T("shunteq_ceqid"), nShuntEQIdx));
		pNewNodeView->m_nKCIMType													= 0;//GETVALUE(int, _T("shunteq_sta"), _T("shunteq_type"), nShuntEQIdx);
		pNewNodeView->m_bStatus														= SW_CLOSE;//GETVALUE( int, _T("shunteq_dyn_mea"), _T("cbsw_nwstat"), nShuntEQIdx );
		pNewNodeView->m_szLocNo														= _T("");
		pNewNodeView->m_nTongID														= 0;
		pNewNodeView->m_nCaption													= 0;

		pNewNodeView->m_nSwKindID													= NDTYPE_SHUNTEQ;

		nNextNodeIdx = nNDIdx;
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_svc"), nNDIdx) > 0)//SVC
	{
		int																			nSVCIdx;
		nSVCIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_svc"), nNDIdx);

		pNewNodeView->m_szLoc														= GETSTRING(_T("svc_sta"), _T("svc_nm"), nSVCIdx);
		pNewNodeView->m_szCEQID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("svc_sta"), _T("svc_ceqid"), nSVCIdx));
		pNewNodeView->m_nKCIMType													= 0;
		pNewNodeView->m_bStatus														= SW_CLOSE;//GETVALUE( int, _T("shunteq_dyn_mea"), _T("cbsw_nwstat"), nSVCIdx );
		pNewNodeView->m_szLocNo														= _T("");
		pNewNodeView->m_nTongID														= 0;
		pNewNodeView->m_nCaption													= 0;

		pNewNodeView->m_nSwKindID													= NDTYPE_SVC;

		nNextNodeIdx = nNDIdx;
	}
	else//br이랑만 연결되어 있음 - Dummy 또는 SVR 임 -> 1.83버전 고객추가.고객도 여기서 구분하자.
	{
		int																			nGNDIdx, nHVCusIdx(0);
		nGNDIdx																		= GETVALUE(int, _T("nd_sta"), _T("nd_ii_gnd"), nNDIdx);
		if (nGNDIdx)
			nHVCusIdx																= GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_hvcus"), nGNDIdx);

		if (nHVCusIdx)
		{
			pNewNodeView->m_szLoc = GETSTRING(_T("nd_sta"), _T("nd_nm"), nNDIdx);
 			pNewNodeView->m_szCEQID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("hvcus_sta"), _T("hvcus_ceqid"), nNDIdx));
			pNewNodeView->m_nKCIMType = 0;
			pNewNodeView->m_bStatus = SW_CLOSE;
			pNewNodeView->m_szLocNo = _T("");
			pNewNodeView->m_nTongID = 0;
			pNewNodeView->m_nCaption = 0;

			pNewNodeView->m_nSwKindID = NDTYPE_CUSTOMER;

			nNextNodeIdx = nNDIdx;

		}
		else
		{
			int																			nSVRIdx = 0;
			int																			nBRIdx;

			nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNDIdx);
			while (nBRIdx)
			{
				if (nBRIdx && GetBrType(nBRIdx) == 2)
				{
					nSVRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
					break;
				}

				nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nBRIdx);
			}

			if (nSVRIdx == 0)
			{
				nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNDIdx);
				while (nBRIdx)
				{
					if (nBRIdx && GetBrType(nBRIdx) == 2)
					{
						nSVRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
						break;
					}
					nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nBRIdx);
				}
			}

			if (nSVRIdx)//SVR
			{
				pNewNodeView->m_szLoc = GETSTRING(_T("tr_sta"), _T("tr_nm"), nSVRIdx);
				pNewNodeView->m_szCEQID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("tr_sta"), _T("tr_ceqid"), nSVRIdx));
				pNewNodeView->m_nKCIMType = 0;// GETVALUE(int, _T("tr_sta"), _T("tr_type"), nSVRIdx);
				pNewNodeView->m_bStatus = SW_CLOSE;//GETVALUE( int, _T("cbsw_dyn_mea"), _T("cbsw_nwstat"), nSVRIdx );
				pNewNodeView->m_szLocNo = _T("");
				pNewNodeView->m_nTongID = 0;
				pNewNodeView->m_nCaption = 0;

				pNewNodeView->m_nSwKindID = NDTYPE_SVR;

				if (GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx) == nNDIdx)		nNextNodeIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_tnd"), nBRIdx);
				else																	nNextNodeIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx);
				pNewNodeView->m_nNDID[1] = nNextNodeIdx;

				m_pNDTrace[nNextNodeIdx - 1] = TRUE;
			}
			else//Dummy
			{
				pNewNodeView->m_szLoc = GETSTRING(_T("nd_sta"), _T("nd_nm"), nNDIdx);
//	 			pNewNodeView->m_szCEQID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("nd_sta"), _T("nd_connectivitynodeid"), nNDIdx));
				pNewNodeView->m_nKCIMType = 0;
				pNewNodeView->m_bStatus = SW_CLOSE;
				pNewNodeView->m_szLocNo = _T("");
				pNewNodeView->m_nTongID = 0;
				pNewNodeView->m_nCaption = 0;

				pNewNodeView->m_nSwKindID = NDTYPE_DUMMY;

				nNextNodeIdx = nNDIdx;
			}
		}
	}

	return nNextNodeIdx;
}

void CSimulatorSLDView::SetMultiCircuitInfo(int nNDIdx, int nCbswidx, int nMultiType, CNodeView* pSubNodeView)
{
	unsigned long long																lValue;
	CString																			szData;

	pSubNodeView->m_szLoc															= GETSTRING(_T("cbsw_sta"), _T("cbsw_nm"), nCbswidx);
	pSubNodeView->m_szCEQID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("cbsw_sta"), _T("cbsw_ceqid"), nCbswidx));
	pSubNodeView->m_nKCIMType														= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCbswidx);
	pSubNodeView->m_nCeqType														= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_rtutype"), nCbswidx);
	pSubNodeView->m_bStatus															= GetSwStatus(nCbswidx);
	pSubNodeView->m_szLocNo															= _T("");

	lValue = GETVALUE(unsigned long long, _T("cbsw_sta"), _T("cbsw_multisw_id"), nCbswidx);
	if (lValue > 0)
	{
		szData.Format(_T("%llu"), lValue);
		pSubNodeView->m_nTongID = _wtoi(szData.Right(8));
	}
	else
	{
		pSubNodeView->m_nTongID = 0;
	}

	pSubNodeView->m_nCaption														= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_multicir_number"), nCbswidx);;

	pSubNodeView->m_nSwKindID = nMultiType;

	int																				nNextNodeIdx;
	if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nCbswidx) == nNDIdx)		nNextNodeIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nCbswidx);
	else																			nNextNodeIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nCbswidx);

	pSubNodeView->m_nNDID[1] = nNextNodeIdx;

	m_pNDTrace[nNextNodeIdx - 1] = TRUE;
}

int CSimulatorSLDView::GetNextNDIdxRcv(int nTargetNDIdx, double& dLen, double& dLoad, double& dRp, double& dR0, double& dXp, double& dX0, CIntArray& nLnSecArr)//다음 대상개폐기를 찾는다(자동화개폐기)
{
	//체크할 노드가 조건에 맞는 설비인지를 찾는다(여기서는 자동화설비)
	//설비가 자동화대상설비(자동개폐기, SVR, DG...등)이거나 다분기 설비(더미, 다회로개폐기)인데 부하측으로 2분기 이상 조건에 맞는 설비가 있는 경우.
	//대상설비를 찾았으면 대상설비 기준 FND를 리턴함.
	if (CheckAutoNode(nTargetNDIdx))												return nTargetNDIdx;

	//설비의 상태가 OPEN이면 그만가자.
	if (GetNDStatus(nTargetNDIdx) == SW_OPEN)										return 0;

	//대상설비가 아니면 다음으로 진행.
	int																				nToNDIdx;

	//설비기준 TND로 설정
	nToNDIdx = GetToNDIdx(nTargetNDIdx);

	int																				nFindNDIdx;

	//현재 설비(들어온쪽 설비)를 포함하여 2개이상 개폐기가 연결되어 있으면 멀티개폐기로 처리.
	//1개이하( 0:더미노드, gen, shunt...svr등, 1:단일개폐기) -> 어차피 동일로직이므로 뭐가되든 상관없다.
	//멀티개폐기 생성 및 토폴로지 진행을 위해 멀티를 구분하는 것임(다분기 더비는 br을 통해 진행하고, 멀티개폐기는 cbsw(tisw)를 통해 진행함) 
	if (IsMultiSw(nToNDIdx)) //다회로개폐기
	{
		int																			nSubSwIdx, nSubNDIdx;
		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nToNDIdx);
		while (nSubSwIdx)
		{
			nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nSubSwIdx);

			nFindNDIdx = GetNextNDIdx(nSubNDIdx, dLen, dLoad, dRp, dR0, dXp, dX0, nLnSecArr);
			if (nFindNDIdx)														return nFindNDIdx;

			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fnd"), nSubSwIdx);
		}

		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nToNDIdx);
		while (nSubSwIdx)
		{
			nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nSubSwIdx);

			nFindNDIdx = GetNextNDIdx(nSubNDIdx, dLen, dLoad, dRp, dR0, dXp, dX0, nLnSecArr);
			if (nFindNDIdx)														return nFindNDIdx;

			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tnd"), nSubSwIdx);
		}
	}
	else
	{
		nFindNDIdx = GetNextNDIdx(nToNDIdx, dLen, dLoad, dRp, dR0, dXp, dX0, nLnSecArr);
		if (nFindNDIdx)															return nFindNDIdx;
	}

	return 0;
}

int CSimulatorSLDView::GetNextNDIdx(int nNDIdx, double& dLen, double& dLoad, double& dRp, double& dR0, double& dXp, double& dX0, CIntArray& nLnSecArr)
{
	if (GetNDStatus(nNDIdx) == SW_OPEN)												return 0;

	int																				nNextNDIdx, nBRIdx;
	nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNDIdx);
	while (nBRIdx)
	{
		if ((GetBrType(nBRIdx) == 1) && (m_pBRTrace[nBRIdx - 1] == FALSE))
		{
			m_pBRTrace[nBRIdx - 1] = TRUE;

			nNextNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_tnd"), nBRIdx);

			int																		nFindNDIdx;
			nFindNDIdx = GetNextNDIdxRcv(nNextNDIdx, dLen, dLoad, dRp, dR0, dXp, dX0, nLnSecArr);
			if (nFindNDIdx)
			{
				dLoad += 0;//구간부하정보 확인해서 넣을것!
				dLen += 1;//KCIM 긍장정보없음(그냥 1km로...)
				dRp += GETVALUE(double, _T("br_sta"), _T("br_posr"), nBRIdx);
				dR0 += GETVALUE(double, _T("br_sta"), _T("br_zerr"), nBRIdx);
				dXp += GETVALUE(double, _T("br_sta"), _T("br_posx"), nBRIdx);
				dX0 += GETVALUE(double, _T("br_sta"), _T("br_zerx"), nBRIdx);

// 				nLNSECIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
				return																nFindNDIdx;
			}
		}

		nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nBRIdx);
	}

	nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNDIdx);
	while (nBRIdx)
	{
		if ((GetBrType(nBRIdx) == 1) && (m_pBRTrace[nBRIdx - 1] == FALSE))
		{
			m_pBRTrace[nBRIdx - 1] = TRUE;

			nNextNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx);

			int																		nFindNDIdx;
			nFindNDIdx = GetNextNDIdxRcv(nNextNDIdx, dLen, dLoad, dRp, dR0, dXp, dX0, nLnSecArr);
			if (nFindNDIdx)
			{
				dLoad += 0;//구간부하정보 확인해서 넣을것!
				dLen += 1;//KCIM 긍장정보없음(그냥 1km로...)
				dRp += GETVALUE(double, _T("br_sta"), _T("br_posr"), nBRIdx);
				dR0 += GETVALUE(double, _T("br_sta"), _T("br_zerr"), nBRIdx);
				dXp += GETVALUE(double, _T("br_sta"), _T("br_posx"), nBRIdx);
				dX0 += GETVALUE(double, _T("br_sta"), _T("br_zerx"), nBRIdx);

				return																nFindNDIdx;
			}

		}
		nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nBRIdx);
	}

	return 0;
}

BOOL CSimulatorSLDView::CheckAutoNode(int nTargetNDIdx)
{
	//내가 대상설비이면 살린다.
	if (IsTargetObj(nTargetNDIdx))													return TRUE;

	if (GetNDStatus(nTargetNDIdx) == SW_OPEN)										return FALSE;

	//내가 대상설비가 아니어도 다분기(더미 또는 다회로)인지 확인하고, 다분기일 경우 이후를 탐색하며 스킵여부를 판단한다.
	//부하측으로 2분기이상 대상(자동화)설비가 있으면 살린다.
	int																				nCheckNDIdx;

	//더미이거나 다회로의 경우 분기를 확인하여 축약여부를 결정함
	nCheckNDIdx = GetCheckNDIdx(nTargetNDIdx);

	//더미노드이거나 다회로 가상더미이면...
	if (nCheckNDIdx)
	{
		int																			nNextAutoCnt(0);
		//더미노드 :: 바로 탐색시작! 나와 연결된 분기별 대상개폐기 유무 확인
		//다회로 가상더미 :: 부하측 단자로부터 탐색시작! 단자와 연결된 다음구간과 (다음구간의) 다음노드를 먼저 확인
		//즉, 다회로일때는 다음구간으로 먼저 진행. 더미일때는 나부터 바로 탐색시작
		if (IsMultiSw(nCheckNDIdx))
		{
			int																		nConnectCBSWIdx;
			int																		nSubNDIdx;

			nConnectCBSWIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nCheckNDIdx);
			while (nConnectCBSWIdx)
			{
				if (GetSwStatus(nConnectCBSWIdx) == SW_CLOSE)
				{
					nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nConnectCBSWIdx);
					if (nSubNDIdx != nTargetNDIdx)									nNextAutoCnt += FindNextAuto(nSubNDIdx, -1);
				}
				nConnectCBSWIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fnd"), nConnectCBSWIdx);
			}

			nConnectCBSWIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nCheckNDIdx);
			while (nConnectCBSWIdx)
			{
				if (GetSwStatus(nConnectCBSWIdx) == SW_CLOSE)
				{
					nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nConnectCBSWIdx);
					if (nSubNDIdx != nTargetNDIdx)									nNextAutoCnt += FindNextAuto(nSubNDIdx, -1);
				}
				nConnectCBSWIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tnd"), nConnectCBSWIdx);
			}
		}
		else
		{//더미노드 처리 -> 다음구간으로부터 다음노드 탐색시작
			int																		nNextNDIdx;
			int																		nConnectBRIdx;

			nConnectBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nCheckNDIdx);
			while (nConnectBRIdx)
			{
				if ((GetBrType(nConnectBRIdx) == 1) && (m_pBRTrace[nConnectBRIdx - 1] == FALSE))
				{
					nNextNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_tnd"), nConnectBRIdx);
					nNextAutoCnt += FindNextAutoRcv(nNextNDIdx, nConnectBRIdx);
				}
				nConnectBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nConnectBRIdx);
			}

			nConnectBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nCheckNDIdx);
			while (nConnectBRIdx)
			{
				if ((GetBrType(nConnectBRIdx) == 1) && (m_pBRTrace[nConnectBRIdx - 1] == FALSE))
				{
					nNextNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nConnectBRIdx);
					nNextAutoCnt += FindNextAutoRcv(nNextNDIdx, nConnectBRIdx);
				}
				nConnectBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nConnectBRIdx);
			}
		}

		//부하측으로 2분기이상에 대상설비가 존재하는 경우 살림.
		if (nNextAutoCnt >= 2)
			return TRUE;
	}

	return FALSE;
}

int CSimulatorSLDView::GetCheckNDIdx(int nNDIdx)
{
	int																				nNextNodeIdx;
	if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0 || GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx) > 0)//cbsw와 연결된 노드.
	{
		int																			nCbswIdx;
		if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0)				nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);

		if (IsMultiSw(nNDIdx))
		{
			if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nCbswIdx) == nNDIdx)	nNextNodeIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nCbswIdx);
			else																		nNextNodeIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nCbswIdx);
		}
		else
		{
			nNextNodeIdx = 0;
		}
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), nNDIdx) > 0)//DG
	{
		nNextNodeIdx = 0;
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_shunteq"), nNDIdx) > 0)//SHUNTEQ
	{
		nNextNodeIdx = 0;
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_svc"), nNDIdx) > 0)//SVC
	{
		nNextNodeIdx = 0;
	}
	else//br이랑만 연결되어 있음 - Dummy 또는 SVR 임
	{
		int																			nSVRIdx = 0;
		int																			nBRIdx;

		nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNDIdx);
		while (nBRIdx)
		{
			if (nBRIdx && GetBrType(nBRIdx) == 2)
			{
				nSVRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
				break;
			}

			nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nBRIdx);
		}

		if (nSVRIdx == 0)
		{
			nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNDIdx);
			while (nBRIdx)
			{
				if (nBRIdx && GetBrType(nBRIdx) == 2)
				{
					nSVRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
					break;
				}
				nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nBRIdx);
			}
		}
		if (nSVRIdx)//SVR
		{
			nNextNodeIdx = 0;
		}
		else//Dummy
		{
			nNextNodeIdx = nNDIdx;
		}
	}

	return nNextNodeIdx;
}

int CSimulatorSLDView::CheckConnectSw(int nNDIdx)
{
	//하나의 노드의 from, to가 모두 스위치이면 --> 다회로의 가상더미임.
	//이전설비의 부하측노드(nNextNDIdx)가 또다른 switch와 연결되어 있다.(방향은 모르지만, 한쪽은 nNextNDIdx의 전원측 switch일꺼고, 다른쪽으로 switch가 또 있다?!)
	//이전설비가 switch가 아니라면 절대 안들어가겠지.
	//따라서 아래 조건을 만족하면 nNextNDIdx는 다회로의 가상더미임.
	int																		nConnectCnt(0), nSWIdx;

	nSWIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
	while (nSWIdx)
	{
		nConnectCnt++;
		nSWIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fnd"), nSWIdx);
	}

	nSWIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);
	while (nSWIdx)
	{
		nConnectCnt++;
		nSWIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tnd"), nSWIdx);
	}

	return nConnectCnt;
}

int CSimulatorSLDView::GetToNDIdx(int nNDIdx)
{
	int																				nNextNodeIdx;
	if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0 || GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx) > 0)//cbsw와 연결된 노드.
	{
		int																			nCbswIdx;
		if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0)				nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);

		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nCbswIdx) == nNDIdx)	nNextNodeIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nCbswIdx);
		else																		nNextNodeIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nCbswIdx);
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), nNDIdx) > 0)//DG
	{
		nNextNodeIdx = nNDIdx;
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_shunteq"), nNDIdx) > 0)//SHUNTEQ
	{
		nNextNodeIdx = nNDIdx;
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_svc"), nNDIdx) > 0)//SVC
	{
		nNextNodeIdx = nNDIdx;
	}
	else//br이랑만 연결되어 있음 - Dummy 또는 SVR 임
	{
		int																			nSVRIdx = 0;
		int																			nBRIdx;

		nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNDIdx);
		while (nBRIdx)
		{
			if (nBRIdx && GetBrType(nBRIdx) == 2)
			{
				nSVRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
				break;
			}

			nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nBRIdx);
		}

		if (nSVRIdx == 0)
		{
			nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNDIdx);
			while (nBRIdx)
			{
				if (nBRIdx && GetBrType(nBRIdx) == 2)
				{
					nSVRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
					break;
				}
				nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nBRIdx);
			}
		}

		if (nSVRIdx)//SVR
		{
			if (GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx) == nNDIdx)	nNextNodeIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_tnd"), nBRIdx);
			else																nNextNodeIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx);
		}
		else//Dummy
		{
			nNextNodeIdx = nNDIdx;
		}
	}

	return nNextNodeIdx;
}

BOOL CSimulatorSLDView::IsTargetObj(int nNDIdx)
{
	if (m_nSLDMode == SHOW_SLDMODE_ALL)
		return TRUE;

	BOOL																			bAuto(FALSE);
	if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0 || GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx) > 0)//cbsw와 연결된 노드.
	{
		int																			nCbswIdx, nCbswType;
		if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0)				nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);

		nCbswType = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCbswIdx);

		if (m_nSLDMode == SHOW_SLDMODE_AUTO)//자동화모드
		{
			if (nCbswType < 4)
				bAuto = TRUE;//4번은 수동개폐기, 5번은 COS, 6번은 EFI
		}
		else//보호기기모드
		{
			if (nCbswType < 3) // 1:CB, 2:RC
				bAuto = TRUE;
			else
				bAuto = IsPCA(nCbswIdx);
		}
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), nNDIdx) > 0)//DG
	{
		if (((CMainFrame *)AfxGetApp()->GetMainWnd())->GetShowVirtualDG() == FALSE)
		{
			int nGenIdx, nTrexcl;
			nGenIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), nNDIdx);
			nTrexcl = GETVALUE(int, _T("gen_sta"), _T("gen_trexcl"), nGenIdx);
			if (nTrexcl == 4)
				bAuto = FALSE;
			else
			{
				if (m_nSLDMode == SHOW_SLDMODE_AUTO || m_nSLDMode == SHOW_SLDMODE_PROTECT)
					bAuto = TRUE;
			}
		}
		else
		{
			if (m_nSLDMode == SHOW_SLDMODE_AUTO || m_nSLDMode == SHOW_SLDMODE_PROTECT)
				bAuto = TRUE;
		}
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_shunteq"), nNDIdx) > 0)//SHUNTEQ
	{
		if (m_nSLDMode == SHOW_SLDMODE_AUTO)
			bAuto = TRUE;
	}
	else if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_svc"), nNDIdx) > 0)//SVC
	{
		if (m_nSLDMode == SHOW_SLDMODE_AUTO)
			bAuto = TRUE;
	}
	else//br이랑만 연결되어 있음 - Dummy 또는 SVR 임
	{
		if (m_nSLDMode == SHOW_SLDMODE_AUTO)
		{
			int																			nSVRIdx = 0;
			int																			nBRIdx;
			nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNDIdx);
			while (nBRIdx)
			{
				if (nBRIdx && GetBrType(nBRIdx) == 2)
				{
					nSVRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
					break;
				}

				nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nBRIdx);
			}

			if (nSVRIdx == 0)
			{
				nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNDIdx);
				while (nBRIdx)
				{
					if (nBRIdx && GetBrType(nBRIdx) == 2)
					{
						nSVRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), nBRIdx);
						break;
					}
					nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nBRIdx);
				}
			}
			if (nSVRIdx)//SVR
			{
				bAuto = TRUE;
			}
		}
	}

	return bAuto;
}

BOOL CSimulatorSLDView::FindNextAutoRcv(int nNDIdx, int nPreBRIdx)
{
	if (IsTargetObj(nNDIdx))
		return TRUE;

	if (GetNDStatus(nNDIdx) == SW_OPEN)												return FALSE;

	//다음 설비로 이동!
	int																				nToNDIdx;
	nToNDIdx = GetToNDIdx(nNDIdx);//설비의 끝노드로 설정.

	if (IsMultiSw(nToNDIdx)) //다회로개폐기
	{
		int																			nSubSwIdx, nSubNDIdx;
		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nToNDIdx);
		while (nSubSwIdx)
		{
			if (GetSwStatus(nSubSwIdx) == SW_CLOSE)
			{
				nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nSubSwIdx);
				if (nSubNDIdx != nNDIdx)
				{
					if (FindNextAuto(nSubNDIdx, -1))								return TRUE;
				}
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fnd"), nSubSwIdx);
		}

		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nToNDIdx);
		while (nSubSwIdx)
		{
			if (GetSwStatus(nSubSwIdx) == SW_CLOSE)
			{
				nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nSubSwIdx);
				if (nSubNDIdx != nNDIdx)
				{
					if (FindNextAuto(nSubNDIdx, -1))								return TRUE;
				}
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tnd"), nSubSwIdx);
		}
	}
	else
	{
		if (FindNextAuto(nToNDIdx, nPreBRIdx))										return TRUE;
	}

	return FALSE;
}

BOOL CSimulatorSLDView::FindNextAuto(int nNDIdx, int nPreBRIdx)
{
	int																				nNextNDIdx, nBRIdx;
	nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNDIdx);
	while (nBRIdx)
	{
		if ((GetBrType(nBRIdx) == 1) && (nBRIdx != nPreBRIdx))
		{
			nNextNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_tnd"), nBRIdx);
			if (FindNextAutoRcv(nNextNDIdx, nBRIdx))								return TRUE;
		}

		nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nBRIdx);
	}

	nBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNDIdx);
	while (nBRIdx)
	{
		if ((GetBrType(nBRIdx) == 1) && (nBRIdx != nPreBRIdx))
		{
			nNextNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx);
			if (FindNextAutoRcv(nNextNDIdx, nBRIdx))								return TRUE;
		}

		nBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nBRIdx);
	}

	return FALSE;
}

int CSimulatorSLDView::GetNDStatus(int nNDIdx)
{
	BOOL																			bStatus;
	if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0 || GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx) > 0)//cbsw와 연결된 노드.
	{
		int																			nCbswIdx;
		if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0)				nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);

		bStatus = GetSwStatus(nCbswIdx);
	}
	else
	{
		bStatus = SW_CLOSE;
	}

	return bStatus;
}

int CSimulatorSLDView::GetSwStatus(int nCbswIdx)
{
	return GETVALUE(int, _T("cbsw_dyn_mea"), _T("cbsw_nwstat"), nCbswIdx);
}

int CSimulatorSLDView::SearchDL(int nNDIdx, int nNoSsarchIdx)
{
	int																				nDlIdx;
	nDlIdx = GetCbswToNode(nNDIdx);
	if (nDlIdx > 0)																	return nDlIdx;

	int																				nRet(0);

	//노드와 연결된 cbsw(tisw포함)의 갯수를 체크한다.
	//1개이하( 0:더미노드, gen, shunt...svr등, 1:단일개폐기) -> 어차피 동일로직이므로 뭐가되든 상관없다.
	//멀티개폐기 생성 및 토폴로지 진행을 위해 멀티를 구분하는 것임(다분기 더비는 br을 통해 진행하고, 멀티개폐기는 cbsw(tisw)를 통해 진행함)
	//MULTIID를 통해 멀티개폐기여부 판정변경(20210628)
	if (IsMultiSw(nNDIdx)) //다회로개폐기(가상더미)
	{
		//다회로 단자들을 찾아가면 생성한다.
		int																			nSubSwIdx, nSubNDIdx;

		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
		while (nSubSwIdx)
		{
			nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nSubSwIdx);
			if (nSubNDIdx != nNoSsarchIdx)
			{
				nRet = FindCB(-1, nSubNDIdx);
				if (nRet)															return nRet;
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fnd"), nSubSwIdx);
		}

		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);
		while (nSubSwIdx)
		{
			nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nSubSwIdx);
			if (nSubNDIdx != nNoSsarchIdx)
			{
				nRet = FindCB(-1, nSubNDIdx);
				if (nRet)															return nRet;
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tnd"), nSubSwIdx);
		}
	}
	else
	{
		nRet = FindCB(-1, nNDIdx);
	}

	return nRet;
}

int CSimulatorSLDView::FindCB(int nPreBRIdx, int nNDIdx)
{
	int																				nCount(theAppDataMng->GetTableRealCount(_T("br_sta")));
	m_pBRTrace2 = new BYTE[nCount];
	memset(m_pBRTrace2, 0x00, sizeof(BYTE) * nCount);

	int																				nNextBRIdx, nRet;
	//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
	nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNDIdx);
	while (nNextBRIdx)
	{
		if ((GetBrType(nNextBRIdx) == 1) && (nPreBRIdx != nNextBRIdx))
		{
			nRet = FindCBRcv(nNextBRIdx, nNDIdx);
			if (nRet)
			{
				delete[] m_pBRTrace2;
				return nRet;
			}
		}
		nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
	}

	//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
	nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNDIdx);
	while (nNextBRIdx)
	{
		if ((GetBrType(nNextBRIdx) == 1) && (nPreBRIdx != nNextBRIdx))
		{
			nRet = FindCBRcv(nNextBRIdx, nNDIdx);
			if (nRet)
			{
				delete[] m_pBRTrace2;
				return nRet;
			}
		}
		nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
	}

	delete[] m_pBRTrace2;
	return 0;
}

int CSimulatorSLDView::FindCBRcv(int nBRIdx, int nFNDIdx)
{
	//이미 지나갔던 구간이면 다시 안간다.
	if (m_pBRTrace2[nBRIdx - 1])														return 0;

	//구간 Trace 체크
	m_pBRTrace2[nBRIdx - 1] = TRUE;

	int																				nTNDIdx, nNextNDIdx, nNextBRIdx, nRet;

	//구간의 다음 노드를 찾는다.
	if (GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx) == nFNDIdx)			nTNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_tnd"), nBRIdx);
	else																			nTNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx);

	if (nTNDIdx <= 0)
	{//축약모드에서는 구간의 부하측노드가 없으면 구간을 안만들고 끝(즉, 축약모드에서는 들어올 일 없음)
		return 0;
	}

	if (GetNDStatus(nTNDIdx) == SW_OPEN)											return 0;

	//CB를 찾았다.
	int																				nDlIdx;
	nDlIdx = GetCbswToNode(nTNDIdx);
	if (nDlIdx > 0)																return nDlIdx;

	//일반모드에서는 구간의 부하측노드가 없을경우 부하측에 가상노드를 하나만들고, 구간까지 생성한 후 종료.
	//nTNDIdx는 구간기준의 ToND -> 즉, 설비기준에서는 FND임
	//위에서 추가한 nTNDIdx 기준의 설비의 세부정보를 세팅하고, 설비기준에서의 TND(nNextNDIdx)로 변경.
	//DG, shunt, svc, Dummy등 토폴로지 기준 단일노드인 설비는 같은값이고, cbsw, tisw, svr 등은 설비기준 TND롤 변경
	//설비의 FND = 구간의 TND, 설비의 TND = 구간의 FND!!!!!!!!!!!!!!!!!!
	nNextNDIdx = GetToNDIdx(nTNDIdx);

// 	//설비의 부하측 노드와 연결된 cbsw(tisw포함)의 갯수를 체크한다.
// 	int																				nConnectCount;
// 	nConnectCount = CheckConnectSw(nNextNDIdx);
	//->CBSW의 멀티ID를 통한 멀티개폐기 확인으로 변경 -> 위 부분이 필요없어짐.

	//현재 설비(들어온쪽 설비)를 포함하여 2개이상 개폐기가 연결되어 있으면 멀티개폐기로 처리.
	//1개이하( 0:더미노드, gen, shunt...svr등, 1:단일개폐기) -> 어차피 동일로직이므로 뭐가되든 상관없다.
	//멀티개폐기 생성 및 토폴로지 진행을 위해 멀티를 구분하는 것임(다분기 더비는 br을 통해 진행하고, 멀티개폐기는 cbsw(tisw)를 통해 진행함) 
	if (IsMultiSw(nNextNDIdx)) //다회로개폐기
	{
		//설비의 FND로 상태값을 확인
		//다회로의 전원측 설비가 OPEN이면 그만.
		if (GetNDStatus(nTNDIdx) == SW_OPEN)										return 0;

		//다회로 단자들을 찾아가면 생성한다.
		int																			nSubSwIdx, nSubNDIdx;

		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNextNDIdx);
		while (nSubSwIdx)
		{
			nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nSubSwIdx);
			if (nSubNDIdx != nTNDIdx)
			{
				//설비의 TND로 상태값을 확인
				if (GetSwStatus(nSubSwIdx) == SW_CLOSE)
				{
					//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
					nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nSubNDIdx);
					while (nNextBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
						{
							nRet = FindCBRcv(nNextBRIdx, nSubNDIdx);
							if (nRet)												return nRet;
						}
						nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
					}

					nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nSubNDIdx);
					while (nNextBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
						{
							nRet = FindCBRcv(nNextBRIdx, nSubNDIdx);
							if (nRet)												return nRet;
						}
						nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
					}
				}
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fnd"), nSubSwIdx);
		}

		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNextNDIdx);
		while (nSubSwIdx)
		{
			nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nSubSwIdx);
			if (nSubNDIdx != nTNDIdx)
			{
				//설비의 TND로 상태값을 확인
				if (GetSwStatus(nSubSwIdx) == SW_CLOSE)
				{
					//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
					nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nSubNDIdx);
					while (nNextBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
						{
							nRet = FindCBRcv(nNextBRIdx, nSubNDIdx);
							if (nRet)												return nRet;
						}
						nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
					}

					nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nSubNDIdx);
					while (nNextBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
						{
							nRet = FindCBRcv(nNextBRIdx, nSubNDIdx);
							if (nRet)												return nRet;
						}
						nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
					}
				}
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tnd"), nSubSwIdx);
		}
	}
	else
	{
		//설비의 TND로 상태값을 확인
		//설비가 OPEN이면 그만.
		if (GetNDStatus(nNextNDIdx) == SW_OPEN)									return 0;

		//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNextNDIdx);
		while (nNextBRIdx)
		{
			if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
			{
				nRet = FindCBRcv(nNextBRIdx, nNextNDIdx);
				if (nRet)															return nRet;
			}
			nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
		}

		//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNextNDIdx);
		while (nNextBRIdx)
		{
			if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
			{
				nRet = FindCBRcv(nNextBRIdx, nNextNDIdx);
				if (nRet)															return nRet;
			}
			nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
		}
	}

	return 0;
}

int	CSimulatorSLDView::GetCbswToNode(int nNDIdx)
{
	int																				nCbswIdx(0);
	if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0 || GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx) > 0)//cbsw와 연결된 노드.
	{
		if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx) > 0)			nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);

		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCbswIdx) == 1)//CB이면
			return GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), nCbswIdx);
	}

	return -1;
}

int CSimulatorSLDView::FindBF(int nPreBRIdx, int nNDIdx)
{
	int																				nCount(theAppDataMng->GetTableRealCount(_T("br_sta")));
	m_pBRTrace2 = new BYTE[nCount];
	memset(m_pBRTrace2, 0x00, sizeof(BYTE) * nCount);

	int																				nNextBRIdx, nRet;
	//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
	nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNDIdx);
	while (nNextBRIdx)
	{
		if ((GetBrType(nNextBRIdx) == 1) && (nPreBRIdx != nNextBRIdx))
		{
			nRet = FindBFRcv(nNextBRIdx, nNDIdx);
			if (nRet)
			{
				delete[] m_pBRTrace2;
				return nRet;
			}
		}
		nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
	}

	//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
	nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNDIdx);
	while (nNextBRIdx)
	{
		if ((GetBrType(nNextBRIdx) == 1) && (nPreBRIdx != nNextBRIdx))
		{
			nRet = FindBFRcv(nNextBRIdx, nNDIdx);
			if (nRet)
			{
				delete[] m_pBRTrace2;
				return nRet;
			}
		}
		nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
	}

	delete[] m_pBRTrace2;
	return 0;
}

int CSimulatorSLDView::FindBFRcv(int nBRIdx, int nFNDIdx)
{
	//이미 지나갔던 구간이면 다시 안간다.
	if (m_pBRTrace2[nBRIdx - 1])														return 0;

	//구간 Trace 체크
	m_pBRTrace2[nBRIdx - 1] = TRUE;

	int																				nTNDIdx, nNextNDIdx, nNextBRIdx, nRet;

	//구간의 다음 노드를 찾는다.
	if (GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx) == nFNDIdx)			nTNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_tnd"), nBRIdx);
	else																			nTNDIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBRIdx);

	// 	//내부개방점을 판단추가. 이미 단선도내에서 그려진 노드이면 내부로 처리
	// 	if( m_pNDTrace[nTNDIdx-1] )
	// 	{
	// 		ASSERT( m_nDLIdx != 0 );//단선도를 그리던 중인데 선로IDX가 없다는건 말이 안됨.
	// 		return m_nDLIdx;
	// 	}

	if (nTNDIdx <= 0)
	{//축약모드에서는 구간의 부하측노드가 없으면 구간을 안만들고 끝(즉, 축약모드에서는 들어올 일 없음)
		return 0;
	}

	if (GetNDStatus(nTNDIdx) == SW_OPEN)											return 0;

	//CB를 찾았다.
	int																				nDlIdx;
	nDlIdx = GetCbswToNode(nTNDIdx);
	if (nDlIdx > 0)
		return nDlIdx;

	//일반모드에서는 구간의 부하측노드가 없을경우 부하측에 가상노드를 하나만들고, 구간까지 생성한 후 종료.
	//nTNDIdx는 구간기준의 ToND -> 즉, 설비기준에서는 FND임
	//위에서 추가한 nTNDIdx 기준의 설비의 세부정보를 세팅하고, 설비기준에서의 TND(nNextNDIdx)로 변경.
	//DG, shunt, svc, Dummy등 토폴로지 기준 단일노드인 설비는 같은값이고, cbsw, tisw, svr 등은 설비기준 TND롤 변경
	//설비의 FND = 구간의 TND, 설비의 TND = 구간의 FND!!!!!!!!!!!!!!!!!!
	nNextNDIdx = GetToNDIdx(nTNDIdx);

// 	//설비의 부하측 노드와 연결된 cbsw(tisw포함)의 갯수를 체크한다.
// 	int																				nConnectCount;
// 	nConnectCount = CheckConnectSw(nNextNDIdx);

	//현재 설비(들어온쪽 설비)를 포함하여 2개이상 개폐기가 연결되어 있으면 멀티개폐기로 처리.
	//1개이하( 0:더미노드, gen, shunt...svr등, 1:단일개폐기) -> 어차피 동일로직이므로 뭐가되든 상관없다.
	//멀티개폐기 생성 및 토폴로지 진행을 위해 멀티를 구분하는 것임(다분기 더비는 br을 통해 진행하고, 멀티개폐기는 cbsw(tisw)를 통해 진행함) 
	if (IsMultiSw(nNextNDIdx)) //다회로개폐기
	{
		//설비의 FND로 상태값을 확인
		//다회로의 전원측 설비가 OPEN이면 그만.
		if (GetNDStatus(nTNDIdx) == SW_OPEN)										return 0;

		//다회로 단자들을 찾아가면 생성한다.
		int																			nSubSwIdx, nSubNDIdx;

		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNextNDIdx);
		while (nSubSwIdx)
		{
			nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tnd"), nSubSwIdx);
			if (nSubNDIdx != nTNDIdx)
			{
				//설비의 TND로 상태값을 확인
				if (GetSwStatus(nSubSwIdx) == SW_CLOSE)
				{
					//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
					nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nSubNDIdx);
					while (nNextBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
						{
							nRet = FindBFRcv(nNextBRIdx, nSubNDIdx);
							if (nRet)												return nRet;
						}
						nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
					}

					nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nSubNDIdx);
					while (nNextBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
						{
							nRet = FindBFRcv(nNextBRIdx, nSubNDIdx);
							if (nRet)												return nRet;
						}
						nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
					}
				}
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fnd"), nSubSwIdx);
		}

		nSubSwIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNextNDIdx);
		while (nSubSwIdx)
		{
			nSubNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nSubSwIdx);
			if (nSubNDIdx != nTNDIdx)
			{
				//설비의 TND로 상태값을 확인
				if (GetSwStatus(nSubSwIdx) == SW_CLOSE)
				{
					//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
					nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nSubNDIdx);
					while (nNextBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
						{
							nRet = FindBFRcv(nNextBRIdx, nSubNDIdx);
							if (nRet)												return nRet;
						}
						nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
					}

					nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nSubNDIdx);
					while (nNextBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
						{
							nRet = FindBFRcv(nNextBRIdx, nSubNDIdx);
							if (nRet)												return nRet;
						}
						nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
					}
				}
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tnd"), nSubSwIdx);
		}
	}
	else
	{
		//설비의 TND로 상태값을 확인
		//설비가 OPEN이면 그만.
		if (GetNDStatus(nNextNDIdx) == SW_OPEN)									return 0;

		//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNextNDIdx);
		while (nNextBRIdx)
		{
			if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
			{
				nRet = FindBFRcv(nNextBRIdx, nNextNDIdx);
				if (nRet)															return nRet;
			}
			nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
		}

		//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNextNDIdx);
		while (nNextBRIdx)
		{
			if ((GetBrType(nNextBRIdx) == 1) && (m_pBRTrace2[nNextBRIdx - 1] == FALSE))
			{
				nRet = FindBFRcv(nNextBRIdx, nNextNDIdx);
				if (nRet)															return nRet;
			}
			nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
		}
	}

	return 0;
}

BOOL CSimulatorSLDView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CSimulatorSLDView::OnNcPaint()
{
	CRect																			rcWindow;
	GetWindowRect(&rcWindow);
	rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);

	int																				nX(0), nY(0);
	LONG lStyle = ::GetWindowLong(this->GetSafeHwnd(), GWL_STYLE);
	// WS_BORDER 속성이 적용되어 있느냐 없느냐에 따라 두께 계산
	if (lStyle & WS_BORDER)
	{
		nX = GetSystemMetrics(SM_CXSIZEFRAME);
		nY = GetSystemMetrics(SM_CYSIZEFRAME);
	}
	else
	{
		nX = GetSystemMetrics(SM_CXSIZEFRAME) - GetSystemMetrics(SM_CXBORDER);
		nY = GetSystemMetrics(SM_CYSIZEFRAME) - GetSystemMetrics(SM_CYBORDER);
	}

	CDC*																			pDC;
	pDC = GetWindowDC();

	// 테두리 영역만을 위해 가운데 영역 제외
	pDC->ExcludeClipRect(nX, nY, rcWindow.right - nX, rcWindow.bottom - nY);
	pDC->FillSolidRect(&rcWindow, SLDVIEW_BACKGROUND_COLOR);

	ReleaseDC(pDC);
}

void CSimulatorSLDView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	theAppDataMng->SetOnlineStudyMode(2);
	theAppDataMng->ConnectKASIMData(0, 2);

	CMainFrame*																		pMain;
	pMain = (CMainFrame *)AfxGetMainWnd();
	pMain->SetWindowText(_T("Simulator_SLD"));
	pMain->InitTreeView();

	m_pNaviDlg = new CNaviDlg();
	m_pNaviDlg->Create(this);
	SetNaviPosition();

	m_szImgPath.Format(_T("%s\\basemap"), GetModulePath());

	DefaultBaseMap();
// 
// 	LoadGis();
}

void CSimulatorSLDView::DefaultBaseMap()
{
	//중심좌표 ->충청북도청
	m_nZoomLevel = 12;
	m_ptOfficeCenter.dx = 5026087;//19레벨기준 화면중앙좌표.x
	m_ptOfficeCenter.dy = 2517872;//19레벨기준 화면중앙좌표.y
	m_ptOfficeCenter.dx /= pow(2., GIS_MAX_ZOOMLEVEL - m_nZoomLevel);
	m_ptOfficeCenter.dy /= pow(2., GIS_MAX_ZOOMLEVEL - m_nZoomLevel);

	m_dZoom = pow(2.0, m_nZoomLevel - GIS_MIN_ZOOMLEVEL) * TM_BASE_ZOOM;
	m_dpOfficeCenter_utm.dx = 999212.6137;
	m_dpOfficeCenter_utm.dy = 1848690.2018;

// 	m_nZoomLevel = 19;
// 	m_ptOfficeCenter.dx = 4978544.2332508136;
// 	m_ptOfficeCenter.dy = 2545553.4285361296;
// 
// 	m_dZoom = pow(2.0, m_nZoomLevel - GIS_MIN_ZOOMLEVEL) * TM_BASE_ZOOM;
// 	m_dpOfficeCenter_utm.dx = 987925.27421089099;
// 	m_dpOfficeCenter_utm.dy = 1855211.5954148816;
// 
// 	m_dpOfficeCenter_tm.dx = 232600.37121089155 - 37;//커지면 지도의 왼쪽으로이동
// 	m_dpOfficeCenter_tm.dy = 355312.15141488152 - 24;//커지면 지도의 아래쪽으로 이동

	ShiftMap();
}

void CSimulatorSLDView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_bLButtonDown = TRUE;
	m_ptStart = point;

	if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
	{
		if (m_pNodeView == NULL)														return;

		CPoint																			ptPosition;
		ptPosition.x = point.x - m_ptPosition.x;
		ptPosition.y = point.y - m_ptPosition.y;

		CNodeView*																		pFindNode;
		pFindNode = m_pNodeView->GetSelectNodeView(ptPosition);

		//선택된 설비표시
		if (pFindNode && (pFindNode->m_nSwKindID != NDTYPE_BACKUP))
			SetSelectDraw(pFindNode);
	}

	CView::OnLButtonDown(nFlags, point);
}

void CSimulatorSLDView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bLButtonDown)
	{
		CPoint																		ptChanged;
		ptChanged = point - m_ptStart;

		if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
			SetShiftPosition(ptChanged);
		else
			m_ptGisPosition -= ptChanged;

		m_ptStart = point;
		Invalidate();
	}
	else
	{
		if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
		{
			if (m_pNodeView == NULL)													return;

			CPoint																		ptPosition;
			ptPosition.x = point.x - m_ptPosition.x;
			ptPosition.y = point.y - m_ptPosition.y;

			CNodeView*																	pFindNode;
			pFindNode = m_pNodeView->GetSelectNodeView(ptPosition);
			if (pFindNode)
			{
				if (pFindNode != m_pTooltipNodeView)
				{
					SetToolTip(GetTooltipMsg(pFindNode));
					m_pTooltipNodeView = pFindNode;
				}

				m_pTooltipBranchView = NULL;
				return;
			}

			if (m_pBranchView == NULL)													return;

			CBranchView*																pFindBranch;
			pFindBranch = m_pBranchView->GetSelectBranchView(ptPosition, m_dZoomScale);
			if (pFindBranch)
			{
				if (pFindBranch != m_pTooltipBranchView)
				{
					SetToolTip(GetTooltipMsg(pFindBranch));
					m_pTooltipBranchView = pFindBranch;
				}

				m_pTooltipNodeView = NULL;
				return;
			}

			m_ToolTip.Hide();
			m_pTooltipNodeView = NULL;
			m_pTooltipBranchView = NULL;
		}
	}

	CView::OnMouseMove(nFlags, point);
}

void CSimulatorSLDView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	m_bLButtonDown = FALSE;

	if (m_nViewMode == SHOW_VIEWMODE_GIS )
	{
		if (m_ptGisPosition == CPoint(0, 0)) 
			return;

		m_ptOfficeCenter.dx += m_ptGisPosition.x;
		m_ptOfficeCenter.dy -= m_ptGisPosition.y;

		m_dpOfficeCenter_utm.dx += (m_ptGisPosition.x / m_dZoom);
		m_dpOfficeCenter_utm.dy -= (m_ptGisPosition.y / m_dZoom);

		ShiftMap();
// 		Invalidate(TRUE);
	}

	CView::OnLButtonUp(nFlags, point);
}

LRESULT CSimulatorSLDView::OnMovePosition(WPARAM wp, LPARAM lp)
{
	if ((int)wp == SHOW_VIEWMODE_SINGLE)
	{
		CPoint	ptShift;
		ptShift.x = (int)(((CPoint*)(lp))->x * m_dZoomScale);
		ptShift.y = (int)(((CPoint*)(lp))->y * m_dZoomScale);

		SetShiftPosition(ptShift);
	}
	else
	{
		double dx, dy;
		CDPoint* pDP;
		pDP = (CDPoint*)(lp);
		dx = pDP->dx - m_dpOfficeCenter_utm.dx;
		dy = pDP->dy - m_dpOfficeCenter_utm.dy;

		m_ptOfficeCenter.dx += (dx * m_dZoom);
		m_ptOfficeCenter.dy += (dy * m_dZoom);

		m_dpOfficeCenter_utm.dx = pDP->dx;
		m_dpOfficeCenter_utm.dy = pDP->dy;

		ShiftMap();
	}

	Invalidate();
	return FALSE;
}

BOOL CSimulatorSLDView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
	{
		if (m_nDLIdx <= 0)															return FALSE;

		double																		dOldZoom;
		dOldZoom = m_dZoomScale;

		BOOL																		bRet;//줌설정이 변경되었는지 확인
		if (zDelta > 0)																bRet = Zoom(ZOOM_IN);
		else																		bRet = Zoom(ZOOM_OUT);

		if (bRet)
		{
			CPoint																	ptPosition, point;
			point = pt;
			ScreenToClient(&point);

			//줌설정이 변경되었으면 비율에 맞게 단선도를 다시 그린다.
			MakeSLDBuffer(FALSE);

			//다시 그린 단선도에 현재위치로 포커스를 이동한다.
			ptPosition.x = -((point.x - m_ptPosition.x) / dOldZoom) * (m_dZoomScale - dOldZoom);
			ptPosition.y = -((point.y - m_ptPosition.y) / dOldZoom) * (m_dZoomScale - dOldZoom);

			SetShiftPosition(ptPosition);
		}
	}
	else
	{
		CPoint																	ptPosition, point, ptCen;
		point = pt;
		ScreenToClient(&point);

		CRect rect;
		GetClientRect(rect);
		ptCen = rect.CenterPoint();

		ptPosition = point - ptCen;
		if (zDelta > 0)
		{
			if (m_nZoomLevel == GIS_MAX_ZOOMLEVEL)								return FALSE;
			m_nZoomLevel++;

			if (::GetKeyState(VK_SHIFT) & 0x8000)
			{
				m_ptOfficeCenter.dx = ((m_ptOfficeCenter.dx) * 2.);
				m_ptOfficeCenter.dy = ((m_ptOfficeCenter.dy) * 2.);
			}
			else
			{
				m_ptOfficeCenter.dx = ((m_ptOfficeCenter.dx * 2) + ptPosition.x);
				m_ptOfficeCenter.dy = ((m_ptOfficeCenter.dy * 2) - ptPosition.y);

				m_dpOfficeCenter_utm.dx = (m_dpOfficeCenter_utm.dx + int((ptPosition.x / 2.) / m_dZoom + 0.5));
				m_dpOfficeCenter_utm.dy = (m_dpOfficeCenter_utm.dy - int((ptPosition.y / 2.) / m_dZoom + 0.5));
			}

			m_dZoom *= 2.0;

		}
		else
		{
			if (m_nZoomLevel == GIS_MIN_ZOOMLEVEL)								return FALSE;
			m_nZoomLevel--;

			if (::GetKeyState(VK_SHIFT) & 0x8000)
			{
				m_ptOfficeCenter.dx = ((m_ptOfficeCenter.dx) / 2.);
				m_ptOfficeCenter.dy = ((m_ptOfficeCenter.dy) / 2.);
			}
			else
			{
				m_ptOfficeCenter.dx = ((m_ptOfficeCenter.dx - ptPosition.x) / 2);
				m_ptOfficeCenter.dy = ((m_ptOfficeCenter.dy + ptPosition.y) / 2);

				m_dpOfficeCenter_utm.dx = (m_dpOfficeCenter_utm.dx - int(ptPosition.x / (m_dZoom)+0.5));
				m_dpOfficeCenter_utm.dy = (m_dpOfficeCenter_utm.dy + int(ptPosition.y / (m_dZoom)+0.5));
			}
			
			m_dZoom /= 2.0;
		}

		ShiftMap();
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CSimulatorSLDView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_nViewMode == SHOW_VIEWMODE_SINGLE)
	{
		if (m_pNodeView == NULL)														return;

		int																				nLoofIdx;
		nLoofIdx																		= GetSelectLoofCB(point);
		if (nLoofIdx >= 0 )
		{
			//루프 CB를 찾는다.
			CNodeView*																	pConnectNode;
			pConnectNode																= m_pNodeView->GetSelectNodeView(m_nLoofCBIdArr.GetAt(nLoofIdx), -1);

			//루프 CB로 이동
			CPoint																		ptTarget;
			ptTarget.x																	= (pConnectNode->m_nPosX * m_dZoomScale);
			ptTarget.y																	= (pConnectNode->m_nPosY * m_dZoomScale);

			SetCenterPosition(ptTarget);
			Invalidate();
			
			return;
		}
		CPoint																			ptPosition;
		ptPosition.x = point.x - m_ptPosition.x;
		ptPosition.y = point.y - m_ptPosition.y;

		CNodeView*																		pFindNode;
		pFindNode = m_pNodeView->GetSelectNodeView(ptPosition);

		if (pFindNode)
		{
			if (pFindNode->m_nSwKindID == NDTYPE_BACKUP)
			{
				if (pFindNode->m_nNDID[1] > 0)//내부연계점이면
				{
					//연계설비를 찾음
					CNodeView*															pConnectNode;
					pConnectNode														= m_pNodeView->GetSelectNodeView(pFindNode->m_nNDID[0], pFindNode->m_nNDID[1]);
					//연계설비로 이동
					CPoint																ptTarget;
					ptTarget.x = (pConnectNode->m_nPosX * m_dZoomScale);
					ptTarget.y = (pConnectNode->m_nPosY * m_dZoomScale);

					SetCenterPosition(ptTarget);
					Invalidate();
				}
				else//외부연계면
				{
					//백업DL로 이동
					MakeSLD(pFindNode->m_nNDID[0]);
					MakeSLDBuffer(TRUE);
				}
			}
			else
			{
				if (m_nSLDMode != SHOW_SLDMODE_ALL)
				{
					CMessageDlg dlg(_T("알림"), MB_OK);
					dlg.SetMessage(_T("계통 축약모드에서는 구간설정기능을\n지원하지 않습니다."));
					dlg.DoModal();
					return;
				}
				pFindNode->m_bBoundarySelect									= !pFindNode->m_bBoundarySelect;
				SetBoundaryArea(((CMainFrame*)AfxGetMainWnd())->GetAreaSetMode());
				MakeSLDBuffer(FALSE);

// 				if (!pFindNode->m_szCEQID.IsEmpty())								TransferMessage(PROGRAM_GISHMI, 1, pFindNode->m_szCEQID);
// 				else																TransferMessage(PROGRAM_GISHMI, 2, pFindNode->m_szLoc);
			}
		}
	}

	CView::OnLButtonDblClk(nFlags, point);
}

void CSimulatorSLDView::TransferMessage(int nProgramIdx, int nMessageType, CString szMessage)
{
	if (nProgramIdx == PROGRAM_GISHMI)
	{
		HWND																				pHMIWnd;
		pHMIWnd = ::FindWindow(NULL, _T("App-Simulator GIS HMI"));
		if (!pHMIWnd)																		return;

		TCHAR																				szSendMsg[128] = { 0, };
		swprintf_s(szSendMsg, _T("%s"), szMessage);

		COPYDATASTRUCT																		_cds = { 0, };
		_cds.dwData = (ULONG)nMessageType;
		_cds.cbData = (DWORD)sizeof(szSendMsg);
		_cds.lpData = (BYTE *)szSendMsg;
		::SendMessage(pHMIWnd, WM_COPYDATA, (WPARAM)this, (LPARAM)&_cds);
	}
	else if (nProgramIdx == PROGRAM_SIMUL_HMI)
	{
		HWND																				pHMIWnd;
		pHMIWnd = ::FindWindow(NULL, _T("Simulator_hmi"));
		if (!pHMIWnd)																		return;

		TCHAR																				szSendMsg[128] = { 0, };
		swprintf_s(szSendMsg, _T("%s"), szMessage);

		COPYDATASTRUCT																		_cds = { 0, };
		_cds.dwData = (ULONG)nMessageType;
		_cds.cbData = (DWORD)sizeof(szSendMsg);
		_cds.lpData = (BYTE *)szSendMsg;
		::SendMessage(pHMIWnd, WM_COPYDATA, (WPARAM)this, (LPARAM)&_cds);
	}
}

void CSimulatorSLDView::OnDestroy()
{
	CView::OnDestroy();
}

void CSimulatorSLDView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	SetNaviPosition();

	MakeGISBuffer(TRUE);
}

void CSimulatorSLDView::OnSetFault()
{
// 	if (m_pSetDfdDlg)
// 	{
// 		delete m_pSetDfdDlg;
// 		m_pSetDfdDlg = NULL;
// 	}
// 
// 	if (m_pNodeView == NULL)														return;
// 	if (m_pContextBranch == NULL)													return;
// 
// 	if (m_pContextBranch->m_bFaultArea)//고장해지
// 	{
// 		if (m_pFaultBranch)														m_pFaultBranch->m_bFaultArea = FALSE;
// 		m_pFaultBranch = NULL;
// 
// 		ResetFault();
// 		MakeSLDBuffer(FALSE);
// 		return;
// 	}
// 
// 	if (m_pFaultBranch)//기존고장정보가 있으면
// 	{
// 
// 		if (AfxMessageBox(L"계통내에 고장처리중입니다.\n기존 고장정보를 제거하고 진행하시겠습니까?(Y/N)", MB_YESNO) != IDYES)
// 			return;
// 
// 		ResetFault();
// 		m_pFaultBranch->m_bFaultArea = FALSE;//기존고장플래그 해지
// 		m_pFaultBranch = NULL;//기존고장정보 초기화
// 		MakeSLDBuffer(FALSE);
// 	}
// 
// 	CNodeViewArray																	pPathNodeView;
// 	if (GetDirectPathRcv(m_pNodeView, m_pContextBranch->m_nNode1, pPathNodeView))
// 	{
// 		int																			nSize;
// 		nSize = pPathNodeView.GetSize();
// 		if (nSize == 0)
// 		{
// 			AfxMessageBox(_T("CB라도 있어야지...ㅠㅠ"));
// 			return;
// 		}
// 
// 		//
// 		CNodeView*																	pNode, *pProtNode, *pSourceNode;
// 		int																			nGBRIdx, nGNDIdx;
// 		if (((CMainFrame *)AfxGetMainWnd())->GetViewMode() == SLDVIEW_ALL_MODE)	nGBRIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_gbr"), m_pContextBranch->m_nDbID);
// 		else																		nGBRIdx = m_pContextBranch->m_nDbID;
// 
// 		int																			nMtrIdx, nSSIdx;
// 		nMtrIdx = GETVALUE(int, _T("dl_sta"), _T("dl_ii_mtr"), m_nDLIdx);
// 		nSSIdx = GETVALUE(int, _T("mtr_sta"), _T("mtr_ii_ss"), nMtrIdx);
// 
// 		CFaultInfo																	pFaultInfo;
// 		pFaultInfo.m_nSSIdx = nSSIdx;
// 		pFaultInfo.m_nDLIdx = m_nDLIdx;
// 		pFaultInfo.m_nGBRIdx = nGBRIdx;
// 
// 		pProtNode = pPathNodeView.GetAt(0);
// 		if (((CMainFrame *)AfxGetMainWnd())->GetViewMode() == SLDVIEW_ALL_MODE)	nGNDIdx = GETVALUE(int, _T("nd_sta"), _T("nd_ii_gnd"), pProtNode->m_nNDID[1]);
// 		else																		nGNDIdx = pProtNode->m_nNDID[1];
// 		pFaultInfo.m_nProtGNDIdx = nGNDIdx;
// 
// 		for (int i = 0; i < nSize; i++)
// 		{
// 			pNode = pPathNodeView.GetAt(i);
// 			if (pNode->m_nKCIMType == 2)//Recloser
// 			{
// 				pProtNode = pNode;
// 				if (((CMainFrame *)AfxGetMainWnd())->GetViewMode() == SLDVIEW_ALL_MODE)	nGNDIdx = GETVALUE(int, _T("nd_sta"), _T("nd_ii_gnd"), pProtNode->m_nNDID[1]);
// 				else																		nGNDIdx = pProtNode->m_nNDID[1];
// 				pFaultInfo.m_nProtGNDIdx = nGNDIdx;
// 			}
// 		}
// 
// 		pSourceNode = pPathNodeView.GetAt(nSize - 1);
// 		if (((CMainFrame *)AfxGetMainWnd())->GetViewMode() == SLDVIEW_ALL_MODE)	nGNDIdx = GETVALUE(int, _T("nd_sta"), _T("nd_ii_gnd"), pSourceNode->m_nNDID[1]);
// 		else																		nGNDIdx = pSourceNode->m_nNDID[1];
// 		pFaultInfo.m_nSourceGNDIdx = nGNDIdx;
// 
// 		CNodeViewArray																pLoadSideNodeView;
// 		FindLoadSideRcv(pSourceNode->m_pCenter, pLoadSideNodeView);
// 		if (pLoadSideNodeView.GetSize() == 0)
// 		{
// // 			CMessageDlg dlg(_T("알림"), MB_OK);
// // 			dlg.SetMessage(_T("말단고장입니다.\n전원측 개폐기 개방~"));
// // 			dlg.DoModal();
// 			return;
// 		}
// 
// 		for (int i = 0; i < pLoadSideNodeView.GetSize(); i++)
// 		{
// 			pNode = pLoadSideNodeView.GetAt(i);
// 			if (((CMainFrame *)AfxGetMainWnd())->GetViewMode() == SLDVIEW_ALL_MODE)	nGNDIdx = GETVALUE(int, _T("nd_sta"), _T("nd_ii_gnd"), pNode->m_nNDID[0]);
// 			else																		nGNDIdx = pNode->m_nNDID[0];
// 			pFaultInfo.m_nLoadGNDIdxs.Add(nGNDIdx);
// 		}
// 
// 		CString																		strPath;
// 		strPath.Format(_T("%s\\DFDFaultGenInfor.txt"), GetModulePath());
// 		FILE*																		stream = _wfopen(strPath, _T("w+"));
// 		if (stream == NULL)
// 		{
// // 			CMessageDlg dlg(_T("오류"), MB_OK);
// // 			dlg.SetMessage(_T("DFDFaultGenInfor.txt파일을 생성할 수 없습니다."));
// // 			dlg.DoModal();
// 			return;
// 		}
// 
// 		CString																		szData;
// 		int																			nCbswIdx, nType;
// 		fwprintf(stream, _T("동작보호기기\n"));
// 		nCbswIdx = GetTargetSwToGNode(pFaultInfo.m_nProtGNDIdx, nType);
// 		szData.Format(_T("%d\t%d\t%s\t%s\n\n"), pFaultInfo.m_nProtGNDIdx, nCbswIdx, nType == 1 ? _T("CBSW") : _T("TISW"), pProtNode->m_szLoc);
// 		fwprintf(stream, szData);
// 
// 		fwprintf(stream, _T("전원측\n"));
// 		nCbswIdx = GetTargetSwToGNode(pFaultInfo.m_nSourceGNDIdx, nType);
// 		szData.Format(_T("%d\t%d\t%s\t%s\n\n"), pFaultInfo.m_nSourceGNDIdx, nCbswIdx, nType == 1 ? _T("CBSW") : _T("TISW"), pSourceNode->m_szLoc);
// 		fwprintf(stream, szData);
// 
// 		fwprintf(stream, _T("부하측\n"));
// 		for (int i = 0; i < pLoadSideNodeView.GetSize(); i++)
// 		{
// 			pNode = pLoadSideNodeView.GetAt(i);
// 			nCbswIdx = GetTargetSwToGNode(pFaultInfo.m_nLoadGNDIdxs.GetAt(i), nType);
// 			szData.Format(_T("%d\t%d\t%s\t%s\n"), pFaultInfo.m_nLoadGNDIdxs.GetAt(i), nCbswIdx, nType == 1 ? _T("CBSW") : _T("TISW"), pNode->m_szLoc);
// 			fwprintf(stream, szData);
// 		}
// 
// 		fclose(stream);
// 
// 		int																			nFaType(0), nMinValue(0), nFiType(0), nNextCbswIndex(0);
// 		m_pSetDfdDlg = new CSetDFDDlg(this);
// 		m_pSetDfdDlg->SetFaultInfo(&pFaultInfo);
// 
// 		m_pSetDfdDlg->Create();
// 		m_pSetDfdDlg->ShowWindow(SW_SHOW);
// 	}
// 	else
// 	{
// // 		CMessageDlg dlg(_T("경고"), MB_OK);
// // 		dlg.SetMessage(_T("고장구간의 전원을 찾을 수 없습니다.\n토폴로지 오류를 체크하세요."));
// // 		dlg.DoModal();
// 		return;
// 	}
}

void CSimulatorSLDView::Fault_Scenario()
{
	CString																szPath;
	szPath = GetModulePath() + _T("\\시나리오\\");
	CFolderPickerDialog													dlg(szPath);
	if (dlg.DoModal() != IDOK)											return;

	CString																szFileName;
	szPath = dlg.GetPathName();

	CFileFind															findfile; // file 검색을 위한 클래스
	BOOL																bFind;
	int																	nFileCnt = 0;
	szPath += _T("\\*.csv");
	bFind = findfile.FindFile((LPCTSTR)szPath);
	while (bFind)
	{
		bFind = findfile.FindNextFile();
		szPath = findfile.GetFilePath();
		szFileName = findfile.GetFileName();

		if (szFileName == _T("fltinfo_dyn_fio.csv"))
		{
			ReadFLTInfoData(szPath);
		}

		if (szFileName == _T("fiinfo_dyn_fio.csv"))
		{
			ReadFIInfoData(szPath);
		}
	}
}

void CSimulatorSLDView::ReadFLTInfoData(CString szPath)
{
	FILE*																stream;
	_wfopen_s(&stream, szPath, _T("r"));
	if (stream == NULL)
	{
		AfxMessageBox(_T("파일로드 실패"));
		return;
	}

	WCHAR															buffer[2048];
	memset(buffer, NULL, 2048);

	int																nHeaderLine = 1, nLines = 0;
	CString															szText, szData;
	while (fgetws(buffer, 2048, stream))
	{
		nLines++;
		if (nLines <= nHeaderLine)									continue;

		szText.Format(_T("%s"), buffer);

		AfxExtractSubString(szData, szText, 0, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_id"), nLines - 1, szData.GetBuffer());
		AfxExtractSubString(szData, szText, 1, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_ii_dl"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 2, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_dl_mrid"), nLines - 1, (unsigned long long)_wtof(szData));
		AfxExtractSubString(szData, szText, 3, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_ii_cbsw"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 4, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_cbsw_ceqid"), nLines - 1, (unsigned long long)_wtof(szData));
		AfxExtractSubString(szData, szText, 5, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_type"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 6, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_iaopr"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 7, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_ibopr"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 8, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_icopr"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 9, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_inopr"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 10, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_hi_fiinfo"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 11, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_hi_isocbsw"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 12, ',');				szData.Trim();	PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_time"), nLines - 1, szData.GetBuffer());
	}
}

void CSimulatorSLDView::ReadFIInfoData(CString szPath)
{
	FILE*															stream;
	_wfopen_s(&stream, szPath, _T("r"));
	if (stream == NULL)
	{
		AfxMessageBox(_T("파일로드 실패"));
		return;
	}

	WCHAR															buffer[2048];
	memset(buffer, NULL, 2048);

	int																nHeaderLine = 1, nLines = 0;
	CString															szText, szData;
	while (fgetws(buffer, 2048, stream))
	{
		nLines++;
		if (nLines <= nHeaderLine)									continue;

		szText.Format(_T("%s"), buffer);

		AfxExtractSubString(szData, szText, 0, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ii_cbsw"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 1, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_cbsw_ceqid"), nLines - 1, (unsigned long long)_wtof(szData));
		AfxExtractSubString(szData, szText, 2, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ii_fltinfo"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 3, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_si_fltinfo"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 4, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_fikind"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 5, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_fitype"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 6, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_iaopr"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 7, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ibopr"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 8, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_icopr"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 9, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_inopr"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 10, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ia"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 11, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ib"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 12, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ic"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 13, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_in"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 14, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_changeable"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 15, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_comerr"), nLines - 1, _wtoi(szData));
		AfxExtractSubString(szData, szText, 16, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ia_th"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 17, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ib_th"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 18, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ic_th"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 19, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_in_th"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 20, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_va"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 21, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_vb"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 22, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_vc"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 23, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_va_th"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 24, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_vb_th"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 25, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_vc_th"), nLines - 1, _wtof(szData));
		AfxExtractSubString(szData, szText, 26, ',');				szData.Trim();	PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_fiorer_diag"), nLines - 1, _wtoi(szData));
	}
}

void CSimulatorSLDView::ResetFault()
{
	int																				nCount(theAppDataMng->GetTableRealCount(_T("fltinfo_dyn_fio")));
	for (int i = 1; i <= nCount; i++)
	{
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_id"), i, _T("0"));
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_ii_dl"), i, 0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_dl_mrid"), i, (unsigned long long)0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_ii_cbsw"), i, 0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_cbsw_ceqid"), i, (unsigned long long)0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_type"), i, 0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_iaopr"), i, 0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_ibopr"), i, 0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_icopr"), i, 0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_inopr"), i, 0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_hi_fiinfo"), i, 0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_hi_isocbsw"), i, 0);
		PUTVALUE(_T("fltinfo_dyn_fio"), _T("fltinfo_time"), i, _T("0"));
	}

	nCount = theAppDataMng->GetTableRealCount(_T("fiinfo_dyn_fio"));
	for (int i = 1; i <= nCount; i++)
	{
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ii_cbsw"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_cbsw_ceqid"), i, (unsigned long long)0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ii_fltinfo"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_si_fltinfo"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_fikind"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_fitype"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_iaopr"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ibopr"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_icopr"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_inopr"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ia"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ib"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ic"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_in"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_changeable"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_comerr"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ia_th"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ib_th"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_ic_th"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_in_th"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_va"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_vb"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_vc"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_va_th"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_vb_th"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_vc_th"), i, 0);
		PUTVALUE(_T("fiinfo_dyn_fio"), _T("fiinfo_fiorer_diag"), i, 0);
	}

	nCount = theAppDataMng->GetTableRealCount(_T("isocbsw_dyn_dfdo"));
	for (int i = 1; i <= nCount; i++)
	{
		PUTVALUE(_T("isocbsw_dyn_dfdo"), _T("isocbsw_ii_cbsw"), i, 0);
		PUTVALUE(_T("isocbsw_dyn_dfdo"), _T("isocbsw_ceqid"), i, (unsigned long long)0);
		PUTVALUE(_T("isocbsw_dyn_dfdo"), _T("isocbsw_ii_fltinfo"), i, 0);
		PUTVALUE(_T("isocbsw_dyn_dfdo"), _T("isocbsw_si_fltinfo"), i, 0);
		PUTVALUE(_T("isocbsw_dyn_dfdo"), _T("isocbsw_updn"), i, 0);
		PUTVALUE(_T("isocbsw_dyn_dfdo"), _T("isocbsw_secid"), i, 0);
		PUTVALUE(_T("isocbsw_dyn_dfdo"), _T("isocbsw_old_state"), i, 0);
		PUTVALUE(_T("isocbsw_dyn_dfdo"), _T("isocbsw_control_state"), i, 0);
		PUTVALUE(_T("isocbsw_dyn_dfdo"), _T("isocbsw_control_result"), i, 0);
	}

	nCount = theAppDataMng->GetTableRealCount(_T("dsrseq_dyn_dsro"));
	for (int i = 1; i <= nCount; i++)
	{
		PUTVALUE(_T("dsrseq_dyn_dsro"), _T("dsrseq_ii_candidate"), i, 0);
		PUTVALUE(_T("dsrseq_dyn_dsro"), _T("dsrseq_ii_cbsw"), i, 0);
		PUTVALUE(_T("dsrseq_dyn_dsro"), _T("dsrseq_cbsw_ceqid"), i, (unsigned long long)0);
		PUTVALUE(_T("dsrseq_dyn_dsro"), _T("dsrseq_before_state"), i, 0);
		PUTVALUE(_T("dsrseq_dyn_dsro"), _T("dsrseq_after_state"), i, 0);
		PUTVALUE(_T("dsrseq_dyn_dsro"), _T("dsrseq_after_state_result"), i, 0);
		PUTVALUE(_T("dsrseq_dyn_dsro"), _T("dsrseq_defend_sw_index1"), i, 0);
		PUTVALUE(_T("dsrseq_dyn_dsro"), _T("dsrseq_defend_sw_index2"), i, 0);
		PUTVALUE(_T("dsrseq_dyn_dsro"), _T("dsrseq_return_sw_index1"), i, 0);
		PUTVALUE(_T("dsrseq_dyn_dsro"), _T("dsrseq_return_sw_index2"), i, 0);
	}
}

void CSimulatorSLDView::OnUpdateSetFault(CCmdUI *pCmdUI)
{
	if (m_pContextBranch)
	{
		if (m_pContextBranch->m_bFaultArea)						pCmdUI->SetText(_T("고장구간 해지"));
		else													pCmdUI->SetText(_T("고장구간 설정"));
	}

	pCmdUI->Enable(FALSE);
}

void CSimulatorSLDView::OnResetFault()
{
	if (m_pFaultBranch)//기존고장정보가 있으면
	{
		m_pFaultBranch->m_bFaultArea = FALSE;//기존고장플래그 해지
		m_pFaultBranch = NULL;//기존고장정보 초기화
	}
	ResetFault();
	MakeSLD(m_nDLIdx);
	MakeSLDBuffer(FALSE);
}

void CSimulatorSLDView::OnUpdateResetFault(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

int CSimulatorSLDView::GetBrType(int nBrIdx)
{
	int nGbrIdx, nType;
	nGbrIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_gbr"), nBrIdx);
	if (nGbrIdx == 0)													return 0;

	nType = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nGbrIdx);
	return nType;
}

void CSimulatorSLDView::ShowSLDView(int nMode)
{
	if (m_pNodeView == NULL)
	{
		m_nGisMode = SHOW_GISMODE_SINGLE;
		m_nViewMode = nMode;
		DefaultBaseMap();
		Invalidate();
		return;
	}

	m_bAction = TRUE;
	if (m_nViewMode == SHOW_VIEWMODE_SINGLE)//SLD -> GIS
	{
		MakeSLDBuffer(TRUE);
		
		CalculationScale();//GIS배경을 기본배율 설정
		ShiftMap();//그리기

		m_dStZoomScale = m_dZoomScale;

		m_nSLDStep = 0;
		m_nGISStep = 0;
		SetTimer(1, ANIMATION_SPEED, NULL);
	}
	else//GIS -> SLD
	{
		m_nGisMode = SHOW_GISMODE_SINGLE;

		SetGISScale();
		ShiftMap();
		
		m_nSLDStep = 0;
		m_nGISStep = 11;
		SetTimer(11, ANIMATION_SPEED, NULL);
	}
}

void CSimulatorSLDView::SetGISScale()
{
	double dx, dy;
	dx = m_ptBaseCenterPos.dx - m_dpOfficeCenter_utm.dx;
	dy = m_ptBaseCenterPos.dy - m_dpOfficeCenter_utm.dy;

	m_dpOfficeCenter_utm.dx += dx;
	m_dpOfficeCenter_utm.dy += dy;

	m_ptOfficeCenter.dx += (dx * m_dZoom);
	m_ptOfficeCenter.dy += (dy * m_dZoom);

	if (m_nZoomLevel != m_nBaseZoomlevel)
	{
		if (m_nZoomLevel > m_nBaseZoomlevel)//zoom_out
		{
			m_ptOfficeCenter.dx = (m_ptOfficeCenter.dx / pow(2., int(m_nZoomLevel - m_nBaseZoomlevel)));
			m_ptOfficeCenter.dy = (m_ptOfficeCenter.dy / pow(2., int(m_nZoomLevel - m_nBaseZoomlevel)));
		}
		else
		{
			m_ptOfficeCenter.dx = (m_ptOfficeCenter.dx * pow(2., int(m_nBaseZoomlevel - m_nZoomLevel)));
			m_ptOfficeCenter.dy = (m_ptOfficeCenter.dy * pow(2., int(m_nBaseZoomlevel - m_nZoomLevel)));
		}

		m_nZoomLevel = m_nBaseZoomlevel;
		m_dZoom = pow(2., (m_nZoomLevel - GIS_MIN_ZOOMLEVEL)) * TM_BASE_ZOOM;
	}																
}

void CSimulatorSLDView::CalculationScale()
{
	if (m_pNodeView == NULL)									return;

	m_nSLDStep = 0;

	if( m_nViewMode == SHOW_VIEWMODE_SINGLE )					m_nGISStep = 0;
	else														m_nGISStep = 11;

	CRect rect;
	GetClientRect(rect);

	//////////////////////////////////////////////////////////////////////////
	//GIS가 한화면에 들어오기위한 배율 계산.
	m_ptBaseCenterPos.dx = (m_dl + m_dr) / 2.0;
	m_ptBaseCenterPos.dy = (m_dt + m_db) / 2.0;

	double								dx, dy, dSize;
	int									nZoomLevelX, nZoomLevelY;
	dx = m_dr - m_dl;
	for (int i = GIS_MAX_ZOOMLEVEL; i >= GIS_MIN_ZOOMLEVEL; i--)
	{
		dSize = rect.Width() / (pow(2.0, i- GIS_MIN_ZOOMLEVEL) * TM_BASE_ZOOM);
		if (dSize > dx)
		{
			nZoomLevelX = i;
			break;
		}
	}

	dy = m_db - m_dt;
	for (int i = GIS_MAX_ZOOMLEVEL; i >= GIS_MIN_ZOOMLEVEL; i--)
	{
		dSize = rect.Height() / (pow(2.0, i - GIS_MIN_ZOOMLEVEL) * TM_BASE_ZOOM);
		if (dSize > dy)
		{
			nZoomLevelY = i;
			break;
		}
	}

	if (nZoomLevelX < nZoomLevelY)			m_nBaseZoomlevel = nZoomLevelX;
	else									m_nBaseZoomlevel = nZoomLevelY;

	SetGISScale();//GIS (기본)배율 적용
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//단선도가 한화면에 들어오기위한 배율 계산.
	double								dSizeX, dSizeY;
	dSizeX = m_pNodeView->GetMaxAxisX() + SLDVIEW_WIDTH_MARGIN;
	dSizeY = m_pNodeView->GetMaxAxisY() + SLDVIEW_HEIGHT_MARGIN;

	if ((rect.Width() / dSizeX) <= (rect.Height() / dSizeY))
		m_dMinZoomScale = (rect.Width() / dSizeX);
	else
		m_dMinZoomScale = (rect.Height() / dSizeY);

	if (m_dMinZoomScale > m_dZoomScale)			m_dMinZoomScale = m_dZoomScale;

// 	CPoint ptStart;
// 	ptStart = CPoint((200 - m_pNodeView->m_nPosX)*m_dMinZoomScale, rect.CenterPoint().y - (m_pNodeView->m_nPosY*m_dMinZoomScale));
// 	SetSLDDPoint(ptStart);//최소사이즈배율에서의 단선도설비 GIS좌표 계산(단선도의 끝 =>> GIS의 시작)
	CPoint ptPosition;
	ptPosition = CPoint(200 - (m_pNodeView->m_nPosX*m_dMinZoomScale), rect.CenterPoint().y - (m_pNodeView->m_nPosY*m_dMinZoomScale));

	CRect																			_rect;
	GetClientRect(&_rect);

	if (ptPosition.x > _rect.CenterPoint().x - (SLDVIEW_WIDTH_MARGIN*m_dZoomScale))
		ptPosition.x = _rect.CenterPoint().x - (SLDVIEW_WIDTH_MARGIN*m_dZoomScale);
	if (ptPosition.y > _rect.CenterPoint().y - (SLDVIEW_HEIGHT_MARGIN*m_dZoomScale))
		ptPosition.y = _rect.CenterPoint().y - (SLDVIEW_HEIGHT_MARGIN*m_dZoomScale);

	if (m_sizeCurSLD.cx + ptPosition.x < _rect.CenterPoint().x + (SLDVIEW_WIDTH_MARGIN))
		ptPosition.x = _rect.CenterPoint().x + (SLDVIEW_WIDTH_MARGIN)-m_sizeCurSLD.cx;
	if (m_sizeCurSLD.cy + ptPosition.y < _rect.CenterPoint().y + (SLDVIEW_HEIGHT_MARGIN))
		ptPosition.y = _rect.CenterPoint().y + (SLDVIEW_HEIGHT_MARGIN)-m_sizeCurSLD.cy;

	SetSLDDPoint(CPoint(-ptPosition.x, ptPosition.y));//최소사이즈배율에서의 단선도설비 GIS좌표 계산(단선도의 끝 =>> GIS의 시작)

	m_pNodeView->SetGISBranchPos(m_pBranchView);
}

void CSimulatorSLDView::MakeGISBuffer(BOOL bInit)
{
	return;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	m_ptGisPosition = CPoint(0, 0);
	DeleteGISBuffer();

	CClientDC																		dc(this);
	CRect																			rect;
	GetClientRect(&rect);

	m_pGISBuffer = new CDC();
	m_pGISBuffer->CreateCompatibleDC(&dc);

	// 메모리 비트맵 선언
	CBitmap bmpBuffer;

	// 호환성 있는 메모리 비트맵 생성하여 메모리 DC에 설정(메모리 버퍼사이즈는 단선도 최대사이즈로 한번만 생성)
	bmpBuffer.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	m_pGISBitmap = (CBitmap *)m_pGISBuffer->SelectObject(&bmpBuffer);

	//m_pGISBuffer->PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);
	m_pGISBuffer->FillSolidRect(rect, GISVIEW_BACKGROUND_COLOR);
	m_pGISBuffer->SetBkMode(TRANSPARENT);

	int nPosX(0), nPosY(0);
	nPosX = rect.CenterPoint().x - int(fmod(m_ptOfficeCenter.dx, (double)TILEMAP_SIZE) - ((TILEMAP_SIZE*(GIS_IMAGE_CNT_X%2)) / 2)) - ((TILEMAP_SIZE * GIS_IMAGE_CNT_X) / 2 );
	nPosY = rect.CenterPoint().y - int(((TILEMAP_SIZE*(GIS_IMAGE_CNT_Y%2)) / 2) - fmod(m_ptOfficeCenter.dy, (double)TILEMAP_SIZE)) - ((TILEMAP_SIZE * GIS_IMAGE_CNT_Y) / 2 );

	CBrush *pOldbrush;
	pOldbrush = (CBrush*)m_pGISBuffer->SelectStockObject(NULL_BRUSH);

	for (int i = 0; i < GIS_IMAGE_CNT_X; i++)
	{
		for (int j = 0; j < GIS_IMAGE_CNT_Y; j++)
		{
			if (!m_pBgImage[i][j].IsNull())
			{
				m_pBgImage[i][j].Draw(*m_pGISBuffer, ((i*TILEMAP_SIZE) + nPosX), ((((GIS_IMAGE_CNT_Y - 1) - j) * TILEMAP_SIZE) + nPosY), TILEMAP_SIZE, TILEMAP_SIZE);
//   				m_pGISBuffer->Rectangle(CRect(((i*TILEMAP_SIZE) + nPosX), ((((GIS_IMAGE_CNT_Y - 1) - j) * TILEMAP_SIZE) + nPosY), ((i*TILEMAP_SIZE) + nPosX) + TILEMAP_SIZE, ((((GIS_IMAGE_CNT_Y - 1) - j) * TILEMAP_SIZE) + nPosY) + TILEMAP_SIZE));
			}
		}
	}

	if (m_nGisMode == SHOW_GISMODE_SINGLE)
		DrawGIS(m_pGISBuffer);
	else
		DrawGISAll(m_pGISBuffer);

	m_pGISBuffer->SelectObject(pOldbrush);

	CPen					pen(PS_SOLID, 1, RGB(255,0,0));
	CPen*					pOldPen = m_pGISBuffer->SelectObject(&pen);
	m_pGISBuffer->MoveTo(CPoint(rect.CenterPoint().x -15, rect.CenterPoint().y));
	m_pGISBuffer->LineTo(CPoint(rect.CenterPoint().x +15, rect.CenterPoint().y));
	m_pGISBuffer->MoveTo(CPoint(rect.CenterPoint().x, rect.CenterPoint().y - 15));
	m_pGISBuffer->LineTo(CPoint(rect.CenterPoint().x, rect.CenterPoint().y + 15));
	m_pGISBuffer->SelectObject(pOldPen);

	
// 	CFont						font, *pOldfont;
// 	font.CreateFont(12, 0, 0, 0, 800, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
// 		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("굴림"));
// 	pOldfont = m_pGISBuffer->SelectObject(&font);
// 	CString szText;
// 	szText.Format(_T("%.6lf::%.6lf"), m_dpOfficeCenter_utm.dx, m_dpOfficeCenter_utm.dy);
// 	m_pGISBuffer->DrawText(szText, CRect( rect.CenterPoint().x - 100, rect.CenterPoint().y+10, rect.CenterPoint().x+100, rect.CenterPoint().y+50), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
// 	m_pGISBuffer->SelectObject(pOldfont);
// 	font.DeleteObject();

	Invalidate();
}

void CSimulatorSLDView::ShiftMap(void)
{
	for (int i = 0; i < GIS_IMAGE_CNT_X; i++)
	{
		for (int j = 0; j < GIS_IMAGE_CNT_Y; j++)
			m_pBgImage[i][j].Destroy();
	}

	CString szPath;
	int nPosX, nPosY;

	nPosX = (int)(m_ptOfficeCenter.dx / TILEMAP_SIZE);
	nPosY = (int)((pow(2.0, m_nZoomLevel - BASE_ZOOMLEVEL) * ZERO_POS_Y) + (m_ptOfficeCenter.dy / TILEMAP_SIZE));

	for (int i = 0; i < GIS_IMAGE_CNT_X; i++)
	{
		for (int j = 0; j < GIS_IMAGE_CNT_Y; j++)
		{
			szPath.Format(_T("%s\\%d\\%d\\%d.png"), m_szImgPath, m_nZoomLevel, (nPosX - (GIS_IMAGE_CNT_X / 2)) + i, (nPosY - ((GIS_IMAGE_CNT_Y - 1) / 2)) + j);
			m_pBgImage[i][j].Load(szPath);
		}
	}

	MakeGISBuffer(TRUE);
}

void CSimulatorSLDView::DrawGIS(CDC* BufferDC)
{
	if (m_pNodeView == NULL)														return;

	BufferDC->SetTextAlign(TA_LEFT);
	BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
	BufferDC->SetBkMode(TRANSPARENT);

	BOOL																			bShowValue(TRUE);
	CFont																			font, *pOldfont;
	font.CreateFont(12, 0, 0, 0, 800, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("굴림체"));
	pOldfont = BufferDC->SelectObject(&font);

	CRect rect;
	GetClientRect(rect);

	if (m_nGISStep == 0)
		m_pBranchView->DrawGIS(BufferDC, 1, m_dZoom, m_dpOfficeCenter_utm.dx, m_dpOfficeCenter_utm.dy, rect.CenterPoint(), m_nSLDStep);
	else
		m_pBranchView->DrawGIS2(BufferDC, 1, m_dZoom, m_dpOfficeCenter_utm.dx, m_dpOfficeCenter_utm.dy, rect.CenterPoint(), m_nGISStep);

	m_pNodeView->DrawGIS(BufferDC, 1, m_dZoom, m_dpOfficeCenter_utm.dx, m_dpOfficeCenter_utm.dy, rect.CenterPoint(), m_nSLDStep, m_nZoomLevel);

	BufferDC->SelectObject(pOldfont);
	font.DeleteObject();
}

void CSimulatorSLDView::DrawGISAll(CDC* BufferDC)
{
	BOOL																			bShowValue(TRUE);
	CFont																			font, *pOldfont;
	font.CreateFont(12, 0, 0, 0, 800, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("굴림체"));
	pOldfont = BufferDC->SelectObject(&font);

	CRect rect;
	GetClientRect(rect);

	CGisSec* pGisSec;
	for (int i = 0; i < m_pGisSecArr.GetSize(); i++)
	{
		pGisSec = m_pGisSecArr.GetAt(i);
		pGisSec->Draw(BufferDC, 1, m_dZoom, m_dpOfficeCenter_utm.dx, m_dpOfficeCenter_utm.dy, rect.CenterPoint());
	}

	BufferDC->SelectObject(pOldfont);
	font.DeleteObject();
}

void CSimulatorSLDView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)//SLD->GIS 1단계..
	{
		if (m_nSLDStep >= SIMULATION_SLD_STEP)
		{
			KillTimer(1);
			m_nViewMode = SHOW_VIEWMODE_GIS;
			
			SetTimer(2, ANIMATION_SPEED, NULL);
			return;
		}

		m_nSLDStep++;
		DrawSimulStep1();
	}
	else if (nIDEvent == 2)//SLD->GIS 2단계
	{
		if (m_nSLDStep <= 0)
		{
			KillTimer(2);
			SetTimer(3, ANIMATION_SPEED, NULL);

			return;
		}

		m_nSLDStep--;
		MakeGISBuffer(TRUE);
	}
	else if (nIDEvent == 3)//SLD->GIS 3단계
	{
		if (m_nGISStep >= SIMULATION_GIS_STEP)
		{
			KillTimer(3);
			m_bAction = FALSE;
			return;
		}

		m_nGISStep++;
		MakeGISBuffer(TRUE);
	}
	if (nIDEvent == 11)//GIS->SLD 1단계..
	{
		if (m_nGISStep <= 0)
		{
			KillTimer(11);
			SetTimer(12, ANIMATION_SPEED, NULL);
			return;
		}

		m_nGISStep--;
		MakeGISBuffer(TRUE);
	}
	else if (nIDEvent == 12)//GIS->SLD 2단계..
	{
		if (m_nSLDStep >= SIMULATION_SLD_STEP)
		{
			KillTimer(12);
			m_nViewMode = SHOW_VIEWMODE_SINGLE;
			SetTimer(13, ANIMATION_SPEED, NULL);
			return;
		}

		m_nSLDStep++;
		MakeGISBuffer(TRUE);
	}
	else if (nIDEvent == 13)//GIS->SLD 3단계..
	{
		if (m_nSLDStep <= 0)
		{
			KillTimer(13);
			m_bAction = FALSE;
			return;
		}

		m_nSLDStep--;
		DrawSimulStep1();
	}
	CView::OnTimer(nIDEvent);
}

void CSimulatorSLDView::DrawSimulStep1()
{
	m_dZoomScale = m_dStZoomScale - ((m_dStZoomScale - m_dMinZoomScale) * ((double)m_nSLDStep / SIMULATION_SLD_STEP));
	//여기서 메모리DC에 단선도를 그린다.
	CPoint ptStart;
	ptStart = DrawSLD(m_pSLDBuffer, FALSE);//CB의 좌표를 넘겨받고 화면의 가운데로 배치하자.

	CRect																		rect;
	GetClientRect(&rect);

	//화면이동 좌표를 초기화하고,
	m_ptPosition = CPoint(0, 0);

	//CB의 좌표를 200, Center.y에 맞춘다.
	ptStart.x *= m_dZoomScale;
	ptStart.y *= m_dZoomScale;

// 	m_ptPosition =   CPoint(((200 * m_dZoomScale) - ptStart.x), (rect.CenterPoint().y - ptStart.y));
	SetShiftPosition(CPoint((200 - ptStart.x), (rect.CenterPoint().y - ptStart.y)));

	Invalidate();
}

void CSimulatorSLDView::SetSLDDPoint(CPoint ptShift)
{
	if (m_pNodeView == NULL)															return;
	
	CRect rect;
	GetClientRect(rect);
	SetSLDDPointRcv(m_pNodeView, ptShift, rect);
}

void CSimulatorSLDView::SetSLDDPointRcv(CNodeView* pNodeView, CPoint ptShift, CRect rect)
{
	pNodeView->m_pSLDDPoint.dx = (((pNodeView->m_nPosX*m_dMinZoomScale) - ptShift.x) - rect.CenterPoint().x) / m_dZoom + m_dpOfficeCenter_utm.dx - 0.5;
	pNodeView->m_pSLDDPoint.dy = (rect.CenterPoint().y - ((pNodeView->m_nPosY*m_dMinZoomScale) + ptShift.y)) / m_dZoom + m_dpOfficeCenter_utm.dy - 0.5;

	if (pNodeView->m_pCenter)											SetSLDDPointRcv(pNodeView->m_pCenter, ptShift, rect);
	if (pNodeView->m_pLeft)												SetSLDDPointRcv(pNodeView->m_pLeft, ptShift, rect);
	if (pNodeView->m_pRight)											SetSLDDPointRcv(pNodeView->m_pRight, ptShift, rect);
	if (pNodeView->m_pLeftTop)											SetSLDDPointRcv(pNodeView->m_pLeftTop, ptShift, rect);
	if (pNodeView->m_pRightBottom)										SetSLDDPointRcv(pNodeView->m_pRightBottom, ptShift, rect);
}

void CSimulatorSLDView::SetBranchPolePos(CBranchView* pBranch, CNodeView* pFNodeView, CNodeView* pTNodeView)
{
	int nLNSECIdx, nINNERPOLEIdx;
	nLNSECIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), pBranch->m_nDbID);

	nINNERPOLEIdx = GETVALUE(int, _T("lnsec_sta"), _T("lnsec_hi_innerpole"), nLNSECIdx);
	if (nINNERPOLEIdx == 0)
	{
// 		AfxMessageBox(_T("LNSEC - INNERPOLE 연결오류!"));
		return;
	}

	CDPoint* pt = new CDPoint();
	pt->dx = GETVALUE(double, _T("innerpole_sta"), _T("innerpole_xcoodi"), nINNERPOLEIdx);
	pt->dy = GETVALUE(double, _T("innerpole_sta"), _T("innerpole_ycoodi"), nINNERPOLEIdx);

	pBranch->m_ptArr.Add(pt);

	if (m_dl > pt->dx)	m_dl = pt->dx;
	if (m_dt > pt->dy)	m_dt = pt->dy;
	if (m_dr < pt->dx)	m_dr = pt->dx;
	if (m_db < pt->dy)	m_db = pt->dy;

	pFNodeView->m_pGISDPoint.dx = pt->dx;
	pFNodeView->m_pGISDPoint.dy = pt->dy;

	pt = NULL;
	nINNERPOLEIdx = GETVALUE(int, _T("innerpole_sta"), _T("innerpole_si_lnsec"), nINNERPOLEIdx);
	while (nINNERPOLEIdx)
	{
		pt = new CDPoint();
		pt->dx = GETVALUE(double, _T("innerpole_sta"), _T("innerpole_xcoodi"), nINNERPOLEIdx);
		pt->dy = GETVALUE(double, _T("innerpole_sta"), _T("innerpole_ycoodi"), nINNERPOLEIdx);
		pBranch->m_ptArr.Add(pt);

		if (m_dl > pt->dx)	m_dl = pt->dx;
		if (m_dt > pt->dy)	m_dt = pt->dy;
		if (m_dr < pt->dx)	m_dr = pt->dx;
		if (m_db < pt->dy)	m_db = pt->dy;

		nINNERPOLEIdx = GETVALUE(int, _T("innerpole_sta"), _T("innerpole_si_lnsec"), nINNERPOLEIdx);
	}

// 	ASSERT(pt != NULL);

	if (pt)
	{
		pTNodeView->m_pGISDPoint.dx = pt->dx;
		pTNodeView->m_pGISDPoint.dy = pt->dy;

		pBranch->m_pSLDDPoint2.dx = pTNodeView->m_pSLDDPoint.dx;
		pBranch->m_pSLDDPoint2.dy = pTNodeView->m_pSLDDPoint.dy;
		pBranch->m_pGISDPoint2.dx = pTNodeView->m_pGISDPoint.dx;
	}

	pBranch->SetZipDPArray();
	pBranch->SetZip();
}

void CSimulatorSLDView::ToggleGisMode()
{
	if (m_nViewMode != SHOW_VIEWMODE_GIS)
		return;

	if (m_nGisMode == SHOW_GISMODE_SINGLE)
		m_nGisMode = SHOW_GISMODE_ALL;
	else
		m_nGisMode = SHOW_GISMODE_SINGLE;

	MakeGISBuffer(TRUE);
}

void CSimulatorSLDView::LoadGis()
{
	LoadGisObj();
	LoadGisSec();
}

void CSimulatorSLDView::LoadGisObj()
{
}

void CSimulatorSLDView::LoadGisSec()
{
	CGisSec*															pGisSec;
	CPole*																pPole;
	int																	nCount, nBrIdx, nPoleIdx;
	nCount																= theAppDataMng->GetTableRealCount(_T("lnsec_sta"));
	for (int i = 1; i <= nCount; i++)
	{
		pGisSec = new CGisSec();
		m_pGisSecArr.Add(pGisSec);

		pGisSec->m_nDbID = i;
		pGisSec->m_nOverHead = GETVALUE(int, _T("lnsec_sta"), _T("lnsec_constype"), i);
		pGisSec->m_szCEQID.Format(_T("%llu"), GETVALUE(unsigned long long, _T("lnsec_sta"), _T("lnsec_ceqid"), i));

		nBrIdx = GETVALUE(int, _T("lnsec_sta"), _T("lnsec_ii_br"), i);
		pGisSec->m_nNDID[0] = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBrIdx);
		pGisSec->m_nNDID[1] = GETVALUE(int, _T("br_sta"), _T("br_ii_tnd"), nBrIdx);

		nPoleIdx = GETVALUE(int, _T("lnsec_sta"), _T("lnsec_hi_innerpole"), i);
		while (nPoleIdx)
		{
			pPole = new CPole();
			pGisSec->m_pPoleArr.Add(pPole);

			pPole->m_szPoleNm = GETSTRING(_T("innerpole_sta"), _T("innerpole_nm"), nPoleIdx);
			pPole->m_dPoint.dx = GETVALUE(double, _T("innerpole_sta"), _T("innerpole_xcoodi"), nPoleIdx);
			pPole->m_dPoint.dy = GETVALUE(double, _T("innerpole_sta"), _T("innerpole_ycoodi"), nPoleIdx);

			nPoleIdx = GETVALUE(int, _T("innerpole_sta"), _T("innerpole_si_lnsec"), nPoleIdx);
		}

// 		ASSERT(pGisSec->m_pPoleArr.GetSize() != 1);
	}
}

void CSimulatorSLDView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	if (m_pNodeView == NULL)														return;

	CMenu*																			contextmenu = NULL;
	CMenu																			menu;

	CPoint																			ptPosition;
	CPoint																			local(point);
	ScreenToClient(&local);
	ptPosition.x = local.x - m_ptPosition.x;
	ptPosition.y = local.y - m_ptPosition.y;

	m_pFaultPosNodeView = m_pNodeView->GetSelectNodeView(ptPosition);
	if (m_pFaultPosNodeView)
	{
		menu.LoadMenu(IDR_POPUP_EDIT);
		contextmenu = menu.GetSubMenu(2);
		contextmenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, GetParentFrame());
	}
	else
	{
		BOOL bSelectBranchView(FALSE);
		if (m_pBranchView)
		{
			CBranchView* pSelBranchView;
			pSelBranchView = m_pBranchView->GetSelectBranchView(ptPosition, m_dZoomScale);
			if (pSelBranchView && pSelBranchView->GetBoundarySelect())
				bSelectBranchView = TRUE;
		}

		if (bSelectBranchView)
		{
			menu.LoadMenu(IDR_POPUP_EDIT);
			contextmenu = menu.GetSubMenu(4);
			contextmenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, GetParentFrame());
		}
		else
		{
			menu.LoadMenu(IDR_POPUP_EDIT);
			contextmenu = menu.GetSubMenu(3);
			contextmenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, GetParentFrame());
		}
	}
}

void CSimulatorSLDView::OnMenuFaultpos()
{
	if (!m_pFaultPosNodeView)
	{
		AfxMessageBox(_T("???"));
		return;
	}

	CFaultPosSetDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_fltr"), 1, (double)dlg.m_nOhms);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flt_gnd"), 1, (int)m_pFaultPosNodeView->m_nNDID[0]);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flttype"), 1, (int)dlg.m_nFaultType + 1);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_incus"), 1, (int)dlg.m_bInFault);

		CString szMsg;
		szMsg.Format(_T("11,1,"));
		TransferMessage(PROGRAM_SIMUL_HMI, 3, szMsg);
	}
}

void CSimulatorSLDView::OnMenuHide()
{
	if (m_nShowOption)
	{
		m_nShowOption = 0;
		MakeSLDBuffer(FALSE);
		Invalidate();
	}
}

void CSimulatorSLDView::PrintImage()
{
	if (m_pNodeView == NULL)
	{
		CMessageDlg dlg(_T("알림"), MB_OK);
		dlg.SetMessage(_T("출력할 계통이 없습니다"));
		dlg.DoModal();
		return;
	}

	CString						szPath;
	szPath.Format(_T("%s\\%s_SLD.png"), GetModulePath(), m_pNodeView->m_szLoc);

	COutputFileOptDlg dlg;
	dlg.m_szPath = szPath;
	dlg.m_bReverseColor = m_bReverseColor;
	if (dlg.DoModal() == IDOK)
	{
		m_bReverseColor = dlg.m_bReverseColor;
		Makepng(dlg.m_szPath, dlg.m_nRatioOpt, dlg.m_nFontRate);
		CMessageDlg dlg(_T("알림"), MB_OK);
		dlg.SetMessage(_T("저장되었습니다"));
		dlg.DoModal();
	}
}

BOOL CSimulatorSLDView::Makepng(CString szFileNm, int nRatioOpt, int nFontRate)
{
	DeleteFile(szFileNm);

	CClientDC dc(this); // device context for painting
	CDC											dcMem;
	CBitmap										bmp, *pOldBmp;
	CPoint										ptComp;
	int											nBottomMargin = 40;

	int nLeft, nTop, nRight, nBottom, nWidth, nHeight, nW, nH;

	nLeft = nTop = nRight = nBottom = 0;

	nLeft = 0;
	nTop = 0;
	nRight = GetMaxSizeX(TRUE);
	nBottom = GetMaxSizeY(TRUE);

	CRect rtComp;
	rtComp.SetRect(nLeft, nTop, nRight, nBottom + 20);

	dcMem.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rtComp.right, rtComp.bottom);
	pOldBmp = dcMem.SelectObject(&bmp);

	if (nRatioOpt > 0)
	{
		double	dRatioW, dRatioH, dRatio;

		if (nRatioOpt == 1)//A4 가로
		{
			nW = 3508;
			nH = 2480;
		}
		else				//A4 세로
		{
			nW = 2480;
			nH = 3508;
		}

		nWidth = rtComp.Width();
		nHeight = rtComp.Height();

		dRatioW = nWidth / (double)nW;
		dRatioH = nHeight / (double)nH;
		dRatio = dRatioW > dRatioH ? dRatioW : dRatioH;

		nWidth = (int)((nW * dRatio) - nWidth) / 2;
		nHeight = (int)((nH * dRatio) - nHeight) / 2;

		rtComp.InflateRect(nWidth, nHeight);
	}

	dcMem.Rectangle(rtComp);

	if( m_bReverseColor )
		dcMem.FillSolidRect(CRect(rtComp.left, rtComp.top, rtComp.right, rtComp.bottom - (nBottomMargin + 10)), RGB(255, 255, 255) );
	else
		dcMem.FillSolidRect(CRect(rtComp.left, rtComp.top, rtComp.right, rtComp.bottom - (nBottomMargin + 10)), RGB(0, 0, 0));

	dcMem.SetTextAlign(TA_LEFT);
	dcMem.SetTextColor(DEFALUT_TEXT_COLOR);
	dcMem.SetBkMode(TRANSPARENT);

	CFont																			font, *pOldFont;

	font.CreateFont(12, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("굴림체"));
	pOldFont = dcMem.SelectObject(&font);

	BOOL bFirst(TRUE);
	CBranchView* pBrenchView;
	pBrenchView = m_pBranchView;
	while (pBrenchView)
	{
		pBrenchView->Draw(&dcMem, 1, m_nShowOption, bFirst, m_bReverseColor);
		if ((((CMainFrame *)AfxGetApp()->GetMainWnd())->GetShowSecMode() == 0))
		{
			pBrenchView->DrawMeasData(&dcMem, 1);
		}

		bFirst = FALSE;
		pBrenchView = pBrenchView->m_pNext;
	}

	if (m_pNodeView)
	{
		m_pNodeView->Draw(&dcMem, 1, m_nShowOption, m_bReverseColor, nFontRate);

		if ((((CMainFrame *)AfxGetApp()->GetMainWnd())->GetShowSecMode() == 0))
		{
			if (m_nShowOption == 4)
			{
				dcMem.SelectObject(pOldFont);
				font.DeleteObject();

				font.CreateFont(11, 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("굴림체"));
				pOldFont = dcMem.SelectObject(&font);

				m_pNodeView->DrawFIFlag(&dcMem, 1);
			}
		}
	}

	dcMem.SelectObject(pOldFont);
	font.DeleteObject();

	CRect r(0, 0, rtComp.Width(), rtComp.Height());
	CImage				_image;
	CWnd*				pWndDesktop = GetDesktopWindow();
	CWindowDC			ScrDC(pWndDesktop);

	_image.Create(rtComp.Width(), rtComp.Height(), ScrDC.GetDeviceCaps(BITSPIXEL));
	CDC* _imgdc = CDC::FromHandle(_image.GetDC());
	_imgdc->Rectangle(r);
	rtComp.InflateRect(-10, -10);
	_imgdc->BitBlt(10, 10, rtComp.Width(), rtComp.Height(), &dcMem, rtComp.left, rtComp.top, SRCCOPY);

	CRect rect;
	font.CreateFont(24, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("맑은 고딕"));
	pOldFont = _imgdc->SelectObject(&font);
	_imgdc->MoveTo(r.left, r.bottom - nBottomMargin);
	_imgdc->LineTo(r.right, r.bottom - nBottomMargin);

	rect.SetRect(r.left + 20, r.bottom - 35, r.right - 20, r.bottom);
	CString szData;
	szData.Format(_T("%s/%s"), m_pNodeView->m_szLocNo, m_pNodeView->m_szLoc);
	_imgdc->DrawText(szData, rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);

	rect.SetRect(r.left + 20, r.bottom - 35, r.right - 20, r.bottom);
	_imgdc->DrawText(_T("ADMS 계통관리시스템 단선도"), rect, DT_RIGHT | DT_VCENTER | DT_WORDBREAK);
	//////////////// 211025 조성민 수정

	_imgdc->SelectObject(pOldFont);

	_image.ReleaseDC();

	_image.Save(szFileNm, Gdiplus::ImageFormatPNG);

	dcMem.SelectObject(pOldBmp);
	dcMem.DeleteDC();

	return TRUE;
}

BOOL CSimulatorSLDView::IsPCA(int nCBSWIdx)
{
	int																			nMultiswID, nNDIdx, nCbswType, nCircuitSwIdx;
	unsigned long long															lValue;
	CString																		szData;
	lValue = GETVALUE(unsigned long long, _T("cbsw_sta"), _T("cbsw_multisw_id"), nCBSWIdx);
	if (lValue > 0)
	{
		szData.Format(_T("%llu"), lValue);
		nMultiswID = _wtoi(szData.Right(8));
	}
	else
	{
		nMultiswID = 0;
	}

	if (nMultiswID == 0)														return FALSE;

	nCbswType																	= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCBSWIdx);
	if (nCbswType == 5)															return TRUE;

	nNDIdx																		= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), nCBSWIdx);
	nCircuitSwIdx																= GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
	while (nCircuitSwIdx)
	{
		nCbswType																= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCircuitSwIdx);
		if (nCbswType == 5)														return TRUE;

		nCircuitSwIdx															= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fnd"), nCircuitSwIdx);
	}

	nCircuitSwIdx																= GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);
	while (nCircuitSwIdx)
	{
		nCbswType																= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCircuitSwIdx);
		if (nCbswType == 5)														return TRUE;

		nCircuitSwIdx															= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tnd"), nCircuitSwIdx);
	}

	return FALSE;
}

BOOL CSimulatorSLDView::IsMultiSw(int nNDIdx)
{
	int																			nMultiswID, nCBSWIdx;
	unsigned long long															lValue;
	CString																		szData;

	nCBSWIdx																	= GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
	if (nCBSWIdx)
	{
		lValue = GETVALUE(unsigned long long, _T("cbsw_sta"), _T("cbsw_multisw_id"), nCBSWIdx);
		if (lValue > 0)
		{
			szData.Format(_T("%llu"), lValue);
			nMultiswID = _wtoi(szData.Right(8));
		}
		else
		{
			nMultiswID = 0;
		}

		if (nMultiswID > 0)														return TRUE;
		else																	return FALSE;
	}

	nCBSWIdx																	= GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);
	if (nCBSWIdx)
	{
		lValue = GETVALUE(unsigned long long, _T("cbsw_sta"), _T("cbsw_multisw_id"), nCBSWIdx);
		if (lValue > 0)
		{
			szData.Format(_T("%llu"), lValue);
			nMultiswID = _wtoi(szData.Right(8));
		}
		else
		{
			nMultiswID = 0;
		}

		if (nMultiswID > 0)														return TRUE;
		else																	return FALSE;
	}

	return FALSE;
}

void CSimulatorSLDView::OnMenuPrintImp()
{
	if (!m_pFaultPosNodeView)
	{
		AfxMessageBox(_T("???"));
		return;
	}

	PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_fltr"), 1, (double)0);
	PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flt_gnd"), 1, (int)m_pFaultPosNodeView->m_nNDID[0]);
	PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flttype"), 1, (int)6);
	PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_incus"), 1, (int)0);

	CString szApplPath = GetModulePath();
	CString szParam = _T("2 0 1 Simulator_hmi");  //// 
	szParam.Format(_T("2 0 11 Simulator_hmi"));

	if (!ShellExecute(NULL, _T("open"), _T("AppWRProject.exe"), szParam, szApplPath, TRUE))
	{
		CMessageDlg dlg(_T("오류"), MB_OK);
		dlg.SetMessage(_T("AppWRProject.exe : Fail"));
		dlg.DoModal();
		return;
	}
}

void CSimulatorSLDView::SetBoundaryArea(BOOL bAreaMode)
{
	if (m_pNodeView == NULL)											
		return;

	if (m_pBranchView == NULL)
		return;

	m_pBranchView->ClearBoundarySelect(bAreaMode);
	SetBoundaryAreaRcv(m_pNodeView, FALSE, bAreaMode);
}

void CSimulatorSLDView::SetBoundaryAreaRcv(CNodeView* pNodeView, BOOL bArea, BOOL bAreaMode)
{
	CBranchView* pBranchView(NULL);

	if (bArea)
	{
		pBranchView = m_pBranchView->GetBranchView2(pNodeView->m_nDbID);
		if (pBranchView)
		{
			if (pBranchView->m_nDbID > 0)
			{
				if (bAreaMode)
				{
					int nLNSECIdx;
					nLNSECIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), pBranchView->m_nDbID);
					PUTVALUE(_T("lnsec_dyn_uin"), _T("lnsec_his_notsrch"), nLNSECIdx, 1);
				}
				else
				{
					pBranchView->SetBoundarySelect(TRUE);
				}
			}
		}
	}

	if (pNodeView->m_bBoundarySelect)
	{
		if (bArea == FALSE)
		{
			//////////////////////////////////////////////////////////////////////////
			//여기서의 pNodeView는 전원측임
			//데이터처리
			//////////////////////////////////////////////////////////////////////////

			bArea = TRUE;
		}
		else
		{
			//////////////////////////////////////////////////////////////////////////
			//여기서의 pNodeView는 부하측임
			//데이터처리
			//////////////////////////////////////////////////////////////////////////

			return;
		}
	}

	if (pNodeView->m_bStatus == SW_OPEN)
		return;

	if (pNodeView->m_pCenter)											SetBoundaryAreaRcv(pNodeView->m_pCenter, bArea, bAreaMode);
	if (pNodeView->m_pLeft)												SetBoundaryAreaRcv(pNodeView->m_pLeft, bArea, bAreaMode);
	if (pNodeView->m_pRight)											SetBoundaryAreaRcv(pNodeView->m_pRight, bArea, bAreaMode);
	if (pNodeView->m_pLeftTop)											SetBoundaryAreaRcv(pNodeView->m_pLeftTop, bArea, bAreaMode);
	if (pNodeView->m_pRightBottom)										SetBoundaryAreaRcv(pNodeView->m_pRightBottom, bArea, bAreaMode);
}

void CSimulatorSLDView::ClearBoundaryCheck(BOOL bAreaMode)
{
	if (m_pNodeView)
		m_pNodeView->ClearBoundaryCheck();

	if (m_pBranchView)
		m_pBranchView->ClearBoundarySelect(bAreaMode);
}

void CSimulatorSLDView::OnMenuPrdeSet()
{
	if (m_pFaultPosNodeView)
	{
		int																				nNodeIdx(0), nCbswIdx(0), nPRDEIdx(0);
		if (m_pFaultPosNodeView->m_nTongID)
		{//멀티이고, 멀티의 다음노드가 가상더미이다. 즉, 다회로 전원측이면
			if (m_pFaultPosNodeView->m_pCenter && m_pFaultPosNodeView->m_pCenter->m_nSwKindID == -1000)		nNodeIdx = m_pFaultPosNodeView->m_nNDID[0];//FND로 확인
			else																							nNodeIdx = m_pFaultPosNodeView->m_nNDID[1];//TND로 확인
		}
		else
		{
			if (m_pFaultPosNodeView->m_nNDID[1] == 0)														nNodeIdx = m_pFaultPosNodeView->m_nNDID[0];//NODE속성이면 ND로 확인
			else																							nNodeIdx = m_pFaultPosNodeView->m_nNDID[1];//BR속성이면 TND로 확인
		}

		if (m_pFaultPosNodeView->IsSwitch())
		{
			if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNodeIdx) > 0)			nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNodeIdx);
			else																		nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNodeIdx);


			nPRDEIdx																	= GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_prde"), nCbswIdx);

			if (nPRDEIdx == 0)
			{
				AfxMessageBox(_T("prde연결정보를 찾을 수 없습니다.\ncbsw_sta의 cbsw_ii_prde를 확인하세요"));
				return;
			}
		}

		if (m_pFaultPosNodeView->m_nKCIMType == KCIMTYPE_CB)//CB
		{
			CRelaySetDlg dlg(nPRDEIdx, FALSE);
			dlg.DoModal();
		}
		else if (m_pFaultPosNodeView->m_nKCIMType == KCIMTYPE_RC)//RC
		{
			CRelcoserSetDlg dlg(nPRDEIdx);
			dlg.DoModal();
		}
		else if (m_pFaultPosNodeView->m_nTongID > 0 && m_pFaultPosNodeView->m_nKCIMType == KCIMTYPE_EFI)//MCA
		{
			CEFISetDlg dlg(nPRDEIdx, SEL_TYPE_MCA);
			dlg.DoModal();
		}
		else if (m_pFaultPosNodeView->m_nKCIMType == KCIMTYPE_EFI)//EFI
		{
			CEFISetDlg dlg(nPRDEIdx, SEL_TYPE_EFI);
			dlg.DoModal();
		}
		else if (m_pFaultPosNodeView->m_nSwKindID == NDTYPE_GEN)//발전기
		{
			int nGENIdx;
			nGENIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), nNodeIdx);

			if (nGENIdx > 0)
			{
				CDgSetDlg dlg(nGENIdx);
				dlg.DoModal();
			}
		}
		else if (m_pFaultPosNodeView->m_nSwKindID == NDTYPE_CUSTOMER)//고객
		{
			int nGNDIdx, nHVCusIdx(0);
			nGNDIdx = GETVALUE(int, _T("nd_sta"), _T("nd_ii_gnd"), nNodeIdx);
			if (nGNDIdx)
				nHVCusIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_hvcus"), nGNDIdx);

			if (nHVCusIdx > 0)
			{
				CCustSetDlg dlg(nHVCusIdx);
				dlg.DoModal();
			}
		}
		else
		{
			return;
		}
	}
}


void CSimulatorSLDView::OnUpdateMenuPrdeSet(CCmdUI *pCmdUI)
{
	BOOL																bEnabled;
	bEnabled															= SetMenuEnabledCheck(m_pFaultPosNodeView);
	pCmdUI->Enable(bEnabled);
}

BOOL CSimulatorSLDView::SetMenuEnabledCheck(CNodeView* pSelNodeView)
{
	if (pSelNodeView == NULL)
		return FALSE;

	
	if (pSelNodeView->m_nKCIMType == KCIMTYPE_CB)//CB
	{
		return TRUE;
	}
	else if (pSelNodeView->m_nKCIMType == KCIMTYPE_RC)//RC
	{
		return TRUE;
	}
	else if (pSelNodeView->m_nTongID > 0 && pSelNodeView->m_nKCIMType == KCIMTYPE_EFI)//MCA
	{
		return TRUE;
	}
	else if (pSelNodeView->m_nKCIMType == KCIMTYPE_EFI)//EFI
	{
		return TRUE;
	}
	else if (pSelNodeView->m_nSwKindID == NDTYPE_GEN)//발전기
	{
		return TRUE;
	}
	else if (pSelNodeView->m_nSwKindID == NDTYPE_CUSTOMER)//고객
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CSimulatorSLDView::OnVvmSet()
{
	CVVMSetDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_pBranchView->SetChangeVoltLevel(dlg.m_nVoltageLevel == 0 ? 1 : 2);
		ClearBoundaryCheck(FALSE);
		MakeSLDBuffer(FALSE);
	}
}

int CSimulatorSLDView::GetSelectLoofCB(CPoint point)
{
	int																nLoofCBSize;
	nLoofCBSize														= m_nLoofCBIdArr.GetSize();
	if (nLoofCBSize == 0)											return -1;

	CRect															_rect;
	GetClientRect(&_rect);

	int																nHeight(30);
	CRect															rArea;
	rArea.left = 15;
	rArea.bottom = (_rect.bottom - 15);
	rArea.right = (rArea.left + 230);
	rArea.top = (rArea.bottom - (nHeight * nLoofCBSize));

	rArea.left += 10;
	rArea.right -= 10;
	rArea.bottom = rArea.top + nHeight;
	for (int i = 0; i < nLoofCBSize; i++)
	{
		if (rArea.PtInRect(point))
			return i;

		rArea.top += nHeight;
		rArea.bottom = rArea.top + nHeight;
	}

	return -1;
}
