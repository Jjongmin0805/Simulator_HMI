#include "pch.h"   
#include "SkinColorCombobox.h"   

#define SET_ZERO(X) memset((void *)&X,0,sizeof(X));
static WNDPROC m_pWndProc = 0;

extern "C" LRESULT FAR PASCAL SkinColorComboboxListBoxProc( HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam )   
{
	return CallWindowProc( m_pWndProc, hWnd, nMsg, wParam, lParam );   
}   

CSkinColorCombobox::CSkinColorCombobox()
{
	m_pFont			 = NULL;
	m_hBmpComboCenH  = NULL;
	m_hBmpComboCenL  = NULL;
	m_hBmpComboLeft  = NULL;
	m_hBmpComboRight = NULL;

	m_colBackGroundHighLight = g_gbl.GetRGB( IDX_RGB_FONT_LITE_BLUE );
	m_colTextHighLight       = g_gbl.GetRGB( IDX_RGB_FONT_BLACK );
	m_colBackGroundNormal	 = g_gbl.GetRGB( IDX_RGB_FONT_WHITE );
	m_colTextNormal			 = g_gbl.GetRGB( IDX_RGB_FONT_BLACK );
		
	m_nListSelectedItemID    = 0;
	m_uHLMargin		         = 0;
	m_dwStyle			     = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
}   
   
   
CSkinColorCombobox::~CSkinColorCombobox()   
{
}

BEGIN_MESSAGE_MAP(CSkinColorCombobox, CComboBox)   
    ON_WM_PAINT()   
    ON_WM_DESTROY()   
    ON_MESSAGE( WM_CTLCOLORLISTBOX, OnCtlColorListBox )   
	ON_WM_CTLCOLOR()	
END_MESSAGE_MAP()   


void CSkinColorCombobox::OnDestroy()
{   
	if ( m_listbox.GetSafeHwnd() != NULL )   
		m_listbox.UnsubclassWindow();

	CComboBox::OnDestroy();
}


void CSkinColorCombobox::SetHighlightColor( COLORREF colBackGround, COLORREF colText )
{
	m_colBackGroundHighLight = colBackGround; 
	m_colTextHighLight		 = colText;
}


void CSkinColorCombobox::SetNormalPositionColor( COLORREF colBackGround, COLORREF colText )
{
	m_colBackGroundNormal = colBackGround; 
	m_colTextNormal		  = colText;
}


void CSkinColorCombobox::SetBitmapID( UINT uComboLeftImage, UINT uComboRightImage, UINT uComboCenHImage )
{
	m_hBmpComboLeft  = g_gbl.GetBitmap( uComboLeftImage  );
	m_hBmpComboRight = g_gbl.GetBitmap( uComboRightImage );
	m_hBmpComboCenH  = g_gbl.GetBitmap( uComboCenHImage  );	

	return;
}


void CSkinColorCombobox::SetBitmapID( UINT uComboLeftImage, UINT uComboRightImage, UINT uComboCenHImage, UINT uComboCenLImage )
{
	// Center low 이미지까지 입력되면 상하좌우로 Bitmap을 처리하고, Center high 이미지까지만 입력되면 좌,중앙,우 로 Bitmap을 처리

	m_hBmpComboLeft  = g_gbl.GetBitmap( uComboLeftImage  );
	m_hBmpComboRight = g_gbl.GetBitmap( uComboRightImage );
	m_hBmpComboCenH  = g_gbl.GetBitmap( uComboCenHImage  );
	m_hBmpComboCenL  = g_gbl.GetBitmap( uComboCenLImage  );

	return;
}


void CSkinColorCombobox::SetDropDownHeight( int itemsToShow )
{  
	//Get rectangles    
	CRect rctComboBox, rctDropDown;   
	GetClientRect( &rctComboBox );																//Combo rect    
	GetDroppedControlRect( &rctDropDown );														//DropDownList rect   
	
	int itemHeight = GetItemHeight( -1 );														//Get Item height   
	GetParent()->ScreenToClient(&rctDropDown);													//Converts coordinates    
	rctDropDown.bottom = rctDropDown.top + rctComboBox.Height() + itemHeight*itemsToShow - 1;	//Set height   
	MoveWindow( &rctDropDown );																	//enable changes  
}


