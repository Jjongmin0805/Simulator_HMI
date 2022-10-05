// TCRcRegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TCRcRegDlg.h"
#include "math.h"
#include "dbexcept.h"
#include "../DataManager/CDataManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTCRcRegDlg dialog


CTCRcRegDlg::CTCRcRegDlg(CSession* pDB, CWnd* pParent /*=NULL*/)
	: CDialog(CTCRcRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTCRcRegDlg)
	m_nType = 0;
	m_bSecond = 0;
	m_fA = 0.0f;
	m_fB = 0.0f;
	m_fC = 0.0f;
	m_fD = 0.0f;
	m_fE = 0.0f;
	m_fF = 0.0f;
	m_fPU1 = 0.0f;
	m_fPU2 = 0.0f;
	//}}AFX_DATA_INIT
	m_pDB = pDB;
	m_pCurve = NULL;
}


void CTCRcRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCRcRegDlg)
	DDX_Control(pDX, IDC_TC_LISTBOX1, m_ctrPU);
	DDX_Control(pDX, IDC_TC_COMBO2, m_ctrRcCurve);
	DDX_Control(pDX, IDC_TC_COMBO1, m_ctrRcType);
	DDX_Radio(pDX, IDC_TC_RADIO2, m_nType);
	DDX_CBIndex(pDX, IDC_TC_COMBO3, m_bSecond);
	DDX_Text(pDX, IDC_TC_EDIT1, m_fA);
	DDX_Text(pDX, IDC_TC_EDIT2, m_fB);
	DDX_Text(pDX, IDC_TC_EDIT3, m_fC);
	DDX_Text(pDX, IDC_TC_EDIT4, m_fD);
	DDX_Text(pDX, IDC_TC_EDIT5, m_fE);
	DDX_Text(pDX, IDC_TC_EDIT6, m_fF);
	DDX_Text(pDX, IDC_TC_EDIT7, m_fPU1);
	DDX_Text(pDX, IDC_TC_EDIT8, m_fPU2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTCRcRegDlg, CDialog)
	//{{AFX_MSG_MAP(CTCRcRegDlg)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDC_TC_BUTTON5, OnTcButton5)
	ON_BN_CLICKED(IDC_TC_BUTTON1, OnTcButton1)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_TC_COMBO1, OnSelchangeTcCombo1)
	ON_BN_CLICKED(IDC_TC_RADIO2, OnTcRadio2)
	ON_BN_CLICKED(IDC_TC_RADIO3, OnTcRadio3)
	ON_CBN_SELCHANGE(IDC_TC_COMBO2, OnSelchangeTcCombo2)
	ON_LBN_SELCHANGE(IDC_TC_LISTBOX1, OnSelchangeTcListbox1)
	ON_BN_CLICKED(IDC_TC_BUTTON2, OnTcButton2)
	ON_BN_CLICKED(IDC_TC_BUTTON4, OnTcButton4)
	ON_BN_CLICKED(IDC_TC_BUTTON3, OnTcButton3)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_TC_COMBO3, OnSelchangeTcCombo3)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCRcRegDlg message handlers

BOOL CTCRcRegDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rect;
//	int x, y, l, height;
//	x = GetSystemMetrics(SM_CXFULLSCREEN);
//	y = GetSystemMetrics(SM_CYFULLSCREEN);
//	GetClientRect( rect );
//	l = rect.right - rect.left;
//	height = rect.bottom - rect.top;

//	MoveWindow( (x-l)/2, (y-height)/2, rect.Width(), rect.Height() );
	//Windows Moving
	CRect rectWnd;
	GetWindowRect( rectWnd );
	CWnd* pWnd = GetDlgItem( IDCANCEL );
	pWnd->GetWindowRect( rect );
	rectWnd.bottom = rect.bottom + 10;
	MoveWindow( rectWnd );

	CString strTmp;

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;
	TRY
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(*m_pDB, _T("select machine_name from n_machine_code where machine_type=1 order by machine_id")) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);

		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strTmp = pBind[0].szValue;
			strTmp.TrimRight();
			m_ctrRcType.AddString(strTmp);


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

	/*COleVariant var;
	CDaoRecordset rs( m_pDB );
	try
	{
		rs.Open( dbOpenDynaset,L"select machine_name from n_machine_code where machine_type=1 order by machine_id" );
		if( rs.GetRecordCount() )
		{
			while( !rs.IsEOF() )
			{
				rs.GetFieldValue( 0, var );
				strTmp = var.bstrVal;
				strTmp.TrimRight();
				m_ctrRcType.AddString( strTmp );
				rs.MoveNext();
			}
		}
		rs.Close();
	}
	catch( CDaoException* e )
	{
		AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}*/
