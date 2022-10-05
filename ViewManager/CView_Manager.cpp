#include "pch.h"
#include "CView_Manager.h"


CView_Manager *CView_Manager::_instance = NULL;

CView_Manager::CView_Manager(void)
{
}

CView_Manager::~CView_Manager(void)
{

}

CView_Manager* CView_Manager::Instance()
{
	if (_instance == 0)
	{
		_instance = new CView_Manager();
	}
	return _instance;
}

void				CView_Manager::DrawArea_Base(CDC* pDC, Graphics &graphics, CRect rectArea,BOOL bBottom)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));

	pDC->FillRect(rectArea, &brush);

	if (bBottom)
	{
		CBrush brush2;
		brush2.CreateSolidBrush(RGB(79, 148, 111));			/////////////// ÇÏ´Ü bottom

		pDC->FillRect(CRect(rectArea.left, rectArea.bottom - 1, rectArea.right, rectArea.bottom), &brush2);

		brush2.DeleteObject();
	}
	
	brush.DeleteObject();
}

void				CView_Manager::DrawArea_List(CDC* pDC, Graphics &graphics, CRect rectArea, BOOL bBottom)
{
	CBrush brush[2];
	brush[0].CreateSolidBrush(RGB(238, 247, 240));			/////////////// ÇÏ´Ü
	

	pDC->FillRect(rectArea, &brush[0]);
	if (bBottom)
	{
		brush[1].CreateSolidBrush(RGB(79, 148, 111));			/////////////// ÇÏ´Ü bottom
		pDC->FillRect(CRect(rectArea.left, rectArea.bottom - 1, rectArea.right, rectArea.bottom), &brush[1]);

		brush[1].DeleteObject();
	}
		
	brush[0].DeleteObject();
}

void				CView_Manager::DrawArea_Title(CDC* pDC, Graphics &graphics, CRect rectArea, CString strTitle,BOOL bMain, CRect rectBack)
{
	CBrush listbrush[2];
	listbrush[0].CreateSolidBrush(RGB(19, 94, 53));				/////////////// »ó´Ü ¶óÀÎ
	listbrush[1].CreateSolidBrush(RGB(255, 255, 255));			/////////////// ¹è°æ

	if (rectBack.bottom > 0)
	{
		CBrush brush;
		brush.CreateSolidBrush(RGB(238, 247, 240));			/////////////// ÇÏ´Ü

		CRect rBack(rectBack.left, rectBack.top, rectBack.right, rectArea.bottom);
		pDC->FillRect(rBack, &brush);
	}
	
	int nBold = 1;

	if (bMain)
		nBold = 2;

	pDC->FillRect(rectArea, &listbrush[0]);
	pDC->FillRect(CRect(rectArea.left, rectArea.top + nBold , rectArea.right, rectArea.bottom), &listbrush[1]);

	Gdiplus::Font					_drawfont(_T("¸¼Àº °íµñ"), 14.0f, FontStyle::FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawTitlebrush(Color(255, 19, 94, 53));

	Gdiplus::RectF  _rTitle;
	_rTitle.X					= rectArea.left;
	_rTitle.Y					= rectArea.top + 1;
	_rTitle.Width				= rectArea.Width();
	_rTitle.Height				= rectArea.Height();

	//graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
	graphics.DrawString(strTitle, -1, &_drawfont, _rTitle, &_drawStrFormat, &_drawTitlebrush);
}

void				CView_Manager::DrawArea_Unit(CDC* pDC, Graphics &graphics, CRect rectArea, CString strUnit)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(232, 232, 232));				/////////////// »ó´Ü ¶óÀÎ
	
	pDC->FillRect(rectArea, &brush);
	

	Gdiplus::Font					_drawfont(_T("¸¼Àº °íµñ"), 12.0f, FontStyle::FontStyleRegular, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawTitlebrush(Color(255, 0, 0, 0));

	Gdiplus::RectF  _rTitle;
	_rTitle.X = rectArea.left;
	_rTitle.Y = rectArea.top ;
	_rTitle.Width = rectArea.Width();
	_rTitle.Height = rectArea.Height();

	//graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
	graphics.DrawString(strUnit, -1, &_drawfont, _rTitle, &_drawStrFormat, &_drawTitlebrush);
}


void  CView_Manager::Draw_Split(CDC* pDC, Graphics &graphics, CRect rectArea, int nMode)
{

	SolidBrush						_drawbrush(Color(197, 197, 197));
	Gdiplus::Pen		_drawpen(&_drawbrush, 1.);

	if (nMode == DRAW_SPLIT_MODE_TOP) ////////////////// »ó
	{
		graphics.DrawLine(&_drawpen, rectArea.left, rectArea.top, rectArea.right , rectArea.top);
	}
	else if (nMode == DRAW_SPLIT_MODE_BOTTOM) ////////////////// ÇÏ
	{
		graphics.DrawLine(&_drawpen, rectArea.left, rectArea.bottom, rectArea.right, rectArea.bottom);
	}
	else if (nMode == DRAW_SPLIT_MODE_LEFT) ////////////////// ÁÂ
	{
		graphics.DrawLine(&_drawpen, rectArea.left, rectArea.top, rectArea.left, rectArea.bottom);
	}
	else   //////////////////////// DRAW_SPLIT_MODE_RIGHT  ¿ì
	{
		graphics.DrawLine(&_drawpen, rectArea.right, rectArea.top, rectArea.right, rectArea.bottom);
	}
	
}

void  CView_Manager::Draw_Setting_Tag(CDC* pDC, Graphics &graphics, CRect rectArea, int nType, CString strTagName)
{

	Gdiplus::RectF  _r;

	_r.X = rectArea.left;
	_r.Y = rectArea.top;
	_r.Width = rectArea.Width();
	_r.Height = rectArea.Height();

	Gdiplus::Font					_drawfont(_T("¸¼Àº °íµñ"), 12.0f, FontStyleBold, UnitPixel);
	StringFormat					_drawStrFormat;
	_drawStrFormat.SetAlignment(StringAlignmentCenter);
	_drawStrFormat.SetLineAlignment(StringAlignmentCenter);
	SolidBrush						_drawFontbrush(Color(255, 19, 94, 53));

	if (nType == 0)
	{
		//graphics.DrawString(strTagName, -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);
	}
	else
	{
		_drawFontbrush.SetColor(Color(255, 54, 55, 59));

	}
	graphics.DrawString(strTagName, -1, &_drawfont, _r, &_drawStrFormat, &_drawFontbrush);
}



void CView_Manager::GetRoundRectPath(Gdiplus::GraphicsPath* gp, int x, int y, int width, int height, int radius)
{
	gp->Reset();

	gp->AddLine(x + radius, y, x + width - radius, y);
	gp->AddArc(x + width - radius, y, radius, radius, 270, 90);
	gp->AddLine(x + width, y + radius, x + width, y + height - radius);
	gp->AddArc(x + width - radius, y + height - radius, radius, radius, 0, 90);
	gp->AddLine(x + width - radius, y + height, x + radius, y + height);
	gp->AddArc(x, y + height - radius, radius, radius, 90, 90);
	gp->AddLine(x, y + height - radius, x, y + radius);
	gp->AddArc(x, y, radius, radius, 180, 90);
	gp->CloseFigure();
}
