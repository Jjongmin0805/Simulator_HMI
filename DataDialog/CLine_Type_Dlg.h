#pragma once

#include "Resource.h"
#include "MyCtrl.h"
// CLine_Type_Dlg 대화 상자

class AFX_EXT_CLASS CLine_Type_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLine_Type_Dlg)

public:
	CLine_Type_Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLine_Type_Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINETYPE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLinetypeDlgBtn1();
	afx_msg void OnBnClickedLinetypeDlgBtn2();
	afx_msg void OnBnClickedLinetypeDlgBtn3();

	CCustomList m_ctrList;
	int			m_nMax_ID;

	void	SetData_List();
	
};