/*	m_ctrButton[0].SubclassDlgItem(IDOK, this);
	m_ctrButton[1].SubclassDlgItem(IDCANCEL, this);
	m_ctrButton[2].SubclassDlgItem(IDC_TC_BUTTON1, this);
	m_ctrButton[3].SubclassDlgItem(IDC_TC_BUTTON2, this);
	m_ctrButton[4].SubclassDlgItem(IDC_TC_BUTTON3, this);
	m_ctrButton[5].SubclassDlgItem(IDC_TC_BUTTON4, this);
	m_ctrButton[6].SubclassDlgItem(IDC_TC_BUTTON5, this);

	m_ctrButton[0].SetColour(RGB(0,0,0), RGB(201,221,234));
	m_ctrButton[1].SetColour(RGB(0,0,0), RGB(201,221,234));
	m_ctrButton[2].SetColour(RGB(0,0,0), RGB(201,221,234));
	m_ctrButton[3].SetColour(RGB(0,0,0), RGB(201,221,234));
	m_ctrButton[4].SetColour(RGB(0,0,0), RGB(201,221,234));
	m_ctrButton[5].SetColour(RGB(0,0,0), RGB(201,221,234));
	m_ctrButton[6].SetColour(RGB(0,0,0), RGB(201,221,234));*/
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTCRcRegDlg::OnOk() 
{
	UpdateData();
	CString strRc, strCurve, strSQL;
	m_ctrRcType.GetWindowText( strRc );
	m_ctrRcCurve.GetWindowText( strCurve );
	if( strRc.IsEmpty() || strCurve.IsEmpty() || m_pCurve == NULL )
	{
		AfxMessageBox( L"등록할 정보가 업습니다." );
		return;
	}
	int i, nMachineID = 0;

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;
	TRY
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select machine_id from n_machine_code where machine_type=1 and machine_name = '%s'"), strRc);
		if (rs.Open(*m_pDB, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);

		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nMachineID = _wtoi(pBind[0].szValue);
		
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

	CDataManager* pDataMng = CDataManager::Instance();

	if (nMachineID)
	{
		strSQL.Format(_T("delete from n_TCcurve_Rc where machine_id=%d and pg=%d and curve='%s'"), nMachineID, m_nType + 1, strCurve);
		pDataMng->SQLDBExcute(m_pDB, strSQL);
	}
	else
	{
		TRY
		{
			ulFields = 1;
			pBind = new MYBIND[ulFields];
			rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
			for (ULONG l = 0; l < ulFields; l++)
				rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
				NULL, &pBind[l].dwStatus);

			strSQL.Format(_T("select max(machine_id) from n_machine_code where machine_type=1"));
			if (rs.Open(*m_pDB, strSQL) != S_OK)
				AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);

			while (rs.MoveNext() == S_OK)
			{
				if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
					wcscpy_s(pBind[0].szValue, _T(""));

				nMachineID = _wtoi(pBind[0].szValue) +1;

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
		
		if (nMachineID == 0)
		{
			nMachineID = 1;
		}

		strSQL.Format(_T("insert into n_machine_code values (%d,1,'%s',NULL)"), nMachineID, strRc);
		pDataMng->SQLDBExcute(m_pDB, strSQL);
		
	}

	CCurveRecloser* pRecloser = (CCurveRecloser*)m_pCurve;
	CRcArray* pArr = pRecloser->GetRcdata();
	RCDATA rd;
	for (i = 0; i < pArr->GetSize(); i++)
	{
		rd = pArr->GetAt(i);
		strSQL.Format(_T("insert into n_TCcurve_Rc values (%d,%d,'%s',%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf)")
			, nMachineID, m_nType + 1, strCurve, rd.m_start, rd.m_end, rd.m_a, rd.m_b, rd.m_c, rd.m_d, rd.m_e, rd.m_n);
		pDataMng->SQLDBExcute(m_pDB, strSQL);
	}

	//COleVariant var;
	//CDaoRecordset rs( m_pDB );
	//try
	//{
	//	//machine_id 가져온다.
	//	strSQL.Format(L"select machine_id from n_machine_code where machine_type=1 and machine_name = '%s'", strRc );
	//	rs.Open( dbOpenDynaset, strSQL );
	//	if( rs.GetRecordCount() )
	//	{
	//		rs.GetFieldValue( 0, var );
	//		nMachineID = var.lVal;
	//	}
	//	rs.Close();
	//	//있으면 내용 없데이트 아니면 둘다 추가한다.
	//	if( nMachineID )
	//	{
	//		//내용을 지우고 현재정보로 다시 삽입한다.
	//		strSQL.Format(L"delete from n_TCcurve_Rc where machine_id=%d and pg=%d and curve='%s'", nMachineID, m_nType+1, strCurve );
	//		m_pDB->Execute( strSQL );
	//	}
	//	else
	//	{
	//		rs.Open( dbOpenDynaset,L"select max(machine_id) from n_machine_code where machine_type=1" );
	//		if( rs.GetRecordCount() )
	//		{
	//			rs.GetFieldValue( 0, var );
	//			nMachineID = var.lVal + 1;
	//		}
	//		else
	//			nMachineID = 1;
	//		rs.Close();
	//		strSQL.Format(L"insert into n_machine_code values (%d,1,'%s',NULL)",nMachineID, strRc );
	//		m_pDB->Execute( strSQL );
	//	}
	//	CCurveRecloser* pRecloser = (CCurveRecloser*)m_pCurve;
	//	CRcArray* pArr = pRecloser->GetRcdata();
	//	RCDATA rd;
	//	for( i = 0; i < pArr->GetSize(); i++ )
	//	{
	//		rd = pArr->GetAt( i );
	//		strSQL.Format(L"insert into n_TCcurve_Rc values (%d,%d,'%s',%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf)"
	//			,nMachineID,m_nType+1,strCurve,rd.m_start,rd.m_end,rd.m_a,rd.m_b,rd.m_c,rd.m_d,rd.m_e,rd.m_n);
	//		m_pDB->Execute( strSQL );
	//	}
	//}
	//catch( CDaoException* e )
	//{
	//	AfxMessageBox( e->m_pErrorInfo->m_strDescription );
	//	e->Delete();
	//}
}

void CTCRcRegDlg::OnTcButton5() 
{
	//삭제
	if( AfxMessageBox(L"삭제하시겠습니까?(Y/N)", MB_YESNO) == IDNO ) return;
	UpdateData();
	int nMachineID = 0;
	
	CString strRc, strCurve, strSQL;
	m_ctrRcType.GetWindowText( strRc );
	m_ctrRcCurve.GetWindowText( strCurve );

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	TRY
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select machine_id from n_machine_code where machine_type=1 and machine_name = '%s'"), strRc);
		if (rs.Open(*m_pDB, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);

		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nMachineID = _wtoi(pBind[0].szValue) ;

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


	if (nMachineID)
	{
		CDataManager* pDataMng = CDataManager::Instance();

		strSQL.Format(_T("delete from n_TCcurve_Rc where machine_id=%d and pg=%d and curve='%s'"), nMachineID, m_nType + 1, strCurve);
		pDataMng->SQLDBExcute(m_pDB,strSQL);
		if (m_pCurve)
		{
			delete m_pCurve;
			m_pCurve = NULL;
		}
		AfxMessageBox(_T("현재 정보가 삭제되었습니다."));
		m_fPU1 = m_fPU2 = m_fA = m_fB = m_fC = m_fD = m_fE = m_fF = 0;
		m_ctrRcCurve.SetWindowText(_T(""));
		UpdateData(FALSE);
	}

/*	COleVariant var;
	CDaoRecordset rs(m_pDB);
	try
	{
		//machine_id 가져온다.
		strSQL.Format(L"select machine_id from n_machine_code where machine_type=1 and machine_name = '%s'", strRc );
		rs.Open( dbOpenDynaset, strSQL );
		if( rs.GetRecordCount() )
		{
			rs.GetFieldValue( 0, var );
			nMachineID = var.lVal;
		}
		rs.Close();
		//있으면 삭제한다.
		if( nMachineID )
		{
			strSQL.Format(L"delete from n_TCcurve_Rc where machine_id=%d and pg=%d and curve='%s'", nMachineID, m_nType+1, strCurve );
			m_pDB->Execute( strSQL );
			if( m_pCurve )
			{
				delete m_pCurve;
				m_pCurve = NULL;
			}
			AfxMessageBox(L"현재 정보가 삭제되었습니다.");
			m_fPU1 = m_fPU2 = m_fA = m_fB = m_fC = m_fD = m_fE = m_fF = 0;
			m_ctrRcCurve.SetWindowText( L"" );
			UpdateData(FALSE);
		}
	}
	catch( CDaoException* e )
	{
		AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}*/
}

void CTCRcRegDlg::OnTcButton1() 
{
	UpdateData();

	if (m_pCurve == NULL)
		return;


	CRect rect, rectWnd;
	GetWindowRect( rectWnd );
	CWnd* pWnd = GetDlgItem( IDC_TCCURVE );
	pWnd->GetWindowRect( rect );
	for( int i = rectWnd.bottom; i < rect.bottom + 96; i+=2 )
	{
		rectWnd.bottom = i;
		MoveWindow( rectWnd );
	}
	CCurveRecloser* pRecloser = (CCurveRecloser*)m_pCurve;
	pRecloser->SetSecond( m_bSecond ); 
	Invalidate();
}

void CTCRcRegDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	((CWnd*)GetDlgItem( IDC_TCCURVE ))->GetWindowRect( rect );
	ScreenToClient( rect );
	DrawGrid( &dc, rect );
	TextGrid( &dc, rect );

	if( m_pCurve )
	{
		m_pCurve->Draw( &dc, rect, 3.5 ,TRUE);
		DrawIndex( &dc, rect );
	}
}

void CTCRcRegDlg::DrawGrid(CDC *pDC, CRect rect)
{
	double dLog, dTabx, dTaby;
	dTabx = rect.Width() / 3.5;
	dTaby = rect.Height() / 3.5;

	CPen pen, *pOldpen;
	pen.CreatePen( PS_DOT, 1, RGB( 255, 255, 255 ) );
	pOldpen = pDC->SelectObject( &pen );
	
	CFont font,*pOldfont;
	font.CreateFont( 12, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS,L"굴림체" );
	pOldfont = pDC->SelectObject(&font);

	int i, x, y, ntab = 1;
	CString strTmp;
	pDC->SetTextColor( RGB( 128, 128, 0 ) );
	pDC->SetBkMode( TRANSPARENT );
	if( m_bSecond )
	{
		for( i = 0 ; i < 50; i += ntab )
		{
			if( i )
			{
				dLog = log10((double) i*60 );
				y = int( rect.bottom - dLog * dTaby );
				if( y > rect.bottom ) continue;
				pDC->MoveTo( rect.left, y );//x
				pDC->LineTo( rect.right, y );//x
			}
			else
			{
				y = rect.bottom;
			}
			// text output
			if( i >= 1000 ) ntab = 1000;
			else if( i >= 100 ) ntab = 100;
			else if( i >= 10 ) ntab = 10;
			if( ntab >= 10 && i/ntab > 5 ) continue;
			strTmp.Format(L"%d", i );
			pDC->SetTextAlign( TA_RIGHT );
			pDC->TextOut( rect.left-2, y-6, strTmp );//y
		}
		ntab = 1;
		for( i = 1 ; i < 3000; i += ntab )
		{
			if( i != 1 )
			{
				dLog = log10((double) i );
				x = int( rect.left + dLog * dTabx );
				if( x > rect.right ) continue;
				pDC->MoveTo( x, rect.top );//y
				pDC->LineTo( x, rect.bottom );//y
			}
			else
			{
				x = rect.left;
			}
			// text output
			if( i >= 1000 ) ntab = 1000;
			else if( i >= 100 ) ntab = 100;
			else if( i >= 10 ) ntab = 10;
			if( ntab >= 10 && i/ntab > 5 ) continue;
			strTmp.Format(L"%d", i );
			pDC->SetTextAlign( TA_CENTER );
			pDC->TextOut( x, rect.bottom+5, strTmp );//x
		}
	}
	else
	{
		for( i = 1 ; i < 3000; i += ntab )
		{
			if( i != 1 )
			{
				dLog = log10((double) i );
				x = int( rect.left + dLog * dTabx );
				if( m_bSecond )
				{
					if( i <= 50)
						y = int( rect.bottom - dLog * dTaby );
				}
				else
					y = int( rect.bottom - dLog * dTaby );
				if( x > rect.right ) continue;
				if( y > rect.bottom ) continue;
				pDC->MoveTo( rect.left, y );//x
				pDC->LineTo( rect.right, y );//x
				pDC->MoveTo( x, rect.top );//y
				pDC->LineTo( x, rect.bottom );//y
			}
			else
			{
				x = rect.left;
				y = rect.bottom;
			}
			// text output
			if( i >= 1000 ) ntab = 1000;
			else if( i >= 100 ) ntab = 100;
			else if( i >= 10 ) ntab = 10;
			if( ntab >= 10 && i/ntab > 5 ) continue;
			strTmp.Format(L"%d", i );
			pDC->SetTextAlign( TA_CENTER );
			pDC->TextOut( x, rect.bottom+5, strTmp );//x
			pDC->SetTextAlign( TA_RIGHT );
			pDC->TextOut( rect.left-2, y-6, strTmp );//y
		}
	}
	pDC->SetTextAlign( TA_LEFT );
	pDC->SetTextColor( RGB( 0, 0, 0 ) );
	pDC->SelectObject( pOldfont );
	pDC->SelectObject( pOldpen );
}

void CTCRcRegDlg::TextGrid(CDC *pDC, CRect rect)
{
	pDC->SetTextColor( RGB( 0, 0, 128 ) );
	CFont font, font2, *pOldfont;
	font.CreateFont( 15, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS,L"굴림체" );
	pOldfont = pDC->SelectObject(&font);
	pDC->SetTextAlign( TA_CENTER );
	//pDC->TextOut( rect.CenterPoint().x, rect.bottom + 30,L"Current(A)");
	pDC->TextOut( rect.CenterPoint().x, rect.bottom + 30,L"Multiples of Pick-Up");
	pDC->SelectObject( pOldfont );
	//
	font2.CreateFont( 15, 0, 900, 0, FW_THIN, FALSE, FALSE, FALSE,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS,L"굴림체" );
	pOldfont = pDC->SelectObject(&font2);
	if( m_bSecond )
		pDC->TextOut( rect.left - 60, rect.CenterPoint().y,L"Time in Seconds (60-HERTZ BASIS)");
	else
		pDC->TextOut( rect.left - 60, rect.CenterPoint().y,L"Time in Cycles (60-HERTZ BASIS)");
	//
	pDC->SetTextColor( RGB( 0, 0, 0 ) );
	pDC->SetTextAlign( TA_LEFT );
	pDC->SelectObject( pOldfont );
}

void CTCRcRegDlg::DrawIndex(CDC *pDC, CRect rect)
{
	CFont font, *pOldfont;
	font.CreateFont( 12, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS,L"굴림체" );
	pOldfont = pDC->SelectObject(&font);

	int nLength;
	nLength = m_pCurve->m_strName.GetLength()*2;
	pDC->Rectangle( rect.right - 200 - nLength, rect.top, rect.right, rect.top + 12 + 6 );

	CPen pen, *pOldpen;
	pen.CreatePen( PS_SOLID, 1, m_pCurve->GetColor() );
	pOldpen = pDC->SelectObject( &pen );
	pDC->MoveTo( rect.right - 190 - nLength, rect.top + 9 );
	pDC->LineTo( rect.right - 150 - nLength, rect.top + 9 );
	pDC->TextOut( rect.right-(12*12)-nLength, rect.top + 3, m_pCurve->m_strName );
	pDC->SelectObject( pOldpen );
	pDC->SelectObject( pOldfont );
}

void CTCRcRegDlg::OnSelchangeTcCombo1() 
{
	UpdateData();
	int nMachineID = 0;
	CString strTmp, strSQL;

	m_ctrRcType.GetLBText( m_ctrRcType.GetCurSel(), strTmp );
	m_fA = m_fB = m_fC = m_fD = m_fE = m_fF = 0;


	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	try
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select machine_id from n_machine_code where machine_type=1 and machine_name = '%s'"), strTmp);
		if (rs.Open(*m_pDB, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);

		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nMachineID = _wtoi(pBind[0].szValue);

		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		////////// Subs

	}
	catch( COLEDBException* e)
	{
		if (pBind != NULL)
			delete pBind;

		e->ReportError();
	}
	

	if (nMachineID)
	{
		m_ctrRcCurve.ResetContent();
		m_ctrPU.ResetContent();

		try
		{
			ulFields = 1;
			pBind = new MYBIND[ulFields];
			rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
			for (ULONG l = 0; l < ulFields; l++)
				rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
					NULL, &pBind[l].dwStatus);

			strSQL.Format(_T("select curve from n_TCcurve_RC where machine_id=%d and pg=%d group by curve order by curve"), nMachineID, m_nType + 1);
			if (rs.Open(*m_pDB, strSQL) != S_OK)
				AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);

			while (rs.MoveNext() == S_OK)
			{
				if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
					wcscpy_s(pBind[0].szValue, _T(""));

				strTmp = pBind[0].szValue;
				strTmp.TrimRight();
				m_ctrRcCurve.AddString(strTmp);

			}
			rs.Close();
			delete pBind;
			pBind = NULL;

			////////// Subs

		}
		catch (COLEDBException* e)
		{
			if (pBind != NULL)
				delete pBind;

			e->ReportError();
		}

		if (m_pCurve)
		{
			delete m_pCurve;
			m_pCurve = NULL;
		}
	
	}

	/*COleVariant var;
	CDaoRecordset rs(m_pDB);
	try
	{
		strSQL.Format(L"select machine_id from n_machine_code where machine_type=1 and machine_name = '%s'", strTmp );
		rs.Open( dbOpenDynaset, strSQL );
		if( rs.GetRecordCount() )
		{
			rs.GetFieldValue( 0, var );
			nMachineID = var.lVal;
		}
		rs.Close();
		if( nMachineID )
		{
			m_ctrRcCurve.ResetContent();
			m_ctrPU.ResetContent();
			strSQL.Format(L"select curve from n_TCcurve_RC where machine_id=%d and pg=%d group by curve order by curve", nMachineID, m_nType+1 );
			rs.Open( dbOpenDynaset, strSQL );
			if( rs.GetRecordCount() )
			{
				while( !rs.IsEOF() )
				{
					rs.GetFieldValue( 0, var );
					strTmp = var.bstrVal;
					strTmp.TrimRight();
					m_ctrRcCurve.AddString( strTmp );
					rs.MoveNext();
				}
			}
			rs.Close();
		}
		if( m_pCurve )
		{
			delete m_pCurve;
			m_pCurve = NULL;
		}
	}
	catch( CDaoException* e )
	{
		AfxMessageBox( e->m_pErrorInfo->m_strDescription );
		e->Delete();
	}*/
	UpdateData( FALSE );
}

