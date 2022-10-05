#include "pch.h"
#include "CView_LF_rst.h"
#include "resource.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"
#include "../DataManager/CDataManager.h"


/////////////////////////////////////////////////

CView_LF_rst::CView_LF_rst()
{
	m_nViewState = -1;
	m_nViewID = -1;

	m_dMax_kW = -1;
	m_dMax_V = 0.;
	m_dMin_V = 99999.;

	m_dSum_Load = 0.;
	m_dSum_Gen = 0.;

	m_headerfont.DeleteObject();
	m_listfont.DeleteObject();

	//m_ptSelect.x = -1;
	//m_ptSelect.y = -1;

	m_bGraph_Check[0] = TRUE;
	m_bGraph_Check[1] = TRUE;

	m_dMax_Load = 0.;
	m_dMax_Gen = 0.;
	m_dSum_Gen = 0.;
	m_dSum_Load = 0.;
}

CView_LF_rst::~CView_LF_rst()
{
	Graph_Data_Clear();
	Group_Data_Clear();
}


BEGIN_MESSAGE_MAP(CView_LF_rst, CView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_CBN_SELCHANGE(ID_APP_RPF_COMBO_1, &CView_LF_rst::OnLF_rstCombo1SelectChange)
	ON_CBN_SELCHANGE(ID_APP_RPF_COMBO_2, &CView_LF_rst::OnLF_rstCombo2SelectChange)
	ON_CBN_SELCHANGE(ID_APP_RPF_COMBO_3, &CView_LF_rst::OnLF_rstCombo3SelectChange)
	ON_NOTIFY(NM_DBLCLK, ID_APP_RPF_LIST_1, &CView_LF_rst::OnListCtrlDBClick_1)
	ON_NOTIFY(NM_DBLCLK, ID_APP_RPF_LIST_2, &CView_LF_rst::OnListCtrlDBClick_2)
	ON_NOTIFY(NM_DBLCLK, ID_APP_RPF_LIST_3, &CView_LF_rst::OnListCtrlDBClick_3)
	ON_NOTIFY(NM_DBLCLK, ID_APP_RPF_LIST_4, &CView_LF_rst::OnListCtrlDBClick_4)
	ON_BN_CLICKED(ID_APP_RPF_BTN_1, &CView_LF_rst::OnControlbutton_click_Run)
	ON_BN_CLICKED(ID_APP_RPF_BTN_2, &CView_LF_rst::OnControlbutton_click_Report)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_SETTINGCHANGE()
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


//void CView_LF_rst::SetVIewState(int nStete )
//{ 
//	if (nStete = VIEW_STATE_HIDE)
//	{
//		ShowWindow(SW_HIDE);
//	}
//	else
//	{
//		ShowWindow(SW_SHOW);
//	}
//
//	m_nViewState = nStete;
//}


void CView_LF_rst::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	Create_Combobox();
	Create_DateTimeCtrl();
	Create_ListCtrl();
	Create_Btn();

	
}

void CView_LF_rst::InitData()
{
	m_ctrCombo[0].ResetContent();
	m_ctrCombo[2].ResetContent();

	SetComboxData_Subs();

	m_dVVM_lmhi = 1.02;
	m_dVVM_lmlo = 0.96;

	CTime t = CTime::GetCurrentTime();


	CString strData;
//	m_ctrCombo[2].AddString(_T("시"));
	for (int i = 0; i < 24; i++)
	{
		strData.Format(_T("%d"), i);
		m_ctrCombo[2].AddString(strData);
	}

	
	m_ctrCombo[2].SetCurSel(0);

	//SetTimer(1111, 100, NULL);

}


void CView_LF_rst::OnDraw(CDC* pDC)
{
	
//	CClientDC dc(this);

	OnPrepareDC(pDC);
	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	//CView_Manager* pViewMng = CView_Manager::Instance();

	//pViewMng->DrawArea_Base(&dc, graphics, m_rectCtrl[0]);
	//pViewMng->DrawArea_Base(&dc, graphics, m_rectCtrl[1]);

	//pViewMng->Draw_Split(&dc, graphics, m_rectCtrl_TopLeft[0], DRAW_SPLIT_MODE_BOTTOM);
	//pViewMng->Draw_Split(&dc, graphics, m_rectCtrl_TopLeft[1], DRAW_SPLIT_MODE_BOTTOM);
	//pViewMng->Draw_Split(&dc, graphics, m_rectCtrl_TopRight[0], DRAW_SPLIT_MODE_BOTTOM);


	////////////////////////////////////////////////////////////////////////
	//pViewMng->DrawArea_List(&dc, graphics, m_rectCtrl[2]);
	//pViewMng->DrawArea_List(&dc, graphics, m_rectCtrl[3]);
	//
	//pViewMng->DrawArea_Title(&dc, graphics, m_rectListTitle[0], _T("개폐기별 전압&전력"));
	//pViewMng->DrawArea_Title(&dc, graphics, m_rectListTitle[1], _T("구간별 부하&발전"));

	//pViewMng->DrawArea_Unit(&dc, graphics, m_rectListUnit[0], _T("단위:kV,kW"));
	//pViewMng->DrawArea_Unit(&dc, graphics, m_rectListUnit[1], _T("단위:kW"));

	Draw_TopLeft_Setting(pDC, graphics);

	
	Draw_TopLeft_Graph(pDC, graphics);
	Draw_TopLeft_Title(pDC, graphics);

	//Draw_TopRight_Title(&dc, graphics);
	//Draw_TopRight_circle(&dc, graphics);


	
	Redraw_Ctrl();
}

void CView_LF_rst::Redraw_Ctrl()
{
	//RedrawWindow();

//	m_ctrCombo[0].SetFocus();
	m_ctrCombo[0].RedrawWindow();
//	m_ctrCombo[1].SetFocus();
	m_ctrCombo[1].RedrawWindow();
//	m_ctrCombo[2].SetFocus();
	m_ctrCombo[2].RedrawWindow();
}


void CView_LF_rst::Create_Combobox()
{
	m_font_Combobox.CreateFont(17 , 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	if (!m_ctrCombo[0].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL /*| CBS_SORT*/
		, CRect(100, 100,200 , 200), this, ID_APP_RPF_COMBO_1))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}
	if (!m_ctrCombo[1].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_SORT
		, CRect(100, 100, 200, 200), this, ID_APP_RPF_COMBO_2))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[2].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_RPF_COMBO_3))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}
/*
	if(!m_ctrCombo[3].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_RPF_COMBO_4))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}

	if(!m_ctrCombo[4].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_RPF_COMBO_5))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[5].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_RPF_COMBO_6))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}
	*/
	m_ctrCombo[0].SetTextFont(&m_font_Combobox);
	m_ctrCombo[1].SetTextFont(&m_font_Combobox);
	m_ctrCombo[2].SetTextFont(&m_font_Combobox);
	/*m_ctrCombo[3].SetTextFont(&m_font_Combobox);
	m_ctrCombo[4].SetTextFont(&m_font_Combobox);
	m_ctrCombo[5].SetTextFont(&m_font_Combobox);*/

	m_ctrCombo[0].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[1].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[2].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	/*m_ctrCombo[3].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[4].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[5].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));*/

	m_ctrCombo[0].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[1].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[2].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	//m_ctrCombo[3].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	//m_ctrCombo[4].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	//m_ctrCombo[5].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);

	m_ctrCombo[0].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[1].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[2].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	/*m_ctrCombo[3].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[4].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[5].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
*/
	m_ctrCombo[0].SetDropDownHeight(10);
	m_ctrCombo[1].SetDropDownHeight(10);
	m_ctrCombo[2].SetDropDownHeight(10);
	
	/*m_ctrCombo[3].SetDropDownHeight(10);
	m_ctrCombo[4].SetDropDownHeight(10);
	m_ctrCombo[5].SetDropDownHeight(10);*/

}

void CView_LF_rst::Create_Btn()
{
	m_btn_ctrl_rect[0] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[0].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[0], this, ID_APP_RPF_BTN_1))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[0].SetBitmapID(IDB_PDVR_RUN_NOR, IDB_PDVR_RUN_CLK, IDB_PDVR_RUN_OVR);

	if (!m_btn_ctrl[1].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[0], this, ID_APP_RPF_BTN_2))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[1].SetBitmapID(IDB_PCE_RPT_NOR, IDB_PCE_RPT_CLK, IDB_PCE_RPT_OVR);

	/////////////////////////////////////////////////////////////
}

void CView_LF_rst::SetComboxData_Subs()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CStringArray Array_SS;

	pDataMng->GetSSName_array(&Array_SS);

	for (int i = 0; i < Array_SS.GetSize(); i++)
	{
		m_ctrCombo[0].AddString(Array_SS.GetAt(i));
	}

	m_ctrCombo[1].ResetContent();
	//m_ctrCombo[2].AddString(_T("A"));
	//m_ctrCombo[2].AddString(_T("B"));
	//m_ctrCombo[2].AddString(_T("C"));

	
}

void CView_LF_rst::OnLF_rstCombo1SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	CString	strSS;
	CStringArray Array_DL;
	CIntArray	Array_DL_Idx;

	m_strComboValue[0] = m_strComboValue[1] = m_strComboValue[2] = _T("");

	m_ctrCombo[0].GetLBText(nSel, strSS);

	m_strComboValue[0] = strSS;

	m_ctrCombo[1].ResetContent();

	//////////  CBS_SORT

	CDataManager* pDataMng = CDataManager::Instance();

	pDataMng->GetDLName_array(strSS , &Array_DL, _T(""),&Array_DL_Idx);

	for (int i = 0; i < Array_DL.GetSize(); i++)
	{
		m_ctrCombo[1].AddString(Array_DL.GetAt(i));
		
		TRACE(_T("%s\t%d\n"), Array_DL.GetAt(i), Array_DL_Idx.GetAt(i));
	}
	TRACE(_T("--------------------------n"));
	CString strName;
	int nIdx;
	for (int i = 0; i < m_ctrCombo[1].GetCount(); i++)
	{
		m_ctrCombo[1].GetLBText(i, strName);

		for (int k = 0; k < Array_DL.GetSize(); k++)
		{
			if (Array_DL.GetAt(k) == strName)
			{
				m_ctrCombo[1].SetItemData(i, (DWORD_PTR)Array_DL_Idx.GetAt(k));
				break;
			}
		}
	}

	for (int i = 0; i < m_ctrCombo[1].GetCount(); i++)
	{
		m_ctrCombo[1].GetLBText(i, strName);
		nIdx = m_ctrCombo[1].GetItemData(i);
		TRACE(_T("%s\t%d\n"), strName, nIdx);
	}
	//m_ctrCombo[2].SetCurSel(0);
}

void CView_LF_rst::OnLF_rstCombo2SelectChange()
{
	/*int nSel = m_ctrCombo[1].GetCurSel();

	if (nSel == -1)
		return;

	CString strDL;

	m_ctrCombo[1].GetLBText(nSel, strDL);

	m_strComboValue[1] = strDL;

	m_ctrCombo[2].SetCurSel(0);*/

	//CString strName;
	//int nNDIdx, nGNDIdx, nRealCount;
	//Graph_Data_Clear();
	//m_nNode_MaxCount = 0;

	//nRealCount = theAppDataMng->GetTableRealCount(_T("dl_sta"));
	//for (int i = 1; i < (int)nRealCount ; i++)
	//{
	//	strName = GETSTRING(_T("dl_sta"), _T("dl_nm"), i);
	//	if (strName.Compare(strDL) != 0)
	//		continue;

	//	nNDIdx = GETVALUE(int, _T("dl_sta"), _T("dl_hi_nd"), i);
	//	nGNDIdx = GETVALUE(int, _T("nd_sta"), _T("nd_ii_gnd"), nNDIdx);

	////	FindGroupCB(-1, nGNDIdx);

	//	break;
	//}

	/*Get_TitleData_RPF();
	Get_GraphData_RPF();
	Get_ChartData_RPF();*/

	//m_dSum_Gen = m_dSum_Load = 0.;
	//Get_TitleData_DLE();

	//RedrawWindow();

}

void CView_LF_rst::OnLF_rstCombo3SelectChange()
{
/*
	int nSel = m_ctrCombo[2].GetCurSel();

	if (nSel == -1)
		return;

	CString strPhase;

	m_ctrCombo[2].GetLBText(nSel, strPhase);

	m_strComboValue[2] = strPhase;

	Get_GraphData_RPF();
	Get_ChartData_RPF();

	RedrawWindow();*/
}

void CView_LF_rst::Create_ListCtrl()
{
	m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect[4];
	rect[0] = CRect(10, 50, 350, 500);
	m_ctrList[0].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_RPF_LIST_1);
	m_ctrList[0].InsertColumn(0, _T("발전기명"), HDF_LEFT, 148);
	m_ctrList[0].InsertColumn(1, _T("정격 용량"), HDF_LEFT, 148);
	m_ctrList[0].InsertColumn(2, _T("발전 출력"), HDF_LEFT, 148);
	m_ctrList[0].InsertColumn(3, _T("idx"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(4, _T("dump"), HDF_LEFT, 0);
	m_ctrList[0].ShowWindow(SW_SHOW);
	m_ctrList[0].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[0].m_HeaderCtrl.SetHeight(27);
	m_ctrList[0].m_HeaderCtrl.SetFlat();
	m_ctrList[0].m_HeaderCtrl.SetFlat();
	m_ctrList[0].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[0].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[0].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[0].SetBgColor(RGB(255, 255, 255));
	m_ctrList[0].SetUnderLine();
	m_ctrList[0].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[0].SetTextFont(&m_listfont);
	m_ctrList[0].SetRowHeight(25);


	rect[1] = CRect(10, 50, 350, 500);
	m_ctrList[1].Create(WS_CHILD |  LVS_REPORT | LVS_NOSORTHEADER, rect[1], this, ID_APP_RPF_LIST_2);
	m_ctrList[1].InsertColumn(0, _T("전원 측 개폐기"), HDF_LEFT, 190);
	m_ctrList[1].InsertColumn(1, _T("총 부하(A)"), HDF_LEFT, 130);
	m_ctrList[1].InsertColumn(2, _T("총 발전량(B)"), HDF_LEFT, 130);
	m_ctrList[1].InsertColumn(3, _T("순 부하(A-B)"), HDF_LEFT, 130);
	m_ctrList[1].InsertColumn(4, _T("idx"), HDF_LEFT, 0);
	m_ctrList[1].InsertColumn(5, _T("dump"), HDF_LEFT, 0);
	m_ctrList[1].ShowWindow(SW_SHOW);
	m_ctrList[1].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[1].m_HeaderCtrl.SetHeight(27);
	m_ctrList[1].m_HeaderCtrl.SetFlat();
	m_ctrList[1].m_HeaderCtrl.SetFlat();
	m_ctrList[1].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[1].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[1].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[1].SetBgColor(RGB(255, 255, 255));
	m_ctrList[1].SetUnderLine();
	m_ctrList[1].SetColorUnderLine(RGB(215, 214, 214));
	m_ctrList[1].SetTextFont(&m_listfont);
	m_ctrList[1].SetRowHeight(25);
	

	rect[2] = CRect(10, 50, 350, 500);
	m_ctrList[2].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, rect[2], this, ID_APP_RPF_LIST_3);
	m_ctrList[2].InsertColumn(0, _T("변전소"), HDF_LEFT, 158);
	m_ctrList[2].InsertColumn(1, _T("선로명"), HDF_LEFT, 158);
	m_ctrList[2].InsertColumn(2, _T("연계 개폐기"), HDF_LEFT, 158);
	m_ctrList[2].InsertColumn(3, _T("구간 부하"), HDF_LEFT, 158);
	m_ctrList[2].InsertColumn(4, _T("발전기 정격 용량"), HDF_LEFT, 158);
	m_ctrList[2].InsertColumn(5, _T("발전량"), HDF_LEFT, 158);
	m_ctrList[2].InsertColumn(6, _T("순 부하"), HDF_LEFT, 158);
	m_ctrList[2].InsertColumn(7, _T("순 부하 전류"), HDF_LEFT, 158);
	m_ctrList[2].InsertColumn(8, _T("idx"), HDF_LEFT, 0);
	m_ctrList[2].InsertColumn(9, _T("dump"), HDF_LEFT, 0);
	m_ctrList[2].ShowWindow(SW_SHOW);
	m_ctrList[2].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[2].m_HeaderCtrl.SetHeight(27);
	m_ctrList[2].m_HeaderCtrl.SetFlat();
	m_ctrList[2].m_HeaderCtrl.SetFlat();
	m_ctrList[2].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[2].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[2].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[2].SetBgColor(RGB(255, 255, 255));
	m_ctrList[2].SetUnderLine();
	m_ctrList[2].SetColorUnderLine(RGB(215, 214, 214));
	m_ctrList[2].SetTextFont(&m_listfont);
	m_ctrList[2].SetRowHeight(25);

	rect[3] = CRect(10, 50, 350, 500);
	m_ctrList[3].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, rect[3], this, ID_APP_RPF_LIST_4);
	m_ctrList[3].InsertColumn(0, _T("노드 명"), HDF_LEFT, 215);
	m_ctrList[3].InsertColumn(1, _T("전압(kV)"), HDF_LEFT, 90);
	m_ctrList[3].InsertColumn(2, _T("km"), HDF_LEFT, 0);
	m_ctrList[3].InsertColumn(3, _T("idx"), HDF_LEFT, 0);
	m_ctrList[3].InsertColumn(4, _T("dump"), HDF_LEFT, 0);
	m_ctrList[3].ShowWindow(SW_SHOW);
	m_ctrList[3].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[3].m_HeaderCtrl.SetHeight(27);
	m_ctrList[3].m_HeaderCtrl.SetFlat();
	m_ctrList[3].m_HeaderCtrl.SetFlat();
	m_ctrList[3].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[3].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[3].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[3].SetBgColor(RGB(255, 255, 255));
	m_ctrList[3].SetUnderLine();
	m_ctrList[3].SetColorUnderLine(RGB(215, 214, 214));
	m_ctrList[3].SetTextFont(&m_listfont);
	m_ctrList[3].SetRowHeight(25);

}	

