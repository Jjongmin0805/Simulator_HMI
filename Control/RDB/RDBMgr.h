#pragma once

#ifdef __COMMON_H__
#include "../Include/Common.h"
#endif
//-----------------------------------------------------------------------
// Summary:
//     ���뵵 ���α׷� �� ť ��� �ε���
//-----------------------------------------------------------------------
enum HMI_APP_CODE
{
	HMI_QUEUE	= 0,
	HMI_APP_TAB1,	//�� ���� ���α׷� ���� �����Ͽ� ���(�ִ� 20 Index ����) 	
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
//     ���뵵 RDB ���� �޸� ���� class
//-----------------------------------------------------------------------
class CRDBMgr
{
public:
	CRDBMgr(void) {}
	~CRDBMgr(void) {}

public:

	//-----------------------------------------------------------------------
	// Summary:
	//     CIM���� ����Ǵ� �������� RDB ���� Access
	// Parameters:
	//     nIndex        - ���� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_IDENTIFIEDOBJECT GetIdent(UINT nIndex) {return (LPST_COMMON_IDENTIFIEDOBJECT)&g_pCommonIDENTIFIEDOBJECT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ����(����) RDB ���� Access
	// Parameters:
	//     nIndex        - ����(����) RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_GEOGRAPHICALREGION GetIndexGeoGraphic(UINT nIndex) {return (LPST_COMMON_GEOGRAPHICALREGION)HMISHARE_GET_DATA(FILE_GEOGRAPHICALREGION, nIndex);}
	static LPST_COMMON_GEOGRAPHICALREGION GetGeoGraphic(UINT nIndex) {return (LPST_COMMON_GEOGRAPHICALREGION)&g_pCommonGEOGRAPHICALREGION[nIndex];}
	
	//-----------------------------------------------------------------------
	// Summary:
	//     ����(���ϻ����) RDB ���� Access
	// Parameters:
	//     nIndex        - ���� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SUBGEOGRAPHICALREGION GetIndexSubGeoGraphic(UINT nIndex) {return (LPST_COMMON_SUBGEOGRAPHICALREGION)HMISHARE_GET_DATA(FILE_SUBGEOGRAPHICALREGION, nIndex);}
	static LPST_COMMON_SUBGEOGRAPHICALREGION GetSubGeoGraphic(UINT nIndex) {return (LPST_COMMON_SUBGEOGRAPHICALREGION)&g_pCommonSUBGEOGRAPHICALREGION[nIndex];}
	
