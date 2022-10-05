#pragma once


// CRelaySetDlg 대화 상자
#include "Resource.h"


#define		RELAY_EDIT_MODE_ADD			 0
#define		RELAY_EDIT_MODE_EDIT		 1

class CRelaySetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRelaySetDlg)

public:
	CRelaySetDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRelaySetDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RELAYSET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedRelaysetDlgBtn1();
	afx_msg void OnCbnSelchangeRelaysetDlgCombo1();

	CComboBox m_ctrCombo;
	CComboBox m_ctrCombo_Curve;

	int		m_nMode;
	int		m_nID;
	int		m_nType;
	int		m_nCurve;
	CString m_strName;
	CString m_strManuf;

	
	BOOL Check2Name();
	int  GetMaxID();

	void Update_Data_D();

	void Insert_Data_D();

	void InitData_Curve();
	
	afx_msg void OnBnClickedRelaysetDlgBtn2();
};
