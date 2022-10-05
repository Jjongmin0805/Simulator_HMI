
///��ȯ�� �ʿ��� ���� �Լ��� �����մϴ�.
#include "stdafx.h"
#include "MwComm.h"

BOOL GetMwBinaryData(uPCComData &m_uPcRtdata, TCHAR* upcReq, int &iRetVal)
{
	CHAR pointName[128]={0,};
 	WideCharToMultiByte(CP_ACP, 0, upcReq, -1, pointName, MAX_PATH, NULL, NULL );
	CHAR typeName[64] = {0,};

	if(!strcmp(pointName, ""))
		return false;

	if(strcmp(m_uPcRtdata.GetTypeName(), "upc_none") == 0)
		return false;

	m_uPcRtdata.GetDataType()->GetTypeNameOfUnitName(pointName, typeName);

	uPCDataType* upc_type = m_uPcRtdata.GetDataType();
	if(upc_type == NULL)
		return false;

	CString value;
	// ����Ʈ ��
	if(!strcmp(typeName, "upc_char") || !strcmp(typeName, "upc_byte"))
	{
		char *cVal = (char*)m_uPcRtdata.GetValue(pointName);	
		if(!cVal)
		{
			return false;
		}
		else
		{
			iRetVal = *cVal;
			return true;
		}
	}
	else if(!strcmp(typeName, "upc_ushort") )
	{
		unsigned short *sVal = (unsigned short*)m_uPcRtdata.GetValue(pointName);
		if(!sVal)
		{
			return false;
		}
		else
		{
			iRetVal = *sVal;
			return true;
		}
	}
	else if(!strcmp(typeName, "upc_time"))
	{
		__time32_t *iVal = (__time32_t *)m_uPcRtdata.GetValue(pointName);
		if(!iVal)
		{
			return false;
		}
		else
		{
			iRetVal = *iVal;
			return true;
		}
	}
	else if(!strcmp(typeName, "upc_uint"))
	{
		unsigned int *iVal = (unsigned int*)m_uPcRtdata.GetValue(pointName);
		if(!iVal)
		{
			return false;
		}
		else
		{
			iRetVal = *iVal;
			return true;
		}
	}

	return false;
}

