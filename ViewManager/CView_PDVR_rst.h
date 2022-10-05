#pragma once
#include "CView_Base.h"
#include "./Combobox/SkinCombobox.h"
#include "./ListCtrl/SkinListCtrl.h"
#include "./Button/Skinbutton.h"
#include "CView_LF_rst.h"
#include "../DataManager/CGraphData.h"
#include "XLSAutomation.h"




class CView_PDVR_rst :
	public CView_Base
{
public:
	CView_PDVR_rst();
	~CView_PDVR_rst();

	virtual void			SetVIewID() { m_nViewID = VIEW_ID_PDVR_RESULT; };
	virtual	void			InitData();
	virtual void			Redraw_Ctrl();

public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnControlbutton_click_Run_PDVR();
	afx_msg void OnControlbutton_click_Opt();
	afx_msg void OnControlbutton_click_Rpt();
	afx_msg void OnControlbutton_click_Cal();
	afx_msg void OnControlbutton_click_Run_PCE();
	afx_msg void OnControlbutton_click_Search1();
	afx_msg void OnControlbutton_click_Search2();
	afx_msg void OnPDVR_rstCombo1SelectChange();
	afx_msg void OnPDVR_rstCombo2SelectChange();
	afx_msg void OnPDVR_rstCombo3SelectChange();
	afx_msg void OnPDVR_rstCombo4SelectChange();
	afx_msg void OnControlbutton_click_Check1();
	afx_msg void OnControlbutton_click_Check2();
	afx_msg void OnControlbutton_click_Check3();
	afx_msg void OnControlbutton_click_Check4();
	afx_msg void OnControlbutton_click_Check5();
	afx_msg void OnControlbutton_click_Check6();
	afx_msg void OnControlbutton_click_Check7();
	afx_msg void OnPDVR_ListCtrlClick_1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPDVR_ListCtrlDBClick_1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPDVR_ListCtrlDBClick_2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPDVR_ListCtrlDBClick_7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickList_2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickList_7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPDVR_ListCtrlDBClick_4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPDVR_ListCtrlDBClick_5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPDVR_ListCtrlDBClick_6(NMHDR *pNMHDR, LRESULT *pResult);
	
	void OnPDVR_rst_Edit_1_Change();
	void OnPDVR_rst_Edit_2_Change();

	afx_msg LRESULT OnList2Ctrl_ComboMsg(WPARAM wp, LPARAM lp);

protected:
	CRect													m_rectBack[4];
	CRect													m_rectTitle[9];//////////////// 5,6,7 = 설비 설정 ; 8 = 누적용량 및 순시전압 변동 검토  
	CRect													m_rectSetting[3];
	CRect													m_rectPDVR[4];
	CRect													m_rectPCE[2];
	//CRect													m_rectTitle_Eq[3];

	CFont													m_headerfont;
	CFont													m_listfont;

	CSkinCustomList											m_ctrList[8];		//////////////////////// 6 제어 불가 ; 7 = 누적용량 및 순시전압
	CRect													m_rectCtrl_List[8]; //////////////////////// 6 제어 불가 

	CFont													m_font_Combobox;
	CRect													m_rectCtrl_Combobox[4];
	CSkinCombobox											m_ctrCombo[4];

	CSkinButton												m_btn_ctrl[8];			//////////////////////// 4 = 삭제
	CRect													m_btn_ctrl_rect[8];		//////////////////////// 4 = 삭제

	CDateTimeCtrl											m_ctrDate[2];
	CImageList m_ImageList;
	//////////////// DataCtrl
	
	CEdit													m_ctrEdit[2];
	CRect													m_rectCtrl_Edit[2];

	CFont													m_font_check;
	CSkinCheckbox											m_ctrBtn_Check[7];
	CRect													m_rectCtrl_Check[7];

	void													Create_Combobox();
	void													Create_ListCtrl();
	void													Create_Btn();
	void													Create_DateTimeCtrl();
	void													Create_Edit();
	void													Create_Btn_Check();

	void													MoveSize_Setting();
	void													MoveSize_PDVR();
	void													MoveSize_PCE();
	void													MoveSize_Btn();


	void													Draw_Setting_Tag_1(CDC* pDC, Graphics &graphics);			//////////////// x 축 단위 라인
	void													Draw_Setting_Tag_2(CDC* pDC, Graphics &graphics);


	void													Draw_Graph(CDC* pDC, Graphics &graphics,CRect rectDraw);
	void													Draw_Graph_Data(CDC* pDC, Graphics &graphics, Gdiplus::RectF r);


	void													Update_Combo1();
	void													DeleteItem_List_2();

	/////////////////////////
	int														m_nNode_MaxCount;
	double													m_dVVM_lmhi, m_dVVM_lmlo;
	double													m_dVVM_lmhi_Tap, m_dVVM_lmlo_Tap;
	//CGraph_infoArray										m_Array_Graph;
	CString													m_strDate[2];
	int														m_nMode;


	CGraphDataArray											m_Array_Graph;
	void													Delete_GraphData();
	void													Update_GraphData();


	void													Update_DGTRData();
	void													Update_PCEData();


	void													Report_PCE(CXLSAutomation* pXL);
	void													Report_PDVR(CXLSAutomation* pXL,int nStartLine);
	void													Report_PDVR_Create_PNG();


	void													test_equipment_data();
	void													test_option_data();
	void													test_protected_list(int nMode);
	void													test_pdvr_graph(int nMode);
	void													test_clear();
	void													test_Draw_Graph(int nMode , CDC* pDC, Graphics &graphics);

public:
	void													test_SetTimer();
	virtual void											recv_Appl(int nAppl);
	virtual void											recv_Init();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

