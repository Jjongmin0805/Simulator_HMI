// CDNDObj_KASIM_TR_TAP.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_TR_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDNDObj_KASIM_TAP 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_KASIM_TR_TAP, CDialog)

CDNDObj_KASIM_TR_TAP::CDNDObj_KASIM_TR_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_TR_DLG, pParent)
{
	m_nSVR_CSVID = 0;
}

CDNDObj_KASIM_TR_TAP::~CDNDObj_KASIM_TR_TAP()
{
}


void CDNDObj_KASIM_TR_TAP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_TR_DLG_COMBO1, m_ctrCombo1[0]);
}


BEGIN_MESSAGE_MAP(CDNDObj_KASIM_TR_TAP, CDialog)
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_TR_DLG_BTN1, &CDNDObj_KASIM_TR_TAP::OnBnClickedDndobjectKasimDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_TR_DLG_BTN1, &CDNDObj_KASIM_TR_TAP::OnUpdateUI_Btn1)
END_MESSAGE_MAP()


// CDNDObj_KASIM_TAP 메시지 처리기
BOOL CDNDObj_KASIM_TR_TAP::OnInitDialog()
{
	CDialog::OnInitDialog();

	_wsetlocale(LC_ALL, _T("Korean"));
	m_ctrCombo1[0].AddString(_T("2권선 MTR"));
	m_ctrCombo1[0].AddString(_T("권선 MTR"));
	m_ctrCombo1[0].AddString(_T("SVR"));
	m_ctrCombo1[0].AddString(_T("일반 2권선"));
	m_ctrCombo1[0].AddString(_T("일반 3권선"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDNDObj_KASIM_TR_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	LoadKASIM();
}

void CDNDObj_KASIM_TR_TAP::LoadKASIM()
{
	int nData = 0;
	int nSVR_Type = 0;
	int nTR_II_BR = 0;
	float fTR_TRMVA = 0;
	float fTR_POSX = 0;
	float fTR_ZERX = 0;
	float fTR_PTRVH = 0;
	float fTR_PTRVL = 0;
	float fTR_CTRCH = 0;
	float fTR_CTRCL = 0;
	CString stKASIM_CEQ, stKASIM_NM;
	CString stCEQID;
	CString stFndFK, stTndFK;
	CString stTR_TRMVA, stTR_POSX, stTR_ZERX, stTR_PTRVH, stTR_PTRVL, stTR_CTRCH, stTR_CTRCL;
	unsigned long long	ullCEQID(0U);

	int nFnd = 0, nTnd = 0;
	int nDL = 0;

	CString stNULL;
	stNULL.Format(_T("0"));

	//INDEX 처리
	m_nSVR_CSVID = m_pSwitch->m_st_Kasim_SVR_Info.m_nSVRID;
	if (m_nSVR_CSVID != 999999) //데이터가 있으면
	{
		stKASIM_NM = CA2W(GETSTRING(("TR_STA"), ("TR_NM"), m_nSVR_CSVID)).m_psz;
		ullCEQID = GETVALUE(unsigned long long, "TR_STA", "TR_CEQID", m_nSVR_CSVID);
		nSVR_Type = GETVALUE(int, _T("TR_STA"), _T("TR_TYPE"), m_nSVR_CSVID);
		fTR_TRMVA = GETVALUE(double, _T("TR_STA"), _T("TR_TRMVA"), m_nSVR_CSVID);
		fTR_POSX = GETVALUE(double, _T("TR_STA"), _T("TR_POSX"), m_nSVR_CSVID);
		fTR_ZERX = GETVALUE(double, _T("TR_STA"), _T("TR_ZERX"), m_nSVR_CSVID);
		fTR_PTRVH = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PTRVH"), m_nSVR_CSVID);
		fTR_PTRVL = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PTRVL"), m_nSVR_CSVID);
		fTR_CTRCH = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_CTRCH"), m_nSVR_CSVID);
		fTR_CTRCL = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_CTRCL"), m_nSVR_CSVID);

		nTR_II_BR = GETVALUE(int, _T("TR_STA"), _T("TR_II_BR"), m_nSVR_CSVID);
		nFnd = GETVALUE(int, _T("BR_STA"), _T("br_ii_fnd"), nTR_II_BR);
		nTnd = GETVALUE(int, _T("BR_STA"), _T("br_ii_tnd"), nTR_II_BR);
		nDL = GETVALUE(int, _T("br_sta"), _T("br_ii_dl"), nTR_II_BR);

		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);

		stTR_TRMVA.Format(_T("%0.2f"), fTR_TRMVA);
		stTR_POSX.Format(_T("%0.2f"), fTR_POSX);
		stTR_ZERX.Format(_T("%0.2f"), fTR_ZERX);
		stTR_PTRVH.Format(_T("%0.2f"), fTR_PTRVH);
		stTR_PTRVL.Format(_T("%0.2f"), fTR_PTRVL);
		stTR_CTRCH.Format(_T("%0.2f"), fTR_CTRCH);
		stTR_CTRCL.Format(_T("%0.2f"), fTR_CTRCL);

		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT1, stKASIM_NM);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT2, stKASIM_CEQ);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT3, stTR_TRMVA);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT4, stTR_POSX);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT5, stTR_ZERX);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT6, stTR_PTRVH);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT7, stTR_PTRVL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT8, stTR_CTRCH);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT9, stTR_CTRCL);

		nSVR_Type = nSVR_Type - 1;
		m_ctrCombo1[0].SetCurSel(nSVR_Type);				
	}
	else
	{
		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT2, stNULL);
		m_ctrCombo1[0].SetCurSel(-1);

	}
}

void CDNDObj_KASIM_TR_TAP::OnBnClickedDndobjectKasimDlgBtn1()
{
	CString stKASIM_NM, stTR_TRMVA, stTR_POSX, stTR_ZERX, stTR_PTRVH, stTR_PTRVL, stTR_CTRCH, stTR_CTRCL;
	UpdateData(TRUE);
	int nPos1 = m_ctrCombo1->GetCurSel();
	nPos1 = nPos1 + 1;
	GetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT1, stKASIM_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT3, stTR_TRMVA);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT4, stTR_POSX);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT5, stTR_ZERX);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT6, stTR_PTRVH);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT7, stTR_PTRVL);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT8, stTR_CTRCH);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_TR_DLG_EDIT9, stTR_CTRCL);

	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TYPE"), m_nSVR_CSVID, (int)nPos1);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TRMVA"), m_nSVR_CSVID, (double)_wtof(stTR_TRMVA));
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_POSX"), m_nSVR_CSVID, (double)_wtof(stTR_POSX));
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ZERX"), m_nSVR_CSVID, (double)_wtof(stTR_ZERX));
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVH"), m_nSVR_CSVID, (double)_wtof(stTR_PTRVH));
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVL"), m_nSVR_CSVID, (double)_wtof(stTR_PTRVL));
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCH"), m_nSVR_CSVID, (double)_wtof(stTR_CTRCH));
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCL"), m_nSVR_CSVID, (double)_wtof(stTR_CTRCL));
	//추가 이름 변경 타입변경?
	PUTVALUE(_T("ND_STA"), _T("ND_NM"), m_nFND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GND_STA"), _T("GND_NM"), m_nFND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("ND_STA"), _T("ND_NM"), m_nTND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GND_STA"), _T("GND_NM"), m_nTND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	m_pSwitch->m_str_keyname.Format(_T("%s"), stKASIM_NM);

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_TR_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}


BOOL CDNDObj_KASIM_TR_TAP::PreTranslateMessage(MSG* pMsg)
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