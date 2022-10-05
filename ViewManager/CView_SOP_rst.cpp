#include "pch.h"
#include "CView_SOP_rst.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"
#include "../DataManager/CDataManager.h"
#include "resource.h"

CView_SOP_rst::CView_SOP_rst()
{

}

CView_SOP_rst::~CView_SOP_rst()
{

}

BEGIN_MESSAGE_MAP(CView_SOP_rst, CView_Base)
	ON_BN_CLICKED(ID_APP_SOP_BTN_1, &CView_SOP_rst::OnControlbutton_click_Run_1)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CView_SOP_rst::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	Create_Combobox();
	Create_DateTimeCtrl();

	Create_Btn();
	Create_TreeCtrl();
	Create_ListCtrl();

}
void CView_SOP_rst::InitData()
{
	m_ctrCombo[0].ResetContent();

	CString strData;
	for (int i = 0; i < 24; i++)
	{
		strData.Format(_T("%d"), i);
		m_ctrCombo[0].AddString(strData);
	}
	m_ctrCombo[0].SetCurSel(0);

	Insert_TreeData();
}

void CView_SOP_rst::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);

	OnPrepareDC(&dc);

	Graphics						graphics(dc.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
	
	CRect r;
	GetClientRect(&r);


	//CSB_Manager* pSBMng = CSB_Manager::Instance();
	//pSBMng->test_Draw(graphics, r);
	Redraw_Ctrl();
}

void CView_SOP_rst::Redraw_Ctrl()
{
	//m_ctrCombo[0].SetFocus();

	m_ctrCombo[0].RedrawWindow();

	//m_ctrTree.SetFocus();
}

BOOL CView_SOP_rst::OnEraseBkgnd(CDC* pDC)
{
	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	CView_Base::OnEraseBkgnd(pDC);

	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[0]);
//	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[1]);
//	pViewMng->DrawArea_List(pDC, graphics, m_rectBack[2]);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectSetting[0], FALSE);
	pViewMng->DrawArea_Base(pDC, graphics, m_rectSetting[1]);

	pViewMng->Draw_Split(pDC, graphics, m_rectSetting[0], DRAW_SPLIT_MODE_BOTTOM);
	pViewMng->Draw_Split(pDC, graphics, m_rectSetting[1], DRAW_SPLIT_MODE_TOP);

	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[0], _T("SOP 설정"), TRUE);
//	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[1], _T("솔루션"), TRUE);
//	pViewMng->DrawArea_Title(pDC, graphics, m_rectTitle[2], _T("조작 개폐기"), TRUE);

	return TRUE;
}




void CView_SOP_rst::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	m_rectBack[0].SetRect(_rect.left, _rect.top, _rect.left + 321, _rect.bottom);
	m_rectBack[1].SetRect(m_rectBack[0].right, _rect.top , _rect.right, _rect.top + 170);
	m_rectBack[2].SetRect(m_rectBack[0].right, m_rectBack[1].bottom, _rect.right, _rect.bottom);

	m_rectBack[0].right -= 5;

	m_rectBack[1].left += 5;
	m_rectBack[1].bottom -= 5;

	m_rectBack[2].left += 5;
	m_rectBack[2].top += 5;

	MoveSize_Setting();
	MoveSize_List();
}

