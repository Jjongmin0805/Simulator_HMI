#ifndef __UPC_TYPE_DEF_H__
#define __UPC_TYPE_DEF_H__

#include "uPCTypeDefC.h"

#define PDB_NAME32_SZ                       (32)
#define PDB_USERID_SZ						(32)
#define ALARM_MSG_SZ						(128)

#define POINT_NAME_SZ						(64)
//#define TYPE_NAME_SZ						(64)
#define SERVICE_NAME_SZ						(64)
#define UNIT_NAME_SZ						(64)
#define ORB_PARAM_STR_SZ					(128)

#define MAX_DEF_POINT_CNT					(100)
#define MAX_DEF_TYPE_CNT					(500)
#define MAX_DATA_POINT_CNT					(100)

#define ADDR_STR_SZ							(32)


#ifndef ushort
#define ushort	unsigned short
#endif

#ifndef uint
#define uint	unsigned int
#endif

#ifndef ulong
#define ulong	unsigned long
#endif

typedef enum _uPCDeplexMode_e
{
	UPC_DM_NONE		=0x0000
	, UPC_DM_SINGLE = 0x0001
	, UPC_DM_DEPLEX = 0x0002
}uPCDeplexMode_e;

typedef enum _uPCDeplexStatus_e
{
	UPC_DS_NONE		=0x0000
	, UPC_DS_ACTIVE = 0x0001
	, UPC_DS_STANDBY = 0x0002
}uPCDeplexStatus_e;

typedef enum _uPCExcuteStatus_e
{
	UPC_ES_NONE		=0x0000
	, UPC_ES_INIT = 0x0001
	, UPC_ES_SWITCH = 0x0002
	, UPC_ES_TAKEOVER = 0x0003
	, UPC_ES_ONLINE = 0x0004
}uPCExcuteStatus_e;


typedef enum _uPCServiceStatus_e
{
	UPC_SS_ACTIVE_ONLINE		=0x0000
	, UPC_SS_ACTIVE_SWITCH = 0x0001
	, UPC_SS_ACTIVE_INIT = 0x0002
	, UPC_SS_ACTIVE_NONE = 0x0003
	, UPC_SS_STANDBY_ONLINE = 0x0004
	, UPC_SS_STANDBY_SWITCH = 0x0005
	, UPC_SS_STANDBY_INIT = 0x0006
	, UPC_SS_STANDBY_NONE = 0x0007
}uPCServiceStatus_e;


//< 서비스 상태정보 구조체
typedef struct _uPCServiceInfo_st
{
	int office_code;
 	int major;
 	int minor;
	char node_name[64];
	char service_name[64];
	uPCDeplexMode_e deplex_mode;
	uPCDeplexStatus_e deplex_status;
	uPCExcuteStatus_e execute_status;
	unsigned int service_start_count[NO_ALL_SERVICE];
}uPCServiceInfo_st;


typedef enum _ePoint_Kind
{
	PK_TP = 0x01,
	PK_DP,
	PK_MP,
	PK_EP,
	PK_CP,
	PK_AP

}ePoint_Kind;


//< 포인트(비동기, 이벤트...)들의 상태정보 구조체
typedef struct _uPCPointInfo_st
{
	char			point_name[SERVICE_NAME_SZ];
	int				total_data_count;
	int				current_data_count;
	int				point_kind;
	unsigned char	point_usage; //메시지 큐 사용 여부 셋팅 0:disable 1:enable
	unsigned int	create_time;
	unsigned int	reference_time;
	unsigned int	push_time;
	unsigned int	pull_time;

}uPCPointInfo_st;


#endif