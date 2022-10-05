// CRelaySetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CRelaySetDlg.h"
#include "afxdialogex.h"
#include "dbexcept.h"
#include "../DataManager/CDataManager.h"

// CRelaySetDlg 대화 상자

IMPLEMENT_DYNAMIC(CRelaySetDlg, CDialogEx)

CRelaySetDlg::CRelaySetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RELAYSET_DLG, pParent)
{
	m_nMode = RELAY_EDIT_MODE_ADD;
}

CRelaySetDlg::~CRelaySetDlg()
{
}

void CRelaySetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RELAYSET_DLG_COMBO1, m_ctrCombo);
	DDX_Control(pDX, IDC_RELAYSET_DLG_COMBO2, m_ctrCombo_Curve);
}


BEGIN_MESSAGE_MAP(CRelaySetDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RELAYSET_DLG_BTN1, &CRelaySetDlg::OnBnClickedRelaysetDlgBtn1)
	ON_CBN_SELCHANGE(IDC_RELAYSET_DLG_COMBO1, &CRelaySetDlg::OnCbnSelchangeRelaysetDlgCombo1)
	ON_BN_CLICKED(IDC_RELAYSET_DLG_BTN2, &CRelaySetDlg::OnBnClickedRelaysetDlgBtn2)
END_MESSAGE_MAP()


// CRelaySetDlg 메시지 처리기


BOOL CRelaySetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	m_ctrCombo.AddString(_T("디지탈"));
	m_ctrCombo.AddString(_T("아날로그"));


	InitData_Curve();
	if (m_nMode == RELAY_EDIT_MODE_ADD)
	{
		SetDlgItemText(IDC_RELAYSET_DLG_EDIT1, m_strName);
		SetDlgItemText(IDC_RELAYSET_DLG_EDIT2, m_strManuf);

		m_ctrCombo.SetCurSel(0);
	}
	else
	{
		SetDlgItemText(IDC_RELAYSET_DLG_EDIT1, m_strName);
		SetDlgItemText(IDC_RELAYSET_DLG_EDIT2, m_strManuf);

		

		m_ctrCombo.SetCurSel(m_nType);
		OnCbnSelchangeRelaysetDlgCombo1();

		///////////////// 커브는 kacim으로 확인 하자..
		
		m_ctrCombo_Curve.SetCurSel(m_nCurve - 1);


		if (m_nType == 0)
			Update_Data_D();
	}

	m_ctrCombo.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CRelaySetDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		


		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CRelaySetDlg::OnBnClickedRelaysetDlgBtn1()
{
	if (m_nMode == RELAY_EDIT_MODE_ADD)
	{
		if (!Check2Name())
			return;
	}
	Insert_Data_D();
	CDialogEx::OnOK();;
}

void CRelaySetDlg::OnBnClickedRelaysetDlgBtn2()
{
	CDialogEx::OnOK();
}


void CRelaySetDlg::OnCbnSelchangeRelaysetDlgCombo1()
{
	int nSel = m_ctrCombo.GetCurSel();


	if (nSel == 0)
	{
		GetDlgItem(IDC_RELAYSET_DLG_EDIT15)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT16)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT17)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT18)->ShowWindow(SW_HIDE);


		GetDlgItem(IDC_RELAYSET_DLG_EDIT3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT10)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT11)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT12)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT13)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT14)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RELAYSET_STC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC10)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_STC11)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_RELAYSET_DLG_EDIT15)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT16)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT17)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT18)->ShowWindow(SW_SHOW);


		GetDlgItem(IDC_RELAYSET_DLG_EDIT3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT9)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT10)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT11)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT12)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT13)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_DLG_EDIT14)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RELAYSET_STC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC9)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC10)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RELAYSET_STC11)->ShowWindow(SW_HIDE);
	}
}


