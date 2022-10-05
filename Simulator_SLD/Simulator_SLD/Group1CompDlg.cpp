// Group1CompDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "Group1CompDlg.h"
#include "afxdialogex.h"
#include "RelaySetDlg.h"
#include "RelcoserSetDlg.h"
#include "DgSetDlg.h"
#include "CustSetDlg.h"
#include "CEFISetDlg.h"

#include "MainFrm.h"

// CGroup1CompDlg 대화 상자

IMPLEMENT_DYNAMIC(CGroup1CompDlg, CDialog)

CGroup1CompDlg::CGroup1CompDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GROUP1_COMP_DLG, pParent)
{
	for (int i = 0; i < 5; i++)											m_szData[i] = _T("");
	for (int i = 0; i < 2; i++)											m_nData[i] = -1;

	m_nSelNodeIdx = 0;
	m_nALTSCBSW = 0;
	m_nSelNodeType = 0;
	m_nCbswIdx = 0;
}

CGroup1CompDlg::~CGroup1CompDlg()
{
}

void CGroup1CompDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGroup1CompDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_GROUP1_1_BTN_PROTECT_SET, &CGroup1CompDlg::OnBnClickedGroup11BtnProtectSet)
	ON_BN_CLICKED(IDC_GROUP1_1_BTN_MODIFY, &CGroup1CompDlg::OnBnClickedGroup11BtnModify)
END_MESSAGE_MAP()


// CGroup1CompDlg 메시지 처리기
BOOL CGroup1CompDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_fontDef.CreateFont(17, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("맑은 고딕"));
	m_fontBold.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("맑은 고딕"));

	GetDlgItem(IDC_GROUP1_1_STC_INFO)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_1_STC_STATUS)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP1_1_STC_INFO_SUBSNM)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_1_STC_INFO_DLNM)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_1_STC_INFO_POLENM)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_1_STC_INFO_TYPE)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_1_STC_STATUS_STATUS)->SetFont(&m_fontDef);
	GetDlgItem(IDC_GROUP1_1_STC_STATUS_MEAS)->SetFont(&m_fontDef);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CGroup1CompDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

HBRUSH CGroup1CompDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_GROUP1_1_EDIT_INFO_SUBSNM:
		case IDC_GROUP1_1_EDIT_INFO_DLNM:
		case IDC_GROUP1_1_EDIT_INFO_POLENM:
		case IDC_GROUP1_1_EDIT_INFO_TYPE:
		case IDC_GROUP1_1_EDIT_STATUS_MEAS:
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

void CGroup1CompDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect																	_rect, rect;
	GetClientRect(&_rect);
	dc.FillSolidRect(_rect, WND_BG_DIALOG_COLOR);

	CPen																	pen, *poldpen;
	pen.CreatePen(PS_SOLID, DIALOG_SEPERATOR_PEN_WIDTH, DIALOG_SEPERATOR_PEN_COLOR);
	poldpen = (CPen*)dc.SelectObject(&pen);

	GetDlgItem(IDC_GROUP1_1_STC_INFO)->GetWindowRect(&rect);
	ScreenToClient(rect);
	dc.MoveTo(rect.right, rect.CenterPoint().y);
	dc.LineTo(_rect.right - 5, rect.CenterPoint().y);

	GetDlgItem(IDC_GROUP1_1_STC_STATUS)->GetWindowRect(&rect);
	ScreenToClient(rect);
	dc.MoveTo(rect.right, rect.CenterPoint().y);
	dc.LineTo(_rect.right - 5, rect.CenterPoint().y);

	dc.SelectObject(poldpen);
	pen.DeleteObject();
}

void CGroup1CompDlg::UpData()
{
	GetDlgItem(IDC_GROUP1_1_EDIT_INFO_SUBSNM)->SetWindowText(m_szData[0]);
	GetDlgItem(IDC_GROUP1_1_EDIT_INFO_DLNM)->SetWindowText(m_szData[1]);
	GetDlgItem(IDC_GROUP1_1_EDIT_INFO_POLENM)->SetWindowText(m_szData[2]);
	GetDlgItem(IDC_GROUP1_1_EDIT_INFO_TYPE)->SetWindowText(m_szData[4]);

	((CComboBox*)GetDlgItem(IDC_GROUP1_1_COMBO_STATUS))->SetCurSel(m_nData[0]);

	if (m_nData[1] == SW_ONLINE)											GetDlgItem(IDC_GROUP1_1_EDIT_STATUS_MEAS)->SetWindowText(_T("YES"));
	else if (m_nData[1] == SW_OFFLINE)										GetDlgItem(IDC_GROUP1_1_EDIT_STATUS_MEAS)->SetWindowText(_T("NO"));
	else																	GetDlgItem(IDC_GROUP1_1_EDIT_STATUS_MEAS)->SetWindowText(_T(""));
}

