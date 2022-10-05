// CDNDObj_KASIM_GENUNIT_TAP.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_GENUNIT_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDNDObj_KASIM_GENUNIT_TAP 대화 상자
IMPLEMENT_DYNAMIC(CDNDObj_KASIM_GENUNIT_TAP, CDialog)

CDNDObj_KASIM_GENUNIT_TAP::CDNDObj_KASIM_GENUNIT_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_GENUNIT_DLG, pParent)
{
	m_nGENERATEUINT_CSVID = 0;
	m_nGENUNIT_CSVID = 0;
	m_nGenUnitIndex = 9999;
}

CDNDObj_KASIM_GENUNIT_TAP::~CDNDObj_KASIM_GENUNIT_TAP()
{
}

void CDNDObj_KASIM_GENUNIT_TAP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrList);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_GENUNIT_DLG_COMBO1, m_ctrCombo1[0]);
}

BEGIN_MESSAGE_MAP(CDNDObj_KASIM_GENUNIT_TAP, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_BTN1, &CDNDObj_KASIM_GENUNIT_TAP::OnBnClickedDndobjectKasimGenunitDlgBtn1)
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_BTN2, &CDNDObj_KASIM_GENUNIT_TAP::OnBnClickedDndobjectKasimGenunitDlgBtn2)
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_BTN3, &CDNDObj_KASIM_GENUNIT_TAP::OnBnClickedDndobjectKasimGenunitDlgBtn3)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_BTN1, &CDNDObj_KASIM_GENUNIT_TAP::OnUpdateUI_Btn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_BTN2, &CDNDObj_KASIM_GENUNIT_TAP::OnUpdateUI_Btn2)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_BTN3, &CDNDObj_KASIM_GENUNIT_TAP::OnUpdateUI_Btn3)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDNDObj_KASIM_GENUNIT_TAP::OnNMDblclkList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CDNDObj_KASIM_GENUNIT_TAP::OnNMClickList1)
END_MESSAGE_MAP()
// CDNDObj_KASIM_GENUNIT_TAP 메시지 처리기

