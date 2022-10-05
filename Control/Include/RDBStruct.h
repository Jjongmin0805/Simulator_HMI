#pragma once
#ifndef __RDBSTRUCT_H__
#define __RDBSTRUCT_H__

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
// RDBStruct.h:  RDB���� ���Ǵ� Share Memory ����ü�� ����
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

// �����޸� ������ �ʿ��� �޸� 
typedef struct __stHMIProject__		
{
	ST_ENV_RDB tItemCnt[2000];	/* �����޸� ���̺��� �̸��� ���ڵ�� ���� */

} ST_HMI_PROJECT, *LPST_HMI_PROJECT;

//CIM���� ����Ǵ� ��������
typedef struct __stCommonIdentifiedObject__		
{
	TCHAR	MRID[RDB_NAME64_SZ];					/*mRID				*/	
	//TCHAR	name[RDB_NAME64_SZ];					/*�̸�				*/	
	TCHAR	aliasName[RDB_NAME64_SZ];				/*��Ī				*/
	TCHAR	localName[RDB_NAME64_SZ];				/*�����̸�			*/
	TCHAR	pathName[RDB_NAME128_SZ];				/*����̸�			*/
	TCHAR	description[RDB_NAME128_SZ];			/*����				*/

} ST_COMMON_IDENTIFIEDOBJECT, *LPST_COMMON_IDENTIFIEDOBJECT;


// ����(����)
typedef struct __stCommonGeographicalRegion__		
{
	INT		GGRID;								/*GGR ID			*/	
	TCHAR	mRIDFK[RDB_NAME64_SZ];				/*mRID ID			*/
	TCHAR	Name[RDB_NAME64_SZ];				/*����(����) ��    	*/
	INT		GGRCode;							/*�����ڵ�			*/

} ST_COMMON_GEOGRAPHICALREGION, *LPST_COMMON_GEOGRAPHICALREGION;

//// ����(���ϻ����)
typedef struct __stCommonSubGeographicalRegion__		
{
	INT		SGRID;								/*SGR ID			*/	
	INT		GGRFK;								/*GGR ID			*/	
	TCHAR	mRIDFK[RDB_NAME64_SZ];				/*mRID ID			*/
	TCHAR	Name[RDB_NAME64_SZ];				/*���� ��	    	*/
	INT		SGRCode;							/*�����ڵ�			*/
	INT		DPGC_ACMFK;

} ST_COMMON_SUBGEOGRAPHICALREGION, *LPST_COMMON_SUBGEOGRAPHICALREGION;

//// �ý��۳� DataPoint ������ ���� ���̺�
typedef struct __stCommonDataPointGroupCode__		
{
	INT		DpGrpId;							/*SGR ID			*/	
	TCHAR	DpGrpName[RDB_NAME64_SZ];			/*�ý��� �Ҽ� �з�	*/
												/* ��������(1), �ߺ�����(2), �л�����(3), ���·���(4), �������(5), TDAS(6), SCADA(7), ������(8), �ý���(9) */
	TCHAR	DpGrpCode[RDB_NAME64_SZ];			/*����������Ʈ �ڵ�	*/
	TCHAR	DpPrefixName[RDB_NAME32_SZ];		/*����������Ʈ Prefix �̸� */

} ST_COMMON_DATAPOINTGROUPCODE, *LPST_COMMON_DATAPOINTGROUPCODE;

//// ��ǻ��(�ý���) ���� ���̺�
typedef struct __stCommonComputerode__		
{
	INT		ComputerId;									 /*��ǻ�� ID			*/	
	TCHAR	ComputerName[RDB_NAME64_SZ];				 /*������ġ �̸�			*/
	CHAR	ComputerType; 								 /*��ġ���� */
	SHORT	PORT;										 /*����ȭ ������ ��ȣ �����Ʈ */
	CHAR	PRIORITY;									 /*����ȭ ������ ����켱 ���� (1=Active, 2=Standby)	UINT	MSINGLE;										 /*�ܵ����� ����(0=False, 1=True) */
	CHAR	MSINGLE;
	CHAR	OFFLINE;									 /*�������� ����(0=�������, 1=����) */
	INT		DpGrpFK;									 /*����������Ʈ �ڵ�	*/
	TCHAR	IP_Addr[RDB_NAME16_SZ];    

} ST_COMMON_COMPUTERCODE, *LPST_COMMON_COMPUTERCODE;

//// ���α׷� ���� ���̺�        
typedef struct __stCommonProgramCode__		
{       
	INT		ProgId;       							     /*���α׷�Id */	
	INT		ComputerId;									 /*ComputerCode�� ����Ǹ�, ���α׷��� ������ ��ǻ�� Id */
	TCHAR	ProgName[RDB_NAME64_SZ];     				 /*��ġ�� ����� .exe ���� �̸� */
	TCHAR	ServiceName[RDB_NAME64_SZ];					 /*��ġ�� ����� ���� ���α׷� �̸� */
	CHAR	ProgLevel;									 /*���α׷� �׷�(1=core, 2=base, 3=Application Level)*/
	CHAR	RunNode;									 /*���� ��� ����	*/
	CHAR	AutoRestart;								 /*���α׷� ��ֽ� ����� ����(0=No Restart, 1=Restart) */

} ST_COMMON_PROGRAMCODE, *LPST_COMMON_PROGRAMCODE;

//// ��ɿ� ���� ���̺�       
typedef struct __stCommonOperatorCode__		
{       
	INT		OperId;                            /*��ɿ� �ڵ� */	
	TCHAR	OperNum[RDB_NAME16_SZ];            /*��ɿ� ���*/	
	TCHAR	OperName[RDB_NAME32_SZ];           /*��ɿ� �̸� */	
    TCHAR	OperPasswd[RDB_NAME16_SZ];         /*��ɿ� ��ȣ(��ȣȭ) */	
    CHAR	ConAuth;                           /*������� (0=������� ����, 1=�����) */

} ST_COMMON_OPERATORCODE, *LPST_COMMON_OPERATORCODE;

//// ����ġ ���� �ڵ�       
typedef struct __stCommonSwitchTypeCode__		
{       
	INT		TypeID;                            /*����ġ ���� ID */	
	TCHAR	Name[RDB_NAME64_SZ];               /*����ġ ���� ��(Normal, Section, Tie, Terminal ��) */	

} ST_COMMON_SWITCHTYPECODE, *LPST_COMMON_SWITCHTYPECODE;

//// �۾����� ���̺�      
typedef struct __stCommonConstructionTypeCode__		
{       
	INT		ConstId;                           /*�۾����� ID */	
	TCHAR	Consttype[RDB_NAME64_SZ];          /*����밳���, ���������б�, �����н�����, �����������̼����� �� */	

} ST_COMMON_CONSTRUCTIONCODE, *LPST_COMMON_CONSTRUCTIONCODE;

//// �������� Ÿ��     
typedef struct __stCommonWaveComType__		
{       
	INT		wavecomTypetId;                          /*����Ÿ�� ID */	
	TCHAR	ComtypeName[RDB_NAME64_SZ];				 /*1:���� DNP ���, 2:������(KDN) DNP+FTP, 3:���� FTP */

} ST_COMMON_WAVECOMTYPE, *LPST_COMMON_WAVECOMTYPE;

//// ���°��� ���� ǥ�� �׷�  
typedef struct __stCommonStateGroup__		
{       
	INT		StateGrpId;                             /*���� �׷� ID */	
	TCHAR	Name[RDB_NAME64_SZ];					/*���� �̸� */	
	SHORT	Count;									/*���� ���� */	

} ST_COMMON_STATEGROUP, *LPST_COMMON_STATEGROUP;

//// �ε����� ������ ����  
typedef struct __stCommonDataByte__		
{       
	INT		DataByteId;                   /*���������� ID */	
	TCHAR	Name[RDB_NAME64_SZ];          /*�ε��� �̸� */
	CHAR	Sign;						  /*��ȣǥ�� 0: Unsigned, 1: Signed */
	CHAR	Size;						  /*DATABYTE ũ�� */

} ST_COMMON_DATABYTE, *LPST_COMMON_DATABYTE;

//// ���°��� ���� ���� ���̺�
typedef struct __stCommonStateSet__		
{       
	INT		StateSetId;                    /*���±׷� ID */
	TCHAR	Name[RDB_NAME64_SZ];          /*�����̸�(�ѱ�)*/
	UCHAR	Value;                         /*��� ���°� */
	INT		StateGrpId;                    /*���±׷� ID */    
} ST_COMMON_STATESET, *LPST_COMMON_STATESET;

//// ���� ǥ�� ����
typedef struct __stCommonUnit__		
{       
	INT		UnitId;							/*���� ID */
	TCHAR	UnitName[RDB_NAME64_SZ];		/*���� �̸�*/

} ST_COMMON_UNIT, *LPST_COMMON_UNIT;

//// ������ ����ǥ�ÿ� ��
typedef struct __stCommonScalefactor__		
{       
	INT		sfid;                         /*���� ID */
	TCHAR	Name[RDB_NAME64_SZ];          /*���� �̸�*/
	FLOAT	Scale;                        /* ������ */
	FLOAT	Offset;                       /* ���ذ� */

} ST_COMMON_SCALEFACTOR, *LPST_COMMON_SCALEFACTOR;

