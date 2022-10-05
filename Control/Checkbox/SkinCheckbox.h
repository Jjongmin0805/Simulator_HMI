#ifndef _SKINCHECKBOX_H
#define _SKINCHECKBOX_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CSkinCheckbox

#define				WM_CHECKBOX2LIST_MSG			WM_USER+3

class CSkinCheckbox : public CButton
{
	DECLARE_DYNAMIC(CSkinCheckbox)

public:
	CSkinCheckbox();
	virtual ~CSkinCheckbox();

public:
	void		 SetCheckButton   ( UINT uCheckStatus )		{	m_uCheckStatus = uCheckStatus;	}
	UINT		 GetCheckButton   ()						{	return m_uCheckStatus;			}
	void		 SetBitmapID      ( UINT uNormalImage, UINT uCheckImage, UINT uDiableImage );	
	virtual void PreSubclassWindow();	

protected:
	DECLARE_MESSAGE_MAP()	

	UINT m_uCheckStatus;			// 0 : Normal, 1 ; Check, 2 : Disable

	// 비트맵 사이즈
	SIZE		m_sizeChkDefault;	// 디폴트
	SIZE		m_sizeChkSelected;	// 선택
	SIZE		m_sizeChkDisable;	// 비활성

	// 비트맵 핸들
	HBITMAP		m_hBmpChkDefault;	// 디폴트
	HBITMAP		m_hBmpChkSelected;	// 선택
	HBITMAP		m_hBmpChkDisable;	// 비활성

	

public:
	afx_msg void OnLButtonUp ( UINT nFlags, CPoint point );
	afx_msg void OnMouseHover( UINT nFlags, CPoint point );
	afx_msg void OnMouseLeave();
	virtual void DrawItem    ( LPDRAWITEMSTRUCT lpDrawItemStruct );


	CFont*		m_pFont_Text;
	COLORREF	m_colorBg;
	COLORREF	m_colorText;

	int m_nItem;
	int m_nSubItem;
};

#endif	//_SKINCHECKBOX_H