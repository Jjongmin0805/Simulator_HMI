#include "pch.h"
#include "CView_NCP_rst.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"
#include "../DataManager/CDataManager.h"
#include "resource.h"

CView_NCP_rst::CView_NCP_rst()
{
	m_bTimer = FALSE;

	m_nCompAppl_ID = -1;
	m_nRecvAppl_ID = -1;
}

CView_NCP_rst::~CView_NCP_rst()
{

}

BEGIN_MESSAGE_MAP(CView_NCP_rst, CView_Base)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(ID_APP_NCP_COMBO_1, &CView_NCP_rst::On_NCP_rst_Combo1SelectChange)
	ON_CBN_SELCHANGE(ID_APP_NCP_COMBO_2, &CView_NCP_rst::On_NCP_rst_Combo2SelectChange)
	ON_CBN_SELCHANGE(ID_APP_NCP_COMBO_3, &CView_NCP_rst::On_NCP_rst_Combo3SelectChange)
	ON_CBN_SELCHANGE(ID_APP_NCP_COMBO_4, &CView_NCP_rst::On_NCP_rst_Combo4SelectChange)
	ON_CBN_SELCHANGE(ID_APP_NCP_COMBO_5, &CView_NCP_rst::On_NCP_rst_Combo5SelectChange)
	ON_BN_CLICKED(ID_APP_NCP_BTN_1, &CView_NCP_rst::On_NCP_rst_Btn1Click_Run)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CView_NCP_rst::InitData()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CStringArray Array_SS;
	CIntArray	Array_SS_idx;

	pDataMng->GetSSName_array(&Array_SS, &Array_SS_idx);

	m_ctrCombo[0].ResetContent();
	m_ctrCombo[1].ResetContent();
	m_ctrCombo[2].ResetContent();
	m_ctrCombo[3].ResetContent();
	m_ctrCombo[4].ResetContent();

	for (int i = 0; i < Array_SS.GetSize(); i++)
	{
		m_ctrCombo[0].AddString(Array_SS.GetAt(i));
		m_ctrCombo[0].SetItemData(i, (DWORD_PTR)Array_SS_idx.GetAt(i));
	}

	CString strCBSWType[10] = { _T("전체"),_T("CB"), _T("리클로져"), _T("통신리클러져"), _T("개폐기"), _T("통신개폐기")
							, _T("차단기"), _T("통신차단기"), _T("FUSE"), _T("COS") };

	for (int i = 0; i < 10; i++)
	{
		m_ctrCombo[2].AddString(strCBSWType[i]);
	}

	CString strEquipType[6] = { _T("전체"),_T("Line"), _T("TR"), _T("GEN"), _T("Shunt"), _T("SVC") };

	for (int i = 0; i < 6; i++)
	{
		m_ctrCombo[3].AddString(strEquipType[i]);
	}

	m_ctrCombo[4].AddString(_T("전체")) ;
	m_ctrCombo[4].AddString(_T("유효")) ;

	m_ctrCombo[2].SetCurSel(0);
	m_ctrCombo[3].SetCurSel(0);
	m_ctrCombo[4].SetCurSel(0);

}

void CView_NCP_rst::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	Create_Btn();
	Create_Combobox();
	Create_ListCtrl();
}


void CView_NCP_rst::OnDraw(CDC* pDC)
{	
	//CClientDC dc(this);

	OnPrepareDC(pDC);
	
	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);


	m_ctrCombo[0].RedrawWindow();
	m_ctrCombo[1].RedrawWindow();
	m_ctrCombo[2].RedrawWindow();
	m_ctrCombo[3].RedrawWindow();
	m_ctrCombo[4].RedrawWindow();

}



BOOL CView_NCP_rst::OnEraseBkgnd(CDC* pDC)
{
	CView_Base::OnEraseBkgnd(pDC);

	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();


	pViewMng->DrawArea_Base(pDC, graphics, m_rectBack[0]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[1]);

	pViewMng->Draw_Split(pDC, graphics, m_rectSetting[0], DRAW_SPLIT_MODE_BOTTOM);

	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[0]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[1]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[2]);

	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[0], _T("자동화기기"), TRUE);
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[1], _T("비가압설비"), TRUE);
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[2], _T("독립계통/모선"), TRUE);

	return TRUE;
}


