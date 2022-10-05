// CDNDObj_Connect_DlgBar.cpp: 구현 파일

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_Connect_DlgBar.h"
#include "afxdialogex.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CDNDObj_Connect_DlgBar, CDialogBar)

CDNDObj_Connect_DlgBar::CDNDObj_Connect_DlgBar(CWnd* pParent /*=nullptr*/)
	: CDialogBar()
{
	m_TDND_KASIM_Tap = NULL;
}

CDNDObj_Connect_DlgBar::~CDNDObj_Connect_DlgBar()
{
	delete m_TDND_KASIM_Tap;
}

void CDNDObj_Connect_DlgBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DND_CONNECT_TAP, m_TConnect_Tap);
}


BEGIN_MESSAGE_MAP(CDNDObj_Connect_DlgBar, CDialogBar)
	ON_MESSAGE(WM_INITDIALOG, InitDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_DND_CONNECT_TAP, &CDNDObj_Connect_DlgBar::OnTcnSelchangeDndConnectTap)
	ON_BN_CLICKED(IDC_DND_CONNECT_DLG_CANCEL, &CDNDObj_Connect_DlgBar::OnBnClickedDndConnectDlgCancel)
	ON_UPDATE_COMMAND_UI(IDC_DND_CONNECT_DLG_CANCEL, &CDNDObj_Connect_DlgBar::OnUpdateUI_Btn)
END_MESSAGE_MAP()

BOOL CDNDObj_Connect_DlgBar::Create(CWnd* pParentWnd, UINT nStyle)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	return CDialogBar::Create(pParentWnd, MAKEINTRESOURCE(IDD), nStyle, IDD);
}

LRESULT CDNDObj_Connect_DlgBar::InitDialog(WPARAM wp, LPARAM lp)
{
	UpdateData(FALSE);
	if (!HandleInitDialog(wp, lp))
	{
	
	}
	return OnInitDialog();
}

BOOL CDNDObj_Connect_DlgBar::OnInitDialog()
{
	CString strTmp1;
	strTmp1.Format(_T("선로정보"));
	m_TConnect_Tap.InsertItem(1, strTmp1);
	m_TConnect_Tap.SetCurSel(0);
	
	CRect rect;
 	m_TConnect_Tap.GetClientRect(&rect);
	m_TDND_KASIM_Tap = new CDNDObj_Connrct_KASIM_Tap();
	m_TDND_KASIM_Tap->Create(IDD_DND_CONNECT_TAP_KASIM_DLG, &m_TConnect_Tap);
	m_TDND_KASIM_Tap->MoveWindow(5, 25, rect.Width() - 10, rect.Height() - 30);
	m_TDND_KASIM_Tap->ShowWindow(SW_HIDE);

	return TRUE;
}

void CDNDObj_Connect_DlgBar::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	CDND_Connect* pConnect = (CDND_Connect*)pDNDObj;
	m_pDND_Connect = pConnect;

	m_TConnect_Tap.SetCurSel(0);
	m_TDND_KASIM_Tap->ShowWindow(SW_SHOW);
	m_TDND_KASIM_Tap->SetSelect_DNDObject(pDNDObj);
}

void CDNDObj_Connect_DlgBar::OnTcnSelchangeDndConnectTap(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nIndex = m_TConnect_Tap.GetCurSel();
	switch (nIndex)
	{
		case 0:
			m_TDND_KASIM_Tap->ShowWindow(SW_SHOW);
			break;
	}
	*pResult = 0;
}

void CDNDObj_Connect_DlgBar::OnUpdateUI_Btn(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CDNDObj_Connect_DlgBar::OnBnClickedDndConnectDlgCancel()
{
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->SettingWnd_Hide();
}

