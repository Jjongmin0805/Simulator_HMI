#include "pch.h"
#include "CView_PDVR_rst.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"
#include "../DataManager/CDataManager.h"
#include "resource.h"
#include "CView_PDVR_rst_TRDlg.h"
#include "CView_PDVR_rst_DGDlg.h"
#include "XLSAutomation.h"
#include "CView_PDVR_rst_RUN_Dlg.h"


CView_PDVR_rst::CView_PDVR_rst()
{
	m_nMode = -1;
	m_bTimer = FALSE;

	m_nCompAppl_ID = -1;
	m_nRecvAppl_ID = -1;
}

CView_PDVR_rst::~CView_PDVR_rst()
{
	Delete_GraphData();
}

BEGIN_MESSAGE_MAP(CView_PDVR_rst, CView_Base)
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_APP_PDVR_BTN_1, &CView_PDVR_rst::OnControlbutton_click_Run_PDVR)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_2, &CView_PDVR_rst::OnControlbutton_click_Opt)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_3, &CView_PDVR_rst::OnControlbutton_click_Rpt)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_4, &CView_PDVR_rst::OnControlbutton_click_Cal)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_5, &CView_PDVR_rst::OnControlbutton_click_Run_PCE)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_6, &CView_PDVR_rst::OnControlbutton_click_Search1)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_7, &CView_PDVR_rst::OnControlbutton_click_Search2)
	ON_CBN_SELCHANGE(ID_APP_PDVR_COMBO_1, &CView_PDVR_rst::OnPDVR_rstCombo1SelectChange)
	ON_CBN_SELCHANGE(ID_APP_PDVR_COMBO_2, &CView_PDVR_rst::OnPDVR_rstCombo2SelectChange)
	ON_CBN_SELCHANGE(ID_APP_PDVR_COMBO_3, &CView_PDVR_rst::OnPDVR_rstCombo3SelectChange)
	ON_CBN_SELCHANGE(ID_APP_PDVR_COMBO_4, &CView_PDVR_rst::OnPDVR_rstCombo4SelectChange)
	ON_NOTIFY(NM_CLICK, ID_APP_PDVR_LIST_1, &CView_PDVR_rst::OnPDVR_ListCtrlClick_1)
	ON_NOTIFY(NM_DBLCLK, ID_APP_PDVR_LIST_1, &CView_PDVR_rst::OnPDVR_ListCtrlDBClick_1)
	ON_NOTIFY(NM_DBLCLK, ID_APP_PDVR_LIST_2, &CView_PDVR_rst::OnPDVR_ListCtrlDBClick_2)
	ON_NOTIFY(NM_DBLCLK, ID_APP_PDVR_LIST_7, &CView_PDVR_rst::OnPDVR_ListCtrlDBClick_7)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_MSG_CTRL_EVENT, &CView_PDVR_rst::OnList2Ctrl_ComboMsg)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_CHECK_1, &CView_PDVR_rst::OnControlbutton_click_Check1)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_CHECK_2, &CView_PDVR_rst::OnControlbutton_click_Check2)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_CHECK_3, &CView_PDVR_rst::OnControlbutton_click_Check3)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_CHECK_4, &CView_PDVR_rst::OnControlbutton_click_Check4)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_CHECK_5, &CView_PDVR_rst::OnControlbutton_click_Check5)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_CHECK_6, &CView_PDVR_rst::OnControlbutton_click_Check6)
	ON_BN_CLICKED(ID_APP_PDVR_BTN_CHECK_7, &CView_PDVR_rst::OnControlbutton_click_Check7)
	//ON_NOTIFY(HDN_ITEMCLICK, ID_APP_PDVR_LIST_2, &CView_PDVR_rst::OnHdnItemclickList_2)
	ON_NOTIFY(LVN_COLUMNCLICK, ID_APP_PDVR_LIST_2, &CView_PDVR_rst::OnHdnItemclickList_2)
	ON_NOTIFY(LVN_COLUMNCLICK, ID_APP_PDVR_LIST_7, &CView_PDVR_rst::OnHdnItemclickList_7)
	//ON_NOTIFY(HDN_ITEMCLICK, ID_APP_PDVR_LIST_7, &CView_PDVR_rst::OnHdnItemclickList_7)
	ON_NOTIFY(NM_DBLCLK, ID_APP_PDVR_LIST_4, &CView_PDVR_rst::OnPDVR_ListCtrlDBClick_4)
	ON_NOTIFY(NM_DBLCLK, ID_APP_PDVR_LIST_5, &CView_PDVR_rst::OnPDVR_ListCtrlDBClick_5)
	ON_NOTIFY(NM_DBLCLK, ID_APP_PDVR_LIST_6, &CView_PDVR_rst::OnPDVR_ListCtrlDBClick_6)
END_MESSAGE_MAP()

void CView_PDVR_rst::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	Create_Combobox();
	Create_ListCtrl();
	Create_Btn();
	Create_DateTimeCtrl();
	Create_Edit();
	Create_Btn_Check();

	/////////////////
	m_ImageList.Create(16, 16, ILC_COLOR32, 1, 1);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_CHECK_CHECK);
	m_ImageList.Add(&bmp, RGB(0, 0, 0));
	m_ctrList[1].SetImageList(&m_ImageList, LVSIL_NORMAL);
//	test_option_data();
}

void CView_PDVR_rst::InitData()
{
	m_ctrCombo[0].ResetContent();
	m_ctrCombo[1].ResetContent();
	m_ctrCombo[2].ResetContent();
	m_ctrCombo[3].ResetContent();

	Update_Combo1();

	CTime t;
	m_ctrDate[1].GetTime(t);
	int nDay = t.GetDay();
	t -= CTimeSpan(nDay, 0, 0, 0);
	m_ctrDate[1].SetTime(&t);
	t -= CTimeSpan(365, 0, 0, 0);
	m_ctrDate[0].SetTime(&t);

	m_dVVM_lmhi = 1.02;// GETVALUE(double, _T("vvm_dyn_uin"), _T("vvm_lmhi"), 1);
	m_dVVM_lmlo = 0.96;// GETVALUE(double, _T("vvm_dyn_uin"), _T("vvm_lmlo"), 1);
	m_dVVM_lmhi_Tap = 0.975;// GETVALUE(double, _T("vvm_dyn_uin"), _T("vvm_lmhi"), 1);
	m_dVVM_lmlo_Tap = 0.91;// GETVALUE(double, _T("vvm_dyn_uin"), _T("vvm_lmlo"), 1);


	m_ctrList[0].DeleteAllItems();
	m_ctrList[1].DeleteAllItems();
	m_ctrList[2].DeleteAllItems();
	m_ctrList[3].DeleteAllItems();
	m_ctrList[4].DeleteAllItems();
	m_ctrList[5].DeleteAllItems();
	m_ctrList[6].DeleteAllItems();
	m_ctrList[7].DeleteAllItems();

	Delete_GraphData();
}

BOOL CView_PDVR_rst::OnEraseBkgnd(CDC* pDC)
{
	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	CView_Base::OnEraseBkgnd(pDC);

	pViewMng->DrawArea_Base(pDC, graphics, m_rectBack[0]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[1]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[2]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[3]);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectPDVR[0], FALSE);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectPDVR[3], FALSE);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectPDVR[1], FALSE);
//	pViewMng->DrawArea_Base(pDC, graphics, m_rectPCE[0], FALSE);

	pViewMng->Draw_Split(pDC, graphics, m_rectPDVR[0], DRAW_SPLIT_MODE_BOTTOM);
	pViewMng->Draw_Split(pDC, graphics, m_rectPDVR[3], DRAW_SPLIT_MODE_BOTTOM);

	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[0]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[1]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[2]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[3]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[4]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[5]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[6]);
	pViewMng->DrawArea_List(pDC, graphics, m_rectCtrl_List[7]);

	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[0], _T("전압 검토") , TRUE);
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[1], _T("보호기기 검토"), TRUE);
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[2], _T("오동작 검토 결과"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[3], _T("부동작 검토 결과"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[4], _T("단락용량 검토 결과"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[5], _T("제어 대상 설정"), TRUE);
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[6], _T("전압 제어 가능 분산형전원"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[7], _T("전압 제어 불가 분산형전원"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[8], _T("누적용량 및 순시전압 변동 검토"),TRUE);

	return TRUE;
}

void CView_PDVR_rst::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);

	OnPrepareDC(&dc);
	

	Graphics						graphics(dc.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);


	Draw_Setting_Tag_1(&dc, graphics);
	Draw_Setting_Tag_2(&dc, graphics);

	Draw_Graph(&dc, graphics, m_rectPDVR[1]);

	
	Redraw_Ctrl();
/*	m_ctrList[0].SetActiveWindow();
	m_ctrList[1].SetActiveWindow();
	m_ctrList[2].SetActiveWindow();
	m_ctrList[3].SetActiveWindow();
	m_ctrList[4].SetActiveWindow();
	m_ctrList[5].SetActiveWindow();*/

}

void CView_PDVR_rst::Redraw_Ctrl()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL)
		return;

//	RedrawWindow();

	m_ctrList[0].RedrawWindow();
	m_ctrList[1].RedrawWindow();
	m_ctrList[2].RedrawWindow();
	m_ctrList[3].RedrawWindow();
	m_ctrList[4].RedrawWindow();
	m_ctrList[5].RedrawWindow();


//	m_ctrCombo[0].SetFocus();
	m_ctrCombo[0].RedrawWindow();
//	m_ctrCombo[1].SetFocus();
	m_ctrCombo[1].RedrawWindow();
//	m_ctrCombo[2].SetFocus();
	m_ctrCombo[2].RedrawWindow();
//	m_ctrCombo[3].SetFocus();
	m_ctrCombo[3].RedrawWindow();

}


void CView_PDVR_rst::Draw_Setting_Tag_1(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectSetting[0];

	rect.InflateRect(-5, -10);

	Gdiplus::RectF  _r;

	_r.X = rect.left;
	_r.Y = rect.top;
	_r.Width = 65;
	_r.Height = 26;


	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));


	graphics.DrawString(_T("기간 설정"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);

	Gdiplus::RectF  _rect_date[3];

	_rect_date[0].Y = rect.top;
	_rect_date[1].Y = rect.top;
	_rect_date[2].Y = rect.top;

	_rect_date[0].Height = 26;
	_rect_date[1].Height = 26;
	_rect_date[2].Height = 26;

	_rect_date[0].X = rect.left + 70 ;
	_rect_date[1].X = _rect_date[0].X + 173 ;
	_rect_date[2].X = _rect_date[1].X + 24;

	_rect_date[0].Width = 173;
	_rect_date[1].Width = 24;
	_rect_date[2].Width = 173;

	graphics.DrawString(_T("~"), -1, &_drawfont, _rect_date[1], &_drawStrFormat, &_drawFontbrush);

	SolidBrush						_drawRectbrush(Color(255, 153, 153, 153));
	Gdiplus::Pen					_drawRectpen(&_drawRectbrush, 1.);

	CView_Manager* pViewMng = CView_Manager::Instance();
	Gdiplus::GraphicsPath gdiPath;
	pViewMng->GetRoundRectPath(&gdiPath, _rect_date[0].GetLeft(), _rect_date[0].GetTop(), _rect_date[0].Width, _rect_date[0].Height, 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);

	pViewMng->GetRoundRectPath(&gdiPath, _rect_date[2].GetLeft(), _rect_date[2].GetTop(), _rect_date[2].Width, _rect_date[2].Height, 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);


	graphics.DrawString(_T("~"), -1, &_drawfont, _rect_date[1], &_drawStrFormat, &_drawFontbrush);

	/*graphics.DrawString(m_strDate[0], -1, &_drawfont, _rect_date[0], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(m_strDate[1], -1, &_drawfont, _rect_date[2], &_drawStrFormat, &_drawFontbrush);*/


	///////////////////////
	rect = m_rectSetting[1];

	rect.InflateRect(-5, -10);

	_r.X = rect.left;
	_r.Y = rect.top;
	_r.Width = 65;
	_r.Height = 26;

	graphics.DrawString(_T("검토 대상"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);

	pViewMng->GetRoundRectPath(&gdiPath, m_rectCtrl_Edit[0].left, m_rectCtrl_Edit[0].top, m_rectCtrl_Edit[0].Width(), m_rectCtrl_Edit[0].Height(), 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);

	pViewMng->GetRoundRectPath(&gdiPath, m_rectCtrl_Edit[1].left, m_rectCtrl_Edit[1].top, m_rectCtrl_Edit[1].Width(), m_rectCtrl_Edit[1].Height(), 6);
	graphics.DrawPath(&_drawRectpen, &gdiPath);
}

void CView_PDVR_rst::Draw_Setting_Tag_2(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectPDVR[3];

	//rect.InflateRect(-5, -10);

	Gdiplus::RectF  _r;

	_r.X = rect.left;
	_r.Y = rect.top;
	_r.Width = 67;
	_r.Height = 28;


	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 19, 94, 53));


	graphics.DrawString(_T("표시 결과"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);

	/*_r.Y += 28;
	graphics.DrawString(_T("표시 결과"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);*/
}

void CView_PDVR_rst::Draw_Graph(CDC* pDC, Graphics &graphics, CRect rectDraw)
{

	Gdiplus::RectF  _rect;
	/*_rect.X = m_rectPDVR[1].left;
	_rect.Y = m_rectPDVR[1].top;
	_rect.Width = m_rectPDVR[1].Width();
	_rect.Height = m_rectPDVR[1].Height();
*/
	_rect.X = rectDraw.left;
	_rect.Y = rectDraw.top;
	_rect.Width = rectDraw.Width();
	_rect.Height = rectDraw.Height();


	SolidBrush						_drawRectbrush(Color(255, 225, 225, 225));
	Gdiplus::Pen		_drawRectpen(&_drawRectbrush, 1.);
	//graphics.FillRectangle(&_drawRectbrush, _rect);

	//_rect.Inflate(-20, -20);
	_rect.X += 54;
	_rect.Y += 20;
	_rect.Width -= 154;
	_rect.Height -= 28 + 40;

	Gdiplus::RectF  _rX, _rY;
	_rX.X = _rect.X - 54;
	_rX.Y = _rect.Y;
	_rX.Width = 54;
	_rX.Height = 20;

	_rY.X = _rect.GetRight() - 84;
	_rY.Y = _rect.GetBottom()+ 20;
	_rY.Width = 84;
	_rY.Height = 20;

	//SolidBrush						_drawXYrush(Color(255, 247, 247, 247));
	//graphics.FillRectangle(&_drawXYrush, _rect);

	SolidBrush						_drawLenbrush(Color(255, 225, 225, 225));
	Gdiplus::Pen		_drawLenpen(&_drawLenbrush, 1.);
	_drawLenpen.SetDashStyle(Gdiplus::DashStyleDash);

	/*double dX;
	for (int i = 5; i < m_nNode_MaxCount + 2; i += 5)
	{

		dX = _rect.X + (_rect.Width  * (((double)i) / (double)m_nNode_MaxCount));
		graphics.DrawLine(&_drawLenpen, (REAL)dX, (REAL)_rect.GetTop(), (REAL)dX, (REAL)_rect.GetBottom());
	}*/

	SolidBrush						_drawXYbrush(Color(255, 0, 0, 0));
	Gdiplus::Pen		_drawXYpen(&_drawXYbrush, 1.);
	graphics.DrawLine(&_drawXYpen, _rect.GetLeft(), _rect.GetTop(), _rect.GetLeft(), _rect.GetBottom());
	graphics.DrawLine(&_drawXYpen, _rect.GetLeft(), _rect.GetBottom(), _rect.GetRight(), _rect.GetBottom());

	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 0, 0, 0));

	graphics.DrawString(_T("전압"), -1, &_drawfont, _rX, &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("선로길이(km)"), -1, &_drawfont, _rY, &_drawStrFormat, &_drawFontbrush);

	if (m_Array_Graph.GetSize() > 0)
		Draw_Graph_Data(pDC, graphics, _rect);
}

