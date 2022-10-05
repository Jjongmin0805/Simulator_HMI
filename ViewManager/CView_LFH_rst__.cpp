#include "pch.h"
#include "CView_LFH_rst.h"
#include "resource.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"
#include "../DataManager/CDataManager.h"

CView_LFH_rst::CView_LFH_rst()
{

}

CView_LFH_rst::~CView_LFH_rst()
{
	Group_Data_Clear();
}


BEGIN_MESSAGE_MAP(CView_LFH_rst, CView_Base)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(ID_APP_LFH_COMBO_1, &CView_LFH_rst::OnLFH_rstCombo1SelectChange)
	ON_CBN_SELCHANGE(ID_APP_LFH_COMBO_3, &CView_LFH_rst::OnLFH_rstCombo3SelectChange)
	ON_BN_CLICKED(ID_APP_LFH_BTN_1, &CView_LFH_rst::OnControlbutton_click_Run_1)
	ON_BN_CLICKED(ID_APP_LFH_BTN_2, &CView_LFH_rst::OnControlbutton_click_Run_2)
	ON_BN_CLICKED(ID_APP_LFH_BTN_3, &CView_LFH_rst::OnControlbutton_click_Run_3)
	ON_BN_CLICKED(ID_APP_LFH_BTN_4, &CView_LFH_rst::OnControlbutton_click_Run_4)
END_MESSAGE_MAP()


void CView_LFH_rst::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	Create_ListCtrl();
	Create_Combobox();
	Create_Btn();
	Create_DateTimeCtrl();
}

void CView_LFH_rst::InitData()
{
	m_ctrCombo[0].ResetContent();
	m_ctrCombo[1].ResetContent();
	m_ctrCombo[2].ResetContent();
	m_ctrCombo[3].ResetContent();
	m_ctrCombo[4].ResetContent();

	SetComboxData_Subs();


	CString strData;
	for (int i = 0; i < 24; i++)
	{
		strData.Format(_T("%d"), i );
		m_ctrCombo[2].AddString(strData);
		m_ctrCombo[3].AddString(strData);
	}

	m_ctrCombo[2].SetCurSel(0);
	m_ctrCombo[3].SetCurSel(23);


	m_ctrCombo[4].AddString(_T("DL 조회"));
	m_ctrCombo[4].AddString(_T("MTR 조회"));
	m_ctrCombo[4].AddString(_T("SS 조회"));
	m_ctrCombo[4].SetCurSel(0);

}

void CView_LFH_rst::SetComboxData_Subs()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CStringArray Array_SS;

	pDataMng->GetSSName_array(&Array_SS);

	for (int i = 0; i < Array_SS.GetSize(); i++)
	{
		m_ctrCombo[0].AddString(Array_SS.GetAt(i));
	}

	//m_ctrCombo[2].AddString(_T("A"));
	//m_ctrCombo[2].AddString(_T("B"));
	//m_ctrCombo[2].AddString(_T("C"));


}

void CView_LFH_rst::OnLFH_rstCombo1SelectChange()
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

	CDataManager* pDataMng = CDataManager::Instance();

	pDataMng->GetDLName_array(strSS, &Array_DL, _T(""), &Array_DL_Idx);

	for (int i = 0; i < Array_DL.GetSize(); i++)
	{
		m_ctrCombo[1].AddString(Array_DL.GetAt(i));
		m_ctrCombo[1].SetItemData(i, (DWORD_PTR)Array_DL_Idx.GetAt(i));

	}

	//m_ctrCombo[2].SetCurSel(0);
}

void CView_LFH_rst::OnLFH_rstCombo3SelectChange()
{
	int nSel = m_ctrCombo[2].GetCurSel();

	if (nSel == -1)
		return;

	m_ctrCombo[3].ResetContent();

	int nSt = nSel;
	CString strData;
	for (int i = nSt; i < 24; i++)
	{
		strData.Format(_T("%d"), i);
		m_ctrCombo[3].AddString(strData);
	}
	m_ctrCombo[3].SetCurSel(0);
	
}

