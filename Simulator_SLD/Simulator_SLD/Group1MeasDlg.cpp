// Group1MeasDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "Group1MeasDlg.h"
#include "afxdialogex.h"
#include "NodeView.h"
#include "MainFrm.h"

// CGroup1MeasDlg 대화 상자

IMPLEMENT_DYNAMIC(CGroup1MeasDlg, CDialog)

CGroup1MeasDlg::CGroup1MeasDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GROUP1_MEAS_DLG, pParent)
	, m_nPhaseType(0)
{
	m_nCompType = m_nCompIdx = 0;
	m_nStatus = SW_CLOSE;
}

CGroup1MeasDlg::~CGroup1MeasDlg()
{
}

void CGroup1MeasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_GROUP1_2_RADIO_PHASE_A, m_nPhaseType);
}


BEGIN_MESSAGE_MAP(CGroup1MeasDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_GROUP1_2_RADIO_PHASE_A, &CGroup1MeasDlg::OnBnClickedGroup12RadioPhaseA)
	ON_BN_CLICKED(IDC_GROUP1_2_RADIO_PHASE_B, &CGroup1MeasDlg::OnBnClickedGroup12RadioPhaseB)
	ON_BN_CLICKED(IDC_GROUP1_2_RADIO_PHASE_C, &CGroup1MeasDlg::OnBnClickedGroup12RadioPhaseC)
	ON_BN_CLICKED(IDC_GROUP1_2_BTN_MODIFY, &CGroup1MeasDlg::OnBnClickedGroup12BtnModify)
END_MESSAGE_MAP()


// CGroup1MeasDlg 메시지 처리기
BOOL CGroup1MeasDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowTheme(GetDlgItem(IDC_GROUP1_2_RADIO_PHASE_A)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP1_2_RADIO_PHASE_B)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP1_2_RADIO_PHASE_C)->m_hWnd, _T(""), _T(""));

	m_fontDef.CreateFont(17, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("맑은 고딕"));
	m_fontBold.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("맑은 고딕"));

	GetDlgItem(IDC_GROUP1_2_RADIO_PHASE_A)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_2_RADIO_PHASE_B)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_2_RADIO_PHASE_C)->SetFont(&m_fontDef);

	GetDlgItem(IDC_GROUP1_2_STC_AMP)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_2_STC_VOLT)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_2_STC_ANGLE)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_2_STC_MW)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_2_STC_MVAR)->SetFont(&m_fontBold);

	GetDlgItem(IDC_GROUP1_2_UNIT_AMP)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_2_UNIT_VOLT)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_2_UNIT_ANGLE)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_2_UNIT_MW)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_2_UNIT_MVAR)->SetFont(&m_fontDef);

	GetDlgItem(IDC_GROUP1_2_STC_STATUS)->SetFont(&m_fontBold);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CGroup1MeasDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

HBRUSH CGroup1MeasDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_GROUP1_2_EDIT_AMP:
		case IDC_GROUP1_2_EDIT_VOLT:
		case IDC_GROUP1_2_EDIT_ANGLE:
		case IDC_GROUP1_2_EDIT_MW:
		case IDC_GROUP1_2_EDIT_MVAR:
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

void CGroup1MeasDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect																	_rect, rect;
	GetClientRect(&_rect);
	dc.FillSolidRect(_rect, WND_BG_DIALOG_COLOR);

	CPen																	pen, *poldpen;
	pen.CreatePen(PS_SOLID, DIALOG_SEPERATOR_PEN_WIDTH, DIALOG_SEPERATOR_PEN_COLOR);
	poldpen = (CPen*)dc.SelectObject(&pen);

	GetDlgItem(IDC_GROUP1_2_STC_MVAR)->GetWindowRect(&rect);
	ScreenToClient(rect);
	dc.MoveTo(_rect.left + 5, rect.bottom + 20);
	dc.LineTo(_rect.right - 5, rect.bottom + 20);

	dc.SelectObject(poldpen);
	pen.DeleteObject();
}

