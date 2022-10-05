#pragma once
#include "resource.h"

// CApplOptDlg 대화 상자

class AFX_EXT_CLASS CApplOptDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CApplOptDlg)

public:
	CApplOptDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CApplOptDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPL_OPT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CMFCPropertyGridCtrl m_ctrProp;


	void		Create_Property_NCP();
	void		Create_Property_DLE();
	void		Create_Property_RPF();
	void		Create_Property_DNR();
	void		Create_Property_SOP();
	void		Create_Property_PDVR();
	void		Create_Property_PCE();

	void		Save_Property_NCP();
	void		Save_Property_DLE();
	void		Save_Property_RPF();
	void		Save_Property_DNR();
	void		Save_Property_SOP();
	void		Save_Property_PDVR();
	void		Save_Property_PCE();


	CComboBox m_ctrCombo;
	afx_msg void OnCbnSelchangeApplOptDlgCombo1();
	afx_msg void OnBnClickedOk();
};
