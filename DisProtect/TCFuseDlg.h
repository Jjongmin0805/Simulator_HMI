#if !defined(AFX_TCFUSEDLG_H__932DA7F0_F10B_435C_9B3A_5D1EDBE2E0BF__INCLUDED_)
#define AFX_TCFUSEDLG_H__932DA7F0_F10B_435C_9B3A_5D1EDBE2E0BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCFuseDlg.h : header file
//
#include "resource.h"
#include "CurveObj.h"

/////////////////////////////////////////////////////////////////////////////
// CTCFuseDlg dialog

class AFX_EXT_CLASS CTCFuseDlg : public CDialog
{
// Construction
public:
	CTCFuseDlg(CSession* pDB, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTCFuseDlg)
	enum { IDD = IDD_FUSE_CURVE_DLG };
	CComboBox	m_ctrCombo;
	int		m_nType;
	int		m_bSecond;
	float	m_fA;
	float	m_fB;
	float	m_fC;
	float	m_fCurrent1;
	float	m_fCurrent2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCFuseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// 	CClrButton m_ctrButton[4];
// 	CBitmapButton m_ctrHButton;
	void DrawIndex(CDC *pDC, CRect rect);
	void TextGrid(CDC *pDC, CRect rect);
	void DrawGrid(CDC *pDC, CRect rect);
	CSession* m_pDB;
	CCurveObj* m_pCurve;
	// Generated message map functions
	//{{AFX_MSG(CTCFuseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTcButton1();
	afx_msg void OnSelchangeTcCombo1();
	afx_msg void OnOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeTcCombo2();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTcRadio1();
	afx_msg void OnTcRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCFUSEDLG_H__932DA7F0_F10B_435C_9B3A_5D1EDBE2E0BF__INCLUDED_)