void CView_SOP_rst::MoveSize_Setting()
{
	if (m_ctrBtn_Check[3].GetSafeHwnd() == NULL || m_ctrBtn[0].GetSafeHwnd() == NULL)							return;

	CRect rect = m_rectBack[0];
	
	m_rectTitle[0] = rect;
	m_rectTitle[0].right = m_rectTitle[0].left + 100;
	m_rectTitle[0].bottom = m_rectTitle[0].top + 30;

	m_rectSetting[0] = rect;
	m_rectSetting[0].top = m_rectSetting[0].top + 30;
	m_rectSetting[0].bottom = m_rectSetting[0].top + 116;

	m_rectSetting[1] = m_rectSetting[0];
	m_rectSetting[1].top = m_rectSetting[0].bottom + 30;
	m_rectSetting[1].bottom = m_rectBack[0].bottom ;
	///////////////////////////
	rect = m_rectSetting[0];
	rect.InflateRect(-8, -10);
	m_rectCtrl_Date[0] = rect;
	m_rectCtrl_Date[0].right = m_rectCtrl_Date[0].left + 120;
	m_rectCtrl_Date[0].bottom = m_rectCtrl_Date[0].top + 24;
	

	m_rectCtrl_Combobox[0] = m_rectCtrl_Date[0];
	m_rectCtrl_Combobox[0].left = m_rectCtrl_Date[0].right + 10;
	m_rectCtrl_Combobox[0].right = m_rectCtrl_Combobox[0].left + 50;
	m_ctrCombo[0].MoveWindow(m_rectCtrl_Combobox[0]);

	m_rectCtrl_Date[0].top += 1;
	m_rectCtrl_Date[0].bottom += 1;
	m_ctrDate[0].MoveWindow(m_rectCtrl_Date[0]);

	///////////////////
	rect = m_rectSetting[0];
	rect.InflateRect(-8, -8);
	m_rectCtrl_Check[0] = rect;
	m_rectCtrl_Check[0].right = m_rectCtrl_Check[0].left + 130; 
	m_rectCtrl_Check[0].bottom = m_rectCtrl_Check[0].top + 16;

	m_rectCtrl_Check[1] = m_rectCtrl_Check[0];
	m_rectCtrl_Check[1].top = m_rectCtrl_Check[0].bottom + 12;
	m_rectCtrl_Check[1].bottom = m_rectCtrl_Check[1].top + 16;

	m_rectCtrl_Check[2] = m_rectCtrl_Check[0];
	m_rectCtrl_Check[2].top = m_rectCtrl_Check[1].bottom + 12;
	m_rectCtrl_Check[2].bottom = m_rectCtrl_Check[2].top + 16;

	m_rectCtrl_Check[3] = m_rectCtrl_Check[0];
	m_rectCtrl_Check[3].top = m_rectCtrl_Check[2].bottom + 12;
	m_rectCtrl_Check[3].bottom = m_rectCtrl_Check[3].top + 16;

	m_rectCtrl_Btn[0] = rect;
	m_rectCtrl_Btn[0].left = m_rectCtrl_Btn[0].right - 87;
	m_rectCtrl_Btn[0].bottom = m_rectCtrl_Btn[0].top + 33;

	
	
	///////////////////////////////////////////////////////////////////////////////
	m_ctrBtn[0].MoveWindow(m_rectCtrl_Btn[0]);
	
	

	m_ctrBtn_Check[0].MoveWindow(m_rectCtrl_Check[0]);
	m_ctrBtn_Check[1].MoveWindow(m_rectCtrl_Check[1]);
	m_ctrBtn_Check[2].MoveWindow(m_rectCtrl_Check[2]);
	m_ctrBtn_Check[3].MoveWindow(m_rectCtrl_Check[3]);
	

	rect = m_rectSetting[1];
	rect.InflateRect(0, -2);
	m_ctrTree.MoveWindow(rect);

}

void CView_SOP_rst::MoveSize_List()
{
	if (m_ctrList[0].GetSafeHwnd() == NULL || m_ctrList[1].GetSafeHwnd() == NULL)							return;

	CRect rect = m_rectBack[1];

	m_rectTitle[1] = rect;
	m_rectTitle[1].right = m_rectTitle[1].left + 80;
	m_rectTitle[1].bottom = m_rectTitle[1].top + 30;

	m_rectCtrl_List[0] = m_rectBack[1];

	rect = m_rectBack[2];

	m_rectTitle[2] = rect;
	m_rectTitle[2].right = m_rectTitle[2].left + 130;
	m_rectTitle[2].bottom = m_rectTitle[2].top + 30;

	m_rectCtrl_List[1] = m_rectBack[2];
	
	rect = m_rectCtrl_List[0];
	rect.top += 30;
	rect.bottom -= 2;

	m_ctrList[0].MoveWindow(rect);

	rect = m_rectCtrl_List[1];
	rect.top += 30;
	rect.bottom -= 2;

	m_ctrList[1].MoveWindow(rect);

}


