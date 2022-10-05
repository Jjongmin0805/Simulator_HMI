#pragma once
#ifndef __RDBSTRUCT_H__
#define __RDBSTRUCT_H__

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
// RDBStruct.h:  RDB에서 사용되는 Share Memory 구조체를 정의
//------------------------------------------------------------------------------
typedef struct __ENV_RDB__				
{
	TCHAR	tRdbFileName[64];
	LONG	tRdbItemCnt;
} ST_ENV_RDB, *LPST_ENV_RDB;

#define RDB_NAME4_SZ						(4)
#define RDB_NAME16_SZ						(16)
#define RDB_NAME32_SZ						(32)
#define RDB_NAME40_SZ						(40)
#define RDB_NAME64_SZ						(64)
#define RDB_NAME128_SZ						(128)
#define RDB_NAME256_SZ						(256)

#define RDB_NAME20_SZ						(20)
#define RDB_MESH22_SZ						(22)
#define RDB_DATETIME25_SZ					(25)
#define RDB_CONTENT256_SZ					(256)
#define RDB_CONTENT512_SZ					(512)

#include	<string>
#include	<vector>
#include	<list>
#include	<map>

#ifdef WIN64
#define DT_FLOAT	double
#else
#define DT_FLOAT	float
#endif

using namespace std;

#pragma pack(1)
typedef std::map<int, void*>	  atlMap;

// 공유메모리 관리에 필요한 메모리 
typedef struct __stHMIProject__		
{
	ST_ENV_RDB tItemCnt[2000];	/* 공유메모리 테이블의 이름과 레코드수 저장 */

} ST_HMI_PROJECT, *LPST_HMI_PROJECT;

//CIM에서 공통되는 정보관리
typedef struct __stCommonIdentifiedObject__		
{
	TCHAR	MRID[RDB_NAME64_SZ];					/*mRID				*/	
	//TCHAR	name[RDB_NAME64_SZ];					/*이름				*/	
	TCHAR	aliasName[RDB_NAME64_SZ];				/*별칭				*/
	TCHAR	localName[RDB_NAME64_SZ];				/*지역이름			*/
	TCHAR	pathName[RDB_NAME128_SZ];				/*경로이름			*/
	TCHAR	description[RDB_NAME128_SZ];			/*설명				*/

} ST_COMMON_IDENTIFIEDOBJECT, *LPST_COMMON_IDENTIFIEDOBJECT;


// 본부(지사)
typedef struct __stCommonGeographicalRegion__		
{
	INT		GGRID;								/*GGR ID			*/	
	TCHAR	mRIDFK[RDB_NAME64_SZ];				/*mRID ID			*/
	TCHAR	Name[RDB_NAME64_SZ];				/*본부(지사) 명    	*/
	INT		GGRCode;							/*본부코드			*/

} ST_COMMON_GEOGRAPHICALREGION, *LPST_COMMON_GEOGRAPHICALREGION;

//// 지점(예하사업소)
typedef struct __stCommonSubGeographicalRegion__		
{
	INT		SGRID;								/*SGR ID			*/	
	INT		GGRFK;								/*GGR ID			*/	
	TCHAR	mRIDFK[RDB_NAME64_SZ];				/*mRID ID			*/
	TCHAR	Name[RDB_NAME64_SZ];				/*지점 명	    	*/
	INT		SGRCode;							/*지점코드			*/
	INT		DPGC_ACMFK;

} ST_COMMON_SUBGEOGRAPHICALREGION, *LPST_COMMON_SUBGEOGRAPHICALREGION;

//// 시스템내 DataPoint 구성을 위한 테이블
typedef struct __stCommonDataPointGroupCode__		
{
	INT		DpGrpId;							/*SGR ID			*/	
	TCHAR	DpGrpName[RDB_NAME64_SZ];			/*시스템 소속 분류	*/
												/* 배전선로(1), 발변전소(2), 분산전원(3), 전력량계(4), 수요관리(5), TDAS(6), SCADA(7), 계산관리(8), 시스템(9) */
	TCHAR	DpGrpCode[RDB_NAME64_SZ];			/*데이터포인트 코드	*/
	TCHAR	DpPrefixName[RDB_NAME32_SZ];		/*데이터포인트 Prefix 이름 */

} ST_COMMON_DATAPOINTGROUPCODE, *LPST_COMMON_DATAPOINTGROUPCODE;

//// 컴퓨터(시스템) 관리 테이블
typedef struct __stCommonComputerode__		
{
	INT		ComputerId;									 /*컴퓨터 ID			*/	
	TCHAR	ComputerName[RDB_NAME64_SZ];				 /*서버장치 이름			*/
	CHAR	ComputerType; 								 /*장치종류 */
	SHORT	PORT;										 /*이중화 구현시 상호 통신포트 */
	CHAR	PRIORITY;									 /*이중화 구현시 실행우선 순서 (1=Active, 2=Standby)	UINT	MSINGLE;										 /*단독실행 유무(0=False, 1=True) */
	CHAR	MSINGLE;
	CHAR	OFFLINE;									 /*실행유무 결정(0=실행안함, 1=실행) */
	INT		DpGrpFK;									 /*데이터포인트 코드	*/
	TCHAR	IP_Addr[RDB_NAME16_SZ];    

} ST_COMMON_COMPUTERCODE, *LPST_COMMON_COMPUTERCODE;

//// 프로그램 관리 테이블        
typedef struct __stCommonProgramCode__		
{       
	INT		ProgId;       							     /*프로그램Id */	
	INT		ComputerId;									 /*ComputerCode와 연결되며, 프로그램이 구동될 컴퓨터 Id */
	TCHAR	ProgName[RDB_NAME64_SZ];     				 /*장치내 실행될 .exe 파일 이름 */
	TCHAR	ServiceName[RDB_NAME64_SZ];					 /*장치내 실행될 서비스 프로그램 이름 */
	CHAR	ProgLevel;									 /*프로그램 그룹(1=core, 2=base, 3=Application Level)*/
	CHAR	RunNode;									 /*실행 대상 설비	*/
	CHAR	AutoRestart;								 /*프로그램 장애시 재실행 설정(0=No Restart, 1=Restart) */

} ST_COMMON_PROGRAMCODE, *LPST_COMMON_PROGRAMCODE;

//// 사령원 관리 테이블       
typedef struct __stCommonOperatorCode__		
{       
	INT		OperId;                            /*사령원 코드 */	
	TCHAR	OperNum[RDB_NAME16_SZ];            /*사령원 사번*/	
	TCHAR	OperName[RDB_NAME32_SZ];           /*사령원 이름 */	
    TCHAR	OperPasswd[RDB_NAME16_SZ];         /*사령원 암호(암호화) */	
    CHAR	ConAuth;                           /*제어권한 (0=제어권한 없음, 1=제어가능) */

} ST_COMMON_OPERATORCODE, *LPST_COMMON_OPERATORCODE;

//// 스위치 구분 코드       
typedef struct __stCommonSwitchTypeCode__		
{       
	INT		TypeID;                            /*스위치 구분 ID */	
	TCHAR	Name[RDB_NAME64_SZ];               /*스위치 종류 명(Normal, Section, Tie, Terminal 등) */	

} ST_COMMON_SWITCHTYPECODE, *LPST_COMMON_SWITCHTYPECODE;

//// 작업종류 테이블      
typedef struct __stCommonConstructionTypeCode__		
{       
	INT		ConstId;                           /*작업종류 ID */	
	TCHAR	Consttype[RDB_NAME64_SZ];          /*공사용개페기, 무정전변압기, 바이패스공법, 무정전전선이선공법 등 */	

} ST_COMMON_CONSTRUCTIONCODE, *LPST_COMMON_CONSTRUCTIONCODE;

//// 파형정보 타입     
typedef struct __stCommonWaveComType__		
{       
	INT		wavecomTypetId;                          /*파형타입 ID */	
	TCHAR	ComtypeName[RDB_NAME64_SZ];				 /*1:기존 DNP 통신, 2:지능형(KDN) DNP+FTP, 3:인텍 FTP */

} ST_COMMON_WAVECOMTYPE, *LPST_COMMON_WAVECOMTYPE;

//// 상태값에 대한 표시 그룹  
typedef struct __stCommonStateGroup__		
{       
	INT		StateGrpId;                             /*상태 그룹 ID */	
	TCHAR	Name[RDB_NAME64_SZ];					/*상태 이름 */	
	SHORT	Count;									/*상태 수량 */	

} ST_COMMON_STATEGROUP, *LPST_COMMON_STATEGROUP;

//// 인덱스별 데이터 형식  
typedef struct __stCommonDataByte__		
{       
	INT		DataByteId;                   /*데이터형식 ID */	
	TCHAR	Name[RDB_NAME64_SZ];          /*인덱스 이름 */
	CHAR	Sign;						  /*부호표시 0: Unsigned, 1: Signed */
	CHAR	Size;						  /*DATABYTE 크기 */

} ST_COMMON_DATABYTE, *LPST_COMMON_DATABYTE;

//// 상태값에 대한 정의 테이블
typedef struct __stCommonStateSet__		
{       
	INT		StateSetId;                    /*상태그룹 ID */
	TCHAR	Name[RDB_NAME64_SZ];          /*상태이름(한글)*/
	UCHAR	Value;                         /*취득 상태값 */
	INT		StateGrpId;                    /*상태그룹 ID */    
} ST_COMMON_STATESET, *LPST_COMMON_STATESET;

//// 계측 표시 단위
typedef struct __stCommonUnit__		
{       
	INT		UnitId;							/*단위 ID */
	TCHAR	UnitName[RDB_NAME64_SZ];		/*단위 이름*/

} ST_COMMON_UNIT, *LPST_COMMON_UNIT;

//// 계측값 단위표시용 값
typedef struct __stCommonScalefactor__		
{       
	INT		sfid;                         /*단위 ID */
	TCHAR	Name[RDB_NAME64_SZ];          /*단위 이름*/
	FLOAT	Scale;                        /* 스케일 */
	FLOAT	Offset;                       /* 기준값 */

} ST_COMMON_SCALEFACTOR, *LPST_COMMON_SCALEFACTOR;

//// 상하한치 정의
typedef struct __stCommonLimitCode__		
{       
	INT		LimitId;                      /*Limit ID */
	INT		LimitSetId;                   /*LimitSet ID */
	TCHAR	Name[RDB_NAME64_SZ];          /*Limit 이름*/
	FLOAT	Val;                          /*기준값 */
	CHAR	Limittype;                    /*상한치,하한치 구분 0=하한치, 1=상한치 */

} ST_COMMON_LIMITCODE, *LPST_COMMON_LIMITCODE;

