#pragma once
#include "afxwin.h"
#include <atldbcli.h>
#include <atldbsch.h>
#include "../DND_Manager/CDND_Manager.h"

// CDNDObj_Symbol_Tap 대화 상자

class CDNDObj_Symbol_Tap : public CDialog
{
	DECLARE_DYNAMIC(CDNDObj_Symbol_Tap)

public:
	CDNDObj_Symbol_Tap(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDNDObj_Symbol_Tap();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DNDOBJECT_TPA_SYMBOL_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
protected:
	CDND_Switch*	m_pDND_Switch;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDndObjectDlgBtn1();
	afx_msg void OnUpdateUI_Btn1(CCmdUI *pCmdUI);

	void			SetSelect_DNDObject(CDND_Object* pDNDObj);

	BOOL PreTranslateMessage(MSG* pMsg);
	
};
