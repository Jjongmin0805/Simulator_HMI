#pragma once



class AFX_EXT_CLASS CWndMsgData
{
public:
	CWndMsgData() ;
	~CWndMsgData() ;

public:
	int					m_nAppl_id;
	int					m_nOption;
	int					m_nEquipType;
	int					m_nIndex;
	CString				m_strData;

	void				SetData(CString strRecvData);
};

