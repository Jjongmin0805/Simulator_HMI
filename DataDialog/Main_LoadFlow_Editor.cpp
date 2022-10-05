// Main_LoadFlow_Editor.cpp : 구현 파일입니다.
//

#include "pch.h"

#include "Main_LoadFlow_Editor.h"
#include "../include/PNOVR_Ctrl/Util_FileParsing_CSV.h"
#include "../DataManager/CDataManager.h"


// CMain_LoadFlow_Editor

IMPLEMENT_DYNAMIC(CMain_LoadFlow_Editor, CWnd)

CMain_LoadFlow_Editor::CMain_LoadFlow_Editor() :	m_nCtrlKey( 0 ), m_nShiftKey( 0 ), m_nOldMultiSelectIndex( -1 ), 
													m_OffsetRect1( 0, 0, 0, 0 ), m_OffsetRect2( m_OffsetRect1 ), m_OffsetRect3( m_OffsetRect1 ), m_OffsetRect4( m_OffsetRect1 ), 
													m_FLOffset_BtnRect( 0, 0, 0, 0 ), m_FLWrite_BtnRect( 0, 0, 0, 0 ), m_nOffsetFocus( -1 ),
													m_szLabelValue( _T("Load Edit") ), m_LabelRect( 0, 0, 0, 0 ), m_LabelTitleRect( 0, 0, 0, 0 )
{
	m_pLFData										= NULL;

	m_pLFMng = new CMain_LoadFlow_Mng;
	m_pLFMng->Loading();
	m_pLFMng->Create_VMLFInfor();
	m_pLFMng->Loading_VMLFInfor();

	thePNO_Ctrlmng->SetColor_MainBKG(theMainColorBgk);
}

CMain_LoadFlow_Editor::~CMain_LoadFlow_Editor()
{
	Writing_VMLFInfor_File();
	for_each( m_vecLFData.begin(), m_vecLFData.end(), PNOVR_EraseObjData() );		m_vecLFData.clear();

	delete m_pLFMng;
}


