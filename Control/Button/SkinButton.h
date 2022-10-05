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

	// ��Ʈ�� ������
	SIZE		m_sizeDefault;		// ��ư ����Ʈ
	SIZE		m_sizeDown;			// ��ư ���콺�ٿ�
	SIZE		m_sizeOver;			// ��ư ���콺����	

	// ��Ʈ�� �ڵ�
	HBITMAP		m_hBmpDefault;		// ��ư ����Ʈ
	HBITMAP		m_hBmpDown;			// ��ư ���콺�ٿ�
	HBITMAP		m_hBmpOver;			// ��ư ���콺����

	CString		 m_strText;			// ��ư ����
	COLORREF	 m_cfText;			// ��ư ���ڻ�
	CToolTipCtrl m_ToolTip;			// ��ư ����
	CFont		*m_pFont;			// ��ư ��Ʈ
	CFont       *m_pToolTipFont;	// ���� ��Ʈ

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