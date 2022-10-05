#pragma once
#include "Resource.h"
#include "MyCtrl.h"

// CUserInfoDlg 대화 상자

class AFX_EXT_CLASS CUserInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserInfoDlg)

public:
	CUserInfoDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUserInfoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERINFO_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedUserinfoDlgBtn1();
	afx_msg void OnBnClickedUserinfoDlgBtn2();
	afx_msg void OnBnClickedUserinfoDlgBtn3();

	CCustomList m_ctrList;

	void	SetData_List();


};