//// 상하한치 정의
typedef struct __stCommonLimitSet__		
{       
	INT		LimitSetId;                   /*LimitSet ID */
	TCHAR	Name[RDB_NAME64_SZ];          /*LimitSet 이름*/

} ST_COMMON_LIMITSET, *LPST_COMMON_LIMITSET;

//// 기기 제작사명 테이블
typedef struct __stCommonEquipCompany__		
{       
	INT		CompanyId;                   /*Company ID */
	TCHAR	CompanyName[RDB_NAME64_SZ];  /*Company 이름*/

} ST_COMMON_EQUIPCOMPANY, *LPST_COMMON_EQUIPCOMPANY;

//// 변전소 관리 테이블
typedef struct __stCommonSubstation__		
{       
	INT		SSID;                       /*Company ID */
	INT		SGRFK;                      /*Company 이름*/
	INT		EQCFK;                      /*EquipmentContainer */
	TCHAR	mRIDFK[RDB_NAME64_SZ];      /*mRIDFK */
	TCHAR	Name[RDB_NAME64_SZ];        /*변전소 명 */
	INT		PSRFK;						/*PSR ID */
	INT		SSCode;						/*변전소 코드 */
	INT		DPGC_ACMFK;

} ST_COMMON_SUBSTATION, *LPST_COMMON_SUBSTATION;

//// 배전 회선
typedef struct __stCommonDistributionLine__		
{       
	INT		 DLID;                      /*DL ID */
	INT		 SSFK;                      /*변전소 ID*/
	INT		 MTRFK;                     /*Main Transformer */
	INT		 EQCFK;                     /*Equipment Container ID */
	TCHAR	 mRIDFK[RDB_NAME64_SZ];     /*mRIDFK */
	TCHAR	 Name[RDB_NAME64_SZ];       /*DL 명 */
	INT		 dl_no;                     /*TDAS의 고유 DL 번호 */
	SHORT	 reliability;               /*신뢰도*/
	SHORT	 priority;                  /*우선순위 */
	FLOAT	 rated_S;                   /*회선별 기준용량*/
	INT		 RATED_S_USFK;              /*회선별 기준용량 단위 */
	INT		 DPGC_ACMFK;				/*ACM관련 FK */ 

} ST_COMMON_DISTRIBUTIONLINE, *LPST_COMMON_DISTRIBUTIONLINE;

//// 기준전압
typedef struct __stCommonBaseVoltage__		
{       
	INT      BVID;                      /*BV ID */
	TCHAR    mRIDFK[RDB_NAME64_SZ];     /*mRIDFK */
	TCHAR    Name[RDB_NAME64_SZ];       /*기준전압명 */
	FLOAT    NominalVoltage;            /*기준전압, 공칭전압값 */
	INT		 NominalVoltage_usfk;       /*단위 */
	FLOAT    MaxVoltage;                /*최고전압값 */
	INT      MaxVoltage_usfk;           /*단위 */

} ST_COMMON_BASEVOLTAGE, *LPST_COMMON_BASEVOLTAGE;

//// 기준전력
typedef struct __stCommonBasePower__		
{       
	INT		BPID;						/*BP ID */
	TCHAR	Name[RDB_NAME64_SZ];		/*기준전력명 */
	TCHAR	mRIDFK[RDB_NAME64_SZ];		/*mRIDFK */
	INT		basePower;					/*기준전력 */
	INT		basePower_usfk;				/*단위 */

} ST_COMMON_BASEPOWER, *LPST_COMMON_BASEPOWER;

//// 전압레벨
typedef struct __stCommonVoltageLevel__		
{       
	INT		VLID;                      /*VL ID */
	INT		SSFK;                      /*변전소 ID */
	INT		BVFK;                      /*기준전압 ID */
	INT		EQCFK;                     /*Equipment Container ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];     /*mRIDFK */
	TCHAR	Name[RDB_NAME64_SZ];       /*전압레벨명 */
	FLOAT	highVoltageLim;            /*busbar 전압 상한*/
	INT		highVoltageLim_usfk;       /*단위 */
	FLOAT	lowVoltageLim;             /*busbar 전압 하한 */
	INT		lowVoltageLim_usfk;        /*단위 */	
	INT		PSRFK;					   /*PowerSystemResource */

} ST_COMMON_VOLTAGELEVEL, *LPST_COMMON_VOLTAGELEVEL;

//// 상 관리 테이블
typedef struct __stCommonPhase__		
{       
	UINT	PhaseID;                      /*Phase ID */
	TCHAR	PhaseName[RDB_NAME64_SZ];     /*Phase 명 */
	TCHAR	Phase[RDB_NAME64_SZ];         /*ABCN, ABC, ABN, ACN, BCN, A, B, C등 */

} ST_COMMON_PHASE, *LPST_COMMON_PHASE;

//// 프로토콜 타입 테이블
typedef struct __stCommonProtocolType__		
{       
	INT		ProtocolTypeId;                /*Protocol ID */
	TCHAR	ProtocolName[RDB_NAME64_SZ];   /*Protocol 명 수동/KODAS/MODBUS/DNP/IEC61850 */
	TCHAR	ProtocolKind[RDB_NAME32_SZ];   /*Protocol 명 FEP에서 사용 */

} ST_COMMON_PROTOCOLTYPE, *LPST_COMMON_PROTOCOLTYPE;

//// 장치종류 타입 테이블
typedef struct __stCommonEquipmentType__		
{       
	INT		EquipTypeId;						/*EquipType ID */
	TCHAR	EquipTypeCode[RDB_NAME64_SZ];		/*장치종류(영문)*/
	TCHAR	EquipTypeDesc[RDB_NAME64_SZ];       /*장치종류(한글) */

} ST_COMMON_EQUIPMENTTYPE, *LPST_COMMON_EQUIPMENTTYPE;

//// RTU Map Index 종류
typedef struct __stCommonRTUMap__		
{       
	UINT	RTUMapId;							 /*RTUMAP ID */
	TCHAR	RTUMapName[RDB_NAME64_SZ];			 /*RTUMAP 이름*/
	TCHAR	DMSName[RDB_NAME64_SZ];				 /*DMS 이름*/
	UINT	RTUTypeId;							 /*RTU TYPE ID) */
	TCHAR	UPC_TypeName[RDB_NAME64_SZ];         /*미들웨어 사용이름 */
	TCHAR	RTUKind[RDB_NAME32_SZ];				 /*FEP 사용이름 */

} ST_COMMON_RTUMAP, *LPST_COMMON_RTUMAP;

////통신 종류 코드
typedef struct __stCommonCommType__		
{       
	INT		CommTypeId;                        /*통신종류 ID */
	TCHAR	ConmmTypeName[RDB_NAME64_SZ];      /*통신종류명 연결안됨/유선/광/에어미디어/PCS_DT1800/KTS216/인텍/TRS/CDMA/광(LIU)/TCPIP */
	TCHAR	ConmmKind[RDB_NAME32_SZ];		   /*FEP에서 쓰는 약어 */	

} ST_COMMON_COMMTYPE, *LPST_COMMON_COMMTYPE;

//// RTU 종류 코드
typedef struct __stCommonRTUType__		
{       
	INT		RTUTypeId;						  /*RTU종류 ID */
	TCHAR	RTUTypeName[RDB_NAME64_SZ];       /*Manual/FRTU/FIED/AMIGW/FRTU(60870) */

} ST_COMMON_RTUTYPE, *LPST_COMMON_RTUTYPE;

//// HMI 뷰 UI에서 Subtab 구분자
typedef struct __stCommonCategoryCode__		
{       
	INT		CCID;								/*카테고리 ID */
	SHORT	CCDType;							/*선로운영, 본체고장, 섹션, PQM, 비접지 고장, 통신, 운영, 기준  */
	TCHAR   Name[RDB_NAME64_SZ];				/*카테고리명 */

} ST_COMMON_CATEGORYCODE, *LPST_COMMON_CATEGORYCODE;

//// 포인트 종류
typedef struct __stCommonMeasureTypeInfo__		
{       
	INT		MeasureTypeID;                 /*포인트종류 ID */
	TCHAR	Name[RDB_NAME64_SZ];           /*포인트종류 명  */
	CHAR	PointType;				       /*포인트종류  BI, BO, AI, AO, Count */
	INT		CCDFK;						   /*카테고리 ID FK */

} ST_COMMON_MEASURETYPEINFO, *LPST_COMMON_MEASURETYPEINFO;

//// BI 맵 인덱스
typedef struct __stCommonDNPBIMapIndex__		
{       
	INT		MapId;							/*맵 ID */
	INT		RTUMapId;						/*RTU맵 ID */
	INT		StateGrpId;						/*StateGroup의 StateGrpId */
	INT		MeasureTypeID;					/*포인트 구분 코드K */
	SHORT	Position;						/*BI_Index */
	SHORT	BO_Position;					/*BO_Index  */
	TCHAR	IndexName[RDB_NAME64_SZ];		/*Index 명 */
	CHAR	CircuitNo;						/*회로번호 */	
	CHAR	NormalValue;					/*정상값 */	
	CHAR	AbnormalValue;					/*비정상값 */	
	TCHAR	Obj_Var[RDB_NAME32_SZ];			/*Object/Variation */	
	CHAR	Class;							/*Class 번호 */	
	CHAR	EMS;							/*EMS 계측 유무 */	
	TCHAR	upc_name[RDB_NAME64_SZ];		/*Value에 대한 MW 데이터 타입 필드 명 */	
	TCHAR	upc_tlq[RDB_NAME64_SZ];			/*TLQ에 대한 MW 데이터 타입 필드 명 */	
	TCHAR	upc_uptime[RDB_NAME64_SZ];		/*업데이트타임에 대한 MW 데이터 타입 필드 명 */	
	CHAR	Alarm;							/* 알람 유무 */	
	CHAR	Important;						/*중요/비중요 알람 결정 0=이벤트 전용, 1=중요 알람 */		
	CHAR	Terminal_DI;					/*1=전원측, 2=부하측*/	  

} ST_COMMON_DNPBIMAPINDEX, *LPST_COMMON_DNPBIMAPINDEX;

