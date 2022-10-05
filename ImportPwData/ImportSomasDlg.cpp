// ImportPwDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImportSomasDlg.h"
#include "afxdialogex.h"
#include <afxinet.h>
#include "PTS_LOGIN_DLG.h"

// CImportSomasDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImportSomasDlg, CDialogEx)

CImportSomasDlg::CImportSomasDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImportSomasDlg::IDD, pParent)
{
	m_nList4ColCount = 0;
	m_dOptimal = 0.;

	/*m_pSomas_Load = NULL;
	m_pSomas_Voltage = NULL;
	m_pPts = NULL;*/

}

CImportSomasDlg::~CImportSomasDlg()
{
	m_Session.Close();
	m_Connect.Close();

	/*if(m_pSomas_Load)
	{
		m_pSomas_Load->Close();
		delete m_pSomas_Load;
		m_pSomas_Load = NULL;
	}
	if(m_pSomas_Voltage)
	{
		m_pSomas_Voltage->Close();
		delete m_pSomas_Voltage;
		m_pSomas_Voltage = NULL;
	}
	if(m_pPts)
	{
		m_pPts->Close();
		delete m_pPts;
		m_pPts = NULL;
	}*/
}

void CImportSomasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_DATE1, m_ctrDataF);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_DATE2, m_ctrDataT);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_LIST1, m_ctrList1);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_PROGRESS1, m_ctrProgress);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_COMBO1, m_ctrCombo1);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_COMBO2, m_ctrCombo2);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_COMBO3, m_ctrCombo3);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_LIST4, m_ctrList4);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_CHK1, m_ctrBtnChk1);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_CHK2, m_ctrBtnChk2);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_CHK3, m_ctrBtnChk3);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_CHK4, m_ctrBtnChk4);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_CHK5, m_ctrBtnChk5);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_CHK6, m_ctrBtnChk6);
	DDX_Control(pDX, IDC_IMPORT_SOMAS_DLG_CHK7, m_ctrBtnChk7);
}

BEGIN_MESSAGE_MAP(CImportSomasDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_IMPORT_SOMAS_DLG_COMBO1, &CImportSomasDlg::OnCbnSelchangeImportPwDlgCombo1)
	ON_CBN_SELCHANGE(IDC_IMPORT_SOMAS_DLG_COMBO2, &CImportSomasDlg::OnCbnSelchangeImportPwDlgCombo2)
	ON_CBN_SELCHANGE(IDC_IMPORT_SOMAS_DLG_COMBO3, &CImportSomasDlg::OnCbnSelchangeImportPwDlgCombo3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_IMPORT_SOMAS_DLG_LIST1, &CImportSomasDlg::OnLvnItemchangedImportPwDlgList1)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_IMPORT_SOMAS_DLG_LIST1, &CImportSomasDlg::OnLvnItemchangingImportPwDlgList1)
	ON_BN_CLICKED(IDC_IMPORT_SOMAS_DLG_CHK1, &CImportSomasDlg::OnBnClickedImportSomasDlgChk1)
	ON_BN_CLICKED(IDC_IMPORT_SOMAS_DLG_BTN2, &CImportSomasDlg::OnBnClickedImportSomasDlgBtn2)
	ON_BN_CLICKED(IDC_IMPORT_SOMAS_DLG_BTN3, &CImportSomasDlg::OnBnClickedImportSomasDlgBtn3)
	ON_BN_CLICKED(IDC_IMPORT_SOMAS_DLG_BTN1, &CImportSomasDlg::OnBnClickedImportSomasDlgBtn1)
	ON_BN_CLICKED(IDC_IMPORT_SOMAS_DLG_CHK2, &CImportSomasDlg::OnBnClickedImportSomasDlgChk2)
	ON_BN_CLICKED(IDC_IMPORT_SOMAS_DLG_BTN4, &CImportSomasDlg::OnBnClickedImportSomasDlgBtn4)
	ON_BN_CLICKED(IDC_IMPORT_SOMAS_DLG_CHK3, &CImportSomasDlg::OnBnClickedImportSomasDlgChk3)
	ON_BN_CLICKED(IDC_IMPORT_SOMAS_DLG_CHK4, &CImportSomasDlg::OnBnClickedImportSomasDlgChk4)
	ON_BN_CLICKED(IDC_IMPORT_SOMAS_DLG_CHK5, &CImportSomasDlg::OnBnClickedImportSomasDlgChk5)
	ON_BN_CLICKED(IDC_IMPORT_SOMAS_DLG_BTN5, &CImportSomasDlg::OnBnClickedImportSomasDlgBtn5)
END_MESSAGE_MAP()


// CImportSomasDlg 메시지 처리기입니다.


BOOL CImportSomasDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	m_pData = CDataManager::Instance();

	if(m_pData == NULL)
		CDialogEx::OnCancel();

	/*if(!CreateSession())
	{

		CDialogEx::OnCancel();
		return FALSE;
	}*/

	DWORD style = m_ctrList1.GetExtendedStyle();
	style |= (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	style |= LVS_EX_CHECKBOXES;
	m_ctrList1.SetExtendedStyle(style);
	m_ctrList1.InsertColumn(0,_T("선로명"),LVCFMT_LEFT,70);

	m_ctrList4.SetExtendedStyle(style);
	m_ctrList4.InsertColumn(0,_T("분산전원명"),LVCFMT_LEFT,190);
	m_ctrList4.InsertColumn(1,_T("ID"),LVCFMT_LEFT,0);

	CTime t;
	m_ctrDataF.GetTime(t);
	t -= CTimeSpan(365,0,0,0);
	m_ctrDataF.SetTime(&t);
	
//	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("Somas 부하정보\r\n\r\n가져오는 중..."));
	InitData();

	

	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT5,_T("00"));
	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT6,_T("24"));

	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT7,_T("00"));
	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT8,_T("24"));

	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT18,_T("23.358"));
	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT19,_T("22.900"));

	m_ctrBtnChk4.SetCheck(TRUE);
	m_ctrBtnChk5.SetCheck(TRUE);
	m_ctrBtnChk6.SetCheck(TRUE);
	m_ctrBtnChk7.SetCheck(TRUE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CImportSomasDlg::PumpMessages()
{
	// Must call Create() before using the dialog
	ASSERT(m_hWnd!=NULL);

	MSG msg;
	// Handle dialog messages
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if(!IsDialogMessage(&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);  
		}
	}
}

void	CImportSomasDlg::InitData()
{
	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL;
	
	CString strTmp;


	m_ctrCombo1.ResetContent();
	m_ctrCombo2.ResetContent();
	m_ctrCombo3.ResetContent();
	m_ctrList1.DeleteAllItems();
	try
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,NULL, &pBind[l].dwStatus);

		if (rs.Open(m_pData->m_Session_SomasInfo, _T("select office_nm from Office1")) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));
					
			strTmp = pBind[0].szValue;
			m_ctrCombo1.AddString(strTmp);
			
		}
		rs.Close();
		delete pBind;
		pBind = NULL;
	}
	catch(COLEDBException* e )
	{
	//	AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}
}

void CImportSomasDlg::OnCbnSelchangeImportPwDlgCombo1()
{
	if( m_ctrCombo1.GetCount() == 0 ) return;
	m_ctrCombo2.ResetContent();
	m_ctrCombo3.ResetContent();
	m_ctrList1.DeleteAllItems();
	m_ctrList4.DeleteAllItems();

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL, strOfc1, strTmp;
	m_ctrCombo1.GetLBText( m_ctrCombo1.GetCurSel(), strOfc1 );

	try
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select office_cd from Office1 where office_nm = '%s' "), strOfc1);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strOfc1 = pBind[0].szValue;
		

		}
		rs.Close();
		delete pBind;
		pBind = NULL;


		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select office_nm from Office2 where office_cd like '%s%%'"), strOfc1);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strTmp = pBind[0].szValue;
			m_ctrCombo2.AddString(strTmp);

		}
		rs.Close();
		delete pBind;
		pBind = NULL;

	}
	catch (COLEDBException* e)
	{
		//	AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}

}


