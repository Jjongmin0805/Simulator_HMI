
// SkinListCtrl.cpp  Version 1.3
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// This code is based on "Neat Stuff to do in List Controls Using Custom Draw"
// by Michael Dunn. See http://www.codeproject.com/listctrl/lvcustomdraw.asp
//
// Thanks to David Patrick for pointing out how to subclass header control
// if CSkinListCtrl is created via Create() instead of via dialog template.
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
#include "SkinListCtrl.h"
#define DEFAULT_CHKBOX_ID		10000		// 동적으로 생성하는 CHECKBOX에 부여 할 ID

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// CSkinListCtrl

CSkinListCtrl::CSkinListCtrl()
{
	m_dwExtendedStyleX      = 0;
	m_bHeaderIsSubclassed   = FALSE;

	m_cr3DFace              = ::GetSysColor(COLOR_3DFACE);
	m_cr3DHighLight         = ::GetSysColor(COLOR_3DHIGHLIGHT);
	m_cr3DShadow            = ::GetSysColor(COLOR_3DSHADOW);
	m_crBtnFace             = /*g_gbl.GetRGB( IDX_RGB_MAIN_MENU );	*/	 RGB(106, 190, 255);
	m_crBtnShadow           = ::GetSysColor(COLOR_BTNSHADOW);
	m_crBtnText             = ::GetSysColor(COLOR_BTNTEXT);
	m_crGrayText            = ::GetSysColor(COLOR_GRAYTEXT);
	m_crHighLight           = RGB(106, 190, 255) ;//g_gbl.GetRGB( IDX_RGB_FONT_LITE_BLUE2 );
	m_crHighLightText       = g_gbl.GetRGB( IDX_RGB_FONT_BLACK );
	m_crWindow              = g_gbl.GetRGB( IDX_RGB_FONT_WHITE );
	m_crWindowText          = ::GetSysColor( COLOR_WINDOWTEXT );
		
	m_bFocusRect			= TRUE;
	m_bResize				= TRUE;
	m_strNoItemMsg			= _T("");
	m_nStatusColumn			= -1;
	m_bUnderLine			= TRUE;
	m_bVerLine				= TRUE;
	m_crUnderLine			= g_gbl.GetRGB( IDX_RGB_FONT_BLACK );
	m_bHeaderTracking		= FALSE;
	m_bHeaderDraging		= FALSE;	
	m_bTracking				= FALSE;
	m_bSort					= TRUE;
	m_nTrackingItem			= -1;
	m_crTracking			= RGB(200, 228, 249); //g_gbl.GetRGB( IDX_RGB_FONT_LITE_BLUE );
	m_pTextFont				= NULL;
	m_hwdParent			    = NULL;
	m_nRowHeight			= 20;

	m_bSort_X = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CSkinListCtrl::~CSkinListCtrl()
{	
}

///////////////////////////////////////////////////////////////////////////////
//
BEGIN_MESSAGE_MAP(CSkinListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CSkinListCtrl)
	ON_NOTIFY_REFLECT_EX(LVN_COLUMNCLICK, OnColumnClick)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_MOUSEWHEEL()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	//}}AFX_MSG_MAP

#ifndef NO_SKINLISTCTRL_TOOL_TIPS
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
#endif
	
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()	
	ON_MESSAGE(WM_CHECKBOX2LIST_MSG, OnCheckbox2Ctrl)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// PreSubclassWindow
void CSkinListCtrl::PreSubclassWindow()
{	
	CListCtrl::PreSubclassWindow();

	// for Dialog based applications, this is a good place
	// to subclass the header control because the OnCreate()
	// function does not get called.

	//ModifyStyle( 0, LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT );
	SetExtendedStyle( LVS_EX_FULLROWSELECT );
	ModifyStyleEx( 0, WS_EX_STATICEDGE );

	SubclassHeaderControl();
}

///////////////////////////////////////////////////////////////////////////////
// OnCreate
int CSkinListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
	{
		ASSERT(FALSE);
		return -1;
	}

	// When the CSkinListCtrl object is created via a call to Create(), instead
	// of via a dialog box template, we must subclass the header control
	// window here because it does not exist when the PreSubclassWindow()
	// function is called.

	SubclassHeaderControl();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// SubclassHeaderControl
void CSkinListCtrl::SubclassHeaderControl()
{
	if( m_bHeaderIsSubclassed )
		return;

	// if the list control has a header control window, then
	// subclass it

	// Thanks to Alberto Gattegno and Alon Peleg젨and their article
	// "A Multiline Header Control Inside a CListCtrl" for easy way
	// to determine if the header control exists.

	CHeaderCtrl* pHeader = GetHeaderCtrl();
	
	if( pHeader )
	{
		VERIFY( m_HeaderCtrl.SubclassWindow( pHeader->m_hWnd ) );
		m_bHeaderIsSubclassed = TRUE;
	}
}

///////////////////////////////////////////////////////////////////////////////
// OnCustomDraw
void CSkinListCtrl::OnCustomDraw( NMHDR* pNMHDR, LRESULT* pResult )
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec);
	int nSubItem = pLVCD->iSubItem;

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	if (pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if (pLVCD->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
	{
		// This is the prepaint stage for a subitem. Here's where we set the
		// item's text and background colors. Our return value will tell
		// Windows to draw the subitem itself, but it will use the new colors
		// we set here.

		*pResult = CDRF_SKIPDEFAULT;	// We've painted everything.

		SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) pLVCD->nmcd.lItemlParam;
		if( !pXLCD )
			return;
		
		COLORREF crText  = pXLCD[nSubItem].crText;
		COLORREF crBkgnd = pXLCD[nSubItem].crBackground;
		
		if( !pXLCD[0].bEnabled )
			crText = m_crGrayText;

		// store the colors back in the NMLVCUSTOMDRAW struct
		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;

		CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);
		CRect rect;
		GetSubItemRect( nItem, nSubItem, LVIR_BOUNDS, rect );

		// CHECKBOX
		if( pXLCD && ( pXLCD[ nSubItem ].nCheckedState != -1 ) )
		{
			if (nItem != 0)
				rect.top += 1;
			DrawCheckbox( nItem, nSubItem, pDC, crText, crBkgnd, rect, pXLCD );
		}
		// DEFAULT
		else
		{
			if(nItem != 0 )
				rect.top += 1;
			rect.left += DrawImage( nItem, nSubItem, pDC, crText, crBkgnd, rect, pXLCD );
			DrawText( nItem, nSubItem, pDC, crText, crBkgnd, rect, pXLCD );
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// GetDrawColors
void CSkinListCtrl::GetDrawColors(int nItem,
							   int nSubItem,
							   COLORREF& colorText,
							   COLORREF& colorBkgnd)
{
	DWORD dwStyle    = GetStyle();
	DWORD dwExStyle  = GetExtendedStyle();

	COLORREF crText  = colorText;
	COLORREF crBkgnd = colorBkgnd;

	if (GetItemState(nItem, LVIS_SELECTED) && m_bFocusRect)
	{
		if (dwExStyle & LVS_EX_FULLROWSELECT)
		{
			// selected?  if so, draw highlight background
			crText  = m_crHighLightText;
			crBkgnd = m_crHighLight;

			// has focus?  if not, draw gray background
			if (m_hWnd != ::GetFocus())
			{
				if (dwStyle & LVS_SHOWSELALWAYS)
				{
					crText  = m_crWindowText;
					crBkgnd = m_crBtnFace;
				}
				else
				{
					crText  = colorText;
					crBkgnd = colorBkgnd;
				}
			}
		}
	}

	// 해당 Item이 Tracking Item과 동일하면 배경 색을 Tracking Color로 저장한다.
	if( m_nTrackingItem >= 0 )
	{
		if( nItem == m_nTrackingItem )
			crBkgnd = m_crTracking;
	}

	colorText = crText;
	colorBkgnd = crBkgnd;
}

CSize CSkinListCtrl::GetCheckBoxSize()
{
	CBitmap bmp;
	bmp.LoadMappedBitmap(m_nRes_CheckBox_Nor);

	BITMAP	bitmap;
	SIZE     sizeBitmap;
	sizeBitmap.cx = 0;
	sizeBitmap.cy = 0;

	bmp.GetBitmap(&bitmap);
	sizeBitmap.cx = bitmap.bmWidth;
	sizeBitmap.cy = bitmap.bmHeight;

	return sizeBitmap;
}
///////////////////////////////////////////////////////////////////////////////
// DrawCheckbox
void CSkinListCtrl::DrawCheckbox( int nItem,
								  int nSubItem,
								  CDC *pDC,
								  COLORREF crText,
								  COLORREF crBkgnd,
								  CRect& rect,
								  SkinListCtrlDATA *pXLCD)
{
	ASSERT(pDC);
	ASSERT(pXLCD);

	CFont *pOldFont = pDC->SelectObject( m_pTextFont );
	CPen  newPen( PS_SOLID, 1, m_crUnderLine );
	CPen *pOldPen = pDC->SelectObject( &newPen );

	GetDrawColors( nItem, nSubItem, crText, crBkgnd );
	pDC->FillSolidRect( &rect, crBkgnd );

	if( m_bUnderLine )
	{
		if( nItem == 0 )
		{
			pDC->MoveTo( rect.left-1, rect.top );
			pDC->LineTo( rect.right+1, rect.top );
		}
		
		pDC->MoveTo( rect.left-1, rect.bottom );
		pDC->LineTo( rect.right+1, rect.bottom );
	}

	if( m_bVerLine )
	{
		pDC->MoveTo( rect.right-1, rect.top );
		pDC->LineTo( rect.right-1, rect.bottom );
	}
		
	CRect rectBtn;
	SIZE sizeBtn = GetCheckBoxSize();// .GetBitmapSize(IDX_PNG_CHK_DEFAULT);
	rectBtn.left   = rect.left + 5;
	rectBtn.top    = rect.top  + 2;
	rectBtn.right  = rectBtn.left + sizeBtn.cx;
	rectBtn.bottom = rectBtn.top  + sizeBtn.cy;

	CString str( _T("") );
	str = GetItemText( nItem, nSubItem );

	if (str.IsEmpty())
	{
		// center the checkbox
		rectBtn.top = rect.top + rect.Height() / 2 - sizeBtn.cy / 2;
		rectBtn.left  = rect.left + rect.Width() / 2 - sizeBtn.cx / 2;
		rectBtn.right = rectBtn.left + sizeBtn.cx;
	}

	int i;
	for( i = 0; i < m_carrCheckData.GetCount(); i++ )
	{
		CCheckData *pCheckData = m_carrCheckData.GetAt( i );
		if( pCheckData )
		{
			if( pCheckData->m_nItem == nItem && pCheckData->m_nSubItem == nSubItem )
			{				
				pCheckData->m_pCheckbox->MoveWindow( rectBtn.left, rectBtn.top, sizeBtn.cx, sizeBtn.cy, TRUE );
				pCheckData->m_pCheckbox->ShowWindow( SW_SHOW );
				pCheckData->m_pCheckbox->Invalidate();
				break;
			}
		}
	}

	if( !str.IsEmpty() )
	{
		pDC->SetBkMode( TRANSPARENT );
		pDC->SetTextColor( crText );
		pDC->SetBkColor( crBkgnd );
		
		CRect textrect;
		textrect = rect;
		textrect.left = rectBtn.right + 5;

		pDC->DrawText( str, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE );
	}

	pDC->SelectObject( pOldFont );
	pDC->SelectObject( pOldPen  );
	newPen.DeleteObject();
}

///////////////////////////////////////////////////////////////////////////////
// DrawImage
int CSkinListCtrl::DrawImage( int nItem,
							  int nSubItem,
							  CDC* pDC,
							  COLORREF crText,
							  COLORREF crBkgnd,
							  CRect rect,
  							  SkinListCtrlDATA *pXLCD)
{
	GetDrawColors(nItem, nSubItem, crText, crBkgnd);
	rect.left +=  1;
	pDC->FillSolidRect(&rect, crBkgnd);

	CPen newPen(PS_SOLID,1, m_crUnderLine);
	CPen *pOldPen = pDC->SelectObject(&newPen);	
	
	if( m_bUnderLine )
	{
		if( nItem == 0 )
		{
			pDC->MoveTo( rect.left-1, rect.top );
			pDC->LineTo( rect.right+1, rect.top );
		}

		pDC->MoveTo( rect.left-1, rect.bottom );
		pDC->LineTo( rect.right+1, rect.bottom );
	}

	if( m_bVerLine )
	{
		pDC->MoveTo( rect.right -1, rect.top );
		pDC->LineTo( rect.right -1, rect.bottom );
	}

	int nWidth = 0;

	CImageList* pImageList = GetImageList(LVSIL_NORMAL);
	if(pImageList)
	{
		SIZE sizeImage;
		sizeImage.cx = sizeImage.cy = 0;
		IMAGEINFO info;

		int nImage = -1;
		if (pXLCD)
			nImage = pXLCD[nSubItem].nImage;

		if (nImage == -1)
			return 0;

		if (pImageList->GetImageInfo(nImage, &info))
		{
			sizeImage.cx = info.rcImage.right - info.rcImage.left;
			sizeImage.cy = info.rcImage.bottom - info.rcImage.top;
		}
		
		if (nImage >= 0)
		{
			if (rect.Width() > 0)
			{
				if( pXLCD[nSubItem].bImageCenter )
					rect.left += rect.Width()/2-sizeImage.cx/2;
				else
					rect.left += m_HeaderCtrl.GetSpacing();

				POINT pt;					
				pt.y = rect.CenterPoint().y - (sizeImage.cy >> 1);
				pt.x = rect.left;
				
				SIZE size;
				size.cx = rect.Width() < sizeImage.cx ? rect.Width() : sizeImage.cx;
				size.cy = rect.Height() < sizeImage.cy ? rect.Height() : sizeImage.cy;

				COLORREF rgb = pImageList->GetBkColor();	// save image list background color					
				pImageList->SetBkColor(crBkgnd);			// set image list background color				
				pImageList->DrawIndirect(pDC, nImage, pt, size, CPoint(0, 0));
				pImageList->SetBkColor(rgb);
			
				if( pXLCD[nSubItem].bImageCenter )
					nWidth = rect.right;
				else
					nWidth = sizeImage.cx + m_HeaderCtrl.GetSpacing();
			}
		}
	}
	pDC->SelectObject(pOldPen);
	newPen.DeleteObject();

	return nWidth;
}

///////////////////////////////////////////////////////////////////////////////
// DrawText
void CSkinListCtrl::DrawText( int nItem,
							  int nSubItem,
							  CDC *pDC,
							  COLORREF crText,
							  COLORREF crBkgnd,
							  CRect& rect,
							  SkinListCtrlDATA *pXLCD)
{
	ASSERT(pDC);
	ASSERT(pXLCD);

	CRect rcNew;
	rcNew = rect;

	CFont *pOldFont = pDC->SelectObject(m_pTextFont);
	CPen newPen(PS_SOLID, 1, m_crUnderLine);
	CPen *pOldPen = pDC->SelectObject(&newPen);

	if( nSubItem == m_nStatusColumn )
	{
		COLORREF crTemp = m_crWindow;
		GetDrawColors(nItem, nSubItem, crText, crTemp);

		pDC->FillSolidRect(&rect, crTemp);
		rcNew.top	+= 1;
		rcNew.left	+= 2;
		rcNew.right	-= 2;
		rcNew.bottom-= 2;
		pDC->FillSolidRect(&rcNew, crBkgnd);
	}
	else
	{
		GetDrawColors(nItem, nSubItem, crText, crBkgnd);
		rect.left += 1;
		pDC->FillSolidRect(&rect, crBkgnd);
	}

	CString str(_T(""));
	str = GetItemText(nItem, nSubItem);	
	if (!str.IsEmpty())
	{
		// get text justification
		/*HDITEM hditem;
		hditem.mask = HDI_FORMAT;
		m_HeaderCtrl.GetItem(nSubItem, &hditem);
		int nFmt = hditem.fmt & HDF_JUSTIFYMASK;*/

		int nFmt = HDF_CENTER;		
		
		pXLCD = (SkinListCtrlDATA *)CListCtrl::GetItemData(nItem);
		if( pXLCD )	nFmt = pXLCD[ nSubItem ].nTextLeftmode;
		
		UINT nFormat = DT_VCENTER | DT_SINGLELINE;
		
		if (nFmt == HDF_CENTER)
		{
			nFormat |= DT_CENTER;
		}
		else if (nFmt == HDF_LEFT)
		{
			nFormat |= DT_LEFT;
			rcNew.left += 5;
		}
		else
		{
			nFormat |= DT_RIGHT;
			rcNew.right -= 5;
		}

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(crText);
		pDC->SetBkColor(crBkgnd);
		rcNew.OffsetRect(0, -1);
		pDC->DrawText(str, &rcNew, nFormat);
	}

	if( m_bUnderLine )
	{
		if( nItem == 0 )
		{
			pDC->MoveTo( rect.left-1, rect.top );
			pDC->LineTo( rect.right+1, rect.top );
		}
		
		pDC->MoveTo( rect.left-1, rect.bottom );
		pDC->LineTo( rect.right+1, rect.bottom );
	}

	if( m_bVerLine )
	{
		pDC->MoveTo( rect.right - 1, rect.top);
		pDC->LineTo( rect.right - 1, rect.bottom );
	}

	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
	newPen.DeleteObject();
}

///////////////////////////////////////////////////////////////////////////////
// GetSubItemRect
BOOL CSkinListCtrl::GetSubItemRect( int nItem,
									int nSubItem,
									int nArea,
									CRect& rect)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	BOOL bRC = CListCtrl::GetSubItemRect(nItem, nSubItem, nArea, rect);

	// if nSubItem == 0, the rect returned by CListCtrl::GetSubItemRect
	// is the entire row, so use left edge of second subitem
	if (nSubItem == 0)
	{
		if (GetColumns() > 1)
		{
			CRect rect1;
			bRC = GetSubItemRect(nItem, 1, LVIR_BOUNDS, rect1);
			if(rect1.left != 0)
				rect.right = rect1.left;
		}
	}

	// 마우스가 올라왔을때 Grid line이 지워지는 문제를 보완
	//rect.bottom -= 1;

	return bRC;
}

///////////////////////////////////////////////////////////////////////////////
// OnLButtonDown
void CSkinListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
//	TRACE(_T("in CSkinListCtrl::OnLButtonDown\n"));

	//
	int nItem = -1;
	CRect rect;
	for(int i=0; i<GetItemCount(); i++)
	{
		if (CListCtrl::GetItemRect(i, &rect, LVIR_BOUNDS))
		{
			if (rect.PtInRect(point))
			{
				nItem = i;
				break;
			}
		}
	}

	if( nItem != -1 )
	{
		SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
		if (!pXLCD)
			return;

		if( !pXLCD[0].bEnabled )
			return;		

		// check if a subitem checkbox was clicked
		CRect rect;
		int nSubItem = -1;

		for( int i = 0; i < GetColumns(); i++ )
		{
			GetSubItemRect(nItem, i, LVIR_BOUNDS, rect);
			if( rect.PtInRect( point ) )
			{
				nSubItem = i;
				break;
			}
		}	
	}

	CListCtrl::OnLButtonDown(nFlags, point);
}


