#pragma once

#include "resource.h"
// CMemopsDlg 대화 상자

class AFX_EXT_CLASS CMemopsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMemopsDlg)

public:
	CMemopsDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMemopsDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMS_MEMOPS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_ctrCombo;
	afx_msg void OnBnClickedAdmsMemopsDlgBtn1();
};