void CImportSomasDlg::OnCbnSelchangeImportPwDlgCombo2()
{

	if( m_ctrCombo2.GetCount() == 0 ) return;
	m_ctrCombo3.ResetContent();
	m_ctrList1.DeleteAllItems();
	m_ctrList4.DeleteAllItems();

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL, strOfc2, strTmp;
	m_ctrCombo2.GetLBText( m_ctrCombo2.GetCurSel(), strOfc2 );

	try
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select office_cd from Office2 where office_nm = '%s' "), strOfc2);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strOfc2 = pBind[0].szValue;


		}
		rs.Close();
		delete pBind;
		pBind = NULL;


		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select [s/s_name] from SS_Info where [s/s_code] like '%s%%'"), strOfc2);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strTmp = pBind[0].szValue;
			m_ctrCombo3.AddString(strTmp);

		}
		rs.Close();
		delete pBind;
		pBind = NULL;

	}
	catch (COLEDBException* e)
	{
		//	AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}

}


void CImportSomasDlg::OnCbnSelchangeImportPwDlgCombo3()
{
	m_ctrList1.DeleteAllItems();
	m_ctrList4.DeleteAllItems();
	int nItem = 0;

	LVITEM lvitem;
	if( m_ctrCombo3.GetCount() == 0 ) return;

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL, strSS, strTmp;
	m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSS );

	try
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select [s/s_code] from SS_Info where [s/s_name] = '%s' "), strSS);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strSS = pBind[0].szValue;


		}
		rs.Close();
		delete pBind;
		pBind = NULL;


		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select [dl_name] from DL_ID where [code] = '%s'"), strSS);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strTmp = pBind[0].szValue;
		
			lvitem.mask = LVIF_TEXT;
			lvitem.iItem = nItem;
			lvitem.iSubItem = 0;
			lvitem.pszText = (LPWSTR)(LPCTSTR)strTmp;
			m_ctrList1.InsertItem(&lvitem);
			nItem++;

		}
		rs.Close();
		delete pBind;
		pBind = NULL;

	}
	catch (COLEDBException* e)
	{
		//	AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}

	if(m_ctrBtnChk2.GetCheck())
		GetPTS_DGName();
}



BOOL	CImportSomasDlg::GetSomasData(int nURLType)
{
	int nState, nCount = 0;
	CString strSQL, strSS, strDL, strTmp;
	if(nURLType == 0)
	{
		
		for(int  i = 0; i < m_ctrList1.GetItemCount(); i++ )
		{
			nState = m_ctrList1.GetItemState( i, LVIS_STATEIMAGEMASK );
			if( nState != 0x2000 ) continue;
			nCount++;
		}
		if( nCount == 0 )
		{
			AfxMessageBox(_T("체크된 배전선로가 없습니다. 체크후 다시... "));
			return FALSE;
		}
		SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("Somas 부하정보\r\n\r\n가져오는 중..."));
	}
	else 
	{

		m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSS );
		if(strSS.IsEmpty())
		{
			AfxMessageBox(_T("선택된 변전소가 없습니다."));
			return FALSE;
		}
		SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("Somas 전압정보\r\n\r\n가져오는 중..."));
	}	
	
	CTime dateF,dateT;
	m_ctrDataF.GetTime(dateF);
	m_ctrDataT.GetTime(dateT);
	if(  dateT < dateF )
	{
		AfxMessageBox(_T("취득기간 설정이 잘못되었습니다."));
		return FALSE;
	}
	
	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CTime dtDate;
	m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSS );

	m_ctrProgress.SetMarquee(TRUE,10);
	try
	{
		if(nURLType == 0)
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo,_T("delete * from somas_dl_time"));
		else
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, _T("delete * from somas_dl_Voltage" ));
		
		

		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select [s/s_code] from SS_Info where [s/s_name] = '%s' "), strSS);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strSS = pBind[0].szValue;


		}
		rs.Close();
		delete pBind;
		pBind = NULL;


		if(nURLType == 0)
		{
			for(int  i = 0; i < m_ctrList1.GetItemCount(); i++ )
			{
				nState = m_ctrList1.GetItemState( i, LVIS_STATEIMAGEMASK );
				if( nState != 0x2000 ) continue;

				ulFields = 1;
				pBind = new MYBIND[ulFields];
				rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
				for (ULONG l = 0; l < ulFields; l++)
					rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

				strSQL.Format(_T("select [dl_ID] from DL_ID where [code]='%s' and [dl_name] = '%s'"), strSS, m_ctrList1.GetItemText(i, 0));
				if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
					AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
				while (rs.MoveNext() == S_OK)
				{
					if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
						wcscpy_s(pBind[0].szValue, _T(""));

					strDL = pBind[0].szValue;
					dtDate = dateF;

					while (1)
					{
						PumpMessages();
						// strSS, strDL
						GetWebDate(nURLType, strSS, strDL, dtDate);
						Conversion(nURLType);
						if (ReadData(strSS.Right(4), m_ctrList1.GetItemText(i, 0), dtDate))
							dtDate += CTimeSpan(1, 0, 0, 0);

						if (dtDate >= dateT)
							break;
						Sleep(200);
					}
				}
				rs.Close();
				delete pBind;
				pBind = NULL;
			}
			SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("Somas 부하정보\r\n\r\n완료"));
		}
		else 
		{
			dtDate = dateF;

			while(1)
			{
				PumpMessages();
				// strSS, strDL
				GetWebDate(nURLType, strSS, strDL, dtDate );
				Conversion(nURLType);
				if( ReadData_Voltage( strSS.Right(4), dtDate ) )
					dtDate += CTimeSpan( 1, 0, 0, 0 );

				if( dtDate >= dateT )
					break;
				Sleep( 200 );
			}
			SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("Somas 전압정보\r\n\r\n완료"));
		}
		m_ctrProgress.SetMarquee(FALSE,10);
		m_ctrProgress.Invalidate(TRUE);
	}
	catch(COLEDBException* e )
	{
		//AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}

	return TRUE;
	
}


void CImportSomasDlg::GetWebDate(int nURLType,CString strSS, CString strDL, CTime dtDate)
{
	CInternetSession session( _T("My session") );
	CString strURL;
	CStdioFile* pFile;
	int nSel;
	char buf[1025];
	FILE* stream ;
	try
	{
		if(nURLType == 0)
			strURL.Format(	_T("http://100.1.21.33/emx/OV_EMX_400_R02_AO.do?ofc_cd_1=%s&ofc_cd_2=%s&ofc_cd_3=%s&imat=%s&ddat=%d-%02d-%02d&flag=D")
				,strSS.Left(4), strSS.Mid(4,4),strSS.Right(4),strDL,dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay());
		else
			strURL.Format(	_T("http://100.1.21.33/tav/OV_TAV_500_R01_AO.do?ymd_knd=D&startDate1=%d-%02d-%02d&ofc_cd_1=%s&ofc_cd_2=%s&ofc_cd_3=%s")
			,dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(),strSS.Left(4), strSS.Mid(4,4),strSS.Right(4));

		pFile = session.OpenURL(strURL);
		stream = fopen( ("SomasData.txt"), ("w+") );
		while(nSel = pFile->Read(buf, sizeof(buf)-1))
		{
			buf[nSel]=NULL;
			fprintf( stream, ("%s"), buf );
		}
		fclose(stream);
		pFile->Close();
		session.Close();
	}
	catch(CInternetException* e)
	{
		e->Delete();
	}	
}

void CImportSomasDlg::Conversion(int nURLType)
{
	FILE* stream = fopen( ("SomasData.txt"), ("r") );
	if( stream == NULL ) return;
	_wsetlocale( LC_ALL, _T("Korean") );
	FILE* output = _wfopen( _T("SomasConv.txt"), _T("w+") );
	int i, j;
	char buf[500], out[500];
	CString strTmp;
	while( fgets(buf, 500, stream ) != NULL )
	{
		j = 0;
		memset(out,0,500);
		if(nURLType == 1)
		{
			strTmp = buf;
			if(strTmp.Find(_T("FIXED_TABLE"),0) > -1  )
				break;
		}
		
		for( i = 0; buf[i] != 0x0A; i++ )
		{
			if( i >= 499 ) break;
			if( buf[i] == '<' )
			{
				for( ; buf[i] != '>'; i++ );
			}
			if( buf[i] == '>' ) continue;
			out[j] = buf[i];
			j++;
		}
		if( j == 0 ) continue;
		strTmp = out;
		if( strTmp.IsEmpty() ) continue;
		if( strTmp.GetAt(0) == 13 ) continue;
		strTmp.Replace( 0x09, '@' );
		strTmp.Replace( _T("@"), _T("") );
		if( strTmp.IsEmpty() ) continue;
		strTmp.Replace( _T("&nbsp;"), _T("") );
		if(nURLType == 1)
		{
			if(strTmp.Find(_T("}"),0) > -1 || strTmp.Find(_T("{"),0) > -1 || strTmp.Find(_T(";"),0) > -1 )
				continue;
		}

		fwprintf(output, _T("%s\n"), strTmp );
	}
	fclose( stream );
	fclose( output );
}

