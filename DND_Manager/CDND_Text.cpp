#include "pch.h"
#include "CDND_Text.h"


CDND_Text::CDND_Text(void)
{

}

CDND_Text::~CDND_Text(void)
{
	delete m_SB_Object;

}


void CDND_Text::SetObjectData(CMarkup* pxml)
{
	m_str_id = pxml->GetAttrib(_T("id"));
	/*m_d_x = _wtof(pxml->GetAttrib(_T("x"))); 
	m_d_y = _wtof(pxml->GetAttrib(_T("y"))); */

	m_SB_Object = new CSB_Text();
	m_SB_Object->SetObjectData(pxml);
	((CSB_Text*)m_SB_Object)->SetFillColor(_T("#000000"));

	m_str_keyname = ((CSB_Text*)m_SB_Object)->GetText();
}

void CDND_Text::GetObjectData(CMarkup* pxml, int&  nDrawOrder)
{
	CString strData[18];
	strData[0].Format(_T("%s"),				((CSB_Text*)m_SB_Object)->m_strText				);
	strData[1].Format(_T("%s"),				m_str_id										);
	strData[2].Format(_T("%s"),				((CSB_Text*)m_SB_Object)->m_strStroke			);
	strData[3].Format(_T("%d"),				1												);
	strData[4].Format(_T("%s"),				_T("solid")										);
	strData[5].Format(_T("%s"),				((CSB_Text*)m_SB_Object)->m_strFill				);
	strData[6].Format(_T("%s"),				_T("")											);
	strData[7].Format(_T("%d"),				nDrawOrder										);
	strData[8].Format(_T("%.0lf"),			((CSB_Text*)m_SB_Object)->m_dX					);
	strData[9].Format(_T("%.0lf"),			((CSB_Text*)m_SB_Object)->m_dY					);
	strData[10].Format(_T("%.0lf"),			((CSB_Text*)m_SB_Object)->m_dWidth				);
	strData[11].Format(_T("%.0lf"),			((CSB_Text*)m_SB_Object)->m_dHeight				);
	strData[12].Format(_T("%s"),			((CSB_Text*)m_SB_Object)->m_strFont_family		);
	strData[13].Format(_T("%d"),			((CSB_Text*)m_SB_Object)->m_nFont_size			);
	strData[14].Format(_T("%s"),			((CSB_Text*)m_SB_Object)->m_strFont_style		);
	strData[15].Format(_T("%s"),			((CSB_Text*)m_SB_Object)->m_strFont_color		);
	strData[16].Format(_T("%s"),			((CSB_Text*)m_SB_Object)->m_strFont_anchor		);
	strData[17].Format(_T("%s"),			((CSB_Text*)m_SB_Object)->m_strFont_valign		);

	pxml->AddElem(_T("text"),						strData[0]);
	pxml->AddAttrib(_T("id"),						strData[1]);
	pxml->AddAttrib(_T("stroke"),					strData[2]);
	pxml->AddAttrib(_T("stroke-width"),				strData[3]);
	pxml->AddAttrib(_T("stroke-type"),				strData[4]);
	pxml->AddAttrib(_T("fill"),						strData[5]);
	pxml->AddAttrib(_T("fill-type"),				strData[6]);
	pxml->AddAttrib(_T("draworder"),				strData[7]);
	pxml->AddAttrib(_T("x"),						strData[8]);
	pxml->AddAttrib(_T("y"),						strData[9]);
	pxml->AddAttrib(_T("width"),					strData[10]);
	pxml->AddAttrib(_T("height"),					strData[11]);
	pxml->AddAttrib(_T("font-family"),				strData[12]);
	pxml->AddAttrib(_T("font-size"),				strData[13]);
	pxml->AddAttrib(_T("font-style"),				strData[14]);
	pxml->AddAttrib(_T("text-color"),				strData[15]);
	pxml->AddAttrib(_T("text-anchor"),				strData[16]);
	pxml->AddAttrib(_T("text-valign"),				strData[17]);
}

