#pragma once
#include "resource.h"
#include "../Ctrl_Object/PNOCtrl_SkinFrame_POP_Dialog.h"

// CVVMSetDlg 대화 상자

class CVVMSetDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(CVVMSetDlg)

public:
	CVVMSetDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVVMSetDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VVM_SET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nVoltageLevel;
};
