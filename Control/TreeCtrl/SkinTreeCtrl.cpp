#include "StdAfx.h"
#include "SkinTreeCtrl.h"

CSkinTreeCtrl::CSkinTreeCtrl(void)
{
	m_hBmpTreeTop		= NULL;
	m_hBmpTreeLeft		= NULL;
	m_hBmpTreeRight		= NULL;
	m_hBmpTreeBot		= NULL;
	m_hBmpTreeDefaultBg = NULL;
	m_pFont				= NULL;
}

CSkinTreeCtrl::~CSkinTreeCtrl(void)
{

}


BEGIN_MESSAGE_MAP(CSkinTreeCtrl, CTreeCtrl)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_NOTIFY_REFLECT( TVN_ITEMEXPANDING, &CSkinTreeCtrl::OnTvnItemexpanding )
	ON_WM_ERASEBKGND()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_MOUSEWHEEL()	
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()

void CSkinTreeCtrl::DrawCenter(int nWidth)
{
	RECT rc;
	CDC MemDC;
	CDC *pDC = GetDC();
	MemDC.CreateCompatibleDC(pDC);
	GetClientRect(&rc);

	if( !m_hBmpTreeDefaultBg )	return;

	CBitmap *bmpImage = CBitmap::FromHandle( m_hBmpTreeDefaultBg );
	BITMAP bitImage;

	if( bmpImage )
	{
		bmpImage->GetBitmap(&bitImage);
		MemDC.SelectObject(bmpImage);
		pDC->SetBkMode(TRANSPARENT);
		pDC->StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&MemDC,0,0,bitImage.bmWidth,bitImage.bmHeight,SRCCOPY);

		MemDC.SelectObject( bmpImage );
		ReleaseDC( pDC );
	}
}


// Draws the left image of the list box
void CSkinTreeCtrl::DrawListLeft(int nHeight)
{
	RECT rc;
	CDC MemDC;
	CDC *pDC = GetDC();
	MemDC.CreateCompatibleDC(pDC);
	GetClientRect(&rc);

	if(!m_hBmpTreeLeft)	return;

	CBitmap *bmpImage = CBitmap::FromHandle( m_hBmpTreeLeft );
	BITMAP bitImage;

	if( bmpImage )
	{
		bmpImage->GetBitmap(&bitImage);
		MemDC.SelectObject(bmpImage);
		pDC->StretchBlt(rc.left,rc.top,bitImage.bmWidth,rc.bottom,&MemDC,0,0,bitImage.bmWidth,bitImage.bmHeight,SRCCOPY);
	}
}

// Draws the right image of the list box
void CSkinTreeCtrl::DrawListRight(int nHeight)
{
	RECT rc;
	CDC MemDC;
	CDC *pDC = GetDC();
	MemDC.CreateCompatibleDC(pDC);
	GetClientRect(&rc);

	CBitmap *bmpImage = CBitmap::FromHandle( m_hBmpTreeRight );
	BITMAP bitImage;

	if( bmpImage )
	{
		bmpImage->GetBitmap(&bitImage);
		MemDC.SelectObject(bmpImage);
		pDC->StretchBlt(rc.right-bitImage.bmWidth,rc.top,bitImage.bmWidth,rc.bottom,&MemDC,0,0,bitImage.bmWidth,bitImage.bmHeight,SRCCOPY);
	}
}

// Draws the top image of the list box
void CSkinTreeCtrl::DrawListTop(int nWidth)
{
	RECT rc;
	CDC MemDC;
	CDC *pDC = GetDC();
	MemDC.CreateCompatibleDC(pDC);
	GetClientRect(&rc);

	CBitmap *bmpImage = CBitmap::FromHandle( m_hBmpTreeTop );
	BITMAP bitImage;

	if( bmpImage )
	{
		bmpImage->GetBitmap(&bitImage);
		MemDC.SelectObject(bmpImage);
		pDC->StretchBlt(rc.left,rc.top,rc.right,bitImage.bmHeight,&MemDC,0,0,bitImage.bmWidth,bitImage.bmHeight,SRCCOPY);
	}		

}

