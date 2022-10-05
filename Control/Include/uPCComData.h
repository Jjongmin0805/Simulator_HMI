#pragma once

#include "uPCDataStore.h"
#include "uPCTypeDefC.h"

#ifdef UPC_DLL_EXPORTS
#define UPC_Export __declspec(dllexport)
#else
#define UPC_Export __declspec(dllimport)
#endif

class uPCDataType;
class uPCDataStore;

class UPC_Export uPCComData
{
public:
	uPCComData(void);
	uPCComData(int nDataSize);
	uPCComData(const char* pTypeName,int nValueKind);
	~uPCComData();
	//uPCComData(const uPCComData& rhs);

	//uPCComData& operator = (const uPCComData& rhs);


	int SetDataType(const char* pTypeName);
	int SetDataType(uPCDataType* pTypeName);
	void SwellSetDataType(uPCDataType* pTypeName);

	void*			GetValue(const char* szUnitName);
	void*			GetValue(int index);
	void*			GetValue(const char* szUnitName, int& nSize);

	void*			U_GetValue(const char* szUnitName);
	void*			U_GetValue(int index);
	void*			U_GetValue(const char* szUnitName, int& nSize);


	int				GetValue(const char* szUnitName, uPCComData& com_data);

	int				PutValue(const char* szUnitName, unsigned int uiValue);
	int				PutValue(const char* szUnitName, int iValue);
	int				PutValue(const char* szUnitName, unsigned short usValue);
	int				PutValue(const char* szUnitName, short sValue);
	int				PutValue(const char* szUnitName, unsigned char usValue);
	int				PutValue(const char* szUnitName, char sValue);
	int				PutValue(const char* szUnitName, const char* pArray);
	int				PutValue(const char* szUnitName, const wchar_t* pArray);
	int				PutValue(const char* szUnitName, float fValue);
	int				PutValue(const char* szUnitName, double fValue);

	// 2013년 12월 30일
	int				PutValue(unsigned int uiValue);
	int				PutValue(int iValue);
	int				PutValue(unsigned short sValue);
	int				PutValue(short sValue);
	int				PutValue(unsigned char usValue);
	int				PutValue(char usValue);
	int				PutValue(const char* pArray);
	int				PutValue(const wchar_t* pArray);
	int				PutValue(float fValue);
	int				PutValue(double fValue);

	// 2013년 12월 23일
	int				PutValue(const char* szUnitName, const char* pData, int nSize);
	int				PutValue(const char* szUnitName, uPCComData& obj);

	bool			IsGood();

	int				SetDataBuffer(const  char* buffer , unsigned int bufsize);
	int				CopyDataBuffer(const  char* buffer , unsigned int bufsize);
	int				SwellSetRawValue(char* pBuffer,int nSize);

	uPCDataType*	GetDataType();

	char*			get_buffer();
	unsigned int	get_size();
	void			set_size(const unsigned int size);

	uPCDataStore*	GetDataStore();

	char*			GetTypeName();

	void			SetTypeName(const char* strTypeName);
	
	int				GetPosOfUnitName(string szUnitName);
	int				GetPosOfUnitName(string szUnitName, int& nSize);

private:
	uPCDataType*			data_type_;
	char					szTypeName_[TYPE_NAME_SZ];
	uPCDataStore			data_store_;
};

//typedef map<std::string, uPCComData*> COMDATAMAP;