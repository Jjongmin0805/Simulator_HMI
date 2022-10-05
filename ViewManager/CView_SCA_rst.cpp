#include "pch.h"
#include "CView_SCA_rst.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"
#include "../DataManager/CDataManager.h"
#include "resource.h"

CView_SCA_rst::CView_SCA_rst()
{
	m_nSelect_SS_GEN = -1;
	m_nSelect_TR = -1;
}

CView_SCA_rst::~CView_SCA_rst()
{

}

BEGIN_MESSAGE_MAP(CView_SCA_rst, CView_Base)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(ID_APP_SCA_BTN_RADIO_1, &CView_SCA_rst::OnControlbutton_click_Radio1)
	ON_BN_CLICKED(ID_APP_SCA_BTN_RADIO_2, &CView_SCA_rst::OnControlbutton_click_Radio2)
	ON_CBN_SELCHANGE(ID_APP_SCA_COMBO_1, &CView_SCA_rst::OnSCA_rstCombo1SelectChange)
	ON_CBN_SELCHANGE(ID_APP_SCA_COMBO_2, &CView_SCA_rst::OnSCA_rstCombo2SelectChange)
	ON_CBN_SELCHANGE(ID_APP_SCA_COMBO_4, &CView_SCA_rst::OnSCA_rstCombo4SelectChange)
	ON_CBN_SELCHANGE(ID_APP_SCA_COMBO_5, &CView_SCA_rst::OnSCA_rstCombo5SelectChange)
	ON_BN_CLICKED(ID_APP_SCA_BTN_1, &CView_SCA_rst::OnControlbutton_click_Run)
	ON_BN_CLICKED(ID_APP_SCA_BTN_2, &CView_SCA_rst::OnControlbutton_click_Apply)
	ON_BN_CLICKED(ID_APP_SCA_BTN_3, &CView_SCA_rst::OnControlbutton_click_Report)
	ON_NOTIFY(NM_DBLCLK, ID_APP_SCA_LIST_1, &CView_SCA_rst::OnSCA_ListCtrlDBClick_1)
	ON_NOTIFY(NM_DBLCLK, ID_APP_SCA_LIST_2, &CView_SCA_rst::OnSCA_ListCtrlDBClick_2)
	ON_WM_TIMER()
END_MESSAGE_MAP()



void CView_SCA_rst::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	Create_Combobox();
	Create_Edit();
	Create_Btn();
	Create_ListCtrl();
}

void CView_SCA_rst::InitData()
{
	m_ctrCombo[0].ResetContent();
	m_ctrCombo[1].ResetContent();
//	m_ctrCombo[2].ResetContent();
	m_ctrCombo[3].ResetContent();
	m_ctrCombo[4].ResetContent();

	Update_Combo1();
}


BOOL CView_SCA_rst::OnEraseBkgnd(CDC* pDC)
{
	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	CView_Base::OnEraseBkgnd(pDC);

	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[0]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[1]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[2]);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectSetting[0], FALSE);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectSetting[1]);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectSetting[2], FALSE);

	pViewMng->Draw_Split(pDC, graphics, m_rectSetting[0], DRAW_SPLIT_MODE_BOTTOM);
	
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[0], _T("계산 설정"), TRUE);
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[1], _T("최대고장전류"), TRUE);
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[2], _T("고장점지정"), TRUE);

	return TRUE;
}


void CView_SCA_rst::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);

	OnPrepareDC(&dc);


	Graphics						graphics(dc.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);


	Draw_Setting_Tag_1(&dc, graphics);

	Redraw_Ctrl();
}


void CView_SCA_rst::Redraw_Ctrl()
{
	//RedrawWindow();
	m_ctrCombo[0].SetFocus();
	m_ctrCombo[0].RedrawWindow();
	m_ctrCombo[1].SetFocus();
	m_ctrCombo[1].RedrawWindow();
	m_ctrCombo[2].SetFocus();
	m_ctrCombo[2].RedrawWindow();
	m_ctrCombo[3].SetFocus();
	m_ctrCombo[3].RedrawWindow();
	m_ctrCombo[4].SetFocus();
	m_ctrCombo[4].RedrawWindow();
	m_ctrCombo[5].SetFocus();
	m_ctrCombo[5].RedrawWindow();
	
	m_ctrCombo[0].SetFocus();
	
	
}


void CView_SCA_rst::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	m_rectBack[0].SetRect(_rect.left, _rect.top, _rect.right, _rect.top + 131);
	m_rectBack[1].SetRect(_rect.left, m_rectBack[0].bottom, _rect.left + (_rect.Width()/2), _rect.bottom);
	m_rectBack[2].SetRect(_rect.left +(_rect.Width() / 2), m_rectBack[0].bottom, _rect.right, _rect.bottom);

	m_rectBack[0].bottom -= 5;

	m_rectBack[1].right -= 5;
	m_rectBack[1].top += 5;

	m_rectBack[2].left += 5;
	m_rectBack[2].top += 5;

	MoveSize_Setting();
	MoveSize_List();
}

