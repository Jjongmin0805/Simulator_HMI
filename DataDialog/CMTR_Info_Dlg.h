#pragma once

#include "Resource.h"
#include "MyCtrl.h"

// CMTR_Info_Dlg 대화 상자

class AFX_EXT_CLASS CMTR_Info_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMTR_Info_Dlg)

public:
	CMTR_Info_Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMTR_Info_Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MTR_INFO_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMtrInfoDlgBtn1();
	afx_msg void OnBnClickedMtrInfoDlgBtn2();
	afx_msg void OnBnClickedMtrInfoDlgBtn3();

	CCustomList m_ctrList;

	void SetData_List();
	int		Get_GEN_Index2TR(int nTR_Idx);
};