void CTCRcRegDlg::OnTcRadio2() 
{
	UpdateData();
	OnSelchangeTcCombo1();
}

void CTCRcRegDlg::OnTcRadio3() 
{
	UpdateData();
	OnSelchangeTcCombo1();
}

void CTCRcRegDlg::OnSelchangeTcCombo2() 
{
	UpdateData();
	int nMachineID = 0;
	CString strType, strCurve, strSQL;
	
	m_ctrRcType.GetLBText( m_ctrRcType.GetCurSel(), strType );
	m_ctrRcCurve.GetLBText( m_ctrRcCurve.GetCurSel(), strCurve );
	m_fPU1 = m_fPU2 = m_fA = m_fB = m_fC = m_fD = m_fE = m_fF = 0;

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	try
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
				NULL, &pBind[l].dwStatus);

		strSQL.Format(_T("select machine_id from n_machine_code where machine_type=1 and machine_name = '%s'"), strType);
		if (rs.Open(*m_pDB, strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);

		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nMachineID = _wtoi(pBind[0].szValue);

		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		////////// Subs

	}
	catch (COLEDBException* e)
	{
		if (pBind != NULL)
			delete pBind;

		e->ReportError();
	}

	if (nMachineID)
	{
		int nCount = 0;
		CCurveRecloser* pRecloser = NULL;
		try
		{
			ulFields = 10;
			pBind = new MYBIND[ulFields];
			rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
			for (ULONG l = 0; l < ulFields; l++)
				rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
					NULL, &pBind[l].dwStatus);

			strSQL.Format(_T("select * from n_TCcurve_RC where machine_id=%d and pg=%d and curve='%s' order by s_cur"), nMachineID, m_nType + 1, strCurve);
			if (rs.Open(*m_pDB, strSQL) != S_OK)
				AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);

			

			while (rs.MoveNext() == S_OK)
			{
				if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
					wcscpy_s(pBind[0].szValue, _T(""));

				if (nCount == 0)
				{
					pRecloser = new CCurveRecloser();
					pRecloser->m_strName.Format(L"RC %s %c %s", strType, (m_nType ? 'G' : 'P'), strCurve);
				}
				nCount++;
				
				RCDATA rcdata;
				rcdata.m_start	= _wtof(pBind[3].szValue);
				rcdata.m_end	= _wtof(pBind[4].szValue);
				rcdata.m_a		= _wtof(pBind[5].szValue);
				rcdata.m_b		= _wtof(pBind[6].szValue);
				rcdata.m_c		= _wtof(pBind[7].szValue);
				rcdata.m_d		= _wtof(pBind[8].szValue);
				rcdata.m_e		= _wtof(pBind[9].szValue);
				rcdata.m_n		= _wtof(pBind[10].szValue);
				pRecloser->Add( &rcdata );
				rs.MoveNext();
			
				// data Accept
				

			}
			rs.Close();
			delete pBind;
			pBind = NULL;

			////////// Subs

		}
		catch (COLEDBException* e)
		{
			if (pBind != NULL)
				delete pBind;

			e->ReportError();
		}

		if (pRecloser)
		{
			pRecloser->m_nColorType = 1;

			if (m_pCurve) delete m_pCurve;
			m_pCurve = pRecloser;
			UpdateList();
		}
		
	}

	//COleVariant var;
	//CDaoRecordset rs(m_pDB);
	//try
	//{
	//	strSQL.Format(L"select machine_id from n_machine_code where machine_type=1 and machine_name = '%s'", strType );
	//	rs.Open( dbOpenDynaset, strSQL );
	//	if( rs.GetRecordCount() )
	//	{
	//		rs.GetFieldValue( 0, var );
	//		nMachineID = var.lVal;
	//	}
	//	rs.Close();
	//	if( nMachineID )
	//	{
	//		strSQL.Format(L"select * from n_TCcurve_RC where machine_id=%d and pg=%d and curve='%s' order by s_cur", nMachineID, m_nType+1, strCurve );
	//		rs.Open( dbOpenDynaset, strSQL );
	//		if( rs.GetRecordCount() )
	//		{
	//			CCurveRecloser* pRecloser = new CCurveRecloser();
	//			pRecloser->m_strName.Format(L"RC %s %c %s", strType, (m_nType?'G':'P'), strCurve );
	//			while( !rs.IsEOF() )
	//			{
	//				RCDATA rcdata;
	//				rs.GetFieldValue(3,var);
	//				rcdata.m_start = var.fltVal;
	//				rs.GetFieldValue(4,var);
	//				rcdata.m_end = var.fltVal;
	//				rs.GetFieldValue(5,var);
	//				rcdata.m_a = var.fltVal;
	//				rs.GetFieldValue(6,var);
	//				rcdata.m_b = var.fltVal;
	//				rs.GetFieldValue(7,var);
	//				rcdata.m_c = var.fltVal;
	//				rs.GetFieldValue(8,var);
	//				rcdata.m_d = var.fltVal;
	//				rs.GetFieldValue(9,var);
	//				rcdata.m_e = var.fltVal;
	//				rs.GetFieldValue(10,var);
	//				rcdata.m_n = var.fltVal;
	//				pRecloser->Add( &rcdata );
	//				rs.MoveNext();
	//			}
	//			// data Accept
	//			pRecloser->m_nColorType = 1;
	//			if( m_pCurve ) delete m_pCurve;
	//			m_pCurve = pRecloser;
	//			UpdateList();
	//		}
	//		rs.Close();
	//	}
	//}
	//catch( CDaoException* e )
	//{
	//	AfxMessageBox( e->m_pErrorInfo->m_strDescription );
	//	e->Delete();
	//}
	UpdateData( FALSE );
	Invalidate();
}