//// ������ġ ����
typedef struct __stCommonLimitCode__		
{       
	INT		LimitId;                      /*Limit ID */
	INT		LimitSetId;                   /*LimitSet ID */
	TCHAR	Name[RDB_NAME64_SZ];          /*Limit �̸�*/
	FLOAT	Val;                          /*���ذ� */
	CHAR	Limittype;                    /*����ġ,����ġ ���� 0=����ġ, 1=����ġ */

} ST_COMMON_LIMITCODE, *LPST_COMMON_LIMITCODE;

//// ������ġ ����
typedef struct __stCommonLimitSet__		
{       
	INT		LimitSetId;                   /*LimitSet ID */
	TCHAR	Name[RDB_NAME64_SZ];          /*LimitSet �̸�*/

} ST_COMMON_LIMITSET, *LPST_COMMON_LIMITSET;

//// ��� ���ۻ�� ���̺�
typedef struct __stCommonEquipCompany__		
{       
	INT		CompanyId;                   /*Company ID */
	TCHAR	CompanyName[RDB_NAME64_SZ];  /*Company �̸�*/

} ST_COMMON_EQUIPCOMPANY, *LPST_COMMON_EQUIPCOMPANY;

//// ������ ���� ���̺�
typedef struct __stCommonSubstation__		
{       
	INT		SSID;                       /*Company ID */
	INT		SGRFK;                      /*Company �̸�*/
	INT		EQCFK;                      /*EquipmentContainer */
	TCHAR	mRIDFK[RDB_NAME64_SZ];      /*mRIDFK */
	TCHAR	Name[RDB_NAME64_SZ];        /*������ �� */
	INT		PSRFK;						/*PSR ID */
	INT		SSCode;						/*������ �ڵ� */
	INT		DPGC_ACMFK;

} ST_COMMON_SUBSTATION, *LPST_COMMON_SUBSTATION;

//// ���� ȸ��
typedef struct __stCommonDistributionLine__		
{       
	INT		 DLID;                      /*DL ID */
	INT		 SSFK;                      /*������ ID*/
	INT		 MTRFK;                     /*Main Transformer */
	INT		 EQCFK;                     /*Equipment Container ID */
	TCHAR	 mRIDFK[RDB_NAME64_SZ];     /*mRIDFK */
	TCHAR	 Name[RDB_NAME64_SZ];       /*DL �� */
	INT		 dl_no;                     /*TDAS�� ���� DL ��ȣ */
	SHORT	 reliability;               /*�ŷڵ�*/
	SHORT	 priority;                  /*�켱���� */
	FLOAT	 rated_S;                   /*ȸ���� ���ؿ뷮*/
	INT		 RATED_S_USFK;              /*ȸ���� ���ؿ뷮 ���� */
	INT		 DPGC_ACMFK;				/*ACM���� FK */ 

} ST_COMMON_DISTRIBUTIONLINE, *LPST_COMMON_DISTRIBUTIONLINE;

//// ��������
typedef struct __stCommonBaseVoltage__		
{       
	INT      BVID;                      /*BV ID */
	TCHAR    mRIDFK[RDB_NAME64_SZ];     /*mRIDFK */
	TCHAR    Name[RDB_NAME64_SZ];       /*�������и� */
	FLOAT    NominalVoltage;            /*��������, ��Ī���а� */
	INT		 NominalVoltage_usfk;       /*���� */
	FLOAT    MaxVoltage;                /*�ְ����а� */
	INT      MaxVoltage_usfk;           /*���� */

} ST_COMMON_BASEVOLTAGE, *LPST_COMMON_BASEVOLTAGE;

//// ��������
typedef struct __stCommonBasePower__		
{       
	INT		BPID;						/*BP ID */
	TCHAR	Name[RDB_NAME64_SZ];		/*�������¸� */
	TCHAR	mRIDFK[RDB_NAME64_SZ];		/*mRIDFK */
	INT		basePower;					/*�������� */
	INT		basePower_usfk;				/*���� */

} ST_COMMON_BASEPOWER, *LPST_COMMON_BASEPOWER;

//// ���з���
typedef struct __stCommonVoltageLevel__		
{       
	INT		VLID;                      /*VL ID */
	INT		SSFK;                      /*������ ID */
	INT		BVFK;                      /*�������� ID */
	INT		EQCFK;                     /*Equipment Container ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];     /*mRIDFK */
	TCHAR	Name[RDB_NAME64_SZ];       /*���з����� */
	FLOAT	highVoltageLim;            /*busbar ���� ����*/
	INT		highVoltageLim_usfk;       /*���� */
	FLOAT	lowVoltageLim;             /*busbar ���� ���� */
	INT		lowVoltageLim_usfk;        /*���� */	
	INT		PSRFK;					   /*PowerSystemResource */

} ST_COMMON_VOLTAGELEVEL, *LPST_COMMON_VOLTAGELEVEL;

//// �� ���� ���̺�
typedef struct __stCommonPhase__		
{       
	UINT	PhaseID;                      /*Phase ID */
	TCHAR	PhaseName[RDB_NAME64_SZ];     /*Phase �� */
	TCHAR	Phase[RDB_NAME64_SZ];         /*ABCN, ABC, ABN, ACN, BCN, A, B, C�� */

} ST_COMMON_PHASE, *LPST_COMMON_PHASE;

//// �������� Ÿ�� ���̺�
typedef struct __stCommonProtocolType__		
{       
	INT		ProtocolTypeId;                /*Protocol ID */
	TCHAR	ProtocolName[RDB_NAME64_SZ];   /*Protocol �� ����/KODAS/MODBUS/DNP/IEC61850 */
	TCHAR	ProtocolKind[RDB_NAME32_SZ];   /*Protocol �� FEP���� ��� */

} ST_COMMON_PROTOCOLTYPE, *LPST_COMMON_PROTOCOLTYPE;

//// ��ġ���� Ÿ�� ���̺�
typedef struct __stCommonEquipmentType__		
{       
	INT		EquipTypeId;						/*EquipType ID */
	TCHAR	EquipTypeCode[RDB_NAME64_SZ];		/*��ġ����(����)*/
	TCHAR	EquipTypeDesc[RDB_NAME64_SZ];       /*��ġ����(�ѱ�) */

} ST_COMMON_EQUIPMENTTYPE, *LPST_COMMON_EQUIPMENTTYPE;

//// RTU Map Index ����
typedef struct __stCommonRTUMap__		
{       
	UINT	RTUMapId;							 /*RTUMAP ID */
	TCHAR	RTUMapName[RDB_NAME64_SZ];			 /*RTUMAP �̸�*/
	TCHAR	DMSName[RDB_NAME64_SZ];				 /*DMS �̸�*/
	UINT	RTUTypeId;							 /*RTU TYPE ID) */
	TCHAR	UPC_TypeName[RDB_NAME64_SZ];         /*�̵���� ����̸� */
	TCHAR	RTUKind[RDB_NAME32_SZ];				 /*FEP ����̸� */

} ST_COMMON_RTUMAP, *LPST_COMMON_RTUMAP;

////��� ���� �ڵ�
typedef struct __stCommonCommType__		
{       
	INT		CommTypeId;                        /*������� ID */
	TCHAR	ConmmTypeName[RDB_NAME64_SZ];      /*��������� ����ȵ�/����/��/����̵��/PCS_DT1800/KTS216/����/TRS/CDMA/��(LIU)/TCPIP */
	TCHAR	ConmmKind[RDB_NAME32_SZ];		   /*FEP���� ���� ��� */	

} ST_COMMON_COMMTYPE, *LPST_COMMON_COMMTYPE;

//// RTU ���� �ڵ�
typedef struct __stCommonRTUType__		
{       
	INT		RTUTypeId;						  /*RTU���� ID */
	TCHAR	RTUTypeName[RDB_NAME64_SZ];       /*Manual/FRTU/FIED/AMIGW/FRTU(60870) */

} ST_COMMON_RTUTYPE, *LPST_COMMON_RTUTYPE;

//// HMI �� UI���� Subtab ������
typedef struct __stCommonCategoryCode__		
{       
	INT		CCID;								/*ī�װ� ID */
	SHORT	CCDType;							/*���ο, ��ü����, ����, PQM, ������ ����, ���, �, ����  */
	TCHAR   Name[RDB_NAME64_SZ];				/*ī�װ��� */

} ST_COMMON_CATEGORYCODE, *LPST_COMMON_CATEGORYCODE;

//// ����Ʈ ����
typedef struct __stCommonMeasureTypeInfo__		
{       
	INT		MeasureTypeID;                 /*����Ʈ���� ID */
	TCHAR	Name[RDB_NAME64_SZ];           /*����Ʈ���� ��  */
	CHAR	PointType;				       /*����Ʈ����  BI, BO, AI, AO, Count */
	INT		CCDFK;						   /*ī�װ� ID FK */

} ST_COMMON_MEASURETYPEINFO, *LPST_COMMON_MEASURETYPEINFO;

