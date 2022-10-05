#pragma once


//#import <msxml3.dll>
//using namespace MSXML2;

#include "Markup.h"
#include "CSB_Object.h"

#define					SYMBOL_MENU_ID_CONNECT		41000
#define					SYMBOL_MENU_ID_TEXT			42000
#define					SYMBOL_MENU_ID_FIRST		40000
#define					SYMBOL_MENU_ID_LAST			SYMBOL_MENU_ID_FIRST + 100

class AFX_EXT_CLASS CSB_Manager
{
public:
	CSB_Manager(void);
	~CSB_Manager(void);

private:
	static CSB_Manager* _instance;// ½Ì±ÛÅæ(Singleton) - ¸Þ¸ð¸®¿¡ ÇÑ¹ø¸¸ ¶ç¿ò
public:
	static CSB_Manager* Instance();


	CString			MyPath();
	
	BOOL							Read_SB_File();

	void							Set_MenuID();
	void							SetMenu(CMenu* pMenu);

	CSB_Object*						GetBlock_SB(int nDevref);
	CSB_Object*						GetBlock_SB2ResourceID(int nResouceID);

	CSB_ObjectArray					m_Array_SB;

	void							test_Draw(Graphics &graphics,CRect rClient);
};

