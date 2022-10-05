#pragma once


// CView_PDVR_rst_RUN_Dlg 대화 상자

class CView_PDVR_rst_RUN_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CView_PDVR_rst_RUN_Dlg)

public:
	CView_PDVR_rst_RUN_Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CView_PDVR_rst_RUN_Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PDVR_RUN_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CButton m_ctrRadio_Main[2];
	CButton m_ctrRadio_Load[2];
	CButton m_ctrRadio_Date[2];
	CButton m_ctrRadio_factor[2];
	CDateTimeCtrl m_ctrDate[2];

	int		m_nGenType;
	int		m_nTrIndex;
	int		m_nMode; //////////////////// 0 =  전압 검토, 1 = 분산형전원 기술평가
	COleDateTime m_timeData[2];
	afx_msg void OnBnClickedPdvrRunDlgRadio7();
	afx_msg void OnBnClickedPdvrRunDlgRadio8();
	afx_msg void OnBnClickedPdvrRunDlgBtn1();
	afx_msg void OnEnChangePdvrRunDlgEdit1();
	afx_msg void OnEnChangePdvrRunDlgEdit8();
	afx_msg void OnBnClickedPdvrRunDlgRadio1();
	afx_msg void OnBnClickedPdvrRunDlgRadio2();
};
