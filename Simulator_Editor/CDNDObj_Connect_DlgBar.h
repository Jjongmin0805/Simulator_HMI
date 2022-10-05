#pragma once
#include "../DND_Manager/CDND_Manager.h"
#include "CDNDObj_Connrct_KASIM_Tap.h"

class CDNDObj_Connect_DlgBar : public CDialogBar
{
	DECLARE_DYNAMIC(CDNDObj_Connect_DlgBar)

public:
	CDNDObj_Connect_DlgBar(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDNDObj_Connect_DlgBar();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DND_CONNECT_DLG };

	BOOL Create(CWnd* pParentWnd, UINT nStyle);
protected:
	DECLARE_MESSAGE_MAP()
	virtual void				 DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg BOOL				 OnInitDialog();
	afx_msg LRESULT				 InitDialog(WPARAM wp, LPARAM lp);
public:
	void						 SetSelect_DNDObject(CDND_Object* pDNDObj);
	afx_msg void				 OnTcnSelchangeDndConnectTap(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				 OnUpdateUI_Btn(CCmdUI *pCmdUI);
	afx_msg void				 OnBnClickedDndConnectDlgCancel();

	CDND_Connect*				 m_pDND_Connect;
	CDNDObj_Connrct_KASIM_Tap*   m_TDND_KASIM_Tap;
	CTabCtrl					 m_TConnect_Tap;

};
