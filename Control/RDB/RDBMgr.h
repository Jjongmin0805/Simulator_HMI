#pragma once

#ifdef __COMMON_H__
#include "../Include/Common.h"
#endif
//-----------------------------------------------------------------------
// Summary:
//     계통도 프로그램 내 큐 사용 인덱스
//-----------------------------------------------------------------------
enum HMI_APP_CODE
{
	HMI_QUEUE	= 0,
	HMI_APP_TAB1,	//각 단위 프로그램 별로 정의하여 사용(최대 20 Index 생성) 	
	HMI_APP_TAB2,		
	HMI_APP_TAB3,		
	HMI_APP_TAB4,		
	HMI_APP_TAB5,
	HMI_APP_TAB6,
	HMI_APP_TAB7,
	HMI_APP_TAB8,		
	HMI_APP_TAB9,		
	HMI_APP_TAB10,		
	HMI_APP_TAB11,
	HMI_APP_TAB12,
	HMI_APP_TAB13,
	HMI_APP_TAB14,
	HMI_APP_TAB15,
	HMI_APP_TAB16,		
	HMI_APP_TAB17,		
	HMI_APP_TAB18,		
	HMI_APP_TAB19,
	HMI_APP_TAB20,
	HMI_APP_COUNT,
};

//-----------------------------------------------------------------------
// Summary:
//     계통도 RDB 공유 메모리 참조 class
//-----------------------------------------------------------------------
class CRDBMgr
{
public:
	CRDBMgr(void) {}
	~CRDBMgr(void) {}

public:

	//-----------------------------------------------------------------------
	// Summary:
	//     CIM에서 공통되는 정보관리 RDB 파일 Access
	// Parameters:
	//     nIndex        - 지점 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_IDENTIFIEDOBJECT GetIdent(UINT nIndex) {return (LPST_COMMON_IDENTIFIEDOBJECT)&g_pCommonIDENTIFIEDOBJECT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     본부(지사) RDB 파일 Access
	// Parameters:
	//     nIndex        - 본부(지사) RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_GEOGRAPHICALREGION GetIndexGeoGraphic(UINT nIndex) {return (LPST_COMMON_GEOGRAPHICALREGION)HMISHARE_GET_DATA(FILE_GEOGRAPHICALREGION, nIndex);}
	static LPST_COMMON_GEOGRAPHICALREGION GetGeoGraphic(UINT nIndex) {return (LPST_COMMON_GEOGRAPHICALREGION)&g_pCommonGEOGRAPHICALREGION[nIndex];}
	
	//-----------------------------------------------------------------------
	// Summary:
	//     지점(예하사업소) RDB 파일 Access
	// Parameters:
	//     nIndex        - 지사 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SUBGEOGRAPHICALREGION GetIndexSubGeoGraphic(UINT nIndex) {return (LPST_COMMON_SUBGEOGRAPHICALREGION)HMISHARE_GET_DATA(FILE_SUBGEOGRAPHICALREGION, nIndex);}
	static LPST_COMMON_SUBGEOGRAPHICALREGION GetSubGeoGraphic(UINT nIndex) {return (LPST_COMMON_SUBGEOGRAPHICALREGION)&g_pCommonSUBGEOGRAPHICALREGION[nIndex];}
	