void CDND_Text::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	if (dZoomValue < DRAW_ZOOMLEVEL)
	{
		return;
	}

	ptDraw.x = int(m_d_x);
	ptDraw.y = int(m_d_y);

	dScale_x *= m_d_scalex;
	dScale_y *= m_d_scaley;

	dZoomValue = 1.;
	if (m_SB_Object)
		(m_SB_Object)->Draw_Object(graphics, ptDraw, dZoomValue, dScale_x, dScale_y, dAngle, strInnerText);
	

}

void CDND_Text::Draw_Object_Select(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	if (dZoomValue < DRAW_ZOOMLEVEL)
	{
		return;
	}

	ptDraw.x = int(m_d_x);
	ptDraw.y = int(m_d_y);

	dScale_x *= m_d_scalex;
	dScale_y *= m_d_scaley;

	SolidBrush penBrush(Color(255, 255, 255));
	Gdiplus::Pen					pen(&penBrush, 2.);
	pen.SetDashStyle((Gdiplus::DashStyle)DashStyleDash);

	CRect r = m_SB_Object->GetSBRect();

	Gdiplus::RectF rStroke;

	rStroke.X = r.left;
	rStroke.Y = r.top;
	rStroke.Width = r.Width();
	rStroke.Height = r.Height();

	rStroke.Inflate(2, 2);
	graphics.DrawRectangle(&pen, rStroke);




}

void CDND_Text::Draw_Object_Move(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle)
{
	if (dZoomValue < DRAW_ZOOMLEVEL)
	{
		return;
	}

	ptDraw = m_Point_Move;

	dScale_x *= m_d_scalex;
	dScale_y *= m_d_scaley;

	SolidBrush penBrush(Color(255, 255, 255));
	Gdiplus::Pen					pen(&penBrush, 2.);
	pen.SetDashStyle((Gdiplus::DashStyle)DashStyleDash);

	CRect r = m_SB_Object->GetSBRect();

	Gdiplus::RectF rStroke;

	rStroke.X = ptDraw.x - (r.Width() / 2);
	rStroke.Y = ptDraw.y - (r.Height() / 2);
	rStroke.Width = r.Width();
	rStroke.Height = r.Height();

	rStroke.Inflate(1, 1);
	graphics.DrawRectangle(&pen, rStroke);




}

BOOL	CDND_Text::Check2DwawRect(CRect rDraw, double dZoomValue)
{
	CPoint ptSB = ((CSB_Text*)m_SB_Object)->GetPoint();
	CPoint pt(int(ptSB.x * dZoomValue), int(ptSB.y * dZoomValue));

	return rDraw.PtInRect(pt);
}

CDND_Object* CDND_Text::Select2Point(CPoint pt, CDND_Object* pSelect)
{
	CRect rect = ((CSB_BLOCK*)m_SB_Object)->GetSBRect();
	CPoint ptReal;
	ptReal.x = int(m_d_x);
	ptReal.y = int(m_d_y);

	rect += ptReal;

	if (rect.PtInRect(pt))
	{
		return this;
	}

	return NULL;
}

void CDND_Text::SetEdit_Move(CPoint pt)
{
	CRect r = m_SB_Object->GetSBRect();

	((CSB_Text*)m_SB_Object)->m_dX = double(pt.x - (r.Width() / 2) );
	((CSB_Text*)m_SB_Object)->m_dY = double(pt.y - (r.Height() / 2) );

	SetEditType(DND_OBJ_EDIT_UPDATE);
}

void CDND_Text::SetEdit_InitData(int nID,CPoint pt, int nResourceID)
{
	SetEditType(DND_OBJ_EDIT_NEW);

	m_str_id.Format(_T("0_TEXT_EDIT_%d"), nID);
	
	m_SB_Object = new CSB_Text();
	CRect r = m_SB_Object->GetSBRect();
	((CSB_Text*)m_SB_Object)->m_dX = double(pt.x - (r.Width() / 2));
	((CSB_Text*)m_SB_Object)->m_dY = double(pt.y - (r.Height() / 2));
	((CSB_Text*)m_SB_Object)->m_strText = m_str_id;

	m_str_keyname = ((CSB_Text*)m_SB_Object)->GetText();

}