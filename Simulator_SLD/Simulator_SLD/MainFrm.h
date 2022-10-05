
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once
#include "PNOCtrl_SkinFrame_SDI.h"
#include "ToolbarDlg.h"
#include "SideControlBar.h"

#define BASE_VOLTAGE																	22.9

#define VIEWMODE_MENU_START_IDX															2
#define VIEWMODE_MENU_CNT																2
#define DISPLAYOPT_MENU_START_IDX														9
#define DISPLAYOPT_MENU_CNT																2

#define DISPLAY_SHOW_PHASE_A															0
#define DISPLAY_SHOW_PHASE_B															1
#define DISPLAY_SHOW_PHASE_C															2
#define DISPLAY_SHOW_AMP																1
#define DISPLAY_SHOW_VOLT																2
#define DISPLAY_SHOW_MW																	4
#define DISPLAY_SHOW_MVAR																8
#define DISPLAY_SHOW_VOLTUINT_PU														0
#define DISPLAY_SHOW_VOLTUNIT_KV														1

class CMainFrame : public CPNOCtrl_SkinFrame_SDI
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:
	CDialogBar														m_wndToolBar;
	CToolbarDlg														m_ToolbarDlg;

	CSideControlBar													m_wndSideCtrl;//좌측 controlbar class

	int																m_nSLDMode;//보기모드 (0:일반, 1:그룹)
	int																m_nPhaseOpt;//대표상
	BOOL															m_bNameOpt;//전주명보이기
	int																m_nMeasValueOpt;//계측값옵션
	int																m_nMeasVoltUnit;//계측전압단위
	int																m_nCalcValueOpt;//계산값옵션
	int																m_nCalcVoltUnit;//계산전압단위

	void															InitTreeView();
	void															TreeClickEvent(int nDLIdx);//선로목록 트리 클릭시 event_receive
	void															TreeDBClickEvent(int nDLIdx);//선로목록 트리 더블클릭시 event_receive
	void															TreeRBClickEvent(int nDLIdx);//선로목록 트리 우클릭시 event_receive

	int																GetSLDMode() { return m_nSLDMode; };
	void															SetPhaseOpt(int nOpt) { m_nPhaseOpt = nOpt; };
	void															SetNameOpt(BOOL bShow) { m_bNameOpt = bShow; };
	void															SetMeasValueOpt(int nOpt) { m_nMeasValueOpt = nOpt; };
	void															SetMeasVoltUnitOpt(int nOpt) { m_nMeasVoltUnit = nOpt; };
	void															SetCalcValueOpt(int nOpt) { m_nCalcValueOpt = nOpt; };
	void															SetCalcVoltUnitOpt(int nOpt) { m_nCalcVoltUnit = nOpt; };
	int																GetPhaseOpt() { return m_nPhaseOpt; };
	BOOL															GetNameOpt() { return m_bNameOpt; };
	int																GetMeasValueOpt() { return m_nMeasValueOpt; };
	int																GetMeasVoltUnitOpt() { return m_nMeasVoltUnit; };
	int																GetCalcValueOpt() { return m_nCalcValueOpt; };
	int																GetCalcVoltUnitOpt() { return m_nCalcVoltUnit; };


	void															SetGroup1CompData(CNodeView* pNodeView, int nDLIdx);
	void															SetGroup1MeasData(int nCompType, int nCompIdx);
	void															SetGroup1ApplData(int nCompType, int nCompIdx);
	void															ShowDLInfo();
	void															SetSelectDLIdx(int nDLIdx) { m_nDLIdx = nDLIdx; };

	int																m_nViewMode;
	int																GetViewMode()	{ return m_nViewMode; };

	BOOL															m_bAreaSetMode;
	BOOL															GetAreaSetMode() { return m_bAreaSetMode; };

	BOOL															m_bShowSecInfo;
	BOOL															GetShowSecMode() { return m_bShowSecInfo; };

	BOOL															m_bShowVirtualDG;
	BOOL															GetShowVirtualDG() { return m_bShowVirtualDG; };

	int																m_nDLIdx;
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

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
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

	afx_msg LRESULT OnToolMenuFunc(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnModifyMeasFunc(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);

	afx_msg LRESULT OnToolbarMsg(WPARAM wParam, LPARAM lParam);
};


