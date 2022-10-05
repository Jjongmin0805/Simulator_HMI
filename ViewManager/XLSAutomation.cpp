#include "pch.h"
#include "XLSAutomation.h"

CXLSAutomation::CXLSAutomation(void)
{
	AppInitVariable();
	StartUp();
}

CXLSAutomation::~CXLSAutomation(void)
{
	EndUp();
}

BOOL CXLSAutomation::StartUp()
{
	if( m_pExApp )
	{
		EndUp();
	}

	COleVariant		VOptional( (long)DISP_E_PARAMNOTFOUND, VT_ERROR );

	m_pExApp = new _Application;
	if(m_pExApp->CreateDispatch(_T("Excel.Application"))==NULL)
	{
		AfxMessageBox( _T("Could not start Excel.") );
		return FALSE;
	}
	m_ExBooks	= m_pExApp->GetWorkbooks();
	m_ExBook	= m_ExBooks.Add( VOptional );
	m_ExSheets	= m_ExBook.GetWorksheets();
	m_ExSheet	= m_ExSheets.GetItem( COleVariant( (short) 1 ) );

	return TRUE;
}

void CXLSAutomation::EndUp()
{
	if( m_pExApp )
	{
		m_pExApp->SetVisible(TRUE);
		m_pExApp->SetUserControl(TRUE);

		delete m_pExApp;
		m_pExApp = NULL;
	}
}

CString CXLSAutomation::GetCellStr( int nCol, int nRow )
{
	CString strCellPos( _T("") ), strCellPos_First( _T("") ), strCellPos_Second( _T("") );

	if( nCol == 0 || nRow == 0 )				strCellPos;

	int		nMod( 0 ), nValue( 0 );
	if( nCol > 702 )
	{
		return strCellPos;
	} else {
		nMod = nCol;
	}
	if( nMod > 26 )
	{
		nValue = ( nMod / 26 );
		nMod = nCol % 26;
		if( nMod == 0 )
		{
			nValue		-= 1;
			nMod		= 26;
		}

		strCellPos_First.Format( _T("%c"), nValue + 64 );
	} else {
		nMod = nCol;
	}
	strCellPos_Second.Format( _T("%c"), nMod + 64 );
	strCellPos.Format( _T("%s%s%d"), strCellPos_First, strCellPos_Second, nRow );

	return strCellPos;
}

void CXLSAutomation::SetRange( CString szCol, int nRow )
{
	CString szCell( _T("") );
	szCell.Format( _T("%s%d"), szCol.MakeUpper(), nRow );
	m_ExRange		= m_ExSheet.GetRange( COleVariant( szCell ), COleVariant( szCell ) );
	m_ExBorders		= m_ExRange.GetBorders();
}

void CXLSAutomation::SetRange( int nCol, int nRow )
{
	CString szCell = GetCellStr( nCol, nRow );
	m_ExRange		= m_ExSheet.GetRange( COleVariant( szCell ), COleVariant( szCell ) );
	m_ExBorders		= m_ExRange.GetBorders();
}

void CXLSAutomation::SetRange( CString szCol_S, int nRow_S, CString szCol_E, int nRow_E )
{
	CString szCell1( _T("") ), szCell2( _T("") );
	szCell1.Format( _T("%s%d"), szCol_S.MakeUpper(), nRow_S );
	szCell2.Format( _T("%s%d"), szCol_E.MakeUpper(), nRow_E );
	m_ExRange		= m_ExSheet.GetRange( COleVariant( szCell1 ), COleVariant( szCell2 ) );
	m_ExBorders		= m_ExRange.GetBorders();
}

void CXLSAutomation::SetRange( int nCol_S, int nRow_S, int nCol_E, int nRow_E )
{
	CString szCell1 = GetCellStr( nCol_S, nRow_S ), szCell2 = GetCellStr( nCol_E, nRow_E );
	m_ExRange		= m_ExSheet.GetRange( COleVariant( szCell1 ), COleVariant( szCell2 ) );
	m_ExBorders		= m_ExRange.GetBorders();
}

void CXLSAutomation::AddSheet( CString szSheetName )
{
	SetActiveSheet( (short)m_ExSheets.GetCount() );

	COleVariant		varOption( (long)DISP_E_PARAMNOTFOUND, VT_ERROR );
	VARIANT			varValue;

	V_VT      (&varValue) = VT_DISPATCH;
	V_DISPATCH(&varValue) = (LPDISPATCH)m_ExSheet;

	m_ExSheet = m_ExSheets.Add( varOption, varValue, varOption, varOption );
	m_ExSheet.SetName( szSheetName );
}