//// BO 맵 인덱스
typedef struct __stCommonDNPBOMapIndex__		
{       
	INT		MapId;							/*맵 ID */
	INT		RTUMapId;						/*RTU맵 ID */
	INT		StateGrpId;						/*StateGroup의 StateGrpId */
	INT		MeasureTypeID;					/*포인트 구분 코드K */
	SHORT	Position;						/*BI_Index  */
	TCHAR	IndexName[RDB_NAME64_SZ];		/*Index 명 */
	CHAR	CircuitNo;						/*회로번호 */	
	TCHAR	Obj_Var[RDB_NAME32_SZ];			/*Object/Variation */	
	CHAR	Class;							/*Class 번호 */	
	CHAR	EMS;							/*EMS 계측 유무 */	
	INT		CCId;							/*ControlCode의 CCID */
	SHORT	RelayOnTime;					/*Puls 제어 On 시간(ms) */
	TCHAR	upc_name[RDB_NAME64_SZ];		/*Value에 대한 MW 데이터 타입 필드 명 */	
	TCHAR	upc_tlq[RDB_NAME64_SZ];			/*TLQ에 대한 MW 데이터 타입 필드 명 */	
	TCHAR	upc_uptime[RDB_NAME64_SZ];		/*업데이트타임에 대한 MW 데이터 타입 필드 명 */	
	CHAR	Alarm;							/* 알람 유무 */	
	CHAR	Important;						/*중요/비중요 알람 결정 0=이벤트 전용, 1=중요 알람 */		
	CHAR	Terminal_DI;					/*1=전원측, 2=부하측*/	  

} ST_COMMON_DNPBOMAPINDEX, *LPST_COMMON_DNPBOMAPINDEX;

//// AI 맵 인덱스
typedef struct __stCommonDNPAIMapIndex__		
{       
	INT		MapId;							/*맵 ID */
	INT		RTUMapId;						/*RTU맵 ID */
	INT		Scale;							/*ScaleFactor ID */
	INT		LimitSetId;						/*Limit Set ID */
	INT		MeasureTypeID;					/*데이터 분류코드 ID */
	SHORT	Position;						/*AI_Index  */
	TCHAR	IndexName[RDB_NAME64_SZ];		/*Index 명 */
	CHAR	CircuitNo;						/*회로번호 */	
	TCHAR	Obj_Var[RDB_NAME32_SZ];			/*Object/Variation */	
	CHAR	Class;							/*Class 번호 */	
	CHAR	EMS;							/*EMS 계측 유무 */	
	CHAR	GrpFlag;						/*그룹구성 0 = 1 index value, 1 = 2 index로 상위워드,  2 = 2 index로 하위워드 */
	UINT	LinkPos;						/*연결되어 있는 참조 인덱스 */
	TCHAR	upc_name[RDB_NAME64_SZ];		/*Value에 대한 MW 데이터 타입 필드 명 */	
	TCHAR	upc_tlq[RDB_NAME64_SZ];			/*TLQ에 대한 MW 데이터 타입 필드 명 */	
	TCHAR	upc_uptime[RDB_NAME64_SZ];		/*업데이트타임에 대한 MW 데이터 타입 필드 명 */	
	UCHAR	Alarm;							/* 알람 유무 */	
	CHAR	Important;						/*중요/비중요 알람 결정 0=이벤트 전용, 1=중요 알람 */		
	CHAR	Terminal_DI;					/*1=전원측, 2=부하측*/	  
	INT		UnitSymbol;						/*단위 */
	INT		MinMaxLimitSet;					/*상한하한치 ID */
	INT		DataByteId;						/*데이터 형 */

} ST_COMMON_DNPAIMAPINDEX, *LPST_COMMON_DNPAIMAPINDEX;

//// AO 맵 인덱스
typedef struct __stCommonDNPAOMapIndex__		
{       
	INT		MapId;							/*맵 ID */
	INT		RTUMapId;						/*RTU맵 ID */
	INT		Scale;							/*ScaleFactor ID */
	INT		StateGrpId;						/*LimitSEt Id*/
	INT		MeasureTypeID;					/*데이터 분류코드 ID */
	SHORT	Position;						/*AO_Index  */
	TCHAR	IndexName[RDB_NAME64_SZ];		/*Index 명 */
	FLOAT	NormalValue;					/*정상값 */
	FLOAT	StepValue;						/*조작값 */
	CHAR	CircuitNo;						/*회로번호 */	
	TCHAR	Obj_Var[RDB_NAME32_SZ];			/*Object/Variation */	
	CHAR	Class;							/*Class 번호 */	
	CHAR	EMS;							/*EMS 계측 유무 */	
	CHAR	GrpFlag;						/*그룹구성 0 = 1 index value, 1 = 2 index로 상위워드,  2 = 2 index로 하위워드 */
	INT		LinkPos;						/*연결되어 있는 참조 인덱스 */
	TCHAR	upc_name[RDB_NAME64_SZ];		/*Value에 대한 MW 데이터 타입 필드 명 */	
	TCHAR	upc_tlq[RDB_NAME64_SZ];			/*TLQ에 대한 MW 데이터 타입 필드 명 */	
	TCHAR	upc_uptime[RDB_NAME64_SZ];		/*업데이트타임에 대한 MW 데이터 타입 필드 명 */	
	CHAR	Alarm;							/* 알람 유무 */	
	CHAR	Important;						/*중요/비중요 알람 결정 0=이벤트 전용, 1=중요 알람 */		
	CHAR	Terminal_DI;					/*1=전원측, 2=부하측*/	  
	INT		UnitSymbol;						/*단위 */
	INT		MinMaxLimitSet;					/*상한하한치 ID */
	CHAR	DateByteId;						/*데이터형 ID */  

} ST_COMMON_DNPAOMAPINDEX, *LPST_COMMON_DNPAOMAPINDEX;

//// Counter 맵 인덱스
typedef struct __stCommonDNPCOUNTERMapIndex__		
{       
	INT		MapId;							/*맵 ID */
	INT		RTUMapId;						/*RTU맵 ID */
	INT		LimitSetId;						/*LimitSEt Id*/
	INT		MeasureTypeID;					 /*테이터분류 코드 */
	SHORT	Position;						/*Counter_Index  */
	TCHAR	IndexName[RDB_NAME64_SZ];		/*Index 명 */
	CHAR	CircuitNo;						/*회로번호 */	
	TCHAR	Obj_Var[RDB_NAME32_SZ];			/*Object/Variation */	
	CHAR	Class;							/*Class 번호 */	
	CHAR	EMS;							/*EMS 계측 유무 */	
	CHAR	GrpFlag;						/*그룹구성 0 = 1 index value, 1 = 2 index로 상위워드,  2 = 2 index로 하위워드 */
	INT		LinkPos;						/*연결되어 있는 참조 인덱스 */
	TCHAR	upc_name[RDB_NAME64_SZ];		/*Value에 대한 MW 데이터 타입 필드 명 */	
	TCHAR	upc_tlq[RDB_NAME64_SZ];			/*TLQ에 대한 MW 데이터 타입 필드 명 */	
	TCHAR	upc_uptime[RDB_NAME64_SZ];		/*업데이트타임에 대한 MW 데이터 타입 필드 명 */	
	CHAR	Alarm;							/* 알람 유무 */	
	CHAR	Important;						/*중요/비중요 알람 결정 0=이벤트 전용, 1=중요 알람 */		
	CHAR	Terminal_DI;					/*1=전원측, 2=부하측*/	  
	//UINT	UnitSymbol;						/*단위 */
	INT		MinMaxLimitSet;					/*상한하한치 ID */

} ST_COMMON_DNPCOUNTERMAPINDEX, *LPST_COMMON_DNPCOUNTERMAPINDEX;

//// 현장기기 통신 설정
typedef struct __stCommonRTUDevice__		
{       
	INT		RUID;							/*RTU ID */
	TCHAR	Name[RDB_NAME64_SZ];			/*RTU 이름 */
	INT		FEP_PROG_ID;					/*소속 프로그램 Id*/
	INT		PRI_FEP;						/*소속 주 FEP ID */
	INT		BCK_FEP;						/*소속 예비 FEP ID  */
	INT		RTUMapId;						/*RTU Map ID */
	INT		EquipTypeId;					/*장치 타입 */	
	INT		Protocol;						/*프로토콜 ID */	
	INT		MasterDnp;						/*FEP DNP 주소 */	
	SHORT	Dnp_Addr;						/*현장기기 DNP 주소 */	
	SHORT	BaudRate;						/*속도 */
	CHAR	Control;						/* */
	CHAR	StopBit;						/* */	
	CHAR	Parity;							/* */	
	TCHAR	IP_Addr[RDB_NAME16_SZ];			/*현장 IP */	
	INT	    Port;							/*LIU port */	
	INT		CommTypeId;						/*CommType id*/	  
	SHORT	Time_Sym_Hour;					/*시각동기화 시간(0~24)*/
	CHAR	Use_SBO;						/*SBO 사용(0=미사용, 1=사용) */
	CHAR	Use_Confirm;					/*컨펌 사용 */
	INT		wave_comtypeId;					/*파형목록(1:기존 DNP 통신, 2:지능형(KDN) DNP+FTP, 3:인텍 FTP)*/
	CHAR	Datalink;						/*연계되는 기기 (0:RTU 연계, 1:Datalink) */
	INT		FunGrpId;						/*Modbus 장치의 FunctionCode 조합ID */
	TCHAR	RTUCompany[RDB_NAME40_SZ];		
	TCHAR	RTUSerialNo[RDB_NAME40_SZ];			
	TCHAR	RTUDate[RDB_NAME40_SZ];			
	TCHAR	DevCompany[RDB_NAME40_SZ];			
	TCHAR	DevSerialNo[RDB_NAME40_SZ];			
	TCHAR	DevDate[RDB_NAME40_SZ];			

} ST_COMMON_RTUDEVICE, *LPST_COMMON_RTUDEVICE;

//// 현장기기 정보
typedef struct __stCommonConductingEquipment__		
{       
	INT		CEQID;							/*CEQ ID */
	INT		SSFK;							/*변전소 Id*/
	INT		DLFK;							/*DL ID */
	INT		PSRFK;							/*PSR ID  */
	INT		BVFK;							/*기준전압 ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];			/*m_RID FK */	
	TCHAR	Name[RDB_NAME64_SZ];			/*설비명 */	
	CHAR	Phase;							/*상연결정보 */	
	INT		EQCFK;							/*EquipmentContainer Id */	
	INT		DpGrpFK;						/*데이터포인트 대분류*/
	INT		DPGC_ACMFK;						/*ACM포인트 대분류*/
	CHAR	CircuitNo;						/*회로 번호 */
	TCHAR	MeshNo[RDB_MESH22_SZ];			/*전산화 번호 */	
	INT		RUID;							/*RTU DEVICE ID - 이종민씨 삭제 2014-03-04*/	
} ST_COMMON_CONDUCTINGEQUIPMENT, *LPST_COMMON_CONDUCTINGEQUIPMENT;

