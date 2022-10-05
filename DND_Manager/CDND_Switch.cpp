#include "pch.h"
#include "CDND_Switch.h"
#include "../SB_Manager/CSB_Manager.h"


CDND_Switch::CDND_Switch(void)
{
	m_pParent = NULL;
}

CDND_Switch::~CDND_Switch(void)
{
	m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.RemoveAll();
	m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.RemoveAll();
	m_st_Kasim_SVR_Info.stKASIM_SVR_BR_Arry.RemoveAll();

	for (int i = 0; i < m_Array_Multi.GetSize(); i++)
	{
		delete m_Array_Multi.GetAt(i);
	}
	m_Array_Multi.RemoveAll();

	for (int i = 0; i < m_Array_SBObject.GetSize(); i++)
	{
		delete m_Array_SBObject.GetAt(i);
	}
	m_Array_SBObject.RemoveAll();
}

void CDND_Switch::SetObjectData(CMarkup* pxml)
{
	CString strData[17];

	strData[0] = pxml->GetAttrib(_T("id"));
	strData[1] = pxml->GetAttrib(_T("psrtype"));
	strData[2] = pxml->GetAttrib(_T("keyid"));
	strData[3] = pxml->GetAttrib(_T("type"));
	strData[4] = pxml->GetAttrib(_T("keyname"));
	strData[5] = pxml->GetAttrib(_T("linktitleid"));
	strData[6] = pxml->GetAttrib(_T("x"));
	strData[7] = pxml->GetAttrib(_T("y"));
	strData[8] = pxml->GetAttrib(_T("scalex"));
	strData[9] = pxml->GetAttrib(_T("scaley"));
	strData[10] = pxml->GetAttrib(_T("rotate"));
	strData[11] = pxml->GetAttrib(_T("innertext"));
	strData[12] = pxml->GetAttrib(_T("devref"));
	strData[13] = pxml->GetAttrib(_T("devrefname"));
	strData[14] = pxml->GetAttrib(_T("usertype"));
	strData[15] = pxml->GetAttrib(_T("draworder"));

	strData[16] = pxml->GetAttrib(_T("roundbox"));

	m_str_id = strData[0];
	m_str_psrtype = strData[1];
	m_str_keyid = strData[2];

	m_n_type = _wtoi(strData[3]);

	m_str_keyname = strData[4];
	m_str_linktitleid = strData[5];

	m_d_x = _wtof(strData[6]);
	m_d_y = _wtof(strData[7]);
	m_d_scalex = _wtof(strData[8]);
	m_d_scaley = _wtof(strData[9]);
	m_d_rotate = _wtof(strData[10]);
	m_str_innertext = strData[11];
	m_n_devref = _wtoi(strData[12]);
	m_str_devrefname = strData[13];
	m_n_usertype = _wtoi(strData[14]);
	m_n_draworder = _wtoi(strData[15]);
	
	CSB_Manager* pSBMng = CSB_Manager::Instance();
		
	m_SB_Object = pSBMng->GetBlock_SB(m_n_devref);
	if (m_SB_Object == NULL)
	{
		TRACE(_T("%d\n"), m_n_devref);
	}

	if (ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
	{
		CString strTagName;
		CDND_Switch* pDND_Sw;
		CSB_Layer	sbLayer;
		CSB_Object* pSBObj;

		m_strRoundbox = strData[16];

		while (pxml->FindChildElem())
		{
			pxml->IntoElem();

			strTagName = pxml->GetTagName();

			TRACE(_T("%s\n"), strTagName);

			if (strTagName == _T("BLOCK"))
			{
				pDND_Sw = new CDND_Switch();
				pDND_Sw->ObjectType_Set(DND_OBJTYPE_MULTI_M);
				m_Array_Multi.Add(pDND_Sw);
				pDND_Sw->SetObjectData(pxml);
				pDND_Sw->m_pParent = this;
			}
			else //// DRAW
			{
				pSBObj = sbLayer.SBObject_Create(strTagName,FALSE);
				m_Array_SBObject.Add(pSBObj);
				pSBObj->SetObjectData(pxml);
			}

			pxml->OutOfElem();
		}
	}
}

void CDND_Switch::GetObjectData(CMarkup* pxml, int&  nDrawOrder)
{
	CString strData[16];
	strData[0].Format(_T("%s"), m_str_id);
	strData[1].Format(_T("%s"), m_str_psrtype);
	strData[2].Format(_T("%s"), m_str_keyid);
	strData[3].Format(_T("%d"), m_n_type);
	strData[4].Format(_T("%s"), m_str_keyname);
	strData[5].Format(_T("%s"), _T(""));
	strData[6].Format(_T("%.0lf"), m_d_x);
	strData[7].Format(_T("%.0lf"), m_d_y);
	strData[8].Format(_T("%.4lf"), m_d_scalex);
	strData[9].Format(_T("%.4lf"), m_d_scaley);
	strData[10].Format(_T("%.4lf"), m_d_rotate);
	strData[11].Format(_T("%s"), m_str_innertext);
	strData[12].Format(_T("%d"), m_n_devref);
	strData[13].Format(_T("%s"), m_str_devrefname);
	strData[14].Format(_T("%d"), m_n_usertype);
	strData[15].Format(_T("%d"), nDrawOrder);


	if (ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
	{
		pxml->AddElem(_T("MULTIBLOCK"));
		/////////////////  roundbox, 
		///////////////////  없는거 innertext usertype rotate
	}
	else
	{
		pxml->AddElem(_T("BLOCK"));
	}
	
	pxml->AddAttrib(_T("id"), strData[0]);
	pxml->AddAttrib(_T("psrtype"), strData[1]);
	pxml->AddAttrib(_T("keyid"), strData[2]);
	pxml->AddAttrib(_T("type"), strData[3]);
	pxml->AddAttrib(_T("keyname"), strData[4]);
	pxml->AddAttrib(_T("linktitleid"), strData[5]);
	pxml->AddAttrib(_T("x"), strData[6]);
	pxml->AddAttrib(_T("y"), strData[7]);
	pxml->AddAttrib(_T("scalex"), strData[8]);
	pxml->AddAttrib(_T("scaley"), strData[9]);

	if (ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
	{
		CRect r = GetRect_Real();
		CString strRound;
		strRound.Format(_T("%d,%d,%d,%d"), r.left, r.top, r.Width(), r.Height());
		pxml->AddAttrib(_T("roundbox"), strRound);
	}
	else if (ObjectType_Get() == DND_OBJTYPE_MULTI_M)
	{
		pxml->AddAttrib(_T("rotate"), strData[10]);
		pxml->AddAttrib(_T("innertext"), strData[11]);
		pxml->AddAttrib(_T("roundbox"), _T(""));
	}
	else
	{
		pxml->AddAttrib(_T("rotate"), strData[10]);
		pxml->AddAttrib(_T("innertext"), strData[11]);
		pxml->AddAttrib(_T("usertype"), strData[14]);
	}

	pxml->AddAttrib(_T("devref"), strData[12]);
	pxml->AddAttrib(_T("devrefname"), strData[13]);
	pxml->AddAttrib(_T("draworder"), strData[15]);

	if (ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
	{
		pxml->IntoElem();
		CDND_Object* pMulti_M;
		for (int i = 0; i < m_Array_Multi.GetSize(); i++)
		{
			pMulti_M = m_Array_Multi.GetAt(i);
			nDrawOrder++;
			pMulti_M->GetObjectData(pxml,nDrawOrder);
		}

		CSB_Object* pSBObj;
		for (int i = 0; i < m_Array_SBObject.GetSize(); i++)
		{
			pSBObj = m_Array_SBObject.GetAt(i);
			nDrawOrder++;
			pSBObj->GetObjectData_SVG(pxml, nDrawOrder);
		}
		pxml->OutOfElem();
	}
	
}

BOOL	CDND_Switch::Check2DwawRect(CRect rDraw, double dZoomValue)
{
	CPoint pt(int(m_d_x * dZoomValue), int(m_d_y * dZoomValue));

	return rDraw.PtInRect(pt);
}

CDND_Object* CDND_Switch::Select2Point(CPoint pt, CDND_Object* pSelect)
{
	if (ObjectType_Get() == DND_OBJTYPE_BLOCK 
		|| ObjectType_Get() == DND_OBJTYPE_MULTI_M)
	{
		if (m_SB_Object)
		{
			CRect rect = ((CSB_BLOCK*)m_SB_Object)->GetSBRect();
			CPoint ptReal;
			ptReal.x = int(m_d_x);
			ptReal.y = int(m_d_y);


			rect += ptReal;

			if (rect.PtInRect(pt))
			{
				m_Point_Move.x = int(m_d_x);
				m_Point_Move.y = int(m_d_y);
				return this;
			}
		}
		
	}
	else
	{
		CDND_Switch* pSubSw;
		CDND_Object* pSelectSw;
		for (int i = 0; i < m_Array_Multi.GetSize(); i++)
		{
			pSubSw = (CDND_Switch*)m_Array_Multi.GetAt(i);
			pSelectSw = pSubSw->Select2Point(pt, pSelect);
			if (pSelectSw)
			{
				if (pSelect)
				{
					if (pSelect->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
					{
						if (this == pSelect)
						{
							return pSelectSw;
						}

					}
					else if (pSelect->ObjectType_Get() == DND_OBJTYPE_MULTI_M)
					{
						if (pSelect == pSelectSw)
						{
							m_Point_Move.x = int(m_d_x);
							m_Point_Move.y = int(m_d_y);
							return this;
						}
						else if (this == ((CDND_Switch*)pSelect)->m_pParent)
						{
							return pSelectSw;
						}
					}
				}
				
				return this;
				
			}
		}
	}

	return NULL;
}

CDND_Object* CDND_Switch::Select2Point_Cancel(CPoint pt, CDND_Object* pSelect)
{
	if (ObjectType_Get() == DND_OBJTYPE_BLOCK
		|| ObjectType_Get() == DND_OBJTYPE_MULTI_M)
	{
		if (m_SB_Object)
		{
			CRect rect ;
			CPoint ptReal;
			if (((CSB_BLOCK*)m_SB_Object)->m_strPSRType == "CABLEPOLE" || ((CSB_BLOCK*)m_SB_Object)->m_strPSRType == "JUNCTION")
			{
				rect = { -15,-15,15,15 };
				ptReal;
				ptReal.x = int(m_d_x);
				ptReal.y = int(m_d_y);
			}
			else
			{
				rect = ((CSB_BLOCK*)m_SB_Object)->GetSBRect();
				ptReal;
				ptReal.x = int(m_d_x); 
				ptReal.y = int(m_d_y);
			}

			rect = rect+ptReal;

			if (rect.PtInRect(pt))
			{
				m_Point_Move.x = int(m_d_x);
				m_Point_Move.y = int(m_d_y);
				return this;
			}
		}

	}
	else
	{
		CDND_Switch* pSubSw;
		CDND_Object* pSelectSw;
		for (int i = 0; i < m_Array_Multi.GetSize(); i++)
		{
			pSubSw = (CDND_Switch*)m_Array_Multi.GetAt(i);
			pSelectSw = pSubSw->Select2Point(pt, pSelect);
			if (pSelectSw)
			{
				if (pSelect)
				{
					if (pSelect->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
					{
						if (this == pSelect)
						{
							return pSelectSw;
						}

					}
					else if (pSelect->ObjectType_Get() == DND_OBJTYPE_MULTI_M)
					{
						if (pSelect == pSelectSw)
						{
							m_Point_Move.x = int(m_d_x);
							m_Point_Move.y = int(m_d_y);
							return this;
						}
						else if (this == ((CDND_Switch*)pSelect)->m_pParent)
						{
							return pSelectSw;
						}
					}
				}

				return this;

			}
		}
	}

	return NULL;
}


void CDND_Switch::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	if (dZoomValue < DRAW_ZOOMLEVEL)
	{
		return;
	}
	ptDraw.x = int(m_d_x);
	ptDraw.y = int(m_d_y);

	dScale_x *= m_d_scalex;
	dScale_y *= m_d_scaley;
	//ASSERT(m_str_id != _T("0_GROUP_86"));

	CString strScript; /////////////// 상태 조건

	//ASSERT(m_d_rotate == 0.);

	
	/*Matrix transMatrix;
	graphics.GetTransform(&transMatrix);
	double x = transMatrix.OffsetX();
	double y = transMatrix.OffsetY();*/
	graphics.TranslateTransform(m_d_x, m_d_y);
	graphics.ScaleTransform(dScale_x, dScale_y);
	graphics.RotateTransform(m_d_rotate);
	graphics.TranslateTransform(m_d_x * -1, m_d_y * -1);

	if (ObjectType_Get() == DND_OBJTYPE_BLOCK)
	{
		if (m_SB_Object)
			((CSB_BLOCK*)m_SB_Object)->Draw(graphics, ptDraw, dZoomValue, strScript, dScale_x, dScale_y, dAngle, m_str_innertext);
	}
	else if (ObjectType_Get() == DND_OBJTYPE_MULTI_M)
	{
		if (m_SB_Object)
			((CSB_BLOCK*)m_SB_Object)->Draw(graphics, ptDraw, dZoomValue, strScript, dScale_x, dScale_y, dAngle, m_str_innertext);
	}
	else  //////////////DND_OBJTYPE_MULTIBLOCK
	{
		CDND_Switch* pSubSw;
		for (int i = 0; i < m_Array_Multi.GetSize(); i++)
		{
			pSubSw = (CDND_Switch*)m_Array_Multi.GetAt(i);
			pSubSw->Draw_Object(graphics, ptDraw, dZoomValue,  dScale_x, dScale_y, dAngle, strInnerText);
		}

		CSB_Object* pSBObj;
		for (int i = 0; i < m_Array_SBObject.GetSize(); i++)
		{
			pSBObj = (CSB_Object*)m_Array_SBObject.GetAt(i);
			pSBObj->Draw_Object(graphics, CPoint(0,0), 1., dScale_x, dScale_y, dAngle, strInnerText);
		}
	}
	graphics.TranslateTransform(m_d_x, m_d_y);
	graphics.RotateTransform(m_d_rotate * -1);
	graphics.ScaleTransform(1 / dScale_x, 1 / dScale_y);
	graphics.TranslateTransform(m_d_x * -1, m_d_y * -1);
	
	//
	/*Gdiplus::Font					_drawfont(_T("맑은 고딕"), 14.0f, FontStyle::FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawTitlebrush(Color(255, 255, 255, 255));

	RectF rStroke;
	rStroke.X = m_d_x;
	rStroke.Y = m_d_y;
	rStroke.Width = 200;
	rStroke.Height = 20;
	graphics.DrawString(m_str_id, m_str_id.GetLength(), &_drawfont, rStroke, &_drawStrFormat, &_drawTitlebrush);*/
}

CRect CDND_Switch::GetRect_Real()
{
	///////////////////// 회전한 객체의 회전값을 판단해야 된다. 201104
	CRect rect;
	if (ObjectType_Get() == DND_OBJTYPE_BLOCK
		|| ObjectType_Get() == DND_OBJTYPE_MULTI_M)
	{
		if (m_SB_Object)
		{
			CRect r = ((CSB_BLOCK*)m_SB_Object)->GetSBRect();
			CPoint ptReal;
			ptReal.x = int(m_d_x);
			ptReal.y = int(m_d_y);
			r += ptReal;		
			rect = r;
		}

	}
	else
	{
		CDND_Switch* pSubSw;
		int nL(999999), nT(999999), nR(-999999), nB(-9999999);

		CRect r;

		for (int i = 0; i < m_Array_Multi.GetSize(); i++)
		{
			pSubSw = (CDND_Switch*)m_Array_Multi.GetAt(i);

			r = pSubSw->GetRect_Real();

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

		rect.SetRect(nL, nT, nR, nB);

		
	}
	return rect;
}

void CDND_Switch::Draw_Object_Select(Graphics &graphics, CPoint ptDraw, double dZoomValue	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	if (dZoomValue < DRAW_ZOOMLEVEL)
	{
		return;
	}
	ptDraw.x = int(m_d_x);
	ptDraw.y = int(m_d_y);

	dScale_x *= m_d_scalex;
	dScale_y *= m_d_scaley;
	//ASSERT(m_str_id != _T("0_GROUP_86"));

	CString strScript; /////////////// 상태 조건

	graphics.TranslateTransform(m_d_x, m_d_y);
	graphics.RotateTransform(m_d_rotate);
	graphics.TranslateTransform(m_d_x * -1, m_d_y * -1);


	SolidBrush penBrush(Color(255, 255, 255));
	Gdiplus::Pen					pen(&penBrush, 2.);
	pen.SetDashStyle((Gdiplus::DashStyle)DashStyleDash);

	CRect r = GetRect_Real();

	Gdiplus::RectF rStroke; 

	rStroke.X = r.left;
	rStroke.Y = r.top;
	rStroke.Width = r.Width();
	rStroke.Height = r.Height();

	rStroke.Inflate(3, 3);
	graphics.DrawRectangle(&pen, rStroke);

	//////////////////////////////////
	graphics.TranslateTransform(m_d_x, m_d_y);
	graphics.RotateTransform(m_d_rotate * -1);
	graphics.TranslateTransform(m_d_x * -1, m_d_y * -1);

}

void CDND_Switch::Draw_Object_Select_Move(Graphics &graphics, CPoint ptDraw, double dZoomValue, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	if (dZoomValue < DRAW_ZOOMLEVEL)
	{
		return;
	}
	ptDraw.x = int(m_d_x);
	ptDraw.y = int(m_d_y);

	dScale_x *= m_d_scalex;
	dScale_y *= m_d_scaley;
	//ASSERT(m_str_id != _T("0_GROUP_86"));

	CString strScript; /////////////// 상태 조건

	graphics.TranslateTransform(m_d_x, m_d_y);
	graphics.RotateTransform(m_d_rotate);
	graphics.TranslateTransform(m_d_x * -1, m_d_y * -1);


	SolidBrush penBrush(Color(255, 255, 255));
	Gdiplus::Pen					pen(&penBrush, 2.);
	pen.SetDashStyle((Gdiplus::DashStyle)DashStyleDash);

	CRect r = GetRect_Real();

	Gdiplus::RectF rStroke;

	rStroke.X =  m_d_x;
	rStroke.Y =  m_d_y;
	rStroke.Width = 5;
	rStroke.Height = 5;

/*	rStroke.Inflate(0.1, 0.1);*/

	graphics.FillEllipse(&penBrush, rStroke);
	graphics.FillEllipse(&penBrush, rStroke);
	graphics.FillEllipse(&penBrush, rStroke);
	graphics.FillEllipse(&penBrush, rStroke);





	//////////////////////////////////
// 	graphics.TranslateTransform(m_d_x, m_d_y);
// 	graphics.RotateTransform(m_d_rotate * -1);
// 	graphics.TranslateTransform(m_d_x * -1, m_d_y * -1);


}

void CDND_Switch::Draw_Object_Move(Graphics &graphics, CPoint ptDraw, double dZoomValue	, double dScale_x, double dScale_y, double dAngle)
{
	if (dZoomValue < DRAW_ZOOMLEVEL)
	{
		return;
	}
	ptDraw = m_Point_Move;

	dScale_x *= m_d_scalex;
	dScale_y *= m_d_scaley;
	//ASSERT(m_str_id != _T("0_GROUP_86"));

	CString strScript; /////////////// 상태 조건

	//ASSERT(m_d_rotate == 0.);


	graphics.TranslateTransform(double(ptDraw.x), double(ptDraw.y));
	graphics.RotateTransform(m_d_rotate);
	graphics.TranslateTransform(double(ptDraw.x) * -1, double(ptDraw.y) * -1);

	SolidBrush penBrush(Color(255, 255, 255));
	Gdiplus::Pen					pen(&penBrush, 2.);
	pen.SetDashStyle((Gdiplus::DashStyle)DashStyleDash);

	CRect r = GetRect_Real();

	Gdiplus::RectF rStroke;
	
	rStroke.X = ptDraw.x  - (r.Width()/2) ;
	rStroke.Y = ptDraw.y -  (r.Height() / 2);
	rStroke.Width = r.Width();
	rStroke.Height = r.Height();

	rStroke.Inflate(2, 2);
	graphics.DrawRectangle(&pen, rStroke);

	//////////////////////////////////
	graphics.TranslateTransform(double(ptDraw.x), double(ptDraw.y));
	graphics.RotateTransform(m_d_rotate * -1);
	graphics.TranslateTransform(double(ptDraw.x) * -1, double(ptDraw.y) * -1);


}

void CDND_Switch::SetEdit_Move(CPoint pt)
{
	if (ObjectType_Get() == DND_OBJTYPE_BLOCK
		|| ObjectType_Get() == DND_OBJTYPE_MULTI_M)
	{
		m_d_x = double(pt.x);
		m_d_y = double(pt.y);
	}
	else
	{
		CRect r = GetRect_Real();

		CPoint ptGap = pt - r.CenterPoint();

		CDND_Switch* pSubSw;
		CSB_Object* pSBObj;

		for (int i = 0; i < m_Array_Multi.GetSize(); i++)
		{
			pSubSw = (CDND_Switch*)m_Array_Multi.GetAt(i);
			pSubSw->m_d_x += double(ptGap.x);
			pSubSw->m_d_y += double(ptGap.y);
		}

		for (int i = 0; i < m_Array_SBObject.GetSize(); i++)
		{
			pSBObj = m_Array_SBObject.GetAt(i);
			pSBObj->SetEdit_Move(ptGap);
		}
	}

	SetEditType(DND_OBJ_EDIT_UPDATE);
}

void CDND_Switch::Draw_Object_Select_Cancel(Graphics &graphics, CPoint ptDraw, double dZoomValue, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	if (dZoomValue < DRAW_ZOOMLEVEL)
	{
		return;
	}
	ptDraw.x = int(m_d_x);
	ptDraw.y = int(m_d_y);

	dScale_x *= m_d_scalex;
	dScale_y *= m_d_scaley;
	//ASSERT(m_str_id != _T("0_GROUP_86"));

	CString strScript; /////////////// 상태 조건

	graphics.TranslateTransform(m_d_x, m_d_y);
	graphics.RotateTransform(m_d_rotate);
	graphics.TranslateTransform(m_d_x * -1, m_d_y * -1);


	SolidBrush penBrush(Color(255, 0, 221));
	Gdiplus::Pen					pen(&penBrush, 2.);
	pen.SetDashStyle((Gdiplus::DashStyle)DashStyleDash);

	CRect r = GetRect_Real();

	Gdiplus::RectF rStroke;

	rStroke.X = r.left;
	rStroke.Y = r.top;
	rStroke.Width = r.Width();
	rStroke.Height = r.Height();

	rStroke.Inflate(2, 2); //선택된 선로 !!!! 좌우 를 표시 할때 
	graphics.DrawRectangle(&pen, rStroke);

	//////////////////////////////////
	graphics.TranslateTransform(m_d_x, m_d_y);
	graphics.RotateTransform(m_d_rotate * -1);
	graphics.TranslateTransform(m_d_x * -1, m_d_y * -1);
}

void CDND_Switch::SetEdit_InitData_Devref(int nID, CPoint pt)
{
	SetEditType(DND_OBJ_EDIT_NEW);
	CSB_Manager* pSBMng = CSB_Manager::Instance();

	CSB_BLOCK* pSBObj;

	pSBObj = (CSB_BLOCK*)pSBMng->GetBlock_SB(m_n_devref);

	if (pSBObj == NULL)
	{
		AfxMessageBox(_T("Symbol menu ID err !!")); ////////////////// 말이 안되긴 하는데
	}
	
	m_str_id.Format(_T("0_BLOCK_EDIT_%d"), nID);
	


	m_str_psrtype = pSBObj->m_strPSRType;
	m_str_keyid.Empty();

	m_n_type = 1;

	m_str_keyname.Empty();
	m_str_linktitleid.Empty();

	m_d_scalex = 1.;
	m_d_scaley = 1.;
	m_d_rotate = 0.;

	m_str_devrefname = pSBObj->GetName();
	m_n_usertype = 0;
	m_n_draworder = 0;
	m_SB_Object = pSBObj;


	if (m_SB_Object == NULL)
	{
		TRACE(_T("%d\n"), m_n_devref);
	}
	
	CRect r = m_SB_Object->GetSBRect();
	m_d_x += double(pt.x);
	m_d_y += double(pt.y);
}

void CDND_Switch::SetEdit_InitData(int nID, CPoint pt, int nResourceID /* = -1 */)
{
	SetEditType(DND_OBJ_EDIT_NEW);
	CSB_Manager* pSBMng = CSB_Manager::Instance();

	CSB_BLOCK* pSBObj;

	pSBObj = (CSB_BLOCK*)pSBMng->GetBlock_SB2ResourceID(nResourceID);

	if (pSBObj == NULL)
	{
		AfxMessageBox(_T("Symbol menu ID err !!")); ////////////////// 말이 안되긴 하는데
	}
	
	if (pSBObj->ObjType_Get() == SBOBJECT_TYPE_MULTIBLOCK)
	{
		m_str_id.Format(_T("0_GROUP_EDIT_%d"), nID);
	}
	else
	{
		m_str_id.Format(_T("0_BLOCK_EDIT_%d"), nID);
	}


	m_str_psrtype = pSBObj->m_strPSRType;
	m_str_keyid.Empty();

	m_n_type = 1;

	m_str_keyname.Empty();
	m_str_linktitleid.Empty();

	m_d_scalex = 1.;
	m_d_scaley = 1.;
	m_d_rotate = 0.;

	m_str_innertext.Empty();

	m_n_devref = pSBObj->GetID();

	m_str_devrefname = pSBObj->GetName();

	m_n_usertype = 0;

	m_n_draworder = 0;

	m_SB_Object = pSBObj;

	   
	if (m_SB_Object == NULL)
	{
		TRACE(_T("%d\n"), m_n_devref);
	}

	//CRect r = m_SB_Object->GetSBRect();
	m_d_x = double(pt.x);
	m_d_y = double(pt.y);

	if (ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
	{
		CString strTagName;
		CDND_Switch* pDND_Sw;
		CSB_Layer	sbLayer;

		CSB_Layer*	pSBLayer;
		CSB_Object* pSBObj_Sub, *pSBObj_Draw;
		CSB_BLOCK_M* pMulti_M;
		CRealPoint ptSB;

		m_strRoundbox.Empty();

		pSBLayer = (CSB_Layer*)pSBObj->m_Array_Layer.GetAt(0);

		for (int i = 0; i < pSBLayer->m_Array_DrawObject.GetSize(); i++)
		{
			pSBObj_Sub = pSBLayer->m_Array_DrawObject.GetAt(i);

			if (pSBObj_Sub->ObjType_Get() == SBOBJECT_TYPE_BLOCK_M)
			{
				pMulti_M = (CSB_BLOCK_M*)pSBObj_Sub;
				pMulti_M->GetPoint(&ptSB);

				pDND_Sw = new CDND_Switch();
				pDND_Sw->ObjectType_Set(DND_OBJTYPE_MULTI_M);
				m_Array_Multi.Add(pDND_Sw);
				pDND_Sw->m_pParent = this;
				pDND_Sw->m_n_devref = pMulti_M->GetDevref();
				pDND_Sw->m_d_x = ptSB.x;
				pDND_Sw->m_d_y = ptSB.y;
				pDND_Sw->m_str_innertext = pMulti_M->GetInnerText();
				//////
			}
			else //// DRAW
			{
				pSBObj_Draw = sbLayer.SBObject_Create(pSBObj_Sub->GetTagName(), FALSE);
				m_Array_SBObject.Add(pSBObj_Draw);
				pSBObj_Sub->Copy(pSBObj_Draw);
				pSBObj_Draw->SetEdit_Move(pt);
				//pSBObj_Draw->SetObjectData(pxml);
			}
		}
	}
	
}

void CDND_Switch::SetEdit_InitData_KASIM_MU_CBSW(int nID, int nNd, int nINDEX, int nCBSWt_Type, int nPRDEID )
{
	CString stCEQID, stNM, stMUCEQID;
	int m_nKASIM_MUSND_Index = 0;
	stCEQID.Format(_T("999921%08d"), nID);
	stNM.Format(_T("SW%08d"), nID);
	m_str_keyid = stCEQID;
	m_str_keyname = stNM;
	m_st_Kasim_CBSW_Info.m_nCBSWID = nID;

	//생성하는 부분을 여기서 만들면?20210712
	if (nCBSWt_Type == 2 || nCBSWt_Type == 5 || nCBSWt_Type == 6 || nCBSWt_Type == 1)
	{
		m_st_Kasim_CBSW_Info.m_nCBSW_PRDE = nPRDEID;
		if (nINDEX == 0)
		{
			m_st_Kasim_CBSW_Info.m_nCBSW_Fnd = nNd;
			m_st_Kasim_CBSW_Info.m_nCBSW_Tnd = nNd + 1;
			m_nKASIM_MUSND_Index = nNd + 1;
			stMUCEQID.Format(_T("999921%08d"), m_nKASIM_MUSND_Index);
			Set_NEW_InitData_KASIM_CBSW(stNM, stCEQID, stMUCEQID, nID, nNd, m_nKASIM_MUSND_Index, nINDEX + 1, nCBSWt_Type, nPRDEID);
		}
		else
		{
			m_st_Kasim_CBSW_Info.m_nCBSW_Fnd = nNd - nINDEX;
			m_st_Kasim_CBSW_Info.m_nCBSW_Tnd = nNd;
			m_nKASIM_MUSND_Index = nNd - nINDEX;
			stMUCEQID.Format(_T("999921%08d"), m_nKASIM_MUSND_Index);
			Set_NEW_InitData_KASIM_CBSW(stNM, stCEQID, stMUCEQID, nID, m_nKASIM_MUSND_Index, nNd, nINDEX + 1, nCBSWt_Type, nPRDEID);
		}
	}
	else
	{
		m_st_Kasim_CBSW_Info.m_nCBSW_PRDE = 0;
		if (nINDEX == 0)
		{
			m_st_Kasim_CBSW_Info.m_nCBSW_Fnd = nNd ;
			m_st_Kasim_CBSW_Info.m_nCBSW_Tnd = nNd + 1;
			m_nKASIM_MUSND_Index = nNd + 1;
			stMUCEQID.Format(_T("999921%08d"), m_nKASIM_MUSND_Index);
			Set_NEW_InitData_KASIM_CBSW(stNM, stCEQID, stMUCEQID, nID, nNd, m_nKASIM_MUSND_Index, nINDEX + 1, nCBSWt_Type, 0);
		}
		else
		{
			m_st_Kasim_CBSW_Info.m_nCBSW_Fnd = nNd - nINDEX;
			m_st_Kasim_CBSW_Info.m_nCBSW_Tnd = nNd;
			m_nKASIM_MUSND_Index = nNd - nINDEX;
			stMUCEQID.Format(_T("999921%08d"), m_nKASIM_MUSND_Index);
			Set_NEW_InitData_KASIM_CBSW(stNM, stCEQID, stMUCEQID, nID, m_nKASIM_MUSND_Index, nNd, nINDEX + 1, nCBSWt_Type, 0);
		}
	}
}
	
void CDND_Switch::SetEdit_InitData_KASIM_CBSW(int nCBSWID, int nFNDID, int nTNDID, int nPRDEID, int nSwType)
{
	CString stCEQID, stNM, stDLCEQID;
	//DL
	if ( nSwType == 1)
	{
		stCEQID.Format(_T("999914%08d"), nCBSWID);
		stNM.Format(_T("SW%08d"), nCBSWID);
		m_str_keyid = stCEQID;
		m_str_keyname = stNM;

		stDLCEQID.Format(_T("999913%08d"), nCBSWID);
		m_str_keyid_dl = stDLCEQID;
	}
	else
	{
		stCEQID.Format(_T("999921%08d"), nCBSWID);
		stNM.Format(_T("SW%08d"), nCBSWID);
		m_str_keyid = stCEQID;
		m_str_keyname = stNM;
	}
	//
	m_st_Kasim_CBSW_Info.m_nCBSWID = nCBSWID;
	m_st_Kasim_CBSW_Info.m_nCBSW_Fnd = nFNDID;
	m_st_Kasim_CBSW_Info.m_nCBSW_Tnd = nTNDID;
	if (nSwType == 2 || nSwType == 5 || nSwType == 6 || nSwType == 1)
	{
		m_st_Kasim_CBSW_Info.m_nCBSW_PRDE = nPRDEID;
	}
	else
	{
		m_st_Kasim_CBSW_Info.m_nCBSW_PRDE = 0;
	}
}

void CDND_Switch::SetEdit_InitData_KASIM_ND(int nID)
{
	CString stCEQID, stNM;
	stCEQID.Format(_T("999929%08d"), nID);
	stNM.Format(_T("ND%08d"), nID);
	m_str_keyid = stCEQID;
	m_str_keyname = stNM;

	m_st_Kasim_ND_Info.m_nNDID = nID;
}

void CDND_Switch::SetEdit_InitData_KASIM_GEN(int nGEN_ID, int nND_ID, int nIJ_ID, int nPRDE_ID)
{
	CString stCEQID, stNM;
	stCEQID.Format(_T("999937%08d"), nGEN_ID);
	stNM.Format(_T("GEN%08d"), nGEN_ID);
	m_str_keyid = stCEQID;
	m_str_keyname = stNM;
	m_str_psrtype.Format(_T("DG"));
	//
	m_st_Kasim_GEN_Info.m_nGENID = nGEN_ID;
	m_st_Kasim_GEN_Info.m_nGEN_ND = nND_ID;
	m_st_Kasim_GEN_Info.m_nGEN_IJ = nIJ_ID;
	m_st_Kasim_GEN_Info.m_nGEN_PRDE = nPRDE_ID;
}

void CDND_Switch::SetEdit_InitData_KASIM_SVR(int nSVR_ID, int nFNDID, int nTNDID, int nBR_ID)
{
	CString stCEQID, stNM;
	stCEQID.Format(_T("999931%08d"), nSVR_ID);
	stNM.Format(_T("SVR%08d"), nSVR_ID);
	m_str_keyid = stCEQID;
	m_str_keyname = stNM;
	//
	m_st_Kasim_SVR_Info.m_nSVRID = nSVR_ID;
	m_st_Kasim_SVR_Info.m_nSVR_BRID = nBR_ID;
	m_st_Kasim_SVR_Info.m_nSVR_Fnd = nFNDID;
	m_st_Kasim_SVR_Info.m_nSVR_Tnd = nTNDID;
}

void CDND_Switch::SetEdit_InitData_KASIM_HVCUS(int nHVCUS_ID, int nND_ID, int nIJ_ID, int nPRDE_ID)
{
	CString stCEQID, stNM;
	stCEQID.Format(_T("999928%08d"), nHVCUS_ID);
	stNM.Format(_T("HVCUS%08d"), nHVCUS_ID);
	m_str_keyid = stCEQID;
	m_str_keyname = stNM;
	//
	m_st_Kasim_HVCUS_Info.m_nHVCUSID = nHVCUS_ID;
	m_st_Kasim_HVCUS_Info.m_nHVCUS_ND = nND_ID;
	m_st_Kasim_HVCUS_Info.m_nHVCUS_IJ = nIJ_ID;
	m_st_Kasim_HVCUS_Info.m_nHVCUS_PRDE = nPRDE_ID;
}

void CDND_Switch::SetEdit_InitData_KASIM_SUBS(int nSSID, int nGENID, int nMTRID, int nTRID, int nBRID, int nNDID, int nPRDEID, int nIJID )
{ 

	CString stCEQID, stNM;
	stCEQID.Format(_T("9999119%07d"), nSSID);
	stNM.Format(_T("SUBS%08d"), nSSID);
	m_str_keyid = stCEQID;
	m_str_keyname = stNM;

	m_st_Kasim_SUBS_Info.m_nSUBSID = nSSID;
	m_st_Kasim_SUBS_Info.m_nGENID = nGENID;
	m_st_Kasim_SUBS_Info.m_nNDID = nNDID;

	m_st_Kasim_SUBS_Info.m_nIJID = nIJID;
	m_st_Kasim_SUBS_Info.m_nPRDEID = nPRDEID;

}



///////////////////데이터 추가를여기서?
void CDND_Switch::Set_NEW_InitData_KASIM_CBSW(CString stKASIM_NM, CString stCEQID, CString stMUCEQID, int nCBSWID, int nFNDID, int nTNDID, int nMUSWINDEX, int nCBSWt_Type, int nPRDE)
{
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_NM"), nCBSWID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_CEQID"), nCBSWID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_TYPE"), nCBSWID, (int)nCBSWt_Type);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_RTUTYPE"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_COMTYPE"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_NORSTAT"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_RTUCODE"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_PRDE"), nCBSWID, (int)nPRDE);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_FND"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_FND"), nCBSWID, (int)nFNDID);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_TND"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_TND"), nCBSWID, (int)nTNDID);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_FGND"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_FGND"), nCBSWID, (int)nFNDID);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_TGND"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_TGND"), nCBSWID, (int)nTNDID);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_DL"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_DL"), nCBSWID, (int)0);
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_MULTISW_ID"), nCBSWID, (unsigned long long)_wtoll(stMUCEQID));
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_MULTICIR_NUMBER"), nCBSWID, (int)nMUSWINDEX);
	//CBSW_DYN_UIN
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_MEAUSE"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_MANF"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_MANSTAT"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_DNRIMPO"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_SRCDIRECTION"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_PFSIGN"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_DIRREF"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_BASE_STATE"), nCBSWID, (int)1);
	//CBSW_DYN_MEA
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_ODSTAT"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_NWSTAT"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAKV_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAKV_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAKV_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAAMP_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAAMP_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAAMP_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAADIFF_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAADIFF_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAADIFF_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_COMSTATSER"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_CONTSTAT"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_DIRSET"), nCBSWID, (int)0);
	//CBSW_DYN_NCPO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_NCPO"), _T("CBSW_DEAD"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_NCPO"), _T("CBSW_NCPISL"), nCBSWID, (int)0);
	//CBSW_DYN_RPFO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_3PRPFMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_3PRPFMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PFDIREC"), nCBSWID, (int)0);
	//CBSW_DYN_DLEO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_3PDLEMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_3PDLEMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PADLEMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PADLEMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PBDLEMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PBDLEMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PCDLEMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PCDLEMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_DIRINVFLAG"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_SRCDIRECTION"), nCBSWID, (int)0);
	//CBSW_DYN_STDLEO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_STDLEO"), _T("CBSW_DERGENMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_STDLEO"), _T("CBSW_DERRAMW"), nCBSWID, (double)0);	
}

