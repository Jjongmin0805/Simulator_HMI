#include "pch.h"   
#include "SkinCombobox.h"   

#define SET_ZERO(X) memset((void *)&X,0,sizeof(X));
static WNDPROC m_pWndProc = 0;



extern "C" LRESULT FAR PASCAL SkinComboboxListBoxProc( HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam )   
{
	return CallWindowProc( m_pWndProc, hWnd, nMsg, wParam, lParam );   
}   

IMPLEMENT_DYNAMIC(CSkinCombobox, CComboBox)

CSkinCombobox::CSkinCombobox()
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
	
	m_nListBoxTextLeft       = 0;
	m_nListSelectedItemID    = 0;
	m_uHLMargin		         = 0;
	m_dwStyle			     = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
}   
   
   
CSkinCombobox::~CSkinCombobox()   
{
}

BEGIN_MESSAGE_MAP(CSkinCombobox, CComboBox)   
    ON_WM_PAINT()   
    ON_WM_DESTROY()   
    ON_MESSAGE( WM_CTLCOLORLISTBOX, OnCtlColorListBox )   
	ON_WM_CTLCOLOR()	
END_MESSAGE_MAP()   


void CSkinCombobox::OnDestroy()
{   
	if ( m_listbox.GetSafeHwnd() != NULL )   
		m_listbox.UnsubclassWindow();

	CComboBox::OnDestroy();
}


void CSkinCombobox::SetHighlightColor( COLORREF colBackGround, COLORREF colText )
{
	m_colBackGroundHighLight = colBackGround; 
	m_colTextHighLight		 = colText;
}


void CSkinCombobox::SetNormalPositionColor( COLORREF colBackGround, COLORREF colText )
{
	m_colBackGroundNormal = colBackGround; 
	m_colTextNormal		  = colText;
}


void CSkinCombobox::SetBitmapID( UINT uComboLeftImage, UINT uComboRightImage, UINT uComboCenHImage )
{
	/*m_hBmpComboLeft  = g_gbl.GetBitmap( uComboLeftImage  );
	m_hBmpComboRight = g_gbl.GetBitmap( uComboRightImage );
	m_hBmpComboCenH  = g_gbl.GetBitmap( uComboCenHImage  );	*/

	CBitmap bmp[3];
	bmp[0].LoadMappedBitmap(uComboLeftImage);
	bmp[1].LoadMappedBitmap(uComboRightImage);
	bmp[2].LoadMappedBitmap(uComboCenHImage);
	//bmp[3].LoadMappedBitmap(uComboCenLImage);

	m_hBmpComboLeft = (HBITMAP)bmp[0].Detach();
	m_hBmpComboRight = (HBITMAP)bmp[1].Detach();
	m_hBmpComboCenH = (HBITMAP)bmp[2].Detach();
	//m_hBmpComboCenL = (HBITMAP)bmp[3].Detach();

	bmp[0].DeleteObject();
	bmp[1].DeleteObject();
	bmp[2].DeleteObject();
//	bmp[3].DeleteObject();

	return;
}


void CSkinCombobox::SetBitmapID( UINT uComboLeftImage, UINT uComboRightImage, UINT uComboCenHImage, UINT uComboCenLImage )
{
	// Center low 이미지까지 입력되면 상하좌우로 Bitmap을 처리하고, Center high 이미지까지만 입력되면 좌,중앙,우 로 Bitmap을 처리

	/*m_hBmpComboLeft  = g_gbl.GetBitmap( uComboLeftImage  );
	m_hBmpComboRight = g_gbl.GetBitmap( uComboRightImage );
	m_hBmpComboCenH  = g_gbl.GetBitmap( uComboCenHImage  );
	m_hBmpComboCenL  = g_gbl.GetBitmap( uComboCenLImage  );*/

	CBitmap bmp[4];

	bmp[0].LoadMappedBitmap(uComboLeftImage);
	bmp[1].LoadMappedBitmap(uComboRightImage);
	bmp[2].LoadMappedBitmap(uComboCenHImage);
	bmp[3].LoadMappedBitmap(uComboCenLImage);

	m_hBmpComboLeft  = (HBITMAP)bmp[0].Detach();
	m_hBmpComboRight = (HBITMAP)bmp[1].Detach();
	m_hBmpComboCenH  = (HBITMAP)bmp[2].Detach();
	m_hBmpComboCenL  = (HBITMAP)bmp[3].Detach();

	bmp[0].DeleteObject();
	bmp[1].DeleteObject();
	bmp[2].DeleteObject();
	bmp[3].DeleteObject();
	return;
}


void CSkinCombobox::SetDropDownHeight( int itemsToShow )
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


void CSkinCombobox::SetTextFont( CFont *pFont )
{
	m_pFont = pFont;
	SetFont( m_pFont );
}


void CSkinCombobox::SetCurSelName( CString strName )
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


