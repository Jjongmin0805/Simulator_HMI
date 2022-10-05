#pragma once

// KASIM MMDB Field Ŭ����
class AFX_EXT_CLASS CPAppDataObj_Field
{
public:
	CPAppDataObj_Field( unsigned int unOfficeCode );		// KASIM MMDB Field ������
	CPAppDataObj_Field( unsigned int unOfficeCode, char* szTableName, int nIndex, char* szFieldName, int nDataTypeID, int nVarSize, int nVarCount = 1, char* szExplan = NULL, int nMaxSize = 0 );		// KASIM MMDB Field ������
	~CPAppDataObj_Field(void);		// KASIM MMDB Field �Ҹ���

	void																	ClearBuffData();		// KASIM �ʵ� Data ����
	unsigned int															GetSize_SchemaInforFIELD();		// KASIM �ʵ� ��Ű�� ������ ũ�� ���
	void																	GetData_SchemaInforFIELD( char *pSchemaData, unsigned int &unDataPosition );		// KASIM �ʵ� ��Ű�� ������ ���
	void																	SetData_SchemaInforFIELD( char *pSchemaData, unsigned int &unDataPosition, int nTableMaxRecord, bool bIsCreateBuffData );		// KASIM �ʵ� ��Ű�� ������ ����
	int																		GetIndex();		// KASIM �ʵ� Index ���
	char*																	GetName();		// KASIM �ʵ� ��Ī ���
	int																		GetVarTypeID();		// KASIM �ʵ� ����ID ���
	int																		GetVarSize();		// KASIM �ʵ� ũ�� ���
	int																		GetVarCount();		// KASIM �ʵ� ���� ���
	char*																	GetExplane();		// KASIM �ʵ� ���� ���
	unsigned int															GetVarRealSize();		// KASIM �ʵ� �ǵ����� ���� ���
	double																	PutString2Value( char* szTableName, int nIndex, int nElement, char* pValue );		// ���ڿ� ���� KASIM �����ͷ� �Է�
	double																	PutString2Value( int nIndex, int nElement, char* pValue );		// ���ڿ� ���� KASIM �����ͷ� �Է�
	void																	PutBuffData( unsigned int unIndex, int nElement, void* pValue );		// KASIM ������ �Է�
	void																	RunExtractionMMDBData( FILE* pHBDataFileStream, unsigned int &unStartPos );		// KASIM ������ ���Ϸ� ����

protected:
	void																	DeleteBuffData();		// KASIM Data ����

protected:
	unsigned int					m_unOfficeCode;							// ����� �ڵ�
	char*							m_pBuffData;							// �ǵ����� ����
	int								m_nIndex;								// �ʵ� �ε���
	char							m_szName[ 128 ];						// �ʵ� ��Ī
	short							m_snVarTypeID;							// �ʵ� ����Ÿ�� id
	int								m_nVarSize;								// �ʵ� ����Ÿ�� ������
	int								m_nVarCount;							// �ʵ� ���� �迭 ����
	char							m_szExplane[ 512 ];						// �ʵ� ���� ��Ī
	int								m_nTableMaxRecordSize;					// ���̺� ���ڵ� �Ѱ���
};

typedef hash_map< string, CPAppDataObj_Field* >							HMAP_FIELD;
typedef hash_map< int, CPAppDataObj_Field* >							HMAP_INDEXFIELD;
typedef map< int, CPAppDataObj_Field* >									MAP_INDEXFIELD;
typedef vector< CPAppDataObj_Field* >									VEC_INDEXFIELD;
