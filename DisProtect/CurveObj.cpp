// CurveObj.cpp: implementation of the CCurveObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"
#include "CurveObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurveObj::CCurveObj()
{
	m_bSecond = FALSE;
	m_dDGPU = 0;
	m_nColorType = 1;
}

CCurveObj::~CCurveObj()
{

}

COLORREF CCurveObj::GetColor()
{
	COLORREF rgn;
	switch (m_nColorType)
	{
	case 1:
		rgn = RGB( 255, 0, 0 );
		break;
	case 2:
		rgn = RGB( 255, 128, 0 );
		break;
	case 3:
		rgn = RGB( 128, 128, 0 );
		break;
	case 4:
		rgn = RGB( 0, 255, 0 );
		break;
	case 5:
		rgn = RGB( 0, 0, 255 );
		break;
	case 6:
		rgn = RGB( 0, 0, 128 );
		break;
	case 7:
		rgn = RGB( 128, 0, 255 );
		break;
	case 8:
		rgn = RGB( 255, 0, 255 );
		break;
	case 9:
		rgn = RGB( 0, 255, 255 );
		break;
	case 10:
		rgn = RGB( 0, 0, 0 );
		break;
	}
	return rgn;
}

//////////////////////////////////////////////////////////////////////
// CRecloser Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurveRecloser::CCurveRecloser()
{
	m_dOneValue = 0;
	m_dmin = 10000;
	m_dmax = 1;
	m_dPU = 0;
	m_bSecond = FALSE;
	m_dTm = 1;
	m_dTa = 0;
	//커브정보추가
	m_dMaxAmp = m_dAmp = 0.0;
}

CCurveRecloser::~CCurveRecloser()
{
	m_pRcdata.RemoveAll();
}

void CCurveRecloser::Add(RCDATA* pdata)
{
	if( m_dmin > pdata->m_start ) m_dmin = pdata->m_start;
	if( m_dmax < pdata->m_end ) m_dmax = pdata->m_end;
	if( m_dmax < 500 ) m_dmax = 500;
	for( int i = 0; i < m_pRcdata.GetSize(); i++ )
	{
		if( m_pRcdata[i].m_start > pdata->m_start )
		{
			m_pRcdata.InsertAt( i, *pdata );
			return;
		}
	}
	m_pRcdata.Add( *pdata );
}

void CCurveRecloser::SetAt(int nIdx, RCDATA *pdata)
{
	m_pRcdata[nIdx] = *pdata;
}