BOOL GetMwAnalogData(uPCComData &m_uPcRtdata, TCHAR* upcReq, float &fRetVal)
{
	CHAR pointName[128]={0,};
	WideCharToMultiByte(CP_ACP, 0, upcReq, -1, pointName, MAX_PATH, NULL, NULL );
	CHAR typeName[64] = {0,};

	if(!strcmp(pointName, ""))
		return false;

	if(strcmp(m_uPcRtdata.GetTypeName(), "upc_none") == 0)
		return false;
	m_uPcRtdata.GetDataType()->GetTypeNameOfUnitName(pointName, typeName);

	uPCDataType* upc_type = m_uPcRtdata.GetDataType();
	if(upc_type == NULL)
		return false;

	CString value;
	// ����Ʈ ��
	if(!strcmp(typeName, "upc_float"))
	{
		float *fVal = (float*)m_uPcRtdata.GetValue(pointName);
		if(!fVal)
		{
			return false;
		}
		else
		{
			fRetVal = *fVal;
			return true;
		}
	}
	else if(!strcmp(typeName, "upc_char")|| !strcmp(typeName, "upc_byte"))
	{
		char *fVal = (char*)m_uPcRtdata.GetValue(pointName);
		if(!fVal)
		{
			return false;
		}
		else
		{
			fRetVal = *fVal;
			return true;
		}
				
	}
	else if(!strcmp(typeName, "upc_ushort"))
	{
		unsigned short *fVal = (unsigned short*)m_uPcRtdata.GetValue(pointName);
		if(!fVal)
		{
			return false;
		}
		else
		{
			fRetVal = *fVal;
			return true;
		}
	}
	else if(!strcmp(typeName, "upc_uint"))
	{
		unsigned int *fVal = (unsigned int*)m_uPcRtdata.GetValue(pointName);
		if(!fVal)
		{
			return false;
		}
		else
		{
			fRetVal = *fVal;
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------------------------
// �̵���� ���� ����Ʈ ���� ���� ����
//------------------------------------------------------------------------------
//����
//int ret = 0;
//uPCComData	m_uPcRtdata;
//if((ret = uPCClientCom::GetDataPoint("DL/ga00013", m_uPcRtdata)) != 0)
//{
//	g_cfg.LogInfo ( _T("MwTestDlg"),_T("�̺�Ʈ ������ ����"), 1);
//}
//int vret = 0;
//USHORT tlq = 0;
//UINT tTime = 0;
//int aa = CMwComm::GetMwBIValue(m_uPcRtdata, 307, vret, tlq, tTime);
//time_t atime = (time_t)tTime;

//float fret = 0;
//int bb = CMwComm::GetMwAXValue(m_uPcRtdata, ENUM_MW_TP_AI, 4641, fret, tlq, tTime);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// BI ����Ʈ �̵���� �� ���� �Լ�
// m_uPcRtdata : RTU ���°� ����ü
// POINTNO : Discrete ���̺� PID
// Return true - ����, false - ����
//	iResult : ���°�
//  tlq : ����Ʈ TLQ
//  iTime : ����Ʈ ������Ʈ Ÿ��(time_t)
//------------------------------------------------------------------------------
BOOL CMwComm::GetMwBIValue( uPCComData &m_uPcRtdata, UINT POINTNO, int& iResult, USHORT& tlq, UINT& iTime )
{
	LPST_COMMON_DISCRETE pDiscrete = CRDBMgr::GetIndexDiscrete(POINTNO);
	if(!pDiscrete) return false;

	LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pDiscrete->RUID);
	if(!pDevice) return false;

	INT iMap = pDevice->RTUMapId;
	INT iPos = pDiscrete->Position;

	int nBiCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPBIMAPINDEX);
 	for(int i = 1; i <= nBiCnt; i++)
	{
		LPST_COMMON_DNPBIMAPINDEX pBi = (LPST_COMMON_DNPBIMAPINDEX)CRDBMgr::GetDnpBI(i);
		if(pBi->RTUMapId == iMap && pBi->Position == iPos )
		{
			int iRet = 0;
			if(!GetMwBinaryData(m_uPcRtdata, pBi->upc_name, iRet))
				return false;

			iResult = iRet;

			iRet = 0;
			GetMwBinaryData(m_uPcRtdata, pBi->upc_tlq, iRet);
			tlq = (USHORT)iRet;

			iRet = 0;
			GetMwBinaryData(m_uPcRtdata, pBi->upc_uptime, iRet);
			iTime = (time_t)iRet;

			return true;
		}
	}

	return false;
}
//------------------------------------------------------------------------------
// BI ����Ʈ �̵���� �� ���� �Լ�
// m_uPcRtdata : RTU ���°� ����ü
// MapId : RTUMAP index id
// Position : DNP BI MAP INDEX ���̺� PID
// Return true - ����, false - ����
//	iResult : ���°�
//  tlq : ����Ʈ TLQ
//  iTime : ����Ʈ ������Ʈ Ÿ��(time_t)
//------------------------------------------------------------------------------
BOOL CMwComm::GetMwBIValue2( uPCComData &m_uPcRtdata, UINT MapId, UINT Position, int& iResult, USHORT& tlq, UINT& iTime )
{
	int nBiCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPBIMAPINDEX);
	for(int i = 1; i <= nBiCnt; i++)
	{
		LPST_COMMON_DNPBIMAPINDEX pBi = (LPST_COMMON_DNPBIMAPINDEX)CRDBMgr::GetDnpBI(i);
		if(pBi->RTUMapId == MapId && pBi->Position == Position )
		{
			int iRet = 0;
			if(!GetMwBinaryData(m_uPcRtdata, pBi->upc_name, iRet))
				return false;

			iResult = iRet;

			iRet = 0;
			GetMwBinaryData(m_uPcRtdata, pBi->upc_tlq, iRet);
			tlq = (USHORT)iRet;

			iRet = 0;
			GetMwBinaryData(m_uPcRtdata, pBi->upc_uptime, iRet);
			iTime = (time_t)iRet;

			return true;
		}
	}

	return false;
}
//------------------------------------------------------------------------------
// AI ����Ʈ �̵���� �� ���� �Լ�
// m_uPcRtdata : RTU ���°� ����ü
// MapId : RTUMAP index id
// Position : DNP AI MAP INDEX ���̺� PID
// Return true - ����, false - ����
//	iResult : ���°�
//  tlq : ����Ʈ TLQ
//  iTime : ����Ʈ ������Ʈ Ÿ��(time_t)
//------------------------------------------------------------------------------
BOOL CMwComm::GetMwAIValue( uPCComData &m_uPcRtdata, UINT MapId, UINT Position, float& fResult, USHORT& tlq, UINT& iTime )
{
	int nAiCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPAIMAPINDEX);
	for(int i = 1; i <= nAiCnt; i++)
	{
		LPST_COMMON_DNPAIMAPINDEX pAi = (LPST_COMMON_DNPAIMAPINDEX)CRDBMgr::GetDnpAI(i);
		if(pAi->RTUMapId == MapId && pAi->Position == Position )
		{
			float fRet = 0;
			if(!GetMwAnalogData(m_uPcRtdata, pAi->upc_name, fRet))
				return false;

			fResult = fRet;

			int iRet = 0;
			GetMwBinaryData(m_uPcRtdata, pAi->upc_tlq, iRet);
			tlq = (USHORT)iRet;

			iRet = 0;
			GetMwBinaryData(m_uPcRtdata, pAi->upc_uptime, iRet);
			iTime = (time_t)iRet;
			return true;
		}
	}

	return false;
}
//------------------------------------------------------------------------------
// AO ����Ʈ �̵���� �� ���� �Լ�
// m_uPcRtdata : RTU ���°� ����ü
// MapId : RTUMAP index id
// Position : DNP AO MAP INDEX ���̺� PID
// Return true - ����, false - ����
//	iResult : ���°�
//  tlq : ����Ʈ TLQ
//  iTime : ����Ʈ ������Ʈ Ÿ��(time_t)
//------------------------------------------------------------------------------
BOOL CMwComm::GetMwAOValue( uPCComData &m_uPcRtdata, UINT MapId, UINT Position, float& fResult, USHORT& tlq, UINT& iTime )
{
	int nAoCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPAOMAPINDEX);
	for(int i = 1; i <= nAoCnt; i++)
	{
		LPST_COMMON_DNPAOMAPINDEX pAo = (LPST_COMMON_DNPAOMAPINDEX)CRDBMgr::GetDnpAO(i);
		if(pAo->RTUMapId == MapId && pAo->Position == Position )
		{
			float fRet = 0;
			if(!GetMwAnalogData(m_uPcRtdata, pAo->upc_name, fRet))
				return false;

			fResult = fRet;

			int iRet = 0;
			GetMwBinaryData(m_uPcRtdata, pAo->upc_tlq, iRet);
			tlq = (USHORT)iRet;

			iRet = 0;
			GetMwBinaryData(m_uPcRtdata, pAo->upc_uptime, iRet);
			iTime = (time_t)iRet;
			return true;
		}
	}

	return false;
}
//------------------------------------------------------------------------------
// AI, AO, COUNTER ����Ʈ �̵���� �� ���� �Լ�
// m_uPcRtdata : RTU ���°� ����ü
// POINTNO : AI-Measurement, AO-SetMeasurement, COUNTER-Accumulator ���̺� PID
// Return  true - ����, false - ����
//	fResult : ������
//  tlq : ����Ʈ TLQ
//  iTime : ����Ʈ ������Ʈ Ÿ��(time_t)
//------------------------------------------------------------------------------
BOOL CMwComm::GetMwAXValue( uPCComData &m_uPcRtdata,  ENUM_MW_TPCODE POINTTYPE, UINT POINTNO, float& fResult, USHORT& tlq, UINT& iTime )
{
	if(POINTTYPE == ENUM_MW_TP_AI)
	{
		LPST_COMMON_MEASUREMENT pMea = CRDBMgr::GetIndexMesurement(POINTNO);
		if(!pMea) return false;

		LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pMea->RUID);
		if(!pDevice) return false;

		INT iMap = pDevice->RTUMapId;
		INT iPos = pMea->Position;

		int nAiCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPAIMAPINDEX);

		for(int i = 1; i <= nAiCnt; i++)
		{
			LPST_COMMON_DNPAIMAPINDEX pAi = (LPST_COMMON_DNPAIMAPINDEX)CRDBMgr::GetDnpAI(i);
			if(pAi->RTUMapId == iMap && pAi->Position == iPos )
			{
				float fRet = 0;
				if(!GetMwAnalogData(m_uPcRtdata, pAi->upc_name, fRet))
					return false;

				fResult = fRet;

				int iRet = 0;
				GetMwBinaryData(m_uPcRtdata, pAi->upc_tlq, iRet);
				tlq = (USHORT)iRet;

				iRet = 0;
				GetMwBinaryData(m_uPcRtdata, pAi->upc_uptime, iRet);
				iTime = (time_t)iRet;
				return true;
			}

		}
	}
	else if(POINTTYPE == ENUM_MW_TP_AO)
	{
		LPST_COMMON_SETMEASUREMENT pSet = CRDBMgr::GetIndexSetMesurement(POINTNO);
		if(!pSet) return false;

		LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pSet->RUID);
		if(!pDevice) return false;

		INT iMap = pDevice->RTUMapId;
		INT iPos = pSet->Position;

		int nAoCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPAOMAPINDEX);
		for(int i = 1; i <= nAoCnt; i++)
		{
			LPST_COMMON_DNPAOMAPINDEX pAo = (LPST_COMMON_DNPAOMAPINDEX)CRDBMgr::GetDnpAO(i);
			if(pAo->RTUMapId == iMap && pAo->Position == iPos )
			{
				float fRet = 0;
				if(!GetMwAnalogData(m_uPcRtdata, pAo->upc_name, fRet))
					return false;

				fResult = fRet;

				int iRet = 0;
				GetMwBinaryData(m_uPcRtdata, pAo->upc_tlq, iRet);
				tlq = (USHORT)iRet;

				iRet = 0;
				GetMwBinaryData(m_uPcRtdata, pAo->upc_uptime, iRet);
				iTime = (time_t)iRet;
				return true;
			}

		}
	}
	else if(POINTTYPE == ENUM_MW_TP_PI)
	{
		LPST_COMMON_ACCUMULATOR pAcc = CRDBMgr::GetIndexAccumulator(POINTNO);
		if(!pAcc) return false;

		LPST_COMMON_RTUDEVICE pDevice = CRDBMgr::GetIndexRTUDevice(pAcc->RUID);
		if(!pDevice) return false;

		INT iMap = pDevice->RTUMapId;
		INT iPos = pAcc->Position;

		int nPiCnt = HMISHARE_GET_RDBRECORDCOUNT(FILE_DNPCOUNTERMAPINDEX);
		for(int i = 1; i <= nPiCnt; i++)
		{
			LPST_COMMON_DNPCOUNTERMAPINDEX pPi = (LPST_COMMON_DNPCOUNTERMAPINDEX)CRDBMgr::GetDnpCOUNTER(i);
			if(pPi->RTUMapId == iMap && pPi->Position == iPos )
			{
				float fRet = 0;
				if(!GetMwAnalogData(m_uPcRtdata, pPi->upc_name, fRet))
					return false;

				fResult = fRet;

				int iRet = 0;
				GetMwBinaryData(m_uPcRtdata, pPi->upc_tlq, iRet);
				tlq = (USHORT)iRet;

				iRet = 0;
				GetMwBinaryData(m_uPcRtdata, pPi->upc_uptime, iRet);
				iTime = (time_t)iRet;

				return true;
			}

		}
	}

	return false;
}