void CView_LF_rst::Create_DateTimeCtrl()
{
	if (!m_ctrDate[0].Create(WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 
		CRect(100, 100, 200, 200), this, ID_APP_RPF_DATE_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

}


void CView_LF_rst::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);


	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	m_rectCtrl[0].SetRect(_rect.left, _rect.top, _rect.Width(), _rect.top + 92);
	m_rectCtrl[1].SetRect(_rect.left, m_rectCtrl[0].bottom + 10, (_rect.Width() * 0.75  - 5)
							,m_rectCtrl[0].bottom + 10 + ((_rect.Height() - 102)/2 - 5));
	m_rectCtrl[2].SetRect(m_rectCtrl[1].right + 10, m_rectCtrl[1].top, _rect.right, m_rectCtrl[1].bottom);
	m_rectCtrl[3].SetRect(_rect.left, m_rectCtrl[1].bottom + 10, (_rect.Width() * 0.32 - 5), _rect.bottom);
	m_rectCtrl[4].SetRect(m_rectCtrl[3].right + 10, m_rectCtrl[3].top, _rect.right, _rect.bottom);

	Setting_MoveSize();
	TopLeft_MoveSize();
	TopRight_MoveSize();
	ListCtrl_MoveSize();
	MoveSize_Btn();
}

void CView_LF_rst::MoveSize_Btn()
{
	if (m_btn_ctrl[0].GetSafeHwnd() == NULL)							return;

	CRect rect = m_rectCtrl[0];

	rect.left = rect.right - 94;
	rect.right = rect.left + 87;
	rect.bottom = rect.top + 45;
	rect.InflateRect(0, -6);

	m_btn_ctrl_rect[1] = rect;
	m_btn_ctrl[1].MoveWindow(m_btn_ctrl_rect[1]);

	m_btn_ctrl_rect[0] = rect;
	m_btn_ctrl_rect[0].right = m_btn_ctrl_rect[1].left - 8;
	m_btn_ctrl_rect[0].left = m_btn_ctrl_rect[0].right - 87;

	m_btn_ctrl[0].MoveWindow(m_btn_ctrl_rect[0]);
}

void CView_LF_rst::Setting_MoveSize()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL)							return;

	m_rectCtrl_Setting[0] = m_rectCtrl[0];
	m_rectCtrl_Setting[0].bottom = m_rectCtrl_Setting[0].top + 46;

	m_rectCtrl_Setting[1] = m_rectCtrl[0];
	m_rectCtrl_Setting[1].top = m_rectCtrl_Setting[0].bottom ;
	m_rectCtrl_Setting[1].bottom = m_rectCtrl_Setting[1].top + 46;


	/////////////////// 콤보랑 에디트 박스 추가

	m_rectCtrl_Combobox[0] = m_rectCtrl_Setting[0];
	m_rectCtrl_Combobox[0].InflateRect(-10, -10);
	m_rectCtrl_Combobox[0].left = m_rectCtrl_Combobox[0].left + 80;
	m_rectCtrl_Combobox[0].right = m_rectCtrl_Combobox[0].left + 165;
	m_rectCtrl_Combobox[0].bottom = m_rectCtrl_Combobox[0].top + 24;
	m_ctrCombo[0].MoveWindow(m_rectCtrl_Combobox[0]);

	m_rectCtrl_Combobox[1] = m_rectCtrl_Combobox[0];
	m_rectCtrl_Combobox[1].left = m_rectCtrl_Combobox[0].right + 10;
	m_rectCtrl_Combobox[1].right = m_rectCtrl_Combobox[1].left + 165;
	m_ctrCombo[1].MoveWindow(m_rectCtrl_Combobox[1]);

	m_rectCtrl_Date[0] = m_rectCtrl_Combobox[0];
	m_rectCtrl_Date[0].top += 1;
	m_rectCtrl_Date[0].bottom += 1;
	m_rectCtrl_Date[0].left = m_rectCtrl_Combobox[1].right + 92;
	m_rectCtrl_Date[0].right = m_rectCtrl_Date[0].left + 115;
	m_ctrDate[0].MoveWindow(m_rectCtrl_Date[0]);

	m_rectCtrl_Combobox[2] = m_rectCtrl_Combobox[1];
	m_rectCtrl_Combobox[2].left = m_rectCtrl_Date[0].right + 10;
	m_rectCtrl_Combobox[2].right = m_rectCtrl_Combobox[2].left + 51;
	m_ctrCombo[2].MoveWindow(m_rectCtrl_Combobox[2]);

	//////////////////////////////// 선로 정보 요약

	m_rectSetting_Data[0] = m_rectCtrl_Setting[1];
	m_rectSetting_Data[0].InflateRect(-10, -10);
	m_rectSetting_Data[0].left = m_rectSetting_Data[0].left + 219;
	m_rectSetting_Data[0].right = m_rectSetting_Data[0].left + 115;

	m_rectSetting_Data[1] = m_rectSetting_Data[0];
	m_rectSetting_Data[1].left = m_rectSetting_Data[0].right + 131;
	m_rectSetting_Data[1].right = m_rectSetting_Data[1].left + 115;

	m_rectSetting_Data[2] = m_rectSetting_Data[0];
	m_rectSetting_Data[2].left = m_rectSetting_Data[1].right + 131;
	m_rectSetting_Data[2].right = m_rectSetting_Data[2].left + 115;

	m_rectSetting_Data[3] = m_rectSetting_Data[0];
	m_rectSetting_Data[3].left = m_rectSetting_Data[2].right + 131;
	m_rectSetting_Data[3].right = m_rectSetting_Data[3].left + 115;

	m_rectSetting_Data[4] = m_rectSetting_Data[0];
	m_rectSetting_Data[4].left = m_rectSetting_Data[3].right + 131;
	m_rectSetting_Data[4].right = m_rectSetting_Data[4].left + 115;

}

void CView_LF_rst::TopLeft_MoveSize()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL)							return;

	m_rectCtrl_TopLeft[0] = m_rectCtrl[1];
	m_rectCtrl_TopLeft[0].right = m_rectCtrl_TopLeft[0].Width() * 0.77;

	m_rectCtrl_TopLeft[1] = m_rectCtrl[1];
	m_rectCtrl_TopLeft[1].left = m_rectCtrl_TopLeft[0].right;

	m_rectListTitle[3] = m_rectCtrl_TopLeft[0];
	m_rectListTitle[3].right = m_rectCtrl_TopLeft[0].left + 100;
	m_rectListTitle[3].bottom = m_rectCtrl_TopLeft[0].top + 30;

	m_rectListTitle[4] = m_rectCtrl_TopLeft[1];
	m_rectListTitle[4].right = m_rectCtrl_TopLeft[1].left + 100;
	m_rectListTitle[4].bottom = m_rectCtrl_TopLeft[1].top + 30;

	CRect rectList;

	rectList = m_rectCtrl_TopLeft[1];
	rectList.top += 29;
	rectList.bottom = m_rectCtrl_TopLeft[1].bottom - 1;
	m_ctrList[3].MoveWindow(rectList);
}

void CView_LF_rst::TopRight_MoveSize()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL)							return;

	m_rectCtrl_TopRight[0] = m_rectCtrl[2];
	m_rectCtrl_TopRight[0].bottom = m_rectCtrl_TopRight[0].top + 40;


	/*m_rectCtrl_TopRight[1] = m_rectCtrl[1];
	m_rectCtrl_TopRight[1].top = m_rectCtrl_TopRight[0].bottom;*/


	/////////////////// 원형 그래프 추가
}

void CView_LF_rst::ListCtrl_MoveSize()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL )							return;

	/////////////////////////////////////////////////////////////////////////// 하단 리스트 
	/////////////////////////////////////////////타이틀  
	m_rectListTitle[0] = m_rectCtrl[2];
	m_rectListTitle[0].right = m_rectListTitle[0].left + 163;
	m_rectListTitle[0].bottom = m_rectListTitle[0].top + 29;

	m_rectListTitle[1] = m_rectCtrl[3];
	m_rectListTitle[1].right = m_rectListTitle[1].left + 150;
	m_rectListTitle[1].bottom = m_rectListTitle[1].top + 29;

	m_rectListTitle[2] = m_rectCtrl[4];
	m_rectListTitle[2].right = m_rectListTitle[2].left + 150;
	m_rectListTitle[2].bottom = m_rectListTitle[2].top + 29;
	/////////////////////////////////////////////타이틀  
	/////////////////////////////////////////////단위
	m_rectListUnit[0] = m_rectCtrl[2];
	m_rectListUnit[0].right = m_rectListUnit[0].right - 4;
	m_rectListUnit[0].left = m_rectListUnit[0].right - 86;
	m_rectListUnit[0].top = m_rectListUnit[0].top + 4;
	m_rectListUnit[0].bottom = m_rectListUnit[0].top + 21;

	m_rectListUnit[1] = m_rectCtrl[3];
	m_rectListUnit[1].right = m_rectListUnit[1].right - 4;
	m_rectListUnit[1].left = m_rectListUnit[1].right - 86;
	m_rectListUnit[1].top = m_rectListUnit[1].top + 4;
	m_rectListUnit[1].bottom = m_rectListUnit[1].top + 21;

	m_rectListUnit[2] = m_rectCtrl[4];
	m_rectListUnit[2].right = m_rectListUnit[2].right - 4;
	m_rectListUnit[2].left = m_rectListUnit[2].right - 86;
	m_rectListUnit[2].top = m_rectListUnit[2].top + 4;
	m_rectListUnit[2].bottom = m_rectListUnit[2].top + 21;

	/////////////////////////////////////////////단위  

	/////////////////////////////////////////////리스트  
	CRect rectList[3];

	rectList[0] = m_rectCtrl[2];
	rectList[0].left  -= 1;
	rectList[0].right += 1;
	rectList[0].top += 29;
	rectList[0].bottom = m_rectCtrl[2].bottom - 1;
	m_ctrList[0].MoveWindow(rectList[0]);

	rectList[1] = m_rectCtrl[3];
	rectList[1].left  -= 1;
	rectList[1].right += 1;
	rectList[1].top += 29;
	rectList[1].bottom = m_rectCtrl[3].bottom - 1;
	m_ctrList[1].MoveWindow(rectList[1]);

	rectList[2] = m_rectCtrl[4];
	rectList[2].left -= 1;
	rectList[2].right += 1;
	rectList[2].top += 29;
	rectList[2].bottom = m_rectCtrl[4].bottom - 1;
	m_ctrList[2].MoveWindow(rectList[2]);
	/////////////////////////////////////////////리스트 
	
}

