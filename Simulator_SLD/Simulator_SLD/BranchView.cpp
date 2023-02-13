// BranchView.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "BranchView.h"
#include "MainFrm.h"

// CBranchView
CBranchView::CBranchView()
{
	m_nDbID					= 0;
	m_szCeqID				= _T("");
	m_nOverHead				= 0;

	m_nNode1				= 0;
	m_nNode2				= 0;
	m_nPosX1				= 0;
	m_nPosY1				= 0;
	m_nPosX2				= 0;
	m_nPosY2				= 0;

	m_dRp					= 0;
	m_dR0					= 0;
	m_dXp					= 0;
	m_dX0					= 0;

	m_nLineTypeCd			= 0;
	m_dLengthReal			= 0;
	m_dLengthDisp			= 0;
	m_dLengthDisp2			= 0;
	m_dLoad					= 0;
	m_nDeadLineDepth		= 0;
	m_bNaviShow				= TRUE;
	m_pNext					= NULL;
	m_bFaultArea			= FALSE;

	m_bBoundarySelect		= FALSE;

// 	m_nFlowCount			= 0;
// 	m_Icons[0].LoadBitmap( IDB_BG_FLOW );
// 	m_Icons[1].LoadBitmap( IDB_MW_FLOW );
// 	m_Icons[2].LoadBitmap( IDB_MVAR_FLOW );
}

CBranchView::~CBranchView()
{
// 	m_Icons[0].DeleteObject();
// 	m_Icons[1].DeleteObject();
// 	m_Icons[2].DeleteObject();

	if( m_pNext )
	{
		delete				m_pNext;
		m_pNext				= NULL;
	}

	for (int i = 0; i < m_ptArr.GetSize(); i++)
		delete m_ptArr.GetAt(i);
	m_ptArr.RemoveAll();

	for (int i = 0; i < m_pZPArray.GetSize(); i++)
		delete m_pZPArray.GetAt(i);
	m_pZPArray.RemoveAll();
}

void CBranchView::RemoveData()
{
	if( m_pNext )
	{
		delete				m_pNext;
		m_pNext				= NULL;
	}

	for (int i = 0; i < m_ptArr.GetSize(); i++)
		delete m_ptArr.GetAt(i);
	m_ptArr.RemoveAll();

	for (int i = 0; i < m_pZPArray.GetSize(); i++)
		delete m_pZPArray.GetAt(i);
	m_pZPArray.RemoveAll();
}

// CBranchView 멤버 함수
void CBranchView::Serialize(CArchive& ar, double dVersion)
{
	if( ar.IsStoring() )
	{
		ar << m_nDbID << m_szCeqID << m_nOverHead << m_nNode1 << m_nNode2 << m_nPosX1 << m_nPosY1 << m_nPosX2 << m_nPosY2 << m_nLineTypeCd << m_dLengthReal << m_dLengthDisp << m_dLengthDisp2;
		ar << m_dRp << m_dR0 << m_dXp << m_dX0 << m_dLoad << m_nDeadLineDepth << m_bNaviShow << m_bFaultArea;

		if( m_pNext )
		{
			ar << TRUE;
			m_pNext->Serialize( ar, dVersion );
		}
		else
		{
			ar << FALSE;
		}
	}
	else
	{
		ar >> m_nDbID >> m_szCeqID >> m_nOverHead >> m_nNode1 >> m_nNode2 >> m_nPosX1 >> m_nPosY1 >> m_nPosX2 >> m_nPosY2 >> m_nLineTypeCd >> m_dLengthReal >> m_dLengthDisp >> m_dLengthDisp2;
		ar >> m_dRp >> m_dR0 >> m_dXp >> m_dX0 >> m_dLoad >> m_nDeadLineDepth >> m_bNaviShow >> m_bFaultArea;

		BOOL bNext;
		ar >> bNext;

		if( bNext )
		{
			if( m_pNext == NULL )									//NULL이 아닐리가 없다!
			{
				m_pNext												= new CBranchView();
				m_pNext->Serialize( ar, dVersion );
			}
		}
	}
}

