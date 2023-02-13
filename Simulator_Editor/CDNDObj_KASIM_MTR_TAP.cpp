// CDNDObj_KASIM_MTR_TAP.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_KASIM_MTR_TAP.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDNDObj_KASIM_MTR_TAP 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_KASIM_MTR_TAP, CDialog)

CDNDObj_KASIM_MTR_TAP::CDNDObj_KASIM_MTR_TAP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_KASIM_MTR_DLG, pParent)
{
	m_nSUBS_CSVID = 0;
	m_nMTR_CSVID = 0;
	m_nMTRIndex = 0;
	for (int i = 0; i < 100; i++)
	{
		m_ListMTR[i] = 0;
	}
}

CDNDObj_KASIM_MTR_TAP::~CDNDObj_KASIM_MTR_TAP()
{
}

void CDNDObj_KASIM_MTR_TAP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNDOBJECT_KASIM_MTR_DLG_LIST1, m_ctrListMTR);
}


BEGIN_MESSAGE_MAP(CDNDObj_KASIM_MTR_TAP, CDialog)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_MTR_DLG_BTN1, &CDNDObj_KASIM_MTR_TAP::OnBnClickedDndobjectKasimMTRDlgBtn1)
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_MTR_DLG_BTN2, &CDNDObj_KASIM_MTR_TAP::OnBnClickedDndobjectKasimMTRDlgBtn2)
	ON_BN_CLICKED(IDC_DNDOBJECT_KASIM_MTR_DLG_BTN3, &CDNDObj_KASIM_MTR_TAP::OnBnClickedDndobjectKasimMTRDlgBtn3)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_MTR_DLG_BTN1, &CDNDObj_KASIM_MTR_TAP::OnUpdateUI_Btn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_MTR_DLG_BTN2, &CDNDObj_KASIM_MTR_TAP::OnUpdateUI_Btn2)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_KASIM_MTR_DLG_BTN3, &CDNDObj_KASIM_MTR_TAP::OnUpdateUI_Btn3)
	ON_NOTIFY(NM_DBLCLK, IDC_DNDOBJECT_KASIM_MTR_DLG_LIST1, &CDNDObj_KASIM_MTR_TAP::OnNMDblclkList1)
	ON_NOTIFY(NM_CLICK, IDC_DNDOBJECT_KASIM_MTR_DLG_LIST1, &CDNDObj_KASIM_MTR_TAP::OnNMClickList1)
END_MESSAGE_MAP()


// CDNDObj_KASIM_MTR_TAP 메시지 처리기