///////////////////////////////////////////////////////////////////////////////
// OnPaint
void CSkinListCtrl::OnPaint()
{

	Default();

	if(GetItemCount() <= 0)
	{
		CDC* pDC = GetDC();
		if(!pDC) return;
		int nSavedDC = pDC->SaveDC();

		CRect rc;
		GetWindowRect(&rc);
		ScreenToClient(&rc);
		CHeaderCtrl* pHC = GetHeaderCtrl();
		if (pHC != NULL)
		{
			CRect rcH;
			pHC->GetItemRect(0, &rcH);
			rc.top += rcH.bottom;
		}

		CString strText = m_strNoItemMsg;
		COLORREF crText = m_crWindowText;
		COLORREF crBkgnd = m_crWindow;		
				
		pDC->SetTextColor( crText );
		pDC->SetBkColor( crBkgnd );
		pDC->SelectObject( m_pTextFont );
		pDC->FillSolidRect( &rc, crBkgnd );

		rc.top += 10;
		pDC->DrawText(strText, -1, rc, DT_CENTER | DT_WORDBREAK | DT_NOPREFIX | DT_NOCLIP);

		pDC->RestoreDC(nSavedDC);
		ReleaseDC(pDC);
	}
	else
	{
		CDC* pDC = GetDC();

		CRect rc, rect;
		GetWindowRect(&rc);
		ScreenToClient(&rc);

		CListCtrl::GetItemRect( GetItemCount() - 1, &rect, LVIR_BOUNDS );
		COLORREF cfBkgnd = m_crWindow;
		rc.top = rect.bottom;
		pDC->FillSolidRect( &rc, cfBkgnd );

		GetWindowRect(&rc);
		ScreenToClient(&rc);
		rc.left = rect.right;
		pDC->FillSolidRect( &rc, cfBkgnd );
		ReleaseDC(pDC);
	}

	m_HeaderCtrl.RedrawWindow();
}