void CView_NCP_rst::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	int nWidth = _rect.Width() / 5 * 3;
	m_rectBack[0].SetRect(_rect.left, _rect.top, _rect.left + nWidth, _rect.bottom);
	m_rectBack[1].SetRect(m_rectBack[0].right + 10, _rect.top, _rect.right, _rect.bottom);

	MoveSize_List_1();
	MoveSize_List_2();
}


void CView_NCP_rst::MoveSize_List_1()
{
	if (m_ctrList[2].GetSafeHwnd() == NULL || m_ctrBtn[0].GetSafeHwnd() == NULL)							return;

	/////////////////////////////////////////////타이틀  
	int nHeight = (m_rectBack[0].Height() - 51) / 2;
	m_rectSetting[0] = m_rectBack[0];
	m_rectSetting[0].bottom = m_rectSetting[0].top + 51;

	m_rectCtrl_List[0] = m_rectBack[0];
	m_rectCtrl_List[0].top = m_rectSetting[0].bottom;
	m_rectCtrl_List[0].bottom = m_rectCtrl_List[0].top + nHeight;

	m_rectCtrl_List[1] = m_rectBack[0];
	m_rectCtrl_List[1].top = m_rectCtrl_List[0].bottom;

	m_rectTitle[0] = m_rectCtrl_List[0];
	m_rectTitle[0].right = m_rectTitle[0].left + 100;
	m_rectTitle[0].bottom = m_rectTitle[0].top + 30;

	m_rectTitle[1] = m_rectCtrl_List[1];
	m_rectTitle[1].right = m_rectTitle[1].left + 100;
	m_rectTitle[1].bottom = m_rectTitle[1].top + 30;

	////////////////////////////////////////////////////////////
	m_rectCtrl_Combobox[0] = m_rectSetting[0];
	m_rectCtrl_Combobox[0].InflateRect(-8, -10);
//	m_rectCtrl_Combobox[0].left = m_rectCtrl_Combobox[0].left ;
	m_rectCtrl_Combobox[0].right = m_rectCtrl_Combobox[0].left + 178;
	m_rectCtrl_Combobox[0].bottom = m_rectCtrl_Combobox[0].top + 24;

	m_rectCtrl_Combobox[1] = m_rectCtrl_Combobox[0];
	m_rectCtrl_Combobox[1].left = m_rectCtrl_Combobox[0].right + 8;
	m_rectCtrl_Combobox[1].right = m_rectCtrl_Combobox[1].left + 178;
	m_rectCtrl_Combobox[1].bottom = m_rectCtrl_Combobox[1].top + 24;

	m_rectCtrl_Combobox[2] = m_rectTitle[0];
	m_rectCtrl_Combobox[2].left = m_rectTitle[0].right + 10 ;
	m_rectCtrl_Combobox[2].right = m_rectCtrl_Combobox[2].left + 178;
	m_rectCtrl_Combobox[2].top  = m_rectCtrl_Combobox[2].top + 3;
	m_rectCtrl_Combobox[2].bottom = m_rectCtrl_Combobox[2].top + 24;

	m_rectCtrl_Combobox[3] = m_rectTitle[1];
	m_rectCtrl_Combobox[3].left = m_rectTitle[1].right + 10;
	m_rectCtrl_Combobox[3].right = m_rectCtrl_Combobox[3].left + 178;
	m_rectCtrl_Combobox[3].top = m_rectCtrl_Combobox[3].top + 3;
	m_rectCtrl_Combobox[3].bottom = m_rectCtrl_Combobox[3].top + 24;


	m_ctrCombo[0].MoveWindow(m_rectCtrl_Combobox[0]);
	m_ctrCombo[1].MoveWindow(m_rectCtrl_Combobox[1]);
	m_ctrCombo[2].MoveWindow(m_rectCtrl_Combobox[2]);
	m_ctrCombo[3].MoveWindow(m_rectCtrl_Combobox[3]);
	//////////////////////////////////////////////////////////////
	m_rectCtrl_Btn[0] = m_rectSetting[0];
	m_rectCtrl_Btn[0].InflateRect(-8, -10);
	m_rectCtrl_Btn[0].left = m_rectCtrl_Btn[0].right - 87;
	m_rectCtrl_Btn[0].bottom = m_rectCtrl_Btn[0].top + 33;

	m_ctrBtn[0].MoveWindow(m_rectCtrl_Btn[0]);
	//////////

	CRect rectList;

	rectList = m_rectCtrl_List[0];
	rectList.top += 30;
	m_ctrList[0].MoveWindow(rectList);

	rectList = m_rectCtrl_List[1];
	rectList.top += 30;
	rectList.bottom -= 2;
	m_ctrList[1].MoveWindow(rectList);

}

