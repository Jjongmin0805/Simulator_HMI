#pragma once
#ifndef __HMIRDBSTRUCT_H__
#define __HMIRDBSTRUCT_H__

#ifndef __HMICONST_H__
#include "HMIConst.h"
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
/////////////////////////////////////////////////////////////////////////////
//  ini structure
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  hmiproject, diProperty, aiProperty 구조체
/////////////////////////////////////////////////////////////////////////////
// HCI Project 일반 정보
//#pragma pack(1)

#pragma pack()
#endif	//__HCISTRUCT_H__