#pragma once

#include "resource.h"
// CDataShareDlg 대화 상자

class AFX_EXT_CLASS CDataShareDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataShareDlg)

public:
	CDataShareDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDataShareDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATASHARE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDatashareDlgBtn1();
	afx_msg void OnBnClickedDatashareDlgBtn2();
	afx_msg void OnBnClickedDatashareDlgBtn3();

	CComboBox m_ctrCombo;
	CListCtrl m_ctrList;

	void UpdateList();
	afx_msg void OnCbnSelchangeDatashareDlgCombo1();
};