//// 개폐기 정보
typedef struct __stCommonSwitch__		
{       
	INT		SWID;							 /*스위치 ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];			 /*mRIDFK Id*/
    TCHAR	name[RDB_NAME64_SZ];			 /*개페기명 */	
	INT		CEQFK;							 /*CEQID  */	
	INT		CPSFK;							 /*CompositeSwitch ID  */
	//INT		BVFK;						 /*BaseVoltage ID */
	INT		PEQFK;							 /*ProtectEquipmentFK */
	INT		normalOpen;						 /*(1)정상 (0)비정상 */	
	INT		SwitchType;						 /*EquipmentContainer Id */
	INT		SwitchType_ACM;						 
	INT		sourceACLSFK;					 /*전원측 선로 정보 */	
	INT		loadACLSFK;						 /*부하측 선로 정보 */	
	//INT		RDID;						 /*RTUDevice ID */
	INT		RatedCurrent;					 /*데이터포인트 대분류*/
	INT		RatedCurrent_usfk;				 /*회로 번호 */
	INT		NormallyService;				 /*전산화 번호 */	
	TCHAR	Switch_no[RDB_NAME64_SZ];		 /*기기 번호 */	

} ST_COMMON_SWITCH, *LPST_COMMON_SWITCH;

//// 선로 구간
typedef struct __stCommonACLineSegment__		
{       
	INT		ACID;							/*선로구간 ID */
	INT		CEQFK;							/*CEQ Id*/	
	INT		PLSIFK;							/*PERLengthSegmentImpedence ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];			/*mRIDFK ID */	
	TCHAR	Name[RDB_NAME64_SZ];			/*선로 명*/	
	FLOAT	length;							/*길이            */
	INT		length_usfk;					/*UnitSymbol      */
	CHAR	phases;							/*상연결정보      */

} ST_COMMON_ACLINESEGMENT, *LPST_COMMON_ACLINESEGMENT;

// 선종 구분
typedef struct __stPDBPerLengthSequenceImpedance__
{
	INT		PLSIID;							/*PerLengthSequenceImpedancd ID		*/
	INT		PSRTypeFK;						/*PSRType ID						*/
	TCHAR	mRIDFK[RDB_NAME64_SZ];			/*DistributionLineSegment Name		*/
	TCHAR	Name3P[RDB_NAME64_SZ];			/*DistributionLineSegment AliasName	*/
	TCHAR	NameN[RDB_NAME64_SZ];			/*DistributionLineSegment AliasName	*/
	FLOAT	b0ch;							/* 서셉턴스 영상분 */
	INT		b0ch_usfk;						/*UnitSymbol      */
	FLOAT	bch;							/* 서셉턴스 */
	INT		bch_usfk;						/*UnitSymbol      */
	FLOAT	g0ch;							/* 컨덕턴스 영상분 */
	INT		g0ch_usfk;						/*UnitSymbol      */
	FLOAT	gch;							/* 컨덕턴스 */
	INT		gch_usfk;						/*UnitSymbol      */
	FLOAT	r;								/* 저항 영상분 */
	INT		r_us_fk;						/*UnitSymbol      */                       
	FLOAT	r0;								/* 저항 */
	INT		r0_us_fk;						/*UnitSymbol      */                       
	FLOAT	x;								/* 리액턴스 영상분 */
	INT		x_us_fk;						/*UnitSymbol      */                       
	FLOAT	x0;								/* 리액턴스 영상분 */
	INT		x0_us_fk;						/*UnitSymbol      */ 
	FLOAT	thermalLimit;					/*선로 열적 제한   */
	INT		thermalLimit_us_fk;				/*UnitSymbol      */
	FLOAT	ETLimit;						/*비상시열적 제한  */
	INT		ETLimit_us_fk;					/*UnitSymbol      */

} ST_COMMON_PERLENGTHSEQUENCEIMPEDANCE, *LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE;

//// 변전소 내 BUSBARSECTION 정보표시
typedef struct __stCommonBusbarSection__		
{       
	INT		BusId;							/*busbarsection ID */
	INT		VLFK;							/*voltage Level Id*/
	INT		CEQFK;							/*CEQID FK */	
	TCHAR	mRIDFK[RDB_NAME64_SZ];			/*mRIDFK ID */	
	TCHAR	Name[RDB_NAME64_SZ];			/*busbarsection 명*/	
	CHAR	busorder;						/*BusbarSection Order 1차/2차*/	

} ST_COMMON_BUSBARSECTION, *LPST_COMMON_BUSBARSECTION;

//// 다회로 설비
typedef struct __stCommonCompositeSwitch__		
{       
	INT		CPSID;							/*다회로설비 ID */	
	INT		PSRFK;							/*PSR Id*/
	INT		EQCFK;							/*EquipmentContainer FK */
	TCHAR	mRIDFK[RDB_NAME64_SZ];			/*mRIDFK ID */	
	TCHAR	Name[RDB_NAME64_SZ];			/*다회로 설비명*/	

} ST_COMMON_COMPOSITESWITCH, *LPST_COMMON_COMPOSITESWITCH;

//// 변압기
typedef struct __stCommonPowerTransformer__		
{       
	INT		PTRID;                            /*다회로설비 ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];            /*mRIDFK ID */		
	TCHAR	Name[RDB_NAME64_SZ];              /*다회로 설비명*/	
	INT		PSRFK;							  /*PSR ID */
	INT		EQCFK;                            /*EquipmentContainer FK */	
	SHORT	bankNo;                           /*뱅크번호*/
	FLOAT	bmagSat;                          /*포화영역에서 철심 병렬 자화 서셉턴스 퍼센트*/	
	INT		bmagSet_usfk;                     /*단위*/
	FLOAT	magBasekV;                        /**/
	INT		magBasekV_usfk;                   /*단위*/
	FLOAT	magSatFlux;                       /**/
	INT		magSatFlux_usfk;                  /*단위*/
	INT		Phase;                            /*위상 ID*/
	SHORT	transCoolingType;				  /*변압기 냉각의 유형*/						
	SHORT	transformerType;				  /*변압기 종류*/

} ST_COMMON_POWERTRANSFORMER, *LPST_COMMON_POWERTRANSFORMER;

//// Tap 제어기
typedef struct __stCommonTapChanger__		
{       
	INT		TCID;                              /*Tap 제어기 ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];             /*IdentifiedObject    */
	TCHAR	Name[RDB_NAME64_SZ];               /*이름                */	
	INT		PSRTYFK;                           /*PSRTYpe FK */	
	INT		highStep;                          /*탭 상한치*/	
	INT		lowSetp;                           /*탭 하한치*/
	INT		neutralStep;                       /*탭 중성점*/
	INT		normalStep;                        /*탭 위치*/
	FLOAT	SVI;                               /*탭간 변화량*/
	UINT	SVI_usfk;                          /*단위*/
	SHORT	tculControlMode;                   /*탭 제어기 제어모드 0: off, 1: Local, 2: Voltage, 3: MVAr*/

} ST_COMMON_TAPCHANGER, *LPST_COMMON_TAPCHANGER;

//// 변압기 결선
typedef struct __stCommonTransformerWiding__		
{       
	INT		TRWID;                             /*변압기 ID           */
	INT		PTRFK;                             /*PowerTransformer    */
	INT		CEQFK;                             /*ConductingEquipment */
	TCHAR	mRIDFK[RDB_NAME64_SZ];			   /*IdentifiedObject    */
	TCHAR	Name[RDB_NAME64_SZ];               /*이름                */
	//INT	BVFK;                              /*BaseVoltage         */	
	//UINT	ECFK;                              /*EquipmentContainer  */
	//UINT	PSRTYFK;                           /*PSRType             */
	//INT	TCHGFK;							   /*TapChanger          */
	CHAR	connectionType;                    /*결선방식            */
	CHAR	windingType;                       /*                    */
	FLOAT	r;                                 /*저항                */
	INT		r_usfk;                            /*UnitSymbol          */	
	FLOAT	r0;                                /*영상저항            */
	INT		r0_usfk;                           /*UnitSymbol          */
	FLOAT	x;                                 /*리액턴스            */
	CHAR	x_usfk;                            /*UnitSymbol          */
	FLOAT	x0;                                /*영상리액턴스        */
	INT		x0_usfk;                           /*UnitSymbol          */
	CHAR	grounded;                          /*                    */
	FLOAT	rground;                           /*접지저항            */
	INT		rground_usfk;                      /*UnitSymbol          */
	FLOAT	xground;                           /*접지리액턴스        */
	INT		xground_usfk;                      /*UnitSymbol          */
	FLOAT	ratedKV;                           /*UnitSymbol          */
	CHAR	ratedKV_usfk;                      /*UnitSymbol          */
	FLOAT	ratedMVA;                          /*정격용량            */
	INT		ratedMVA_usfk;                     /*UnitSymbol          */
	FLOAT	eMVA;                              /*비상상태 용량       */
	INT		eMVA_usfk;                         /*UnitSymbol          */
	INT		TCFK;

} ST_COMMON_TRANSFORMERWINDING, *LPST_COMMON_TRANSFORMERWINDING;
  

//// Tap 제어 스케쥴
typedef struct __stCommonTapRegulationSchedule__		
{       
	INT		TRSCID;                             /*Tap 제어기 ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];				/*IdentifiedObject    */
	INT		TCFK;								/*TapChangerFK	*/	
	TCHAR	Name[RDB_NAME64_SZ];				/*이름                */
	INT		AVR;								/*전압 제어 모드	*/	
	FLOAT	PATBSVL;                            /*제어 모션의 A상 전압 목표치*/
	INT		PATBSVL_usfk;                       /*Unit Symbol */	
	FLOAT	PADEV;								/*제어 모션의 A상 전압 목표치 편차*/
	INT		PADEV_usfk;							/*Unit Symbol*/
	FLOAT	PBTBSVL;                            /*제어 모션의 B상 전압 목표치*/
	INT		PBTBSVL_usfk;                       /*Unit Symbol */	
	FLOAT	PBDEV;								/*제어 모션의 B상 전압 목표치 편차*/
	INT		PBDEV_usfk;							/*Unit Symbol*/
	FLOAT	PCTBSVL;                            /*제어 모션의 C상 전압 목표치*/
	INT		PCTBSVL_usfk;                       /*Unit Symbol */	
	FLOAT	PCDEV;								/*제어 모션의 C상 전압 목표치 편차*/
	INT		PCDEV_usfk;							/*Unit Symbol*/
	INT		VVOFLAG;							/*VVO 제어 참여 여부*/
	INT		CON3P;								/*3상 일괄제어 여부*/
	INT		IIPFVM;
	FLOAT	PACOMPR;							/*A상 compensator R*/
	FLOAT	PACOMPX;							/*A상 compensator X*/
	FLOAT	PBCOMPR;							/*B상 compensator R*/
	FLOAT	PBCOMPX;							/*B상 compensator X*/
	FLOAT	PCCOMPR;							/*C상 compensator R*/
	FLOAT	PCCOMPX;							/*C상 compensator X*/
	INT		CONMEAP3;							/*3상 제어 TR의 LDC  기준 전압*/
	FLOAT	PATAPCOST;							
	FLOAT	PACONTAPMX;
	FLOAT	PBTAPCOST;
	FLOAT	PBCONTAPMX;
	FLOAT	PCTAPCOST;
	FLOAT	PCCONTAPMX;
	INT		PACONTAPMXDAY;						/*A상 하루 최대 동작횟수*/
	INT		PATAPOPDAY;							/*A상 하루 동작횟수*/
	INT		PBCONTAPMXDAY;						/*B상 하루 최대 동작횟수*/
	INT		PBTAPOPDAY;							/*B상 하루 동작횟수*/
	INT		PCCONTAPMXDAY;						/*C상 하루 최대 동작횟수*/
	INT		PCTAPOPDAY;							/*C상 하루 동작횟수*/

} ST_COMMON_TAPREGULATIONSCHEDULE, *LPST_COMMON_TAPREGULATIONSCHEDULE;