///////////////////////////////////////////////////////////////////////////////
// OnEraseBkgnd
BOOL CSkinListCtrl::OnEraseBkgnd(CDC* pDC) 
{	
	// TODO: Add your message handler code here and/or call default	
#if 0
	CRect clip;
	m_HeaderCtrl.GetWindowRect(&clip);		// get rect of the control
	ScreenToClient(&clip);
	pDC->ExcludeClipRect(&clip);
	pDC->GetClipBox(&clip);	
	pDC->FillSolidRect(clip, m_crWindow);
	return TRUE;
#else
	return FALSE;
#endif
	return CListCtrl::OnEraseBkgnd(pDC);
}

///////////////////////////////////////////////////////////////////////////////
// InsertItem
int CSkinListCtrl::InsertItem(const LVITEM* pItem)
{
	ASSERT(pItem->iItem >= 0);
	if (pItem->iItem < 0)
		return -1;

	int index = CListCtrl::InsertItem(pItem);

	if (index < 0)
		return index;

	SkinListCtrlDATA *pXLCD = new SkinListCtrlDATA [GetColumns()];
	ASSERT(pXLCD);
	if (!pXLCD)
		return -1;

	pXLCD[0].crText       = m_crWindowText;
	pXLCD[0].crBackground = m_crWindow;
	pXLCD[0].nImage       = pItem->iImage;

	CListCtrl::SetItemData(index, (DWORD_PTR) pXLCD);

	return index;
}

///////////////////////////////////////////////////////////////////////////////
// InsertItem
int CSkinListCtrl::InsertItem(int nItem, LPCTSTR lpszItem, int nFmt)
{
	ASSERT(nItem >= 0);
	if (nItem < 0)
		return -1;

	return InsertItem(nItem,
					  lpszItem,
					  m_crWindowText,
					  m_crWindow,
					  nFmt );
}

///////////////////////////////////////////////////////////////////////////////
// InsertItem
int CSkinListCtrl::InsertItem(int nItem, LPCTSTR lpszItem, COLORREF crText, COLORREF crBackground, int nFmt )						
{
	ASSERT(nItem >= 0);
	if (nItem < 0)
		return -1;

	int index = CListCtrl::InsertItem(nItem, lpszItem);

	if (index < 0)
		return index;

	SkinListCtrlDATA *pXLCD = new SkinListCtrlDATA [GetColumns()];
	ASSERT(pXLCD);
	if (!pXLCD)
		return -1;

	pXLCD[0].crText        = crText;
	pXLCD[0].crBackground  = crBackground;
	pXLCD[0].nTextLeftmode = nFmt;
	CListCtrl::SetItemData(index, (DWORD_PTR)pXLCD);

	return index;
}

///////////////////////////////////////////////////////////////////////////////
// SetItem
int CSkinListCtrl::SetItem(const LVITEM* pItem)
{
	ASSERT(pItem->iItem >= 0);
	if (pItem->iItem < 0)
		return -1;

	BOOL rc = CListCtrl::SetItem(pItem);

	if (!rc)
		return FALSE;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(pItem->iItem);
	if (pXLCD)
	{
		pXLCD[pItem->iSubItem].nImage = pItem->iImage;
		UpdateSubItem(pItem->iItem, pItem->iSubItem);
		rc = TRUE;
	}
	else
	{
		rc = FALSE;
	}

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
// GetItemImage
int CSkinListCtrl::GetItemImage(int nItem, int nSubItem)
{
	int nImage = -1;

	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return nImage;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return nImage;	

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (pXLCD)
		nImage = pXLCD[nSubItem].nImage;

	return nImage;
}


BOOL CSkinListCtrl::SetItemImage(int nItem, int nSubItem, int nImage, BOOL bImageCenter/*=FALSE*/)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	BOOL rc = TRUE;

	if (nItem < 0)
		return FALSE;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (pXLCD)
	{
		// 기존 데이터와 비교후 틀리면 업데이트
		if( pXLCD[nSubItem].nImage == nImage && 
			pXLCD[nSubItem].bImageCenter == bImageCenter )
			return rc;

		pXLCD[nSubItem].nImage = nImage;
		pXLCD[nSubItem].bImageCenter = bImageCenter;
	}

	UpdateSubItem(nItem, nSubItem);

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
// SetItemText
BOOL CSkinListCtrl::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText, int nFmt)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;
	
	CString	szText(_T(""));
	szText = GetItemText(nItem, nSubItem);

	// 기존 데이터와 비교후 틀리면 업데이트
	if( !szText.Compare( lpszText ) )
		return 0;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if( pXLCD )	pXLCD[ nSubItem ].nTextLeftmode = nFmt;	
	
	BOOL rc = CListCtrl::SetItemText(nItem, nSubItem, lpszText);
	UpdateSubItem(nItem, nSubItem);

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
// SetItemText
//
// This function will set the text and colors for a subitem.  If lpszText
// is NULL, only the colors will be set.  If a color value is -1, the display
// color will be set to the default Windows color.
//
BOOL CSkinListCtrl::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText,
					COLORREF crText, COLORREF crBackground, int nFmt)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	BOOL rc = TRUE;

	if (nItem < 0)
		return FALSE;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);

	// 기존 데이터와 비교후 틀리면 업데이트
	//if( pXLCD[nSubItem].crBackground == crBackground &&	pXLCD[nSubItem].crText == crText )
	//	return FALSE;	

	if( lpszText )
		rc = CListCtrl::SetItemText( nItem, nSubItem, lpszText );
	
	if (pXLCD)
	{
		pXLCD[nSubItem].crText        = (crText == -1) ? m_crWindowText : crText;
		pXLCD[nSubItem].crBackground  = (crBackground == -1) ? m_crWindow : crBackground;
		pXLCD[nSubItem].nTextLeftmode = nFmt;
	}

	UpdateSubItem( nItem, nSubItem );
	return rc;
}