void CTCRcRegDlg::UpdateList()
{
	if( m_pCurve == NULL ) return;
	m_ctrPU.ResetContent();
	CString strTmp;
	CCurveRecloser* pRecloser = (CCurveRecloser*)m_pCurve;
	CRcArray* pArr = pRecloser->GetRcdata();
	for( int i = 0; i < pArr->GetSize(); i++ )
	{
		strTmp.Format(L"%g ~ %g", pArr->GetAt(i).m_start, pArr->GetAt(i).m_end );
		m_ctrPU.AddString( strTmp );
	}
}

void CTCRcRegDlg::OnSelchangeTcListbox1() 
{
	if( m_pCurve == NULL ) return;
	CCurveRecloser* pRecloser = (CCurveRecloser*)m_pCurve;
	CRcArray* pArr = pRecloser->GetRcdata();
	int nItem = m_ctrPU.GetCurSel();

	if (nItem == -1)
		return;

	m_fPU1 = pArr->GetAt(nItem).m_start;
	m_fPU2 = pArr->GetAt(nItem).m_end;
	m_fA = pArr->GetAt(nItem).m_a;
	m_fB = pArr->GetAt(nItem).m_b;
	m_fC = pArr->GetAt(nItem).m_c;
	m_fD = pArr->GetAt(nItem).m_d;
	m_fE = pArr->GetAt(nItem).m_e;
	m_fF = pArr->GetAt(nItem).m_n;
	UpdateData(FALSE);
}