void CXLSAutomation::SetActiveSheet(short nIdxSheet)
{
	m_ExSheet = m_ExSheets.GetItem( COleVariant( nIdxSheet ) );
	m_ExSheet.Activate();
}

int	CXLSAutomation::GetPageSize()
{
	return m_ExSheets.GetCount();
}

void CXLSAutomation::SetSheetName(short nIdxSheet, CString szSheetName)
{
	m_ExSheet = m_ExSheets.GetItem( COleVariant( nIdxSheet ) );
	m_ExSheet.SetName( szSheetName );
}

void CXLSAutomation::SetValue( CString szCol, long lRow, CString szValue )
{
	SetRange( szCol, lRow );
	SetValue( szValue );
}

void CXLSAutomation::SetValue( long lCol, long lRow, CString szValue )
{
	SetRange( lCol, lRow );
	SetValue( szValue );
}

void CXLSAutomation::SetValue( CString szValue )
{
	m_ExRange.SetNumberFormatLocal( COleVariant( _T("@") ) );
	m_ExRange.SetValue2( COleVariant( szValue ) );	
}

void CXLSAutomation::SetValue( long lCol, long lRow, long lValue )
{
	SetRange( lCol, lRow );
	SetValue( lValue );
}

void CXLSAutomation::SetValue( long lValue )
{
	m_ExRange.SetNumberFormatLocal( COleVariant( _T("0_ ") ) );
	m_ExRange.SetValue2( COleVariant( lValue ) );
}

void CXLSAutomation::SetValue(long lCol, long lRow, double dValue, int nDecimal)
{
	SetRange( lCol, lRow );
	SetValue( dValue, nDecimal );
}

void CXLSAutomation::SetValue( double dValue, int nDecimal )
{
	CString decFormat = _T("0.");
	for( int i = 0; i < nDecimal ; i++ )
	{
		decFormat = decFormat + _T("0");
	}
	decFormat=decFormat + _T("_ ");

	m_ExRange.SetNumberFormatLocal( COleVariant( decFormat ) );
	m_ExRange.SetValue2( COleVariant( dValue ) );
}

void CXLSAutomation::SetMergeValue( CString szCol1, long lRow1, CString szCol2, long lRow2, CString szValue, long lHalign )
{
	SetRange( szCol1, lRow1, szCol2, lRow2 );
	SetMergeCell( true );
	SetValue( szCol1, lRow1, szValue );
	SetTextHAlign( lHalign );
}

void CXLSAutomation::SetMergeValue( long lCol1, long lRow1, long lCol2, long lRow2, CString szValue, long lHalign )
{
	SetMergeCell( lCol1, lRow1, lCol2, lRow2, true );
	SetValue( lCol1, lRow1, szValue );
	SetTextHAlign( lHalign );
}

void CXLSAutomation::SetValueWithComma( long lCol, long lRow, long lValue )
{
	SetRange( lCol, lRow );
	SetValueWithComma( lValue );
}

void CXLSAutomation::SetValueWithComma( long lValue )
{
	m_ExRange.SetNumberFormatLocal( COleVariant( _T("#,##0_ ") ) );
	m_ExRange.SetValue2( COleVariant( lValue ) );
}

void CXLSAutomation::SetValueWithComma( long lCol, long lRow, double dValue, int nDecimal )
{
	SetRange( lCol, lRow );
	SetValueWithComma( dValue, nDecimal );
}

void CXLSAutomation::SetValueWithComma( double dValue )
{
	m_ExRange.SetNumberFormatLocal( COleVariant( _T("#,##0_ ") ) );
	m_ExRange.SetValue2( COleVariant( dValue ) );
}

void CXLSAutomation::SetValueWithComma( double dValue, int nDecimal )
{
	CString decFormat = _T("#,##0.");
	for( int i = 0 ; i < nDecimal ; i++ )
	{
		decFormat = decFormat + _T("0");
	}
	decFormat = decFormat + _T("_ ");

	m_ExRange.SetNumberFormatLocal( COleVariant( decFormat ) );
	m_ExRange.SetValue2( COleVariant( dValue ) );
}

void CXLSAutomation::SetValueWithPercent( long lCol, long lRow, double dValue )
{
	SetRange( lCol, lRow );
	SetValueWithPercent( dValue );
}