BOOL CDNDObj_KASIM_MTR_TAP::OnInitDialog()
{
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CDialog::OnInitDialog();
	_wsetlocale(LC_ALL, _T("Korean"));

	m_ctrListMTR.DeleteAllItems();
	DWORD style = m_ctrListMTR.GetExtendedStyle();
	style |= (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrListMTR.SetExtendedStyle(style);
	m_ctrListMTR.DeleteAllItems();
	LV_COLUMN														lvcolumn;
	wchar_t*														list[12] = { _T(""), _T("NO."), _T("이름"), _T("KEY"), _T("BANK"), _T("용량"), _T("정상분리액턴스"), _T("영상분리액턴스"), _T("PT1차"), _T("PT2차"), _T("CT1차"), _T("CT2차") };
	int																width[12] = { 0,40 , 80, 120,40,50,70, 70, 50, 50 , 50, 50 };

	for (int i = 0; i < 12; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_CENTER;
		lvcolumn.pszText = list[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = width[i];

		m_ctrListMTR.InsertColumn(i, &lvcolumn);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
			  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDNDObj_KASIM_MTR_TAP::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	m_pSwitch = (CDND_Switch*)pDNDObj;
	LoadKASIM();
}

void CDNDObj_KASIM_MTR_TAP::LoadKASIM()
{
	//공통 
	CString stNULL;
	stNULL.Format(_T(""));

	unsigned long long	ullCEQID(0U);
	//INDEX 처리	   
	m_nSUBS_CSVID = m_pSwitch->m_st_Kasim_SUBS_Info.m_nSUBSID;
	m_nSUBS_NDID = m_pSwitch->m_st_Kasim_SUBS_Info.m_nNDID;
	m_nSUBS_BRID = m_pSwitch->m_st_Kasim_SUBS_Info.m_nBRID;
	//추가시
	if (m_nSUBS_CSVID != 999999)
	{
		//리스트 입력 
		LV_ITEM															lvitem;
		int																nCount, nDlIdx(0), nDlIdx2(0), nIdx(0);
		int																nMTR_TRID(0), nMTR_BANK(0);
		CString															szCount, szName, szData, szKEY;
		float fTR_TRMVA = 0;
		float fTR_POSX = 0;
		float fTR_ZERX = 0;
		float fTR_PTRVH = 0;
		float fTR_PTRVL = 0;
		float fTR_CTRCH = 0;
		float fTR_CTRCL = 0;

		m_ctrListMTR.DeleteAllItems();

		nCount = theAppDataMng->GetTableRealCount(_T("MTR_STA"));
		for (int i = 1; i <= nCount; i++)
		{
			nDlIdx = GETVALUE(int, _T("MTR_STA"), _T("MTR_II_SS"), i);
			nMTR_TRID = GETVALUE(int, _T("MTR_STA"), _T("MTR_HI_TR"), i);
			if (nDlIdx == 0)											continue;
			if (nDlIdx != m_nSUBS_CSVID)								continue;

			szName = GETSTRING(_T("MTR_STA"), _T("MTR_NM"), i);
			nMTR_BANK = GETVALUE(int, _T("MTR_STA"), _T("MTR_BANK"), i);
			ullCEQID = GETVALUE(unsigned long long, "MTR_STA", "MTR_MAINTRID", i);
			szKEY.Format(_T("%lld"), ullCEQID);


			fTR_TRMVA = GETVALUE(double, _T("TR_STA"), _T("TR_TRMVA"), nMTR_TRID);
			fTR_POSX = GETVALUE(double, _T("TR_STA"), _T("TR_POSX"), nMTR_TRID);
			fTR_ZERX = GETVALUE(double, _T("TR_STA"), _T("TR_ZERX"), nMTR_TRID);
			fTR_PTRVH = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PTRVH"), nMTR_TRID);
			fTR_PTRVL = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PTRVL"), nMTR_TRID);
			fTR_CTRCH = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_CTRCH"), nMTR_TRID);
			fTR_CTRCL = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_CTRCL"), nMTR_TRID);

			lvitem.mask = LVIF_TEXT;
			lvitem.iItem = nIdx;
			lvitem.iSubItem = 0;
			lvitem.pszText = (LPWSTR)(LPCTSTR)_T("");
			m_ctrListMTR.InsertItem(&lvitem);

			szData.Format(_T("%d"), nIdx);
			m_ctrListMTR.SetItemText(nIdx, 1, szData);

			m_ctrListMTR.SetItemText(nIdx, 2, szName);
			m_ctrListMTR.SetItemText(nIdx, 3, szKEY);
			szData.Format(_T("%d"), nMTR_BANK);
			m_ctrListMTR.SetItemText(nIdx, 4, szData);
			szData.Format(_T("%.2f"), fTR_TRMVA);
			m_ctrListMTR.SetItemText(nIdx, 5, szData);
			szData.Format(_T("%.2f"), fTR_POSX);
			m_ctrListMTR.SetItemText(nIdx, 6, szData);
			szData.Format(_T("%.2f"), fTR_ZERX);
			m_ctrListMTR.SetItemText(nIdx, 7, szData);
			szData.Format(_T("%.2f"), fTR_PTRVH);
			m_ctrListMTR.SetItemText(nIdx, 8, szData);
			szData.Format(_T("%.2f"), fTR_PTRVL);
			m_ctrListMTR.SetItemText(nIdx, 9, szData);
			szData.Format(_T("%.2f"), fTR_CTRCH);
			m_ctrListMTR.SetItemText(nIdx, 10, szData);
			szData.Format(_T("%.2f"), fTR_CTRCL);
			m_ctrListMTR.SetItemText(nIdx, 11, szData);

			m_ListMTR[nIdx] = i;
			nIdx++;
		}

		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT3, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT4, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT5, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT6, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT7, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT8, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT9, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT10, stNULL);
	}
	else
	{
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT1, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT2, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT3, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT4, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT5, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT6, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT7, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT8, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT9, stNULL);
		SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT10, stNULL);
	}
}