void CSkinColorCombobox::SetTextFont( CFont *pFont )
{
	m_pFont = pFont;
	SetFont( m_pFont );
}


void CSkinColorCombobox::SetCurSelName( CString strName )
{
	CString strText;
	int i;
	int nCnt = GetCount();

	for( i = 0; i < nCnt; i++ )
	{
		GetLBText( i, strText );
		
		if( strText == strName )
		{
			SetCurSel( i );
			break;
		}
	}

	return;
}


void CSkinColorCombobox::SetCurSelId( int nId )
{	
	int i;
	int nRet = -1;
	int nCnt = GetCount();

	for( i = 0; i < nCnt; i++ )
	{
		nRet = GetItemData( i );
		
		if( nRet == nId )
		{
			SetCurSel( i );
			break;
		}
	}

	return;
}


CString CSkinColorCombobox::GetCurSelName()
{
	CString strText;
	int nSel = GetCurSel();

	if( nSel < 0 )	return strText;
	GetLBText( nSel, strText );

	return strText;
}


int CSkinColorCombobox::GetCurSelId()
{
	int nSel = GetCurSel();
	int nRet = -1;
	nRet = GetItemData( nSel );

	return nRet;
}


LRESULT CSkinColorCombobox::OnCtlColorListBox( WPARAM wParam, LPARAM lParam )    
{          
    if( this->m_listbox.m_hWnd == 0 ) 
	{   
        HWND hWnd = (HWND)lParam;   
   
        if ( hWnd != 0 && hWnd != m_hWnd )    
        {   
            m_listbox.m_hWnd = hWnd;
			m_pWndProc = (WNDPROC)GetWindowLong( m_listbox.m_hWnd, -4 );  
			SetWindowLong( m_listbox.m_hWnd, -4, (LONG)SkinColorComboboxListBoxProc );
        }   
    }

    return DefWindowProc( WM_CTLCOLORLISTBOX, wParam, lParam );
}   