BEGIN_MESSAGE_MAP(CMain_LoadFlow_Editor, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(ID_MGLFEDIT_1_1, &CMain_LoadFlow_Editor::OnSDMSLfeditCombo11SelectChange)
	ON_CBN_SELCHANGE(ID_MGLFEDIT_1_2, &CMain_LoadFlow_Editor::OnSDMSLfeditCombo12SelectChange)
	ON_CBN_SELCHANGE(ID_MGLFEDIT_1_3, &CMain_LoadFlow_Editor::OnSDMSLfeditCombo13SelectChange)
	ON_CBN_SELCHANGE(ID_MGLFEDIT_1_4, &CMain_LoadFlow_Editor::OnSDMSLfeditCombo14SelectChange)
	ON_CBN_SELCHANGE(ID_MGLFEDIT_1_5, &CMain_LoadFlow_Editor::OnSDMSLfeditComboFLAppSelectChange)
	ON_BN_CLICKED(ID_MGLFEDIT_3_1, &CMain_LoadFlow_Editor::OnSDMSLfeditButton31)
	ON_BN_CLICKED(ID_MGLFEDIT_3_2, &CMain_LoadFlow_Editor::OnSDMSLfeditButton32)
	ON_BN_CLICKED(ID_MGLFEDIT_3_3, &CMain_LoadFlow_Editor::OnSDMSLfeditButton33)
	ON_BN_CLICKED(ID_MGLFEDIT_3_4, &CMain_LoadFlow_Editor::OnSDMSLfeditButton34)
	ON_MESSAGE(PNOVR_LISTEDITRETURN, &CMain_LoadFlow_Editor::OnSendMsgEditReturn)
	ON_MESSAGE(SENDMSG_LOADFLOW, &CMain_LoadFlow_Editor::OnSendMsg2LoadFlow)
END_MESSAGE_MAP()

// CMain_LoadFlow_Editor 메시지 처리기입니다.


void CMain_LoadFlow_Editor::OnPaint()
{
	CPaintDC dc(this);

	Draw( &dc );
}

BOOL CMain_LoadFlow_Editor::Draw( CDC* pDC )
{
	CRect							_rect( 0, 0, 0, 0 ), _roundrect( 0, 0, 0, 0 );
	GetClientRect( &_rect );

	if( !m_pLFData )
	{
		CDC							BufferDC;
		BufferDC.CreateCompatibleDC( pDC );
		CBitmap						bmpBuffer, *pOldBitmap1											= NULL;
		bmpBuffer.CreateCompatibleBitmap( pDC, _rect.Width(), _rect.Height() );
		pOldBitmap1																			= (CBitmap *)BufferDC.SelectObject( &bmpBuffer );
		BufferDC.FillSolidRect( 0, 0, _rect.Width(), _rect.Height(),theMainColorBgk );

		Draw_BackLabel( &BufferDC );
		ViewEditContent( &BufferDC );
		ViewEmptyData( &BufferDC );

		pDC->BitBlt( 0, 0, _rect.Width(), _rect.Height(), &BufferDC, 0, 0, SRCCOPY );
		BufferDC.SelectObject( pOldBitmap1 );
		BufferDC.DeleteDC();

	} else {
		int							nWidth( m_pLFData->m_ViewRect.right > _rect.Width() ? m_pLFData->m_ViewRect.right : _rect.Width() );
		int							nHeight( m_pLFData->m_ViewRect.Height() > _rect.Height() ? m_pLFData->m_ViewRect.Height() : _rect.Height() );
		nWidth																				+= 50;

		CDC							BufferDC;
		BufferDC.CreateCompatibleDC( pDC );
		CBitmap						bmpBuffer, *pOldBitmap1									= NULL;
		bmpBuffer.CreateCompatibleBitmap( pDC, nWidth, nHeight );
		pOldBitmap1																			= (CBitmap *)BufferDC.SelectObject( &bmpBuffer );

		CDC							BufferDC_Se;
		BufferDC_Se.CreateCompatibleDC( &BufferDC );
		CBitmap						bmpBuffer_Se, *pOldBitmap1_Se							= NULL;
		bmpBuffer_Se.CreateCompatibleBitmap( &BufferDC, nWidth, nHeight );
		pOldBitmap1_Se																		= (CBitmap *)BufferDC_Se.SelectObject( &bmpBuffer_Se );
		BufferDC_Se.FillSolidRect( 0, 0, nWidth, nHeight, theMainColorBgk );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Draw_BackLabel( &BufferDC_Se );
		ViewEditContent( &BufferDC_Se );
		BufferDC.BitBlt( 0, 0, _rect.Width(), _rect.Height(), &BufferDC_Se, 0, 0, SRCCOPY );

//------

		ViewCoordinates( &BufferDC_Se );
		ViewLoadLine( &BufferDC_Se );
		CRect						ClipRect( m_pLFData->m_ViewRoundRect );

		ViewRoundLoadLine( &BufferDC, true );

		//ClipRect.left																		-= 140;
		ClipRect.left																		+= 5;
		ClipRect.right																		= _rect.right - 50;
		ClipRect.bottom																		+= 70;
		CRgn						_DrawRgn;
		_DrawRgn.CreateRectRgnIndirect( ClipRect );
		BufferDC.SelectClipRgn( &_DrawRgn );
		BufferDC.BitBlt( 0, 0, _rect.Width(), _rect.Height(), &BufferDC_Se, m_pLFData->m_nScrollPos, 0, SRCCOPY );

//------

		pDC->BitBlt( 0, 0, _rect.Width(), _rect.Height(), &BufferDC, 0, 0, SRCCOPY );

		_DrawRgn.DeleteObject();

		BufferDC_Se.SelectObject( pOldBitmap1_Se );
		BufferDC_Se.DeleteDC();

		BufferDC.SelectObject( pOldBitmap1 );
		BufferDC.DeleteDC();

//------


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 		CRect				ClipRect( m_pLFData->m_ViewRoundRect );
// 		ClipRect.left																		-= 140;
// 		ClipRect.right																		= _rect.right - 50;
// 		ClipRect.bottom																		+= 70;
// 		pDC->FillSolidRect( ClipRect.left, ClipRect.top, ClipRect.Width(), ClipRect.Height(), RGB( 225, 0, 0 ) );
	}

	return TRUE;
}


void CMain_LoadFlow_Editor::ViewCoordinates( CDC* pDC )
{
	CPen								pen, *pOldpen;
	CBrush								brush, *pOldbrush;
	pen.CreatePen( PS_SOLID, 2, RGB( 128, 128, 128 ) );
	pOldpen																			= pDC->SelectObject( &pen );
	pOldbrush																		= (CBrush*)pDC->SelectStockObject( NULL_BRUSH );

	CRect								_viewrect( m_pLFData->m_ViewRect );
	_viewrect.bottom																+= 70;

	pDC->FillSolidRect( _viewrect, RGB( 204, 208, 217 ) );
	pDC->Rectangle( m_pLFData->m_ViewRoundRect );

	pDC->SelectObject( pOldbrush );
	brush.DeleteObject();
	pDC->SelectObject( pOldpen );
	pen.DeleteObject();
}

CRect CMain_LoadFlow_Editor::ViewRoundLoadLine( CDC* pDC, bool bScreenSizeOn )
{
	if( !m_pLFData )																			return  CRect( 0, 0, 0, 0 );

	CPen								pen, *pOldpen;
	CBrush								brush, *pOldbrush;
	pen.CreatePen( PS_SOLID, 1, RGB( 128, 128, 128 ) );
	pOldpen																			= pDC->SelectObject( &pen );
	pOldbrush																		= (CBrush*)pDC->SelectStockObject( NULL_BRUSH );

	pDC->MoveTo( m_pLFData->m_ViewRoundRect.left + 10, m_pLFData->m_ViewRoundRect.top );
	pDC->LineTo( m_pLFData->m_ViewRoundRect.left +  0, m_pLFData->m_ViewRoundRect.top );
	pDC->LineTo( m_pLFData->m_ViewRoundRect.left +  0, m_pLFData->m_ViewRoundRect.bottom - 1 );
	pDC->LineTo( m_pLFData->m_ViewRoundRect.left + 10, m_pLFData->m_ViewRoundRect.bottom - 1 );

	pDC->SelectObject( pOldpen );
	pen.DeleteObject();
	pen.CreatePen( PS_SOLID, 1, RGB( 128, 128, 128 ) );
	pOldpen																			= pDC->SelectObject( &pen );

	CFont						_font, *pOldFont;
	_font.CreateFont( 16, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔고딕"));
	pOldFont																		= pDC->SelectObject( &_font );

	int									i( 0 ), nViewFontSize( (int)( (double)( m_pLFData->m_vecLoadValuePt[ 1 ].x - m_pLFData->m_vecLoadValuePt[ 0 ].x ) / 2.0 ) );
	CString								szStr( _T("") );
	pDC->SetBkMode( TRANSPARENT );

	pen.DeleteObject();
	pen.CreatePen( PS_DOT, 1, RGB( 255, 127, 39 ) );
	pOldpen																			= pDC->SelectObject( &pen );

	pDC->MoveTo( m_pLFData->m_ViewRoundRect.left - (INT)( (double)m_pLFData->m_ViewRoundRect.Height() * 0.01 ), m_pLFData->m_MaxValuePt.y );		pDC->LineTo( m_pLFData->m_ViewRoundRect.left, m_pLFData->m_MaxValuePt.y );
	pDC->MoveTo( m_pLFData->m_ViewRoundRect.left - (INT)( (double)m_pLFData->m_ViewRoundRect.Height() * 0.01 ), m_pLFData->m_MinValuePt.y );		pDC->LineTo( m_pLFData->m_ViewRoundRect.left, m_pLFData->m_MinValuePt.y );
	if( bScreenSizeOn )
	{
		CRect							_thisrect( 0, 0, 0, 0 );
		GetClientRect( &_thisrect );
		_thisrect.right																-= 50;
		pDC->MoveTo( m_pLFData->m_ViewRoundRect.left + 5, m_pLFData->m_MaxValuePt.y );																pDC->LineTo( _thisrect.right, m_pLFData->m_MaxValuePt.y );
		pDC->MoveTo( m_pLFData->m_ViewRoundRect.left + 5, m_pLFData->m_MinValuePt.y );																pDC->LineTo( _thisrect.right, m_pLFData->m_MinValuePt.y );
	} else {
		pDC->MoveTo( m_pLFData->m_ViewRoundRect.left + 5, m_pLFData->m_MaxValuePt.y );																pDC->LineTo( m_pLFData->m_ViewRoundRect.right, m_pLFData->m_MaxValuePt.y );
		pDC->MoveTo( m_pLFData->m_ViewRoundRect.left + 5, m_pLFData->m_MinValuePt.y );																pDC->LineTo( m_pLFData->m_ViewRoundRect.right, m_pLFData->m_MinValuePt.y );
	}

	CRect								_YSideViewTextRect( 0, 0, 0, 0 ), _TempRect( _YSideViewTextRect );
	_YSideViewTextRect.right														= m_pLFData->m_ViewRoundRect.left - (INT)( (double)m_pLFData->m_ViewRoundRect.Height() * 0.01 ) * 2;
	_YSideViewTextRect.bottom														= m_pLFData->m_MaxValuePt.y + 15;
	_YSideViewTextRect.left															= _YSideViewTextRect.right - 100;
	_YSideViewTextRect.top															= m_pLFData->m_MaxValuePt.y - 15;
	szStr.Format( _T("MAX %.0f"), m_pLFData->m_dValueMax );
	pDC->DrawText( szStr, _YSideViewTextRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE );

	_YSideViewTextRect.bottom														= m_pLFData->m_MinValuePt.y + 15;
	_YSideViewTextRect.top															= m_pLFData->m_MinValuePt.y - 15;
	szStr.Format( _T("MIN %.0f"), m_pLFData->m_dValueMin );
	pDC->DrawText( szStr, _YSideViewTextRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE );

	pDC->SelectObject(pOldFont);
	_font.DeleteObject();
	pDC->SelectObject( pOldbrush );
	brush.DeleteObject();
	pDC->SelectObject( pOldpen );
	pen.DeleteObject();

	return _YSideViewTextRect;
}


void CMain_LoadFlow_Editor::ViewLoadLine( CDC* pDC )
{
	if( !m_pLFData )																			return  ;

	CPen								pen, *pOldpen;
	CBrush								brush, *pOldbrush;
	pen.CreatePen( PS_SOLID, 2, RGB( 128, 128, 128 ) );
	pOldpen																			= pDC->SelectObject( &pen );
	pOldbrush																		= (CBrush*)pDC->SelectStockObject( NULL_BRUSH );

	CFont						_font, *pOldFont;
	_font.CreateFont( 16, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔고딕"));
	pOldFont																		= pDC->SelectObject( &_font );

	int									i( 0 ), nViewFontSize( (int)( (double)( m_pLFData->m_vecLoadValuePt[ 1 ].x - m_pLFData->m_vecLoadValuePt[ 0 ].x ) / 2.0 ) );
	CString								szStr( _T("") );
	pDC->SetBkMode( TRANSPARENT );
	for( i = 0 ; i < 96 ; i++ )
	{
		if( i % 2 == 0 )
		{
			if( m_pLFData->m_nMultiSelectIndex[ i ] == VIEWLB_CLICK )
			{
				pDC->FillSolidRect( CRect( m_pLFData->m_vecLoadValuePt[ i ].x - nViewFontSize, m_pLFData->m_ViewRoundRect.top + 5, m_pLFData->m_vecLoadValuePt[ i ].x + nViewFontSize, m_pLFData->m_ViewRoundRect.bottom - 5 ), RGB( 164, 96, 96 ) );
			} else {
				pDC->FillSolidRect( CRect( m_pLFData->m_vecLoadValuePt[ i ].x - nViewFontSize, m_pLFData->m_ViewRoundRect.top + 5, m_pLFData->m_vecLoadValuePt[ i ].x + nViewFontSize, m_pLFData->m_ViewRoundRect.bottom - 5 ), RGB( 128, 128, 128 ) );
			}
		} else {
			if( m_pLFData->m_nMultiSelectIndex[ i ] == VIEWLB_CLICK )
			{
				pDC->FillSolidRect( CRect( m_pLFData->m_vecLoadValuePt[ i ].x - nViewFontSize, m_pLFData->m_ViewRoundRect.top + 5, m_pLFData->m_vecLoadValuePt[ i ].x + nViewFontSize, m_pLFData->m_ViewRoundRect.bottom - 5 ), RGB( 128, 96, 96 ) );
			} else {
				pDC->FillSolidRect( CRect( m_pLFData->m_vecLoadValuePt[ i ].x - nViewFontSize, m_pLFData->m_ViewRoundRect.top + 5, m_pLFData->m_vecLoadValuePt[ i ].x + nViewFontSize, m_pLFData->m_ViewRoundRect.bottom - 5 ), RGB( 96, 96, 96 ) );
			}
		}

		pDC->MoveTo( m_pLFData->m_vecLoadValuePt[ i ].x, m_pLFData->m_ViewRoundRect.bottom );
		pDC->LineTo( m_pLFData->m_vecLoadValuePt[ i ].x, m_pLFData->m_ViewRoundRect.bottom + (INT)( (double)m_pLFData->m_ViewRoundRect.Height() * 0.01 ) );

		pDC->SetTextColor( RGB( 128, 128, 128 ) );
		szStr.Format( _T("%d"),  i + 1 );
		pDC->DrawText( szStr, CRect( m_pLFData->m_vecLoadValuePt[ i ].x - nViewFontSize, m_pLFData->m_ViewRoundRect.bottom + 10, m_pLFData->m_vecLoadValuePt[ i ].x + nViewFontSize, m_pLFData->m_ViewRoundRect.bottom + 25 ), DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		szStr.Format( _T("%d-%d"), ( i / 4 ) + 1, ( i % 4 ) * 15 );
		pDC->DrawText( szStr, CRect( m_pLFData->m_vecLoadValuePt[ i ].x - nViewFontSize, m_pLFData->m_ViewRoundRect.bottom + 30, m_pLFData->m_vecLoadValuePt[ i ].x + nViewFontSize, m_pLFData->m_ViewRoundRect.bottom + 45 ), DT_CENTER | DT_VCENTER | DT_SINGLELINE );

// 		if( i % 2 == 0 )
// 		{
// 			pDC->SetTextColor( RGB( 0, 168, 0 ) );
// 		} else {
// 			pDC->SetTextColor( RGB( 196, 196, 196 ) );
// 		}

		if( m_pLFData->m_nSelectIndex == i || 
			( m_pLFData->m_nSelectIndex > 0 && m_pLFData->m_nMultiSelectIndex[ m_pLFData->m_nSelectIndex ] == VIEWLB_CLICK ) && m_pLFData->m_nMultiSelectIndex[ i ] == VIEWLB_CLICK )
		{
			pDC->SetTextColor( RGB( 66, 255, 60 ) );
		} else {
			pDC->SetTextColor( RGB( 0, 168, 0 ) );
		}
		szStr.Format( _T("%.0f"), m_pLFData->m_vecLoadValue[ i ] );
		pDC->DrawText( szStr, CRect( m_pLFData->m_vecLoadValuePt[ i ].x - nViewFontSize, m_pLFData->m_ViewRoundRect.bottom + 45, m_pLFData->m_vecLoadValuePt[ i ].x + nViewFontSize, m_pLFData->m_ViewRoundRect.bottom + 80 ), DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	}

	CRect								_YSideViewTextRect( ViewRoundLoadLine( pDC, false ) );

// 	pDC->MoveTo( m_pLFData->m_ViewRoundRect.left - (INT)( (double)m_pLFData->m_ViewRoundRect.Height() * 0.01 ), m_pLFData->m_MaxValuePt.y );		pDC->LineTo( m_pLFData->m_ViewRoundRect.left, m_pLFData->m_MaxValuePt.y );
// 	pDC->MoveTo( m_pLFData->m_ViewRoundRect.left - (INT)( (double)m_pLFData->m_ViewRoundRect.Height() * 0.01 ), m_pLFData->m_MinValuePt.y );		pDC->LineTo( m_pLFData->m_ViewRoundRect.left, m_pLFData->m_MinValuePt.y );
// 
// 	pen.DeleteObject();
// 	pen.CreatePen( PS_DOT, 1, RGB( 128, 128, 128 ) );
// 	pOldpen																			= pDC->SelectObject( &pen );
// 	pDC->MoveTo( m_pLFData->m_ViewRoundRect.left + 5, m_pLFData->m_MaxValuePt.y );													pDC->LineTo( m_pLFData->m_ViewRoundRect.right, m_pLFData->m_MaxValuePt.y );
// 	pDC->MoveTo( m_pLFData->m_ViewRoundRect.left + 5, m_pLFData->m_MinValuePt.y );													pDC->LineTo( m_pLFData->m_ViewRoundRect.right, m_pLFData->m_MinValuePt.y );
// 
//	CRect								_YSideViewTextRect( 0, 0, 0, 0 ), _TempRect( _YSideViewTextRect );
//	_YSideViewTextRect.right														= m_pLFData->m_ViewRoundRect.left - (INT)( (double)m_pLFData->m_ViewRoundRect.Height() * 0.01 ) * 2;
// 	_YSideViewTextRect.bottom														= m_pLFData->m_MaxValuePt.y + 15;
// 	_YSideViewTextRect.left															= _YSideViewTextRect.right - 100;
// 	_YSideViewTextRect.top															= m_pLFData->m_MaxValuePt.y - 15;
// 	szStr.Format( _T("MAX %.0f"), m_pLFData->m_dValueMax );
// 	pDC->DrawText( szStr, _YSideViewTextRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE );
// 
// 	_YSideViewTextRect.bottom														= m_pLFData->m_MinValuePt.y + 15;
// 	_YSideViewTextRect.top															= m_pLFData->m_MinValuePt.y - 15;
// 	szStr.Format( _T("MIN %.0f"), m_pLFData->m_dValueMin );
// 	pDC->DrawText( szStr, _YSideViewTextRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE );

	// Select Box Draw
	for( i = 0 ; i < 96 ; i++ )
	{
		if( m_pLFData->m_nMultiSelectIndex[ i ] == VIEWLB_CLICK )
		{
			pen.DeleteObject();
			pen.CreatePen( PS_SOLID, 2, RGB( 185, 0, 0 ) );
			pOldpen																	= pDC->SelectObject( &pen );

			_YSideViewTextRect														= CRect( m_pLFData->m_vecLoadValuePt[ i ], m_pLFData->m_vecLoadValuePt[ i ] );
			_YSideViewTextRect.InflateRect( CSize( 10, 10 ) );
			pDC->Rectangle( _YSideViewTextRect );
		} else if( m_pLFData->m_nMoveSelectIndex == i )
		{
			pen.DeleteObject();
			pen.CreatePen( PS_DOT, 1, RGB( 0, 255, 0 ) );
			pOldpen																	= pDC->SelectObject( &pen );

			_YSideViewTextRect														= CRect( m_pLFData->m_vecLoadValuePt[ i ], m_pLFData->m_vecLoadValuePt[ i ] );
			_YSideViewTextRect.InflateRect( CSize( 10, 10 ) );
			pDC->Rectangle( _YSideViewTextRect );
		}
	}

	// Line Draw
	pen.DeleteObject();
	pen.CreatePen( PS_DASH, 3, RGB( 0, 255, 0 ) );
	pOldpen																			= pDC->SelectObject( &pen );

	pDC->MoveTo( m_pLFData->m_vecLoadValuePt[ 0 ] );
	for( i = 1 ; i < 96 ; i++ )
	{
		pDC->LineTo( m_pLFData->m_vecLoadValuePt[ i ] );
	}

	CPoint								_UpDnArrowObjPt[ 3 ];
	for( i = 0 ; i < 96 ; i++ )
	{
		if( m_pLFData->m_nSelectIndex == i || 
			( m_pLFData->m_nSelectIndex > 0 && m_pLFData->m_nMultiSelectIndex[ m_pLFData->m_nSelectIndex ] == VIEWLB_CLICK ) && m_pLFData->m_nMultiSelectIndex[ i ] == VIEWLB_CLICK )
		{
			_YSideViewTextRect														= CRect( m_pLFData->m_vecLoadValuePt[ i ], m_pLFData->m_vecLoadValuePt[ i ] );
			_YSideViewTextRect.InflateRect( CSize( 10, 10 ) );

			_UpDnArrowObjPt[ 0 ]													= CPoint( _YSideViewTextRect.left, _YSideViewTextRect.top - 3 );
			_UpDnArrowObjPt[ 1 ]													= CPoint( _YSideViewTextRect.right, _YSideViewTextRect.top - 3 );
			_UpDnArrowObjPt[ 2 ]													= CPoint( _YSideViewTextRect.CenterPoint().x, _YSideViewTextRect.top - 3 - (int)( (double)_YSideViewTextRect.Height() / 2.0 ) );
			pen.DeleteObject();

			pOldpen																	= (CPen*)pDC->SelectStockObject( NULL_PEN );
			brush.DeleteObject();
			brush.CreateSolidBrush( RGB( 255, 107, 5 ) );
			pOldbrush																= pDC->SelectObject( &brush );
			pDC->Polygon( _UpDnArrowObjPt, 3 );

			_UpDnArrowObjPt[ 0 ]													= CPoint( _YSideViewTextRect.left, _YSideViewTextRect.bottom + 3 );
			_UpDnArrowObjPt[ 1 ]													= CPoint( _YSideViewTextRect.right, _YSideViewTextRect.bottom + 3 );
			_UpDnArrowObjPt[ 2 ]													= CPoint( _YSideViewTextRect.CenterPoint().x, _YSideViewTextRect.bottom + 3 + (int)( (double)_YSideViewTextRect.Height() / 2.0 ) );
			pen.DeleteObject();
			pOldpen																	= (CPen*)pDC->SelectStockObject( NULL_PEN );
			brush.DeleteObject();
			brush.CreateSolidBrush( RGB( 0, 162, 233 ) );
			pOldbrush																= pDC->SelectObject( &brush );
			pDC->Polygon( _UpDnArrowObjPt, 3 );
		}
	}

	// Point Box Draw
	pen.DeleteObject();
	pen.CreatePen( PS_DASH, 3, RGB( 0, 255, 0 ) );
	pOldpen																			= pDC->SelectObject( &pen );
	brush.DeleteObject();
	brush.CreateSolidBrush( RGB( 0, 128, 0 ) );
	pOldbrush																		= pDC->SelectObject( &brush );
	for( i = 0 ; i < 96 ; i++ )
	{
		_YSideViewTextRect															= CRect( m_pLFData->m_vecLoadValuePt[ i ], m_pLFData->m_vecLoadValuePt[ i ] );
		_YSideViewTextRect.InflateRect( CSize( 5, 5 ) );
		pDC->Rectangle( _YSideViewTextRect );
	}

	pDC->SelectObject(pOldFont);
	_font.DeleteObject();
	pDC->SelectObject( pOldbrush );
	brush.DeleteObject();
	pDC->SelectObject( pOldpen );
	pen.DeleteObject();
}

void CMain_LoadFlow_Editor::ViewEditContent( CDC* pDC )
{
//	COLORREF							_DrawColor( RGB( 64, 64, 64 ) );
	COLORREF							_DrawColor( RGB( 255, 202, 18 ) ), _LineColor( RGB( 50, 52, 57 ) ), _ObjdectColor( RGB( 81, 83, 87 ) );


	CPen								pen, *pOldpen;
	CBrush								brush, *pOldbrush;
	pen.CreatePen( PS_SOLID, 2, _LineColor );
	pOldpen																			= pDC->SelectObject( &pen );
	brush.CreateSolidBrush( _ObjdectColor );
	pOldbrush																		= pDC->SelectObject( &brush );
//	pOldbrush																		= (CBrush*)pDC->SelectStockObject( NULL_BRUSH );

	CRect								_viewrect( 0, 0, 0, 0 ), _grouprect( 0, 0, 0, 0 );
	_viewrect = m_OffsetRect1;			_viewrect.InflateRect( CSize( 4, 4 ) );			pDC->Rectangle( _viewrect );
	_viewrect = m_OffsetRect2;			_viewrect.InflateRect( CSize( 4, 4 ) );			pDC->Rectangle( _viewrect );
	_viewrect = m_OffsetRect3;			_viewrect.InflateRect( CSize( 4, 4 ) );			pDC->Rectangle( _viewrect );
	_viewrect = m_OffsetRect4;			_viewrect.InflateRect( CSize( 4, 4 ) );			pDC->Rectangle( _viewrect );

	_viewrect																		= CRect( m_OffsetRect1.left - 100, m_OffsetRect1.top, m_OffsetRect1.left - 10, m_OffsetRect1.bottom );
	_grouprect.TopLeft()															= _viewrect.TopLeft();
	_grouprect.top																	-= 5;
	_grouprect.BottomRight()														= m_FLOffset_BtnRect.BottomRight();
	_grouprect.right																+= 5;

	pen.DeleteObject();
	pen.CreatePen( PS_SOLID, 2, _LineColor );
	pOldpen																			= pDC->SelectObject( &pen );

	CRect								_FirstComboRect( 0, 0, 0, 0 );
	m_InforCombo1.GetWindowRect( &_FirstComboRect );
	ScreenToClient( &_FirstComboRect );
	_grouprect.left																	= _FirstComboRect.left;
	_grouprect.InflateRect( CSize( 10, 10 ) );
	pDC->RoundRect( _grouprect, CPoint( 5, 5 ) );

	_grouprect																		= CRect( m_FLAppExe_ComboRect.TopLeft(), m_FLAppStop_BtnRect.BottomRight() );
	_grouprect.top																	= m_FLAppStop_BtnRect.top;
	_grouprect.InflateRect( CSize( 10, 10 ) );
	pDC->RoundRect( _grouprect, CPoint( 5, 5 ) );

	_grouprect																		= m_FLWrite_BtnRect;
	_grouprect.InflateRect( CSize( 10, 10 ) );
	pDC->RoundRect( _grouprect, CPoint( 5, 5 ) );

	CFont						_font, *pOldFont;
	_font.CreateFont( 20, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	pOldFont																		= pDC->SelectObject( &_font );
	pDC->SetTextColor( RGB(0,0,0) );
	pDC->DrawText( _T("LF Offset ("), _viewrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	_viewrect																		= CRect( m_OffsetRect1.right, m_OffsetRect1.top, m_OffsetRect2.left, m_OffsetRect1.bottom );
	pDC->DrawText( _T("~"), _viewrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	_viewrect																		= CRect( m_OffsetRect2.right, m_OffsetRect1.top, m_OffsetRect3.left, m_OffsetRect1.bottom );
	pDC->DrawText( _T(") ×"), _viewrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	_viewrect																		= CRect( m_OffsetRect3.right, m_OffsetRect1.top, m_OffsetRect4.left, m_OffsetRect1.bottom );
	pDC->DrawText( _T("±"), _viewrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	pDC->SelectObject(pOldFont);
	_font.DeleteObject();

	pDC->SelectObject( pOldbrush );
	brush.DeleteObject();
	pDC->SelectObject( pOldpen );
	pen.DeleteObject();
}

void CMain_LoadFlow_Editor::Draw_BackLabel( CDC* pDC )
{
	CRect							thisrect( m_LabelRect ), titleROUNDrect( 0, 0, 250, 35 );
	titleROUNDrect																			+= thisrect.TopLeft();
	CRect							titlepointrect( titleROUNDrect ), titlenamerect( titleROUNDrect );
//	GetClientRect( &thisrect );

	//-

	Graphics						graphics( pDC->GetSafeHdc() );

	pDC->FillSolidRect( thisrect, thePNO_Ctrlmng->GetColor_MainBKG() );
	//pDC->FillSolidRect(thisrect, RGB(255,0,0));

	thisrect.top																			= ( titleROUNDrect.bottom - 18 );
	Color							crBoxGradient_B, crBoxGradient_E;
	//crBoxGradient_B.SetFromCOLORREF( thePNO_Ctrlmng->GetColor_Label_Bk() );
	crBoxGradient_B																			= ( Color( 255, 250, 250, 250 ) );
	crBoxGradient_E.SetFromCOLORREF(thePNO_Ctrlmng->GetColor_Label_GradientEndBk() );

	RectF							rectDrawBox( (REAL)thisrect.left, (REAL)thisrect.top, (REAL)thisrect.Width(), (REAL)thisrect.Height() );
	LinearGradientBrush				brushLiner( rectDrawBox, crBoxGradient_B, crBoxGradient_E, LinearGradientModeVertical );
	graphics.FillRectangle( &brushLiner, rectDrawBox );

	titleROUNDrect																			+= CPoint( 3, 3 );
	CPen*							pPen													= (CPen*)pDC->SelectStockObject( NULL_PEN );
	CBrush							brush( RGB( 161, 162, 163 ) );
	CBrush*							pOldBrush												= pDC->SelectObject( &brush );
	pDC->RoundRect( titleROUNDrect, CPoint( 8, 8 ) );
	pDC->SelectObject( pOldBrush );
	brush.DeleteObject();

	titleROUNDrect																			-= CPoint( 3, 3 );
	brush.CreateSolidBrush( thePNO_Ctrlmng->GetColor_Label_Bk() );
	pOldBrush																				= pDC->SelectObject( &brush );
	pDC->RoundRect( titleROUNDrect, CPoint( 8, 8 ) );
	pDC->SelectObject( pOldBrush );
	brush.DeleteObject();

	pDC->SelectObject( pPen );

	titlenamerect.DeflateRect( CSize( 5, 5 ) );
	titlenamerect.left																		+= 30;							//titlepointrect.right + 15;

	graphics.ReleaseHDC( pDC->GetSafeHdc() );

	//-

	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( RGB( 225, 227, 230 ) );

	CFont							font;
	LOGFONT							lf;
	memset( &lf, 0, sizeof( LOGFONT ) );
	lf.lfHeight																				= 22;
	wcscpy_s( lf.lfFaceName, thePNO_Ctrlmng->GetList_ItemFontType() );
	lf.lfWeight																				= FW_BOLD;
	font.CreateFontIndirect( &lf );
	CFont*							def_font												= pDC->SelectObject(&font);

	pDC->DrawText( m_szLabelValue.c_str(), (int)m_szLabelValue.length(), titlenamerect, DT_LEFT | DT_VCENTER | DT_SINGLELINE );
	m_LabelTitleRect																		= titlenamerect;

	pDC->SelectObject( def_font );
	font.DeleteObject();

	CPen							InPen, *pInOldpen;
	InPen.CreatePen( PS_SOLID, 2, RGB( 225, 225, 225 ) );
	pInOldpen																				= pDC->SelectObject( &InPen );
	pOldBrush																				= (CBrush*)pDC->SelectStockObject( NULL_BRUSH );

	CRect							InDrawRect( m_LabelRect );
	InDrawRect.DeflateRect( CSize( 15, 15 ) );
	InDrawRect.top																			+= 40;
	pDC->Rectangle( InDrawRect );

	pDC->SelectObject( pOldBrush );
	pDC->SelectObject( pInOldpen );
	InPen.DeleteObject();
}


//////////////////////////////////////////////////////////////////////////

BOOL CMain_LoadFlow_Editor::Create( const RECT& rect, CWnd* pParentWnd )
{
	CWnd* pWnd = this;
	return pWnd->Create( NULL, NULL, LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL, rect, pParentWnd, 0 );		//| WS_HSCROLL | WS_VSCROLL
}

int CMain_LoadFlow_Editor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CreateComboCtrl();
	CreateEditCtrl();
	CreateButtonCtrl();

	return 0;
}

void CMain_LoadFlow_Editor::CreateComboCtrl()
{
	int							nComboWidth( 100 );
	CRect						_combo1_rect( 10, 20, 10 + nComboWidth, 220 ), _combo2_rect( _combo1_rect ), _combo3_rect( _combo1_rect ), _combo4_rect( _combo1_rect ), _combo5_rect( _combo1_rect );
	_combo2_rect.left			= _combo1_rect.right + 10;				_combo2_rect.right			= _combo2_rect.left + nComboWidth;
	_combo3_rect.left			= _combo2_rect.right + 10;				_combo3_rect.right			= _combo3_rect.left + nComboWidth;
	_combo4_rect.left			= _combo3_rect.right + 10;				_combo4_rect.right			= _combo4_rect.left + nComboWidth;
	_combo5_rect.left			= _combo4_rect.right + 10;				_combo5_rect.right			= _combo5_rect.left + nComboWidth;

	if( !m_InforCombo1.Create( WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS, _combo1_rect, this, ID_MGLFEDIT_1_1 ) )
	{
		AfxMessageBox( _T("Create RPF ComboBox Fail.\n") );
		return ;
	}
	if( !m_InforCombo2.Create( WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS, _combo2_rect, this, ID_MGLFEDIT_1_2 ) )
	{
		AfxMessageBox( _T("Create RPF ComboBox Fail.\n") );
		return ;
	}
	if( !m_InforCombo3.Create( WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS, _combo3_rect, this, ID_MGLFEDIT_1_3 ) )
	{
		AfxMessageBox( _T("Create RPF ComboBox Fail.\n") );
		return ;
	}
	if( !m_InforCombo4.Create( WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS, _combo4_rect, this, ID_MGLFEDIT_1_4 ) )
	{
		AfxMessageBox( _T("Create RPF ComboBox Fail.\n") );
		return ;
	}
	if( !m_Combo_FLApp.Create( WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS, _combo5_rect, this, ID_MGLFEDIT_1_5 ) )
	{
		AfxMessageBox( _T("Create RPF ComboBox Fail.\n") );
		return ;
	}

	m_InforCombo1.SetFont( CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) ) );
	m_InforCombo2.SetFont( CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) ) );
	m_InforCombo3.SetFont( CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) ) );
	m_InforCombo4.SetFont( CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) ) );
	m_Combo_FLApp.SetFont( CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) ) );
	m_InforCombo1.SetBkColor( RGB( 225, 225, 225 ) );
	m_InforCombo2.SetBkColor( RGB( 196, 196, 196 ) );
	m_InforCombo3.SetBkColor( RGB( 225, 225, 225 ) );
	m_InforCombo4.SetBkColor( RGB( 196, 196, 196 ) );
	m_Combo_FLApp.SetBkColor( RGB( 196, 196, 196 ) );

	m_InforCombo1.AddString( _T("전체") );	m_InforCombo1.SetCurSel( 0 );
	m_InforCombo2.AddString( _T("전체") );	m_InforCombo2.SetCurSel( 0 );
	m_InforCombo3.AddString( _T("전체") );	m_InforCombo3.SetCurSel( 0 );
	m_InforCombo4.AddString( _T("전체") );	m_InforCombo4.SetCurSel( 0 );
	m_Combo_FLApp.AddString( _T("AppVer500__MGBB") );	m_InforCombo4.SetCurSel( 0 );
}

