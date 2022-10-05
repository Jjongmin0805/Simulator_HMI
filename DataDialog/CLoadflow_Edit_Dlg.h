#pragma once

#include "Resource.h"

// CLoadflow_Edit_Dlg 대화 상자
class CMain_LoadFlow_Editor;
class AFX_EXT_CLASS CLoadflow_Edit_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoadflow_Edit_Dlg)

public:
	CLoadflow_Edit_Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLoadflow_Edit_Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOADFLOW_EDIT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	CMain_LoadFlow_Editor*					m_pLFEditor;
};