void CGroup1MeasDlg::SetData(int nCompType, int nCompIdx)
{
	m_nCompType = nCompType;
	m_nCompIdx = nCompIdx;

	if (nCompType == NDTYPE_SWITCH)//nCompIdx가 cbsw의 Idx이다.
	{
		GetDlgItem(IDC_GROUP1_2_COMBO_STATUS)->EnableWindow(TRUE);
		GetDlgItem(IDC_GROUP1_2_BTN_MODIFY)->EnableWindow(TRUE);

		if (GETVALUE(int, _T("cbsw_dyn_mea"), _T("cbsw_nwstat"), nCompIdx) == SW_OPEN)
			m_nStatus = SW_OPEN;
		else
			m_nStatus = SW_CLOSE;
		((CComboBox*)GetDlgItem(IDC_GROUP1_2_COMBO_STATUS))->SetCurSel(m_nStatus);

		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nCompIdx) >= 4)//수동
		{
			GetDlgItem(IDC_GROUP1_2_EDIT_AMP)->SendMessage(EM_SETREADONLY, TRUE);
			GetDlgItem(IDC_GROUP1_2_EDIT_VOLT)->SendMessage(EM_SETREADONLY, TRUE);
			GetDlgItem(IDC_GROUP1_2_EDIT_ANGLE)->SendMessage(EM_SETREADONLY, TRUE);

			SetDlgItemText(IDC_GROUP1_2_EDIT_AMP, _T("0"));
			SetDlgItemText(IDC_GROUP1_2_EDIT_VOLT, _T("0"));
			SetDlgItemText(IDC_GROUP1_2_EDIT_ANGLE, _T("0"));
			SetDlgItemText(IDC_GROUP1_2_EDIT_MW, _T("0"));
			SetDlgItemText(IDC_GROUP1_2_EDIT_MVAR, _T("0"));
		}
		else
		{
			GetDlgItem(IDC_GROUP1_2_EDIT_AMP)->SendMessage(EM_SETREADONLY, FALSE);
			GetDlgItem(IDC_GROUP1_2_EDIT_VOLT)->SendMessage(EM_SETREADONLY, FALSE);
			GetDlgItem(IDC_GROUP1_2_EDIT_ANGLE)->SendMessage(EM_SETREADONLY, FALSE);

			SetMeasureData();
		}
	}
	else
	{//나머지 타입인 경우는 일단 보류
		GetDlgItem(IDC_GROUP1_2_COMBO_STATUS)->EnableWindow(FALSE);
		GetDlgItem(IDC_GROUP1_2_BTN_MODIFY)->EnableWindow(FALSE);

		((CComboBox*)GetDlgItem(IDC_GROUP1_2_COMBO_STATUS))->SetCurSel(-1);
		m_nStatus = -1;

		GetDlgItem(IDC_GROUP1_2_EDIT_AMP)->SendMessage(EM_SETREADONLY, TRUE);
		GetDlgItem(IDC_GROUP1_2_EDIT_VOLT)->SendMessage(EM_SETREADONLY, TRUE);
		GetDlgItem(IDC_GROUP1_2_EDIT_ANGLE)->SendMessage(EM_SETREADONLY, TRUE);

		SetDlgItemText(IDC_GROUP1_2_EDIT_AMP, _T("0"));
		SetDlgItemText(IDC_GROUP1_2_EDIT_VOLT, _T("0"));
		SetDlgItemText(IDC_GROUP1_2_EDIT_ANGLE, _T("0"));
		SetDlgItemText(IDC_GROUP1_2_EDIT_MW, _T("0"));
		SetDlgItemText(IDC_GROUP1_2_EDIT_MVAR, _T("0"));
	}
}

void CGroup1MeasDlg::OnBnClickedGroup12RadioPhaseA()
{
	UpdateData();
	SetMeasureData();
}

void CGroup1MeasDlg::OnBnClickedGroup12RadioPhaseB()
{
	UpdateData();
	SetMeasureData();
}

void CGroup1MeasDlg::OnBnClickedGroup12RadioPhaseC()
{
	UpdateData();
	SetMeasureData();
}

void CGroup1MeasDlg::SetMeasureData()
{
	if (m_nCompIdx <= 0)													return;

	double																	dAmp(0), dkV(0), dAngle(0), dP(0), dQ(0), dPI = 3.141592654;
	CString																	szData;

	if (m_nCompType == NDTYPE_SWITCH)//nCompIdx가 cbsw의 Idx이다.
	{
		if (m_nPhaseType == 0)//A상
		{
			dAmp = GETVALUE(double, _T("cbsw_dyn_mea"), _T("cbsw_pameaamp"), m_nCompIdx);
			dkV = GETVALUE(double, _T("cbsw_dyn_mea"), _T("cbsw_pameakv"), m_nCompIdx);
			dAngle = GETVALUE(double, _T("cbsw_dyn_mea"), _T("cbsw_pameaadiff"), m_nCompIdx);
			dP = dkV * dAmp * cos(dAngle * dPI / 180.0);
			dQ = dkV * dAmp * sin(dAngle * dPI / 180.0);
		}
		else if (m_nPhaseType == 1)//B상
		{
			dAmp = GETVALUE(double, _T("cbsw_dyn_mea"), _T("cbsw_pbmeaamp"), m_nCompIdx);
			dkV = GETVALUE(double, _T("cbsw_dyn_mea"), _T("cbsw_pbmeakv"), m_nCompIdx);
			dAngle = GETVALUE(double, _T("cbsw_dyn_mea"), _T("cbsw_pbmeaadiff"), m_nCompIdx);
			dP = dkV * dAmp * cos(dAngle * dPI / 180.0);
			dQ = dkV * dAmp * sin(dAngle * dPI / 180.0);
		}
		else//C상
		{
			dAmp = GETVALUE(double, _T("cbsw_dyn_mea"), _T("cbsw_pcmeaamp"), m_nCompIdx);
			dkV = GETVALUE(double, _T("cbsw_dyn_mea"), _T("cbsw_pcmeakv"), m_nCompIdx);
			dAngle = GETVALUE(double, _T("cbsw_dyn_mea"), _T("cbsw_pcmeaadiff"), m_nCompIdx);
			dP = dkV * dAmp * cos(dAngle * dPI / 180.0);
			dQ = dkV * dAmp * sin(dAngle * dPI / 180.0);
		}
	}
	else
	{//나머지 타입인 경우는 일단 보류

	}

	szData.Format(_T("%.2lf"), dAmp);
	SetDlgItemText(IDC_GROUP1_2_EDIT_AMP, szData);

	szData.Format(_T("%.3lf"), dkV);
	SetDlgItemText(IDC_GROUP1_2_EDIT_VOLT, szData);

	szData.Format(_T("%.2lf"), dAngle);
	SetDlgItemText(IDC_GROUP1_2_EDIT_ANGLE, szData);

	szData.Format(_T("%.2lf"), dP);
	SetDlgItemText(IDC_GROUP1_2_EDIT_MW, szData);

	szData.Format(_T("%.2lf"), dQ);
	SetDlgItemText(IDC_GROUP1_2_EDIT_MVAR, szData);
}

