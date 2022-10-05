// CDNDObj_KASIM_JUNCTION_TAP.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_JUNCTION_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDNDObj_KASIM_JUNCTION_TAP 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_KASIM_JUNCTION_TAP, CDialog)

CDNDObj_KASIM_JUNCTION_TAP::CDNDObj_KASIM_JUNCTION_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_JUNCTION_DLG, pParent)
{

}

CDNDObj_KASIM_JUNCTION_TAP::~CDNDObj_KASIM_JUNCTION_TAP()
{
}

void CDNDObj_KASIM_JUNCTION_TAP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDNDObj_KASIM_JUNCTION_TAP, CDialog)
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_JUNCTION_DLG_BTN1, &CDNDObj_KASIM_JUNCTION_TAP::OnBnClickedDndobjectKasimJunctionDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_JUNCTION_DLG_BTN1, &CDNDObj_KASIM_JUNCTION_TAP::OnUpdateUI_Btn1)
END_MESSAGE_MAP()


// CDNDObj_KASIM_JUNCTION_TAP 메시지 처리기

BOOL CDNDObj_KASIM_JUNCTION_TAP::OnInitDialog()
{
	CDialog::OnInitDialog();
	_wsetlocale(LC_ALL, _T("Korean"));
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  
}

void CDNDObj_KASIM_JUNCTION_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	LoadKASIM();
}

void CDNDObj_KASIM_JUNCTION_TAP::LoadKASIM()
{
	CString stKASIM_CEQ, stKASIM_NM, stKASIM_ND;
	unsigned long long	ullCEQID(0U);
	unsigned long long	ullND(0U);
	CString stNULL;
	stNULL.Format(_T(""));
	//INDEX 처리
	m_nJUNCTION_CSVID = m_pSwitch->m_st_Kasim_ND_Info.m_nNDID;

	if (m_nJUNCTION_CSVID != 999999) //데이터가 있으면
	{
		stKASIM_NM = CA2W(GETSTRING(("nd_sta"), ("nd_nm"), m_nJUNCTION_CSVID)).m_psz;
		ullCEQID = GETVALUE(unsigned long long, "nd_sta", "ND_CEQID", m_nJUNCTION_CSVID);
		ullND = GETVALUE(unsigned long long, "nd_sta", "ND_CONNECTIVITYNODEID", m_nJUNCTION_CSVID);

		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		stKASIM_ND.Format(_T("%lld"), ullND);

		SetDlgItemText(IDC_DNDOBJECT_KASIM_JUNCTION_DLG_EDIT1, stKASIM_NM);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_JUNCTION_DLG_EDIT2, stKASIM_CEQ);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_JUNCTION_DLG_EDIT3, stKASIM_ND);
	}
	else
	{
		SetDlgItemText(IDC_DNDOBJECT_KASIM_JUNCTION_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_JUNCTION_DLG_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_JUNCTION_DLG_EDIT3, stNULL);
	}	
}

void CDNDObj_KASIM_JUNCTION_TAP::OnBnClickedDndobjectKasimJunctionDlgBtn1()
{
	CString stKASIM_NM, stCEQID;

	//설정값 가져오기
	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_JUNCTION_DLG_EDIT1, stKASIM_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_JUNCTION_DLG_EDIT2, stCEQID);

	PUTVALUE(_T("nd_sta"), _T("nd_nm"), m_nJUNCTION_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("nd_sta"), _T("nd_ConnectivityNodeID"), m_nJUNCTION_CSVID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("nd_sta"), _T("ND_II_GND"), m_nJUNCTION_CSVID, (int)m_nJUNCTION_CSVID);

	PUTVALUE(_T("gnd_sta"), _T("gnd_nm"), m_nJUNCTION_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("gnd_sta"), _T("gnd_hi_nd"), m_nJUNCTION_CSVID, (int)m_nJUNCTION_CSVID);
	//추가 이름 변경 타입변경?
	m_pSwitch->m_str_keyname.Format(_T("%s"), stKASIM_NM);

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_JUNCTION_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

BOOL CDNDObj_KASIM_JUNCTION_TAP::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == 13)
		{
			CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
			OnBnClickedDndobjectKasimJunctionDlgBtn1();
			pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
