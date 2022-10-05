#include "pch.h"
#include "CView_PCE_rst.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"
#include "../DataManager/CDataManager.h"
#include "resource.h"

CView_PCE_rst::CView_PCE_rst()
{
	m_pTabGroup = NULL;

	m_dAmp_Range[0] = 200;
	m_dAmp_Range[1] = 7000;
	m_dOCB_SDelay = 0.04;

	m_nSelect_Path = -1;

	m_dCurve_X_Gap = -999999.;
	m_dCurve_X_Tap = -999999.;
	m_nCurve_X_Base = -999999;
	m_dCurve_Y_MAX = -1;
	m_nCurve_Y_Base = -1;
}

CView_PCE_rst::~CView_PCE_rst()
{
	m_pTabGroup->RemoveAllTab();
	delete m_pTabGroup;
}

BEGIN_MESSAGE_MAP(CView_PCE_rst, CView_Base)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_CBN_SELCHANGE(ID_APP_PCE_COMBO_1, &CView_PCE_rst::OnPCE_rstCombo1SelectChange)
	ON_CBN_SELCHANGE(ID_APP_PCE_COMBO_2, &CView_PCE_rst::OnPCE_rstCombo2SelectChange)
	ON_CBN_SELCHANGE(ID_APP_PCE_COMBO_5, &CView_PCE_rst::OnPCE_rstCombo5SelectChange)
	ON_CBN_SELCHANGE(ID_APP_PCE_COMBO_6, &CView_PCE_rst::OnPCE_rstCombo6SelectChange)
	ON_NOTIFY(NM_DBLCLK, ID_APP_PCE_LIST_1, &CView_PCE_rst::OnPCE_ListCtrlDBClick_1)
	ON_BN_CLICKED(ID_APP_PCE_BTN_CHECK_1, &CView_PCE_rst::OnControlbutton_click_check1)
	ON_BN_CLICKED(ID_APP_PCE_BTN_CHECK_2, &CView_PCE_rst::OnControlbutton_click_check2)
	ON_BN_CLICKED(ID_APP_PCE_BTN_RADIO_1, &CView_PCE_rst::OnControlbutton_click_Radio1)
	ON_BN_CLICKED(ID_APP_PCE_BTN_RADIO_2, &CView_PCE_rst::OnControlbutton_click_Radio2)
	ON_BN_CLICKED(ID_APP_PCE_BTN_1, &CView_PCE_rst::OnControlbutton_click_Run)
	ON_BN_CLICKED(ID_APP_PCE_BTN_2, &CView_PCE_rst::OnControlbutton_click_Auto)
	ON_BN_CLICKED(ID_APP_PCE_BTN_3, &CView_PCE_rst::OnControlbutton_click_Rpt)
	ON_EN_CHANGE(ID_APP_PCE_EDIT_1, &CView_PCE_rst::OnEditCtrl_1_EN_Change)
	ON_EN_KILLFOCUS(ID_APP_PCE_EDIT_1, &CView_PCE_rst::OnEditCtrl_1_EN_Killfocus)
	ON_EN_KILLFOCUS(ID_APP_PCE_EDIT_2, &CView_PCE_rst::OnEditCtrl_2_EN_Killfocus)
	ON_EN_KILLFOCUS(ID_APP_PCE_EDIT_3, &CView_PCE_rst::OnEditCtrl_3_EN_Killfocus)
	ON_EN_KILLFOCUS(ID_APP_PCE_EDIT_4, &CView_PCE_rst::OnEditCtrl_4_EN_Killfocus)
	ON_CONTROL_RANGE(BN_CLICKED, ID_APP_PCE_BTN_CHECK_3, ID_APP_PCE_BTN_CHECK_20, &CView_PCE_rst::OnCtrl_Range_Btn_Check)
	ON_WM_TIMER()
	ON_MESSAGE(WM_MSG_PCE_TAB, &CView_PCE_rst::OnTabMsg)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



void CView_PCE_rst::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	Create_Combobox();
	Create_ListCtrl();
	Create_Btn_Check();
	Create_Btn();
	Create_Tab();
	Create_Edit();
}


void CView_PCE_rst::InitData()
{

	m_ctrCombo[0].ResetContent();
	m_ctrCombo[1].ResetContent();
	m_ctrCombo[2].ResetContent();
	m_ctrCombo[3].ResetContent();
	m_ctrCombo[4].ResetContent();
	m_ctrCombo[5].ResetContent();

	SetComboxData_Subs();

	
	SetDlgItemText(ID_APP_PCE_EDIT_1, _T("200"));
	SetDlgItemText(ID_APP_PCE_EDIT_2, _T("7000"));
	SetDlgItemText(ID_APP_PCE_EDIT_3, _T("50"));
	SetDlgItemText(ID_APP_PCE_EDIT_4, _T("5000"));

	CString strCOS[12] = { _T("선택 없음"),_T("6K"),_T("10K"),_T("20K"),_T("30K"),_T("40K"),_T("50K")
							,_T("65K") ,_T("80K") ,_T("100K") ,_T("140K") ,_T("200K") };

	for (int i = 0; i < 12; i++)
	{
		m_ctrCombo[4].AddString(strCOS[i]);
		m_ctrCombo[5].AddString(strCOS[i]);
	}

	m_ctrCombo[4].SetCurSel(0);
	m_ctrCombo[5].SetCurSel(0);
	
}

void CView_PCE_rst::SetComboxData_Subs()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CStringArray Array_SS;
	CIntArray	 Array_SS_Idx;

	pDataMng->GetSSName_array(&Array_SS,&Array_SS_Idx);

	int nIdx = 0;
	for (int i = 0; i < Array_SS.GetSize(); i++)
	{
		m_ctrCombo[0].AddString(Array_SS.GetAt(i));

		nIdx = Array_SS_Idx.GetAt(i);

		m_ctrCombo[0].SetItemData(i, (DWORD_PTR)nIdx);

	}

}


BOOL CView_PCE_rst::OnEraseBkgnd(CDC* pDC)
{
	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	CView_Base::OnEraseBkgnd(pDC);

	pViewMng->DrawArea_Base(pDC, graphics, m_rectBack[0]);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectBack[1], FALSE);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectBack[3]);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectBack[4]);

	pViewMng->Draw_Split(pDC, graphics, m_rectGraph[0], DRAW_SPLIT_MODE_BOTTOM);
	pViewMng->Draw_Split(pDC, graphics, m_rectGraph[1], DRAW_SPLIT_MODE_BOTTOM);
	pViewMng->Draw_Split(pDC, graphics, m_rectGraph[2], DRAW_SPLIT_MODE_BOTTOM);
	pViewMng->Draw_Split(pDC, graphics, m_rectGraph[3], DRAW_SPLIT_MODE_BOTTOM);

	//////////////////////////////////////////////////////////////////////
	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[1]);
	//	pViewMng->DrawArea_List(&dc, graphics, m_rectBack[2]);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectBack[5], FALSE);


	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[0], _T("DL 경로"));
	//	pViewMng->DrawArea_Title(&dc, graphics, m_rectTitle[1], _T("CB 정보"));
	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[2], _T("TC 커브"), FALSE, m_rectBack[4]);

	Draw_Graph_Tag_1(pDC, graphics);
	Draw_Graph_Tag_2(pDC, graphics);

	Draw_EditRound(pDC);


	return TRUE;
	return CView_Base::OnEraseBkgnd(pDC);
}

void CView_PCE_rst::Draw_EditRound(CDC* pDC)
{
	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	SolidBrush						_drawRectbrush(Color(255, 153, 153, 153));
	Gdiplus::Pen					_drawRectpen(&_drawRectbrush, 1.);
	Gdiplus::GraphicsPath gdiPath;
	CRect rect;

	for (int i = 0; i < 4; i++)
	{
		rect = m_rectCtrl_Edit[i];
		rect.InflateRect(1, 1);
		rect.top -= 2;
		pViewMng->GetRoundRectPath(&gdiPath, rect.left, rect.top, rect.Width(), rect.Height(), 5);
		graphics.DrawPath(&_drawRectpen, &gdiPath);
	}


}



void CView_PCE_rst::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);

	OnPrepareDC(&dc);
	Graphics						graphics(dc.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	
	Draw_Setting_Tag(&dc, graphics);
	Draw_Graph(&dc, graphics);


	m_ctrCombo[0].RedrawWindow();
	m_ctrCombo[1].RedrawWindow();
	m_ctrCombo[2].RedrawWindow();
	m_ctrCombo[3].RedrawWindow();
	m_ctrCombo[0].SetFocus();
	m_ctrCombo[1].SetFocus();
	m_ctrCombo[2].SetFocus();
	m_ctrCombo[3].SetFocus();

}

void CView_PCE_rst::Draw_Setting_Tag(CDC* pDC, Graphics &graphics)
{
	CRect rTag[7];

	rTag[0] = m_rectCtrl_Combobox[0];
	rTag[0].left = m_rectCtrl_Combobox[0].left - 80;
	rTag[0].right = rTag[0].left + 80;

	

	CView_Manager* pViewMng = CView_Manager::Instance();

	pViewMng->Draw_Setting_Tag(pDC, graphics, rTag[0], 0, _T("변전소/선로"));

}

void CView_PCE_rst::Draw_Graph_Tag_1(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectGraph[0];

	rect.InflateRect(-8, -10);

	Gdiplus::RectF  _r;

	_r.X = rect.left;
	_r.Y = rect.top;
	_r.Width = 54;
	_r.Height = rect.Height();


	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentNear);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));


	graphics.DrawString(_T("설정치"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);
	/////////////////////////////////////////////////////////////////////////
	rect = m_rectGraph[1];

	rect.InflateRect(-8, -10);

	_r.X = rect.left;
	_r.Y = rect.top;
	_r.Width = 54;
	_r.Height = rect.Height();

	graphics.DrawString(_T("권고치"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);


	/////////////////////////////////
	
	CPoint pt[18][2];
	

	for (int i = 0; i < 18; i++)
	{
		rect =  m_rectCtrl_Check[i+2];
		rect.left = rect.right;
		rect.right = rect.left + 60;

	//	rect.InflateRect(-8, 0);

		pt[i][0].x = rect.left+4;
		pt[i][0].y = rect.CenterPoint().y;
		pt[i][1].x = rect.right-16;
		pt[i][1].y = rect.CenterPoint().y;

	}


	int nTabCount = m_pTabGroup->GetTabCount();
	SolidBrush						LineBrush(Color(255, 237, 20, 20));
	Gdiplus::Pen					_drawLinepen(&LineBrush, 2.);
	UINT nDashStyle[4] = { DashStyleSolid, DashStyleDot ,DashStyleDash ,DashStyleDashDotDot };
	
	if (nTabCount > 0)
	{
		graphics.DrawLine(&_drawLinepen, pt[0][0].x, pt[0][0].y, pt[0][1].x, pt[0][1].y);
		_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[2]);
		_drawLinepen.SetDashOffset(10);
		graphics.DrawLine(&_drawLinepen, pt[9][0].x, pt[9][0].y, pt[9][1].x, pt[9][1].y);

	}
		
	if (nTabCount > 1)
	{
		LineBrush.SetColor(Color(255, 64, 51, 226));
		_drawLinepen.SetBrush(&LineBrush);
		_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[0]);
		graphics.DrawLine(&_drawLinepen, pt[1][0].x, pt[1][0].y, pt[1][1].x, pt[1][1].y);
		
		_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[2]);
		graphics.DrawLine(&_drawLinepen, pt[10][0].x, pt[10][0].y, pt[10][1].x, pt[10][1].y);

		if (m_pTabGroup->GetTabType(1) == 2)
		{
			_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[1]);
			graphics.DrawLine(&_drawLinepen, pt[2][0].x, pt[2][0].y, pt[2][1].x, pt[2][1].y);

			_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[3]);
			graphics.DrawLine(&_drawLinepen, pt[11][0].x, pt[11][0].y, pt[11][1].x, pt[11][1].y);
		}

		
	}
	
	if (nTabCount > 2)
	{
		LineBrush.SetColor(Color(255, 228, 140, 15));
		_drawLinepen.SetBrush(&LineBrush);
		_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[0]);
		graphics.DrawLine(&_drawLinepen, pt[3][0].x, pt[3][0].y, pt[3][1].x, pt[3][1].y);
		
		_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[2]);
		graphics.DrawLine(&_drawLinepen, pt[12][0].x, pt[12][0].y, pt[12][1].x, pt[12][1].y);
		

		if (m_pTabGroup->GetTabType(2) == 2)
		{
			_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[1]);
			graphics.DrawLine(&_drawLinepen, pt[4][0].x, pt[4][0].y, pt[4][1].x, pt[4][1].y);

			_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[3]);
			graphics.DrawLine(&_drawLinepen, pt[13][0].x, pt[13][0].y, pt[13][1].x, pt[13][1].y);
		}
	}
	
	if (nTabCount > 3)
	{
		LineBrush.SetColor(Color(255, 63, 119, 25));
		_drawLinepen.SetBrush(&LineBrush);
		_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[0]);
		graphics.DrawLine(&_drawLinepen, pt[5][0].x, pt[5][0].y, pt[5][1].x, pt[5][1].y);
		
		_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[2]);
		graphics.DrawLine(&_drawLinepen, pt[14][0].x, pt[14][0].y, pt[14][1].x, pt[14][1].y);
		

		if (m_pTabGroup->GetTabType(3) == 2)
		{
			_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[1]);
			graphics.DrawLine(&_drawLinepen, pt[6][0].x, pt[6][0].y, pt[6][1].x, pt[6][1].y);

			_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[3]);
			graphics.DrawLine(&_drawLinepen, pt[15][0].x, pt[15][0].y, pt[15][1].x, pt[15][1].y);
		}
	}

	if (nTabCount > 4)
	{
		LineBrush.SetColor(Color(255, 15, 215, 228));
		_drawLinepen.SetBrush(&LineBrush);
		_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[0]);
		graphics.DrawLine(&_drawLinepen, pt[7][0].x, pt[7][0].y, pt[7][1].x, pt[7][1].y);
		
		_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[2]);
		graphics.DrawLine(&_drawLinepen, pt[16][0].x, pt[16][0].y, pt[16][1].x, pt[16][1].y);
		

		if (m_pTabGroup->GetTabType(4) == 2)
		{
			_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[1]);
			graphics.DrawLine(&_drawLinepen, pt[8][0].x, pt[8][0].y, pt[8][1].x, pt[8][1].y);

			_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[3]);
			graphics.DrawLine(&_drawLinepen, pt[17][0].x, pt[17][0].y, pt[17][1].x, pt[17][1].y);
		}
	}

	//////////////////////////////////




}

