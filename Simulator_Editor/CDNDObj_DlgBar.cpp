#include "pch.h"
#include "CDNDObj_DlgBar.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CDNDObj_DlgBar, CDialogBar)

CDNDObj_DlgBar::CDNDObj_DlgBar(CWnd* pParent /*=NULL*/)
	: CDialogBar()
{
	m_TObject_Symbol_Tap = NULL;
	m_TObject_KASIM_SW_Tap = NULL;
	m_nTap_Object = 0;
	m_nPRED_Tap_Object = 0;
}

CDNDObj_DlgBar::~CDNDObj_DlgBar()
{
	delete m_TObject_Symbol_Tap;
	delete m_TObject_KASIM_SW_Tap;
	delete m_TObject_KASIM_JUNCTION_Tap;
	delete m_TObject_KASIM_CONSUMER_Tap;
	delete m_TObject_KASIM_GENERATEUNIT_Tap;
	delete m_TObject_KASIM_PRDE_Tap;
	delete m_TObject_KASIM_PRDE_RECLOSER_Tap;
	delete m_TObject_KASIM_TR_Tap;
	delete m_TObject_KASIM_SUBS_Tap;
	delete m_TObject_KASIM_CB_Tap;
	delete m_TObject_KASIM_GENUNIT_Tap;
	delete m_TObject_KASIM_MTR_Tap;
}

void CDNDObj_DlgBar::DoDataExchange(CDataExchange* pDX)
{
	//	DDX_Control(pDX, IDC_DNDOBJECT_DLG_COMBO1, m_ctrCombo);

	CDialogBar::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNDOBJECT_DLG_TAB, m_TObject_Tap);
}

BOOL CDNDObj_DlgBar::Create(CWnd* pParentWnd,  UINT nStyle)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogBar::Create(pParentWnd, MAKEINTRESOURCE(IDD), nStyle, IDD);
}

BEGIN_MESSAGE_MAP(CDNDObj_DlgBar, CDialogBar)
	ON_MESSAGE(WM_INITDIALOG, InitDialog)
	ON_BN_CLICKED(IDC_DNDOBJECT_DLG_CANCEL, &CDNDObj_DlgBar::OnBnClickedDndobjectDlgBtn2)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_DLG_CANCEL, &CDNDObj_DlgBar::OnUpdateUI_Btn2)
	ON_NOTIFY(TCN_SELCHANGE, IDC_DNDOBJECT_DLG_TAB, &CDNDObj_DlgBar::OnTcnSelchangeDndobjectDlgTab)
END_MESSAGE_MAP()


LRESULT CDNDObj_DlgBar::InitDialog(WPARAM wp, LPARAM lp)
{
 	UpdateData(FALSE);
	if (!HandleInitDialog(wp, lp))
	{
		//return FALSE;
	}
	return OnInitDialog();
}

BOOL CDNDObj_DlgBar::OnInitDialog()
{

	CRect rect;
	m_TObject_Tap.GetClientRect(&rect);

	m_TObject_KASIM_SW_Tap = new CDNDObj_KASIM_SW_TAP();
	m_TObject_KASIM_SW_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_SW_DLG, &m_TObject_Tap);
	m_TObject_KASIM_SW_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);

	m_TObject_KASIM_JUNCTION_Tap = new CDNDObj_KASIM_JUNCTION_TAP();
	m_TObject_KASIM_JUNCTION_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_JUNCTION_DLG, &m_TObject_Tap);
	m_TObject_KASIM_JUNCTION_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);

	m_TObject_KASIM_CONSUMER_Tap = new CDNDObj_KASIM_CONSUMER_TAP();
	m_TObject_KASIM_CONSUMER_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_CONSUMER_DLG, &m_TObject_Tap);
	m_TObject_KASIM_CONSUMER_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);

	m_TObject_KASIM_GENERATEUNIT_Tap = new CDNDObj_KASIM_GENERATEUNIT_TAP();
	m_TObject_KASIM_GENERATEUNIT_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_GENERATEUNIT_DLG, &m_TObject_Tap);
	m_TObject_KASIM_GENERATEUNIT_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
	//20210914
	m_TObject_KASIM_GENUNIT_Tap = new CDNDObj_KASIM_GENUNIT_TAP();
	m_TObject_KASIM_GENUNIT_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_GENUNIT_DLG, &m_TObject_Tap);
	m_TObject_KASIM_GENUNIT_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);

	m_TObject_KASIM_PRDE_Tap = new CDNDObj_KASIM_PRDE_TAP();
	m_TObject_KASIM_PRDE_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_PRDE_DLG, &m_TObject_Tap);
	m_TObject_KASIM_PRDE_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE);

	m_TObject_KASIM_PRDE_RECLOSER_Tap = new CDNDObj_KASIM_PRDE_RECLOSER_TAP();
	m_TObject_KASIM_PRDE_RECLOSER_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_PRDE_RECLOSER_DLG, &m_TObject_Tap);
	m_TObject_KASIM_PRDE_RECLOSER_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE);

	m_TObject_KASIM_TR_Tap = new CDNDObj_KASIM_TR_TAP();
	m_TObject_KASIM_TR_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_TR_DLG, &m_TObject_Tap);
	m_TObject_KASIM_TR_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);

	m_TObject_KASIM_SUBS_Tap = new CDNDObj_KASIM_SUBS_TAP();
	m_TObject_KASIM_SUBS_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_SUBS_DLG, &m_TObject_Tap);
	m_TObject_KASIM_SUBS_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);

	m_TObject_KASIM_MTR_Tap = new CDNDObj_KASIM_MTR_TAP();
	m_TObject_KASIM_MTR_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_MTR_DLG, &m_TObject_Tap);
	m_TObject_KASIM_MTR_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);

	m_TObject_KASIM_CB_Tap = new CDNDObj_KASIM_CB_TAP();
	m_TObject_KASIM_CB_Tap->Create(IDD_DNDOBJECT_TPA_KASIM_CB_DLG, &m_TObject_Tap);
	m_TObject_KASIM_CB_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);

	return TRUE;
}


