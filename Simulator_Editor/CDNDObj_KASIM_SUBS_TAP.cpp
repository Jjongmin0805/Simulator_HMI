#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_SUBS_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CDNDObj_KASIM_TAP 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_KASIM_SUBS_TAP, CDialog)

CDNDObj_KASIM_SUBS_TAP::CDNDObj_KASIM_SUBS_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_CB_DLG, pParent)
{
	m_nSUBS_CSVID = 0;
	m_nND_CSVID = 0;
}

CDNDObj_KASIM_SUBS_TAP::~CDNDObj_KASIM_SUBS_TAP()
{
}


void CDNDObj_KASIM_SUBS_TAP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDNDObj_KASIM_SUBS_TAP, CDialog)
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_SUBS_DLG_BTN1, &CDNDObj_KASIM_SUBS_TAP::OnBnClickedDndobjectKasimDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_SUBS_DLG_BTN1, &CDNDObj_KASIM_SUBS_TAP::OnUpdateUI_Btn1)
END_MESSAGE_MAP()


// CDNDObj_KASIM_TAP 메시지 처리기
BOOL CDNDObj_KASIM_SUBS_TAP::OnInitDialog()
{
	CDialog::OnInitDialog();
	_wsetlocale(LC_ALL, _T("Korean"));

	return TRUE;
}

void CDNDObj_KASIM_SUBS_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	LoadKASIM();
}

void CDNDObj_KASIM_SUBS_TAP::LoadKASIM()
{
	CString stKASIM_CEQ, stKASIM_NM, stData;
	CString stCEQID;
	unsigned long long	ullCEQID(0U);

	int nFnd = 0, nTnd = 0, nSNV = 0;

	CString stNULL;
	stNULL.Format(_T("0"));

	//INDEX 처리
	m_nSUBS_CSVID = m_pSwitch->m_st_Kasim_SUBS_Info.m_nSUBSID;
	if (m_nSUBS_CSVID != 999999) //데이터가 있으면
	{

		stKASIM_NM = CA2W(GETSTRING(("SS_STA"), ("SS_NM"), m_nSUBS_CSVID)).m_psz;
		ullCEQID = GETVALUE(unsigned long long, "SS_STA", "SS_SUBSTATIONID", m_nSUBS_CSVID);
		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);

		SetDlgItemText(IDC_DNDOBJECT_KASIM_SUBS_DLG_EDIT1, stKASIM_NM);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_SUBS_DLG_EDIT2, stKASIM_CEQ);
	}
	else
	{
		SetDlgItemText(IDC_DNDOBJECT_KASIM_SUBS_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_SUBS_DLG_EDIT2, stNULL);
	}
}

void CDNDObj_KASIM_SUBS_TAP::OnBnClickedDndobjectKasimDlgBtn1()
{
	int i = 0, j = 0, k = 0;
	unsigned long long	ullCEQID(0U);
	CString stKASIM_NM, stCEQID;
	CString stFndFK, stTndFK;
	CString stMTR_NM, stMTR_CEQ, stMTR_BANK;

	//설정값 가져오기
	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_SUBS_DLG_EDIT1, stKASIM_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_SUBS_DLG_EDIT2, stCEQID);

	PUTVALUE(_T("SS_STA"), _T("SS_NM"), m_nSUBS_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("SS_STA"), _T("SS_SUBSTATIONID"), m_nSUBS_CSVID, (unsigned long long)_wtoll(stCEQID));


	
	m_pSwitch->m_str_keyname.Format(_T("%s"), stKASIM_NM);
	m_pSwitch->m_str_innertext.Format(_T("%s"), stKASIM_NM);


	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_SUBS_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

BOOL CDNDObj_KASIM_SUBS_TAP::PreTranslateMessage(MSG* pMsg)
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