void CView_PCE_rst::Draw_Graph_Tag_2(CDC* pDC, Graphics &graphics)
{
	CRect rect = m_rectCtrl_Combobox[4];

	Gdiplus::RectF  _r;

	_r.X = rect.left - 80;
	_r.Y = rect.top;
	_r.Width = 80;
	_r.Height = rect.Height();


	Gdiplus::Font					_drawfont(_T("맑은 고딕"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentNear);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 54, 55, 59));


	graphics.DrawString(_T("COS Curve 1"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);

	rect = m_rectCtrl_Combobox[5];

	_r.X = rect.left - 80;
	_r.Y = rect.top;
	_r.Width = 80;
	_r.Height = rect.Height();

	graphics.DrawString(_T("COS Curve 2"), -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);
	
}

void CView_PCE_rst::Draw_Graph(CDC* pDC, Graphics &graphics)
{
	CRect r[2];
	r[0] = r[1] = m_rectGraph[4];
	r[0].left		+= 15;
	r[0].top		+= 25;
	r[0].right		= r[0].left + 15;
	r[0].bottom		= r[0].top + 100;

	r[1].right		-= 20;
	r[1].bottom		-= 25;
	r[1].left		= r[1].right - 100;
	r[1].top		= r[1].bottom - 15;


	CString strTitle;
	pDC->SetTextColor(RGB(0, 0, 0));
	CFont font, font2, *pOldfont;
	font.CreateFont(12, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, L"굴림체");
	pOldfont = pDC->SelectObject(&font);
	pDC->SetTextAlign(TA_CENTER);
//	if (bShowPu)
//		strTitle = _T("Multiples of Pick-Up");
//	else
		strTitle = _T("Current(A)");
	pDC->TextOut(r[1].left, r[1].top, strTitle);
	pDC->SelectObject(pOldfont);

	font2.CreateFont(12, 0, 900, 0, FW_THIN, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, L"굴림체");
	pOldfont = pDC->SelectObject(&font2);
	pDC->TextOut(r[0].left, r[0].bottom, _T("Time in Cycles (60-HERTZ BASIS)"));

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetTextAlign(TA_LEFT);
	pDC->SelectObject(pOldfont);

	////////////////////////////////////
	Gdiplus::RectF  _rect;
	_rect.X = m_rectGraph[4].left + 90;
	_rect.Y = m_rectGraph[4].top + 25;
	_rect.Width = m_rectGraph[4].Width() - (90 + 20);
	_rect.Height = m_rectGraph[4].Height() - (25 + 95) ;

	SolidBrush						_drawXYbrush(Color(255, 0, 0, 0));
	Gdiplus::Pen					_drawXYpen(&_drawXYbrush, 1.);
	graphics.DrawLine(&_drawXYpen, _rect.GetLeft(), _rect.GetTop(), _rect.GetLeft(), _rect.GetBottom());
	graphics.DrawLine(&_drawXYpen, _rect.GetLeft(), _rect.GetBottom(), _rect.GetRight(), _rect.GetBottom());

	SolidBrush						_drawbrush_Dash(Color(255, 190, 190, 190));
	Gdiplus::Pen					_drawpen_Dash(&_drawbrush_Dash, 1.);
	//_drawpen_Dash.SetDashStyle(dashs)

	/////////////////////////////////

	CRect rect(_rect.GetLeft(), _rect.GetTop(), _rect.GetRight(), _rect.GetBottom());
	double dRange = log10(10000 / 4);
	double dLog, dTabx, dTaby;
	
	dTaby = rect.Height() / dRange;

	CPen pen, *pOldpen;
	pen.CreatePen(PS_DOT, 1, RGB(255, 255, 255));
	pOldpen = pDC->SelectObject(&pen);

//	CFont font, *pOldfont;
	font.DeleteObject();
	font.CreateFont(12, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, L"굴림체");
	pOldfont = pDC->SelectObject(&font);

	int i, x, y, ntab = 1;
	CString strTmp;
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	//커브정보추가
	int nCount = 0;
	double di,dTab = 2;
	double dGap = log10((double)4);
	for ( di = 4; di <= 10000; di += dTab)
	{
		
		if (di != 4)
		{
			dLog = log10((double)di);
			y = int(rect.bottom - (dLog - dGap) * dTaby);
			if (y > rect.bottom) continue;
		}
		else
		{
		//	x = rect.left;
			y = rect.bottom;
			continue;
		}
		// text output
		if (di >= 4000) dTab = 2000.;
		else if (di >= 1000) dTab = 1000.;
		else if (di >= 400) dTab = 200.;
		else if (di >= 100) dTab = 100.;
		else if (di >= 40) dTab = 20;
		else if (di >= 10) dTab = 10;
		if(di < 10) continue;
	//	if (di > 100 && di / dTab > 5)continue;
		strTmp.Format(_T("%g"), di/100);
		//pDC->SetTextAlign(TA_CENTER);
		//pDC->TextOut(x, rect.bottom + 5, strTmp);//x

		//if (i < 10 && i % 2 == 1 && i != 1)	continue;
		pDC->SetTextAlign(TA_RIGHT);
		pDC->TextOut(rect.left - 2, y - 6, strTmp);//y

	}

	dTab = 1;
	for (di = 4; di <= 10000; di += dTab)
	{
		if (di != 4)
		{
			dLog = log10((double)di);
			y = int(rect.bottom - (dLog - dGap) * dTaby);
			if (y > rect.bottom) continue;
		}
		else
		{
		
			y = rect.bottom;
			continue;
		}
		if (di >= 1000) dTab = 1000.;
		else if (di >= 100) dTab = 100.;
		else if (di >= 10) dTab = 10;

		graphics.DrawLine(&_drawpen_Dash, rect.left, y, rect.right, y);

	}

	/////////////////////////////// X 축
	dRange = log10(m_dAmp_Range[1] / m_dAmp_Range[0]);
	dTabx = rect.Width() / dRange;
	ntab = 1;
	int nInit = Get_X_FirstValue();
	dGap = log10((double)nInit);
	for (i = nInit; i <= m_dAmp_Range[1]; i += ntab)
	{
		if (i != int(m_dAmp_Range[0]))
		{
			dLog = log10((double)i);
			x = int(rect.left + abs(dLog - dGap) * dTabx);
			if (x < rect.left) continue;
		}
		else
		{
			x = rect.left;
			y = rect.bottom;
		}
		// text output
		if (i >= 1000)
		{
			ntab = 1000;
		}
		else if (i >= 100)
		{
			ntab = 100;
		}
		else if (i >= 10)
		{
			ntab = 10;
		}
		if (i <= m_dAmp_Range[0] ) continue;
		//if (ntab >= 10 && i / ntab > 5) continue;
		//if (i == 4000 || i == 400)	continue;*/
		strTmp.Format(_T("%d"), i);
		pDC->SetTextAlign(TA_CENTER);
		pDC->TextOut(x, rect.bottom + 5, strTmp);//x

		
	}
	ntab = 1;
	for (i = nInit; i <= m_dAmp_Range[1]; i += ntab)
	{
		if (i != int(m_dAmp_Range[0]))
		{
			dLog = log10((double)i);
			x = int(rect.left + abs(dLog - dGap) * dTabx);
			if (x < rect.left) continue;
		}
		else
		{
			x = rect.left;
			y = rect.bottom;
		}
		// text output
		if (i >= 8000)
		{
			ntab = 2000;
		}
		else if (i >= 2000)
		{
			ntab = 1000;
		}
		else if (i >= 100)
		{
			ntab = 100;
		}
		else if (i >= 10)
		{
			ntab = 10;
		}
		if (i <= m_dAmp_Range[0]) continue;


		graphics.DrawLine(&_drawpen_Dash, x ,rect.bottom, x, rect.top);
	}

	pDC->SetTextAlign(TA_LEFT);
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SelectObject(pOldfont);
	pDC->SelectObject(pOldpen);

	int nTabCount = m_pTabGroup->GetTabCount();
	int nTabType;
	int nAmp;
	int nLineType;
	double dSDelay, dLog_X, dLog_Y;
	double dX_Gap, dY_Gap;

	nInit = Get_X_FirstValue();
	dX_Gap = log10((double)nInit);
	dY_Gap = log10((double)4);
	Gdiplus::GraphicsPath gp_Value, gp_Highlight;
	CPoint pt_F;

	gp_Value.Reset();
	pt_F.SetPoint(0, 0);

	m_dCurve_X_Gap = dX_Gap;
	m_dCurve_X_Tap = dTabx;
	m_nCurve_X_Base = rect.left;
	m_nCurve_Y_Base = rect.bottom;

	double dSel_Value_X, dSel_Value_Y;
	int nSel_Pos_Y;
	if (m_pTabGroup->GetTabCount() > 0)
	{
		for (int i = 0; i < nTabCount; i++)
		{
			nTabType = m_pTabGroup->GetTabType(i);

		
			for (int m = 0; m < 4; m++)
			{
				if(m_TCCurve_Data[i][m].m_Array_X_Value.GetSize() == 0)
					continue;
				//////////////////////////// 권고치는 어떻게 하냐
				////////////////////////// check 버튼 확인
				gp_Value.Reset();
				pt_F.SetPoint(0, 0);
				for (int k = 0; k < m_TCCurve_Data[i][m].m_Array_X_Value.GetSize(); k++)
				{
					nAmp = m_TCCurve_Data[i][m].m_Array_X_Value.GetAt(k);
					dSDelay = m_TCCurve_Data[i][m].m_Array_Y_Value.GetAt(k);
					if(dSDelay <= 0. )
						continue;
					dSDelay *= 100;
					dLog_X = log10((double)nAmp);
					dLog_Y = log10((double)dSDelay);
					/////////////
					x = int(rect.left + abs(dLog_X - dX_Gap) * dTabx);
					y = int(rect.bottom - (dLog_Y - dY_Gap) * dTaby);
					if (x < rect.left || x > rect.right) continue;
					if (y < rect.top || y > rect.bottom) continue;

					if (pt_F.x == 0 && pt_F.y == 0)
					{
						pt_F.SetPoint(x, y);
						continue;
					}
					//////////////// 선택 추가
					if (nAmp == m_nCurve_Select )
					{
						Draw_Graph_Data_Select(pDC, graphics, i, m, x, y, dSDelay);
						
					}

					gp_Value.AddLine(pt_F.x, pt_F.y, x, y);
					pt_F.SetPoint(x, y);
				}
				//gp_Value.CloseFigure();

				Draw_Graph_Data(pDC, graphics,i, m,&gp_Value);
				/////////////////// 그리기
			}


		}
	}

	///////////////////////////// COS
	
	if (m_TCCurve_Data_COS[0].m_Array_X_Value.GetSize() > 0)
	{
		gp_Value.Reset();
		pt_F.SetPoint(0, 0);
		for (int k = 0; k < m_TCCurve_Data_COS[0].m_Array_X_Value.GetSize(); k++)
		{
			nAmp = m_TCCurve_Data_COS[0].m_Array_X_Value.GetAt(k);
			dSDelay = m_TCCurve_Data_COS[0].m_Array_Y_Value.GetAt(k);
			if (dSDelay <= 0.)
				continue;
			dSDelay *= 100;
			dLog_X = log10((double)nAmp);
			dLog_Y = log10((double)dSDelay);
			/////////////
			x = int(rect.left + abs(dLog_X - dX_Gap) * dTabx);
			y = int(rect.bottom - (dLog_Y - dY_Gap) * dTaby);
			if (x < rect.left || x > rect.right) continue;
			if (y < rect.top || y > rect.bottom) continue;

			if (pt_F.x == 0 && pt_F.y == 0)
			{
				pt_F.SetPoint(x, y);
				continue;
			}
			if (nAmp == m_nCurve_Select)
			{
				Draw_Graph_Data_Select(pDC, graphics, 5, 0, x, y, dSDelay);

			}

			gp_Value.AddLine(pt_F.x, pt_F.y, x, y);
			pt_F.SetPoint(x, y);
		}
		//gp_Value.CloseFigure();

		Draw_Graph_Data(pDC, graphics, 5, 0, &gp_Value);
	}

	if (m_TCCurve_Data_COS[1].m_Array_X_Value.GetSize() > 0)
	{
		gp_Value.Reset();
		pt_F.SetPoint(0, 0);
		for (int k = 0; k < m_TCCurve_Data_COS[1].m_Array_X_Value.GetSize(); k++)
		{
			nAmp = m_TCCurve_Data_COS[1].m_Array_X_Value.GetAt(k);
			dSDelay = m_TCCurve_Data_COS[1].m_Array_Y_Value.GetAt(k);
			if (dSDelay <= 0.)
				continue;
			dSDelay *= 100;
			dLog_X = log10((double)nAmp);
			dLog_Y = log10((double)dSDelay);
			/////////////
			x = int(rect.left + abs(dLog_X - dX_Gap) * dTabx);
			y = int(rect.bottom - (dLog_Y - dY_Gap) * dTaby);
			if (x < rect.left || x > rect.right) continue;
			if (y < rect.top || y > rect.bottom) continue;

			if (pt_F.x == 0 && pt_F.y == 0)
			{
				pt_F.SetPoint(x, y);
				continue;
			}

			if (nAmp == m_nCurve_Select)
			{
				Draw_Graph_Data_Select(pDC, graphics, 5, 3, x, y, dSDelay);

			}

			gp_Value.AddLine(pt_F.x, pt_F.y, x, y);
			pt_F.SetPoint(x, y);
		}
		//gp_Value.CloseFigure();

		Draw_Graph_Data(pDC, graphics, 5, 3, &gp_Value);
	}
}

