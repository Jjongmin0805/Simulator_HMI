#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "Resource.h"
#include "../DataManager/CDataManager.h"
#include "afxwin.h"


// CImportSomasDlg 대화 상자입니다.
typedef CArray<double, double&> CDoubleArray;

class AFX_EXT_CLASS	CImportSomasDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImportSomasDlg)

public:
	CImportSomasDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CImportSomasDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_IMPORT_SOMAS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeImportPwDlgCombo1();
	afx_msg void OnCbnSelchangeImportPwDlgCombo2();
	afx_msg void OnCbnSelchangeImportPwDlgCombo3();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CDateTimeCtrl m_ctrDataF;
	CDateTimeCtrl m_ctrDataT;

	CListCtrl m_ctrList1;
	CListCtrl m_ctrList4;
	int			m_nList4ColCount;

	CComboBox m_ctrCombo1;
	CComboBox m_ctrCombo2;
	CComboBox m_ctrCombo3;

	CProgressCtrl m_ctrProgress;
	void PumpMessages();

	CDataManager* m_pData;
	
	void		InitData();

	double m_dOptimal  ;

	//////////////////////////////////// PTS
	CDataSource m_Connect;
	CSession    m_Session;
	BOOL  CreateSession();
	BOOL	GetPTSData();

	

	//////////////////////////////////// SOMAS
	BOOL	GetSomasData(int nURLType);
	void	GetWebDate(int nURLType,CString strSS, CString strDL, CTime dtDate);
	void	Conversion(int nURLType);
	BOOL	ReadData(CString strSS, CString strDL, CTime dtDate);
	BOOL	ReadData_Voltage(CString strSS, CTime dtDate);

	void	SetBadData_Voltage();
	void	SetBadData_Load();
	void	UpdateList();
	void	GetPTS_DGName();
		
	afx_msg void OnLvnItemchangedImportPwDlgList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingImportPwDlgList1(NMHDR *pNMHDR, LRESULT *pResult);
	
	CButton m_ctrBtnChk1;
	CButton m_ctrBtnChk2;
	CButton m_ctrBtnChk3;
	CButton m_ctrBtnChk4;
	CButton m_ctrBtnChk5;
	CButton m_ctrBtnChk6;
	CButton m_ctrBtnChk7;
	CButton m_ctrBtnChk8;
	afx_msg void OnBnClickedImportSomasDlgChk1();
	afx_msg void OnBnClickedImportSomasDlgChk2();
	afx_msg void OnBnClickedImportSomasDlgBtn2();
	afx_msg void OnBnClickedImportSomasDlgBtn3();
	afx_msg void OnBnClickedImportSomasDlgBtn4();
	afx_msg void OnBnClickedImportSomasDlgBtn1();
	afx_msg void OnBnClickedImportSomasDlgChk3();
	afx_msg void OnBnClickedImportSomasDlgChk4();
	afx_msg void OnBnClickedImportSomasDlgChk5();
	afx_msg void OnBnClickedImportSomasDlgBtn5();


	//CDaoDatabase* m_pSomas_Load;
	//CDaoDatabase* m_pSomas_Voltage;
	//CDaoDatabase* m_pPts;
};