void CView_SCA_rst::MoveSize_Setting()
{
	if (m_ctrCombo[0].GetSafeHwnd() == NULL || m_btn_ctrl[0].GetSafeHwnd() == NULL)							return;

	CRect rect = m_rectBack[0];


	m_rectTitle[0] = rect;
	m_rectTitle[0].right = m_rectTitle[0].left + 131;
	m_rectTitle[0].bottom = m_rectTitle[0].top + 30;

	m_rectSetting[0] = rect;
	m_rectSetting[0].top = m_rectSetting[0].top + 30 ;
	m_rectSetting[0].bottom = m_rectSetting[0].top + 51;
	
	m_rectSetting[1] = m_rectSetting[0];
	m_rectSetting[1].top = m_rectSetting[1].bottom;
	m_rectSetting[1].bottom = m_rectSetting[1].top + 49;

	m_rectCtrl_Combobox[0] = m_rectSetting[0];
	m_rectCtrl_Combobox[0].InflateRect(-8, -13);
	m_rectCtrl_Combobox[0].left = m_rectCtrl_Combobox[0].left + 80;
	m_rectCtrl_Combobox[0].right = m_rectCtrl_Combobox[0].left + 178;

	m_rectCtrl_Combobox[1] = m_rectCtrl_Combobox[0];
	m_rectCtrl_Combobox[1].left = m_rectCtrl_Combobox[0].right + 8;
	m_rectCtrl_Combobox[1].right = m_rectCtrl_Combobox[1].left + 178;

	m_rectCtrl_Radio[0] = m_rectCtrl_Combobox[1];
	m_rectCtrl_Radio[0].InflateRect(0, -4);
	m_rectCtrl_Radio[0].left = m_rectCtrl_Combobox[1].right + 50;
	m_rectCtrl_Radio[0].right = m_rectCtrl_Radio[0].left + 120;

	m_rectCtrl_Radio[1] = m_rectCtrl_Radio[0];
	m_rectCtrl_Radio[1].left = m_rectCtrl_Radio[0].right + 8;
	m_rectCtrl_Radio[1].right = m_rectCtrl_Radio[1].left + 120;

	m_btn_ctrl_rect[2] = m_rectSetting[0]; 
	m_btn_ctrl_rect[2].InflateRect(-8, -9);
	m_btn_ctrl_rect[2].left = m_btn_ctrl_rect[2].right - 87;

	m_btn_ctrl_rect[0] = m_rectSetting[0];
	m_btn_ctrl_rect[0].InflateRect(-8, -9);
	m_btn_ctrl_rect[0].left = m_btn_ctrl_rect[2].left - 8 - 87;
	m_btn_ctrl_rect[0].right = m_btn_ctrl_rect[0].left + 87;

	//////////////////////////////////////////////////////////////////////////////////
	m_rectCtrl_Edit[0] = m_rectSetting[1];
	m_rectCtrl_Edit[0].InflateRect(-53, -13);

	m_rectCtrl_Edit[0].right = m_rectCtrl_Edit[0].left + 178;

	m_rectCtrl_Edit[1] = m_rectCtrl_Edit[0];
	m_rectCtrl_Edit[1].left = m_rectCtrl_Edit[0].right + 76;
	m_rectCtrl_Edit[1].right = m_rectCtrl_Edit[1].left + 178;

	m_rectCtrl_Edit[2] = m_rectCtrl_Edit[0];
	m_rectCtrl_Edit[2].left = m_rectCtrl_Edit[1].right + 76;
	m_rectCtrl_Edit[2].right = m_rectCtrl_Edit[2].left + 178;

	m_rectCtrl_Edit[3] = m_rectCtrl_Edit[0];
	m_rectCtrl_Edit[3].left = m_rectCtrl_Edit[2].right + 76;
	m_rectCtrl_Edit[3].right = m_rectCtrl_Edit[3].left + 178;

	m_rectCtrl_Edit[4] = m_rectCtrl_Edit[0];
	m_rectCtrl_Edit[4].left = m_rectCtrl_Edit[3].right + 76;
	m_rectCtrl_Edit[4].right = m_rectCtrl_Edit[4].left + 178;


	m_btn_ctrl_rect[1] = m_rectSetting[1];
	m_btn_ctrl_rect[1].InflateRect(-8, -9);
	m_btn_ctrl_rect[1].left = m_rectCtrl_Edit[4].right + 10;
	m_btn_ctrl_rect[1].right = m_btn_ctrl_rect[1].left + 87;



	///////////////////////////////////////////////////////////////////////////////
	m_ctrCombo[0].MoveWindow(m_rectCtrl_Combobox[0]);
	m_ctrCombo[1].MoveWindow(m_rectCtrl_Combobox[1]);

	m_ctrBtn_Radio[0].MoveWindow(m_rectCtrl_Radio[0]);
	m_ctrBtn_Radio[1].MoveWindow(m_rectCtrl_Radio[1]);

	rect = m_rectCtrl_Edit[0];
	rect.InflateRect(-1, -2);
	m_ctrEdit[0].MoveWindow(rect);

	rect = m_rectCtrl_Edit[1];
	rect.InflateRect(-1, -2);
	m_ctrEdit[1].MoveWindow(rect);

	rect = m_rectCtrl_Edit[2];
	rect.InflateRect(-1, -2);
	m_ctrEdit[2].MoveWindow(rect);

	rect = m_rectCtrl_Edit[3];
	rect.InflateRect(-1, -2);
	m_ctrEdit[3].MoveWindow(rect);

	rect = m_rectCtrl_Edit[4];
	rect.InflateRect(-1, -2);
	m_ctrEdit[4].MoveWindow(rect);

	m_btn_ctrl[2].MoveWindow(m_btn_ctrl_rect[2]);
	m_btn_ctrl[0].MoveWindow(m_btn_ctrl_rect[0]);
	m_btn_ctrl[1].MoveWindow(m_btn_ctrl_rect[1]);

}

