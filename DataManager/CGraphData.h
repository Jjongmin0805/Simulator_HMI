#pragma once
#include <afx.h>
class AFX_EXT_CLASS CGraphData :
	public CObject
{

public:
	CGraphData(void);
	~CGraphData(void);


public:
	int m_nAdd;
	int m_nType; ////   0 = dummy, 1 = cbsw , 2 = gen , 3 = svr;
	int m_nGNDIdx[2];
	int m_nGBRIdx; /////// SVR 만본다
	double m_dLen[2];

	int m_nCBSW_idx;
	int m_nGEN_idx;
	int m_nTR_idx;
	int m_nBS_idx[2];

	//////////// PDVR
	double	m_dPDVR_pu_p[2][2]; //////////// 이전 노드;   0 = cur , 1 = cal ;0 = max  , 1 = min 
	double	m_dPDVR_pu_c[2][2]; //////////// 현재 노드
	int		m_nTapChange;

	/////////////////// 고장 전류
	double m_dFault_value[4];

	double m_dRPFO_value[2];

};

typedef CTypedPtrArray<CObArray, CGraphData*> CGraphDataArray;