void CView_NCP_rst::MoveSize_List_2()
{
	if (m_ctrList[2].GetSafeHwnd() == NULL )							return;

	m_rectCtrl_List[2] = m_rectBack[1];
	
	m_rectTitle[2] = m_rectCtrl_List[2];
	m_rectTitle[2].right = m_rectTitle[2].left + 130;
	m_rectTitle[2].bottom = m_rectTitle[2].top + 30;

	m_rectCtrl_Combobox[4] = m_rectTitle[2];
	m_rectCtrl_Combobox[4].left = m_rectTitle[2].right + 10;
	m_rectCtrl_Combobox[4].right = m_rectCtrl_Combobox[4].left + 178;
	m_rectCtrl_Combobox[4].top = m_rectCtrl_Combobox[4].top + 3;
	m_rectCtrl_Combobox[4].bottom = m_rectCtrl_Combobox[4].top + 24;

	m_ctrCombo[4].MoveWindow(m_rectCtrl_Combobox[4]);


	CRect rectList;

	rectList = m_rectCtrl_List[2];
	rectList.top += 30;
	rectList.bottom -= 2;
	m_ctrList[2].MoveWindow(rectList);
}


void CView_NCP_rst::Create_ListCtrl()
{
	m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect[2];
	rect[0] = CRect(10, 50, 350, 500);
	m_ctrList[0].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER | LVS_SHOWSELALWAYS, rect[0], this, ID_APP_NCP_LIST_1);
	m_ctrList[0].InsertColumn(0, _T("Index"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(1, _T("변전소"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(2, _T("DL"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(3, _T("설비명"), HDF_LEFT, 366);
	m_ctrList[0].InsertColumn(4, _T("종류"), HDF_LEFT, 150);
	m_ctrList[0].InsertColumn(5, _T("상태"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(6, _T("공청KV"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(7, _T("자/수동"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(8, _T("idx"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(9, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
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

	m_ctrList[0].SetCheckBox_Bitmap(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	rect[1] = CRect(10, 50, 350, 500);
	m_ctrList[1].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_NCP_LIST_2);
	m_ctrList[1].InsertColumn(0, _T("Index"), HDF_LEFT, 100);
	m_ctrList[1].InsertColumn(1, _T("변전소"), HDF_LEFT, 100);
	m_ctrList[1].InsertColumn(2, _T("DL"), HDF_LEFT, 100);
	m_ctrList[1].InsertColumn(3, _T("설비명"), HDF_LEFT, 366);
	m_ctrList[1].InsertColumn(4, _T("종류"), HDF_LEFT, 150);
	m_ctrList[1].InsertColumn(5, _T("BR/IJ idx"), HDF_LEFT, 100);
	m_ctrList[1].InsertColumn(6, _T("Log Time"), HDF_LEFT, 150);
	m_ctrList[1].InsertColumn(7, _T("idx"), HDF_LEFT, 0);
	m_ctrList[1].InsertColumn(8, _T("dump"), HDF_LEFT, 0);
	m_ctrList[1].ShowWindow(SW_SHOW);
	m_ctrList[1].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SINGLEROW);
	m_ctrList[1].m_HeaderCtrl.SetHeight(27);
	m_ctrList[1].m_HeaderCtrl.SetFlat();
	m_ctrList[1].m_HeaderCtrl.SetFlat();
	m_ctrList[1].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[1].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[1].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[1].SetBgColor(RGB(255, 255, 255));
	m_ctrList[1].SetUnderLine();
	m_ctrList[1].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[1].SetTextFont(&m_listfont);
	m_ctrList[1].SetRowHeight(25);
	m_ctrList[1].SetCheckBox_Bitmap(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	
	////////////////////////////////////////////            PDVR
	m_ctrList[2].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_NCP_LIST_3);
	m_ctrList[2].InsertColumn(0, _T("Index"), HDF_LEFT, 80);
	m_ctrList[2].InsertColumn(1, _T("기준모선"), HDF_LEFT, 80);
	m_ctrList[2].InsertColumn(2, _T("변전소"), HDF_LEFT, 200);
	m_ctrList[2].InsertColumn(3, _T("DL"), HDF_LEFT, 180);
	m_ctrList[2].InsertColumn(4, _T("유효/무효"), HDF_LEFT, 80);
	m_ctrList[2].InsertColumn(5, _T("시작모선"), HDF_LEFT, 80);
	m_ctrList[2].InsertColumn(6, _T("idx"), HDF_LEFT, 0);
	m_ctrList[2].InsertColumn(7, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
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
	m_ctrList[2].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[2].SetTextFont(&m_listfont);
	m_ctrList[2].SetRowHeight(25);

	//m_ctrList[2].ShowWindow(SW_HIDE);
}

void CView_NCP_rst::Create_Combobox()
{
	m_font_Combobox.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	if (!m_ctrCombo[0].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_NCP_COMBO_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}
	if (!m_ctrCombo[1].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_SORT
		, CRect(100, 100, 200, 200), this, ID_APP_NCP_COMBO_2))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[2].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_NCP_COMBO_3))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}
	if (!m_ctrCombo[3].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWN | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_NCP_COMBO_4))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[4].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWN | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_NCP_COMBO_5))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}


	m_ctrCombo[0].SetTextFont(&m_font_Combobox);
	m_ctrCombo[1].SetTextFont(&m_font_Combobox);
	m_ctrCombo[2].SetTextFont(&m_font_Combobox);
	m_ctrCombo[3].SetTextFont(&m_font_Combobox);
	m_ctrCombo[4].SetTextFont(&m_font_Combobox);

	m_ctrCombo[0].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[1].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[2].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[3].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[4].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));

	m_ctrCombo[0].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[1].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[2].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[3].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[4].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);

	m_ctrCombo[0].SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[1].SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[2].SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[3].SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[4].SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);


	m_ctrCombo[0].SetDropDownHeight(10);
	m_ctrCombo[1].SetDropDownHeight(10);
	m_ctrCombo[2].SetDropDownHeight(10);
	m_ctrCombo[3].SetDropDownHeight(10);
	m_ctrCombo[4].SetDropDownHeight(10);



	//m_ctrCombo[4].ShowWindow(SW_HIDE);
}

void CView_NCP_rst::Create_Btn()
{
	m_rectCtrl_Btn[0] = CRect(10, 20, 90, 250);
	if (!m_ctrBtn[0].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_rectCtrl_Btn[0], this, ID_APP_NCP_BTN_1))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_ctrBtn[0].SetBitmapID(IDB_PCE_RUN_NOR, IDB_PCE_RUN_CLK, IDB_PCE_RUN_OVR);
}

void CView_NCP_rst::On_NCP_rst_Combo1SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	m_ctrCombo[1].ResetContent();

	CString	strSS;
	CStringArray Array_DL;
	CIntArray	Array_DL_Idx;
	m_ctrCombo[0].GetLBText(nSel, strSS);

	CDataManager* pDataMng = CDataManager::Instance();

	pDataMng->GetDLName_array(strSS, &Array_DL, _T(""),&Array_DL_Idx);

	for (int i = 0; i < Array_DL.GetSize(); i++)
	{
		m_ctrCombo[1].AddString(Array_DL.GetAt(i));
	}

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

	///////////////////// List update
//	Update_List_1();
//	Update_List_2();
}

