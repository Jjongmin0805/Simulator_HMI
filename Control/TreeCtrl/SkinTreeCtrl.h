#ifndef _SKINTREECTRL_H
#define _SKINTREECTRL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkinTreeCtrl : public CTreeCtrl
{
public:
	CSkinTreeCtrl(void);
	virtual ~CSkinTreeCtrl(void);
		
	void SetTextFont  ( CFont *pFont );
	BOOL SetTextNBkClr( COLORREF clrText, COLORREF clrBk = NULL );

	void DrawListBot  ( int nWidth =0 );
	void DrawListTop  ( int nWidth =0 );
	void DrawListRight( int nHeight=0 );
	void DrawListLeft ( int nHeight=0 );
	void DrawCenter   ( int nWidth =0 );

	void SetCheckAll  ( BOOL bCheck );
	void SetCheckItem ( HTREEITEM hItem, BOOL bCheck );
	void SetBitmapID  ( UINT uTreeTopImage, UINT uTreeLeftImage, UINT uTreeRightImage, UINT uTreeBotImage, UINT uTreeDefaultBgImage = NULL );
	BOOL SetBkImage   ();

	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	afx_msg void OnPaint  ();
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg BOOL OnQueryNewPalette();
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);

protected:
	HBITMAP		m_hBmpTreeTop;
	HBITMAP		m_hBmpTreeLeft;
	HBITMAP		m_hBmpTreeRight;
	HBITMAP		m_hBmpTreeBot;
	HBITMAP		m_hBmpTreeDefaultBg;

	CFont	   *m_pFont;
	CPalette	m_pal;
	CBitmap		m_bitmap;
	int			m_cxBitmap; 
	int			m_cyBitmap;	
};

#endif	//_SKINTREECTRL_H