BOOL CView_LF_rst::OnEraseBkgnd(CDC* pDC)
{
//	

	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	CView_Base::OnEraseBkgnd(pDC);

	pViewMng->DrawArea_Base(pDC, graphics, m_rectCtrl[0]);
	//pViewMng->DrawArea_Base(pDC, graphics, m_rectCtrl[1]);

	pViewMng->Draw_Split(pDC, graphics, m_rectCtrl_Setting[0], DRAW_SPLIT_MODE_BOTTOM);
//	pViewMng->Draw_Split(pDC, graphics, m_rectCtrl_TopLeft[1], DRAW_SPLIT_MODE_BOTTOM);
//	pViewMng->Draw_Split(pDC, graphics, m_rectCtrl_TopRight[0], DRAW_SPLIT_MODE_BOTTOM);


	//////////////////////////////////////////////////////////////////////
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl[2]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl[3]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl[4]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_TopLeft[0]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_TopLeft[1]);

	pViewMng->DrawArea_Title(pDC, graphics, m_rectListTitle[0], _T("발전기 별 발전량"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectListTitle[1], _T("구간별 부하&발전"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectListTitle[2], _T("연계선로 정보"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectListTitle[3], _T("전압 프로파일"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectListTitle[4], _T("노드 별 전압"));

	pViewMng->DrawArea_Unit(pDC, graphics, m_rectListUnit[0], _T("단위:kW"));
	pViewMng->DrawArea_Unit(pDC, graphics, m_rectListUnit[1], _T("단위:kV"));
	pViewMng->DrawArea_Unit(pDC, graphics, m_rectListUnit[2], _T("단위:kW"));

	
	CRect r = m_rectCtrl_TopLeft[0];
	r.top += m_rectListTitle[3].Height();
	pViewMng->DrawArea_Base(pDC, graphics, r);

	
	return TRUE;
}

void CView_LF_rst::Draw_TopLeft_Setting(CDC* pDC, Graphics &graphics)
{

	CRect rTag[3];

	rTag[0] = m_rectCtrl_Combobox[0];
	rTag[0].left = m_rectCtrl_Combobox[0].left - 80;
	rTag[0].right = rTag[0].left + 80;

	rTag[1] = m_rectCtrl_Date[0];
	rTag[1].left = m_rectCtrl_Date[0].left - 60;
	rTag[1].right = rTag[1].left + 60;

	rTag[2] = m_rectCtrl_Combobox[2];
	rTag[2].left = m_rectCtrl_Combobox[2].right ;
	rTag[2].right = rTag[2].left + 15;

	/*rTag[2] = m_rectCtrl_Radio[2];
	rTag[2].left = m_rectCtrl_Radio[2].left - 62;
	rTag[2].right = rTag[2].left + 62;*/


	CView_Manager* pViewMng = CView_Manager::Instance();

	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[0], 0, _T("변전소/선로"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[1], 0, _T("분석시점"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[2], 0, _T("시"));
	//pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[2], 0, _T("부하유형"));*/


	SolidBrush						_drawRectbrush(Color(255, 153, 153, 153));
	Gdiplus::Pen					_drawRectpen(&_drawRectbrush, 1.);

//	CView_Manager* pViewMng = CView_Manager::Instance();
	CRect rectdate = m_rectCtrl_Date[0];
	rectdate.left -= 1;
	rectdate.top -= 1;
	Gdiplus::GraphicsPath gdiPath;
	pViewMng->GetRoundRectPath(&gdiPath, rectdate.left, rectdate.top, rectdate.Width(), rectdate.Height(), 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);
}


void CView_LF_rst::Draw_TopLeft_Title(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectCtrl_Setting[1];

	rect.InflateRect(-10, -10);

	CRect  _r[6];

	_r[0] = rect;
	_r[0].left = 0;
	_r[0].right = rect.left + 90;

	_r[1] = m_rectSetting_Data[0];
	_r[1].left = m_rectSetting_Data[0].left - 60;
	_r[1].right = _r[1].left + 60;

	_r[2] = m_rectSetting_Data[1];
	_r[2].left = m_rectSetting_Data[1].left - 80;
	_r[2].right = _r[2].left + 80;
	
	_r[3] = m_rectSetting_Data[2];
	_r[3].left = m_rectSetting_Data[2].left - 90;
	_r[3].right = _r[3].left + 90;
	
	_r[4] = m_rectSetting_Data[3];
	_r[4].left = m_rectSetting_Data[3].left - 80;
	_r[4].right = _r[4].left + 80;

	_r[5] = m_rectSetting_Data[4];
	_r[5].left = m_rectSetting_Data[4].left - 70;
	_r[5].right = _r[5].left + 70;
	

	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));


	/*graphics.DrawString(_T("운전용량"), -1, &_drawfont, _r[0], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("최고전압"), -1, &_drawfont, _r[1], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("최저전압"), -1, &_drawfont, _r[2], &_drawStrFormat, &_drawFontbrush);*/

	CView_Manager* pViewMng = CView_Manager::Instance();

	pViewMng->Draw_Setting_Tag(pDC, graphics, _r[0], 0, _T("선로 정보 요약"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, _r[1], 0, _T("총 부하"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, _r[2], 0, _T("발전기 용량"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, _r[3], 0, _T("발전기 발전량"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, _r[4], 0, _T("순 부하(MW)"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, _r[5], 0, _T("순 부하(A)"));
	

	SolidBrush						_drawRectbrush(Color(255, 153, 153, 153));
	Gdiplus::Pen					_drawRectpen(&_drawRectbrush, 1.);

	//	CView_Manager* pViewMng = CView_Manager::Instance();

	CString strData[5];
	strData[0].Format(_T("%.1lf"), m_dMax_Load);
	strData[1].Format(_T("%.1lf"), m_dSum_Gen);
	strData[2].Format(_T("%.1lf"), m_dMax_Gen);
	strData[3].Format(_T("%.1lf"), m_dMax_Load - m_dMax_Gen);
	strData[4].Format(_T("%.1lf"), m_dSum_Load);

	CRect _rect;
	
	Gdiplus::GraphicsPath gdiPath;

	for (int i = 0; i < 5; i++)
	{
		_rect = m_rectSetting_Data[i];
		gdiPath.Reset();
		pViewMng->GetRoundRectPath(&gdiPath, _rect.left, _rect.top, _rect.Width(), _rect.Height(), 6);
		graphics.DrawPath(&_drawRectpen, &gdiPath);
		
		if(m_dMax_Load > 0.)
			pViewMng->Draw_Setting_Tag(pDC, graphics, _rect, 1, strData[i]);
	}

	

	

	//Draw_TopLeft_Infor(pDC, graphics);
}

void CView_LF_rst::Draw_TopLeft_Infor(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectCtrl_TopLeft[1];
	rect.InflateRect(-8, -10);

	Gdiplus::RectF  _r[3];

	_r[0].X = rect.left + 62 + 165;
	_r[0].Y = rect.top;
	_r[0].Width = 124;
	_r[0].Height = 26;

	int nSplit = 8 + 54 + 124 + 8;

	_r[1] = _r[2] = _r[0];
	_r[1].X = _r[0].X + nSplit;
	_r[2].X = _r[1].X + nSplit;


	SolidBrush						_drawRectbrush(Color(255, 153, 153, 153));
	Gdiplus::Pen					_drawRectpen(&_drawRectbrush, 1.);

	CView_Manager* pViewMng = CView_Manager::Instance();
	Gdiplus::GraphicsPath gdiPath;
	pViewMng->GetRoundRectPath(&gdiPath, _r[0].GetLeft(), _r[0].GetTop(), _r[0].Width, _r[0].Height, 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);

	pViewMng->GetRoundRectPath(&gdiPath, _r[1].GetLeft(), _r[1].GetTop(), _r[1].Width, _r[1].Height, 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);

	pViewMng->GetRoundRectPath(&gdiPath, _r[2].GetLeft(), _r[2].GetTop(), _r[2].Width, _r[2].Height, 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);


	if (m_dMax_kW < 0)
		return;

	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 16.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));



	CString strkW, strV[2];
	strkW.Format(_T("%.1lf kW"), m_dMax_kW * 1000);
	strV[0].Format(_T("%.3lf kV"), m_dMax_V);
	strV[1].Format(_T("%.3lf kV"), m_dMin_V);
	graphics.DrawString(strkW, -1, &_drawfont, _r[0], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(strV[0], -1, &_drawfont, _r[1], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(strV[1], -1, &_drawfont, _r[2], &_drawStrFormat, &_drawFontbrush);

}

void CView_LF_rst::Draw_TopLeft_Graph(CDC* pDC, Graphics &graphics)
{
	Gdiplus::RectF  _rect;
	_rect.X = m_rectCtrl_TopLeft[0].left;
	_rect.Y = m_rectCtrl_TopLeft[0].top + 30;
	_rect.Width = m_rectCtrl_TopLeft[0].Width();
	_rect.Height = m_rectCtrl_TopLeft[0].Height();


	SolidBrush						_drawRectbrush(Color(255, 225, 225, 225));
	Gdiplus::Pen		_drawRectpen(&_drawRectbrush, 1.);
	//graphics.FillRectangle(&_drawRectbrush, _rect);

	//_rect.Inflate(-20, -20);
	_rect.X += 60;
	//_rect.Y += 40;
//	_rect.Width -= 154;
	_rect.Width -= 70;
	_rect.Height -= 60+ 20;

	Gdiplus::RectF  _rX, _rY;
	_rX.X = _rect.X - 60;
	_rX.Y = _rect.Y;
	_rX.Width = 60;
	_rX.Height = 20;

	_rY.X = _rect.GetRight() - 84 ;
	_rY.Y = _rect.GetBottom() +20;
	_rY.Width = 84;
	_rY.Height = 20;

	//SolidBrush						_drawXYrush(Color(255, 247, 247, 247));
	//graphics.FillRectangle(&_drawXYrush, _rect);

	SolidBrush						_drawLenbrush(Color(255, 225, 225, 225));
	Gdiplus::Pen		_drawLenpen(&_drawLenbrush, 1.);
	_drawLenpen.SetDashStyle(Gdiplus::DashStyleDash);

	double dX;
	for (int i = 5; i < m_nNode_MaxCount + 2; i += 5)
	{

		dX = _rect.X + (_rect.Width  * (((double)i) / (double)m_nNode_MaxCount));
		graphics.DrawLine(&_drawLenpen, (REAL)dX, (REAL)_rect.GetTop(), (REAL)dX, (REAL)_rect.GetBottom());
	}

	


	SolidBrush						_drawXYbrush(Color(255, 0, 0, 0));
	Gdiplus::Pen		_drawXYpen(&_drawXYbrush, 1.);
	graphics.DrawLine(&_drawXYpen, _rect.GetLeft(), _rect.GetTop(), _rect.GetLeft(), _rect.GetBottom());
	graphics.DrawLine(&_drawXYpen, _rect.GetLeft(), _rect.GetBottom(), _rect.GetRight(), _rect.GetBottom());

	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 0, 0, 0));

	graphics.DrawString(_T("전압(kV)"), -1, &_drawfont, _rX, &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("선로길이(km)"), -1, &_drawfont, _rY, &_drawStrFormat, &_drawFontbrush);



	SolidBrush						_drawSelect_1_brush(Color(255, 32, 106, 207));
	Gdiplus::Pen					_drawSelect_1_pen(&_drawSelect_1_brush, 2.);

	SolidBrush						_drawSelect_2_brush(Color(255, 192, 72, 206));
	Gdiplus::Pen					_drawSelect_2_pen(&_drawSelect_2_brush, 2.);

	Gdiplus::RectF  _rect_check[2];
	_rect_check[0].X = m_rect_Graph_Check[0].left;
	_rect_check[0].Y = m_rect_Graph_Check[0].top;
	_rect_check[0].Width = m_rect_Graph_Check[0].Width();
	_rect_check[0].Height = m_rect_Graph_Check[0].Height();

	_rect_check[1].X = m_rect_Graph_Check[1].left;
	_rect_check[1].Y = m_rect_Graph_Check[1].top;
	_rect_check[1].Width = m_rect_Graph_Check[1].Width();
	_rect_check[1].Height = m_rect_Graph_Check[1].Height();

	

	//Gdiplus::Font					_drawbtnfont(_T("맑은 고딕"), 13.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
	//SolidBrush						_drawFontbrush2(Color(255, 255, 255, 255));

	//CView_Manager* pViewMng = CView_Manager::Instance();
	//Gdiplus::GraphicsPath gdiPath;
	//
	//pViewMng->GetRoundRectPath(&gdiPath, _rect_check[0].GetLeft(), _rect_check[0].GetTop(), _rect_check[0].Width, _rect_check[0].Height, 4);
	//if (m_bGraph_Check[0])
	//{
	//	
	//	graphics.FillPath(&_drawSelect_1_brush, &gdiPath);
	//	graphics.DrawString(_T("측정"), -1, &_drawbtnfont, _rect_check[0], &_drawStrFormat, &_drawFontbrush2);
	//}
	//else
	//{
	//	graphics.DrawPath(&_drawSelect_1_pen, &gdiPath);
	//	graphics.DrawString(_T("측정"), -1, &_drawbtnfont, _rect_check[0], &_drawStrFormat, &_drawSelect_1_brush);
	//}

	//pViewMng->GetRoundRectPath(&gdiPath, _rect_check[1].GetLeft(), _rect_check[1].GetTop(), _rect_check[1].Width, _rect_check[1].Height, 4);
	//if (m_bGraph_Check[1])
	//{
	//	
	//	graphics.FillPath(&_drawSelect_2_brush, &gdiPath);
	//	graphics.DrawString(_T("추정"), -1, &_drawbtnfont, _rect_check[1], &_drawStrFormat, &_drawFontbrush2);
	//}
	//else
	//{
	//	graphics.DrawPath(&_drawSelect_2_pen, &gdiPath);
	//	graphics.DrawString(_T("추정"), -1, &_drawbtnfont, _rect_check[1], &_drawStrFormat, &_drawSelect_2_brush);
	//}


	//	graphics.DrawString( _T("추정")  ,	-1, &_drawfont, _rect_check[1], &_drawStrFormat, &_drawFontbrush );


	if (m_Array_Graph.GetSize() > 0)
		Draw_TopLeft_Graph_Data(pDC, graphics, _rect);

}

void CView_LF_rst::Draw_TopLeft_Graph_Data(CDC* pDC, Graphics &graphics, Gdiplus::RectF r)
{

	SolidBrush						_drawDatabrush(Color(255, 90, 183, 255));
	Gdiplus::Pen		_drawDatapen(&_drawDatabrush, 1.);

	/*double dTempMin_V = m_dMin_V - 0.200;
	double dTemp_V = m_dMax_V - dTempMin_V + 0.200 ;*/

	double dTempMin_V = (13.200*m_dVVM_lmlo) - (0.200*sqrt(3.)) ;
	double dTemp_V = (13.200*m_dVVM_lmhi) - dTempMin_V + (0.200*sqrt(3.));

	Gdiplus::RectF r_hi, r_lo;
	SolidBrush						_drawVVMhibrush(Color(100, 237, 22, 113));
	SolidBrush						_drawVVNlobrush(Color(100, 10, 185, 146));
	SolidBrush						_drawVVMhipenbrush(Color(255, 237, 22, 113));
	SolidBrush						_drawVVMlopenbrush(Color(255, 10, 185, 146));
	Gdiplus::Pen		_drawVVMhipen(&_drawVVMhipenbrush, 1.);
	Gdiplus::Pen		_drawVVMlopen(&_drawVVMlopenbrush, 1.);

	r_hi = r;
	r_lo = r;

	r_hi.Height = r.Height - (r.Height * (((13.200*m_dVVM_lmhi) - dTempMin_V) / dTemp_V));
	r_lo.Y = r.GetBottom() - (r.Height * (((13.200*m_dVVM_lmlo) - dTempMin_V) / dTemp_V));
	r_lo.Height = r_hi.Height;

//	graphics.FillRectangle(&_drawVVMhibrush, r_hi);
//	graphics.FillRectangle(&_drawVVNlobrush, r_lo);
	graphics.DrawLine(&_drawVVMhipen, (REAL)r_hi.GetLeft(), (REAL)r_hi.GetBottom(), (REAL)r_hi.GetRight(), (REAL)r_hi.GetBottom());
	graphics.DrawLine(&_drawVVMlopen, (REAL)r_lo.GetLeft(), (REAL)r_lo.GetTop(), (REAL)r_lo.GetRight(), (REAL)r_lo.GetTop());

	Gdiplus::RectF r_hi_var, r_lo_var;
	r_hi_var.X = r_hi.X - 50;
	r_hi_var.Y = r_hi.GetBottom();
	r_hi_var.Width = 50;
	r_hi_var.Height = 1;
	r_hi_var.Inflate(0, 10);

	r_lo_var.X = r_lo.X - 50;
	r_lo_var.Y = r_lo.GetTop();
	r_lo_var.Width = 50;
	r_lo_var.Height = 1;
	r_lo_var.Inflate(0, 10);

	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentFar);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));
	CString strVVM_hi, strVVM_lo;
	strVVM_hi.Format(_T("%.3lf"), 13.200*m_dVVM_lmhi);
	strVVM_lo.Format(_T("%.3lf"), 13.200*m_dVVM_lmlo);
	graphics.DrawString(strVVM_hi, -1, &_drawfont, r_hi_var, &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(strVVM_lo, -1, &_drawfont, r_lo_var, &_drawStrFormat, &_drawFontbrush);

	CGraphData *pData;
	double  dX_P, dY_P, dX, dY, dValue[2];
	SolidBrush						_drawSWbrush_h(Color(255, 255, 23, 23));
	SolidBrush						_drawSWbrush_l(Color(255, 21, 114, 219));
	SolidBrush						_drawSWbrush_n(Color(150, 0, 0, 0));
	Gdiplus::RectF _rSW;

	Gdiplus::RectF _r_X_Tag;
	_r_X_Tag.X = -10;
	_r_X_Tag.Y = r.GetBottom() +2;
	_r_X_Tag.Width = 20;
	_r_X_Tag.Height = 20;

	double dMax_Len = -1.;
	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	{
		pData = m_Array_Graph.GetAt(i);

		if (pData->m_dLen[1] > dMax_Len)
			dMax_Len = pData->m_dLen[1];
	}

	CString strX_Tag;
	double dLen_tag = 0;
	while (dMax_Len)
	{
		dX_P = r.X + (r.Width  * (((double)dLen_tag) / (double)dMax_Len));

		_r_X_Tag.X = dX_P - 10.;

		strX_Tag.Format(_T("%.0lf"), dLen_tag);
		graphics.DrawString(strX_Tag, -1, &_drawfont, _r_X_Tag, &_drawStrFormat, &_drawFontbrush);

		dLen_tag += 1.;

		if (dLen_tag >= dMax_Len)
			break;
	}
	
	//if (m_bGraph_Check[1])
	{
		for (int i = 0; i < m_Array_Graph.GetSize(); i++)
		{
			pData = m_Array_Graph.GetAt(i);

			if (pData->m_nGNDIdx[0] < 0 /*|| pData->m_nType == 0*/)
			{
				////////////////// 노드 모양만 그리자
				continue;
			}
			dValue[0] = pData->m_dRPFO_value[0];
			dValue[1] = pData->m_dRPFO_value[1];

			if ((dValue[0] - dTempMin_V) > dTemp_V)
				dValue[0] = dTemp_V + dTempMin_V;
			else if (dValue[0] < dTempMin_V)
				dValue[0] = dTempMin_V;

			if ((dValue[1] - dTempMin_V) > dTemp_V)
				dValue[1] = dTemp_V + dTempMin_V;
			else if (dValue[1] < dTempMin_V)
				dValue[1] = dTempMin_V;

			/*dX_P = r.X + (r.Width  * (((double)pData->m_nCount - 1.) / (double)m_nNode_MaxCount));
			dY_P = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

			dX = r.X + (r.Width  * ((double)pData->m_nCount / (double)m_nNode_MaxCount));
			dY = r.GetBottom() - (r.Height * ((dValue[1] - dTempMin_V) / dTemp_V));*/

			dX_P = r.X + (r.Width  * (((double)pData->m_dLen[0]) / (double)dMax_Len));
			dY_P = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

			dX = r.X + (r.Width  * ((double)pData->m_dLen[1] / (double)dMax_Len));
			dY = r.GetBottom() - (r.Height * ((dValue[1] - dTempMin_V) / dTemp_V));

			graphics.DrawLine(&_drawDatapen, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);

		}


		for (int i = 0; i < m_Array_Graph.GetSize(); i++)
		{
			pData = m_Array_Graph.GetAt(i);

		/*	if (pData->m_nType == 0)
			{
				continue;
			}*/
			dValue[0] = pData->m_dRPFO_value[1];
			if ((dValue[0] - dTempMin_V) > dTemp_V)
				dValue[0] = dTemp_V + dTempMin_V;
			else if (dValue[0] < dTempMin_V)
				dValue[0] = dTempMin_V;

			/*dX = r.X + (r.Width  * ((double)pData->m_nCount / (double)m_nNode_MaxCount));
			dY = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));*/
			dX = r.X + (r.Width  * ((double)pData->m_dLen[1] / (double)dMax_Len));
			dY = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

			_rSW.X = dX - 2;
			_rSW.Y = dY - 2;
			_rSW.Width = 4.;
			_rSW.Height = 4.;

			if(pData->m_dRPFO_value[1] > 13.200*m_dVVM_lmhi )
				graphics.FillEllipse(&_drawSWbrush_h, _rSW);
			else if(pData->m_dRPFO_value[1] < 13.200*m_dVVM_lmlo)
				graphics.FillEllipse(&_drawSWbrush_l, _rSW);
			else
				graphics.FillEllipse(&_drawSWbrush_n, _rSW);
			


			/*if (pData->m_nCheck == 1)
			{
				SolidBrush						_drawLenbrush(Color(200, 150, 150, 150));
				Gdiplus::Pen		_drawLenpen(&_drawLenbrush, 1.);
				_drawLenpen.SetDashStyle(Gdiplus::DashStyleDashDot);

				graphics.DrawLine(&_drawLenpen, (REAL)r.GetLeft(), (REAL)dY, (REAL)dX, (REAL)dY);
				graphics.DrawLine(&_drawLenpen, (REAL)dX, (REAL)dY, (REAL)dX, (REAL)r_lo.GetBottom());

				Gdiplus::RectF r_value;
				r_value.X = dX;
				r_value.Y = dY - 20;
				r_value.Width = 50;
				r_value.Height = 20;
				_drawStrFormat.SetAlignment(StringAlignmentCenter);
				_drawLenbrush.SetColor(Color(255, 255, 243, 178));
				_drawLenpen.SetColor(Color(255, 54, 55, 59));
				_drawLenpen.SetDashStyle(Gdiplus::DashStyleSolid);

				graphics.FillRectangle(&_drawLenbrush, r_value);
				graphics.DrawRectangle(&_drawLenpen, r_value);

				CString strValue;
				strValue.Format(_T("%.3lf"), dValue[0]);
				graphics.DrawString(strValue, -1, &_drawfont, r_value, &_drawStrFormat, &_drawFontbrush);
			}*/

		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////

	//SolidBrush						_drawMeaDatabrush(Color(255, 127, 7, 106));
	//Gdiplus::Pen		_drawMeaDatapen(&_drawMeaDatabrush, 1.);
	//SolidBrush						_drawMeaSWbrush(Color(255, 7, 151, 34));
	//if (m_bGraph_Check[0])
	//{
	//	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	//	{
	//		pData = m_Array_Graph.GetAt(i);

	//		if (pData->m_nNodeID_Prev < 0 || pData->m_nType == 0 || pData->m_dCurrValue_mea <= 0.)
	//		{
	//			////////////////// 노드 모양만 그리자
	//			continue;
	//		}

	//		dValue[0] = pData->m_dPrevValue_mea;
	//		dValue[1] = pData->m_dCurrValue_mea;

	//		if ((dValue[0] - dTempMin_V) > dTemp_V)
	//			dValue[0] = dTemp_V + dTempMin_V;
	//		else if (dValue[0] < dTempMin_V)
	//			dValue[0] = dTempMin_V;

	//		if ((dValue[1] - dTempMin_V) > dTemp_V)
	//			dValue[1] = dTemp_V + dTempMin_V;
	//		else if (dValue[1] < dTempMin_V)
	//			dValue[1] = dTempMin_V;

	//		dX_P = r.X + (r.Width  * (((double)pData->m_nPrev_idx) / (double)m_nNode_MaxCount));
	//		dY_P = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

	//		dX = r.X + (r.Width  * ((double)pData->m_nCount / (double)m_nNode_MaxCount));
	//		dY = r.GetBottom() - (r.Height * ((dValue[1] - dTempMin_V) / dTemp_V));

	//		graphics.DrawLine(&_drawMeaDatapen, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);

	//	}

	//	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	//	{
	//		pData = m_Array_Graph.GetAt(i);

	//		if (pData->m_nType == 0 || pData->m_dCurrValue_mea <= 0.)
	//		{
	//			continue;
	//		}
	//		dValue[0] = pData->m_dCurrValue_mea;
	//		if ((dValue[0] - dTempMin_V) > dTemp_V)
	//			dValue[0] = dTemp_V + dTempMin_V;
	//		else if (dValue[0] < dTempMin_V)
	//			dValue[0] = dTempMin_V;

	//		dX = r.X + (r.Width  * ((double)pData->m_nCount / (double)m_nNode_MaxCount));
	//		dY = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

	//		_rSW.X = dX - 2;
	//		_rSW.Y = dY - 2;
	//		_rSW.Width = 4.;
	//		_rSW.Height = 4.;

	//		graphics.FillEllipse(&_drawMeaSWbrush, _rSW);
	//	}
	//}
	///////////////////////////////////////////////////////////////////////////////////////////
	//CString strValue;
	////double dValue_C;
	//int nSelCount;
	//if (m_ptSelect.x > 0 && m_ptSelect.y > 0)
	//{
	//	nSelCount = (m_ptSelect.x - r.X) / r.Width * m_nNode_MaxCount;

	//	double dMax = 0.;
	//	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	//	{
	//		pData = m_Array_Graph.GetAt(i);
	//		if (pData->m_nType == 0)
	//		{
	//			continue;
	//		}

	//		if (pData->m_nCount == nSelCount)
	//		{
	//			if (dMax < pData->m_dCurrValue)
	//				dMax = pData->m_dCurrValue;
	//		}
	//	}



	//	dX = r.X + (r.Width  * ((double)nSelCount / (double)m_nNode_MaxCount));

	//	dY = r.GetBottom() - (r.Height * ((dMax - dTempMin_V) / dTemp_V));

	//	strValue.Format(_T("%.3lf"), dMax);

	//	SolidBrush						_drawLenbrush(Color(200, 150, 150, 150));
	//	Gdiplus::Pen		_drawLenpen(&_drawLenbrush, 1.);
	//	_drawLenpen.SetDashStyle(Gdiplus::DashStyleDashDot);

	//	graphics.DrawLine(&_drawLenpen, (REAL)r.GetLeft(), (REAL)dY, (REAL)dX, (REAL)dY);
	//	graphics.DrawLine(&_drawLenpen, (REAL)dX, (REAL)dY, (REAL)dX, (REAL)r_lo.GetBottom());

	//	Gdiplus::RectF r_value;
	//	r_value.X = dX;
	//	r_value.Y = dY - 20;
	//	r_value.Width = 50;
	//	r_value.Height = 20;
	//	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	//	_drawLenbrush.SetColor(Color(255, 150, 200, 59));
	//	_drawLenpen.SetColor(Color(255, 54, 55, 59));
	//	_drawLenpen.SetDashStyle(Gdiplus::DashStyleSolid);

	//	graphics.FillRectangle(&_drawLenbrush, r_value);
	//	graphics.DrawRectangle(&_drawLenpen, r_value);

	//	graphics.DrawString(strValue, -1, &_drawfont, r_value, &_drawStrFormat, &_drawFontbrush);
	//}

}

void CView_LF_rst::Draw_TopRight_Title(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectCtrl_TopRight[0];

	rect.InflateRect(-8, -10);

	Gdiplus::RectF  _r[3];

	_r[0].X = rect.right - 369 ;
	_r[0].Y = rect.top + 40;
	_r[0].Width = 22;
	_r[0].Height = rect.Height();
		
	_r[1] = _r[2] = _r[0];

	_r[1].X = _r[0].X + _r[0].Width + 85;
	_r[1].Width = 33;

	_r[2].X = _r[1].X + _r[1].Width + 85;
	_r[2].Width = 58;

	CPoint ptEx[3];
	ptEx[0].x = _r[0].X + _r[0].Width + 8;
	ptEx[0].y = rect.CenterPoint().y +40;

	ptEx[1].x = _r[1].X + _r[1].Width + 8;
	ptEx[1].y = rect.CenterPoint().y + 40;

	ptEx[2].x = _r[2].X + _r[2].Width + 8;
	ptEx[2].y = rect.CenterPoint().y + 40;


	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));


	graphics.DrawString(_T("PV"), -1, &_drawfont, _r[0], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("Load"), -1, &_drawfont, _r[1], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("Net load"), -1, &_drawfont, _r[2], &_drawStrFormat, &_drawFontbrush);


	SolidBrush						LineBrush(Color(255, 23, 23, 233));
	Gdiplus::Pen					_drawLinepen(&LineBrush, 2.);
	
	graphics.DrawLine(&_drawLinepen, ptEx[0].x, ptEx[0].y, ptEx[0].x + 62, ptEx[0].y);

	LineBrush.SetColor(Color(255, 12, 133, 12));
	_drawLinepen.SetBrush(&LineBrush);
	graphics.DrawLine(&_drawLinepen, ptEx[1].x, ptEx[1].y, ptEx[1].x + 62, ptEx[1].y);

	LineBrush.SetColor(Color(255, 255, 8, 8));
	_drawLinepen.SetBrush(&LineBrush);
	graphics.DrawLine(&_drawLinepen, ptEx[2].x, ptEx[2].y, ptEx[2].x + 62, ptEx[2].y);

	Draw_TopRight_Graph(pDC, graphics);

	Draw_TopRight_Infor(pDC, graphics);
}

void CView_LF_rst::Draw_TopRight_Infor(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectCtrl_TopRight[0];
	rect.InflateRect(-8, -10);

	Gdiplus::RectF  _r[3],_rName[3];

	_r[0].X = rect.left + 68;
	_r[0].Y = rect.top;
	_r[0].Width = 124;
	_r[0].Height = 26;

	int nSplit = 8 + 60 + 124 + 8;

	_r[1] = _r[2] = _r[0];
	_r[1].X = _r[0].X + nSplit;
	_r[2].X = _r[1].X + nSplit;

	_rName[0] = _r[0];
	_rName[0].X -= 60;
	_rName[0].Width = 60;

	_rName[1] = _r[1];
	_rName[1].X -= 60;
	_rName[1].Width = 60;

	_rName[2] = _r[2];
	_rName[2].X -= 60;
	_rName[2].Width = 60;

	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));


	graphics.DrawString(_T("총 부하"), -1, &_drawfont, _rName[0], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("총 발전"), -1, &_drawfont, _rName[1], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("Net 부하"), -1, &_drawfont, _rName[2], &_drawStrFormat, &_drawFontbrush);


	SolidBrush						_drawRectbrush(Color(255, 153, 153, 153));
	Gdiplus::Pen					_drawRectpen(&_drawRectbrush, 1.);

	CView_Manager* pViewMng = CView_Manager::Instance();
	Gdiplus::GraphicsPath gdiPath;
	pViewMng->GetRoundRectPath(&gdiPath, _r[0].GetLeft(), _r[0].GetTop(), _r[0].Width, _r[0].Height, 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);

	pViewMng->GetRoundRectPath(&gdiPath, _r[1].GetLeft(), _r[1].GetTop(), _r[1].Width, _r[1].Height, 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);

	pViewMng->GetRoundRectPath(&gdiPath, _r[2].GetLeft(), _r[2].GetTop(), _r[2].Width, _r[2].Height, 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);


	if (m_dMax_Load < 0)
		return;

	Gdiplus::Font					_drawfont_Value(_T("맑은 고딕"), 16.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
	StringFormat					_drawStrFormat_Value;
	_drawStrFormat_Value.SetAlignment(StringAlignmentCenter);
	_drawStrFormat_Value.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush_Value(Color(255, 54, 55, 59));



	CString strkW[3];
	strkW[0].Format(_T("%.1lf kW"), m_dMax_Load * 1000);
	strkW[1].Format(_T("%.1lf kW"), m_dMax_Gen * 1000);
	strkW[2].Format(_T("%.1lf kW"), (m_dMax_Load - m_dMax_Gen) * 1000);
	graphics.DrawString(strkW[0], -1, &_drawfont_Value, _r[0], &_drawStrFormat_Value, &_drawFontbrush_Value);
	graphics.DrawString(strkW[1], -1, &_drawfont_Value, _r[1], &_drawStrFormat_Value, &_drawFontbrush_Value);
	graphics.DrawString(strkW[2], -1, &_drawfont_Value, _r[2], &_drawStrFormat_Value, &_drawFontbrush_Value);

	

}


void CView_LF_rst::Draw_TopRight_Graph(CDC* pDC, Graphics &graphics)
{
	//CRect rect = m_rectCtrl_TopRight[1];

	//rect.InflateRect(-10, -10);
	//rect.top += 40;
	//rect.left += 50;
	//rect.bottom -= 50;

	//
	//SolidBrush						LineBrush(Color(255, 0,0,0));
	//Gdiplus::Pen					_drawLinepen(&LineBrush, 1.);

	//graphics.DrawLine(&_drawLinepen, rect.left , rect.bottom, rect.left, rect.top);
	//graphics.DrawLine(&_drawLinepen, rect.left, rect.bottom, rect.right, rect.bottom);

	//////////////////////////////////////////////////////////////////////

	//Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	//StringFormat					_drawStrFormat;
	//_drawStrFormat.SetAlignment(StringAlignmentFar);
	//_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	//SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));

	//Gdiplus::RectF  _rect_Y_Name;
	//Gdiplus::RectF  _rect_X_Name;
	//Gdiplus::RectF  _rect_Y_Split[7];

	//_rect_Y_Name.X = m_rectCtrl_TopRight[1].left;
	//_rect_Y_Name.Y = rect.top - 40;
	//_rect_Y_Name.Width = 60;
	//_rect_Y_Name.Height = 20;

	//_rect_X_Name.X = rect.right - 60;
	//_rect_X_Name.Y = rect.bottom + 20;
	//_rect_X_Name.Width = 60;
	//_rect_X_Name.Height = 20;

	//graphics.DrawString(_T("전력(kW)"), -1, &_drawfont, _rect_Y_Name, &_drawStrFormat, &_drawFontbrush);
	//graphics.DrawString(_T("기간"), -1, &_drawfont, _rect_X_Name, &_drawStrFormat, &_drawFontbrush);


	//double dY_Split = double(rect.Height() / 6.);
	//int nMax = 15000 , nMin = -15000;
	//CString strSplit;

	//for (int i = 0; i < 7; i++)
	//{
	//	_rect_Y_Split[i] = _rect_Y_Name;

	//	_rect_Y_Split[i].Y = rect.top + (dY_Split * i) -10;

	//	strSplit.Format(_T("%d"), nMax - (5000 * i)) ;

	//	graphics.DrawString(strSplit , -1, &_drawfont, _rect_Y_Split[i], &_drawStrFormat, &_drawFontbrush);
	//}

	//
	////////////////////////////////////////////////////////////////////////////////////

	//SolidBrush						LineBrush_1(Color(255, 23, 23, 233));
	//SolidBrush						LineBrush_2(Color(255, 12, 133, 12));
	//SolidBrush						LineBrush_3(Color(255, 255, 8, 8));
	//Gdiplus::Pen					_drawLinepen_1(&LineBrush_1, 2.);
	//Gdiplus::Pen					_drawLinepen_2(&LineBrush_2, 2.);
	//Gdiplus::Pen					_drawLinepen_3(&LineBrush_3, 2.);

	//Gdiplus::RectF  r;
	//r.X = rect.left;
	//r.Y = rect.top;
	//r.Width = rect.Width();
	//r.Height = rect.Height();

	//Gdiplus::RectF  rIndex;
	//_drawStrFormat.SetAlignment(StringAlignmentCenter);

	//CGraph_DLE* pData[2];
	//double  dX_P, dY_P, dX, dY, dValue[2];
	//int nCount = m_Array_Graph_DLE.GetSize();
	//CString strIndex;



	//for (int i = 1; i < m_Array_Graph_DLE.GetSize(); i++)
	//{
	//	pData[0] = m_Array_Graph_DLE.GetAt(i-1);
	//	pData[1] = m_Array_Graph_DLE.GetAt(i);

	//	dValue[0] = pData[0]->m_dValue[0];
	//	dValue[1] = pData[1]->m_dValue[0];

	//	if (dValue[0] > nMax)
	//		dValue[0] = double(nMax) ;
	//	else if (dValue[0] < nMin)
	//		dValue[0] = double(nMin);

	//	if (dValue[1] > nMax)
	//		dValue[1] = double(nMax);
	//	else if (dValue[1] < nMin)
	//		dValue[1] = double(nMin);

	//	dX_P = r.X + (r.Width  * (((double) i - 1.) / (double)nCount));
	//	dY_P = r.GetBottom() - (r.Height * ((dValue[0] - nMin ) / double(nMax - nMin) ));

	//	dX = r.X + (r.Width  * ((double) i  / (double)nCount));
	//	dY = r.GetBottom() - (r.Height * ((dValue[1] - nMin) / double(nMax - nMin)));


	//	graphics.DrawLine(&_drawLinepen_1, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);

	//	strIndex.Format(_T("%d"), pData[1]->m_nIndex);
	//	rIndex.X = dX - 10;
	//	rIndex.Y = r.GetBottom() + 5;
	//	rIndex.Width = 20;
	//	rIndex.Height = 20;


	//	graphics.DrawString(strIndex, -1, &_drawfont, rIndex, &_drawStrFormat, &_drawFontbrush);

	//	if (i == 1)
	//	{
	//		strIndex.Format(_T("%d"), pData[0]->m_nIndex);
	//		rIndex.X = dX_P - 10;
	//		graphics.DrawString(strIndex, -1, &_drawfont, rIndex, &_drawStrFormat, &_drawFontbrush);
	//	}

	//	

	//}
	///////////////////////////////////////////////////////
	//for (int i = 1; i < m_Array_Graph_DLE.GetSize(); i++)
	//{
	//	pData[0] = m_Array_Graph_DLE.GetAt(i - 1);
	//	pData[1] = m_Array_Graph_DLE.GetAt(i);

	//	dValue[0] = pData[0]->m_dValue[1];
	//	dValue[1] = pData[1]->m_dValue[1];

	//	if (dValue[0] > nMax)
	//		dValue[0] = double(nMax);
	//	else if (dValue[0] < nMin)
	//		dValue[0] = double(nMin);

	//	if (dValue[1] > nMax)
	//		dValue[1] = double(nMax);
	//	else if (dValue[1] < nMin)
	//		dValue[1] = double(nMin);

	//	dX_P = r.X + (r.Width  * (((double)i - 1.) / (double)nCount));
	//	dY_P = r.GetBottom() - (r.Height * ((dValue[0] - nMin) / double(nMax - nMin)));

	//	dX = r.X + (r.Width  * ((double)i / (double)nCount));
	//	dY = r.GetBottom() - (r.Height * ((dValue[1] - nMin) / double(nMax - nMin)));


	//	graphics.DrawLine(&_drawLinepen_2, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);

	//}
	///////////////////////////////////////////////////////

	//for (int i = 1; i < m_Array_Graph_DLE.GetSize(); i++)
	//{
	//	pData[0] = m_Array_Graph_DLE.GetAt(i - 1);
	//	pData[1] = m_Array_Graph_DLE.GetAt(i);

	//	dValue[0] = pData[0]->m_dValue[2];
	//	dValue[1] = pData[1]->m_dValue[2];

	//	if (dValue[0] > nMax)
	//		dValue[0] = double(nMax);
	//	else if (dValue[0] < nMin)
	//		dValue[0] = double(nMin);

	//	if (dValue[1] > nMax)
	//		dValue[1] = double(nMax);
	//	else if (dValue[1] < nMin)
	//		dValue[1] = double(nMin);

	//	dX_P = r.X + (r.Width  * (((double)i - 1.) / (double)nCount));
	//	dY_P = r.GetBottom() - (r.Height * ((dValue[0] - nMin) / double(nMax - nMin)));

	//	dX = r.X + (r.Width  * ((double)i / (double)nCount));
	//	dY = r.GetBottom() - (r.Height * ((dValue[1] - nMin) / double(nMax - nMin)));


	//	graphics.DrawLine(&_drawLinepen_3, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);

	//}
}


void CView_LF_rst::Draw_TopRight_circle(CDC* pDC, Graphics &graphics)
{
	Gdiplus::RectF  _rect;
	_rect.X = m_rectCtrl_TopRight[1].left;
	_rect.Y = m_rectCtrl_TopRight[1].top;
	_rect.Width = m_rectCtrl_TopRight[1].Width();
	_rect.Height = m_rectCtrl_TopRight[1].Height();


	//SolidBrush						_drawRectbrush(Color(255, 225, 225, 225));
	//graphics.FillRectangle(&_drawRectbrush, _rect);

	//_rect.Inflate(-20, -20);
	//SolidBrush						_drawXYrush(Color(255, 245, 245, 255));
	//graphics.FillRectangle(&_drawXYrush, _rect);

	Gdiplus::RectF  _rChart[3];
	Gdiplus::RectF  _rChart_center[3];
	Gdiplus::RectF  _rChart_header[3];
	Gdiplus::RectF  _rChart_type[3];

	_rChart[0] = _rect;
	_rChart[0].Width = _rect.Width * 1 / 3 -1;

	_rChart[1] = _rect;
	_rChart[1].X = _rChart[0].GetRight() + 1 ;
	_rChart[1].Width = _rect.Width * 1 / 3 -1;

	_rChart[2] = _rect;
	_rChart[2].X = _rChart[1].GetRight() -1;
	_rChart[2].Width = _rect.Width * 1 / 3;

	_rChart_header[0] = _rChart[0];
	_rChart_header[1] = _rChart[1];
	_rChart_header[2] = _rChart[2];

	_rChart_header[0].Height = 86;
	_rChart_header[1].Height = 86;
	_rChart_header[2].Height = 86;

	_rChart_type[0].Y = _rChart[0].GetTop() + 86 + 229 + 29;
	_rChart_type[1].Y = _rChart[1].GetTop() + 86 + 229 + 29;
	_rChart_type[2].Y = _rChart[2].GetTop() + 86 + 229 + 29;

	_rChart_type[0].X = _rChart[0].GetLeft();
	_rChart_type[1].X = _rChart[1].GetLeft() ;
	_rChart_type[2].X = _rChart[2].GetLeft();

	_rChart_type[0].Width = 22 + 38 + 24 + 22 + 38;
	_rChart_type[1].Width = 22 + 38 + 24 + 22 + 38;
	_rChart_type[2].Width = 22 + 38 + 24 + 22 + 38;

	_rChart_type[0].Height = 20;
	_rChart_type[1].Height = 20;
	_rChart_type[2].Height = 20;

	_rChart[0].Inflate(-41, 0);
	_rChart[1].Inflate(-41, 0);
	_rChart[2].Inflate(-41, 0);

	_rChart[0].Y += 86;
	_rChart[1].Y += 86;
	_rChart[2].Y += 86;

	_rChart[0].Height = 229 ;
	_rChart[1].Height = 229;
	_rChart[2].Height = 229;

	_rChart_center[0] = _rChart[0];
	_rChart_center[1] = _rChart[1];
	_rChart_center[2] = _rChart[2];

	_rChart_center[0].Inflate( -64, -64);
	_rChart_center[1].Inflate( -64, -64);
	_rChart_center[2].Inflate( -64, -64);

	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 14.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 0, 0, 0));


	graphics.DrawString(_T("DG 연계개소"), -1, &_drawfont, _rChart_header[0], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("DG 연계용량"), -1, &_drawfont, _rChart_header[1], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("DG 발전량"), -1, &_drawfont, _rChart_header[2], &_drawStrFormat, &_drawFontbrush);


	if (m_Array_Graph.GetSize() == 0)
		return;

	int		nCount_Max = 0, nCount_hi(0), nCount_lo(0);
	double  dkVA_Max(0.), dkVA_hi(0.), dkVA_lo(0.);
	/*CGraph_info* pRPF;
	int nTest = 0;
	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	{
		pRPF = m_Array_Graph.GetAt(i);

		if (pRPF->m_nGen_type == 8)
		{
			nCount_lo++;
			dkVA_lo += pRPF->m_dGen_Value_kVA;
		}

		if (pRPF->m_nGen_type == 9)
		{
			nCount_hi++;
			dkVA_hi += pRPF->m_dGen_Value_kVA;
		}

		if (pRPF->m_nGen_type > 0)
			nTest++;
	}
*/
	nCount_Max = nCount_lo + nCount_hi;
	dkVA_Max = dkVA_lo + dkVA_hi;

	if (nCount_Max > 0)
	{
		SolidBrush						_drawChartbrush_center(Color(255, 255, 255, 255));
		SolidBrush						_drawChartbrush_1_1(Color(255, 68, 172, 255));
		SolidBrush						_drawChartbrush_1_2(Color(255, 176, 196, 211));

		double dAngle[2];

		dAngle[0] = 360. * double(nCount_hi) / double(nCount_Max);
		dAngle[1] = 360. * double(nCount_lo) / double(nCount_Max);


		//////////////////////////////////////////////

		graphics.FillPie(&_drawChartbrush_1_1, _rChart[0], 270., dAngle[0]);
		graphics.FillPie(&_drawChartbrush_1_2, _rChart[0], dAngle[0] - 90., dAngle[1]);

		graphics.FillEllipse(&_drawChartbrush_center, _rChart_center[0]);


		CRect rDump[2];
		rDump[0].SetRect(_rChart[0].GetLeft(), _rChart[0].GetTop(), _rChart[0].GetRight(), _rChart[0].GetBottom());

		Gdiplus::PointF ptValue[2], ptCenter, ptBase;
		ptCenter.X = rDump[0].CenterPoint().x;
		ptCenter.Y = rDump[0].CenterPoint().y;
		ptBase.X = rDump[0].CenterPoint().x;
		ptBase.Y = rDump[0].top + (_rChart[0].Width * 1 / 8);

		ptValue[0] = RotatePoint(ptBase, ptCenter, dAngle[0] / 2);
		ptValue[1] = RotatePoint(ptBase, ptCenter, dAngle[1] / 2 + dAngle[0]);

		Gdiplus::RectF  _rChart_data[2];

		_rChart_data[0].X = ptValue[0].X - 5;
		_rChart_data[0].Y = ptValue[0].Y - 5;
		_rChart_data[0].Width = 10;
		_rChart_data[0].Height = 10;
		_rChart_data[0].Inflate(15, 5);

		_rChart_data[1].X = ptValue[1].X - 5;
		_rChart_data[1].Y = ptValue[1].Y - 5;
		_rChart_data[1].Width = 10;
		_rChart_data[1].Height = 10;
		_rChart_data[1].Inflate(15, 5);

		Gdiplus::Font					_drawValuefont(_T("맑은 고딕"), 18.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
		SolidBrush						_drawFontbrush_w(Color(255, 255, 255, 255));
		CString strValue[3];

		strValue[0].Format(_T("%d"), nCount_hi);
		strValue[1].Format(_T("%d"), nCount_lo);
		strValue[2].Format(_T("%d 개소"), nCount_Max);

		graphics.DrawString(strValue[0], -1, &_drawValuefont, _rChart_data[0], &_drawStrFormat, &_drawFontbrush_w);
		graphics.DrawString(strValue[1], -1, &_drawValuefont, _rChart_data[1], &_drawStrFormat, &_drawFontbrush);
		graphics.DrawString(strValue[2], -1, &_drawValuefont, _rChart_center[0], &_drawStrFormat, &_drawFontbrush);

		Gdiplus::Font					_drawTypefont(_T("맑은 고딕"), 12.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);

		Gdiplus::RectF  _rType[2];

		_rType[0] = _rChart_type[0];
		_rType[0].Width = 22;
		_rType[0].Height = 20;
		_rType[0].Inflate(0, -5);

		_rType[1] = _rType[0];
		_rType[1].X += 22;
		_rType[1].Width = 20;

		graphics.FillRectangle(&_drawChartbrush_1_1, _rType[0]);
		graphics.DrawString(_T("고압"), -1, &_drawTypefont, _rType[1], &_drawStrFormat, &_drawFontbrush);

		_rType[0].X = _rType[0].GetRight() + 62;
		_rType[1].X = _rType[1].GetRight() + 62;

		graphics.FillRectangle(&_drawChartbrush_1_2, _rType[0]);
		graphics.DrawString(_T("저압"), -1, &_drawTypefont, _rType[1], &_drawStrFormat, &_drawFontbrush);

		////////////////////////////////////////////////////////////////////////////////

		dAngle[0] = 360. * dkVA_hi / dkVA_Max;
		dAngle[1] = 360. * dkVA_lo / dkVA_Max;

		graphics.FillPie(&_drawChartbrush_1_1, _rChart[1], 270, dAngle[0]);
		graphics.FillPie(&_drawChartbrush_1_2, _rChart[1], dAngle[0] - 90., dAngle[1]);

		graphics.FillEllipse(&_drawChartbrush_center, _rChart_center[1]);

		rDump[1].SetRect(_rChart[1].GetLeft(), _rChart[1].GetTop(), _rChart[1].GetRight(), _rChart[1].GetBottom());

		ptCenter.X = rDump[1].CenterPoint().x;
		ptCenter.Y = rDump[1].CenterPoint().y;
		ptBase.X = rDump[1].CenterPoint().x;
		ptBase.Y = rDump[1].top + (_rChart[1].Width * 1 / 8);

		ptValue[0] = RotatePoint(ptBase, ptCenter, dAngle[0] / 2);
		ptValue[1] = RotatePoint(ptBase, ptCenter, dAngle[1] / 2 + dAngle[0]);

		_rChart_data[0].X = ptValue[0].X - 5;
		_rChart_data[0].Y = ptValue[0].Y - 5;
		_rChart_data[0].Width = 10;
		_rChart_data[0].Height = 10;
		_rChart_data[0].Inflate(15, 5);

		_rChart_data[1].X = ptValue[1].X - 5;
		_rChart_data[1].Y = ptValue[1].Y - 5;
		_rChart_data[1].Width = 10;
		_rChart_data[1].Height = 10;
		_rChart_data[1].Inflate(15, 5);

		strValue[0].Format(_T("%.1lf"), dkVA_hi);
		strValue[1].Format(_T("%.1lf"), dkVA_lo);
		strValue[2].Format(_T("%.1lf MVA"), dkVA_Max);

		graphics.DrawString(strValue[0], -1, &_drawValuefont, _rChart_data[0], &_drawStrFormat, &_drawFontbrush_w);
		graphics.DrawString(strValue[1], -1, &_drawValuefont, _rChart_data[1], &_drawStrFormat, &_drawFontbrush);
		graphics.DrawString(strValue[2], -1, &_drawValuefont, _rChart_center[1], &_drawStrFormat, &_drawFontbrush);

		_rType[0] = _rChart_type[1];
		_rType[0].Width = 22;
		_rType[0].Height = 20;
		_rType[0].Inflate(0, -5);

		_rType[1] = _rType[0];
		_rType[1].X += 22;
		_rType[1].Width = 38;

		graphics.FillRectangle(&_drawChartbrush_1_1, _rType[0]);
		graphics.DrawString(_T("고압"), -1, &_drawTypefont, _rType[1], &_drawStrFormat, &_drawFontbrush);

		_rType[0].X = _rType[0].GetRight() + 62;
		_rType[1].X = _rType[1].GetRight() + 62;

		graphics.FillRectangle(&_drawChartbrush_1_2, _rType[0]);
		graphics.DrawString(_T("저압"), -1, &_drawTypefont, _rType[1], &_drawStrFormat, &_drawFontbrush);
	}



	double  dMW_Max(0.);

	dMW_Max = abs(m_dSum_Load) + abs(m_dSum_Gen);

	if (dMW_Max > 0.)
	{
		SolidBrush						_drawChartbrush_center(Color(255, 255, 255, 255));
		SolidBrush						_drawChartbrush_1_1(Color(255, 255, 51, 51));
		SolidBrush						_drawChartbrush_1_2(Color(255, 236, 181, 181));

		double dAngle[2];

		dAngle[0] = 360. * m_dSum_Load / dMW_Max;
		dAngle[1] = 360. * m_dSum_Gen / dMW_Max;


		//////////////////////////////////////////////

		graphics.FillPie(&_drawChartbrush_1_1, _rChart[2], 270., dAngle[0]);
		graphics.FillPie(&_drawChartbrush_1_2, _rChart[2], dAngle[0] - 90., dAngle[1]);

		graphics.FillEllipse(&_drawChartbrush_center, _rChart_center[2]);


		CRect rDump[2];
		rDump[0].SetRect(_rChart[2].GetLeft(), _rChart[2].GetTop(), _rChart[2].GetRight(), _rChart[2].GetBottom());

		Gdiplus::PointF ptValue[2], ptCenter, ptBase;
		ptCenter.X = rDump[0].CenterPoint().x;
		ptCenter.Y = rDump[0].CenterPoint().y;
		ptBase.X = rDump[0].CenterPoint().x;
		ptBase.Y = rDump[0].top + (_rChart[2].Width * 1 / 8);

		ptValue[0] = RotatePoint(ptBase, ptCenter, dAngle[0] / 2);
		ptValue[1] = RotatePoint(ptBase, ptCenter, dAngle[1] / 2 + dAngle[0]);

		Gdiplus::RectF  _rChart_data[2];

		_rChart_data[0].X = ptValue[0].X - 5;
		_rChart_data[0].Y = ptValue[0].Y - 5;
		_rChart_data[0].Width = 10;
		_rChart_data[0].Height = 10;
		_rChart_data[0].Inflate(15, 5);

		_rChart_data[1].X = ptValue[1].X - 5;
		_rChart_data[1].Y = ptValue[1].Y - 5;
		_rChart_data[1].Width = 10;
		_rChart_data[1].Height = 10;
		_rChart_data[1].Inflate(15, 5);

		Gdiplus::Font					_drawValuefont(_T("맑은 고딕"), 18.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
		SolidBrush						_drawFontbrush_w(Color(255, 255, 255, 255));
		CString strValue[3];

		strValue[0].Format(_T("%.1lf"), m_dSum_Load);
		strValue[1].Format(_T("%.1lf"), m_dSum_Gen);
		strValue[2].Format(_T("%.1lf MW"), dMW_Max);

		graphics.DrawString(strValue[0], -1, &_drawValuefont, _rChart_data[0], &_drawStrFormat, &_drawFontbrush_w);
		graphics.DrawString(strValue[1], -1, &_drawValuefont, _rChart_data[1], &_drawStrFormat, &_drawFontbrush);
		graphics.DrawString(strValue[2], -1, &_drawValuefont, _rChart_center[2], &_drawStrFormat, &_drawFontbrush);

		Gdiplus::Font					_drawTypefont(_T("맑은 고딕"), 12.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);

		Gdiplus::RectF  _rType[2];

		_rType[0] = _rChart_type[2];
		_rType[0].Width = 22;
		_rType[0].Height = 20;
		_rType[0].Inflate(0, -5);

		_rType[1] = _rType[0];
		_rType[1].X += 22;
		_rType[1].Width = 20;
		
		graphics.FillRectangle(&_drawChartbrush_1_1, _rType[0]);
		graphics.DrawString(_T("측정"), -1, &_drawTypefont, _rType[1], &_drawStrFormat, &_drawFontbrush);

		_rType[0].X = _rType[0].GetRight() + 62;
		_rType[1].X = _rType[1].GetRight() + 62;

		graphics.FillRectangle(&_drawChartbrush_1_2, _rType[0]);
		graphics.DrawString(_T("추정"), -1, &_drawTypefont, _rType[1], &_drawStrFormat, &_drawFontbrush);
	}

}

Gdiplus::PointF CView_LF_rst::RotatePoint(Gdiplus::PointF ptCurrent, Gdiplus::PointF ptBase, double dAngle)//대상좌표, 기준좌표, 각도(0~360)
{
	Gdiplus::PointF ptChangePoint;
	double dPi = 3.1415926535;

	ptChangePoint.X = (int)floor((ptCurrent.X - ptBase.X)*cos(dAngle / 180.*dPi) - (ptCurrent.Y - ptBase.Y)*sin(dAngle / 180.*dPi)) + ptBase.X;
	ptChangePoint.Y = (int)floor((ptCurrent.X - ptBase.X)*sin(dAngle / 180.*dPi) + (ptCurrent.Y - ptBase.Y)*cos(dAngle / 180.*dPi)) + ptBase.Y;

	return ptChangePoint;
}


void CView_LF_rst::Get_TitleData_DLE()
{
	int nSel = m_ctrCombo[1].GetCurSel();

	if (nSel == -1)
		return;

	int nDL_Idx = (int)m_ctrCombo[1].GetItemData(nSel);

	m_dMax_Load = GETVALUE(double, _T("dl_dyn_rpfo"), _T("dl_3pldrpfmw"), nDL_Idx);
	m_dMax_Gen = GETVALUE(double, _T("dl_dyn_rpfo"), _T("dl_3pgenrpfmw"), nDL_Idx);
	m_dSum_Gen = GETVALUE(double, _T("dl_dyn_stdleo"), _T("dl_gen_ra_sum"), nDL_Idx);


	int nCBSW_hi_idx, nCBSW_si_idx,nType;
	int nCBSW_idx = -1;

	nCBSW_hi_idx = GETVALUE(int, _T("dl_sta"), _T("dl_hi_cbsw"), nDL_Idx);
	while (1)
	{
		nType = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCBSW_hi_idx);
		if (nType == 1)
		{
			nCBSW_idx = nCBSW_hi_idx;
			break;
		}

		nCBSW_si_idx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_dl"), nCBSW_hi_idx);
		if(nCBSW_si_idx == 0)
			break;

		nCBSW_hi_idx = nCBSW_si_idx;
	}

	if(nCBSW_idx != -1)
		m_dSum_Load = GETVALUE(double, _T("cbsw_dyn_rpfo"), _T("cbsw_parpfamp"), nCBSW_idx);

	//UpdateData_DLE(nDL_idx);
}

BOOL	CView_LF_rst::Check_ChartData_DLE(int nCBSW_idx)
{
	/*CGroup_info* pData;

	for (int i = 0; i < m_Array_Group.GetSize(); i++)
	{
		pData = m_Array_Group.GetAt(i);

		if (pData->m_nCBSW_idx == nCBSW_idx)
			return FALSE;
	}
*/
	return TRUE;
}

void CView_LF_rst::SetSumData_DLE()
{
	m_dSum_Gen = m_dSum_Load = 0.;
	CString strCheck, strLoad, strGen;
	for (int i = 0; i < m_ctrList[1].GetItemCount(); i++)
	{
		strCheck = m_ctrList[1].GetItemText(i, 0);

		/*	if(strCheck.IsEmpty())
				continue;*/
		strLoad = m_ctrList[1].GetItemText(i, 5);
		strGen = m_ctrList[1].GetItemText(i, 6);

		m_dSum_Load += (_wtof(strLoad) / 1000.);
		m_dSum_Gen += (_wtof(strGen) / 1000.);
	}

	RedrawWindow();
}

void CView_LF_rst::Get_ChartData_DLE()
{
	Group_Data_Clear();
	/*int nCount = theAppDataMng->GetTableMaxCount(_T("spf_dyn_spfo"));

	CString strData;
	int nIdx;
	double dValue[3];
	CGraph_DLE* pData;

	for (int i = 1; i <= nCount; i++)
	{
		nIdx = GETVALUE(int, ("spf_dyn_spfo"), ("spfo_index"), i);
		strData = GETSTRING(_T("spf_dyn_spfo"), _T("spfo_step"), i);
		if (strData.IsEmpty())
			break;

		dValue[0] = GETVALUE(double, ("spf_dyn_spfo"), ("spfo_genp"), i);
		dValue[1] = GETVALUE(double, ("spf_dyn_spfo"), ("spfo_gloadp"), i);
		dValue[2] = GETVALUE(double, ("spf_dyn_spfo"), ("spfo_netp"), i);
	
		pData = new CGraph_DLE();
		m_Array_Graph_DLE.Add(pData);
		pData->m_nIndex = nIdx;
		pData->m_dValue[0] = dValue[0] * 1000;
		pData->m_dValue[1] = dValue[1] * 1000;
		pData->m_dValue[2] = dValue[2] * 1000;
	}
*/
	
}

void CView_LF_rst::UpdateData_DLE()
{
	m_ctrList[1].DeleteAllItems();

	
	CString strValue[4];
	double dValue[2];
	int nCBSW_idx;

	CString strName;
	int nCount = theAppDataMng->GetTableRealCount(_T("cbgroup_dyn_dleo"));
	for (int i = 1; i <= (int)nCount; i++)
	{

		nCBSW_idx = GETVALUE(int, _T("cbgroup_dyn_dleo"), _T("cbgroup_firstcb"), i);

		if(nCBSW_idx == 0)
			break;

		strName = GETSTRING(_T("cbgroup_dyn_dleo"), _T("cbgroup_nm"), i);
		dValue[0] = GETVALUE(double, _T("cbgroup_dyn_dleo"), _T("cbgroup_3pgenestmw"), i) * 1000;
		dValue[1] = GETVALUE(double, _T("cbgroup_dyn_dleo"), _T("cbgroup_3pnetldmw"), i) * 1000;

		strValue[0].Format(_T("%.1lf"), dValue[0]  + dValue[1]);
		strValue[1].Format(_T("%.1lf"), dValue[0]);
		strValue[2].Format(_T("%.1lf"), dValue[1]);
		strValue[3].Format(_T("%d"), nCBSW_idx );

		m_ctrList[1].InsertItem(m_ctrList[1].GetItemCount(), strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 1, strValue[0], RGB(0, 0, 0), RGB(255, 255, 255));
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 2, strValue[1], RGB(0, 0, 0), RGB(255, 255, 255));
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 3, strValue[2], RGB(0, 0, 0), RGB(255, 255, 255));
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 4, strValue[3], RGB(0, 0, 0), RGB(255, 255, 255));
	}


	//SetSumData_DLE();
}

