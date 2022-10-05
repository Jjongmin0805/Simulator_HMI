#pragma once
#include <afxwin.h>

#define					VIEW_STATE_HIDE						0x00
#define					VIEW_STATE_SHOW						0x01

///////////////////////// HISTORY
#define					VIEW_ID_HISTORY_LOG					0x0010
///////////////////////// MMDATA EDITOR
#define					VIEW_ID_EDITOR_MMDATA				0x0020
///////////////////////// LOADFLOW
#define					VIEW_ID_LOADFLOW_SET				0x0100
#define					VIEW_ID_LOADFLOW_RESULT				0x0101
#define					VIEW_ID_LF_HISTORY_RESULT			0x0102
///////////////////////// DFD
#define					VIEW_ID_DFD_SET						0x0200
#define					VIEW_ID_DFD_RESULT					0x0201
///////////////////////// PCE
#define					VIEW_ID_PCE_SET						0x0300
#define					VIEW_ID_PCE_RESULT					0x0301
///////////////////////// PDVR
#define					VIEW_ID_PDVR_SET					0x0400
#define					VIEW_ID_PDVR_RESULT					0x0401
///////////////////////// SOP
#define					VIEW_ID_SOP_SET						0x0500
#define					VIEW_ID_SOP_RESULT					0x0501
///////////////////////// NCP
#define					VIEW_ID_NCP_SET						0x0600
#define					VIEW_ID_NCP_RESULT					0x0601
///////////////////////// SCA
#define					VIEW_ID_SCA_SET						0x0700
#define					VIEW_ID_SCA_RESULT					0x0701
///////////////////////// DNR
#define					VIEW_ID_DNR_SET						0x0800
#define					VIEW_ID_DNR_RESULT					0x0801


class CView_Base :
	public CView
{
	DECLARE_DYNAMIC(CView_Base)
public:
	CView_Base();
	virtual ~CView_Base();


protected:
	DECLARE_MESSAGE_MAP()

	virtual void OnInitialUpdate();

protected:
	int						m_nViewState;
	int						m_nViewID;

	BOOL					m_bTimer;
	int						m_nRecvAppl_ID;
	int						m_nCompAppl_ID;

public:
	int						GetVIewState() { return m_nViewState; };
	int						GetVIewID() { return m_nViewID; };

	void					SetVIewState(int nStete = VIEW_STATE_HIDE);

	virtual void			SetVIewID() { m_nViewID = -1; };

	virtual void			InitData() {};

	virtual void			recv_Appl(int nAppl) {};
	virtual void			recv_Wnd(CWndMsgData* pWndMsgData ) {};
	virtual void			recv_Init() {};

	virtual void			Redraw_Ctrl() {};

	BOOL				Create(const RECT& rect, CWnd* pParentWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};

