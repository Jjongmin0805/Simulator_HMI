// RelcoserSetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "RelcoserSetDlg.h"
#include "afxdialogex.h"


// CRelcoserSetDlg 대화 상자

IMPLEMENT_DYNAMIC(CRelcoserSetDlg, CPNOCtrl_SkinFrame_POP_Dialog)

CRelcoserSetDlg::CRelcoserSetDlg(int nPrdeIdx, CWnd* pParent /*=nullptr*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_RECLOSER_SET_DLG, pParent)
{
	m_nPRDEIdx = nPrdeIdx;
}

CRelcoserSetDlg::~CRelcoserSetDlg()
{
}

void CRelcoserSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_P_FAST_CURVE, m_ctrPFastCom);
	DDX_Control(pDX, IDC_COM_P_DELAY_CURVE, m_ctrPDelayCom);
	DDX_Control(pDX, IDC_COM_G_FAST_CURVE, m_ctrGFastCom);
	DDX_Control(pDX, IDC_COM_G_DELAY_CURVE, m_ctrGDelayCom);
}


BEGIN_MESSAGE_MAP(CRelcoserSetDlg, CPNOCtrl_SkinFrame_POP_Dialog)
	ON_BN_CLICKED(IDOK, &CRelcoserSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRelcoserSetDlg 메시지 처리기
void CRelcoserSetDlg::UpdateCombo()
{
	CString														szName;
	for (int i = 1; i <= 100; i++)
	{
		szName = GETSTRING(_T("tccset_sta"), _T("tccset_nm"), i);
		if (szName.IsEmpty())
			break;

		m_ctrPFastCom.AddString(szName);
		m_ctrPDelayCom.AddString(szName);
		m_ctrGFastCom.AddString(szName);
		m_ctrGDelayCom.AddString(szName);
	}
}

BOOL CRelcoserSetDlg::OnInitDialog()
{
	CPNOCtrl_SkinFrame_POP_Dialog::OnInitDialog();

	SetWindowText(_T("리클로저 설정"));

	UpdateCombo();

	double													dMinAmp[2];
	int														nFCurveidx[2];
	double													dFTD[2];
	double													dFMRT[2];
	int														nDCurveidx[2];
	double													dDTD[2];
	double													dDMRT[2];
	double													dInsAmp[2];

	dMinAmp[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocr_pickup_c"), m_nPRDEIdx);
	dMinAmp[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgr_pickup_c"), m_nPRDEIdx);
	nFCurveidx[0] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocrf_ii_tccset"), m_nPRDEIdx);
	nFCurveidx[1] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocgrf_ii_tccset"), m_nPRDEIdx);
	dFTD[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrf_tms"), m_nPRDEIdx);
	dFTD[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrf_tms"), m_nPRDEIdx);
	dFMRT[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrf_mrt"), m_nPRDEIdx);
	dFMRT[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrf_mrt"), m_nPRDEIdx);
	nDCurveidx[0] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocrd_ii_tccset"), m_nPRDEIdx);
	nDCurveidx[1] = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocgrd_ii_tccset"), m_nPRDEIdx);
	dDTD[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrd_tms"), m_nPRDEIdx);
	dDTD[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrd_tms"), m_nPRDEIdx);
	dDMRT[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrd_mrt"), m_nPRDEIdx);
	dDMRT[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrd_mrt"), m_nPRDEIdx);
	dInsAmp[0] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocr_iic"), m_nPRDEIdx);
	dInsAmp[1] = GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgr_iic"), m_nPRDEIdx);

	if (nFCurveidx[0] != 0)
		m_ctrPFastCom.SetCurSel(nFCurveidx[0] - 1);

	if (nFCurveidx[1] != 0)
		m_ctrGFastCom.SetCurSel(nFCurveidx[1] - 1);

	if (nDCurveidx[0] != 0)
		m_ctrPDelayCom.SetCurSel(nDCurveidx[0] - 1);

	if (nDCurveidx[1] != 0)
		m_ctrGDelayCom.SetCurSel(nDCurveidx[1] - 1);

	CString													szData;
	szData.Format(_T("%g"), dMinAmp[0]);
	SetDlgItemText(IDC_EDIT_P_MIN_CUR, szData);
	szData.Format(_T("%g"), dMinAmp[1]);
	SetDlgItemText(IDC_EDIT_G_MIN_CUR, szData);

	szData.Format(_T("%g"), dFTD[0]);
	SetDlgItemText(IDC_EDIT_P_FAST_TD, szData);
	szData.Format(_T("%g"), dFTD[1]);
	SetDlgItemText(IDC_EDIT_G_FAST_TD, szData);

	szData.Format(_T("%g"), dFMRT[0]);
	SetDlgItemText(IDC_EDIT_P_FAST_MRT, szData);
	szData.Format(_T("%g"), dFMRT[1]);
	SetDlgItemText(IDC_EDIT_G_FAST_MRT, szData);

	szData.Format(_T("%g"), dDTD[0]);
	SetDlgItemText(IDC_EDIT_P_DELAY_TD, szData);
	szData.Format(_T("%g"), dDTD[1]);
	SetDlgItemText(IDC_EDIT_G_DELAY_TD, szData);

	szData.Format(_T("%g"), dDMRT[0]);
	SetDlgItemText(IDC_EDIT_P_DELAY_MRT, szData);
	szData.Format(_T("%g"), dDMRT[1]);
	SetDlgItemText(IDC_EDIT_G_DELAY_MRT, szData);

	szData.Format(_T("%g"), dInsAmp[0]);
	SetDlgItemText(IDC_EDIT_P_SCUR, szData);
	szData.Format(_T("%g"), dInsAmp[1]);
	SetDlgItemText(IDC_EDIT_G_SCUR, szData);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CRelcoserSetDlg::OnBnClickedOk()
{
	CString													szData;
	double													dMinAmp[2];
	int														nFCurveidx[2];
	double													dFTD[2];
	double													dFMRT[2];
	int														nDCurveidx[2];
	double													dDTD[2];
	double													dDMRT[2];
	double													dInsAmp[2];

	GetDlgItemText(IDC_EDIT_P_MIN_CUR, szData);
	dMinAmp[0] = _wtof(szData);
	if (dMinAmp[0] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - 최소동작전류]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_G_MIN_CUR, szData);
	dMinAmp[1] = _wtof(szData);
	if (dMinAmp[1] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - 최소동작전류]"));
		dlg.DoModal();
		return;
	}

	nFCurveidx[0] = m_ctrPFastCom.GetCurSel() + 1;
	if (nFCurveidx[0] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - Fast 곡선]"));
		dlg.DoModal();
		return;
	}

	nFCurveidx[1] = m_ctrGFastCom.GetCurSel() + 1;
	if (nFCurveidx[1] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - Fast 곡선]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_P_FAST_TD, szData);
	dFTD[0] = _wtof(szData);
	if (dFTD[0] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - Fast T.D]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_G_FAST_TD, szData);
	dFTD[1] = _wtof(szData);
	if (dFTD[1] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - Fast T.D]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_P_FAST_MRT, szData);
	dFMRT[0] = _wtof(szData);
	if (dFMRT[0] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - Fast M.R.T]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_G_FAST_MRT, szData);
	dFMRT[1] = _wtof(szData);
	if (dFMRT[1] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - Fast M.R.T]"));
		dlg.DoModal();
		return;
	}

	nDCurveidx[0] = m_ctrPDelayCom.GetCurSel() + 1;
	if (nDCurveidx[0] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - Delay 곡선]"));
		dlg.DoModal();
		return;
	}

	nDCurveidx[1] = m_ctrGDelayCom.GetCurSel() + 1;
	if (nDCurveidx[1] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - Delay 곡선]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_P_DELAY_TD, szData);
	dDTD[0] = _wtof(szData);
	if (dDTD[0] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - Delay T.D]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_G_DELAY_TD, szData);
	dDTD[1] = _wtof(szData);
	if (dDTD[1] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - Delay T.D]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_P_DELAY_MRT, szData);
	dDMRT[0] = _wtof(szData);
	if (dDMRT[0] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - Delay M.R.T]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_G_DELAY_MRT, szData);
	dDMRT[1] = _wtof(szData);
	if (dDMRT[1] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - Delay M.R.T]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_P_SCUR, szData);
	dInsAmp[0] = _wtof(szData);
	if (dInsAmp[0] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PHASE - 순시동작전류]"));
		dlg.DoModal();
		return;
	}

	GetDlgItemText(IDC_EDIT_G_SCUR, szData);
	dInsAmp[1] = _wtof(szData);
	if (dInsAmp[1] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[GROUND - 순시동작전류]"));
		dlg.DoModal();
		return;
	}

	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocr_pickup_c"), m_nPRDEIdx, dMinAmp[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgr_pickup_c"), m_nPRDEIdx, dMinAmp[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrf_ii_tccset"), m_nPRDEIdx, nFCurveidx[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrf_ii_tccset"), m_nPRDEIdx, nFCurveidx[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrf_tms"), m_nPRDEIdx, dFTD[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrf_tms"), m_nPRDEIdx, dFTD[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrf_mrt"), m_nPRDEIdx, dFMRT[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrf_mrt"), m_nPRDEIdx, dFMRT[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrd_ii_tccset"), m_nPRDEIdx, nDCurveidx[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrd_ii_tccset"), m_nPRDEIdx, nDCurveidx[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrd_tms"), m_nPRDEIdx, dDTD[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrd_tms"), m_nPRDEIdx, dDTD[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrd_mrt"), m_nPRDEIdx, dDMRT[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrd_mrt"), m_nPRDEIdx, dDMRT[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocr_iic"), m_nPRDEIdx, dInsAmp[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgr_iic"), m_nPRDEIdx, dInsAmp[1]);

	CPNOCtrl_SkinFrame_POP_Dialog::OnOK();
}
