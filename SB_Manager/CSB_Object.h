#pragma once
#include <afx.h>
#include "Markup.h"

#define						SBOBJECT_TYPE_BASE			0
#define						SBOBJECT_TYPE_LAYER			1
#define						SBOBJECT_TYPE_BLOCK			2
#define						SBOBJECT_TYPE_MULTIBLOCK	3
#define						SBOBJECT_TYPE_BLOCK_M		4

#define						SBOBJECT_TYPE_DRAW_RECT				10
#define						SBOBJECT_TYPE_DRAW_POLYLINE			11
#define						SBOBJECT_TYPE_DRAW_ELLIPSE			12
#define						SBOBJECT_TYPE_DRAW_TEXT				13
#define						SBOBJECT_TYPE_DRAW_ARC				14
#define						SBOBJECT_TYPE_DRAW_POLYGON			15
#define						SBOBJECT_TYPE_DRAW_TEXT_ANALOG		16

#define						TEXT_SCALE							0.7

#define						PI									3.141592

class AFX_EXT_CLASS CRealPoint :
	public CObject
{
public:
	CRealPoint() { x = 0., y = 0.; };
	~CRealPoint() {};

	void		SetSplitRect() {
		rect.X = x;
		rect.Y = y;
		rect.Width = 0.;
		rect.Height = 0.;

		rect.Inflate(4., 4.);
	}

	double x;
	double y;

	RectF rect;
};
typedef CTypedPtrArray<CObArray, CRealPoint*> CRealPointArray;

class AFX_EXT_CLASS CSB_Object :
	public CObject
{
public:
	CSB_Object();
	~CSB_Object();

public:
	int 								ObjType_Get() { return m_nObjType; };
	int									MenuID_Get() { return m_nResourceMenuID; };
	void								MenuID_Set(int nMenuID) { m_nResourceMenuID = nMenuID; };
	CString								GetTagName() { return m_strTagName; };

public:
	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_BASE; };
	
	virtual		void					SetObjectData(CMarkup* pxml) {};
	virtual		void					GetObjectData_SVG(CMarkup* pxml, int nDrawOrder) {};

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
													,double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText =_T("")) {};

	virtual		void					Draw_Object_Image(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T("")) {};

	virtual		CRect					GetSBRect() { return CRect(0, 0, 0, 0); };

	virtual		void					SetEdit_Move(CPoint pt) {}; ///////////////////////////////////////// 이동한 크기가 온다.

	virtual		void					Copy(CSB_Object* pSBObj) {};

	void								GetPoint_Draw(CPoint ptCenter, double dx, double dy, CRealPoint* pReturn);
	void								GetPoint_Draw(CPoint ptCenter, CRealPoint ptReal, CRealPoint* pReturn);

	void								GetValue_double2int(CRealPoint* pt, double* dValue);


	/////////////////////////////////////////////////////////////////////////////
	
	Gdiplus::Color						GetColor(CString strColor);
	Gdiplus::Brush*						GetBrush(CString strColor,CString strType); ///////////// 0 , 1 = Path, 2 
	UINT								GetPenStyle(CString strPenStyle);

	UINT								GetFontStyle(CString strFontStyle);
	UINT								GetFontAlignment(CString strFontAlignment,int nMode = 0);

protected:
	CString								m_strTagName;

	int									m_nResourceMenuID;

	int									m_nObjType;

	Gdiplus::GraphicsPath				m_GDI_path;
	Gdiplus::RectF						m_GDI_rect;

		

};

typedef CTypedPtrArray<CObArray, CSB_Object*> CSB_ObjectArray;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				LAYER
////////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CSB_Layer :
	public CSB_Object
{
public:
	CSB_Layer();
	~CSB_Layer();


	
public:
	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_LAYER; };

	virtual		void					SetObjectData(CMarkup* pxml) ;

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	void								Draw(Graphics &graphics, CPoint ptDraw, double dZoomValue, CString strScript
											, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T("")); /////////////// 멀티 용

	virtual		CRect					GetSBRect();
	/////////////////
	void								Set_mem_MultiBlock(CSB_Object* pSBObj);

	CSB_ObjectArray						m_Array_DrawObject;

	CSB_Object*							GetRealObject(int nDevref);

	BOOL								GetCheckLayarState(int nState);
	
	CSB_Object*							SBObject_Create(CString strTagName,BOOL bAdd = TRUE);

