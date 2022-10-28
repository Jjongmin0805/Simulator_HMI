#include "pch.h"
#include "CDND_Connect.h"


CDND_Connect::CDND_Connect(void)
{
	m_nSelect_Index = -1;
	m_nSelect_Line = -1;

	m_nSelect_Form_Index = -1;
	m_nSelect_To_Index = -1;
}

CDND_Connect::~CDND_Connect(void)
{

	for (int i = 0; i < m_Array_Point.GetSize(); i++)
	{
		delete m_Array_Point.GetAt(i);
	}
	m_Array_Point.GetSize();

}

void CDND_Connect::SetObjectData(CMarkup* pxml)
{
	CString strData[11];

	strData[0] = pxml->GetAttrib(_T("id"));
	strData[1] = pxml->GetAttrib(_T("psrtype"));
	strData[2] = pxml->GetAttrib(_T("keyid"));
	strData[3] = pxml->GetAttrib(_T("type"));
	strData[4] = pxml->GetAttrib(_T("d"));
	strData[5] = pxml->GetAttrib(_T("link"));
	strData[6] = pxml->GetAttrib(_T("stroke"));
	strData[7] = pxml->GetAttrib(_T("stroke-width"));
	strData[8] = pxml->GetAttrib(_T("stroke-type"));
	strData[9] = pxml->GetAttrib(_T("usertype"));
	strData[10] = pxml->GetAttrib(_T("draworder"));


	m_str_id = strData[0];
	m_str_psrtype = strData[1];
	m_str_keyid = strData[2];

	m_n_type = _wtoi(strData[3]);

	

	m_str_link = strData[5];
	Split_Link(strData[5]);
	   
	m_str_stroke = strData[6];
	m_n_stroke_width = _wtoi(strData[7]);
	m_str_stroke_type = strData[8];

	m_n_usertype = _wtoi(strData[9]);
	m_n_draworder = _wtoi(strData[10]);

	Split_Point(strData[4]);
}

void CDND_Connect::GetObjectData(CMarkup* pxml, int&  nDrawOrder)
{
	CString strData[11];
	strData[0].Format(_T("%s"),				m_str_id										);
	strData[1].Format(_T("%s"),				m_str_psrtype									);
	strData[2].Format(_T("%s"),				m_str_keyid										);
	strData[3].Format(_T("%d"),				m_n_type										);
	
	strData[5].Format(_T("0,0,%s;1,0,%s"),	m_strID_From,m_strID_To							);
	strData[6].Format(_T("%s"),				m_str_stroke									);
	strData[7].Format(_T("%d"),				m_n_stroke_width								);
	strData[8].Format(_T("%s"),				m_str_stroke_type								);
	strData[9].Format(_T("%d"),				m_n_usertype									);
	strData[10].Format(_T("%d"),			nDrawOrder										);
	
	CString strPoint;
	CRealPoint* pPt;
	strData[4].Empty();
	for (int i = 0; i < m_Array_Point.GetSize(); i++)
	{
		pPt = m_Array_Point.GetAt(i);
		strPoint.Format(_T("%.0lf,%.0lf "), pPt->x, pPt->y);

		strData[4] += strPoint;
	}
	int nLen = strData[4].GetLength();
	strData[4].Delete(nLen - 1, 1);
	

	pxml->AddElem(_T("CONNECT"));
	pxml->AddAttrib(_T("id"),						strData[0]);
	pxml->AddAttrib(_T("psrtype"),					strData[1]);
	pxml->AddAttrib(_T("keyid"),					strData[2]);
	pxml->AddAttrib(_T("type"),						strData[3]);
	pxml->AddAttrib(_T("d"),						strData[4]);
	pxml->AddAttrib(_T("link"),						strData[5]);
	pxml->AddAttrib(_T("stroke"),					strData[6]);
	pxml->AddAttrib(_T("stroke-width"),				strData[7]);
	pxml->AddAttrib(_T("stroke-type"),				strData[8]);
	pxml->AddAttrib(_T("usertype"),					strData[9]);
	pxml->AddAttrib(_T("draworder"),				strData[10]);

}

void CDND_Connect::Split_Point(CString strData)
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
		m_Array_Point.Add(pPt);
		pPt->x = _wtof(strX);
		pPt->y = _wtof(strY);

		pPt->SetSplitRect();


		nCount++;

	}
}