BOOL CImportSomasDlg::ReadData(CString strSS, CString strDL, CTime dtDate)
{
	_wsetlocale( LC_ALL, _T("Korean") );
	FILE* stream = _wfopen( _T("SomasConv.txt"), _T("r+") );
	if( stream == NULL ) return FALSE;
	BOOL bRv = TRUE;
	WCHAR buf[500];
	int i, nHour;
	double dLoad;
	CString strTmp, strSQL,strSubs;
	CTime dtTomo;
	m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSubs );
	for( i = 0; i < 10; i++ )
	{//헤더부분임.
		if( fgetws( buf, 500, stream ) == NULL ) break; 
		if( i == 0 )
		{
			strTmp = buf;
			if( strTmp.Left(10) == "ORA-01000:" )//"ORA-01000: maximum open cursors exceeded"
			{
				FILE* error = _wfopen( _T("ServerDelay.txt"), _T("a+") );
				fwprintf( error, _T("%s\t%s\t%s\n"), strSubs, strDL,dtDate.Format( _T("%Y-%m-%d") ));
				fclose(error);
				Sleep(30*1000);
				bRv = FALSE;
			}
		}
	}
	while(bRv)
	{
		if( fgetws( buf, 500, stream ) == NULL ) break;
		strTmp = buf;
		if( strTmp.Find( _T("시부하(MW)전압(kV)시부하(MW)전압(kV)") ,0) > -1)  continue;
		else if( strTmp.Find( _T("시"), 0) > -1 )
		{
			strTmp.Delete(strTmp.GetLength()-2,2);
			nHour = _wtoi(strTmp);
		}
		else
			continue;
		fgetws( buf, 500, stream );//부하
		dLoad = _wtof(buf);
		// 강현구차장님 
		// Somas Data 추출시 0값 제외
		if ( dLoad <= 0 )
		{
			continue;
		}

		strSQL.Format(_T("insert into SOMAS_DL_TIME values ('%s','%s','%s',%d,%.1lf)")
			, strSubs, strDL, dtDate.Format("%Y%m%d"), nHour, dLoad);
		m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);
		//if(m_pSomas_Load)
		{
			strSQL.Format(_T("insert into Somas_Load values ('%s','%s','%s',%d,%.1lf)")
				, strSubs, strDL, dtDate.Format("%Y%m%d"), nHour, dLoad);
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasLog, strSQL);
		}
		

		if( nHour == 24 ) break;
	}

	fclose(stream);
	return bRv;
}

BOOL CImportSomasDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE) return TRUE;
		if(pMsg->wParam == VK_RETURN)
		{
			//OnBnClickedPtsDlgBtn1();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CImportSomasDlg::CreateSession()
{
	if (m_Session.m_spOpenRowset != NULL)
	{
		return TRUE;
		m_Session.m_spOpenRowset.Release();
	}

	CString strPath,strTmp;
	strPath.Format(_T("%s\\config\\config_pts.pas"),m_pData->MyPath());
	FILE* stream = _wfopen(strPath,_T("r"));
	if(stream == NULL)
	{
		AfxMessageBox(_T("PTS 연결정보가 없습니다."));
		return FALSE;
	}
	WCHAR ch[1000];
	memset(ch,0x00,1000);
	fgetws(ch,1000,stream);
	
	fclose(stream);

	CString strID,strPass;
	strTmp.Format(_T("%s"),ch);
	int nPos = strTmp.Find(_T(";"));
	strID = strTmp.Left(nPos);
	strTmp.Delete(0,nPos+1);
	nPos = strTmp.Find(_T(";"));
	strPass = strTmp.Left(nPos);

	CString strConnect;

	strConnect.Format(_T("Provider=MSDAORA.1;Password=%s;User ID=%s;Data Source=pts;"),strPass,strID);
//	strConnect.Format(_T("Provider=MSDAORA.1;Password=%s;User ID=%s;Data Source=dw;"),strPass,strID);
	
	GUID guid;
	DBPROPID propid;
	
	VARIANT VAR;
	BSTR bStr;
	
	if (m_Connect.OpenFromInitializationString(strConnect.AllocSysString(),TRUE) != S_OK)
	{
		
		AfxMessageBox(_T("Unable to connect to data source(PTS DB)"));
		//AfxMessageBox( strConnect );
		/*m_Connect.Close();
		CPTS_LOGIN_DLG dlg;

		if(dlg.DoModal() == IDOK)
		{
		CreateSession();
		return TRUE;
		}*/
		
		return FALSE;
	}
	else 
	{
		m_Connect.GetInitializationString(&bStr,TRUE);
		if (m_Session.Open(m_Connect) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source(PTS DB)"));
			return FALSE ;
		}
	}

	stream = _wfopen(strPath,_T("w+"));
	if(stream == NULL)
	{
		AfxMessageBox(_T("PTS 연결정보가 없습니다."));
		return FALSE;
	}
//	m_Connect.GetInitializationString(&bStr,TRUE);

	strTmp.Format(_T("%s") ,bStr);
	nPos = strTmp.Find(_T("User ID"));
	int nPos2 = strTmp.Find(_T("="),nPos);
	nPos = strTmp.Find(_T(";"),nPos2);
	strID = strTmp.Mid(nPos2+1,nPos - nPos2 -1);

	nPos = strTmp.Find(_T("Password"));
	nPos2 = strTmp.Find(_T("="),nPos);
	nPos = strTmp.Find(_T(";"),nPos2);
	strPass = strTmp.Mid(nPos2+1,nPos - nPos2 -1);

	strTmp.Format(_T("%s;%s;"),strID,strPass);

//	AfxMessageBox(strTmp);

	fwprintf(stream,strTmp);

	fclose(stream);


	return TRUE;
}

void	CImportSomasDlg::GetPTS_DGName()
{
	if (m_Session.m_spOpenRowset == NULL)
	{
		if(!CreateSession())
		{
			return;
		}
	}	
	int nCount = 0;
	
	int nPos = m_ctrCombo3.GetCurSel();

	if(nPos == -1)
	{
		AfxMessageBox(_T("변전소 선택이 없습니다."));
		return;
	}

	CString strSS;
	m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSS );
	if(strSS.IsEmpty())
	{
		AfxMessageBox(_T("변전소 선택이 없습니다."));
		return;
	}
	
	m_ctrList4.DeleteAllItems();

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind    = NULL;
	ULONG   ulFields;

	CString strSQL;

	m_ctrProgress.SetMarquee(TRUE, 10);
	m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSS );
	strSQL.Format(_T("select CDGUNAME,CDGUID from V_SYMTMASTER where ONM2 = '%s' Group by CDGUNAME,CDGUID"),strSS);
	FILE* error = _wfopen( _T("ptsname.txt"), _T("a+") );
	fwprintf( error, _T("%s\n"), strSQL);
	fclose(error);
	TRY
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l=0; l<ulFields; l++)
			rs.AddBindEntry(l+1, DBTYPE_WSTR, sizeof(TCHAR)*50, &pBind[l].szValue,NULL, &pBind[l].dwStatus);

		if (rs.Open(m_Session, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			m_ctrList4.InsertItem(m_ctrList4.GetItemCount(),pBind[0].szValue);	
			m_ctrList4.SetItemText(m_ctrList4.GetItemCount()-1,1,pBind[1].szValue);
			FILE* error = _wfopen( _T("ptsname.txt"), _T("a+") );
			fwprintf( error, _T("%s\n"), pBind[0].szValue);
			fclose(error);
			PumpMessages();
		}
		rs.Close();
		delete pBind;
		pBind = NULL;
	}
	CATCH(COLEDBException, e)
	{
		if (pBind != NULL)
			delete pBind;
		AfxMessageBox(_T("분산전원명 추출 오류"));
		e->ReportError();
	}
	END_CATCH

	m_ctrProgress.SetMarquee(FALSE, 10);
	m_ctrProgress.Invalidate(TRUE);
		
}

