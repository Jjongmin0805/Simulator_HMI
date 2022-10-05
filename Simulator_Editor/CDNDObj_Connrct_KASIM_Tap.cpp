// CDNDObj_Connrct_KASIM_Tap.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_Connrct_KASIM_Tap.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDNDObj_Connrct_KASIM_Tap 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_Connrct_KASIM_Tap, CDialog)

CDNDObj_Connrct_KASIM_Tap::CDNDObj_Connrct_KASIM_Tap(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DND_CONNECT_TAP_KASIM_DLG, pParent)
{
	m_pParent = pParent;

	m_nLNSEC_CSVID = 0;
	m_nBR_CSVID = 0;
	m_nNewData = 0;
	m_nFNDID = 0 ;
	m_nTNDID = 0 ;
	for (int i = 0 ; i < 300; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_nLNINETYPECODE[i][j] = 0;
		}
	}
}

CDNDObj_Connrct_KASIM_Tap::~CDNDObj_Connrct_KASIM_Tap()
{
}

void CDNDObj_Connrct_KASIM_Tap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DND_CONNECT_TAP_KASIM_DLG__COMBO1, m_ctrCombo1[0]);
	DDX_Control(pDX, IDC_DND_CONNECT_TAP_KASIM_DLG__COMBO2, m_ctrCombo2[0]);
	DDX_Control(pDX, IDC_DND_CONNECT_TAP_KASIM_DLG__COMBO3, m_ctrCombo3[0]);
}


BEGIN_MESSAGE_MAP(CDNDObj_Connrct_KASIM_Tap, CDialog)
	ON_BN_CLICKED(IDC_DND_CONNECT_TAP_KASIM_DLG_BTN1, &CDNDObj_Connrct_KASIM_Tap::OnBnClickedDndConnectTapKasimDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DND_CONNECT_TAP_KASIM_DLG_BTN1, &CDNDObj_Connrct_KASIM_Tap::OnUpdateUI_Btn1)
	ON_CBN_SELCHANGE(IDC_DND_CONNECT_TAP_KASIM_DLG__COMBO2, &CDNDObj_Connrct_KASIM_Tap::OnCbnSelchangeDndConnectTapKasimDlg)
	ON_CBN_SELCHANGE(IDC_DND_CONNECT_TAP_KASIM_DLG__COMBO3, &CDNDObj_Connrct_KASIM_Tap::OnCbnSelchangeDndConnectTapKasimDlg1)
	ON_EN_CHANGE(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT9, &CDNDObj_Connrct_KASIM_Tap::OnEnChangeDndConnectTapKasimDlgDeit3)
END_MESSAGE_MAP()


// CDNDObj_Connrct_KASIM_Tap 메시지 처리기
BOOL CDNDObj_Connrct_KASIM_Tap::OnInitDialog()
{
	CDialog::OnInitDialog();

	_wsetlocale(LC_ALL, _T("Korean"));

	m_ctrCombo1[0].ResetContent();
	m_ctrCombo1[0].AddString(_T("지중선"));
	m_ctrCombo1[0].AddString(_T("가공선"));
	return TRUE;  
}

void CDNDObj_Connrct_KASIM_Tap::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pDND_Connect = (CDND_Connect*)pDNDObj;
	LoadLnsec_Type();
	LoadKASIM();
}

void CDNDObj_Connrct_KASIM_Tap::LoadLnsec_Type()
{
	int i = 0, j = 0, k = 1;
	CString stNM, stNM1, stDate;
	stNM.Format(_T("0"));
	stDate.Format(_T(""));
	m_ctrCombo2[0].ResetContent();
	int nCount_table = theAppDataMng->GetTableRealCount(_T("LINETYPE_CODE_STA"));
	for (i = 1; i <= (int)nCount_table; i++)
	{
		stNM = CA2W(GETSTRING(("LINETYPE_CODE_STA"), ("LINETYPE_PHA_NM"), i)).m_psz;
		if (stNM != stDate)
		{
			m_ctrCombo2[0].AddString(stNM);
			stDate = stNM;

			j = 0;	
			m_nLNINETYPECODE[i-k][j] = i;
			
		}
		else
		{
			j++;
			k++;
			m_nLNINETYPECODE[i-k][j] = i;
		}
	}
}

