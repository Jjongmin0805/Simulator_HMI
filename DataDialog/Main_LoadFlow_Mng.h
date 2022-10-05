#pragma once


#define						VIEWLB_CLICK						1
#define						VIEWLB_UNCLICK						0

class CLFData
{
public:
	CLFData::CLFData() : m_nIdx(0), m_szSSName(_T("")), m_szDLName(_T("")), m_szGENName(_T("")), m_nType(0),
		m_ViewRect(0, 0, 0, 0), m_ViewRoundRect(m_ViewRect), m_MaxValuePt(0, 0), m_MinValuePt(m_MaxValuePt),
		m_nScrollPos(0), m_nChangeYposValue(0), m_dValueMax(0.0), m_dValueMin(0.0), m_nValueMaxLimit(0),
		m_nValueMinLimit(0), m_nSelectIndex(0), m_nMoveSelectIndex(0), m_dDrawRatio(0.0)
	{
		for (int i = 0; i < 96; i++)
		{
			m_nMultiSelectIndex[i] = VIEWLB_UNCLICK;
			m_vecLoadValue.push_back(0.0);
		}
	};
	CLFData::~CLFData()
	{
		if (m_vecLoadValue.size() > 0)
		{
			m_vecLoadValue.clear();
		}
		if (m_vecLoadValuePt.size() > 0)
		{
			m_vecLoadValuePt.clear();
		}
	};

public:
	int										m_nIdx;
	wstring									m_szSSName, m_szDLName, m_szGENName;
	int										m_nType;				// 1 : cb , 2 : DG
	CRect									m_ViewRect, m_ViewRoundRect;
	vector<double>							m_vecLoadValue;
	vector<CPoint>							m_vecLoadValuePt;
	CPoint									m_MaxValuePt, m_MinValuePt;
	int										m_nScrollPos, m_nChangeYposValue;
	double									m_dValueMax, m_dValueMin;
	int										m_nValueMaxLimit, m_nValueMinLimit;
	int										m_nSelectIndex, m_nMoveSelectIndex, m_nMultiSelectIndex[96];
	double									m_dDrawRatio;
};


class CVMLFData
{
public:
	CVMLFData::CVMLFData(void) : m_nType(0)
	{
		memset(m_szSSName, 0x00, sizeof(m_szSSName));
		memset(m_szDLName, 0x00, sizeof(m_szDLName));
		memset(m_szGENName, 0x00, sizeof(m_szGENName));
		memset(m_dLoadValue, 0x00, sizeof(m_dLoadValue));
	};
	CVMLFData::CVMLFData(CLFData* pLFData) : m_nType(pLFData->m_nType)
	{
		swprintf_s(m_szSSName, _T("%s"), pLFData->m_szSSName.c_str());
		swprintf_s(m_szDLName, _T("%s"), pLFData->m_szDLName.c_str());
		swprintf_s(m_szGENName, _T("%s"), pLFData->m_szGENName.c_str());
		for (int i = 0; i < 96; i++)
		{
			m_dLoadValue[i] = pLFData->m_vecLoadValue[i];
		}
	};

	CVMLFData::~CVMLFData(void)
	{
		//
	};

public:
	wchar_t									m_szSSName[32];
	wchar_t									m_szDLName[32];
	wchar_t									m_szGENName[64];
	int										m_nType;
	double									m_dLoadValue[96];
};

#define								CLASSSIZEBUFF_SIZE										8
#define								LFINFOR_VMNAME											_T("MG_LFVMInforData")

#define								SENDMSG_LOADFLOW										( WM_USER + 22 )

class CMain_LoadFlow_Mng
{
public:
	CMain_LoadFlow_Mng(void);
	~CMain_LoadFlow_Mng(void);

	void									CloseThread();

	void									Loading( void );
	int										LoadLFFInfor_CSVFile();
	void									LoadingScada( void );
	void									Create_VMLFInfor();
	void									Loading_VMLFInfor();
//	void									CSVWrite_LFFInfor();
	int										CheckLFFSchedule();
	void									SetLFFSeqTimeValue( int nValue );
	void									SetDLNode_load();
	int										GetLFFSeqIndex(){ return m_nLFFSeqIndex; };
	void									SetLFFSeqNowPosition( int nPos ){ m_nLFFSeqNow = nPos; };
	void									SetDGBeforeSWinit();
	int										GetClassSize();
	void									CreateVMemory_LFInfor( int nSIze, char* pDataBuff );
	char*									LoadVMemory_LFInfor( unsigned int &nSize );
	void									WriteVMemory_LFInfor( int nSIze, char* pDataBuff );
	void									ThreadRun_LFAppl();

	bool									IsLFApplReady();
	bool									GetThread_LFAppl(){ return m_bThread_LFAPPL; };
	void									SetThread_LFAppl( bool bStatus ){ m_bThread_LFAPPL = bStatus; };
	void									SetLFSMIndex( int nIndex ){ m_nLFSM_Index = nIndex; };
	int										GetLFSMIndex(){ return  m_nLFSM_Index; };
	void									SetLFSMCaseId( int nCaseId ){ m_nLFSM_CaseId = nCaseId; };
	int										GetLFSMCaseId(){ return m_nLFSM_CaseId; };
	bool									RunProcess_LFAppl();

	void									Start_LoadFlow();
	void									Stop_LoadFlow();

	void									SetLoadProfilePath( CString szLoadProfilePath ){ m_szLoadProfilePath = szLoadProfilePath; };
	CString									GetLoadProfilePath(){ return m_szLoadProfilePath; };
	void									SetLFFExeFileName( CString szFileName );
	void									SetLoadFlowWnd( CWnd* pLoadFlowWnd );
	void									SetLoadFlowEditorMSG( int nWPvalue, int nLPvalue );

protected:
	void									CSVWrite_LFFInfor_Current( FILE* pCSVfile, double* fData );
	void									SetFLData_ACMLoading();
	void									SetFLData_ScadaCSVFile();
	void									SetFLData_GenValue();
	CVMLFData*								GetLFData( wstring szSSName, wstring szDLName, wstring szGENName, int nType );

	void									GetDowntreeGBRs( int nGNDIdx, int nNextGbrIdx );
	void									SetDLNode_load_CB( wstring szSSName, wstring szDLName, double dLoad );
	void									SetDLNode_load_DG( wstring szGenName, double dLoad );
	void									SetDLNode_load_GENa( wstring szGenName, double dLoad );

	void									SetDLNode_load_LDdynDLPO( int nIjIdx );

//	void									SetDGBeforeSWinit();
	BOOL									AddInitIJIdx( int nGNDIdx );
	void									GetDowntreeGND( int nGNDIdx, int nGBRIdx );
	void									GetDowntreeCBSWs( int nGNDIdx, int nCBSWIdx );
	void									GetDowntreeTISWs( int nGNDIdx, int nTISWIdx );
	static UINT WINAPI						LFAppl_Process( LPVOID pParam );

	vector<int>								m_vecIJIDXs;
	vector<CVMLFData*>						m_vecVMLFdata;
	int										m_nLFFSeqValue, m_nLFFSeqNow, m_nLFFSeqIndex;
	double									m_dPFRadial;

	HANDLE									m_hLFInfor;
	LPVOID									m_pLFInfor;

	HANDLE									m_hThread_LFAPPL;
	bool									m_bThread_LFAPPL;
	int										m_nLFSM_Index, m_nLFSM_CaseId;
	CString									m_szLoadProfilePath;
	CString									m_szLFFExeFileName;

	CWnd*									m_pLoadFlowEditor;
};