void CDND_Connect::Split_Link(CString strData)
{
	CString strS;
	CString strINDEX;
	int nCount = 0;
	int nINDEX;
	
	while (AfxExtractSubString(strS, strData, nCount, _T(';')))
	{
		if (strS.IsEmpty())
			break;

		AfxExtractSubString(strINDEX, strS, 0, _T(','));
		nINDEX = _ttoi(strINDEX);

		if (nINDEX == 0)
		{
			AfxExtractSubString(strINDEX, strS, 0, _T(','));
			m_nSelect_Form_Index = nINDEX;
			AfxExtractSubString(m_strID_From, strS, 2, _T(','));
		}
		else
		{
			AfxExtractSubString(strINDEX, strS, 0, _T(','));
			m_nSelect_To_Index = nINDEX;
			AfxExtractSubString(m_strID_To, strS, 2, _T(','));
		}
	
		nCount++;
	}
	
// 	//202100817
// 	AfxExtractSubString(m_strID_CEQ_From, m_strID_From, 2, _T('_'));
// 	AfxExtractSubString(m_strID_CEQ_To, m_strID_To, 2, _T('_'));



	CString strErr;

	if(nCount != 2)
	{
		strErr.Format(_T("연결정보 오류(ID : %s)"), m_str_id);
		AfxMessageBox(strErr);
	}
		
}


BOOL	CDND_Connect::Check2DwawRect(CRect rDraw, double dZoomValue)
{
	CPoint ptMain = rDraw.CenterPoint();

	double dLen = sqrt(pow(double(rDraw.Width()), 2) + pow(double(rDraw.Height()), 2));

	double Angle1, Angle2, Anglediff, distA, distB, dbool, dCos, dSin;

	CRealPoint* pPoint1, *pPoint2;
	Gdiplus::PointF	pt1, pt2;
	for (int i = 0; i < m_Array_Point.GetSize() - 1; i++)
	{
		pPoint1 = m_Array_Point.GetAt(i);
		pPoint2 = m_Array_Point.GetAt(i + 1);

		pt1.X = (pPoint1->x * dZoomValue);
		pt1.Y = (pPoint1->y * dZoomValue);

		pt2.X = (pPoint2->x * dZoomValue);
		pt2.Y = (pPoint2->y * dZoomValue);

		Angle1 = atan2(double(pt2.Y - pt1.Y), double(pt2.X - pt1.X));
		Angle2 = atan2(double(ptMain.y - pt1.Y), double(ptMain.x - pt1.X));
		Anglediff = fabs(Angle1 - Angle2);

		distA = sqrt(pow(double(pt2.Y - pt1.Y), 2) + pow(double(pt2.X - pt1.X), 2));
		distB = sqrt(pow(double(ptMain.y - pt1.Y), 2) + pow(double(ptMain.x - pt1.X), 2));

		dSin = sin(Anglediff);
		dCos = cos(Anglediff);

		dbool = (fabs(distB)*dCos) / fabs(distA);
		//if (dbool >= (0) && dbool <= (1))
		{
			distA = fabs(distB*dSin);
			if (distA < dLen)
				return TRUE;
		}
	}

	return FALSE;
	
}

