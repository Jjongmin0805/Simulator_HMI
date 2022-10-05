#pragma once
#include "../Ctrl_Object/MessageDlg.h"
#include "../Ctrl_Object/PNOCtrl_SkinFrame_POP_Dialog.h"


// CRelcoserSetDlg 대화 상자

class CRelcoserSetDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(CRelcoserSetDlg)

public:
	CRelcoserSetDlg(int nPrdeIdx, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRelcoserSetDlg();

	void													UpdateCombo();

	int														m_nPRDEIdx;//보호기기정보 인덱스

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECLOSER_SET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrPFastCom;
	CComboBox m_ctrPDelayCom;
	CComboBox m_ctrGFastCom;
	CComboBox m_ctrGDelayCom;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