void CMain_LoadFlow_Editor::CreateEditCtrl()
{
	m_OffsetEdit1.SetColor( theMainColorTxt, theMainColorBgk );
	m_OffsetEdit2.SetColor( theMainColorTxt, theMainColorBgk );
	m_OffsetEdit3.SetColor( theMainColorTxt, theMainColorBgk );
	m_OffsetEdit4.SetColor( theMainColorTxt, theMainColorBgk );

	DWORD						dwStyle( WS_CHILD | WS_VISIBLE | ES_CENTER | ES_AUTOHSCROLL );
	if( !m_OffsetEdit1.Create( dwStyle, CRect( 10, 20, 90, 220 ), this, ID_MGLFEDIT_2_1  ) )
	{
		AfxMessageBox( _T("Craete Fail Err : OffSet1 Edit.\n") );
		return ;
	}
	m_OffsetEdit1.SetColor( RGB( 0, 0, 0 ), RGB( 196, 196, 196 ) );

	if( !m_OffsetEdit2.Create( dwStyle, CRect( 10, 20, 90, 220 ), this, ID_MGLFEDIT_2_2  ) )
	{
		AfxMessageBox( _T("Craete Fail Err : OffSet2 Edit.\n") );
		return ;
	}
	m_OffsetEdit2.SetColor( RGB( 0, 0, 0 ), RGB( 196, 196, 196 ) );

	if( !m_OffsetEdit3.Create( dwStyle, CRect( 10, 20, 90, 220 ), this, ID_MGLFEDIT_2_3  ) )
	{
		AfxMessageBox( _T("Craete Fail Err : OffSet3 Edit.\n") );
		return ;
	}
	m_OffsetEdit3.SetColor( RGB( 0, 0, 0 ), RGB( 196, 196, 196 ) );

	if( !m_OffsetEdit4.Create( dwStyle, CRect( 10, 20, 90, 220 ), this, ID_MGLFEDIT_2_4  ) )
	{
		AfxMessageBox( _T("Craete Fail Err : OffSet4 Edit.\n") );
		return ;
	}
	m_OffsetEdit4.SetColor( RGB( 0, 0, 0 ), RGB( 196, 196, 196 ) );
}