void CView_LFH_rst::Create_ListCtrl()
{
	m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect[4];
	rect[0] = CRect(10, 50, 350, 500);
	m_ctrList[0].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_LFH_LIST_1);
	m_ctrList[0].InsertColumn(0, _T("\n구분"), HDF_LEFT, 467);
	m_ctrList[0].InsertColumn(1, _T("\n정보"), HDF_LEFT, 467);
	m_ctrList[0].InsertColumn(2, _T("dump"), HDF_LEFT, 0);
	m_ctrList[0].ShowWindow(SW_SHOW);
	m_ctrList[0].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[0].m_HeaderCtrl.SetHeight(54);
	m_ctrList[0].m_HeaderCtrl.SetFlat();
	m_ctrList[0].m_HeaderCtrl.SetFlat();
	m_ctrList[0].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[0].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[0].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[0].SetBgColor(RGB(255, 255, 255));
	m_ctrList[0].SetUnderLine();
	m_ctrList[0].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[0].SetTextFont(&m_listfont);
	m_ctrList[0].SetRowHeight(38);


	rect[1] = CRect(10, 50, 350, 500);
	m_ctrList[1].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, rect[1], this, ID_APP_LFH_LIST_2);
	m_ctrList[1].InsertColumn(0, _T(""), HDF_LEFT, 93);
	m_ctrList[1].InsertColumn(1, _T("\n일시"), HDF_LEFT, 210);
	m_ctrList[1].InsertColumn(2, _T("\n총 부하"), HDF_LEFT, 210);
	m_ctrList[1].InsertColumn(3, _T("\n발전량"), HDF_LEFT, 210);
	m_ctrList[1].InsertColumn(4, _T("\n순 부하"), HDF_LEFT, 210);
	m_ctrList[1].InsertColumn(5, _T("dump"), HDF_LEFT, 0);
	m_ctrList[1].ShowWindow(SW_SHOW);
	m_ctrList[1].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[1].m_HeaderCtrl.SetHeight(53);
	m_ctrList[1].m_HeaderCtrl.SetFlat();
	m_ctrList[1].m_HeaderCtrl.SetFlat();
	m_ctrList[1].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[1].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[1].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[1].SetBgColor(RGB(255, 255, 255));
	m_ctrList[1].SetUnderLine();
	m_ctrList[1].SetColorUnderLine(RGB(215, 214, 214));
	m_ctrList[1].SetTextFont(&m_listfont);
	m_ctrList[1].SetRowHeight(37);


	rect[2] = CRect(10, 50, 350, 500);
	m_ctrList[2].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, rect[2], this, ID_APP_LFH_LIST_3);
	m_ctrList[2].InsertColumn(0, _T("시간"), HDF_LEFT, 211);
	m_ctrList[2].InsertColumn(1, _T("총 부하"), HDF_LEFT, 235);
	m_ctrList[2].InsertColumn(2, _T("발전량"), HDF_LEFT, 235);
	m_ctrList[2].InsertColumn(3, _T("순 부하"), HDF_LEFT, 235);
	m_ctrList[2].InsertColumn(4, _T("dump"), HDF_LEFT, 0);
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

	m_ctrList[0].InsertItem(0,_T("선로 긍장 길이"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	m_ctrList[0].InsertItem(1, _T("분산전원 정격용량 합계(A+B+C)"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	m_ctrList[0].InsertItem(2, _T("특고압 누적 연계용량(A+B)"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	m_ctrList[0].InsertItem(3, _T("특고압 연계용량(A)"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	m_ctrList[0].InsertItem(4, _T("저압전용 연계용량(B)"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	m_ctrList[0].InsertItem(5, _T("저압공용 연계용량(C)"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	//m_ctrList[0].SetItemText(0,1, _T("선로 긍장 길이"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

	m_ctrList[1].InsertItem(0, _T("최대 부하"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	m_ctrList[1].InsertItem(1, _T("최소 부하"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	m_ctrList[1].InsertItem(2, _T("최대 발전"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	m_ctrList[1].InsertItem(3, _T("최소 발전"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	m_ctrList[1].InsertItem(4, _T("최대 순 부하"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);
	m_ctrList[1].InsertItem(5, _T("최소 순 부하"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);

}

void CView_LFH_rst::Create_DateTimeCtrl()
{
	if (!m_ctrDate[0].Create(WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT,
		CRect(100, 100, 200, 200), this, ID_APP_LFH_DATE_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrDate[1].Create(WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT,
		CRect(100, 100, 200, 200), this, ID_APP_LFH_DATE_2))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrDate[2].Create(WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT,
		CRect(100, 100, 200, 200), this, ID_APP_LFH_DATE_3))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

}


void CView_LFH_rst::Create_Combobox()
{
	m_font_Combobox.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	if (!m_ctrCombo[0].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_LFH_COMBO_1))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}
	if (!m_ctrCombo[1].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_LFH_COMBO_2))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[2].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_LFH_COMBO_3))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}
	
	if (!m_ctrCombo[3].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_LFH_COMBO_4))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[4].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_LFH_COMBO_5))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
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
	m_ctrCombo[4].SetDropDownHeight(3);

}

void CView_LFH_rst::Create_Btn()
{
	m_btn_ctrl_rect[0] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[0].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[0], this, ID_APP_LFH_BTN_1))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[0].SetBitmapID(IDB_LFH_NOR, IDB_LFH_CLK, IDB_LFH_OVR);

	m_btn_ctrl_rect[1] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[1].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[1], this, ID_APP_LFH_BTN_2))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[1].SetBitmapID(IDB_LFH_NOR, IDB_LFH_CLK, IDB_LFH_OVR);
	/////////////////////////////////////////////////////////////

	m_btn_ctrl_rect[2] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[2].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[1], this, ID_APP_LFH_BTN_3))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[2].SetBitmapID(IDB_PCE_RPT_NOR, IDB_PCE_RPT_CLK, IDB_PCE_RPT_OVR);

	m_btn_ctrl_rect[3] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[3].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[1], this, ID_APP_LFH_BTN_4))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[3].SetBitmapID(IDB_PCE_RPT_NOR, IDB_PCE_RPT_CLK, IDB_PCE_RPT_OVR);
}



void CView_LFH_rst::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);

	OnPrepareDC(&dc);
	Graphics						graphics(dc.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
	
	Draw_Setting_Tag(&dc, graphics);
	Draw_Right_Title(&dc, graphics);

	Redraw_Ctrl();
}

void CView_LFH_rst::Redraw_Ctrl()
{
	/*if (m_ctrCombo[3].GetFocus() == GetFocus())
		return;*/

	//m_ctrCombo[0].SetFocus();
	m_ctrCombo[0].RedrawWindow();
	//m_ctrCombo[1].SetFocus();
	m_ctrCombo[1].RedrawWindow();
	//m_ctrCombo[2].SetFocus();
	m_ctrCombo[2].RedrawWindow();
	//m_ctrCombo[3].SetFocus();
	m_ctrCombo[3].RedrawWindow();
	m_ctrCombo[4].RedrawWindow();
}

void CView_LFH_rst::Draw_Setting_Tag(CDC* pDC, Graphics &graphics)
{
	CRect rTag[7];

	rTag[0] = m_rectCtrl_Combobox[0];
	rTag[0].left = m_rectCtrl_Combobox[0].left - 80;
	rTag[0].right = rTag[0].left + 80;

	rTag[1] = m_rectCtrl_Date[0];
	rTag[1].left = m_rectCtrl_Date[0].left - 60;
	rTag[1].right = rTag[1].left + 60;

	rTag[2] = m_rectCtrl_Date[0];
	rTag[2].left = m_rectCtrl_Date[0].right;
	rTag[2].right = rTag[2].left + 27;

	rTag[3] = m_rectCtrl_Combobox[2];
	rTag[3].left = m_rectCtrl_Combobox[2].left - 60;
	rTag[3].right = rTag[3].left + 60;

	rTag[4] = m_rectCtrl_Combobox[3];
	rTag[4].left = m_rectCtrl_Combobox[3].left - 45;
	rTag[4].right = rTag[4].left + 50;

	rTag[5] = m_rectCtrl_Combobox[3];
	rTag[5].left = m_rectCtrl_Combobox[3].right;
	rTag[5].right = rTag[5].left + 20;

	rTag[6] = m_rectCtrl_Date[2];
	rTag[6].left = m_rectCtrl_Date[2].left - 60;
	rTag[6].right = rTag[6].left + 60;

	CView_Manager* pViewMng = CView_Manager::Instance();

	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[0], 0, _T("변전소/선로"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[1], 0, _T("조회 기간"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[2], 0, _T("~"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[3], 0, _T("조회시간"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[4], 0, _T("시  ~"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[5], 0, _T("시"));
	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[6], 0, _T("조회 일"));
}

void CView_LFH_rst::Draw_Right_Title(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectCtrl_Right[1];

	rect.bottom = rect.top + 30;
	rect.InflateRect(-8, -10);

	Gdiplus::RectF  _r[3];

	_r[0].X = rect.right - 400;
	_r[0].Y = rect.top + 40;
	_r[0].Width = 55;
	_r[0].Height = rect.Height();

	_r[1] = _r[2] = _r[0];

	_r[1].X = _r[0].X + _r[0].Width + 85;
	_r[1].Width = 55;

	_r[2].X = _r[1].X + _r[1].Width + 85;
	_r[2].Width = 55;

	CPoint ptEx[3];
	ptEx[0].x = _r[0].X + _r[0].Width + 8;
	ptEx[0].y = rect.CenterPoint().y + 40;

	ptEx[1].x = _r[1].X + _r[1].Width + 8;
	ptEx[1].y = rect.CenterPoint().y + 40;

	ptEx[2].x = _r[2].X + _r[2].Width + 8;
	ptEx[2].y = rect.CenterPoint().y + 40;


	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));


	graphics.DrawString(_T("총부하"), -1, &_drawfont, _r[0], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("발전"), -1, &_drawfont, _r[1], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("순부하"), -1, &_drawfont, _r[2], &_drawStrFormat, &_drawFontbrush);


	SolidBrush						LineBrush(Color(255, 23, 23, 233));
	Gdiplus::Pen					_drawLinepen(&LineBrush, 2.);

	graphics.DrawLine(&_drawLinepen, ptEx[0].x, ptEx[0].y, ptEx[0].x + 62, ptEx[0].y);

	LineBrush.SetColor(Color(255, 12, 133, 12));
	_drawLinepen.SetBrush(&LineBrush);
	graphics.DrawLine(&_drawLinepen, ptEx[1].x, ptEx[1].y, ptEx[1].x + 62, ptEx[1].y);

	LineBrush.SetColor(Color(255, 255, 8, 8));
	_drawLinepen.SetBrush(&LineBrush);
	graphics.DrawLine(&_drawLinepen, ptEx[2].x, ptEx[2].y, ptEx[2].x + 62, ptEx[2].y);

	Draw_Right_Graph(pDC, graphics);

	//Draw_TopRight_Infor(pDC, graphics);
}

void CView_LFH_rst::Draw_Right_Graph(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectCtrl_Graph;

	rect.InflateRect(-10, -10);
	rect.top += 40;
	rect.left += 50;
	rect.bottom -= 50;

	
	SolidBrush						LineBrush(Color(255, 0,0,0));
	Gdiplus::Pen					_drawLinepen(&LineBrush, 1.);

	graphics.DrawLine(&_drawLinepen, rect.left , rect.bottom, rect.left, rect.top);
	graphics.DrawLine(&_drawLinepen, rect.left, rect.bottom, rect.right, rect.bottom);

	////////////////////////////////////////////////////////////////////

	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentFar);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));

	Gdiplus::RectF  _rect_Y_Name;
	Gdiplus::RectF  _rect_X_Name;
	Gdiplus::RectF  _rect_Y_Split[6];

	_rect_Y_Name.X = m_rectCtrl_Graph.left;
	_rect_Y_Name.Y = rect.top - 40;
	_rect_Y_Name.Width = 60;
	_rect_Y_Name.Height = 20;

	_rect_X_Name.X = rect.right - 60;
	_rect_X_Name.Y = rect.bottom + 20;
	_rect_X_Name.Width = 60;
	_rect_X_Name.Height = 20;

	graphics.DrawString(_T("전력(kW)"), -1, &_drawfont, _rect_Y_Name, &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("시간"), -1, &_drawfont, _rect_X_Name, &_drawStrFormat, &_drawFontbrush);


	double dY_Split = double(rect.Height() / 6.);
	int nMax = 12000 , nMin = -12000;
	CString strSplit;

	for (int i = 0; i < 6; i++)
	{
		_rect_Y_Split[i] = _rect_Y_Name;

		_rect_Y_Split[i].Y = rect.top + (dY_Split * i) -10;

		strSplit.Format(_T("%d"), nMax - (4000 * i)) ;

		graphics.DrawString(strSplit , -1, &_drawfont, _rect_Y_Split[i], &_drawStrFormat, &_drawFontbrush);
	}

	

	
	//////////////////////////////////////////////////////////////////////////////////

	SolidBrush						LineBrush_1(Color(255, 23, 23, 233));
	SolidBrush						LineBrush_2(Color(255, 12, 133, 12));
	SolidBrush						LineBrush_3(Color(255, 255, 8, 8));
	Gdiplus::Pen					_drawLinepen_1(&LineBrush_1, 2.);
	Gdiplus::Pen					_drawLinepen_2(&LineBrush_2, 2.);
	Gdiplus::Pen					_drawLinepen_3(&LineBrush_3, 2.);

	Gdiplus::RectF  r;
	r.X = rect.left;
	r.Y = rect.top;
	r.Width = rect.Width();
	r.Height = rect.Height();

	Gdiplus::RectF  rIndex;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);

	CGraph_DLE* pData[2];
	double  dX_P, dY_P, dX, dY, dValue[2];
	

	/*Gdiplus::RectF _r_X_Tag;
	_r_X_Tag.X = -10;
	_r_X_Tag.Y = r.GetBottom() + 2;
	_r_X_Tag.Width = 20;
	_r_X_Tag.Height = 20;

	

	CString strX_Tag;
	for (int i = 0; i < m_Array_Graph_DLE.GetSize(); i++)
	{
		dX_P = r.X + (r.Width  * (((double)i) / (double)nCount));

		_r_X_Tag.X = dX_P - 10.;

		strX_Tag.Format(_T("%d"), i);
		graphics.DrawString(strX_Tag, -1, &_drawfont, _r_X_Tag, &_drawStrFormat, &_drawFontbrush);
	}*/

	CString strIndex;

	int nCount = m_Array_Graph_DLE.GetSize();

	for (int i = 1; i < m_Array_Graph_DLE.GetSize(); i++)
	{
		pData[0] = m_Array_Graph_DLE.GetAt(i-1);
		pData[1] = m_Array_Graph_DLE.GetAt(i);

		dValue[0] = pData[0]->m_dValue[0];
		dValue[1] = pData[1]->m_dValue[0];

		if (dValue[0] > nMax)
			dValue[0] = double(nMax) ;
		else if (dValue[0] < nMin)
			dValue[0] = double(nMin);

		if (dValue[1] > nMax)
			dValue[1] = double(nMax);
		else if (dValue[1] < nMin)
			dValue[1] = double(nMin);

		dX_P = r.X + (r.Width  * (((double) i - 1.) / (double)nCount));
		dY_P = r.GetBottom() - (r.Height * ((dValue[0] - nMin ) / double(nMax - nMin) ));

		dX = r.X + (r.Width  * ((double) i  / (double)nCount));
		dY = r.GetBottom() - (r.Height * ((dValue[1] - nMin) / double(nMax - nMin)));


		graphics.DrawLine(&_drawLinepen_1, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);

		strIndex.Format(_T("%d"), pData[1]->m_nIndex);
		rIndex.X = dX - 10;
		rIndex.Y = r.GetBottom() + 5;
		rIndex.Width = 20;
		rIndex.Height = 20;


		graphics.DrawString(strIndex, -1, &_drawfont, rIndex, &_drawStrFormat, &_drawFontbrush);

		if (i == 1)
		{
			strIndex.Format(_T("%d"), pData[0]->m_nIndex);
			rIndex.X = dX_P - 10;
			graphics.DrawString(strIndex, -1, &_drawfont, rIndex, &_drawStrFormat, &_drawFontbrush);
		}

		

	}
	/////////////////////////////////////////////////////
	for (int i = 1; i < m_Array_Graph_DLE.GetSize(); i++)
	{
		pData[0] = m_Array_Graph_DLE.GetAt(i - 1);
		pData[1] = m_Array_Graph_DLE.GetAt(i);

		dValue[0] = pData[0]->m_dValue[1];
		dValue[1] = pData[1]->m_dValue[1];

		if (dValue[0] > nMax)
			dValue[0] = double(nMax);
		else if (dValue[0] < nMin)
			dValue[0] = double(nMin);

		if (dValue[1] > nMax)
			dValue[1] = double(nMax);
		else if (dValue[1] < nMin)
			dValue[1] = double(nMin);

		dX_P = r.X + (r.Width  * (((double)i - 1.) / (double)nCount));
		dY_P = r.GetBottom() - (r.Height * ((dValue[0] - nMin) / double(nMax - nMin)));

		dX = r.X + (r.Width  * ((double)i / (double)nCount));
		dY = r.GetBottom() - (r.Height * ((dValue[1] - nMin) / double(nMax - nMin)));


		graphics.DrawLine(&_drawLinepen_2, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);

	}
	/////////////////////////////////////////////////////

	for (int i = 1; i < m_Array_Graph_DLE.GetSize(); i++)
	{
		pData[0] = m_Array_Graph_DLE.GetAt(i - 1);
		pData[1] = m_Array_Graph_DLE.GetAt(i);

		dValue[0] = pData[0]->m_dValue[2];
		dValue[1] = pData[1]->m_dValue[2];

		if (dValue[0] > nMax)
			dValue[0] = double(nMax);
		else if (dValue[0] < nMin)
			dValue[0] = double(nMin);

		if (dValue[1] > nMax)
			dValue[1] = double(nMax);
		else if (dValue[1] < nMin)
			dValue[1] = double(nMin);

		dX_P = r.X + (r.Width  * (((double)i - 1.) / (double)nCount));
		dY_P = r.GetBottom() - (r.Height * ((dValue[0] - nMin) / double(nMax - nMin)));

		dX = r.X + (r.Width  * ((double)i / (double)nCount));
		dY = r.GetBottom() - (r.Height * ((dValue[1] - nMin) / double(nMax - nMin)));


		graphics.DrawLine(&_drawLinepen_3, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);

	}
}

