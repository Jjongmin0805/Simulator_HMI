#pragma once
#include "resource.h"
#include "ToolHeader.h"

#define WM_TOOLBAR_MSG						WM_USER + 1000

// CToolbarDlg 대화 상자입니다.
class CToolbarDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolbarDlg)

public:
	CToolbarDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CToolbarDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_TOOLBAR_DLG };

	void													SetParentWnd(CWnd* pFrameWnd) { m_pFrameWnd = pFrameWnd; };

	void													LoadIcons();
	void													InitIcons();
	CString													GetModulePath();
	CString													GetIconFileName(UINT nIconID);

	void													DrawToolbar(CDC* pDC);
	void													SetSysIconsRect();

	HBITMAP													m_TBSysIcons[4][3];
	BITMAP													m_TBSysIconsInfor[4][3];
	CRect													m_rectTBSysIcons[3];

	HBITMAP													m_Icons[IDX_TOOLMENU_CNT][4];
	BITMAP													m_IconsInfor[IDX_TOOLMENU_CNT][4];
	CRect													m_rectIcons[IDX_TOOLMENU_CNT];

	HBITMAP													m_ImgLogo;
	BITMAP													m_ImgLogoInfor;
	CRect													m_rectImgLogo;

	int														m_nViewMode;

	int														m_nSelectIcon;
	int														m_nMoveIcon;
	int														m_nSysSelectIcon;
	int														m_nSysMoveIcon;
	BOOL													m_bLButtonDown;

	CWnd*													m_pFrameWnd;

	void													InitMenuBarCtrl();

	CFrame_MenuBar_Ctrl*									m_wndMenuBarCtrl;

	BOOL													m_bBoundarySet;
	void													SetBoundarCheckMode(BOOL bSet) { m_bBoundarySet = bSet; };

	BOOL													m_bShowSecInfo;
	void													SetShowSecMode(BOOL bSet) { m_bShowSecInfo = bSet; };

	BOOL													m_bShowVirtualDG;
	void													SetShowVirtualDG(BOOL bSet) { m_bShowVirtualDG = bSet; };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
