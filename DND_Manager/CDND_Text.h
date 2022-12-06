#pragma once
#include "CDND_Object.h"
#include "../SB_Manager/CSB_Object.h"
class CDND_Text :
	public CDND_Object
{
public:
	CDND_Text(void);
	~CDND_Text(void);

	virtual		void					SetObjectData(CMarkup* pxml);
	virtual		void					GetObjectData(CMarkup* pxml, int&  nDrawOrder);

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
		, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		void					Draw_Object_Image(Graphics &graphics, CPoint ptDraw, double dZoomValue
		, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));


	virtual		void					Draw_Object_Select(Graphics &graphics, CPoint ptDraw, double dZoomValue
		, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		void					Draw_Object_Move(Graphics &graphics, CPoint ptDraw, double dZoomValue
		, double dScale_x = 1., double dScale_y = 1., double dAngle = 0.);

	virtual		BOOL					Check2DwawRect(CRect rDraw, double dZoomValue);
	virtual		CDND_Object*			Select2Point(CPoint pt, CDND_Object* pSelect);
	virtual		void					SetEdit_Move(CPoint pt);

	CSB_Text*							GetTextSB() {return (CSB_Text*)m_SB_Object;	};

	virtual		void					SetEdit_InitData(int nID, CPoint pt, int nResourceID = -1);

public:

	
};

