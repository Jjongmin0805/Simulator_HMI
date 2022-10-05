#pragma once
#include "CView_Base.h"
#include "./Combobox/SkinCombobox.h"
#include "./ListCtrl/SkinListCtrl.h"
#include "./Button/Skinbutton.h"
#include "../DataManager/CGraphData.h"







class CView_LF_rst :
	public CView_Base
{
public:
	CView_LF_rst();
	~CView_LF_rst();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnInitialUpdate();



//	virtual void			SetVIewState(int nStete = VIEW_STATE_HIDE) ;
	virtual void			SetVIewID() { m_nViewID = VIEW_ID_LOADFLOW_RESULT; };
	virtual	void			InitData();
	virtual void			Redraw_Ctrl();

public:
	
	virtual void OnDraw(CDC* pDC);

	CRect													m_rectCtrl[5];
	CRect													m_rectCtrl_Setting[2];
	CRect													m_rectCtrl_TopLeft[2];
	CRect													m_rectCtrl_TopRight[1];

	CFont													m_font_Combobox;
	CRect													m_rectCtrl_Combobox[3];
	CSkinCombobox											m_ctrCombo[3];
	CString													m_strComboValue[3];

	void													SetComboxData_Subs();

	///////////
	CSkinButton												m_btn_ctrl[2];
	CRect													m_btn_ctrl_rect[2];


	CFont													m_headerfont;
	CFont													m_listfont;

	CRect													m_rectListTitle[5];
	CRect													m_rectListUnit[3];
	CSkinListCtrl											m_ctrList[4];

	CRect													m_rectSetting_Data[5];
	CRect													m_rectCtrl_Date[1];
	CDateTimeCtrl											m_ctrDate[1];
	
	CPoint								m_ptSelect;

	void													ListCtrl_MoveSize();
	void													Setting_MoveSize();
	void													TopLeft_MoveSize();
	void													TopRight_MoveSize();
	void													MoveSize_Btn();

	void													Create_Combobox();
	void													Create_ListCtrl();
	void													Create_Btn();
	void													Create_DateTimeCtrl();


	void													Get_TitleData_RPF();
	void													Get_GraphData_RPF();
	void													Get_ChartData_RPF();
	double													Get_Prev_MeaData(int nPrevID, int* nPrevID_next, int* nPrevCount_next);
	void													UpdateData_RPF();

	void													UpdateData_Gen();
	void													UpdateData_Link();

	void													Get_TitleData_DLE();
	void													Get_ChartData_DLE();
	BOOL													Check_ChartData_DLE(int nCBSW_idx);
	void													UpdateData_DLE();
	void													SetSumData_DLE();

	void													Graph_Data_Add(int nCount, int nPrevID, int nCurrID, BOOL bAdd = TRUE);
	void													Graph_Data_Clear();
	void													Group_Data_Clear();
	CGraphDataArray											m_Array_Graph;





	CRect													m_rect_Graph_Check[2];
	BOOL													m_bGraph_Check[2];
	double													m_dMax_kW, m_dMax_V, m_dMin_V;
	int														m_nNode_MaxCount;
	double													m_dVVM_lmhi, m_dVVM_lmlo;

	void													Draw_TopLeft_Setting(CDC* pDC, Graphics &graphics);

	void													Draw_TopLeft_Title(CDC* pDC, Graphics &graphics);
	void													Draw_TopLeft_Infor(CDC* pDC, Graphics &graphics);
	void													Draw_TopLeft_Graph(CDC* pDC, Graphics &graphics);
	void													Draw_TopLeft_Graph_Data(CDC* pDC, Graphics &graphics, Gdiplus::RectF r);

	double													m_dMax_Load, m_dMax_Gen;
	double													m_dSum_Load, m_dSum_Gen;
	
	Gdiplus::PointF											RotatePoint(Gdiplus::PointF ptCurrent, Gdiplus::PointF ptBase, double dAngle);
	void													Draw_TopRight_Title(CDC* pDC, Graphics &graphics);
	void													Draw_TopRight_Infor(CDC* pDC, Graphics &graphics);
	void													Draw_TopRight_circle(CDC* pDC, Graphics &graphics);
	void													Draw_TopRight_Graph(CDC* pDC, Graphics &graphics);

	/*void																					Draw_Time(CDC* pDC, Graphics &graphics);
	void																					Draw_DLE_Infor(CDC* pDC, Graphics &graphics);
	void																					Draw_DLE_Graph(CDC* pDC, Graphics &graphics);
	void																					Draw_DLE_Graph_circle(CDC* pDC, Graphics &graphics);
	Gdiplus::PointF																			RotatePoint(Gdiplus::PointF ptCurrent, Gdiplus::PointF ptBase, double dAngle);

	void																					GetRoundRectPath(Gdiplus::GraphicsPath* gp, int x, int y, int width, int height, int radius);
	void																					Draw_Chart(CDC* pDC, Graphics &graphics);
	void																					Draw_Chart_DLE(CDC* pDC, Graphics &graphics);*/



	int														FindGroupCB(int nPreGBRIdx, int nGNDIdx);
	int														FindGroupCBRcv(int nGBRIdx, int nFGNDIdx, int nEq_Count, int nGraphND_Prev);
	int														GetGroupCbswToNode(int nGNDIdx);
	int														GetGroupNDStatus(int nGNDIdx);//NODE_ID를 가지고 상태값을 확인한다(개폐기가 아니라면 그냥 CLOSE로 함)
	int														GetSwStatus(int nCbswIdx);//cbsw_sta_id를 가지고 개폐기 상태값을 확인
	int														GetTieStatus(int nTiswIdx);//tisw_sta_id를 가지고 개폐기 상태값을 확인
	int														CheckGroupConnectSw(int nGNDIdx);//다회로개폐기인지 체크(연결스위치가 2개이상이면 다회로)
	int														GetGroupToNDIdx(int nGNDIdx);//설비기준 전원측노드 -> 부하측노드를 가져온다.

	BYTE*													m_pBRTrace2;					//BR탐색 (중복) 2차탐색(BF)체크용 메모리

	void													Excute(int nDL_idx,int nRunMode = 0);

public:
	virtual void											recv_Appl(int nAppl);
	virtual void											recv_Init();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnLF_rstCombo1SelectChange();
	afx_msg void OnLF_rstCombo2SelectChange();
	afx_msg void OnLF_rstCombo3SelectChange();

	afx_msg void OnListCtrlDBClick_1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnListCtrlDBClick_2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnListCtrlDBClick_3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnListCtrlDBClick_4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnControlbutton_click_Run();
	afx_msg void OnControlbutton_click_Report();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
};