void CView_SCA_rst::MoveSize_List()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL || m_ctrList[1].GetSafeHwnd() == NULL)							return;

	CRect rect = m_rectBack[1];
	
	m_rectTitle[1] = rect;
	m_rectTitle[1].right = m_rectTitle[1].left + 131;
	m_rectTitle[1].bottom = m_rectTitle[1].top + 30;

	m_rectCtrl_Combobox[3] = m_rectTitle[1];
	m_rectCtrl_Combobox[3].MoveToX(m_rectTitle[1].right);
	m_rectCtrl_Combobox[3].InflateRect(-8, -3);

	m_rectCtrl_List[0] = m_rectBack[1];

	rect = m_rectBack[2];

	m_rectTitle[2] = rect;
	m_rectTitle[2].right = m_rectTitle[2].left + 131;
	m_rectTitle[2].bottom = m_rectTitle[2].top + 30;

	m_rectCtrl_Combobox[4] = m_rectTitle[2];
	m_rectCtrl_Combobox[4].MoveToX(m_rectTitle[2].right);
	m_rectCtrl_Combobox[4].InflateRect(-8, -3);

	m_rectSetting[2] = rect;
	m_rectSetting[2].top = m_rectSetting[2].top + 30;
	m_rectSetting[2].bottom = m_rectSetting[2].top + 42;

	m_rectCtrl_List[1] = m_rectBack[2];
	m_rectCtrl_List[1].top += 30;

	m_rectCtrl_Edit[5] = m_rectSetting[2];
	m_rectCtrl_Edit[5].InflateRect(-67, -8);
	m_rectCtrl_Edit[5].right = m_rectCtrl_Edit[5].left + 178;

	m_rectCtrl_Combobox[2] = m_rectCtrl_Edit[5];
	m_rectCtrl_Combobox[2].left = m_rectCtrl_Edit[5].right + 73;
	m_rectCtrl_Combobox[2].right = m_rectCtrl_Combobox[2].left + 178;


	m_rectCtrl_Edit[6] = m_rectCtrl_Edit[5];
	m_rectCtrl_Edit[6].left = m_rectCtrl_Combobox[2].right + 73;
	m_rectCtrl_Edit[6].right = m_rectCtrl_Edit[6].left + 178;

	rect = m_rectCtrl_List[0];
	rect.top += 30;
	rect.bottom -= 2;

	m_ctrList[0].MoveWindow(rect);

	rect = m_rectCtrl_List[1];
	rect.top += 42;
	rect.bottom -= 2;

	m_ctrList[1].MoveWindow(rect);

	rect = m_rectCtrl_Edit[5];
	rect.InflateRect(-1, -2);
	m_ctrEdit[5].MoveWindow(rect);

	rect = m_rectCtrl_Edit[6];
	rect.InflateRect(-1, -2);
	m_ctrEdit[6].MoveWindow(rect);

	m_ctrCombo[2].MoveWindow(m_rectCtrl_Combobox[2]);

	m_ctrCombo[3].MoveWindow(m_rectCtrl_Combobox[3]);
	m_ctrCombo[4].MoveWindow(m_rectCtrl_Combobox[4]);

}


void CView_SCA_rst::Create_ListCtrl()
{
	m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect[2];
	rect[0] = CRect(10, 50, 350, 500);
	m_ctrList[0].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER | LVS_SHOWSELALWAYS, rect[0], this, ID_APP_SCA_LIST_1);
	m_ctrList[0].InsertColumn(0, _T("DL"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(1, _T("설비"), HDF_LEFT, 191);
	m_ctrList[0].InsertColumn(2, _T("3상단락"), HDF_LEFT, 157);
	m_ctrList[0].InsertColumn(3, _T("2선단락"), HDF_LEFT, 157);
	m_ctrList[0].InsertColumn(4, _T("1선지락"), HDF_LEFT, 157);
	m_ctrList[0].InsertColumn(5, _T("1선지락(30Ω)"), HDF_LEFT, 157);
	m_ctrList[0].InsertColumn(6, _T("idx"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(7, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
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
	m_ctrList[1].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_SCA_LIST_2);
	m_ctrList[1].InsertColumn(0, _T("DL"), HDF_LEFT, 80);
	m_ctrList[1].InsertColumn(1, _T("From"), HDF_LEFT, 186);
	m_ctrList[1].InsertColumn(2, _T("To"), HDF_LEFT, 186);
	m_ctrList[1].InsertColumn(3, _T("A"), HDF_LEFT, 117);
	m_ctrList[1].InsertColumn(4, _T("B"), HDF_LEFT, 117);
	m_ctrList[1].InsertColumn(5, _T("C"), HDF_LEFT, 117);
	m_ctrList[1].InsertColumn(6, _T("N"), HDF_LEFT, 117);
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
}

void CView_SCA_rst::Create_Edit()
{
	if (!m_ctrEdit[0].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | DT_VCENTER,
		CRect(100, 100, 200, 200), this, ID_APP_SCA_EDIT_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrEdit[1].Create(WS_CHILD | WS_VISIBLE | ES_CENTER,
		CRect(100, 100, 200, 200), this, ID_APP_SCA_EDIT_2))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrEdit[2].Create(WS_CHILD | WS_VISIBLE | ES_CENTER,
		CRect(100, 100, 200, 200), this, ID_APP_SCA_EDIT_3))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrEdit[3].Create(WS_CHILD | WS_VISIBLE | ES_CENTER,
		CRect(100, 100, 200, 200), this, ID_APP_SCA_EDIT_4))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrEdit[4].Create(WS_CHILD | WS_VISIBLE | ES_CENTER,
		CRect(100, 100, 200, 200), this, ID_APP_SCA_EDIT_5))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrEdit[5].Create(WS_CHILD | WS_VISIBLE | ES_CENTER,
		CRect(100, 100, 200, 200), this, ID_APP_SCA_EDIT_6))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrEdit[6].Create(WS_CHILD | WS_VISIBLE | ES_CENTER,
		CRect(100, 100, 200, 200), this, ID_APP_SCA_EDIT_7))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

//	m_ctrEdit[5].ShowWindow(SW_HIDE);
//	m_ctrEdit[6].ShowWindow(SW_HIDE);
}

void CView_SCA_rst::Create_Combobox()
{
	m_font_Combobox.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	if (!m_ctrCombo[0].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_SCA_COMBO_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}
	if (!m_ctrCombo[1].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_SCA_COMBO_2))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[2].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE |  CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_SCA_COMBO_3))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[3].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_SORT
		, CRect(100, 100, 200, 200), this, ID_APP_SCA_COMBO_4))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[4].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_SORT
		, CRect(100, 100, 200, 200), this, ID_APP_SCA_COMBO_5))
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

	m_ctrCombo[0].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[1].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[2].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[3].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[4].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	m_ctrCombo[0].SetDropDownHeight(10);
	m_ctrCombo[1].SetDropDownHeight(10);
	m_ctrCombo[2].SetDropDownHeight(10);
	m_ctrCombo[3].SetDropDownHeight(10);
	m_ctrCombo[4].SetDropDownHeight(10);


	m_ctrCombo[2].AddString(_T("3상 단락"));
	m_ctrCombo[2].AddString(_T("1선 지락"));
	m_ctrCombo[2].AddString(_T("2선 단락"));
	m_ctrCombo[2].AddString(_T("2선 지락"));



	//m_ctrCombo[2].ShowWindow(SW_HIDE);
}