CDND_Object* CDND_Connect::Select2Point(CPoint pt, CDND_Object* pSelect)
{
	m_nSelect_Index = -1;
	m_nSelect_Line = -1;
	double Angle1, Angle2, Anglediff, distA, distB, dbool, dCos, dSin;

	CRealPoint* pPoint1, *pPoint2;
	Gdiplus::PointF	pt1, pt2;

	CRect r;
	if (this == pSelect)
	{
		for (int k = 0; k < m_Array_Point.GetSize(); k++)
		{
			pPoint1 = m_Array_Point.GetAt(k);
			r.SetRect(pPoint1->rect.X, pPoint1->rect.Y, pPoint1->rect.GetRight(), pPoint1->rect.GetBottom());
			if (r.PtInRect(pt))
			{
				m_nSelect_Index = k;
				m_Point_Move.x = pPoint1->x;
				m_Point_Move.y = pPoint1->y;

				return this;
			}
		}
	}
		
	for (int i = 0; i < m_Array_Point.GetSize() - 1; i++)
	{
		pPoint1 = m_Array_Point.GetAt(i);
		pPoint2 = m_Array_Point.GetAt(i + 1);

		pt1.X = (pPoint1->x );
		pt1.Y = (pPoint1->y );

		pt2.X = (pPoint2->x );
		pt2.Y = (pPoint2->y );

		Angle1 = atan2(double(pt2.Y - pt1.Y), double(pt2.X - pt1.X));
		Angle2 = atan2(double(pt.y - pt1.Y), double(pt.x - pt1.X));
		Anglediff = fabs(Angle1 - Angle2);

		distA = sqrt(pow(double(pt2.Y - pt1.Y), 2) + pow(double(pt2.X - pt1.X), 2));
		distB = sqrt(pow(double(pt.y - pt1.Y), 2) + pow(double(pt.x - pt1.X), 2));

		dSin = sin(Anglediff);
		dCos = cos(Anglediff);

		dbool = (fabs(distB)*dCos) / fabs(distA);
		if (dbool >= (0) && dbool <= (1))
		{
			m_nSelect_Line = i;
			distA = fabs(distB*dSin);
			if (distA < CONNECT_SELECT_GAP) //선로 선택시 변경!
			{
				CRect r;
				for (int k = 0; k < m_Array_Point.GetSize(); k++)
				{
					pPoint1 = m_Array_Point.GetAt(k);
					r.SetRect(pPoint1->rect.X, pPoint1->rect.Y, pPoint1->rect.GetRight(), pPoint1->rect.GetBottom());
					if (r.PtInRect(pt))
					{
						m_nSelect_Index = k;
						m_Point_Move.x = pPoint1->x;
						m_Point_Move.y = pPoint1->y;
						break;
					}
				}
				return this;
			}
				
		}
	}

	return NULL;
}


void CDND_Connect::Draw_Object_Select(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	CSB_Object sbObj;

	SolidBrush brush_ellipse (Color(255,255,255));
	Gdiplus::Pen					pen_ellipse(&brush_ellipse, 1.);

	Gdiplus::Brush* pBrush_stroke = sbObj.GetBrush(_T("#FF0000"), _T(""));
	UINT	unPenStyle = sbObj.GetPenStyle(m_str_stroke_type);
	Gdiplus::Pen					pen(pBrush_stroke, double(m_n_stroke_width) *2);
	pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);
	pen.SetLineJoin(LineJoinRound);

	Gdiplus::GraphicsPath gp;

	CRealPoint* pPoint1, *pPoint2;
	Gdiplus::PointF	pt1, pt2;
	for (int i = 0; i < m_Array_Point.GetSize() - 1; i++)
	{
		pPoint1 = m_Array_Point.GetAt(i);
		pPoint2 = m_Array_Point.GetAt(i + 1);

		pt1.X = (pPoint1->x );
		pt1.Y = (pPoint1->y );

		pt2.X = (pPoint2->x );
		pt2.Y = (pPoint2->y );

		gp.AddLine(pt1, pt2);
	}
	graphics.DrawPath(&pen, &gp);
	for (int i = 0; i < m_Array_Point.GetSize() ; i++)
	{
		pPoint1 = m_Array_Point.GetAt(i);

		graphics.FillEllipse(&brush_ellipse,pPoint1->rect);
	}
	delete pBrush_stroke;
}

