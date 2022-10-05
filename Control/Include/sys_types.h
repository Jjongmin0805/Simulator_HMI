#ifndef	__POWER_MANAGEMENT_SYSTEM_TYPES_H__
#define __POWER_MANAGEMENT_SYSTEM_TYPES_H__

#ifndef __cplusplus
typedef boolean			DT_BOOL;
#else
typedef unsigned char	DT_BOOL;
#endif

typedef unsigned char		DT_BYTE;
typedef	         char		DT_CHAR;
typedef unsigned char		DT_UCHAR;
typedef	         short		DT_SHORT;
typedef unsigned short		DT_USHORT;
typedef unsigned short		DT_WORD;
typedef	         int		DT_INT;
typedef unsigned int		DT_UINT;
typedef	         long		DT_LONG;
typedef	         long		DT_LONG32;
typedef	         long long	DT_LONG63;
typedef unsigned long		DT_ULONG;
typedef unsigned long		DT_ULONG32;
typedef unsigned long long	DT_ULONG64;
typedef unsigned long		DT_DWORD;
//typedef          float		DT_FLOAT;
typedef          double		DT_DOUBLE;
typedef          void		DT_VOID;

/// 함수실행 결과
#define RET_SUCCESS			0
#define RET_ERROR			1

#define	FILENAME_MAX_SZ		32
#endif	/* __POWER_MANAGEMENT_SYSTEM_TYPES_H__ */