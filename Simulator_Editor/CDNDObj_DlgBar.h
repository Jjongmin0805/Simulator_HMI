#pragma once
#include <afxext.h>
#include "resource.h"
#include "./Combobox/SkinCombobox.h"
#include "../DND_Manager/CDND_Manager.h"

#include "CDNDObj_Symbol_Tap.h"
#include "CDNDObj_KASIM_SW_TAP.h"
#include "CDNDObj_KASIM_CONSUMER_TAP.h"
#include "CDNDObj_KASIM_GENERATEUNIT_TAP.h"
#include "CDNDObj_KASIM_JUNCTION_TAP.h"
#include "CDNDObj_KASIM_PRDE_TAP.h"
#include "CDNDObj_KASIM_PRDE_RECLOSER_TAP.h"
#include "CDNDObj_KASIM_TR_TAP.h"
#include "CDNDObj_KASIM_SUBS_TAP.h"
#include "CDNDObj_KASIM_CB_TAP.h"
#include "CDNDObj_KASIM_GENUNIT_TAP.h"
#include "CDNDObj_KASIM_MTR_TAP.h"

class CDNDObj_DlgBar :
	public CDialogBar
{
	DECLARE_DYNAMIC(CDNDObj_DlgBar)
public:
	CDNDObj_DlgBar(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDNDObj_DlgBar();

	enum { IDD = IDD_DNDOBJECT_DLG };


	BOOL Create(CWnd* pParentWnd, UINT nStyle);
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT InitDialog(WPARAM wp, LPARAM lp);
	afx_msg BOOL	OnInitDialog();

	//CSkinCombobox				m_ctrCombo;
	virtual void DoDataExchange(CDataExchange* pDX);


protected:
	CDND_Switch*	m_pDND_Switch;

	int				m_nTap_Object;
	int				m_nPRED_Tap_Object;
public:
	void		SetSelect_DNDObject(CDND_Object* pDNDObj);

	afx_msg void OnBnClickedDndobjectDlgBtn2();
	afx_msg void OnUpdateUI_Btn2(CCmdUI *pCmdUI);


	CTabCtrl m_TObject_Tap;

	CDNDObj_Symbol_Tap*					 m_TObject_Symbol_Tap;
	CDNDObj_KASIM_SW_TAP*				 m_TObject_KASIM_SW_Tap;
	CDNDObj_KASIM_JUNCTION_TAP*			 m_TObject_KASIM_JUNCTION_Tap;
	CDNDObj_KASIM_CONSUMER_TAP*			 m_TObject_KASIM_CONSUMER_Tap;
	CDNDObj_KASIM_GENERATEUNIT_TAP*		 m_TObject_KASIM_GENERATEUNIT_Tap;
	CDNDObj_KASIM_PRDE_TAP*				 m_TObject_KASIM_PRDE_Tap;
	CDNDObj_KASIM_PRDE_RECLOSER_TAP*	 m_TObject_KASIM_PRDE_RECLOSER_Tap;
	CDNDObj_KASIM_TR_TAP*				 m_TObject_KASIM_TR_Tap;
	CDNDObj_KASIM_SUBS_TAP*				 m_TObject_KASIM_SUBS_Tap;
	CDNDObj_KASIM_CB_TAP*				 m_TObject_KASIM_CB_Tap;
	CDNDObj_KASIM_GENUNIT_TAP*			 m_TObject_KASIM_GENUNIT_Tap;
	CDNDObj_KASIM_MTR_TAP*				 m_TObject_KASIM_MTR_Tap;


	afx_msg void OnTcnSelchangeDndobjectDlgTab(NMHDR *pNMHDR, LRESULT *pResult);
};

