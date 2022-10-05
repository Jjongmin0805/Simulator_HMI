#pragma once
#include "StyleDef.h"
#include "NodeView.h"

// CGroup1CompDlg 대화 상자
#define	SW_CLOSE				1
#define	SW_OPEN					0

#define	SW_ONLINE				0
#define	SW_OFFLINE				1

class CGroup1CompDlg : public CDialog
{
	DECLARE_DYNAMIC(CGroup1CompDlg)

public:
	CGroup1CompDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGroup1CompDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GROUP1_COMP_DLG };
#endif

	void																	SetData(CNodeView* pNodeView, int nDLIdx);
	void																	UpData();

protected:
	CString																	m_szData[5];//0:변전소명, 1:소속DL명, 2:전주번호, 3:연계정보, 4:설비종류(->3:연계정보는 사용안함-20210713)
	int																		m_nData[2];//0:현재상태, 1:계측치유무
	
	int																		m_nSelNodeIdx;//선택설비의 NDIdx
	int																		m_nALTSCBSW;//선택설비가 ALTS일때만 사용함(반대쪽 설비IDX)

	int																		m_nSelNodeType;//1:CBSW(보호기기), 2:DG(분산전원);
	CFont																	m_fontDef;
	CFont																	m_fontBold;
	int																		m_nCbswIdx;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedGroup11BtnProtectSet();
	afx_msg void OnBnClickedGroup11BtnModify();
};
