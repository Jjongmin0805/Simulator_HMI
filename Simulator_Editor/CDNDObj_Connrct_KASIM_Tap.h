#pragma once
#include "afxwin.h"
#include <atldbcli.h>
#include <atldbsch.h>
#include "../DND_Manager/CDND_Manager.h"
// CDNDObj_Connrct_KASIM_Tap 대화 상자

#define WM_CONNECT_MSG												WM_USER + 2000

class CDNDObj_Connrct_KASIM_Tap : public CDialog
{
	DECLARE_DYNAMIC(CDNDObj_Connrct_KASIM_Tap)

public:
	CDNDObj_Connrct_KASIM_Tap(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDNDObj_Connrct_KASIM_Tap();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DND_CONNECT_TAP_KASIM_DLG };
#endif

	CWnd*															m_pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	CDND_Connect*													m_pDND_Connect;

public:
	CString					MyPath();

	CComboBox				m_ctrCombo1[1];
	CComboBox				m_ctrCombo2[1];
	CComboBox				m_ctrCombo3[1];
	CString					m_stCEQ_ID;			//현재 선택된 ceq?
	int						m_nLNSEC_CSVID;
	int						m_nBR_CSVID;
	int						m_nLD_CSVID;
	int						m_nIJ_CSVID;
	int						m_nNewData;
	int						m_nFNDID;
	int						m_nTNDID;
	int						m_nOlg_FNDID;
	int						m_nOlg_TNDID;
	//KASIM 데이터 때문에 넣은 함수인데 ??
	int						m_nBR_II_EQU;
	int						m_nDL;
	int						m_nMTR;
	int						m_nSS;


	int						m_nLNINETYPECODE[300][10];

	virtual		BOOL		OnInitDialog();
	void					SetSelect_DNDObject(CDND_Object* pDNDObj);
	void					LoadLnsec_Type();
	void					LoadKASIM();
	void					GET_Connrct_BR_DL(int nBRID, int nIJID, int nNDID);
	void					GET_Connrct_InsertDB(int nBRID, int nNDID);

	afx_msg		void		OnBnClickedDndConnectTapKasimDlgBtn1();
	afx_msg		void		OnUpdateUI_Btn1(CCmdUI *pCmdUI);
	afx_msg		void		OnCbnSelchangeDndConnectTapKasimDlg();
	afx_msg		void		OnCbnSelchangeDndConnectTapKasimDlg1();
	afx_msg		void		OnEnChangeDndConnectTapKasimDlgDeit3();

	BOOL PreTranslateMessage(MSG* pMsg);
};

