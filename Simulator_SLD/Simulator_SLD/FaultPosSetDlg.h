#pragma once
#include "pch.h"
#include "../Ctrl_Object/PNOCtrl_SkinFrame_POP_Dialog.h"

// CFaultPosSetDlg 대화 상자

class CFaultPosSetDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(CFaultPosSetDlg)

public:
	CFaultPosSetDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFaultPosSetDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FAULT_POS_SET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nOhms;
	int m_nFaultType;
	BOOL m_bInFault;
};