void CView_LF_rst::Get_TitleData_RPF()
{
	CGraphData* pData;
	int nCBSW_idx[2], nBS_idx, nND_idx, nGen_idx;

	double dValue_kW, dValue_V[3];
	m_dMax_kW = 0;
	m_dMax_V = -1;
	m_dMin_V = 99999;


	//for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	//{
	//	pData = m_Array_Graph.GetAt(i);

	//	nCBSW_idx[0] = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), pData->m_nGNDIdx[1]);
	//	nCBSW_idx[1] = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), pData->m_nGNDIdx[1]);
	//	nND_idx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_nd"), pData->m_nGNDIdx[1]);

	//	nGen_idx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), nND_idx);

	//	/*if (nGen_idx > 0)
	//	{
	//		pData->m_nGen_idx = nGen_idx;
	//		pData->m_nGen_type = GETVALUE(int, _T("gen_sta"), _T("gen_type"), nGen_idx);
	//		pData->m_dGen_Value_kVA = GETVALUE(double, _T("gen_sta"), _T("gen_mwlmmx"), nGen_idx);
	//	}*/


	//	dValue_kW = 0;
	//	if (nCBSW_idx[0] > 0)
	//	{
	//		dValue_kW = GETVALUE(double, _T("cbsw_dyn_rpfo"), _T("cbsw_3prpfmw"), nCBSW_idx[0]);
	//	}
	//	else if (nCBSW_idx[1] > 0)
	//	{
	//		dValue_kW = GETVALUE(double, _T("cbsw_dyn_rpfo"), _T("cbsw_3prpfmw"), nCBSW_idx[1]);
	//	}

	//	if (abs(dValue_kW) > abs(m_dMax_kW))
	//	{
	//		m_dMax_kW = dValue_kW;
	//	}

	//	nBS_idx = GETVALUE(int, _T("gnd_dyn_ncpo"), _T("gnd_ii_bs"), pData->m_nGNDIdx[1]);

	//	dValue_V[0] = dValue_V[1] = dValue_V[2] = -1;
	//	if (nBS_idx > 0)
	//	{
	//		dValue_V[0] = GETVALUE(double, _T("bs_dyn_rpfo"), _T("bs_parpfkv"), nBS_idx);
	//		dValue_V[1] = GETVALUE(double, _T("bs_dyn_rpfo"), _T("bs_pbrpfkv"), nBS_idx);
	//		dValue_V[2] = GETVALUE(double, _T("bs_dyn_rpfo"), _T("bs_pcrpfkv"), nBS_idx);

	//		if (dValue_V[0] > m_dMax_V)		m_dMax_V = dValue_V[0];
	//		if (dValue_V[1] > m_dMax_V)		m_dMax_V = dValue_V[1];
	//		if (dValue_V[2] > m_dMax_V)		m_dMax_V = dValue_V[2];

	//		if (dValue_V[0] < m_dMin_V)		m_dMin_V = dValue_V[0];
	//		if (dValue_V[1] < m_dMin_V)		m_dMin_V = dValue_V[1];
	//		if (dValue_V[2] < m_dMin_V)		m_dMin_V = dValue_V[2];
	//	}
	//}
}