BOOL	CImportSomasDlg::GetPTSData()
{
	
	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("PTS 정보\r\n\r\n설정 중..."));

	_wsetlocale( LC_ALL, _T("Korean") );
	int nState, nCount = 0;
	CString strSS, strDL, strTmp;

	m_ctrProgress.SetMarquee(TRUE,10);
	CString strSQL;
	int nFrom, nTo;

	//// 추출 시간대 제외
	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT5,strTmp);
	nFrom = _wtoi(strTmp);
	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT6,strTmp);
	nTo = _wtoi(strTmp);
	strSQL.Format(_T("delete * from somas_dl_Time where HOUR <=  %d OR HOUR  > %d"),nFrom,nTo);
	
	m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);
	


	if(m_ctrBtnChk2.GetCheck())
	{
		if (m_Session.m_spOpenRowset == NULL)
		{
			if(!CreateSession())
			{
				return FALSE;
			}
		}	


		for(int  i = 0; i < m_ctrList4.GetItemCount(); i++ )
		{
			nState = m_ctrList4.GetItemState( i, LVIS_STATEIMAGEMASK );
			if( nState != 0x2000 ) continue;
			nCount++;
		}
		if( nCount == 0 )
		{
			//AfxMessageBox(_T("체크된 분산전원이 없습니다. 체크후 다시... "));
			//return FALSE;
		}


		CString strName,strFTime,strTTime,strID,strDLName;
		CTime timeF ,timeT;
		m_ctrDataF.GetTime(timeF);
		m_ctrDataT.GetTime(timeT);

		m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSS );

		strFTime = timeF.Format(_T("%Y%m%d"));
		strTTime = timeT.Format(_T("%Y%m%d"));

		CCommand<CManualAccessor> rs;
		struct MYBIND* pBind    = NULL;
		ULONG   ulFields;

		for(int  i = 0; i < m_ctrList4.GetItemCount(); i++ )
		{
			nState = m_ctrList4.GetItemState( i, LVIS_STATEIMAGEMASK );
			if( nState != 0x2000 ) continue;
			strName = m_ctrList4.GetItemText( i, 0 ) ;
			strID	= m_ctrList4.GetItemText( i, 1 ) ;
			strSQL.Format(_T("delete * from PTS")
				,strFTime,strTTime,strSS,strName);
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);

			strSQL.Format(_T("select TRADE_DATE,TIME,AMGO from OFFICEMGO where TRADE_DATE >= '%s' AND TRADE_DATE <= '%s'\
							 AND CDGUID =  = '%s'")
							 ,strFTime,strTTime,strID);

			/*FILE* error = _wfopen( _T("ptserr.txt"), _T("a+") );
			fwprintf( error, _T("%s\n"), strSQL);
			fclose(error);*/
			PumpMessages();

			TRY
			{
				ulFields = 5;
				pBind = new MYBIND[ulFields];
				rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
				for (ULONG l=0; l<ulFields; l++)
					rs.AddBindEntry(l+1, DBTYPE_WSTR, sizeof(TCHAR)*50, &pBind[l].szValue,NULL, &pBind[l].dwStatus);

				if (rs.Open(m_Session, strSQL) != S_OK)
					AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
				while (rs.MoveNext() == S_OK)
				{

					//if(m_pPts)
					{
						strSQL.Format( _T("insert into PTS values ('%s','%s','%s','%s','%s')")
							, strSS, strName, pBind[0].szValue,pBind[1].szValue, pBind[2].szValue );
						m_pData->SQLDBExcute(&m_pData->m_Session_SomasLog, strSQL);
					}

					strSQL.Format(_T("delete * from somas_dl_Time where EX_data = '%s' AND HOUR = %s"),pBind[0].szValue,pBind[2].szValue);
					
					m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);
				

					PumpMessages();
				}
				rs.Close();
				delete pBind;
				pBind = NULL;
			}
			CATCH(COLEDBException, e)
			{
				if (pBind != NULL)
					delete pBind;
				AfxMessageBox(_T("errer"));
				e->ReportError();
			}
			END_CATCH
		}

	}

	if(m_ctrBtnChk1.GetCheck())
	{
		////////////////////////////////////// 태양광 발전
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT1,strTmp);
		nFrom = _wtoi(strTmp);
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT2,strTmp);
		nTo = _wtoi(strTmp);
		strSQL.Format(_T("delete * from somas_dl_Time where HOUR >  %d AND HOUR  < %d"),nFrom,nTo);
		
		m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);
	
	

		/*	FILE* error = _wfopen( _T("ptserr.txt"), _T("a+") );
		fwprintf( error, _T("%s\n"), strSQL);
		fclose(error);*/
		PumpMessages();
	}
	if(m_ctrBtnChk3.GetCheck())
	{
		////////////////////////////////////// 기타 발전 1
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT10,strTmp);
		nFrom = _wtoi(strTmp);
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT11,strTmp);
		nTo = _wtoi(strTmp);
		if(nFrom < nTo)
		{
			strSQL.Format(_T("delete * from somas_dl_Time where HOUR <=  %d OR HOUR  > %d"),nFrom,nTo);
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);
		}

		////////////////////////////////////// 기타 발전 2
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT12,strTmp);
		nFrom = _wtoi(strTmp);
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT13,strTmp);
		nTo = _wtoi(strTmp);
		if(nFrom < nTo)
		{
			strSQL.Format(_T("delete * from somas_dl_Time where HOUR <=  %d OR HOUR  > %d"),nFrom,nTo);
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);
		}
		////////////////////////////////////// 기타 발전 3
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT14,strTmp);
		nFrom = _wtoi(strTmp);
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT15,strTmp);
		nTo = _wtoi(strTmp);
		if(nFrom < nTo)
		{
			strSQL.Format(_T("delete * from somas_dl_Time where HOUR <=  %d OR HOUR  > %d"),nFrom,nTo);
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);
		}
		////////////////////////////////////// 기타 발전 4
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT16,strTmp);
		nFrom = _wtoi(strTmp);
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT17,strTmp);
		nTo = _wtoi(strTmp);
		if(nFrom < nTo)
		{
			strSQL.Format(_T("delete * from somas_dl_Time where HOUR <=  %d OR HOUR  > %d"),nFrom,nTo);
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);
		}
	}

	

	m_ctrProgress.SetMarquee(FALSE,1000);
	m_ctrProgress.Invalidate(TRUE);

	//m_Session.Close();
	//m_Connect.Close();

	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("PTS 정보\r\n완료"));

	return TRUE;
}


void CImportSomasDlg::SetBadData_Load()
{
	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("\r\n부하 정보 최적화..."));

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	int nState;
	CString strName,strSQL,strTime,strSubs;
	int nMaxCount,nCutCount,nHour;
	double dMaxLoad = 0, dMinLoad = 0;

	m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSubs );

	m_ctrProgress.SetMarquee(TRUE,10);
	
	try
	{
		for(int  i = 0; i < m_ctrList1.GetItemCount(); i++ )
		{
			nState = m_ctrList1.GetItemState( i, LVIS_STATEIMAGEMASK );
			if( nState != 0x2000 ) continue;
			strName = m_ctrList1.GetItemText(i,0);

			
			ulFields = 1;
			pBind = new MYBIND[ulFields];
			rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
			for (ULONG l = 0; l < ulFields; l++)
				rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

			strSQL.Format(_T("select count(*) from somas_dl_Time where dl_Name = '%s' "), strName);
			if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
				AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
			while (rs.MoveNext() == S_OK)
			{
				if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
					wcscpy_s(pBind[0].szValue, _T(""));

				nMaxCount = _wtoi(pBind[0].szValue);

			}
			rs.Close();
			delete pBind;
			pBind = NULL;

			nCutCount = int( nMaxCount * 5 /100);

			ulFields = 1;
			pBind = new MYBIND[ulFields];
			rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
			for (ULONG l = 0; l < ulFields; l++)
				rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

			strSQL.Format(_T("select buha from somas_dl_Time where dl_Name = '%s' order by buha "), strName);
			if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
				AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
			while (rs.MoveNext() == S_OK)
			{
				if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
					wcscpy_s(pBind[0].szValue, _T(""));

				nCutCount--;
				if (nCutCount < 0)
				{
					
					dMinLoad = _wtof(pBind[0].szValue);
					PumpMessages();
					break;
				}

			}
			rs.Close();
			delete pBind;
			pBind = NULL;

			nCutCount = int( nMaxCount * 5 /100);

			ulFields = 1;
			pBind = new MYBIND[ulFields];
			rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
			for (ULONG l = 0; l < ulFields; l++)
				rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);
			
			strSQL.Format(_T("select buha from somas_dl_Time where dl_Name = '%s' order by buha DESC "), strName);
			if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
				AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
			while (rs.MoveNext() == S_OK)
			{
				if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
					wcscpy_s(pBind[0].szValue, _T(""));

				nCutCount--;
				if (nCutCount < 0)
				{
					dMaxLoad = _wtof(pBind[0].szValue);
					PumpMessages();
					break;
				}

			}
			rs.Close();
			delete pBind;
			pBind = NULL;

			
			strSQL.Format(_T("delete * from somas_dl_Time\
								 where dl_Name = '%s' AND (buha >= %lf OR buha <= %lf)")
								 , strName,dMaxLoad,dMinLoad );
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);

		
			PumpMessages();

		}
		
	
	}
	catch( COLEDBException* e ) 
	{
		//AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}
	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("부하정보 최적화\r\n\r\n완료"));

	m_ctrProgress.SetMarquee(FALSE,1000);
	m_ctrProgress.Invalidate(TRUE);
}