BOOL CMwComm::GetMwRtPoint(uPCComData &m_uPcRtdata, int nCEQID, int nDpCode)
{
	if(&m_uPcRtdata == 0) return false;
	CHAR rtuName[128]={0,};
	CString strName;
	int ret = -1;
	CString strPrefix;
	CString	strDpCode;

	LPST_COMMON_DATAPOINTGROUPCODE pDpGrp = (LPST_COMMON_DATAPOINTGROUPCODE)CRDBMgr::GetIndexDpGrp(nDpCode);
	if(!pDpGrp) return false;

	strDpCode.Format(_T("%s"), pDpGrp->DpGrpCode);
	strPrefix.Format(_T("%s"), pDpGrp->DpPrefixName);

	strName.Format(_T("%s/%s%05d"), strDpCode, strPrefix, nCEQID);
	WideCharToMultiByte(CP_ACP, 0, strName, -1, rtuName, MAX_PATH, NULL, NULL );
	if((ret = uPCClientCom::GetDataPoint(rtuName, m_uPcRtdata)) != 0)
	{
		//g_cfg.LogInfo ( _T("MwTestDlg"),_T("����������Ʈ����"), 1);
		return false;
	}

	return true;
}
BOOL CMwComm::GetMwCalPoint(int nPointId, float &fRet)
{
	CString strRTU_NAME, strMsg, strValue;
	CString strUpcName = _T("value");

	CHAR pointName[ 128 ] = { 0, };
	WideCharToMultiByte( CP_ACP, 0, strUpcName, -1, pointName, MAX_PATH, NULL, NULL );


	LPST_COMMON_CALCULATION Calc = CRDBMgr::GetIndexCal( nPointId );
		
	if( !Calc ) return false;

	strRTU_NAME = CRDBMgr::GetCalcPointName( Calc->PID );

	CHAR rtuName[ 128 ] = { 0, };	
	WideCharToMultiByte( CP_ACP, 0, strRTU_NAME, -1, rtuName, MAX_PATH, NULL, NULL );
		
	uPCComData	uPcRtdata;
	
	int nRet = -1;

	nRet = uPCClientCom::GetDataPoint( rtuName, uPcRtdata );

	if( nRet != 0 )
	{
		return false;
	}
			
	strValue = _T("");
			
	if( strcmp(pointName, "") && nRet == 0 )
	{
		float *fVal = (float *)uPcRtdata.GetValue( pointName );
		fRet = *fVal;
	}

	return true;
}
BOOL CMwComm::GetMwCommonData(uPCComData &m_uPcRtdata, int nPointNo, int &iRetVal)
{
	CHAR pointName[128]={0,};
	CHAR typeName[128]={0,};
	WideCharToMultiByte(CP_ACP, 0, g_cfg.m_stDnpPoint[nPointNo].point_name, -1, pointName, MAX_PATH, NULL, NULL );
	WideCharToMultiByte(CP_ACP, 0, g_cfg.m_stDnpPoint[nPointNo].type, -1, typeName, MAX_PATH, NULL, NULL );

	if(!strcmp(pointName, ""))
		return false;

	if(m_uPcRtdata.get_size() == 0)
		return false;
	if(!strcmp(typeName, "upc_char")|| !strcmp(typeName, "upc_byte"))
	{
		char *cVal = (char*)m_uPcRtdata.GetValue(pointName);	
		if(!cVal)
		{
			return false;
		}
		else
		{
			iRetVal = *cVal;
			return true;
		}
				
	}
	else if(!strcmp(typeName, "upc_ushort"))
	{
		unsigned short *sVal = (unsigned short*)m_uPcRtdata.GetValue(pointName);
		if(!sVal)
		{
			return false;
		}
		else
		{
			iRetVal = *sVal;
			return true;
		}
	}
	else if(!strcmp(typeName, "upc_uint"))
	{
		unsigned int *iVal = (unsigned int*)m_uPcRtdata.GetValue(pointName);
		if(!iVal)
		{
			return false;
		}
		else
		{
			iRetVal = *iVal;
			return true;
		}
	}
	return false;
}
BOOL CMwComm::GetMwACMBIValue( uPCComData &m_uPcRtdata,  int nPosition, UINT nDPgroup, int& iResult, UINT& iTime )
{
	int iTotal = HMISHARE_GET_RDBRECORDCOUNT(FILE_ACM_MAPINDEX);
	for(int index = 1; index <= iTotal; index++)
	{
		LPST_COMMON_ACM_MAPINDEX pAcm = CRDBMgr::GetAcmMapIndex(index);
		if(!pAcm) continue;

		if(pAcm->DPGC_ACMFK == nDPgroup && pAcm->Position == nPosition)
		{
			float fRet = 0;
			if(!GetMwBinaryData(m_uPcRtdata, pAcm->upc_name, iResult))
				return false;

			int	iRet = 0;
			GetMwBinaryData(m_uPcRtdata, pAcm->upc_uptime, iRet);
			iTime = (time_t)iRet;

			break;
		}
	}

	return true;
}

