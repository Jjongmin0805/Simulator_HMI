#pragma once


// CView_PCE_rst_CUSDlg 대화 상자

class CView_PCE_rst_CUSDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CView_PCE_rst_CUSDlg)

public:
	CView_PCE_rst_CUSDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CView_PCE_rst_CUSDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PCE_RST_CUS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	int							GetData_Idx() { return m_nIndex; };
	void						Update_Data();

	void						Draw_EditRound(CDC* pDC);

public:
	int							m_nIndex;
	int							m_nType;
	CWnd*						m_pMsg_Wnd;
	int							m_nEndEdit;

	int							m_nMachine_OCR;
	int							m_nMachine_OCGR;

	//afx_msg void OnNMThemeChangedPceRstRcDlgEdit1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedPceRstCUSDlgBtn1();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangePceRstCUSDlgEdit9();
	afx_msg void OnEnChangePceRstCUSDlgEdit20();
	afx_msg void OnEnChangePceRstCUSDlgEdit1();
	afx_msg void OnEnChangePceRstCUSDlgEdit5();
	afx_msg void OnEnChangePceRstCUSDlgEdit12();
	afx_msg void OnEnChangePceRstCUSDlgEdit16();
	afx_msg void OnEnChangePceRstCUSDlgEdit26();
	afx_msg void OnEnChangePceRstCUSDlgEdit27();
};
