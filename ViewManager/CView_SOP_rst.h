#pragma once
#include "CView_Base.h"
#include "./ListCtrl/SkinListCtrl.h"
#include "./Button/Skinbutton.h"
#include "./Combobox/SkinCombobox.h"

class CView_SOP_rst :
	public CView_Base
{
public:
	CView_SOP_rst();
	~CView_SOP_rst();
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnControlbutton_click_Run_1();

	virtual void			SetVIewID() { m_nViewID = VIEW_ID_SOP_RESULT; };
	virtual	void			InitData();
	virtual void			Redraw_Ctrl();

public:
	virtual void											recv_Appl(int nAppl);
	virtual void											recv_Init();


protected:
	CRect													m_rectBack[4];
	CRect													m_rectTitle[3];
	CRect													m_rectSetting[2];

	CFont													m_headerfont;
	CFont													m_listfont;
	CSkinCustomList											m_ctrList[2];		
	CRect													m_rectCtrl_List[2]; 

	CSkinButton												m_ctrBtn[1];
	CRect													m_rectCtrl_Btn[1];

	CFont													m_font_check;
	CSkinCheckbox											m_ctrBtn_Check[4];
	CRect													m_rectCtrl_Check[4];

	//////////////////// 

	CFont													m_font_Combobox;
	CRect													m_rectCtrl_Combobox[1];
	CSkinCombobox											m_ctrCombo[1];

	CTreeCtrl												m_ctrTree;
	CRect													m_rectCtrl_Tree;

	CRect													m_rectCtrl_Date[1];
	CDateTimeCtrl											m_ctrDate[1];

	void													Create_ListCtrl();
	void													Create_Btn();
	void													Create_TreeCtrl();
	void													Create_DateTimeCtrl();
	void													Create_Combobox();

	void													MoveSize_Setting();
	void													MoveSize_List();


	void													Insert_TreeData();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