BOOL CView_LFH_rst::OnEraseBkgnd(CDC* pDC)
{
	CView_Base::OnEraseBkgnd(pDC);

	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	pViewMng->DrawArea_Base(pDC, graphics, m_rectCtrl[0]);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectCtrl[1]);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectCtrl[2]);

	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_Left[1],FALSE);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_Left[2]);

	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_Right[1],FALSE);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectCtrl_Graph,FALSE);
	pViewMng->Draw_Split(pDC, graphics, m_rectCtrl_Graph, DRAW_SPLIT_MODE_TOP);

	pViewMng->DrawArea_Title(pDC, graphics, m_rectListTitle[0], _T("선로 정보 요약"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectListTitle[1], _T("조회 결과"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectListTitle[2], _T("시간대별 총부하/발전량/순부하"));

	pViewMng->DrawArea_Unit(pDC, graphics, m_rectListUnit[0], _T("단위:km,kW"));
	pViewMng->DrawArea_Unit(pDC, graphics, m_rectListUnit[1], _T("단위:kW"));
	pViewMng->DrawArea_Unit(pDC, graphics, m_rectListUnit[2], _T("단위:kW"));

//	return CView_Base::OnEraseBkgnd(pDC);
	return TRUE;
}

void CView_LFH_rst::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	m_rectCtrl[0].SetRect(_rect.left, _rect.top, _rect.Width(), _rect.top + 45);
	m_rectCtrl[1].SetRect(_rect.left, m_rectCtrl[0].bottom + 10, (_rect.Width() * 0.5 - 5)
		, _rect.bottom );
	m_rectCtrl[2].SetRect(m_rectCtrl[1].right + 10, m_rectCtrl[1].top, _rect.right, _rect.bottom);

	MoveSize_Setting();
	MoveSize_Left();
	MoveSize_Right();
}

