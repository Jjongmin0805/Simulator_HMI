#include "pch.h"
#include "CSB_Object.h"


CSB_Object::CSB_Object()
{
	m_nResourceMenuID = -1;
}

CSB_Object::~CSB_Object()
{
	
}

void CSB_Object::GetPoint_Draw(CPoint ptCenter, CRealPoint ptReal, CRealPoint* pReturn)
{
	pReturn->x = ptCenter.x + ptReal.x;
	pReturn->y = ptCenter.y + ptReal.y;
}

void CSB_Object::GetPoint_Draw(CPoint ptCenter, double dx, double dy, CRealPoint* pReturn)
{
	pReturn->x = ptCenter.x + dx;
	pReturn->y = ptCenter.y + dy;
}

Gdiplus::Color CSB_Object::GetColor(CString strColor)
{
	int nRed = 0, nGreen = 0, nBlue = 0;

	strColor.Delete(0, 1);

	nRed	= wcstol(strColor.Left(2),NULL,16);
	nGreen	= wcstol(strColor.Mid(2,2), NULL, 16);
	nBlue	= wcstol(strColor.Right(2), NULL, 16);

	return Gdiplus::Color(nRed, nGreen, nBlue);

}

Gdiplus::Brush* CSB_Object::GetBrush(CString strColor, CString strType)
{
	CString strFill_type, strFill_style, strFill_color,strTmp;
	if (strType.Find(_T(":")) > -1)
	{
		AfxExtractSubString(strTmp, strType, 0, _T(';'));
		AfxExtractSubString(strFill_type, strTmp, 0, _T(':'));
		AfxExtractSubString(strFill_style, strTmp, 1, _T(':'));
		if (strFill_type != _T("hash"))
			AfxExtractSubString(strFill_color, strType, 1, _T(';'));

	}
	else
		strFill_type = strType;


	Gdiplus::Brush* pBrush;

	if (strFill_type == _T("hash"))
	{
		pBrush = new Gdiplus::HatchBrush(Gdiplus::HatchStyle::HatchStyleHorizontal,GetColor(strColor));
	}
	else if (strFill_type == _T("gradient"))
	{
		if (strFill_style == _T("center"))
		{
			Gdiplus::PathGradientBrush* pPGB = new Gdiplus::PathGradientBrush(&m_GDI_path);
			Gdiplus::PointF pt;
			pt.X = m_GDI_rect.X + (m_GDI_rect.Width / 2);
			pt.Y = m_GDI_rect.Y + (m_GDI_rect.Height / 2);
			pPGB->SetCenterPoint(pt);
			pPGB->SetCenterColor(GetColor(strColor));
			int nCount = 1;
			pPGB->SetSurroundColors(&GetColor(strFill_color), &nCount);
			pBrush = pPGB;
		}
		else if (strFill_style == _T("rightbottom"))
		{
			Gdiplus::PointF ptF(0.,0.),ptT(0., 0.);

			ptF.X = m_GDI_rect.X ;
			ptF.Y = m_GDI_rect.Y;

			ptT.X = m_GDI_rect.X + (m_GDI_rect.Width );
			ptT.Y = m_GDI_rect.Y + (m_GDI_rect.Height);

			LinearGradientBrush* pLGB = new LinearGradientBrush(ptF, ptT, GetColor(strColor), GetColor(strFill_color));
			pBrush = pLGB;
		}
		else if (strFill_style == _T("leftbottom"))
		{
			Gdiplus::PointF ptF(0., 0.), ptT(0., 0.);

			ptF.X = m_GDI_rect.X + (m_GDI_rect.Width); 
			ptF.Y = m_GDI_rect.Y;

			ptT.X = m_GDI_rect.X;
			ptT.Y = m_GDI_rect.Y + (m_GDI_rect.Height);

			LinearGradientBrush* pLGB = new LinearGradientBrush(ptF, ptT, GetColor(strColor), GetColor(strFill_color));
			pBrush = pLGB;
		}
		else if (strFill_style == _T("right"))
		{
			Gdiplus::PointF ptF(0., 0.), ptT(0., 0.);

			ptF.X = m_GDI_rect.X;
			ptF.Y = m_GDI_rect.Y;

			ptT.X = m_GDI_rect.X + (m_GDI_rect.Width);
			ptT.Y = m_GDI_rect.Y;

			LinearGradientBrush* pLGB = new LinearGradientBrush(ptF, ptT, GetColor(strColor), GetColor(strFill_color));
			pBrush = pLGB;
		}
		else if (strFill_style == _T("left"))
		{
			Gdiplus::PointF ptF(0., 0.), ptT(0., 0.);

			ptF.X = m_GDI_rect.X + (m_GDI_rect.Width);
			ptF.Y = m_GDI_rect.Y;

			ptT.X = m_GDI_rect.X;
			ptT.Y = m_GDI_rect.Y;

			LinearGradientBrush* pLGB = new LinearGradientBrush(ptF, ptT, GetColor(strColor), GetColor(strFill_color));
			pBrush = pLGB;
		}
		else //if(strFill_style == _T("bottom"))
		{
			Gdiplus::PointF ptF(0., 0.), ptT(0., 0.);

			ptF.X = m_GDI_rect.X;
			ptF.Y = m_GDI_rect.Y;

			ptT.X = m_GDI_rect.X;
			ptT.Y = m_GDI_rect.Y + (m_GDI_rect.Height);

			LinearGradientBrush* pLGB = new LinearGradientBrush(ptF, ptT, GetColor(strColor), GetColor(strFill_color));
			pBrush = pLGB;
		}
		
	}
	else
	{
		pBrush = new Gdiplus::SolidBrush(GetColor(strColor));
	}

	return pBrush;
}

UINT CSB_Object::GetFontStyle(CString strFontStyle)
{
	UINT unStyle = 0;
	///normal, bold, italic, bolditalic, underline, strikeout

	/*FontStyleRegular = 0,
		FontStyleBold = 1,
		FontStyleItalic = 2,
		FontStyleBoldItalic = 3,
		FontStyleUnderline = 4,
		FontStyleStrikeout = 8*/
	if (strFontStyle == ("bold"))
	{
		unStyle = Gdiplus::FontStyle::FontStyleBold;
	}
	else if (strFontStyle == ("italic"))
	{
		unStyle = Gdiplus::FontStyle::FontStyleItalic;
	}
	else if (strFontStyle == ("bolditalic"))
	{
		unStyle = Gdiplus::FontStyle::FontStyleBoldItalic;
	}
	else if (strFontStyle == ("underline"))
	{
		unStyle = Gdiplus::FontStyle::FontStyleUnderline;
	}
	else if (strFontStyle == ("strikeout"))
	{
		unStyle = Gdiplus::FontStyle::FontStyleStrikeout;
	}
	else 
	{
		unStyle = Gdiplus::FontStyle::FontStyleRegular;
	}

	return unStyle;
}

UINT CSB_Object::GetPenStyle(CString strPenStyle)
{
	UINT unPenStyle;

	/////////////  solid, dash, dot, dashdot, dashdotdot

	//DashStyleDash,           // 1
	//	DashStyleDot,            // 2
	//	DashStyleDashDot,        // 3
	//	DashStyleDashDotDot,     // 4
	//	DashStyleCustom          // 5
	if (strPenStyle == _T("dash"))
	{
		unPenStyle = Gdiplus::DashStyle::DashStyleDash;
	}
	else if (strPenStyle == _T("dot"))
	{
		unPenStyle = Gdiplus::DashStyle::DashStyleDot;
	}
	else if (strPenStyle == _T("dashdot"))
	{
		unPenStyle = Gdiplus::DashStyle::DashStyleDashDot;
	}
	else if (strPenStyle == _T("dashdotdot"))
	{
		unPenStyle = Gdiplus::DashStyle::DashStyleDashDotDot;
	}
	else
	{
		unPenStyle = Gdiplus::DashStyle::DashStyleSolid;
	}

	return unPenStyle;
}

UINT CSB_Object::GetFontAlignment(CString strFontAlignment,int nMode)
{
	UINT unStyle = 0;

	////start, middle, end 
	////top, middle, bottom
	if (nMode == 0)
	{
		if (strFontAlignment == ("start") )
		{
			unStyle = Gdiplus::StringAlignment::StringAlignmentNear;
		}
		else if (strFontAlignment == ("end"))
		{
			unStyle = Gdiplus::StringAlignment::StringAlignmentFar;
		}
		else
		{
			unStyle = Gdiplus::StringAlignment::StringAlignmentCenter;
		}
	}
	else
	{
		if (strFontAlignment == ("top"))
		{
			unStyle = Gdiplus::StringAlignment::StringAlignmentNear;
		}
		else if ( strFontAlignment == ("bottom"))
		{
			unStyle = Gdiplus::StringAlignment::StringAlignmentFar;
		}
		else
		{
			unStyle = Gdiplus::StringAlignment::StringAlignmentCenter;
		}
	}
	

	return unStyle;
}