void CView_PDVR_rst::Draw_Graph_Data(CDC* pDC, Graphics &graphics, Gdiplus::RectF r)
{


	/*double dTempMin_V = m_dMin_V - 0.200;
	double dTemp_V = m_dMax_V - dTempMin_V + 0.200 ;*/

	double dBase_V = 13.200;
	double dTap_V = 12.600;
	double dTempMin_V = (dBase_V*m_dVVM_lmlo_Tap) - 0.812;			///////////// 11200
	double dTemp_V = (dBase_V*m_dVVM_lmhi) - dTempMin_V + 0.396;    ///////////// 13800

	CGraphData *pData;
	double dMax_Len = -1.;
	double dTabChange = 0.;
	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	{
		pData = m_Array_Graph.GetAt(i);

		if (pData->m_dLen[1] > dMax_Len)
			dMax_Len = pData->m_dLen[1];

		if (pData->m_nTapChange == 2 && dTabChange == 0.)
			dTabChange = pData->m_dLen[1];
	}



	Gdiplus::RectF r_hi, r_lo;
	SolidBrush						_drawVVMhibrush(Color(30, 237, 22, 113));
	SolidBrush						_drawVVNlobrush(Color(30, 10, 185, 146));
	SolidBrush						_drawVVMhipenbrush(Color(255, 237, 22, 113));
	SolidBrush						_drawVVMlopenbrush(Color(255, 10, 185, 146));
	Gdiplus::Pen		_drawVVMhipen(&_drawVVMhipenbrush, 1.);
	Gdiplus::Pen		_drawVVMlopen(&_drawVVMlopenbrush, 1.);
	_drawVVMhipen.SetDashStyle(Gdiplus::DashStyleDot);
	_drawVVMlopen.SetDashStyle(Gdiplus::DashStyleDot);

	r_hi = r;
	r_lo = r;

	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentFar);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));

	if (dTabChange > 0.)
	{
		double dTapLen;
		

		dTapLen = r.X + (r.Width  * (((double)dTabChange) / (double)dMax_Len));

		r_hi.Height = r.Height - (r.Height * (((dBase_V*m_dVVM_lmhi) - dTempMin_V) / dTemp_V));
		r_hi.Width = dTapLen - r_hi.X;
		r_lo.Y = r.GetBottom() - (r.Height * (((dBase_V*m_dVVM_lmlo) - dTempMin_V) / dTemp_V));
		r_lo.Width = dTapLen - r_lo.X;
		r_lo.Height = r.GetBottom() - r_lo.Y; 

		//graphics.FillRectangle(&_drawVVMhibrush, r_hi);
		//graphics.FillRectangle(&_drawVVNlobrush, r_lo);
		graphics.DrawLine(&_drawVVMhipen, (REAL)r_hi.GetLeft(), (REAL)r_hi.GetBottom(), (REAL)dTapLen, (REAL)r_hi.GetBottom());
		if(m_nMode == 1)
			graphics.DrawLine(&_drawVVMlopen, (REAL)r_lo.GetLeft(), (REAL)r_lo.GetTop(), (REAL)dTapLen, (REAL)r_lo.GetTop());

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

		
		SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));
		CString strVVM_hi, strVVM_lo;
		strVVM_hi.Format(_T("%.3lf"), dBase_V*m_dVVM_lmhi);
		strVVM_lo.Format(_T("%.3lf"), dBase_V*m_dVVM_lmlo);
		graphics.DrawString(strVVM_hi, -1, &_drawfont, r_hi_var, &_drawStrFormat, &_drawFontbrush);
		graphics.DrawString(strVVM_lo, -1, &_drawfont, r_lo_var, &_drawStrFormat, &_drawFontbrush);



		r_hi.Height = r.Height - (r.Height * (((dBase_V*m_dVVM_lmhi_Tap) - dTempMin_V) / dTemp_V));
		r_hi.X = dTapLen;
		r_hi.Width = r.GetRight() - dTapLen;
		r_lo.Y = r.GetBottom() - (r.Height * (((dBase_V*m_dVVM_lmlo_Tap) - dTempMin_V) / dTemp_V));
		r_lo.X = dTapLen;
		r_lo.Width = r.GetRight() - dTapLen;
		r_lo.Height = r.GetBottom() - r_lo.Y;

	//	graphics.FillRectangle(&_drawVVMhibrush, r_hi);
	//	graphics.FillRectangle(&_drawVVNlobrush, r_lo);
		graphics.DrawLine(&_drawVVMhipen, (REAL)dTapLen, (REAL)r_hi.GetBottom(), (REAL)r_hi.GetRight(), (REAL)r_hi.GetBottom());
		if (m_nMode == 1)
			graphics.DrawLine(&_drawVVMlopen, (REAL)dTapLen, (REAL)r_lo.GetTop(), (REAL)r_lo.GetRight(), (REAL)r_lo.GetTop());

		r_hi_var.X = r.X - 50;
		r_hi_var.Y = r_hi.GetBottom();
		r_hi_var.Width = 50;
		r_hi_var.Height = 1;
		r_hi_var.Inflate(0, 10);

		r_lo_var.X = r.X - 50;
		r_lo_var.Y = r_lo.GetTop();
		r_lo_var.Width = 50;
		r_lo_var.Height = 1;
		r_lo_var.Inflate(0, 10);

		strVVM_hi.Format(_T("%.3lf"), dBase_V*m_dVVM_lmhi_Tap);
		strVVM_lo.Format(_T("%.3lf"), dBase_V*m_dVVM_lmlo_Tap);
		graphics.DrawString(strVVM_hi, -1, &_drawfont, r_hi_var, &_drawStrFormat, &_drawFontbrush);
		graphics.DrawString(strVVM_lo, -1, &_drawfont, r_lo_var, &_drawStrFormat, &_drawFontbrush);
	}
	else
	{
		r_hi.Height = r.Height - (r.Height * (((13.200*m_dVVM_lmhi) - dTempMin_V) / dTemp_V));
		r_lo.Y = r.GetBottom() - (r.Height * (((13.200*m_dVVM_lmlo) - dTempMin_V) / dTemp_V));
		r_lo.Height = r.GetBottom() - r_lo.Y;

	//	graphics.FillRectangle(&_drawVVMhibrush, r_hi);
	//	graphics.FillRectangle(&_drawVVNlobrush, r_lo);
		graphics.DrawLine(&_drawVVMhipen, (REAL)r_hi.GetLeft(), (REAL)r_hi.GetBottom(), (REAL)r_hi.GetRight(), (REAL)r_hi.GetBottom());
		if (m_nMode == 1)
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

		
		
		CString strVVM_hi, strVVM_lo;
		strVVM_hi.Format(_T("%.3lf"), dBase_V*m_dVVM_lmhi);
		strVVM_lo.Format(_T("%.3lf"), dBase_V*m_dVVM_lmlo);
		graphics.DrawString(strVVM_hi, -1, &_drawfont, r_hi_var, &_drawStrFormat, &_drawFontbrush);
		graphics.DrawString(strVVM_lo, -1, &_drawfont, r_lo_var, &_drawStrFormat, &_drawFontbrush);
	}
	

	

	
	double  dX_P, dY_P, dX, dY, dValue[2];
	SolidBrush						_drawSWbrush(Color(255, 253, 90, 63));
	Gdiplus::RectF _rSW;



	BOOL	bDraw_Check_Type[4] = { TRUE,TRUE, TRUE, TRUE };
	bDraw_Check_Type[0] = m_ctrBtn_Check[3].GetCheckButton();
	bDraw_Check_Type[1] = m_ctrBtn_Check[4].GetCheckButton();
	bDraw_Check_Type[2] = m_ctrBtn_Check[5].GetCheckButton();
	bDraw_Check_Type[3] = m_ctrBtn_Check[6].GetCheckButton();


	SolidBrush						_drawDatabrush_cur_mx(Color(255, 255, 0, 0));
	Gdiplus::Pen					_drawDatapen_cur_mx(&_drawDatabrush_cur_mx, 2.);
	_drawDatapen_cur_mx.SetDashStyle(DashStyleDashDotDot);


	SolidBrush						_drawDatabrush_cur_mn(Color(255, 0, 0, 255));
	Gdiplus::Pen					_drawDatapen_cur_mn(&_drawDatabrush_cur_mn, 2.);
	_drawDatapen_cur_mn.SetDashStyle(DashStyleDashDotDot);

	SolidBrush						_drawDatabrush_cal_mx(Color(255,255,127, 39));
	Gdiplus::Pen					_drawDatapen_cal_mx(&_drawDatabrush_cal_mx, 2.);

	SolidBrush						_drawDatabrush_cal_mn(Color(255, 100, 142, 255));
	Gdiplus::Pen					_drawDatapen_cal_mn(&_drawDatabrush_cal_mn, 2.);

	Gdiplus::RectF _r_X_Tag;
	_r_X_Tag.X = -10;
	_r_X_Tag.Y = r.GetBottom() + 2;
	_r_X_Tag.Width = 20;
	_r_X_Tag.Height = 20;

	CString strX_Tag;
	double dStep = dMax_Len / 10.;
	int nStep;
	if (dStep < 1.)
	{
		if (dMax_Len >= 1.)
			dStep = 1.;
		else
			dStep = 0.1;
	
	}
	else
	{
		nStep = int(dStep);
		dStep = double(nStep);
	}
		
	double dLen_tag = 0;
	while (dMax_Len)
	{
		dX_P = r.X + (r.Width  * (((double)dLen_tag) / (double)dMax_Len));

		_r_X_Tag.X = dX_P - 10.;

		if(dStep ==  0.1)
			strX_Tag.Format(_T("%.1lf"), dLen_tag);
		else
			strX_Tag.Format(_T("%.0lf"), dLen_tag);

		graphics.DrawString(strX_Tag, -1, &_drawfont, _r_X_Tag, &_drawStrFormat, &_drawFontbrush);

		dLen_tag += dStep;

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

			if (bDraw_Check_Type[0]) ////////////////////////////////// 기존 값 MX
			{
				dValue[0] = dBase_V * pData->m_dPDVR_pu_p[0][0];
				dValue[1] = dBase_V * pData->m_dPDVR_pu_c[0][0];

				if ((dValue[0] - dTempMin_V) > dTemp_V)
					dValue[0] = dTemp_V + dTempMin_V;
				else if (dValue[0] < dTempMin_V)
					dValue[0] = dTempMin_V;

				if ((dValue[1] - dTempMin_V) > dTemp_V)
					dValue[1] = dTemp_V + dTempMin_V;
				else if (dValue[1] < dTempMin_V)
					dValue[1] = dTempMin_V;

				dX_P = r.X + (r.Width  * (((double)pData->m_dLen[0]) / (double)dMax_Len));
				dY_P = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

				dX = r.X + (r.Width  * ((double)pData->m_dLen[1] / (double)dMax_Len));
				dY = r.GetBottom() - (r.Height * ((dValue[1] - dTempMin_V) / dTemp_V));

				graphics.DrawLine(&_drawDatapen_cur_mx, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);
			}
			if (m_nMode == 1)
			{
				if (bDraw_Check_Type[1]) ////////////////////////////////// 기존 값 MN
				{
					dValue[0] = dBase_V * pData->m_dPDVR_pu_p[0][1];
					dValue[1] = dBase_V * pData->m_dPDVR_pu_c[0][1];

					if ((dValue[0] - dTempMin_V) > dTemp_V)
						dValue[0] = dTemp_V + dTempMin_V;
					else if (dValue[0] < dTempMin_V)
						dValue[0] = dTempMin_V;

					if ((dValue[1] - dTempMin_V) > dTemp_V)
						dValue[1] = dTemp_V + dTempMin_V;
					else if (dValue[1] < dTempMin_V)
						dValue[1] = dTempMin_V;

					dX_P = r.X + (r.Width  * (((double)pData->m_dLen[0]) / (double)dMax_Len));
					dY_P = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

					dX = r.X + (r.Width  * ((double)pData->m_dLen[1] / (double)dMax_Len));
					dY = r.GetBottom() - (r.Height * ((dValue[1] - dTempMin_V) / dTemp_V));

					graphics.DrawLine(&_drawDatapen_cur_mn, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);
				}

				if (bDraw_Check_Type[2]) ////////////////////////////////// 제안 값 MX
				{
					dValue[0] = dBase_V * pData->m_dPDVR_pu_p[1][0];
					dValue[1] = dBase_V * pData->m_dPDVR_pu_c[1][0];

					if ((dValue[0] - dTempMin_V) > dTemp_V)
						dValue[0] = dTemp_V + dTempMin_V;
					else if (dValue[0] < dTempMin_V)
						dValue[0] = dTempMin_V;

					if ((dValue[1] - dTempMin_V) > dTemp_V)
						dValue[1] = dTemp_V + dTempMin_V;
					else if (dValue[1] < dTempMin_V)
						dValue[1] = dTempMin_V;

					dX_P = r.X + (r.Width  * (((double)pData->m_dLen[0]) / (double)dMax_Len));
					dY_P = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

					dX = r.X + (r.Width  * ((double)pData->m_dLen[1] / (double)dMax_Len));
					dY = r.GetBottom() - (r.Height * ((dValue[1] - dTempMin_V) / dTemp_V));

					graphics.DrawLine(&_drawDatapen_cal_mx, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);
				}

				if (bDraw_Check_Type[3]) ////////////////////////////////// 제안 값 MN
				{
					dValue[0] = dBase_V * pData->m_dPDVR_pu_p[1][1];
					dValue[1] = dBase_V * pData->m_dPDVR_pu_c[1][1];

					if ((dValue[0] - dTempMin_V) > dTemp_V)
						dValue[0] = dTemp_V + dTempMin_V;
					else if (dValue[0] < dTempMin_V)
						dValue[0] = dTempMin_V;

					if ((dValue[1] - dTempMin_V) > dTemp_V)
						dValue[1] = dTemp_V + dTempMin_V;
					else if (dValue[1] < dTempMin_V)
						dValue[1] = dTempMin_V;

					dX_P = r.X + (r.Width  * (((double)pData->m_dLen[0]) / (double)dMax_Len));
					dY_P = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

					dX = r.X + (r.Width  * ((double)pData->m_dLen[1] / (double)dMax_Len));
					dY = r.GetBottom() - (r.Height * ((dValue[1] - dTempMin_V) / dTemp_V));

					graphics.DrawLine(&_drawDatapen_cal_mn, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);
				}
			}
			
			

		}

		double dWidth = 5;
		for (int i = 0; i < m_Array_Graph.GetSize(); i++)
		{
			pData = m_Array_Graph.GetAt(i);

			if (pData->m_nType == 0)
			{
				continue;
			}

			if (bDraw_Check_Type[0])
			{
				dValue[0] = dBase_V * pData->m_dPDVR_pu_c[0][0];
				if ((dValue[0] - dTempMin_V) > dTemp_V)
					dValue[0] = dTemp_V + dTempMin_V;
				else if (dValue[0] < dTempMin_V)
					dValue[0] = dTempMin_V;

				dX = r.X + (r.Width  * ((double)pData->m_dLen[1] / (double)dMax_Len));
				dY = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

				_rSW.X = dX - (dWidth /2.);
				_rSW.Y = dY - (dWidth / 2.);
				_rSW.Width = dWidth;
				_rSW.Height = dWidth;

				graphics.FillEllipse(&_drawDatabrush_cur_mx, _rSW);
			}

			if (m_nMode == 1)
			{
				if (bDraw_Check_Type[1])
				{
					dValue[0] = dBase_V * pData->m_dPDVR_pu_c[0][1];
					if ((dValue[0] - dTempMin_V) > dTemp_V)
						dValue[0] = dTemp_V + dTempMin_V;
					else if (dValue[0] < dTempMin_V)
						dValue[0] = dTempMin_V;

					dX = r.X + (r.Width  * ((double)pData->m_dLen[1] / (double)dMax_Len));
					dY = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

					_rSW.X = dX - (dWidth / 2.);
					_rSW.Y = dY - (dWidth / 2.);
					_rSW.Width = dWidth;
					_rSW.Height = dWidth;

					graphics.FillEllipse(&_drawDatabrush_cur_mn, _rSW);
				}

				if (bDraw_Check_Type[2])
				{
					dValue[0] = dBase_V * pData->m_dPDVR_pu_c[1][0];
					if ((dValue[0] - dTempMin_V) > dTemp_V)
						dValue[0] = dTemp_V + dTempMin_V;
					else if (dValue[0] < dTempMin_V)
						dValue[0] = dTempMin_V;

					dX = r.X + (r.Width  * ((double)pData->m_dLen[1] / (double)dMax_Len));
					dY = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

					_rSW.X = dX - (dWidth / 2.);
					_rSW.Y = dY - (dWidth / 2.);
					_rSW.Width = dWidth;
					_rSW.Height = dWidth;

					graphics.FillEllipse(&_drawDatabrush_cal_mx, _rSW);
				}

				if (bDraw_Check_Type[3])
				{
					dValue[0] = dBase_V * pData->m_dPDVR_pu_c[1][1];
					if ((dValue[0] - dTempMin_V) > dTemp_V)
						dValue[0] = dTemp_V + dTempMin_V;
					else if (dValue[0] < dTempMin_V)
						dValue[0] = dTempMin_V;

					dX = r.X + (r.Width  * ((double)pData->m_dLen[1] / (double)dMax_Len));
					dY = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

					_rSW.X = dX - (dWidth / 2.);
					_rSW.Y = dY - (dWidth / 2.);
					_rSW.Width = dWidth;
					_rSW.Height = dWidth;

					graphics.FillEllipse(&_drawDatabrush_cal_mn, _rSW);
				}
			}
		
			

			/*
			if (pData->m_nCheck == 1)
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

	//////////////////////////////////////////////////////////////////////////////////////////

	SolidBrush						_drawMeaDatabrush(Color(255, 127, 7, 106));
	Gdiplus::Pen		_drawMeaDatapen(&_drawMeaDatabrush, 1.);
	SolidBrush						_drawMeaSWbrush(Color(255, 7, 151, 34));
	/*	if (m_bGraph_Check[0])
		{
			for (int i = 0; i < m_Array_Graph.GetSize(); i++)
			{
				pData = m_Array_Graph.GetAt(i);

				if (pData->m_nNodeID_Prev < 0 || pData->m_nType == 0 || pData->m_dCurrValue_mea <= 0.)
				{
					////////////////// 노드 모양만 그리자
					continue;
				}

				dValue[0] = pData->m_dPrevValue_mea;
				dValue[1] = pData->m_dCurrValue_mea;

				if ((dValue[0] - dTempMin_V) > dTemp_V)
					dValue[0] = dTemp_V + dTempMin_V;
				else if (dValue[0] < dTempMin_V)
					dValue[0] = dTempMin_V;

				if ((dValue[1] - dTempMin_V) > dTemp_V)
					dValue[1] = dTemp_V + dTempMin_V;
				else if (dValue[1] < dTempMin_V)
					dValue[1] = dTempMin_V;

				dX_P = r.X + (r.Width  * (((double)pData->m_nPrev_idx) / (double)m_nNode_MaxCount));
				dY_P = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

				dX = r.X + (r.Width  * ((double)pData->m_nCount / (double)m_nNode_MaxCount));
				dY = r.GetBottom() - (r.Height * ((dValue[1] - dTempMin_V) / dTemp_V));

				graphics.DrawLine(&_drawMeaDatapen, (REAL)dX_P, (REAL)dY_P, (REAL)dX, (REAL)dY);

			}

			for (int i = 0; i < m_Array_Graph.GetSize(); i++)
			{
				pData = m_Array_Graph.GetAt(i);

				if (pData->m_nType == 0 || pData->m_dCurrValue_mea <= 0.)
				{
					continue;
				}
				dValue[0] = pData->m_dCurrValue_mea;
				if ((dValue[0] - dTempMin_V) > dTemp_V)
					dValue[0] = dTemp_V + dTempMin_V;
				else if (dValue[0] < dTempMin_V)
					dValue[0] = dTempMin_V;

				dX = r.X + (r.Width  * ((double)pData->m_nCount / (double)m_nNode_MaxCount));
				dY = r.GetBottom() - (r.Height * ((dValue[0] - dTempMin_V) / dTemp_V));

				_rSW.X = dX - 2;
				_rSW.Y = dY - 2;
				_rSW.Width = 4.;
				_rSW.Height = 4.;

				graphics.FillEllipse(&_drawMeaSWbrush, _rSW);
			}
		}*/
		/////////////////////////////////////////////////////////////////////////////////////////
	CString strValue;
	//double dValue_C;
	int nSelCount;
	/*if (m_ptSelect.x > 0 && m_ptSelect.y > 0)
	{
		nSelCount = (m_ptSelect.x - r.X) / r.Width * m_nNode_MaxCount;

		double dMax = 0.;
		for (int i = 0; i < m_Array_Graph.GetSize(); i++)
		{
			pData = m_Array_Graph.GetAt(i);
			if (pData->m_nType == 0)
			{
				continue;
			}

			if (pData->m_nCount == nSelCount)
			{
				if (dMax < pData->m_dCurrValue)
					dMax = pData->m_dCurrValue;
			}
		}



		dX = r.X + (r.Width  * ((double)nSelCount / (double)m_nNode_MaxCount));

		dY = r.GetBottom() - (r.Height * ((dMax - dTempMin_V) / dTemp_V));

		strValue.Format(_T("%.3lf"), dMax);

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
		_drawLenbrush.SetColor(Color(255, 150, 200, 59));
		_drawLenpen.SetColor(Color(255, 54, 55, 59));
		_drawLenpen.SetDashStyle(Gdiplus::DashStyleSolid);

		graphics.FillRectangle(&_drawLenbrush, r_value);
		graphics.DrawRectangle(&_drawLenpen, r_value);

		graphics.DrawString(strValue, -1, &_drawfont, r_value, &_drawStrFormat, &_drawFontbrush);
	}*/

}

void CView_PDVR_rst::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	m_rectBack[0].SetRect(_rect.left, _rect.top, _rect.left + 453 , _rect.bottom );
	m_rectBack[1].SetRect(m_rectBack[0].right , _rect.top , (m_rectBack[0].right + 10) + ((_rect.Width() - m_rectBack[0].right) / 2) , _rect.bottom );
	m_rectBack[2].SetRect(m_rectBack[1].right , _rect.top, _rect.right, _rect.top + 95);
	m_rectBack[3].SetRect(m_rectBack[1].right, m_rectBack[2].bottom + 10, _rect.right, _rect.bottom);

	MoveSize_Setting();
	MoveSize_PDVR();
	MoveSize_PCE();
	MoveSize_Btn();

	//Redraw_Ctrl();
}

