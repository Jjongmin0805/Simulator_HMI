#pragma once

#include <string>
#include <vector>
#include <map>
using namespace std;

#ifdef UPC_DLL_EXPORTS
#define UPC_Export __declspec(dllexport)
#else
#define UPC_Export __declspec(dllimport)
#endif

typedef struct stSubType_
{
	string				type_name;
	string				unit_name;
	unsigned int		arr_count;
	unsigned int		type_size;
}stSubType;


typedef enum _eTypeValue
{
	UPC_NONE_TYPE = 0,
	UPC_BYTE_TYPE,
	UPC_CHAR_TYPE,
	UPC_WCHAR_TYPE,
	UPC_WORD_TYPE,
	UPC_UN_WORD_TYPE,
	UPC_FLOAT_TYPE,
	UPC_DOUBLE_TYPE,
	UPC_INT_TYPE,
	UPC_UN_INT_TYPE,
	UPC_LONG_TYPE,
	UPC_UN_LONG_TYPE,
	UPC_TIME_TYPE,
	UPC_TIME64_TYPE,
	UPC_USERDEF_TYPE
}eTypeValue;


class UPC_Export uPCDataType
{
public:
	typedef vector<stSubType*> TYPEVECTOR;

public:
	uPCDataType();
	uPCDataType(string szTypeName);
	uPCDataType(string szTypeName, unsigned int nTypeSize);
	~uPCDataType(void);

	void AddSubType(stSubType* sub_type);
	void AddSubType(string szSubTypeName, string szSubUnitName, unsigned int nSubTypeSize, unsigned int nArrCount = 1);


	TYPEVECTOR* GetArrSubType(){ return &arrSubType_; }

	int GetTypeSize();
	string GetTypeName();


	int GetIndexOfUnitName(const char* szUnitName, int arr_index = 0);// GetPosOfUnitName;
	int GetSizeOfUnitName(const char* szUnitName, int& nSize);
	int GetSizeOfUnitName(const char* szUnitName);
	int GetArrCountOfUnitName(const char* szUnitName);
	int GetSubTypeCount();
	int GetTypeNameOfUnitName(const char* szUnitName, string& szTypeName);
	int GetTypeNameOfUnitName(const char* szUnitName, char* szTypeName);
	int GetSubTypeOfUnitName(const char* szUnitName, stSubType& sub_type);

	int GetTypeValueOfUnitName(const char* szUnitName);

	void SubTypeReserve(int nCount);

	const char*		GetFieldName(int index);
	const char*		GetTypeName(int index);
	eTypeValue		GetTypeValue(int index);
	int				GetArrayCount(int index);

	void SetTypeSize(unsigned int type_size);
	int SetTypeName(/*const char* */string szTypeName);
	int GetTypeValue();
	static int GetTypeValue(string type_name);
private:
	string				szTypeName_;
	unsigned int		nTypeSize_;
	TYPEVECTOR			arrSubType_;

};



