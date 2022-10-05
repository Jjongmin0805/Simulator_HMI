#pragma once

#include <atldbcli.h>
#include <atldbsch.h>
#include "DBContainer_Object.h"

class AFX_EXT_CLASS CDBContainer_Insatnce
{
public:
	CDBContainer_Insatnce(void);
	~CDBContainer_Insatnce(void);
	// CDBContainer_Insatnce�� �������� ����� �� �ֵ��� ����
	static CDBContainer_Insatnce*															Instance( void );
	static void																				Close(void);

protected : 
	static CDBContainer_Insatnce*	m_pMngData;												//�̱����� �������� ����ϱ� ���Ͽ� ����

public:
	// �ʱ�ȭ
	bool																					Init();
	// DB ���� �б�
	DB_VECSTR																				LoadingDBConfig();

	// ������ġ ����( ����ġ, ����ġ )
	_tstring																				GetMyPath( _tstring szPath, _tstring szFile = _T("") );
	// ���ڿ��� �ҹ��ڷ� ����( ���ڿ� )
	bool																					TranformLow( wchar_t* szValue );
	// ���ڿ��� �빮�ڷ� ����( ���ڿ� )
	bool																					TranformHigh( wchar_t* szValue );
	// str Trim
	void																					strTrim( _tstring& szSource, _tstring szTarget, _tstring szRep );
	// DB ���� ���� ����
	void																					SetConnectStatus( int nIndex, BOOL bStatus );
	// DB ���� ����
	BOOL																					IsConnect( int nIndex );
	// DB ����( DB ���� )
	BOOL																					ConnectDB( bool bAutoReconnect = false );
	// DB ����
	BOOL																					ConnectDB( int nIndex );
	// DB ���� ����
	BOOL																					DisConnectDB( int nIndex );
	// DB �翬��
	BOOL																					ReConnectDB( int nIndex );


	// DB DataSource ���
	CDataSource*																			GetDataSource( int nIndex );
	// DB Session ���
	CSession*																				GetSession( int nIndex );
	// DB Object ���� ���
	int																						GetDBObjectCount();
	// ���� ���� ���(MSSQL:1, Orcle:2, ADO:3)
	int																						GetSessionConnectSourceMode( int nIndex );

	bool																					IsCheckDBConnect( int nIndex );

	CDBContainer_Object*																	GetDBConnectObject( int nIndex );

	// ������ ���� �޼��� �����
	CString																					GetLastErrMsg();
	void																					SetLastErrMsg( int nIndex, CString szErrMsg );

	void																					SetLogMutexName( _tstring szName );
	_tstring																				GetLogFileName();
	void																					SetLogFileName( _tstring szFileName );
	void																					WriteLog( const wchar_t *msg, ... );
	void																					WriteLog( const char *msg, ... );
	void																					WriteLog2File( char* szFilePath, char* szMsg );

	bool																					SetValue2String( unsigned long long* ullDblData, int nDataSize, char* pRtBuff );
	bool																					SetValue2String( unsigned long long* ullDblData, int nDataSize, wchar_t* pRtBuff );
	bool																					SetValue2String( double* pDblData, int nDataSize, char* pRtBuff );
	bool																					SetValue2String( double* pDblData, int nDataSize, wchar_t* pRtBuff );
	bool																					SetValue2String( int* pDblData, int nDataSize, char* pRtBuff );
	bool																					SetValue2String( int* pDblData, int nDataSize, wchar_t* pRtBuff );

	bool																					SetStrings2Value( char* pRtBuff, unsigned long long* pDblData, int nDataSize );
	bool																					SetStrings2Value( wchar_t* pRtBuff, unsigned long long* pDblData, int nDataSize );
	bool																					SetStrings2Value( char* pRtBuff, double* pDblData, int nDataSize );
	bool																					SetStrings2Value( wchar_t* pRtBuff, double* pDblData, int nDataSize );
	bool																					SetStrings2Value( char* pRtBuff, int* pDblData, int nDataSize );
	bool																					SetStrings2Value( wchar_t* pRtBuff, int* pDblData, int nDataSize );

