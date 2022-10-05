///////////////////
// CDNDObj_KASIM_TAP.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_CB_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CDNDObj_KASIM_TAP 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_KASIM_CB_TAP, CDialog)

CDNDObj_KASIM_CB_TAP::CDNDObj_KASIM_CB_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_CB_DLG, pParent)
{
	m_nCBSW_CSVID = 0;


	for (int i = 0; i < 100; i++ )
	{
		pSS_SSID[i] = 0;
		pMTR_MTRID[i] = 0;
	}
}

CDNDObj_KASIM_CB_TAP::~CDNDObj_KASIM_CB_TAP()
{
}


void CDNDObj_KASIM_CB_TAP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_CB_DLG_COMBO1, m_ctrCombo1[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_CB_DLG_COMBO2, m_ctrCombo2[0]);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_CB_DLG_COMBO3, m_ctrCombo3[0]);
	DDX_Control(pDX, IDC_COMBO1, m_ctrComboMtrIdx);
}



BEGIN_MESSAGE_MAP(CDNDObj_KASIM_CB_TAP, CDialog)
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_CB_DLG_BTN11, &CDNDObj_KASIM_CB_TAP::OnBnClickedDndobjectKasimDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_CB_DLG_BTN11, &CDNDObj_KASIM_CB_TAP::OnUpdateUI_Btn1)
	ON_CBN_SELCHANGE(IDC_DNDOBJECT_KASIM_CB_DLG_COMBO2, &CDNDObj_KASIM_CB_TAP::OnCbnSelchangeDndobjectKasimCbDlgCombo2)
	ON_CBN_SELCHANGE(IDC_DNDOBJECT_KASIM_CB_DLG_COMBO3, &CDNDObj_KASIM_CB_TAP::OnCbnSelchangeDndobjectKasimCbDlgCombo3)
END_MESSAGE_MAP()


// CDNDObj_KASIM_TAP 메시지 처리기
BOOL CDNDObj_KASIM_CB_TAP::OnInitDialog()
{
	CDialog::OnInitDialog();
	_wsetlocale(LC_ALL, _T("Korean"));
	m_ctrCombo1[0].AddString(_T("Close"));
	m_ctrCombo1[0].AddString(_T("Open"));
	return TRUE; 
}

void CDNDObj_KASIM_CB_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	LoadKASIM_SS();
	LoadKASIM();
}

void CDNDObj_KASIM_CB_TAP::LoadKASIM_SS()
{
	for (int k = 0; k < 100; k++)
	{
		pSS_SSID[k] = 0;
	}

	int i = 0;
	int nSSID = 0;
	int nCount = 0;
	CString stSSNM, stMTRNM, stNM;
	m_ctrCombo2[0].ResetContent();
	int nCount_SS_table = theAppDataMng->GetTableRealCount(_T("SS_STA"));
	for (i = 1; i <= (int)nCount_SS_table; i++)
	{
		stSSNM = CA2W(GETSTRING(("SS_STA"), ("SS_NM"), i)).m_psz;

		if (!(stSSNM.IsEmpty()))
		{
			stNM.Format(_T("%s"), stSSNM);
			m_ctrCombo2[0].AddString(stNM);
			pSS_SSID[nCount] = i;
			nCount++;
		}
	}
}

void CDNDObj_KASIM_CB_TAP::LoadKASIM_MTR(int nSSID)
{
	for (int k = 0; k < 100; k++)
	{
		pMTR_MTRID[k] = 0;
	}

	int i = 0;
	int nMTRSSID = 0;
	int nCount = 0;
	CString stSSNM, stMTRNM, stNM, stMTRIndex;
	m_ctrCombo3[0].ResetContent();
	m_ctrComboMtrIdx.ResetContent();
	int nCount_MTR_table = theAppDataMng->GetTableRealCount(_T("MTR_STA"));
	for (i = 1; i <= (int)nCount_MTR_table; i++)
	{
		nMTRSSID = GETVALUE(int, _T("MTR_STA"), _T("MTR_II_SS"), i);
		if (nMTRSSID == nSSID)
		{
			stMTRNM = CA2W(GETSTRING(("MTR_STA"), ("MTR_NM"), i)).m_psz;
			
			stMTRIndex.Format(_T("%d"), i);
			if (!(stMTRNM.IsEmpty()))
			{
				stNM.Format(_T("%s"), stMTRNM);
				m_ctrCombo3[0].AddString(stNM);
				m_ctrComboMtrIdx.AddString(stMTRIndex);

				pMTR_MTRID[nCount] = i;
				nCount++;
			}
		}
	}

	if (m_ctrCombo3[0].GetCurSel())
	{
		m_ctrCombo3[0].SetCurSel(0);
		m_ctrComboMtrIdx.SetCurSel(0);
	}
}

