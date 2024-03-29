
#include "StdAfx.h"
#include "RDBMgr.h"

enum MIDAS_NUM
{
	MIDAS_COMMON_START = 0,
	MIDAS_OPR_START    = 80,	// OPR DB의 시작점
};

TCHAR* _tTableName[] = 
{	
	FILE_IDENTIFIEDOBJECT				,
	FILE_GEOGRAPHICALREGION				,
	FILE_SUBGEOGRAPHICALREGION			,
	FILE_DATAPOINTGROUPCODE				,
	FILE_COMPUTERCODE					,
	FILE_PROGRAMCODE					,
	FILE_OPERATORCODE					,
	FILE_SWITCHTYPECODE					,
	FILE_CONSTRUCTIONCODE				,
	FILE_WAVECOMTYPE					,
	FILE_STATEGROUP						,
	FILE_DATABYTE						,
	FILE_STATESET						,
	FILE_UNIT							,
	FILE_SCALEFACTOR					,
	FILE_LIMITCODE						,
	FILE_LIMITSET						,
	FILE_EQUIPCOMPANY					,
	FILE_SUBSTATION						,
	FILE_DISTRIBUTIONLINE				,
	FILE_BASEVOLTAGE					,
	FILE_BASEPOWER						,
	FILE_VOLTAGELEVEL					,
	FILE_PHASE							,
	FILE_PROTOCOLTYPE					,
	FILE_EQUIPMENTTYPE					,
	FILE_RTUMAP							,
	FILE_COMMTYPE						,
	FILE_RTUTYPE						,
	FILE_CATEGORYCODE					,
	FILE_MEASURETYPEINFO				,
	FILE_DNPBIMAPINDEX					,
	FILE_DNPBOMAPINDEX					,
	FILE_DNPAIMAPINDEX					,
	FILE_DNPAOMAPINDEX					,
	FILE_DNPCOUNTERMAPINDEX				,
	FILE_RTUDEVICE						,
	FILE_CONDUCTINGEQUIPMENT			,
	FILE_SWITCH							,
	FILE_ACLINESEGMENT					,
	FILE_PERLENGTHSEQUENCEIMPEDANCE		,
	FILE_BUSBARSECTION					,
	FILE_COMPOSITESWITCH				,
	FILE_POWERTRANSFORMER				,
	FILE_TRANSFORMERWINDING				,
	FILE_TAPCHANGER						,
	FILE_TAPREGULATIONSCHEDULE			,
	FILE_PROTECTIONEQUIPMENT			,
	FILE_RECLOSESEQUENCE				,
	FILE_CURRENTRELAY					,
	FILE_BATTERYSTORAGE					,
	FILE_GENERATINGUNIT					,
	FILE_GENREGULATIONSCHEDULE			,
	FILE_WINDTURBINE					,
	FILE_PHOTOVOLTAIC					,
	FILE_GENUNITOPCOSTCURVE				,
	FILE_ENERGYCONSUMER					,
	FILE_SHUNTCOMPASATOR				,
	FILE_STATICVARCOMPENSATOR			,
	FILE_POWERSYSTEMRESOURCE			,
	FILE_PSRTYPE						,
	FILE_EQUIPMENTCONTAINER				,
	FILE_SYMBOL							,
	FILE_DASDIAGRAMINFO					,
	FILE_STATIONDIAGRAMINFO				,
	FILE_DISCRETE						,
	FILE_SETDISCRETE					,
	FILE_MEASUREMENT					,
	FILE_SETMEASUREMENT					,
	FILE_ACCUMULATOR					,
	FILE_CALCULATION					,
	FILE_POSITION						,
	FILE_WATER							,
	FILE_ACM_APPGROUP					,
	FILE_ACM_MAPINDEX					,
	FILE_ACM_TABLE						,
	FILE_ACM_TABLEGROUP					,
	FILE_PCS							,
	FILE_MAINTRANSFORMER				,
	FILE_VIRTUAL_LINE					,

	FILE_MEMO							,	//midas_opr 시작
	FILE_MESSAGE						,
	FILE_CONSTRUCTION					,
	FILE_OPERATORASSIGN					,
	FILE_WAVE_LIST						,
	FILE_WAVE_FILE						,
	FILE_COMPUTERSTATUS					,
	FILE_CALCULATION_RESULT				,
};

INT CRDBMgr::GetRDBFileListCount(TCHAR* pszFileName)
{
	INT iCnt = HMISHARE_GET_RDBRECORDCOUNT(pszFileName);
	return iCnt;
}


