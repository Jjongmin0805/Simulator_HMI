#pragma once
#ifndef __DATASWAP_H__
#define __DATASWAP_H__



void OnInsertIDENTIFIEDOBJECT(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_IDENTIFIEDOBJECT* ptrBase				= (ST_COMMON_IDENTIFIEDOBJECT*)(*p);

	ST_COMMON_IDENTIFIEDOBJECT pst = {0,};

	int nSeq = 0;
	_tcscpy_s(pst.MRID,  strArray->GetAt(nSeq++));
	//_tcscpy_s(pst.name, strArray->GetAt(nSeq++));
	_tcscpy_s(pst.aliasName, strArray->GetAt(nSeq++));
	_tcscpy_s(pst.localName, strArray->GetAt(nSeq++));
	_tcscpy_s(pst.pathName, strArray->GetAt(nSeq++));
	_tcscpy_s(pst.description, strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_IDENTIFIEDOBJECT));	
}
void OnInsertGEOGRAPHICALREGION(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_GEOGRAPHICALREGION* ptrBase				= (ST_COMMON_GEOGRAPHICALREGION*)(*p);

	ST_COMMON_GEOGRAPHICALREGION pst = {0,};

	int nSeq = 0;
	pst.GGRID =_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.mRIDFK,	strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.GGRCode =_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_GEOGRAPHICALREGION));	
}
void OnInsertSUBGEOGRAPHICALREGION(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_SUBGEOGRAPHICALREGION* ptrBase				= (ST_COMMON_SUBGEOGRAPHICALREGION*)(*p);

	ST_COMMON_SUBGEOGRAPHICALREGION pst = {0,};

	int nSeq = 0;
	pst.SGRID		=_ttoi(strArray->GetAt(nSeq++));			
	pst.GGRFK		=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.mRIDFK,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.SGRCode	=_ttoi(strArray->GetAt(nSeq++));
	pst.DPGC_ACMFK =_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_SUBGEOGRAPHICALREGION));	
}
void OnInsertDATAPOINTGROUPCODE(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_DATAPOINTGROUPCODE* ptrBase				= (ST_COMMON_DATAPOINTGROUPCODE*)(*p);

	ST_COMMON_DATAPOINTGROUPCODE pst = {0,};
	
	int nSeq = 0;
	pst.DpGrpId		 =_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.DpGrpName,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.DpGrpCode,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.DpPrefixName,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_DATAPOINTGROUPCODE));	
}
void OnInsertCOMPUTERCODE(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_COMPUTERCODE* ptrBase				= (ST_COMMON_COMPUTERCODE*)(*p);

	ST_COMMON_COMPUTERCODE pst = {0,};

	int nSeq = 0;
	pst.ComputerId		=_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.ComputerName,	strArray->GetAt(nSeq++));
	pst.ComputerType	=_ttoi(strArray->GetAt(nSeq++));
	pst.PORT			=_ttoi(strArray->GetAt(nSeq++));
	pst.PRIORITY		=_ttoi(strArray->GetAt(nSeq++));
	pst.MSINGLE		=_ttoi(strArray->GetAt(nSeq++));
	pst.OFFLINE		=_ttoi(strArray->GetAt(nSeq++));
	pst.DpGrpFK		=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.IP_Addr,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_COMPUTERCODE));	
}
void OnInsertPROGRAMCODE(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_PROGRAMCODE* ptrBase				= (ST_COMMON_PROGRAMCODE*)(*p);

	ST_COMMON_PROGRAMCODE pst = {0,};

	int nSeq = 0;
	pst.ProgId			=_ttoi(strArray->GetAt(nSeq++));			
	pst.ComputerId		=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.ProgName,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.ServiceName,	strArray->GetAt(nSeq++));
	pst.ProgLevel			=_ttoi(strArray->GetAt(nSeq++));
	pst.RunNode			=_ttoi(strArray->GetAt(nSeq++));
	pst.AutoRestart		=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_PROGRAMCODE));	
}
void OnInsertOPERATORCODE(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_OPERATORCODE* ptrBase				= (ST_COMMON_OPERATORCODE*)(*p);

	ST_COMMON_OPERATORCODE pst = {0,};

	int nSeq = 0;
	pst.OperId			=_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.OperNum,		strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.OperName,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.OperPasswd,	strArray->GetAt(nSeq++));
	pst.ConAuth			=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_OPERATORCODE));	
}
void OnInsertSWITCHTYPECODE(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_SWITCHTYPECODE* ptrBase				= (ST_COMMON_SWITCHTYPECODE*)(*p);

	ST_COMMON_SWITCHTYPECODE pst = {0,};

	int nSeq = 0;
	pst.TypeID			=_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_SWITCHTYPECODE));	
}
void OnInsertCONSTRUCTIONCODE(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_CONSTRUCTIONCODE* ptrBase				= (ST_COMMON_CONSTRUCTIONCODE*)(*p);

	ST_COMMON_CONSTRUCTIONCODE pst = {0,};

	int nSeq = 0;
	pst.ConstId			=_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.Consttype,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_CONSTRUCTIONCODE));	
}
void OnInsertWAVECOMTYPE(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_WAVECOMTYPE* ptrBase				= (ST_COMMON_WAVECOMTYPE*)(*p);

	ST_COMMON_WAVECOMTYPE pst = {0,};

	int nSeq = 0;
	pst.wavecomTypetId			=_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.ComtypeName,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_WAVECOMTYPE));	
}
void OnInsertSTATEGROUP(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_STATEGROUP* ptrBase				= (ST_COMMON_STATEGROUP*)(*p);

	ST_COMMON_STATEGROUP pst = {0,};

	int nSeq = 0;
	pst.StateGrpId			=_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.Count			=_ttoi(strArray->GetAt(nSeq++));	

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_STATEGROUP));	
}
void OnInsertDATABYTE(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_DATABYTE* ptrBase				= (ST_COMMON_DATABYTE*)(*p);

	ST_COMMON_DATABYTE pst = {0,};

	int nSeq = 0;
	pst.DataByteId			=_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.Sign				=_ttoi(strArray->GetAt(nSeq++));	
	pst.Size				=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_DATABYTE));	
}
void OnInsertSTATESET(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_STATESET* ptrBase				= (ST_COMMON_STATESET*)(*p);

	ST_COMMON_STATESET pst = {0,};
	
	int nSeq = 0;
	pst.StateSetId			=_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.Value				=_ttoi(strArray->GetAt(nSeq++));	
	pst.StateGrpId			=_ttoi(strArray->GetAt(nSeq++));	

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_STATESET));	
}
void OnInsertUNIT(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_UNIT* ptrBase				= (ST_COMMON_UNIT*)(*p);

	ST_COMMON_UNIT pst = {0,};

	int nSeq = 0;
	pst.UnitId			=_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.UnitName,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_UNIT));	
}
void OnInsertSCALEFACTOR(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_SCALEFACTOR* ptrBase				= (ST_COMMON_SCALEFACTOR*)(*p);

	ST_COMMON_SCALEFACTOR pst = {0,};

	int nSeq = 0;
	pst.sfid			=_ttoi(strArray->GetAt(nSeq++));			
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.Scale			=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.Offset			=(FLOAT)_ttof(strArray->GetAt(nSeq++));	

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_SCALEFACTOR));	
}
void OnInsertLIMITCODE(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_LIMITCODE* ptrBase				= (ST_COMMON_LIMITCODE*)(*p);

	ST_COMMON_LIMITCODE pst = {0,};

	int nSeq = 0;
	pst.LimitId			= _ttoi(strArray->GetAt(nSeq++));		
	pst.LimitSetId		= _ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.Val				= (FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.Limittype		= _ttoi(strArray->GetAt(nSeq++));	

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_LIMITCODE));	
}
void OnInsertLIMITSET(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_LIMITSET* ptrBase				= (ST_COMMON_LIMITSET*)(*p);

	ST_COMMON_LIMITSET pst = {0,};

	int nSeq = 0;
	pst.LimitSetId			=_ttoi(strArray->GetAt(nSeq++));		
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_LIMITSET));	
}
void OnInsertEQUIPCOMPANY(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_EQUIPCOMPANY* ptrBase				= (ST_COMMON_EQUIPCOMPANY*)(*p);

	ST_COMMON_EQUIPCOMPANY pst = {0,};

	int nSeq = 0;
	pst.CompanyId			=_ttoi(strArray->GetAt(nSeq++));		
	_tcscpy_s(pst.CompanyName,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_EQUIPCOMPANY));	
}
void OnInsertSUBSTATION(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_SUBSTATION* ptrBase				= (ST_COMMON_SUBSTATION*)(*p);

	ST_COMMON_SUBSTATION pst = {0,};

	int nSeq = 0;
	pst.SSID			=_ttoi(strArray->GetAt(nSeq++));	
	pst.SGRFK			=_ttoi(strArray->GetAt(nSeq++));	
	pst.EQCFK			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.PSRFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.SSCode			=_ttoi(strArray->GetAt(nSeq++));
	pst.DPGC_ACMFK		=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_SUBSTATION));	
}
void OnInsertDISTRIBUTIONLINE(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_DISTRIBUTIONLINE* ptrBase				= (ST_COMMON_DISTRIBUTIONLINE*)(*p);

	ST_COMMON_DISTRIBUTIONLINE pst = {0,};

	int nSeq = 0;
	pst.DLID			=_ttoi(strArray->GetAt(nSeq++));	
	pst.SSFK			=_ttoi(strArray->GetAt(nSeq++));	
	pst.MTRFK			=_ttoi(strArray->GetAt(nSeq++));	
	pst.EQCFK			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.dl_no			=_ttoi(strArray->GetAt(nSeq++));
	pst.reliability		=_ttoi(strArray->GetAt(nSeq++));
	pst.priority		=_ttoi(strArray->GetAt(nSeq++));
	pst.rated_S			=(FLOAT)(_ttof(strArray->GetAt(nSeq++)));
	pst.RATED_S_USFK	=_ttoi(strArray->GetAt(nSeq++));
	pst.DPGC_ACMFK		=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_DISTRIBUTIONLINE));	
}
void OnInsertBASEVOLTAGE(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_BASEVOLTAGE* ptrBase				= (ST_COMMON_BASEVOLTAGE*)(*p);

	ST_COMMON_BASEVOLTAGE pst = {0,};

	int nSeq = 0;
	pst.BVID			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.NominalVoltage					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.NominalVoltage_usfk			=_ttoi(strArray->GetAt(nSeq++));
	pst.MaxVoltage						=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.MaxVoltage_usfk				=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_BASEVOLTAGE));	
}
void OnInsertBASEPOWER(long* p, int idx, CStringArray *strArray)				
{	
	ST_COMMON_BASEPOWER* ptrBase				= (ST_COMMON_BASEPOWER*)(*p);

	ST_COMMON_BASEPOWER pst = {0,};

	int nSeq = 0;
	pst.BPID									=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.basePower								=_ttoi(strArray->GetAt(nSeq++));
	pst.basePower_usfk							=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_BASEPOWER));	

}
void OnInsertVOLTAGELEVEL(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_VOLTAGELEVEL* ptrBase				= (ST_COMMON_VOLTAGELEVEL*)(*p);

	ST_COMMON_VOLTAGELEVEL pst = {0,};

	int nSeq = 0;
	pst.VLID			=_ttoi(strArray->GetAt(nSeq++));	
	pst.SSFK			=_ttoi(strArray->GetAt(nSeq++));	
	pst.BVFK			=_ttoi(strArray->GetAt(nSeq++));	
	pst.EQCFK			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.highVoltageLim					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.highVoltageLim_usfk			=_ttoi(strArray->GetAt(nSeq++));
	pst.lowVoltageLim					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.lowVoltageLim_usfk				=_ttoi(strArray->GetAt(nSeq++));
	pst.PSRFK							=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_VOLTAGELEVEL));
}
void OnInsertPHASE(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_PHASE* ptrBase				= (ST_COMMON_PHASE*)(*p);

	ST_COMMON_PHASE pst = {0,};

	int nSeq = 0;
	pst.PhaseID			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.PhaseName,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Phase,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_PHASE));
}
void OnInsertPROTOCOLTYPE(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_PROTOCOLTYPE* ptrBase				= (ST_COMMON_PROTOCOLTYPE*)(*p);

	ST_COMMON_PROTOCOLTYPE pst = {0,};

	int nSeq = 0;
	pst.ProtocolTypeId			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.ProtocolName,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.ProtocolKind,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_PROTOCOLTYPE));
}
void OnInsertEQUIPMENTTYPE(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_EQUIPMENTTYPE* ptrBase				= (ST_COMMON_EQUIPMENTTYPE*)(*p);

	ST_COMMON_EQUIPMENTTYPE pst = {0,};

	int nSeq = 0;
	pst.EquipTypeId			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.EquipTypeCode,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.EquipTypeDesc,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_EQUIPMENTTYPE));
}
void OnInsertRTUMAP(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_RTUMAP* ptrBase				= (ST_COMMON_RTUMAP*)(*p);

	ST_COMMON_RTUMAP pst = {0,};

	int nSeq = 0;
	pst.RTUMapId			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.RTUMapName,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.DMSName,		strArray->GetAt(nSeq++));
	pst.RTUTypeId			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.UPC_TypeName,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.RTUKind,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_RTUMAP));
}
void OnInsertCOMMTYPE(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_COMMTYPE* ptrBase				= (ST_COMMON_COMMTYPE*)(*p);

	ST_COMMON_COMMTYPE pst = {0,};

	int nSeq = 0;
	pst.CommTypeId			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.ConmmTypeName,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.ConmmKind,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_COMMTYPE));
}
void OnInsertRTUTYPE(long* p, int idx, CStringArray *strArray)						
{
	ST_COMMON_RTUTYPE* ptrBase				= (ST_COMMON_RTUTYPE*)(*p);

	ST_COMMON_RTUTYPE pst = {0,};

	int nSeq = 0;
	pst.RTUTypeId			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.RTUTypeName,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_RTUTYPE));
}
void OnInsertCATEGORYCODE(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_CATEGORYCODE* ptrBase				= (ST_COMMON_CATEGORYCODE*)(*p);

	ST_COMMON_CATEGORYCODE pst = {0,};

	int nSeq = 0;
	pst.CCID				=_ttoi(strArray->GetAt(nSeq++));	
	pst.CCDType			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Name,		strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_CATEGORYCODE));
}
void OnInsertMEASURETYPEINFO(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_MEASURETYPEINFO* ptrBase				= (ST_COMMON_MEASURETYPEINFO*)(*p);

	ST_COMMON_MEASURETYPEINFO pst = {0,};

	int nSeq = 0;
	pst.MeasureTypeID			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Name,		strArray->GetAt(nSeq++));
	pst.PointType				=_ttoi(strArray->GetAt(nSeq++));
	pst.CCDFK					=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_MEASURETYPEINFO));
}
void OnInsertDNPBIMAPINDEX(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_DNPBIMAPINDEX* ptrBase				= (ST_COMMON_DNPBIMAPINDEX*)(*p);

	ST_COMMON_DNPBIMAPINDEX pst = {0,};

	int nSeq = 0;
	pst.MapId					=_ttoi(strArray->GetAt(nSeq++));	
	pst.RTUMapId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.StateGrpId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.MeasureTypeID			=_ttoi(strArray->GetAt(nSeq++));	
	pst.Position				=_ttoi(strArray->GetAt(nSeq++));	
	pst.BO_Position			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.IndexName,	strArray->GetAt(nSeq++));
	pst.CircuitNo				=_ttoi(strArray->GetAt(nSeq++));	
	pst.NormalValue			=_ttoi(strArray->GetAt(nSeq++));	
	pst.AbnormalValue			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Obj_Var,		strArray->GetAt(nSeq++));
	pst.Class					=_ttoi(strArray->GetAt(nSeq++));	
	pst.EMS					=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.upc_name,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_tlq,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_uptime,	strArray->GetAt(nSeq++));
	pst.Alarm					=_ttoi(strArray->GetAt(nSeq++));
	pst.Important				=_ttoi(strArray->GetAt(nSeq++));
	pst.Terminal_DI			=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_DNPBIMAPINDEX));
}
void OnInsertDNPBOMAPINDEX(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_DNPBOMAPINDEX* ptrBase				= (ST_COMMON_DNPBOMAPINDEX*)(*p);

	ST_COMMON_DNPBOMAPINDEX pst = {0,};

	int nSeq = 0;
	pst.MapId					=_ttoi(strArray->GetAt(nSeq++));	
	pst.RTUMapId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.StateGrpId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.MeasureTypeID			=_ttoi(strArray->GetAt(nSeq++));	
	pst.Position				=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.IndexName,	strArray->GetAt(nSeq++));
	pst.CircuitNo				=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Obj_Var,		strArray->GetAt(nSeq++));
	pst.Class					=_ttoi(strArray->GetAt(nSeq++));	
	pst.EMS					=_ttoi(strArray->GetAt(nSeq++));	
	pst.CCId					=_ttoi(strArray->GetAt(nSeq++));
	pst.RelayOnTime			=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_name,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_tlq,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_uptime,	strArray->GetAt(nSeq++));
	pst.Alarm					=_ttoi(strArray->GetAt(nSeq++));
	pst.Important				=_ttoi(strArray->GetAt(nSeq++));
	pst.Terminal_DI			=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_DNPBOMAPINDEX));
}
void OnInsertDNPAIMAPINDEX(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_DNPAIMAPINDEX* ptrBase				= (ST_COMMON_DNPAIMAPINDEX*)(*p);

	ST_COMMON_DNPAIMAPINDEX pst = {0,};

	int nSeq = 0;
	pst.MapId					=_ttoi(strArray->GetAt(nSeq++));	
	pst.RTUMapId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.Scale					=_ttoi(strArray->GetAt(nSeq++));	
	pst.LimitSetId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.MeasureTypeID			=_ttoi(strArray->GetAt(nSeq++));	
	pst.Position				=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.IndexName,	strArray->GetAt(nSeq++));
	pst.CircuitNo				=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Obj_Var,		strArray->GetAt(nSeq++));
	pst.Class					=_ttoi(strArray->GetAt(nSeq++));	
	pst.EMS					=_ttoi(strArray->GetAt(nSeq++));	
	pst.GrpFlag				=_ttoi(strArray->GetAt(nSeq++));
	pst.LinkPos				=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_name,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_tlq,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_uptime,	strArray->GetAt(nSeq++));
	pst.Alarm					=_ttoi(strArray->GetAt(nSeq++));
	pst.Important				=_ttoi(strArray->GetAt(nSeq++));
	pst.Terminal_DI			=_ttoi(strArray->GetAt(nSeq++));
	pst.UnitSymbol				=_ttoi(strArray->GetAt(nSeq++));
	pst.MinMaxLimitSet			=_ttoi(strArray->GetAt(nSeq++));
	pst.DataByteId				=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_DNPAIMAPINDEX));
}
void OnInsertDNPAOMAPINDEX(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_DNPAOMAPINDEX* ptrBase				= (ST_COMMON_DNPAOMAPINDEX*)(*p);

	ST_COMMON_DNPAOMAPINDEX pst = {0,};

	int nSeq = 0;
	pst.MapId					=_ttoi(strArray->GetAt(nSeq++));	
	pst.RTUMapId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.Scale					=_ttoi(strArray->GetAt(nSeq++));	
	pst.StateGrpId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.MeasureTypeID			=_ttoi(strArray->GetAt(nSeq++));	
	pst.Position				=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.IndexName,	strArray->GetAt(nSeq++));
	pst.NormalValue			=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.StepValue				=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.CircuitNo				=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Obj_Var,		strArray->GetAt(nSeq++));
	pst.Class					=_ttoi(strArray->GetAt(nSeq++));	
	pst.EMS					=_ttoi(strArray->GetAt(nSeq++));	
	pst.GrpFlag				=_ttoi(strArray->GetAt(nSeq++));
	pst.LinkPos				=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_name,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_tlq,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_uptime,	strArray->GetAt(nSeq++));
	pst.Alarm					=_ttoi(strArray->GetAt(nSeq++));
	pst.Important				=_ttoi(strArray->GetAt(nSeq++));
	pst.Terminal_DI			=_ttoi(strArray->GetAt(nSeq++));
	pst.UnitSymbol				=_ttoi(strArray->GetAt(nSeq++));
	pst.MinMaxLimitSet			=_ttoi(strArray->GetAt(nSeq++));
	pst.DateByteId				=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_DNPAOMAPINDEX));
}
void OnInsertDNPCOUNTERMAPINDEX(long* p, int idx, CStringArray *strArray)		
{
	ST_COMMON_DNPCOUNTERMAPINDEX* ptrBase				= (ST_COMMON_DNPCOUNTERMAPINDEX*)(*p);

	ST_COMMON_DNPCOUNTERMAPINDEX pst = {0,};

	int nSeq = 0;
	pst.MapId					=_ttoi(strArray->GetAt(nSeq++));	
	pst.RTUMapId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.LimitSetId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.MeasureTypeID			=_ttoi(strArray->GetAt(nSeq++));	
	pst.Position				=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.IndexName,	strArray->GetAt(nSeq++));
	pst.CircuitNo				=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Obj_Var,		strArray->GetAt(nSeq++));
	pst.Class					=_ttoi(strArray->GetAt(nSeq++));	
	pst.EMS					=_ttoi(strArray->GetAt(nSeq++));	
	pst.GrpFlag				=_ttoi(strArray->GetAt(nSeq++));
	pst.LinkPos				=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_name,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_tlq,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_uptime,	strArray->GetAt(nSeq++));
	pst.Alarm					=_ttoi(strArray->GetAt(nSeq++));
	pst.Important				=_ttoi(strArray->GetAt(nSeq++));
	pst.Terminal_DI			=_ttoi(strArray->GetAt(nSeq++));
