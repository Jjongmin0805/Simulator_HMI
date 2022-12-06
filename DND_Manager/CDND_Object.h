#pragma once
#include <afx.h>
#include "../SB_Manager/CSB_Object.h"

#define						DND_OBJTYPE_BLOCK				1
#define						DND_OBJTYPE_MULTIBLOCK			2
#define						DND_OBJTYPE_CONNECT				3
#define						DND_OBJTYPE_TEXT				4
#define						DND_OBJTYPE_MULTI_M				5

#define						DRAW_ZOOMLEVEL					0.4

#define						DND_OBJ_EDIT_NO					0
#define						DND_OBJ_EDIT_NEW				1
#define						DND_OBJ_EDIT_UPDATE				2
#define						DND_OBJ_EDIT_DELETE				3
#define						DND_OBJ_EDIT_CAL				3

class AFX_EXT_CLASS CDND_Object :
	public CObject
{
public:
	CDND_Object(void);
	~CDND_Object(void);

public:
	int	m_nID;
	int	m_nObjType;
	int	m_nObjEditType;

	void								SetEditType(int nEditType) { m_nObjEditType = nEditType; };
	int									GetEditType() { return m_nObjEditType; };

	virtual		void					SetObjectData(CMarkup* pxml) {};
	virtual		void					GetObjectData(CMarkup* pxml,int& nDrawOrder) {};

	void								ObjectType_Set(int nObjType) { m_nObjType = nObjType; };
	int									ObjectType_Get() { return m_nObjType; };

	CString								Get_ID_Real() { return m_str_id; };

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T("")) {};
	
	virtual		void					Draw_Object_Image(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T("")) {};


	virtual		void					Draw_Object_Select(Graphics &graphics, CPoint ptDraw, double dZoomValue
										, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T("")) {};

	virtual		void					Draw_Object_Select_Move(Graphics &graphics, CPoint ptDraw, double dZoomValue
										, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T("")) {};
	 
	virtual		void					Draw_Object_Select_Cancel(Graphics &graphics, CPoint ptDraw, double dZoomValue
										, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T("")) {};

	virtual		void					Draw_Object_Move(Graphics &graphics, CPoint ptDraw, double dZoomValue
										, double dScale_x = 1., double dScale_y = 1., double dAngle = 0.) {};

	virtual		void					Draw_Object_Cancle(Graphics &graphics, CPoint ptDraw, double dZoomValue
										, double dScale_x = 1., double dScale_y = 1., double dAngle = 0.) {};


	virtual		BOOL					Check2DwawRect(CRect rDraw, double dZoomValue) { return TRUE; };

	virtual		CDND_Object*			Select2Point(CPoint pt,CDND_Object* pSelect) { return NULL; };
	virtual		CDND_Object*			Select2Point_Cancel(CPoint pt, CDND_Object* pSelect) { return NULL; };

	virtual		void					SetEdit_Move(CPoint pt) {};
	virtual		void					SetEdit_Move_Cancel(CPoint pt) {};
	virtual		void					SetEdit_InitData(int nID, CPoint pt,int nResourceID = -1) {};
	
public://////////////////////////// SVG Çü½Ä

	CString				m_str_id				;

	CString				m_str_psrtype			;
	CString				m_str_keyid				;
	CString				m_str_keyid_dl			;
	CString				m_str_keyname			;
	CString				m_str_linktitleid		;

	int					m_n_type				;

	
	
	double				m_d_x					;
	double				m_d_y					;
	double				m_d_scalex				;
	double				m_d_scaley				;
	double				m_d_rotate				;
	
	CString 			m_str_innertext			;
	
	int 				m_n_draworder			;
	int					m_n_devref				;
	CString				m_str_devrefname		;
	
	int					m_n_usertype			;

	CSB_Object*			m_SB_Object				;


public:
	int					m_Kasim_br_id;

	CPoint				m_Point_Move;

};

typedef CTypedPtrArray<CObArray, CDND_Object*> CDND_ObjectArray;