void CGroup1MeasDlg::OnBnClickedGroup12BtnModify()
{
	if (ModifyMeasureData())
	{
		SetMeasureData();

		if (((CComboBox*)GetDlgItem(IDC_GROUP1_2_COMBO_STATUS))->GetCurSel() != m_nStatus)//상태값이 달라졌으면.
			((CMainFrame *)AfxGetMainWnd())->SendMessage(WM_MODIFY_MEASURE_MSG, 1L, 0L);
		else
			((CMainFrame *)AfxGetMainWnd())->SendMessage(WM_MODIFY_MEASURE_MSG, 0L, 0L);
	}
}

BOOL CGroup1MeasDlg::ModifyMeasureData()
{
	if (m_nCompIdx <= 0)													return FALSE;

	int																		nStatus;
	double																	dAmp(0), dkV(0), dAngle(0), dP(0), dQ(0), dPI = 3.141592654;
	CString																	szData;

	nStatus = ((CComboBox*)GetDlgItem(IDC_GROUP1_2_COMBO_STATUS))->GetCurSel();

	GetDlgItemText(IDC_GROUP1_2_EDIT_AMP, szData);
	if (InputErrorCheck(szData) == FALSE)									return FALSE;
	dAmp = _wtof(szData);

	GetDlgItemText(IDC_GROUP1_2_EDIT_VOLT, szData);
	if (InputErrorCheck(szData) == FALSE)									return FALSE;
	dkV = _wtof(szData);

	GetDlgItemText(IDC_GROUP1_2_EDIT_ANGLE, szData);
	if (InputErrorCheck(szData) == FALSE)									return FALSE;
	dAngle = _wtof(szData);

	if (m_nCompType == NDTYPE_SWITCH)//nCompIdx가 cbsw의 Idx이다.
	{
		PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_nwstat"), m_nCompIdx, nStatus);

		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), m_nCompIdx) < 4)
		{
			if (m_nPhaseType == 0)//A상
			{
				PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_pameaamp"), m_nCompIdx, dAmp);
				PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_pameakv"), m_nCompIdx, dkV);
				PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_pameaadiff"), m_nCompIdx, dAngle);
			}
			else if (m_nPhaseType == 1)//B상
			{
				PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_pbmeaamp"), m_nCompIdx, dAmp);
				PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_pbmeakv"), m_nCompIdx, dkV);
				PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_pbmeaadiff"), m_nCompIdx, dAngle);
			}
			else//C상
			{
				PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_pcmeaamp"), m_nCompIdx, dAmp);
				PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_pcmeakv"), m_nCompIdx, dkV);
				PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_pcmeaadiff"), m_nCompIdx, dAngle);
			}
		}
	}
	else
	{//나머지 타입인 경우는 일단 보류
		return FALSE;
	}

	return TRUE;
}

BOOL CGroup1MeasDlg::InputErrorCheck(CString szData)
{
	if (szData.IsEmpty())
	{
// 		CMessageDlg dlg(_T("경고"), MB_OK);
// 		dlg.SetMessage(_T("입력데이터가 없습니다."));
// 		dlg.DoModal();
		AfxMessageBox(_T("입력데이터가 없습니다."));
		return FALSE;
	}
	else
	{
		for (int i = 0; i < szData.GetLength(); i++)
		{
			if (!(szData.GetAt(i) >= '0' && szData.GetAt(i) <= '9' || szData.GetAt(i) == '.' || szData.GetAt(i) == '-'))
			{
// 				CMessageDlg dlg(_T("경고"), MB_OK);
// 				dlg.SetMessage(_T("입력데이터 오류입니다."));
// 				dlg.DoModal();
				AfxMessageBox(_T("입력데이터가 오류입니다."));
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL CGroup1MeasDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