////////////////////////////////////////////////////////////////////////////////////////////
//// 계통도에 입력되어야 할 설비 정보 취득 ////////////////////////////////////////////////////
//// 단일회로, 분산전원 설비의 포인트 추출 CEQ -> RTU Device -> RTUMap -> DNP_BI,DNP_AI,.....
BOOL CRDBMgr::GetCondectionEquipData(int nIndex, BLOCKVIEWDATA* pdata)
{
	BOOL ret = FALSE;

	LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetEquip(nIndex); //인덱스 아님 루프로 찾음
	if(!pequip || pequip->CEQID == 0) return ret; // 14, 15번 TDAS 데이터만 취득

	LPST_COMMON_POWERSYSTEMRESOURCE pPsr = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetIndexPSR(pequip->PSRFK);
	if(!pPsr) return ret;

	if(pequip->DpGrpFK > 0)
	{
		LPST_COMMON_DATAPOINTGROUPCODE pDpGrp = (LPST_COMMON_DATAPOINTGROUPCODE)CRDBMgr::GetIndexDpGrp(pequip->DpGrpFK);
		if(!pDpGrp) return ret;

		pdata->DPCODE   = pequip->DpGrpFK;
		_tcscpy_s(pdata->DPName, pDpGrp->DpGrpName);
	}

	//공통입력 부분
	pdata->PSRTYFK	= pPsr->PSRTYPEFK;				//PSR 타입 
	pdata->CEQID	= pequip->CEQID;				//CEQID
	pdata->DLFK		= pequip->DLFK;					//소속 DL
	pdata->RUID		= pequip->RUID;					//RTU Device ID


	pdata->switchType = 0;

	const int iSwitch = CRDBMgr::GetRDBFileListCount(FILE_SWITCH);
	for(int isw = 1; isw <= iSwitch; isw++)
	{
		LPST_COMMON_SWITCH pSw = (LPST_COMMON_SWITCH)CRDBMgr::GetSwitch(isw);
		if(pSw->CEQFK == pdata->CEQID)
		{
			pdata->switchType = pSw->SwitchType;
			pdata->datad[0].data = pSw->normalOpen;
			ret = TRUE;
			break;
		}
	}

	if(pdata->RUID > 0)
	{
		LPST_COMMON_RTUDEVICE pDevice = (LPST_COMMON_RTUDEVICE)CRDBMgr::GetIndexRTUDevice(pequip->RUID);
		if(!pDevice) return ret;

		LPST_COMMON_RTUMAP pMap = (LPST_COMMON_RTUMAP)CRDBMgr::GetIndexRTUMap(pDevice->RTUMapId);// => 맵의 타입과 종류 확인일때만 필요
		if(!pMap) return ret;

		//pdata->out_dl = pequip->link_dl_fk;			//연계 DL
		pdata->RTUType	= pMap->RTUTypeId;				//자수동 구분
		pdata->RTUMapId  = pMap->RTUMapId;				//RTUMAP ID
		//비도, 암자, 장하 OCB의 AI 데이터는 PQ 메터 데이터로 전부 교체 2014-10-30 하드코딩
		//////////////////////////////////////////////////////////////////////////////
		//2015-06-24 TDAS TO CIM DB로 변경되어 PQ메터 CEQ 변경됨 PQ암자-709, PQ비도-710, PQ장하-711, PQ신안파워-712, PQ해아름-713
		int nEqualCEQ = 0;
		if(pdata->CEQID == 26 || pdata->CEQID == 36 || pdata->CEQID == 39)
		{
			switch(pdata->CEQID)
			{
			case 26: //암자PQ
				nEqualCEQ = 709;
				break;
			case 36: //비도PQ
				nEqualCEQ =710;
				break;
			case 39: //장하PQ
				nEqualCEQ = 711;
				break;
			}

			LPST_COMMON_CONDUCTINGEQUIPMENT pPQ = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(nEqualCEQ); 
			if(!pPQ || pPQ->CEQID == 0) return ret; 

			// ai point => DNP_AI로 변경
			const int imeasure = CRDBMgr::GetRDBFileListCount(FILE_MEASUREMENT);
			for(int ian = 1; ian <= imeasure; ian++)
			{			
				LPST_COMMON_MEASUREMENT pMeasure = (LPST_COMMON_MEASUREMENT)CRDBMgr::GetMesurement(ian);
				if(!pMeasure->MeasureTypeID)
				{
					continue;
				}

				if(aPsrType[pdata->PSRTYFK] == 8)	/* 분산전원 */
				{
					if(pMeasure->CEQId == pPQ->CEQID && aRDBDataPoint[pMeasure->MeasureTypeID][8] > -1 && aRDBDataPoint[pMeasure->MeasureTypeID][0] == 3) //타입이 아날로그 인 것
					{
						pdata->data[aRDBDataPoint[pMeasure->MeasureTypeID][8]].pointid = pMeasure->PID;
						pdata->data[aRDBDataPoint[pMeasure->MeasureTypeID][8]].data = 0;
					}
				}
				else		/* 그외 */
				{
					if(pMeasure->CEQId == pPQ->CEQID && aRDBDataPoint[pMeasure->MeasureTypeID][2] > -1 && aRDBDataPoint[pMeasure->MeasureTypeID][0] == 3)
					{
						pdata->data[aRDBDataPoint[pMeasure->MeasureTypeID][2]].pointid = pMeasure->PID;
						pdata->data[aRDBDataPoint[pMeasure->MeasureTypeID][2]].data = 0;
					}
				}
			}

		}
		else
		{
			// ai point
			const int imeasure = CRDBMgr::GetRDBFileListCount(FILE_MEASUREMENT);
			for(int ian = 1; ian <= imeasure; ian++)
			{			
				LPST_COMMON_MEASUREMENT pMeasure = (LPST_COMMON_MEASUREMENT)CRDBMgr::GetMesurement(ian);
				if(!pMeasure->MeasureTypeID)
				{
					//ASSERT(FALSE);
					//break;

					//TCHAR buf[1024] = {0,};
					//wchar_t dwChar[1024] = {0,};
					//MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pre->name,-1, dwChar, 1024);
					//_stprintf(buf, GetLangString(LANG_MSG_00448), dwChar, pre->eq_fk,  ian); //%s(%d) 설비의 AI 포인트 %d이 존재하지 않습니다
					//AfxMessageBox(buf);
					continue;

				}

				if(aPsrType[pdata->PSRTYFK] == 8)	/* 분산전원 - BESS1, 2, L-MG-EMS */ 
				{
					// 회로를 구분할 수 없어 하드코딩
					//!< 0 : 유효, 1 : 무효, 2: rms a.b.c, 5 : rms r.s.t, 8 : 부하  9 : Phase a.b.c 12:Phse r.s.t 15: PF a.b.c 18:I a.b.c.n 22:유효 a.b.c 25:무효 a.b.c
					if(pdata->CEQID == 672 && pdata->RUID == pMeasure->RUID ) //비금신안풍력(ESS1)
					{
						switch(pMeasure->Position)
						{
						case 29:  // PCS1 PCS주입 유효전력
							pdata->data[0].pointid = pMeasure->PID;
							pdata->data[0].data = 0;
							break;
						case 30: // PCS1 PCS주입 무효전력
							pdata->data[1].pointid = pMeasure->PID;
							pdata->data[1].data = 0;
							break;
						case 34: // 계통전압(R상)
							pdata->data[2].pointid = pMeasure->PID;
							pdata->data[2].data = 0;
							break;
						case 35: // 계통전압(S상)
							pdata->data[3].pointid = pMeasure->PID;
							pdata->data[3].data = 0;
							break;
						case 36: // 계통전압(T상)
							pdata->data[4].pointid = pMeasure->PID;
							pdata->data[4].data = 0;
							break;
						case 26: // PCS1 PCS 전류(R상)
							pdata->data[18].pointid = pMeasure->PID;
							pdata->data[18].data = 0;
							break;
						case 27: // PCS1 PCS 전류(S상)
							pdata->data[19].pointid = pMeasure->PID;
							pdata->data[19].data = 0;
							break;
						case 28: // PCS1 PCS 전류(T상)
							pdata->data[20].pointid = pMeasure->PID;
							pdata->data[20].data = 0;
							break;
						}
					}
				}
				else if(aPsrType[pdata->PSRTYFK] == 15 )	/* STATCOM1,2 */
				{
					// 회로를 구분할 수 없어 하드코딩
					//!< 0 : 유효, 1 : 무효, 2: rms a.b.c, 5 : rms r.s.t, 8 : 부하  9 : Phase a.b.c 12:Phse r.s.t 15: PF a.b.c 18:I a.b.c.n 22:유효 a.b.c 25:무효 a.b.c
					if(pdata->CEQID == 670 && pdata->RUID == pMeasure->RUID ) //비금신안풍력(STATCOM1)
					{
						switch(pMeasure->Position)
						{
						case 9:  // 계통주입 유효전력
							pdata->data[0].pointid = pMeasure->PID;
							pdata->data[0].data = 0;
							break;
						case 24: // STC1 STATCOM 계통주입 무효전력
							pdata->data[1].pointid = pMeasure->PID;
							pdata->data[1].data = 0;
							break;
						case 12: // 계통전압(R상)
							pdata->data[2].pointid = pMeasure->PID;
							pdata->data[2].data = 0;
							break;
						case 13: // 계통전압(S상)
							pdata->data[3].pointid = pMeasure->PID;
							pdata->data[3].data = 0;
							break;
						case 14: // 계통전압(T상)
							pdata->data[4].pointid = pMeasure->PID;
							pdata->data[4].data = 0;
							break;
						case 21: // STC1 STATCOM 전류(R상)
							pdata->data[18].pointid = pMeasure->PID;
							pdata->data[18].data = 0;
							break;
						case 22: // STC1 STATCOM 전류(S상)
							pdata->data[19].pointid = pMeasure->PID;
							pdata->data[19].data = 0;
							break;
						case 23: // STC1 STATCOM 전류(T상)
							pdata->data[20].pointid = pMeasure->PID;
							pdata->data[20].data = 0;
							break;
						}
					}
					else if( pdata->CEQID == 671 && pdata->RUID == pMeasure->RUID ) //비금신안풍력(STATCOM2)
					{
						switch(pMeasure->Position)
						{
						case 9:  // 계통주입 유효전력
							pdata->data[0].pointid = pMeasure->PID;
							pdata->data[0].data = 0;
							break;
						case 29: // STC2 STATCOM 계통주입 무효전력
							pdata->data[1].pointid = pMeasure->PID;
							pdata->data[1].data = 0;
							break;
						case 12: // 계통전압(R상)
							pdata->data[2].pointid = pMeasure->PID;
							pdata->data[2].data = 0;
							break;
						case 13: // 계통전압(S상)
							pdata->data[3].pointid = pMeasure->PID;
							pdata->data[3].data = 0;
							break;
						case 14: // 계통전압(T상)
							pdata->data[4].pointid = pMeasure->PID;
							pdata->data[4].data = 0;
							break;
						case 26: // STC2 STATCOM 전류(R상)
							pdata->data[18].pointid = pMeasure->PID;
							pdata->data[18].data = 0;
							break;
						case 27: // STC2 STATCOM 전류(S상)
							pdata->data[19].pointid = pMeasure->PID;
							pdata->data[19].data = 0;
							break;
						case 28: // STC2 STATCOM 전류(T상)
							pdata->data[20].pointid = pMeasure->PID;
							pdata->data[20].data = 0;
							break;
						}
					}
				}
				else		/* 그외 */
				{
					if(pMeasure->CEQId == pequip->CEQID && aRDBDataPoint[pMeasure->MeasureTypeID][2] > -1 && aRDBDataPoint[pMeasure->MeasureTypeID][0] == 3)
					{
						pdata->data[aRDBDataPoint[pMeasure->MeasureTypeID][2]].pointid =pMeasure->PID;
						pdata->data[aRDBDataPoint[pMeasure->MeasureTypeID][2]].data = 0;
					}
				}
			}
		}

		//bi point scan
		const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_DISCRETE);
		for(int idi = 1; idi <= iTotal; idi++)
		{
			LPST_COMMON_DISCRETE pdigi = (LPST_COMMON_DISCRETE)CRDBMgr::GetDiscrete(idi);
			
			if(pdigi->CEQId == pequip->CEQID && aRDBDataPoint[pdigi->MeasureTypeID][2] > -1 && aRDBDataPoint[pdigi->MeasureTypeID][0] == 1) // Measure type 테이블에 BI인 것
			{
				pdata->datad[aRDBDataPoint[pdigi->MeasureTypeID][2]].pointid = pdigi->PID;
				pdata->datad[aRDBDataPoint[pdigi->MeasureTypeID][2]].abnormal = pdigi->AbnormalVal;

				pdata->datad[aRDBDataPoint[pdigi->MeasureTypeID][2]].stateGrpId = pdigi->StateGrpId;

				//if(aRDBDataPoint[pdigi->MeasureTypeID][2] == 0)
				//	pdata->datad[aRDBDataPoint[pdigi->MeasureTypeID][2]].data = pdigi->Initval; // !pdigi->value;
				//else
				//	pdata->datad[aRDBDataPoint[pdigi->MeasureTypeID][2]].data = 0;
			}
		} 
	}
	//SE, PF  Scan
	//if(pequip->DPGC_ACMFK > 0)
	//{
	//	const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_ACM_MAPINDEX);
	//	for(int idx = 1; idx <= iTotal; idx++)
	//	{
	//		LPST_COMMON_ACM_MAPINDEX pAcm = (LPST_COMMON_ACM_MAPINDEX)CRDBMgr::GetIndexAcmMapIndex(idx);
	//		if(pAcm->DPGC_ACMFK == pequip->DPGC_ACMFK)
	//		{
	//			if(pAcm->Position > -1 && pAcm->Position < 15) //SE
	//			{
	//				_tcscpy_s(pdata->acmSedata[pAcm->Position].upcName, pAcm->upc_name);
	//				_tcscpy_s(pdata->acmSedata[pAcm->Position].Name, pAcm->Name);
	//				pdata->acmSedata[pAcm->Position].Index = pAcm->Position;
	//				pdata->acmSedata[pAcm->Position].data = 0;
	//			}
	//			else if(pAcm->Position > 15 && pAcm->Position < 32) //PF
	//			{
	//				_tcscpy_s(pdata->acmPfdata[pAcm->Position].upcName, pAcm->upc_name);
	//				_tcscpy_s(pdata->acmPfdata[pAcm->Position].Name, pAcm->Name);
	//				pdata->acmPfdata[pAcm->Position].Index = pAcm->Position;
	//				pdata->acmPfdata[pAcm->Position].data = 0;
	//			}
	//		}
	//	}
	//}

	// name, aliasname
	switch(aPsrType[pdata->PSRTYFK])
	{
	case 3:  //다회로
	case 11: //ALTS
		{
			const int ncps = GetRDBFileListCount(FILE_COMPOSITESWITCH);			// compositeswitch 카운터

			for(int icnt = 1; icnt <= ncps; icnt++)
			{
				LPST_COMMON_COMPOSITESWITCH cps = (LPST_COMMON_COMPOSITESWITCH)CRDBMgr::GetComposite(icnt);

				if(cps->EQCFK == pequip->EQCFK)
				{
					pdata->ppid = cps->CPSID;
					_tcscpy_s(pdata->Name, cps->Name);
					ret = TRUE;
					break;
				}
			}
		}
		break;

	case 7:
		{
			const int ndls = GetRDBFileListCount(FILE_ACLINESEGMENT);			// 구간 카운터

			for(int icnt = 1; icnt <= ndls; icnt++)
			{
				LPST_COMMON_ACLINESEGMENT dls = (LPST_COMMON_ACLINESEGMENT)CRDBMgr::GetAcLine(icnt);
				LPST_COMMON_UNIT psyle = (LPST_COMMON_UNIT)CRDBMgr::GetUnit(dls->length_usfk);
				//LPST_COMMON_UNIT lsyle = (LPST_COMMON_UNIT)CRDBMgr::GetUnit(dls->secload_us_fk);//부하표시 없음
				if(dls->CEQFK == pequip->CEQID)
				{
					_tcscpy_s(pdata->Name, dls->Name);

					pdata->DLFK = pequip->DLFK;
					pdata->line = dls->length;						// 선로길이
					//pdata->secload = dls->secload;					// 부하

					_tcscpy_s(pdata->linename, psyle->UnitName);		// 선로길이단위
					//strcpy_s(pdata->loadname, lsyle->name);		// 부하 단위
					ret = true;
					break;
				}
			}
		}
		break;
	case 6: //고압수용가
		_tcscpy_s(pdata->Name, pequip->Name);
		ret = TRUE;
		break;
	case 19: //SVC - 변압기 결선
		{
			// ai point
			if(pdata->RUID == 0)
				break;
			const int imeasure = CRDBMgr::GetRDBFileListCount(FILE_MEASUREMENT);
			for(int ian = 1; ian <= imeasure; ian++)
			{			
				LPST_COMMON_MEASUREMENT pMeasure = (LPST_COMMON_MEASUREMENT)CRDBMgr::GetMesurement(ian);
				if(!pMeasure->MeasureTypeID)
				{
					continue;
				}

				/* 탭위치, 전원전압, 부하전압 */
				if(pdata->CEQID == pMeasure->CEQId && aRDBDataPoint[pMeasure->MeasureTypeID][2] >= 0 && aRDBDataPoint[pMeasure->MeasureTypeID][2] < 15)
				{
					pdata->svrData[aRDBDataPoint[pMeasure->MeasureTypeID][2]].pointid = pMeasure->PID;
				}

			}
			ret = TRUE;
		}
		break;
	case 16: //SC
			_tcscpy_s(pdata->Name, pequip->Name);
			ret = TRUE;
		break;
	default:
			_tcscpy_s(pdata->Name, pequip->Name);
			ret = TRUE;
		break;
	}

	return ret;
}
////////////////////////////////////////////////////////////////////////////////////////////
//// 변전소단선도에 입력되어야 할 설비 정보 취득 
//// MTRCB, SectionCB, TieCB, OCB의 데이터 취득 후 맵핑
//// MTRCB의 포인트는 MTR, MTR단로기, SectionCB, SectionCB단로기 상태정보를 포함
//// TieCB의 포인트는 Tie 단로기 상태정보를 포함
//// OCB의 포인트는 OCB 단로기 상태정보를 포함
//// 부스바 상태 정보는 ACM에서 표시
//// OCB에는 PQ 정보를 표시
//////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CRDBMgr::GetCondectionEquipSubData(int nIndex, BLOCKSUBDATA* pdata)
{
	BOOL ret = FALSE;

	LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetEquip(nIndex); //인덱스 아님 루프로 찾음
	if(!pequip || pequip->CEQID == 0) return ret;

	LPST_COMMON_POWERSYSTEMRESOURCE pPsr = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetIndexPSR(pequip->PSRFK);
	if(!pPsr) return ret;

	///변전소 내부 설비인 것만 취득
	/// PSRTYPE 14:모선 37-41 :CB, 92:PQ메터  57: 단로기 8 : MTR
	if(pPsr->PSRTYPEFK != 14 && (pPsr->PSRTYPEFK < 37 || pPsr->PSRTYPEFK > 41) && pPsr->PSRTYPEFK != 92 && pPsr->PSRTYPEFK != 57 && pPsr->PSRTYPEFK != 8)
		return ret;

	if(pequip->DpGrpFK > 0)
	{
		LPST_COMMON_DATAPOINTGROUPCODE pDpGrp = (LPST_COMMON_DATAPOINTGROUPCODE)CRDBMgr::GetIndexDpGrp(pequip->DpGrpFK);
		if(!pDpGrp) return ret;

		pdata->DPCODE   = pequip->DpGrpFK;
		_tcscpy_s(pdata->DPName, pDpGrp->DpGrpName);
	}

	//공통입력 부분
	pdata->PSRTYFK	= pPsr->PSRTYPEFK;				//PSR 타입 
	pdata->CEQID	= pequip->CEQID;				//CEQID
	pdata->DLFK		= pequip->DLFK;					//소속 DL
	pdata->RUID		= pequip->RUID;					//RTU Device ID
	pdata->switchType = 0;

	const int iSwitch = CRDBMgr::GetRDBFileListCount(FILE_SWITCH);
	for(int isw = 1; isw <= iSwitch; isw++)
	{
		LPST_COMMON_SWITCH pSw = (LPST_COMMON_SWITCH)CRDBMgr::GetSwitch(isw);
		if(pSw->CEQFK == pdata->CEQID)
		{
			pdata->switchType = pSw->SwitchType;
			ret = TRUE;
			_tcscpy_s(pdata->Name, pSw->Switch_no);
			break;
		}
	}
	//모선 과 PQ메터
	if(pPsr->PSRTYPEFK == 14 || pPsr->PSRTYPEFK == 92 )
		ret = TRUE;
	if(pdata->RUID > 0)
	{
		LPST_COMMON_RTUDEVICE pDevice = (LPST_COMMON_RTUDEVICE)CRDBMgr::GetIndexRTUDevice(pequip->RUID);
		if(!pDevice) return ret;

		LPST_COMMON_RTUMAP pMap = (LPST_COMMON_RTUMAP)CRDBMgr::GetIndexRTUMap(pDevice->RTUMapId);// => 맵의 타입과 종류 확인일때만 필요
		if(!pMap) return ret;

		pdata->RTUType	= pMap->RTUTypeId;				//자수동 구분

		// ai point
		const int imeasure = CRDBMgr::GetRDBFileListCount(FILE_MEASUREMENT);
		for(int ian = 1; ian <= imeasure; ian++)
		{			
			LPST_COMMON_MEASUREMENT pMeasure = (LPST_COMMON_MEASUREMENT)CRDBMgr::GetMesurement(ian);
			if(!pMeasure->MeasureTypeID)
			{
				continue;
			}

			if(pMeasure->CEQId == pequip->CEQID && pMeasure->Position < _MAX_SUB_DATA_ && (pdata->PSRTYFK == 37 || pdata->PSRTYFK == 40 || pdata->PSRTYFK == 41 || pdata->PSRTYFK == 48 || pdata->PSRTYFK == 92))
			{
				pdata->measurement[pMeasure->Position].pointId = pMeasure->PID;
				_tcscpy_s(pdata->measurement[pMeasure->Position].Name, pMeasure->Name);
				//pdata->measurement[pMeasure->Position].upcName;
				pdata->measurement[pMeasure->Position].data = 0;
			}

		}

		//bi point scan
		const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_DISCRETE);
		for(int idi = 1; idi <= iTotal; idi++)
		{
			LPST_COMMON_DISCRETE pdigi = (LPST_COMMON_DISCRETE)CRDBMgr::GetDiscrete(idi);
			if(!pdigi)
				continue;
			if(pdigi->CEQId == pequip->CEQID && pdigi->Position < _MAX_SUB_DATA_&& (pdata->PSRTYFK == 37 || pdata->PSRTYFK == 40 || pdata->PSRTYFK == 41 || pdata->PSRTYFK == 48))
			{
				pdata->discrete[pdigi->Position].pointId = pdigi->PID;
				_tcscpy_s(pdata->discrete[pdigi->Position].Name, pdigi->Name);
				//pdata->discrete[pdigi->Position].upcName;
				pdata->discrete[pdigi->Position].data = 0;	
				pdata->discrete[pdigi->Position].stateGrpId = pdigi->StateGrpId;
				LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pdigi->StateGrpId);
				const int istateSet = GetRDBFileListCount(FILE_STATESET);
				for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
				{
					LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
					if(pSet->StateGrpId == pdigi->StateGrpId)
					{

						_tcscpy(pdata->discrete[pdigi->Position].PtName[pSet->Value], pSet->Name);
					}
				}				
			}
		} 
	}
	//설비명을 SW명으로 변경
	//_tcscpy_s(pdata->Name, pequip->Name);

	return ret;
}
////////////////////////////////////////////////////////////////////////////////////////////
//// 태양광 발전 화면에 필요한 데이터 취득
//////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CRDBMgr::GetCondectionEquipPVData(int nIndex, BLOCKPVDATA* pdata)
{
	LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(nIndex);
	if(!pequip) return FALSE;

	LPST_COMMON_POWERSYSTEMRESOURCE pPsr = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetIndexPSR(pequip->PSRFK);
	if(!pPsr) return FALSE;

	if(pequip->DpGrpFK > 0)
	{
		LPST_COMMON_DATAPOINTGROUPCODE pDpGrp = (LPST_COMMON_DATAPOINTGROUPCODE)CRDBMgr::GetIndexDpGrp(pequip->DpGrpFK);
		if(!pDpGrp) return FALSE;

		pdata->DPCODE   = pequip->DpGrpFK;
		_tcscpy_s(pdata->DPName, pDpGrp->DpGrpName);
	}

	//공통입력 부분
	pdata->PSRTYFK	= pPsr->PSRTYPEFK;				//PSR 타입 
	pdata->CEQID	= pequip->CEQID;				//CEQID
	pdata->DLFK		= pequip->DLFK;					//소속 DL
	pdata->RUID		= pequip->RUID;					//RTU Device ID
	pdata->switchType = 0;

	if(pdata->RUID > 0)
	{
		LPST_COMMON_RTUDEVICE pDevice = (LPST_COMMON_RTUDEVICE)CRDBMgr::GetIndexRTUDevice(pequip->RUID);
		if(!pDevice) return FALSE;

		LPST_COMMON_RTUMAP pMap = (LPST_COMMON_RTUMAP)CRDBMgr::GetIndexRTUMap(pDevice->RTUMapId);// => 맵의 타입과 종류 확인일때만 필요
		if(!pMap) return FALSE;

		pdata->RTUType	= pMap->RTUTypeId;				//자수동 구분
		pdata->MapID	= pDevice->RTUMapId;
		// ai point
		const int imeasure = CRDBMgr::GetRDBFileListCount(FILE_DNPAIMAPINDEX);
		for(int ian = 1; ian <= imeasure; ian++)
		{			
			LPST_COMMON_DNPAIMAPINDEX pDnpAI = (LPST_COMMON_DNPAIMAPINDEX)CRDBMgr::GetDnpAI(ian);
			LPST_COMMON_UNIT		  pUnit = (LPST_COMMON_UNIT)CRDBMgr::GetIndexUnit(pDnpAI->UnitSymbol);
			if(!pDnpAI->MeasureTypeID)
			{
				continue;
			}

			if(pDnpAI->RTUMapId == pDevice->RTUMapId)
			{
				pdata->measurement[pDnpAI->Position].pointId = pDnpAI->MapId;
				_tcscpy_s(pdata->measurement[pDnpAI->Position].Name, pDnpAI->IndexName);
				//pdata->measurement[pMeasure->Position].upcName;
				pdata->measurement[pDnpAI->Position].data = 0;
				if(pUnit)
				{
					_tcscpy_s(pdata->measurement[pDnpAI->Position].UnitName, pUnit->UnitName);
				}
			}

		}

		//bi point scan
		const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_DNPBIMAPINDEX);
		for(int idi = 1; idi <= iTotal; idi++)
		{
			LPST_COMMON_DNPBIMAPINDEX pDnpBI = (LPST_COMMON_DNPBIMAPINDEX)CRDBMgr::GetDnpBI(idi);
			if(!pDnpBI)
				continue;
			if(pDnpBI->RTUMapId == pDevice->RTUMapId)
			{
				pdata->discrete[pDnpBI->Position].pointId = pDnpBI->MapId;
				_tcscpy_s(pdata->discrete[pDnpBI->Position].Name, pDnpBI->IndexName);
				//pdata->discrete[pdigi->Position].upcName;
				pdata->discrete[pDnpBI->Position].data = 0;	

				LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pDnpBI->StateGrpId);
				const int istateSet = GetRDBFileListCount(FILE_STATESET);
				for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
				{
					LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
					if(pSet->StateGrpId == pDnpBI->StateGrpId)
					{
						_tcscpy(pdata->discrete[pDnpBI->Position].PtName[pSet->Value], pSet->Name);
					}
				}				
			}
		} 

		//AO point scan
		const int iAoTotal = CRDBMgr::GetRDBFileListCount(FILE_DNPAOMAPINDEX);
		for(int idi = 1; idi <= iAoTotal; idi++)
		{
			LPST_COMMON_DNPAOMAPINDEX pDnpAO = (LPST_COMMON_DNPAOMAPINDEX)CRDBMgr::GetDnpAO(idi);
			if(!pDnpAO)
				continue;
			if(pDnpAO->RTUMapId == pDevice->RTUMapId)
			{
				pdata->setmeasurement[pDnpAO->Position].pointId = pDnpAO->MapId;
				_tcscpy_s(pdata->setmeasurement[pDnpAO->Position].Name, pDnpAO->IndexName);
				//pdata->setmeasurement[pdigi->Position].upcName;
				pdata->setmeasurement[pDnpAO->Position].data = 0;	

				//LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pDnpAO->StateGrpId);
				//const int istateSet = GetRDBFileListCount(FILE_STATESET);
				//for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
				//{
				//	LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
				//	if(pSet->StateGrpId == pDnpAO->StateGrpId)
				//	{
				//		_tcscpy(pdata->setmeasurement[pDnpAO->Position].PtName[pSet->Value], pSet->Name);
				//	}
				//}				
			}
		} 
		//BO point scan
		const int iBoTotal = CRDBMgr::GetRDBFileListCount(FILE_DNPBOMAPINDEX);
		for(int idi = 1; idi <= iBoTotal; idi++)
		{
			LPST_COMMON_DNPBOMAPINDEX pDnpBO = (LPST_COMMON_DNPBOMAPINDEX)CRDBMgr::GetDnpBO(idi);
			if(!pDnpBO)
				continue;
			if(pDnpBO->RTUMapId == pDevice->RTUMapId)
			{
				pdata->setdiscrete[pDnpBO->Position].pointId = pDnpBO->MapId;
				_tcscpy_s(pdata->setdiscrete[pDnpBO->Position].Name, pDnpBO->IndexName);
				//pdata->setdiscrete[pdigi->Position].upcName;
				pdata->setdiscrete[pDnpBO->Position].data = 0;	

				LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pDnpBO->StateGrpId);
				const int istateSet = GetRDBFileListCount(FILE_STATESET);
				for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
				{
					LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
					if(pSet->StateGrpId == pDnpBO->StateGrpId)
					{
						_tcscpy(pdata->setdiscrete[pDnpBO->Position].PtName[pSet->Value], pSet->Name);
					}
				}				
			}
		} 
	}
	_tcscpy_s(pdata->Name, pequip->Name);

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////
//// 태양광 발전 화면에 필요한 데이터 취득
//////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CRDBMgr::GetCondectionEquipBESSData(int nIndex, BLOCKBESSDATA* pdata)
{
	LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(nIndex);
	if(!pequip) return FALSE;

	LPST_COMMON_POWERSYSTEMRESOURCE pPsr = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetIndexPSR(pequip->PSRFK);
	if(!pPsr) return FALSE;

	if(pequip->DpGrpFK > 0)
	{
		LPST_COMMON_DATAPOINTGROUPCODE pDpGrp = (LPST_COMMON_DATAPOINTGROUPCODE)CRDBMgr::GetIndexDpGrp(pequip->DpGrpFK);
		if(!pDpGrp) return FALSE;

		pdata->DPCODE   = pequip->DpGrpFK;
		_tcscpy_s(pdata->DPName, pDpGrp->DpGrpName);
	}

	//공통입력 부분
	pdata->PSRTYFK	= pPsr->PSRTYPEFK;				//PSR 타입 
	pdata->CEQID	= pequip->CEQID;				//CEQID
	pdata->DLFK		= pequip->DLFK;					//소속 DL
	pdata->RUID		= pequip->RUID;					//RTU Device ID
	pdata->switchType = 0;

	if(pdata->RUID > 0)
	{
		LPST_COMMON_RTUDEVICE pDevice = (LPST_COMMON_RTUDEVICE)CRDBMgr::GetIndexRTUDevice(pequip->RUID);
		if(!pDevice) return FALSE;

		LPST_COMMON_RTUMAP pMap = (LPST_COMMON_RTUMAP)CRDBMgr::GetIndexRTUMap(pDevice->RTUMapId);// => 맵의 타입과 종류 확인일때만 필요
		if(!pMap) return FALSE;

		pdata->RTUType	= pMap->RTUTypeId;				//자수동 구분
		pdata->MapID	= pDevice->RTUMapId;
		// ai point
		const int imeasure = CRDBMgr::GetRDBFileListCount(FILE_DNPAIMAPINDEX);
		for(int ian = 1; ian <= imeasure; ian++)
		{			
			LPST_COMMON_DNPAIMAPINDEX pDnpAI = (LPST_COMMON_DNPAIMAPINDEX)CRDBMgr::GetDnpAI(ian);
			LPST_COMMON_UNIT		  pUnit = (LPST_COMMON_UNIT)CRDBMgr::GetIndexUnit(pDnpAI->UnitSymbol);
			if(!pDnpAI->MeasureTypeID)
			{
				continue;
			}

			if(pDnpAI->RTUMapId == pDevice->RTUMapId)
			{
				pdata->measurement[pDnpAI->Position].pointId = pDnpAI->MapId;
				_tcscpy_s(pdata->measurement[pDnpAI->Position].Name, pDnpAI->IndexName);
				//pdata->measurement[pMeasure->Position].upcName;
				pdata->measurement[pDnpAI->Position].data = 0;
				if(pUnit)
				{
					_tcscpy_s(pdata->measurement[pDnpAI->Position].UnitName, pUnit->UnitName);
				}
			}

		}

		//bi point scan
		const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_DNPBIMAPINDEX);
		for(int idi = 1; idi <= iTotal; idi++)
		{
			LPST_COMMON_DNPBIMAPINDEX pDnpBI = (LPST_COMMON_DNPBIMAPINDEX)CRDBMgr::GetDnpBI(idi);
			if(!pDnpBI)
				continue;
			if(pDnpBI->RTUMapId == pDevice->RTUMapId)
			{
				pdata->discrete[pDnpBI->Position].pointId = pDnpBI->MapId;
				_tcscpy_s(pdata->discrete[pDnpBI->Position].Name, pDnpBI->IndexName);
				//pdata->discrete[pdigi->Position].upcName;
				pdata->discrete[pDnpBI->Position].data = 0;	

				LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pDnpBI->StateGrpId);
				const int istateSet = GetRDBFileListCount(FILE_STATESET);
				for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
				{
					LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
					if(pSet->StateGrpId == pDnpBI->StateGrpId)
					{
						_tcscpy(pdata->discrete[pDnpBI->Position].PtName[pSet->Value], pSet->Name);
					}
				}				
			}
		} 

		//AO point scan
		const int iAoTotal = CRDBMgr::GetRDBFileListCount(FILE_DNPAOMAPINDEX);
		for(int idi = 1; idi <= iAoTotal; idi++)
		{
			LPST_COMMON_DNPAOMAPINDEX pDnpAO = (LPST_COMMON_DNPAOMAPINDEX)CRDBMgr::GetDnpAO(idi);
			if(!pDnpAO)
				continue;
			if(pDnpAO->RTUMapId == pDevice->RTUMapId)
			{
				pdata->setmeasurement[pDnpAO->Position].pointId = pDnpAO->MapId;
				_tcscpy_s(pdata->setmeasurement[pDnpAO->Position].Name, pDnpAO->IndexName);
				//pdata->setmeasurement[pdigi->Position].upcName;
				pdata->setmeasurement[pDnpAO->Position].data = 0;	

				//LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pDnpAO->StateGrpId);
				//const int istateSet = GetRDBFileListCount(FILE_STATESET);
				//for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
				//{
				//	LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
				//	if(pSet->StateGrpId == pDnpAO->StateGrpId)
				//	{
				//		_tcscpy(pdata->setmeasurement[pDnpAO->Position].PtName[pSet->Value], pSet->Name);
				//	}
				//}				
			}
		} 
		//BO point scan
		const int iBoTotal = CRDBMgr::GetRDBFileListCount(FILE_DNPBOMAPINDEX);
		for(int idi = 1; idi <= iBoTotal; idi++)
		{
			LPST_COMMON_DNPBOMAPINDEX pDnpBO = (LPST_COMMON_DNPBOMAPINDEX)CRDBMgr::GetDnpBO(idi);
			if(!pDnpBO)
				continue;
			if(pDnpBO->RTUMapId == pDevice->RTUMapId)
			{
				pdata->setdiscrete[pDnpBO->Position].pointId = pDnpBO->MapId;
				_tcscpy_s(pdata->setdiscrete[pDnpBO->Position].Name, pDnpBO->IndexName);
				//pdata->setdiscrete[pdigi->Position].upcName;
				pdata->setdiscrete[pDnpBO->Position].data = 0;	

				LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pDnpBO->StateGrpId);
				const int istateSet = GetRDBFileListCount(FILE_STATESET);
				for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
				{
					LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
					if(pSet->StateGrpId == pDnpBO->StateGrpId)
					{
						_tcscpy(pdata->setdiscrete[pDnpBO->Position].PtName[pSet->Value], pSet->Name);
					}
				}				
			}
		} 
	}
	_tcscpy_s(pdata->Name, pequip->Name);

	return TRUE;
}
BOOL CRDBMgr::GetDLNameData(int nIndex, DIAGRAMLINEDATA* dlName)
{
	LPST_COMMON_DISTRIBUTIONLINE pdl = (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetIndexDLine(nIndex);
	if(!pdl) return false;

	LPST_COMMON_SUBSTATION pSub = (LPST_COMMON_SUBSTATION)CRDBMgr::GetIndexSubStation(pdl->SSFK);
	if(!pSub) return false;

	if( pdl->DLID > 0)
	{
		dlName->dl_id = pdl->DLID;
		_tcscpy_s(dlName->name, pdl->Name);
		_tcscpy_s(dlName->substation, pSub->Name);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CRDBMgr::GetSubstationData(int nIndex, TCHAR* ssName)
{
	LPST_COMMON_SUBSTATION pSubstation = (LPST_COMMON_SUBSTATION)CRDBMgr::GetSubStation(nIndex);
	if(!pSubstation) return false;

	if(pSubstation->SSID > 0)
	{
		_tcscpy(ssName, pSubstation->Name);
		return true;
	}
	else
		return FALSE;
}

INT CRDBMgr::GetCompositeInEquipCount(int nIndex, long* id, long* psrid, TCHAR* szname)
{
	LPST_COMMON_COMPOSITESWITCH pcomposite = (LPST_COMMON_COMPOSITESWITCH)GetComposite(nIndex);

	int compositecnt = 0;
	*id		= pcomposite->CPSID;

	LPST_COMMON_POWERSYSTEMRESOURCE pPsr = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetIndexPSR(pcomposite->PSRFK);
	if(!pPsr) return 0;
	*psrid	= pPsr->PSRTYPEFK;
	_tcscpy(szname, pcomposite->Name);

	const int nTotalSw = GetRDBFileListCount(FILE_SWITCH);

	for(int nIndex = 1; nIndex < nTotalSw; nIndex++)
	{
		LPST_COMMON_SWITCH pSw = (LPST_COMMON_SWITCH)CRDBMgr::GetSwitch(nIndex);

		if(pcomposite->CPSID == pSw->CPSFK)
			compositecnt++;
	}

	return compositecnt;
}

INT CRDBMgr::GetUnderTrInEquipName(int nIndex, long* id, TCHAR* szname)
{
	LPST_COMMON_POWERTRANSFORMER punderTr = (LPST_COMMON_POWERTRANSFORMER)CRDBMgr::GetPowerTr(nIndex);

	*id		= punderTr->PTRID;
	_tcscpy(szname, punderTr->Name);

	return 2;
}

INT CRDBMgr::GetSVREquipName(int nIndex, long* id, TCHAR* szname)  //무효전력 보상장치
{
	const int iSvr = GetRDBFileListCount(FILE_STATICVARCOMPENSATOR);

	for(int iCnt = 1; iCnt <= iSvr; iCnt++)
	{
		LPST_COMMON_STATICVARCOMPENSATOR pSvr = (LPST_COMMON_STATICVARCOMPENSATOR)CRDBMgr::GetSvr(nIndex);
		if(nIndex  == pSvr->CEQFK)
		{
			*id		= pSvr->CEQFK;
			_tcscpy(szname, pSvr->Name);
			break;
		}
	}

	return 2;
}
BOOL CRDBMgr::GetUnitInfo(long equipid, long psrid, UNITINFO* pinfo)
{
	CString strName; //SVR의 경우 1번 Winding의 CEQID를 표시하고 PTR의 이름을 표시한다
	CString strID;
	if(aPsrType[psrid] == 14 || aPsrType[psrid] == 10 ) //SVR, TR
	{
		LPST_COMMON_POWERTRANSFORMER pTr = CRDBMgr::GetIndexPowerTr(equipid);
		if(!pTr) return false;

		const int iTotal = GetRDBFileListCount(FILE_TRANSFORMERWINDING);
		for(int index = 1; index <= iTotal; index++)
		{
			LPST_COMMON_TRANSFORMERWINDING	wind = (LPST_COMMON_TRANSFORMERWINDING)CRDBMgr::GetIndexDisTransWind(index);
			if(!wind) return false;
			
			if( wind->PTRFK == equipid && wind->windingType == 1)
			{
				equipid = wind->CEQFK;
				strID.Format(_T("%d"), equipid);
				_tcscpy(pinfo->CeqID, strID);
				strName.Format(_T("%s"), pTr->Name);
				break;
			}

		}
	}
	else
	{
		strID.Format(_T("%d"), equipid);
		_tcscpy(pinfo->CeqID, strID);
	}

	LPST_COMMON_CONDUCTINGEQUIPMENT pequip  = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(equipid);
	if(!pequip) return false;
	LPST_COMMON_RTUDEVICE pDevice			= (LPST_COMMON_RTUDEVICE)CRDBMgr::GetIndexRTUDevice(pequip->RUID);
	if(!pDevice) return false;
	LPST_COMMON_RTUMAP pMap					= (LPST_COMMON_RTUMAP)CRDBMgr::GetIndexRTUMap(pDevice->RTUMapId);
	if(!pMap) return false;
	LPST_COMMON_POWERSYSTEMRESOURCE pPsr	= (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetPSR(psrid);
	if(!pPsr) return false;
	LPST_COMMON_PSRTYPE pPsrType			= (LPST_COMMON_PSRTYPE)CRDBMgr::GetIndexPsrType(pPsr->PSRTYPEFK);
	if(!pPsrType) return false;
	LPST_COMMON_DISTRIBUTIONLINE pdl		= (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetIndexDLine(pequip->DLFK);
	if(!pdl) return false;
	LPST_COMMON_SUBSTATION pst				= (LPST_COMMON_SUBSTATION)CRDBMgr::GetIndexSubStation(pdl->SSFK);
	if(!pst) return false;
	LPST_COMMON_PROTOCOLTYPE pProtocol		= (LPST_COMMON_PROTOCOLTYPE)CRDBMgr::GetIndexProtocolType(pDevice->Protocol);
	if(!pProtocol) return false;
	LPST_COMMON_COMMTYPE pCommType			= (LPST_COMMON_COMMTYPE)CRDBMgr::GetIndexCommType(pDevice->CommTypeId);
	if(!pCommType) return false;

	//설비PSR 에 RTUMAP 이름으로 수정
	_tcscpy(pinfo->psrName,  pMap->RTUKind);
	//if(pPsr->PSRTYPEFK == 26)
	//{
	//	int equip_svr = 0;
	//	if((equip_svr = GetSVRConductEquipmentInfo(equipid)) > 0)
	//		equipid = equip_svr;
	//}
	_itot(pDevice->PRI_FEP, pinfo->mAddress, 10);
	_itot(pDevice->BCK_FEP, pinfo->sAddress, 10);
	_itot(pDevice->MasterDnp, pinfo->DnpAddress, 10);
	if(pMap->RTUTypeId == MENUAL)
		 wcscpy_s(pinfo->type,	_T("수동"));
	else
		 wcscpy_s(pinfo->type, _T("자동"));

	//_tcscpy(pinfo->psr, pPsrType->Name);
	_tcscpy(pinfo->dl, pdl->Name);
	_tcscpy(pinfo->station, pst->Name);
	//_tcscpy(pinfo->create, premote->rtu_company); => Equipmentcompany 코드와 연결안됨
	//_tcscpy(pinfo->day, premote->rtu_make_date); => 설치 일자 없음
	//_tcscpy(pinfo->custate, premote->rtu_install_date);

	_tcscpy(pinfo->proto, pProtocol->ProtocolName);
	_tcscpy(pinfo->commType, pCommType->ConmmTypeName);
	//_tcscpy(pinfo->makeNo, premote->rtu_seralno); => 제작 번호 없음
	//_tcscpy(pinfo->makeDate, premote->rtu_install_date); => 설치일자 없음
	//_tcscpy(pinfo->version, premote->rtu_version); => 버전 없음
	//_tcscpy(pinfo->makeNo2, premote->eq_serialno); => 제작 번호2 없음
	//_tcscpy(pinfo->man, premote->eq_install_manager); => 설치자 없음
	//_tcscpy(pinfo->psrName,  pPsrType->Name);
	if(aPsrType[psrid] == 14 || aPsrType[psrid] == 10 ) //SVR, TR
	{
		_tcscpy(pinfo->name, strName);
	}
	else
	{
		_tcscpy(pinfo->name, pequip->Name);
	}
	_tcscpy(pinfo->MeshNo, pequip->MeshNo);

	
	return TRUE;
}
int CRDBMgr::GetSVRConductEquipmentInfo(long svrid)
{

	LPST_COMMON_STATICVARCOMPENSATOR pSvr = (LPST_COMMON_STATICVARCOMPENSATOR)CRDBMgr::GetSvr(svrid);
	if(pSvr->CEQFK > 0)
		return pSvr->CEQFK;

	return 0;
}
BOOL CRDBMgr::GetEnergyCom(long equipid, long psrid, ENERGYCON* pinfo)
{
	LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(equipid);
	if(!pequip) return false;
	LPST_COMMON_DISTRIBUTIONLINE pdl	   = (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetIndexDLine(pequip->DLFK);
	if(!pdl) return false;

	for(int icnt = 1; icnt <= CRDBMgr::GetRDBFileListCount(FILE_ENERGYCONSUMER); icnt++)
	{
		LPST_COMMON_ENERGYCONSUMER pec = (LPST_COMMON_ENERGYCONSUMER)&g_pCommonENERGYCONSUMER[icnt];

		if(pequip->CEQID == pec->CEQFK)
		{
			LPST_COMMON_UNIT pUnit = (LPST_COMMON_UNIT)&g_pCommonUNIT[pec->pfixed_usfk];

			_tcscpy(pinfo->dlname, pdl->Name);
			_tcscpy(pinfo->Name, pec->Name);
			_tcscpy(pinfo->Tel, pec->Tel);
			_tcscpy(pinfo->HP, pec->HP);
			_stprintf(pinfo->pfixed, _T("%.02f%s"), pec->pfixed, pec->pfixed);
			_stprintf(pinfo->qfixed, _T("%.02f%s"), pec->qfixed, pec->qfixed);
			_tcscpy(pinfo->Customer_key, pec->Customer_key);
			_itot_s(pec->customerCount, pinfo->customerCount, 10);
			_itot_s(pec->Priority, pinfo->Priority, 10);
			(pec->SmsUse) ? _tcscpy_s(pinfo->SmsUse, _T("유")) : _tcscpy_s(pinfo->SmsUse, _T("무"));

			break;
		}
	}

	return TRUE;
}

BOOL CRDBMgr::GetLineSec(long equipid, long psrid, LINESEC* pinfo)
{
	LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(equipid);
	if(!pequip) return false;
	
	for(int icnt = 1; icnt <= GetRDBFileListCount(FILE_ACLINESEGMENT); icnt++) // 구간 카운트
	{
		LPST_COMMON_ACLINESEGMENT dls = (LPST_COMMON_ACLINESEGMENT)&g_pCommonACLINESEGMENT[icnt];

		LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE pPer = (LPST_COMMON_PERLENGTHSEQUENCEIMPEDANCE)&g_pCommonPERLENGTHSEQUENCEIMPEDANCE[dls->PLSIFK];

		if(dls->CEQFK == pequip->CEQID)
		{
			LPST_COMMON_UNIT psyle = (LPST_COMMON_UNIT)&g_pCommonUNIT[dls->length_usfk];
			LPST_COMMON_DISTRIBUTIONLINE pdl = (LPST_COMMON_DISTRIBUTIONLINE)&g_pCommonDISTRIBUTIONLINE[pequip->DLFK];
			LPST_COMMON_SUBSTATION psub = (LPST_COMMON_SUBSTATION)&g_pCommonSUBSTATION[pequip->SSFK];

			_tcscpy_s(pinfo->name, dls->Name);
			_tcscpy_s(pinfo->dl, pdl->Name);
			_tcscpy_s(pinfo->substation, psub->Name);

			CString szTem;
			TCHAR	szTem1[20] = {0, };
			szTem.Format(_T("%.2f"), dls->length);
			_tcscpy(szTem1, psyle->UnitName);
			szTem = szTem + szTem1;
			_tcscpy_s(pinfo->line, (LPTSTR)(LPCTSTR)szTem);
			
			//szTem.Format(_T("%.2f"), dls->secload);
			//_tcscpy_s(szTem1, dls->secload_us);
			//szTem = szTem + szTem1;
			//
			//_tcscpy_s(pinfo->size, (LPTSTR)(LPCTSTR)szTem);
			
			//(dls->PLSIFK) ? _tcscpy_s(pinfo->sang, GetLangString(LANG_CAP_00397)) : _tcscpy_s(pinfo->sang, GetLangString(LANG_CAP_00398));

		}
	}

	return TRUE;
}

BOOL CRDBMgr::GetSubStationList(CList<SEARCHDATA*, SEARCHDATA*>* pdata)
{
	for(int icnt = 1; icnt <= GetRDBFileListCount(FILE_CONDUCTINGEQUIPMENT); icnt++)
	{
		LPST_COMMON_CONDUCTINGEQUIPMENT equip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetEquip(icnt);
		LPST_COMMON_POWERSYSTEMRESOURCE psr   = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetPSR(equip->PSRFK);
		LPST_COMMON_PSRTYPE psrtype           = (LPST_COMMON_PSRTYPE)CRDBMgr::GetPsrType(psr->PSRTYPEFK);
		if(psr->PSRTYPEFK == 3)
		{
			LPST_COMMON_SUBSTATION st				= (LPST_COMMON_SUBSTATION)CRDBMgr::GetSubStation(equip->SSFK);
			LPST_COMMON_SUBGEOGRAPHICALREGION sub	= (LPST_COMMON_SUBGEOGRAPHICALREGION)CRDBMgr::GetSubGeoGraphic(st->SGRFK);
			LPST_COMMON_GEOGRAPHICALREGION geo		= (LPST_COMMON_GEOGRAPHICALREGION)CRDBMgr::GetGeoGraphic(sub->GGRFK);

			SEARCHDATA* pData = new SEARCHDATA;
			memset(pData, 0, sizeof(SEARCHDATA));
			pData->equipid = equip->CEQID;
			pData->psrid = psr->PSRTYPEFK;


			_tcscpy_s(pData->sta, st->Name);
			_tcscpy_s(pData->sub, sub->Name);
			_tcscpy_s(pData->geo, geo->Name);
			_tcscpy_s(pData->eq, equip->Name);

			pdata->AddTail(pData);
		}
	}

	return FALSE;
}

BOOL CRDBMgr::GetEquipList(CList<SEARCHDATA*, SEARCHDATA*>* pdata)
{
	for(int icnt = 1; icnt <= GetRDBFileListCount(FILE_CONDUCTINGEQUIPMENT); icnt++)
	{
		LPST_COMMON_CONDUCTINGEQUIPMENT equip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetEquip(icnt);

		LPST_COMMON_DISTRIBUTIONLINE dl		  = (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetDLine(equip->DLFK);
		LPST_COMMON_SUBSTATION st			  = (LPST_COMMON_SUBSTATION)CRDBMgr::GetSubStation(dl->SSFK);
		LPST_COMMON_SUBGEOGRAPHICALREGION sub = (LPST_COMMON_SUBGEOGRAPHICALREGION)CRDBMgr::GetSubGeoGraphic(st->SGRFK);
		LPST_COMMON_GEOGRAPHICALREGION geo	  = (LPST_COMMON_GEOGRAPHICALREGION)CRDBMgr::GetGeoGraphic(sub->GGRFK);
		LPST_COMMON_POWERSYSTEMRESOURCE psr   = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetPSR(equip->PSRFK);
		LPST_COMMON_PSRTYPE psrtype           = (LPST_COMMON_PSRTYPE)CRDBMgr::GetPsrType(psr->PSRTYPEFK);

		SEARCHDATA* pData = new SEARCHDATA;
		memset(pData, 0, sizeof(SEARCHDATA));
		pData->equipid = equip->CEQID;
		pData->psrid = psrtype->PSRTYPEID;

		_tcscpy_s(pData->dl, dl->Name);
		_tcscpy_s(pData->sta, st->Name);
		_tcscpy_s(pData->sub, sub->Name);
		_tcscpy_s(pData->geo, geo->Name);
		_tcscpy_s(pData->eq, equip->Name);
		_tcscpy_s(pData->psr, psrtype->Name);

		pdata->AddTail(pData);
	}

	return TRUE;
}

BOOL CRDBMgr::GetEquipList(long geo, long sub, long station, long dl, CList<SEARCHDATA*, SEARCHDATA*>* pdata)
{
	for(int icnt = 1; icnt <= GetRDBFileListCount(FILE_CONDUCTINGEQUIPMENT); icnt++)
	{
		LPST_COMMON_CONDUCTINGEQUIPMENT equip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetEquip(icnt);

		if(equip->DLFK == dl && equip->SSFK == station)
		{
			LPST_COMMON_DISTRIBUTIONLINE dl		  = (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetDLine(equip->DLFK);
			LPST_COMMON_SUBSTATION st			  = (LPST_COMMON_SUBSTATION)CRDBMgr::GetSubStation(dl->SSFK);
			LPST_COMMON_SUBGEOGRAPHICALREGION sub = (LPST_COMMON_SUBGEOGRAPHICALREGION)CRDBMgr::GetSubGeoGraphic(st->SGRFK);
			LPST_COMMON_GEOGRAPHICALREGION geo	  = (LPST_COMMON_GEOGRAPHICALREGION)CRDBMgr::GetGeoGraphic(sub->GGRFK);
			LPST_COMMON_POWERSYSTEMRESOURCE psr   = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetPSR(equip->PSRFK);
			LPST_COMMON_PSRTYPE psrtype           = (LPST_COMMON_PSRTYPE)CRDBMgr::GetPsrType(psr->PSRTYPEFK);

			SEARCHDATA* pData = new SEARCHDATA;
			memset(pData, 0, sizeof(SEARCHDATA));
			pData->equipid = equip->CEQID;
			pData->psrid = psrtype->PSRTYPEID;

			_tcscpy_s(pData->dl, dl->Name);
			_tcscpy_s(pData->sta, st->Name);
			_tcscpy_s(pData->sub, sub->Name);
			_tcscpy_s(pData->geo, geo->Name);
			_tcscpy_s(pData->eq, equip->Name);
			_tcscpy_s(pData->psr, psrtype->Name);

			pdata->AddTail(pData);
		}
	}

	return TRUE;
}

BOOL CRDBMgr::GetCtrlInfo(long equipid, long dlid, long deviceId, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list)
{
	LPST_COMMON_RTUDEVICE pDevice			 = (LPST_COMMON_RTUDEVICE)CRDBMgr::GetIndexRTUDevice(deviceId);
	if(!pDevice) return false;

	LPST_COMMON_CONDUCTINGEQUIPMENT pEquip	 = (LPST_COMMON_CONDUCTINGEQUIPMENT)GetIndexEquip(equipid);
	if(!pEquip) return false;

	const int iSetDiscrete = GetRDBFileListCount(FILE_DNPBOMAPINDEX);

	for(int iIndex = 1; iIndex <= iSetDiscrete; iIndex++)
	{
		LPST_COMMON_DNPBOMAPINDEX pBo = (LPST_COMMON_DNPBOMAPINDEX)&g_pCommonDNPBOMAPINDEX[iIndex];

		if(!pBo->MeasureTypeID)
			continue;
		/* DO */
		if(pBo->MapId == deviceId && aRDBDataPoint[pBo->MeasureTypeID][0] == 2)
		{
			UNITDIGIINFO* pItem = new UNITDIGIINFO;
			memset(pItem, 0, sizeof(UNITDIGIINFO));

			//pItem->cid		= pBo->pid;
			//pItem->cpos		= pBo->MeasureTypeID;
			//pItem->cline		= pBo->circuit_no;
			//pItem->cpoint		= pBo->bi_fk;

			pItem->MapId		= pBo->RTUMapId;
			pItem->DeviceId		= pBo->MapId;
			pItem->Index		= pBo->Position;
			pItem->CircuitNo    = pBo->CircuitNo;
			pItem->linkpoint	= pBo->Position;

			_tcscpy(pItem->upc_name, pBo->upc_name);
			_tcscpy(pItem->upc_tlq, pBo->upc_tlq);
			_tcscpy(pItem->upc_uptime, pBo->upc_uptime);
			_tcscpy(pItem->szName, pBo->IndexName);

			LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pBo->StateGrpId);

			const int istateSet = GetRDBFileListCount(FILE_STATESET);
			for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
			{
				LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
				if(pSet->StateGrpId == pBo->StateGrpId)
				{
					_tcscpy(pItem->szNames[icnt], pSet->Name);
				}

				//LPST_RDB_COLOR	pcolor = (LPST_RDB_COLOR)CRDBMgr::GetColor(pcmvalue->color_fk);
				//pItem->color[icnt] = pcolor->value;
				//pItem->colorFk[icnt]	= pcmvalue->color_fk;
				//pItem->ccommand[icnt]	= pcmvalue->value;
			}
	
			list->AddTail(pItem);
		}
	}

	return TRUE;
}

BOOL CRDBMgr::GetStatInfo(long equipid, long dlid, long remote, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list)
{
	LPST_COMMON_RTUDEVICE pre				= (LPST_COMMON_RTUDEVICE)CRDBMgr::GetIndexRTUDevice(remote);
	if(!pre) return false;

	LPST_COMMON_CONDUCTINGEQUIPMENT pEquip	= (LPST_COMMON_CONDUCTINGEQUIPMENT)GetEquip(equipid);
	if(!pEquip) return false;

	const int iDiscrete = GetRDBFileListCount(FILE_DNPBIMAPINDEX);

	for(int iIndex = 1; iIndex <= iDiscrete; iIndex++)
	{
		LPST_COMMON_DNPBIMAPINDEX pBI = (LPST_COMMON_DNPBIMAPINDEX)&g_pCommonDNPBIMAPINDEX[iIndex];

		if(!pBI->MeasureTypeID)
			continue;
		if(aRDBDataPoint[pBI->MeasureTypeID][0] == 1)
		{
			UNITDIGIINFO* pItem = new UNITDIGIINFO;
			memset(pItem, 0, sizeof(UNITDIGIINFO));

			//pItem->cid		= pdis->pid;
			//pItem->cpoint	= pdis->bo_fk;
			//pItem->cpos		= pdis->dp_fk;
			//pItem->cline	= pdis->circuit_no;
			//pItem->abnormalValue = pdis->abnormal_value;

			pItem->MapId		= pBI->RTUMapId;
			pItem->DeviceId		= pBI->MapId;
			pItem->Index		= pBI->Position;
			pItem->CircuitNo    = pBI->CircuitNo;
			pItem->linkpoint	= pBI->BO_Position;
			pItem->abnormalValue = pBI->AbnormalValue;
			pItem->normalValue   = pBI->NormalValue;  

			_tcscpy(pItem->upc_name, pBI->upc_name);
			_tcscpy(pItem->upc_tlq, pBI->upc_tlq);
			_tcscpy(pItem->upc_uptime, pBI->upc_uptime);
			_tcscpy(pItem->szName, pBI->IndexName);

			LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pBI->StateGrpId);

			const int istateSet = GetRDBFileListCount(FILE_STATESET);
			for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
			{
				LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
				if(pSet->StateGrpId == pBI->StateGrpId)
				{
					_tcscpy(pItem->szNames[icnt], pSet->Name);
				}

				//LPST_RDB_COLOR	pcolor = (LPST_RDB_COLOR)CRDBMgr::GetColor(pcmvalue->color_fk);
				//pItem->color[icnt] = pcolor->value;
				//pItem->colorFk[icnt]	= pcmvalue->color_fk;
				//pItem->ccommand[icnt]	= pcmvalue->value;
			}

			list->AddTail(pItem);
		}		
	}
	return TRUE;
}

BOOL CRDBMgr::GeCtrlInfo(long equipid, long psrid, UNITCTRLINFO* pInfo)
{
	LPST_COMMON_CONDUCTINGEQUIPMENT pequip	= (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(equipid);
	if(!pequip) return false;

	LPST_COMMON_POWERSYSTEMRESOURCE psr   = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetIndexPSR(pequip->PSRFK);
	if(!psr) return false;

	LPST_COMMON_PSRTYPE pPsrtype				= (LPST_COMMON_PSRTYPE)CRDBMgr::GetIndexPsrType(psr->PSRTYPEFK);
	if(!pPsrtype) return false;

	LPST_COMMON_DISTRIBUTIONLINE pdl		= (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetIndexDLine(pequip->DLFK);
	if(!pdl) return false;

	pInfo->equipid = pequip->CEQID;
	pInfo->psr	= psr->PSRTYPEFK;

	_tcscpy(pInfo->psrname, pPsrtype->Name);
	_tcscpy(pInfo->name, pequip->Name);

	return TRUE;
}
BOOL CRDBMgr::GetFIListPoint(FIDATA fi, FILISTDATA *fiList)
{
	//FIDATA 데이터 구조체 확인 필요
	LPST_COMMON_CONDUCTINGEQUIPMENT pequip	= (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(fi._id);
	if(!pequip) return false;

	LPST_COMMON_DISTRIBUTIONLINE dl			= (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetIndexDLine(pequip->DLFK);
	if(!dl) return false;

	LPST_COMMON_SUBSTATION st				= (LPST_COMMON_SUBSTATION)CRDBMgr::GetIndexSubStation(pequip->SSFK);
	if(!st) return false;

	LPST_COMMON_SUBGEOGRAPHICALREGION sub	= (LPST_COMMON_SUBGEOGRAPHICALREGION)CRDBMgr::GetIndexSubGeoGraphic(st->SGRFK);
	if(!sub) return false;

	LPST_COMMON_DNPBIMAPINDEX pBI			= (LPST_COMMON_DNPBIMAPINDEX)CRDBMgr::GetIndexDnpBI(fi._point); //fi._point ; 포인트 인덱스 
	if(!pBI) return false;
	//LPST_COMMON_DISCRETE dis				= (LPST_COMMON_DISCRETE)CRDBMgr::GetDigital(fi._point);

	//sprintf(fiList->evtId, fi._evtId, sizeof(fi._evtId));			//이벤트 아이디
	fiList->Id = fi._id;											//설비 아이디
	fiList->psr = fi._psr;											//설비 PSR
	fiList->type = fi._type;										//설비 타입
	fiList->point = fi._point;										//발생 포인트
	memcpy(fiList->current, fi._current, sizeof(fi._current));		// 고장 전류
	memcpy(fiList->status, fi._status, sizeof(fi._status));			// 설비 상태

	_tcscpy(fiList->szunit, pequip->Name);		//전주번호
	_tcscpy(fiList->szstation, st->Name);		//변전소
	_tcscpy(fiList->szsubgeo, sub->Name);		//지사
	_tcscpy(fiList->szdl, dl->Name);			//DL
	_tcscpy(fiList->szPoint, pBI->IndexName);	//포인트 명

	return TRUE;
}
BOOL CRDBMgr::GetFIPoint(uPCComData m_uPcRtdata,long equip, long lPoint, UINT Type, FIDATA* pData)
{
	BOOL fRet = FALSE;

	switch(Type)
	{
	case ENUM_COMM_TP_BI:			// di
		{
			LPST_COMMON_DISCRETE pdigi = (LPST_COMMON_DISCRETE)CRDBMgr::GetIndexDiscrete(lPoint);
			if(!pdigi)
				break;

			if(aRDBDataPoint[pdigi->MeasureTypeID][0] == 1 && aRDBDataPoint[pdigi->MeasureTypeID][2] > 0)
			{
				switch(aRDBDataPoint[pdigi->MeasureTypeID][2])
				{
				case 1: // FI일시(A)
				case 2:	// FI일시(B)
				case 3:	// FI일시(C)
				case 4:	// FI일시(N)
					{
						//미들웨어 접속 데이터 업데이트 
						INT  iRet = 0;
						USHORT sTlq = 0;
						UINT  uiTime = 0;
						if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
						{
							//if(iRet) iRet = 1;
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 1] = iRet;
							pData->_type = 0;
							pData->_point = pdigi->PID; //pdigi->Position;
							pData->_time = uiTime;
						}
						
					}
					break;

				case 5:	// FI순간(A)
				case 6:	// FI순간(B)
				case 7:	// FI순간(C)
				case 8:	// FI순간(N)
					{
						//미들웨어 접속 데이터 업데이트 
						INT  iRet = 0;
						USHORT sTlq = 0;
						UINT  uiTime = 0;
						if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
						{
							//if(!iRet) iRet = 1;
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 5] = iRet;
							pData->_type = 1;
							pData->_point = pdigi->PID; //pBI->Position;
							pData->_time = uiTime;
						}
					}
					break;

				case 9:  //FI검출
				case 10:
				case 11:
				case 12:
					{
						//미들웨어 접속 데이터 업데이트 
						INT  iRet = 0;
						USHORT sTlq = 0;
						UINT  uiTime = 0;
						if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
						{
							pData->_type = 2;
							//if(!iRet) iRet = 1;
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 9] = iRet;
							pData->_point = pdigi->PID; //pBI->Position;
							pData->_time = uiTime;
						}
					}
					break;

				case 13: //고장유형-일시고장
					{
						//미들웨어 접속 데이터 업데이트 
						INT  iRet = 0;
						USHORT sTlq = 0;
						UINT  uiTime = 0;
						if( CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
						{
							if(!iRet)
							{
								pData->_type = 4; //해제
							}
							else
							{
								pData->_type = 0;
							}
							pData->_point = pdigi->PID; //pdigi->Position;
							pData->_time = uiTime;
						}
					}
					break;
				case 14: //고장유형-순간고장
					{
						//미들웨어 접속 데이터 업데이트 
						INT  iRet = 0;
						USHORT sTlq = 0;
						UINT  uiTime = 0;
						if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
						{
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 9] = iRet;
							if(!iRet)
							{
								pData->_type = 4; //해제
							}
							else
							{
								pData->_type = 1;
							}
							pData->_point = pdigi->PID; //pBI->Position;
							pData->_time = uiTime;
						}
					}
					break;
				case 15://FI 일시ABCN
				case 16:
				case 17:
				case 18:
					{
						//미들웨어 접속 데이터 업데이트 
						INT  iRet = 0;
						USHORT sTlq = 0;
						UINT  uiTime = 0;
						if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
						{
							//if(!iRet) iRet = 1;
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 15] = iRet;
							pData->_type = 0;
							pData->_point = pdigi->PID; //pBI->Position;
							pData->_time = uiTime;
						}
						
					}
					break;

				case 19://FI 순간ABCN
				case 20:
				case 21:
				case 22:
					{
						//미들웨어 접속 데이터 업데이트 
						INT  iRet = 0;
						USHORT sTlq = 0;
						UINT  uiTime = 0;
						if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
						{
							//if(!iRet) iRet = 1;
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 19] = iRet;
							pData->_type = 1;
							pData->_point = pdigi->PID; //pdigi->Position;
							pData->_time = uiTime;
						}
					}
					break;
				case 23://고장검출ABCN
				case 24:
				case 25:
				case 26:
					{
						//미들웨어 접속 데이터 업데이트 
						INT  iRet = 0;
						USHORT sTlq = 0;
						UINT  uiTime = 0;
						if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
						{
							//if(!iRet) iRet = 1;
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 23] = iRet;
							pData->_type = 2;
							pData->_point = pdigi->PID; //pdigi->Position;
							pData->_time = uiTime;
						}
					}
					break;
			
				case 27: //대전류 개방완료
					{
						//미들웨어 접속 데이터 업데이트 
						pData->_type = -1;
						//INT  iRet = 0;
						//USHORT sTlq = 0;
						//UINT  uiTime = 0;
						//if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
						//{
						//	if(!iRet)
						//	{
						//		pData->_type = -1;
						//	}
						//	else
						//	{
						//		pData->_type = 1;
						//	}
						//	pData->_point = pdigi->PID; //pdigi->Position;
						//}
					}
					break;
				case 28: //락아웃
					{
						//미들웨어 접속 데이터 업데이트 
						INT  iRet = 0;
						USHORT sTlq = 0;
						UINT  uiTime = 0;
						if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
						{
							if(!iRet)
							{
								pData->_type = 4;
							}
							else
							{
								pData->_type = 3;
							}
							pData->_point = pdigi->PID; //pBI->Position;
							pData->_time = uiTime;
						}
					}
					break;
				default://외부전원상실, 과전압, 과전류
					pData->_type = -1;
					break;
				}

				//LPST_RDB_REMOTEUNIT punit = (LPST_RDB_REMOTEUNIT)GetRemote(pdigi->rtu_fk);
				//LPST_COMMON_RTUDEVICE	pDevice = (LPST_COMMON_RTUDEVICE)GetIndexRTUDevice(pBI->MapId);
				//if(!pDevice)
				//	break;

				const int iMeasurement = GetRDBFileListCount(FILE_MEASUREMENT);
				for(int icnt = 1; icnt <= iMeasurement; icnt++)
				{
					LPST_COMMON_MEASUREMENT panal = (LPST_COMMON_MEASUREMENT)CRDBMgr::GetMesurement(icnt);
					if(aRDBDataPoint[panal->MeasureTypeID][4] != -1 && aRDBDataPoint[panal->MeasureTypeID][0] == 3)
					{
						float flRet = 0.0f;
						USHORT	usTlq2 =0;
						UINT	uiTime2 = 0;
						if(CMwComm::GetMwAXValue(m_uPcRtdata, ENUM_MW_TP_AI, panal->PID, flRet, usTlq2, uiTime2))
						{
							pData->_current[aRDBDataPoint[panal->MeasureTypeID][4]] = flRet;
						}
					}
				}				
				fRet = TRUE;
			}
		}
		break;
	}

	return fRet;
}
BOOL CRDBMgr::GetAllFIPoint(uPCComData m_uPcRtdata, long equip, long lPoint, UINT Type, FIDATA* pData)
{
	const int iDis = GetRDBFileListCount(FILE_DISCRETE);
	for(int icnt = 1; icnt <= iDis; icnt++)
	{
		LPST_COMMON_DISCRETE pdigi = (LPST_COMMON_DISCRETE)CRDBMgr::GetDiscrete(icnt);
		if(!pdigi)	continue;
		if(pdigi->CEQId == equip && aRDBDataPoint[pdigi->MeasureTypeID][0] == 1 && aRDBDataPoint[pdigi->MeasureTypeID][2] > 0)
		{
			switch(aRDBDataPoint[pdigi->MeasureTypeID][2])
			{
			case 1://삭제됨
			case 2:
			case 3:
			case 4:
				{
					//미들웨어 접속 데이터 업데이트 
					INT  iRet = 0;
					USHORT sTlq = 0;
					UINT  uiTime = 0;
					if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
					{
						if(iRet)
						{
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 1] = iRet;
							for(int n = 0; n < 10; n++)
							{
								if(pData->_FIPoint[n] ==  0)
								{
									pData->_FIPoint[n] = pdigi->PID;
									break;
								}
							}
							pData->_type = 0;
							pData->_point = pdigi->PID; //pdigi->Position;
							pData->_time = uiTime;
						}
					}
						
				}
				break;

			case 5://삭제됨
			case 6:
			case 7:
			case 8:
				{
					//미들웨어 접속 데이터 업데이트 
					INT  iRet = 0;
					USHORT sTlq = 0;
					UINT  uiTime = 0;
					if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
					{
						if(iRet)
						{
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 5] = iRet;
							for(int n = 0; n < 10; n++)
							{
								if(pData->_FIPoint[n] ==  0)
								{
									pData->_FIPoint[n] = pdigi->PID;
									break;
								}
							}
							pData->_type = 1;
							pData->_point = pdigi->PID; //pBI->Position;
							pData->_time = uiTime;
						}
					}
				}
				break;

			case 9: 
			case 10:
			case 11:
			case 12:
				{
					//미들웨어 접속 데이터 업데이트 
					INT  iRet = 0;
					USHORT sTlq = 0;
					UINT  uiTime = 0;
					if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
					{
						if(iRet)
						{
							pData->_type = 2;
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 9] = iRet;
							for(int n = 0; n < 10; n++)
							{
								if(pData->_FIPoint[n] ==  0)
								{
									pData->_FIPoint[n] = pdigi->PID;
									break;
								}
							}
							pData->_point = pdigi->PID; //pBI->Position;
							pData->_time = uiTime;
						}
					}

				}
				break;

			case 13: //일시
				{
					//미들웨어 접속 데이터 업데이트 
					INT  iRet = 0;
					USHORT sTlq = 0;
					UINT  uiTime = 0;
					if( CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
					{
						if(!iRet)
						{
							pData->_type = 4; //해제
						}
						else
						{
							pData->_type = 0;
						}
						pData->_point = pdigi->PID; //pdigi->Position;
						pData->_time = uiTime;
					}
				}
				break;
			case 14: //순간
				{
					//미들웨어 접속 데이터 업데이트 
					INT  iRet = 0;
					USHORT sTlq = 0;
					UINT  uiTime = 0;
					if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
					{
						//pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 9] = iRet;
						if(!iRet)
						{
							pData->_type = 4; //해제
						}
						else
						{
							pData->_type = 1;
						}
						pData->_point = pdigi->PID; //pBI->Position;
						pData->_time = uiTime;
					}
				}
				break;
			case 15://일시ABCN
			case 16:
			case 17:
			case 18:
				{
					//미들웨어 접속 데이터 업데이트 
					INT  iRet = 0;
					USHORT sTlq = 0;
					UINT  uiTime = 0;
					if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
					{
						if(iRet)
						{
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 15] = iRet;
							for(int n = 0; n < 10; n++)
							{
								if(pData->_FIPoint[n] ==  0)
								{
									pData->_FIPoint[n] = pdigi->PID;
									break;
								}
							}
							pData->_type = 0;
							pData->_point = pdigi->PID; //pBI->Position;
							pData->_time = uiTime;
						}
					}
						
				}
				break;

			case 19://순간ABCN
			case 20:
			case 21:
			case 22:
				{
					//미들웨어 접속 데이터 업데이트 
					INT  iRet = 0;
					USHORT sTlq = 0;
					UINT  uiTime = 0;
					if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
					{	
						if(iRet)
						{
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 19] = iRet;
							for(int n = 0; n < 10; n++)
							{
								if(pData->_FIPoint[n] ==  0)
								{
									pData->_FIPoint[n] = pdigi->PID;
									break;
								}
							}
							pData->_type = 1;
							pData->_point = pdigi->PID; //pdigi->Position;
							pData->_time = uiTime;
						}
					}
				}
				break;
			case 23://고장검출ABCN
			case 24:
			case 25:
			case 26:
				{
					//미들웨어 접속 데이터 업데이트 
					INT  iRet = 0;
					USHORT sTlq = 0;
					UINT  uiTime = 0;
					if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
					{
						if(iRet)
						{
							pData->_status[aRDBDataPoint[pdigi->MeasureTypeID][2] - 23] = iRet;
							for(int n = 0; n < 10; n++)
							{
								if(pData->_FIPoint[n] ==  0)
								{
									pData->_FIPoint[n] = pdigi->PID;
									break;
								}
							}
							pData->_type = 2;
							pData->_point = pdigi->PID; //pdigi->Position;
							pData->_time = uiTime;
						}
					}
				}
				break;
			
			case 27: //대전류 개방완료
				{
					pData->_type = -1;
					//미들웨어 접속 데이터 업데이트 
					//INT  iRet = 0;
					//USHORT sTlq = 0;
					//UINT  uiTime = 0;
					//if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
					//{
					//	if(!iRet)
					//	{
					//		pData->_type = -1;
					//	}
					//	else
					//	{
					//		pData->_type = 1;
					//	}
					//	pData->_point = pdigi->PID; //pdigi->Position;
					//}
				}
				break;
			case 28: //락아웃
				{

					//미들웨어 접속 데이터 업데이트 
					INT  iRet = 0;
					USHORT sTlq = 0;
					UINT  uiTime = 0;
					if(CMwComm::GetMwBIValue(m_uPcRtdata, pdigi->PID, iRet, sTlq, uiTime))
					{
						if(!iRet)
						{
							pData->_type = 1;
						}
						else
						{
							pData->_type = 0;
						}
						pData->_point = pdigi->PID; //pBI->Position;
						pData->_time = uiTime;
					}
				}
				break;
			default:
				pData->_type = -1;
				break;
			}
		}
	}
	const int iMeasurement = GetRDBFileListCount(FILE_MEASUREMENT);
	for(int icnt = 1; icnt <= iMeasurement; icnt++)
	{
		LPST_COMMON_MEASUREMENT panal = (LPST_COMMON_MEASUREMENT)CRDBMgr::GetMesurement(icnt);
		if(aRDBDataPoint[panal->MeasureTypeID][4] != -1 && aRDBDataPoint[panal->MeasureTypeID][0] == 3)
		{
			float flRet = 0.0f;
			USHORT	usTlq2 =0;
			UINT	uiTime2 = 0;
			if(CMwComm::GetMwAXValue(m_uPcRtdata, ENUM_MW_TP_AI, panal->PID, flRet, usTlq2, uiTime2))
			{
				pData->_current[aRDBDataPoint[panal->MeasureTypeID][4]] = flRet;
			}
		}
	}
	return true;
}