void CDND_Switch::Set_NEW_InitData_KASIM_CBSW_DL(CString stKASIM_NM, CString stCEQID, CString stMUCEQID, int nCBSWID, int nFNDID, int nTNDID, int nMUSWINDEX, int nCBSWt_Type, int nPRDE, CString stKASIM_DL, int nDLID)
{
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_NM"), nCBSWID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_CEQID"), nCBSWID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_TYPE"), nCBSWID, (int)nCBSWt_Type);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_RTUTYPE"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_COMTYPE"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_NORSTAT"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_RTUCODE"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_PRDE"), nCBSWID, (int)nPRDE);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_FND"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_FND"), nCBSWID, (int)nFNDID);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_TND"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_TND"), nCBSWID, (int)nTNDID);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_FGND"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_FGND"), nCBSWID, (int)nFNDID);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_TGND"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_TGND"), nCBSWID, (int)nTNDID);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_DL"), nCBSWID, (int)nDLID);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_DL"), nCBSWID, (int)0);
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_MULTISW_ID"), nCBSWID, (unsigned long long)_wtoll(stMUCEQID));
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_MULTICIR_NUMBER"), nCBSWID, (int)nMUSWINDEX);
	//CBSW_DYN_UIN
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_MEAUSE"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_MANF"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_MANSTAT"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_DNRIMPO"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_SRCDIRECTION"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_PFSIGN"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_DIRREF"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_BASE_STATE"), nCBSWID, (int)1);
	//CBSW_DYN_MEA
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_ODSTAT"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_NWSTAT"), nCBSWID, (int)1);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAKV_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAKV_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAKV_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAAMP_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAAMP_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAAMP_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAADIFF_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAADIFF_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAADIFF_OLD"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_COMSTATSER"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_CONTSTAT"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_DIRSET"), nCBSWID, (int)0);
	//CBSW_DYN_NCPO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_NCPO"), _T("CBSW_DEAD"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_NCPO"), _T("CBSW_NCPISL"), nCBSWID, (int)0);
	//CBSW_DYN_RPFO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFKV"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFAMP"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFADIFF"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_3PRPFMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_3PRPFMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PFDIREC"), nCBSWID, (int)0);
	//CBSW_DYN_DLEO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_3PDLEMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_3PDLEMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PADLEMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PADLEMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PBDLEMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PBDLEMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PCDLEMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PCDLEMVAR"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_DIRINVFLAG"), nCBSWID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_SRCDIRECTION"), nCBSWID, (int)0);
	//CBSW_DYN_STDLEO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_STDLEO"), _T("CBSW_DERGENMW"), nCBSWID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_STDLEO"), _T("CBSW_DERRAMW"), nCBSWID, (double)0);

	PUTVALUE(_T("DL_STA"), _T("DL_NM"), nDLID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("DL_STA"), _T("DL_DistributionLineID"), nDLID, (unsigned long long)_wtoll(stKASIM_DL));
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_II_OLM"), nDLID, (int)1);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_II_MTR"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_SI_MTR"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_II_BOF"), nDLID, (int)1);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_SI_BOF"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_HI_IJ"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_HI_CBSW"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_HI_BR"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_II_CB"), nDLID, (int)nCBSWID);
	//
	PUTDOUBLE2VALUE(_T("DL_DYN_UIN"), _T("DL_PROTECSEQ"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_DYN_UIN"), _T("DL_CVRFACTOR"), nDLID, (double)0.1);
	PUTDOUBLE2VALUE(_T("DL_DYN_UIN"), _T("DL_PEAKLIM"), nDLID, (double)10);
	PUTDOUBLE2VALUE(_T("DL_DYN_UIN"), _T("DL_OPRCAPACITY"), nDLID, (double)1);
	PUTDOUBLE2VALUE(_T("DL_DYN_UIN"), _T("DL_SCA_ALLFLAG"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_DYN_UIN"), _T("DL_SOP_FLAG"), nDLID, (int)0);
	//
	PUTDOUBLE2VALUE(_T("DL_DYN_NCPO"), _T("DL_HI_BS"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_DYN_NCPO"), _T("DL_HI_ND"), nDLID, (int)0);
	//
	PUTDOUBLE2VALUE(_T("DL_DYN_RPFO"), _T("DL_3PGENRPFMW"), nDLID, (double)0);
	//
	PUTDOUBLE2VALUE(_T("DL_DYN_VVOO"), _T("DL_3PGENVVOMW"), nDLID, (double)0);
	//
	PUTDOUBLE2VALUE(_T("DL_DYN_DNRO"), _T("DL_SOL1RESLT_LOAD_MW"), nDLID, (double)0);
	//
	PUTDOUBLE2VALUE(_T("DL_DYN_STDLEO"), _T("DL_GEN_RA_SUM"), nDLID, (double)0);

}


void CDND_Switch::Set_NEW_InitData_KASIM_ND(CString stKASIM_NM, CString stCEQID, int nID, int nFNDID, int nTNDID, int nIJDID, int nSNVID, int nType)
{
	CString stFndFK, stTndFK;
	int nNDID = 0;

	//
	if (nType == 1) //CBSW
	{
		if (!(nFNDID == 0 || nFNDID == 999999))
		{
			//FND	
			stFndFK.Format(_T("%s01"), stCEQID);
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nFNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nFNDID, (unsigned long long)_wtoll(stCEQID));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nFNDID, (unsigned long long)_wtoll(stFndFK));
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_SNV"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_SNV"), nFNDID, (int)nSNVID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nFNDID, (int)nID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nFNDID, (int)nFNDID);
			//ND_DYN_UIN
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nFNDID, (int)1);
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nFNDID, (int)1);
			//FGND
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nFNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nFNDID, (int)nFNDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nFNDID, (int)nID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nFNDID, (int)0);

			Set_NEW_InitData_KASIM_GND(nFNDID);

		}
		if (!(nTNDID == 0 || nTNDID == 999999))
		{
			//TND	
			stTndFK.Format(_T("%s02"), stCEQID);
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nTNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nTNDID, (unsigned long long)_wtoll(stCEQID));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nTNDID, (unsigned long long)_wtoll(stTndFK));
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_SNV"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_SNV"), nTNDID, (int)nSNVID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nTNDID, (int)nID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nTNDID, (int)nTNDID);
			//ND_DYN_UIN
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nTNDID, (int)1);
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nTNDID, (int)1);
			//TGND
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nTNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nTNDID, (int)nTNDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nTNDID, (int)nID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nTNDID, (int)0);

			Set_NEW_InitData_KASIM_GND(nTNDID);

		}
	}
	else if (nType == 2) //LNSEC
	{
		
	}
	else if (nType == 3) //GEN
	{
		if (!(nFNDID == 0 || nFNDID == 999999)) { nNDID = nFNDID;	}
		if (!(nTNDID == 0 || nTNDID == 999999)) { nNDID = nFNDID;	}

		if (nNDID != 0)
		{
			//FND	
			stFndFK.Format(_T("%s01"), stCEQID);
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nNDID, (unsigned long long)_wtoll(stCEQID));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nNDID, (unsigned long long)_wtoll(stFndFK));
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_SNV"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_SNV"), nNDID, (int)nSNVID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nNDID, (int)nID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nNDID, (int)nNDID);
			//ND_DYN_UIN
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nNDID, (int)1);
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nNDID, (int)1);
			//FGND
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nNDID, (int)nNDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nNDID, (int)nID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nNDID, (int)nIJDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nNDID, (int)0);

			Set_NEW_InitData_KASIM_GND(nNDID);
		}
	}
	else if (nType == 4) //HVCUS
	{
		if (!(nFNDID == 0 || nFNDID == 999999)) { nNDID = nFNDID; }
		if (!(nTNDID == 0 || nTNDID == 999999)) { nNDID = nFNDID; }

		if (nNDID != 0)
		{
			//FND	
			stFndFK.Format(_T("%s01"), stCEQID);
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nNDID, (unsigned long long)_wtoll(stCEQID));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nNDID, (unsigned long long)_wtoll(stFndFK));
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_SNV"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_SNV"), nNDID, (int)nSNVID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nNDID, (int)nNDID);
			//ND_DYN_UIN
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nNDID, (int)1);
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nNDID, (int)1);
			//ND_DYN_NCPO
			PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_DL"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_DL"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_MTR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_MTR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_SS"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_SS"), nNDID, (int)0);
			//FGND
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nNDID, (int)nNDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nNDID, (int)nIJDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nNDID, (int)nID);

			Set_NEW_InitData_KASIM_GND(nNDID);
		}
	}
	else if (nType == 5) //junction
	{
		if (!(nFNDID == 0 || nFNDID == 999999)) { nNDID = nFNDID; }
		if (!(nTNDID == 0 || nTNDID == 999999)) { nNDID = nFNDID; }

		if (nNDID != 0)
		{
			//FND	
			stFndFK.Format(_T("%s01"), stCEQID);
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nNDID, (unsigned long long)_wtoll(stCEQID));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nNDID, (unsigned long long)_wtoll(stFndFK));
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_SNV"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_SNV"), nNDID, (int)nSNVID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nNDID, (int)nNDID);
			//ND_DYN_UIN
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nNDID, (int)1);
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nNDID, (int)1);
			//FGND
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nNDID, (int)nNDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nNDID, (int)0);

			Set_NEW_InitData_KASIM_GND(nNDID);
		}
	}
	else if (nType == 6) //svr
	{
		if (!(nFNDID == 0 || nFNDID == 999999))
		{
			//FND	
			stFndFK.Format(_T("%s01"), stCEQID);
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nFNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nFNDID, (unsigned long long)_wtoll(stCEQID));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nFNDID, (unsigned long long)_wtoll(stFndFK));
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_SNV"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_SNV"), nFNDID, (int)nSNVID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nFNDID, (int)nIJDID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nFNDID, (int)nFNDID);
			//ND_DYN_UIN
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nFNDID, (int)1);
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nFNDID, (int)1);
			//FGND
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nFNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nFNDID, (int)nFNDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nFNDID, (int)nIJDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nFNDID, (int)0);

			Set_NEW_InitData_KASIM_GND(nFNDID);

		}
		if (!(nTNDID == 0 || nTNDID == 999999))
		{
			//TND	
			stTndFK.Format(_T("%s02"), stCEQID);
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nTNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nTNDID, (unsigned long long)_wtoll(stCEQID));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nTNDID, (unsigned long long)_wtoll(stTndFK));
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_SNV"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_SNV"), nTNDID, (int)nSNVID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nTNDID, (int)nIJDID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nTNDID, (int)nTNDID);
			//ND_DYN_UIN
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nTNDID, (int)1);
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nTNDID, (int)1);
			//TGND
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nTNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nTNDID, (int)nTNDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nTNDID, (int)nIJDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nTNDID, (int)0);
			Set_NEW_InitData_KASIM_GND(nTNDID);
		}
	}
	else if (nType == 7) //MUCBSW
	{
		if (!(nFNDID == 0 || nFNDID == 999999))
		{
			//FND	
			stFndFK.Format(_T("%s01"), stCEQID);
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nFNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nFNDID, (unsigned long long)_wtoll(stCEQID));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nFNDID, (unsigned long long)_wtoll(stFndFK));
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_SNV"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_SNV"), nFNDID, (int)nSNVID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nFNDID, (int)nID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nFNDID, (int)nFNDID);
			//ND_DYN_UIN
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nFNDID, (int)1);
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nFNDID, (int)1);
			//FGND
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nFNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nFNDID, (int)nFNDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nFNDID, (int)nID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nFNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nFNDID, (int)0);

			Set_NEW_InitData_KASIM_GND(nFNDID);
		}
	}
	else if (nType == 8) //MUCBSW
	{
		if (!(nTNDID == 0 || nTNDID == 999999))
		{
			//TND	
			stTndFK.Format(_T("%s02"), stCEQID);
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nTNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nTNDID, (unsigned long long)_wtoll(stCEQID));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nTNDID, (unsigned long long)_wtoll(stTndFK));
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_SNV"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_SNV"), nTNDID, (int)nSNVID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nTNDID, (int)nID);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nTNDID, (int)nTNDID);
			//ND_DYN_UIN
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nTNDID, (int)1);
			PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nTNDID, (int)1);
			//TGND
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nTNDID, (wchar_t*)stKASIM_NM.GetBuffer());
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nTNDID, (int)nTNDID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nTNDID, (int)nID);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nTNDID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nTNDID, (int)0);

			Set_NEW_InitData_KASIM_GND(nTNDID);
		}
	}
	else
	{

	}	
}

