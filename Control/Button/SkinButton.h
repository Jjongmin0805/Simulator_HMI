#ifndef _SKINBUTTON_H
#define _SKINBUTTON_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// CSkinButton

class CSkinButton : public CButton
{
	DECLARE_DYNAMIC(CSkinButton)

public:
	CSkinButton();
	virtual ~CSkinButton();

public:	
	void		 SetBitmapID      ( UINT uDefaultImage, UINT uDownImage, UINT uOverImage );
	void		 SetBitmap      ( CString strDefaultImage, CString strDownImage, CString strOverImage );
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage( MSG* pMsg );

protected:
	BOOL m_bHover;
	BOOL m_bTracking;
	BOOL m_bToolTip;
	
	int  m_nWidth;
	int  m_nHeight;

	// 비트맵 사이즈
	SIZE		m_sizeDefault;		// 버튼 디폴트
	SIZE		m_sizeDown;			// 버튼 마우스다운
	SIZE		m_sizeOver;			// 버튼 마우스오버	

	// 비트맵 핸들
	HBITMAP		m_hBmpDefault;		// 버튼 디폴트
	HBITMAP		m_hBmpDown;			// 버튼 마우스다운
	HBITMAP		m_hBmpOver;			// 버튼 마우스오버

	CString		 m_strText;			// 버튼 글자
	COLORREF	 m_cfText;			// 버튼 글자색
	CToolTipCtrl m_ToolTip;			// 버튼 툴팁
	CFont		*m_pFont;			// 버튼 폰트
	CFont       *m_pToolTipFont;	// 툴팁 폰트

public:	
	void    SetButtonColor( COLORREF cfText )						{	m_cfText  = cfText;		}	
	void    SetFont       ( CFont *pFont, CFont *pToolTipFont )		{   m_pFont = pFont;	m_pToolTipFont = pToolTipFont;	}
	CString GetButtonText()											{	return  m_strText;		}
	void    SetButtonText ( CString strText, int nWidth = 0, int nHeight = 0 );
	void    SetToolTipText( CString strText );	
		
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg void DrawItem   ( LPDRAWITEMSTRUCT lpDrawItemStruct );
	afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnMouseHover( WPARAM wParam, LPARAM lParam );

protected:
	DECLARE_MESSAGE_MAP()	
};

#endif	//_SKINBUTTON_H