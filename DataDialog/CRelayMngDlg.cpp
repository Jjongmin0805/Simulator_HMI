// CRelayMngDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CRelayMngDlg.h"
#include "afxdialogex.h"
#include "dbexcept.h"
#include "../DataManager/CDataManager.h"
#include "CRelaySetDlg.h"

// CRelayMngDlg 대화 상자

IMPLEMENT_DYNAMIC(CRelayMngDlg, CDialogEx)

CRelayMngDlg::CRelayMngDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RERAYMNG_DLG, pParent)
{
	m_nMax_ID = 0;
}

CRelayMngDlg::~CRelayMngDlg()
{
	CDataManager* pDataMng = CDataManager::Instance();
	pDataMng->SetRelayInfo2DB();
}

void CRelayMngDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RERAYMNG_DLG_LIST1, m_ctrList);
}


BEGIN_MESSAGE_MAP(CRelayMngDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RERAYMNG_DLG_BTN3, &CRelayMngDlg::OnBnClickedReraymngDlgBtn3)
	ON_BN_CLICKED(IDC_RERAYMNG_DLG_BTN1, &CRelayMngDlg::OnBnClickedReraymngDlgBtn1)
	ON_BN_CLICKED(IDC_RERAYMNG_DLG_BTN2, &CRelayMngDlg::OnBnClickedReraymngDlgBtn2)
	ON_NOTIFY(NM_DBLCLK, IDC_RERAYMNG_DLG_LIST1, &CRelayMngDlg::OnNMDblclkReraymngDlgList1)
	ON_NOTIFY(NM_RCLICK, IDC_RERAYMNG_DLG_LIST1, &CRelayMngDlg::OnNMRClickReraymngDlgList1)
	ON_COMMAND(ID_RELAYMNGDLG_SETINFO, &CRelayMngDlg::OnRelaymngdlgSetinfo)
	ON_COMMAND(ID_RELAYMNGDLG_DEL, &CRelayMngDlg::OnRelaymngdlgDel)
END_MESSAGE_MAP()


// CRelayMngDlg 메시지 처리기


BOOL CRelayMngDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ctrList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_SHOWSELALWAYS);
	//	m_ctrList.m_nEditLimit = 3;
	CString strTmp;
	LV_COLUMN lvcolumn;
	CString strlist[7] = { _T("id"),_T("type"),_T("curve"),_T("계전기명"),_T("계전기종류"),_T("제조사") , _T("커브")};
	

	CRect r;
	m_ctrList.GetWindowRect(r);

	m_ctrList.InsertColumn(0, strlist[0], LVCFMT_CENTER, 0);
	m_ctrList.InsertColumn(1, strlist[1], LVCFMT_CENTER, 0);
	m_ctrList.InsertColumn(2, strlist[2], LVCFMT_CENTER, 0);
	m_ctrList.InsertColumn(3, strlist[3], LVCFMT_LEFT, r.Width() / 4);
	m_ctrList.InsertColumn(4, strlist[4], LVCFMT_CENTER, r.Width() / 4);
	m_ctrList.InsertColumn(5, strlist[5], LVCFMT_CENTER, r.Width() / 4);
	m_ctrList.InsertColumn(6, strlist[6], LVCFMT_CENTER, r.Width() / 4 - 18);

	UpdateList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CRelayMngDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		if (pMsg->wParam == VK_RETURN)
			OnBnClickedReraymngDlgBtn3();
		

		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CRelayMngDlg::OnBnClickedReraymngDlgBtn1()
{
	CRelaySetDlg Dlg;

	Dlg.m_nMode = RELAY_EDIT_MODE_ADD;
	
	Dlg.DoModal();

	UpdateList();
}


void CRelayMngDlg::OnBnClickedReraymngDlgBtn2()
{
	CDialogEx::OnOK();
}

void CRelayMngDlg::OnBnClickedReraymngDlgBtn3()
{
	CString strFilter;

	GetDlgItemText(IDC_RERAYMNG_DLG_EDIT1, strFilter);

	UpdateList(strFilter);
}

