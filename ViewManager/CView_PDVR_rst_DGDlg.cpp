// CView_PDVR_rst_DGDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CView_PDVR_rst_DGDlg.h"
#include "afxdialogex.h"
#include "resource.h"

// CView_PDVR_rst_DGDlg 대화 상자

IMPLEMENT_DYNAMIC(CView_PDVR_rst_DGDlg, CDialogEx)

CView_PDVR_rst_DGDlg::CView_PDVR_rst_DGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PDVR_DG_SET_DLG, pParent)
{

}

CView_PDVR_rst_DGDlg::~CView_PDVR_rst_DGDlg()
{
}

void CView_PDVR_rst_DGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PDVR_DG_SET_DLG_RADIO1, m_ctrRadio[0]);
	DDX_Control(pDX, IDC_PDVR_DG_SET_DLG_RADIO2, m_ctrRadio[1]);
	DDX_Control(pDX, IDC_PDVR_DG_SET_DLG_COMBO1, m_ctrCombo);
}


BEGIN_MESSAGE_MAP(CView_PDVR_rst_DGDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PDVR_DG_SET_DLG_BTN1, &CView_PDVR_rst_DGDlg::OnBnClickedPdvrDgSetDlgBtn1)
	ON_BN_CLICKED(IDC_PDVR_DG_SET_DLG_RADIO1, &CView_PDVR_rst_DGDlg::OnBnClickedPdvrDgSetDlgRadio1)
	ON_BN_CLICKED(IDC_PDVR_DG_SET_DLG_RADIO2, &CView_PDVR_rst_DGDlg::OnBnClickedPdvrDgSetDlgRadio2)
END_MESSAGE_MAP()


// CView_PDVR_rst_DGDlg 메시지 처리기


BOOL CView_PDVR_rst_DGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	m_ctrCombo.AddString(_T("특고압 전용"));
	m_ctrCombo.AddString(_T("저압 전용"));
	m_ctrCombo.AddString(_T("저압 공용"));

	SetData_DGInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CView_PDVR_rst_DGDlg::SetData_DGInfo()
{
	int nPDVR_Mode;

	int nTR_Value;
	double dValue[7];

	CString strData[7];
	//GEN_TREXCL   GEN_DERAVMQVRATIO


	nTR_Value = GETVALUE(int, _T("GEN_STA"), _T("GEN_TREXCL"), m_nIndex);
	nPDVR_Mode = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_MVARCONMODE"), m_nIndex);
	dValue[0] = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_DERAVMVUBREF"), m_nIndex);
	dValue[1] = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_DERAVMVLBREF"), m_nIndex);
	dValue[2] = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_QVCURVEV1"), m_nIndex);
	dValue[3] = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_QVCURVEV2"), m_nIndex);
	dValue[4] = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_QVCURVEV3"), m_nIndex);
	dValue[5] = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_QVCURVEV4"), m_nIndex);
	dValue[6] = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_DERAVMQVRATIO"), m_nIndex);

	if (nTR_Value > 0)
	{
		m_ctrCombo.SetCurSel(nTR_Value - 1);
	}
	

	strData[0].Format(_T("%g"), dValue[0]);
	strData[1].Format(_T("%g"), dValue[1]);
	strData[2].Format(_T("%g"), dValue[2]);
	strData[3].Format(_T("%g"), dValue[3]);
	strData[4].Format(_T("%g"), dValue[4]);
	strData[5].Format(_T("%g"), dValue[5]);
	strData[6].Format(_T("%.2lf"), dValue[6]);

	SetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT1, strData[0]);
	SetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT2, strData[1]);
	SetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT3, strData[2]);
	SetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT4, strData[3]);
	SetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT5, strData[4]);
	SetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT6, strData[5]);
	SetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT7, strData[6]);

	if (nPDVR_Mode == 5)
	{
		m_ctrRadio[1].SetCheck(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT4)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT6)->EnableWindow(TRUE);
	}
	else
	{
		m_ctrRadio[0].SetCheck(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT2)->EnableWindow(TRUE);
	}
	

}

void CView_PDVR_rst_DGDlg::OnBnClickedPdvrDgSetDlgBtn1()
{
	int nPDVR_Mode;

	double dValue[7];
	CString strData[7];

	if (m_ctrRadio[1].GetCheck() == 1)
		nPDVR_Mode = 5;
	else
		nPDVR_Mode = 4;

	int nTR_Value;

	nTR_Value = m_ctrCombo.GetCurSel();
	
	GetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT1, strData[0]);
	GetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT2, strData[1]);
	GetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT3, strData[2]);
	GetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT4, strData[3]);
	GetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT5, strData[4]);
	GetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT6, strData[5]);
	GetDlgItemText(IDC_PDVR_DG_SET_DLG_EDIT7, strData[6]);

	dValue[0] = _wtof(strData[0]);
	dValue[1] = _wtof(strData[1]);
	dValue[2] = _wtof(strData[2]);
	dValue[3] = _wtof(strData[3]);
	dValue[4] = _wtof(strData[4]);
	dValue[5] = _wtof(strData[5]);
	dValue[6] = _wtof(strData[6]);
		
	PUTVALUE( _T("GEN_STA"), _T("GEN_TREXCL"), m_nIndex, nTR_Value +1);
	PUTVALUE( _T("GEN_DYN_UIN"), _T("GEN_MVARCONMODE"), m_nIndex, nPDVR_Mode);
	PUTVALUE( _T("GEN_DYN_UIN"), _T("GEN_DERAVMVUBREF"), m_nIndex, dValue[0]);
	PUTVALUE( _T("GEN_DYN_UIN"), _T("GEN_DERAVMVLBREF"), m_nIndex, dValue[1]);
	PUTVALUE( _T("GEN_DYN_UIN"), _T("GEN_QVCURVEV1"), m_nIndex, dValue[2]);
	PUTVALUE( _T("GEN_DYN_UIN"), _T("GEN_QVCURVEV2"), m_nIndex, dValue[3]);
	PUTVALUE( _T("GEN_DYN_UIN"), _T("GEN_QVCURVEV3"), m_nIndex, dValue[4]);
	PUTVALUE( _T("GEN_DYN_UIN"), _T("GEN_QVCURVEV4"), m_nIndex, dValue[5]);
	PUTVALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMQVRATIO"), m_nIndex, dValue[6]);

	CDialogEx::OnOK();
}


void CView_PDVR_rst_DGDlg::OnBnClickedPdvrDgSetDlgRadio1()
{
	int nCheck = m_ctrRadio[0].GetCheck();

	if (nCheck == 1)
	{
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT2)->EnableWindow(TRUE);
		
		m_ctrRadio[1].SetCheck(FALSE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT4)->EnableWindow(FALSE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT6)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT2)->EnableWindow(FALSE);

		m_ctrRadio[1].SetCheck(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT4)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT6)->EnableWindow(TRUE);
	}
	
}


void CView_PDVR_rst_DGDlg::OnBnClickedPdvrDgSetDlgRadio2()
{
	int nCheck = m_ctrRadio[1].GetCheck();

	if (nCheck == 1)
	{
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT2)->EnableWindow(FALSE);
		m_ctrRadio[0].SetCheck(FALSE);

		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT4)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT6)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT2)->EnableWindow(TRUE);

		m_ctrRadio[0].SetCheck(TRUE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT4)->EnableWindow(FALSE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_PDVR_DG_SET_DLG_EDIT6)->EnableWindow(FALSE);
	}
}
