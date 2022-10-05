// Group1ApplDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "Group1ApplDlg.h"
#include "afxdialogex.h"
#include "NodeView.h"
#include "MainFrm.h"

// CGroup1ApplDlg 대화 상자

IMPLEMENT_DYNAMIC(CGroup1ApplDlg, CDialog)

CGroup1ApplDlg::CGroup1ApplDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GROUP1_APPL_DLG, pParent)
{
	m_nCompType = m_nCompIdx = 0;
}

CGroup1ApplDlg::~CGroup1ApplDlg()
{
}

void CGroup1ApplDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGroup1ApplDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_GROUP1_3_RADIO_PHASE_A, &CGroup1ApplDlg::OnBnClickedGroup13RadioPhaseA)
	ON_BN_CLICKED(IDC_GROUP1_3_RADIO_PHASE_B, &CGroup1ApplDlg::OnBnClickedGroup13RadioPhaseB)
	ON_BN_CLICKED(IDC_GROUP1_3_RADIO_PHASE_C, &CGroup1ApplDlg::OnBnClickedGroup13RadioPhaseC)
END_MESSAGE_MAP()


// CGroup1ApplDlg 메시지 처리기
BOOL CGroup1ApplDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_fontDef.CreateFont(17, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("맑은 고딕"));
	m_fontBold.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("맑은 고딕"));

	GetDlgItem(IDC_GROUP1_3_STC_RPF_AMP)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_3_STC_RPF_VOLT)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_3_STC_RPF_ANGLE)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_3_STC_RPF_MW)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_3_STC_RPF_MVAR)->SetFont(&m_fontBold);

	GetDlgItem(IDC_GROUP1_3_UNIT_RPF_AMP)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_3_UNIT_RPF_VOLT)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_3_UNIT_RPF_ANGLE)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_3_UNIT_RPF_MW)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_3_UNIT_RPF_MVAR)->SetFont(&m_fontDef);

	GetDlgItem(IDC_GROUP1_3_STC_VIOLATE)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_3_UNIT_VIOLATE)->SetFont(&m_fontDef);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CGroup1ApplDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

HBRUSH CGroup1ApplDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_GROUP1_3_EDIT_RPF_AMP:
		case IDC_GROUP1_3_EDIT_RPF_VOLT:
		case IDC_GROUP1_3_EDIT_RPF_ANGLE:
		case IDC_GROUP1_3_EDIT_RPF_MW:
		case IDC_GROUP1_3_EDIT_RPF_MVAR:
		case IDC_GROUP1_3_EDIT_VIOLATE_YN:
		case IDC_GROUP1_3_EDIT_VIOLATE:
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

void CGroup1ApplDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect																	_rect, rect;
	GetClientRect(&_rect);
	dc.FillSolidRect(_rect, WND_BG_DIALOG_COLOR);

	CPen																	pen, *poldpen;
	pen.CreatePen(PS_SOLID, DIALOG_SEPERATOR_PEN_WIDTH, DIALOG_SEPERATOR_PEN_COLOR);
	poldpen = (CPen*)dc.SelectObject(&pen);

	GetDlgItem(IDC_GROUP1_3_STC_RPF_MVAR)->GetWindowRect(&rect);
	ScreenToClient(rect);
	dc.MoveTo(_rect.left + 5, rect.bottom + 20);
	dc.LineTo(_rect.right - 5, rect.bottom + 20);

	dc.SelectObject(poldpen);
	pen.DeleteObject();
}

void CGroup1ApplDlg::SetData(int nCompType, int nCompIdx)
{
	m_nCompType = nCompType;
	m_nCompIdx = nCompIdx;

	SetApplData();
}

void CGroup1ApplDlg::OnBnClickedGroup13RadioPhaseA()
{
	UpdateData();
	SetApplData();
}

void CGroup1ApplDlg::OnBnClickedGroup13RadioPhaseB()
{
	UpdateData();
	SetApplData();
}

void CGroup1ApplDlg::OnBnClickedGroup13RadioPhaseC()
{
	UpdateData();
	SetApplData();
}

