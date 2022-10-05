#include "pch.h"
#include "PolyInfo.h"


CPolyInfo::CPolyInfo(void)
{
	m_nTogi = 0;
}


CPolyInfo::~CPolyInfo(void)
{
	for( int i = 0; i < m_pPolyArr.GetSize(); i++ )
		delete m_pPolyArr.GetAt( i );
}


void CPolyInfo::AddPoint(double dx, double dy)
{
	CDPoint* dpd = new CDPoint();
	dpd->dx = dx;
	dpd->dy = dy;
	m_pPolyArr.Add( dpd );
}

void CPolyInfo::Draw(CDC* pDC, double dzoom, CDPoint* pCen, CPoint ptCen)
{
	POINT* scrPts;
	CPen pen, *pOldpen;
	CBrush brush, *pOldbrush;
	if( m_pPolyArr.GetSize() )
	{
		COLORREF color;
		pen.CreatePen( PS_SOLID, 0, RGB( 150,150,150 ) );
		pOldpen = pDC->SelectObject( &pen );
		//1:녹지, 2:주택, 3:상업, 4:산업, 5:공공
		if( m_nTogi == 1 )
			color = RGB(196,226,185);
		else if( m_nTogi == 2 )
			color = RGB(226,220,185);
		else if( m_nTogi == 3 )
			color = RGB(226,185,207);
		else if( m_nTogi == 4 )
			color = RGB(220,185,226);
		else if( m_nTogi == 5 )
			color = RGB(225,185,185);
		else
			color = RGB(255,255,255);

		brush.CreateSolidBrush(color);
		pOldbrush = pDC->SelectObject( &brush );

		scrPts = Relocation(dzoom, pCen, ptCen);
		pDC->Polygon( scrPts, m_pPolyArr.GetSize() );
		free( scrPts );

		pDC->SelectObject( pOldpen );
		pDC->SelectObject(pOldbrush);
	}
}

POINT* CPolyInfo::Relocation(double dzoom, CDPoint* pCen, CPoint ptCen)
{
	POINT* pPts = (POINT*)malloc(sizeof(POINT) * m_pPolyArr.GetSize());
	POINT* dummyPt = pPts;
	CDPoint* pdp;

	for(int i = 0; i < m_pPolyArr.GetSize(); i++, dummyPt++)
	{
		pdp = m_pPolyArr.GetAt( i );
		dummyPt->x = LONG((pdp->dx - pCen->dx) * dzoom + 0.5) + ptCen.x;
		dummyPt->y = LONG((pCen->dy - pdp->dy) * dzoom + 0.5) + ptCen.y;
	}
	return pPts;
}
