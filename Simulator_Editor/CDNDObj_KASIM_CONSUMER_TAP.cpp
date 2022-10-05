// CDNDObj_KASIM_CONSUMER_TAP.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_CONSUMER_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDNDObj_KASIM_CONSUMER_TAP 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_KASIM_CONSUMER_TAP, CDialog)

CDNDObj_KASIM_CONSUMER_TAP::CDNDObj_KASIM_CONSUMER_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_CONSUMER_DLG, pParent)
{

}

CDNDObj_KASIM_CONSUMER_TAP::~CDNDObj_KASIM_CONSUMER_TAP()
{
}

void CDNDObj_KASIM_CONSUMER_TAP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_CUNSUMER_DLG_COMBOX1, m_ctrCombo1[0]);
}


BEGIN_MESSAGE_MAP(CDNDObj_KASIM_CONSUMER_TAP, CDialog)
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_BTN1, &CDNDObj_KASIM_CONSUMER_TAP::OnBnClickedDndobjectKasimConsumerDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_BTN1, &CDNDObj_KASIM_CONSUMER_TAP::OnUpdateUI_Btn1)
END_MESSAGE_MAP()


BOOL CDNDObj_KASIM_CONSUMER_TAP::OnInitDialog()
{
	CDialog::OnInitDialog();
	_wsetlocale(LC_ALL, _T("Korean"));

	m_ctrCombo1[0].AddString(_T("Ygyg"));
	m_ctrCombo1[0].AddString(_T("Ygd"));
	m_ctrCombo1[0].AddString(_T("Dyg"));
	m_ctrCombo1[0].AddString(_T("Yd"));
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDNDObj_KASIM_CONSUMER_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	LoadKASIM();
}

void CDNDObj_KASIM_CONSUMER_TAP::LoadKASIM()
{
	CString stKASIM_CEQ, stKASIM_NM, stINNER_TEXT;
	CString stHVCUS_CON_KVA, stHVCUS_ITR_KVA, stHVCUS_ITR_PZ;
	double dHVCUS_CON_KVA, dHVCUS_ITR_KVA, dHVCUS_ITR_PZ;	
	unsigned long long	ullCEQID(0U);
	int nHVCUS_ITR_WDC = 0;
	CString stNULL;
	stNULL.Format(_T("0"));

	//INDEX 처리
	m_nCOUNSUMER_CSVID = m_pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUSID;
	m_nIJ_CSVID = m_pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_IJ;
	m_nND_CSVID = m_pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_ND;
	m_nPRDE_CSVID = m_pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_PRDE;

	if (m_nCOUNSUMER_CSVID != 999999) //데이터가 있으면
	{
		stINNER_TEXT = m_pSwitch->m_str_innertext;

		stKASIM_NM = CA2W(GETSTRING(("HVCUS_STA"), ("HVCUS_NM"), m_nCOUNSUMER_CSVID)).m_psz;
		ullCEQID = GETVALUE(unsigned long long, "HVCUS_STA", "HVCUS_CEQID", m_nCOUNSUMER_CSVID);
		dHVCUS_CON_KVA = GETVALUE(double, _T("HVCUS_STA"), _T("HVCUS_CON_KVA"), m_nCOUNSUMER_CSVID);
		dHVCUS_ITR_KVA = GETVALUE(double, _T("HVCUS_STA"), _T("HVCUS_ITR_KVA"), m_nCOUNSUMER_CSVID);
		dHVCUS_ITR_PZ = GETVALUE(double, _T("HVCUS_STA"), _T("HVCUS_ITR_PZ"), m_nCOUNSUMER_CSVID);
		nHVCUS_ITR_WDC = GETVALUE(int, _T("HVCUS_STA"), _T("HVCUS_ITR_WDC"), m_nCOUNSUMER_CSVID);
		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		stHVCUS_CON_KVA.Format(_T("%0.2f"), dHVCUS_CON_KVA);
		stHVCUS_ITR_KVA.Format(_T("%0.2f"), dHVCUS_ITR_KVA);
		stHVCUS_ITR_PZ.Format(_T("%0.2f"), dHVCUS_ITR_PZ);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT1, stKASIM_NM);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT2, stKASIM_CEQ);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT3, stHVCUS_CON_KVA);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT4, stHVCUS_ITR_KVA);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT5, stHVCUS_ITR_PZ);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT6, stINNER_TEXT);

		m_ctrCombo1[0].SetCurSel(nHVCUS_ITR_WDC - 1);

	}
	else
	{
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT3, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT4, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT5, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT6, stNULL);
		m_ctrCombo1[0].SetCurSel(-1);
	}
}

void CDNDObj_KASIM_CONSUMER_TAP::OnBnClickedDndobjectKasimConsumerDlgBtn1()
{
	CString stKASIM_NM, stCEQID;
	CString stHVCUS_CON_KVA,stHVCUS_ITR_KVA,stHVCUS_ITR_PZ, stINNER_TEXT;

	//설정값 가져오기
	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT1, stKASIM_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT2, stCEQID);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT3, stHVCUS_CON_KVA);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT4, stHVCUS_ITR_KVA);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT5, stHVCUS_ITR_PZ);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_CONSUMER_DLG_EDIT6, stINNER_TEXT);
	int nHVCUS_ITR_WDC = m_ctrCombo1->GetCurSel(); 
	//
	PUTVALUE(_T("HVCUS_STA"), _T("HVCUS_NM"), m_nCOUNSUMER_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("HVCUS_STA"), _T("HVCUS_CEQID"), m_nCOUNSUMER_CSVID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_CON_KVA"), m_nCOUNSUMER_CSVID, (double)_wtof(stHVCUS_CON_KVA));
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_ITR_KVA"), m_nCOUNSUMER_CSVID, (double)_wtof(stHVCUS_ITR_KVA));
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_ITR_PZ"), m_nCOUNSUMER_CSVID, (double)_wtof(stHVCUS_ITR_PZ));
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_ITR_WDC"), m_nCOUNSUMER_CSVID, (int)nHVCUS_ITR_WDC+1);
	//추가 이름 변경 타입변경?
	PUTVALUE(_T("ND_STA"), _T("ND_NM"), m_nND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GND_STA"), _T("GND_NM"), m_nND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	m_pSwitch->m_str_keyname.Format(_T("%s"), stKASIM_NM);	
	m_pSwitch->m_str_innertext.Format(_T("%s"), stINNER_TEXT);

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_CONSUMER_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

BOOL CDNDObj_KASIM_CONSUMER_TAP::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == 13)
		{
			CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
			OnBnClickedDndobjectKasimConsumerDlgBtn1();
			pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
		}			
	}

	return CDialog::PreTranslateMessage(pMsg);
}