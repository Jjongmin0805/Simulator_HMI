// CustSetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "CustSetDlg.h"
#include "afxdialogex.h"


// CCustSetDlg 대화 상자

IMPLEMENT_DYNAMIC(CCustSetDlg, CPNOCtrl_SkinFrame_POP_Dialog)

CCustSetDlg::CCustSetDlg(int nHVCustIdx, CWnd* pParent /*=nullptr*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_CUST_SET_DLG, pParent)
{
	m_nHVCustIdx													= nHVCustIdx;
}

CCustSetDlg::~CCustSetDlg()
{
}

void CCustSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_CUST_TYPE, m_ctrConnTypeCom);
}


BEGIN_MESSAGE_MAP(CCustSetDlg, CPNOCtrl_SkinFrame_POP_Dialog)
	ON_BN_CLICKED(IDOK, &CCustSetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SET_RELAY, &CCustSetDlg::OnBnClickedBtnSetRelay)
END_MESSAGE_MAP()


// CCustSetDlg 메시지 처리기


BOOL CCustSetDlg::OnInitDialog()
{
	CPNOCtrl_SkinFrame_POP_Dialog::OnInitDialog();

	CString szData;
	szData.Format(_T("고객속성설정[HVCUS_IDX = %d]"), m_nHVCustIdx);
	SetWindowText(szData);

	CString															szCustName(_T(""));
	double															dCapacity(0.0);
	double															dTrCapa(0.0);
	double															dTrImp(0.0);
	int																nConnType(0);//1:Yg-Yg, 2:Yg-D, 3:D-Yg, 4:Y-d

	if (m_nHVCustIdx > 0)
	{
		szCustName													= GETSTRING(_T("hvcus_sta"), _T("hvcus_nm"), m_nHVCustIdx);
		dCapacity													= GETVALUE(double, _T("hvcus_sta"), _T("hvcus_con_kva"), m_nHVCustIdx);
		dTrCapa														= GETVALUE(double, _T("hvcus_sta"), _T("hvcus_itr_kva"), m_nHVCustIdx);
		dTrImp														= GETVALUE(double, _T("hvcus_sta"), _T("hvcus_itr_pz"), m_nHVCustIdx);
		nConnType													= GETVALUE(int, _T("hvcus_sta"), _T("hvcus_itr_wdc"), m_nHVCustIdx);
	}
	else
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);
	}

	SetDlgItemText(IDC_EDIT_CUST_NAME, szCustName);
	szData.Format(_T("%g"), dCapacity);
	SetDlgItemText(IDC_EDIT_CUST_CAPA, szData);
	szData.Format(_T("%g"), dTrCapa);
	SetDlgItemText(IDC_EDIT_CUST_TR_CAPA, szData);
	szData.Format(_T("%g"), dTrImp);
	SetDlgItemText(IDC_EDIT_CUST_TR_IMP, szData);

	m_ctrConnTypeCom.SetCurSel(nConnType - 1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCustSetDlg::OnBnClickedOk()
{
	CString															szData;
	double															dCapacity(0.0);
	double															dTrCapa(0.0);
	double															dTrImp(0.0);
	int																nConnType(0);//1:Yg-Yg, 2:Yg-D, 3:D-Yg, 4:Y-d

	GetDlgItemText(IDC_EDIT_CUST_CAPA, szData);
	dCapacity = _wtof(szData);
	GetDlgItemText(IDC_EDIT_CUST_TR_CAPA, szData);
	dTrCapa = _wtof(szData);
	GetDlgItemText(IDC_EDIT_CUST_TR_IMP, szData);
	dTrImp = _wtof(szData);

	nConnType = m_ctrConnTypeCom.GetCurSel();

	if (dCapacity < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[계약용량]"));
		dlg.DoModal();
		return;
	}

	if (dTrCapa < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[변압기용량]"));
		dlg.DoModal();
		return;
	}

	if (dTrImp < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[변압기임피던스]"));
		dlg.DoModal();
		return;
	}

	if (nConnType < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[변압기결선]"));
		dlg.DoModal();
		return;
	}

	PUTVALUE(_T("hvcus_sta"), _T("hvcus_con_kva"), m_nHVCustIdx, dCapacity);
	PUTVALUE(_T("hvcus_sta"), _T("hvcus_itr_kva"), m_nHVCustIdx, dTrCapa);
	PUTVALUE(_T("hvcus_sta"), _T("hvcus_itr_pz"), m_nHVCustIdx, dTrImp);
	PUTVALUE(_T("hvcus_sta"), _T("hvcus_itr_wdc"), m_nHVCustIdx, nConnType+1);

	CPNOCtrl_SkinFrame_POP_Dialog::OnOK();
}

void CCustSetDlg::OnBnClickedBtnSetRelay()
{
	int nPRDEIdx;
	nPRDEIdx = GETVALUE(int, _T("hvcus_sta"), _T("hvcus_ii_prde"), m_nHVCustIdx);

	if (nPRDEIdx <= 0)
	{
		CString szData;
		CMessageDlg dlg(_T("오류"), MB_OK);
		szData.Format(_T("해당 고객정보에 PRDE 매핑정보가 없습니다\nKasim정보를 확인하세요.\nHVCUS_STA(Idx = %d) - [HVCUS_II_PRDE]"), m_nHVCustIdx);
		dlg.SetMessage(szData);
		dlg.DoModal();
		return;

	}

	CRelaySetDlg dlg(nPRDEIdx, TRUE);
	dlg.DoModal();
}
