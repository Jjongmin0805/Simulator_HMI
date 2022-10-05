
// FHSDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FHS.h"
#include "FHSDlg.h"
#include "afxdialogex.h"

//#include "../Include/DBContainer/DB_EXTRACT.h"
#include "../Include/DBContainer/DB_QUERY.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFHSDlg 대화 상자



CFHSDlg::CFHSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FHS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nOnline = 0;
}

void CFHSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FHS_DLG_COMBO1, m_ctrCombo[0]);
	DDX_Control(pDX, IDC_FHS_DLG_COMBO2, m_ctrCombo[1]);
	DDX_Control(pDX, IDC_FHS_DLG_COMBO3, m_ctrCombo[2]);
	DDX_Control(pDX, IDC_FHS_DLG_COMBO4, m_ctrCombo[3]);
	DDX_Control(pDX, IDC_FHS_DLG_LIST1, m_ctrList);
	DDX_Control(pDX, IDC_FHS_DLG_DATETIMEPICKER1, m_ctrDate[0]);
	DDX_Control(pDX, IDC_FHS_DLG_DATETIMEPICKER2, m_ctrDate[1]);
	DDX_Control(pDX, IDC_FHS_DLG_RADIO2, m_ctrRadio[0]);
	DDX_Control(pDX, IDC_FHS_DLG_RADIO1, m_ctrRadio[1]);
}

BEGIN_MESSAGE_MAP(CFHSDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_FHS_DLG_BTN1, &CFHSDlg::OnBnClickedFhsDlgBtn1)
	ON_BN_CLICKED(IDC_FHS_DLG_RADIO2, &CFHSDlg::OnBnClickedFhsDlgRadio2)
	ON_BN_CLICKED(IDC_FHS_DLG_RADIO1, &CFHSDlg::OnBnClickedFhsDlgRadio1)
	ON_CBN_SELCHANGE(IDC_FHS_DLG_COMBO1, &CFHSDlg::OnCbnSelchangeFhsDlgCombo1)
	ON_CBN_SELCHANGE(IDC_FHS_DLG_COMBO2, &CFHSDlg::OnCbnSelchangeFhsDlgCombo2)
	ON_WM_TIMER()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CFHSDlg::OnHdnItemclickFhsDlgList1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_FHS_DLG_LIST1, &CFHSDlg::OnLvnColumnclickFhsDlgList1)
	ON_BN_CLICKED(IDC_FHS_DLG_BTN2, &CFHSDlg::OnBnClickedFhsDlgBtn2)
	ON_CBN_SELCHANGE(IDC_FHS_DLG_COMBO4, &CFHSDlg::OnCbnSelchangeFhsDlgCombo4)
END_MESSAGE_MAP()


// CFHSDlg 메시지 처리기

BOOL CFHSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

//	ShowWindow(SW_MAXIMIZE);

//	ShowWindow(SW_MINIMIZE);

	theAppDataMng->SetOnlineStudyMode(2);
	theAppDataMng->ConnectKASIMData(0, 2);

	if (!theDBContainer->ConnectDB())
	{
		TRACE(L"Err : DB Connect Fail.\n");
	}

	Create_List();

	Set_Center();

	m_ctrRadio[0].SetCheck(TRUE);
	m_ctrDate[0].EnableWindow(FALSE);
	m_ctrDate[1].EnableWindow(FALSE);
	GetDlgItem(IDC_FHS_DLG_BTN2)->EnableWindow(FALSE);

	//m_ctrDate[0].SetFormat(_T("'yy'-'MM'-'dd' 'HH':'mm':'SS'"));
	m_ctrDate[0].SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	m_ctrDate[1].SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	
	CTime t_F(2021, 9, 17, 14, 30, 0);
	CTime t_T(2021, 9, 17, 15, 30, 0);

	t_F = CTime::GetCurrentTime();
	t_T = t_F;

	m_ctrDate[0].SetTime(&t_F);
	m_ctrDate[1].SetTime(&t_T);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFHSDlg::Create_List()
{
	m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	m_ctrList.InsertColumn(0, _T("발생시간"), HDF_LEFT, 200);
	m_ctrList.InsertColumn(1, _T("지사"), HDF_LEFT, 80);
	m_ctrList.InsertColumn(2, _T("변전소"), HDF_LEFT, 80);
	m_ctrList.InsertColumn(3, _T("회선명"), HDF_LEFT, 80);
	m_ctrList.InsertColumn(4, _T("개폐기명"), HDF_LEFT, 100);
	m_ctrList.InsertColumn(5, _T("상태변경내용"), HDF_LEFT, 1000);
	m_ctrList.InsertColumn(6, _T("id"), HDF_LEFT, 0);
	m_ctrList.InsertColumn(7, _T("dump"), HDF_LEFT, 0);
	m_ctrList.ShowWindow(SW_SHOW);
	m_ctrList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList.m_HeaderCtrl.SetHeight(27);
	m_ctrList.m_HeaderCtrl.SetFlat();
	m_ctrList.m_HeaderCtrl.SetFlat();
	m_ctrList.m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList.m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList.m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList.SetBgColor(RGB(255, 255, 255));
	m_ctrList.SetUnderLine();
	m_ctrList.SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList.SetTextFont(&m_listfont);
	m_ctrList.SetRowHeight(25);
}

