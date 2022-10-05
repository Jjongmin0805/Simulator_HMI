#include "pch.h"
#include "CView_DNR_rst.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"
#include "../DataManager/CDataManager.h"
#include "resource.h"
#include "CView_DNR_rst_SSDlg.h"

CView_DNR_rst::CView_DNR_rst()
{
	m_bTimer = FALSE;
}

CView_DNR_rst::~CView_DNR_rst()
{

}


BEGIN_MESSAGE_MAP(CView_DNR_rst, CView_Base)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_APP_DNR_BTN_1, &CView_DNR_rst::OnControlbutton_click_Run)
	ON_NOTIFY(NM_CLICK, ID_APP_DNR_LIST_2, &CView_DNR_rst::OnListCtrlClick_2)
	ON_BN_CLICKED(ID_APP_DNR_BTN_CHECK_1, &CView_DNR_rst::OnControlbutton_click_Check1)
	ON_BN_CLICKED(ID_APP_DNR_BTN_CHECK_2, &CView_DNR_rst::OnControlbutton_click_Check2)
	ON_BN_CLICKED(ID_APP_DNR_BTN_CHECK_3, &CView_DNR_rst::OnControlbutton_click_Check3)
	ON_BN_CLICKED(ID_APP_DNR_BTN_CHECK_4, &CView_DNR_rst::OnControlbutton_click_Check4)
	ON_BN_CLICKED(ID_APP_DNR_BTN_CHECK_5, &CView_DNR_rst::OnControlbutton_click_Check5)
	ON_BN_CLICKED(ID_APP_DNR_BTN_CHECK_6, &CView_DNR_rst::OnControlbutton_click_Check6)
	ON_BN_CLICKED(ID_APP_DNR_BTN_CHECK_7, &CView_DNR_rst::OnControlbutton_click_Check7)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CView_DNR_rst::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	Create_Combobox();
	Create_Btn();
	Create_ListCtrl();
}

void CView_DNR_rst::InitData()
{
	m_ctrCombo[0].ResetContent();

	m_ctrCombo[0].AddString(_T("제한없음"));
	m_ctrCombo[0].AddString(_T("1"));
	m_ctrCombo[0].AddString(_T("2"));
	m_ctrCombo[0].AddString(_T("3"));
	m_ctrCombo[0].AddString(_T("4"));
	m_ctrCombo[0].AddString(_T("5"));

	//InitData_Substation();
	InitData_DNRopt();
}

void CView_DNR_rst::InitData_Substation()
{
	CString strIdx;
	int nIdx;
	int nCheck;

	for (int i = 0; i < m_ctrList[0].GetItemCount(); i++)
	{
		strIdx = m_ctrList[0].GetItemText(i, 2);
		nIdx = _wtoi(strIdx);

		
		nCheck = GETVALUE(int, _T("ss_dyn_uin"), _T("SS_DNRFLAG"), nIdx);

		if (nCheck == 1)
		{
			m_ctrList[0].SetCheckBox(i, 0, CHECKBOX_CHECKED);
		}
		else
		{
			m_ctrList[0].SetCheckBox(i, 0, CHECKBOX_NORMAL);
		}
	}
}

void CView_DNR_rst::InitData_DNRopt()
{
	VECWSTR vecTableName;
	theAppDataMng->GetTableNames(vecTableName);
	if (vecTableName.size() == size_t(0))
		return;

	int nDNR_opt = GETVALUE(int, _T("dnropt_dyn_uin"), _T("dnropt_object"), 1);
	int nDNR_swtype[3];
	nDNR_swtype[0] = GETVALUE(int, _T("dnropt_dyn_uin"), _T("dnropt_cben"), 1);
	nDNR_swtype[1] = GETVALUE(int, _T("dnropt_dyn_uin"), _T("dnropt_gaen"), 1);
	nDNR_swtype[2] = GETVALUE(int, _T("dnropt_dyn_uin"), _T("dnropt_maen"), 1);
	int nDNR_load = GETVALUE(int, _T("dnropt_dyn_uin"), _T("dnropt_load_type"), 1);
	int nDNR_ssmove = GETVALUE(int, _T("dnropt_dyn_uin"), _T("dnropt_ss_move_en"), 1);
	int nDNR_rcmove = GETVALUE(int, _T("dnropt_dyn_uin"), _T("dnropt_rc_move_en"), 1);

	if (nDNR_opt == 1)
		m_ctrBtn_Check[0].SetCheckButton(CHECKBOX_CHECKED);
	else if (nDNR_opt == 2)
		m_ctrBtn_Check[1].SetCheckButton(CHECKBOX_CHECKED);
	else if (nDNR_opt == 3)
		m_ctrBtn_Check[2].SetCheckButton(CHECKBOX_CHECKED);

	if(nDNR_load == 1)
		m_ctrBtn_Check[3].SetCheckButton(CHECKBOX_CHECKED);
	else if (nDNR_load == 2)
		m_ctrBtn_Check[4].SetCheckButton(CHECKBOX_CHECKED);
	else if (nDNR_load == 3)
		m_ctrBtn_Check[5].SetCheckButton(CHECKBOX_CHECKED);
	else if (nDNR_load == 4)
		m_ctrBtn_Check[6].SetCheckButton(CHECKBOX_CHECKED);

	if(nDNR_swtype[0] == 1)
		m_ctrBtn_Check[7].SetCheckButton(CHECKBOX_CHECKED);

	if (nDNR_swtype[1] == 1)
		m_ctrBtn_Check[8].SetCheckButton(CHECKBOX_CHECKED);

	if (nDNR_swtype[2] == 1)
		m_ctrBtn_Check[9].SetCheckButton(CHECKBOX_CHECKED);

	if (nDNR_ssmove == 1)
		m_ctrBtn_Check[10].SetCheckButton(CHECKBOX_CHECKED);

	if (nDNR_rcmove == 1)
		m_ctrBtn_Check[11].SetCheckButton(CHECKBOX_CHECKED);

	int nSW_opr_Mx = GETVALUE(int, _T("dnropt_dyn_uin"), _T("dnropt_max_chgsw"), 1);
	
	if (nSW_opr_Mx > 5)
		m_ctrCombo[0].SetCurSel(5);
	else
	{
		m_ctrCombo[0].SetCurSel(nSW_opr_Mx);
	}
}


