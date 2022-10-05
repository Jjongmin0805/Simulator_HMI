#pragma once

class CDBContainer_Object;
class AFX_EXT_CLASS CDB_QUERY
{
public:
	CDB_QUERY( const wchar_t* szQuery, int nSourceIndex = 0 );
	CDB_QUERY( int nSourceIndex = 0 );
	~CDB_QUERY( void );

	
	ULONGLONG																					GetRecordCount();			// ����� ���� ���ڵ� ������
	unsigned int																				GetFieldCount();			// ����� ������ �ʵ� ����

	BOOL																						IsConnect();				// DB ���� ����
	BOOL																						Connect();					// DB ����
	void																						DisConnect();				// DB ���� ����
	bool																						IsSuccess();
	bool																						IsOpen();					// �������� �˱�
	void																						Close();

	bool																						Query( const wchar_t* szQuery );
	bool																						RunExcute( const wchar_t* szQuery );			// Query ����
	bool																						RunQuery( const wchar_t* szQuery );				// Query Data ��ȸ
	
	int																							DBQuery_GetBuff( const wchar_t* szQuery, LONGLONG llBuffSize );				// DB Buff ������
	int																							DBQuery_SetBuff( byte *pBuffData, ULONGLONG ullBuffSize, CString szTableName, CString szFieldName, CString szWhereCon );			// DB Buff �ֱ�
	bool																						GetDBfieldCOUNT();
	bool																						GetDBfieldCOUNT( CString szQuery );
	void																						SetThisRecordCount();

	// Data ��ġ �̵�
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

// ������ ���
	wchar_t*																					GetQuery(){ return (wchar_t*)m_szQuery.c_str(); };

protected:
	void																						RemoveImageData();
	char*																						GetData( unsigned int unField );			// Data ��� Buff

protected:
	CDBContainer_Object				*m_DBContainerOBJ;
	CCommand<CManualAccessor>		m_QueryRS;
	struct DBBINDContainer*			m_pQueryBind;
	HRESULT							m_hQueryOpenResult;
	bool							m_bSuccess;							// ���� ��������

	_tstring						m_szQuery;							// ���� ������
//	int								m_nSourceIndex;						// DB Source Index
	unsigned int					m_unFieldSize;
	unsigned long long				m_ullRecordSize;
	MYSQL_RES						*m_pMySQL_DBResult;
	unsigned long long				m_ullMySQL_RowCurrentPos;
	MYSQL_ROW						m_pMySQL_RowData;

public:
	LONGLONG						m_llImageDataSize;					// IMAGE Data size
	byte*							m_pImageData;						// IMAGE Data

};