void CXLSAutomation::SetValueWithPercent( double dValue )
{
	m_ExRange.SetNumberFormatLocal( COleVariant( _T("0%") ) );
	m_ExRange.SetValue2(COleVariant( dValue ));
}

void CXLSAutomation::SetValueWithPercent( long lCol, long lRow, double dValue, int nDecimal )
{
	SetRange( lCol, lRow );
	SetValueWithPercent( dValue, nDecimal );
}

void CXLSAutomation::SetValueWithPercent( double dValue, int nDecimal )
{
	CString decFormat = _T("0.");
	for( int i = 0 ; i < nDecimal ; i++)
	{
		decFormat = decFormat + _T("0");
	}
	decFormat = decFormat + _T("%");

	m_ExRange.SetNumberFormatLocal( COleVariant( decFormat ) );
	m_ExRange.SetValue2( COleVariant( dValue ) );
}

void CXLSAutomation::GetCellPosXY(int nCol, int nRow, double* dx, double* dy)
{
	CString szCell1 = GetCellStr(nCol, nRow);

	double dW = 0., dH = 0.;
	VARIANT			varValue;

	for (int i = 1; i < nCol; i++)
	{
		szCell1 = GetCellStr(i, 1);
		m_ExRange = m_ExSheet.GetRange(COleVariant(szCell1), COleVariant(szCell1));

		varValue = m_ExRange.GetWidth();
		dW += varValue.dblVal;
	}

	for (int i = 1; i < nRow; i++)
	{
		szCell1 = GetCellStr(1, i);
		m_ExRange = m_ExSheet.GetRange(COleVariant(szCell1), COleVariant(szCell1));

		varValue = m_ExRange.GetHeight();
		dH += varValue.dblVal;
	}


	//m_ExRange = m_ExSheet.GetRange(COleVariant(szCell1), COleVariant(szCell1));

	//m_ExRange.GetColumnWidth();

	*dx = dW;
	*dy = dH;

}

void CXLSAutomation::SetColWidth( long lCol, double width )
{
	SetColWidth( lCol, lCol, width );
}

void CXLSAutomation::SetColWidth( long lCol1, long lCol2, double lWidth )
{
	CString szCell1 = GetCellStr( lCol1, lCol2 );
	CString szCell2 = GetCellStr( lCol2, lCol1 );

	m_ExRange = m_ExSheet.GetRange( COleVariant( szCell1 ), COleVariant( szCell2 ) );
	m_ExRange.SetColumnWidth( COleVariant( lWidth ) );
}

void CXLSAutomation::SetRowHeight( long lRow, long lHeight )
{
	SetRowHeight( lRow, lRow, lHeight );
}

void CXLSAutomation::SetRowHeight( long lRow1, long lRow2, long lHeight )
{
	CString cell1 = _T(""), cell2 = _T("");

	cell1.Format( _T("%d:%d"), lRow1, lRow1 );
	cell2.Format( _T("%d:%d"), lRow2, lRow2 );

	m_ExRange = m_ExSheet.GetRange( COleVariant( cell1 ), COleVariant( cell2 ) );
	m_ExRange.SetRowHeight( COleVariant( lHeight ) );
}

void CXLSAutomation::SetTextColor( long lCol1, long lRow1, long lCol2, long lRow2, long lColor )
{
	SetRange( lCol1, lRow1, lCol2, lRow2 );
	SetTextColor( lColor );
}

void CXLSAutomation::SetTextColor( long lCol, long lRow, long lColor )
{
	SetRange( lCol, lRow );
	SetTextColor( lColor );
}

void CXLSAutomation::SetTextColor( long lColor )
{
	XFont pXFont = m_ExRange.GetXFont();
	pXFont.SetColor( COleVariant( lColor ) );
}

void CXLSAutomation::SetBkColor( long lCol1, long lRow1, long lCol2, long lRow2, long lColor )
{
	SetRange( lCol1, lRow1, lCol2, lRow2 );
	SetBkColor( lColor );
}

void CXLSAutomation::SetBkColor( long lCol, long lRow, long lColor )
{
	SetRange( lCol, lRow );
	SetBkColor( lColor );
}

void CXLSAutomation::SetBkColor( long lColor )
{
	Interior pInterior = m_ExRange.GetInterior();
	pInterior.SetColor( COleVariant( lColor ) );
}