//// BI �� �ε���
typedef struct __stCommonDNPBIMapIndex__		
{       
	INT		MapId;							/*�� ID */
	INT		RTUMapId;						/*RTU�� ID */
	INT		StateGrpId;						/*StateGroup�� StateGrpId */
	INT		MeasureTypeID;					/*����Ʈ ���� �ڵ�K */
	SHORT	Position;						/*BI_Index */
	SHORT	BO_Position;					/*BO_Index  */
	TCHAR	IndexName[RDB_NAME64_SZ];		/*Index �� */
	CHAR	CircuitNo;						/*ȸ�ι�ȣ */	
	CHAR	NormalValue;					/*���� */	
	CHAR	AbnormalValue;					/*������ */	
	TCHAR	Obj_Var[RDB_NAME32_SZ];			/*Object/Variation */	
	CHAR	Class;							/*Class ��ȣ */	
	CHAR	EMS;							/*EMS ���� ���� */	
	TCHAR	upc_name[RDB_NAME64_SZ];		/*Value�� ���� MW ������ Ÿ�� �ʵ� �� */	
	TCHAR	upc_tlq[RDB_NAME64_SZ];			/*TLQ�� ���� MW ������ Ÿ�� �ʵ� �� */	
	TCHAR	upc_uptime[RDB_NAME64_SZ];		/*������ƮŸ�ӿ� ���� MW ������ Ÿ�� �ʵ� �� */	
	CHAR	Alarm;							/* �˶� ���� */	
	CHAR	Important;						/*�߿�/���߿� �˶� ���� 0=�̺�Ʈ ����, 1=�߿� �˶� */		
	CHAR	Terminal_DI;					/*1=������, 2=������*/	  

} ST_COMMON_DNPBIMAPINDEX, *LPST_COMMON_DNPBIMAPINDEX;

//// BO �� �ε���
typedef struct __stCommonDNPBOMapIndex__		
{       
	INT		MapId;							/*�� ID */
	INT		RTUMapId;						/*RTU�� ID */
	INT		StateGrpId;						/*StateGroup�� StateGrpId */
	INT		MeasureTypeID;					/*����Ʈ ���� �ڵ�K */
	SHORT	Position;						/*BI_Index  */
	TCHAR	IndexName[RDB_NAME64_SZ];		/*Index �� */
	CHAR	CircuitNo;						/*ȸ�ι�ȣ */	
	TCHAR	Obj_Var[RDB_NAME32_SZ];			/*Object/Variation */	
	CHAR	Class;							/*Class ��ȣ */	
	CHAR	EMS;							/*EMS ���� ���� */	
	INT		CCId;							/*ControlCode�� CCID */
	SHORT	RelayOnTime;					/*Puls ���� On �ð�(ms) */
	TCHAR	upc_name[RDB_NAME64_SZ];		/*Value�� ���� MW ������ Ÿ�� �ʵ� �� */	
	TCHAR	upc_tlq[RDB_NAME64_SZ];			/*TLQ�� ���� MW ������ Ÿ�� �ʵ� �� */	
	TCHAR	upc_uptime[RDB_NAME64_SZ];		/*������ƮŸ�ӿ� ���� MW ������ Ÿ�� �ʵ� �� */	
	CHAR	Alarm;							/* �˶� ���� */	
	CHAR	Important;						/*�߿�/���߿� �˶� ���� 0=�̺�Ʈ ����, 1=�߿� �˶� */		
	CHAR	Terminal_DI;					/*1=������, 2=������*/	  

} ST_COMMON_DNPBOMAPINDEX, *LPST_COMMON_DNPBOMAPINDEX;

//// AI �� �ε���
typedef struct __stCommonDNPAIMapIndex__		
{       
	INT		MapId;							/*�� ID */
	INT		RTUMapId;						/*RTU�� ID */
	INT		Scale;							/*ScaleFactor ID */
	INT		LimitSetId;						/*Limit Set ID */
	INT		MeasureTypeID;					/*������ �з��ڵ� ID */
	SHORT	Position;						/*AI_Index  */
	TCHAR	IndexName[RDB_NAME64_SZ];		/*Index �� */
	CHAR	CircuitNo;						/*ȸ�ι�ȣ */	
	TCHAR	Obj_Var[RDB_NAME32_SZ];			/*Object/Variation */	
	CHAR	Class;							/*Class ��ȣ */	
	CHAR	EMS;							/*EMS ���� ���� */	
	CHAR	GrpFlag;						/*�׷챸�� 0 = 1 index value, 1 = 2 index�� ��������,  2 = 2 index�� �������� */
	UINT	LinkPos;						/*����Ǿ� �ִ� ���� �ε��� */
	TCHAR	upc_name[RDB_NAME64_SZ];		/*Value�� ���� MW ������ Ÿ�� �ʵ� �� */	
	TCHAR	upc_tlq[RDB_NAME64_SZ];			/*TLQ�� ���� MW ������ Ÿ�� �ʵ� �� */	
	TCHAR	upc_uptime[RDB_NAME64_SZ];		/*������ƮŸ�ӿ� ���� MW ������ Ÿ�� �ʵ� �� */	
	UCHAR	Alarm;							/* �˶� ���� */	
	CHAR	Important;						/*�߿�/���߿� �˶� ���� 0=�̺�Ʈ ����, 1=�߿� �˶� */		
	CHAR	Terminal_DI;					/*1=������, 2=������*/	  
	INT		UnitSymbol;						/*���� */
	INT		MinMaxLimitSet;					/*��������ġ ID */
	INT		DataByteId;						/*������ �� */

} ST_COMMON_DNPAIMAPINDEX, *LPST_COMMON_DNPAIMAPINDEX;

//// AO �� �ε���
typedef struct __stCommonDNPAOMapIndex__		
{       
	INT		MapId;							/*�� ID */
	INT		RTUMapId;						/*RTU�� ID */
	INT		Scale;							/*ScaleFactor ID */
	INT		StateGrpId;						/*LimitSEt Id*/
	INT		MeasureTypeID;					/*������ �з��ڵ� ID */
	SHORT	Position;						/*AO_Index  */
	TCHAR	IndexName[RDB_NAME64_SZ];		/*Index �� */
	FLOAT	NormalValue;					/*���� */
	FLOAT	StepValue;						/*���۰� */
	CHAR	CircuitNo;						/*ȸ�ι�ȣ */	
	TCHAR	Obj_Var[RDB_NAME32_SZ];			/*Object/Variation */	
	CHAR	Class;							/*Class ��ȣ */	
	CHAR	EMS;							/*EMS ���� ���� */	
	CHAR	GrpFlag;						/*�׷챸�� 0 = 1 index value, 1 = 2 index�� ��������,  2 = 2 index�� �������� */
	INT		LinkPos;						/*����Ǿ� �ִ� ���� �ε��� */
	TCHAR	upc_name[RDB_NAME64_SZ];		/*Value�� ���� MW ������ Ÿ�� �ʵ� �� */	
	TCHAR	upc_tlq[RDB_NAME64_SZ];			/*TLQ�� ���� MW ������ Ÿ�� �ʵ� �� */	
	TCHAR	upc_uptime[RDB_NAME64_SZ];		/*������ƮŸ�ӿ� ���� MW ������ Ÿ�� �ʵ� �� */	
	CHAR	Alarm;							/* �˶� ���� */	
	CHAR	Important;						/*�߿�/���߿� �˶� ���� 0=�̺�Ʈ ����, 1=�߿� �˶� */		
	CHAR	Terminal_DI;					/*1=������, 2=������*/	  
	INT		UnitSymbol;						/*���� */
	INT		MinMaxLimitSet;					/*��������ġ ID */
	CHAR	DateByteId;						/*�������� ID */  

} ST_COMMON_DNPAOMAPINDEX, *LPST_COMMON_DNPAOMAPINDEX;

//// Counter �� �ε���
typedef struct __stCommonDNPCOUNTERMapIndex__		
{       
	INT		MapId;							/*�� ID */
	INT		RTUMapId;						/*RTU�� ID */
	INT		LimitSetId;						/*LimitSEt Id*/
	INT		MeasureTypeID;					 /*�����ͺз� �ڵ� */
	SHORT	Position;						/*Counter_Index  */
	TCHAR	IndexName[RDB_NAME64_SZ];		/*Index �� */
	CHAR	CircuitNo;						/*ȸ�ι�ȣ */	
	TCHAR	Obj_Var[RDB_NAME32_SZ];			/*Object/Variation */	
	CHAR	Class;							/*Class ��ȣ */	
	CHAR	EMS;							/*EMS ���� ���� */	
	CHAR	GrpFlag;						/*�׷챸�� 0 = 1 index value, 1 = 2 index�� ��������,  2 = 2 index�� �������� */
	INT		LinkPos;						/*����Ǿ� �ִ� ���� �ε��� */
	TCHAR	upc_name[RDB_NAME64_SZ];		/*Value�� ���� MW ������ Ÿ�� �ʵ� �� */	
	TCHAR	upc_tlq[RDB_NAME64_SZ];			/*TLQ�� ���� MW ������ Ÿ�� �ʵ� �� */	
	TCHAR	upc_uptime[RDB_NAME64_SZ];		/*������ƮŸ�ӿ� ���� MW ������ Ÿ�� �ʵ� �� */	
	CHAR	Alarm;							/* �˶� ���� */	
	CHAR	Important;						/*�߿�/���߿� �˶� ���� 0=�̺�Ʈ ����, 1=�߿� �˶� */		
	CHAR	Terminal_DI;					/*1=������, 2=������*/	  
	//UINT	UnitSymbol;						/*���� */
	INT		MinMaxLimitSet;					/*��������ġ ID */

} ST_COMMON_DNPCOUNTERMAPINDEX, *LPST_COMMON_DNPCOUNTERMAPINDEX;