//	pst.UnitSymbol				=_ttoi(strArray->GetAt(18));
	pst.MinMaxLimitSet			=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_DNPCOUNTERMAPINDEX));
}
void OnInsertRTUDEVICE(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_RTUDEVICE* ptrBase				= (ST_COMMON_RTUDEVICE*)(*p);

	ST_COMMON_RTUDEVICE pst = {0,};
	
	int nSeq = 0;
	pst.RUID					=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Name,		strArray->GetAt(nSeq++));
	pst.FEP_PROG_ID			=_ttoi(strArray->GetAt(nSeq++));	
	pst.PRI_FEP				=_ttoi(strArray->GetAt(nSeq++));	
	pst.BCK_FEP				=_ttoi(strArray->GetAt(nSeq++));	
	pst.RTUMapId				=_ttoi(strArray->GetAt(nSeq++));	
	pst.EquipTypeId			=_ttoi(strArray->GetAt(nSeq++));	
	pst.Protocol				=_ttoi(strArray->GetAt(nSeq++));	
	pst.MasterDnp				=_ttoi(strArray->GetAt(nSeq++));	
	pst.Dnp_Addr				=_ttoi(strArray->GetAt(nSeq++));
	pst.BaudRate				=_ttoi(strArray->GetAt(nSeq++));
	pst.Control				=_ttoi(strArray->GetAt(nSeq++));
	pst.StopBit				=_ttoi(strArray->GetAt(nSeq++));
	pst.Parity					=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.IP_Addr,	strArray->GetAt(nSeq++));
	pst.Port					=_ttoi(strArray->GetAt(nSeq++));
	pst.CommTypeId				=_ttoi(strArray->GetAt(nSeq++));
	pst.Time_Sym_Hour			=_ttoi(strArray->GetAt(nSeq++));
	pst.Use_SBO				=_ttoi(strArray->GetAt(nSeq++));
	pst.Use_Confirm			=_ttoi(strArray->GetAt(nSeq++));
	pst.wave_comtypeId			=_ttoi(strArray->GetAt(nSeq++));
	pst.Datalink				=_ttoi(strArray->GetAt(nSeq++));
	pst.FunGrpId				=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.RTUCompany,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.RTUSerialNo,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.RTUDate,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.DevCompany,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.DevSerialNo,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.DevDate,		strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_RTUDEVICE));
}
void OnInsertCONDUCTINGEQUIPMENT(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_CONDUCTINGEQUIPMENT* ptrBase				= (ST_COMMON_CONDUCTINGEQUIPMENT*)(*p);

	ST_COMMON_CONDUCTINGEQUIPMENT pst = {0,};

	int nSeq = 0;
	pst.CEQID					=_ttoi(strArray->GetAt(nSeq++));	
	pst.SSFK 					=_ttoi(strArray->GetAt(nSeq++));	
	pst.DLFK 					=_ttoi(strArray->GetAt(nSeq++));	
	pst.PSRFK					=_ttoi(strArray->GetAt(nSeq++));	
	pst.BVFK 					=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.Phase    				=_ttoi(strArray->GetAt(nSeq++));	
	pst.EQCFK    				=_ttoi(strArray->GetAt(nSeq++));	
	pst.DpGrpFK  				=_ttoi(strArray->GetAt(nSeq++));
	pst.DPGC_ACMFK 				=_ttoi(strArray->GetAt(nSeq++));
	pst.CircuitNo				=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.MeshNo,		strArray->GetAt(nSeq++));
	pst.RUID					=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_CONDUCTINGEQUIPMENT));
}
void OnInsertSWITCH(long* p, int idx, CStringArray *strArray)						
{
	ST_COMMON_SWITCH* ptrBase				= (ST_COMMON_SWITCH*)(*p);

	ST_COMMON_SWITCH pst = {0,};

	int nSeq = 0;
	pst.SWID					=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.name,			strArray->GetAt(nSeq++));
	pst.CEQFK              		=_ttoi(strArray->GetAt(nSeq++));	
	pst.CPSFK              		=_ttoi(strArray->GetAt(nSeq++));	
	//pst.BVFK               		=_ttoi(strArray->GetAt(nSeq++));	
	pst.PEQFK              		=_ttoi(strArray->GetAt(nSeq++));	
	pst.normalOpen         		=_ttoi(strArray->GetAt(nSeq++));	
	pst.SwitchType         		=_ttoi(strArray->GetAt(nSeq++));
	pst.SwitchType_ACM     		=_ttoi(strArray->GetAt(nSeq++));
	pst.sourceACLSFK       		=_ttoi(strArray->GetAt(nSeq++));	
	pst.loadACLSFK         		=_ttoi(strArray->GetAt(nSeq++));
	//pst.RDID					=_ttoi(strArray->GetAt(nSeq++));
	pst.RatedCurrent       		=_ttoi(strArray->GetAt(nSeq++));	
	pst.RatedCurrent_usfk  		=_ttoi(strArray->GetAt(nSeq++));	
	pst.NormallyService    		=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Switch_no,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_SWITCH));
}
void OnInsertACLINESEGMENT(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_ACLINESEGMENT* ptrBase				= (ST_COMMON_ACLINESEGMENT*)(*p);

	ST_COMMON_ACLINESEGMENT pst = {0,};

	int nSeq = 0;
	pst.ACID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.CEQFK              		=_ttoi(strArray->GetAt(nSeq++));
	pst.PLSIFK               		=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.length              		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.length_usfk         		=_ttoi(strArray->GetAt(nSeq++));	
	pst.phases         			=_ttoi(strArray->GetAt(nSeq++));	

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_ACLINESEGMENT));
}
void OnInsertPERLENGTHSEQUENCEIMPEDANCE(long* p, int idx, CStringArray *strArray)	
{
	ST_COMMON_PERLENGTHSEQUENCEIMPEDANCE* ptrBase				= (ST_COMMON_PERLENGTHSEQUENCEIMPEDANCE*)(*p);

	ST_COMMON_PERLENGTHSEQUENCEIMPEDANCE pst = {0,};

	int nSeq = 0;
	pst.PLSIID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.PSRTypeFK					=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name3P,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.NameN,			strArray->GetAt(nSeq++));
	pst.b0ch              			=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.b0ch_usfk         			=_ttoi(strArray->GetAt(nSeq++));	
	pst.bch         				=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.bch_usfk			        =_ttoi(strArray->GetAt(nSeq++));	
	pst.g0ch				        =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.g0ch_usfk			        =_ttoi(strArray->GetAt(nSeq++));	
	pst.gch							=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.gch_usfk			        =_ttoi(strArray->GetAt(nSeq++));	
	pst.r					        =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.r_us_fk						=_ttoi(strArray->GetAt(nSeq++));	
	pst.r0					        =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.r0_us_fk			        =_ttoi(strArray->GetAt(nSeq++));	
	pst.x					        =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.x_us_fk						=_ttoi(strArray->GetAt(nSeq++));
	pst.x0							=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.x0_us_fk					=_ttoi(strArray->GetAt(nSeq++));	
	pst.thermalLimit				=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.thermalLimit_us_fk			=_ttoi(strArray->GetAt(nSeq++));	
	pst.ETLimit						=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ETLimit_us_fk				=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_PERLENGTHSEQUENCEIMPEDANCE));
}
void OnInsertBUSBARSECTION(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_BUSBARSECTION* ptrBase				= (ST_COMMON_BUSBARSECTION*)(*p);

	ST_COMMON_BUSBARSECTION pst = {0,};

	int nSeq = 0;
	pst.BusId						=_ttoi(strArray->GetAt(nSeq++));	
	pst.VLFK              			=_ttoi(strArray->GetAt(nSeq++));	
	pst.CEQFK              		=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.busorder         			=_ttoi(strArray->GetAt(nSeq++));	

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_BUSBARSECTION));
}
void OnInsertCOMPOSITESWITCH(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_COMPOSITESWITCH* ptrBase				= (ST_COMMON_COMPOSITESWITCH*)(*p);

	ST_COMMON_COMPOSITESWITCH pst = {0,};

	int nSeq = 0;
	pst.CPSID						=_ttoi(strArray->GetAt(nSeq++));
	pst.PSRFK              			=_ttoi(strArray->GetAt(nSeq++));	
	pst.EQCFK              			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,				strArray->GetAt(nSeq++));
	
	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_COMPOSITESWITCH));
}
void OnInsertPOWERTRANSFORMER(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_POWERTRANSFORMER* ptrBase				= (ST_COMMON_POWERTRANSFORMER*)(*p);

	ST_COMMON_POWERTRANSFORMER pst = {0,};

	int nSeq = 0;
	pst.PTRID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.PSRFK					=_ttoi(strArray->GetAt(nSeq++));	
	pst.EQCFK              		=_ttoi(strArray->GetAt(nSeq++));	
	pst.bankNo              		=_ttoi(strArray->GetAt(nSeq++));	
	pst.bmagSat              		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.bmagSet_usfk              	=_ttoi(strArray->GetAt(nSeq++));	
	pst.magBasekV              	=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.magBasekV_usfk             =_ttoi(strArray->GetAt(nSeq++));	
	pst.magSatFlux              	=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.magSatFlux_usfk            =_ttoi(strArray->GetAt(nSeq++));	
	pst.Phase              		=_ttoi(strArray->GetAt(nSeq++));	
	pst.transCoolingType           =_ttoi(strArray->GetAt(nSeq++));	
	pst.transformerType            =_ttoi(strArray->GetAt(nSeq++));	

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_POWERTRANSFORMER));
}
void OnInsertTRANSFORMERWINDING(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_TRANSFORMERWINDING* ptrBase				= (ST_COMMON_TRANSFORMERWINDING*)(*p);

	ST_COMMON_TRANSFORMERWINDING pst = {0,};

	int nSeq = 0;
	pst.TRWID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.PTRFK						=_ttoi(strArray->GetAt(nSeq++));	
	pst.CEQFK						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	//pst.BVFK             			=_ttoi(strArray->GetAt(5));	
	//pst.TCHGFK                  	=_ttoi(strArray->GetAt(nSeq++));	
	pst.connectionType       		=_ttoi(strArray->GetAt(nSeq++));	
	pst.windingType				=_ttoi(strArray->GetAt(nSeq++));	
	pst.r                     		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.r_usfk						=_ttoi(strArray->GetAt(nSeq++));	
	pst.r0               			=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.r0_usfk					=_ttoi(strArray->GetAt(nSeq++));	
	pst.x							=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.x_usfk						=_ttoi(strArray->GetAt(nSeq++));
	pst.x0            				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.x0_usfk       				=_ttoi(strArray->GetAt(nSeq++));
	pst.grounded      				=_ttoi(strArray->GetAt(nSeq++));
	//pst.grounded_usfk 				=_ttoi(strArray->GetAt(18));
	pst.rground       				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.rground_usfk  				=_ttoi(strArray->GetAt(nSeq++));
	pst.xground       				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.xground_usfk  				=_ttoi(strArray->GetAt(nSeq++));
	pst.ratedKV       				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.ratedKV_usfk  				=_ttoi(strArray->GetAt(nSeq++));
	pst.ratedMVA      				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.ratedMVA_usfk 				=_ttoi(strArray->GetAt(nSeq++));
	pst.eMVA          				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.eMVA_usfk     				=_ttoi(strArray->GetAt(nSeq++));
	pst.TCFK						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_TRANSFORMERWINDING));
}
void OnInsertTAPCHANGER(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_TAPCHANGER* ptrBase				= (ST_COMMON_TAPCHANGER*)(*p);

	ST_COMMON_TAPCHANGER pst = {0,};

	int nSeq = 0;
	pst.TCID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));	
	pst.PSRTYFK          			=_ttoi(strArray->GetAt(nSeq++));	
	pst.highStep           		=_ttoi(strArray->GetAt(nSeq++));	
	pst.lowSetp                 	=_ttoi(strArray->GetAt(nSeq++));	
	pst.neutralStep          		=_ttoi(strArray->GetAt(nSeq++));	
	pst.normalStep     			=_ttoi(strArray->GetAt(nSeq++));	
	pst.SVI                   		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.SVI_usfk       			=_ttoi(strArray->GetAt(nSeq++));	
	pst.tculControlMode  			=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_TAPCHANGER));
}
void OnInsertTAPREGULATIONSCHEDULE(long* p, int idx, CStringArray *strArray)		
{
	ST_COMMON_TAPREGULATIONSCHEDULE* ptrBase				= (ST_COMMON_TAPREGULATIONSCHEDULE*)(*p);

	ST_COMMON_TAPREGULATIONSCHEDULE pst = {0,};

	int nSeq = 0;
	pst.TRSCID						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	pst.TCFK						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.AVR			  			=_ttoi(strArray->GetAt(nSeq++));	
	pst.PATBSVL           			=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.PATBSVL_usfk       		=_ttoi(strArray->GetAt(nSeq++));	
	pst.PADEV			         	=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.PADEV_usfk		      		=_ttoi(strArray->GetAt(nSeq++));	
	pst.PBTBSVL        			=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.PBTBSVL_usfk          		=_ttoi(strArray->GetAt(nSeq++));	
	pst.PBDEV						=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.PBDEV_usfk		  			=_ttoi(strArray->GetAt(nSeq++));
	pst.PCTBSVL					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PCTBSVL_usfk				=_ttoi(strArray->GetAt(nSeq++));
	pst.PCDEV						=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PCDEV_usfk					=_ttoi(strArray->GetAt(nSeq++));
	pst.VVOFLAG					=_ttoi(strArray->GetAt(nSeq++));
	pst.CON3P						=_ttoi(strArray->GetAt(nSeq++));
	pst.IIPFVM						=_ttoi(strArray->GetAt(nSeq++));
	pst.PACOMPR					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PACOMPX					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PBCOMPR					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PBCOMPX					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PCCOMPR					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PCCOMPX					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.CONMEAP3					=_ttoi(strArray->GetAt(nSeq++));
	pst.PATAPCOST					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PACONTAPMX					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PBTAPCOST					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PBCONTAPMX					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PCTAPCOST					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PCCONTAPMX					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PACONTAPMXDAY				=_ttoi(strArray->GetAt(nSeq++));
	pst.PATAPOPDAY					=_ttoi(strArray->GetAt(nSeq++));
	pst.PBCONTAPMXDAY				=_ttoi(strArray->GetAt(nSeq++));
	pst.PBTAPOPDAY					=_ttoi(strArray->GetAt(nSeq++));
	pst.PCCONTAPMXDAY				=_ttoi(strArray->GetAt(nSeq++));
	pst.PCTAPOPDAY					=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_TAPREGULATIONSCHEDULE));
}
void OnInsertPROTECTIONEQUIPMENT(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_PROTECTIONEQUIPMENT* ptrBase				= (ST_COMMON_PROTECTIONEQUIPMENT*)(*p);

	ST_COMMON_PROTECTIONEQUIPMENT pst = {0,};

	int nSeq = 0;
	pst.PEQID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,				strArray->GetAt(nSeq++));
	//pst.RSFK			  			=_ttoi(strArray->GetAt(nSeq++));	
	//pst.CRFK           			=_ttoi(strArray->GetAt(nSeq++));	
	pst.EquipmentType       		=_ttoi(strArray->GetAt(nSeq++));	
	pst.DIRTYPE						=_ttoi(strArray->GetAt(nSeq++));	
	pst.CTRATIO		      			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Manufacture,		strArray->GetAt(nSeq++));
	pst.RecloserType        		=_ttoi(strArray->GetAt(nSeq++));	
	
	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_PROTECTIONEQUIPMENT));
}
void OnInsertRECLOSESEQUENCE(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_RECLOSESEQUENCE* ptrBase				= (ST_COMMON_RECLOSESEQUENCE*)(*p);

	ST_COMMON_RECLOSESEQUENCE pst = {0,};

	int nSeq = 0;
	pst.RSID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	pst.PEQFK						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,				strArray->GetAt(nSeq++));
	pst.RecloseDelay			  	=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.RecloseDelay_usfk			=_ttoi(strArray->GetAt(nSeq++));	
	pst.recloseStep       			=_ttoi(strArray->GetAt(nSeq++));		

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_RECLOSESEQUENCE));
}
void OnInsertCURRENTRELAY(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_CURRENTRELAY* ptrBase				= (ST_COMMON_CURRENTRELAY*)(*p);

	ST_COMMON_CURRENTRELAY pst = {0,};

	int nSeq = 0;
	pst.CRID					=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.PEQFK					=_ttoi(strArray->GetAt(nSeq++));
	pst.OCR_MCODEFK    	  		=_ttoi(strArray->GetAt(nSeq++));	
	pst.OCGR_MCODEFK			=_ttoi(strArray->GetAt(nSeq++));	
	pst.TAPCHOICE      			=_ttoi(strArray->GetAt(nSeq++));	
	pst.LEVERSTAP      	  		=_ttoi(strArray->GetAt(nSeq++));	
	pst.RECTMPAA				=_ttoi(strArray->GetAt(nSeq++));	
	pst.RECTMPAB       			=_ttoi(strArray->GetAt(nSeq++));	
	pst.RECTMPAC       	  		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GROUNDTAPCHOICE			=_ttoi(strArray->GetAt(nSeq++));	
	pst.GROUNDLEVERSTAP			=_ttoi(strArray->GetAt(nSeq++));	

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_CURRENTRELAY));
}
void OnInsertBATTERYSTORAGE(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_BATTERYSTORAGE* ptrBase				= (ST_COMMON_BATTERYSTORAGE*)(*p);

	ST_COMMON_BATTERYSTORAGE pst = {0,};

	int nSeq = 0;
	pst.BATTID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.GENFK						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));	
	pst.ESSCHGTM 					=_ttoi(strArray->GetAt(nSeq++));
	pst.ESSCHGTM_usfk	  			=_ttoi(strArray->GetAt(nSeq++));
	pst.ESSDCHGTM 					=_ttoi(strArray->GetAt(nSeq++));	
	pst.ESSDCHGTM_usfk				=_ttoi(strArray->GetAt(nSeq++));	
	pst.ESSTYPE       				=_ttoi(strArray->GetAt(nSeq++));	
	pst.ESSMXSOC       				=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ESSMXSOC_usfk  	  			=_ttoi(strArray->GetAt(nSeq++));
	pst.ESSMNSOC      				=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ESSMNSOC_usfk 				=_ttoi(strArray->GetAt(nSeq++));
	pst.ESSCHGEFF      	  			=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ESSCHGEFF_usfk 				=_ttoi(strArray->GetAt(nSeq++));
	pst.ESSCRATIO     				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.ESSCRATIO_usfk	  			=_ttoi(strArray->GetAt(nSeq++));
	pst.ESSMWh     					=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ESSMWh_USFK					=_ttoi(strArray->GetAt(nSeq++));
	pst.ESSCHARMXMW					=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ESSCHARMXMW_USFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.ESSCHARMNMW					=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ESSCHARMNMW_USFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.ESSDICHMXMW					=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ESSDICHMXMW_USFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.ESSDICHMNMW					=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ESSDICHMNMW_USFK			=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_BATTERYSTORAGE));
}
void OnInsertGENERATINGUNIT(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_GENERATINGUNIT* ptrBase				= (ST_COMMON_GENERATINGUNIT*)(*p);

	ST_COMMON_GENERATINGUNIT pst = {0,};

	int nSeq = 0;
	pst.GENID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.CEQFK						=_ttoi(strArray->GetAt(nSeq++));	
	//pst.GRSHFK						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	//pst.BVFK                		=_ttoi(strArray->GetAt(5));	
	pst.GenerationType      		=_ttoi(strArray->GetAt(nSeq++));	
	pst.intnectionType        		=_ttoi(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMW_PA         =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMW_PA_usfk    =_ttoi(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMW_PA         =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMW_PA_usfk    =_ttoi(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMVAR_PA       =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMVAR_PA_usfk  =_ttoi(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMVAR_PA       =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMVAR_PA_usfk  =_ttoi(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMW_PB         =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMW_P_usfk     =_ttoi(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMW_PB         =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMW_PB_usfk    =_ttoi(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMVAR_PB       =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMVAR_PB_usfk  =_ttoi(strArray->GetAt(nSeq++));
	pst.minimumOperatingMVAR_PB       =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMVAR_PB_usfk  =_ttoi(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMW_PC         =(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.maximumOperatingMW_PC_usfk    =_ttoi(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMW_PC         =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMW_PC_usfk    =_ttoi(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMVAR_PC       =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.maximumOperatingMVAR_PC_usfk  =_ttoi(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMVAR_PC       =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.minimumOperatingMVAR_PC_usfk  =_ttoi(strArray->GetAt(nSeq++));	
	pst.genSTX              		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.genSTX_usfk         		=_ttoi(strArray->GetAt(nSeq++));	
	pst.genTX               		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.genTX_usfk          		=_ttoi(strArray->GetAt(nSeq++));	
	pst.genSSX              		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.genSSX_usfk         		=_ttoi(strArray->GetAt(nSeq++));	
	pst.genZERX             		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.genZERX_usfk        		=_ttoi(strArray->GetAt(nSeq++));	
	pst.baseMVA             		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.baseMVA_usfk        		=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.TEL,				strArray->GetAt(nSeq++));
	pst.efficiency          		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.efficiency_usfk     		=_ttoi(strArray->GetAt(nSeq++));	
	pst.normalPF            		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.normalPF_usfk       		=_ttoi(strArray->GetAt(nSeq++));	
	pst.Pole                		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.connectionType      		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ0             		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ0_usfk      		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ0           		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ0_usfk      		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ20          		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ20_usfk     		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ20          		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ20_usfk     		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ40          		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ40_usfk     		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ40          		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ40_usfk     		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ60          		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ60_usfk     		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ60          		=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.GEN_MAXQ60_usfk     		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ80          		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ80_usfk     		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ80          		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ80_usfk     		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ100         		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MINQ100_usfk      		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ100         		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_MAXQ100_usfk    		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_PFMINLAG        		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_PFMINLAG_usfk   		=_ttoi(strArray->GetAt(nSeq++));	
	pst.GEN_PFMINLEAD       		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GEN_PFMINLEAD_usfk  		=_ttoi(strArray->GetAt(nSeq++));	
	pst.MAXECOMW            		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.MAXECOMW_usfk       		=_ttoi(strArray->GetAt(nSeq++));	
	pst.MINECOMW            		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.MINECOMW_usfk       		=_ttoi(strArray->GetAt(nSeq++));	
	pst.ratedGrossMaxMW     		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ratedGrossMaxMW_usfk		=_ttoi(strArray->GetAt(nSeq++));	
	pst.ratedGrossMinMW     		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ratedGrossMinMW_usfk		=_ttoi(strArray->GetAt(nSeq++));
	pst.raiseRampRate       		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.raiseRampRate_usfk  		=_ttoi(strArray->GetAt(nSeq++));	
	pst.lowerRampRate       		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.lowerRampRate_usfk       	=_ttoi(strArray->GetAt(nSeq++));
	pst.muston						=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.muston_USFK					=_ttoi(strArray->GetAt(nSeq++));
	pst.mustoff						=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.mustoff_USFK				=_ttoi(strArray->GetAt(nSeq++));
	pst.gen_mea						=_ttoi(strArray->GetAt(nSeq++));
	pst.gen_COgenEff				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.gen_COgenEff_USFK			=_ttoi(strArray->GetAt(nSeq++));
	
	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_GENERATINGUNIT));
}
void OnInsertGENREGULATIONSCHEDULE(long* p, int idx, CStringArray *strArray)		
{
	ST_COMMON_GENREGULATIONSCHEDULE* ptrBase				= (ST_COMMON_GENREGULATIONSCHEDULE*)(*p);

	ST_COMMON_GENREGULATIONSCHEDULE pst = {0,};

	int nSeq = 0;
	pst.RSCID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.GENFK						=_ttoi(strArray->GetAt(nSeq++));	
	pst.AVR                  		=_ttoi(strArray->GetAt(nSeq++));	
	pst.TBSVL              		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.TBSVL_usfk         		=_ttoi(strArray->GetAt(nSeq++));	
	pst.DEV                	  	=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.DEV_usfk           		=_ttoi(strArray->GetAt(nSeq++));	
	pst.PF                 		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.PF_usfk              		=_ttoi(strArray->GetAt(nSeq++));	
	pst.FLTContribution    		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.FLTContribution_usfk		=_ttoi(strArray->GetAt(nSeq++));	
	pst.VVOFLAG              		=_ttoi(strArray->GetAt(nSeq++));	
	pst.MVARCONMODE        		=_ttoi(strArray->GetAt(nSeq++));	
	pst.OUTQ               		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.OUTQ_usfk            		=_ttoi(strArray->GetAt(nSeq++));	
	pst.PFVVOMINLAG        		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.PFVVOMINLAG_usfk   		=_ttoi(strArray->GetAt(nSeq++));	
	pst.PFVVOMINLEAD         		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.PFVVOMINLEAD_usfk  		=_ttoi(strArray->GetAt(nSeq++));	

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_GENREGULATIONSCHEDULE));
}
void OnInsertWINDTURBINE(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_WINDTURBINE* ptrBase				= (ST_COMMON_WINDTURBINE*)(*p);

	ST_COMMON_WINDTURBINE pst = {0,};

	int nSeq = 0;
	pst.WTID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.GENFK						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.LENGTH               		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.LENGTH_usfk          		=_ttoi(strArray->GetAt(nSeq++));	
	pst.HEIGHT               		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.HEIGHT_usfk				=_ttoi(strArray->GetAt(nSeq++));	
	pst.ALTITUDE             		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.ALTITUDE_usfk        		=_ttoi(strArray->GetAt(nSeq++));	
	pst.WINDDIR              		=_ttoi(strArray->GetAt(nSeq++));	
	pst.WINDREVERSE          		=_ttoi(strArray->GetAt(nSeq++));	
	pst.LAT							=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.LAT_USFK        		    =_ttoi(strArray->GetAt(nSeq++));
	pst.LONG						=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.LONG_USFK        		    =_ttoi(strArray->GetAt(nSeq++));
	pst.ALT							=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.ALT_USFK        		    =_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_WINDTURBINE));
}
void OnInsertPHOTOVOLTAIC(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_PHOTOVOLTAIC* ptrBase				= (ST_COMMON_PHOTOVOLTAIC*)(*p);

	ST_COMMON_PHOTOVOLTAIC pst = {0,};

	int nSeq = 0;
	pst.PVID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.GENFK						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.SIZE                 		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.SIZE_usfk            		=_ttoi(strArray->GetAt(nSeq++));	
	pst.EFF                  		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.EFF_usfk             		=_ttoi(strArray->GetAt(nSeq++));	
	pst.NOOFMD               		=_ttoi(strArray->GetAt(nSeq++));	
	pst.LAT							=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.LAT_USFK        		    =_ttoi(strArray->GetAt(nSeq++));
	pst.LONG						=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.LONG_USFK        		    =_ttoi(strArray->GetAt(nSeq++));
	pst.ALT							=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.ALT_USFK        		    =_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_PHOTOVOLTAIC));
}
void OnInsertGENUNITOPCOSTCURVE(long* p, int idx, CStringArray *strArray)		
{
	ST_COMMON_GENUNITOPCOSTCURVE* ptrBase				= (ST_COMMON_GENUNITOPCOSTCURVE*)(*p);

	ST_COMMON_GENUNITOPCOSTCURVE pst = {0,};
	
	int nSeq = 0;
	pst.GUOCCID              	=_ttoi(strArray->GetAt(nSeq++));	
	pst.GENFK                 	=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.GENCSTCUR_TYPE,			strArray->GetAt(nSeq++));
	pst.GENCSTCUR_COEF1      	=_ttoi(strArray->GetAt(nSeq++));	
	pst.GENCSTCUR_COEF2      	=_ttoi(strArray->GetAt(nSeq++));	
	pst.GENCSTCUR_CONST      	=_ttoi(strArray->GetAt(nSeq++));		
	pst.GENCSTCUR_STC			=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.GENCSTCUR_USFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW1		    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST1	    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW2		    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST2	    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW3		    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST3	    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW4		    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST4	    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW5		    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST5	    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW6		    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST6	    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW7		    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST7	    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW8		    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST8	    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW9		    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST9	    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW10		    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST10	    =_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KW_USFK		=_ttoi(strArray->GetAt(nSeq++));
	pst.GENCSTCUR_KWCOST_USFK	=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_GENUNITOPCOSTCURVE));
}
void OnInsertENERGYCONSUMER(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_ENERGYCONSUMER* ptrBase				= (ST_COMMON_ENERGYCONSUMER*)(*p);

	ST_COMMON_ENERGYCONSUMER pst = {0,};

	int nSeq = 0;
	pst.ECRID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.ACLSFK						=_ttoi(strArray->GetAt(nSeq++));	
	pst.CEQFK						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.customerCount              =_ttoi(strArray->GetAt(nSeq++));	
	pst.pfixed            			=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.pfixed_usfk                =_ttoi(strArray->GetAt(nSeq++));	
	pst.qfixed             		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.qfixed_usfk               	=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Tel,				strArray->GetAt(nSeq++));
	_tcscpy_s(pst.HP,				strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Customer_key,	strArray->GetAt(nSeq++));
	pst.Priority              		=_ttoi(strArray->GetAt(nSeq++));	
	pst.SmsUse         			=_ttoi(strArray->GetAt(nSeq++));
	pst.WATFK         			=_ttoi(strArray->GetAt(nSeq++));
	pst.LoadDiv					=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.LoadMea				    =_ttoi(strArray->GetAt(nSeq++));
	pst.LoadCapMW				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.LoadCapMVAR			    =(FLOAT)_ttof(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_ENERGYCONSUMER));
}
void OnInsertSHUNTCOMPASATOR(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_SHUNTCOMPASATOR* ptrBase				= (ST_COMMON_SHUNTCOMPASATOR*)(*p);

	ST_COMMON_SHUNTCOMPASATOR pst = {0,};

	int nSeq = 0;
	pst.SCID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.CEQFK						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	//pst.BVFK						=_ttoi(strArray->GetAt(nSeq++));	
	pst.NominalMVAr            	=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.NominalMVAr_usfk           =_ttoi(strArray->GetAt(nSeq++));	

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_SHUNTCOMPASATOR));
}
void OnInsertSTATICVARCOMPENSATOR(long* p, int idx, CStringArray *strArray)		
{
	ST_COMMON_STATICVARCOMPENSATOR* ptrBase				= (ST_COMMON_STATICVARCOMPENSATOR*)(*p);

	ST_COMMON_STATICVARCOMPENSATOR pst = {0,};

	int nSeq = 0;
	pst.SVCID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.CEQFK						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.capacitiveRating    		=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.capacitiveRating_usfk      =_ttoi(strArray->GetAt(nSeq++));	
	pst.inductiveRating            =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.inductiveRating_usfk		=_ttoi(strArray->GetAt(nSeq++));	
	pst.slope                      =_ttoi(strArray->GetAt(nSeq++));	
	pst.SVCControlMode      		=_ttoi(strArray->GetAt(nSeq++));	
	pst.VoltageSetPoint            =(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.VoltageSetPoint_usfk       =_ttoi(strArray->GetAt(nSeq++));	
	pst.BaNo						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_STATICVARCOMPENSATOR));
}
void OnInsertPOWERSYSTEMRESOURCE(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_POWERSYSTEMRESOURCE* ptrBase				= (ST_COMMON_POWERSYSTEMRESOURCE*)(*p);

	ST_COMMON_POWERSYSTEMRESOURCE pst = {0,};

	int nSeq = 0;
	pst.PSRID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.PSRTYPEFK					=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,				strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_POWERSYSTEMRESOURCE));
}
void OnInsertPSRTYPE(long* p, int idx, CStringArray *strArray)						
{
	ST_COMMON_PSRTYPE* ptrBase				= (ST_COMMON_PSRTYPE*)(*p);

	ST_COMMON_PSRTYPE pst = {0,};

	int nSeq = 0;
	pst.PSRTYPEID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,				strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,					strArray->GetAt(nSeq++));
	_tcscpy_s(pst.mRCode,				strArray->GetAt(nSeq++));
	pst.symbolfk						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_PSRTYPE));
}
void OnInsertEQUIPMENTCONTAINER(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_EQUIPMENTCONTAINER* ptrBase				= (ST_COMMON_EQUIPMENTCONTAINER*)(*p);

	ST_COMMON_EQUIPMENTCONTAINER pst = {0,};

	int nSeq = 0;
	pst.EQCID						=_ttoi(strArray->GetAt(nSeq++));	
	pst.SGRFK						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
//	pst.mRCode						=_ttoi(strArray->GetAt(nSeq++));
	pst.PSRFK						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_EQUIPMENTCONTAINER));
}
void OnInsertSYMBOL(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_SYMBOL* ptrBase				= (ST_COMMON_SYMBOL*)(*p);

	ST_COMMON_SYMBOL pst = {0,};

	int nSeq = 0;
	pst.SYMBOLID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.NAME,				strArray->GetAt(nSeq++));
	_tcscpy_s(pst.FILENAME,			strArray->GetAt(nSeq++));
	pst.FILESIZE						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_SYMBOL));
}
void OnInsertDASDIAGRAMINFO(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_DASDIAGRAMINFO* ptrBase				= (ST_COMMON_DASDIAGRAMINFO*)(*p);

	ST_COMMON_DASDIAGRAMINFO pst = {0,};;

	int nSeq = 0;
	pst.DAS_DIAID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.NAME,					strArray->GetAt(nSeq++));
	_tcscpy_s(pst.VERSION,				strArray->GetAt(nSeq++));
	_tcscpy_s(pst.EDITOR,				strArray->GetAt(nSeq++));
	_tcscpy_s(pst.BUILDTIME,			strArray->GetAt(nSeq++));
	//pst.BUILDTIME						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.FILENAME,				strArray->GetAt(nSeq++));
	pst.FILESIZE						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_DASDIAGRAMINFO));
}
void OnInsertSTATIONDIAGRAMINFO(long* p, int idx, CStringArray *strArray)	
{
	ST_COMMON_STATIONDIAGRAMINFO* ptrBase				= (ST_COMMON_STATIONDIAGRAMINFO*)(*p);

	ST_COMMON_STATIONDIAGRAMINFO pst = {0,};

	int nSeq = 0;
	pst.STATIONDIAID					=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.NAME,					strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.VERSION,				strArray->GetAt(nSeq++));
	_tcscpy_s(pst.EDITOR,				strArray->GetAt(nSeq++));
	_tcscpy_s(pst.BUILDTIME,			strArray->GetAt(nSeq++));
	//pst.BUILDTIME						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.FILENAME,				strArray->GetAt(nSeq++));
	pst.FILESIZE						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_STATIONDIAGRAMINFO));
}
void OnInsertDISCRETE(long* p, int idx, CStringArray *strArray)				
{
	ST_COMMON_DISCRETE* ptrBase				= (ST_COMMON_DISCRETE*)(*p);

	ST_COMMON_DISCRETE pst = {0,};

	int nSeq = 0;
	pst.PID								=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,				strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,					strArray->GetAt(nSeq++));
	pst.SSId      						=_ttoi(strArray->GetAt(nSeq++));
	pst.DLId      						=_ttoi(strArray->GetAt(nSeq++));
	pst.CEQId     						=_ttoi(strArray->GetAt(nSeq++));
	pst.RUID      						=_ttoi(strArray->GetAt(nSeq++));
	pst.MeasureTypeID					=_ttoi(strArray->GetAt(nSeq++));
	pst.TMId      						=_ttoi(strArray->GetAt(nSeq++));
	pst.StateGrpId						=_ttoi(strArray->GetAt(nSeq++));
	pst.CommandID 						=_ttoi(strArray->GetAt(nSeq++));
	pst.NormalVal 						=_ttoi(strArray->GetAt(nSeq++));
	pst.AbnormalVal						=_ttoi(strArray->GetAt(nSeq++));
	pst.Initval   						=_ttoi(strArray->GetAt(nSeq++));
	pst.Position  						=_ttoi(strArray->GetAt(nSeq++));
	pst.CircuitNo 						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_DISCRETE));
}
void OnInsertSETDISCRETE(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_SETDISCRETE* ptrBase				= (ST_COMMON_SETDISCRETE*)(*p);

	ST_COMMON_SETDISCRETE pst = {0,};

	int nSeq = 0;
	pst.PID							=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,				strArray->GetAt(nSeq++));
	pst.SSId      					=_ttoi(strArray->GetAt(nSeq++));
	pst.DLId      					=_ttoi(strArray->GetAt(nSeq++));
	pst.CEQId     					=_ttoi(strArray->GetAt(nSeq++));
	pst.RUID      					=_ttoi(strArray->GetAt(nSeq++));
	pst.MeasureTypeID				=_ttoi(strArray->GetAt(nSeq++));
	pst.TMId      					=_ttoi(strArray->GetAt(nSeq++));
	pst.StateGrpId					=_ttoi(strArray->GetAt(nSeq++));
	//pst.DiscreteId					=_ttoi(strArray->GetAt(9));
	//pst.Initval   					=_ttoi(strArray->GetAt(10));
	pst.Position  					=_ttoi(strArray->GetAt(nSeq++));
	pst.CircuitNo 					=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_SETDISCRETE));
}
void OnInsertMEASUREMENT(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_MEASUREMENT* ptrBase				= (ST_COMMON_MEASUREMENT*)(*p);

	ST_COMMON_MEASUREMENT pst = {0,};

	int nSeq = 0;
	pst.PID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.SSId       				=_ttoi(strArray->GetAt(nSeq++));
	pst.DLId       				=_ttoi(strArray->GetAt(nSeq++));
	pst.CEQId      				=_ttoi(strArray->GetAt(nSeq++));
	pst.RUID       				=_ttoi(strArray->GetAt(nSeq++));
	pst.MeasureTypeID 			=_ttoi(strArray->GetAt(nSeq++));
	pst.TMId       				=_ttoi(strArray->GetAt(nSeq++));
	pst.UnitId     				=_ttoi(strArray->GetAt(nSeq++));
	pst.RLS_FK     				=_ttoi(strArray->GetAt(nSeq++));
	pst.LS_FK      				=_ttoi(strArray->GetAt(nSeq++));
	pst.SF_FK      				=_ttoi(strArray->GetAt(nSeq++));
	pst.InitVal    				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.Position				=_ttoi(strArray->GetAt(nSeq++));
	pst.CircuitNo  				=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_MEASUREMENT));
}
void OnInsertSETMEASUREMENT(long* p, int idx, CStringArray *strArray)			
{
	ST_COMMON_SETMEASUREMENT* ptrBase				= (ST_COMMON_SETMEASUREMENT*)(*p);

	ST_COMMON_SETMEASUREMENT pst = {0,};

	int nSeq = 0;
	pst.PID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.SSId      				=_ttoi(strArray->GetAt(nSeq++));
	pst.DLId      				=_ttoi(strArray->GetAt(nSeq++));
	pst.CEQId     				=_ttoi(strArray->GetAt(nSeq++));
	pst.RUID      				=_ttoi(strArray->GetAt(nSeq++));
	pst.MeasureTypeID			=_ttoi(strArray->GetAt(nSeq++));
	pst.StateGrpId				=_ttoi(strArray->GetAt(nSeq++));
	pst.TMId      				=_ttoi(strArray->GetAt(nSeq++));
	pst.UnitID    				=_ttoi(strArray->GetAt(nSeq++));
	pst.RLS_FK    				=_ttoi(strArray->GetAt(nSeq++));
	pst.SF_FK     				=_ttoi(strArray->GetAt(nSeq++));
	pst.NormalValue				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.StepValue				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.Position  				=_ttoi(strArray->GetAt(nSeq++));
	pst.CircuitNo 				=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_SETMEASUREMENT));
	
}
void OnInsertACCUMULATOR(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_ACCUMULATOR* ptrBase				= (ST_COMMON_ACCUMULATOR*)(*p);

	ST_COMMON_ACCUMULATOR pst = {0,};

	int nSeq = 0;
	pst.PID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));
	pst.SSId       				=_ttoi(strArray->GetAt(nSeq++));
	pst.DLId       				=_ttoi(strArray->GetAt(nSeq++));
	pst.CEQId      				=_ttoi(strArray->GetAt(nSeq++));
	pst.RUID       				=_ttoi(strArray->GetAt(nSeq++));
	pst.MeasureTypeID 			=_ttoi(strArray->GetAt(nSeq++));
	pst.TMId       				=_ttoi(strArray->GetAt(nSeq++));
	//pst.UnitID     				=_ttoi(strArray->GetAt(nSeq++));
	pst.RLS_FK     				=_ttoi(strArray->GetAt(nSeq++));
	pst.LS_FK     					=_ttoi(strArray->GetAt(nSeq++));
	//pst.SF_FK    					=_ttoi(strArray->GetAt(11));
	//pst.InitVal    				=(FLOAT)_ttof(strArray->GetAt(12));
	pst.Position   				=_ttoi(strArray->GetAt(nSeq++));
	pst.CircuitNo  				=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_ACCUMULATOR));

}
void OnInsertCALCULATION(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_CALCULATION* ptrBase				= (ST_COMMON_CALCULATION*)(*p);

	ST_COMMON_CALCULATION pst = {0,};

	int nSeq = 0;
	pst.PID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.mRIDFK,		strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,			strArray->GetAt(nSeq++));	
	pst.DpGrpFK      			=_ttoi(strArray->GetAt(nSeq++));
	pst.UnitID		 			=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.formular,		strArray->GetAt(nSeq++));
	pst.degree   				=_ttoi(strArray->GetAt(nSeq++));
	pst.interval  				=_ttoi(strArray->GetAt(nSeq++));
	pst.Alarm     				=_ttoi(strArray->GetAt(nSeq++));
	pst.Important 				=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_CALCULATION));

}