void CDNDObj_KASIM_CB_TAP::LoadKASIM()
{
	int nCbsw_Norstat = 0;
	int nCbsw_Type = 0;
	int nCbsw_ii_dl = 0;
	int nCBSW_RTUCODE = 0;
	int nMTRSSID = 0;
	CString stKASIM_CEQ, stKASIM_NM, stData;
	CString stCEQID, stINNER_TEXT;
	CString stFndFK, stTndFK;
	unsigned long long	ullCEQID(0U);

	int nFnd = 0, nTnd = 0, nSNV = 0;
	int nMTRID = 0;
	int nMTR_BANK = 0;
	CString stNULL;
	stNULL.Format(_T("0"));

	//INDEX 처리
	m_nCBSW_CSVID = m_pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID;
	if (m_nCBSW_CSVID != 999999) //데이터가 있으면
	{
		stINNER_TEXT = m_pSwitch->m_str_innertext;

		stKASIM_NM = CA2W(GETSTRING(("CBSW_STA"), ("CBSW_NM"), m_nCBSW_CSVID)).m_psz;
		ullCEQID = GETVALUE(unsigned long long, "CBSW_STA", "CBSW_CEQID", m_nCBSW_CSVID);
		nCbsw_ii_dl = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_DL"), m_nCBSW_CSVID);
		nFnd = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_FND"), m_nCBSW_CSVID);
		nTnd = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_TND"), m_nCBSW_CSVID);
		nCbsw_Norstat = GETVALUE(int, _T("CBSW_DYN_MEA"), _T("CBSW_NWSTAT"), m_nCBSW_CSVID);

		//
		nMTRID = GETVALUE(int, _T("DL_STA"), _T("DL_II_MTR"), nCbsw_ii_dl);
		
		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CB_DLG_EDIT1, stKASIM_NM);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CB_DLG_EDIT2, stKASIM_CEQ);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CB_DLG_EDIT3, stINNER_TEXT);

		if (nCbsw_Norstat == 0)
		{
			m_ctrCombo1[0].SetCurSel(1);
		}
		else
		{
			m_ctrCombo1[0].SetCurSel(0);
		}

		nMTRSSID = GETVALUE(int, _T("MTR_STA"), _T("MTR_II_SS"), nMTRID );
		//MTR정보 불러오기위해
		LoadKASIM_MTR(nMTRSSID);

		//SS
		int nSS_ID = 0;
		for (int i = 0; i < 100; i++)
		{
			nSS_ID = pSS_SSID[i];
			if (nMTRSSID == nSS_ID)
			{
				m_ctrCombo2[0].SetCurSel(i);
			}
		}
		//MTR
		int nMTR_ID = 0;
		for (int i = 0; i < 100; i++)
		{
			nMTR_ID = pMTR_MTRID[i];
			if (nMTRID == nMTR_ID)
			{
				m_ctrCombo3[0].SetCurSel(i);
				m_ctrComboMtrIdx.SetCurSel(i);
			}
		}
// 		int nComboMTRIndex = 0;
// 		for (int i = 0; i < m_ctrComboMtrIdx.GetCount(); i++)
// 		{
// 			m_ctrComboMtrIdx.GetCurSel(i);
// 			nComboMTRIndex = m_ctrComboMtrIdx.GetCurSel(i);
// 			if (nMTRID == nComboMTRIndex)
// 			{
// 				m_ctrCombo3[0].SetCurSel(i);
// 				m_ctrComboMtrIdx.SetCurSel(i);
// 			}
// 		}

	}
	else
	{
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CB_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CB_DLG_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_CB_DLG_EDIT3, stNULL);
		m_ctrCombo1[0].SetCurSel(0);
		m_ctrCombo2[0].SetCurSel(0);
	}
}