void CView_LFH_rst::MoveSize_Setting()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL)							return;

	m_rectCtrl_Combobox[0] = m_rectCtrl[0];
	m_rectCtrl_Combobox[0].InflateRect(-10, -10);
	m_rectCtrl_Combobox[0].left = m_rectCtrl_Combobox[0].left + 80;
	m_rectCtrl_Combobox[0].right = m_rectCtrl_Combobox[0].left + 165;
	m_rectCtrl_Combobox[0].bottom = m_rectCtrl_Combobox[0].top + 24;
	m_ctrCombo[0].MoveWindow(m_rectCtrl_Combobox[0]);

	m_rectCtrl_Combobox[1] = m_rectCtrl_Combobox[0];
	m_rectCtrl_Combobox[1].left = m_rectCtrl_Combobox[0].right + 10;
	m_rectCtrl_Combobox[1].right = m_rectCtrl_Combobox[1].left + 165;
	m_ctrCombo[1].MoveWindow(m_rectCtrl_Combobox[1]);

}

void CView_LFH_rst::MoveSize_Left()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL)							return;

	m_rectCtrl_Left[0] = m_rectCtrl[1];
	m_rectCtrl_Left[0].bottom = m_rectCtrl_Left[0].top + 47;

	m_rectCtrl_Left[1] = m_rectCtrl[1];
	m_rectCtrl_Left[1].top = m_rectCtrl_Left[0].bottom  ;
	m_rectCtrl_Left[1].bottom = m_rectCtrl_Left[1].top + ((m_rectCtrl[1]. Height() - m_rectCtrl_Left[0].Height()) /2) + 2;

	m_rectCtrl_Left[2] = m_rectCtrl[1];
	m_rectCtrl_Left[2].top = m_rectCtrl_Left[1].bottom;
	//////////////////////
	m_rectCtrl_Date[0] = m_rectCtrl_Left[0];
	m_rectCtrl_Date[0].InflateRect(-10,-10);
	m_rectCtrl_Date[0].bottom = m_rectCtrl_Date[0].top + 24;
	m_rectCtrl_Date[0].top += 1;
	m_rectCtrl_Date[0].bottom += 1;
	m_rectCtrl_Date[0].left = m_rectCtrl_Date[0].left + 55;
	m_rectCtrl_Date[0].right = m_rectCtrl_Date[0].left + 100;
	m_ctrDate[0].MoveWindow(m_rectCtrl_Date[0]);

	m_rectCtrl_Date[1] = m_rectCtrl_Date[0];
	m_rectCtrl_Date[1].left = m_rectCtrl_Date[0].right + 27;
	m_rectCtrl_Date[1].right = m_rectCtrl_Date[1].left + 100;
	m_ctrDate[1].MoveWindow(m_rectCtrl_Date[1]);
	/////////////////////////
	///////////////// 시간대 설정 combobox
	m_rectCtrl_Combobox[2] = m_rectCtrl_Date[1];
	m_rectCtrl_Combobox[2].left = m_rectCtrl_Date[1].right + 84;
	m_rectCtrl_Combobox[2].right = m_rectCtrl_Combobox[2].left + 50;

	m_rectCtrl_Combobox[3] = m_rectCtrl_Combobox[2];
	m_rectCtrl_Combobox[3].left = m_rectCtrl_Combobox[2].right + 40;
	m_rectCtrl_Combobox[3].right = m_rectCtrl_Combobox[3].left + 50;

	m_rectCtrl_Combobox[4] = m_rectCtrl_Combobox[2];
	m_rectCtrl_Combobox[4].left = m_rectCtrl_Combobox[3].right + 50;
	m_rectCtrl_Combobox[4].right = m_rectCtrl_Combobox[4].left + 100;


	m_ctrCombo[2].MoveWindow(m_rectCtrl_Combobox[2]);
	m_ctrCombo[3].MoveWindow(m_rectCtrl_Combobox[3]);
	m_ctrCombo[4].MoveWindow(m_rectCtrl_Combobox[4]);

	///////////////////////

	m_btn_ctrl_rect[2] = m_rectCtrl_Left[0];  // 33x87
	m_btn_ctrl_rect[2].left = m_btn_ctrl_rect[2].right - 8 - 87;
	m_btn_ctrl_rect[2].right = m_btn_ctrl_rect[2].left + 87;
	m_btn_ctrl_rect[2].InflateRect(0, -7);
	m_btn_ctrl[2].MoveWindow(m_btn_ctrl_rect[2]);

	m_btn_ctrl_rect[0] = m_rectCtrl_Left[0];  // 33x87
	m_btn_ctrl_rect[0].left = m_btn_ctrl_rect[2].left -8 - 87;
	m_btn_ctrl_rect[0].right = m_btn_ctrl_rect[0].left + 87;
	m_btn_ctrl_rect[0].InflateRect(0, -7);
	m_btn_ctrl[0].MoveWindow(m_btn_ctrl_rect[0]);

	///////////////////////////////////////
	m_rectListTitle[0] = m_rectCtrl_Left[1];
	m_rectListTitle[0].right = m_rectCtrl_Left[1].left + 121;
	m_rectListTitle[0].bottom = m_rectListTitle[0].top +  30;

	m_rectListUnit[0] = m_rectListTitle[0];
	m_rectListUnit[0].left = m_rectCtrl_Left[1].right - 86;
	m_rectListUnit[0].right = m_rectListUnit[0].left + 82;
	m_rectListUnit[0].InflateRect(0, -5);
