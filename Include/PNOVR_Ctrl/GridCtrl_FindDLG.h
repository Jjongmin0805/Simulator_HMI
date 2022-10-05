#pragma once
#include "afxwin.h"


// CGridCtrl_FindDLG ��ȭ �����Դϴ�.

class CGridCtrl_FindDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CGridCtrl_FindDLG)

public:
	CGridCtrl_FindDLG(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGridCtrl_FindDLG();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GRIDCTRL_FIND };

	CPoint							GetSearchFirstCell();
	void							SetSearchFirstCell( LONG nX, LONG nY );
	void							SetSearchFirstCell( CPoint ptCell );
	CString							GetFindString();


protected:
	CPoint							m_ptSearchCell;
	CString							m_szFindValue;

	CWnd*							m_pThisParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedGridctrlFindButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