void CBranchView::Draw(CDC* BufferDC, double dScale, int nShowOption, BOOL bFirst, BOOL bPrint)
{
	if( m_nDbID > 0 )
	{
		CPoint															ptFwdScale, ptBwdScale;
		CPen															pen, *pOldpen;
		int																nWidth;

		ptFwdScale.x													= m_nPosX1 * dScale;
		ptFwdScale.y													= m_nPosY1 * dScale;
		ptBwdScale.x													= m_nPosX2 * dScale;
		ptBwdScale.y													= m_nPosY2 * dScale;

		COLORREF													color;
		int nVVMF(0), nVVMB(0);
		nVVMF = GETVALUE(int, ("nd_dyn_uin"), ("ND_II_VVM"), m_nNDID[0]);
		nVVMB = GETVALUE(int, ("nd_dyn_uin"), ("ND_II_VVM"), m_nNDID[1]);
		if ((nVVMF == 2) && (nVVMB == 2))//탭변경구간(전원/부하측 모두 12600탭)
		{
			if( m_nDeadLineDepth == 2000)								{color = RGB(   0, 150,   0 );				nWidth = 3;}//부하절체
			else if( m_nDeadLineDepth == 1000 )							{color = RGB( 255, 125,  55 );				nWidth = 3;}//고장구간
			else if( m_nDeadLineDepth > 0 )								{color = RGB( 200,   0,   0 );				nWidth = 1;}//사선구간
			else														{color = RGB( 255, 255,   0 );				nWidth = 1;}//활선구간
		}
		else if (nVVMF == 2)//탭변경구간(전원측만 12600탭)
		{
			if( m_nDeadLineDepth == 2000)								{color = RGB(   0, 150,   0 );				nWidth = 3;}//부하절체
			else if( m_nDeadLineDepth == 1000 )							{color = RGB( 255, 125,  55 );				nWidth = 3;}//고장구간
			else if( m_nDeadLineDepth > 0 )								{color = RGB( 200,   0,   0 );				nWidth = 1;}//사선구간
			else//활선구간
			{
				color = RGB( 255, 255,   0 );							nWidth = 1;

				if (m_nOverHead == 0)									pen.CreatePen(PS_SOLID, nWidth, color);
				else													pen.CreatePen(PS_DOT, nWidth, color);
				pOldpen													= BufferDC->SelectObject(&pen);

				CPoint													ptHalf;
				ptHalf.x												= (ptFwdScale.x + ptBwdScale.x) / 2;
				ptHalf.y												= (ptFwdScale.y + ptBwdScale.y) / 2;

				BufferDC->MoveTo(ptFwdScale);
				BufferDC->LineTo(ptHalf);

				ptFwdScale												= ptHalf;


				BufferDC->SelectObject(pOldpen);
				pen.DeleteObject();

				color = RGB(0, 255, 255);
			}
		}
		else if (nVVMB == 2)//탭변경구간(부하측만 12600탭)
		{
			if( m_nDeadLineDepth == 2000)								{color = RGB(   0, 150,   0 );				nWidth = 3;}//부하절체
			else if( m_nDeadLineDepth == 1000 )							{color = RGB( 255, 125,  55 );				nWidth = 3;}//고장구간
			else if( m_nDeadLineDepth > 0 )								{color = RGB( 200,   0,   0 );				nWidth = 1;}//사선구간
			else//활선구간
			{
				color = RGB(255, 255, 0);								nWidth = 1;

				if (m_nOverHead == 0)									pen.CreatePen(PS_SOLID, nWidth, color);
				else													pen.CreatePen(PS_DOT, nWidth, color);
				pOldpen													= BufferDC->SelectObject(&pen);

				CPoint													ptHalf;
				ptHalf.x												= (ptFwdScale.x + ptBwdScale.x) / 2;
				ptHalf.y												= (ptFwdScale.y + ptBwdScale.y) / 2;

				BufferDC->MoveTo(ptHalf);
				BufferDC->LineTo(ptBwdScale);

				ptBwdScale												= ptHalf;

				BufferDC->SelectObject(pOldpen);
				pen.DeleteObject();

				color = RGB(0, 255, 255);
			}
		}
		else
		{
			if( m_nDeadLineDepth == 2000)								{color = RGB(   0, 150,   0 );				nWidth = 3;}//부하절체
			else if( m_nDeadLineDepth == 1000 )							{color = RGB( 255, 125,  55 );				nWidth = 3;}//고장구간
			else if( m_nDeadLineDepth > 0 )								{color = RGB( 200,   0,   0 );				nWidth = 1;}//사선구간
			else														{color = RGB(   0, 255, 255 );				nWidth = 1;}//활선구간
		}

		if( m_nOverHead == 0 )			pen.CreatePen( PS_SOLID, nWidth, color );
		else							pen.CreatePen( PS_DOT, nWidth, color );

		pOldpen							= BufferDC->SelectObject( &pen );

		BufferDC->MoveTo( ptFwdScale );
		BufferDC->LineTo( ptBwdScale );

		BufferDC->SelectObject(pOldpen);
		pen.DeleteObject();

		//다시 원래좌표로 돌려놓자..
		ptFwdScale.x = m_nPosX1 * dScale;
		ptFwdScale.y = m_nPosY1 * dScale;
		ptBwdScale.x = m_nPosX2 * dScale;
		ptBwdScale.y = m_nPosY2 * dScale;

		int nLNSECIdx(0), nLINETYPEIdx(0), nLNSECHISNOTSRCH(0);
		nLNSECIdx = GETVALUE(int, ("br_sta"), ("br_ii_equ"), m_nDbID);

		nLNSECHISNOTSRCH = GETVALUE(int, ("lnsec_dyn_uin"), ("lnsec_his_notsrch"), nLNSECIdx);
		if ( nLNSECHISNOTSRCH )
		{
			Graphics												graphics(*BufferDC);
			Gdiplus::Pen											drawLinePen(Gdiplus::Color(95, 255, 29, 43), 10.0f);
			Gdiplus::PointF											point1, point2;
			point1													= Gdiplus::PointF((REAL)ptFwdScale.x, (REAL)ptFwdScale.y);
			point2													= Gdiplus::PointF((REAL)ptBwdScale.x, (REAL)ptBwdScale.y);

			graphics.DrawLine(&drawLinePen, point1, point2);
		}
		else if( m_bBoundarySelect )
		{
			Graphics												graphics(*BufferDC);
			Gdiplus::Pen											drawLinePen(Gdiplus::Color(95, 255, 255, 0), 10.0f);
			Gdiplus::PointF											point1, point2;
			point1													= Gdiplus::PointF((REAL)ptFwdScale.x, (REAL)ptFwdScale.y);
			point2													= Gdiplus::PointF((REAL)ptBwdScale.x, (REAL)ptBwdScale.y);

			graphics.DrawLine(&drawLinePen, point1, point2);
		}

		if (dScale >= SHOW_TEXT_SCALE)
		{
			if (((CMainFrame *)AfxGetApp()->GetMainWnd())->GetShowSecMode())
			{
				if (m_nDbID > 0)
				{
					nLINETYPEIdx = GETVALUE(int, ("lnsec_sta"), ("lnsec_type_id"), nLNSECIdx);
					if (nLINETYPEIdx < 1) nLINETYPEIdx = 1;

					CRect														rect;
					double														dLength;
					CString														szData, szPhase, szNeut;
					dLength = GETVALUE(double, ("lnsec_sta"), ("lnsec_length"), nLNSECIdx);

					szPhase = GETSTRING(("linetype_code_sta"), ("linetype_pha_nm"), nLINETYPEIdx);
					szNeut = GETSTRING(("linetype_code_sta"), ("linetype_neu_nm"), nLINETYPEIdx);
					szData.Format(_T("%s\n%s"), szPhase, szNeut);

					if( bPrint )
						BufferDC->SetTextColor(RGB(0, 0, 0));
					else
						BufferDC->SetTextColor(RGB(255, 255, 255));
					
					rect.SetRect((ptFwdScale.x + ptBwdScale.x) / 2 - 50, (ptFwdScale.y + ptBwdScale.y) / 2 - 25, (ptFwdScale.x + ptBwdScale.x) / 2 + 50, (ptFwdScale.y + ptBwdScale.y) / 2);
					BufferDC->DrawText(szData, rect, DT_CENTER);

					szData.Format(_T("%.3lf[km]"), dLength);
					rect.SetRect((ptFwdScale.x + ptBwdScale.x) / 2 - 50, (ptFwdScale.y + ptBwdScale.y) / 2 + 5, (ptFwdScale.x + ptBwdScale.x) / 2 + 50, (ptFwdScale.y + ptBwdScale.y) / 2 + 20);
					BufferDC->DrawText(szData, rect, DT_CENTER);
				}
			}
			else
			{
				double dFault_value[4] = { 0, };
				dFault_value[0] = GETVALUE(double, ("gbr_dyn_scao"), ("GBR_FLT_PA_C"), m_nDbID);
				dFault_value[1] = GETVALUE(double, ("gbr_dyn_scao"), ("GBR_FLT_PB_C"), m_nDbID);
				dFault_value[2] = GETVALUE(double, ("gbr_dyn_scao"), ("GBR_FLT_PC_C"), m_nDbID);
				dFault_value[3] = GETVALUE(double, ("gbr_dyn_scao"), ("GBR_FLT_PN_C"), m_nDbID);

				if (((abs(dFault_value[0]) + abs(dFault_value[1]) + abs(dFault_value[2]) + abs(dFault_value[3])) > 0) && (nShowOption & 1))
				{
					BufferDC->SetTextColor(RGB(0, 0, 0));

					CRect														rect;
					CString														szFaultVal;

					CBrush brush, *pOldbrush;
					brush.CreateSolidBrush(RGB(255, 240, 0));
					pOldbrush = BufferDC->SelectObject(&brush);

					CPoint pp[5];
					pp[0] = CPoint(ptBwdScale.x + 10, ptBwdScale.y - 20);
					pp[1] = CPoint(ptBwdScale.x + 10, ptBwdScale.y - 80);
					pp[2] = CPoint(ptBwdScale.x + 75, ptBwdScale.y - 80);
					pp[3] = CPoint(ptBwdScale.x + 75, ptBwdScale.y - 25);
					pp[4] = CPoint(ptBwdScale.x + 20, ptBwdScale.y - 25);
					BufferDC->Polygon(pp, 5);

					szFaultVal.Format(_T("A:%7.1lf\nB:%7.1lf\nC:%7.1lf\nN:%7.1lf"), dFault_value[0], dFault_value[1], dFault_value[2], dFault_value[3]);
					rect.SetRect(ptBwdScale.x + 10, ptBwdScale.y - 75, ptBwdScale.x + 70, ptBwdScale.y + 20);
					BufferDC->DrawText(szFaultVal, rect, DT_RIGHT);

					if (bFirst)
					{
						pp[0] = CPoint(ptFwdScale.x + 10, ptFwdScale.y - 20);
						pp[1] = CPoint(ptFwdScale.x + 10, ptFwdScale.y - 80);
						pp[2] = CPoint(ptFwdScale.x + 75, ptFwdScale.y - 80);
						pp[3] = CPoint(ptFwdScale.x + 75, ptFwdScale.y - 25);
						pp[4] = CPoint(ptFwdScale.x + 20, ptFwdScale.y - 25);
						BufferDC->Polygon(pp, 5);

						szFaultVal.Format(_T("A:%7.1lf\nB:%7.1lf\nC:%7.1lf\nN:%7.1lf"), dFault_value[0], dFault_value[1], dFault_value[2], dFault_value[3]);
						rect.SetRect(ptFwdScale.x + 10, ptFwdScale.y - 75, ptFwdScale.x + 70, ptFwdScale.y + 20);
						BufferDC->DrawText(szFaultVal, rect, DT_RIGHT);
					}

					BOOL bReverse;

					if ((dFault_value[0] + dFault_value[1] + dFault_value[2]) > 0)
						bReverse = FALSE;
					else
						bReverse = TRUE;

					DrawFaultDirection(BufferDC, dScale, bReverse);

					BufferDC->SelectObject(pOldbrush);
				}
				else
				{
					if (nShowOption & 2)
					{
						int nGNDIdx;
						nGNDIdx = GETVALUE(int, ("nd_sta"), ("ND_II_GND"), m_nNDID[1]);

						dFault_value[0] = GETVALUE(double, ("gnd_dyn_scao"), ("GND_FC_3LL"), nGNDIdx);
						dFault_value[1] = GETVALUE(double, ("gnd_dyn_scao"), ("GND_FC_2LL"), nGNDIdx);
						dFault_value[2] = GETVALUE(double, ("gnd_dyn_scao"), ("GND_FC_1LG"), nGNDIdx);
						dFault_value[3] = GETVALUE(double, ("gnd_dyn_scao"), ("GND_FC_1LG_30OHM"), nGNDIdx);

						if ((abs(dFault_value[0]) + abs(dFault_value[1]) + abs(dFault_value[2]) + abs(dFault_value[3])) > 0)
						{
							if( bPrint )
								BufferDC->SetTextColor(RGB(0, 0, 0));
							else
								BufferDC->SetTextColor(RGB(255, 255, 255));

							CRect														rect;
							CString														szFaultVal;

							szFaultVal.Format(_T("%5.1lf\n%5.1lf\n%5.1lf\n%5.1lf"), dFault_value[0], dFault_value[1], dFault_value[2], dFault_value[3]);
							rect.SetRect(ptBwdScale.x + 10, ptBwdScale.y - 65, ptBwdScale.x + 45, ptBwdScale.y + 20);
							BufferDC->DrawText(szFaultVal, rect, DT_RIGHT);

							if (bFirst)
							{
								nGNDIdx = GETVALUE(int, ("nd_sta"), ("ND_II_GND"), m_nNDID[0]);

								dFault_value[0] = GETVALUE(double, ("gnd_dyn_scao"), ("GND_FC_3LL"), nGNDIdx);
								dFault_value[1] = GETVALUE(double, ("gnd_dyn_scao"), ("GND_FC_2LL"), nGNDIdx);
								dFault_value[2] = GETVALUE(double, ("gnd_dyn_scao"), ("GND_FC_1LG"), nGNDIdx);
								dFault_value[3] = GETVALUE(double, ("gnd_dyn_scao"), ("GND_FC_1LG_30OHM"), nGNDIdx);

								szFaultVal.Format(_T("%5.1lf\n%5.1lf\n%5.1lf\n%5.1lf"), dFault_value[0], dFault_value[1], dFault_value[2], dFault_value[3]);
								rect.SetRect(ptFwdScale.x + 10, ptFwdScale.y - 75, ptFwdScale.x + 45, ptFwdScale.y + 20);
								BufferDC->DrawText(szFaultVal, rect, DT_RIGHT);
							}
						}
					}
				}

				if (m_bFaultArea)
				{
					HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
					BufferDC->DrawIcon((ptFwdScale.x + ptBwdScale.x) / 2 - 16, (ptFwdScale.y + ptBwdScale.y) / 2 - 16, hIcon);
				}
			}
		}
	}
// 	if( m_pNext )
// 		m_pNext->Draw( BufferDC, dScale, nShowOption, FALSE, bPrint );
}