//	m_rectListUnit[0].bottom = m_rectListTitle[0].top + 30;

	
	m_rectList[0] = m_rectCtrl_Left[1];
	m_rectList[0].top += 30;
	m_rectList[0].bottom -= 1;
	m_ctrList[0].MoveWindow(m_rectList[0]);
	////////////// 행의 높이 설정??

	///////////////////////////////////////
	m_rectListTitle[1] = m_rectCtrl_Left[2];
	m_rectListTitle[1].right = m_rectListTitle[1].left + 92;
	m_rectListTitle[1].bottom = m_rectListTitle[1].top + 30;

	m_rectListUnit[1] = m_rectListTitle[1];
	m_rectListUnit[1].left = m_rectCtrl_Left[2].right - 86;
	m_rectListUnit[1].right = m_rectListUnit[1].left + 82;
	m_rectListUnit[1].InflateRect(0, -5);

	m_rectList[1] = m_rectCtrl_Left[2];
	m_rectList[1].top += 30;
	m_rectList[1].bottom -= 1;
	m_ctrList[1].MoveWindow(m_rectList[1]);

}

void CView_LFH_rst::MoveSize_Right()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL)							return;

	m_rectCtrl_Right[0] = m_rectCtrl[2];
	m_rectCtrl_Right[0].bottom = m_rectCtrl_Right[0].top + 47;

	m_rectCtrl_Right[1] = m_rectCtrl[2];
	m_rectCtrl_Right[1].top = m_rectCtrl_Right[0].bottom;
	m_rectCtrl_Right[1].bottom = m_rectCtrl_Right[1].top + ((m_rectCtrl[2].Height() - m_rectCtrl_Right[0].Height()) / 2);

	m_rectCtrl_Right[2] = m_rectCtrl[2];
	m_rectCtrl_Right[2].top = m_rectCtrl_Right[1].bottom;
	//////////////////////
	m_rectCtrl_Date[2] = m_rectCtrl_Right[0];
	m_rectCtrl_Date[2].InflateRect(-10, -10);
	m_rectCtrl_Date[2].bottom = m_rectCtrl_Date[2].top + 24;
	m_rectCtrl_Date[2].top += 1;
	m_rectCtrl_Date[2].bottom += 1;
	m_rectCtrl_Date[2].left = m_rectCtrl_Date[2].left + 55;
	m_rectCtrl_Date[2].right = m_rectCtrl_Date[2].left + 165;
	m_ctrDate[2].MoveWindow(m_rectCtrl_Date[2]);

	m_btn_ctrl_rect[3] = m_rectCtrl_Right[0];  // 33x87
	m_btn_ctrl_rect[3].left = m_btn_ctrl_rect[3].right - 8 - 87;
	m_btn_ctrl_rect[3].right = m_btn_ctrl_rect[3].left + 87;
	m_btn_ctrl_rect[3].InflateRect(0, -7);

	m_btn_ctrl[3].MoveWindow(m_btn_ctrl_rect[3]);


	m_btn_ctrl_rect[1] = m_rectCtrl_Right[0];  // 33x87
	m_btn_ctrl_rect[1].left = m_btn_ctrl_rect[3].left - 8 - 87;
	m_btn_ctrl_rect[1].right = m_btn_ctrl_rect[1].left + 87;
	m_btn_ctrl_rect[1].InflateRect(0, -7);

	m_btn_ctrl[1].MoveWindow(m_btn_ctrl_rect[1]);
	
	///////////////////////////////////////
	m_rectListTitle[2] = m_rectCtrl_Right[1];
	m_rectListTitle[2].right = m_rectListTitle[2].left + 246;
	m_rectListTitle[2].bottom = m_rectListTitle[2].top + 30;

	m_rectListUnit[2] = m_rectListTitle[2];
	m_rectListUnit[2].left = m_rectCtrl_Right[1].right - 86;
	m_rectListUnit[2].right = m_rectListUnit[2].left + 82;
	m_rectListUnit[2].InflateRect(0, -5);

	m_rectCtrl_Graph = m_rectCtrl_Right[1];
	m_rectCtrl_Graph.top = m_rectListTitle[2].bottom;

	m_rectList[2] = m_rectCtrl_Right[2];
	m_rectList[2].bottom -= 1;
	m_ctrList[2].MoveWindow(m_rectList[2]);
	////////////// 행의 높이 설정??

}


