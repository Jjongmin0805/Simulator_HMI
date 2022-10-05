// CView_PDVR_rst_TRDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CView_PDVR_rst_TRDlg.h"
#include "afxdialogex.h"
#include "resource.h"

// CView_PDVR_rst_TRDlg 대화 상자

IMPLEMENT_DYNAMIC(CView_PDVR_rst_TRDlg, CDialogEx)

CView_PDVR_rst_TRDlg::CView_PDVR_rst_TRDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PDVR_TR_SET_DLG, pParent)
{
	m_nIndex = -1;
	m_nMode = 0;
}

CView_PDVR_rst_TRDlg::~CView_PDVR_rst_TRDlg()
{
}

void CView_PDVR_rst_TRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PDVR_TR_SET_DLG_COMBO1, m_ctrCombo);
}


BEGIN_MESSAGE_MAP(CView_PDVR_rst_TRDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PDVR_TR_SET_DLG_BTN_1, &CView_PDVR_rst_TRDlg::OnBnClickedPdvrTrSetDlgBtn1)
END_MESSAGE_MAP()


// CView_PDVR_rst_TRDlg 메시지 처리기


BOOL CView_PDVR_rst_TRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ctrCombo.AddString(_T("LDC 운전"));
	m_ctrCombo.AddString(_T("DVM 운전"));
	m_ctrCombo.AddString(_T("LDC+DVM 운전"));
	m_ctrCombo.AddString(_T("송출 전압 고정"));

	SetData_TRInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CView_PDVR_rst_TRDlg::SetData_TRInfo()
{
	if (m_nIndex == -1)
		return;

	double dValue[9];
	int	   nValue;
	CString strData[9];

	dValue[0] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_DVMMXV"), m_nIndex);
	dValue[1] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_DVMMNV"), m_nIndex);
	dValue[2] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PATBSVL"), m_nIndex);
	dValue[3] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PADEV"), m_nIndex);
	dValue[4] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PACOMPR"), m_nIndex);
	dValue[5] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PACOMPX"), m_nIndex);
	/*dValue[2] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PTRVL"), m_nIndex);
	dValue[3] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_CTRCH"), m_nIndex);
	dValue[4] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_CTRCL"), m_nIndex);
	dValue[5] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PATBSVL"), m_nIndex);
	dValue[6] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PADEV"), m_nIndex);
	dValue[7] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PACOMPR"), m_nIndex);
	dValue[8] = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PACOMPX"), m_nIndex);*/

	nValue = GETVALUE(int, _T("PDVROPT_DYN_UIN"), _T("pdvropt_oltcmodel"), 1);

	strData[0].Format(_T("%g"), dValue[0]);
	strData[1].Format(_T("%g"), dValue[1]);
	strData[2].Format(_T("%g"), dValue[2]);
	strData[3].Format(_T("%g"), dValue[3]);
	strData[4].Format(_T("%g"), dValue[4]);
	strData[5].Format(_T("%g"), dValue[5]);
	/*strData[6].Format(_T("%g"), dValue[6]);
	strData[7].Format(_T("%g"), dValue[7]);
	strData[8].Format(_T("%g"), dValue[8]);*/

	SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT6, strData[2]);
	SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT7, strData[3]);
	SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT8, strData[4]);
	SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT9, strData[5]);

	if (m_nMode == 0)
	{
		SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT1, strData[0]);
		SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT2, strData[1]);
		m_ctrCombo.SetCurSel(nValue - 1);

		
	}
	else
	{
		GetDlgItem(IDC_PDVR_TR_SET_DLG_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_PDVR_TR_SET_DLG_EDIT2)->EnableWindow(FALSE);
		m_ctrCombo.EnableWindow(FALSE);
	}
	
	/*SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT3, strData[2]);
	SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT4, strData[3]);
	SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT5, strData[4]);
	SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT6, strData[5]);
	SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT7, strData[6]);
	SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT8, strData[7]);
	SetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT9, strData[8]);
*/
	

}

void CView_PDVR_rst_TRDlg::OnBnClickedPdvrTrSetDlgBtn1()
{
	double dValue[9];
	int	   nValue;
	CString strData[9];

	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT1, strData[0]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT2, strData[1]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT6, strData[2]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT7, strData[3]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT8, strData[4]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT9, strData[5]);
	/*GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT3, strData[2]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT4, strData[3]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT5, strData[4]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT6, strData[5]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT7, strData[6]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT8, strData[7]);
	GetDlgItemText(IDC_PDVR_TR_SET_DLG_EDIT9, strData[8]);*/

	
	dValue[2] =	_wtof(strData[2]);
	dValue[3] =	_wtof(strData[3]);
	dValue[4] =	_wtof(strData[4]);
	dValue[5] = _wtof(strData[5]);
	/*dValue[6] = _wtof(strData[6]);
	dValue[7] = _wtof(strData[7]);
	dValue[8] = _wtof(strData[8]);*/
	

	if (m_nMode == 0)
	{
		dValue[0] = _wtof(strData[0]);
		dValue[1] = _wtof(strData[1]);
		nValue = m_ctrCombo.GetCurSel() + 1;
	
		PUTVALUE(_T("TR_DYN_UIN"), _T("TR_DVMMXV"), m_nIndex, dValue[0]);
		PUTVALUE(_T("TR_DYN_UIN"), _T("TR_DVMMNV"), m_nIndex, dValue[1]);
		PUTVALUE(_T("PDVROPT_DYN_UIN"), _T("pdvropt_oltcmodel"), 1, nValue);
	}
		


	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PATBSVL"), m_nIndex, dValue[2]);
	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PADEV"), m_nIndex, dValue[3]);
	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PACOMPR"), m_nIndex, dValue[4]);
	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PACOMPX"), m_nIndex, dValue[5]);

	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PBTBSVL"), m_nIndex, dValue[2]);
	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PBDEV"), m_nIndex, dValue[3]);
	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PBCOMPR"), m_nIndex, dValue[4]);
	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PBCOMPX"), m_nIndex, dValue[5]);

	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PCTBSVL"), m_nIndex, dValue[2]);
	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PCDEV"), m_nIndex, dValue[3]);
	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PCCOMPR"), m_nIndex, dValue[4]);
	PUTVALUE(_T("TR_DYN_UIN"), _T("TR_PCCOMPX"), m_nIndex, dValue[5]);


	CDialogEx::OnOK();
}
