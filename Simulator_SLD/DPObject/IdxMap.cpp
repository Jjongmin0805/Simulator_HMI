#include "pch.h"
#include "IdxMap.h"


CIdxMap::CIdxMap(void)
{
	m_dmaxx = m_dmaxy = 0;
	m_dminx = m_dminy = 999999999;
}


CIdxMap::~CIdxMap(void)
{
	for( int i = 0; i < m_pPolyArray.GetSize(); i++ )
		delete m_pPolyArray.GetAt( i );
}


void CIdxMap::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
		BYTE btIns;
		short i, nCnt;
		double x, y;
		CPolyInfo* pInfo;
		ar >> btIns;
		while( btIns != 255 )
		{
			ar >> nCnt;
			pInfo = new CPolyInfo();
			for( i = 0; i < nCnt; i++ )
			{
				ar >> x >> y;
				pInfo->AddPoint( x, y );
				if( m_dmaxx < x ) m_dmaxx = x;
				if( m_dmaxy < y ) m_dmaxy = y;
				if( m_dminx > x ) m_dminx = x;
				if( m_dminy > y ) m_dminy = y;
			}
			m_pPolyArray.Add( pInfo );
			ar >> btIns;
		}
	}
}


void CIdxMap::DrawNavi(CDC* pDC, CRect rect)
{
	CDPoint ptCenNavi;
	double dx, dy, dZoomNavi;

	pDC->SetBkMode( TRANSPARENT );

	dx = rect.Width() / ( m_dmaxx - m_dminx );
	dy = rect.Height() / ( m_dmaxy - m_dminy );
	dZoomNavi = ( dx > dy ? dy : dx );

	CPoint pt = rect.CenterPoint();

	ptCenNavi.dx = m_dminx + ( m_dmaxx - m_dminx ) / 2.;
	ptCenNavi.dy = m_dminy + ( m_dmaxy - m_dminy ) / 2.;

	if( m_pPolyArray.GetSize() )
	{
		POINT* scrPts;
		CPen pen, *pOldpen;
		pen.CreatePen( PS_SOLID, 0, RGB( 150,150,150 ) );
		pOldpen = pDC->SelectObject( &pen );
		CPolyInfo* pInfo;
		for( int i = 0; i < m_pPolyArray.GetSize(); i++ )
		{
			pInfo = m_pPolyArray.GetAt(i);
			scrPts = Relocation(pInfo, dZoomNavi, &ptCenNavi, pt);
			pDC->Polygon( scrPts, pInfo->m_pPolyArr.GetSize() );
			free( scrPts );
		}
		pDC->SelectObject( pOldpen );
	}
}


POINT* CIdxMap::Relocation(CPolyInfo* pInfo, double dzoom, CDPoint* pCen, CPoint ptCen)
{
	POINT* pPts = (POINT*)malloc(sizeof(POINT) * pInfo->m_pPolyArr.GetSize());
	POINT* dummyPt = pPts;
	CDPoint* pdp;

	for(int i = 0; i < pInfo->m_pPolyArr.GetSize(); i++, dummyPt++)
	{
		pdp = pInfo->m_pPolyArr.GetAt( i );
		dummyPt->x = LONG((pdp->dx - pCen->dx) * dzoom + 0.5) + ptCen.x;
		dummyPt->y = LONG((pCen->dy - pdp->dy) * dzoom + 0.5) + ptCen.y;
	}
	return pPts;
}


CDPoint* CIdxMap::NaviLBtnDown(CRect rect, CPoint point)
{
	double dx, dy, dratio, dCenx, dCeny;
	CDPoint* pDP = new CDPoint();

	dx = (m_dmaxx - m_dminx) / double(rect.Width());
	dy = (m_dmaxy - m_dminy) / double(rect.Height());
	dratio = ( dx < dy ? dy : dx );
	
	dCenx = m_dminx + ( m_dmaxx - m_dminx ) / 2.;
	dCeny = m_dminy + ( m_dmaxy - m_dminy ) / 2.;
	dx = dCenx + (point.x-rect.CenterPoint().x) * dratio;// + 확대축소 비율에 따른 증가값..;
	dy = dCeny - (point.y-rect.CenterPoint().y) * dratio;// + 확대축소 비율에 따른 증가값..;
	pDP->dx = dx;
	pDP->dy = dy;
	return pDP;
}

