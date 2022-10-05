// CDNDObj_KASIM_PRDE_TAP.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_PRDE_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"
// CDNDObj_KASIM_PRDE_TAP 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_KASIM_PRDE_TAP, CDialog)

CDNDObj_KASIM_PRDE_TAP::CDNDObj_KASIM_PRDE_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_PRDE_DLG, pParent)
{

}

CDNDObj_KASIM_PRDE_TAP::~CDNDObj_KASIM_PRDE_TAP()
{
}

void CDNDObj_KASIM_PRDE_TAP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNDOBJECT_PRDE_KASIM_DLG_COMBO1, m_ctrCombo1[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_PRDE_KASIM_DLG_COMBO2, m_ctrCombo2[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_PRDE_KASIM_DLG_COMBO3, m_ctrCombo3[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_PRDE_KASIM_DLG_COMBO4, m_ctrCombo4[0]);
}


BEGIN_MESSAGE_MAP(CDNDObj_KASIM_PRDE_TAP, CDialog)
	ON_BN_CLICKED(IDC_DNDOBJECT_PRDE_DLG_BTN1, &CDNDObj_KASIM_PRDE_TAP::OnBnClickedDndobjectKasimDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_PRDE_DLG_BTN1, &CDNDObj_KASIM_PRDE_TAP::OnUpdateUI_Btn1)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDNDObj_KASIM_TAP 메시지 처리기
BOOL CDNDObj_KASIM_PRDE_TAP::OnInitDialog()
{
	CDialog::OnInitDialog();

	_wsetlocale(LC_ALL, _T("Korean"));
	return TRUE; 
}

void CDNDObj_KASIM_PRDE_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	Load_MACHINE();
	LoadKASIM();
}

void CDNDObj_KASIM_PRDE_TAP::Load_MACHINE()
{
	int i = 0;
	CString stNM;
	int nCount_PRDE_table = theAppDataMng->GetTableRealCount(_T("MACHINE_DYN_UIN"));
	for (i = 1; i <= (int)nCount_PRDE_table; i++)
	{
		stNM = CA2W(GETSTRING(("MACHINE_DYN_UIN"), ("MACHINE_NM"), i)).m_psz;
		m_ctrCombo1[0].AddString(stNM);
		m_ctrCombo3[0].AddString(stNM);
	}
	int nCount_TCCSET_table = theAppDataMng->GetTableRealCount(_T("TCCSET_STA"));
	for (i = 1; i <= (int)nCount_TCCSET_table; i++)
	{
		stNM = CA2W(GETSTRING(("TCCSET_STA"), ("TCCSET_NM"), i)).m_psz;
		m_ctrCombo2[0].AddString(stNM);
		m_ctrCombo4[0].AddString(stNM);
	}
}

void CDNDObj_KASIM_PRDE_TAP::LoadKASIM()
{
	CString stKASIM_NM;
	CString stKASIM_TCCSET_OCRF_NM, stKASIM_TCCSET_OCRD_NM;
	CString stNULL, szData;
	stNULL.Format(_T("0"));

	int														nTCCSET_Index[2];
	int														nCTRatio[2];
	int														nTypeidx[2];
	double													dTabVal[2];
	double													dLever[2];
	double													dSTabVal[2];


	double		dTabVal1, dTabVal2;
	double		dSTabVal1, dSTabVal2;

	//INDEX 처리
	if (m_pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE != 0) { m_nPRDE_CSVID = m_pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE; }
	else if (m_pSwitch->m_st_Kasim_GEN_Info.m_nGEN_PRDE != 0) { m_nPRDE_CSVID = m_pSwitch->m_st_Kasim_GEN_Info.m_nGEN_PRDE; }
	else if (m_pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_PRDE != 0) { m_nPRDE_CSVID = m_pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_PRDE; }

	if (m_nPRDE_CSVID != 999999) //데이터가 있으면
	{
		stKASIM_NM = CA2W(GETSTRING(("PRDE_STA"), ("PRDE_NM"), m_nPRDE_CSVID)).m_psz;
		nCTRatio[0] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocr_ctr"), m_nPRDE_CSVID);
		nCTRatio[1] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocgr_ctr"), m_nPRDE_CSVID);
		nTCCSET_Index[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("PRDE_OCRF_II_TCCSET"), m_nPRDE_CSVID) ;
		nTCCSET_Index[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("PRDE_OCRD_II_TCCSET"), m_nPRDE_CSVID);
		nTypeidx[0] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocr_ii_machine"), m_nPRDE_CSVID);
		nTypeidx[1] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocgr_ii_machine"), m_nPRDE_CSVID);
		dTabVal[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocr_pickup_c"), m_nPRDE_CSVID) ;
		dTabVal[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgr_pickup_c"), m_nPRDE_CSVID);
		dLever[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrf_tms"), m_nPRDE_CSVID);
		dLever[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrf_tms"), m_nPRDE_CSVID);
		dSTabVal[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocr_iic"), m_nPRDE_CSVID) ;
		dSTabVal[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgr_iic"), m_nPRDE_CSVID) ;

		if (nCTRatio[0] == 0)
		{
			dTabVal1 = 0;
			dSTabVal1 = 0;
		}
		else
		{
			dTabVal1 = (dTabVal[0] / nCTRatio[0]);
			dSTabVal1 = (dSTabVal[0] / nCTRatio[0]);
		}

		if (nCTRatio[1] == 0)
		{
			dTabVal2 = 0;
			dSTabVal2 = 0;
		}
		else
		{
			dTabVal2 = (dTabVal[1] / nCTRatio[1]);
			dSTabVal2 = (dSTabVal[1] / nCTRatio[1]);
		}

		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT1, stKASIM_NM);
		szData.Format(_T("%d"), (nCTRatio[0] * 5));
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT2, szData);
		szData.Format(_T("%0.2f"), dTabVal1 );
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT4, szData);
		szData.Format(_T("%0.2f"), dLever[0]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT5, szData);
		szData.Format(_T("%0.2f"), dSTabVal1 );  //dSTabVal[0] / nCTRatio[0]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT6, szData);
		szData.Format(_T("%d"), (nCTRatio[1] * 5));
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT7, szData);
		szData.Format(_T("%0.2f"), dTabVal2 );
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT9, szData);
		szData.Format(_T("%0.2f"), dLever[1]);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT10, szData);
		szData.Format(_T("%0.2f"), dSTabVal2 );
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT11, szData);
		//
		if (nTypeidx[0] != 0)
			m_ctrCombo1[0].SetCurSel(nTypeidx[0] - 1);
		if (nTypeidx[1] != 0)
			m_ctrCombo2[0].SetCurSel(nTypeidx[1] - 1);
		//TCCSET
		if (nTCCSET_Index[0] != 0)
			m_ctrCombo3[0].SetCurSel(nTCCSET_Index[0] - 1);
		if (nTCCSET_Index[1] != 0)
			m_ctrCombo4[0].SetCurSel(nTCCSET_Index[1] - 1);
	}
	else
	{		
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT4, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT5, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT6, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT7, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT9, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT10, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT11, stNULL);
		m_ctrCombo1[0].SetCurSel(-1);
		m_ctrCombo2[0].SetCurSel(-1);	
		m_ctrCombo3[0].SetCurSel(-1);
		m_ctrCombo4[0].SetCurSel(-1);
	}
}

