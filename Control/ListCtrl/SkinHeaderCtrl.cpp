// SkinHeaderCtrl.cpp
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// This code is based on "Outlook 98-Style FlatHeader Control" 
// by Maarten Hoeben.
//
// See http://www.codeguru.com/listview/FlatHeader.shtml
//
// This software is released into the public domain.
// You are free to use it in any way you like.
//
// This software is provided "as is" with no expressed
// or implied warranty.  I accept no liability for any
// damage or loss of business that this software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "SkinHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinHeaderCtrl

CSkinHeaderCtrl::CSkinHeaderCtrl()
{
	m_bDoubleBuffer   = TRUE;
	m_iSpacing	      = 0;
	m_sizeArrow.cx    = 8;
	m_sizeArrow.cy    = 8;
	m_sizeImage.cx    = 0;
	m_sizeImage.cy    = 0;
	m_bStaticBorder   = FALSE;
	m_nDontDropCursor = 0;
	m_bResizing       = FALSE;
	m_nClickFlags     = 0;

	m_cr3DHighLight = RGB(0,0,255);//::GetSysColor( COLOR_3DHIGHLIGHT );
	m_cr3DShadow    = ::GetSysColor( COLOR_3DSHADOW );
	m_cr3DFace      = ::GetSysColor( COLOR_3DFACE );	
	m_crBtnText     = ::GetSysColor( COLOR_BTNTEXT );

	// JCW_+ 2008.04.12 START
	m_bTracking		= FALSE;
	m_bLMouseDown	= FALSE;
	m_bFlat			= FALSE;

	m_colorHeader   = g_gbl.GetRGB( IDX_RGB_FONT_BLACK );
	m_nHeight		= 30;
	m_pTextFont		= NULL;
	// JCW_+ 2008.04.12 END
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CSkinHeaderCtrl::~CSkinHeaderCtrl()
{
}

///////////////////////////////////////////////////////////////////////////////
//
IMPLEMENT_DYNCREATE(CSkinHeaderCtrl, CHeaderCtrl)

BEGIN_MESSAGE_MAP(CSkinHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CSkinHeaderCtrl)
	ON_MESSAGE(HDM_INSERTITEM, OnInsertItem)
	ON_MESSAGE(HDM_DELETEITEM, OnDeleteItem)
	ON_MESSAGE(HDM_SETIMAGELIST, OnSetImageList)
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// ModifyProperty
BOOL CSkinHeaderCtrl::ModifyProperty(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case FH_PROPERTY_SPACING:
			m_iSpacing = (int)lParam;
			break;

		case FH_PROPERTY_ARROW:
			m_sizeArrow.cx = LOWORD(lParam);
			m_sizeArrow.cy = HIWORD(lParam);
			break;

		case FH_PROPERTY_STATICBORDER:
			m_bStaticBorder = (BOOL)lParam;
			break;

		case FH_PROPERTY_DONTDROPCURSOR:
			m_nDontDropCursor = (UINT)lParam;
			break;

		default:
			return FALSE;
	}

	Invalidate();
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// DrawCtrl
void CSkinHeaderCtrl::DrawCtrl(CDC* pDC)
{
	CRect rectClip;
	if (pDC->GetClipBox(&rectClip) == ERROR)
		return;

	CRect rectClient(0,0,0,0), rectItem(0,0,0,0);
	GetClientRect(&rectClient);

	// JCW_U 2008.04.12 START
	HCURSOR hCursor = GetCursor();
	HCURSOR hCursorArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	//pDC->FillSolidRect(rectClip, m_cr3DFace);
	pDC->FillSolidRect( rectClip, RGB(209 ,209, 209) ); //g_gbl.GetRGB( IDX_RGB_FONT_WHITE ) ); //g_gbl.GetRGB( IDX_RGB_FONT_LITE_GRAY ) ); //헤더의 배경 IDX_RGB_FONT_WHITE
	// JCW_U 2008.04.12 END

	int iItems = GetItemCount();
	ASSERT(iItems >= 0);

	CPen penHighLight(PS_SOLID, 1, m_cr3DHighLight);
	CPen penShadow(PS_SOLID, 1, m_cr3DShadow);
	CPen* pPen = pDC->GetCurrentPen();

	// JCW_U 2008.04.12 START
	CFont* pFont = pDC->SelectObject( m_pTextFont );
	//CFont* pFont = pDC->SelectObject(GetFont());
	// JCW_U 2008.04.12 END

	pDC->SetBkColor( RGB(215 ,214, 214) );	//RGB( 240, 240, 240 ) );
	pDC->SetTextColor(m_crBtnText);

	int iWidth = 0;

	// JCW_+ 2008.04.12 START

	DWORD dwStyle = ::GetWindowLong(GetParent()->GetSafeHwnd(), GWL_STYLE);	

	POINT pointMouse;
	::GetCursorPos(&pointMouse);
	::ScreenToClient(m_hWnd, &pointMouse);	
	// JCW_+ 2008.04.12 END

	for (int i = 0; i < iItems; i++)
	{
		int iItem = OrderToIndex(i);

		TCHAR szText[FLATHEADER_TEXT_MAX];

		HDITEM hditem;
		hditem.mask = HDI_WIDTH|HDI_FORMAT|HDI_TEXT|HDI_IMAGE|HDI_BITMAP;
		hditem.pszText = szText;
		hditem.cchTextMax = sizeof(szText);
		VERIFY(GetItem(iItem, &hditem));
		VERIFY(GetItemRect(iItem, rectItem));

		/////////////////////// 헤더컨트롤 옅은회색 지정 ///////////////////////////
		CRect rectColumn = rectItem;
		
		rectColumn.bottom -= 1;		
		
		if (iItems == i + 1)
			rectColumn.right = rectClip.right;
		else
			rectColumn.left += 1;
		
		pDC->FillSolidRect( &rectColumn, m_cr3DFace);
		////////////////////////////////////////////////////////////////////////////

		// JCW_U 2008.04.12 START
		if( !(dwStyle&LVS_NOSORTHEADER) && 
			rectItem.PtInRect(pointMouse) && 
			hCursor == hCursorArrow )
		{
			if( !m_bLMouseDown )
				DrawMouseOver(pDC, rectItem);
			else
				DrawMouseDown(pDC, rectItem);
		}
		else
			DrawMouseOut(pDC, rectItem);
		// JCW_U 2008.04.12 END

		if( rectItem.right >= rectClip.left || rectItem.left <= rectClip.right )
		{
			if( hditem.fmt & HDF_OWNERDRAW )
			{
				DRAWITEMSTRUCT disItem;
				disItem.CtlType = ODT_BUTTON;
				disItem.CtlID = GetDlgCtrlID();
				disItem.itemID = iItem;
				disItem.itemAction = ODA_DRAWENTIRE;
				disItem.itemState = 0;
				disItem.hwndItem = m_hWnd;
				disItem.hDC = pDC->m_hDC;
				disItem.rcItem = rectItem;
				disItem.itemData = 0;

				DrawItem(&disItem);
			}
			else
			{
				rectItem.DeflateRect(m_iSpacing, 0);
				DrawItem(pDC, rectItem, &hditem);
				rectItem.InflateRect(m_iSpacing, 0);

				//if (m_nClickFlags & MK_LBUTTON && m_iHotIndex == iItem && m_hdhtiHotItem.flags & HHT_ONHEADER)
				//	pDC->InvertRect(rectItem);
			}
			// JCW_U 2008.04.12 START
			SIZE size = g_gbl.GetBitmapSize(IDX_PNG_LISTCTRL_HEADER_DIVISION);
			SIZE size2 = g_gbl.GetBitmapSize(IDX_PNG_LISTCTRL_HEADER_SHADOW);
			CDC tmpDC;
			tmpDC.CreateCompatibleDC(pDC);
			tmpDC.SelectObject(g_gbl.GetBitmap(IDX_PNG_LISTCTRL_HEADER_DIVISION));
			pDC->BitBlt(rectItem.right, rectItem.bottom - size.cy - size2.cy, size.cx, size.cy, &tmpDC, 0, 0, SRCCOPY);
			tmpDC.DeleteDC();
			// JCW_U 2008.04.12 END

		}
		iWidth += hditem.cxy;
	}

	// JCW_+ 2008.04.12 START
	rectItem.left = iWidth;
	rectItem.right = rectClient.Width();

	if( !(dwStyle&LVS_NOSORTHEADER) && 
		rectItem.PtInRect(pointMouse) && 
		hCursor == hCursorArrow )
	{
		if( !m_bLMouseDown )
			DrawMouseOver(pDC, rectItem);
		else
			DrawMouseDown(pDC, rectItem);
	}
	else
		DrawMouseOut(pDC, rectItem);
	// JCW_+ 2008.04.12 END

	pDC->SelectObject(pFont);
	pDC->SelectObject(pPen);

	penHighLight.DeleteObject();
	penShadow.DeleteObject();
}

///////////////////////////////////////////////////////////////////////////////
// DrawItem
void CSkinHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT)
{
	ASSERT(FALSE);  // must override for self draw header controls
}