//종합화면용
BOOL CRDBMgr::GetFIPointData(int nMapID, long equip, UINT Type, FIDATA* pData)
{
	BOOL fRet = FALSE;

	switch(Type)
	{
	case ENUM_COMM_TP_BI:			// di
		{
			LPST_COMMON_DNPBIMAPINDEX pBI			= (LPST_COMMON_DNPBIMAPINDEX)CRDBMgr::GetIndexDnpBI(nMapID); //BI 포인트의 인덱스
			if(!pBI) break;

			if(aRDBDataPoint[pBI->MeasureTypeID][0] == 1 && aRDBDataPoint[pBI->MeasureTypeID][2] > 0)
			{
				switch(aRDBDataPoint[pBI->MeasureTypeID][2])
				{
				case 1://삭제됨
				case 2:
				case 3:
				case 4:
					{
						short ret = 0;
						//미들웨어 접속 데이터 업데이트 
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);
						if(!ret) ret = 1;
						pData->_status[aRDBDataPoint[pBI->MeasureTypeID][2] - 1] = ret;
						pData->_type = 0;
						pData->_point = pBI->Position;

					}
					break;

				case 5://삭제됨
				case 6:
				case 7:
				case 8:
					{
						short ret = 0;
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);
						if(!ret) ret = 1;
						pData->_status[aRDBDataPoint[pBI->MeasureTypeID][2] - 5] = ret;
						pData->_type = 1;
						pData->_point = pBI->Position;
					}
					break;

				case 9: 
				case 10:
				case 11:
				case 12:
					{
						short ret = 0;
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);
						pData->_type = 2;
						if(!ret) ret = 1;
						pData->_status[aRDBDataPoint[pBI->MeasureTypeID][2] - 9] = ret;
						pData->_point = pBI->Position;
					}
					break;

				case 13: //일시
					{
						short ret = 0;
						if(!ret) ret = 1;
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);

						if(!ret)
						{
							pData->_type = 4; //해제
						}
						else
						{
							pData->_type = 0;
						}
						pData->_point = pBI->Position;
					}
					break;
				case 14: //순간
					{
						short ret = 0;
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);
						if(!ret) ret = 1;
						pData->_status[aRDBDataPoint[pBI->MeasureTypeID][2] - 9] = ret;
						if(!ret)
						{
							pData->_type = 4; //해제
						}
						else
						{
							pData->_type = 1;
						}
						pData->_point = pBI->Position;
					}
					break;
				case 15://일시ABCN
				case 16:
				case 17:
				case 18:
					{
						short ret = 0;
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);
						if(!ret) ret = 1;
						pData->_status[aRDBDataPoint[pBI->MeasureTypeID][2] - 15] = ret;
						pData->_type = 0;
						pData->_point = pBI->Position;

					}
					break;

				case 19://순간ABCN
				case 20:
				case 21:
				case 22:
					{
						short ret = 0;
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);
						if(!ret) ret = 1;
						pData->_status[aRDBDataPoint[pBI->MeasureTypeID][2] - 19] = ret;
						pData->_type = 1;
						pData->_point = pBI->Position;
					}
					break;
				case 23://고장검출ABCN
				case 24:
				case 25:
				case 26:
					{
						short ret = 0;
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);
						if(!ret) ret = 1;
						pData->_status[aRDBDataPoint[pBI->MeasureTypeID][2] - 23] = ret;
						pData->_type = 2;
						pData->_point = pBI->Position;
					}
					break;

				case 27: //대전류 개방완료
					{
						short ret = 0;
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);
						if(!ret)
						{
							pData->_type = 1;
						}
						else
						{
							pData->_type = 0;
						}
						pData->_point = pBI->Position;
					}
					break;
				case 28: //락아웃
					{
						short ret = 0;
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);
						if(!ret)
						{
							pData->_type = 1;
						}
						else
						{
							pData->_type = 0;
						}
						pData->_point = pBI->Position;
					}
					break;
				}

				const int iMeasurement = GetRDBFileListCount(FILE_DNPAIMAPINDEX);
				for(int icnt = 1; icnt <= iMeasurement; icnt++)
				{
					LPST_COMMON_DNPAIMAPINDEX pAI = (LPST_COMMON_DNPAIMAPINDEX)CRDBMgr::GetDnpAI(icnt);

					if(!pAI->MeasureTypeID)
						continue;
					if(aRDBDataPoint[pAI->MeasureTypeID][4] != -1 && aRDBDataPoint[pAI->MeasureTypeID][0] == 3)
					{
						if(aRDBDataPoint[pAI->MeasureTypeID][4] < 100)
						{
							float flRet = 0.0f;
							//HCIMM_GET_AXPTVALUE(ENUM_COMM_TP_AI, panal->pid, &flRet);
							pData->_current[aRDBDataPoint[pAI->MeasureTypeID][4]] = flRet;
						}
					}
				}

				fRet = TRUE;
			}
		}
		break;


	case ENUM_COMM_TP_AI:			// di
		{
			LPST_COMMON_DNPAIMAPINDEX pAI			= (LPST_COMMON_DNPAIMAPINDEX)CRDBMgr::GetIndexDnpAI(nMapID); //BI 포인트의 인덱스
			if(!pAI)break;

			if(aRDBDataPoint[pAI->MeasureTypeID][0] == 3 && aRDBDataPoint[pAI->MeasureTypeID][4] > 0)
			{
				switch(aRDBDataPoint[pAI->MeasureTypeID][4])
				{
				case 100:	//전류 (상전류)
				case 101:
				case 102:
				case 103:
					{
						short ret = 0;
						//미들웨어 접속 데이터 업데이트 
						//HCIMM_GET_BXPTVALUE(ENUM_COMM_TP_BI, pdigi->pid, &ret);
						if(!ret) ret = 1;
						pData->_status[aRDBDataPoint[pAI->MeasureTypeID][4] - 100] = ret;
						pData->_type = 0;
						pData->_point = pAI->Position;
					}
					break;
				}
				fRet = TRUE;
			}
		}
		break;
	}

	return fRet;
}

