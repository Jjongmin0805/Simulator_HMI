#pragma once
#include "CView_Base.h"
#include "./Combobox/SkinCombobox.h"
#include "./ListCtrl/SkinListCtrl.h"
#include "./Button/Skinbutton.h"

class CView_SCA_rst :
	public CView_Base
{
public:
	CView_SCA_rst();
	~CView_SCA_rst();

	virtual void			SetVIewID() { m_nViewID = VIEW_ID_SCA_RESULT; };
	virtual	void			InitData();
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnControlbutton_click_Radio1();
	afx_msg void OnControlbutton_click_Radio2();
	afx_msg void OnSCA_rstCombo1SelectChange();
	afx_msg void OnSCA_rstCombo2SelectChange();
	afx_msg void OnSCA_rstCombo4SelectChange();
	afx_msg void OnSCA_rstCombo5SelectChange();
	afx_msg void OnControlbutton_click_Run();
	afx_msg void OnControlbutton_click_Report();
	afx_msg void OnControlbutton_click_Apply();
	afx_msg void OnSCA_ListCtrlDBClick_1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSCA_ListCtrlDBClick_2(NMHDR *pNMHDR, LRESULT *pResult);


protected:
	CRect													m_rectBack[3];
	CRect													m_rectSetting[3];
	CRect													m_rectTitle[3];

	CFont													m_headerfont;
	CFont													m_listfont;
	CSkinCustomList											m_ctrList[2];		//////////////////////// 0 = 최대고장, 1 = 고장점지정
	CRect													m_rectCtrl_List[2]; ////////////////////////

	CFont													m_font_Combobox;
	CRect													m_rectCtrl_Combobox[5];
	CSkinCombobox											m_ctrCombo[5];

	CSkinCheckbox											m_ctrBtn_Radio[2];
	CRect													m_rectCtrl_Radio[2];

	CSkinButton												m_btn_ctrl[3];			//////////////////////// 4 = 삭제
	CRect													m_btn_ctrl_rect[3];		//////////////////////// 4 = 삭제

	CEdit													m_ctrEdit[7];
	CRect													m_rectCtrl_Edit[7];

	//////////////////////////////////////
	void													Create_Combobox();
	void													Create_ListCtrl();
	void													Create_Btn();
	void													Create_Edit();

	void													MoveSize_Setting();
	void													MoveSize_List();

	void													Draw_Setting_Tag_1(CDC* pDC, Graphics &graphics);

	////////////////////////////////////////////////////////////////////
	int														m_nSelect_SS_GEN ;
	int														m_nSelect_TR;
	int														m_nSelect_GND;
	void													Update_Combo1();

	void													Update_List_Max();
	void													Update_List_Pos();
public:
	virtual void											recv_Appl(int nAppl);
	virtual void											recv_Init();
	virtual void											recv_Wnd(CWndMsgData* pWndMsgData);
	virtual void											Redraw_Ctrl();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

