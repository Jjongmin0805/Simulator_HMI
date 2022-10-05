#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_PRDE_RECLOSER_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"
// CDNDObj_KASIM_PRDE_RECLOSER_TAP 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_KASIM_PRDE_RECLOSER_TAP, CDialog)

CDNDObj_KASIM_PRDE_RECLOSER_TAP::CDNDObj_KASIM_PRDE_RECLOSER_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_PRDE_RECLOSER_DLG, pParent)
{

}

CDNDObj_KASIM_PRDE_RECLOSER_TAP::~CDNDObj_KASIM_PRDE_RECLOSER_TAP()
{
}

void CDNDObj_KASIM_PRDE_RECLOSER_TAP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNDOBJECT_PRDE_KASIM_RECLOSER_DLG_COMBO1, m_ctrCombo1[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_PRDE_KASIM_RECLOSER_DLG_COMBO2, m_ctrCombo2[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_PRDE_KASIM_RECLOSER_DLG_COMBO3, m_ctrCombo3[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_PRDE_KASIM_RECLOSER_DLG_COMBO4, m_ctrCombo4[0]);
}


BEGIN_MESSAGE_MAP(CDNDObj_KASIM_PRDE_RECLOSER_TAP, CDialog)
	ON_BN_CLICKED(IDC_DNDOBJECT_PRDE_RECLOSER_DLG_BTN1, &CDNDObj_KASIM_PRDE_RECLOSER_TAP::OnBnClickedDndobjectKasimDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_PRDE_RECLOSER_DLG_BTN1, &CDNDObj_KASIM_PRDE_RECLOSER_TAP::OnUpdateUI_Btn1)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDNDObj_KASIM_TAP 메시지 처리기
BOOL CDNDObj_KASIM_PRDE_RECLOSER_TAP::OnInitDialog()
{
	CDialog::OnInitDialog();

	_wsetlocale(LC_ALL, _T("Korean"));
	return TRUE;
}

void CDNDObj_KASIM_PRDE_RECLOSER_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	Load_MACHINE();
	LoadKASIM();
}

void CDNDObj_KASIM_PRDE_RECLOSER_TAP::Load_MACHINE()
{
	int i = 0;
	CString stNM;
	int nCount_TCCSET_table = theAppDataMng->GetTableRealCount(_T("TCCSET_STA"));
	for (i = 1; i <= (int)nCount_TCCSET_table; i++)
	{
		stNM = CA2W(GETSTRING(("TCCSET_STA"), ("TCCSET_NM"), i)).m_psz;
		m_ctrCombo1[0].AddString(stNM);
		m_ctrCombo2[0].AddString(stNM);
		m_ctrCombo3[0].AddString(stNM);
		m_ctrCombo4[0].AddString(stNM);
	}
}

