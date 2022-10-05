#pragma once


// CFrame_SkinCtrl_SDIEx �������Դϴ�.

class AFX_EXT_CLASS CFrame_SkinCtrl_SDIEx : public CFrameWndEx
{
	DECLARE_DYNCREATE(CFrame_SkinCtrl_SDIEx)
protected:
	CFrame_SkinCtrl_SDIEx();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CFrame_SkinCtrl_SDIEx();

public:
	enum{									CLICKED_BOX_NONE = 0,
											CLICKED_BOX_MINIMIZE,
											CLICKED_BOX_MAXIMIZE,
											CLICKED_BOX_RESTORE,
											CLICKED_BOX_EXIT
	};

protected:
	CSize									m_pOriWVMFSize, m_pWVMFSize;		//Windows Ver 7 Main Frame Size;
	BOOL									m_bCreated;
	DWORD									m_dwOrgStyle;		// ���� ������ ��Ÿ��
	CRgn									m_rgnWnd;			// ������ ����
	CBrush									m_CtlColorBrush;
	int										m_nClickedBox;		// ���� Ŭ���� �ڽ� ����
	BOOL									m_bTracking;		// ���� ���콺 �ڽ����� �ִ��� �ƴ��� ���� �÷���
	BOOL									m_bDraging;			// �����찡 ���콺 �巡�׷� �̵� ������ �ƴ����� ���� �÷���
	BOOL									m_bSizeCursor;		// Ŀ������� ���������� ������� �ƴ����� ���� �÷���
	BOOL									m_bActive;
	COLORREF								m_cfText;			// �ؽ�Ʈ ��
	COLORREF								m_cfMask;			// ����ũ ��

	// ��Ʈ�� ������
	SIZE									m_sizeWindowCaption[ IDX_SYSTEMICON_MAX ];
	// ��Ʈ�� �ڵ�
	HBITMAP									m_hBmpWindowCaption[ IDX_SYSTEMICON_MAX ];

	HBITMAP									m_hCMin, m_hCMax, m_hCExit;
	CRect									m_rectMin, m_rectMax, m_rectExit;
	UINT									m_unNcMouseClick;

	// ������ �ڵ�
	HICON									m_hIcon;
	DWORD									m_dwMinWidth;
	DWORD									m_dwMinHeight;

protected:
	void																					SetskinIMGsize();
	void																					DrawFrame();
	void																					GetMonitorInforRect( CRect *pMonitorRect, UINT flags );
	void																					SetCheckLBtnUp( CPoint point );

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int																				OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL																			PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void																			OnDestroy();
	afx_msg void																			OnSize(UINT nType, int cx, int cy);
	afx_msg void																			OnPaint();
	afx_msg void																			OnNcPaint();
	afx_msg BOOL																			OnNcActivate(BOOL bActive);
	afx_msg void																			OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void																			OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void																			OnEnterSizeMove();
	afx_msg void																			OnExitSizeMove();
	afx_msg void																			OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void																			OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void																			OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void																			OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void																			OnNcMouseLeave();
	afx_msg void																			OnLButtonUp(UINT nFlags, CPoint point);
};