///////////////////////////////////////////////////////////////////////////////
// DrawItem
void CSkinHeaderCtrl::DrawItem(CDC* pDC, CRect rect, LPHDITEM lphdi)
{
	ASSERT(lphdi->mask & HDI_FORMAT);

	int iWidth = 0;

	CBitmap* pBitmap = NULL;
	BITMAP BitmapInfo;

	if (lphdi->fmt & HDF_BITMAP)
	{
		ASSERT(lphdi->mask & HDI_BITMAP);
		ASSERT(lphdi->hbm);

		pBitmap = CBitmap::FromHandle(lphdi->hbm);
		if (pBitmap)
			VERIFY(pBitmap->GetObject(sizeof(BITMAP), &BitmapInfo));
	}

	rect.left += ((iWidth = DrawImage(pDC, rect, lphdi, FALSE)) != 0) ? iWidth + m_iSpacing : 0;
	rect.right -= ((iWidth = DrawBitmap(pDC, rect, lphdi, pBitmap, &BitmapInfo, TRUE)) != 0) ? 
		iWidth + m_iSpacing : 0;	

	DrawText(pDC, rect, lphdi);
}

///////////////////////////////////////////////////////////////////////////////
// DrawImage
int CSkinHeaderCtrl::DrawImage(CDC* pDC, CRect rect, LPHDITEM lphdi, BOOL bRight)
{
	CImageList* pImageList = GetImageList();
	int iWidth = 0;

	if (lphdi->iImage != SKINHEADERCTRL_NO_IMAGE)
	{
		if (pImageList)
		{
			if (rect.Width() > 0)
			{
				POINT point;

				point.y = rect.CenterPoint().y - (m_sizeImage.cy >> 1);

				if (bRight)
					point.x = rect.right - m_sizeImage.cx;
				else
					point.x = rect.left;

				SIZE size;
				size.cx = rect.Width()<m_sizeImage.cx ? rect.Width():m_sizeImage.cx;
				size.cy = m_sizeImage.cy;

				// save image list background color
				COLORREF rgb = pImageList->GetBkColor();

				// set image list background color to same as header control
				pImageList->SetBkColor(pDC->GetBkColor());
				pImageList->DrawIndirect(pDC, lphdi->iImage, point, size, CPoint(0, 0));
				pImageList->SetBkColor(rgb);
				
				iWidth = m_sizeImage.cx;
			}
		}
	}

	return iWidth;
}

