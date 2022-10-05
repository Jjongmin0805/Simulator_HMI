#ifndef _SKINCOMBOBOX_H
#define _SKINCOMBOBOX_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkinComboboxlist.h"  

#define DROPDOWN_BTN_WIDTH	19
///////////////////////////////////////////////////////////////////////////// 
// CSkinCombobox window 
 
class CSkinCombobox : public CComboBox
{ 
	DECLARE_DYNAMIC(CSkinCombobox)
public: 
	CSkinCombobox(); 
	virtual ~CSkinCombobox();	
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	void    SetNormalPositionColor( COLORREF colBackGround, COLORREF colText );
	void    SetHighlightColor     ( COLORREF colBackGround, COLORREF colText );
	void    SetBitmapID           ( UINT uComboLeftImage, UINT uComboRightImage, UINT uComboCenHImage );
	void    SetBitmapID           ( UINT uComboLeftImage, UINT uComboRightImage, UINT uComboCenHImage, UINT uComboCenLImage );
	void    SetDropDownHeight     ( int itemsToShow );								//Drop down되는 아이템 갯수 설정
	void    SetTextFont	          ( CFont *pFont );
	void    SetCurSelName         ( CString strName );
	void	SetCurSelId			  ( int nId );	 
	CString GetCurSelName         ();
	int	    GetCurSelId			  ();
	
	void SetHLMargin			  ( UINT uHLMargin )	{	m_uHLMargin = uHLMargin;	}	// 상하의 여백을 결정
	void SetTextStyle			  ( DWORD dwStyle  )	{	m_dwStyle   = dwStyle;		}	// 글자정렬 스타일설정

protected:
	CSkinComboboxlist    m_listbox; 
	CFont				*m_pFont;						// 글자 폰트	 
	COLORREF			 m_colBackGroundHighLight;		// 마우스 하이라이트 배경색
	COLORREF			 m_colTextHighLight;			// 마우스 하이라이트 글자색
	COLORREF			 m_colBackGroundNormal;			// 배경색
	COLORREF			 m_colTextNormal;				// 글자색
		
	HBITMAP				 m_hBmpComboCenH;
	HBITMAP				 m_hBmpComboCenL;
	HBITMAP				 m_hBmpComboLeft;
	HBITMAP				 m_hBmpComboRight;
	
	int					 m_nListBoxTextLeft;
	UINT				 m_nListSelectedItemID;
	UINT				 m_uHLMargin;
	DWORD				 m_dwStyle;						// 글자정렬 스타일

///////////////////////////////////////////////////////////////////////////////// 
protected:
	afx_msg void	OnPaint  (); 
	afx_msg void	OnDestroy();
	afx_msg LRESULT OnCtlColorListBox( WPARAM wParam, LPARAM lParam ); 
	afx_msg HBRUSH  OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor );
 
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};
 
#endif // _SKINCOMBOBOX_H