#pragma once

#include "PAppDataObj_RDB.h"

// KASIM MMDB Category Ŭ����
// RDB( Real DB )
class CPAppDataObj_Category
{
public:
	CPAppDataObj_Category(void);			// KASIM MMDB Category Ŭ���� ������
	CPAppDataObj_Category( unsigned int unOfficeCode );			// KASIM MMDB Category Ŭ���� ������( ����� �ڵ� ���� )
	~CPAppDataObj_Category(void);			// KASIM MMDB Category Ŭ���� �Ҹ���

	unsigned int															GetOfficeCode();				// KASIM MMDB Category ����� �ڵ� ���
	unsigned int															GetSelectRDBDyn();				// ���� ����� ���õ� RDB ID ���
	unsigned int															GetSize_SchemaInforCATEGORY( unsigned int unDBIndex );				// DBIndex�� �´� KASIM MMDB Category ũ�� ���
	void																	GetData_SchemaInforCATEGORY( char *pSchemaData, unsigned int unDBIndex );				// ��Ű�� �����Ϳ� DBIndex�� �´� KASIM MMDB Category ũ�� ���
	void																	SetData_SchemaInforCATEGORY( char *pSchemaData, unsigned int unDBIndex, bool bIsCreateBuffData );				// ��Ű�� �����Ϳ� DBIndex�� �´� KASIM MMDB Category ����
	void																	Insert_RDBData( unsigned int unDBIndex );				// DBIndex�� �´� KASIM MMDB Category RDB ���
	void																	Delete_RDBData( unsigned int unDBIndex );				// DBIndex�� �´� KASIM MMDB Category RDB ����
	bool																	CopyHBFile_RDBData( unsigned int unSourceDBIndex, unsigned int unTargetDBIndex, bool bForcedContinue_CopyFail );				// KASIM MMDB Category RDB ���� ����
	void																	CopyMMDB_RDBData( unsigned int unSourceDBIndex, unsigned int unTargetDBIndex );				// KASIM MMDB Category RDB ����
	bool																	IsRDBData( unsigned int unDBIndex );				// KASIM MMDB Category RDB ���� Ȯ��
	void																	Insert_Table( unsigned int unDBIndex, unsigned int unDBType, unsigned int unDBEnv, char *szTableName, unsigned int unMaxCount );				// KASIM MMDB Category ���̺� �Է�
	void																	Insert_Field( unsigned int unDBIndex, char *szTableName, int nIndex, char* szFieldName, int nDataTypeID, int nVarSize, int nVarCount, char* szExplan );				// KASIM MMDB Category �ʵ� �Է�
	void																	MakeKASIMS_SchemaInforCategory( bool bIsCreateBuffData );				// KASIM MMDB Category ��Ű�� ����
	void																	MakeKASIMS_SchemaInforCategory( unsigned int unDBIndex, bool bIsCreateBuffData );				// DBIndex�� �´� KASIM MMDB Category ��Ű�� ����
	bool																	MakeKASIMS_HBYFile();				// KASIM MMDB Category ������ ���� ����
	bool																	MakeKASIMS_HBYFile( unsigned int unDBIndex );				// DBIndex�� �´� KASIM MMDB Category ������ ���� ����
	bool																	ConnectKASIMS_HBYFile();				// KASIM MMDB Category ������ ���� ����
	void																	LoadKASIMS_HBYFile2TableRealCount();				// KASIM MMDB Category ������ ���� ���� ���
	void																	InsertSTAorDYNIndex_RDB();				// Static & Dynamic RDB Index ���� ����
	bool																	SelectRDB( unsigned int unDBIndex );				// �������� ����� RDB Index ����
	unsigned int															GetFieldVarSize( char *szTable, char *szField );				// ���̺�� �ʵ� ��Ī�� �´� �ʵ� ���� ũ�� ���
	unsigned int															GetFieldVarType( char *szTable, char *szField );				// ���̺�� �ʵ� ��Ī�� �´� �ʵ� ���� ���� ���

//	void																	GET_CheckData( char *szTableName, char* szFieldName, unsigned int unIndex, unsigned int unElement );				// 
	void*																	GetData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, int &nFieldVarType );				// KASIM Data ���
	CPString																GetData2String( unsigned int unRDBIndex, char* szTable, char* szField, unsigned int unIndex, int nElement );				// KASIM Data ���ڿ��� ���
	double																	GetData2Double( unsigned int unRDBIndex, char* szTable, char* szField, unsigned int unIndex, int nElement );				// KASIM Data Double�� ��ġ�� ���
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, void* pValue );				// KASIM Data �ֱ�
	void																	PutDouble2Data( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, double dValue );				// Double�� ���� KASIM Data �ֱ�
	void																	PutString2Data( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, char* pValue );				// ���ڿ� ���� KASIM Data �ֱ�
	void																	LoadCSVcategory( int nCompressionMode );				// CSV ���� �б�
	void																	LoadCSVcategory( int nCompressionMode, unsigned int unDBIndex, CPString szFilterName = "" );				// Ư�� ��ġ�� �ִ� CSV������ �о RDB Index�� �°� ����
	bool																	LoadXMLcategory( CSAXMgr *pSAXObj );				// ��뷮 CSV������ ����

	void																	Find_Data_Category( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unStartID, unsigned int unCountID );				// Category ã��
	void																	ReportOut_Table_Category( unsigned int unRDBIndex, char *szTable, unsigned int unStartID, unsigned int unCountID );				// ���̺� ������ Report�ϱ�
	void																	ReportOut_Field_Category( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int nStartID, unsigned int nEndID );				// �ʵ� ������ Report�ϱ�
	void																	ReportOut_List( unsigned int unRDBIndex, int nMode, char *szTableName );				// KASIM ��Ű�� �� �����Ϳ� ���� Report
	unsigned int															GetTableRealCount( char *szTableName, int nRDBIndex );				// ���̺� ���� �ǵ������� ����
	unsigned int															GetTableMaxCount( char *szTableName );				// ���̺� ���� �ִ� ����
	void																	GetTableNames( VECSTR &vecTableNames );				// ���̺� ��Ī�� ���
	void																	GetTableFieldNames( char *szTableName, VECSTR &vecFieldNames );				// ���̺� �´� �ʵ� ���� ���
	void																	GetTablePosORFieldVarInfor( unsigned int unRDBIndex, bool bIsGetBuffData, char *szTableName, VECFIELDVARINFOR &vecFieldVarInfor );				// ���̺� �´� �ʵ��� ������ ������ ��ġ�� ���
	void																	SetTableBuffDataByKASIMRDB( unsigned int unRDBIndex, char *szTable, char *szField, char* pValue, unsigned int unSize );				// KASIM RDB �����͸� ���
	void																	SortIndexRDBTableField();				// RDB�� �°� ���̺� �� �ʵ带 ����
	void																	XMLWriteKASIMData_Category( FILE* pWriteDataFileStream, unsigned int unRDBIndex );				// KASIM �����͸� CSV ���Ϸ� �Է�
	void																	XMLWriteReadData_Category( FILE* pWriteDataFileStream, unsigned int unRDBIndex, char* szFilter );				// KASIM �����͸� CSV ���Ϸ� �Է� - ���̺� ��Ī���� ���͸� ����
	void																	XMLWriteCSV_Category( unsigned int unRDBIndex, CPString szPath, char* szFilter, bool bIsSendReviewerMsg, bool bIsShowLogMessage );				// Ư�� RDB�� �ش��ϴ� ���̺� ���� CSV���� ����
	void																	ClearRDBTableData( unsigned int unRDBIndex, char *szTableName );				// ���̺� �ش��ϴ� ������ ����
	