protected:
	int m_nID;
	int m_nType;
	int m_nZoomLevelenable;


	BOOL m_bShow;

	CString m_strScript;
	CString m_strName;

	
	CSB_ObjectArray						m_Array_Multi;			//////////////////////////////// BLOCK 연결

	

	/////////////////
	double			m_dZoom_start;
	double			m_dZoom_end;


};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				BLOCK
////////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CSB_BLOCK :
	public CSB_Object
{
public:
	CSB_BLOCK();
	~CSB_BLOCK();

public:
	void								PSRType_Set(CString strPSRType);
	CString								PSRType_Get();
	CString								Usage_Get() { return m_strUsage; };

	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_BLOCK; };

	virtual		void					SetObjectData(CMarkup* pxml);

	virtual		CRect					GetSBRect();

	CString								GetName() { return m_strName; };

	void								Draw(Graphics &graphics, CPoint ptDraw, double dZoomValue, CString strScript
											, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	CSB_ObjectArray						m_Array_Layer;

	int									GetID() { return m_nID; };

public:
	CString								m_strPSRType;
	CString								m_strCEQType;
	CString								m_strName;
	CString								m_strUsage;

	int									m_nID;

	int									m_nInnerText_LayerID;
		


	
};
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				MULTIBLOCK
////////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CSB_BLOCK_M :
	public CSB_Object
{
public:
	CSB_BLOCK_M();
	~CSB_BLOCK_M() ;

public:
	void								PSRType_Set(CString strPSRType);
	CString								PSRType_Get();

	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_BLOCK_M; };

	virtual		void					SetObjectData(CMarkup* pxml);

	void								GetPoint(CRealPoint* pt);


	int									GetDevref() { return m_nDevref; };

	CString								GetInnerText() { return m_strText_inner; };

protected:
	CString								m_strPSRType;
	CString								m_strID;
	CString								m_strKeyName;
	CString								m_strDevref_name;
	CString								m_strText_inner;
	CString								m_strRoundBox;
	CString								m_strUsertype;

	int									m_nKeyID;
	int									m_nType;
	int									m_nSequence;
	int									m_nDevref;

	double								m_dX;
	double								m_dY;
	double								m_dScale_x;
	double								m_dScale_y;
	double								m_dRotate;
									
	int									m_nDrawOrder;

};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				RECT
////////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CSB_Rect :
	public CSB_Object
{
public:
	CSB_Rect() { 
		ObjType_Set(); 
		m_strTagName = _T("rect");
	};
	~CSB_Rect() {};

public:

	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_DRAW_RECT; };

	virtual		void					SetObjectData(CMarkup* pxml);
	virtual		void					GetObjectData_SVG(CMarkup* pxml,int nDrawOrder);

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		CRect					GetSBRect();
	virtual		void					SetEdit_Move(CPoint pt);
	virtual		void					Copy(CSB_Object* pSBObj);

protected:
	double		m_dX;
	double		m_dY;
	double		m_dWidth;
	double		m_dHeight;

	CString		m_strStroke;
	int			m_nStroke_width;
	CString		m_strStroke_type;

	CString		m_strFill;
	CString		m_strFill_type;
	
	int			m_nDrawOrder;


};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				Polyline
////////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CSB_Polyline :
	public CSB_Object
{
public:
	CSB_Polyline() {
		ObjType_Set();
		m_strTagName = _T("polyline");
	};
	~CSB_Polyline() {
		for (int i = 0; i < m_Array_RealPoint.GetSize(); i++)
			delete m_Array_RealPoint.GetAt(i);

		m_Array_RealPoint.RemoveAll();
	};

public:

	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_DRAW_POLYLINE; };

	virtual		void					SetObjectData(CMarkup* pxml);
	virtual		void					GetObjectData_SVG(CMarkup* pxml, int nDrawOrder);

	void								Split_Point(CString strData);

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		CRect					GetSBRect();
	virtual		void					SetEdit_Move(CPoint pt);
	virtual		void					Copy(CSB_Object* pSBObj);

protected:
	CRealPointArray m_Array_RealPoint;

	CString		m_strStroke;
	int			m_nStroke_width;
	CString		m_strStroke_type;

	CString		m_strFill;

	int			m_nDrawOrder;


};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				ELLIPSE
////////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CSB_Ellipse :
	public CSB_Object
{
public:
	CSB_Ellipse() {
		ObjType_Set();
		m_strTagName = _T("ellipse");
	};
	~CSB_Ellipse() {};

public:

	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_DRAW_ELLIPSE; };

	virtual		void					SetObjectData(CMarkup* pxml);
	virtual		void					GetObjectData_SVG(CMarkup* pxml, int nDrawOrder);

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		CRect					GetSBRect();
	virtual		void					SetEdit_Move(CPoint pt);
	virtual		void					Copy(CSB_Object* pSBObj);

