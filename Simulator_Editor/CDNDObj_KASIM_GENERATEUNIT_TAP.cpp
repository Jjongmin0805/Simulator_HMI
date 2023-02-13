// CDNDObj_KASIM_GENERATEUNIT_TAP.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_GENERATEUNIT_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDNDObj_KASIM_GENERATEUNIT_TAP 대화 상자
IMPLEMENT_DYNAMIC(CDNDObj_KASIM_GENERATEUNIT_TAP, CDialog)

CDNDObj_KASIM_GENERATEUNIT_TAP::CDNDObj_KASIM_GENERATEUNIT_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_GENERATEUNIT_DLG, pParent)
{
	m_nGENERATEUINT_CSVID = 0;
}

CDNDObj_KASIM_GENERATEUNIT_TAP::~CDNDObj_KASIM_GENERATEUNIT_TAP()
{
}

void CDNDObj_KASIM_GENERATEUNIT_TAP::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_GEN_DLG_COMBO1, m_ctrCombo1[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_GEN_DLG_COMBO3, m_ctrCombo3[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_GEN_DLG_COMBO5, m_ctrCombo5[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_GEN_DLG_COMBO10, m_ctrCombo10[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_GEN_DLG_COMBO11, m_ctrCombo11[0]);
	CDialog::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CDNDObj_KASIM_GENERATEUNIT_TAP, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_GEN_DLG_BTN1, &CDNDObj_KASIM_GENERATEUNIT_TAP::OnBnClickedDndobjectKasimGenDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_GEN_DLG_BTN1, &CDNDObj_KASIM_GENERATEUNIT_TAP::OnUpdateUI_Btn1)
END_MESSAGE_MAP()
// CDNDObj_KASIM_GENERATEUNIT_TAP 메시지 처리기

BOOL CDNDObj_KASIM_GENERATEUNIT_TAP::OnInitDialog()
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

	m_ctrCombo3[0].AddString(_T("A상"));
	m_ctrCombo3[0].AddString(_T("B상"));
	m_ctrCombo3[0].AddString(_T("C상"));
	m_ctrCombo3[0].AddString(_T("AB상"));
	m_ctrCombo3[0].AddString(_T("BC상"));
	m_ctrCombo3[0].AddString(_T("AC상"));
	m_ctrCombo3[0].AddString(_T("3상"));

	m_ctrCombo5[0].AddString(_T("특고압 전용"));
	m_ctrCombo5[0].AddString(_T("저압 전용"));
	m_ctrCombo5[0].AddString(_T("저압 공용"));

	m_ctrCombo10[0].AddString(_T("인버터"));
	m_ctrCombo10[0].AddString(_T("동기기"));
	m_ctrCombo10[0].AddString(_T("유도기"));
	m_ctrCombo10[0].AddString(_T("고압 동기기"));

	m_ctrCombo11[0].AddString(_T("Ygyg"));
	m_ctrCombo11[0].AddString(_T("Ygd"));
	m_ctrCombo11[0].AddString(_T("Dyg"));
	m_ctrCombo11[0].AddString(_T("Yd"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDNDObj_KASIM_GENERATEUNIT_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	LoadKASIM();
}

void CDNDObj_KASIM_GENERATEUNIT_TAP::LoadKASIM()
{
	//공통 
	CString stKASIM_CEQ, stKASIM_NM;
	unsigned long long	ullCEQID(0U);
	CString stNULL;
	stNULL.Format(_T("0"));
	//신규 추가
	CString stCEQID, stFndFK;
	int nIJEQU = 0, nIJEQUTY = 0, nIJ_WhileID = 0;
	//수정
	CString  stGen_cap, stGen_ssx;
	double dGen_cap;
	double dGen_ssx;
	int nGen_Type = 0;
	int nGen_conndrep = 0;
	int nGen_contype = 0;
	int nGen_trexcl = 0;
	CString stGEN_ITR_CAP, stGEN_ITR_X, stGEN_ITR_NGR_R, stGEN_ITR_NGR_X, stGEN_DERAVMQVRATIO;
	double dGEN_ITR_CAP, dGEN_ITR_X, dGEN_ITR_NGR_R, dGEN_ITR_NGR_X;
	int nGEN_MACH_TYPE;
	int nGEN_ITR_WDC;
	double dGEN_DERAVMQVRATIO;
	//INDEX 처리
	m_nGENERATEUINT_CSVID = m_pSwitch->m_st_Kasim_GEN_Info.m_nGENID;
	m_nND_CSVID = m_pSwitch->m_st_Kasim_GEN_Info.m_nGEN_ND;
	m_nIJ_CSVID = m_pSwitch->m_st_Kasim_GEN_Info.m_nGEN_IJ;
	m_nESS_CSVID = m_pSwitch->m_st_Kasim_GEN_Info.m_nGEN_ESS;

	//추가시
	if (m_nGENERATEUINT_CSVID != 999999)
	{
		//GEN_STA
		stKASIM_NM = CA2W(GETSTRING(("GEN_STA"), ("GEN_NM"), m_nGENERATEUINT_CSVID)).m_psz;
		ullCEQID = GETVALUE(unsigned long long, "GEN_STA", "GEN_CEQID", m_nGENERATEUINT_CSVID);
		dGen_cap = GETVALUE(double, _T("GEN_STA"), _T("GEN_MWLMMX"), m_nGENERATEUINT_CSVID);
		dGen_ssx = GETVALUE(double, _T("GEN_STA"), _T("GEN_SSX"), m_nGENERATEUINT_CSVID);
		nGen_Type = GETVALUE(int, _T("GEN_STA"), _T("GEN_TYPE"), m_nGENERATEUINT_CSVID);
		nGen_contype = GETVALUE(int, _T("GEN_STA"), _T("GEN_CONTYPE"), m_nGENERATEUINT_CSVID);
		nGen_trexcl = GETVALUE(int, _T("GEN_STA"), _T("GEN_TREXCL"), m_nGENERATEUINT_CSVID);
		//GEN_DYN_UIN
		dGEN_ITR_CAP = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_ITR_CAP"), m_nGENERATEUINT_CSVID);
		dGEN_ITR_X = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_ITR_X"), m_nGENERATEUINT_CSVID);
		dGEN_ITR_NGR_R = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_ITR_NGR_R"), m_nGENERATEUINT_CSVID);
		dGEN_ITR_NGR_X = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_ITR_NGR_X"), m_nGENERATEUINT_CSVID);
		nGEN_ITR_WDC = GETVALUE(int, _T("GEN_DYN_UIN"), _T("GEN_ITR_WDC"), m_nGENERATEUINT_CSVID);
		nGEN_MACH_TYPE = GETVALUE(int, _T("GEN_DYN_UIN"), _T("GEN_MACH_TYPE"), m_nGENERATEUINT_CSVID);
		dGEN_DERAVMQVRATIO = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_DERAVMQVRATIO"), m_nGENERATEUINT_CSVID);

		dGen_cap = dGen_cap * 1000;
		//GEN_STA
		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		stGen_cap.Format(_T("%0.2f"), dGen_cap);
		stGen_ssx.Format(_T("%0.2f"), dGen_ssx);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT1, stKASIM_NM);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT2, stKASIM_CEQ);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT3, stGen_cap);       //최대 MW 발전용량(설비용량 기준)
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT4, stGen_ssx);		//발전기 정상 리액턴스
		m_ctrCombo1[0].SetCurSel(nGen_Type - 1);								//발전기 종류 (1:무한모선, 2: 디젤, 3:ESS, 4:풍력, 5:태양광, 6:바이오)
		m_ctrCombo3[0].SetCurSel(nGen_contype - 1);								//분산전원 연결 정보(1:A 상, 2 : B상, 3 : C상, 4 : AB상, 5 : BC상, 6 : CA상, 7 : 3상)
		m_ctrCombo5[0].SetCurSel(nGen_trexcl - 1);								//분산전원 연계변압기 전용여부	(1:특고압 전용, 2 : 저압 전용 3 : 저압 공용)
		//GEN_DYN_UIN
		stGEN_ITR_CAP.Format(_T("%0.4f"), dGEN_ITR_CAP);
		stGEN_ITR_X.Format(_T("%0.4f"), dGEN_ITR_X);
		stGEN_ITR_NGR_R.Format(_T("%0.4f"), dGEN_ITR_NGR_R);
		stGEN_ITR_NGR_X.Format(_T("%0.4f"), dGEN_ITR_NGR_X);
		stGEN_DERAVMQVRATIO.Format(_T("%0.4f"), dGEN_DERAVMQVRATIO);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT5, stGEN_ITR_CAP);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT6, stGEN_ITR_X);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT7, stGEN_ITR_NGR_R);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT8, stGEN_ITR_NGR_X);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT9, stGEN_DERAVMQVRATIO);
		m_ctrCombo10[0].SetCurSel(nGEN_MACH_TYPE - 1);						   //발전기 유형(1:인버터, 2:동기기, 3:유도기, 4:고압동기기)
		m_ctrCombo11[0].SetCurSel(nGEN_ITR_WDC - 1);
	}
	else
	{
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT3, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT4, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT5, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT6, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT7, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT8, stNULL);
		m_ctrCombo1[0].SetCurSel(-1);
		m_ctrCombo3[0].SetCurSel(-1);
		m_ctrCombo5[0].SetCurSel(-1);
		m_ctrCombo10[0].SetCurSel(-1);
	}
}

