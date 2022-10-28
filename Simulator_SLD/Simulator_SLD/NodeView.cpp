// NodeView.cpp : ���� �����Դϴ�.
//

#include "pch.h"
#include "NodeView.h"
#include "MainFrm.h"

// CNodeView
#define						NON_DIRECTION			0
#define						CENTER_DIRECTION		1
#define						LEFT_DIRECTION			2
#define						RIGHT_DIRECTION			3
#define						LEFTTOP_DIRECTION		4
#define						RIGHTBOTTOM_DIRECTION	5

#define						TEXT_AREA_WIDTH			500

CNodeView::CNodeView()
{
	m_nDbID					= 0;
	m_nSwKindID				= 0;
	m_nKCIMType				= 0;
	m_nCeqType				= 0;

	m_nPosX					= 0;
	m_nPosY					= 0;
	m_szLoc					= _T("");
	m_szLocNo				= _T("");
	m_bStatus				= SW_CLOSE;
	m_nTongID				= 0;
	m_nCaption				= 0;
	m_nNDID[0]				= 0;
	m_nNDID[1]				= 0;

	m_rectObj				= CRect(0, 0, 0, 0);

	m_pLeft					= NULL;
	m_pCenter				= NULL;
	m_pRight				= NULL;
	m_pLeftTop				= NULL;
	m_pRightBottom			= NULL;

	m_nReviseLevel			= 0;
	m_nDirection			= 0;
	m_nDirection2			= 0;

	m_bBoundarySelect		= FALSE;

	m_szCEQID				= _T("");

	m_nFromND = 0;

	m_bBoundarySelect		= FALSE;

	m_nALTSCBSW				= 0;
}

CNodeView::~CNodeView()
{
	if( m_pCenter )
	{
		delete				m_pCenter;
		m_pCenter			= NULL;
	}
	if( m_pLeft )
	{
		delete				m_pLeft;
		m_pLeft				= NULL;
	}
	if( m_pRight )
	{
		delete				m_pRight;
		m_pRight			= NULL;
	}
	if( m_pLeftTop )
	{
		delete				m_pLeftTop;
		m_pLeftTop			= NULL;
	}
	if( m_pRightBottom )
	{
		delete				m_pRightBottom;
		m_pRightBottom		= NULL;
	}
}

void CNodeView::RemoveData()
{
	if( m_pCenter )
	{
		delete				m_pCenter;
		m_pCenter			= NULL;
	}
	if( m_pLeft )
	{
		delete				m_pLeft;
		m_pLeft				= NULL;
	}
	if( m_pRight )
	{
		delete				m_pRight;
		m_pRight			= NULL;
	}
	if( m_pLeftTop )
	{
		delete				m_pLeftTop;
		m_pLeftTop			= NULL;
	}
	if( m_pRightBottom )
	{
		delete				m_pRightBottom;
		m_pRightBottom		= NULL;
	}
}

// CNodeView ��� �Լ�
void CNodeView::Serialize(CArchive& ar, double dVersion)
{
	if( ar.IsStoring() )
	{
		ar << m_nDbID << m_nSwKindID << m_nKCIMType << m_nPosX << m_nPosY << m_szLoc << m_szLocNo << m_bStatus << m_nTongID << m_nCaption << m_rectObj;
		ar << m_nCrossCnt << m_nReviseLevel << m_nDirection << m_nNDID[0] << m_nNDID[1] << m_nDirection << m_nDirection2 << m_szCEQID << m_nCeqType << m_nALTSCBSW;

		
		if( m_pCenter )
		{
			ar << (int)CENTER_DIRECTION;
			m_pCenter->Serialize( ar, dVersion );
		}
		if( m_pLeft )
		{
			ar << (int)LEFT_DIRECTION;
			m_pLeft->Serialize( ar, dVersion );
		}
		if( m_pRight )
		{
			ar << (int)RIGHT_DIRECTION;
			m_pRight->Serialize( ar, dVersion );
		}
		if( m_pLeftTop )
		{
			ar << (int)LEFTTOP_DIRECTION;
			m_pLeftTop->Serialize( ar, dVersion );
		}
		if( m_pRightBottom )
		{
			ar << (int)RIGHTBOTTOM_DIRECTION;
			m_pRightBottom->Serialize( ar, dVersion );
		}

		ar << (int)NON_DIRECTION;
	}
	else
	{
		ar >> m_nDbID >> m_nSwKindID >> m_nKCIMType >> m_nPosX >> m_nPosY >> m_szLoc >> m_szLocNo >> m_bStatus >> m_nTongID >> m_nCaption >> m_rectObj;
		ar >> m_nCrossCnt >> m_nReviseLevel >> m_nDirection >> m_nNDID[0] >> m_nNDID[1] >> m_nDirection >> m_nDirection2 >> m_szCEQID >> m_nCeqType >> m_nALTSCBSW;

		int																nNextDirection;
		ar >> nNextDirection;

		while( nNextDirection != NON_DIRECTION )
		{
			CNodeView*													pNodeView;
			pNodeView													= new CNodeView();
			pNodeView->Serialize( ar, dVersion );

			if( nNextDirection == CENTER_DIRECTION )					m_pCenter		= pNodeView;
			else if( nNextDirection == LEFT_DIRECTION )					m_pLeft			= pNodeView;
			else if( nNextDirection == RIGHT_DIRECTION)					m_pRight		= pNodeView;
			else if( nNextDirection == LEFTTOP_DIRECTION)				m_pLeftTop		= pNodeView;
			else if( nNextDirection == RIGHTBOTTOM_DIRECTION)			m_pRightBottom	= pNodeView;

			ar >> nNextDirection;
		}
	}
}