void CFHSDlg::Set_Center()
{
	m_ctrCombo[3].ResetContent();

	CString strSQL;
	strSQL.Format(_T("Select center_office_id, name from center_office order by center_office_id"));

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

			m_ctrCombo[3].AddString(strName);
			m_ctrCombo[3].SetItemData(nCount, (DWORD_PTR)nCenter);

			nCount++;
		}
	}
	dbquery.Close();
}

void CFHSDlg::Set_Office()
{

	int nSel = m_ctrCombo[3].GetCurSel();

	if (nSel < 0)
		return;


	int nCenter = (int)m_ctrCombo[3].GetItemData(nSel);

	m_ctrCombo[0].ResetContent();
	
	m_ctrCombo[1].ResetContent();
	m_ctrCombo[1].AddString(_T("선택없음"));
	m_ctrCombo[1].SetItemData(0, (DWORD_PTR)-1);

	m_ctrCombo[2].ResetContent();
	m_ctrCombo[2].AddString(_T("선택없음"));
	m_ctrCombo[2].SetItemData(0, (DWORD_PTR)-1);

	CString strSQL;
	strSQL.Format(_T("Select member_office_id, name from member_office where center_office_fk = %d;"), nCenter);

	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer(),2);
	CDB_QUERY							dbquery(strSQL.GetBuffer(), 2);

	int nOffice;

	CString strName;

	int nCount = 0;
	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			nOffice =  dbquery.GetData_LONG(0);
			strName.Format(_T("%s"), dbquery.GetData_STR(1));

			m_ctrCombo[0].AddString(strName);
			m_ctrCombo[0].SetItemData(nCount, (DWORD_PTR)nOffice);

			nCount++;
		}
	}
	dbquery.Close();
}

void CFHSDlg::Set_Subs()
{
	int nSel = m_ctrCombo[0].GetCurSel();

	if (nSel < 0)
		return;


	int nOfficeFK = (int)m_ctrCombo[0].GetItemData(nSel);

	m_ctrCombo[1].ResetContent();
	m_ctrCombo[1].AddString(_T("선택없음"));
	m_ctrCombo[1].SetItemData(0, (DWORD_PTR) -1);

	m_ctrCombo[2].ResetContent();
	m_ctrCombo[2].AddString(_T("선택없음"));
	m_ctrCombo[2].SetItemData(0, (DWORD_PTR)-1);

	CString strSQL;
	strSQL.Format(_T("select mrid,name from identifiedobject where mrid in \
		(select  distinct CHANGE_EQC_MRFK  from  conductingequipment where mrid in \
		(select distinct mtr_mrfk from dl where member_office_fk = %d))"), nOfficeFK);

	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer(), 1);
	CDB_QUERY							dbquery(strSQL.GetBuffer(),1);

	LONGLONG lmrid,test;
	CString strName;

	int nCount = 1;
	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			lmrid = dbquery.GetData_LONGLONG(0);
			strName.Format(_T("%s"), dbquery.GetData_STR(1));

			m_ctrCombo[1].AddString(strName);
			m_ctrCombo[1].SetItemData(nCount, (DWORD_PTR)lmrid);
			

			test = m_ctrCombo[1].GetItemData(nCount);

			nCount++;
		}
	}
	m_ctrCombo[1].SetCurSel(0);
	m_ctrCombo[2].SetCurSel(0);

	dbquery.Close();
}

void CFHSDlg::Set_DL()
{
	int nSel = m_ctrCombo[1].GetCurSel();

	if (nSel < 0)
		return;


	LONGLONG lSubsFK = (LONGLONG)m_ctrCombo[1].GetItemData(nSel);

	m_ctrCombo[2].ResetContent();
	m_ctrCombo[2].AddString(_T("선택없음"));
	m_ctrCombo[2].SetItemData(0, (DWORD_PTR)-1);

	CString strSQL;
	strSQL.Format(_T("select mrid,name from identifiedobject where mrid in \
		(select eqc_mrfk from dl where mtr_mrfk in \
		(select  ceq_mrfk from powertransformer where SECONDARY_VOLTAGELEVEL_FK in \
		(select  distinct EQC_MRFK  from  voltagelevel where SUBS_MRFK = %lld)))"), lSubsFK);

	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer(), 1);
	CDB_QUERY							dbquery(strSQL.GetBuffer(), 1);

	LONGLONG lmrid;
	CString strName;

	int nCount = 1;
	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			lmrid = dbquery.GetData_LONGLONG(0);
			strName.Format(_T("%s"), dbquery.GetData_STR(1));

			m_ctrCombo[2].AddString(strName);
			m_ctrCombo[2].SetItemData(nCount, (DWORD_PTR)lmrid);


			nCount++;
		}
	}
	m_ctrCombo[2].SetCurSel(0);

	dbquery.Close();
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFHSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFHSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFHSDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_ctrList.GetSafeHwnd() != NULL)
	{
		CRect rClient, rList;

		GetClientRect(&rClient);
	//	m_ctrList.GetClientRect(&rList);
		
		rList.left = rClient.left +12;
		rList.top = rClient.top + 87;
		rList.bottom = rClient.bottom -10;
		rList.right = rClient.right -10;
		m_ctrList.MoveWindow(rList);
	}
	

}