BOOL CMwComm::GetMwACMAXValue( uPCComData &m_uPcRtdata,  int nPosition, UINT nDPgroup, float& fResult, UINT& iTime )
{
	int iTotal = HMISHARE_GET_RDBRECORDCOUNT(FILE_ACM_MAPINDEX);
	for(int index = 1; index <= iTotal; index++)
	{
		LPST_COMMON_ACM_MAPINDEX pAcm = CRDBMgr::GetAcmMapIndex(index);
		if(!pAcm) continue;

		if(pAcm->DPGC_ACMFK == nDPgroup && pAcm->Position == nPosition)
		{
			float fRet = 0.0f;
			if(!GetMwAnalogData(m_uPcRtdata, pAcm->upc_name, fResult))
				return false;

			int	iRet = 0;
			GetMwBinaryData(m_uPcRtdata, pAcm->upc_uptime, iRet);
			iTime = (time_t)iRet;

			break;
		}
	}

	return true;
}

BOOL CMwComm::GetCommStatus( int nCEQID, int &iRetVal )
{
	LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(nCEQID);
	if(!pequip) return false;

	LPST_COMMON_DATAPOINTGROUPCODE pDpGrp = (LPST_COMMON_DATAPOINTGROUPCODE)CRDBMgr::GetIndexDpGrp(pequip->DpGrpFK);
	if(!pDpGrp) return false;

	int ret = -1;
	CHAR rtuName[128]={0,};
	CString strDpCode, strPrefix, strName;
	strDpCode.Format(_T("%s"), pDpGrp->DpGrpCode);
	strPrefix.Format(_T("%s"), pDpGrp->DpPrefixName);

	strName.Format(_T("%s/%s%05d"), strDpCode, strPrefix, nCEQID);
	WideCharToMultiByte(CP_ACP, 0, strName, -1, rtuName, MAX_PATH, NULL, NULL );

	uPCComData	m_uPcRtdata;
	if((ret = uPCClientCom::GetDataPoint(rtuName, m_uPcRtdata)) != 0)
	{
		//g_cfg.LogInfo ( _T("MwComm"),_T("����������Ʈ����"), 1);
		return false;
	}

	CHAR pointName[128]={0,};
	CHAR typeName[128]={0,};
	WideCharToMultiByte(CP_ACP, 0, g_cfg.m_stDnpPoint[6].point_name, -1, pointName, MAX_PATH, NULL, NULL ); //��Ż��� 6��
	WideCharToMultiByte(CP_ACP, 0, g_cfg.m_stDnpPoint[6].type, -1, typeName, MAX_PATH, NULL, NULL );

	if(!strcmp(pointName, ""))
		return false;

	if(!strcmp(typeName, "upc_char")|| !strcmp(typeName, "upc_byte"))
	{
		char *cVal = (char*)m_uPcRtdata.GetValue(pointName);	
		if(!cVal)
		{
			return false;
		}
		else
		{
			iRetVal = *cVal;
			return true;
		}
				
	}
	else if(!strcmp(typeName, "upc_ushort"))
	{
		unsigned short *sVal = (unsigned short*)m_uPcRtdata.GetValue(pointName);
		if(!sVal)
		{
			return false;
		}
		else
		{
			iRetVal = *sVal;
			return true;
		}
	}
	else if(!strcmp(typeName, "upc_uint"))
	{
		unsigned int *iVal = (unsigned int*)m_uPcRtdata.GetValue(pointName);
		if(!iVal)
		{
			return false;
		}
		else
		{
			iRetVal = *iVal;
			return true;
		}
	}
	return false;
}