void CGroup1CompDlg::SetData(CNodeView* pNodeView, int nDLIdx)
{
	if (pNodeView)
	{
		int																	nMtrIdx, nSSIdx;
		nMtrIdx = GETVALUE(int, _T("dl_sta"), _T("dl_ii_mtr"), nDLIdx);
		nSSIdx = GETVALUE(int, _T("mtr_sta"), _T("mtr_ii_ss"), nMtrIdx);

		m_szData[0] = GETSTRING(_T("ss_sta"), _T("ss_nm"), nSSIdx);
		m_szData[1] = GETSTRING(_T("dl_sta"), _T("dl_nm"), nDLIdx);
		m_szData[2] = pNodeView->m_szLoc;

		if (pNodeView->IsCBreaker())										m_szData[3] = _T("-");
		else
		{
			if (pNodeView->m_szLocNo.IsEmpty())								m_szData[3] = _T("-");
			else															m_szData[3] = pNodeView->m_szLocNo;
		}

		m_szData[4] = pNodeView->GetKindName();

		m_nData[0] = pNodeView->m_bStatus;
		m_nData[1] = pNodeView->IsAuto() ? SW_ONLINE : SW_OFFLINE;

		int																				nNodeIdx(0);

		m_nALTSCBSW																		= 0;
		if (pNodeView->m_nTongID)
		{//멀티이고, 멀티의 다음노드가 가상더미이다. 즉, 다회로 전원측이면
			if (pNodeView->m_pCenter && pNodeView->m_pCenter->m_nSwKindID == -1000)		nNodeIdx = pNodeView->m_nNDID[0];//FND로 확인
			else																		nNodeIdx = pNodeView->m_nNDID[1];//TND로 확인
		}
		else
		{
			if (pNodeView->m_nNDID[1] == 0)												nNodeIdx = pNodeView->m_nNDID[0];//NODE속성이면 ND로 확인
			else																		nNodeIdx = pNodeView->m_nNDID[1];//BR속성이면 TND로 확인
		}

		if (pNodeView->IsSwitch() || (pNodeView->m_nALTSCBSW > 0) )
		{
			GetDlgItem(IDC_GROUP1_1_COMBO_STATUS)->EnableWindow(TRUE);
			GetDlgItem(IDC_GROUP1_1_BTN_MODIFY)->EnableWindow(TRUE);

			if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNodeIdx) > 0)			m_nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNodeIdx);
			else																		m_nCbswIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNodeIdx);

			if (pNodeView->m_nALTSCBSW > 0)
			{
				if (GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNodeIdx) > 0)		m_nALTSCBSW = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), pNodeView->m_nALTSCBSW);
				else																	m_nALTSCBSW = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), pNodeView->m_nALTSCBSW);
			}
		}
		else
		{
			GetDlgItem(IDC_GROUP1_1_COMBO_STATUS)->EnableWindow(FALSE);
			GetDlgItem(IDC_GROUP1_1_BTN_MODIFY)->EnableWindow(FALSE);
			m_nCbswIdx																	= 0;
		}

		if (pNodeView->m_nKCIMType == KCIMTYPE_CB)//CB
		{
			GetDlgItem(IDC_GROUP1_1_BTN_PROTECT_SET)->EnableWindow(TRUE);
			m_nSelNodeIdx = nNodeIdx;
			m_nSelNodeType = SEL_TYPE_CB;
		}
		else if (pNodeView->m_nKCIMType == KCIMTYPE_RC)//RC
		{
			GetDlgItem(IDC_GROUP1_1_BTN_PROTECT_SET)->EnableWindow(TRUE);
			m_nSelNodeIdx = nNodeIdx;
			m_nSelNodeType = SEL_TYPE_RC;
		}
		else if (pNodeView->m_nTongID > 0 && pNodeView->m_nKCIMType == KCIMTYPE_EFI)//MCA
		{
			GetDlgItem(IDC_GROUP1_1_BTN_PROTECT_SET)->EnableWindow(TRUE);
			m_nSelNodeIdx = nNodeIdx;
			m_nSelNodeType = SEL_TYPE_MCA;
		}
		else if (pNodeView->m_nKCIMType == KCIMTYPE_EFI)//EFI
		{
			GetDlgItem(IDC_GROUP1_1_BTN_PROTECT_SET)->EnableWindow(TRUE);
			m_nSelNodeIdx = nNodeIdx;
			m_nSelNodeType = SEL_TYPE_EFI;
		}
		else if (pNodeView->m_nSwKindID == NDTYPE_GEN)//발전기
		{
			GetDlgItem(IDC_GROUP1_1_BTN_PROTECT_SET)->EnableWindow(TRUE);
			m_nSelNodeIdx = nNodeIdx;
			m_nSelNodeType = SEL_TYPE_DG;
		}
		else if (pNodeView->m_nSwKindID == NDTYPE_CUSTOMER)//고객
		{
			GetDlgItem(IDC_GROUP1_1_BTN_PROTECT_SET)->EnableWindow(TRUE);
			m_nSelNodeIdx = nNodeIdx;
			m_nSelNodeType = SEL_TYPE_CUSTOMER;
		}
		else
		{
			GetDlgItem(IDC_GROUP1_1_BTN_PROTECT_SET)->EnableWindow(FALSE);
			m_nSelNodeIdx = 0;
			m_nSelNodeType = 0;
		}

	}
	else
	{
		for (int i = 0; i < 5; i++)											m_szData[i] = _T("");
		for (int i = 0; i < 2; i++)											m_nData[i] = -1;
	}
	
	UpData();
}

