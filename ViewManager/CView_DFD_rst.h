#pragma once
#include "CView_Base.h"
#include "./ListCtrl/SkinListCtrl.h"
#include "./Button/Skinbutton.h"

class CView_DFD_rst :
	public CView_Base
{
public:
	CView_DFD_rst();
	~CView_DFD_rst();


	virtual void			SetVIewID() { m_nViewID = VIEW_ID_DFD_RESULT; };
	virtual	void			InitData();

protected:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnControlbutton_DFD();
	afx_msg void OnControlbutton_DSR();
	afx_msg void OnControlbutton_run_DFD();
	afx_msg void OnControlbutton_run_DSR();
	afx_msg void OnListCtrlClick(NMHDR *pNMHDR, LRESULT *pResult);

protected:

	CSkinButton							m_btn_control[4];
	CRect								m_btn_control_rect[4];

	CSkinListCtrl						m_1st_InforList1[2], m_1st_InforList2[3], m_1st_InforList3[3];
	CRect								m_1st_ListCtrlRect1[2], m_1st_ListCtrlRect2[3], m_1st_ListCtrlRect3[3];
	CRect								m_1st_TitleRect1[2], m_1st_TitleRect2[3], m_1st_TitleRect3[3];
	CString								m_1st_ListCtrlTitle1[2], m_1st_ListCtrlTitle2[3], m_1st_ListCtrlTitle3[3];

	CFont								m_headerfont;
	CFont								m_listfont;

	void								CreateButtonCtrl();
	void								CreateListCtrl();
	void								List_MoveSize();

	void								SetListStyle(CSkinListCtrl& list);

public:
	void								SetData_Alarm();
	void								SetData_Alarm_fiinfo(int nfltinfo_hi_fiinfo);
	void								SetData_DFD();
	void								SetData_DFD_OA();
	void								SetData_DSR();
	void								SetData_DSR_Sub_1(int nidx, int nRank_main);
	void								SetData_DSR_Sub_2(int nIdx);

	void								ClearData();
	void								SendWinMsg(int nType, CString strData);
};