void CDNDObj_KASIM_GENERATEUNIT_TAP::OnBnClickedDndobjectKasimGenDlgBtn1()
{
	CString stGen_cap, stGen_ssx, stKASIM_NM, stCEQID;
	CString stGEN_ITR_CAP, stGEN_ITR_X, stGEN_ITR_NGR_R, stGEN_ITR_NGR_X, stGEN_DERAVMQVRATIO;
	float dGen_cap;
	UpdateData(TRUE);
	//GEN_STA
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT1, stKASIM_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT2, stCEQID);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT3, stGen_cap);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT4, stGen_ssx);
	int nGEN_TYPE = m_ctrCombo1->GetCurSel();
	int nGEN_CONTYPE = m_ctrCombo3->GetCurSel();
	int nGEN_TREXCL = m_ctrCombo5->GetCurSel();
	//GEN_DYN_UIN
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT5, stGEN_ITR_CAP);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT6, stGEN_ITR_X);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT7, stGEN_ITR_NGR_R);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT8, stGEN_ITR_NGR_X);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT9, stGEN_DERAVMQVRATIO);
	int nGEN_MACH_TYPE = m_ctrCombo10 ->GetCurSel();
	int nGEN_ITR_WDC = m_ctrCombo11->GetCurSel();
	//

	dGen_cap = _wtof(stGen_cap);
	dGen_cap = dGen_cap / 1000;
	//GEN_STA
	PUTVALUE(_T("GEN_STA"), _T("GEN_NM"), m_nGENERATEUINT_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GEN_STA"), _T("GEN_CEQID"), m_nGENERATEUINT_CSVID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMX"), m_nGENERATEUINT_CSVID, (double)dGen_cap);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_SSX"), m_nGENERATEUINT_CSVID, (double)_wtof(stGen_ssx));
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TYPE"), m_nGENERATEUINT_CSVID, (int)nGEN_TYPE+1);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_CONTYPE"), m_nGENERATEUINT_CSVID, (int)nGEN_CONTYPE+1);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TREXCL"), m_nGENERATEUINT_CSVID, (int)nGEN_TREXCL+1);
	//GEN_DYN_UIN
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_CAP"), m_nGENERATEUINT_CSVID, (double)_wtof(stGEN_ITR_CAP));
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_X"), m_nGENERATEUINT_CSVID, (double)_wtof(stGEN_ITR_X));
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_NGR_R"), m_nGENERATEUINT_CSVID, (double)_wtof(stGEN_ITR_NGR_R));
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_NGR_X"), m_nGENERATEUINT_CSVID, (double)_wtof(stGEN_ITR_NGR_X));
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MACH_TYPE"), m_nGENERATEUINT_CSVID, (int)nGEN_MACH_TYPE + 1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_WDC"), m_nGENERATEUINT_CSVID, (int)nGEN_ITR_WDC + 1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMQVRATIO"), m_nGENERATEUINT_CSVID, (double)_wtof(stGEN_DERAVMQVRATIO));
	//추가 이름 변경 타입변경?
	PUTVALUE(_T("ND_STA"), _T("ND_NM"), m_nND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GND_STA"), _T("GND_NM"), m_nND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	m_pSwitch->m_str_keyname.Format(_T("%s"), stKASIM_NM);

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_GENERATEUNIT_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}