void CDNDObj_KASIM_CB_TAP::OnBnClickedDndobjectKasimDlgBtn1()
{
	int i = 0, j = 0, k = 0;
	int nCbsw_ii_dl;
	unsigned long long	ullCEQID(0U);
	CString stKASIM_NM, stCEQID, stINNER_TEXT;
	CString stFndFK, stTndFK;
	int nMTRID = 0;


	nCbsw_ii_dl = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_DL"), m_nCBSW_CSVID);
	//설정값 가져오기
	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_CB_DLG_EDIT1, stKASIM_NM);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_CB_DLG_EDIT2, stCEQID);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_CB_DLG_EDIT3, stINNER_TEXT);
	int nPos1 = m_ctrCombo1->GetCurSel();
	int nPos2 = m_ctrCombo2->GetCurSel();
	int nPos3 = m_ctrCombo3->GetCurSel();
	nPos1 = nPos1 + 1;
	nPos2 = nPos2 + 1;
	nPos3 = nPos3 + 1;
	//CBSW
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_NM"), m_nCBSW_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_CEQID"), m_nCBSW_CSVID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_TYPE"), m_nCBSW_CSVID, (int)1); //CB속성 박아놓자!
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_RTUCODE"), m_nCBSW_CSVID, (int)0);
//	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_DL"), m_nCBSW_CSVID, (int)nCbsw_ii_dl);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_BASE_STATE"), m_nCBSW_CSVID, (int)nPos1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_ODSTAT"), m_nCBSW_CSVID, (int)nPos1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_NWSTAT"), m_nCBSW_CSVID, (int)nPos1);
	//추가 이름 변경 타입변경?
	PUTVALUE(_T("ND_STA"), _T("ND_NM"), m_nFND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GND_STA"), _T("GND_NM"), m_nFND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("ND_STA"), _T("ND_NM"), m_nTND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GND_STA"), _T("GND_NM"), m_nTND_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	m_pSwitch->m_str_keyname.Format(_T("%s"), stKASIM_NM);
	m_pSwitch->m_str_innertext.Format(_T("%s"), stINNER_TEXT);

	PUTVALUE(_T("DL_STA"), _T("DL_NM"), nCbsw_ii_dl, (wchar_t*)stKASIM_NM.GetBuffer());
	//MTR뱅크 찾기!!
	nMTRID = GET_MTR_ID(nPos2, nPos3);

	//
	int nPos4 = m_ctrCombo2->GetCurSel();
	int nPos5 = m_ctrCombo3->GetCurSel();
	int nSS_ID = 0, nMTR_ID = 0;
	nSS_ID = pSS_SSID[nPos4];
	nMTR_ID = pMTR_MTRID[nPos5];

// 	int nIdx = 0;
// 	nIdx = m_ctrCombo3[0].GetCurSel();
// 	nMTR_ID = m_ctrComboMtrIdx.SetCurSel(nIdx);
// 	m_ctrComboMtrIdx.GetCurSel()

	//음????????????
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_II_MTR"), nCbsw_ii_dl, (int)nMTR_ID);
	PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_II_SS"), nMTR_ID, (int)nSS_ID);

	//여기서 MTR이 변경될때마가 계속 바뀌게 된다.
	int nCBSW_TRID, nCBSW_BRID, nCBSW_TNDID;
	nCBSW_TRID = GETVALUE(int, _T("MTR_STA"), _T("MTR_HI_TR"), nMTR_ID);
	nCBSW_BRID = GETVALUE(int, _T("TR_STA"), _T("TR_II_BR"), nCBSW_TRID);
	nCBSW_TNDID = GETVALUE(int, _T("BR_STA"), _T("BR_II_TND"), nCBSW_BRID);

	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_FND"), m_nCBSW_CSVID, (int)nCBSW_TNDID);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_FGND"), m_nCBSW_CSVID, (int)nCBSW_TNDID);
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_CB_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

BOOL CDNDObj_KASIM_CB_TAP::PreTranslateMessage(MSG* pMsg)
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

void CDNDObj_KASIM_CB_TAP::OnCbnSelchangeDndobjectKasimCbDlgCombo2()
{

	int nPos2 = m_ctrCombo2->GetCurSel();
	int  nSS_ID = 0;
	nSS_ID = pSS_SSID[nPos2];

	LoadKASIM_MTR(nSS_ID);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

int CDNDObj_KASIM_CB_TAP::GET_MTR_ID(int nSSID, int nMTR_BANK)
{
	int i = 0;
	int nMTRSSID = 0;
	int nMTR_TMTR_BANK = 0;
	int nCount_MTR_table = theAppDataMng->GetTableRealCount(_T("MTR_STA"));
	for (i = 1; i <= (int)nCount_MTR_table; i++)
	{
		nMTRSSID = GETVALUE(int, _T("MTR_STA"), _T("MTR_II_SS"), i);
		if (nMTRSSID == nSSID)
		{
			nMTR_TMTR_BANK = GETVALUE(int, _T("MTR_STA"), _T("MTR_BANK"), i);
			if (nMTR_TMTR_BANK == nMTR_BANK)
			{
				return i;
			}
		}
	}
	return 0;
}

void CDNDObj_KASIM_CB_TAP::OnCbnSelchangeDndobjectKasimCbDlgCombo3()
{
	int nIdx;
	nIdx = m_ctrCombo3[0].GetCurSel();
	m_ctrComboMtrIdx.SetCurSel(nIdx);
}