void	CSB_Object::GetValue_double2int(CRealPoint* pt, double* dValue)
{
	if (pt->x < 0.)
	{
		dValue[0] = floor(pt->x);
	}
	else
	{
		dValue[0] = ceil(pt->x);
	}

	if (pt->y < 0.)
	{
		dValue[1] = floor(pt->y);
	}
	else
	{
		dValue[1] = ceil(pt->y);
	}

}



////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				Layer
////////////////////////////////////////////////////////////////////////////////

CSB_Layer::CSB_Layer()
{
	m_nID = -1;
	m_strName.Empty();
	m_nType = -1;
	m_bShow = FALSE;
	m_nZoomLevelenable = -1;
	m_strScript.Empty();

	m_strTagName = _T("LAYER");
	ObjType_Set();
}

CSB_Layer::~CSB_Layer()
{
	for (int i = 0; i < m_Array_DrawObject.GetSize(); i++)
		delete m_Array_DrawObject.GetAt(i);
	m_Array_DrawObject.RemoveAll();
}

CSB_Object*				CSB_Layer::SBObject_Create(CString strTagName,BOOL bAdd)
{
	CSB_Object* pSBObj = NULL;

	if (strTagName == _T("BLOCK"))
	{
		pSBObj = new CSB_BLOCK_M();
	}
	else if (strTagName == _T("rect"))
	{
		pSBObj = new CSB_Rect();
	}
	else if (strTagName == _T("polyline"))
	{
		pSBObj = new CSB_Polyline();
	}
	else if (strTagName == _T("ellipse"))
	{
		pSBObj = new CSB_Ellipse();
	}
	else if (strTagName == _T("text"))
	{
		pSBObj = new CSB_Text();
	}
	else if (strTagName == _T("arc"))
	{
		pSBObj = new CSB_Arc();
	}
	else if (strTagName == _T("polygon"))
	{
		pSBObj = new CSB_Polygon();
	}
	else if (strTagName == _T("ANALOGTEXT"))
	{
		pSBObj = new CSB_Text_analog();
	}
	else
	{
		AfxMessageBox(_T("새로운 그리기!!!"));
		return NULL;
	}
	if(bAdd)
		m_Array_DrawObject.Add(pSBObj);
	return pSBObj;
}


void					CSB_Layer::SetObjectData(CMarkup* pxml)
{
	CString strID, strName, strType, strShow, strZoom, strScript,strZoom_S,strZoom_E;
	strID		= pxml->GetAttrib(_T("id"));
	strName		= pxml->GetAttrib(_T("name"));
	strType		= pxml->GetAttrib(_T("type"));
	strShow		= pxml->GetAttrib(_T("show"));
	strZoom		= pxml->GetAttrib(_T("zoomlevelenable"));
	strScript	= pxml->GetAttrib(_T("script"));
	strZoom_S = pxml->GetAttrib(_T("zoomlevelstart"));
	strZoom_E = pxml->GetAttrib(_T("zoomlevelend"));

	m_nID							= _wtoi(strID);
	m_strName						= strName;
	m_nType							= _wtoi(strType);
	m_bShow							= _wtoi(strShow);
	m_nZoomLevelenable				= _wtoi(strZoom);
	m_strScript						= strScript;

	m_dZoom_start					= _wtof(strZoom_S);
	m_dZoom_end						= _wtof(strZoom_E);

	/////
	CString strTagName;
	CSB_Object* pSBObj;


	while (pxml->FindChildElem())
	{
		pxml->IntoElem();

		strTagName = pxml->GetTagName();

		pSBObj = SBObject_Create(strTagName);
		pSBObj->SetObjectData(pxml);


		pxml->OutOfElem();
	}
}

void CSB_Layer::Set_mem_MultiBlock(CSB_Object* pSBObj)
{
	m_Array_Multi.Add(pSBObj);
}

void CSB_Layer::Draw(Graphics &graphics, CPoint ptDraw, double dZoomValue, CString strScript
			, double dScale_x , double dScale_y , double dAngle , CString strInnerText )
{
	CSB_Object* pSBObj ,*pBlock;
	CSB_BLOCK_M* pBlock_M;
	CPoint pt;
	CRealPoint ptReal;
	CString strText;

	for (int i = 0; i < m_Array_DrawObject.GetSize(); i++)
	{
		pSBObj = m_Array_DrawObject.GetAt(i);
		if (pSBObj->ObjType_Get() == SBOBJECT_TYPE_BLOCK_M)
		{
			pBlock_M = (CSB_BLOCK_M*)pSBObj;
			pBlock_M->GetPoint(&ptReal);
			pt.x = int(double(ptDraw.x) + (ptReal.x * dZoomValue));
			pt.y = int(double(ptDraw.y) + (ptReal.y * dZoomValue));

			pBlock = GetRealObject(pBlock_M->GetDevref());
			if (pBlock)
			{
				if(!strInnerText.IsEmpty() )
					strText = strInnerText;
				else
					strText = pBlock_M->GetInnerText();
				((CSB_BLOCK*)pBlock)->Draw(graphics, pt, dZoomValue,strScript, dScale_x, dScale_y, dAngle, strText);


			}
		}
		else
		{
			pSBObj->Draw_Object(graphics, ptDraw, dZoomValue, dScale_x, dScale_y, dAngle, strInnerText);
		}
		
	}

}

CSB_Object* CSB_Layer::GetRealObject(int nDevref)
{
	CSB_BLOCK* pBlock;

	for (int i = 0; i < m_Array_DrawObject.GetSize(); i++)
	{
		pBlock = (CSB_BLOCK*)m_Array_Multi.GetAt(i);
		if (pBlock->GetID() == nDevref)
		{
			return pBlock;
		}
	}
	return NULL;
}
BOOL CSB_Layer::GetCheckLayarState(int nState)
{
	CString strScript = m_strScript;
	int nPos = strScript.Find(_T("BI"));
	if (nPos > -1)
	{
		nPos = strScript.Find(_T("=="));
		strScript.Delete(0, nPos + 2);

		strScript.Trim();
		if (nState != _wtoi(strScript))
			return FALSE;

	}
	else
	{
		nPos = strScript.Find(_T("SYS"));
		if (nPos > -1)
			return FALSE;

		nPos = strScript.Find(_T("UI"));
		if(nPos > -1)
			return FALSE;

		
		if (strScript == _T("0"))
			return FALSE;
	}

	return TRUE;
}

void CSB_Layer::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	CSB_Object* pSBObj/*, *pSBObj2*/;
	
	for (int i = 0; i < m_Array_DrawObject.GetSize(); i++)
	{
		pSBObj = m_Array_DrawObject.GetAt(i);

		pSBObj->Draw_Object(graphics, ptDraw,dZoomValue, dScale_x, dScale_y, dAngle, strInnerText);
	}
}