void CView_LFH_rst::OnTimer(UINT_PTR nIDEvent)
{
	if (!m_bTimer)
	{
		KillTimer(nIDEvent);
		if (nIDEvent == 1)
		{
			Update_DL_History();
		}
		else if (nIDEvent == 2)
		{
			Get_ChartData_DLE();
		}
	}

	CView_Base::OnTimer(nIDEvent);
}


void CView_LFH_rst::recv_Appl(int nAppl)
{
	if (!m_bTimer)
		return;

	m_nRecvAppl_ID = nAppl;

	if (m_nCompAppl_ID == nAppl)
	{
		m_bTimer = FALSE;
	}
}

void CView_LFH_rst::recv_Init()
{
	m_bTimer = FALSE;
	KillTimer(1);
}


void CView_LFH_rst::Group_Data_Clear()
{
	for (int i = 0; i < m_Array_Graph_DLE.GetSize(); i++)
	{
		delete m_Array_Graph_DLE.GetAt(i);
	}
	m_Array_Graph_DLE.RemoveAll();
}

void CView_LFH_rst::Update_DL_History()
{
	int nSel_DL;

	nSel_DL = m_ctrCombo[1].GetCurSel();
	if (nSel_DL == -1)
	{
		AfxMessageBox(_T("선택된 DL 없습니다."));
		return;
	}
	int nDL_idx = (int)m_ctrCombo[1].GetItemData(nSel_DL);

	CString strData[6];
	double dValue[6];
	dValue[0] = GETVALUE(double, ("dl_dyn_stdleo"), ("dl_line_length"), nDL_idx);
	dValue[1] = GETVALUE(double, ("dl_dyn_stdleo"), ("dl_gen_ra_sum"), nDL_idx);
	dValue[2] = GETVALUE(double, ("dl_dyn_stdleo"), ("dl_gen_ra_sum2"), nDL_idx);
	dValue[3] = GETVALUE(double, ("dl_dyn_stdleo"), ("dl_gen_ra_hv"), nDL_idx);
	dValue[4] = GETVALUE(double, ("dl_dyn_stdleo"), ("dl_gen_ra_lvp"), nDL_idx);
	dValue[5] = GETVALUE(double, ("dl_dyn_stdleo"), ("dl_gen_ra_lvc"), nDL_idx);
	strData[0].Format(_T("%.1lf"), dValue[0]);
	strData[1].Format(_T("%.1lf"), dValue[1]* 1000);
	strData[2].Format(_T("%.1lf"), dValue[2]* 1000);
	strData[3].Format(_T("%.1lf"), dValue[3]* 1000);
	strData[4].Format(_T("%.1lf"), dValue[4]* 1000);
	strData[5].Format(_T("%.1lf"), dValue[5]* 1000);

	m_ctrList[0].SetItemText(0, 1, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].SetItemText(1, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].SetItemText(2, 1, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].SetItemText(3, 1, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].SetItemText(4, 1, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].SetItemText(5, 1, strData[5], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

	int nCount = theAppDataMng->GetTableMaxCount(_T("histsrch_dyn_rlto"));
	int nIdx;
	int nDay, nLoad;
	double dGenMW, dNetLoad;
	for (int i = 0; i < 6; i++)
	{
		m_ctrList[1].SetItemText(i, 1, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i, 2, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i, 3, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i, 4, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	}
	
	CString strDate, strDate_Format;

	for (int i = 1; i <= nCount; i++)
	{
		nIdx = GETVALUE(int, ("histsrch_dyn_rlto"), ("histsrch_index"), i);
		if(nIdx == 0)
			break;

		nDay = GETVALUE(int, ("histsrch_dyn_rlto"), ("histsrch_datehour"), i);
		nLoad = GETVALUE(int, ("histsrch_dyn_rlto"), ("histsrch_grossload"), i);
		dGenMW = GETVALUE(double, ("histsrch_dyn_rlto"), ("histsrch_gen"), i);
		dNetLoad = GETVALUE(double, ("histsrch_dyn_rlto"), ("histsrch_netload"), i);

		strDate.Format(_T("%d"), nDay);


		strData[0].Format(_T("%s/%s/%s %s시")
			, strDate.Left(4), strDate.Mid(4,2), strDate.Mid(6, 2), strDate.Mid(8, 2));
		strData[1].Format(_T("%d"), nLoad);
		strData[2].Format(_T("%.1lf"), dGenMW);
		strData[3].Format(_T("%.1lf"), dNetLoad);

		m_ctrList[1].SetItemText(i - 1, 1, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 2, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 3, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 4, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

	}

}

void CView_LFH_rst::Get_ChartData_DLE()
{
	Group_Data_Clear();
	int nCount = theAppDataMng->GetTableMaxCount(_T("spf_dyn_spfo"));

	CString strData;
	int nIdx;
	double dValue[3];
	CGraph_DLE* pData;

	CString strValue[3];

	m_ctrList[2].DeleteAllItems();
	for (int i = 1; i <= nCount; i++)
	{
		nIdx = GETVALUE(int, ("spf_dyn_spfo"), ("spfo_index"), i);
		strData = GETSTRING(_T("spf_dyn_spfo"), _T("spfo_step"), i);
		if (strData.IsEmpty())
			break;

		dValue[0] = GETVALUE(double, ("spf_dyn_spfo"), ("spfo_gloadp"), i); 
		dValue[1] = GETVALUE(double, ("spf_dyn_spfo"), ("spfo_genp"), i);
		dValue[2] = GETVALUE(double, ("spf_dyn_spfo"), ("spfo_netp"), i);

		pData = new CGraph_DLE();
		m_Array_Graph_DLE.Add(pData);
		pData->m_nIndex = nIdx;
		pData->m_dValue[0] = dValue[0];
		pData->m_dValue[1] = dValue[1];
		pData->m_dValue[2] = dValue[2];

		strValue[0].Format(_T("%.1lf"), pData->m_dValue[0]);
		strValue[1].Format(_T("%.1lf"), pData->m_dValue[1]);
		strValue[2].Format(_T("%.1lf"), pData->m_dValue[2]);

		strData.Format(_T("%d"), nIdx);

		m_ctrList[2].InsertItem(m_ctrList[2].GetItemCount(), strData, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 1, strValue[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 2, strValue[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 3, strValue[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	}

	RedrawWindow(m_rectCtrl_Right[1]);
}

void CView_LFH_rst::OnControlbutton_click_Run_1()
{
	int nSel_DL;

	nSel_DL = m_ctrCombo[1].GetCurSel();
	if (nSel_DL == -1)
	{
		AfxMessageBox(_T("선택된 DL 없습니다."));
		return;
	}
	int nSearch = m_ctrCombo[4].GetCurSel();
	int nDL_idx = (int)m_ctrCombo[1].GetItemData(nSel_DL);

	COleDateTime timeData[2];
	CString strTime[2];
	m_ctrDate[0].GetTime(timeData[0]);
	m_ctrDate[1].GetTime(timeData[1]);

	strTime[0].Format(_T("%s"), timeData[0].Format(_T("%Y%m%d")));
	strTime[1].Format(_T("%s"), timeData[1].Format(_T("%Y%m%d")));

	int nSel[2];
	nSel[0] = m_ctrCombo[2].GetCurSel();
	nSel[1] = m_ctrCombo[3].GetCurSel();
	
	CString strHour[2];
	m_ctrCombo[2].GetLBText(nSel[0], strHour[0]);
	m_ctrCombo[3].GetLBText(nSel[1], strHour[1]);

	int nHour[2];
	nHour[0] = _wtoi(strHour[0]);
	nHour[1] = _wtoi(strHour[1]);

	int nDay[2];
	nDay[0] = _wtoi(strTime[0]);
	nDay[1] = _wtoi(strTime[1]);
	int nType = 4;

	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_DL"), 1, (double)nDL_idx);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_SRTDAY"), 1, (double)nDay[0]);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_ENDDAY"), 1, (double)nDay[1]);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_SRTHR"), 1, (double)nHour[0]);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_ENDHR"), 1, (double)nHour[1]);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_MODE"), 1, (double)nType);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_MODE"), 1, (double)nSearch);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("4"), GetVIewID());

	m_bTimer = TRUE;
	m_nCompAppl_ID = 4;
	SetTimer(1, 100, NULL);



}

void CView_LFH_rst::OnControlbutton_click_Run_3()
{
	int nSel_DL;

	nSel_DL = m_ctrCombo[1].GetCurSel();
	if (nSel_DL == -1)
	{
		AfxMessageBox(_T("선택된 DL 없습니다."));
		return;
	}
	int nSearch = m_ctrCombo[4].GetCurSel();
	int nDL_idx = (int)m_ctrCombo[1].GetItemData(nSel_DL);

	COleDateTime timeData[2];
	CString strTime[2];
	m_ctrDate[0].GetTime(timeData[0]);
	m_ctrDate[1].GetTime(timeData[1]);

	strTime[0].Format(_T("%s"), timeData[0].Format(_T("%Y%m%d")));
	strTime[1].Format(_T("%s"), timeData[1].Format(_T("%Y%m%d")));

	int nSel[2];
	nSel[0] = m_ctrCombo[2].GetCurSel();
	nSel[1] = m_ctrCombo[3].GetCurSel();

	CString strHour[2];
	m_ctrCombo[2].GetLBText(nSel[0], strHour[0]);
	m_ctrCombo[3].GetLBText(nSel[1], strHour[1]);

	int nHour[2];
	nHour[0] = _wtoi(strHour[0]);
	nHour[1] = _wtoi(strHour[1]);

	int nDay[2];
	nDay[0] = _wtoi(strTime[0]);
	nDay[1] = _wtoi(strTime[1]);
	int nType = 7;

	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_DL"), 1, (double)nDL_idx);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_SRTDAY"), 1, (double)nDay[0]);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_ENDDAY"), 1, (double)nDay[1]);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_SRTHR"), 1, (double)nHour[0]);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_ENDHR"), 1, (double)nHour[1]);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_MODE"), 1, (double)nType);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_MODE"), 1, (double)nSearch);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("4"), GetVIewID());

	m_bTimer = TRUE;
	m_nCompAppl_ID = 4;
	SetTimer(1, 100, NULL);
}