void CView_PDVR_rst::MoveSize_Btn()
{
	if (m_btn_ctrl[0].GetSafeHwnd() == NULL)							return;

	CRect rect = m_rectPDVR[0];

	rect.left = rect.right - 578;
	rect.right = rect.left + 87;
	rect.InflateRect(0, -6);

	m_btn_ctrl_rect[0] = rect;
	m_btn_ctrl[0].MoveWindow(m_btn_ctrl_rect[0]);

	m_btn_ctrl_rect[1] = rect;
	m_btn_ctrl_rect[1].left = m_btn_ctrl_rect[0].right + 8;
	m_btn_ctrl_rect[1].right = m_btn_ctrl_rect[1].left + 150;
	m_btn_ctrl[1].MoveWindow(m_btn_ctrl_rect[1]);

	m_btn_ctrl_rect[2] = rect;
	m_btn_ctrl_rect[2].left = m_btn_ctrl_rect[1].right + 8;
	m_btn_ctrl_rect[2].right = m_btn_ctrl_rect[2].left + 155;
	m_btn_ctrl[2].MoveWindow(m_btn_ctrl_rect[2]);

	m_btn_ctrl_rect[3] = rect;
	m_btn_ctrl_rect[3].left = m_btn_ctrl_rect[2].right + 8;
	m_btn_ctrl_rect[3].right = m_btn_ctrl_rect[3].left + 155;
	m_btn_ctrl[3].MoveWindow(m_btn_ctrl_rect[3]);

	//////////////////////////////////////////////
	//rect = m_rectPCE[0];

	//rect.left = rect.right - 94;
	//rect.right = rect.left + 87;
	//rect.InflateRect(0, -6);

	//m_btn_ctrl_rect[4] = rect;
	//m_btn_ctrl[4].MoveWindow(m_btn_ctrl_rect[4]);

}

void CView_PDVR_rst::MoveSize_Setting()
{
	if(m_ctrList[1].GetSafeHwnd() == NULL || m_btn_ctrl[6].GetSafeHwnd() == NULL)							return;

	/////////////////////////////////////////////타이틀  
	m_rectSetting[0] = m_rectBack[0];
	m_rectSetting[0].bottom = m_rectSetting[0].top + 44;

	m_rectSetting[1] = m_rectBack[0];
	m_rectSetting[1].top = m_rectSetting[0].bottom;
	m_rectSetting[1].bottom = m_rectSetting[1].top + 44;

	m_rectSetting[2] = m_rectBack[0];
	m_rectSetting[2].top = m_rectSetting[1].bottom;
	   	

	m_rectCtrl_Combobox[0] = m_rectSetting[1];
	m_rectCtrl_Combobox[0].InflateRect(-8, -10);
	m_rectCtrl_Combobox[0].left = m_rectCtrl_Combobox[0].left + 65;
	m_rectCtrl_Combobox[0].right = m_rectCtrl_Combobox[0].left + 178;

	m_rectCtrl_Combobox[1] = m_rectCtrl_Combobox[0];
	m_rectCtrl_Combobox[1].left = m_rectCtrl_Combobox[0].right + 8;
	m_rectCtrl_Combobox[1].right = m_rectCtrl_Combobox[1].left + 178;

	m_ctrCombo[0].MoveWindow(m_rectCtrl_Combobox[0]);
	m_ctrCombo[1].MoveWindow(m_rectCtrl_Combobox[1]);

	//////////////////

	CRect rect = m_rectSetting[0];

	rect.InflateRect(-5, -10);

	CRect _rect_date[2];

	_rect_date[0].top = rect.top +1;
	_rect_date[1].top = rect.top +1;

	_rect_date[0].bottom = _rect_date[0].top + 25;
	_rect_date[1].bottom = _rect_date[1].top + 25;

	_rect_date[0].left = rect.left + 71;
	_rect_date[1].left = _rect_date[0].left + 24 + 173;

	_rect_date[0].right = _rect_date[0].left + 172;
	_rect_date[1].right = _rect_date[1].left + 172 ;

	
	m_ctrDate[0].MoveWindow(_rect_date[0]);
	m_ctrDate[1].MoveWindow(_rect_date[1]);

	/////////////////////////

	m_rectTitle[5] = m_rectSetting[2];
	m_rectTitle[5].right = m_rectTitle[5].left + 127;
	m_rectTitle[5].bottom = m_rectTitle[5].top + 30;

	/////////// 콤보추가
	m_rectCtrl_Combobox[2] = m_rectCtrl_Combobox[0];
	m_rectCtrl_Combobox[2].top = m_rectTitle[5].top + 3;
	m_rectCtrl_Combobox[2].left = m_rectSetting[2].right - m_rectCtrl_Combobox[0].Width() - 8;
	m_rectCtrl_Combobox[2].right = m_rectCtrl_Combobox[2].left + m_rectCtrl_Combobox[0].Width();
	m_rectCtrl_Combobox[2].bottom = m_rectCtrl_Combobox[2].top + 20;

	m_ctrCombo[2].MoveWindow(m_rectCtrl_Combobox[2]);

	int nH = (m_rectSetting[2].Height()) / 3;
		
	m_rectCtrl_List[0] = m_rectSetting[2];
	m_rectCtrl_List[0].bottom = m_rectCtrl_List[0].top + 204;

	////////////////////////////////////////////// ///////////////// 제어가능

	m_rectTitle[6] = m_rectSetting[2];
	m_rectTitle[6].top = m_rectCtrl_List[0].bottom ;
	m_rectTitle[6].right = m_rectTitle[6].left + 207;
	m_rectTitle[6].bottom = m_rectTitle[6].top + 30;
	
	m_rectCtrl_List[1] = m_rectSetting[2];
	m_rectCtrl_List[1].top = m_rectCtrl_List[0].bottom;
	m_rectCtrl_List[1].bottom = m_rectCtrl_List[1].top + 309;

	/////////// edit 추가 btn 21,17 
	m_rectCtrl_Edit[0] = m_btn_ctrl_rect[5] = m_rectCtrl_List[1];

	m_btn_ctrl_rect[5].left = m_btn_ctrl_rect[5].right - 32;
	m_btn_ctrl_rect[5].right = m_btn_ctrl_rect[5].left + 21;
	m_btn_ctrl_rect[5].bottom = m_btn_ctrl_rect[5].top + 30;
	m_btn_ctrl_rect[5].InflateRect(0, -6);
	m_btn_ctrl_rect[5].bottom -= 1;

	m_rectCtrl_Edit[0].left = m_btn_ctrl_rect[5].left - 130;
	m_rectCtrl_Edit[0].right = m_rectCtrl_Edit[0].left + 125;
	m_rectCtrl_Edit[0].bottom = m_rectCtrl_Edit[0].top + 30;
	m_rectCtrl_Edit[0].InflateRect(-1, -4);

	m_ctrEdit[0].MoveWindow(m_rectCtrl_Edit[0]);
	m_btn_ctrl[5].MoveWindow(m_btn_ctrl_rect[5]);

	m_rectCtrl_Edit[0].InflateRect(1, 1);

	/////////////////////////////////////////////////////////////////////// 제어 불가


	m_rectTitle[7] = m_rectSetting[2];
	m_rectTitle[7].top = m_rectCtrl_List[1].bottom;
	m_rectTitle[7].right = m_rectTitle[7].left + 207;
	m_rectTitle[7].bottom = m_rectTitle[7].top + 30;

	

	m_rectCtrl_List[6] = m_rectSetting[2];
	m_rectCtrl_List[6].top = m_rectCtrl_List[1].bottom;
	m_rectCtrl_List[6].bottom = m_rectCtrl_List[6].top + 309;

	/////////// edit 추가 btn 21,17 
	m_rectCtrl_Edit[1] = m_btn_ctrl_rect[6] = m_rectCtrl_List[6];

	m_btn_ctrl_rect[6].left = m_btn_ctrl_rect[6].right - 32;
	m_btn_ctrl_rect[6].right = m_btn_ctrl_rect[6].left + 21;
	m_btn_ctrl_rect[6].bottom = m_btn_ctrl_rect[6].top + 30;
	m_btn_ctrl_rect[6].InflateRect(0, -6);
	m_btn_ctrl_rect[6].bottom -= 1;

	m_rectCtrl_Edit[1].left = m_btn_ctrl_rect[6].left - 130;
	m_rectCtrl_Edit[1].right = m_rectCtrl_Edit[1].left + 125;
	m_rectCtrl_Edit[1].bottom = m_rectCtrl_Edit[1].top + 30;
	m_rectCtrl_Edit[1].InflateRect(-1, -4);

	m_ctrEdit[1].MoveWindow(m_rectCtrl_Edit[1]);
	m_btn_ctrl[6].MoveWindow(m_btn_ctrl_rect[6]);

	m_rectCtrl_Edit[1].InflateRect(1, 1);


	//////////

	CRect rectList;

	rectList = m_rectCtrl_List[0];
	rectList.top += 30;
	m_ctrList[0].MoveWindow(rectList);

	rectList = m_rectCtrl_List[1];
	rectList.top += 30;
	m_ctrList[1].MoveWindow(rectList);

	rectList = m_rectCtrl_List[6];
	rectList.top += 30;
	m_ctrList[6].MoveWindow(rectList);
}

void CView_PDVR_rst::MoveSize_PDVR()
{
	if (m_ctrList[2].GetSafeHwnd() == NULL)							return;

	m_rectBack[1].InflateRect(-10, 0);
	CRect rect = m_rectBack[1];
	

	m_rectTitle[0] = rect;
	m_rectTitle[0].right = m_rectTitle[0].left + 98;
	m_rectTitle[0].bottom = m_rectTitle[0].top + 30;

	m_rectPDVR[0] = rect;
	m_rectPDVR[0].top = m_rectTitle[0].bottom;
	m_rectPDVR[0].bottom = m_rectPDVR[0].top + 45;

	m_rectPDVR[3] = rect;
	m_rectPDVR[3].top = m_rectPDVR[0].bottom;
	m_rectPDVR[3].bottom = m_rectPDVR[3].top + 30;

	m_rectPDVR[1] = rect;
	m_rectPDVR[1].top = m_rectPDVR[3].bottom;
	m_rectPDVR[1].bottom = m_rectPDVR[1].top + 500;

	m_rectPDVR[2] = rect;
	m_rectPDVR[2].top = m_rectPDVR[1].bottom;
	m_rectPDVR[2].bottom -= 2;

	m_rectCtrl_List[2] = m_rectPDVR[2];

	m_ctrList[2].MoveWindow(m_rectCtrl_List[2]);

	////////////////////////////////// 체크 박스 추가
	m_rectCtrl_Check[0] = m_rectPDVR[3];
	m_rectCtrl_Check[0].bottom = m_rectCtrl_Check[0].top + 28;
	m_rectCtrl_Check[0].left = m_rectCtrl_Check[0].left + 67;
	m_rectCtrl_Check[0].right= m_rectCtrl_Check[0].left + 90;
	m_rectCtrl_Check[0].InflateRect(0 , -5);

	m_rectCtrl_Check[1] = m_rectCtrl_Check[0];
	m_rectCtrl_Check[1].left = m_rectCtrl_Check[1].left + 90;
	m_rectCtrl_Check[1].right = m_rectCtrl_Check[1].left + 90;

	m_rectCtrl_Check[2] = m_rectCtrl_Check[1];
	m_rectCtrl_Check[2].left = m_rectCtrl_Check[2].left + 90;
	m_rectCtrl_Check[2].right = m_rectCtrl_Check[2].left + 90;

	m_rectCtrl_Check[3] = m_rectPDVR[3];
	m_rectCtrl_Check[3].top = m_rectCtrl_Check[3].top + 28;
	m_rectCtrl_Check[3].bottom = m_rectCtrl_Check[3].top + 28;
	m_rectCtrl_Check[3].left = m_rectCtrl_Check[3].left + 67;
	m_rectCtrl_Check[3].right = m_rectCtrl_Check[3].left + 79;
	m_rectCtrl_Check[3].InflateRect(0, -5);

	m_rectCtrl_Check[4] = m_rectCtrl_Check[3];
	m_rectCtrl_Check[4].left = m_rectCtrl_Check[4].left + 90;
	m_rectCtrl_Check[4].right = m_rectCtrl_Check[4].left + 90;

	m_rectCtrl_Check[5] = m_rectCtrl_Check[4];
	m_rectCtrl_Check[5].left = m_rectCtrl_Check[5].left + 90;
	m_rectCtrl_Check[5].right = m_rectCtrl_Check[5].left + 90;

	//m_rectCtrl_Check[6] = m_rectCtrl_Check[5];
	m_rectCtrl_Check[6] = m_rectCtrl_Check[2];
	m_rectCtrl_Check[6].left = m_rectCtrl_Check[6].left + 90;
	m_rectCtrl_Check[6].right = m_rectCtrl_Check[6].left + 90;

	m_ctrBtn_Check[0].MoveWindow(m_rectCtrl_Check[0]);
	m_ctrBtn_Check[0].ShowWindow(SW_HIDE);
	m_ctrBtn_Check[1].MoveWindow(m_rectCtrl_Check[1]);
	m_ctrBtn_Check[1].ShowWindow(SW_HIDE);
	m_ctrBtn_Check[2].MoveWindow(m_rectCtrl_Check[2]);
	m_ctrBtn_Check[2].ShowWindow(SW_HIDE);
	m_ctrBtn_Check[3].MoveWindow(m_rectCtrl_Check[0]);
	m_ctrBtn_Check[4].MoveWindow(m_rectCtrl_Check[1]);
	m_ctrBtn_Check[5].MoveWindow(m_rectCtrl_Check[2]);
	m_ctrBtn_Check[6].MoveWindow(m_rectCtrl_Check[6]);

	
	///////////////////////////////// Combo
	m_rectCtrl_Combobox[3] = m_rectCtrl_Combobox[0];
	m_rectCtrl_Combobox[3].top = m_rectPDVR[3].top + 3;
	m_rectCtrl_Combobox[3].left = m_rectPDVR[3].right - m_rectCtrl_Combobox[0].Width() - 50;
	m_rectCtrl_Combobox[3].right = m_rectCtrl_Combobox[3].left + m_rectCtrl_Combobox[0].Width();
	m_rectCtrl_Combobox[3].bottom = m_rectCtrl_Combobox[3].top + 20;

	m_ctrCombo[3].MoveWindow(m_rectCtrl_Combobox[3]);



}

void CView_PDVR_rst::MoveSize_PCE()
{
	if (m_ctrList[5].GetSafeHwnd() == NULL)							return;

	CRect rect = m_rectBack[2];

	m_rectTitle[8] = rect;
	m_rectTitle[8].right = m_rectTitle[8].left + 300;
	m_rectTitle[8].bottom = m_rectTitle[8].top + 30;

	m_rectCtrl_List[7] = rect;
	m_rectCtrl_List[7].bottom = m_rectCtrl_List[7].bottom - 1;

	m_rectTitle[1] = rect;
	m_rectTitle[1].top = m_rectCtrl_List[7].bottom + 10;
	m_rectTitle[1].right = m_rectTitle[1].left + 145;
	m_rectTitle[1].bottom = m_rectTitle[1].top + 30;

	//m_rectPCE[0] = rect;
	//m_rectPCE[0].top = m_rectTitle[1].bottom;
	//m_rectPCE[0].bottom = m_rectPCE[0].top + 44;
	////////////////////////// 버튼 추가

	rect = m_rectBack[3];

	///////////////////////////
	m_rectPCE[1] = rect;
	m_rectPCE[1].top = m_rectTitle[1].bottom;

	m_rectCtrl_List[3] = m_rectPCE[1];
	m_rectCtrl_List[3].bottom = m_rectCtrl_List[3].top + 252;

	
	
	m_rectCtrl_List[4] = m_rectPCE[1];
	m_rectCtrl_List[4].top = m_rectCtrl_List[3].bottom;
	m_rectCtrl_List[4].bottom = m_rectCtrl_List[4].top + 253;

	

	m_rectCtrl_List[5] = m_rectPCE[1];
	m_rectCtrl_List[5].top = m_rectCtrl_List[4].bottom;
	m_rectCtrl_List[5].bottom = m_rectCtrl_List[5].top + 253;

	m_rectTitle[2] = m_rectCtrl_List[3];
	m_rectTitle[2].bottom = m_rectTitle[2].top + 30;
	m_rectTitle[2].right = m_rectTitle[2].left + 145;

	m_rectTitle[3] = m_rectCtrl_List[4];
	m_rectTitle[3].bottom = m_rectTitle[3].top + 30;
	m_rectTitle[3].right = m_rectTitle[3].left + 145;

	m_rectTitle[4] = m_rectCtrl_List[5];
	m_rectTitle[4].bottom = m_rectTitle[4].top + 30;
	m_rectTitle[4].right = m_rectTitle[4].left + 145;

	rect = m_rectCtrl_List[3];
	rect.top = rect.top + 30;
	m_ctrList[3].MoveWindow(rect);

	rect = m_rectCtrl_List[4];
	rect.top = rect.top + 30;
	m_ctrList[4].MoveWindow(rect);

	rect = m_rectCtrl_List[5];
	rect.top = rect.top + 30;
	m_ctrList[5].MoveWindow(rect);

	rect = m_rectCtrl_List[7];
	rect.top = rect.top + 30;
	m_ctrList[7].MoveWindow(rect);

}