///////////////////////////////////////////////////////////////////////////////
// SetItemTextColor
//
BOOL CSkinListCtrl::SetItemTextColor(int nItem, int nSubItem, COLORREF crText, COLORREF crBackground)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	if (nItem < 0)
		return FALSE;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);

	// 기존 데이터와 비교후 틀리면 업데이트
	if( pXLCD[nSubItem].crBackground == crBackground &&
		pXLCD[nSubItem].crText == crText )
		return FALSE;

	if (pXLCD)
	{
		pXLCD[nSubItem].crText       = (crText == -1) ? m_crWindowText : crText;
		pXLCD[nSubItem].crBackground = (crBackground == -1) ? m_crWindow : crBackground;
	}

	UpdateSubItem(nItem, nSubItem);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// DeleteItem
BOOL CSkinListCtrl::DeleteItem(int nItem)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());

	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	
	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (pXLCD)
		delete [] pXLCD;
	
	CListCtrl::SetItemData(nItem, 0);
	return CListCtrl::DeleteItem(nItem);
}


///////////////////////////////////////////////////////////////////////////////
// DeleteAllColumns
void CSkinListCtrl::DeleteAllColumns()
{
	int nCnt = GetColumns();
	DeleteAllItems();
	
	for( int i = 0; i < nCnt; i++ )
	{
		DeleteColumn( 0 );
	}

	DeleteCheckbox();
}


void CSkinListCtrl::DeleteCheckbox()
{
	int i;
	for( i = 0; i < m_carrCheckData.GetCount(); i++ )
	{
		CCheckData *pCheckData = m_carrCheckData.GetAt( i );
		
		if( pCheckData )
		{
			if( pCheckData->m_pCheckbox )
			{
				delete pCheckData->m_pCheckbox;
				 pCheckData->m_pCheckbox = NULL;
			}

			delete pCheckData;
			pCheckData = NULL;
		}
	}

	m_carrCheckData.RemoveAll();
	m_carrCheckData.FreeExtra();	
}


void CSkinListCtrl::HideCheckbox()
{
	int i;
	for( i = 0; i < m_carrCheckData.GetCount(); i++ )
	{
		CCheckData *pCheckData = m_carrCheckData.GetAt( i );
		if( pCheckData )
		{
			pCheckData->m_pCheckbox->ShowWindow( SW_HIDE );
			pCheckData->m_pCheckbox->Invalidate();
		}
	}	
}

void CSkinListCtrl::HideCheckbox2Select(int nRow, int nCol)
{
	int i;
	for (i = 0; i < m_carrCheckData.GetCount(); i++)
	{
		CCheckData *pCheckData = m_carrCheckData.GetAt(i);
		if (pCheckData->m_nItem == nRow && pCheckData->m_nSubItem == nCol)
		{
			pCheckData->m_pCheckbox->ShowWindow(SW_HIDE);
			pCheckData->m_pCheckbox->Invalidate();
		}
	}
}

void CSkinListCtrl::ShowCheckbox2Select(int nRow, int nCol)
{
	int i;
	for (i = 0; i < m_carrCheckData.GetCount(); i++)
	{
		CCheckData *pCheckData = m_carrCheckData.GetAt(i);
		if (pCheckData->m_nItem == nRow && pCheckData->m_nSubItem == nCol)
		{
			pCheckData->m_pCheckbox->ShowWindow(SW_SHOW);
			pCheckData->m_pCheckbox->Invalidate();
		}
	}
}



///////////////////////////////////////////////////////////////////////////////
// DeleteAllItems
BOOL CSkinListCtrl::DeleteAllItems()
{
	int n = GetItemCount();
	for (int i = 0; i < n; i++)
	{
		SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(i);
		if (pXLCD)
			delete [] pXLCD;
		CListCtrl::SetItemData(i, 0);
	}

	DeleteCheckbox();
	Refresh();

	return CListCtrl::DeleteAllItems();
}

///////////////////////////////////////////////////////////////////////////////
// OnDestroy
void CSkinListCtrl::OnDestroy()
{
	DeleteCheckbox();

	int n = GetItemCount();
	for (int i = 0; i < n; i++)
	{
		SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(i);
		if( pXLCD )
			delete [] pXLCD;
		
		CListCtrl::SetItemData(i, 0);
	}

	CListCtrl::OnDestroy();
}

///////////////////////////////////////////////////////////////////////////////
// GetEnabled
//
// Note that GetEnabled and SetEnabled only Get/Set the enabled flag from
// subitem 0, since this is a per-row flag.
//
BOOL CSkinListCtrl::GetEnabled(int nItem)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	return pXLCD[0].bEnabled;
}

///////////////////////////////////////////////////////////////////////////////
// SetEnabled
BOOL CSkinListCtrl::SetEnabled(int nItem, BOOL bEnable)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	pXLCD[0].bEnabled = bEnable;

	CRect rect;
	GetItemRect(nItem, &rect, LVIR_BOUNDS);
	InvalidateRect(&rect);
	UpdateWindow();

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// SetBold
BOOL CSkinListCtrl::SetBold(int nItem, int nSubItem, BOOL bBold)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	// update bold flag
	pXLCD[nSubItem].bBold = bBold;
	UpdateSubItem(nItem, nSubItem);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// GetBold
BOOL CSkinListCtrl::GetBold(int nItem, int nSubItem)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	// update bold flag
	return pXLCD[nSubItem].bBold;
}

///////////////////////////////////////////////////////////////////////////////

void CSkinListCtrl::UpdateDate(int nItem, int nSubItem, CTime time, COLORREF crText, COLORREF crBackground)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	
	if ((nItem < 0) || nItem >= GetItemCount())
		return;
	
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
		return;

	// 기존 데이터와 비교후 틀리면 업데이트
	if( pXLCD[nSubItem].crBackground == crBackground &&	pXLCD[nSubItem].crText == crText )
		return;
	
	pXLCD[nSubItem].crText       = (crText == -1) ? m_crWindowText : crText;
	pXLCD[nSubItem].crBackground = (crBackground == -1) ? m_crWindow : crBackground;	

	UpdateSubItem( nItem, nSubItem );
}

///////////////////////////////////////////////////////////////////////////////
// SetCurSel
BOOL CSkinListCtrl::SetCurSel( int nItem )
{
	int nBefore = SetSelectionMark(nItem);
	if (nBefore >= 0 )             // 기존것 unselect
		SetItemState(nBefore, NULL, LVIS_SELECTED | LVIS_FOCUSED);


출처: https://chondaddy.tistory.com/11 [촌돌애비 요지경]

	return SetItemState( nItem, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED );
}

///////////////////////////////////////////////////////////////////////////////
// GetCurSel - returns selected item number, or -1 if no item selected
//
// Note:  for single-selection lists only
//
int CSkinListCtrl::GetCurSel()
{
	POSITION pos = GetFirstSelectedItemPosition();	
	int nSelectedItem = -1;
	
	if (pos != NULL)
		nSelectedItem = GetNextSelectedItem(pos);
	
	return nSelectedItem;
}

///////////////////////////////////////////////////////////////////////////////
// UpdateSubItem
void CSkinListCtrl::UpdateSubItem(int nItem, int nSubItem)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	
	if ((nItem < 0) || nItem >= GetItemCount())
		return;
	
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return;

	CRect rect;
	if (nSubItem == -1)
		GetItemRect(nItem, &rect, LVIR_BOUNDS);
	else
		GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);

	//Invalidate( FALSE );
	InvalidateRect(&rect); //깜박임 제거
	//UpdateWindow();
}

