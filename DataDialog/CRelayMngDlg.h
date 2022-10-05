#pragma once


// CRelayMngDlg 대화 상자
#include "Resource.h"

class AFX_EXT_CLASS CRelayMngDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRelayMngDlg)

public:
	CRelayMngDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRelayMngDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RERAYMNG_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedReraymngDlgBtn3();
	afx_msg void OnBnClickedReraymngDlgBtn1();
	afx_msg void OnBnClickedReraymngDlgBtn2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMDblclkReraymngDlgList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickReraymngDlgList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRelaymngdlgSetinfo();
	afx_msg void OnRelaymngdlgDel();

	int		m_nMax_ID;
	CListCtrl m_ctrList;

	void UpdateList(CString strFilter = _T(""));

	void Delete_Data();

	

};

	