// Draws the bottom image of the list box
void CSkinTreeCtrl::DrawListBot(int nWidth)
{
	//Width must be check, sometimes we may not need to stretch to the whole control's width
	RECT rc;
	CDC MemDC;
	CDC *pDC = GetDC();
	MemDC.CreateCompatibleDC(pDC);
	GetClientRect(&rc);

	CBitmap *bmpImage = CBitmap::FromHandle( m_hBmpTreeBot );
	BITMAP bitImage;

	if( bmpImage )
	{
		bmpImage->GetBitmap(&bitImage);
		MemDC.SelectObject(bmpImage);
		pDC->StretchBlt(rc.left,rc.bottom-bitImage.bmHeight,rc.right,bitImage.bmHeight,&MemDC,0,0,bitImage.bmWidth,bitImage.bmHeight,SRCCOPY);
	}

}


void CSkinTreeCtrl::PreSubclassWindow()
{
	ModifyStyle ( 0, TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS );	

	CTreeCtrl::PreSubclassWindow();
}


void CSkinTreeCtrl::OnPaint()
{	
	CPaintDC dc(this);

	CRect rcClip, rcClient;
	dc.GetClipBox( &rcClip );
	GetClientRect(&rcClient);

	// Create a compatible memory DC 
	CDC memDC;
	memDC.CreateCompatibleDC( &dc );

	// Select a compatible bitmap into the memory DC
	CBitmap bitmap, bmpImage;
	bitmap.CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() );
	memDC.SelectObject( &bitmap );

	//// First let the control do its default drawing.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );

	// Draw bitmap in the background if one has been set
	if( m_bitmap.m_hObject != NULL )
	{
		// Now create a mask
		//CDC maskDC;
		//maskDC.CreateCompatibleDC(&dc);
		//CBitmap maskBitmap;

		//// Create monochrome bitmap for the mask
		//maskBitmap.CreateBitmap( rcClient.Width(), rcClient.Height(),
		//	1, 1, NULL );
		//maskDC.SelectObject( &maskBitmap );
		//memDC.SetBkColor( ::GetSysColor( COLOR_WINDOW ) );

		//// Create the mask from the memory DC
		//maskDC.BitBlt( 0, 0, rcClient.Width(), rcClient.Height(), &memDC,
		//	rcClient.left, rcClient.top, SRCCOPY );


		//CDC tempDC;
		//tempDC.CreateCompatibleDC(&dc);
		//tempDC.SelectObject( &m_bitmap );

		//CDC imageDC;
		//CBitmap bmpImage;
		//imageDC.CreateCompatibleDC( &dc );
		//bmpImage.CreateCompatibleBitmap( &dc, rcClient.Width(),
		//	rcClient.Height() );
		//imageDC.SelectObject( &bmpImage );

		//if( dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL )
		//{
		//	dc.SelectPalette( &m_pal, FALSE );
		//	dc.RealizePalette();

		//	imageDC.SelectPalette( &m_pal, FALSE );
		//}

		//// Get x and y offset
		//CRect rcRoot;
		//GetItemRect( GetRootItem(), rcRoot, FALSE );
		//rcRoot.left = -GetScrollPos( SB_HORZ );

		//// Draw bitmap in tiled manner to imageDC
		//for( int i = rcRoot.left; i < rcClient.right; i += m_cxBitmap )
		//	for( int j = rcRoot.top; j < rcClient.bottom; j += m_cyBitmap )
		//		imageDC.BitBlt( i, j, m_cxBitmap, m_cyBitmap, &tempDC,
		//		0, 0, SRCCOPY );

		// Set the background in memDC to black. Using SRCPAINT with black and any other
		// color results in the other color, thus making black the transparent color
		//memDC.SetBkColor(RGB(0,0,0));
		//memDC.SetTextColor(RGB(255,255,255));
		//memDC.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &maskDC,
		//	rcClip.left, rcClip.top, SRCAND);

		// Set the foreground to black. See comment above.
		//imageDC.SetBkColor(RGB(255,255,255));
		//imageDC.SetTextColor(RGB(0,0,0));
		//imageDC.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &maskDC,
		//	rcClip.left, rcClip.top, SRCAND);

		// Combine the foreground with the background
		//imageDC.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC, rcClip.left, rcClip.top,SRCPAINT);

		// Draw the final image to the screen		
		//dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(),
		//	&imageDC, rcClip.left, rcClip.top, SRCCOPY );

		//BITMAP bm;
		//bmpImage.GetBitmap( &bm );

		//CRect rcTmp;
		//GetClientRect(rcTmp);		
		//dc.StretchBlt(rcClient.left,rcClient.top,rcClient.right,rcClient.bottom,&imageDC,0,0,bm.bmWidth, bm.bmHeight,SRCCOPY);
	}
	else
	{
		dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(),
			rcClip.Height(), &memDC,
			rcClip.left, rcClip.top, SRCCOPY );
	}

	//DrawListLeft ();		// Draw the left side of the list box	
	//DrawListRight();		// Draw the right side of the list box	
	//DrawListTop  ();		// Draw the top of the list bar	
	//DrawListBot  ();		// Draw the bottom of the list bar
}


