#ifndef _SKINCOLORCOMBOBOX_H
#define _SKINCOLORCOMBOBOX_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkinComboboxlist.h"  

#define DROPDOWN_BTN_WIDTH	19
///////////////////////////////////////////////////////////////////////////// 
// CSkinColorCombobox window 
 
class CSkinColorCombobox : public CComboBox 
{ 
public: 
	CSkinColorCombobox(); 
	virtual ~CSkinColorCombobox();	
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	
	void    SetNormalPositionColor( COLORREF colBackGround, COLORREF colText );
	void    SetHighlightColor     ( COLORREF colBackGround, COLORREF colText );
	void    SetBitmapID           ( UINT uComboLeftImage, UINT uComboRightImage, UINT uComboCenHImage );
	void    SetBitmapID           ( UINT uComboLeftImage, UINT uComboRightImage, UINT uComboCenHImage, UINT uComboCenLImage );
	void    SetDropDownHeight     ( int itemsToShow );								//Drop down�Ǵ� ������ ���� ����
	void    SetTextFont	          ( CFont *pFont );
	void    SetCurSelName         ( CString strName );
	void	SetCurSelId			  ( int nId );	 
	CString GetCurSelName         ();
	int	    GetCurSelId			  ();
	
	void SetHLMargin			  ( UINT uHLMargin )	{	m_uHLMargin = uHLMargin;	}	// ������ ������ ����
	void SetTextStyle			  ( DWORD dwStyle  )	{	m_dwStyle   = dwStyle;		}	// �������� ��Ÿ�ϼ���

protected:
	CSkinComboboxlist    m_listbox; 
	CFont				*m_pFont;						// ���� ��Ʈ	 
	COLORREF			 m_colBackGroundHighLight;		// ���콺 ���̶���Ʈ ����
	COLORREF			 m_colTextHighLight;			// ���콺 ���̶���Ʈ ���ڻ�
	COLORREF			 m_colBackGroundNormal;			// ����
	COLORREF			 m_colTextNormal;				// ���ڻ�
		
	HBITMAP				 m_hBmpComboCenH;
	HBITMAP				 m_hBmpComboCenL;
	HBITMAP				 m_hBmpComboLeft;
	HBITMAP				 m_hBmpComboRight;
		
	UINT				 m_nListSelectedItemID;
	UINT				 m_uHLMargin;
	DWORD				 m_dwStyle;						// �������� ��Ÿ��

///////////////////////////////////////////////////////////////////////////////// 
protected:
	afx_msg void	OnPaint  (); 
	afx_msg void	OnDestroy();
	afx_msg LRESULT OnCtlColorListBox( WPARAM wParam, LPARAM lParam ); 
	afx_msg HBRUSH  OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor );
 
	DECLARE_MESSAGE_MAP()
}; 
 
#endif // _SKINCOLORCOMBOBOX_H