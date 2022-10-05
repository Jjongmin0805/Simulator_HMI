#include "pch.h"
#include "GisSec.h"

CGisSec::CGisSec()
{
}

CGisSec::~CGisSec()
{
	for (int i = 0; i < m_pPoleArr.GetSize(); i++)
		delete m_pPoleArr.GetAt(i);
	m_pPoleArr.RemoveAll();
}

void CGisSec::Draw(CDC* BufferDC, int nSize, double dZoom, double pCenX, double pCenY, CPoint ptCen)
{
	if (m_nDbID == 0)
		return;

	CPen							pen, *pOldpen;
	if (m_nOverHead == 0)			
		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	else							
		pen.CreatePen(PS_SOLID, 2, RGB(129, 81, 54));

	pOldpen = BufferDC->SelectObject(&pen);

	int i, nCnt;
	POINT* pPts, *dummyPt;

	CDPoint ptPrev, ptCurr;
	nCnt = m_pPoleArr.GetSize();
	pPts = (POINT*)malloc(sizeof(POINT) * nCnt);
	dummyPt = pPts;

	CPole* pPole;
	for (i = 0; i < m_pPoleArr.GetSize(); i++, dummyPt++)
	{
		pPole = m_pPoleArr.GetAt(i);
		ptCurr.dx = pPole->m_dPoint.dx;
		ptCurr.dy = pPole->m_dPoint.dy;
		if (i == 0)
		{
			ptPrev.dx = ptCurr.dx;
			ptPrev.dy = ptCurr.dy;
		}

		if (fabs(ptPrev.dx - ptCurr.dx) > 1000. || fabs(ptPrev.dy - ptCurr.dy) > 1000. )
		{
			ptCurr.dx = ptPrev.dx;
			ptCurr.dy = ptPrev.dy;
		}

		dummyPt->x = LONG((ptCurr.dx - pCenX) * dZoom + 0.5) + ptCen.x;
		dummyPt->y = LONG((pCenY - ptCurr.dy) * dZoom + 0.5) + ptCen.y;

	}
	BufferDC->Polyline(pPts, nCnt);

	BufferDC->SelectObject(pOldpen);
	free(pPts);
}