void CView_PCE_rst::Draw_Graph_Data(CDC* pDC, Graphics &graphics, int nTab_Idx,int nLineType,Gdiplus::GraphicsPath* gp_Value, Gdiplus::GraphicsPath* gp_Highlight)
{
	SolidBrush						LineBrush(Color(255, 237, 20, 20));
	UINT nDashStyle[4] = { DashStyleSolid, DashStyleDot ,DashStyleDash ,DashStyleDashDotDot };
	int nTab_Type = m_pTabGroup->GetTabType(nTab_Idx);

	/*if (nTab_Type > 2)
	{
		nLineType += 1;
	}*/

	switch (nTab_Idx)
	{
	case 1:
		LineBrush.SetColor(Color(255, 64, 51, 226));
		break;
	case 2:
		LineBrush.SetColor(Color(255, 228, 140, 15));
		break;
	case 3:
		LineBrush.SetColor(Color(255, 63, 119, 25));
		break;
	case 4:
		LineBrush.SetColor(Color(255, 15, 215, 228));
		break;
	case 5:
		LineBrush.SetColor(Color(255, 0, 0, 0));
		break;
	default:
		break;
	}

	Gdiplus::Pen					_drawLinepen(&LineBrush, 2);
	_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[nLineType]);
	graphics.DrawPath(&_drawLinepen, gp_Value);

}

void CView_PCE_rst::Draw_Graph_Data_Select(CDC* pDC, Graphics &graphics, int nTab_Idx, int nLineType, int x, int y, double dSDelay)
{
	SolidBrush						LineBrush(Color(255, 237, 20, 20));
	UINT nDashStyle[4] = { DashStyleSolid, DashStyleDot ,DashStyleDash ,DashStyleDashDotDot };
	int nTab_Type = m_pTabGroup->GetTabType(nTab_Idx);

	CFont font, *pOldfont;
	font.DeleteObject();
	font.CreateFont(12, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, L"굴림체");
	pOldfont = pDC->SelectObject(&font);

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	COLORREF color;
	color = RGB(237, 20, 20);
	switch (nTab_Idx)
	{
	case 1:
		LineBrush.SetColor(Color(255, 64, 51, 226));
		color = RGB(64, 51, 226);
		break;
	case 2:
		LineBrush.SetColor(Color(255, 228, 140, 15));
		color = RGB(228, 140, 15);
		break;
	case 3:
		LineBrush.SetColor(Color(255, 63, 119, 25));
		color = RGB(63, 119, 25);
		break;
	case 4:
		LineBrush.SetColor(Color(255, 15, 215, 228));
		color = RGB(15, 215, 228);
		break;
	case 5:
		LineBrush.SetColor(Color(255, 0, 0, 0));
		color = RGB(0, 0, 0);
		break;
	default:
		break;
	}

	graphics.FillEllipse(&LineBrush, x - 3, y - 3, 6, 6);
	

	Gdiplus::Pen					_drawLinepen(&LineBrush, 1);
	_drawLinepen.SetDashStyle((Gdiplus::DashStyle)nDashStyle[nLineType]);
	graphics.DrawLine(&_drawLinepen, m_nCurve_X_Base, y, x, y);

	CString strValue;
	strValue.Format(_T("%.2lf"), dSDelay/100 );

	pDC->SetTextColor(color);
	pDC->SetTextAlign(TA_RIGHT);
	pDC->TextOut(m_nCurve_X_Base - 25, y - 6, strValue);//y

	
	pDC->SetTextColor(RGB(0, 0, 0));

	CString strMAX[2];

	strMAX[0].Format(_T("%.6lf"), dSDelay / 100);
	strMAX[1].Format(_T("%.6lf"), m_dCurve_Y_MAX);

	if (strMAX[1]== strMAX[0])
	{
		strValue.Format(_T("%d"), m_nCurve_Select);

		SolidBrush						BaseBrush(Color(255, 0, 0, 0));
		Gdiplus::Pen					_drawBasepen(&BaseBrush, 1);
		_drawBasepen.SetDashStyle((Gdiplus::DashStyle)DashStyleSolid);
		graphics.DrawLine(&_drawBasepen, x, y, x, m_nCurve_Y_Base);

		pDC->SetTextAlign(TA_CENTER);
		pDC->TextOut(x, m_nCurve_Y_Base + 20, strValue);//x
	}

	pDC->SetTextAlign(TA_LEFT);
	

	pDC->SelectObject(pOldfont);
}

int CView_PCE_rst::Get_X_FirstValue()
{
	
	int nInit = int(m_dAmp_Range[0]);
	if (nInit >= 1000)
	{
		nInit /= 1000;
		nInit *= 1000;

	}
	else if (nInit >= 100)
	{
		nInit /= 100;
		nInit *= 100;
	}
	else if (nInit >= 10)
	{
		nInit /= 10;
		nInit *= 10;
	}

	return nInit;
}

void CView_PCE_rst::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	m_rectBack[0].SetRect(_rect.left, _rect.top, _rect.Width() / 2 - 5, _rect.top + 44);
	m_rectBack[1].SetRect(_rect.left, m_rectBack[0].bottom + 10, _rect.Width() / 2 - 5, m_rectBack[0].bottom + 264);
//	m_rectBack[2].SetRect(_rect.left, m_rectBack[1].bottom + 10, _rect.Width() / 2 - 5, m_rectBack[1].bottom + 128);
	m_rectBack[3].SetRect(_rect.left, m_rectBack[1].bottom + 10, _rect.Width() / 2 - 5, _rect.bottom);
	m_rectBack[4].SetRect(_rect.Width() / 2 + 5, _rect.top, _rect.right, _rect.bottom);

	MoveSize_List1();
	MoveSize_List2();
	MoveSize_Graph();

	MoveSize_Combo();
	MoveSize_Btn_Check();
	MoveSize_Btn();

	MoveSize_Tab();
}

void CView_PCE_rst::MoveSize_Btn()
{
	if (m_btn_ctrl[0].GetSafeHwnd() == NULL)							return;

	CRect rect = m_rectBack[0];
	
	rect.left = rect.right - 284;
	rect.right = rect.left + 87;
	rect.InflateRect(0, -6);

	m_btn_ctrl_rect[0] = rect;
	m_btn_ctrl[0].MoveWindow(m_btn_ctrl_rect[0]);

	m_btn_ctrl_rect[1] = rect;
	m_btn_ctrl_rect[1].left = m_btn_ctrl_rect[0].right + 8;
	m_btn_ctrl_rect[1].right = m_btn_ctrl_rect[1].left + 87;
	m_btn_ctrl[1].MoveWindow(m_btn_ctrl_rect[1]);

	m_btn_ctrl_rect[2] = rect;
	m_btn_ctrl_rect[2].left = m_btn_ctrl_rect[1].right + 8;
	m_btn_ctrl_rect[2].right = m_btn_ctrl_rect[2].left + 87;
	m_btn_ctrl[2].MoveWindow(m_btn_ctrl_rect[2]);

}

void CView_PCE_rst::MoveSize_Btn_Check()
{
	if (m_ctrBtn_Check[0].GetSafeHwnd() == NULL )							return;

	m_rectCtrl_Check[0] = m_rectBack[1];
	m_rectCtrl_Check[0].bottom = m_rectCtrl_Check[0].top + 44;
	m_rectCtrl_Check[0].InflateRect(-8, -12);
	m_rectCtrl_Check[0].top += 2;
	m_rectCtrl_Check[0].left = m_rectCtrl_Check[0].left + 16;
	m_rectCtrl_Check[0].right = m_rectCtrl_Check[0].left + 83;
	m_ctrBtn_Check[0].MoveWindow(m_rectCtrl_Check[0]);

	m_rectCtrl_Check[1] = m_rectBack[1];
	m_rectCtrl_Check[1].bottom = m_rectCtrl_Check[1].top + 44;
	m_rectCtrl_Check[1].InflateRect(-8, -12);
	m_rectCtrl_Check[1].top += 2;
	m_rectCtrl_Check[1].left = m_rectCtrl_Check[1].left + 310;
	m_rectCtrl_Check[1].right = m_rectCtrl_Check[1].left + 130;
	m_ctrBtn_Check[1].MoveWindow(m_rectCtrl_Check[1]);

	m_rectCtrl_Check_DG= m_rectBack[1];
	m_rectCtrl_Check_DG.bottom = m_rectCtrl_Check_DG.top + 44;
	m_rectCtrl_Check_DG.InflateRect(-8, -12);
	m_rectCtrl_Check_DG.top += 2;
	m_rectCtrl_Check_DG.left = m_rectCtrl_Check_DG.left + 310 + (310 - 16);
	m_rectCtrl_Check_DG.right = m_rectCtrl_Check_DG.left + 130;
	m_ctrBtn_Check_DG.MoveWindow(m_rectCtrl_Check_DG);


	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	m_rectCtrl_Radio[0] = m_rectGraph[3];
	m_rectCtrl_Radio[0].bottom = m_rectCtrl_Radio[0].top + 44;
	m_rectCtrl_Radio[0].InflateRect(-8, -12);
	m_rectCtrl_Radio[0].top += 2;
//	m_rectCtrl_Radio[0].left = m_rectCtrl_Check[0].left + 16;
	m_rectCtrl_Radio[0].right = m_rectCtrl_Radio[0].left + 59;
	m_ctrBtn_Radio[0].MoveWindow(m_rectCtrl_Radio[0]);

	/////////////////////Edit 범위설정
	m_rectCtrl_Edit[0] = m_rectGraph[3];
	m_rectCtrl_Edit[0].top = m_rectCtrl_Radio[0].top;
	m_rectCtrl_Edit[0].left = m_rectCtrl_Radio[0].right ;
	m_rectCtrl_Edit[0].right = m_rectCtrl_Edit[0].left + 86;
	m_rectCtrl_Edit[0].bottom = m_rectCtrl_Edit[0].top + 20;
	m_rectCtrl_Edit[0].InflateRect(-1, -1);
	m_ctrEdit[0].MoveWindow(m_rectCtrl_Edit[0]);

	m_rectCtrl_Edit[1] = m_rectCtrl_Edit[0];
	m_rectCtrl_Edit[1].left = m_rectCtrl_Edit[0].right + 8;
	m_rectCtrl_Edit[1].right = m_rectCtrl_Edit[1].left + 86;
	m_ctrEdit[1].MoveWindow(m_rectCtrl_Edit[1]);


	m_rectCtrl_Radio[1] = m_rectGraph[3];
	m_rectCtrl_Radio[1].bottom = m_rectCtrl_Radio[1].top + 44;
	m_rectCtrl_Radio[1].InflateRect(-8, -12);
	m_rectCtrl_Radio[1].top += 2;
	m_rectCtrl_Radio[1].left = m_rectCtrl_Radio[0].right + 223;
	m_rectCtrl_Radio[1].right = m_rectCtrl_Radio[1].left + 69;
	m_ctrBtn_Radio[1].MoveWindow(m_rectCtrl_Radio[1]);

	/////////////////////Edit 범위설정
	m_rectCtrl_Edit[2] = m_rectCtrl_Edit[1];
	m_rectCtrl_Edit[2].left = m_rectCtrl_Radio[1].right + 5;
	m_rectCtrl_Edit[2].right = m_rectCtrl_Edit[2].left + 86;
	m_ctrEdit[2].MoveWindow(m_rectCtrl_Edit[2]);

	m_rectCtrl_Edit[3] = m_rectCtrl_Edit[2];
	m_rectCtrl_Edit[3].left = m_rectCtrl_Edit[2].right + 8;
	m_rectCtrl_Edit[3].right = m_rectCtrl_Edit[3].left + 86;
	m_ctrEdit[3].MoveWindow(m_rectCtrl_Edit[3]);

}

void CView_PCE_rst::MoveSize_Combo()
{
	if (m_ctrCombo[0].GetSafeHwnd() == NULL)							return;


	/////////////////// 콤보랑 에디트 박스 추가

	m_rectCtrl_Combobox[0] = m_rectBack[0];
	m_rectCtrl_Combobox[0].InflateRect(-8, -10);
	m_rectCtrl_Combobox[0].left = m_rectCtrl_Combobox[0].left + 80;
	m_rectCtrl_Combobox[0].right = m_rectCtrl_Combobox[0].left + 165;
	m_ctrCombo[0].MoveWindow(m_rectCtrl_Combobox[0]);

	m_rectCtrl_Combobox[1] = m_rectCtrl_Combobox[0];
	m_rectCtrl_Combobox[1].left = m_rectCtrl_Combobox[0].right + 8;
	m_rectCtrl_Combobox[1].right = m_rectCtrl_Combobox[1].left + 165;
	m_ctrCombo[1].MoveWindow(m_rectCtrl_Combobox[1]);

	m_rectCtrl_Combobox[2] = m_rectBack[1];
	m_rectCtrl_Combobox[2].bottom = m_rectCtrl_Combobox[2].top + 44;
	m_rectCtrl_Combobox[2].InflateRect(-8, -10);
	m_rectCtrl_Combobox[2].left = m_rectCtrl_Combobox[2].left + 99;
	m_rectCtrl_Combobox[2].right = m_rectCtrl_Combobox[2].left + 178;
	m_ctrCombo[2].MoveWindow(m_rectCtrl_Combobox[2]);

	m_rectCtrl_Combobox[3] = m_rectCtrl_Combobox[2];
	m_rectCtrl_Combobox[3].left = m_rectCtrl_Combobox[2].right + 166;
	m_rectCtrl_Combobox[3].right = m_rectCtrl_Combobox[3].left + 178;
	m_ctrCombo[3].MoveWindow(m_rectCtrl_Combobox[3]);
	////////////////////////////////////////////////


	/*m_rectCtrl_Combobox[4] = m_rectGraph[2];
	m_rectCtrl_Combobox[4].InflateRect(-8, -10);
	m_rectCtrl_Combobox[4].left = m_rectCtrl_Combobox[4].left + 60;
	m_rectCtrl_Combobox[4].right = m_rectCtrl_Combobox[4].left + 178;
	m_ctrCombo[4].MoveWindow(m_rectCtrl_Combobox[4]);*/


}

