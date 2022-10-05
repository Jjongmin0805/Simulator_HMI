#pragma once
#include "../Ctrl_Object/PNOCtrl_SkinFrame_POP_Dialog.h"

// COutputFileOptDlg 대화 상자

class COutputFileOptDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(COutputFileOptDlg)

public:
	COutputFileOptDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~COutputFileOptDlg();

	CString				m_szPath;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OUTPUT_RATIOSET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nRatioOpt;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPathOpt();
	afx_msg void OnBnClickedOk();
	BOOL m_bReverseColor;
	int m_nFontRate;
};
