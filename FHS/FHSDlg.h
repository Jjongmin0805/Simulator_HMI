
// FHSDlg.h: 헤더 파일
//

#pragma once

#include "./Combobox/SkinCombobox.h"
#include "./ListCtrl/SkinListCtrl.h"
#include "./Button/Skinbutton.h"

// CFHSDlg 대화 상자
class CFHSDlg : public CDialogEx
{
// 생성입니다.
public:
	CFHSDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FHS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CFont													m_headerfont;
	CFont													m_listfont;
	CComboBox m_ctrCombo[4];
	CSkinListCtrl m_ctrList;
	CDateTimeCtrl m_ctrDate[2];
	CButton m_ctrRadio[2];

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedFhsDlgBtn1();
	afx_msg void OnBnClickedFhsDlgRadio2();
	afx_msg void OnBnClickedFhsDlgRadio1();
	virtual BOOL DestroyWindow();
	afx_msg void OnCbnSelchangeFhsDlgCombo1();
	afx_msg void OnCbnSelchangeFhsDlgCombo2();


	void Set_Center();
	void Set_Office();
	void Set_Subs();
	void Set_DL();

	void Create_List();

	int		GetIndex_CBSW(LONGLONG lCeqID);

	int			m_nOnline;
	LONGLONG	m_lMaxLogID;
	void			GetMaxLogID();
	void UpdateList_Online();
	void UpdateList_History();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHdnItemclickFhsDlgList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickFhsDlgList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedFhsDlgBtn2();
	afx_msg void OnCbnSelchangeFhsDlgCombo4();
};