void CView_PCE_rst::MoveSize_List1()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL)							return;

	/////////////////////////////////////////////타이틀  
	m_rectTitle[0] = m_rectBack[1];
	m_rectTitle[0].top = m_rectTitle[0].top + 44;
	m_rectTitle[0].right = m_rectTitle[0].left + 81;
	m_rectTitle[0].bottom = m_rectTitle[0].top + 30;

	m_rectBack[5] = m_rectBack[1];
	m_rectBack[5].bottom = m_rectBack[5].top + 44;


	CRect rectList;

	rectList = m_rectBack[1];
	rectList.left -= 1;
	rectList.right += 1;
	rectList.top += 44 + 30;
	rectList.bottom = m_rectBack[1].bottom - 1;
	m_ctrList[0].MoveWindow(rectList);

	////////////////// combo , check 추가
	
}
void CView_PCE_rst::MoveSize_Tab()
{
	if (m_pTabGroup == NULL) return;
	
	m_rectCtrl_Tab = m_rectBack[3];
	m_rectCtrl_Tab.bottom -= 2;

	m_pTabGroup->MoveWindow(m_rectCtrl_Tab);

}
void CView_PCE_rst::MoveSize_List2()
{
	if (m_ctrList[1].GetSafeHwnd() == NULL)							return;

	/////////////////////////////////////////////타이틀  
	m_rectTitle[1] = m_rectBack[2];
	m_rectTitle[1].right = m_rectTitle[1].left + 81;
	m_rectTitle[1].bottom = m_rectTitle[1].top + 30;


	CRect rectList;

	rectList = m_rectBack[2];
	rectList.left -= 1;
	rectList.right += 1;
	rectList.top += 30;
	rectList.bottom = m_rectBack[2].bottom - 1;
	m_ctrList[1].MoveWindow(rectList);

}

void CView_PCE_rst::MoveSize_Graph()
{
	if (m_ctrBtn_Check[2].GetSafeHwnd() == NULL)
		return;

	////////////////////////////////////////////타이틀  
	m_rectTitle[2] = m_rectBack[4];
	m_rectTitle[2].right = m_rectTitle[2].left + 146;
	m_rectTitle[2].bottom = m_rectTitle[2].top + 30;


	m_rectGraph[0] = m_rectBack[4];
	m_rectGraph[0].top		= m_rectTitle[2].bottom; 
	m_rectGraph[0].bottom	= m_rectGraph[0].top + 56;

	m_rectGraph[1] = m_rectBack[4];
	m_rectGraph[1].top = m_rectGraph[0].bottom;
	m_rectGraph[1].bottom = m_rectGraph[1].top + 56;

	m_rectGraph[2] = m_rectBack[4];
	m_rectGraph[2].top = m_rectGraph[1].bottom;
	m_rectGraph[2].bottom = m_rectGraph[2].top + 45;

	m_rectGraph[3] = m_rectBack[4];
	m_rectGraph[3].top = m_rectGraph[2].bottom;
	m_rectGraph[3].bottom = m_rectGraph[3].top + 45;


	m_rectGraph[4] = m_rectBack[4];
	m_rectGraph[4].top = m_rectGraph[3].bottom;

	/////////////////////////////////////////////////////////// 설정치
	m_rectCtrl_Check[2] = m_rectGraph[0];
	m_rectCtrl_Check[2].left += 96;
	m_rectCtrl_Check[2].right = m_rectCtrl_Check[2].left + 39;
	m_rectCtrl_Check[2].top += 6;
	m_rectCtrl_Check[2].bottom = m_rectCtrl_Check[2].top + 20;
	////
	m_rectCtrl_Check[3] = m_rectCtrl_Check[2];
	m_rectCtrl_Check[3].left = m_rectCtrl_Check[2].right + 60;
	m_rectCtrl_Check[3].right = m_rectCtrl_Check[3].left + 84;

	m_rectCtrl_Check[4] = m_rectCtrl_Check[3];
	m_rectCtrl_Check[4].top = m_rectCtrl_Check[3].bottom + 5;
	m_rectCtrl_Check[4].bottom = m_rectCtrl_Check[4].top + 20;
	////

	m_rectCtrl_Check[5] = m_rectCtrl_Check[3];
	m_rectCtrl_Check[5].left = m_rectCtrl_Check[3].right + 60;
	m_rectCtrl_Check[5].right = m_rectCtrl_Check[5].left + 84;

	m_rectCtrl_Check[6] = m_rectCtrl_Check[5];
	m_rectCtrl_Check[6].top = m_rectCtrl_Check[6].bottom + 5;
	m_rectCtrl_Check[6].bottom = m_rectCtrl_Check[6].top + 20;
	////

	m_rectCtrl_Check[7] = m_rectCtrl_Check[5];
	m_rectCtrl_Check[7].left = m_rectCtrl_Check[5].right + 60;
	m_rectCtrl_Check[7].right = m_rectCtrl_Check[7].left + 84;

	m_rectCtrl_Check[8] = m_rectCtrl_Check[7];
	m_rectCtrl_Check[8].top = m_rectCtrl_Check[7].bottom + 5;
	m_rectCtrl_Check[8].bottom = m_rectCtrl_Check[8].top + 20;
	////

	m_rectCtrl_Check[9] = m_rectCtrl_Check[7];
	m_rectCtrl_Check[9].left = m_rectCtrl_Check[7].right + 60;
	m_rectCtrl_Check[9].right = m_rectCtrl_Check[9].left + 84;

	m_rectCtrl_Check[10] = m_rectCtrl_Check[9];
	m_rectCtrl_Check[10].top = m_rectCtrl_Check[9].bottom + 5;
	m_rectCtrl_Check[10].bottom = m_rectCtrl_Check[10].top + 20;

	/////////////////////////////////////////////////////////// 권고치
	m_rectCtrl_Check[11] = m_rectGraph[1];
	m_rectCtrl_Check[11].left += 96;
	m_rectCtrl_Check[11].right = m_rectCtrl_Check[11].left + 39;
	m_rectCtrl_Check[11].top += 6;
	m_rectCtrl_Check[11].bottom = m_rectCtrl_Check[11].top + 20;
	////
	m_rectCtrl_Check[12] = m_rectCtrl_Check[11];
	m_rectCtrl_Check[12].left = m_rectCtrl_Check[11].right + 60;
	m_rectCtrl_Check[12].right = m_rectCtrl_Check[12].left + 84;

	m_rectCtrl_Check[13] = m_rectCtrl_Check[12];
	m_rectCtrl_Check[13].top = m_rectCtrl_Check[12].bottom + 5;
	m_rectCtrl_Check[13].bottom = m_rectCtrl_Check[13].top + 20;
	////

	m_rectCtrl_Check[14] = m_rectCtrl_Check[12];
	m_rectCtrl_Check[14].left = m_rectCtrl_Check[12].right + 60;
	m_rectCtrl_Check[14].right = m_rectCtrl_Check[14].left + 84;

	m_rectCtrl_Check[15] = m_rectCtrl_Check[14];
	m_rectCtrl_Check[15].top = m_rectCtrl_Check[14].bottom + 5;
	m_rectCtrl_Check[15].bottom = m_rectCtrl_Check[15].top + 20;
	////

	m_rectCtrl_Check[16] = m_rectCtrl_Check[14];
	m_rectCtrl_Check[16].left = m_rectCtrl_Check[14].right + 60;
	m_rectCtrl_Check[16].right = m_rectCtrl_Check[16].left + 84;

	m_rectCtrl_Check[17] = m_rectCtrl_Check[16];
	m_rectCtrl_Check[17].top = m_rectCtrl_Check[16].bottom + 5;
	m_rectCtrl_Check[17].bottom = m_rectCtrl_Check[17].top + 20;
	////

	m_rectCtrl_Check[18] = m_rectCtrl_Check[16];
	m_rectCtrl_Check[18].left = m_rectCtrl_Check[16].right + 60;
	m_rectCtrl_Check[18].right = m_rectCtrl_Check[18].left + 84;

	m_rectCtrl_Check[19] = m_rectCtrl_Check[18];
	m_rectCtrl_Check[19].top = m_rectCtrl_Check[18].bottom + 5;
	m_rectCtrl_Check[19].bottom = m_rectCtrl_Check[19].top + 20;


	for (int i = 2; i < 20; i++)
		m_ctrBtn_Check[i].MoveWindow(m_rectCtrl_Check[i]);

	///////////////////////////////////////////////////////////  COS

	m_rectCtrl_Combobox[4] = m_rectGraph[2];
	m_rectCtrl_Combobox[4].InflateRect(-8, -10);
	m_rectCtrl_Combobox[4].left = m_rectCtrl_Combobox[4].left + 100;
	m_rectCtrl_Combobox[4].right = m_rectCtrl_Combobox[4].left + 178;
	m_ctrCombo[4].MoveWindow(m_rectCtrl_Combobox[4]);

	m_rectCtrl_Combobox[5] = m_rectCtrl_Combobox[4];
	m_rectCtrl_Combobox[5].left = m_rectCtrl_Combobox[4].right + 100;
	m_rectCtrl_Combobox[5].right = m_rectCtrl_Combobox[5].left + 178;
	m_ctrCombo[5].MoveWindow(m_rectCtrl_Combobox[5]);

}

void CView_PCE_rst::Create_Edit()
{
	if (!m_ctrEdit[0].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | DT_VCENTER,
		CRect(100, 100, 200, 200), this, ID_APP_PCE_EDIT_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrEdit[1].Create(WS_CHILD | WS_VISIBLE | ES_CENTER,
		CRect(100, 100, 200, 200), this, ID_APP_PCE_EDIT_2))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrEdit[2].Create(WS_CHILD | WS_VISIBLE | ES_CENTER,
		CRect(100, 100, 200, 200), this, ID_APP_PCE_EDIT_3))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrEdit[3].Create(WS_CHILD | WS_VISIBLE | ES_CENTER,
		CRect(100, 100, 200, 200), this, ID_APP_PCE_EDIT_4))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	m_ctrEdit[2].EnableWindow(FALSE);
	m_ctrEdit[3].EnableWindow(FALSE);
}

