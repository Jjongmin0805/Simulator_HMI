// CDNDObj_Symbol_Tap.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_Symbol_Tap.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDNDObj_Symbol_Tap 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_Symbol_Tap, CDialog)

CDNDObj_Symbol_Tap::CDNDObj_Symbol_Tap(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNDOBJECT_TPA_SYMBOL_DLG, pParent)
{

}

CDNDObj_Symbol_Tap::~CDNDObj_Symbol_Tap()
{
}

void CDNDObj_Symbol_Tap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDNDObj_Symbol_Tap, CDialog)
	ON_BN_CLICKED(IDC_DNDOBJECT_DLG_BTN1, &CDNDObj_Symbol_Tap::OnBnClickedDndObjectDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DNDOBJECT_DLG_BTN1, &CDNDObj_Symbol_Tap::OnUpdateUI_Btn1)
END_MESSAGE_MAP()


// CDNDObj_Symbol_Tap 메시지 처리기

BOOL CDNDObj_Symbol_Tap::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  
}

void CDNDObj_Symbol_Tap::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	CDND_Switch* pSwitch = (CDND_Switch*)pDNDObj;

	CString strData[10];

	strData[0] = pSwitch->Get_ID_Real();
	strData[1] = pSwitch->m_str_psrtype;
	strData[2] = pSwitch->m_str_keyid;
	strData[3] = pSwitch->m_str_keyname;
	strData[4] = pSwitch->m_str_innertext;
	strData[5].Format(_T("%.4lf"), pSwitch->m_d_x);
	strData[6].Format(_T("%.4lf"), pSwitch->m_d_y);
	strData[7].Format(_T("%.4lf"), pSwitch->m_d_scalex);
	strData[8].Format(_T("%.4lf"), pSwitch->m_d_scaley);
	strData[9].Format(_T("%.4lf"), pSwitch->m_d_rotate);
	
	
	SetDlgItemText(IDC_DNDOBJECT_DLG_EDIT1, strData[0]);
	SetDlgItemText(IDC_DNDOBJECT_DLG_EDIT2, strData[1]);
	SetDlgItemText(IDC_DNDOBJECT_DLG_EDIT3, strData[2]);
	SetDlgItemText(IDC_DNDOBJECT_DLG_EDIT4, strData[3]);
	SetDlgItemText(IDC_DNDOBJECT_DLG_EDIT10, strData[4]);
	SetDlgItemText(IDC_DNDOBJECT_DLG_EDIT5, strData[5]);
	SetDlgItemText(IDC_DNDOBJECT_DLG_EDIT6, strData[6]);
	SetDlgItemText(IDC_DNDOBJECT_DLG_EDIT7, strData[7]);
	SetDlgItemText(IDC_DNDOBJECT_DLG_EDIT8, strData[8]);
	SetDlgItemText(IDC_DNDOBJECT_DLG_EDIT9, strData[9]);
	
	m_pDND_Switch = pSwitch;
}

void CDNDObj_Symbol_Tap::OnBnClickedDndObjectDlgBtn1()
{
 	CString strData[5];

	strData[0] = m_pDND_Switch->m_str_keyname;
	strData[1] = m_pDND_Switch->m_str_innertext;
	strData[2].Format(_T("%.4lf"), m_pDND_Switch->m_d_scalex);
	strData[3].Format(_T("%.4lf"), m_pDND_Switch->m_d_scaley);
	strData[4].Format(_T("%.4lf"), m_pDND_Switch->m_d_rotate);

	GetDlgItemText(IDC_DNDOBJECT_DLG_EDIT4, strData[0]);
	GetDlgItemText(IDC_DNDOBJECT_DLG_EDIT10, strData[1]);
	GetDlgItemText(IDC_DNDOBJECT_DLG_EDIT7, strData[2]);
	GetDlgItemText(IDC_DNDOBJECT_DLG_EDIT8, strData[3]);
	GetDlgItemText(IDC_DNDOBJECT_DLG_EDIT9, strData[4]);

	m_pDND_Switch->m_str_keyname = strData[0];
	m_pDND_Switch->m_str_innertext = strData[1];
	m_pDND_Switch->m_d_scalex = _wtof(strData[2]);
	m_pDND_Switch->m_d_scaley = _wtof(strData[3]);
	m_pDND_Switch->m_d_rotate = _wtof(strData[4]);
	
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

void CDNDObj_Symbol_Tap::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}


BOOL CDNDObj_Symbol_Tap::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}