void CMain_LoadFlow_Editor::CreateButtonCtrl()
{
	if( !m_FLOffset_Btn.Create( _T("Apply"), WS_CHILD | WS_VISIBLE, CRect( 10, 20, 90, 220 ), this, ID_MGLFEDIT_3_1 ) )
	{
		AfxMessageBox( _T("OffSetr Button Fail.\n") );
		return ;
	}
// 	m_FLOffset_Btn.SetFont( CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) ) );
// 	m_FLOffset_Btn.SetColor( RGB( 255, 255, 255 ), RGB( 128, 128, 128 ) );

	if( !m_FLWrite_Btn.Create( _T("Save"), WS_CHILD | WS_VISIBLE, CRect( 10, 20, 90, 220 ), this, ID_MGLFEDIT_3_2 ) )
	{
		AfxMessageBox( _T("Save LFInfor Button Fail.\n") );
		return ;
	}
// 	m_FLWrite_Btn.SetFont( CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) ) );
// 	m_FLWrite_Btn.SetColor( RGB( 255, 255, 255 ), RGB( 128, 128, 128 ) );

	if( !m_FLAppStart_Btn.Create( _T("Run"), WS_CHILD | WS_VISIBLE, CRect( 10, 20, 90, 220 ), this, ID_MGLFEDIT_3_3 ) )
	{
		AfxMessageBox( _T("OffSetr Button Fail.\n") );
		return ;
	}
	if( !m_FLAppStop_Btn.Create( _T("Stop"), WS_CHILD | WS_VISIBLE, CRect( 10, 20, 90, 220 ), this, ID_MGLFEDIT_3_4 ) )
	{
		AfxMessageBox( _T("OffSetr Button Fail.\n") );
		return ;
	}
	m_FLAppStop_Btn.EnableWindow( FALSE );
}

void CMain_LoadFlow_Editor::SetSSDL_ComboBox()
{
	wstring															szCombo1Name( _T("") ), szCombo2Name( _T("") );
	vector<wstring>													vecAddString;
	vector<wstring>::iterator										_str_iter;

	m_InforCombo1.ResetContent();
	theDataMng->GetSSNames( &vecAddString );
	for( _str_iter = vecAddString.begin() ; _str_iter != vecAddString.end() ; ++_str_iter )
	{
		m_InforCombo1.AddString( (*_str_iter).c_str() );
	}
	if( vecAddString.begin() != vecAddString.end() )
	{
		_str_iter = vecAddString.begin();
		szCombo1Name																= (*_str_iter).c_str();
	}
	m_InforCombo1.SetCurSel( 0 );

	m_InforCombo2.ResetContent();
	theDataMng->GetDLNames( szCombo1Name, &vecAddString );
	for( _str_iter = vecAddString.begin() ; _str_iter != vecAddString.end() ; ++_str_iter )
	{
		m_InforCombo2.AddString( (*_str_iter).c_str() );
	}
	if( vecAddString.begin() != vecAddString.end() )
	{
		_str_iter = vecAddString.begin();
		szCombo2Name																= (*_str_iter).c_str();
	}
	m_InforCombo2.SetCurSel( 0 );

	m_pLFData																		= GetLFData( szCombo1Name, szCombo2Name, szCombo2Name, 1 );
	if( m_pLFData )
	{
		ViewChageLFData( m_pLFData );
		DrawInvalidate();
	}

	m_InforCombo3.ResetContent();
	m_InforCombo3.AddString( _T("CB Load") );
	m_InforCombo3.AddString( _T("DG Load") );
	m_InforCombo3.SetCurSel( 0 );

	m_InforCombo4.ResetContent();
	m_InforCombo4.AddString( szCombo2Name.c_str() );
	m_InforCombo4.SetCurSel( 0 );

	// 20170824 sis 수행하고자 하는 Back-Bone 파일명을 검색
	m_Combo_FLApp.ResetContent();
	m_szBBAppFileName																			= _T("");

	CString							szWorkPath, nExeFileName;
	CFileFind						FFfinder;

	/*szWorkPath.Format( _T("%s\\*.exe"), MYPATH( _T(""), _T("") ).c_str() );
	BOOL							bWorking( FFfinder.FindFile( szWorkPath ) );
	while( bWorking )
	{
		bWorking																				= FFfinder.FindNextFile();
		if( FFfinder.IsDots() )
		{
			continue;
		}
		nExeFileName																			= FFfinder.GetFileName();
		if( nExeFileName.Find( _T("__MGBB") ) > 0 )
		{
			m_Combo_FLApp.AddString( nExeFileName );
		}
	}
	FFfinder.Close();

	if( m_Combo_FLApp.GetCount() > 0 )
	{
		m_Combo_FLApp.SetCurSel( 0 );
		m_Combo_FLApp.GetLBText( m_Combo_FLApp.GetCurSel(), m_szBBAppFileName );
		if( m_szBBAppFileName != _T("") )
		{
			theLFMng->SetLFFExeFileName( m_szBBAppFileName );
		}
	}*/
}