void CView_PCE_rst::Create_ListCtrl()
{
	m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect[2];
	rect[0] = CRect(10, 50, 350, 500);
	m_ctrList[0].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER| LVS_SHOWSELALWAYS, rect[0], this, ID_APP_PCE_LIST_1);
	m_ctrList[0].InsertColumn(0, _T("순번"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(1, _T("1"), HDF_LEFT, 165);
	m_ctrList[0].InsertColumn(2, _T("2"), HDF_LEFT, 165);
	m_ctrList[0].InsertColumn(3, _T("3"), HDF_LEFT, 165);
	m_ctrList[0].InsertColumn(4, _T("4"), HDF_LEFT, 165);
	m_ctrList[0].InsertColumn(5, _T("5"), HDF_LEFT, 165);
	m_ctrList[0].InsertColumn(6, _T("idx_1"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(7, _T("idx_2"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(8, _T("idx_3"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(9, _T("idx_4"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(10, _T("idx_5"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(11, _T("type_1"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(12, _T("type_2"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(13, _T("type_3"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(14, _T("type_4"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(15, _T("type_5"), HDF_LEFT, 0);
	m_ctrList[0].ShowWindow(SW_SHOW);
	m_ctrList[0].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SINGLEROW );
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


	/*rect[1] = CRect(10, 50, 350, 500);
	m_ctrList[1].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_PCE_LIST_2);
	m_ctrList[1].InsertColumn(0, _T(""), HDF_LEFT, 100);
	m_ctrList[1].InsertColumn(1, _T("형식"), HDF_LEFT, 140);
	m_ctrList[1].InsertColumn(2, _T("한시탭"), HDF_LEFT, 140);
	m_ctrList[1].InsertColumn(3, _T("한시레버"), HDF_LEFT, 140);
	m_ctrList[1].InsertColumn(4, _T("순시탭"), HDF_LEFT, 140);
	m_ctrList[1].InsertColumn(5, _T("CT 1차"), HDF_LEFT, 140);
	m_ctrList[1].InsertColumn(6, _T("CT 2차"), HDF_LEFT, 140);
	m_ctrList[1].InsertColumn(7, _T("CT 2차"), HDF_LEFT, 0);
	m_ctrList[1].ShowWindow(SW_SHOW);
	m_ctrList[1].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[1].m_HeaderCtrl.SetHeight(25);
	m_ctrList[1].m_HeaderCtrl.SetFlat();
	m_ctrList[1].m_HeaderCtrl.SetFlat();
	m_ctrList[1].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[1].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[1].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[1].SetBgColor(RGB(255, 255, 255));
	m_ctrList[1].SetUnderLine();
	m_ctrList[1].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[1].SetTextFont(&m_listfont);
	m_ctrList[1].SetRowHeight(23);

	m_ctrList[1].InsertItem(0, _T("OCR"), RGB(0, 0, 0), RGB(238,247,240), HDF_CENTER);
	m_ctrList[1].SetItemText(0, 1, _T("OCGR"), RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
	m_ctrList[1].InsertItem(1, _T("OCGR"), RGB(0, 0, 0), RGB(238, 247, 240), HDF_CENTER);*/
}

void CView_PCE_rst::Create_Combobox()
{
	m_font_Combobox.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	if (!m_ctrCombo[0].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_PCE_COMBO_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}
	if (!m_ctrCombo[1].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_SORT
		, CRect(100, 100, 200, 200), this, ID_APP_PCE_COMBO_2))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[2].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_PCE_COMBO_3))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[3].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_PCE_COMBO_4))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[4].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_PCE_COMBO_5))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	if (!m_ctrCombo[5].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_PCE_COMBO_6))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	m_ctrCombo[0].SetTextFont(&m_font_Combobox);
	m_ctrCombo[1].SetTextFont(&m_font_Combobox);
	m_ctrCombo[2].SetTextFont(&m_font_Combobox);
	m_ctrCombo[3].SetTextFont(&m_font_Combobox);
	m_ctrCombo[4].SetTextFont(&m_font_Combobox);
	m_ctrCombo[5].SetTextFont(&m_font_Combobox);

	m_ctrCombo[0].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[1].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[2].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[3].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[4].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo[5].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));

	m_ctrCombo[0].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[1].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[2].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[3].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[4].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo[5].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);

	m_ctrCombo[0].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[1].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[2].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[3].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[4].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo[5].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	m_ctrCombo[0].SetDropDownHeight(10);
	m_ctrCombo[1].SetDropDownHeight(10);
	m_ctrCombo[2].SetDropDownHeight(10);
	m_ctrCombo[3].SetDropDownHeight(10);
	m_ctrCombo[4].SetDropDownHeight(10);
	m_ctrCombo[5].SetDropDownHeight(10);


	m_ctrCombo[2].ShowWindow(SW_HIDE);
	m_ctrCombo[3].ShowWindow(SW_HIDE);

	//m_ctrCombo[4].AddString(_T("전류"));
	//m_ctrCombo[4].AddString(_T("PU"));
	//m_ctrCombo[4].SetCurSel(1);

	//m_ctrCombo[4].ShowWindow(SW_HIDE);
}

void CView_PCE_rst::Create_Btn_Check()
{
	CRect rect;
	rect = CRect(10, 50, 350, 500);

	if (!m_ctrBtn_Check[0].Create(_T("EFI 검토"), WS_CHILD | WS_VISIBLE |  BS_CHECKBOX | BS_OWNERDRAW
		, rect , this, ID_APP_PCE_BTN_CHECK_1) )
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	

	if (!m_ctrBtn_Check[1].Create(_T("고압 수용가 검토"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_2))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	m_ctrBtn_Check[0].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
	m_ctrBtn_Check[1].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	m_ctrBtn_Check[0].m_pFont_Text = &m_font_Combobox;
	m_ctrBtn_Check[1].m_pFont_Text = &m_font_Combobox;
	m_ctrBtn_Check[0].m_colorBg = RGB(255, 255, 255);
	m_ctrBtn_Check[1].m_colorBg = RGB(255, 255, 255);

	if (!m_ctrBtn_Check_DG.Create(_T("분산형전원 검토"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_DG))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}
	m_ctrBtn_Check_DG.SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
	m_ctrBtn_Check_DG.m_pFont_Text = &m_font_Combobox;
	m_ctrBtn_Check_DG.m_colorBg = RGB(255, 255, 255);

	////////////////////////////////////////////////////////////////////////////////  설정치
	if (!m_ctrBtn_Check[2].Create(_T("CB Relay"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_3))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[3].Create(_T("R1 - Fast"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_4))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[4].Create(_T("R1 - Delay"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_5))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[5].Create(_T("R2 - Fast"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_6))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[6].Create(_T("R2 - Delay"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_7))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[7].Create(_T("R3 - Fast"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_8))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[8].Create(_T("R3 - Delay"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_9))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[9].Create(_T("R4 - Fast"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_10))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[10].Create(_T("R4 - Delay"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_11))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}
	///////////////////////////////////////////////// 권고치
	if (!m_ctrBtn_Check[11].Create(_T("CB Relay"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_12))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[12].Create(_T("R1 - Fast"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_13))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[13].Create(_T("R1 - Delay"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_14))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[14].Create(_T("R2 - Fast"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_15))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[15].Create(_T("R2 - Delay"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_16))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[16].Create(_T("R3 - Fast"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_17))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[17].Create(_T("R3 - Delay"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_18))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[18].Create(_T("R4 - Fast"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_19))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[19].Create(_T("R4 - Delay"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_CHECK_20))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}


	for (int i = 2 ; i < 20; i++)
	{
		m_ctrBtn_Check[i].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
		m_ctrBtn_Check[i].m_pFont_Text = &m_font_Combobox;
		m_ctrBtn_Check[i].m_colorBg = RGB(255, 255, 255);
	}
	m_ctrBtn_Check[2].m_colorText = RGB(237,20,20);

	m_ctrBtn_Check[3].m_colorText = RGB(64, 51, 226);   
	m_ctrBtn_Check[4].m_colorText = RGB(64, 51, 226);

	m_ctrBtn_Check[5].m_colorText = RGB(228,140,15);
	m_ctrBtn_Check[6].m_colorText = RGB(228, 140, 15);

	m_ctrBtn_Check[7].m_colorText = RGB(63, 119, 25);
	m_ctrBtn_Check[8].m_colorText = RGB(63, 119, 25);

	m_ctrBtn_Check[9].m_colorText = RGB(7, 196, 208); ///////////////// 선색:(15,215,228)
	m_ctrBtn_Check[10].m_colorText = RGB(7, 196, 208);
	

	m_ctrBtn_Check[11].m_colorText = RGB(237, 20, 20);

	m_ctrBtn_Check[12].m_colorText = RGB(64, 51, 226);
	m_ctrBtn_Check[13].m_colorText = RGB(64, 51, 226);

	m_ctrBtn_Check[14].m_colorText = RGB(228, 140, 15);
	m_ctrBtn_Check[15].m_colorText = RGB(228, 140, 15);

	m_ctrBtn_Check[16].m_colorText = RGB(63, 119, 25);
	m_ctrBtn_Check[17].m_colorText = RGB(63, 119, 25);

	m_ctrBtn_Check[18].m_colorText = RGB(7, 196, 208); ///////////////// 선색:(15,215,228)
	m_ctrBtn_Check[19].m_colorText = RGB(7, 196, 208);

	for (int i = 2; i < 20; i++)
	{
		m_ctrBtn_Check[i].ShowWindow(SW_HIDE);
		m_ctrBtn_Check[i].SetCheckButton(CHECKBOX_CHECKED);
	}
		

	////////////////////////////////////////////////////////////////////////////////
	if (!m_ctrBtn_Radio[0].Create(_T("Phase"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_RADIO_1))
	{
		AfxMessageBox(_T("Create PCE Radio Fail.\n"));
		return;
	}



	if (!m_ctrBtn_Radio[1].Create(_T("Ground"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_PCE_BTN_RADIO_2))
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

void CView_PCE_rst::Create_Btn()
{
	m_btn_ctrl_rect[0] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[0].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[0], this, ID_APP_PCE_BTN_1))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PCE Button Fail.\n"));
		return;
	}
	m_btn_ctrl[0].SetBitmapID(IDB_PCE_PATH_NOR, IDB_PCE_PATH_CLK, IDB_PCE_PATH_OVR);

	m_btn_ctrl_rect[1] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[1].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[1], this, ID_APP_PCE_BTN_2))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PCE Button Fail.\n"));
		return;
	}
	m_btn_ctrl[1].SetBitmapID(IDB_PCE_AUTO_NOR, IDB_PCE_AUTO_CLK, IDB_PCE_AUTO_OVR);

	m_btn_ctrl_rect[2] = CRect(10, 20, 90, 250);
	if (!m_btn_ctrl[2].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_ctrl_rect[0], this, ID_APP_PCE_BTN_3))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PCE Button Fail.\n"));
		return;
	}
	m_btn_ctrl[2].SetBitmapID(IDB_PCE_RPT_NOR, IDB_PCE_RPT_CLK, IDB_PCE_RPT_OVR);
}

void CView_PCE_rst::Create_Tab()
{
	m_rectCtrl_Tab = CRect(10, 20, 90, 250);
	m_pTabGroup = new CPNOCtrl_Group;
	BOOL bRet = m_pTabGroup->Create(m_rectCtrl_Tab, this);
	m_pTabGroup->SetSkinInit_Res(IDB_TAB_LEFT, IDB_TAB_CENTER, IDB_TAB_RIGHT, IDB_TAB_ACTIVE, IDB_TAB_INACTIVE);
	//m_pTabGroup->AddTabInfor((LPWSTR)(LPCTSTR)_T("CB:123456789101112131415"), NULL);
	//m_pTabGroup->AddTabInfor((LPWSTR)(LPCTSTR)_T("RA:123456789101112131415"), NULL);
	//m_pTabGroup->AddTabInfor((LPWSTR)(LPCTSTR)_T("RA:123456789101112131415"), NULL);
	//m_pTabGroup->AddTabInfor((LPWSTR)(LPCTSTR)_T("RA:123456789101112131415"), NULL);
	//m_pTabGroup->AddTabInfor((LPWSTR)(LPCTSTR)_T("RA:123456789101112131415"), NULL);
	m_pTabGroup->ShowWindow(SW_SHOW);


	
	
}

CView_PCE_rst_RelayDlg*			CView_PCE_rst::Create_Tab_Relay()
{
	CRect r = m_pTabGroup->GetInDrawScreenRect();
	CView_PCE_rst_RelayDlg* pTab_Relay = new CView_PCE_rst_RelayDlg();
	pTab_Relay->Create(IDD_PCE_RST_RELAY_DLG, m_pTabGroup);
	pTab_Relay->MoveWindow(r);
	pTab_Relay->ShowWindow(SW_HIDE);
	pTab_Relay->m_pMsg_Wnd = this;

	return pTab_Relay;
}

CView_PCE_rst_RCDlg*			CView_PCE_rst::Create_Tab_RC()
{
	CRect r = m_pTabGroup->GetInDrawScreenRect();
	CView_PCE_rst_RCDlg* pTab_RC = new CView_PCE_rst_RCDlg();
	pTab_RC->Create(IDD_PCE_RST_RC_DLG, m_pTabGroup);
	pTab_RC->MoveWindow(r);
	pTab_RC->ShowWindow(SW_HIDE);
	pTab_RC->m_pMsg_Wnd = this;

	return pTab_RC;
}

CView_PCE_rst_EFIDlg*			CView_PCE_rst::Create_Tab_EFI()
{
	CRect r = m_pTabGroup->GetInDrawScreenRect();
	CView_PCE_rst_EFIDlg* pTab_EFI = new CView_PCE_rst_EFIDlg();
	pTab_EFI->Create(IDD_PCE_RST_EFI_DLG, m_pTabGroup);
	pTab_EFI->MoveWindow(r);
	pTab_EFI->ShowWindow(SW_HIDE);
	pTab_EFI->m_pMsg_Wnd = this;

	return pTab_EFI;
}

CView_PCE_rst_CUSDlg*			CView_PCE_rst::Create_Tab_CUS()
{
	CRect r = m_pTabGroup->GetInDrawScreenRect();
	CView_PCE_rst_CUSDlg* pTab_CUS = new CView_PCE_rst_CUSDlg();
	pTab_CUS->Create(IDD_PCE_RST_CUS_DLG, m_pTabGroup);
	pTab_CUS->MoveWindow(r);
	pTab_CUS->ShowWindow(SW_HIDE);
	pTab_CUS->m_pMsg_Wnd = this;

	return pTab_CUS;
}

void CView_PCE_rst::OnControlbutton_click_check1()
{
	BOOL bCheck = m_ctrBtn_Check[0].GetCheckButton();

	if (bCheck)
	{
		m_ctrCombo[2].EnableWindow(TRUE);
	}
	else
	{
		m_ctrCombo[2].EnableWindow(FALSE);
	}
}

void CView_PCE_rst::OnControlbutton_click_check2()
{
	BOOL bCheck = m_ctrBtn_Check[1].GetCheckButton();

	if (bCheck)
	{
		m_ctrCombo[3].EnableWindow(TRUE);
	}
	else
	{
		m_ctrCombo[3].EnableWindow(FALSE);
	}
}

void CView_PCE_rst::OnControlbutton_click_Radio1()
{
	BOOL bCheck = m_ctrBtn_Radio[0].GetCheckButton();
	CString strMin, strMax;
	if (bCheck)
	{
		m_ctrBtn_Radio[1].SetCheckButton(FALSE);

		GetDlgItemText(ID_APP_PCE_EDIT_1, strMin);
		GetDlgItemText(ID_APP_PCE_EDIT_2, strMax);

		m_dAmp_Range[0] = _wtof(strMin);
		m_dAmp_Range[1] = _wtof(strMax);

		m_ctrEdit[0].EnableWindow(TRUE);
		m_ctrEdit[1].EnableWindow(TRUE);
		m_ctrEdit[2].EnableWindow(FALSE);
		m_ctrEdit[3].EnableWindow(FALSE);
	}
	else
	{
		m_ctrBtn_Radio[1].SetCheckButton(TRUE);

		GetDlgItemText(ID_APP_PCE_EDIT_3, strMin);
		GetDlgItemText(ID_APP_PCE_EDIT_4, strMax);

		m_dAmp_Range[0] = _wtof(strMin);
		m_dAmp_Range[1] = _wtof(strMax);

		m_ctrEdit[2].EnableWindow(TRUE);
		m_ctrEdit[3].EnableWindow(TRUE);
		m_ctrEdit[0].EnableWindow(FALSE);
		m_ctrEdit[1].EnableWindow(FALSE);
	}
	m_ctrBtn_Radio[1].RedrawWindow();
	RedrawWindow(m_rectGraph[4]);
}

void CView_PCE_rst::OnControlbutton_click_Radio2()
{
	BOOL bCheck = m_ctrBtn_Radio[1].GetCheckButton();

	CString strMin, strMax;

	if (bCheck)
	{
		m_ctrBtn_Radio[0].SetCheckButton(FALSE);
			
		GetDlgItemText(ID_APP_PCE_EDIT_3, strMin);
		GetDlgItemText(ID_APP_PCE_EDIT_4, strMax);

		m_dAmp_Range[0] = _wtof(strMin);
		m_dAmp_Range[1] = _wtof(strMax);

		m_ctrEdit[2].EnableWindow(TRUE);
		m_ctrEdit[3].EnableWindow(TRUE);
		m_ctrEdit[0].EnableWindow(FALSE);
		m_ctrEdit[1].EnableWindow(FALSE);
	}
	else
	{
		m_ctrBtn_Radio[0].SetCheckButton(TRUE);

		GetDlgItemText(ID_APP_PCE_EDIT_1, strMin);
		GetDlgItemText(ID_APP_PCE_EDIT_2, strMax);

		m_dAmp_Range[0] = _wtof(strMin);
		m_dAmp_Range[1] = _wtof(strMax);

		m_ctrEdit[0].EnableWindow(TRUE);
		m_ctrEdit[1].EnableWindow(TRUE);
		m_ctrEdit[2].EnableWindow(FALSE);
		m_ctrEdit[3].EnableWindow(FALSE);
	}
	m_ctrBtn_Radio[0].RedrawWindow();
	RedrawWindow(m_rectGraph[4]);
}



void CView_PCE_rst::OnControlbutton_click_Run()
{
	int nSel = m_ctrCombo[1].GetCurSel();
	if (nSel == -1)
		return;

	int nDL_Idx = (int)m_ctrCombo[1].GetItemData(nSel);
	int nEFI_chk = m_ctrBtn_Check[0].GetCheckButton();
	int nCUS_chk = m_ctrBtn_Check[1].GetCheckButton();
	int nDG_chk = m_ctrBtn_Check_DG.GetCheckButton();

	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_RUN_DL"), 1, (double)nDL_Idx);
	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_RUN_MODE"), 1, (double)1);
	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_PATH_EFIEN"), 1, (double)nEFI_chk);
	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_PATH_HVCUSEN"), 1, (double)nCUS_chk);
	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_PATH_GENEN"), 1, (double)nDG_chk);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("12"), GetVIewID());
	//pDataMng->Excute_Appl(_T("8/9"));

	m_bTimer = TRUE;
	m_nCompAppl_ID = 12;
	SetTimer(1, 100, NULL);
}

void CView_PCE_rst::Clear_TCCurveData()
{
	for (int i = 0; i < 5; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			m_TCCurve_Data[i][k].Init();
		}
	}

	m_dCurve_X_Gap = -999999.;
	m_dCurve_X_Tap = -999999.;
	m_nCurve_X_Base = -999999;
	m_dCurve_Y_MAX  = -1;
	m_nCurve_Y_Base = -1;
//	m_nCurve_Select = -1;
}

void CView_PCE_rst::OnCtrl_Range_Btn_Check(UINT id)
{
	Update_Data_PCE();
	//OnControlbutton_click_Auto();
}

void CView_PCE_rst::OnControlbutton_click_Auto()
{
	if(m_nSelect_Path == -1)
	{
		AfxMessageBox(_T("선택된 경로가 없습니다."));
		return;
	}

	int nSel = m_ctrCombo[1].GetCurSel();
	if (nSel == -1)
		return;

	int nDL_Idx = (int)m_ctrCombo[1].GetItemData(nSel);

	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_RUN_DL"), 1, (double)nDL_Idx);
	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_RUN_MODE"), 1, (double)2);
	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_RUN_PATH"), 1, (double)m_nSelect_Path);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("12"), GetVIewID());
	//pDataMng->Excute_Appl(_T("8/9"));

	m_bTimer = TRUE;
	m_nCompAppl_ID = 12;
	SetTimer(1, 100, NULL);

	

}

void CView_PCE_rst::OnControlbutton_click_Rpt()
{
	if (m_nSelect_Path == -1)
	{
		AfxMessageBox(_T("선택된 경로가 없습니다."));
		return;
	}

	int nSel = m_ctrCombo[1].GetCurSel();
	if (nSel == -1)
		return;

	int nDL_Idx = (int)m_ctrCombo[1].GetItemData(nSel);

	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_RUN_DL"), 1, (double)nDL_Idx);
	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_RUN_MODE"), 1, (double)4);
	PUTDOUBLE2VALUE(_T("PCEOPT_DYN_UIN"), _T("PCEOPT_RUN_PATH"), 1, (double)m_nSelect_Path);

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("12"), GetVIewID());
	//pDataMng->Excute_Appl(_T("8/9"));

	m_bTimer = TRUE;
	m_nCompAppl_ID = 12;
	SetTimer(1, 100, NULL);
}

void CView_PCE_rst::OnPCE_rstCombo1SelectChange()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	Clear_Data();

	CString	strSS;
	CStringArray Array_DL;
	CIntArray	 Array_DL_Idx;

	m_strComboValue[0] = m_strComboValue[1] = m_strComboValue[2] = _T("");

	m_ctrCombo[0].GetLBText(nSel, strSS);

	m_strComboValue[0] = strSS;

	m_ctrCombo[1].ResetContent();

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
}