void OnInsertPOSITION(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_POSITION* ptrBase				= (ST_COMMON_POSITION*)(*p);

	ST_COMMON_POSITION pst = {0,};

	int nSeq = 0;
	pst.PositionID					=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.NAME,			strArray->GetAt(nSeq++));
	pst.PSRFK   				    =_ttoi(strArray->GetAt(nSeq++));
	pst.POSITIONX   				=_ttoi(strArray->GetAt(nSeq++));
	pst.POSITONY  					=_ttoi(strArray->GetAt(nSeq++));
	pst.Order     					=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_POSITION));
}


void OnInsertWATER(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_WATER* ptrBase = (ST_COMMON_WATER*)(*p);

	ST_COMMON_WATER pst = {0,};

	int nSeq = 0;
	pst.WATID					=_ttoi(strArray->GetAt(nSeq++));
	pst.WaterTCap				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.WaterTCap_USFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.WaterTMax				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.WaterTMin				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.WaterTInit				=(FLOAT)_ttof(strArray->GetAt(nSeq++));	
	pst.WaterT_USFK			    =_ttoi(strArray->GetAt(nSeq++));
	pst.Water_MCap				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.WaterMCap_USFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.Water_MEff				=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.WaterMEff_USFK			=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_WATER));
}

void OnInsertACM_APPGROUP(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_ACM_APPGROUP* ptrBase	= (ST_COMMON_ACM_APPGROUP*)(*p);

	ST_COMMON_ACM_APPGROUP pst = {0,};

	int nSeq = 0;
	pst.ACMAGID	=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_ACM_APPGROUP));
}