void CSkinCombobox::SetCurSelId( int nId )
{	
	int i;
	int nRet = -1;
	int nCnt = GetCount();

	for( i = 0; i < nCnt; i++ )
	{
		nRet = (int)GetItemData( i );
		
		if( nRet == nId )
		{
			SetCurSel( i );
			break;
		}
	}

	return;
}


CString CSkinCombobox::GetCurSelName()
{
	CString strText;
	int nSel = GetCurSel();

	if( nSel < 0 )	return strText;
	GetLBText( nSel, strText );

	return strText;
}


int CSkinCombobox::GetCurSelId()
{
	int nSel = GetCurSel();
	int nRet = -1;
	nRet = (int)GetItemData( nSel );

	return nRet;
}


LRESULT CSkinCombobox::OnCtlColorListBox( WPARAM wParam, LPARAM lParam )    
{        
	BOOL b;
    if( this->m_listbox.m_hWnd == 0 ) 
	{   
		m_hWnd;
        HWND hWnd = (HWND)lParam;   
   
        if ( hWnd != 0 && hWnd != m_hWnd )    
        {   
            m_listbox.m_hWnd = hWnd;

			m_pWndProc = (WNDPROC)GetWindowLong( m_listbox.m_hWnd, -4 );   

			SetWindowLong( m_listbox.m_hWnd, -4, (LONG)SkinComboboxListBoxProc );
		
			
        }   
    }

    return DefWindowProc( WM_CTLCOLORLISTBOX, wParam, lParam );
}   


void CSkinCombobox::OnPaint()    
{   
    CPaintDC dc(this);
    RECT rc;
	CDC MemDC;

	GetClientRect( &rc );
	MemDC.CreateCompatibleDC( &dc );

	CBitmap *bmpComboRight, *bmpComboLeft, *bmpComboCenterH, *bmpComboCenterL;
	CBitmap *OldbmpComboRight(NULL), *OldbmpComboLeft(NULL), *OldbmpComboCenterH(NULL), *OldbmpComboCenterL(NULL);
    
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
	if( GetFocus() )	
	{
		if (GetFocus()->m_hWnd == m_hWnd)
		{
			dc.FillSolidRect(&rc, m_colBackGroundNormal);
			dc.SetTextColor(m_colTextHighLight);
		}
		else
		{
			dc.FillSolidRect(&rc, m_colBackGroundNormal);
			dc.SetTextColor(m_colTextNormal);
		}
	}
	

	//Select the font only if list box is created	
	dc.SelectObject( m_pFont );

	rc.left  += 2;
	rc.right -= 2;

	CString sz;
	GetWindowText( sz );
	dc.SetBkMode( TRANSPARENT );
	dc.DrawText( sz, &rc, m_dwStyle );	

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

			//rcItemData.left += bitLeft.bmWidth + 5;
            m_nListBoxTextLeft = rcItemData.left;   

			pDC->SelectObject( m_pFont );
            pDC->DrawText( szItemString, &rcItemData, DT_LEFT );		
			//pDC->DrawText(szItemString, &rcItemData, m_dwStyle);
        }
    }

	MemDC.DeleteDC();
}

   
void CSkinCombobox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)    
{
    if( lpDrawItemStruct->itemID == -1 )
        return;
   
    CDC pDC;
    pDC.Attach( lpDrawItemStruct->hDC );
    CBrush pBrush;
    CString sItem;

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

	//lpDrawItemStruct->rcItem.left = m_nListBoxTextLeft;
    pDC.DrawText( sItem, &lpDrawItemStruct->rcItem, m_dwStyle );

	SIZE sizeText = pDC.GetTextExtent( sItem );

	if( sizeText.cx > lpDrawItemStruct->rcItem.right )	
		SetHorizontalExtent( sizeText.cx );

	pDC.Detach();	
}


HBRUSH CSkinCombobox::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	HBRUSH hbr = CComboBox::OnCtlColor( pDC, pWnd, nCtlColor );

	if (nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetTextColor( m_colTextHighLight );
		pDC->SetBkColor( m_colBackGroundNormal );
	}

	return hbr;
}

void CSkinCombobox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	ASSERT(lpMeasureItemStruct->CtlType == ODT_COMBOBOX);

	if (lpMeasureItemStruct->itemID != (UINT)-1)
	{
		LPCTSTR lpszText = (LPCTSTR)lpMeasureItemStruct->itemData;
	//	ASSERT(lpszText != NULL);
		CSize   sz;
		CDC*    pDC = GetDC();

		sz = pDC->GetTextExtent(lpszText);

		ReleaseDC(pDC);

		lpMeasureItemStruct->itemHeight = 2 * sz.cy;
	}
}


BOOL CSkinCombobox::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (message == WM_DRAWITEM)
	{
		int a = 0;
	}
	return CComboBox::OnChildNotify(message, wParam, lParam, pLResult);
}