protected:
	void																	Remove_RDBData();				// KASIM MMDB Category RDB ����

	CPAppDataObj_RDB*														GetRDBData( unsigned int unDBIndex );				// DBIndex�� �´� KASIM MMDB Category RDB ���
	CPAppDataObj_RDB*														GetTableName2CategoryRDB( unsigned int unRDBIndex, char *szTable );				// DBIndex�� ���̺� ��Ī�� �´� KASIM MMDB Category RDB ���
	void																	SetRealCount_STA2DYN();				// Static�� Dynamic�� �ǵ����� ������ ����
	void																	SetZeroRealCount_InjectionMaxCount();				// KASIM MMDB Category ���̺��� �ִ� ������ �������� ���� ��� ��Ű���� ���� �ִ� ������ ����

protected:
	unsigned int					m_unOfficeCode;				// KASIM MMDB Category ����� �ڵ�
	CPAppDataObj_RDB				*m_pOrderInfo_RDB_STA, *m_pOrderInfo_RDB_DYN;				// KASIM MMDB Category Static, Dynamic RDB
	VECAPPDATAOB_RDB				m_vecInfo_RDB;				// KASIM MMDB Category RDB �迭
};

typedef hash_map< unsigned int, CPAppDataObj_Category* >					HMAP_CATEGORY;