void CImportSomasDlg::UpdateList()
{
	int nState, nCount = 0;

	double dSum;
	int nMaxCount,nCutCount,nHour;
	double dMaxLoad = 0,dMinLoad = 0 ,dSumVol;

	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("\r\n\r\n최적 정보 계산 중..."));

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	COleVariant var;
	CString strSQL,strName,strTmp,strSubs;
	CString strDate,strBankNo;

	m_ctrProgress.SetMarquee(TRUE,10);

	m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSubs );

	if(m_ctrBtnChk4.GetCheck())
	{
		for(int  i = 0; i < m_ctrList1.GetItemCount(); i++ )
		{
			nState = m_ctrList1.GetItemState( i, LVIS_STATEIMAGEMASK );
			if( nState != 0x2000 ) continue;
			nCount++;
		}
		if( nCount == 0 )
		{
			AfxMessageBox(_T("체크된 배전선로가 없습니다. 체크후 다시... "));
			return;
		}


		CStringArray Array_DGName;
		CDoubleArray Array_Load;
		

		try
		{
			for(int  i = 0; i < m_ctrList1.GetItemCount(); i++ )
			{
				nState = m_ctrList1.GetItemState( i, LVIS_STATEIMAGEMASK );
				if( nState != 0x2000 ) continue;
				strName = m_ctrList1.GetItemText(i,0);
				Array_DGName.RemoveAll();

				PumpMessages();

				dSum= 0;
				dSumVol=0;


				m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, _T("delete * from temp"));

				ulFields = 3;
				pBind = new MYBIND[ulFields];
				rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
				for (ULONG l = 0; l < ulFields; l++)
					rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

				strSQL.Format(_T("select ex_date,hour,buha from somas_dl_time where dl_Name = '%s'"), strName);
				if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
					AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
				while (rs.MoveNext() == S_OK)
				{
					if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
						wcscpy_s(pBind[0].szValue, _T(""));

					PumpMessages();
					
					strDate = pBind[0].szValue;
					nHour = _wtoi(pBind[1].szValue);
					dSumVol = _wtof(pBind[2].szValue);

					strSQL.Format(_T("insert into temp values('%s',%d,%lf)"), strDate, nHour, dSumVol);

					m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);


				}
				rs.Close();
				delete pBind;
				pBind = NULL;

				ulFields = 2;
				pBind = new MYBIND[ulFields];
				rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
				for (ULONG l = 0; l < ulFields; l++)
					rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

				strSQL.Format(_T("select min(Load),max(Load) from temp"), strName);
				if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
					AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
				while (rs.MoveNext() == S_OK)
				{
					if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
						wcscpy_s(pBind[0].szValue, _T(""));

					dMinLoad = _wtof(pBind[0].szValue);
					dMaxLoad = _wtof(pBind[1].szValue);


				}
				rs.Close();
				delete pBind;
				pBind = NULL;

				dMinLoad += ( dMaxLoad - dMinLoad ) * 5 /100;


				dSumVol=0;
				dSum = 0;
				nMaxCount =0,nCutCount = 0;

				ulFields = 3;
				pBind = new MYBIND[ulFields];
				rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
				for (ULONG l = 0; l < ulFields; l++)
					rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

				strSQL.Format(_T("select date,hour,load from temp where load <= %lf "), dMinLoad);
				if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
					AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
				while (rs.MoveNext() == S_OK)
				{
					if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
						wcscpy_s(pBind[0].szValue, _T(""));

					PumpMessages();
					strDate = pBind[0].szValue;
					nHour = _wtoi(pBind[1].szValue);
					
					dSum += _wtof(pBind[2].szValue);

					nCutCount++;
				}

				rs.Close();
				delete pBind;
				pBind = NULL;
				
				dSum /= nCutCount;

				/////////////// list

				dSumVol /= nMaxCount;

				m_dOptimal = dSum;
				strTmp.Format(_T("%.3lf"),dSum);

				SetDlgItemText(IDC_IMPORT_SOMAS_DLG_STC17 ,strTmp);

				int nLow, nUp;
				m_ctrProgress.SetMarquee(FALSE,1000);
				m_ctrProgress.GetRange(nLow,nUp);
				m_ctrProgress.Invalidate(TRUE);
				PumpMessages();
			}


		}
		catch( COLEDBException* e ) 
		{
			//AfxMessageBox( e->m_pErrorInfo->m_strDescription );
			e->Delete();
		}
	}

	if(m_ctrBtnChk5.GetCheck())
	{
	//	AfxMessageBox(_T("전압 산정"));
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT9 ,strBankNo);

		try
		{
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, _T("delete * from temp"));

			ulFields = 3;
			pBind = new MYBIND[ulFields];
			rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
			for (ULONG l = 0; l < ulFields; l++)
				rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

			strSQL.Format(_T("select ex_time,hour,voltage from somas_dl_voltage where ss_code = '%s' AND MTRNO = %s"), strSubs, strBankNo);
			if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
				AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
			while (rs.MoveNext() == S_OK)
			{
				if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
					wcscpy_s(pBind[0].szValue, _T(""));

				PumpMessages();
				strDate = pBind[0].szValue;
				nHour = _wtoi(pBind[1].szValue);
				dSumVol = _wtof(pBind[2].szValue);

				strSQL.Format(_T("insert into temp values('%s',%d,%lf)"), strDate, nHour, dSumVol);

				m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);
			}

			rs.Close();
			delete pBind;
			pBind = NULL;

			ulFields = 2;
			pBind = new MYBIND[ulFields];
			rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
			for (ULONG l = 0; l < ulFields; l++)
				rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

			strSQL.Format(_T("select min(Load),max(Load) from temp"), strName);
			if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
				AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
			while (rs.MoveNext() == S_OK)
			{
				if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
					wcscpy_s(pBind[0].szValue, _T(""));

				dMinLoad = _wtof(pBind[0].szValue);
				dMaxLoad = _wtof(pBind[1].szValue);


			}
			rs.Close();
			delete pBind;
			pBind = NULL;

			dMinLoad += ( dMaxLoad - dMinLoad ) * 5 /100;
			dSumVol=0;
			dSum = 0;
			nMaxCount =0,nCutCount = 0;


			ulFields = 3;
			pBind = new MYBIND[ulFields];
			rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
			for (ULONG l = 0; l < ulFields; l++)
				rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

			strSQL.Format(_T("select date,hour,load from temp where load <= %lf "), dMinLoad);
			if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
				AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
			while (rs.MoveNext() == S_OK)
			{
				if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
					wcscpy_s(pBind[0].szValue, _T(""));

				PumpMessages();
				strDate = pBind[0].szValue;
				nHour = _wtoi(pBind[1].szValue);

				dSum += _wtof(pBind[2].szValue);

				nCutCount++;
			}

			rs.Close();
			delete pBind;
			pBind = NULL;

			dSum /= nCutCount;

			/////////////// list

	
			strTmp.Format(_T("%.3lf"),dSum);
			SetDlgItemText(IDC_IMPORT_SOMAS_DLG_STC18 ,strTmp);
		}
		catch( COLEDBException* e ) 
		{
			//AfxMessageBox( e->m_pErrorInfo->m_strDescription );
			e->Delete();
		}
	}
	
	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("산정 완료"));

	m_ctrProgress.SetMarquee(FALSE,1000);
	m_ctrProgress.Invalidate(TRUE);
}



void CImportSomasDlg::OnLvnItemchangedImportPwDlgList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	

	*pResult = 0;
}


void CImportSomasDlg::OnLvnItemchangingImportPwDlgList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	if(pNMLV->uNewState == 0x1000)
		return;

	int nState;
	for(int  i = 0; i < m_ctrList1.GetItemCount(); i++ )
	{
		nState = m_ctrList1.GetItemState( i, LVIS_STATEIMAGEMASK );
		m_ctrList1.SetItemState(i,0x1000,LVIS_STATEIMAGEMASK);
	}
	*pResult = 0;
}


