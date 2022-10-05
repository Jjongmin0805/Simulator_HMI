#pragma once
#include "CView_Base.h"
#include "./ListCtrl/SkinListCtrl.h"

class CView_History :
	public CView_Base
{
public:
	CView_History();
	~CView_History();

protected:
public:
	virtual void OnInitialUpdate();

	virtual void			SetVIewID() { m_nViewID = VIEW_ID_LOADFLOW_RESULT; };
	virtual	void			InitData();

	void					AddMessage(wchar_t* szMsg, COLORREF crText);

protected:
	CFont													m_headerfont;
	CFont													m_listfont;
	CRect													m_rectListTitle;
	CRect													m_rectList;
	CSkinListCtrl											m_ctrList;

	void													ListCtrl_MoveSize();
	void													Create_ListCtrl();

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

