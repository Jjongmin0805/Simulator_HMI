// TCFuseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TCFuseDlg.h"
#include "math.h"
#include "../DataManager/CDataManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTCFuseDlg dialog


CTCFuseDlg::CTCFuseDlg(CSession* pDB, CWnd* pParent /*=NULL*/)
	: CDialog(CTCFuseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTCFuseDlg)
	m_nType = 0;
	m_bSecond = 0;
	m_fA = 0.0f;
	m_fB = 0.0f;
	m_fC = 0.0f;
	m_fCurrent1 = 0.0f;
	m_fCurrent2 = 0.0f;
	//}}AFX_DATA_INIT
	m_pDB = pDB;
	m_pCurve = NULL;
}


void CTCFuseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCFuseDlg)
	DDX_Control(pDX, IDC_TC_COMBO1, m_ctrCombo);
	DDX_Radio(pDX, IDC_TC_RADIO1, m_nType);
	DDX_CBIndex(pDX, IDC_TC_COMBO2, m_bSecond);
	DDX_Text(pDX, IDC_TC_EDIT1, m_fA);
	DDX_Text(pDX, IDC_TC_EDIT2, m_fB);
	DDX_Text(pDX, IDC_TC_EDIT3, m_fC);
	DDX_Text(pDX, IDC_TC_EDIT4, m_fCurrent1);
	DDX_Text(pDX, IDC_TC_EDIT5, m_fCurrent2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTCFuseDlg, CDialog)
	//{{AFX_MSG_MAP(CTCFuseDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TC_BUTTON1, OnTcButton1)
	ON_CBN_SELCHANGE(IDC_TC_COMBO1, OnSelchangeTcCombo1)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_TC_COMBO2, OnSelchangeTcCombo2)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_TC_RADIO1, OnTcRadio1)
	ON_BN_CLICKED(IDC_TC_RADIO2, OnTcRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCFuseDlg message handlers

BOOL CTCFuseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rect;
	//Windows Moving
	CRect rectWnd;
	GetWindowRect( rectWnd );
	CWnd* pWnd = GetDlgItem( IDCANCEL );
	pWnd->GetWindowRect( rect );
	rectWnd.bottom = rect.bottom + 10;
	MoveWindow( rectWnd );

	CString strTmp;

	/*COleVariant var;
	CDaoRecordset rs( m_pDB );
	try
	{
		rs.Open( dbOpenDynaset,L"select machine_name from n_machine_code where machine_type=3 order by machine_id" );
		if( rs.GetRecordCount() )
		{
			while( !rs.IsEOF() )
			{
				rs.GetFieldValue( 0, var );
				strTmp = var.bstrVal;
				strTmp.TrimRight();
				m_ctrCombo.AddString( strTmp );
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


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTCFuseDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	((CWnd*)GetDlgItem( IDC_TCCURVE ))->GetWindowRect( rect );
	ScreenToClient( rect );
	DrawGrid( &dc, rect );
	TextGrid( &dc, rect );

	if( m_pCurve )
	{
		m_pCurve->Draw( &dc, rect, 3.5 );
		DrawIndex( &dc, rect );
	}
}

void CTCFuseDlg::OnTcButton1() 
{
	UpdateData();
	if( m_ctrCombo.GetCurSel() == -1 )
	{
		AfxMessageBox(L"Fuse Type을 선택하십시요.");
		return;
	}
	CRect rect, rectWnd;
	GetWindowRect( rectWnd );
	CWnd* pWnd = GetDlgItem( IDC_TCCURVE );
	pWnd->GetWindowRect( rect );
	for( int i = rectWnd.bottom; i < rect.bottom + 96; i+=2 )
	{
		rectWnd.bottom = i;
		MoveWindow( rectWnd );
	}
	//
	CString strType;
	m_ctrCombo.GetLBText( m_ctrCombo.GetCurSel(), strType );
	CCurveFuse* pFuse = new CCurveFuse( m_fCurrent1, m_fCurrent2, m_fA, m_fB, m_fC );
	pFuse->m_strName.Format( L"FUSE %s %c", strType, (m_nType?'F':'D') );
	pFuse->m_nColorType = 1;
	if( m_pCurve ) delete m_pCurve;
	m_pCurve = pFuse;
	Invalidate();
}

void CTCFuseDlg::DrawGrid(CDC *pDC, CRect rect)
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

void CTCFuseDlg::TextGrid(CDC *pDC, CRect rect)
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
	font2.CreateFont( 15, 0, 900, 0, FW_THIN, FALSE, FALSE, FALSE,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS,L"굴림체" );
	pOldfont = pDC->SelectObject(&font2);
	if( m_bSecond )
		pDC->TextOut( rect.left - 60, rect.CenterPoint().y,L"Time in Seconds (60-HERTZ BASIS)");
	else
		pDC->TextOut( rect.left - 60, rect.CenterPoint().y,L"Time in Cycles (60-HERTZ BASIS)");
	pDC->SetTextColor( RGB( 0, 0, 0 ) );
	pDC->SetTextAlign( TA_LEFT );
	pDC->SelectObject( pOldfont );
}

void CTCFuseDlg::DrawIndex(CDC *pDC, CRect rect)
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

void CTCFuseDlg::OnSelchangeTcCombo1() 
{
	CString strType, strSQL;
	
	m_ctrCombo.GetLBText( m_ctrCombo.GetCurSel(), strType );
	m_fA = m_fB = m_fC = m_fCurrent1 = m_fCurrent2 = 0;

	//COleVariant var;
	//CDaoRecordset rs(m_pDB);
	//try
	//{
	//	strSQL.Format(L"select * from n_TCcurve_Fuse where machine_id = (select machine_id from n_machine_code where machine_type=3 and machine_name = '%s') and kind=%d", strType, m_nType+1 );
	//	rs.Open( dbOpenDynaset, strSQL );
	//	if( rs.GetRecordCount() )
	//	{
	//		rs.GetFieldValue( 2, var );
	//		m_fCurrent1 = var.fltVal;
	//		rs.GetFieldValue( 3, var );
	//		m_fCurrent2 = var.fltVal;
	//		rs.GetFieldValue( 4, var );
	//		m_fA = var.fltVal;
	//		rs.GetFieldValue( 5, var );
	//		m_fB = var.fltVal;
	//		rs.GetFieldValue( 6, var );
	//		m_fC = var.fltVal;

	//		CCurveFuse* pFuse = new CCurveFuse( m_fCurrent1, m_fCurrent2, m_fA, m_fB, m_fC );
	//		pFuse->m_strName.Format( L"FUSE %s %c", strType, (m_nType?'F':'D') );
	//		pFuse->m_nColorType = 1;

	//		if( m_pCurve ) delete m_pCurve;
	//		m_pCurve = pFuse;
	//	}
	//	rs.Close();
	//}
	//catch( CDaoException* e )
	//{
	//	AfxMessageBox( e->m_pErrorInfo->m_strDescription );
	//	e->Delete();
	//}
	UpdateData( FALSE );
	Invalidate();
}

void CTCFuseDlg::OnOk() 
{
	UpdateData();
	CString strFuse, strSQL;
	m_ctrCombo.GetLBText( m_ctrCombo.GetCurSel(), strFuse );
	if( m_ctrCombo.GetCurSel() == -1 )
	{
		AfxMessageBox( L"등록할 정보가 업습니다." );
		return;
	}
	int nMachineID = 0;
	//COleVariant var;
	//CDaoRecordset rs( m_pDB );
	//try
	//{
	//	//machine_id 가져온다.
	//	strSQL.Format(L"select machine_id from n_machine_code where machine_type=3 and machine_name = '%s'", strFuse );
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
	//		strSQL.Format(L"update n_TCcurve_Fuse set s_cur=%lf,e_cur=%lf,a=%lf,b=%lf,n=%lf where machine_id=%d and kind=%d",
	//			m_fCurrent1,m_fCurrent2,m_fA,m_fB,m_fC,nMachineID,m_nType+1 );
	//		m_pDB->Execute( strSQL );
	//		AfxMessageBox(L"현재 정보로 변경되었습니다.");
	//	}
	//}
	//catch( CDaoException* e )
	//{
	//	AfxMessageBox( e->m_pErrorInfo->m_strDescription );
	//	e->Delete();
	//}
}

HBRUSH CTCFuseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
// 	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_LISTBOX)
//    {
//         static CBrush s_brush(RGB(201,221,234));
//         pDC->SetBkMode(TRANSPARENT);
//         pDC->SetTextColor(RGB(3,3,3));
// 		pDC->SetBkColor(RGB(201,221,234));
//         return s_brush;
//     }	
	return hbr;
}

void CTCFuseDlg::OnSelchangeTcCombo2() 
{
	UpdateData();
	if( m_pCurve)
		m_pCurve->SetSecond(m_bSecond);
	Invalidate();
}

void CTCFuseDlg::OnMouseMove(UINT nFlags, CPoint point) 
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

void CTCFuseDlg::OnTcRadio1() 
{
	UpdateData();
	OnSelchangeTcCombo1();
}

void CTCFuseDlg::OnTcRadio2() 
{
	UpdateData();
	OnSelchangeTcCombo1();
}
