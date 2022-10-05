// CDataShareDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CDataShareDlg.h"
#include "afxdialogex.h"
#include "../DataManager/CDataManager.h"

// CDataShareDlg 대화 상자

//#include "../Include/DBContainer/DB_EXTRACT.h"
#include "../Include/DBContainer/DB_QUERY.h"

IMPLEMENT_DYNAMIC(CDataShareDlg, CDialogEx)

CDataShareDlg::CDataShareDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DATASHARE_DLG, pParent)
{

}

CDataShareDlg::~CDataShareDlg()
{
}

void CDataShareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATASHARE_DLG_COMBO1, m_ctrCombo);
	DDX_Control(pDX, IDC_DATASHARE_DLG_LIST1, m_ctrList);
}


BEGIN_MESSAGE_MAP(CDataShareDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DATASHARE_DLG_BTN1, &CDataShareDlg::OnBnClickedDatashareDlgBtn1)
	ON_BN_CLICKED(IDC_DATASHARE_DLG_BTN2, &CDataShareDlg::OnBnClickedDatashareDlgBtn2)
	ON_BN_CLICKED(IDC_DATASHARE_DLG_BTN3, &CDataShareDlg::OnBnClickedDatashareDlgBtn3)
	ON_CBN_SELCHANGE(IDC_DATASHARE_DLG_COMBO1, &CDataShareDlg::OnCbnSelchangeDatashareDlgCombo1)
END_MESSAGE_MAP()


// CDataShareDlg 메시지 처리기


BOOL CDataShareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ctrCombo.AddString(_T("전체"));
	m_ctrCombo.AddString(_T("KACIM"));
	m_ctrCombo.AddString(_T("SVG"));
	m_ctrCombo.SetCurSel(0);

	CRect r;
	m_ctrList.GetWindowRect(r);
	m_ctrList.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 0);
	m_ctrList.InsertColumn(1, _T("Date"), LVCFMT_CENTER, r.Width() / 20 * 4);
	m_ctrList.InsertColumn(2, _T("User"), LVCFMT_CENTER, r.Width() / 20 * 2);
	m_ctrList.InsertColumn(3, _T("File"), LVCFMT_CENTER, r.Width() / 20 * 9);
	m_ctrList.InsertColumn(4, _T("Type"), LVCFMT_CENTER, r.Width() / 20 * 2);
	m_ctrList.InsertColumn(5, _T("Size"), LVCFMT_CENTER, r.Width() / 20 * 3 -20);

	m_ctrList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_SHOWSELALWAYS);
	
	UpdateList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDataShareDlg::UpdateList()
{
//	CDBContainer_Insatnce* pDB = CDataManager::Instance()->GetDBContainer();
	int nSearch = m_ctrCombo.GetCurSel();
	
	m_ctrList.DeleteAllItems();
	
	CString strSQL;

	if(nSearch == 1)
		strSQL.Format(_T("Select id,update_time,user_id,file_name,file_type,file_size from adms_simulator_share where file_type = 0;"));
	else if (nSearch == 2)
		strSQL.Format(_T("Select id,update_time,user_id,file_name,file_type,file_size from adms_simulator_share where file_type = 1;"));
	else
		strSQL.Format(_T("Select id,update_time,user_id,file_name,file_type,file_size from adms_simulator_share ;"));


	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer());
	CDB_QUERY							dbquery(strSQL.GetBuffer());
	int nType;
	CString strData[6];
	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			strData[0].Format(_T("%s"), dbquery.GetData_STR(0));
			strData[1].Format(_T("%s"), dbquery.GetData_STR(1));
			strData[2].Format(_T("%s"), dbquery.GetData_STR(2));
			strData[3].Format(_T("%s"), dbquery.GetData_STR(3));

			nType = dbquery.GetData_NUM(4);

			if (nType == 0)
				strData[4].Format(_T("%s"), _T("KACIM"));
			else
				strData[4].Format(_T("%s"), _T("SVG"));

			strData[5].Format(_T("%s"), dbquery.GetData_STR(5));

			m_ctrList.InsertItem(m_ctrList.GetItemCount(), strData[0]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 1, strData[1]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 2, strData[2]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 3, strData[3]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 4, strData[4]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 5, strData[5]);
		}
	}
	dbquery.Close();

}

