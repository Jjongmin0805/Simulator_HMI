
#pragma once
#include "StyleDef.h"
/////////////////////////////////////////////////////////////////////////////
// CViewTree 창입니다.

class CViewTree : public CTreeCtrl
{
// 생성입니다.
public:
	CViewTree();

// 재정의입니다.
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// 구현입니다.
public:
	virtual ~CViewTree();

	CFont				m_fontNor;
	CFont				m_fontBold;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