void CView_SCA_rst::Create_Btn()
{
	m_btn_ctrl_rect[0] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[0].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[0], this, ID_APP_SCA_BTN_1))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create SCA Button Fail.\n"));
		return;
	}
	m_btn_ctrl[0].SetBitmapID(IDB_PCE_RUN_NOR, IDB_PCE_RUN_CLK, IDB_PCE_RUN_OVR);

	m_btn_ctrl_rect[1] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[1].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[1], this, ID_APP_SCA_BTN_2))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create SCA Button Fail.\n"));

		return;
	}
	m_btn_ctrl[1].SetBitmapID(IDB_APPLY_NOR, IDB_APPLY_CLK, IDB_APPLY_OVR);

	m_btn_ctrl_rect[2] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[2].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[2], this, ID_APP_SCA_BTN_3))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));

		return;
	}
	m_btn_ctrl[2].SetBitmapID(IDB_PCE_RPT_NOR, IDB_PCE_RPT_CLK, IDB_PCE_RPT_OVR);

//	m_btn_ctrl[0].ShowWindow(SW_HIDE);
//	m_btn_ctrl[1].ShowWindow(SW_HIDE);

	m_rectCtrl_Radio[0] = CRect(10, 20, 90, 250);
	if (!m_ctrBtn_Radio[0].Create(_T("최대고장전류"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, m_rectCtrl_Radio[0], this, ID_APP_SCA_BTN_RADIO_1))
	{
		AfxMessageBox(_T("Create PCE Radio Fail.\n"));
		return;
	}


	m_rectCtrl_Radio[1] = CRect(10, 20, 90, 250);
	if (!m_ctrBtn_Radio[1].Create(_T("고장점지정"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, m_rectCtrl_Radio[1], this, ID_APP_SCA_BTN_RADIO_2))
	{
		AfxMessageBox(_T("Create PCE Radio Fail.\n"));
		return;
	}

	m_ctrBtn_Radio[0].SetBitmapID(IDB_RADIO_UNCHECK, IDB_RADIO_CHECK, IDB_RADIO_DISABLE);
	m_ctrBtn_Radio[1].SetBitmapID(IDB_RADIO_UNCHECK, IDB_RADIO_CHECK, IDB_RADIO_DISABLE);

	m_ctrBtn_Radio[0].m_pFont_Text = &m_font_Combobox;
	m_ctrBtn_Radio[1].m_pFont_Text = &m_font_Combobox;
	m_ctrBtn_Radio[0].m_colorBg = RGB(255, 255, 255);
	m_ctrBtn_Radio[1].m_colorBg = RGB(255, 255, 255);

	m_ctrBtn_Radio[0].SetCheckButton(CHECKBOX_CHECKED);
}


void CView_SCA_rst::Draw_Setting_Tag_1(CDC* pDC, Graphics &graphics)
{
	CRect rTag[1];

	rTag[0] = m_rectCtrl_Combobox[0];
	rTag[0].left = m_rectCtrl_Combobox[0].left - 80;
	rTag[0].right = rTag[0].left + 80;

	CView_Manager* pViewMng = CView_Manager::Instance();

	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[0], 0, _T("변전소/MTR"));



	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentFar);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));

	SolidBrush						_drawRectbrush(Color(255, 153, 153, 153));
	Gdiplus::Pen					_drawRectpen(&_drawRectbrush, 1.);


//	CView_Manager* pViewMng = CView_Manager::Instance();
	Gdiplus::GraphicsPath gdiPath;

	Gdiplus::RectF  _rect_Imp[5];
	for (int i = 0; i < 5; i++)
	{
		_rect_Imp[i].X = m_rectCtrl_Edit[i].left;
		_rect_Imp[i].Y = m_rectCtrl_Edit[i].top;
		_rect_Imp[i].Width = m_rectCtrl_Edit[i].Width();
		_rect_Imp[i].Height = m_rectCtrl_Edit[i].Height();

		pViewMng->GetRoundRectPath(&gdiPath, _rect_Imp[i].GetLeft(), _rect_Imp[i].GetTop(), _rect_Imp[i].Width, _rect_Imp[i].Height, 6);
		graphics.DrawPath(&_drawRectpen, &gdiPath);
	}
	
	_rect_Imp[0].X -= 53;
	_rect_Imp[0].Width = 45;

	_rect_Imp[1].X -= 76;
	_rect_Imp[1].Width = 68;

	_rect_Imp[2].X -= 76;
	_rect_Imp[2].Width = 68;

	_rect_Imp[3].X -= 76;
	_rect_Imp[3].Width = 68;

	_rect_Imp[4].X -= 76;
	_rect_Imp[4].Width = 68;


	

	graphics.DrawString(_T("R1"), -1, &_drawfont, _rect_Imp[0], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("X1"), -1, &_drawfont, _rect_Imp[1], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("R0"), -1, &_drawfont, _rect_Imp[2], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("X0"), -1, &_drawfont, _rect_Imp[3], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("Mtr12_X1"), -1, &_drawfont, _rect_Imp[4], &_drawStrFormat, &_drawFontbrush);


	Gdiplus::RectF  _rect_FaultPos[3];
	for (int i = 5; i < 7; i++)
	{
		_rect_FaultPos[i - 5].X = m_rectCtrl_Edit[i].left;
		_rect_FaultPos[i - 5].Y = m_rectCtrl_Edit[i].top;
		_rect_FaultPos[i - 5].Width = m_rectCtrl_Edit[i].Width();
		_rect_FaultPos[i - 5].Height = m_rectCtrl_Edit[i].Height();

		pViewMng->GetRoundRectPath(&gdiPath
			, _rect_FaultPos[i - 5].GetLeft()
			, _rect_FaultPos[i - 5].GetTop()
			, _rect_FaultPos[i - 5].Width
			, _rect_FaultPos[i - 5].Height, 6);
		graphics.DrawPath(&_drawRectpen, &gdiPath);
	}

	_rect_FaultPos[2].X = m_rectCtrl_Combobox[2].left - 73;
	_rect_FaultPos[2].Y = m_rectCtrl_Combobox[2].top;
	_rect_FaultPos[2].Width = 65;
	_rect_FaultPos[2].Height = 26;

	_rect_FaultPos[0].X -= 67;
	_rect_FaultPos[0].Width = 59;

	_rect_FaultPos[1].X -= 73;
	_rect_FaultPos[1].Width = 65;

	graphics.DrawString(_T("고장위치"), -1, &_drawfont, _rect_FaultPos[0], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("저항값"), -1, &_drawfont, _rect_FaultPos[1], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("고장유형"), -1, &_drawfont, _rect_FaultPos[2], &_drawStrFormat, &_drawFontbrush);
	
}


