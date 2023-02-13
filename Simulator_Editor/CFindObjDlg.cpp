// FindObjDlg.cpp: 구현 파일
//
#include "pch.h"
#include "Simulator_Editor.h"
#include "CFindObjDlg.h"
#include "afxdialogex.h"
#include "../Ctrl_Object_Editor/MessageDlg.h"
#include "../DND_Manager/CDND_Manager.h"
// CFindObjDlg 대화 상자

IMPLEMENT_DYNAMIC(CFindObjDlg, CPNOCtrl_SkinFrame_POP_Dialog)

CFindObjDlg::CFindObjDlg(CWnd* pParent /*=nullptr*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_FINDOBJ_DLG, pParent)
	, m_nFindOpt(0)
{
	m_pParent = pParent;
}

CFindObjDlg::~CFindObjDlg()
{
}

void CFindObjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_FINDOPT1, m_nFindOpt);
	DDX_Control(pDX, IDC_LIST_RESULT, m_ctrList);
}


BEGIN_MESSAGE_MAP(CFindObjDlg, CPNOCtrl_SkinFrame_POP_Dialog)
	ON_BN_CLICKED(IDC_RADIO_FINDOPT1, &CFindObjDlg::OnBnClickedRadioFindopt1)
	ON_BN_CLICKED(IDC_RADIO_FINDOPT2, &CFindObjDlg::OnBnClickedRadioFindopt2)
	ON_BN_CLICKED(IDCANCEL, &CFindObjDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CFindObjDlg::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RESULT, &CFindObjDlg::OnNMDblclkListResult)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CFindObjDlg::OnEnChangeEditName)
	ON_BN_CLICKED(IDC_RADIO_FINDOPT3, &CFindObjDlg::OnBnClickedRadioFindopt3)
END_MESSAGE_MAP()


// CFindObjDlg 메시지 처리기
BOOL CFindObjDlg::Create()
{
	return CPNOCtrl_SkinFrame_POP_Dialog::Create(IDD_FINDOBJ_DLG, m_pParent);
}

BOOL CFindObjDlg::OnInitDialog()
{
	CPNOCtrl_SkinFrame_POP_Dialog::OnInitDialog();

	SetWindowTheme(GetDlgItem(IDC_STC_FIND_OPTION)->m_hWnd, _T(""), _T(""));

	CWnd*															pWnd;
	pWnd = GetDlgItem(IDC_STC_FIND_OPTION);
	pWnd->SetFont(&m_FontBold);
	pWnd = GetDlgItem(IDC_STATIC_DESC);
	pWnd->SetFont(&m_FontBold);

	CRect															rectWnd, rect;
	m_pParent->GetWindowRect(&rectWnd);
	GetClientRect(&rect);
	rectWnd.right = rectWnd.left + rect.Width();
	rectWnd.bottom = rectWnd.top + rect.Height();
	MoveWindow(rectWnd);

	GetDlgItem(IDC_STATIC_DESC)->GetWindowRect(&rect);
	rectWnd.bottom = rect.top;
	MoveWindow(rectWnd);

	m_ctrList.DeleteAllItems();
	DWORD style = m_ctrList.GetExtendedStyle();
	style |= (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList.SetExtendedStyle(style);
	m_ctrList.DeleteAllItems();
	LV_COLUMN														lvcolumn;
	wchar_t*														list[2] = { _T(""), _T("설비") };
	int																width[2] = { 0, 250 };

	for (int i = 0; i < 2; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_CENTER;
		lvcolumn.pszText = list[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = width[i];

		m_ctrList.InsertColumn(i, &lvcolumn);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CFindObjDlg::OnBnClickedOk()
{
	UpdateData();

	CString															szFindText;
	GetDlgItemText(IDC_EDIT_NAME, szFindText);

	if (szFindText.IsEmpty())
	{
		CMessageDlg dlg(_T("알림"), MB_OK);
		dlg.SetMessage(_T("검색할 문자열을 입력하세요."));
		dlg.DoModal();

		return;
	}

	szFindText.MakeUpper();
	if      (m_nFindOpt == 0)	{ FindToName(szFindText); }
	else if	(m_nFindOpt == 1)	{ FindToCEQ(szFindText); }
	else						{ FindToCustNo(szFindText); }
}

void CFindObjDlg::FindToName(CString szFindText)
{
	int																nIdx(0);
	CString															szCount, szName, szData;
	m_ctrList.DeleteAllItems();

	CDND_Manager* pDNDMng = CDND_Manager::Instance();
	pDNDMng->GetDNDObject2NM(szFindText, &m_ctrList);
	
	nIdx = m_ctrList.GetItemCount();
	szCount.Format(L" %s 건이 검색되었습니다.", ConvertNumber(nIdx));
	SetDlgItemText(IDC_STATIC_DESC, szCount);

	CRect															rect, rectWnd;
	GetWindowRect(rectWnd);
	CWnd*															pWnd = GetDlgItem(IDCANCEL);
	pWnd->GetWindowRect(rect);
	if (rectWnd.bottom < rect.bottom)
	{
		rectWnd.bottom = rect.bottom + 15;
		MoveWindow(rectWnd);
	}
}

void CFindObjDlg::FindToCEQ(CString szFindText)
{
	int																nIdx(0);
	CString															szCount, szName, szData;
	m_ctrList.DeleteAllItems();

	CDND_Manager* pDNDMng = CDND_Manager::Instance();
	pDNDMng->GetDNDObject2CEQ(szFindText, &m_ctrList);

	nIdx = m_ctrList.GetItemCount();
	szCount.Format(L" %s 건이 검색되었습니다.", ConvertNumber(nIdx));
	SetDlgItemText(IDC_STATIC_DESC, szCount);

	CRect															rect, rectWnd;
	GetWindowRect(rectWnd);
	CWnd*															pWnd = GetDlgItem(IDCANCEL);
	pWnd->GetWindowRect(rect);
	if (rectWnd.bottom < rect.bottom)
	{
		rectWnd.bottom = rect.bottom + 15;
		MoveWindow(rectWnd);
	}
}

void CFindObjDlg::FindToCustNo(CString szFindText)
{
	int																nIdx(0);
	CString															szCount, szName, szData;
	m_ctrList.DeleteAllItems();

	CDND_Manager* pDNDMng = CDND_Manager::Instance();
	pDNDMng->GetDNDObject2CUSTOMER_NO(szFindText, &m_ctrList);

	nIdx = m_ctrList.GetItemCount();
	szCount.Format(L" %s 건이 검색되었습니다.", ConvertNumber(nIdx));
	SetDlgItemText(IDC_STATIC_DESC, szCount);

	CRect															rect, rectWnd;
	GetWindowRect(rectWnd);
	CWnd*															pWnd = GetDlgItem(IDCANCEL);
	pWnd->GetWindowRect(rect);
	if (rectWnd.bottom < rect.bottom)
	{
		rectWnd.bottom = rect.bottom + 15;
		MoveWindow(rectWnd);
	}
}


void CFindObjDlg::OnNMDblclkListResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW*													pNMListView = (NM_LISTVIEW*)pNMHDR;

	CString																stFindIdx;
	stFindIdx = m_ctrList.GetItemText(pNMListView->iItem, 0);

	if (m_pParent)													m_pParent->SendMessage(WM_FINDOBJ_MSG, (WPARAM)0, (LPARAM)&stFindIdx);

	*pResult = 0;
}

CString CFindObjDlg::ConvertNumber(int nNum)
{
	CString															szNumber(_T("")), szTemp;

	szTemp.Format(_T("%d"), nNum);
	while (szTemp.GetLength() > 3)
	{
		szNumber.Insert(0, szTemp.Right(3));
		szNumber.Insert(0, _T(","));

		szTemp.Delete(szTemp.GetLength() - 3, 3);
	}

	szNumber.Insert(0, szTemp);

	return szNumber;
}

void CFindObjDlg::OnBnClickedRadioFindopt1()
{
	UpdateData();
}

void CFindObjDlg::OnBnClickedRadioFindopt2()
{
	UpdateData();
}

void CFindObjDlg::OnBnClickedCancel()
{
	if (m_pParent)													m_pParent->SendMessage(WM_FINDOBJ_MSG, (WPARAM)-1, (LPARAM)this);
}

void CFindObjDlg::OnEnChangeEditName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CPNOCtrl_SkinFrame_POP_Dialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CFindObjDlg::OnBnClickedRadioFindopt3()
{
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