void CView_PDVR_rst::Create_Btn_Check()
{
	m_font_check.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect;
	rect = CRect(10, 50, 350, 500);
	//////////////////////////////////////////// 표시 단위
	if (!m_ctrBtn_Check[0].Create(_T("개폐기"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PDVR_BTN_CHECK_1))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[1].Create(_T("분산형전원"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PDVR_BTN_CHECK_2))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[2].Create(_T("노드"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PDVR_BTN_CHECK_3))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	m_ctrBtn_Check[0].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
	m_ctrBtn_Check[1].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
	m_ctrBtn_Check[2].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	m_ctrBtn_Check[0].m_pFont_Text = &m_font_check;
	m_ctrBtn_Check[1].m_pFont_Text = &m_font_check;
	m_ctrBtn_Check[2].m_pFont_Text = &m_font_check;

	m_ctrBtn_Check[0].m_colorBg = RGB(255, 255, 255);
	m_ctrBtn_Check[1].m_colorBg = RGB(255, 255, 255);
	m_ctrBtn_Check[2].m_colorBg = RGB(255, 255, 255);



	//////////////////////////////////////////// 표시결과

	if (!m_ctrBtn_Check[3].Create(_T("현재최대"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PDVR_BTN_CHECK_4))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[4].Create(_T("현재최소"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PDVR_BTN_CHECK_5))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[5].Create(_T("제안최대"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PDVR_BTN_CHECK_6))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[6].Create(_T("제안최소"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PDVR_BTN_CHECK_7))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}
	m_ctrBtn_Check[3].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
	m_ctrBtn_Check[4].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
	m_ctrBtn_Check[5].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
	m_ctrBtn_Check[6].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	m_ctrBtn_Check[3].m_pFont_Text = &m_font_Combobox;
	m_ctrBtn_Check[4].m_pFont_Text = &m_font_Combobox;
	m_ctrBtn_Check[5].m_pFont_Text = &m_font_Combobox;
	m_ctrBtn_Check[6].m_pFont_Text = &m_font_Combobox;

	m_ctrBtn_Check[3].m_colorBg = RGB(255, 255, 255);
	m_ctrBtn_Check[4].m_colorBg = RGB(255, 255, 255);
	m_ctrBtn_Check[5].m_colorBg = RGB(255, 255, 255);
	m_ctrBtn_Check[6].m_colorBg = RGB(255, 255, 255);


	m_ctrBtn_Check[0].SetCheckButton(CHECKBOX_DISABLE);
	m_ctrBtn_Check[1].SetCheckButton(CHECKBOX_DISABLE);
	m_ctrBtn_Check[2].SetCheckButton(CHECKBOX_DISABLE);
	m_ctrBtn_Check[3].SetCheckButton(CHECKBOX_CHECKED);
	m_ctrBtn_Check[4].SetCheckButton(CHECKBOX_CHECKED);
	m_ctrBtn_Check[5].SetCheckButton(CHECKBOX_CHECKED);
	m_ctrBtn_Check[6].SetCheckButton(CHECKBOX_CHECKED);


}


void CView_PDVR_rst::Create_ListCtrl()
{
	m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect[2];
	rect[0] = CRect(10, 50, 350, 500);
	m_ctrList[0].Create(WS_CHILD | WS_EX_TOPMOST| LVS_REPORT | LVS_NOSORTHEADER| LVS_SHOWSELALWAYS, rect[0], this, ID_APP_PDVR_LIST_1);
	m_ctrList[0].InsertColumn(0, _T(""), HDF_LEFT, 40);
	m_ctrList[0].InsertColumn(1, _T("제어 대상"), HDF_LEFT, 392);
	m_ctrList[0].InsertColumn(2, _T("idx"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(3, _T("type"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(4, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
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
	m_ctrList[1].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT  , rect[0], this, ID_APP_PDVR_LIST_2);
	m_ctrList[1].InsertColumn(0, _T(""), HDF_LEFT, 40);
	m_ctrList[1].InsertColumn(1, _T("제어 대상"), HDF_LEFT, 210);
	m_ctrList[1].InsertColumn(2, _T("제어 방식"), HDF_LEFT, 112);
	m_ctrList[1].InsertColumn(3, _T("신규 검토"), HDF_LEFT, 70); ////// 스크롤바 21
	m_ctrList[1].InsertColumn(4, _T("idx"), HDF_LEFT, 0);
	m_ctrList[1].InsertColumn(5, _T("dump"), HDF_LEFT, 0);
	m_ctrList[1].ShowWindow(SW_SHOW);
	m_ctrList[1].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_SINGLEROW);
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
	m_ctrList[6].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT , rect[0], this, ID_APP_PDVR_LIST_7);
	m_ctrList[6].InsertColumn(0, _T(""), HDF_LEFT, 40);
	m_ctrList[6].InsertColumn(1, _T("제어 대상"), HDF_LEFT, 210);
	m_ctrList[6].InsertColumn(2, _T("제어 방식"), HDF_LEFT, 112);
	m_ctrList[6].InsertColumn(3, _T("신규 검토"), HDF_LEFT, 70);
	m_ctrList[6].InsertColumn(4, _T("idx"), HDF_LEFT, 0);
	m_ctrList[6].InsertColumn(5, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
	m_ctrList[6].ShowWindow(SW_SHOW);
	m_ctrList[6].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES| LVS_EX_SINGLEROW);
	m_ctrList[6].m_HeaderCtrl.SetHeight(27);
	m_ctrList[6].m_HeaderCtrl.SetFlat();
	m_ctrList[6].m_HeaderCtrl.SetFlat();
	m_ctrList[6].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[6].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[6].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[6].SetBgColor(RGB(255, 255, 255));
	m_ctrList[6].SetUnderLine();
	m_ctrList[6].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[6].SetTextFont(&m_listfont);
	m_ctrList[6].SetRowHeight(25);
	m_ctrList[6].SetCheckBox_Bitmap(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	
	////////////////////////////////////////////            PDVR
	m_ctrList[2].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_PDVR_LIST_3);
	m_ctrList[2].InsertColumn(0, _T("설비"), HDF_LEFT, 167);
	m_ctrList[2].InsertColumn(1, _T("설명"), HDF_LEFT, 520);
	m_ctrList[2].InsertColumn(2, _T("idx"), HDF_LEFT, 0);
	m_ctrList[2].InsertColumn(3, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
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

	////////////////////////////////////////////// 오동작
	m_ctrList[3].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_PDVR_LIST_4);
	m_ctrList[3].InsertColumn(0, _T("구분"), HDF_LEFT, 80);
	m_ctrList[3].InsertColumn(1, _T("전주번호"), HDF_LEFT, 230);
	m_ctrList[3].InsertColumn(2, _T("설정값(A)"), HDF_LEFT, 128);
	m_ctrList[3].InsertColumn(3, _T("고장전류(A)"), HDF_LEFT, 128);
	m_ctrList[3].InsertColumn(4, _T("검토결과"), HDF_LEFT, 128);
	m_ctrList[3].InsertColumn(5, _T("idx"), HDF_LEFT, 0);
	m_ctrList[3].InsertColumn(6, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
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
	m_ctrList[3].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[3].SetTextFont(&m_listfont);
	m_ctrList[3].SetRowHeight(25);

	m_ctrList[4].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_PDVR_LIST_5);
	m_ctrList[4].InsertColumn(0, _T("구분"), HDF_LEFT, 80);
	m_ctrList[4].InsertColumn(1, _T("전주번호"), HDF_LEFT, 230);
	m_ctrList[4].InsertColumn(2, _T("설정값(A)"), HDF_LEFT, 128);
	m_ctrList[4].InsertColumn(3, _T("고장전류(A)"), HDF_LEFT, 128);
	m_ctrList[4].InsertColumn(4, _T("검토결과"), HDF_LEFT, 128);
	m_ctrList[4].InsertColumn(5, _T("idx"), HDF_LEFT, 0);
	m_ctrList[4].InsertColumn(6, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
	m_ctrList[4].ShowWindow(SW_SHOW);
	m_ctrList[4].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
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

	m_ctrList[5].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_PDVR_LIST_6);
	m_ctrList[5].InsertColumn(0, _T("구분"), HDF_LEFT, 80);
	m_ctrList[5].InsertColumn(1, _T("전주번호"), HDF_LEFT, 230);
	m_ctrList[5].InsertColumn(2, _T("단락용량(kA)"), HDF_LEFT, 128);
	m_ctrList[5].InsertColumn(3, _T("고장전류(kA)"), HDF_LEFT, 128);
	m_ctrList[5].InsertColumn(4, _T("검토결과"), HDF_LEFT, 128);
	m_ctrList[5].InsertColumn(5, _T("idx"), HDF_LEFT, 0);
	m_ctrList[5].InsertColumn(6, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
	m_ctrList[5].ShowWindow(SW_SHOW);
	m_ctrList[5].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[5].m_HeaderCtrl.SetHeight(27);
	m_ctrList[5].m_HeaderCtrl.SetFlat();
	m_ctrList[5].m_HeaderCtrl.SetFlat();
	m_ctrList[5].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[5].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[5].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[5].SetBgColor(RGB(255, 255, 255));
	m_ctrList[5].SetUnderLine();
	m_ctrList[5].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[5].SetTextFont(&m_listfont);
	m_ctrList[5].SetRowHeight(25);

	m_ctrList[7].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_PDVR_LIST_8);
	m_ctrList[7].InsertColumn(0, _T("변전소 누적용량"), HDF_LEFT, 172);
	m_ctrList[7].InsertColumn(1, _T("MTR 누적용량"), HDF_LEFT, 172);
	m_ctrList[7].InsertColumn(2, _T("배전선로 누적용량"), HDF_LEFT, 172);
	m_ctrList[7].InsertColumn(3, _T("순시전압 변동량"), HDF_LEFT, 172);
	m_ctrList[7].InsertColumn(4, _T("dump"), HDF_LEFT, 0);
	//m_ctrList[7].InsertColumn(5, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
	m_ctrList[7].ShowWindow(SW_SHOW);
	m_ctrList[7].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[7].m_HeaderCtrl.SetHeight(27);
	m_ctrList[7].m_HeaderCtrl.SetFlat();
	m_ctrList[7].m_HeaderCtrl.SetFlat();
	m_ctrList[7].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[7].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[7].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[7].SetBgColor(RGB(255, 255, 255));
	m_ctrList[7].SetUnderLine();
	m_ctrList[7].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[7].SetTextFont(&m_listfont);
	m_ctrList[7].SetRowHeight(25);

}

void CView_PDVR_rst::Create_DateTimeCtrl()
{
	if (!m_ctrDate[0].Create(WS_CHILD |  WS_VISIBLE | DTS_SHORTDATEFORMAT,
		CRect(100, 100, 200, 200),  this, ID_APP_PDVR_DATE_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrDate[1].Create(WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT,
		CRect(100, 100, 200, 200), this, ID_APP_PDVR_DATE_2))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}
}

void CView_PDVR_rst::Create_Edit()
{
	if (!m_ctrEdit[0].Create(WS_CHILD | WS_VISIBLE | DT_VCENTER, 
		CRect(100, 100, 200, 200), this, ID_APP_PDVR_EDIT_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrEdit[1].Create(WS_CHILD | WS_VISIBLE | ES_LEFT,
		CRect(100, 100, 200, 200), this, ID_APP_PDVR_EDIT_2))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}
}

void CView_PDVR_rst::Create_Combobox()
{
	m_font_Combobox.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	if (!m_ctrCombo[0].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE |  CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_PDVR_COMBO_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}
	if (!m_ctrCombo[1].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE |  CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_PDVR_COMBO_2))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[2].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_PDVR_COMBO_3))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}
	if (!m_ctrCombo[3].Create(WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWN | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_PDVR_COMBO_4))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}


	m_ctrCombo[0].SetTextFont(&m_font_Combobox);
	m_ctrCombo[1].SetTextFont(&m_font_Combobox);
	m_ctrCombo[2].SetTextFont(&m_font_Combobox);
	m_ctrCombo[3].SetTextFont(&m_font_Combobox);
	
	m_ctrCombo[0].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[1].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[2].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[3].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
		
	m_ctrCombo[0].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[1].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[2].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[3].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);

	m_ctrCombo[0].SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[1].SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[2].SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[3].SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);


	m_ctrCombo[0].SetDropDownHeight(10);
	m_ctrCombo[1].SetDropDownHeight(10);
	m_ctrCombo[2].SetDropDownHeight(10);
	m_ctrCombo[3].SetDropDownHeight(10);






	//m_ctrCombo[4].ShowWindow(SW_HIDE);
}

void CView_PDVR_rst::Create_Btn()
{
	m_btn_ctrl_rect[0] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[0].Create(_T(""), WS_CHILD | WS_EX_TOPMOST| WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[0], this, ID_APP_PDVR_BTN_1))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[0].SetBitmapID(IDB_PDVR_RUN_NOR, IDB_PDVR_RUN_CLK, IDB_PDVR_RUN_OVR);

	m_btn_ctrl_rect[1] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[1].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[1], this, ID_APP_PDVR_BTN_2))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[1].SetBitmapID(IDB_PDVR_OPT_NOR, IDB_PDVR_OPT_CLK, IDB_PDVR_OPT_OVR);

	m_btn_ctrl_rect[2] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[2].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[2], this, ID_APP_PDVR_BTN_3))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[2].SetBitmapID(IDB_PDVR_RPT_NOR, IDB_PDVR_RPT_CLK, IDB_PDVR_RPT_OVR);

	m_btn_ctrl_rect[3] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[3].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[3], this, ID_APP_PDVR_BTN_4))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[3].SetBitmapID(IDB_PDVR_CAL_NOR, IDB_PDVR_CAL_CLK, IDB_PDVR_CAL_OVR);

	//m_btn_ctrl_rect[4] = CRect(10, 20, 90, 250);
	//if (!m_btn_ctrl[4].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[4], this, ID_APP_PDVR_BTN_5))			// | BS_OWNERDRAW
	//{
	//	AfxMessageBox(_T("Create PDVR Button Fail.\n"));
	//	return;
	//}
	//m_btn_ctrl[4].SetBitmapID(IDB_PDVR_RUN_NOR, IDB_PDVR_RUN_CLK, IDB_PDVR_RUN_OVR);

	m_btn_ctrl_rect[5] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[5].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[5], this, ID_APP_PDVR_BTN_6))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[5].SetBitmapID(IDB_SEARCH_NOR, IDB_SEARCH_CLK, IDB_SEARCH_OVR);

	m_btn_ctrl_rect[6] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[6].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[6], this, ID_APP_PDVR_BTN_7))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_btn_ctrl[6].SetBitmapID(IDB_SEARCH_NOR, IDB_SEARCH_CLK, IDB_SEARCH_OVR);
}

void CView_PDVR_rst::test_SetTimer()
{
	m_bTimer = FALSE;
}

void CView_PDVR_rst::recv_Appl(int nAppl)
{
	if (!m_bTimer)
		return;

	m_nRecvAppl_ID = nAppl;

	if (m_nCompAppl_ID == nAppl)
	{
		m_bTimer = FALSE;
	}
}

void CView_PDVR_rst::recv_Init()
{
	m_bTimer = FALSE;
	KillTimer(1);
}

void CView_PDVR_rst::OnControlbutton_click_Run_PDVR()
{
	if (m_bTimer)
		return;


	int nSel = m_ctrCombo[1].GetCurSel();
	if (nSel == -1)
	{
		AfxMessageBox(_T("OLTC 또는 DL을 선택해야 합니다."));
		return;
	}
	else
	{
		if (m_ctrList[0].GetCheckBox(0, 0) != CHECKBOX_CHECKED)
		{
			nSel = m_ctrCombo[2].GetCurSel();
			if (nSel == -1)
			{
				AfxMessageBox(_T("OLTC 또는 DL을 선택해야 합니다."));
				return;
			}
		}
	}

	int nCheck =0;
	for (int i = 0; i < m_ctrList[1].GetItemCount(); i++)
	{
		nCheck = m_ctrList[1].GetCheckBox(i, 3);
		if (nCheck == CHECKBOX_CHECKED)
		{
			AfxMessageBox(_T("신규 검토 대상을 해제 후 전압 검토를 수행하세요."));
			return;
		}
	}

	for (int i = 0; i < m_ctrList[6].GetItemCount(); i++)
	{
		nCheck = m_ctrList[6].GetCheckBox(i, 3);
		if (nCheck == CHECKBOX_CHECKED)
		{
			AfxMessageBox(_T("신규 검토 대상을 해제 후 전압 검토를 수행하세요."));
			return;
		}
	}


	/////////////// 날짜
	COleDateTime timeData[2];
	CString strTime[2];
	m_ctrDate[0].GetTime(timeData[0]);
	m_ctrDate[1].GetTime(timeData[1]);

	if (timeData[0] > timeData[1])
	{
		AfxMessageBox(_T("기간 범위 설정 오류"));
		return;
	}

	CView_PDVR_rst_RUN_Dlg Dlg;

	Dlg.m_nMode = 0;
	Dlg.m_timeData[0] = timeData[0];
	Dlg.m_timeData[1] = timeData[1];

	if (Dlg.DoModal() == IDOK)
	{
		timeData[0] = Dlg.m_timeData[0];
		timeData[1] = Dlg.m_timeData[1];

		m_ctrDate[0].SetTime(timeData[0]);
		m_ctrDate[1].SetTime(timeData[1]);
	}
	else
	{
		return;
	}


	strTime[0].Format(_T("%s"), timeData[0].Format(_T("%Y%m%d")));
	strTime[1].Format(_T("%s"), timeData[1].Format(_T("%Y%m%d")));


	/////////////// mtr

	CString strTRidx, strOLTC;
	CString strTRType;
	nCheck = 0;
	int nOLTC = 0;
	int nDL_Idx;
	for (int i = 0; i < m_ctrList[0].GetItemCount(); i++)
	{
		strTRidx = m_ctrList[0].GetItemText(i, 2);
		strTRType = m_ctrList[0].GetItemText(i, 3);

		if (_wtoi(strTRType) == 0)
		{
			strOLTC = strTRidx;
			if (m_ctrList[0].GetCheckBox(i, 0) == CHECKBOX_CHECKED)
				nOLTC = 1;
		}
		else
		{
			nCheck = m_ctrList[0].GetCheckBox(i, 0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PDVRFLAG"), _wtoi(strTRidx), (double)nCheck);
		}
	}

	
	////////////////// 신규 검토 분산전원
	int nZoneMode = 2;
	if (nOLTC == 1)
	{
		nZoneMode = 1;
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_TGDL"), 1, (double)_wtoi(strOLTC));
	}
	else
	{
		int nSel = m_ctrCombo[2].GetCurSel();
		nDL_Idx = (int)m_ctrCombo[2].GetItemData(nSel);
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_TGDL"), 1, (double)nDL_Idx);
	}
	PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_ZONEMODE"), 1, (double)nZoneMode);

//	strTime[0] = _T("20210401");
//	strTime[1] = _T("20210410");
	/////////////////////
	PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_SRTHIS"), 1, (double)_wtoi(strTime[0]));
	PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_ENDHIS"), 1, (double)_wtoi(strTime[1]));
	

//	PUTDOUBLE2VALUE(_T("DGTR_DYN_UIN"), _T("DGTR_TGINDEX"), 1, (double)_wtoi(strGENidx));

	CDataManager* pDataMng = CDataManager::Instance();
	//pDataMng->Excute_Appl(_T("8"));
	pDataMng->Excute_Appl(_T("8"), GetVIewID());

	m_bTimer = TRUE;
	m_nCompAppl_ID = 8;
	SetTimer(1, 100, NULL);


	
}

void CView_PDVR_rst::OnControlbutton_click_Opt()
{
	if (m_bTimer)
		return;

	////////////////// 신규 검토 분산전원

	int nCheck = 0;
	CString strGENidx;
	for (int i = 0; i < m_ctrList[1].GetItemCount(); i++)
	{
		nCheck = m_ctrList[1].GetCheckBox(i, 3);
		if (nCheck != CHECKBOX_CHECKED)
			continue;
		strGENidx = m_ctrList[1].GetItemText(i, 4);
	}
	if (nCheck == 0)
	{
		for (int i = 0; i < m_ctrList[6].GetItemCount(); i++)
		{
			nCheck = m_ctrList[6].GetCheckBox(i, 3);
			if (nCheck != CHECKBOX_CHECKED)
				continue;
			strGENidx = m_ctrList[6].GetItemText(i, 4);
		}
	}

	if (nCheck == 0)
	{
		AfxMessageBox(_T("신규 검토 대상이 없습니다."));
		return;
	}

	/////////////// 날짜
	COleDateTime timeData[2];
	CString strTime[2];
	m_ctrDate[0].GetTime(timeData[0]);
	m_ctrDate[1].GetTime(timeData[1]);

	if (timeData[0] > timeData[1])
	{
		AfxMessageBox(_T("기간 범위 설정 오류"));
		return;
	}

	/////////////// mtr

	CString strTRidx,strOLTC;
	CString strTRType;
	
	int nOLTC = 0;
	int nDL_Idx;
	for (int i = 0; i < m_ctrList[0].GetItemCount(); i++)
	{
		strTRidx = m_ctrList[0].GetItemText(i, 2);
		strTRType = m_ctrList[0].GetItemText(i, 3);

		if (_wtoi(strTRType) == 0)
		{
			strOLTC = strTRidx;
			if (m_ctrList[0].GetCheckBox(i, 0) == CHECKBOX_CHECKED)
				nOLTC = 1;
		}
		else
		{
			nCheck = m_ctrList[0].GetCheckBox(i, 0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PDVRFLAG"), _wtoi(strTRidx), (double)nCheck);
		}
	}
	/////////////////////////////////////////////////////
	int nType;
	nType = GETVALUE(int, _T("gen_sta"), _T("gen_type"), _wtoi(strGENidx));
	CView_PDVR_rst_RUN_Dlg Dlg;

	Dlg.m_nGenType = (nType == 5 ? 1 : 0);
	Dlg.m_nTrIndex = _wtoi(strOLTC);
	Dlg.m_nMode = 1;
	Dlg.m_timeData[0] = timeData[0];
	Dlg.m_timeData[1] = timeData[1];

	if (Dlg.DoModal() == IDOK)
	{
		timeData[0] = Dlg.m_timeData[0];
		timeData[1] = Dlg.m_timeData[1];

		m_ctrDate[0].SetTime(timeData[0]);
		m_ctrDate[1].SetTime(timeData[1]);
	}
	else
	{
		return;
	}


	strTime[0].Format(_T("%s"), timeData[0].Format(_T("%Y%m%d")));
	strTime[1].Format(_T("%s"), timeData[1].Format(_T("%Y%m%d")));

	//////////////////////////////////////////////////////////////////

	int nZoneMode = 2;
	if (nOLTC == 1)
	{
		nZoneMode = 1;
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_TGDL"), 1, (double)_wtoi(strOLTC));
	}
	else
	{
		int nSel = m_ctrCombo[2].GetCurSel();
		nDL_Idx = (int)m_ctrCombo[2].GetItemData(nSel);
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_TGDL"), 1, (double)nDL_Idx);
	}
	PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_ZONEMODE"), 1, (double)nZoneMode);

	/*int nSel = m_ctrCombo[2].GetCurSel();
	m_ctrCombo[3].SetCurSel(nSel);
	OnPDVR_rstCombo4SelectChange();
	Update_DGTRData();
	Update_PCEData();
	
	return;*/

	//strTime[0] = _T("20210401");
	//strTime[1] = _T("20210410");
	/////////////////////
	PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_SRTHIS"), 1, (double)_wtoi(strTime[0]));
	PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_ENDHIS"), 1, (double)_wtoi(strTime[1]));
	
	//PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_TGTTR"), 1, (double)_wtoi(strGENidx)); // 211130 

	PUTDOUBLE2VALUE(_T("DGTR_DYN_UIN"), _T("DGTR_TGINDEX"), 1, (double)_wtoi(strGENidx));
	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_RUN_MODE"), 1, (double) 3);

	CDataManager* pDataMng = CDataManager::Instance();
	//pDataMng->Excute_Appl_test(_T("12"));
	pDataMng->Excute_Appl(_T("12/8/9"), GetVIewID());

	m_bTimer = TRUE;
	m_nCompAppl_ID = 9;
	SetTimer(1, 100, NULL);
}

void CView_PDVR_rst::OnControlbutton_click_Rpt()
{
	if (m_bTimer)
		return;

	if (m_Array_Graph.GetSize() == 0)
	{
		AfxMessageBox(_T("전압검토 결과가 없습니다."));
		return;
	}


	CXLSAutomation XL;
	Report_PDVR(&XL,2);
}

void CView_PDVR_rst::OnControlbutton_click_Cal()
{
	if (m_bTimer)
		return;

	if (m_ctrList[3].GetItemCount() == 0)
	{
		AfxMessageBox(_T("분산형전원 기술검토 결과가 없습니다."));
		return;
	}


	CXLSAutomation XL;
	Report_PCE(&XL);

	

}

void CView_PDVR_rst::OnControlbutton_click_Run_PCE()
{
	if (m_bTimer)
		return;

	CDataManager* pDataMng = CDataManager::Instance();
//	pDataMng->Excute_Appl(1);

	m_bTimer = TRUE;
	SetTimer(3, 100, NULL);

	
}

void CView_PDVR_rst::OnControlbutton_click_Search1()
{
	CString strName,strFind;

	m_ctrEdit[0].GetWindowText(strFind);

	int nCurRow1 = m_ctrList[1].GetCurSel();
	int nCurRow = m_ctrList[1].GetSelectionMark();

	nCurRow++;

	if (nCurRow < -1 || nCurRow >  m_ctrList[1].GetItemCount())
		nCurRow = 0;

	BOOL bFind = FALSE;
	for (int i = nCurRow ; i < m_ctrList[1].GetItemCount(); i++)
	{
		strName = m_ctrList[1].GetItemText(i, 1);
		if (strName.Find(strFind) > -1)
		{
			m_ctrList[1].EnsureVisible(i,FALSE);
			//m_ctrList[1].SetSelectionMark(i);
			m_ctrList[1].SetCurSel(i);
			bFind = TRUE;
			break; 
		}
	}
	if (!bFind)
	{
		AfxMessageBox(_T("찾는 문자열이 없습니다."));
	}

}

void CView_PDVR_rst::OnControlbutton_click_Search2()
{
	CString strName, strFind;

	m_ctrEdit[1].GetWindowText(strFind);

	int nCurRow1 = m_ctrList[6].GetCurSel();
	int nCurRow = m_ctrList[6].GetSelectionMark();

	nCurRow++;

	if (nCurRow < -1 || nCurRow >  m_ctrList[6].GetItemCount())
		nCurRow = 0;

	BOOL bFind = FALSE;
	for (int i = nCurRow; i < m_ctrList[6].GetItemCount(); i++)
	{
		strName = m_ctrList[6].GetItemText(i, 1);
		if (strName.Find(strFind) > -1)
		{
			m_ctrList[6].EnsureVisible(i, FALSE);
			//m_ctrList[1].SetSelectionMark(i);
			m_ctrList[6].SetCurSel(i);
			bFind = TRUE;
			break;
		}
	}
	if (!bFind)
	{
		AfxMessageBox(_T("찾는 문자열이 없습니다."));
	}

}

void CView_PDVR_rst::OnPDVR_rst_Edit_1_Change()
{
	
	OnControlbutton_click_Search1();
}


void CView_PDVR_rst::OnPDVR_rst_Edit_2_Change()
{

	OnControlbutton_click_Search2();
}


void CView_PDVR_rst::Update_Combo1()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CStringArray Array_SS;

	pDataMng->GetSSName_array(&Array_SS);

	for (int i = 0; i < Array_SS.GetSize(); i++)
	{
		m_ctrCombo[0].AddString(Array_SS.GetAt(i));
	}
}

void CView_PDVR_rst::OnPDVR_rstCombo1SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	CString	strSS;
	CStringArray Array_MTR;


	m_ctrCombo[0].GetLBText(nSel, strSS);

	m_ctrCombo[1].ResetContent();
	m_ctrCombo[2].ResetContent();
	m_ctrCombo[3].ResetContent();

	CDataManager* pDataMng = CDataManager::Instance();

	pDataMng->GetMTRName_array(strSS, &Array_MTR);

	for (int i = 0; i < Array_MTR.GetSize(); i++)
	{
		m_ctrCombo[1].AddString(Array_MTR.GetAt(i));
	}

	m_ctrList[0].DeleteAllItems();
	m_ctrList[1].DeleteAllItems();
	m_ctrList[6].DeleteAllItems();

	//test_clear();

	RedrawWindow();
}

