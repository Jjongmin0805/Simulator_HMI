#pragma once
#include "CView_Base.h"
#include "./ListCtrl/SkinListCtrl.h"
#include "./Button/Skinbutton.h"
#include "../DataManager/CDataManager.h"
#include "./Combobox/SkinCombobox.h"

class CView_DNR_rst :
	public CView_Base
{

public:
	CView_DNR_rst();
	~CView_DNR_rst();

	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnControlbutton_click_Run();
	afx_msg void OnListCtrlClick_2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnControlbutton_click_Check1();
	afx_msg void OnControlbutton_click_Check2();
	afx_msg void OnControlbutton_click_Check3();
	afx_msg void OnControlbutton_click_Check4();
	afx_msg void OnControlbutton_click_Check5();
	afx_msg void OnControlbutton_click_Check6();
	afx_msg void OnControlbutton_click_Check7();

	virtual void			SetVIewID() { m_nViewID = VIEW_ID_DNR_RESULT; };
	virtual	void			InitData();

protected:
	CRect													m_rectBack[5];
	CRect													m_rectTitle[4];
	CRect													m_rectSetting[3];

	CFont													m_headerfont;
	CFont													m_listfont;
	CSkinCustomList											m_ctrList[5];
	CRect													m_rectCtrl_List[5];

	CSkinButton												m_ctrBtn[1];
	CRect													m_rectCtrl_Btn[1];

	CFont													m_font_check;
	CSkinCheckbox											m_ctrBtn_Check[12];
	CRect													m_rectCtrl_Check[12];

	CFont													m_font_Combobox;
	CRect													m_rectCtrl_Combobox[1];
	CSkinCombobox											m_ctrCombo[1];									////// MTR
	CString													m_strComboValue[1];

	void													Create_Combobox();
	void													Create_ListCtrl();
	void													Create_Btn();

	void													MoveSize_Setting();
	void													MoveSize_List();

	void													Draw_Setting_Tag_1(CDC* pDC, Graphics &graphics);		

	void													GetCheckList_SS(CIntArray *pArray_Idx);
	void													UpdateList1();
	void													UpdateList2(int nSol_Idx);
	void													UpdateList3(int nSol_Idx);
	void													UpdateList4(int nSol_Idx);


	void													InitData_Substation();
	void													InitData_DNRopt();

public:
	virtual void											recv_Appl(int nAppl);
	virtual void											recv_Init();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

