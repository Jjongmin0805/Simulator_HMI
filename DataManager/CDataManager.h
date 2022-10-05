#pragma once

#include <oledb.h>
#include <atldbcli.h>//CSession용
#include <atldbsch.h>

#include "CGraphData.h"
#include "CAppl_Info.h"
#include "CDB_Info.h"

#define								WNDMSG_PROGRAMID_HMI												2
#define								WNDMSG_PROGRAMID_SLD												3
#define								WNDMSG_PROGRAMID_EDITOR												4

#define								SENDLOGMSG_PARAM										( WM_USER + 1 )

#define								SENDLOGMSG_COLOR_NOR									RGB(0,0,0)
#define								SENDLOGMSG_COLOR_SUC									RGB(0,0,255)
#define								SENDLOGMSG_COLOR_ERR									RGB(255,0,0)

#define	SW_CLOSE				1
#define	SW_OPEN					0

#define				RELAY_AD_TYPE_ANALOG			0
#define				RELAY_AD_TYPE_DISITAL			1

#define				RELAY_OG_TYPE_OCR			0
#define				RELAY_OG_TYPE_OCGR			1

#define				RELAY_FD_TYPE_FAST			1
#define				RELAY_FD_TYPE_DELAY			0


typedef AFX_EXT_CLASS CArray<int, int&> CIntArray;
typedef AFX_EXT_CLASS CArray<double, double&> CDoubleArray;

struct MYBIND
{
	MYBIND()
	{
		memset(this, 0, sizeof(*this));
	}

	TCHAR   szValue[50];
	DWORD   dwStatus;
};


class AFX_EXT_CLASS CDataManager
{
public:
	CDataManager(void);
	~CDataManager(void);

private:
	static CDataManager* _instance;// 싱글톤(Singleton) - 메모리에 한번만 띄움
public:
	static CDataManager* Instance(BOOL bInit = FALSE);

	CString MyPath();

	////////////////// KACIM MMDB
	void										LoadKASIM();
	void										EndKASIM(); 
	void										MakeOfficeCodeMMDB(unsigned int unOfficeCode, int nRDBType, int nRDBIndex);
	void										GetTestKASIMData();
	void										PutTestKASIMData();



	///////////////
	void										GetSSName_array(CStringArray* pArray,CIntArray* pArray_idx = NULL);
	void										GetSSNames(vector<wstring>* vecString);
	void										GetDLName_array(CString strSSName,CStringArray* pArray, CString strMTRName = _T(""), CIntArray* pArray_idx = NULL);
	void										GetDLNames(wstring szSSName, vector<wstring>* vecString);
	void										GetMTRName_array(CString strSSName, CStringArray* pArray, CIntArray* pArray_idx = NULL);

	BYTE*										m_pBRTrace;
	void										GetData_Graph(int nDL_idx,CGraphDataArray* pArray);
	void										Graph_Data_Add(CGraphDataArray* pArray, double dPrev_Len,double dCurr_Len ,int nGBR_idx, int nPrevID, int nCurrID, BOOL bAdd);
	int											FindGroupCB(CGraphDataArray* pArray,int nPreBRIdx, int nNDIdx);
	int											FindGroupCBRcv(CGraphDataArray* pArray, int nGBRIdx, int nFGNDIdx,int nGraphND_Prev, double dPrev_Len, double dCurr_Len);
	int											GetGroupCbswToNode( int nGNDIdx);
	int											GetGroupNDStatus(int nGNDIdx);//NODE_ID를 가지고 상태값을 확인한다(개폐기가 아니라면 그냥 CLOSE로 함)
	int											GetSwStatus(int nCbswIdx);//cbsw_sta_id를 가지고 개폐기 상태값을 확인
	int											CheckGroupConnectSw(int nGNDIdx);//다회로개폐기인지 체크(연결스위치가 2개이상이면 다회로)
	int											GetGroupToNDIdx(CGraphDataArray* pArray, double dPrev_Len, double dCurr_Len, int nFGNDIdx, int nGNDIdx);//설비기준 전원측노드 -> 부하측노드를 가져온다.

	int											GetDLIndex(CString strDLName);

	int											GetTCCSET_Index(CString strCOSName);

	void										SetRelayInfo2DB();


	void										KASIM_SaveAs(CString strPath);
	void										KASIM_LoadAs(CString strPath);
	void										MMDB_Restart();

	//////////////  
	int											m_nExe_ViewID;
	int											GetExe_ViewID() {	return m_nExe_ViewID;	};
	void										Excute_Appl(CString strAppl_ID,int nViewID = 0);
	void										Excute_Appl_test(CString strAppl_ID);

	/////////////////
	BOOL										Excute_SLD();

	BOOL										GetProcessModule(DWORD dwPID, wstring sProcessName);
	BOOL										KillProcess(wstring szProcessName);


	void										SQLDBExcute(CSession *pDB, CString szQuery);
	/////////////////////////// 로컬데이터 관리
	CSession									m_Session_localData;
	CDataSource									m_Connect_localData;
	void										ConnectDB_LocalData();

	/////////////////////////// lineType, 보호기기 관리
	CSession									m_Session_OD;

	CDataSource									m_Connect_OD;
	CString										m_OleDB_Provider;
	void										Read_OleDBConfig();
	void										ConnectDB_OD();

	////////////////////////// Somas
	CSession									m_Session_SomasInfo;
	CDataSource									m_Connect_SomasInfo;
	void										ConnectDB_SomasInfo();

	CSession									m_Session_SomasLog;
	CDataSource									m_Connect_SomasLog;
	void										ConnectDB_SomasLog();

	///////////////////////// Appl info
	CAppl_InfoArray								m_Array_ApplInfo;
	BOOL										Read_ApplInfo();

	///////////////////////// Ole ODBC ADMS DB
	CDB_InfoArray								m_Array_DBInfo;
	BOOL										Read_DBInfo();
	void										ConnectDB_ADMS();
//	CDBContainer_Insatnce*						GetDBContainer();
	int											GetMachineType_AD(int nMachine_ID);
	double										GetRelayTabValue(int nMachine_ID, int nOGType, int nFDType, double dInput_value);


	///////////////////////
	void										Set_PDVR_Voltage2ADMS(int nTR_Idx,int nMode,COleDateTime tFrom, COleDateTime tTo);

public:
	void										Send_WndMsg(int nProgramID, int nType, CString strData);
};

#define								theDataMng												CDataManager::Instance()

#define								SENDLOGMSG( msg, color )	\
{ \
	if( AfxGetApp() && AfxGetApp()->GetMainWnd() ) \
	{ \
	AfxGetApp()->GetMainWnd()->SendMessage( SENDLOGMSG_PARAM, (WPARAM)##msg, (LPARAM)##color );  \
	} \
}