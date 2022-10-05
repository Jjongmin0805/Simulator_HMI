#pragma once

#include "Resource.h"
#include "../DataManager/CDataManager.h"
// CView_DNR_rst_SSDlg 대화 상자

class CView_DNR_rst_SSDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CView_DNR_rst_SSDlg)

public:
	CView_DNR_rst_SSDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CView_DNR_rst_SSDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DNR_RST_SS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDnrRstSsDlgBtn1();

	void			InitData();
	CListCtrl m_ctrList;

	CStringArray			m_Array_SS;
	CIntArray				m_Array_SS_idx;
};
