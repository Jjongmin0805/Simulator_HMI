#pragma once
#include "afxwin.h"
#include <atldbcli.h>
#include <atldbsch.h>
#include "../DND_Manager/CDND_Manager.h"
// CDNDObj_KASIM_CONSUMER_TAP 대화 상자

class CDNDObj_KASIM_CONSUMER_TAP : public CDialog
{
	DECLARE_DYNAMIC(CDNDObj_KASIM_CONSUMER_TAP)

public:
	CDNDObj_KASIM_CONSUMER_TAP(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDNDObj_KASIM_CONSUMER_TAP();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DNDOBJECT_TPA_KASIM_CONSUMER_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
protected:
	CDND_Switch*	m_pSwitch;

	int				m_nCOUNSUMER_CSVID;
	int				m_nND_CSVID;
	int				m_nIJ_CSVID;
	int				m_nPRDE_CSVID;
	CComboBox		m_ctrCombo1[1];

public:

	virtual			BOOL	OnInitDialog();
	void					SetSelect_DNDObject(CDND_Object* pDNDObj);
	void					LoadKASIM();
	afx_msg		void		OnBnClickedDndobjectKasimConsumerDlgBtn1();
	afx_msg		void		OnUpdateUI_Btn1(CCmdUI *pCmdUI);

	BOOL PreTranslateMessage(MSG* pMsg);
};