void CView_SCA_rst::OnControlbutton_click_Radio1()
{
	BOOL bCheck = m_ctrBtn_Radio[0].GetCheckButton();

	if (bCheck)
	{
		m_ctrBtn_Radio[1].SetCheckButton(FALSE);
	}
	else
	{
		m_ctrBtn_Radio[1].SetCheckButton(TRUE);
	}
	m_ctrBtn_Radio[1].RedrawWindow();
}

void CView_SCA_rst::OnControlbutton_click_Radio2()
{
	BOOL bCheck = m_ctrBtn_Radio[1].GetCheckButton();

	if (bCheck)
	{
		m_ctrBtn_Radio[0].SetCheckButton(FALSE);
	}
	else
	{
		m_ctrBtn_Radio[0].SetCheckButton(TRUE);
	}
	m_ctrBtn_Radio[0].RedrawWindow();
}

void CView_SCA_rst::Update_Combo1()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CStringArray Array_SS;
	CIntArray	Array_SS_Idx;

	pDataMng->GetSSName_array(&Array_SS, &Array_SS_Idx);

	for (int i = 0; i < Array_SS.GetSize(); i++)
	{
		m_ctrCombo[0].AddString(Array_SS.GetAt(i));
		m_ctrCombo[0].SetItemData(i, (DWORD_PTR)Array_SS_Idx.GetAt(i));
	}
}

void CView_SCA_rst::OnSCA_rstCombo1SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	CString	strSS;
	CStringArray Array_MTR;
	CIntArray	Array_MTR_Idx;

	m_ctrCombo[0].GetLBText(nSel, strSS);

	m_ctrCombo[1].ResetContent();
	m_ctrCombo[3].ResetContent();
	m_ctrCombo[4].ResetContent();
	CDataManager* pDataMng = CDataManager::Instance();

	pDataMng->GetMTRName_array(strSS, &Array_MTR,&Array_MTR_Idx);

	for (int i = 0; i < Array_MTR.GetSize(); i++)
	{
		m_ctrCombo[1].AddString(Array_MTR.GetAt(i));
		m_ctrCombo[1].SetItemData(i, (DWORD_PTR)Array_MTR_Idx.GetAt(i));
	}

	m_ctrEdit[0].Clear();
	m_ctrEdit[1].Clear();
	m_ctrEdit[2].Clear();
	m_ctrEdit[3].Clear();
	m_ctrEdit[4].Clear();

	m_nSelect_SS_GEN = -1;
	m_nSelect_TR = -1;

//	RedrawWindow();
}

void CView_SCA_rst::OnSCA_rstCombo2SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();
	if (nSel == -1)
		return;

	CString	strSS, strMTR;

	m_ctrCombo[0].GetLBText(nSel, strSS);

	nSel = m_ctrCombo[1].GetCurSel();
	if (nSel == -1)
		return;

	m_ctrCombo[3].ResetContent();
	m_ctrCombo[4].ResetContent();

	m_ctrCombo[1].GetLBText(nSel, strMTR);


	int								nTRCnt(theAppDataMng->GetTableMaxCount(_T("tr_sta")));
	if (nTRCnt == 0)														return;

	int								i(0);
	int								ntrIndex(0), nTrType, nSSindex;
	int								nTrPDVRflag;

	CString str_data_ss, str_data_mtr, strTrIdx;
	
	for (i = 1; i <= (int)nTRCnt; i++)
	{
		nTrType = GETVALUE(int, "tr_sta", "tr_type", i);
		if (nTrType != 1)
			continue;


		ntrIndex = GETVALUE(int, "tr_sta", "tr_ii_ss", i);
		if (ntrIndex < 1)
		{
			continue;
		}

		str_data_ss = CA2W(GETSTRING(("ss_sta"), ("ss_nm"), ntrIndex)).m_psz;
		if (strSS != str_data_ss)
		{
			continue;
		}

		str_data_mtr = CA2W(GETSTRING(("tr_sta"), ("tr_nm"), i)).m_psz;
		if (strMTR != str_data_mtr)
		{
			continue;
		}
		nSSindex = ntrIndex;
		m_nSelect_TR = i;
		break;
	}
	int nND_idx,nND_ii_ss;
	int nGenType;
	int nGenCount = theAppDataMng->GetTableMaxCount(_T("gen_sta"));
	for (i = 1; i <= (int)nGenCount; i++)
	{
		nGenType = GETVALUE(int, "gen_sta", "gen_type", i);
		if (nGenType != 1)
			continue;

		nND_idx = GETVALUE(int, "gen_sta", "gen_ii_nd", i);
		nND_ii_ss = GETVALUE(int, "nd_dyn_ncpo", "nd_ii_ss", nND_idx);
		if (nSSindex != nND_ii_ss)
		{
			continue;
		}


		m_nSelect_SS_GEN = i;
		break;
	}

	CString strData[5];
	int nBR_idx,nGBR_idx;

	double dGen_r1, dGen_x1, dMtr_x1, dMtr_r0, dMtr_x0,dPosX;

	dGen_r1 = GETVALUE(double, "gen_sta", "gen_r", m_nSelect_SS_GEN);
	dGen_x1 = GETVALUE(double, "gen_sta", "gen_ssx", m_nSelect_SS_GEN);

	nBR_idx = GETVALUE(int, "tr_sta", "tr_ii_br", m_nSelect_TR);
	nGBR_idx = GETVALUE(int, "br_sta", "br_ii_gbr", nBR_idx);
	//dMtr_x1 = GETVALUE(double, "gbr_sta", "gbr_posr", nGBR_idx);
	dMtr_x1 = GETVALUE(double, "gbr_sta", "gbr_posx", nGBR_idx);
	dMtr_r0 = GETVALUE(double, "gbr_sta", "gbr_zerr", nGBR_idx);
	dMtr_x0 = GETVALUE(double, "gbr_sta", "gbr_zerx", nGBR_idx);

	dPosX = dGen_x1 + dMtr_x1;

	strData[0].Format(_T("%.3lf"), dGen_r1);
	strData[1].Format(_T("%.3lf"), dPosX);
	strData[2].Format(_T("%.3lf"), dMtr_r0);
	strData[3].Format(_T("%.3lf"), dMtr_x0);
	strData[4].Format(_T("%.3lf"), dMtr_x1);

	for(int i = 0 ; i < 5 ; i++)
		m_ctrEdit[i].SetWindowText(strData[i]);

	CStringArray Array_DL;
	CIntArray	Array_DL_Idx;
	CDataManager* pDataMng = CDataManager::Instance();

	pDataMng->GetDLName_array(strSS, &Array_DL,strMTR,&Array_DL_Idx);

	/*for (int i = 0; i < Array_DL.GetSize(); i++)
	{
		m_ctrCombo[3].AddString(Array_DL.GetAt(i));
		m_ctrCombo[4].AddString(Array_DL.GetAt(i));

		m_ctrCombo[3].SetItemData(i, (DWORD_PTR)Array_DL_Idx.GetAt(i));
		m_ctrCombo[4].SetItemData(i, (DWORD_PTR)Array_DL_Idx.GetAt(i));
	}*/
	for (int i = 0; i < Array_DL.GetSize(); i++)
	{
		m_ctrCombo[3].AddString(Array_DL.GetAt(i));
		m_ctrCombo[4].AddString(Array_DL.GetAt(i));
	}

	CString strName;
	int nIdx;
	for (int i = 0; i < m_ctrCombo[3].GetCount(); i++)
	{
		m_ctrCombo[3].GetLBText(i, strName);

		for (int k = 0; k < Array_DL.GetSize(); k++)
		{
			if (Array_DL.GetAt(k) == strName)
			{
				m_ctrCombo[3].SetItemData(i, (DWORD_PTR)Array_DL_Idx.GetAt(k));
				m_ctrCombo[4].SetItemData(i, (DWORD_PTR)Array_DL_Idx.GetAt(k));
				break;
			}
		}
		
	}
	

	m_ctrCombo[3].SetCurSel(0);
	m_ctrCombo[4].SetCurSel(0);
}