void CImportSomasDlg::OnBnClickedImportSomasDlgChk1()
{
	if(m_ctrBtnChk1.GetCheck())
	{
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC1)->EnableWindow(TRUE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC2)->EnableWindow(TRUE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC3)->EnableWindow(TRUE);

		SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT1,_T("9"));
		SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT2,_T("18"));
	//	m_ctrList4.EnableWindow(FALSE);
	}
	else 
	{
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC1)->EnableWindow(FALSE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC2)->EnableWindow(FALSE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC3)->EnableWindow(FALSE);
		SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT1,_T(""));
		SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT2,_T(""));

	//	m_ctrList4.EnableWindow(TRUE);
	}
}

void CImportSomasDlg::OnBnClickedImportSomasDlgChk2()
{
	m_ctrList4.DeleteAllItems();
	
	if(m_ctrBtnChk2.GetCheck())
	{
		if(!CreateSession())
		{
			m_ctrBtnChk2.SetCheck(FALSE);
			return;
		}

		GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT4)->EnableWindow(TRUE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC4)->EnableWindow(TRUE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN4)->EnableWindow(TRUE);
		m_ctrList4.EnableWindow(TRUE);
		GetPTS_DGName();
	}
	else 
	{
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT4)->EnableWindow(FALSE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC4)->EnableWindow(FALSE);
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN4)->EnableWindow(FALSE);
		m_ctrList4.EnableWindow(FALSE);
	}
	
	
}


void CImportSomasDlg::OnBnClickedImportSomasDlgChk3()
{
	BOOL bEnable ;
	if(m_ctrBtnChk3.GetCheck())
	{
		bEnable = TRUE;
	}
	else 
	{
		bEnable = FALSE;
	}
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC5)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC6)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC7)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC8)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC9)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC10)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC11)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC12)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC13)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC14)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC15)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_STC16)->EnableWindow(bEnable);

	GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT10)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT11)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT12)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT13)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT14)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT15)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT16)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT17)->EnableWindow(bEnable);
	
}

void CImportSomasDlg::OnBnClickedImportSomasDlgChk4()
{
	if(m_ctrBtnChk4.GetCheck())
	{
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN3)->EnableWindow(TRUE);
		if(!m_ctrBtnChk5.GetCheck())
		{
			GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN2)->EnableWindow(TRUE);
		}
	}
	else 
	{
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN3)->EnableWindow(FALSE);
		if(!m_ctrBtnChk5.GetCheck())
		{
			GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN2)->EnableWindow(FALSE);
		}
	}
	
}


void CImportSomasDlg::OnBnClickedImportSomasDlgChk5()
{
	if(m_ctrBtnChk5.GetCheck())
	{
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN5)->EnableWindow(TRUE);
		if(!m_ctrBtnChk4.GetCheck())
		{
			GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN2)->EnableWindow(TRUE);
		}
	}
	else 
	{
		GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN5)->EnableWindow(FALSE);
		if(!m_ctrBtnChk4.GetCheck())
		{
			GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN2)->EnableWindow(FALSE);
		}
	}
}

void CImportSomasDlg::OnBnClickedImportSomasDlgBtn2()
{
	int nPos =  m_ctrCombo3.GetCurSel();
	
	CString strTmp,strSubs;
	if(nPos < 0 )
	{
		AfxMessageBox(_T("선택된 변전소가 없습니다."));
		return ;
	}
	m_ctrCombo3.GetLBText( nPos, strSubs );
	

	int nFrom, nTo;
	if(m_ctrBtnChk4.GetCheck())
	{
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT5,strTmp);
		nFrom = _wtoi(strTmp);
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT6,strTmp);
		nTo = _wtoi(strTmp);

		if( nFrom >= nTo)
		{
			AfxMessageBox(_T("Somas 부하량 추출의 시간 정보가 잘못 되었습니다."));
			return;
		}
	}
	if(m_ctrBtnChk5.GetCheck())
	{
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT7,strTmp);
		nFrom = _wtoi(strTmp);
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT8,strTmp);
		nTo = _wtoi(strTmp);

		if( nFrom >= nTo)
		{
			AfxMessageBox(_T("Somas 전압 추출의 시간 정보가 잘못 되었습니다."));
			return;
		}

		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT9,strTmp);
		if( _wtoi(strTmp) <= 0)
		{
			AfxMessageBox(_T("Somas 전압 추출의 Bank No 정보가 잘못 되었습니다."));
			return;
		}
	}

	if(m_ctrBtnChk1.GetCheck())
	{
		
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT1,strTmp);
		nFrom = _wtoi(strTmp);
		GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT2,strTmp);
		nTo = _wtoi(strTmp);

		if( nFrom >= nTo)
		{
			AfxMessageBox(_T("태양광 발전의 시간 정보가 잘못 되었습니다."));
			return;
		}
	}
	EnableWindow(FALSE);	
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT9)->EnableWindow(FALSE);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN2)->EnableWindow(FALSE);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN3)->EnableWindow(FALSE);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN5)->EnableWindow(FALSE);
	m_ctrBtnChk4.EnableWindow(FALSE);
	m_ctrBtnChk5.EnableWindow(FALSE);
	m_dOptimal = 0.;
#ifdef NDEBUG
	//////////// somas 추출
	if(m_ctrBtnChk4.GetCheck() )
	{
		if( !GetSomasData(0))
		{
			SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("Somas 부하량 취득 실패"));
			GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT9)->EnableWindow(TRUE);
			return;
		}

		//////////// 기본정보삭제 (태양광발전 설정 확인)
		if( !GetPTSData()  )
		{
			SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("PTS 취득 실패"));
			GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT9)->EnableWindow(TRUE);
			return;
		}
	}
	if(m_ctrBtnChk5.GetCheck() )
	{
	//	AfxMessageBox(_T("전압 추출"));
		if( !GetSomasData(1)  )
		{
			SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("Somas 전압 취득 실패"));
			GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT9)->EnableWindow(TRUE);
			return;
		}
	}
	
#endif
	//////////// bad data 정리
	if(m_ctrBtnChk4.GetCheck() )
		SetBadData_Load();
	if(m_ctrBtnChk5.GetCheck() )
	{
	//	AfxMessageBox(_T("전압 BAD"));
		SetBadData_Voltage();
	}
	
	//////////// 최소부하량 산정
	UpdateList();

	EnableWindow(TRUE);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_EDIT9)->EnableWindow(TRUE);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN2)->EnableWindow(TRUE);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN3)->EnableWindow(TRUE);
	GetDlgItem(IDC_IMPORT_SOMAS_DLG_BTN5)->EnableWindow(TRUE);
	m_ctrBtnChk4.EnableWindow(TRUE);
	m_ctrBtnChk5.EnableWindow(TRUE);
}
void CImportSomasDlg::OnBnClickedImportSomasDlgBtn5()
{
	CString strTmp ,strSubs;
	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_STC18,strTmp);
	double dVoltage = _wtof(strTmp);
	if(dVoltage < 0.00000001)
	{
		AfxMessageBox(_T("송출전압 정보가 잘못 되었습니다."));
		return;
	}
	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT9,strTmp);
	if( _wtoi(strTmp) <= 0)
	{
		AfxMessageBox(_T("Somas 전압 추출의 Bank No 정보가 잘못 되었습니다."));
		return;
	}
	m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSubs );

	int nNext ;
	//CInfo_Subs* pSubs;
	//CInfo_MTR* pMTR = NULL;
	//CDataAdministrator* pNewDM = CDataAdministrator::Instance();
	//CDataManager* pData = pNewDM->GetDataMng(3940);
	//for(int i = 0 ; i < pData->m_Info_SubsArr.GetSize() ; i++ )
	//{
	//	pSubs = pData->m_Info_SubsArr.GetAt(i);
	//	if(pSubs->GetName() != strSubs)
	//		continue;

	//	nNext = 0;
	//	while(pMTR = pSubs->GetNextMTR(nNext))
	//	{
	//		if(pMTR->GetBankNo() == _wtoi(strTmp))
	//			break;
	//	}
	//	break;
	//}
	//if(pMTR == NULL)
	//{
	//	AfxMessageBox(_T("해당 변전소 또는 M.tr 정보가 없습니다."));
	//	return ;
	//}

	//if(m_ctrBtnChk6.GetCheck())
	//{
	//	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT18,strTmp);
	//	if(dVoltage > _wtof(strTmp))
	//		dVoltage = _wtof(strTmp);
	//}

	//if(m_ctrBtnChk7.GetCheck())
	//{
	//	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT19,strTmp);
	//	if(dVoltage < _wtof(strTmp))
	//		dVoltage = _wtof(strTmp);
	//}

	//CString strMsg;
	//strMsg.Format(_T("M.tr 선간전압을 %g kV 로 설정합니다"),dVoltage);
	//if(AfxMessageBox(strMsg,MB_YESNO) == IDYES)
	//{

	//	pMTR->m_dOut_kV = dVoltage;
	//	//CDialogEx::OnOK();
	//}

}