//데이터 일어오는부분 
void CDNDObj_Connrct_KASIM_Tap::LoadKASIM()
{
	 CString stKASIM_NM, stCEQID,stKASIM_Length;
	int nData = 0;
	int nLNSEC_CONSTYPE = 0;
	int nLNSEC_TYPE_ID = 0;
	int nLNSEC_PRIVAT = 0;
	unsigned long long	ullCEQID(0U);
	double dlength;
	int nIJEQUTY = 0, nIJEQU = 0;

	CString stBR_POSR, stBR_POSX, stBR_ZERR, stBR_ZERX;
	double dBR_POSR, dBR_POSX, dBR_ZERR, dBR_ZERX;
	CString stNULL;
	stNULL.Format(_T(""));

	m_nFNDID = m_pDND_Connect->m_st_Kasim_LNsec_Info.m_nBR_Fnd;
	m_nTNDID = m_pDND_Connect->m_st_Kasim_LNsec_Info.m_nBR_Tnd;
	//
	m_nLNSEC_CSVID  = m_pDND_Connect->m_st_Kasim_LNsec_Info.m_nLNSECID; //LNSEC값  없으면 999999
	m_nBR_CSVID		= m_pDND_Connect->m_st_Kasim_LNsec_Info.m_nBRID;    //BR값     없으면 999999

	//노드를 자동으로 연결하자!! - 흠?
	//20211129 DL연결을 해보자? 
	if (!(m_nFNDID == 0 || m_nFNDID == 999999))
	{
		//1개 연결시 정보가 입력되는부분
		GET_Connrct_BR_DL(m_nBR_CSVID, m_nIJ_CSVID,m_nFNDID);
		GET_Connrct_InsertDB(m_nBR_CSVID, m_nFNDID);
	}
	if (!(m_nTNDID == 0 || m_nTNDID == 999999))
	{
		//1개 연결시 정보가 입력되는부분
		GET_Connrct_BR_DL(m_nBR_CSVID, m_nIJ_CSVID, m_nTNDID);
		GET_Connrct_InsertDB(m_nBR_CSVID, m_nTNDID);
	}	
	//----------------------------------구분선 !
	//수정 

	GetDlgItem(IDC_DND_CONNECT_TAP_KASIM_DLG__COMBO3)->EnableWindow(TRUE);
	if ( m_nLNSEC_CSVID != 999999)
	{
		stKASIM_NM = CA2W(GETSTRING(("lnsec_sta"), ("lnsec_nm"), m_nLNSEC_CSVID)).m_psz;
		ullCEQID = GETVALUE(unsigned long long, "lnsec_sta", "lnsec_ceqid", m_nLNSEC_CSVID);
		nLNSEC_TYPE_ID = GETVALUE(int, _T("lnsec_sta"), _T("lnsec_type_id"), m_nLNSEC_CSVID);
		dlength = GETVALUE(double, _T("lnsec_sta"), _T("lnsec_length"), m_nLNSEC_CSVID);
		nLNSEC_CONSTYPE = GETVALUE(int, _T("lnsec_sta"), _T("LNSEC_CONSTYPE"), m_nLNSEC_CSVID);
		//지중 - 0 /가공 - 1
	
		stCEQID.Format(_T("%lld"), ullCEQID);
		stKASIM_Length.Format(_T("%0.2f"), dlength);
		//LNSEC
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT1, stKASIM_NM);
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT2, stCEQID);
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT9, stKASIM_Length);
		//SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT9, stKASIM_Length);

		if (nLNSEC_CONSTYPE == 0) // TYPE 0 가공 1 이면 지중?
		{
			m_ctrCombo1[0].SetCurSel(1); //가공
		}
		else
		{
			m_ctrCombo1[0].SetCurSel(0); //지중
		}

		int nType_code = 0;
		int nType_code1 = 0;
		int nCode = 0;
		CString stNM;
		for (int i = 0; i < 300; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (m_nLNINETYPECODE[i][j] == nLNSEC_TYPE_ID )
				{
					nType_code = i;
					nType_code1 = j;
					i = 99999;
					j = 99999;
				}
			}
		}

		m_ctrCombo3[0].ResetContent();
		for (int j = 0; j < 10; j++)
		{
			nCode = 0;
			nCode = m_nLNINETYPECODE[nType_code][j];
			stNM = CA2W(GETSTRING(("LINETYPE_CODE_STA"), ("LINETYPE_NEU_NM"), nCode)).m_psz;
			if (nCode != 0)
			{
				m_ctrCombo3[0].AddString(stNM);
			}
		}


		m_ctrCombo2[0].SetCurSel(nType_code);			//KASIM_CODE_LINETYPE참조
		m_ctrCombo3[0].SetCurSel(nType_code1);
		//BR
		
		dBR_POSR = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("POSITIVE_R"), nLNSEC_TYPE_ID);
		dBR_POSX = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("POSITIVE_X"), nLNSEC_TYPE_ID);
		dBR_ZERR = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("ZERO_R"), nLNSEC_TYPE_ID);
		dBR_ZERX = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("ZERO_X"), nLNSEC_TYPE_ID);
	
		dBR_POSR = dBR_POSR * dlength;
		dBR_POSX = dBR_POSX * dlength;
		dBR_ZERR = dBR_ZERR * dlength;
		dBR_ZERX = dBR_ZERX * dlength;

		stBR_POSR.Format(_T("%0.4f"), dBR_POSR);
		stBR_POSX.Format(_T("%0.4f"), dBR_POSX);
		stBR_ZERR.Format(_T("%0.4f"), dBR_ZERR);
		stBR_ZERX.Format(_T("%0.4f"), dBR_ZERX);
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT4, stBR_POSR);
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT5, stBR_POSX);
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT6, stBR_ZERR);
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT7, stBR_ZERX);
	}
	else
	{
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT1, stNULL);
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT2, stNULL);
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT9, stNULL);	  //stKASIM_Length
		//BR 값
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT4, stNULL);	  //stBR_POSR
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT5, stNULL);	  //stBR_POSX
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT6, stNULL);	  //stBR_ZERR
		SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT7, stNULL);	  //stBR_ZERX
		m_ctrCombo1[0].SetCurSel(-1);
		m_ctrCombo2[0].SetCurSel(-1);
	}
}