void CView_LF_rst::Get_GraphData_RPF()
{
	CGraphData* pData;
	int nBS_idx[2] = { 0, 0 };
	CString strField, strField_mea;
	
	strField_mea = _T("cbsw_pameakv");
	strField = _T("bs_parpfpukv");
	
	m_ctrList[3].DeleteAllItems();

	double dH_value = 13.200*m_dVVM_lmhi;
	double dL_value = 13.200*m_dVVM_lmlo;

	CString strName,strValue;
	CString strLen,strIdx;

	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	{
		pData = m_Array_Graph.GetAt(i);

		nBS_idx[0] = GETVALUE(int, _T("gnd_dyn_ncpo"), _T("gnd_ii_bs"), pData->m_nGNDIdx[1]);

		if (pData->m_nGNDIdx[0] > 0)
			nBS_idx[1] = GETVALUE(int, _T("gnd_dyn_ncpo"), _T("gnd_ii_bs"), pData->m_nGNDIdx[0]);

		if (nBS_idx[0] > 0)
		{
			pData->m_dRPFO_value[1] = GETVALUE(double, _T("bs_dyn_rpfo"), (wchar_t*)strField.GetBuffer(), nBS_idx[0]) *13.2;

			strName = GETSTRING(_T("gnd_sta"), _T("gnd_nm"), pData->m_nGNDIdx[1]);
			strValue.Format(_T("%.1lf"), pData->m_dRPFO_value[1]);
			strLen.Format(_T("%.1lf"), pData->m_dLen[1]);
			strIdx.Format(_T("%d"), pData->m_nGNDIdx[1]);

			if (pData->m_dRPFO_value[1] > dH_value)
			{
				
				m_ctrList[3].InsertItem(m_ctrList[3].GetItemCount(), strName, RGB(255, 23, 23), RGB(255, 255, 255), HDF_LEFT);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 1, strValue, RGB(255, 23, 23), RGB(255, 255, 255));
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 2, strLen, RGB(255, 23, 23), RGB(255, 255, 255));
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 3, strIdx, RGB(255, 23, 23), RGB(255, 255, 255));
			}
			else if (pData->m_dRPFO_value[1] < dL_value)
			{
				m_ctrList[3].InsertItem(m_ctrList[3].GetItemCount(), strName, RGB(21, 114, 219), RGB(255, 255, 255), HDF_LEFT);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 1, strValue, RGB(21, 114, 219), RGB(255, 255, 255));
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 2, strLen, RGB(21, 114, 219), RGB(255, 255, 255));
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 3, strIdx, RGB(21, 114, 219), RGB(255, 255, 255));
			}
			else
			{
				m_ctrList[3].InsertItem(m_ctrList[3].GetItemCount(), strName, RGB(0, 0, 0), RGB(255, 255,255), HDF_LEFT);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 1, strValue, RGB(0, 0, 0), RGB(255, 255, 255));
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 2, strLen, RGB(0, 0, 0), RGB(255, 255, 255));
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 3, strIdx, RGB(0, 0, 0), RGB(255, 255, 255));
			}
		}

		if (nBS_idx[1] > 0)
		{
			pData->m_dRPFO_value[0] = GETVALUE(double, _T("bs_dyn_rpfo"), (wchar_t*)strField.GetBuffer(), nBS_idx[1]) *13.2;
		}

		
	}