void CFHSDlg::OnBnClickedFhsDlgBtn1()
{
	int nCheck = m_ctrRadio[0].GetCheck();

	if (nCheck == 1)
	{
		if (m_nOnline == 0)
		{
			m_nOnline = 1;
			m_ctrCombo[0].EnableWindow(FALSE);
			m_ctrCombo[1].EnableWindow(FALSE);
			m_ctrCombo[2].EnableWindow(FALSE);
			m_ctrCombo[3].EnableWindow(FALSE);
			m_ctrRadio[0].EnableWindow(FALSE);
			m_ctrRadio[1].EnableWindow(FALSE);
			
			m_ctrList.DeleteAllItems();
			GetMaxLogID();

			GetDlgItem(IDC_FHS_DLG_BTN1)->SetWindowText(_T("종료"));

			SetTimer(1, 10000, NULL);
		}
		else
		{
			m_nOnline = 0;
			m_ctrCombo[0].EnableWindow(TRUE);
			m_ctrCombo[1].EnableWindow(TRUE);
			m_ctrCombo[2].EnableWindow(TRUE);
			m_ctrCombo[3].EnableWindow(TRUE);
			m_ctrRadio[0].EnableWindow(TRUE);
			m_ctrRadio[1].EnableWindow(TRUE);

			GetDlgItem(IDC_FHS_DLG_BTN1)->SetWindowText(_T("조회"));
			KillTimer(1);
		}
		
	}
	else
	{
		UpdateList_History();
	}
}


void CFHSDlg::OnBnClickedFhsDlgRadio2()
{
	int nCheck = m_ctrRadio[0].GetCheck();

	if (nCheck == 1)
	{
		m_ctrRadio[1].SetCheck(0);
		m_ctrDate[0].EnableWindow(FALSE);
		m_ctrDate[1].EnableWindow(FALSE);
		GetDlgItem(IDC_FHS_DLG_BTN2)->EnableWindow(FALSE);
	}

}


void CFHSDlg::OnBnClickedFhsDlgRadio1()
{
	int nCheck = m_ctrRadio[1].GetCheck();

	if (nCheck == 1)
	{
		m_ctrRadio[0].SetCheck(0);

		m_ctrDate[0].EnableWindow(TRUE);
		m_ctrDate[1].EnableWindow(TRUE);
		GetDlgItem(IDC_FHS_DLG_BTN2)->EnableWindow(TRUE);
	}

	
}


BOOL CFHSDlg::DestroyWindow()
{
	m_headerfont.DeleteObject();
	m_listfont.DeleteObject();

	theDBContainer->Close();

	theAppDataMng->DIsConnectKASIMData(0);
	theAppDataMng->Close();
	theUtil->Close();

	

	return CDialogEx::DestroyWindow();
}

void CFHSDlg::OnCbnSelchangeFhsDlgCombo4()
{
	Set_Office();
}

void CFHSDlg::OnCbnSelchangeFhsDlgCombo1()
{
	Set_Subs();
}


void CFHSDlg::OnCbnSelchangeFhsDlgCombo2()
{
	Set_DL();
}

void CFHSDlg::GetMaxLogID()
{
	CString strSQL;
	strSQL.Format(_T("select max(log_id) from log_event"))	;

	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer(), 1);
	CDB_QUERY							dbquery(strSQL.GetBuffer(), 1);

	m_lMaxLogID = 0;

	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			m_lMaxLogID = dbquery.GetData_LONGLONG(0);
		}
	}
	dbquery.Close();
}