CString CDNDObj_Connrct_KASIM_Tap::MyPath()
{
	CString slmpath;
	WCHAR szDirve[256], szDir[256];
	WCHAR programpath[2048];
	GetModuleFileName(0, programpath, 1024);
	_wsplitpath(programpath, szDirve, szDir, NULL, NULL);
	slmpath.Format(_T("%s%s"), szDirve, szDir);

	return slmpath.Left(slmpath.GetLength() - 1);
}

//저장하는부분 
void CDNDObj_Connrct_KASIM_Tap::OnBnClickedDndConnectTapKasimDlgBtn1()
{
	UpdateData();

	int i = 0;
	CString stKASIM_CEQ;
	unsigned long long	ullCEQID(0U);
	int nBR_ID = 0;
	int nCount_LNSEC_table = 0;
	int nCount_BR_table = 0;
	int nFnd = 0, nTnd = 0;
	int nND_Fbr = 0, nND_Tbr = 0;
	CString stlength, stKASIM_NM, stCEQID;
	CString stBR_POSR, stBR_POSX, stBR_ZERR, stBR_ZERX, stBR_NORLM;
	CString stConstype, stTypeid, stBRID;

	//설정값 가져오기
	UpdateData(TRUE);
	//LNSEC
	GetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT1, stKASIM_NM);
	GetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT2, stCEQID);
	GetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT9, stlength);
	//BR
	GetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT4, stBR_POSR);
	GetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT5, stBR_POSX);
	GetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT6, stBR_ZERR);
	GetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT7, stBR_ZERX);
	int nPos1 = m_ctrCombo1->GetCurSel(); //지중 - 0 /가공 - 1
 	int nPos2 = m_ctrCombo2->GetCurSel();
	int nPos3 = m_ctrCombo3->GetCurSel();
	int nCode;	
	int nOverHead = 0;
	nCode = m_nLNINETYPECODE[nPos2][nPos3];
	if (nCode == 0 )
	{
		m_nLNINETYPECODE[nPos2][0];
	}
	//연결이 안된 선로가 있을수 있겠지?
	if (m_nFNDID == 999999)
	{
		m_nFNDID = 0;
	}
	if (m_nTNDID == 999999)
	{
		m_nTNDID = 0;
	}

	if (nPos1 == 0)
	{
		nOverHead = 1; //지종
	}
	else
	{
		nOverHead = 0; //가공
	}
	   
	//LNSEC
	i = m_nLNSEC_CSVID;
	PUTVALUE(_T("lnsec_sta"), _T("lnsec_nm"), i, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("lnsec_sta"), _T("LNSEC_CEQID"), i, (unsigned long long)_wtoll(stCEQID));
	PUTVALUE(_T("lnsec_sta"), _T("LNSEC_II_BR"), i, (int)m_nBR_CSVID);
	PUTDOUBLE2VALUE(_T("lnsec_sta"), _T("lnsec_constype"), i, (int)nOverHead);//가공 - 0 /지중 - 1
	PUTDOUBLE2VALUE(_T("lnsec_sta"), _T("lnsec_type_id"), i, (int)nCode); //설로 Type
	PUTDOUBLE2VALUE(_T("lnsec_sta"), _T("lnsec_length"), i, (double)_wtof(stlength));
	//BR
	i = m_nBR_CSVID;
	PUTVALUE(_T("br_sta"), _T("br_nm"), i, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_equ"), i, (int)m_nBR_II_EQU);
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_posr"), i, (double)_wtof(stBR_POSR));
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_posx"), i, (double)_wtof(stBR_POSX));
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_zerr"), i, (double)_wtof(stBR_ZERR));
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_zerx"), i, (double)_wtof(stBR_ZERX));
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_gbr"), i, (int)i);
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_dl"), i, (int)0);
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_fnd"), i, (int)m_nFNDID);
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_tnd"), i, (int)m_nTNDID);
	//GBR
	PUTVALUE(_T("gbr_sta"), _T("gbr_nm"), i, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_equ"), i, (int)m_nBR_II_EQU);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_posr"), i, (double)_wtof(stBR_POSR));
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_posx"), i, (double)_wtof(stBR_POSX));
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_zerr"), i, (double)_wtof(stBR_ZERR));
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_zerx"), i, (double)_wtof(stBR_ZERX));
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_norlm"), i, (double)_wtof(stBR_NORLM));
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("GBR_HI_BR"), i, (int)i);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("GBR_II_EQUTY"), i, (int)1);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_fgnd"), i, (int)m_nFNDID);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_tgnd"), i, (int)m_nTNDID);
	//IJ
	PUTVALUE(_T("ij_sta"), _T("ij_nm"), m_nIJ_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("ij_sta"), _T("ij_ii_gnd"), m_nIJ_CSVID, (int)m_nTNDID);
	PUTDOUBLE2VALUE(_T("ij_sta"), _T("ij_ii_equty"), m_nIJ_CSVID, (int)6);
	PUTDOUBLE2VALUE(_T("ij_sta"), _T("ij_ii_dl"), m_nIJ_CSVID, (int)0);
	//LD
	PUTVALUE(_T("LD_STA"), _T("LD_NM"), m_nLD_CSVID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_GND"), m_nLD_CSVID, (int)m_nTNDID);
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_IJ"), m_nLD_CSVID, (int)m_nIJ_CSVID);
	 
	//선로 지중 가공 저장!
	if (nPos1 == 0) //////  지중
	{
		m_pDND_Connect->m_str_stroke = _T("#FFFF00");
		m_pDND_Connect->m_str_stroke_type = _T("dot");
	}
	else
	{
		m_pDND_Connect->m_str_stroke = _T("#00FFFF");
		m_pDND_Connect->m_str_stroke_type = _T("solid");
	}

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_Connrct_KASIM_Tap::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CDNDObj_Connrct_KASIM_Tap::GET_Connrct_BR_DL(int nBRID, int nIJID ,int nNDID)
{
	int nFBRID, nTBRID;
	int nFCBSWID, nTCBSWID;
	int nDLID = 0;
	//ND에도 정보를 입력 하자!
	if (nNDID != 0)
	{
		nFBRID = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNDID);
		nTBRID = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNDID);
		nFCBSWID = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDID);
		nTCBSWID = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDID);
	}
	if (nFBRID == 0 && nTBRID != nBRID && nNDID != 0)
	{
		if (nFCBSWID != 0 && nTCBSWID == 0)
		{
			PUTDOUBLE2VALUE(_T("nd_sta"), _T("nd_hi_tbr"), nNDID, (int)nBRID);
			PUTDOUBLE2VALUE(_T("gnd_sta"), _T("gnd_hi_tgbr"), nNDID, (int)nBRID);
		}
		else
		{
			//ND에 정보입력하는 부분
			PUTDOUBLE2VALUE(_T("nd_sta"), _T("nd_hi_fbr"), nNDID, (int)nBRID);
			PUTDOUBLE2VALUE(_T("gnd_sta"), _T("gnd_hi_fgbr"), nNDID, (int)nBRID);
		}	
	}
	else if (nTBRID == 0 && nFBRID != nBRID  && nNDID != 0)
	{
		if (nFCBSWID == 0 && nTCBSWID != 0)
		{
			PUTDOUBLE2VALUE(_T("nd_sta"), _T("nd_hi_fbr"), nNDID, (int)nBRID);
			PUTDOUBLE2VALUE(_T("gnd_sta"), _T("gnd_hi_fgbr"), nNDID, (int)nBRID);
		}
		else
		{
			//ND에 정보입력하는 부분
			PUTDOUBLE2VALUE(_T("nd_sta"), _T("nd_hi_tbr"), nNDID, (int)nBRID);
			PUTDOUBLE2VALUE(_T("gnd_sta"), _T("gnd_hi_tgbr"), nNDID, (int)nBRID);
		}
	}
	//DL정보를 찾자!!
	if (nFBRID != 0)
	{
		nDLID = GETVALUE(int, _T("BR_STA"), _T("BR_II_DL"), nFBRID);
	}
	else if (nTBRID != 0)
	{
		nDLID = GETVALUE(int, _T("BR_STA"), _T("BR_II_DL"), nTBRID);
	}
	if (nDLID != 0)
	{
		PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_DL"), nBRID, (int)nDLID);
		if ( nIJID != 0)
		{
			PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_DL"), nIJID, (int)nDLID);
		}
	}
	else //연결된 선로가 BR이 없으면 
	{
		if (nFCBSWID != 0)
		{
			nDLID = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_DL"), nFCBSWID);
		}
		else if (nTCBSWID != 0)
		{
			nDLID = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_DL"), nTCBSWID);
		}
		if (nDLID != 0)
		{
			PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_DL"), nBRID, (int)nDLID);
			if (nIJID != 0)
			{
				PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_DL"), nIJID, (int)nDLID);
			}
		}
	}
}

