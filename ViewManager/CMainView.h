#pragma once

#include "CView_Base.h"


// CMainView 폼 보기

class AFX_EXT_CLASS CMainView : public CFormView
{
	DECLARE_DYNCREATE(CMainView)

public:
	CMainView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMainView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_VIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnDraw(CDC* /*pDC*/);



public: 
	BOOL									Create_Main(const RECT& rect, CWnd* pParentWnd);

	void									SetActive_View(int nViewID);
	void									InitData();

	void									AddMessage(wchar_t* szMsg, COLORREF crText);

	void									recv_Appl(int nAppl);
	void									recv_Init();
	void									recv_Wnd(CWndMsgData* pWndMsgData) ;

protected:
	CMap<int, int, CView_Base*, CView_Base*>  m_ViewMap;
	   

	void									Create_View();
	void									Clear_View();

	CView_Base								*m_pHistoryView;

	CView_Base*								GetActive_ApplView();
	
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
};