BOOL CDNDObj_KASIM_GENUNIT_TAP::OnInitDialog()
{
	CDialog::OnInitDialog();
	_wsetlocale(LC_ALL, _T("Korean"));

	m_ctrCombo1[0].AddString(_T("INF_GEN"));
	m_ctrCombo1[0].AddString(_T("DIESEL"));
	m_ctrCombo1[0].AddString(_T("ESS"));
	m_ctrCombo1[0].AddString(_T("WIND"));
	m_ctrCombo1[0].AddString(_T("PV"));
	m_ctrCombo1[0].AddString(_T("COMBINED"));	// 20210728 심재성 차장이 추가해줌 메일로 보냄
	m_ctrCombo1[0].AddString(_T("HYDRO"));		 // 20210728 심재성 차장이 추가해줌 메일로 보냄
	m_ctrCombo1[0].AddString(_T("FUEL"));		 // 20210728 심재성 차장이 추가해줌 메일로 보냄
	m_ctrCombo1[0].AddString(_T("WASTE"));		 // 20210728 심재성 차장이 추가해줌 메일로 보냄
	m_ctrCombo1[0].AddString(_T("ETC"));		 // 20210728 심재성 차장이 추가해줌 메일로 보냄

	m_ctrList.DeleteAllItems();
	DWORD style = m_ctrList.GetExtendedStyle();
	style |= (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList.SetExtendedStyle(style);
	m_ctrList.DeleteAllItems();
	LV_COLUMN														lvcolumn;
	wchar_t*														list[9] = { _T(""), _T("NO."), _T("고객명"), _T("고객MRID"), _T("전산화번호"), _T("고객전주명"), _T("고객번호"), _T("용량"), _T("Type") };
	int																width[9] = { 0,40, 100, 150, 90,70, 90, 50, 50 };

	for (int i = 0; i < 9; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_CENTER;
		lvcolumn.pszText = list[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = width[i];

		m_ctrList.InsertColumn(i, &lvcolumn);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
/*
BOOL CDNDObj_KASIM_GENUNIT_TAP::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

HBRUSH CDNDObj_KASIM_GENUNIT_TAP::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT1:
		case IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT2:
		case IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT3:
		case IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT4:
		case IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT5:
		{
			static CBrush s_brush(DIALOG_EDIT_READONLY_COLOR);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(DIALOG_EDIT_READONLY_PEN_COLOR);
			pDC->SetBkColor(DIALOG_EDIT_READONLY_COLOR);
			return s_brush;
		}
		}
		static CBrush s_brush(WND_BG_DIALOG_COLOR);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(DIALOG_STATIC_PEN_COLOR);
		pDC->SetBkColor(WND_BG_DIALOG_COLOR);
		return s_brush;
	}
	else if (nCtlColor == CTLCOLOR_EDIT)
	{
		static CBrush s_brush(DIALOG_EDIT_DEFAULT_COLOR);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(DIALOG_EDIT_DEFAULT_PEN_COLOR);
		pDC->SetBkColor(DIALOG_EDIT_DEFAULT_COLOR);
		return s_brush;
	}
	return hbr;
}

void CDNDObj_KASIM_GENUNIT_TAP::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect																	_rect, rect;
	GetClientRect(&_rect);
	dc.FillSolidRect(_rect, WND_BG_DIALOG_COLOR);

	CPen																	pen, *poldpen;
	pen.CreatePen(PS_SOLID, DIALOG_SEPERATOR_PEN_WIDTH, DIALOG_SEPERATOR_PEN_COLOR);
	poldpen = (CPen*)dc.SelectObject(&pen);

	dc.SelectObject(poldpen);
	pen.DeleteObject();
}
*/

void CDNDObj_KASIM_GENUNIT_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	LoadKASIM();
}

void CDNDObj_KASIM_GENUNIT_TAP::LoadKASIM()
{
	//공통 
	CString stNULL;
	stNULL.Format(_T(""));
	CString stGENUNIT_NM, stGENUNIT_LOCATION_NO, stGENUNIT_LOCATION_NM, stGENUNIT_CUSTOMER_NO , stGENUNIT_CAP_KW;
	CString nGENUNIT_CEQ_GEN;
	float fGENUNIT_CAP_KW;
	int nGENUNIT_II_GEN = 0;
	unsigned long long	ullCEQID(0U);
	int nGENUNIT_Type = 0;
	//INDEX 처리
	m_nGENERATEUINT_CSVID = m_pSwitch->m_st_Kasim_GEN_Info.m_nGENID;

	//추가시
	if (m_nGENERATEUINT_CSVID != 999999)
	{
		//리스트 입력 
		LV_ITEM															lvitem;
		int																nCount, nDlIdx(0), nDlIdx2(0), nIdx(0);
		CString															szCount, szName, szData;
		float															fCap;
		m_ctrList.DeleteAllItems();

		nCount = theAppDataMng->GetTableRealCount(_T("GENUNIT_STA"));
		for (int i = 1; i <= nCount; i++)
		{
			nDlIdx = GETVALUE(int, _T("GENUNIT_STA"), _T("GENUNIT_II_GEN"), i);
			if (nDlIdx == 0)											continue;
			if (nDlIdx != m_nGENERATEUINT_CSVID)						continue;


			ullCEQID = GETVALUE(unsigned long long, "GEN_STA", "GENUNIT_CONNECT_CEQID", i);
			szName = GETSTRING(_T("GENUNIT_STA"), _T("GENUNIT_NM"), i);
			stGENUNIT_LOCATION_NO = GETSTRING(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NO"), i);
			stGENUNIT_LOCATION_NM = GETSTRING(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NM"), i);
			stGENUNIT_CUSTOMER_NO = GETSTRING(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), i);
			fCap = GETVALUE(double, _T("GENUNIT_STA"), _T("GENUNIT_CAP_KW"), i);
			nGENUNIT_Type = GETVALUE(int, _T("GENUNIT_STA"), _T("GENUNIT_TYPE"), i);
			//
			nGENUNIT_CEQ_GEN.Format(_T("%lld"), ullCEQID);

			lvitem.mask = LVIF_TEXT;
			lvitem.iItem = nIdx;
			lvitem.iSubItem = 0;
			lvitem.pszText = (LPWSTR)(LPCTSTR)_T("");
			m_ctrList.InsertItem(&lvitem);

			szData.Format(_T("%d"), nIdx);
			m_ctrList.SetItemText(nIdx, 1, szData);

			m_ctrList.SetItemText(nIdx, 2, szName);
			m_ctrList.SetItemText(nIdx, 3, nGENUNIT_CEQ_GEN);
			m_ctrList.SetItemText(nIdx, 4, stGENUNIT_LOCATION_NO);
			m_ctrList.SetItemText(nIdx, 5, stGENUNIT_LOCATION_NM);
			m_ctrList.SetItemText(nIdx, 6, stGENUNIT_CUSTOMER_NO);

			szData.Format(_T("%.2f"), fCap);
			m_ctrList.SetItemText(nIdx, 7, szData);

			szData.Format(_T("%d"), nGENUNIT_Type);
			m_ctrList.SetItemText(nIdx, 8, szData);

			//이거를 찾아야지 뭘 선택했는지 알겠지?
			m_ListGenUnit[nIdx] = i;
			if (nIdx == 0)
			{
				nGENUNIT_II_GEN = i;
			}
			nIdx++;
		}
  		
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT3, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT4, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT5, stNULL);
	}
	else
	{
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT3, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT4, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT5, stNULL);
	}
}

void CDNDObj_KASIM_GENUNIT_TAP::OnBnClickedDndobjectKasimGenunitDlgBtn1()
{
	CString stGENUNIT_NM, stGENUNIT_LOCATION_NO, stGENUNIT_LOCATION_NM, stGENUNIT_CUSTOMER_NO, stGENUNIT_CAP_KW;
	CString szName;
	float fGENUNIT_CAP_KW;
	int nCount, nDlIdx;
	int nCheck = 0;

	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT1, stGENUNIT_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT2, stGENUNIT_LOCATION_NO);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT3, stGENUNIT_LOCATION_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT4, stGENUNIT_CUSTOMER_NO);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT5, stGENUNIT_CAP_KW);
	fGENUNIT_CAP_KW = _wtof(stGENUNIT_CAP_KW);
	int nGENUNIT_TYPE = m_ctrCombo1->GetCurSel();
	nGENUNIT_TYPE = nGENUNIT_TYPE + 1;

	nCount = theAppDataMng->GetTableRealCount(_T("GENUNIT_STA"));
	for (int i = 1; i <= nCount; i++)
	{
		nDlIdx = GETVALUE(int, _T("GENUNIT_STA"), _T("GENUNIT_II_GEN"), i);
		if (nDlIdx == 0)											continue;
		if (nDlIdx != m_nGENERATEUINT_CSVID)						continue;

		szName = GETSTRING(_T("GENUNIT_STA"), _T("GENUNIT_NM"), i);
		if (szName == stGENUNIT_NM)
		{
			AfxMessageBox(_T("중복데이터입니다."));
			nCheck = 9999;
		}
	}
	if (stGENUNIT_NM == "")
	{
		AfxMessageBox(_T("이름이 없습니다."));
		nCheck = 9999;
	}
	//같은 데이터가 있으면 넣지 않는다!
	if (nCheck == 0)
	{
		nCount = nCount + 1;

		PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_NM"), nCount, (wchar_t*)stGENUNIT_NM.GetBuffer());
		PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NO"), nCount, (wchar_t*)stGENUNIT_LOCATION_NO.GetBuffer());
		PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NO"), nCount, (wchar_t*)stGENUNIT_LOCATION_NO.GetBuffer());
		PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NM"), nCount, (wchar_t*)stGENUNIT_LOCATION_NM.GetBuffer());
		PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), nCount, (wchar_t*)stGENUNIT_CUSTOMER_NO.GetBuffer());
		PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_CAP_KW"), nCount, (double)fGENUNIT_CAP_KW);
		PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_TYPE"), nCount, (int)nGENUNIT_TYPE);
	}

	LoadKASIM();
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_GENUNIT_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CDNDObj_KASIM_GENUNIT_TAP::OnBnClickedDndobjectKasimGenunitDlgBtn2()
{
	CString stGENUNIT_NM, stGENUNIT_LOCATION_NO, stGENUNIT_LOCATION_NM, stGENUNIT_CUSTOMER_NO, stGENUNIT_CAP_KW;
	CString szName;
	float fGENUNIT_CAP_KW;

	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT1, stGENUNIT_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT2, stGENUNIT_LOCATION_NO);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT3, stGENUNIT_LOCATION_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT4, stGENUNIT_CUSTOMER_NO);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT5, stGENUNIT_CAP_KW);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT5, stGENUNIT_CAP_KW);
	fGENUNIT_CAP_KW = _wtof(stGENUNIT_CAP_KW);
	int nGENUNIT_TYPE = m_ctrCombo1->GetCurSel();
	nGENUNIT_TYPE = nGENUNIT_TYPE + 1;

	//같은 데이터가 있으면 넣지 않는다!
	if (stGENUNIT_NM == "" )
	{
		AfxMessageBox(_T("이름이 없습니다."));
	}
	else if (m_nGenUnitIndex == -1)
	{
		AfxMessageBox(_T("수정할 설비가 없습니다."));
	}
	else
	{
		if (m_nGenUnitIndex != 9999 )
		{
			PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_NM"), m_nGenUnitIndex, (wchar_t*)stGENUNIT_NM.GetBuffer());
			PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NO"), m_nGenUnitIndex, (wchar_t*)stGENUNIT_LOCATION_NO.GetBuffer());
			PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NM"), m_nGenUnitIndex, (wchar_t*)stGENUNIT_LOCATION_NM.GetBuffer());
			PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), m_nGenUnitIndex, (wchar_t*)stGENUNIT_CUSTOMER_NO.GetBuffer());
			PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_CAP_KW"), m_nGenUnitIndex, (double)fGENUNIT_CAP_KW);
			PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_TYPE"), m_nGenUnitIndex, (int)nGENUNIT_TYPE);
			PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_II_GEN"), m_nGenUnitIndex, (int)m_nGENERATEUINT_CSVID);
		}
	}
	m_nGenUnitIndex = -1;

	LoadKASIM();
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_GENUNIT_TAP::OnUpdateUI_Btn2(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CDNDObj_KASIM_GENUNIT_TAP::OnBnClickedDndobjectKasimGenunitDlgBtn3()
{
	if (m_nGenUnitIndex != 9999)
	{
		PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_NM"), m_nGenUnitIndex, 0);
		PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NO"), m_nGenUnitIndex, 0);
		PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NM"), m_nGenUnitIndex, 0);
		PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), m_nGenUnitIndex, 0);
		PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_CAP_KW"), m_nGenUnitIndex, 0);
		PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_II_GEN"), m_nGenUnitIndex, 0);
		PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_TYPE"), m_nGenUnitIndex, 0);
		PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_CONNECT_CEQID"), m_nGenUnitIndex, 0);
	}

	LoadKASIM();
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}


