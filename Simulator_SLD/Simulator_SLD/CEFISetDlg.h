#pragma once
#include "../Ctrl_Object/MessageDlg.h"
#include "../Ctrl_Object/PNOCtrl_SkinFrame_POP_Dialog.h"

// CEFISetDlg 대화 상자

class CEFISetDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(CEFISetDlg)

public:
	CEFISetDlg(int nPrdeIdx, int nProtectKind, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CEFISetDlg();

	int														m_nPRDEIdx;//보호기기정보 인덱스
	int														m_nProtectKind;//1:EFI, 2:PCA (단지 다이얼로그 타이틀을 구분하기 위함)

	void													UpdateCombo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EFI_SET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrPDelayCom;
	CComboBox m_ctrGDelayCom;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
