#pragma once

#include "excel9.h"

class AFX_EXT_CLASS CXLSAutomation
{
public:
	CXLSAutomation(void);
	~CXLSAutomation(void);

public:
	int					GetPageSize();
	void				SetRange( CString szCol, int nRow );
	void				SetRange( int nCol, int nRow );
	void				SetRange( CString szCol_S, int nRow_S, CString szCol_E, int nRow_E );
	void				SetRange( int nCol_S, int nRow_S, int nCol_E, int nRow_E );
	void				AddSheet( CString szSheetName );
	void				SetActiveSheet(short nIdxSheet);
	void				SetSheetName(short nIdxSheet, CString szSheetName);
	void				SetValue( CString szCol, long lRow, CString szValue );
	void 				SetValue( long lCol, long lRow, CString szValue );
	void				SetValue( CString szValue );
	void				SetValue( long lCol, long lRow, long lValue );
	void				SetValue( long lValue );
	void				SetValue(long lCol, long lRow, double dValue, int nDecimal);
	void				SetValue( double dValue, int nDecimal );
	void				SetMergeValue( CString szCol1, long lRow1, CString szCol2, long lRow2, CString szValue, long lHalign = xlAlignHCenter );
	void				SetMergeValue( long lCol1, long lRow1, long lCol2, long lRow2, CString szValue, long lHalign = xlAlignHCenter );
	void				SetValueWithComma( long lCol, long lRow, long lValue );
	void				SetValueWithComma( long lValue );
	void				SetValueWithComma( long lCol, long lRow, double dValue, int nDecimal );
	void				SetValueWithComma( double dValue );
	void				SetValueWithComma( double dValue, int nDecimal );
	void				SetValueWithPercent( long lCol, long lRow, double dValue );
	void				SetValueWithPercent( double dValue );
	void				SetValueWithPercent( long lCol, long lRow, double dValue, int nDecimal );
	void				SetValueWithPercent( double dValue, int nDecimal );
	void				SetColWidth( long lCol, double width );
	void				SetColWidth( long lCol1, long lCol2, double lWidth );
	void				SetRowHeight( long lRow, long lHeight );
	void				SetRowHeight( long lRow1, long lRow2, long lHeight );
	void				SetTextColor( long lCol1, long lRow1, long lCol2, long lRow2, long lColor );
	void				SetTextColor( long lCol, long lRow, long lColor );
	void				SetTextColor( long lColor );
	void				SetBkColor( long lCol1, long lRow1, long lCol2, long lRow2, long lColor );
	void				SetBkColor( long lCol, long lRow, long lColor );
	void				SetBkColor( long lColor );
	void				SetFont( long lCol1, long lRow1, long lCol2, long lRow2, CString szXFontName, long lSize, bool bBold = false );
	void				SetFont( long lCol, long lRow, CString szXFontName, long lSize, bool bBold = false );
	void				SetFont( CString szXFontName, long lSize, bool bBold = false );
	void				SetFontUnderLine( long lStyle = xlLineNone );
	void				SetFontItalic( bool bItalic = false );
	void				SetFontBold( bool bBold = false );
	void				SetTextAlign( long lHalign = xlAlignHLeft, long lValign = xlAlignVCenter );
	void				SetTextHAlign( long lHalign = xlAlignHLeft );
	void				SetTextVAlign( long lValign = xlAlignVCenter );
	void				SetWrapText( bool bWrap = false );
	void				SetMergeCell( long lCol1, long lRow1, long lCol2, long lRow2, bool bMerge = false );
	void				SetMergeCell( bool bMerge = false );
	void				AutoFitColumn( CString szCol );
	void				AutoFitColumn( long lCol );
	void				AutoFitColumn( long lCol1, long lCol2 );
	void				SetFormula( long lCol, long lRow, CString szFormula );
	void				SetLineStyle( long pType );
	void				SetLineWeight( long pWeight );
	void				SetLineColor( long lColor );
	void				SetLineEdge( long lEdge );
	void				SetOutlineEdge( int nCol_S, int nRow_S, int nCol_E, int nRow_E );
	void				AddImage( int nIdxSheet, CString szImagepath, int nCol, int nRow, int nWidth = 0, int nHeight = 0 );

	void				GetCellPosXY(int nCol, int nRow,double* dx, double* dy);

public:
	enum { xlTextUnderLineNone = -4142, xlTextUnderLineSingle = 4, xlTextUnderLineDouble };
	enum { xlAlignHLeft = 1, xlAlignHCenter = -4108, xlAlignHRight = -4152 };
	enum { xlAlignVTop = -4160, xlAlignVCenter = -4108, xlAlignVBottom = -4107 };
	enum { xlLineDiagonalDown = 5, xlLineDiagonalUp, xlLineLeft, xlLineTop, xlLineBottom, xlLineRight, xlLineInsideVertical, xlLineInsideHorizontal, xlLineNone = -4142 };
	enum { xlThin = 2, xlMedium = -4138, xlThick = 4 };
	enum { xlLineStyle_Continuous = 1, xlLineStyle_Dot = -4118, xlLineStyle_Dash = -4115, xlLineStyle_Double = -4119, xlLineStyle_None = -4142 };

protected:
	BOOL				StartUp();
	void				EndUp();
	CString				GetCellStr( int nCol, int nRow );
	void				AppInitVariable()
	{
						m_pExApp = NULL;
	}
protected:
	_Application		*m_pExApp;
	Workbooks			m_ExBooks;
	_Workbook			m_ExBook;
	Worksheets			m_ExSheets;
	_Worksheet			m_ExSheet;
	Range				m_ExRange;
	Borders				m_ExBorders;
};