//// 보호설비
typedef struct __stCommonProtectionEquipment__		
{       
	INT		PEQID;								 /*ProtectionEquipment ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];				 /*IdentifiedObject       */
	TCHAR	Name[RDB_NAME64_SZ];				 /*이름                   */
	//INT		RSFK;							 /*RecloseSequence        */
	//INT		CRFK;							 /*CurrentRelay           */
	SHORT	EquipmentType;						 /*                       */
	SHORT	DIRTYPE;                             /*보호기기 방향성 구분   */
	INT		CTRATIO;                             /*보호 기기의 기본 CT 비 */
	TCHAR	Manufacture[RDB_NAME32_SZ];			 /*제작사 이름            */
	SHORT	RecloserType;						 /*리클로져 Type          */

} ST_COMMON_PROTECTIONEQUIPMENT, *LPST_COMMON_PROTECTIONEQUIPMENT;

//// 재페로시퀀스
typedef struct __stCommonRecloseSequence__		
{       
	INT		RSID;                              /*RecloseSequence ID  */	
	TCHAR	mRIDFK[RDB_NAME64_SZ];             /*IdentifiedObject    */
	INT		PEQFK;							   /*ProtectionEquipment ID */
	TCHAR	Name[RDB_NAME64_SZ];               /*이름                */
	FLOAT	RecloseDelay;                      /*Dead Time           */
	INT		RecloseDelay_usfk;                 /*UnitSymbol          */
	INT		recloseStep;                       /*                    */

} ST_COMMON_RECLOSESEQUENCE, *LPST_COMMON_RECLOSESEQUENCE;

//// 계전기
typedef struct __stCommonCurrentRelay__		
{       
	INT		CRID;                        /*CurrentRelay ID         */
	TCHAR	mRIDFK[RDB_NAME64_SZ];       /*IdentifiedObject        */
	TCHAR	Name[RDB_NAME64_SZ];         /*이름                    */
	INT		PEQFK;						 /*ProtectionEquipment ID */
	INT		OCR_MCODEFK;                 /*Machine Code            */
	INT		OCGR_MCODEFK;                /*Machine Code            */
	INT		TAPCHOICE;                   /*한시 Tap 선정계수 (상)  */
	INT		LEVERSTAP;                   /*Time Lever Step (상)    */
	INT		RECTMPAA;                    /*Relay 복귀시간 계수     */
	INT		RECTMPAB;                    /*Relay 복귀시간 계수     */
	INT		RECTMPAC;                    /* Relay 복귀시간 계수    */
	INT		GROUNDTAPCHOICE;             /*한시 Tap 선정계수 (지락)*/
	INT		GROUNDLEVERSTAP;             /*Time Lever Step (지락)  */

} ST_COMMON_CURRENTRELAY, *LPST_COMMON_CURRENTRELAY;
     
//// 에너지 저장장치
typedef struct __stCommonBatteryStorage__		
{       
	INT			BATTID;                       /*BatteryStorage ID   */
	INT			GENFK;                        /*GeneratingUnit      */
	TCHAR		mRIDFK[RDB_NAME64_SZ];        /*IdentifiedObject    */
	TCHAR		Name[RDB_NAME64_SZ];          /*이름                */
	INT			ESSCHGTM;					  
	INT			ESSCHGTM_usfk;
	INT			ESSDCHGTM;
	INT			ESSDCHGTM_usfk;
	INT			ESSTYPE;
	FLOAT		ESSMXSOC;
	INT			ESSMXSOC_usfk;
	FLOAT		ESSMNSOC;
	INT			ESSMNSOC_usfk;
	FLOAT		ESSCHGEFF;
	INT			ESSCHGEFF_usfk;
	FLOAT		ESSCRATIO;
	INT			ESSCRATIO_usfk;
	FLOAT		ESSMWh;
	INT			ESSMWh_USFK;
	FLOAT		ESSCHARMXMW;
	INT			ESSCHARMXMW_USFK;
	FLOAT		ESSCHARMNMW;
	INT			ESSCHARMNMW_USFK;
	FLOAT		ESSDICHMXMW;
	INT			ESSDICHMXMW_USFK;
	FLOAT		ESSDICHMNMW;
	INT			ESSDICHMNMW_USFK;

} ST_COMMON_BATTERYSTORAGE, *LPST_COMMON_BATTERYSTORAGE;
                                         
//// 발전기 또는 발전소
typedef struct __stCommonGeneratingUnit__		
{                                                           
	INT		GENID;                      /*GeneratingUnit ID    */
	INT		CEQFK;                      /*ConductingEquipment  */
	//INT    EQCFK;                     /*EquipmentContainer   */
	//INT		GRSHFK;                 /*GenRegulationSchedule*/
	TCHAR   mRIDFK[RDB_NAME64_SZ];      /*IdentifiedObject     */
	TCHAR   Name[RDB_NAME64_SZ];        /*이름                 */
	//INT		BVFK;                   /*BaseVoltage  - 이종민씨 삭제 */
	//INT    BSTFK;                     /*BatteryStorage       */
	INT		GenerationType;             /*                     */
	INT		intnectionType;             /*                     */
	FLOAT   maximumOperatingMW_PA;                  /*                     */
	INT		maximumOperatingMW_PA_usfk;             /*UnitSymbol           */
	FLOAT	minimumOperatingMW_PA;                  /*                     */
	INT		minimumOperatingMW_PA_usfk;             /*UnitSymbol           */
	FLOAT   maximumOperatingMVAR_PA;                /*                     */
	INT		maximumOperatingMVAR_PA_usfk;           /*UnitSymbol           */
	FLOAT   minimumOperatingMVAR_PA;                /*                     */
	INT		minimumOperatingMVAR_PA_usfk;           /*UnitSymbol           */
	FLOAT   maximumOperatingMW_PB;                  /*                     */
	INT		maximumOperatingMW_P_usfk;              /*UnitSymbol           */
	FLOAT   minimumOperatingMW_PB;                  /*                     */
	INT		minimumOperatingMW_PB_usfk;             /*UnitSymbol           */
	FLOAT   maximumOperatingMVAR_PB;                /*                     */
	INT		maximumOperatingMVAR_PB_usfk;           /*UnitSymbol           */
	FLOAT   minimumOperatingMVAR_PB;                /*                     */
	INT		minimumOperatingMVAR_PB_usfk;           /*UnitSymbol           */
	FLOAT   maximumOperatingMW_PC;                  /*                     */
	CHAR    maximumOperatingMW_PC_usfk;             /*UnitSymbol           */
	FLOAT   minimumOperatingMW_PC;                  /*                     */
	INT		minimumOperatingMW_PC_usfk;             /*UnitSymbol           */
	FLOAT   maximumOperatingMVAR_PC;                /*                     */
	INT		maximumOperatingMVAR_PC_usfk;           /*UnitSymbol           */
	FLOAT   minimumOperatingMVAR_PC;                /*                     */
	INT		minimumOperatingMVAR_PC_usfk;           /*UnitSymbol           */
	FLOAT   genSTX;                     /*                     */
	INT		genSTX_usfk;                /*UnitSymbol           */
	FLOAT   genTX;                      /*발전기과도리액턴스(1)*/
	INT		genTX_usfk;                 /*UnitSymbol           */
	FLOAT   genSSX;                     /*발전기정상리액턴스(1)*/
	INT		genSSX_usfk;                /*UnitSymbol           */
	FLOAT   genZERX;                    /*발전기영상리액턴스(1)*/
	INT		genZERX_usfk;               /*UnitSymbol           */
	FLOAT   baseMVA;                    /*정격용량             */
	INT		baseMVA_usfk;               /*UnitSymbol           */
	TCHAR   TEL[RDB_NAME64_SZ];			/*전화번호(02-)        */
	FLOAT   efficiency;                 /*효율                 */
	INT		efficiency_usfk;            /*UnitSymbol           */
	FLOAT   normalPF;                   /*역율                 */
	INT		normalPF_usfk;              /*UnitSymbol           */
	FLOAT   Pole;                       /*극수                 */
	INT		connectionType;             /*                     */
	FLOAT   GEN_MINQ0;                  /*                     */
	INT		GEN_MINQ0_usfk;             /*UnitSymbol           */
	FLOAT   GEN_MAXQ0;                  /*                     */
	INT		GEN_MAXQ0_usfk;             /*UnitSymbol           */
	FLOAT   GEN_MINQ20;                 /*                     */
	INT		GEN_MINQ20_usfk;            /*UnitSymbol           */
	FLOAT   GEN_MAXQ20;                 /*                     */
	INT		GEN_MAXQ20_usfk;            /*UnitSymbol           */
	FLOAT   GEN_MINQ40;                 /*                     */
	INT		GEN_MINQ40_usfk;            /*UnitSymbol           */
	FLOAT   GEN_MAXQ40;                 /*                     */
	INT		GEN_MAXQ40_usfk;            /*UnitSymbol           */
	FLOAT   GEN_MINQ60;                 /*                     */
	INT		GEN_MINQ60_usfk;            /*UnitSymbol           */
	FLOAT   GEN_MAXQ60;                 /*                     */
	INT		GEN_MAXQ60_usfk;            /*UnitSymbol           */
	FLOAT   GEN_MINQ80;                 /*                     */
	INT		GEN_MINQ80_usfk;            /*UnitSymbol           */
	FLOAT   GEN_MAXQ80;                 /*                     */
	INT		GEN_MAXQ80_usfk;            /*UnitSymbol           */
	FLOAT   GEN_MINQ100;                /*                     */
	INT		GEN_MINQ100_usfk;           /*UnitSymbol           */
	FLOAT   GEN_MAXQ100;                /*                     */
	INT		GEN_MAXQ100_usfk;           /*UnitSymbol           */
	FLOAT   GEN_PFMINLAG;               /*                     */
	INT		GEN_PFMINLAG_usfk;         /*UnitSymbol           */
	FLOAT   GEN_PFMINLEAD;              /*                     */
	INT		GEN_PFMINLEAD_usfk;         /*UnitSymbol           */
	FLOAT	MAXECOMW;                   /*                     */
	INT		MAXECOMW_usfk;              /*UnitSymbol           */
	FLOAT	MINECOMW;                   /*                     */
	INT		MINECOMW_usfk;              /*UnitSymbol           */
	FLOAT	ratedGrossMaxMW;            /*                     */
	INT		ratedGrossMaxMW_usfk;       /*UnitSymbol           */
	FLOAT	ratedGrossMinMW;            /*                     */
	INT		ratedGrossMinMW_usfk;       /*UnitSymbol           */
	FLOAT	raiseRampRate;              /*                     */
	INT		raiseRampRate_usfk;         /*UnitSymbol           */
	FLOAT	lowerRampRate;              /*                     */
	INT		lowerRampRate_usfk;         /*UnitSymbol           */
	FLOAT	muston;
	INT		muston_USFK;
	FLOAT	mustoff;
	INT		mustoff_USFK;
	INT		gen_mea;
	FLOAT	gen_COgenEff;
	INT		gen_COgenEff_USFK;

} ST_COMMON_GENERATINGUNIT, *LPST_COMMON_GENERATINGUNIT;

