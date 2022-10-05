#pragma once
#include "../Ctrl_Object/MessageDlg.h"
#include "../Ctrl_Object/PNOCtrl_SkinFrame_POP_Dialog.h"

#define DOUBLE_COMP_RANGE_VALUE		0.0000001
// CRelaySetDlg 대화 상자

class CRelaySetDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(CRelaySetDlg)

public:
	CRelaySetDlg(int nPrdeIdx, BOOL bCustomer, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRelaySetDlg();

	void													UpdateCombo();

	double													SetAutoValue(double dValue, int nMachineID, int nOgKind, int nFdKind);
	int														CheckRelayAD(int nMachineID);

	int														m_nPRDEIdx;//보호기기정보 인덱스
	BOOL													m_bCustomer;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RELAY_SET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_ctrOCRTypeCom;
	CComboBox m_ctrOCGRTypeCom;
	afx_msg void OnCbnSelchangeComOcrType();
	afx_msg void OnCbnSelchangeComOcgrType();
};