void CDNDObj_KASIM_PRDE_TAP::OnBnClickedDndobjectKasimDlgBtn1()
{
	CString stKASIM_NM, szData;
	CString stKASIM_TCCSET_OCRF_NM, stKASIM_TCCSET_OCRD_NM;
		
	int														nCTRatio[2];
	double													dTabVal[2];
	double													dLever[2];
	double													dSTabVal[2];
	//설정값 가져오기
	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT1, stKASIM_NM);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT2, szData);
	nCTRatio[0] = _wtoi(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT4, szData);
	dTabVal[0] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT5, szData);
	dLever[0] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT6, szData);
	dSTabVal[0] = _wtof(szData);

	GetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT7, szData);
	nCTRatio[1] = _wtoi(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT9, szData);
	dTabVal[1] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT10, szData);
	dLever[1] = _wtof(szData);
	GetDlgItemText(IDC_DNDOBJECT_PRDE_EDIT11, szData);
	dSTabVal[1] = _wtof(szData);

	int nPos1 = m_ctrCombo1->GetCurSel();
	int nPos2 = m_ctrCombo2->GetCurSel();
	int nPos3 = m_ctrCombo3->GetCurSel();
	int nPos4 = m_ctrCombo4->GetCurSel();
	nPos1 = nPos1 + 1;
	nPos2 = nPos2 + 1;
	nPos3 = nPos3 + 1;
	nPos4 = nPos4 + 1;

	PUTVALUE(_T("PRDE_STA"), _T("PRDE_NM"), m_nPRDE_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_II_MACHINE"), m_nPRDE_CSVID, (int)nPos1);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_II_MACHINE"), m_nPRDE_CSVID, (int)nPos2);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), m_nPRDE_CSVID, (int)nPos3);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_II_TCCSET"), m_nPRDE_CSVID, (int)nPos4);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocr_ctr"), m_nPRDE_CSVID, (int)nCTRatio[0]/5);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgr_ctr"), m_nPRDE_CSVID, (int)nCTRatio[1]/5);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocr_pickup_c"), m_nPRDE_CSVID, (double)dTabVal[0]* nCTRatio[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgr_pickup_c"), m_nPRDE_CSVID, (double)dTabVal[1]* nCTRatio[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocrf_tms"), m_nPRDE_CSVID, (double)dLever[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgrf_tms"), m_nPRDE_CSVID, (double)dLever[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocr_iic"), m_nPRDE_CSVID, (double)dSTabVal[0]* nCTRatio[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("prde_ocgr_iic"), m_nPRDE_CSVID, (double)dSTabVal[1]* nCTRatio[1]);

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_PRDE_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

BOOL CDNDObj_KASIM_PRDE_TAP::PreTranslateMessage(MSG* pMsg)
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