void CView_LFH_rst::OnControlbutton_click_Run_2()
{
	int nSel_DL;

	nSel_DL = m_ctrCombo[1].GetCurSel();
	if (nSel_DL == -1)
	{
		AfxMessageBox(_T("선택된 DL 없습니다."));
		return;
	}
	int nDL_idx = (int)m_ctrCombo[1].GetItemData(nSel_DL);

	COleDateTime timeData[1];
	CString strTime[1];
	m_ctrDate[2].GetTime(timeData[0]);

	strTime[0].Format(_T("%s"), timeData[0].Format(_T("%Y%m%d")));


	int nDay[1];
	nDay[0] = _wtoi(strTime[0]);
	int nType = 5;

	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_DL"), 1, (double)nDL_idx);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_SRTDAY"), 1, (double)nDay[0]);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_MODE"), 1, (double)nType);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("4"), GetVIewID());

	m_bTimer = TRUE;
	m_nCompAppl_ID = 4;
	SetTimer(2, 100, NULL);
}

void CView_LFH_rst::OnControlbutton_click_Run_4()
{
	int nSel_DL;

	nSel_DL = m_ctrCombo[1].GetCurSel();
	if (nSel_DL == -1)
	{
		AfxMessageBox(_T("선택된 DL 없습니다."));
		return;
	}
	int nDL_idx = (int)m_ctrCombo[1].GetItemData(nSel_DL);

	COleDateTime timeData[1];
	CString strTime[1];
	m_ctrDate[2].GetTime(timeData[0]);

	strTime[0].Format(_T("%s"), timeData[0].Format(_T("%Y%m%d")));


	int nDay[1];
	nDay[0] = _wtoi(strTime[0]);
	int nType = 8;

	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_DL"), 1, (double)nDL_idx);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_HIST_SRTDAY"), 1, (double)nDay[0]);
	PUTDOUBLE2VALUE(_T("RPFOPT_DYN_UIN"), _T("RPFOPT_MODE"), 1, (double)nType);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("4"), GetVIewID());

	m_bTimer = TRUE;
	m_nCompAppl_ID = 4;
	SetTimer(2, 100, NULL);
}