void CDNDObj_KASIM_GENUNIT_TAP::OnUpdateUI_Btn3(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}


void CDNDObj_KASIM_GENUNIT_TAP::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW*													pNMListView = (NM_LISTVIEW*)pNMHDR;

	int																nFindIdx;
	nFindIdx = pNMListView->iItem;
	m_nGenUnitIndex = m_ListGenUnit[nFindIdx];

	*pResult = 0;
}

void CDNDObj_KASIM_GENUNIT_TAP::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW*													pNMListView = (NM_LISTVIEW*)pNMHDR;

	CString stGENUNIT_NM, stGENUNIT_LOCATION_NO, stGENUNIT_LOCATION_NM, stGENUNIT_CUSTOMER_NO, stGENUNIT_CAP_KW;
	CString nGENUNIT_CEQ_GEN;
	float fGENUNIT_CAP_KW;
	unsigned long long	ullCEQID(0U);
	//////////

	int																nFindIdx;
	nFindIdx = pNMListView->iItem;

	int nGenUnitIndex = 0;
	int nGenUnitType = 0;
	nGenUnitIndex = m_ListGenUnit[nFindIdx];

	//GENUNIT_STA
	stGENUNIT_NM = CA2W(GETSTRING(("GENUNIT_STA"), ("GENUNIT_NM"), nGenUnitIndex)).m_psz;
	nGENUNIT_CEQ_GEN = CA2W(GETSTRING(("GENUNIT_STA"), ("GENUNIT_CONNECT_CEQID"), nGenUnitIndex)).m_psz;
	stGENUNIT_LOCATION_NO = CA2W(GETSTRING(("GENUNIT_STA"), ("GENUNIT_LOCATION_NO"), nGenUnitIndex)).m_psz;
	stGENUNIT_LOCATION_NM = CA2W(GETSTRING(("GENUNIT_STA"), ("GENUNIT_LOCATION_NM"), nGenUnitIndex)).m_psz;
	stGENUNIT_CUSTOMER_NO = CA2W(GETSTRING(("GENUNIT_STA"), ("GENUNIT_CUSTOMER_NO"), nGenUnitIndex)).m_psz;
	fGENUNIT_CAP_KW = GETVALUE(double, _T("GENUNIT_STA"), _T("GENUNIT_CAP_KW"), nGenUnitIndex);
	nGenUnitType = GETVALUE(int, _T("GENUNIT_STA"), _T("GENUNIT_TYPE"), nGenUnitIndex);
	ullCEQID = GETVALUE(unsigned long long, "GEN_STA", "GENUNIT_CONNECT_CEQID", nGenUnitIndex);

	nGENUNIT_CEQ_GEN.Format(_T("%lld"), ullCEQID);
	stGENUNIT_CAP_KW.Format(_T("%.2f"), fGENUNIT_CAP_KW);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT1, stGENUNIT_NM);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT2, stGENUNIT_LOCATION_NO);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT3, stGENUNIT_LOCATION_NM);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT4, stGENUNIT_CUSTOMER_NO);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT5, stGENUNIT_CAP_KW);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_GENUNIT_DLG_EDIT6, nGENUNIT_CEQ_GEN);
	m_ctrCombo1[0].SetCurSel(nGenUnitType - 1);

	*pResult = 0;

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

BOOL CDNDObj_KASIM_GENUNIT_TAP::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}