CRect CSB_Layer::GetSBRect()
{
	int nL(999999), nT(999999), nR(-999999), nB(-9999999);

	CSB_Object* pSBObj,*pSBObj2;
	BOOL bMulti = FALSE;
	CRect r;

	for (int i = 0; i < m_Array_DrawObject.GetSize(); i++)
	{
		pSBObj = m_Array_DrawObject.GetAt(i);

		if (pSBObj->ObjType_Get() == SBOBJECT_TYPE_BLOCK_M)
		{
			bMulti = TRUE;
			//break;
		}

		r = pSBObj->GetSBRect();

		if (r.left < nL)
		{
			nL = r.left;
		}
		if (r.right > nR)
		{
			nR = r.right;
		}

		if (r.top < nT)
		{
			nT = r.top;
		}
		if (r.bottom > nB)
		{
			nB = r.bottom;
		}
	}

	CRealPoint pt;
	double dValue[2];

	if(bMulti)
	{ 
		for (int i = 0; i < m_Array_Multi.GetSize(); i++)
		{
			pSBObj = m_Array_Multi.GetAt(i);
			pSBObj2 = m_Array_DrawObject.GetAt(i);

			r = pSBObj->GetSBRect();

			((CSB_BLOCK_M*)pSBObj2)->GetPoint(&pt);

			GetValue_double2int(&pt, dValue);
			

			r.left += int (dValue[0]);
			r.right += int(dValue[0]);

			r.top += int(dValue[1]);
			r.bottom += int(dValue[1]);
			

			if (r.left < nL)
			{
				nL = r.left;
			}
			if (r.right > nR)
			{
				nR = r.right;
			}

			if (r.top < nT)
			{
				nT = r.top;
			}
			if (r.bottom > nB)
			{
				nB = r.bottom;
			}
		}
	}

	return CRect(nL, nT, nR, nB);
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				BLOCK
////////////////////////////////////////////////////////////////////////////////

CSB_BLOCK::CSB_BLOCK()
{
	m_nInnerText_LayerID = -1;
	ObjType_Set();

	m_strTagName = _T("BLOCK");
}

CSB_BLOCK::~CSB_BLOCK()
{
	for (int i = 0; i < m_Array_Layer.GetSize(); i++)
		delete m_Array_Layer.GetAt(i);

	m_Array_Layer.RemoveAll();
}

void CSB_BLOCK::PSRType_Set(CString strPSRType)
{
	m_strPSRType = strPSRType;


}


CString CSB_BLOCK::PSRType_Get()
{
	return m_strPSRType;
}


void					CSB_BLOCK::SetObjectData(CMarkup* pxml)
{
	CString strTagName;
	CString strPSRType, strCeqType, strID, strName, strUsage;
	CString strData[1];

	strPSRType	= pxml->GetAttrib(_T("psrtype"));
	strCeqType	= pxml->GetAttrib(_T("ceqtype"));
	strID		= pxml->GetAttrib(_T("id"));
	strName		= pxml->GetAttrib(_T("name"));
	strUsage	= pxml->GetAttrib(_T("usage"));

	strData[0] = pxml->GetAttrib(_T("innertextlayerid"));

	strTagName = pxml->GetTagName();
	if (strTagName == _T("MULTIBLOCK"))
	{
		m_nObjType = SBOBJECT_TYPE_MULTIBLOCK;
	}


	m_nID			= _wtoi(strID);
	m_strPSRType	= strPSRType; 
	m_strCEQType	= strCeqType;
	m_strUsage		= strUsage;
	m_strName		= strName;
	
	if(!strData[0].IsEmpty())
		m_nInnerText_LayerID = _wtoi(strData[0]);

	/////
	CSB_Object* pSBObj;


	while (pxml->FindChildElem(_T("LAYER"))  )
	{
		pxml->IntoElem();

		strTagName = pxml->GetTagName();

		pSBObj = new CSB_Layer();
		m_Array_Layer.Add(pSBObj);
		pSBObj->SetObjectData(pxml);


		pxml->OutOfElem();
	}
}

void CSB_BLOCK::Draw(Graphics &graphics, CPoint ptDraw, double dZoomValue, CString strScript
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	//ASSERT(m_nID != 432);

	CSB_Object* pSBObj;
	dZoomValue = 1.;

	for (int i = 0; i < m_Array_Layer.GetSize(); i++)
	{
		pSBObj = m_Array_Layer.GetAt(i);

		
		if (ObjType_Get() == SBOBJECT_TYPE_BLOCK && i != m_nInnerText_LayerID)
		{
			if(((CSB_Layer*)pSBObj)->GetCheckLayarState(0))
				pSBObj->Draw_Object(graphics, ptDraw, dZoomValue, dScale_x, dScale_y, dAngle, _T(""));
			
		}
		else if (i == 0)////  SBOBJECT_TYPE_MULTIBLOCK
		{
			((CSB_Layer*)pSBObj)->Draw(graphics, ptDraw, dZoomValue, strScript, dScale_x, dScale_y, dAngle, strInnerText);
		}
		
		if (m_nInnerText_LayerID > -1)
		{
			if (i == m_nInnerText_LayerID)
			{
				pSBObj->Draw_Object(graphics, ptDraw, dZoomValue, dScale_x, dScale_y, dAngle, strInnerText);

			}
		}
		
	}

	if (!strInnerText.IsEmpty())
	{
		/*SolidBrush						_drawFontbrush(Color( 0, 0, 0));

		Gdiplus::Font					_drawfont(_T("굴림"), 10., Gdiplus::FIFontStyleRegular, UnitPixel);
		StringFormat					_drawStrFormat;
		_drawStrFormat.SetAlignment(StringAlignmentCenter);
		_drawStrFormat.SetLineAlignment(StringAlignmentCenter);

		Gdiplus::RectF rStroke;

		rStroke.X = ptDraw.x + (r.left * dZoomValue);
		rStroke.Y = ptDraw.y + (r.top * dZoomValue);
		rStroke.Width = r.Width() * dZoomValue;
		rStroke.Height = r.Height() * dZoomValue;

		graphics.DrawString(strInnerText, -1, &_drawfont, rStroke, &_drawStrFormat, &_drawFontbrush);*/
	}


}
CRect CSB_BLOCK::GetSBRect()
{
	int nL(999999), nT(999999), nR(-999999), nB(-9999999);

	CSB_Object* pSBObj;
	CRect r;

	for (int i = 0; i < m_Array_Layer.GetSize(); i++)
	{
		pSBObj = m_Array_Layer.GetAt(i);
		if ( !((CSB_Layer*)pSBObj)->GetCheckLayarState(0))
			continue;

		r = pSBObj->GetSBRect();

		if (r.left < nL)
		{
			nL = r.left;
		}
		if (r.right > nR)
		{
			nR = r.right;
		}

		if (r.top < nT)
		{
			nT = r.top;
		}
		if (r.bottom > nB)
		{
			nB = r.bottom;
		}
	}

	return CRect(nL, nT, nR, nB);
}
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				MULTIBLOCK
////////////////////////////////////////////////////////////////////////////////

CSB_BLOCK_M::CSB_BLOCK_M()
{
	ObjType_Set();
	m_strTagName = _T("BLOCK");
}

CSB_BLOCK_M::~CSB_BLOCK_M()
{

}

void CSB_BLOCK_M::PSRType_Set(CString strPSRType)
{
	m_strPSRType = strPSRType;


}


CString CSB_BLOCK_M::PSRType_Get()
{
	return m_strPSRType;
}


void					CSB_BLOCK_M::SetObjectData(CMarkup* pxml)
{
	CString strData[17];
	strData[0] = pxml->GetAttrib(_T("psrtype"));
	strData[1] = pxml->GetAttrib(_T("id"));
	strData[2] = pxml->GetAttrib(_T("keyid"));
	strData[3] = pxml->GetAttrib(_T("keyname"));
	strData[4] = pxml->GetAttrib(_T("x"));
	strData[5] = pxml->GetAttrib(_T("y"));
	strData[6] = pxml->GetAttrib(_T("type"));
	strData[7] = pxml->GetAttrib(_T("scalex"));
	strData[8] = pxml->GetAttrib(_T("scaley"));
	strData[9] = pxml->GetAttrib(_T("rotate"));
	strData[10] = pxml->GetAttrib(_T("innertext"));
	strData[11] = pxml->GetAttrib(_T("sequence"));
	strData[12] = pxml->GetAttrib(_T("roundbox"));
	strData[13] = pxml->GetAttrib(_T("usertype"));
	strData[14] = pxml->GetAttrib(_T("devref"));
	strData[15] = pxml->GetAttrib(_T("devrefname"));
	strData[16] = pxml->GetAttrib(_T("draworder"));

	m_strPSRType	= strData[0];
	m_strID = strData[1];
	m_nKeyID = _wtoi(strData[2]);
	m_strKeyName = strData[3];

	m_dX = _wtof(strData[4]);
	m_dY = _wtof(strData[5]);

	m_nType = _wtoi(strData[6]);

	m_dScale_x = _wtof(strData[7]);
	m_dScale_y = _wtof(strData[8]);
	m_dRotate = _wtof(strData[9]);

	m_strText_inner = strData[10];

	m_nSequence = _wtoi(strData[11]);

	m_strRoundBox = strData[12];
	m_strUsertype = strData[13];

	m_nDevref = _wtoi(strData[14]);
	m_strDevref_name = strData[15];

	m_nDrawOrder = _wtoi(strData[16]);
	



}

void		CSB_BLOCK_M::GetPoint(CRealPoint* pt)
{
	pt->x = m_dX;
	pt->y = m_dY;
}


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				RECT
////////////////////////////////////////////////////////////////////////////////

void					CSB_Rect::SetObjectData(CMarkup* pxml)
{
	CString strData[10];
	strData[0] = pxml->GetAttrib(_T("x"));
	strData[1] = pxml->GetAttrib(_T("y"));
	strData[2] = pxml->GetAttrib(_T("width"));
	strData[3] = pxml->GetAttrib(_T("height"));
	strData[4] = pxml->GetAttrib(_T("stroke"));
	strData[5] = pxml->GetAttrib(_T("stroke-width"));
	strData[6] = pxml->GetAttrib(_T("stroke-type"));
	strData[7] = pxml->GetAttrib(_T("fill"));
	strData[8] = pxml->GetAttrib(_T("fill-type"));
	strData[9] = pxml->GetAttrib(_T("draworder"));

	
	m_dX = _wtof(strData[0]);
	m_dY = _wtof(strData[1]);
	m_dWidth = _wtof(strData[2]);
	m_dHeight = _wtof(strData[3]);

	m_strStroke = strData[4];
	m_nStroke_width = _wtoi(strData[5]);
	m_strStroke_type = strData[6];

	m_strFill = strData[7];
	m_strFill_type = strData[8];

	m_nDrawOrder = _wtoi(strData[9]);

}

void CSB_Rect::GetObjectData_SVG(CMarkup* pxml, int nDrawOrder)
{
	CString strData[11];
	strData[0].Format(_T("%s"), _T(""));
	strData[1].Format(_T("%.0lf"), m_dX);
	strData[2].Format(_T("%.0lf"), m_dY);
	strData[3].Format(_T("%.0lf"), m_dWidth);
	strData[4].Format(_T("%.0lf"), m_dHeight);
	strData[5].Format(_T("%s"), m_strStroke);
	strData[6].Format(_T("%d"), m_nStroke_width);
	strData[7].Format(_T("%s"), m_strStroke_type);
	strData[8].Format(_T("%s"), m_strFill);
	strData[9].Format(_T("%s"), m_strFill_type);
	strData[10].Format(_T("%d"), nDrawOrder);

	pxml->AddElem(m_strTagName);
	pxml->AddAttrib(_T("id"), strData[0]);
	pxml->AddAttrib(_T("x"), strData[1]);
	pxml->AddAttrib(_T("y"), strData[2]);
	pxml->AddAttrib(_T("width"), strData[3]);
	pxml->AddAttrib(_T("height"), strData[4]);
	pxml->AddAttrib(_T("stroke"), strData[5]);
	pxml->AddAttrib(_T("stroke-width"), strData[6]);
	pxml->AddAttrib(_T("stroke-type"), strData[7]);
	pxml->AddAttrib(_T("fill"), strData[8]);
	pxml->AddAttrib(_T("fill-type"), strData[9]);
	pxml->AddAttrib(_T("draworder"), strData[10]);
}

void CSB_Rect::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	
	Gdiplus::Brush* pBrush_stroke = GetBrush(m_strStroke, _T(""));
	UINT	unPenStyle = GetPenStyle(m_strStroke_type);
	Gdiplus::Pen					pen(pBrush_stroke, double(m_nStroke_width));
	pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);
	
	Gdiplus::RectF rStroke, rFill;

	rStroke.X = ptDraw.x + (m_dX * dZoomValue);
	rStroke.Y = ptDraw.y + (m_dY * dZoomValue);
	rStroke.Width = m_dWidth * dZoomValue;
	rStroke.Height = m_dHeight * dZoomValue;



	rFill = rStroke;
	//rFill.Inflate(double(m_nStroke_width) * -1., double(m_nStroke_width) * -1.);

	m_GDI_path.Reset();
	m_GDI_path.AddRectangle(rFill);
	m_GDI_rect = rFill;
	Gdiplus::Brush* pBrush_fill = GetBrush(m_strFill, m_strFill_type);

	if (m_strFill != _T("none"))
		graphics.FillRectangle(pBrush_fill, rFill);

	graphics.DrawRectangle(&pen, rStroke);
	
	

	delete pBrush_stroke;
	delete pBrush_fill;
	
}