///////////////////////////////////////////////////////////////////////////////
// GetColumns
int CSkinListCtrl::GetColumns()
{
	return GetHeaderCtrl()->GetItemCount();
}

///////////////////////////////////////////////////////////////////////////////
// GetItemData
//
// The GetItemData and SetItemData functions allow for app-specific data
// to be stored, by using an extra field in the SkinListCtrlDATA struct.
//
DWORD CSkinListCtrl::GetItemData(int nItem)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return 0;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return 0;
	}

	return pXLCD->dwItemData;
}

///////////////////////////////////////////////////////////////////////////////
// SetItemData
BOOL CSkinListCtrl::SetItemData(int nItem, DWORD dwData)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	pXLCD->dwItemData = dwData;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// GetHeaderCheckedState
//
// The GetHeaderCheckedState and SetHeaderCheckedState may be used to toggle
// the checkbox in a column header.
//     0 = no checkbox
//     1 = unchecked
//     2 = checked
//
int CSkinListCtrl::GetHeaderCheckedState(int nSubItem)
{
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return -1;

	HDITEM hditem;

	// use the image index (0 or 1) to indicate the checked status
	hditem.mask = HDI_IMAGE;
	m_HeaderCtrl.GetItem(nSubItem, &hditem);
	return hditem.iImage;
}

///////////////////////////////////////////////////////////////////////////////
// SetHeaderCheckedState
BOOL CSkinListCtrl::SetHeaderCheckedState(int nSubItem, int nCheckedState)
{
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;
	ASSERT(nCheckedState == 0 || nCheckedState == 1 || nCheckedState == 2);

	HDITEM hditem;

	hditem.mask = HDI_IMAGE;
	hditem.iImage = nCheckedState;
	m_HeaderCtrl.SetItem(nSubItem, &hditem);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// OnColumnClick
BOOL CSkinListCtrl::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLISTVIEW* pnmlv = (NMLISTVIEW*)pNMHDR;

	int nSubItem = pnmlv->iSubItem;
	int nCheckedState = GetHeaderCheckedState(nSubItem);
		
	if (nCheckedState != SKINHEADERCTRL_NO_IMAGE)
	{
		nCheckedState = (nCheckedState == 1) ? 2 : 1;
		SetHeaderCheckedState(nSubItem, nCheckedState);

		m_HeaderCtrl.UpdateWindow();		
	}

	BOOL bRet = CheckSortData( nSubItem );
	if( bRet && m_bSort_X == FALSE)
	{
		m_bSort = !m_bSort;
		Sort( nSubItem, m_bSort );
	}

	*pResult = 0;
	return FALSE;		// return FALSE to send message to parent also -
						// NOTE:  MSDN documentation is incorrect
}


///////////////////////////////////////////////////////////////////////////////
// OnSysColorChange
void CSkinListCtrl::OnSysColorChange()
{
	CListCtrl::OnSysColorChange();

	m_cr3DFace        = ::GetSysColor(COLOR_3DFACE);
	m_cr3DHighLight   = ::GetSysColor(COLOR_3DHIGHLIGHT);
	m_cr3DShadow      = ::GetSysColor(COLOR_3DSHADOW);
	m_crBtnFace       = RGB(240,0,0);//::GetSysColor(COLOR_BTNFACE);
	m_crBtnShadow     = ::GetSysColor(COLOR_BTNSHADOW);
	m_crBtnText       = ::GetSysColor(COLOR_BTNTEXT);
	m_crGrayText      = ::GetSysColor(COLOR_GRAYTEXT);
	m_crHighLight     = RGB(245,245,245);//::GetSysColor(COLOR_HIGHLIGHT);//RGB(220,220,250);//
	m_crHighLightText = RGB(140,140,140);//::GetSysColor(COLOR_HIGHLIGHTTEXT);//RGB(0,0,0);//
	m_crWindow        = RGB(255,255,255);//::GetSysColor(COLOR_WINDOW);
	m_crWindowText    = ::GetSysColor(COLOR_WINDOWTEXT);

}


void CSkinListCtrl::SetLButtonDown(int nStartItem, int nStartSubItem)
{
	BOOL bFind = FALSE;

	int nCntItem    = GetItemCount();
	int nCntSubItem = GetColumns();
	int i = nStartItem;
	int k = nStartSubItem + 1;
	
	for( ; i<nCntItem; i++, k=0 )
	{
		for(; k<nCntSubItem; k++)
		{
			SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *)CListCtrl::GetItemData(i);
			if( pXLCD )
			{				
				CRect rc;
				GetSubItemRect(i, k, LVIR_BOUNDS, rc);
				CPoint pt(rc.left+rc.Width()/2, rc.top+rc.Height()/2);
				PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));
				bFind = TRUE;

				return;
			}
		}
	}
}


#ifndef NO_SKINLISTCTRL_TOOL_TIPS

///////////////////////////////////////////////////////////////////////////////
// OnToolHitTest
INT_PTR CSkinListCtrl::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
{
	LVHITTESTINFO lvhitTestInfo;
	
	lvhitTestInfo.pt = point;
	
	int nItem = ListView_SubItemHitTest(this->m_hWnd, &lvhitTestInfo);
	int nSubItem = lvhitTestInfo.iSubItem;
//	TRACE(_T("in CToolTipListCtrl::OnToolHitTest: %d,%d\n"), nItem, nSubItem);

	UINT nFlags = lvhitTestInfo.flags;

	// nFlags is 0 if the SubItemHitTest fails
	// Therefore, 0 & <anything> will equal false
	if (nFlags & LVHT_ONITEMLABEL)
	{
		// If it did fall on a list item,
		// and it was also hit one of the
		// item specific subitems we wish to show tool tips for
		
		// get the client (area occupied by this control
		RECT rcClient;
		GetClientRect(&rcClient);
		
		// fill in the TOOLINFO structure
		pTI->hwnd = m_hWnd;
		pTI->uId = (UINT) (nItem * 1000 + nSubItem + 1);
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		pTI->rect = rcClient;
		
		return (INT_PTR)pTI->uId;	// By returning a unique value per listItem,
									// we ensure that when the mouse moves over another
									// list item, the tooltip will change
	}
	else
	{
		//Otherwise, we aren't interested, so let the message propagate
		return -1;
	}
}

///////////////////////////////////////////////////////////////////////////////
// OnToolTipText
BOOL CSkinListCtrl::OnToolTipText(UINT /*id*/, NMHDR * pNMHDR, LRESULT * pResult)
{
	UINT_PTR nID = pNMHDR->idFrom;
//	TRACE(_T("in CSkinListCtrl::OnToolTipText: id=%d\n"), nID);
	
	// check if this is the automatic tooltip of the control
	if (nID == 0) 
		return TRUE;	// do not allow display of automatic tooltip,
						// or our tooltip will disappear
	
	// handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	
	*pResult = 0;
	
	// get the mouse position
	const MSG* pMessage;
	pMessage = GetCurrentMessage();
	ASSERT(pMessage);
	CPoint pt;
	pt = pMessage->pt;		// get the point from the message
	ScreenToClient(&pt);	// convert the point's coords to be relative to this control
	
	// see if the point falls onto a list item
	
	LVHITTESTINFO lvhitTestInfo;
	
	lvhitTestInfo.pt = pt;
	
	int nItem = SubItemHitTest(&lvhitTestInfo);
	int nSubItem = lvhitTestInfo.iSubItem;
	
	UINT nFlags = lvhitTestInfo.flags;
	
	// nFlags is 0 if the SubItemHitTest fails
	// Therefore, 0 & <anything> will equal false
	if (nFlags & LVHT_ONITEMLABEL)
	{
		// If it did fall on a list item,
		// and it was also hit one of the
		// item specific subitems we wish to show tooltips for
		
		CString strToolTip;
		strToolTip = _T("");

		SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
		if (pXLCD)
		{
			strToolTip = pXLCD[nSubItem].strToolTip;
		}

		if (!strToolTip.IsEmpty())
		{
			// If there was a CString associated with the list item,
			// copy it's text (up to 80 characters worth, limitation 
			// of the TOOLTIPTEXT structure) into the TOOLTIPTEXT 
			// structure's szText member
			
#ifndef _UNICODE
			if (pNMHDR->code == TTN_NEEDTEXTA)
				lstrcpyn(pTTTA->szText, strToolTip, 80);
			else
				_mbstowcsz(pTTTW->szText, strToolTip, 80);
#else
			if (pNMHDR->code == TTN_NEEDTEXTA)
				_wcstombsz(pTTTA->szText, strToolTip, 80);
			else
				lstrcpyn(pTTTW->szText, strToolTip, 80);
#endif
			return FALSE;	 // we found a tool tip,
		}
	}
	
	return FALSE;	// we didn't handle the message, let the 
					// framework continue propagating the message
}

