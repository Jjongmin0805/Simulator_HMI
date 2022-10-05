#ifndef __POWER_MANAGEMENT_SYSTEM_DEFINE_H__
#define __POWER_MANAGEMENT_SYSTEM_DEFINE_H__

#include "sys_types.h"

#define MRID_MAX_SZ			64
#define NAME_MAX_SZ			64
#define LNAME_MAX_SZ		64
#define PNAME_MAX_SZ		128
#define ANAME_MAX_SZ		64
#define DESC_MAX_SZ			128
#define MESHCODE_MAX_SZ		12
#define IPADDR_MAX_SZ		16
#define OPER_CODE_MAX_SZ	8
#define PASSWORD_MAX_SZ		16

#define	REC_MAX_ProcInfo				256

/* NAME SIZE */
#define ERRORDESC_NAME_MAX_SZ			32
#define WAVEFILE_NAME_MAX_SZ			16

#define MAX_PROC_NAME_SZ	32
#define MAX_SERVICE_NAME_SZ	64

typedef struct tagTypeString
{
	DT_INT			nTypeNo;
	const DT_CHAR	*TypeName;
} TypeString ;

#define PID_UNKNOWN			0
#define PID_DMSROOT			1
#define PID_HAMD			2
#define PID_HMIMD			3
#define PID_FEPMD			4
#define PID_RTMD			5
#define PID_AEMD			6
#define PID_RGSMD			7
#define PID_RTCMD			8
#define PID_LOGMD			9
#define PID_NETGEN			10
#define PID_TDASMD			11
#define PID_SLSMD			12
#define PID_LGEMSMD			13
#define PID_TIMESYNC		14
#define PID_RESERVED		15

#endif	/* __POWER_MANAGEMENT_SYSTEM_DEFINE_H__ */