CRect CSB_Rect::GetSBRect()
{
	CRect r;

	CRealPoint ptLT, ptRB;

	ptLT.x = m_dX;
	ptLT.y = m_dY;

	ptRB.x = m_dX + m_dWidth;
	ptRB.y = m_dY + m_dHeight;

	double dValue_LT[2], dValue_RB[2];

	GetValue_double2int(&ptLT, dValue_LT);
	GetValue_double2int(&ptRB, dValue_RB);

	r.SetRect(int(dValue_LT[0]), int(dValue_LT[1]), int(dValue_RB[0]), int(dValue_RB[1]));

	return r;

}
void	CSB_Rect::SetEdit_Move(CPoint pt)
{
	m_dX += pt.x;
	m_dY += pt.y;
}

void CSB_Rect::Copy(CSB_Object* pSBObj)
{
	CSB_Rect* pSBRect = (CSB_Rect*)pSBObj;
	pSBRect->m_dX = m_dX;
	pSBRect->m_dY = m_dY;
	pSBRect->m_dWidth = m_dWidth;
	pSBRect->m_dHeight = m_dHeight;
	pSBRect->m_strStroke = m_strStroke;
	pSBRect->m_nStroke_width = m_nStroke_width;
	pSBRect->m_strStroke_type = m_strStroke_type;
	pSBRect->m_strFill = m_strFill;
	pSBRect->m_strFill_type = m_strFill_type;
	
	pSBRect->m_nDrawOrder = m_nDrawOrder;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				Polyline
////////////////////////////////////////////////////////////////////////////////

void					CSB_Polyline::SetObjectData(CMarkup* pxml)
{
	CString strData[6];
	strData[0] = pxml->GetAttrib(_T("points"));
	strData[1] = pxml->GetAttrib(_T("stroke"));
	strData[2] = pxml->GetAttrib(_T("stroke-width"));
	strData[3] = pxml->GetAttrib(_T("stroke-type"));
	strData[4] = pxml->GetAttrib(_T("fill"));
	strData[5] = pxml->GetAttrib(_T("draworder"));

	Split_Point(strData[0]);

	m_strStroke = strData[1];
	m_nStroke_width = _wtoi(strData[2]);
	m_strStroke_type = strData[3];

	m_strFill = strData[4];
	
	m_nDrawOrder = _wtoi(strData[5]);

}

void CSB_Polyline::GetObjectData_SVG(CMarkup* pxml, int nDrawOrder)
{
	CString strData[7];
	strData[0].Format(_T("%s"), _T(""));
	
	strData[2].Format(_T("%s"), m_strStroke);
	strData[3].Format(_T("%d"), m_nStroke_width);
	strData[4].Format(_T("%s"), m_strStroke_type);
	strData[5].Format(_T("%s"), m_strFill);
	strData[6].Format(_T("%d"), nDrawOrder);

	CString strPoint;
	CRealPoint* pPt;
	strData[1].Empty();
	for (int i = 0; i < m_Array_RealPoint.GetSize(); i++)
	{
		pPt = m_Array_RealPoint.GetAt(i);
		strPoint.Format(_T("%.0lf,%.0lf "), pPt->x, pPt->y);

		strData[1] += strPoint;
	}
	int nLen = strData[1].GetLength();
	strData[1].Delete(nLen - 1, 1);


	pxml->AddElem(m_strTagName);
	pxml->AddAttrib(_T("id"), strData[0]);
	pxml->AddAttrib(_T("points"), strData[1]);
	pxml->AddAttrib(_T("stroke"), strData[2]);
	pxml->AddAttrib(_T("stroke-width"), strData[3]);
	pxml->AddAttrib(_T("stroke-type"), strData[4]);
	pxml->AddAttrib(_T("fill"), strData[5]);
	pxml->AddAttrib(_T("draworder"), strData[6]);
}

void CSB_Polyline::Split_Point(CString strData)
{
	CString strS,strX,strY;
	int nCount = 0;
	CRealPoint *pPt;

	while (AfxExtractSubString(strS, strData, nCount, _T(' ')))
	{
		if(strS.IsEmpty())
			break;

		AfxExtractSubString(strX, strS, 0, _T(','));
		AfxExtractSubString(strY, strS, 1, _T(','));

		pPt = new CRealPoint();
		m_Array_RealPoint.Add(pPt);
		pPt->x = _wtof(strX);
		pPt->y = _wtof(strY);
		
		nCount++;
	}
}

void CSB_Polyline::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	Gdiplus::Brush* pBrush_stroke = GetBrush(m_strStroke, _T(""));
	UINT	unPenStyle = GetPenStyle(m_strStroke_type);
	Gdiplus::Pen					pen(pBrush_stroke, double(m_nStroke_width));
	pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);

	Gdiplus::GraphicsPath gp;

	CRealPoint* pPoint1,*pPoint2;
	Gdiplus::PointF	pt1, pt2;
	for (int i = 0; i < m_Array_RealPoint.GetSize()-1; i++)
	{
		pPoint1 = m_Array_RealPoint.GetAt(i);
		pPoint2 = m_Array_RealPoint.GetAt(i+1);
		
		pt1.X = double(ptDraw.x) + (pPoint1->x * dZoomValue);
		pt1.Y = double(ptDraw.y) + (pPoint1->y * dZoomValue);

		pt2.X = double(ptDraw.x) + (pPoint2->x * dZoomValue);
		pt2.Y = double(ptDraw.y) + (pPoint2->y * dZoomValue);

		gp.AddLine(pt1, pt2);
	}

	graphics.DrawPath(&pen, &gp);



	delete pBrush_stroke;
	
}

