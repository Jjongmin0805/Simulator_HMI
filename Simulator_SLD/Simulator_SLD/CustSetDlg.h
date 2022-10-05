#pragma once
#include "../Ctrl_Object/MessageDlg.h"
#include "../Ctrl_Object/PNOCtrl_SkinFrame_POP_Dialog.h"
#include "RelaySetDlg.h"

// CCustSetDlg 대화 상자

class CCustSetDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(CCustSetDlg)

public:
	CCustSetDlg(int nHVCustIdx, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCustSetDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUST_SET_DLG };
#endif

protected:
	int																	m_nHVCustIdx;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_ctrConnTypeCom;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSetRelay();
};
