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

	// ��Ʈ�� ������
	SIZE		m_sizeChkDefault;	// ����Ʈ
	SIZE		m_sizeChkSelected;	// ����
	SIZE		m_sizeChkDisable;	// ��Ȱ��

	// ��Ʈ�� �ڵ�
	HBITMAP		m_hBmpChkDefault;	// ����Ʈ
	HBITMAP		m_hBmpChkSelected;	// ����
	HBITMAP		m_hBmpChkDisable;	// ��Ȱ��

	

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