void CXLSAutomation::SetFont( long lCol1, long lRow1, long lCol2, long lRow2, CString szXFontName, long lSize, bool bBold )
{
	SetRange( lCol1, lRow1, lCol2, lRow2 );
	SetFont( szXFontName, lSize, bBold );
}

void CXLSAutomation::SetFont( long lCol, long lRow, CString szXFontName, long lSize, bool bBold )
{
	SetRange( lCol, lRow );
	SetFont( szXFontName, lSize, bBold );
}

void CXLSAutomation::SetFont( CString szXFontName, long lSize, bool bBold )
{
	XFont pXFont = m_ExRange.GetXFont();

	pXFont.SetName( COleVariant( szXFontName ) );
	pXFont.SetSize( COleVariant( lSize ) );
	SetFontBold( bBold );
	SetFontUnderLine();
	SetFontItalic();	
}

void CXLSAutomation::SetFontUnderLine( long lStyle )
{
	switch( lStyle )
	{
		case xlTextUnderLineNone	:
		case xlTextUnderLineSingle	:
		case xlTextUnderLineDouble	:
		case 2L	:
		case 3L	:
										break;
		default:
										return;
		break;
	}
	XFont pXFont = m_ExRange.GetXFont();
	pXFont.SetUnderline( COleVariant( lStyle ) );
}

void CXLSAutomation::SetFontItalic( bool bItalic )
{
	XFont pXFont = m_ExRange.GetXFont();

	if( bItalic == true )	pXFont.SetItalic( COleVariant( (long) 1 ) );
	else					pXFont.SetItalic( COleVariant( (long) 0 ) );
}

void CXLSAutomation::SetFontBold( bool bBold )
{
	XFont pXFont=m_ExRange.GetXFont();

	if( bBold == true )		pXFont.SetBold( COleVariant( (long) 1 ) );
	else					pXFont.SetBold( COleVariant( (long) 0 ) );
}

void CXLSAutomation::SetTextAlign( long lHalign, long lValign )
{
	SetTextHAlign( lHalign );
	SetTextVAlign( lValign );
}

void CXLSAutomation::SetTextHAlign( long lHalign )
{
	switch( lHalign )
	{
		case xlAlignHLeft	: 
		case xlAlignHCenter	:
		case xlAlignHRight	:
								break;
		default				:
								return;
								break;
	}
	m_ExRange.SetHorizontalAlignment( COleVariant( lHalign ) );
}

void CXLSAutomation::SetTextVAlign( long lValign )
{
	switch( lValign ) {
		case xlAlignVTop	:
		case xlAlignVCenter	:
		case xlAlignVBottom	:
								break;
		default:
								return;
								break;
	}
	m_ExRange.SetVerticalAlignment( COleVariant( lValign ) );
}

void CXLSAutomation::SetWrapText( bool bWrap )
{
	if( bWrap == true )		m_ExRange.SetWrapText( COleVariant( (long) 1 ) );
	else					m_ExRange.SetWrapText( COleVariant( (long) 0 ) );
}

void CXLSAutomation::SetMergeCell( long lCol1, long lRow1, long lCol2, long lRow2, bool bMerge )
{
	SetRange( lCol1, lRow1, lCol2, lRow2 );
	SetMergeCell( bMerge );
}

void CXLSAutomation::SetMergeCell( bool bMerge )
{
	if( bMerge == true )
	{
		m_ExRange.SetMergeCells( COleVariant( (long) 1 ) );
	} else {
		m_ExRange.SetMergeCells( COleVariant( (long) 0 ) );
	}
}

void CXLSAutomation::AutoFitColumn( CString szCol )
{
	SetRange( szCol, 1 );
	Range pCols = m_ExRange.GetEntireColumn();
	pCols.AutoFit();
}

void CXLSAutomation::AutoFitColumn( long lCol )
{
	SetRange( lCol, 1 );
	Range pCols = m_ExRange.GetEntireColumn();
	pCols.AutoFit();
}

void CXLSAutomation::AutoFitColumn( long lCol1, long lCol2 )
{
	SetRange( lCol1, 1, lCol2, 1 );
	Range pCols = m_ExRange.GetEntireColumn();
	pCols.AutoFit();
}

void CXLSAutomation::SetFormula( long lCol, long lRow, CString szFormula )
{
	SetRange( lCol, lRow );

	m_ExRange.SetFormula( COleVariant( szFormula ) );
}