//// 전력변환장치
typedef struct __stCommonGenRegulationSchedule__		
{                                                               
	INT     RSCID;                      /*RegulationSchedule ID     */
	TCHAR   mRIDFK[RDB_NAME64_SZ];      /*FK, IdentifiedObject      */
	TCHAR   Name[RDB_NAME64_SZ];        /*이름                      */
	INT		GENFK;						/*GeneratingUnit FK			*/
	INT     AVR;                        /*자동전압 제어 참여여부(1: 참여, 0: 참여안함) */
	FLOAT   TBSVL;                      /*제어 모선의 전압 목표치   */
	INT		TBSVL_usfk;                 /*UnitSymbol                */
	FLOAT   DEV;                        /*제어 모선 A상의 전압 목표치 편차*/
	INT     DEV_usfk;                   /*UnitSymbol                */
	FLOAT   PF;                         /*역률제어를 위한 역률 목표치*/
	INT     PF_usfk;                    /*UnitSymbol                */
	FLOAT   FLTContribution;            /*고장기여분(인버터 연계형) */
	INT     FLTContribution_usfk;       /*UnitSymbol                */
	INT     VVOFLAG;                    /*발전기 무효전력 제어에 VVO 참여여부(0: 불참, 1: 참여)*/
	INT     MVARCONMODE;                /*무효전력 제어모드(1:전압, 2:역률, 3: 일정무효전력)*/
	FLOAT   OUTQ;                       /*일정 무효전력 제어 모드인 발전기의 무효전력 목표치*/
	INT     OUTQ_usfk;                  /*UnitSymbol                */
	FLOAT   PFVVOMINLAG;                /*VVO 제어시 발전기 최소 지상 역률 */
	INT     PFVVOMINLAG_usfk;           /*UnitSymbol                       */
	FLOAT   PFVVOMINLEAD;               /*VO 제어시 발전기 최소 진상 역률  */
	INT     PFVVOMINLEAD_usfk;          /*UnitSymbol                */

} ST_COMMON_GENREGULATIONSCHEDULE, *LPST_COMMON_GENREGULATIONSCHEDULE;

//// 풍력 분산전원
typedef struct __stCommonWindTurbine__		
{                                                                                                       
	INT		WTID;                    /*WindTurbine ID                                                     */
	INT		GENFK;                   /*GeneratingUnit FK                                                  */
	TCHAR   mRIDFK[RDB_NAME64_SZ];   /*IdentifiedObject                                                   */
	TCHAR   Name[RDB_NAME64_SZ];     /*이름                                                               */
	FLOAT	LENGTH;                  /*블래이드 길이                                                      */
	INT		LENGTH_usfk;             /*UnitSymbol                                                         */
	FLOAT	HEIGHT;                  /*회전축 높이                                                        */
	INT		HEIGHT_usfk;             /*UnitSymbol                                                         */
	FLOAT	ALTITUDE;                /*해발고도                                                           */
	INT		ALTITUDE_usfk;           /*UnitSymbol                                                         */
	INT		WINDDIR;                 /*풍향                                                               */
	INT		WINDREVERSE;             /*역풍시 발전가능여부                                                */	
	FLOAT   LAT;					 /*풍력발전기 위도													  */		
	INT     LAT_USFK;				 /*풍력발전기 위도 단위												  */
	FLOAT   LONG;					 /*풍력발전기 경도													  */		
	INT     LONG_USFK;				 /*풍력발전기 경도 단위												  */
	FLOAT   ALT;					 /*풍력발전기 해발고도												  */		
	INT     ALT_USFK;				 /*풍력발전기 해발고도 단위											  */

} ST_COMMON_WINDTURBINE, *LPST_COMMON_WINDTURBINE;

//// 태양광 분산전원
typedef struct __stCommonPhotoVoltaic__		
{                                                                                                   
	INT    PVID;                     /*PhotoVoltaic ID                                                    */
	INT    GENFK;                    /*GeneratingUnit FK                                                  */
	TCHAR  mRIDFK[RDB_NAME64_SZ];    /*IdentifiedObject                                                   */
	TCHAR  Name[RDB_NAME64_SZ];      /*이름                                                               */
	FLOAT  SIZE;                     /*태양광 모듈 1개당 면적(m2)                                         */
	INT    SIZE_usfk;                /*UnitSymbol                                                         */
	FLOAT  EFF;                      /*모듈별 효율                                                        */
	INT    EFF_usfk;                 /*UnitSymbol                                                         */
	INT    NOOFMD;                   /*모듈 개수                                                          */
	FLOAT  LAT;						 /*태양광 위도														  */		
	INT    LAT_USFK;				 /*태양광 위도 단위													  */
	FLOAT  LONG;					 /*태양광 경도														  */		
	INT    LONG_USFK;				 /*태양광 경도 단위													  */
	FLOAT  ALT;						 /*태양광 해발고도													  */		
	INT    ALT_USFK;				 /*태양광 해발고도 단위												  */

} ST_COMMON_PHOTOVOLTAIC, *LPST_COMMON_PHOTOVOLTAIC;

//// 발전기 연료비 곡선
typedef struct __stCommonGenUnitOpCostCurve__		
{                                                                                            
	INT		  GUOCCID;                /*GenUnitOpCostCurve ID                                         */
	INT		  GENFK;                   /*GeneratingUnit                                                */
	TCHAR	  GENCSTCUR_TYPE[RDB_NAME32_SZ];         /*발전기 비용함수 종류                                          */
	INT		  GENCSTCUR_COEF1;        /*2차비용곡선 계수                                              */
	INT		  GENCSTCUR_COEF2;        /*2차비용곡선 계수                                              */
	INT       GENCSTCUR_CONST;        /*2차비용곡선 상수                                              */	
	FLOAT	  GENCSTCUR_STC;
	INT		  GENCSTCUR_USFK;
	INT		  GENCSTCUR_KW1;
	INT		  GENCSTCUR_KWCOST1;
	INT		  GENCSTCUR_KW2;
	INT		  GENCSTCUR_KWCOST2;
	INT		  GENCSTCUR_KW3;
	INT		  GENCSTCUR_KWCOST3;
	INT		  GENCSTCUR_KW4;
	INT		  GENCSTCUR_KWCOST4;
	INT		  GENCSTCUR_KW5;
	INT		  GENCSTCUR_KWCOST5;
	INT		  GENCSTCUR_KW6;
	INT		  GENCSTCUR_KWCOST6;
	INT		  GENCSTCUR_KW7;
	INT		  GENCSTCUR_KWCOST7;
	INT		  GENCSTCUR_KW8;
	INT		  GENCSTCUR_KWCOST8;
	INT		  GENCSTCUR_KW9;
	INT		  GENCSTCUR_KWCOST9;
	INT		  GENCSTCUR_KW10;
	INT		  GENCSTCUR_KWCOST10;
	INT		  GENCSTCUR_KW_USFK;
	INT		  GENCSTCUR_KWCOST_USFK;

} ST_COMMON_GENUNITOPCOSTCURVE, *LPST_COMMON_GENUNITOPCOSTCURVE;

//// 고압수용가
typedef struct __stCommonEnergyConsumer__		
{                                                                   
	INT		ECRID;                        /*EnergyConsumer ID                            */
	INT		ACLSFK;                        /*ACLineSegment                                */
	INT		CEQFK;                        /*ConductingEquipment                          */
	TCHAR   mRIDFK[RDB_NAME64_SZ];        /*IdentifiedObject                             */
	TCHAR   Name[RDB_NAME64_SZ];          /*이름                                         */
	INT		customerCount;                /*고객수(1)                                    */
	FLOAT	pfixed;                       /*계약전력P(100KW)                             */
	INT		pfixed_usfk;                  /*UnitSymbol                                   */
	FLOAT	qfixed;                       /*계약전력Q(100Kvar)                           */
	INT		qfixed_usfk;                  /*UnitSymbol                                   */
	TCHAR   Tel[RDB_NAME20_SZ];           /*전화번호(02-)                                */
	TCHAR   HP[RDB_NAME20_SZ];            /*핸드폰번호(010-)                             */
	TCHAR   Customer_key[RDB_NAME20_SZ];  /*Custermer Key(80-)                           */
	INT     Priority;                     /*중요도(1)                                    */
	CHAR    SmsUse;                       /*SMS(0: 사용안함, 1: 사용)                    */
	INT		WATFK;						  /*Water로의 참조키							 */
	FLOAT   LoadDiv;
	INT		LoadMea;
	FLOAT	LoadCapMW;
	FLOAT	LoadCapMVAR;

} ST_COMMON_ENERGYCONSUMER, *LPST_COMMON_ENERGYCONSUMER;

//// 병렬 역률보상기기
typedef struct __stCommonShuntCompasator__		
{                                                                   
	INT     SCID;                          /*ShuntCompansator ID                          */
	INT     CEQFK;                         /*ConductingEquipment                          */
	TCHAR   mRIDFK[RDB_NAME64_SZ];         /*IdentifiedObject                             */
	TCHAR   Name[RDB_NAME64_SZ];           /*이름                                         */
	//INT     BVFK;                          /*BaseVoltage                                  */
    FLOAT   NominalMVAr;                   /*정격 출력                                    */
	INT     NominalMVAr_usfk;              /*UnitSymbol                                   */

} ST_COMMON_SHUNTCOMPASATOR, *LPST_COMMON_SHUNTCOMPASATOR;