void CMain_LoadFlow_Editor::SetFLData_Loading()
{
	Loading_VMLFInfor();
}

CLFData* CMain_LoadFlow_Editor::GetLFData( wstring szSSName, wstring szDLName, wstring szGENName, int nType )
{
	CLFData*			pLFData				= NULL;
	vector<CLFData*>::iterator				_iter;
	for( _iter = m_vecLFData.begin() ; _iter != m_vecLFData.end() ; ++_iter )
	{
		if( (*_iter)->m_szSSName == szSSName && (*_iter)->m_szDLName == szDLName && (*_iter)->m_szGENName == szGENName && (*_iter)->m_nType == nType )
		{
			return (*_iter);
		}
	}
	return NULL;
}


void CMain_LoadFlow_Editor::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect						_rect( 0, 0, 0, 0 );
	GetClientRect( &_rect );

	int							nWidthMargin( int( (double)_rect.Width() * 0.1 ) );
	int							nHeightMargin( int( (double)_rect.Height() * 0.1 ) );
	int							i( 0 );
	CLFData*					pLFData												= NULL;

	for( i = 0 ; i < (int)m_vecLFData.size() ; i++ )
	{
		pLFData																		= m_vecLFData[ i ];
		if( !pLFData )																					continue ;

		pLFData->m_ViewRect															= _rect;
		pLFData->m_ViewRect.DeflateRect( CSize( nWidthMargin, nHeightMargin ) );

		if( pLFData->m_ViewRect == CRect( 0, 0, 0, 0 ) )												continue ;

		pLFData->m_ViewRect.right													= pLFData->m_vecLoadValuePt[ CalueValuePosition( pLFData ) - 1 ].x + nWidthMargin;
		pLFData->m_ViewRect.bottom													-= 30;
		pLFData->m_ViewRoundRect													= pLFData->m_ViewRect;
		pLFData->m_ViewRoundRect.right												= pLFData->m_ViewRect.right + 50 - nWidthMargin;
	}

	if( m_pLFData )
	{
		SCROLLINFO p;
		GetScrollInfo( SB_HORZ, &p );
		p.cbSize																	= sizeof( SCROLLINFO );
		p.fMask																		= SIF_ALL;
		p.nMin																		= 0;
		p.nMax																		= ( m_pLFData->m_ViewRect.right + 10 + nWidthMargin ) - _rect.Width();
		p.nPage																		= (UINT)( (double)_rect.Width() * 0.10 );
		p.nPos																		= m_pLFData->m_nScrollPos;
		p.nTrackPos																	= 0;
		SetScrollInfo( SB_HORZ, &p );

		CalueValuePosition(m_pLFData);
	}

	int							nComboWidth( 100 ), nStrartXpos( 300 );
	CRect						mv_combo_rect( nStrartXpos, 15, nStrartXpos + nComboWidth, 220 );
	if( m_InforCombo1.GetSafeHwnd() )
	{
		m_InforCombo1.MoveWindow( mv_combo_rect );
	}
	if( m_InforCombo2.GetSafeHwnd() )
	{
		mv_combo_rect.left																	= mv_combo_rect.right + 10;
		mv_combo_rect.right																	= mv_combo_rect.left + nComboWidth;
		m_InforCombo2.MoveWindow( mv_combo_rect );
	}
	if( m_InforCombo3.GetSafeHwnd() )
	{
		mv_combo_rect.left																	= mv_combo_rect.right + 10;
		mv_combo_rect.right																	= mv_combo_rect.left + nComboWidth;
		m_InforCombo3.MoveWindow( mv_combo_rect );
	}
	if( m_InforCombo4.GetSafeHwnd() )
	{
		mv_combo_rect.left																	= mv_combo_rect.right + 10;
		mv_combo_rect.right																	= mv_combo_rect.left + nComboWidth;
		m_InforCombo4.MoveWindow( mv_combo_rect );
	}

	int							nBtnWidth( 80 ), nEditWidth( 50 );
	CRect						_Btn_rect( 0, 0, 0, 0 );
	if( m_FLWrite_Btn.GetSafeHwnd() )
	{
		_Btn_rect																	= CRect( _rect.right - ( nBtnWidth + 10 ), 12, _rect.right - 10, 40 );
		m_FLWrite_BtnRect															= _Btn_rect;
		m_FLWrite_Btn.MoveWindow( _Btn_rect );
	}

	if( m_FLAppStop_Btn.GetSafeHwnd() )
	{
		_Btn_rect.right																= _Btn_rect.left - ( 30 );
		_Btn_rect.left																= _Btn_rect.right - ( nBtnWidth );
		m_FLAppStop_BtnRect															= _Btn_rect;
		m_FLAppStop_Btn.MoveWindow( _Btn_rect );
	}
	if( m_FLAppStart_Btn.GetSafeHwnd() )
	{
		_Btn_rect.right																= _Btn_rect.left - ( 10 );
		_Btn_rect.left																= _Btn_rect.right - ( nBtnWidth );
		m_FLAppStart_BtnRect														= _Btn_rect;
		m_FLAppStart_Btn.MoveWindow( _Btn_rect );
	}

	if( m_Combo_FLApp.GetSafeHwnd() )
	{
		mv_combo_rect.right															= _Btn_rect.left - ( 10 );
		mv_combo_rect.left															= mv_combo_rect.right - ( nComboWidth * 2 );
		m_FLAppExe_ComboRect														= mv_combo_rect;
		m_Combo_FLApp.MoveWindow( mv_combo_rect );
	}

	if( m_FLOffset_Btn.GetSafeHwnd() )
	{
		_Btn_rect.right																= mv_combo_rect.left - ( 35 );
		_Btn_rect.left																= _Btn_rect.right - ( nBtnWidth );
		m_FLOffset_BtnRect															= _Btn_rect;
		m_FLOffset_Btn.MoveWindow( _Btn_rect );
	}
	if( m_OffsetEdit4.GetSafeHwnd() )
	{
		_Btn_rect.top																+= 6;
		_Btn_rect.right																= _Btn_rect.left - 30;
		_Btn_rect.left																= _Btn_rect.right - nEditWidth;
		_Btn_rect.bottom															-= 4;
		m_OffsetRect4																= _Btn_rect;
		m_OffsetEdit4.MoveWindow( m_OffsetRect4 );
	}
	if( m_OffsetEdit3.GetSafeHwnd() )
	{
		_Btn_rect.right																= _Btn_rect.left - 40;
		_Btn_rect.left																= _Btn_rect.right - nEditWidth;
		m_OffsetRect3																= _Btn_rect;
		m_OffsetEdit3.MoveWindow( m_OffsetRect3 );
	}
	if( m_OffsetEdit2.GetSafeHwnd() )
	{
		_Btn_rect.right																= _Btn_rect.left - 50;
		_Btn_rect.left																= _Btn_rect.right - nEditWidth;
		m_OffsetRect2																= _Btn_rect;
		m_OffsetEdit2.MoveWindow( m_OffsetRect2 );
	}
	if( m_OffsetEdit1.GetSafeHwnd() )
	{
		_Btn_rect.right																= _Btn_rect.left - 40;
		_Btn_rect.left																= _Btn_rect.right - nEditWidth;
		m_OffsetRect1																= _Btn_rect;
		m_OffsetEdit1.MoveWindow( m_OffsetRect1 );
	}

	m_LabelRect																		= _rect;
	m_LabelRect.DeflateRect( CSize( 20, 20 ) );
}

int CMain_LoadFlow_Editor::CalueValuePosition( CLFData* pLFData )
{
	if( pLFData->m_vecLoadValuePt.size() > 0 )
	{
		pLFData->m_vecLoadValuePt.clear();
	}
	pLFData->m_dValueMax															= *max_element( pLFData->m_vecLoadValue.begin(), pLFData->m_vecLoadValue.end() );
	pLFData->m_dValueMin															= *min_element( pLFData->m_vecLoadValue.begin(), pLFData->m_vecLoadValue.end() );

	int							nViewWidthMargin( int( (double)pLFData->m_ViewRect.Width() * 0.02 ) );
	int							nViewHeightMargin( int( (double)pLFData->m_ViewRect.Height() * 0.02 ) );

	pLFData->m_nValueMaxLimit														= (UINT)( (double)pLFData->m_dValueMax + abs( (double)pLFData->m_dValueMax - (double)pLFData->m_dValueMin ) * 0.1 );
	pLFData->m_nValueMinLimit														= (UINT)( (double)pLFData->m_dValueMin - abs( (double)pLFData->m_dValueMax - (double)pLFData->m_dValueMin ) * 0.1 );

	if( pLFData->m_nValueMaxLimit > 14000 )
	{
		pLFData->m_nValueMaxLimit													= 14000;
	}
	if( pLFData->m_nValueMinLimit < 0 )
	{
		pLFData->m_nValueMinLimit													= 0;
	}

	if( abs( (double)pLFData->m_nValueMaxLimit - (double)pLFData->m_nValueMinLimit ) == 0.0 )
	{
		pLFData->m_nValueMaxLimit													= 5000;
	}

	if( (double)( pLFData->m_ViewRect.Height() - ( nViewHeightMargin * 2 ) ) == 0.0 )
	{
		pLFData->m_dDrawRatio														= 0.0;
	} else {
		pLFData->m_dDrawRatio														= (double)( pLFData->m_ViewRect.Height() - ( nViewHeightMargin * 2 ) ) / abs( (double)pLFData->m_nValueMaxLimit - (double)pLFData->m_nValueMinLimit );
	}
	CPoint						_drawPt( 0, 0 );

	int							i( 0 );
	for( i = 0 ; i < 96 ; i++ )
	{
		_drawPt.x																	= pLFData->m_ViewRect.left + ( i + 1 ) * 50;
		_drawPt.y																	= pLFData->m_ViewRect.bottom - (int)( (double)( pLFData->m_vecLoadValue[ i ] - pLFData->m_nValueMinLimit ) * pLFData->m_dDrawRatio );
		pLFData->m_vecLoadValuePt.push_back( _drawPt );

		if( pLFData->m_dValueMax == pLFData->m_vecLoadValue[ i ] )
		{
			pLFData->m_MaxValuePt													= _drawPt;
		}
		if( pLFData->m_dValueMin == pLFData->m_vecLoadValue[ i ] )
		{
			pLFData->m_MinValuePt													= _drawPt;
		}
	}
	return i ;
}

