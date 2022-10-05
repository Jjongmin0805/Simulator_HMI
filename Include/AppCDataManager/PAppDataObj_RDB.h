#pragma once

#include "PAppDataObj_Table.h"

// KASIM MMDB RealDB Ŭ����
class CPAppDataObj_RDB
{
public:
	CPAppDataObj_RDB( unsigned int unOfficeCode, unsigned int unDBIndex );		// KASIM MMDB RealDB Ŭ���� ������
	~CPAppDataObj_RDB(void);		// KASIM MMDB RealDB Ŭ���� �Ҹ���

	unsigned int															GetSize_SchemaInforRDB();		// KASIM �ʵ� ��Ű�� ������ ũ�� ���
	void																	GetData_SchemaInforRDB( char *pSchemaData );		// KASIM �ʵ� ��Ű�� ������ ���
	void																	SetData_SchemaInforRDB( char *pSchemaData, bool bIsCreateBuffData );		// KASIM �ʵ� ��Ű�� ������ ����
	unsigned int															GetDBIndex();		// ������ RDB Index ���
	unsigned int															GetFieldVarType( char* szTable, char* szField );		// ���̺�� �ʵ� ��Ī�� �´� �ʵ� ���� ũ�� ���
	unsigned int															GetFieldVarSize( char* szTable, char* szField );		// ���̺�� �ʵ� ��Ī�� �´� �ʵ� ���� ���� ���

	void																	Insert_TableData( unsigned int unDBType, unsigned int unDBEnv, char *szTableName, unsigned int unMaxCount );		// KASIM MMDB Category ���̺� �Է�
	void																	Insert_FieldData( char *szTableName, int nIndex, char* szFieldName, int nDataTypeID, int nVarSize, int nVarCount, char* szExplan );		// KASIM MMDB Category �ʵ� �Է�
	bool																	IsTable( char *szTableName );		// KASIM MMDB Category ���̺� ���� Ȯ��
//	bool																	RunExtractionMMDBData( FILE* pHBDataFileStream, HMAP_STR4UINT &hmHBDataFileIndex, unsigned int &unStartPos );
	bool																	MakeKASIMS_RDBData();		// KASIM RDB�� ����
	bool																	ConnectKASIMS_RDBData();		// ������ KASIM RDB�� ����
	bool																	CopyKASIM_HBFileRDBData( CPAppDataObj_RDB* pSourRDB, bool bForcedContinue_CopyFail );		// KASIM MMDB Category RDB ���� ����
	int																		CopyKASIM_MMDBRDBData( CPAppDataObj_RDB* pSourRDB );		// KASIM MMDB Category RDB ����
	void																	InsertSTAorDYNIndex_TABLE();		// Static & Dynamic RDB Index ���� ����

//	void																	GET_CheckData( char *szTableName, char* szFieldName, unsigned int unIndex, unsigned int unElement );
	void*																	GetData( char* szTable, char* szField, unsigned int nIndex, int &nFieldVarType );		// KASIM Data ���
	void*																	GetData( char* szTable, char* szField, unsigned int nIndex, int nElement, int &nFieldVarType );		// KASIM Data ���
	CPString																GetData2String( char* szTable, char* szField, unsigned int unIndex, int nElement );		// KASIM Data ���ڿ��� ���
	double																	GetData2Double( char* szTable, char* szField, unsigned int unIndex, int nElement );		// KASIM Data Double�� ��ġ�� ���
	void																	PutData( char* szTable, char* szField, unsigned int unIndex, int nElement, void* pValue );		// KASIM Data �ֱ�
	void																	PutDouble2Data( char* szTable, char* szField, unsigned int unIndex, int nElement, double dValue );		// Double�� ���� KASIM Data �ֱ�
	void																	PutString2Data( char* szTable, char* szField, unsigned int unIndex, int nElement, char* pValue );		// ���ڿ� ���� KASIM Data �ֱ�
	void																	LoadCSVrdb( CPString szFilterName = "" );		// CSV ���� �б�
	void																	LoadXMLrdb( CSAXMgr *pSAXObj, CPString szTableName );		// CSV ���� �б�
	void																	LoadKASIMS_HBYFile2TableRealCountRDB();		// KASIM ���̺� �ش��ϴ� �ǵ����� ������ �缳��

	void																	Find_Data_Rdb( char *szTable, char *szField, unsigned int unStartID, unsigned int unCountID );		// KASIM RDB ������ ã��
	void																	ReportOut_Table_Rdb( char *szTable, unsigned int unStartID, unsigned int unCountID );		// ���̺� ������ Report�ϱ�
	void																	ReportOut_Field_Rdb( char *szTable, char *szField, unsigned int nStartID, unsigned int nEndID );		// �ʵ� ������ Report�ϱ�
	void																	ReportOut_List( int nMode, char *szTable );		// KASIM ���̺� �´� ��Ű�� �� �����Ϳ� ���� Report
	void																	ReportOut_ListALLTable( char *szTable, vector< string > &vecTableInfor );		// KASIM ��� ���̺��� ��Ű�� �� �����Ϳ� ���� Report
	unsigned int															GetTableRealCount( char *szTableName );		// ���̺� ���� �ǵ������� ���� ���
	void																	SetTableRealCount( char *szTableName, unsigned int unRealCount );		// ���̺� ���� �ǵ������� ���� ����
	unsigned int															GetTableMaxCount( char *szTableName );		// ���̺� ���� �ִ� ����
	void																	GetTableFieldNames( char *szTableName, VECSTR &vecFieldNames );		// �ʵ� ��Ī�� ���
	void																	GetTablePosORFieldVarInfor( bool bIsGetBuffData, char *szTableName, VECFIELDVARINFOR &vecFieldVarInfor );		// ���̺� �´� �ʵ��� ������ ������ ��ġ�� ���
	void																	SetTableBuffDataByKASIMRDB( char* szTable, char* szField, char* pValue, unsigned int unSize );		// KASIM RDB �����͸� ���
	void																	SortIndexTableField();		// �� �°� ���̺� �� �ʵ带 ����
	//void																	XMLWriteKASIMData_RDB( FILE* pWriteDataFileStream, char* szFilter );
	void																	XMLWriteKASIMData_RDB( FILE* pWriteDataFileStream );		// KASIM RDB ��Ű�� �� �����͸� XML ���Ϸ� ����
	void																	XMLWriteRealData_RDB( FILE* pWriteDataFileStream, char* szFilter );		// KASIM RDB �����͸� XML ���Ϸ� ����
	void																	XMLWriteCSVData_RDB( CPString szPath, char* szFilter, bool bIsSendReviewerMsg, bool bIsShowLogMessage );		// KASIM XML ������ �о� CSV ���Ϸ� ����
	void																	GetTableNames( VECSTR &vecTableNames );		// ���̺� ��Ī�� ���
	int																		GetTableNamesAndLoadingCount( VECPSTR &vecTableNames, VECUINT &vecTableLoadingCount );		// KASIM ���̺� ���� ������ ���� ���
	void																	SetTableNameLoadingCount( CPString szSearchTableName, unsigned int unTableLoadingCount );		// KASIM ���̺� ���� ������ ���� ����
	void																	SetTableName4ZeroCount_MaxCount();		// KASIM ���̺� �ǵ����� ������ 0�� ���̺��� Max ������ ����

	unsigned int															GetRDBHBFileMMDBSize();		// KASIM RDB ���� ũ�� ���
	unsigned int															GetIRBHBIndexMMDBSize();		// KASIM RDB index ũ�� ���
	char*																	GetIRBHBIndexMMDBData();		// KASIM RDB ������ ũ�� ���
	void																	ClearTableData( char* szTableName );		// KASIM ���̺� ������ ����

protected:
	void																	ClearMMDB();		// KASIM RDB ����
	void																	ClearHBDataFileIndex();		// KASIM RDB Index ����
	void																	ClearTABLEs();		// KASIM RDB�� ��ϵ� ���̺� ����

	unsigned int															GetTableDataMovePoint( unsigned int unIndex, int nElement, int nFieldVarCount, unsigned int unFieldVarSize, unsigned int unFieldVarRealSize );		// 
	CPAppDataObj_Table*														GetTableData( char *szTableName );		// KASIM ���̺� ���� ���
	long																	GetHBINdexPosition( char* szTable, char* szField );		// KASIM ���̺� �� �ʵ� ������ ��ġ ���
	unsigned int															GetHBINdexTableRealCountPosition( char* szTable );		// KASIM ���̺� �ǵ����� ���� ���� ��ġ ���
	CPString																GetHBFileObjName();		// KASIM RDB ���� ��Ī ���
	CPString																GetHBFileIndexObjName();		// KASIM RDB Index ���� ��Ī ���
	CPString																GetHBIndexObjName();		// KASIM RDB Index ��Ī ���
	CPString																GetHBIndexObjName( unsigned int unID );		// KASIM RDB Index ��Ī ���
	CPString																GetHBIndexObjTableFieldName( char* szTable, char* szField );		// ���̺� �� �ʵ� ��Ī�� �´� KASIM RDB Index ��Ī ���
	bool																	GetDataMovePosition(	bool bIsGetMode, unsigned int &unMovePosValue, unsigned int &unFieldVarType, unsigned int &unFieldVarSize, 
																									unsigned int &unFieldVarRealSize, char* szTable, char* szField, unsigned int unIndex, int nElement );		// KASIM RDB Index ��ġ �� �ʵ� ���� ���

protected:
	unsigned int					m_unOfficeCode;
	unsigned int					m_unID;									// MMDB INDEX : STA, SCHEDUL, EVENT, EXCEPTION, STUDY
	CPString						m_szRData_File, m_szIData_File;			// Hybrid-File MMDB Real Data, Index Data ���� ��Ī
	CFileMapObject					*m_pRData_MMDB, *m_pIData_MMDB;			// MMDB Real Data, Index Data
	HMAP_STR4UINT					m_hmHBDataFileIndex;					// MMDB RDB�� ���� ��ġ Index ����
	CPAppDataObj_Table				*m_pOrderInfo_Table;					// ���� �ֱٿ� �˻��� Table ����
	HMAP_TABLE						m_hmInfor_Table;						// RDB Table ���� ����( Online & Study Mode�� ���� ����Ǵ� ������ �ٸ�)
	HMAP_TABLE						m_hmExcludeInfor_Table;					// RDB Online�� ����Ǵ� �������� Table ����
};

typedef vector< CPAppDataObj_RDB* >											VECAPPDATAOB_RDB;