void CIdxMap::DrawNaviRect(CDC* pDC, CRect rect, CDPoint* pLT, CDPoint* pRB)
{
	if( m_pPolyArray.GetSize() == 0 ) return;
	//화면크기의 실좌표를 구한다.
	CPoint ptCen = rect.CenterPoint();
	//나비영역으로 재계산.
	CRect rectNavi;
	CPoint pp = rect.CenterPoint();
	double dx1, dy1, dx2, dy2, dx, dy, dZoom;
	//1.현재계산된 화면영역의 가운데점을 생성한다.
	//이변수는 정가운데에서 떨어진 거리만 계산한 변수.
	dx = rect.Width() / ( m_dmaxx - m_dminx );
	dy = rect.Height() / ( m_dmaxy - m_dminy );
	dZoom = ( dx > dy ? dy : dx );
	dx1 = ( pLT->dx - (m_dminx + ( m_dmaxx - m_dminx ) / 2.) );
	dy1 = ( (m_dminy + ( m_dmaxy - m_dminy ) / 2.) - pLT->dy );
	dx2 = ( pRB->dx - (m_dminx + ( m_dmaxx - m_dminx ) / 2.) );
	dy2 = ( (m_dminy + ( m_dmaxy - m_dminy ) / 2.) - pRB->dy );

	rectNavi.left  = int( dx1*dZoom+0.5 ) + pp.x;
	rectNavi.top   = int( dy1*dZoom+0.5 ) + pp.y;
	rectNavi.right = int( dx2*dZoom+0.5 ) + pp.x;
	rectNavi.bottom= int( dy2*dZoom+0.5 ) + pp.y;
	//
	CPen *pOldPenR, penR;
	CBrush *pOldBrushR;
	penR.CreatePen( PS_SOLID, 1, RGB( 255, 0, 0 ) ); // 두께 1, 빨간색 테두리
	pOldPenR = pDC->SelectObject( &penR );
	pOldBrushR = (CBrush*)pDC->SelectStockObject( NULL_BRUSH ); // 빈 내부
// 	pDC->FrameRect( rect, pOldBrushR );

	// 빨간색 영역 표시
	pDC->Rectangle( rectNavi );
	CPoint ptCenNavi = rectNavi.CenterPoint();
	// 십자표시
	pDC->MoveTo( ptCenNavi.x-7, ptCenNavi.y );
	pDC->LineTo( ptCenNavi.x+7, ptCenNavi.y );
	pDC->MoveTo( ptCenNavi.x, ptCenNavi.y-7 );
	pDC->LineTo( ptCenNavi.x, ptCenNavi.y+7 );

	pDC->SelectObject(pOldPenR);
	pDC->SelectObject(pOldBrushR);
}

CRect CIdxMap::GetNaviRect(CRect rect, CDPoint* pLT, CDPoint* pRB)
{
	CRect rectNavi(0, 0, 0, 0);

	if (m_pPolyArray.GetSize() == 0)	return rectNavi;
	//화면크기의 실좌표를 구한다.
	CPoint ptCen = rect.CenterPoint();
	//나비영역으로 재계산.
	CPoint pp = rect.CenterPoint();
	double dx1, dy1, dx2, dy2, dx, dy, dZoom;
	//1.현재계산된 화면영역의 가운데점을 생성한다.
	//이변수는 정가운데에서 떨어진 거리만 계산한 변수.
	dx = rect.Width() / (m_dmaxx - m_dminx);
	dy = rect.Height() / (m_dmaxy - m_dminy);
	dZoom = (dx > dy ? dy : dx);
	dx1 = (pLT->dx - (m_dminx + (m_dmaxx - m_dminx) / 2.));
	dy1 = ((m_dminy + (m_dmaxy - m_dminy) / 2.) - pLT->dy);
	dx2 = (pRB->dx - (m_dminx + (m_dmaxx - m_dminx) / 2.));
	dy2 = ((m_dminy + (m_dmaxy - m_dminy) / 2.) - pRB->dy);
	rectNavi.left = int(dx1*dZoom + 0.5) + pp.x;
	rectNavi.top = int(dy1*dZoom + 0.5) + pp.y;
	rectNavi.right = int(dx2*dZoom + 0.5) + pp.x;
	rectNavi.bottom = int(dy2*dZoom + 0.5) + pp.y;

	return rectNavi;

}