//이건 연결되는 선로쪽으로 보내자
void CDNDObj_Connrct_KASIM_Tap::GET_Connrct_InsertDB(int nBRID, int nNDID)
{
	int nFCBSWID, nTCBSWID;
	int nDLID = 0;

	nDLID = GETVALUE(int, _T("BR_STA"), _T("BR_II_DL"), nBRID);//	
	if (nNDID != 0)
	{
		nFCBSWID = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FCBSW"), nNDID);
		nTCBSWID = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TCBSW"), nNDID);
	}
	if (nFCBSWID != 0)
	{
		PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_DL"), nFCBSWID, (int)nDLID);
	}
	else if (nTCBSWID != 0)
	{
		PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_DL"), nTCBSWID, (int)nDLID);
	}
}

void CDNDObj_Connrct_KASIM_Tap::OnCbnSelchangeDndConnectTapKasimDlg()
{
	GetDlgItem(IDC_DND_CONNECT_TAP_KASIM_DLG__COMBO3)->EnableWindow(TRUE);


	int nPos2 = m_ctrCombo2->GetCurSel();
	int nPos3 = m_ctrCombo3->GetCurSel();

	int nCode = 0;
	CString stNM;

	m_ctrCombo3[0].ResetContent();
	for (int j = 0; j < 10; j++)
	{
		nCode = 0;
		nCode = m_nLNINETYPECODE[nPos2][j];
		stNM = CA2W(GETSTRING(("LINETYPE_CODE_STA"), ("LINETYPE_NEU_NM"), nCode)).m_psz;
		if (nCode != 0)
		{
			m_ctrCombo3[0].AddString(stNM);
		}
	}
	m_ctrCombo3[0].SetCurSel(0);

	OnCbnSelchangeDndConnectTapKasimDlg1();


}