void OnInsertACM_MAPINDEX(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_ACM_MAPINDEX* ptrBase	= (ST_COMMON_ACM_MAPINDEX*)(*p);

	ST_COMMON_ACM_MAPINDEX pst = {0,};

	int nSeq = 0;
	pst.ACMMIID			=_ttoi(strArray->GetAt(nSeq++));
	pst.DPGC_ACMFK		=_ttoi(strArray->GetAt(nSeq++));
	pst.ACMAGFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.ACMTGFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.ACMTFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.MeasureTypeID	=_ttoi(strArray->GetAt(nSeq++));
	pst.Position		=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_name,	strArray->GetAt(nSeq++));
	_tcscpy_s(pst.upc_uptime,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_ACM_MAPINDEX));
}

void OnInsertACM_TABLE(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_ACM_TABLE* ptrBase	= (ST_COMMON_ACM_TABLE*)(*p);

	ST_COMMON_ACM_TABLE pst = {0,};

	int nSeq = 0;
	pst.ACMTID	=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_ACM_TABLE));
}

void OnInsertACM_TABLEGROUP(long* p, int idx, CStringArray *strArray)					
{
	ST_COMMON_ACM_TABLEGROUP* ptrBase	= (ST_COMMON_ACM_TABLEGROUP*)(*p);

	ST_COMMON_ACM_TABLEGROUP pst = {0,};

	int nSeq = 0;
	pst.ACMTGID	=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_ACM_TABLEGROUP));
}