void CView_DNR_rst::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);

	OnPrepareDC(&dc);

	Graphics						graphics(dc.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CRect r;
	GetClientRect(&r);

	Draw_Setting_Tag_1(&dc, graphics);

	m_ctrCombo[0].SetFocus();
	m_ctrCombo[0].RedrawWindow();
	
}


void CView_DNR_rst::Draw_Setting_Tag_1(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectSetting[0];

	rect.InflateRect(-8, -8);

	Gdiplus::RectF  _r;

	_r.X = rect.left;
	_r.Y = rect.top;
	_r.Width = 44;
	_r.Height = 78;


	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 19, 94, 53));


	graphics.DrawString(_T("변전소"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);

	rect = m_rectSetting[1];
	rect.InflateRect(0, -8);

	_r.X = rect.left;
	_r.Y = rect.top;
	_r.Width = 100;
	_r.Height = 16;

	_drawStrFormat.SetAlignment(StringAlignmentNear);

	graphics.DrawString(_T("재구성 목적"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);
	_r.Y = m_rectCtrl_Check[3].top;
	graphics.DrawString(_T("기준 부하"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);
	_r.Y = m_rectCtrl_Check[7].top;
	graphics.DrawString(_T("조작 SW-Type"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);

	rect = m_rectSetting[2];
	rect.InflateRect(0, -8);

	_r.X = rect.left;
	_r.Y = rect.top;
	_r.Width = 150;
	_r.Height = 16;

	_drawStrFormat.SetAlignment(StringAlignmentNear);

	graphics.DrawString(_T("변전소간 이동 적용"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);
	_r.Y = m_rectCtrl_Check[11].top;
	graphics.DrawString(_T("Recloser DL 변동 허용"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);

	_r.Y = m_rectCtrl_Combobox[0].top + 6;
	graphics.DrawString(_T("최대 조작 개폐기 수"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);
}


BOOL CView_DNR_rst::OnEraseBkgnd(CDC* pDC)
{
	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	CView_Base::OnEraseBkgnd(pDC);

	pViewMng->DrawArea_Base(pDC, graphics, m_rectBack[0]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[1]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[2]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[3]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[4]);
	/*pViewMng->DrawArea_Base(pDC, graphics, m_rectSetting[0], FALSE);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectSetting[1]);

	/*pViewMng->Draw_Split(pDC, graphics, m_rectSetting[0], DRAW_SPLIT_MODE_BOTTOM);
	pViewMng->Draw_Split(pDC, graphics, m_rectSetting[1], DRAW_SPLIT_MODE_TOP);*/

	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[0], _T("솔루션"), TRUE);
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[1], _T("변전소별 변화량"), TRUE);
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[2], _T("DL별 변화량"), TRUE);
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[3], _T("개폐기 조작 리스트"), TRUE);


	return TRUE;
}


void CView_DNR_rst::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	m_rectBack[0].SetRect(_rect.left, _rect.top, _rect.right, _rect.top + 88);
	m_rectBack[1].SetRect(_rect.left, m_rectBack[0].bottom +10, _rect.right, m_rectBack[0].bottom + 197);
	m_rectBack[2].SetRect(_rect.left, m_rectBack[1].bottom +10, _rect.left +1222, m_rectBack[1].bottom + 313);
	m_rectBack[3].SetRect(_rect.left, m_rectBack[2].bottom +10, _rect.left + 1222, _rect.bottom);
	m_rectBack[4].SetRect(m_rectBack[2].right +10, m_rectBack[1].bottom + 10, _rect.right, _rect.bottom);
	
	MoveSize_Setting();
	MoveSize_List();
}

void CView_DNR_rst::MoveSize_Setting()
{
	if (m_ctrBtn_Check[11].GetSafeHwnd() == NULL || m_ctrBtn[0].GetSafeHwnd() == NULL)							return;

	CRect rect = m_rectBack[0];

	m_rectSetting[0] = rect;
	m_rectSetting[0].right = m_rectSetting[0].left + 235;

	m_rectSetting[1] = m_rectSetting[0];
	m_rectSetting[1].left = m_rectSetting[0].right + 30;
	m_rectSetting[1].right = m_rectSetting[1].left + 664;

	m_rectSetting[2] = m_rectSetting[0];
	m_rectSetting[2].left = m_rectSetting[1].right + 107;
	m_rectSetting[2].right = m_rectSetting[2].left + 200;

	///////////////////
	m_rectCtrl_List[0] = m_rectSetting[0];
	m_rectCtrl_List[0].left += 60;
	m_rectCtrl_List[0].bottom -= 2;
	//////////////////////////////////////////////////////
	rect = m_rectSetting[1];
	rect.InflateRect( 0, -8);
	m_rectCtrl_Check[0] = rect;
	m_rectCtrl_Check[0].left = m_rectCtrl_Check[0].left + 100;
	m_rectCtrl_Check[0].right = m_rectCtrl_Check[0].left + 138;
	m_rectCtrl_Check[0].bottom = m_rectCtrl_Check[0].top + 16;

	m_rectCtrl_Check[1] = m_rectCtrl_Check[0];
	m_rectCtrl_Check[1].left = m_rectCtrl_Check[0].right + 2;
	m_rectCtrl_Check[1].right = m_rectCtrl_Check[1].left + 138;

	m_rectCtrl_Check[2] = m_rectCtrl_Check[0];
	m_rectCtrl_Check[2].left = m_rectCtrl_Check[1].right + 2;
	m_rectCtrl_Check[2].right = m_rectCtrl_Check[2].left + 138;
	////////
	m_rectCtrl_Check[3] = rect;
	m_rectCtrl_Check[3].left = m_rectCtrl_Check[3].left + 100;
	m_rectCtrl_Check[3].right = m_rectCtrl_Check[3].left + 138;
	m_rectCtrl_Check[3].top = m_rectCtrl_Check[3].top + 28;
	m_rectCtrl_Check[3].bottom = m_rectCtrl_Check[3].top + 16;

	m_rectCtrl_Check[4] = m_rectCtrl_Check[3];
	m_rectCtrl_Check[4].left = m_rectCtrl_Check[3].right + 2;
	m_rectCtrl_Check[4].right = m_rectCtrl_Check[4].left + 138;

	m_rectCtrl_Check[5] = m_rectCtrl_Check[3];
	m_rectCtrl_Check[5].left = m_rectCtrl_Check[4].right + 2;
	m_rectCtrl_Check[5].right = m_rectCtrl_Check[5].left + 138;

	m_rectCtrl_Check[6] = m_rectCtrl_Check[3];
	m_rectCtrl_Check[6].left = m_rectCtrl_Check[5].right + 2;
	m_rectCtrl_Check[6].right = m_rectCtrl_Check[6].left + 138;
	////////
	m_rectCtrl_Check[7] = rect;
	m_rectCtrl_Check[7].left = m_rectCtrl_Check[7].left + 100;
	m_rectCtrl_Check[7].right = m_rectCtrl_Check[7].left + 138;
	m_rectCtrl_Check[7].top = m_rectCtrl_Check[7].top + 56;
	m_rectCtrl_Check[7].bottom = m_rectCtrl_Check[7].top + 16;

	m_rectCtrl_Check[8] = m_rectCtrl_Check[7];
	m_rectCtrl_Check[8].left = m_rectCtrl_Check[7].right + 2;
	m_rectCtrl_Check[8].right = m_rectCtrl_Check[8].left + 138;

	m_rectCtrl_Check[9] = m_rectCtrl_Check[7];
	m_rectCtrl_Check[9].left = m_rectCtrl_Check[8].right + 2;
	m_rectCtrl_Check[9].right = m_rectCtrl_Check[9].left + 138;
	//////////////////////////////////////////////////////
	rect = m_rectSetting[2];
	rect.InflateRect(0, -8);
	m_rectCtrl_Check[10] = rect;
	m_rectCtrl_Check[10].left = m_rectCtrl_Check[10].left + 150;
	m_rectCtrl_Check[10].right = m_rectCtrl_Check[10].left + 18;
	m_rectCtrl_Check[10].bottom = m_rectCtrl_Check[10].top + 16;

	m_rectCtrl_Check[11] = rect;
	m_rectCtrl_Check[11].left = m_rectCtrl_Check[11].left + 150;
	m_rectCtrl_Check[11].right = m_rectCtrl_Check[11].left + 18;
	m_rectCtrl_Check[11].top = m_rectCtrl_Check[11].top + 28;
	m_rectCtrl_Check[11].bottom = m_rectCtrl_Check[11].top + 16;

	m_rectCtrl_Combobox[0] = rect;
	m_rectCtrl_Combobox[0].left = m_rectCtrl_Combobox[0].left + 150;
	m_rectCtrl_Combobox[0].right = m_rectCtrl_Combobox[0].left + 100;
	m_rectCtrl_Combobox[0].top = m_rectCtrl_Combobox[0].top + 50;
	m_rectCtrl_Combobox[0].bottom = m_rectCtrl_Combobox[0].top + 16;

	m_ctrCombo[0].MoveWindow(m_rectCtrl_Combobox[0]);

	rect = m_rectBack[0];
	rect.InflateRect(-7, -8);
	m_rectCtrl_Btn[0] = rect;
	m_rectCtrl_Btn[0].left = m_rectCtrl_Btn[0].right - 87;
	m_rectCtrl_Btn[0].bottom = m_rectCtrl_Btn[0].top + 33;



	///////////////////////////////////////////////////////////////////////////////
	m_ctrBtn[0].MoveWindow(m_rectCtrl_Btn[0]);
	
	for(int i = 0 ;i < 12 ; i++)
		m_ctrBtn_Check[i].MoveWindow(m_rectCtrl_Check[i]);

	
	m_ctrList[0].MoveWindow(m_rectCtrl_List[0]);

}

void CView_DNR_rst::MoveSize_List()
{
	if ( m_ctrList[4].GetSafeHwnd() == NULL)							return;

	CRect rect = m_rectBack[1];

	m_rectTitle[0] = rect;
	m_rectTitle[0].right = m_rectTitle[0].left + 78;
	m_rectTitle[0].bottom = m_rectTitle[0].top + 30;

	m_rectCtrl_List[1] = m_rectBack[1];
	m_rectCtrl_List[1].top += 30;
	m_rectCtrl_List[1].bottom -= 2;
	/////////////////////////////////////////////////
	rect = m_rectBack[2];

	m_rectTitle[1] = rect;
	m_rectTitle[1].right = m_rectTitle[1].left + 114;
	m_rectTitle[1].bottom = m_rectTitle[1].top + 30;

	m_rectCtrl_List[2] = m_rectBack[2];
	m_rectCtrl_List[2].top += 30;
	m_rectCtrl_List[2].bottom -= 2;
	/////////////////////////////////////////////////
	rect = m_rectBack[3];

	m_rectTitle[2] = rect;
	m_rectTitle[2].right = m_rectTitle[2].left + 114;
	m_rectTitle[2].bottom = m_rectTitle[2].top + 30;

	m_rectCtrl_List[3] = m_rectBack[3];
	m_rectCtrl_List[3].top += 30;
	m_rectCtrl_List[3].bottom -= 2;
	/////////////////////////////////////////////////
	rect = m_rectBack[4];

	m_rectTitle[3] = rect;
	m_rectTitle[3].right = m_rectTitle[3].left + 158;
	m_rectTitle[3].bottom = m_rectTitle[3].top + 30;

	m_rectCtrl_List[4] = m_rectBack[4];
	m_rectCtrl_List[4].top += 30;
	m_rectCtrl_List[4].bottom -= 2;
	///////////////////////////////////////////////////////////////////////////


	
	m_ctrList[1].MoveWindow(m_rectCtrl_List[1]);
	m_ctrList[2].MoveWindow(m_rectCtrl_List[2]);
	m_ctrList[3].MoveWindow(m_rectCtrl_List[3]);
	m_ctrList[4].MoveWindow(m_rectCtrl_List[4]);

}

void	CView_DNR_rst::Create_ListCtrl()
{
	m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect[2];
	rect[0] = CRect(10, 50, 350, 500);
	m_ctrList[0].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER | LVS_SHOWSELALWAYS, rect[0], this, ID_APP_DNR_LIST_1);
	m_ctrList[0].InsertColumn(0, _T(""), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(1, _T("변전소"), HDF_LEFT, 154);
	m_ctrList[0].InsertColumn(2, _T("idx"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(3, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
	m_ctrList[0].ShowWindow(SW_SHOW);
	m_ctrList[0].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[0].m_HeaderCtrl.SetHeight(1);
	m_ctrList[0].m_HeaderCtrl.SetFlat();
	m_ctrList[0].m_HeaderCtrl.SetFlat();
	m_ctrList[0].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[0].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[0].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[0].SetBgColor(RGB(255, 255, 255));
	m_ctrList[0].SetUnderLine();
	m_ctrList[0].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[0].SetTextFont(&m_listfont);
	m_ctrList[0].SetRowHeight(22);

	m_ctrList[0].m_HeaderCtrl.ShowWindow(SW_HIDE);
	m_ctrList[0].SetCheckBox_Bitmap(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	rect[1] = CRect(10, 50, 350, 500);
	m_ctrList[1].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_DNR_LIST_2);
	m_ctrList[1].InsertColumn(0, _T("솔루션"), HDF_CENTER				, 100);
	m_ctrList[1].InsertColumn(1, _T("손실"), HDF_CENTER, 158);
	m_ctrList[1].InsertColumn(2, _T("손실변화량"), HDF_CENTER, 158);
	m_ctrList[1].InsertColumn(3, _T("피더밸런스"), HDF_CENTER, 158); ////// 스크롤바 21
	m_ctrList[1].InsertColumn(4, _T("밸런스변화량"), HDF_CENTER, 158);
	m_ctrList[1].InsertColumn(5, _T("복합지수"), HDF_CENTER, 158);
	m_ctrList[1].InsertColumn(6, _T("복합지수 변화량"), HDF_CENTER, 158);
	m_ctrList[1].InsertColumn(7, _T("최대전압 위배량"), HDF_CENTER, 158);
	m_ctrList[1].InsertColumn(8, _T("최대전압 위배수"), HDF_CENTER, 158);
	m_ctrList[1].InsertColumn(9, _T("선로용량 위배량"), HDF_CENTER, 158);
	m_ctrList[1].InsertColumn(10, _T("위배용량 선로수"), HDF_CENTER, 158);
	m_ctrList[1].InsertColumn(11, _T("이동개폐기수"), HDF_CENTER, 158);
	m_ctrList[1].InsertColumn(12, _T("dump"), HDF_CENTER, 0);
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

	rect[1] = CRect(10, 50, 350, 500);
	m_ctrList[2].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_DNR_LIST_3);
	m_ctrList[2].InsertColumn(0, _T("변전소"), HDF_LEFT, 120);
	m_ctrList[2].InsertColumn(1, _T("부하량"), HDF_LEFT, 154);
	m_ctrList[2].InsertColumn(2, _T("밸런스"), HDF_LEFT, 154); ////// 스크롤바 21
	m_ctrList[2].InsertColumn(3, _T("복합지수"), HDF_LEFT, 154);
	m_ctrList[2].InsertColumn(4, _T("최대전압 위배량"), HDF_LEFT, 154);
	m_ctrList[2].InsertColumn(5, _T("전압위배 노드수"), HDF_LEFT, 154);
	m_ctrList[2].InsertColumn(6, _T("선로용량 위배량"), HDF_LEFT, 154);
	m_ctrList[2].InsertColumn(7, _T("위배용량 선로수"), HDF_LEFT, 154);
	m_ctrList[2].InsertColumn(8, _T("idx"), HDF_LEFT, 0);
	m_ctrList[2].InsertColumn(9, _T("dump"), HDF_LEFT, 0);
	m_ctrList[2].ShowWindow(SW_SHOW);
	m_ctrList[2].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SINGLEROW);
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
	m_ctrList[2].SetCheckBox_Bitmap(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	rect[1] = CRect(10, 50, 350, 500);
	m_ctrList[3].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_DNR_LIST_4);
	m_ctrList[3].InsertColumn(0, _T("변전소"), HDF_LEFT, 100);
	m_ctrList[3].InsertColumn(1, _T("주변압기"), HDF_LEFT, 80);
	m_ctrList[3].InsertColumn(2, _T("DL"), HDF_LEFT, 80); ////// 스크롤바 21
	m_ctrList[3].InsertColumn(3, _T("부하량"), HDF_LEFT, 85);
	m_ctrList[3].InsertColumn(4, _T("부하변화량"), HDF_LEFT, 85);
	m_ctrList[3].InsertColumn(5, _T("손실"), HDF_LEFT, 85);
	m_ctrList[3].InsertColumn(6, _T("손실변화량"), HDF_LEFT, 90);
	m_ctrList[3].InsertColumn(7, _T("최대전압 위배량"), HDF_LEFT, 150);
	m_ctrList[3].InsertColumn(8, _T("전압위대 노드수"), HDF_LEFT, 140);
	m_ctrList[3].InsertColumn(9, _T("선로용량 위배량"), HDF_LEFT, 150);
	m_ctrList[3].InsertColumn(10, _T("위배용량 선로수"), HDF_LEFT, 140);
	m_ctrList[3].InsertColumn(11, _T("idx"), HDF_LEFT, 0);
	m_ctrList[3].InsertColumn(12, _T("dump"), HDF_LEFT, 0);
	m_ctrList[3].ShowWindow(SW_SHOW);
	m_ctrList[3].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SINGLEROW);
	m_ctrList[3].m_HeaderCtrl.SetHeight(27);
	m_ctrList[3].m_HeaderCtrl.SetFlat();
	m_ctrList[3].m_HeaderCtrl.SetFlat();
	m_ctrList[3].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[3].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[3].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[3].SetBgColor(RGB(255, 255, 255));
	m_ctrList[3].SetUnderLine();
	m_ctrList[3].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[3].SetTextFont(&m_listfont);
	m_ctrList[3].SetRowHeight(25);
	m_ctrList[3].SetCheckBox_Bitmap(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	rect[1] = CRect(10, 50, 350, 500);
	m_ctrList[4].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_DNR_LIST_5);
	m_ctrList[4].InsertColumn(0, _T("순서"), HDF_LEFT, 50);
	//m_ctrList[4].InsertColumn(1, _T("개폐기명"), HDF_LEFT, 210);
	m_ctrList[4].InsertColumn(1, _T("닫힘"), HDF_LEFT, 160);
	m_ctrList[4].InsertColumn(2, _T("열림"), HDF_LEFT, 160); ////// 스크롤바 21
	m_ctrList[4].InsertColumn(3, _T("루프선로1"), HDF_LEFT, 90);
	m_ctrList[4].InsertColumn(4, _T("루프선로2"), HDF_LEFT, 90);
	m_ctrList[4].InsertColumn(5, _T("루프구분"), HDF_LEFT, 80);
	m_ctrList[4].InsertColumn(6, _T("idx1"), HDF_LEFT, 0);
	m_ctrList[4].InsertColumn(7, _T("idx2"), HDF_LEFT, 0);
	m_ctrList[4].InsertColumn(8, _T("dump"), HDF_LEFT, 0);
	m_ctrList[4].ShowWindow(SW_SHOW);
	m_ctrList[4].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SINGLEROW);
	m_ctrList[4].m_HeaderCtrl.SetHeight(27);
	m_ctrList[4].m_HeaderCtrl.SetFlat();
	m_ctrList[4].m_HeaderCtrl.SetFlat();
	m_ctrList[4].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[4].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[4].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[4].SetBgColor(RGB(255, 255, 255));
	m_ctrList[4].SetUnderLine();
	m_ctrList[4].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[4].SetTextFont(&m_listfont);
	m_ctrList[4].SetRowHeight(25);
	m_ctrList[4].SetCheckBox_Bitmap(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	/*m_ctrList[1].ShowWindow(SW_HIDE);
	m_ctrList[2].ShowWindow(SW_HIDE);
	m_ctrList[3].ShowWindow(SW_HIDE);
	m_ctrList[4].ShowWindow(SW_HIDE);*/

	/*m_ctrList[0].InsertItem(0, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].InsertItem(1, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].InsertItem(2, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].InsertItem(3, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].InsertItem(4, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

	m_ctrList[0].SetItemText(0, 1, _T("SS 변전소 1"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].SetItemText(1, 1, _T("SS 변전소 2"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].SetItemText(2, 1, _T("SS 변전소 3"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].SetItemText(3, 1, _T("SS 변전소 4"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].SetItemText(4, 1, _T("SS 변전소 5"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

	m_ctrList[0].SetCheckBox(0, 0, CHECKBOX_NORMAL);
	m_ctrList[0].SetCheckBox(1, 0, CHECKBOX_NORMAL);
	m_ctrList[0].SetCheckBox(2, 0, CHECKBOX_NORMAL);
	m_ctrList[0].SetCheckBox(3, 0, CHECKBOX_NORMAL);
	m_ctrList[0].SetCheckBox(4, 0, CHECKBOX_NORMAL);*/
}

void CView_DNR_rst::Create_Combobox()
{
	m_font_Combobox.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	if (!m_ctrCombo[0].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_DNR_COMBO_1))
	{
		AfxMessageBox(_T("Create DNR ComboBox Fail.\n"));
		return;
	}
	

	m_ctrCombo[0].SetTextFont(&m_font_Combobox);

	m_ctrCombo[0].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	
	m_ctrCombo[0].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	

	m_ctrCombo[0].SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	m_ctrCombo[0].SetDropDownHeight(10);

}


