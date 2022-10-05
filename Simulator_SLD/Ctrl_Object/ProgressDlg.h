#pragma once
#include "resource.h"
#include "PNOCtrl_SkinFrame_POP_Dialog.h"

// CProgressDlg 대화 상자

class AFX_EXT_CLASS CProgressDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(CProgressDlg)

public:
	CProgressDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CProgressDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRESS_DLG };
#endif

	BOOL					Create(CWnd *pParent = NULL);
	virtual BOOL			DestroyWindow();

	virtual BOOL			OnInitDialog();
	void					SetRange(int nLower, int nUpper);
	void					SetStatus(LPCTSTR lpszMessage);
	int						SetStep(int nStep);
	int						SetPos(int nPos);
	int						StepIt();
	void					PumpMessages();
	CString					UpdatePercent(int nCurrent);
	void					ReEnableParent();
	int						OffsetPos(int nPos);
	void					UpdateMessaage(CString szMsg);

	CProgressCtrl			m_Progress;
	int						m_nLower;
	int						m_nUpper;
	int						m_nStep;
	BOOL					m_bParentDisabled;

	CString					m_szTitle;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNMCustomdrawIdcProgdlgProgress(NMHDR *pNMHDR, LRESULT *pResult);
};
