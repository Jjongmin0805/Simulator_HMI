#include "pch.h"
#include "CGraphData.h"


CGraphData::CGraphData()
{
	m_nAdd = 0;
	m_nType = 0; ////   0 = dummy, 1 = cbsw , 2 = gen , 3 = svr;
	m_nGNDIdx[0] = -1;
	m_nGNDIdx[1] = -1;
	m_nGBRIdx = -1; /////// SVR ¸¸º»´Ù
	m_dLen[0] = 0.;
	m_dLen[1] = 0.;

	m_nCBSW_idx = -1;
	m_nGEN_idx = -1;
	m_nTR_idx = -1;
	m_nBS_idx[0] = -1;
	m_nBS_idx[1] = -1;

	//////////// PDVR
	m_dPDVR_pu_p[0][0] = 0.;
	m_dPDVR_pu_p[0][1] = 0.;
	m_dPDVR_pu_p[1][0] = 0.;
	m_dPDVR_pu_p[1][1] = 0.;

	m_nTapChange = 0;
}

CGraphData::~CGraphData()
{

}