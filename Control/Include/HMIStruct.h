#pragma once
#ifndef __HMISTRUCT_H__
#define __HMISTRUCT_H__

#ifndef __HMICONST_H__
#include "HMIConst.h"
#endif

#ifndef __RDBFILEDEF_H__
#include "RDBFileDef.h"
#endif

#ifndef __RDBSTRUCT_H__
#include "RDBStruct.h"
#endif



#ifdef WIN64
#define DT_FLOAT	double
#else
#define DT_FLOAT	float
#endif
/////////////////////////////////////////////////////////////////////////////

#pragma pack(1)


typedef struct __stVoid__
{
	long pid;
	void* pv;
} ST_VOID, *LPST_VOID;
//#pragma pack(1)

#endif	//__HCISTRUCT_H__