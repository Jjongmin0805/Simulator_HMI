#pragma once
#include "afx.h"

class CNode :
	public CObject
{
public:
	CNode(void);
	~CNode(void);

public:
	CString	m_strMRID;
	CString	m_strName;		//���ֹ�ȣ
	CString	m_strNum;		//����ȭ��ȣ
	CString m_strCEQID;
	CString	m_strGENName;

	int		m_nSS;
	int		m_nDL;
	int		m_nKind;		//ADMS Code;
	int		m_nConn;		//����� ������

	int		m_nNDID;
	int		m_nGNDID;

	int		m_nCheck;

	int		m_nSwid;
	int		m_nCeq_Type;
	int		m_nName_Type;

	int    m_genType;
	float  m_fDG_CAPACITY;

	//GEN ������
	float  m_GEN_UIN_fGEN_ITR_CAP;
	float  m_GEN_UIN_fGEN_ITR_R;
	float  m_GEN_UIN_fGEN_ITR_X;
	float  m_GEN_UIN_fGEN_ITR_NGR_R;
	float  m_GEN_UIN_fGEN_ITR_NGR_X;
	int    m_GEN_UIN_nGEN_ITR_WDC;
	int    m_GEN_UIN_nGEN_MACH_TYPE;
	//��
	float  m_HVCUS_fPROMISE_LOAD;
	CString szGEN_DG_TR_MRID;

 


};

typedef CTypedPtrArray<CObArray, CNode*> CNodeArray;
