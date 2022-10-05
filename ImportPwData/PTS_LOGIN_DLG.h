#pragma once
#include "Resource.h"

// CPTS_LOGIN_DLG 대화 상자입니다.

class CPTS_LOGIN_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(CPTS_LOGIN_DLG)

public:
	CPTS_LOGIN_DLG(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPTS_LOGIN_DLG();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PTS_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	BOOL CreateSession();
	afx_msg void OnBnClickedPtsLoginDlgBtn();

	CDataSource m_Connect;
	CSession    m_Session;
};
