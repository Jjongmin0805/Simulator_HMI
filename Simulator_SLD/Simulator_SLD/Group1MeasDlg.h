#pragma once
#include "StyleDef.h"

// CGroup1MeasDlg 대화 상자
#define WM_MODIFY_MEASURE_MSG												WM_USER + 3000

class CGroup1MeasDlg : public CDialog
{
	DECLARE_DYNAMIC(CGroup1MeasDlg)

public:
	CGroup1MeasDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGroup1MeasDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GROUP1_MEAS_DLG };
#endif

	void																	SetData(int nCompType, int nCompIdx);
	void																	SetMeasureData();
	BOOL																	ModifyMeasureData();
	BOOL																	InputErrorCheck(CString szData);

protected:
	int																		m_nCompType;
	int																		m_nCompIdx;
	int																		m_nStatus;

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
	int m_nPhaseType;
	afx_msg void OnBnClickedGroup12RadioPhaseA();
	afx_msg void OnBnClickedGroup12RadioPhaseB();
	afx_msg void OnBnClickedGroup12RadioPhaseC();
	afx_msg void OnBnClickedGroup12BtnModify();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
