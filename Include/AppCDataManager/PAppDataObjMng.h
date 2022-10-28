#pragma once

#include "PKASIM_Schema_VarData.h"
#include "PAppDataObj_Category.h"

#ifdef _APPGOVERNOR_COM_VER_
#include "../PUSDT_PCommManager/PLocker.h"
#include "../PUSDT_PCommManager/PWThread.h"
#else
#include "../include/PUSDT_PCommManager/PLocker.h"
#include "../include/PUSDT_PCommManager/PWThread.h"
#endif

// ����� ���� Ŭ����
class COfficeCodeInfor
{
public:
	COfficeCodeInfor() : m_unOfficeCode( 0U ), m_nRDBType( -1 ), m_nRDBIndex( 0 )		// ����� ���� Ŭ���� ������
	{
		//
	};
	~COfficeCodeInfor()			// ����� ���� Ŭ���� �Ҹ���
	{
		//
	};

public:
	CPString				m_szApplRunName;			// �������α׷� ���� ��Ī
	unsigned int			m_unOfficeCode;			// ������ڵ�
//	int						m_nCreateCategoryStatus;				// -1 : Init, 0 : stand by, 1: STA & DYN Create, 2: DYN Update
	int						m_nRDBType;						// 1 : Static, 2 : Dynamic
	int						m_nRDBIndex;					// RDB Index
};

// KASIM ���� Ŭ����
class AFX_EXT_CLASS CPAppDataObjMng
{
public:
	static CPAppDataObjMng*													InitInstance( void );
	static void																Close( void );

protected:
	static CPAppDataObjMng*			m_pMngData;

//------------------------------------------------------------------------------------------------

public:
	CPAppDataObjMng(void);		// KASIM ���� Ŭ���� ������
	~CPAppDataObjMng(void);			// KASIM ���� Ŭ���� �Ҹ���

	bool																	ConnectDB();				// KASSIM ����
	void																	CloseDB();			// KASSIM ���� ����
	int																		GetOnlineStudyMode();					// Online�� Study Mode ���
	void																	SetOnlineStudyMode( int nMode );			// Online�� Study Mode ����
	CPString																GetKASIMAP_WriteIndex();				// KASIM RDB ������ ���
	void																	SetKASIMAP_WriteIndex( CPString nWriteIndex );				// KASIM RDB ������ ����
	void																	MakeKASIMAP_WriteIndex();				// KASIM RDB ������ ����
	CPString																GetKASIMST_WriteIndex();				// KASIM RDB Index ������ ���
	void																	SetKASIMST_WriteIndex( CPString nWriteIndex );				// KASIM RDB Index ������ ����
	void																	MakeKASIMST_WriteIndex();				// KASIM RDB Index ������ ����

	void																	AddOfficeCode( CPString szOfficeCodesString );		// ����� ���� ���
	void																	AddOfficeCode( unsigned int unOfficeCode );		// ����� ���� ���
	void																	DeleteOfficeCode( unsigned int unOfficeCode );		// ����� ���� ����
	void																	SetOfficeInforStatus( unsigned int unOfficeCode, int nRDBType, int nRDBIndex );		// ����� ���� ���� ����
	void																	MakeOfficeInfor_MakeTopology( unsigned int unOfficeCode, int nRDBIndex );		// KASIM ���� ���� ����
	void																	MakeOfficeInfor_UpdateDynamic( unsigned int unOfficeCode, int nRDBIndex );		// KSAIM Dynamic ���� ����
	int																		GetOfficeInforRDBType( unsigned int unOfficeCode );		// KASIM RDB ���� ���
	void																	DeleteCategoryData( unsigned int unOfficeCode );				// ����� �ڵ��� ī�װ� ����
	unsigned int															GetFieldVariant( unsigned int unVarType );				// ��Ű�� �ʵ��� ���� ������ ���
	unsigned int															GetTableType( char* szTableName );					// ���̺��� ������ ���
	unsigned int															GetDefault_STAorDYN( unsigned int unSTAorDYN );			// ���� �������Ʈ���� ���� ���� ������ ���� ���� ���
	void																	SetTableType( char* szTableName, unsigned int unSTAorDYN );		// ��Ű�� ���̺� ��Ī�� ���� ������ ���� ���� ����
	void																	ReleaseOfficeInfor();					// ����� ���� ����
	void																	InitOfficeInfor();										// ��Ű�� ������ ����� ���� �ʱ�ȭ �۾�
	int																		IsConnectKASIMData( unsigned int unOfficeCode, unsigned int unRDBIndex );		// ������ڵ忡 �´� KASIM ���� ���� Ȯ��
	bool																	ConnectKASIMData( unsigned int unOfficeCode, unsigned int unRDBIndex = KASIMRDBINDEX_DYN );		// ������ڵ忡 �´� KASIM ����
	void																	DIsConnectKASIMData( unsigned int unOfficeCode );		// ������ڵ忡 �´� KASIM ���� ����
	void																	DIsConnectKASIMRDBData( unsigned int unOfficeCode, unsigned int unRDBIndex );		// ������ڵ�� KASIM RDB�� �´� KASIM RDB ���� ����
	void																	LoadOfficeInfor();										// ����Һ��� mmdb�� ����
	char*																	GetSchemaDataSTA();										// ��Ű���� ���������� ���
	char*																	GetSchemaDataDYN();										// ��Ű���� ���������� ���
	void																	InsertSTAorDYNIndex();									// ��Ű���� ������ ���� ���� ���� �߰�
	CPAppDataObj_Category*													GetOrderOfficeCode();									// ���� ������ ����� �ڵ� ���
	void																	SetSelectFirstofficecode();									// ���� ������ ����� �ڵ� ���
	void																	SetofficecodeNrdbtype( unsigned int unOfficeCode, unsigned int unRDBType );			// Search MMDB ���� = Office, RDBType
	int																		SelectOfficecodeANDRDBType();							// OfficeCode �� DBType ���� �о� ������ ����
	int																		SetSelectOffceCodeNRDBIndex( unsigned int unOfficeCode, unsigned int unRDBIndex );			// ���� ���õ� ������ڵ��� RDB Index�� ����
	int																		SetSelectRDBIndex( unsigned int unRDBIndex );			// RDB Index ����
	void																	LoadCSV( int nCompressionMode );			// KASIM CSV������ �б�
	bool																	LoadXML( unsigned int unOfficeCode );			// KASIM XML������ �б�
	bool																	LoadXML( CPAppDataObj_Category *pCategoryInfor );			// KASIM XML������ �б�

	void																	Find_Data( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unStartID, unsigned int unCountID );			// KASIM �����͸� ã��
	void																	ReportOut_Table( unsigned int unRDBIndex, char *szTable, unsigned int unStartID, unsigned int unCountID );			// KASIM ���̺� ���� Report
	void																	ReportOut_Field( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int nStartID, unsigned int nEndID );			// KASIM �ʵ� ���� Report
	void																	ReportOut_List( unsigned int unRDBIndex, int nMode, char *szTable );			// KASIM ���� ������ Report
	CPString																ReportOut_SelectInfor();							// ���� ǥ���� KASIM RDB Index ���� Report
	unsigned int															GetTableRealCount( CPString szTableName, int nRDBIndex = 1 );		// ���̺� ���� �ǵ������� ���� ���(char Ÿ��)
	unsigned int															GetTableMaxCount( CPString szTableName );	// ���̺� ���� �ִ� ����(char Ÿ��)
	void																	GetTableNames( VECSTR &vecTableNames );			// KASIM ���̺� ��Ī ���(char Ÿ��)
	void																	GetTableFieldNames( CPString szTableName, VECSTR &vecFieldNames );			// KASIM ���̺�, �ʵ� ��Ī ���(char Ÿ��)
	void																	GetTablePosORFieldVarInfor( unsigned int unRDBIndex, bool bIsGetBuffData, CPString szTableName, VECFIELDVARINFOR &vecFieldVarInfor );			// KASIM �ʵ� ���� �� RDB Index ��ġ ���� ���

	char*																	GetText( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex );							// KASIM Data Text�� ���(char Ÿ��)
	void*																	GetData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex );							// KASIM Data ��ġ�� ���(char Ÿ��)
	void*																	GetData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement );			// KASIM Data ��ġ�� ���, �迭 ��ġ ����(char Ÿ��)
	CPString																GetData2String( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex );;		// KASIM Data ���ڿ��� ���(char Ÿ��)
	CPString																GetData2String( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement );;		// KASIM Data ���ڿ��� ���(char Ÿ��)
	double																	GetData2Double( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex );		// KASIM Data Double�� ��ġ�� ���(char Ÿ��)
	double																	GetData2Double( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement );		// KASIM Data Double�� ��ġ�� ���(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, char* szValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, short snValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, short snValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, int nValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, unsigned int unValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, unsigned int unValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, long lValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, long lValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, unsigned long ulValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, unsigned long ulValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, float fValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, float fValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, double dValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, double dValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, unsigned long long ullValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutData( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, unsigned long long ullValue );		// KASIM Data �ֱ�(char Ÿ��)
	void																	PutDouble2Data( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, double dValue );		// Double�� ���� KASIM Data �ֱ�(char Ÿ��)
	void																	PutDouble2Data( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, double dValue );		// Double�� ���� KASIM Data �ֱ�(char Ÿ��)
	void																	PutString2Data( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, char* pValue );		// ���ڿ� ���� KASIM Data �ֱ�(char Ÿ��)
	void																	PutString2Data( unsigned int unRDBIndex, char *szTable, char *szField, unsigned int unIndex, int nElement, char* pValue );		// ���ڿ� ���� KASIM Data �ֱ�(char Ÿ��)
	void																	SetTableBuffDataByKASIMRDB( unsigned int unRDBIndex, const char *szTable, const char *szField, char* pValue, unsigned int unSize );		// ���̺� KASIM RDB ������ ����

	bool																	IsFindDataViewBreak();		// KASIM Data ȭ�� ǥ��� ���� ���� ���� Ȯ��
	void																	SetFindDataViewBreak( bool bBreakValue );		// KASIM Data ȭ�� ǥ��� ���� ���� ����
	void																	MakeKASIMData( unsigned int unOfficeCode, unsigned int unRDBIndex );		// ����� �ڵ��� ���� �������Ʈ���� ���� �� ���� �����
	bool																	UpdateKASIMData( unsigned int unOfficeCode, unsigned int unRDBIndex );		// KASIM Data�� ����

	unsigned int															GetSelectOfficeIndex();		// ���� ���õ� ������ڵ� ���
	unsigned int															GetSelectCategoryKASIMRDBIndex();		// ���� ���õ� Category�� RDB Index�� ���
	void																	WriteKASIMXMLFile( unsigned int unRDBIndex, char* szFilter, bool bIsCompressAction );			// KASIM �����͸� XML ���Ϸ� ����(char Ÿ��)
	void																	WriteKASIMCSVFile( unsigned int unRDBIndex, char* szFilter, bool bIsSendReviewerMsg, bool bIsCompressAction, bool bIsLogDBUpload, bool bIsShowLogMessage );		// KASIM �����͸� CSV ���Ϸ� ����(char Ÿ��)
	void																	WriteKASIMCSVFile_MoveCompression( int nCompressionMode, CPString szSource, CPString szTarget, bool bZipSourceFileDelete );		// KASIM �����͸� CSV���Ϸ� �����ϰ� �����ϱ�
	void																	Clear_HBTableData( unsigned int unRDBIndex, char *szTableName );		// KASIM RDB ������ ����

	int																		LoadXML_KASIMSchemaData();		// KASIM XML ���� ��Ű�� �б�
	void																	LoadXML_KASIMSchemaData_Ex();		// KASIM XML ���� ��Ű�� �б�
	void																	RunLogDB_Write( CPString szBackupAPFilePath, CPString szBackupSTFilePath );		// KASIM ������ ������ �α� DB�� ����
	int																		SetCSVBackup2CompressionFile( CPString &szDUALSourcePath, CPString &szSTSourcePath, CPString &szBackupDUALPathFile, CPString &szBackupSTPathFile, bool bDeleteCompressSourceFiles );		// KASIM CSV������ �����ϰ� ���� CSV ������ ����
	int																		RunLogDB_Download_AND_UpdateKASIM();		// Log DB���� KASIM �����͸� �ٿ�ε� �ް�, KASIM�� Update ���
	void																	LoadKASIMSTLogID();							// �ֱ� ����� DB�� Study Binary �������� ��Ī
	int																		MakeOfficeKASIM( unsigned int unOfficeCode );		// ����� �ڵ忡 �ش��ϴ� KASIM ����
	void																	SetStopExportCSVWork( bool bStopValue );			// export csv ���� �۾��� ���� ���� ����
	bool																	GetStopExportCSVWork();					 // export csv ���� �۾��� ���� ���� ���� ���
	void																	SetDBLog_Delete();		// LogDB ���̺� ������ ����

// WCHAR
	unsigned int															GetTableRealCount( wchar_t *szTableName, int nRDBIndex = 1 );		// ���̺� ���� �ǵ������� ���� ���(wchar_t Ÿ��)
	unsigned int															GetTableMaxCount( wchar_t *szTableName );		// ���̺� ���� �ִ� ����(wchar_t Ÿ��)
	void																	GetTableNames( VECWSTR &vecTableNames );			// KASIM ���̺� ��Ī ���(wchar_t Ÿ��)
	void																	GetTableFieldNames( wchar_t * szTableName, VECWSTR &vecFieldNames );		// KASIM ���̺�, �ʵ� ��Ī ���(wchar_t Ÿ��)

	wchar_t*																GetText( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex );							// KASIM Data Text�� ���(wchar_t Ÿ��)
	void*																	GetData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex );							// KASIM Data ��ġ�� ���(wchar_t Ÿ��)
	void*																	GetData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement );			// KASIM Data ��ġ�� ���, �迭 ��ġ ����(wchar_t Ÿ��)
	CPString																GetData2String( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex );			// KASIM Data ���ڿ��� ���(wchar_t Ÿ��)
	CPString																GetData2String( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement );			// KASIM Data ���ڿ��� ���(wchar_t Ÿ��)
	double																	GetData2Double( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex );			// KASIM Data Double�� ��ġ�� ���(wchar_t Ÿ��)
	double																	GetData2Double( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement );			// KASIM Data Double�� ��ġ�� ���(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, wchar_t* szValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, short snValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement, short snValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement, int nValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, unsigned int unValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement, unsigned int unValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, long lValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement, long lValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, unsigned long ulValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement, unsigned long ulValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, float fValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement, float fValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, double dValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement, double dValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, unsigned long long ullValue );			// KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutData( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement, unsigned long long ullValue );			// 
	void																	PutDouble2Data( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, double dValue );			// Double�� ���� KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutDouble2Data( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement, double dValue );			// Double�� ���� KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutString2Data( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, wchar_t* pValue );			// ���ڿ� ���� KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	PutString2Data( unsigned int unRDBIndex, wchar_t *szTable, wchar_t *szField, unsigned int unIndex, int nElement, wchar_t* pValue );			// ���ڿ� ���� KASIM Data �ֱ�(wchar_t Ÿ��)
	void																	WriteKASIMXMLFile( unsigned int unRDBIndex, wchar_t* szFilter, bool bIsCompressAction );			// KASIM �����͸� XML ���Ϸ� ����(wchar_t Ÿ��)
	void																	WriteKASIMCSVFile( unsigned int unRDBIndex, wchar_t* szFilter, bool bIsSendReviewerMsg, bool bIsCompressAction, bool bIsLogDBUpload, bool bIsShowLogMessage );		// KASIM �����͸� CSV ���Ϸ� ����(wchar_t Ÿ��)

	CPString																GetKASIMVer_VerData();		// KASIM Version ���
	CPString																GetKASIMVer_LastUpdate();		// KASIM ������ ������Ʈ ��¥ ���
	CPString																GetKASIMVer_MakeBy();		// KASIM ������ ���� ���
	unsigned int															GetTableFieldVariantType( char *szTable, char *szField );		// ���̺� �� �ʵ� ��Ī�� ���� KASIM �ʵ� ���� ���� ���
	void																	SetKASIM_ASSERT_MODE( bool bMode );
	bool																	GetKASIM_ASSERT_MODE();
//	void Test_WriteDB();
	bool																	CheckThisProcessStatus();
	bool																	InitThisProcessStatus();
#ifdef DRM_MODULE_DEFINE
	void																	DoDRMKASIMInit();
	bool																	DoDRMKASIMFiles();
#endif

