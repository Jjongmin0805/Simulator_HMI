// SkinComboboxlist.cpp : implementation file
//

#include "pch.h"
#include "SkinComboboxlist.h"

/////////////////////////////////////////////////////////////////////////////
// CSkinComboboxlist

CSkinComboboxlist::CSkinComboboxlist()
{
	m_cfBackGround = g_gbl.GetRGB( IDX_RGB_FONT_WHITE );
}

CSkinComboboxlist::~CSkinComboboxlist()
{
}


BEGIN_MESSAGE_MAP(CSkinComboboxlist, CListBox)	
	ON_WM_PAINT()	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinComboboxlist message handlers

void CSkinComboboxlist::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	RECT rc;
	GetClientRect(&rc);

	CBrush br;
	br.CreateSolidBrush( m_cfBackGround );
	dc.FillRect( &rc,&br );
}