void CSkinTreeCtrl::SetTextFont( CFont *pFont )
{
	m_pFont = pFont;
	SetFont( m_pFont );
}


BOOL CSkinTreeCtrl::SetTextNBkClr( COLORREF clrText, COLORREF clrBk )
{
	SetTextColor( clrText );

	if( clrBk && !m_hBmpTreeDefaultBg )
		SetBkColor( clrBk );

	return TRUE;
}


void CSkinTreeCtrl::SetCheckAll( BOOL bCheck )
{
	HTREEITEM hRoot = GetRootItem();
	SetCheck( hRoot, bCheck );
	
	SetCheckItem( hRoot, bCheck );
}


void CSkinTreeCtrl::SetCheckItem( HTREEITEM hItem, BOOL bCheck )
{
	HTREEITEM hChildItem = GetChildItem( hItem );
	
	while( hChildItem != NULL )
	{
		SetCheck( hChildItem, bCheck );

		if( ItemHasChildren( hChildItem ) )
		{
			SetCheckItem( hChildItem, bCheck );
		}

		hChildItem = GetNextItem( hChildItem, TVGN_NEXT );
	}
}


void CSkinTreeCtrl::SetBitmapID( UINT uTreeTopImage, UINT uTreeLeftImage, UINT uTreeRightImage, UINT uTreeBotImage, UINT uTreeDefaultBgImage )
{
	// 각 비트맵의 핸들을 얻어온다.
	m_hBmpTreeTop   = g_gbl.GetBitmap( uTreeTopImage   );	
	m_hBmpTreeLeft  = g_gbl.GetBitmap( uTreeLeftImage  );
	m_hBmpTreeRight = g_gbl.GetBitmap( uTreeRightImage );
	m_hBmpTreeBot   = g_gbl.GetBitmap( uTreeBotImage   );

	if(uTreeDefaultBgImage)
	{
		m_hBmpTreeDefaultBg = g_gbl.GetBitmap( uTreeDefaultBgImage );
		SetBkImage();
	}

	return;
}

BOOL CSkinTreeCtrl::SetBkImage()
{
	if( !m_hBmpTreeDefaultBg )	return FALSE;

	// If this is not the first call then Delete GDI objects
	if( m_bitmap.m_hObject != NULL )
		m_bitmap.DeleteObject();

	if( m_pal.m_hObject != NULL )
		m_pal.DeleteObject();

	if( m_hBmpTreeDefaultBg == NULL )
		return FALSE;

	m_bitmap.Attach( m_hBmpTreeDefaultBg );
	BITMAP bm;
	m_bitmap.GetBitmap( &bm );
	m_cxBitmap = bm.bmWidth;
	m_cyBitmap = bm.bmHeight;

	// Create a logical palette for the bitmap
	DIBSECTION ds;
	BITMAPINFOHEADER &bmInfo = ds.dsBmih;
	m_bitmap.GetObject( sizeof(ds), &ds );

	int nColors = bmInfo.biClrUsed ? bmInfo.biClrUsed : 1 << bmInfo.biBitCount;

	// Create a halftone palette if colors > 256. 
	CClientDC dc(NULL);			// Desktop DC
	
	if( nColors > 256 )
		m_pal.CreateHalftonePalette( &dc );
	else
	{
		// Create the palette

		RGBQUAD *pRGB = new RGBQUAD[nColors];
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		memDC.SelectObject( &m_bitmap );
		::GetDIBColorTable( memDC, 0, nColors, pRGB );

		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;

		for( int i=0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed   = pRGB[i].rgbRed;
			pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
			pLP->palPalEntry[i].peBlue  = pRGB[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}

		m_pal.CreatePalette( pLP );

		delete[] pLP;
		delete[] pRGB;
	}
	
	Invalidate();
	return TRUE;
}

void CSkinTreeCtrl::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( m_bitmap.m_hObject != NULL )
		InvalidateRect( NULL );
	
	switch( nSBCode )
	{
	case SB_LINEUP     :
	case SB_LINEDOWN   :
	case SB_THUMBTRACK :
		this->Invalidate();
		break;
	}
	
	CTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CSkinTreeCtrl::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( m_bitmap.m_hObject != NULL )
		InvalidateRect( NULL );
	
	switch( nSBCode )
	{
	case SB_LINELEFT   :
	case SB_LINERIGHT  :
	case SB_THUMBTRACK :
		this->Invalidate();
		break;
	}
	
	CTreeCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSkinTreeCtrl::OnTvnItemexpanding( NMHDR *pNMHDR, LRESULT *pResult )
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	InvalidateRect( NULL );
	*pResult = 0;
}