void CDND_Switch::Set_NEW_InitData_KASIM_GND(int nID)
{
	//ND_DYN_NCPO
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_DL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_DL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_MTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_MTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_SS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_SS"), nID, (int)0);
	//GND_DYN_NCPO
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_SI_ISL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_II_ISL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_DEAD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_SI_BS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_II_BS"), nID, (int)0);
	//GND_DYN_RPFO
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIONW"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIORECV"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIOLMHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIOLMLO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIOFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PHSFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PAVIOKVHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PAVIOPERHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PAVIOKVLO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PAVIOPERLO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOKVHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOPERHI"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOKVLO"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOPERLO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOKVHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOPERHI"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOKVLO"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOPERLO"), nID, (double)0);
	//GND_DYN_SCAO
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FC_3LL"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FC_2LL"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FC_1LG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FC_1LG_30ohm"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FLT_PA_V"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FLT_PB_V"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FLT_PC_V"), nID, (double)0);

}

void CDND_Switch::Set_NEW_InitData_KASIM_GEN_STA(CString stKASIM_NM, CString stCEQID, int nID, int nNDID, int nIJID, int nPRDEID, int nGenType , double dGEN_MWLMMX, int nGEN_TREXCL , int nGENUNITID )
{
	CString stNULL;
	stNULL.Format(_T(""));
	//GEN_STA
	PUTVALUE(_T("GEN_STA"), _T("GEN_NM"), nID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GEN_STA"), _T("GEN_CEQID"), nID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_SI_ND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_ND"), nID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_SI_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_GND"), nID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_IJ"), nID, (int)nIJID);
	if (nGenType == 1 ) //무한모선이면
	{
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_NAMKV"), nID, (double)154);
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMX"), nID, (double)0.01);
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TYPE"), nID, (int)nGenType);
	}
	else
	{
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_NAMKV"), nID, (double)22.9);
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMX"), nID, (double)dGEN_MWLMMX/1000);
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TYPE"), nID, (int)nGenType);
	}

	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MVARLMMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MVARLMMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_R"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_STX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_SSX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_VOL_CLS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_CONND"), nID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_CONNDREP"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_CONTYPE"), nID, (int)7);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_NOOFP"), nID, (int)4);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_PF"), nID, (double)0.95);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_EFF"), nID, (double)0.85);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_PFMINLAG"), nID, (double)-0.95);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_PFMINLEAD"), nID, (double)0.95);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_HI_ESS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MEA"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TREXCL"), nID, (int)nGEN_TREXCL);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_PRDE"), nID, (int)nPRDEID); //2222222222
	
	/////
	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_NM"), nGENUNITID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_II_GEN"), nGENUNITID, (int)nID);
	PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_SI_GEN"), nGENUNITID, (int)0);
	PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_CAP_KW"), nGENUNITID, (double)dGEN_MWLMMX);
	PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_TYPE"), nGENUNITID, (int)nGenType);

	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NO"), nGENUNITID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NM"), nGENUNITID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), nGENUNITID, (wchar_t*)stNULL.GetBuffer());
}