protected:
	void																	Clear_VarInfo();						// ��Ű�� �ʵ��� ���� ���� ����
	void																	Clear_CategoryInfo();					// ��Ű�� ������ ī�װ��� ����
	void																	Clear_SchemaMMDB();						// ��Ű�� ���� ����
	void																	Clear_OfficeCode();						// ����� ��� ���� ����
	void																	CloseWorkThread();						// �۾� ������ ����

	bool																	MakeKASIMRDB_STADYN( CPAppDataObj_Category *pCategoryData );			// KASIM RDB ����
	COfficeCodeInfor*														GetOfficeInfor( unsigned int unOfficeCode );			// ����� �ڵ� ���� ���
	void																	MakeKASIMSchema();										// ���� �������Ʈ���� ���� �� ��Ű�� �б�
	void																	MakeKASIMSchema_KASIMVer();				// KASIM Version �����
	void																	MakeKASIMSchema_KASIMSchema_Variant();			// KASIM ��Ű�� �ʵ� ���� ����
	void																	MakeKASIMSchema_KASIMSchema_TableField();			// KASIM ��Ű�� ���̺� �� �ʵ� ����
	bool																	LoadKASIMSchema();										// ���� �������Ʈ���� ���� �� ��Ű�� �б�
	CPAppDataObj_Category*													GetCategoryData( unsigned int unOfficeCode );			// ����� �ڵ��� ī�װ� ���
	void																	XMLWriteKASIMData_Version( FILE* pWriteDataFileStream );			// Write XML Version
	void																	XMLWriteKASIMData_Variant( unsigned int unRDBIndex, FILE* pWriteDataFileStream, char* szFilter, CPAppDataObj_Category* pCategoryData );		// Write XML Version
	CPString																GetMakeName_SchemaData_STA();		// KASIM Static ��Ű�� ������ ���
	CPString																GetMakeName_SchemaData_DYN();		// KASIM Dynamic ��Ű�� ������ ���

	static UINT WINAPI														ThreadWorks_WorkProcess( LPVOID pParam );		// KASIM ���� �۾� ������ �Լ�

	KASIMVER_INFOR					m_stKasimVerInfor;						// ���� �������Ʈ���� ���� �� ���� ����
	HMAP_SC_VARDATA					m_hmVarInfo;							// ���� �������Ʈ���� ���� �� �ʵ� ���� ���� ����
	HMAP_STR4UINT					m_hmSTAorDYN_Index;						// ���� �������Ʈ���� ���� ���� ���� �� ���� ���� ����
	CPAppDataObj_Category			*m_pOrderOfficeCode;					// ���õ� office code�� category ����
	HMAP_CATEGORY					m_hmCategoryInfo;						// ���� �������Ʈ���� ���� �� ��Ű�� �� ������ ����
	CFileMapObject					*m_pRSchemaData_STA, *m_pRSchemaData_DYN;	// MMDB Real Schema Static, MMDB Real Schema Dynamic

	map< unsigned int, COfficeCodeInfor* >		m_mapOfficeCode;				// ����� �ڵ�� ã������ map����

	unsigned int					m_unKasimOfficeCode, m_unKasimRdbIndex;		// ���õ� �۾� ������ڵ�, ���õ� �۾� KASIM�� RDB Index
	char							m_szGetDataTextValue[ 512 ];				// ���ڿ� ��ȯ�� ���� �Ͻ����� ����( MULTI BYTE )
	wchar_t							m_szWSGetDataTextValue[ 512 ];				// ���ڿ� ��ȯ�� ���� �Ͻ����� ����( WHCAR )
	bool							m_bFindDataViewBreak;					// ������ ã��� ������ ���� �ߴ� ����
	CPLocker						*m_pLock_OfficeLoad;					// ����ҿ� ���� KASIM Data �б��� �ߺ� ���� ����
	CPLocker						*m_pLock_DBLogDelete;					// DBLogDelete �۾��� �ߺ��� ȸ���ϱ� ���� �κ�
	CPLocker						*m_pLock_GetPutData;					// Get-Put RDB Data �ߺ� ����
	CPWThread						*m_pOfficeLoadThread;					// ����Һ� �۾� ������
	int								m_nOnlineStudyMode;							// KASIM ���� ����( 1=Online , 2=Study )
	CPString						m_szKASIMAP_WriteID, m_szKASIMST_WriteID;		// DB Upload�� ���Ǵ� DUAL ��Ī, DB Upload�� ���Ǵ� Study ��Ī
	bool							m_bStopExportCSVWork;					// export csv ���� �۾��� ���� ���� ����

	int								m_nKASIM_NULL_ReplaceValue;
	long							m_lKASIM_NULL_ReplaceValue;
	float							m_fKASIM_NULL_ReplaceValue;
	double							m_dKASIM_NULL_ReplaceValue;
	long long						m_llKASIM_NULL_ReplaceValue;
	bool							m_bKASIM_AssertMode;




};

#define								theAppDataMng							CPAppDataObjMng::InitInstance()
#define								GETTABLE_MAXCOUNT( a )					CPAppDataObjMng::InitInstance()->GetTableMaxCount( a )