BOOL CRDBMgr::GetSwitchPoint(long equip, long lPoint, UINT Type)
{
	BOOL fRet = FALSE;

	switch(Type)
	{
	case ENUM_COMM_TP_BI:			// di
		{
			LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = (LPST_COMMON_CONDUCTINGEQUIPMENT)GetIndexEquip(equip);
			if(!pEquip) break;

			LPST_COMMON_RTUDEVICE	pDevice = (LPST_COMMON_RTUDEVICE)GetIndexRTUDevice(pEquip->RUID);
			if(!pDevice) break;

			//LPST_RDB_DISCRETE pdigi = (LPST_RDB_DISCRETE)CRDBMgr::GetDigital(lPoint);
			const int iMeasurement = GetRDBFileListCount(FILE_DNPBIMAPINDEX);
			for(int icnt = 1; icnt <= iMeasurement; icnt++)
			{
				LPST_COMMON_DNPBIMAPINDEX pBI = (LPST_COMMON_DNPBIMAPINDEX)CRDBMgr::GetDnpBI(lPoint);

				//if(pDevice->RTUMapId == pBI->MapId && aRDBDataPoint[pBI->MeasureTypeID][0] == 1 && aRDBDataPoint[pBI->MeasureTypeID][2] == 0)
				//{
				//	fRet = TRUE;
				//	return fRet;
				//}
			}
		}
		break;
	}

	return fRet;
}