///////////////////////////////////////////////////////////////////////////////
// DrawBitmap
int CSkinHeaderCtrl::DrawBitmap(CDC* pDC, 
								CRect rect, 
								LPHDITEM lphdi, 
								CBitmap* pBitmap, 
								BITMAP* pBitmapInfo, 
								BOOL bRight)
{
	UNUSED_ALWAYS(lphdi);

	int iWidth = 0;

	if (pBitmap)
	{
		iWidth = pBitmapInfo->bmWidth;
		if (iWidth <= rect.Width() && rect.Width() > 0)
		{
			POINT point;

			// JCW_U 2008.04.12 START
			//point.y = rect.CenterPoint().y - (pBitmapInfo->bmHeight >> 1);
			point.y = rect.bottom - pBitmapInfo->bmHeight - 10;
			// JCW_U 2008.04.12 END

			if (bRight)
				point.x = rect.right - iWidth;
			else
				point.x = rect.left;

			CDC dc;
			if (dc.CreateCompatibleDC(pDC) == TRUE) 
			{
				VERIFY(dc.SelectObject(pBitmap));
				iWidth = pDC->BitBlt(
					point.x, point.y, 
					pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, 
					&dc, 
					0, 0, 
					SRCCOPY
				) ? iWidth:0;
			}
			else 
				iWidth = 0;
		}
		else
			iWidth = 0;
	}

	return iWidth;
}

