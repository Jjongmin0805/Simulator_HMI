#pragma once
#include "Resource.h"

// CPTS_LOGIN_DLG ��ȭ �����Դϴ�.

class CPTS_LOGIN_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(CPTS_LOGIN_DLG)

public:
	CPTS_LOGIN_DLG(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPTS_LOGIN_DLG();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PTS_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	BOOL CreateSession();
	afx_msg void OnBnClickedPtsLoginDlgBtn();

	CDataSource m_Connect;
	CSession    m_Session;
};
