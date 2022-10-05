// FindObjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "FindObjDlg.h"
#include "afxdialogex.h"
#include "../Ctrl_Object/MessageDlg.h"


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
	DDX_Control(pDX, IDC_COMBO_INDEX, m_ctrIndexCom);
	DDX_Radio(pDX, IDC_RADIO_FINDOPT1, m_nFindOpt);
	DDX_Control(pDX, IDC_LIST_RESULT, m_ctrList);
}


BEGIN_MESSAGE_MAP(CFindObjDlg, CPNOCtrl_SkinFrame_POP_Dialog)
	ON_BN_CLICKED(IDC_RADIO_FINDOPT1, &CFindObjDlg::OnBnClickedRadioFindopt1)
	ON_BN_CLICKED(IDC_RADIO_FINDOPT2, &CFindObjDlg::OnBnClickedRadioFindopt2)
	ON_BN_CLICKED(IDCANCEL, &CFindObjDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CFindObjDlg::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RESULT, &CFindObjDlg::OnNMDblclkListResult)
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
	wchar_t*														list[4] = { _T(""), _T("ND"), _T("GND"), _T("명칭") };
	int																width[4] = { 0, 50, 50, 135 };

	for (int i = 0; i < 4; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_CENTER;
		lvcolumn.pszText = list[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = width[i];

		m_ctrList.InsertColumn(i, &lvcolumn);
	}

	EnableControl();
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
	if (m_nFindOpt == 0)											FindToName(szFindText);
	else															FindToIndex(szFindText);
}

void CFindObjDlg::FindToName(CString szFindText)
{
	LV_ITEM															lvitem;
	int																nCount, nDlIdx, nIdx(0);
	CString															szCount, szName, szData;
	m_ctrList.DeleteAllItems();

	nCount = theAppDataMng->GetTableRealCount(_T("nd_sta"));
	for (int i = 1; i <= nCount; i++)
	{
		nDlIdx = GETVALUE(int, _T("nd_dyn_ncpo"), _T("nd_ii_dl"), i);
		if (nDlIdx == 0)											continue;

		szName = GETSTRING(_T("nd_sta"), _T("nd_nm"), i);
		if (szName.Find(szFindText) < 0)							continue;

		lvitem.mask = LVIF_TEXT;
		lvitem.iItem = nIdx;
		lvitem.iSubItem = 0;
		lvitem.pszText = (LPWSTR)(LPCTSTR)_T("");
		m_ctrList.InsertItem(&lvitem);

		szData.Format(_T("%d"), i);
		m_ctrList.SetItemText(nIdx, 1, szData);

		szData.Format(_T("%d"), GETVALUE(int, _T("nd_sta"), _T("nd_ii_gnd"), i));
		m_ctrList.SetItemText(nIdx, 2, szData);

		m_ctrList.SetItemText(nIdx, 3, szName);

		nIdx++;
	}

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

void CFindObjDlg::FindToIndex(CString szFindText)
{
	int																nIdxOpt, nFindIdx;
	nIdxOpt = m_ctrIndexCom.GetCurSel();

	if (nIdxOpt < 0)
	{
		CMessageDlg dlg(_T("알림"), MB_OK);
		dlg.SetMessage(_T("인덱스 옵션을 선택하세요."));
		dlg.DoModal();

		return;
	}

	nFindIdx = _wtoi(szFindText);
	if (nFindIdx <= 0)
	{
		CMessageDlg dlg(_T("알림"), MB_OK);
		dlg.SetMessage(_T("검색할 인덱스가 올바르지 않습니다."));
		dlg.DoModal();

		return;
	}

	if (m_pParent)													
		m_pParent->SendMessage(WM_FINDOBJ_MSG, (WPARAM)nIdxOpt + 1, (LPARAM)nFindIdx);
}

void CFindObjDlg::OnNMDblclkListResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW*													pNMListView = (NM_LISTVIEW*)pNMHDR;

	int																nFindIdx;
	nFindIdx = _wtoi(m_ctrList.GetItemText(pNMListView->iItem, 1));

	if (m_pParent)													m_pParent->SendMessage(WM_FINDOBJ_MSG, (WPARAM)0, (LPARAM)nFindIdx);

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
	EnableControl();
}

void CFindObjDlg::OnBnClickedRadioFindopt2()
{
	UpdateData();
	EnableControl();

	CRect															rect, rectWnd;
	GetWindowRect(rectWnd);
	CWnd*															pWnd = GetDlgItem(IDOK);
	pWnd->GetWindowRect(rect);
	if (rectWnd.bottom > rect.bottom)
	{
		rectWnd.bottom = rect.bottom + 15;
		MoveWindow(rectWnd);
	}
}

void CFindObjDlg::EnableControl()
{
	CWnd*															pWnd;
	pWnd = GetDlgItem(IDC_COMBO_INDEX);
	if (m_nFindOpt == 0)											pWnd->EnableWindow(FALSE);
	else															pWnd->EnableWindow(TRUE);
}

void CFindObjDlg::OnBnClickedCancel()
{
	if (m_pParent)													m_pParent->SendMessage(WM_FINDOBJ_MSG, (WPARAM)-1, (LPARAM)this);
}