/*
	int nCBSW_idx[2], nidx;
	double dValue;
	CGraph_info* pData_prev;

	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	{
		pData = m_Array_Graph.GetAt(i);

		nCBSW_idx[0] = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), pData->m_nNodeID);
		nCBSW_idx[1] = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), pData->m_nNodeID);

		if (nCBSW_idx[0] > 0)
		{
			nidx = nCBSW_idx[0];
		}
		else if (nCBSW_idx[1] > 0)
		{
			nidx = nCBSW_idx[1];
		}
		else
			continue;

		dValue = GETVALUE(double, _T("cbsw_dyn_mea"), strField_mea.GetBuffer(), nidx);

		pData->m_dCurrValue_mea = dValue;

	}
	int nNextID = 0, nPrevID, nPrevCount;
	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	{
		pData = m_Array_Graph.GetAt(i);

		if (pData->m_nNodeID_Prev <= 0 || pData->m_nType == 0)
			continue;

		nPrevID = pData->m_nNodeID_Prev;
		while (1)
		{
			dValue = Get_Prev_MeaData(nPrevID, &nNextID, &nPrevCount);
			if (dValue > 0 || nNextID == 0)
				break;

			nPrevID = nNextID;
		}

		pData->m_nPrev_idx = nPrevCount;
		pData->m_dPrevValue_mea = dValue;
	}*/
}

double CView_LF_rst::Get_Prev_MeaData(int nPrevID, int* nPrevID_next, int* nPrevCount_next)
{
	/*CGraph_info* pData;
	for (int k = 0; k < m_Array_Graph.GetSize(); k++)
	{
		pData = m_Array_Graph.GetAt(k);
		if (pData->m_nType == 0)
			continue;


		if (pData->m_nNodeID == nPrevID)
		{
			*nPrevCount_next = pData->m_nCount;
			*nPrevID_next = pData->m_nNodeID_Prev;
			return pData->m_dCurrValue_mea;
		}
	}
*/
	return 0.;
}