void CDND_Connect::Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle, CString strInnerText)
{
	CSB_Object sbObj;

	Gdiplus::Brush* pBrush_stroke = sbObj.GetBrush(m_str_stroke, _T(""));
	UINT	unPenStyle = sbObj.GetPenStyle(m_str_stroke_type);
	Gdiplus::Pen					pen(pBrush_stroke, double(m_n_stroke_width) );
	pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);
	pen.SetLineJoin(LineJoinRound);
	
	Gdiplus::GraphicsPath gp;

	CRealPoint* pPoint1, *pPoint2;
	Gdiplus::PointF	pt1, pt2;
	
	for (int i = 0; i < m_Array_Point.GetSize() - 1; i++)
	{
		pPoint1 = m_Array_Point.GetAt(i);
		pPoint2 = m_Array_Point.GetAt(i + 1);

		pt1.X = (pPoint1->x);
		pt1.Y = (pPoint1->y);

		pt2.X = (pPoint2->x);
		pt2.Y = (pPoint2->y);

		gp.AddLine(pt1, pt2);
	}

	//연결된 선로 없음을 표시 하는 부분 
	if (m_st_Kasim_LNsec_Info.m_nBR_Fnd == 0 || m_st_Kasim_LNsec_Info.m_nBR_Tnd == 0)
	{
		Gdiplus::Brush* pBrush_stroke = sbObj.GetBrush(_T("#FF00DD"), _T(""));
		UINT	unPenStyle = sbObj.GetPenStyle(m_str_stroke_type);
		Gdiplus::Pen					pen(pBrush_stroke, double(m_n_stroke_width*2)); //해지된 선로 크기 !
		pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);
		pen.SetLineJoin(LineJoinRound);

		graphics.DrawPath(&pen, &gp);
		delete pBrush_stroke;
	}
	else
	{
		graphics.DrawPath(&pen, &gp);
		delete pBrush_stroke;
	}
// 	graphics.DrawPath(&pen, &gp);
// 	delete pBrush_stroke;

}

void CDND_Connect::Draw_Object_Move(Graphics &graphics, CPoint ptDraw, double dZoomValue
	, double dScale_x, double dScale_y, double dAngle)
{
	CSB_Object sbObj;

	SolidBrush brush_ellipse(Color(255, 255, 255));
	Gdiplus::Pen					pen_ellipse(&brush_ellipse, 1.);

	Gdiplus::Brush* pBrush_stroke = sbObj.GetBrush(_T("#FF0000"), _T(""));
	UINT	unPenStyle = sbObj.GetPenStyle(m_str_stroke_type);
	Gdiplus::Pen					pen(pBrush_stroke, double(m_n_stroke_width) * 2);
	pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);
	/*pen.SetStartCap(LineCapRound);
	pen.SetEndCap(LineCapRound);*/
	pen.SetLineJoin(LineJoinRound);
	Gdiplus::GraphicsPath gp;

	CRealPoint* pPoint1, *pPoint2;
	Gdiplus::PointF	pt1, pt2;
	//선로 색상 변경 하는 부분!!!!
	for (int i = 0; i < m_Array_Point.GetSize() - 1; i++)
	{
		pPoint1 = m_Array_Point.GetAt(i);
		pPoint2 = m_Array_Point.GetAt(i + 1);

		if (m_nSelect_Index == i)
		{
			pt1.X = double(m_Point_Move.x);
			pt1.Y = double(m_Point_Move.y);

			pt2.X = (pPoint2->x);
			pt2.Y = (pPoint2->y);
		}
		else if (m_nSelect_Index == i+1)
		{
			pt1.X = (pPoint1->x);
			pt1.Y = (pPoint1->y);

			pt2.X = double(m_Point_Move.x);
			pt2.Y = double(m_Point_Move.y);
		}
		else
		{
			pt1.X = (pPoint1->x);
			pt1.Y = (pPoint1->y);

			pt2.X = (pPoint2->x);
			pt2.Y = (pPoint2->y);
		}
		

		gp.AddLine(pt1, pt2);

	}
	graphics.DrawPath(&pen, &gp);
	//이동 할때 구분점 점 표시 부분 
	RectF rect;
	for (int i = 0; i < m_Array_Point.GetSize(); i++)
	{
		pPoint1 = m_Array_Point.GetAt(i);

		if (m_nSelect_Index == i)
		{
			rect.X = m_Point_Move.x - ( pPoint1->rect.Width / 2);
			rect.Y = m_Point_Move.y - ( pPoint1->rect.Height / 2);
			rect.Width = pPoint1->rect.Width;
			rect.Height = pPoint1->rect.Height;

			graphics.FillEllipse(&brush_ellipse, rect);
		}
		else
		{
			graphics.FillEllipse(&brush_ellipse, pPoint1->rect);
		}
		
	}



	delete pBrush_stroke;

}

