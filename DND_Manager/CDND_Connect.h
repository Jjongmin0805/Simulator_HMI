#pragma once
#include "CDND_Object.h"

#define					CONNECT_SELECT_GAP				5.
#define					CONNECT_SELECT_CALCEL_GAP		10.

#define					CONNECT_POS_NORMAL		0
#define					CONNECT_POS_FIRST		1
#define					CONNECT_POS_LAST		2

struct stKASIM_LNsec
{
	int m_nLNSECID;
	int m_nBRID;
	int m_nBR_SI_Fnd;
	int m_nBR_SI_Tnd;
	int m_nBR_Fnd;
	int m_nBR_Tnd;
	int m_nIJID;
	int m_nLDID;
	CString m_nFnd_ceq;
	CString m_nTnd_ceq;

	int m_nBR_Connect_Check;
};



class AFX_EXT_CLASS  CDND_Connect :
	public CDND_Object
{
public:
	CDND_Connect(void);
	~CDND_Connect(void);

	virtual		void					SetObjectData(CMarkup* pxml);
	virtual		void					GetObjectData(CMarkup* pxml, int&  nDrawOrder);

	void								Split_Point(CString strData);
	void								Split_Link(CString strData);

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
		, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));


	virtual		void					Draw_Object_Select(Graphics &graphics, CPoint ptDraw, double dZoomValue
		, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		void					Draw_Object_Move(Graphics &graphics, CPoint ptDraw, double dZoomValue
		, double dScale_x = 1., double dScale_y = 1., double dAngle = 0.);


	virtual		void					Draw_Object_Cancle(Graphics &graphics, CPoint ptDraw, double dZoomValue
		, double dScale_x = 1., double dScale_y = 1., double dAngle = 0.);

	virtual		BOOL					Check2DwawRect(CRect rDraw, double dZoomValue);
	virtual		CDND_Object*			Select2Point(CPoint pt, CDND_Object* pSelect);
	virtual		void					SetEdit_Move(CPoint pt);
	virtual		void					SetEdit_InitData(int nID, CPoint pt, int nResourceID = -1);
	virtual		void					SetEdit_InitData_KASIM(int nLNSEC_ID, int nBR_ID, int nIJ_ID , int nLD_ID);
	virtual		void					Set_NEW_InitData_KASIM(CString stKASIM_NM, CString stCEQID, int nLNSECID, int nBRID, int nIJID, int nLDID, int nFnd, int nTnd );



	void								SetEdit_Split_Add();
	void								SetEdit_Split_Del();

	int									GetLinkPos();

public:


	//
	CString						m_str_link;

	CString						m_str_stroke;
	int							m_n_stroke_width;
	CString						m_str_stroke_type;

	CRealPointArray				m_Array_Point;
	CString						m_strID_From;
	CString						m_strID_To;

	CString						m_strID_CEQ_From;
	CString						m_strID_CEQ_To;

	int							m_nSelect_Index;
	int							m_nSelect_Line;
	int							m_nSelect_Form_Index;
	int							m_nSelect_To_Index;

	

	//
	stKASIM_LNsec				m_st_Kasim_LNsec_Info;
};