BOOL CMwComm::GetCommRate( int nCEQID, float &fRetVal )
{
	LPST_COMMON_CONDUCTINGEQUIPMENT pequip = (LPST_COMMON_CONDUCTINGEQUIPMENT)CRDBMgr::GetIndexEquip(nCEQID);
	if(!pequip) return false;

	LPST_COMMON_DATAPOINTGROUPCODE pDpGrp = (LPST_COMMON_DATAPOINTGROUPCODE)CRDBMgr::GetIndexDpGrp(pequip->DpGrpFK);
	if(!pDpGrp) return false;

	int ret = -1;
	CHAR rtuName[128]={0,};
	CString strDpCode, strPrefix, strName;
	strDpCode.Format(_T("%s"), pDpGrp->DpGrpCode);
	strPrefix.Format(_T("%s"), pDpGrp->DpPrefixName);

	strName.Format(_T("%s/%s%05d"), strDpCode, strPrefix, nCEQID);
	WideCharToMultiByte(CP_ACP, 0, strName, -1, rtuName, MAX_PATH, NULL, NULL );

	uPCComData	m_uPcRtdata;
	if((ret = uPCClientCom::GetDataPoint(rtuName, m_uPcRtdata)) != 0)
	{
		return false;
	}

	int iTotalCnt = 0;
	int iSuccCnt = 0;
	CHAR pointName[128]={0,};
	CHAR typeName[128]={0,};
	WideCharToMultiByte(CP_ACP, 0, g_cfg.m_stDnpPoint[7].point_name, -1, pointName, MAX_PATH, NULL, NULL ); //�ѽõ� Ƚ��
	WideCharToMultiByte(CP_ACP, 0, g_cfg.m_stDnpPoint[7].type, -1, typeName, MAX_PATH, NULL, NULL );

	if(!strcmp(pointName, ""))
		return false;

	if(!strcmp(typeName, "upc_ushort"))
	{
		unsigned short *sVal = (unsigned short*)m_uPcRtdata.GetValue(pointName);
		if(!sVal)
		{	
			return false;
		}
		else
		{
			iTotalCnt = *sVal;
			if(iTotalCnt == 0)
				return false;
		}
	}
	WideCharToMultiByte(CP_ACP, 0, g_cfg.m_stDnpPoint[8].point_name, -1, pointName, MAX_PATH, NULL, NULL ); //����Ƚ��
	WideCharToMultiByte(CP_ACP, 0, g_cfg.m_stDnpPoint[8].type, -1, typeName, MAX_PATH, NULL, NULL );

	if(!strcmp(pointName, ""))
		return false;

	if(!strcmp(typeName, "upc_ushort"))
	{
		unsigned short *sVal = (unsigned short*)m_uPcRtdata.GetValue(pointName);
		if(!sVal)
		{	
			return false;
		}
		else
		{
			iSuccCnt = *sVal;			
			fRetVal = iSuccCnt / iTotalCnt * 100;
			return true;
		}
	}
	return false;
}