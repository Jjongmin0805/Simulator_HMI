// CustMenu.cpp: implementation of the CSkinMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkinMenu.h"

// DrawText flags
const int DT_MYSTANDARD = DT_SINGLELINE | DT_LEFT | DT_VCENTER;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkinMenu, CMenu)

CSkinMenu::CSkinMenu()
{	
	//initialize colors with system default	
	m_clrBackGround   = g_gbl.GetRGB( IDX_RGB_MAIN_BACKGROUND );
	m_clrSelectedBar  = g_gbl.GetRGB( IDX_RGB_FONT_LITE_BLUE );
	m_clrSelectedText = g_gbl.GetRGB( IDX_RGB_FONT_BLACK );
	m_clrText         = g_gbl.GetRGB( IDX_RGB_FONT_BLACK );
	m_clrDisabledText = g_gbl.GetRGB( IDX_RGB_FONT_GRAY );

	//initialize sidebar colors
	m_clrSideBarStart = g_gbl.GetRGB( IDX_RGB_FONT_GRAY2 );
	m_clrSideBarEnd   = g_gbl.GetRGB( IDX_RGB_FONT_WHITE );

	m_bLSidebar = FALSE;
	m_pFont		= NULL;
	m_hBitmapBG = NULL;

	memset( &m_sizeBG, 0x00, sizeof(SIZE) );
}

CSkinMenu::~CSkinMenu()
{	
	Clear();
}


void CSkinMenu::MeasureItem( LPMEASUREITEMSTRUCT lpms )
{
	if ( lpms->CtlType != ODT_MENU )
		return;

	CSkinMenuItem *pItem = (CSkinMenuItem  *)lpms->itemData;	

	if ( !pItem )
		return;

	if ( pItem->m_bSideBar )
	{
		lpms->itemWidth  = pItem->m_nSize;
		lpms->itemHeight = 0;
	}
	else if ( pItem->m_bSeparator )
	{
		// separator: use half system height and zero width
		lpms->itemHeight = ::GetSystemMetrics( SM_CYMENUCHECK ) >> 1;
		lpms->itemWidth  = 0;		
	}
	else
	{
		// calculate the size needed to draw the text: use DrawText with DT_CALCRECT
		CWindowDC dc( NULL );	// screen DC--I won't actually draw on it
		CRect rcText( 0, 0, 0, 0 );
		CFont* pOldFont;		
		pOldFont = dc.SelectObject( m_pFont );
		dc.DrawText( pItem->m_strText, rcText, DT_MYSTANDARD | DT_CALCRECT );
		dc.SelectObject( pOldFont );

		// the height of the item should be the maximun of the text and the button
		lpms->itemHeight = max( rcText.Height(), pItem->m_nSize + (CYBUTTONMARGIN << 1) );

		// width is width of text plus a bunch of stuff
		int cx = rcText.Width();	// text width 
		cx += CXTEXTMARGIN << 1;	// L/R margin for readability
		cx += CXGAP;				// space between button and menu text
		cx += (pItem->m_nSize + CYBUTTONMARGIN * 2) << 1;		// button width (L=button; R=empty margin)

		lpms->itemWidth = cx;		// done deal
	}
	
	// whatever value I return in lpms->itemWidth, Windows will add the
	// width of a menu checkmark, so I must subtract to defeat Windows. Argh.	
	lpms->itemWidth -= GetSystemMetrics( SM_CXMENUCHECK ) - 1;
}

void CSkinMenu::DrawItem( LPDRAWITEMSTRUCT lpds )
{
	ASSERT( lpds );
	if ( lpds->CtlType != ODT_MENU )		return; 
	
	CSkinMenuItem  *pItem = (CSkinMenuItem *)lpds->itemData;
	if ( !pItem )		return;
	
	ASSERT( lpds->itemAction != ODA_FOCUS );
	ASSERT( lpds->hDC );
	CDC dc;
	dc.Attach( lpds->hDC );

	//get the drawing area
	CRect rcItem = lpds->rcItem;

	if( pItem->m_bSideBar )
	{
		CRect rcClipBox;
		dc.GetClipBox( rcClipBox );
		
		//draw the side bar
		CRect rc = rcItem;
		rc.top = rcClipBox.top;
		rc.bottom = rcClipBox.bottom;
		DrawSideBar( &dc, rc, pItem->m_strText );
	}
	else if( pItem->m_bSeparator ) 
	{
		//draw background first
		DrawBackGround( &dc, rcItem, FALSE, FALSE );
		// draw the background
		CRect rc = rcItem;								// copy rect
		rc.top += rc.Height() >> 1;						// vertical center
		dc.DrawEdge( &rc, EDGE_ETCHED, BF_TOP );		// draw separator line
	} 
	else
	{
		BOOL bDisabled = lpds->itemState & ODS_GRAYED;
		BOOL bSelected = lpds->itemState & ODS_SELECTED;
		BOOL bChecked  = lpds->itemState & ODS_CHECKED;

		DrawBackGround( &dc, rcItem, bSelected, bDisabled );
		
		//draw the button
		CRect rcButton( rcItem.TopLeft(), CSize( rcItem.Height(), rcItem.Height() ) );
		if( bChecked )
		{
			DrawButton( &dc, rcButton, bSelected, bDisabled, bChecked );
		}
		if( bChecked )
		{
			//draw the check mark
			CRect	rcCheck = rcButton;
			rcCheck.DeflateRect( 2, 2 );
			DrawCheckMark( &dc, rcCheck, bSelected );
		}

		//draw text finally
		CRect rcText = rcItem;										// start w/whole item
		rcText.left += rcButton.Width() + CXGAP + CXTEXTMARGIN;		// left margin
		rcText.right -= pItem->m_nSize;								// right margin
		DrawText( &dc, rcText, pItem->m_strText, bSelected, bDisabled, lpds->itemState&ODS_DEFAULT ? 1 : 0 );
	}

	dc.Detach();
}