BOOL CRDBMgr::GetRemoteBIPoint(long ceq, long device, CList<BIMENUALDATA*, BIMENUALDATA*>* pdata)
{
	LPST_COMMON_CONDUCTINGEQUIPMENT pEquip	 = (LPST_COMMON_CONDUCTINGEQUIPMENT)GetIndexEquip(ceq);
	if(!pEquip) return false;

	LPST_COMMON_RTUDEVICE pDevice			 = (LPST_COMMON_RTUDEVICE)GetIndexRTUDevice(device);
	if(!pDevice) return false;

	//다회로의 내부 스위치 위치값을 찾을 수 없어 전체 BI를 뒤짐, 변경되어 일반 스위치도 동일하게 뒤짐
	const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_DNPBIMAPINDEX);
	for(int icnt = 1; icnt <= iTotal; icnt++)
	{
		LPST_COMMON_DNPBIMAPINDEX pBI = (LPST_COMMON_DNPBIMAPINDEX)CRDBMgr::GetDnpBI(icnt);
		if(!pBI->MeasureTypeID)
			continue;
		if(aRDBDataPoint[pBI->MeasureTypeID][0] == 1)
		{
			LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetIndexStateGroup(pBI->StateGrpId);
			if(!pStateGrp) return false;
			//LPST_RDB_VALUEALIASSET pvalueset = (LPST_RDB_VALUEALIASSET)CRDBMgr::GetValueAliasSet(pdigi->vas_fk);
			BIMENUALDATA* pItem = new BIMENUALDATA;
			pItem->cnt			= pStateGrp->Count;
			pItem->curvalue		= pBI->NormalValue;
			pItem->id			= pBI->Position;
			pItem->uiTlq		= NORMAL;
			pItem->setvalue		= -1;
			pItem->foverride	= false;

			_tcscpy(pItem->szName, pBI->IndexName);

			pItem->paliasdata = new POINTALIASDATA[pItem->cnt];
			memset(pItem->paliasdata, 0, sizeof(POINTALIASDATA) * pItem->cnt);

			const int istateSet = GetRDBFileListCount(FILE_STATESET);
			for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
			{
				LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
				if(!pSet) continue;
				if(pSet->StateGrpId == pBI->StateGrpId)
				{
					//LPST_RDB_COLOR	pcolor = (LPST_RDB_COLOR)CRDBMgr::GetColor(pvalue->color_fk);
					pItem->paliasdata[index].index  = index;
					pItem->paliasdata[index].value 	= pSet->Value;
					//pItem->paliasdata[index].color	= pSet->color_fk;

					_tcscpy_s(pItem->paliasdata[index].szName, pSet->Name);
				}

				//LPST_RDB_COLOR	pcolor = (LPST_RDB_COLOR)CRDBMgr::GetColor(pcmvalue->color_fk);
				//pItem->color[icnt] = pcolor->value;
				//pItem->colorFk[icnt]	= pcmvalue->color_fk;
				//pItem->ccommand[icnt]	= pcmvalue->value;
			}
			//valuealias 얻기 추가
/*			for(int nSetIndex = pvalueset->va_pos_fk, nIndex = 0; nSetIndex < pvalueset->va_pos_fk + pvalueset->state_count; nSetIndex++, nIndex++)
			{
				LPST_RDB_VALUEALIAS pvalue = (LPST_RDB_VALUEALIAS)CRDBMgr::GetValueAlias(nSetIndex);

				LPST_RDB_COLOR	pcolor = (LPST_RDB_COLOR)CRDBMgr::GetColor(pvalue->color_fk);
				pItem->paliasdata[nIndex].index  = nIndex;
				pItem->paliasdata[nIndex].value 	= pvalue->value;
				pItem->paliasdata[nIndex].color	= pvalue->color_fk;

				_tcscpy(pItem->paliasdata[nIndex].szName, pvalue->state_name);
			}	*/		

			pdata->AddTail(pItem);
		}
	}



	return TRUE;
}

BOOL CRDBMgr::GetRemoteAIPoint(long ceq, long device, CList<AIMENUALDATA*, AIMENUALDATA*>* pdata)
{
	LPST_COMMON_RTUDEVICE pDevice			= (LPST_COMMON_RTUDEVICE)GetIndexRTUDevice(device);
	if(!device) return false;

	LPST_COMMON_CONDUCTINGEQUIPMENT pEquip	= (LPST_COMMON_CONDUCTINGEQUIPMENT)GetIndexEquip(ceq);
	if(!pEquip) return false;

	int nTotal = GetRDBFileListCount(FILE_DNPAIMAPINDEX);
	for(int icnt = 1; icnt <= nTotal; icnt++)
	{
		//LPST_RDB_ANALOG panal = (LPST_RDB_ANALOG)CRDBMgr::GetAnalog(icnt);
		LPST_COMMON_DNPAIMAPINDEX pAI = (LPST_COMMON_DNPAIMAPINDEX)CRDBMgr::GetDnpAI(icnt);
		if(!pAI->MeasureTypeID)
			continue;
		/* AI && remote id */
		if(aRDBDataPoint[pAI->MeasureTypeID][0] == 3 && pDevice->RTUMapId == pAI->RTUMapId )
		{
			AIMENUALDATA* pItem = new AIMENUALDATA;
			//pItem->curvalue		= pAI->init_value;
			pItem->id			= pAI->Position;

			LPST_COMMON_LIMITSET pLimitSet = (LPST_COMMON_LIMITSET)CRDBMgr::GetLimitSet(pAI->LimitSetId);

			const int iLimitCode = GetRDBFileListCount(FILE_LIMITCODE);
			for(int index = 1; index <= iLimitCode; index++)
			{
				LPST_COMMON_LIMITCODE pLimitCode = (LPST_COMMON_LIMITCODE)CRDBMgr::GetLimitCode(index);
				if(pLimitCode->LimitSetId == pAI->LimitSetId)
				{
					if(pLimitCode->Limittype == 0) // 하한
					{
						pItem->minvalue		= pLimitCode->Val;
					}
					else if(pLimitCode->Limittype == 1) //상한
					{
						pItem->maxvalue		= pLimitCode->Val;
					}
				}
			}
			
			pItem->setvalue		= 0.0f;

			pItem->uiTlq		= NORMAL;
			pItem->foverride	= false;

			_tcscpy_s(pItem->szName, pAI->IndexName);

			pdata->AddTail(pItem);
		}
	}

	return TRUE;
}

BOOL CRDBMgr::GetRemoteBOPoint(long ceq, long device, CList<BIMENUALDATA*, BIMENUALDATA*>* pdata)
{
	LPST_COMMON_RTUDEVICE pDevice = (LPST_COMMON_RTUDEVICE)GetIndexRTUDevice(device);
	if(!pDevice) return false;

	//다회로의 내부 스위치 위치값을 찾을 수 없어 전체 BI를 뒤짐
	const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_DNPBOMAPINDEX);
	for(int icnt = 1; icnt <= iTotal; icnt++)
	{
		LPST_COMMON_DNPBOMAPINDEX pBo = (LPST_COMMON_DNPBOMAPINDEX)CRDBMgr::GetDnpBO(icnt);
		if(!pBo->MeasureTypeID)
			continue;
		/* DO && remote id */
		if(aRDBDataPoint[pBo->MeasureTypeID][0] == 2)
		{
			LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pBo->StateGrpId);
			BIMENUALDATA* pItem = new BIMENUALDATA;
			pItem->cnt		= pStateGrp->Count;
			//pItem->curvalue = pBo->init_value;
			pItem->id		= pBo->Position;

			_tcscpy(pItem->szName, pBo->IndexName);

			pItem->paliasdata = new POINTALIASDATA[pItem->cnt];
			memset(pItem->paliasdata, 0, sizeof(POINTALIASDATA) * pItem->cnt);

			const int istateSet = GetRDBFileListCount(FILE_STATESET);
			for(int index = 1, icnt = 0; index < istateSet + pStateGrp->Count; index++, icnt++)
			{
				LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
				if(pSet->StateGrpId == pBo->StateGrpId)
				{
					//LPST_RDB_COLOR	pcolor = (LPST_RDB_COLOR)CRDBMgr::GetColor(pvalue->color_fk);
					pItem->paliasdata[index].index  = index;
					pItem->paliasdata[index].value 	= pSet->Value;
					//pItem->paliasdata[index].color	= pSet->color_fk;

					_tcscpy_s(pItem->paliasdata[index].szName, pSet->Name);
				}
			}

			pItem->foverride = false;
			pItem->uiTlq	= NORMAL;
			pItem->setvalue	= -1;
			pdata->AddTail(pItem);
		}
	}

	return TRUE;
}

BOOL CRDBMgr::GetRemoteAOPoint(long ceq, long device, CList<AIMENUALDATA*, AIMENUALDATA*>* pdata)
{
	LPST_COMMON_RTUDEVICE punit			   = (LPST_COMMON_RTUDEVICE)GetIndexRTUDevice(device);
	if(!punit) return false;
	
	LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = (LPST_COMMON_CONDUCTINGEQUIPMENT)GetEquip(ceq);
	if(!pEquip) return false;

	const int iSetMeasure = GetRDBFileListCount(FILE_DNPAOMAPINDEX);
	for(int icnt = 1; icnt <= iSetMeasure; icnt++)
	{
		LPST_COMMON_DNPAOMAPINDEX pAo = (LPST_COMMON_DNPAOMAPINDEX)CRDBMgr::GetDnpAO(icnt);

		if(!pAo->MeasureTypeID)
			continue;
		/* AO && remote id */
		if(aRDBDataPoint[pAo->MeasureTypeID][0] == 4 && device == pAo->MapId)
		{
			LPST_COMMON_LIMITSET pLimitSet = (LPST_COMMON_LIMITSET)CRDBMgr::GetLimitSet(pAo->MinMaxLimitSet);
			if(!pLimitSet) continue;

			AIMENUALDATA* pItem = new AIMENUALDATA;
			//pItem->curvalue		= pAo->init_value;
			pItem->id			= pAo->Position;

			const int iLimitCode = GetRDBFileListCount(FILE_LIMITCODE);
			for(int index = 1; index <= iLimitCode; index++)
			{
				LPST_COMMON_LIMITCODE pLimitCode = (LPST_COMMON_LIMITCODE)CRDBMgr::GetLimitCode(index);
				if(!pLimitCode) continue;

				if(pLimitCode->LimitSetId == pAo->MinMaxLimitSet)
				{
					if(pLimitCode->Limittype == 0) // 하한
					{
						pItem->minvalue		= pLimitCode->Val;
					}
					else if(pLimitCode->Limittype == 1) //상한
					{
						pItem->maxvalue		= pLimitCode->Val;
					}
				}
			}

			pItem->setvalue		= 0.0f;
			pItem->uiTlq	= NORMAL;
			pItem->foverride = false;

			_tcscpy(pItem->szName, pAo->IndexName);

			pdata->AddTail(pItem);
		}
	}

	return TRUE;
}

BOOL CRDBMgr::GetRemoteOpenPoint(long station, long dl, long device, long ceq, long* pid)
{
	BOOL fret = FALSE;
	LPST_COMMON_RTUDEVICE pDevice			= (LPST_COMMON_RTUDEVICE)GetIndexRTUDevice(device);
	if(!pDevice) return false;

	LPST_COMMON_CONDUCTINGEQUIPMENT pEquip  = (LPST_COMMON_CONDUCTINGEQUIPMENT)GetIndexEquip(ceq);
	if(!pEquip) return false;

	const int iSetDiscrete = GetRDBFileListCount(FILE_DNPBOMAPINDEX);
	for(int icnt =1; icnt <= iSetDiscrete; icnt++)
	{
		LPST_COMMON_DNPBOMAPINDEX pBo = (LPST_COMMON_DNPBOMAPINDEX)CRDBMgr::GetDnpBO(icnt);
		if(!pBo->MeasureTypeID)
			continue;
		if(aRDBDataPoint[pBo->MeasureTypeID][0] == 2/* && remote == pdigi->rtu_fk*/ && aRDBDataPoint[pBo->MeasureTypeID][1] == 9) //comand 1번의 rtu_fk가 0이라 처리
		{
			*pid = pBo->Position;
			fret = TRUE;
			break;
		}
	}

	return fret;
}

//-----------------------------------------------------------------------
// Summary:
//     리모트유닛 정보
// Parameters:
//     cequip			- 설비 id
//     punit			- 리모트 유닛정보[out]
//-----------------------------------------------------------------------
BOOL CRDBMgr::GetEquipIdToRemoteId(long cequip, long* device)
{
	//LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetEquip(cequip);
	//if(pequip->RUID >0)
	//{
	//	*device = pequip->RUID;
	//	return true;
	//}
	//else
	//	*device = 0;

	return FALSE;
}

//다시해야 함 DrUnit 사라짐
//-----------------------------------------------------------------------
// Summary:
//     리모트유닛 분산전원 정보
// Parameters:
//     lline			- 회로(단일일경우 0)
//     punit			- 리모트 유닛정보
//     pdrunit			- 분산전원 정보[out]
//-----------------------------------------------------------------------
BOOL CRDBMgr::GetDRInfo(long lline, long ceqid, DRUNIT* pdrunit)
{
//	if(!ceqid || !pdrunit)
//		return FALSE;
//	
//	LPST_COMMON_CONDUCTINGEQUIPMENT pcon = CRDBMgr::GetEquip(ceqid);
//
//	const int drcnt = CRDBMgr::GetRDBFileListCount(FILE_RDB_DRUNIT);
//
//	for(int index = 1; index <= drcnt; index++)
//	{
//		LPST_RDB_DRUNIT pDrunit = (LPST_RDB_DRUNIT)CRDBMgr::GetDrUnit(index);
//
//		if(pDrunit->ceq_fk == pcon->ceqid && pcon->dl_fk == pDrunit->dl_fk)
//		{
//			// 여기에 분산전원 추가
//			char szTem[MAX_STRING] = {0, };
//			LPST_RDB_UNITSYMBOL psy = NULL;
//
//			_itoa(pDrunit->powerrating, szTem, 0xa);			// 발전용량
//			psy = (LPST_RDB_UNITSYMBOL)GetUnitSymbol(pDrunit->powerrating_us_fk);
//			strcat(szTem, psy->name);
//
//#ifdef _UNICODE
//			_MBS2WCS(pdrunit->turbin, szTem, MAX_STRING);
//#else		
//			_tcscpy_s(pdrunit->turbin, szTem);
//#endif
//
//			sprintf(szTem, "%.01f", pDrunit->voltagerating);	// 전격전압
//			psy = (LPST_RDB_UNITSYMBOL)GetUnitSymbol(pDrunit->voltagerating_us_fk);
//			strcat(szTem, psy->name);
//
//#ifdef _UNICODE
//			_MBS2WCS(pdrunit->volt, szTem, MAX_STRING);
//#else		
//			_tcscpy_s(pdrunit->volt, szTem);
//#endif
//			_itoa(pDrunit->amprating, szTem, 0xa);			// 정격전류
//			psy = (LPST_RDB_UNITSYMBOL)GetUnitSymbol(pDrunit->amprating_us_fk);
//			strcat(szTem, psy->name);
//			
//			const int recnt = CRDBMgr::GetRDBFileListCount(FILE_RDB_REMOTEUNIT);
//
//			for(int reindex = 1; reindex <= recnt; reindex++)
//			{
//				LPST_RDB_REMOTEUNIT preunit = (LPST_RDB_REMOTEUNIT)CRDBMgr::GetRemote(reindex);
//
//				if(preunit->eq_fk == pcon->ceqid && preunit->eq_type != 2)
//				{
//#ifdef _UNICODE
//					_MBS2WCS(pdrunit->prot, preunit->protocol_name, MAX_STRING);
//					_MBS2WCS(pdrunit->comm, preunit->comm_info, MAX_STRING);
//#else
//					_tcscpy_s(pdrunit->prot, preunit->protocol_name);
//					_tcscpy_s(pdrunit->comm, preunit->comm_info);
//#endif
//					break;
//				}
//			}
//
//#ifdef _UNICODE
//			_MBS2WCS(pdrunit->arm, szTem, MAX_STRING);
//			_MBS2WCS(pdrunit->name, pDrunit->name, MAX_STRING);
//#else		
//			_tcscpy_s(pdrunit->storige, szTem);
//			_tcscpy_s(pdrunit->name, pDrunit->name);
//#endif
//			break;
//		}		
//	}
//
	return TRUE;
}


