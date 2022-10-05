// CView_DNR_rst_SSDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CView_DNR_rst_SSDlg.h"
#include "afxdialogex.h"
#include "../DataManager/CDataManager.h"


// CView_DNR_rst_SSDlg 대화 상자

IMPLEMENT_DYNAMIC(CView_DNR_rst_SSDlg, CDialogEx)

CView_DNR_rst_SSDlg::CView_DNR_rst_SSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DNR_RST_SS_DLG, pParent)
{

}

CView_DNR_rst_SSDlg::~CView_DNR_rst_SSDlg()
{
}

void CView_DNR_rst_SSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNR_RST_SS_DLG_LIST1, m_ctrList);
}


BEGIN_MESSAGE_MAP(CView_DNR_rst_SSDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DNR_RST_SS_DLG_BTN1, &CView_DNR_rst_SSDlg::OnBnClickedDnrRstSsDlgBtn1)
END_MESSAGE_MAP()


// CView_DNR_rst_SSDlg 메시지 처리기


BOOL CView_DNR_rst_SSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect r;
	m_ctrList.GetWindowRect(r);
	m_ctrList.InsertColumn(0, _T(""), LVCFMT_CENTER, r.Width() / 10 * 1 );
	m_ctrList.InsertColumn(1, _T("SS Name"), LVCFMT_CENTER, r.Width() / 10 * 9 - 20);
	m_ctrList.InsertColumn(2, _T("Idx"), LVCFMT_CENTER,0);

	m_ctrList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |  LVS_EX_CHECKBOXES);

	InitData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CView_DNR_rst_SSDlg::InitData()
{
	CStringArray Array_SS;
	CIntArray	 Array_SS_idx;
	CString strName, strIdx;
	int nIdx, nCheck;
	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->GetSSName_array(&Array_SS, &Array_SS_idx);

	for (int i = 0; i < Array_SS.GetCount(); i++)
	{
		strName = Array_SS.GetAt(i);
		nIdx = Array_SS_idx.GetAt(i);

		nCheck = GETVALUE(int, _T("ss_dyn_uin"), _T("SS_DNRFLAG"), nIdx);

		strIdx.Format(_T("%d"), nIdx);

		m_ctrList.InsertItem(i, _T(""));
		m_ctrList.SetItemText(i, 1, strName);
		m_ctrList.SetItemText(i, 2, strIdx);

		if (nCheck == 1)
		{
			m_ctrList.SetCheck(i);
		}
	}
}


void CView_DNR_rst_SSDlg::OnBnClickedDnrRstSsDlgBtn1()
{
	CString strName;
	CString strIdx;
	int nIdx;

	for (int i = 0; i < m_ctrList.GetItemCount(); i++)
	{
		strIdx = m_ctrList.GetItemText(i, 2);
		nIdx = _wtoi(strIdx);


		if (m_ctrList.GetCheck(i))
		{
			strName = m_ctrList.GetItemText(i, 1);
		
			m_Array_SS.Add(strName);
			m_Array_SS_idx.Add(nIdx);
			PUTDOUBLE2VALUE(_T("SS_DYN_UIN"), _T("SS_DNRFLAG"), nIdx, (double)1);
		}
		else
		{
			PUTDOUBLE2VALUE(_T("SS_DYN_UIN"), _T("SS_DNRFLAG"), nIdx, (double)0);
		}
	}

	CDialogEx::OnOK();
}
