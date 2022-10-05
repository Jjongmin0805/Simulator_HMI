// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CMyToolTipCtrl window

class CMyToolTipCtrl : public CToolTipCtrl
{
	DECLARE_DYNCREATE(CMyToolTipCtrl)

// Construction
public:
	CMyToolTipCtrl();

// Attributes
public:

// Operations
public:
	CPoint				m_ptMargin;
	CPoint				m_ptLocation;
	CString				m_strDescription;
	CSize				m_sizeImage;

	int					m_nFixedWidthRegular;
	int					m_nFixedWidthWithImage;

	CMFCToolTipInfo		m_Params;
	CFont				m_pFontLabelNormal;
	CFont				m_pFontLabelBold;
	CFont				m_pFontDescNormal;
	CFont				m_pFontDescBold;

	void				SetParams(CMFCToolTipInfo* pParams);
	int					GetFixedWidth ();
	void				SetFixedWidth(int nWidthRegular, int nWidthLargeImage);
	void				SetLocation(CPoint pt);
	void				AddIcon(UINT nID);

	void				Show();
	void				Hide();
	void				SetLayout();
	void				Clear();

// Overrides
	virtual void		SetDescription (const CString strDesrciption);
	virtual CSize		GetIconSize ();
	virtual void		OnFillBackground (CDC* pDC, CRect rect, COLORREF& clrFill, COLORREF& clrFillGradient);

	virtual void		OnDrawBorder(CDC* pDC, CRect rect, COLORREF clrLine);
	virtual BOOL		OnDrawIcon(CDC* pDC, CRect rectImage);
	virtual CSize		OnDrawLabel(CDC* pDC, CRect rect, BOOL bCalcOnly);
	virtual CSize		OnDrawDescription(CDC* pDC, CRect rect, BOOL bCalcOnly);
	virtual void		OnDrawSeparator(CDC* pDC, int x1, int x2, int y);

// Implementation
public:
	virtual ~CMyToolTipCtrl();

protected:
	//{{AFX_MSG(CMyToolTipCtrl)
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnPaint();
	afx_msg BOOL		OnEraseBkgnd(CDC* pDC);
	afx_msg void		OnShow(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void		OnPop(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	HICON	m_hIcon;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};