void CFHSDlg::UpdateList_Online()
{
	int nSel[3];

	nSel[0] = m_ctrCombo[0].GetCurSel();

	if (nSel[0] < 0)
		return;

	nSel[1] = m_ctrCombo[1].GetCurSel();

	if (nSel[1] < 0)
		return;

	nSel[2] = m_ctrCombo[2].GetCurSel();

	if (nSel[2] < 0)
		return;

	int nOfficeFK = (int)m_ctrCombo[0].GetItemData(nSel[0]);
	LONGLONG lSubsFK;// = (LONGLONG)m_ctrCombo[1].GetItemData(nSel[1]);
	LONGLONG lDLFK;// = (LONGLONG)m_ctrCombo[2].GetItemData(nSel[2]);


	/*CTime timeF, timeT;
	m_ctrDate[0].GetTime(timeF);
	m_ctrDate[1].GetTime(timeT);*/

	CString strSQL;
	
	if (nSel[2] > 0)
	{
		lSubsFK = (LONGLONG)m_ctrCombo[1].GetItemData(nSel[1]);
		lDLFK = (LONGLONG)m_ctrCombo[2].GetItemData(nSel[2]);

		strSQL.Format(_T("select a.LOG_ID,a.event_time,f.NAME as subs,d.NAME as dlnm,g.NAME as eq,a.event_msg \
			from log_event a \
			inner join \
			identifiedobject f \
			on f.mrid = a.subs_mrfk \
			inner join \
			identifiedobject d \
			on d.mrid = a.dl_mrfk \
			inner join \
			identifiedobject g \
			on g.mrid = a.ceq_mrfk \
			where event_type = 0 and log_id > %lld \
			and  member_office_fk = %d and subs_mrfk = %lld and dl_mrfk = %lld")
			, m_lMaxLogID, nOfficeFK, lSubsFK, lDLFK);
	}
	else if (nSel[1] > 0)
	{
		lSubsFK = (LONGLONG)m_ctrCombo[1].GetItemData(nSel[1]);

		strSQL.Format(_T("select a.LOG_ID,a.event_time,f.NAME as subs,d.NAME as dlnm,g.NAME as eq,a.event_msg \
			from log_event a \
			inner join \
			identifiedobject f \
			on f.mrid = a.subs_mrfk \
			inner join \
			identifiedobject d \
			on d.mrid = a.dl_mrfk \
			inner join \
			identifiedobject g \
			on g.mrid = a.ceq_mrfk \
			where event_type = 0 and log_id > %lld \
			and  member_office_fk = %d and subs_mrfk > %lld")
			, m_lMaxLogID, nOfficeFK, lSubsFK);

	}
	else
	{
		strSQL.Format(_T("select a.LOG_ID,a.event_time,f.NAME as subs,d.NAME as dlnm,g.NAME as eq,a.event_msg \
			from log_event a \
			inner join \
			identifiedobject f \
			on f.mrid = a.subs_mrfk \
			inner join \
			identifiedobject d \
			on d.mrid = a.dl_mrfk \
			inner join \
			identifiedobject g \
			on g.mrid = a.ceq_mrfk \
			where event_type = 0 and log_id > %lld \
			and  member_office_fk = %d ")
			, m_lMaxLogID, nOfficeFK);
	}


	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer(), 1);
	CDB_QUERY							dbquery(strSQL.GetBuffer(), 1);

	CString strData[7];

	m_ctrCombo[0].GetLBText(nSel[0], strData[2]);
	//m_ctrCombo[1].GetLBText(nSel[1], strData[3]);
	//m_ctrCombo[2].GetLBText(nSel[2], strData[4]);


	LONGLONG lLogID;
	CString strName;


	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			lLogID = dbquery.GetData_LONGLONG(0);
			strData[0].Format(_T("%lld"), lLogID);
			strData[1].Format(_T("%s"), dbquery.GetData_STR(1));
			strData[3].Format(_T("%s"), dbquery.GetData_STR(2));
			strData[4].Format(_T("%s"), dbquery.GetData_STR(3));
			strData[5].Format(_T("%s"), dbquery.GetData_STR(4));
			strData[6].Format(_T("%s"), dbquery.GetData_STR(5));
	
			m_ctrList.InsertItem(m_ctrList.GetItemCount(), strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 1, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 2, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 3, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 4, strData[5], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 5, strData[6], RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 6, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);


			m_lMaxLogID = lLogID;

		}
	}
	dbquery.Close();

	m_ctrList.SetFocus();
	m_ctrList.RedrawWindow();

	int nCount = m_ctrList.GetItemCount() -1;
	m_ctrList.EnsureVisible(nCount,TRUE);
}

