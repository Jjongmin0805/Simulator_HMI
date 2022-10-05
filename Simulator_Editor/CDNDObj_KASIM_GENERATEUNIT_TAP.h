#pragma once
#include "afxwin.h"
#include <atldbcli.h>
#include <atldbsch.h>
#include "../DND_Manager/CDND_Manager.h"

#include "StyleDef.h"
// CDNDObj_KASIM_GENERATEUNIT_TAP 대화 상자
class CDNDObj_KASIM_GENERATEUNIT_TAP : public CDialog
{
	DECLARE_DYNAMIC(CDNDObj_KASIM_GENERATEUNIT_TAP)

public:
	CDNDObj_KASIM_GENERATEUNIT_TAP(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDNDObj_KASIM_GENERATEUNIT_TAP();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DNDOBJECT_TPA_KASIM_GENERATEUNIT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


	DECLARE_MESSAGE_MAP()
protected:
	CDND_Switch*	m_pSwitch;

	int				m_nGENERATEUINT_CSVID;
	int				m_nND_CSVID;
	int				m_nIJ_CSVID;
	int				m_nESS_CSVID;

	CComboBox		m_ctrCombo1[1];
	CComboBox		m_ctrCombo3[1];
	CComboBox		m_ctrCombo5[1];
	CComboBox		m_ctrCombo10[1];
	CComboBox		m_ctrCombo11[1];
	//이미지?
	CFont																	m_fontDef;
	CFont																	m_fontBold;
public:
	virtual BOOL	OnInitDialog();

	void			SetSelect_DNDObject(CDND_Object* pDNDObj);
	void			LoadKASIM();
	afx_msg void OnBnClickedDndobjectKasimGenDlgBtn1();
	afx_msg void OnUpdateUI_Btn1(CCmdUI *pCmdUI);

	BOOL PreTranslateMessage(MSG* pMsg);

	//이미지?
// 	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
// 	afx_msg HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void	OnPaint();
};