void CCurveRecloser::Draw(CDC *pDC, CRect rect, double dTab, BOOL bShowPu)
{
	int x, y;
	double dLog, dTabx, dTaby;
	dTabx = rect.Width() / dTab;
	dTaby = rect.Height() / dTab;

	CPen pen, *pOldpen;
	pen.CreatePen( PS_SOLID, 1, GetColor() );
	pOldpen = pDC->SelectObject( &pen );

	double i, dtab = 0.1;

	//커브정보추가
	//나형화변경
	double dCurrent;
	BOOL	bCheck = FALSE;
	BOOL	bStart = TRUE;
	if( bShowPu )
	{
		for( i = m_dmin ; i <= m_dmax; i += dtab )
		{
			dLog = log10( GetY( (float)i ) );
			x = int( rect.left + log10( i ) * dTabx );
			y = int( rect.bottom - dLog * dTaby );
			if( y < rect.top ) y = rect.top;
			if( x > rect.right ) continue;
			if( y > rect.bottom ) continue;
			if( i == m_dmin )
				pDC->MoveTo( x, y );
			else
				pDC->LineTo( x, y );

			if( i > 1000 ) dtab = 1000;
			else if( i > 100 ) dtab = 100;
			else if( i > 50 ) dtab = 10;
			else if( i > 2 ) dtab = 1;
		}
	}
	else
	{
		for( i = m_dmin ; i <= m_dmax; i += dtab )
		{
			//커브정보추가
			if( i == m_dmax )
				bCheck = TRUE;
			dCurrent = i*m_dAmp;
			dLog = log10( GetY( (float)i ) );
			x = int( rect.left + log10( dCurrent ) * dTabx );
			y = int( rect.bottom - dLog * dTaby );

			if( y < rect.top ) y = rect.top;
			if( x > rect.right ) continue;
			if( y > rect.bottom ) continue;
			if( x < rect.left ) continue;
			if( bStart )
			{
				pDC->MoveTo( x, y );
				bStart = FALSE;
			}
			else
				pDC->LineTo( x, y );

			if( i > 1000 ) dtab = 1000;
			else if( i > 100 ) dtab = 100;
			else if( i > 50 ) dtab = 10;
			else if( i > 2 ) dtab = 1;
		}
		//커브정보추가
		if( bCheck == FALSE )
		{
			dCurrent = m_dmax*m_dAmp;
			dLog = log10( GetY( (float)m_dmax ) );
			x = int( rect.left + log10( dCurrent ) * dTabx );
			y = int( rect.bottom - dLog * dTaby );
		
			if( y < rect.top ) y = rect.top;
			if( x < rect.right && y < rect.bottom )
				pDC->LineTo( x, y );
		}
	}
	pDC->SelectObject( pOldpen );
	if( m_dPU == 0 ) return;
	CBrush brush, *pOldbrush;
	if( m_dDGPU )
	{
		pOldbrush = (CBrush*)pDC->SelectStockObject(WHITE_BRUSH);
		dLog = log10( GetY( (float)m_dDGPU ) );

		if( bShowPu )
		{
			x = int( rect.left + log10( m_dDGPU ) * dTabx );
			y = int( rect.bottom - dLog * dTaby );
		}
		else
		{
			x = int( rect.left + log10( m_dAmp*m_dDGPU ) * dTabx );
			y = int( rect.bottom - dLog * dTaby );
		}
		pDC->Ellipse( x-4,y-4,x+4,y+4 );
		pDC->SelectObject( pOldbrush );
	}
	brush.CreateSolidBrush(RGB(255,0,0));
	pOldbrush = pDC->SelectObject(&brush);
	dLog = log10( GetY( (float)m_dPU ) );

	if( bShowPu )
	{
		x = int( rect.left + log10( m_dPU ) * dTabx );
		y = int( rect.bottom - dLog * dTaby );
	}
	else
	{
		x = int( rect.left + log10( m_dAmp*m_dPU ) * dTabx );
		y = int( rect.bottom - dLog * dTaby );
	}
	pDC->Ellipse( x-3,y-3,x+3,y+3 );
	pDC->SelectObject( pOldbrush );
}

double CCurveRecloser::GetY(float in)
{
	double y = 0;
	for( int i = 0 ; i < m_pRcdata.GetSize(); i ++ )
	{
		if( m_pRcdata[ i ].m_start <= in && m_pRcdata[ i ].m_end >= in )
			y = ( m_pRcdata[ i ].m_a / ( pow( in, m_pRcdata[ i ].m_b ) + m_pRcdata[ i ].m_c ) + m_pRcdata[ i ].m_d ) * m_pRcdata[ i ].m_e + m_pRcdata[ i ].m_n;
	}
	if( y == 0 )
	{
		int i = m_pRcdata.GetSize()-1;
		y = ( m_pRcdata[ i ].m_a / ( pow( in, m_pRcdata[ i ].m_b ) + m_pRcdata[ i ].m_c ) + m_pRcdata[ i ].m_d ) * m_pRcdata[ i ].m_e + m_pRcdata[ i ].m_n;
	}
	return m_dTm*y*60+m_dTa;
}

