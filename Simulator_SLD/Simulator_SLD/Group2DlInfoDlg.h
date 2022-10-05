#pragma once
#include "StyleDef.h"

// CGroup2DlInfoDlg 대화 상자

class CGroup2DlInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CGroup2DlInfoDlg)

public:
	CGroup2DlInfoDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGroup2DlInfoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GROUP2_DLINFO_DLG };
#endif

protected:
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
};
