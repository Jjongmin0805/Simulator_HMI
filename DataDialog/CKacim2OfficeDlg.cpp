// CKacim2OfficeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CKacim2OfficeDlg.h"
#include "afxdialogex.h"
#include "../DataManager/CDataManager.h"

//#include "../Include/DBContainer/DB_EXTRACT.h"
#include "../Include/DBContainer/DB_QUERY.h"
// CKacim2OfficeDlg 대화 상자

IMPLEMENT_DYNAMIC(CKacim2OfficeDlg, CDialogEx)

CKacim2OfficeDlg::CKacim2OfficeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KACIM_OFFCIE_DLG, pParent)
{

}

CKacim2OfficeDlg::~CKacim2OfficeDlg()
{
}

void CKacim2OfficeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KACIM_OFFCIE_DLG_COMBO1, m_ctrCombo[0]);
	DDX_Control(pDX, IDC_KACIM_OFFCIE_DLG_COMBO2, m_ctrCombo[1]);
}


BEGIN_MESSAGE_MAP(CKacim2OfficeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_KACIM_OFFCIE_DLG_BTN1, &CKacim2OfficeDlg::OnBnClickedKacimOffcieDlgBtn1)
	ON_BN_CLICKED(IDC_KACIM_OFFCIE_DLG_BTN2, &CKacim2OfficeDlg::OnBnClickedKacimOffcieDlgBtn2)
	ON_CBN_SELCHANGE(IDC_KACIM_OFFCIE_DLG_COMBO1, &CKacim2OfficeDlg::OnCbnSelchangeKacimOffcieDlgCombo1)
	ON_BN_CLICKED(IDC_KACIM_OFFCIE_DLG_RADIO1, &CKacim2OfficeDlg::OnBnClickedKacimOffcieDlgRadio1)
	ON_BN_CLICKED(IDC_KACIM_OFFCIE_DLG_RADIO2, &CKacim2OfficeDlg::OnBnClickedKacimOffcieDlgRadio2)
END_MESSAGE_MAP()


// CKacim2OfficeDlg 메시지 처리기


BOOL CKacim2OfficeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Set_Center();

	CButton* pBtn = (CButton*)GetDlgItem(IDC_KACIM_OFFCIE_DLG_RADIO2);
	pBtn->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CKacim2OfficeDlg::OnBnClickedKacimOffcieDlgBtn1()
{

	CADMStoKCIMDlg					ConvertDLG;

	CString strConfig, strCode, strPath;

	strConfig.Format(_T("DSN=%s; UID=%s; PWD=%s;")
		, theDBContainer->GetConfigDBName(1), theDBContainer->GetConfigUserID(1), theDBContainer->GetConfigPassWord(1));

	strCode.Format(_T("DSN=%s; UID=%s; PWD=%s;")
		, theDBContainer->GetConfigDBName(2), theDBContainer->GetConfigUserID(2), theDBContainer->GetConfigPassWord(2));


	CButton* pBtn = (CButton*)GetDlgItem(IDC_KACIM_OFFCIE_DLG_RADIO2);
	if (pBtn->GetCheck() == TRUE)
	{
		int nSel = m_ctrCombo[1].GetCurSel();

		if (nSel == -1)
			return;

		int nOffice = (int)m_ctrCombo[1].GetItemData(nSel);

		
		
		ConvertDLG.ST_CODE(nOffice);
			
	}
	else
	{
		ConvertDLG.ST_CODE(0);
	}

	ConvertDLG.ST_MODE(1);
	ConvertDLG.ADMStoKCIM_Offic_Config(strConfig);
	//ConvertDLG.ADMStoKCIM_Offic_Code(strCode);
	ConvertDLG.ADMStoKCIM_Code_Config(strCode);
	ConvertDLG.ADMStoKCIM_CSV_Route(_T("\\Data\\CSVFile\\0\\"));
	ConvertDLG.m_szADMS_Code.Format(_T("adms_code"));

	ConvertDLG.DoModal();

	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->MMDB_Restart();

	CDialogEx::OnOK();
}


void CKacim2OfficeDlg::OnBnClickedKacimOffcieDlgBtn2()
{
	CDialogEx::OnOK();
}


void CKacim2OfficeDlg::OnCbnSelchangeKacimOffcieDlgCombo1()
{
	Set_Office();
}


void CKacim2OfficeDlg::Set_Center()
{
	m_ctrCombo[0].ResetContent();

	CString strSQL;
	strSQL.Format(_T("Select center_office_id, name from center_office order by center_office_id"));

	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer(), 2);
	CDB_QUERY							dbquery(strSQL.GetBuffer(),2);

	/*if (dbquery.IsOpen() == FALSE)
	{
		dbquery.DBExcute(strSQL.GetBuffer());
	}*/

	int nCenter;
	CString strName;

	int nCount = 0;
	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			nCenter = dbquery.GetData_LONG(0);
			strName.Format(_T("%s"), dbquery.GetData_STR(1));

			m_ctrCombo[0].AddString(strName);
			m_ctrCombo[0].SetItemData(nCount, (DWORD_PTR)nCenter);

			nCount++;
		}
	}

	dbquery.Close();
}

void CKacim2OfficeDlg::Set_Office()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel == -1)
		return;

	int nCenter = (int)m_ctrCombo[0].GetItemData(nSel);

	m_ctrCombo[1].ResetContent();

	CString strSQL;
	strSQL.Format(_T("Select member_office_id, name from member_office where center_office_fk = %d;"), nCenter);


//	CDB_EXTRACT						dbquery(0, strSQL.GetBuffer(), 2);
	CDB_QUERY							dbquery(strSQL.GetBuffer(), 2);
	

	int nOffice;
	CString strName;

	int nCount = 0;
	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			nOffice = dbquery.GetData_LONG(0);
			strName.Format(_T("%s"), dbquery.GetData_STR(1));

			m_ctrCombo[1].AddString(strName);
			m_ctrCombo[1].SetItemData(nCount, (DWORD_PTR)nOffice);

			nCount++;
		}
	}
	dbquery.Close();

	//dbquery.
}

void CKacim2OfficeDlg::OnBnClickedKacimOffcieDlgRadio1()
{
	m_ctrCombo[0].EnableWindow(FALSE);
	m_ctrCombo[1].EnableWindow(FALSE);
}


void CKacim2OfficeDlg::OnBnClickedKacimOffcieDlgRadio2()
{
	m_ctrCombo[0].EnableWindow(TRUE);
	m_ctrCombo[1].EnableWindow(TRUE);
}