void CTCRcRegDlg::OnTcButton2() 
{
	UpdateData();
	if( m_fPU1 >= m_fPU2 )
	{
		AfxMessageBox(L"PU값 설정이 잘못되었습니다.");
		return;
	}
	CCurveRecloser* pRecloser;
	if( m_pCurve == NULL )
	{
		CString strType, strCurve;
		m_ctrRcType.GetWindowText( strType );
		m_ctrRcCurve.GetWindowText( strCurve );
		pRecloser = new CCurveRecloser();
		pRecloser->m_strName.Format(L"RC %s %c %s", strType, (m_nType?'G':'P'), strCurve );
		m_pCurve = pRecloser;
	}
	pRecloser = (CCurveRecloser*)m_pCurve;
	RCDATA rcdata;
	rcdata.m_start = m_fPU1;
	rcdata.m_end = m_fPU2;
	rcdata.m_a = m_fA;
	rcdata.m_b = m_fB;
	rcdata.m_c = m_fC;
	rcdata.m_d = m_fD;
	rcdata.m_e = m_fE;
	rcdata.m_n = m_fF;
	pRecloser->Add( &rcdata );
	UpdateList();
	Invalidate();
}

void CTCRcRegDlg::OnTcButton4() 
{
	if( m_pCurve == NULL ) return;
	int nItem = m_ctrPU.GetCurSel();
	if( nItem == -1 )
	{
		AfxMessageBox(L"수정할 목록을 선택하십시요.");
		return;
	}
	UpdateData();
	CCurveRecloser* pRecloser = (CCurveRecloser*)m_pCurve;
	CRcArray* pArr = pRecloser->GetRcdata();
	m_ctrPU.DeleteString( nItem );
	RCDATA rcdata = pArr->GetAt(nItem);
	rcdata.m_start = m_fPU1;
	rcdata.m_end = m_fPU2;
	rcdata.m_a = m_fA;
	rcdata.m_b = m_fB;
	rcdata.m_c = m_fC;
	rcdata.m_d = m_fD;
	rcdata.m_e = m_fE;
	rcdata.m_n = m_fF;
	pRecloser->SetAt( nItem, &rcdata );
	UpdateList();
	Invalidate();
}