void OnInsertPCS(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_PCS* ptrBase	= (ST_COMMON_PCS*)(*p);

	ST_COMMON_PCS pst = {0,};

	int nSeq = 0;
	pst.PCSID			=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.PCS_CAPMVA		=(FLOAT)_ttof(strArray->GetAt(nSeq++));
	pst.PCS_CAPMVA_USFK	=_ttoi(strArray->GetAt(nSeq++));
	pst.BSFK		    =_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_PCS));
}

void OnInsertMAINTRANSFORMER(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_MAINTRANSFORMER* ptrBase	= (ST_COMMON_MAINTRANSFORMER*)(*p);

	ST_COMMON_MAINTRANSFORMER pst = {0,};

	int nSeq = 0;
	pst.MTRID			=_ttoi(strArray->GetAt(nSeq++));
	pst.SSFK			=_ttoi(strArray->GetAt(nSeq++));
	pst.EQCFK			=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.mRIDFK, strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Name,	strArray->GetAt(nSeq++));
	pst.DPGC_ACMFK	    =_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_MAINTRANSFORMER));
}
void OnInsertVIRTUAL_LINE(long* p, int idx, CStringArray *strArray)
{
	ST_COMMON_VIRTUAL_LINE* ptrBase				= (ST_COMMON_VIRTUAL_LINE*)(*p);

	ST_COMMON_VIRTUAL_LINE pst = {0,};

	int nSeq = 0;
	pst.VirtualLineCEQID	  				=_ttoi(strArray->GetAt(nSeq++));
	pst.ReferenceLineCEQID     				=_ttoi(strArray->GetAt(nSeq++));	
	pst.ReferenceRTUCEQID	  				=_ttoi(strArray->GetAt(nSeq++));
	pst.DLID	  							=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_COMMON_VIRTUAL_LINE));
}