void CRelayMngDlg::UpdateList(CString strFilter)
{
	CDataManager* pDataMng = CDataManager::Instance();

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL;
	int nID;

	CString strData[7];

	strFilter.Trim();

	if (strFilter.IsEmpty())
	{
		strSQL = _T("SELECT distinct a.* , b.ad_sep from adms_n_machine_code a, adms_n_relay_type b \
											 where a.machine_id =  b.machine_id");
	}
	else
	{
		strSQL.Format(_T("SELECT distinct a.* , b.ad_sep from adms_n_machine_code a, adms_n_relay_type b \
											 where a.machine_id =  b.machine_id and a.machine_name like '%%%s%%'"), strFilter);
	}
	
	m_ctrList.DeleteAllItems();
	TRY
	{
		ulFields = 5;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(pDataMng->m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strData[0] = pBind[0].szValue;
			nID = _wtoi(pBind[0].szValue);
			if (nID > m_nMax_ID)
			{
				m_nMax_ID = nID;
			}

			strData[1] = pBind[4].szValue;
			strData[2] = pBind[3].szValue;
			strData[3] = pBind[1].szValue;
			strData[4] = (_wtoi(strData[1]) == 0 ? _T("디지탈") : _T("아날로그") );
			strData[5] = pBind[2].szValue;
			strData[6] = _T("Curve");///////////////////////// kacim 에서 꺼내와야된다
			
			m_ctrList.InsertItem(m_ctrList.GetItemCount(), strData[0]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 1		,strData[1]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 2		,strData[2]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 3		,strData[3]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 4		,strData[4]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 5		,strData[5]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 6		,strData[6]);



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




void CRelayMngDlg::OnNMDblclkReraymngDlgList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int nSel = m_ctrList.GetSelectionMark();

	CString strData[5];


	strData[0] = m_ctrList.GetItemText(nSel, 0);
	strData[1] = m_ctrList.GetItemText(nSel, 1);
	strData[2] = m_ctrList.GetItemText(nSel, 2);
	strData[3] = m_ctrList.GetItemText(nSel, 3);
	strData[4] = m_ctrList.GetItemText(nSel, 5);
	
	CRelaySetDlg Dlg;

	Dlg.m_nMode = RELAY_EDIT_MODE_EDIT;
	Dlg.m_nID		= _wtoi(strData[0]);
	Dlg.m_nType		= _wtoi(strData[1]);
	Dlg.m_nCurve	= _wtoi(strData[2]);
	Dlg.m_strName	= (strData[3]);
	Dlg.m_strManuf  = (strData[4]);

	Dlg.DoModal();

	UpdateList();

	*pResult = 0;
}


void CRelayMngDlg::OnNMRClickReraymngDlgList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_MENU);
	CMenu* contextmenu;
	contextmenu = menu.GetSubMenu(0);

	
	//int nCol = m_ctrList.getse();

	
	CPoint pt = pNMListView->ptAction;
	m_ctrList.ClientToScreen(&pt);
	contextmenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);


	*pResult = 0;
}


void CRelayMngDlg::OnRelaymngdlgSetinfo()
{
	int nRow = m_ctrList.GetSelectionMark();
	CString strData[5];

	strData[0] = m_ctrList.GetItemText(nRow, 0);
	strData[1] = m_ctrList.GetItemText(nRow, 1);
	strData[2] = m_ctrList.GetItemText(nRow, 2);
	strData[3] = m_ctrList.GetItemText(nRow, 3);
	strData[4] = m_ctrList.GetItemText(nRow, 5);

	CRelaySetDlg Dlg;

	Dlg.m_nMode = RELAY_EDIT_MODE_EDIT;
	Dlg.m_nID = _wtoi(strData[0]);
	Dlg.m_nType = _wtoi(strData[1]);
	Dlg.m_nCurve = _wtoi(strData[2]);
	Dlg.m_strName = (strData[3]);
	Dlg.m_strManuf = (strData[4]);

	Dlg.DoModal();

	UpdateList();
}


void CRelayMngDlg::OnRelaymngdlgDel()
{
	int nRow = m_ctrList.GetSelectionMark();

	CString strData[3];

	strData[0] = m_ctrList.GetItemText(nRow, 0);
	strData[1] = m_ctrList.GetItemText(nRow, 1);
	strData[2] = m_ctrList.GetItemText(nRow, 3);

	CString strMsg;
	strMsg.Format(_T("%s 계전기를 삭제 하시겠습니까?"), strData[2]);

	if (AfxMessageBox(strMsg, MB_YESNO) == IDYES)
	{
		CString strSQL;
		CDataManager* pDataMng = CDataManager::Instance();
		int nType = _wtoi(strData[1]);

		strSQL.Format(_T("delete from  adms_n_machine_code where machine_id = %s"), strData[0]);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		strSQL.Format(_T("delete from  adms_n_relay_Type where machine_id = %s"), strData[0]);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		if (nType == 0)
		{
			strSQL.Format(_T("delete from  ADMS_n_relay_D_tap where machine_id = %s"), strData[0]);
		}
		else
		{
			strSQL.Format(_T("delete from  ADMS_n_relay_A_tap where machine_id = %s"), strData[0]);
		}
		
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		UpdateList();
	}
	

}
