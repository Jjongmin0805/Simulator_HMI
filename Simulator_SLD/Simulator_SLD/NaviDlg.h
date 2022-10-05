#pragma once
#include "../DPObject/IdxMap.h"
#include "NodeView.h"
#include "BranchView.h"

#define WM_NAVIGATOR_MSG					WM_USER + 1000

#define	DEFAULT_NAVIGATOR_SIZEX				300
#define	DEFAULT_NAVIGATOR_SIZEY				170

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class CNavigatorIcons
{
public:
	CNavigatorIcons::CNavigatorIcons() : m_rect(0, 0, 0, 0)
	{
		m_hCtrlIcon = NULL;
	};
	virtual	~CNavigatorIcons()
	{
	};

	CRect																	m_rect;
	HBITMAP																	m_hCtrlIcon;
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// CNaviDlg 대화 상자

class CNaviDlg : public CDialog
{
	DECLARE_DYNAMIC(CNaviDlg)

public:
	CNaviDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNaviDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAVI_DLG };
#endif

	void																	ResetData();
	CString																	GetModulePath();
	void																	LoadIcons();
	void																	InitIcons(void);
	void																	DrawIcons(CDC* pDC);

	BOOL																	Create(CWnd* pParent = NULL);
	void																	ShowNavi(BOOL bShow);
	BOOL																	IsShowNavi() { return m_bShowNavi; };
	CSize																	GetWindowSize();




	void																	SetViewMode(int nMode) { m_nViewMode = nMode; };

	//단선도용/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void																	SetNaviSLDRatio(int nSDLSizeX, int nSLDSizeY);//단선도 기본좌표를 가지고 비율설정.
	void																	SetNaviRatio(CRect rectView);//현재 단선도 스케일을 가지고 비율설정
	void																	UpData(CNodeView* pNodeView, CBranchView* pBranchView);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//GIS용////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void																	SetGISRectNavi(CRect rect, double dZoom, CDPoint* pCen);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

protected:
	int																		m_nViewMode;

	BOOL																	m_bShowNavi;
	HBITMAP																	m_Icons[2][3];
	BITMAP																	m_IconsInfor[2][3];
	CNavigatorIcons															m_CtrlIcons;
	BOOL																	m_bLButtonDown;

	//단선도용/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double																	m_dSLDRatioX;	//단선도기본사이즈대비 내비비율 Width
	double																	m_dSLDRatioY;	//단선도기본사이즈대비 내비비율 Height
	CRect																	m_rectView;	//단선도가 표시되고 있는 View영역
	CWnd*																	m_pParentWnd;
	CNodeView*																m_pNodeView;
	CBranchView*															m_pBranchView;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//GIS용////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CRect																	m_rectWnd;
	CRect																	m_rectBtn;
	CRect																	m_rectScreen;
	double																	m_dScrZoom;
	CRect																	m_rectRgn;
	double																	m_dRatio;
	CIdxMap*																m_pMap;
	CDPoint*																m_dpCenter;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};
