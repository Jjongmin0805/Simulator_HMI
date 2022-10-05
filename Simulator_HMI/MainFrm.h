
// MainFrm.h : CMainFrame 클래스의 인터페이스
//
#include "PNOCtrl_SkinFrame_SDI.h"
#include "ToolbarDlg.h"
#include "Simulator_HMIView.h"


#pragma once

class CMainFrame : public CPNOCtrl_SkinFrame_SDI
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:
	CDialogBar														m_wndToolBar;
	CToolbarDlg														m_ToolbarDlg;
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



protected:  // 컨트롤 모음이 포함된 멤버입니다.

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnEnterSizeMove();
	afx_msg void OnExitSizeMove();
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseLeave();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);

	afx_msg LRESULT OnToolbarMsg(WPARAM wParam, LPARAM lParam);

	afx_msg void OnTimer( UINT_PTR nIDEvent );

	//////////////////////////////////// ActiveView 가 바뀌네???
	CSimulator_HMIView*						m_pSimView;
	void									SetSimView();

	void									RunMenuMsg(int nMenuID);


	afx_msg LRESULT OnSendLogMsgParam(WPARAM wParam, LPARAM lParam);
	//////////////

	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnRunapplicationstudyApplicationtest();


	void	Excute_Import_OCB();

};