void CDND_Switch::Set_NEW_InitData_KASIM_GEN_DYN_MEA(int nID)
{
	//GEN_DYN_MEA
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_ONOFF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_OLDESSSOC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_ESSSOC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PAMEAVOLT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PBMEAVOLT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PCMEAVOLT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PAMEACUR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PBMEACUR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PCMEACUR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PAMEAANG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PBMEAANG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PCMEAANG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PAMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PAMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PBMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PBMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PCMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PCMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_MEAMWDIR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_MEAMVARDIR"), nID, (int)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_GEN_DYN_UIN(int nID , double dGEN_ITR_CAP, int nGEN_ITR_WDC, double dGEN_ITR_X, int nGEN_MACH_TYPE)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//GEN_DYN_UIN
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_AVR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_TBSVL"), nID, (double)1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DEV"), nID, (double)0.02);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PF"), nID, (double)0.95);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_VVOFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MVARCONMODE"), nID, (int)4);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_OUTQ"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PFVVOMINLAG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PFVVOMINLEAD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVMINS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMVUBREF"), nID, (double)1.02);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMVLBREF"), nID, (double)0.96);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMQVRATIO"), nID, (double)1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEQMAX"), nID, (double)48);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEQMIN"), nID, (double)-48);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV1"), nID, (double)0.96);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV2"), nID, (double)0.97);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV3"), nID, (double)1.01);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV4"), nID, (double)1.02);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_CAP"), nID, (double)dGEN_ITR_CAP);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_R"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_X"), nID, (double)dGEN_ITR_X);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_NGR_R"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_NGR_X"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_WDC"), nID, (int)nGEN_ITR_WDC);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MACH_TYPE"), nID, (int)nGEN_MACH_TYPE);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_SCA_EXCEPTION"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PDVRFLAG"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM1"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM2"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM3"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM4"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM5"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM6"), nID, (double)0);
	PUTVALUE(_T("GEN_DYN_UIN"), _T("GEN_MDL_TIME"), nID, (wchar_t*)stNULL.GetBuffer());
}

