#pragma once
#include "afxwin.h"
#include <atldbcli.h>
#include <atldbsch.h>
#include "../DND_Manager/CDND_Manager.h"

// CDNDObj_KASIM_MTR_TAP 대화 상자

class CDNDObj_KASIM_MTR_TAP : public CDialog
{
	DECLARE_DYNAMIC(CDNDObj_KASIM_MTR_TAP)

public:
	CDNDObj_KASIM_MTR_TAP(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDNDObj_KASIM_MTR_TAP();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DNDOBJECT_TPA_KASIM_MTR_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	CDND_Switch*	m_pSwitch;

	int				m_nSUBS_CSVID;
	int				m_nSUBS_NDID;
	int				m_nSUBS_BRID;
	int				m_nMTR_CSVID;
	int				m_nMTRIndex;
	int				m_ListMTR[100];
// 
 	CListCtrl m_ctrListMTR;

public:
	virtual BOOL OnInitDialog();
	void			SetSelect_DNDObject(CDND_Object* pDNDObj);
	void			LoadKASIM();

	int				GET_MTR_BANK(int nSSID);


	afx_msg void	OnBnClickedDndobjectKasimMTRDlgBtn1();
	afx_msg void	OnBnClickedDndobjectKasimMTRDlgBtn2();
	afx_msg void	OnBnClickedDndobjectKasimMTRDlgBtn3();
	afx_msg void	OnUpdateUI_Btn1(CCmdUI *pCmdUI);
	afx_msg void	OnUpdateUI_Btn2(CCmdUI *pCmdUI);
	afx_msg void	OnUpdateUI_Btn3(CCmdUI *pCmdUI);
	afx_msg void	OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void	OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);

	BOOL PreTranslateMessage(MSG* pMsg);
};

