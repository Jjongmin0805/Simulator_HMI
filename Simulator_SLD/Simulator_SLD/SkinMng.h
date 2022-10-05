#pragma once

//#include "CommonHeader.h"

#define						theskin_component						CSkinMng::instance()

class CSkinMng
{
public:
	static CSkinMng*		instance( void );
protected : 
	static CSkinMng*		pSingletonData;

public:
	CSkinMng(void);
	~CSkinMng(void);

	// Attributes
public:
	CFont					*m_pFont[IDX_FONT_MAX];
	BITMAP_INFO				m_infoBitmap[IDX_SYSTEMICON_MAX];
	HICON					m_hIcon[IDX_ICON_MAX][3];
	COLORREF				m_cf[IDX_RGB_MAX];
	LPFounction				SetLayeredWindowAttributes;
	CRect					m_RectToolbarChildSysMin, m_RectToolbarChildSysMax, m_RectToolbarChildSysExit;

protected:

	// Operations
public:
	void					DeleteBitmaps();	
	void					LoadBitmaps();	
	HBITMAP					GetBitmap(UINT nBitmapID);
	SIZE					GetBitmapSize(UINT nBitmapID);
	CString					GetBitmapFileName(UINT nBitmapID);
	CString					GetModulePath();
	void					DeleteIcons();
	void					LoadIcons();
	CString					GetIconFileName(UINT nIconID);
	HICON					GetIcon(UINT nIconID, UINT nType);
	void					SetRGB(UINT nRGBID, COLORREF cf);
	COLORREF				GetRGB(UINT nRGBID);
	void					DeleteFonts();
	CFont*					SetFont(CWnd* pWnd, UINT nFontID, CString sFaceName, UINT nFontSize, BOOL bBold = FALSE);
	CFont*					GetFont(UINT nFontID);
	CSize					FormatText(CString& sText, CDC* pDC, int nWidth);
	COLORREF				Darker(COLORREF crBase, float fFactor);
	COLORREF				Lighter(COLORREF crBase, float fFactor);
};

#define						theskin						CSkinMng::instance()