///////////////////////////////////////////////////////////////////////////////
// DrawText
int CSkinHeaderCtrl::DrawText(CDC* pDC, CRect rect, LPHDITEM lphdi)
{
	// JCW_+ 2008.04.12 START
	pDC->SetBkMode(TRANSPARENT);
	// JCW_+ 2008.04.12 END

	CSize size;

	//pDC->SetTextColor(RGB(0,0,255));
	pDC->SetTextColor(m_colorHeader);
	
	if (rect.Width() > 0 && lphdi->mask & HDI_TEXT && lphdi->fmt & HDF_STRING)
	{
		size = pDC->GetTextExtent(lphdi->pszText);

		// JCW_U 2008.04.12 START
		rect.top = 5;
		// always center column headers
		pDC->DrawText(lphdi->pszText, -1, rect, DT_CENTER | DT_END_ELLIPSIS | DT_WORDBREAK | DT_VCENTER );
		// JCW_U 2008.04.12 END
	}

	size.cx = rect.Width()>size.cx ? size.cx:rect.Width();
	return size.cx>0 ? size.cx:0;
}

///////////////////////////////////////////////////////////////////////////////
// OnInsertItem
LRESULT CSkinHeaderCtrl::OnInsertItem(WPARAM, LPARAM)
{
	return Default();
}

///////////////////////////////////////////////////////////////////////////////
// OnDeleteItem
LRESULT CSkinHeaderCtrl::OnDeleteItem(WPARAM, LPARAM)
{
	return Default();
}

///////////////////////////////////////////////////////////////////////////////
// OnSetImageList
LRESULT CSkinHeaderCtrl::OnSetImageList(WPARAM, LPARAM lParam)
{
	CImageList* pImageList;
	pImageList = CImageList::FromHandle((HIMAGELIST)lParam);	

	IMAGEINFO info;
	if (pImageList->GetImageInfo(0, &info))
	{
		m_sizeImage.cx = info.rcImage.right - info.rcImage.left;
		m_sizeImage.cy = info.rcImage.bottom - info.rcImage.top;
	}

	return Default();
}

///////////////////////////////////////////////////////////////////////////////
// OnLayout
LRESULT CSkinHeaderCtrl::OnLayout(WPARAM, LPARAM lParam)
{
// JCW_U 2008.04.12 START
#if 1
	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);

	if( m_nHeight > 0 )
	{
		LPHDLAYOUT lphdlayout = (LPHDLAYOUT)lParam;
		RECT *prc = lphdlayout->prc;
		WINDOWPOS *pwpos = lphdlayout->pwpos;

		pwpos->cy = m_nHeight;
		prc->top = m_nHeight;
	}
	return lResult;	
#else
	LPHDLAYOUT lphdlayout = (LPHDLAYOUT)lParam;

	if (m_bStaticBorder)
		lphdlayout->prc->right += GetSystemMetrics(SM_CXBORDER)*2;

	return CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);
#endif
// JCW_U 2008.04.12 END
}