void CDND_Connect::SetEdit_Move(CPoint pt)
{
	if (m_Array_Point.GetSize() - 1 < m_nSelect_Index || m_nSelect_Index == -1)
	{
		AfxMessageBox(_T("connect : point index err !!"));
		return;
	}	
	CRealPoint* ptReal;
	ptReal = m_Array_Point.GetAt(m_nSelect_Index);
	ptReal->x = double(pt.x);
	ptReal->y = double(pt.y);

	ptReal->SetSplitRect();	
}

void CDND_Connect::SetEdit_Split_Add()
{
	if (m_Array_Point.GetSize() - 2 < m_nSelect_Line || m_nSelect_Line  == -1)
	{
		AfxMessageBox(_T("connect : point index err !!"));
		return;
	}
	double Angle1, distA, dCos, dSin;

	CRealPoint* pPoint1, *pPoint2, *ptNew;
	Gdiplus::PointF	pt1, pt2;

	pPoint1 = m_Array_Point.GetAt(m_nSelect_Line);
	pPoint2 = m_Array_Point.GetAt(m_nSelect_Line + 1);

	pt1.X = (pPoint1->x);
	pt1.Y = (pPoint1->y);

	pt2.X = (pPoint2->x);
	pt2.Y = (pPoint2->y);

	Angle1 = atan2(double(pt2.Y - pt1.Y), double(pt2.X - pt1.X));

	distA = sqrt(pow(double(pt2.Y - pt1.Y), 2) + pow(double(pt2.X - pt1.X), 2));

	dSin = sin(Angle1) * distA / 2;
	dCos = cos(Angle1) * distA / 2;

	ptNew = new CRealPoint();
	m_Array_Point.InsertAt(m_nSelect_Line + 1, ptNew);
	ptNew->x = double(int(pt1.X) + int(dCos));
	ptNew->y = double(int(pt1.Y) + int(dSin));

	ptNew->SetSplitRect();
	SetEditType(DND_OBJ_EDIT_UPDATE);
}

void CDND_Connect::SetEdit_Split_Del()
{
	if (m_Array_Point.GetSize() - 1 < m_nSelect_Index || m_nSelect_Index == -1)
	{
		AfxMessageBox(_T("connect : point index err !!"));
		return;
	}
	
	CRealPoint* ptReal;
	ptReal = m_Array_Point.GetAt(m_nSelect_Index);
	m_Array_Point.RemoveAt(m_nSelect_Index);
	
	delete ptReal;
	
	SetEditType(DND_OBJ_EDIT_UPDATE);
}

void CDND_Connect::SetEdit_InitData(int nID, CPoint pt, int nResourceID)
{
	SetEditType(DND_OBJ_EDIT_NEW);
	m_str_id.Format(_T("0_CONNECT_EDIT_%d"), nID);
	m_str_psrtype = _T("LINE");
	m_str_keyid.Empty();

	m_n_type = 1;
	   
	m_str_link.Empty();
	m_strID_From.Empty();
	m_strID_To.Empty();
	m_strID_CEQ_From.Empty();
	m_strID_CEQ_To.Empty();

	m_str_stroke = _T("#00FFFF");
	m_n_stroke_width = 2;
	m_str_stroke_type = _T("solid");

	m_n_usertype = 2 ;
	m_n_draworder = 0 ; 

	CRealPoint* pPt = new CRealPoint();
	m_Array_Point.Add(pPt);
	pPt->x = double(pt.x);
	pPt->y = double(pt.y);
	pPt->SetSplitRect();

	pPt = new CRealPoint();
	m_Array_Point.Add(pPt);
	pPt->x = double(pt.x);
	pPt->y = double(pt.y);
	pPt->SetSplitRect();

	m_Point_Move.x = pPt->x;
	m_Point_Move.y = pPt->y;

	m_nSelect_Index = 1;
	m_nSelect_Line = 0;
}

void CDND_Connect::SetEdit_InitData_KASIM(int nLNSEC_ID, int nBR_ID, int nIJ_ID, int nLD_ID)
{
	CString stCEQID, stName;
	stCEQID.Format(_T("999051%08d"), nLNSEC_ID);
	m_str_keyid = stCEQID;
	stName.Format(_T("LNSEC%08d"), nLNSEC_ID);
	m_str_keyname = stName;

	m_st_Kasim_LNsec_Info.m_nLNSECID = nLNSEC_ID;
	m_st_Kasim_LNsec_Info.m_nBRID = nBR_ID;
	m_st_Kasim_LNsec_Info.m_nIJID = nIJ_ID;
	m_st_Kasim_LNsec_Info.m_nLDID = nLD_ID;
}