void CXLSAutomation::SetLineStyle( long pType )
{
	switch( pType )
	{
		case xlLineStyle_Continuous	: 
		case xlLineStyle_Dot		: 
		case xlLineStyle_Dash		:
		case xlLineStyle_Double		:
		case xlLineStyle_None		:
		case 7		:
										break;
		default:
										ASSERT( 0 );
										break;
	}
	m_ExBorders.SetLineStyle( COleVariant( (long) pType ) );
}

void CXLSAutomation::SetLineWeight( long pWeight )
{
	switch( pWeight )
	{
		case xlThin		:
		case xlMedium	:
		case xlThick	:
							break;
		default			:	
							ASSERT(0);
							break;
	}
	m_ExBorders.SetWeight(COleVariant( (long)pWeight) );
}

void CXLSAutomation::SetLineColor( long lColor )
{
	m_ExBorders.SetColor(COleVariant( (long) lColor )) ;
}

void CXLSAutomation::SetLineEdge( long lEdge )
{
	switch( lEdge )
	{
		case xlLineDiagonalDown			: 
		case xlLineDiagonalUp			:
		case xlLineLeft					: 
		case xlLineTop					: 
		case xlLineBottom				: 
		case xlLineRight				:
		case xlLineInsideVertical		:
		case xlLineInsideHorizontal		:
		case xlLineNone					:
											break;
		default:
											ASSERT(0);
											break;
	}

	m_ExBorders = m_ExBorders.GetItem( lEdge );
}

void CXLSAutomation::SetOutlineEdge( int nCol_S, int nRow_S, int nCol_E, int nRow_E )
{
	CString szCell1 = GetCellStr( nCol_S, nRow_S ), szCell2 = GetCellStr( nCol_E, nRow_E );
	m_ExRange		= m_ExSheet.GetRange( COleVariant( szCell1 ), COleVariant( szCell2 ) );
	m_ExBorders		= m_ExRange.GetBorders();

	

	Border			_bdLeft, _bdTop, _bdRight, _bfBottom;
	_bdLeft			= m_ExBorders.GetItem( (long)xlLineLeft  );				_bdLeft.SetLineStyle( COleVariant( (short)1 ) );
	_bdTop			= m_ExBorders.GetItem( (long)xlLineTop  );				_bdTop.SetLineStyle( COleVariant( (short)1 )  );
	_bdRight		= m_ExBorders.GetItem( (long)xlLineRight );				_bdRight.SetLineStyle( COleVariant( (short)1 ) );
	_bfBottom		= m_ExBorders.GetItem( (long)xlLineBottom  );			_bfBottom.SetLineStyle( COleVariant( (short)1 ) );
	COLORREF	_outlinecolor = RGB( 255, 255, 255 );
	Interior	_outlineinterior = m_ExRange.GetInterior();
	_outlineinterior.SetColor( COleVariant( (double) _outlinecolor ) );
}

void CXLSAutomation::AddImage( int nIdxSheet, CString szImagepath, int nCol, int nRow, int nWidth, int nHeight )
{
	if( nIdxSheet == 0 )					return ;

	int			nImgWidth( nWidth ), nImgHeight( nHeight );

	CImage		viewImage;
	viewImage.Load( szImagepath );
	if( nWidth == 0 || nHeight == 0 )
	{
		//	if( viewImage.Load( szImagepath ) == S_OK )
		{
			nImgWidth			= viewImage.GetWidth();
			nImgHeight			= viewImage.GetHeight();
		}
	}

	m_ExSheet = m_ExSheets.GetItem( COleVariant( (long)nIdxSheet ) );
	m_ExSheet.Activate();

	double dx, dy;
	GetCellPosXY(nCol, nRow, &dx,&dy);

	Shapes		_shapes;
	Shape		_shape;

	_shapes		=m_ExSheet.GetShapes();
	//_shape		= _shapes.AddPicture(szImagepath, (long)0, (long)-1, (float)nCol*55, (float)nRow * 11, (float)nImgWidth, (float)nImgHeight );
	_shape = _shapes.AddPicture(szImagepath, (long)0, (long)-1, (float)dx, (float)dy, (float)nImgWidth, (float)nImgHeight);
	////////////// 셀의 시작 정확히는 실수형
	_shape.SetWidth( (float)nImgWidth );
	_shape.SetHeight( (float)nImgHeight );
	_shape.SetShapesDefaultProperties();
	//	VARIANT sw,sh;
}