#if !defined(AFX_TCRELAYREGDLG_H__17DFB704_5E96_42BE_AB20_4D360228BF0F__INCLUDED_)
#define AFX_TCRELAYREGDLG_H__17DFB704_5E96_42BE_AB20_4D360228BF0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCRelayRegDlg.h : header file
//
#include "resource.h"
#include "CurveObj.h"
/////////////////////////////////////////////////////////////////////////////
// CTCRelayRegDlg dialog

class AFX_EXT_CLASS CTCRelayRegDlg : public CDialog
{
// Construction
public:
	CTCRelayRegDlg(CSession* pDB, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTCRelayRegDlg)
	enum { IDD = IDD_RELAY_CURVE_DLG };
	CComboBox	m_ctrCombo;
	int		m_bSecond;
	float	m_fA;
	float	m_fB;
	float	m_fC;
	float	m_fD;
	float	m_fE;
	float	m_fF;
	float	m_fLever;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCRelayRegDlg)
	public:
	virtual BOOL DestroyWindow();
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
	//{{AFX_MSG(CTCRelayRegDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTcButton1();
	afx_msg void OnSelchangeTcCombo1();
	afx_msg void OnPaint();
	afx_msg void OnTcButton5();
	afx_msg void OnOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeTcCombo2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCRELAYREGDLG_H__17DFB704_5E96_42BE_AB20_4D360228BF0F__INCLUDED_)