	//-----------------------------------------------------------------------
	// Summary:
	//     �ý��۳� DataPoint ������ ���� ���̺� RDB ���� Access
	// Parameters:
	//     nIndex        - DATAPOINTGROUPCODE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DATAPOINTGROUPCODE GetIndexDpGrp(UINT nIndex) {return (LPST_COMMON_DATAPOINTGROUPCODE)HMISHARE_GET_DATA(FILE_DATAPOINTGROUPCODE, nIndex);}
	static LPST_COMMON_DATAPOINTGROUPCODE GetDpGrp(UINT nIndex) {return (LPST_COMMON_DATAPOINTGROUPCODE)&g_pCommonDATAPOINTGROUPCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    ��ǻ��(�ý���) ���� ���̺� RDB ���� Access
	// Parameters:
	//     nIndex        - ��ǻ��(�ý���) ���� ���̺� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_COMPUTERCODE GetIndexComputer(UINT nIndex) {return (LPST_COMMON_COMPUTERCODE)HMISHARE_GET_DATA(FILE_OPERATORCODE, nIndex);}
	static LPST_COMMON_COMPUTERCODE GetComputer(UINT nIndex) {return (LPST_COMMON_COMPUTERCODE)&g_pCommonCOMPUTERCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ���α׷� ���� ���̺�    RDB ���� Access
	// Parameters:
	//     nIndex        - PROGRAMCODE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PROGRAMCODE GetIndexProCode(UINT nIndex) {return (LPST_COMMON_PROGRAMCODE)HMISHARE_GET_DATA(FILE_PROGRAMCODE, nIndex);}
	static LPST_COMMON_PROGRAMCODE GetProCode(UINT nIndex) {return (LPST_COMMON_PROGRAMCODE)&g_pCommonPROGRAMCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ��ɿ� ���� ���̺�     RDB ���� Access
	// Parameters:
	//     nIndex        - OPERATORCODE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_OPERATORCODE GetIndexOpCode(UINT nIndex) {return (LPST_COMMON_OPERATORCODE)HMISHARE_GET_DATA(FILE_OPERATORCODE, nIndex);}
	static LPST_COMMON_OPERATORCODE GetOpCode(UINT nIndex) {return (LPST_COMMON_OPERATORCODE)&g_pCommonOPERATORCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ����ġ ���� �ڵ�      RDB ���� Access
	// Parameters:
	//     nIndex        - SWITCHTYPECODE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SWITCHTYPECODE GetIndexSwitchType(UINT nIndex) {return (LPST_COMMON_SWITCHTYPECODE)HMISHARE_GET_DATA(FILE_SWITCHTYPECODE, nIndex);}
	static LPST_COMMON_SWITCHTYPECODE GetSwitchType(UINT nIndex) {return (LPST_COMMON_SWITCHTYPECODE)&g_pCommonSWITCHTYPECODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �۾����� ���̺�    RDB ���� Access
	// Parameters:
	//     nIndex        - CONSTRUCTIONCODE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_CONSTRUCTIONCODE GetIndexConstCode(UINT nIndex) {return (LPST_COMMON_CONSTRUCTIONCODE)HMISHARE_GET_DATA(FILE_CONSTRUCTIONCODE, nIndex);}
	static LPST_COMMON_CONSTRUCTIONCODE GetConstCode(UINT nIndex) {return (LPST_COMMON_CONSTRUCTIONCODE)&g_pCommonCONSTRUCTIONCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �������� Ÿ��       RDB ���� Access
	// Parameters:
	//     nIndex        - WAVECOMTYPE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_WAVECOMTYPE GetIndexWaveType(UINT nIndex) {return (LPST_COMMON_WAVECOMTYPE)HMISHARE_GET_DATA(FILE_WAVECOMTYPE, nIndex);}
	static LPST_COMMON_WAVECOMTYPE GetWaveType(UINT nIndex) {return (LPST_COMMON_WAVECOMTYPE)&g_pCommonWAVECOMTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ���°��� ���� ǥ�� �׷�        RDB ���� Access
	// Parameters:
	//     nIndex        - STATEGROUP RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_STATEGROUP GetIndexStateGroup(UINT nIndex) {return (LPST_COMMON_STATEGROUP)HMISHARE_GET_DATA(FILE_STATEGROUP, nIndex);}
	static LPST_COMMON_STATEGROUP GetStateGroup(UINT nIndex) {return (LPST_COMMON_STATEGROUP)&g_pCommonSTATEGROUP[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �ε����� ������ ����          RDB ���� Access
	// Parameters:
	//     nIndex        - DATABYTE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DATABYTE GetIndexDataByte(UINT nIndex) {return (LPST_COMMON_DATABYTE)HMISHARE_GET_DATA(FILE_DATABYTE, nIndex);}
	static LPST_COMMON_DATABYTE GetDataByte(UINT nIndex) {return (LPST_COMMON_DATABYTE)&g_pCommonDATABYTE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ���°��� ���� ���� ���̺� RDB ���� Access
	// Parameters:
	//     nIndex        - STATESET RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_STATESET GetIndexStateSet(UINT nIndex) {return (LPST_COMMON_STATESET)HMISHARE_GET_DATA(FILE_STATESET, nIndex);}
	static LPST_COMMON_STATESET GetStateSet(UINT nIndex) {return (LPST_COMMON_STATESET)&g_pCommonSTATESET[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ���� ǥ�� ����          RDB ���� Access
	// Parameters:
	//     nIndex        - DATABYTE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_UNIT GetIndexUnit(UINT nIndex) {return (LPST_COMMON_UNIT)HMISHARE_GET_DATA(FILE_UNIT, nIndex);}
	static LPST_COMMON_UNIT GetUnit(UINT nIndex) {return (LPST_COMMON_UNIT)&g_pCommonUNIT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ ����ǥ�ÿ� �� �ڵ� RDB ���� Access
	// Parameters:
	//     nIndex        - ���б� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SCALEFACTOR GetIndexScale(UINT nIndex) {return (LPST_COMMON_SCALEFACTOR)HMISHARE_GET_DATA(FILE_SCALEFACTOR, nIndex);}
	static LPST_COMMON_SCALEFACTOR GetScale(UINT nIndex) {return (LPST_COMMON_SCALEFACTOR)&g_pCommonSCALEFACTOR[nIndex];}
	
	//-----------------------------------------------------------------------
	// Summary:
	//     ����/���� �ڵ� RDB ���� Access
	// Parameters:
	//     nIndex        - ���б� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_LIMITCODE GetIndexLimitCode(UINT nIndex) {return (LPST_COMMON_LIMITCODE)HMISHARE_GET_DATA(FILE_LIMITCODE, nIndex);}
	static LPST_COMMON_LIMITCODE GetLimitCode(UINT nIndex) {return (LPST_COMMON_LIMITCODE)&g_pCommonLIMITCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ����/���� ���� RDB ���� Access
	// Parameters:
	//     nIndex        - ���б� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_LIMITSET GetIndexLimitSet(UINT nIndex) {return (LPST_COMMON_LIMITSET)HMISHARE_GET_DATA(FILE_LIMITSET, nIndex);}
	static LPST_COMMON_LIMITSET GetLimitSet(UINT nIndex) {return (LPST_COMMON_LIMITSET)&g_pCommonLIMITSET[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ��� ���ۻ�� ���̺� RDB ���� Access
	// Parameters:
	//     nIndex        - EQUIPCOMPANY RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_EQUIPCOMPANY GetIndexCompany(UINT nIndex) {return (LPST_COMMON_EQUIPCOMPANY)HMISHARE_GET_DATA(FILE_EQUIPCOMPANY, nIndex);}
	static LPST_COMMON_EQUIPCOMPANY GetCompany(UINT nIndex) {return (LPST_COMMON_EQUIPCOMPANY)&g_pCommonEQUIPCOMPANY[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ RDB ���� Access
	// Parameters:
	//     nIndex        - ������ RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SUBSTATION GetIndexSubStation(UINT nIndex) {return (LPST_COMMON_SUBSTATION)HMISHARE_GET_DATA(FILE_SUBSTATION, nIndex);}
	static LPST_COMMON_SUBSTATION GetSubStation(UINT nIndex) {return (LPST_COMMON_SUBSTATION)&g_pCommonSUBSTATION[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DL RDB ���� Access
	// Parameters:
	//     nIndex        - DL RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DISTRIBUTIONLINE GetIndexDLine(UINT nIndex) {return (LPST_COMMON_DISTRIBUTIONLINE)HMISHARE_GET_DATA(FILE_DISTRIBUTIONLINE, nIndex);}
	static LPST_COMMON_DISTRIBUTIONLINE GetDLine(UINT nIndex) {return (LPST_COMMON_DISTRIBUTIONLINE)&g_pCommonDISTRIBUTIONLINE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �������� ���� Access
	// Parameters:
	//     nIndex        - BASEVOLTAGE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_BASEVOLTAGE GetIndexBaseVoltage(UINT nIndex) {return (LPST_COMMON_BASEVOLTAGE)HMISHARE_GET_DATA(FILE_BASEVOLTAGE, nIndex);}
	static LPST_COMMON_BASEVOLTAGE GetBaseVoltage(UINT nIndex) {return (LPST_COMMON_BASEVOLTAGE)&g_pCommonBASEVOLTAGE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �������� ���� Access
	// Parameters:
	//     nIndex        - BASEPOWER RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_BASEPOWER GetIndexBasePower(UINT nIndex) {return (LPST_COMMON_BASEPOWER)HMISHARE_GET_DATA(FILE_BASEPOWER, nIndex);}
	static LPST_COMMON_BASEPOWER GetBasePower(UINT nIndex) {return (LPST_COMMON_BASEPOWER)&g_pCommonBASEPOWER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ���з��� ���� Access
	// Parameters:
	//     nIndex        - VOLTAGELEVEL RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_VOLTAGELEVEL GetIndexVoltageLevel(UINT nIndex) {return (LPST_COMMON_VOLTAGELEVEL)HMISHARE_GET_DATA(FILE_VOLTAGELEVEL, nIndex);}
	static LPST_COMMON_VOLTAGELEVEL GetVoltageLevel(UINT nIndex) {return (LPST_COMMON_VOLTAGELEVEL)&g_pCommonVOLTAGELEVEL[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �� ���� ���̺� ���� Access
	// Parameters:
	//     nIndex        - PHASE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PHASE GetIndexPhase(UINT nIndex) {return (LPST_COMMON_PHASE)HMISHARE_GET_DATA(FILE_PHASE, nIndex);}
	static LPST_COMMON_PHASE GetPhase(UINT nIndex) {return (LPST_COMMON_PHASE)&g_pCommonPHASE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     PROTOCOL TYPE ���̺� ���� Access
	// Parameters:
	//     nIndex        - PROTOCOLTYPE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PROTOCOLTYPE GetIndexProtocolType(UINT nIndex) {return (LPST_COMMON_PROTOCOLTYPE)HMISHARE_GET_DATA(FILE_PROTOCOLTYPE, nIndex);}
	static LPST_COMMON_PROTOCOLTYPE GetProtocolType(UINT nIndex) {return (LPST_COMMON_PROTOCOLTYPE)&g_pCommonPROTOCOLTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ��ġ���� Ÿ�� ���̺� ���� ���̺� ���� Access
	// Parameters:
	//     nIndex        - EQUIPMENTTYPE ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_EQUIPMENTTYPE GetIndexEqType(UINT nIndex) {return (LPST_COMMON_EQUIPMENTTYPE)HMISHARE_GET_DATA(FILE_EQUIPMENTTYPE, nIndex);}
	static LPST_COMMON_EQUIPMENTTYPE GetEqType(UINT nIndex) {return (LPST_COMMON_EQUIPMENTTYPE)&g_pCommonEQUIPMENTTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     RTU Map RDB ���� Access
	// Parameters:
	//     nIndex        - ����Ʈ����̽� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_RTUMAP GetIndexRTUMap(UINT nIndex) {return (LPST_COMMON_RTUMAP)HMISHARE_GET_DATA(FILE_RTUMAP, nIndex);}
	static LPST_COMMON_RTUMAP GetRTUMap(UINT nIndex) {return (LPST_COMMON_RTUMAP)&g_pCommonRTUMAP[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ��� ���� RDB ���� Access
	// Parameters:
	//     nIndex        - ���б� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_COMMTYPE GetIndexCommType(UINT nIndex) {return (LPST_COMMON_COMMTYPE)HMISHARE_GET_DATA(FILE_COMMTYPE, nIndex);}
	static LPST_COMMON_COMMTYPE GetCommType(UINT nIndex) {return (LPST_COMMON_COMMTYPE)&g_pCommonCOMMTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     RTU ���� �ڵ� ���̺� ���� Access
	// Parameters:
	//     nIndex        - RTUTYPE ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_RTUTYPE GetIndexRtuType(UINT nIndex) {return (LPST_COMMON_RTUTYPE)HMISHARE_GET_DATA(FILE_RTUTYPE, nIndex);}
	static LPST_COMMON_RTUTYPE GetRtuType(UINT nIndex) {return (LPST_COMMON_RTUTYPE)&g_pCommonRTUTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     HMI �� UI���� Subtab ������ RDB ���� Access
	// Parameters:
	//     nIndex        - CATEGORYCODE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_CATEGORYCODE GetIndexCatCode(UINT nIndex) {return (LPST_COMMON_CATEGORYCODE)HMISHARE_GET_DATA(FILE_CATEGORYCODE, nIndex);}
	static LPST_COMMON_CATEGORYCODE GetCatCode(UINT nIndex) {return (LPST_COMMON_CATEGORYCODE)&g_pCommonCATEGORYCODE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ����Ʈ ���� RDB ���� Access
	// Parameters:
	//     nIndex        - MEASURETYPEINFO RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_MEASURETYPEINFO GetIndexMtInfo(UINT nIndex) {return (LPST_COMMON_MEASURETYPEINFO)HMISHARE_GET_DATA(FILE_MEASURETYPEINFO, nIndex);}
	static LPST_COMMON_MEASURETYPEINFO GetMtInfo(UINT nIndex) {return (LPST_COMMON_MEASURETYPEINFO)&g_pCommonMEASURETYPEINFO[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DNP_BI_MAPINDEX  RDB ���� Access
	// Parameters:
	//     nIndex        - ���� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DNPBIMAPINDEX GetIndexDnpBI(UINT nIndex) {return (LPST_COMMON_DNPBIMAPINDEX)HMISHARE_GET_DATA(FILE_DNPBIMAPINDEX, nIndex);}
	static LPST_COMMON_DNPBIMAPINDEX GetDnpBI(UINT nIndex) {return (LPST_COMMON_DNPBIMAPINDEX)&g_pCommonDNPBIMAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DNP_B0_MAPINDEX  RDB ���� Access
	// Parameters:
	//     nIndex        - ���� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DNPBOMAPINDEX GetIndexDnpBO(UINT nIndex) {return (LPST_COMMON_DNPBOMAPINDEX)HMISHARE_GET_DATA(FILE_DNPBOMAPINDEX, nIndex);}
	static LPST_COMMON_DNPBOMAPINDEX GetDnpBO(UINT nIndex) {return (LPST_COMMON_DNPBOMAPINDEX)&g_pCommonDNPBOMAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DNP_AI_MAPINDEX  RDB ���� Access
	// Parameters:
	//     nIndex        - ���� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DNPAIMAPINDEX GetIndexDnpAI(UINT nIndex) {return (LPST_COMMON_DNPAIMAPINDEX)HMISHARE_GET_DATA(FILE_DNPAIMAPINDEX, nIndex);}
	static LPST_COMMON_DNPAIMAPINDEX GetDnpAI(UINT nIndex) {return (LPST_COMMON_DNPAIMAPINDEX)&g_pCommonDNPAIMAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DNP_AO_MAPINDEX  RDB ���� Access
	// Parameters:
	//     nIndex        - ���� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DNPAOMAPINDEX GetIndexDnpAO(UINT nIndex) {return (LPST_COMMON_DNPAOMAPINDEX)HMISHARE_GET_DATA(FILE_DNPAOMAPINDEX, nIndex);}
	static LPST_COMMON_DNPAOMAPINDEX GetDnpAO(UINT nIndex) {return (LPST_COMMON_DNPAOMAPINDEX)&g_pCommonDNPAOMAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DNP_COUNTER_MAPINDEX  RDB ���� Access
	// Parameters:
	//     nIndex        - ���� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DNPCOUNTERMAPINDEX GetIndexDnpCOUNTER(UINT nIndex) {return (LPST_COMMON_DNPCOUNTERMAPINDEX)HMISHARE_GET_DATA(FILE_DNPCOUNTERMAPINDEX, nIndex);}
	static LPST_COMMON_DNPCOUNTERMAPINDEX GetDnpCOUNTER(UINT nIndex) {return (LPST_COMMON_DNPCOUNTERMAPINDEX)&g_pCommonDNPCOUNTERMAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ ��� ���� RDB ���� Access
	// Parameters:
	//     nIndex        - ����Ʈ����̽� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_RTUDEVICE GetIndexRTUDevice(UINT nIndex) {return (LPST_COMMON_RTUDEVICE)HMISHARE_GET_DATA(FILE_RTUDEVICE, nIndex);}
	static LPST_COMMON_RTUDEVICE GetRTUDevice(UINT nIndex) {return (LPST_COMMON_RTUDEVICE)&g_pCommonRTUDEVICE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ ���� RDB ���� Access
	// Parameters:
	//     nIndex        - ���� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_CONDUCTINGEQUIPMENT GetIndexEquip(UINT nIndex) {return (LPST_COMMON_CONDUCTINGEQUIPMENT)HMISHARE_GET_DATA(FILE_CONDUCTINGEQUIPMENT, nIndex);}
	static LPST_COMMON_CONDUCTINGEQUIPMENT GetEquip(UINT nIndex) {return (LPST_COMMON_CONDUCTINGEQUIPMENT)&g_pCommonCONDUCTINGEQUIPMENT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ����ġ ���� �ڵ�      RDB ���� Access
	// Parameters:
	//     nIndex        - SWITCHTYPECODE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SWITCH GetIndexSwitch(UINT nIndex) {return (LPST_COMMON_SWITCH)HMISHARE_GET_DATA(FILE_SWITCH, nIndex);}
	static LPST_COMMON_SWITCH GetSwitch(UINT nIndex) {return (LPST_COMMON_SWITCH)&g_pCommonSWITCH[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ���� ����      RDB ���� Access
	// Parameters:
	//     nIndex        - ACLINESEGMENT RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACLINESEGMENT GetIndexAcLine(UINT nIndex) {return (LPST_COMMON_ACLINESEGMENT)HMISHARE_GET_DATA(FILE_ACLINESEGMENT, nIndex);}	
	static LPST_COMMON_ACLINESEGMENT GetAcLine(UINT nIndex) {return (LPST_COMMON_ACLINESEGMENT)&g_pCommonACLINESEGMENT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ���� ����      RDB ���� Access
	// Parameters:
	//     nIndex        - PERLENGTHSEQUENCEIMPEDANCE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE GetIndexPerLeng(UINT nIndex) {return (LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE)HMISHARE_GET_DATA(FILE_PERLENGTHSEQUENCEIMPEDANCE, nIndex);}	
	static LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE GetPerLeng(UINT nIndex) {return (LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE)&g_pCommonPERLENGTHSEQUENCEIMPEDANCE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    ������ �� BUSBARSECTION ����ǥ��      RDB ���� Access
	// Parameters:
	//     nIndex        - BUSBARSECTION RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_BUSBARSECTION GetIndexBusBar(UINT nIndex) {return (LPST_COMMON_BUSBARSECTION)HMISHARE_GET_DATA(FILE_BUSBARSECTION, nIndex);}	
	static LPST_COMMON_BUSBARSECTION GetBusBar(UINT nIndex) {return (LPST_COMMON_BUSBARSECTION)&g_pCommonBUSBARSECTION[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ RDB ���� Access
	// Parameters:
	//     nIndex        - ������ RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_COMPOSITESWITCH GetIndexComposite(UINT nIndex) {return (LPST_COMMON_COMPOSITESWITCH)HMISHARE_GET_DATA(FILE_COMPOSITESWITCH, nIndex);}
	static LPST_COMMON_COMPOSITESWITCH GetComposite(UINT nIndex) {return (LPST_COMMON_COMPOSITESWITCH)&g_pCommonCOMPOSITESWITCH[nIndex];}
	
	//-----------------------------------------------------------------------
	// Summary:
	//     ���б� RDB ���� Access
	// Parameters:
	//     nIndex        - ���б� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_POWERTRANSFORMER GetIndexPowerTr(UINT nIndex) {return (LPST_COMMON_POWERTRANSFORMER)HMISHARE_GET_DATA(FILE_POWERTRANSFORMER, nIndex);}
	static LPST_COMMON_POWERTRANSFORMER GetPowerTr(UINT nIndex) {return (LPST_COMMON_POWERTRANSFORMER)&g_pCommonPOWERTRANSFORMER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     Tap ����� RDB ���� Access
	// Parameters:
	//     nIndex        - TAPCHANGER RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_TAPCHANGER GetIndexTapChanger(UINT nIndex) {return (LPST_COMMON_TAPCHANGER)HMISHARE_GET_DATA(FILE_TAPCHANGER, nIndex);}
	static LPST_COMMON_TAPCHANGER GetTapChanger(UINT nIndex) {return (LPST_COMMON_TAPCHANGER)&g_pCommonTAPCHANGER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ���б� �ἱ RDB ���� Access
	// Parameters:
	//     nIndex        - ���б� �ἱ RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_TRANSFORMERWINDING GetIndexDisTransWind(UINT nIndex) {return (LPST_COMMON_TRANSFORMERWINDING)HMISHARE_GET_DATA(FILE_TRANSFORMERWINDING, nIndex);}
	static LPST_COMMON_TRANSFORMERWINDING GetDisTransWind(UINT nIndex) {return (LPST_COMMON_TRANSFORMERWINDING)&g_pCommonTRANSFORMERWINDING[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     Tap ���� ������ RDB ���� Access
	// Parameters:
	//     nIndex        - TAPREGULATIONSCHEDULE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_TAPREGULATIONSCHEDULE GetIndexTapSche(UINT nIndex) {return (LPST_COMMON_TAPREGULATIONSCHEDULE)HMISHARE_GET_DATA(FILE_TAPREGULATIONSCHEDULE, nIndex);}
	static LPST_COMMON_TAPREGULATIONSCHEDULE GetTapSche(UINT nIndex) {return (LPST_COMMON_TAPREGULATIONSCHEDULE)&g_pCommonTAPREGULATIONSCHEDULE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ��ȣ���� RDB ���� Access
	// Parameters:
	//     nIndex        - PROTECTIONEQUIPMENT RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PROTECTIONEQUIPMENT GetIndexProtect(UINT nIndex) {return (LPST_COMMON_PROTECTIONEQUIPMENT)HMISHARE_GET_DATA(FILE_PROTECTIONEQUIPMENT, nIndex);}
	static LPST_COMMON_PROTECTIONEQUIPMENT GetProtect(UINT nIndex) {return (LPST_COMMON_PROTECTIONEQUIPMENT)&g_pCommonPROTECTIONEQUIPMENT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ����ν����� RDB ���� Access
	// Parameters:
	//     nIndex        - RECLOSESEQUENCE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_RECLOSESEQUENCE GetIndexRecloser(UINT nIndex) {return (LPST_COMMON_RECLOSESEQUENCE)HMISHARE_GET_DATA(FILE_RECLOSESEQUENCE, nIndex);}
	static LPST_COMMON_RECLOSESEQUENCE GetRecloser(UINT nIndex) {return (LPST_COMMON_RECLOSESEQUENCE)&g_pCommonRECLOSESEQUENCE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ RDB ���� Access
	// Parameters:
	//     nIndex        - CURRENTRELAY RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_CURRENTRELAY GetIndexRelay(UINT nIndex) {return (LPST_COMMON_CURRENTRELAY)HMISHARE_GET_DATA(FILE_CURRENTRELAY, nIndex);}
	static LPST_COMMON_CURRENTRELAY GetRelay(UINT nIndex) {return (LPST_COMMON_CURRENTRELAY)&g_pCommonCURRENTRELAY[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ ������ġ RDB ���� Access
	// Parameters:
	//     nIndex        - CURRENTRELAY RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_BATTERYSTORAGE GetIndexBattery(UINT nIndex) {return (LPST_COMMON_BATTERYSTORAGE)HMISHARE_GET_DATA(FILE_BATTERYSTORAGE, nIndex);}
	static LPST_COMMON_BATTERYSTORAGE GetBattery(UINT nIndex) {return (LPST_COMMON_BATTERYSTORAGE)&g_pCommonBATTERYSTORAGE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ �Ǵ� ������ RDB ���� Access
	// Parameters:
	//     nIndex        - ������ �Ǵ� ������  RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_GENERATINGUNIT GetIndexGeneratingUnit(UINT nIndex) {return (LPST_COMMON_GENERATINGUNIT)HMISHARE_GET_DATA(FILE_GENERATINGUNIT, nIndex);}
	static LPST_COMMON_GENERATINGUNIT GetGeneratingUnit(UINT nIndex) {return (LPST_COMMON_GENERATINGUNIT)&g_pCommonGENERATINGUNIT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    ���º�ȯ��ġ RDB ���� Access
	// Parameters:
	//     nIndex        - GENREGULATIONSCHEDULE  RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_GENREGULATIONSCHEDULE GetIndexGenSche(UINT nIndex) {return (LPST_COMMON_GENREGULATIONSCHEDULE)HMISHARE_GET_DATA(FILE_GENREGULATIONSCHEDULE, nIndex);}
	static LPST_COMMON_GENREGULATIONSCHEDULE GetGenSche(UINT nIndex) {return (LPST_COMMON_GENREGULATIONSCHEDULE)&g_pCommonGENREGULATIONSCHEDULE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �л����� RDB ���� Access
	//		WindTurbine, PhotoVoltaic, BATTERYSTORAGE
	// Parameters:
	//     nIndex        - �л����� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_WINDTURBINE GetIndexWind(UINT nIndex) {return (LPST_COMMON_WINDTURBINE)HMISHARE_GET_DATA(FILE_WINDTURBINE, nIndex);}
	static LPST_COMMON_WINDTURBINE GetWind(UINT nIndex) {return (LPST_COMMON_WINDTURBINE)&g_pCommonWINDTURBINE[nIndex];}

	static LPST_COMMON_PHOTOVOLTAIC GetIndexPhoto(UINT nIndex) {return (LPST_COMMON_PHOTOVOLTAIC)HMISHARE_GET_DATA(FILE_PHOTOVOLTAIC, nIndex);}
	static LPST_COMMON_PHOTOVOLTAIC GetPhoto(UINT nIndex) {return (LPST_COMMON_PHOTOVOLTAIC)&g_pCommonPHOTOVOLTAIC[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ ����� � RDB ���� Access
	// Parameters:
	//     nIndex        - GENUNITOPCOSTCURVE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_GENUNITOPCOSTCURVE GetIndexGenCurve(UINT nIndex) {return (LPST_COMMON_GENUNITOPCOSTCURVE)HMISHARE_GET_DATA(FILE_GENUNITOPCOSTCURVE, nIndex);}
	static LPST_COMMON_GENUNITOPCOSTCURVE GetGenCurve(UINT nIndex) {return (LPST_COMMON_GENUNITOPCOSTCURVE)&g_pCommonGENUNITOPCOSTCURVE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ��м��밡 RDB ���� Access
	// Parameters:
	//     nIndex        - ENERGYCONSUMER RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ENERGYCONSUMER GetIndexEnergy(UINT nIndex) {return (LPST_COMMON_ENERGYCONSUMER)HMISHARE_GET_DATA(FILE_ENERGYCONSUMER, nIndex);}
	static LPST_COMMON_ENERGYCONSUMER GetEnergy(UINT nIndex) {return (LPST_COMMON_ENERGYCONSUMER)&g_pCommonENERGYCONSUMER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ���� ���������� RDB ���� Access
	// Parameters:
	//     nIndex        - SHUNTCOMPASATOR RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SHUNTCOMPASATOR GetIndexShunt(UINT nIndex) {return (LPST_COMMON_SHUNTCOMPASATOR)HMISHARE_GET_DATA(FILE_SHUNTCOMPASATOR, nIndex);}
	static LPST_COMMON_SHUNTCOMPASATOR GetShunt(UINT nIndex) {return (LPST_COMMON_SHUNTCOMPASATOR)&g_pCommonSHUNTCOMPASATOR[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ��ȿ���� ������ġ RDB ���� Access
	// Parameters:
	//     nIndex        - SHUNTCOMPASATOR RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_STATICVARCOMPENSATOR GetIndexSvr(UINT nIndex) {return (LPST_COMMON_STATICVARCOMPENSATOR)HMISHARE_GET_DATA(FILE_STATICVARCOMPENSATOR, nIndex);}
	static LPST_COMMON_STATICVARCOMPENSATOR GetSvr(UINT nIndex) {return (LPST_COMMON_STATICVARCOMPENSATOR)&g_pCommonSTATICVARCOMPENSATOR[nIndex];}
	
	//-----------------------------------------------------------------------
	// Summary:
	//     ���� �� ���հ����� ���� RDB ���� Access
	// Parameters:
	//     nIndex        - POWERSYSTEMRESOURCE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_POWERSYSTEMRESOURCE GetIndexPSR(UINT nIndex) {return (LPST_COMMON_POWERSYSTEMRESOURCE)HMISHARE_GET_DATA(FILE_POWERSYSTEMRESOURCE, nIndex);}
	static LPST_COMMON_POWERSYSTEMRESOURCE GetPSR(UINT nIndex) {return (LPST_COMMON_POWERSYSTEMRESOURCE)&g_pCommonPOWERSYSTEMRESOURCE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     PSR type RDB ���� Access
	// Parameters:
	//     nIndex        - ���� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PSRTYPE GetIndexPsrType(UINT nIndex) {return (LPST_COMMON_PSRTYPE)HMISHARE_GET_DATA(FILE_PSRTYPE, nIndex);}
	static LPST_COMMON_PSRTYPE GetPsrType(UINT nIndex) {return (LPST_COMMON_PSRTYPE)&g_pCommonPSRTYPE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    ���հ��� RDB ���� Access
	// Parameters:
	//     nIndex        - EQUIPMENTCONTAINER RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_EQUIPMENTCONTAINER GetIndexEqCon(UINT nIndex) {return (LPST_COMMON_EQUIPMENTCONTAINER)HMISHARE_GET_DATA(FILE_EQUIPMENTCONTAINER, nIndex);}
	static LPST_COMMON_EQUIPMENTCONTAINER GetEqCon(UINT nIndex) {return (LPST_COMMON_EQUIPMENTCONTAINER)&g_pCommonEQUIPMENTCONTAINER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    �ɺ� RDB ���� Access
	// Parameters:
	//     nIndex        - SYMBOL RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SYMBOL GetIndexSymbol(UINT nIndex) {return (LPST_COMMON_SYMBOL)HMISHARE_GET_DATA(FILE_SYMBOL, nIndex);}
	static LPST_COMMON_SYMBOL GetSymbol(UINT nIndex) {return (LPST_COMMON_SYMBOL)&g_pCommonSYMBOL[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    ���뵵 ������ �������� ���̺� Access
	// Parameters:
	//     nIndex        - DASDIAGRAMINFO RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DASDIAGRAMINFO GetIndexDasDiagram(UINT nIndex) {return (LPST_COMMON_DASDIAGRAMINFO)HMISHARE_GET_DATA(FILE_DASDIAGRAMINFO, nIndex);}
	static LPST_COMMON_DASDIAGRAMINFO GetDasDiagram(UINT nIndex) {return (LPST_COMMON_DASDIAGRAMINFO)&g_pCommonDASDIAGRAMINFO[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//   ������ ���뵵 ������ �������� ���̺� Access
	// Parameters:
	//     nIndex        - STATIONDIAGRAMINFO RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_STATIONDIAGRAMINFO GetIndexStationDiagram(UINT nIndex) {return (LPST_COMMON_STATIONDIAGRAMINFO)HMISHARE_GET_DATA(FILE_STATIONDIAGRAMINFO, nIndex);}
	static LPST_COMMON_STATIONDIAGRAMINFO GetStationDiagram(UINT nIndex) {return (LPST_COMMON_STATIONDIAGRAMINFO)&g_pCommonSTATIONDIAGRAMINFO[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ �Է� ����Ʈ RDB ���� Access
	// Parameters:
	//     nIndex        - ������ �Է� ����Ʈ RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_DISCRETE GetIndexDiscrete(UINT nIndex) {return (LPST_COMMON_DISCRETE)HMISHARE_GET_DATA(FILE_DISCRETE, nIndex);}
	static LPST_COMMON_DISCRETE GetDiscrete(UINT nIndex) {return (LPST_COMMON_DISCRETE)&g_pCommonDISCRETE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DO RDB ���� Access
	// Parameters:
	//     nIndex        - DO RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SETDISCRETE GetIndexSetDiscrete(UINT nIndex) {return (LPST_COMMON_SETDISCRETE)HMISHARE_GET_DATA(FILE_SETDISCRETE, nIndex);}
	static LPST_COMMON_SETDISCRETE GetSetDiscrete(UINT nIndex) {return (LPST_COMMON_SETDISCRETE)&g_pCommonSETDISCRETE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �Ƴ��α� �Է� ����Ʈ RDB ���� Access
	// Parameters:
	//     nIndex        - �Ƴ��α� �Է� ����Ʈ RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_MEASUREMENT GetIndexMesurement(UINT nIndex) {return (LPST_COMMON_MEASUREMENT)HMISHARE_GET_DATA(FILE_MEASUREMENT, nIndex);}
	static LPST_COMMON_MEASUREMENT GetMesurement(UINT nIndex) {return (LPST_COMMON_MEASUREMENT)&g_pCommonMEASUREMENT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     AO RDB ���� Access
	// Parameters:
	//     nIndex        - AO RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_SETMEASUREMENT GetIndexSetMesurement(UINT nIndex) {return (LPST_COMMON_SETMEASUREMENT)HMISHARE_GET_DATA(FILE_SETMEASUREMENT, nIndex);}
	static LPST_COMMON_SETMEASUREMENT GetSetMesurement(UINT nIndex) {return (LPST_COMMON_SETMEASUREMENT)&g_pCommonSETMEASUREMENT[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ī���� ����Ʈ ���� RDB ���� Access
	// Parameters:
	//     nIndex        - ACCUMULATOR RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACCUMULATOR GetIndexAccumulator(UINT nIndex) {return (LPST_COMMON_ACCUMULATOR)HMISHARE_GET_DATA(FILE_ACCUMULATOR, nIndex);}
	static LPST_COMMON_ACCUMULATOR GetAccumulator(UINT nIndex) {return (LPST_COMMON_ACCUMULATOR)&g_pCommonACCUMULATOR[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ��� ����Ʈ ���� ���� RDB ���� Access
	// Parameters:
	//     nIndex        - CALCULATION RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_CALCULATION GetIndexCal(UINT nIndex) {return (LPST_COMMON_CALCULATION)HMISHARE_GET_DATA(FILE_CALCULATION, nIndex);}
	static LPST_COMMON_CALCULATION GetCal(UINT nIndex) {return (LPST_COMMON_CALCULATION)&g_pCommonCALCULATION[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ���뵵 ���� ���� ����Ʈ RDB ���� Access
	// Parameters:
	//     nIndex        - POSITION RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_POSITION GetIndexPosition(UINT nIndex) {return (LPST_COMMON_POSITION)HMISHARE_GET_DATA(FILE_POSITION, nIndex);}
	static LPST_COMMON_POSITION GetPosition(UINT nIndex) {return (LPST_COMMON_POSITION)&g_pCommonPOSITION[nIndex];}


	//-----------------------------------------------------------------------
	// Summary:
	//     WATER ���� ���� ����Ʈ RDB ���� Access
	// Parameters:
	//     nIndex        - WATER RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_WATER GetIndexWater(UINT nIndex) {return (LPST_COMMON_WATER)HMISHARE_GET_DATA(FILE_WATER, nIndex);}
	static LPST_COMMON_WATER GetWater(UINT nIndex) {return (LPST_COMMON_WATER)&g_pCommonWATER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ACM APPGROUP RDB ���� Access
	// Parameters:
	//     nIndex        -  ACM APPGROUP RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACM_APPGROUP GetIndexAcmAppGroup(UINT nIndex) {return (LPST_COMMON_ACM_APPGROUP)HMISHARE_GET_DATA(FILE_ACM_APPGROUP, nIndex);}
	static LPST_COMMON_ACM_APPGROUP GetAcmAppGroup(UINT nIndex) {return (LPST_COMMON_ACM_APPGROUP)&g_pCommonACM_APPGROUP[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ACM MAPINDEX RDB ���� Access
	// Parameters:
	//     nIndex        -  ACM MAPINDEX RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACM_MAPINDEX GetIndexAcmMapIndex(UINT nIndex) {return (LPST_COMMON_ACM_MAPINDEX)HMISHARE_GET_DATA(FILE_ACM_MAPINDEX, nIndex);}
	static LPST_COMMON_ACM_MAPINDEX GetAcmMapIndex(UINT nIndex) {return (LPST_COMMON_ACM_MAPINDEX)&g_pCommonACM_MAPINDEX[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ACM TABLE RDB ���� Access
	// Parameters:
	//     nIndex        -  ACM TABLE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACM_TABLE GetIndexAcmTable(UINT nIndex) {return (LPST_COMMON_ACM_TABLE)HMISHARE_GET_DATA(FILE_ACM_TABLE, nIndex);}
	static LPST_COMMON_ACM_TABLE GetAcmTable(UINT nIndex) {return (LPST_COMMON_ACM_TABLE)&g_pCommonACM_TABLE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ACM TABLEGROUP RDB ���� Access
	// Parameters:
	//     nIndex        -  ACM TABLE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_ACM_TABLEGROUP GetIndexAcmTableGroup(UINT nIndex) {return (LPST_COMMON_ACM_TABLEGROUP)HMISHARE_GET_DATA(FILE_ACM_TABLEGROUP, nIndex);}
	static LPST_COMMON_ACM_TABLEGROUP GetAcmTableGroup(UINT nIndex) {return (LPST_COMMON_ACM_TABLEGROUP)&g_pCommonACM_TABLEGROUP[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     PCS RDB ���� Access
	// Parameters:
	//     nIndex        -  PCS RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_PCS GetIndexPcs(UINT nIndex) {return (LPST_COMMON_PCS)HMISHARE_GET_DATA(FILE_PCS, nIndex);}
	static LPST_COMMON_PCS GetPcs(UINT nIndex) {return (LPST_COMMON_PCS)&g_pCommonPCS[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     MAINTRANSFORMER RDB ���� Access
	// Parameters:
	//     nIndex        -  MAINTRANSFORMER RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_MAINTRANSFORMER GetIndexMainTransformer(UINT nIndex) {return (LPST_COMMON_MAINTRANSFORMER)HMISHARE_GET_DATA(FILE_MAINTRANSFORMER, nIndex);}
	static LPST_COMMON_MAINTRANSFORMER GetMainTransformer(UINT nIndex) {return (LPST_COMMON_MAINTRANSFORMER)&g_pCommonMAINTRANSFORMER[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     VIRTUAL_LINE RDB ���� Access
	// Parameters:
	//     nIndex        -  VIRTUAL_LINE RDB RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_COMMON_VIRTUAL_LINE GetIndexVirtualLine(UINT nIndex) {return (LPST_COMMON_VIRTUAL_LINE)HMISHARE_GET_DATA(FILE_VIRTUAL_LINE, nIndex);}
	static LPST_COMMON_VIRTUAL_LINE GetVirtualLine(UINT nIndex) {return (LPST_COMMON_VIRTUAL_LINE)&g_pCommonVIRTUAL_LINE[nIndex];}


	//-----------------------------------------------------------------------
	// Summary:
	//     �޸� ���� RDB ���� Access
	// Parameters:
	//     nIndex        - Memo RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_OPR_MEMO GetIndexMemo(UINT nIndex) {return (LPST_OPR_MEMO)HMISHARE_GET_DATA(FILE_MEMO, nIndex);}
	static LPST_OPR_MEMO GetMemo(UINT nIndex) {return (LPST_OPR_MEMO)&g_pOprMEMO[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �������� ���� RDB ���� Access
	// Parameters:
	//     nIndex        - MESSAGE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_OPR_MESSAGE GetIndexMessage(UINT nIndex) {return (LPST_OPR_MESSAGE)HMISHARE_GET_DATA(FILE_MESSAGE, nIndex);}
	static LPST_OPR_MESSAGE GetMessage(UINT nIndex) {return (LPST_OPR_MESSAGE)&g_pOprMESSAGE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �۾����� ���� RDB ���� Access
	// Parameters:
	//     nIndex        - CONSTRUCTION RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_OPR_CONSTRUCTION GetIndexContruction(UINT nIndex) {return (LPST_OPR_CONSTRUCTION)HMISHARE_GET_DATA(FILE_CONSTRUCTION, nIndex);}
	static LPST_OPR_CONSTRUCTION GetContruction(UINT nIndex) {return (LPST_OPR_CONSTRUCTION)&g_pOprCONSTRUCTION[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     ��ɿ� ���� ���̺� ���� RDB ���� Access
	// Parameters:
	//     nIndex        - ��ɿ� ���� ���̺� RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_OPR_OPERATORASSIGN GetIndexOpAssign(UINT nIndex) {return (LPST_OPR_OPERATORASSIGN)HMISHARE_GET_DATA(FILE_CONSTRUCTION, nIndex);}
	static LPST_OPR_OPERATORASSIGN GetOpAssign(UINT nIndex) {return (LPST_OPR_OPERATORASSIGN)&g_pOprOPERATORASSIGN[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//   ������� ������ �����ϴ� ���̺� RDB ���� Access
	// Parameters:
	//     nIndex        - WAVE_LIST RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_OPR_WAVE_LIST GetIndexOpWaveList(UINT nIndex) {return (LPST_OPR_WAVE_LIST)HMISHARE_GET_DATA(FILE_WAVE_LIST, nIndex);}
	static LPST_OPR_WAVE_LIST GetOpWaveList(UINT nIndex) {return (LPST_OPR_WAVE_LIST)&g_pOprWAVE_LIST[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//   ���� ������ �����ϴ� ���̺� RDB ���� Access
	// Parameters:
	//     nIndex        - WAVE_FILE RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_OPR_WAVE_FILE GetIndexOpWaveFile(UINT nIndex) {return (LPST_OPR_WAVE_FILE)HMISHARE_GET_DATA(FILE_WAVE_FILE, nIndex);}
	static LPST_OPR_WAVE_FILE GetOpWaveFile(UINT nIndex) {return (LPST_OPR_WAVE_FILE)&g_pOprWAVE_FILE[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//    ���� ���� ������ ���� ���̺� RDB ���� Access
	// Parameters:
	//     nIndex        - OPERATORASSIGN RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_OPR_COMPUTERSTATUS GetIndexComStatus(UINT nIndex) {return (LPST_OPR_COMPUTERSTATUS)HMISHARE_GET_DATA(FILE_COMPUTERSTATUS, nIndex);}
	static LPST_OPR_COMPUTERSTATUS GetComStatus(UINT nIndex) {return (LPST_OPR_COMPUTERSTATUS)&g_pOprCOMPUTERSTATUS[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//   ����� ���� ���̺� RDB ���� Access
	// Parameters:
	//     nIndex        - OPERATORASSIGN RDB ���� index
	//-----------------------------------------------------------------------
	static LPST_OPR_CALCULATION_RESULT GetIndexCalResult(UINT nIndex) {return (LPST_OPR_CALCULATION_RESULT)HMISHARE_GET_DATA(FILE_CALCULATION_RESULT, nIndex);}
	static LPST_OPR_CALCULATION_RESULT GetCalResult(UINT nIndex) {return (LPST_OPR_CALCULATION_RESULT)&g_pOprCALCULATION_RESULT[nIndex];}

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     ���� / ���� ����Ʈ üũ - ��� ����
	// Parameters:
	//     equip			- ���� id
	//     lPoint			- ����Ʈ id
	//     Type				- ����Ʈ Ÿ��
	//-----------------------------------------------------------------------
	static BOOL GetSwitchPoint(long equip, long lPoint, UINT Type);

	//-----------------------------------------------------------------------
	// Summary:
	//     F.I ����Ʈ üũ
	// Parameters:
	//     equip			- ���� id
	//     lPoint			- ����Ʈ id
	//     Type				- ����Ʈ Ÿ��
	//     pData			- FI data[out]
	//-----------------------------------------------------------------------
	static BOOL GetFIPoint(uPCComData m_uPcRtdata, long equip, long lPoint, UINT Type, FIDATA* pData);
	static BOOL GetAllFIPoint(uPCComData m_uPcRtdata, long equip, long lPoint, UINT Type, FIDATA* pData);
	//-----------------------------------------------------------------------
	// Summary:
	//     F.I ����Ʈ üũ
	// Parameters:
	//     equip			- ���� id
	//     lPoint			- ����Ʈ id
	//     Type				- ����Ʈ Ÿ��
	//     pData			- FI data[out]
	//-----------------------------------------------------------------------
	static BOOL GetFIPointData(int nMapID, long equip, UINT Type, FIDATA* pData);

	//-----------------------------------------------------------------------
	// Summary:
	//     F.I ����Ʈ ����Ʈ �Է¿�
	// Parameters:
	//     fi				- FI data[in]
	//     fiList			- FI List data[out]
	//-----------------------------------------------------------------------
	static BOOL GetFIListPoint(FIDATA fi, FILISTDATA *fiList);
	//-----------------------------------------------------------------------
	// Summary:
	//     D/L �� 
	// Parameters:
	//     nIndex			- d/l index
	//     dlName			- D/L ����[out]
	//-----------------------------------------------------------------------
	static BOOL GetDLNameData(int nIndex, DIAGRAMLINEDATA* dlName);
	//-----------------------------------------------------------------------
	// Summary:
	//     D/L �� 
	// Parameters:
	//     nIndex			- s/s index
	//     dlName			- ������ ��[out]
	//-----------------------------------------------------------------------
	static BOOL GetSubstationData(int nIndex, TCHAR* ssName);
	//-----------------------------------------------------------------------
	// Summary:
	//     RDB ���� ī����
	// Parameters:
	//     pszFileName        - RDB ���ϸ�
	//-----------------------------------------------------------------------
	static INT GetRDBFileListCount(TCHAR* pszFileName);
		//-----------------------------------------------------------------------
	// Summary:
	//     RDB ��Ȱ�� ī����
	// Parameters:
	//     
	//-----------------------------------------------------------------------
	static INT GetRDBLineCount();
	//-----------------------------------------------------------------------
	// Summary:
	//     ACM ���� ī����
	// Parameters:
	//     pszFileName        - ACM ���ϸ�
	//-----------------------------------------------------------------------
	static INT GetAsiFileListCount(TCHAR* pszFileName);

	//-----------------------------------------------------------------------
	// Summary:
	//     ������ ���� count
	// Parameters:
	//     nIndex			- ���� id
	//     id				- ����Ʈ id[out]
	//     psrid			- psr id[out]
	//     szname			- �����[out]
	//-----------------------------------------------------------------------
	static INT GetCompositeInEquipCount(int nIndex, long* id, long* psrid, TCHAR* szname);
	//-----------------------------------------------------------------------
	// Summary:
	//     ���ߺ��б� ���� count
	// Parameters:
	//     nIndex			- ���� id
	//     id				- ����Ʈ id[out]
	//     psrid			- psr id[out]
	//     szname			- �����[out]
	//-----------------------------------------------------------------------
	static INT GetUnderTrInEquipName(int nIndex, long* id, TCHAR* szname);
	//-----------------------------------------------------------------------
	// Summary:
	//     Distribution Tr ���� ī��Ʈ
	// Parameters:
	//     nIndex		- ���� id
	//     pdata		- ���� ����[out]	
	//-----------------------------------------------------------------------

	static INT GetSVREquipName(int nIndex, long* id, TCHAR* szname);
	//-----------------------------------------------------------------------
	// Summary:
	//     ��������(��ü)
	// Parameters:
	//     nIndex		- ���� id
	//     pdata		- ���� ����[out]	
	//-----------------------------------------------------------------------

	static BOOL GetCondectionEquipData(int nIndex, BLOCKVIEWDATA* pdata);
	//-----------------------------------------------------------------------
	// Summary:
	//     ������ ��������(��ü)
	// Parameters:
	//     nIndex		- ���� id
	//     pdata		- ���� ����[out]	
	//-----------------------------------------------------------------------

	static BOOL GetCondectionEquipSubData(int nIndex, BLOCKSUBDATA* pdata);
	//-----------------------------------------------------------------------
	// Summary:
	//     �¾籤 ������(��ü) PV + BESS
	// Parameters:
	//     nIndex		- ���� id
	//     pdata		- ���� ����[out]	
	//-----------------------------------------------------------------------

	static BOOL GetCondectionEquipPVData(int nIndex, BLOCKPVDATA* pdata);
	static BOOL GetCondectionEquipBESSData(int nIndex, BLOCKBESSDATA* pdata);
	//-----------------------------------------------------------------------
	// Summary:
	//     ������������
	// Parameters:
	//     equipid			- ���� id
	//     psrid			- psr id
	//     pInfo			- ������������[out]
	//-----------------------------------------------------------------------
	
	static BOOL GeCtrlInfo(long equipid, long psrid, UNITCTRLINFO* pInfo);
	//-----------------------------------------------------------------------
	// Summary:
	//     ������������
	// Parameters:
	//     equipid			- ���� id
	//     psrid			- psr id
	//     pInfo			- ������������[out]
	//-----------------------------------------------------------------------
	static BOOL GetUnitInfo(long equipid, long psrid, UNITINFO* pinfo);

	//-----------------------------------------------------------------------
	// Summary:
	//     ������������(DO)
	// Parameters:
	//     equipid			- ���� id
	//     dlid				- D/L id
	//     deviceId			- RTU Device  id
	//     list				- ������������[out]
	//-----------------------------------------------------------------------
	static BOOL GetCtrlInfo(long equipid, long dlid, long deviceId, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list);

	//-----------------------------------------------------------------------
	// Summary:
	//     �����������(DI)
	// Parameters:
	//     equipid			- ���� id
	//     dlid				- D/L id
	//     remoteid			- ����Ʈ ���� id
	//     list				- �����������[out]
	//-----------------------------------------------------------------------
	static BOOL GetStatInfo(long equipid, long dlid, long remote, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list);
	//-----------------------------------------------------------------------
	// Summary:
	//     SVR�� SVR��ũ�� Conducting Equipment List�� ���� ���� ã��
	// Parameters:
	//     svrid			- SVR ��ũ ���̵�
	//	   return			- SVR ��ũ�� ù��° ���� Winding ���̵�
	//-----------------------------------------------------------------------
	static int GetSVRConductEquipmentInfo(long svrid);

	//-----------------------------------------------------------------------
	// Summary:
	//     ��м��밡����
	// Parameters:
	//     equipid			- ���� id
	//     psrid			- psr id
	//     pinfo			- ��м��밡����[out]
	//-----------------------------------------------------------------------
	static BOOL GetEnergyCom(long equipid, long psrid, ENERGYCON* pinfo);

	//-----------------------------------------------------------------------
	// Summary:
	//     ��������
	// Parameters:
	//     equipid			- ���� id
	//     psrid			- psr id
	//     pinfo			- ��������[out]
	//-----------------------------------------------------------------------
	static BOOL GetLineSec(long equipid, long psrid, LINESEC* pinfo);

	//-----------------------------------------------------------------------
	// Summary:
	//     ��������(�˻�)
	// Parameters:
	//     geo			- ����
	//     sub			- ����
	//     station		- ������
	//     dl			- D/L
	//     pdata		- �˻� ����Ʈ����[out]	
	//-----------------------------------------------------------------------
	static BOOL GetEquipList(long geo, long sub, long station, long dl, CList<SEARCHDATA*, SEARCHDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     ��������(�˻�)
	// Parameters:
	//     pdata			- �˻� ����Ʈ����[out]
	//-----------------------------------------------------------------------
	static BOOL GetEquipList(CList<SEARCHDATA*, SEARCHDATA*>* pdata);
	static BOOL GetSubStationList(CList<SEARCHDATA*, SEARCHDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     ��������(DI ����Ʈ)
	// Parameters:
	//     ceq			- ���� id
	//     device		- ����Ʈ���� id
	//     pdata		- ���� ����Ʈ[out]
	//-----------------------------------------------------------------------
	static BOOL GetRemoteBIPoint(long ceq, long device, CList<BIMENUALDATA*, BIMENUALDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     ��������(AI ����Ʈ)
	// Parameters:
	//     ceq			- ���� id
	//     device		- RTU Device���� id
	//     pdata		- ���� ����Ʈ[out]
	//-----------------------------------------------------------------------
	static BOOL GetRemoteAIPoint(long ceq, long device, CList<AIMENUALDATA*, AIMENUALDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     Dts ��������(AI ����Ʈ)
	// Parameters:
	//     ceq			- ���� id
	//     remote		- ����Ʈ���� id
	//     pdata		- ���� ����Ʈ[out]
	//-----------------------------------------------------------------------
	//static BOOL GetDtsRemoteAIPoint(long ceq, long remote, CList<AIMENUALDATA*, AIMENUALDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     ��������(DO ����Ʈ)
	// Parameters:
	//     ceq			- ���� id
	//     device		- ����Ʈ���� id
	//     pdata		- ���� ����Ʈ[out]
	//-----------------------------------------------------------------------
	static BOOL GetRemoteBOPoint(long ceq, long device, CList<BIMENUALDATA*, BIMENUALDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     ��������(AO ����Ʈ)
	// Parameters:
	//     ceq			- ���� id
	//     device		- ����Ʈ���� id
	//     pdata		- ���� ����Ʈ[out]
	//-----------------------------------------------------------------------
	static BOOL GetRemoteAOPoint(long ceq, long device, CList<AIMENUALDATA*, AIMENUALDATA*>* pdata);

	//-----------------------------------------------------------------------
	// Summary:
	//     ��������(����/���� ����Ʈ)
	// Parameters:
	//     station		- ������
	//     dl			- D/L
	//     device		- ����Ʈ���� id
	//     pid			- ���� ����/���� ����Ʈ[out]
	//-----------------------------------------------------------------------
	static BOOL GetRemoteOpenPoint(long station, long dl, long device, long ceq, long* pid);

	//-----------------------------------------------------------------------
	// Summary:
	//     ����Ʈ���� id
	// Parameters:
	//     cequip		- ����id
	//     device		- ����Ʈ���� id[out]
	//-----------------------------------------------------------------------
	static BOOL CRDBMgr::GetEquipIdToRemoteId(long cequip, long* device);

	//-----------------------------------------------------------------------
	// Summary:
	//     ����Ʈ���� �л����� ����
	// Parameters:
	//     lline			- ȸ��(�����ϰ�� 0)
	//     punit			- ����Ʈ ��������
	//     pdrunit			- �л����� ����[out]
	//-----------------------------------------------------------------------
	static BOOL GetDRInfo(long lline, long ceqid, DRUNIT* pdrunit);

	//-----------------------------------------------------------------------
	// Summary:
	//     DTS ����
	// Parameters:
	//     ceqid			- conduct Equipment id
	//     pdata			- DTS ����[out]
	//-----------------------------------------------------------------------
	static BOOL GetDtsInfo(long ceqid, CList<DTSINFO*, DTSINFO*>* pdata);
	static int GetDtsCount(long ceqid);
	static int GetDtsSectionID(long ceqid);
	//-----------------------------------------------------------------------
	// Summary:
	//     ����Ʈ���� RDB ���� Access
	// Parameters:
	//     nIndex        - ����Ʈ���� RDB ���� index
	//-----------------------------------------------------------------------
	//static LPST_RTDB_LINEST GetLineStatus(UINT nIndex) {return (LPST_RTDB_LINEST)&g_pRTDBLinest[nIndex];}
	//-----------------------------------------------------------------------
	// Summary:
	//     Transformer BI����
	// Parameters:
	//     ceqid			- conduct Equipment id
	//     pdata			- Transformer ;����[out]
	//-----------------------------------------------------------------------
	static BOOL GetAmiBIPoint(long ceqid, TRANSFORMERLIST* pdata);
	static BOOL GetAmiBIPoint(long ceqid, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list);

	//-----------------------------------------------------------------------
	// Summary:
	//     Transformer AI ����
	// Parameters:
	//     ceqid			- conduct Equipment id
	//     pdata			- Transformer ;����[out]
	//-----------------------------------------------------------------------
	static BOOL GetAmiAIPoint(long ceqid, CList<UNITANALOGININFO*, UNITANALOGININFO*>* list);

	//-----------------------------------------------------------------------
	// Summary:
	//    color ����Ʈ RDB ���� Access
	// Parameters:
	//     nIndex        - color code ����Ʈ RDB ���� index
	//-----------------------------------------------------------------------
	//static LPST_RDB_COLOR GetColor(UINT nIndex) {return (LPST_RDB_COLOR)&g_pRDBColor[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     DMC RDB ���� Access
	// Parameters:
	//     nIndex        - DMC RDB ���� index
	//-----------------------------------------------------------------------
	//static LPST_RDB_DMC GetDMC(UINT nIndex) {return (LPST_RDB_DMC)&g_pRDBDmc[nIndex];}

	//-----------------------------------------------------------------------
	// Summary:
	//     �Ҽ� D/L �� ����Ʈ ����
	// Parameters:
	//     eqcfk			- equipment container ID
	//     dlid				- D/L id
	//     pInfo			- ����Ʈ ��������[out]
	//-----------------------------------------------------------------------
	static BOOL GetEquipInfoFromTransBankAI(long eqcfk, long dlid, CList<UNITANALOGININFO*, UNITANALOGININFO*>* list);

	//-----------------------------------------------------------------------
	// Summary:
	//     ������������(DO)
	// Parameters:
	//     eqcfk			- ���� id
	//     dlid				- D/L id
	//     list				- ������������[out]
	//-----------------------------------------------------------------------
	static BOOL GetEquipInfoFromTransBankBO(long eqcfk, long dlid, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list);
	//-----------------------------------------------------------------------
	// Summary:
	//     ���� ���� ���� ���
	// Parameters:
	//     nDL				- �Ҽ� DL
	//     list				- �Ҽ� DL�� ���輳�� ����[out]s
	//-----------------------------------------------------------------------
	static BOOL GetTieSWInfo(int nDL, CList<TIESWITCH*, TIESWITCH*>* list);
	//-----------------------------------------------------------------------
	// Summary:
	//     ��� ���� ���� ���� ���
	// Parameters:
	//     list				- �Ҽ� DL�� ���輳�� ����[out]
	//-----------------------------------------------------------------------
	static BOOL GetAllTieSWInfo(CList<TIESWITCH*, TIESWITCH*>* list);
	//-----------------------------------------------------------------------
	// Summary:
	//     ������������(DO)
	// Parameters:
	//     pointid			- pointid
	//     pointtype		- pointtype
	//-----------------------------------------------------------------------
	static BOOL IsAccessArea(long pointid, long pointtype);
	//-----------------------------------------------------------------------
	// Summary:
	//     �����ͺ��̽����� RDB ������ ������ �����޸� ����
	// Parameters:
	//-----------------------------------------------------------------------

	static BOOL CreateSharedDB();
	static BOOL AllUpdateSharedDB();
	static BOOL UpdateSharedDB(TCHAR *tTableName);

	//-----------------------------------------------------------------------
	// Summary:
	//     �����ͺ��̽����� �̵���� ��ü ����Ʈ ��û�� ������ ���� 
	// Parameters: iCeqid : CEQ id, list : �ش� ������ ����Ʈ ����Ʈ
	//-----------------------------------------------------------------------
	static BOOL GetMwDataPoint(int iCeqid, CList<MWPOINTINFO*, MWPOINTINFO*>* list);

	//-----------------------------------------------------------------------
	// Summary:
	//		CEQ�� RTU ���̵�� ��ȯ
	// Parameters: iCeqid : CEQ id, 
	//-----------------------------------------------------------------------
	static BOOL GetCeqToRtu(int iCeqid, int &iRtuId);

	//-----------------------------------------------------------------------
	// Summary:
	//		����Ʈ ��ȣ�� RTUMap Id �� Index ����
	// Parameters: iCeqid : CEQ id, 
	//-----------------------------------------------------------------------
	static BOOL    GetPointToIndex(int iPtNo, int PtType, int &iRtumap, int &iIndex);
	static CString TlqToString(unsigned short tlq_id);
	static CString SelectToQuery( CString strDBName, CString strSPName, CString strTBName );
	static void	   GetBIPointUpcName( MWPOINTINFO* pItem );	
	static CString GetDataPointName( int nCEQID );																// �����ͱ׷쿡 ���� UPC�̸� üũ
	static CString GetCalcPointName( int nPID   );																// �����ͱ׷쿡 ���� UPC�̸� üũ : �������Ʈ
	static CString GetStringComma  ( float fValue, int nDigit );												// õ���� ���ڿ� �޸��� �־��ش�
	static CString GetACMDataPointName( int nCEQID );															// �����ͱ׷쿡 ���� ACM UPC�̸� üũ
	static CString GetStateSetName ( int nRTUMAPID, int nPOSITION, int nVALUE, int nTYPE = POINT_TYPE_BI );		// STATEGRP�� ���� STATESET �̸��� �����´�
	static CString GetTlqName	   ( int nTlqNum );
	static BOOL	   CheckUseControl  ( int nCEQID, BOOL bMsg = FALSE );											// �����Ҽ��ִ� �����ͱ׷����� üũ
	static BOOL	   SetSqlConnect    ();																			// SQL ����
	static void	   SetSqlDisconnect ();																			// SQL ���� ����
	static void	   EndControlProcess();																			// ����â ���� �޼���
	static void	   SendAsyncQue     ( int nPGID, CString strClientName, CString strLogHMI );
	static void	   InsertControlLog ( int nCEQID, int nRUID, int nControlType, int nPointType, int nMAPID, float fOldVal, float fSetVal, int nComputerID, CString strOperName, CString strReason );
	static void	   InsertControlLog2( int nCEQID, int nRUID, int nControlType, int nPointType, int nMAPID, float fOldVal, float fSetVal, int nComputerID, CString strOperName, CString strReason );
	static void	   InsertAlarmAck   ( int nCEQID, CString strCreateTime, CString strContents, CString strAckUser, int nIMPORTANT, CString strHMIId );
	
	static int	   GetPointMapId    ( int nCEQID, int nControlType, int nPosition );
	static int	   CheckTlqPsLock   ( int nCEQID, int nControlType, int nMapId );
	static int	   CheckControlPriority();
	static CPoint  GetMonitorCenterPoint( HWND hWnd );
};