void CFHSDlg::UpdateList_History()
{
	m_ctrList.DeleteAllItems();

	int nSel[3];
		
	nSel[0] = m_ctrCombo[0].GetCurSel();

	if (nSel[0] < 0)
		return;

	nSel[1] = m_ctrCombo[1].GetCurSel();

	if (nSel[1] < 0)
		return;

	nSel[2] = m_ctrCombo[2].GetCurSel();

	if (nSel[2] < 0)
		return;

	int nOfficeFK = (int)m_ctrCombo[0].GetItemData(nSel[0]);
	LONGLONG lSubsFK;// = (LONGLONG)m_ctrCombo[1].GetItemData(nSel[1]);
	LONGLONG lDLFK;// = (LONGLONG)m_ctrCombo[2].GetItemData(nSel[2]);


	CTime timeF, timeT;
	m_ctrDate[0].GetTime(timeF);
	m_ctrDate[1].GetTime(timeT);
	
	CString strSQL;
	if (nSel[2] > 0)
	{
		lSubsFK = (LONGLONG)m_ctrCombo[1].GetItemData(nSel[1]);
		lDLFK = (LONGLONG)m_ctrCombo[2].GetItemData(nSel[2]);

		strSQL.Format(_T("select a.LOG_ID,a.event_time,f.NAME as subs,d.NAME as dlnm,g.NAME as eq,a.event_msg \
			from log_event a \
			inner join \
			identifiedobject f \
			on f.mrid = a.subs_mrfk \
			inner join \
			identifiedobject d \
			on d.mrid = a.dl_mrfk \
			inner join \
			identifiedobject g \
			on g.mrid = a.ceq_mrfk \
			where event_type = 0 and event_time >= '%s' and	event_time <= '%s' \
			and  member_office_fk = %d and subs_mrfk = %lld and dl_mrfk = %lld")
			, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S")), nOfficeFK, lSubsFK, lDLFK);
	}
	else if (nSel[1] > 0)
	{
		lSubsFK = (LONGLONG)m_ctrCombo[1].GetItemData(nSel[1]);

		strSQL.Format(_T("select a.LOG_ID,a.event_time,f.NAME as subs,d.NAME as dlnm,g.NAME as eq,a.event_msg \
			from log_event a \
			inner join \
			identifiedobject f \
			on f.mrid = a.subs_mrfk \
			inner join \
			identifiedobject d \
			on d.mrid = a.dl_mrfk \
			inner join \
			identifiedobject g \
			on g.mrid = a.ceq_mrfk \
			where event_type = 0 and event_time >= '%s' and	event_time <= '%s' \
			and  member_office_fk = %d and subs_mrfk = %lld")
			, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S")), nOfficeFK, lSubsFK);

	}
	else
	{
		strSQL.Format(_T("select a.LOG_ID,a.event_time,f.NAME as subs,d.NAME as dlnm,g.NAME as eq,a.event_msg \
			from log_event a \
			inner join \
			identifiedobject f \
			on f.mrid = a.subs_mrfk \
			inner join \
			identifiedobject d \
			on d.mrid = a.dl_mrfk \
			inner join \
			identifiedobject g \
			on g.mrid = a.ceq_mrfk \
			where event_type = 0 and event_time >= '%s' and	event_time <= '%s' \
			and  member_office_fk = %d ")
			, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S")) , nOfficeFK);
	}
	

	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer(), 1);
	CDB_QUERY							dbquery(strSQL.GetBuffer(), 1);

	CString strData[7];

	m_ctrCombo[0].GetLBText(nSel[0], strData[2]);
	//m_ctrCombo[1].GetLBText(nSel[1], strData[3]);
	//m_ctrCombo[2].GetLBText(nSel[2], strData[4]);


	LONGLONG lLogID;
	CString strName;

	if (dbquery.GetRecordCount() > 0)
	{
		while (dbquery.MoveNext())
		{
			lLogID = dbquery.GetData_LONGLONG(0);
			strData[0].Format(_T("%lld"), lLogID);
			strData[1].Format(_T("%s"), dbquery.GetData_STR(1));
			strData[3].Format(_T("%s"), dbquery.GetData_STR(2));
			strData[4].Format(_T("%s"), dbquery.GetData_STR(3));
			strData[5].Format(_T("%s"), dbquery.GetData_STR(4));
			strData[6].Format(_T("%s"), dbquery.GetData_STR(5));


			m_ctrList.InsertItem(m_ctrList.GetItemCount(), strData[1], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 1, strData[2], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 2, strData[3], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 3, strData[4], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 4, strData[5], RGB(0, 0, 0), RGB(255, 255, 255), HDF_CENTER);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 5, strData[6], RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 6, strData[0], RGB(0, 0, 0), RGB(255, 255, 255), HDF_LEFT);

		}
	}
	dbquery.Close();

	//m_ctrList.SetFocus();
	m_ctrList.RedrawWindow();
}

void CFHSDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		UpdateList_Online();
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CFHSDlg::OnHdnItemclickFhsDlgList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CFHSDlg::OnLvnColumnclickFhsDlgList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CFHSDlg::OnBnClickedFhsDlgBtn2()
{
	int nCount = theAppDataMng->GetTableRealCount(_T("FIINFO_DYN_FIO"));
	
	for (int i = 1 ; i <= nCount; i++)
	{
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_II_CBSW"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_CBSW_CEQID"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_II_FLTINFO"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_SI_FLTINFO"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_FIKIND"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_FITYPE"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IAOPR"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IBOPR"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_ICOPR"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_INOPR"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IA"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IB"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IC"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IN"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_CHANGEABLE"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_COMERR"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_FIORER_DIAG"), i, (double)0.);
		
	}

	int nSel[3];

	nSel[0] = m_ctrCombo[0].GetCurSel();

	if (nSel[0] < 0)
		return;

	nSel[1] = m_ctrCombo[1].GetCurSel();

	if (nSel[1] < 1)
	{
		AfxMessageBox(_T("변전소 정보가 없습니다."));
		return;
	}

	nSel[2] = m_ctrCombo[2].GetCurSel();

	if (nSel[2] < 1)
	{
		AfxMessageBox(_T("DL 정보가 없습니다."));
		return;
	}

	int nOfficeFK = (int)m_ctrCombo[0].GetItemData(nSel[0]);
	LONGLONG lSubsFK;// = (LONGLONG)m_ctrCombo[1].GetItemData(nSel[1]);
	LONGLONG lDLFK;// = (LONGLONG)m_ctrCombo[2].GetItemData(nSel[2]);


	CTime timeF, timeT;
	m_ctrDate[0].GetTime(timeF);
	m_ctrDate[1].GetTime(timeT);

	CString strSQL, strSQL_pre;
	lSubsFK = (LONGLONG)m_ctrCombo[1].GetItemData(nSel[1]);
	lDLFK = (LONGLONG)m_ctrCombo[2].GetItemData(nSel[2]);
	

	strSQL.Format(_T("SELECT lg.CEQ_MRFK AS FIINFO_CBSW_CEQID, IFNULL(lga.NEW_VALUE, 0) AS 'FIINFO_IAOPR', IFNULL(lgb.NEW_VALUE, 0) AS 'FIINFO_IBOPR', \
		IFNULL(lgc.NEW_VALUE, 0) AS 'FIINFO_ICOPR', IFNULL(lgn.NEW_VALUE, 0) AS 'FIINFO_INOPR', lgia.NEW_VALUE AS 'FIINFO_IA', lgib.NEW_VALUE AS 'FIINFO_IB',\
		lgic.NEW_VALUE AS 'FIINFO_IC', lgin.NEW_VALUE AS 'FIINFO_IN' \
		FROM adms_office.log_event lg \
		left JOIN(SELECT CEQ_MRFK, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(code = 29 OR CODE = 177) and OLD_VALUE = 0 and \
		EVENT_TIME BETWEEN '%s' AND '%s') AS lga ON lga.CEQ_MRFK = lg.CEQ_MRFK \
		left JOIN(SELECT CEQ_MRFK, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 30 or CODE = 178) and OLD_VALUE = 0 and \
		EVENT_TIME BETWEEN '%s' AND '%s') AS lgb ON lgb.CEQ_MRFK = lg.CEQ_MRFK \
		left JOIN(SELECT CEQ_MRFK, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 31 or CODE = 179) and OLD_VALUE = 0 and \
		EVENT_TIME BETWEEN '%s' AND '%s') AS lgc ON lgc.CEQ_MRFK = lg.CEQ_MRFK \
		left JOIN(SELECT CEQ_MRFK, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 32 or CODE = 180) and OLD_VALUE = 0 and \
		EVENT_TIME BETWEEN '%s' AND '%s') AS lgn ON lgn.CEQ_MRFK = lg.CEQ_MRFK \
		left JOIN(SELECT CEQ_MRFK, NEW_VALUE FROM adms_office.log_event WHERE point_type = 1 AND CODE = 53 and OLD_VALUE = 0 and \
		EVENT_TIME BETWEEN '%s' AND '%s') AS lgia ON lgia.CEQ_MRFK = lg.CEQ_MRFK \
		left JOIN(SELECT CEQ_MRFK, NEW_VALUE FROM adms_office.log_event WHERE point_type = 1 AND CODE = 54 and OLD_VALUE = 0 and \
		EVENT_TIME BETWEEN '%s' AND '%s') AS lgib ON lgib.CEQ_MRFK = lg.CEQ_MRFK \
		left JOIN(SELECT CEQ_MRFK, NEW_VALUE FROM adms_office.log_event WHERE point_type = 1 AND CODE = 55 and OLD_VALUE = 0 and \
		EVENT_TIME BETWEEN '%s' AND '%s') AS lgic ON lgic.CEQ_MRFK = lg.CEQ_MRFK \
		left JOIN(SELECT CEQ_MRFK, NEW_VALUE FROM adms_office.log_event WHERE point_type = 1 AND CODE = 56 and OLD_VALUE = 0 and \
		EVENT_TIME BETWEEN '%s' AND '%s') AS lgin ON lgin.CEQ_MRFK = lg.CEQ_MRFK \
		WHERE lg.point_type = 3 AND(lg.code = 33 OR lg.code = 177 OR lg.code = 178 OR lg.code = 179 OR lg.code = 180) AND lg.OLD_VALUE = 0 AND \
		lg.MEMBER_OFFICE_FK = %d AND lg.SUBS_MRFK = %lld AND lg.DL_MRFK = %lld AND (lgia.NEW_VALUE IS NOT NULL OR lgib.NEW_VALUE IS NOT NULL OR lgic.NEW_VALUE IS NOT NULL OR lgin.NEW_VALUE IS NOT NULL) AND \
		lg.EVENT_TIME BETWEEN '%s' AND '%s' GROUP BY lg.CEQ_MRFK;")
		, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S"))
		, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S"))
		, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S"))
		, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S"))
		, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S"))
		, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S"))
		, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S"))
		, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S"))
		, nOfficeFK, lSubsFK, lDLFK
		, timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S")));

	
	strSQL_pre.Format(_T("SELECT MIN(le.LOG_ID), Max(le.LOG_ID) FROM adms_office.log_event le WHERE le.EVENT_TIME BETWEEN '%s' AND '%s' ;"), timeF.Format(_T("%Y-%m-%d %H:%M:%S")), timeT.Format(_T("%Y-%m-%d %H:%M:%S")));
	//CDB_EXTRACT						dbquery1(0, strSQL_pre.GetBuffer(), 1);
	CDB_QUERY							dbquery1(strSQL.GetBuffer(), 1);
	int Start_index;
	int End_index;
	if (dbquery1.GetRecordCount() > 0)
	{
		while (dbquery1.MoveNext())
		{
			Start_index = dbquery1.GetData_NUM(0);
			End_index = dbquery1.GetData_NUM(1);
		}
	}


	strSQL.Format(_T("SELECT lg0.CEQ_MRFK AS FIINFO_CBSW_CEQID, max(IFNULL(lga.NEW_VALUE,0)) AS 'FIINFO_IAOPR' , max(IFNULL(lgb.NEW_VALUE,0)) AS 'FIINFO_IBOPR' ,max(IFNULL(lgc.NEW_VALUE,0)) AS 'FIINFO_ICOPR' , max(IFNULL(lgn.NEW_VALUE,0)) AS 'FIINFO_INOPR' ,\
							 max(IFNULL(lgia.NEW_VALUE,0)) AS 'FIINFO_IA', max(ifnull(lgib.NEW_VALUE,0)) AS 'FIINFO_IB', max(ifnull(lgic.NEW_VALUE,0)) AS 'FIINFO_IC', max(ifnull(lgin.NEW_VALUE,0)) AS 'FIINFO_IN',\
							 max(IFNULL(lgocrs.NEW_VALUE, 0)) AS 'FIINFO_OCRS', max(IFNULL(lgocrd.NEW_VALUE, 0)) AS 'FIINFO_OCRD', max(IFNULL(lgocgrs.NEW_VALUE, 0)) AS 'FIINFO_OCGRS', max(IFNULL(lgocgrd.NEW_VALUE, 0)) AS 'FIINFO_OCGRD'\
						FROM(SELECT * from adms_office.log_event lg0 WHERE lg0.LOG_ID BETWEEN %d AND %d) AS lg0 \
						left JOIN(SELECT LOG_ID, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 29 OR CODE = 177) AND OLD_VALUE = 0 AND LOG_ID BETWEEN %d AND %d) AS lga ON lga.LOG_ID = lg0.LOG_ID \
						left jOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 30 or CODE = 178) and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgb ON lg0.LOG_ID = lgb.LOG_ID \
						left jOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 31 or CODE = 179) and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgc ON lg0.LOG_ID = lgc.LOG_ID \
						left JOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 32 or CODE = 180) and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgn ON lg0.LOG_ID = lgn.LOG_ID \
						left JOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 430) and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgocrs ON lg0.LOG_ID = lgocrs.LOG_ID \
						left JOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 431) and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgocrd ON lg0.LOG_ID = lgocrd.LOG_ID \
						left JOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 432) and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgocgrs ON lg0.LOG_ID = lgocgrs.LOG_ID \
						left JOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 3 AND(CODE = 433) and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgocgrd ON lg0.LOG_ID = lgocgrd.LOG_ID \
						left JOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 1 AND CODE = 53 and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgia ON lgia.LOG_ID = lg0.LOG_ID \
						left JOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 1 AND CODE = 54 and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgib ON lgib.LOG_ID = lg0.LOG_ID \
						left JOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 1 AND CODE = 55 and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgic ON lgic.LOG_ID = lg0.LOG_ID \
						left JOIN(SELECT log_id, NEW_VALUE FROM adms_office.log_event WHERE point_type = 1 AND CODE = 56 and OLD_VALUE = 0 and LOG_ID BETWEEN %d AND %d) AS lgin ON lgin.LOG_ID = lg0.LOG_ID \
						WHERE((lgocrs.NEW_VALUE IS NOT NULL OR lgocrd.NEW_VALUE IS NOT NULL OR lgocgrs.NEW_VALUE IS NOT NULL OR lgocgrd.NEW_VALUE IS NOT NULL) OR(lga.NEW_VALUE is not null OR lgb.NEW_VALUE is not null OR lgc.NEW_VALUE is not null OR lgn.NEW_VALUE is not NULL) or (lgia.NEW_VALUE IS NOT NULL OR lgib.NEW_VALUE IS NOT NULL OR lgic.NEW_VALUE IS NOT NULL OR lgin.NEW_VALUE IS NOT NULL))\
						GROUP BY lg0.CEQ_MRFK;"), Start_index, End_index, Start_index, End_index, Start_index, End_index, Start_index, End_index, Start_index, End_index, Start_index, End_index, Start_index, End_index, Start_index, End_index, Start_index, End_index, Start_index, End_index, Start_index, End_index, Start_index, End_index, Start_index, End_index);

	//CDB_EXTRACT						dbquery(0, strSQL.GetBuffer(), 1);
	CDB_QUERY							dbquery(strSQL.GetBuffer(), 1);
	CString strData[7];

	m_ctrCombo[0].GetLBText(nSel[0], strData[2]);
	//m_ctrCombo[1].GetLBText(nSel[1], strData[3]);
	//m_ctrCombo[2].GetLBText(nSel[2], strData[4]);


	LONGLONG lCeqID;
	int		nIdx;
	int nOper[4];
	int nCBOper[4];
	double dValue[4];
	
	int nND_Idx = -1;

	CString strName;

	if (dbquery.GetRecordCount() > 0)
	{
		nCount = 1;
		while (dbquery.MoveNext())
		{
			lCeqID = dbquery.GetData_LONGLONG(0);
			nIdx = GetIndex_CBSW(lCeqID);
			if(nIdx == -1)
				continue;

			nOper[0] = dbquery.GetData_NUM(1);
			nOper[1] = dbquery.GetData_NUM(2);
			nOper[2] = dbquery.GetData_NUM(3);
			nOper[3] = dbquery.GetData_NUM(4);
			dValue[0] = dbquery.GetData_DBL(5);
			dValue[1] = dbquery.GetData_DBL(6);
			dValue[2] = dbquery.GetData_DBL(7);
			dValue[3] = dbquery.GetData_DBL(8);
			nCBOper[0] = dbquery.GetData_DBL(9);
			nCBOper[1] = dbquery.GetData_DBL(10);
			nCBOper[2] = dbquery.GetData_DBL(11);
			nCBOper[3] = dbquery.GetData_DBL(12);

			PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_II_CBSW"), nCount, (double)nIdx);
			PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_CBSW_CEQID"), nCount, (double)lCeqID);
			PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IAOPR"), nCount, (double)nOper[0]);
			PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IBOPR"), nCount, (double)nOper[1]);
			PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_ICOPR"), nCount, (double)nOper[2]);
			PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_INOPR"), nCount, (double)nOper[3]);
			PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IA"), nCount, (double)dValue[0]);
			PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IB"), nCount, (double)dValue[1]);
			PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IC"), nCount, (double)dValue[2]);
			PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IN"), nCount, (double)dValue[3]);


			if ((nCBOper[0] == 1) || (nCBOper[1] == 1) || (nCBOper[2] == 1) || (nCBOper[3] == 1))
			{
				PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_FIKIND"), nCount, (int)1);
				PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IAOPR"), nCount, nCBOper[0]);
				PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IBOPR"), nCount, nCBOper[1]);
				PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_ICOPR"), nCount, nCBOper[2]);
				PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_INOPR"), nCount, nCBOper[3]);
			}
			else
			{
				PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_FIKIND"), nCount, (int)0);
				PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IAOPR"), nCount, 0);
				PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_IBOPR"), nCount, 0);
				PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_ICOPR"), nCount, 0);
				PUTDOUBLE2VALUE(_T("FIINFO_DYN_FIO"), _T("FIINFO_INOPR"), nCount, 0);
			}

			nND_Idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_TND"), nIdx);

			nCount++;
		}
	}
	dbquery.Close();

	CString strMsg;
	
	if (nCount > 1)
		//strMsg = _T("고장알림이력 KACIM 입력 완료");
		strMsg.Format(_T("고장알림이력 %d FI정보 단선도 입력 완료"), nCount);
	else
		strMsg = _T("고장알림이력 없음");

	AfxMessageBox(strMsg);

	if (nND_Idx < 1)
		return;

	HWND																				pHMIWnd;
	pHMIWnd = ::FindWindow(NULL, _T("Simulator_SLD"));
	if (!pHMIWnd)																		return;

	CString strSend;
	strSend.Format(_T("888,%d,고장이력단선도"), nND_Idx);

	TCHAR																				szSendMsg[128] = { 0, };
	swprintf_s(szSendMsg, _T("%s"), strSend);

	COPYDATASTRUCT																		_cds = { 0, };
	_cds.dwData = (ULONG)2;
	_cds.cbData = (DWORD)sizeof(szSendMsg);
	_cds.lpData = (BYTE *)szSendMsg;
	::SendMessage(pHMIWnd, WM_COPYDATA, (WPARAM)this, (LPARAM)&_cds);


}


int CFHSDlg::GetIndex_CBSW(LONGLONG lCeqID)
{
	int nCount = theAppDataMng->GetTableRealCount(_T("CBSW_STA"));

	LONGLONG lCeqID_kacim;

	for (int i = 1; i <= nCount; i++)
	{
		lCeqID_kacim = GETVALUE(unsigned long long, _T("CBSW_STA"), _T("CBSW_CEQID"),i);

		if (lCeqID == lCeqID_kacim)
		{
			return i;
		}

	}

	return -1;
}