void	CView_DNR_rst::Create_Btn()
{
	m_rectCtrl_Btn[0] = CRect(10, 20, 90, 250);
	if (!m_ctrBtn[0].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_rectCtrl_Btn[0], this, ID_APP_DNR_BTN_1))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_ctrBtn[0].SetBitmapID(IDB_PCE_RUN_NOR, IDB_PCE_RUN_CLK, IDB_PCE_RUN_OVR);

	m_font_check.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	//////////////////////////////////////////// 표시결과
	CRect rect = CRect(10, 20, 90, 250);
	if (!m_ctrBtn_Check[0].Create(_T("손실최소화"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_1))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[1].Create(_T("Feeder Balancing"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_2))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[2].Create(_T("전압/용량 위배 해소"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_3))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[3].Create(_T("전일 최대 부하"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_4))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[4].Create(_T("전월 최대 부하"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_5))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[5].Create(_T("하계 최대 부하"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_6))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[6].Create(_T("동계 최대 부하"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_7))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[7].Create(_T("CB"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_8))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[8].Create(_T("자동"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_9))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[9].Create(_T("수동"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_10))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[10].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_11))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[11].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_DNR_BTN_CHECK_12))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	for (int i = 0; i < 12; i++)
	{
		m_ctrBtn_Check[i].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
		m_ctrBtn_Check[i].m_pFont_Text = &m_font_check;
		m_ctrBtn_Check[i].m_colorBg = RGB(255, 255, 255);
	//	m_ctrBtn_Check[i].SetCheckButton(CHECKBOX_CHECKED);
	}
		
}