void CDataShareDlg::OnBnClickedDatashareDlgBtn1()
{
	// Upload
	CString strSQL;
	strSQL.Format(_T("Select MAX(id) from adms_simulator_share ;"));

	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer());
	CDB_QUERY							dbquery(strSQL.GetBuffer());
	int nMxID = 0;
	CString strData;
	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			nMxID = dbquery.GetData_NUM(0);
		}
	}
	dbquery.Close();

	nMxID++;
	//////////////////////////////////
	CTime t = CTime::GetCurrentTime();

	CDataManager* pDataMng = CDataManager::Instance();
	CFileDialog FileDlg(TRUE, _T("zip"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("KASIM Data File(*.zip)|*.zip| All Files(*.*)|*.*|"));

	CString strPath = pDataMng->MyPath();
	FileDlg.m_pOFN->lpstrInitialDir = (LPCWSTR)strPath;

	if (FileDlg.DoModal() != IDOK)
		return;

	CString strDUAL, strST;
	CString strTitleName = FileDlg.GetFileTitle();
	CString strFilePath = FileDlg.GetPathName();
	CString strFileName = FileDlg.GetFileName();
	CString strFileTmp = strFileName;

	int nType = 0;
	if (strFileTmp.Find(_T(".svg")) > -1)
		nType = 1;

	CString						szQuery;
	szQuery.Format(_T("insert into adms_simulator_share( id, update_time, user_id, file_name,file_type) values ( %d, '%s', %d ,'%s', %d );"),
		nMxID, t.Format(_T("%Y/%m/%d %H:%M:%S")), 12345678 , strFileName, nType);

	

	
	//CDB_EXTRACT						dbquery_1(1, szQuery.GetBuffer());
	CDB_QUERY							dbquery_1(szQuery.GetBuffer());
	if (!dbquery_1.IsSuccess())
	{
		LOGOUT("* Err : DB Query Fail.( %s )", "insert into adms_simulator_share");
		LOGOUT("DB Write End");
		return ;
	}
	dbquery_1.Close();

	CPString						szQueryWhereData;
	szQueryWhereData.Format("id = %d", nMxID );
	int								nRetValue(0);
	if ((nRetValue = theDBContainer->MariaDB_UploadFile(0, CW2A(strFilePath).m_psz
														, CW2A(_T("adms_simulator_share")).m_psz
														, CW2A(_T("file_binary")).m_psz
														, CW2A(_T("file_size")).m_psz
														, szQueryWhereData.GetValue())) != 0)
	{
		LOGOUT("* Err : Upload BuffData Fail.( %d )", nRetValue);
		LOGOUT("DB Write End");
		return ;
	}

	LOGOUT("DB Upload End");

	UpdateList();
}


void CDataShareDlg::OnBnClickedDatashareDlgBtn2()
{
	// Download
	int nRow = m_ctrList.GetSelectionMark();
	if (nRow == -1)
		return;

	CString strFileName = m_ctrList.GetItemText(nRow, 3);

	CDataManager* pDataMng = CDataManager::Instance();
	CFileDialog FileDlg(FALSE, _T("zip"), strFileName, OFN_CREATEPROMPT| OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("KASIM Data File(*.zip)|*.zip| All Files(*.*)|*.*|"));

	CString strPath = pDataMng->MyPath();
	FileDlg.m_pOFN->lpstrInitialDir = (LPCWSTR)strPath;

	if (FileDlg.DoModal() != IDOK)
		return;

	int nID = _wtoi(m_ctrList.GetItemText(nRow, 0));
	CString strTitleName = FileDlg.GetFileTitle();
	CString strFilePath = FileDlg.GetPathName();
	strFileName = FileDlg.GetFileName();
	strFilePath.Trim(strFileName);
	
	nID = 5;
	CPString						szDNWhereData;
	szDNWhereData.Format("diagram_id = %d", nID);

	/*if (theDBContainer->MariaDB_DownloadFile(0,
		CW2A(strFilePath).m_psz
		, CW2A(strFileName).m_psz
		, CW2A(_T("adms_simulator_share")).m_psz
		, CW2A(_T("file_binary")).m_psz
		, szDNWhereData.GetValue()) != 0)
	{
		LOGOUT("* Err : Download DB Fail");
		LOGOUT("DB Download End");
		return;
	}*/

	if (theDBContainer->MariaDB_DownloadFile(1, 
		CW2A(strFilePath).m_psz
		, CW2A(strFileName).m_psz
		, CW2A(_T("diagram")).m_psz
		, CW2A(_T("diagram_file")).m_psz
		, szDNWhereData.GetValue()) != 0)
	{
		LOGOUT("* Err : Download DB Fail");
		LOGOUT("DB Download End");
		return ;
	}

	LOGOUT("DB Download End");

	CString strZipPath;
	strZipPath.Format(_T("%s\\%s"), strFilePath, strFileName);
	theUtil->doUnzip(strZipPath.GetBuffer(), strFilePath.GetBuffer());

}


void CDataShareDlg::OnBnClickedDatashareDlgBtn3()
{
	UpdateList();
}


void CDataShareDlg::OnCbnSelchangeDatashareDlgCombo1()
{
	UpdateList();
}