//// 무효전력 보상장치
typedef struct __stCommonStaticVarCompensator__		
{                                                                                      
	INT     SVCID;                         /*ShuntCompansator ID                          */
	INT     CEQFK;                         /*ConductingEquipment                          */
	TCHAR   mRIDFK[RDB_NAME64_SZ];         /*IdentifiedObject                             */
	TCHAR   Name[RDB_NAME64_SZ];           /*이름                                         */
	FLOAT   capacitiveRating;              /*최대 가능 캐패시터 무효전력                  */
	INT     capacitiveRating_usfk;         /*UnitSymbol                                   */
	FLOAT   inductiveRating;               /*최대 가능 인덕터 무효전력                    */
	INT		inductiveRating_usfk;          /*UnitSymbol                                   */
	INT		slope;                         /*특성 기울기                                  */	
	INT		SVCControlMode;                /*SVR Control mode                             */
	FLOAT	VoltageSetPoint;               /*Voltage Set Point                            */
	INT		VoltageSetPoint_usfk;          /*UnitSymbol                                   */
	INT		BaNo;                          /*뱅크 번호                                    */ 

} ST_COMMON_STATICVARCOMPENSATOR, *LPST_COMMON_STATICVARCOMPENSATOR;

//// 설비 및 집합개념의 모음
typedef struct __stCommonPowerSystemResource__		
{                                                                        
	INT	    PSRID;						/*PointID                 */
	INT	    PSRTYPEFK;					/*PSRTYPE ID              */
	TCHAR   mRIDFK[RDB_NAME64_SZ];		/*Identified Object       */
	TCHAR   Name[RDB_NAME64_SZ];		/*이름                    */

} ST_COMMON_POWERSYSTEMRESOURCE, *LPST_COMMON_POWERSYSTEMRESOURCE;

//// Power System Resource의 종류
typedef struct __stCommonPSRType__		
{                                                                        
	INT     PSRTYPEID;					/*PointID                 */
	TCHAR   mRIDFK[RDB_NAME64_SZ];		/*Identified Object       */
	TCHAR   Name[RDB_NAME64_SZ];		/*이름                    */
	TCHAR   mRCode[RDB_NAME16_SZ];		/*PointID                 */
	INT     symbolfk;					/*심볼					  */

} ST_COMMON_PSRTYPE, *LPST_COMMON_PSRTYPE;

//// 집합개념
typedef struct __stCommonEquipmentContainer__		
{                                                                        
	INT     EQCID;						/*PointID					*/
	INT     SGRFK;						/*SubGeographical Region ID */
	TCHAR   mRIDFK[RDB_NAME64_SZ];		/*Identified Object       */
	TCHAR   Name[RDB_NAME64_SZ];		/*이름                    */
	//UINT    mRCode;					/*mRCode prefix           */
	INT     PSRFK;						/*PSR ID				  */
} ST_COMMON_EQUIPMENTCONTAINER, *LPST_COMMON_EQUIPMENTCONTAINER;

//// 심볼
typedef struct __stCommonSymbol__		
{                                                                        
	INT     SYMBOLID;						/*심볼 아이디			*/
	TCHAR   NAME[RDB_NAME64_SZ];			/*심볼 이름				*/
	TCHAR   FILENAME[RDB_NAME64_SZ];		/*파일 명			    */
	INT     FILESIZE;						/*파일 사이즈			*/

} ST_COMMON_SYMBOL, *LPST_COMMON_SYMBOL;


//// 계통도 파일을 가져오는 테이블
typedef struct __stCommonDASDIAGRAMINFO__		
{                                                                        
	INT     DAS_DIAID;						/*도면 아이디			*/
	TCHAR   NAME[RDB_NAME64_SZ];			/*도면 이름				*/
	TCHAR	VERSION[RDB_NAME16_SZ];			/*도면 버전				*/
	TCHAR	EDITOR[RDB_NAME16_SZ];			/*도면 작성자			*/
	TCHAR	BUILDTIME[RDB_DATETIME25_SZ];	/*도면 작성일자			*/
	TCHAR   FILENAME[RDB_NAME64_SZ];		/*파일 이름			    */
	INT     FILESIZE;						/*파일 사이즈			*/

} ST_COMMON_DASDIAGRAMINFO, *LPST_COMMON_DASDIAGRAMINFO;

//// 계통도 파일을 가져오는 테이블
typedef struct __stCommonSTATIONDIAGRAMINFO__		
{                                                                        
	INT		STATIONDIAID;					/*도면 아이디			*/
	TCHAR   NAME[RDB_NAME64_SZ];			/*도면 이름				*/	
	TCHAR	VERSION[RDB_NAME16_SZ];			/*도면 버전				*/
	TCHAR	EDITOR[RDB_NAME16_SZ];			/*도면 작성자			*/
	TCHAR	BUILDTIME[RDB_DATETIME25_SZ];	/*도면 작성일자			*/
	TCHAR   FILENAME[RDB_NAME64_SZ];		/*파일 이름			    */
	INT     FILESIZE;						/*파일 사이즈			*/

} ST_COMMON_STATIONDIAGRAMINFO, *LPST_COMMON_STATIONDIAGRAMINFO;

//// 상태 포인트 정의
typedef struct __stCommonDiscrete__		
{                                                                        
	INT    PID;                    /*PointID                        */
	TCHAR  mRIDFK[RDB_NAME64_SZ];  /*Identified Object       */
	TCHAR  Name[RDB_NAME64_SZ];    /*SW_닫힘열림                    */
	INT    SSId;                   /*변전소 ID                      */
	INT    DLId;                   /*D/L ID                         */
	INT    CEQId;                  /*CEQID                          */
	INT    RUID;                   /*RemoteUnit ID                  */
	INT    MeasureTypeID;			/*포인트 분류                    */
	INT    TMId;                   /*Terminal ID                    */
	INT    StateGrpId;             /*상태그룹                       */
	INT    CommandID;              /*제어                           */
	CHAR   NormalVal;              /*정상 값                        */
	CHAR   AbnormalVal;            /*비정상 값                      */
	CHAR   Initval;                /*초기 값                        */ 
	SHORT  Position;               /*IndexNo                        */
	CHAR   CircuitNo;              /*회로번호                       */

} ST_COMMON_DISCRETE, *LPST_COMMON_DISCRETE;

//// 제어 포인트 정의
typedef struct __stCommonSetDiscrete__		
{                                                                        
	INT		PID;                    /*PointID                        */
	TCHAR   mRIDFK[RDB_NAME64_SZ];	/*Identified Object				 */
	TCHAR	Name[RDB_NAME64_SZ];    /*SW_닫힘열림                    */
	INT		SSId;                   /*변전소 ID                      */
	INT		DLId;                   /*D/L ID                         */
	INT		CEQId;                  /*CEQID                          */
	INT		RUID;                   /*RemoteUnit ID                  */
	INT     MeasureTypeID;			/*포인트 분류                    */
	INT		TMId;                   /*Terminal ID                    */
	INT		StateGrpId;             /*상태그룹                       */
	//INT		DiscreteId;         /*제어                           */
	//CHAR    Initval;              /*초기 값                        */ 
	SHORT    Position;              /*IndexNo                        */
	CHAR    CircuitNo;              /*회로번호                       */

} ST_COMMON_SETDISCRETE, *LPST_COMMON_SETDISCRETE;

//// 계측 포인트 정의
typedef struct __stCommonMeasurement__		
{                                                                       
	INT     PID;                    /*PointID                       */
	TCHAR   mRIDFK[RDB_NAME64_SZ];	/*Identified Object       */
	TCHAR   Name[RDB_NAME64_SZ];    /*SW_닫힘열림                    */
	INT		SSId;                   /*변전소 ID                      */
	INT		DLId;                   /*D/L ID                         */
	INT		CEQId;                  /*CEQ ID                         */
	INT		RUID;                   /*RemoteUnit ID                  */
	INT     MeasureTypeID;			/*포인트 분류                    */
	INT		TMId;                   /*Terminal ID                    */
	INT		UnitId;                 /*단위                          */
	INT		RLS_FK;                 /*Max/Min Range LimitSet ID      */
	INT		LS_FK;                  /*High/Low LimitSet ID          */ 
	INT		SF_FK;                  /*Sclae Factor ID               */
	FLOAT   InitVal;                /*초기 값                        */ 
	SHORT   Position;               /*IndexNo                       */
	CHAR    CircuitNo;              /*회로번호                       */	

} ST_COMMON_MEASUREMENT, *LPST_COMMON_MEASUREMENT;

//// 설정 포인트 정의
typedef struct __stCommonSetMeasurement__		
{                                                                       
	INT    PID;                    /*PointID                        */
	TCHAR  mRIDFK[RDB_NAME64_SZ];  /*Identified Object       */
	TCHAR  Name[RDB_NAME64_SZ];    /*SW_닫힘열림                    */
	INT    SSId;                   /*변전소 ID                      */
	INT    DLId;                   /*D/L ID                         */
	INT    CEQId;                  /*CEQ ID                         */
	INT    RUID;                   /*RemoteUnit ID                  */
	INT    MeasureTypeID;          /*포인트 분류                    */
	INT	   StateGrpId;			   /*state Group Id					*/
	INT    TMId;                   /*Terminal ID                    */
	INT    UnitID;                 /*단위                           */
	INT    RLS_FK;                 /*High/Low LimitSet ID          */ 
	INT    SF_FK;                  /*Sclae Factor ID               */
	FLOAT  NormalValue;            /*정상 값                        */ 
	FLOAT  StepValue;			   /*스텝 값                        */ 
	SHORT  Position;               /*IndexNo                        */
	CHAR   CircuitNo;              /*회로번호                       */	

} ST_COMMON_SETMEASUREMENT, *LPST_COMMON_SETMEASUREMENT;

//// 카운터 포인트 정의
typedef struct __stCommonAccumulator__		
{                                                                       
	INT		PID;                    /*PointID                        */
	TCHAR   mRIDFK[RDB_NAME64_SZ];	/*Identified Object       */
	TCHAR	Name[RDB_NAME64_SZ];    /*SW_닫힘열림                    */
	INT		SSId;                   /*변전소 ID                      */
	INT		DLId;                   /*D/L ID                         */
	INT		CEQId;                  /*CEQ ID                         */
	INT		RUID;                   /*RemoteUnit ID                  */
	INT     MeasureTypeID;			/*포인트 분류                    */
	INT		TMId;                   /*Terminal ID                    */
	//INT		UnitID;             /*단위                           */
	INT		RLS_FK;                 /*Max/Min Range LimitSet ID      */
	INT		LS_FK;                  /*High/Low LimitSet ID          */ 
	//INT		SF_FK;              /*Sclae Factor ID               */
	//FLOAT   InitVal;              /*초기 값                        */ 
	SHORT    Position;              /*IndexNo                        */
	CHAR    CircuitNo;              /*회로번호                       */	
} ST_COMMON_ACCUMULATOR, *LPST_COMMON_ACCUMULATOR;

