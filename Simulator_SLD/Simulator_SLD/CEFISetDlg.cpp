// CEFISetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "CEFISetDlg.h"
#include "afxdialogex.h"


// CEFISetDlg 대화 상자

IMPLEMENT_DYNAMIC(CEFISetDlg, CPNOCtrl_SkinFrame_POP_Dialog)

CEFISetDlg::CEFISetDlg(int nPrdeIdx, int nProtectKind, CWnd* pParent /*=nullptr*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_EFI_SET_DLG, pParent)
{
	m_nPRDEIdx = nPrdeIdx;
	m_nProtectKind = nProtectKind;
}

CEFISetDlg::~CEFISetDlg()
{
}

void CEFISetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_P_EFI_CURVE, m_ctrPDelayCom);
	DDX_Control(pDX, IDC_COM_G_EFI_CURVE, m_ctrGDelayCom);
}


BEGIN_MESSAGE_MAP(CEFISetDlg, CPNOCtrl_SkinFrame_POP_Dialog)
	ON_BN_CLICKED(IDOK, &CEFISetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEFISetDlg 메시지 처리기
BOOL CEFISetDlg::OnInitDialog()
{
	CPNOCtrl_SkinFrame_POP_Dialog::OnInitDialog();

	if (m_nProtectKind == SEL_TYPE_EFI)
		SetWindowText(_T("EFI 설정"));
	else
		SetWindowText(_T("다회로차단기 설정"));

	UpdateCombo();

	double													dMinAmp[2];
	int														nDCurveidx[2];
	double													dDTD[2];
	double													dDMRT[2];

	dMinAmp[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocr_pickup_c"), m_nPRDEIdx);
	dMinAmp[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgr_pickup_c"), m_nPRDEIdx);
	nDCurveidx[0] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocrd_ii_tccset"), m_nPRDEIdx);
	nDCurveidx[1] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocgrd_ii_tccset"), m_nPRDEIdx);
	dDTD[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrd_tms"), m_nPRDEIdx);
	dDTD[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrd_tms"), m_nPRDEIdx);
	dDMRT[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrd_mrt"), m_nPRDEIdx);
	dDMRT[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrd_mrt"), m_nPRDEIdx);

	if (nDCurveidx[0] != 0)
		m_ctrPDelayCom.SetCurSel(nDCurveidx[0] - 1);

	if (nDCurveidx[1] != 0)
		m_ctrGDelayCom.SetCurSel(nDCurveidx[1] - 1);

	CString													szData;
	szData.Format(_T("%g"), dMinAmp[0]);
	SetDlgItemText(IDC_EDIT_EFI_P_MIN_CUR, szData);
	szData.Format(_T("%g"), dMinAmp[1]);
	SetDlgItemText(IDC_EDIT_EFI_G_MIN_CUR, szData);

	szData.Format(_T("%g"), dDTD[0]);
	SetDlgItemText(IDC_EDIT_P_EFI_TD, szData);
	szData.Format(_T("%g"), dDTD[1]);
	SetDlgItemText(IDC_EDIT_G_EFI_TD, szData);

	szData.Format(_T("%g"), dDMRT[0]);
	SetDlgItemText(IDC_EDIT_P_EFI_MRT, szData);
	szData.Format(_T("%g"), dDMRT[1]);
	SetDlgItemText(IDC_EDIT_G_EFI_MRT, szData);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CEFISetDlg::UpdateCombo()
{
	CString														szName;
	for (int i = 1; i <= 100; i++)
	{
		szName = GETSTRING(_T("tccset_sta"), _T("tccset_nm"), i);
		if (szName.IsEmpty())
			break;

		m_ctrPDelayCom.AddString(szName);
		m_ctrGDelayCom.AddString(szName);
	}
}

void CEFISetDlg::OnBnClickedOk()
{
	CString													szData;
	double													dMinAmp[2];
	int														nDCurveidx[2];
	double													dDTD[2];
	double													dDMRT[2];

	GetDlgItemText(IDC_EDIT_EFI_P_MIN_CUR, szData);
	dMinAmp[0] = _wtof(szData);
	if (dMinAmp[0] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - 최소동작전류]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_EFI_G_MIN_CUR, szData);
	dMinAmp[1] = _wtof(szData);
	if (dMinAmp[1] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - 최소동작전류]"));
		dlg.DoModal();
		return;
	}

	nDCurveidx[0] = m_ctrPDelayCom.GetCurSel() + 1;
	if (nDCurveidx[0] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - 곡선]"));
		dlg.DoModal();
		return;
	}

	nDCurveidx[1] = m_ctrGDelayCom.GetCurSel() + 1;
	if (nDCurveidx[1] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - 곡선]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_P_EFI_TD, szData);
	dDTD[0] = _wtof(szData);
	if (dDTD[0] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - T.D]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_G_EFI_TD, szData);
	dDTD[1] = _wtof(szData);
	if (dDTD[1] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - T.D]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_P_EFI_MRT, szData);
	dDMRT[0] = _wtof(szData);
	if (dDMRT[0] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - M.R.T]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_G_EFI_MRT, szData);
	dDMRT[1] = _wtof(szData);
	if (dDMRT[1] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - M.R.T]"));
		dlg.DoModal();
		return;
	}

	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocr_pickup_c"), m_nPRDEIdx, dMinAmp[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgr_pickup_c"), m_nPRDEIdx, dMinAmp[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrd_ii_tccset"), m_nPRDEIdx, nDCurveidx[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrd_ii_tccset"), m_nPRDEIdx, nDCurveidx[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrd_tms"), m_nPRDEIdx, dDTD[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrd_tms"), m_nPRDEIdx, dDTD[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrd_mrt"), m_nPRDEIdx, dDMRT[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrd_mrt"), m_nPRDEIdx, dDMRT[1]);

	CPNOCtrl_SkinFrame_POP_Dialog::OnOK();
}