void CView_PCE_rst::OnPCE_rstCombo2SelectChange()
{
	Clear_Data();
}

void CView_PCE_rst::OnPCE_rstCombo5SelectChange()
{
	m_TCCurve_Data_COS[0].Init();

	CDataManager* pDataMng = CDataManager::Instance();
	int nSel_COS = m_ctrCombo[4].GetCurSel();

	if (nSel_COS > 0)
	{
		CString strCOS;
		m_ctrCombo[4].GetLBText(nSel_COS, strCOS);
		int nTCCSET_idx = pDataMng->GetTCCSET_Index(strCOS);
		if (nTCCSET_idx)
		{
			//////////////nSEL_COS -1
			Update_TCCurve_COS(0, nSel_COS - 1, nTCCSET_idx);
		}
	}
	
	RedrawWindow(m_rectGraph[4]);
}

void CView_PCE_rst::OnPCE_rstCombo6SelectChange()
{

	m_TCCurve_Data_COS[1].Init();

	CDataManager* pDataMng = CDataManager::Instance();
	int nSel_COS = m_ctrCombo[5].GetCurSel();

	if (nSel_COS > 0)
	{
		CString strCOS;
		m_ctrCombo[5].GetLBText(nSel_COS, strCOS);
		int nTCCSET_idx = pDataMng->GetTCCSET_Index(strCOS);
		if (nTCCSET_idx)
		{
			//////////////nSEL_COS -1
			Update_TCCurve_COS(1, nSel_COS - 1, nTCCSET_idx);
		}
	}

	RedrawWindow(m_rectGraph[4]);
}

void CView_PCE_rst::Update_TCCurve_COS(int nNumber,int nSel_COS , int nTCCSET_idx)
{
	double dTccSet[4];
	dTccSet[0] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_A"), nTCCSET_idx);
	dTccSet[1] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_B"), nTCCSET_idx);
	dTccSet[2] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_C"), nTCCSET_idx);
	dTccSet[3] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_D"), nTCCSET_idx);

	double dPickup[2];
	double dSDelay;
	double dSet_Pickup[11] = {	13.2 ,21.45,43,69.5	,88	,111,140.5	,176,220,341,528 };


	m_TCCurve_Data_COS[nNumber].Init();
	

	double dSValue = dSet_Pickup[1];
	double dStart_Value = max(dSet_Pickup[nSel_COS], m_dAmp_Range[0]);

	for (int i = int(dStart_Value); i <= m_dAmp_Range[1]; i++)
	{
		//pick_up(i) = x(i) / (app.CB_OCR_tap_EF.Value*app.CB_OCR_CTr_EF.Value);
		dPickup[0] = i / (dSet_Pickup[nSel_COS]);
		//pick_up1(i) = pick_up(i) ^ b;
		dPickup[1] = pow(dPickup[0], dTccSet[1]);
		//y_cb_ocr(i) = max(tms * (a / (pick_up1(i) + c) + d), mrt);
		dSDelay = dTccSet[0] / (dPickup[1] + dTccSet[2]); 

		if (m_nCurve_Select == i)
		{
			if (m_dCurve_Y_MAX < dSDelay)
				m_dCurve_Y_MAX = dSDelay;
		}

		m_TCCurve_Data_COS[nNumber].m_Array_X_Value.Add(i);
		m_TCCurve_Data_COS[nNumber].m_Array_Y_Value.Add(dSDelay);
	}



}

void CView_PCE_rst::OnPCE_ListCtrlDBClick_1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	if (nRow == -1)
		return;


	if (m_pTabGroup->GetTabCount() > 0)
	{
		if (AfxMessageBox(_T("검토 경로를 변경하시겠습니까?"), MB_YESNO) == IDNO)
			return;
	}
	
	m_pTabGroup->RemoveAllTab();

	for (int i = 2; i < 20; i++)
	{
		m_ctrBtn_Check[i].EnableWindow(FALSE);
		m_ctrBtn_Check[i].ShowWindow(SW_HIDE);
	}
	

	m_nSelect_Path = _wtoi(m_ctrList[0].GetItemText(nRow, 0));

	int nTabCount = 0;

	CString strIdx,strType;
	CString strName[5] ;
	int nIdx[5] = { 0, };
	int nType[5] = { 0, };
	for (int i = 6; i <= 10; i++)
	{
		strIdx = m_ctrList[0].GetItemText(nRow, i);
		strType = m_ctrList[0].GetItemText(nRow, i + 5);
		if (_wtoi(strType) == 0)
			continue;

		nIdx[i - 6] = _wtoi(strIdx);
		nType[i - 6] = _wtoi(strType);
		strName[i - 6] = m_ctrList[0].GetItemText(nRow, i-5);
		if(nIdx[i-6] == 0)
			break;
		
		nTabCount++;
	}

	//CView_PCE_rst_RelayDlg*	pTab_Relay = Create_Tab_Relay();
	//m_pTabGroup->SetTabView(0, pTab_Relay, PCE_STUDY_EQUIP_RELAY);

	//CView_PCE_rst_RCDlg*	pTab_RC = Create_Tab_RC();
	//m_pTabGroup->SetTabView(1, pTab_RC, PCE_STUDY_EQUIP_RC);

	//CView_PCE_rst_EFIDlg*	pTab_EFI = Create_Tab_EFI();
	//m_pTabGroup->SetTabView(2, pTab_EFI, PCE_STUDY_EQUIP_EFI);

	//return;

	CString strTabName;
	int nRC_Count = 1;
	for (int i = 0; i < 5; i++)
	{
		if(i >= nTabCount)
			break;

		if (nType[i] == 0)
			continue;

		if (nType[i] >= 1 && nType[i] <= 2)
		{
			if (nType[i] == 1)
			{
				strTabName.Format(_T("CB:%s"), strName[i]);
				m_pTabGroup->AddTabInfor((LPWSTR)(LPCTSTR)strTabName, NULL);

				CView_PCE_rst_RelayDlg*	pTab_Relay = Create_Tab_Relay();
				pTab_Relay->m_nIndex = nIdx[i];
				pTab_Relay->m_nEquipType = nType[i];
				pTab_Relay->Update_Data();
				m_pTabGroup->SetTabView(i + 1, pTab_Relay, PCE_STUDY_EQUIP_RELAY);

			}
			else if (nType[i] == 2)
			{
				strTabName.Format(_T("R%d:%s"), nRC_Count,strName[i]);
				m_pTabGroup->AddTabInfor((LPWSTR)(LPCTSTR)strTabName, NULL);

				CView_PCE_rst_RCDlg*	pTab_RC = Create_Tab_RC();
				pTab_RC->m_nIndex = nIdx[i];
				m_pTabGroup->SetTabView(i+1, pTab_RC, PCE_STUDY_EQUIP_RC);
				pTab_RC->Update_Data();
				nRC_Count++;
			}
			
		}
		else if (nType[i] == 3)
		{
			strTabName.Format(_T("EFI:%s"), strName[i]);
			m_pTabGroup->AddTabInfor((LPWSTR)(LPCTSTR)strTabName, NULL);

			CView_PCE_rst_EFIDlg*	pTab_EFI = Create_Tab_EFI();
			pTab_EFI->m_nIndex = nIdx[i];
			m_pTabGroup->SetTabView(i + 1, pTab_EFI, PCE_STUDY_EQUIP_EFI);
			pTab_EFI->Update_Data();
			//nRC_Count++;
		}
		else //////////// 고객 type =4
		{
			strTabName.Format(_T("%s"), strName[i]);
			m_pTabGroup->AddTabInfor((LPWSTR)(LPCTSTR)strTabName, NULL);

			CView_PCE_rst_CUSDlg*	pTab_CUS = Create_Tab_CUS();
			pTab_CUS->m_nIndex = nIdx[i];
			pTab_CUS->m_nType = nType[i];
			m_pTabGroup->SetTabView(i + 1, pTab_CUS, nType[i]);
			pTab_CUS->Update_Data();
			
		}
	}

	m_pTabGroup->SetTabFocus();


	m_ctrBtn_Check[2].EnableWindow(TRUE);
	m_ctrBtn_Check[2].ShowWindow(SW_SHOW);

	m_ctrBtn_Check[11].EnableWindow(TRUE);
	m_ctrBtn_Check[11].ShowWindow(SW_SHOW);

	if (nTabCount > 1)
	{
		m_ctrBtn_Check[3].SetWindowText(_T("R1 - Fast"));
		m_ctrBtn_Check[3].EnableWindow(TRUE);
		m_ctrBtn_Check[3].ShowWindow(SW_SHOW);

		m_ctrBtn_Check[12].SetWindowText(_T("R1 - Fast"));
		m_ctrBtn_Check[12].EnableWindow(TRUE);
		m_ctrBtn_Check[12].ShowWindow(SW_SHOW);
		
		if (nType[1] == 3)
		{
			m_ctrBtn_Check[3].SetWindowText(_T("EFI"));
			m_ctrBtn_Check[12].SetWindowText(_T("EFI"));
		}
		else if (nType[1] == 4)
		{
			m_ctrBtn_Check[3].SetWindowText(_T("Customer"));
			m_ctrBtn_Check[12].SetWindowText(_T("Customer"));
		}
		else if (nType[1] == 5)
		{
			m_ctrBtn_Check[3].SetWindowText(_T("GEN"));
			m_ctrBtn_Check[12].SetWindowText(_T("GEN"));
		}
		else
		{
			m_ctrBtn_Check[4].EnableWindow(TRUE);
			m_ctrBtn_Check[4].ShowWindow(SW_SHOW);
			m_ctrBtn_Check[13].EnableWindow(TRUE);
			m_ctrBtn_Check[13].ShowWindow(SW_SHOW);
		}
	}

	if (nTabCount > 2)
	{
		m_ctrBtn_Check[5].SetWindowText(_T("R2 - Fast"));
		m_ctrBtn_Check[5].EnableWindow(TRUE);
		m_ctrBtn_Check[5].ShowWindow(SW_SHOW);

		m_ctrBtn_Check[14].SetWindowText(_T("R2 - Fast"));
		m_ctrBtn_Check[14].EnableWindow(TRUE);
		m_ctrBtn_Check[14].ShowWindow(SW_SHOW);

		
		if (nType[2] == 3)
		{
			m_ctrBtn_Check[5].SetWindowText(_T("EFI"));
			m_ctrBtn_Check[14].SetWindowText(_T("EFI"));
		}
		else if (nType[2] == 4)
		{
			m_ctrBtn_Check[5].SetWindowText(_T("Customer"));
			m_ctrBtn_Check[14].SetWindowText(_T("Customer"));
		}
		else if (nType[2] == 5)
		{
			m_ctrBtn_Check[5].SetWindowText(_T("GEN"));
			m_ctrBtn_Check[14].SetWindowText(_T("GEN"));
		}
		else
		{
			m_ctrBtn_Check[6].EnableWindow(TRUE);
			m_ctrBtn_Check[6].ShowWindow(SW_SHOW);
			m_ctrBtn_Check[15].EnableWindow(TRUE);
			m_ctrBtn_Check[15].ShowWindow(SW_SHOW);
		}
	}
	if (nTabCount > 3)
	{
		m_ctrBtn_Check[7].SetWindowText(_T("R3 - Fast"));
		m_ctrBtn_Check[7].EnableWindow(TRUE);
		m_ctrBtn_Check[7].ShowWindow(SW_SHOW);

		m_ctrBtn_Check[16].SetWindowText(_T("R3 - Fast"));
		m_ctrBtn_Check[16].EnableWindow(TRUE);
		m_ctrBtn_Check[16].ShowWindow(SW_SHOW);

		
		if (nType[3] == 3)
		{
			m_ctrBtn_Check[7].SetWindowText(_T("EFI"));
			m_ctrBtn_Check[16].SetWindowText(_T("EFI"));
		}
		else if (nType[3] == 4)
		{
			m_ctrBtn_Check[7].SetWindowText(_T("Customer"));
			m_ctrBtn_Check[16].SetWindowText(_T("Customer"));
		}
		else if (nType[3] == 5)
		{
			m_ctrBtn_Check[7].SetWindowText(_T("GEN"));
			m_ctrBtn_Check[16].SetWindowText(_T("GEN"));
		}
		else
		{
			m_ctrBtn_Check[8].EnableWindow(TRUE);
			m_ctrBtn_Check[8].ShowWindow(SW_SHOW);
			m_ctrBtn_Check[17].EnableWindow(TRUE);
			m_ctrBtn_Check[17].ShowWindow(SW_SHOW);
		}
	}

	if (nTabCount > 4)
	{
		m_ctrBtn_Check[9].SetWindowText(_T("R4 - Fast"));
		m_ctrBtn_Check[9].EnableWindow(TRUE);
		m_ctrBtn_Check[9].ShowWindow(SW_SHOW);

		m_ctrBtn_Check[18].SetWindowText(_T("R4 - Fast"));
		m_ctrBtn_Check[18].EnableWindow(TRUE);
		m_ctrBtn_Check[18].ShowWindow(SW_SHOW);

		
		if (nType[4] == 3)
		{
			m_ctrBtn_Check[9].SetWindowText(_T("EFI"));
			m_ctrBtn_Check[18].SetWindowText(_T("EFI"));
		}
		else if (nType[4] == 4)
		{
			m_ctrBtn_Check[9].SetWindowText(_T("Customer"));
			m_ctrBtn_Check[18].SetWindowText(_T("Customer"));
		}
		else if (nType[4] == 5)
		{
			m_ctrBtn_Check[9].SetWindowText(_T("GEN"));
			m_ctrBtn_Check[18].SetWindowText(_T("GEN"));
		}
		else
		{
			m_ctrBtn_Check[10].EnableWindow(TRUE);
			m_ctrBtn_Check[10].ShowWindow(SW_SHOW);
			m_ctrBtn_Check[19].EnableWindow(TRUE);
			m_ctrBtn_Check[19].ShowWindow(SW_SHOW);
		}
	}

	RedrawWindow(m_rectGraph[0]);
	RedrawWindow(m_rectGraph[1]);
}

