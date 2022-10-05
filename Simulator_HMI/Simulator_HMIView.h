
// Simulator_HMIView.h : CSimulator_HMIView 클래스의 인터페이스
//

#pragma once

#include "../ViewManager/CMainView.h"
#include "Simulator_HMIDoc.h"

class CSimulator_HMIView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSimulator_HMIView();
	DECLARE_DYNCREATE(CSimulator_HMIView)

// 특성입니다.
public:
	CSimulator_HMIDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CSimulator_HMIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);




	//////////////////////////////////////////

public:
	void									SetActive_View(int nViewID);
	void									InitData();
	void									AddMessage(wchar_t* szMsg, COLORREF crText);

	void									recv_Appl(int nAppl);
	void									recv_Init();
	void									recv_Wnd(CWndMsgData* pWndMsgData);

protected:
	CMainView*								m_pMainView;
	void									CreateMainView();
	

public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // Simulator_HMIView.cpp의 디버그 버전
inline CSimulator_HMIDoc* CSimulator_HMIView::GetDocument() const
   { return reinterpret_cast<CSimulator_HMIDoc*>(m_pDocument); }
#endif

