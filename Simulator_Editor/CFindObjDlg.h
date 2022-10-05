#pragma once
#include "../Ctrl_Object_Editor/MessageDlg.h"
#include "../Ctrl_Object_Editor/PNOCtrl_SkinFrame_POP_Dialog.h"

// CFindObjDlg 대화 상자
#define WM_FINDOBJ_MSG												WM_USER + 2000

class CFindObjDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(CFindObjDlg)

public:
	CFindObjDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFindObjDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINDOBJ_DLG };
#endif
	BOOL															Create();
	CString															ConvertNumber(int nNum);
	void															FindToName(CString szFindText);
	void															FindToCEQ(CString szFindText);
	CWnd*															m_pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CComboBox	m_ctrIndexCom;
	int			m_nFindOpt;
	virtual BOOL OnInitDialog();
	CListCtrl m_ctrList;
	afx_msg void OnBnClickedRadioFindopt1();
	afx_msg void OnBnClickedRadioFindopt2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMDblclkListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditName();

};