///////////////////////////////////////////////////////////////////////////////
// OnSysColorChange
void CSkinHeaderCtrl::OnSysColorChange() 
{	
	CHeaderCtrl::OnSysColorChange();
	m_cr3DHighLight = ::GetSysColor(COLOR_3DHIGHLIGHT);
	m_cr3DShadow    = ::GetSysColor(COLOR_3DSHADOW);
	m_cr3DFace      = ::GetSysColor(COLOR_3DFACE);
	m_crBtnText     = ::GetSysColor(COLOR_BTNTEXT);
}

///////////////////////////////////////////////////////////////////////////////
// OnEraseBkgnd
BOOL CSkinHeaderCtrl::OnEraseBkgnd(CDC* pDC) 
{
	UNUSED_ALWAYS(pDC);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// OnPaint
void CSkinHeaderCtrl::OnPaint() 
{
    CPaintDC dc(this);
	
    if (m_bDoubleBuffer)
    {
        CMemCDC MemCDC( &dc );
		DrawCtrl( &MemCDC );
    }
    else
        DrawCtrl(&dc);
}

// JCW_+ 2008.04.12 START
void CSkinHeaderCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//
    if(!m_bTracking) 
	{
        TRACKMOUSEEVENT t = { sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_hWnd, 0 };
        if (::_TrackMouseEvent(&t)) 
		{
            m_bTracking = TRUE;
        }
    }
	else
	{
		Invalidate();
	}

	CHeaderCtrl::OnMouseMove(nFlags, point);
}

LRESULT CSkinHeaderCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bTracking = FALSE;
    Invalidate();
	return 0L;
}

void CSkinHeaderCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLMouseDown = TRUE;

	CHeaderCtrl::OnLButtonDown(nFlags, point);
}

void CSkinHeaderCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLMouseDown = FALSE;

	CHeaderCtrl::OnLButtonDown(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////////
// DrawMouseOver
void CSkinHeaderCtrl::DrawMouseOver(CDC* pDC, CRect rect)
{
	SIZE size = g_gbl.GetBitmapSize( IDX_PNG_LISTCTRL_HEADER_SHADOW );
	CDC tmpDC;
	tmpDC.CreateCompatibleDC( pDC );
	tmpDC.SelectObject( g_gbl.GetBitmap( IDX_PNG_LISTCTRL_HEADER_SHADOW ) );
	pDC->StretchBlt( rect.left, rect.bottom-size.cy, rect.Width(), size.cy, &tmpDC, 0, 0, size.cx, size.cy, SRCCOPY );
	tmpDC.DeleteDC();
}

///////////////////////////////////////////////////////////////////////////////
// DrawMouseOut
void CSkinHeaderCtrl::DrawMouseOut(CDC* pDC, CRect rect)
{
	SIZE size = g_gbl.GetBitmapSize( IDX_PNG_LISTCTRL_HEADER_SHADOW );
	CDC tmpDC;
	tmpDC.CreateCompatibleDC(pDC);
	tmpDC.SelectObject( g_gbl.GetBitmap(IDX_PNG_LISTCTRL_HEADER_SHADOW) );
	pDC->StretchBlt(rect.left, rect.bottom-size.cy, rect.Width(), size.cy, &tmpDC, 0, 0, size.cx, size.cy, SRCCOPY);
	tmpDC.DeleteDC();
}

///////////////////////////////////////////////////////////////////////////////
// DrawMouseDown
void CSkinHeaderCtrl::DrawMouseDown(CDC* pDC, CRect rect)
{
	SIZE size = g_gbl.GetBitmapSize( IDX_PNG_LISTCTRL_HEADER_SHADOW ) ;
	CDC tmpDC;
	tmpDC.CreateCompatibleDC(pDC);
	tmpDC.SelectObject( g_gbl.GetBitmap( IDX_PNG_LISTCTRL_HEADER_SHADOW ) );
	pDC->StretchBlt(rect.left, rect.bottom-size.cy, rect.Width(), size.cy, &tmpDC, 0, 0, size.cx, size.cy, SRCCOPY);
	tmpDC.DeleteDC();
}
// JCW_+ 2008.04.12 END