//// 계산 포인트 정의
typedef struct __stCommonCalculation__		
{                                                                       
	INT		PID;                      /*PointID                        */
	TCHAR   mRIDFK[RDB_NAME64_SZ];	  /*Identified Object			   */
	TCHAR   Name[RDB_NAME64_SZ];      /*SW_닫힘열림                    */	
	INT		DpGrpFK;				  /*데이터포인트 대분류			   */
	INT		UnitID;                   /*단위                           */	 
	TCHAR   formular[RDB_NAME256_SZ]; /*계산식                         */
	CHAR    degree;                   /*우선순위                       */
	CHAR    interval;                 /*계산주기                       */	
	CHAR    Alarm;                    /*Alarm 여부                     */
	CHAR    Important;                /*중요도                         */

} ST_COMMON_CALCULATION, *LPST_COMMON_CALCULATION;

//// 계통도 설비 구성 포인트
typedef struct __stCommonPosition__		
{                                                                       
	INT		PositionID;               /* PointID                    */	
	TCHAR   NAME[RDB_NAME64_SZ];      /* 설비명                     */
	INT		PSRFK;				      /* PowerSystemResource ID     */
	INT		POSITIONX;				  /* X축 좌표 정보				*/
	INT		POSITONY;				  /* Y축 좌표 정보				*/
	INT		Order;					  /*선로지점 순서				*/

} ST_COMMON_POSITION, *LPST_COMMON_POSITION;

//// Water 설비 구성 포인트
typedef struct __stCommonWater__		
{                                                                       
	INT		WATID;				
	FLOAT   WaterTCap;		
	INT		WaterTCap_USFK;	
	FLOAT	WaterTMax;	
	FLOAT	WaterTMin;	
	FLOAT	WaterTInit;		
	INT     WaterT_USFK;
	FLOAT	Water_MCap;
	INT	    WaterMCap_USFK;
	FLOAT	Water_MEff;
	INT		WaterMEff_USFK;

} ST_COMMON_WATER, *LPST_COMMON_WATER;


//// ACM GROUP
typedef struct __stCommonAcmAppGroup__		
{                                                                        
	INT     ACMAGID;					
	TCHAR   Name[RDB_NAME32_SZ];

} ST_COMMON_ACM_APPGROUP, *LPST_COMMON_ACM_APPGROUP;


//// ACM MAPINDEX
typedef struct __stCommonAcmMapIndex__		
{                                                                        
	INT     ACMMIID;
	INT		DPGC_ACMFK;
	INT		ACMAGFK;
	INT		ACMTGFK;
	INT		ACMTFK;
	INT		MeasureTypeID;
	INT		Position;
	TCHAR   Name[RDB_NAME64_SZ];
	TCHAR   upc_name[RDB_NAME32_SZ];
	TCHAR   upc_uptime[RDB_NAME40_SZ];

} ST_COMMON_ACM_MAPINDEX, *LPST_COMMON_ACM_MAPINDEX;
	

//// ACM TABLE
typedef struct __stCommonAcmTable__		
{                                                                        
	INT     ACMTID;					
	TCHAR   Name[RDB_NAME32_SZ];

} ST_COMMON_ACM_TABLE, *LPST_COMMON_ACM_TABLE;


//// ACM TABLEGROUP
typedef struct __stCommonAcmTableGroup__		
{                                                                        
	INT     ACMTGID;					
	TCHAR   Name[RDB_NAME32_SZ];

} ST_COMMON_ACM_TABLEGROUP, *LPST_COMMON_ACM_TABLEGROUP;


//// PCS
typedef struct __stCommonPcs__		
{                                                                        
	INT     PCSID;					
	TCHAR   Name[RDB_NAME64_SZ];
	FLOAT   PCS_CAPMVA;
	INT		PCS_CAPMVA_USFK;
	INT		BSFK;

} ST_COMMON_PCS, *LPST_COMMON_PCS;


//// MAINTRANSFORMER
typedef struct __stCommonMainTransformer__		
{                                                                        
	INT     MTRID;
	INT		SSFK;
	INT		EQCFK;
	TCHAR   mRIDFK[RDB_NAME64_SZ];
	TCHAR   Name[RDB_NAME64_SZ];	
	INT		DPGC_ACMFK;

} ST_COMMON_MAINTRANSFORMER, *LPST_COMMON_MAINTRANSFORMER;

//// 가상선로 사활선 처리
typedef struct __stCommonVirtual_Line_
{                                                   
	INT		VirtualLineCEQID;								 /*가상선로 CEQID                     */
	INT		ReferenceLineCEQID;								 /*사활선참조 선로  CEQID             */
	INT		ReferenceRTUCEQID;								 /*사활선참조 스위치 CEQID            */
	INT		DLID;											 /*가상선로의 DL					  */

} ST_COMMON_VIRTUAL_LINE, *LPST_COMMON_VIRTUAL_LINE;

//// 메모 관리
typedef struct __stOprMemo_
{   
	INT		MMID;                            /*PID                         */
	TCHAR	CREATE_TIME[RDB_DATETIME25_SZ];	 /*생성시간                    */
	INT		SSFK;							 /*변전소 이름                 */
	INT		DLFK;							 /*DL 이름                     */
	INT		CEQFK;							 /*전주번호                    */
	INT		USERID_FK;                       /*작성자 ID                   */
	TCHAR   CONTENTS[RDB_CONTENT512_SZ];     /*내용                        */

} ST_OPR_MEMO, *LPST_OPR_MEMO;

//// 공지사항 관리
typedef struct __stOprMessage_
{   
	INT		MSGID;								/*PID                         */
	TCHAR    CREATE_TIME[RDB_DATETIME25_SZ];	/*생성시간                    */
	CHAR    MSG_TYPE;						    /*메시지 종류 (1=긴급, 2=보통) */
	INT		USERID_FK;                          /*작성자 ID                   */
	TCHAR   CONTENTS[RDB_CONTENT512_SZ];        /*내용                        */

} ST_OPR_MESSAGE, *LPST_OPR_MESSAGE;

//// 작업관리 관리
typedef struct __stOprConstruction_
{                    
	INT     CTRID;                            /*PID                         */
	TCHAR	CREATE_TIME[RDB_DATETIME25_SZ];   /*생성시간                    */
	INT     SSFK;							  /*변전소 이름                 */
	INT     DLFK;							  /*DL 이름                     */
	INT     CEQFK;							  /*전주번호                    */
	CHAR    CONSTTYPE ;                       /*작업구분                    */ 
	INT     USERID_FK;                        /*작성자 ID                   */
	TCHAR   CONTENTS[RDB_CONTENT512_SZ];      /*내용                        */

} ST_OPR_CONSTRUCTION, *LPST_OPR_CONSTRUCTION;

//// 사령원 관리 테이블
typedef struct __stOprOperatorAssign_
{                    
	INT		OPRAId;                            /*사령원 관한관리             */
	INT		USERFK;                            /*OperatorCodeID FK           */
	CHAR    AssignType;                        /*권한제어 타입(0=지점,1=변전소, 2=DL */ 
	INT		TableId;                           /*지점(SubGeographicalRegion의 ID), 변전소(Substation의 ID), DL(DistributionID) */

} ST_OPR_OPERATORASSIGN, *LPST_OPR_OPERATORASSIGN;

//// 파형목록 파일을 저장하는 테이블
typedef struct __stOprWAVE_LIST_
{                    
	INT		WaveListId;                       /*파형 Id                     */
	TCHAR  CreateTm[RDB_DATETIME25_SZ];       /*생성시간                    */
	INT		RUID;                             /*RTU ID                      */
	INT		SampRate;                         /*샘플링 수                   */
	TCHAR   Filename[RDB_NAME64_SZ];          /*파일이름                    */
	INT		FileSize;                         /*파일크기                    */ 

} ST_OPR_WAVE_LIST, *LPST_OPR_WAVE_LIST;

//// 파형목록 파일을 저장하는 테이블
typedef struct __stOprWAVE_FILE_
{                    
	INT		WaveId;							  /*파형 Id                     */
	TCHAR	CreateTm[RDB_DATETIME25_SZ];      /*생성시간                    */
	INT		RUID;                             /*RTU ID                      */
	INT		WaveType;                         /*파형 타입                   */	
	TCHAR   Filename[RDB_NAME64_SZ];          /*파일이름                    */
	INT		FileSize;                         /*파일크기                    */ 

} ST_OPR_WAVE_FILE, *LPST_OPR_WAVE_FILE;

//// 서버 상태 데이터 저장 테이블
typedef struct __stOprComputerStatus_
{                                                   
	INT		 ComputerID;								 /* 컴퓨터 ID                         */
	TCHAR    ComputerName[RDB_NAME64_SZ];				 /* 컴퓨터 이름                       */
	CHAR	 ComputerType;								 /* 컴퓨터 종류                       */
	SHORT    ActiveState;								 /* 동작 상태                         */
	SHORT    RunState;									 /* 운전상태                          */
	SHORT    UpcActiveState;							 /* MW 동작상태                       */
	SHORT    UpcRunState;								 /* MW 운전상태		                  */
	SHORT    RdbRunState;								 /* RDB 상태						  */
	SHORT    RdbRoleState;								 /* RDB 미러링 상태                   */
	TCHAR    SysStart_tm[RDB_DATETIME25_SZ];			 /* 최종실행시각                      */
	TCHAR    SysStop_tm[RDB_DATETIME25_SZ];				 /* 최종종료시각					  */
	TCHAR    lastupdate_tm[RDB_DATETIME25_SZ];			 /* DP 업데이트 시간                  */

} ST_OPR_COMPUTERSTATUS, *LPST_OPR_COMPUTERSTATUS;

//// 계산결과 저장 테이블
typedef struct __stOprCalculation_Result_
{                                                   
	INT		PID;									 /*포인트 ID                           */
	INT		VALUE;									 /*계산결과                            */
	INT		Old_Value;								 /*이전계산결과                        */
	SHORT   TLQ;									 /*TLQ                                 */
	TCHAR   LAST_UPDATE[RDB_DATETIME25_SZ];			 /*마지막 업데이트 시간                */

} ST_OPR_CALCULATION_RESULT, *LPST_OPR_CALCULATION_RESULT;


#pragma pack()
#endif	/* __PDBSTRUCT_H__ */