void CImportSomasDlg::OnBnClickedImportSomasDlgBtn3()
{
	/////////////////////// 선로 적용
	if(m_dOptimal < 0.00000001)
	{
		AfxMessageBox(_T("최소 순수 부하량 정보가 잘못 되었습니다."));
		return;
	}

	CString strMsg,strDLName;
	int nState;
	for(int  i = 0; i < m_ctrList1.GetItemCount(); i++ )
	{
		nState = m_ctrList1.GetItemState( i, LVIS_STATEIMAGEMASK );
		if( nState != 0x2000 ) continue;
		strDLName = m_ctrList1.GetItemText(i, 0);
	}
	if( strDLName.IsEmpty() )
	{
		AfxMessageBox(_T("체크된 선로가 없습니다. 체크후 다시... "));
		return ;
	}

	//CInfo_CB* pInfo;
	//CDataAdministrator* pNewDM = CDataAdministrator::Instance();
	//CDataManager* pData = pNewDM->GetDataMng(3940);
	//pInfo = pData->GetCBInfo2Name(strDLName);
	//if(pInfo == NULL)
	//{
	//	AfxMessageBox(_T("해당 선로 정보가 없습니다."));
	//	return ;
	//}

	//strMsg.Format(_T("DL 부하량을 %g MW 로 설정합니다"),m_dOptimal);
	//if(AfxMessageBox(strMsg,MB_YESNO) == IDYES)
	//{

	//	pData->SetLoad_DL(pInfo->GetID(), m_dOptimal/22.9/sqrt(3.)*1000 );

	////CDialogEx::OnOK();
	//}

}

void CImportSomasDlg::OnBnClickedImportSomasDlgBtn1()
{
	if( m_ctrCombo3.GetCurSel() < 0 )
	{
		AfxMessageBox(_T("전력관리처정보를 선택해 주세요."));
		return;
	}
	CString strSQL, strSS, strSSID;

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSS );

	try
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);
		strSQL.Format(_T("select [s/s_code] from SS_Info where [s/s_name] = '%s' "), strSS);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strSSID = pBind[0].szValue;


		}
		rs.Close();
		delete pBind;
		pBind = NULL;
	}
	catch (COLEDBException* e)
	{
		//	AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}

	m_ctrProgress.SetMarquee(TRUE,10);

	int nSel;
	FILE* stream ;
	CString strURL;
	CInternetSession session( _T("My session") );
	CStdioFile* pFile;
	CTime dtDate = CTime::GetCurrentTime();
	char buf[1025];
	WORD mark = 0xFEFF,rmark;
	try
	{
		strURL.Format( _T("http://100.1.21.33/emx/OV_EMX_400_R01_AO.do?ofc_cd_1=%s&ofc_cd_2=%s&ofc_cd_3=%s&startDate1=%s&flag=D"),
			strSSID.Left(4), strSSID.Mid(4,4),strSSID.Right(4),dtDate.Format("%Y-%m-%d"));
		pFile = session.OpenURL(strURL);
		stream = fopen( "DL_Info.txt", "w+" );
		//fwrite(&mark, sizeof(WORD), 1, stream);  /////////////////////////////추가
		while(nSel = pFile->Read(buf, sizeof(buf)-1))
		{
			buf[nSel]=NULL;
			fprintf(stream, ("%s"), buf);
		}
		fclose(stream);
		pFile->Close();
		session.Close();
	}
	catch(CInternetException* e)
	{
		e->Delete();
	}

	stream = fopen( "DL_Info.txt", "r+" );

	if( stream == NULL )
	{
		AfxMessageBox(_T("Somas 기본정보를 가져오기 실패하였습니다. 접속가능한 후 다시..." ));
		return;
	}
	//기존 디비 삭제한다.

	m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, _T("delete * from Office1"));
	m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, _T("delete * from Office2"));
	m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, _T("delete * from SS_INFO"));
	strSQL.Format(_T("delete * from DL_ID where [code] = '%s' "), strSSID);
	m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);


	int  n1, n2, nLoc = 0, nPos = 0 ;
	char ch, buffer[300];
	CString strTmp,strCode,strName,strDL;

	fread(&rmark, sizeof(WORD), 1, stream);
	while( feof(stream) == 0 )
	{
		ch = fgetc(stream);
		if( ch == '\n' )
		{
			buffer[nPos] = NULL;
			strTmp = buffer;
			if( strTmp.Left(7) == _T("ofc_cd_") )
			{
				nSel = strTmp.GetAt( 7 ) - '0';
				n1 = strTmp.Find( _T("]='"), 8 );
				n2 = strTmp.Find( _T("';"), 8 );
				strCode = strTmp.Mid( n1+3, n2-n1-3 );
			}
			else if( strTmp.Left(7) == _T("ofc_nm_") )
			{
				n1 = strTmp.Find( _T("]='"), 8 );
				n2 = strTmp.Find( _T("';"), 8 );
				strName = strTmp.Mid( n1+3, n2-n1-3 );
				//
				if( nSel != 3 )
				{
					strSQL.Format( _T("INSERT INTO OFFICE%d VALUES('%s','%s')"), nSel, strCode, strName);
				}
				else
				{
					strSQL.Format( _T("INSERT INTO SS_INFO VALUES('%s','%s')"), strCode, strName);
				}
				PumpMessages();

				if (!strCode.IsEmpty())
					m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);

			
			}
			nPos = 0;
		}
		else 
		{
			if( nPos > 298 ) continue;
			buffer[nPos] = ch;
			nPos++;
		}
	}

	fseek( stream, 0, SEEK_SET );
	nLoc = 0, nPos = 0 ;
	strCode.Format( _T("javascript:searchDetail('%s',") , strSSID.Right(4));
	while( feof(stream) == 0 )
	{
		ch = fgetc(stream);
		if( nLoc == 1)
		{
			if(ch == ')')
			{
				buffer[nPos] = NULL;
				buffer[nPos-1] = NULL;
				strDL = buffer;
				nPos =0;
			}
		}
		else if( nLoc == 2)
		{
			if(ch == '<')
			{
				buffer[nPos] = NULL;
				strName = buffer;
				nPos = nLoc = 0;
				strSQL.Format( _T("INSERT INTO DL_ID VALUES('%s','%s','%s')"),strSSID,strDL,strName);
				
				m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);
				
				PumpMessages();
			}	
		}
		if(nLoc == 1 && ch == ' ')
		{
			nLoc = 2;
			nPos = 0;
		}
		else if( ch == ' ' || ch == '\n' || ch == '"' )
		{
			buffer[nPos] = NULL;
			strTmp = buffer;
			nPos = 0;
		}
		else if( strTmp == strCode && nLoc == 0)
		{
			nLoc=1;
		}
		else 
		{
			buffer[nPos] = ch;
			nPos++;
		}
	}
	m_ctrProgress.SetMarquee(FALSE,10);
	m_ctrProgress.Invalidate();
	fclose(stream);
	m_ctrCombo1.ResetContent();
	m_ctrCombo2.ResetContent();
	m_ctrCombo3.ResetContent();
	m_ctrList1.DeleteAllItems();
	m_ctrList4.DeleteAllItems();
	InitData();
	AfxMessageBox(_T("완료"));
}

