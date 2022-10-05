#pragma once


// CDate_Csv_File_Dlg 대화 상자

class AFX_EXT_CLASS CDate_Csv_File_Dlg : public CDialog
{
	DECLARE_DYNAMIC(CDate_Csv_File_Dlg)

public:
	CDate_Csv_File_Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDate_Csv_File_Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSV_FILES_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int																				m_nCheck_Gen_upload;


	CString																			MyPath();

	void																			GenCSV_Insert();
	int																				GenCSV_Insert_ADD(int nGen_Index, CString szGen_Name, double dGen_CAP_kw, CString szGEN_Connect_NdName, int nGen_TREXCL, int nGen_ITR_WDC, int nGen_TYPE, double dGen_ITR_X, int nGen_MACH_TYPE, CString szGenunit_NM, double dGenunit_CAP_KW, CString szGenunit_NO, int nGen_Check, CString szGen_CEQID );
	void																			GenCSV_Insert_Editor(int nGen_Index, CString szGen_Name, double dGen_CAP_kw, CString szGEN_Connect_NdName, int nGen_TREXCL, int nGen_ITR_WDC, int nGen_TYPE, double dGen_ITR_X, int nGen_MACH_TYPE, double		dGEN_DERAVMVUBRE, double		dGEN_DERAVMVLBREF, double		dGEN_DERAVMQVRATIO, CString szGEN_CEQ, int nGEN_AVR, CString szGEN_CEQID);
	void																			GenUnitCSV_Insert_Editor(CString szGENUNIT_NM, double dGENUNIT_CAP_KW, CString szGENUNIT_CUSTOMER_NO, CString szGEN_CEQID, CString szGEN_Connect_NdName, CString szBOFNM, CString szSSNM, CString szMTRNM, CString szDLNM);
	void																			Set_NEW_InitData_KASIM_GEN_STA_Editor(int nGen_Index, CString szGen_Name, double dGen_CAP_kw, int nGen_TREXCL, int nGen_ITR_WDC, int nGen_TYPE, int dGen_ITR_X, int nGen_MACH_TYPE, int nNDID);
	void																			GenCSV_Editor_Download();
	void																			GenCSV_Editor_Upload();
	void																			RECLOSERCSV_Editor_Download();
	void																			RECLOSERCSV_Editor_Upload();
	//BR
	void																			Set_NEW_InitData_KASIM( int nLNSECID, int nBRID, int nIJID, int nLDID, int nFnd, int nTnd);
	//GEN

	virtual		void																Set_NEW_InitData_KASIM_GEN_STA(CString stKASIM_NM, CString stCEQID, int nID, int nNDID, int nIJID, int nPRDEID, int nGenType, double dGEN_MWLMMX, int nGEN_TREXCL, int nGENUNITID);
	virtual		void																Set_NEW_InitData_KASIM_GEN_DYN_MEA(int nGEN_ID);
	virtual		void																Set_NEW_InitData_KASIM_GEN_DYN_UIN(int nGEN_ID, double dGEN_ITR_CAP, int nGEN_ITR_WDC, double dGEN_ITR_X, int nGEN_MACH_TYPE);
	virtual		void																Set_NEW_InitData_KASIM_GEN_DYN_VVOO(int nGEN_ID);
	virtual		void																Set_NEW_InitData_KASIM_GEN_DYN_PDVRO(int nGEN_ID);

	virtual		void																Set_NEW_InitData_KASIM_IJ(CString stKASIM_NM, int nID, int nNDID, int nIJ_II_EQUTY);
	virtual		void																Set_NEW_InitData_KASIM_ND(CString stKASIM_NM, CString stCEQID, int nID, int nFNDID, int nTNDID, int nIJDID, int nSNVID, int nType);
	virtual		void																Set_NEW_InitData_KASIM_GND(int nID);
	virtual		void																Set_NEW_InitData_KASIM_PRDE(CString stKASIM_NM, int nID);
	virtual		void																Set_NEW_InitData_KASIM_GENUNIT_STA(CString stKASIM_NM, CString stGENUNIT_CUSTOMER_NO, int nID, double dGEN_MWLMMX, int nGENUNITID, CString stGEN_UNIT_CEQID, CString stGEN_CEQID);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