CRect CSB_Polyline::GetSBRect()
{
	CRect r;
	int nL(999999), nT(999999), nR(-999999), nB(-9999999);
	CRealPoint *pt;
	double dValue[2];

	for (int i = 0; i < m_Array_RealPoint.GetSize(); i++)
	{
		pt = m_Array_RealPoint.GetAt(i);

		GetValue_double2int(pt,dValue);

		if (pt->x < nL)
		{
			nL = pt->x;
		}
		if (pt->x > nR)
		{
			nR = pt->x;
		}

		if (pt->y < nT)
		{
			nT = pt->y;
		}
		if (pt->y > nB)
		{
			nB = pt->y;
		}
	}

	r.SetRect(nL, nT, nR, nB);

	return r;

}
void	CSB_Polyline::SetEdit_Move(CPoint pt)
{
	CRealPoint *ptReal;
	for (int i = 0; i < m_Array_RealPoint.GetSize(); i++)
	{
		ptReal = m_Array_RealPoint.GetAt(i);

		ptReal->x += double(pt.x);
		ptReal->y += double(pt.y);
	}
}

void CSB_Polyline::Copy(CSB_Object* pSBObj)
{
	CSB_Polyline* pSBPolyline = (CSB_Polyline*)pSBObj;

	pSBPolyline->m_strStroke = m_strStroke;
	pSBPolyline->m_nStroke_width = m_nStroke_width;
	pSBPolyline->m_strStroke_type = m_strStroke_type;
	pSBPolyline->m_strFill = m_strFill;
	pSBPolyline->m_nDrawOrder = m_nDrawOrder;

	CRealPoint *ptReal,*ptNew;
	for (int i = 0; i < m_Array_RealPoint.GetSize(); i++)
	{
		ptReal = m_Array_RealPoint.GetAt(i);

		ptNew = new CRealPoint();
		pSBPolyline->m_Array_RealPoint.Add(ptNew);
		ptNew->x = ptReal->x;
		ptNew->y = ptReal->y;
	}
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				ELLIPSE
////////////////////////////////////////////////////////////////////////////////

void					CSB_Ellipse::SetObjectData(CMarkup* pxml)
{
	CString strData[10];
	strData[0] = pxml->GetAttrib(_T("cx"));
	strData[1] = pxml->GetAttrib(_T("cy"));
	strData[2] = pxml->GetAttrib(_T("rx"));
	strData[3] = pxml->GetAttrib(_T("ry"));
	strData[4] = pxml->GetAttrib(_T("stroke"));
	strData[5] = pxml->GetAttrib(_T("stroke-width"));
	strData[6] = pxml->GetAttrib(_T("stroke-type"));
	strData[7] = pxml->GetAttrib(_T("fill"));
	strData[8] = pxml->GetAttrib(_T("fill-type"));
	strData[9] = pxml->GetAttrib(_T("draworder"));


	m_dCX = _wtof(strData[0]);
	m_dCY = _wtof(strData[1]);
	m_dRX = _wtof(strData[2]);
	m_dRY = _wtof(strData[3]);

	m_strStroke = strData[4];
	m_nStroke_width = _wtoi(strData[5]);
	m_strStroke_type = strData[6];

	m_strFill = strData[7];
	m_strFill_type = strData[8];

	m_nDrawOrder = _wtoi(strData[9]);

}

void CSB_Ellipse::GetObjectData_SVG(CMarkup* pxml, int nDrawOrder)
{
	CString strData[11];
	strData[0].Format(_T("%s"), _T(""));
	strData[1].Format(_T("%.6lf"), m_dCX );
	strData[2].Format(_T("%.6lf"), m_dCY );
	strData[3].Format(_T("%.6lf"), m_dRX );
	strData[4].Format(_T("%.6lf"), m_dRY );
	strData[5].Format(_T("%s"), m_strStroke);
	strData[6].Format(_T("%d"), m_nStroke_width);
	strData[7].Format(_T("%s"), m_strStroke_type);
	strData[8].Format(_T("%s"), m_strFill);
	strData[9].Format(_T("%s"), m_strFill_type);
	strData[10].Format(_T("%d"), nDrawOrder);

	pxml->AddElem(m_strTagName);
	pxml->AddAttrib(_T("id"), strData[0]);
	pxml->AddAttrib(_T("cx"), strData[1]);
	pxml->AddAttrib(_T("cy"), strData[2]);
	pxml->AddAttrib(_T("rx"), strData[3]);
	pxml->AddAttrib(_T("ry"), strData[4]);
	pxml->AddAttrib(_T("stroke"), strData[5]);
	pxml->AddAttrib(_T("stroke-width"), strData[6]);
	pxml->AddAttrib(_T("stroke-type"), strData[7]);
	pxml->AddAttrib(_T("fill"), strData[8]);
	pxml->AddAttrib(_T("fill-type"), strData[9]);
	pxml->AddAttrib(_T("draworder"), strData[10]);
}

void CSB_Ellipse::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	Gdiplus::Brush* pBrush_stroke = GetBrush(m_strStroke, _T(""));
	UINT	unPenStyle = GetPenStyle(m_strStroke_type);
	Gdiplus::Pen					pen(pBrush_stroke, double(m_nStroke_width));
	pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);

	Gdiplus::RectF rStroke, rFill;

	rStroke.X = ptDraw.x + (m_dCX * dZoomValue) ;
	rStroke.Y = ptDraw.y + (m_dCY * dZoomValue);
	rStroke.Width = 0.;/*m_dRX * dZoomValue *2*/;
	rStroke.Height = 0.;;

	rStroke.Inflate(m_dRX * dZoomValue, m_dRY* dZoomValue);

	rFill = rStroke;
	//rFill.Inflate(double(m_nStroke_width) * -1., double(m_nStroke_width) * -1.);

	m_GDI_path.Reset();
	m_GDI_path.AddEllipse(rFill);
	m_GDI_rect = rFill;
	Gdiplus::Brush* pBrush_fill = GetBrush(m_strFill, m_strFill_type);

	if (m_strFill != _T("none"))
		graphics.FillEllipse(pBrush_fill, rFill);
	graphics.DrawEllipse(&pen, rStroke);
	

	delete pBrush_stroke;
	delete pBrush_fill;
	
}

CRect CSB_Ellipse::GetSBRect()
{
	CRect r;

	CRealPoint ptLT, ptRB;

	ptLT.x = m_dCX - m_dRX ;
	ptLT.y = m_dCY - m_dRY ;

	ptRB.x = m_dCX + m_dRX ;
	ptRB.y = m_dCY + m_dRY ;

	double dValue_LT[2], dValue_RB[2];

	GetValue_double2int(&ptLT, dValue_LT);
	GetValue_double2int(&ptRB, dValue_RB);

	r.SetRect(int(dValue_LT[0]), int(dValue_LT[1]), int(dValue_RB[0]), int(dValue_RB[1]));

	return r;

}

void	CSB_Ellipse::SetEdit_Move(CPoint pt)
{
	m_dCX += pt.x;
	m_dCY += pt.y;
}