	bool																					DeleteAllFilesInFolder( TCHAR* szDeleteFolder, TCHAR* szFileExtend, bool bDoAsk = false );

	CString																					GetConfigProvider( int nIndex );
	CString																					GetConfigDataSource( int nIndex );
	CString																					GetConfigDBName( int nIndex );
	CString																					GetConfigUserID( int nIndex );
	CString																					GetConfigPassWord( int nIndex );
	CString																					GetConfigFailOver( int nIndex );
	CString																					GetConfigActiveDataSource( int nIndex );
	CString																					GetConfigServerIP( int nIndex );
	int																						GetConfigServerPort( int nIndex );
	void																					SetBCopyFolderName( CString szFolderName );
	CString																					GetBCopyFolderName();
	void																					CheckBCopyFolder();
	BOOL																					GetProcessLive( CString sProcessName );
	BOOL																					KillProcess( CString szProcessName );
	int																						MariaDB_UploadFile( int nDBSourceIndex, char *szPathFile, char *szUploadData_TableName, char *szUploadData_FieldName, char *szUploadSize_FieldName, char *szUploadData_WhereData );
	int																						MariaDB_DownloadFile( int nDBSourceIndex, char *szDownloadFile_Path, char *szDownloadFile_Name, char *szDN_DBTableName, char *szDN_DBFieldName, char *szDN_DBWhereData );
	void																					SetIsThread_CheckDBConnectStatus( bool bIsStatus );
	bool																					IsThread_CheckDBConnectStatus();
	void																					CloseThread_CheckDBConnectStatus();
	void																					RunThread_CheckDBConnectStatus();
	void																					SetAutoConnection( bool bIsAutoConnection );
	bool																					GetAutoConnection();
	MYSQL*																					GetMySQLConn( int nIndex );
	string																					StrConvert_MultiCharToUFT8( const char* pszInString );
	string																					StrConvert_UFT8ToMultiChar( const char* pszInString );
	void																					SetAutoConnection_Lock();
	void																					SetAutoConnection_Unlock();

	int MariaDB_GetTest();

protected : 
	void																					RemoveData();
	BOOL																					GetProcessModule( DWORD dwPID, CString sProcessName );
	bool																					CreateRealDirectory( const char* szPath );

	static UINT WINAPI																		RunThreadProcess_CheckDBConnectStatus( LPVOID pParam );

protected : 
	VECDBC_OBJ						m_vecObjs;

	HANDLE							m_hLockMutex_Log;							// Log ���� ��ȣ �ڵ�
	_tstring						m_szLogMutexName;							// Log Lock Mutext Name
	_tstring						m_szLogFileName;							// Log ���� �̸�
	int								m_nLastDBIndex;								// ������ ���õ� DB Source Index ����
	CString							m_szBCopyFolder;							// Binary Copy ���� ��Ī
	HANDLE							m_hThread_CheckDBConnectStatus;				// DB ���� ���� Ȯ�� ������ �ڵ�
	bool							m_bIsThread_CheckDBConnectStatus;			// DB ���� ���� Ȯ�� ������ ���� ����
	bool							m_bAutoConnection;
	CRITICAL_SECTION				m_LockAutoConnection;
};

#define								theDBContainer											CDBContainer_Insatnce::Instance()
#define								MYPATH( a, b )											CDBContainer_Insatnce::Instance()->GetMyPath( a, b )
#define								TEXTLOW( a )											CDBContainer_Insatnce::Instance()->TranformLow( a )
#define								TEXTHIGH( a )											CDBContainer_Insatnce::Instance()->TranformHigh( a )
#define								TEXTTRIM( a, b, c )										CDBContainer_Insatnce::Instance()->strTrim( a, b, c )
#define								DBCLOG													CDBContainer_Insatnce::Instance()->WriteLog