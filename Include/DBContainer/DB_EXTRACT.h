#pragma once

class AFX_EXT_CLASS CDB_EXTRACT
{
public:
	CDB_EXTRACT( int nMode = -1, wchar_t* szQuery = NULL, int nSourceIndex = 0 );			// nMode = 0 : DBQuery, 1 : DBExcute
	~CDB_EXTRACT(void);

	// Config XML���� ������ DB Database Index ��ġ ���� (Default : 0)
	void																						SetSourceIndex( int nSourceIndex );

	// DB ���� ����
	void																						DBExcute( const wchar_t* szQuery );
	// �ʵ� ���� ������
	int																							DBfieldCOUNT( const wchar_t* szTableName );
	bool																						GetDBfieldCOUNT();
	bool																						GetDBfieldCOUNT( CString szQuery );

	//
	void																						Close();
	// DB Table ���� �б�
	int																							DBQuery( const wchar_t* szQuery );
	// DB Table ���� �б�
	int																							DBQuery_Table( const wchar_t* szTableName, const wchar_t* szSortName = NULL );
	// ���� ���ڵ� ������ ���
	void																						SetThisRecordCount();
	// ����� ���� ���ڵ� ������
	ULONGLONG																					GetRecordCount();
	// ����� ������ �ʵ� ����
	unsigned int																				GetFieldCount();

	bool																						MovePrev();
	bool																						MoveNext();
	bool																						MoveFirst();
	bool																						MoveLast();
	bool																						MoveInitialize();

	// Data ���(���� ���� ��)
	INT																							GetData_NUM( unsigned int unField );
	LONG																						GetData_LONG( unsigned int unField );
	CString																						GetData_STR( unsigned int unField );
	FLOAT																						GetData_FLT( unsigned int unField );
	DOUBLE																						GetData_DBL( unsigned int unField );
	LONGLONG																					GetData_LONGLONG( unsigned int unField );
	CTime																						GetData_TIME_c( unsigned int unField );
	time_t																						GetData_TIME_t( unsigned int unField );

	// �������� �˱�
	bool																						IsOpen();
	//
	bool																						IsSuccess();
	// ������ ���
	wchar_t*																					GetQuery(){ return (wchar_t*)m_szQuery.c_str(); };

	void																						RemoveImageData();
	// DB Buff ������
	int																							DBQuery_GetBuff( const wchar_t* szQuery, LONGLONG llBuffSize );
	int																							DBQuery_SetBuff( byte *pBuffData, ULONGLONG ullBuffSize, CString szTableName, CString szFieldName, CString szWhereCon );

protected : 
	// Data ���( ��, ��)
	char*																						GetData( unsigned int unField );

protected : 
	//
	CCommand<CManualAccessor>		m_QueryRS;
	//
	struct DBBINDContainer*			m_pQueryBind;
	//
	HRESULT							m_hQueryOpenResult;
	// ���� ��������
	bool							m_bSuccess;



	// ���� ������
	_tstring						m_szQuery;
	// DB Source Index
	int								m_nSourceIndex;
	//
	unsigned int					m_unFieldSize;
	//
	unsigned long long				m_ullRecordSize;

	MYSQL_RES						*m_pMySQL_DBResult;
	unsigned long long				m_ullMySQL_RowCurrentPos;
	MYSQL_ROW						m_pMySQL_RowData;

public:
	// IMAGE Data size
	LONGLONG						m_llImageDataSize;
	// IMAGE Data
	byte*							m_pImageData;
};