BOOL CDNDObj_KASIM_GENERATEUNIT_TAP::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == 13)
		{
			CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
			OnBnClickedDndobjectKasimGenDlgBtn1();
			pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

/*
BOOL CDNDObj_KASIM_GENERATEUNIT_TAP::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

HBRUSH CDNDObj_KASIM_GENERATEUNIT_TAP::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
// 	if (nCtlColor == CTLCOLOR_STATIC)
// 	{
// 		switch (pWnd->GetDlgCtrlID())
// 		{
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT1:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT2:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT3:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT4:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT5:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT6:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT7:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_EDIT8:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_COMBO1:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_COMBO3:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_COMBO5:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_COMBO10:
// 			case IDC_DNDOBJECT_KASIM_GEN_DLG_COMBO11:
// 			{
// 				static CBrush s_brush(DIALOG_EDIT_READONLY_COLOR);
// 				pDC->SetBkMode(TRANSPARENT);
// 				pDC->SetTextColor(DIALOG_EDIT_READONLY_PEN_COLOR);
// 				pDC->SetBkColor(DIALOG_EDIT_READONLY_COLOR);
// 				return s_brush;
// 			}
// 		}
// 		static CBrush s_brush(WND_BG_DIALOG_COLOR);
// 		pDC->SetBkMode(TRANSPARENT);
// 		pDC->SetTextColor(DIALOG_STATIC_PEN_COLOR);
// 		pDC->SetBkColor(WND_BG_DIALOG_COLOR);
// 		return s_brush;
// 	}
// 	else if (nCtlColor == CTLCOLOR_EDIT)
// 	{
// 		static CBrush s_brush(DIALOG_EDIT_DEFAULT_COLOR);
// 		pDC->SetBkMode(TRANSPARENT);
// 		pDC->SetTextColor(DIALOG_EDIT_DEFAULT_PEN_COLOR);
// 		pDC->SetBkColor(DIALOG_EDIT_DEFAULT_COLOR);
// 		return s_brush;
// 	}
	return hbr;
}

void CDNDObj_KASIM_GENERATEUNIT_TAP::OnPaint()
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