void CView_SCA_rst::OnSCA_rstCombo4SelectChange()
{
	Update_List_Max();
}

void CView_SCA_rst::OnSCA_rstCombo5SelectChange()
{
	Update_List_Pos();
}


void CView_SCA_rst::OnControlbutton_click_Run()
{
	if (m_bTimer)
		return;

	if (m_ctrBtn_Radio[0].GetCheckButton())
	{
		int nBR_idx, nGBR_idx,nGND_idx;

		/*nBR_idx = GETVALUE(int, "tr_sta", "tr_ii_br", m_nSelect_TR);
		nGBR_idx = GETVALUE(int, "br_sta", "br_ii_gbr", nBR_idx);
		nGND_idx = GETVALUE(int, "gbr_sta", "gbr_ii_tgnd", nGBR_idx);*/

		if (m_ctrCombo[3].GetCount() == 0)
			return;

		int nDL_Idx;
		CGraphDataArray		Array_Graph;
		CGraphData*			pData;
		CDataManager* pDataMng = CDataManager::Instance();

		for (int i = 0; i < m_ctrCombo[3].GetCount(); i++)
		{
			nDL_Idx = (int)m_ctrCombo[3].GetItemData(i);

			pDataMng->GetData_Graph(nDL_Idx, &Array_Graph);
			if (Array_Graph.GetSize() > 0)
				break;
		}

		if (Array_Graph.GetSize() == 0)
		{

			return;
		}
			
		
	
		pData = Array_Graph.GetAt(0);

		nGND_idx = pData->m_nGNDIdx[1];

		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_fltr"), 1, (double)0.);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flt_gnd"), 1, (int)nGND_idx);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flttype"), 1, (int) 5 );


		for (int i = 0; i < Array_Graph.GetSize(); i++)
			delete Array_Graph.GetAt(i);
	}
	else
	{
		int nGND_idx, nFlt_Type;
		CString strData;
		double dFlt_R;

		m_ctrEdit[6].GetWindowText(strData);
		dFlt_R = _wtof(strData);

		nFlt_Type = m_ctrCombo[2].GetCurSel() + 1; /////////  3상단락,1선지락,2선단락,2선지락
		
	
	//	nGND_idx = GETVALUE(int, "cbsw_sta", "cbsw_ii_tgnd", m_nSelect_CBSW);
		nGND_idx = m_nSelect_GND;
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_fltr"), 1, (double)dFlt_R);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flt_gnd"), 1, (int)nGND_idx);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flttype"), 1, (int)nFlt_Type);
	}


	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("11"), GetVIewID());
	//pDataMng->Excute_Appl(_T("8/9"));

	m_bTimer = TRUE;
	m_nCompAppl_ID = 11;
	SetTimer(1, 100, NULL);
	
}

void CView_SCA_rst::OnControlbutton_click_Report()
{
	if (m_bTimer)
		return;

	if (m_ctrBtn_Radio[0].GetCheckButton())
	{
		int nBR_idx, nGBR_idx, nGND_idx;

		/*nBR_idx = GETVALUE(int, "tr_sta", "tr_ii_br", m_nSelect_TR);
		nGBR_idx = GETVALUE(int, "br_sta", "br_ii_gbr", nBR_idx);
		nGND_idx = GETVALUE(int, "gbr_sta", "gbr_ii_tgnd", nGBR_idx);*/

		if (m_ctrCombo[3].GetCount() == 0)
			return;

		int nDL_Idx;
		CGraphDataArray		Array_Graph;
		CGraphData*			pData;
		CDataManager* pDataMng = CDataManager::Instance();

		for (int i = 0; i < m_ctrCombo[3].GetCount(); i++)
		{
			nDL_Idx = (int)m_ctrCombo[3].GetItemData(i);

			pDataMng->GetData_Graph(nDL_Idx, &Array_Graph);
			if (Array_Graph.GetSize() > 0)
				break;
		}

		if (Array_Graph.GetSize() == 0)
		{

			return;
		}



		pData = Array_Graph.GetAt(0);

		nGND_idx = pData->m_nGNDIdx[1];

		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_fltr"), 1, (double)0.);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flt_gnd"), 1, (int)nGND_idx);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flttype"), 1, (int)7);


		for (int i = 0; i < Array_Graph.GetSize(); i++)
			delete Array_Graph.GetAt(i);
	}
	else
	{
		int nGND_idx, nFlt_Type;
		CString strData;
		double dFlt_R;

		m_ctrEdit[6].GetWindowText(strData);
		dFlt_R = _wtof(strData);

		nFlt_Type = m_ctrCombo[2].GetCurSel() + 1; /////////  3상단락,1선지락,2선단락,2선지락


	//	nGND_idx = GETVALUE(int, "cbsw_sta", "cbsw_ii_tgnd", m_nSelect_CBSW);
		nGND_idx = m_nSelect_GND;
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_fltr"), 1, (double)dFlt_R);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flt_gnd"), 1, (int)nGND_idx);
		PUTDOUBLE2VALUE(_T("scaopt_dyn_uin"), _T("scaopt_flttype"), 1, (int)8);
	}


	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("11"), GetVIewID());
	//pDataMng->Excute_Appl(_T("8/9"));

	m_bTimer = TRUE;
	m_nCompAppl_ID = 11;
	SetTimer(1, 100, NULL);

}