void OnInsertMEMO(long* p, int idx, CStringArray *strArray)						
{
	ST_OPR_MEMO* ptrBase				= (ST_OPR_MEMO*)(*p);

	ST_OPR_MEMO pst = {0,};

	int nSeq = 0;
	pst.MMID						=_ttoi(strArray->GetAt(nSeq++));	
	//pst.CREATE_TIME      			=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.CREATE_TIME,			strArray->GetAt(nSeq++));
	pst.SSFK   					=_ttoi(strArray->GetAt(nSeq++));
	pst.DLFK  						=_ttoi(strArray->GetAt(nSeq++));
	pst.CEQFK     					=_ttoi(strArray->GetAt(nSeq++));
	pst.USERID_FK     				=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.CONTENTS,			strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_OPR_MEMO));
}
void OnInsertMESSAGE(long* p, int idx, CStringArray *strArray)						
{
	ST_OPR_MESSAGE* ptrBase				= (ST_OPR_MESSAGE*)(*p);

	ST_OPR_MESSAGE pst = {0,};

	int nSeq = 0;
	pst.MSGID							=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.CREATE_TIME,			strArray->GetAt(nSeq++));	
	pst.MSG_TYPE   						=_ttoi(strArray->GetAt(nSeq++));
	pst.USERID_FK  						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.CONTENTS,				strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_OPR_MESSAGE));
}
void OnInsertCONSTRUCTION(long* p, int idx, CStringArray *strArray)				
{
	ST_OPR_CONSTRUCTION* ptrBase				= (ST_OPR_CONSTRUCTION*)(*p);

	ST_OPR_CONSTRUCTION pst = {0,};

	int nSeq = 0;
	pst.CTRID						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.CREATE_TIME,			strArray->GetAt(nSeq++));
	//pst.CREATE_TIME      			=_ttoi(strArray->GetAt(nSeq++));	
	pst.SSFK   						=_ttoi(strArray->GetAt(nSeq++));
	pst.DLFK  						=_ttoi(strArray->GetAt(nSeq++));
	pst.CEQFK  						=_ttoi(strArray->GetAt(nSeq++));
	pst.CONSTTYPE					=_ttoi(strArray->GetAt(nSeq++));
	//pst.EQ_TYPE  					=_ttoi(strArray->GetAt(5));
	pst.USERID_FK  					=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.CONTENTS,			strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_OPR_CONSTRUCTION));
}
void OnInsertOPERATORASSIGN(long* p, int idx, CStringArray *strArray)			
{
	ST_OPR_OPERATORASSIGN* ptrBase				= (ST_OPR_OPERATORASSIGN*)(*p);

	ST_OPR_OPERATORASSIGN pst = {0,};

	int nSeq = 0;
	pst.OPRAId							=_ttoi(strArray->GetAt(nSeq++));	
	pst.USERFK      					=_ttoi(strArray->GetAt(nSeq++));	
	pst.AssignType   					=_ttoi(strArray->GetAt(nSeq++));
	pst.TableId  						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_OPR_OPERATORASSIGN));
}
void OnInsertWAVE_LIST(long* p, int idx, CStringArray *strArray)					
{
	ST_OPR_WAVE_LIST* ptrBase				= (ST_OPR_WAVE_LIST*)(*p);

	ST_OPR_WAVE_LIST pst = {0,};

	int nSeq = 0;
	pst.WaveListId						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.CreateTm,			strArray->GetAt(nSeq++));
	//pst.CreateTm      					=_ttoi(strArray->GetAt(nSeq++));	
	pst.RUID   						    =_ttoi(strArray->GetAt(nSeq++));
	pst.SampRate  						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.Filename,			strArray->GetAt(nSeq++));
	pst.FileSize  						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_OPR_WAVE_LIST));
}
void OnInsertWAVE_FILE(long* p, int idx, CStringArray *strArray)					
{
	ST_OPR_WAVE_FILE* ptrBase				= (ST_OPR_WAVE_FILE*)(*p);

	ST_OPR_WAVE_FILE pst = {0,};

	int nSeq = 0;
	pst.WaveId						=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.CreateTm,			strArray->GetAt(nSeq++));
	//pst.CreateTm      					=_ttoi(strArray->GetAt(nSeq++));	
	pst.RUID   						=_ttoi(strArray->GetAt(nSeq++));
	pst.WaveType  						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.Filename,			strArray->GetAt(nSeq++));
	pst.FileSize  						=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_OPR_WAVE_FILE));
}
void OnInsertCOMPUTERSTATUS(long* p, int idx, CStringArray *strArray)			
{
	ST_OPR_COMPUTERSTATUS* ptrBase				= (ST_OPR_COMPUTERSTATUS*)(*p);

	ST_OPR_COMPUTERSTATUS pst = {0,};

	int nSeq = 0;
	pst.ComputerID						=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.ComputerName,			strArray->GetAt(nSeq++));	
	pst.ComputerType					=_ttoi(strArray->GetAt(nSeq++));
	pst.ActiveState						=_ttoi(strArray->GetAt(nSeq++));
	pst.RunState						=_ttoi(strArray->GetAt(nSeq++));
	pst.UpcActiveState					=_ttoi(strArray->GetAt(nSeq++));
	pst.UpcRunState						=_ttoi(strArray->GetAt(nSeq++));	
	pst.RdbRunState						=_ttoi(strArray->GetAt(nSeq++));
	pst.RdbRoleState					=_ttoi(strArray->GetAt(nSeq++));	
	_tcscpy_s(pst.SysStart_tm,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.SysStop_tm,			strArray->GetAt(nSeq++));
	_tcscpy_s(pst.lastupdate_tm,		strArray->GetAt(nSeq++));	