void CDND_Connect::Set_NEW_InitData_KASIM(CString stKASIM_NM, CString stCEQID, int nLNSECID, int nBRID, int nIJID, int nLDID, int nFnd, int nTnd)
{
	int nIJ_WhileID = 0, nBR_II_EQU = 0, nIJEQU = 0, nIJEQUTY= 0;
	//
	int nGBR_II_EQUTY = 0, nBR_WhileID = nBRID;

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
		if (nGBR_II_EQUTY == 1)
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
	//LNSEC_STA
	PUTVALUE(_T("LNSEC_STA"), _T("LNSEC_NM"), nLNSECID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("LNSEC_STA"), _T("LNSEC_CEQID"), nLNSECID, (unsigned long long)_wtoll(stCEQID));
	PUTVALUE(_T("LNSEC_STA"), _T("LNSEC_II_BR"), nLNSECID, (int)nBRID);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_INNERPOLE"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_FPOLE"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_TPOLE"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_INNERSEC"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_PRIVAT"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_TYPE_ID"), nLNSECID, (int)1);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_LENGTH"), nLNSECID, (double)0.1);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_CONSTYPE"), nLNSECID, (int)0);
	//LNSEC_DYN_UIN
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_UIN"), _T("LNSEC_SW_FOR_CONST"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_UIN"), _T("LNSEC_HIS_NOTSRCH"), nLNSECID, (int)0);
	//LNSEC_DYN_NCPO
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_NCPO"), _T("LNSEC_DEAD"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_NCPO"), _T("LNSEC_II_ISL"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_NCPO"), _T("LNSEC_II_DL"), nLNSECID, (int)0);
	//LNSEC_DYN_RPFO
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PLOADMW"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PLOADMVAR"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PGENMW"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PGENMVAR"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PALOADMW"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PBLOADMW"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PCLOADMW"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PALOADMAR"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PBLOADMAR"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PCLOADMAR"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PARPFKV"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PBRPFKV"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PCRPFKV"), nLNSECID, (double)0);	
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
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_EQUTY"), nBRID, (int)1); //lnsec은 
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

	nIJ_WhileID = nIJID; //특별하게 저장
	while (nIJEQU == 0)
	{
		if (nIJID == 999999)
		{
			break;
		}
		if (nIJ_WhileID == 1)
		{
			nIJEQU = 1;
			break;
		}
		nIJEQUTY = GETVALUE(int, _T("IJ_STA"), _T("IJ_II_EQUTY"), nIJ_WhileID - 1);
		if (nIJEQUTY == 6)
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
	PUTVALUE(_T("IJ_STA"), _T("IJ_NM"), nIJID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_EQUTY"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_EQUTY"), nIJID, (int)6);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_EQU"), nIJID, (int)nIJEQU);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_GND"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_GND"), nIJID, (int)nTnd);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_DL"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_DL"), nIJID, (int)0);
	//IJ_DYN_UIN
	PUTDOUBLE2VALUE(_T("IJ_DYN_UIN"), _T("IJ_SOCMAXORDER"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_UIN"), _T("IJ_SOCMINORDER"), nIJID, (int)0);
	//IJ_DYN_NCPO
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_SI_BS"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_II_BS"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_DEAD"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_BSSTAT"), nIJID, (int)0);
	//IJ_DYN_MEA
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_3PMEAMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_3PMEAMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PAMEAMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PAMEAMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PBMEAMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PBMEAMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PCMEAMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PCMEAMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_MEAFLAG"), nIJID, (int)0);
	//IJ_DYN_RPFO
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PARPFMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PARPFMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PBRPFMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PBRPFMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PCRPFMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PCRPFMVAR"), nIJID, (double)0);
	//IJ_DYN_VVOO
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PAVVOMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PAVVOMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PBVVOMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PBVVOMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PCVVOMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PCVVOMVAR"), nIJID, (double)0);
	//IJ_DYN_DLEO
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PAGENESTMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PBGENESTMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PCGENESTMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PAGENESTMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PBGENESTMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PCGENESTMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_3PGENESTMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_3PGENESTMVAR"), nIJID, (double)0);
	//LD_STA
	PUTVALUE(_T("LD_STA"), _T("LD_NM"), nLDID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_SI_GND"), nLDID, (int)0);
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_GND"), nLDID, (int)nTnd);
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_IJ"), nLDID, (int)nIJID);
	//LD_DYN_UIN
	PUTDOUBLE2VALUE(_T("LD_DYN_UIN"), _T("LD_DIV"), nLDID, (double)0);
}

int	CDND_Connect::GetLinkPos()
{
	if (m_nSelect_Index == -1)
		return CONNECT_POS_NORMAL;

	if (m_nSelect_Index == 0)
		return CONNECT_POS_FIRST;

	if(m_nSelect_Index == m_Array_Point.GetSize() -1)
		return CONNECT_POS_LAST;


	return CONNECT_POS_NORMAL;
}

void CDND_Connect::Draw_Object_Cancle(Graphics &graphics, CPoint ptDraw, double dZoomValue, double dScale_x, double dScale_y, double dAngle)
{
	CSB_Object sbObj;

	SolidBrush brush_ellipse(Color(255, 255, 255));
	Gdiplus::Pen					pen_ellipse(&brush_ellipse, 3.);

	Gdiplus::Brush* pBrush_stroke = sbObj.GetBrush(_T("#FF4848"), _T(""));
	UINT	unPenStyle = sbObj.GetPenStyle(m_str_stroke_type);
	Gdiplus::Pen					pen(pBrush_stroke, double(m_n_stroke_width) * 3);
	pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);
	/*pen.SetStartCap(LineCapRound);
	pen.SetEndCap(LineCapRound);*/
	pen.SetLineJoin(LineJoinRound);
	Gdiplus::GraphicsPath gp;

	CRealPoint* pPoint1, *pPoint2;
	Gdiplus::PointF	pt1, pt2;
	//선로 색상 변경 하는 부분!!!!

	for (int i = 0; i < m_Array_Point.GetSize() - 1; i++)
	{
		pPoint1 = m_Array_Point.GetAt(i);
		pPoint2 = m_Array_Point.GetAt(i + 1);

		pt1.X = (pPoint1->x);
		pt1.Y = (pPoint1->y);

		pt2.X = (pPoint2->x);
		pt2.Y = (pPoint2->y);

		gp.AddLine(pt1, pt2);
	}

// 	graphics.DrawPath(&pen, &gp);
//  delete pBrush_stroke;

	//연결된 선로 없음을 표시 하는 부분 
	if (m_st_Kasim_LNsec_Info.m_nBR_Fnd == 0 )
	{
		if (m_st_Kasim_LNsec_Info.m_nBR_Connect_Check != 9999)
		{
			Gdiplus::Brush* pBrush_stroke = sbObj.GetBrush(_T("#FF00DD"), _T(""));
			UINT	unPenStyle = sbObj.GetPenStyle(m_str_stroke_type);
			Gdiplus::Pen					pen(pBrush_stroke, double(m_n_stroke_width));
			pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);
			pen.SetLineJoin(LineJoinRound);

			graphics.DrawPath(&pen, &gp);
			delete pBrush_stroke;
		}	
		else {
			graphics.DrawPath(&pen, &gp);
			delete pBrush_stroke;
		}
	}
	else if ( m_st_Kasim_LNsec_Info.m_nBR_Tnd == 0)
	{
		if (m_st_Kasim_LNsec_Info.m_nBR_Connect_Check != 9999)
		{
			Gdiplus::Brush* pBrush_stroke = sbObj.GetBrush(_T("#FF00DD"), _T(""));
			UINT	unPenStyle = sbObj.GetPenStyle(m_str_stroke_type);
			Gdiplus::Pen					pen(pBrush_stroke, double(m_n_stroke_width));
			pen.SetDashStyle((Gdiplus::DashStyle)unPenStyle);
			pen.SetLineJoin(LineJoinRound);

			graphics.DrawPath(&pen, &gp);
			delete pBrush_stroke;
		}
		else
		{
			graphics.DrawPath(&pen, &gp);
			delete pBrush_stroke;		
		}
	}
	else
	{
		graphics.DrawPath(&pen, &gp);
		delete pBrush_stroke;
	}
}