	//-----------------------------------------------------------------------
	// Summary:
	//     시스템내 DataPoint 구성을 위한 테이블 RDB 파일 Access
	// Parameters:
	//     nIndex        - DATAPOINTGROUPCODE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DATAPOINTGROUPCODE GetIndexDpGrp(UINT nIndex) {return (LPST_COMMON_DATAPOINTGROUPCODE)HMISHARE_GET_DATA(FILE_DATAPOINTGROUPCODE, nIndex);}
	static LPST_COMMON_DATAPOINTGROUPCODE GetDpGrp(UINT nIndex) {return (LPST_COMMON_DATAPOINTGROUPCODE)&g_pCommonDATAPOINTGROUPCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    컴퓨터(시스템) 관리 테이블 RDB 파일 Access
	// Parameters:
	//     nIndex        - 컴퓨터(시스템) 관리 테이블 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_COMPUTERCODE GetIndexComputer(UINT nIndex) {return (LPST_COMMON_COMPUTERCODE)HMISHARE_GET_DATA(FILE_OPERATORCODE, nIndex);}
	static LPST_COMMON_COMPUTERCODE GetComputer(UINT nIndex) {return (LPST_COMMON_COMPUTERCODE)&g_pCommonCOMPUTERCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     프로그램 관리 테이블    RDB 파일 Access
	// Parameters:
	//     nIndex        - PROGRAMCODE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PROGRAMCODE GetIndexProCode(UINT nIndex) {return (LPST_COMMON_PROGRAMCODE)HMISHARE_GET_DATA(FILE_PROGRAMCODE, nIndex);}
	static LPST_COMMON_PROGRAMCODE GetProCode(UINT nIndex) {return (LPST_COMMON_PROGRAMCODE)&g_pCommonPROGRAMCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     사령원 관리 테이블     RDB 파일 Access
	// Parameters:
	//     nIndex        - OPERATORCODE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_OPERATORCODE GetIndexOpCode(UINT nIndex) {return (LPST_COMMON_OPERATORCODE)HMISHARE_GET_DATA(FILE_OPERATORCODE, nIndex);}
	static LPST_COMMON_OPERATORCODE GetOpCode(UINT nIndex) {return (LPST_COMMON_OPERATORCODE)&g_pCommonOPERATORCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     스위치 구분 코드      RDB 파일 Access
	// Parameters:
	//     nIndex        - SWITCHTYPECODE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SWITCHTYPECODE GetIndexSwitchType(UINT nIndex) {return (LPST_COMMON_SWITCHTYPECODE)HMISHARE_GET_DATA(FILE_SWITCHTYPECODE, nIndex);}
	static LPST_COMMON_SWITCHTYPECODE GetSwitchType(UINT nIndex) {return (LPST_COMMON_SWITCHTYPECODE)&g_pCommonSWITCHTYPECODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     작업종류 테이블    RDB 파일 Access
	// Parameters:
	//     nIndex        - CONSTRUCTIONCODE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_CONSTRUCTIONCODE GetIndexConstCode(UINT nIndex) {return (LPST_COMMON_CONSTRUCTIONCODE)HMISHARE_GET_DATA(FILE_CONSTRUCTIONCODE, nIndex);}
	static LPST_COMMON_CONSTRUCTIONCODE GetConstCode(UINT nIndex) {return (LPST_COMMON_CONSTRUCTIONCODE)&g_pCommonCONSTRUCTIONCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     파형정보 타입       RDB 파일 Access
	// Parameters:
	//     nIndex        - WAVECOMTYPE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_WAVECOMTYPE GetIndexWaveType(UINT nIndex) {return (LPST_COMMON_WAVECOMTYPE)HMISHARE_GET_DATA(FILE_WAVECOMTYPE, nIndex);}
	static LPST_COMMON_WAVECOMTYPE GetWaveType(UINT nIndex) {return (LPST_COMMON_WAVECOMTYPE)&g_pCommonWAVECOMTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     상태값에 대한 표시 그룹        RDB 파일 Access
	// Parameters:
	//     nIndex        - STATEGROUP RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_STATEGROUP GetIndexStateGroup(UINT nIndex) {return (LPST_COMMON_STATEGROUP)HMISHARE_GET_DATA(FILE_STATEGROUP, nIndex);}
	static LPST_COMMON_STATEGROUP GetStateGroup(UINT nIndex) {return (LPST_COMMON_STATEGROUP)&g_pCommonSTATEGROUP[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     인덱스별 데이터 형식          RDB 파일 Access
	// Parameters:
	//     nIndex        - DATABYTE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DATABYTE GetIndexDataByte(UINT nIndex) {return (LPST_COMMON_DATABYTE)HMISHARE_GET_DATA(FILE_DATABYTE, nIndex);}
	static LPST_COMMON_DATABYTE GetDataByte(UINT nIndex) {return (LPST_COMMON_DATABYTE)&g_pCommonDATABYTE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     상태값에 대한 정의 테이블 RDB 파일 Access
	// Parameters:
	//     nIndex        - STATESET RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_STATESET GetIndexStateSet(UINT nIndex) {return (LPST_COMMON_STATESET)HMISHARE_GET_DATA(FILE_STATESET, nIndex);}
	static LPST_COMMON_STATESET GetStateSet(UINT nIndex) {return (LPST_COMMON_STATESET)&g_pCommonSTATESET[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     계측 표시 단위          RDB 파일 Access
	// Parameters:
	//     nIndex        - DATABYTE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_UNIT GetIndexUnit(UINT nIndex) {return (LPST_COMMON_UNIT)HMISHARE_GET_DATA(FILE_UNIT, nIndex);}
	static LPST_COMMON_UNIT GetUnit(UINT nIndex) {return (LPST_COMMON_UNIT)&g_pCommonUNIT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     계측값 단위표시용 값 코드 RDB 파일 Access
	// Parameters:
	//     nIndex        - 변압기 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SCALEFACTOR GetIndexScale(UINT nIndex) {return (LPST_COMMON_SCALEFACTOR)HMISHARE_GET_DATA(FILE_SCALEFACTOR, nIndex);}
	static LPST_COMMON_SCALEFACTOR GetScale(UINT nIndex) {return (LPST_COMMON_SCALEFACTOR)&g_pCommonSCALEFACTOR[nIndex];}
	
	//-----------------------------------------------------------------------
	// Summary:
	//     상한/하한 코드 RDB 파일 Access
	// Parameters:
	//     nIndex        - 변압기 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_LIMITCODE GetIndexLimitCode(UINT nIndex) {return (LPST_COMMON_LIMITCODE)HMISHARE_GET_DATA(FILE_LIMITCODE, nIndex);}
	static LPST_COMMON_LIMITCODE GetLimitCode(UINT nIndex) {return (LPST_COMMON_LIMITCODE)&g_pCommonLIMITCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     상한/하한 집합 RDB 파일 Access
	// Parameters:
	//     nIndex        - 변압기 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_LIMITSET GetIndexLimitSet(UINT nIndex) {return (LPST_COMMON_LIMITSET)HMISHARE_GET_DATA(FILE_LIMITSET, nIndex);}
	static LPST_COMMON_LIMITSET GetLimitSet(UINT nIndex) {return (LPST_COMMON_LIMITSET)&g_pCommonLIMITSET[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     기기 제작사명 테이블 RDB 파일 Access
	// Parameters:
	//     nIndex        - EQUIPCOMPANY RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_EQUIPCOMPANY GetIndexCompany(UINT nIndex) {return (LPST_COMMON_EQUIPCOMPANY)HMISHARE_GET_DATA(FILE_EQUIPCOMPANY, nIndex);}
	static LPST_COMMON_EQUIPCOMPANY GetCompany(UINT nIndex) {return (LPST_COMMON_EQUIPCOMPANY)&g_pCommonEQUIPCOMPANY[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     변전소 RDB 파일 Access
	// Parameters:
	//     nIndex        - 변전소 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SUBSTATION GetIndexSubStation(UINT nIndex) {return (LPST_COMMON_SUBSTATION)HMISHARE_GET_DATA(FILE_SUBSTATION, nIndex);}
	static LPST_COMMON_SUBSTATION GetSubStation(UINT nIndex) {return (LPST_COMMON_SUBSTATION)&g_pCommonSUBSTATION[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DL RDB 파일 Access
	// Parameters:
	//     nIndex        - DL RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DISTRIBUTIONLINE GetIndexDLine(UINT nIndex) {return (LPST_COMMON_DISTRIBUTIONLINE)HMISHARE_GET_DATA(FILE_DISTRIBUTIONLINE, nIndex);}
	static LPST_COMMON_DISTRIBUTIONLINE GetDLine(UINT nIndex) {return (LPST_COMMON_DISTRIBUTIONLINE)&g_pCommonDISTRIBUTIONLINE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     기준전압 파일 Access
	// Parameters:
	//     nIndex        - BASEVOLTAGE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_BASEVOLTAGE GetIndexBaseVoltage(UINT nIndex) {return (LPST_COMMON_BASEVOLTAGE)HMISHARE_GET_DATA(FILE_BASEVOLTAGE, nIndex);}
	static LPST_COMMON_BASEVOLTAGE GetBaseVoltage(UINT nIndex) {return (LPST_COMMON_BASEVOLTAGE)&g_pCommonBASEVOLTAGE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     기준전력 파일 Access
	// Parameters:
	//     nIndex        - BASEPOWER RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_BASEPOWER GetIndexBasePower(UINT nIndex) {return (LPST_COMMON_BASEPOWER)HMISHARE_GET_DATA(FILE_BASEPOWER, nIndex);}
	static LPST_COMMON_BASEPOWER GetBasePower(UINT nIndex) {return (LPST_COMMON_BASEPOWER)&g_pCommonBASEPOWER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     전압레벨 파일 Access
	// Parameters:
	//     nIndex        - VOLTAGELEVEL RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_VOLTAGELEVEL GetIndexVoltageLevel(UINT nIndex) {return (LPST_COMMON_VOLTAGELEVEL)HMISHARE_GET_DATA(FILE_VOLTAGELEVEL, nIndex);}
	static LPST_COMMON_VOLTAGELEVEL GetVoltageLevel(UINT nIndex) {return (LPST_COMMON_VOLTAGELEVEL)&g_pCommonVOLTAGELEVEL[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     상 관리 테이블 파일 Access
	// Parameters:
	//     nIndex        - PHASE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PHASE GetIndexPhase(UINT nIndex) {return (LPST_COMMON_PHASE)HMISHARE_GET_DATA(FILE_PHASE, nIndex);}
	static LPST_COMMON_PHASE GetPhase(UINT nIndex) {return (LPST_COMMON_PHASE)&g_pCommonPHASE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     PROTOCOL TYPE 테이블 파일 Access
	// Parameters:
	//     nIndex        - PROTOCOLTYPE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PROTOCOLTYPE GetIndexProtocolType(UINT nIndex) {return (LPST_COMMON_PROTOCOLTYPE)HMISHARE_GET_DATA(FILE_PROTOCOLTYPE, nIndex);}
	static LPST_COMMON_PROTOCOLTYPE GetProtocolType(UINT nIndex) {return (LPST_COMMON_PROTOCOLTYPE)&g_pCommonPROTOCOLTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     장치종류 타입 테이블 관리 테이블 파일 Access
	// Parameters:
	//     nIndex        - EQUIPMENTTYPE 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_EQUIPMENTTYPE GetIndexEqType(UINT nIndex) {return (LPST_COMMON_EQUIPMENTTYPE)HMISHARE_GET_DATA(FILE_EQUIPMENTTYPE, nIndex);}
	static LPST_COMMON_EQUIPMENTTYPE GetEqType(UINT nIndex) {return (LPST_COMMON_EQUIPMENTTYPE)&g_pCommonEQUIPMENTTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     RTU Map RDB 파일 Access
	// Parameters:
	//     nIndex        - 리모트디바이스 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_RTUMAP GetIndexRTUMap(UINT nIndex) {return (LPST_COMMON_RTUMAP)HMISHARE_GET_DATA(FILE_RTUMAP, nIndex);}
	static LPST_COMMON_RTUMAP GetRTUMap(UINT nIndex) {return (LPST_COMMON_RTUMAP)&g_pCommonRTUMAP[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     통신 종류 RDB 파일 Access
	// Parameters:
	//     nIndex        - 변압기 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_COMMTYPE GetIndexCommType(UINT nIndex) {return (LPST_COMMON_COMMTYPE)HMISHARE_GET_DATA(FILE_COMMTYPE, nIndex);}
	static LPST_COMMON_COMMTYPE GetCommType(UINT nIndex) {return (LPST_COMMON_COMMTYPE)&g_pCommonCOMMTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     RTU 종류 코드 테이블 파일 Access
	// Parameters:
	//     nIndex        - RTUTYPE 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_RTUTYPE GetIndexRtuType(UINT nIndex) {return (LPST_COMMON_RTUTYPE)HMISHARE_GET_DATA(FILE_RTUTYPE, nIndex);}
	static LPST_COMMON_RTUTYPE GetRtuType(UINT nIndex) {return (LPST_COMMON_RTUTYPE)&g_pCommonRTUTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     HMI 뷰 UI에서 Subtab 구분자 RDB 파일 Access
	// Parameters:
	//     nIndex        - CATEGORYCODE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_CATEGORYCODE GetIndexCatCode(UINT nIndex) {return (LPST_COMMON_CATEGORYCODE)HMISHARE_GET_DATA(FILE_CATEGORYCODE, nIndex);}
	static LPST_COMMON_CATEGORYCODE GetCatCode(UINT nIndex) {return (LPST_COMMON_CATEGORYCODE)&g_pCommonCATEGORYCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     포인트 종류 RDB 파일 Access
	// Parameters:
	//     nIndex        - MEASURETYPEINFO RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_MEASURETYPEINFO GetIndexMtInfo(UINT nIndex) {return (LPST_COMMON_MEASURETYPEINFO)HMISHARE_GET_DATA(FILE_MEASURETYPEINFO, nIndex);}
	static LPST_COMMON_MEASURETYPEINFO GetMtInfo(UINT nIndex) {return (LPST_COMMON_MEASURETYPEINFO)&g_pCommonMEASURETYPEINFO[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DNP_BI_MAPINDEX  RDB 파일 Access
	// Parameters:
	//     nIndex        - 설비 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DNPBIMAPINDEX GetIndexDnpBI(UINT nIndex) {return (LPST_COMMON_DNPBIMAPINDEX)HMISHARE_GET_DATA(FILE_DNPBIMAPINDEX, nIndex);}
	static LPST_COMMON_DNPBIMAPINDEX GetDnpBI(UINT nIndex) {return (LPST_COMMON_DNPBIMAPINDEX)&g_pCommonDNPBIMAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DNP_B0_MAPINDEX  RDB 파일 Access
	// Parameters:
	//     nIndex        - 설비 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DNPBOMAPINDEX GetIndexDnpBO(UINT nIndex) {return (LPST_COMMON_DNPBOMAPINDEX)HMISHARE_GET_DATA(FILE_DNPBOMAPINDEX, nIndex);}
	static LPST_COMMON_DNPBOMAPINDEX GetDnpBO(UINT nIndex) {return (LPST_COMMON_DNPBOMAPINDEX)&g_pCommonDNPBOMAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DNP_AI_MAPINDEX  RDB 파일 Access
	// Parameters:
	//     nIndex        - 설비 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DNPAIMAPINDEX GetIndexDnpAI(UINT nIndex) {return (LPST_COMMON_DNPAIMAPINDEX)HMISHARE_GET_DATA(FILE_DNPAIMAPINDEX, nIndex);}
	static LPST_COMMON_DNPAIMAPINDEX GetDnpAI(UINT nIndex) {return (LPST_COMMON_DNPAIMAPINDEX)&g_pCommonDNPAIMAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DNP_AO_MAPINDEX  RDB 파일 Access
	// Parameters:
	//     nIndex        - 설비 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DNPAOMAPINDEX GetIndexDnpAO(UINT nIndex) {return (LPST_COMMON_DNPAOMAPINDEX)HMISHARE_GET_DATA(FILE_DNPAOMAPINDEX, nIndex);}
	static LPST_COMMON_DNPAOMAPINDEX GetDnpAO(UINT nIndex) {return (LPST_COMMON_DNPAOMAPINDEX)&g_pCommonDNPAOMAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DNP_COUNTER_MAPINDEX  RDB 파일 Access
	// Parameters:
	//     nIndex        - 설비 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DNPCOUNTERMAPINDEX GetIndexDnpCOUNTER(UINT nIndex) {return (LPST_COMMON_DNPCOUNTERMAPINDEX)HMISHARE_GET_DATA(FILE_DNPCOUNTERMAPINDEX, nIndex);}
	static LPST_COMMON_DNPCOUNTERMAPINDEX GetDnpCOUNTER(UINT nIndex) {return (LPST_COMMON_DNPCOUNTERMAPINDEX)&g_pCommonDNPCOUNTERMAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     현장기기 통신 설정 RDB 파일 Access
	// Parameters:
	//     nIndex        - 리모트디바이스 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_RTUDEVICE GetIndexRTUDevice(UINT nIndex) {return (LPST_COMMON_RTUDEVICE)HMISHARE_GET_DATA(FILE_RTUDEVICE, nIndex);}
	static LPST_COMMON_RTUDEVICE GetRTUDevice(UINT nIndex) {return (LPST_COMMON_RTUDEVICE)&g_pCommonRTUDEVICE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     현장기기 정보 RDB 파일 Access
	// Parameters:
	//     nIndex        - 설비 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_CONDUCTINGEQUIPMENT GetIndexEquip(UINT nIndex) {return (LPST_COMMON_CONDUCTINGEQUIPMENT)HMISHARE_GET_DATA(FILE_CONDUCTINGEQUIPMENT, nIndex);}
	static LPST_COMMON_CONDUCTINGEQUIPMENT GetEquip(UINT nIndex) {return (LPST_COMMON_CONDUCTINGEQUIPMENT)&g_pCommonCONDUCTINGEQUIPMENT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     스위치 구분 코드      RDB 파일 Access
	// Parameters:
	//     nIndex        - SWITCHTYPECODE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SWITCH GetIndexSwitch(UINT nIndex) {return (LPST_COMMON_SWITCH)HMISHARE_GET_DATA(FILE_SWITCH, nIndex);}
	static LPST_COMMON_SWITCH GetSwitch(UINT nIndex) {return (LPST_COMMON_SWITCH)&g_pCommonSWITCH[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     선로 구간      RDB 파일 Access
	// Parameters:
	//     nIndex        - ACLINESEGMENT RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACLINESEGMENT GetIndexAcLine(UINT nIndex) {return (LPST_COMMON_ACLINESEGMENT)HMISHARE_GET_DATA(FILE_ACLINESEGMENT, nIndex);}	
	static LPST_COMMON_ACLINESEGMENT GetAcLine(UINT nIndex) {return (LPST_COMMON_ACLINESEGMENT)&g_pCommonACLINESEGMENT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     선종 구분      RDB 파일 Access
	// Parameters:
	//     nIndex        - PERLENGTHSEQUENCEIMPEDANCE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE GetIndexPerLeng(UINT nIndex) {return (LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE)HMISHARE_GET_DATA(FILE_PERLENGTHSEQUENCEIMPEDANCE, nIndex);}	
	static LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE GetPerLeng(UINT nIndex) {return (LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE)&g_pCommonPERLENGTHSEQUENCEIMPEDANCE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    변전소 내 BUSBARSECTION 정보표시      RDB 파일 Access
	// Parameters:
	//     nIndex        - BUSBARSECTION RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_BUSBARSECTION GetIndexBusBar(UINT nIndex) {return (LPST_COMMON_BUSBARSECTION)HMISHARE_GET_DATA(FILE_BUSBARSECTION, nIndex);}	
	static LPST_COMMON_BUSBARSECTION GetBusBar(UINT nIndex) {return (LPST_COMMON_BUSBARSECTION)&g_pCommonBUSBARSECTION[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     컴포짓 RDB 파일 Access
	// Parameters:
	//     nIndex        - 컴포짓 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_COMPOSITESWITCH GetIndexComposite(UINT nIndex) {return (LPST_COMMON_COMPOSITESWITCH)HMISHARE_GET_DATA(FILE_COMPOSITESWITCH, nIndex);}
	static LPST_COMMON_COMPOSITESWITCH GetComposite(UINT nIndex) {return (LPST_COMMON_COMPOSITESWITCH)&g_pCommonCOMPOSITESWITCH[nIndex];}
	
	//-----------------------------------------------------------------------
	// Summary:
	//     변압기 RDB 파일 Access
	// Parameters:
	//     nIndex        - 변압기 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_POWERTRANSFORMER GetIndexPowerTr(UINT nIndex) {return (LPST_COMMON_POWERTRANSFORMER)HMISHARE_GET_DATA(FILE_POWERTRANSFORMER, nIndex);}
	static LPST_COMMON_POWERTRANSFORMER GetPowerTr(UINT nIndex) {return (LPST_COMMON_POWERTRANSFORMER)&g_pCommonPOWERTRANSFORMER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     Tap 제어기 RDB 파일 Access
	// Parameters:
	//     nIndex        - TAPCHANGER RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_TAPCHANGER GetIndexTapChanger(UINT nIndex) {return (LPST_COMMON_TAPCHANGER)HMISHARE_GET_DATA(FILE_TAPCHANGER, nIndex);}
	static LPST_COMMON_TAPCHANGER GetTapChanger(UINT nIndex) {return (LPST_COMMON_TAPCHANGER)&g_pCommonTAPCHANGER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     변압기 결선 RDB 파일 Access
	// Parameters:
	//     nIndex        - 변압기 결선 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_TRANSFORMERWINDING GetIndexDisTransWind(UINT nIndex) {return (LPST_COMMON_TRANSFORMERWINDING)HMISHARE_GET_DATA(FILE_TRANSFORMERWINDING, nIndex);}
	static LPST_COMMON_TRANSFORMERWINDING GetDisTransWind(UINT nIndex) {return (LPST_COMMON_TRANSFORMERWINDING)&g_pCommonTRANSFORMERWINDING[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     Tap 제어 스케쥴 RDB 파일 Access
	// Parameters:
	//     nIndex        - TAPREGULATIONSCHEDULE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_TAPREGULATIONSCHEDULE GetIndexTapSche(UINT nIndex) {return (LPST_COMMON_TAPREGULATIONSCHEDULE)HMISHARE_GET_DATA(FILE_TAPREGULATIONSCHEDULE, nIndex);}
	static LPST_COMMON_TAPREGULATIONSCHEDULE GetTapSche(UINT nIndex) {return (LPST_COMMON_TAPREGULATIONSCHEDULE)&g_pCommonTAPREGULATIONSCHEDULE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     보호설비 RDB 파일 Access
	// Parameters:
	//     nIndex        - PROTECTIONEQUIPMENT RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PROTECTIONEQUIPMENT GetIndexProtect(UINT nIndex) {return (LPST_COMMON_PROTECTIONEQUIPMENT)HMISHARE_GET_DATA(FILE_PROTECTIONEQUIPMENT, nIndex);}
	static LPST_COMMON_PROTECTIONEQUIPMENT GetProtect(UINT nIndex) {return (LPST_COMMON_PROTECTIONEQUIPMENT)&g_pCommonPROTECTIONEQUIPMENT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     재페로시퀀스 RDB 파일 Access
	// Parameters:
	//     nIndex        - RECLOSESEQUENCE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_RECLOSESEQUENCE GetIndexRecloser(UINT nIndex) {return (LPST_COMMON_RECLOSESEQUENCE)HMISHARE_GET_DATA(FILE_RECLOSESEQUENCE, nIndex);}
	static LPST_COMMON_RECLOSESEQUENCE GetRecloser(UINT nIndex) {return (LPST_COMMON_RECLOSESEQUENCE)&g_pCommonRECLOSESEQUENCE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     계전기 RDB 파일 Access
	// Parameters:
	//     nIndex        - CURRENTRELAY RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_CURRENTRELAY GetIndexRelay(UINT nIndex) {return (LPST_COMMON_CURRENTRELAY)HMISHARE_GET_DATA(FILE_CURRENTRELAY, nIndex);}
	static LPST_COMMON_CURRENTRELAY GetRelay(UINT nIndex) {return (LPST_COMMON_CURRENTRELAY)&g_pCommonCURRENTRELAY[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     에너지 저장장치 RDB 파일 Access
	// Parameters:
	//     nIndex        - CURRENTRELAY RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_BATTERYSTORAGE GetIndexBattery(UINT nIndex) {return (LPST_COMMON_BATTERYSTORAGE)HMISHARE_GET_DATA(FILE_BATTERYSTORAGE, nIndex);}
	static LPST_COMMON_BATTERYSTORAGE GetBattery(UINT nIndex) {return (LPST_COMMON_BATTERYSTORAGE)&g_pCommonBATTERYSTORAGE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     발전기 또는 발전소 RDB 파일 Access
	// Parameters:
	//     nIndex        - 발전기 또는 발전소  RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_GENERATINGUNIT GetIndexGeneratingUnit(UINT nIndex) {return (LPST_COMMON_GENERATINGUNIT)HMISHARE_GET_DATA(FILE_GENERATINGUNIT, nIndex);}
	static LPST_COMMON_GENERATINGUNIT GetGeneratingUnit(UINT nIndex) {return (LPST_COMMON_GENERATINGUNIT)&g_pCommonGENERATINGUNIT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    전력변환장치 RDB 파일 Access
	// Parameters:
	//     nIndex        - GENREGULATIONSCHEDULE  RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_GENREGULATIONSCHEDULE GetIndexGenSche(UINT nIndex) {return (LPST_COMMON_GENREGULATIONSCHEDULE)HMISHARE_GET_DATA(FILE_GENREGULATIONSCHEDULE, nIndex);}
	static LPST_COMMON_GENREGULATIONSCHEDULE GetGenSche(UINT nIndex) {return (LPST_COMMON_GENREGULATIONSCHEDULE)&g_pCommonGENREGULATIONSCHEDULE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     분산전원 RDB 파일 Access
	//		WindTurbine, PhotoVoltaic, BATTERYSTORAGE
	// Parameters:
	//     nIndex        - 분산전원 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_WINDTURBINE GetIndexWind(UINT nIndex) {return (LPST_COMMON_WINDTURBINE)HMISHARE_GET_DATA(FILE_WINDTURBINE, nIndex);}
	static LPST_COMMON_WINDTURBINE GetWind(UINT nIndex) {return (LPST_COMMON_WINDTURBINE)&g_pCommonWINDTURBINE[nIndex];}

	static LPST_COMMON_PHOTOVOLTAIC GetIndexPhoto(UINT nIndex) {return (LPST_COMMON_PHOTOVOLTAIC)HMISHARE_GET_DATA(FILE_PHOTOVOLTAIC, nIndex);}
	static LPST_COMMON_PHOTOVOLTAIC GetPhoto(UINT nIndex) {return (LPST_COMMON_PHOTOVOLTAIC)&g_pCommonPHOTOVOLTAIC[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     발전기 연료비 곡선 RDB 파일 Access
	// Parameters:
	//     nIndex        - GENUNITOPCOSTCURVE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_GENUNITOPCOSTCURVE GetIndexGenCurve(UINT nIndex) {return (LPST_COMMON_GENUNITOPCOSTCURVE)HMISHARE_GET_DATA(FILE_GENUNITOPCOSTCURVE, nIndex);}
	static LPST_COMMON_GENUNITOPCOSTCURVE GetGenCurve(UINT nIndex) {return (LPST_COMMON_GENUNITOPCOSTCURVE)&g_pCommonGENUNITOPCOSTCURVE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     고압수용가 RDB 파일 Access
	// Parameters:
	//     nIndex        - ENERGYCONSUMER RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ENERGYCONSUMER GetIndexEnergy(UINT nIndex) {return (LPST_COMMON_ENERGYCONSUMER)HMISHARE_GET_DATA(FILE_ENERGYCONSUMER, nIndex);}
	static LPST_COMMON_ENERGYCONSUMER GetEnergy(UINT nIndex) {return (LPST_COMMON_ENERGYCONSUMER)&g_pCommonENERGYCONSUMER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     병렬 역률보상기기 RDB 파일 Access
	// Parameters:
	//     nIndex        - SHUNTCOMPASATOR RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SHUNTCOMPASATOR GetIndexShunt(UINT nIndex) {return (LPST_COMMON_SHUNTCOMPASATOR)HMISHARE_GET_DATA(FILE_SHUNTCOMPASATOR, nIndex);}
	static LPST_COMMON_SHUNTCOMPASATOR GetShunt(UINT nIndex) {return (LPST_COMMON_SHUNTCOMPASATOR)&g_pCommonSHUNTCOMPASATOR[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     무효전력 보상장치 RDB 파일 Access
	// Parameters:
	//     nIndex        - SHUNTCOMPASATOR RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_STATICVARCOMPENSATOR GetIndexSvr(UINT nIndex) {return (LPST_COMMON_STATICVARCOMPENSATOR)HMISHARE_GET_DATA(FILE_STATICVARCOMPENSATOR, nIndex);}
	static LPST_COMMON_STATICVARCOMPENSATOR GetSvr(UINT nIndex) {return (LPST_COMMON_STATICVARCOMPENSATOR)&g_pCommonSTATICVARCOMPENSATOR[nIndex];}
	
	//-----------------------------------------------------------------------
	// Summary:
	//     설비 및 집합개념의 모음 RDB 파일 Access
	// Parameters:
	//     nIndex        - POWERSYSTEMRESOURCE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_POWERSYSTEMRESOURCE GetIndexPSR(UINT nIndex) {return (LPST_COMMON_POWERSYSTEMRESOURCE)HMISHARE_GET_DATA(FILE_POWERSYSTEMRESOURCE, nIndex);}
	static LPST_COMMON_POWERSYSTEMRESOURCE GetPSR(UINT nIndex) {return (LPST_COMMON_POWERSYSTEMRESOURCE)&g_pCommonPOWERSYSTEMRESOURCE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     PSR type RDB 파일 Access
	// Parameters:
	//     nIndex        - 설비 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PSRTYPE GetIndexPsrType(UINT nIndex) {return (LPST_COMMON_PSRTYPE)HMISHARE_GET_DATA(FILE_PSRTYPE, nIndex);}
	static LPST_COMMON_PSRTYPE GetPsrType(UINT nIndex) {return (LPST_COMMON_PSRTYPE)&g_pCommonPSRTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    집합개념 RDB 파일 Access
	// Parameters:
	//     nIndex        - EQUIPMENTCONTAINER RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_EQUIPMENTCONTAINER GetIndexEqCon(UINT nIndex) {return (LPST_COMMON_EQUIPMENTCONTAINER)HMISHARE_GET_DATA(FILE_EQUIPMENTCONTAINER, nIndex);}
	static LPST_COMMON_EQUIPMENTCONTAINER GetEqCon(UINT nIndex) {return (LPST_COMMON_EQUIPMENTCONTAINER)&g_pCommonEQUIPMENTCONTAINER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    심볼 RDB 파일 Access
	// Parameters:
	//     nIndex        - SYMBOL RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SYMBOL GetIndexSymbol(UINT nIndex) {return (LPST_COMMON_SYMBOL)HMISHARE_GET_DATA(FILE_SYMBOL, nIndex);}
	static LPST_COMMON_SYMBOL GetSymbol(UINT nIndex) {return (LPST_COMMON_SYMBOL)&g_pCommonSYMBOL[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    계통도 파일을 가져오는 테이블 Access
	// Parameters:
	//     nIndex        - DASDIAGRAMINFO RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DASDIAGRAMINFO GetIndexDasDiagram(UINT nIndex) {return (LPST_COMMON_DASDIAGRAMINFO)HMISHARE_GET_DATA(FILE_DASDIAGRAMINFO, nIndex);}
	static LPST_COMMON_DASDIAGRAMINFO GetDasDiagram(UINT nIndex) {return (LPST_COMMON_DASDIAGRAMINFO)&g_pCommonDASDIAGRAMINFO[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//   변발전 계통도 파일을 가져오는 테이블 Access
	// Parameters:
	//     nIndex        - STATIONDIAGRAMINFO RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_STATIONDIAGRAMINFO GetIndexStationDiagram(UINT nIndex) {return (LPST_COMMON_STATIONDIAGRAMINFO)HMISHARE_GET_DATA(FILE_STATIONDIAGRAMINFO, nIndex);}
	static LPST_COMMON_STATIONDIAGRAMINFO GetStationDiagram(UINT nIndex) {return (LPST_COMMON_STATIONDIAGRAMINFO)&g_pCommonSTATIONDIAGRAMINFO[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     디지털 입력 포인트 RDB 파일 Access
	// Parameters:
	//     nIndex        - 디지털 입력 포인트 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DISCRETE GetIndexDiscrete(UINT nIndex) {return (LPST_COMMON_DISCRETE)HMISHARE_GET_DATA(FILE_DISCRETE, nIndex);}
	static LPST_COMMON_DISCRETE GetDiscrete(UINT nIndex) {return (LPST_COMMON_DISCRETE)&g_pCommonDISCRETE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DO RDB 파일 Access
	// Parameters:
	//     nIndex        - DO RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SETDISCRETE GetIndexSetDiscrete(UINT nIndex) {return (LPST_COMMON_SETDISCRETE)HMISHARE_GET_DATA(FILE_SETDISCRETE, nIndex);}
	static LPST_COMMON_SETDISCRETE GetSetDiscrete(UINT nIndex) {return (LPST_COMMON_SETDISCRETE)&g_pCommonSETDISCRETE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     아날로그 입력 포인트 RDB 파일 Access
	// Parameters:
	//     nIndex        - 아날로그 입력 포인트 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_MEASUREMENT GetIndexMesurement(UINT nIndex) {return (LPST_COMMON_MEASUREMENT)HMISHARE_GET_DATA(FILE_MEASUREMENT, nIndex);}
	static LPST_COMMON_MEASUREMENT GetMesurement(UINT nIndex) {return (LPST_COMMON_MEASUREMENT)&g_pCommonMEASUREMENT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     AO RDB 파일 Access
	// Parameters:
	//     nIndex        - AO RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SETMEASUREMENT GetIndexSetMesurement(UINT nIndex) {return (LPST_COMMON_SETMEASUREMENT)HMISHARE_GET_DATA(FILE_SETMEASUREMENT, nIndex);}
	static LPST_COMMON_SETMEASUREMENT GetSetMesurement(UINT nIndex) {return (LPST_COMMON_SETMEASUREMENT)&g_pCommonSETMEASUREMENT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     카운터 포인트 정의 RDB 파일 Access
	// Parameters:
	//     nIndex        - ACCUMULATOR RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACCUMULATOR GetIndexAccumulator(UINT nIndex) {return (LPST_COMMON_ACCUMULATOR)HMISHARE_GET_DATA(FILE_ACCUMULATOR, nIndex);}
	static LPST_COMMON_ACCUMULATOR GetAccumulator(UINT nIndex) {return (LPST_COMMON_ACCUMULATOR)&g_pCommonACCUMULATOR[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     계산 포인트 정의 정의 RDB 파일 Access
	// Parameters:
	//     nIndex        - CALCULATION RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_CALCULATION GetIndexCal(UINT nIndex) {return (LPST_COMMON_CALCULATION)HMISHARE_GET_DATA(FILE_CALCULATION, nIndex);}
	static LPST_COMMON_CALCULATION GetCal(UINT nIndex) {return (LPST_COMMON_CALCULATION)&g_pCommonCALCULATION[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     계통도 설비 구성 포인트 RDB 파일 Access
	// Parameters:
	//     nIndex        - POSITION RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_POSITION GetIndexPosition(UINT nIndex) {return (LPST_COMMON_POSITION)HMISHARE_GET_DATA(FILE_POSITION, nIndex);}
	static LPST_COMMON_POSITION GetPosition(UINT nIndex) {return (LPST_COMMON_POSITION)&g_pCommonPOSITION[nIndex];}


	//-----------------------------------------------------------------------
	// Summary:
	//     WATER 설비 구성 포인트 RDB 파일 Access
	// Parameters:
	//     nIndex        - WATER RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_WATER GetIndexWater(UINT nIndex) {return (LPST_COMMON_WATER)HMISHARE_GET_DATA(FILE_WATER, nIndex);}
	static LPST_COMMON_WATER GetWater(UINT nIndex) {return (LPST_COMMON_WATER)&g_pCommonWATER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ACM APPGROUP RDB 파일 Access
	// Parameters:
	//     nIndex        -  ACM APPGROUP RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACM_APPGROUP GetIndexAcmAppGroup(UINT nIndex) {return (LPST_COMMON_ACM_APPGROUP)HMISHARE_GET_DATA(FILE_ACM_APPGROUP, nIndex);}
	static LPST_COMMON_ACM_APPGROUP GetAcmAppGroup(UINT nIndex) {return (LPST_COMMON_ACM_APPGROUP)&g_pCommonACM_APPGROUP[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ACM MAPINDEX RDB 파일 Access
	// Parameters:
	//     nIndex        -  ACM MAPINDEX RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACM_MAPINDEX GetIndexAcmMapIndex(UINT nIndex) {return (LPST_COMMON_ACM_MAPINDEX)HMISHARE_GET_DATA(FILE_ACM_MAPINDEX, nIndex);}
	static LPST_COMMON_ACM_MAPINDEX GetAcmMapIndex(UINT nIndex) {return (LPST_COMMON_ACM_MAPINDEX)&g_pCommonACM_MAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ACM TABLE RDB 파일 Access
	// Parameters:
	//     nIndex        -  ACM TABLE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACM_TABLE GetIndexAcmTable(UINT nIndex) {return (LPST_COMMON_ACM_TABLE)HMISHARE_GET_DATA(FILE_ACM_TABLE, nIndex);}
	static LPST_COMMON_ACM_TABLE GetAcmTable(UINT nIndex) {return (LPST_COMMON_ACM_TABLE)&g_pCommonACM_TABLE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ACM TABLEGROUP RDB 파일 Access
	// Parameters:
	//     nIndex        -  ACM TABLE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACM_TABLEGROUP GetIndexAcmTableGroup(UINT nIndex) {return (LPST_COMMON_ACM_TABLEGROUP)HMISHARE_GET_DATA(FILE_ACM_TABLEGROUP, nIndex);}
	static LPST_COMMON_ACM_TABLEGROUP GetAcmTableGroup(UINT nIndex) {return (LPST_COMMON_ACM_TABLEGROUP)&g_pCommonACM_TABLEGROUP[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     PCS RDB 파일 Access
	// Parameters:
	//     nIndex        -  PCS RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PCS GetIndexPcs(UINT nIndex) {return (LPST_COMMON_PCS)HMISHARE_GET_DATA(FILE_PCS, nIndex);}
	static LPST_COMMON_PCS GetPcs(UINT nIndex) {return (LPST_COMMON_PCS)&g_pCommonPCS[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     MAINTRANSFORMER RDB 파일 Access
	// Parameters:
	//     nIndex        -  MAINTRANSFORMER RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_MAINTRANSFORMER GetIndexMainTransformer(UINT nIndex) {return (LPST_COMMON_MAINTRANSFORMER)HMISHARE_GET_DATA(FILE_MAINTRANSFORMER, nIndex);}
	static LPST_COMMON_MAINTRANSFORMER GetMainTransformer(UINT nIndex) {return (LPST_COMMON_MAINTRANSFORMER)&g_pCommonMAINTRANSFORMER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     VIRTUAL_LINE RDB 파일 Access
	// Parameters:
	//     nIndex        -  VIRTUAL_LINE RDB RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_COMMON_VIRTUAL_LINE GetIndexVirtualLine(UINT nIndex) {return (LPST_COMMON_VIRTUAL_LINE)HMISHARE_GET_DATA(FILE_VIRTUAL_LINE, nIndex);}
	static LPST_COMMON_VIRTUAL_LINE GetVirtualLine(UINT nIndex) {return (LPST_COMMON_VIRTUAL_LINE)&g_pCommonVIRTUAL_LINE[nIndex];}


	//-----------------------------------------------------------------------
	// Summary:
	//     메모 관리 RDB 파일 Access
	// Parameters:
	//     nIndex        - Memo RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_OPR_MEMO GetIndexMemo(UINT nIndex) {return (LPST_OPR_MEMO)HMISHARE_GET_DATA(FILE_MEMO, nIndex);}
	static LPST_OPR_MEMO GetMemo(UINT nIndex) {return (LPST_OPR_MEMO)&g_pOprMEMO[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     공지사항 관리 RDB 파일 Access
	// Parameters:
	//     nIndex        - MESSAGE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_OPR_MESSAGE GetIndexMessage(UINT nIndex) {return (LPST_OPR_MESSAGE)HMISHARE_GET_DATA(FILE_MESSAGE, nIndex);}
	static LPST_OPR_MESSAGE GetMessage(UINT nIndex) {return (LPST_OPR_MESSAGE)&g_pOprMESSAGE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     작업관리 관리 RDB 파일 Access
	// Parameters:
	//     nIndex        - CONSTRUCTION RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_OPR_CONSTRUCTION GetIndexContruction(UINT nIndex) {return (LPST_OPR_CONSTRUCTION)HMISHARE_GET_DATA(FILE_CONSTRUCTION, nIndex);}
	static LPST_OPR_CONSTRUCTION GetContruction(UINT nIndex) {return (LPST_OPR_CONSTRUCTION)&g_pOprCONSTRUCTION[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     사령원 관리 테이블 관리 RDB 파일 Access
	// Parameters:
	//     nIndex        - 사령원 관리 테이블 RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_OPR_OPERATORASSIGN GetIndexOpAssign(UINT nIndex) {return (LPST_OPR_OPERATORASSIGN)HMISHARE_GET_DATA(FILE_CONSTRUCTION, nIndex);}
	static LPST_OPR_OPERATORASSIGN GetOpAssign(UINT nIndex) {return (LPST_OPR_OPERATORASSIGN)&g_pOprOPERATORASSIGN[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//   파형목록 파일을 저장하는 테이블 RDB 파일 Access
	// Parameters:
	//     nIndex        - WAVE_LIST RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_OPR_WAVE_LIST GetIndexOpWaveList(UINT nIndex) {return (LPST_OPR_WAVE_LIST)HMISHARE_GET_DATA(FILE_WAVE_LIST, nIndex);}
	static LPST_OPR_WAVE_LIST GetOpWaveList(UINT nIndex) {return (LPST_OPR_WAVE_LIST)&g_pOprWAVE_LIST[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//   파형 파일을 저장하는 테이블 RDB 파일 Access
	// Parameters:
	//     nIndex        - WAVE_FILE RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_OPR_WAVE_FILE GetIndexOpWaveFile(UINT nIndex) {return (LPST_OPR_WAVE_FILE)HMISHARE_GET_DATA(FILE_WAVE_FILE, nIndex);}
	static LPST_OPR_WAVE_FILE GetOpWaveFile(UINT nIndex) {return (LPST_OPR_WAVE_FILE)&g_pOprWAVE_FILE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    서버 상태 데이터 저장 테이블 RDB 파일 Access
	// Parameters:
	//     nIndex        - OPERATORASSIGN RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_OPR_COMPUTERSTATUS GetIndexComStatus(UINT nIndex) {return (LPST_OPR_COMPUTERSTATUS)HMISHARE_GET_DATA(FILE_COMPUTERSTATUS, nIndex);}
	static LPST_OPR_COMPUTERSTATUS GetComStatus(UINT nIndex) {return (LPST_OPR_COMPUTERSTATUS)&g_pOprCOMPUTERSTATUS[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//   계산결과 저장 테이블 RDB 파일 Access
	// Parameters:
	//     nIndex        - OPERATORASSIGN RDB 파일 index
	//-----------------------------------------------------------------------
	static LPST_OPR_CALCULATION_RESULT GetIndexCalResult(UINT nIndex) {return (LPST_OPR_CALCULATION_RESULT)HMISHARE_GET_DATA(FILE_CALCULATION_RESULT, nIndex);}
	static LPST_OPR_CALCULATION_RESULT GetCalResult(UINT nIndex) {return (LPST_OPR_CALCULATION_RESULT)&g_pOprCALCULATION_RESULT[nIndex];}

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     열림 / 닫힘 포인트 체크 - 사용 안함
	// Parameters:
	//     equip			- 설비 id
	//     lPoint			- 포인트 id
	//     Type				- 포인트 타입
	//-----------------------------------------------------------------------
	static BOOL GetSwitchPoint(long equip, long lPoint, UINT Type);

	//-----------------------------------------------------------------------
	// Summary:
	//     F.I 포인트 체크
	// Parameters:
	//     equip			- 설비 id
	//     lPoint			- 포인트 id
	//     Type				- 포인트 타입
	//     pData			- FI data[out]
	//-----------------------------------------------------------------------
	static BOOL GetFIPoint(uPCComData m_uPcRtdata, long equip, long lPoint, UINT Type, FIDATA* pData);
	static BOOL GetAllFIPoint(uPCComData m_uPcRtdata, long equip, long lPoint, UINT Type, FIDATA* pData);
	//-----------------------------------------------------------------------
	// Summary:
	//     F.I 포인트 체크
	// Parameters:
	//     equip			- 설비 id
	//     lPoint			- 포인트 id
	//     Type				- 포인트 타입
	//     pData			- FI data[out]
	//-----------------------------------------------------------------------
	static BOOL GetFIPointData(int nMapID, long equip, UINT Type, FIDATA* pData);

	//-----------------------------------------------------------------------
	// Summary:
	//     F.I 리스트 포인트 입력용
	// Parameters:
	//     fi				- FI data[in]
	//     fiList			- FI List data[out]
	//-----------------------------------------------------------------------
	static BOOL GetFIListPoint(FIDATA fi, FILISTDATA *fiList);
	//-----------------------------------------------------------------------
	// Summary:
	//     D/L 명 
	// Parameters:
	//     nIndex			- d/l index
	//     dlName			- D/L 정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetDLNameData(int nIndex, DIAGRAMLINEDATA* dlName);
	//-----------------------------------------------------------------------
	// Summary:
	//     D/L 명 
	// Parameters:
	//     nIndex			- s/s index
	//     dlName			- 변전소 명[out]
	//-----------------------------------------------------------------------
	static BOOL GetSubstationData(int nIndex, TCHAR* ssName);
	//-----------------------------------------------------------------------
	// Summary:
	//     RDB 파일 카운터
	// Parameters:
	//     pszFileName        - RDB 파일명
	//-----------------------------------------------------------------------
	static INT GetRDBFileListCount(TCHAR* pszFileName);
		//-----------------------------------------------------------------------
	// Summary:
	//     RDB 사활선 카운터
	// Parameters:
	//     
	//-----------------------------------------------------------------------
	static INT GetRDBLineCount();
	//-----------------------------------------------------------------------
	// Summary:
	//     ACM 파일 카운터
	// Parameters:
	//     pszFileName        - ACM 파일명
	//-----------------------------------------------------------------------
	static INT GetAsiFileListCount(TCHAR* pszFileName);

	//-----------------------------------------------------------------------
	// Summary:
	//     컴포짓 설비 count
	// Parameters:
	//     nIndex			- 설비 id
	//     id				- 포인트 id[out]
	//     psrid			- psr id[out]
	//     szname			- 설비명[out]
	//-----------------------------------------------------------------------
	static INT GetCompositeInEquipCount(int nIndex, long* id, long* psrid, TCHAR* szname);
	//-----------------------------------------------------------------------
	// Summary:
	//     지중변압기 설비 count
	// Parameters:
	//     nIndex			- 설비 id
	//     id				- 포인트 id[out]
	//     psrid			- psr id[out]
	//     szname			- 설비명[out]
	//-----------------------------------------------------------------------
	static INT GetUnderTrInEquipName(int nIndex, long* id, TCHAR* szname);
	//-----------------------------------------------------------------------
	// Summary:
	//     Distribution Tr 설비 카운트
	// Parameters:
	//     nIndex		- 설비 id
	//     pdata		- 설비 정보[out]	
	//-----------------------------------------------------------------------

	static INT GetSVREquipName(int nIndex, long* id, TCHAR* szname);
	//-----------------------------------------------------------------------
	// Summary:
	//     설비정보(전체)
	// Parameters:
	//     nIndex		- 설비 id
	//     pdata		- 설비 정보[out]	
	//-----------------------------------------------------------------------

	static BOOL GetCondectionEquipData(int nIndex, BLOCKVIEWDATA* pdata);
	//-----------------------------------------------------------------------
	// Summary:
	//     변전소 설비정보(전체)
	// Parameters:
	//     nIndex		- 설비 id
	//     pdata		- 설비 정보[out]	
	//-----------------------------------------------------------------------

	static BOOL GetCondectionEquipSubData(int nIndex, BLOCKSUBDATA* pdata);
	//-----------------------------------------------------------------------
	// Summary:
	//     태양광 발전기(전체) PV + BESS
	// Parameters:
	//     nIndex		- 설비 id
	//     pdata		- 설비 정보[out]	
	//-----------------------------------------------------------------------

	static BOOL GetCondectionEquipPVData(int nIndex, BLOCKPVDATA* pdata);
	static BOOL GetCondectionEquipBESSData(int nIndex, BLOCKBESSDATA* pdata);
	//-----------------------------------------------------------------------
	// Summary:
	//     설비제어정보
	// Parameters:
	//     equipid			- 설비 id
	//     psrid			- psr id
	//     pInfo			- 설비제어정보[out]
	//-----------------------------------------------------------------------
	
	static BOOL GeCtrlInfo(long equipid, long psrid, UNITCTRLINFO* pInfo);
	//-----------------------------------------------------------------------
	// Summary:
	//     설비제어정보
	// Parameters:
	//     equipid			- 설비 id
	//     psrid			- psr id
	//     pInfo			- 설비제어정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetUnitInfo(long equipid, long psrid, UNITINFO* pinfo);

	//-----------------------------------------------------------------------
	// Summary:
	//     설비제어정보(DO)
	// Parameters:
	//     equipid			- 설비 id
	//     dlid				- D/L id
	//     deviceId			- RTU Device  id
	//     list				- 설비제어정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetCtrlInfo(long equipid, long dlid, long deviceId, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list);

	//-----------------------------------------------------------------------
	// Summary:
	//     설비상태정보(DI)
	// Parameters:
	//     equipid			- 설비 id
	//     dlid				- D/L id
	//     remoteid			- 리모트 유닛 id
	//     list				- 설비상태정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetStatInfo(long equipid, long dlid, long remote, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list);
	//-----------------------------------------------------------------------
	// Summary:
	//     SVR의 SVR뱅크로 Conducting Equipment List의 내부 설비를 찾음
	// Parameters:
	//     svrid			- SVR 뱅크 아이디
	//	   return			- SVR 뱅크의 첫번째 내부 Winding 아이디
	//-----------------------------------------------------------------------
	static int GetSVRConductEquipmentInfo(long svrid);

	//-----------------------------------------------------------------------
	// Summary:
	//     고압수용가정보
	// Parameters:
	//     equipid			- 설비 id
	//     psrid			- psr id
	//     pinfo			- 고압수용가정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetEnergyCom(long equipid, long psrid, ENERGYCON* pinfo);

	//-----------------------------------------------------------------------
	// Summary:
	//     선로정보
	// Parameters:
	//     equipid			- 설비 id
	//     psrid			- psr id
	//     pinfo			- 선로정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetLineSec(long equipid, long psrid, LINESEC* pinfo);

	//-----------------------------------------------------------------------
	// Summary:
	//     설비정보(검색)
	// Parameters:
	//     geo			- 지사
	//     sub			- 지점
	//     station		- 변전소
	//     dl			- D/L
	//     pdata		- 검색 리스트정보[out]	
	//-----------------------------------------------------------------------
	static BOOL GetEquipList(long geo, long sub, long station, long dl, CList<SEARCHDATA*, SEARCHDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     설비정보(검색)
	// Parameters:
	//     pdata			- 검색 리스트정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetEquipList(CList<SEARCHDATA*, SEARCHDATA*>* pdata);
	static BOOL GetSubStationList(CList<SEARCHDATA*, SEARCHDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     설비정보(DI 포인트)
	// Parameters:
	//     ceq			- 설비 id
	//     device		- 리모트유닛 id
	//     pdata		- 설비 포인트[out]
	//-----------------------------------------------------------------------
	static BOOL GetRemoteBIPoint(long ceq, long device, CList<BIMENUALDATA*, BIMENUALDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     설비정보(AI 포인트)
	// Parameters:
	//     ceq			- 설비 id
	//     device		- RTU Device유닛 id
	//     pdata		- 설비 포인트[out]
	//-----------------------------------------------------------------------
	static BOOL GetRemoteAIPoint(long ceq, long device, CList<AIMENUALDATA*, AIMENUALDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     Dts 설비정보(AI 포인트)
	// Parameters:
	//     ceq			- 설비 id
	//     remote		- 리모트유닛 id
	//     pdata		- 설비 포인트[out]
	//-----------------------------------------------------------------------
	//static BOOL GetDtsRemoteAIPoint(long ceq, long remote, CList<AIMENUALDATA*, AIMENUALDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     설비정보(DO 포인트)
	// Parameters:
	//     ceq			- 설비 id
	//     device		- 리모트유닛 id
	//     pdata		- 설비 포인트[out]
	//-----------------------------------------------------------------------
	static BOOL GetRemoteBOPoint(long ceq, long device, CList<BIMENUALDATA*, BIMENUALDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     설비정보(AO 포인트)
	// Parameters:
	//     ceq			- 설비 id
	//     device		- 리모트유닛 id
	//     pdata		- 설비 포인트[out]
	//-----------------------------------------------------------------------
	static BOOL GetRemoteAOPoint(long ceq, long device, CList<AIMENUALDATA*, AIMENUALDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     설비정보(열림/닫힘 포인트)
	// Parameters:
	//     station		- 변전소
	//     dl			- D/L
	//     device		- 리모트유닛 id
	//     pid			- 설비 열림/닫힘 포인트[out]
	//-----------------------------------------------------------------------
	static BOOL GetRemoteOpenPoint(long station, long dl, long device, long ceq, long* pid);

	//-----------------------------------------------------------------------
	// Summary:
	//     리모트유닛 id
	// Parameters:
	//     cequip		- 설비id
	//     device		- 리모트유닛 id[out]
	//-----------------------------------------------------------------------
	static BOOL CRDBMgr::GetEquipIdToRemoteId(long cequip, long* device);

	//-----------------------------------------------------------------------
	// Summary:
	//     리모트유닛 분산전원 정보
	// Parameters:
	//     lline			- 회로(단일일경우 0)
	//     punit			- 리모트 유닛정보
	//     pdrunit			- 분산전원 정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetDRInfo(long lline, long ceqid, DRUNIT* pdrunit);

	//-----------------------------------------------------------------------
	// Summary:
	//     DTS 정보
	// Parameters:
	//     ceqid			- conduct Equipment id
	//     pdata			- DTS 정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetDtsInfo(long ceqid, CList<DTSINFO*, DTSINFO*>* pdata);
	static int GetDtsCount(long ceqid);
	static int GetDtsSectionID(long ceqid);
	//-----------------------------------------------------------------------
	// Summary:
	//     리모트유닛 RDB 파일 Access
	// Parameters:
	//     nIndex        - 리모트유닛 RDB 파일 index
	//-----------------------------------------------------------------------
	//static LPST_RTDB_LINEST GetLineStatus(UINT nIndex) {return (LPST_RTDB_LINEST)&g_pRTDBLinest[nIndex];}
	//-----------------------------------------------------------------------
	// Summary:
	//     Transformer BI정보
	// Parameters:
	//     ceqid			- conduct Equipment id
	//     pdata			- Transformer ;정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetAmiBIPoint(long ceqid, TRANSFORMERLIST* pdata);
	static BOOL GetAmiBIPoint(long ceqid, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list);

	//-----------------------------------------------------------------------
	// Summary:
	//     Transformer AI 정보
	// Parameters:
	//     ceqid			- conduct Equipment id
	//     pdata			- Transformer ;정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetAmiAIPoint(long ceqid, CList<UNITANALOGININFO*, UNITANALOGININFO*>* list);

	//-----------------------------------------------------------------------
	// Summary:
	//    color 포인트 RDB 파일 Access
	// Parameters:
	//     nIndex        - color code 포인트 RDB 파일 index
	//-----------------------------------------------------------------------
	//static LPST_RDB_COLOR GetColor(UINT nIndex) {return (LPST_RDB_COLOR)&g_pRDBColor[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DMC RDB 파일 Access
	// Parameters:
	//     nIndex        - DMC RDB 파일 index
	//-----------------------------------------------------------------------
	//static LPST_RDB_DMC GetDMC(UINT nIndex) {return (LPST_RDB_DMC)&g_pRDBDmc[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     소속 D/L 의 리모트 정보
	// Parameters:
	//     eqcfk			- equipment container ID
	//     dlid				- D/L id
	//     pInfo			- 리모트 유닛정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetEquipInfoFromTransBankAI(long eqcfk, long dlid, CList<UNITANALOGININFO*, UNITANALOGININFO*>* list);

	//-----------------------------------------------------------------------
	// Summary:
	//     설비제어정보(DO)
	// Parameters:
	//     eqcfk			- 설비 id
	//     dlid				- D/L id
	//     list				- 설비제어정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetEquipInfoFromTransBankBO(long eqcfk, long dlid, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list);
	//-----------------------------------------------------------------------
	// Summary:
	//     연계 설비 정보 취득
	// Parameters:
	//     nDL				- 소속 DL
	//     list				- 소속 DL의 연계설비 정보[out]s
	//-----------------------------------------------------------------------
	static BOOL GetTieSWInfo(int nDL, CList<TIESWITCH*, TIESWITCH*>* list);
	//-----------------------------------------------------------------------
	// Summary:
	//     모든 연계 설비 정보 취득
	// Parameters:
	//     list				- 소속 DL의 연계설비 정보[out]
	//-----------------------------------------------------------------------
	static BOOL GetAllTieSWInfo(CList<TIESWITCH*, TIESWITCH*>* list);
	//-----------------------------------------------------------------------
	// Summary:
	//     설비제어정보(DO)
	// Parameters:
	//     pointid			- pointid
	//     pointtype		- pointtype
	//-----------------------------------------------------------------------
	static BOOL IsAccessArea(long pointid, long pointtype);
	//-----------------------------------------------------------------------
	// Summary:
	//     데이터베이스에서 RDB 데이터 가져와 공유메모리 생성
	// Parameters:
	//-----------------------------------------------------------------------

	static BOOL CreateSharedDB();
	static BOOL AllUpdateSharedDB();
	static BOOL UpdateSharedDB(TCHAR *tTableName);

	//-----------------------------------------------------------------------
	// Summary:
	//     데이터베이스에서 미들웨어 전체 포인트 요청을 데이터 추출 
	// Parameters: iCeqid : CEQ id, list : 해당 설비의 포인트 리스트
	//-----------------------------------------------------------------------
	static BOOL GetMwDataPoint(int iCeqid, CList<MWPOINTINFO*, MWPOINTINFO*>* list);

	//-----------------------------------------------------------------------
	// Summary:
	//		CEQ를 RTU 아이디로 변환
	// Parameters: iCeqid : CEQ id, 
	//-----------------------------------------------------------------------
	static BOOL GetCeqToRtu(int iCeqid, int &iRtuId);

	//-----------------------------------------------------------------------
	// Summary:
	//		포인트 번호로 RTUMap Id 와 Index 추출
	// Parameters: iCeqid : CEQ id, 
	//-----------------------------------------------------------------------
	static BOOL    GetPointToIndex(int iPtNo, int PtType, int &iRtumap, int &iIndex);
	static CString TlqToString(unsigned short tlq_id);
	static CString SelectToQuery( CString strDBName, CString strSPName, CString strTBName );
	static void	   GetBIPointUpcName( MWPOINTINFO* pItem );	
	static CString GetDataPointName( int nCEQID );																// 데이터그룹에 따른 UPC이름 체크
	static CString GetCalcPointName( int nPID   );																// 데이터그룹에 따른 UPC이름 체크 : 계산포인트
	static CString GetStringComma  ( float fValue, int nDigit );												// 천단위 숫자에 콤마를 넣어준다
	static CString GetACMDataPointName( int nCEQID );															// 데이터그룹에 따른 ACM UPC이름 체크
	static CString GetStateSetName ( int nRTUMAPID, int nPOSITION, int nVALUE, int nTYPE = POINT_TYPE_BI );		// STATEGRP에 따른 STATESET 이름을 가져온다
	static CString GetTlqName	   ( int nTlqNum );
	static BOOL	   CheckUseControl  ( int nCEQID, BOOL bMsg = FALSE );											// 제어할수있는 데이터그룹인지 체크
	static BOOL	   SetSqlConnect    ();																			// SQL 연결
	static void	   SetSqlDisconnect ();																			// SQL 연결 해제
	static void	   EndControlProcess();																			// 제어창 종료 메세지
	static void	   SendAsyncQue     ( int nPGID, CString strClientName, CString strLogHMI );
	static void	   InsertControlLog ( int nCEQID, int nRUID, int nControlType, int nPointType, int nMAPID, float fOldVal, float fSetVal, int nComputerID, CString strOperName, CString strReason );
	static void	   InsertControlLog2( int nCEQID, int nRUID, int nControlType, int nPointType, int nMAPID, float fOldVal, float fSetVal, int nComputerID, CString strOperName, CString strReason );
	static void	   InsertAlarmAck   ( int nCEQID, CString strCreateTime, CString strContents, CString strAckUser, int nIMPORTANT, CString strHMIId );
	
	static int	   GetPointMapId    ( int nCEQID, int nControlType, int nPosition );
	static int	   CheckTlqPsLock   ( int nCEQID, int nControlType, int nMapId );
	static int	   CheckControlPriority();
	static CPoint  GetMonitorCenterPoint( HWND hWnd );
};