///////////////////////////////////////////////////////////////////////////////
// SetItemToolTipText
BOOL CSkinListCtrl::SetItemToolTipText(int nItem, int nSubItem, LPCTSTR lpszToolTipText)
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return FALSE;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (!pXLCD)
	{
		return FALSE;
	}

	pXLCD[nSubItem].strToolTip = lpszToolTipText;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// GetItemToolTipText
CString CSkinListCtrl::GetItemToolTipText(int nItem, int nSubItem)
{
	CString strToolTip;
	strToolTip = _T("");

	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return strToolTip;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if ((nSubItem < 0) || nSubItem >= GetColumns())
		return strToolTip;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
	if (pXLCD)
	{
		strToolTip = pXLCD[nSubItem].strToolTip;
	}

	return strToolTip;
}

///////////////////////////////////////////////////////////////////////////////
// DeleteAllToolTips
void CSkinListCtrl::DeleteAllToolTips()
{
	int nRow = GetItemCount();
	int nCol = GetColumns();

	for (int nItem = 0; nItem < nRow; nItem++)
	{
		SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData(nItem);
		if (pXLCD)
			for (int nSubItem = 0; nSubItem < nCol; nSubItem++)
				pXLCD[nSubItem].strToolTip = _T("");
	}
}

#endif

BOOL CSkinListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class

	HD_NOTIFY *pHDN = (HD_NOTIFY*)lParam;

	// 컬럼 사이즈가 20 이하가 안되게 한다.
	if( (pHDN->hdr.code == HDN_ITEMCHANGINGW || pHDN->hdr.code == HDN_ITEMCHANGINGA) 
		&& pHDN->pitem->cxy < 20 )		
    {		
        *pResult = TRUE;                // disable change		
        return TRUE;                    // Processed message		
    }

	switch( pHDN->hdr.code/*((NMHDR*)lParam)->code*/ )
	{
	case HDN_BEGINTRACKW:	
	case HDN_BEGINTRACKA:	m_bHeaderTracking=TRUE;		break;
	case HDN_ENDTRACKW :	
	case HDN_ENDTRACKA :
		{
			m_bHeaderTracking=FALSE;
			
			Refresh();		
			break;
		}
	case HDN_BEGINDRAG :	m_bHeaderDraging=TRUE;		break;
	case HDN_ENDDRAG :		m_bHeaderDraging=FALSE;		break;
	case HDN_ITEMCLICK:		
		m_bHeaderDraging = FALSE;	
		break;
	}

	if( m_bHeaderTracking )
	{
		// 마우스의 트래킹 방지
		if( !m_bResize )
		{
			*pResult = TRUE;							
			return TRUE;
		}
	}

	return CListCtrl::OnNotify(wParam, lParam, pResult);
}

void CSkinListCtrl::SetRowHeight(int nRowHeight)
{
	CFont font;
	LOGFONT logfont;

	CDC *pDC = GetDC();
	if( !pDC ) return;

	int nRevision=7;

	logfont.lfHeight = -MulDiv(nRowHeight-nRevision, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);
	ReleaseDC( pDC );

	logfont.lfEscapement	= 0;
	logfont.lfOrientation	= 0;
	logfont.lfWeight		= FW_NORMAL;
	logfont.lfItalic		= FALSE;
	logfont.lfUnderline		= FALSE;
	logfont.lfStrikeOut		= FALSE;
	logfont.lfCharSet		= ANSI_CHARSET;
	logfont.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	logfont.lfQuality		= PROOF_QUALITY;
	logfont.lfPitchAndFamily= DEFAULT_PITCH;
	_tcscpy_s(logfont.lfFaceName, _T("System"));
	font.CreateFontIndirect(&logfont);

	SetFont(&font);
	font.DeleteObject();
}


void CSkinListCtrl::SetHeaderColumn( const TCHAR **pszTitle )
{
	LV_COLUMN lvcolumn;
	memset( &lvcolumn, 0, sizeof( lvcolumn ) );
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT /*| LVCF_WIDTH | LVCF_IMAGE*/;
	
	for( int i = 0; ; i++ )
	{
		if( pszTitle[i] == NULL )
			break;

		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.pszText = (TCHAR *)pszTitle[i];
		lvcolumn.iSubItem = i;
		InsertColumn( i, &lvcolumn );
	}	

	lvcolumn.pszText = (TCHAR *)pszTitle[0];
	lvcolumn.iSubItem = 0;
	SetColumn( 0, &lvcolumn );
	SetExtendedStyle( LVS_EX_FULLROWSELECT/*| LVS_EX_GRIDLINES | LVS_EX_FLATSB | LVS_EX_SUBITEMIMAGES*/ );
	EnableToolTips( TRUE );

	// 리스트 아이템 높이 설정
	SetRowHeight( m_nRowHeight );
	// 리스트 폰트 설정
	SetTextFont( m_pTextFont );
	// 언더라인 컬러 설정
	SetColorUnderLine( g_gbl.GetRGB( IDX_RGB_MAIN_TAB ) );

	// 헤더 높이 설정
	m_HeaderCtrl.SetHeight( 30 );
	// 헤더 폰트 설정
	m_HeaderCtrl.SetTextFont( g_gbl.GetFont( IDX_FONT_SIZE_10 ) );
}


void CSkinListCtrl::SetColumnSize( const int *arrWidth, BOOL bAutoSize )
{
	SCROLLINFO si;
	CRect rc;
	GetWindowRect( &rc );
	int nMargin = 0;

	// 스크롤 유무에 따른 마진 추가
	GetScrollInfo( SB_VERT, &si );	
	if( si.nPage && si.nPage <= (UINT)si.nMax ) 
	{
		nMargin = ::GetSystemMetrics( SM_CXVSCROLL );
	}

	// 보더 유무에 따른 마진 추가
	DWORD dwExStyle = GetExStyle();
	
	if( dwExStyle&WS_EX_STATICEDGE || 
		dwExStyle&WS_EX_CLIENTEDGE )
	{
		nMargin += ::GetSystemMetrics( SM_CXEDGE ) * 2;
	}

	int nWidth = 0;
	int nLastWidth = rc.Width() - nMargin;
	for( int i = 0; ; i++ )
	{
		// 마지막 컬럼일 경우
		if( arrWidth[i] == 0 )
		{
			SetColumnWidth( i, nLastWidth );
			break;
		}	

		if( bAutoSize )
			nWidth = ( rc.Width() * arrWidth[i] ) / 100;
		else
			nWidth = arrWidth[i];

		SetColumnWidth( i, nWidth );
		nLastWidth -= nWidth;
	}	

	Refresh();
}


