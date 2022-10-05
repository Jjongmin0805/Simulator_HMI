#pragma once

// KASIM ��Ű�� ���� Ŭ����
class CPKASIM_Schema_VarData
{
public:
	CPKASIM_Schema_VarData(void);		// KASIM ��Ű�� ���� Ŭ���� ������
	~CPKASIM_Schema_VarData(void);			// KASIM ��Ű�� ���� Ŭ���� �Ҹ���

	unsigned int					m_unID;		// ��Ű�� ID
	unsigned int					m_unSize;		// ��Ű�� ũ��
	CPString						m_szName;			// ��Ű�� ��Ī
};

typedef hash_map< int, CPKASIM_Schema_VarData* >							HMAP_SC_VARDATA;