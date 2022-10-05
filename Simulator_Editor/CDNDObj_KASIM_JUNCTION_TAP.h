#pragma once
#include "afxwin.h"
#include <atldbcli.h>
#include <atldbsch.h>
#include "../DND_Manager/CDND_Manager.h"

// CDNDObj_KASIM_JUNCTION_TAP 대화 상자

class CDNDObj_KASIM_JUNCTION_TAP : public CDialog
{
	DECLARE_DYNAMIC(CDNDObj_KASIM_JUNCTION_TAP)

public:
	CDNDObj_KASIM_JUNCTION_TAP(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDNDObj_KASIM_JUNCTION_TAP();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DNDOBJECT_TPA_KASIM_JUNCTION_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
protected:
	CDND_Switch*	m_pSwitch;

	int				m_nJUNCTION_CSVID;

public:
	virtual		BOOL OnInitDialog();	

	void			SetSelect_DNDObject(CDND_Object* pDNDObj);
	void			LoadKASIM();
	afx_msg void OnUpdateUI_Btn1(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedDndobjectKasimJunctionDlgBtn1();

	BOOL PreTranslateMessage(MSG* pMsg);
};