void CView_PDVR_rst::OnPDVR_rstCombo2SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	CString	strSS,strMTR;
	CStringArray Array_DL;


	m_ctrCombo[0].GetLBText(nSel, strSS);

	nSel = m_ctrCombo[1].GetCurSel();

	if (nSel == -1)
		return;
	int nCount = m_ctrList[0].GetItemCount();

	m_ctrCombo[1].GetLBText(nSel, strMTR);

	m_ctrList[0].DeleteAllItems();
	m_ctrList[1].DeleteAllItems();
	m_ctrList[6].DeleteAllItems();

	DeleteItem_List_2();



	m_ctrCombo[2].ResetContent();
	m_ctrCombo[3].ResetContent();
	CDataManager* pDataMng = CDataManager::Instance();
	CIntArray Array_DL_Idx;
	pDataMng->GetDLName_array(strSS, &Array_DL,strMTR, &Array_DL_Idx);
	CString strDL,strIdx;
	int nIdx;
	//for (int i = 0; i < Array_DL.GetSize(); i++)
	//{
	//	strDL = Array_DL.GetAt(i);
	//	nIdx = Array_DL_idx.GetAt(i);// pDataMng->GetDLIndex(strDL);

	//	if (nIdx == 0)
	//	{
	//		continue;
	//	}

	//	strIdx.Format(_T("%d"), nIdx);

	//	/*m_ctrList[0].InsertItem(m_ctrList[0].GetItemCount(), strDL,  RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	//	m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount()-1, 1,strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);*/
	////	m_ctrList[0].setdate
	//	m_ctrCombo[2].AddString(strDL);
	//	m_ctrCombo[2].SetItemData(i,nIdx);
	//	m_ctrCombo[3].AddString(strDL);
	//	m_ctrCombo[3].SetItemData(i, nIdx);
	//}

	for (int i = 0; i < Array_DL.GetSize(); i++)
	{
		m_ctrCombo[2].AddString(Array_DL.GetAt(i));
		m_ctrCombo[3].AddString(Array_DL.GetAt(i));
	}

	CString strName;
//	int nIdx;
	for (int i = 0; i < m_ctrCombo[2].GetCount(); i++)
	{
		m_ctrCombo[2].GetLBText(i, strName);

		for (int k = 0; k < Array_DL.GetSize(); k++)
		{
			if (Array_DL.GetAt(k) == strName)
			{
				m_ctrCombo[2].SetItemData(i, (DWORD_PTR)Array_DL_Idx.GetAt(k));
				m_ctrCombo[3].SetItemData(i, (DWORD_PTR)Array_DL_Idx.GetAt(k));
				break;
			}
		}

	}



//	RedrawWindow();
}

