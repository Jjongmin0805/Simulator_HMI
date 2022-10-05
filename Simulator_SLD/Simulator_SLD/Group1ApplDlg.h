#pragma once
#include "StyleDef.h"

// CGroup1ApplDlg 대화 상자

class CGroup1ApplDlg : public CDialog
{
	DECLARE_DYNAMIC(CGroup1ApplDlg)

public:
	CGroup1ApplDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGroup1ApplDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GROUP1_APPL_DLG };
#endif

	void																	SetData(int nCompType, int nCompIdx);
	void																	SetApplData();

	double																	GetViolation(int nVVMIdx, double dV);

protected:
	int																		m_nCompType;
	int																		m_nCompIdx;
	int																		m_nGNDIdx;

	CFont																	m_fontDef;
	CFont																	m_fontBold;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedGroup13RadioPhaseA();
	afx_msg void OnBnClickedGroup13RadioPhaseB();
	afx_msg void OnBnClickedGroup13RadioPhaseC();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