void CDNDObj_DlgBar::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	CDND_Switch* pSwitch = (CDND_Switch*)pDNDObj;
	CSB_BLOCK* pBlock = (CSB_BLOCK*)pDNDObj->m_SB_Object;

	int nCEQ_Type = 0;
	CString stCEQ_TYPE;
	
	if (pDNDObj->m_str_psrtype == "COMPSWITCH" || pDNDObj->m_str_psrtype == "TR")
	{
		if (pDNDObj->m_str_innertext == "")
		{
			m_TObject_Tap.DeleteAllItems();
			return;
		}
	}

	CString  strTmp2, strTmp3, strTmp4, strTmp5;

	int a = m_TObject_Tap.GetCurSel();
	m_TObject_Tap.DeleteAllItems();
	if ( pDNDObj->m_str_psrtype == "BREAKER"  )
	{	
		strTmp2.Format(_T("BREAKER"));
		strTmp3.Format(_T("PRDE"));
		m_TObject_Tap.InsertItem(0, strTmp2);
		m_TObject_Tap.InsertItem(1, strTmp3);
		m_TObject_Tap.SetCurSel(0);
	}
	else if ( pDNDObj->m_str_psrtype == "CB")
	{
		strTmp2.Format(_T("CB"));
		strTmp3.Format(_T("PRDE"));
		m_TObject_Tap.InsertItem(0, strTmp2);
		m_TObject_Tap.InsertItem(1, strTmp3);
		m_TObject_Tap.SetCurSel(0);
	}
	else if (pDNDObj->m_str_psrtype == "RECLOSER" )
	{
		strTmp2.Format(_T("RECLOSER"));
		strTmp3.Format(_T("PRDE"));
		m_TObject_Tap.InsertItem(0, strTmp2);
		m_TObject_Tap.InsertItem(1, strTmp3);
		m_TObject_Tap.SetCurSel(0);
	}
	else if (pDNDObj->m_str_psrtype == "CONSUMER")
	{
		strTmp2.Format(_T("CONSUMER"));
		strTmp3.Format(_T("PRDE"));
		m_TObject_Tap.InsertItem(0, strTmp2);
		m_TObject_Tap.InsertItem(1, strTmp3);
		m_TObject_Tap.SetCurSel(0);
	}
	else if (pDNDObj->m_str_psrtype == "COMPSWITCH")
	{
		if (pDNDObj->m_str_innertext != "")
		{
			strTmp2.Format(_T("COMPSWITCH"));
			m_TObject_Tap.InsertItem(0, strTmp2);
			m_TObject_Tap.SetCurSel(0);
		}
	}
	else if (pDNDObj->m_str_psrtype == "TR")
	{
		if (pDNDObj->m_str_innertext != "")
		{
			strTmp2.Format(_T("TR"));
			m_TObject_Tap.InsertItem(0, strTmp2);
			m_TObject_Tap.SetCurSel(0);
		}
	}
	else if (pDNDObj->m_str_psrtype == "GENERATEUNIT" || pDNDObj->m_str_psrtype == "DG" || pDNDObj->m_str_psrtype ==  "ENERGYSOURCEEQ")
	{
		strTmp2.Format(_T("GENERATEUNIT"));
		strTmp3.Format(_T("PRDE"));
		strTmp5.Format(_T("GENUNIT"));
		m_TObject_Tap.InsertItem(0, strTmp2);
		m_TObject_Tap.InsertItem(1, strTmp3);
		m_TObject_Tap.InsertItem(2, strTmp5);
		m_TObject_Tap.SetCurSel(0);
	}
	else if (pDNDObj->m_str_psrtype == "SVR")
	{
		strTmp2.Format(_T("SVR"));
		m_TObject_Tap.InsertItem(0, strTmp2);
		m_TObject_Tap.SetCurSel(0);
	}
	else if (pDNDObj->m_str_psrtype == "JUNCTION")
	{
		strTmp2.Format(_T("JUNCTION"));
		m_TObject_Tap.InsertItem(0, strTmp2);
		m_TObject_Tap.SetCurSel(0);
	}
	else if (pDNDObj->m_str_psrtype == "CABLEPOLE")
	{
		strTmp2.Format(_T("CABLEPOLE"));
		m_TObject_Tap.InsertItem(0, strTmp2);
		m_TObject_Tap.SetCurSel(0);
	}
	else if (pDNDObj->m_str_psrtype == "SUBSTATION")
	{
		strTmp2.Format(_T("SUBSTATION"));
		strTmp3.Format(_T("MTR"));
		m_TObject_Tap.InsertItem(0, strTmp2);
		m_TObject_Tap.InsertItem(1, strTmp3);
		m_TObject_Tap.SetCurSel(0);
	}
	else
	{
		strTmp2.Format(_T("SWITCH"));
		m_TObject_Tap.InsertItem(0, strTmp2);
		m_TObject_Tap.SetCurSel(0);
	}

	m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
	m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
	m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
	m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
	m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
	m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
	m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
	m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
	m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
	m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
	m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
	///////////////////////// 확인작업!
	//SWITCH - BREAKER - TR - COMPSWITCH - 
	if ( pDNDObj->m_str_psrtype == "BREAKER")
	{
		m_TObject_KASIM_SW_Tap->ShowWindow(SW_SHOW);
		m_TObject_KASIM_SW_Tap->SetSelect_DNDObject(pDNDObj);
		m_nTap_Object = 0;

		m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
		m_TObject_KASIM_PRDE_Tap->SetSelect_DNDObject(pDNDObj);
		m_nPRED_Tap_Object = 0;

	}
	else if (pDNDObj->m_str_psrtype == "RECLOSER" )
	{
		m_TObject_KASIM_SW_Tap->ShowWindow(SW_SHOW);
		m_TObject_KASIM_SW_Tap->SetSelect_DNDObject(pDNDObj);
		m_nTap_Object = 0;

		m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
		m_TObject_KASIM_PRDE_RECLOSER_Tap->SetSelect_DNDObject(pDNDObj);
		m_nPRED_Tap_Object = 1;

	}
	//JUNCTION - CABLEPOLE
	else if (pDNDObj->m_str_psrtype == "JUNCTION" || pDNDObj->m_str_psrtype == "CABLEPOLE" )
	{
		m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_SHOW);
		m_TObject_KASIM_JUNCTION_Tap->SetSelect_DNDObject(pDNDObj);
		m_nTap_Object = 1;	
	}
	//CONSUMER
	else if (pDNDObj->m_str_psrtype == "CONSUMER")
	{
		m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_SHOW);
		m_TObject_KASIM_CONSUMER_Tap->SetSelect_DNDObject(pDNDObj);
		m_nTap_Object = 2;
		//PRDE
		m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
		m_TObject_KASIM_PRDE_Tap->SetSelect_DNDObject(pDNDObj);
		m_nPRED_Tap_Object = 0;
	}
	//GENERATEUNIT
	else if (pDNDObj->m_str_psrtype == "GENERATEUNIT" || pDNDObj->m_str_psrtype == "DG" || pDNDObj->m_str_psrtype == "ENERGYSOURCEEQ")
	{
		m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_SHOW);
		m_TObject_KASIM_GENERATEUNIT_Tap->SetSelect_DNDObject(pDNDObj);
		m_nTap_Object = 3;
		//PRDE
		m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
		m_TObject_KASIM_PRDE_Tap->SetSelect_DNDObject(pDNDObj);
		//GENUNIT
		m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE); 
		m_TObject_KASIM_GENUNIT_Tap->SetSelect_DNDObject(pDNDObj);
		m_nPRED_Tap_Object = 0;
	}
	else if (pDNDObj->m_str_psrtype == "COMPSWITCH" || pDNDObj->m_str_psrtype == "TR")
	{
		if (pDNDObj->m_str_innertext != "")
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_SHOW);
			m_TObject_KASIM_SW_Tap->SetSelect_DNDObject(pDNDObj);
			m_nTap_Object = 0;
		}
	}
	else if (pDNDObj->m_str_psrtype == "SVR" )
	{
		m_TObject_KASIM_TR_Tap->ShowWindow(SW_SHOW);
		m_TObject_KASIM_TR_Tap->SetSelect_DNDObject(pDNDObj);
		m_nTap_Object = 6;
	}
	//20210826 신규 추가내용
	else if (pDNDObj->m_str_psrtype == "CB")
	{
		m_TObject_KASIM_CB_Tap->ShowWindow(SW_SHOW);
		m_TObject_KASIM_CB_Tap->SetSelect_DNDObject(pDNDObj);
		m_nTap_Object = 4;

		m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
		m_TObject_KASIM_PRDE_Tap->SetSelect_DNDObject(pDNDObj);
		m_nPRED_Tap_Object = 0;

	}
	else if (pDNDObj->m_str_psrtype == "SUBSTATION")
	{
		m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_SHOW);
		m_TObject_KASIM_SUBS_Tap->SetSelect_DNDObject(pDNDObj);
		m_nTap_Object = 5;
		//MTR
		m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
		m_TObject_KASIM_MTR_Tap->SetSelect_DNDObject(pDNDObj);
		m_nPRED_Tap_Object = 2;
	}
	else
	{
		m_TObject_KASIM_SW_Tap->ShowWindow(SW_SHOW);
		m_TObject_KASIM_SW_Tap->SetSelect_DNDObject(pDNDObj);
		m_nTap_Object = 0;
	}
	stCEQ_TYPE.Format(_T("%s"), pBlock->m_strCEQType);
	nCEQ_Type = _ttoi(stCEQ_TYPE);
}