void CRelaySetDlg::Update_Data_D()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL;

	CString strData[3];
	double dValue[3];
	
	//////////////////////////////////////////////////////////////// OCR 한시
	strSQL.Format(_T("SELECT tap_start,tap_end,tap_step from ADMS_n_relay_D_tap \
						where machine_id = %d and ocr_ocgr_sep = 0 and fd_sep = 0"),m_nID);

	TRY
	{
		ulFields = 3;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(pDataMng->m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		if (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			dValue[0] = _wtof(pBind[0].szValue);
			dValue[1] = _wtof(pBind[1].szValue);
			dValue[2] = _wtof(pBind[2].szValue);

			strData[0].Format(_T("%g"), dValue[0]);
			strData[1].Format(_T("%g"), dValue[1]);
			strData[2].Format(_T("%g"), dValue[2]);
			
			SetDlgItemText(IDC_RELAYSET_DLG_EDIT3, strData[0]);
			SetDlgItemText(IDC_RELAYSET_DLG_EDIT4, strData[1]);
			SetDlgItemText(IDC_RELAYSET_DLG_EDIT5, strData[2]);

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

	//////////////////////////////////////////////////////////////// OCR 순시
	strSQL.Format(_T("SELECT tap_start,tap_end,tap_step from ADMS_n_relay_D_tap \
						where machine_id = %d and ocr_ocgr_sep = 0 and fd_sep = 1"), m_nID);

	TRY
	{
		ulFields = 3;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(pDataMng->m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		if (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			dValue[0] = _wtof(pBind[0].szValue);
			dValue[1] = _wtof(pBind[1].szValue);
			dValue[2] = _wtof(pBind[2].szValue);

			strData[0].Format(_T("%g"), dValue[0]);
			strData[1].Format(_T("%g"), dValue[1]);
			strData[2].Format(_T("%g"), dValue[2]);

			SetDlgItemText(IDC_RELAYSET_DLG_EDIT6, strData[0]);
			SetDlgItemText(IDC_RELAYSET_DLG_EDIT7, strData[1]);
			SetDlgItemText(IDC_RELAYSET_DLG_EDIT8, strData[2]);

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


	//////////////////////////////////////////////////////////////// OCGR 한시
	strSQL.Format(_T("SELECT tap_start,tap_end,tap_step from ADMS_n_relay_D_tap \
						where machine_id = %d and ocr_ocgr_sep = 1 and fd_sep = 0"), m_nID);

	TRY
	{
		ulFields = 3;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(pDataMng->m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		if (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			dValue[0] = _wtof(pBind[0].szValue);
			dValue[1] = _wtof(pBind[1].szValue);
			dValue[2] = _wtof(pBind[2].szValue);

			strData[0].Format(_T("%g"), dValue[0]);
			strData[1].Format(_T("%g"), dValue[1]);
			strData[2].Format(_T("%g"), dValue[2]);

			SetDlgItemText(IDC_RELAYSET_DLG_EDIT9, strData[0]);
			SetDlgItemText(IDC_RELAYSET_DLG_EDIT10, strData[1]);
			SetDlgItemText(IDC_RELAYSET_DLG_EDIT11, strData[2]);

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



	//////////////////////////////////////////////////////////////// OCGR 순시
	strSQL.Format(_T("SELECT tap_start,tap_end,tap_step from ADMS_n_relay_D_tap \
						where machine_id = %d and ocr_ocgr_sep = 1 and fd_sep = 1"), m_nID);

	TRY
	{
		ulFields = 3;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(pDataMng->m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		if (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			dValue[0] = _wtof(pBind[0].szValue);
			dValue[1] = _wtof(pBind[1].szValue);
			dValue[2] = _wtof(pBind[2].szValue);

			strData[0].Format(_T("%g"), dValue[0]);
			strData[1].Format(_T("%g"), dValue[1]);
			strData[2].Format(_T("%g"), dValue[2]);

			SetDlgItemText(IDC_RELAYSET_DLG_EDIT12, strData[0]);
			SetDlgItemText(IDC_RELAYSET_DLG_EDIT13, strData[1]);
			SetDlgItemText(IDC_RELAYSET_DLG_EDIT14, strData[2]);

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

int CRelaySetDlg::GetMaxID()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL;

	int nMaxID = 0;
	//////////////////////////////////////////////////////////////// OCR 한시
	strSQL.Format(_T("SELECT MAX(machine_id) from adms_n_machine_code"));

	TRY
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(pDataMng->m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		if (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nMaxID = _wtoi(pBind[0].szValue);

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

	nMaxID++;
	return nMaxID;
}


BOOL CRelaySetDlg::Check2Name()
{
	CString strName;
	GetDlgItemText(IDC_RELAYSET_DLG_EDIT1, strName);

	strName.Trim();

	if (strName.IsEmpty())
	{
		AfxMessageBox(_T("계전기명이 없습니다."));
		return FALSE;
	}
		
	CDataManager* pDataMng = CDataManager::Instance();

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL;

	BOOL bFind = FALSE;
	//////////////////////////////////////////////////////////////// OCR 한시
	strSQL.Format(_T("SELECT machine_id from adms_n_machine_code \
											 where machine_name = '%s'"), strName);

	TRY
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(pDataMng->m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		if (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			bFind = TRUE;

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

	if (bFind)
	{
		AfxMessageBox(_T("중복된 계전기명 입니다."));
		return FALSE;
	}

	return TRUE;
}

void CRelaySetDlg::Insert_Data_D()
{
	CString strName;
	CString strManuf;
	int		nType;
	int		nCurve;

	CString strData[3];
	double dOCR_F[3];
	double dOCR_D[3];
	double dOCGR_F[3];
	double dOCGR_D[3];

	GetDlgItemText(IDC_RELAYSET_DLG_EDIT1, strName);
	GetDlgItemText(IDC_RELAYSET_DLG_EDIT2, strManuf);
	nType = m_ctrCombo.GetCurSel();
	nCurve = m_ctrCombo_Curve.GetCurSel()+1;

	GetDlgItemText(IDC_RELAYSET_DLG_EDIT3, strData[0]);
	GetDlgItemText(IDC_RELAYSET_DLG_EDIT4, strData[1]);
	GetDlgItemText(IDC_RELAYSET_DLG_EDIT5, strData[2]);
	dOCR_F[0] = _wtof(strData[0]);
	dOCR_F[1] = _wtof(strData[1]);
	dOCR_F[2] = _wtof(strData[2]);

	GetDlgItemText(IDC_RELAYSET_DLG_EDIT6, strData[0]);
	GetDlgItemText(IDC_RELAYSET_DLG_EDIT7, strData[1]);
	GetDlgItemText(IDC_RELAYSET_DLG_EDIT8, strData[2]);
	dOCR_D[0] = _wtof(strData[0]);
	dOCR_D[1] = _wtof(strData[1]);
	dOCR_D[2] = _wtof(strData[2]);

	GetDlgItemText(IDC_RELAYSET_DLG_EDIT9, strData[0]);
	GetDlgItemText(IDC_RELAYSET_DLG_EDIT10, strData[1]);
	GetDlgItemText(IDC_RELAYSET_DLG_EDIT11, strData[2]);
	dOCGR_F[0] = _wtof(strData[0]);
	dOCGR_F[1] = _wtof(strData[1]);
	dOCGR_F[2] = _wtof(strData[2]);

	GetDlgItemText(IDC_RELAYSET_DLG_EDIT12, strData[0]);
	GetDlgItemText(IDC_RELAYSET_DLG_EDIT13, strData[1]);
	GetDlgItemText(IDC_RELAYSET_DLG_EDIT14, strData[2]);
	dOCGR_D[0] = _wtof(strData[0]);
	dOCGR_D[1] = _wtof(strData[1]);
	dOCGR_D[2] = _wtof(strData[2]);
	//////////////////

	CString strSQL;
	CDataManager* pDataMng = CDataManager::Instance();

	if (m_nMode == RELAY_EDIT_MODE_ADD)
	{
		int nMaxID = GetMaxID();
		//////////////////////////////////////////////////////////////// machine
		strSQL.Format(_T("insert into adms_n_machine_code \
						values( %d , '%s' , '%s', %d)"), nMaxID, strName, strManuf, nCurve);

		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		//////////////////////////////////////////////////////////////// machine type
		strSQL.Format(_T("insert into adms_n_relay_Type \
						values( %d, %d, 0, 0)"), nMaxID, nType);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		strSQL.Format(_T("insert into adms_n_relay_Type \
						values( %d, %d, 0, 1)"), nMaxID, nType);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		strSQL.Format(_T("insert into adms_n_relay_Type \
						values( %d, %d, 1, 0)"), nMaxID, nType);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		strSQL.Format(_T("insert into adms_n_relay_Type \
						values( %d, %d, 1, 1)"), nMaxID, nType);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		//////////////////////////////////////////////////////////////// 디지탈 탭 정보
		strSQL.Format(_T("insert into ADMS_n_relay_D_tap \
						values( %d, 0, 0, %lf,%lf,%lf)"), nMaxID, dOCR_F[0], dOCR_F[1], dOCR_F[2]);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		strSQL.Format(_T("insert into ADMS_n_relay_D_tap \
						values( %d, 0, 1, %lf,%lf,%lf)"), nMaxID, dOCR_D[0], dOCR_D[1], dOCR_D[2]);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		strSQL.Format(_T("insert into ADMS_n_relay_D_tap \
						values( %d, 1, 0, %lf,%lf,%lf)"), nMaxID, dOCGR_F[0], dOCGR_F[1], dOCGR_F[2]);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		strSQL.Format(_T("insert into ADMS_n_relay_D_tap \
						values( %d, 1, 1, %lf,%lf,%lf)"), nMaxID, dOCGR_D[0], dOCGR_D[1], dOCGR_D[2]);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);
		
	}
	else
	{
		//////////////////////////////////////////////////////////////// machine
		strSQL.Format(_T("Update adms_n_machine_code \
						set machine_name = '%s' , machine_manuf = '%s', machine_ii_TCCSET = %d \
						where machine_id = %d"),  strName, strManuf, nCurve, m_nID);

		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		//////////////////////////////////////////////////////////////// 디지탈 탭 정보
		strSQL.Format(_T("Update ADMS_n_relay_D_tap \
						set tap_start = %g , tap_end = %g, tap_step = %g \
						where machine_id = %d and ocr_ocgr_sep = 0 and fd_sep = 0 ")
						, dOCR_F[0], dOCR_F[1], dOCR_F[2], m_nID);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		strSQL.Format(_T("Update ADMS_n_relay_D_tap \
						set tap_start = %g , tap_end = %g, tap_step = %g \
						where machine_id = %d and ocr_ocgr_sep = 0 and fd_sep = 1 ")
			, dOCR_D[0], dOCR_D[1], dOCR_D[2], m_nID);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		strSQL.Format(_T("Update ADMS_n_relay_D_tap \
						set tap_start = %g , tap_end = %g, tap_step = %g \
						where machine_id = %d and ocr_ocgr_sep = 1 and fd_sep = 0 ")
			, dOCGR_F[0], dOCGR_F[1], dOCGR_F[2], m_nID);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);

		strSQL.Format(_T("Update ADMS_n_relay_D_tap \
						set tap_start = %g , tap_end = %g, tap_step = %g \
						where machine_id = %d and ocr_ocgr_sep = 1 and fd_sep = 1 ")
			, dOCGR_D[0], dOCGR_D[1], dOCGR_D[2], m_nID);
		pDataMng->SQLDBExcute(&pDataMng->m_Session_OD, strSQL);
	}
	

}

void CRelaySetDlg::InitData_Curve()
{
	m_ctrCombo_Curve.ResetContent();

	int nCount = theAppDataMng->GetTableRealCount(_T("tccset_sta"));

	CString strName;
	for (int i = 1; i <= nCount; i++)
	{

		strName = GETSTRING(_T("tccset_sta"), _T("tccset_nm"), i);

		m_ctrCombo_Curve.AddString(strName);
		m_ctrCombo_Curve.SetItemData(i - 1, (DWORD_PTR)i);
	}
}