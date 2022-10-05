#pragma once
#include "ViewTree.h"

// CTreeViewDlg 대화 상자

class CTreeViewDlg : public CDialog
{
	DECLARE_DYNAMIC(CTreeViewDlg)

public:
	CTreeViewDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTreeViewDlg();

	CString																		GetModulePath();
	void																		SetOptionValue(int nOpt) { m_nTreeViewMode = nOpt; };
	BOOL																		CreateTreeView();
	void																		ShowTree(int nMode);

	HTREEITEM																	InsertTreeItem(int nIdx, CString szName, int nImage, int nSelImage, HTREEITEM hParent, int nMode, int nData = -1);
	void																		RemoveTreeItem();

	void																		TreeClickEvent(int nDLIdx);
	void																		TreeDBClickEvent(int nDLIdx);
	void																		TreeRBClickEvent(int nDLIdx);

protected:
	int																			m_nTreeViewMode;//트리표시모드(0:변전소별, 1:DL별)
	CViewTree																	m_wndViewTree[2];//0:변전소별 트리, 1:DL별 트리
	CImageList																	m_TreeImgList;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TREEVIEW_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