BOOL CRDBMgr::GetAmiAIPoint(long ceqid, CList<UNITANALOGININFO*, UNITANALOGININFO*>* list)
{
	if(!ceqid)
		return FALSE;

		LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = (LPST_COMMON_CONDUCTINGEQUIPMENT)GetIndexEquip(ceqid);
		if(!pEquip) return false;

		const int iMeasure = GetRDBFileListCount(FILE_DNPAIMAPINDEX);
		for(int icnt = 1; icnt <= iMeasure; icnt++)
		{
			//LPST_RDB_ANALOG pana = (LPST_RDB_ANALOG)&g_pRDBAnalog[icnt];
			LPST_COMMON_DNPAIMAPINDEX pAi = (LPST_COMMON_DNPAIMAPINDEX)&g_pCommonDNPAIMAPINDEX[icnt];
			if(!pAi->MeasureTypeID)
				continue;
			if(aRDBDataPoint[pAi->MeasureTypeID][0] == 3)
			{
				LPST_COMMON_UNIT pUnit = (LPST_COMMON_UNIT)&g_pCommonUNIT[pAi->UnitSymbol];

				UNITANALOGININFO* pItem = new UNITANALOGININFO;
				memset(pItem, 0, sizeof(UNITANALOGININFO));

				//pItem->MapId				= pEquip->RUID;
				pItem->RTUMapId				= pAi->RTUMapId;
				pItem->Position				= pAi->Position;					// ai point
				pItem->MeasureTypeID		= pAi->MeasureTypeID;				// datapointinfo index
				pItem->CircuitNo			= pAi->CircuitNo;			// 사용안함

				LPST_COMMON_SCALEFACTOR pScale = (LPST_COMMON_SCALEFACTOR)CRDBMgr::GetScale(pAi->Scale);
				if(!pScale->sfid)
					pItem->sfactor = pScale->Scale;

				const int iLimitCode = GetRDBFileListCount(FILE_LIMITCODE);
				for(int index = 1; index <= iLimitCode; index++)
				{
					LPST_COMMON_LIMITCODE pLimitCode = (LPST_COMMON_LIMITCODE)CRDBMgr::GetLimitCode(index);
					if(pLimitCode->LimitSetId == pAi->LimitSetId)
					{
						if(pLimitCode->Limittype == 0) // 하한
						{
							pItem->aminvalue		= pLimitCode->Val;
						}
						else if(pLimitCode->Limittype == 1) //상한
						{
							pItem->amaxvalue		= pLimitCode->Val;
						}
					}
				}

				//pItem->aminlimitvalue		= pAi->low_value;			// 최소 한계값
				//pItem->amaxlimitvalue		= pAi->high_value;			// 최대 한계값

				_tcscpy(pItem->szName, pAi->IndexName);
				_tcscpy(pItem->szMeasure, pUnit->UnitName);

				_tcscpy(pItem->upc_name,	 pAi->upc_name);
				_tcscpy(pItem->upc_tlq,		 pAi->upc_tlq);
				_tcscpy(pItem->upc_uptime,	 pAi->upc_uptime);
	
				list->AddTail(pItem);
			}
		}

	return TRUE;
}
BOOL CRDBMgr::GetAmiBIPoint(long ceqid, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list)
{
	if(!ceqid)
		return FALSE;

	const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_DNPBIMAPINDEX);
	for(int icnt = 1; icnt <= iTotal; icnt++)
	{
		LPST_COMMON_DNPBIMAPINDEX pBI = (LPST_COMMON_DNPBIMAPINDEX)CRDBMgr::GetDnpBI(icnt);
		if(!pBI->MeasureTypeID)
			continue;
		if(aRDBDataPoint[pBI->MeasureTypeID][0] == 1)
		{
			LPST_COMMON_STATEGROUP pStateGrp = (LPST_COMMON_STATEGROUP)CRDBMgr::GetStateGroup(pBI->StateGrpId);
			//LPST_RDB_VALUEALIASSET pvalueset = (LPST_RDB_VALUEALIASSET)CRDBMgr::GetValueAliasSet(pdigi->vas_fk);
			UNITDIGIINFO* pItem = new UNITDIGIINFO;
			memset(pItem, 0, sizeof(UNITDIGIINFO));
			pItem->Index			= pBI->Position;
			pItem->linkpoint		= pBI->BO_Position;
			pItem->measureTypeId	= pBI->MeasureTypeID;
			pItem->CircuitNo		= pBI->CircuitNo;
			pItem->abnormalValue	= pBI->AbnormalValue;
			pItem->normalValue		= pBI->NormalValue;

			_tcscpy(pItem->szName, pBI->IndexName);

			const int istateSet = GetRDBFileListCount(FILE_STATESET);
			for(int index = 1, icnt = 0; index <= istateSet; index++, icnt++)
			{
				LPST_COMMON_STATESET pSet = (LPST_COMMON_STATESET)CRDBMgr::GetStateSet(index);
				if(pSet->StateGrpId == pBI->StateGrpId)
				{
					_tcscpy(pItem->szNames[icnt], pSet->Name);

					//LPST_RDB_COLOR	pcolor = (LPST_RDB_COLOR)CRDBMgr::GetColor(pcmvalue->color_fk);
					//pItem->color[icnt]  = pcolor->value;
					//pItem->colorFk[icnt] 	= pcmvalue->color_fk;
					pItem->ccommand[icnt]	= pSet->Value;
				}
			}
			_tcscpy(pItem->szName, pBI->IndexName);
			list->AddTail(pItem);
		}
	}
	


	return TRUE;
}

BOOL CRDBMgr::GetAmiBIPoint(long ceqid, TRANSFORMERLIST* pdata)
{
	if(!ceqid)
		return FALSE;

	LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = (LPST_COMMON_CONDUCTINGEQUIPMENT)GetIndexEquip(ceqid);
	if(!pEquip) return false;

	const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_DNPBIMAPINDEX);
	for(int icnt = 1; icnt <= iTotal; icnt++)
	{
		LPST_COMMON_DNPBIMAPINDEX pBI = (LPST_COMMON_DNPBIMAPINDEX)CRDBMgr::GetDnpBI(icnt);
		//if(pEquip->RUID == pBI->MapId) //pdtw->ceq_fk)
		//{
		//	if(aRDBDataPoint[pBI->MeasureTypeID][16] != -1) 
		//	{
		//		pdata->transBI[aRDBDataPoint[pBI->MeasureTypeID][16]].pointId = pBI->Position;
		//		pdata->transBI[aRDBDataPoint[pBI->MeasureTypeID][16]].data = 0;

		//		_tcscpy_s(pdata->transBI[aRDBDataPoint[pBI->MeasureTypeID][16]].szname, pBI->IndexName);
		//	}
		//}
	}

	return TRUE;
}


BOOL CRDBMgr::GetEquipInfoFromTransBankAI(long eqcfk, long dlid, CList<UNITANALOGININFO*, UNITANALOGININFO*>* list)
{
	int nCnt = GetRDBFileListCount(FILE_POWERTRANSFORMER);

	for(int nIndex = 0; nIndex <= nCnt; nIndex++)
	{
		LPST_COMMON_POWERTRANSFORMER pUnit = (LPST_COMMON_POWERTRANSFORMER)&g_pCommonPOWERTRANSFORMER[nIndex];

		int nWinCnt = GetRDBFileListCount(FILE_TRANSFORMERWINDING);

		for(int nWIndex = 1; nWIndex <= nWinCnt; nWIndex++)
		{
			LPST_COMMON_TRANSFORMERWINDING pWind = (LPST_COMMON_TRANSFORMERWINDING)&g_pCommonTRANSFORMERWINDING[nWIndex];
			if(pWind->CEQFK < 1)
				continue;

			if( pUnit->PTRID != pWind->PTRFK)
				continue;

			LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)GetIndexEquip(pWind->CEQFK);
			if(!pequip) return false;

			LPST_COMMON_DISTRIBUTIONLINE pstation  = (LPST_COMMON_DISTRIBUTIONLINE)GetIndexDLine(pequip->DLFK);
			if(!pstation) return false;

			if(pequip->DLFK != dlid || pequip->EQCFK != eqcfk)
				continue;

			//GetAnalogPoint(pequip->ceqid, dlid, 0, list);
		}
	}

	return TRUE;
}
	
BOOL CRDBMgr::GetEquipInfoFromTransBankBO(long eqcfk, long dlid, CList<UNITDIGIINFO*, UNITDIGIINFO*>* list)
{
	int nCnt = GetRDBFileListCount(FILE_POWERTRANSFORMER);

	for(int nIndex = 0; nIndex <= nCnt; nIndex++)
	{
		LPST_COMMON_POWERTRANSFORMER pUnit = (LPST_COMMON_POWERTRANSFORMER)&g_pCommonPOWERTRANSFORMER[nIndex];

		int nWinCnt = GetRDBFileListCount(FILE_TRANSFORMERWINDING);

		for(int nWIndex = 1; nWIndex <= nWinCnt; nWIndex++)
		{
			LPST_COMMON_TRANSFORMERWINDING pWind = (LPST_COMMON_TRANSFORMERWINDING)&g_pCommonTRANSFORMERWINDING[nWIndex];
			if(pWind->CEQFK < 1)
				continue;

			if( pUnit->PTRID != pWind->PTRFK)
				continue;

			LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)GetEquip(pWind->CEQFK);
			if(!pequip) return false;

			LPST_COMMON_DISTRIBUTIONLINE pstation  = (LPST_COMMON_DISTRIBUTIONLINE)GetDLine(pequip->DLFK);
			if(!pstation) return false;

			if(pequip->DLFK != dlid || pequip->EQCFK != eqcfk)
				continue;

			GetCtrlInfo(pequip->CEQID, dlid, 0, list);
		}
	}

	return TRUE;
}
//단선도 사용
BOOL CRDBMgr::GetTieSWInfo(int nDL, CList<TIESWITCH*, TIESWITCH*>* list)
{
	const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_SWITCH);
	for(int icnt = 1; icnt <= iTotal; icnt++)
	{
		LPST_COMMON_SWITCH pSwitch = (LPST_COMMON_SWITCH)CRDBMgr::GetSwitch(icnt);
		LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(pSwitch->CEQFK);
		if(!pequip) return false;

		if((pSwitch->SwitchType == 2 ||  pSwitch->SwitchType == 3) && pequip->DLFK == nDL)
		{
			LPST_COMMON_POWERSYSTEMRESOURCE pPsr = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetIndexPSR(pequip->PSRFK);
			if(!pPsr)continue;

			LPST_COMMON_DISTRIBUTIONLINE pInDL = (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetIndexDLine(nDL);
			if(!pInDL)continue;

			LPST_COMMON_DISTRIBUTIONLINE pOutDL = (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetIndexDLine(nDL);
			if(!pOutDL)continue;

			TIESWITCH* pItem = new TIESWITCH;
			memset(pItem, 0, sizeof(TIESWITCH));
			pItem->nCEQID = pequip->CEQID;
			pItem->nPSRFK = pPsr->PSRTYPEFK;
			pItem->nInDL = nDL;
			pItem->nOutDL = 1; // 방법을 찾아야 함

			_tcscpy_s(pItem->szname, pequip->Name);
			_tcscpy_s(pItem->szInDL, pInDL->Name);
			_tcscpy_s(pItem->szOutDL, pOutDL->Name);

			list->AddTail(pItem);
		}
	}
	
	if(list->GetCount() == 0)
		return FALSE;

	return TRUE;
}

//DB내 설정된 상시연계점을 모두 찾아 리스트 한다
BOOL CRDBMgr::GetAllTieSWInfo(CList<TIESWITCH*, TIESWITCH*>* list)
{
	const int iTotal = CRDBMgr::GetRDBFileListCount(FILE_SWITCH);
	for(int icnt = 1; icnt <= iTotal; icnt++)
	{
		LPST_COMMON_SWITCH pSwitch = (LPST_COMMON_SWITCH)CRDBMgr::GetSwitch(icnt);
		LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(pSwitch->CEQFK);
		if(!pequip) return false;

		if((pSwitch->SwitchType == 2 ||  pSwitch->SwitchType == 3))
		{
			LPST_COMMON_POWERSYSTEMRESOURCE pPsr = (LPST_COMMON_POWERSYSTEMRESOURCE)CRDBMgr::GetIndexPSR(pequip->PSRFK);
			if(!pPsr)continue;

			LPST_COMMON_DISTRIBUTIONLINE pInDL = (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetIndexDLine(pequip->DLFK);
			if(!pInDL)continue;

			LPST_COMMON_DISTRIBUTIONLINE pOutDL = (LPST_COMMON_DISTRIBUTIONLINE)CRDBMgr::GetIndexDLine(pequip->DLFK);
			if(!pOutDL)continue;

			TIESWITCH* pItem = new TIESWITCH;
			memset(pItem, 0, sizeof(TIESWITCH));
			pItem->nCEQID = pequip->CEQID;
			pItem->nPSRFK = pPsr->PSRTYPEFK;
			pItem->nInDL = pequip->DLFK;
			pItem->nOutDL = 1; // 방법을 찾아야 함

			_tcscpy_s(pItem->szname, pequip->Name);
			_tcscpy_s(pItem->szInDL, pInDL->Name);
			_tcscpy_s(pItem->szOutDL, pOutDL->Name);

			list->AddTail(pItem);
		}
	}
	
	if(list->GetCount() == 0)
		return FALSE;

	return TRUE;
}
BOOL CRDBMgr::GetMwDataPoint( int iCeqid, CList<MWPOINTINFO*, MWPOINTINFO*>* list )
{
	int nCircuitNo = 0;

	LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = CRDBMgr::GetIndexEquip(iCeqid);
	if(!pEquip) return FALSE;

	LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pEquip->RUID);
	if(!pDevice) return FALSE;

	LPST_COMMON_RTUMAP pMap = CRDBMgr::GetIndexRTUMap(pDevice->RTUMapId); //이름 찾음
	if(!pMap) return FALSE;
	
	nCircuitNo = pEquip->CircuitNo;
	int nBiCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPBIMAPINDEX);

	for(int i = 1; i <= nBiCnt; i++)
	{
		LPST_COMMON_DNPBIMAPINDEX bi = CRDBMgr::GetDnpBI(i);
		if(bi->RTUMapId == pMap->RTUMapId)
		{
			if( bi->CircuitNo == 0 || bi->CircuitNo == nCircuitNo )
			{			
				MWPOINTINFO* pItem = new MWPOINTINFO;
				memset(pItem, 0, sizeof(MWPOINTINFO));
				pItem->ceqid     = iCeqid;
				pItem->pointid   = bi->MapId;
				pItem->rtumapid  = bi->RTUMapId;
				pItem->position  = bi->Position;
				pItem->pointType = 1;
				pItem->cricuitno = bi->CircuitNo;
				pItem->MeasureTypeID = bi->MeasureTypeID;
				_tcscpy(pItem->szName, bi->IndexName);
				_tcscpy(pItem->upcName, bi->upc_name);
				_tcscpy(pItem->upcTime, bi->upc_uptime);
				_tcscpy(pItem->upcTlq, bi->upc_tlq);

				list->AddTail(pItem);
			}
		}
	}

	int nBoCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPBOMAPINDEX);
	for(int i = 1; i <= nBoCnt; i++)
	{
		LPST_COMMON_DNPBOMAPINDEX bo = CRDBMgr::GetDnpBO(i);
		if(bo->RTUMapId == pMap->RTUMapId)
		{
			if( bo->CircuitNo == 0 || bo->CircuitNo == nCircuitNo )
			{			
				MWPOINTINFO* pItem = new MWPOINTINFO;
				memset(pItem, 0, sizeof(MWPOINTINFO));
				pItem->ceqid     = iCeqid;
				pItem->pointid   = bo->MapId;
				pItem->rtumapid  = bo->RTUMapId;
				pItem->position  = bo->Position;
				pItem->pointType = 2;
				pItem->MeasureTypeID = bo->MeasureTypeID;
				_tcscpy(pItem->szName, bo->IndexName);			
				_tcscpy(pItem->upcTlq, bo->upc_tlq);
				GetBIPointUpcName( pItem );

				list->AddTail(pItem);
			}
		}
	}

	int nAiCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPAIMAPINDEX);
	for(int i = 1; i <= nAiCnt; i++)
	{
		LPST_COMMON_DNPAIMAPINDEX ai = CRDBMgr::GetDnpAI(i);
		if(ai->RTUMapId == pMap->RTUMapId)
		{
			if( ai->CircuitNo == 0 || ai->CircuitNo == nCircuitNo )
			{
				MWPOINTINFO* pItem = new MWPOINTINFO;
				memset(pItem, 0, sizeof(MWPOINTINFO));
				pItem->ceqid     = iCeqid;
				pItem->pointid   = ai->MapId;
				pItem->rtumapid  = ai->RTUMapId;
				pItem->position  = ai->Position;
				pItem->pointType = 3;
				pItem->MeasureTypeID = ai->MeasureTypeID;
				_tcscpy(pItem->szName, ai->IndexName);
				_tcscpy(pItem->upcName, ai->upc_name);
				_tcscpy(pItem->upcTime, ai->upc_uptime);
				_tcscpy(pItem->upcTlq, ai->upc_tlq);

				list->AddTail(pItem);
			}
		}
	}

	int nAoCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPAOMAPINDEX);
	for(int i = 1; i <= nAoCnt; i++)
	{
		LPST_COMMON_DNPAOMAPINDEX ao = CRDBMgr::GetDnpAO(i);
		if(ao->RTUMapId == pMap->RTUMapId)
		{
			if( ao->CircuitNo == 0 || ao->CircuitNo == nCircuitNo )
			{
				MWPOINTINFO* pItem = new MWPOINTINFO;
				memset(pItem, 0, sizeof(MWPOINTINFO));
				pItem->ceqid     = iCeqid;
				pItem->pointid   = ao->MapId;
				pItem->rtumapid  = ao->RTUMapId;
				pItem->position  = ao->Position;
				pItem->pointType = 4;
				pItem->MeasureTypeID = ao->MeasureTypeID;
				_tcscpy(pItem->szName, ao->IndexName);
				_tcscpy(pItem->upcName, ao->upc_name);
				_tcscpy(pItem->upcTime, ao->upc_uptime);
				_tcscpy(pItem->upcTlq, ao->upc_tlq);

				list->AddTail(pItem);
			}
		}
	}

	int nCountCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPCOUNTERMAPINDEX);
	for(int i = 1; i <= nCountCnt; i++)
	{
		LPST_COMMON_DNPCOUNTERMAPINDEX cn = CRDBMgr::GetDnpCOUNTER(i);
		if(cn->RTUMapId == pMap->RTUMapId)
		{
			if( cn->CircuitNo == 0 || cn->CircuitNo == nCircuitNo )
			{
				MWPOINTINFO* pItem = new MWPOINTINFO;
				memset(pItem, 0, sizeof(MWPOINTINFO));
				pItem->ceqid     = iCeqid;
				pItem->pointid   = cn->MapId;
				pItem->rtumapid  = cn->RTUMapId;
				pItem->position  = cn->Position;
				pItem->pointType = 5;
				_tcscpy(pItem->szName, cn->IndexName);
				_tcscpy(pItem->upcName, cn->upc_name);
				_tcscpy(pItem->upcTime, cn->upc_uptime);
				_tcscpy(pItem->upcTlq, cn->upc_tlq);

				list->AddTail(pItem);
			}
		}
	}

	return TRUE;
}

BOOL CRDBMgr::GetCeqToRtu(int iCeqid, int &iRtuId)
{
	LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = CRDBMgr::GetIndexEquip(iCeqid);
	if(!pEquip) return FALSE;

	LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pEquip->RUID);
	if(!pDevice) return FALSE;

	iRtuId = pDevice->RUID;

	return TRUE;
}

BOOL CRDBMgr::GetPointToIndex(int iPtNo, int PtType, int &iRtumap, int &iIndex)
{
	switch(PtType)
	{
	case 1:
		{
			LPST_COMMON_DISCRETE iDis = CRDBMgr::GetIndexDiscrete(iPtNo);
			if(!iDis) return FALSE;

			LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = CRDBMgr::GetIndexEquip(iDis->CEQId);
			if(!pEquip) return FALSE;

			LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pEquip->RUID);
			if(!pDevice) return FALSE;

			iRtumap = pDevice->RTUMapId;
			iIndex = iDis->Position;
		}
		break;
	case 2:
		{
			LPST_COMMON_SETDISCRETE iSetDis = CRDBMgr::GetIndexSetDiscrete(iPtNo);
			if(!iSetDis) return FALSE;

			LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = CRDBMgr::GetIndexEquip(iSetDis->CEQId);
			if(!pEquip) return FALSE;

			LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pEquip->RUID);
			if(!pDevice) return FALSE;

			iRtumap = pDevice->RTUMapId;
			iIndex = iSetDis->Position;
		}
		break;
	case 3:
		{
			LPST_COMMON_MEASUREMENT iMea = CRDBMgr::GetIndexMesurement(iPtNo);
			if(!iMea) return FALSE;

			LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = CRDBMgr::GetIndexEquip(iMea->CEQId);
			if(!pEquip) return FALSE;

			LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pEquip->RUID);
			if(!pDevice) return FALSE;

			iRtumap = pDevice->RTUMapId;
			iIndex = iMea->Position;
		}
		break;
	case 4:
		{
			LPST_COMMON_SETMEASUREMENT iSetMea = CRDBMgr::GetIndexSetMesurement(iPtNo);
			if(!iSetMea) return FALSE;

			LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = CRDBMgr::GetIndexEquip(iSetMea->CEQId);
			if(!pEquip) return FALSE;

			LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pEquip->RUID);
			if(!pDevice) return FALSE;

			iRtumap = pDevice->RTUMapId;
			iIndex = iSetMea->Position;
		}
		break;
	case 5:
		{
			LPST_COMMON_ACCUMULATOR iAcc = CRDBMgr::GetAccumulator(iPtNo);
			if(!iAcc) return FALSE;

			LPST_COMMON_CONDUCTINGEQUIPMENT pEquip = CRDBMgr::GetIndexEquip(iAcc->CEQId);
			if(!pEquip) return FALSE;

			LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pEquip->RUID);
			if(!pDevice) return FALSE;

			iRtumap = pDevice->RTUMapId;
			iIndex = iAcc->Position;
		}
		break;

	default:
		break;
	}

	return TRUE;
}