void CMain_LoadFlow_Editor::ViewChageLFData( CLFData* pLFData )
{
	if( !pLFData )																	return ;

	pLFData->m_nScrollPos														= 0;
	pLFData->m_nChangeYposValue													= 0;
	pLFData->m_nSelectIndex														= -1;
	pLFData->m_nMoveSelectIndex													= -1;
	m_nOldMultiSelectIndex														= -1;

	CRect						_rect( 0, 0, 0, 0 );
	GetClientRect( &_rect );
	int							nWidthMargin( int( (double)_rect.Width() * 0.1 ) );
	int							nHeightMargin( int( (double)_rect.Height() * 0.1 ) );

	CalueValuePosition( pLFData );

	SCROLLINFO					p = { 0, };
	GetScrollInfo( SB_HORZ, &p );
	p.cbSize																	= sizeof( SCROLLINFO );
	p.fMask																		= SIF_ALL;
	p.nMin																		= 0;
	p.nMax																		= ( pLFData->m_ViewRect.right + 10 + nWidthMargin ) - _rect.Width();
	p.nPage																		= (UINT)( (double)_rect.Width() * 0.10 );
	p.nPos																		= pLFData->m_nScrollPos;
	p.nTrackPos																	= 0;
	SetScrollInfo( SB_HORZ, &p );
}

void CMain_LoadFlow_Editor::SetView()
{
	SetSSDL_ComboBox();
}

void CMain_LoadFlow_Editor::CalcuCoordinates()
{
	//
}