void CDNDObj_DlgBar::OnUpdateUI_Btn2(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CDNDObj_DlgBar::OnBnClickedDndobjectDlgBtn2()
{
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->SettingWnd_Hide();
}

void CDNDObj_DlgBar::OnTcnSelchangeDndobjectDlgTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nIndex = m_TObject_Tap.GetCurSel();
	switch (nIndex)
	{
	case 0:// 
		if (m_nTap_Object == 0)
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_SHOW);
			m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
			break;
		}
		if (m_nTap_Object == 1)
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_SHOW);
			m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
			break;
		}
		if (m_nTap_Object == 2)
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_SHOW);
			m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
			break;
		}
		if (m_nTap_Object == 3)
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_SHOW);
			m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
			break;
		}
		if (m_nTap_Object == 4) //CB
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CB_Tap->ShowWindow(SW_SHOW);
			m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
			break;
		}
		if (m_nTap_Object == 5) //SUBS
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_SHOW);
			m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
			break;
		}
		if (m_nTap_Object == 6)
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_TR_Tap->ShowWindow(SW_SHOW);
			m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
			break;
		}
		break;
	case 1:// 
		if (m_nPRED_Tap_Object == 0)
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_SHOW); //PRDE
			m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
			break;
		}
		if (m_nPRED_Tap_Object == 1)
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_SHOW); //PRDE
			m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
			break;
		}
		if (m_nPRED_Tap_Object == 2)
		{
			m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
			m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
			m_TObject_KASIM_MTR_Tap->ShowWindow(SW_SHOW);
			break;
		}
		break;
	case 2:// 
		m_TObject_KASIM_SW_Tap->ShowWindow(SW_HIDE);
		m_TObject_KASIM_JUNCTION_Tap->ShowWindow(SW_HIDE);
		m_TObject_KASIM_CONSUMER_Tap->ShowWindow(SW_HIDE);
		m_TObject_KASIM_GENERATEUNIT_Tap->ShowWindow(SW_HIDE);
		m_TObject_KASIM_GENUNIT_Tap->ShowWindow(SW_SHOW);
		m_TObject_KASIM_PRDE_Tap->ShowWindow(SW_HIDE); //PRDE
		m_TObject_KASIM_PRDE_RECLOSER_Tap->ShowWindow(SW_HIDE); //PRDE
		m_TObject_KASIM_TR_Tap->ShowWindow(SW_HIDE);
		m_TObject_KASIM_SUBS_Tap->ShowWindow(SW_HIDE);
		m_TObject_KASIM_CB_Tap->ShowWindow(SW_HIDE);
		m_TObject_KASIM_MTR_Tap->ShowWindow(SW_HIDE);
		break;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