void	CView_SOP_rst::Create_ListCtrl()
{
	m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect[2];
	rect[0] = CRect(10, 50, 350, 500);
	m_ctrList[0].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER | LVS_SHOWSELALWAYS, rect[0], this, ID_APP_SOP_LIST_1);
	m_ctrList[0].InsertColumn(0, _T(""), HDF_LEFT, 40);
	m_ctrList[0].InsertColumn(1, _T("제어 대상"), HDF_LEFT, 392);
	m_ctrList[0].InsertColumn(2, _T("idx"), HDF_LEFT, 0);
	m_ctrList[0].InsertColumn(3, _T("dump"), HDF_LEFT, 0); ////// 스크롤바 21
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
	m_ctrList[1].Create(WS_CHILD | WS_EX_TOPMOST | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_SOP_LIST_1);
	m_ctrList[1].InsertColumn(0, _T(""), HDF_LEFT, 40);
	m_ctrList[1].InsertColumn(1, _T("제어 대상"), HDF_LEFT, 210);
	m_ctrList[1].InsertColumn(2, _T("제어 방식"), HDF_LEFT, 112);
	m_ctrList[1].InsertColumn(3, _T("신규 검토"), HDF_LEFT, 70); ////// 스크롤바 21
	m_ctrList[1].InsertColumn(4, _T("idx"), HDF_LEFT, 0);
	m_ctrList[1].InsertColumn(5, _T("dump"), HDF_LEFT, 0);
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

	m_ctrList[0].ShowWindow(SW_HIDE);
	m_ctrList[1].ShowWindow(SW_HIDE);
}

void	CView_SOP_rst::Create_Btn()
{
	m_rectCtrl_Btn[0] = CRect(10, 20, 90, 250);
	if (!m_ctrBtn[0].Create(_T(""), WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE | BS_OWNERDRAW, m_rectCtrl_Btn[0], this, ID_APP_SOP_BTN_1))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_ctrBtn[0].SetBitmapID(IDB_PCE_RUN_NOR, IDB_PCE_RUN_CLK, IDB_PCE_RUN_OVR);

	m_font_check.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	//////////////////////////////////////////// 표시결과
	CRect rect = CRect(10, 20, 90, 250);
	if (!m_ctrBtn_Check[0].Create(_T("현재최대"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_SOP_BTN_CHECK_1))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[1].Create(_T("현재최소"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_SOP_BTN_CHECK_2))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[2].Create(_T("제안최대"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_SOP_BTN_CHECK_3))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}

	if (!m_ctrBtn_Check[3].Create(_T("제안최소"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_OWNERDRAW
		, rect, this, ID_APP_SOP_BTN_CHECK_4))
	{
		AfxMessageBox(_T("Create PCE CheckBox Fail.\n"));
		return;
	}
	m_ctrBtn_Check[0].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
	m_ctrBtn_Check[1].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
	m_ctrBtn_Check[2].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);
	m_ctrBtn_Check[3].SetBitmapID(IDB_CHECK_UNCHECK, IDB_CHECK_CHECK, IDB_CHECK_DISABLE);

	m_ctrBtn_Check[0].m_pFont_Text = &m_font_check;
	m_ctrBtn_Check[1].m_pFont_Text = &m_font_check;
	m_ctrBtn_Check[2].m_pFont_Text = &m_font_check;
	m_ctrBtn_Check[3].m_pFont_Text = &m_font_check;

	m_ctrBtn_Check[0].m_colorBg = RGB(255, 255, 255);
	m_ctrBtn_Check[1].m_colorBg = RGB(255, 255, 255);
	m_ctrBtn_Check[2].m_colorBg = RGB(255, 255, 255);
	m_ctrBtn_Check[3].m_colorBg = RGB(255, 255, 255);


	m_ctrBtn_Check[0].SetCheckButton(CHECKBOX_CHECKED);
	m_ctrBtn_Check[1].SetCheckButton(CHECKBOX_CHECKED);
	m_ctrBtn_Check[2].SetCheckButton(CHECKBOX_CHECKED);
	m_ctrBtn_Check[3].SetCheckButton(CHECKBOX_CHECKED);
	

	m_ctrBtn_Check[0].ShowWindow(SW_HIDE);
	m_ctrBtn_Check[1].ShowWindow(SW_HIDE);
	m_ctrBtn_Check[2].ShowWindow(SW_HIDE);
	m_ctrBtn_Check[3].ShowWindow(SW_HIDE);
}