void CMain_LoadFlow_Editor::ViewEmptyData( CDC* pDC )
{
	CRect						_rect( 0, 0, 0, 0 );
	GetClientRect( &_rect );

	int							nWidthMargin( int( (double)_rect.Width() * 0.1 ) );
	int							nHeightMargin( int( (double)_rect.Height() * 0.1 ) );

	_rect.DeflateRect( CSize( nWidthMargin, nHeightMargin ) );

	CPen								pen, *pOldpen;
	CBrush								brush, *pOldbrush;
	pen.CreatePen( PS_SOLID, 3, RGB( 225, 32, 32 ) );
	pOldpen																			= pDC->SelectObject( &pen );
	pOldbrush																		= (CBrush*)pDC->SelectStockObject( NULL_BRUSH );
	CFont						_font, *pOldFont;
	_font.CreateFont( 30, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔고딕"));
	pOldFont																		= pDC->SelectObject( &_font );

	pDC->SetTextColor( RGB( 225, 96, 96 ) );
	pDC->DrawText( _T("No Data"), _rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	pDC->Rectangle( _rect );

	pDC->SelectObject(pOldFont);
	_font.DeleteObject();
	pDC->SelectObject( pOldbrush );
	brush.DeleteObject();
	pDC->SelectObject( pOldpen );
	pen.DeleteObject();
}

void CMain_LoadFlow_Editor::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if( !m_pLFData )																			return CWnd::OnHScroll(nSBCode, nPos, pScrollBar);

	int					nMin( 0 ), nMax( 0 );
	BOOL				bIsReturn( FALSE );

	GetScrollRange( SB_HORZ, &nMin, &nMax )	;


	SCROLLINFO			_ScrollInfor												= { 0, };
	GetScrollInfo( 0, &_ScrollInfor );


	CRect				_rect( 0, 0, 0, 0 );
	GetClientRect( &_rect );


	if( nSBCode == SB_PAGEUP )
	{
		m_pLFData->m_nScrollPos														-= 250;
		if( m_pLFData->m_nScrollPos <= 0)
			m_pLFData->m_nScrollPos													= 0;

		SetScrollPos( SB_HORZ, m_pLFData->m_nScrollPos );
		bIsReturn																	= TRUE;
	} else if( nSBCode == SB_LINEUP )
	{
		m_pLFData->m_nScrollPos														-= 50;
		if( m_pLFData->m_nScrollPos <= 0)
			m_pLFData->m_nScrollPos													= 0;

		SetScrollPos( SB_HORZ, m_pLFData->m_nScrollPos );
		bIsReturn																	= TRUE;
	} else if( nSBCode == SB_PAGEDOWN )
	{
		m_pLFData->m_nScrollPos														+= 250;
		if( m_pLFData->m_nScrollPos > ( nMax - (int)_ScrollInfor.nPage + 1 ) )
		{
			m_pLFData->m_nScrollPos													= ( nMax - (int)_ScrollInfor.nPage + 1 );
		}

		SetScrollPos( SB_HORZ, m_pLFData->m_nScrollPos );
		bIsReturn																	= TRUE;
	} else if( nSBCode == SB_LINEDOWN )
	{
		m_pLFData->m_nScrollPos														+= 50;
		if( m_pLFData->m_nScrollPos > ( nMax - (int)_ScrollInfor.nPage + 1 ) )
		{
			m_pLFData->m_nScrollPos													= ( nMax - (int)_ScrollInfor.nPage + 1 );
		}
		SetScrollPos( SB_HORZ, m_pLFData->m_nScrollPos );
		bIsReturn																	= TRUE;
	}	
	if( nSBCode == SB_ENDSCROLL )
	{
		if( m_pLFData->m_nScrollPos <= 0)
			m_pLFData->m_nScrollPos													= 0;

		bIsReturn																	= TRUE;
	}
	if( nSBCode == SB_THUMBPOSITION )
	{
// 		if( nPos >= (UINT)nMax )
// 			nPos																	+= 100;
		SetScrollPos( SB_HORZ ,nPos );	
		m_pLFData->m_nScrollPos														= nPos;			// - (nPos%50) ;
	}
	if( nSBCode == SB_THUMBTRACK )
	{
		SetScrollPos( SB_HORZ ,nPos );
		m_pLFData->m_nScrollPos														= nPos;			// - (nPos%50) ;
	}

	DrawInvalidate();

	if( bIsReturn )
	{
		return ;
	}

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMain_LoadFlow_Editor::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( !m_pLFData )																			return CWnd::OnLButtonDown(nFlags, point);

	SetCapture();

	CPoint						_checkpt( point.x + m_pLFData->m_nScrollPos, point.y );
	CRect						_YSideViewTextRect( 0, 0, 0, 0 );
	bool						bClickObj( false );

	int							i( 0 ), j( 0 ), nStartIdx( 0 ), nEndIdx( 0 );
	for( i = 0 ; i < 96 ; i++ )
	{
		_YSideViewTextRect																		= CRect( m_pLFData->m_vecLoadValuePt[ i ], m_pLFData->m_vecLoadValuePt[ i ] );
		_YSideViewTextRect.InflateRect( CSize( 10, 10 ) );

		if( _YSideViewTextRect.PtInRect( _checkpt ) )
		{
			if( !bClickObj )
			{
				bClickObj																		= true;
			}
			
			if( m_nCtrlKey == VK_LCONTROL )
			{
				if( m_nShiftKey == VK_LSHIFT && m_nOldMultiSelectIndex > 0 )
				{
					if( m_nOldMultiSelectIndex <= i )
					{
						nStartIdx																= m_nOldMultiSelectIndex;
						nEndIdx																	= i;
					} else {
						nStartIdx																= i;
						nEndIdx																	= m_nOldMultiSelectIndex;
					}

					for( j = nStartIdx ; j <= nEndIdx ; j++ )
					{
						m_pLFData->m_nMultiSelectIndex[ j ]										= VIEWLB_CLICK;
					}
				} else {
					if( m_pLFData->m_nMultiSelectIndex[ i ] == VIEWLB_CLICK )
					{
						m_pLFData->m_nMultiSelectIndex[ i ]										= VIEWLB_UNCLICK;
					} else {
						m_pLFData->m_nMultiSelectIndex[ i ]										= VIEWLB_CLICK;
					}
				}
				m_nOldMultiSelectIndex															= i;
			} else {
				m_pLFData->m_nSelectIndex														= i;
				m_pLFData->m_nChangeYposValue													= point.y;
				if( m_pLFData->m_nMultiSelectIndex[ i ] == VIEWLB_UNCLICK )
				{
					for( j = 0 ; j < 96 ; j++ )
					{
						m_pLFData->m_nMultiSelectIndex[ j ]										= VIEWLB_UNCLICK;
					}
				}
			}

			DrawInvalidate();
			break;
		}
	}
	if( !bClickObj )
	{
		bool						bUpdate( false );
		for( i = 0 ; i < 96 ; i++ )
		{
			if( m_pLFData->m_nMultiSelectIndex[ i ] == VIEWLB_CLICK )
			{
				if( !bUpdate )
				{
					bUpdate																		= true;
				}
			}
			m_pLFData->m_nMultiSelectIndex[ i ]													= VIEWLB_UNCLICK;
		}
		if( bUpdate )
		{
			DrawInvalidate();
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CMain_LoadFlow_Editor::OnLButtonUp(UINT nFlags, CPoint point)
{
	if( !m_pLFData )																			return CWnd::OnLButtonUp(nFlags, point);

	int							i( 0 );
	m_pLFData->m_nSelectIndex															= -1;
	m_pLFData->m_nChangeYposValue														= 0;
	m_pLFData->m_nMoveSelectIndex														= -1;
	CalueValuePosition( m_pLFData );

	CPoint						_checkpt( point.x + m_pLFData->m_nScrollPos, point.y );
	CRect						_YSideViewTextRect( 0, 0, 0, 0 ), _tempRect( _YSideViewTextRect );
	for( i = 0 ; i < 96 ; i++ )
	{
		_YSideViewTextRect															= CRect( m_pLFData->m_vecLoadValuePt[ i ], m_pLFData->m_vecLoadValuePt[ i ] );
		_YSideViewTextRect.InflateRect( CSize( 10, 10 ) );
		if( _YSideViewTextRect.PtInRect( _checkpt ) )
		{
			if( m_pLFData->m_nMoveSelectIndex != i )
			{
				m_pLFData->m_nMoveSelectIndex										= i;
				break;
			}
		}
	}
	DrawInvalidate();

	ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}

void CMain_LoadFlow_Editor::OnMouseMove(UINT nFlags, CPoint point)
{
	if( !m_pLFData )																			return CWnd::OnMouseMove(nFlags, point);

	int							i( 0 );
	if( m_pLFData->m_nSelectIndex > -1 )
	{
		CPoint						_drawCheckPt( point );

		if( _drawCheckPt.y < m_pLFData->m_ViewRect.top )
		{
			_drawCheckPt.y															= m_pLFData->m_ViewRect.top;
		} else if( _drawCheckPt.y > m_pLFData->m_ViewRect.bottom )
		{
			_drawCheckPt.y															= m_pLFData->m_ViewRect.bottom;
		}

		int							nChangeYpos( _drawCheckPt.y - m_pLFData->m_vecLoadValuePt[ m_pLFData->m_nSelectIndex ].y );
		double						dLoadValue( ( (double)( m_pLFData->m_ViewRect.bottom - point.y ) / m_pLFData->m_dDrawRatio ) + (double)m_pLFData->m_nValueMinLimit ), dChangeLoad( dLoadValue - m_pLFData->m_vecLoadValue[ m_pLFData->m_nSelectIndex ] );

// 		m_pLFData->m_vecLoadValuePt[ m_pLFData->m_nSelectIndex ].y					= _drawCheckPt.y;
// 		m_pLFData->m_vecLoadValue[ m_pLFData->m_nSelectIndex ]						= ( (double)( m_pLFData->m_ViewRect.bottom - point.y ) / m_pLFData->m_dDrawRatio ) + (double)m_pLFData->m_nValueMinLimit;
		m_pLFData->m_vecLoadValuePt[ m_pLFData->m_nSelectIndex ].y					= _drawCheckPt.y;
		m_pLFData->m_vecLoadValue[ m_pLFData->m_nSelectIndex ]						= dLoadValue;

		if( m_pLFData->m_vecLoadValue[ m_pLFData->m_nSelectIndex ] < 0.0 )
		{
			m_pLFData->m_vecLoadValue[ m_pLFData->m_nSelectIndex ]					= 0.0;
		}
		if( m_pLFData->m_vecLoadValue[ m_pLFData->m_nSelectIndex ] > 14000.0 )
		{
			m_pLFData->m_vecLoadValue[ m_pLFData->m_nSelectIndex ]					= 14000.0;
		}

		if( m_pLFData->m_nMultiSelectIndex[ m_pLFData->m_nSelectIndex ] == VIEWLB_CLICK )
		{
			for( i = 0 ; i < 96 ; i++ )
			{
				if( m_pLFData->m_nSelectIndex != i && m_pLFData->m_nMultiSelectIndex[ i ] == VIEWLB_CLICK )
				{
					m_pLFData->m_vecLoadValuePt[ i ].y								+= nChangeYpos;
					m_pLFData->m_vecLoadValue[ i ]									+= dChangeLoad;

					if( m_pLFData->m_vecLoadValue[ i ] < 0.0 )
					{
						m_pLFData->m_vecLoadValue[ i ]								= 0.0;
					}
					if( m_pLFData->m_vecLoadValue[ i ] > 14000.0 )
					{
						m_pLFData->m_vecLoadValue[ i ]								= 14000.0;
					}
				}
			}
		}

		DrawInvalidate();
	} else {
		CPoint						_checkpt( point.x + m_pLFData->m_nScrollPos, point.y );
		CRect						_YSideViewTextRect( 0, 0, 0, 0 ), _tempRect( _YSideViewTextRect );

		for( i = 0 ; i < 96 ; i++ )
		{
			_YSideViewTextRect														= CRect( m_pLFData->m_vecLoadValuePt[ i ], m_pLFData->m_vecLoadValuePt[ i ] );
			_YSideViewTextRect.InflateRect( CSize( 10, 10 ) );
			if( _YSideViewTextRect.PtInRect( _checkpt ) )
			{
				if( m_pLFData->m_nMoveSelectIndex != i )
				{
					m_pLFData->m_nMoveSelectIndex									= i;
					DrawInvalidate();
				}
				return CWnd::OnMouseMove(nFlags, point);
			}
		}
		if( m_pLFData->m_nMoveSelectIndex > -1 )
		{
			m_pLFData->m_nMoveSelectIndex											= -1;
			DrawInvalidate();
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CMain_LoadFlow_Editor::DrawInvalidate()
{
	if( !m_pLFData )																			return ;

	CRect				_rect( 0, 0, 0, 0 );
	GetClientRect( &_rect );

	_rect.DeflateRect( CSize( 20, 20 ) );

	_rect.top																		= m_pLFData->m_ViewRect.top - 10;
	_rect.right																		+= 20;
	_rect.bottom																	+= 10;
	InvalidateRect( _rect );
}

void CMain_LoadFlow_Editor::OnSDMSLfeditCombo11SelectChange()
{
	int					nSelectSel			= m_InforCombo1.GetCurSel();
	CString				szValue( _T("") );
	m_InforCombo1.GetLBText( nSelectSel, szValue );
	wstring				szCombo1Name( szValue ), szCombo2Name( _T("") );

	vector<wstring>													vecAddString;
	vector<wstring>::iterator										_str_iter;

	m_InforCombo2.ResetContent();
	theDataMng->GetDLNames( szCombo1Name, &vecAddString );
	for( _str_iter = vecAddString.begin() ; _str_iter != vecAddString.end() ; ++_str_iter )
	{
		m_InforCombo2.AddString( (*_str_iter).c_str() );
	}
	if( vecAddString.begin() != vecAddString.end() )
	{
		_str_iter = vecAddString.begin();
	}
	szCombo2Name																	= vecAddString[ 0 ];
	m_InforCombo2.SetCurSel( 0 );


	m_pLFData																		= GetLFData( szCombo1Name, szCombo2Name, szCombo2Name, 1 );
	if( m_pLFData )
	{
		ViewChageLFData( m_pLFData );
		DrawInvalidate();
	}

	m_InforCombo3.ResetContent();
	m_InforCombo3.AddString( _T("CB Load") );
	m_InforCombo3.AddString( _T("DG Load") );
	m_InforCombo3.SetCurSel( 0 );

	m_InforCombo4.ResetContent();
	m_InforCombo4.AddString( szCombo2Name.c_str() );
	m_InforCombo4.SetCurSel( 0 );
}

void CMain_LoadFlow_Editor::OnSDMSLfeditCombo12SelectChange()
{
	int					nSelectSel			= m_InforCombo1.GetCurSel();
	CString				szValue( _T("") );
	m_InforCombo1.GetLBText( nSelectSel, szValue );
	wstring				szCombo1Name( szValue );

	nSelectSel								= m_InforCombo2.GetCurSel();
	m_InforCombo2.GetLBText( nSelectSel, szValue );
	wstring				szCombo2Name( szValue );

	m_pLFData																		= GetLFData( szCombo1Name, szCombo2Name, szCombo2Name, 1 );
	if( m_pLFData )
	{
		ViewChageLFData( m_pLFData );
		DrawInvalidate();
	}

	m_InforCombo3.ResetContent();
	m_InforCombo3.AddString( _T("CB Load") );
	m_InforCombo3.AddString( _T("DG Load") );
	m_InforCombo3.SetCurSel( 0 );

	m_InforCombo4.ResetContent();
	m_InforCombo4.AddString( szCombo2Name.c_str() );
	m_InforCombo4.SetCurSel( 0 );
}

void CMain_LoadFlow_Editor::OnSDMSLfeditCombo13SelectChange()
{
	int					nSelectSel			= m_InforCombo1.GetCurSel();
	CString				szValue( _T("") );
	m_InforCombo1.GetLBText( nSelectSel, szValue );
	wstring				szCombo1Name( szValue );

	nSelectSel								= m_InforCombo2.GetCurSel();
	m_InforCombo2.GetLBText( nSelectSel, szValue );
	wstring				szCombo2Name( szValue );

	wstring				szCombo3Name( _T("") );
	if( m_InforCombo3.GetCurSel() == 0 )
	{
		szCombo3Name						= szCombo2Name;
		m_InforCombo4.ResetContent();
		m_InforCombo4.AddString( szCombo2Name.c_str() );
		m_InforCombo4.SetCurSel( 0 );
	} else {
		m_InforCombo4.ResetContent();
		vector<CLFData*>::iterator							_iter;
		for( _iter = m_vecLFData.begin() ; _iter != m_vecLFData.end() ; ++_iter )
		{
			if( (*_iter)->m_szSSName == szCombo1Name && (*_iter)->m_szDLName == szCombo2Name && (*_iter)->m_nType == 2 )
			{
				m_InforCombo4.AddString( (*_iter)->m_szGENName.c_str() );
			}
		}
		if( m_InforCombo4.GetCount() > 0 )
		{
			m_InforCombo4.SetCurSel( 0 );
			m_InforCombo4.GetLBText( 0, szValue );
			szCombo3Name						= szValue;
		}
	}

	m_pLFData																		= GetLFData( szCombo1Name, szCombo2Name, szCombo3Name, ( m_InforCombo3.GetCurSel() == 0 ? 1 : 2 ) );
	if( m_pLFData )
	{
		ViewChageLFData( m_pLFData );
		DrawInvalidate();
	}
}

void CMain_LoadFlow_Editor::OnSDMSLfeditCombo14SelectChange()
{
	int					nSelectSel			= m_InforCombo1.GetCurSel();
	CString				szValue( _T("") );
	m_InforCombo1.GetLBText( nSelectSel, szValue );
	wstring				szCombo1Name( szValue );

	nSelectSel								= m_InforCombo2.GetCurSel();
	m_InforCombo2.GetLBText( nSelectSel, szValue );
	wstring				szCombo2Name( szValue );

	nSelectSel								= m_InforCombo4.GetCurSel();
	m_InforCombo4.GetLBText( nSelectSel, szValue );
	wstring				szCombo3Name( szValue );

	m_pLFData																			= GetLFData( szCombo1Name, szCombo2Name, szCombo3Name, ( m_InforCombo3.GetCurSel() == 0 ? 1 : 2 ) );

	if( m_pLFData )
	{
		ViewChageLFData( m_pLFData );
		DrawInvalidate();
	}
}

void CMain_LoadFlow_Editor::OnSDMSLfeditComboFLAppSelectChange()
{
	if( m_Combo_FLApp.GetCount() > 0 )
	{
		m_Combo_FLApp.GetLBText( m_Combo_FLApp.GetCurSel(), m_szBBAppFileName );
		if( m_szBBAppFileName != _T("") )
		{
			GetLFMng()->SetLFFExeFileName( m_szBBAppFileName );
		}
	}
}



void CMain_LoadFlow_Editor::OnSDMSLfeditButton31()
{
	if( !m_pLFData )																	return ;

	CString				szStart( _T("") ), szEnd( _T("") ), szMulti( _T("") ), szAdder( _T("") );
	GetDlgItem( ID_MGLFEDIT_2_1 )->GetWindowText( szStart );
	GetDlgItem( ID_MGLFEDIT_2_2 )->GetWindowText( szEnd );
	GetDlgItem( ID_MGLFEDIT_2_3 )->GetWindowText( szMulti );
	GetDlgItem( ID_MGLFEDIT_2_4 )->GetWindowText( szAdder );

	int					i( 0 );
	for( i = 0 ; i < szStart.GetLength() ; i++ )
	{
		if( iswdigit( szStart.GetAt( i ) ) == 0 )
		{
			return ;
		}
	}
	for( i = 0 ; i < szEnd.GetLength() ; i++ )
	{
		if( iswdigit( szEnd.GetAt( i ) ) == 0 )
		{
			return ;
		}
	}
	for( i = 0 ; i < szMulti.GetLength() ; i++ )
	{
		if( iswdigit( szMulti.GetAt( i ) ) == 0 )
		{
			return ;
		}
	}
	for( i = 0 ; i < szAdder.GetLength() ; i++ )
	{
		if( iswdigit( szAdder.GetAt( i ) ) == 0 )
		{
			return ;
		}
	}

	if( szStart.IsEmpty() || szEnd.IsEmpty() || szMulti.IsEmpty() )						return ;

	int					nStartIdx( _wtoi( szStart ) - 1 ), nEndIdx( _wtoi( szEnd ) - 1 ), nTempIdx( 0 );

	if( nStartIdx > nEndIdx )
	{
		nTempIdx																		= nStartIdx;
		nStartIdx																		= nEndIdx;
		nEndIdx																			= nTempIdx;
	}
	if( nStartIdx < 0 || nEndIdx >= 96 )
	{
		return ;
	}

	double				dMulti( _wtof( szMulti ) ), dAdder( _wtof( szAdder ) );

	for( i = nStartIdx ; i <= nEndIdx ; i++ )
	{
		m_pLFData->m_vecLoadValue[ i ]													= m_pLFData->m_vecLoadValue[ i ] * dMulti + dAdder;
	}
	CalueValuePosition( m_pLFData );

	m_nOffsetFocus																		= -1;

	DrawInvalidate();
}

void CMain_LoadFlow_Editor::OnSDMSLfeditButton32()
{
	BeginWaitCursor();

	Writing_VMLFInfor();

	Writing_VMLFInfor_File();

	EndWaitCursor();
}

void CMain_LoadFlow_Editor::OnSDMSLfeditButton33()
{
	GetLFMng()->SetLoadFlowWnd( this );
	GetLFMng()->Start_LoadFlow();
}

void CMain_LoadFlow_Editor::OnSDMSLfeditButton34()
{
	GetLFMng()->Stop_LoadFlow();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CMain_LoadFlow_Editor::Loading_VMLFInfor()
{
	if( m_vecLFData.size() > 0 )
	{
		for_each( m_vecLFData.begin(), m_vecLFData.end(), PNOVR_EraseObjData() );
		m_vecLFData.clear();
	}

	unsigned int		nLFDataSize( 0 );
	char*				pRtBuff															= NULL;

	pRtBuff																				= GetLFMng()->LoadVMemory_LFInfor( nLFDataSize );

	int					i( 0 ), j( 0 ), nGetDataPos( 0 ), nDataCount( 0 );
	CVMLFData			readLFinfor;
	for( i = 0 ; i < (int)( nLFDataSize/ sizeof( CVMLFData ) ) ; i++ )
	{
		memset( &readLFinfor, 0x00, sizeof( CVMLFData ) );
		memcpy( &readLFinfor, pRtBuff + nGetDataPos, sizeof( CVMLFData ) );

		CLFData*					pLFData										= new CLFData;
		pLFData->m_nIdx															= nDataCount++;
		pLFData->m_szSSName														= readLFinfor.m_szSSName;
		pLFData->m_szDLName														= readLFinfor.m_szDLName;
		pLFData->m_szGENName													= readLFinfor.m_szGENName;
		pLFData->m_nType														= readLFinfor.m_nType;
		for( j = 0 ; j < 96 ; j++ )
		{
			pLFData->m_vecLoadValue[ j ]										= readLFinfor.m_dLoadValue[ j ];
		}

		m_vecLFData.push_back( pLFData );

		nGetDataPos																		+= sizeof( CVMLFData );
	}
	delete pRtBuff;
	pRtBuff																				= NULL;
}

void CMain_LoadFlow_Editor::Writing_VMLFInfor()
{
	int					nTotalSize(GetLFMng()->GetClassSize() + ( (int)m_vecLFData.size() * sizeof( CVMLFData ) ) );
	int					nGetDataPos( 0 );

	char*				pRtBuff															= new char[ nTotalSize ];
	memset( pRtBuff, 0x00, nTotalSize );

	memcpy( pRtBuff, &nTotalSize, GetLFMng()->GetClassSize() );
	nGetDataPos																			= GetLFMng()->GetClassSize();
	for( int i = 0 ; i < (int)m_vecLFData.size() ; i++ )
	{
		CVMLFData		writeLFinfor( m_vecLFData[ i ] );
		memcpy( pRtBuff + nGetDataPos, &writeLFinfor, sizeof( CVMLFData ) );
		nGetDataPos																		+= sizeof( CVMLFData );
	}

	GetLFMng()->WriteVMemory_LFInfor( nTotalSize, pRtBuff );

	delete pRtBuff;
	pRtBuff																				= NULL;
}

void CMain_LoadFlow_Editor::KeyDown( MSG* pMsg )
{
	if( GetKeyState( VK_ESCAPE ) < 0 )
	{
		int							i( 0 );
		if( m_pLFData )
		{
			for( i = 0 ; i < 64 ; i++ )
			{
				m_pLFData->m_nMultiSelectIndex[ i ] 									= VIEWLB_UNCLICK;
			}

			m_pLFData->m_nSelectIndex													= -1;
			m_pLFData->m_nChangeYposValue												= 0;
			m_pLFData->m_nMoveSelectIndex												= -1;
			m_nOldMultiSelectIndex														= -1;
			m_nOffsetFocus																= -1;
			GetDlgItem( ID_MGLFEDIT_3_1 )->SetFocus(); 

			DrawInvalidate();
		}
	} else if( GetKeyState( VK_RETURN ) < 0 )
	{
//		SetOffsetCtrlFocus_Return();
	} else if( GetKeyState( VK_TAB ) < 0 )
	{
		SetOffsetCtrlFocus_Tab();
	} else {
		if( GetKeyState( VK_LCONTROL ) < 0 )
		{
			m_nCtrlKey																	= VK_LCONTROL;
			if( GetKeyState( 65 ) < 0 || GetKeyState( 97 ) < 0 )
			{
				CheckRnageMultiSelect( 0, 96 );
			}
		}
		if( GetKeyState( VK_LSHIFT ) < 0 )
		{
			m_nShiftKey																	= VK_LSHIFT;
		}
	}
}

void CMain_LoadFlow_Editor::KeyUp( MSG* pMsg )
{
	if( !( GetKeyState( VK_LCONTROL ) < 0 ) )
	{
		m_nCtrlKey																		= 0;
	}
	if( !( GetKeyState( VK_LSHIFT ) < 0 ) )
	{
		m_nShiftKey																		= 0;
	}
}

void CMain_LoadFlow_Editor::CheckRnageMultiSelect( int nStart, int nEnd )
{
	BOOL						bCheckUnClick( FALSE );
	int							i( 0 );
	for( i = nStart ; i < nEnd ; i++ )
	{
		if( m_pLFData && m_pLFData->m_nMultiSelectIndex[ i ] == VIEWLB_UNCLICK )
		{
			bCheckUnClick																= TRUE;
			break ;
		}
	}
	if( bCheckUnClick )
	{
		for( i = nStart ; i < nEnd ; i++ )
		{
			m_pLFData->m_nMultiSelectIndex[ i ]											= VIEWLB_CLICK;
		}
	} else {
		for( i = nStart ; i < nEnd ; i++ )
		{
			m_pLFData->m_nMultiSelectIndex[ i ]											= VIEWLB_UNCLICK;
		}
	}
	DrawInvalidate();
}

void CMain_LoadFlow_Editor::SetOffsetCtrlFocus()
{
	for( UINT i = ID_MGLFEDIT_2_1 ; i <= ID_MGLFEDIT_2_4 ; i++ )
	{
		GetDlgItem( i )->SendMessage( WM_COMMAND, WM_KILLFOCUS );
	}

	if( m_nOffsetFocus < 0 || m_nOffsetFocus > ID_MGLFEDIT_2_4 - ID_MGLFEDIT_2_1 )							return ;

	GetDlgItem( ID_MGLFEDIT_2_1 + m_nOffsetFocus )->SetFocus();
}

void CMain_LoadFlow_Editor::SetOffsetCtrlFocus_Return()
{
	if( m_nOffsetFocus == -1 )
	{
		m_nOffsetFocus																	= 0;
		SetOffsetCtrlFocus();
	} else {
		m_nOffsetFocus																	= -1;
		for( UINT i = ID_MGLFEDIT_2_1 ; i <= ID_MGLFEDIT_2_4 ; i++ )
		{
			GetDlgItem( i )->SendMessage( WM_COMMAND, WM_KILLFOCUS );
		}
	}
}

void CMain_LoadFlow_Editor::SetOffsetCtrlFocus_Tab()
{
	if( m_nOffsetFocus == -1 )
	{
		m_nOffsetFocus																	= 0;
	} else {
		++m_nOffsetFocus;
	}
	if( m_nOffsetFocus > ID_MGLFEDIT_2_4 - ID_MGLFEDIT_2_1 )
	{
		m_nOffsetFocus																	= 0;
	}
	SetOffsetCtrlFocus();
}


LRESULT CMain_LoadFlow_Editor::OnSendMsgEditReturn( WPARAM wParam, LPARAM lParam )
{
	return S_OK;
}

void CMain_LoadFlow_Editor::Writing_VMLFInfor_File()
{
	int								i( 0 ), j( 0 );
	wchar_t							setData[ 4096 ]												= { 0, };
	_tstring						szCSVFileData( _T("") );
	CUtil_FileParsing_CSV			CSVFile( _T("Scada_Data"), _T("lffdata.csv") );

	CSVFile.SetString_Header( _T("S/S,D/L,Dev_Name,Type,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96") );
	for( i = 0 ; i < (int)( m_vecLFData.size() ) ; i++ )
	{
		memset( setData, 0x00, sizeof( setData ) );
		swprintf_s( setData, _T("%s,%s,%s,%d"), m_vecLFData[ i ]->m_szSSName.c_str(), m_vecLFData[ i ]->m_szDLName.c_str(), m_vecLFData[ i ]->m_szGENName.c_str(), m_vecLFData[ i ]->m_nType );
		szCSVFileData																			= setData;
		for( j = 0 ; j < 96 ; j++ )
		{
			memset( setData, 0x00, sizeof( setData ) );
			swprintf_s( setData, _T(",%.02f"), m_vecLFData[ i ]->m_vecLoadValue[ j ] );
			szCSVFileData																		+= setData;
		}
		CSVFile.SetString_Content( (wchar_t*)( szCSVFileData.c_str() ) );
	}

	CSVFile.Writing();
}


LRESULT CMain_LoadFlow_Editor::OnSendMsg2LoadFlow( WPARAM wParam, LPARAM lParam )
{
	if( (int)wParam == 1 )
	{
		if( (int)lParam == 1 )
		{
			if( m_FLAppStart_Btn.GetSafeHwnd() )
			{
				m_FLAppStart_Btn.SetWindowText( _T("Running...") );
				m_FLAppStart_Btn.EnableWindow( FALSE );
			}
			if( m_FLAppStop_Btn.GetSafeHwnd() )
			{
				m_FLAppStop_Btn.EnableWindow( TRUE );
			}
		} else if( (int)lParam == 2 )
		{
			if( m_FLAppStart_Btn.GetSafeHwnd() )
			{
				m_FLAppStart_Btn.SetWindowText( _T("Run") );
				m_FLAppStart_Btn.EnableWindow( TRUE );
			}
			if( m_FLAppStop_Btn.GetSafeHwnd() )
			{
				m_FLAppStop_Btn.EnableWindow( FALSE );
			}
		}
	}

	return S_OK;
}
