// CDNDObj_KASIM_TAP.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_SW_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDNDObj_KASIM_TAP 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_KASIM_SW_TAP, CDialog)

CDNDObj_KASIM_SW_TAP::CDNDObj_KASIM_SW_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_SW_DLG, pParent)
{
	m_nCBSW_CSVID = 0;
}

CDNDObj_KASIM_SW_TAP::~CDNDObj_KASIM_SW_TAP()
{
}


void CDNDObj_KASIM_SW_TAP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_SW_DLG_COMBO1, m_ctrCombo1[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_SW_DLG_COMBO2, m_ctrCombo2[0]);
}


BEGIN_MESSAGE_MAP(CDNDObj_KASIM_SW_TAP, CDialog)
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_SW_DLG_BTN1, &CDNDObj_KASIM_SW_TAP::OnBnClickedDndobjectKasimDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_SW_DLG_BTN1, &CDNDObj_KASIM_SW_TAP::OnUpdateUI_Btn1)
END_MESSAGE_MAP()


// CDNDObj_KASIM_TAP 메시지 처리기
BOOL CDNDObj_KASIM_SW_TAP::OnInitDialog()
{
	CDialog::OnInitDialog();
	_wsetlocale(LC_ALL, _T("Korean"));
	m_ctrCombo1[0].AddString(_T("차단기"));
	m_ctrCombo1[0].AddString(_T("리클로져"));
	m_ctrCombo1[0].AddString(_T("자동개폐기"));
	m_ctrCombo1[0].AddString(_T("수동개폐기"));
	m_ctrCombo1[0].AddString(_T("COS"));
	m_ctrCombo1[0].AddString(_T("EFI"));
	m_ctrCombo1[0].AddString(_T("LV"));
	m_ctrCombo1[0].AddString(_T("HV"));

	m_ctrCombo2[0].AddString(_T("Close"));
	m_ctrCombo2[0].AddString(_T("Open"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDNDObj_KASIM_SW_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	LoadKASIM();
}

void CDNDObj_KASIM_SW_TAP::LoadKASIM()
{
	int nCbsw_Norstat = 0;
	int nCbsw_Type = 0;
	int nCbsw_ii_dl = 0;
	int nCBSW_RTUCODE = 0;
	CString stKASIM_CEQ, stKASIM_NM, stData;
	CString stCEQID, stINNER_TEXT;
	CString stFndFK, stTndFK;
	unsigned long long	ullCEQID(0U);

	int nFnd = 0, nTnd = 0, nSNV = 0;

	CString stNULL;
	stNULL.Format(_T("0"));
	
	//INDEX 처리

	m_nCBSW_CSVID = m_pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID;

	CDND_Switch* pMulti_M;
	for (int i = 0; i < m_pSwitch->m_Array_Multi.GetSize(); i++)
	{
		pMulti_M = (CDND_Switch*)m_pSwitch->m_Array_Multi.GetAt(i);


		m_nCBSW_CSVID = pMulti_M->m_st_Kasim_CBSW_Info.m_nCBSWID;
		stINNER_TEXT = m_pSwitch->m_str_innertext;
	}

	if (m_nCBSW_CSVID != 999999) //데이터가 있으면
	{
		stINNER_TEXT = m_pSwitch->m_str_innertext;

		stKASIM_NM = CA2W(GETSTRING(("CBSW_STA"), ("CBSW_NM"), m_nCBSW_CSVID)).m_psz;
		ullCEQID = GETVALUE(unsigned long long, "CBSW_STA", "CBSW_CEQID", m_nCBSW_CSVID);
		nCbsw_Type = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_TYPE"), m_nCBSW_CSVID);
		nCbsw_ii_dl = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_DL"), m_nCBSW_CSVID);
		nFnd = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_FND"), m_nCBSW_CSVID);
		nTnd = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_TND"), m_nCBSW_CSVID);
		nCbsw_Norstat = GETVALUE(int, _T("CBSW_DYN_MEA"), _T("CBSW_NWSTAT"), m_nCBSW_CSVID);

		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_SW_DLG_EDIT1, stKASIM_NM);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_SW_DLG_EDIT2, stKASIM_CEQ);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_SW_DLG_EDIT3, stINNER_TEXT);

		nCbsw_Type = nCbsw_Type - 1;
		m_ctrCombo1[0].SetCurSel(nCbsw_Type);
		if (nCbsw_Norstat == 0)
		{
			m_ctrCombo2[0].SetCurSel(1);
		}
		else
		{
			m_ctrCombo2[0].SetCurSel(0);
		}
	}
	else
	{
		SetDlgItemText(IDC_DNDOBJECT_KASIM_SW_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_SW_DLG_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_SW_DLG_EDIT3, stNULL);
		m_ctrCombo1[0].SetCurSel(-1);
		m_ctrCombo2[0].SetCurSel(-1);
	}
}