void CSkinListCtrl::SetCheckBox( int nItem, int nSubItem, int nCheckedState )
{
	if( nItem < 0 || nItem >= GetItemCount() )
		return;

	if( nSubItem < 0 || nSubItem >= GetColumns() )
		return;

	if( nCheckedState != CHECKBOX_NORMAL && nCheckedState != CHECKBOX_CHECKED && nCheckedState != CHECKBOX_DISABLE )
		return;

	SkinListCtrlDATA *pXLCD = (SkinListCtrlDATA *) CListCtrl::GetItemData( nItem );
	if( !pXLCD )	return;
	
	pXLCD[ nSubItem ].nCheckedState = nCheckedState;

	BOOL bNew = TRUE;
	int i;	
	for( i = 0; i < m_carrCheckData.GetCount(); i++ )
	{
		CCheckData *pCheckData = m_carrCheckData.GetAt( i );
		if( pCheckData )
		{
			if( pCheckData->m_nItem == nItem && pCheckData->m_nSubItem == nSubItem )
			{
				pCheckData->m_pCheckbox->SetCheckButton( (UINT)nCheckedState );
				bNew = FALSE;
				break;
			}
		}
	}
	
	if( bNew )
	{
		CCheckData *pCheckData = new CCheckData;
		if( !pCheckData )	return;
	
		pCheckData->m_pCheckbox = new CSkinCheckbox;

		CRect rc, rectBtn;
		GetSubItemRect( nItem, nSubItem, LVIR_BOUNDS, rc );

		pCheckData->m_pCheckbox->SetCheckButton( (UINT)nCheckedState );
		pCheckData->m_pCheckbox->Create( _T("BTN_CHKBOX"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, rectBtn, this, DEFAULT_CHKBOX_ID );
	//	pCheckData->m_pCheckbox->SetBitmapID( IDX_PNG_CHK_DEFAULT, IDX_PNG_CHK_CHECKED, IDX_PNG_CHK_DISABLE );	
		pCheckData->m_pCheckbox->SetBitmapID(m_nRes_CheckBox_Nor, m_nRes_CheckBox_Chk, m_nRes_CheckBox_Dis);
		pCheckData->m_nItem    = nItem;
		pCheckData->m_nSubItem = nSubItem;

		pCheckData->m_pCheckbox->m_nItem = nItem;
		pCheckData->m_pCheckbox->m_nSubItem = nSubItem;
	
		m_carrCheckData.Add( pCheckData );	
		UpdateSubItem( nItem, nSubItem );
	}	
}


void CSkinListCtrl::Refresh()
{
	CDC* pDC = GetDC();
	CRect clip;
	m_HeaderCtrl.GetWindowRect( &clip );		// get rect of the control
	ScreenToClient( &clip );
	pDC->ExcludeClipRect( &clip );
	pDC->GetClipBox( &clip );	
	pDC->FillSolidRect( clip, m_crWindow );
	this->Invalidate();

	return;
}


int CSkinListCtrl::GetCheckBox( int nItem, int nSubItem )
{
	int i;
	int nRet = -1;
	
	for( i = 0; i < m_carrCheckData.GetCount(); i++ )
	{
		CCheckData *pCheckData = m_carrCheckData.GetAt( i );
		if( pCheckData )
		{
			if( pCheckData->m_nItem == nItem && pCheckData->m_nSubItem == nSubItem )
			{
				nRet = pCheckData->m_pCheckbox->GetCheckButton();
				return nRet;
			}
		}
	}
	
	return nRet;
}


BOOL CSkinListCtrl::CheckSortData( int nSubItem )
{
	int i;
	int nCount = GetItemCount();
	CString strText;
	
	for( i = 0; i < nCount; i++ )
	{
		strText =  GetItemText( i, nSubItem );
		if( strText != _T("") )	 return TRUE;
	}

	return FALSE;
}


void CSkinListCtrl::Sort(int nSubItem, BOOL bSort)
{
	if( GetItemCount() <= 0 )
		return;

	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetColumns());
	if( nSubItem < 0 || nSubItem >= GetColumns() )
		return;

	SetRedraw(FALSE);

	CString str(_T(""));
    int nCount = GetItemCount();
    for(int i=0; i<nCount; i++) 
    {
		DWORD dw = GetItemData(i);
		str = GetItemText(i, nSubItem) + GetItemText(i, 0 );
		SetItemData( i, (DWORD_PTR)new CSortData(str, dw) );
    }

	CListCtrl::SortItems(&CompareFunc, bSort);

    for(int i=0; i<nCount; i++)
    {
        CSortData* pItem = (CSortData*)GetItemData(i);
        ASSERT( pItem );
        SetItemData(i, pItem->m_dw);
        delete pItem;
    }

	SetRedraw(TRUE);
}

int CALLBACK CSkinListCtrl::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	SkinListCtrlDATA *pXLCD1 = (SkinListCtrlDATA *)lParam1;
	SkinListCtrlDATA *pXLCD2 = (SkinListCtrlDATA *)lParam2;
	if(!pXLCD1 || !pXLCD2)
		return 0;

    CSortData *pLc1 = (CSortData*)pXLCD1->dwItemData;
	CSortData *pLc2 = (CSortData*)pXLCD2->dwItemData;
	if(!pLc1 || !pLc2)
		return 0;

    int nReturn = pLc1->m_strText.Compare(pLc2->m_strText);

    if(lParamSort)
        return nReturn;
    else
        return -nReturn;
}

BOOL CSkinListCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_MOUSEWHEEL )
	{
		this->Invalidate();
	}

	if (pMsg->message == WM_MOUSEMOVE && GetFocus() == this )
	{
		// 현재 마우스 위치를 가져온다.
		CRect rect;
		POINT point;
		::GetCursorPos(&point);
		::ScreenToClient(m_hWnd, &point);	

		// 현재 마우스 위치에 해당하는 Item을 가져온다.
		LVHITTESTINFO lvhitTestInfo;	
		lvhitTestInfo.pt = point;	
		int nItem = SubItemHitTest(&lvhitTestInfo);
		int nSubItem = lvhitTestInfo.iSubItem;

		// nItem과 nSubItem의 값이 정상이고 현재 커서가 일반커서이면 다음을 수행한다.
		if( nItem >= 0 && nSubItem >= 0 &&
			nItem != m_nTrackingItem &&
			GetCursor() == AfxGetApp()->LoadStandardCursor(IDC_ARROW) )
		{			
			// Tracking 플래그를 설정하고 마우스 포인터가 윈도우를 벗어났을때
			// WM_MOUSELEAVE 이벤트가 발생하도록 설정한다.
			if(!m_bTracking) 
			{
				TRACKMOUSEEVENT t = { sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_hWnd, 0 };
				if (::_TrackMouseEvent(&t)) 
				{
					m_bTracking = TRUE;
				}
			}
			
			// 이전 Tracking Item을 Invalidate 한다.		
			if( m_nTrackingItem >= 0 )
			{				
				GetItemRect(m_nTrackingItem, &rect, LVIR_BOUNDS);
				InvalidateRect(&rect, FALSE);
			}			

			// 새로운 Tracking Item을 저장하고 Invalite 한다.
			m_nTrackingItem = nItem;
			GetItemRect(nItem, &rect, LVIR_BOUNDS);			
			InvalidateRect(&rect, FALSE);
		}

		//m_HeaderCtrl.SendMessage(WM_MOUSEMOVE, pMsg->wParam, pMsg->lParam);
		//return TRUE;	
	}	

	return CListCtrl::PreTranslateMessage(pMsg);
}

LRESULT CSkinListCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	// Tracking 플래그를 클리어한다.
	// Tracking Item을 Invalidate한다.
	// Tracking Item을 클리어한다.
	CRect rect;
	m_bTracking = FALSE;	
	if( m_nTrackingItem >= 0 )
	{
		GetItemRect(m_nTrackingItem, &rect, LVIR_BOUNDS);
		InvalidateRect(&rect, FALSE);
		m_nTrackingItem = -1;
	}
	return 0L;
}

void CSkinListCtrl::OnNcPaint()
{
	Default();

	DWORD dwExStyle = GetExStyle();
	
	if( dwExStyle & WS_EX_STATICEDGE || dwExStyle & WS_EX_CLIENTEDGE )
	{
		CRect rc;
		GetWindowRect( &rc );

		//COLORREF cr = g_gbl.GetRGB( IDX_RGB_MAIN_TAB );
		COLORREF cr = RGB(210, 221, 212);

		//Non-Client 영역의 DC를 얻어온다.
		CWindowDC dc(this);
		dc.Draw3dRect( 0, 0, rc.Width(), rc.Height(), cr, cr );
	}
}

void CSkinListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch( nSBCode )
	{
	case SB_LINEUP     :
	case SB_LINEDOWN   :
	case SB_THUMBTRACK :
		{
			HideCheckbox();
			this->Invalidate();
		}
		break;
	
	case SB_ENDSCROLL:
		{
			Refresh();
		}
		break;
	}

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CSkinListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch( nSBCode )
	{
	case SB_LINELEFT   :
	case SB_LINERIGHT  :
	case SB_THUMBTRACK :
		{
			HideCheckbox();
			this->Invalidate();
		}
		break;

	case SB_ENDSCROLL:
		{
			Refresh();
		}
		break;
	}

	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CSkinListCtrl::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
{
	// Wheel Down
	if( zDelta <= 0 )
	{

	}
	// Wheel Up
	else
	{

	}
	HideCheckbox();
	return CListCtrl::OnMouseWheel( nFlags, zDelta, pt );
}

void CSkinListCtrl::SetCheckBox_Bitmap(int nRes_Nor, int nRes_Chk, int nRes_Dis)
{
	m_nRes_CheckBox_Nor = nRes_Nor;
	m_nRes_CheckBox_Chk = nRes_Chk;
	m_nRes_CheckBox_Dis = nRes_Dis;

}

LRESULT CSkinListCtrl::OnCheckbox2Ctrl(WPARAM wp, LPARAM lp)
{
	CString strMsg;

	strMsg.Format(_T("1,%d,%d,"), wp, lp);

	GetParent()->SendMessage(WM_MSG_CTRL_EVENT, GetDlgCtrlID(), (LPARAM)strMsg.GetBuffer());
	return TRUE;
}

/////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

// CMyCtrl 메시지 처리기입니다.

