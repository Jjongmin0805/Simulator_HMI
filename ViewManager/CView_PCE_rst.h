#pragma once
#include "CView_Base.h"
#include "./Combobox/SkinCombobox.h"
#include "./ListCtrl/SkinListCtrl.h"
#include "./Button/Skinbutton.h"
#include "PNOCtrl_Group.h"
#include "CView_PCE_rst_RelayDlg.h"
#include "CView_PCE_rst_RCDlg.h"
#include "CView_PCE_rst_EFIDlg.h"
#include "CView_PCE_rst_CUSDlg.h"
#include "../DataManager/CDataManager.h"


#define		PCE_STUDY_MODE_PHASE			0
#define		PCE_STUDY_MODE_GROUND			1



class CTCCurve_Data : public CObject
{
public:
	CTCCurve_Data() {};
	~CTCCurve_Data() {};

public:
	CIntArray		m_Array_X_Value;
	CDoubleArray	m_Array_Y_Value;

	void Init()
	{
		m_Array_X_Value.RemoveAll();
		m_Array_Y_Value.RemoveAll();
	};


};

class CView_PCE_rst :
	public CView_Base
{
public:
	CView_PCE_rst();
	~CView_PCE_rst();

	virtual void			SetVIewID() { m_nViewID = VIEW_ID_PCE_RESULT; };
	virtual	void			InitData();

	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnPCE_ListCtrlDBClick_1(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnPCE_rstCombo1SelectChange();
	afx_msg void OnPCE_rstCombo2SelectChange();
	afx_msg void OnPCE_rstCombo5SelectChange();
	afx_msg void OnPCE_rstCombo6SelectChange();

	afx_msg void OnControlbutton_click_check1();
	afx_msg void OnControlbutton_click_check2();
	afx_msg void OnControlbutton_click_Radio1();
	afx_msg void OnControlbutton_click_Radio2();

	afx_msg void OnControlbutton_click_Run();
	afx_msg void OnControlbutton_click_Auto();
	afx_msg void OnControlbutton_click_Rpt();

	afx_msg void OnEditCtrl_1_EN_Change();
	afx_msg void OnEditCtrl_1_EN_Killfocus();
	afx_msg void OnEditCtrl_2_EN_Killfocus();
	afx_msg void OnEditCtrl_3_EN_Killfocus();
	afx_msg void OnEditCtrl_4_EN_Killfocus();
	
	afx_msg void OnCtrl_Range_Btn_Check(UINT id);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg LRESULT OnTabMsg(WPARAM wp, LPARAM lp);

protected:
	CRect													m_rectBack[6];
	CRect													m_rectTitle[3];
	CRect													m_rectGraph[5];


	CFont													m_headerfont;
	CFont													m_listfont;

	CSkinListCtrl											m_ctrList[2];
	
	CFont													m_font_Combobox;
	CRect													m_rectCtrl_Combobox[6];
	CSkinCombobox											m_ctrCombo[6];									////// MTR
	CString													m_strComboValue[6];										


	CSkinCheckbox											m_ctrBtn_Check[20];
	CRect													m_rectCtrl_Check[20];
	CSkinCheckbox											m_ctrBtn_Check_DG;
	CRect													m_rectCtrl_Check_DG;

	CSkinCheckbox											m_ctrBtn_Radio[2];
	CRect													m_rectCtrl_Radio[2];

	CSkinButton												m_btn_ctrl[3];
	CRect													m_btn_ctrl_rect[3];

	CEdit													m_ctrEdit[4];
	CRect													m_rectCtrl_Edit[4];

	CPNOCtrl_Group*											m_pTabGroup;
	CRect													m_rectCtrl_Tab;

	void													Create_Combobox();
	void													Create_ListCtrl();
	void													Create_Btn_Check();
	void													Create_Btn();
	void													Create_Tab();
	void													Create_Edit();
	CView_PCE_rst_RelayDlg*									Create_Tab_Relay();
	CView_PCE_rst_RCDlg*									Create_Tab_RC();
	CView_PCE_rst_EFIDlg*									Create_Tab_EFI();
	CView_PCE_rst_CUSDlg*									Create_Tab_CUS();

	void													MoveSize_Btn_Check();
	void													MoveSize_Combo();
	void													MoveSize_List1();
	void													MoveSize_List2();
	void													MoveSize_Graph();
	void													MoveSize_Btn();
	void													MoveSize_Tab();


	void													Update_List_Path();
	void													Update_Data_PCE();

	double													m_dAmp_Range[2];
	int														Get_X_FirstValue();

	int														m_nSelect_Path;
	CTCCurve_Data											m_TCCurve_Data[5][4];
	CTCCurve_Data											m_TCCurve_Data_COS[2];
	double													m_dOCB_SDelay;
	void                                                    Clear_TCCurveData();
	void													Update_TCCurve_Relay(int nTabIdx, int nIdx,int nPhase,int nSetType);
	void													Update_TCCurve_RC(int nTabIdx, int nIdx, int nPhase, int nFast, int nSetType);
	void													Update_TCCurve_COS(int nNumber, int nSel_COS, int nTCCSET_idx);
	///////////////////////////////
public:
	void													Clear_Data();
	virtual void											recv_Appl(int nAppl);
	virtual void											recv_Init();

	void													SetComboxData_Subs();

	void													Draw_Setting_Tag(CDC* pDC, Graphics &graphics);
	void													Draw_Graph_Tag_1(CDC* pDC, Graphics &graphics);			//////////////// x 축 단위 라인
	void													Draw_Graph_Tag_2(CDC* pDC, Graphics &graphics);

	void													Draw_Graph(CDC* pDC, Graphics &graphics);

	void													Draw_Graph_Data(CDC* pDC, Graphics &graphics, int nTab_Idx, int nLineType, Gdiplus::GraphicsPath* gp_Value, Gdiplus::GraphicsPath* gp_Highlight = NULL);

	void													Draw_EditRound(CDC* pDC);
	

	
	CPoint m_ptSelect;
	
	double													m_dCurve_X_Gap;
	double													m_dCurve_X_Tap;
	double													m_dCurve_Y_MAX;
	int														m_nCurve_X_Base;
	int														m_nCurve_Y_Base;
	int														m_nCurve_Select;
	int														GetSelectCurve(CPoint pt);

	void													Draw_Graph_Data_Select(CDC* pDC, Graphics &graphics, int nTab_Idx, int nLineType,int x,int y, double dSDelay);

};