void CTCRcRegDlg::OnTcButton3() 
{
	if( m_pCurve == NULL ) return;
	int nItem = m_ctrPU.GetCurSel();
	if( nItem == -1 )
	{
		AfxMessageBox(L"삭제할 목록을 선택하십시요.");
		return;
	}
	CCurveRecloser* pRecloser = (CCurveRecloser*)m_pCurve;
	CRcArray* pArr = pRecloser->GetRcdata();
	pArr->RemoveAt( nItem );
	m_fPU1 = m_fPU2 = m_fA = m_fB = m_fC = m_fD = m_fE = m_fF = 0;
	UpdateList();
	UpdateData(FALSE);
	Invalidate();
}

BOOL CTCRcRegDlg::DestroyWindow() 
{
	if( m_pCurve ) delete m_pCurve;
	return CDialog::DestroyWindow();
}

HBRUSH CTCRcRegDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
// 	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_LISTBOX)
//    {
// //        HBRUSH Br = CreateSolidBrush(RGB(201,221,234)); 
//         static CBrush s_brush(RGB(201,221,234));
//         pDC->SetBkMode(TRANSPARENT);
//         pDC->SetTextColor(RGB(3,3,3));
// 		pDC->SetBkColor(RGB(201,221,234));
//         return s_brush;
//     }	
	return hbr;
}