void CDNDObj_KASIM_PRDE_RECLOSER_TAP::LoadKASIM()
{
	CString stKASIM_NM;
	CString stNULL, szData;
	stNULL.Format(_T("0"));
	
	double													dMinAmp[2];
	int														nFCurveidx[2];
	double													dFTD[2];
	double													dFMRT[2];
	int														nDCurveidx[2];
	double													dDTD[2];
	double													dDMRT[2];
	double													dInsAmp[2];


	//INDEX 처리
	if (m_pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE != 0) { m_nPRDE_CSVID = m_pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE; }
	else if (m_pSwitch->m_st_Kasim_GEN_Info.m_nGEN_PRDE != 0) { m_nPRDE_CSVID = m_pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE; }
	else if (m_pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_PRDE != 0) { m_nPRDE_CSVID = m_pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE; }

	if (m_nPRDE_CSVID != 999999) //데이터가 있으면
	{
		stKASIM_NM = CA2W(GETSTRING(("PRDE_STA"), ("PRDE_NM"), m_nPRDE_CSVID)).m_psz;
			   
		dMinAmp[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocr_pickup_c"), m_nPRDE_CSVID);
		dMinAmp[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgr_pickup_c"), m_nPRDE_CSVID);
		nFCurveidx[0] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocrf_ii_tccset"), m_nPRDE_CSVID);
		nFCurveidx[1] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocgrf_ii_tccset"), m_nPRDE_CSVID);
		dFTD[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrf_tms"), m_nPRDE_CSVID);
		dFTD[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrf_tms"), m_nPRDE_CSVID);
		dFMRT[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrf_mrt"), m_nPRDE_CSVID);
		dFMRT[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrf_mrt"), m_nPRDE_CSVID);
		nDCurveidx[0] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocrd_ii_tccset"), m_nPRDE_CSVID);
		nDCurveidx[1] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocgrd_ii_tccset"), m_nPRDE_CSVID);
		dDTD[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrd_tms"), m_nPRDE_CSVID);
		dDTD[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrd_tms"), m_nPRDE_CSVID);
		dDMRT[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrd_mrt"), m_nPRDE_CSVID);
		dDMRT[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrd_mrt"), m_nPRDE_CSVID);
		dInsAmp[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocr_iic"), m_nPRDE_CSVID);
		dInsAmp[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgr_iic"), m_nPRDE_CSVID);


		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT1, stKASIM_NM);

		szData.Format(_T("%.2f"), dMinAmp[0]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT2, szData);
		szData.Format(_T("%.2f"), dFTD[0]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT3, szData);
		szData.Format(_T("%.2f"), dFMRT[0]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT4, szData);
		szData.Format(_T("%.2f"), dDTD[0]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT5, szData);
		szData.Format(_T("%.2f"), dDMRT[0]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT6, szData);
		szData.Format(_T("%.2f"), dInsAmp[0]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT7, szData);

		szData.Format(_T("%.2f"), dMinAmp[1]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT8, szData);
		szData.Format(_T("%.2f"), dFTD[1]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT9, szData);
		szData.Format(_T("%.2f"), dFMRT[1]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT10, szData);
		szData.Format(_T("%.2f"), dDTD[1]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT11, szData);
		szData.Format(_T("%.2f"), dDMRT[1]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT12, szData);
		szData.Format(_T("%.2f"), dInsAmp[1]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT13, szData);
		//
		if (nFCurveidx[0] != 0)
			m_ctrCombo1[0].SetCurSel(nFCurveidx[0] - 1);
		if (nDCurveidx[0] != 0)
			m_ctrCombo2[0].SetCurSel(nDCurveidx[0] - 1);
		//TCCSET
		if (nFCurveidx[1] != 0)
			m_ctrCombo3[0].SetCurSel(nFCurveidx[1] - 1);
		if (nDCurveidx[1] != 0)
			m_ctrCombo4[0].SetCurSel(nDCurveidx[1] - 1);
	}
	else
	{
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT3, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT4, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT5, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT6, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT7, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT8, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT9, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT10, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT11, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT12, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT13, stNULL);
		m_ctrCombo1[0].SetCurSel(-1);
		m_ctrCombo2[0].SetCurSel(-1);
		m_ctrCombo3[0].SetCurSel(-1);
		m_ctrCombo4[0].SetCurSel(-1);
	}
}

void CDNDObj_KASIM_PRDE_RECLOSER_TAP::OnBnClickedDndobjectKasimDlgBtn1()
{
	CString stKASIM_NM, szData;

	double													dMinAmp[2];
	double													dFTD[2];
	double													dFMRT[2];
	double													dDTD[2];
	double													dDMRT[2];
	double													dInsAmp[2];
	//설정값 가져오기
	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT1, stKASIM_NM);

	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT2, szData);
	dMinAmp[0] = _wtoi(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT3, szData);
	dFTD[0] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT4, szData);
	dFMRT[0] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT5, szData);
	dDTD[0] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT6, szData);
	dDMRT[0] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT7, szData);
	dInsAmp[0] = _wtof(szData);

	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT8, szData);
	dMinAmp[1] = _wtoi(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT9, szData);
	dFTD[1] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT10, szData);
	dFMRT[1] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT11, szData);
	dDTD[1] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT12, szData);
	dDMRT[1] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_RECLOSER_EDIT13, szData);
	dInsAmp[1] = _wtof(szData);

	int nPos1 = m_ctrCombo1->GetCurSel();
	int nPos2 = m_ctrCombo2->GetCurSel();
	int nPos3 = m_ctrCombo3->GetCurSel();
	int nPos4 = m_ctrCombo4->GetCurSel();
	nPos1 = nPos1 + 1;
	nPos2 = nPos2 + 1;
	nPos3 = nPos3 + 1;
	nPos4 = nPos4 + 1;

	PUTVALUE(_T("PRDE_STA"), _T("PRDE_NM"), m_nPRDE_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocrf_ii_tccset"), m_nPRDE_CSVID, (int)nPos1);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocrd_ii_tccset"), m_nPRDE_CSVID, (int)nPos2);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgrf_ii_tccset"), m_nPRDE_CSVID, (int)nPos3);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgrd_ii_tccset"), m_nPRDE_CSVID, (int)nPos4);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocr_pickup_c"), m_nPRDE_CSVID, (int)dMinAmp[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgr_pickup_c"), m_nPRDE_CSVID, (int)dMinAmp[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocrf_tms"), m_nPRDE_CSVID, (double)dFTD[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgrf_tms"), m_nPRDE_CSVID, (double)dFTD[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocrf_mrt"), m_nPRDE_CSVID, (double)dFMRT[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgrf_mrt"), m_nPRDE_CSVID, (double)dFMRT[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocrd_tms"), m_nPRDE_CSVID, (double)dDTD[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgrd_tms"), m_nPRDE_CSVID, (double)dDTD[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocrd_tms"), m_nPRDE_CSVID, (double)dDTD[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgrd_tms"), m_nPRDE_CSVID, (double)dDTD[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocrd_mrt"), m_nPRDE_CSVID, (double)dDTD[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgrd_mrt"), m_nPRDE_CSVID, (double)dDTD[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocr_iic"), m_nPRDE_CSVID, (double)dInsAmp[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgr_iic"), m_nPRDE_CSVID, (double)dInsAmp[1]);




	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_PRDE_RECLOSER_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

BOOL CDNDObj_KASIM_PRDE_RECLOSER_TAP::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == 13)
		{
			CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
			OnBnClickedDndobjectKasimDlgBtn1();
			pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}