//	pst.SysStart_tm	   					=_ttoi(strArray->GetAt(nSeq++));	
//	pst.SysStop_tm						=_ttoi(strArray->GetAt(nSeq++));
//	pst.lastupdate_tm					=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_OPR_COMPUTERSTATUS));
}
void OnInsertCALCULATION_RESULT(long* p, int idx, CStringArray *strArray)
{
	ST_OPR_CALCULATION_RESULT* ptrBase				= (ST_OPR_CALCULATION_RESULT*)(*p);

	ST_OPR_CALCULATION_RESULT pst = {0,};

	int nSeq = 0;
	pst.PID        					=_ttoi(strArray->GetAt(nSeq++));	
	pst.VALUE         				=_ttoi(strArray->GetAt(nSeq++));	
	pst.Old_Value  					=_ttoi(strArray->GetAt(nSeq++));
	pst.TLQ        					=_ttoi(strArray->GetAt(nSeq++));
	_tcscpy_s(pst.LAST_UPDATE,		strArray->GetAt(nSeq++));
//	pst.LAST_UPDATE					=_ttoi(strArray->GetAt(nSeq++));

	memcpy(&ptrBase[idx], &pst, sizeof(ST_OPR_CALCULATION_RESULT));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// 공유 메모리 삭제 함수
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
void OnDelIDENTIFIEDOBJECT(long* p, int idx)
{
	ST_COMMON_IDENTIFIEDOBJECT* ptrBase								= (ST_COMMON_IDENTIFIEDOBJECT*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_IDENTIFIEDOBJECT));
}
void OnDelGEOGRAPHICALREGION(long* p, int idx)
{
	ST_COMMON_GEOGRAPHICALREGION* ptrBase								= (ST_COMMON_GEOGRAPHICALREGION*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_GEOGRAPHICALREGION));
}
void OnDelSUBGEOGRAPHICALREGION(long* p, int idx)
{
	ST_COMMON_SUBGEOGRAPHICALREGION* ptrBase								= (ST_COMMON_SUBGEOGRAPHICALREGION*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_SUBGEOGRAPHICALREGION));
}
void OnDelDATAPOINTGROUPCODE(long* p, int idx)
{	
	ST_COMMON_DATAPOINTGROUPCODE* ptrBase								= (ST_COMMON_DATAPOINTGROUPCODE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_DATAPOINTGROUPCODE));
}
void OnDelCOMPUTERCODE(long* p, int idx)
{
	ST_COMMON_COMPUTERCODE* ptrBase								= (ST_COMMON_COMPUTERCODE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_COMPUTERCODE));
}
void OnDelPROGRAMCODE(long* p, int idx)
{
	ST_COMMON_PROGRAMCODE* ptrBase								= (ST_COMMON_PROGRAMCODE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_PROGRAMCODE));
}
void OnDelOPERATORCODE(long* p, int idx)
{
	ST_COMMON_OPERATORCODE* ptrBase								= (ST_COMMON_OPERATORCODE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_OPERATORCODE));
}
void OnDelSWITCHTYPECODE(long* p, int idx)
{
	ST_COMMON_SWITCHTYPECODE* ptrBase								= (ST_COMMON_SWITCHTYPECODE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_SWITCHTYPECODE));
}
void OnDelCONSTRUCTIONCODE(long* p, int idx)
{
	ST_COMMON_CONSTRUCTIONCODE* ptrBase								= (ST_COMMON_CONSTRUCTIONCODE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_CONSTRUCTIONCODE));
}
void OnDelWAVECOMTYPE(long* p, int idx)
{
	ST_COMMON_WAVECOMTYPE* ptrBase								= (ST_COMMON_WAVECOMTYPE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_WAVECOMTYPE));
}
void OnDelSTATEGROUP(long* p, int idx)
{
	ST_COMMON_STATEGROUP* ptrBase								= (ST_COMMON_STATEGROUP*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_STATEGROUP));
}
void OnDelDATABYTE(long* p, int idx)
{
	ST_COMMON_DATABYTE* ptrBase								= (ST_COMMON_DATABYTE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_DATABYTE));
}
void OnDelSTATESET(long* p, int idx)
{
	ST_COMMON_STATESET* ptrBase								= (ST_COMMON_STATESET*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_STATESET));
}
void OnDelUNIT(long* p, int idx)
{
	ST_COMMON_UNIT* ptrBase								= (ST_COMMON_UNIT*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_UNIT));
}
void OnDelSCALEFACTOR(long* p, int idx)
{	
	ST_COMMON_SCALEFACTOR* ptrBase								= (ST_COMMON_SCALEFACTOR*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_SCALEFACTOR));
}
void OnDelLIMITCODE(long* p, int idx)
{
	ST_COMMON_LIMITCODE* ptrBase								= (ST_COMMON_LIMITCODE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_LIMITCODE));
}
void OnDelLIMITSET(long* p, int idx)
{
	ST_COMMON_LIMITSET* ptrBase								= (ST_COMMON_LIMITSET*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_LIMITSET));
}						
void OnDelEQUIPCOMPANY(long* p, int idx)
{
	ST_COMMON_EQUIPCOMPANY* ptrBase								= (ST_COMMON_EQUIPCOMPANY*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_EQUIPCOMPANY));
}					
void OnDelSUBSTATION(long* p, int idx)
{
	ST_COMMON_SUBSTATION* ptrBase								= (ST_COMMON_SUBSTATION*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_SUBSTATION));
}						
void OnDelDISTRIBUTIONLINE(long* p, int idx)
{
	ST_COMMON_DISTRIBUTIONLINE* ptrBase								= (ST_COMMON_DISTRIBUTIONLINE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_DISTRIBUTIONLINE));
}				
void OnDelBASEVOLTAGE(long* p, int idx)
{
	ST_COMMON_BASEVOLTAGE* ptrBase								= (ST_COMMON_BASEVOLTAGE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_BASEVOLTAGE));
}					
void OnDelBASEPOWER(long* p, int idx)
{
	ST_COMMON_BASEPOWER* ptrBase								= (ST_COMMON_BASEPOWER*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_BASEPOWER));
}						
void OnDelVOLTAGELEVEL(long* p, int idx)
{
	ST_COMMON_VOLTAGELEVEL* ptrBase								= (ST_COMMON_VOLTAGELEVEL*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_VOLTAGELEVEL));
}					
void OnDelPHASE(long* p, int idx)
{
	ST_COMMON_PHASE* ptrBase								= (ST_COMMON_PHASE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_PHASE));
}							
void OnDelPROTOCOLTYPE(long* p, int idx)
{
	ST_COMMON_PROTOCOLTYPE* ptrBase								= (ST_COMMON_PROTOCOLTYPE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_PROTOCOLTYPE));
}					
void OnDelEQUIPMENTTYPE(long* p, int idx)
{
	ST_COMMON_EQUIPMENTTYPE* ptrBase								= (ST_COMMON_EQUIPMENTTYPE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_EQUIPMENTTYPE));
}					
void OnDelRTUMAP(long* p, int idx)
{
	ST_COMMON_RTUMAP* ptrBase								= (ST_COMMON_RTUMAP*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_RTUMAP));
}							
void OnDelCOMMTYPE(long* p, int idx)
{
	ST_COMMON_COMMTYPE* ptrBase								= (ST_COMMON_COMMTYPE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_COMMTYPE));
}						
void OnDelRTUTYPE(long* p, int idx)
{
	ST_COMMON_RTUTYPE* ptrBase								= (ST_COMMON_RTUTYPE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_RTUTYPE));
}						
void OnDelCATEGORYCODE(long* p, int idx)
{
	ST_COMMON_CATEGORYCODE* ptrBase								= (ST_COMMON_CATEGORYCODE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_CATEGORYCODE));
}					
void OnDelMEASURETYPEINFO(long* p, int idx)
{
	ST_COMMON_MEASURETYPEINFO* ptrBase								= (ST_COMMON_MEASURETYPEINFO*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_MEASURETYPEINFO));
}				
void OnDelDNPBIMAPINDEX(long* p, int idx)
{
	ST_COMMON_DNPBIMAPINDEX* ptrBase								= (ST_COMMON_DNPBIMAPINDEX*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_DNPBIMAPINDEX));
}				
void OnDelDNPBOMAPINDEX(long* p, int idx)
{
	ST_COMMON_DNPBOMAPINDEX* ptrBase								= (ST_COMMON_DNPBOMAPINDEX*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_DNPBOMAPINDEX));
}				
void OnDelDNPAIMAPINDEX(long* p, int idx)
{
	ST_COMMON_DNPAIMAPINDEX* ptrBase								= (ST_COMMON_DNPAIMAPINDEX*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_DNPAIMAPINDEX));
}					
void OnDelDNPAOMAPINDEX(long* p, int idx)
{
	ST_COMMON_DNPAOMAPINDEX* ptrBase								= (ST_COMMON_DNPAOMAPINDEX*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_DNPAOMAPINDEX));
}					
void OnDelDNPCOUNTERMAPINDEX(long* p, int idx)
{
	ST_COMMON_DNPCOUNTERMAPINDEX* ptrBase								= (ST_COMMON_DNPCOUNTERMAPINDEX*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_DNPCOUNTERMAPINDEX));
}				