void CBranchView::DrawFaultDirection( CDC* BufferDC, double dScale, BOOL bReverse )
{
	double							dAngle;
	dAngle = atan2(double(m_nPosY2 - m_nPosY1), double(m_nPosX2 - m_nPosX1));
	CPoint							ptPos(0, 0);
	ptPos = CPoint(((m_nPosX1 + m_nPosX2) / 2)*dScale, ((m_nPosY1 + m_nPosY2) / 2) * dScale);

	if ( bReverse ) 
		dAngle += 3.14159265358979323846;

	CPoint																pts[7];
	pts[0] = RotatePoint(CPoint(ptPos.x - (10 * dScale), ptPos.y - (5 * dScale)), dAngle, ptPos );
	pts[1] = RotatePoint(CPoint(ptPos.x + ( 0 * dScale), ptPos.y - (5 * dScale)), dAngle, ptPos);
	pts[2] = RotatePoint(CPoint(ptPos.x + ( 0 * dScale), ptPos.y - (12 * dScale)), dAngle, ptPos);
	pts[3] = RotatePoint(CPoint(ptPos.x + (10 * dScale), ptPos.y), dAngle, ptPos);
	pts[4] = RotatePoint(CPoint(ptPos.x + ( 0 * dScale), ptPos.y + (12 * dScale)), dAngle, ptPos);
	pts[5] = RotatePoint(CPoint(ptPos.x + ( 0 * dScale), ptPos.y + (5 * dScale)), dAngle, ptPos);
	pts[6] = RotatePoint(CPoint(ptPos.x - (10 * dScale), ptPos.y + (5 * dScale)), dAngle, ptPos);

	BufferDC->Polygon(pts, 7);




















// 	CBitmap*						pOldBitmap;
// 	CDC								memdc;
// 
// 	if (m_nFlowCount != 0)
// 	{
// 		ptPos = RotatePoint(CPoint((m_nPosX1 + m_nFlowCount)*dScale, (m_nPosY1)*dScale), dAngle, CPoint(m_nPosX1*dScale, (m_nPosY1)*dScale));
// 		memdc.CreateCompatibleDC(pDC);
// 		pOldBitmap = memdc.SelectObject(&m_Icons[0]);
// 		BufferDC->BitBlt(ptPos.x - 5, ptPos.y - 5, 10, 10, &memdc, 0, 0, SRCCOPY);
// 		memdc.SelectObject(pOldBitmap);
// 		memdc.DeleteDC();
// 	}
// 
// 	if (m_nFlowCount == 0 || nSize <= (m_nFlowCount + (18 * dScale)))		m_nFlowCount = 18 * dScale;
// 	m_nFlowCount += 2;
// 
// 	ptPos = RotatePoint(CPoint((m_nPosX1 + m_nFlowCount)*dScale, (m_nPosY1)*dScale), dAngle, CPoint(m_nPosX1*dScale, (m_nPosY1)*dScale));
// 	memdc.CreateCompatibleDC(pDC);
// 	pOldBitmap = memdc.SelectObject(&m_Icons[1]);
// 	BufferDC->BitBlt(ptPos.x - 5, ptPos.y - 5, 10, 10, &memdc, 0, 0, SRCCOPY);
// 	memdc.SelectObject(pOldBitmap);
// 	memdc.DeleteDC();
}