void CDNDObj_KASIM_SW_TAP::OnBnClickedDndobjectKasimDlgBtn1()
{
	int i = 0, j = 0, k = 0;
	unsigned long long	ullCEQID(0U);
	CString stKASIM_NM, stCEQID, stINNER_TEXT;
	CString stFndFK, stTndFK;

	//설정값 가져오기
	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_SW_DLG_EDIT1, stKASIM_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_SW_DLG_EDIT2, stCEQID);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_SW_DLG_EDIT3, stINNER_TEXT);

	int nPos1 = m_ctrCombo1->GetCurSel();
	int nPos2 = m_ctrCombo2->GetCurSel();
	nPos1 = nPos1 + 1;
	nPos2 = nPos2 + 1;	
	//콤보박스 변경시 변경해야함!!!!!
	if (m_pSwitch->m_str_innertext == "")
	{
		SW_Type_Chang(nPos1);
	}
	//CBSW
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_NM"), m_nCBSW_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_CEQID"), m_nCBSW_CSVID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_TYPE"), m_nCBSW_CSVID, (int)nPos1);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_RTUCODE"), m_nCBSW_CSVID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_DL"), m_nCBSW_CSVID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_BASE_STATE"), m_nCBSW_CSVID, (int)nPos2);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_ODSTAT"), m_nCBSW_CSVID, (int)nPos2);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_NWSTAT"), m_nCBSW_CSVID, (int)nPos2);
	//추가 이름 변경 타입변경?
	PUTVALUE(_T("ND_STA"), _T("ND_NM"), m_nFND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GND_STA"), _T("GND_NM"), m_nFND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("ND_STA"), _T("ND_NM"), m_nTND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GND_STA"), _T("GND_NM"), m_nTND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	m_pSwitch->m_str_keyname.Format(_T("%s"), stKASIM_NM);
	m_pSwitch->m_str_innertext.Format(_T("%s"), stINNER_TEXT);

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_SW_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CDNDObj_KASIM_SW_TAP::SW_Type_Chang(int nType)
{
	CSB_BLOCK* pBlock;
	pBlock = (CSB_BLOCK*)m_pSwitch;
	if (nType == 1)
	{
		m_pSwitch->m_str_psrtype.Format(_T("CB"));
		m_pSwitch->m_str_devrefname.Format(_T("배전CB"));
		m_pSwitch->m_n_devref = 421;
		pBlock->m_nID = 421;
	}
	else if (nType == 2)
	{
		m_pSwitch->m_str_psrtype.Format(_T("RECLOSER"));
		m_pSwitch->m_str_devrefname.Format(_T("자동리클로저"));
		m_pSwitch->m_n_devref = 439;
		pBlock->m_nID = 439;
	}
	else if (nType == 3)
	{
		m_pSwitch->m_str_psrtype.Format(_T("SWITCH"));
		m_pSwitch->m_str_devrefname.Format(_T("자동개폐기"));
		m_pSwitch->m_n_devref = 151;
		pBlock->m_nID = 151;
	}
	else if (nType == 4)
	{
		m_pSwitch->m_str_psrtype.Format(_T("SWITCH"));
		m_pSwitch->m_str_devrefname.Format(_T("수동개폐기"));
		m_pSwitch->m_n_devref = 418;
		pBlock->m_nID = 418;
		
	}
	else if (nType == 5)
	{
		m_pSwitch->m_str_psrtype.Format(_T("RECLOSER"));
		m_pSwitch->m_str_devrefname.Format(_T("자동EFI차단기"));
		m_pSwitch->m_n_devref = 444;
		pBlock->m_nID = 444;
	}
	else if (nType == 6)
	{
		m_pSwitch->m_str_psrtype.Format(_T("BREAKER"));
		m_pSwitch->m_str_devrefname.Format(_T("Cut Out Switch"));
		m_pSwitch->m_n_devref = 472;
		pBlock->m_nID = 472;
	}
	else if (nType == 7)
	{
		m_pSwitch->m_str_psrtype.Format(_T("SWITCH"));
		m_pSwitch->m_str_devrefname.Format(_T("LV"));
		m_pSwitch->m_n_devref = 441;
		pBlock->m_nID = 441;
	}
	else if (nType == 8)
	{
		m_pSwitch->m_str_psrtype.Format(_T("SWITCH"));
		m_pSwitch->m_str_devrefname.Format(_T("HV"));
		m_pSwitch->m_n_devref = 441;
		pBlock->m_nID = 441;
	}
	else if (nType == 9)
	{

	}
}


BOOL CDNDObj_KASIM_SW_TAP::PreTranslateMessage(MSG* pMsg)
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