void CCurveRecloser::ShowValue(CDC *pDC, CRect rect, double dTab, double x, BOOL bShowPu)
{
	int a, b;
	double dLog, dTabx, dTaby, value;
	dTabx = rect.Width() / dTab;
	dTaby = rect.Height() / dTab;


	//커브정보추가
	double dPU;

	if( bShowPu )
	{
		if( m_dmin > x || m_dmax < x ) return;

		value = GetY( (float)x );
		dLog = log10( value );
	}
	else
	{
		if( x < (m_dmin*m_dAmp) || x > (m_dmax*m_dAmp) )
			return;

		dPU = x/m_dAmp;
		value = GetY( (float)dPU );
		dLog = log10( value );
	}
	a = int( rect.left + log10( x ) * dTabx );
	b = int( rect.bottom - dLog * dTaby );
	if( rect.PtInRect( CPoint(a,b) ) == FALSE ) return;
	CBrush brush, *pOldbrush;
	brush.CreateSolidBrush( RGB( 0, 0, 0 ) );
	pOldbrush = pDC->SelectObject( &brush );

	pDC->MoveTo( rect.left, b );
	pDC->LineTo( a, b );
	pDC->LineTo( a, rect.bottom );

	CString strTmp;
	pDC->SetTextColor( RGB( 255, 255, 0 ) );
	pDC->SetBkMode( TRANSPARENT );

	pDC->Rectangle( rect.left - 70, b - 7, rect.left - 5, b + 7 );
	strTmp.Format(L"%.4lf", value );
	pDC->TextOut( rect.left - 70, b-6, strTmp );

	pDC->Rectangle( a, rect.bottom + 20, a + 60, rect.bottom + 36 );
	strTmp.Format(L"%.4lf", x );

	pDC->TextOut( a, rect.bottom + 21, strTmp );
	pDC->SetTextColor( RGB( 0, 0, 0 ) );
	pDC->SelectObject( pOldbrush );
}
//////////////////////////////////////////////////////////////////////
// CRelay Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurveRelay::CCurveRelay( double a, double b, double c, double d, double e, double n, double L)
{
	m_a = a, m_b = b, m_c = c, m_d = d, m_e = e, m_n = n, m_L = L;
	m_dPU = 0;
	//커브정보추가
	m_dTab = m_dCT = m_dAmp = 0.0;
}

CCurveRelay::~CCurveRelay()
{

}

void CCurveRelay::Draw(CDC *pDC, CRect rect, double dTab, BOOL bShowPu)
{
	int x, y;
	double dLog, dTabx, dTaby;
	dTabx = rect.Width() / dTab;
	dTaby = rect.Height() / dTab;

	CPen pen, *pOldpen;
	pen.CreatePen( PS_SOLID, 1, GetColor() );
	pOldpen = pDC->SelectObject( &pen );
	
	double i, dtab = 0.1;
	CString strTmp;
	//커브정보추가
	double dPU, dCurrent;

	if( bShowPu )
	{
		for( i = 1 ; i <= 500; i += dtab )//i는 고장전류야.
		{
			dLog = log10( GetY( i ) );
			x = int( rect.left + log10( i ) * dTabx );
			y = int( rect.bottom - dLog * dTaby );
			if( y < rect.top ) y = rect.top;
			if( x > rect.right ) continue;
			if( y > rect.bottom ) continue;
			if( i == 1 )
				pDC->MoveTo( x, y );
			else
				pDC->LineTo( x, y );

			if( i > 1000 ) dtab = 1000;
			else if( i > 100 ) dtab = 100;
			else if( i > 10 ) dtab = 10;
			else if( i > 2 ) dtab = 1;
		}
	}
	else
	{
		BOOL bStart = TRUE;
		int nStart = m_dCT*m_dTab;
		for( i = 1 ; i <= 10000; i += dtab )
		{
			//커브정보추가
			if( i < (m_dCT*m_dTab) )	continue;

			dPU = i / (m_dCT*m_dTab);
			dLog = log10( GetY( dPU ) );
			x = int( rect.left + log10( i ) * dTabx );
			y = int( rect.bottom - dLog * dTaby );


			if( y < rect.top ) y = rect.top;
			if( x > rect.right ) continue;
			if( y > rect.bottom )
			{
				pDC->LineTo( x, rect.bottom );
				break;
			}
			if( x < rect.left )	continue;

			if( bStart )
			{
				pDC->MoveTo( x, y );
				bStart = FALSE;
			}
			else
				pDC->LineTo( x, y );

			if( dPU > 1000 ) dtab = 1000;
			else if( dPU > 100 ) dtab = 100;
			else if( dPU > 10 ) dtab = 10;
			else if( dPU > 2 ) dtab = 1;
		}
	}
	pDC->SelectObject( pOldpen );
	if( m_dPU == 0 ) return;
	CBrush brush, *pOldbrush;
	if( m_dDGPU )
	{
		pOldbrush = (CBrush*)pDC->SelectStockObject(WHITE_BRUSH);
		dLog = log10( GetY( (float)m_dDGPU ) );

		if( bShowPu )
		{
			x = int( rect.left + log10( m_dDGPU ) * dTabx );
			y = int( rect.bottom - dLog * dTaby );
		}
		else
		{
			//커브정보추가
			double dAmp;
			dAmp = m_dAmp / m_dPU;
			x = int( rect.left + log10( dAmp * m_dDGPU ) * dTabx );
			y = int( rect.bottom - dLog * dTaby );
		}
		pDC->Ellipse( x-4,y-4,x+4,y+4 );
		pDC->SelectObject( pOldbrush );
	}
	brush.CreateSolidBrush(RGB(255,0,0));
	pOldbrush = pDC->SelectObject(&brush);
	dLog = log10( GetY( m_dPU ) );
	//커브정보추가
	if( bShowPu )
	{
		x = int( rect.left + log10( m_dPU ) * dTabx );
		y = int( rect.bottom - dLog * dTaby );
	}
	else
	{
		x = int( rect.left + log10( m_dAmp ) * dTabx );
		y = int( rect.bottom - dLog * dTaby );
	}
	pDC->Ellipse( x-3,y-3,x+3,y+3 );
	pDC->SelectObject( pOldbrush );
}