CString CRDBMgr::TlqToString(unsigned short tlq_id)
{
	CString strTLQ, strMsg;

	if( tlq_id == NORMAL )
	{		
		return strTLQ;
	}

	if( tlq_id & TLQ_CI )
	{		
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 1 ) );	// 제어금지
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 1 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_SI )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 2 ) );	// 스캔금지
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 2 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_AI )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 3 ) );	// 알람금지
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 3 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_EI )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 4 ) );	// 이벤트금지
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 4 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_CS )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 5 ) );	// 점검중
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 5 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_MH )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 6 ) );	// 최고상한치
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 6 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_ML )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 7 ) );	// 최저하한치
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 7 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_HL )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 8 ) );	// 상한치
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 8 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_LL )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 9 ) );	// 하한치
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 9 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_CP )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 10 ) );	// 제어진행중
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 10 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_PS )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 11 ) );	// 포인트선택중
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 11 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_MU )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 12 ) );	// 수동입력
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 12 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_NU )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 13 ) );	// 업데이트불량
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 13 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_ON )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 14 ) );	// 비정상상태
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 14 ) );

		strTLQ.Append( strMsg );
	}
	if( tlq_id & TLQ_OFF )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T("-%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 15 ) );	// 포인트OFFLINE
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 15 ) );

		strTLQ.Append( strMsg );
	}

	return strTLQ;
}


CString CRDBMgr::SelectToQuery( CString strDBName, CString strSPName, CString strTBName )
{
	CString strQuery;

	if( strTBName == FILE_IDENTIFIEDOBJECT )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY MRID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_GEOGRAPHICALREGION )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY GGRID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_SUBGEOGRAPHICALREGION )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY SGRID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_DATAPOINTGROUPCODE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY DPGRPID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_COMPUTERCODE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY COMPUTERID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_PROGRAMCODE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PROGID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_OPERATORCODE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY OPERID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_SWITCHTYPECODE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY TYPEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_CONSTRUCTIONCODE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY CONSTID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_WAVECOMTYPE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY WAVECOMTYPEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_STATEGROUP )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY STATEGRPID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_DATABYTE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY DATABYTEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_STATESET )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY STATESETID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_UNIT )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY UNITID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_SCALEFACTOR )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY SFID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_LIMITCODE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY LIMITID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_LIMITSET )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY LIMITSETID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_EQUIPCOMPANY )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY COMPANYID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_SUBSTATION )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY SSID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_DISTRIBUTIONLINE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY DLID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_BASEVOLTAGE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY BVID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_BASEPOWER )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY BPID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_VOLTAGELEVEL )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY VLID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_PHASE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PHASEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_PROTOCOLTYPE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PROTOCOLTYPEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_EQUIPMENTTYPE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY EQUIPTYPEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_RTUMAP )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY RTUMAPID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_COMMTYPE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY COMMTYPEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_RTUTYPE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY RTUTYPEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_CATEGORYCODE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY CCID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_MEASURETYPEINFO )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY MEASURETYPEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_DNPBIMAPINDEX )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY MAPID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_DNPBOMAPINDEX )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY MAPID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_DNPAIMAPINDEX )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY MAPID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_DNPAOMAPINDEX )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY MAPID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_DNPCOUNTERMAPINDEX )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY MAPID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_RTUDEVICE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY RUID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_CONDUCTINGEQUIPMENT )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY CEQID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_SWITCH )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY SWID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_ACLINESEGMENT )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY ACID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_PERLENGTHSEQUENCEIMPEDANCE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PLSIID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_BUSBARSECTION )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY BBSID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_COMPOSITESWITCH )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY CPSID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_POWERTRANSFORMER )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PTRID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_TRANSFORMERWINDING )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY TRWID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_TAPCHANGER )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY TCID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_TAPREGULATIONSCHEDULE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY TRSCID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_PROTECTIONEQUIPMENT )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PEQID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_RECLOSESEQUENCE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY RSID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_CURRENTRELAY	)
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY CRID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_BATTERYSTORAGE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY BATTID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_GENERATINGUNIT )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY GENID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_GENREGULATIONSCHEDULE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY GRSCID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_WINDTURBINE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY WTID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_PHOTOVOLTAIC )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PVID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_GENUNITOPCOSTCURVE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY GUOCCID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_ENERGYCONSUMER )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY ECRID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_SHUNTCOMPASATOR )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY SCID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_STATICVARCOMPENSATOR )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY SVCID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_POWERSYSTEMRESOURCE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PSRID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_PSRTYPE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PSRTYPEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_EQUIPMENTCONTAINER )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY EQCID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_SYMBOL )
		strQuery.Format( _T("SELECT SYMBOLID, NAME, FILENAME, FILESIZE FROM [%s].[%s].[%s] ORDER BY SYMBOLID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_DASDIAGRAMINFO )
		strQuery.Format( _T("SELECT DASDIAID, NAME, VERSION, EDITOR, BUILDTIME, FILENAME, FILESIZE FROM [%s].[%s].[%s] ORDER BY DASDIAID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_STATIONDIAGRAMINFO )
		strQuery.Format( _T("SELECT STATIONDIAID, NAME, VERSION, EDITOR, BUILDTIME, FILENAME, FILESIZE FROM [%s].[%s].[%s] ORDER BY STATIONDIAID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_DISCRETE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_SETDISCRETE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_MEASUREMENT )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_SETMEASUREMENT )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_ACCUMULATOR )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_CALCULATION )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_POSITION )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY POSITIONID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_WATER )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY WATID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_ACM_APPGROUP )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY ACMAGID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_ACM_MAPINDEX )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY ACMMIID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_ACM_TABLE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY ACMTID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_ACM_TABLEGROUP )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY ACMTGID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_PCS )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PCSID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_MAINTRANSFORMER )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY MTRID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_VIRTUAL_LINE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY VIRTUALLINECEQID"), strDBName, strSPName, strTBName );

	else if( strTBName == FILE_MEMO )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY MMID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_MESSAGE )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY MSGID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_CONSTRUCTION )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY CTRID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_OPERATORASSIGN )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY OPRAID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_WAVE_LIST )
		strQuery.Format( _T("SELECT WAVELISTID, CREATETM, RUID, SAMPRATE, FILENAME, FILESIZE FROM [%s].[%s].[%s] ORDER BY WAVELISTID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_WAVE_FILE )
		strQuery.Format( _T("SELECT WAVEID, CREATETM, RUID, WAVETYPE, FILENAME, FILESIZE FROM [%s].[%s].[%s] ORDER BY WAVEID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_COMPUTERSTATUS )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY COMPUTERID"), strDBName, strSPName, strTBName );
	else if( strTBName == FILE_CALCULATION_RESULT )
		strQuery.Format( _T("SELECT * FROM [%s].[%s].[%s] ORDER BY PID"), strDBName, strSPName, strTBName );

	return strQuery;
}


void CRDBMgr::GetBIPointUpcName( MWPOINTINFO* pItem )
{
	int i;	
	int nBiCnt = HMISHARE_GET_RDBRECORDCOUNT( FILE_DNPBIMAPINDEX );

	for( i = 1; i <= nBiCnt; i++ )
	{
		LPST_COMMON_DNPBIMAPINDEX bi = CRDBMgr::GetDnpBI( i );
		if( bi->RTUMapId == pItem->rtumapid && bi->BO_Position == pItem->position )
		{		
			_tcscpy( pItem->upcName, bi->upc_name   );
			_tcscpy( pItem->upcTime, bi->upc_uptime );
			break;
		}
	}
}


CString CRDBMgr::GetDataPointName( int nCEQID )
{
	CString strDpGrpCode, strDpPrefix, strPointName;
	
	LPST_COMMON_CONDUCTINGEQUIPMENT Ceq = CRDBMgr::GetIndexEquip( nCEQID );
	if( Ceq )
	{
		LPST_COMMON_DATAPOINTGROUPCODE DpGrpCode = CRDBMgr::GetIndexDpGrp( Ceq->DpGrpFK );
		if( DpGrpCode )
		{
			strDpGrpCode.Format( _T("%s"), DpGrpCode->DpGrpCode );
			strDpPrefix .Format( _T("%s"), DpGrpCode->DpPrefixName );
		}
	}	
	
	strPointName.Format(_T("%s/%s%05d"), strDpGrpCode, strDpPrefix, nCEQID );
	return strPointName;
}


CString CRDBMgr::GetCalcPointName( int nPID )
{
	CString strDpGrpCode, strDpPrefix, strPointName;
	
	LPST_COMMON_CALCULATION Calc = CRDBMgr::GetIndexCal( nPID );
	if( Calc )
	{
		LPST_COMMON_DATAPOINTGROUPCODE DpGrpCode = CRDBMgr::GetIndexDpGrp( Calc->DpGrpFK );
		if( DpGrpCode )
		{
			strDpGrpCode.Format( _T("%s"), DpGrpCode->DpGrpCode );
			strDpPrefix .Format( _T("%s"), DpGrpCode->DpPrefixName );
		}
	}	
	
	strPointName.Format(_T("%s/%s%05d"), strDpGrpCode, strDpPrefix, nPID );
	return strPointName;
}


CString CRDBMgr::GetStringComma( float fValue, int nDigit )
{
	CString strValue;
	TCHAR tBuffer[ 20 ] = { 0, };
	strValue.Format( _T("%0.2f"), fValue );
				
	NUMBERFMT fmt = { nDigit, 1, 3, _T("."), _T(","), 1 };
	::GetNumberFormat( NULL, NULL, strValue, &fmt, tBuffer, sizeof( TCHAR ) * 20 );

	strValue.Format( _T("%s"), tBuffer );
	return strValue;
}


CString CRDBMgr::GetACMDataPointName( int nCEQID )
{
	CString strDpGrpCode, strDpPrefix, strPointName;
	
	LPST_COMMON_CONDUCTINGEQUIPMENT Ceq = CRDBMgr::GetIndexEquip( nCEQID );
	if( Ceq )
	{
		LPST_COMMON_DATAPOINTGROUPCODE DpGrpCode = CRDBMgr::GetIndexDpGrp( Ceq->DPGC_ACMFK );
		if( DpGrpCode )
		{
			strDpGrpCode.Format( _T("%s"), DpGrpCode->DpGrpCode );
			strDpPrefix .Format( _T("%s"), DpGrpCode->DpPrefixName );
		}
	}	
	
	strPointName.Format(_T("%s/%s%05d"), strDpGrpCode, strDpPrefix, nCEQID );
	return strPointName;
}


CString CRDBMgr::GetStateSetName( int nRTUMAPID, int nPOSITION, int nVALUE, int nTYPE )
{
	CString strName;
	
	int i;
	int nStateGrp = 0;
	int nCnt = 0; 
		
	if( nTYPE == POINT_TYPE_BO )
	{
		nCnt = HMISHARE_GET_RDBRECORDCOUNT( FILE_DNPBOMAPINDEX );
		for( i = 1; i <= nCnt; i++ )
		{
			LPST_COMMON_DNPBOMAPINDEX BO = CRDBMgr::GetDnpBO( i );
			if( BO->RTUMapId == nRTUMAPID && BO->Position == nPOSITION )
			{		
				nStateGrp = BO->StateGrpId;
				break;
			}
		}
	}
	else if( nTYPE == POINT_TYPE_AO )
	{
		nCnt = HMISHARE_GET_RDBRECORDCOUNT( FILE_DNPAOMAPINDEX );
		for( i = 1; i <= nCnt; i++ )
		{
			LPST_COMMON_DNPAOMAPINDEX AO = CRDBMgr::GetDnpAO( i );
			if( AO->RTUMapId == nRTUMAPID && AO->Position == nPOSITION )
			{		
				nStateGrp = AO->StateGrpId;
				break;
			}
		}
	}
	else
	{
		nCnt = HMISHARE_GET_RDBRECORDCOUNT( FILE_DNPBIMAPINDEX );
		for( i = 1; i <= nCnt; i++ )
		{
			LPST_COMMON_DNPBIMAPINDEX BI = CRDBMgr::GetDnpBI( i );
			if( BI->RTUMapId == nRTUMAPID && BI->Position == nPOSITION )
			{		
				nStateGrp = BI->StateGrpId;
				break;
			}
		}
	}

	nCnt = HMISHARE_GET_RDBRECORDCOUNT( FILE_STATESET );
	for( i = 1; i <= nCnt; i++ )
	{
		LPST_COMMON_STATESET pStateSet = CRDBMgr::GetStateSet( i );
		if( pStateSet->StateGrpId == nStateGrp && pStateSet->Value == nVALUE )
		{
			strName.Format( _T("%s"), pStateSet->Name );
			break;
		}
	}

	return strName;
}


CString CRDBMgr::GetTlqName( int nTlqNum )
{
	CString strTLQ, strMsg;

	if( nTlqNum == NORMAL )
	{	
		strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 16 ) );		// 태그없음
		return strMsg;
	}

	if( nTlqNum & TLQ_CI )
	{		
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T(",%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 17 ) );	// 제어
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 17 ) );

		strTLQ.Append( strMsg );
	}

	if( nTlqNum & TLQ_SI )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T(",%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 18 ) );	// 스캔
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 18 ) );

		strTLQ.Append( strMsg );
	}

	if( nTlqNum & TLQ_AI )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T(",%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 19 ) );	// 알람
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 19 ) );

		strTLQ.Append( strMsg );
	}

	if( nTlqNum & TLQ_EI )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T(",%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 20 ) );	// 이벤트
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 20 ) );

		strTLQ.Append( strMsg );
	}

	if( nTlqNum & TLQ_CS )
	{
		if( strTLQ.GetLength() > 0 )
			strMsg.Format( _T(",%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 21 ) );	// 점검
		else
			strMsg.Format( _T("%s"), g_cfg.GetLangMsg( _T("GLOBAL"), _T("CAP"), 21 ) );

		strTLQ.Append( strMsg );
	}

	return strTLQ;
}


BOOL CRDBMgr::CheckUseControl( int nCEQID, BOOL bMsg )
{
	CString strMsg, strDpGrp1, strDpGrp2, strCEQ_NAME, strGRP_NAME, strP;
	CStringArray arrDpGrp;

	LPST_COMMON_CONDUCTINGEQUIPMENT Ceq = CRDBMgr::GetIndexEquip( nCEQID );
	if( Ceq )
	{
		strDpGrp1  .Format( _T("%d"), Ceq->DpGrpFK );
		strCEQ_NAME.Format( _T("%s"), Ceq->Name );

		LPST_COMMON_DATAPOINTGROUPCODE DpGrpCode = CRDBMgr::GetIndexDpGrp( Ceq->DpGrpFK );
		if( DpGrpCode )		strGRP_NAME.Format( _T("%s"), DpGrpCode->DpGrpName );
	}

	int i;
	int nRet = g_cfg.SplitByPattern( (TCHAR *)(LPCTSTR)g_cfg.m_strCONTROL_POSSIBLE_DPGRP, _T(","), arrDpGrp, g_cfg.m_strCONTROL_POSSIBLE_DPGRP );

	for( i = 0; i < nRet; i++ )
	{
		strDpGrp2 = arrDpGrp.GetAt( i );
		
		if( strDpGrp2 == strDpGrp1 )
			return TRUE;
	}

	if( bMsg )
	{
		// 해당 데이터그룹은 제어를 할수없습니다
		strMsg.Format( _T("[%s: %s]\n%s"), strCEQ_NAME, strGRP_NAME, g_cfg.GetLangMsg( _T("GLOBAL"), _T("MSG"), 1 ) );	
		SkinMsgBox( _T("INFORMATION"), strMsg, MB_ICONINFORMATION, MB_OK );
	}
	
	return FALSE;
}


BOOL CRDBMgr::SetSqlConnect()
{
	CString strDB_CONNECT, strMsg;
	strDB_CONNECT.Format( _T("PROVIDER=SQLNCLI11.1; PERSIST SECURITY INFO=FALSE; USER ID=%s; PASSWORD=%s; INITIAL CATALOG=%s; DATA SOURCE=%s; FAILOVER PARTNER=%s"),
						  g_cfg.m_strDATABASE_DB_USER, g_cfg.m_strDATABASE_DB_PASSWORD, g_cfg.m_strDATABASE_DB_HISTORY, g_cfg.m_strDATABASE_DB_SERVER1, g_cfg.m_strDATABASE_DB_SERVER2 );

	BOOL bConnect = SqlConnect( strDB_CONNECT );
	if( !bConnect )
	{		
		strMsg = g_cfg.GetLangMsg( _T("GLOBAL"), _T("MSG"), 3 );			// DB 연결을 실패했습니다
		SkinMsgBox( _T("INFORMATION"), strMsg, MB_ICONINFORMATION, MB_OK );
		
		return FALSE;
	}

	return TRUE;
}


void CRDBMgr::SetSqlDisconnect()
{
	SqlDisConnect();
}


void CRDBMgr::EndControlProcess()
{
	HWND hWnd = ::FindWindow( NULL, _T("ControlInfoHMI") );
	if( hWnd )
	{
		COPYDATASTRUCT cds;
		memset( &cds, 0x00, sizeof( cds ) );
		cds.dwData = PROCESS_END_MESSAGE;
		
		PDWORD_PTR sResult = 0;
		::SendMessageTimeout( hWnd, WM_COPYDATA, NULL, (LPARAM)&cds, SMTO_NORMAL, 1000, sResult );
	}
}


void CRDBMgr::SendAsyncQue( int nPGID, CString strClientName, CString strLogHMI )
{
	CString strComName, strMsgName, strMsg;
	CHAR MsgName[ 64 ] = { 0, };
		
	int i;
	int nCnt   = HMISHARE_GET_RDBRECORDCOUNT( FILE_COMPUTERCODE );
	int nOP_ID = _ttoi( g_cfg.m_strOPERATOR_OP_ID );
	int nRet   = 0;
		
	// 비동기 패킷헤더 생성 - FunctionCode, Length, SendTime, HMIID, ProgramID, Seq_Con_ID, Count
	ST_SENDHEADER2 *pHeader = new ST_SENDHEADER2;	
	
	// 미들웨어 패킷생성 ( Header: 18 )
	UINT uBuffSize = sizeof( ST_SENDHEADER2 );
	uPCComData v_data( uBuffSize );

	for( i = 1; i <= nCnt; i++ )
	{
		LPST_COMMON_COMPUTERCODE ComCode = CRDBMgr::GetComputer( i );
		if( ComCode->ComputerType == 2 )
		{
			strMsgName = MSG_PREFIX;	//ex) MSG_HMI001_P002
			strComName.Format( _T("%s"), ComCode->ComputerName );
			strMsgName.Append( strComName );
			strMsgName.Append( _T("_") );
			strMsgName.Append( strClientName );
			WideCharToMultiByte( CP_ACP, 0, strMsgName, -1, MsgName, MAX_PATH, NULL, NULL );			
			
			pHeader->usFcode		= FC_CONTROL_UPDATE;
			pHeader->usLength		= sizeof( ST_SENDHEADER );
			CTime time				= CTime::GetCurrentTime();
			pHeader->uiTime			= (UINT)time.GetTime();
			pHeader->uiSeqId		= 1;
			pHeader->usHmiId		= ComCode->ComputerId;			
			pHeader->usProgId		= nPGID;
			pHeader->usCount		= 1;

			CString strMsg, strSTime;
			strSTime.Format( _T("%04d-%02d-%02d %02d:%02d:%02d"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond() );
			strMsg.Format( _T("[CONTROLLOG: PACKET_HEADER: SEND] FC: 0x%04X LEN: %d STIME: %s HMIID: %d PGID: %d SEQID: %d CNT: %d"), 
						   pHeader->usFcode, pHeader->usLength, strSTime, pHeader->usHmiId, pHeader->usProgId, pHeader->uiSeqId, pHeader->usCount );
			
			g_cfg.LogInfo( strLogHMI, strMsg, LOG_FULL );			
			
			// 패킷해더 메모리카피
			BYTE SendBuff[ HMI_COMM_BUFFER ] = { 0, };
			memcpy( SendBuff, pHeader, sizeof( ST_SENDHEADER2 ) );
			v_data.SetDataBuffer( (CHAR *)SendBuff, uBuffSize );

			nRet = uPCClientCom::SendMsgData( MsgName, v_data );
			if( nRet != 0 )		strMsg.Format( _T("[CONTOLLOG: SEND_MSG: FAIL] nRet: %d - %s"), nRet, strMsgName );		
			else				strMsg.Format( _T("[CONTOLLOG: SEND_MSG: SUCCESS] %s"), strMsgName );

			g_cfg.LogInfo( strLogHMI, strMsg, LOG_FULL );
		}
	}

	delete pHeader;
	return;
}


void CRDBMgr::InsertControlLog ( int nCEQID, int nRUID, int nControlType, int nPointType, int nMAPID, float fOldVal, float fSetVal, int nComputerID, CString strOperName, CString strReason )
{
	// Sql 연결
	if( !SetSqlConnect() )
	{
		SetSqlDisconnect();
		return;
	}

	CString strQuery, strMsg, strMapID, strfOldVal, strfSetVal;
	CString strSPName = _T("DBO");
	CString strTBName = _T("HMICONTROLLOG");
	int nGGRID = -1, nSGRID = -1, nSSID = -1, nDLID = -1;
	
	LPST_COMMON_CONDUCTINGEQUIPMENT Ceq = CRDBMgr::GetIndexEquip( nCEQID );
	if( Ceq )
	{
		nSSID = Ceq->SSFK;
		nDLID = Ceq->DLFK;

		LPST_COMMON_SUBSTATION SubSta = CRDBMgr::GetIndexSubStation( nSSID );
		if( SubSta )
		{
			nSGRID = SubSta->SGRFK;

			LPST_COMMON_SUBGEOGRAPHICALREGION SubGeo = CRDBMgr::GetIndexSubGeoGraphic( nSGRID );
			if( SubGeo )	nGGRID = SubGeo->GGRFK;
		}
	}

	if( nMAPID == 0 )	strMapID = _T("NULL");
	else				strMapID.Format( _T("%d"), nMAPID );

	strfOldVal.Format( _T("%0.2f"), fOldVal );
	strfSetVal.Format( _T("%0.2f"), fSetVal );
		
	COleDateTime   dtCurrDate = COleDateTime::GetCurrentTime();
	strQuery.Format( _T("INSERT INTO [%s].[%s].[%s] VALUES ( ")
					 _T("( SELECT ISNULL( MAX( HCLID ) + 1, 1 ) FROM [%s].[%s].[%s] ), '%s', ")
					 _T("%d, %d, %d, %d, %d, %d, %d, %d, %s, %s, '%s', %d, '%s', %s )"),

					 g_cfg.m_strDATABASE_DB_HISTORY, strSPName, strTBName,
					 g_cfg.m_strDATABASE_DB_HISTORY, strSPName, strTBName, dtCurrDate.Format( _T("%Y-%m-%d %H:%M:%S") ),
					 nGGRID, nSGRID, nSSID, nDLID, nRUID, nCEQID, nControlType, nPointType, strMapID,
					 strfSetVal, strOperName, nComputerID, strReason, strfOldVal
	);

	BOOL bRet = SqlExecuteQuery( strQuery );
	if( !bRet )		
	{
		strMsg = SqlGetError();
		SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
	}

	strMsg.Format( _T("[CEQID: %d] [RUID: %d] [CTYPE: %d] [PTYPE: %d] [MAPID: %d] [OldVal: %s] [SetVal: %s] [COM: %d] [OperName: %s] [Reason: %s]"),
				   nCEQID, nRUID, nControlType, nPointType, nMAPID, strfOldVal, strfSetVal, nComputerID, strOperName, strReason );

	g_cfg.LogInfo( CONTROLINFO_HMI, strMsg, LOG_FULL );
	SetSqlDisconnect();

	return;
}


void CRDBMgr::InsertControlLog2 ( int nCEQID, int nRUID, int nControlType, int nPointType, int nMAPID, float fOldVal, float fSetVal, int nComputerID, CString strOperName, CString strReason )
{	
	CString strQuery, strMsg, strMapID, strfOldVal, strfSetVal;
	CString strSPName = _T("DBO");
	CString strTBName = _T("HMICONTROLLOG");
	int nGGRID = -1, nSGRID = -1, nSSID = -1, nDLID = -1;
	
	LPST_COMMON_CONDUCTINGEQUIPMENT Ceq = CRDBMgr::GetIndexEquip( nCEQID );
	if( Ceq )
	{
		nSSID = Ceq->SSFK;
		nDLID = Ceq->DLFK;

		LPST_COMMON_SUBSTATION SubSta = CRDBMgr::GetIndexSubStation( nSSID );
		if( SubSta )
		{
			nSGRID = SubSta->SGRFK;

			LPST_COMMON_SUBGEOGRAPHICALREGION SubGeo = CRDBMgr::GetIndexSubGeoGraphic( nSGRID );
			if( SubGeo )	nGGRID = SubGeo->GGRFK;
		}
	}

	if( nMAPID == 0 )	strMapID = _T("NULL");
	else				strMapID.Format( _T("%d"), nMAPID );

	strfOldVal.Format( _T("%0.2f"), fOldVal );
	strfSetVal.Format( _T("%0.2f"), fSetVal );
		
	COleDateTime   dtCurrDate = COleDateTime::GetCurrentTime();
	strQuery.Format( _T("INSERT INTO [%s].[%s].[%s] VALUES ( ")
					 _T("( SELECT ISNULL( MAX( HCLID ) + 1, 1 ) FROM [%s].[%s].[%s] ), '%s', ")
					 _T("%d, %d, %d, %d, %d, %d, %d, %d, %s, %s, '%s', %d, '%s', %s )"),

					 g_cfg.m_strDATABASE_DB_HISTORY, strSPName, strTBName,
					 g_cfg.m_strDATABASE_DB_HISTORY, strSPName, strTBName, dtCurrDate.Format( _T("%Y-%m-%d %H:%M:%S") ),
					 nGGRID, nSGRID, nSSID, nDLID, nRUID, nCEQID, nControlType, nPointType, strMapID,
					 strfSetVal, strOperName, nComputerID, strReason, strfOldVal
	);

	BOOL bRet = SqlExecuteQuery( strQuery );
	if( !bRet )		
	{
		strMsg = SqlGetError();
		SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
	}

	strMsg.Format( _T("[CEQID: %d] [RUID: %d] [CTYPE: %d] [PTYPE: %d] [MAPID: %d] [OldVal: %s] [SetVal: %s] [COM: %d] [OperName: %s] [Reason: %s]"),
				   nCEQID, nRUID, nControlType, nPointType, nMAPID, strfOldVal, strfSetVal, nComputerID, strOperName, strReason );

	g_cfg.LogInfo( CONTROLINFO_HMI, strMsg, LOG_FULL );
	return;
}


void CRDBMgr::InsertAlarmAck( int nCEQID, CString strCreateTime, CString strContents, CString strAckUser, int nIMPORTANT, CString strHMIId )
{	
	// Sql 연결
	if( !SetSqlConnect() )
	{
		SetSqlDisconnect();
		return;
	}

	CString strQuery, strMsg;
	CString strSPName = _T("DBO");
	CString strTBName = _T("HMIALARMACK");
	int nSSID = -1, nDLID = -1, nDPGRP = -1;
	
	LPST_COMMON_CONDUCTINGEQUIPMENT Ceq = CRDBMgr::GetIndexEquip( nCEQID );
	if( Ceq )
	{
		nSSID  = Ceq->SSFK;
		nDLID  = Ceq->DLFK;
		nDPGRP = Ceq->DpGrpFK;
	}

	COleDateTime   dtCurrDate = COleDateTime::GetCurrentTime();
	strQuery.Format( _T("INSERT INTO [%s].[%s].[%s] VALUES ( ")
					 _T("( SELECT ISNULL( MAX( ACKID ) + 1, 1 ) FROM [%s].[%s].[%s] ), '%s', ")
					 _T("%d, %d, %d, '%s', '%s', '%s', %d, %d )"),

					 g_cfg.m_strDATABASE_DB_HISTORY, strSPName, strTBName,
					 g_cfg.m_strDATABASE_DB_HISTORY, strSPName, strTBName, strCreateTime,
					 nSSID, nDLID, nCEQID, strContents, strAckUser, dtCurrDate.Format( _T("%Y-%m-%d %H:%M:%S") ), 
					 nIMPORTANT, _ttoi(strHMIId)
	);

	BOOL bRet = SqlExecuteQuery( strQuery );
	if( !bRet )		
	{
		strMsg = SqlGetError();
		SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
	}

	strMsg.Format( _T("[CEQID: %d] [CREATTIME: %s] [CONTENTS: %s] [ACKUSER: %s] [ACKTIME: %s]"),
				   nCEQID, strCreateTime, strContents, strAckUser, dtCurrDate.Format( _T("%Y-%m-%d %H:%M:%S") ) );

	g_cfg.LogInfo( TOTALINFO_HMI, strMsg, LOG_FULL );
	SetSqlDisconnect();

	return;
}


int CRDBMgr::GetPointMapId( int nCEQID, int nControlType, int nPosition )
{
	int i;
	int nMapId = 0;
	int nCnt   = 0;		

	LPST_COMMON_CONDUCTINGEQUIPMENT Ceq = CRDBMgr::GetIndexEquip( nCEQID );
	if( Ceq )
	{
		LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice( Ceq->RUID );
		if( pDevice )
		{
			if( nControlType == CONTROL_TYPE_BO )
			{
				nCnt = HMISHARE_GET_RDBRECORDCOUNT( FILE_DNPBOMAPINDEX );
				for( i = 1; i <= nCnt; i++ )
				{
					LPST_COMMON_DNPBOMAPINDEX BO_INDEX = CRDBMgr::GetDnpBO(i);
					if( BO_INDEX->RTUMapId == pDevice->RTUMapId && BO_INDEX->Position == nPosition )
					{
						nMapId = BO_INDEX->MapId;
						break;
					}
				}
			}
			else if( nControlType == CONTROL_TYPE_AO )
			{
				nCnt = HMISHARE_GET_RDBRECORDCOUNT( FILE_DNPAOMAPINDEX );
				for( i = 1; i <= nCnt; i++ )
				{
					LPST_COMMON_DNPAOMAPINDEX AO_INDEX = CRDBMgr::GetDnpAO(i);
					if( AO_INDEX->RTUMapId == pDevice->RTUMapId && AO_INDEX->Position == nPosition )
					{
						nMapId = AO_INDEX->MapId;
						break;
					}
				}
			}
		}
	}

	return nMapId;
}


int CRDBMgr::CheckTlqPsLock( int nCEQID, int nControlType, int nMapId )
{
	int nRet = -1;
	CString strUpcTlq, strRtuname, strMsg;
	CHAR rtuName  [ 128 ] = { 0, };
	CHAR pointName[ 128 ] = { 0, };

	if( nControlType == CONTROL_TYPE_BO )
	{
		LPST_COMMON_DNPBOMAPINDEX pIndex = CRDBMgr::GetIndexDnpBO( nMapId );	
		if( pIndex )
		{
			strUpcTlq.Format( _T("%s"), pIndex->upc_tlq );
		}
	}
	else if( nControlType == CONTROL_TYPE_AO )
	{
		LPST_COMMON_DNPAOMAPINDEX pIndex = CRDBMgr::GetIndexDnpAO( nMapId );	
		if( pIndex )
		{
			strUpcTlq.Format( _T("%s"), pIndex->upc_tlq );
		}
	}
	else
		return -1;
		
	strRtuname = CRDBMgr::GetDataPointName( nCEQID );
	WideCharToMultiByte( CP_ACP, 0, strRtuname, -1, rtuName, MAX_PATH, NULL, NULL );
		
	uPCComData	uPcRtdata;	
	nRet = uPCClientCom::GetDataPoint( rtuName, uPcRtdata );

	if( nRet != 0 )
	{
		//strMsg = g_cfg.GetLangMsg( _T("GENUNITINFO"), _T("MSG"), 4 );				// 미들웨어 GetDataPoint 데이터 획득실패
		//SkinMsgBox( _T("INFORMATION"), strMsg, MB_ICONINFORMATION, MB_OK );
		
		return -1;
	}
	
	WideCharToMultiByte( CP_ACP, 0, strUpcTlq, -1, pointName, MAX_PATH, NULL, NULL );

	if(!strcmp(pointName, ""))
		return -1;

	unsigned short* sVal = (unsigned short *)uPcRtdata.GetValue( pointName );
	if( sVal )
	{
		int nVal = *sVal;

		// PS LOCK이 걸린 상태
		if( ( *sVal != NORMAL ) && ( *sVal & TLQ_PS ) )
			return 1;
	}	

	return 0;
}


int CRDBMgr::CheckControlPriority()
{
	CString strMsg1, strMsg2;
	int nOP_ID = _ttoi( g_cfg.m_strOPERATOR_OP_ID );

	LPST_COMMON_OPERATORCODE pOperCode = CRDBMgr::GetIndexOpCode( nOP_ID );	
	if( pOperCode )	
	{
		if( pOperCode->ConAuth == 1 )
			return 0;	
	}

	strMsg1 = g_cfg.GetLangMsg( _T("GLOBAL"), _T("MSG"), 2 );				// 해당 사용자는 제어권한이 없습니다
	strMsg2.Format( _T("[%s]\n%s"), g_cfg.m_strOPERATOR_OP_NAME, strMsg1 );
	SkinMsgBox( _T("INFORMATION"), strMsg2, MB_ICONINFORMATION, MB_OK );
	
	return -1;
}


CPoint CRDBMgr::GetMonitorCenterPoint( HWND hWnd )
{
	MONITORINFOEX MonInfo;
	memset(&MonInfo, 0, sizeof(MONITORINFOEX));
	MonInfo.cbSize = sizeof(MonInfo);

	// Monitor Handle
	HMONITOR monitor = MonitorFromWindow( hWnd, MONITOR_DEFAULTTONEAREST);
	GetMonitorInfo(monitor,&MonInfo);

	CPoint pPoint;
	pPoint.x = ((MonInfo.rcMonitor.right-MonInfo.rcMonitor.left)/2)+MonInfo.rcMonitor.left;
	pPoint.y = MonInfo.rcMonitor.bottom/2;
	
	return pPoint;
}


BOOL CRDBMgr::CreateSharedDB()
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 데이터베이스 쿼리 및 공유 메모리 생성
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	::CoInitialize( NULL );
	HMISHARE_CREATE();

	for( int i= 0 ; i < _countof(_tTableName); i++ )
	{
		CString strQuery;
		CString strSPName = _T("DBO");
		CString strTBName = (TCHAR*)(LPCTSTR)_tTableName[i]; 
		
		// MIDAS_COMMON
		if( i < MIDAS_OPR_START )
		{
			strQuery = SelectToQuery( g_cfg.m_strDATABASE_DB_COMMON, strSPName, strTBName );
		}
		// MIDAS_OPR
		else	
		{
			strQuery = SelectToQuery( g_cfg.m_strDATABASE_DB_OPER, strSPName, strTBName );
		}

		CPtrArray *ptrArray = new CPtrArray;

		int nRet = SqlSelectQuery( strQuery, ptrArray );
		LONG nCount =  ptrArray->GetCount();
		
		if( nRet <  0 )
		{	
			CString strMsg = SqlGetError();
			g_cfg.LogInfo( MAININFO_HMI, strMsg, LOG_INFO );
			SqlDelPtrArray( ptrArray );			
			
			SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );		
			return FALSE;
		}
		else if(nRet == 0)
		{
			CString result;
			result.Format( _T("%s - 데이터 없음"), strTBName );
			g_cfg.LogInfo( MAININFO_HMI, result, LOG_INFO );
			SqlDelPtrArray( ptrArray );
			
			continue;
		}
		else
		{
			CString result;
			result.Format (_T("%s - 데이터 쿼리성공(%d)"), strTBName, nRet );
			g_cfg.LogInfo( MAININFO_HMI, result, LOG_INFO );
		}

		if( HMISHARE_ALLOC_RDBMEM(_tTableName[i], nCount) < 0 )
		{
			CString strMsg;
			strMsg.Format(_T("%s - 공유메모리생성실패(Rec:%d)"), _tTableName[i], nCount);			
			g_cfg.LogInfo( MAININFO_HMI, strMsg, LOG_INFO );
			SqlDelPtrArray( ptrArray );

			SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
			return FALSE;
		}


		for( int index = 0; index < nCount; index++ )
		{
			CStringArray *strArray = new CStringArray;
			strArray->Copy(*(CStringArray *)ptrArray->GetAt(index));

			if( HMISHARE_INSERT_MEM(_tTableName[i], index+1, strArray) < 0 ) //0 메모리는 사용 안함 
			{
				CString strMsg;
				strMsg.Format(_T("%s - 공유메모리 데이터 입력 실패(Rec:%d)"), _tTableName[i], nCount);
				g_cfg.LogInfo( MAININFO_HMI, strMsg, LOG_INFO);				
				delete strArray;

				SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
				return FALSE;
			}

			delete strArray;
		}

		SqlDelPtrArray( ptrArray );		
	}

	return TRUE;
}

