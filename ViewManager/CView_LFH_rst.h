#pragma once
#include "CView_Base.h"

#include "./Combobox/SkinCombobox.h"
#include "./ListCtrl/SkinListCtrl.h"
#include "./Button/Skinbutton.h"


class CGraph_DLE :
	public CObject
{

public:
	CGraph_DLE(void) {};
	~CGraph_DLE(void) {};


public:
	int			m_nIndex;
	double		m_dValue[3];

};

typedef CTypedPtrArray<CObArray, CGraph_DLE*> CGraph_DLE_Array;
///////////////////////////////////////////////////////////////////////////////

class CView_LFH_rst :
	public CView_Base
{
public:
	CView_LFH_rst();
	~CView_LFH_rst();

public:
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	virtual void			SetVIewID() { m_nViewID = VIEW_ID_LF_HISTORY_RESULT; };
	virtual	void			InitData();
	virtual void			Redraw_Ctrl();

public:
	virtual void											recv_Appl(int nAppl);
	virtual void											recv_Init();


protected:
	//////////////////////// ¿µ¿ª 3		: Setting , Left 3 , Right 3
	//////////////////////// setting	: combo 2
	//////////////////////// left		: datetime 2 , combo 2 ? , title 2 , btn 1 , list 2
	//////////////////////// right		: datetime 1 , title 1 , btn 1 , graph 1, list 1 

	CRect													m_rectCtrl[3];
	CRect													m_rectCtrl_Left[3];
	CRect													m_rectCtrl_Right[3];
	/////////////
	CFont													m_font_Combobox;
	CRect													m_rectCtrl_Combobox[5];
	CSkinCombobox											m_ctrCombo[5];
	CString													m_strComboValue[5];
	///////////
	CSkinButton												m_btn_ctrl[4];
	CRect													m_btn_ctrl_rect[4];

	CFont													m_headerfont;
	CFont													m_listfont;

	CRect													m_rectListTitle[3];
	CRect													m_rectListUnit[3];
	CRect													m_rectList[3];
	CSkinListCtrl											m_ctrList[3];

	CRect													m_rectCtrl_Date[3];
	CDateTimeCtrl											m_ctrDate[3];

	CRect													m_rectCtrl_Graph;
	CGraph_DLE_Array										m_Array_Graph_DLE;

protected:
	void													Create_Combobox();
	void													Create_ListCtrl();
	void													Create_Btn();
	void													Create_DateTimeCtrl();

	void													MoveSize_Setting();
	void													MoveSize_Left();
	void													MoveSize_Right();

	void													Draw_Setting_Tag(CDC* pDC, Graphics &graphics);
	void													Draw_Right_Title(CDC* pDC, Graphics &graphics);
	void													Draw_Right_Graph(CDC* pDC, Graphics &graphics);

	void													SetComboxData_Subs();

	void													Update_DL_History();
	void													Get_ChartData_DLE();
	void													Group_Data_Clear();

	///////////////////////
	afx_msg void OnLFH_rstCombo1SelectChange();
	afx_msg void OnLFH_rstCombo3SelectChange();
	afx_msg void OnControlbutton_click_Run_1();
	afx_msg void OnControlbutton_click_Run_2();
	afx_msg void OnControlbutton_click_Run_3();
	afx_msg void OnControlbutton_click_Run_4();
};

