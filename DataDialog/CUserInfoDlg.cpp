// CUserInfoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CUserInfoDlg.h"
#include "afxdialogex.h"
#include "../DataManager/CDataManager.h"
#include "dbexcept.h"


// CUserInfoDlg 대화 상자

IMPLEMENT_DYNAMIC(CUserInfoDlg, CDialogEx)

CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERINFO_DLG, pParent)
{

}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERINFO_DLG_LIST1, m_ctrList);
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_USERINFO_DLG_BTN1, &CUserInfoDlg::OnBnClickedUserinfoDlgBtn1)
	ON_BN_CLICKED(IDC_USERINFO_DLG_BTN2, &CUserInfoDlg::OnBnClickedUserinfoDlgBtn2)
	ON_BN_CLICKED(IDC_USERINFO_DLG_BTN3, &CUserInfoDlg::OnBnClickedUserinfoDlgBtn3)
END_MESSAGE_MAP()


// CUserInfoDlg 메시지 처리기


BOOL CUserInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	CRect r;
	m_ctrList.GetWindowRect(r);
	m_ctrList.InsertColumn(0, _T("Idx"), LVCFMT_CENTER, r.Width() / 5 * 1 - 20 );
	m_ctrList.InsertColumn(1, _T("사번"), LVCFMT_CENTER, r.Width() / 5 * 2);
	m_ctrList.InsertColumn(2, _T("성명"), LVCFMT_CENTER, r.Width() /5 * 2 );

	m_ctrList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_SHOWSELALWAYS);

	SetData_List();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CUserInfoDlg::SetData_List()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL;
	int nCount = 1;

	CString strData[3];

	TRY
	{
		ulFields = 2;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(pDataMng->m_Session_localData, _T("Select ID , User_Name from UserInfo")) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strData[0].Format(_T("%d"), nCount);
			strData[1] = pBind[0].szValue;
			strData[2] = pBind[1].szValue;

			m_ctrList.InsertItem(m_ctrList.GetItemCount(), strData[0]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 1, strData[1]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 2, strData[2]);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 1, LIST_TYPE_EDIT, NULL);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 2, LIST_TYPE_EDIT, NULL);


			nCount++;
		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		////////// Subs

	}
		CATCH(COLEDBException, e)
	{
		if (pBind != NULL)
			delete pBind;

		e->ReportError();
	}
	END_CATCH
}


void CUserInfoDlg::OnBnClickedUserinfoDlgBtn1()
{
	CString strData;
	strData.Format(_T("%d"), m_ctrList.GetItemCount()+1);
	m_ctrList.InsertItem(m_ctrList.GetItemCount(), strData);
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 1, _T("#사번#"));
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 2, _T("#성명#"));
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 1, LIST_TYPE_EDIT, NULL);
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 2, LIST_TYPE_EDIT, NULL);
}


void CUserInfoDlg::OnBnClickedUserinfoDlgBtn2()
{
	int nPos = m_ctrList.GetSelectionMark();

	if (nPos == -1)
		return;

	m_ctrList.DeleteItem(nPos);
	CString strIdx;
	for (int i = 0; i < m_ctrList.GetItemCount(); i++)
	{
		strIdx.Format(_T("%d"), i + 1);
		m_ctrList.SetItemText(i, 0, strIdx);
	}
}


void CUserInfoDlg::OnBnClickedUserinfoDlgBtn3()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CString strData[2],strSQL;

	strSQL.Format(_T("delete * from userinfo"));

	pDataMng->SQLDBExcute(&pDataMng->m_Session_localData, strSQL);
	for (int i = 0; i < m_ctrList.GetItemCount(); i++)
	{
		strData[0] = m_ctrList.GetItemText(i, 1);
		strData[1] = m_ctrList.GetItemText(i, 2);

		strSQL.Format(_T("insert into userinfo Values(%s,'%s','')") , strData[0],strData[1]);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_localData, strSQL);
	}

}