void CSkinColorCombobox::OnPaint()    
{   
    CPaintDC dc(this);
    RECT rc;
	CDC MemDC;

	GetClientRect( &rc );
	MemDC.CreateCompatibleDC( &dc );

	CBitmap *bmpComboRight, *bmpComboLeft, *bmpComboCenterH, *bmpComboCenterL;
	CBitmap *OldbmpComboRight(NULL), *OldbmpComboLeft(NULL), *OldbmpComboCenterH(NULL),  *OldbmpComboCenterL(NULL);
    
	BITMAP bitRight, bitLeft, bitHigh, bitLow;
    SET_ZERO( bitRight ); SET_ZERO( bitLeft ); SET_ZERO( bitHigh );	SET_ZERO( bitLow );

	bmpComboLeft = CBitmap::FromHandle( m_hBmpComboLeft );
	if( bmpComboLeft )
	{
		bmpComboLeft->GetBitmap(&bitLeft);
		OldbmpComboLeft = MemDC.SelectObject(bmpComboLeft);
		dc.BitBlt(rc.left,rc.top,bitLeft.bmWidth,bitLeft.bmHeight,&MemDC,0,0,SRCCOPY);
	}

	bmpComboRight = CBitmap::FromHandle( m_hBmpComboRight );
	if( bmpComboRight )
	{
		bmpComboRight->GetBitmap(&bitRight);
		OldbmpComboRight = MemDC.SelectObject(bmpComboRight);
		dc.BitBlt(rc.right-DROPDOWN_BTN_WIDTH,rc.top,bitRight.bmWidth,bitRight.bmHeight,&MemDC,0,0,SRCCOPY);
	}

	bmpComboCenterH = CBitmap::FromHandle( m_hBmpComboCenH );
	if( bmpComboCenterH )
	{
		bmpComboCenterH->GetBitmap(&bitHigh);
		OldbmpComboCenterH = MemDC.SelectObject(bmpComboCenterH);
		dc.StretchBlt(rc.left+bitLeft.bmWidth,rc.top,rc.right-bitLeft.bmWidth-DROPDOWN_BTN_WIDTH,bitHigh.bmHeight,&MemDC,0,0,bitHigh.bmWidth,bitHigh.bmHeight,SRCCOPY);
	}

	bmpComboCenterL = CBitmap::FromHandle( m_hBmpComboCenL );
	if( bmpComboCenterL )
	{
		bmpComboCenterL->GetBitmap(&bitLow);
		OldbmpComboCenterL = MemDC.SelectObject(bmpComboCenterL);
		dc.StretchBlt(rc.left+bitLeft.bmWidth,rc.top+bitLeft.bmHeight-1,rc.right-bitLeft.bmWidth-DROPDOWN_BTN_WIDTH,bitLow.bmHeight,&MemDC,0,0,bitLow.bmWidth,bitLow.bmHeight,SRCCOPY);

		rc.left += bitLeft.bmWidth;
		rc.right -= DROPDOWN_BTN_WIDTH;
		rc.top += bitHigh.bmHeight;
		rc.bottom -= bitLow.bmHeight;
	}
	else
	{
		rc.left += bitLeft.bmWidth;
		rc.right -= DROPDOWN_BTN_WIDTH;
		rc.top += m_uHLMargin;
		rc.bottom -= m_uHLMargin;
	}

	if( bmpComboLeft    )	MemDC.SelectObject( OldbmpComboLeft );
	if( bmpComboRight   )	MemDC.SelectObject( OldbmpComboRight );
	if( bmpComboCenterH )	MemDC.SelectObject( OldbmpComboCenterH );
	if( bmpComboCenterL )	MemDC.SelectObject( OldbmpComboCenterL );

	// Set the normal/highlight color when its repainted (Part of Combo Edit and Set Drop List)	
	if( !GetFocus() )	return;

	if( GetFocus()->m_hWnd == m_hWnd )
	{
		dc.FillSolidRect( &rc,m_colBackGroundNormal );
		dc.SetTextColor( m_colTextHighLight );		
	}
	else
	{
		dc.FillSolidRect( &rc,m_colBackGroundNormal );
		dc.SetTextColor( m_colTextNormal );		
	}	

	//Select the font only if list box is created	
	dc.SelectObject( m_pFont );
		
	CString sz;
	GetWindowText( sz );
	dc.SetBkMode( TRANSPARENT );
	
	CRect rBlock( rc );
	int nWidth = ( rBlock.Width() / 4 ) - 2;
	int nColor = GetCurSelId();

	dc.TextOut( nWidth + 5, 4, sz );

	rBlock.DeflateRect( CSize( 3, 3 ) );
	rBlock.right = nWidth;

	dc.FillSolidRect( &rBlock, nColor );
	CBrush brFrame;
	brFrame.CreateStockObject( BLACK_BRUSH );
	dc.FrameRect( &rBlock, &brFrame );

	if( m_listbox )
    {   		
		CDC *pDC = m_listbox.GetDC();
		m_listbox.GetClientRect( &rc );

		CBrush pBrush;
		pBrush.CreateSolidBrush( m_colBackGroundNormal );

		m_listbox.GetDC()->FillRect( &rc, &pBrush );
		pDC->SetTextColor( m_colTextNormal );		
		
		CBrush brItemData;   
		RECT rcItemData;   
        CString szItemString;   
        brItemData.CreateSolidBrush( m_colBackGroundHighLight );
        
		for( int i = 0; i < m_listbox.GetCount(); i++ )
        {
            m_listbox.GetText( i, szItemString );   
            m_listbox.GetItemRect( i, &rcItemData );			
			
			CRect rBoxkRect( rcItemData );
			int nBoxWidth = ( rBoxkRect.Width() / 4 );
					
			rBoxkRect.DeflateRect( CSize( 2, 2 ) );
			rBoxkRect.right = nBoxWidth;
		   
            pDC->SetBkMode( TRANSPARENT );
			
			if( i == m_nListSelectedItemID )
			{
				pDC->SetTextColor( m_colTextHighLight );
				pDC->FillRect( &rcItemData, &brItemData );
			}
			else
			{
				pDC->SetTextColor( m_colTextNormal );				
			}		

			pDC->FillSolidRect( &rBoxkRect, GetItemData( i ) );
			CBrush brBoxeBrush;
			brBoxeBrush.CreateStockObject( BLACK_BRUSH );
			pDC->FrameRect( &rBoxkRect, &brBoxeBrush );
			         
			pDC->SelectObject( m_pFont );
            //pDC->DrawText( szItemString, &rcItemData, m_dwStyle );
			
			int nXPos = rcItemData.left + nBoxWidth + 5;
			int nYPos = rcItemData.top;
			pDC->TextOut( nXPos, nYPos, szItemString );
        }
    }	

	MemDC.DeleteDC();
}

   
void CSkinColorCombobox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)    
{
    if( lpDrawItemStruct->itemID == -1 )
        return;
   
    CDC pDC;
    pDC.Attach( lpDrawItemStruct->hDC );
    CBrush pBrush;
    CString sItem;

	////
	CRect rBlockRect( lpDrawItemStruct->rcItem );
	rBlockRect.left -= 1;
	int iFourthWidth = ( rBlockRect.Width() / 4 ) - 1;

	// calculate colour block area.
	rBlockRect.DeflateRect( CSize( 2, 2 ) );
	rBlockRect.right = iFourthWidth;
	////

	if( (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) && (lpDrawItemStruct->itemState & ODS_FOCUS) )
		Invalidate();
	
    if( lpDrawItemStruct->itemState & ODS_FOCUS || lpDrawItemStruct->itemState & ODS_SELECTED )
    {
        pBrush.CreateSolidBrush( m_colBackGroundHighLight );
        pDC.FillRect( &lpDrawItemStruct->rcItem, &pBrush );
        pDC.SetTextColor( m_colTextHighLight );

		m_nListSelectedItemID = lpDrawItemStruct->itemID;
    }	
    else
    {
        pBrush.CreateSolidBrush( m_colBackGroundNormal );
        pDC.FillRect( &lpDrawItemStruct->rcItem, &pBrush );
        pDC.SetTextColor( m_colTextNormal );		
    }

    this->GetLBText( lpDrawItemStruct->itemID, sItem );
    pDC.SetBkMode( TRANSPARENT );
	
	int nXPos = rBlockRect.right + 5;
	int nYPos = rBlockRect.top - 1;
	pDC.TextOut( nXPos, nYPos, sItem );
	//pDC.DrawText( sItem, &lpDrawItemStruct->rcItem, m_dwStyle );
		
	pDC.FillSolidRect( &rBlockRect, GetItemData( lpDrawItemStruct->itemID ) );
	CBrush brFrameBrush;
	brFrameBrush.CreateStockObject( BLACK_BRUSH );
	pDC.FrameRect( &rBlockRect, &brFrameBrush );

	SIZE sizeText = pDC.GetTextExtent( sItem );

	if( sizeText.cx > lpDrawItemStruct->rcItem.right )	
		SetHorizontalExtent( sizeText.cx );

	pDC.Detach();	
}


HBRUSH CSkinColorCombobox::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	HBRUSH hbr = CComboBox::OnCtlColor( pDC, pWnd, nCtlColor );

	if (nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetTextColor( m_colTextHighLight );
		pDC->SetBkColor( m_colBackGroundNormal );
	}

	return hbr;
}