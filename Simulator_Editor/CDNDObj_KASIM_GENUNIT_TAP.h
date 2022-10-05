
//////////////////////////////////
#pragma once
#include "afxwin.h"
#include <atldbcli.h>
#include <atldbsch.h>
#include "../DND_Manager/CDND_Manager.h"

#include "StyleDef.h"
// CDNDObj_KASIM_GENERATEUNIT_TAP 대화 상자
class CDNDObj_KASIM_GENUNIT_TAP : public CDialog
{
	DECLARE_DYNAMIC(CDNDObj_KASIM_GENUNIT_TAP)

public:
	CDNDObj_KASIM_GENUNIT_TAP(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDNDObj_KASIM_GENUNIT_TAP();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum {	IDD = IDD_DNDOBJECT_TPA_KASIM_GENUNIT_DLG};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
protected:
	CDND_Switch*	m_pSwitch;

	int				m_nGENERATEUINT_CSVID;
	int				m_nGENUNIT_CSVID;

	int				m_nGenUnitIndex;
	int				m_ListGenUnit[100];
	//이미지?

	CComboBox		m_ctrCombo1[1];

	CFont			m_fontDef;
	CFont			m_fontBold;
	CListCtrl m_ctrList;
public:
	virtual BOOL	OnInitDialog();
	//이미지?
	//afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	//afx_msg HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void	OnPaint();

	void			SetSelect_DNDObject(CDND_Object* pDNDObj);
	void			LoadKASIM();
	afx_msg void	OnBnClickedDndobjectKasimGenunitDlgBtn1();
	afx_msg void	OnBnClickedDndobjectKasimGenunitDlgBtn2();
	afx_msg void	OnBnClickedDndobjectKasimGenunitDlgBtn3();
	afx_msg void	OnUpdateUI_Btn1(CCmdUI *pCmdUI);
	afx_msg void	OnUpdateUI_Btn2(CCmdUI *pCmdUI);
	afx_msg void	OnUpdateUI_Btn3(CCmdUI *pCmdUI);
	afx_msg void	OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);

	BOOL PreTranslateMessage(MSG* pMsg);
};