void CDNDObj_Connrct_KASIM_Tap::OnCbnSelchangeDndConnectTapKasimDlg1()
{
	//콤보박스 변경시!
	int nPos2 = m_ctrCombo2->GetCurSel();
	int nPos3 = m_ctrCombo3->GetCurSel();


	int nCode = 0;
	CString stNM;

	nCode = m_nLNINETYPECODE[nPos2][nPos3];

	int i = 0;
	double dBR_POSR = 0, dBR_POSX = 0, dBR_ZERR = 0, dBR_ZERX = 0;
	CString stBR_POSR, stBR_POSX, stBR_ZERR, stBR_ZERX;
	CString stlength;
	double dlength;

	GetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT9, stlength);
	dlength = _wtof(stlength);

	dBR_POSR = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("POSITIVE_R"), nCode);
	dBR_POSX = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("POSITIVE_X"), nCode);
	dBR_ZERR = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("ZERO_R"), nCode);
	dBR_ZERX = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("ZERO_X"), nCode);

	dBR_POSR = dlength * dBR_POSR;
	dBR_POSX = dlength * dBR_POSX;
	dBR_ZERR = dlength * dBR_ZERR;
	dBR_ZERX = dlength * dBR_ZERX;

	stBR_POSR.Format(_T("%0.4f"), dBR_POSR);
	stBR_POSX.Format(_T("%0.4f"), dBR_POSX);
	stBR_ZERR.Format(_T("%0.4f"), dBR_ZERR);
	stBR_ZERX.Format(_T("%0.4f"), dBR_ZERX);

	SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT4, stBR_POSR);
	SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT5, stBR_POSX);
	SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT6, stBR_ZERR);
	SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT7, stBR_ZERX);
}


