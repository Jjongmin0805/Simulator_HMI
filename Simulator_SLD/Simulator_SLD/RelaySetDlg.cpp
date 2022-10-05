// RelaySetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "RelaySetDlg.h"
#include "afxdialogex.h"


// CRelaySetDlg 대화 상자

IMPLEMENT_DYNAMIC(CRelaySetDlg, CPNOCtrl_SkinFrame_POP_Dialog)

CRelaySetDlg::CRelaySetDlg(int nPrdeIdx, BOOL bCustomer, CWnd* pParent /*=nullptr*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_RELAY_SET_DLG, pParent)
{
	m_nPRDEIdx = nPrdeIdx;
	m_bCustomer = bCustomer;
}

CRelaySetDlg::~CRelaySetDlg()
{
}

void CRelaySetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_OCR_TYPE, m_ctrOCRTypeCom);
	DDX_Control(pDX, IDC_COM_OCGR_TYPE, m_ctrOCGRTypeCom);
}


BEGIN_MESSAGE_MAP(CRelaySetDlg, CPNOCtrl_SkinFrame_POP_Dialog)
	ON_BN_CLICKED(IDOK, &CRelaySetDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COM_OCR_TYPE, &CRelaySetDlg::OnCbnSelchangeComOcrType)
	ON_CBN_SELCHANGE(IDC_COM_OCGR_TYPE, &CRelaySetDlg::OnCbnSelchangeComOcgrType)
END_MESSAGE_MAP()


// CRelaySetDlg 메시지 처리기
BOOL CRelaySetDlg::OnInitDialog()
{
	CPNOCtrl_SkinFrame_POP_Dialog::OnInitDialog();

	if (m_bCustomer)
		SetWindowText(_T("고객계전기 설정"));

	UpdateCombo();

	int														nCTRatio[2];
	int														nTypeidx[2];
	double													dTabVal[2];
	double													dLever[2];
	double													dSTabVal[2];

	nCTRatio[0]												= GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocr_ctr"), m_nPRDEIdx);
	nCTRatio[1]												= GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocgr_ctr"), m_nPRDEIdx);
	nTypeidx[0]												= GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocr_ii_machine"), m_nPRDEIdx);
	nTypeidx[1]												= GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocgr_ii_machine"), m_nPRDEIdx);
	dTabVal[0]												= GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocr_pickup_c"), m_nPRDEIdx) / nCTRatio[0];
	dTabVal[1]												= GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgr_pickup_c"), m_nPRDEIdx) / nCTRatio[1];
	dLever[0]												= GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocrf_tms"), m_nPRDEIdx);
	dLever[1]												= GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgrf_tms"), m_nPRDEIdx);
	dSTabVal[0]												= GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocr_iic"), m_nPRDEIdx) / nCTRatio[0];
	dSTabVal[1]												= GETVALUE(double, _T("prde_dyn_uin"), _T("prde_ocgr_iic"), m_nPRDEIdx) / nCTRatio[1];

	m_ctrOCRTypeCom.SetCurSel(nTypeidx[0]);
	OnCbnSelchangeComOcrType();

	m_ctrOCGRTypeCom.SetCurSel(nTypeidx[1]);
	OnCbnSelchangeComOcgrType();

	CString													szData;
	szData.Format(_T("%d"), nCTRatio[0] * 5);
	SetDlgItemText(IDC_EDIT_OCR_CT, szData);
	szData.Format(_T("%g"), dTabVal[0]);
	SetDlgItemText(IDC_EDIT_OCR_TAB, szData);
	szData.Format(_T("%g"), dTabVal[1]);
	SetDlgItemText(IDC_EDIT_OCGR_TAB, szData);

	szData.Format(_T("%d"), nCTRatio[1] * 5);
	SetDlgItemText(IDC_EDIT_OCGR_CT, szData);
	szData.Format(_T("%g"), dLever[0]);
	SetDlgItemText(IDC_EDIT_OCR_LEVER, szData);
	szData.Format(_T("%g"), dLever[1]);
	SetDlgItemText(IDC_EDIT_OCGR_LEVER, szData);

	szData.Format(_T("%g"), dSTabVal[0]);
	SetDlgItemText(IDC_EDIT_OCR_STAB, szData);
	szData.Format(_T("%g"), dSTabVal[1]);
	SetDlgItemText(IDC_EDIT_OCGR_STAB, szData);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRelaySetDlg::UpdateCombo()
{
	m_ctrOCRTypeCom.AddString( _T("선택없음") );
	m_ctrOCGRTypeCom.AddString( _T("선택없음") );

	CString														szName;
	for (int i = 1; i <= 100; i++)
	{
		szName = GETSTRING(_T("machine_dyn_uin"), _T("machine_nm"), i);
		if (szName.IsEmpty())
			break;

		m_ctrOCRTypeCom.AddString(szName);
		m_ctrOCGRTypeCom.AddString(szName);
	}
}

void CRelaySetDlg::OnBnClickedOk()
{
	CString													szData;
	int														nCTRatio[2];
	int														nTypeidx[2] = { 0, 0 };
	CString													szMachineNm[2];
	int														nTccSetIdx[2] = { 12, 12 };
	double													dTabVal[2] = { 0, 0 };
	double													dLever[2] = { 0, 0 };
	double													dSTabVal[2] = { 0, 0};

	GetDlgItemText(IDC_EDIT_OCR_CT, szData);
	nCTRatio[0] = _wtoi(szData);
	if (nCTRatio <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[OCR CT 비]"));
		dlg.DoModal();
		return;
	}
	nCTRatio[0] /= 5;

	GetDlgItemText(IDC_EDIT_OCGR_CT, szData);
	nCTRatio[1] = _wtoi(szData);
	if (nCTRatio[1] <= 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[OCGR CT 비]"));
		dlg.DoModal();
		return;
	}
	nCTRatio[1] /= 5;

	nTypeidx[0] = m_ctrOCRTypeCom.GetCurSel();
	if (nTypeidx[0] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[OCR 기기형식]"));
		dlg.DoModal();
		return;
	}
	m_ctrOCRTypeCom.GetLBText(nTypeidx[0], szMachineNm[0]);

	nTypeidx[1] = m_ctrOCGRTypeCom.GetCurSel();
	if (nTypeidx[0] < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[OCGR 기기형식]"));
		dlg.DoModal();
		return;
	}
	m_ctrOCGRTypeCom.GetLBText(nTypeidx[1], szMachineNm[1]);

	if( nTypeidx[0] > 0 )
	{
		nTccSetIdx[0] = GETVALUE(int, _T("machine_dyn_uin"), _T("machine_ii_tccset"), nTypeidx[0]);

		GetDlgItemText(IDC_EDIT_OCR_TAB, szData);
		dTabVal[0] = _wtof(szData);
	
		GetDlgItemText(IDC_EDIT_OCR_LEVER, szData);
		dLever[0] = _wtof(szData);

		GetDlgItemText(IDC_EDIT_OCR_STAB, szData);
		dSTabVal[0] = _wtof(szData);

		if (dTabVal[0] <= 0)
		{
			CMessageDlg dlg(_T("경고"), MB_OK);
			dlg.SetMessage(_T("입력데이터를 확인하세요[OCR 한시탭]"));
			dlg.DoModal();
			return;
		}
		if (dLever[0] <= 0)
		{
			CMessageDlg dlg(_T("경고"), MB_OK);
			dlg.SetMessage(_T("입력데이터를 확인하세요[OCR 레버]"));
			dlg.DoModal();
			return;
		}
		if (dSTabVal[0] <= 0)
		{
			CMessageDlg dlg(_T("경고"), MB_OK);
			dlg.SetMessage(_T("입력데이터를 확인하세요[OCR 순시탭]"));
			dlg.DoModal();
			return;
		}
	}

	if (nTypeidx[1] > 0)
	{
		nTccSetIdx[1] = GETVALUE(int, _T("machine_dyn_uin"), _T("machine_ii_tccset"), nTypeidx[1]);

		GetDlgItemText(IDC_EDIT_OCGR_TAB, szData);
		dTabVal[1] = _wtof(szData);
	
		GetDlgItemText(IDC_EDIT_OCGR_LEVER, szData);
		dLever[1] = _wtof(szData);

		GetDlgItemText(IDC_EDIT_OCGR_STAB, szData);
		dSTabVal[1] = _wtof(szData);

		if (dTabVal[1] <= 0)
		{
			CMessageDlg dlg(_T("경고"), MB_OK);
			dlg.SetMessage(_T("입력데이터를 확인하세요[OCGR 한시탭]"));
			dlg.DoModal();
			return;
		}

		if (dLever[1] <= 0)
		{
			CMessageDlg dlg(_T("경고"), MB_OK);
			dlg.SetMessage(_T("입력데이터를 확인하세요[OCGR 레버]"));
			dlg.DoModal();
			return;
		}

		if (dSTabVal[1] <= 0)
		{
			CMessageDlg dlg(_T("경고"), MB_OK);
			dlg.SetMessage(_T("입력데이터를 확인하세요[OCGR 순시탭]"));
			dlg.DoModal();
			return;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//탭값 자동 보정
	double dAutoValue;

	//OCR 한시탭 설정확인
	dAutoValue = SetAutoValue(dTabVal[0], nTypeidx[0], 0, 0);
	if (dAutoValue < 0)
	{
		CMessageDlg dlg(_T("OCR 한시탭이 데이터 오류"), MB_OK);
		szData.Format(_T("OCR 한시탭 범위설정데이터가 없습니다."));
		dlg.SetMessage(szData);
		dlg.DoModal();
		return;
	}
	if (dAutoValue)
	{
		szData.Format(_T("OCR 한시탭이 설정범위를 벗어났습니다.\n자동설정 하시겠습니까?\nOCR 한시탭 = %g"), dAutoValue);
		CMessageDlg dlg(_T("경고"), MB_YESNO);
		dlg.SetMessage(szData);
		if (dlg.DoModal() == IDCANCEL)
			return;

		dTabVal[0] = dAutoValue;
		szData.Format(_T("%g"), dTabVal[0]);
		SetDlgItemText(IDC_EDIT_OCR_TAB, szData);
	}

	//OCR 순시탭 설정확인
	dAutoValue = SetAutoValue(dSTabVal[0], nTypeidx[0], 0, 1);
	if (dAutoValue < 0)
	{
		CMessageDlg dlg(_T("OCR 순시탭이 데이터 오류"), MB_OK);
		szData.Format(_T("OCR 순시탭 범위설정데이터가 없습니다."));
		dlg.SetMessage(szData);
		dlg.DoModal();
		return;
	}
	if (dAutoValue)
	{
		szData.Format(_T("OCR 순시탭이 설정범위를 벗어났습니다.\n자동설정 하시겠습니까?\nOCR 순시탭 = %g"), dAutoValue);
		CMessageDlg dlg(_T("경고"), MB_YESNO);
		dlg.SetMessage(szData);
		if (dlg.DoModal() == IDCANCEL)
			return;

		dSTabVal[0] = dAutoValue;
		szData.Format(_T("%g"), dSTabVal[0]);
		SetDlgItemText(IDC_EDIT_OCR_STAB, szData);
	}

	//OCGR 한시탭 설정확인
	dAutoValue = SetAutoValue(dTabVal[1], nTypeidx[1], 1, 0);
	if (dAutoValue < 0)
	{
		CMessageDlg dlg(_T("OCGR 한시탭이 데이터 오류"), MB_OK);
		szData.Format(_T("OCGR 한시탭 범위설정데이터가 없습니다."));
		dlg.SetMessage(szData);
		dlg.DoModal();
		return;
	}
	if (dAutoValue)
	{
		szData.Format(_T("OCGR 한시탭이 설정범위를 벗어났습니다.\n자동설정 하시겠습니까?\nOCGR 한시탭 = %g"), dAutoValue);
		CMessageDlg dlg(_T("경고"), MB_YESNO);
		dlg.SetMessage(szData);
		if (dlg.DoModal() == IDCANCEL)
			return;

		dTabVal[1] = dAutoValue;
		szData.Format(_T("%g"), dTabVal[1]);
		SetDlgItemText(IDC_EDIT_OCGR_TAB, szData);
	}

	//OCGR 순시탭 설정확인
	dAutoValue = SetAutoValue(dSTabVal[1], nTypeidx[1], 1, 1);
	if (dAutoValue < 0)
	{
		CMessageDlg dlg(_T("OCGR 순시탭이 데이터 오류"), MB_OK);
		szData.Format(_T("OCGR 순시탭 범위설정데이터가 없습니다."));
		dlg.SetMessage(szData);
		dlg.DoModal();
		return;
	}
	if (dAutoValue)
	{
		szData.Format(_T("OCGR 순시탭이 설정범위를 벗어났습니다.\n자동설정 하시겠습니까?\nOCGR 순시탭 = %g"), dAutoValue);
		CMessageDlg dlg(_T("경고"), MB_YESNO);
		dlg.SetMessage(szData);
		if (dlg.DoModal() == IDCANCEL)
			return;

		dSTabVal[1] = dAutoValue;
		szData.Format(_T("%g"), dSTabVal[1]);
		SetDlgItemText(IDC_EDIT_OCGR_STAB, szData);
	}

	//////////////////////////////////////////////////////////////////////////

	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocr_ctr"), m_nPRDEIdx, nCTRatio[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgr_ctr"), m_nPRDEIdx, nCTRatio[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocr_ii_machine"), m_nPRDEIdx, nTypeidx[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgr_ii_machine"), m_nPRDEIdx, nTypeidx[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocr_machine_nm"), m_nPRDEIdx, szMachineNm[0].GetBuffer());
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgr_machine_nm"), m_nPRDEIdx, szMachineNm[1].GetBuffer());
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrf_ii_tccset"), m_nPRDEIdx, nTccSetIdx[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrf_ii_tccset"), m_nPRDEIdx, nTccSetIdx[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocr_pickup_c"), m_nPRDEIdx, dTabVal[0]*nCTRatio[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgr_pickup_c"), m_nPRDEIdx, dTabVal[1]*nCTRatio[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocrf_tms"), m_nPRDEIdx, dLever[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgrf_tms"), m_nPRDEIdx, dLever[1]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocr_iic"), m_nPRDEIdx, dSTabVal[0]*nCTRatio[0]);
	PUTVALUE(_T("prde_dyn_uin"), _T("prde_ocgr_iic"), m_nPRDEIdx, dSTabVal[1] * nCTRatio[1]);

	CPNOCtrl_SkinFrame_POP_Dialog::OnOK();
}


void CRelaySetDlg::OnCbnSelchangeComOcrType()
{
	int nCurSel;
	nCurSel = m_ctrOCRTypeCom.GetCurSel();

	if (nCurSel < 0)
	{
		SetDlgItemText(IDC_EDIT_OCR_CURVE, _T("-"));
		GetDlgItem(IDC_EDIT_OCR_TAB)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OCR_LEVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OCR_STAB)->EnableWindow(FALSE);
	}
	else if (nCurSel == 0)
	{
		CString szName;
		szName = GETSTRING(_T("tccset_sta"), _T("tccset_nm"), 12);//계전기 기본값으로 고정(12)
		SetDlgItemText(IDC_EDIT_OCR_CURVE, szName);

		GetDlgItem(IDC_EDIT_OCR_TAB)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OCR_LEVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OCR_STAB)->EnableWindow(FALSE);
	}
	else
	{
		int nTccSetIdx;
		nTccSetIdx = GETVALUE(int, _T("machine_dyn_uin"), _T("machine_ii_tccset"), nCurSel);
		if (nTccSetIdx < 1) nTccSetIdx = 1;

		CString szName;
		szName = GETSTRING(_T("tccset_sta"), _T("tccset_nm"), nTccSetIdx);
		SetDlgItemText(IDC_EDIT_OCR_CURVE, szName);

		GetDlgItem(IDC_EDIT_OCR_TAB)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_OCR_LEVER)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_OCR_STAB)->EnableWindow(TRUE);
	}
}

void CRelaySetDlg::OnCbnSelchangeComOcgrType()
{
	int nCurSel;
	nCurSel = m_ctrOCGRTypeCom.GetCurSel();

	if (nCurSel < 0)
	{
		SetDlgItemText(IDC_EDIT_OCGR_CURVE, _T("-"));
		GetDlgItem(IDC_EDIT_OCGR_TAB)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OCGR_LEVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OCGR_STAB)->EnableWindow(FALSE);
	}
	else if (nCurSel == 0)
	{
		CString szName;
		szName = GETSTRING(_T("tccset_sta"), _T("tccset_nm"), 12);//계전기 기본값으로 고정(12)
		SetDlgItemText(IDC_EDIT_OCGR_CURVE, szName);

		GetDlgItem(IDC_EDIT_OCGR_TAB)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OCGR_LEVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OCGR_STAB)->EnableWindow(FALSE);
	}
	else
	{
		int nTccSetIdx;
		nTccSetIdx = GETVALUE(int, _T("machine_dyn_uin"), _T("machine_ii_tccset"), nCurSel);
		if (nTccSetIdx < 1) nTccSetIdx = 1;

		CString szName;
		szName = GETSTRING(_T("tccset_sta"), _T("tccset_nm"), nTccSetIdx);
		SetDlgItemText(IDC_EDIT_OCGR_CURVE, szName);

		GetDlgItem(IDC_EDIT_OCGR_TAB)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_OCGR_LEVER)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_OCGR_STAB)->EnableWindow(TRUE);
	}
}

double CRelaySetDlg::SetAutoValue(double dValue, int nMachineID, int nOgKind, int nFdKind)
{
	if (nMachineID == 0)//선택없음이면 그냥 패스
		return 0;

	int nAdKind;

	nAdKind = CheckRelayAD(nMachineID);

	if( nAdKind == 0 )
	{
		double dStart(0), dEnd(-1), dStep(1);

		int nCount;
		nCount = theAppDataMng->GetTableRealCount(_T("relay_d_tap_dyn_uin"));
		for (int nIdx = 1; nIdx <= nCount; nIdx++)
		{
			if( GETVALUE(int, _T("relay_d_tap_dyn_uin"), _T("relay_ii_machine"), nIdx ) != nMachineID )
				continue;

			if (GETVALUE(int, _T("relay_d_tap_dyn_uin"), _T("relay_og_sep"), nIdx) != nOgKind)
				continue;

			if (GETVALUE(int, _T("relay_d_tap_dyn_uin"), _T("relay_fd_sep"), nIdx) != nFdKind)
				continue;

			dStart	= GETVALUE(double, _T("relay_d_tap_dyn_uin"), _T("relay_tap_start"), nIdx);
			dEnd	= GETVALUE(double, _T("relay_d_tap_dyn_uin"), _T("relay_tap_end"), nIdx);
			dStep	= GETVALUE(double, _T("relay_d_tap_dyn_uin"), _T("relay_tap_step"), nIdx);
			
			break;
		}

		for (double dTap = dStart; dTap <= (dEnd+DOUBLE_COMP_RANGE_VALUE); dTap += dStep)
		{
			if (abs(dTap - dValue) <= DOUBLE_COMP_RANGE_VALUE )
				return 0;

			if (dTap > dValue)
				return dTap;
		}

		return dEnd;
	}
	else
	{
		double dTapValue(-1);
		int nCount;
		nCount = theAppDataMng->GetTableRealCount(_T("relay_a_tap_dyn_uin"));
		for (int nIdx = 1; nIdx <= nCount; nIdx++)
		{
			if (GETVALUE(int, _T("relay_a_tap_dyn_uin"), _T("relay_ii_machine"), nIdx) != nMachineID)
				continue;

			if (GETVALUE(int, _T("relay_a_tap_dyn_uin"), _T("relay_og_sep"), nIdx) != nOgKind)
				continue;

			if (GETVALUE(int, _T("relay_a_tap_dyn_uin"), _T("relay_fd_sep"), nIdx) != nFdKind)
				continue;

			dTapValue = GETVALUE(double, _T("relay_d_tap_dyn_uin"), _T("relay_tap_value"), nIdx);

			if (abs(dTapValue - dValue) <= DOUBLE_COMP_RANGE_VALUE )
				return 0;

			if (dTapValue > dValue)
				return dTapValue;
		}

		return dTapValue;
	}
}

int CRelaySetDlg::CheckRelayAD(int nMachineID)
{
	int nCount;
	nCount = theAppDataMng->GetTableRealCount(_T("relay_type_dyn_uin"));
	for (int nIdx = 1; nIdx <= nCount; nIdx++)
	{
		if (GETVALUE(int, _T("relay_type_dyn_uin"), _T("relay_ii_machine"), nIdx) == nMachineID)
			return GETVALUE(int, _T("relay_type_dyn_uin"), _T("relay_ad_sep"), nIdx);
	}

	return -1;
}