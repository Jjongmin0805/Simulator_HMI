#pragma once
#include "pch.h"
#include "PNOCtrl_CommonHeader.h"

// CPNOCtrl_SkinFrame_CTRL_Dialog
class AFX_EXT_CLASS CPNOCtrl_SkinFrame_CTRL_Dialog : public CDialog
{
	DECLARE_DYNAMIC(CPNOCtrl_SkinFrame_CTRL_Dialog)

public:
	CPNOCtrl_SkinFrame_CTRL_Dialog();
	virtual ~CPNOCtrl_SkinFrame_CTRL_Dialog();

	enum{		CLICKED_BOX_NONE = 0,
				CLICKED_BOX_MINIMIZE,
				CLICKED_BOX_MAXIMIZE,
				CLICKED_BOX_RESTORE,
				CLICKED_BOX_EXIT,
				CLICKED_BOX_WIDE
	};

protected:
	BOOL				m_bMoveWindow;
	UINT				m_unCaptionStyle;
	BOOL				m_bCreated;
	DWORD				m_dwOrgStyle;		// ���� ������ ��Ÿ��
	CRgn				m_rgnWnd;			// ������ ����
	CBrush				m_CtlColorBrush;
	int					m_nClickedBox;		// ���� Ŭ���� �ڽ� ����
	BOOL				m_bTracking;		// ���� ���콺 �ڽ����� �ִ��� �ƴ��� ���� �÷���
	BOOL				m_bDraging;			// �����찡 ���콺 �巡�׷� �̵� ������ �ƴ����� ���� �÷���
	BOOL				m_bSizeCursor;		// Ŀ������� ���������� ������� �ƴ����� ���� �÷���
	BOOL				m_bActive;
	COLORREF			m_cfText;			// �ؽ�Ʈ ��
	COLORREF			m_cfMask;			// ����ũ ��

	// ��Ʈ�� ������
	SIZE				m_sizeWindowCaption[ PNOCtrl_IDX_SYSTEMICON_MAX ];
	// ��Ʈ�� �ڵ�
	HBITMAP				m_hBmpWindowCaption[ PNOCtrl_IDX_SYSTEMICON_MAX ];

	HBITMAP				m_hCMin, m_hCMax, m_hCExit, m_hWidth, m_hHeight;
	CRect				m_rectMin, m_rectMax, m_rectExit, m_rectWide;
	UINT				m_unNcMouseClick;

	// ������ �ڵ�
	HICON				m_hIcon;
	DWORD				m_dwMinWidth;
	DWORD				m_dwMinHeight;
	BOOL				m_bControlShow;
	BOOL				m_bControlDlgStatus;
public:
	void				SetCaptionStyle( UINT unStyle ){ m_unCaptionStyle = unStyle; };
	void				SetMiniMizeSysIcons();
	void				ChildFrmReSize();
	void				SetMoveWindow(){ m_bMoveWindow = TRUE; };
	void				SetNotMoveWindow(){ m_bMoveWindow = FALSE; };
	void				SetShow(){ m_bControlShow = TRUE; };
	void				SetHide(){ m_bControlShow = FALSE; };
	BOOL				GetShow(){ return m_bControlShow; };
	void				SetWidth(){ m_bControlDlgStatus = FALSE; };
	void				SetHeight(){ m_bControlDlgStatus = TRUE; };

protected:
	void				SetskinIMGsize();
	void				DrawFrame();
	void				GetMonitorInforRect( CRect *pMonitorRect, UINT flags );
	void				SetCheckLBtnUp( CPoint point );

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
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
};