void	CView_SOP_rst::Create_TreeCtrl()
{
	m_rectCtrl_Tree = CRect(10, 20, 90, 250);
	if (!m_ctrTree.Create( WS_CHILD | WS_EX_TOPMOST | WS_VISIBLE 
		| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES | TVS_CHECKBOXES, m_rectCtrl_Tree[0], this, ID_APP_SOP_TREE_1))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create PDVR Button Fail.\n"));
		return;
	}
	m_ctrTree.SetFont(&m_font_check);
	
	
	
}

void CView_SOP_rst::Create_Combobox()
{
	m_font_Combobox.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	if (!m_ctrCombo[0].Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL
		, CRect(100, 100, 200, 200), this, ID_APP_SOP_COMBO_1))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}


	m_ctrCombo[0].SetTextFont(&m_font_Combobox);
	

	m_ctrCombo[0].SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	

	m_ctrCombo[0].SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);

	m_ctrCombo[0].SetTextStyle(DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	m_ctrCombo[0].SetDropDownHeight(10);
}

void CView_SOP_rst::Create_DateTimeCtrl()
{
	if (!m_ctrDate[0].Create(WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT,
		CRect(100, 100, 200, 200), this, ID_APP_SOP_DATE_1))
	{
		AfxMessageBox(_T("Create PCE ComboBox Fail.\n"));
		return;
	}

	
}


void CView_SOP_rst::recv_Appl(int nAppl)
{
	if (!m_bTimer)
		return;

	m_nRecvAppl_ID = nAppl;

	if (m_nCompAppl_ID == nAppl)
	{
		m_bTimer = FALSE;
	}
}

void CView_SOP_rst::recv_Init()
{
	m_bTimer = FALSE;
	KillTimer(1);
}