void CGroup1ApplDlg::SetApplData()
{
	if (m_nCompIdx <= 0)
	{
		SetDlgItemText(IDC_GROUP1_3_EDIT_RPF_AMP, _T(""));
		SetDlgItemText(IDC_GROUP1_3_EDIT_RPF_VOLT, _T(""));
		SetDlgItemText(IDC_GROUP1_3_EDIT_RPF_ANGLE, _T(""));
		SetDlgItemText(IDC_GROUP1_3_EDIT_RPF_MW, _T(""));
		SetDlgItemText(IDC_GROUP1_3_EDIT_RPF_MVAR, _T(""));
		SetDlgItemText(IDC_GROUP1_3_EDIT_VIOLATE, _T(""));
		SetDlgItemText(IDC_GROUP1_3_EDIT_VIOLATE, _T(""));
		return;
	}

	double																	dAmp_PF(0), dAngle_PF(0), dkV_PF(0), dP_PF(0), dQ_PF(0), dViolation(0);
	if (m_nCompType == NDTYPE_SWITCH)//nCompIdx가 cbsw의 Idx이다.
	{
		int																	nGNDIdx, nVVMIdx;
		nGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fnd"), m_nCompIdx);
		nVVMIdx = GETVALUE(int, _T("nd_dyn_uin"), _T("nd_ii_vvm"), nGNDIdx);

		dAmp_PF = GETVALUE(double, _T("cbsw_dyn_rpfo"), _T("cbsw_parpfamp"), m_nCompIdx);
		dkV_PF = GETVALUE(double, _T("cbsw_dyn_rpfo"), _T("cbsw_parpfkv"), m_nCompIdx);
		dAngle_PF = GETVALUE(double, _T("cbsw_dyn_rpfo"), _T("cbsw_parpfadiff"), m_nCompIdx);
		dP_PF = GETVALUE(double, _T("cbsw_dyn_rpfo"), _T("cbsw_3prpfmw"), m_nCompIdx) * 1000;
		dQ_PF = GETVALUE(double, _T("cbsw_dyn_rpfo"), _T("cbsw_3prpfmvar"), m_nCompIdx) * 1000;
		dViolation = GetViolation(nVVMIdx, dkV_PF);
	}

	CString																	szData;

	szData.Format(_T("%.3lf"), dAmp_PF);
	SetDlgItemText(IDC_GROUP1_3_EDIT_RPF_AMP, szData);

	szData.Format(_T("%.3lf"), dkV_PF);
	SetDlgItemText(IDC_GROUP1_3_EDIT_RPF_VOLT, szData);

	szData.Format(_T("%.3lf"), dAngle_PF);
	SetDlgItemText(IDC_GROUP1_3_EDIT_RPF_ANGLE, szData);

	szData.Format(_T("%.3lf"), dP_PF);
	SetDlgItemText(IDC_GROUP1_3_EDIT_RPF_MW, szData);

	szData.Format(_T("%.3lf"), dQ_PF);
	SetDlgItemText(IDC_GROUP1_3_EDIT_RPF_MVAR, szData);

	if (dViolation < 0)
	{
		SetDlgItemText(IDC_GROUP1_3_EDIT_VIOLATE_YN, _T("하한위반"));
		szData.Format(_T("%.3lf"), abs(dViolation));
		SetDlgItemText(IDC_GROUP1_3_EDIT_VIOLATE, szData);
	}
	else if (dViolation > 0)
	{
		SetDlgItemText(IDC_GROUP1_3_EDIT_VIOLATE_YN, _T("상한위반"));
		szData.Format(_T("%.3lf"), abs(dViolation));
		SetDlgItemText(IDC_GROUP1_3_EDIT_VIOLATE, szData);
	}
	else
	{
		SetDlgItemText(IDC_GROUP1_3_EDIT_VIOLATE_YN, _T("정상"));
		SetDlgItemText(IDC_GROUP1_3_EDIT_VIOLATE, _T("-"));
	}
}

double CGroup1ApplDlg::GetViolation(int nVVMIdx, double dV)
{
	if (dV <= 0)															return 0;

	//예외처리용(임시)
	if (nVVMIdx == 0)
		nVVMIdx = 1;
	//

	double																	dHigh, dLow, dViolation;
	dHigh = GETVALUE(double, _T("vvm_dyn_uin"), _T("vvm_lmhi"), nVVMIdx) * (BASE_VOLTAGE / sqrt(3.0));
	dLow = GETVALUE(double, _T("vvm_dyn_uin"), _T("vvm_lmlo"), nVVMIdx) * (BASE_VOLTAGE / sqrt(3.0));

	if (dHigh < dV)														dViolation = dV - dHigh;
	else if (dLow > dV)													dViolation = dV - dLow;
	else																dViolation = 0;

	return dViolation;
}

BOOL CGroup1ApplDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
