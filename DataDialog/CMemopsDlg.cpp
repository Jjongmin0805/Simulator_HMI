// CMemopsDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CMemopsDlg.h"
#include "afxdialogex.h"
#include "../DataManager/CDataManager.h"
//#include "../Include/DBContainer/DB_EXTRACT.h"
#include "../Include/DBContainer/DB_QUERY.h"

// CMemopsDlg 대화 상자

IMPLEMENT_DYNAMIC(CMemopsDlg, CDialogEx)

CMemopsDlg::CMemopsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMS_MEMOPS_DLG, pParent)
{

}

CMemopsDlg::~CMemopsDlg()
{
}

void CMemopsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADMS_MEMOPS_DLG_COMBO1, m_ctrCombo);
}


BEGIN_MESSAGE_MAP(CMemopsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADMS_MEMOPS_DLG_BTN1, &CMemopsDlg::OnBnClickedAdmsMemopsDlgBtn1)
END_MESSAGE_MAP()


// CMemopsDlg 메시지 처리기


BOOL CMemopsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ctrCombo.ResetContent();

	CString strSQL;
	strSQL.Format(_T("Select head_office_id, name from head_office order by head_office_id"));

	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer(), 2);
	CDB_QUERY							dbquery(strSQL.GetBuffer(), 2);

	int nCenter;
	CString strName;

	int nCount = 0;
	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			nCenter = dbquery.GetData_LONG(0);
			strName.Format(_T("%s"), dbquery.GetData_STR(1));

			m_ctrCombo.AddString(strName);
			m_ctrCombo.SetItemData(nCount, (DWORD_PTR)nCenter);

			nCount++;
		}
	}
	dbquery.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMemopsDlg::OnBnClickedAdmsMemopsDlgBtn1()
{
	
	int nSel = m_ctrCombo.GetCurSel();
	if (nSel == -1)
		return;

	int nHead = (int)m_ctrCombo.GetItemData(nSel);

	//// 본부코드/0/DB_ID/DB_PW/DSN
	////  memops
}
