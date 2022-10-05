#pragma once


// CView_PCE_rst_RelayDlg 대화 상자

class CView_PCE_rst_RelayDlg : public CDialog
{
	DECLARE_DYNAMIC(CView_PCE_rst_RelayDlg)

public:
	CView_PCE_rst_RelayDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CView_PCE_rst_RelayDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PCE_RST_RELAY_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();


	void						Draw_EditRound(CDC* pDC);
	int							GetData_EqType() { return m_nEquipType; };
	int							GetData_Idx() { return m_nIndex; };
	void						Update_Data();


public:
	int							m_nEquipType;///////////////////////////////// CBSW , 고객계전기??
	int							m_nIndex;
	int							m_nMachine_OCR;
	int							m_nMachine_OCGR;

	BOOL						m_bEdit ;

	CWnd*						m_pMsg_Wnd;


	afx_msg void OnBnClickedPceRstRelayDlgBtn1();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangePceRstRelayDlgEdit3();
	afx_msg void OnEnChangePceRstRelayDlgEdit7();
	afx_msg void OnEnChangePceRstRelayDlgEdit9();
	afx_msg void OnEnChangePceRstRelayDlgEdit19();
	afx_msg void OnEnChangePceRstRelayDlgEdit23();
	afx_msg void OnEnChangePceRstRelayDlgEdit25();
	afx_msg void OnNMThemeChangedPceRstRelayDlgEdit3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnUpdatePceRstRelayDlgEdit3();
	afx_msg void OnEnKillfocusPceRstRelayDlgEdit3();
};
