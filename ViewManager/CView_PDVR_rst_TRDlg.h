#pragma once


// CView_PDVR_rst_TRDlg 대화 상자

class CView_PDVR_rst_TRDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CView_PDVR_rst_TRDlg)

public:
	CView_PDVR_rst_TRDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CView_PDVR_rst_TRDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PDVR_TR_SET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPdvrTrSetDlgBtn1();

public:
	int						m_nIndex;
	int						m_nMode;


protected:
	CComboBox				m_ctrCombo;


	void					SetData_TRInfo();

	
	
};