void CDNDObj_KASIM_MTR_TAP::OnBnClickedDndobjectKasimMTRDlgBtn1()
{
	CString stNULL;
	stNULL.Format(_T("0"));
	CString szName, szKey, szBank, szKeyND;
	int nMTRBank;
	CString szTR_TRMVA, szTR_POSX, szTR_ZERX, szTR_PTRVH, szTR_PTRVL, szTR_CTRCH, szTR_CTRCL;
	float fTR_TRMVA = 0;
	float fTR_POSX = 0;
	float fTR_ZERX = 0;
	float fTR_PTRVH = 0;
	float fTR_PTRVL = 0;
	float fTR_CTRCH = 0;
	float fTR_CTRCL = 0;
	int nCount, nDlIdx;
	int nCheck = 0;
	int nID = 0;
	int nBRID = 0;
	int nNDID = 0;

	int nIJ_CSVID = 0;
	int nLD_CSVID = 0;

	nCount = theAppDataMng->GetTableRealCount(_T("MTR_STA"));
	szKey.Format(_T("9999179%07d"), nCount + 1);
	szKeyND.Format(_T("999917%08d01"), nCount + 1);
	nID = theAppDataMng->GetTableRealCount(_T("TR_STA"));
	nBRID = theAppDataMng->GetTableRealCount(_T("BR_STA"));
	nNDID = theAppDataMng->GetTableRealCount(_T("ND_STA"));

	nIJ_CSVID = theAppDataMng->GetTableRealCount(_T("IJ_STA"));
	nLD_CSVID = theAppDataMng->GetTableRealCount(_T("LD_STA"));

	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT1, szName);
	//GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT2, szKey);
	//GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT3, szBank);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT4, szTR_TRMVA);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT5, szTR_POSX);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT6, szTR_ZERX);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT7, szTR_PTRVH);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT8, szTR_PTRVL);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT9, szTR_CTRCH);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT10, szTR_CTRCL);

	if (szName == "")
	{
		AfxMessageBox(_T("이름이 없습니다."));
		nCheck = 9999;
	}
	//같은 데이터가 있으면 넣지 않는다!
	if (nCheck == 0)
	{
		nCount = nCount + 1; //MTRID
		nID = nID + 1; //TRID
		nBRID = nBRID + 1; //BRID
		nNDID = nNDID + 1;
		nIJ_CSVID = nIJ_CSVID + 1;
		nLD_CSVID = nLD_CSVID + 1;
		//
				//
		int nBR_II_EQU = 0, nBR_WhileID = nBRID, nGBR_II_EQUTY = 0;
		while (nBR_II_EQU == 0)
		{
			if (nBRID == 999999)
			{
				break;
			}
			if (nBR_WhileID == 1)
			{
				nBR_II_EQU = 1;
				break;
			}
			nGBR_II_EQUTY = GETVALUE(int, _T("gbr_sta"), _T("GBR_II_EQUTY"), nBR_WhileID - 1);
			if (nGBR_II_EQUTY == 2)
			{
				nBR_II_EQU = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equ"), nBR_WhileID - 1);
				nBR_II_EQU = nBR_II_EQU + 1;
				break;
			}
			else
			{
				nBR_WhileID = nBR_WhileID - 1;
			}
		}
		//변전소 찾기 부분!!

		int nGenID = 0;
		int nSSNDID = 0;
		int nNDBR_FBR = 0;
		int nNDBR_TBR = 0;
		int nSSGBR_II_EQUTY = 0;


		nGenID = GETVALUE(int, _T("SS_STA"), _T("SS_II_VGEN"), m_nSUBS_CSVID);	//SS에서 GEN 아이디 찾기
		nSSNDID = GETVALUE(int, _T("GEN_STA"), _T("GEN_II_ND"), nGenID);			//GEN ND 아이디 찾기!
		//연결된 BR이 있는지 찾아볼까?
		nNDBR_FBR = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FBR"), nSSNDID);
		nNDBR_TBR = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TBR"), nSSNDID);
		//신규는 여기서 들어와서 찾겠지?
		if (nNDBR_FBR != 0)
		{
			nSSGBR_II_EQUTY = GETVALUE(int, _T("GBR_STA"), _T("GBR_II_EQUTY"), nNDBR_FBR);
		}
		if (nNDBR_TBR != 0 && nSSGBR_II_EQUTY != 2)
		{
			nSSGBR_II_EQUTY = GETVALUE(int, _T("GBR_STA"), _T("GBR_II_EQUTY"), nNDBR_TBR);
		}
		if (nSSGBR_II_EQUTY != 2 && nNDBR_FBR != 0 && nNDBR_TBR != 0) //아마 기존꺼는 여기로 들어올꺼고 
		{
			nSSNDID = nSSNDID + 1;
			nNDBR_FBR = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FBR"), nSSNDID);
			nNDBR_TBR = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TBR"), nSSNDID);

			if (nNDBR_FBR != 0)
			{
				nSSGBR_II_EQUTY = GETVALUE(int, _T("GBR_STA"), _T("GBR_II_EQUTY"), nNDBR_FBR);
			}
			if (nNDBR_TBR != 0 && nSSGBR_II_EQUTY != 2)
			{
				nSSGBR_II_EQUTY = GETVALUE(int, _T("GBR_STA"), _T("GBR_II_EQUTY"), nNDBR_TBR);
			}
		}
		if (nSSGBR_II_EQUTY != 2)//이건 완전 잘못된것
		{
			//이건 신규가 아닌 기존꺼로 해야겠는데?
			//nSSGBR_II_EQUTY = nGBR_II_EQUTY;
		}
		//
		//MTR 뱅크 찾기
		int nMTR_BANK_Count = 0;
		nMTR_BANK_Count = GET_MTR_BANK(m_nSUBS_CSVID);
		//MTR_STA
		PUTVALUE(_T("MTR_STA"), _T("MTR_NM"), nCount, (wchar_t*)szName.GetBuffer());
		PUTVALUE(_T("MTR_STA"), _T("MTR_MAINTRID"), nCount, (unsigned long long)_wtoll(szKey));
		PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_II_SS"), nCount, (int)m_nSUBS_CSVID);
		PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_HI_TR"), nCount, (int)nID);
		PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_BANK"), nCount, (int)nMTR_BANK_Count);
		//
		PUTDOUBLE2VALUE(_T("MTR_DYN_UIN"), _T("MTR_SOP_FLAG"), nCount, (int)0);
		PUTDOUBLE2VALUE(_T("MTR_DYN_NCPO"), _T("MTR_HI_ND"), nCount, (int)0);
		PUTDOUBLE2VALUE(_T("MTR_DYN_RPFO"), _T("MTR_3PGENRPFMW"), nCount, (int)0);
		PUTDOUBLE2VALUE(_T("MTR_DYN_VVOO"), _T("MTR_3PGENVVOMW"), nCount, (int)0);

		//TR_STA
		PUTVALUE(_T("TR_STA"), _T("TR_NM"), nID, (wchar_t*)szName.GetBuffer());
		PUTVALUE(_T("TR_STA"), _T("TR_CEQID"), nID, (unsigned long long)_wtoll(szKey));
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TYPE"), nID, (int)1);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_BR"), nID, (int)nBRID);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_FNORKV"), nID, (double)154);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TNORKV"), nID, (double)22.9);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TRMVA"), nID, (double)_wtof(szTR_TRMVA));
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_CONTY"), nID, (int)2);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ONLTC"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_POSX"), nID, (double)_wtof(szTR_POSX));
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ZERX"), nID, (double)_wtof(szTR_ZERX));
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMX"), nID, (int)21);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMN"), nID, (int)1);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPNOR"), nID, (int)11);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPSTEP"), nID, (double)-0.0125);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMX"), nID, (int)21);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMN"), nID, (int)1);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nID, (int)11);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nID, (double)-0.0125);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMX"), nID, (int)21);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMN"), nID, (int)1);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPNOR"), nID, (int)11);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPSTEP"), nID, (double)-0.0125);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_CONND"), nID, (int)nSSNDID);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PGR"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PGX"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SGR"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SGX"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_SS"), nID, (int)m_nSUBS_CSVID);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SI_SS"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_MTR"), nID, (int)nCount);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SI_MTR"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_LOCTAP"), nID, (int)0);

		//TR_DYN_UIN
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CON3P"), nID, (int)1);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_II_PFVM"), nID, (int)1);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_3CONMEAP"), nID, (int)1);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMX"), nID, (int)140);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMN"), nID, (int)85);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFSS"), nID, (int)0.5);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMX"), nID, (int)9);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMN"), nID, (int)0.5);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWSS"), nID, (int)0.1);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMX"), nID, (int)25);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMN"), nID, (int)-25);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXSS"), nID, (int)1);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PDVRFLAG"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVH"), nID, (int)_wtof(szTR_PTRVH));
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVL"), nID, (int)_wtof(szTR_PTRVL));
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCH"), nID, (int)_wtof(szTR_CTRCH));
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCL"), nID, (int)_wtof(szTR_CTRCL));
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_LDCTYPE"), nID, (int)3);
		//
		PUTDOUBLE2VALUE(_T("TR_DYN_MEA"), _T("TR_PAMEATAP"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_NCPO"), _T("TR_DEAD"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PAVREFOLD"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PAVREF"), nID, (int)0);


		//ND
		PUTVALUE(_T("ND_STA"), _T("ND_NM"), nNDID, (wchar_t*)szName.GetBuffer());
		PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nNDID, (unsigned long long)_wtoll(szKey));
		PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nNDID, (unsigned long long)_wtoll(szKeyND));
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nNDID, (int)nNDID);
		//
		PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_DL"), nNDID, (int)0);
		//GND입력부분
		PUTVALUE(_T("GND_STA"), _T("GND_NM"), nNDID, (wchar_t*)szName.GetBuffer());
		//
		PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_SI_ISL "), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIONW"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FC_3LL"), nNDID, (int)0);
		//BR
		PUTVALUE(_T("br_sta"), _T("br_nm"), nBRID, (wchar_t*)szName.GetBuffer());
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_equ"), nBRID, (int)nBR_II_EQU);
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_gbr"), nBRID, (int)nBRID);
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_dl"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_fnd"), nBRID, (int)nSSNDID);
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_tnd"), nBRID, (int)nNDID);
		//GBR
		PUTVALUE(_T("gbr_sta"), _T("gbr_nm"), nBRID, (wchar_t*)szName.GetBuffer());
		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_equ"), nBRID, (int)nBR_II_EQU);
		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("GBR_HI_BR"), nBRID, (int)nBRID);
		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("GBR_II_EQUTY"), nBRID, (int)2);
		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_fgnd"), nBRID, (int)nSSNDID);
		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_tgnd"), nBRID, (int)nNDID);
		//
		PUTDOUBLE2VALUE(_T("GBR_DYN_UIN"), _T("GBR_MORFLAG"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PA_C"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_SI_FBS"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMW12"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMW12"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIONW"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("GBR_DYN_VVOAV"), _T("GBR_VVORECFLAG"), nBRID, (int)0);

	}

	LoadKASIM();
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_MTR_TAP::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CDNDObj_KASIM_MTR_TAP::OnBnClickedDndobjectKasimMTRDlgBtn2()
{
	CString stNULL;
	stNULL.Format(_T("0"));
	CString szName, szKey, szBank, szKeyND;
	int nMTRBank;
	CString szTR_TRMVA, szTR_POSX, szTR_ZERX, szTR_PTRVH, szTR_PTRVL, szTR_CTRCH, szTR_CTRCL;
	float fTR_TRMVA = 0;
	float fTR_POSX = 0;
	float fTR_ZERX = 0;
	float fTR_PTRVH = 0;
	float fTR_PTRVL = 0;
	float fTR_CTRCH = 0;
	float fTR_CTRCL = 0;
	int nID = 0;
	int nBRID = 0, nNDID = 0;

	UpdateData(TRUE);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT1, szName);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT2, szKey);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT3, szBank);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT4, szTR_TRMVA);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT5, szTR_POSX);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT6, szTR_ZERX);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT7, szTR_PTRVH);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT8, szTR_PTRVL);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT9, szTR_CTRCH);
	GetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT10, szTR_CTRCL);

	///////////////////////////
	if (m_nMTRIndex != 9999)
	{
		//MTR_STA
		PUTVALUE(_T("MTR_STA"), _T("MTR_NM"), m_nMTRIndex, (wchar_t*)szName.GetBuffer());
		PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_II_SS"), m_nMTRIndex, (int)m_nSUBS_CSVID);
		PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_BANK"), m_nMTRIndex, (int)_wtoi(szBank));

		nID = GETVALUE(int, _T("MTR_STA"), _T("MTR_HI_TR"), m_nMTRIndex);
		//TR_STA
		PUTVALUE(_T("TR_STA"), _T("TR_NM"), nID, (wchar_t*)szName.GetBuffer());
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TRMVA"), nID, (double)_wtof(szTR_TRMVA));
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_POSX"), nID, (double)_wtof(szTR_POSX));
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_MTR"), nID, (int)m_nMTRIndex);
		//TR_DYN_UIN
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVH"), nID, (int)_wtof(szTR_PTRVH));
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVL"), nID, (int)_wtof(szTR_PTRVL));
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCH"), nID, (int)_wtof(szTR_CTRCH));
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCL"), nID, (int)_wtof(szTR_CTRCL));
		////////////////////////

		nBRID = GETVALUE(int, _T("TR_STA"), _T("TR_II_BR"), nID);			   
		//BR
		PUTVALUE(_T("br_sta"), _T("br_nm"), nBRID, (wchar_t*)szName.GetBuffer());
		//GBR
		PUTVALUE(_T("gbr_sta"), _T("gbr_nm"), nBRID, (wchar_t*)szName.GetBuffer());

		nNDID = GETVALUE(int, _T("TR_STA"), _T("TR_II_CONND"), nID);
		//ND
		PUTVALUE(_T("ND_STA"), _T("ND_NM"), nNDID, (wchar_t*)szName.GetBuffer());
		//GND입력부분
		PUTVALUE(_T("GND_STA"), _T("GND_NM"), nNDID, (wchar_t*)szName.GetBuffer());
	}
	LoadKASIM();
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_KASIM_MTR_TAP::OnUpdateUI_Btn2(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CDNDObj_KASIM_MTR_TAP::OnBnClickedDndobjectKasimMTRDlgBtn3()
{
	CString stNULL;
	stNULL.Format(_T("0"));
	int nID = 0;
	int nNDID = 0;
	int nBRID = 0;
	int nIJID = 0;
	int nLDID = 0;
	if (m_nMTRIndex != 9999)
	{
		//
		nID = GETVALUE(int, _T("MTR_STA"), _T("MTR_HI_TR"), m_nMTRIndex);
		nNDID = GETVALUE(int, _T("TR_STA"), _T("TR_II_CONND"), nID);
		nBRID = GETVALUE(int, _T("TR_STA"), _T("TR_II_BR"), nID);

		PUTVALUE(_T("MTR_STA"), _T("MTR_NM"), m_nMTRIndex, (wchar_t*)stNULL.GetBuffer());
		PUTVALUE(_T("MTR_STA"), _T("MTR_MAINTRID"), m_nMTRIndex, (unsigned long long)_wtoll(stNULL));
		PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_II_SS"), m_nMTRIndex, (int)0);
		//TR_STA
		PUTVALUE(_T("TR_STA"), _T("TR_NM"), nID, (wchar_t*)stNULL.GetBuffer());
		PUTVALUE(_T("TR_STA"), _T("TR_CEQID"), nID, (unsigned long long)_wtoll(stNULL));
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TYPE"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_BR"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_FNORKV"), nID, (double)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TNORKV"), nID, (double)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TRMVA"), nID, (double)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_CONTY"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ONLTC"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_POSX"), nID, (double)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ZERX"), nID, (double)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMX"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMN"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPNOR"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPSTEP"), nID, (double)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMX"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMN"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nID, (double)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMX"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMN"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPNOR"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPSTEP"), nID, (double)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_CONND"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PGR"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PGX"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SGR"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SGX"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_SS"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SI_SS"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_MTR"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SI_MTR"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_LOCTAP"), nID, (int)0);

		//TR_DYN_UIN
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CON3P"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_II_PFVM"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_3CONMEAP"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMX"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMN"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFSS"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMX"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMN"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWSS"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMX"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMN"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXSS"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PDVRFLAG"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVH"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVL"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCH"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCL"), nID, (int)0);
		PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_LDCTYPE"), nID, (int)0);
		//ND
		PUTVALUE(_T("ND_STA"), _T("ND_NM"), nNDID, (wchar_t*)stNULL.GetBuffer());
		PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nNDID, (unsigned long long)_wtoll(stNULL));
		PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nNDID, (unsigned long long)_wtoll(stNULL));
		//GND입력부분
		PUTVALUE(_T("GND_STA"), _T("GND_NM"), nNDID, (wchar_t*)stNULL.GetBuffer());
		//BR
		PUTVALUE(_T("br_sta"), _T("br_nm"), nBRID, (wchar_t*)stNULL.GetBuffer());
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_equ"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_gbr"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_dl"), nBRID, (int)0);
		//GBR
		PUTVALUE(_T("gbr_sta"), _T("gbr_nm"), nBRID, (wchar_t*)stNULL.GetBuffer());
		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_equ"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("GBR_HI_BR"), nBRID, (int)0);
		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("GBR_II_EQUTY"), nBRID, (int)2);

	}

	LoadKASIM();
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}


