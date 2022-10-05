#pragma once

#include "PNOCtrl_CommonHeader.h"

enum AFX_EXT_CLASS SYS_OSVER {
	SYSOS_ERROR = 0,
	SYSOS_WIN32,
	SYSOS_WIN95,
	SYSOS_WINOSR2,
	SYSOS_WIN98,
	SYSOS_WIN98SE,
	SYSOS_WINME,
	SYSOS_WINNT,
	SYSOS_WIN2K,
	SYSOS_WINXP,
	SYSOS_NEXTOS,
	SYSOS_VISTA,
	SYSOS_WIN7
};

class AFX_EXT_CLASS CPNOCtrl_SkinMng
{
public:
	static CPNOCtrl_SkinMng*		instance( void );
protected : 
	static CPNOCtrl_SkinMng*		pSingletonData;

public:
	CPNOCtrl_SkinMng(void);
	~CPNOCtrl_SkinMng(void);

	// Attributes
public:
	CFont					*m_pFont[PNOCtrl_IDX_FONT_MAX];
	PNOCtrl_BITMAP_INFO		m_infoBitmap[PNOCtrl_IDX_SYSTEMICON_MAX];
	HICON					m_hIcon[PNOCtrl_IDX_ICON_MAX][3];
	COLORREF				m_cf[PNOCtrl_IDX_RGB_MAX];
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
	UINT					GetSystemVersion();
};

#define						thePNOCtrolskin						CPNOCtrl_SkinMng::instance()