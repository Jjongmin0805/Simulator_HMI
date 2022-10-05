#pragma once
#include "resource.h"
#include "PNOCtrl_SkinFrame_POP_Dialog.h"

// CMessageDlg 대화 상자

class AFX_EXT_CLASS CMessageDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(CMessageDlg)

public:
	CMessageDlg(CString szTitle, int nDlgMode = MB_OK, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMessageDlg();

	void				SetMessage(CString szMsg) { m_szMessage = szMsg; };
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESSAGE_DLG };
#endif

protected:
	int					m_nMode;
	CString				m_szTitle;
	CString				m_szMessage;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
