
// Simulator_HMIView.h : CSimulator_HMIView Ŭ������ �������̽�
//

#pragma once

#include "../ViewManager/CMainView.h"
#include "Simulator_HMIDoc.h"

class CSimulator_HMIView : public CView
{
protected: // serialization������ ��������ϴ�.
	CSimulator_HMIView();
	DECLARE_DYNCREATE(CSimulator_HMIView)

// Ư���Դϴ�.
public:
	CSimulator_HMIDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CSimulator_HMIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // Simulator_HMIView.cpp�� ����� ����
inline CSimulator_HMIDoc* CSimulator_HMIView::GetDocument() const
   { return reinterpret_cast<CSimulator_HMIDoc*>(m_pDocument); }
#endif