void CSB_Ellipse::Copy(CSB_Object* pSBObj)
{
	CSB_Ellipse* pSBElipse = (CSB_Ellipse*)pSBObj;

	pSBElipse->m_dCX = m_dCX;
	pSBElipse->m_dCY = m_dCY;
	pSBElipse->m_dRX = m_dRX;
	pSBElipse->m_dRY = m_dRY;
	pSBElipse->m_strStroke = m_strStroke;
	pSBElipse->m_nStroke_width = m_nStroke_width;
	pSBElipse->m_strStroke_type = m_strStroke_type;
	pSBElipse->m_strFill = m_strFill;
	pSBElipse->m_strFill_type = m_strFill_type;
	pSBElipse->m_nDrawOrder = m_nDrawOrder;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				TEXT
////////////////////////////////////////////////////////////////////////////////

void					CSB_Text::SetObjectData(CMarkup* pxml)
{
	CString strData[14];
	strData[0] = pxml->GetAttrib(_T("x"));
	strData[1] = pxml->GetAttrib(_T("y"));
	strData[2] = pxml->GetAttrib(_T("width"));
	strData[3] = pxml->GetAttrib(_T("height"));
	strData[4] = pxml->GetAttrib(_T("font-family"));
	strData[5] = pxml->GetAttrib(_T("font-size"));
	strData[6] = pxml->GetAttrib(_T("font-style"));
	strData[7] = pxml->GetAttrib(_T("text-color"));
	strData[8] = pxml->GetAttrib(_T("text-anchor"));
	strData[9] = pxml->GetAttrib(_T("text-valign"));
	strData[10] = pxml->GetAttrib(_T("stroke"));
	strData[11] = pxml->GetAttrib(_T("fill"));
	strData[12] = pxml->GetAttrib(_T("draworder"));
	strData[13] = pxml->GetData();


	m_dX = _wtof(strData[0]);
	m_dY = _wtof(strData[1]);
	m_dWidth = _wtof(strData[2]);
	m_dHeight = _wtof(strData[3]);

	m_strFont_family = strData[4];
	m_nFont_size = _wtoi(strData[5]);
	m_strFont_style = strData[6];
	m_strFont_color = strData[7];
	m_strFont_anchor = strData[8];
	m_strFont_valign = strData[9];

	m_strStroke = strData[10];

	m_strFill = strData[11];

	m_nDrawOrder = _wtoi(strData[12]);

	m_strText = strData[13];

}

void CSB_Text::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	Gdiplus::Brush* pBrush_stroke = GetBrush(m_strStroke, _T(""));
	Gdiplus::Brush* pBrush_fill = GetBrush(m_strFill, _T(""));
	Gdiplus::Brush* pBrush_Font = GetBrush(m_strFont_color, _T(""));


	Gdiplus::Pen					pen(pBrush_stroke, double(1.));

	Gdiplus::Font					_drawfont(m_strFont_family, double(m_nFont_size) * TEXT_SCALE * dZoomValue , GetFontStyle(m_strFont_style), Gdiplus::Unit::UnitPixel);
	StringFormat					_drawStrFormat(StringFormatFlagsNoClip);
	_drawStrFormat.SetAlignment((Gdiplus::StringAlignment)GetFontAlignment(m_strFont_anchor));
	_drawStrFormat.SetLineAlignment((Gdiplus::StringAlignment)GetFontAlignment(m_strFont_valign,1));
	
	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

	Gdiplus::RectF rStroke, rFill;

	rStroke.X = ptDraw.x + ((m_dX + 1.) * dZoomValue);
	rStroke.Y = ptDraw.y + ((m_dY + 1.) * dZoomValue);
	rStroke.Width = m_dWidth * dZoomValue ;
	rStroke.Height = m_dHeight * dZoomValue ;

	rFill = rStroke;

	if (m_strFill != _T("none"))
		graphics.FillRectangle(pBrush_fill, rFill);
	if(m_strStroke != _T("none"))
		graphics.DrawRectangle(&pen, rStroke);
	
	CString strText;
	if (!strInnerText.IsEmpty())
		strText = strInnerText;
	else
		strText = m_strText;

	Gdiplus::RectF rMes;
	graphics.MeasureString(strText, strText.GetLength(), &_drawfont, rStroke, &_drawStrFormat, &rMes);

	graphics.DrawString(strText, strText.GetLength(), &_drawfont, rStroke, &_drawStrFormat, pBrush_Font);
	
	delete pBrush_stroke;
	delete pBrush_fill;
	delete pBrush_Font;
}

CRect CSB_Text::GetSBRect()
{
	CRect r;

	CRealPoint ptLT, ptRB;

	ptLT.x = m_dX;
	ptLT.y = m_dY;

	ptRB.x = m_dX + m_dWidth;
	ptRB.y = m_dY + m_dHeight;

	double dValue_LT[2], dValue_RB[2];

	GetValue_double2int(&ptLT, dValue_LT);
	GetValue_double2int(&ptRB, dValue_RB);

	r.SetRect(int(dValue_LT[0]), int(dValue_LT[1]), int(dValue_RB[0]), int(dValue_RB[1]));

	return r;

}

void	CSB_Text::SetEdit_Move(CPoint pt)
{
	m_dX += pt.x;
	m_dY += pt.y;
}

void CSB_Text::Copy(CSB_Object* pSBObj)
{
	CSB_Text* pSBText = (CSB_Text*)pSBObj;

	pSBText->m_dX = m_dX;
	pSBText->m_dY = m_dY;
	pSBText->m_dWidth = m_dWidth;
	pSBText->m_dHeight = m_dHeight;
	pSBText->m_strStroke = m_strStroke;
	pSBText->m_strFill = m_strFill;
	pSBText->m_nDrawOrder = m_nDrawOrder;

	pSBText->m_strFont_family = m_strFont_family;
	pSBText->m_nFont_size = m_nFont_size;
	pSBText->m_strFont_style = m_strFont_style;
	pSBText->m_strFont_color = m_strFont_color;
	pSBText->m_strFont_anchor = m_strFont_anchor;
	pSBText->m_strFont_valign = m_strFont_valign;
	pSBText->m_strText = m_strText;

}
	

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				ANALOGTEXT
////////////////////////////////////////////////////////////////////////////////

void					CSB_Text_analog::SetObjectData(CMarkup* pxml)
{
	CString strData[22];
	strData[0] = pxml->GetAttrib(_T("x"));
	strData[1] = pxml->GetAttrib(_T("y"));
	strData[2] = pxml->GetAttrib(_T("width"));
	strData[3] = pxml->GetAttrib(_T("height"));
	strData[4] = pxml->GetAttrib(_T("font-family"));
	strData[5] = pxml->GetAttrib(_T("font-size"));
	strData[6] = pxml->GetAttrib(_T("font-style"));
	strData[7] = pxml->GetAttrib(_T("text-color"));
	strData[8] = pxml->GetAttrib(_T("text-anchor"));
	strData[9] = pxml->GetAttrib(_T("text-valign"));
	strData[10] = pxml->GetAttrib(_T("stroke"));
	strData[11] = pxml->GetAttrib(_T("fill"));
	strData[12] = pxml->GetAttrib(_T("draworder"));
	strData[13] = pxml->GetData();

	strData[14] = pxml->GetAttrib(_T("psrtype"));
	strData[15] = pxml->GetAttrib(_T("id"));
	strData[16] = pxml->GetAttrib(_T("pointtype"));
	strData[17] = pxml->GetAttrib(_T("pointcode"));

	strData[18] = pxml->GetAttrib(_T("datatype"));
	strData[19] = pxml->GetAttrib(_T("showsign"));
	strData[20] = pxml->GetAttrib(_T("dotforamt"));
	strData[21] = pxml->GetAttrib(_T("showunit"));



	m_dX = _wtof(strData[0]);
	m_dY = _wtof(strData[1]);
	m_dWidth = _wtof(strData[2]);
	m_dHeight = _wtof(strData[3]);

	m_strFont_family = strData[4];
	m_nFont_size = _wtoi(strData[5]);
	m_strFont_style = strData[6];
	m_strFont_color = strData[7];
	m_strFont_anchor = strData[8];
	m_strFont_valign = strData[9];

	m_strStroke = strData[10];

	m_strFill = strData[11];

	m_nDrawOrder = _wtoi(strData[12]);

	m_strText = strData[13];


	m_strPSRType = strData[14];
	m_strID = strData[15];
	m_strPoint_type = strData[16];
	m_strPoint_code = strData[17];

	m_strDataType = strData[18];
	m_nShowSign = _wtoi(strData[19]);
	m_dDotForamt = _wtof(strData[20]);
	m_nShowUnit = _wtoi(strData[21]);

}