void CNodeView::Draw(CDC* BufferDC, double dScale, int nShowOption, BOOL bPrint, int nFontRate)
{
	COLORREF															color;
	
	if( m_nSwKindID != -1000 )
	{
		m_rectObj														= GetSimbolRect( dScale );

		if( m_nSwKindID == NDTYPE_GEN )									DrawDG( BufferDC, dScale, bPrint, nFontRate);//�л�����
		else if( m_nSwKindID == NDTYPE_SVR )							DrawSVR( BufferDC, dScale, bPrint, nFontRate);//SVR
		else if( m_nSwKindID == NDTYPE_ESS )							DrawAutoSw( BufferDC, dScale, bPrint, nFontRate);//�ڵ�����ġ�� �����ϰ� �׸���.
		else if( m_nSwKindID == NDTYPE_SHUNTEQ )						DrawAutoSw( BufferDC, dScale, bPrint, nFontRate);//�ڵ�����ġ�� �����ϰ� �׸���.
		else if( m_nSwKindID == NDTYPE_SVC )							DrawAutoSw( BufferDC, dScale, bPrint, nFontRate);//�ڵ�����ġ�� �����ϰ� �׸���.
		else if( m_nSwKindID == NDTYPE_DUMMY )							DrawDummy( BufferDC, dScale, bPrint, nFontRate);//����													
		else if( m_nSwKindID == NDTYPE_BACKUP )							DrawBF( BufferDC, dScale, bPrint, nFontRate);//����Ǵ�
		else if (m_nSwKindID == NDTYPE_CUSTOMER)						DrawCustomer(BufferDC, dScale, bPrint, nFontRate);//��													
		else
		{//�Ϲݽ���ġ, Ÿ�̽���ġ, ��Ƽ����, ���б����...(��Ƽ���� - �Ϲݰ����� Draw�Լ� ������ m_nTongID������ ������.
			//ALTS�� ������̿��� �ѹ��� �׸�!!!
			if (m_nSwKindID != NDTYPE_ALTS)
			{
				if (m_nKCIMType == KCIMTYPE_CB)							DrawCB(BufferDC, dScale, bPrint, nFontRate);
				else if (m_nKCIMType == KCIMTYPE_MANUAL)
				{
					if (m_nSwKindID == NDTYPE_TR)
						DrawAutoSw(BufferDC, dScale, bPrint, nFontRate);//�ڵ�����ġ�� �����ϰ� �׸���.
					else
						DrawManualSw(BufferDC, dScale, bPrint, nFontRate);
				}
				else if (m_nKCIMType == KCIMTYPE_COS)					DrawCOS(BufferDC, dScale, bPrint, nFontRate);
				else if (m_nKCIMType == KCIMTYPE_EFI)					DrawEFI(BufferDC, dScale, bPrint, nFontRate);
				else if (m_nKCIMType == KCIMTYPE_RC)
				{
					if( m_nCeqType == 67 )								DrawManualSw(BufferDC, dScale, bPrint, nFontRate);//����RC
					else												DrawAutoSw(BufferDC, dScale, bPrint, nFontRate);//�ڵ�RC
				}
				else													DrawAutoSw(BufferDC, dScale, bPrint, nFontRate);//2:RC, 3:�ڵ�
			}
		}
		if (((CMainFrame *)AfxGetApp()->GetMainWnd())->GetShowSecMode() == 0)
		{
			if (nShowOption & 1)
			{
				int																nFaultPosGND;
				nFaultPosGND = GETVALUE(int, _T("scaopt_dyn_uin"), _T("scaopt_flt_gnd"), 1);
				if ((nFaultPosGND > 0) && ((m_nNDID[0] == nFaultPosGND) || (m_nNDID[1] == nFaultPosGND)))
				{
					int nGNDIdx;
					nGNDIdx = GETVALUE(int, _T("nd_sta"), _T("ND_II_GND"), m_nNDID[0]);

					double dFault_value[4] = { 0, };
					dFault_value[0] = GETVALUE(double, _T("gnd_dyn_scao"), _T("GND_FC_3LL"), nGNDIdx);
					dFault_value[1] = GETVALUE(double, _T("gnd_dyn_scao"), _T("GND_FC_2LL"), nGNDIdx);
					dFault_value[2] = GETVALUE(double, _T("gnd_dyn_scao"), _T("GND_FC_1LG"), nGNDIdx);
					dFault_value[3] = GETVALUE(double, _T("gnd_dyn_scao"), _T("GND_FC_1LG_30OHM"), nGNDIdx);

					if ((abs(dFault_value[0]) + abs(dFault_value[1]) + abs(dFault_value[2]) + abs(dFault_value[3])) <= 0)
					{
						HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
						BufferDC->DrawIcon(m_rectObj.CenterPoint().x - 12, m_rectObj.CenterPoint().y - 14, hIcon);
					}
				}
			}
		}
	}
	else//��ȸ�� ������̿��� ���ֹ�ȣ ���
	{
		//������̴� ������ ��� TR���� MULTI���� ������ �ȵ�. �׷��� ��������� Ÿ������ �����ϴ� ����.
		if (m_pCenter && m_pCenter->m_nSwKindID == NDTYPE_TR)
		{
			//TR�̸� ������ �׸���.
			DrawTRCase(BufferDC, dScale, bPrint, nFontRate);//�ڵ�����ġ�� �����ϰ� �׸���.
		}
		else if ((m_pCenter && m_pCenter->m_nSwKindID == NDTYPE_ALTS) || (m_pLeft && m_pLeft->m_nSwKindID == NDTYPE_ALTS) || (m_pRight && m_pRight->m_nSwKindID == NDTYPE_ALTS))
		{
			DrawALTS(BufferDC, dScale, bPrint, nFontRate);//ALTS
		}
		if( dScale >= SHOW_TEXT_SCALE && ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt() )
		{
			if (!bPrint)
				BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
			else
				BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

			CRect														rect;
			int															nGap;

			if( m_nDirection == 1 && (m_pLeftTop || m_pRightBottom) )	nGap = 55;
			else														nGap = 30;

			CFont font, *pOldfont;
			int nFontSize;
			nFontSize = (int)(12 * (nFontRate / 100.));
			font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
			pOldfont = BufferDC->SelectObject(&font);

			TEXTMETRIC tm;
			BufferDC->GetTextMetrics(&tm);
			int nHeight;
			nHeight = (tm.tmHeight + tm.tmExternalLeading) + 10;

			rect.SetRect((m_nPosX*dScale) - TEXT_AREA_WIDTH, ((m_nPosY + nGap)*dScale), (m_nPosX*dScale) + TEXT_AREA_WIDTH, ((m_nPosY + nGap)*dScale) + nHeight);
			BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			BufferDC->SelectObject(pOldfont);
			font.DeleteObject();

			if (((CMainFrame *)AfxGetApp()->GetMainWnd())->GetShowSecMode() == 0)
			{
				if (m_pCenter && m_pCenter->IsAuto())
				{
					int nCbswIdx;
					CString szText;

					nCbswIdx = GetCbswIdx();
					if (nCbswIdx > 0)
					{
						if (!bPrint)
							BufferDC->SetTextColor(RGB(250, 250, 0));
						else
							BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

						rect.top = rect.bottom;
						rect.bottom = rect.top + 15;
						szText.Format(_T("%.0lfkW"), GetDerGenMw(nCbswIdx));
						//////////////// 211025 ������ ����
						BufferDC->DrawText(szText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

						rect.top = rect.bottom;
						rect.bottom = rect.top + 15;
						szText.Format(_T("%.0lfkW"), GetDerRaMw(nCbswIdx));
						//////////////// 211025 ������ ����
						BufferDC->DrawText(szText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

						BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
					}
				}
			}
		}
	}

	if( m_pCenter )														m_pCenter->Draw( BufferDC, dScale, nShowOption, bPrint, nFontRate);
	if( m_pLeft )														m_pLeft->Draw( BufferDC, dScale, nShowOption, bPrint, nFontRate);
	if( m_pRight )														m_pRight->Draw( BufferDC, dScale, nShowOption, bPrint, nFontRate);
	if( m_pLeftTop )													m_pLeftTop->Draw( BufferDC, dScale, nShowOption, bPrint, nFontRate);
	if( m_pRightBottom )												m_pRightBottom->Draw( BufferDC, dScale, nShowOption, bPrint, nFontRate);
}

void CNodeView::DrawCB( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	CPen							pen, *pOldpen;
	pen.CreatePen( PS_SOLID, 2, RGB(255, 255, 0) );
	pOldpen							= BufferDC->SelectObject( &pen );

	CBrush							brush, *pOldbrush;
	if( m_bBoundarySelect )			brush.CreateSolidBrush( RGB(255, 255, 255) );
	else
	{
		if( m_bStatus == SW_OPEN )	brush.CreateSolidBrush( RGB(0, 250, 0) );
		else						brush.CreateSolidBrush( RGB(250, 0, 0) );
	}
	pOldbrush						= BufferDC->SelectObject( &brush );

	BufferDC->Ellipse( m_rectObj );

	BufferDC->SelectObject(pOldpen);
	pen.DeleteObject();
	BufferDC->SelectObject( pOldbrush );
	brush.DeleteObject();

	if( dScale >= SHOW_TEXT_SCALE )
	{
		CFont						font, *pOldfont;
		font.CreateFont( (int)(20*dScale) ,0,0,0,800,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		pOldfont = BufferDC->SelectObject( &font );

		BufferDC->SetTextColor( RGB(0, 0, 0) );
		BufferDC->DrawText( GetSimbolText(), m_rectObj, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if( !bPrint )
			BufferDC->SetTextColor( DEFALUT_TEXT_COLOR );
		else
			BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

		BufferDC->SelectObject( pOldfont );
		font.DeleteObject();

		int nCbswIdx;
		nCbswIdx = GetCbswIdx();
		if (((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt())
		{
			int nFontSize;
			nFontSize = (int)(12 * (nFontRate / 100.));
			font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
			pOldfont = BufferDC->SelectObject(&font);

			TEXTMETRIC tm;
			BufferDC->GetTextMetrics(&tm);
			int nHeight;
			nHeight = (tm.tmHeight + tm.tmExternalLeading) + 10;

			CRect rect;
			rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.bottom + 5, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.bottom + nHeight);
			BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			BufferDC->SelectObject(pOldfont);
			font.DeleteObject();

			if (((CMainFrame *)AfxGetApp()->GetMainWnd())->GetShowSecMode())
				return;

			CString szText;
			if (nCbswIdx > 0)
			{
				if( !bPrint )
					BufferDC->SetTextColor(RGB(250, 250, 0));
				else
					BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

				rect.top = rect.bottom;
				rect.bottom = rect.top + 15;
				szText.Format(_T("%.1lf"), GetDerGenMw(nCbswIdx));
				BufferDC->DrawText(szText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				rect.top = rect.bottom;
				rect.bottom = rect.top + 15;
				szText.Format(_T("%.1lf"), GetDerRaMw(nCbswIdx));
				BufferDC->DrawText(szText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				int nPRDEIdx;
				nPRDEIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_prde"), nCbswIdx);
				if (nPRDEIdx > 0)
				{
					CString szData;
					int		nOCR_DOCR, nOCGR_DOCGR;
					nOCR_DOCR = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocr_docr"), nPRDEIdx);
					nOCGR_DOCGR = GETVALUE(int, _T("prde_dyn_uin"), _T("prde_ocgr_docgr"), nPRDEIdx);

					szData.Format(_T("%s/%s"), nOCR_DOCR == 0 ? _T("OCR") : _T("DOCR"), nOCGR_DOCGR == 0 ? _T("OCGR") : _T("DOCGR"));

					if( !bPrint )
						BufferDC->SetTextColor(RGB(250, 250, 0));
					else
						BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

					CRect rect;
					rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.top - 25, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.top + 5);
					BufferDC->DrawText(szData, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				if( !bPrint )
					BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
				else
					BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

			}
		}
	}
}

void CNodeView::DrawDG( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	pen.CreatePen( PS_SOLID, 1, RGB(255, 0, 255) );
	pOldpen							= BufferDC->SelectObject( &pen );

	if( m_bBoundarySelect )			brush.CreateSolidBrush( RGB(255, 255, 255) );
	else							brush.CreateSolidBrush( RGB(255, 0, 255) );
	pOldbrush						= BufferDC->SelectObject( &brush );

	BufferDC->Ellipse( m_rectObj );

	BufferDC->SelectObject( pOldpen );
	BufferDC->SelectObject( pOldbrush );
	pen.DeleteObject();
	brush.DeleteObject();

	if( dScale >= SHOW_TEXT_SCALE )
	{
		CFont						font, *pOldfont;
		font.CreateFont( (int)(18*dScale) ,0,0,0,800,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		pOldfont = BufferDC->SelectObject( &font );

		BufferDC->SetTextColor( RGB(0, 0, 0) );
		BufferDC->DrawText( GetSimbolText(), m_rectObj, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if (!bPrint)
			BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
		else
			BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

		BufferDC->SelectObject( pOldfont );
		font.DeleteObject();

		if( ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt() )
		{
			int nFontSize;
			nFontSize = (int)(12 * (nFontRate / 100.));
			font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
			pOldfont = BufferDC->SelectObject(&font);

			TEXTMETRIC tm;
			BufferDC->GetTextMetrics(&tm);
			int nHeight;
			nHeight = (tm.tmHeight + tm.tmExternalLeading) + 10;

			CRect rect;
			rect.SetRect( m_rectObj.CenterPoint().x-TEXT_AREA_WIDTH, m_rectObj.bottom+5, m_rectObj.CenterPoint().x+ TEXT_AREA_WIDTH, m_rectObj.bottom+ nHeight);
			BufferDC->DrawText( m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			BufferDC->SelectObject(pOldfont);
			font.DeleteObject();
		}
	}
}

void CNodeView::DrawAutoSw( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	int								nFontSize;
	CPen							pen, *pOldpen;


	if( m_nTongID )				
		nFontSize					= 14;
	else						
	{
		if( m_nKCIMType == KCIMTYPE_HVE )
			nFontSize				= 12;
		else
			nFontSize				= 18;
	}

	if (m_nCeqType == 7 || m_nCeqType == 9 || m_nCeqType == 17 || m_nCeqType == 22 || m_nCeqType == 33 || m_nCeqType == 65)
	{
		if (m_bStatus == SW_OPEN)	pen.CreatePen(PS_SOLID, 1, RGB(0, 250, 0));
		else						pen.CreatePen(PS_SOLID, 1, RGB(250, 0, 0));
	}
	else
	{
		pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	}

	pOldpen							= BufferDC->SelectObject( &pen );

	CBrush							brush, *pOldbrush;
	if( m_bBoundarySelect )			brush.CreateSolidBrush( RGB(255, 255, 255) );
	else
	{
		if( m_bStatus == SW_OPEN )	brush.CreateSolidBrush( RGB(0, 250, 0) );
		else						brush.CreateSolidBrush( RGB(250, 0, 0) );
	}
	pOldbrush						= BufferDC->SelectObject( &brush );

	if (m_nCeqType == 7 || m_nCeqType == 9 || m_nCeqType == 17 || m_nCeqType == 22 || m_nCeqType == 33 || m_nCeqType == 65)
	{
		CBrush						brush2;
		brush2.CreateSolidBrush(RGB(255, 255, 255));
		BufferDC->SelectObject(&brush2);

		BufferDC->Ellipse(m_rectObj);

		BufferDC->SelectObject(&brush);
		CPoint pp[4];
		pp[0] = CPoint( m_rectObj.CenterPoint().x, m_rectObj.top );
		pp[1] = CPoint( m_rectObj.left, m_rectObj.CenterPoint().y );
		pp[2] = CPoint( m_rectObj.CenterPoint().x, m_rectObj.bottom );
		pp[3] = CPoint( m_rectObj.right, m_rectObj.CenterPoint().y );
		BufferDC->Polygon(pp, 4);

	}
	else if (m_nCeqType == 86 || m_nCeqType == 88)//TRŸ�Կ� ���� ����
	{
		CPoint pp[4];
		pp[0] = CPoint(m_rectObj.CenterPoint().x, m_rectObj.top);
		pp[1] = CPoint(m_rectObj.left, m_rectObj.CenterPoint().y);
		pp[2] = CPoint(m_rectObj.CenterPoint().x, m_rectObj.bottom);
		pp[3] = CPoint(m_rectObj.right, m_rectObj.CenterPoint().y);
		BufferDC->Polygon(pp, 4);

	}
	else
	{
		BufferDC->Ellipse(m_rectObj);
	}

	BufferDC->SelectObject( pOldpen );
	pen.DeleteObject();
	BufferDC->SelectObject( pOldbrush );
	brush.DeleteObject();

	if( dScale >= SHOW_TEXT_SCALE )
	{
		CFont						font, *pOldfont;
		font.CreateFont( (int)(nFontSize*dScale) ,0,0,0,800,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		pOldfont = BufferDC->SelectObject( &font );

		BufferDC->SetTextColor( RGB(0, 0, 0) );
		BufferDC->DrawText( GetSimbolText(), m_rectObj, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if( !bPrint )
			BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
		else
			BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);


		BufferDC->SelectObject( pOldfont );
		font.DeleteObject();

		if( !m_nTongID && ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt() )
		{
			int nFontSize;
			nFontSize = (int)(12 * (nFontRate / 100.));
			font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
			pOldfont = BufferDC->SelectObject(&font);

			TEXTMETRIC tm;
			BufferDC->GetTextMetrics(&tm);
			int nHeight;
			nHeight = (tm.tmHeight + tm.tmExternalLeading) + 10;

			CRect rect;
			rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.bottom + 5, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.bottom + nHeight);
			BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			BufferDC->SelectObject(pOldfont);
			font.DeleteObject();

			if (((CMainFrame *)AfxGetApp()->GetMainWnd())->GetShowSecMode())
				return;

			if (m_nSwKindID == NDTYPE_SWITCH )
			{
				int nCbswIdx;
				CString szText;
				
				nCbswIdx = GetCbswIdx();
				if (nCbswIdx > 0)
				{
					if( !bPrint )
						BufferDC->SetTextColor(RGB(250, 250, 0));
					else
						BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);


					rect.top = rect.bottom;
					rect.bottom = rect.top + 15;
					szText.Format(_T("%.1lf"), GetDerGenMw(nCbswIdx));
					BufferDC->DrawText(szText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

					rect.top = rect.bottom;
					rect.bottom = rect.top + 15;
					szText.Format(_T("%.1lf"), GetDerRaMw(nCbswIdx));
					BufferDC->DrawText(szText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

					BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
				}
			}
		}
	}
}

void CNodeView::DrawManualSw( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	int								nFontSize;
	CPen							pen, *pOldpen;

	if( m_nTongID )				
	{
		pen.CreatePen( PS_SOLID, 1, RGB(255, 255, 0) );
		nFontSize					= 14;
	}
	else						
	{
		pen.CreatePen( PS_SOLID, 2, RGB(255, 255, 0) );
		nFontSize					= 18;
	}
	pOldpen							= BufferDC->SelectObject( &pen );

	CBrush							brush, *pOldbrush;
	if( m_bBoundarySelect )			brush.CreateSolidBrush( RGB(255, 255, 255) );
	else
	{
		if( m_bStatus == SW_OPEN )	brush.CreateSolidBrush( RGB(0, 250, 0) );
		else						brush.CreateSolidBrush( RGB(250, 0, 0) );
	}
	pOldbrush						= BufferDC->SelectObject( &brush );

	BufferDC->Rectangle( m_rectObj );

	BufferDC->SelectObject( pOldpen );
	pen.DeleteObject();
	BufferDC->SelectObject( pOldbrush );
	brush.DeleteObject();

	if( dScale >= SHOW_TEXT_SCALE )
	{
		CFont						font, *pOldfont;
		font.CreateFont( (int)(nFontSize*dScale) ,0,0,0,800,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		pOldfont = BufferDC->SelectObject( &font );

		BufferDC->SetTextColor( RGB(0, 0, 0) );
		BufferDC->DrawText( GetSimbolText(), m_rectObj, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if( !bPrint )
			BufferDC->SetTextColor( DEFALUT_TEXT_COLOR );
		else
			BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);


		BufferDC->SelectObject( pOldfont );
		font.DeleteObject();

		if( !m_nTongID && ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt() )
		{
			int nFontSize;
			nFontSize = (int)(12 * (nFontRate / 100.));
			font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
			pOldfont = BufferDC->SelectObject(&font);

			TEXTMETRIC tm;
			BufferDC->GetTextMetrics(&tm);
			int nHeight;
			nHeight = (tm.tmHeight + tm.tmExternalLeading) + 10;

			CRect rect;
			rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.bottom + 5, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.bottom + nHeight);
			BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			BufferDC->SelectObject(pOldfont);
			font.DeleteObject();
		}
	}
}

void CNodeView::DrawSVR( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	int								nFontSize;
	CPen							pen, *pOldpen;

	pen.CreatePen( PS_SOLID, 2, RGB(255, 255, 0) );
	nFontSize						= 12;
	pOldpen							= BufferDC->SelectObject( &pen );

	CBrush							brush, *pOldbrush;
	if( m_bBoundarySelect )			brush.CreateSolidBrush( RGB(255, 255, 255) );
	else
	{
		if( m_bStatus == SW_OPEN )	brush.CreateSolidBrush( RGB(0, 250, 0) );
		else						brush.CreateSolidBrush( RGB(250, 0, 0) );
	}
	pOldbrush						= BufferDC->SelectObject( &brush );

// 	BufferDC->Ellipse( m_rectObj );
	CPoint							pt[8];
	pt[0]							= CPoint( m_rectObj.left + m_rectObj.Width()/4, m_rectObj.top );
	pt[1]							= CPoint( m_rectObj.right - m_rectObj.Width()/4, m_rectObj.top );
	pt[2]							= CPoint( m_rectObj.right, m_rectObj.top + m_rectObj.Height()/4 );
	pt[3]							= CPoint( m_rectObj.right, m_rectObj.bottom - m_rectObj.Height()/4 );
	pt[4]							= CPoint( m_rectObj.right - m_rectObj.Width()/4, m_rectObj.bottom );
	pt[5]							= CPoint( m_rectObj.left + m_rectObj.Width()/4, m_rectObj.bottom );
	pt[6]							= CPoint( m_rectObj.left, m_rectObj.bottom - m_rectObj.Height()/4 );
	pt[7]							= CPoint( m_rectObj.left, m_rectObj.top + m_rectObj.Height()/4 );
	BufferDC->Polygon( pt, 8 );

	BufferDC->SelectObject( pOldpen );
	pen.DeleteObject();
	BufferDC->SelectObject( pOldbrush );
	brush.DeleteObject();

	if( dScale >= SHOW_TEXT_SCALE )
	{
		CFont						font, *pOldfont;
		font.CreateFont( (int)(nFontSize*dScale) ,0,0,0,800,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		pOldfont = BufferDC->SelectObject( &font );

		BufferDC->SetTextColor( RGB(0, 0, 0) );
		BufferDC->DrawText( GetSimbolText(), m_rectObj, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if( !bPrint )
			BufferDC->SetTextColor( DEFALUT_TEXT_COLOR );
		else
			BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

		BufferDC->SelectObject( pOldfont );
		font.DeleteObject();

		if( ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt() )
		{
			int nFontSize;
			nFontSize = (int)(12 * (nFontRate / 100.));
			font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
			pOldfont = BufferDC->SelectObject(&font);

			TEXTMETRIC tm;
			BufferDC->GetTextMetrics(&tm);
			int nHeight;
			nHeight = (tm.tmHeight + tm.tmExternalLeading) + 10;

			CRect rect;
			rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.bottom + 5, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.bottom + nHeight);
			BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			BufferDC->SelectObject(pOldfont);
			font.DeleteObject();
		}
	}
}

void CNodeView::DrawOH( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	pen.CreatePen( PS_SOLID, 1, RGB(20, 20, 255) );
	pOldpen					= BufferDC->SelectObject( &pen );

	if( m_bBoundarySelect )			brush.CreateSolidBrush( RGB(255, 255, 255) );
	else							brush.CreateSolidBrush( RGB(20, 20, 255) );
	pOldbrush						= BufferDC->SelectObject( &brush );

	BufferDC->Ellipse( m_rectObj );

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject( pOldbrush );
	pen.DeleteObject();
	brush.DeleteObject();

	if (!bPrint)
		BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
	else
		BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

	if( dScale >= SHOW_TEXT_SCALE && ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt() )
	{
		CFont font, *pOldfont;
		int nFontSize;
		nFontSize = (int)(12 * (nFontRate / 100.));
		font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
		pOldfont = BufferDC->SelectObject(&font);

		TEXTMETRIC tm;
		BufferDC->GetTextMetrics(&tm);
		int nHeight;
		nHeight = (tm.tmHeight + tm.tmExternalLeading) + 10;

		CRect rect;
		rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.bottom + 5, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.bottom + nHeight);
		BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		BufferDC->SelectObject(pOldfont);
		font.DeleteObject();
	}
}

void CNodeView::DrawCOS( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	CPen							pen, *pOldpen;
	pen.CreatePen( PS_SOLID, 1, RGB(255, 255, 0) );
	pOldpen							= BufferDC->SelectObject( &pen );

	CBrush							brush, *pOldbrush;
	if( m_bBoundarySelect )			brush.CreateSolidBrush( RGB(255, 255, 255) );
	else
	{
		if( m_bStatus == SW_OPEN )	brush.CreateSolidBrush( RGB(0, 250, 0) );
		else						brush.CreateSolidBrush( RGB(250, 0, 0) );
	}
	pOldbrush						= BufferDC->SelectObject( &brush );

	if (m_nTongID)
	{
		CPoint							pt[4];
		pt[0] = CPoint(m_rectObj.CenterPoint().x, m_rectObj.top);
		pt[1] = CPoint(m_rectObj.right, m_rectObj.CenterPoint().y);
		pt[2] = CPoint(m_rectObj.CenterPoint().x, m_rectObj.bottom);
		pt[3] = CPoint(m_rectObj.left, m_rectObj.CenterPoint().y);
		BufferDC->Polygon(pt, 4);
	}
	else
	{
		BufferDC->Rectangle(m_rectObj);
	}

	BufferDC->SelectObject(pOldpen);
	pen.DeleteObject();
	BufferDC->SelectObject( pOldbrush );
	brush.DeleteObject();

	if( dScale >= SHOW_TEXT_SCALE )
	{
		CFont						font, *pOldfont;
		font.CreateFont( (int)(16*dScale) ,0,0,0,800,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		pOldfont = BufferDC->SelectObject( &font );

		BufferDC->SetTextColor( RGB(0, 0, 0) );
		BufferDC->DrawText( GetSimbolText(), m_rectObj, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if (!bPrint)
			BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
		else
			BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

		BufferDC->SelectObject( pOldfont );
		font.DeleteObject();

		if( ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt() )
		{
			int nFontSize;
			nFontSize = (int)(12 * (nFontRate / 100.));
			font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
			pOldfont = BufferDC->SelectObject(&font);

			TEXTMETRIC tm;
			BufferDC->GetTextMetrics(&tm);
			int nHeight;
			nHeight = (tm.tmHeight + tm.tmExternalLeading) + 10;

			CRect rect;
			rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.bottom + 5, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.bottom + nHeight);
			BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			BufferDC->SelectObject(pOldfont);
			font.DeleteObject();
		}
	}
}

void CNodeView::DrawEFI( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	CPen							pen, *pOldpen;
	pen.CreatePen( PS_SOLID, 1, RGB(255, 255, 0) );
	pOldpen							= BufferDC->SelectObject( &pen );

	CBrush							brush, *pOldbrush;
	if( m_bBoundarySelect )			brush.CreateSolidBrush( RGB(255, 255, 255) );
	else
	{
		if( m_bStatus == SW_OPEN )	brush.CreateSolidBrush( RGB(0, 250, 0) );
		else						brush.CreateSolidBrush( RGB(250, 0, 0) );
	}
	pOldbrush						= BufferDC->SelectObject( &brush );

	if (m_nTongID)
	{
		CPoint							pt[4];
		pt[0] = CPoint(m_rectObj.CenterPoint().x, m_rectObj.top);
		pt[1] = CPoint(m_rectObj.right, m_rectObj.CenterPoint().y);
		pt[2] = CPoint(m_rectObj.CenterPoint().x, m_rectObj.bottom);
		pt[3] = CPoint(m_rectObj.left, m_rectObj.CenterPoint().y);
		BufferDC->Polygon(pt, 4);
	}
	else
	{
		if( m_nCeqType == 68 )//�ڵ�
			BufferDC->Ellipse(m_rectObj);
		else
			BufferDC->Rectangle(m_rectObj);
	}

	BufferDC->SelectObject(pOldpen);
	pen.DeleteObject();
	BufferDC->SelectObject( pOldbrush );
	brush.DeleteObject();

	if( dScale >= SHOW_TEXT_SCALE )
	{
		CFont						font, *pOldfont;
		font.CreateFont( (int)(16*dScale) ,0,0,0,800,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		pOldfont = BufferDC->SelectObject( &font );

		BufferDC->SetTextColor( RGB(0, 0, 0) );
		BufferDC->DrawText( GetSimbolText(), m_rectObj, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if (!bPrint)
			BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
		else
			BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

		BufferDC->SelectObject( pOldfont );
		font.DeleteObject();

		if (!m_nTongID && ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt())
		{
			int nFontSize;
			nFontSize = (int)(12 * (nFontRate / 100.));
			font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
			pOldfont = BufferDC->SelectObject(&font);

			TEXTMETRIC tm;
			BufferDC->GetTextMetrics(&tm);
			int nHeight;
			nHeight = (tm.tmHeight + tm.tmExternalLeading) + 10;

			CRect rect;
			rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.bottom + 5, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.bottom + nHeight);
			BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			BufferDC->SelectObject(pOldfont);
			font.DeleteObject();
		}
	}
}

void CNodeView::DrawBF( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	pen.CreatePen( PS_SOLID, 1, RGB(250, 250, 0) );
	pOldpen							= BufferDC->SelectObject( &pen );
	brush.CreateSolidBrush( RGB(250, 0, 0) );
	pOldbrush						= BufferDC->SelectObject( &brush );

	CRect							rectText;
	UINT							uStyle;
	CPoint							pt[5];
	if( m_nDirection == 0 )
	{
		pt[0]						= CPoint( m_rectObj.left, m_rectObj.CenterPoint().y );
		pt[1]						= CPoint( m_rectObj.CenterPoint().x, m_rectObj.top );
		pt[2]						= CPoint( m_rectObj.right, m_rectObj.top );
		pt[3]						= CPoint( m_rectObj.right, m_rectObj.bottom );
		pt[4]						= CPoint( m_rectObj.CenterPoint().x, m_rectObj.bottom );

		rectText.SetRect( m_rectObj.right+5, m_rectObj.CenterPoint().y-10, m_rectObj.right+5+(TEXT_AREA_WIDTH*2), m_rectObj.CenterPoint().y+10 );
		uStyle						= DT_LEFT;
	}
	else if( m_nDirection == 1 )
	{
		pt[0]						= CPoint( m_rectObj.CenterPoint().x, m_rectObj.top );
		pt[1]						= CPoint( m_rectObj.right, m_rectObj.CenterPoint().y );
		pt[2]						= CPoint( m_rectObj.right, m_rectObj.bottom );
		pt[3]						= CPoint( m_rectObj.left, m_rectObj.bottom );
		pt[4]						= CPoint( m_rectObj.left, m_rectObj.CenterPoint().y );

		rectText.SetRect( m_rectObj.CenterPoint().x- TEXT_AREA_WIDTH, m_rectObj.bottom+5, m_rectObj.CenterPoint().x+ TEXT_AREA_WIDTH, m_rectObj.bottom+25 );
		uStyle						= DT_CENTER;
	}
	else if( m_nDirection == 2 )
	{
		pt[0]						= CPoint( m_rectObj.right, m_rectObj.CenterPoint().y );
		pt[1]						= CPoint( m_rectObj.CenterPoint().x, m_rectObj.bottom );
		pt[2]						= CPoint( m_rectObj.left, m_rectObj.bottom );
		pt[3]						= CPoint( m_rectObj.left, m_rectObj.top );
		pt[4]						= CPoint( m_rectObj.CenterPoint().x, m_rectObj.top );

		rectText.SetRect( m_rectObj.left-5-(TEXT_AREA_WIDTH *2), m_rectObj.CenterPoint().y-10, m_rectObj.left-5, m_rectObj.CenterPoint().y+10 );
		uStyle						= DT_RIGHT;
	}
	else
	{
		pt[0]						= CPoint( m_rectObj.CenterPoint().x, m_rectObj.bottom );
		pt[1]						= CPoint( m_rectObj.left, m_rectObj.CenterPoint().y );
		pt[2]						= CPoint( m_rectObj.left, m_rectObj.top );
		pt[3]						= CPoint( m_rectObj.right, m_rectObj.top );
		pt[4]						= CPoint( m_rectObj.right, m_rectObj.CenterPoint().y );

		rectText.SetRect( m_rectObj.CenterPoint().x- TEXT_AREA_WIDTH, m_rectObj.top-25, m_rectObj.CenterPoint().x+ TEXT_AREA_WIDTH, m_rectObj.top-5 );
		uStyle						= DT_CENTER;
	}

	BufferDC->Polygon( pt, 5 );

	BufferDC->SelectObject(pOldpen);
	pen.DeleteObject();
	BufferDC->SelectObject( pOldbrush );
	brush.DeleteObject();

	if (!bPrint)
		BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
	else
		BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

	if( dScale >= SHOW_TEXT_SCALE && ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt() )
	{
		CString szText;
		if( m_nNDID[1] > 0 )		szText.Format(_T("(���ο���)") );
		else						szText.Format( _T("%s/%s"), m_szLocNo, m_szLoc );
		BufferDC->DrawText( szText, rectText, uStyle | DT_VCENTER | DT_SINGLELINE);

		if (m_nNDID[1] == 0)
		{
			double					dLdMw(0), dGenMw(0), dNetMw(0);
			dLdMw					= GETVALUE(double, _T("dl_dyn_rpfo"), _T("dl_3pldrpfmw"), m_nNDID[0]) * 1000;
			dGenMw					= GETVALUE(double, _T("dl_dyn_rpfo"), _T("dl_3pgenrpfmw"), m_nNDID[0]) * 1000;
			dNetMw					= dLdMw - dGenMw;

			CFont					font, *pOldfont;
			font.CreateFont(22, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("���� ���"));
			pOldfont = BufferDC->SelectObject(&font);

			if (!bPrint)
				BufferDC->SetTextColor(RGB(250, 250, 0));
			else
				BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

			if (m_nDirection != 3)
			{
				rectText.top = rectText.bottom;
				rectText.bottom = rectText.top + 20;
				szText.Format(_T("%.1lf/%.1lf"), dLdMw, dGenMw);
				BufferDC->DrawText(szText, rectText, uStyle | DT_VCENTER | DT_SINGLELINE);

				rectText.top = rectText.bottom;
				rectText.bottom = rectText.top + 20;
				szText.Format(_T("(%.1lf)"), dNetMw);
				BufferDC->DrawText(szText, rectText, uStyle | DT_VCENTER | DT_SINGLELINE);
			}
			else
			{
				rectText.bottom = rectText.top;
				rectText.top = rectText.bottom - 20;
				szText.Format(_T("%.1lf/%.1lf"), dLdMw, dGenMw);
				BufferDC->DrawText(szText, rectText, uStyle | DT_VCENTER | DT_SINGLELINE);

				rectText.bottom = rectText.top;
				rectText.top = rectText.bottom - 20;
				szText.Format(_T("(%.1lf)"), dNetMw);
				BufferDC->DrawText(szText, rectText, uStyle | DT_VCENTER | DT_SINGLELINE);
			}


			BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
			BufferDC->SelectObject(pOldfont);
			font.DeleteObject();

		}
	}
}

void CNodeView::DrawALTS(CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush, subBrush;
	COLORREF						color1, color2;
	pen.CreatePen(PS_SOLID, 1, RGB(250, 250, 0));
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(RGB(250, 250, 250));
	pOldbrush = BufferDC->SelectObject(&brush);

	if (m_pCenter && m_pCenter->m_bStatus == SW_OPEN)
	{
		if (m_nDirection <= 1)
		{
			color1 = RGB(250, 0, 0);
			color2 = RGB(0, 250, 0);
		}
		else
		{
			color1 = RGB(0, 250, 0);
			color2 = RGB(250, 0, 0);
		}
	}
	else
	{
		if (m_nDirection <= 1)
		{
			color1 = RGB(0, 250, 0);
			color2 = RGB(250, 0, 0);
		}
		else
		{
			color1 = RGB(250, 0, 0);
			color2 = RGB(0, 250, 0);
		}
	}

	//�������� ������ ������
	int nAngleDirection(0);//������(����)
	if (m_nDirection == 0)
	{
		if (m_pRight != NULL)
			nAngleDirection = 1;
		else
			nAngleDirection = 3;
	}
	else if (m_nDirection == 1)
	{
		if (m_pRight != NULL)
			nAngleDirection = 2;
		else
			nAngleDirection = 0;
	}
	else if (m_nDirection == 2)
	{
		if (m_pLeft != NULL)
			nAngleDirection = 1;
		else
			nAngleDirection = 3;
	}
	else
	{
		if (m_pLeft != NULL)
			nAngleDirection = 2;
		else
			nAngleDirection = 0;
	}

	CPoint							pt[3];
	if (nAngleDirection == 0)
	{
		pt[0] = CPoint((m_nPosX + 24)*dScale, (m_nPosY)*dScale);
		pt[1] = CPoint((m_nPosX - 12)*dScale, (m_nPosY - 22)*dScale);
		pt[2] = CPoint((m_nPosX - 12)*dScale, (m_nPosY + 22)*dScale);
		BufferDC->Polygon(pt, 3);

		subBrush.CreateSolidBrush(color1);
		BufferDC->SelectObject(&subBrush);
		pt[0] = CPoint((m_nPosX + 8)*dScale, (m_nPosY - 10)*dScale);
		pt[1] = CPoint((m_nPosX - 12)*dScale, (m_nPosY - 22)*dScale);
		pt[2] = CPoint((m_nPosX - 12)*dScale, (m_nPosY)*dScale);
		BufferDC->Polygon(pt, 3);
		subBrush.DeleteObject();

		subBrush.CreateSolidBrush(color2);
		BufferDC->SelectObject(&subBrush);
		pt[0] = CPoint((m_nPosX + 8)*dScale, (m_nPosY + 10)*dScale);
		pt[1] = CPoint((m_nPosX - 12)*dScale, (m_nPosY + 22)*dScale);
		pt[2] = CPoint((m_nPosX - 12)*dScale, (m_nPosY)*dScale);
		BufferDC->Polygon(pt, 3);
		subBrush.DeleteObject();
	}
	else if (nAngleDirection == 1)
	{
		pt[0] = CPoint((m_nPosX)*dScale, (m_nPosY + 24)*dScale);
		pt[1] = CPoint((m_nPosX - 22)*dScale, (m_nPosY - 12)*dScale);
		pt[2] = CPoint((m_nPosX + 22)*dScale, (m_nPosY - 12)*dScale);
		BufferDC->Polygon(pt, 3);

		subBrush.CreateSolidBrush(color1);
		BufferDC->SelectObject(&subBrush);
		pt[0] = CPoint((m_nPosX - 10)*dScale, (m_nPosY + 8)*dScale);
		pt[1] = CPoint((m_nPosX - 22)*dScale, (m_nPosY - 12)*dScale);
		pt[2] = CPoint((m_nPosX)*dScale, (m_nPosY - 12)*dScale);
		BufferDC->Polygon(pt, 3);
		subBrush.DeleteObject();

		subBrush.CreateSolidBrush(color2);
		BufferDC->SelectObject(&subBrush);
		pt[0] = CPoint((m_nPosX + 10)*dScale, (m_nPosY + 8)*dScale);
		pt[1] = CPoint((m_nPosX + 22)*dScale, (m_nPosY - 12)*dScale);
		pt[2] = CPoint((m_nPosX)*dScale, (m_nPosY - 12)*dScale);
		BufferDC->Polygon(pt, 3);
		subBrush.DeleteObject();
	}
	else if (nAngleDirection == 2)
	{
		pt[0] = CPoint((m_nPosX - 24)*dScale, (m_nPosY)*dScale);
		pt[1] = CPoint((m_nPosX + 12)*dScale, (m_nPosY - 22)*dScale);
		pt[2] = CPoint((m_nPosX + 12)*dScale, (m_nPosY + 22)*dScale);
		BufferDC->Polygon(pt, 3);

		subBrush.CreateSolidBrush(color1);
		BufferDC->SelectObject(&subBrush);
		pt[0] = CPoint((m_nPosX - 8)*dScale, (m_nPosY - 10)*dScale);
		pt[1] = CPoint((m_nPosX + 12)*dScale, (m_nPosY - 22)*dScale);
		pt[2] = CPoint((m_nPosX + 12)*dScale, (m_nPosY)*dScale);
		BufferDC->Polygon(pt, 3);
		subBrush.DeleteObject();

		subBrush.CreateSolidBrush(color2);
		BufferDC->SelectObject(&subBrush);
		pt[0] = CPoint((m_nPosX - 8)*dScale, (m_nPosY + 10)*dScale);
		pt[1] = CPoint((m_nPosX + 12)*dScale, (m_nPosY + 22)*dScale);
		pt[2] = CPoint((m_nPosX + 12)*dScale, (m_nPosY)*dScale);
		BufferDC->Polygon(pt, 3);
		subBrush.DeleteObject();
	}
	else
	{
		pt[0] = CPoint((m_nPosX)*dScale, (m_nPosY-24)*dScale);
		pt[1] = CPoint((m_nPosX - 22)*dScale, (m_nPosY + 12)*dScale);
		pt[2] = CPoint((m_nPosX + 22)*dScale, (m_nPosY + 12)*dScale);
		BufferDC->Polygon(pt, 3);

		subBrush.CreateSolidBrush(color1);
		BufferDC->SelectObject(&subBrush);
		pt[0] = CPoint((m_nPosX - 10)*dScale, (m_nPosY - 8)*dScale);
		pt[1] = CPoint((m_nPosX - 22)*dScale, (m_nPosY + 12)*dScale);
		pt[2] = CPoint((m_nPosX)*dScale, (m_nPosY + 12)*dScale);
		BufferDC->Polygon(pt, 3);
		subBrush.DeleteObject();

		subBrush.CreateSolidBrush(color2);
		BufferDC->SelectObject(&subBrush);
		pt[0] = CPoint((m_nPosX + 10)*dScale, (m_nPosY - 8)*dScale);
		pt[1] = CPoint((m_nPosX + 22)*dScale, (m_nPosY + 12)*dScale);
		pt[2] = CPoint((m_nPosX)*dScale, (m_nPosY + 12)*dScale);
		BufferDC->Polygon(pt, 3);
		subBrush.DeleteObject();
	}

	BufferDC->SelectObject(pOldpen);
	pen.DeleteObject();
	BufferDC->SelectObject(pOldbrush);
	brush.DeleteObject();
}

void CNodeView::DrawCustomer( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	pen.CreatePen( PS_SOLID, 1, RGB(250, 250, 0) );
	pOldpen							= BufferDC->SelectObject( &pen );
	brush.CreateSolidBrush( RGB(150, 150, 150) );
	pOldbrush						= BufferDC->SelectObject( &brush );

	BufferDC->Rectangle( m_rectObj );

	BufferDC->SelectObject(pOldpen);
	pen.DeleteObject();
	BufferDC->SelectObject( pOldbrush );
	brush.DeleteObject();

	if (!bPrint)
		BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
	else
		BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

	if( dScale >= SHOW_TEXT_SCALE && ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt() )
	{
		CFont font, *pOldfont;
		int nFontSize;
		nFontSize = (int)(12 * (nFontRate / 100.));
		font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
		pOldfont = BufferDC->SelectObject(&font);

		TEXTMETRIC tm;
		BufferDC->GetTextMetrics(&tm);
		int nWidth, nHeight;
		nWidth = tm.tmWeight + 10;
		nHeight = (tm.tmHeight + tm.tmExternalLeading) + 10;

		CRect rect;
		rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.bottom + 5, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.bottom + nHeight);
		BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		BufferDC->SelectObject(pOldfont);
		font.DeleteObject();
	}
}

void CNodeView::DrawDummy( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	pen.CreatePen( PS_SOLID, 1, RGB(250, 250, 250) );
	pOldpen							= BufferDC->SelectObject( &pen );

	if( m_bBoundarySelect )			brush.CreateSolidBrush( RGB(255, 255, 255) );
	else							brush.CreateSolidBrush( RGB(50, 50, 50) );
	pOldbrush						= BufferDC->SelectObject( &brush );
	BufferDC->Rectangle( m_rectObj );

	BufferDC->SelectObject(pOldpen);
	pen.DeleteObject();
	BufferDC->SelectObject( pOldbrush );
	brush.DeleteObject();

	if (!bPrint)
		BufferDC->SetTextColor(DEFALUT_TEXT_COLOR);
	else
		BufferDC->SetTextColor(DEFALUT_PRINT_COLOR);

	if( dScale >= SHOW_TEXT_SCALE && ((CMainFrame *)AfxGetApp()->GetMainWnd())->GetNameOpt() )
	{
		CFont font, *pOldfont;
		int nFontSize;
		nFontSize = (int)(12 * (nFontRate / 100.));
		font.CreateFont(nFontSize, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����ü"));
		pOldfont = BufferDC->SelectObject(&font);

		TEXTMETRIC tm;
		BufferDC->GetTextMetrics(&tm);
		int nHeight;
		nHeight = (tm.tmHeight + tm.tmExternalLeading)+10;
		
		CRect rect;
		rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.bottom + 5, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.bottom + nHeight);
		BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		BufferDC->SelectObject(pOldfont);
		font.DeleteObject();
	}
}

void CNodeView::DrawTRCase(CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate)
{
	CPen							pen, *pOldpen;
	if( !bPrint )
		pen.CreatePen(PS_SOLID, 1, RGB(250, 250, 250));
	else
		pen.CreatePen(PS_SOLID, 1, RGB(120, 120, 120));
	pOldpen = BufferDC->SelectObject(&pen);

	CPoint pp[5];
	if (m_nDirection % 2 == 0)
	{
		pp[0] = CPoint((m_nPosX - 12)*dScale, (m_nPosY - 8)*dScale);
		pp[1] = CPoint((m_nPosX - 6)*dScale, (m_nPosY - 14)*dScale);
		pp[2] = CPoint((m_nPosX)*dScale, (m_nPosY - 8)*dScale);
		pp[3] = CPoint((m_nPosX + 6)*dScale, (m_nPosY - 14)*dScale);
		pp[4] = CPoint((m_nPosX + 12)*dScale, (m_nPosY - 8)*dScale);
	}
	else
	{
		pp[0] = CPoint((m_nPosX - 8)*dScale, (m_nPosY - 12)*dScale);
		pp[1] = CPoint((m_nPosX - 14)*dScale, (m_nPosY - 6)*dScale);
		pp[2] = CPoint((m_nPosX - 8)*dScale, (m_nPosY)*dScale);
		pp[3] = CPoint((m_nPosX - 14)*dScale, (m_nPosY + 6)*dScale);
		pp[4] = CPoint((m_nPosX - 8)*dScale, (m_nPosY + 12)*dScale);
	}

	BufferDC->Polyline(pp, 5);

	if (m_nCeqType != 82)
	{
		CRect rect;
		
		BufferDC->SelectStockObject(NULL_BRUSH);

		if (m_nDirection % 2 == 0)
		{
			rect.left	= (m_nPosX - 26)*dScale;
			rect.top	= (m_nPosY - 14)*dScale;
			rect.right	= (m_nPosX + 26)*dScale;
			rect.bottom	= (m_nPosY + 14)*dScale;
		}
		else
		{
			rect.left	= (m_nPosX - 14)*dScale;
			rect.top	= (m_nPosY - 26)*dScale;
			rect.right	= (m_nPosX + 14)*dScale;
			rect.bottom = (m_nPosY + 26)*dScale;
		}

		BufferDC->Rectangle(rect);

		BufferDC->SelectStockObject(WHITE_BRUSH);
	}

	BufferDC->SelectObject(pOldpen);
	pen.DeleteObject();
}

void CNodeView::DrawNavi( CDC* BufferDC, double dRatioX, double dRatioY )
{
	CPoint							ptPosition;
	ptPosition						= CPoint( m_nPosX, m_nPosY );
	ptPosition.x					*= dRatioX;
	ptPosition.y					*= dRatioY;

	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	CRect							rect;
	if( IsCBreaker() )//CB�׸���
	{
		color = RGB(255, 0, 0);
		pen.CreatePen( PS_SOLID, 1, color );
		pOldpen							= BufferDC->SelectObject( &pen );
		brush.CreateSolidBrush( color );
		pOldbrush						= BufferDC->SelectObject( &brush );

		rect.SetRect( ptPosition, ptPosition );
		rect.InflateRect( 3, 3 );
		BufferDC->Ellipse( rect );

		BufferDC->SelectObject( pOldpen );
		pen.DeleteObject();
		BufferDC->SelectObject( pOldbrush );
		brush.DeleteObject();

	}
	else if( m_nSwKindID == NDTYPE_GEN )//�л�����
	{
		color = RGB(255, 0, 255);
		pen.CreatePen( PS_SOLID, 1, color );
		pOldpen							= BufferDC->SelectObject( &pen );
		brush.CreateSolidBrush( color );
		pOldbrush						= BufferDC->SelectObject( &brush );

		rect.SetRect( ptPosition, ptPosition );
		rect.InflateRect( 2, 2 );
		BufferDC->Ellipse( rect );

		BufferDC->SelectObject( pOldpen );
		pen.DeleteObject();
		BufferDC->SelectObject( pOldbrush );
		brush.DeleteObject();
	}

	if( m_pCenter )								m_pCenter->DrawNavi( BufferDC, dRatioX, dRatioY );
	if( m_pLeft )								m_pLeft->DrawNavi( BufferDC, dRatioX, dRatioY );
	if( m_pRight )								m_pRight->DrawNavi( BufferDC, dRatioX, dRatioY );
	if( m_pLeftTop )							m_pLeftTop->DrawNavi( BufferDC, dRatioX, dRatioY );
	if( m_pRightBottom )						m_pRightBottom->DrawNavi( BufferDC, dRatioX, dRatioY );
}

CNodeView* CNodeView::FindUnsetNode(int reviselevel)
{
	CNodeView* pnodeview = NULL;
	// ���� ���� ����� �������� ������ �־��� �������� ������ �ƴϸ� ���� ��带 ������
	if(m_nReviseLevel!=reviselevel)
		return(this);

	if(m_pCenter!=NULL) {
		// ��� �±װ� ���� �ƴϸ� �������� ��Ŀ�ú� ȣ��
		pnodeview = m_pCenter->FindUnsetNode(reviselevel);
		// ���ϵǾ�� ���� ���� �ƴϸ� ������ -> �ٸ� ������ �����ϱ� ���Ͽ� �ڵ尡 �̷��� ��.  
		if(pnodeview!=NULL) 
			return pnodeview;
	}
	if(m_pRight!=NULL) {
		pnodeview = m_pRight->FindUnsetNode(reviselevel);
		if(pnodeview!=NULL) 
			return pnodeview;
	}
	if(m_pLeft!=NULL) {
		pnodeview = m_pLeft->FindUnsetNode(reviselevel);
		if(pnodeview!=NULL) return pnodeview;
	}
	if(m_pLeftTop!=NULL) {
		pnodeview = m_pLeftTop->FindUnsetNode(reviselevel);
		if(pnodeview!=NULL) return pnodeview;
	}
	if(m_pRightBottom!=NULL) {
		pnodeview = m_pRightBottom->FindUnsetNode(reviselevel);
		if(pnodeview!=NULL) return pnodeview;
	}

	return(NULL);
}

int CNodeView::SetLongestPathToCenter(double maxlength, double currentlength, CBranchView* pbranchview)
{
	int nodeid;
	double sumlength;

	if( maxlength == currentlength )
	{
		m_nReviseLevel = 1;
		return m_nDbID;
	}
	if(m_pCenter!=NULL){
		sumlength=currentlength+pbranchview->GetLengthDisp(m_nDbID,m_pCenter->m_nDbID);//pdm.GetBranchLength(m_nId,m_pCenter.m_nId);
		if((nodeid=m_pCenter->SetLongestPathToCenter(maxlength,sumlength,pbranchview))>0){
			//��ü�� Center�̱⿡ �̵�����.
			m_nReviseLevel		= 1;
			return				nodeid;
		}
	}
	if(m_pRight!=NULL){
		sumlength=currentlength+pbranchview->GetLengthDisp(m_nDbID,m_pRight->m_nDbID);//pdm.GetBranchLength(m_nId,m_pRight.m_nId);
		if((nodeid=m_pRight->SetLongestPathToCenter(maxlength,sumlength,pbranchview))>0){
			//Center <. Right
			if( m_nSwKindID != 2000 )
			{
				CNodeView*		imsinodeview;
				imsinodeview	= m_pRight;
				m_pRight		= m_pCenter;
				m_pCenter		= imsinodeview;
			}
			m_nReviseLevel		= 1;
			return				nodeid;
		}
	}
	if(m_pLeft!=NULL){
		sumlength=currentlength+pbranchview->GetLengthDisp(m_nDbID,m_pLeft->m_nDbID);//pdm.GetBranchLength(m_nId,m_pLeft.m_nId);
		if((nodeid=m_pLeft->SetLongestPathToCenter(maxlength,sumlength,pbranchview))>0){
			//Center <. Left
			if( m_nSwKindID != 2000 )
			{
				CNodeView*		imsinodeview;
				imsinodeview	= m_pLeft;
				m_pLeft			= m_pCenter;
				m_pCenter		= imsinodeview;
			}
			m_nReviseLevel		= 1;
			return				nodeid;
		}
	}
	if(m_pLeftTop!=NULL){
		sumlength=currentlength+pbranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);//pdm.GetBranchLength(m_nId,m_pLeft.m_nId);
		if((nodeid=m_pLeftTop->SetLongestPathToCenter(maxlength,sumlength,pbranchview))>0){
			//Center <. Left
			if( m_nSwKindID != 2000 )
			{
				CNodeView*		imsinodeview;
				imsinodeview	= m_pLeftTop;
				m_pLeftTop		= m_pCenter;
				m_pCenter		= imsinodeview;
			}
			m_nReviseLevel		= 1;
			return				nodeid;
		}
	}
	if(m_pRightBottom!=NULL){
		sumlength=currentlength+pbranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);//pdm.GetBranchLength(m_nId,m_pLeft.m_nId);
		if((nodeid=m_pRightBottom->SetLongestPathToCenter(maxlength,sumlength,pbranchview))>0){
			//Center <. Left
			if( m_nSwKindID != 2000 )
			{
				CNodeView*		imsinodeview;
				imsinodeview	= m_pRightBottom;
				m_pRightBottom	= m_pCenter;
				m_pCenter		= imsinodeview;
			}
			m_nReviseLevel		= 1;
			return				nodeid;
		}
	}

	return 0;
}

void CNodeView::SetShortestPathDiagonal(CBranchView* pranchview)
{
	double leftlongestpathlength = 0;
	double rightlongestpathlength = 0;
	double lefttoplongestpathlength = 0;
	double rightbottomlongestpathlength = 0;

	if(m_pLeftTop!=NULL)
	{
		// ���ʺб��� ������ ���
		if(m_pLeft!=NULL)
			leftlongestpathlength = m_pLeft->GetLongestPathLength(pranchview)
			+ pranchview->GetLengthDisp(m_nDbID,m_pLeft->m_nDbID);

		// ������ �б��� ������ ���
		if(m_pRight!=NULL)
			rightlongestpathlength = m_pRight->GetLongestPathLength(pranchview)
			+ pranchview->GetLengthDisp(m_nDbID,m_pRight->m_nDbID);

		if( m_pRightBottom!=NULL)
		{
			rightbottomlongestpathlength = m_pRightBottom->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);

			if( leftlongestpathlength < rightlongestpathlength )//Left�� Right���� ª����
			{
				if( leftlongestpathlength < rightbottomlongestpathlength )//Left�� rightbottom���� ª���� �ٲ۴�
				{
					CNodeView*				pTemp;
					pTemp					= m_pRightBottom;
					m_pRightBottom			= m_pLeft;
					m_pLeft					= pTemp;

					leftlongestpathlength	= rightbottomlongestpathlength;
				}
			}
			else
			{
				if( rightlongestpathlength < rightbottomlongestpathlength )//Right�� rightbottom���� ª���� �ٲ۴�.
				{
					CNodeView*				pTemp;
					pTemp					= m_pRightBottom;
					m_pRightBottom			= m_pRight;
					m_pRight				= pTemp;

					rightlongestpathlength	= rightbottomlongestpathlength;
				}
			}
		}

		lefttoplongestpathlength = m_pLeftTop->GetLongestPathLength(pranchview)
			+ pranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);

		if( leftlongestpathlength < rightlongestpathlength )//Left�� Right���� ª����
		{
			if( leftlongestpathlength < lefttoplongestpathlength )//Left�� LeftTop���� ª���� �ٲ۴�
			{
				CNodeView*		pTemp;
				pTemp			= m_pLeftTop;
				m_pLeftTop		= m_pLeft;
				m_pLeft			= pTemp;

			}
		}
		else
		{
			if( rightlongestpathlength < lefttoplongestpathlength )//Right�� LeftTop���� ª���� �ٲ۴�.
			{
				CNodeView*		pTemp;
				pTemp			= m_pLeftTop;
				m_pLeftTop		= m_pRight;
				m_pRight		= pTemp;

			}
		}
	}
	// �ڽĳ����� ���ȣ��
	if(m_pCenter!=NULL)
	{
		m_pCenter->SetShortestPathDiagonal(pranchview);
	}
	if(m_pRight!=NULL)
	{
		m_pRight->SetShortestPathDiagonal(pranchview);
	}
	if(m_pLeft!=NULL)
	{
		m_pLeft->SetShortestPathDiagonal(pranchview);
	}
	if(m_pLeftTop!=NULL)
	{
		m_pLeftTop->SetShortestPathDiagonal(pranchview);
	}
	if( m_pRightBottom!=NULL)
	{
		m_pRightBottom->SetShortestPathDiagonal(pranchview);
	}
}

void CNodeView::SetLongestPathToRightTop(int direction, CBranchView* pranchview)
{
	double leftlongestpathlength		= 0;
	double rightlongestpathlength		= 0;
	double lefttoplongestpathlength		= 0;
	double rightbottomlongestpathlength = 0;

	// ���ʺб��� ������ ���
	if(m_pLeft!=NULL)
		leftlongestpathlength = m_pLeft->GetLongestPathLength(pranchview)
		+ pranchview->GetLengthDisp(m_nDbID,m_pLeft->m_nDbID);

	// ������ �б��� ������ ���
	if(m_pRight!=NULL)
		rightlongestpathlength = m_pRight->GetLongestPathLength(pranchview)
		+ pranchview->GetLengthDisp(m_nDbID,m_pRight->m_nDbID);

	// �б⼱���� ���⿡ ���� ��ǥ�� �����.
	switch(direction)
	{
		// �б⼱�ΰ� ���������� ���� ���
	case 0:
		{// �� �б⼱�ΰ� left tag�� �پ�� ��
			if(leftlongestpathlength < rightlongestpathlength)
			{
				CNodeView* m_pTemp;
				m_pTemp = m_pRight;
				m_pRight = m_pLeft;
				m_pLeft = m_pTemp;
			}

			//Left-Right�� �ٲܶ�, �밢�бⰡ ������ �ݴ�� ��ġ�Ѵ�.
			//�� �밢�б⼱�ΰ� rightbottom�� �پ�� ��.
			// ���ʴ밢���б��� ������ ���
			if(m_pLeftTop!=NULL)
				lefttoplongestpathlength = m_pLeftTop->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);

			// �����ʴ밢���б��� ������ ���
			if(m_pRightBottom!=NULL)
				rightbottomlongestpathlength = m_pRightBottom->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);

			if( leftlongestpathlength == rightlongestpathlength )
			{
				if(lefttoplongestpathlength < rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}
			else
			{
				if(lefttoplongestpathlength > rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}

			break;
		}
		// �б⼱�ΰ� �Ʒ��� ���� ���
	case 1:
		{// �� �б⼱�ΰ� left tag�� �پ�� ��
			if(leftlongestpathlength < rightlongestpathlength)
			{
				CNodeView* m_pTemp;
				m_pTemp = m_pRight;
				m_pRight = m_pLeft;
				m_pLeft = m_pTemp;
			}

			//Left-Right�� �ٲܶ�, �밢�бⰡ ������ �ݴ�� ��ġ�Ѵ�.
			//�� �밢�б⼱�ΰ� rightbottom�� �پ�� ��.
			// ���ʴ밢���б��� ������ ���
			if(m_pLeftTop!=NULL)
				lefttoplongestpathlength = m_pLeftTop->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);

			// �����ʴ밢���б��� ������ ���
			if(m_pRightBottom!=NULL)
				rightbottomlongestpathlength = m_pRightBottom->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);

			if( leftlongestpathlength == rightlongestpathlength )
			{
				if(lefttoplongestpathlength < rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}
			else
			{
				if(lefttoplongestpathlength > rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}

			break;
		}
		// �б⼱�ΰ� �������� ���� ���
	case 2:
		{// �� �б⼱�ΰ� right tag�� �پ�� ��
			if(leftlongestpathlength > rightlongestpathlength)
			{
				CNodeView* m_pTemp;
				m_pTemp = m_pRight;
				m_pRight = m_pLeft;
				m_pLeft = m_pTemp;
			}

			//Left-Right�� �ٲܶ�, �밢�бⰡ ������ �ݴ�� ��ġ�Ѵ�.
			//�� �밢�б⼱�ΰ� lefttop�� �پ�� ��.
			// ���ʴ밢���б��� ������ ���
			if(m_pLeftTop!=NULL)
				lefttoplongestpathlength = m_pLeftTop->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);

			// �����ʴ밢���б��� ������ ���
			if(m_pRightBottom!=NULL)
				rightbottomlongestpathlength = m_pRightBottom->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);

			if( leftlongestpathlength == rightlongestpathlength )
			{
				if(lefttoplongestpathlength > rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}
			else
			{
				if(lefttoplongestpathlength < rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}

			break;
		}
		// �б⼱�ΰ� ���� ���� ���
	case 3:
		{// �� �б⼱�ΰ� right tag�� �پ�� ��
			if(leftlongestpathlength > rightlongestpathlength)
			{
				CNodeView* m_pTemp;
				m_pTemp = m_pRight;
				m_pRight = m_pLeft;
				m_pLeft = m_pTemp;
			}

			//Left-Right�� �ٲܶ�, �밢�бⰡ ������ �ݴ�� ��ġ�Ѵ�.
			//�� �밢�б⼱�ΰ� lefftop�� �پ�� ��.
			// ���ʴ밢���б��� ������ ���
			if(m_pLeftTop!=NULL)
				lefttoplongestpathlength = m_pLeftTop->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);

			// �����ʴ밢���б��� ������ ���
			if(m_pRightBottom!=NULL)
				rightbottomlongestpathlength = m_pRightBottom->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);

			if( leftlongestpathlength == rightlongestpathlength )
			{
				if(lefttoplongestpathlength > rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}
			else
			{
				if(lefttoplongestpathlength < rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}

			break;
		}
	default:
		{
			break;
		}
	}
	// �ڽĳ����� ���ȣ��
	if(m_pCenter!=NULL)
	{
		m_pCenter->SetLongestPathToRightTop(direction,pranchview);
	}
	if(m_pRight!=NULL)
	{
		m_pRight->SetLongestPathToRightTop((direction+5)%4,pranchview);
	}
	if(m_pLeft!=NULL)
	{
		m_pLeft->SetLongestPathToRightTop((direction+3)%4,pranchview);
	}
	if(m_pLeftTop!=NULL)
	{
		m_pLeftTop->SetLongestPathToRightTop((direction+3)%4,pranchview);
	}
	if(m_pRightBottom!=NULL)
	{
		m_pRightBottom->SetLongestPathToRightTop((direction+5)%4,pranchview);
	}
}

void CNodeView::SetLongestPathToRightBottom(int direction, CBranchView* pranchview)
{
	double leftlongestpathlength		= 0;
	double rightlongestpathlength		= 0;
	double lefttoplongestpathlength		= 0;
	double rightbottomlongestpathlength = 0;

	// ���ʺб��� ������ ���
	if(m_pLeft!=NULL)
		leftlongestpathlength = m_pLeft->GetLongestPathLength(pranchview)
		+ pranchview->GetLengthDisp(m_nDbID,m_pLeft->m_nDbID);

	// ������ �б��� ������ ���
	if(m_pRight!=NULL)
		rightlongestpathlength = m_pRight->GetLongestPathLength(pranchview)
		+ pranchview->GetLengthDisp(m_nDbID,m_pRight->m_nDbID);

	// �б⼱���� ���⿡ ���� ��ǥ�� �����.
	switch(direction)
	{
		// �б⼱�ΰ� ���������� ���� ���
	case 0:
		{// �� �б⼱�ΰ� right tag�� �پ�� ��
			if(leftlongestpathlength > rightlongestpathlength)
			{
				CNodeView* m_pTemp;
				m_pTemp = m_pRight;
				m_pRight = m_pLeft;
				m_pLeft = m_pTemp;
			}

			//Left-Right�� �ٲܶ�, �밢�бⰡ ������ �ݴ�� ��ġ�Ѵ�.
			//�� �밢�б⼱�ΰ� lefftop�� �پ�� ��.
			// ���ʴ밢���б��� ������ ���
			if(m_pLeftTop!=NULL)
				lefttoplongestpathlength = m_pLeftTop->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);

			// �����ʴ밢���б��� ������ ���
			if(m_pRightBottom!=NULL)
				rightbottomlongestpathlength = m_pRightBottom->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);

			if(leftlongestpathlength == rightlongestpathlength)
			{
				if(lefttoplongestpathlength > rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}
			else
			{
				if(lefttoplongestpathlength < rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}

			break;
		}
		// �б⼱�ΰ� �Ʒ��� ���� ���
	case 1:
		{// �� �б⼱�ΰ� left tag�� �پ�� ��
			if(leftlongestpathlength < rightlongestpathlength)
			{
				CNodeView* m_pTemp;
				m_pTemp = m_pRight;
				m_pRight = m_pLeft;
				m_pLeft = m_pTemp;
			}

			//Left-Right�� �ٲܶ�, �밢�бⰡ ������ �ݴ�� ��ġ�Ѵ�.
			//�� �밢�б⼱�ΰ� rightbottom�� �پ�� ��.
			// ���ʴ밢���б��� ������ ���
			if(m_pLeftTop!=NULL)
				lefttoplongestpathlength = m_pLeftTop->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);

			// �����ʴ밢���б��� ������ ���
			if(m_pRightBottom!=NULL)
				rightbottomlongestpathlength = m_pRightBottom->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);

			if(leftlongestpathlength == rightlongestpathlength)
			{
				if(lefttoplongestpathlength < rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}
			else
			{
				if(lefttoplongestpathlength > rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}

			break;
		}
		// �б⼱�ΰ� �������� ���� ���
	case 2:
		{// �� �б⼱�ΰ� left tag�� �پ�� ��
			if(leftlongestpathlength < rightlongestpathlength)
			{
				CNodeView* m_pTemp;
				m_pTemp = m_pRight;
				m_pRight = m_pLeft;
				m_pLeft = m_pTemp;
			}

			//Left-Right�� �ٲܶ�, �밢�бⰡ ������ �ݴ�� ��ġ�Ѵ�.
			//�� �밢�б⼱�ΰ� rightbottom�� �پ�� ��.
			// ���ʴ밢���б��� ������ ���
			if(m_pLeftTop!=NULL)
				lefttoplongestpathlength = m_pLeftTop->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);

			// �����ʴ밢���б��� ������ ���
			if(m_pRightBottom!=NULL)
				rightbottomlongestpathlength = m_pRightBottom->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);

			if(leftlongestpathlength == rightlongestpathlength)
			{
				if(lefttoplongestpathlength < rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}
			else
			{
				if(lefttoplongestpathlength > rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}

			break;
		}
		// �б⼱�ΰ� ���� ���� ���
	case 3:
		{// �� �б⼱�ΰ� right tag�� �پ�� ��
			if(leftlongestpathlength > rightlongestpathlength)
			{
				CNodeView* m_pTemp;
				m_pTemp = m_pRight;
				m_pRight = m_pLeft;
				m_pLeft = m_pTemp;
			}

			//Left-Right�� �ٲܶ�, �밢�бⰡ ������ �ݴ�� ��ġ�Ѵ�.
			//�� �밢�б⼱�ΰ� lefftop�� �پ�� ��.
			// ���ʴ밢���б��� ������ ���
			if(m_pLeftTop!=NULL)
				lefttoplongestpathlength = m_pLeftTop->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);

			// �����ʴ밢���б��� ������ ���
			if(m_pRightBottom!=NULL)
				rightbottomlongestpathlength = m_pRightBottom->GetLongestPathLength(pranchview)
				+ pranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);

			if(leftlongestpathlength == rightlongestpathlength)
			{
				if(lefttoplongestpathlength > rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}
			else
			{
				if(lefttoplongestpathlength < rightbottomlongestpathlength)
				{
					CNodeView* m_pTemp;
					m_pTemp = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = m_pTemp;
				}
			}

			break;
		}
	default:
		{
			break;
		}
	}
	// �ڽĳ����� ���ȣ��
	if(m_pCenter!=NULL)
	{
		m_pCenter->SetLongestPathToRightBottom(direction,pranchview);
	}
	if(m_pRight!=NULL)
	{
		m_pRight->SetLongestPathToRightBottom((direction+5)%4,pranchview);
	}
	if(m_pLeft!=NULL)
	{
		m_pLeft->SetLongestPathToRightBottom((direction+3)%4,pranchview);
	}
	if(m_pLeftTop!=NULL)
	{
		m_pLeftTop->SetLongestPathToRightBottom((direction+3)%4,pranchview);
	}
	if(m_pRightBottom!=NULL)
	{
		m_pRightBottom->SetLongestPathToRightBottom((direction+5)%4,pranchview);
	}
}

double CNodeView::GetLongestPathLength(CBranchView* pbranchview)
{
	// ������ ���� �� ��ο� ���� ����
	double maxlength=0;

	// ���� ������ ���� ����
	double center=0,left=0,right=0, lefttop=0, rightbottom=0;

	// ����� ���� �ƴϸ�
	if(m_pCenter!=NULL){

		// �ڽ� ���� ��� ȣ����
		center = m_pCenter->GetLongestPathLength(pbranchview);
		// �ڱ���� ��� �ڽ� ��尣�� ������ ����
		center += pbranchview->GetLengthDisp(m_nDbID,m_pCenter->m_nDbID);
	}
	if(m_pRight!=NULL){
		right = m_pRight->GetLongestPathLength(pbranchview);
		right += pbranchview->GetLengthDisp(m_nDbID,m_pRight->m_nDbID);
	}
	if(m_pLeft!=NULL){
		left = m_pLeft->GetLongestPathLength(pbranchview);
		left += pbranchview->GetLengthDisp(m_nDbID,m_pLeft->m_nDbID);
	}
	if(m_pLeftTop!=NULL){
		lefttop = m_pLeftTop->GetLongestPathLength(pbranchview);
		lefttop += pbranchview->GetLengthDisp(m_nDbID,m_pLeftTop->m_nDbID);
	}
	if(m_pRightBottom!=NULL){
		rightbottom = m_pRightBottom->GetLongestPathLength(pbranchview);
		rightbottom += pbranchview->GetLengthDisp(m_nDbID,m_pRightBottom->m_nDbID);
	}

	// ��, ��, �� �߿��� ���� �� ��θ� ã�� ������.
	if( center > maxlength )		
		maxlength = center;
	if( left > maxlength )			
		maxlength = left;
	if( right > maxlength )			
		maxlength = right;
	if( lefttop > maxlength )		
		maxlength = lefttop;
	if( rightbottom > maxlength )	
		maxlength = rightbottom;

	return maxlength;
}

int CNodeView::BreakNode(CBranchView* pbranchview)
{
	int																rv = 0;
	// Center�� �ڽĳ����� ���ȣ��
	if(m_pCenter!=NULL)												rv = m_pCenter->BreakNode( pbranchview );

	double															dLeftLength;
	double															dRightLength;
	double															dLeftTopLength;
	double															dRightBottomLength;

	dLeftLength														= 0;
	dRightLength													= 0;
	dLeftTopLength													= 0;
	dRightBottomLength												= 0;
	if( m_nSwKindID == -1000 || m_nSwKindID == NDTYPE_DUMMY ) // ���� ���� DM�̸�
	{
		if( m_pLeft != NULL )										dLeftLength			= m_pLeft->GetLongestPathLength( pbranchview );
		if( m_pRight != NULL )										dRightLength		= m_pRight->GetLongestPathLength( pbranchview );
		if( m_pLeftTop != NULL )									dLeftTopLength		= m_pLeftTop->GetLongestPathLength( pbranchview );
		if( m_pRightBottom != NULL )								dRightBottomLength	= m_pRightBottom->GetLongestPathLength( pbranchview );

		if( (dLeftLength == 0) && (dRightLength == 0) )				return rv;

		if( rv%2 == 1 )
		{
			if( dLeftLength > dRightLength )
			{
				// �����ʰ� ���� ����
				CNodeView* pImsi;
				pImsi = m_pRight;
				m_pRight = m_pLeft;
				m_pLeft = pImsi;
			}

			//����-�������� ���̰� ������ �밢������ ������ �켱! �ٸ��� ª���� �켱!
			if( dLeftLength == dRightLength )
			{
				if( dLeftTopLength > dRightBottomLength )
				{
					// �����ʰ� ���� ����
					CNodeView* pImsi;
					pImsi = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = pImsi;
				}
			}
			else
			{
				if( dLeftTopLength < dRightBottomLength )
				{
					// �����ʰ� ���� ����
					CNodeView* pImsi;
					pImsi = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = pImsi;
				}
			}
		}
		else
		{
			if( dLeftLength < dRightLength )
			{
				// �����ʰ� ���� ����
				CNodeView* pImsi;
				pImsi = m_pRight;
				m_pRight = m_pLeft;
				m_pLeft = pImsi;
			}

			if( dLeftLength == dRightLength )
			{
				if( dLeftTopLength < dRightBottomLength )
				{
					// �����ʰ� ���� ����
					CNodeView* pImsi;
					pImsi = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = pImsi;
				}
			}
			else
			{
				if( dLeftTopLength > dRightBottomLength )
				{
					// �����ʰ� ���� ����
					CNodeView* pImsi;
					pImsi = m_pRightBottom;
					m_pRightBottom = m_pLeftTop;
					m_pLeftTop = pImsi;
				}
			}
		}

		if( m_pLeft )											m_pLeft->SetLongestPathToRightTop( 3, pbranchview );
		if( m_pRight )											m_pRight->SetLongestPathToRightBottom( 1, pbranchview );
		if( m_pLeftTop )										m_pLeftTop->SetLongestPathToRightTop( 3, pbranchview );
		if( m_pRightBottom )									m_pRightBottom->SetLongestPathToRightBottom( 1, pbranchview );

		rv++;
	}

	return rv;
}

// int CNodeView::BreakNode(CBranchView* pbranchview)
// {
// 	int rv = 0;
// 	double leftL,rightL;
// 	// Center�� �ڽĳ����� ���ȣ��
// 	if(m_pCenter!=NULL){
// 		rv = m_pCenter->BreakNode( pbranchview );
// 	}
// 	leftL = rightL = 0;
// 	if( m_nSwKindID == -1000 || m_nSwKindID == NDTYPE_DUMMY ) // ���� ���� DM�̸�
// 	{
// 		if( m_pLeft!=NULL )
// 			leftL = m_pLeft->GetLongestPathLength( pbranchview );
// 		if( m_pRight!=NULL )
// 			rightL = m_pRight->GetLongestPathLength( pbranchview );
// 		if( leftL > 0 || rightL > 0 ) rv++;
// 	}
// 	if( rv%2 == 1 )
// 	{
// 		if( m_nSwKindID == -1000 || m_nSwKindID == NDTYPE_DUMMY ) // ���� ���� DM�̸�
// 		{
// 			if( m_pLeft!=NULL )
// 				leftL = m_pLeft->GetLongestPathLength( pbranchview );
// 			else
// 				leftL = 0;
// 			if( m_pRight!=NULL )
// 				rightL = m_pRight->GetLongestPathLength( pbranchview );
// 			else
// 				rightL = 0;
// 			if( leftL < rightL )
// 			{
// 				// �����ʰ� ���� ����
// 				CNodeView* pImsi;
// 				pImsi = m_pRight;
// 				m_pRight = m_pLeft;
// 				m_pLeft = pImsi;
// 
// 				//�¿찡 �ٲ� ������ ���������� ��ġ�� �ٽ� �ٲ��ش�.
// 				if( m_pLeft )
// 					m_pLeft->SetLongestPathToRightTop( 3, pbranchview );
// 				if( m_pRight )
// 					m_pRight->SetLongestPathToRightBottom( 1, pbranchview );
// 			}
// 		}
// 	}
// 	return rv;
// }

void CNodeView::CalculateAxis(int direction, double length, double length2, int prex, int prey, CBranchView* pbranchviewheader, CNodeView* prevNode )
{
	m_nDirection								= (direction%1000);
	if( direction >= 1000 )						m_nDirection2 = 1;

	int											nTargetlength;
	int											nCrosslength;
	nTargetlength								= (int)(length*GRID_GAP);//������
	nCrosslength								= (int)(length2*GRID_GAP);//Cross Direction->�밢����
	// �б⼱���� ���⿡ ���� ��ǥ�� �����.
	switch(m_nDirection)
	{
		// �б⼱�ΰ� ���������� ���� ���
	case 0:
		{
			// X���� ��ǥ�� �����ϰ�, �밢���ϰ�� ���⿡ ���� Y�൵ ����
			m_nPosX								= prex+nTargetlength;

			if( direction >= 2000 )				m_nPosY = prey-nCrosslength;//RightBottom
			else if( direction >= 1000 )		m_nPosY = prey+nCrosslength;//LeftTop
			else								m_nPosY = prey;
		}
		break;
		// �б⼱�ΰ� �Ʒ��� ���� ���
	case 1:
		{
			// Y���� ��ǥ�� �����ϰ�, �밢���ϰ�� ���⿡ ���� X�൵ ����
			if( direction >= 2000 )				m_nPosX = prex+nCrosslength;//RightBottom
			else if( direction >= 1000 )		m_nPosX = prex-nCrosslength;//LeftTop
			else								m_nPosX = prex;
			
			m_nPosY								= prey+nTargetlength;
		}
		break;
		// �б⼱�ΰ� �������� ���� ���
	case 2:
		{
			// X���� ��ǥ�� �����ϰ�, �밢���ϰ�� ���⿡ ���� Y�൵ ����
			m_nPosX								= prex-nTargetlength;

			if( direction >= 2000 )				m_nPosY = prey+nCrosslength;//RightBottom
			else if( direction >= 1000 )		m_nPosY = prey-nCrosslength;//LeftTop
			else								m_nPosY = prey;
		}
		break;
		// �б⼱�ΰ� ���� ���� ���
	case 3:
		{
			// Y���� ��ǥ�� �����ϰ�, �밢���ϰ�� ���⿡ ���� X�൵ ����
			if( direction >= 2000 )				m_nPosX = prex-nCrosslength;//RightBottom
			else if( direction >= 1000 )		m_nPosX = prex+nCrosslength;//LeftTop
			else								m_nPosX = prex;

			m_nPosY								= prey-nTargetlength;
		}
		break;
	}

	// ��� �ڽĳ����� ���ȣ��
	CBranchView* pBranchView;
	if(m_pCenter!=NULL) 
	{
		pBranchView = pbranchviewheader->GetBranchView(m_nDbID,m_pCenter->m_nDbID);
		//��ȸ�� ������ ������ ���, �Դ��������� �ѹ� ������!
		if( (prevNode && prevNode->m_nSwKindID == -1000) )
		{
			if( (pBranchView->GetLengthDisp2() == 0) && (direction>=1000) && (m_pCenter->m_nSwKindID != NDTYPE_BACKUP) )
				pBranchView->IncreaseLengthDisp2();

			m_pCenter->CalculateAxis(direction,pBranchView->GetLengthDisp(),pBranchView->GetLengthDisp2(),m_nPosX,m_nPosY,pbranchviewheader, this);
		}
		else
			m_pCenter->CalculateAxis(m_nDirection,pBranchView->GetLengthDisp(),pBranchView->GetLengthDisp2(),m_nPosX,m_nPosY,pbranchviewheader, this);
	}
	// ������ �ڽĳ����� ���ȣ��
	if(m_pRight!=NULL) 
	{
		pBranchView = pbranchviewheader->GetBranchView(m_nDbID,m_pRight->m_nDbID);
		m_pRight->CalculateAxis((m_nDirection+5)%4,pBranchView->GetLengthDisp(),pBranchView->GetLengthDisp2(),m_nPosX,m_nPosY,pbranchviewheader, this);
	}
	// ���� �ڽĳ����� ���ȣ��
	if(m_pLeft!=NULL) 
	{
		pBranchView = pbranchviewheader->GetBranchView(m_nDbID,m_pLeft->m_nDbID);
		m_pLeft->CalculateAxis((m_nDirection+3)%4,pBranchView->GetLengthDisp(),pBranchView->GetLengthDisp2(),m_nPosX,m_nPosY,pbranchviewheader, this);
	}
	//LeftTop �ڽĳ��� ���ȣ��
	if( m_pLeftTop!=NULL) 
	{
		pBranchView = pbranchviewheader->GetBranchView(m_nDbID,m_pLeftTop->m_nDbID);
		if( (m_nSwKindID != -1000) )
		{
			if( pBranchView->GetLengthDisp2() == 0 )
				pBranchView->IncreaseLengthDisp2();
		}
		m_pLeftTop->CalculateAxis(((m_nDirection+3)%4)+1000, pBranchView->GetLengthDisp(),pBranchView->GetLengthDisp2(), m_nPosX, m_nPosY,pbranchviewheader, this);
	}
	//rightbottom �ڽĳ��� ���ȣ��
	if( m_pRightBottom!=NULL) 
	{
		pBranchView = pbranchviewheader->GetBranchView(m_nDbID,m_pRightBottom->m_nDbID);
		if( (m_nSwKindID != -1000) )
		{
			if( pBranchView->GetLengthDisp2() == 0 )
				pBranchView->IncreaseLengthDisp2();
		}
		m_pRightBottom->CalculateAxis(((m_nDirection+5)%4)+2000, pBranchView->GetLengthDisp(),pBranchView->GetLengthDisp2(), m_nPosX, m_nPosY,pbranchviewheader, this);
	}
}

void CNodeView::SetBranchPosition( CBranchView* pbranchview )
{
	//�ڽĳ����� ���ȣ��
	if(m_pCenter!=NULL){
		pbranchview->SetPosition(m_nDbID,m_pCenter->m_nDbID,m_nPosX,m_nPosY,m_pCenter->m_nPosX,m_pCenter->m_nPosY);
		m_pCenter->SetBranchPosition(pbranchview);
	}
	if(m_pRight!=NULL){
		pbranchview->SetPosition(m_nDbID,m_pRight->m_nDbID,m_nPosX,m_nPosY,m_pRight->m_nPosX,m_pRight->m_nPosY);
		m_pRight->SetBranchPosition(pbranchview);
	}
	if(m_pLeft!=NULL){
		pbranchview->SetPosition(m_nDbID,m_pLeft->m_nDbID,m_nPosX,m_nPosY,m_pLeft->m_nPosX,m_pLeft->m_nPosY);
		m_pLeft->SetBranchPosition(pbranchview);
	}
	if(m_pLeftTop!=NULL){
		pbranchview->SetPosition(m_nDbID,m_pLeftTop->m_nDbID,m_nPosX,m_nPosY,m_pLeftTop->m_nPosX,m_pLeftTop->m_nPosY);
		m_pLeftTop->SetBranchPosition(pbranchview);
	}
	if(m_pRightBottom!=NULL){
		pbranchview->SetPosition(m_nDbID,m_pRightBottom->m_nDbID,m_nPosX,m_nPosY,m_pRightBottom->m_nPosX,m_pRightBottom->m_nPosY);
		m_pRightBottom->SetBranchPosition(pbranchview);
	}
}

BOOL CNodeView::CheckPosition( CNodeView* pRootNode, CBranchView* pRootBranch )
{
	int														nFromNodeID		= 0;
	int														nToNodeID		= 0;
	CNodeView*												pSamePosNode	= NULL;
	CNodeView*												pCrossNode		= NULL;

	if( (m_nTongID == 0) || (m_nSwKindID == -1000))//��ȸ�ΰ� �ƴϰų�, ��ȸ�ζ�� ��������϶��� Ȯ��(��ȸ�� ���ڵ��� ������ ������ġ�ϱ� ������̿����� Ȯ���ϸ� ��)
	{
		//������� �ߺ��Ǵ� ��尡 �ִ��� Ȯ���Ѵ�.
		pSamePosNode										= pRootNode->FindSamePosition( this );
		if( pSamePosNode )
		{
			//Cross�б⸦ ã������ Ž���� �����Ѵ�.
			pRootNode->CheckCrossPosition( this, pSamePosNode );
			//Cross�б⸦ ���Ѵ�.
			pCrossNode = pRootNode->FindCrossNode();

			//(1) -> �˻����س��(this)
			//(2) -> ��ġ�³��(pSamePosNode)
			//(3) -> Cross�б���(pCrossNode)

			CNodeView*						pPathNode		= NULL;
			CNodeView*						pFwNode			= NULL;
			CNodeView*						pBwNode			= NULL;
			int								nNextDirection	= 0;
			if( (pCrossNode == pRootNode) )
			{//(3)�� ����??? -> (2)�� (1) ������ ���Ƶ��� �����. ��,(3) = (1)��
				//(1)���� (2)�� ���鼭 (2)�� �ݴ�������� ���� ù��° �б⸦ �ø���.

				//(1)���� (2)�� ���ϴ� PathNode�� ���Ѵ�.
				pPathNode					= this->FindDirectPathNode( pSamePosNode );
				//Branch ħ���� (1)��(2)�� �ݴ��ϼ� ����. ���� Path�� ��ã���� �ݴ�ε� ã�ƺ���.
				if( pPathNode == NULL )
				{
					pPathNode				= pSamePosNode->FindDirectPathNode( this );
				}

				if( pPathNode != NULL )//NULL�ϸ��� ����!
				{
					int						nDirection		= 0;
					CNodeView*				pTargetNode		= NULL;

					//(2)�� �ݴ������ ����Ѵ�.
					nDirection				= ((pSamePosNode->m_nDirection+2) % 4);
					//nDirection�������� ���� ù��° �б⸦ ã�´�.
					pTargetNode				= pPathNode->FindTargetNode( nDirection );

					if( pTargetNode != NULL )//NULL�ϸ��� ����!
					{
						if ( pTargetNode->m_nSwKindID == -1000 )
						{
							pFwNode					= pTargetNode->GetNextPathNode(nNextDirection);
							pBwNode					= pFwNode->GetNextPathNode();
						}
						else
						{
							pFwNode					= pPathNode;
							pBwNode					= pFwNode->GetNextPathNode(nNextDirection);
						}

						CBranchView*				pTargetBranch;
						pTargetBranch				= pRootBranch->GetBranchView(pFwNode->m_nDbID, pBwNode->m_nDbID);
						if( pTargetBranch )
						{
							pTargetBranch->IncreaseLengthDisp();
						}

						delete pPathNode;//�ӽ÷� �� �޸𸮴ϱ� ������!
						pPathNode = NULL;
						if( pTargetBranch->GetLengthDisp() > 100 )	return FALSE;
						else										return TRUE;
					}
					else
					{
						delete pPathNode;//�ӽ÷� �� �޸𸮴ϱ� ������!
						pPathNode = NULL;
						AfxMessageBox( _T("�̷����� ���µ�?") );
					}
				}
				else
				{
					AfxMessageBox( _T("�̷����� ���µ�?") );
				}
			}
			else if( (pCrossNode->m_nDirection == pSamePosNode->m_nDirection) )
			{//(3)�� Center���� ���ʿ��� ��ħ, CrossNode�� Center line���� ��ħ, (1)�� (3)�� Center�������� ���Ƶ��� �����
				//(3)���� (1)�� ���� ù��° �б⸦ �ø���.

				//(3)���� (1)�� ���ϴ� PathNode�� ���Ѵ�.
				pPathNode					= pCrossNode->FindDirectPathNode( this );

				if( pPathNode != NULL )//NULL�ϸ��� ����!
				{
					if ( pPathNode->m_nSwKindID == -1000 )
					{
						pFwNode					= pPathNode->GetNextPathNode(nNextDirection);
						pBwNode					= pFwNode->GetNextPathNode();
					}
					else
					{
						pFwNode					= pPathNode;
						pBwNode					= pFwNode->GetNextPathNode(nNextDirection);
					}

					CBranchView*				pTargetBranch;
					pTargetBranch				= pRootBranch->GetBranchView(pFwNode->m_nDbID, pBwNode->m_nDbID);
					if( pTargetBranch )
					{
						//���Branch�� ������ �밢���̸� Left, Right���⵵ Ȯ������.
						if( nNextDirection == 4 )//���бⰡ LeftTop�϶�,
						{
							//LeftTop�б� 1ĭ����(Left�� ������ ����)
							pTargetBranch->IncreaseLengthDisp();

							//Left�бⰡ �밢�б⺸�� ª���� Left�б⵵ �÷���.
							if( pCrossNode->m_nSwKindID == -1000 )
							{
								nFromNodeID		= pCrossNode->m_pLeft->m_nDbID;
								nToNodeID		= pCrossNode->m_pLeft->m_pCenter->m_nDbID;
							}
							else
							{
								nFromNodeID		= pCrossNode->m_nDbID;
								nToNodeID		= pCrossNode->m_pLeft->m_nDbID;
							}
							CBranchView*		pLeftBranch;
							pLeftBranch			= pRootBranch->GetBranchView(nFromNodeID, nToNodeID);
							if( pLeftBranch )
							{
								if( pLeftBranch->GetLengthDisp() <= pTargetBranch->GetLengthDisp() )
									pLeftBranch->IncreaseLengthDisp();
							}
						}
						else if( nNextDirection == 5 )//���бⰡ RightBottom�϶�,
						{
							//RightBottom�б� 1ĭ����(Right�� ������ ����)
							pTargetBranch->IncreaseLengthDisp();

							//Right�бⰡ �밢�б⺸�� ª���� Right�б⵵ �÷���.
							if( pCrossNode->m_nSwKindID == -1000 )
							{
								nFromNodeID		= pCrossNode->m_pRight->m_nDbID;
								nToNodeID		= pCrossNode->m_pRight->m_pCenter->m_nDbID;
							}
							else
							{
								nFromNodeID		= pCrossNode->m_nDbID;
								nToNodeID		= pCrossNode->m_pRight->m_nDbID;
							}
							CBranchView*		pRightBranch;
							pRightBranch		= pRootBranch->GetBranchView(nFromNodeID, nToNodeID);
							if( pRightBranch )
							{
								if( pRightBranch->GetLengthDisp() <= pTargetBranch->GetLengthDisp() )
									pRightBranch->IncreaseLengthDisp();
							}
						}
						else
						{
							//�밢�бⰡ �ƴϸ� �׳� 1ĭ����.
							pTargetBranch->IncreaseLengthDisp();
						}

						delete pPathNode;//�ӽ÷� �� �޸𸮴ϱ� ������!
						pPathNode = NULL;
						if( pTargetBranch->GetLengthDisp() > 100 )	return FALSE;
						else										return TRUE;
					}
					else
					{

						delete pPathNode;//�ӽ÷� �� �޸𸮴ϱ� ������!
						pPathNode = NULL;
						AfxMessageBox( _T("�̷����� ���µ�?") );
					}
				}
				else
				{
					AfxMessageBox( _T("�̷����� ���µ�?") );
				}
			}
			else
			{//(3)�� Center���� ���ʿ��� ��ħ, �Ϲ����� ���
				//(3)���� (2)�� ���� ù��° �б⸦ �ø���.

				//(3)���� (2)�� ���ϴ� PathNode�� ���Ѵ�.
				pPathNode					= pCrossNode->FindDirectPathNode( pSamePosNode );
				if( pPathNode != NULL )//NULL�ϸ��� ����!
				{
					if ( pPathNode->m_nSwKindID == -1000 )
					{
						pFwNode					= pPathNode->GetNextPathNode(nNextDirection);
						pBwNode					= pFwNode->GetNextPathNode();
					}
					else
					{
						pFwNode					= pPathNode;
						pBwNode					= pFwNode->GetNextPathNode(nNextDirection);
					}

					CBranchView*				pTargetBranch;
					pTargetBranch				= pRootBranch->GetBranchView(pFwNode->m_nDbID, pBwNode->m_nDbID);
					if( pTargetBranch )
					{
						//���Branch�� ������ �밢���̸� Center���⵵ Ȯ������.
						if( nNextDirection >= 4 )//�밢�б��϶�, LeftTop(4), RightBottom(5)
						{
							//�밢�б� 1ĭ����(Left/Right�� ��������)
							pTargetBranch->IncreaseLengthDisp2();
							//Center�бⰡ �밢�б⺸�� ª���� Center�б⵵ �÷���.
							if( pCrossNode->m_nSwKindID == -1000 )
							{
								nFromNodeID		= pCrossNode->m_pCenter->m_nDbID;
								nToNodeID		= pCrossNode->m_pCenter->m_pCenter->m_nDbID;
							}
							else
							{
								nFromNodeID		= pCrossNode->m_nDbID;
								nToNodeID		= pCrossNode->m_pCenter->m_nDbID;
							}
							CBranchView*			pCenterBranch;
							pCenterBranch			= pRootBranch->GetBranchView(nFromNodeID, nToNodeID);
							if( pCenterBranch )
							{
								if( pCenterBranch->GetLengthDisp() <= pTargetBranch->GetLengthDisp2() )
									pCenterBranch->IncreaseLengthDisp();
							}
						}
						else
						{
							//�밢�бⰡ �ƴϸ� �׳� 1ĭ����.
							pTargetBranch->IncreaseLengthDisp();
						}

						delete pPathNode;//�ӽ÷� �� �޸𸮴ϱ� ������!
						pPathNode = NULL;

						if( pTargetBranch->GetLengthDisp() > 100 )	return FALSE;
						else										return TRUE;
					}
					else
					{
						delete pPathNode;//�ӽ÷� �� �޸𸮴ϱ� ������!
						pPathNode = NULL;
						AfxMessageBox( _T("�̷����� ���µ�?") );
					}
				}
				else
				{
					AfxMessageBox( _T("�̷����� ���µ�?") );
				}
			}
		}
	}

	if(m_pRight != NULL)
	{
		if( m_pRight->CheckPosition(pRootNode, pRootBranch) )
			return TRUE;
	}
	if(m_pLeft != NULL)
	{
		if( m_pLeft->CheckPosition(pRootNode, pRootBranch) )
			return TRUE;
	}
	if(m_pLeftTop != NULL)
	{
		if( !((m_pLeftTop->m_pCenter) && (m_pLeftTop->m_pCenter->m_nSwKindID == NDTYPE_BACKUP)) )
		{
			if( m_pLeftTop->CheckPosition(pRootNode, pRootBranch) )
				return TRUE;
		}
	}
	if(m_pRightBottom != NULL)
	{
		if( !((m_pRightBottom->m_pCenter) && (m_pRightBottom->m_pCenter->m_nSwKindID == NDTYPE_BACKUP)) )
		{
			if( m_pRightBottom->CheckPosition(pRootNode, pRootBranch) )
				return TRUE;
		}
	}
	if(m_pCenter != NULL)//CASE�� ����ϱ� ���� �б⸦ ���� Ž���ϰ�, CENTER�� ����!! �̷��� �ϸ� CrossNode�� CENTER������ �������� ������ ���ʳ��(����=this)�� ��ġ�� ���ʳ��(��ħ���=pSamePosNode ������.
	{
		if( m_pCenter->CheckPosition(pRootNode, pRootBranch) )
			return TRUE;
	}

	return FALSE;
}

int CNodeView::CheckCrossPosition( CNodeView* pNode1, CNodeView* pNode2 )
{
	m_nCrossCnt															= 0;

	int																	nCnt = 0;
	if ( (pNode1 == this) || (pNode2 == this) )								
		return 1;

	if(m_pCenter != NULL)												nCnt += m_pCenter->CheckCrossPosition(pNode1, pNode2);
	if(m_pRight != NULL)												nCnt += m_pRight->CheckCrossPosition(pNode1, pNode2);
	if(m_pLeft != NULL)													nCnt += m_pLeft->CheckCrossPosition(pNode1, pNode2);
	if(m_pLeftTop != NULL)												nCnt += m_pLeftTop->CheckCrossPosition(pNode1, pNode2);
	if(m_pRightBottom != NULL)											nCnt += m_pRightBottom->CheckCrossPosition(pNode1, pNode2);

	m_nCrossCnt															= nCnt;

	return nCnt;
}

CNodeView* CNodeView::FindCrossNode()
{
	BOOL bFind = TRUE;
	if(m_pCenter != NULL)
	{
		if( m_pCenter->m_nCrossCnt > 1 )
			return m_pCenter->FindCrossNode();
	}
	if(m_pRight != NULL)
	{
		if( m_pRight->m_nCrossCnt > 1 )
			return m_pRight->FindCrossNode();
	}
	if(m_pLeft != NULL)
	{
		if( m_pLeft->m_nCrossCnt > 1 )
			return m_pLeft->FindCrossNode();
	}
	if(m_pLeftTop != NULL)
	{
		if( m_pLeftTop->m_nCrossCnt > 1 )
			return m_pLeftTop->FindCrossNode();
	}
	if(m_pRightBottom != NULL)
	{
		if( m_pRightBottom->m_nCrossCnt > 1 )
			return m_pRightBottom->FindCrossNode();
	}

	return this;
}

CNodeView* CNodeView::FindDirectPathNode( CNodeView* pTargetNode )
{
	if( pTargetNode == this )											return this->Copy();

	CNodeView*															pNextNode;
	if(m_pCenter != NULL)
	{
		pNextNode														= m_pCenter->FindDirectPathNode( pTargetNode );
		if( pNextNode )
		{
			CNodeView*													pNode;
			pNode														= this->Copy();
			pNode->m_pCenter											= pNextNode;
			return pNode;
		}
	}
	if(m_pLeft != NULL)
	{
		pNextNode														= m_pLeft->FindDirectPathNode( pTargetNode );
		if( pNextNode )
		{
			CNodeView*													pNode;
			pNode														= this->Copy();
			pNode->m_pLeft												= pNextNode;
			return pNode;
		}
	}
	if(m_pRight != NULL)
	{
		pNextNode														= m_pRight->FindDirectPathNode( pTargetNode );
		if( pNextNode )
		{
			CNodeView*													pNode;
			pNode														= this->Copy();
			pNode->m_pRight												= pNextNode;
			return pNode;
		}
	}
	if(m_pLeftTop != NULL)
	{
		pNextNode														= m_pLeftTop->FindDirectPathNode( pTargetNode );
		if( pNextNode )
		{
			CNodeView*													pNode;
			pNode														= this->Copy();
			pNode->m_pLeftTop											= pNextNode;
			return pNode;
		}
	}
	if(m_pRightBottom != NULL)
	{
		pNextNode														= m_pRightBottom->FindDirectPathNode( pTargetNode );
		if( pNextNode )
		{
			CNodeView*													pNode;
			pNode														= this->Copy();
			pNode->m_pRightBottom										= pNextNode;
			return pNode;
		}
	}

	return NULL;
}

CNodeView* CNodeView::FindTargetNode( int nDirection )
{
	if( m_pCenter != NULL )
	{
		if( m_pCenter->m_nDirection == nDirection )
			return this;

		return m_pCenter->FindTargetNode( nDirection );
	}
	if( m_pRight != NULL )
	{
		if( m_pRight->m_nDirection == nDirection )
			return this;

		return m_pRight->FindTargetNode( nDirection );
	}
	if( m_pLeft != NULL )
	{
		if( m_pLeft->m_nDirection == nDirection )
			return this;

		return m_pLeft->FindTargetNode( nDirection );
	}
	if( m_pLeftTop != NULL )
	{
		if( m_pLeftTop->m_nDirection == nDirection )
			return this;

		return m_pLeftTop->FindTargetNode( nDirection );
	}
	if( m_pRightBottom != NULL )
	{
		if( m_pRightBottom->m_nDirection == nDirection )
			return this;

		return m_pRightBottom->FindTargetNode( nDirection );
	}

	return NULL;
}

int CNodeView::GetMaxAxisX()
{
	int																	xmaxcenter		= 0;
	int																	xmaxright		= 0;
	int																	xmaxleft		= 0;
	int																	xmaxrightbottom	= 0;
	int																	xmaxlefttop		= 0;
	int																	xmax			= 0;

	// �ڽĳ����� ���ȣ��
	if(m_pCenter!=NULL)													xmaxcenter		= m_pCenter->GetMaxAxisX();
	if(m_pRight!=NULL)													xmaxright		= m_pRight->GetMaxAxisX();
	if(m_pLeft!=NULL)													xmaxleft		= m_pLeft->GetMaxAxisX();
	if(m_pLeftTop!=NULL)												xmaxlefttop		= m_pLeftTop->GetMaxAxisX();
	if(m_pRightBottom!=NULL)											xmaxrightbottom	= m_pRightBottom->GetMaxAxisX();

	// �ڽĳ��鿡�� ���ϵ� ���� �������� X��ǥ�� ����Ͽ� �ִ�ġ�� ������
	xmax = m_nPosX;
	if(xmaxcenter>xmax)													xmax=xmaxcenter;
	if(xmaxright>xmax)													xmax=xmaxright;
	if(xmaxleft>xmax)													xmax=xmaxleft;
	if(xmaxlefttop>xmax)												xmax=xmaxlefttop;
	if(xmaxrightbottom>xmax)											xmax=xmaxrightbottom;

	return(xmax);
}

int CNodeView::GetMinAxisX()
{
	int xmincenter=0;
	int xminright=0;
	int xminleft=0;
	int xminlefttop=0;
	int xminrightbottom=0;
	int xmin=0;

	// // �ڽĳ����� ���ȣ��
	if(m_pCenter!=NULL)													xmincenter		= m_pCenter->GetMinAxisX();
	if(m_pRight!=NULL)													xminright		= m_pRight->GetMinAxisX();
	if(m_pLeft!=NULL)													xminleft		= m_pLeft->GetMinAxisX();
	if(m_pLeftTop!=NULL)												xminlefttop		= m_pLeftTop->GetMinAxisX();
	if(m_pRightBottom!=NULL)											xminrightbottom	= m_pRightBottom->GetMinAxisX();

	// �ڽĳ��鿡�� ���ϵ� ���� �������� X��ǥ�� ����Ͽ� �ּ�ġ�� ������
	xmin = m_nPosX;
	if(xmincenter<xmin)													xmin=xmincenter;
	if(xminright<xmin)													xmin=xminright;
	if(xminleft<xmin)													xmin=xminleft;
	if(xminlefttop<xmin)												xmin=xminlefttop;
	if(xminrightbottom<xmin)											xmin=xminrightbottom;
	return(xmin);
}

int CNodeView::GetMaxAxisY()
{
	int ymaxcenter,ymaxleft,ymaxright,ymaxlefttop,ymaxrightbottom,ymax;
	ymaxcenter=ymaxleft=ymaxright=ymaxlefttop=ymaxrightbottom=ymax=0;

	//�ڽĳ����� ���ȣ��
	if(m_pCenter!=NULL)													ymaxcenter		= m_pCenter->GetMaxAxisY();
	if(m_pRight!=NULL)													ymaxright		= m_pRight->GetMaxAxisY();
	if(m_pLeft!=NULL)													ymaxleft		= m_pLeft->GetMaxAxisY();
	if(m_pLeftTop!=NULL)												ymaxlefttop		= m_pLeftTop->GetMaxAxisY();
	if(m_pRightBottom!=NULL)											ymaxrightbottom	= m_pRightBottom->GetMaxAxisY();

	ymax = m_nPosY;
	if(ymaxcenter > ymax)												ymax=ymaxcenter;
	if(ymaxright > ymax)												ymax=ymaxright;
	if(ymaxleft > ymax)													ymax=ymaxleft;
	if(ymaxlefttop > ymax)												ymax=ymaxlefttop;
	if(ymaxrightbottom > ymax)											ymax=ymaxrightbottom;

	return ymax;
}

int CNodeView::GetMinAxisY()
{
	int ymincenter,yminleft,yminright,yminlefttop,yminrightbottom,ymin;
	ymincenter=yminleft=yminright=yminlefttop=yminrightbottom=ymin=10000;

	//�ڽĳ����� ���ȣ��
	if(m_pCenter!=NULL)													ymincenter		= m_pCenter->GetMinAxisY();
	if(m_pRight!=NULL)													yminright		= m_pRight->GetMinAxisY();
	if(m_pLeft!=NULL)													yminleft		= m_pLeft->GetMinAxisY();
	if(m_pLeftTop!=NULL)												yminlefttop		= m_pLeftTop->GetMinAxisY();
	if(m_pRightBottom!=NULL)											yminrightbottom	= m_pRightBottom->GetMinAxisY();

	ymin = m_nPosY;
	if(ymincenter < ymin)												ymin=ymincenter;
	if(yminleft < ymin)													ymin=yminleft;
	if(yminright < ymin)												ymin=yminright;
	if(yminlefttop < ymin)												ymin=yminlefttop;
	if(yminrightbottom < ymin)											ymin=yminrightbottom;

	return ymin;
}

void CNodeView::ShiftPosition( int nPosX, int nPosY )
{
	m_nPosX																+= nPosX;
	m_nPosY																+= nPosY;
	//�ڽĳ����� ���ȣ��
	if(m_pCenter!=NULL)													m_pCenter->ShiftPosition( nPosX, nPosY );
	if(m_pLeft!=NULL)													m_pLeft->ShiftPosition( nPosX, nPosY );
	if(m_pRight!=NULL)													m_pRight->ShiftPosition( nPosX, nPosY );
	if(m_pLeftTop!=NULL)												m_pLeftTop->ShiftPosition( nPosX, nPosY );
	if(m_pRightBottom!=NULL)											m_pRightBottom->ShiftPosition( nPosX, nPosY );
}

// CString CNodeView::GetStrKind()
// {
// 	CString strKind;
// 	switch( m_nSwKindID ) {
// 	case 1://GA
// 	case 22:
// 	case 23:
// 	case 24:
// 	case 38:
// 	case 44:
// 	case 80:
// 	case 81:
// 	case 82:
// 	case 83:
// 	case 87:
// 	case 100://GS
// 		strKind = _T("G");
// 		break;
// 
// 	case 51:
// 	case 72:
// 		strKind = _T("IG");
// 		break;
// 		//////////////////////////////////////////////////////////////////
// 	case 26://A-Switch
// 	case 28://A-Switch
// 	case 29://A-Switch
// 	case 30://A-Switch
// 		strKind = _T("A");
// 		break;
// 	case 123://M-Switch
// 		strKind = _T("");
// 		break;
// 	case 2://RA
// 	case 10://RA
// 	case 13://RA
// 	case 14://RA
// 	case 43:
// 	case 45:
// 	case 101://RC
// 	case -1004://������ �ڵ� ��Ŭ����
// 	case -1010://�޽� ��Ŭ����
// 		strKind = _T("R");
// 		break;
// 	case 52://RA
// 	case 71://RA
// 		strKind = _T("IR");
// 		break;
// 	case -1006://EFI
// 	case 162://EFI
// 		strKind = _T("EFI");
// 		break;
// 	case 3://CB
// 	case 102://CB
// 	case 159://CB
// 		strKind = _T("CB");
// 		break;
// 	case 18://CM
// 		strKind = _T("CM");
// 		break;
// 	case 31://CA
// 		strKind = _T("CA");
// 		break;
// 	case 6://FAS
// 		strKind = _T("FA");
// 		break;
// 	case 7://FTS
// 		strKind = _T("FT");
// 		break;
// 	case 8://FTS
// 		strKind = _T("AG");
// 		break;
// 	case 64://�Ƿڱ�
// 		strKind = _T("L");
// 		break;
// 	case 112://FA
// 		strKind = _T("FS");
// 		break;
// 	case 113://FT
// 		strKind = _T("FT");
// 		break;
// 	case 103://IS
// 		strKind = _T("IS");
// 		break;
// 	case 104://SE
// 		strKind = _T("SE");
// 		break;
// 	case 105://COS
// 		strKind = _T("C");
// 		//strKind = _T("FU");
// 		break;
// 	case 108://TR
// 	case 120://LTR
// 		strKind = _T("Tr");
// 		break;
// 	case 110://ASS
// 		strKind = _T("AS");
// 		break;
// 	case 114://AG
// 		strKind = _T("AG");
// 		break;
// 	case 500://Relay��
// 	case 501://Ass��
// 		strKind = _T("��");
// 		break;
// 	case 161:// ���кл�����
// 	case 160:// �л�����
// 		strKind = _T("DG");
// 		break;
// 	case 1001:// TAP
// 		strKind = _T("T");
// 		break;
// 	case 70:// SVR
// 		strKind = _T("V");
// 		break;
// 	case 1003:// Line condensor
// 		strKind = _T("LC");
// 		break;
// 	case 170:// COS
// 		strKind = _T("C");
// 		break;
// 	case 171:// �ڵ����屸�����ܱ�
// 		strKind = _T("FS");
// 		break;
// 	case 9:
// 	case 20:
// 	case 27:
// 	case 40:
// 	case 46:
// 	case 66:
// 	case 84:
// 	case 85:
// 	case 91:
// 	case 92:
// 	case 106:
// 	case 151:
// 	case -1001:
// 	case -1002:
// 	case -1003:
// 	case -1009:
// 	case -1015:
// 	case -1024:
// 	case -1025:
// 	case -2000:
// 	case -2001:
// 		strKind = _T("G");
// 		break;
// 	case -2002:
// 		strKind = _T("EX");
// 		break;
// 	case -2005:
// 		strKind = _T("H");
// 		break;
// 	case -1007:
// 		strKind = _T("HIF");
// 		break;
// 	case -1008:
// 		strKind = _T("NEO");
// 		break;
// 	case -1011:
// 		strKind = _T("AVM");
// 		break;
// 	case -1016:
// 		strKind = _T("MF");
// 		break;
// 	case -1020:
// 	case -1021:
// 		strKind = _T("LV");
// 		break;
// 	case -1022:
// 		strKind = _T("SVR");
// 		break;
// 	case -1023:
// 		strKind = _T("ESS");
// 		break;
// 	default:
// 		strKind = _T("");
// 		break;
// 	}
// 	return strKind ;
// }

// CString CNodeView::GetKindName()
// {
// 	CString strKind;
// 	switch( m_nSwKindID ) {
// 	case -2005:		strKind = _T("Ư��� �л������� �ܸ���ġ");								break;
// 	case -2004:		strKind = _T("���ɰ��� PAD BMS");										break;
// 	case -2003:		strKind = _T("PAD BMS");												break;
// 	case -2002:		strKind = _T("���ɰ���GA BMS");											break;
// 	case -2001:		strKind = _T("GA BMS");													break;
// 	case -2000:		strKind = _T("���ɰ��� �ٱ�� �ܸ���ġ HIF");							break;
// 	case -1030:		strKind = _T("IP��� ���ߺи���(6)");									break;
// 	case -1029:		strKind = _T("IP��� ���ߺи���(5)");									break;
// 	case -1028:		strKind = _T("IP��� ���ߺи���(4)");									break;
// 	case -1027:		strKind = _T("IP��� ���ߺи���(3)");									break;
// 	case -1026:		strKind = _T("IP��� ���ߵ�����(4)");									break;
// 	case -1025:		strKind = _T("IP��� ����������");										break;
// 	case -1024:		strKind = _T("IP��� �����и���");										break;
// 	case -1023:		strKind = _T("MIDAS ESS");												break;
// 	case -1022:		strKind = _T("MIDAS SVR");												break;
// 	case -1021:		strKind = _T("MiDAS ���� �л���������");								break;
// 	case -1020:		strKind = _T("���� �л��������� �ܸ���ġ");								break;
// 	case -1019:		strKind = _T("���ɰ����ٱ�� �л����� �ܸ���ġ(6)");					break;
// 	case -1018:		strKind = _T("���ɰ����ٱ�� �л����� �ܸ���ġ(5)");					break;
// 	case -1017:		strKind = _T("���ɰ����ٱ�� �л����� �ܸ���ġ(4)");					break;
// 	case -1016:		strKind = _T("���ɰ����ٱ�� �л����� �ܸ���ġ");						break;
// 	case -1015:		strKind = _T("������ ������ �ܸ���ġ");									break;
// 	case -1014:		strKind = _T("���ɰ����ٱ�ɴܸ���ġ���忹��(6)");						break;
// 	case -1013:		strKind = _T("���ɰ����ٱ�ɴܸ���ġ���忹��(5)");						break;
// 	case -1012:		strKind = _T("���ɰ����ٱ�ɴܸ���ġ���忹��(4)");						break;
// 	case -1011:		strKind = _T("�������ܸ���ġ AVM");										break;
// 	case -1010:		strKind = _T("�޽� ��Ŭ����");											break;
// 	case -1009:		strKind = _T("�������ܸ���ġ ���忹��");								break;
// 	case -1008:		strKind = _T("FI����跮��_NEO");										break;
// 	case -1007:		strKind = _T("�������ܸ���ġHIF");										break;
// 	case -1006:		strKind = _T("�ڵ� EFI ���ܱ�");										break;
// 	case -1005:		strKind = _T("������ �ڵ� PAD sw");										break;
// 	case -1004:		strKind = _T("������ �ڵ� ��ũ����");									break;
// 	case -1003:		strKind = _T("������ �⺻�������ܸ���ġ");								break;
// 	case -1002:		strKind = _T("������ ���ɰ���GA");										break;
// 	case -1001:		strKind = _T("������ �ڵ�GA");											break;
// 	case 1:			strKind = _T("�ڵ� Sw");												break;
// 	case 2:			strKind = _T("��������");												break;
// 	case 3:			strKind = _T("�ڵ����� CB");											break;
// 	case 4:			strKind = _T("�ڵ� PAD Sw");											break;
// 	case 5:			strKind = _T("�ڵ� LG PAD Sw");											break;
// 	case 6:			strKind = _T("�ڵ� �������� Sw");										break;
// 	case 7:			strKind = _T("�ڵ� FT");												break;
// 	case 8:			strKind = _T("�ڵ� GAS ASS");											break;
// 	case 9:			strKind = _T("�ڵ� CI ���ܱ�");											break;
// 	case 10:		strKind = _T("������");													break;
// 	case 11:		strKind = _T("��Ÿ ������ġ");											break;
// 	case 12:		strKind = _T("����PAD FCI");											break;
// 	case 13:		strKind = _T("������ü��");												break;
// 	case 14:		strKind = _T("��������");												break;
// 	case 16:		strKind = _T("�и��� ��ȸ�� �����");									break;
// 	case 17:		strKind = _T("�и��� ��ȸ�� ���ܱ�");									break;
// 	case 18:		strKind = _T("FI����跮��");											break;
// 	case 19:		strKind = _T("SIX_PAD");												break;
// 	case 20:		strKind = _T("�ٱ�ɴܸ���ġ");											break;
// 	case 21:		strKind = _T("���� �ٱ�� �ܸ���ġ");									break;
// 	case 22:		strKind = _T("�ٱ�� ������");											break;
// 	case 23:		strKind = _T("���� �ٱ�� ������");										break;
// 	case 24:		strKind = _T("�ڵ� SW ���ɰ���");										break;
// 	case 25:		strKind = _T("�ڵ� PADSW ���ɰ���");									break;
// 	case 26:		strKind = _T("�ڵ�6ȸ��SW ���ɰ���");									break;
// 	case 27:		strKind = _T("GPS �ڵ� Sw");											break;
// 	case 28:		strKind = _T("GPS �ڵ� PAD Sw");										break;
// 	case 29:		strKind = _T("��Ŭ���� ���ɰ���");										break;
// 	case 30:		strKind = _T("������ ������ü RC");										break;
// 	case 31:		strKind = _T("������ ������ RC");										break;
// 	case 33:		strKind = _T("�и��� PD �����");										break;
// 	case 34:		strKind = _T("�и��� PD ���ܱ�");										break;
// 	case 37:		strKind = _T("Close-Loop �ý���");										break;
// 	case 38:		strKind = _T("��������� ���ݴܸ���ġ");								break;
// 	case 39:		strKind = _T("��������� ���ݴܸ���ġ PAD");							break;
// 	case 40:		strKind = _T("������ �ܸ���ġ");										break;
// 	case 42:		strKind = _T("CFD(�ı���ְ��尨��)");									break;
// 	case 43:		strKind = _T("���⼺ ��ȣ��� RA");										break;
// 	case 44:		strKind = _T("���⼺ ��ȣ��� GA");										break;
// 	case 45:		strKind = _T("���⼺ ��ȣ��� RC");										break;
// 	case 46:		strKind = _T("ASS ���ݴܸ���ġ");										break;
// 	case 47:		strKind = _T("HSSB");													break;
// 	case 51:		strKind = _T("������ GA");												break;
// 	case 52:		strKind = _T("������ RC");												break;
// 	case 54:		strKind = _T("4ȸPQM��ȸ�ΰ����");										break;
// 	case 59:		strKind = _T("4ȸ��PQM��ȸ�ΰ����");									break;
// 	case 60:		strKind = _T("4ȸ��PQM��ȸ�����ܱ�");									break;
// 	case 64:		strKind = _T("�Ƿڱ�");													break;
// 	case 65:		strKind = _T("�������бⰨ����ġ");										break;
// 	case 66:		strKind = _T("CSS_GA");													break;
// 	case 67:		strKind = _T("CSS_RC");													break;
// 	case 68:		strKind = _T("CSS_ACB");												break;
// 	case 69:		strKind = _T("FUSE �����");											break;
// 	case 70:		strKind = _T("SVR ���ݰ�����ġ");										break;
// 	case 71:		strKind = _T("������ RC");												break;
// 	case 72:		strKind = _T("������ GA");												break;
// 	case 73:		strKind = _T("��ü�� ��ȸ�� �����");									break;
// 	case 74:		strKind = _T("��ü�� ��ȸ�� ���ܱ�");									break;
// 	case 80:		strKind = _T("���ɰ��� �ٱ�� �ܸ���ġ");								break;
// 	case 81:		strKind = _T("���ɰ��� �ٱ�� �ܸ���ġ(4)");							break;
// 	case 82:		strKind = _T("���ɰ��� �ٱ�� �ܸ���ġ(5)");							break;
// 	case 83:		strKind = _T("���ɰ��� �ٱ�� �ܸ���ġ(6)");							break;
// 	case 84:		strKind = _T("���忹��");												break;
// 	case 85:		strKind = _T("Open Loop");												break;
// 	case 86:		strKind = _T("Open Loop(4)");											break;
// 	case 87:		strKind = _T("�⺻�����մܸ���ġ");										break;
// 	case 88:		strKind = _T("���忹��(4)");											break;
// 	case 89:		strKind = _T("���忹��(5)");											break;
// 	case 90:		strKind = _T("���忹��(6)");											break;
// 	case 91:		strKind = _T("�Ϲ�GA����������");										break;
// 	case 92:		strKind = _T("Open loop ip");											break;
// 	case 93:		strKind = _T("Open loop ip 4ȸ��");										break;
// 	case 94:		strKind = _T("SVR");													break;
// 	case 100:		strKind = _T("�Ϲ� Sw");												break;
// 	case 101:		strKind = _T("�Ϲ� Recloser");											break;
// 	case 102:		strKind = _T("�Ϲݼ��� CB");											break;
// 	case 103:		strKind = _T("Interrupt Sw");											break;
// 	case 104:		strKind = _T("Sectionalizer");											break;
// 	case 105:		strKind = _T("Cut Out Sw");												break;
// 	case 106:		strKind = _T("CI �����");												break;
// 	case 107:		strKind = _T("�Ϲ� PAD Sw");											break;
// 	case 108:		strKind = _T("���б�");													break;
// 	case 109:		strKind = _T("ALTS");													break;
// 	case 110:		strKind = _T("Auto Sectionalizer");										break;
// 	case 111:		strKind = _T("������ġ");												break;
// 	case 112:		strKind = _T("�Ϲ� �������� Sw");										break;
// 	case 113:		strKind = _T("�Ϲ� FT");												break;
// 	case 114:		strKind = _T("�Ϲ� GAS ASS");											break;
// 	case 115:		strKind = _T("23kv Bus Sec CB");										break;
// 	case 116:		strKind = _T("23kv Bus Tie CB");										break;
// 	case 117:		strKind = _T("MTR CB	");												break;
// 	case 118:		strKind = _T("���� Station");											break;
// 	case 119:		strKind = _T("���� SIX_PAD");											break;
// 	case 151:		strKind = _T("Ÿ�� SW");												break;
// 	case 152:		strKind = _T("Ÿ�� CB");												break;
// 	case 153:		strKind = _T("SP");														break;
// 	case 154:		strKind = _T("SR");														break;
// 	case 155:		strKind = _T("st");														break;
// 	case 156:		strKind = _T("�ù� MCB");												break;
// 	case 157:		strKind = _T("�ù� DS");												break;
// 	case 158:		strKind = _T("�ù� LS");												break;
// 	case 159:		strKind = _T("�ù� CB");												break;
// 	case 160:		strKind = _T("DR");														break;
// 	case 161:		strKind = _T("VCB");													break;
// 	case 162:		strKind = _T("���� EFI ���ܱ�");										break;
// 	case 163:		strKind = _T("���ϰ����� ���б�");										break;
// 	case 200:		strKind = _T("Dummy Sw");												break;
// 	case 201:		strKind = _T("���̺��Ի���");											break;
// 	case 501:		strKind = _T("���дٽ�MASTER");											break;
// 	case 502:		strKind = _T("���дٽ�ControlSlave");									break;
// 	case 503:		strKind = _T("���дٽ�SLAVE");											break;
// 	case 600:		strKind = _T("���輱��");												break;//��� ���� ���Ƿ� ������ Ÿ���ڵ��!
// 	case 1000:		strKind = _T("����DAS ���б� 4ȸ��");									break;
// 	case 1001:		strKind = _T("����DAS ������");											break;
// 	case 1010:		strKind = _T("����DAS ���� ������");									break;
// 	case 1011:		strKind = _T("����DAS ���������̼�");									break;
// 	case 1012:		strKind = _T("����DAS ���� ���б� 5ȸ��");								break;
// 	case 1013:		strKind = _T("����DAS �����Կ� �ܸ� ��ġ");								break;
// 	case 1014:		strKind = _T("����DAS ���������̼� Ȯ��");								break;
// 	case 1015:		strKind = _T("����DAS ���б� 5ȸ��");									break;
// 	case 1016:		strKind = _T("����DAS ������ ���б� 5ȸ��");							break;
// 	case 1017:		strKind = _T("����DAS Compact�� ���б�");								break;
// 	default:		strKind = _T("");														break;
// 	}
// 	return strKind ;
// }

CString CNodeView::GetStrKind()
{
	CString																strKind;
	if( m_nSwKindID == NDTYPE_SWITCH )
	{
		if( m_nKCIMType == KCIMTYPE_CB)									strKind = _T("CB");
		else if( m_nKCIMType == KCIMTYPE_RC)							strKind = _T("R");
		else if( m_nKCIMType == KCIMTYPE_COS)							strKind = _T("C");
		else if( m_nKCIMType == KCIMTYPE_EFI)							strKind = _T("EFI");
		else if (m_nKCIMType == KCIMTYPE_LV)							strKind = _T("LV");
		else if (m_nKCIMType == KCIMTYPE_HV)							strKind = _T("HV");
		else if (m_nKCIMType == KCIMTYPE_HVE)							strKind = _T("HVe");
		else															strKind = _T("S");
	}
	else if( m_nSwKindID == NDTYPE_GEN )								strKind = _T("DG");
	else if( m_nSwKindID == NDTYPE_SVR )								strKind = _T("SVR");
	else if( m_nSwKindID == NDTYPE_ESS )								strKind = _T("ESS");
	else if( m_nSwKindID == NDTYPE_SHUNTEQ )							strKind = _T("SH");
	else if( m_nSwKindID == NDTYPE_SVC )								strKind = _T("SVC");
	else if( m_nSwKindID == NDTYPE_BACKUP )								strKind = _T("");
	else																strKind = _T("");

	return strKind;
}

CString CNodeView::GetKindName()
{
	CString																strKind;
	if( m_nSwKindID == NDTYPE_SWITCH )
	{
		if( m_nKCIMType == KCIMTYPE_CB)									strKind = _T("��������CB");
		else if( m_nKCIMType == KCIMTYPE_RC)							strKind = _T("RC");
		else if( m_nKCIMType == KCIMTYPE_COS )							strKind = _T("COS");
		else if( m_nKCIMType == KCIMTYPE_EFI)							strKind = _T("EFI");
		else if (m_nKCIMType == KCIMTYPE_LV)							strKind = _T("LV");
		else if (m_nKCIMType == KCIMTYPE_HV)							strKind = _T("HV");
		else if (m_nKCIMType == KCIMTYPE_HVE)							strKind = _T("HVe");
		else															strKind = _T("�Ϲݰ����");
	}
	else if (m_nSwKindID == NDTYPE_MULTI)
	{
		if (m_nKCIMType == KCIMTYPE_CB)									strKind = _T("��������CB");
		else if (m_nKCIMType == KCIMTYPE_RC)							strKind = _T("RC");
		else if (m_nKCIMType == KCIMTYPE_COS)							strKind = _T("COS");
		else if (m_nKCIMType == KCIMTYPE_EFI)							strKind = _T("EFI");
		else if (m_nKCIMType == KCIMTYPE_LV)							strKind = _T("LV");
		else if (m_nKCIMType == KCIMTYPE_HV)							strKind = _T("HV");
		else if (m_nKCIMType == KCIMTYPE_HVE)							strKind = _T("HVe");
		else															strKind = _T("��ȸ�δ���");
	}
	else if( m_nSwKindID == NDTYPE_GEN )								strKind = _T("�л�����");
	else if( m_nSwKindID == NDTYPE_SVR )								strKind = _T("SVR");
	else if( m_nSwKindID == NDTYPE_ESS )								strKind = _T("ESS���͸�");
	else if( m_nSwKindID == NDTYPE_SHUNTEQ )							strKind = _T("SHUNTEQ");
	else if( m_nSwKindID == NDTYPE_SVC )								strKind = _T("SVC");
	else if( m_nSwKindID == NDTYPE_TR )									strKind = _T("���б�");
	else if( m_nSwKindID == NDTYPE_ALTS )								strKind = _T("ALTS");
	else if( m_nSwKindID == NDTYPE_BACKUP )								strKind = _T("���輱��");
	else if( m_nSwKindID == NDTYPE_CUSTOMER )							strKind = _T("��");
	else																strKind = _T("Dummy");

	return strKind;
}

CNodeView* CNodeView::Copy()
{
	CNodeView*															pNodeView;
	pNodeView															= new CNodeView();
	pNodeView->m_nDbID													= m_nDbID;
	pNodeView->m_nSwKindID												= m_nSwKindID;
	pNodeView->m_nKCIMType												= m_nKCIMType;
	pNodeView->m_nCeqType												= m_nCeqType;
	pNodeView->m_szLoc													= m_szLoc;
	pNodeView->m_szLocNo												= m_szLocNo;
	pNodeView->m_bStatus												= m_bStatus;
	pNodeView->m_nTongID												= m_nTongID;
	pNodeView->m_nCaption												= m_nCaption;
	pNodeView->m_nDirection												= m_nDirection;
	pNodeView->m_nDirection2											= m_nDirection2;
	pNodeView->m_nNDID[0]												= m_nNDID[0];
	pNodeView->m_nNDID[1]												= m_nNDID[1];
	pNodeView->m_szCEQID												= m_szCEQID;
	pNodeView->m_nALTSCBSW												= m_nALTSCBSW;

	return pNodeView;
}

CNodeView* CNodeView::GetNextPathNode(int& nDirection)
{
	if(m_pCenter != NULL)
	{
		nDirection	= 1;
		return m_pCenter;
	}
	else if(m_pLeft != NULL)
	{
		nDirection = 2;
		return m_pLeft;
	}
	else if(m_pRight != NULL)
	{
		nDirection = 3;
		return m_pRight;
	}
	else if(m_pLeftTop != NULL)
	{
		nDirection = 4;
		return m_pLeftTop;
	}
	else if(m_pRightBottom != NULL)
	{
		nDirection = 5;
		return m_pRightBottom;
	}
	else
	{
		nDirection = 0;
		return NULL;
	}
}
CNodeView* CNodeView::GetNextPathNode()
{
	if(m_pCenter != NULL)												return m_pCenter;
	else if(m_pLeft != NULL)											return m_pLeft;
	else if(m_pRight != NULL)											return m_pRight;
	else if(m_pLeftTop != NULL)											return m_pLeftTop;
	else if(m_pRightBottom != NULL)										return m_pRightBottom;
	else																return NULL;
}

BOOL CNodeView::IsOverlapNode( CNodeView* pRootNode, CBranchView* pRootBranch )
{
	if( (m_nTongID == 0) || (m_nSwKindID == -1000) )//��ȸ�ΰ� �ƴϰų�, ��ȸ�ζ�� ��������϶��� Ȯ��(��ȸ�� ���ڵ��� ������ ������ġ�ϱ� ������̿����� Ȯ���ϸ� ��)
	{
		//������� �ߺ��Ǵ� ��尡 �ִ��� Ȯ���Ѵ�.
		CNodeView*														pSamePosNode	= NULL;
		pSamePosNode													= pRootNode->FindSamePosition( this );

		if( pSamePosNode )								
			return TRUE;

	}

	if(m_pCenter != NULL)
	{
		if( m_pCenter->IsOverlapNode(pRootNode, pRootBranch) )
			return TRUE;
	}
	if(m_pRight != NULL)
	{
		if( m_pRight->IsOverlapNode(pRootNode, pRootBranch) )
			return TRUE;
	}
	if(m_pLeft != NULL)
	{
		if( m_pLeft->IsOverlapNode(pRootNode, pRootBranch) )
			return TRUE;
	}
	if(m_pLeftTop != NULL)
	{
		if( !((m_pLeftTop->m_pCenter) && (m_pLeftTop->m_pCenter->m_nSwKindID == NDTYPE_BACKUP)) )
		{
			if( m_pLeftTop->IsOverlapNode(pRootNode, pRootBranch) )
				return TRUE;
		}
	}
	if(m_pRightBottom != NULL)
	{
		if( !((m_pRightBottom->m_pCenter) && (m_pRightBottom->m_pCenter->m_nSwKindID == NDTYPE_BACKUP)) )
		{
			if( m_pRightBottom->IsOverlapNode(pRootNode, pRootBranch) )
				return TRUE;
		}
	}

	return FALSE;
}

CNodeView* CNodeView::FindSamePosition( CNodeView* pTargetNode )
{
	CNodeView*															pFindNode;
	if(m_pCenter != NULL)
	{
		pFindNode														= m_pCenter->FindSamePositionRcv(pTargetNode, this);
		if( pFindNode )													return pFindNode;
	}
	if(m_pRight!= NULL)
	{
		pFindNode														= m_pRight->FindSamePositionRcv(pTargetNode, this);
		if( pFindNode )													return pFindNode;
	}
	if(m_pLeft != NULL)
	{
		pFindNode														= m_pLeft->FindSamePositionRcv(pTargetNode, this);
		if( pFindNode )													return pFindNode;
	}
	if(m_pLeftTop != NULL)
	{
// 		if( !((m_pLeftTop->m_pCenter) && (m_pLeftTop->m_pCenter->m_nSwKindID == NDTYPE_BACKUP)) )
		{
			pFindNode													= m_pLeftTop->FindSamePositionRcv(pTargetNode, this);
			if( pFindNode )												return pFindNode;
		}
	}
	if(m_pRightBottom != NULL)
	{
// 		if( !((m_pRightBottom->m_pCenter) && (m_pRightBottom->m_pCenter->m_nSwKindID == NDTYPE_BACKUP)) )
		{
			pFindNode													= m_pRightBottom->FindSamePositionRcv(pTargetNode, this);
			if( pFindNode )												return pFindNode;
		}
	}

	return NULL;
}

CNodeView* CNodeView::FindSamePositionRcv( CNodeView* pTargetNode, CNodeView* prevnodeview )
{
	if( pTargetNode != this )//������ ��尡 �ƴҶ�, ��ǥ�� ��ĥ��(Branch����),
	{
		int																nMinX = 0;
		int																nMinY = 0;
		int																nMaxX = 0;
		int																nMaxY = 0;

		if( m_nDirection == 0 )//���������� �������
		{
			if( prevnodeview->m_nPosY != m_nPosY )//�밢���̴�
			{
				nMinX													= m_nPosX;
				nMaxX													= m_nPosX;
				nMinY													= m_nPosY;
				nMaxY													= m_nPosY;
			}
			else
			{
				nMinX													= prevnodeview->m_nPosX+(GRID_GAP/2.);
				nMaxX													= m_nPosX;
				nMinY													= m_nPosY;
				nMaxY													= m_nPosY;
			}
		}
		else if( m_nDirection == 1 )//�Ʒ������� �������
		{
			if( prevnodeview->m_nPosX != m_nPosX )//�밢���̴�
			{
				nMinX													= m_nPosX;
				nMaxX													= m_nPosX;
				nMinY													= m_nPosY;
				nMaxY													= m_nPosY;
			}
			else
			{
				nMinX													= m_nPosX;
				nMaxX													= m_nPosX;
				nMinY													= prevnodeview->m_nPosY+(GRID_GAP/2.);
				nMaxY													= m_nPosY;
			}
		}
		else if( m_nDirection == 2 )//�������� �������
		{
			if( prevnodeview->m_nPosY != m_nPosY )//�밢���̴�
			{
				nMinX													= m_nPosX;
				nMaxX													= m_nPosX;
				nMinY													= m_nPosY;
				nMaxY													= m_nPosY;
			}
			else
			{
				nMinX													= m_nPosX;
				nMaxX													= prevnodeview->m_nPosX-(GRID_GAP/2.);
				nMinY													= m_nPosY;
				nMaxY													= m_nPosY;
			}
		}
		else//�������� �������
		{
			if( prevnodeview->m_nPosX != m_nPosX )//�밢���̴�
			{
				nMinX													= m_nPosX;
				nMaxX													= m_nPosX;
				nMinY													= m_nPosY;
				nMaxY													= m_nPosY;
			}
			else
			{
				nMinX													= m_nPosX;
				nMaxX													= m_nPosX;
				nMinY													= m_nPosY;
				nMaxY													= prevnodeview->m_nPosY-(GRID_GAP/2.);
			}
		}

		if( ((nMinX <= pTargetNode->m_nPosX) && (pTargetNode->m_nPosX <= nMaxX)) && ((nMinY <= pTargetNode->m_nPosY) && (pTargetNode->m_nPosY <= nMaxY)) )
		{
			if( (m_nTongID == 0 ) || (m_nTongID && (m_nTongID != pTargetNode->m_nTongID)) )//��ȸ�ΰ� �ƴϰų�, ��ȸ���̰� ���ϴ�ȸ�γ� ���ڰ� �ƴϸ�(��, Ÿ�����̸�) ã�Ҵ�!
				return this;
		}
	}

	CNodeView*															pFindNode;
	if(m_pCenter != NULL)
	{
		pFindNode														= m_pCenter->FindSamePositionRcv(pTargetNode, this);
		if( pFindNode )													return pFindNode;
	}
	if(m_pRight!= NULL)
	{
		pFindNode														= m_pRight->FindSamePositionRcv(pTargetNode, this);
		if( pFindNode )													return pFindNode;
	}
	if(m_pLeft != NULL)
	{
		pFindNode														= m_pLeft->FindSamePositionRcv(pTargetNode, this);
		if( pFindNode )													return pFindNode;
	}
	if(m_pLeftTop != NULL)
	{
// 		if( !((m_pLeftTop->m_pCenter) && (m_pLeftTop->m_pCenter->m_nSwKindID == NDTYPE_BACKUP)) )
		{
			pFindNode													= m_pLeftTop->FindSamePositionRcv(pTargetNode, this);
			if( pFindNode )												return pFindNode;
		}
	}
	if(m_pRightBottom != NULL)
	{
// 		if( !((m_pRightBottom->m_pCenter) && (m_pRightBottom->m_pCenter->m_nSwKindID == NDTYPE_BACKUP)) )
		{
			pFindNode													= m_pRightBottom->FindSamePositionRcv(pTargetNode, this);
			if( pFindNode )												return pFindNode;
		}
	}

	return NULL;
}

void CNodeView::SetPosition()
{
	int																	targetXY(16), nBFSize(65), nGap(0);

	if ( m_pCenter != NULL )
	{
		if( m_pCenter->m_nSwKindID == -1000  )// ��Ƽ Sw �������     
		{
			// ���б���ڴ� ���ݸ� ����.
// 			if( m_nSwKindID == NDTYPE_TR )								targetXY /= 2;
			// ���б����� �޶�����. �׳� ��ȸ�ζ� �Ȱ��� ����

			if( m_nDirection == 0 )// �� -> ��
			{
				m_nPosX -= targetXY;
				if( m_pCenter->m_pRight != NULL )
					m_pCenter->m_pRight->m_nPosY						+= targetXY;
				if( m_pCenter->m_pLeft != NULL )	
					m_pCenter->m_pLeft->m_nPosY							-= targetXY;
				if( m_pCenter->m_pLeftTop != NULL )
				{
					nGap												= (targetXY/2);
					m_pCenter->m_pLeftTop->m_nPosX						+= (targetXY + nGap);
					m_pCenter->m_pLeftTop->m_nPosY						-= targetXY;

					if( (m_pCenter->m_pLeftTop->m_pCenter) && (m_pCenter->m_pLeftTop->m_pCenter->m_nSwKindID == NDTYPE_BACKUP) )
					{
						m_pCenter->m_pLeftTop->m_pCenter->m_nPosX		+= (targetXY + nGap);
						m_pCenter->m_pLeftTop->m_pCenter->m_nPosY		+= (targetXY + nGap);
					}
				}
				if( m_pCenter->m_pRightBottom != NULL )
				{
					nGap												= (targetXY/2);
					m_pCenter->m_pRightBottom->m_nPosX					+= (targetXY + nGap);
					m_pCenter->m_pRightBottom->m_nPosY					+= targetXY;

					if( (m_pCenter->m_pRightBottom->m_pCenter) && (m_pCenter->m_pRightBottom->m_pCenter->m_nSwKindID == NDTYPE_BACKUP) )
					{
						m_pCenter->m_pRightBottom->m_pCenter->m_nPosX	+= (targetXY + nGap);
						m_pCenter->m_pRightBottom->m_pCenter->m_nPosY	-= (targetXY + nGap);
					}

				}
				if( m_pCenter->m_pCenter != NULL )
					m_pCenter->m_pCenter->m_nPosX						+= (targetXY + (nGap*3));
			}
			else if( m_nDirection == 1 )// �� -> ��
			{
				m_nPosY													-= targetXY;
				if( m_pCenter->m_pRight != NULL )
					m_pCenter->m_pRight->m_nPosX						-= targetXY;
				if( m_pCenter->m_pLeft != NULL )
					m_pCenter->m_pLeft->m_nPosX							+= targetXY;
				if( m_pCenter->m_pLeftTop != NULL )
				{
					nGap												= (targetXY/2);
					m_pCenter->m_pLeftTop->m_nPosX						+= targetXY;
					m_pCenter->m_pLeftTop->m_nPosY						+= (targetXY + nGap);

					if( (m_pCenter->m_pLeftTop->m_pCenter) && (m_pCenter->m_pLeftTop->m_pCenter->m_nSwKindID == NDTYPE_BACKUP) )
					{
						m_pCenter->m_pLeftTop->m_pCenter->m_nPosX		-= (targetXY + nGap);
						m_pCenter->m_pLeftTop->m_pCenter->m_nPosY		+= (targetXY + nGap);
					}
				}
				if( m_pCenter->m_pRightBottom != NULL )
				{
					nGap												= (targetXY/2);
					m_pCenter->m_pRightBottom->m_nPosX					-= targetXY;
					m_pCenter->m_pRightBottom->m_nPosY					+= (targetXY + nGap);

					if( (m_pCenter->m_pRightBottom->m_pCenter) && (m_pCenter->m_pRightBottom->m_pCenter->m_nSwKindID == NDTYPE_BACKUP) )
					{
						m_pCenter->m_pRightBottom->m_pCenter->m_nPosX	+= (targetXY + nGap);
						m_pCenter->m_pRightBottom->m_pCenter->m_nPosY	+= (targetXY + nGap);
					}
				}
				if( m_pCenter->m_pCenter != NULL )
					m_pCenter->m_pCenter->m_nPosY						+= (targetXY + (nGap*3)); 
			}
			else if( m_nDirection == 2 )// �� -> ��
			{
				m_nPosX													+= targetXY;
				if( m_pCenter->m_pRight != NULL )
					m_pCenter->m_pRight->m_nPosY						-= targetXY;
				if( m_pCenter->m_pLeft != NULL )
					m_pCenter->m_pLeft->m_nPosY							+= targetXY;
				if( m_pCenter->m_pLeftTop != NULL )
				{
					nGap												= (targetXY/2);
					m_pCenter->m_pLeftTop->m_nPosX						-= (targetXY + nGap);
					m_pCenter->m_pLeftTop->m_nPosY						+= targetXY;

					if( (m_pCenter->m_pLeftTop->m_pCenter) && (m_pCenter->m_pLeftTop->m_pCenter->m_nSwKindID == NDTYPE_BACKUP) )
					{
						m_pCenter->m_pLeftTop->m_pCenter->m_nPosX		-= (targetXY + nGap);
						m_pCenter->m_pLeftTop->m_pCenter->m_nPosY		-= (targetXY + nGap);
					}
				}
				if( m_pCenter->m_pRightBottom != NULL )
				{
					nGap												= (targetXY/2);
					m_pCenter->m_pRightBottom->m_nPosX					-= (targetXY + nGap);
					m_pCenter->m_pRightBottom->m_nPosY					-= targetXY;

					if( (m_pCenter->m_pRightBottom->m_pCenter) && (m_pCenter->m_pRightBottom->m_pCenter->m_nSwKindID == NDTYPE_BACKUP) )
					{
						m_pCenter->m_pRightBottom->m_pCenter->m_nPosX	-= (targetXY + nGap);
						m_pCenter->m_pRightBottom->m_pCenter->m_nPosY	+= (targetXY + nGap);
					}
				}
				if( m_pCenter->m_pCenter != NULL )
					m_pCenter->m_pCenter->m_nPosX						-= (targetXY + (nGap*3));
			}
			else// �� -> ��
			{
				m_nPosY													+= targetXY;
				if( m_pCenter->m_pRight != NULL )
					m_pCenter->m_pRight->m_nPosX						+= targetXY;
				if( m_pCenter->m_pLeft != NULL )
					m_pCenter->m_pLeft->m_nPosX							-= targetXY;
				if( m_pCenter->m_pLeftTop != NULL )
				{
					nGap												= (targetXY/2);
					m_pCenter->m_pLeftTop->m_nPosX						-= targetXY;
					m_pCenter->m_pLeftTop->m_nPosY						-= (targetXY + nGap);

					if( (m_pCenter->m_pLeftTop->m_pCenter) && (m_pCenter->m_pLeftTop->m_pCenter->m_nSwKindID == NDTYPE_BACKUP) )
					{
						m_pCenter->m_pLeftTop->m_pCenter->m_nPosX		+= (targetXY + nGap);
						m_pCenter->m_pLeftTop->m_pCenter->m_nPosY		-= (targetXY + nGap);
					}
				}
				if( m_pCenter->m_pRightBottom != NULL )
				{
					nGap												= (targetXY/2);
					m_pCenter->m_pRightBottom->m_nPosX					+= targetXY;
					m_pCenter->m_pRightBottom->m_nPosY					-= (targetXY + nGap);

					if( (m_pCenter->m_pRightBottom->m_pCenter) && (m_pCenter->m_pRightBottom->m_pCenter->m_nSwKindID == NDTYPE_BACKUP) )
					{
						m_pCenter->m_pRightBottom->m_pCenter->m_nPosX	-= (targetXY + nGap);
						m_pCenter->m_pRightBottom->m_pCenter->m_nPosY	-= (targetXY + nGap);
					}
				}
				if( m_pCenter->m_pCenter != NULL )
					m_pCenter->m_pCenter->m_nPosY						-= (targetXY + (nGap*3));
			}
		}
	}

	if( m_nSwKindID != -1000 && m_nPosX != -1000 && m_nPosY != -1000 )
	{
		int																nKind;
		if ( m_nSwKindID == NDTYPE_BACKUP )
		{
			if ( m_nDirection == 0 )
			{
				nKind													= 601;
				m_nPosX													-= nBFSize;
			}
			else if ( m_nDirection == 1 )
			{
				nKind													= 602;
				m_nPosY													-= nBFSize;
			}
			else if ( m_nDirection == 2 )
			{
				nKind													= 603;
				m_nPosX													+= nBFSize;
			}
			else
			{
				nKind													= 604;
				m_nPosY													+= nBFSize;
			}
		}
		else
		{
			nKind														= m_nSwKindID;
		}
	}

	if( m_pCenter != NULL )												m_pCenter->SetPosition();
	if( m_pRight != NULL)												m_pRight->SetPosition();
	if( m_pLeft != NULL)												m_pLeft->SetPosition();
	if( m_pLeftTop != NULL)												m_pLeftTop->SetPosition();
	if( m_pRightBottom != NULL)											m_pRightBottom->SetPosition();
}

CNodeView* CNodeView::GetSelectNodeView( CPoint ptPosition )
{
	if( m_rectObj.PtInRect( ptPosition ) )								return this;

	CNodeView*															pFindNode;
	if(m_pCenter != NULL)
	{
		pFindNode														= m_pCenter->GetSelectNodeView(ptPosition);
		if( pFindNode )													return pFindNode;
	}
	if(m_pRight!= NULL)
	{
		pFindNode														= m_pRight->GetSelectNodeView(ptPosition);
		if( pFindNode )													return pFindNode;
	}
	if(m_pLeft != NULL)
	{
		pFindNode														= m_pLeft->GetSelectNodeView(ptPosition);
		if( pFindNode )													return pFindNode;
	}
	if(m_pLeftTop != NULL)
	{
		pFindNode														= m_pLeftTop->GetSelectNodeView(ptPosition);
		if( pFindNode )													return pFindNode;
	}
	if(m_pRightBottom != NULL)
	{
		pFindNode														= m_pRightBottom->GetSelectNodeView(ptPosition);
		if( pFindNode )													return pFindNode;
	}

	return NULL;
}

CNodeView* CNodeView::GetSelectNodeView( int nNDIdx, int nNotDbID )
{
	if( (nNotDbID != m_nDbID) && (m_nSwKindID != NDTYPE_BACKUP) )
	{
		if( nNDIdx == m_nNDID[0] || nNDIdx == m_nNDID[1] )
			return this;
	}

	CNodeView*															pFindNode;
	if(m_pCenter != NULL)
	{
		pFindNode														= m_pCenter->GetSelectNodeView(nNDIdx, nNotDbID);
		if( pFindNode )													return pFindNode;
	}
	if(m_pRight!= NULL)
	{
		pFindNode														= m_pRight->GetSelectNodeView(nNDIdx, nNotDbID);
		if( pFindNode )													return pFindNode;
	}
	if(m_pLeft != NULL)
	{
		pFindNode														= m_pLeft->GetSelectNodeView(nNDIdx, nNotDbID);
		if( pFindNode )													return pFindNode;
	}
	if(m_pLeftTop != NULL)
	{
		pFindNode														= m_pLeftTop->GetSelectNodeView(nNDIdx, nNotDbID);
		if( pFindNode )													return pFindNode;
	}
	if(m_pRightBottom != NULL)
	{
		pFindNode														= m_pRightBottom->GetSelectNodeView(nNDIdx, nNotDbID);
		if( pFindNode )													return pFindNode;
	}

	return NULL;
}

BOOL CNodeView::IsCBreaker()
{
	if( m_nSwKindID == NDTYPE_SWITCH && m_nKCIMType == KCIMTYPE_CB)		return TRUE;
	else																return FALSE;
}

BOOL CNodeView::IsProtectSw()
{
	if (m_nKCIMType == KCIMTYPE_CB)//CB
		return TRUE;
	else if (m_nKCIMType == KCIMTYPE_RC)//RC
		return TRUE;
	else if (m_nTongID > 0 && m_nKCIMType == KCIMTYPE_EFI)//MCA(PCA)
		return TRUE;
	else if (m_nKCIMType == KCIMTYPE_EFI)//EFI
		return TRUE;
	else
		return FALSE;
}

BOOL CNodeView::IsSwitch()
{
	if( m_nSwKindID == NDTYPE_SWITCH || m_nSwKindID == NDTYPE_MULTI )
		return TRUE;
	else
		return FALSE;
}										

CString CNodeView::GetSimbolText()
{
	CString																szSimbolText(_T(""));
	if( m_nTongID )
	{
		if( m_nSwKindID == -1000 )										return _T("");
		if( m_nSwKindID == NDTYPE_TR )
		{
			if( m_nCaption == 1 )										szSimbolText	= _T("S");
			else														szSimbolText	= _T("L");
		}
		else
		{
			szSimbolText.Format( _T("%d"), m_nCaption );
		}
	}
	else
	{
		szSimbolText													= GetStrKind();
	}

	return																szSimbolText;
}

CString CNodeView::GetGISSimbolText()
{
	CString																szSimbolText(_T(""));
	if (m_nTongID)
	{
		if (m_nSwKindID != -1000)
			return szSimbolText;

		if (m_pCenter == NULL)											
			return szSimbolText;

		if (m_pCenter->m_nSwKindID == NDTYPE_TR)						szSimbolText = _T("TR");
		else if (m_pCenter->m_nSwKindID == NDTYPE_ALTS)					szSimbolText = _T("AL");
		else															szSimbolText = _T("PD");
	}
	else
	{
		szSimbolText = GetStrKind();
	}

	return																szSimbolText;
}

CRect CNodeView::GetSimbolRect( double dScale /*= 1.0*/ )
{
	//Draw������ ����з��� �� �����!!!!!!!!!!!!!!!!!!!!
	CRect																rect;
	int																	nObjSize;
	CPoint																ptPosition;
	ptPosition															= CPoint( m_nPosX*dScale, m_nPosY*dScale );

	if( m_nSwKindID == -1000 )
	{
		rect.SetRect( ptPosition, ptPosition );
		return rect;
	}

	if( m_nSwKindID == NDTYPE_BACKUP )
	{
		nObjSize									= int(10 * dScale);
		if( m_nDirection % 2 == 0 )//����
			rect.SetRect( ptPosition.x-(nObjSize*1.2), ptPosition.y-nObjSize, ptPosition.x+(nObjSize*1.2), ptPosition.y+nObjSize );
		else
			rect.SetRect( ptPosition.x-nObjSize, ptPosition.y-(nObjSize*1.2), ptPosition.x+nObjSize, ptPosition.y+(nObjSize*1.2) );

		return rect;
	}

	if( m_nSwKindID == NDTYPE_GEN )										nObjSize = int(20 * dScale);
	else if( m_nSwKindID == NDTYPE_SVR )								nObjSize = int(16 * dScale);
	else if( m_nSwKindID == NDTYPE_ESS )								nObjSize = int(16 * dScale);
	else if( m_nSwKindID == NDTYPE_SHUNTEQ )							nObjSize = int(16 * dScale);
	else if( m_nSwKindID == NDTYPE_SVC )								nObjSize = int(16 * dScale);
	else if( m_nSwKindID == NDTYPE_DUMMY )								nObjSize = int(4 * dScale);
	else if (m_nSwKindID == NDTYPE_CUSTOMER)							nObjSize = int(20 * dScale);
	else
	{
		if( m_nKCIMType == KCIMTYPE_CB)									nObjSize = int(24 * dScale);
		else if (m_nKCIMType == KCIMTYPE_RC)
		{
			if (m_nCeqType == 67)										nObjSize = int(16 * dScale);//����
			else														nObjSize = int(20 * dScale);//����
		}
		else if( m_nKCIMType == KCIMTYPE_MANUAL)
		{
			if( m_nTongID )												nObjSize = int(8 * dScale);
			else														nObjSize = int(14 * dScale);
		}
		else if( m_nKCIMType == KCIMTYPE_COS)							nObjSize = int(12 * dScale);
		else if (m_nKCIMType == KCIMTYPE_EFI)
		{
			if (m_nCeqType == 68)										nObjSize = int(16 * dScale);//�ڵ�
			else														nObjSize = int(15 * dScale);//����
		}
		else
		{
			if( m_nTongID )												nObjSize = int(11 * dScale);
			else														nObjSize = int(16 * dScale);
		}
	}


	rect.SetRect( ptPosition, ptPosition );

	if( m_nSwKindID == NDTYPE_CUSTOMER )								rect.InflateRect( nObjSize-5, nObjSize );
	else																rect.InflateRect(nObjSize, nObjSize);

	return rect;
}

void CNodeView::DBSave( int nOffice, CString sztime, CString szSubstID, int nCBID, int nSLDMode )
{
// 	if( m_nDbID != 0 )					
// 	{
// 		CDBMng*								pDBMng = CDBMng::Instance();
// 		CString								szQuery;
// 		CRect								rect;
// 		rect								= GetSimbolRect();
// 
// 		szQuery.Format( _T("INSERT INTO IBNE6140 \
// 						   ( JURIS_OFFICE_CD,	CRE_YMD,	SUBST_IDTF,			DIST_LINE_ID,	AUTO_MODE,	SW_IDTF,	SW_LOC,			SW_MESH_NO,		SW_KND_IDTF,	STAT_CD,\
// 							 SW_DIRE,			DONG_CD,	SWTC_NO,			TOP,			LFT,		RGHT,		BOTTOM,			X_POS,			Y_POS,			SYMBOL_CD ) VALUES \
// 						   ( '%d',				'%s',		'%s',				%d,				%d,			%d,			'%s',			'%s',			%d,				%d,\
// 							 %d,				%d,			'%s',				%d,				%d,			%d,			%d,				%d,				%d,				%s )"), 
// 							nOffice,			sztime,		szSubstID,			nCBID,			nSLDMode,	m_nDbID,	m_szLoc,		m_szLocNo,		m_nSwKindID,	m_bStatus?1:0,
// 							m_nDirection,		m_nTongID,	GetSimbolText(),	rect.top,		rect.left,	rect.right,	rect.bottom,	m_nPosX,		m_nPosY,		GetSimbolCode() );
// 		pDBMng->DBExcuteDW( szQuery );
// 	}
// 
// 	if( m_pCenter )						m_pCenter->DBSave(nOffice, sztime, szSubstID, nCBID, nSLDMode);
// 	if( m_pLeft )						m_pLeft->DBSave(nOffice, sztime, szSubstID, nCBID, nSLDMode);
// 	if( m_pRight )						m_pRight->DBSave(nOffice, sztime, szSubstID, nCBID, nSLDMode);
// 	if( m_pLeftTop )					m_pLeftTop->DBSave(nOffice, sztime, szSubstID, nCBID, nSLDMode);
// 	if( m_pRightBottom )				m_pRightBottom->DBSave(nOffice, sztime, szSubstID, nCBID, nSLDMode);
}

CNodeView* CNodeView::GetNodeView( int nID )
{
	if( m_nDbID == nID )												return this;

	CNodeView* pFindNode;
	if( m_pCenter )
	{
		pFindNode														= m_pCenter->GetNodeView( nID );
		if( pFindNode )													return pFindNode;
	}
	if( m_pRight )
	{
		pFindNode														= m_pRight->GetNodeView( nID );
		if( pFindNode )													return pFindNode;
	}
	if( m_pLeft )
	{
		pFindNode														= m_pLeft->GetNodeView( nID );
		if( pFindNode )													return pFindNode;
	}
	if( m_pLeftTop )
	{
		pFindNode														= m_pLeftTop->GetNodeView( nID );
		if( pFindNode )													return pFindNode;
	}
	if( m_pRightBottom )
	{
		pFindNode														= m_pRightBottom->GetNodeView( nID );
		if( pFindNode )													return pFindNode;
	}

	return NULL;
}

void CNodeView::SetSelectDraw( CDC* BufferDC )
{
	CRect																		rSelect;
	CPen																		pen, *pOldpen;
	pen.CreatePen(PS_DOT, 1, SELECT_DRAW_COLOR);
	pOldpen = BufferDC->SelectObject(&pen);
	BufferDC->SelectStockObject(NULL_BRUSH);

	rSelect = m_rectObj;
	rSelect.InflateRect(4, 4);
	BufferDC->Rectangle(rSelect);

	BufferDC->SelectStockObject(WHITE_BRUSH);
	BufferDC->SelectObject(pOldpen);
	pen.DeleteObject();
}

void CNodeView::DrawFIFlag( CDC* BufferDC, double dScale )
{
	int																	nfiinfoIdx(0), nCbswIdx(0);
	
	if (m_nSwKindID < NDTYPE_BACKUP && m_nSwKindID != -1000)
	{
		nCbswIdx = GetCbswIdx();
		nfiinfoIdx = GetFiInfoIdx(nCbswIdx);
	}

	if( nfiinfoIdx )
	{
		CPen															pen,*pOldpen;
		CBrush															brush, *pOldbrush;
		COLORREF														_InColor( RGB( 0, 0, 0 ) ), _OutColor( RGB( 0, 0, 0 ) ), _NormalColor( RGB( 128, 128, 128 ) );
		wstring															szFiName( _T("") );
		TCHAR															szFaCurrent[ 64 ] = { 0, };
		CRect															FiIndiView( 0, 0, 0, 0 ), HeaderText( FiIndiView );
		POINT															Fi_Pt[3] = { 0, };

		if( GETVALUE( int, _T("fiinfo_dyn_fio"), _T("fiinfo_fitype"), nfiinfoIdx ) == 1 )//����FI
		{
			_InColor													= RGB( 0, 0, 255 );
			_OutColor													= RGB( 255, 255, 255 );
			szFiName													= _T("����");
		}
		else//�Ͻ�FI
		{
			_InColor													= RGB( 255, 0, 0 );
			_OutColor													= RGB( 255, 255, 0 );
			szFiName													= _T("�Ͻ�");
		}

		int																nDirection;
		if (m_nTongID)
		{
			if (m_pCenter && m_pCenter->m_nSwKindID == -1000)//��ȸ�� ������
			{
				nDirection = (m_nDirection+2)%4;
			}
			else
			{
				nDirection = m_nDirection;
			}
		}
		else
		{
			nDirection = 0;
		}

		
		if (nDirection == 1)
		{
			FiIndiView.top												= (m_nPosY + 15)*dScale;
			FiIndiView.bottom											= FiIndiView.top + 75;
			FiIndiView.left												= (m_nPosX + 15)*dScale;
			FiIndiView.right											= FiIndiView.left + 65;

			Fi_Pt[0].x													= FiIndiView.left;
			Fi_Pt[0].y													= FiIndiView.top + 12;
			Fi_Pt[1].x													= FiIndiView.left - 5;
			Fi_Pt[1].y													= FiIndiView.top - 5;
			Fi_Pt[2].x													= FiIndiView.left + 12;
			Fi_Pt[2].y													= FiIndiView.top + 2;
		}
		else if( nDirection == 2 )
		{
			FiIndiView.top												= (m_nPosY + 15)*dScale;
			FiIndiView.bottom											= FiIndiView.top + 75;
			FiIndiView.right											= (m_nPosX - 15)*dScale;
			FiIndiView.left												= FiIndiView.right - 65;

			Fi_Pt[0].x													= FiIndiView.right;
			Fi_Pt[0].y													= FiIndiView.top + 12;
			Fi_Pt[1].x													= FiIndiView.right + 5;
			Fi_Pt[1].y													= FiIndiView.top - 5;
			Fi_Pt[2].x													= FiIndiView.right - 12;
			Fi_Pt[2].y													= FiIndiView.top + 2;
		}
		else if( nDirection == 3 )
		{
			FiIndiView.bottom											= (m_nPosY - 15)*dScale;
			FiIndiView.top												= FiIndiView.bottom - 75;
			FiIndiView.right											= (m_nPosX - 15)*dScale;
			FiIndiView.left												= FiIndiView.right - 65;

			Fi_Pt[0].x													= FiIndiView.right;
			Fi_Pt[0].y													= FiIndiView.bottom - 12;
			Fi_Pt[1].x													= FiIndiView.right + 5;
			Fi_Pt[1].y													= FiIndiView.bottom + 5;
			Fi_Pt[2].x													= FiIndiView.right - 12;
			Fi_Pt[2].y													= FiIndiView.bottom - 2;
		}
		else
		{
			FiIndiView.bottom											= (m_nPosY - 15)*dScale;
			FiIndiView.top												= FiIndiView.bottom - 75;
			FiIndiView.left												= (m_nPosX + 15)*dScale;
			FiIndiView.right											= FiIndiView.left + 65;

			Fi_Pt[0].x													= FiIndiView.left;
			Fi_Pt[0].y													= FiIndiView.bottom - 12;
			Fi_Pt[1].x													= FiIndiView.left - 5;
			Fi_Pt[1].y													= FiIndiView.bottom + 5;
			Fi_Pt[2].x													= FiIndiView.left + 12;
			Fi_Pt[2].y													= FiIndiView.bottom - 2;
		}

		HeaderText.left													= FiIndiView.left+1;
		HeaderText.right												= FiIndiView.right-2;
		HeaderText.top													= FiIndiView.top+1;
		HeaderText.bottom												= HeaderText.top+15;


		//����
		pen.CreatePen( PS_SOLID, 1, _InColor );							
		pOldpen															= BufferDC->SelectObject(&pen);
		brush.CreateSolidBrush( _InColor );								
		pOldbrush														= BufferDC->SelectObject( &brush );
		BufferDC->Polygon( Fi_Pt, 3 );
		BufferDC->SelectObject( pOldpen );
		BufferDC->SelectObject( pOldbrush );
		pen.DeleteObject();		
		brush.DeleteObject();

		//���
		pen.CreatePen( PS_SOLID, 2, _InColor );	
		pOldpen															= BufferDC->SelectObject(&pen);
		brush.CreateSolidBrush( _OutColor );	
		pOldbrush														= BufferDC->SelectObject( &brush );
		BufferDC->RoundRect( FiIndiView, CPoint( 8, 8 ) );
		BufferDC->SelectObject( pOldpen );
		BufferDC->SelectObject( pOldbrush );
		pen.DeleteObject();		
		brush.DeleteObject();

		//Header
		pen.CreatePen( PS_SOLID, 1, _OutColor );
		pOldpen															= BufferDC->SelectObject(&pen);
		brush.CreateSolidBrush( _InColor );		
		pOldbrush														= BufferDC->SelectObject( &brush );
		BufferDC->RoundRect( HeaderText, CPoint( 5, 5 ) );
		pen.DeleteObject();
		brush.DeleteObject();
		BufferDC->SelectObject( pOldpen );
		BufferDC->SelectObject( pOldbrush );

		HeaderText.left													+= 3;
		HeaderText.right												-= 2;
		BufferDC->SetTextColor( _OutColor );
		if( (m_bStatus == SW_OPEN) && IsProtOperSw(nCbswIdx) )
		{
			if( m_nKCIMType == 1 )										BufferDC->DrawText( _T("Trip"), HeaderText, DT_SINGLELINE | DT_RIGHT | DT_VCENTER );
			else														BufferDC->DrawText( _T("Lockout"), HeaderText, DT_SINGLELINE | DT_RIGHT | DT_VCENTER );
		}
		else
		{//Header String
			BufferDC->DrawText( szFiName.c_str(), HeaderText, DT_SINGLELINE | DT_RIGHT | DT_VCENTER );

			//Header String2
			szFiName																			= _T("");
			if( GETVALUE( int, _T("fiinfo_dyn_fio"), _T("fiinfo_iaopr"), nfiinfoIdx ) > 0 )		{ szFiName += _T("A,"); };
			if( GETVALUE( int, _T("fiinfo_dyn_fio"), _T("fiinfo_ibopr"), nfiinfoIdx ) > 0 )		{ szFiName += _T("B,"); };
			if( GETVALUE( int, _T("fiinfo_dyn_fio"), _T("fiinfo_icopr"), nfiinfoIdx ) > 0 )		{ szFiName += _T("C,"); };
			if( GETVALUE( int, _T("fiinfo_dyn_fio"), _T("fiinfo_inopr"), nfiinfoIdx ) > 0 )		{ szFiName += _T("N,"); };
			szFiName																			= szFiName.substr( 0, szFiName.length() - 1 );
			BufferDC->DrawText( szFiName.c_str(), HeaderText, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
		}
		//Value
		HeaderText.bottom																		+= 1;

		//A�� ��������
		swprintf_s( szFaCurrent, _T("%.0f[A]"), GETVALUE( double, _T("fiinfo_dyn_fio"), _T("fiinfo_ia"), nfiinfoIdx ) );
		if( GETVALUE( int, _T("fiinfo_dyn_fio"), _T("fiinfo_iaopr"), nfiinfoIdx ) > 0 )			BufferDC->SetTextColor( _InColor );
		else																					BufferDC->SetTextColor( _NormalColor );
		HeaderText.top																			= HeaderText.bottom + 2;
		HeaderText.bottom																		= HeaderText.top + 12;
		BufferDC->DrawText( _T("A:"), HeaderText, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
		BufferDC->DrawText( szFaCurrent, HeaderText, DT_SINGLELINE | DT_RIGHT | DT_VCENTER );

		//B�� ��������
		swprintf_s( szFaCurrent, _T("%.0f[A]"), GETVALUE( double, _T("fiinfo_dyn_fio"), _T("fiinfo_ib"), nfiinfoIdx ) );
		if( GETVALUE( int, _T("fiinfo_dyn_fio"), _T("fiinfo_ibopr"), nfiinfoIdx ) > 0 )			BufferDC->SetTextColor( _InColor );
		else																					BufferDC->SetTextColor( _NormalColor );
		HeaderText.top																			= HeaderText.bottom + 2;
		HeaderText.bottom																		= HeaderText.top + 12;
		BufferDC->DrawText( _T("B:"), HeaderText, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
		BufferDC->DrawText( szFaCurrent, HeaderText, DT_SINGLELINE | DT_RIGHT | DT_VCENTER );

		//C�� ��������
		swprintf_s( szFaCurrent, _T("%.0f[A]"), GETVALUE( double, _T("fiinfo_dyn_fio"), _T("fiinfo_ic"), nfiinfoIdx ) );
		if( GETVALUE( int, _T("fiinfo_dyn_fio"), _T("fiinfo_icopr"), nfiinfoIdx ) > 0 )			BufferDC->SetTextColor( _InColor );
		else																					BufferDC->SetTextColor( _NormalColor );
		HeaderText.top																			= HeaderText.bottom + 2;
		HeaderText.bottom																		= HeaderText.top + 12;
		BufferDC->DrawText( _T("C:"), HeaderText, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
		BufferDC->DrawText( szFaCurrent, HeaderText, DT_SINGLELINE | DT_RIGHT | DT_VCENTER );

		//N�� ��������
		swprintf_s( szFaCurrent, _T("%.0f[A]"), GETVALUE( double, _T("fiinfo_dyn_fio"), _T("fiinfo_in"), nfiinfoIdx ) );
		if( GETVALUE( int, _T("fiinfo_dyn_fio"), _T("fiinfo_inopr"), nfiinfoIdx ) > 0 )			BufferDC->SetTextColor( _InColor );
		else																					BufferDC->SetTextColor( _NormalColor );

		HeaderText.top																			= HeaderText.bottom + 2;
		HeaderText.bottom																		= HeaderText.top + 12;
		BufferDC->DrawText( _T("N:"), HeaderText, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
		BufferDC->DrawText( szFaCurrent, HeaderText, DT_SINGLELINE | DT_RIGHT | DT_VCENTER );
	}

	int																	nCbswDrawType; //1:DFD, 2:DSR
	nCbswDrawType														= GetFaultType(nCbswIdx);
	if( nCbswDrawType )
	{
		BufferDC->SelectStockObject( NULL_BRUSH );

		CPen															pen,*pOldpen;
		if( nCbswDrawType == 1 )										pen.CreatePen( PS_SOLID, 4, RGB(255, 0, 0) );//DFD �����(������)
		else if( nCbswDrawType == 2 )									pen.CreatePen( PS_SOLID, 4, RGB(255, 255, 255) );//DFD �����(������)
		else if( nCbswDrawType == 3 )									pen.CreatePen( PS_SOLID, 4, RGB(255, 255, 0) );//DSR �����(������)
		else															pen.CreatePen( PS_SOLID, 4, RGB(0, 0, 255) );//DSR �����(������ü)

		pOldpen															= BufferDC->SelectObject( &pen );
		BufferDC->Ellipse( CRect(m_rectObj.left-8, m_rectObj.top-8, m_rectObj.right+8, m_rectObj.bottom+8) );
		BufferDC->SelectObject( pOldpen );
		pen.DeleteObject();
	}

	if( m_pCenter != NULL )												m_pCenter->DrawFIFlag(BufferDC, dScale);
	if( m_pRight != NULL)												m_pRight->DrawFIFlag(BufferDC, dScale);
	if( m_pLeft != NULL)												m_pLeft->DrawFIFlag(BufferDC, dScale);
	if( m_pLeftTop != NULL)												m_pLeftTop->DrawFIFlag(BufferDC, dScale);
	if( m_pRightBottom != NULL)											m_pRightBottom->DrawFIFlag(BufferDC, dScale);
}

int CNodeView::GetCbswIdx()
{
	int																	nNDIdx(0), nCbswIdx(0);
	if (m_nTongID)//��ȸ���϶�
	{
		if (m_nSwKindID == -1000)										nNDIdx = m_nFromND;//��������϶��� �����������ND
		else if (m_pCenter && m_pCenter->m_nSwKindID == -1000)			nNDIdx = m_nNDID[0];//������������϶��� ������ND
		else															nNDIdx = m_nNDID[1];//������������϶��� ������ND
	}
	else
	{
		nNDIdx															= m_nNDID[0];
	}

	if( nNDIdx == 0 )													return 0;

	nCbswIdx															= GETVALUE( int, _T("nd_sta"), _T("nd_hi_fcbsw"), nNDIdx);
	if( nCbswIdx )														return nCbswIdx;

	nCbswIdx															= GETVALUE( int, _T("nd_sta"), _T("nd_hi_tcbsw"), nNDIdx);
	if( nCbswIdx )														return nCbswIdx;

	return 0;
}

BOOL CNodeView::IsAuto()
{
	if( m_nSwKindID != NDTYPE_SWITCH && m_nSwKindID != NDTYPE_MULTI )
		return FALSE;

	if( m_nKCIMType > 0 && m_nKCIMType < KCIMTYPE_MANUAL)				return TRUE;
	else																return FALSE;
}

BOOL CNodeView::IsProtOperSw( int nCbswIdx )
{
	if (nCbswIdx == 0)													return FALSE;

	int																	nfltinfo_ii_cbsw;
	int																	nCnt;
	nCnt = theAppDataMng->GetTableRealCount(_T("fltinfo_dyn_fio"));
	for (int i = 1; i <= nCnt; i++)
	{
		nfltinfo_ii_cbsw = GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_ii_cbsw"), i);
		if (nfltinfo_ii_cbsw == 0)										break;

		if (nfltinfo_ii_cbsw == nCbswIdx)
			return TRUE;
	}

	return FALSE;
}

int CNodeView::GetFiInfoIdx( int nCbswIdx )
{
	if( nCbswIdx == 0 )													return FALSE;

	int																	nfiinfo_ii_cbsw;
	int																	nCnt;
	nCnt																= theAppDataMng->GetTableRealCount(_T("fiinfo_dyn_fio"));
	for( int i = 1; i <= nCnt; i++)
	{
		nfiinfo_ii_cbsw													= GETVALUE( int, _T("fiinfo_dyn_fio"), _T("fiinfo_ii_cbsw"), i );
		if( nfiinfo_ii_cbsw == 0 )										break;

		if( nfiinfo_ii_cbsw == nCbswIdx )								return i;
	}

	return 0;
}

int CNodeView::GetFaultType( int nCbswIdx )
{
// 	if( nCbswIdx == 0 )													return 0;
// 
// 	int																	nisocbsw_ii_cbsw;
// 	for( int i = 1 ; i <= (int)GETCOUNT( _T("isocbsw_dyn_dfdo") ) ; i++ )
// 	{
// 		nisocbsw_ii_cbsw												= GETVALUE( int, _T("isocbsw_dyn_dfdo"), _T("isocbsw_ii_cbsw"), i );
// 		if( nisocbsw_ii_cbsw == 0 )										break;
// 
// 		if( nisocbsw_ii_cbsw == nCbswIdx )
// 			return GETVALUE( int, _T("isocbsw_dyn_dfdo"), _T("isocbsw_updn"), i );
// 	}
// 
// 	for( int i = 1 ; i <= (int)GETCOUNT( _T("fltinfo_dyn_fio") ) ; i++ )
// 	{
// 		nisocbsw_ii_cbsw												= GETVALUE( int, _T("fltinfo_dyn_fio"), _T("fltinfo_ii_cbsw"), i );
// 		if( nisocbsw_ii_cbsw == 0 )										break;
// 
// 		if( nCbswIdx == nisocbsw_ii_cbsw )
// 			return 1;
// 	}
// 
// 	for( int i = 1 ; i <= (int)GETCOUNT( _T("dsrseq_dyn_dsro") ) ; i++ )
// 	{
// 		nisocbsw_ii_cbsw												= GETVALUE( int, _T("dsrseq_dyn_dsro"), _T("dsrseq_ii_cbsw"), i );
// 		if( nisocbsw_ii_cbsw == 0 )										break;
// 
// 		
// 		if( nCbswIdx == nisocbsw_ii_cbsw )
// 		{
// 			int															nstatus;
// 			nstatus														= GETVALUE( int, _T("dsrseq_dyn_dsro"), _T("dsrseq_before_state"), i );
// 
// 			if( nstatus == 1 )											return 4;//������°� OPEN�̸� ��ü�����
// 			else														return 3;//������°� CLOSE�̸� ���Ұ����
// 		}
// 	}

	return 0;
}

void CNodeView::ClearBoundaryCheck()
{
	m_bBoundarySelect													= FALSE;

	if( m_pCenter != NULL )												m_pCenter->ClearBoundaryCheck();
	if( m_pRight != NULL)												m_pRight->ClearBoundaryCheck();
	if( m_pLeft != NULL)												m_pLeft->ClearBoundaryCheck();
	if( m_pLeftTop != NULL)												m_pLeftTop->ClearBoundaryCheck();
	if( m_pRightBottom != NULL)											m_pRightBottom->ClearBoundaryCheck();
}

void CNodeView::DrawGIS(CDC* BufferDC, int nSize, double dZoom, double pCenX, double pCenY, CPoint ptCen, int nStep, int nZoomLevel)
{
	if (m_pSLDDPoint.dx != 0 && m_pSLDDPoint.dy != 0 && m_pGISDPoint.dy != 0 && m_pGISDPoint.dy != 0)
	{
		if ((m_nTongID == 0 || (m_nTongID && m_nSwKindID == -1000)) && (m_nSwKindID != NDTYPE_BACKUP) )
		{
			BufferDC->SetTextColor(RGB(0, 0, 0));
			BufferDC->SetBkMode(TRANSPARENT);

			double dx, dy;
			int x, y;
			dx = m_pSLDDPoint.dx + ((m_pGISDPoint.dx - m_pSLDDPoint.dx) * ((20 - nStep) / 20.));
			dy = m_pSLDDPoint.dy + ((m_pGISDPoint.dy - m_pSLDDPoint.dy) * ((20 - nStep) / 20.));
			x = int((dx - pCenX) * dZoom + 0.5) + ptCen.x;
			y = int((pCenY - dy) * dZoom + 0.5) + ptCen.y;

			m_rectObj = GetGISSimbolRect(x, y, nZoomLevel);

			int nKindID;
			if (m_nSwKindID == -1000)
			{
				ASSERT(m_pCenter != NULL);
				nKindID = m_pCenter->m_nSwKindID;
			}
			else
			{
				nKindID = m_nSwKindID;
			}

			if (nKindID == NDTYPE_GEN)										DrawGISDG(BufferDC);//�л�����
			else if (nKindID == NDTYPE_SVR)									DrawGISSVR(BufferDC);//SVR
			else if (nKindID == NDTYPE_ESS)									DrawGISAutoSw(BufferDC);//�ڵ�����ġ�� �����ϰ� �׸���.
			else if (nKindID == NDTYPE_SHUNTEQ)								DrawGISAutoSw(BufferDC);//�ڵ�����ġ�� �����ϰ� �׸���.
			else if (nKindID == NDTYPE_SVC)									DrawGISAutoSw(BufferDC);//�ڵ�����ġ�� �����ϰ� �׸���.
			else if (nKindID == NDTYPE_DUMMY)								DrawGISDummy(BufferDC);//����
			else if (nKindID == NDTYPE_TR)									DrawGISTR(BufferDC);//TR
			else if (nKindID == NDTYPE_ALTS)								DrawGISALTS(BufferDC);//ALTS
			else if (nKindID == NDTYPE_MULTI)								DrawGISMulti(BufferDC);//��ȸ��
			else
			{//�Ϲݽ���ġ, Ÿ�̽���ġ, ��Ƽ����, ���б����...(��Ƽ���� - �Ϲݰ����� Draw�Լ� ������ m_nTongID������ ������.
				if (m_nKCIMType == KCIMTYPE_CB)								DrawGISCB(BufferDC); //CB
				else if (m_nKCIMType == KCIMTYPE_MANUAL)					DrawGISManualSw(BufferDC);//���������
				else if (m_nKCIMType == KCIMTYPE_COS)						DrawGISCOS(BufferDC);//COS
				else if (m_nKCIMType == KCIMTYPE_EFI)						DrawGISEFI(BufferDC);
				else														DrawGISAutoSw(BufferDC);//2:RC, 3:�ڵ�
			}

			if (nZoomLevel > SHOW_TEXT_SCALE_GIS)
			{
				CFont						font, *pOldfont;
				font.CreateFont((int)(10 + ((nZoomLevel - SHOW_TEXT_SCALE_GIS) * 2)), 0, 0, 0, 800, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����"));
				pOldfont = BufferDC->SelectObject(&font);
				BufferDC->DrawText(GetGISSimbolText(), m_rectObj, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				BufferDC->SelectObject(pOldfont);
				font.DeleteObject();

// 				if (nKindID != NDTYPE_DUMMY)
				{
					font.CreateFont((int)(8 + ((nZoomLevel - SHOW_TEXT_SCALE_GIS) * 2)), 0, 0, 0, 800, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("����"));
					pOldfont = BufferDC->SelectObject(&font);
					BufferDC->SetTextColor(RGB(0, 0, 0));

					CRect rect;
					rect.SetRect(m_rectObj.CenterPoint().x - TEXT_AREA_WIDTH, m_rectObj.bottom + 5, m_rectObj.CenterPoint().x + TEXT_AREA_WIDTH, m_rectObj.bottom + 25);
					BufferDC->DrawText(m_szLoc, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

					BufferDC->SelectObject(pOldfont);
					font.DeleteObject();
				}
			}
		}
	}

	if (m_pCenter)																		m_pCenter->DrawGIS(BufferDC, nSize, dZoom, pCenX, pCenY, ptCen, nStep, nZoomLevel);
	if (m_pLeft)																		m_pLeft->DrawGIS(BufferDC, nSize, dZoom, pCenX, pCenY, ptCen, nStep, nZoomLevel);
	if (m_pRight)																		m_pRight->DrawGIS(BufferDC, nSize, dZoom, pCenX, pCenY, ptCen, nStep, nZoomLevel);
	if (m_pLeftTop)																		m_pLeftTop->DrawGIS(BufferDC, nSize, dZoom, pCenX, pCenY, ptCen, nStep, nZoomLevel);
	if (m_pRightBottom)																	m_pRightBottom->DrawGIS(BufferDC, nSize, dZoom, pCenX, pCenY, ptCen, nStep, nZoomLevel);
}

void CNodeView::DrawGISCB(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	if (m_bStatus == SW_OPEN)										color = RGB(0, 250, 0);
	else															color = RGB(250, 0, 0);

	pen.CreatePen(PS_SOLID, 2, RGB(255,255,0));
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Ellipse(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISDG(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	color = RGB(255, 0, 255);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Ellipse(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISAutoSw(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	if (m_bStatus == SW_OPEN)										color = RGB(0, 250, 0);
	else															color = RGB(250, 0, 0);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Ellipse(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISManualSw(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	if (m_bStatus == SW_OPEN)										color = RGB(0, 250, 0);
	else															color = RGB(250, 0, 0);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Rectangle(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISOH(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	color = RGB(20, 20, 255);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Ellipse(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISSVR(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	color = RGB(250, 0, 0);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	CPoint							pt[8];
	pt[0] = CPoint(m_rectObj.left + m_rectObj.Width() / 4, m_rectObj.top);
	pt[1] = CPoint(m_rectObj.right - m_rectObj.Width() / 4, m_rectObj.top);
	pt[2] = CPoint(m_rectObj.right, m_rectObj.top + m_rectObj.Height() / 4);
	pt[3] = CPoint(m_rectObj.right, m_rectObj.bottom - m_rectObj.Height() / 4);
	pt[4] = CPoint(m_rectObj.right - m_rectObj.Width() / 4, m_rectObj.bottom);
	pt[5] = CPoint(m_rectObj.left + m_rectObj.Width() / 4, m_rectObj.bottom);
	pt[6] = CPoint(m_rectObj.left, m_rectObj.bottom - m_rectObj.Height() / 4);
	pt[7] = CPoint(m_rectObj.left, m_rectObj.top + m_rectObj.Height() / 4);
	BufferDC->Polygon(pt, 8);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISEFI(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	if (m_bStatus == SW_OPEN)										color = RGB(0, 250, 0);
	else															color = RGB(250, 0, 0);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Rectangle(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISCOS(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	if (m_bStatus == SW_OPEN)										color = RGB(0, 250, 0);
	else															color = RGB(250, 0, 0);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Rectangle(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISDummy(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	color = RGB(50, 50, 50);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Rectangle(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISCustomer(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	color = RGB(100, 100, 100);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Rectangle(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISTR(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	color = RGB(250, 0, 0);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Rectangle(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CNodeView::DrawGISALTS(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	color = RGB(250, 0, 0);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Rectangle(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();

}

void CNodeView::DrawGISMulti(CDC* BufferDC)
{
	CPen							pen, *pOldpen;
	CBrush							brush, *pOldbrush;
	COLORREF						color;

	color = RGB(250, 0, 0);

	pen.CreatePen(PS_SOLID, 1, color);
	pOldpen = BufferDC->SelectObject(&pen);
	brush.CreateSolidBrush(color);
	pOldbrush = BufferDC->SelectObject(&brush);

	BufferDC->Rectangle(m_rectObj);

	BufferDC->SelectObject(pOldpen);
	BufferDC->SelectObject(pOldbrush);
	pen.DeleteObject();
	brush.DeleteObject();

}

CRect CNodeView::GetGISSimbolRect(double dx, double dy, int nZoomLevel)
{
	int nSize;
	nSize = (nZoomLevel - 11);

	//Draw������ ����з��� �� �����!!!!!!!!!!!!!!!!!!!!
	CRect															rect;
	int																nObjSize;
	CPoint															ptPosition;
	ptPosition = CPoint(dx, dy);

	if (m_nSwKindID == NDTYPE_GEN)									nObjSize = (nSize * 3);//�л�����
	else if (m_nSwKindID == NDTYPE_SVR)								nObjSize = (nSize * 3);//SVR
	else if (m_nSwKindID == NDTYPE_ESS)								nObjSize = (nSize * 2);//�ڵ�����ġ�� �����ϰ� �׸���.
	else if (m_nSwKindID == NDTYPE_SHUNTEQ)							nObjSize = (nSize * 2);//�ڵ�����ġ�� �����ϰ� �׸���.
	else if (m_nSwKindID == NDTYPE_SVC)								nObjSize = (nSize * 2);//�ڵ�����ġ�� �����ϰ� �׸���.
	else if (m_nSwKindID == NDTYPE_DUMMY)							nObjSize = (nSize * 1);//����													
	else if (m_nSwKindID == NDTYPE_TR)								nObjSize = (nSize * 2);//TR
	else if (m_nSwKindID == NDTYPE_ALTS)							nObjSize = (nSize * 3);//ALTS
	else
	{//�Ϲݽ���ġ, Ÿ�̽���ġ, ��Ƽ����, ���б����...(��Ƽ���� - �Ϲݰ����� Draw�Լ� ������ m_nTongID������ ������.
		if (m_nKCIMType == KCIMTYPE_CB)								nObjSize = (nSize * 3); //CB
		else if (m_nKCIMType == KCIMTYPE_MANUAL)					nObjSize = (nSize * 2);//���������
		else if (m_nKCIMType == KCIMTYPE_COS)						nObjSize = (nSize * 2);//COS
		else if (m_nKCIMType == KCIMTYPE_EFI)						nObjSize = (nSize * 2);//EFI
		else														nObjSize = (nSize * 2);//2:RC, 3:�ڵ�
	}

	rect.SetRect(ptPosition, ptPosition);
	rect.InflateRect(nObjSize, nObjSize);

	return rect;
}

void CNodeView::SetGISBranchPos(CBranchView* pbranchview)
{
	//�ڽĳ����� ���ȣ��
	if (m_pCenter != NULL) {
		pbranchview->SetGISPosition(m_nDbID, m_pCenter->m_nDbID, m_pSLDDPoint, m_pGISDPoint, m_pCenter->m_pSLDDPoint, m_pCenter->m_pGISDPoint);
		m_pCenter->SetGISBranchPos(pbranchview);
	}
	if (m_pRight != NULL) {
		pbranchview->SetGISPosition(m_nDbID, m_pRight->m_nDbID, m_pSLDDPoint, m_pGISDPoint, m_pRight->m_pSLDDPoint, m_pRight->m_pGISDPoint);
		m_pRight->SetGISBranchPos(pbranchview);
	}
	if (m_pLeft != NULL) {
		pbranchview->SetGISPosition(m_nDbID, m_pLeft->m_nDbID, m_pSLDDPoint, m_pGISDPoint, m_pLeft->m_pSLDDPoint, m_pLeft->m_pGISDPoint);
		m_pLeft->SetGISBranchPos(pbranchview);
	}
	if (m_pLeftTop != NULL) {
		pbranchview->SetGISPosition(m_nDbID, m_pLeftTop->m_nDbID, m_pSLDDPoint, m_pGISDPoint, m_pLeftTop->m_pSLDDPoint, m_pLeftTop->m_pGISDPoint);
		m_pLeftTop->SetGISBranchPos(pbranchview);
	}
	if (m_pRightBottom != NULL) {
		pbranchview->SetGISPosition(m_nDbID, m_pRightBottom->m_nDbID, m_pSLDDPoint, m_pGISDPoint, m_pRightBottom->m_pSLDDPoint, m_pRightBottom->m_pGISDPoint);
		m_pRightBottom->SetGISBranchPos(pbranchview);
	}
}

double CNodeView::GetDerGenMw(int nCbswIdx)
{
	double dVal(0);
	
	dVal = GETVALUE(double, _T("cbsw_dyn_stdleo"), _T("cbsw_dergenmw"), nCbswIdx);
// 	dVal = 13854;
	
	return dVal * 1000;
	//////////////// 211025 ������ ����
}

double CNodeView::GetDerRaMw(int nCbswIdx)
{
	double dVal(0);

	dVal = GETVALUE(double, _T("cbsw_dyn_stdleo"), _T("cbsw_derramw"), nCbswIdx);
// 	dVal = 14000;

	return dVal * 1000;
	//////////////// 211025 ������ ����
}