BOOL CGroup1CompDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CGroup1CompDlg::OnBnClickedGroup11BtnProtectSet()
{
	if (m_nSelNodeType <= SEL_TYPE_EFI)
	{
		int nPRDEIdx;

		nPRDEIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_prde"), m_nCbswIdx);

		if (nPRDEIdx == 0)
		{
			AfxMessageBox(_T("prde연결정보를 찾을 수 없습니다.\ncbsw_sta의 cbsw_ii_prde를 확인하세요"));
			return;
		}

		if (m_nSelNodeType == SEL_TYPE_CB)
		{
			CRelaySetDlg dlg(nPRDEIdx, FALSE);
			dlg.DoModal();
		}
		else if (m_nSelNodeType == SEL_TYPE_RC)
		{
			CRelcoserSetDlg dlg(nPRDEIdx);
			dlg.DoModal();
		}
		else
		{
			CEFISetDlg dlg(nPRDEIdx, m_nSelNodeType);
			dlg.DoModal();
		}
	}
	else if (m_nSelNodeType == SEL_TYPE_DG)
	{
		int nGENIdx;
		nGENIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_gen"), m_nSelNodeIdx);

		if (nGENIdx > 0)
		{
			CDgSetDlg dlg(nGENIdx);
			dlg.DoModal();
		}
	}
	else if (m_nSelNodeType == SEL_TYPE_CUSTOMER)
	{
		int nGNDIdx, nHVCusIdx(0);
		nGNDIdx = GETVALUE(int, _T("nd_sta"), _T("nd_ii_gnd"), m_nSelNodeIdx);
		if (nGNDIdx)
			nHVCusIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_hvcus"), nGNDIdx);

		if (nHVCusIdx > 0)
		{
			CCustSetDlg dlg(nHVCusIdx);
			dlg.DoModal();
		}
	}
}

void CGroup1CompDlg::OnBnClickedGroup11BtnModify()
{
	int nStatus;
	nStatus = (int)((CComboBox*)GetDlgItem(IDC_GROUP1_1_COMBO_STATUS))->GetCurSel();

	if (nStatus != m_nData[0])//상태값이 달라졌으면.
	{
		PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_nwstat"), m_nCbswIdx, nStatus == 0 ? SW_OPEN : SW_CLOSE);

		if( m_nALTSCBSW > 0 )
			PUTVALUE(_T("cbsw_dyn_mea"), _T("cbsw_nwstat"), m_nALTSCBSW, nStatus == 0 ? SW_CLOSE : SW_OPEN);

		((CMainFrame *)AfxGetMainWnd())->SendMessage(WM_MODIFY_MEASURE_MSG, 1L, 0L);
	}
}
