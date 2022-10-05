#pragma once

#include "PAppDataObj_Field.h"

// KASIM MMDB ���̺� Ŭ����
class CPAppDataObj_Table
{
public:
	CPAppDataObj_Table( unsigned int unOfficeCode );		// KASIM MMDB ���̺� Ŭ���� ������
	CPAppDataObj_Table( unsigned int unOfficeCode, unsigned int unDBType, unsigned int unDBEnv, char *szName, unsigned int unMaxCount );		// KASIM MMDB ���̺� Ŭ���� ������
	~CPAppDataObj_Table(void);		// KASIM MMDB ���̺� Ŭ���� �Ҹ���

	void																	SortIndexField();		// �ʵ� Index ���� ����
	unsigned int															GetSize_SchemaInforTABLE();		// KASIM �ʵ� ��Ű�� ������ ũ�� ���
	void																	GetData_SchemaInforTABLE( char *pSchemaData, unsigned int &unDataPosition );		// KASIM �ʵ� ��Ű�� ������ ���
	void																	SetData_SchemaInforTABLE( char *pSchemaData, unsigned int &unDataPosition, bool bIsCreateBuffData );		// KASIM �ʵ� ��Ű�� ������ ����
	CPAppDataObj_Field*														GetFieldData( char* szFieldName );		// �ʵ� ������ ���
	CPAppDataObj_Field*														GetFieldData( int nFieldIndex );		// �ʵ� ������ ���
	unsigned int															GetDBType();		// RDB Ÿ�� ���
	unsigned int															GetDBEnv();		// RDB �뵵 ���� ���
	char*																	GetName();		// ��Ī ���
	void																	SetLoadingRecordCount( unsigned int nRecordCount );		// �ǵ����� ���� ����
	unsigned int															GetLoadingRecordCount();		// �ǵ����� ���� ���
	unsigned int															GetMaxRecordCount();		// �ִ뵥���� ���� ����

	void																	Insert_FieldData( int nIndex, char* szFieldName, int nDataTypeID, int nVarSize, int nVarCount, char* szExplan );		// �ʵ� ���� ���
//	void																	GET_CheckData( char* szFieldName, unsigned int unIndex, unsigned int unElement );
	bool																	RunExtractionMMDBData( CPString szHBIndexHeaderName, FILE* pHBDataFileStream, HMAP_STR4UINT &hmHBDataFileIndex, unsigned int &unStartPos );		// KASIM RDB�� ���� �ʵ� �����͸� ����
	int																		LoadingCSVtable( unsigned int unRDBIndex );		// ���̺� ��Ī���� �� CSV ���� �б�
	int																		LoadingCSVtableEx( unsigned int unRDBIndex );		// ���̺� ��Ī���� �� CSV ���� �б�(Ȯ��)
	int																		LoadingXMLtable( CSAXMgr *pSAXObj, unsigned int unRDBIndex, unsigned int &unRecordCnt );		// ���̺� ��Ī���� �� XML ���� �б�
	void																	Find_Data( char *szField, unsigned int unStartID, unsigned int unCountID, unsigned int unRealRecordCount );		// �ʵ� ��Ī���� KASIM ������ ���
	void																	ReportOut_TableData( unsigned int unStartID, unsigned int unCountID );		// ���̺� ������ Report�ϱ�
	void																	ReportOut_FieldData( char *szFieldName, unsigned int nStartID, unsigned int nEndID, unsigned int unRealRecordCount );		// �ʵ� ������ Report�ϱ�
	CPString																ReportOut_List();		// KASIM ���̺� �´� ��Ű�� �� �����Ϳ� ���� Report
	void																	GetFieldNames( VECSTR &vecFieldNames );		// �ʵ� ��Ī ���
	void																	GetFieldVarInfor( VECFIELDVARINFOR &vecFieldVarInfor );		// �ʵ� ���� ���� ���
	void																	XMLWriteKASIMData_Table( FILE* pWriteDataFileStream );		// XML ���Ϸ� ����

protected:
	void																	ClearFIELDs();		// �ʵ� ���� ����
	int																		GetCSVData( FILE* pCSVFile, char* pRetBuffData, int &nRetBuffSize );		// �ʵ� ���� CSV���� �б�

protected:
	unsigned int					m_unOfficeCode;

	unsigned int					m_unDBType;								// MMDB ���� : Static(Topology), Dynamic, USER Input
	unsigned int					m_unDBEnv;								// DB Environment : 1 = Application Governor, 2 = Study Mode Process, 3 = DUAL Process
	char							m_szName[ 128 ];						// ���̺� ��Ī
	unsigned int					m_unLoadingRecordCount;					// CSV ���Ͽ��� Loading�� Data ����
	unsigned int					m_unMaxRecordCount;						// ���̺� �ִ� ����

	CPAppDataObj_Field*				m_pOrderInfo_Field;						// ���� �ֱ� ������ Field ����
//	VECPSTR							m_vecFieldName;							// �ʵ� ��Ī ����
	HMAP_FIELD						m_hmapInfor_Field;						// �ʵ� ���� ����
//	MAP_INDEXFIELD					m_mapInfor_IndexField;
	VEC_INDEXFIELD					m_vec_IndexField;						// �ʵ� Index ���� ����
};
 
typedef hash_map< string, CPAppDataObj_Table* >							HMAP_TABLE;
//typedef hash_map< CPString, CPAppDataObj_Table* >							HMAP_TABLE;
//typedef hash_map< CPString, int >											HMAP_TABLEFILTER;

//typedef CAtlMap< CPString, CPAppDataObj_Table*, ATLTRAITS_STRING >									ALTMAP_TABLE;
//typedef CAtlMap< CPString, int, ATLTRAITS_STRING >													ALTMAP_TABLEFILTER;