void CView_PCE_rst::OnEditCtrl_1_EN_Change()
{
	//if (m_ctrBtn_Radio[0].GetCheckButton() == CHECKBOX_CHECKED)
	//{
	//	CString strMin, strMax;
	//	GetDlgItemText(ID_APP_PCE_EDIT_1, strMin);
	//	GetDlgItemText(ID_APP_PCE_EDIT_2, strMax);

	//	m_dAmp_Range[0] = _wtof(strMin);
	//	m_dAmp_Range[1] = _wtof(strMax);

	//	//RedrawWindow(m_rectGraph[3]);
	//}
}

void CView_PCE_rst::OnEditCtrl_1_EN_Killfocus()
{
	if (m_ctrBtn_Radio[0].GetCheckButton() == CHECKBOX_CHECKED)
	{
		CString strMin, strMax;
		GetDlgItemText(ID_APP_PCE_EDIT_1, strMin);
		GetDlgItemText(ID_APP_PCE_EDIT_2, strMax);

		double dMin = _wtof(strMin);
		double dMax = _wtof(strMax);
		if (dMin < 0)
		{
			AfxMessageBox(_T("0 보다 작을 수 없습니다."));
			strMin.Format(_T("%g"), m_dAmp_Range[0]);
			return;
		}
		if(dMax < dMin)
		{
			AfxMessageBox(_T("MAX 값보다 클 수 없습니다."));
			strMin.Format(_T("%g"), m_dAmp_Range[0]);
			return;
		}

		m_dAmp_Range[0] = _wtof(strMin);
		m_dAmp_Range[1] = _wtof(strMax);

		Update_Data_PCE();
		RedrawWindow(m_rectGraph[4]);
	}
}

void CView_PCE_rst::OnEditCtrl_2_EN_Killfocus()
{
	if (m_ctrBtn_Radio[0].GetCheckButton() == CHECKBOX_CHECKED)
	{
		CString strMin, strMax;
		GetDlgItemText(ID_APP_PCE_EDIT_1, strMin);
		GetDlgItemText(ID_APP_PCE_EDIT_2, strMax);

		double dMin = _wtof(strMin);
		double dMax = _wtof(strMax);
		if (dMax  > 10000)
		{
			AfxMessageBox(_T("10000 보다 클 수 없습니다."));
			strMin.Format(_T("%g"), m_dAmp_Range[0]);
			return;
		}
		if (dMax < dMin)
		{
			AfxMessageBox(_T("MIN 값보다 작을 수 없습니다."));
			strMin.Format(_T("%g"), m_dAmp_Range[0]);
			return;
		}

		m_dAmp_Range[0] = _wtof(strMin);
		m_dAmp_Range[1] = _wtof(strMax);

		Update_Data_PCE();
		RedrawWindow(m_rectGraph[4]);
	}
}

void CView_PCE_rst::OnEditCtrl_3_EN_Killfocus()
{
	if (m_ctrBtn_Radio[1].GetCheckButton() == CHECKBOX_CHECKED)
	{
		CString strMin, strMax;
		GetDlgItemText(ID_APP_PCE_EDIT_3, strMin);
		GetDlgItemText(ID_APP_PCE_EDIT_4, strMax);

		double dMin = _wtof(strMin);
		double dMax = _wtof(strMax);
		if (dMin < 0)
		{
			AfxMessageBox(_T("0 보다 작을 수 없습니다."));
			strMin.Format(_T("%g"), m_dAmp_Range[0]);
			return;
		}
		if (dMax < dMin)
		{
			AfxMessageBox(_T("MAX 값보다 클 수 없습니다."));
			strMin.Format(_T("%g"), m_dAmp_Range[0]);
			return;
		}

		m_dAmp_Range[0] = _wtof(strMin);
		m_dAmp_Range[1] = _wtof(strMax);

		Update_Data_PCE();
		RedrawWindow(m_rectGraph[4]);
	}
}

void CView_PCE_rst::OnEditCtrl_4_EN_Killfocus()
{
	if (m_ctrBtn_Radio[1].GetCheckButton() == CHECKBOX_CHECKED)
	{
		CString strMin, strMax;
		GetDlgItemText(ID_APP_PCE_EDIT_3, strMin);
		GetDlgItemText(ID_APP_PCE_EDIT_4, strMax);

		double dMin = _wtof(strMin);
		double dMax = _wtof(strMax);
		if (dMax > 10000)
		{
			AfxMessageBox(_T("10000 보다 클 수 없습니다."));
			strMin.Format(_T("%g"), m_dAmp_Range[0]);
			return;
		}
		if (dMax < dMin)
		{
			AfxMessageBox(_T("MIN 값보다 작을 수 없습니다."));
			strMin.Format(_T("%g"), m_dAmp_Range[0]);
			return;
		}

		m_dAmp_Range[0] = _wtof(strMin);
		m_dAmp_Range[1] = _wtof(strMax);

		Update_Data_PCE();
		RedrawWindow(m_rectGraph[4]);
	}
}

void CView_PCE_rst::recv_Appl(int nAppl)
{
	if (!m_bTimer)
		return;

	m_nRecvAppl_ID = nAppl;

	if (m_nCompAppl_ID == nAppl)
	{
		m_bTimer = FALSE;
	}
}

void CView_PCE_rst::recv_Init()
{
	m_bTimer = FALSE;
	KillTimer(1);
}

void CView_PCE_rst::OnTimer(UINT_PTR nIDEvent)
{
	if (!m_bTimer)
	{
		KillTimer(nIDEvent);
		if (nIDEvent == 1)
		{
			Sleep(500);
			
			if (m_nCompAppl_ID == 12)
			{
				int nMode = GETVALUE(int,_T("PCEOPT_DYN_UIN"), _T("PCEOPT_RUN_MODE"), 1);
				if (nMode == 1)
				{
					Update_List_Path();
				}
				else
				{
					Update_Data_PCE();
				}
			
			}
		}
		else if (nIDEvent == 2)
		{
		

		}
		
		RedrawWindow();
	}

	CView_Base::OnTimer(nIDEvent);
}