double CCurveRelay::GetY(double in)
{
	double y = ( m_a / ( m_b * pow( in, m_c ) - m_d ) + m_e ) * ( m_L + m_n );
/*	if( m_bSecond )
		return y;
	else*/
		return y*60;
}

void CCurveRelay::ShowValue(CDC *pDC, CRect rect, double dTab, double x, BOOL bShowPu)
{
	int a, b;
	double dLog, dTabx, dTaby, value;
	dTabx = rect.Width() / dTab;
	dTaby = rect.Height() / dTab;

	//커브정보추가
	double dPU;
	if( bShowPu )
	{
		if( x > 500 )	return;
		value = GetY( (float)x );
		dLog = log10( value );
	}
	else
	{
		dPU = x / (m_dCT*m_dTab);
		if( dPU < 1.0 || x > 10000 )
			return;
		value = GetY( (float)dPU );
		dLog = log10( value );
	}
	a = int( rect.left + log10( x ) * dTabx );
	b = int( rect.bottom - dLog * dTaby );
	if( rect.PtInRect( CPoint(a,b) ) == FALSE ) return;
	CBrush brush, *pOldbrush;
	brush.CreateSolidBrush( RGB( 0, 0, 0 ) );
	pOldbrush = pDC->SelectObject( &brush );

	pDC->MoveTo( rect.left, b );
	pDC->LineTo( a, b );
	pDC->LineTo( a, rect.bottom );

	CString strTmp;
	pDC->SetTextColor( RGB( 255, 255, 0 ) );
	pDC->SetBkMode( TRANSPARENT );

	pDC->Rectangle( rect.left - 70, b - 7, rect.left - 2, b + 7 );
	strTmp.Format(L"%.4lf", value );
	pDC->TextOut( rect.left - 70, b-6, strTmp );

	pDC->Rectangle( a, rect.bottom + 20, a + 60, rect.bottom + 36 );
	strTmp.Format(L"%.4lf", x );

	pDC->TextOut( a, rect.bottom + 21, strTmp );
	pDC->SetTextColor( RGB( 0, 0, 0 ) );
	pDC->SelectObject( pOldbrush );
}

//////////////////////////////////////////////////////////////////////
// CFuse Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurveFuse::CCurveFuse( double start, double end, double a, double b, double n)
{
	m_start = start, m_end = end, m_a = a, m_b = b, m_n = n;
	m_dAmp = 100;
}

CCurveFuse::~CCurveFuse()
{

}

