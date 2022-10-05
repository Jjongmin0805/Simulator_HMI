#pragma once

#include "../DND_Manager/CDND_Manager.h"
// CDNDObj_Text_DlgBar 대화 상자

class CDNDObj_Text_DlgBar : public CDialogBar
{
	DECLARE_DYNAMIC(CDNDObj_Text_DlgBar)

public:
	CDNDObj_Text_DlgBar(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDNDObj_Text_DlgBar();

// 대화 상자 데이터입니다.

	enum { IDD = IDD_DND_TEXT_DLG };


	BOOL Create(CWnd* pParentWnd, UINT nStyle);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT InitDialog(WPARAM wp, LPARAM lp);
	afx_msg BOOL	OnInitDialog();

protected:
	CDND_Text*		m_pDND_Text;
public:
	void		SetSelect_DNDObject(CDND_Object* pDNDObj);

	CComboBox							m_ctrCombo[4];

	afx_msg void OnBnClickedDndTextDlgBtn2();
	afx_msg void OnBnClickedDndTextDlgBtn1();

	afx_msg void OnUpdateUI_Btn1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUI_Btn2(CCmdUI *pCmdUI);

};