void CView_LF_rst::Get_ChartData_RPF()
{
	/*CString strPhase;
	if (wcscmp(m_strComboValue[2], _T("B상")) == 0)				strPhase = _T("b");
	else if (wcscmp(m_strComboValue[2], _T("C상")) == 0)		strPhase = _T("c");
	else																strPhase = _T("a");

	CGraph_info* pData;
	int nCBSW_idx[2], nidx;

	double dValue[5], dValueS[2];
	int nDirset(0), nDirflag(0);

	CString strName, strFieldName;

	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	{
		pData = m_Array_Graph.GetAt(i);

		strName = GETSTRING(_T("gnd_sta"), _T("gnd_nm"), pData->m_nNodeID);
		nCBSW_idx[0] = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), pData->m_nNodeID);
		nCBSW_idx[1] = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), pData->m_nNodeID);

		if (nCBSW_idx[0] > 0)
		{
			nidx = nCBSW_idx[0];
		}
		else if (nCBSW_idx[1] > 0)
		{
			nidx = nCBSW_idx[1];
		}
		else
			continue;

		strFieldName.Format(_T("cbsw_p%smeakv"), strPhase);
		dValue[0] = GETVALUE(double, _T("cbsw_dyn_mea"), strFieldName.GetBuffer(), nidx);

		strFieldName.Format(_T("cbsw_p%srpfkv"), strPhase);
		dValue[1] = GETVALUE(double, _T("cbsw_dyn_rpfo"), strFieldName.GetBuffer(), nidx);

		strFieldName.Format(_T("cbsw_p%smeaamp"), strPhase);
		dValueS[0] = GETVALUE(double, _T("cbsw_dyn_mea"), strFieldName.GetBuffer(), nidx);
		strFieldName.Format(_T("cbsw_p%smeaadiff"), strPhase);
		dValueS[1] = GETVALUE(double, _T("cbsw_dyn_mea"), strFieldName.GetBuffer(), nidx);

		dValue[2] = dValue[0] * dValueS[0] * cos(dValueS[1]) / (180 * 3.1426) * 1000;

		strFieldName.Format(_T("cbsw_p%srpfmw"), strPhase);
		dValue[3] = GETVALUE(double, _T("cbsw_dyn_rpfo"), strFieldName.GetBuffer(), nidx) * 1000;

		strFieldName.Format(_T("cbsw_dirset"));
		nDirset = GETVALUE(int, _T("cbsw_dyn_mea"), strFieldName.GetBuffer(), nidx);

		strFieldName.Format(_T("cbsw_dirinvflag"));
		nDirflag = GETVALUE(int, _T("cbsw_dyn_dleo"), strFieldName.GetBuffer(), nidx);

		strFieldName.Format(_T("cbsw_3prpfmw"));
		dValue[4] = GETVALUE(double, _T("cbsw_dyn_rpfo"), strFieldName.GetBuffer(), nidx) * 1000;

		pData->m_strName = strName;
		pData->m_dValue_mea_kV = dValue[0];
		pData->m_dValue_rpf_kV = dValue[1];
		pData->m_dValue_mea_kW = dValue[2];
		pData->m_dValue_rpf_kW = dValue[3];
		pData->m_nValue_dirset = nDirset;
		pData->m_nValue_dirflag = nDirflag;
		pData->m_dValue_rpf_3pkW = dValue[4];

		pData->m_nCBSW_idx = nidx;
	}

	UpdateData_RPF();*/
}

void CView_LF_rst::UpdateData_RPF()
{
	/*m_ctrList[0].DeleteAllItems();

	CGraph_info* pData;
	CString strValue[7], strCBSWIdx;
	int nCount = 0;
	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	{
		pData = m_Array_Graph.GetAt(i);

		if (pData->m_strName.IsEmpty() || pData->m_nType == 0)
			continue;

		strValue[0].Format(_T("%.3lf"), pData->m_dValue_mea_kV);
		strValue[1].Format(_T("%.3lf"), pData->m_dValue_rpf_kV);
		strValue[2].Format(_T("%.1lf"), pData->m_dValue_mea_kW);
		strValue[3].Format(_T("%.1lf"), pData->m_dValue_rpf_kW);

		if (pData->m_nValue_dirset == 1) strValue[4] = _T("Forward");
		else if (pData->m_nValue_dirset == 2) strValue[4] = _T("Reverse");
		else strValue[4].Empty();

		strValue[5].Format(_T("%s"), (pData->m_nValue_dirflag == 1 ? _T("V") : _T("")));
		strValue[6].Format(_T("%.1lf"), pData->m_dValue_rpf_3pkW);

		strCBSWIdx.Format(_T("%d"), pData->m_nCBSW_idx);

		m_ctrList[0].InsertItem(nCount, pData->m_strName, RGB(0,0,0), RGB(255,255,255), HDF_LEFT);
		m_ctrList[0].SetItemText(nCount, 1, strValue[0],  RGB(0,0,0), RGB(255,255,255));;
		m_ctrList[0].SetItemText(nCount, 2, strValue[1],  RGB(0,0,0), RGB(255,255,255));
		m_ctrList[0].SetItemText(nCount, 3, strValue[2],  RGB(0,0,0), RGB(255,255,255));
		m_ctrList[0].SetItemText(nCount, 4, strValue[3],  RGB(0,0,0), RGB(255,255,255));
		m_ctrList[0].SetItemText(nCount, 5, strValue[4],  RGB(0,0,0), RGB(255,255,255));
		m_ctrList[0].SetItemText(nCount, 6, strValue[5],  RGB(0,0,0), RGB(255,255,255));
		m_ctrList[0].SetItemText(nCount, 7, strValue[6],  RGB(0,0,0), RGB(255,255,255));
		m_ctrList[0].SetItemText(nCount, 8, strCBSWIdx,   RGB(0,0,0), RGB(255,255,255));

		nCount++;
	}*/
}

void CView_LF_rst::Graph_Data_Add(int nCount, int nPrevID, int nCurrID, BOOL bAdd)
{
	/*CGraph_info* pData = new CGraph_info();
	m_Array_Graph.Add(pData);
	pData->m_nCount = nCount;
	pData->m_nNodeID = nCurrID;
	pData->m_nNodeID_Prev = nPrevID;
	if (bAdd)
		pData->m_nType = 1;

	if (m_nNode_MaxCount < nCount + 1)
		m_nNode_MaxCount = nCount + 1;


	TRACE(_T("%d\t%d\n"), nPrevID, nCurrID);*/
}

void CView_LF_rst::Graph_Data_Clear()
{
	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	{
		delete m_Array_Graph.GetAt(i);
	}
	m_Array_Graph.RemoveAll();

	m_ptSelect.x = -1;
	m_ptSelect.y = -1;
}

void CView_LF_rst::Group_Data_Clear()
{
	/*for (int i = 0; i < m_Array_Graph_DLE.GetSize(); i++)
	{
		delete m_Array_Graph_DLE.GetAt(i);
	}
	m_Array_Graph_DLE.RemoveAll();*/
}

int CView_LF_rst::FindGroupCB(int nPreGBRIdx, int nGNDIdx)
{
	int																				nCount;
	nCount = theAppDataMng->GetTableRealCount(_T("gbr_sta"));
	m_pBRTrace2 = new BYTE[nCount];
	memset(m_pBRTrace2, 0x00, sizeof(BYTE) * nCount);

	int																				nNextGBRIdx, nRet;
	int																				nEq_Count = 0;
	//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)

	Graph_Data_Add(nEq_Count, -1, nGNDIdx);

	nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nGNDIdx);
	while (nNextGBRIdx)
	{
		if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (nPreGBRIdx != nNextGBRIdx))
		{
			nRet = FindGroupCBRcv(nNextGBRIdx, nGNDIdx, nEq_Count, nGNDIdx);
			if (nRet)
			{
				delete[] m_pBRTrace2;
				return nRet;
			}
		}
		nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGBRIdx);
	}

	//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
	nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nGNDIdx);
	while (nNextGBRIdx)
	{
		if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (nPreGBRIdx != nNextGBRIdx))
		{
			nRet = FindGroupCBRcv(nNextGBRIdx, nGNDIdx, nEq_Count, nGNDIdx);
			if (nRet)
			{
				delete[] m_pBRTrace2;
				return nRet;
			}
		}
		nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nNextGBRIdx);
	}

	delete[] m_pBRTrace2;
	return 0;
}

int CView_LF_rst::FindGroupCBRcv(int nGBRIdx, int nFGNDIdx, int nEq_Count, int nGraphND_Prev)
{
	////이미 지나갔던 구간이면 다시 안간다.
	if (m_pBRTrace2[nGBRIdx - 1])													return 0;

	//구간 Trace 체크
	m_pBRTrace2[nGBRIdx - 1] = TRUE;



	int																				nTGNDIdx, nNextGNDIdx, nNextGBRIdx, nRet;
	int		nPrev_ND = nGraphND_Prev;
	BOOL	bAdd = FALSE;


	//else if( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGBRIdx ) > 0 || GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGBRIdx ) > 0 )//t
	//{
	//	bAdd = FALSE;
	//}

	//구간의 다음 노드를 찾는다.
	if (GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nGBRIdx) == nFGNDIdx)	nTGNDIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_tgnd"), nGBRIdx);
	else																			nTGNDIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nGBRIdx);

	if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nTGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nTGNDIdx) > 0)//cbsw와 연결된 노드.
	{
		bAdd = TRUE;
	}

	if (GetGroupNDStatus(nTGNDIdx) == SW_OPEN)
	{
		if (nEq_Count > 0)
		{


			if (bAdd)
			{
				nEq_Count++;
				nPrev_ND = nTGNDIdx;
			}
			Graph_Data_Add(nEq_Count, nGraphND_Prev, nTGNDIdx, bAdd);
		}
		return 0;
	}

	//일반모드에서는 구간의 부하측노드가 없을경우 부하측에 가상노드를 하나만들고, 구간까지 생성한 후 종료.
	if (nTGNDIdx <= 0)
	{//축약모드에서는 구간의 부하측노드가 없으면 구간을 안만들고 끝(즉, 축약모드에서는 들어올 일 없음)
		return 0;
	}

	//CB를 찾았다.
	/*int																				nDlIdx;
	nDlIdx																			= GetGroupCbswToNode( nTGNDIdx );
	if( nDlIdx > 0 )																return nDlIdx;*/

	//nTNDIdx는 구간기준의 ToND -> 즉, 설비기준에서는 FND임
	//위에서 추가한 nTNDIdx 기준의 설비의 세부정보를 세팅하고, 설비기준에서의 TND(nNextNDIdx)로 변경.
	//DG, shunt, svc, Dummy등 토폴로지 기준 단일노드인 설비는 같은값이고, cbsw, tisw, svr 등은 설비기준 TND롤 변경
	//설비의 FND = 구간의 TND, 설비의 TND = 구간의 FND!!!!!!!!!!!!!!!!!!
	nNextGNDIdx = GetGroupToNDIdx(nTGNDIdx);

	if (bAdd)
	{
		nEq_Count++;
		nPrev_ND = nTGNDIdx;

	}
	Graph_Data_Add(nEq_Count, nGraphND_Prev, nTGNDIdx, bAdd);

	//설비의 부하측 노드와 연결된 cbsw(tisw포함)의 갯수를 체크한다.
	int																				nConnectCount;
	nConnectCount = CheckGroupConnectSw(nNextGNDIdx);

	//현재 설비(들어온쪽 설비)를 포함하여 2개이상 개폐기가 연결되어 있으면 멀티개폐기로 처리.
	//1개이하( 0:더미노드, gen, shunt...svr등, 1:단일개폐기) -> 어차피 동일로직이므로 뭐가되든 상관없다.
	//멀티개폐기 생성 및 토폴로지 진행을 위해 멀티를 구분하는 것임(다분기 더비는 br을 통해 진행하고, 멀티개폐기는 cbsw(tisw)를 통해 진행함) 
	if (nConnectCount >= 2) //다회로개폐기
	{
		//설비의 FND로 상태값을 확인
		//다회로의 전원측 설비가 OPEN이면 그만.
		if (GetGroupNDStatus(nTGNDIdx) == SW_OPEN)								return 0;

		//다회로 단자들을 찾아가면 생성한다.
		int																			nSubSwIdx, nSubGNDIdx;

		nSubSwIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nNextGNDIdx);
		while (nSubSwIdx)
		{
			nSubGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tgnd"), nSubSwIdx);
			if (nSubGNDIdx != nTGNDIdx)
			{
				//설비의 TND로 상태값을 확인
				if (GetSwStatus(nSubSwIdx) == SW_CLOSE)
				{
					//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace2[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(nNextGBRIdx, nSubGNDIdx, nEq_Count, nPrev_ND);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGBRIdx);
					}

					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace2[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(nNextGBRIdx, nSubGNDIdx, nEq_Count, nPrev_ND);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nNextGBRIdx);
					}
				}
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fgnd"), nSubSwIdx);
		}

		nSubSwIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nNextGNDIdx);
		while (nSubSwIdx)
		{
			nSubGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fgnd"), nSubSwIdx);
			if (nSubGNDIdx != nTGNDIdx)
			{
				//설비의 TND로 상태값을 확인
				if (GetSwStatus(nSubSwIdx) == SW_CLOSE)
				{
					//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace2[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(nNextGBRIdx, nSubGNDIdx, nEq_Count, nPrev_ND);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGBRIdx);
					}

					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace2[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(nNextGBRIdx, nSubGNDIdx, nEq_Count, nPrev_ND);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nNextGBRIdx);
					}
				}
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tgnd"), nSubSwIdx);
		}

		nSubSwIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nNextGNDIdx);
		while (nSubSwIdx)
		{
			nSubGNDIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_ii_tgnd"), nSubSwIdx);
			if (nSubGNDIdx != nTGNDIdx)
			{
				//설비의 TND로 상태값을 확인
				if (GetTieStatus(nSubSwIdx) == SW_CLOSE)
				{
					//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace2[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(nNextGBRIdx, nSubGNDIdx, nEq_Count, nPrev_ND);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGBRIdx);
					}

					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace2[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(nNextGBRIdx, nSubGNDIdx, nEq_Count, nPrev_ND);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nNextGBRIdx);
					}
				}
			}
			nSubSwIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_si_fgnd"), nSubSwIdx);
		}

		nSubSwIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nNextGNDIdx);
		while (nSubSwIdx)
		{
			nSubGNDIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_ii_fgnd"), nSubSwIdx);
			if (nSubGNDIdx != nTGNDIdx)
			{
				//설비의 TND로 상태값을 확인
				if (GetTieStatus(nSubSwIdx) == SW_CLOSE)
				{
					//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace2[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(nNextGBRIdx, nSubGNDIdx, nEq_Count, nPrev_ND);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGBRIdx);
					}

					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace2[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(nNextGBRIdx, nSubGNDIdx, nEq_Count, nPrev_ND);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nNextGBRIdx);
					}
				}
			}
			nSubSwIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_si_tgnd"), nSubSwIdx);
		}
	}
	else
	{
		//설비의 TND로 상태값을 확인
		//설비가 OPEN이면 그만.
		if (GetGroupNDStatus(nNextGNDIdx) == SW_OPEN)							return 0;

		//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nNextGNDIdx);
		while (nNextGBRIdx)
		{
			if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace2[nNextGBRIdx - 1] == FALSE))
			{
				nRet = FindGroupCBRcv(nNextGBRIdx, nNextGNDIdx, nEq_Count, nPrev_ND);
				if (nRet)															return nRet;
			}
			nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGBRIdx);
		}

		//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nNextGNDIdx);
		while (nNextGBRIdx)
		{
			if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace2[nNextGBRIdx - 1] == FALSE))
			{
				nRet = FindGroupCBRcv(nNextGBRIdx, nNextGNDIdx, nEq_Count, nPrev_ND);
				if (nRet)															return nRet;
			}
			nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nNextGBRIdx);
		}
	}

	return 0;
}

int	CView_LF_rst::GetGroupCbswToNode(int nGNDIdx)
{
	int																				nCbswIdx(0);
	if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx) > 0)//cbsw와 연결된 노드.
	{
		if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0)		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx);

		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCbswIdx) == 1)//CB이면
			return GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), nCbswIdx);
	}

	return -1;
}

int CView_LF_rst::CheckGroupConnectSw(int nGNDIdx)
{
	//하나의 노드의 from, to가 모두 스위치이면 --> 다회로의 가상더미임.
	//이전설비의 부하측노드(nNextNDIdx)가 또다른 switch와 연결되어 있다.(방향은 모르지만, 한쪽은 nNextNDIdx의 전원측 switch일꺼고, 다른쪽으로 switch가 또 있다?!)
	//이전설비가 switch가 아니라면 절대 안들어가겠지.
	//따라서 아래 조건을 만족하면 nNextNDIdx는 다회로의 가상더미임.
	int																		nConnectCnt(0), nSWIdx;

	nSWIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx);
	while (nSWIdx)
	{
		nConnectCnt++;
		nSWIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fgnd"), nSWIdx);
	}

	nSWIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx);
	while (nSWIdx)
	{
		nConnectCnt++;
		nSWIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tgnd"), nSWIdx);
	}

	nSWIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx);
	while (nSWIdx)
	{
		nConnectCnt++;
		nSWIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_si_fgnd"), nSWIdx);
	}

	nSWIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx);
	while (nSWIdx)
	{
		nConnectCnt++;
		nSWIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_si_tgnd"), nSWIdx);
	}

	return nConnectCnt;
}

