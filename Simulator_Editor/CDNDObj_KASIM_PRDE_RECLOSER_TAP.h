#pragma once
#include "afxwin.h"
#include <atldbcli.h>
#include <atldbsch.h>
#include "../DND_Manager/CDND_Manager.h"

// CDNDObj_KASIM_PRDE_TAP 대화 상자

class CDNDObj_KASIM_PRDE_RECLOSER_TAP : public CDialog
{
	DECLARE_DYNAMIC(CDNDObj_KASIM_PRDE_RECLOSER_TAP)

public:
	CDNDObj_KASIM_PRDE_RECLOSER_TAP(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDNDObj_KASIM_PRDE_RECLOSER_TAP();

	// 대화 상자 데이터입니다.
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DNDOBJECT_TPA_KASIM_PRDE_RECLOSER_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	CDND_Switch*	m_pSwitch;

	int				m_nPRDE_CSVID;
	CComboBox		m_ctrCombo1[1];
	CComboBox		m_ctrCombo2[1];
	CComboBox		m_ctrCombo3[1];
	CComboBox		m_ctrCombo4[1];

public:
	virtual BOOL	OnInitDialog();
	void			SetSelect_DNDObject(CDND_Object* pDNDObj);
	void			Load_MACHINE();
	void			LoadKASIM();
	afx_msg void OnBnClickedDndobjectKasimDlgBtn1();
	afx_msg void OnUpdateUI_Btn1(CCmdUI *pCmdUI);

	BOOL PreTranslateMessage(MSG* pMsg);
};