void CView_NCP_rst::On_NCP_rst_Combo2SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	Update_List_1();
	Update_List_2();
}

void CView_NCP_rst::On_NCP_rst_Combo3SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	Update_List_1();
}

void CView_NCP_rst::On_NCP_rst_Combo4SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;
}

void CView_NCP_rst::On_NCP_rst_Combo5SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	Update_List_3();
}

void CView_NCP_rst::Update_List_1()
{
	
	m_ctrList[0].DeleteAllItems();

	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	BeginWaitCursor();

	int nSS_idx, nDL_idx = -1;
	nSS_idx = (int)m_ctrCombo[0].GetItemData(nSel);

	nSel = m_ctrCombo[1].GetCurSel();
	if (nSel != -1)
	{
		nDL_idx = (int)m_ctrCombo[1].GetItemData(nSel);
	}
		
	int nType = m_ctrCombo[2].GetCurSel();

	int							i(0), j(0), nCount(0);
	int							nCBSWdlIDX(0), nDLmtrIDX(0), nMTRssIDX(0);
	int							nCBSWType;
	TCHAR						szContext[64] = { 0 };
	wstring						szSSName(_T(""));
	CString strCBSWType[10] = { _T("전체"),_T("CB"), _T("리클로져"), _T("통신리클러져"), _T("개폐기"), _T("통신개폐기")
							, _T("차단기"), _T("통신차단기"), _T("FUSE"), _T("COS") };

	int nListCount = 0;
	nCount = theAppDataMng->GetTableRealCount(_T("cbsw_sta"));
	for (i = 1; i <= (int)nCount ; i++)
	{
		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), i) == 0)											continue;

		nCBSWdlIDX = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), i);
		if (nCBSWdlIDX < 1)
		{
			continue;
		}

		nDLmtrIDX = GETVALUE(int, _T("dl_sta"), _T("dl_ii_mtr"), nCBSWdlIDX);
		if (nDLmtrIDX < 1)
		{
			continue;
		}

		nMTRssIDX = GETVALUE(int, _T("mtr_sta"), _T("mtr_ii_ss"), nDLmtrIDX);
		if (nMTRssIDX < 1)
		{
			continue;
		}

		szSSName = GETSTRING(_T("ss_sta"), _T("ss_nm"), nMTRssIDX);
		if (szSSName == _T(""))
		{
			continue;
		}

		nCBSWType = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), i);
		if(nCBSWType > 9)
			continue;
		//if (nType != 0) ////////////// 계통 전체 확인
		{
			//if (m_3rd_Combo1Value != szSSName)																	continue;
			if (nDL_idx != -1)
			{
				if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), i) == 0)									continue;
				if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), i) != nDL_idx)						continue;
			}

			if (nType != 0)
			{
				if (nType != nCBSWType)			continue;
			}
		}

		nListCount = m_ctrList[0].GetItemCount();
		m_ctrList[0].InsertItem(nListCount, _T(""), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
		swprintf(szContext, _T("%d"), nCount + 1);
		m_ctrList[0].SetItemText(nListCount, 0, szContext, RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
		m_ctrList[0].SetItemText(nListCount, 1, szSSName.c_str(), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), i) > 0)
			m_ctrList[0].SetItemText(nListCount, 2, GETSTRING(_T("dl_sta"), _T("dl_nm"), nCBSWdlIDX), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
		else
			m_ctrList[0].SetItemText(nListCount, 2, _T("Not Matched"));
		m_ctrList[0].SetItemText(nListCount, 3, GETSTRING(_T("cbsw_sta"), _T("cbsw_nm"), i), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
		swprintf(szContext, _T("%s"), strCBSWType[nCBSWType]);
		m_ctrList[0].SetItemText(nListCount, 4, szContext, RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);

		if (GETVALUE(int, _T("CBSW_DYN_MEA"), _T("cbsw_nwstat"), i) == 1)			
			m_ctrList[0].SetItemText(nListCount, 5, _T("닫힘"), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
		else										
			m_ctrList[0].SetItemText(nListCount, 5, _T("열림"), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);


		m_ctrList[0].SetItemText(nListCount, 6, szSSName.c_str(), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
		/*switch (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), i))
		{
		case 1:
		case 2:
		case 3: { swprintf(szContext, _T("%s"), PNOLOADSTRING(_T("NCPWnd"), 40)); };	break;
		case 4:
		case 5:
		case 6: { swprintf(szContext, _T("%s"), PNOLOADSTRING(_T("NCPWnd"), 41)); };	break;
		}*/
		if(nCBSWType == 3	|| nCBSWType == 5	|| nCBSWType == 7)
			m_ctrList[0].SetItemText(nListCount, 7, _T("자동"), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
		else if (nCBSWType != 1)
			m_ctrList[0].SetItemText(nListCount, 7, _T("수동"), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);

	}

	EndWaitCursor();
}

void CView_NCP_rst::Update_List_2()
{
	BeginWaitCursor();
	m_ctrList[1].DeleteAllItems();

	EndWaitCursor();
}

void CView_NCP_rst::Update_List_3()
{
	BeginWaitCursor();
	m_ctrList[2].DeleteAllItems();
	
	int nType = m_ctrCombo[4].GetCurSel();


	int							i(0), j(0), nCount(0);
	TCHAR						szContext[64] = { 0 };

	int nListCount = 0;
	nCount = theAppDataMng->GetTableRealCount(_T("isl_dyn_ncpo"));
	for (i = 1; i <= (int)nCount ; i++)
	{
		if (GETVALUE(int, _T("isl_dyn_ncpo"), _T("isl_hi_bs"), i) == 0)								continue;

		if (nType == 1)
		{
			if (GETVALUE(int, _T("isl_dyn_ncpo"), _T("isl_effisl"), i) != 1)
			{
				continue;
			}
		}
		nListCount = m_ctrList[2].GetItemCount();
		m_ctrList[2].InsertItem(nListCount,_T(""), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
	//	list.Lst_InsertItem(nCount, _T(""));
		for (j = 0; j < 6; j++)
		{
			switch (j)
			{
			case 0: {
				swprintf(szContext, _T("%d"), GETVALUE(int, _T("isl_dyn_ncpo"), _T("isl_islno"), i));
				m_ctrList[2].SetItemText(nListCount, j, szContext, RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
			};	break;
			case 1: {
				swprintf(szContext, _T("%d"), GETVALUE(int, _T("isl_dyn_ncpo"), _T("isl_ii_slcbs"), i));
				m_ctrList[2].SetItemText(nListCount, j, szContext, RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
			};	break;
			case 2: {
				swprintf(szContext, _T("%s"), GETSTRING(_T("isl_dyn_ncpo"), _T("isl_slcbsst"), i));
				m_ctrList[2].SetItemText(nListCount, j, szContext, RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
			};	break;
			case 3: {
				swprintf(szContext, _T("%s"), GETSTRING(_T("isl_dyn_ncpo"), _T("isl_slcbsdl"), i));
				m_ctrList[2].SetItemText(nListCount, j, szContext, RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
			};	break;
			case 4: {
				if (GETVALUE(int, _T("isl_dyn_ncpo"), _T("isl_effisl"), i) == 1)
					m_ctrList[2].SetItemText(nListCount, j, _T("유효"), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
				else
					m_ctrList[2].SetItemText(nListCount, j, _T("무효"), RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
			};	break;
			case 5: {
				swprintf(szContext, _T("%d"), GETVALUE(int, _T("isl_dyn_ncpo"), _T("isl_hi_bs"), i));
				m_ctrList[2].SetItemText(nListCount, j, szContext, RGB(54, 55, 59), RGB(247, 247, 247), HDF_LEFT);
			};	break;
			}
		}
		//nCount += 1;
	}

	EndWaitCursor();
}

void CView_NCP_rst::On_NCP_rst_Btn1Click_Run()
{
	if (m_bTimer)
		return;

	BeginWaitCursor();
	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("1"), GetVIewID());

	m_bTimer = TRUE;
	m_nCompAppl_ID = 1;
	SetTimer(1, 100, NULL);

	
}

void CView_NCP_rst::recv_Appl(int nAppl)
{
	if (!m_bTimer)
		return;
	EndWaitCursor();
	m_nRecvAppl_ID = nAppl;

	if (m_nCompAppl_ID == nAppl)
	{
		m_bTimer = FALSE;
	}
}

void CView_NCP_rst::recv_Init()
{
	m_bTimer = FALSE;
	KillTimer(1);
}

void CView_NCP_rst::OnTimer(UINT_PTR nIDEvent)
{
	if (!m_bTimer)
	{
		KillTimer(nIDEvent);
		if (nIDEvent == 1)
		{
			Sleep(500);

			Update_List_1();
			Update_List_2();
			Update_List_3();


		}
	}

	CView_Base::OnTimer(nIDEvent);
}