void CView_SOP_rst::OnControlbutton_click_Run_1()
{
	int nCount = theAppDataMng->GetTableMaxCount(_T("ss_sta"));
	for (int i = 1; i <= nCount; i++)
	{
		PUTDOUBLE2VALUE(_T("SS_DYN_UIN"), _T("SS_DNRFLAG"), i, (double)0);
	}

	nCount = theAppDataMng->GetTableMaxCount(_T("mtr_sta"));
	for (int i = 1; i <= nCount; i++)
	{
		PUTDOUBLE2VALUE(_T("MTR_DYN_UIN"), _T("MTR_SOP_FLAG"), i, (double)0);
	}

	if (m_bTimer)
		return;

	int nSS_Idx, nMTR_Idx;;
	HTREEITEM hRoot = m_ctrTree.GetRootItem();
	HTREEITEM hMTR;
	BOOL bCheck_SS, bCheck_MTR;
	BOOL bFind = FALSE;
	while (hRoot)
	{
		bCheck_SS = m_ctrTree.GetCheck(hRoot);
		if (!bCheck_SS)
		{
			hMTR = m_ctrTree.GetChildItem(hRoot);
			while (hMTR)
			{
				bCheck_MTR = m_ctrTree.GetCheck(hMTR);
				if (bCheck_MTR)
				{
					nMTR_Idx = (int)m_ctrTree.GetItemData(hMTR);
					PUTDOUBLE2VALUE(_T("MTR_DYN_UIN"), _T("MTR_SOP_FLAG"), nMTR_Idx, (double)1);
					bFind = TRUE;
				}
				hMTR = m_ctrTree.GetNextItem(hMTR, TVGN_NEXT);
			}
		}
		else
		{
			nSS_Idx = (int)m_ctrTree.GetItemData(hRoot);
			PUTDOUBLE2VALUE(_T("SS_DYN_UIN"), _T("SS_DNRFLAG"), nSS_Idx, (double)1);
			bFind = TRUE;
		}
		hRoot = m_ctrTree.GetNextItem(hRoot, TVGN_NEXT);
	}
	
	if (!bFind)
	{
		AfxMessageBox(_T("선택된 변전소 또는 MTR 이 없습니다."));
		return;
	}


	
	COleDateTime timeData[1];
	CString strTime[1];
	m_ctrDate[0].GetTime(timeData[0]);
	
	
	
	int nSel[1];
	nSel[0] = m_ctrCombo[0].GetCurSel();

	CString strHour[1];
	m_ctrCombo[0].GetLBText(nSel[0], strHour[0]);

	int nHour[2];
	nHour[0] = _wtoi(strHour[0]);

	strTime[0].Format(_T("%s%02d"), timeData[0].Format(_T("%Y%m%d")),nHour[0]);

	PUTDOUBLE2VALUE(_T("SOPOPT_DYN_UIN"), _T("SOPOPT_TARGET_LOAD"), 1, (double)_wtoi(strTime[0]));
	

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->Excute_Appl(_T("13"), GetVIewID());

	m_bTimer = TRUE;
	m_nCompAppl_ID = 13;
	SetTimer(1, 100, NULL);



}

void CView_SOP_rst::Insert_TreeData()
{
	m_ctrTree.DeleteAllItems();

	CDataManager* pDataMng = CDataManager::Instance();

	HTREEITEM hRoot;
	HTREEITEM hMTR = NULL;

	CStringArray Array_SS;
	CIntArray	Array_SS_Idx;
	CStringArray Array_MTR;
	CIntArray	Array_MTR_Idx;

	pDataMng->GetSSName_array(&Array_SS, &Array_SS_Idx);

	CString strSS,strMTR;
	int nSS_Idx, nMTR_Idx;
	for (int i = 0; i < Array_SS.GetSize(); i++)
	{
		strSS = Array_SS.GetAt(i);
		nSS_Idx = Array_SS_Idx.GetAt(i);
		hRoot = m_ctrTree.InsertItem(strSS);
		m_ctrTree.SetItemData(hRoot,(DWORD_PTR)nSS_Idx);

		Array_MTR.RemoveAll();
		Array_MTR_Idx.RemoveAll();
		pDataMng->GetMTRName_array(strSS, &Array_MTR, &Array_MTR_Idx);

		for (int k = 0; k < Array_MTR.GetSize(); k++)
		{
			strMTR = Array_MTR.GetAt(k);
			nMTR_Idx = Array_MTR_Idx.GetAt(k);

			hMTR = m_ctrTree.InsertItem(strMTR, hRoot);
			m_ctrTree.SetItemData(hMTR, (DWORD_PTR)nMTR_Idx);

		}
	}

	

	//m_ctrTree.GetItemData()
	if (hMTR)
	{
		for (int i = 0; i < 10; i++)
		{
			m_ctrTree.InsertItem(_T("DL 선로"), hMTR);
		}
	}
	
}

void CView_SOP_rst::OnTimer(UINT_PTR nIDEvent)
{
	if (!m_bTimer)
	{
		KillTimer(nIDEvent);
		if (nIDEvent == 1)
		{
			
		}

		RedrawWindow();
	}

	CView_Base::OnTimer(nIDEvent);
}