void CView_SCA_rst::OnControlbutton_click_Apply()
{
	if (m_nSelect_SS_GEN < 0 || m_nSelect_TR < 0)
		return;

	
	CString strData[5];
	for (int i = 0; i < 5; i++)
		m_ctrEdit[i].GetWindowText(strData[i]);

	int nBR_idx, nGBR_idx;

	double dGen_r1, dGen_x1, dMtr_x1, dMtr_r0, dMtr_x0, dPosX;

	dGen_r1	 = _wtof(strData[0]);
	dPosX	 = _wtof(strData[1]);
	dMtr_r0	 = _wtof(strData[2]);
	dMtr_x0	 = _wtof(strData[3]);
	dMtr_x1	 = _wtof(strData[4]);

	nBR_idx = GETVALUE(int, "tr_sta", "tr_ii_br", m_nSelect_TR);
	nGBR_idx = GETVALUE(int, "br_sta", "br_ii_gbr", nBR_idx);

	dGen_x1 = dPosX - dMtr_x1;
		
	if (dGen_x1 < 0)
		dGen_x1 = 0;

	PUTDOUBLE2VALUE(_T("gen_sta"), _T("gen_r"), m_nSelect_SS_GEN, (double) dGen_r1 );
	PUTDOUBLE2VALUE(_T("gen_sta"), _T("gen_ssx"), m_nSelect_SS_GEN, (double)dGen_x1);

	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_posx"), nGBR_idx, (double)dMtr_x1);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_zerr"), nGBR_idx, (double)dMtr_r0);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_zerx"), nGBR_idx, (double)dMtr_x0);

	OnSCA_rstCombo2SelectChange();
}

void CView_SCA_rst::recv_Appl(int nAppl)
{
	if (!m_bTimer)
		return;

	m_nRecvAppl_ID = nAppl;

	if (m_nCompAppl_ID == nAppl)
	{
		m_bTimer = FALSE;
	}
}

void CView_SCA_rst::recv_Init()
{
	m_bTimer = FALSE;
	KillTimer(1);
}

void CView_SCA_rst::recv_Wnd(CWndMsgData* pWndMsgData)
{
	
	if (pWndMsgData->m_nAppl_id != 11)
		return;

	if (pWndMsgData->m_nOption == 1)
	{
		int nGND_idx, nFlt_Type;
		CString strData[2];
		double dFlt_R;

		dFlt_R = GETVALUE(double, _T("scaopt_dyn_uin"), _T("scaopt_fltr"), 1);
		nGND_idx = GETVALUE(int, _T("scaopt_dyn_uin"), _T("scaopt_flt_gnd"), 1);
		nFlt_Type = GETVALUE(int, _T("scaopt_dyn_uin"), _T("scaopt_flttype"), 1);

		int nSS_Idx, nMTR_Idx, nDL_Idx;
		nDL_Idx = GETVALUE(int, _T("nd_dyn_ncpo"), _T("nd_ii_dl"), nGND_idx);
		nMTR_Idx = GETVALUE(int, _T("nd_dyn_ncpo"), _T("nd_ii_mtr"), nGND_idx);
		nSS_Idx = GETVALUE(int, _T("nd_dyn_ncpo"), _T("nd_ii_ss"), nGND_idx);

		m_ctrCombo[0].SetCurSelId(nSS_Idx);
		OnSCA_rstCombo1SelectChange();
		m_ctrCombo[1].SetCurSelId(nMTR_Idx);
		OnSCA_rstCombo2SelectChange();
		m_ctrCombo[4].SetCurSelId(nDL_Idx);

		strData[0] = GETSTRING(_T("gnd_sta"), _T("gnd_nm"), nGND_idx);
		strData[1].Format(_T("%g"), dFlt_R);

		m_ctrEdit[5].SetWindowText(strData[0]);
		m_ctrEdit[6].SetWindowText(strData[1]);

		if(nFlt_Type > 0 && nFlt_Type < 5)
			m_ctrCombo[2].SetCurSel(nFlt_Type - 1);

		m_nSelect_GND = nGND_idx;

		m_ctrBtn_Radio[1].SetCheckButton(TRUE);
		m_ctrBtn_Radio[0].SetCheckButton(FALSE);
		m_ctrBtn_Radio[0].RedrawWindow();
		m_ctrBtn_Radio[1].RedrawWindow();
	}
	
}

void CView_SCA_rst::OnTimer(UINT_PTR nIDEvent)
{

	if (!m_bTimer)
	{
		KillTimer(nIDEvent);
		if (nIDEvent == 1)
		{
			Sleep(500);
			int nMode;
			if (m_ctrBtn_Radio[0].GetCheckButton())
			{
				nMode = 2;
				Update_List_Max();
			}
			else
			{
				nMode = 1;
				Update_List_Pos();
			}
			CString strData;
			strData.Format(_T("11,%d,"), nMode);
			CDataManager* pDataMng = CDataManager::Instance();
			pDataMng->Send_WndMsg(3, 2, strData);
		}

		RedrawWindow();
	}

	CView_Base::OnTimer(nIDEvent);
}