void CView_PCE_rst::Update_List_Path()
{
	m_nSelect_Path = -1;
	m_pTabGroup->RemoveAllTab();
	m_ctrList[0].DeleteAllItems();

	int nPath_Count = theAppDataMng->GetTableRealCount(_T("PRDEPATH_DYN_PCEO"));

	int nPathID,nPrevID = 0;
	int nOrder , nIdx ,nType;
	CString strName, strIdx, strType,strID;
	for (int i = 1; i <= nPath_Count; i++)
	{
		nPathID = GETVALUE(int, _T("PRDEPATH_DYN_PCEO"), _T("PRDEPATH_ID"), i);

		if (nPathID == 0)
		{
			break;
		}

		nOrder = GETVALUE(int, _T("PRDEPATH_DYN_PCEO"), _T("PRDEPATH_ORDER"), i);
		nIdx = GETVALUE(int, _T("PRDEPATH_DYN_PCEO"), _T("PRDEPATH_II_INDEX"), i);
		nType = GETVALUE(int, _T("PRDEPATH_DYN_PCEO"), _T("PRDEPATH_LINK_TYPE"), i);

		if (nType == 1 || nType == 2 || nType == 3)
		{
			strName = CA2W(GETSTRING("CBSW_STA", "CBSW_NM", nIdx)).m_psz;
		}
		else if(nType == 4)
		{
			strName = CA2W(GETSTRING("HVCUS_STA", "HVCUS_NM", nIdx)).m_psz;
		}
		else  ///////////////// GEN
		{
			strName = CA2W(GETSTRING("GEN_STA", "GEN_NM", nIdx)).m_psz;
		}
		
		strIdx.Format(_T("%d"), nIdx);
		strType.Format(_T("%d"), nType);

		if (nOrder == 1)
		{
			strID.Format(_T("%d"), nPathID);
			m_ctrList[0].InsertItem(nPathID - 1, strID, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		}
		m_ctrList[0].SetItemText(nPathID - 1, nOrder, strName, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(nPathID - 1, nOrder+5, strIdx, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		m_ctrList[0].SetItemText(nPathID - 1, nOrder+10, strType, RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
		
	}
}

void CView_PCE_rst::Update_Data_PCE()
{
	int nCount = m_pTabGroup->GetTabCount();

	int nType, nEqType, nIndex;

	int nPhase = (m_ctrBtn_Radio[0].GetCheckButton() == CHECKBOX_CHECKED ? 0 : 1);

	int nCheckBtnIdx[2][10] = { {2,0,3,4,5,6,7,8,9,10},{11,0,12,13,14,15,16,17,18,19} };///////////////////// 컨트롤 인덱스 바뀌면 같이 바꿔야된다
	int nCheckIdx;
	CView_PCE_rst_RelayDlg* pRelay;
	CView_PCE_rst_RCDlg*	pRC;
	CView_PCE_rst_EFIDlg*	pEFI;
	CView_PCE_rst_CUSDlg*	pCUS;

	Clear_TCCurveData();

	for (int i = 0; i < nCount; i++)
	{
		nType = m_pTabGroup->GetTabType(i);
		if (nType == PCE_STUDY_EQUIP_RELAY)
		{

			pRelay = (CView_PCE_rst_RelayDlg*)m_pTabGroup->GetTabWnd(i);
			pRelay->Update_Data();
			nEqType = pRelay->GetData_EqType();
			nIndex = pRelay->GetData_Idx();

			nCheckIdx = nCheckBtnIdx[0][i * 2];
			if (m_ctrBtn_Check[nCheckIdx].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_Relay(i, nIndex, nPhase, 0);
			}

			nCheckIdx = nCheckBtnIdx[1][i * 2];
			if (m_ctrBtn_Check[nCheckIdx].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_Relay(i, nIndex, nPhase, 2);
			}


		}
		else if (nType == PCE_STUDY_EQUIP_RC)
		{
			pRC = (CView_PCE_rst_RCDlg*)m_pTabGroup->GetTabWnd(i);
			pRC->Update_Data();
			nIndex = pRC->GetData_Idx();

			nCheckIdx = nCheckBtnIdx[0][i * 2];
			if (m_ctrBtn_Check[nCheckIdx].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_RC(i, nIndex, nPhase, 0, 0);
			}

			if (m_ctrBtn_Check[nCheckIdx + 1].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_RC(i, nIndex, nPhase, 1, 1);
			}

			nCheckIdx = nCheckBtnIdx[1][i * 2];
			if (m_ctrBtn_Check[nCheckIdx].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_RC(i, nIndex, nPhase, 0, 2);
			}

			if (m_ctrBtn_Check[nCheckIdx + 1].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_RC(i, nIndex, nPhase, 1, 3);
			}
		}
		else if(nType == PCE_STUDY_EQUIP_EFI)
		{
			pEFI = (CView_PCE_rst_EFIDlg*)m_pTabGroup->GetTabWnd(i);
			pEFI->Update_Data();
			nIndex = pEFI->GetData_Idx();

			nCheckIdx = nCheckBtnIdx[0][i * 2];
			if (m_ctrBtn_Check[nCheckIdx].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_RC(i, nIndex, nPhase, 1, 0);
			}

		/*	if (m_ctrBtn_Check[nCheckIdx + 1].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_RC(i, nIndex, nPhase, 1, 1);
			}*/

			nCheckIdx = nCheckBtnIdx[1][i * 2];
			if (m_ctrBtn_Check[nCheckIdx].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_RC(i, nIndex, nPhase, 1, 2);
			}
/*
			if (m_ctrBtn_Check[nCheckIdx + 1].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_RC(i, nIndex, nPhase, 1, 3);
			}*/
		}
		else if (nType == PCE_STUDY_EQUIP_CUSTOMER || nType == PCE_STUDY_EQUIP_GEN)
		{

			pCUS = (CView_PCE_rst_CUSDlg*)m_pTabGroup->GetTabWnd(i);
			pCUS->Update_Data();
		//	nEqType = pRelay->GetData_EqType();
			nIndex = pCUS->GetData_Idx();

			nCheckIdx = nCheckBtnIdx[0][i * 2];
			if (m_ctrBtn_Check[nCheckIdx].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_Relay(i, nIndex, nPhase, 0);
			}

			nCheckIdx = nCheckBtnIdx[1][i * 2];
			if (m_ctrBtn_Check[nCheckIdx].GetCheckButton() == CHECKBOX_CHECKED)
			{
				Update_TCCurve_Relay(i, nIndex, nPhase, 2);
			}
					   
		}


	}
	

	RedrawWindow(m_rectGraph[4]);
}

void CView_PCE_rst::Update_TCCurve_Relay(int nTabIdx, int nIdx, int nPhase, int nSetType)
{
	int nType = m_pTabGroup->GetTabType(nTabIdx);

	int nPRDE_idx;
	if (nType == PCE_STUDY_EQUIP_CUSTOMER)
	{
		nPRDE_idx = GETVALUE(int, _T("HVCUS_STA"), _T("HVCUS_II_PRDE"), nIdx);
	}
	else if (nType == PCE_STUDY_EQUIP_GEN)
	{
		nPRDE_idx = GETVALUE(int, _T("GEN_STA"), _T("GEN_II_PRDE"), nIdx);
	}
	else
	{
		nPRDE_idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_PRDE"), nIdx);
	}
	if (nPRDE_idx <= 0)
		return;

	int nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nPRDE_idx);
	if (nTCCSET_OCRF_Idx <= 0)
		return;

	int nCTR;
	double dTms, dMrt;
	double dTccSet[4];
	double dSet_Pickup[2];
	
	
	if (nSetType == 0)
	{
		if (nPhase == PCE_STUDY_MODE_PHASE)
		{
			nCTR = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_CTR"), nPRDE_idx);
			dTms = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_TMS"), nPRDE_idx);
			dMrt = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_MRT"), nPRDE_idx);
			dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_Pickup_C"), nPRDE_idx) / nCTR;
			dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_IIC"), nPRDE_idx) / nCTR;
		}
		else ////////////// OCGR
		{
			nCTR = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_CTR"), nPRDE_idx);
			dTms = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_TMS"), nPRDE_idx);
			dMrt = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_MRT"), nPRDE_idx);
			dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_Pickup_C"), nPRDE_idx) / nCTR;
			dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_IIC"), nPRDE_idx) / nCTR;
		}
	}
	else
	{
		if (nPhase == PCE_STUDY_MODE_PHASE)
		{
			nCTR = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_CTR"), nPRDE_idx);
		//	dTms = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_TMS"), nPRDE_idx);
			
		//	dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_Pickup_C"), nPRDE_idx) / nCTR;
		//	dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_IIC"), nPRDE_idx) / nCTR;

			dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_REC"), nPRDE_idx) / nCTR;
			dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_IIC_REC"), nPRDE_idx) / nCTR;
			dTms = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_F_TMS"), nPRDE_idx);
			dMrt = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_F_MRT"), nPRDE_idx);
		}
		else ////////////// OCGR
		{
			nCTR = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_CTR"), nPRDE_idx);
			dMrt = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_MRT"), nPRDE_idx);
		
			dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_REC"), nPRDE_idx) / nCTR;
			dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_IIC_REC"), nPRDE_idx) / nCTR;
			dTms = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_F_TMS"), nPRDE_idx);
			dMrt = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_F_MRT"), nPRDE_idx);
		}
	}
	

	
	dTccSet[0] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_A"), nTCCSET_OCRF_Idx);
	dTccSet[1] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_B"), nTCCSET_OCRF_Idx);
	dTccSet[2] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_C"), nTCCSET_OCRF_Idx);
	dTccSet[3] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_D"), nTCCSET_OCRF_Idx);

	double dPickup[2];
	double dSDelay;
	
	m_TCCurve_Data[nTabIdx][nSetType].Init();
//	m_TCCurve_Data[nTabIdx][2].Init();

	double dSValue = dSet_Pickup[1] * nCTR;

	for (int i = int(m_dAmp_Range[0]); i <= m_dAmp_Range[1]; i++)
	{
		//pick_up(i) = x(i) / (app.CB_OCR_tap_EF.Value*app.CB_OCR_CTr_EF.Value);
		if (i > dSValue && dSValue != 0)
		{
			dSDelay = m_dOCB_SDelay;
		}
		else
		{
			dPickup[0] = i / (dSet_Pickup[0] * nCTR);
			//pick_up1(i) = pick_up(i) ^ b;
			dPickup[1] = pow(dPickup[0], dTccSet[1]);
			//y_cb_ocr(i) = max(tms * (a / (pick_up1(i) + c) + d), mrt);
			dSDelay = max(dTms * (dTccSet[0] / (dPickup[1] + dTccSet[2]) + dTccSet[3]), dMrt);
		}

		if (m_nCurve_Select == i)
		{
			if (m_dCurve_Y_MAX < dSDelay)
				m_dCurve_Y_MAX = dSDelay;
		}
		
		m_TCCurve_Data[nTabIdx][nSetType].m_Array_X_Value.Add(i);
		m_TCCurve_Data[nTabIdx][nSetType].m_Array_Y_Value.Add(dSDelay);
	}
}

void CView_PCE_rst::Update_TCCurve_RC(int nTabIdx, int nIdx, int nPhase, int nFast, int nSetType)
{
	int nPRDE_idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_PRDE"), nIdx);

	if (nPRDE_idx <= 0)
		return;

	int nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nPRDE_idx);
	if (nTCCSET_OCRF_Idx <= 0)
		return;

	double dTms, dMrt;
	double dTccSet[4];
	double dSet_Pickup[2];


	if (nSetType < 2)
	{
		if (nPhase == PCE_STUDY_MODE_PHASE)
		{
			if (nFast == 1)
			{
				nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRD_II_TCCSET"), nPRDE_idx);
				dTms = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRD_TMS"), nPRDE_idx);
				dMrt = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRD_MRT"), nPRDE_idx);
			}
			else
			{
				nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nPRDE_idx);
				dTms = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_TMS"), nPRDE_idx);
				dMrt = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_MRT"), nPRDE_idx);
			}
			dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_Pickup_C"), nPRDE_idx);
			dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_IIC"), nPRDE_idx);
		}
		else ////////////// OCGR
		{
			if (nFast == 1)
			{
				nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRD_II_TCCSET"), nPRDE_idx);
				dTms = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_TMS"), nPRDE_idx);
				dMrt = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_MRT"), nPRDE_idx);
			}
			else
			{
				nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nPRDE_idx);
				dTms = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_TMS"), nPRDE_idx);
				dMrt = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_MRT"), nPRDE_idx);
			}


			dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_Pickup_C"), nPRDE_idx);
			dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_IIC"), nPRDE_idx);
		}
	}
	else
	{
		if (nPhase == PCE_STUDY_MODE_PHASE)
		{
			if (nFast == 1)
			{
				nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRD_II_TCCSET"), nPRDE_idx);
				dTms = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_D_TMS"), nPRDE_idx);
				dMrt = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_D_MRT"), nPRDE_idx);
			}
			else
			{
				nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nPRDE_idx);
				dTms = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_F_TMS"), nPRDE_idx);
				dMrt = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_F_MRT"), nPRDE_idx);
			}
			dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_REC"), nPRDE_idx);
			dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_IIC_REC"), nPRDE_idx);
		}
		else ////////////// OCGR
		{
			if (nFast == 1)
			{
				nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRD_II_TCCSET"), nPRDE_idx);
				dTms = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_D_TMS"), nPRDE_idx);
				dMrt = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_D_MRT"), nPRDE_idx);
			}
			else
			{
				nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nPRDE_idx);
				dTms = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_F_TMS"), nPRDE_idx);
				dMrt = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_F_MRT"), nPRDE_idx);
			}


			dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_Pickup_C_REC"), nPRDE_idx);
			dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_IIC_REC"), nPRDE_idx);
		}
	}
	


	dTccSet[0] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_A"), nTCCSET_OCRF_Idx);
	dTccSet[1] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_B"), nTCCSET_OCRF_Idx);
	dTccSet[2] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_C"), nTCCSET_OCRF_Idx);
	dTccSet[3] = GETVALUE(double, _T("TCCSET_DYN_UIN"), _T("TCCSET_D"), nTCCSET_OCRF_Idx);

	double dPickup[2];
	double dSDelay;

	m_TCCurve_Data[nTabIdx][nSetType].Init();
	//	m_TCCurve_Data[nTabIdx][nSetType].Init();

	double dSValue = dSet_Pickup[1];
	double dStart_Value = max(dSet_Pickup[0], m_dAmp_Range[0]);

	for (int i = int(dStart_Value); i <= m_dAmp_Range[1]; i++)
	{

		if( i < dStart_Value )
			continue;

		//pick_up(i) = x(i) / (app.CB_OCR_tap_EF.Value*app.CB_OCR_CTr_EF.Value);
		if (i > dSValue && dSValue != 0)
		{
			dSDelay = m_dOCB_SDelay;
		}
		else
		{
			dPickup[0] = i / (dSet_Pickup[0]);
			//pick_up1(i) = pick_up(i) ^ b;
			dPickup[1] = pow(dPickup[0], dTccSet[1]);
			//y_cb_ocr(i) = max(tms * (a / (pick_up1(i) + c) + d), mrt);
			dSDelay = max(dTms * (dTccSet[0] / (dPickup[1] + dTccSet[2]) + dTccSet[3]), dMrt);
		}

		if (m_nCurve_Select == i)
		{
			if (m_dCurve_Y_MAX < dSDelay)
				m_dCurve_Y_MAX = dSDelay;
		}

		m_TCCurve_Data[nTabIdx][nSetType].m_Array_X_Value.Add(i);
		m_TCCurve_Data[nTabIdx][nSetType].m_Array_Y_Value.Add(dSDelay);
	}

}

void CView_PCE_rst::Clear_Data()
{
	m_ctrList[0].DeleteAllItems();
	m_pTabGroup->RemoveAllTab();

	RedrawWindow();
}

LRESULT CView_PCE_rst::OnTabMsg(WPARAM wp, LPARAM lp)
{

	Update_Data_PCE();

	return 0;
}

int CView_PCE_rst::GetSelectCurve(CPoint pt)
{
	//x = int(rect.left + abs(dLog_X - dX_Gap) * dTabx);

	if (m_nCurve_X_Base > 0 && m_dCurve_X_Gap > 0 && m_dCurve_X_Gap)
	{
		double dLog_X = (pt.x - m_nCurve_X_Base) / m_dCurve_X_Tap + m_dCurve_X_Gap;

		int nAmp = int(pow(10., dLog_X));


		return nAmp;
	}
	

	return -1;
}



void CView_PCE_rst::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect  _rect;
	_rect.left = m_rectGraph[4].left + 90;
	_rect.top = m_rectGraph[4].top + 25;
	_rect.right = m_rectGraph[4].right - ( 20);
	_rect.bottom = m_rectGraph[4].bottom - ( 95);
	if (_rect.PtInRect(point))
	{
		/////////////////// 그래프 데이터 있는 지 확인
		m_ptSelect = point;
	//	m_dCurve_Y_MAX = -1;
		m_nCurve_Select = GetSelectCurve(point);
		Update_Data_PCE();

		RedrawWindow(m_rectGraph[4]);
	}

	CView_Base::OnLButtonUp(nFlags, point);
}