void CView_PDVR_rst::OnPDVR_rstCombo3SelectChange()
{

	int nSel = m_ctrCombo[2].GetCurSel();

	if (nSel == -1)
		return;

	DeleteItem_List_2();

	m_ctrList[1].DeleteAllItems();
	m_ctrList[6].DeleteAllItems();

	CString	strDL;

	int nDL_idx;
	m_ctrCombo[2].GetLBText(nSel, strDL);
	nDL_idx = (int)m_ctrCombo[2].GetItemData(nSel);
	CDataManager* pDataMng = CDataManager::Instance();
	
	int nND_idx, nDB_idx;
	int nType;
	int nBR_idx;
	CString strIdx;
	CString strName;
	int nTrPDVRflag;

	int nCount = theAppDataMng->GetTableRealCount(_T("tr_sta"));
	for (int i = 1; i <= (int)nCount; i++)
	{
		nType = GETVALUE(int, _T("tr_sta"), _T("tr_type"), i);
		if (nType != 3)
			continue;

		nBR_idx = GETVALUE(int, _T("tr_sta"), _T("tr_ii_br"), i);
		nND_idx = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), nBR_idx);

		nDB_idx = GETVALUE(int, _T("nd_dyn_ncpo"), _T("nd_ii_dl"), nND_idx);

		if (nDB_idx != nDL_idx)
			continue;


		nTrPDVRflag = GETVALUE(int, "tr_dyn_uin", "tr_pdvrflag", i);
	
		strName = CA2W(GETSTRING(("tr_sta"), ("tr_nm"), i)).m_psz;
		strIdx.Format(_T("%d"), i);
		/*m_ctrList[1].InsertColumn(0, _T(""), HDF_LEFT, 20);
		m_ctrList[1].InsertColumn(1, _T("제어 대상"), HDF_LEFT, 150);
		m_ctrList[1].InsertColumn(2, _T("종류"), HDF_LEFT, 80);
		m_ctrList[1].InsertColumn(3, _T(""), HDF_LEFT, 30);
		m_ctrList[1].InsertColumn(4, _T("idx"), HDF_LEFT, 0);
		m_ctrList[1].InsertColumn(5, _T("dump"), HDF_LEFT, 0);*/

		m_ctrList[0].InsertItem(m_ctrList[0].GetItemCount(), _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 1, strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	//	m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 2, _T("SVR"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	//	m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 3, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 2, strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 3, _T("1"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

		if (nTrPDVRflag == 0)
			m_ctrList[0].SetCheckBox(m_ctrList[0].GetItemCount() - 1, 0, CHECKBOX_NORMAL);
		else
			m_ctrList[0].SetCheckBox(m_ctrList[0].GetItemCount() - 1, 0, CHECKBOX_CHECKED);
	}


	CStringArray ArrayData;
	ArrayData.Add(_T("일정전압"));
	ArrayData.Add(_T("일정역률"));
	ArrayData.Add(_T("일정무효전력"));
	ArrayData.Add(_T("전압범위"));
	ArrayData.Add(_T("Q-V곡선"));

	int nCtrlType;
	int nCheck; 
	CString strCtrlMode;

	nCount = theAppDataMng->GetTableRealCount(_T("gen_sta"));
	for (int i = 1; i <= (int)nCount; i++)
	{
		nND_idx = GETVALUE(int, _T("gen_sta"), _T("gen_ii_nd"), i);
		nDB_idx = GETVALUE(int, _T("nd_dyn_ncpo"), _T("nd_ii_dl"), nND_idx);

		PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PDVRFLAG"),i, (double)0.);
		if (nDB_idx != nDL_idx)
			continue;

		nType = GETVALUE(int, _T("gen_dyn_uin"), _T("gen_mvarconmode"), i);
		nCtrlType = GETVALUE(int, _T("gen_dyn_uin"), _T("gen_pdvrflag"), i);
		strCtrlMode.Empty();
		if(nType > 0)
			strCtrlMode = ArrayData.GetAt(nType - 1);

		if (nCtrlType == 0)
			nCheck = CHECKBOX_NORMAL;
		else
			nCheck = CHECKBOX_CHECKED;


		strName = CA2W(GETSTRING(("gen_sta"), ("gen_nm"), i)).m_psz;
		strIdx.Format(_T("%d"), i);

		/////////////// 신규 검토가 있으면 나머니 모두 설정 해줘야된다

		if (nType == 0)
		{

			m_ctrList[6].InsertItem(m_ctrList[6].GetItemCount(), _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[6].SetItemText(m_ctrList[6].GetItemCount() - 1, 1, strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
			m_ctrList[6].SetItemText(m_ctrList[6].GetItemCount() - 1, 2, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[6].SetItemText(m_ctrList[6].GetItemCount() - 1, 3, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[6].SetItemText(m_ctrList[6].GetItemCount() - 1, 4, strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[6].SetCheckBox(m_ctrList[6].GetItemCount() - 1, 0, nCheck);
			m_ctrList[6].SetCheckBox(m_ctrList[6].GetItemCount() - 1, 3, CHECKBOX_NORMAL);
		}
		else
		{

			m_ctrList[1].InsertItem(m_ctrList[1].GetItemCount(), _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 1, strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
			m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 2, strCtrlMode, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 3, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 4, strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[1].SetCheckBox(m_ctrList[1].GetItemCount() - 1, 0, nCheck);
			m_ctrList[1].SetCheckBox(m_ctrList[1].GetItemCount() - 1, 3, CHECKBOX_NORMAL);
			//m_ctrList[1].SetItemInfo(m_ctrList[1].GetItemCount() - 1, 2, LIST_TYPE_COMBO, &ArrayData);
		}

	
		/*m_ctrList[1].InsertColumn(0, _T(""), HDF_LEFT, 20);
		m_ctrList[1].InsertColumn(1, _T("제어 대상"), HDF_LEFT, 150);
		m_ctrList[1].InsertColumn(2, _T("종류"), HDF_LEFT, 80);
		m_ctrList[1].InsertColumn(3, _T(""), HDF_LEFT, 30);
		m_ctrList[1].InsertColumn(4, _T("idx"), HDF_LEFT, 0);
		m_ctrList[1].InsertColumn(5, _T("dump"), HDF_LEFT, 0);*/

	}




	m_ctrList[0].RedrawWindow();
	m_ctrList[1].RedrawWindow();


	//Delete_GraphData();

	//pDataMng->GetData_Graph(nDL_idx, &m_Array_Graph);


	RedrawWindow();

}

void CView_PDVR_rst::OnPDVR_rstCombo4SelectChange()
{

	int nSel = m_ctrCombo[3].GetCurSel();

	if (nSel == -1)
		return;
	
	CString	strDL;
	m_ctrCombo[3].GetLBText(nSel, strDL);
	
	CDataManager* pDataMng = CDataManager::Instance();
	int nDL_idx;// = pDataMng->GetDLIndex(strDL);
	nDL_idx = (int)m_ctrCombo[2].GetItemData(nSel);
	Delete_GraphData();

	pDataMng->GetData_Graph(nDL_idx, &m_Array_Graph);

	Update_GraphData();

	RedrawWindow(m_rectPDVR[1]);
}

void CView_PDVR_rst::DeleteItem_List_2()
{
	m_ctrList[0].DeleteAllItems();

	m_ctrList[0].InsertItem(m_ctrList[0].GetItemCount(), _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 1, _T("OLTC"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
//	m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 2, _T("OLTC"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
//	m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 3, _T("0"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
//	m_ctrList[0].SetItemText(m_ctrList[0].GetItemCount() - 1, 3, _T("-1"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

	m_ctrList[0].SetCheckBox(m_ctrList[0].GetItemCount() - 1, 0, CHECKBOX_NORMAL);
//	m_ctrList[1].SetItemImage(m_ctrList[1].GetItemCount() - 1, 3, 0,TRUE);

	int nSel = m_ctrCombo[0].GetCurSel();
	if (nSel == -1)
		return;

	CString	strSS, strMTR;
	
	m_ctrCombo[0].GetLBText(nSel, strSS);

	nSel = m_ctrCombo[1].GetCurSel();
	if (nSel == -1)
		return;
	m_ctrCombo[1].GetLBText(nSel, strMTR);


	int								nTRCnt(theAppDataMng->GetTableMaxCount(_T("tr_sta")));
	if ( nTRCnt == 0)														return;

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

		nTrPDVRflag = GETVALUE(int, "tr_dyn_uin", "tr_pdvrflag", i);
		if (nTrPDVRflag == 1)
			m_ctrList[0].SetCheckBox(0, 0, CHECKBOX_CHECKED);

		strTrIdx.Format(_T("%d"), i);
		m_ctrList[0].SetItemText(0, 2, strTrIdx);
		m_ctrList[0].SetItemText(0, 3, _T("0"));


		break;
	}
}

void CView_PDVR_rst::OnPDVR_ListCtrlClick_1(NMHDR *pNMHDR, LRESULT *pResult)
{
	return;
	//DeleteItem_List_2();

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;
	CString strIdx = m_ctrList[0].GetItemText(nRow, 1);
	CString strName = m_ctrList[0].GetItemText(nRow, 0);

	//if (strName == _T("태감"))
	//{
	//	m_ctrList[1].SetCheckBox(0, 0, CHECKBOX_CHECKED);
	//	test_equipment_data();

	//	test_protected_list(0);

	//}
	//else
	//{
	//	//// 초기화
	//}

	//
	//return;
	/////////////////////////////////////////////
	CString strDLID;
	int nDL_idx = _wtoi(strIdx);
	int nND_idx,nDB_idx;
	int nType;
	int nBR_idx;

	int nCount = theAppDataMng->GetTableRealCount(_T("tr_sta"));
	for (int i = 1; i <= (int)nCount; i++)
	{
		nType = GETVALUE(int, _T("tr_sta"), _T("tr_type"), i);
		if (nType != 3)
			continue;

		nBR_idx = GETVALUE(int, _T("tr_sta"), _T("tr_ii_br"), i);
		nND_idx = GETVALUE(int, _T("br_sta"), _T("br_ii_fnd"), i);

		nDB_idx = GETVALUE(int, _T("nd_dyn_ncpo"), _T("nd_ii_dl"), nND_idx);

		if (nDB_idx != nDL_idx)
			continue;



		strName = CA2W(GETSTRING(("tr_sta"), ("tr_nm"), i)).m_psz;
		strIdx.Format(_T("%d"), i);
		/*m_ctrList[1].InsertColumn(0, _T(""), HDF_LEFT, 20);
		m_ctrList[1].InsertColumn(1, _T("제어 대상"), HDF_LEFT, 150);
		m_ctrList[1].InsertColumn(2, _T("종류"), HDF_LEFT, 80);
		m_ctrList[1].InsertColumn(3, _T(""), HDF_LEFT, 30);
		m_ctrList[1].InsertColumn(4, _T("idx"), HDF_LEFT, 0);
		m_ctrList[1].InsertColumn(5, _T("dump"), HDF_LEFT, 0);*/

		m_ctrList[1].InsertItem(m_ctrList[1].GetItemCount(), _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 1, strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 2, _T("SVR"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 3, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 4, strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

		m_ctrList[1].SetCheckBox(m_ctrList[1].GetItemCount() - 1, 0, CHECKBOX_NORMAL);
	}

	nCount = theAppDataMng->GetTableRealCount(_T("gen_sta"));
	for (int i = 1; i <= (int)nCount; i++)
	{
		nND_idx = GETVALUE(int, _T("gen_sta"), _T("gen_ii_nd"), i);
		nDB_idx = GETVALUE(int, _T("nd_dyn_ncpo"), _T("nd_ii_dl"), nND_idx);

		if(nDB_idx != nDL_idx)
			continue;

		nType = GETVALUE(int, _T("gen_dyn_uin"), _T("gen_mvarconmode"), i);
		if(nType == 0)
			continue;

		strName = CA2W(GETSTRING(("gen_sta"), ("gen_nm"), i)).m_psz;
		strIdx.Format(_T("%d"), i);
		/*m_ctrList[1].InsertColumn(0, _T(""), HDF_LEFT, 20);
		m_ctrList[1].InsertColumn(1, _T("제어 대상"), HDF_LEFT, 150);
		m_ctrList[1].InsertColumn(2, _T("종류"), HDF_LEFT, 80);
		m_ctrList[1].InsertColumn(3, _T(""), HDF_LEFT, 30);
		m_ctrList[1].InsertColumn(4, _T("idx"), HDF_LEFT, 0);
		m_ctrList[1].InsertColumn(5, _T("dump"), HDF_LEFT, 0);*/

		m_ctrList[1].InsertItem(m_ctrList[1].GetItemCount(), _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 1, strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 2, _T("DG"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 3, _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 4, strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

		m_ctrList[1].SetCheckBox(m_ctrList[1].GetItemCount() - 1, 0, CHECKBOX_NORMAL);
	}
	


	
	m_ctrList[0].RedrawWindow();
	m_ctrList[1].RedrawWindow();
}

void CView_PDVR_rst::OnPDVR_ListCtrlDBClick_1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	if (nRow == -1)
		return;

	/*if (m_ctrList[0].GetCheckBox(nRow, 0) != CHECKBOX_CHECKED)
		return;*/

	CString strIdx = m_ctrList[0].GetItemText(nRow, 2);
	int nTrType = _wtoi(m_ctrList[0].GetItemText(nRow, 3));

	CView_PDVR_rst_TRDlg Dlg;
	Dlg.m_nIndex = _wtoi(strIdx);
	Dlg.m_nMode = nTrType;

	if (Dlg.DoModal() == IDCANCEL)
		return;


}

void CView_PDVR_rst::OnHdnItemclickList_2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int nCol = pNMLV->iSubItem;

	if (nCol != 0)
	{
		*pResult = 0;
		return;
	}
		
	CString strIdx;
	BOOL bCheck = FALSE;
	for (int i = 0; i < m_ctrList[1].GetItemCount(); i++)
	{
		if (m_ctrList[1].GetCheckBox(i, 0) == CHECKBOX_NORMAL)
		{
			bCheck = TRUE;
			break;
		}
	}

	for (int i = 0; i < m_ctrList[1].GetItemCount(); i++)
	{
		strIdx = m_ctrList[1].GetItemText(i, 4);
		if (bCheck)
		{
			
			m_ctrList[1].SetCheckBox(i, 0, CHECKBOX_CHECKED);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PDVRFLAG"), _wtoi(strIdx), (double)1);

		}
		else
		{
			m_ctrList[1].SetCheckBox(i, 0, CHECKBOX_NORMAL);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PDVRFLAG"), _wtoi(strIdx), (double)0);
		}
			


	}
	m_ctrList[1].RedrawWindow();






	*pResult = 0;
}

void CView_PDVR_rst::OnHdnItemclickList_7(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int nCol = pNMLV->iSubItem;

	if (nCol != 0)
	{
		*pResult = 0;
		return;
	}

	CString strIdx;
	BOOL bCheck = FALSE;
	for (int i = 0; i < m_ctrList[6].GetItemCount(); i++)
	{
		if (m_ctrList[6].GetCheckBox(i, 0) == CHECKBOX_NORMAL)
		{
			bCheck = TRUE;
			break;
		}
	}

	for (int i = 0; i < m_ctrList[6].GetItemCount(); i++)
	{
		strIdx = m_ctrList[6].GetItemText(i, 4);
		if (bCheck)
		{

			m_ctrList[6].SetCheckBox(i, 0, CHECKBOX_CHECKED);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PDVRFLAG"), _wtoi(strIdx), (double)1);

		}
		else
		{
			m_ctrList[6].SetCheckBox(i, 0, CHECKBOX_NORMAL);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PDVRFLAG"), _wtoi(strIdx), (double)0);
		}


	}
	m_ctrList[6].RedrawWindow();


	*pResult = 0;
}
void CView_PDVR_rst::OnPDVR_ListCtrlDBClick_2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	if (nRow == -1)
		return;

	CString strIdx = m_ctrList[1].GetItemText(nRow, 4);

	CView_PDVR_rst_DGDlg Dlg;
	Dlg.m_nIndex = _wtoi(strIdx);

	if (Dlg.DoModal() == IDCANCEL)
		return;


	CStringArray ArrayData;
	ArrayData.Add(_T("일정전압"));
	ArrayData.Add(_T("일정역률"));
	ArrayData.Add(_T("일정무효전력"));
	ArrayData.Add(_T("전압범위"));
	ArrayData.Add(_T("Q-V곡선"));

	int nPDVR_Mode = GETVALUE(int, _T("gen_dyn_uin"), _T("gen_mvarconmode"), Dlg.m_nIndex);

	m_ctrList[1].SetItemText(nRow, 2, ArrayData.GetAt(nPDVR_Mode - 1));

}

void CView_PDVR_rst::OnPDVR_ListCtrlDBClick_7(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	if (nRow == -1)
		return;

	CString strIdx = m_ctrList[6].GetItemText(nRow, 4);

	CView_PDVR_rst_DGDlg Dlg;
	Dlg.m_nIndex = _wtoi(strIdx);

	if (Dlg.DoModal() == IDCANCEL)
		return;


	CStringArray ArrayData;
	ArrayData.Add(_T("일정전압"));
	ArrayData.Add(_T("일정역률"));
	ArrayData.Add(_T("일정무효전력"));
	ArrayData.Add(_T("전압범위"));
	ArrayData.Add(_T("Q-V곡선"));

	int nPDVR_Mode = GETVALUE(int, _T("gen_dyn_uin"), _T("gen_mvarconmode"), Dlg.m_nIndex);

	m_ctrList[6].SetItemText(nRow, 2, ArrayData.GetAt(nPDVR_Mode - 1));
}

void CView_PDVR_rst::test_equipment_data()
{
	CDataManager* pDataMng = CDataManager::Instance();
	CString strPath;
	strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("equipment.txt"));


	FILE* stream = _wfopen(strPath, _T("r,ccs=UNICODE"));
	WCHAR ch, buffer[10000];

	CString strData[4], strT;
	int nCnt;


	while (feof(stream) == 0)
	{
		memset(buffer, 0x00, sizeof(buffer));
		fgetws(buffer, 10000, stream);
		nCnt = 0;
		while (AfxExtractSubString(strT, buffer, nCnt, _T(',')))
		{
			strData[nCnt] = strT;
			nCnt++;
		}
		if (nCnt < 2)
			break;

		m_ctrList[1].InsertItem(m_ctrList[1].GetItemCount(), _T(""), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount()-1, 1, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
		m_ctrList[1].SetItemText(m_ctrList[1].GetItemCount() - 1, 2, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

		m_ctrList[1].SetCheckBox(m_ctrList[1].GetItemCount() - 1, 0, CHECKBOX_CHECKED);
	}

	fclose(stream);
}



void CView_PDVR_rst::OnPDVR_ListCtrlDBClick_4(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	if (nRow == -1)
		return;


	CString strIdx = m_ctrList[3].GetItemText(nRow, 5); //// list 3,4,5

	int nND_idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_TND"), _wtoi(strIdx));

	CString strSend;

	strSend.Format(_T("999,%d,단선도이동"), nND_idx);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Send_WndMsg(WNDMSG_PROGRAMID_SLD, WNDMSG_PROGRAMID_HMI, strSend);


}

void CView_PDVR_rst::OnPDVR_ListCtrlDBClick_5(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	if (nRow == -1)
		return;


	CString strIdx = m_ctrList[4].GetItemText(nRow, 5); //// list 3,4,5

	int nND_idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_TND"), _wtoi(strIdx));

	CString strSend;

	strSend.Format(_T("999,%d,단선도이동"), nND_idx);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Send_WndMsg(WNDMSG_PROGRAMID_SLD, WNDMSG_PROGRAMID_HMI, strSend);


}

void CView_PDVR_rst::OnPDVR_ListCtrlDBClick_6(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	if (nRow == -1)
		return;


	CString strIdx = m_ctrList[5].GetItemText(nRow, 4); //// list 3,4,5

	int nND_idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_TND"), _wtoi(strIdx));

	CString strSend;

	strSend.Format(_T("999,%d,단선도이동"), nND_idx);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Send_WndMsg(WNDMSG_PROGRAMID_SLD, WNDMSG_PROGRAMID_HMI, strSend);

}

void CView_PDVR_rst::test_option_data()
{
	CDataManager* pDataMng = CDataManager::Instance();
	CString strPath;
	strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("option.txt"));


	FILE* stream = _wfopen(strPath, _T("r,ccs=UNICODE"));
	WCHAR ch, buffer[10000];

	CString strData[4], strT;
	int nCnt;


	while (feof(stream) == 0)
	{
		memset(buffer, 0x00, sizeof(buffer));
		fgetws(buffer, 10000, stream);
		nCnt = 0;
		while (AfxExtractSubString(strT, buffer, nCnt, _T(',')))
		{
			strData[nCnt] = strT;
			nCnt++;
		}
		if (nCnt < 4)
			break;

		m_strDate[0].Format(_T("%s"), strData[0]);
		m_strDate[1].Format(_T("%s"), strData[1]);
	}

	fclose(stream);
}

void CView_PDVR_rst::test_pdvr_graph(int nMode)
{
	/*for (int k = 0; k < m_Array_Graph.GetSize(); k++)
	{
		delete m_Array_Graph.GetAt(k);
	}
	m_Array_Graph.RemoveAll();

	CDataManager* pDataMng = CDataManager::Instance();
	CString strPath;
	if(nMode == 0)
		strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("voltage_cur.txt"));
	else
		strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("voltage_rst.txt"));

	FILE* stream = _wfopen(strPath, _T("r,ccs=UNICODE"));
	WCHAR ch, buffer[10000];

	CString strData[3], strT;
	int nCnt;

	CGraph_info* pData;
	if (stream)
	{
		while (feof(stream) == 0)
		{
			memset(buffer, 0x00, sizeof(buffer));
			fgetws(buffer, 10000, stream);
			nCnt = 0;
			while (AfxExtractSubString(strT, buffer, nCnt, _T(',')))
			{
				strData[nCnt] = strT;
				nCnt++;
			}
			if (nCnt < 3)
				break;

			pData = new CGraph_info();
			m_Array_Graph.Add(pData);

			pData->m_nType = 1;
			pData->m_nNodeID = _wtoi(strData[0]);
			pData->m_nNodeID_Prev = _wtoi(strData[1]);
			pData->m_dCurrValue = _wtof(strData[2]) / 1000;

		}

		fclose(stream);
	}
	

	if (m_Array_Graph.GetSize() > 0)
	{
		pData = m_Array_Graph.GetAt(0);

		pData->m_nNodeID_Prev = -1;
		pData->m_nCount = 0;

		m_nNode_MaxCount = 0;

		CGraph_info* pData_prev;
		for (int i = 1; i < m_Array_Graph.GetSize(); i++)
		{
			pData = m_Array_Graph.GetAt(i);


			for (int k = 0; k < m_Array_Graph.GetSize(); k++)
			{
				pData_prev = m_Array_Graph.GetAt(k);

				if (pData_prev->m_nNodeID == pData->m_nNodeID_Prev)
				{
					break;
				}

			}

			pData->m_nCount = pData_prev->m_nCount + 1;
			pData->m_dPrevValue = pData_prev->m_dCurrValue;

			if (m_nNode_MaxCount < pData->m_nCount + 1 )
				m_nNode_MaxCount = pData->m_nCount + 1;
		}

	}*/

	/////////////////////////////////////////

	CDataManager* pDataMng = CDataManager::Instance();
	CString strPath;

	if (nMode == 0)
		strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("voltage_eq_cur.txt"));
	else
		strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("voltage_eq_rst.txt"));

	FILE* stream = _wfopen(strPath, _T("r,ccs=UNICODE"));
	WCHAR ch, buffer[10000];

	CString strData[3], strT;
	int nCnt;

	m_ctrList[2].DeleteAllItems();

	if (stream)
	{
		while (feof(stream) == 0)
		{
			memset(buffer, 0x00, sizeof(buffer));
			fgetws(buffer, 10000, stream);
			nCnt = 0;
			while (AfxExtractSubString(strT, buffer, nCnt, _T(',')))
			{
				strData[nCnt] = strT;
				nCnt++;

			}

			if (nCnt < 2)
				break;

			m_ctrList[2].InsertItem(m_ctrList[2].GetItemCount(), strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
			m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
		}

		fclose(stream);
	}

}

void CView_PDVR_rst::test_protected_list(int nMode)
{
	CDataManager* pDataMng = CDataManager::Instance();
	CString strPath;
	strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("오동작.txt"));


	FILE* stream = _wfopen(strPath, _T("r,ccs=UNICODE"));
	WCHAR ch, buffer[10000];

	CString strData[5],strT;
	int nCnt;


	m_ctrList[3].DeleteAllItems();

	while (feof(stream) == 0)
	{
		memset(buffer, 0x00, sizeof(buffer));
		fgetws(buffer,10000,stream);
		nCnt = 0;
		while (AfxExtractSubString(strT, buffer, nCnt, _T(',')))
		{
			strData[nCnt] = strT;
			nCnt++;
		}
		if(nCnt < 4)
			break;

		m_ctrList[3].InsertItem(m_ctrList[3].GetItemCount(), strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

		if (nMode != 0)
		{
			m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 2, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 3, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 4, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		}
		
	}

	fclose(stream);
	///////////////////////////////////////////////////////////////////////////////////////////////////
	strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("부동작.txt"));
	
	stream = _wfopen(strPath, _T("r,ccs=UNICODE"));
	
	m_ctrList[4].DeleteAllItems();

	while (feof(stream) == 0)
	{
		memset(buffer, 0x00, sizeof(buffer));
		fgetws(buffer, 10000, stream);
		nCnt = 0;
		while (AfxExtractSubString(strT, buffer, nCnt, _T(',')))
		{
			strData[nCnt] = strT;
			nCnt++;

		}

		if (nCnt < 4)
			break;

		m_ctrList[4].InsertItem(m_ctrList[4].GetItemCount(), strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

		if (nMode != 0)
		{
			m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 2, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 3, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 4, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		}
	}

	fclose(stream);
	///////////////////////////////////////////////////////////////////////////////////////////////////
	strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("단락용량.txt"));

	stream = _wfopen(strPath, _T("r,ccs=UNICODE"));

	m_ctrList[5].DeleteAllItems();

	while (feof(stream) == 0)
	{
		memset(buffer, 0x00, sizeof(buffer));
		fgetws(buffer, 10000, stream);
		nCnt = 0;
		while (AfxExtractSubString(strT, buffer, nCnt, _T(',')))
		{
			strData[nCnt] = strT;
			nCnt++;

		}
		if (nCnt < 4)
			break;

		m_ctrList[5].InsertItem(m_ctrList[5].GetItemCount(), strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		if (nMode != 0)
		{
			m_ctrList[5].SetItemText(m_ctrList[5].GetItemCount() - 1, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[5].SetItemText(m_ctrList[5].GetItemCount() - 1, 2, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[5].SetItemText(m_ctrList[5].GetItemCount() - 1, 3, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		}
	}

	fclose(stream);


	m_ctrList[3].RedrawWindow();
	m_ctrList[4].RedrawWindow();
	m_ctrList[5].RedrawWindow();
}



void CView_PDVR_rst::test_clear()
{
	m_nMode = -1;
	m_ctrList[2].DeleteAllItems();
	m_ctrList[3].DeleteAllItems();
	m_ctrList[4].DeleteAllItems();
	m_ctrList[5].DeleteAllItems();


}

void CView_PDVR_rst::test_Draw_Graph(int nMode,CDC* pDC, Graphics &graphics)
{
	CDataManager* pDataMng = CDataManager::Instance();
	CString strPath;

	if (nMode == 0)
		strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("graph_1.bmp"));
	else
		strPath.Format(_T("%s\\시연용\\%s"), pDataMng->MyPath(), _T("graph_3.bmp"));


	HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		strPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	
	if (hBmp)
	{
		::SelectObject(memDC, hBmp);
		pDC->BitBlt(m_rectPDVR[1].left, m_rectPDVR[1].top, m_rectPDVR[1].right, m_rectPDVR[1].bottom, &memDC, 0, 0, SRCCOPY);

	}
	
}

LRESULT CView_PDVR_rst::OnList2Ctrl_ComboMsg(WPARAM wp, LPARAM lp)
{
	int nPos, nRow,nCol;
	CString strIdx;
	CString strMsg;
	int nCheck = 0;

	int nCtrlID = (int)wp;

	strMsg.Format(_T("%s"), (wchar_t*)lp);

	nPos = strMsg.Find(_T(","));
	int nCtrlType = _wtoi(strMsg.Left(nPos));

	strMsg.Delete(0,nPos+1);
	nPos = strMsg.Find(_T(","));
	nRow = _wtoi(strMsg.Left(nPos));

	strMsg.Delete(0, nPos + 1);
	nPos = strMsg.Find(_T(","));
	nCol = _wtoi(strMsg.Left(nPos));
	
	if (m_ctrList[1].GetDlgCtrlID() == nCtrlID)
	{
		//nPos = m_ctrList[1].GetSelectionMark();
		strIdx = m_ctrList[1].GetItemText(nRow, 4);
		if (nCol == 0)
		{
			nCheck = m_ctrList[1].GetCheckBox(nRow, nCol);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PDVRFLAG"), _wtoi(strIdx), (double)nCheck);

		}
		else if (nCol == 2)
		{
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MVARCONMODE"), _wtoi(strIdx), (double)lp + 1);
		}
		else if (nCol == 3)
		{
			////////////////
			nCheck = m_ctrList[1].GetCheckBox(nRow, nCol);
			for (int i = 0; i < m_ctrList[1].GetItemCount(); i++)
			{
				if (nCheck == 0)
				{
					if (i != nRow)
						m_ctrList[1].SetCheckBox(i, 3, CHECKBOX_NORMAL);
				}
				else
				{
					if(i != nRow)
						m_ctrList[1].SetCheckBox(i, 3, CHECKBOX_DISABLE);
				}
			}

			for (int i = 0; i < m_ctrList[6].GetItemCount(); i++)
			{
				if (nCheck == 0)
				{
					m_ctrList[6].SetCheckBox(i, 3, CHECKBOX_NORMAL);
				}
				else
				{
					m_ctrList[6].SetCheckBox(i, 3, CHECKBOX_DISABLE);
				}
			}

		}
		
		m_ctrList[1].RedrawWindow();
		
	}
	else if (m_ctrList[6].GetDlgCtrlID() == nCtrlID)
	{
		strIdx = m_ctrList[6].GetItemText(nRow, 4);
		if (nCol == 0)
		{
			nCheck = m_ctrList[6].GetCheckBox(nRow, nCol);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PDVRFLAG"), _wtoi(strIdx), (double)nCheck);

		}
		else if (nCol == 2)
		{
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MVARCONMODE"), _wtoi(strIdx), (double)lp + 1);
		}
		else if (nCol == 3)
		{
			////////////////
			nCheck = m_ctrList[6].GetCheckBox(nRow, nCol);
			for (int i = 0; i < m_ctrList[6].GetItemCount(); i++)
			{
				if (nCheck == 0)
				{
					if (i != nRow)
						m_ctrList[6].SetCheckBox(i, 3, CHECKBOX_NORMAL);
				}
				else
				{
					if (i != nRow)
						m_ctrList[6].SetCheckBox(i, 3, CHECKBOX_DISABLE);
				}
			}

			for (int i = 0; i < m_ctrList[1].GetItemCount(); i++)
			{
				if (nCheck == 0)
				{
					m_ctrList[1].SetCheckBox(i, 3, CHECKBOX_NORMAL);
				}
				else
				{
					m_ctrList[1].SetCheckBox(i, 3, CHECKBOX_DISABLE);
				}
			}
		}
		m_ctrList[6].RedrawWindow();
	}
	else if (m_ctrList[0].GetDlgCtrlID() == nCtrlID)
	{
		strIdx = m_ctrList[0].GetItemText(nRow, 2);
		nCheck = m_ctrList[0].GetCheckBox(nRow, nCol);
		PUTDOUBLE2VALUE(_T("tr_dyn_uin"), _T("TR_PDVRFLAG"), _wtoi(strIdx), (double)nCheck);
	}

	return true;
}

void CView_PDVR_rst::Update_GraphData()
{
	
	m_ctrList[2].DeleteAllItems();

	CGraphData* pData;
	BOOL bOver = FALSE;
	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
	{
		pData = m_Array_Graph.GetAt(i);

		if (pData->m_nGNDIdx[0] > 0)
		{
			pData->m_dPDVR_pu_p[0][0] = GETVALUE(double, _T("bs_dyn_pdvro"), _T("bs_mxv0"), pData->m_nBS_idx[0]);
			pData->m_dPDVR_pu_p[0][1] = GETVALUE(double, _T("bs_dyn_pdvro"), _T("bs_mnv0"), pData->m_nBS_idx[0]);
			pData->m_dPDVR_pu_p[1][0] = GETVALUE(double, _T("bs_dyn_pdvro"), _T("bs_mxv"), pData->m_nBS_idx[0]);
			pData->m_dPDVR_pu_p[1][1] = GETVALUE(double, _T("bs_dyn_pdvro"), _T("bs_mnv"), pData->m_nBS_idx[0]);
		}

	
		pData->m_dPDVR_pu_c[0][0] = GETVALUE(double, _T("bs_dyn_pdvro"), _T("bs_mxv0"), pData->m_nBS_idx[1]);
		pData->m_dPDVR_pu_c[0][1] = GETVALUE(double, _T("bs_dyn_pdvro"), _T("bs_mnv0"), pData->m_nBS_idx[1]);
		pData->m_dPDVR_pu_c[1][0] = GETVALUE(double, _T("bs_dyn_pdvro"), _T("bs_mxv"), pData->m_nBS_idx[1]);
		pData->m_dPDVR_pu_c[1][1] = GETVALUE(double, _T("bs_dyn_pdvro"), _T("bs_mnv"), pData->m_nBS_idx[1]);

		if (pData->m_dPDVR_pu_c[0][0] >= 1.02)
			bOver = TRUE;
	}

	if (m_nMode == 2)
	{
		if (bOver)
		{
			m_ctrList[2].InsertItem(0, _T("과전압 발생"), RGB(255, 0, 102), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList[2].SetItemText(0, 1, _T("분산형전원의 전압제어장치가 필요함"), RGB(255, 0, 102), RGB(255, 255, 255), HDF_LEFT);
		}
		
		return;
	}
	else
	{
		m_ctrList[2].InsertItem(0, _T("OLTC 정정치 기준"), RGB(2, 30, 253), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(0, 1, _T("PT비:13200/110 , CT비:200/5"), RGB(2, 30, 253), RGB(255, 255, 255), HDF_LEFT);
		m_ctrList[2].InsertItem(1, _T("SVR 정정치 기준"), RGB(2, 30, 253), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(1, 1, _T("PT비:13200/120 , CT비:300/0.2"), RGB(2, 30, 253), RGB(255, 255, 255), HDF_LEFT);
	}
	

	CString strIdx,strName,strInfo,strType;
	double dVerf , dUr, dUx, dBW ;
	double dValue, dMx, dMn, dQV[4];
	for (int i = 0; i < m_ctrList[0].GetItemCount(); i++)
	{

		if(m_ctrList[0].GetCheckBox(i,0) != CHECKBOX_CHECKED)
			continue;;

		strName = m_ctrList[0].GetItemText(i, 1);
		strIdx = m_ctrList[0].GetItemText(i, 2);
		strType = m_ctrList[0].GetItemText(i, 3);

		dVerf	= GETVALUE(double, _T("tr_dyn_pdvro"), _T("tr_pavref"), _wtoi(strIdx));
		dUr		= GETVALUE(double, _T("tr_dyn_pdvro"), _T("tr_par"), _wtoi(strIdx));
		dUx		= GETVALUE(double, _T("tr_dyn_pdvro"), _T("tr_pax"), _wtoi(strIdx));
		dBW		= GETVALUE(double, _T("tr_dyn_pdvro"), _T("tr_pavbw"), _wtoi(strIdx));
		dMx		= GETVALUE(double, _T("tr_dyn_pdvro"), _T("tr_dvmmxv"), _wtoi(strIdx));
		dMn		= GETVALUE(double, _T("tr_dyn_pdvro"), _T("tr_dvmmnv"), _wtoi(strIdx));

		if(_wtoi(strType) == 0)
			strInfo.Format(_T("Verf:%.3lf Ur:%.3lf Ux:%.3lf BandWidth:%.2lf 전압상한:%.2lf 전압하한:%.2lf"), dVerf, dUr, dUx, dBW,dMx,dMn);
		else
			strInfo.Format(_T("Verf:%.3lf Ur:%.3lf Ux:%.3lf BandWidth:%.2lf"), dVerf, dUr, dUx, dBW);	

		m_ctrList[2].InsertItem(m_ctrList[2].GetItemCount(), strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 1, strInfo, RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 2, strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	}

	/*CStringArray ArrayData;
	ArrayData.Add(_T("일정전압"));
	ArrayData.Add(_T("일정역률"));
	ArrayData.Add(_T("일정무효전력"));
	ArrayData.Add(_T("전압범위"));
	ArrayData.Add(_T("Q-V곡선"));*/

	
	for (int i = 0; i < m_ctrList[1].GetItemCount(); i++)
	{
		if (m_ctrList[1].GetCheckBox(i, 0) != CHECKBOX_CHECKED)
			continue;;

		strName = m_ctrList[1].GetItemText(i, 1);
		strType = m_ctrList[1].GetItemText(i, 2);
		strIdx = m_ctrList[1].GetItemText(i, 4);

		if (strType == _T("전압범위"))
		{
			dMx = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMVUBREF"), _wtoi(strIdx));
			dMn = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMVLBREF"), _wtoi(strIdx));
			dValue = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMQVRATIO"), _wtoi(strIdx));

			strInfo.Format(_T("전압상한:%.2lf 전압하한:%.2lf QV ratio:%.2lf"), dMx, dMn, dValue);
		}
		else if (strType == _T("Q-V곡선"))
		{
			dQV[0] = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_QVCURVEV1"), _wtoi(strIdx));
			dQV[1] = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_QVCURVEV2"), _wtoi(strIdx));
			dQV[2] = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_QVCURVEV3"), _wtoi(strIdx));
			dQV[3] = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_QVCURVEV4"), _wtoi(strIdx));
		
		//	strInfo.Format(_T("QV curve V1:%.3lf V2:%.3lf V3:%.3lf V4:%.3lf"), dQV[0], dQV[2], dQV[2], dQV[3]);
			strInfo.Format(_T("V3:%.3lf V4:%.3lf"), /*dQV[0], dQV[2],*/ dQV[2], dQV[3]);
		}
		else if (strType == _T("일정전압"))
		{
			dValue = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMVREF"), _wtoi(strIdx));
		
			strInfo.Format(_T("일정전압:%.2lf"), dValue);
		}
		else if (strType == _T("일정무효전력"))
		{
			dValue = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMQVRATIO"), _wtoi(strIdx));
			
			strInfo.Format(_T("QV ratio:%.2lf"), dValue);
		}
		else 
		{
			dValue = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMPFREF"), _wtoi(strIdx));
			
			strInfo.Format(_T("일정역률:%.2lf"), dValue);
		}	

		m_ctrList[2].InsertItem(m_ctrList[2].GetItemCount(), strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 1, strInfo, RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 2, strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	}

	for (int i = 0; i < m_ctrList[6].GetItemCount(); i++)
	{
		if (m_ctrList[6].GetCheckBox(i, 0) != CHECKBOX_CHECKED)
			continue;;

		strName = m_ctrList[6].GetItemText(i, 1);
		strType = m_ctrList[6].GetItemText(i, 2);
		strIdx = m_ctrList[6].GetItemText(i, 4);

		if (strType == _T("전압범위"))
		{
			dMx = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMVUBREF"), _wtoi(strIdx));
			dMn = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMVLBREF"), _wtoi(strIdx));

			strInfo.Format(_T("전압상한:%.2lf 전압하한:%.2lf "), dMx, dMn);
		}
		else if (strType == _T("Q-V곡선"))
		{
			dQV[0] = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_QVCURVEV1"), _wtoi(strIdx));
			dQV[1] = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_QVCURVEV2"), _wtoi(strIdx));
			dQV[2] = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_QVCURVEV3"), _wtoi(strIdx));
			dQV[3] = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_QVCURVEV4"), _wtoi(strIdx));

			strInfo.Format(_T("QV curve V1:%.3lf V2:%.3lf V3:%.3lf V4:%.3lf"), dQV[0], dQV[2], dQV[2], dQV[3]);
		}
		else if (strType == _T("일정전압"))
		{
			dValue = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMVREF"), _wtoi(strIdx));

			strInfo.Format(_T("일정전압:%.2lf"), dValue);
		}
		else if (strType == _T("일정무효전력"))
		{
			dValue = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMQVRATIO"), _wtoi(strIdx));

			strInfo.Format(_T("QV ratio:%.2lf"), dValue);
		}
		else
		{
			dValue = GETVALUE(double, _T("gen_dyn_pdvro"), _T("GEN_DERAVMPFREF"), _wtoi(strIdx));

			strInfo.Format(_T("일정역률:%.2lf"), dValue);
		}

		m_ctrList[2].InsertItem(m_ctrList[2].GetItemCount(), strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 1, strInfo, RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
		m_ctrList[2].SetItemText(m_ctrList[2].GetItemCount() - 1, 2, strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	}
}


void CView_PDVR_rst::Update_DGTRData()
{
	m_ctrList[7].DeleteAllItems();

	CString strData[4];
	double dSS_MW, dMTR_MW, dDL_MW, dChange;

	dSS_MW		= GETVALUE(double, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_SSCKW"), 1);
	dMTR_MW		= GETVALUE(double, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_MTCKW"), 1);
	dDL_MW		= GETVALUE(double, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_DLCKW"), 1);
	dChange		= GETVALUE(double, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_VOLTCHANGE"), 1);

	strData[0].Format(_T("%.3lf MW"), dSS_MW/1000);
	strData[1].Format(_T("%.3lf MW"), dMTR_MW / 1000);
	strData[2].Format(_T("%.3lf MW"), dDL_MW / 1000);
	strData[3].Format(_T("%.2lf %%"), dChange);

	m_ctrList[7].InsertItem(0, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[7].SetItemText(0, 1, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[7].SetItemText(0, 2, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[7].SetItemText(0, 3, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

}

void CView_PDVR_rst::Update_PCEData()
{
	m_ctrList[3].DeleteAllItems();
	m_ctrList[4].DeleteAllItems();
	m_ctrList[5].DeleteAllItems();

	CString strType,strName,strCBSW_Idx;
	CString strData[3]  ;
	double dValue[3],dSetValue[3];
	int nResult[3] ;
	int nType;

	int nCount = theAppDataMng->GetTableRealCount(_T("DGTROUT_DYN_DGTRO"));
	for (int i = 1; i <= nCount; i++)
	{
		nType = GETVALUE(int, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_CBSWTYPE"), i);
		if(nType  == 0)
			break;

		if (nType == 1)
			strType = _T("CB");
		else if (nType == 2)
			strType = _T("RC");
		else
			strType = _T("확인필요");

		
		strCBSW_Idx = CA2W(GETSTRING("DGTROUT_DYN_DGTRO", "DGTROUT_CBSWNM", i)).m_psz;

		strName = CA2W(GETSTRING("CBSW_STA", "CBSW_NM", _wtoi(strCBSW_Idx))).m_psz;


		dValue[0] = GETVALUE(double, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_SLG0"), i);
		dValue[1] = GETVALUE(double, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_SLG30"), i);
		dValue[2] = GETVALUE(double, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_MXFC"), i);

		dSetValue[0] = GETVALUE(double, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_OCGRPC"), i);
		dSetValue[1] = GETVALUE(double, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_OCGRPC"), i);
		dSetValue[2] = GETVALUE(double, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_RBC"), i);

		nResult[0] = GETVALUE(int, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_RESORCH"), i);
		nResult[1] = GETVALUE(int, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_RESURCH"), i);
		nResult[2] = GETVALUE(int, _T("DGTROUT_DYN_DGTRO"), _T("DGTROUT_RESRBC"), i);

		//////////////////////////////////////////////////////////////////////
		strData[0].Format(_T("%.1lf"), dSetValue[0]);
		strData[1].Format(_T("%.1lf"), dValue[0]);

		if (nResult[0] == 1)
			strData[2] = _T("부적합");
		else if (nResult[0] == 2)
			strData[2] = _T("적합");
		else if (nResult[0] == 3)
			strData[2] = _T("적합(양방향)");
		else
			strData[2] = _T("확인필요");

		m_ctrList[3].InsertItem(m_ctrList[3].GetItemCount(), strType, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() -1, 1, strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 2, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 3, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 4, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[3].SetItemText(m_ctrList[3].GetItemCount() - 1, 5, strCBSW_Idx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		//////////////////////////////////////////////////////////////////////
		
		strData[0].Format(_T("%.1lf"), dSetValue[1]);
		strData[1].Format(_T("%.1lf"), dValue[1]);

		if (nResult[1] == 1)
			strData[2] = _T("부적합");
		else if (nResult[1] == 2)
			strData[2] = _T("적합");
		else
			strData[2] = _T("확인필요");

		m_ctrList[4].InsertItem(m_ctrList[4].GetItemCount(), strType, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 1, strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 2, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 3, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 4, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[4].SetItemText(m_ctrList[4].GetItemCount() - 1, 5, strCBSW_Idx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		//////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////

		strData[0].Format(_T("%.1lf"), dSetValue[2]/1000);
		strData[1].Format(_T("%.1lf"), dValue[2]/1000);

		if (nResult[2] == 1)
			strData[2] = _T("부적합");
		else if (nResult[2] == 2)
			strData[2] = _T("적합");
		else
			strData[2] = _T("확인필요");

		m_ctrList[5].InsertItem(m_ctrList[5].GetItemCount(), strType, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[5].SetItemText(m_ctrList[5].GetItemCount() - 1, 1, strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[5].SetItemText(m_ctrList[5].GetItemCount() - 1, 2, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[5].SetItemText(m_ctrList[5].GetItemCount() - 1, 3, strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[5].SetItemText(m_ctrList[5].GetItemCount() - 1, 4, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[5].SetItemText(m_ctrList[5].GetItemCount() - 1, 5, strCBSW_Idx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);

	}
}

void CView_PDVR_rst::OnTimer(UINT_PTR nIDEvent)
{
	
	if (!m_bTimer)
	{
		KillTimer(nIDEvent);
		if (nIDEvent == 1)
		{
			Sleep(500);
			int nSel = m_ctrCombo[2].GetCurSel();
			m_ctrCombo[3].SetCurSel(nSel);
			
			if (m_nCompAppl_ID == 8)
			{
				m_nMode = 1;
				//Update_DGTRData();
				//test_protected_list(1);


				OnPDVR_rstCombo4SelectChange();
			}
			else if (m_nCompAppl_ID == 9)
			{
				m_nMode = 2;
				OnPDVR_rstCombo4SelectChange();
				Update_DGTRData();
				Update_PCEData();
			}

			int nZoneMode = GETVALUE(int, _T("PDVROPT_DYN_UIN"), _T("PDVROPT_ZONEMODE"), 1);

			if (nZoneMode == 1)
			{
				int nSel = m_ctrCombo[2].GetCurSel();
				m_ctrCombo[3].SetCurSel(nSel);
				m_ctrCombo[3].EnableWindow(TRUE);
				m_ctrBtn_Check[3].EnableWindow(TRUE);
				m_ctrBtn_Check[4].EnableWindow(TRUE);
				m_ctrBtn_Check[5].EnableWindow(TRUE);
				m_ctrBtn_Check[6].EnableWindow(TRUE);


			}
			else
			{

				int nSel = m_ctrCombo[2].GetCurSel();
				m_ctrCombo[3].SetCurSel(nSel);
				m_ctrCombo[3].EnableWindow(FALSE);
				m_ctrBtn_Check[3].EnableWindow(FALSE);
				m_ctrBtn_Check[4].EnableWindow(FALSE);
				m_ctrBtn_Check[5].EnableWindow(FALSE);
				m_ctrBtn_Check[6].EnableWindow(FALSE);
			}
		}
		/*else if (nIDEvent == 2)
		{
			m_nMode = 1;

			test_pdvr_graph(1);

		}
		else if (nIDEvent == 3)
		{
			test_protected_list(1);
		}*/

		//Redraw_Ctrl();
		RedrawWindow();
	}

	CView_Base::OnTimer(nIDEvent);
}




BOOL CView_PDVR_rst::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->hwnd == m_ctrEdit[0].GetSafeHwnd())
	{
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{

			OnPDVR_rst_Edit_1_Change();
		}
	}


	return CView_Base::PreTranslateMessage(pMsg);
}


void CView_PDVR_rst::Delete_GraphData()
{
	for (int i = 0; i < m_Array_Graph.GetSize(); i++)
		delete m_Array_Graph.GetAt(i);

	m_Array_Graph.RemoveAll();
}



void CView_PDVR_rst::OnControlbutton_click_Check1()
{
	RedrawWindow(m_rectPDVR[1]);
}

void CView_PDVR_rst::OnControlbutton_click_Check2()
{
	RedrawWindow(m_rectPDVR[1]);
}

void CView_PDVR_rst::OnControlbutton_click_Check3()
{
	RedrawWindow(m_rectPDVR[1]);
}

void CView_PDVR_rst::OnControlbutton_click_Check4()
{
	RedrawWindow(m_rectPDVR[1]);
}

void CView_PDVR_rst::OnControlbutton_click_Check5()
{
	RedrawWindow(m_rectPDVR[1]);
}

void CView_PDVR_rst::OnControlbutton_click_Check6()
{
	RedrawWindow(m_rectPDVR[1]);
}

void CView_PDVR_rst::OnControlbutton_click_Check7()
{
	RedrawWindow(m_rectPDVR[1]);
}


void CView_PDVR_rst::Report_PCE(CXLSAutomation* pXL)
{
	//////////////////// col = A,BC,D,E,F
	//////////////////// w : A,B = 20
	//////////////////// h = 

	CString font = _T("맑은 고딕");
	int		nRow = 2;

	pXL->SetSheetName(1, _T("기술검토 보고서"));
	pXL->SetActiveSheet(1);

	pXL->SetColWidth(1, 20);
	pXL->SetColWidth(2, 20);
	pXL->SetColWidth(3, 20);
	pXL->SetColWidth(4, 20);
	pXL->SetColWidth(5, 20);
	pXL->SetColWidth(6, 20);

	CString strCol[5], strCol_Name[5];
	int nRow_S, nRow_E;
	CString strValue;

	//////////////////////// 단락용량 상회여부 검토
	nRow_S = nRow;
	pXL->SetRange(_T("A"), nRow, _T("F"), nRow);
	pXL->SetMergeCell(TRUE);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetFont(font, 14, TRUE);
	pXL->SetValue(_T("A"), nRow, _T("단락용량 상회여부 검토"));
	nRow++;



	strCol_Name[0] = _T("A");
	strCol_Name[1] = _T("B");
	strCol_Name[2] = _T("D");
	strCol_Name[3] = _T("E");
	strCol_Name[4] = _T("F");
	strCol[0] = _T("구분");
	strCol[1] = _T("전주번호");
	strCol[2] = _T("단락용량(kA)");
	strCol[3] = _T("고장전류(KA)");
	strCol[4] = _T("검토결과");

	for (int i = 0; i < 5; i++)
	{
		if (i == 1)
		{
			pXL->SetRange(strCol_Name[i], nRow, _T("C"), nRow);
			pXL->SetMergeCell(TRUE);
		}
		else
		{
			pXL->SetRange(strCol_Name[i], nRow, strCol_Name[i], nRow);
		}
		
		pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
		pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
		pXL->SetFont(font, 13, FALSE);
		pXL->SetValue(strCol_Name[i], nRow, strCol[i]);
	}
	pXL->SetRange(strCol_Name[0], nRow, strCol_Name[4], nRow);
	pXL->SetTextColor(RGB(255, 255, 255));
	pXL->SetBkColor(RGB(68, 114, 196));
	nRow++;

	
	for (int i = 0; i < m_ctrList[5].GetItemCount(); i++)
	{
		for (int k = 0; k < 5; k++)
		{
			strValue = m_ctrList[5].GetItemText(i, k);


			if (k == 1)
			{
				pXL->SetRange(strCol_Name[k], nRow, _T("C"), nRow);
				pXL->SetMergeCell(TRUE);
			}
			else
			{
				pXL->SetRange(strCol_Name[k], nRow, strCol_Name[k], nRow);
			}
			pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
			pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
			pXL->SetFont(font, 12, FALSE);
			pXL->SetValue(strCol_Name[k], nRow, strValue);
		}
		nRow++;
	}
	nRow_E = nRow - 1;

	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineInsideHorizontal);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineInsideVertical);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineTop);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineBottom);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineLeft);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineRight);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);

	nRow++;
	
	//////////////////////// 보호기기 부동작 검토
	nRow_S = nRow;
	pXL->SetRange(_T("A"), nRow, _T("F"), nRow);
	pXL->SetMergeCell(TRUE);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetFont(font, 14, TRUE);
	pXL->SetValue(_T("A"), nRow, _T("보호기기 부동작 검토"));
	nRow++;

	strCol_Name[0] = _T("A");
	strCol_Name[1] = _T("B");
	strCol_Name[2] = _T("D");
	strCol_Name[3] = _T("E");
	strCol_Name[4] = _T("F");
	strCol[0] = _T("구분");
	strCol[1] = _T("전주번호");
	strCol[2] = _T("설정값(A)");
	strCol[3] = _T("고장전류(A)");
	strCol[4] = _T("검토결과");

	for (int i = 0; i < 5; i++)
	{
		if (i == 1)
		{
			pXL->SetRange(strCol_Name[i], nRow, _T("C"), nRow);
			pXL->SetMergeCell(TRUE);
		}
		else
		{
			pXL->SetRange(strCol_Name[i], nRow, strCol_Name[i], nRow);
		}

		pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
		pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
		pXL->SetFont(font, 13, FALSE);
		pXL->SetValue(strCol_Name[i], nRow, strCol[i]);
	}
	pXL->SetRange(strCol_Name[0], nRow, strCol_Name[4], nRow);
	pXL->SetTextColor(RGB(255, 255, 255));
	pXL->SetBkColor(RGB(68, 114, 196));
	nRow++;


	for (int i = 0; i < m_ctrList[4].GetItemCount(); i++)
	{
		for (int k = 0; k < 5; k++)
		{
			strValue = m_ctrList[4].GetItemText(i, k);


			if (k == 1)
			{
				pXL->SetRange(strCol_Name[k], nRow, _T("C"), nRow);
				pXL->SetMergeCell(TRUE);
			}
			else
			{
				pXL->SetRange(strCol_Name[k], nRow, strCol_Name[k], nRow);
			}
			pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
			pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
			pXL->SetFont(font, 12, FALSE);
			pXL->SetValue(strCol_Name[k], nRow, strValue);
		}
		nRow++;
	}
	nRow_E = nRow - 1;

	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineInsideHorizontal);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineInsideVertical);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineTop);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineBottom);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineLeft);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineRight);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);

	nRow++;

	//////////////////////// 보호기기 부동작 검토
	nRow_S = nRow;
	pXL->SetRange(_T("A"), nRow, _T("F"), nRow);
	pXL->SetMergeCell(TRUE);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetFont(font, 14, TRUE);
	pXL->SetValue(_T("A"), nRow, _T("보호기기 오동작 검토"));
	nRow++;

	strCol_Name[0] = _T("A");
	strCol_Name[1] = _T("B");
	strCol_Name[2] = _T("D");
	strCol_Name[3] = _T("E");
	strCol_Name[4] = _T("F");
	strCol[0] = _T("구분");
	strCol[1] = _T("전주번호");
	strCol[2] = _T("설정값(A)");
	strCol[3] = _T("고장전류(A)");
	strCol[4] = _T("검토결과");

	for (int i = 0; i < 5; i++)
	{
		if (i == 1)
		{
			pXL->SetRange(strCol_Name[i], nRow, _T("C"), nRow);
			pXL->SetMergeCell(TRUE);
		}
		else
		{
			pXL->SetRange(strCol_Name[i], nRow, strCol_Name[i], nRow);
		}

		pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
		pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
		pXL->SetFont(font, 13, FALSE);
		pXL->SetValue(strCol_Name[i], nRow, strCol[i]);
	}
	pXL->SetRange(strCol_Name[0], nRow, strCol_Name[4], nRow);
	pXL->SetTextColor(RGB(255, 255, 255));
	pXL->SetBkColor(RGB(68, 114, 196));
	nRow++;


	for (int i = 0; i < m_ctrList[3].GetItemCount(); i++)
	{
		for (int k = 0; k < 5; k++)
		{
			strValue = m_ctrList[3].GetItemText(i, k);


			if (k == 1)
			{
				pXL->SetRange(strCol_Name[k], nRow, _T("C"), nRow);
				pXL->SetMergeCell(TRUE);
			}
			else
			{
				pXL->SetRange(strCol_Name[k], nRow, strCol_Name[k], nRow);
			}
			pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
			pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
			pXL->SetFont(font, 12, FALSE);
			pXL->SetValue(strCol_Name[k], nRow, strValue);
		}
		nRow++;
	}
	nRow_E = nRow - 1;

	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineInsideHorizontal);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineInsideVertical);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineTop);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineBottom);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineLeft);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineRight);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);

	nRow++;

	Report_PDVR(pXL,nRow);
}

void CView_PDVR_rst::Report_PDVR(CXLSAutomation* pXL,int nStartLine)
{
	CString font = _T("맑은 고딕");
	int		nRow = nStartLine;

	pXL->SetSheetName(1, _T("기술검토 보고서"));
	pXL->SetActiveSheet(1);

	pXL->SetColWidth(1, 20);
	pXL->SetColWidth(2, 20);
	pXL->SetColWidth(3, 20);
	pXL->SetColWidth(4, 20);
	pXL->SetColWidth(5, 20);
	pXL->SetColWidth(6, 20);

	CString strCol[5], strCol_Name[5];
	int nRow_S, nRow_E;
	CString strValue;

	//////////////////////// 적정 전압 이탈 가능성 검토				
	nRow_S = nRow;
	pXL->SetRange(_T("A"), nRow, _T("F"), nRow);
	pXL->SetMergeCell(TRUE);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetFont(font, 14, TRUE);
	pXL->SetValue(_T("A"), nRow, _T("적정 전압 이탈 가능성 검토"));
	nRow++;

	strCol_Name[0] = _T("A");
	strCol_Name[1] = _T("C");
	
	int nValue = GETVALUE(int, _T("PDVROUT_DYN_PDVRO"), _T("PDVROUT_SOLTYPE"), 1);

	if (nValue == 2)
	{
		strValue = _T("저전압 주의");
	}
	else
	{
		strValue = _T("이탈 없음");
	}
	pXL->SetRange(strCol_Name[0], nRow, _T("B"), nRow);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetFont(font, 13, TRUE);
	pXL->SetTextColor(RGB(255, 255, 255));
	pXL->SetBkColor(RGB(68, 114, 196));
	pXL->SetMergeCell(TRUE);
	pXL->SetValue(_T("A"), nRow, _T("적정전압 이탈여부"));

	pXL->SetRange(_T("C"), nRow, _T("C"), nRow);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetFont(font, 13, TRUE);
	pXL->SetValue(_T("C"), nRow, strValue);

	pXL->SetRange(_T("D"), nRow, _T("F"), nRow);
	pXL->SetMergeCell(TRUE);

	/////////////그래프 추가
	Report_PDVR_Create_PNG();

	CDataManager* pDataMng = CDataManager::Instance();
	CString strFileName;
	strFileName.Format(_T("%s\\temp\\pdvr.png"), pDataMng->MyPath());

	pXL->AddImage(1, strFileName, 1, nRow+1, 700, 350);
	nRow += 22;
	pXL->SetRange(_T("A"), nRow_S+2, _T("F"), nRow);
	pXL->SetMergeCell(TRUE);

	nRow++;

	//////////////////////// 설정 변경 설비				
	pXL->SetRange(strCol_Name[0], nRow, _T("B"), nRow);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetMergeCell(TRUE);
	pXL->SetValue(_T("A"), nRow, _T("설정 변경 설비"));

	pXL->SetRange(_T("C"), nRow, _T("F"), nRow);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetMergeCell(TRUE);
	pXL->SetValue(_T("C"), nRow, _T("운전 설정"));

	pXL->SetRange(_T("A"), nRow, _T("F"), nRow);
	pXL->SetFont(font, 13, TRUE);
	pXL->SetTextColor(RGB(255, 255, 255));
	pXL->SetBkColor(RGB(68, 114, 196));
	nRow++;

	for (int i = 0; i < m_ctrList[2].GetItemCount(); i++)
	{
		for (int k = 0; k < 2; k++)
		{
			strValue = m_ctrList[2].GetItemText(i, k);


			if (k == 1)
			{
				pXL->SetRange(_T("C"), nRow, _T("F"), nRow);
				pXL->SetMergeCell(TRUE);
				pXL->SetTextHAlign(CXLSAutomation::xlAlignHLeft);
				pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
			}
			else
			{
				pXL->SetRange(_T("A"), nRow, _T("B"), nRow);
				
				pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
				pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
				pXL->SetMergeCell(TRUE);
			}
		//	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
			pXL->SetFont(font, 12, FALSE);
			pXL->SetValue(strCol_Name[k], nRow, strValue);
		}
		nRow++;
	}
	nRow_E = nRow - 1;

	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineInsideHorizontal);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineInsideVertical);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineTop);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineBottom);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineLeft);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineRight);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);

	nRow++;

	//////////////////////// 순시전압변동 계산 결과				
	nRow_S = nRow;
	pXL->SetRange(_T("A"), nRow, _T("F"), nRow);
	pXL->SetMergeCell(TRUE);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetFont(font, 14, TRUE);
	pXL->SetValue(_T("A"), nRow, _T("순시전압변동 계산 결과"));
	nRow++;

	pXL->SetRange(strCol_Name[0], nRow, _T("B"), nRow);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetFont(font, 13, TRUE);
	pXL->SetTextColor(RGB(255, 255, 255));
	pXL->SetBkColor(RGB(68, 114, 196));
	pXL->SetMergeCell(TRUE);
	pXL->SetValue(_T("A"), nRow, _T("출력변동에 따른 순시전압변동"));

	if (m_ctrList[7].GetItemCount() > 0)
	{
		strValue = m_ctrList[7].GetItemText(0, 3);
	}
	else
	{
		strValue = _T("결과 없음");
	}

	pXL->SetRange(_T("C"), nRow, _T("C"), nRow);
	pXL->SetTextHAlign(CXLSAutomation::xlAlignHCenter);
	pXL->SetTextVAlign(CXLSAutomation::xlAlignVCenter);
	pXL->SetFont(font, 13, TRUE);
	pXL->SetValue(_T("C"), nRow, strValue);

	pXL->SetRange(_T("D"), nRow, _T("F"), nRow);
	pXL->SetMergeCell(TRUE);
	nRow++;

	nRow_E = nRow - 1;

	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineInsideHorizontal);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineInsideVertical);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineTop);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineBottom);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineLeft);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
	pXL->SetRange(strCol_Name[0], nRow_S, _T("F"), nRow_E);
	pXL->SetLineEdge(CXLSAutomation::xlLineRight);
	pXL->SetLineStyle(CXLSAutomation::xlLineStyle_Continuous);
}

void CView_PDVR_rst::Report_PDVR_Create_PNG()
{
	CRect rDraw(0, 0, m_rectPDVR[1].Width() + 200, m_rectPDVR[1].Height());

	CClientDC dc(this); // device context for painting
	CDC											dcMem;
	CBitmap										bmp, *pOldBmp;
	
	dcMem.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rDraw.Width() + 200, rDraw.Height());
	pOldBmp = dcMem.SelectObject(&bmp);

	CBrush brh, *pOldbrh;
	brh.CreateSolidBrush(RGB(255,255, 255));
	pOldbrh = dcMem.SelectObject(&brh);
	dcMem.Rectangle(rDraw);
	dcMem.SelectObject(&pOldbrh);

	Graphics						graphics(dcMem.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CRect rGraph = rDraw;
	rGraph.right -= 200;

	Draw_Graph(&dcMem, graphics, rGraph);

	/////////////////// 범례
	Gdiplus::RectF r[4];

	r[0].X = rDraw.right - 180;
	r[0].Y = rDraw.top + 30;
	r[0].Width = 150;
	r[0].Height = 18;

	r[1] = r[2] = r[3] = r[0];
	r[1].Y = r[0].GetBottom() + 18;
	r[2].Y = r[1].GetBottom() + 18;
	r[3].Y = r[2].GetBottom() + 18;

	/*SolidBrush						_drawDatabrush_cur_mx(Color(255, 255, 0, 0));
	Gdiplus::Pen					_drawDatapen_cur_mx(&_drawDatabrush_cur_mx, 2.);
	_drawDatapen_cur_mx.SetDashStyle(DashStyleDashDotDot);


	SolidBrush						_drawDatabrush_cur_mn(Color(255, 0, 0, 255));
	Gdiplus::Pen					_drawDatapen_cur_mn(&_drawDatabrush_cur_mn, 2.);
	_drawDatapen_cur_mn.SetDashStyle(DashStyleDashDotDot);

	SolidBrush						_drawDatabrush_cal_mx(Color(255, 255, 127, 39));
	Gdiplus::Pen					_drawDatapen_cal_mx(&_drawDatabrush_cal_mx, 2.);

	SolidBrush						_drawDatabrush_cal_mn(Color(255, 100, 142, 255));
	Gdiplus::Pen					_drawDatapen_cal_mn(&_drawDatabrush_cal_mn, 2.);*/

	SolidBrush						_drawXYbrush(Color(255, 255, 0, 0));
	Gdiplus::Pen		_drawXYpen(&_drawXYbrush, 3.);
	graphics.DrawLine(&_drawXYpen, r[0].X - 80, r[0].Y, r[0].X - 10, r[0].Y);

	_drawXYbrush.SetColor(Color(255, 255, 127, 39));
	_drawXYpen.SetBrush(&_drawXYbrush);
	graphics.DrawLine(&_drawXYpen, r[1].X - 80, r[1].Y, r[1].X - 10, r[1].Y);

	_drawXYbrush.SetColor(Color(255, 0, 0, 255));
	_drawXYpen.SetBrush(&_drawXYbrush);
	graphics.DrawLine(&_drawXYpen, r[2].X - 80, r[2].Y, r[2].X - 10, r[2].Y);

	_drawXYbrush.SetColor(Color( 255, 100, 142, 255));
	_drawXYpen.SetBrush(&_drawXYbrush);
	graphics.DrawLine(&_drawXYpen, r[3].X - 80, r[3].Y, r[3].X - 10, r[3].Y);

	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 11.0f, FontStyleBold/*FontStyleRegular*/, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 0, 0, 0));
	r[0].Y -= 9;
	r[1].Y -= 9;
	r[2].Y -= 9;
	r[3].Y -= 9;

	graphics.DrawString(_T("현재 설정 적용 시 최대전압"), -1, &_drawfont, r[0], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("신규 설정 적용 시 최대전압"), -1, &_drawfont, r[1], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("현재 설정 적용 시 최대전압"), -1, &_drawfont, r[2], &_drawStrFormat, &_drawFontbrush);
	graphics.DrawString(_T("신규 설정 적용 시 최대전압"), -1, &_drawfont, r[3], &_drawStrFormat, &_drawFontbrush);


	/////////////////////////////////////

	CImage				_image;
	CWnd*				pWndDesktop = GetDesktopWindow();
	CWindowDC			ScrDC(pWndDesktop);

	_image.Create(rDraw.Width(), rDraw.Height(), ScrDC.GetDeviceCaps(BITSPIXEL));
	CDC* _imgdc = CDC::FromHandle(_image.GetDC());

	_imgdc->BitBlt(0, 0, rDraw.Width(), rDraw.Height(), &dcMem, rDraw.left, rDraw.top, SRCCOPY);

	_image.ReleaseDC();

	CDataManager* pDataMng = CDataManager::Instance();
	CString strFileName;

	strFileName.Format(_T("%s\\temp\\pdvr.png"), pDataMng->MyPath());

	_image.Save(strFileName, Gdiplus::ImageFormatPNG);

	dcMem.SelectObject(pOldBmp);

	dcMem.DeleteDC();

	ReleaseDC(&dc);
}