void CSB_Text_analog::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	Gdiplus::Brush* pBrush_stroke = GetBrush(m_strStroke, _T(""));
	Gdiplus::Brush* pBrush_fill = GetBrush(m_strFill, _T(""));
	Gdiplus::Brush* pBrush_Font = GetBrush(m_strFont_color, _T(""));


	Gdiplus::Pen					pen(pBrush_stroke, double(1.));

	Gdiplus::Font					_drawfont(m_strFont_family, double(m_nFont_size) * dZoomValue, GetFontStyle(m_strFont_style), UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment((Gdiplus::StringAlignment)GetFontAlignment(m_strFont_anchor));
	_drawStrFormat.SetLineAlignment((Gdiplus::StringAlignment)GetFontAlignment(m_strFont_valign));

	Gdiplus::RectF rStroke, rFill;

	rStroke.X = ptDraw.x + (m_dX * dZoomValue);
	rStroke.Y = ptDraw.y + (m_dY * dZoomValue);
	rStroke.Width = m_dWidth * dZoomValue;
	rStroke.Height = m_dHeight * dZoomValue;

	rFill = rStroke;
	rFill.Inflate(double(1.) * -1., double(1.) * -1.);

	if (m_strFill != _T("none"))
		graphics.FillRectangle(pBrush_fill, rFill);
	if (m_strStroke != _T("none"))
		graphics.DrawRectangle(&pen, rStroke);
	

	graphics.DrawString(m_strText, -1, &_drawfont, rStroke, &_drawStrFormat, pBrush_Font);

	delete pBrush_stroke;
	delete pBrush_fill;
	delete pBrush_Font;
}

CRect CSB_Text_analog::GetSBRect()
{
	CRect r;

	CRealPoint ptLT, ptRB;

	ptLT.x = m_dX;
	ptLT.y = m_dY;

	ptRB.x = m_dX + m_dWidth;
	ptRB.y = m_dY + m_dHeight;

	double dValue_LT[2], dValue_RB[2];

	GetValue_double2int(&ptLT, dValue_LT);
	GetValue_double2int(&ptRB, dValue_RB);

	r.SetRect(int(dValue_LT[0]), int(dValue_LT[1]), int(dValue_RB[0]), int(dValue_RB[1]));

	return r;

}

void	CSB_Text_analog::SetEdit_Move(CPoint pt)
{
	m_dX += pt.x;
	m_dY += pt.y;
}

void CSB_Text_analog::Copy(CSB_Object* pSBObj)
{
	CSB_Text_analog* pSBText = (CSB_Text_analog*)pSBObj;

	pSBText->m_dX = m_dX;
	pSBText->m_dY = m_dY;
	pSBText->m_dWidth = m_dWidth;
	pSBText->m_dHeight = m_dHeight;
	pSBText->m_strStroke = m_strStroke;
	pSBText->m_strFill = m_strFill;
	pSBText->m_nDrawOrder = m_nDrawOrder;

	pSBText->m_strFont_family = m_strFont_family;
	pSBText->m_nFont_size = m_nFont_size;
	pSBText->m_strFont_style = m_strFont_style;
	pSBText->m_strFont_color = m_strFont_color;
	pSBText->m_strFont_anchor = m_strFont_anchor;
	pSBText->m_strFont_valign = m_strFont_valign;
	pSBText->m_strText = m_strText;

	pSBText->m_strPSRType = m_strPSRType;
	pSBText->m_strID = m_strID;
	pSBText->m_strPoint_type = m_strPoint_type;
	pSBText->m_strPoint_code = m_strPoint_code;
	pSBText->m_strDataType = m_strDataType;
	pSBText->m_nShowSign = m_nShowSign;
	pSBText->m_dDotForamt = m_dDotForamt;
	pSBText->m_nShowUnit = m_nShowUnit;

}


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				ARC
////////////////////////////////////////////////////////////////////////////////

void					CSB_Arc::SetObjectData(CMarkup* pxml)
{
	CString strData[13];
	strData[0] = pxml->GetAttrib(_T("cx"));
	strData[1] = pxml->GetAttrib(_T("cy"));
	strData[2] = pxml->GetAttrib(_T("rx"));
	strData[3] = pxml->GetAttrib(_T("ry"));
	strData[4] = pxml->GetAttrib(_T("startangle"));
	strData[5] = pxml->GetAttrib(_T("endangle"));
	strData[6] = pxml->GetAttrib(_T("pie"));
	strData[7] = pxml->GetAttrib(_T("stroke"));
	strData[8] = pxml->GetAttrib(_T("stroke-width"));
	strData[9] = pxml->GetAttrib(_T("stroke-type"));
	strData[10] = pxml->GetAttrib(_T("draworder"));

	strData[11] = pxml->GetAttrib(_T("fill"));
	strData[12] = pxml->GetAttrib(_T("fill-type"));


	m_dCX = _wtof(strData[0]);
	m_dCY = _wtof(strData[1]);
	m_dRX = _wtof(strData[2]);
	m_dRY = _wtof(strData[3]);

	m_dAngle_start = _wtof(strData[4]);
	m_dAngle_end = _wtof(strData[5]);
	m_nPie = _wtoi(strData[6]);

	m_strStroke = strData[7];
	m_nStroke_width = _wtoi(strData[8]);
	m_strStroke_type = strData[9];

	m_nDrawOrder = _wtoi(strData[10]);

	m_strFill = strData[11];
	m_strFill_type = strData[12];

}

void CSB_Arc::GetObjectData_SVG(CMarkup* pxml, int nDrawOrder)
{
	CString strData[14];
	strData[0].Format(_T("%s"), _T(""));
	strData[1].Format(_T("%.6lf"), m_dCX);
	strData[2].Format(_T("%.6lf"), m_dCY);
	strData[3].Format(_T("%.6lf"), m_dRX);
	strData[4].Format(_T("%.6lf"), m_dRY);
	strData[5].Format(_T("%.6lf"), m_dAngle_start);
	strData[6].Format(_T("%.6lf"), m_dAngle_end);
	strData[7].Format(_T("%d"), m_nPie);
	strData[8].Format(_T("%s"), m_strStroke);
	strData[9].Format(_T("%d"), m_nStroke_width);
	strData[10].Format(_T("%s"), m_strStroke_type);
	strData[11].Format(_T("%s"), m_strFill);
	strData[12].Format(_T("%s"), m_strFill_type);
	strData[13].Format(_T("%d"), nDrawOrder);

	pxml->AddElem(m_strTagName);
	pxml->AddAttrib(_T("id"), strData[0]);
	pxml->AddAttrib(_T("cx"), strData[1]);
	pxml->AddAttrib(_T("cy"), strData[2]);
	pxml->AddAttrib(_T("rx"), strData[3]);
	pxml->AddAttrib(_T("ry"), strData[4]);
	pxml->AddAttrib(_T("startangle"), strData[5]);
	pxml->AddAttrib(_T("endangle"), strData[6]);
	pxml->AddAttrib(_T("pie"), strData[7]);
	pxml->AddAttrib(_T("stroke"), strData[8]);
	pxml->AddAttrib(_T("stroke-width"), strData[9]);
	pxml->AddAttrib(_T("stroke-type"), strData[10]);
	pxml->AddAttrib(_T("fill"), strData[11]);
	pxml->AddAttrib(_T("fill-type"), strData[12]);
	pxml->AddAttrib(_T("draworder"), strData[13]);
}



void CSB_Arc::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	Gdiplus::Brush* pBrush_stroke = GetBrush(m_strStroke, _T(""));
	UINT	unPenStyle = GetPenStyle(m_strStroke_type);
	Gdiplus::Pen					pen(pBrush_stroke, double(m_nStroke_width));
	pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);
	
	
	Gdiplus::Brush* pBrush_fill = GetBrush(m_strFill,m_strFill_type);

	double dAngle_s = m_dAngle_start / PI * 180.;
	double dAngle_e = m_dAngle_end / PI * 180.;

	if (m_nPie == 1)
	{
		Gdiplus::RectF rPie,rFill;


		rPie.X = ptDraw.x + (m_dCX * dZoomValue);
		rPie.Y = ptDraw.y + (m_dCY * dZoomValue);
		rPie.Width = 0.;/*m_dRX * dZoomValue *2*/;
		rPie.Height = 0.;;

		rPie.Inflate(m_dRX * dZoomValue, m_dRY* dZoomValue);
		
		rFill = rPie;

		rFill.Inflate(double(m_nStroke_width) * -1, double(m_nStroke_width) * -1);

		graphics.FillPie(pBrush_fill, rFill, dAngle_s,abs( dAngle_s - dAngle_e));
		graphics.DrawPie(&pen, rPie, dAngle_s, abs(dAngle_s - dAngle_e));
		

	}
	else
	{
		Gdiplus::RectF rArc;

		rArc.X = ptDraw.x + (m_dCX * dZoomValue);
		rArc.Y = ptDraw.y + (m_dCY * dZoomValue);
		rArc.Width = 0.;/*m_dRX * dZoomValue *2*/;
		rArc.Height = 0.;;

		rArc.Inflate(m_dRX * dZoomValue, m_dRY* dZoomValue);
		
		graphics.DrawArc(&pen, rArc, dAngle_s, dAngle_e);
	}

	

	delete pBrush_stroke;
	delete pBrush_fill;

}