void CView_SCA_rst::Update_List_Max()
{
	int nSel = m_ctrCombo[3].GetCurSel();

	if (nSel == -1)
		return;

	CString	strDL;
	int nDL_Idx = (int)m_ctrCombo[3].GetItemData(nSel);
	m_ctrCombo[3].GetLBText(nSel, strDL);
	CGraphDataArray		Array_Graph;
	CGraphData*			pData;

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->GetData_Graph(nDL_Idx, &Array_Graph);

	m_ctrList[0].DeleteAllItems();

	CString strData[7];
	for (int i = 0; i < Array_Graph.GetSize(); i++)
	{
		pData = Array_Graph.GetAt(i);

		pData->m_dFault_value[0] = GETVALUE(double, _T("gnd_dyn_scao"), _T("gnd_fc_3ll"), pData->m_nGNDIdx[1]);
		pData->m_dFault_value[1] = GETVALUE(double, _T("gnd_dyn_scao"), _T("gnd_fc_2ll"), pData->m_nGNDIdx[1]);
		pData->m_dFault_value[2] = GETVALUE(double, _T("gnd_dyn_scao"), _T("gnd_fc_1lg"), pData->m_nGNDIdx[1]);
		pData->m_dFault_value[3] = GETVALUE(double, _T("gnd_dyn_scao"), _T("gnd_fc_1lg_30ohm"), pData->m_nGNDIdx[1]);

		strData[0] = strDL;
		strData[1] = CA2W(GETSTRING(("gnd_sta"), ("gnd_nm"), pData->m_nGNDIdx[1])).m_psz;
		strData[2].Format(_T("%.1lf"), pData->m_dFault_value[0]);
		strData[3].Format(_T("%.1lf"), pData->m_dFault_value[1]);
		strData[4].Format(_T("%.1lf"), pData->m_dFault_value[2]);
		strData[5].Format(_T("%.1lf"), pData->m_dFault_value[3]);
		strData[6].Format(_T("%d"), pData->m_nGNDIdx[1]);

		m_ctrList[0].InsertItem(m_ctrList[0].GetItemCount(), strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 2, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 3, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 4, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 5, strData[5], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 6, strData[6], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	}
	
	for (int i = 0; i < Array_Graph.GetSize(); i++)
		delete Array_Graph.GetAt(i);

	RedrawWindow();
}

void CView_SCA_rst::Update_List_Pos()
{
	int nSel = m_ctrCombo[4].GetCurSel();

	if (nSel == -1)
		return;

	CString	strDL;
	int nDL_Idx = (int)m_ctrCombo[4].GetItemData(nSel);
	m_ctrCombo[4].GetLBText(nSel, strDL);
	CGraphDataArray		Array_Graph;
	CGraphData*			pData;

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->GetData_Graph(nDL_Idx, &Array_Graph);

	m_ctrList[1].DeleteAllItems();

	CString strData[8];
	int nGBR_Idx,nGND_Idx[2];
	for (int i = 0; i < Array_Graph.GetSize(); i++)
	{
		pData = Array_Graph.GetAt(i);

		/////////////////// nd == gnd

		nGBR_Idx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), pData->m_nGNDIdx[1]);
	
		if(nGBR_Idx == 0)
		{
			nGBR_Idx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), pData->m_nGNDIdx[1]);
		}
			

		if (nGBR_Idx == 0)
			continue;

		nGND_Idx[0] = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nGBR_Idx);
		nGND_Idx[1] = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_tgnd"), nGBR_Idx);

		pData->m_dFault_value[0] = GETVALUE(double, _T("gbr_dyn_scao"), _T("GBR_FLT_PA_C"), nGBR_Idx);
		pData->m_dFault_value[1] = GETVALUE(double, _T("gbr_dyn_scao"), _T("GBR_FLT_PB_C"), nGBR_Idx);
		pData->m_dFault_value[2] = GETVALUE(double, _T("gbr_dyn_scao"), _T("GBR_FLT_PC_C"), nGBR_Idx);
		pData->m_dFault_value[3] = GETVALUE(double, _T("gbr_dyn_scao"), _T("GBR_FLT_PN_C"), nGBR_Idx);

		if( (abs(pData->m_dFault_value[0] )
			+abs(pData->m_dFault_value[1])
			+abs(pData->m_dFault_value[2])
			+abs(pData->m_dFault_value[3]) ) == 0)
			continue;

		strData[0] = strDL;
		strData[1] = CA2W(GETSTRING(("gnd_sta"), ("gnd_nm"), nGND_Idx[0])).m_psz;
		strData[2] = CA2W(GETSTRING(("gnd_sta"), ("gnd_nm"), nGND_Idx[1])).m_psz;
		strData[3].Format(_T("%.1lf"), pData->m_dFault_value[0]);
		strData[4].Format(_T("%.1lf"), pData->m_dFault_value[1]);
		strData[5].Format(_T("%.1lf"), pData->m_dFault_value[2]);
		strData[6].Format(_T("%.1lf"), pData->m_dFault_value[3]);
		strData[7].Format(_T("%d"), pData->m_nGNDIdx[1]);

		m_ctrList[1].InsertItem(m_ctrList[1].GetItemCount(), strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 2, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 3, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 4, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 5, strData[5], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 6, strData[6], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 7, strData[7], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	}

	for (int i = 0; i < Array_Graph.GetSize(); i++)
		delete Array_Graph.GetAt(i);

	RedrawWindow();
}

void CView_SCA_rst::OnSCA_ListCtrlDBClick_1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	if (nRow == -1)
		return;

	CString strIdx = m_ctrList[0].GetItemText(nRow, 6);

	int nND_idx = _wtoi(strIdx);

	CString strSend;

	strSend.Format(_T("999,%d,단선도이동"), nND_idx);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Send_WndMsg(WNDMSG_PROGRAMID_SLD, WNDMSG_PROGRAMID_HMI, strSend);


}

void CView_SCA_rst::OnSCA_ListCtrlDBClick_2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	if (nRow == -1)
		return;

	CString strIdx = m_ctrList[1].GetItemText(nRow, 7);

	int nND_idx = _wtoi(strIdx);
	CString strSend;

	strSend.Format(_T("999,%d,단선도이동"), nND_idx);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Send_WndMsg(WNDMSG_PROGRAMID_SLD, WNDMSG_PROGRAMID_HMI, strSend);


}