void CTCRcRegDlg::OnSelchangeTcCombo3() 
{
	UpdateData();
	if( m_pCurve)
		m_pCurve->SetSecond(m_bSecond);
	Invalidate();	
}

void CTCRcRegDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rect;
	((CWnd*)GetDlgItem( IDC_TCCURVE ))->GetWindowRect( rect );
	ScreenToClient( rect );
	if( !rect.PtInRect( point ) ) return;

	CClientDC dc(this);
	double dTabx, dTaby;
	dTabx = rect.Width() / 3.5;
	dTaby = rect.Height() / 3.5;

	CFont font,*pOldfont;
	font.CreateFont( 12, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS,L"굴림체" );
	pOldfont = dc.SelectObject(&font);

	CBrush brush, *pOldbrush;
	brush.CreateSolidBrush( RGB( 0, 0, 128 ) );
	pOldbrush = dc.SelectObject( &brush );
	int x, y;
	CString strTmp;
	dc.SetTextColor( RGB( 255, 255, 0 ) );
	dc.SetBkMode( TRANSPARENT );

	x = rect.left-5;
	y = rect.bottom - 20;
	dc.Rectangle( x - 55, y - 14, x, y );
	if( m_bSecond )	strTmp.Format(L"%.4lf", pow( 10, ( rect.bottom - point.y ) / dTaby )/60 );
	else strTmp.Format(L"%.4lf", pow( 10, ( rect.bottom - point.y ) / dTaby ) );
	dc.TextOut( x - 55, y-13, strTmp );
	dc.Rectangle( rect.left, rect.bottom + 20, rect.left + 60, rect.bottom + 36 );
	strTmp.Format(L"%.4lf", pow( 10, ( point.x - rect.left ) / dTabx ) );
	dc.TextOut( rect.left, rect.bottom + 21, strTmp );

	dc.SetTextColor( RGB( 0, 0, 0 ) );
	dc.SelectObject( pOldbrush );
	dc.SelectObject( pOldfont );
	CDialog::OnMouseMove(nFlags, point);
}