void CDND_Switch::Set_NEW_InitData_KASIM_GEN_DYN_VVOO(int nID)
{	
	//GEN_DYN_VVOO
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VREFOLD"), nID, (double)1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_PFREFOLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_QREFOLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_SI_DPDL"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_BASEKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVOVREF"), nID, (double)1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVOPFREF"), nID, (double)0.95);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVOQREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVORCOMFLAG"), nID, (int)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_GEN_DYN_PDVRO(int nID)
{
	
	//GEN_DYN_PDVRO
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_DERAVMPFREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_DERAVMVREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_DERAVMVUBREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_DERAVMVLBREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_DERAVMQVRATIO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_QVCURVEV1"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_QVCURVEV2"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_QVCURVEV3"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_QVCURVEV4"), nID, (double)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_SVR(CString stKASIM_NM, CString stCEQID, int nID, int nFNDID, int nTNDID, int nBRID)
{
	//TR_STA
	PUTVALUE(_T("TR_STA"), _T("TR_NM"), nID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("TR_STA"), _T("TR_CEQID"), nID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TYPE"), nID, (int)3);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_BR"), nID, (int)nBRID);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_FNORKV"), nID, (double)22.9);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TNORKV"), nID, (double)22.9);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TRMVA"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_CONTY"), nID, (int)2);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ONLTC"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_POSX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ZERX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMX"), nID, (int)32);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMN"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPNOR"), nID, (int)15);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPSTEP"), nID, (double)0.625);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMX"), nID, (int)32);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMN"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nID, (int)15);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nID, (double)0.625);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMX"), nID, (int)32);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMN"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPNOR"), nID, (int)15);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPSTEP"), nID, (double)0.625);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_CONND"), nID, (int)nFNDID);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PGR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PGX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SGR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SGX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_SS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SI_SS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_MTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SI_MTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_LOCTAP"), nID, (int)0);
	//TR_DYN_UIN
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_AVR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PATBSVL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PADEV"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PBTBSVL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PBDEV"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PCTBSVL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PCDEV"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VVOFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CON3P"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_II_PFVM"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PACOMPR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PACOMPX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PBCOMPR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PBCOMPX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PCCOMPR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PCCOMPX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_3CONMEAP"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PATAPCOST"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PACONTAPMX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PBTAPCOST"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PBCONTAPMX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PCTAPCOST"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PCCONTAPMX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PACONTAPMXDAY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PATAPOPDAY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PBCONTAPMXDAY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PBTAPOPDAY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PCCONTAPMXDAY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PCTAPOPDAY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMX"), nID, (int)140);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMN"), nID, (int)85);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFSS"), nID, (int)0.5);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMX"), nID, (int)9);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMN"), nID, (int)0.5);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWSS"), nID, (int)0.1);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMX"), nID, (int)25);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMN"), nID, (int)-25);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXSS"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PDVRFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVH"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCH"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_LDCTYPE"), nID, (int)3);
	//TR_DYN_MEA
	PUTDOUBLE2VALUE(_T("TR_DYN_MEA"), _T("TR_PAMEATAP"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_MEA"), _T("TR_PBMEATAP"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_MEA"), _T("TR_PCMEATAP"), nID, (int)0);
	//TR_DYN_NCPO
	PUTDOUBLE2VALUE(_T("TR_DYN_NCPO"), _T("TR_DEAD"), nID, (int)0);
	//TR_DYN_VVOO
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PAVREFOLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PBVREFOLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PCVREFOLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PATAPREFOLD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PBTAPREFOLD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PCTAPREFOLD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_BASEKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_SI_DPDL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PAVVOVREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PBVVOVREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PCVVOVREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PAVVOTAPREF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PBVVOTAPREF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PCVVOTAPREF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_VVORCOMFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PAPF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PBPF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PCPF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_SI_ISL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PARPFPF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PBRPFPF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PCRPFPF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PFMIN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PFAVNW"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PFAVRECV"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_VIOPF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_VIOPER"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_RECVFLAG"), nID, (int)0);
	//TR_DYN_PDVRO
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PAVREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PBVREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PCVREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PAVBW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PBVBW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PCVBW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PBR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PCR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PAX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PBX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PCX"), nID, (double)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_HVCUS(CString stKASIM_NM, CString stCEQID, int nID, int nNDID, int nIJID, int nPRDEID)
{
	//HVCUS_STA
	PUTVALUE(_T("HVCUS_STA"), _T("HVCUS_NM"), nID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("HVCUS_STA"), _T("HVCUS_CEQID"), nID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_II_GND"), nID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_SI_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_CON_KVA"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_ITR_KVA"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_ITR_PZ"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_II_PRDE"), nID, (int)nPRDEID);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_ITR_WDC"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_II_IJ"), nID, (int)nIJID);
}

void CDND_Switch::Set_NEW_InitData_KASIM_PRDE(CString stKASIM_NM, int nID)
{
	//PRDE_STA
	PUTVALUE(_T("PRDE_STA"), _T("PRDE_NM"), nID, (wchar_t*)stKASIM_NM.GetBuffer());
	//PRDE_DYN_UIN
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_Pickup_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_IIC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_Pickup_C"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_IIC"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_TYPE"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_SET_GTYPE"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_NOF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_NOD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_NOF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_NOD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_TAS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_TAS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_TAS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_TAS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_CTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_CTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_MX_LD_C_PHA"), nID, (double)0);
	//PRDE_DYN_PCEO
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCRF_TM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCRD_TM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGRF_TM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGRD_TM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_F_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_F_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_D_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_D_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_IIC_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_RECMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_RECMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_IIC_RECMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_TMS_RECMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_MX_FLT_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_MN_FLT_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_F_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_F_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_D_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_D_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_IIC_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_RECMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_RECMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_IIC_RECMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_TMS_RECMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_MX_FLT_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_MN_FLT_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCRF_TM_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCRD_TM_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGRF_TM_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGRD_TM_REC"), nID, (double)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_LD(CString stKASIM_NM, int nID, int nNDID, int nIJID)
{
	//LD_STA
	PUTVALUE(_T("LD_STA"), _T("LD_NM"), nID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_SI_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_GND"), nID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_IJ"), nID, (int)nIJID);
	//LD_DYN_UIN
	PUTDOUBLE2VALUE(_T("LD_DYN_UIN"), _T("LD_DIV"), nID, (double)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_IJ(CString stKASIM_NM, int nID, int nNDID, int nIJ_II_EQUTY)
{
	int nIJ_WhileID = 0, nIJEQU = 0, nIJEQUTY = 0;
	nIJ_WhileID = nID; //특별하게 저장
	while (nIJEQU == 0)
	{
		if (nID == 999999)
		{
			break;
		}
		if (nIJ_WhileID == 1)
		{
			nIJEQUTY = 1;
			break;
		}
		nIJEQUTY = GETVALUE(int, _T("IJ_STA"), _T("IJ_II_EQUTY"), nIJ_WhileID - 1);
		if (nIJEQUTY == nIJ_II_EQUTY) //4-gen,6-선로,8수용가입니다.
		{
			nIJEQU = GETVALUE(int, _T("IJ_STA"), _T("IJ_II_EQU"), nIJ_WhileID - 1);
			nIJEQU = nIJEQU + 1;
			break;
		}
		else
		{
			nIJ_WhileID = nIJ_WhileID - 1;
		}
	}

	//IJ_STA
	PUTVALUE(_T("IJ_STA"), _T("IJ_NM"), nID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_EQUTY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_EQUTY"), nID, (int)nIJ_II_EQUTY);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_EQU"), nID, (int)nIJEQU);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_GND"), nID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_DL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_DL"), nID, (int)0);
	//IJ_DYN_UIN
	PUTDOUBLE2VALUE(_T("IJ_DYN_UIN"), _T("IJ_SOCMAXORDER"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_UIN"), _T("IJ_SOCMINORDER"), nID, (int)0);
	//IJ_DYN_NCPO
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_SI_BS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_II_BS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_DEAD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_BSSTAT"), nID, (int)0);
	//IJ_DYN_MEA
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_3PMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_3PMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PAMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PAMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PBMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PBMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PCMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PCMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_MEAFLAG"), nID, (int)0);
	//IJ_DYN_RPFO
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PARPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PARPFMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PBRPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PBRPFMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PCRPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PCRPFMVAR"), nID, (double)0);
	//IJ_DYN_VVOO
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PAVVOMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PAVVOMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PBVVOMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PBVVOMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PCVVOMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PCVVOMVAR"), nID, (double)0);
	//IJ_DYN_DLEO
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PAGENESTMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PBGENESTMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PCGENESTMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PAGENESTMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PBGENESTMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PCGENESTMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_3PGENESTMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_3PGENESTMVAR"), nID, (double)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_ESS(int nID)
{

}

void CDND_Switch::Set_NEW_InitData_KASIM_SVR_BR(CString stKASIM_NM,  int nBRID, int nFnd, int nTnd )
{
	int nBR_II_EQU = 0, nBR_WhileID = nBRID;
	//
	int nGBR_II_EQUTY = 0;
	while (nBR_II_EQU == 0)
	{
		if (nBRID == 999999)
		{
			break;
		}
		if (nBR_WhileID == 1)
		{
			nBR_II_EQU = 1;
			break;
		}
		nGBR_II_EQUTY = GETVALUE(int, _T("gbr_sta"), _T("GBR_II_EQUTY"), nBR_WhileID - 1);
		if (nGBR_II_EQUTY == 2)
		{
			nBR_II_EQU = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equ"), nBR_WhileID - 1);
			nBR_II_EQU = nBR_II_EQU + 1;
			break;
		}
		else
		{
			nBR_WhileID = nBR_WhileID - 1;
		}
	}
	//BR
	PUTVALUE(_T("BR_STA"), _T("BR_NM"), nBRID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_EQU"), nBRID, (int)nBR_II_EQU);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_FND"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_FND"), nBRID, (int)nFnd);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_TND"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_TND"), nBRID, (int)nTnd);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSR"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSX"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSG"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSB"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERR"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERX"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERG"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERB"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_NORLM"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_EMRLM"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_GBR"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_GBR"), nBRID, (int)nBRID);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_DL"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_DL"), nBRID, (int)0);
	//GBR
	PUTVALUE(_T("GBR_STA"), _T("GBR_NM"), nBRID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_EQU"), nBRID, (int)nBR_II_EQU);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_SI_FGND"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_FGND"), nBRID, (int)nFnd);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_SI_TGND"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_TGND"), nBRID, (int)nTnd);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSR"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSX"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSG"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSB"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERR"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERX"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERG"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERB"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_HI_BR"), nBRID, (int)nBRID);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_SI_EQUTY"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_EQUTY"), nBRID, (int)2); //lnsec은 
	//GBR_DYN_UIN
	PUTDOUBLE2VALUE(_T("GBR_DYN_UIN"), _T("GBR_MORFLAG"), nBRID, (int)1);
	PUTDOUBLE2VALUE(_T("GBR_DYN_UIN"), _T("GBR_SCAFLAG"), nBRID, (int)1);
	//GBR_DYN_SCAO
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PA_C"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PB_C"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PC_C"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PN_C"), nBRID, (double)0);
	//GBR_DYN_NCPO
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_SI_FBS"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_SI_TBS"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_II_FBS"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_II_TBS"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_FBSSTAT"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_TBSSTAT"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_DEAD"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_II_OUTCMP"), nBRID, (int)0);
	//GBR_DYN_RPFO
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMVAR21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMVAR21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMVAR21"), nBRID, (double)0);
	//GBR_DYN_VVOO
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMVAR21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMVAR21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMVAR21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_MVA"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFPS"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFMVA"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFMW"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFMVAR"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOPS"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOMVA"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOMW"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOMVAR"), nBRID, (double)0);
	//GBR_DYN_AV
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIONW"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIORECV"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIOLM"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIOMVA"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIOPER"), nBRID, (double)0);
	//GBR_DYN_VVOAV
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOAV"), _T("GBR_VVORECFLAG"), nBRID, (int)0);
}