// Draw Background
void CSkinMenu::DrawBackGround( CDC *pDC, CRect rect, BOOL bSelected, BOOL bDisabled )
{
	if( m_hBitmapBG && (!bSelected || bDisabled) )
	{		
		pDC->StretchBlt( rect.left, rect.top,rect.Width(), rect.Height(), &m_memDC, 0, 0, m_sizeBG.cx, m_sizeBG.cy, SRCCOPY );

	}
	else if( bSelected )
	{
		FillRect( pDC, rect, m_clrSelectedBar );
	}
	else
	{
		FillRect( pDC, rect, m_clrBackGround );
	}
}

// Draw the Button
void CSkinMenu::DrawButton( CDC *pDC, CRect rect, BOOL bSelected, BOOL bDisabled, BOOL bChecked )
{
	// normal: fill BG depending on state
	if( bChecked && !bSelected )
	{
		FillRect( pDC, rect, GetSysColor( COLOR_3DHILIGHT ) );
	}
	else
		FillRect( pDC, rect, m_clrBackGround );

	// draw pushed-in or popped-out edge
	if( !bDisabled && (bSelected || bChecked) )
	{
		pDC->DrawEdge( rect, bChecked ? BDR_SUNKENOUTER : BDR_RAISEDINNER, BF_RECT );
	}
}

//draw the sidebar
void CSkinMenu::DrawSideBar( CDC *pDC, CRect rect, CString strText )
{
	rect.right += 3;	// fill the gap produced by the menubreak

	HBITMAP	bmpBar = CreateGradientBMP(	pDC->m_hDC, m_clrSideBarStart, m_clrSideBarEnd,	rect.Width(), rect.Height(), 0, 256 );	
	if( bmpBar )
	{
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		
		HBITMAP hOldBmp = (HBITMAP)::SelectObject( memDC.m_hDC, bmpBar );
		pDC->BitBlt( rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY );
		::SelectObject( memDC, hOldBmp );
		::DeleteObject( bmpBar );
	}

	//Draw Sidebar text	
	CFont *pOldFont = pDC->SelectObject( m_pFont );
	COLORREF oldColor = pDC->GetTextColor();
	pDC->SetTextColor( m_clrText );
	pDC->SetBkMode( TRANSPARENT );
	pDC->TextOut( rect.left + 2, rect.bottom - 4, strText );
	pDC->SetTextColor( oldColor );	
	pDC->SelectObject( pOldFont );
}

//draw the check mark
void CSkinMenu::DrawCheckMark( CDC *pDC, CRect rect, BOOL bSelected )
{
	//Draw it myself :(
	const int nCheckDots = 8;
	CPoint pt1, pt2, pt3;	//3 point of the checkmark
	pt1.x = 0;				// 5/18 of the rect width
	pt1.y = 3;	
	pt2.x = 2;
	pt2.y = 5;
	pt3.x = 7;
	pt3.y = 0;

	int xOff = (rect.Width()-nCheckDots)/2 + rect.left ;
	int yOff = (rect.Height()-nCheckDots)/2 + rect.top;
	pt1.Offset(xOff, yOff);
	pt2.Offset(xOff, yOff);
	pt3.Offset(xOff, yOff);

	CPen	pen( PS_SOLID, 1, RGB(0, 0, 0) );
	CGdiObject *pOldPen = pDC->SelectObject( &pen );
	
	pDC->MoveTo( pt1  );
	pDC->LineTo( pt2  );
	pDC->LineTo( pt3  );
	pt1.Offset ( 0, 1 );
	pt2.Offset ( 0, 1 );
	pt3.Offset ( 0, 1 );
	pDC->MoveTo( pt1  );
	pDC->LineTo( pt2  );
	pDC->LineTo( pt3  );
	pt1.Offset ( 0, 1 );
	pt2.Offset ( 0, 1 );
	pt3.Offset ( 0, 1 );
	pDC->MoveTo( pt1  );
	pDC->LineTo( pt2  );
	pDC->LineTo( pt3  );
	pDC->SelectObject( pOldPen );
}