//// ������ ��� ����
typedef struct __stCommonRTUDevice__		
{       
	INT		RUID;							/*RTU ID */
	TCHAR	Name[RDB_NAME64_SZ];			/*RTU �̸� */
	INT		FEP_PROG_ID;					/*�Ҽ� ���α׷� Id*/
	INT		PRI_FEP;						/*�Ҽ� �� FEP ID */
	INT		BCK_FEP;						/*�Ҽ� ���� FEP ID  */
	INT		RTUMapId;						/*RTU Map ID */
	INT		EquipTypeId;					/*��ġ Ÿ�� */	
	INT		Protocol;						/*�������� ID */	
	INT		MasterDnp;						/*FEP DNP �ּ� */	
	SHORT	Dnp_Addr;						/*������ DNP �ּ� */	
	SHORT	BaudRate;						/*�ӵ� */
	CHAR	Control;						/* */
	CHAR	StopBit;						/* */	
	CHAR	Parity;							/* */	
	TCHAR	IP_Addr[RDB_NAME16_SZ];			/*���� IP */	
	INT	    Port;							/*LIU port */	
	INT		CommTypeId;						/*CommType id*/	  
	SHORT	Time_Sym_Hour;					/*�ð�����ȭ �ð�(0~24)*/
	CHAR	Use_SBO;						/*SBO ���(0=�̻��, 1=���) */
	CHAR	Use_Confirm;					/*���� ��� */
	INT		wave_comtypeId;					/*�������(1:���� DNP ���, 2:������(KDN) DNP+FTP, 3:���� FTP)*/
	CHAR	Datalink;						/*����Ǵ� ��� (0:RTU ����, 1:Datalink) */
	INT		FunGrpId;						/*Modbus ��ġ�� FunctionCode ����ID */
	TCHAR	RTUCompany[RDB_NAME40_SZ];		
	TCHAR	RTUSerialNo[RDB_NAME40_SZ];			
	TCHAR	RTUDate[RDB_NAME40_SZ];			
	TCHAR	DevCompany[RDB_NAME40_SZ];			
	TCHAR	DevSerialNo[RDB_NAME40_SZ];			
	TCHAR	DevDate[RDB_NAME40_SZ];			

} ST_COMMON_RTUDEVICE, *LPST_COMMON_RTUDEVICE;

//// ������ ����
typedef struct __stCommonConductingEquipment__		
{       
	INT		CEQID;							/*CEQ ID */
	INT		SSFK;							/*������ Id*/
	INT		DLFK;							/*DL ID */
	INT		PSRFK;							/*PSR ID  */
	INT		BVFK;							/*�������� ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];			/*m_RID FK */	
	TCHAR	Name[RDB_NAME64_SZ];			/*����� */	
	CHAR	Phase;							/*�󿬰����� */	
	INT		EQCFK;							/*EquipmentContainer Id */	
	INT		DpGrpFK;						/*����������Ʈ ��з�*/
	INT		DPGC_ACMFK;						/*ACM����Ʈ ��з�*/
	CHAR	CircuitNo;						/*ȸ�� ��ȣ */
	TCHAR	MeshNo[RDB_MESH22_SZ];			/*����ȭ ��ȣ */	
	INT		RUID;							/*RTU DEVICE ID - �����ξ� ���� 2014-03-04*/	
} ST_COMMON_CONDUCTINGEQUIPMENT, *LPST_COMMON_CONDUCTINGEQUIPMENT;

//// ����� ����
typedef struct __stCommonSwitch__		
{       
	INT		SWID;							 /*����ġ ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];			 /*mRIDFK Id*/
    TCHAR	name[RDB_NAME64_SZ];			 /*������ */	
	INT		CEQFK;							 /*CEQID  */	
	INT		CPSFK;							 /*CompositeSwitch ID  */
	//INT		BVFK;						 /*BaseVoltage ID */
	INT		PEQFK;							 /*ProtectEquipmentFK */
	INT		normalOpen;						 /*(1)���� (0)������ */	
	INT		SwitchType;						 /*EquipmentContainer Id */
	INT		SwitchType_ACM;						 
	INT		sourceACLSFK;					 /*������ ���� ���� */	
	INT		loadACLSFK;						 /*������ ���� ���� */	
	//INT		RDID;						 /*RTUDevice ID */
	INT		RatedCurrent;					 /*����������Ʈ ��з�*/
	INT		RatedCurrent_usfk;				 /*ȸ�� ��ȣ */
	INT		NormallyService;				 /*����ȭ ��ȣ */	
	TCHAR	Switch_no[RDB_NAME64_SZ];		 /*��� ��ȣ */	

} ST_COMMON_SWITCH, *LPST_COMMON_SWITCH;

//// ���� ����
typedef struct __stCommonACLineSegment__		
{       
	INT		ACID;							/*���α��� ID */
	INT		CEQFK;							/*CEQ Id*/	
	INT		PLSIFK;							/*PERLengthSegmentImpedence ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];			/*mRIDFK ID */	
	TCHAR	Name[RDB_NAME64_SZ];			/*���� ��*/	
	FLOAT	length;							/*����            */
	INT		length_usfk;					/*UnitSymbol      */
	CHAR	phases;							/*�󿬰�����      */

} ST_COMMON_ACLINESEGMENT, *LPST_COMMON_ACLINESEGMENT;

// ���� ����
typedef struct __stPDBPerLengthSequenceImpedance__
{
	INT		PLSIID;							/*PerLengthSequenceImpedancd ID		*/
	INT		PSRTypeFK;						/*PSRType ID						*/
	TCHAR	mRIDFK[RDB_NAME64_SZ];			/*DistributionLineSegment Name		*/
	TCHAR	Name3P[RDB_NAME64_SZ];			/*DistributionLineSegment AliasName	*/
	TCHAR	NameN[RDB_NAME64_SZ];			/*DistributionLineSegment AliasName	*/
	FLOAT	b0ch;							/* �����Ͻ� ����� */
	INT		b0ch_usfk;						/*UnitSymbol      */
	FLOAT	bch;							/* �����Ͻ� */
	INT		bch_usfk;						/*UnitSymbol      */
	FLOAT	g0ch;							/* �����Ͻ� ����� */
	INT		g0ch_usfk;						/*UnitSymbol      */
	FLOAT	gch;							/* �����Ͻ� */
	INT		gch_usfk;						/*UnitSymbol      */
	FLOAT	r;								/* ���� ����� */
	INT		r_us_fk;						/*UnitSymbol      */                       
	FLOAT	r0;								/* ���� */
	INT		r0_us_fk;						/*UnitSymbol      */                       
	FLOAT	x;								/* �����Ͻ� ����� */
	INT		x_us_fk;						/*UnitSymbol      */                       
	FLOAT	x0;								/* �����Ͻ� ����� */
	INT		x0_us_fk;						/*UnitSymbol      */ 
	FLOAT	thermalLimit;					/*���� ���� ����   */
	INT		thermalLimit_us_fk;				/*UnitSymbol      */
	FLOAT	ETLimit;						/*���ÿ��� ����  */
	INT		ETLimit_us_fk;					/*UnitSymbol      */

} ST_COMMON_PERLENGTHSEQUENCEIMPEDANCE, *LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE;

//// ������ �� BUSBARSECTION ����ǥ��
typedef struct __stCommonBusbarSection__		
{       
	INT		BusId;							/*busbarsection ID */
	INT		VLFK;							/*voltage Level Id*/
	INT		CEQFK;							/*CEQID FK */	
	TCHAR	mRIDFK[RDB_NAME64_SZ];			/*mRIDFK ID */	
	TCHAR	Name[RDB_NAME64_SZ];			/*busbarsection ��*/	
	CHAR	busorder;						/*BusbarSection Order 1��/2��*/	

} ST_COMMON_BUSBARSECTION, *LPST_COMMON_BUSBARSECTION;

//// ��ȸ�� ����
typedef struct __stCommonCompositeSwitch__		
{       
	INT		CPSID;							/*��ȸ�μ��� ID */	
	INT		PSRFK;							/*PSR Id*/
	INT		EQCFK;							/*EquipmentContainer FK */
	TCHAR	mRIDFK[RDB_NAME64_SZ];			/*mRIDFK ID */	
	TCHAR	Name[RDB_NAME64_SZ];			/*��ȸ�� �����*/	

} ST_COMMON_COMPOSITESWITCH, *LPST_COMMON_COMPOSITESWITCH;

//// ���б�
typedef struct __stCommonPowerTransformer__		
{       
	INT		PTRID;                            /*��ȸ�μ��� ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];            /*mRIDFK ID */		
	TCHAR	Name[RDB_NAME64_SZ];              /*��ȸ�� �����*/	
	INT		PSRFK;							  /*PSR ID */
	INT		EQCFK;                            /*EquipmentContainer FK */	
	SHORT	bankNo;                           /*��ũ��ȣ*/
	FLOAT	bmagSat;                          /*��ȭ�������� ö�� ���� ��ȭ �����Ͻ� �ۼ�Ʈ*/	
	INT		bmagSet_usfk;                     /*����*/
	FLOAT	magBasekV;                        /**/
	INT		magBasekV_usfk;                   /*����*/
	FLOAT	magSatFlux;                       /**/
	INT		magSatFlux_usfk;                  /*����*/
	INT		Phase;                            /*���� ID*/
	SHORT	transCoolingType;				  /*���б� �ð��� ����*/						
	SHORT	transformerType;				  /*���б� ����*/

} ST_COMMON_POWERTRANSFORMER, *LPST_COMMON_POWERTRANSFORMER;