// void CDND_Switch::GetDelete_BR_Array(int nID)
// {
// 	for ( int i = 0 ; i < m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.GetSize(); i++)
// 	{
// 		delete m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.GetAt(i);
// 		i--;
// 	}
// }


//변전소 부부
void CDND_Switch::Set_NEW_InitData_KASIM_SS_STA(CString stKASIM_NM, CString stCEQID, int nSSID, int nGENID, int nIJID, int nNDID, int nPRDEID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//SS_STA
	PUTVALUE(_T("SS_STA"), _T("SS_NM"), nSSID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("SS_STA"), _T("SS_SUBSTATIONID"), nSSID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("SS_STA"), _T("SS_HI_MTR"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_STA"), _T("SS_HI_SNV"), nSSID, (int)0);
	PUTVALUE(_T("SS_STA"), _T("SS_CODE"), nSSID, (wchar_t*)stNULL.GetBuffer());
	PUTDOUBLE2VALUE(_T("SS_STA"), _T("SS_II_VGEN"), nSSID, (int)nGENID);
}

void CDND_Switch::Set_NEW_InitData_KASIM_SS_DYN_UIN(int nSSID)
{
	PUTDOUBLE2VALUE(_T("SS_DYN_UIN"), _T("SS_DNRFLAG"), nSSID, (int)1);
	PUTDOUBLE2VALUE(_T("SS_DYN_UIN"), _T("SS_TIEOUTKW"), nSSID, (double)10);
	PUTDOUBLE2VALUE(_T("SS_DYN_UIN"), _T("SS_TIEINKW"), nSSID, (double)10);
}

void CDND_Switch::Set_NEW_InitData_KASIM_SS_DYN_NCPO(int nSSID)
{
	PUTDOUBLE2VALUE(_T("SS_DYN_NCPO"), _T("SS_STATCHG"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_NCPO"), _T("SS_HI_BS"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_NCPO"), _T("SS_HI_ND"), nSSID, (int)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_SS_DYN_RPFO(int nSSID)
{
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_3PGENRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_3PGENRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_3PLDRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_3PLDRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_3PLSRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_3PLSRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_3PCAPRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PAGENRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PAGENRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PALDRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PALDRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PALSRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PALSRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PBGENRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PBGENRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PBLDRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PBLDRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PBLSRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PBLSRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PCGENRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PCGENRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PCLDRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PCLDRPFMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PCLSRPFMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_RPFO"), _T("SS_PCLSRPFMVAR"), nSSID, (double)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_SS_DYN_VVOO(int nSSID)
{
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_3PGENVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_3PGENVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_3PLDVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_3PLDVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_3PLSVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_3PLSVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_3PCAPVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PAGENVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PAGENVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PALDVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PALDVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PALSVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PALSVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PBGENVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PBGENVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PBLDVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PBLDVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PBLSVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PBLSVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PCGENVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PCGENVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PCLDVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PCLDVVOMVAR"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PCLSVVOMW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_VVOO"), _T("SS_PCLSVVOMVAR"), nSSID, (double)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_SS_DYN_DNRO(int nSSID)
{
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_INISOLRESLT_LOSS"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_INIRESLT_BALANCE"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_INISOLRESLT_COMBI"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_INIRESLT_MAX_VOLTVIO"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_INIRESLT_COUNT_VOLTVIO"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_INIRESLT_MAX_MWVIO"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_INIRESLT_COUNT_MWVIO"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL1RESLT_LOSS"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL1RESLT_BALANCE"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL1RESLT_COMBI"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL1RESLT_MAX_VOLTVIO"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL1RESLT_COUNT_VOLTVIO"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL1RESLT_MAX_MWVIO"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL1RESLT_COUNT_MWVIO"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL2RESLT_LOSS"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL2RESLT_BALANCE"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL2RESLT_COMBI"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL2RESLT_MAX_VOLTVIO"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL2RESLT_COUNT_VOLTVIO"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL2RESLT_MAX_MWVIO"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL2RESLT_COUNT_MWVIO"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL3RESLT_LOSS"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL3RESLT_BALANCE"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL3RESLT_COMBI"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL3RESLT_MAX_VOLTVIO"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL3RESLT_COUNT_VOLTVIO"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL3RESLT_MAX_MWVIO"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_DNRO"), _T("SS_SOL3RESLT_COUNT_MWVIO"), nSSID, (int)0);
}

void CDND_Switch::Set_NEW_InitData_KASIM_MTR(CString stKASIM_NM, CString stCEQID, int nMTRID, int nTRID, int nBRID, int nNDID, int nSSID, int nSSFNDID)
{
	CString stNULL;
	stNULL.Format(_T(""));

	//MTR_STA
	PUTVALUE(_T("MTR_STA"), _T("MTR_NM"), nMTRID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("MTR_STA"), _T("MTR_MAINTRID"), nMTRID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_II_SS"), nMTRID, (int)nSSID);
	PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_BANK"), nMTRID, (int)1);
	PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_HI_TR"), nMTRID, (int)nTRID);
	//
	PUTDOUBLE2VALUE(_T("MTR_DYN_UIN"), _T("MTR_SOP_FLAG"), nMTRID, (int)0);
	PUTDOUBLE2VALUE(_T("MTR_DYN_NCPO"), _T("MTR_HI_ND"), nMTRID, (int)0);
	PUTDOUBLE2VALUE(_T("MTR_DYN_RPFO"), _T("MTR_3PGENRPFMW"), nMTRID, (int)0);
	PUTDOUBLE2VALUE(_T("MTR_DYN_VVOO"), _T("MTR_3PGENVVOMW"), nMTRID, (int)0);
	   
	//TR_STA
	PUTVALUE(_T("TR_STA"), _T("TR_NM"), nTRID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("TR_STA"), _T("TR_CEQID"), nTRID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TYPE"), nTRID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_BR"), nTRID, (int)nBRID);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_FNORKV"), nTRID, (double)154);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TNORKV"), nTRID, (double)22.9);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TRMVA"), nTRID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_CONTY"), nTRID, (int)2);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ONLTC"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_POSX"), nTRID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ZERX"), nTRID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMX"), nTRID, (int)21);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMN"), nTRID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPNOR"), nTRID, (int)11);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPSTEP"), nTRID, (double)-0.0125);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMX"), nTRID, (int)21);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMN"), nTRID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nTRID, (int)11);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nTRID, (double)-0.0125);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMX"), nTRID, (int)21);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMN"), nTRID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPNOR"), nTRID, (int)11);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPSTEP"), nTRID, (double)-0.0125);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_CONND"), nTRID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PGR"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PGX"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SGR"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SGX"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_SS"), nTRID , (int)nSSID);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SI_SS"), nTRID , (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_MTR"), nTRID, (int)nMTRID);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_SI_MTR"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_LOCTAP"), nTRID, (int)0);

	//TR_DYN_UIN
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CON3P"), nTRID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_II_PFVM"), nTRID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_3CONMEAP"), nTRID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMX"), nTRID, (int)140);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMN"), nTRID, (int)85);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFSS"), nTRID, (int)0.5);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMX"), nTRID, (int)9);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMN"), nTRID, (int)0.5);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWSS"), nTRID, (int)0.1);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMX"), nTRID, (int)25);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMN"), nTRID, (int)-25);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXSS"), nTRID, (int)1);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PDVRFLAG"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVH"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVL"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCH"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCL"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_LDCTYPE"), nTRID, (int)3);
	//
	PUTDOUBLE2VALUE(_T("TR_DYN_MEA"), _T("TR_PAMEATAP"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_NCPO"), _T("TR_DEAD"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_VVOO"), _T("TR_PAVREFOLD"), nTRID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_PDVRO"), _T("TR_PAVREF"), nTRID, (int)0);


	//ND
	PUTVALUE(_T("ND_STA"), _T("ND_NM"), nNDID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nNDID, (unsigned long long)_wtoll(stCEQID));
	CString szND_ConnectivityNodeID;
	szND_ConnectivityNodeID.Format(_T("%s01"), stCEQID);
	PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nNDID, (unsigned long long)_wtoll(szND_ConnectivityNodeID));
	PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nNDID, (int)nNDID);
	//
	PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nNDID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_DL"), nNDID, (int)0);
	//GND입력부분
	PUTVALUE(_T("GND_STA"), _T("GND_NM"), nNDID, (wchar_t*)stKASIM_NM.GetBuffer());
	//
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_SI_ISL "), nNDID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIONW"), nNDID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FC_3LL"), nNDID, (int)0);
	//BR
	//
	int nBR_II_EQU = 0, nBR_WhileID = nBRID, nGBR_II_EQUTY = 0;
	while (nBR_II_EQU == 0)
	{
		if (nBRID == 999999)
		{
			break;
		}
		if (nBR_WhileID == 1)
		{
			nBR_II_EQU = 1;
			break;
		}
		nGBR_II_EQUTY = GETVALUE(int, _T("gbr_sta"), _T("GBR_II_EQUTY"), nBR_WhileID - 1);
		if (nGBR_II_EQUTY == 2)
		{
			nBR_II_EQU = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equ"), nBR_WhileID - 1);
			nBR_II_EQU = nBR_II_EQU + 1;
			break;
		}
		else
		{
			nBR_WhileID = nBR_WhileID - 1;
		}
	}
	//
	PUTVALUE(_T("br_sta"), _T("br_nm"), nBRID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_equ"), nBRID, (int)nBR_II_EQU);
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_gbr"), nBRID, (int)nBRID);
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_dl"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_fnd"), nBRID, (int)nSSFNDID);
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_tnd"), nBRID, (int)nNDID);
	//GBR
	PUTVALUE(_T("gbr_sta"), _T("gbr_nm"), nBRID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_equ"), nBRID, (int)nBR_II_EQU);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("GBR_HI_BR"), nBRID, (int)nBRID);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("GBR_II_EQUTY"), nBRID, (int)2);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_fgnd"), nBRID, (int)nSSFNDID);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_tgnd"), nBRID, (int)nNDID);
	//
	PUTDOUBLE2VALUE(_T("GBR_DYN_UIN"), _T("GBR_MORFLAG"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PA_C"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_SI_FBS"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMW12"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMW12"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIONW"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOAV"), _T("GBR_VVORECFLAG"), nBRID, (int)0);
}