BEGIN_MESSAGE_MAP(CMyBrowseEdit, CEdit)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, &CMyBrowseEdit::OnEnKillfocus)
END_MESSAGE_MAP()

void CMyBrowseEdit::OnEnKillfocus()
{
	if (!m_bBrowse)
		GetParent()->SendMessage(WM_LIST2CTRL, GetDlgCtrlID(), VK_RETURN);
}

BOOL CMyBrowseEdit::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		GetParent()->SendMessage(WM_LIST2CTRL, GetDlgCtrlID(), pMsg->wParam);
		return TRUE;
	}
	return CEdit::PreTranslateMessage(pMsg);
}
///// 
BEGIN_MESSAGE_MAP(CMyCombo, CComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CMyCombo::OnCbnSelchange)
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, &CMyCombo::OnCbnKillfocus)
	ON_CONTROL_REFLECT(CBN_SELENDCANCEL, &CMyCombo::OnCbnSelCancel)
END_MESSAGE_MAP()
void CMyCombo::OnCbnKillfocus()
{
	GetParent()->SendMessage(WM_LIST2CTRL, GetDlgCtrlID(), 0);
}
void CMyCombo::OnCbnSelCancel()
{
	GetParent()->SendMessage(WM_LIST2CTRL, GetDlgCtrlID(), 0);
}

void CMyCombo::OnCbnSelchange()
{
	GetParent()->SendMessage(WM_LIST2CTRL, GetDlgCtrlID(), VK_RETURN);
}

BOOL CMyCombo::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		GetParent()->SendMessage(WM_LIST2CTRL, GetDlgCtrlID(), pMsg->wParam);
		return TRUE;
	}
	return CComboBox::PreTranslateMessage(pMsg);
}
////
CSkinCustomList::CSkinCustomList()
{
	m_pDataArr.RemoveAll();
}
CSkinCustomList::~CSkinCustomList()
{
	for (int i = 0; i < m_pDataArr.GetSize(); i++)
		delete m_pDataArr.GetAt(i);
}

BEGIN_MESSAGE_MAP(CSkinCustomList, CSkinListCtrl)
	//{{AFX_MSG_MAP(CCustomList)
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_LIST2CTRL, &CSkinCustomList::OnList2Ctrl)
END_MESSAGE_MAP()

void CSkinCustomList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	LVHITTESTINFO info;
	info.pt = point;

	HitTest(&info);
	SubItemHitTest(&info);
	CListItem* pItem = NULL;
	for (int i = 0; i < m_pDataArr.GetSize(); i++)
	{
		pItem = m_pDataArr.GetAt(i);
		if (pItem->m_nRow != info.iItem || pItem->m_nCol != info.iSubItem)
		{
			pItem = NULL;
			continue;
		}

		break;
	}
	SetFocus();

	if (pItem)
	{

		//// 컨트롤 생성
		CRect r;
		GetSubItemRect(pItem->m_nRow, pItem->m_nCol, LVIR_LABEL, r);
		CString strTmp = GetItemText(pItem->m_nRow, pItem->m_nCol);
		CString strData;
		int nSel = -1;
		if (pItem->m_nType == LIST_TYPE_EDIT || pItem->m_nType == LIST_TYPE_BTN)
		{

			m_wndEdit.Create(ES_LEFT | WS_BORDER | WS_CHILD | ES_AUTOHSCROLL | ES_AUTOVSCROLL, r, this, 35000, CPoint(pItem->m_nRow, pItem->m_nCol));
			m_wndEdit.SetWindowText(strTmp);
			m_wndEdit.ShowWindow(TRUE);
			m_wndEdit.SetFocus();
			m_wndEdit.SetSel(0, strTmp.GetLength());
			/*if(pItem->m_nType == LIST_TYPE_BTN)
				m_wndEdit.EnableBrowseButton();
			else
				m_wndEdit.EnableBrowseButton(FALSE);*/
		}
		else if (pItem->m_nType == LIST_TYPE_COMBO)
		{
			r.top += 1;

			m_wndCombo.Create(CBS_DROPDOWNLIST | WS_BORDER | WS_CHILD, r, this, 35001, CPoint(pItem->m_nRow, pItem->m_nCol));
			
			for (int i = 0; i < pItem->m_strComboArr.GetSize(); i++)
			{
				strData = pItem->m_strComboArr.GetAt(i);
				m_wndCombo.AddString(strData);
				if (strData == strTmp)
				{
					nSel = i;
				}
			}
			m_wndCombo.SetWindowText(strTmp);
			m_wndCombo.ShowWindow(TRUE);
			m_wndCombo.ShowDropDown();
			m_wndCombo.SetFocus();
			if (nSel != -1)
				m_wndCombo.SetCurSel(nSel);
		}
	}
	else
	{
		CSkinListCtrl::OnLButtonDblClk(nFlags, point);
	}
}
void CSkinCustomList::SetItemInfo(int nItem, int nSubItem, int nType, CStringArray *pData)
{
	CListItem* pItem = new CListItem;
	pItem->m_nType = nType;
	pItem->m_nRow = nItem;
	pItem->m_nCol = nSubItem;
	if (nType == LIST_TYPE_COMBO)
		pItem->m_strComboArr.Copy(*pData);
	else
		pItem->m_strComboArr.RemoveAll();

	m_pDataArr.Add(pItem);
}

LRESULT CSkinCustomList::OnList2Ctrl(WPARAM wp, LPARAM lp)
{
	if (m_wndEdit.GetSafeHwnd())
	{
		//////////////////////////// 실시간 처리시 부모로 쏴줘야된다.
		if (wp == m_wndEdit.GetDlgCtrlID())
		{
			CString strTmp;
			if (lp == VK_RETURN)
			{
				m_wndEdit.GetWindowText(strTmp);
				SetItemText(m_wndEdit.m_Pos.x, m_wndEdit.m_Pos.y, strTmp);
			}
			else if (lp == VK_ESCAPE)
			{
			}
			SetSelectionMark(m_wndEdit.m_Pos.x);
			m_wndEdit.DestroyWindow();
		}
	}
	if (m_wndCombo.GetSafeHwnd())
	{
		if (wp == m_wndCombo.GetDlgCtrlID())
		{
			CString strTmp;
			if (lp == VK_RETURN)
			{
				int nPos = m_wndCombo.GetCurSel();
				if (nPos == -1)
					m_wndCombo.GetWindowText(strTmp);
				else
					m_wndCombo.GetLBText(nPos, strTmp);

				SkinListCtrlDATA* pXLCD = (SkinListCtrlDATA *)CListCtrl::GetItemData(m_wndCombo.m_Pos.x);
				COLORREF crText = pXLCD[m_wndCombo.m_Pos.y].crText;
				COLORREF crBkgnd = pXLCD[m_wndCombo.m_Pos.y].crBackground;
				int		 nA		 = pXLCD[m_wndCombo.m_Pos.y].nTextLeftmode;

				SetItemText(m_wndCombo.m_Pos.x, m_wndCombo.m_Pos.y, strTmp,crText, crBkgnd, nA);

				CString strMsg;

				strMsg.Format(_T("3,%d,%d,"), m_wndCombo.m_Pos.x, m_wndCombo.m_Pos.y);

				GetParent()->SendMessage(WM_MSG_CTRL_EVENT, GetDlgCtrlID(), (LPARAM)strMsg.GetBuffer());
				//if (_wtoi(strTmp) != 0)
				//{
				//	/*int nEndPos = GetItemCount();
				//	CString strData[9];
				//	for (int k = 1; k < 9; k++)
				//	{
				//		strData[k] = GetItemText(m_wndCombo.m_Pos.x, k);
				//	}
				//	DeleteItem(m_wndCombo.m_Pos.x);*/
				//	
				//	

				//	InsertItem(_wtoi(strTmp) - 1, strTmp, pXLCD[]);
				//	for (int k = 1; k < 9; k++)
				//	{
				//		SetItemText(_wtoi(strTmp) - 1, k, strData[k]);
				//	}
				//	for (int k = 0; k < GetItemCount(); k++)
				//	{
				//		strTmp.Format(_T("%d"), k + 1);
				//		SetItemText(k, 0, strTmp);
				//	}
				//}
			}
			else if (lp == VK_ESCAPE)
			{
			}
			SetSelectionMark(m_wndCombo.m_Pos.x);
			m_wndCombo.DestroyWindow();
		}
	}
	//SetFocus();
	return true;
}



BOOL CSkinListCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (GetDlgCtrlID() == 20402)
	{
		if (message == WM_NOTIFY)
		{
			int a;
			if(wParam == 1111)
				 a = 0;
		}
		
	}

	return CListCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}
