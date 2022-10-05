#pragma once


// CView_PDVR_rst_DGDlg 대화 상자

class CView_PDVR_rst_DGDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CView_PDVR_rst_DGDlg)

public:
	CView_PDVR_rst_DGDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CView_PDVR_rst_DGDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PDVR_DG_SET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPdvrDgSetDlgBtn1();
	afx_msg void OnBnClickedPdvrDgSetDlgRadio1();
	afx_msg void OnBnClickedPdvrDgSetDlgRadio2();

protected:
	CButton			m_ctrRadio[2];
	CComboBox		m_ctrCombo;

	void			SetData_DGInfo();

		
public:

	int				m_nIndex;
	
	
};