void CCurveFuse::Draw(CDC *pDC, CRect rect, double dTab, BOOL bShowPu)
{
	if( bShowPu )	return;
	int x, y;
	double dLog, dTabx, dTaby;
	dTabx = rect.Width() / dTab;
	dTaby = rect.Height() / dTab;

	CPen pen, *pOldpen;
	pen.CreatePen( PS_SOLID, 1, GetColor() );
	pOldpen = pDC->SelectObject( &pen );
	
	double i, dtab = 0.1, dCurrent, dPU;
	CString strTmp;
	if( bShowPu )
	{
		for( i = m_start ; i < m_end; i += dtab )
		{
			dLog = log10( GetY( i ) );
			x = int( rect.left + log10( i ) * dTabx );
			if( m_bSecond )
			{
				if( i <= 50)
					y = int( rect.bottom - dLog * dTaby );
			}
			else
				y = int( rect.bottom - dLog * dTaby );
			if( y < rect.top ) y = rect.top;
			if( x > rect.right ) continue;
			if( y > rect.bottom )
			{
				y = rect.bottom;
				pDC->LineTo( x, y );
				break;
			}
			if( i == m_start )
				pDC->MoveTo( x, y );
			else
				pDC->LineTo( x, y );

			if( i > 1000 ) dtab = 10;
			else if( i > 100 ) dtab = 100;
			else if( i > 20 ) dtab = 10;
			else if( i > 2 ) dtab = 1;
		}
	}
	else
	{
		BOOL bStart = TRUE;
		for( i = 1 ; i <= 10000; i += dtab )
		{
			//커브정보추가
			dPU = i;
			if( dPU < m_start )		continue;
			dLog = log10( GetY( dPU ) );
			x = int( rect.left + log10( i ) * dTabx );
			y = int( rect.bottom - dLog * dTaby );


			if( y < rect.top ) y = rect.top;
			if( x > rect.right ) continue;
			if( y > rect.bottom ) 
			{
				y = rect.bottom;
				pDC->LineTo( x, y );
				break;
			}
			if( x < rect.left )	continue;

			if( bStart )
			{
				pDC->MoveTo( x, y );
				bStart = FALSE;
			}
			else
				pDC->LineTo( x, y );

			if( i > 1000 ) dtab = 10;
			else if( i > 100 ) dtab = 100;
			else if( i > 20 ) dtab = 10;
			else if( i > 2 ) dtab = 1;
		}
	}
	pDC->SelectObject( pOldpen );
}

double CCurveFuse::GetY(double in)
{
	double y = m_b / ( pow( in, m_a ) + m_n );
/*	if( m_bSecond )
		return y;
	else*/
		return y*60;
}

void CCurveFuse::ShowValue(CDC *pDC, CRect rect, double dTab, double x, BOOL bShowPu)
{
	if( bShowPu )	return;
	int a, b;
	double dLog, dTabx, dTaby, value;
	dTabx = rect.Width() / dTab;
	dTaby = rect.Height() / dTab;

	double dPU;
	if( bShowPu )
	{
		value = GetY( (float)x );
		dLog = log10( value );
	}
	else
	{
		dPU = x;
		if( dPU < m_start || x > m_end )
			return;
		value = GetY( (float)dPU );
		dLog = log10( value );
	}
	a = int( rect.left + log10( x ) * dTabx );
	b = int( rect.bottom - dLog * dTaby );
	if( rect.PtInRect( CPoint(a,b) ) == FALSE ) return;
	CBrush brush, *pOldbrush;
	brush.CreateSolidBrush( RGB( 0, 0, 0 ) );
	pOldbrush = pDC->SelectObject( &brush );

	pDC->MoveTo( rect.left, b );
	pDC->LineTo( a, b );
	pDC->LineTo( a, rect.bottom );

	CString strTmp;
	pDC->SetTextColor( RGB( 255, 255, 0 ) );
	pDC->SetBkMode( TRANSPARENT );

	pDC->Rectangle( rect.left - 60, b - 7, rect.left - 5, b + 7 );
	strTmp.Format(L"%.4lf", value );
	pDC->TextOut( rect.left - 60, b-6, strTmp );
	if( bShowPu )
	{
		pDC->Rectangle( a, rect.bottom + 20, a + 60, rect.bottom + 36 );
		strTmp.Format(L"%.4lf", x );
	}
	else
	{
		pDC->Rectangle( a, rect.bottom + 20, a + 80, rect.bottom + 36 );
		strTmp.Format(L"%.4lf", x );
	}

	pDC->TextOut( a, rect.bottom + 21, strTmp );
	pDC->SetTextColor( RGB( 0, 0, 0 ) );
	pDC->SelectObject( pOldbrush );
}