void CImportSomasDlg::OnBnClickedImportSomasDlgBtn4()
{

	if (m_Session.m_spOpenRowset == NULL)
	{
		if(!CreateSession())
		{
			return;
		}
	}	
	int nCount = 0;

	CString strValue;
	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT4,strValue);
	strValue.Trim();
	if(strValue.IsEmpty())
		return;

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind    = NULL;
	ULONG   ulFields;

	CString strSQL,strMsg,strTmp,strName;

	m_ctrProgress.SetMarquee(TRUE, 10);
	
	strSQL.Format(_T("select CDGUNAME,CDGUID from V_SYMTMASTER where CDGUNAME Like '%%%s%%' Group by CDGUNAME,CDGUID"),strValue);
	/*FILE* error = _wfopen( _T("ptsname.txt"), _T("a+") );
	fwprintf( error, _T("%s\n"), strSQL);
	fclose(error);*/
	TRY
	{
		ulFields = 2;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l=0; l<ulFields; l++)
			rs.AddBindEntry(l+1, DBTYPE_WSTR, sizeof(TCHAR)*50, &pBind[l].szValue,NULL, &pBind[l].dwStatus);

		if (rs.Open(m_Session, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			strTmp.Format(_T("%s\n"),pBind[0].szValue);
			strName += strTmp;
			
			PumpMessages();
		}
		rs.Close();
		delete pBind;
		pBind = NULL;
	}
	CATCH(COLEDBException, e)
	{
		if (pBind != NULL)
			delete pBind;
		AfxMessageBox(_T("분산전원명 추출 오류"));
		e->ReportError();
	}
	END_CATCH

	if(!strName.IsEmpty())
	{
		strMsg.Format(_T("다음 분산전원이 조회되었습니다.\n%s\n추가 하시겠습니까?"),strName);
		if(AfxMessageBox(strMsg,MB_YESNO) == IDYES)
		{
			strSQL.Format(_T("select CDGUNAME,CDGUID from V_SYMTMASTER where CDGUNAME Like '%%%s%%' Group by CDGUNAME,CDGUID"),strValue);
	
			TRY
			{
				ulFields = 2;
				pBind = new MYBIND[ulFields];
				rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
				for (ULONG l=0; l<ulFields; l++)
					rs.AddBindEntry(l+1, DBTYPE_WSTR, sizeof(TCHAR)*50, &pBind[l].szValue,NULL, &pBind[l].dwStatus);

				if (rs.Open(m_Session, strSQL) != S_OK)
					AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
				while (rs.MoveNext() == S_OK)
				{
					m_ctrList4.InsertItem(m_ctrList4.GetItemCount(),pBind[0].szValue);
					m_ctrList4.SetItemText(m_ctrList4.GetItemCount()-1,1,pBind[1].szValue);
					PumpMessages();
				}
				rs.Close();
				delete pBind;
				pBind = NULL;
			}
			CATCH(COLEDBException, e)
			{
				if (pBind != NULL)
					delete pBind;
				AfxMessageBox(_T("분산전원명 추출 오류"));
				e->ReportError();
			}
			END_CATCH
		}
	}

	m_ctrProgress.SetMarquee(FALSE, 10);
	m_ctrProgress.Invalidate(TRUE);
}

BOOL CImportSomasDlg::ReadData_Voltage(CString strSS, CTime dtDate)
{
	_wsetlocale( LC_ALL, _T("Korean") );
	FILE* stream = _wfopen( _T("SomasConv.txt"), _T("r+") );
	if( stream == NULL ) return FALSE;
	BOOL bRv = TRUE;
	WCHAR buf[500];
	int i, nHour,nMtrNo;
	double dLoad;
	CString strTmp, strSQL,strSubs,strBankNo;
	CTime dtTomo;
	m_ctrCombo3.GetLBText( m_ctrCombo3.GetCurSel(), strSubs );
	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT9 ,strBankNo);

	// 김영선
	int nPos = -1;

	for( i = 0; i < 10; i++ )
	{//헤더부분임.
		if( fgetws( buf, 500, stream ) == NULL ) break; 
		if( i == 0 )
		{
			strTmp = buf;
			if( strTmp.Left(10) == "ORA-01000:" )//"ORA-01000: maximum open cursors exceeded"
			{
				FILE* error = _wfopen( _T("ServerDelay.txt"), _T("a+") );
				fwprintf( error, _T("%s\t%s\n"), strSubs, dtDate.Format( _T("%Y-%m-%d") ));
				fclose(error);
				Sleep(30*1000);
				bRv = FALSE;
			}
		}
	}
	while(bRv)
	{
		if( fgetws( buf, 500, stream ) == NULL ) break;
		strTmp = buf;
		if( strTmp.Find( _T("#"), 0) != 0 )
			continue;
		//////////////////////////////////////////////////////////////////////////
		nPos = strTmp.Find( _T(" ") ) - 1;
		nMtrNo = _wtoi(strTmp.Mid(1,nPos));
		if(_wtoi(strBankNo) != nMtrNo )
			continue;

		nHour = 1;
		while(nHour < 25)
		{
			fgetws( buf, 500, stream );
			dLoad = _wtof(buf);
			// 강현구차장님 
			// Somas Data 추출시 0값 제외
			if ( dLoad <= 0 )
			{
				nHour++;
				continue;
			}
		
			strSQL.Format(_T("insert into SOMAS_DL_VOLTAGE values ('%s',%d,'%s',%d,%.1lf)")
				, strSubs, nMtrNo, dtDate.Format("%Y%m%d"), nHour, dLoad);
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);


			strSQL.Format(_T("insert into Somas_Voltage values ('%s',%d,'%s',%d,%.1lf)")
				, strSubs, nMtrNo, dtDate.Format("%Y%m%d"), nHour, dLoad);
			m_pData->SQLDBExcute(&m_pData->m_Session_SomasLog, strSQL);

			nHour++;
		}
	}

	fclose(stream);
	return bRv;
}

void CImportSomasDlg::SetBadData_Voltage()
{
	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("\r\n전압 정보 최적화..."));

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	int nState;
	CString strName,strSQL,strTime,strSubs,strTemp;
	int nMaxCount,nCutCount,nHour;
	double dMaxLoad , dMinLoad ;
	int nPos =  m_ctrCombo3.GetCurSel();

	
	if(nPos < 0 )
	{
		AfxMessageBox(_T("선택된 변전소가 없습니다."));
		return ;
	}
	m_ctrCombo3.GetLBText( nPos, strSubs );

	CString strBankID,strBankNo;
	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT9 ,strBankNo);
	int nBankNo = _wtoi(strBankNo);

	//// 추출 시간대 제외
	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT7,strTemp);
	int nFrom = _wtoi(strTemp);
	GetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT8,strTemp);
	int nTo = _wtoi(strTemp);
	strSQL.Format(_T("delete * from somas_dl_voltage where HOUR <=  %d OR HOUR  > %d"),nFrom,nTo);
	m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);

	try
	{
		/*for(int  i = 0; i < m_ctrList1.GetItemCount(); i++ )
		{
		nState = m_ctrList1.GetItemState( i, LVIS_STATEIMAGEMASK );
		if( nState != 0x2000 ) continue;
		strName = m_ctrList1.GetItemText(i,0);*/



		/*strTemp.Format(_T("%d"),nBankNo);
		if(strBankID.Find(strTemp,0) > -1)
		continue;
		strTemp.Format(_T("[%d]"),nBankNo);
		strBankID += strTemp;*/

		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select count(*) from somas_dl_Voltage where ss_code = '%s' AND MTRNO = %d "), strSubs, nBankNo);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nMaxCount = _wtoi(pBind[0].szValue);

		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		nCutCount = int( nMaxCount * 5 /100);

		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select Voltage from somas_dl_Voltage where  ss_code = '%s' AND MTRNO = %d order by Voltage"), strSubs, nBankNo);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nCutCount--;
			if (nCutCount < 0)
			{

				dMinLoad = _wtof(pBind[0].szValue);
				PumpMessages();
				break;
			}

		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		nCutCount = int( nMaxCount * 5 /100);

		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue, NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select Voltage from somas_dl_Voltage where ss_code = '%s' AND MTRNO = %d  order by Voltage DESC "), strSubs, nBankNo);
		if (rs.Open(m_pData->m_Session_SomasInfo, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nCutCount--;
			if (nCutCount < 0)
			{

				dMaxLoad = _wtof(pBind[0].szValue);
				PumpMessages();
				break;
			}

		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		strSQL.Format(_T("delete * from somas_dl_Voltage\
								 where ss_code = '%s' AND MTRNO = %d AND (Voltage >= %lf OR Voltage <= %lf)")
			, strSubs, nBankNo, dMaxLoad, dMinLoad);
		m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);

		dMinLoad = 22.9 * 4 / 100;

		strSQL.Format(_T("delete * from somas_dl_Voltage\
								 where ss_code = '%s' AND MTRNO = %d AND (Voltage >= %lf OR Voltage <= %lf)")
			, strSubs, nBankNo, 22.9 + dMinLoad, 22.9 - dMinLoad);
		m_pData->SQLDBExcute(&m_pData->m_Session_SomasInfo, strSQL);

	}
	catch( COLEDBException* e ) 
	{
		//AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}
	SetDlgItemText(IDC_IMPORT_SOMAS_DLG_EDIT3 ,_T("전압정보 최적화\r\n\r\n완료"));
}