BOOL CRDBMgr::UpdateSharedDB(TCHAR *tFileName)
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 테이블별 공유 메모리 해제 및 데이터베이스 쿼리 공유메모리 재생성
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	::CoInitialize( NULL );
	
	for( int i= 0 ; i < _countof(_tTableName); i++ )
	{
		if( _tcscmp(_tTableName[i], tFileName) != 0 )
			continue;

		CString strQuery;
		CString strSPName = _T("DBO");
		CString strTBName = (TCHAR*)(LPCTSTR)_tTableName[i]; 
		
		// MIDAS_COMMON
		if( i < MIDAS_OPR_START )
		{
			strQuery = SelectToQuery( g_cfg.m_strDATABASE_DB_COMMON, strSPName, strTBName );
		}
		// MIDAS_OPR
		else	
		{
			strQuery = SelectToQuery( g_cfg.m_strDATABASE_DB_OPER, strSPName, strTBName );			
		}

		CPtrArray *ptrArray = new CPtrArray;

		int nRet = SqlSelectQuery( strQuery, ptrArray );
		LONG nCount =  ptrArray->GetCount();
		
		if( nRet <  0 )
		{
			CString strMsg = SqlGetError();			
			g_cfg.LogInfo( MAININFO_HMI, strMsg, LOG_INFO );
			SqlDelPtrArray( ptrArray );

			SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
			return FALSE;
		}
		else if(nRet == 0)
		{
			CString result;
			result.Format(_T("%s - 데이터 없음"), strTBName);
			g_cfg.LogInfo( MAININFO_HMI, result, LOG_INFO );
			//SqlDelPtrArray( ptrArray );
			
			//continue;
		}
		else
		{
			CString result;
			result.Format(_T("%s - 데이터 쿼리성공(%d)"), strTBName, nRet);
			g_cfg.LogInfo( MAININFO_HMI, result, LOG_INFO );
		}

		
		if( HMISHARE_REALLOC_RDBMEM(_tTableName[i], nCount) < 0 )
		{
			CString strMsg;
			strMsg.Format(_T("%s - 공유메모리생성실패(Rec:%d)"), _tTableName[i], nCount);			
			g_cfg.LogInfo( MAININFO_HMI, strMsg, LOG_INFO );
			SqlDelPtrArray( ptrArray );

			SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
			return FALSE;
		}
		
		
		for(int index = 0; index < nCount; index++)
		{
			CStringArray *strArray = new CStringArray;
			strArray->Copy(*(CStringArray *)ptrArray->GetAt(index));

			if( HMISHARE_INSERT_MEM(_tTableName[i], index+1, strArray) < 0 ) //0 메모리는 사용 안함 
			{
				CString strMsg;
				strMsg.Format(_T("%s - 공유메모리 데이터 입력 실패(Rec:%d)"), _tTableName[i], nCount);				
				g_cfg.LogInfo( MAININFO_HMI, strMsg, LOG_INFO );
				delete strArray;

				SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
				return FALSE;
			}

			delete strArray;
		}


		HMISHARE_INDEX_MEM();


		


		SqlDelPtrArray( ptrArray );		
	}

	return TRUE;
}

BOOL CRDBMgr::AllUpdateSharedDB()
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 테이블별 공유 메모리 해제 및 데이터베이스 쿼리 공유메모리 재생성
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	::CoInitialize( NULL );
	
	for(int i= 0 ; i < _countof(_tTableName); i++)
	{

		CString strQuery;
		CString strSPName = _T("DBO");
		CString strTBName = (TCHAR*)(LPCTSTR)_tTableName[i];
	
		// MIDAS_COMMON
		if( i < MIDAS_OPR_START )
		{
			strQuery = SelectToQuery( g_cfg.m_strDATABASE_DB_COMMON, strSPName, strTBName );
		}
		// MIDAS_OPR
		else	
		{
			strQuery = SelectToQuery( g_cfg.m_strDATABASE_DB_OPER, strSPName, strTBName );			
		}

		CPtrArray *ptrArray = new CPtrArray;

		int nRet = SqlSelectQuery( strQuery, ptrArray );
		LONG nCount =  ptrArray->GetCount();
		
		if( nRet <  0 )
		{	
			CString strMsg = SqlGetError();			
			g_cfg.LogInfo( MAININFO_HMI, strMsg, LOG_INFO );
			SqlDelPtrArray( ptrArray );

			SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
			return FALSE;
		}
		else if(nRet == 0)
		{
			CString result;
			result.Format(_T("%s - 데이터 없음"), strTBName);
			g_cfg.LogInfo( MAININFO_HMI, result, LOG_INFO );
			SqlDelPtrArray( ptrArray );
			
			continue;
		}
		else
		{
			CString result;
			result.Format(_T("%s - 데이터 쿼리성공(%d)"), strTBName, nRet);
			g_cfg.LogInfo( MAININFO_HMI, result, LOG_INFO );
		}

		if( HMISHARE_REALLOC_RDBMEM(_tTableName[i], nCount) < 0 )
		{
			CString strMsg;
			strMsg.Format(_T("%s - 공유메모리생성실패(Rec:%d)"), _tTableName[i], nCount);			
			g_cfg.LogInfo( MAININFO_HMI, strMsg, LOG_INFO );
			SqlDelPtrArray( ptrArray );

			SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
			return FALSE;
		}


		for(int index = 0; index < nCount; index++)
		{
			CStringArray *strArray = new CStringArray;
			strArray->Copy(*(CStringArray *)ptrArray->GetAt(index));

			if( HMISHARE_INSERT_MEM(_tTableName[i], index+1, strArray) < 0 ) //0 메모리는 사용 안함 
			{
				CString strMsg;
				strMsg.Format(_T("%s - 공유메모리 데이터 입력 실패(Rec:%d)"), _tTableName[i], nCount);				
				g_cfg.LogInfo( MAININFO_HMI, strMsg, LOG_INFO );
				delete strArray;

				SkinMsgBox( _T("ERROR"), strMsg, MB_ICONERROR, MB_OK );
				return FALSE;
			}

			delete strArray;
		}

		SqlDelPtrArray( ptrArray );
		
	}

	return TRUE;
}