void CBranchView::DrawMeasData(CDC* BufferDC, double dScale)
{
	CPoint								ptFwdScale, ptBwdScale;
	if( m_nDbID > 0 && m_nDeadLineDepth == 0 )
	{
		ShowMeasValue( BufferDC, dScale );
	}
	if( m_pNext )
		m_pNext->DrawMeasData( BufferDC, dScale );
}

void CBranchView::ShowMeasValue( CDC* BufferDC, double dScale )
{
	int																		nCbswIdx(0), nNodeType;
	nNodeType = GetFromCbswIdx(nCbswIdx);

	if( nCbswIdx == 0 )														return;
	if( GETVALUE( int, _T("cbsw_sta"), _T("cbsw_type"), nCbswIdx ) >= 4 )	return;

	int																		nDirection(0), nShift(0), nLeftAmp, nTopAmp, nLeftMW, nTopMW;
	UINT																	uStyleAmp, uStyleMW;

	if (m_nPosY1 == m_nPosY2)//Y축이 동일 
	{
		if (m_nPosX1 < m_nPosX2)
		{
			nDirection = 0;

			nLeftAmp = 0;
			nTopAmp = -10;
			uStyleAmp = DT_LEFT;

			nLeftMW = 0;
			nTopMW = -10;
			uStyleMW = DT_LEFT;
		}
		else
		{
			nDirection = 2;

			nLeftAmp = -55;
			nTopAmp = -10;
			uStyleAmp = DT_RIGHT;
	
			nLeftMW = -55;
			nTopMW = -10;
			uStyleMW = DT_RIGHT;
		}
	}
	else if (m_nPosX1 == m_nPosX2)//X축이 동일
	{
		if (m_nPosY1 < m_nPosY2)
		{
			nDirection = 1;

			nLeftAmp = -10;
			nTopAmp = 0;
			uStyleAmp = DT_LEFT;

			nLeftMW = -45;
			nTopMW = 0;
			uStyleMW = DT_RIGHT;

			nShift = 24;
		}
		else
		{
			nDirection = 3;

			nLeftAmp = -45;
			nTopAmp = (int)(18.*dScale);
			uStyleAmp = DT_RIGHT;

			nLeftMW = -10;
			nTopMW = (int)(18.*dScale);
			uStyleMW = DT_LEFT;
		}
	}
	else
	{
		nDirection															= -1;//방향에 상관없이 대각분기.
		nLeftAmp = nTopAmp = nLeftMW = nTopMW = 0;
		uStyleAmp = DT_CENTER;
		uStyleMW = DT_CENTER;
	}

	double																	dCalcA, dCalcMw, dPI = 3.141592654;
	//개폐기 계산값
	dCalcA																	= GETVALUE( double, _T("cbsw_dyn_rpfo"), _T("cbsw_parpfamp"), nCbswIdx );
	dCalcMw																	= GETVALUE( double, _T("cbsw_dyn_rpfo"), _T("cbsw_3prpfmw"), nCbswIdx ) * (1000);
// 
// 	dCalcA = 12354;
// 	dCalcMw = 36595;
// 	dCalcMvar = 0;
// 
	CString																	szData;
	CPoint																	ptCalcFlow[3];
	CPoint																	ptPosition;
	CBrush																	brush, *pOldbrush;
	double																	dAngle;
	dAngle																	= atan2(double(m_nPosY2-m_nPosY1), double(m_nPosX2-m_nPosX1));

	//빨간색화살표 제거 - 조성민(2023-02-08)
// 	if( ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetMeasValueOpt() & DISPLAY_SHOW_MW )
// 	{
// 		if(dCalcA >= 0 )//계측정방향(전류)
// 		{
// 			ptCalcFlow[0]													= RotatePoint(CPoint((m_nPosX1+50+nShift)*dScale, (m_nPosY1-15)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
// 			ptCalcFlow[1]													= RotatePoint(CPoint((m_nPosX1+40+nShift)*dScale, (m_nPosY1-25)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
// 			ptCalcFlow[2]													= RotatePoint(CPoint((m_nPosX1+40+nShift)*dScale, (m_nPosY1-5)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
// 
// 			brush.CreateSolidBrush( RGB( 255,0,0 ) );
// 			pOldbrush = BufferDC->SelectObject( &brush );
// 			BufferDC->Polygon(ptCalcFlow, 3 );
// 			BufferDC->SelectObject( pOldbrush );
// 			brush.DeleteObject();
// 		}
// 		else
// 		{
// 			ptCalcFlow[0]													= RotatePoint(CPoint((m_nPosX1+40+nShift)*dScale, (m_nPosY1-15)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
// 			ptCalcFlow[1]													= RotatePoint(CPoint((m_nPosX1+50+nShift)*dScale, (m_nPosY1-25)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
// 			ptCalcFlow[2]													= RotatePoint(CPoint((m_nPosX1+50+nShift)*dScale, (m_nPosY1-5)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
// 
// 			brush.CreateSolidBrush( RGB( 255,0,0 ) );
// 			pOldbrush = BufferDC->SelectObject( &brush );
// 			BufferDC->Polygon(ptCalcFlow, 3 );
// 			BufferDC->SelectObject( pOldbrush );
// 			brush.DeleteObject();
// 		}
// 	}

	if( ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetMeasValueOpt() & DISPLAY_SHOW_MVAR )
	{
		if (dCalcMw >= 0)//계산정방향(유효전력)
		{
			ptCalcFlow[0]													= RotatePoint(CPoint((m_nPosX1+50+nShift)*dScale, (m_nPosY1 + 15)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
			ptCalcFlow[1]													= RotatePoint(CPoint((m_nPosX1+40+nShift)*dScale, (m_nPosY1 + 25)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
			ptCalcFlow[2]													= RotatePoint(CPoint((m_nPosX1+40+nShift)*dScale, (m_nPosY1 + 5)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));

			brush.CreateSolidBrush(RGB(0, 255, 0));
			pOldbrush = BufferDC->SelectObject(&brush);
			BufferDC->Polygon(ptCalcFlow, 3);
			BufferDC->SelectObject(pOldbrush);
			brush.DeleteObject();
		}
		else
		{
			ptCalcFlow[0]													= RotatePoint(CPoint((m_nPosX1+40+nShift)*dScale, (m_nPosY1 + 15)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
			ptCalcFlow[1]													= RotatePoint(CPoint((m_nPosX1+50+nShift)*dScale, (m_nPosY1 + 25)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
			ptCalcFlow[2]													= RotatePoint(CPoint((m_nPosX1+50+nShift)*dScale, (m_nPosY1 + 5)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));

			brush.CreateSolidBrush(RGB(0, 255, 0));
			pOldbrush = BufferDC->SelectObject(&brush);
			BufferDC->Polygon(ptCalcFlow, 3);
			BufferDC->SelectObject(pOldbrush);
			brush.DeleteObject();
		}
	}

	if( ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetMeasValueOpt() & DISPLAY_SHOW_AMP && dScale >= SHOW_TEXT_SCALE)
	{
		CRect																rArea;

		ptPosition															= RotatePoint(CPoint((m_nPosX1+55+nShift)*dScale, (m_nPosY1-15)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
		rArea.left															= ptPosition.x + nLeftAmp;
		rArea.top															= ptPosition.y + nTopAmp;
		rArea.right															= rArea.left + 55;
		rArea.bottom														= rArea.top + 20;

		BufferDC->SetTextColor( RGB( 255, 180, 180 ) );
		szData.Format(_T("%.0lfA"), dCalcA);
		//////////////// 211025 조성민 수정
		BufferDC->DrawText(szData, rArea, uStyleAmp | DT_SINGLELINE | DT_VCENTER);

		ptPosition															= RotatePoint(CPoint((m_nPosX1+55+nShift)*dScale, (m_nPosY1+15)*dScale), dAngle, CPoint(m_nPosX1*dScale, m_nPosY1*dScale));
		rArea.left															= ptPosition.x + nLeftMW;
		rArea.top															= ptPosition.y + nTopMW;
		rArea.right															= rArea.left + 55;
		rArea.bottom														= rArea.top + 20;

		BufferDC->SetTextColor(RGB(0, 255, 255));
		szData.Format(_T("%.0lfkW"), abs(dCalcMw));
		//////////////// 211025 조성민 수정
		BufferDC->DrawText(szData, rArea, uStyleMW | DT_SINGLELINE | DT_VCENTER);
	}
}

void CBranchView::DrawNavi(CDC* BufferDC, double dRatioX, double dRatioY )
{
	if( m_bNaviShow )
	{
		CPoint							ptPosition1, ptPosition2;
		ptPosition1						= CPoint( m_nPosX1, m_nPosY1 );
		ptPosition1.x					*= dRatioX;
		ptPosition1.y					*= dRatioY;

		ptPosition2						= CPoint( m_nPosX2, m_nPosY2 );
		ptPosition2.x					*= dRatioX;
		ptPosition2.y					*= dRatioY;

		COLORREF						color;
		CPen							Pen, *pOldPen;
		if( m_nDeadLineDepth == 2000)								color = RGB(   0, 150,   0 );//부하절체
		else if( m_nDeadLineDepth == 1000 )							color = RGB( 255, 125,  55 );//고장구간
		else if( m_nDeadLineDepth > 0 )								color = RGB( 200,   0,   0 );//사선구간
		else														color = RGB( 255, 255,   0 );//활선구간
		Pen.CreatePen( PS_SOLID, 1, color );
		pOldPen							= (CPen*)BufferDC->SelectObject( &Pen );

		BufferDC->MoveTo( ptPosition1 );
		BufferDC->LineTo( ptPosition2 );

		BufferDC->SelectObject( pOldPen );
		Pen.DeleteObject();
	}
	if( m_pNext )
		m_pNext->DrawNavi( BufferDC, dRatioX, dRatioY );
}

void CBranchView::IncreaseLengthDisp(int node1, int node2, double dStep/*=1.0*/)
{
	double returnvalue = 0;
	if(node1 == m_nNode1 && node2 == m_nNode2)
	{
		m_dLengthDisp += dStep;	
	}
	else if(node2 == m_nNode1 && node1 == m_nNode2)
	{
		m_dLengthDisp += dStep;	
	}
	else
	{
		if( m_pNext != NULL )
			m_pNext->IncreaseLengthDisp(node1,node2,dStep);
	}

	return;
}

double CBranchView::GetLengthDisp(int node1, int node2)
{
	double returnvalue = 0;
	if(node1 == m_nNode1 && node2 == m_nNode2) 		return m_dLengthDisp;
	if(node2 == m_nNode1 && node1 == m_nNode2) 		return m_dLengthDisp;

	if( m_pNext != NULL )
		returnvalue = m_pNext->GetLengthDisp(node1,node2);

	return returnvalue;
}

void CBranchView::SetLengthDisp(int node1, int node2, double dLen)
{
	if(node1 == m_nNode1 && node2 == m_nNode2)		m_dLengthDisp = dLen; 
	if(node2 == m_nNode1 && node1 == m_nNode2)		m_dLengthDisp = dLen;

	if( m_pNext != NULL )
		m_pNext->SetLengthDisp(node1,node2,dLen);
}

// void CBranchView::Add( int nId, int node1, int node2, double lengthreal, int nLineType, int overheadcable, double dload, double dRp, double dR0, double dXp, double dX0 )
// {
// 	//if(m_pNext != NULL)
// 	if(m_pNext)
// 	{
// 		m_pNext->Add(nId, node1, node2, lengthreal, nLineType, overheadcable, dload, dRp, dR0, dXp, dX0);
// 	}
// 	else  // 널이면, 즉, 마지막 레코드이면
// 	{
// 		m_pNext									= new CBranchView();
// 		m_pNext->m_nDbID						= nId;
// 		m_pNext->m_nOverHead					= overheadcable;
// 		m_pNext->m_nNode1						= node1;
// 		m_pNext->m_nNode2						= node2;
// 		m_pNext->m_nLineTypeCd					= nLineType;
// 
// 		m_pNext->m_dLengthReal					= lengthreal;
// 		m_pNext->m_dLoad						= dload;
// 
// 		m_pNext->m_dRp							= dRp;
// 		m_pNext->m_dR0							= dR0;
// 		m_pNext->m_dXp							= dXp;
// 		m_pNext->m_dX0							= dX0;
// 
// 		if( lengthreal > 0 || (node1 > 0 && node2 > 0) )		
// 			m_pNext->m_dLengthDisp			= 1;
// 		else												
// 			m_pNext->m_dLengthDisp			= 0;
// 	}
// }

CBranchView* CBranchView::Add( int nId, int node1, int node2, int nNDIdx1, int nNDIdx2, double lengthreal, int nLineType, int overheadcable, double dload, double dRp, double dR0, double dXp, double dX0, CString szCeqID, int nDeadLineDepth, BOOL bNaviShow )
{
	//if(m_pNext != NULL)
	if(m_pNext)
	{
		return m_pNext->Add(nId, node1, node2, nNDIdx1, nNDIdx2, lengthreal, nLineType, overheadcable, dload, dRp, dR0, dXp, dX0, szCeqID, nDeadLineDepth, bNaviShow);
	}
	else  // 널이면, 즉, 마지막 레코드이면
	{
		m_pNext									= new CBranchView();
		m_pNext->m_nDbID						= nId;
		m_pNext->m_nNode1						= node1;
		m_pNext->m_nNode2						= node2;
		m_pNext->m_nNDID[0]						= nNDIdx1;
		m_pNext->m_nNDID[1]						= nNDIdx2;
		m_pNext->m_szCeqID						= szCeqID;
		m_pNext->m_nOverHead					= overheadcable;
		m_pNext->m_nLineTypeCd					= nLineType;

		m_pNext->m_dLengthReal					= lengthreal;
		m_pNext->m_dLoad						= dload;

		m_pNext->m_dRp							= dRp;
		m_pNext->m_dR0							= dR0;
		m_pNext->m_dXp							= dXp;
		m_pNext->m_dX0							= dX0;
		m_pNext->m_nDeadLineDepth				= nDeadLineDepth;

		if( lengthreal < 0 )					m_pNext->m_dLengthDisp = 0;
		else									m_pNext->m_dLengthDisp = 1;

		m_pNext->m_bNaviShow					= bNaviShow;

		return m_pNext;
	}
}

void CBranchView::Add( CBranchView* pBranchView )
{
	if ( m_pNext != NULL )
	{
		m_pNext->Add( pBranchView );
	}
	else
	{
		m_pNext									= pBranchView;
	}
}

void CBranchView::SetPosition(int node1, int node2, int posx1, int posy1, int posx2, int posy2)
{
	if(node1 == m_nNode1 && node2 == m_nNode2){
		ASSERT( m_nDbID != 25381 );
		m_nPosX1 = posx1;
		m_nPosY1 = posy1;
		m_nPosX2 = posx2;
		m_nPosY2 = posy2;
	}
	else if(node2 == m_nNode1 && node1 == m_nNode2){
		ASSERT( m_nDbID != 25381 );
		m_nPosX1 = posx2;
		m_nPosY1 = posy2;
		m_nPosX2 = posx1;
		m_nPosY2 = posy1;
	}

	if(m_pNext!=NULL)
	{
		m_pNext->SetPosition(node1,node2,posx1,posy1,posx2,posy2);
	}
}

void CBranchView::SetLength(int nID1, int nID2, double dLen)
{
	if(nID1 == m_nNode1 && nID2 == m_nNode2)
	{
		if( m_dLengthDisp == 1 ) m_dLengthDisp = dLen;
	}
	else if(nID2 == m_nNode1 && nID1 == m_nNode2){
		if( m_dLengthDisp == 1 ) m_dLengthDisp = dLen;
	}

	if(m_pNext!=NULL){
		m_pNext->SetLength( nID1, nID2, dLen );
	}
}

CBranchView* CBranchView::Copy()
{
	CBranchView*										pBranchView;
	pBranchView											= new CBranchView();

	pBranchView->m_nDbID								= m_nDbID;
	pBranchView->m_szCeqID								= m_szCeqID;
	pBranchView->m_nOverHead							= m_nOverHead;

	pBranchView->m_nNode1								= m_nNode1;
	pBranchView->m_nNode2								= m_nNode2;

	pBranchView->m_dRp									= m_dRp;
	pBranchView->m_dR0									= m_dR0;
	pBranchView->m_dXp									= m_dXp;
	pBranchView->m_dX0									= m_dX0;

	pBranchView->m_nLineTypeCd							= m_nLineTypeCd;
	pBranchView->m_dLengthReal							= m_dLengthReal;
	pBranchView->m_dLengthDisp							= m_dLengthDisp;
	pBranchView->m_dLoad								= m_dLoad;
	pBranchView->m_bNaviShow							= m_bNaviShow;
	pBranchView->m_bFaultArea							= m_bFaultArea;

	return pBranchView;
}

CBranchView* CBranchView::GetBranchView(int node1, int node2)
{
	if(node1 == m_nNode1 && node2 == m_nNode2)
	{
		return this;
	}
	else if(node2 == m_nNode1 && node1 == m_nNode2)
	{
		return this;
	}

	if(m_pNext!=NULL)
	{
		return m_pNext->GetBranchView(node1, node2);
	}

	return NULL;
}

CBranchView* CBranchView::GetBranchView2(int node)
{
	if (m_nNode2 == node)
		return this;

	if (m_pNext != NULL)
	{
		return m_pNext->GetBranchView2(node);
	}

	return NULL;
}

CBranchView* CBranchView::GetSelectBranchView(CPoint ptPosition, double dZoom)
{
	if( IsSelectArea(ptPosition, dZoom) )
		return this;

	if(m_pNext!=NULL)
	{
		return m_pNext->GetSelectBranchView(ptPosition, dZoom);
	}

	return NULL;
}

BOOL CBranchView::IsSelectArea( CPoint ptPosition, double dZoom )
{
	int				nPosX1, nPosY1, nPosX2, nPosY2;
	nPosX1			= m_nPosX1 * dZoom;
	nPosY1			= m_nPosY1 * dZoom;
	nPosX2			= m_nPosX2 * dZoom;
	nPosY2			= m_nPosY2 * dZoom;

	double			Angle1, Angle2, Anglediff, distA, distB, dRet, dCos, dSin;
	Angle1			= atan2(double(nPosY2-nPosY1), double(nPosX2-nPosX1)); 
	Angle2			= atan2(double(ptPosition.y-nPosY1),double(ptPosition.x-nPosX1)); 
	Anglediff		= fabs(Angle1-Angle2);

	distA			= sqrt( pow(double(nPosY2-nPosY1), 2) + pow(double(nPosX2-nPosX1), 2) );
	distB			= sqrt( pow(double(ptPosition.y-nPosY1), 2) + pow(double(ptPosition.x-nPosX1), 2) );

	dSin			= sin(Anglediff);
	dCos			= cos(Anglediff);

	dRet			= (fabs(distB)*dCos)/fabs(distA);
	if( (dRet >= 0) && (dRet <= 1) )
	{
		distA		= fabs(distB*dSin);

		if(distA < 5.0  )
			return TRUE;
	}

	return FALSE;
}

void CBranchView::DBSave( int nOffice, CString sztime, CString szSubstID, int nCBID, int nSLDMode )
{
// 	if( m_nNode1 != 0 && m_nNode2 != 0 )
// 	{
// 		CDBMng*								pDBMng = CDBMng::Instance();
// 		CString								szQuery;
// 
// 		szQuery.Format( _T("INSERT INTO IBNE6138 \
// 						   ( JURIS_OFFICE_CD,	CRE_YMD,	SUBST_IDTF,			DIST_LINE_ID,	AUTO_MODE,		LINE_IDTF,		FWD_SW_IDTF,	BWD_SW_IDTF,	WIKI_CD,		OVUN_CLSF,\
// 						   LINE_LENG,			NMPT_REST,	NMPT_RCTN,			IMAGE_REST,		IMAGE_RCTN,		FWD_X_POS,		FWD_Y_POS,		BWD_X_POS,		BWD_Y_POS ) VALUES \
// 						   ( '%d',				'%s',		'%s',				%d,				%d,				%d,				%d,				%d,				%d,				%d,\
// 						   %lf,				%lf,		%lf,				%lf,			%lf,			%d,				%d,				%d,				%d )"), 
// 						   nOffice,			sztime,		szSubstID,			nCBID,			nSLDMode,		m_nDbID,		m_nNode1,		m_nNode2,		m_nLineTypeCd,	m_nOverHead,
// 						   m_dLengthReal,		m_dRp,		m_dXp,				m_dR0,			m_dX0,			m_nPosX1,		m_nPosY1,		m_nPosX2,		m_nPosY2 );
// 		pDBMng->DBExcuteDW( szQuery );
// 	}
// 
// 	if( m_pNext )										m_pNext->DBSave( nOffice, sztime, szSubstID, nCBID, nSLDMode );
}

void CBranchView::DrawFlow(CDC* BufferDC, double dScale, CDC* pDC)
{
// 	if( m_nDbID > 0 && m_nDeadLineDepth == 0 )
// 	{
// 		double							dAngle;
// 		dAngle							= atan2(double(m_nPosY2-m_nPosY1), double(m_nPosX2-m_nPosX1)); 
// 
// 		CPoint							ptPos(0,0);
// 		int								nSize = (int)sqrt( pow((m_nPosX2-m_nPosX1), 2.) + pow((m_nPosY2-m_nPosY1), 2.) );
// 		
// 		CBitmap*						pOldBitmap;
// 		CDC								memdc;
// 
// 		if( m_nFlowCount != 0 )
// 		{
// 			ptPos						= RotatePoint( CPoint((m_nPosX1+m_nFlowCount)*dScale, (m_nPosY1)*dScale), dAngle, CPoint(m_nPosX1*dScale, (m_nPosY1)*dScale) );
// 			memdc.CreateCompatibleDC( pDC );
// 			pOldBitmap	= memdc.SelectObject( &m_Icons[0] );
// 			BufferDC->BitBlt( ptPos.x-5, ptPos.y-5, 10, 10, &memdc, 0, 0, SRCCOPY );
// 			memdc.SelectObject(pOldBitmap);
// 			memdc.DeleteDC();
// 		}
// 
// 		if( m_nFlowCount == 0 || nSize <= (m_nFlowCount+(18*dScale)) )		m_nFlowCount = 18*dScale;
// 		m_nFlowCount+=2;
// 
// 		ptPos							= RotatePoint( CPoint((m_nPosX1+m_nFlowCount)*dScale, (m_nPosY1)*dScale), dAngle, CPoint(m_nPosX1*dScale, (m_nPosY1)*dScale) );
// 		memdc.CreateCompatibleDC( pDC );
// 		pOldBitmap	= memdc.SelectObject( &m_Icons[1] );
// 		BufferDC->BitBlt( ptPos.x-5, ptPos.y-5, 10, 10, &memdc, 0, 0, SRCCOPY );
// 		memdc.SelectObject(pOldBitmap);
// 		memdc.DeleteDC();
// 	}
// 	if( m_pNext )
// 		m_pNext->DrawFlow( BufferDC, dScale, pDC );
}

CPoint	CBranchView::RotatePoint( CPoint ptCurrent, double dAngle, CPoint ptAxis )
{
	CPoint								ptChangePoint;
// 	double								dPi = 3.1415926535;
// 	double								dAngle;
// 	dAngle								= -90 * (m_nCrossMode%4);
// 
// 	ptChangePoint.x						= (int)floor((ptCurrent.x-ptAxis.x)*cos(dAngle/180.*dPi) - (ptCurrent.y-ptAxis.y)*sin(dAngle/180.*dPi)) + ptAxis.x;
// 	ptChangePoint.y						= (int)floor((ptCurrent.x-ptAxis.x)*sin(dAngle/180.*dPi) + (ptCurrent.y-ptAxis.y)*cos(dAngle/180.*dPi)) + ptAxis.y;

	ptChangePoint.x						= (int)floor((ptCurrent.x-ptAxis.x)*cos(dAngle) - (ptCurrent.y-ptAxis.y)*sin(dAngle) + 0.5) + ptAxis.x;
	ptChangePoint.y						= (int)floor((ptCurrent.x-ptAxis.x)*sin(dAngle) + (ptCurrent.y-ptAxis.y)*cos(dAngle) + 0.5) + ptAxis.y;

	return ptChangePoint;
}

int CBranchView::GetFromCbswIdx(int& nCbswIdx)
{
	int																	nNDIdx(0);
	nNDIdx																= m_nNDID[0];
	if( nNDIdx == 0 )													return 0;

	nCbswIdx														= GETVALUE( int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
	if( nCbswIdx )													return NDTYPE_SWITCH;

	nCbswIdx														= GETVALUE( int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);
	if( nCbswIdx )													return NDTYPE_SWITCH;

	return 0;
}

void CBranchView::SetGISPosition(int node1, int node2, CDPoint& dSLDDPoint1, CDPoint& dGISDPoint1, CDPoint& dSLDDPoint2, CDPoint& dGISDPoint2)
{
	if (node1 == m_nNode1 && node2 == m_nNode2) {
		m_pSLDDPoint1.dx = dSLDDPoint1.dx;
		m_pSLDDPoint1.dy = dSLDDPoint1.dy;
		m_pGISDPoint1.dx = dGISDPoint1.dx;
		m_pGISDPoint1.dy = dGISDPoint1.dy;

		m_pSLDDPoint2.dx = dSLDDPoint2.dx;
		m_pSLDDPoint2.dy = dSLDDPoint2.dy;
		m_pGISDPoint2.dx = dGISDPoint2.dx;
		m_pGISDPoint2.dy = dGISDPoint2.dy;

		return;
	}
	else if (node2 == m_nNode1 && node1 == m_nNode2) {
		m_pSLDDPoint1.dx = dSLDDPoint2.dx;
		m_pSLDDPoint1.dy = dSLDDPoint2.dy;
		m_pGISDPoint1.dx = dGISDPoint2.dx;
		m_pGISDPoint1.dy = dGISDPoint2.dy;

		m_pSLDDPoint2.dx = dSLDDPoint1.dx;
		m_pSLDDPoint2.dy = dSLDDPoint1.dy;
		m_pGISDPoint2.dx = dGISDPoint1.dx;
		m_pGISDPoint2.dy = dGISDPoint1.dy;

		return;
	}

	if (m_pNext != NULL)
	{
		m_pNext->SetGISPosition(node1, node2, dSLDDPoint1, dGISDPoint1, dSLDDPoint2, dGISDPoint2);
	}
}

void CBranchView::DrawGIS(CDC* BufferDC, int nSize, double dZoom, double pCenX, double pCenY, CPoint ptCen, int nStep)
{
	if (m_nDbID > 0)
	{
		if (m_pSLDDPoint1.dx != 0 && m_pSLDDPoint1.dy != 0 && m_pGISDPoint1.dy != 0 && m_pGISDPoint1.dy != 0
			&& m_pSLDDPoint2.dx != 0 && m_pSLDDPoint2.dy != 0 && m_pGISDPoint2.dy != 0 && m_pGISDPoint2.dy != 0)
		{
			double dx1, dy1, dx2, dy2;
			int x1, y1, x2, y2;
			dx1 = m_pSLDDPoint1.dx + ((m_pGISDPoint1.dx - m_pSLDDPoint1.dx) * ((20 - nStep) / 20.));
			dy1 = m_pSLDDPoint1.dy + ((m_pGISDPoint1.dy - m_pSLDDPoint1.dy) * ((20 - nStep) / 20.));
			x1 = int((dx1 - pCenX) * dZoom + 0.5) + ptCen.x;
			y1 = int((pCenY - dy1) * dZoom + 0.5) + ptCen.y;

			dx2 = m_pSLDDPoint2.dx + ((m_pGISDPoint2.dx - m_pSLDDPoint2.dx) * ((20 - nStep) / 20.));
			dy2 = m_pSLDDPoint2.dy + ((m_pGISDPoint2.dy - m_pSLDDPoint2.dy) * ((20 - nStep) / 20.));
			x2 = int((dx2 - pCenX) * dZoom + 0.5) + ptCen.x;
			y2 = int((pCenY - dy2) * dZoom + 0.5) + ptCen.y;

			CPen							pen, *pOldpen;
			if (m_nOverHead == 0)			pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			else							pen.CreatePen(PS_DOT, 1, RGB(0, 0, 255));

			pOldpen = BufferDC->SelectObject(&pen);

			CPoint							ptFwdScale, ptBwdScale;
			ptFwdScale.x = (int)x1;
			ptFwdScale.y = (int)y1;
			ptBwdScale.x = (int)x2;
			ptBwdScale.y = (int)y2;

			BufferDC->MoveTo(ptFwdScale);
			BufferDC->LineTo(ptBwdScale);

			BufferDC->SelectObject(pOldpen);
			pen.DeleteObject();
		}
	}
	if (m_pNext)
		m_pNext->DrawGIS(BufferDC, nSize, dZoom, pCenX, pCenY, ptCen, nStep);
}

void CBranchView::DrawGIS2(CDC* BufferDC, int nSize, double dZoom, double pCenX, double pCenY, CPoint ptCen, int nStep2)
{
	if (m_nDbID > 0)
	{
		if (m_pSLDDPoint1.dx != 0 && m_pSLDDPoint1.dy != 0 && m_pGISDPoint1.dy != 0 && m_pGISDPoint1.dy != 0
			&& m_pSLDDPoint2.dx != 0 && m_pSLDDPoint2.dy != 0 && m_pGISDPoint2.dy != 0 && m_pGISDPoint2.dy != 0)
		{
			CPen							pen, *pOldpen;
			if (m_nOverHead == 0)			pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
			else							pen.CreatePen(PS_SOLID, 2, RGB(129, 81, 54));

			pOldpen = BufferDC->SelectObject(&pen);

			int i, nCnt;
			POINT* pPts, *dummyPt;

			if (nStep2 > 10)
			{
				nCnt = m_ptArr.GetSize();
				pPts = (POINT*)malloc(sizeof(POINT) * nCnt);
				dummyPt = pPts;
				for (i = 0; i < m_ptArr.GetSize(); i++, dummyPt++)
				{
					dummyPt->x = LONG((m_ptArr[i]->dx - pCenX) * dZoom + 0.5) + ptCen.x;
					dummyPt->y = LONG((pCenY - m_ptArr[i]->dy) * dZoom + 0.5) + ptCen.y;
				}
			}
			else
			{
				nCnt = m_pZPArray.GetSize();

				CZPoint* pZipPoint;
				pPts = (POINT*)malloc(sizeof(POINT) * nCnt);
				dummyPt = pPts;
				for (int i = 0; i < m_pZPArray.GetSize(); i++, dummyPt++)
				{
					pZipPoint = m_pZPArray.GetAt(i);

					dummyPt->x = LONG((pZipPoint->m_dXArray[nStep2 - 1] - pCenX) * dZoom + 0.5) + ptCen.x;
					dummyPt->y = LONG((pCenY - pZipPoint->m_dYArray[nStep2 - 1]) * dZoom + 0.5) + ptCen.y;
				}
			}

			BufferDC->Polyline(pPts, nCnt);

			BufferDC->SelectObject(pOldpen);

			free(pPts);
		}

	}
	if (m_pNext)
		m_pNext->DrawGIS2(BufferDC, nSize, dZoom, pCenX, pCenY, ptCen, nStep2);
}

void CBranchView::SetZipDPArray()
{
	for (int i = 0; i < m_pZPArray.GetSize(); i++)
		delete m_pZPArray.GetAt(i);
	m_pZPArray.RemoveAll();

	CDPoint* pDP;
	CZPoint* pZP;

	for (int i = 0; i < m_ptArr.GetSize(); i++)
	{
		pDP = m_ptArr.GetAt(i);

		pZP = new CZPoint();

		pZP->m_dX = pDP->dx;
		pZP->m_dY = pDP->dy;

		m_pZPArray.Add(pZP);
	}
}

void CBranchView::SetZip()
{
	CZPoint* pZP1, *pZP2, *pZP3;

	double  dPI = 3.14159265358979323846;
	double dX1, dY1, dX2, dY2, dX3, dY3, dAngle;

// 	if (m_ptArr.GetSize() < 3) return;
	if (m_ptArr.GetSize() < 2)
	{
// 		AfxMessageBox( _T("LNSEC - INNERPOLE 매핑오류!") );
		return;
	}

	for (int i = 0; i < m_pZPArray.GetSize() - 2; i++)
	{
		pZP1 = m_pZPArray.GetAt(i);
		pZP2 = m_pZPArray.GetAt(i + 1);
		pZP3 = m_pZPArray.GetAt(i + 2);

		dX1 = pZP1->m_dX;
		dY1 = pZP1->m_dY;
		dX2 = pZP2->m_dX;
		dY2 = pZP2->m_dY;
		dX3 = pZP3->m_dX;
		dY3 = pZP3->m_dY;

		dAngle = fabs(atan2((dY3 - dY2), (dX3 - dX2)) - atan2((dY2 - dY1), (dX2 - dX1)));
		dAngle *= (180 / dPI);
		if (dAngle < 10.0)
		{
			delete m_pZPArray.GetAt(i + 1);
			m_pZPArray.RemoveAt(i + 1);
			i--;

		}
	}

	CZPoint* pZP;
	CDPoint* pSDP, *pLDP;
	double dXGap = 0, dYGap = 0;

	pSDP = m_ptArr.GetAt(0);
	pLDP = m_ptArr.GetAt(m_ptArr.GetSize() - 1);

	for (int i = 0; i < m_pZPArray.GetSize(); i++)
	{
		pZP = m_pZPArray.GetAt(i);

		dXGap = (pZP->m_dX - pSDP->dx) / 10;
		dYGap = (pZP->m_dY - pSDP->dy) / 10;

		for (int j = 0; j < 10; j++)
		{
			if ((i == 0) || (i == m_pZPArray.GetSize() - 1))
			{
				pZP->m_dXArray[j] = pZP->m_dX;
				pZP->m_dYArray[j] = pZP->m_dY;
			}
			else
			{
				pZP->m_dXArray[j] = pSDP->dx + (dXGap * (j + 1));
				pZP->m_dYArray[j] = pSDP->dy + (dYGap * (j + 1));
			}
		}
	}
}

void CBranchView::ClearBoundarySelect(BOOL bAreaMode)
{
	if (m_nDbID > 0)
	{
		if (bAreaMode)
		{
			int nLNSECIdx;
			nLNSECIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_equ"), m_nDbID);
			PUTVALUE(_T("lnsec_dyn_uin"), _T("lnsec_his_notsrch"), nLNSECIdx, 0);
		}

		m_bBoundarySelect = FALSE;
	}

	if (m_pNext)
		m_pNext->ClearBoundarySelect(bAreaMode);

}

void CBranchView::SetChangeVoltLevel(int nTabValue)
{
	if (m_nDbID > 0)
	{
		if (m_bBoundarySelect)
		{
			PUTVALUE(_T("nd_dyn_uin"), _T("ND_II_VVM"), m_nNDID[0], nTabValue);
			PUTVALUE(_T("nd_dyn_uin"), _T("ND_II_VVM"), m_nNDID[1], nTabValue);
		}
	}

	if (m_pNext)
		m_pNext->SetChangeVoltLevel(nTabValue);
}