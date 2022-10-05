
#pragma once

///��ȯ�� �ʿ��� ���� �Լ��� �����մϴ�.
#include "Include/uPCGlobalC.h"
#include "../Control/Include/HMIFuncStruct.h"
//-----------------------------------------------------------------------
// Summary:
//     ���뵵 ���α׷� �� ť ��� �ε���
//-----------------------------------------------------------------------
// ��� TPCODE ���
enum ENUM_MW_TPCODE 
{
	 ENUM_MW_TP_BI	= 1,
	 ENUM_MW_TP_BO,
	 ENUM_MW_TP_AI,
	 ENUM_MW_TP_AO,
	 ENUM_MW_TP_PI,
	 ENUM_MW_TP_CAL,
};
class CMwComm
{
public:
	CMwComm(void) {}
	~CMwComm(void) {}

public:
	static BOOL GetMwRtPoint( uPCComData &m_uPcRtdata, int nCEQID, int nDpCode );
	static BOOL GetMwBIValue( uPCComData &m_uPcRtdata, UINT POINTNO, int& iResult, USHORT& tlq, UINT& iTime  );
	static BOOL GetMwBIValue2( uPCComData &m_uPcRtdata, UINT MapId, UINT Position, int& iResult, USHORT& tlq, UINT& iTime );
	static BOOL GetMwAIValue( uPCComData &m_uPcRtdata, UINT MapId, UINT Position, float& fResult, USHORT& tlq, UINT& iTime );
	static BOOL GetMwAOValue( uPCComData &m_uPcRtdata, UINT MapId, UINT Position, float& fResult, USHORT& tlq, UINT& iTime );
	static BOOL GetMwAXValue( uPCComData &m_uPcRtdata, ENUM_MW_TPCODE POINTTYPE, UINT POINTNO, float& fResult, USHORT& tlq, UINT& iTime );
	static BOOL GetMwCommonData(uPCComData &m_uPcRtdata, int nPointNo, int &iRetVal);
	static BOOL GetMwCalPoint(int nPointId, float &fRet);
	static BOOL GetMwACMAXValue( uPCComData &m_uPcRtdata,  int nPosition, UINT nDPgroup, float& fResult, UINT& iTime );
	static BOOL GetMwACMBIValue( uPCComData &m_uPcRtdata, int nPosition, UINT nDPgroup, int& iResult, UINT& iTime  );
	static BOOL	GetCommStatus( int nCEQID, int &iRetVal ); //!< ������ ��Ż��¸� ����
	static BOOL	GetCommRate( int nCEQID, float &fRetVal ); //!< ������ ��Ż��¸� ����
};