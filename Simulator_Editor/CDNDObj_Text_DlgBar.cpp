// CDNDObj_Text_DlgBar.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_Editor.h"
#include "CDNDObj_Text_DlgBar.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CDNDObj_Text_DlgBar 대화 상자

IMPLEMENT_DYNAMIC(CDNDObj_Text_DlgBar, CDialogBar)

CDNDObj_Text_DlgBar::CDNDObj_Text_DlgBar(CWnd* pParent /*=nullptr*/)
	: CDialogBar()
{

}

CDNDObj_Text_DlgBar::~CDNDObj_Text_DlgBar()
{
}

void CDNDObj_Text_DlgBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DND_TEXT_DLG_COMBO1, m_ctrCombo[0]);
	DDX_Control(pDX, IDC_DND_TEXT_DLG_COMBO2, m_ctrCombo[1]);
	DDX_Control(pDX, IDC_DND_TEXT_DLG_COMBO3, m_ctrCombo[2]);
	DDX_Control(pDX, IDC_DND_TEXT_DLG_COMBO4, m_ctrCombo[3]);
}


BEGIN_MESSAGE_MAP(CDNDObj_Text_DlgBar, CDialogBar)
	ON_MESSAGE(WM_INITDIALOG,InitDialog)
	ON_BN_CLICKED(IDC_DND_TEXT_DLG_BTN2, &CDNDObj_Text_DlgBar::OnBnClickedDndTextDlgBtn2)
	ON_BN_CLICKED(IDC_DND_TEXT_DLG_BTN1, &CDNDObj_Text_DlgBar::OnBnClickedDndTextDlgBtn1)
	ON_UPDATE_COMMAND_UI(IDC_DND_TEXT_DLG_BTN1, &CDNDObj_Text_DlgBar::OnUpdateUI_Btn1)
	ON_UPDATE_COMMAND_UI(IDC_DND_TEXT_DLG_BTN2, &CDNDObj_Text_DlgBar::OnUpdateUI_Btn2)
END_MESSAGE_MAP()

BOOL CDNDObj_Text_DlgBar::Create(CWnd* pParentWnd, UINT nStyle)
{


	return CDialogBar::Create(pParentWnd, MAKEINTRESOURCE(IDD), nStyle, IDD);
}
// CDNDObj_Text_DlgBar 메시지 처리기

LRESULT CDNDObj_Text_DlgBar::InitDialog(WPARAM wp, LPARAM lp)
{
	UpdateData(FALSE);
	if (!HandleInitDialog(wp, lp) )
	{
		//return FALSE;
	}



	return OnInitDialog();
}

BOOL CDNDObj_Text_DlgBar::OnInitDialog()
{
	m_ctrCombo[0].AddString(_T("굴림"));
	m_ctrCombo[0].AddString(_T("맑은 고딕"));

	m_ctrCombo[1].AddString(_T("normal"));
	m_ctrCombo[1].AddString(_T("bold"));
	m_ctrCombo[1].AddString(_T("italic"));
	m_ctrCombo[1].AddString(_T("bolditalic"));
	m_ctrCombo[1].AddString(_T("underline"));
	m_ctrCombo[1].AddString(_T("strikeout"));

	m_ctrCombo[2].AddString(_T("start"));
	m_ctrCombo[2].AddString(_T("middle"));
	m_ctrCombo[2].AddString(_T("end"));

	m_ctrCombo[3].AddString(_T("top"));
	m_ctrCombo[3].AddString(_T("middle"));
	m_ctrCombo[3].AddString(_T("bottom"));

	return TRUE;
}

void CDNDObj_Text_DlgBar::SetSelect_DNDObject(CDND_Object* pDNDObj)
{
	CDND_Text* pText = (CDND_Text*)pDNDObj;
	m_pDND_Text = pText;

	CString strData[12];

	strData[0] = pText->Get_ID_Real();
	strData[1] = pText->GetTextSB()->m_strText;
	strData[2] = pText->GetTextSB()->m_strFont_family;
	strData[3].Format(_T("%d"), pText->GetTextSB()->m_nFont_size);
	strData[4] = pText->GetTextSB()->m_strFont_color;
	strData[5] = pText->GetTextSB()->m_strFont_style;
	strData[6] = pText->GetTextSB()->m_strFont_anchor;
	strData[7] = pText->GetTextSB()->m_strFont_valign;
	strData[8].Format(_T("%.4lf"), pText->GetTextSB()->m_dX);
	strData[9].Format(_T("%.4lf"), pText->GetTextSB()->m_dY);
	strData[10].Format(_T("%.4lf"), pText->GetTextSB()->m_dWidth);
	strData[11].Format(_T("%.4lf"), pText->GetTextSB()->m_dHeight);


	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT1, strData[0]);
	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT2, strData[1]);
	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT3, strData[3]);
	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT4, strData[4]);
	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT5, strData[8]);
	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT6, strData[9]);
	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT7, strData[10]);
	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT8, strData[11]);


	int nPos = m_ctrCombo[0].FindString(0,strData[2]);
	if (nPos != -1)
	{
		m_ctrCombo[0].SetCurSel(nPos);
	}

	nPos = m_ctrCombo[1].FindString(0, strData[5]);
	if (nPos != -1)
	{
		m_ctrCombo[1].SetCurSel(nPos);
	}

	nPos = m_ctrCombo[2].FindString(0, strData[6]);
	if (nPos != -1)
	{
		m_ctrCombo[2].SetCurSel(nPos);
	}

	nPos = m_ctrCombo[3].FindString(0, strData[7]);
	if (nPos != -1)
	{
		m_ctrCombo[3].SetCurSel(nPos);
	}
}

void CDNDObj_Text_DlgBar::OnUpdateUI_Btn1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CDNDObj_Text_DlgBar::OnUpdateUI_Btn2(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CDNDObj_Text_DlgBar::OnBnClickedDndTextDlgBtn2()
{
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->SettingWnd_Hide();
}


void CDNDObj_Text_DlgBar::OnBnClickedDndTextDlgBtn1()
{

	CString strData[8];

	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT2, strData[0]);
	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT3, strData[1]);
	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT7, strData[2]);
	SetDlgItemText(IDC_DND_TEXT_DLG_EDIT8, strData[3]);
	


	int nPos = m_ctrCombo[0].GetCurSel();
	if (nPos != -1)
	{
		m_ctrCombo[0].GetLBText(nPos,strData[4]);
	}

	nPos = m_ctrCombo[1].GetCurSel();
	if (nPos != -1)
	{
		m_ctrCombo[1].GetLBText(nPos, strData[5]);
	}

	nPos = m_ctrCombo[2].GetCurSel();
	if (nPos != -1)
	{
		m_ctrCombo[2].GetLBText(nPos, strData[6]);
	}

	nPos = m_ctrCombo[3].GetCurSel();
	if (nPos != -1)
	{
		m_ctrCombo[3].GetLBText(nPos, strData[7]);
	}


	m_pDND_Text->GetTextSB()->m_strText = strData[0];
	m_pDND_Text->GetTextSB()->m_strFont_family = strData[4];
	m_pDND_Text->GetTextSB()->m_nFont_size = _wtoi(strData[1]);
	m_pDND_Text->GetTextSB()->m_strFont_style = strData[5];
	m_pDND_Text->GetTextSB()->m_strFont_anchor = strData[6];
	m_pDND_Text->GetTextSB()->m_strFont_valign = strData[7];
	m_pDND_Text->GetTextSB()->m_dWidth = _wtof(strData[2]);
	m_pDND_Text->GetTextSB()->m_dHeight = _wtof(strData[3]);
	
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->Redraw_View();
}

