#ifndef _SKINMENU_H
#define _SKINMENU_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// constants used for drawing
#define CXGAP			0	// num pixels between button and text
#define CXTEXTMARGIN	2	// num pixels after hilite to start text
#define CXBUTTONMARGIN	2	// num pixels wider button is than bitmap
#define CYBUTTONMARGIN	2	// ditto for height

//The ownerdraw data
class CSkinMenuItem
{
public:
	DWORD		m_dwID;			// Menu ID
	BOOL		m_bSeparator;	// Separator
	BOOL		m_bSideBar;		// A gradient sidebar
	CString		m_strText;		// Menu item text
	int			m_nSize;		// Height of the item(Width of the sidebar if m_bSideBar is true)

public:
	CSkinMenuItem() 
	{
		m_dwID       = 0;
		m_bSeparator = FALSE;
		m_bSideBar   = FALSE;
		m_nSize      = 16;
	};
};

///////////////////////////////////////////////////////////////////////////////////////////////
//	For convenient, derive some class from CSkinMenuItem, 
//	and do the initialization in constructor
class CSkinMenuText : public CSkinMenuItem			// Normal item with text and an optional icon
{
public:
	CSkinMenuText( DWORD dwID, LPCTSTR strText ) : CSkinMenuItem()
	{
		m_dwID    = dwID;
		m_strText = strText;
	}
};

class CSkinMenuSeparator : public CSkinMenuItem		// A separator item
{
public:
	CSkinMenuSeparator() : CSkinMenuItem()
	{
		m_bSeparator = TRUE;
	}
};

class CSkinMenuSideBar : public CSkinMenuItem		// A gradient sidebar
{
public:
	CSkinMenuSideBar( int nSize = 32, LPCTSTR strText = NULL, DWORD dwID = 0 ) : CSkinMenuItem()
	{
		m_dwID     = dwID;
		m_bSideBar = TRUE;
		m_strText  = strText;
		m_nSize    = nSize;
		m_dwID     = dwID;
	}
};

////////////////////////////////////////////////////////////////////////////////////////
// Class CSkinMenu, an ownerdraw menu

class CSkinMenu : public CMenu
{
	DECLARE_DYNAMIC( CSkinMenu )

public:
	CSkinMenu();
	virtual ~CSkinMenu();

	//Below is the functions to build the menu
	BOOL	AddSideBar     ( int nWidth, CString strText = _T("") );
	BOOL	AppendODMenu   ( UINT nFlags, DWORD dwID, LPCTSTR strText, ACCEL *pAccel = 0 );
	BOOL	AppendSeparator( void );	
	BOOL	AppendODPopup  ( UINT nFlags, CSkinMenu *pPopup, DWORD dwID, LPCTSTR strText );

protected:
	CFont	   *m_pFont;			// 폰트
	COLORREF	m_clrBackGround;	// Background color
	COLORREF	m_clrSelectedBar;	// selected bar color
	COLORREF	m_clrText;			// Text color
	COLORREF	m_clrSelectedText;	// selected text color
	COLORREF	m_clrDisabledText;	// disabled text color
	COLORREF	m_clrSideBarStart;	// Start color of the gradient sidebar
	COLORREF	m_clrSideBarEnd;	// end color of the gradient sidebar
	
	BOOL		m_bLSidebar;		// if true, next item inserted into the menu will be added with the sytle MF_MENUBREAK
	HBITMAP		m_hBitmapBG;		// Background bitmap
	SIZE		m_sizeBG;			// Background size
	CDC			m_memDC;			// Memory dc holding the background bitmap

public:	//User these functions to change the default attribute of the menu
	void	SetBackColor	    ( COLORREF clr )	{ m_clrBackGround = clr;   }	// Menu 바탕 색상
	void	SetSelectedBarColor ( COLORREF clr )	{ m_clrSelectedBar = clr;  }	// Mouse over 메뉴 색상
	void	SetTextColor	    ( COLORREF clr )	{ m_clrText = clr;		   }	// 기본 폰트 색상
	void	SetSelectedTextColor( COLORREF clr )	{ m_clrSelectedText = clr; }	// Mouse over 폰트 색상
	void	SetDisabledTextColor( COLORREF clr )	{ m_clrDisabledText = clr; }	// Disable된 폰트 색상
	void	SetSideBarStartColor( COLORREF clr )	{ m_clrSideBarStart = clr; }	// Side Bar의 그라데이션 시작 색상
	void	SetSideBarEndColor  ( COLORREF clr )	{ m_clrSideBarEnd = clr;   }	// Side Bar의 그라데이션 끝 색상
	void	SetMenuFont         ( CFont *pFont )	{ m_pFont = pFont;		   }	// 기본 폰트
	void	SetBitmapID			( UINT uBaseImage );								// 메뉴 비트맵
	void	Clear				();													// Clean all memory and handles
	void	FillRect			( CDC *pDC, const CRect& rc, COLORREF color );
	HBITMAP	CreateGradientBMP   ( HDC hDC,COLORREF cl1,COLORREF cl2,int nWidth,int nHeight,int nDir,int nNumColors );

public:
	virtual void DrawItem   ( LPDRAWITEMSTRUCT lpDrawItemStruct );
	virtual void MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct );

protected:
	virtual void DrawBackGround( CDC *pDC, CRect rect, BOOL bSelected, BOOL bDisabled);
	virtual void DrawButton    ( CDC *pDC, CRect rect, BOOL bSelected, BOOL bDisabled, BOOL bChecked);
	virtual void DrawSideBar   ( CDC *pDC, CRect rect, CString strText);
	virtual void DrawText      ( CDC *pDC, CRect rect, CString strText, BOOL bSelected, BOOL bDisabled, BOOL bBold);
	virtual void DrawMenuText  ( CDC& dc, CRect rc, CString text, COLORREF color);
	virtual void DrawCheckMark ( CDC *pDC, CRect rect, BOOL bSelected);	
};

#endif // _SKINMENU_H