void OnDelRTUDEVICE(long* p, int idx)
{
	ST_COMMON_RTUDEVICE* ptrBase								= (ST_COMMON_RTUDEVICE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_RTUDEVICE));
}						
void OnDelCONDUCTINGEQUIPMENT(long* p, int idx)
{
	ST_COMMON_CONDUCTINGEQUIPMENT* ptrBase								= (ST_COMMON_CONDUCTINGEQUIPMENT*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_CONDUCTINGEQUIPMENT));
}			
void OnDelSWITCH(long* p, int idx)
{
	ST_COMMON_SWITCH* ptrBase								= (ST_COMMON_SWITCH*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_SWITCH));
}							
void OnDelACLINESEGMENT(long* p, int idx)
{
	ST_COMMON_ACLINESEGMENT* ptrBase								= (ST_COMMON_ACLINESEGMENT*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_ACLINESEGMENT));
}					
void OnDelPERLENGTHSEQUENCEIMPEDANCE(long* p, int idx)
{
	ST_COMMON_PERLENGTHSEQUENCEIMPEDANCE* ptrBase								= (ST_COMMON_PERLENGTHSEQUENCEIMPEDANCE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_PERLENGTHSEQUENCEIMPEDANCE));
}		
void OnDelBUSBARSECTION(long* p, int idx)
{
	ST_COMMON_BUSBARSECTION* ptrBase								= (ST_COMMON_BUSBARSECTION*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_BUSBARSECTION));
}					
void OnDelCOMPOSITESWITCH(long* p, int idx)
{
	ST_COMMON_COMPOSITESWITCH* ptrBase								= (ST_COMMON_COMPOSITESWITCH*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_COMPOSITESWITCH));
}				
void OnDelPOWERTRANSFORMER(long* p, int idx)
{
	ST_COMMON_POWERTRANSFORMER* ptrBase								= (ST_COMMON_POWERTRANSFORMER*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_POWERTRANSFORMER));
}				
void OnDelTRANSFORMERWINDING(long* p, int idx)
{
	ST_COMMON_TRANSFORMERWINDING* ptrBase								= (ST_COMMON_TRANSFORMERWINDING*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_TRANSFORMERWINDING));
}				
void OnDelTAPCHANGER(long* p, int idx)
{
	ST_COMMON_TAPCHANGER* ptrBase								= (ST_COMMON_TAPCHANGER*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_TAPCHANGER));
}						
void OnDelTAPREGULATIONSCHEDULE(long* p, int idx)
{
	ST_COMMON_TAPREGULATIONSCHEDULE* ptrBase								= (ST_COMMON_TAPREGULATIONSCHEDULE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_TAPREGULATIONSCHEDULE));
}			
void OnDelPROTECTIONEQUIPMENT(long* p, int idx)
{
	ST_COMMON_PROTECTIONEQUIPMENT* ptrBase								= (ST_COMMON_PROTECTIONEQUIPMENT*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_PROTECTIONEQUIPMENT));
}			
void OnDelRECLOSESEQUENCE(long* p, int idx)
{
	ST_COMMON_RECLOSESEQUENCE* ptrBase								= (ST_COMMON_RECLOSESEQUENCE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_RECLOSESEQUENCE));
}				
void OnDelCURRENTRELAY(long* p, int idx)
{
	ST_COMMON_CURRENTRELAY* ptrBase								= (ST_COMMON_CURRENTRELAY*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_CURRENTRELAY));
}					
void OnDelBATTERYSTORAGE(long* p, int idx)
{
	ST_COMMON_BATTERYSTORAGE* ptrBase								= (ST_COMMON_BATTERYSTORAGE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_BATTERYSTORAGE));
}					
void OnDelGENERATINGUNIT(long* p, int idx)
{
	ST_COMMON_GENERATINGUNIT* ptrBase								= (ST_COMMON_GENERATINGUNIT*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_GENERATINGUNIT));
}					
void OnDelGENREGULATIONSCHEDULE(long* p, int idx)
{
	ST_COMMON_GENREGULATIONSCHEDULE* ptrBase								= (ST_COMMON_GENREGULATIONSCHEDULE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_GENREGULATIONSCHEDULE));
}			
void OnDelWINDTURBINE(long* p, int idx)
{
	ST_COMMON_WINDTURBINE* ptrBase								= (ST_COMMON_WINDTURBINE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_WINDTURBINE));
}					
void OnDelPHOTOVOLTAIC(long* p, int idx)
{
	ST_COMMON_PHOTOVOLTAIC* ptrBase								= (ST_COMMON_PHOTOVOLTAIC*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_PHOTOVOLTAIC));
}					
void OnDelGENUNITOPCOSTCURVE(long* p, int idx)
{
	ST_COMMON_GENUNITOPCOSTCURVE* ptrBase								= (ST_COMMON_GENUNITOPCOSTCURVE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_IDENTIFIEDOBJECT));
}				
void OnDelENERGYCONSUMER(long* p, int idx)
{
	ST_COMMON_ENERGYCONSUMER* ptrBase								= (ST_COMMON_ENERGYCONSUMER*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_ENERGYCONSUMER));
}					
void OnDelSHUNTCOMPASATOR(long* p, int idx)
{
	ST_COMMON_SHUNTCOMPASATOR* ptrBase								= (ST_COMMON_SHUNTCOMPASATOR*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_SHUNTCOMPASATOR));
}				
void OnDelSTATICVARCOMPENSATOR(long* p, int idx)
{
	ST_COMMON_STATICVARCOMPENSATOR* ptrBase								= (ST_COMMON_STATICVARCOMPENSATOR*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_STATICVARCOMPENSATOR));
}			
void OnDelPOWERSYSTEMRESOURCE(long* p, int idx)
{
	ST_COMMON_POWERSYSTEMRESOURCE* ptrBase								= (ST_COMMON_POWERSYSTEMRESOURCE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_POWERSYSTEMRESOURCE));
}			
void OnDelPSRTYPE(long* p, int idx)
{
	ST_COMMON_PSRTYPE* ptrBase								= (ST_COMMON_PSRTYPE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_PSRTYPE));
}						
void OnDelEQUIPMENTCONTAINER(long* p, int idx)
{
	ST_COMMON_EQUIPMENTCONTAINER* ptrBase								= (ST_COMMON_EQUIPMENTCONTAINER*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_EQUIPMENTCONTAINER));
}				
void OnDelSYMBOL(long* p, int idx)
{
	ST_COMMON_SYMBOL* ptrBase								= (ST_COMMON_SYMBOL*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_SYMBOL));
}							
void OnDelDASDIAGRAMINFO(long* p, int idx)
{
	ST_COMMON_DASDIAGRAMINFO* ptrBase								= (ST_COMMON_DASDIAGRAMINFO*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_DASDIAGRAMINFO));
}					
void OnDelSTATIONDIAGRAMINFO(long* p, int idx)
{
	ST_COMMON_STATIONDIAGRAMINFO* ptrBase								= (ST_COMMON_STATIONDIAGRAMINFO*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_STATIONDIAGRAMINFO));
}				

void OnDelDISCRETE(long* p, int idx)
{
	ST_COMMON_DISCRETE* ptrBase								= (ST_COMMON_DISCRETE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_DISCRETE));
}						
void OnDelSETDISCRETE(long* p, int idx)
{
	ST_COMMON_SETDISCRETE* ptrBase								= (ST_COMMON_SETDISCRETE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_SETDISCRETE));
}					
void OnDelMEASUREMENT(long* p, int idx)
{
	ST_COMMON_MEASUREMENT* ptrBase								= (ST_COMMON_MEASUREMENT*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_MEASUREMENT));
}					
void OnDelSETMEASUREMENT(long* p, int idx)
{
	ST_COMMON_SETMEASUREMENT* ptrBase								= (ST_COMMON_SETMEASUREMENT*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_SETMEASUREMENT));
}					
void OnDelACCUMULATOR(long* p, int idx)
{
	ST_COMMON_ACCUMULATOR* ptrBase								= (ST_COMMON_ACCUMULATOR*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_ACCUMULATOR));
}					
void OnDelCALCULATION(long* p, int idx)
{
	ST_COMMON_CALCULATION* ptrBase								= (ST_COMMON_CALCULATION*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_CALCULATION));
}

void OnDelPOSITION(long* p, int idx)
{
	ST_COMMON_POSITION* ptrBase								= (ST_COMMON_POSITION*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_POSITION));
}						

void OnDelWATER(long* p, int idx)
{
	ST_COMMON_WATER* ptrBase								= (ST_COMMON_WATER*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_WATER));
}

void OnDelACM_APPGROUP(long* p, int idx)
{
	ST_COMMON_ACM_APPGROUP* ptrBase							= (ST_COMMON_ACM_APPGROUP*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_ACM_APPGROUP));
}

void OnDelACM_MAPINDEX(long* p, int idx)
{
	ST_COMMON_ACM_MAPINDEX* ptrBase							= (ST_COMMON_ACM_MAPINDEX*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_ACM_MAPINDEX));
}

void OnDelACM_TABLE(long* p, int idx)
{
	ST_COMMON_ACM_TABLE* ptrBase							= (ST_COMMON_ACM_TABLE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_ACM_TABLE));
}

void OnDelACM_TABLEGROUP(long* p, int idx)
{
	ST_COMMON_ACM_TABLEGROUP* ptrBase						= (ST_COMMON_ACM_TABLEGROUP*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_ACM_TABLEGROUP));
}

void OnDelPCS(long* p, int idx)
{
	ST_COMMON_PCS* ptrBase = (ST_COMMON_PCS*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_PCS));
}

void OnDelMAINTRANSFORMER(long* p, int idx)
{
	ST_COMMON_MAINTRANSFORMER* ptrBase = (ST_COMMON_MAINTRANSFORMER*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_MAINTRANSFORMER));
}

void OnDelVIRTUAL_LINE(long* p, int idx)
{
	ST_COMMON_VIRTUAL_LINE* ptrBase								= (ST_COMMON_VIRTUAL_LINE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_COMMON_VIRTUAL_LINE));
}	

void OnDelMEMO(long* p, int idx)
{
	ST_OPR_MEMO* ptrBase								= (ST_OPR_MEMO*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_OPR_MEMO));
}							
void OnDelMESSAGE(long* p, int idx)
{
	ST_OPR_MESSAGE* ptrBase								= (ST_OPR_MESSAGE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_OPR_MESSAGE));
}						
void OnDelCONSTRUCTION(long* p, int idx)
{
	ST_OPR_CONSTRUCTION* ptrBase								= (ST_OPR_CONSTRUCTION*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_OPR_CONSTRUCTION));
}					
void OnDelOPERATORASSIGN(long* p, int idx)
{
	ST_OPR_OPERATORASSIGN* ptrBase								= (ST_OPR_OPERATORASSIGN*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_OPR_OPERATORASSIGN));
}					
void OnDelWAVE_LIST(long* p, int idx)
{
	ST_OPR_WAVE_LIST* ptrBase								= (ST_OPR_WAVE_LIST*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_OPR_WAVE_LIST));
}					
void OnDelWAVE_FILE(long* p, int idx)
{
	ST_OPR_WAVE_FILE* ptrBase								= (ST_OPR_WAVE_FILE*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_OPR_WAVE_FILE));
}	

void OnDelCOMPUTERSTATUS(long* p, int idx)
{
	ST_OPR_COMPUTERSTATUS* ptrBase								= (ST_OPR_COMPUTERSTATUS*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_OPR_COMPUTERSTATUS));
}					
void OnDelCALCULATION_RESULT(long* p, int idx)
{
	ST_OPR_CALCULATION_RESULT* ptrBase							= (ST_OPR_CALCULATION_RESULT*)(*p);
	
	memset(&ptrBase[idx], 0, sizeof(ST_OPR_CALCULATION_RESULT));
}	

#endif//__DATACopy_H__
