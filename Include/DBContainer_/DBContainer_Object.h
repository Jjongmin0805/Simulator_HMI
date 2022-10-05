#pragma once

class AFX_EXT_CLASS CDBContainer_Object
{
public:
	CDBContainer_Object(void);
	~CDBContainer_Object(void);

	void																						SetSourceIndex( int nSourceIndex );
	int																							GetSourceIndex();
	void																						SetName( CString szName );
	CString																						GetName();
	void																						DisConnect();
	void																						SetConnectSource( CString szSource );
	void																						SetConnectSource( int nMode );
	CDataSource*																				GetDataSource();
	CSession*																					GetSession();
	CString																						GetErrMessage();
	void																						SetErrMessage( CString szMessage );
	void																						SetConnectStatus( BOOL bStatus );
	BOOL																						IsConnect();
	BOOL																						ConnectDB();

	void																						SetConfig_Provider( CString szProvider );
	void																						SetConfig_DataSource( CString szDataSource );
	void																						SetConfig_DBName( CString szDBName );
	void																						SetConfig_UserID( CString szUserID );
	void																						SetConfig_PassWord( CString szPassWord );
	void																						SetConfig_FailOver( CString szFailOver );
	void																						SetConfig_ServerIP( CString szServerIP );
	void																						SetConfig_ServerPort( int nServerPort );

	CString																						GetConfig_Provider();
	CString																						GetConfig_DataSource();
	CString																						GetConfig_DBName();
	CString																						GetConfig_UserID();
	CString																						GetConfig_PassWord();
	CString																						GetConfig_FailOver();
	CString																						GetConfig_ActiveDataSource();
	CString																						GetConfig_ServerIP();
	int																							GetConfig_ServerPort();

	int																							GetConnectSoureceMode();
	MYSQL*																						GetMySQLConnData();
	CDBContainer_Object*																		Clone();

protected:
	int								m_nSourceIndex;						// DBContainer Source ��ġ
	CString							m_szName;							// Datasource / Dbname�� �����Ǿ� �ִ�
	CDataSource*					m_ACMDBConnect;						// MSSQL �����
	CSession*						m_pACMDBSession;					// MSSQL ���� ����
	CString							m_szErrMessage;						// ���� �޼���
	CString							m_szConnectSourceStr, m_szConnectFailOverSourceStr;				// DBConfig
	BOOL							m_bConnect;							// ���� ����

	CString							m_szProvider;						// Config Provider
	CString							m_szDataSource;						// Config Datasource
	CString							m_szActiveDataSource;				// Config Active Datasource
	CString							m_szDBName;							// Config DBName
	CString							m_szUserID;							// Config UserID
	CString							m_szPassWord;						// Config PassWord
	CString							m_szFailOver;						// Config FailOver
	CString							m_szServerIP;						// Config Server IP
	int								m_nServerPort;						// Config Server Port

	MYSQL							m_DBInitConn;
	MYSQL							*m_pMySQL_DBConn;

	int								m_nConnectSoureceMode;				// ���� ���� ����
};

typedef								vector< CDBContainer_Object* >								VECDBC_OBJ;