void CView_DNR_rst::OnControlbutton_click_Run()
{
	if (m_bTimer)
		return;

	CView_DNR_rst_SSDlg Dlg;

	if (Dlg.DoModal() == IDCANCEL)
		return;

	m_ctrList[0].DeleteAllItems();
	
	CString strName, strIdx;
	int nIdx, nCheck;
	
	for (int i = 0; i < Dlg.m_Array_SS.GetCount(); i++)
	{
		strName = Dlg.m_Array_SS.GetAt(i);
		nIdx = Dlg.m_Array_SS_idx.GetAt(i);

		nCheck = GETVALUE(int, _T("ss_dyn_uin"), _T("SS_DNRFLAG"), nIdx);

		strIdx.Format(_T("%d"), nIdx);

		m_ctrList[0].InsertItem(i, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(i, 1, strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(i, 2, strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

	//	m_ctrList[0].SetCheckBox(i, 0, CHECKBOX_CHECKED);
	}

		///////////////////////////////////////////////////
	int nDNR_opt = 0;
	int nDNR_swtype[3]= { 0., };
	int nDNR_load = 0;
	int nDNR_ssmove = 0;
	int nDNR_rcmove = 0;
	int nDNR_swoper = 0;


	for (int i = 0; i < 3; i++)
	{
		nCheck = m_ctrBtn_Check[i].GetCheckButton();
		if (nCheck == 1)
		{
			nDNR_opt = i+ 1;
		}
			
	}

	if (nDNR_opt == 0)
	{
		AfxMessageBox(_T("재구성 목적을 선택하세요"));
		return;
	}


	for (int i = 3; i < 7; i++)
	{
		nCheck = m_ctrBtn_Check[i].GetCheckButton();
		if (nCheck == 1)
		{
			nDNR_load = i - 2;
		}

	}

	if (nDNR_load == 0)
	{
		AfxMessageBox(_T("재구성 목적을 선택하세요"));
		return;
	}

	nDNR_swtype[0] = m_ctrBtn_Check[7].GetCheckButton();
	nDNR_swtype[1] = m_ctrBtn_Check[8].GetCheckButton();
	nDNR_swtype[2] = m_ctrBtn_Check[9].GetCheckButton();

	nDNR_ssmove = m_ctrBtn_Check[10].GetCheckButton();
	nDNR_rcmove = m_ctrBtn_Check[11].GetCheckButton();

	nDNR_swoper = m_ctrCombo[0].GetCurSel();
	
	PUTDOUBLE2VALUE(_T("dnropt_dyn_uin"), _T("dnropt_object"), 1, (double)nDNR_opt);
	PUTDOUBLE2VALUE(_T("dnropt_dyn_uin"), _T("dnropt_load_type"), 1, (double)nDNR_load);
	PUTDOUBLE2VALUE(_T("dnropt_dyn_uin"), _T("dnropt_cben"), 1, (double)nDNR_swtype[0]);
	PUTDOUBLE2VALUE(_T("dnropt_dyn_uin"), _T("dnropt_gaen"), 1, (double)nDNR_swtype[1]);
	PUTDOUBLE2VALUE(_T("dnropt_dyn_uin"), _T("dnropt_maen"), 1, (double)nDNR_swtype[2]);
	PUTDOUBLE2VALUE(_T("dnropt_dyn_uin"), _T("dnropt_ss_move_en"), 1, (double)nDNR_ssmove);
	PUTDOUBLE2VALUE(_T("dnropt_dyn_uin"), _T("dnropt_rc_move_en"), 1, (double)nDNR_rcmove);
	PUTDOUBLE2VALUE(_T("dnropt_dyn_uin"), _T("dnropt_max_chgsw"), 1, (double)nDNR_swoper);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("10"),GetVIewID());
	//pDataMng->Excute_Appl(_T("8/9"));

	m_bTimer = TRUE;
	m_nCompAppl_ID = 10;
	SetTimer(1, 100, NULL);

}


void CView_DNR_rst::UpdateList1()
{
	m_ctrList[1].DeleteAllItems();
	m_ctrList[2].DeleteAllItems();
	m_ctrList[3].DeleteAllItems();
	m_ctrList[4].DeleteAllItems();

	CString strName[4] = { _T("초기"),_T("1") ,_T("2") ,_T("3") };
	CString strData[11];
	double dValue[8];
	int	   nValue[3];

	for (int i = 1; i < 5; i++)
	{
		dValue[0] = GETVALUE(double, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_LOSS"), i);
		dValue[1] = GETVALUE(double, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_DLOSS"), i);
		dValue[2] = GETVALUE(double, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_BALANCE"), i);
		dValue[3] = GETVALUE(double, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_DBALANCE"), i);
		dValue[4] = GETVALUE(double, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_COMBI"), i);
		dValue[5] = GETVALUE(double, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_DCOMBI"), i);
		dValue[6] = GETVALUE(double, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_MAX_VOLTVIO"), i);
		dValue[7] = GETVALUE(double, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_MAX_MWVIO"), i);

		nValue[0] = GETVALUE(int, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_COUNT_VOLTVIO"), i);
		nValue[1] = GETVALUE(int, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_COUNT_MWVIO"), i);
		nValue[2] = GETVALUE(int, _T("DNRRESLT_DYN_DNRO"), _T("DNR_RESLT_SWCHGD"), i);

		strData[0].Format(_T("%.4lf"), dValue[0]);
		strData[1].Format(_T("%.4lf"), dValue[1]);
		strData[2].Format(_T("%.4lf"), dValue[2]);
		strData[3].Format(_T("%.4lf"), dValue[3]);
		strData[4].Format(_T("%.4lf"), dValue[4]);
		strData[5].Format(_T("%.4lf"), dValue[5]);
		strData[6].Format(_T("%.4lf"), dValue[6]);
		strData[7].Format(_T("%d"), nValue[0]);
		strData[8].Format(_T("%.4lf"), dValue[7]);
		strData[9].Format(_T("%d"), nValue[1]);
		strData[10].Format(_T("%d"), nValue[2]);


		m_ctrList[1].InsertItem(i - 1, strName[i-1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 1, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 2, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 3, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 4, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 5, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 6, strData[5], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 7, strData[6], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 8, strData[7], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 9, strData[8], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 10, strData[9], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(i - 1, 11, strData[10], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		
	}


}

void CView_DNR_rst::GetCheckList_SS(CIntArray *pArray_Idx)
{
	CString strSSIdx;
	int nSSIdx;
	for (int i = 0; i < m_ctrList[0].GetItemCount() ; i++)
	{
		if (m_ctrList[0].GetCheckBox(i, 0) == CHECKBOX_CHECKED)
		{
			strSSIdx = m_ctrList[0].GetItemText(i, 2);
			nSSIdx = _wtoi(strSSIdx);
			pArray_Idx->Add(nSSIdx);
		}
	}
}

void CView_DNR_rst::OnListCtrlClick_2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	if (nRow < 1 || nRow > 3)
		return;

	UpdateList2(nRow);
	UpdateList3(nRow);
	UpdateList4(nRow);
}

void CView_DNR_rst::UpdateList2(int nSol_Idx)
{
	m_ctrList[2].DeleteAllItems();

	CString strColName[7] = { _T("SS_SOL%dRESLT_LOSS") ,_T("SS_SOL%dRESLT_BALANCE") ,_T("SS_SOL%dRESLT_COMBI") ,_T("SS_SOL%dRESLT_MAX_VOLTVIO")
							,_T("SS_SOL%dRESLT_COUNT_VOLTVIO") ,_T("SS_SOL%dRESLT_MAX_MWVIO") ,_T("SS_SOL%dRESLT_COUNT_MWVIO") };

	for (int i = 0; i < 7; i++)
	{
		strColName[i].Format(strColName[i], nSol_Idx);
	}

	CString strData[8];
	double dValue[5];
	int	   nValue[2];
	
	CIntArray Array_SS_Idx;
	GetCheckList_SS(&Array_SS_Idx);

	int nSS_Idx;
	for (int i = 0; i < Array_SS_Idx.GetSize(); i++)
	{
		nSS_Idx = Array_SS_Idx.GetAt(i);
		
		dValue[0] = GETVALUE(double, _T("SS_DYN_DNRO"), strColName[0].GetBuffer(), nSS_Idx);
		dValue[1] = GETVALUE(double, _T("SS_DYN_DNRO"), strColName[1].GetBuffer(), nSS_Idx);
		dValue[2] = GETVALUE(double, _T("SS_DYN_DNRO"), strColName[2].GetBuffer(), nSS_Idx);
		dValue[3] = GETVALUE(double, _T("SS_DYN_DNRO"), strColName[3].GetBuffer(), nSS_Idx);
		nValue[0] = GETVALUE(int, _T("SS_DYN_DNRO"), strColName[4].GetBuffer(), nSS_Idx);
		dValue[4] = GETVALUE(double, _T("SS_DYN_DNRO"), strColName[5].GetBuffer(), nSS_Idx);
		nValue[1] = GETVALUE(int, _T("SS_DYN_DNRO"), strColName[6].GetBuffer(), nSS_Idx);
		
		strData[0] = CA2W( GETSTRING(("SS_STA"), ("SS_NM"), nSS_Idx) ).m_psz;

		strData[1].Format(_T("%.4lf"), dValue[0]);
		strData[2].Format(_T("%.4lf"), dValue[1]);
		strData[3].Format(_T("%.4lf"), dValue[2]);
		strData[4].Format(_T("%.4lf"), dValue[3]);
		strData[5].Format(_T("%d"), nValue[0]);
		strData[6].Format(_T("%.4lf"), dValue[4]);
		strData[7].Format(_T("%d"), nValue[1]);
		
		m_ctrList[2].InsertItem(i ,  strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(i, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(i, 2, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(i, 3, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(i, 4, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(i, 5, strData[5], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(i, 6, strData[6], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(i, 7, strData[7], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	}
	

}

void CView_DNR_rst::UpdateList3(int nSol_Idx)
{
	m_ctrList[3].DeleteAllItems();
	CString strColName[8] = { _T("DL_SOL%dRESLT_LOAD_MW") ,_T("DL_SOL%dRESLT_DE_LOAD_MW") ,_T("DL_SOL%dRESLT_LOSS_MW") ,_T("DL_SOL%dRESLT_DE_LOSS")
							,_T("DL_SOL%dRESLT_PU_VVIO") ,_T("DL_SOL%dRESLT_COUNT_VVIO") ,_T("DL_SOL%dRESLT_MW_OVLOAD"),_T("DL_SOL%dRESLT_COUNT_OVLOAD") };

	for (int i = 0; i < 8; i++)
	{
		strColName[i].Format(strColName[i], nSol_Idx);
	}

	CString strData[11];
	double dValue[6];
	int	   nValue[2];

	CIntArray Array_SS_Idx;
	GetCheckList_SS(&Array_SS_Idx);

	CStringArray Array_MTR,Array_DL;
	CIntArray Array_DL_Idx;

	CDataManager* pDataMng = CDataManager::Instance();

	int nSS_Idx, nDL_Idx;
	for (int i = 0; i < Array_SS_Idx.GetSize(); i++)
	{
		nSS_Idx = Array_SS_Idx.GetAt(i);

		strData[0] = CA2W(GETSTRING(("SS_STA"), ("SS_NM"), nSS_Idx)).m_psz;
		pDataMng->GetMTRName_array(strData[0], &Array_MTR);
		for (int k = 0; k < Array_MTR.GetSize(); k++)
		{
			strData[1] = Array_MTR.GetAt(k);

			pDataMng->GetDLName_array(strData[0], &Array_DL, strData[1], &Array_DL_Idx);

			for (int m = 0; m < Array_DL.GetSize(); m++)
			{
				strData[2] = Array_DL.GetAt(m);
				nDL_Idx = Array_DL_Idx.GetAt(m);
			

				dValue[0] = GETVALUE(double, _T("DL_DYN_DNRO"), strColName[0].GetBuffer(), nDL_Idx);
				dValue[1] = GETVALUE(double, _T("DL_DYN_DNRO"), strColName[1].GetBuffer(), nDL_Idx);
				dValue[2] = GETVALUE(double, _T("DL_DYN_DNRO"), strColName[2].GetBuffer(), nDL_Idx);
				dValue[3] = GETVALUE(double, _T("DL_DYN_DNRO"), strColName[3].GetBuffer(), nDL_Idx);
				dValue[4] = GETVALUE(double, _T("DL_DYN_DNRO"), strColName[4].GetBuffer(), nDL_Idx);
				nValue[0] = GETVALUE(int, _T("DL_DYN_DNRO"), strColName[5].GetBuffer(), nDL_Idx);
				dValue[5] = GETVALUE(double, _T("DL_DYN_DNRO"), strColName[6].GetBuffer(), nDL_Idx);
				nValue[1] = GETVALUE(int, _T("DL_DYN_DNRO"), strColName[7].GetBuffer(), nDL_Idx);

				strData[3].Format(_T("%.4lf"), dValue[0]);
				strData[4].Format(_T("%.4lf"), dValue[1]);
				strData[5].Format(_T("%.4lf"), dValue[2]);
				strData[6].Format(_T("%.4lf"), dValue[3]);
				strData[7].Format(_T("%.4lf"), dValue[4]);
				strData[8].Format(_T("%d"), nValue[0]);
				strData[9].Format(_T("%.4lf"), dValue[5]);
				strData[10].Format(_T("%d"), nValue[1]);

				m_ctrList[3].InsertItem(m_ctrList[3].GetItemCount(), strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 2, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 3, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 4, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 5, strData[5], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 6, strData[6], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 7, strData[7], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 8, strData[8], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 9, strData[9], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
				m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 10, strData[10], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			}
		}	
	}
}

void CView_DNR_rst::UpdateList4(int nSol_Idx)
{
	m_ctrList[4].DeleteAllItems();
	CString strColName[5] = { _T("DNRSWCMD_SOL%d_CLOSE_II_CBSW") ,_T("DNRSWCMD_SOL%d_OPEN_II_CBSW") ,_T("DNRSWCMD_SOL%d_II_DL1")
							,_T("DNRSWCMD_SOL%d_II_DL2")	,_T("DNRSWCMD_SOL%d_CONTYPE")};

	for (int i = 0; i < 5; i++)
	{
		strColName[i].Format(strColName[i], nSol_Idx);
	}

	CString strData[6];
	int	   nValue[5];

	int					nCount(theAppDataMng->GetTableMaxCount("DNRSWCMD_DYN_DNRO"));
	for (int i = 1; i <= nCount; i++)
	{
		nValue[0] = GETVALUE(int, _T("DNRSWCMD_DYN_DNRO"), strColName[0].GetBuffer(), i);
		if(nValue[0] == 0)
			break;

		nValue[1] = GETVALUE(int, _T("DNRSWCMD_DYN_DNRO"), strColName[1].GetBuffer(), i);
		nValue[2] = GETVALUE(int, _T("DNRSWCMD_DYN_DNRO"), strColName[2].GetBuffer(), i);
		nValue[3] = GETVALUE(int, _T("DNRSWCMD_DYN_DNRO"), strColName[3].GetBuffer(), i);
		nValue[4] = GETVALUE(int, _T("DNRSWCMD_DYN_DNRO"), strColName[4].GetBuffer(), i);

		strData[0].Format(_T("%d"), i);

		strData[1] = CA2W(GETSTRING(("cbsw_sta"), ("cbsw_nm"), nValue[0])).m_psz;
		strData[2] = CA2W(GETSTRING(("cbsw_sta"), ("cbsw_nm"), nValue[1])).m_psz;
		strData[3] = CA2W(GETSTRING(("dl_sta"), ("dl_nm"), nValue[2])).m_psz;
		strData[4] = CA2W(GETSTRING(("dl_sta"), ("dl_nm"), nValue[3])).m_psz;

		strData[5].Empty();
		if (nValue[4] == 1)
			strData[5] = _T("DL내부");
		else if (nValue[4] == 2)
			strData[5] = _T("SS내부");
		else if (nValue[4] == 3)
			strData[5] = _T("SS외부");

		m_ctrList[4].InsertItem(m_ctrList[4].GetItemCount(), strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 2, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 3, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 4, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 5, strData[5], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	}


}
//////////////////////////////

void CView_DNR_rst::OnControlbutton_click_Check1()
{
	int nCheck = m_ctrBtn_Check[0].GetCheckButton();

	if (nCheck == CHECKBOX_CHECKED)
	{
		m_ctrBtn_Check[1].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[2].SetCheckButton(CHECKBOX_NORMAL);
	}
	
	m_ctrBtn_Check[0].RedrawWindow();
	m_ctrBtn_Check[1].RedrawWindow();
	m_ctrBtn_Check[2].RedrawWindow();
}

void CView_DNR_rst::OnControlbutton_click_Check2()
{
	int nCheck = m_ctrBtn_Check[1].GetCheckButton();

	if (nCheck == CHECKBOX_CHECKED)
	{
		m_ctrBtn_Check[0].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[2].SetCheckButton(CHECKBOX_NORMAL);
	}

	m_ctrBtn_Check[0].RedrawWindow();
	m_ctrBtn_Check[1].RedrawWindow();
	m_ctrBtn_Check[2].RedrawWindow();
}

void CView_DNR_rst::OnControlbutton_click_Check3()
{
	int nCheck = m_ctrBtn_Check[2].GetCheckButton();

	if (nCheck == CHECKBOX_CHECKED)
	{
		m_ctrBtn_Check[0].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[1].SetCheckButton(CHECKBOX_NORMAL);
	}

	m_ctrBtn_Check[0].RedrawWindow();
	m_ctrBtn_Check[1].RedrawWindow();
	m_ctrBtn_Check[2].RedrawWindow();
}
////////////////////////////////
void CView_DNR_rst::OnControlbutton_click_Check4()
{
	int nCheck = m_ctrBtn_Check[3].GetCheckButton();

	if (nCheck == CHECKBOX_CHECKED)
	{
		m_ctrBtn_Check[4].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[5].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[6].SetCheckButton(CHECKBOX_NORMAL);
	}

	m_ctrBtn_Check[3].RedrawWindow();
	m_ctrBtn_Check[4].RedrawWindow();
	m_ctrBtn_Check[5].RedrawWindow();
	m_ctrBtn_Check[6].RedrawWindow();
}

void CView_DNR_rst::OnControlbutton_click_Check5()
{
	int nCheck = m_ctrBtn_Check[4].GetCheckButton();

	if (nCheck == CHECKBOX_CHECKED)
	{
		m_ctrBtn_Check[3].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[5].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[6].SetCheckButton(CHECKBOX_NORMAL);
	}

	m_ctrBtn_Check[3].RedrawWindow();
	m_ctrBtn_Check[4].RedrawWindow();
	m_ctrBtn_Check[5].RedrawWindow();
	m_ctrBtn_Check[6].RedrawWindow();
}

void CView_DNR_rst::OnControlbutton_click_Check6()
{
	int nCheck = m_ctrBtn_Check[5].GetCheckButton();

	if (nCheck == CHECKBOX_CHECKED)
	{
		m_ctrBtn_Check[3].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[4].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[6].SetCheckButton(CHECKBOX_NORMAL);
	}

	m_ctrBtn_Check[3].RedrawWindow();
	m_ctrBtn_Check[4].RedrawWindow();
	m_ctrBtn_Check[5].RedrawWindow();
	m_ctrBtn_Check[6].RedrawWindow();
}

void CView_DNR_rst::OnControlbutton_click_Check7()
{
	int nCheck = m_ctrBtn_Check[6].GetCheckButton();

	if (nCheck == CHECKBOX_CHECKED)
	{
		m_ctrBtn_Check[3].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[4].SetCheckButton(CHECKBOX_NORMAL);
		m_ctrBtn_Check[5].SetCheckButton(CHECKBOX_NORMAL);
	}

	m_ctrBtn_Check[3].RedrawWindow();
	m_ctrBtn_Check[4].RedrawWindow();
	m_ctrBtn_Check[5].RedrawWindow();
	m_ctrBtn_Check[6].RedrawWindow();
}

void CView_DNR_rst::recv_Appl(int nAppl)
{
	if (!m_bTimer)
		return;

	m_nRecvAppl_ID = nAppl;

	if (m_nCompAppl_ID == nAppl)
	{
		m_bTimer = FALSE;
	}
}
void CView_DNR_rst::recv_Init()
{
	m_bTimer = FALSE;
	KillTimer(1);
}

void CView_DNR_rst::OnTimer(UINT_PTR nIDEvent)
{
	
	if (!m_bTimer)
	{
		KillTimer(nIDEvent);
		if (nIDEvent == 1)
		{
			Sleep(500);
			UpdateList1();
		}

		RedrawWindow();
	}

	CView_Base::OnTimer(nIDEvent);
}