void CDNDObj_KASIM_MTR_TAP::OnUpdateUI_Btn3(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}


void CDNDObj_KASIM_MTR_TAP::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW*													pNMListView = (NM_LISTVIEW*)pNMHDR;

	int																nFindIdx;
	nFindIdx = pNMListView->iItem;
	m_nMTRIndex = m_ListMTR[nFindIdx];

	*pResult = 0;
}

void CDNDObj_KASIM_MTR_TAP::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	unsigned long long	ullCEQID(0U);
	CString szName, szKey, szBank;
	CString szTR_TRMVA, szTR_POSX, szTR_ZERX, szTR_PTRVH, szTR_PTRVL, szTR_CTRCH, szTR_CTRCL;
	int nMTR_TRID, nMTRBank;
	float fTR_TRMVA = 0;
	float fTR_POSX = 0;
	float fTR_ZERX = 0;
	float fTR_PTRVH = 0;
	float fTR_PTRVL = 0;
	float fTR_CTRCH = 0;
	float fTR_CTRCL = 0;

	NM_LISTVIEW*													pNMListView = (NM_LISTVIEW*)pNMHDR;
	int																nFindIdx;
	nFindIdx = pNMListView->iItem;
	m_nMTRIndex = m_ListMTR[nFindIdx];

	nMTR_TRID = GETVALUE(int, _T("MTR_STA"), _T("MTR_HI_TR"), m_nMTRIndex);

	szName = GETSTRING(_T("MTR_STA"), _T("MTR_NM"), m_nMTRIndex);
	ullCEQID = GETVALUE(unsigned long long, "MTR_STA", "MTR_MAINTRID", m_nMTRIndex);
	szKey.Format(_T("%lld"), ullCEQID);

	nMTRBank = GETVALUE(int, _T("MTR_STA"), _T("MTR_BANK"), m_nMTRIndex);

	fTR_TRMVA = GETVALUE(double, _T("TR_STA"), _T("TR_TRMVA"), nMTR_TRID);
	fTR_POSX = GETVALUE(double, _T("TR_STA"), _T("TR_POSX"), nMTR_TRID);
	fTR_ZERX = GETVALUE(double, _T("TR_STA"), _T("TR_ZERX"), nMTR_TRID);
	fTR_PTRVH = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PTRVH"), nMTR_TRID);
	fTR_PTRVL = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_PTRVL"), nMTR_TRID);
	fTR_CTRCH = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_CTRCH"), nMTR_TRID);
	fTR_CTRCL = GETVALUE(double, _T("TR_DYN_UIN"), _T("TR_CTRCL"), nMTR_TRID);

	szBank.Format(_T("%d"), nMTRBank);
	szTR_TRMVA.Format(_T("%.2f"), fTR_TRMVA);
	szTR_POSX.Format(_T("%.2f"), fTR_POSX);
	szTR_ZERX.Format(_T("%.2f"), fTR_ZERX);
	szTR_PTRVH.Format(_T("%.2f"), fTR_PTRVH);
	szTR_PTRVL.Format(_T("%.2f"), fTR_PTRVL);
	szTR_CTRCH.Format(_T("%.2f"), fTR_CTRCH);
	szTR_CTRCL.Format(_T("%.2f"), fTR_CTRCL);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT1, szName);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT2, szKey);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT3, szBank);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT4, szTR_TRMVA);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT5, szTR_POSX);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT6, szTR_ZERX);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT7, szTR_PTRVH);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT8, szTR_PTRVL);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT9, szTR_CTRCH);
	SetDlgItemText(IDC_DNDOBJECT_KASIM_MTR_DLG_EDIT10, szTR_CTRCL);

	*pResult = 0;

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

BOOL CDNDObj_KASIM_MTR_TAP::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}



int CDNDObj_KASIM_MTR_TAP::GET_MTR_BANK(int nSSID)
{
	int i = 0;
	int nMTRSSID = 0;
	int nMTR_Count = 0;
	int nCount_MTR_table = theAppDataMng->GetTableRealCount(_T("MTR_STA"));
	for (i = 1; i <= (int)nCount_MTR_table; i++)
	{
		nMTRSSID = GETVALUE(int, _T("MTR_STA"), _T("MTR_II_SS"), i);
		if (nMTRSSID == nSSID)
		{
			nMTR_Count++;
		}
	}
	return nMTR_Count+1;
}