//Draw menu text
void CSkinMenu::DrawText( CDC *pDC, CRect rect, CString strText, BOOL bSelected, BOOL bDisabled, BOOL bBold )
{
	CFont*	pOldFont;
	CFont	fontBold;

	if( bBold )
	{
		LOGFONT	logFont;
		m_pFont->GetLogFont( &logFont );
		logFont.lfWeight = FW_BOLD;
		fontBold.CreateFontIndirect( &logFont );

		pOldFont = pDC->SelectObject( &fontBold );
	}
	else
	{
		pOldFont = pDC->SelectObject( m_pFont );
	}

	pDC->SetBkMode( TRANSPARENT );
	
	if( bDisabled && !bSelected )
	{
		DrawMenuText( *pDC, rect + CPoint(1, 1), strText, m_clrSelectedText );
	}
	if( bDisabled )
	{
		DrawMenuText( *pDC, rect, strText, m_clrDisabledText );
	}
	else
	{
		DrawMenuText( *pDC, rect, strText, bSelected? m_clrSelectedText : m_clrText );
	}

	pDC->SelectObject( pOldFont );

	if( bBold )
		fontBold.DeleteObject();
}

// Clear all memory and handles
void CSkinMenu::Clear()
{
	UINT	nCount = GetMenuItemCount();	
	for( UINT i = 0; i < nCount; i++ )
	{
		MENUITEMINFO	info;
		memset( &info, 0, sizeof( MENUITEMINFO ) );
		info.cbSize = sizeof( MENUITEMINFO );
		info.fMask  = MIIM_DATA | MIIM_TYPE;
		GetMenuItemInfo( i, &info, TRUE );
		
		CSkinMenuItem *pData = (CSkinMenuItem *)info.dwItemData;
		if ((info.fType & MFT_OWNERDRAW) && pData)
		{
			delete pData;
		}

		CMenu	*pSubMenu = GetSubMenu(i);
		if (pSubMenu && pSubMenu->IsKindOf(RUNTIME_CLASS(CSkinMenu)))
			delete pSubMenu;
	}
}

//////////////////
// Shorthand to fill a rectangle with a solid color.
//
void CSkinMenu::FillRect( CDC *pDC, const CRect& rc, COLORREF color )
{
	CBrush brush(color);
	CBrush* pOldBrush = pDC->SelectObject( &brush );
	pDC->PatBlt( rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY );
	pDC->SelectObject( pOldBrush );
	brush.DeleteObject();
}


HBITMAP CSkinMenu::CreateGradientBMP( HDC hDC,COLORREF cl1,COLORREF cl2,int nWidth,int nHeight,int nDir,int nNumColors )
{
	if(nNumColors > 256)
		nNumColors = 256;

	COLORREF		PalVal[ 256 ];
	memset( PalVal, 0, sizeof(COLORREF) * 256 );

	int nIndex;
	BYTE peRed = 0, peGreen = 0, peBlue = 0;

	int r1 = GetRValue( cl1 );
	int r2 = GetRValue( cl2 );
	int g1 = GetGValue( cl1 );
	int g2 = GetGValue( cl2 );
	int b1 = GetBValue( cl1 );
	int b2 = GetBValue( cl2 );

    for ( nIndex = 0; nIndex < nNumColors; nIndex++ )
    {
        peRed   = (BYTE)( r1 + MulDiv((r2-r1), nIndex, nNumColors - 1) );
        peGreen = (BYTE)( g1 + MulDiv((g2-g1), nIndex, nNumColors - 1) );
        peBlue  = (BYTE)( b1 + MulDiv((b2-b1), nIndex, nNumColors - 1) );

		PalVal[nIndex]=(peRed << 16) | (peGreen << 8) | (peBlue);
	}

	int x,y,w,h;
	w=nWidth;
	h=nHeight;
	
	LPDWORD			pGradBits;
	BITMAPINFO		GradBitInfo;

	pGradBits = (DWORD *) malloc( w * h * sizeof(DWORD) );
	memset( &GradBitInfo, 0, sizeof(BITMAPINFO) );

	GradBitInfo.bmiHeader.biSize=sizeof( BITMAPINFOHEADER );
	GradBitInfo.bmiHeader.biWidth=w;
	GradBitInfo.bmiHeader.biHeight=h;
	GradBitInfo.bmiHeader.biPlanes=1;
	GradBitInfo.bmiHeader.biBitCount=32;
	GradBitInfo.bmiHeader.biCompression=BI_RGB;
	
	if(nDir==0) 
	{
		for(y=0;y<h;y++) 
		{
			for(x=0;x<w;x++) 
			{
				*(pGradBits+(y*w)+x)=PalVal[MulDiv(nNumColors,y,h)];
			}
		}
	}
	else if(nDir==1) 
	{
		for(y=0;y<h;y++)
		{
			int l,r;
			l=MulDiv((nNumColors/2),y,h);
			r=l+(nNumColors/2)-1;
			for(x=0;x<w;x++)
			{
				*(pGradBits+(y*w)+x)=PalVal[l+MulDiv((r-l),x,w)];
			}
		}
	}
	else if(nDir==2)
	{
		for(x=0;x<w;x++)
		{
			for(y=0;y<h;y++)
			{
				*(pGradBits+(y*w)+x)=PalVal[MulDiv(nNumColors,x,w)];
			}
		}
	}
	else if(nDir==3)
	{
		for(y=0;y<h;y++)
		{
			int l,r;
			r=MulDiv((nNumColors/2),y,h);
			l=r+(nNumColors/2)-1;
			for(x=0;x<w;x++)
			{
				*(pGradBits+(y*w)+x)=PalVal[l+MulDiv((r-l),x,w)];
			}
		}
	}

	HBITMAP hBmp = CreateDIBitmap( hDC, &GradBitInfo.bmiHeader, CBM_INIT, pGradBits,&GradBitInfo,DIB_RGB_COLORS );
	free( pGradBits );

	return hBmp;
}