//// Tap �����
typedef struct __stCommonTapChanger__		
{       
	INT		TCID;                              /*Tap ����� ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];             /*IdentifiedObject    */
	TCHAR	Name[RDB_NAME64_SZ];               /*�̸�                */	
	INT		PSRTYFK;                           /*PSRTYpe FK */	
	INT		highStep;                          /*�� ����ġ*/	
	INT		lowSetp;                           /*�� ����ġ*/
	INT		neutralStep;                       /*�� �߼���*/
	INT		normalStep;                        /*�� ��ġ*/
	FLOAT	SVI;                               /*�ǰ� ��ȭ��*/
	UINT	SVI_usfk;                          /*����*/
	SHORT	tculControlMode;                   /*�� ����� ������ 0: off, 1: Local, 2: Voltage, 3: MVAr*/

} ST_COMMON_TAPCHANGER, *LPST_COMMON_TAPCHANGER;

//// ���б� �ἱ
typedef struct __stCommonTransformerWiding__		
{       
	INT		TRWID;                             /*���б� ID           */
	INT		PTRFK;                             /*PowerTransformer    */
	INT		CEQFK;                             /*ConductingEquipment */
	TCHAR	mRIDFK[RDB_NAME64_SZ];			   /*IdentifiedObject    */
	TCHAR	Name[RDB_NAME64_SZ];               /*�̸�                */
	//INT	BVFK;                              /*BaseVoltage         */	
	//UINT	ECFK;                              /*EquipmentContainer  */
	//UINT	PSRTYFK;                           /*PSRType             */
	//INT	TCHGFK;							   /*TapChanger          */
	CHAR	connectionType;                    /*�ἱ���            */
	CHAR	windingType;                       /*                    */
	FLOAT	r;                                 /*����                */
	INT		r_usfk;                            /*UnitSymbol          */	
	FLOAT	r0;                                /*��������            */
	INT		r0_usfk;                           /*UnitSymbol          */
	FLOAT	x;                                 /*�����Ͻ�            */
	CHAR	x_usfk;                            /*UnitSymbol          */
	FLOAT	x0;                                /*���󸮾��Ͻ�        */
	INT		x0_usfk;                           /*UnitSymbol          */
	CHAR	grounded;                          /*                    */
	FLOAT	rground;                           /*��������            */
	INT		rground_usfk;                      /*UnitSymbol          */
	FLOAT	xground;                           /*���������Ͻ�        */
	INT		xground_usfk;                      /*UnitSymbol          */
	FLOAT	ratedKV;                           /*UnitSymbol          */
	CHAR	ratedKV_usfk;                      /*UnitSymbol          */
	FLOAT	ratedMVA;                          /*���ݿ뷮            */
	INT		ratedMVA_usfk;                     /*UnitSymbol          */
	FLOAT	eMVA;                              /*������ �뷮       */
	INT		eMVA_usfk;                         /*UnitSymbol          */
	INT		TCFK;

} ST_COMMON_TRANSFORMERWINDING, *LPST_COMMON_TRANSFORMERWINDING;
  

//// Tap ���� ������
typedef struct __stCommonTapRegulationSchedule__		
{       
	INT		TRSCID;                             /*Tap ����� ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];				/*IdentifiedObject    */
	INT		TCFK;								/*TapChangerFK	*/	
	TCHAR	Name[RDB_NAME64_SZ];				/*�̸�                */
	INT		AVR;								/*���� ���� ���	*/	
	FLOAT	PATBSVL;                            /*���� ����� A�� ���� ��ǥġ*/
	INT		PATBSVL_usfk;                       /*Unit Symbol */	
	FLOAT	PADEV;								/*���� ����� A�� ���� ��ǥġ ����*/
	INT		PADEV_usfk;							/*Unit Symbol*/
	FLOAT	PBTBSVL;                            /*���� ����� B�� ���� ��ǥġ*/
	INT		PBTBSVL_usfk;                       /*Unit Symbol */	
	FLOAT	PBDEV;								/*���� ����� B�� ���� ��ǥġ ����*/
	INT		PBDEV_usfk;							/*Unit Symbol*/
	FLOAT	PCTBSVL;                            /*���� ����� C�� ���� ��ǥġ*/
	INT		PCTBSVL_usfk;                       /*Unit Symbol */	
	FLOAT	PCDEV;								/*���� ����� C�� ���� ��ǥġ ����*/
	INT		PCDEV_usfk;							/*Unit Symbol*/
	INT		VVOFLAG;							/*VVO ���� ���� ����*/
	INT		CON3P;								/*3�� �ϰ����� ����*/
	INT		IIPFVM;
	FLOAT	PACOMPR;							/*A�� compensator R*/
	FLOAT	PACOMPX;							/*A�� compensator X*/
	FLOAT	PBCOMPR;							/*B�� compensator R*/
	FLOAT	PBCOMPX;							/*B�� compensator X*/
	FLOAT	PCCOMPR;							/*C�� compensator R*/
	FLOAT	PCCOMPX;							/*C�� compensator X*/
	INT		CONMEAP3;							/*3�� ���� TR�� LDC  ���� ����*/
	FLOAT	PATAPCOST;							
	FLOAT	PACONTAPMX;
	FLOAT	PBTAPCOST;
	FLOAT	PBCONTAPMX;
	FLOAT	PCTAPCOST;
	FLOAT	PCCONTAPMX;
	INT		PACONTAPMXDAY;						/*A�� �Ϸ� �ִ� ����Ƚ��*/
	INT		PATAPOPDAY;							/*A�� �Ϸ� ����Ƚ��*/
	INT		PBCONTAPMXDAY;						/*B�� �Ϸ� �ִ� ����Ƚ��*/
	INT		PBTAPOPDAY;							/*B�� �Ϸ� ����Ƚ��*/
	INT		PCCONTAPMXDAY;						/*C�� �Ϸ� �ִ� ����Ƚ��*/
	INT		PCTAPOPDAY;							/*C�� �Ϸ� ����Ƚ��*/

} ST_COMMON_TAPREGULATIONSCHEDULE, *LPST_COMMON_TAPREGULATIONSCHEDULE;

//// ��ȣ����
typedef struct __stCommonProtectionEquipment__		
{       
	INT		PEQID;								 /*ProtectionEquipment ID */
	TCHAR	mRIDFK[RDB_NAME64_SZ];				 /*IdentifiedObject       */
	TCHAR	Name[RDB_NAME64_SZ];				 /*�̸�                   */
	//INT		RSFK;							 /*RecloseSequence        */
	//INT		CRFK;							 /*CurrentRelay           */
	SHORT	EquipmentType;						 /*                       */
	SHORT	DIRTYPE;                             /*��ȣ��� ���⼺ ����   */
	INT		CTRATIO;                             /*��ȣ ����� �⺻ CT �� */
	TCHAR	Manufacture[RDB_NAME32_SZ];			 /*���ۻ� �̸�            */
	SHORT	RecloserType;						 /*��Ŭ���� Type          */

} ST_COMMON_PROTECTIONEQUIPMENT, *LPST_COMMON_PROTECTIONEQUIPMENT;

//// ����ν�����
typedef struct __stCommonRecloseSequence__		
{       
	INT		RSID;                              /*RecloseSequence ID  */	
	TCHAR	mRIDFK[RDB_NAME64_SZ];             /*IdentifiedObject    */
	INT		PEQFK;							   /*ProtectionEquipment ID */
	TCHAR	Name[RDB_NAME64_SZ];               /*�̸�                */
	FLOAT	RecloseDelay;                      /*Dead Time           */
	INT		RecloseDelay_usfk;                 /*UnitSymbol          */
	INT		recloseStep;                       /*                    */

} ST_COMMON_RECLOSESEQUENCE, *LPST_COMMON_RECLOSESEQUENCE;

//// ������
typedef struct __stCommonCurrentRelay__		
{       
	INT		CRID;                        /*CurrentRelay ID         */
	TCHAR	mRIDFK[RDB_NAME64_SZ];       /*IdentifiedObject        */
	TCHAR	Name[RDB_NAME64_SZ];         /*�̸�                    */
	INT		PEQFK;						 /*ProtectionEquipment ID */
	INT		OCR_MCODEFK;                 /*Machine Code            */
	INT		OCGR_MCODEFK;                /*Machine Code            */
	INT		TAPCHOICE;                   /*�ѽ� Tap ������� (��)  */
	INT		LEVERSTAP;                   /*Time Lever Step (��)    */
	INT		RECTMPAA;                    /*Relay ���ͽð� ���     */
	INT		RECTMPAB;                    /*Relay ���ͽð� ���     */
	INT		RECTMPAC;                    /* Relay ���ͽð� ���    */
	INT		GROUNDTAPCHOICE;             /*�ѽ� Tap ������� (����)*/
	INT		GROUNDLEVERSTAP;             /*Time Lever Step (����)  */

} ST_COMMON_CURRENTRELAY, *LPST_COMMON_CURRENTRELAY;
     
