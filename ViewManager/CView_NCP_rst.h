#pragma once

#include "CView_Base.h"
#include "./Combobox/SkinCombobox.h"
#include "./ListCtrl/SkinListCtrl.h"
#include "./Button/Skinbutton.h"

class CView_NCP_rst :
	public CView_Base
{
public:
	CView_NCP_rst();
	~CView_NCP_rst();

	virtual void			SetVIewID() { m_nViewID = VIEW_ID_NCP_RESULT; };
	virtual	void			InitData();

	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void On_NCP_rst_Combo1SelectChange();
	afx_msg void On_NCP_rst_Combo2SelectChange();
	afx_msg void On_NCP_rst_Combo3SelectChange();
	afx_msg void On_NCP_rst_Combo4SelectChange();
	afx_msg void On_NCP_rst_Combo5SelectChange(); 
	afx_msg void On_NCP_rst_Btn1Click_Run();

	CRect													m_rectBack[2];		////////////// 자동화 개폐기, 독립모선, 비가압
	CRect													m_rectTitle[3];
	CRect													m_rectSetting[1];

	CFont													m_headerfont;
	CFont													m_listfont;
	CSkinCustomList											m_ctrList[3];
	CRect													m_rectCtrl_List[3];

	CSkinButton												m_ctrBtn[1];
	CRect													m_rectCtrl_Btn[1];

	CFont													m_font_Combobox;
	CRect													m_rectCtrl_Combobox[5];
	CSkinCombobox											m_ctrCombo[5];

	void													Create_Combobox();
	void													Create_ListCtrl();
	void													Create_Btn();

	void													MoveSize_List_1();
	void													MoveSize_List_2();


	void													Update_List_1();
	void													Update_List_2();
	void													Update_List_3();



	

public:
	virtual void											recv_Appl(int nAppl);
	virtual void											recv_Init();
};

