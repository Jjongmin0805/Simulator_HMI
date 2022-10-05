#pragma once
#include "StyleDef.h"

#define OPTION_STATUS_DOWN							0
#define OPTION_STATUS_ON							1
#define OPTION_STATUS_OVER							2

#include <vector>
using namespace std;

class CGroupTab_Infor
{
public:
	CGroupTab_Infor() : m_bSelected( FALSE ), m_bMoveSelect( FALSE ), m_szTabName( _T("") ), m_TapSize( 0, 0, 0, 0 ){ m_pView = NULL; };
	virtual ~CGroupTab_Infor(){};

	BOOL																					m_bSelected;
	BOOL																					m_bMoveSelect;
	wstring																					m_szTabName;
	CRect																					m_TapSize;
	CWnd*																					m_pView;
};


// CPNOCtrl_Group
class CPNOCtrl_Group : public CWnd
{
	DECLARE_DYNAMIC(CPNOCtrl_Group)

public:
	CWnd*																					m_pParentWnd;

	CPNOCtrl_Group();
	virtual ~CPNOCtrl_Group();

	BOOL																					Create( const RECT& rect, CWnd* pParentWnd );
	void																					SetSkinInit1();
	void																					SetSkinInit2();
	void																					AddTabInfor( wstring szName, CWnd*	pView );
	void																					SetTabView( int nTabIndex, CWnd* pView );
	CRect																					GetInDrawScreenRect();
	void																					SetTabFocus( int nTabIndex = 1 );
	int																						GetActiveSelect();

	void																					SetSkinOption();
	BOOL																					SetOptionMode( int nOpt );

protected:
	void																					DrawSkin( CDC* pDC, int nDrawIdx = 0 );
	CString																					GetModulePath();
	void																					ResetSelect();
	void																					ResetMoveSelect();
	void																					ResetView();

	HBITMAP																					m_hBtmCaptionSkin[3];
	BITMAP																					m_BtmCaptionSkinInfor[3];

	HBITMAP																					m_hBtmSelectedTab, m_hBtmUnSelectedTab;
	BITMAP																					m_hBtmSelectedTabInfor, m_hBtmUnSelectedTabInfor;

	HBITMAP																					m_hBtmOptSkin[6];
	BITMAP																					m_hBtmOptSkinInfor;
	HBITMAP																					m_hBtmOpt[2];
	CRect																					m_rectOpt[2];
	int																						m_nSetOption;
	int																						m_nStatus;

	int																						m_nTabCnt;
	vector<CGroupTab_Infor*>																m_vecTabInfor;

	BOOL																					m_bTrackMouse;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void																			OnPaint();
	afx_msg BOOL																			OnEraseBkgnd(CDC* pDC);
	afx_msg void																			OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void																			OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL																			OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
};