//// ������ ������ġ
typedef struct __stCommonBatteryStorage__		
{       
	INT			BATTID;                       /*BatteryStorage ID   */
	INT			GENFK;                        /*GeneratingUnit      */
	TCHAR		mRIDFK[RDB_NAME64_SZ];        /*IdentifiedObject    */
	TCHAR		Name[RDB_NAME64_SZ];          /*�̸�                */
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
                                         
//// ������ �Ǵ� ������
typedef struct __stCommonGeneratingUnit__		
{                                                           
	INT		GENID;                      /*GeneratingUnit ID    */
	INT		CEQFK;                      /*ConductingEquipment  */
	//INT    EQCFK;                     /*EquipmentContainer   */
	//INT		GRSHFK;                 /*GenRegulationSchedule*/
	TCHAR   mRIDFK[RDB_NAME64_SZ];      /*IdentifiedObject     */
	TCHAR   Name[RDB_NAME64_SZ];        /*�̸�                 */
	//INT		BVFK;                   /*BaseVoltage  - �����ξ� ���� */
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
	FLOAT   genTX;                      /*��������������Ͻ�(1)*/
	INT		genTX_usfk;                 /*UnitSymbol           */
	FLOAT   genSSX;                     /*���������󸮾��Ͻ�(1)*/
	INT		genSSX_usfk;                /*UnitSymbol           */
	FLOAT   genZERX;                    /*�����⿵�󸮾��Ͻ�(1)*/
	INT		genZERX_usfk;               /*UnitSymbol           */
	FLOAT   baseMVA;                    /*���ݿ뷮             */
	INT		baseMVA_usfk;               /*UnitSymbol           */
	TCHAR   TEL[RDB_NAME64_SZ];			/*��ȭ��ȣ(02-)        */
	FLOAT   efficiency;                 /*ȿ��                 */
	INT		efficiency_usfk;            /*UnitSymbol           */
	FLOAT   normalPF;                   /*����                 */
	INT		normalPF_usfk;              /*UnitSymbol           */
	FLOAT   Pole;                       /*�ؼ�                 */
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

//// ���º�ȯ��ġ
typedef struct __stCommonGenRegulationSchedule__		
{                                                               
	INT     RSCID;                      /*RegulationSchedule ID     */
	TCHAR   mRIDFK[RDB_NAME64_SZ];      /*FK, IdentifiedObject      */
	TCHAR   Name[RDB_NAME64_SZ];        /*�̸�                      */
	INT		GENFK;						/*GeneratingUnit FK			*/
	INT     AVR;                        /*�ڵ����� ���� ��������(1: ����, 0: ��������) */
	FLOAT   TBSVL;                      /*���� ���� ���� ��ǥġ   */
	INT		TBSVL_usfk;                 /*UnitSymbol                */
	FLOAT   DEV;                        /*���� �� A���� ���� ��ǥġ ����*/
	INT     DEV_usfk;                   /*UnitSymbol                */
	FLOAT   PF;                         /*������� ���� ���� ��ǥġ*/
	INT     PF_usfk;                    /*UnitSymbol                */
	FLOAT   FLTContribution;            /*����⿩��(�ι��� ������) */
	INT     FLTContribution_usfk;       /*UnitSymbol                */
	INT     VVOFLAG;                    /*������ ��ȿ���� ��� VVO ��������(0: ����, 1: ����)*/
	INT     MVARCONMODE;                /*��ȿ���� ������(1:����, 2:����, 3: ������ȿ����)*/
	FLOAT   OUTQ;                       /*���� ��ȿ���� ���� ����� �������� ��ȿ���� ��ǥġ*/
	INT     OUTQ_usfk;                  /*UnitSymbol                */
	FLOAT   PFVVOMINLAG;                /*VVO ����� ������ �ּ� ���� ���� */
	INT     PFVVOMINLAG_usfk;           /*UnitSymbol                       */
	FLOAT   PFVVOMINLEAD;               /*VO ����� ������ �ּ� ���� ����  */
	INT     PFVVOMINLEAD_usfk;          /*UnitSymbol                */

} ST_COMMON_GENREGULATIONSCHEDULE, *LPST_COMMON_GENREGULATIONSCHEDULE;

//// ǳ�� �л�����
typedef struct __stCommonWindTurbine__		
{                                                                                                       
	INT		WTID;                    /*WindTurbine ID                                                     */
	INT		GENFK;                   /*GeneratingUnit FK                                                  */
	TCHAR   mRIDFK[RDB_NAME64_SZ];   /*IdentifiedObject                                                   */
	TCHAR   Name[RDB_NAME64_SZ];     /*�̸�                                                               */
	FLOAT	LENGTH;                  /*���̵� ����                                                      */
	INT		LENGTH_usfk;             /*UnitSymbol                                                         */
	FLOAT	HEIGHT;                  /*ȸ���� ����                                                        */
	INT		HEIGHT_usfk;             /*UnitSymbol                                                         */
	FLOAT	ALTITUDE;                /*�ع߰�                                                           */
	INT		ALTITUDE_usfk;           /*UnitSymbol                                                         */
	INT		WINDDIR;                 /*ǳ��                                                               */
	INT		WINDREVERSE;             /*��ǳ�� �������ɿ���                                                */	
	FLOAT   LAT;					 /*ǳ�¹����� ����													  */		
	INT     LAT_USFK;				 /*ǳ�¹����� ���� ����												  */
	FLOAT   LONG;					 /*ǳ�¹����� �浵													  */		
	INT     LONG_USFK;				 /*ǳ�¹����� �浵 ����												  */
	FLOAT   ALT;					 /*ǳ�¹����� �ع߰�												  */		
	INT     ALT_USFK;				 /*ǳ�¹����� �ع߰� ����											  */

} ST_COMMON_WINDTURBINE, *LPST_COMMON_WINDTURBINE;

//// �¾籤 �л�����
typedef struct __stCommonPhotoVoltaic__		
{                                                                                                   
	INT    PVID;                     /*PhotoVoltaic ID                                                    */
	INT    GENFK;                    /*GeneratingUnit FK                                                  */
	TCHAR  mRIDFK[RDB_NAME64_SZ];    /*IdentifiedObject                                                   */
	TCHAR  Name[RDB_NAME64_SZ];      /*�̸�                                                               */
	FLOAT  SIZE;                     /*�¾籤 ��� 1���� ����(m2)                                         */
	INT    SIZE_usfk;                /*UnitSymbol                                                         */
	FLOAT  EFF;                      /*��⺰ ȿ��                                                        */
	INT    EFF_usfk;                 /*UnitSymbol                                                         */
	INT    NOOFMD;                   /*��� ����                                                          */
	FLOAT  LAT;						 /*�¾籤 ����														  */		
	INT    LAT_USFK;				 /*�¾籤 ���� ����													  */
	FLOAT  LONG;					 /*�¾籤 �浵														  */		
	INT    LONG_USFK;				 /*�¾籤 �浵 ����													  */
	FLOAT  ALT;						 /*�¾籤 �ع߰�													  */		
	INT    ALT_USFK;				 /*�¾籤 �ع߰� ����												  */

} ST_COMMON_PHOTOVOLTAIC, *LPST_COMMON_PHOTOVOLTAIC;

//// ������ ����� �
typedef struct __stCommonGenUnitOpCostCurve__		
{                                                                                            
	INT		  GUOCCID;                /*GenUnitOpCostCurve ID                                         */
	INT		  GENFK;                   /*GeneratingUnit                                                */
	TCHAR	  GENCSTCUR_TYPE[RDB_NAME32_SZ];         /*������ ����Լ� ����                                          */
	INT		  GENCSTCUR_COEF1;        /*2����� ���                                              */
	INT		  GENCSTCUR_COEF2;        /*2����� ���                                              */
	INT       GENCSTCUR_CONST;        /*2����� ���                                              */	
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

//// ��м��밡
typedef struct __stCommonEnergyConsumer__		
{                                                                   
	INT		ECRID;                        /*EnergyConsumer ID                            */
	INT		ACLSFK;                        /*ACLineSegment                                */
	INT		CEQFK;                        /*ConductingEquipment                          */
	TCHAR   mRIDFK[RDB_NAME64_SZ];        /*IdentifiedObject                             */
	TCHAR   Name[RDB_NAME64_SZ];          /*�̸�                                         */
	INT		customerCount;                /*����(1)                                    */
	FLOAT	pfixed;                       /*�������P(100KW)                             */
	INT		pfixed_usfk;                  /*UnitSymbol                                   */
	FLOAT	qfixed;                       /*�������Q(100Kvar)                           */
	INT		qfixed_usfk;                  /*UnitSymbol                                   */
	TCHAR   Tel[RDB_NAME20_SZ];           /*��ȭ��ȣ(02-)                                */
	TCHAR   HP[RDB_NAME20_SZ];            /*�ڵ�����ȣ(010-)                             */
	TCHAR   Customer_key[RDB_NAME20_SZ];  /*Custermer Key(80-)                           */
	INT     Priority;                     /*�߿䵵(1)                                    */
	CHAR    SmsUse;                       /*SMS(0: ������, 1: ���)                    */
	INT		WATFK;						  /*Water���� ����Ű							 */
	FLOAT   LoadDiv;
	INT		LoadMea;
	FLOAT	LoadCapMW;
	FLOAT	LoadCapMVAR;

} ST_COMMON_ENERGYCONSUMER, *LPST_COMMON_ENERGYCONSUMER;

//// ���� ����������
typedef struct __stCommonShuntCompasator__		
{                                                                   
	INT     SCID;                          /*ShuntCompansator ID                          */
	INT     CEQFK;                         /*ConductingEquipment                          */
	TCHAR   mRIDFK[RDB_NAME64_SZ];         /*IdentifiedObject                             */
	TCHAR   Name[RDB_NAME64_SZ];           /*�̸�                                         */
	//INT     BVFK;                          /*BaseVoltage                                  */
    FLOAT   NominalMVAr;                   /*���� ���                                    */
	INT     NominalMVAr_usfk;              /*UnitSymbol                                   */

} ST_COMMON_SHUNTCOMPASATOR, *LPST_COMMON_SHUNTCOMPASATOR;

//// ��ȿ���� ������ġ
typedef struct __stCommonStaticVarCompensator__		
{                                                                                      
	INT     SVCID;                         /*ShuntCompansator ID                          */
	INT     CEQFK;                         /*ConductingEquipment                          */
	TCHAR   mRIDFK[RDB_NAME64_SZ];         /*IdentifiedObject                             */
	TCHAR   Name[RDB_NAME64_SZ];           /*�̸�                                         */
	FLOAT   capacitiveRating;              /*�ִ� ���� ĳ�н��� ��ȿ����                  */
	INT     capacitiveRating_usfk;         /*UnitSymbol                                   */
	FLOAT   inductiveRating;               /*�ִ� ���� �δ��� ��ȿ����                    */
	INT		inductiveRating_usfk;          /*UnitSymbol                                   */
	INT		slope;                         /*Ư�� ����                                  */	
	INT		SVCControlMode;                /*SVR Control mode                             */
	FLOAT	VoltageSetPoint;               /*Voltage Set Point                            */
	INT		VoltageSetPoint_usfk;          /*UnitSymbol                                   */
	INT		BaNo;                          /*��ũ ��ȣ                                    */ 

} ST_COMMON_STATICVARCOMPENSATOR, *LPST_COMMON_STATICVARCOMPENSATOR;

//// ���� �� ���հ����� ����
typedef struct __stCommonPowerSystemResource__		
{                                                                        
	INT	    PSRID;						/*PointID                 */
	INT	    PSRTYPEFK;					/*PSRTYPE ID              */
	TCHAR   mRIDFK[RDB_NAME64_SZ];		/*Identified Object       */
	TCHAR   Name[RDB_NAME64_SZ];		/*�̸�                    */

} ST_COMMON_POWERSYSTEMRESOURCE, *LPST_COMMON_POWERSYSTEMRESOURCE;

//// Power System Resource�� ����
typedef struct __stCommonPSRType__		
{                                                                        
	INT     PSRTYPEID;					/*PointID                 */
	TCHAR   mRIDFK[RDB_NAME64_SZ];		/*Identified Object       */
	TCHAR   Name[RDB_NAME64_SZ];		/*�̸�                    */
	TCHAR   mRCode[RDB_NAME16_SZ];		/*PointID                 */
	INT     symbolfk;					/*�ɺ�					  */

} ST_COMMON_PSRTYPE, *LPST_COMMON_PSRTYPE;

//// ���հ���
typedef struct __stCommonEquipmentContainer__		
{                                                                        
	INT     EQCID;						/*PointID					*/
	INT     SGRFK;						/*SubGeographical Region ID */
	TCHAR   mRIDFK[RDB_NAME64_SZ];		/*Identified Object       */
	TCHAR   Name[RDB_NAME64_SZ];		/*�̸�                    */
	//UINT    mRCode;					/*mRCode prefix           */
	INT     PSRFK;						/*PSR ID				  */
} ST_COMMON_EQUIPMENTCONTAINER, *LPST_COMMON_EQUIPMENTCONTAINER;

//// �ɺ�
typedef struct __stCommonSymbol__		
{                                                                        
	INT     SYMBOLID;						/*�ɺ� ���̵�			*/
	TCHAR   NAME[RDB_NAME64_SZ];			/*�ɺ� �̸�				*/
	TCHAR   FILENAME[RDB_NAME64_SZ];		/*���� ��			    */
	INT     FILESIZE;						/*���� ������			*/

} ST_COMMON_SYMBOL, *LPST_COMMON_SYMBOL;


//// ���뵵 ������ �������� ���̺�
typedef struct __stCommonDASDIAGRAMINFO__		
{                                                                        
	INT     DAS_DIAID;						/*���� ���̵�			*/
	TCHAR   NAME[RDB_NAME64_SZ];			/*���� �̸�				*/
	TCHAR	VERSION[RDB_NAME16_SZ];			/*���� ����				*/
	TCHAR	EDITOR[RDB_NAME16_SZ];			/*���� �ۼ���			*/
	TCHAR	BUILDTIME[RDB_DATETIME25_SZ];	/*���� �ۼ�����			*/
	TCHAR   FILENAME[RDB_NAME64_SZ];		/*���� �̸�			    */
	INT     FILESIZE;						/*���� ������			*/

} ST_COMMON_DASDIAGRAMINFO, *LPST_COMMON_DASDIAGRAMINFO;

//// ���뵵 ������ �������� ���̺�
typedef struct __stCommonSTATIONDIAGRAMINFO__		
{                                                                        
	INT		STATIONDIAID;					/*���� ���̵�			*/
	TCHAR   NAME[RDB_NAME64_SZ];			/*���� �̸�				*/	
	TCHAR	VERSION[RDB_NAME16_SZ];			/*���� ����				*/
	TCHAR	EDITOR[RDB_NAME16_SZ];			/*���� �ۼ���			*/
	TCHAR	BUILDTIME[RDB_DATETIME25_SZ];	/*���� �ۼ�����			*/
	TCHAR   FILENAME[RDB_NAME64_SZ];		/*���� �̸�			    */
	INT     FILESIZE;						/*���� ������			*/

} ST_COMMON_STATIONDIAGRAMINFO, *LPST_COMMON_STATIONDIAGRAMINFO;

//// ���� ����Ʈ ����
typedef struct __stCommonDiscrete__		
{                                                                        
	INT    PID;                    /*PointID                        */
	TCHAR  mRIDFK[RDB_NAME64_SZ];  /*Identified Object       */
	TCHAR  Name[RDB_NAME64_SZ];    /*SW_��������                    */
	INT    SSId;                   /*������ ID                      */
	INT    DLId;                   /*D/L ID                         */
	INT    CEQId;                  /*CEQID                          */
	INT    RUID;                   /*RemoteUnit ID                  */
	INT    MeasureTypeID;			/*����Ʈ �з�                    */
	INT    TMId;                   /*Terminal ID                    */
	INT    StateGrpId;             /*���±׷�                       */
	INT    CommandID;              /*����                           */
	CHAR   NormalVal;              /*���� ��                        */
	CHAR   AbnormalVal;            /*������ ��                      */
	CHAR   Initval;                /*�ʱ� ��                        */ 
	SHORT  Position;               /*IndexNo                        */
	CHAR   CircuitNo;              /*ȸ�ι�ȣ                       */

} ST_COMMON_DISCRETE, *LPST_COMMON_DISCRETE;

//// ���� ����Ʈ ����
typedef struct __stCommonSetDiscrete__		
{                                                                        
	INT		PID;                    /*PointID                        */
	TCHAR   mRIDFK[RDB_NAME64_SZ];	/*Identified Object				 */
	TCHAR	Name[RDB_NAME64_SZ];    /*SW_��������                    */
	INT		SSId;                   /*������ ID                      */
	INT		DLId;                   /*D/L ID                         */
	INT		CEQId;                  /*CEQID                          */
	INT		RUID;                   /*RemoteUnit ID                  */
	INT     MeasureTypeID;			/*����Ʈ �з�                    */
	INT		TMId;                   /*Terminal ID                    */
	INT		StateGrpId;             /*���±׷�                       */
	//INT		DiscreteId;         /*����                           */
	//CHAR    Initval;              /*�ʱ� ��                        */ 
	SHORT    Position;              /*IndexNo                        */
	CHAR    CircuitNo;              /*ȸ�ι�ȣ                       */

} ST_COMMON_SETDISCRETE, *LPST_COMMON_SETDISCRETE;

//// ���� ����Ʈ ����
typedef struct __stCommonMeasurement__		
{                                                                       
	INT     PID;                    /*PointID                       */
	TCHAR   mRIDFK[RDB_NAME64_SZ];	/*Identified Object       */
	TCHAR   Name[RDB_NAME64_SZ];    /*SW_��������                    */
	INT		SSId;                   /*������ ID                      */
	INT		DLId;                   /*D/L ID                         */
	INT		CEQId;                  /*CEQ ID                         */
	INT		RUID;                   /*RemoteUnit ID                  */
	INT     MeasureTypeID;			/*����Ʈ �з�                    */
	INT		TMId;                   /*Terminal ID                    */
	INT		UnitId;                 /*����                          */
	INT		RLS_FK;                 /*Max/Min Range LimitSet ID      */
	INT		LS_FK;                  /*High/Low LimitSet ID          */ 
	INT		SF_FK;                  /*Sclae Factor ID               */
	FLOAT   InitVal;                /*�ʱ� ��                        */ 
	SHORT   Position;               /*IndexNo                       */
	CHAR    CircuitNo;              /*ȸ�ι�ȣ                       */	

} ST_COMMON_MEASUREMENT, *LPST_COMMON_MEASUREMENT;

//// ���� ����Ʈ ����
typedef struct __stCommonSetMeasurement__		
{                                                                       
	INT    PID;                    /*PointID                        */
	TCHAR  mRIDFK[RDB_NAME64_SZ];  /*Identified Object       */
	TCHAR  Name[RDB_NAME64_SZ];    /*SW_��������                    */
	INT    SSId;                   /*������ ID                      */
	INT    DLId;                   /*D/L ID                         */
	INT    CEQId;                  /*CEQ ID                         */
	INT    RUID;                   /*RemoteUnit ID                  */
	INT    MeasureTypeID;          /*����Ʈ �з�                    */
	INT	   StateGrpId;			   /*state Group Id					*/
	INT    TMId;                   /*Terminal ID                    */
	INT    UnitID;                 /*����                           */
	INT    RLS_FK;                 /*High/Low LimitSet ID          */ 
	INT    SF_FK;                  /*Sclae Factor ID               */
	FLOAT  NormalValue;            /*���� ��                        */ 
	FLOAT  StepValue;			   /*���� ��                        */ 
	SHORT  Position;               /*IndexNo                        */
	CHAR   CircuitNo;              /*ȸ�ι�ȣ                       */	

} ST_COMMON_SETMEASUREMENT, *LPST_COMMON_SETMEASUREMENT;

//// ī���� ����Ʈ ����
typedef struct __stCommonAccumulator__		
{                                                                       
	INT		PID;                    /*PointID                        */
	TCHAR   mRIDFK[RDB_NAME64_SZ];	/*Identified Object       */
	TCHAR	Name[RDB_NAME64_SZ];    /*SW_��������                    */
	INT		SSId;                   /*������ ID                      */
	INT		DLId;                   /*D/L ID                         */
	INT		CEQId;                  /*CEQ ID                         */
	INT		RUID;                   /*RemoteUnit ID                  */
	INT     MeasureTypeID;			/*����Ʈ �з�                    */
	INT		TMId;                   /*Terminal ID                    */
	//INT		UnitID;             /*����                           */
	INT		RLS_FK;                 /*Max/Min Range LimitSet ID      */
	INT		LS_FK;                  /*High/Low LimitSet ID          */ 
	//INT		SF_FK;              /*Sclae Factor ID               */
	//FLOAT   InitVal;              /*�ʱ� ��                        */ 
	SHORT    Position;              /*IndexNo                        */
	CHAR    CircuitNo;              /*ȸ�ι�ȣ                       */	
} ST_COMMON_ACCUMULATOR, *LPST_COMMON_ACCUMULATOR;

//// ��� ����Ʈ ����
typedef struct __stCommonCalculation__		
{                                                                       
	INT		PID;                      /*PointID                        */
	TCHAR   mRIDFK[RDB_NAME64_SZ];	  /*Identified Object			   */
	TCHAR   Name[RDB_NAME64_SZ];      /*SW_��������                    */	
	INT		DpGrpFK;				  /*����������Ʈ ��з�			   */
	INT		UnitID;                   /*����                           */	 
	TCHAR   formular[RDB_NAME256_SZ]; /*����                         */
	CHAR    degree;                   /*�켱����                       */
	CHAR    interval;                 /*����ֱ�                       */	
	CHAR    Alarm;                    /*Alarm ����                     */
	CHAR    Important;                /*�߿䵵                         */

} ST_COMMON_CALCULATION, *LPST_COMMON_CALCULATION;

//// ���뵵 ���� ���� ����Ʈ
typedef struct __stCommonPosition__		
{                                                                       
	INT		PositionID;               /* PointID                    */	
	TCHAR   NAME[RDB_NAME64_SZ];      /* �����                     */
	INT		PSRFK;				      /* PowerSystemResource ID     */
	INT		POSITIONX;				  /* X�� ��ǥ ����				*/
	INT		POSITONY;				  /* Y�� ��ǥ ����				*/
	INT		Order;					  /*�������� ����				*/

} ST_COMMON_POSITION, *LPST_COMMON_POSITION;

//// Water ���� ���� ����Ʈ
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

//// ���󼱷� ��Ȱ�� ó��
typedef struct __stCommonVirtual_Line_
{                                                   
	INT		VirtualLineCEQID;								 /*���󼱷� CEQID                     */
	INT		ReferenceLineCEQID;								 /*��Ȱ������ ����  CEQID             */
	INT		ReferenceRTUCEQID;								 /*��Ȱ������ ����ġ CEQID            */
	INT		DLID;											 /*���󼱷��� DL					  */

} ST_COMMON_VIRTUAL_LINE, *LPST_COMMON_VIRTUAL_LINE;

//// �޸� ����
typedef struct __stOprMemo_
{   
	INT		MMID;                            /*PID                         */
	TCHAR	CREATE_TIME[RDB_DATETIME25_SZ];	 /*�����ð�                    */
	INT		SSFK;							 /*������ �̸�                 */
	INT		DLFK;							 /*DL �̸�                     */
	INT		CEQFK;							 /*���ֹ�ȣ                    */
	INT		USERID_FK;                       /*�ۼ��� ID                   */
	TCHAR   CONTENTS[RDB_CONTENT512_SZ];     /*����                        */

} ST_OPR_MEMO, *LPST_OPR_MEMO;

//// �������� ����
typedef struct __stOprMessage_
{   
	INT		MSGID;								/*PID                         */
	TCHAR    CREATE_TIME[RDB_DATETIME25_SZ];	/*�����ð�                    */
	CHAR    MSG_TYPE;						    /*�޽��� ���� (1=���, 2=����) */
	INT		USERID_FK;                          /*�ۼ��� ID                   */
	TCHAR   CONTENTS[RDB_CONTENT512_SZ];        /*����                        */

} ST_OPR_MESSAGE, *LPST_OPR_MESSAGE;

//// �۾����� ����
typedef struct __stOprConstruction_
{                    
	INT     CTRID;                            /*PID                         */
	TCHAR	CREATE_TIME[RDB_DATETIME25_SZ];   /*�����ð�                    */
	INT     SSFK;							  /*������ �̸�                 */
	INT     DLFK;							  /*DL �̸�                     */
	INT     CEQFK;							  /*���ֹ�ȣ                    */
	CHAR    CONSTTYPE ;                       /*�۾�����                    */ 
	INT     USERID_FK;                        /*�ۼ��� ID                   */
	TCHAR   CONTENTS[RDB_CONTENT512_SZ];      /*����                        */

} ST_OPR_CONSTRUCTION, *LPST_OPR_CONSTRUCTION;

//// ��ɿ� ���� ���̺�
typedef struct __stOprOperatorAssign_
{                    
	INT		OPRAId;                            /*��ɿ� ���Ѱ���             */
	INT		USERFK;                            /*OperatorCodeID FK           */
	CHAR    AssignType;                        /*�������� Ÿ��(0=����,1=������, 2=DL */ 
	INT		TableId;                           /*����(SubGeographicalRegion�� ID), ������(Substation�� ID), DL(DistributionID) */

} ST_OPR_OPERATORASSIGN, *LPST_OPR_OPERATORASSIGN;

//// ������� ������ �����ϴ� ���̺�
typedef struct __stOprWAVE_LIST_
{                    
	INT		WaveListId;                       /*���� Id                     */
	TCHAR  CreateTm[RDB_DATETIME25_SZ];       /*�����ð�                    */
	INT		RUID;                             /*RTU ID                      */
	INT		SampRate;                         /*���ø� ��                   */
	TCHAR   Filename[RDB_NAME64_SZ];          /*�����̸�                    */
	INT		FileSize;                         /*����ũ��                    */ 

} ST_OPR_WAVE_LIST, *LPST_OPR_WAVE_LIST;

//// ������� ������ �����ϴ� ���̺�
typedef struct __stOprWAVE_FILE_
{                    
	INT		WaveId;							  /*���� Id                     */
	TCHAR	CreateTm[RDB_DATETIME25_SZ];      /*�����ð�                    */
	INT		RUID;                             /*RTU ID                      */
	INT		WaveType;                         /*���� Ÿ��                   */	
	TCHAR   Filename[RDB_NAME64_SZ];          /*�����̸�                    */
	INT		FileSize;                         /*����ũ��                    */ 

} ST_OPR_WAVE_FILE, *LPST_OPR_WAVE_FILE;

//// ���� ���� ������ ���� ���̺�
typedef struct __stOprComputerStatus_
{                                                   
	INT		 ComputerID;								 /* ��ǻ�� ID                         */
	TCHAR    ComputerName[RDB_NAME64_SZ];				 /* ��ǻ�� �̸�                       */
	CHAR	 ComputerType;								 /* ��ǻ�� ����                       */
	SHORT    ActiveState;								 /* ���� ����                         */
	SHORT    RunState;									 /* ��������                          */
	SHORT    UpcActiveState;							 /* MW ���ۻ���                       */
	SHORT    UpcRunState;								 /* MW ��������		                  */
	SHORT    RdbRunState;								 /* RDB ����						  */
	SHORT    RdbRoleState;								 /* RDB �̷��� ����                   */
	TCHAR    SysStart_tm[RDB_DATETIME25_SZ];			 /* ��������ð�                      */
	TCHAR    SysStop_tm[RDB_DATETIME25_SZ];				 /* ��������ð�					  */
	TCHAR    lastupdate_tm[RDB_DATETIME25_SZ];			 /* DP ������Ʈ �ð�                  */

} ST_OPR_COMPUTERSTATUS, *LPST_OPR_COMPUTERSTATUS;

//// ����� ���� ���̺�
typedef struct __stOprCalculation_Result_
{                                                   
	INT		PID;									 /*����Ʈ ID                           */
	INT		VALUE;									 /*�����                            */
	INT		Old_Value;								 /*���������                        */
	SHORT   TLQ;									 /*TLQ                                 */
	TCHAR   LAST_UPDATE[RDB_DATETIME25_SZ];			 /*������ ������Ʈ �ð�                */

} ST_OPR_CALCULATION_RESULT, *LPST_OPR_CALCULATION_RESULT;


#pragma pack()
#endif	/* __PDBSTRUCT_H__ */