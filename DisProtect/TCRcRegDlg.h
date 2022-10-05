#if !defined(AFX_TCRCREGDLG_H__45B1CA19_334A_4180_AB8F_7FDA64384A7F__INCLUDED_)
#define AFX_TCRCREGDLG_H__45B1CA19_334A_4180_AB8F_7FDA64384A7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCRcRegDlg.h : header file
//
#include "resource.h"
#include "CurveObj.h"
/////////////////////////////////////////////////////////////////////////////
// CTCRcRegDlg dialog

class AFX_EXT_CLASS CTCRcRegDlg : public CDialog
{
// Construction
public:
	CTCRcRegDlg(CSession* pDB, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTCRcRegDlg)
	enum { IDD = IDD_RECLOSER_CURVE_DLG };
	CListBox	m_ctrPU;
	CComboBox	m_ctrRcCurve;
	CComboBox	m_ctrRcType;
	int		m_nType;
	int		m_bSecond;
	float	m_fA;
	float	m_fB;
	float	m_fC;
	float	m_fD;
	float	m_fE;
	float	m_fF;
	float	m_fPU1;
	float	m_fPU2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCRcRegDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	CClrButton m_ctrButton[7];
	CBitmapButton m_ctrHButton;
	void UpdateList();
	void DrawIndex(CDC *pDC, CRect rect);
	void TextGrid(CDC *pDC, CRect rect);
	void DrawGrid(CDC *pDC, CRect rect);
	CSession* m_pDB;
	CCurveObj* m_pCurve;
	// Generated message map functions
	//{{AFX_MSG(CTCRcRegDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	afx_msg void OnTcButton5();
	afx_msg void OnTcButton1();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeTcCombo1();
	afx_msg void OnTcRadio2();
	afx_msg void OnTcRadio3();
	afx_msg void OnSelchangeTcCombo2();
	afx_msg void OnSelchangeTcListbox1();
	afx_msg void OnTcButton2();
	afx_msg void OnTcButton4();
	afx_msg void OnTcButton3();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeTcCombo3();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCRCREGDLG_H__45B1CA19_334A_4180_AB8F_7FDA64384A7F__INCLUDED_)