int CView_LF_rst::GetGroupToNDIdx(int nGNDIdx)
{
	int																				nNextGNDIdx(-1);
	if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx) > 0)//cbsw와 연결된 노드.
	{
		int																			nCbswIdx;
		if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0)		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx);

		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fgnd"), nCbswIdx) == nGNDIdx)	nNextGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tgnd"), nCbswIdx);
		else																			nNextGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fgnd"), nCbswIdx);
	}
	else if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx) > 0)//tiesw와 연결된 노드.
	{
		int																			nCbswIdx;
		if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx) > 0)		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx);

		if (GETVALUE(int, _T("tisw_sta"), _T("tisw_ii_fgnd"), nCbswIdx) == nGNDIdx)	nNextGNDIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_ii_tgnd"), nCbswIdx);
		else																			nNextGNDIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_ii_fgnd"), nCbswIdx);
	}
	else//br이랑만 연결되어 있음 - Dummy 또는 SVR 임
	{
		int																			nSVRIdx = 0;
		int																			nGBRIdx;

		nGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nGNDIdx);
		while (nGBRIdx)
		{
			if (nGBRIdx && GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nGBRIdx) == 2)
			{
				nSVRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equ"), nGBRIdx);
				break;
			}

			nGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nGBRIdx);
		}

		if (nSVRIdx == 0)
		{
			nGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nGNDIdx);
			while (nGBRIdx)
			{
				if (nGBRIdx && GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nGBRIdx) == 2)
				{
					nSVRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equ"), nGBRIdx);
					break;
				}
				nGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nGBRIdx);
			}
		}

		if (nSVRIdx)//SVR
		{
			if (GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nGBRIdx) == nGNDIdx)	nNextGNDIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_tgnd"), nGBRIdx);
			else																		nNextGNDIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nGBRIdx);

			return nNextGNDIdx;
		}

		//BR속성의 설비가 아니면 그냥 자신
		nNextGNDIdx = nGNDIdx;
	}

	return nNextGNDIdx;
}

int CView_LF_rst::GetGroupNDStatus(int nGNDIdx)
{
	BOOL																			bStatus( TRUE);
	if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx) > 0)//cbsw와 연결된 노드.
	{
		int																			nCbswIdx;
		if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0)		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx);

		bStatus = GetSwStatus(nCbswIdx);
	}
	else if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx) > 0)//tiesw와 연결된 노드.
	{
		int																			nCbswIdx;
		if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx) > 0)		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx);

		bStatus = GetTieStatus(nCbswIdx);
	}
	else
	{
		bStatus = SW_CLOSE;
	}

	return bStatus;
}

int CView_LF_rst::GetSwStatus(int nCbswIdx)
{
	return  GETVALUE(int, _T("cbsw_dyn_mea"), _T("cbsw_nwstat"), nCbswIdx);
}

int CView_LF_rst::GetTieStatus(int nTiswIdx)
{
	return GETVALUE(int, _T("tisw_dyn_mea"), _T("tisw_nwstat"), nTiswIdx);
}

void CView_LF_rst::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CRect r = m_rectCtrl_TopLeft[2];

	//r.left		+= 54;
	//r.top		+= 20;
	//r.right		-= 154;
	//r.bottom	-= 28;

	///*r.InflateRect(-20, -20);
	//r.left += 30;*/

	//if (r.PtInRect(point))
	//{
	//	m_ptSelect = point;

	//	RedrawWindow();
	//}
	//else
	//{
	//	m_ptSelect.x = -1;
	//	m_ptSelect.y = -1;
	//	RedrawWindow();
	//}

	//if (m_rect_Graph_Check[0].PtInRect(point))
	//{
	//	m_bGraph_Check[0] = (m_bGraph_Check[0] == TRUE ? FALSE : TRUE);
	//	RedrawWindow();
	//}

	//if (m_rect_Graph_Check[1].PtInRect(point))
	//{
	//	m_bGraph_Check[1] = (m_bGraph_Check[1] == TRUE ? FALSE : TRUE);
	//	RedrawWindow();
	//}


	CView_Base::OnLButtonDown(nFlags, point);
}


void CView_LF_rst::OnListCtrlDBClick_1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;
	CString strIdx = m_ctrList[0].GetItemText(nRow, 3);

	
	int nND_idx = GETVALUE(int, _T("GEN_STA"), _T("GEN_II_ND"), _wtoi(strIdx));

	CString strSend;

	strSend.Format(_T("999,%d,단선도이동"), nND_idx);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Send_WndMsg(WNDMSG_PROGRAMID_SLD, WNDMSG_PROGRAMID_HMI, strSend);
	///*CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	//pFrm->SendWinMsg(99, strSend);*/ //////////////// 윈도우 전송 부분 처리해야된다.


	//CGraph_info* pData;

	//for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	//{
	//	pData = m_Array_Graph.GetAt(i);
	//	pData->m_nCheck = 0;
	//}
	//for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	//{
	//	pData = m_Array_Graph.GetAt(i);
	//	if (pData->m_nType == 0)
	//		continue;

	//	if (pData->m_nCBSW_idx == _wtoi(strIdx))
	//	{
	//		pData->m_nCheck = 1;
	//		break;
	//	}
	//}

	//RedrawWindow();

}

void CView_LF_rst::OnListCtrlDBClick_2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;
	CString strIdx = m_ctrList[1].GetItemText(nRow, 4);


	int nND_idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_TND"), _wtoi(strIdx));

	CString strSend;

	strSend.Format(_T("999,%d,단선도이동"), nND_idx);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Send_WndMsg(WNDMSG_PROGRAMID_SLD, WNDMSG_PROGRAMID_HMI, strSend);


}

void CView_LF_rst::OnListCtrlDBClick_3(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;
	CString strIdx = m_ctrList[2].GetItemText(nRow, 8);

	int nCBSW_Idx = _wtoi(strIdx);
	if (nCBSW_Idx <= 0)
		return;

	int nND_idx = GETVALUE(int, ("cbsw_sta"), ("cbsw_ii_tnd"), nCBSW_Idx);

	CString strSend;

	strSend.Format(_T("999,%d,단선도이동"), nND_idx);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Send_WndMsg(WNDMSG_PROGRAMID_SLD, WNDMSG_PROGRAMID_HMI, strSend);


}

void CView_LF_rst::OnListCtrlDBClick_4(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;
	CString strIdx = m_ctrList[3].GetItemText(nRow, 3);


	int nND_idx = _wtoi(strIdx);

	CString strSend;

	strSend.Format(_T("999,%d,단선도이동"), nND_idx);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Send_WndMsg(WNDMSG_PROGRAMID_SLD, WNDMSG_PROGRAMID_HMI, strSend);


}

void CView_LF_rst::Excute(int nDL_idx, int nRunMode)
{
	/*int nSel[5];
	nSel[1] = m_ctrCombo[2].GetCurSel();
	if (nSel[1] == -1)
	{
		AfxMessageBox(_T("선택된 년도가 없습니다."));
		return;
	}

	nSel[2] = m_ctrCombo[3].GetCurSel();
	if (nSel[2] <= 0)
	{
		AfxMessageBox(_T("선택된 월이 없습니다."));
		return;
	}

	nSel[3] = m_ctrCombo[4].GetCurSel();
	if (nSel[3] <= 0)
	{
		AfxMessageBox(_T("선택된 시각이 없습니다."));
		return;
	}

	nSel[4] = m_ctrCombo[5].GetCurSel();
	if (nSel[4] == -1)
	{
		AfxMessageBox(_T("선택된 부하유형이 없습니다."));
		return;
 
	/*CString strData[4];
	m_ctrCombo[2].GetLBText(nSel[1], strData[0]);
	m_ctrCombo[3].GetLBText(nSel[2], strData[1]);
	m_ctrCombo[4].GetLBText(nSel[3], strData[2]);*/

	int nSel = m_ctrCombo[2].GetCurSel();
	if (nSel < 0)
	{
		AfxMessageBox(_T("선택된 시각이 없습니다."));
		return;
	}

	
	COleDateTime timeData[1];
	CString strTime[1];
	m_ctrDate[0].GetTime(timeData[0]);
	//m_ctrDate[1].GetTime(timeData[1]);

	strTime[0].Format(_T("%s"), timeData[0].Format(_T("%Y%m%d")));

	int nDay = _wtoi(strTime[0]);
	int nHour = nSel;
	int nType = 3;
//	CString strTime = _T("20210721");
	if (nRunMode != 0)
		nType = 6;

	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_DL"), 1, (double)nDL_idx);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_SRTDAY"), 1, (double)nDay);
//	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_MONTH"), 1, (double)nMonth);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_SRTHR"), 1, (double)nHour);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_MODE"), 1, (double)nType);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("4"), GetVIewID());

	m_bTimer = TRUE;
	m_nCompAppl_ID = 4;
	SetTimer(1, 100, NULL);

	
}

void CView_LF_rst::OnControlbutton_click_Run()
{
	if (m_bTimer)
		return;

	CDataManager* pDataMng = CDataManager::Instance();

	int nSel;

	nSel = m_ctrCombo[1].GetCurSel();
	if (nSel == -1)
	{
		AfxMessageBox(_T("선택된 DL 없습니다."));
		return;
	}
	int nDL_idx = (int)m_ctrCombo[1].GetItemData(nSel);


	Excute(nDL_idx);

	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	
	/*UpdateData_Gen();
	UpdateData_Link();
	UpdateData_DLE();

	Graph_Data_Clear();
	pDataMng->GetData_Graph(nDL_idx, &m_Array_Graph);
	Get_GraphData_RPF();
	Get_TitleData_RPF();

	Get_TitleData_DLE();
	Get_ChartData_DLE();

	RedrawWindow();*/
}

void CView_LF_rst::OnControlbutton_click_Report()
{
	if (m_bTimer)
		return;

	CDataManager* pDataMng = CDataManager::Instance();

	int nSel;

	nSel = m_ctrCombo[1].GetCurSel();
	if (nSel == -1)
	{
		AfxMessageBox(_T("선택된 DL 없습니다."));
		return;
	}
	int nDL_idx = (int)m_ctrCombo[1].GetItemData(nSel);


	Excute(nDL_idx,1);

	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	/*UpdateData_Gen();
	UpdateData_Link();
	UpdateData_DLE();

	Graph_Data_Clear();
	pDataMng->GetData_Graph(nDL_idx, &m_Array_Graph);
	Get_GraphData_RPF();
	Get_TitleData_RPF();

	Get_TitleData_DLE();
	Get_ChartData_DLE();

	RedrawWindow();*/
}



void CView_LF_rst::UpdateData_Gen()
{
	m_ctrList[0].DeleteAllItems();
	int nSel = m_ctrCombo[1].GetCurSel();

	if (nSel == -1)
		return;

	int nDL_Idx = (int)m_ctrCombo[1].GetItemData(nSel);

	int nIJ_Idx, nIJ_si_dl,nEquty,nEqu;
	CString strName, strData[3];
	double dValue[2];


	nIJ_Idx = GETVALUE(int, ("dl_sta"), ("dl_hi_ij"), nDL_Idx);
	if (nIJ_Idx == 0)
		return;

	while (1)
	{
		nEquty = GETVALUE(int, ("ij_sta"), ("ij_ii_equty"), nIJ_Idx);
		nIJ_si_dl = GETVALUE(int, ("ij_sta"), ("ij_si_dl"), nIJ_Idx);
		if (nEquty != 4)
		{
			if (nIJ_si_dl == 0)
				break;

			nIJ_Idx = nIJ_si_dl;
			continue;
		}
		
		strName = CA2W(GETSTRING("ij_sta", "ij_nm", nIJ_Idx)).m_psz;

		nEqu = GETVALUE(int, ("ij_sta"), ("ij_ii_equ"), nIJ_Idx);

		dValue[0] = GETVALUE(double, ("gen_sta"), ("gen_mwlmmx"), nEqu);
		dValue[1] = GETVALUE(double, ("ij_dyn_mea"), ("ij_3pmeamw"), nIJ_Idx);
		

		strData[0].Format(_T("%.1lf"), dValue[0] * 1000);
		strData[1].Format(_T("%.1lf"), dValue[1] * 1000);
		strData[2].Format(_T("%d"), nEqu);

		m_ctrList[0].InsertItem(m_ctrList[0].GetItemCount(), strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 1, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 2, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 3, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);


		if(nIJ_si_dl == 0)
			break;

		nIJ_Idx = nIJ_si_dl;
	}
}

void CView_LF_rst::UpdateData_Link()
{
	m_ctrList[2].DeleteAllItems();
	int nCount = theAppDataMng->GetTableMaxCount(_T("stdle_dyn_stdleo"));

	CString strData[9];
	int nIdx[3];
	double dValue[5];

	for (int i = 1; i <= nCount; i++)
	{
		nIdx[0] = GETVALUE(int, ("stdle_dyn_stdleo"), ("stdle_ss"), i);
		if(nIdx[0] == 0)
			break;

		nIdx[1] = GETVALUE(int, ("stdle_dyn_stdleo"), ("stdle_dl"), i);
		nIdx[2] = GETVALUE(int, ("stdle_dyn_stdleo"), ("stdle_cbsw"), i);

		dValue[0] = GETVALUE(double, ("stdle_dyn_stdleo"), ("stdle_gload"), i);
		dValue[1] = GETVALUE(double, ("stdle_dyn_stdleo"), ("stdle_gen_ratesum"), i);
		dValue[2] = GETVALUE(double, ("stdle_dyn_stdleo"), ("stdle_gen"), i);
		dValue[3] = GETVALUE(double, ("stdle_dyn_stdleo"), ("stdle_net"), i);
		dValue[4] = GETVALUE(double, ("stdle_dyn_stdleo"), ("stdle_net_amp"), i);

		strData[0] = CA2W(GETSTRING("ss_sta", "ss_nm", nIdx[0])).m_psz;
		strData[1] = CA2W(GETSTRING("dl_sta", "dl_nm", nIdx[1])).m_psz;
		strData[2] = CA2W(GETSTRING("cbsw_sta", "cbsw_nm", nIdx[2])).m_psz;
		strData[3].Format(_T("%.1lf"), dValue[0] * 1000);
		strData[4].Format(_T("%.1lf"), dValue[1] * 1000);
		strData[5].Format(_T("%.1lf"), dValue[2] * 1000);
		strData[6].Format(_T("%.1lf"), dValue[3] * 1000);
		strData[7].Format(_T("%.1lf"), dValue[4] * 1000);
		strData[8].Format(_T("%d"), nIdx[2]);

		m_ctrList[2].InsertItem(m_ctrList[2].GetItemCount(), strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 2, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 3, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 4, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 5, strData[5], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 6, strData[6], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 7, strData[7], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 8, strData[8], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);



	}

}

void CView_LF_rst::recv_Appl(int nAppl)
{
	if (!m_bTimer)
		return;

	m_nRecvAppl_ID = nAppl;

	if (m_nCompAppl_ID == nAppl)
	{
		m_bTimer = FALSE;
	}
}

void CView_LF_rst::recv_Init()
{
	m_bTimer = FALSE;
	KillTimer(1);
}

void CView_LF_rst::OnTimer(UINT_PTR nIDEvent)
{
	if (!m_bTimer)
	{
		
		if (nIDEvent == 1)
		{
			KillTimer(nIDEvent);
			Sleep(500);
		
			UpdateData_Gen();
			UpdateData_Link();
			UpdateData_DLE();
			Get_TitleData_DLE();


			int nSel = m_ctrCombo[1].GetCurSel();

			if (nSel == -1)
				return;
			int nDL_idx = (int)m_ctrCombo[1].GetItemData(nSel);


			CDataManager* pDataMng = CDataManager::Instance();
			Graph_Data_Clear();
			pDataMng->GetData_Graph(nDL_idx, &m_Array_Graph);
			Get_GraphData_RPF();
			Get_TitleData_RPF();

		//	Get_TitleData_DLE();
		//	Get_ChartData_DLE();
			
		}
	
		//Redraw_Ctrl();
		RedrawWindow();
		
	}
	if (nIDEvent == 1111)
	{
	//	KillTimer(1111);
		Redraw_Ctrl();
	}


	CView_Base::OnTimer(nIDEvent);
}


void CView_LF_rst::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Redraw_Ctrl();
	CView_Base::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CView_LF_rst::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CView_Base::OnSettingChange(uFlags, lpszSection);

	//Redraw_Ctrl();
}


void CView_LF_rst::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CView_Base::OnWindowPosChanged(lpwndpos);

	Redraw_Ctrl();
}