void CDNDObj_Connrct_KASIM_Tap::OnEnChangeDndConnectTapKasimDlgDeit3()
{
	int nPos2 = m_ctrCombo2->GetCurSel();
	int nPos3 = m_ctrCombo3->GetCurSel();
	int nCode = 0;

	nCode = m_nLNINETYPECODE[nPos2][nPos3];

	int i = 0;
	double dBR_POSR = 0, dBR_POSX = 0, dBR_ZERR = 0, dBR_ZERX = 0;
	CString stBR_POSR, stBR_POSX, stBR_ZERR, stBR_ZERX;
	CString stlength;
	double dlength;

	GetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT9, stlength);
	dlength = _wtof(stlength);

	dBR_POSR = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("POSITIVE_R"), nCode);
	dBR_POSX = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("POSITIVE_X"), nCode);
	dBR_ZERR = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("ZERO_R"), nCode);
	dBR_ZERX = GETVALUE(double, _T("LINETYPE_CODE_STA"), _T("ZERO_X"), nCode);

	dBR_POSR = dlength * dBR_POSR;
	dBR_POSX = dlength * dBR_POSX;
	dBR_ZERR = dlength * dBR_ZERR;
	dBR_ZERX = dlength * dBR_ZERX;

	stBR_POSR.Format(_T("%0.4f"), dBR_POSR);
	stBR_POSX.Format(_T("%0.4f"), dBR_POSX);
	stBR_ZERR.Format(_T("%0.4f"), dBR_ZERR);
	stBR_ZERX.Format(_T("%0.4f"), dBR_ZERX);

	SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT4, stBR_POSR);
	SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT5, stBR_POSX);
	SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT6, stBR_ZERR);
	SetDlgItemText(IDC_DND_CONNECT_TAP_KASIM_DLG_DEIT7, stBR_ZERX);
}

BOOL CDNDObj_Connrct_KASIM_Tap::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == 13)
		{
			CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
			OnBnClickedDndConnectTapKasimDlgBtn1();
			pFrm->m_wndSetting_Connect.OnBnClickedDndConnectDlgCancel();
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}