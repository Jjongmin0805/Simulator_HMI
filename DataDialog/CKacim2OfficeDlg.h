#pragma once


#include "Resource.h"

// CKacim2OfficeDlg 대화 상자

class AFX_EXT_CLASS CKacim2OfficeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKacim2OfficeDlg)

public:
	CKacim2OfficeDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CKacim2OfficeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KACIM_OFFCIE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedKacimOffcieDlgBtn1();
	afx_msg void OnBnClickedKacimOffcieDlgBtn2();
	afx_msg void OnCbnSelchangeKacimOffcieDlgCombo1();


	CComboBox m_ctrCombo[2];

	void Set_Center();
	void Set_Office();
	afx_msg void OnBnClickedKacimOffcieDlgRadio1();
	afx_msg void OnBnClickedKacimOffcieDlgRadio2();
};
