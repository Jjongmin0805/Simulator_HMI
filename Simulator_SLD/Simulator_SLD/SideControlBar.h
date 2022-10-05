#pragma once
#include "CommonHeader.h"
#include "PNOCtrl_Group.h"
#include "TreeViewDlg.h"
#include "Group1CompDlg.h"
#include "Group1MeasDlg.h"
#include "Group1ApplDlg.h"
#include "Group2DlInfoDlg.h"
#include "ViewTree.h"


// CSideControlBar
class CSCBDockBar : public CDockBar
{
	friend class CSideControlBar;

	void DrawBorder();
};


class CSideControlBar : public CControlBar
{
	DECLARE_DYNAMIC(CSideControlBar)

public:
	CSideControlBar();
	virtual ~CSideControlBar();
	virtual BOOL				Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, CSize sizeDefault, UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE);
	virtual void				OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize				CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize				CalcDynamicLayout(int nLength, DWORD dwMode);
	virtual BOOL				DestroyWindow();

	const BOOL					IsFloating() const;
	const BOOL					IsHorzDocked() const;
	const BOOL					IsVertDocked() const;
	const BOOL					IsSideTracking() const;
	void						Show();
	void						Hide();
	CString						GetModulePath();
	void						AdjustLayout();
	void						CreateGroup();//그룹레이어 생성
	void						CreateGroup_Tab1(CRect _drawrect);//1번그룹 탭생성
	void						CreateGroup_Tab2(CRect _drawrect);//2번그룹 탭생성
	void						CreateGroup_Tab3(CRect _drawrect);//3번그룹 탭생성
	void						ResizeGroup();//그룹창 사이즈조정
	void						ResizeGroup_Tab1();//1번그룹내 Wnd 사이즈조정
	void						ResizeGroup_Tab2();//2번그룹내 Wnd 사이즈조정
	void						ResizeGroup_Tab3();//3번그룹내 Wnd 사이즈조정

	void						InitTreeView();//선로목록을 업데이트
	void						SetGroup1CompData(CNodeView* pNodeView, int nDLIdx);
	void						SetGroup1MeasData(int nCompType, int nCompIdx);
	void						SetGroup1ApplData(int nCompType, int nCompIdx);
	void						ShowDLInfo(int nDLIdx);

protected:
	CPNOCtrl_Group*				m_pTabGroup1;//Tab그룹1 -> 선로목록트리
	CPNOCtrl_Group*				m_pTabGroup2;//Tab그룹2 -> 설비정보 / 계측정보 / Appl.정보
	CPNOCtrl_Group*				m_pTabGroup3;//Tab그룹3 -> DL요약정보 / 전압프로파일 / 부하패턴

	CTreeViewDlg*				m_pTreeViewDlg;//변전소/DL목록
	CGroup1CompDlg*				m_pGroup1CompDlg;//설비정보화면
	CGroup1MeasDlg*				m_pGroup1MeasDlg;//계측정보화면
	CGroup1ApplDlg*				m_pGroup1ApplDlg;//Appl정보화면
	CGroup2DlInfoDlg*			m_pGroup2DlInfoDlg;//DL요약화면

protected:
	UINT						GetEdgeCode(int nEdge);
	BOOL						GetEdgeRect(CRect rcWnd, UINT nHitTest, CRect& rcEdge);
	BOOL						NegoSpace(int nLengthAvail, BOOL bHorz);

	virtual void				StartTracking(UINT nHitTest);
	virtual void				StopTracking();
	virtual void				OnTrackUpdateSize(CPoint& point);
	virtual void				OnTrackInvertTracker();
	virtual void				RecalcLayoutControlBar();

protected:
	CSize						m_szHorz;
	CSize						m_szVert;
	CSize						m_szFloat;

	DWORD						m_dwSCBSstyle;
	UINT						m_unDocEdge;
	CSize						m_szMin, m_szMinTemp, m_szMaxTemp;
	CSize						m_szHorzVertOld;
	CPoint						m_ptEdgeOld;
	BOOL						m_bTracking;
	BOOL						m_bKeepSize;
	BOOL						m_bParentSizing;
	BOOL						m_bDragContent;
	UINT						m_nDockBarID;
	int							m_nEdgeXsize;
	CSize						m_szRestoreHorz, m_szRestoreVert;
	BOOL						m_bControlShow;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseLeave();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg LRESULT	OnSideControlBarMsg(WPARAM wparam, LPARAM lparam);
};