BOOL CSkinTreeCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if( m_bitmap.m_hObject != NULL )
		return TRUE;

	return false; //CTreeCtrl::OnEraseBkgnd(pDC);
}


BOOL CSkinTreeCtrl::OnQueryNewPalette()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC dc(this);
	if( dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL )
	{
		dc.SelectPalette( &m_pal, FALSE );
		BOOL result = dc.RealizePalette();
		
		if( result )
			Invalidate();
		
		return result;
	}

	return CTreeCtrl::OnQueryNewPalette();
}


BOOL CSkinTreeCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	this->Invalidate();
	return CTreeCtrl::OnMouseWheel(nFlags, zDelta, pt);
}


void CSkinTreeCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMTVCUSTOMDRAW* pcd = (NMTVCUSTOMDRAW*)pNMHDR;
	HTREEITEM hItem = 0;

	switch( pcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;

	case CDDS_ITEMPREPAINT:
		hItem = (HTREEITEM)pcd->nmcd.dwItemSpec;
		//pcd->clrText = RGB(255,0,0);

		if(pcd->iLevel == 4) //설비명
		{
			DWORD_PTR nCeqID = GetItemData( hItem );
			TREEDATA *pTreeData = (TREEDATA*)nCeqID;
			switch(pTreeData->STATUS)
			{
			case 1: //자동 통신정상
				pcd->clrText = RGB(0,0,0);
				if(pcd->nmcd.uItemState == 17) //선택됐을 경우
				{
					pcd->clrText = RGB(255,255,255);
				}
				else if(pcd->nmcd.uItemState == 1) //선택됐고 비활성
				{
					pcd->clrText = RGB(255,255,255);
					pcd->clrTextBk = RGB(113,113,113);
				}
				break;
			case 2: //자동 통신이상
				pcd->clrText = RGB(255,0,0);
				if(pcd->nmcd.uItemState == 17) //선택됐을 경우
				{
					pcd->clrText = RGB(255,255,255);
				}
				else if(pcd->nmcd.uItemState == 1) //선택됐고 비활성
				{
					pcd->clrText = RGB(255,255,255);
					pcd->clrTextBk = RGB(113,113,113);
				}
				break;
			case 3: //수동
				pcd->clrText = RGB(128,128,128);
				if(pcd->nmcd.uItemState == 17) //선택됐을 경우
				{
					pcd->clrText = RGB(255,255,255);
				}
				else if(pcd->nmcd.uItemState == 1) //선택됐고 비활성
				{
					pcd->clrText = RGB(255,255,255);
					pcd->clrTextBk = RGB(113,113,113);
				}
				break;
			default:
				pcd->clrText = RGB(0,0,0);
				break;
			}
			//if(pTreeData->STATUS == 2)
			//	pcd->clrText = RGB(255,0,0);
		}
		else
		{
			pcd->clrText = RGB(0,0,0);
			if(pcd->nmcd.uItemState == 17) //선택됐을 경우
			{
				pcd->clrText = RGB(255,255,255);
			}
			else if(pcd->nmcd.uItemState == 1) //선택됐고 비활성
			{
				pcd->clrText = RGB(255,255,255);
				pcd->clrTextBk = RGB(113,113,113);
			}
		}


		//break;
	}
}