void CSkinMenu::DrawMenuText( CDC& dc, CRect rc, CString text, COLORREF color )
{
	CString left = text;
	CString right;
	
	int iTabPos = left.Find('\t');	
	if( iTabPos >= 0 ) 
	{	
		right = left.Right(left.GetLength() - iTabPos - 1);
		left  = left.Left(iTabPos);
	}

	dc.SetTextColor( color );
	dc.DrawText( left, &rc, DT_MYSTANDARD );
	
	if( iTabPos > 0 )
		dc.DrawText( right, &rc, DT_MYSTANDARD | DT_RIGHT );
}

//Add a gradient sidebar, it must be the first item in a popupmenu
BOOL CSkinMenu::AddSideBar( int nWidth, CString strText )
{
	CSkinMenuSideBar *pItem = new CSkinMenuSideBar(nWidth, strText);

	m_bLSidebar = TRUE;
	return AppendMenu( MF_OWNERDRAW | MF_SEPARATOR, pItem->m_dwID, (LPCTSTR)pItem );
}

//add a normal menuitem, an accelerator key could be specified, and the accel text will
//be added automatically
BOOL CSkinMenu::AppendODMenu( UINT nFlags, DWORD dwID, LPCTSTR strText, ACCEL *pAccel )
{
	CSkinMenuText *pItem = new CSkinMenuText(dwID,  strText);
	nFlags |= MF_OWNERDRAW;

	if( m_bLSidebar ) 
		nFlags |= MF_MENUBREAK;
	
	m_bLSidebar = FALSE;
	return AppendMenu( nFlags, pItem->m_dwID, (LPCTSTR)pItem );
}

//Add a separator line
BOOL CSkinMenu::AppendSeparator(void)	
{
	m_bLSidebar = FALSE;

	CSkinMenuSeparator *pItem = new CSkinMenuSeparator;
	return AppendMenu( MF_OWNERDRAW | MF_SEPARATOR, 0, (LPCTSTR)pItem );
}

//add a popup menu
BOOL CSkinMenu::AppendODPopup( UINT nFlags, CSkinMenu *pPopup, DWORD dwID, LPCTSTR strText )
{
	ASSERT(pPopup);
	CSkinMenuText *pItem = new CSkinMenuText(dwID,  strText);

	nFlags |= MF_OWNERDRAW;
	nFlags |= MF_POPUP;
	
	if ( m_bLSidebar ) 
		nFlags |= MF_MENUBREAK;
	
	m_bLSidebar = FALSE;
	return AppendMenu( nFlags, (UINT)pPopup->m_hMenu, (LPCTSTR)pItem );
}

void CSkinMenu::SetBitmapID( UINT uBaseImage )
{
	// 각 비트맵의 사이즈 정보를 얻어온다.
	m_sizeBG = g_gbl.GetBitmapSize( uBaseImage );

	// 각 비트맵의 핸들을 얻어온다.
	m_hBitmapBG = g_gbl.GetBitmap( uBaseImage );

	if ( !m_memDC.m_hDC )
	{
		CWindowDC	dc( NULL );
		m_memDC.CreateCompatibleDC( &dc );
	}

	ASSERT( m_memDC.m_hDC );
	::SelectObject( m_memDC.m_hDC, m_hBitmapBG );
	return;
}