CRect CSB_Arc::GetSBRect()
{
	//////////// angle 도 확인해야 되는데...
	CRect r;

	CRealPoint ptLT, ptRB;

	ptLT.x = m_dCX - m_dRX;
	ptLT.y = m_dCY - m_dRY;

	ptRB.x = m_dCX + m_dRX;
	ptRB.y = m_dCY + m_dRY;

	double dValue_LT[2], dValue_RB[2];

	GetValue_double2int(&ptLT, dValue_LT);
	GetValue_double2int(&ptRB, dValue_RB);

	r.SetRect(int(dValue_LT[0]), int(dValue_LT[1]), int(dValue_RB[0]), int(dValue_RB[1]));

	return r;

}

void	CSB_Arc::SetEdit_Move(CPoint pt)
{
	m_dCX += pt.x;
	m_dCY += pt.y;
}

void CSB_Arc::Copy(CSB_Object* pSBObj)
{
	CSB_Arc* pSBArc = (CSB_Arc*)pSBObj;

	pSBArc->m_dCX = m_dCX;
	pSBArc->m_dCY = m_dCY;
	pSBArc->m_dRX = m_dRX;
	pSBArc->m_dRY = m_dRY;
	pSBArc->m_strStroke = m_strStroke;
	pSBArc->m_nStroke_width = m_nStroke_width;
	pSBArc->m_strStroke_type = m_strStroke_type;
	pSBArc->m_strFill = m_strFill;
	pSBArc->m_strFill_type = m_strFill_type;
	pSBArc->m_nDrawOrder = m_nDrawOrder;
	pSBArc->m_dAngle_start = m_dAngle_start;
	pSBArc->m_dAngle_end = m_dAngle_end;
	pSBArc->m_nPie = m_nPie;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////				Polygon
////////////////////////////////////////////////////////////////////////////////

void					CSB_Polygon::SetObjectData(CMarkup* pxml)
{
	CString strData[7];
	strData[0] = pxml->GetAttrib(_T("points"));
	strData[1] = pxml->GetAttrib(_T("stroke"));
	strData[2] = pxml->GetAttrib(_T("stroke-width"));
	strData[3] = pxml->GetAttrib(_T("stroke-type"));
	strData[4] = pxml->GetAttrib(_T("fill"));
	strData[5] = pxml->GetAttrib(_T("fill-type"));
	strData[6] = pxml->GetAttrib(_T("draworder"));

	Split_Point(strData[0]);

	m_strStroke = strData[1];
	m_nStroke_width = _wtoi(strData[2]);
	m_strStroke_type = strData[3];

	m_strFill = strData[4];
	m_strFill_type = strData[5];

	m_nDrawOrder = _wtoi(strData[6]);

}

void CSB_Polygon::GetObjectData_SVG(CMarkup* pxml, int nDrawOrder)
{
	CString strData[8];
	strData[0].Format(_T("%s"), _T(""));

	strData[2].Format(_T("%s"), m_strStroke);
	strData[3].Format(_T("%d"), m_nStroke_width);
	strData[4].Format(_T("%s"), m_strStroke_type);
	strData[5].Format(_T("%s"), m_strFill);
	strData[6].Format(_T("%s"), m_strFill_type);
	strData[7].Format(_T("%d"), nDrawOrder);

	CString strPoint;
	CRealPoint* pPt;
	strData[1].Empty();
	for (int i = 0; i < m_Array_RealPoint.GetSize(); i++)
	{
		pPt = m_Array_RealPoint.GetAt(i);
		strPoint.Format(_T("%.0lf,%.0lf "), pPt->x, pPt->y);

		strData[1] += strPoint;
	}
	int nLen = strData[1].GetLength();
	strData[1].Delete(nLen - 1, 1);


	pxml->AddElem(m_strTagName);
	pxml->AddAttrib(_T("id"), strData[0]);
	pxml->AddAttrib(_T("points"), strData[1]);
	pxml->AddAttrib(_T("stroke"), strData[2]);
	pxml->AddAttrib(_T("stroke-width"), strData[3]);
	pxml->AddAttrib(_T("stroke-type"), strData[4]);
	pxml->AddAttrib(_T("fill"), strData[5]);
	pxml->AddAttrib(_T("fill-type"), strData[6]);
	pxml->AddAttrib(_T("draworder"), strData[7]);
}

void CSB_Polygon::Split_Point(CString strData)
{
	CString strS, strX, strY;
	int nCount = 0;
	CRealPoint *pPt;

	while (AfxExtractSubString(strS, strData, nCount, _T(' ')))
	{
		if (strS.IsEmpty())
			break;

		AfxExtractSubString(strX, strS, 0, _T(','));
		AfxExtractSubString(strY, strS, 1, _T(','));

		pPt = new CRealPoint();
		m_Array_RealPoint.Add(pPt);
		pPt->x = _wtof(strX);
		pPt->y = _wtof(strY);

		nCount++;
	}
}

void CSB_Polygon::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	Gdiplus::Brush* pBrush_stroke = GetBrush(m_strStroke, _T(""));
	UINT	unPenStyle = GetPenStyle(m_strStroke_type);
	Gdiplus::Pen					pen(pBrush_stroke, double(m_nStroke_width));
	pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);
	
	int nSize = m_Array_RealPoint.GetSize();
	CRealPoint* pPoint;
	Gdiplus::PointF	pt[100];
	
	for (int i = 0; i < m_Array_RealPoint.GetSize() ; i++)
	{
		pPoint = m_Array_RealPoint.GetAt(i);
	
		pt[i].X = double(ptDraw.x) + (pPoint->x * dZoomValue) ;
		pt[i].Y = double(ptDraw.y) + (pPoint->y * dZoomValue);

	}

	m_GDI_path.Reset();
	m_GDI_path.AddPolygon(pt, nSize);
	
	Gdiplus::Brush* pBrush_fill = GetBrush(m_strFill, m_strFill_type);

	graphics.FillPolygon(pBrush_fill, pt, nSize);
	graphics.DrawPolygon(&pen, pt, nSize);



	delete pBrush_stroke;
	delete pBrush_fill;

}

CRect CSB_Polygon::GetSBRect()
{
	CRect r;
	int nL(999999), nT(999999), nR(-999999), nB(-9999999);
	CRealPoint *pt;
	double dValue[2];

	for (int i = 0; i < m_Array_RealPoint.GetSize(); i++)
	{
		pt = m_Array_RealPoint.GetAt(i);

		GetValue_double2int(pt, dValue);

		if (pt->x < nL)
		{
			nL = (int)pt->x;
		}
		if (pt->x > nR)
		{
			nR = (int)pt->x;
		}

		if (pt->y < nT)
		{
			nT = (int)pt->y;
		}
		if (pt->y > nB)
		{
			nB = (int)pt->y;
		}
	}

	r.SetRect(nL, nT, nR, nB);

	return r;

}

void	CSB_Polygon::SetEdit_Move(CPoint pt)
{
	CRealPoint *ptReal;
	for (int i = 0; i < m_Array_RealPoint.GetSize(); i++)
	{
		ptReal = m_Array_RealPoint.GetAt(i);

		ptReal->x += double(pt.x);
		ptReal->y += double(pt.y);
	}
}

void CSB_Polygon::Copy(CSB_Object* pSBObj)
{
	CSB_Polygon* pSBPolygon = (CSB_Polygon*)pSBObj;
	   	 
	pSBPolygon->m_strStroke = m_strStroke;
	pSBPolygon->m_nStroke_width = m_nStroke_width;
	pSBPolygon->m_strStroke_type = m_strStroke_type;
	pSBPolygon->m_strFill = m_strFill;
	pSBPolygon->m_strFill_type = m_strFill_type;
	pSBPolygon->m_nDrawOrder = m_nDrawOrder;

	CRealPoint *ptReal, *ptNew;
	for (int i = 0; i < m_Array_RealPoint.GetSize(); i++)
	{
		ptReal = m_Array_RealPoint.GetAt(i);

		ptNew = new CRealPoint();
		pSBPolygon->m_Array_RealPoint.Add(ptNew);
		ptNew->x = ptReal->x;
		ptNew->y = ptReal->y;
	}
}