protected:
	double		m_dCX;
	double		m_dCY;
	double		m_dRX;
	double		m_dRY;

	CString		m_strStroke;
	int			m_nStroke_width;
	CString		m_strStroke_type;

	CString		m_strFill;
	CString		m_strFill_type;

	int			m_nDrawOrder;


};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				TEXT
////////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CSB_Text :
	public CSB_Object
{
public:
	CSB_Text() {
		ObjType_Set();

		m_dX = 0.;
		m_dY = 0.;
		m_dWidth = 150.; 
		m_dHeight = 18.;

		m_strFont_family = _T("굴림");
		m_nFont_size = 18;
		m_strFont_style = _T("solid");
		m_strFont_color = _T("#FFFFFF");
		m_strFont_anchor = _T("middle");
		m_strFont_valign = _T("middle");

		m_strStroke.Empty();

		m_strFill = _T("#000000");

		m_nDrawOrder = 0;

		m_strText = _T("Text");

		m_strTagName = _T("text");
	};
	~CSB_Text() {};

public:

	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_DRAW_TEXT; };

	virtual		void					SetObjectData(CMarkup* pxml);

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
												, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		CRect					GetSBRect();

	void								SetFillColor(CString strColor) { m_strFill = strColor; };

	CPoint								GetPoint() { return CPoint(int(m_dX), int(m_dY)) ; };

	CString								GetText() { 	return m_strText; };
	virtual		void					SetEdit_Move(CPoint pt);
	virtual		void					Copy(CSB_Object* pSBObj);
public:
	double		m_dX;
	double		m_dY;
	double		m_dWidth;
	double		m_dHeight;

	CString		m_strFont_family;
	int			m_nFont_size;
	CString		m_strFont_style;
	CString		m_strFont_color;
	CString		m_strFont_anchor;
	CString		m_strFont_valign;

	CString		m_strStroke;

	CString		m_strFill;

	int			m_nDrawOrder;

	CString		m_strText;


};
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				ANALOGTEXT
////////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CSB_Text_analog :
	public CSB_Object
{
public:
	CSB_Text_analog() {
		ObjType_Set();

		m_strTagName = _T("ANALOGTEXT");
	};
	~CSB_Text_analog() {};

public:

	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_DRAW_TEXT_ANALOG; };

	virtual		void					SetObjectData(CMarkup* pxml);

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		CRect					GetSBRect();
	virtual		void					SetEdit_Move(CPoint pt);
	virtual		void					Copy(CSB_Object* pSBObj);

protected:
	CString		m_strPSRType;
	CString		m_strID;
	CString		m_strPoint_type;
	CString		m_strPoint_code;

	double		m_dX;
	double		m_dY;
	double		m_dWidth;
	double		m_dHeight;

	CString		m_strDataType;
	int			m_nShowSign;
	double		m_dDotForamt;
	int			m_nShowUnit;

	CString		m_strFont_family;
	int			m_nFont_size;
	CString		m_strFont_style;
	CString		m_strFont_color;
	CString		m_strFont_anchor;
	CString		m_strFont_valign;

	CString		m_strStroke;

	CString		m_strFill;

	int			m_nDrawOrder;

	CString		m_strText;

	
};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				ARC
////////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CSB_Arc :
	public CSB_Object
{
public:
	CSB_Arc() {
		ObjType_Set();

		m_strTagName = _T("arc");

	};
	~CSB_Arc() {};

public:

	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_DRAW_ARC; };

	virtual		void					SetObjectData(CMarkup* pxml);
	virtual		void					GetObjectData_SVG(CMarkup* pxml, int nDrawOrder);

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		CRect					GetSBRect();
	virtual		void					SetEdit_Move(CPoint pt);
	virtual		void					Copy(CSB_Object* pSBObj);

protected:
	double		m_dCX;
	double		m_dCY;
	double		m_dRX;
	double		m_dRY;

	double		m_dAngle_start;
	double		m_dAngle_end;
	int			m_nPie;


	CString		m_strStroke;
	int			m_nStroke_width;
	CString		m_strStroke_type;

	CString		m_strFill;
	CString		m_strFill_type;

	int			m_nDrawOrder;


};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				Polygon
////////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CSB_Polygon :
	public CSB_Object
{
public:
	CSB_Polygon() {
		ObjType_Set();
		m_strTagName = _T("polygon");
	};
	~CSB_Polygon() {
		for (int i = 0; i < m_Array_RealPoint.GetSize(); i++)
			delete m_Array_RealPoint.GetAt(i);

		m_Array_RealPoint.RemoveAll();
	};

public:

	virtual		void					ObjType_Set() { m_nObjType = SBOBJECT_TYPE_DRAW_POLYGON; };

	virtual		void					SetObjectData(CMarkup* pxml);
	virtual		void					GetObjectData_SVG(CMarkup* pxml, int nDrawOrder);

	void								Split_Point(CString strData);

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));
		
	virtual		CRect					GetSBRect();
	virtual		void					SetEdit_Move(CPoint pt);
	virtual		void					Copy(CSB_Object* pSBObj);

protected:
	CRealPointArray m_Array_RealPoint;

	CString		m_strStroke;
	int			m_nStroke_width;
	CString		m_strStroke_type;

	CString		m_strFill;
	CString		m_strFill_type;

	int			m_nDrawOrder;


};