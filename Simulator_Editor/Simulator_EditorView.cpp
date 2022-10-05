
// Simulator_EditorView.cpp: CSimulator_EditorView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Simulator_Editor.h"
#endif

#include "Simulator_EditorDoc.h"
#include "Simulator_EditorView.h"
#include "MainFrm.h"

#include "../DND_Manager/CDND_Manager.h"
#include "../SB_Manager/CSB_Manager.h"

#include "../DND_Manager/CKASIM_ND.h"
#include "../Date_CSV_Files/CDate_Csv_File_Dlg.h"

#define SELECT_DRAW_COLOR															RGB( 200, 200, 200 )
#define	DEFALUT_TEXT_COLOR															RGB( 255, 255, 255 )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimulator_EditorView

IMPLEMENT_DYNCREATE(CSimulator_EditorView, CScrollView)

BEGIN_MESSAGE_MAP(CSimulator_EditorView, CScrollView)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSELEAVE()
	ON_COMMAND(ID_EDITMENU_MOVE, &CSimulator_EditorView::OnEditmenuMove)
	ON_MESSAGE(WM_FINDOBJ_MSG, &CSimulator_EditorView::OnFindObjPosition)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDITMENU_DEL, &CSimulator_EditorView::OnEditmenuDel)
	ON_COMMAND(ID_CONNECTMENU_SPLIT_MOVE, &CSimulator_EditorView::OnConnectmenuSplitMove)
	ON_COMMAND(ID_CONNECTMENU_SPLIT_DEL, &CSimulator_EditorView::OnConnectmenuSplitDel)
	ON_COMMAND(ID_CONNECTMENU_DEL, &CSimulator_EditorView::OnConnectmenuDel)
	ON_COMMAND(ID_CONNECTMENU_SPLIT_INSERT, &CSimulator_EditorView::OnConnectmenuSplitInsert)
	ON_COMMAND_RANGE(SYMBOL_MENU_ID_FIRST, SYMBOL_MENU_ID_LAST, &CSimulator_EditorView::OnEdit_Add_Symbol)
	ON_COMMAND(SYMBOL_MENU_ID_CONNECT, &CSimulator_EditorView::OnEdit_Add_Connect)
	ON_COMMAND(SYMBOL_MENU_ID_TEXT, &CSimulator_EditorView::OnEdit_Add_Text)
	ON_COMMAND(ID_CONNECTMENU_CANCEL, &CSimulator_EditorView::OnConnectmenuCancel)
	ON_COMMAND(ID_EDITMENU_CANCEL, &CSimulator_EditorView::OnEditmenuCancel)
END_MESSAGE_MAP()

// CSimulator_EditorView 생성/소멸

CSimulator_EditorView::CSimulator_EditorView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.	
	m_nMouseMode = MOUSE_MODE_NORMAL;
	m_dZoomValue = 1.0;

	m_pSelect_DNDObj = NULL;
	m_pSelect_DNDObj_Move = NULL;
	m_pSelect_DNDObj_Cancle = NULL;
	m_pSelect_DNDObj_Cancle_From = NULL;
	m_pSelect_DNDObj_Cancle_TO = NULL;
	m_pFindDlg = NULL;
	m_nCheck_Gen_upload = 0;
	m_nMTRDELETE_NO = 0;

	InitTooltip();
}

CSimulator_EditorView::~CSimulator_EditorView()
{
	delete m_pFindDlg;
}

BOOL CSimulator_EditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CSimulator_EditorView 그리기

void CSimulator_EditorView::OnDraw(CDC* pDC)
{
	CDND_Manager* pDNDMng = CDND_Manager::Instance();
	if (pDNDMng->m_strFileName.IsEmpty())
	{
		return;
	}
	   
	OnPrepareDC(pDC);

	CRect rect;
	GetClientRect(&rect);

	rect.InflateRect(int(50 * m_dZoomValue), int(50 * m_dZoomValue));

	CPoint pt = GetScrollPosition();

	rect += pt;

	CDC memDC;
	CBitmap	* pOldBitmap, bitmap;

	memDC.CreateCompatibleDC(pDC);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&bitmap);

	memDC.SetWindowOrg(rect.left, rect.top);

	Graphics						graphics(memDC.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	double zx, zy;
	zx = m_dZoomValue;
	zy = m_dZoomValue;

	graphics.ScaleTransform(zx, zy);

	pDNDMng->Draw_DND(graphics, rect.CenterPoint(), rect, m_dZoomValue, 1., 1.);
	//캡쳐하는부분 만들어야함 !

	if(m_pSelect_DNDObj)
	{
		if (m_nMouseMode == MOUSE_MODE_OBJ_MOVE)
		{
			m_pSelect_DNDObj->Draw_Object_Move(graphics, rect.CenterPoint(), m_dZoomValue, 1., 1.);
		}
		else 
			m_pSelect_DNDObj->Draw_Object_Select(graphics, rect.CenterPoint(), m_dZoomValue, 1., 1.);
	}
	if (m_pSelect_DNDObj_Move) //선로 자동으로 잡아 주는 부분 각도 맞추기 !
	{
		m_pSelect_DNDObj_Move->Draw_Object_Select_Move(graphics, rect.CenterPoint(), m_dZoomValue, 1., 1.);
	}
	if (m_pSelect_DNDObj_Cancle) //선로 연결해지 부분
	{
		if (m_pSelect_DNDObj_Cancle->ObjectType_Get() == DND_OBJTYPE_CONNECT )
		{
			m_pSelect_DNDObj_Cancle->Draw_Object_Cancle(graphics, rect.CenterPoint(), m_dZoomValue, 1., 1.);
			if (m_pSelect_DNDObj_Cancle_From)
			{
				m_pSelect_DNDObj_Cancle_From->Draw_Object_Select_Cancel(graphics, rect.CenterPoint(), m_dZoomValue, 1., 1.);
			}
			if (m_pSelect_DNDObj_Cancle_TO)
			{
				m_pSelect_DNDObj_Cancle_TO->Draw_Object_Select_Cancel(graphics, rect.CenterPoint(), m_dZoomValue, 1., 1.);
			}
		}

		if (m_pSelect_DNDObj_Cancle->ObjectType_Get() != DND_OBJTYPE_CONNECT && m_pSelect_DNDObj_Cancle->ObjectType_Get() != DND_OBJTYPE_TEXT)
		{
			//설비 
			int nBRID = 0;
			CDND_Switch* pSwitch = (CDND_Switch*)m_pSelect_DNDObj_Cancle;
			CDND_Manager* pDNDMng = CDND_Manager::Instance();
			CDND_Switch* pMulti_M;
			CDND_Connect* pConnect;
			int nFNDID = 0, nTNDID = 0;
			if ( pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID != 0 )
			{
				//다회로 개폐기?
				for (int i = 0; i < pSwitch->m_Array_Multi.GetSize(); i++)
				{
					pMulti_M = (CDND_Switch*)pSwitch->m_Array_Multi.GetAt(i); 

					nBRID = pMulti_M->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.GetAt(i);

					m_pSelect_DNDObj_Cancle_LNSEC = pDNDMng->GetDNDObject2_KASIM_ID(nBRID);

					if (m_pSelect_DNDObj_Cancle_LNSEC)
					{
						m_pSelect_DNDObj_Cancle_LNSEC->Draw_Object_Cancle(graphics, rect.CenterPoint(), m_dZoomValue, 1., 1.);
					}
				}
				//일반 스위치
				for (int i = 0; i < pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.GetSize(); i++)
				{
					nBRID = pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.GetAt(i);
					m_pSelect_DNDObj_Cancle_LNSEC = pDNDMng->GetDNDObject2_KASIM_ID(nBRID);

					//20210927 선로 체크용??
					pConnect = (CDND_Connect*)m_pSelect_DNDObj_Cancle_LNSEC;
					pConnect->m_st_Kasim_LNsec_Info.m_nBR_Connect_Check = 0;
					if (pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd == 0 )
					{
						if (pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd || pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd  )
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Connect_Check = 9999; //연결이 되있음
						}
					}
					if (pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd == 0)
					{
						if (pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd || pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd)
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Connect_Check = 9999; //연결이 되있음
						}
					}

					if (m_pSelect_DNDObj_Cancle_LNSEC)
					{
						m_pSelect_DNDObj_Cancle_LNSEC->Draw_Object_Cancle(graphics, rect.CenterPoint(), m_dZoomValue, 1., 1.);
					}
				}
			}
			else
			{
				for (int i = 0; i < pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.GetSize(); i++)
				{
					nBRID = pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.GetAt(i);
					m_pSelect_DNDObj_Cancle_LNSEC = pDNDMng->GetDNDObject2_KASIM_ID(nBRID);

					//20210927 선로 체크용??
					pConnect = (CDND_Connect*)m_pSelect_DNDObj_Cancle_LNSEC;
					pConnect->m_st_Kasim_LNsec_Info.m_nBR_Connect_Check = 0;
					if (pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd == 0)
					{
						if (pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd == pSwitch->m_st_Kasim_ND_Info.m_nNDID )
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Connect_Check = 9999; //연결이 되있음
						}
					}
					if (pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd == 0)
					{
						if (pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd == pSwitch->m_st_Kasim_ND_Info.m_nNDID)
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Connect_Check = 9999; //연결이 되있음
						}
					}
					if (m_pSelect_DNDObj_Cancle_LNSEC)
					{
						m_pSelect_DNDObj_Cancle_LNSEC->Draw_Object_Cancle(graphics, rect.CenterPoint(), m_dZoomValue, 1., 1.);
					}					
				}
			}
		}
	}

	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0,0,SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}

void CSimulator_EditorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;

	sizeTotal.cx = 100;
	sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);	

	//자동으로 읽어오는 부분입니다.

	CDND_Manager* pDNDMng = CDND_Manager::Instance();
	pDNDMng->SVG_AutoLoadAs();
	//김종민 - 입력 20210625 
	pDNDMng->SVG_KASIM_Association(); //20210303
	pDNDMng->SVG_KASIM_Association_Index(); //20210303
// 	
	Reset(); //20211203
	//RedrawWindow();
	SetForegroundWindow();

}

void CSimulator_EditorView::Reset()
{
	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	CDND_Manager* pDNDMng = CDND_Manager::Instance();

	sizeTotal.cx = pDNDMng->m_st_SVG_G.st_dWidth;
	sizeTotal.cy = pDNDMng->m_st_SVG_G.st_dHeight;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
	//위치 포인트로 변경???
	CPoint pt;
	pt.x = sizeTotal.cx / 2;
	pt.y = sizeTotal.cy / 2;
	ScrollToPosition(pt);
}

// CSimulator_EditorView 진단

#ifdef _DEBUG
void CSimulator_EditorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSimulator_EditorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG


// CSimulator_EditorView 메시지 처리기


BOOL CSimulator_EditorView::OnEraseBkgnd(CDC* pDC)
{

	CDND_Manager* pDNDMng = CDND_Manager::Instance();
	if (pDNDMng->m_strFileName.IsEmpty())
	{
		Graphics						graphics(pDC->GetSafeHdc());
		graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

		CRect rect;
		GetClientRect(&rect);

		RectF r;
		r.X = rect.left;
		r.Y = rect.top;
		r.Width = rect.Width();
		r.Height = rect.Height();

		SolidBrush bgBrush(Color(0, 0, 0));
		graphics.FillRectangle(&bgBrush, r);
	}
	
	return TRUE;
}

CPoint CSimulator_EditorView::GetScreenPoint(CPoint pt)
{
	CPoint scpt = GetScrollPosition();
	double x = ((scpt.x + pt.x) / m_dZoomValue);
	double y = ((scpt.y + pt.y) / m_dZoomValue);

	return CPoint(x, y);
}

CPoint CSimulator_EditorView::GetScreenPoint_Real(CPoint pt)
{
	CPoint scpt = GetScrollPosition();

	double x = (pt.x * m_dZoomValue) - (scpt.x);
	double y = (pt.y * m_dZoomValue) - (scpt.y);

	return CPoint(x, y);
}

CDND_Object*		CSimulator_EditorView::Get_DND_Object2Pt(CPoint pt, BOOL bConnect)
{
	CDND_Manager* pDNDMng = CDND_Manager::Instance();

	return pDNDMng->GetDNDObject2Point(pt,m_pSelect_DNDObj, bConnect);
}

CDND_Object*		CSimulator_EditorView::Get_DND_Object2Pt_Cancel(CPoint pt, BOOL bConnect)
{
	CDND_Manager* pDNDMng = CDND_Manager::Instance();

	return pDNDMng->GetDNDObject2Point_Cancel(pt, m_pSelect_DNDObj, bConnect);
}

CDND_Object*		CSimulator_EditorView::Get_DND_ObjectToINDEX(CString stNDIndex)
{
	return NULL;
}

void CSimulator_EditorView::SetLink_Connect(CPoint pt)
{
	int nMultSW = 0;
	CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj;
	int nLinkPos = pConnect->GetLinkPos();
	if (nLinkPos == CONNECT_POS_FIRST
		|| nLinkPos == CONNECT_POS_LAST)
	{
		CDND_Object*  pLinkObj = Get_DND_Object2Pt(pt,FALSE);
		if (pLinkObj)
		{
			if (pLinkObj->ObjectType_Get() == DND_OBJTYPE_BLOCK
				|| pLinkObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
			{
				CDND_Object*  pBlock;
				if (pLinkObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
				{
					CDND_Manager* pDNDMng = CDND_Manager::Instance();
					pBlock = pDNDMng->GetDNDObject2Point(pt, pLinkObj,FALSE);
					nMultSW = 1;
				}
				else
				{
					pBlock = pLinkObj;
				}
				////////////////////////// 개폐기의 상태도 확인 해야된다.
				////////////////////////// 다회로 1 link, 개폐기 2 link , 더미 4 link ?
				if (pConnect->m_strID_From != pBlock->Get_ID_Real()
					&& pConnect->m_strID_To != pBlock->Get_ID_Real())
				{
					CString strMsg;
					strMsg.Format(_T("%s,%s 와 연결을 구성시겠습니까?"), pBlock->Get_ID_Real(), pBlock->m_str_keyname);

					UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);
					if (nRe == IDYES)
					{
						CDND_Switch*	pSwitch = (CDND_Switch*)pBlock;
						if (nLinkPos == CONNECT_POS_LAST)
						{
							pConnect->m_strID_To = pBlock->Get_ID_Real();
							//pConnect->m_nLnsec_Tnd = pBlock->m_nTNDID;
							//연결된 선로 입력?
							//CBSW일 경우?			
							pConnect->m_strID_CEQ_To = pBlock->m_str_keyid;
							pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq = pBlock->m_str_keyid;						
							SetLink_Connect_Inset_ND(pSwitch, pConnect, 2, nMultSW);
							STA_Inset(pConnect, pSwitch);
						}
						else
						{
							pConnect->m_strID_From = pBlock->Get_ID_Real();
							//pConnect->m_nLnsec_Fnd = pBlock->m_nFNDID;	
							//연결된 선로 입력?
							//CBSW일 경우?
							pConnect->m_strID_CEQ_From = pBlock->m_str_keyid;
							pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq = pBlock->m_str_keyid;
							SetLink_Connect_Inset_ND(pSwitch, pConnect,1, nMultSW);
							STA_Inset(pConnect, pSwitch);
						}
					}
				}
				
			}
		}	
	}
}

void CSimulator_EditorView::SetLink_Connect_Inset_ND(CDND_Switch *pSwitch, CDND_Connect *pConnect, int nNdINDEX, int nMultSW)
{
	if (pSwitch->m_str_psrtype == "JUNCTION" || pSwitch->m_str_psrtype == "CABLEPOLE")
	{
		if (nNdINDEX == 1)
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pSwitch->m_st_Kasim_ND_Info.m_nNDID;
			pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
		}
		else
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pSwitch->m_st_Kasim_ND_Info.m_nNDID;
			pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
		}
	}
	//CONSUMER
	else if (pSwitch->m_str_psrtype == "CONSUMER")
	{
		if (nNdINDEX == 1)
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_ND;
			pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_BR = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
			pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
		}
		else
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_ND;
			pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_BR = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
			pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
		}
	}
	//GENERATEUNITBR
	else if (pSwitch->m_str_psrtype == "GENERATEUNIT" || pSwitch->m_str_psrtype == "DG" || pSwitch->m_str_psrtype == "ENERGYSOURCEEQ")
	{
		if (nNdINDEX == 1)
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pSwitch->m_st_Kasim_GEN_Info.m_nGEN_ND;
			pSwitch->m_st_Kasim_GEN_Info.m_nGEN_BR = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
			pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
		}
		else
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pSwitch->m_st_Kasim_GEN_Info.m_nGEN_ND;
			pSwitch->m_st_Kasim_GEN_Info.m_nGEN_BR = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
			pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
		}
	}
	//TR
	else if (pSwitch->m_str_psrtype == "SVR")
	{
		CDND_Manager* pDNDMng = CDND_Manager::Instance();
		CKASIM_ND* pNDArray;
		for (int i = 0; i < pDNDMng->m_Array_KASIM_ND.GetSize(); i++)
		{
			pNDArray = pDNDMng->m_Array_KASIM_ND.GetAt(i);
			if (nNdINDEX == 1)
			{
				if (pNDArray->nND_ID == pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Fnd)
				{
					if (pNDArray->nND_FSVRID == 0 && pNDArray->nND_TSVRID ==0 )
					{
						pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Fnd;
						pSwitch->m_st_Kasim_SVR_Info.stKASIM_SVR_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
						pNDArray->nND_FBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
						pNDArray->nND_FSVRID = pSwitch->m_st_Kasim_SVR_Info.m_nSVRID;
						break;
					}
				}
				if (pNDArray->nND_ID == pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Tnd )
				{
					if (pNDArray->nND_FSVRID == 0 && pNDArray->nND_TSVRID == 0)
					{
						pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Tnd;
						pSwitch->m_st_Kasim_SVR_Info.stKASIM_SVR_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
						pNDArray->nND_FBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
						pNDArray->nND_FSVRID = pSwitch->m_st_Kasim_SVR_Info.m_nSVRID;
						break;
					}
				}
			}
			else
			{
				if (pNDArray->nND_ID == pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Fnd)
				{
					if (pNDArray->nND_FSVRID == 0 && pNDArray->nND_TSVRID ==0  )
					{
						pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Fnd;
						pSwitch->m_st_Kasim_SVR_Info.stKASIM_SVR_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
						pNDArray->nND_TBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
						pNDArray->nND_TSVRID = pSwitch->m_st_Kasim_SVR_Info.m_nSVRID;
						break;
					}
				}
				if (pNDArray->nND_ID == pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Tnd)
				{
					if (pNDArray->nND_FSVRID == 0 && pNDArray->nND_TSVRID == 0)
					{
						pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Tnd;
						pSwitch->m_st_Kasim_SVR_Info.stKASIM_SVR_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
						pNDArray->nND_TBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
						pNDArray->nND_TSVRID = pSwitch->m_st_Kasim_SVR_Info.m_nSVRID;
						break;
					}	
				}
			}
		}
	}
	else //CBSW 스위치? 연결정보????
	{
		CDND_Manager* pDNDMng = CDND_Manager::Instance();
		CKASIM_ND* pNDArray;
		if (nMultSW == 1) //멀티 스위치 일 경우?
		{
			for (int i = 0; i < pDNDMng->m_Array_KASIM_ND.GetSize(); i++)
			{
				pNDArray = pDNDMng->m_Array_KASIM_ND.GetAt(i);
				if (pNDArray->nND_MUSW == 0) continue; 
				if (pNDArray->nND_MUSW == 9999) continue;
				if (nNdINDEX == 1)
				{
					if (pNDArray->nND_ID == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd)
					{
						if (pNDArray->nND_FBRID == 0 && pNDArray->nND_TBRID == 0)
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd;
							pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
							pNDArray->nND_FBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
							break;
						}
					}
					if (pNDArray->nND_ID == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd)
					{
						if (pNDArray->nND_FBRID == 0 && pNDArray->nND_TBRID == 0)
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd;
							pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
							pNDArray->nND_FBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
							break;
						}
					}
				}
				else
				{
					if (pNDArray->nND_ID == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd)
					{
						if (pNDArray->nND_FBRID == 0 && pNDArray->nND_TBRID == 0)
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd;
							pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
							pNDArray->nND_TBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
							break;
						}
					}
					if (pNDArray->nND_ID == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd)
					{
						if (pNDArray->nND_FBRID == 0 && pNDArray->nND_TBRID == 0)
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd;
							pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
							pNDArray->nND_TBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
							break;
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < pDNDMng->m_Array_KASIM_ND.GetSize(); i++)
			{
				pNDArray = pDNDMng->m_Array_KASIM_ND.GetAt(i);
				if (nNdINDEX == 1)
				{
					if (pNDArray->nND_ID == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd)
					{
						if (pNDArray->nND_FBRID == 0 && pNDArray->nND_TBRID == 0)
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd;
							pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
							pNDArray->nND_FBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
							break;
						}
					}
					if (pNDArray->nND_ID == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd)
					{
						if (pNDArray->nND_FBRID == 0 && pNDArray->nND_TBRID == 0)
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd;
							pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
							pNDArray->nND_FBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
							break;
						}
					}
				}
				else
				{
					if (pNDArray->nND_ID == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd)
					{
						if (pNDArray->nND_FBRID == 0 && pNDArray->nND_TBRID == 0)
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd;
							pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
							pNDArray->nND_TBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
							break;
						}
					}
					if (pNDArray->nND_ID == pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd)
					{
						if (pNDArray->nND_FBRID == 0 && pNDArray->nND_TBRID == 0)
						{
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd;
							pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.Add(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
							pNDArray->nND_TBRID = pConnect->m_st_Kasim_LNsec_Info.m_nBRID;
							break;
						}
					}
				}
			}
		}
	}
}

void CSimulator_EditorView::STA_Inset(CDND_Connect *pConnect, CDND_Switch *pSwitch)
{
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_fnd"), pConnect->m_st_Kasim_LNsec_Info.m_nBRID, (int)pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_fgnd"), pConnect->m_st_Kasim_LNsec_Info.m_nBRID, (int)pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd);
	PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_tnd"), pConnect->m_st_Kasim_LNsec_Info.m_nBRID, (int)pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd);
	PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_tgnd"), pConnect->m_st_Kasim_LNsec_Info.m_nBRID, (int)pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd);
		   
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_GND"), pConnect->m_st_Kasim_LNsec_Info.m_nIJID, (int)pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd);
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_GND"), pConnect->m_st_Kasim_LNsec_Info.m_nLDID, (int)pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd);	   
}

void CSimulator_EditorView::SetLink_Connect_Object(CPoint pt)
{
	CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj;
	int nLinkPos = pConnect->GetLinkPos();
	if (nLinkPos == CONNECT_POS_FIRST	|| nLinkPos == CONNECT_POS_LAST)
	{
		CDND_Object*  pLinkObj = Get_DND_Object2Pt(pt, FALSE);
		if (pLinkObj)
		{
			if (pLinkObj->ObjectType_Get() == DND_OBJTYPE_BLOCK	|| pLinkObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
			{
				CDND_Object*  pBlock;
				if (pLinkObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
				{
					CDND_Manager* pDNDMng = CDND_Manager::Instance();
					pBlock = pDNDMng->GetDNDObject2Point(pt, pLinkObj, FALSE);

				}
				else
				{
					pBlock = pLinkObj;
				}
				////////////////////////// 개폐기의 상태도 확인 해야된다.
				////////////////////////// 다회로 1 link, 개폐기 2 link , 더미 4 link ?
				if (pConnect->m_strID_From != pBlock->Get_ID_Real() && pConnect->m_strID_To != pBlock->Get_ID_Real())
				{
					m_pSelect_DNDObj_Move = pBlock;
				}
			}
		}

	}
}

void CSimulator_EditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	CDND_Object* pDNDObj;
	CPoint ptReal = GetScreenPoint(point);
	CString strMsg;
	if (m_nMouseMode == MOUSE_MODE_OBJ_MOVE)
	{
		if (m_pSelect_DNDObj)
		{
			ptReal = m_pSelect_DNDObj->m_Point_Move;
			///////////////// 계통 연결?
			if (m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
			{
				//설비를 찾는다.
				SetLink_Connect(ptReal);
				//그설비에 점을 그린다.
			}
			m_pSelect_DNDObj->SetEdit_Move(ptReal);
			pFrm->SetSelect_DNDObject(m_pSelect_DNDObj->Get_ID_Real());
		}

		m_nMouseMode = MOUSE_MODE_NORMAL;
	}
	else if ( m_nMouseMode == MOUSE_MODE_OBJ_CANCEL)
	{
		pDNDObj = Get_DND_Object2Pt_Cancel(ptReal); //잡은 위치가?
		if (pDNDObj)
		{
			//설비 선택 선로 삭제 하는부분
			if (pDNDObj->ObjectType_Get() != DND_OBJTYPE_TEXT)
			{
				//설비 입력 해야 한다!!!!
				CDND_Switch* pDNDObj_Musw = (CDND_Switch*)pDNDObj;
				CDND_Switch* pMulti_M;
				for (int i = 0; i < pDNDObj_Musw->m_Array_Multi.GetSize(); i++)
				{
					pMulti_M = (CDND_Switch*)pDNDObj_Musw->m_Array_Multi.GetAt(i);

					if (pMulti_M == m_pSelect_DNDObj_Cancle_From)
					{
						pDNDObj = pMulti_M;
						break;
					}
					if (pMulti_M == m_pSelect_DNDObj_Cancle_TO)
					{
						pDNDObj = pMulti_M;
						break;
					}
				}
				//선로  연결 해지 
				if (pDNDObj == m_pSelect_DNDObj_Cancle_From)
				{
					//연결된 선로 삭제 해야 하는부분
					m_nMouseMode = MOUSE_MODE_NORMAL;				//
					CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj_Cancle;
					CDND_Switch* pSwitch = (CDND_Switch*)pDNDObj;

					strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_From->m_str_keyname);
					UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

					if (nRe == IDYES)
					{
						if (m_pSelect_DNDObj_Cancle_From->m_str_keyid == pConnect->m_strID_CEQ_From)
						{
							OnConnectmenuCancel_KASIM(pConnect, 1);//KASIM 삭제
							OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
							pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq.Format(_T(""));
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = 0;
							pConnect->m_strID_CEQ_From.Format(_T(""));
							pConnect->m_strID_From.Format(_T(""));
						}
						if (m_pSelect_DNDObj_Cancle_From->m_str_keyid == pConnect->m_strID_CEQ_To)
						{
							OnConnectmenuCancel_KASIM(pConnect, 2);//KASIM 삭제
							OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
							pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq.Format(_T(""));
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = 0;
							pConnect->m_strID_CEQ_To.Format(_T(""));
							pConnect->m_strID_To.Format(_T(""));
						}
					}
					m_pSelect_DNDObj_Cancle_From = NULL;
					m_pSelect_DNDObj_Cancle_TO = NULL;
					m_pSelect_DNDObj_Cancle = NULL;
					//pDNDObj = NULL;
					OnMouseMove(nFlags, point);
				}
				if (pDNDObj == m_pSelect_DNDObj_Cancle_TO)
				{
					m_nMouseMode = MOUSE_MODE_NORMAL;
					//
					CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj_Cancle;
					CDND_Switch* pSwitch = (CDND_Switch*)pDNDObj;

					strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_TO->m_str_keyname);
					UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

					if (nRe == IDYES)
					{
						if (m_pSelect_DNDObj_Cancle_TO->m_str_keyid == pConnect->m_strID_CEQ_From)
						{
							OnConnectmenuCancel_KASIM(pConnect, 1);//KASIM 삭제
							OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
							pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq.Format(_T(""));
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = 0;
							pConnect->m_strID_CEQ_From.Format(_T(""));
							pConnect->m_strID_From.Format(_T(""));
						}
						if (m_pSelect_DNDObj_Cancle_TO->m_str_keyid == pConnect->m_strID_CEQ_To)
						{
							OnConnectmenuCancel_KASIM(pConnect, 2);//KASIM 삭제
							OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
							pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq.Format(_T(""));
							pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = 0;
							pConnect->m_strID_CEQ_To.Format(_T(""));
							pConnect->m_strID_To.Format(_T(""));
						}
					}
					m_pSelect_DNDObj_Cancle_From = NULL;
					m_pSelect_DNDObj_Cancle_TO = NULL;
					m_pSelect_DNDObj_Cancle = NULL;
					//pDNDObj = NULL;
					OnMouseMove(nFlags, point);
				}

				//설비 삭제시
				if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT && m_pSelect_DNDObj_Cancle_From == NULL && m_pSelect_DNDObj_Cancle_TO == NULL)
				{
					if (m_pSelect_DNDObj_Cancle)
					{
						//설비 
						int nBRID = 0;
						int nNDID = 0;
						int nFNDID = 0, nTNDID = 0;
						CDND_Switch* pSwitch = (CDND_Switch*)m_pSelect_DNDObj_Cancle;
						CDND_Manager* pDNDMng = CDND_Manager::Instance();
						if (pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID != 0)
						{
							for (int i = 0; i < pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.GetSize(); i++)
							{
								nBRID = pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.GetAt(i);
								nFNDID = pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd;
								nTNDID = pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd;

								m_pSelect_DNDObj_Cancle_LNSEC = pDNDMng->GetDNDObject2_KASIM_ID(nBRID);
								if (m_pSelect_DNDObj_Cancle_LNSEC == pDNDObj)
								{
									CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj_Cancle_LNSEC;
									if (nFNDID == pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd)
									{
										strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_LNSEC->m_str_keyid);
										UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

										if (nRe == IDYES)
										{
											m_nMouseMode = MOUSE_MODE_NORMAL;

											OnConnectmenuCancel_KASIM(pConnect, 1);//KASIM 삭제
											OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); 
											pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq.Format(_T(""));
											pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = 0;
											pConnect->m_strID_CEQ_From.Format(_T(""));
											pConnect->m_strID_From.Format(_T(""));
										}
										m_pSelect_DNDObj_Cancle = NULL;
										m_pSelect_DNDObj_Cancle_LNSEC = NULL;
									}
									if (nFNDID == pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd)
									{
										strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_LNSEC->m_str_keyid);
										UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

										if (nRe == IDYES)
										{
											m_nMouseMode = MOUSE_MODE_NORMAL;

											OnConnectmenuCancel_KASIM(pConnect, 2);//KASIM 삭제
											OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
											pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq.Format(_T(""));
											pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = 0;
											pConnect->m_strID_CEQ_To.Format(_T(""));
											pConnect->m_strID_To.Format(_T(""));
										}
										m_pSelect_DNDObj_Cancle = NULL;
										m_pSelect_DNDObj_Cancle_LNSEC = NULL;
									}
									if (nTNDID == pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd)
									{
										strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_LNSEC->m_str_keyid);
										UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

										if (nRe == IDYES)
										{
											m_nMouseMode = MOUSE_MODE_NORMAL;

											OnConnectmenuCancel_KASIM(pConnect, 1);//KASIM 삭제
											OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
											pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq.Format(_T(""));
											pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = 0;
											pConnect->m_strID_CEQ_From.Format(_T(""));
											pConnect->m_strID_From.Format(_T(""));
										}
										m_pSelect_DNDObj_Cancle = NULL;
										m_pSelect_DNDObj_Cancle_LNSEC = NULL;
									}
									if (nTNDID == pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd)
									{
										strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_LNSEC->m_str_keyid);
										UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

										if (nRe == IDYES)
										{
											m_nMouseMode = MOUSE_MODE_NORMAL;

											OnConnectmenuCancel_KASIM(pConnect, 2);//KASIM 삭제
											OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
											pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq.Format(_T(""));
											pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = 0;
											pConnect->m_strID_CEQ_To.Format(_T(""));
											pConnect->m_strID_To.Format(_T(""));
										}
										m_pSelect_DNDObj_Cancle = NULL;
										m_pSelect_DNDObj_Cancle_LNSEC = NULL;
									}
									
								}
							}
							OnMouseMove(nFlags, point);
						}
						else if (pSwitch->m_st_Kasim_SVR_Info.m_nSVRID != 0)
						{
							for (int i = 0; i < pSwitch->m_st_Kasim_SVR_Info.stKASIM_SVR_BR_Arry.GetSize(); i++)
							{
								nBRID = pSwitch->m_st_Kasim_SVR_Info.stKASIM_SVR_BR_Arry.GetAt(i);
								nFNDID = pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Fnd;
								nTNDID = pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Tnd;

								m_pSelect_DNDObj_Cancle_LNSEC = pDNDMng->GetDNDObject2_KASIM_ID(nBRID);
								if (m_pSelect_DNDObj_Cancle_LNSEC == pDNDObj)
								{
									CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj_Cancle_LNSEC;
									if (nFNDID == pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd)
									{
										strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_LNSEC->m_str_keyid);
										UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

										if (nRe == IDYES)
										{
											m_nMouseMode = MOUSE_MODE_NORMAL;

											OnConnectmenuCancel_KASIM(pConnect, 1);//KASIM 삭제
											OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1);
											pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq.Format(_T(""));
											pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = 0;
											pConnect->m_strID_CEQ_From.Format(_T(""));
											pConnect->m_strID_From.Format(_T(""));
										}
										m_pSelect_DNDObj_Cancle = NULL;
										m_pSelect_DNDObj_Cancle_LNSEC = NULL;
									}
									if (nFNDID == pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd)
									{
										strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_LNSEC->m_str_keyid);
										UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

										if (nRe == IDYES)
										{
											m_nMouseMode = MOUSE_MODE_NORMAL;

											OnConnectmenuCancel_KASIM(pConnect, 2);//KASIM 삭제
											OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
											pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq.Format(_T(""));
											pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = 0;
											pConnect->m_strID_CEQ_To.Format(_T(""));
											pConnect->m_strID_To.Format(_T(""));
										}
										m_pSelect_DNDObj_Cancle = NULL;
										m_pSelect_DNDObj_Cancle_LNSEC = NULL;
									}
									if (nTNDID == pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd)
									{
										strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_LNSEC->m_str_keyid);
										UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

										if (nRe == IDYES)
										{
											m_nMouseMode = MOUSE_MODE_NORMAL;

											OnConnectmenuCancel_KASIM(pConnect, 1);//KASIM 삭제
											OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
											pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq.Format(_T(""));
											pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = 0;
											pConnect->m_strID_CEQ_From.Format(_T(""));
											pConnect->m_strID_From.Format(_T(""));
										}
										m_pSelect_DNDObj_Cancle = NULL;
										m_pSelect_DNDObj_Cancle_LNSEC = NULL;
									}
									if (nTNDID == pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd)
									{
										strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_LNSEC->m_str_keyid);
										UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

										if (nRe == IDYES)
										{
											m_nMouseMode = MOUSE_MODE_NORMAL;

											OnConnectmenuCancel_KASIM(pConnect, 2);//KASIM 삭제
											OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
											pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq.Format(_T(""));
											pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = 0;
											pConnect->m_strID_CEQ_To.Format(_T(""));
											pConnect->m_strID_To.Format(_T(""));
										}
										m_pSelect_DNDObj_Cancle = NULL;
										m_pSelect_DNDObj_Cancle_LNSEC = NULL;
									}
								}
							}
							OnMouseMove(nFlags, point);
						}
						else
						{
							for (int i = 0; i < pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.GetSize(); i++)
							{
								nNDID = 0;
								nBRID = pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.GetAt(i);
								nNDID = pSwitch->m_st_Kasim_ND_Info.m_nNDID;
								if (pSwitch->m_str_psrtype == "CONSUMER" && nNDID == 0)
								{
									nNDID = pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_ND;
								}
								if ((pSwitch->m_str_psrtype == "GENERATEUNIT" || pSwitch->m_str_psrtype == "DG" || pSwitch->m_str_psrtype == "ENERGYSOURCEEQ") && nNDID == 0 )
								{
									nNDID = pSwitch->m_st_Kasim_GEN_Info.m_nGEN_ND;
								}

								m_pSelect_DNDObj_Cancle_LNSEC = pDNDMng->GetDNDObject2_KASIM_ID(nBRID);

								if (m_pSelect_DNDObj_Cancle_LNSEC == pDNDObj)
								{
									CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj_Cancle_LNSEC;

									if (nNDID == pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd)
									{
										strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_LNSEC->m_str_keyid);
										UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);
										if (nRe == IDYES)
										{
											m_nMouseMode = MOUSE_MODE_NORMAL;

											OnConnectmenuCancel_KASIM(pConnect, 1);//KASIM 삭제
											OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
											pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq.Format(_T(""));
											pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = 0;
											pConnect->m_strID_CEQ_From.Format(_T(""));
											pConnect->m_strID_From.Format(_T(""));
										}
										m_pSelect_DNDObj_Cancle = NULL;
										m_pSelect_DNDObj_Cancle_LNSEC = NULL;
									}

									if (nNDID == pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd)
									{

										strMsg.Format(_T("%s 해지 하시겠습니까?"), m_pSelect_DNDObj_Cancle_LNSEC->m_str_keyid);
										UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);
										if (nRe == IDYES)
										{
											m_nMouseMode = MOUSE_MODE_NORMAL;

											OnConnectmenuCancel_KASIM(pConnect, 2);//KASIM 삭제
											OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 1); //BR연결 해지 부분이니까!!!
											pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq.Format(_T(""));
											pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = 0;
											pConnect->m_strID_CEQ_To.Format(_T(""));
											pConnect->m_strID_To.Format(_T(""));
										}
										m_pSelect_DNDObj_Cancle = NULL;
										m_pSelect_DNDObj_Cancle_LNSEC = NULL;
									}									
								}
							}
							OnMouseMove(nFlags, point);
						}
					}
				}
			}
		} 
	}
	else
	{
		pDNDObj = Get_DND_Object2Pt(ptReal);
		if (pDNDObj)
		{
			m_nMouseMode = MOUSE_MODE_SELECT;
			m_pSelect_DNDObj = pDNDObj;

			CString strName;
			if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
			{
				strName.Format(_T("%s"), pDNDObj->m_str_id);
			}
			else if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_TEXT)
			{
				strName.Format(_T("%s"), pDNDObj->m_str_id);
			}
			else
			{
				strName.Format(_T("%s"), pDNDObj->m_str_keyname);
				pDNDObj->m_Point_Move.x = int(pDNDObj->m_d_x);
				pDNDObj->m_Point_Move.y = int(pDNDObj->m_d_y);
			}

			pFrm->SetSelect_DNDObject(pDNDObj->Get_ID_Real());
		}
		else
		{
			//	m_pSelect_DNDObj = NULL;
			m_nMouseMode = MOUSE_MODE_SCREEN;
			m_pt_Move = GetScrollPosition();
			m_pt_Select = point;
		}
	}
		

	CScrollView::OnLButtonDown(nFlags, point);
}

void CSimulator_EditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT trackmouseevent;
	trackmouseevent.cbSize = sizeof(trackmouseevent);
	trackmouseevent.dwFlags = TME_HOVER | TME_LEAVE;
	trackmouseevent.hwndTrack = GetSafeHwnd();
	trackmouseevent.dwHoverTime = 0x00000001;
	_TrackMouseEvent(&trackmouseevent);	

	if (m_nMouseMode == MOUSE_MODE_SCREEN)
	{
		CPoint ppt(point), pppt;
		ppt -= m_pt_Select;
		pppt = m_pt_Move - ppt;
		BOOL bH, bV;
		CheckScrollBars(bH, bV);

		if (!bH)
			pppt.x = 0;

		if (!bV)
			pppt.y = 0;

		ScrollToPosition(pppt);
		RedrawWindow(FALSE);
	}
	else if (m_nMouseMode == MOUSE_MODE_OBJ_MOVE)
	{
		if (m_pSelect_DNDObj)
		{
			CPoint ptReal = GetScreenPoint(point);

			if (::GetKeyState(VK_SHIFT) & 0x8000)
			{
				CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj;
				ptReal = GetCurrentPoint(point, pConnect);
			}
			//선로가 여기에 올때?점표시?
			if (m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
			{
				m_pSelect_DNDObj_Move = NULL;
				SetLink_Connect_Object(ptReal);
			}
			//
			m_pSelect_DNDObj->m_Point_Move = ptReal;					   
			RedrawWindow();
		}
	}	
	CScrollView::OnMouseMove(nFlags, point);
}

void CSimulator_EditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_nMouseMode != MOUSE_MODE_OBJ_CANCEL)
	{
		m_nMouseMode = MOUSE_MODE_NORMAL;
	}
	//m_nMouseMode = MOUSE_MODE_NORMAL;
	RedrawWindow();
	CScrollView::OnLButtonUp(nFlags, point);
}

void CSimulator_EditorView::OnMouseLeave()
{
	if ( m_nMouseMode != MOUSE_MODE_OBJ_CANCEL)
	{
		m_nMouseMode = MOUSE_MODE_NORMAL;
	}
	
	RedrawWindow();

	CScrollView::OnMouseLeave();
}

BOOL CSimulator_EditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CDND_Manager* pDNDMng = CDND_Manager::Instance();
	CRect r;
	GetClientRect(r);
	

	if (pDNDMng->m_strFileName.IsEmpty())
		return TRUE;
	

	if (m_dZoomValue < 0.09)
	{
		//return TRUE;
	}
	double dZoomValue = m_dZoomValue;
	if (zDelta < 0)
	{
		m_dZoomValue -= 0.1;
		if (m_dZoomValue < 0.1)
		{
			m_dZoomValue =  r.Width() / pDNDMng->m_st_SVG_G.st_dWidth;
			if (m_dZoomValue < 0.03) // 20210824 축소 에러 때문에 
			{
				m_dZoomValue = 0.03;
			}
		}	
	}
	else
	{
		if (m_dZoomValue < 0.1)
		{
			m_dZoomValue = 0.0;
		}
		m_dZoomValue += 0.1;
		if (m_dZoomValue > 2.)
			m_dZoomValue = 2.;
	}
		
	CSize sizeTotal;
		
	ScreenToClient(&pt);
	
	CPoint ptScroll = GetScrollPosition();
	double x = 0, y = 0;

	x = ((ptScroll.x + r.CenterPoint().x) / dZoomValue);
	y = ((ptScroll.y + r.CenterPoint().y) / dZoomValue);

	x = ((ptScroll.x + pt.x) / dZoomValue);
	y = ((ptScroll.y + pt.y) / dZoomValue);
	
	double dx = x * m_dZoomValue - r.CenterPoint().x;
	double dy = y * m_dZoomValue - r.CenterPoint().y;

	sizeTotal.cx = pDNDMng->m_st_SVG_G.st_dWidth * m_dZoomValue;
	sizeTotal.cy = pDNDMng->m_st_SVG_G.st_dHeight * m_dZoomValue;
	SetScrollSizes(MM_TEXT, sizeTotal);

	SetScrollPos(SB_HORZ, dx);
	SetScrollPos(SB_VERT, dy);


	CPoint ptCenter = r.CenterPoint();
	
	ClientToScreen(&ptCenter);

	SetCursorPos(ptCenter.x, ptCenter.y);

	if(m_dZoomValue != dZoomValue)
		RedrawWindow();
	return TRUE;
}

void CSimulator_EditorView::Editor_View_Expansion()
{
	CRect rect;
	GetClientRect(&rect);
	CPoint pt;
	pt.x = rect.Width() / 2;
	pt.y = rect.Height() / 2;
	OnMouseWheel(TRUE, 120, pt);
}

void CSimulator_EditorView::Editor_View_Reduce()
{
	CRect rect;
	GetClientRect(&rect);
	CPoint pt;
	pt.x = rect.Width() / 2;
	pt.y = rect.Height() / 2;
	OnMouseWheel(TRUE, -120, pt);
}
void CSimulator_EditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_pt_Select = point;
	CDND_Object* pDNDObj = NULL;
	CPoint ptReal = GetScreenPoint(point);

	BOOL bSelect_New = TRUE;
	BOOL bShowMenu = FALSE;

	if (m_pSelect_DNDObj && m_nMapMode != MOUSE_MODE_OBJ_MOVE )
	{
		pDNDObj = m_pSelect_DNDObj->Select2Point(ptReal, m_pSelect_DNDObj);

		//다회로 설비는 메뉴를 넣지 않기?
	
		if (pDNDObj == m_pSelect_DNDObj)
		{
			bShowMenu = TRUE;
			bSelect_New = FALSE;
		}	
	}	
	if(bSelect_New)
	{
		if (m_nMouseMode == MOUSE_MODE_NORMAL)
			pDNDObj = Get_DND_Object2Pt(ptReal);


		if (pDNDObj)
		{
			m_nMouseMode = MOUSE_MODE_SELECT;


			CString strName;
			if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
			{
				bShowMenu = TRUE;
				m_pSelect_DNDObj = pDNDObj;
			}
			else if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_TEXT)
			{
				bShowMenu = TRUE;
				m_pSelect_DNDObj = pDNDObj;
			}
			else
			{
				bShowMenu = TRUE;
				if (m_pSelect_DNDObj)
				{
					if (m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK
						&& pDNDObj->ObjectType_Get() == DND_OBJTYPE_MULTI_M)
					{
						bShowMenu = TRUE;
					}
					else if (m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_MULTI_M
						&& pDNDObj->ObjectType_Get() == DND_OBJTYPE_MULTI_M)
					{
						m_pSelect_DNDObj = pDNDObj;
					}
					else if (m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_MULTI_M
						&& pDNDObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
					{
						if (((CDND_Switch*)m_pSelect_DNDObj)->m_pParent == pDNDObj)
						{
							bShowMenu = TRUE;
						}
						else
						{
							m_pSelect_DNDObj = pDNDObj;
						}
					}
					else
					{
						m_pSelect_DNDObj = pDNDObj;
					}
				}
				else
				{
					m_pSelect_DNDObj = pDNDObj;
				}

			}


			CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
			pFrm->SetSelect_DNDObject(pDNDObj->Get_ID_Real());
		}
		else
		{
				m_pSelect_DNDObj_Cancle_From = NULL;
				m_pSelect_DNDObj_Cancle_TO = NULL;
				m_pSelect_DNDObj_Cancle = NULL;
				//
				m_pSelect_DNDObj_Cancle_LNSEC = NULL;
				//
				m_nMouseMode = MOUSE_MODE_NORMAL;
				m_pSelect_DNDObj = NULL;
				bShowMenu = FALSE;
//			}

			RedrawWindow();

		}
	}

	if (m_pSelect_DNDObj && bShowMenu)
	{
		CMenu menu;
		menu.LoadMenu(IDR_POPUP_EDIT);
		CMenu* contextmenu;
		if (m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
		{
			contextmenu = menu.GetSubMenu(1);
			if (((CDND_Connect*)m_pSelect_DNDObj)->m_nSelect_Index > -1)
			{
				contextmenu->EnableMenuItem(ID_CONNECTMENU_SPLIT_INSERT, MF_DISABLED | MF_GRAYED);
				
			}
			else
			{
				contextmenu->EnableMenuItem(ID_CONNECTMENU_SPLIT_MOVE, MF_DISABLED | MF_GRAYED);
				contextmenu->EnableMenuItem(ID_CONNECTMENU_SPLIT_DEL, MF_DISABLED | MF_GRAYED);
			}
		}
		else
		{
			contextmenu = menu.GetSubMenu(0);
			
			//20210927 김종민 작업 다회로 개폐기는 선로 해지 메뉴를 비 활성화
			if (m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
				contextmenu->EnableMenuItem(ID_EDITMENU_CANCEL, MF_DISABLED | MF_GRAYED);

			//다회로 개폐기 각각 설버 메뉴 선택시 삭제 메뉴는 비활성화  
			if(m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_MULTI_M)
				contextmenu->EnableMenuItem(ID_EDITMENU_DEL, MF_DISABLED | MF_GRAYED);
		}	

		CPoint pt = point;
		ClientToScreen(&pt);
		contextmenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
	
	}
	else
	{
		CMenu menu;
		menu.LoadMenu(IDR_POPUP_EDIT);
		CMenu* contextmenu,AddMenu;

		contextmenu = menu.GetSubMenu(0);
		AddMenu.CreatePopupMenu();

		CSB_Manager* pSBMng = CSB_Manager::Instance();
		pSBMng->SetMenu(&AddMenu);
		contextmenu->InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR );
		contextmenu->InsertMenu(2, MF_BYPOSITION|MF_POPUP, (UINT)AddMenu.Detach(), _T("추가"));

		contextmenu->EnableMenuItem(ID_EDITMENU_MOVE, MF_DISABLED | MF_GRAYED);
		contextmenu->EnableMenuItem(ID_EDITMENU_DEL, MF_DISABLED | MF_GRAYED);


		///////////////////
		CPoint pt = point;
		ClientToScreen(&pt);
		contextmenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
	}


	CScrollView::OnRButtonUp(nFlags, point);
}

void CSimulator_EditorView::OnEditmenuMove()
{
	m_nMouseMode = MOUSE_MODE_OBJ_MOVE;
	RedrawWindow();
}

void CSimulator_EditorView::OnEditmenuDel()
{
	if (m_pSelect_DNDObj)
	{
		//KASIM 삭제
		OnEditmenuDel_KASIM(m_pSelect_DNDObj);
		//
		if (m_nMTRDELETE_NO == 0) //MTR 삭제 안할때 ~~!!
		{
			m_pSelect_DNDObj->SetEditType(DND_OBJ_EDIT_DELETE);
			m_pSelect_DNDObj = NULL;
			m_nMouseMode = MOUSE_MODE_NORMAL;
		}

		RedrawWindow();
	}
}

void CSimulator_EditorView::OnConnectmenuDel()
{
	if (m_pSelect_DNDObj)
	{
		CDND_Connect *pConnect = (CDND_Connect*)m_pSelect_DNDObj;
		if (pConnect->m_strID_CEQ_From != _T("") && pConnect->m_strID_CEQ_To != _T(""))
		{
			OnConnectmenuDel_KASIM(m_pSelect_DNDObj);
			//
			m_pSelect_DNDObj->SetEditType(DND_OBJ_EDIT_DELETE);
			m_pSelect_DNDObj = NULL;
			m_nMouseMode = MOUSE_MODE_NORMAL;
			RedrawWindow();
		}
		else
		{
			AfxMessageBox(_T("선로 연결된 설비가 없습니다.\n삭제시 NCP 오류로 인해 삭제할 수 없습니다."));
		}
		RedrawWindow();
	}
}

//삭제 KASIM
void CSimulator_EditorView::OnConnectmenuDel_KASIM(CDND_Object* pDNDObj)
{
	CDND_Connect *pConnect = (CDND_Connect*)pDNDObj;
	Del_KASIM_LNSEC(pConnect->m_st_Kasim_LNsec_Info.m_nLNSECID);
	Del_KASIM_BR(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
	Del_KASIM_GBR(pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
	Del_KASIM_IJ(pConnect->m_st_Kasim_LNsec_Info.m_nIJID);
	Del_KASIM_LD(pConnect->m_st_Kasim_LNsec_Info.m_nLDID);
	Del_KASIM_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd, pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd, 2, pConnect->m_st_Kasim_LNsec_Info.m_nBRID);
	//20211126
	OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 2);
	OnConnectmenuCancel_KASI_ND(pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd, pConnect->m_st_Kasim_LNsec_Info.m_nBRID, 2);
}

//삭제시
void CSimulator_EditorView::OnEditmenuDel_KASIM(CDND_Object* pDNDObj )
{
	CDND_Switch *pMulti;
	CDND_Switch *pSwitch;
	m_nMTRDELETE_NO = 0;
	//다회로 삭제시
	pSwitch = (CDND_Switch*)pDNDObj;
	if (pDNDObj->m_str_psrtype == "COMPSWITCH" || pDNDObj->m_str_psrtype == "TR")
	{
		if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
		{
			pMulti = (CDND_Switch*)pDNDObj;
			for (int k = 0; k < pSwitch->m_Array_Multi.GetSize(); k++)
			{
				pMulti = (CDND_Switch*)pSwitch->m_Array_Multi.GetAt(k);
				//삭제하는 부분!!!
				Del_KASIM_CBSW(pMulti->m_st_Kasim_CBSW_Info.m_nCBSWID);
				Del_KASIM_ND(pMulti->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd, pMulti->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd, 1, pMulti->m_st_Kasim_CBSW_Info.m_nCBSWID);
			}
		}
	}
	else if (pDNDObj->m_str_psrtype == "RECLOSER" )
	{
		Del_KASIM_CBSW(pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID);
		Del_KASIM_ND(pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd, pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd, 1, pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID);
		Del_KASIM_PRDE(pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE);
	}
	else if ( pDNDObj->m_str_psrtype == "CB")
	{
		Del_KASIM_DL(pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID);
		Del_KASIM_CBSW(pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID);
		Del_KASIM_ND(pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd, pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd, 1, pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID);
		Del_KASIM_PRDE(pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE);
	}
	//JUNCTION - CABLEPOLE
	else if (pDNDObj->m_str_psrtype == "JUNCTION" || pDNDObj->m_str_psrtype == "CABLEPOLE")
	{
		Del_KASIM_ND(pSwitch->m_st_Kasim_ND_Info.m_nNDID, pSwitch->m_st_Kasim_ND_Info.m_nNDID, 5, 0);
	}
	//CONSUMER
	else if (pDNDObj->m_str_psrtype == "CONSUMER")
	{
		Del_KASIM_HVCUS(pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUSID);
		Del_KASIM_ND(pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_ND, pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_ND, 4, pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUSID);
		Del_KASIM_IJ(pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_IJ);
		Del_KASIM_PRDE(pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_PRDE);
	}
	//GENERATEUNIT
	else if (pDNDObj->m_str_psrtype == "GENERATEUNIT" || pDNDObj->m_str_psrtype == "DG" || pDNDObj->m_str_psrtype == "ENERGYSOURCEEQ")
	{		
		Del_KASIM_GEN(pSwitch->m_st_Kasim_GEN_Info.m_nGENID);
		Del_KASIM_ND(pSwitch->m_st_Kasim_GEN_Info.m_nGEN_ND, pSwitch->m_st_Kasim_GEN_Info.m_nGEN_ND, 3, pSwitch->m_st_Kasim_GEN_Info.m_nGENID);
		Del_KASIM_IJ(pSwitch->m_st_Kasim_GEN_Info.m_nGEN_IJ);
		Del_KASIM_PRDE(pSwitch->m_st_Kasim_GEN_Info.m_nGEN_PRDE);
		//ESS?	
		Del_KASIM_ESS(pSwitch->m_st_Kasim_GEN_Info.m_nGEN_ESS);
	}
	//TR
	else if (pDNDObj->m_str_psrtype == "SVR" )
	{
		Del_KASIM_SVR(pSwitch->m_st_Kasim_SVR_Info.m_nSVRID);
		Del_KASIM_ND(pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Fnd, pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Tnd, 6, pSwitch->m_st_Kasim_SVR_Info.m_nSVR_BRID);
		Del_KASIM_BR(pSwitch->m_st_Kasim_SVR_Info.m_nSVR_BRID);
		Del_KASIM_GBR(pSwitch->m_st_Kasim_SVR_Info.m_nSVR_BRID);
	}//SUBS
	else if (pDNDObj->m_str_psrtype == "SUBSTATION") //삭제 변전소
	{
		int i = 0, nMTRSSID = 0;
		int k = 0, nDLID = 0;
		int  nMTR_Count = 0;
		int  nDL_Count = 0;
		int  nSSID = 0;
		nSSID = pSwitch->m_st_Kasim_SUBS_Info.m_nSUBSID;
		CString strMsg;
		int nCount_MTR_table = theAppDataMng->GetTableRealCount(_T("MTR_STA"));
		for (i = 1; i <= (int)nCount_MTR_table; i++)
		{
			nMTRSSID = GETVALUE(int, _T("MTR_STA"), _T("MTR_II_SS"), i);
			if (nMTRSSID == nSSID)
			{
				nMTR_Count++;

				int nCount_DL_table = theAppDataMng->GetTableRealCount(_T("DL_STA"));
				for (k = 1; k <= (int)nCount_DL_table; k++)
				{
					nDLID = GETVALUE(int, _T("DL_STA"), _T("DL_II_MTR"), k);
					if (nDLID == i)
					{
						nDL_Count++;
						AfxMessageBox(_T("연결된 DL있어 삭제 할수 없습니다."));
						break;
					}
				}
			}
		}
		if (nDL_Count ==0)
		{
			strMsg.Format(_T("현재 %d개의 MTR이 연결되어 있습니다. 삭제 하시겠습니까?"), nMTR_Count);
			UINT nRe = AfxMessageBox(strMsg, MB_YESNOCANCEL);

			if (nRe == IDYES)
			{

				Del_KASIM_GEN(pSwitch->m_st_Kasim_SUBS_Info.m_nGENID);
				Del_KASIM_SUBS(pSwitch->m_st_Kasim_SUBS_Info.m_nSUBSID);
				Del_KASIM_IJ(pSwitch->m_st_Kasim_SUBS_Info.m_nIJID);

				Del_KASIM_ND(pSwitch->m_st_Kasim_SUBS_Info.m_nNDID, pSwitch->m_st_Kasim_SUBS_Info.m_nNDID, 7, pSwitch->m_st_Kasim_SUBS_Info.m_nGENID);
				Del_KASIM_PRDE(pSwitch->m_st_Kasim_SUBS_Info.m_nPRDEID);

				//MTR삭제 !!
				int nCount_MTR_table = theAppDataMng->GetTableRealCount(_T("MTR_STA"));
				for (i = 1; i <= (int)nCount_MTR_table; i++)
				{
					nMTRSSID = GETVALUE(int, _T("MTR_STA"), _T("MTR_II_SS"), i);
					if (nMTRSSID == nSSID)
					{
						Del_KASIM_MTR(i);
					}
				}
			}
			else
			{
				m_nMTRDELETE_NO = 9999;
			}
		}
		else
		{
			m_nMTRDELETE_NO = 9999;
		}
	}
	else
	{
		Del_KASIM_CBSW(pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID);
		Del_KASIM_ND(pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd, pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd, 1, pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID);
	}
}

void CSimulator_EditorView::Del_KASIM_LNSEC(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//LNSEC_STA 삭제
	PUTVALUE(_T("LNSEC_STA"), _T("LNSEC_NM"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("LNSEC_STA"), _T("LNSEC_CEQID"), nID, (unsigned long long)_wtoll(stNULL));
	//PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_II_BR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_INNERPOLE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_FPOLE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_TPOLE"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_INNERSEC"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_PRIVAT"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_TYPE_ID"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_LENGTH"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_CONSTYPE"), nID, (int)0);
	//LNSEC_DYN_UIN
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_UIN"), _T("LNSEC_SW_FOR_CONST"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_UIN"), _T("LNSEC_HIS_NOTSRCH"), nID, (int)0);
	//LNSEC_DYN_NCPO
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_NCPO"), _T("LNSEC_DEAD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_NCPO"), _T("LNSEC_II_ISL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_NCPO"), _T("LNSEC_II_DL"), nID, (int)0);
	//LNSEC_DYN_RPFO
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PLOADMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PLOADMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PGENMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PGENMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PALOADMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PBLOADMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PCLOADMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PALOADMAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PBLOADMAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PCLOADMAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PARPFKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PBRPFKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PCRPFKV"), nID, (double)0);

}

void CSimulator_EditorView::Del_KASIM_BR(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//BR_STA
	PUTVALUE(_T("BR_STA"), _T("BR_NM"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_EQU"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_FND"), nID, (int)0);
	//PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_FND"), nID, (int)0); //이게 NCP 가 죽는 문제 때문에 삭제 하지 않음
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_TND"), nID, (int)0);
	//PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_TND"), nID, (int)0); ; //이게 NCP 가 죽는 문제 때문에 삭제 하지 않음
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSB"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERB"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_NORLM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_EMRLM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_GBR"), nID, (int)0);
	//PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_GBR"), nID, (int)0);; //이게 NCP 가 죽는 문제 때문에 삭제 하지 않음
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_DL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_DL"), nID, (int)0);
}

void CSimulator_EditorView::Del_KASIM_GBR(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//GBR_STA
	PUTVALUE(_T("GBR_STA"), _T("GBR_NM"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_EQU"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_SI_FGND"), nID, (double)0);
	//PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_FGND"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_SI_TGND"), nID, (double)0);
	//PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_TGND"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSB"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERB"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_HI_BR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_SI_EQUTY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_EQUTY"), nID, (int)0);
	//GBR_DYN_UIN
	PUTDOUBLE2VALUE(_T("GBR_DYN_UIN"), _T("GBR_MORFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_UIN"), _T("GBR_SCAFLAG"), nID, (int)0);	
	//GBR_DYN_UIN
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PA_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PB_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PC_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PN_C"), nID, (double)0);
	//GBR_DYN_NCPO
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_SI_FBS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_SI_TBS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_II_FBS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_II_TBS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_FBSSTAT"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_TBSSTAT"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_DEAD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG11"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB11"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG22"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB22"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG11"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB11"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG22"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB22"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG11"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB11"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG22"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB22"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG11"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB11"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG22"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB22"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_II_OUTCMP"), nID, (int)0);
	//GBR_DYN_RPFO
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMW12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMVAR12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMW21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMVAR21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMW12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMVAR12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMW21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMVAR21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMW12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMVAR12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMW21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMVAR21"), nID, (double)0);
	//GBR_DYN_VVOO
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMW12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMVAR12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMW21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMVAR21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMW12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMVAR12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMW21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMVAR21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMW12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMVAR12"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMW21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMVAR21"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_MVA"), nID, (double)0);
	PUTVALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFPS"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFMVA"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFMVAR"), nID, (double)0);
	PUTVALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOPS"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOMVA"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOMVAR"), nID, (double)0);
	//GBR_DYN_AV
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIONW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIORECV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIOLM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIOMVA"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIOPER"), nID, (double)0);
	//GBR_DYN_VVOAV
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOAV"), _T("GBR_VIONW"), nID, (double)0);
}

void CSimulator_EditorView::Del_KASIM_CBSW(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//CBSW_STA
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_NM"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_CEQID"), nID, (unsigned long long)_wtoll(stNULL));
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_TYPE"), nID, (int)3);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_RTUTYPE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_COMTYPE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_NORSTAT"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_RTUCODE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_PRDE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_FND"), nID, (int)0);
	//PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_FND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_TND"), nID, (int)0);
	//PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_TND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_FGND"), nID, (int)0);
	//PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_FGND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_TGND"), nID, (int)0);
	//PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_TGND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_II_DL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_SI_DL"), nID, (int)0);
	PUTVALUE(_T("CBSW_STA"), _T("CBSW_MULTISW_ID"), nID, (unsigned long long)_wtoll(stNULL));
	PUTDOUBLE2VALUE(_T("CBSW_STA"), _T("CBSW_MULTICIR_NUMBER"), nID, (int)0);
	//CBSW_DYN_UIN
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_MEAUSE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_MANF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_MANSTAT"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_DNRIMPO"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_SRCDIRECTION"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_PFSIGN"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_DIRREF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_UIN"), _T("CBSW_BASE_STATE"), nID, (int)0);
	//CBSW_DYN_MEA
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_ODSTAT"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_NWSTAT"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAKV_OLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAKV_OLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAKV_OLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAAMP"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAAMP_OLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAAMP"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAAMP_OLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAAMP"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAAMP_OLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAADIFF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PAMEAADIFF_OLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAADIFF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PBMEAADIFF_OLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAADIFF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_PCMEAADIFF_OLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_COMSTATSER"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_CONTSTAT"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_MEA"), _T("CBSW_DIRSET"), nID, (int)0);
	//CBSW_DYN_NCPO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_NCPO"), _T("CBSW_DEAD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_NCPO"), _T("CBSW_NCPISL"), nID, (int)0);
	//CBSW_DYN_RPFO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFAMP"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFAMP"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFAMP"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFADIFF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFADIFF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFADIFF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_3PRPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_3PRPFMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PARPFMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PBRPFMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PCRPFMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_RPFO"), _T("CBSW_PFDIREC"), nID, (int)0);
	//CBSW_DYN_DLEO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_3PDLEMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_3PDLEMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PADLEMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PADLEMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PBDLEMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PBDLEMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PCDLEMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_PCDLEMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_DIRINVFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_DLEO"), _T("CBSW_SRCDIRECTION"), nID, (int)0);
	//CBSW_DYN_STDLEO
	PUTDOUBLE2VALUE(_T("CBSW_DYN_STDLEO"), _T("CBSW_DERGENMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("CBSW_DYN_STDLEO"), _T("CBSW_DERRAMW"), nID, (double)0);
}

void CSimulator_EditorView::Del_KASIM_DL(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	int nDLID = 0;
	nDLID = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_DL"), nID);

	PUTVALUE(_T("DL_STA"), _T("DL_NM"), nDLID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("DL_STA"), _T("DL_DistributionLineID"), nDLID, (unsigned long long)_wtoll(stNULL));
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_II_OLM"), nDLID, (int)1);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_II_MTR"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_SI_MTR"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_II_BOF"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_SI_BOF"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_HI_IJ"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_HI_CBSW"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_HI_BR"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_STA"), _T("DL_II_CB"), nDLID, (int)0);
	//
	PUTDOUBLE2VALUE(_T("DL_DYN_UIN"), _T("DL_PROTECSEQ"), nDLID, (int)0);
	PUTDOUBLE2VALUE(_T("DL_DYN_UIN"), _T("DL_CVRFACTOR"), nDLID, (double)0);
	PUTDOUBLE2VALUE(_T("DL_DYN_UIN"), _T("DL_PEAKLIM"), nDLID, (double)0);
	PUTDOUBLE2VALUE(_T("DL_DYN_UIN"), _T("DL_OPRCAPACITY"), nDLID, (double)0);
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

void CSimulator_EditorView::Del_KASIM_GEN(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//GEN_STA
	PUTVALUE(_T("GEN_STA"), _T("GEN_NM"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("GEN_STA"), _T("GEN_CEQID"), nID, (unsigned long long)_wtoll(stNULL));
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_SI_ND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_ND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_SI_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_IJ"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_NAMKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MVARLMMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MVARLMMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_R"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_STX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_SSX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TYPE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_VOL_CLS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_CONND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_CONNDREP"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_CONTYPE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_NOOFP"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_PF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_EFF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_PFMINLAG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_PFMINLEAD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_HI_ESS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MEA"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TREXCL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_PRDE"), nID, (int)0); //2222222222
	//GEN_DYN_UIN
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_AVR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_TBSVL"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DEV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_VVOFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MVARCONMODE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_OUTQ"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PFVVOMINLAG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PFVVOMINLEAD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVMINS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMVUBREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMVLBREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMQVRATIO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEQMAX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEQMIN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV1"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV2"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV3"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV4"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_CAP"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_R"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_X"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_NGR_R"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_NGR_X"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_WDC"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MACH_TYPE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_SCA_EXCEPTION"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PDVRFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM1"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM2"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM3"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM4"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM5"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM6"), nID, (double)0);
	PUTVALUE(_T("GEN_DYN_UIN"), _T("GEN_MDL_TIME"), nID, (wchar_t*)stNULL.GetBuffer());
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
	//GEN_DYN_VVOO
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VREFOLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_PFREFOLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_QREFOLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_SI_DPDL"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_BASEKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVOVREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVOPFREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVOQREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVORCOMFLAG"), nID, (int)0);
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

void CSimulator_EditorView::Del_KASIM_ESS(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
}

void CSimulator_EditorView::Del_KASIM_HVCUS(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//CUNSUMER
	PUTVALUE(_T("HVCUS_STA"), _T("HVCUS_NM"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("HVCUS_STA"), _T("HVCUS_CEQID"), nID, (unsigned long long)_wtoll(stNULL));
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_II_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_SI_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_CON_KVA"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_ITR_KVA"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_ITR_PZ"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_II_PRDE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_ITR_WDC"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("HVCUS_STA"), _T("HVCUS_II_IJ"), nID, (int)0);		//2222222222
}

void CSimulator_EditorView::Del_KASIM_PRDE(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//PRDE_STA
	PUTVALUE(_T("PRDE_STA"), _T("PRDE_NM"), nID, (wchar_t*)stNULL.GetBuffer());
	//PRDE_DYN_UIN
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_Pickup_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_IIC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_Pickup_C"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_IIC"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_TYPE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_SET_GTYPE"), nID, (int)0);
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

void CSimulator_EditorView::Del_KASIM_IJ(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//IJ_STA
	PUTVALUE(_T("IJ_STA"), _T("IJ_NM"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_EQUTY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_EQUTY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_EQU"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_GND"), nID, (int)0);
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

void CSimulator_EditorView::Del_KASIM_LD(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//LD_STA
	PUTVALUE(_T("LD_STA"), _T("LD_NM"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_SI_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_IJ"), nID, (int)0);
	//LD_DYN_UIN
	PUTDOUBLE2VALUE(_T("LD_DYN_UIN"), _T("LD_DIV"), nID, (double)0);
}

void CSimulator_EditorView::Del_KASIM_ND(int nFID, int nTID, int nType, int nCSV_ID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	int nCSV_FND = 0, nCSV_TND;
	int nID = 0;
	if (nType == 1) //CBSW
	{
		if (!(nFID == 0 || nFID == 999999))
		{
			//FND			
			nCSV_FND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FCBSW"), nFID);
			nCSV_TND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TCBSW"), nFID);
			if (nCSV_ID == nCSV_FND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nFID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nFID, (int)0);
			}
			if (nCSV_ID == nCSV_TND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nFID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nFID, (int)0);
			}
			//FGND
			Del_KASIM_ND_2(nFID);

		}
		if (!(nTID == 0 || nTID == 999999))
		{
			nCSV_FND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FCBSW"), nTID);
			nCSV_TND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TCBSW"), nTID);
			if (nCSV_ID == nCSV_FND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nTID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nTID, (int)0);
			}
			if (nCSV_ID == nCSV_TND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nTID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nTID, (int)0);
			}
			Del_KASIM_ND_2(nTID);
		}
	}
	else if (nType == 2) //LNSEC
	{
		if (!(nFID == 0 || nFID == 999999))
		{
			nCSV_FND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FBR"), nFID);
			nCSV_TND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TBR"), nFID);
			if (nCSV_ID == nCSV_FND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nFID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nFID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nFID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nFID, (int)0);
			}
			if (nCSV_ID == nCSV_TND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nFID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nFID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nFID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nFID, (int)0);
			}
			Del_KASIM_ND_2(nFID);
		}
		if (!(nTID == 0 || nTID == 999999))
		{
			nCSV_FND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FBR"), nTID);
			nCSV_TND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TBR"), nTID);
			if (nCSV_ID == nCSV_FND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nTID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nTID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nTID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nTID, (int)0);
			}
			if (nCSV_ID == nCSV_TND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nTID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nTID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nTID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nTID, (int)0);
			}
			Del_KASIM_ND_2(nTID);
		}

	}
	else if (nType == 3) //GEN
	{
		if (!(nFID == 0 || nFID == 999999))
		{
			//FND	
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nFID, (int)0);
			//FGND
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nFID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nFID, (int)0);
			Del_KASIM_ND_2(nFID);
		}
		else if (!(nTID == 0 || nTID == 999999))
		{
			//TND	
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nTID, (int)0);
			//TGND
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nTID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nTID, (int)0);
			Del_KASIM_ND_2(nTID);
		}
	}
	else if (nType == 4) //HVCUS
	{
		if (!(nFID == 0 || nFID == 999999))
		{
			//FGND
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nFID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nFID, (int)0);
			Del_KASIM_ND_2(nFID);
		}
		else if (!(nTID == 0 || nTID == 999999))
		{
			//TGND
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nTID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nTID, (int)0);
			Del_KASIM_ND_2(nTID);
		}
	}
	else if (nType == 5) //
	{
		if (!(nFID == 0 || nFID == 999999)) {		nID = nFID;		 }
		else if (!(nTID == 0 || nTID == 999999)){	nID = nFID;		 }

		if (nID != 0)
		{
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nID, (wchar_t*)stNULL.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nID, (unsigned long long)_wtoll(stNULL));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nID, (unsigned long long)_wtoll(stNULL));
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nID, (int)0);
			//PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_GND"), nID, (int)0);
			//GND입력부분
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nID, (wchar_t*)stNULL.GetBuffer());
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nID, (int)0);

			Del_KASIM_ND_2(nID);
		}
	}
	else if (nType == 6) //SVR
	{
		if (!(nFID == 0 || nFID == 999999))
		{
			nCSV_FND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FBR"), nFID);
			nCSV_TND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TBR"), nFID);
			if (nCSV_ID == nCSV_FND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nFID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nFID, (int)0);
			}
			if (nCSV_ID == nCSV_TND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nFID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nFID, (int)0);
			}
			Del_KASIM_ND_2(nFID);
		}
		if (!(nTID == 0 || nTID == 999999))
		{
			nCSV_FND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FBR"), nTID);
			nCSV_TND = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TBR"), nTID);
			if (nCSV_ID == nCSV_FND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nTID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nTID, (int)0);
			}
			if (nCSV_ID == nCSV_TND)
			{
				PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nTID, (int)0);
				PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nTID, (int)0);
			}
			Del_KASIM_ND_2(nTID);
		}
	}
	else if (nType == 7) //GEN
	{
		//TND	
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nFID, (int)0);
		//TGND
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nFID, (int)0);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nFID, (int)0);
		Del_KASIM_ND_2(nFID);
	}
	else
	{

	}
}

void CSimulator_EditorView::Del_KASIM_ND_2(int nID)
{
	//ND_DYN_UIN
	PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nID, (int)0);
	//ND_DYN_NCPO
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_DL"), nID, (int)0);
	//PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_DL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_MTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_MTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_SS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_SS"), nID, (int)0);
	//GND_DYN_NCPO
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_SI_ISL "), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_II_ISL "), nID, (int)0);
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
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOPERHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOKVLO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOPERLO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOKVHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOPERHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOKVLO"), nID, (double)0);
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

void CSimulator_EditorView::Del_KASIM_SVR(int nID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//TR_STA
	PUTVALUE(_T("TR_STA"), _T("TR_NM"), nID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("TR_STA"), _T("TR_CEQID"), nID, (unsigned long long)_wtoll(stNULL));
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TYPE"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_BR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_FNORKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TNORKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TRMVA"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_CONTY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ONLTC"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_POSX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ZERX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMN"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPNOR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPSTEP"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMN"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMN"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPNOR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPSTEP"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_CONND"), nID, (int)0);
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
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_II_PFVM"), nID, (int)0);
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
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMN"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFSS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMN"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWSS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMX"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMN"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXSS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PDVRFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVH"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCH"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_LDCTYPE"), nID, (int)0);
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

void CSimulator_EditorView::Del_KASIM_SUBS(int nSSID)
{	
	CString stNULL;
	stNULL.Format(_T(""));

	//SS_STA
	PUTVALUE(_T("SS_STA"), _T("SS_NM"), nSSID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("SS_STA"), _T("SS_SUBSTATIONID"), nSSID, (unsigned long long)_wtoll(stNULL));
	PUTDOUBLE2VALUE(_T("SS_STA"), _T("SS_HI_MTR"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_STA"), _T("SS_HI_SNV"), nSSID, (int)0);
	PUTVALUE(_T("SS_STA"), _T("SS_CODE"), nSSID, (wchar_t*)stNULL.GetBuffer());
	PUTDOUBLE2VALUE(_T("SS_STA"), _T("SS_II_VGEN"), nSSID, (int)0);

	PUTDOUBLE2VALUE(_T("SS_DYN_UIN"), _T("SS_DNRFLAG"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_UIN"), _T("SS_TIEOUTKW"), nSSID, (double)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_UIN"), _T("SS_TIEINKW"), nSSID, (double)0);

	PUTDOUBLE2VALUE(_T("SS_DYN_NCPO"), _T("SS_STATCHG"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_NCPO"), _T("SS_HI_BS"), nSSID, (int)0);
	PUTDOUBLE2VALUE(_T("SS_DYN_NCPO"), _T("SS_HI_ND"), nSSID, (int)0);

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

void CSimulator_EditorView::Del_KASIM_MTR(int nMTRID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	int nID = 0, nNDID = 0, nBRID = 0, i = 0, nTR_MTRID=0;

	PUTVALUE(_T("MTR_STA"), _T("MTR_NM"), nMTRID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("MTR_STA"), _T("MTR_MAINTRID"), nMTRID, (unsigned long long)_wtoll(stNULL));
	PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_II_SS"), nMTRID, (int)0);
	PUTDOUBLE2VALUE(_T("MTR_STA"), _T("MTR_HI_TR"), nMTRID, (int)0);
	//TR_STA
	int nCount_TR_table = theAppDataMng->GetTableRealCount(_T("TR_STA"));
	for (i = 1; i <= (int)nCount_TR_table; i++)
	{
		nTR_MTRID = GETVALUE(int, _T("TR_STA"), _T("TR_II_MTR"), i);
		if (nTR_MTRID == nMTRID)
		{			
			nID = i;
			nNDID = GETVALUE(int, _T("TR_STA"), _T("TR_II_CONND"), nID);
			nBRID = GETVALUE(int, _T("TR_STA"), _T("TR_II_BR"), nID);

			PUTVALUE(_T("TR_STA"), _T("TR_NM"), nID, (wchar_t*)stNULL.GetBuffer());
			PUTVALUE(_T("TR_STA"), _T("TR_CEQID"), nID, (unsigned long long)_wtoll(stNULL));
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TYPE"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_BR"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_FNORKV"), nID, (double)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TNORKV"), nID, (double)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_TRMVA"), nID, (double)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_CONTY"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ONLTC"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_POSX"), nID, (double)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_ZERX"), nID, (double)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMX"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPMN"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPNOR"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PATAPSTEP"), nID, (double)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMX"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPMN"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PBTAPSTEP"), nID, (double)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMX"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPMN"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPNOR"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_PCTAPSTEP"), nID, (double)0);
			PUTDOUBLE2VALUE(_T("TR_STA"), _T("TR_II_CONND"), nID, (int)0);
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
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CON3P"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_II_PFVM"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_3CONMEAP"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMX"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFMN"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VREFSS"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMX"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWMN"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_VBWSS"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMX"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXMN"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_RXSS"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PDVRFLAG"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVH"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_PTRVL"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCH"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_CTRCL"), nID, (int)0);
			PUTDOUBLE2VALUE(_T("TR_DYN_UIN"), _T("TR_LDCTYPE"), nID, (int)0);

			//ND
			PUTVALUE(_T("ND_STA"), _T("ND_NM"), nNDID, (wchar_t*)stNULL.GetBuffer());
			PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nNDID, (unsigned long long)_wtoll(stNULL));
			PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nNDID, (unsigned long long)_wtoll(stNULL));
			//GND입력부분
			PUTVALUE(_T("GND_STA"), _T("GND_NM"), nNDID, (wchar_t*)stNULL.GetBuffer());
			//BR
			PUTVALUE(_T("br_sta"), _T("br_nm"), nBRID, (wchar_t*)stNULL.GetBuffer());
			PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_equ"), nBRID, (int)0);
			PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_gbr"), nBRID, (int)0);
			PUTDOUBLE2VALUE(_T("br_sta"), _T("br_ii_dl"), nBRID, (int)0);
			//GBR
			PUTVALUE(_T("gbr_sta"), _T("gbr_nm"), nBRID, (wchar_t*)stNULL.GetBuffer());
			PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_ii_equ"), nBRID, (int)0);
			PUTDOUBLE2VALUE(_T("gbr_sta"), _T("GBR_HI_BR"), nBRID, (int)0);
			PUTDOUBLE2VALUE(_T("gbr_sta"), _T("GBR_II_EQUTY"), nBRID, (int)0);

		}
	}



}

void CSimulator_EditorView::OnConnectmenuSplitMove()
{
	m_nMouseMode = MOUSE_MODE_OBJ_MOVE;
	RedrawWindow();

}

void CSimulator_EditorView::OnConnectmenuSplitDel()
{
	if (m_pSelect_DNDObj)
	{
		if (m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
		{
			CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj;
			pConnect->SetEdit_Split_Del();
		
			RedrawWindow();
		}
	}
}

void CSimulator_EditorView::OnConnectmenuSplitInsert()
{
	if (m_pSelect_DNDObj)
	{
		if (m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
		{
			CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj;
			pConnect->SetEdit_Split_Add();
			
			RedrawWindow();
		}
	}
}

void CSimulator_EditorView::OnEdit_Add_Symbol(UINT id)
{
	CDND_Manager* pDNDMng = CDND_Manager::Instance();

	CPoint ptReal = GetScreenPoint(m_pt_Select);
	m_pSelect_DNDObj = pDNDMng->Add_DND_Obj_Switch(ptReal,id);	

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->SetSelect_DNDObject(m_pSelect_DNDObj->Get_ID_Real());
	RedrawWindow();
}

void CSimulator_EditorView::OnEdit_Add_Connect()
{
	CDND_Manager* pDNDMng = CDND_Manager::Instance();

	CPoint ptReal = GetScreenPoint(m_pt_Select);
	m_pSelect_DNDObj = pDNDMng->Add_DND_Obj_Connect(ptReal);

	m_nMouseMode = MOUSE_MODE_OBJ_MOVE;

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->SetSelect_DNDObject(m_pSelect_DNDObj->Get_ID_Real());
	RedrawWindow();
}

void CSimulator_EditorView::OnEdit_Add_Text()
{
	CDND_Manager* pDNDMng = CDND_Manager::Instance();

	CPoint ptReal = GetScreenPoint(m_pt_Select);
	m_pSelect_DNDObj = pDNDMng->Add_DND_Obj_Text(ptReal);

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->SetSelect_DNDObject(m_pSelect_DNDObj->Get_ID_Real());
	RedrawWindow();
}

//찾기 
BOOL CSimulator_EditorView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam == 70) && (GetKeyState(VK_CONTROL) < 0)) //Ctrl + F -> 객체찾기
		{
			FindObject();
		}
		else if(pMsg->wParam == 13) //엔터키
		{
			MsgEnter();
		}
		else if (pMsg->wParam == 27) //엔터키
		{
			MsgEsc();
		}
	}

	m_ToolTip.RelayEvent(pMsg);
	return CView::PreTranslateMessage(pMsg);
}

void CSimulator_EditorView::InitTooltip()
{
	m_ToolTip.Create(this); //. 생성
	m_ToolTip.Hide();

	CMFCToolTipInfo																	param;
	param.m_bBalloonTooltip = TRUE;
	param.m_bDrawIcon = TRUE;
	param.m_bDrawDescription = TRUE;
	param.m_bRoundedCorners = TRUE;
	param.m_bBoldLabel = TRUE;
	param.m_bDrawSeparator = TRUE;
	param.m_bVislManagerTheme = FALSE;
	param.m_nMaxDescrWidth = 500;
	param.m_nGradientAngle = 45;
	param.m_clrFill = (COLORREF)RGB(21, 48, 85);
	param.m_clrFillGradient = (COLORREF)RGB(14, 19, 34);
	param.m_clrText = (COLORREF)RGB(153, 193, 225);
	param.m_clrBorder = (COLORREF)RGB(3, 25, 43);

	m_ToolTip.SetParams(&param);
}

void CSimulator_EditorView::SetToolTip(CString szMessage)
{
	m_ToolTip.Hide();
	m_ToolTip.AddTool(this, szMessage, NULL, 0);
	m_ToolTip.Show();
}

void CSimulator_EditorView::FindObject()
{
	if (m_pFindDlg)																return;

	m_pFindDlg = new CFindObjDlg(this);
	m_pFindDlg->Create();
}

void CSimulator_EditorView::MsgEnter() //엔터키 입력
{
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	if (m_pSelect_DNDObj->m_str_psrtype == "BREAKER")
	{
		pFrm->m_wndSetting_Single.m_TObject_KASIM_SW_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.m_TObject_KASIM_PRDE_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	else if (m_pSelect_DNDObj->m_str_psrtype == "RECLOSER" )
	{
		pFrm->m_wndSetting_Single.m_TObject_KASIM_SW_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.m_TObject_KASIM_PRDE_RECLOSER_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	else if ( m_pSelect_DNDObj->m_str_psrtype == "CB")
	{
		pFrm->m_wndSetting_Single.m_TObject_KASIM_CB_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.m_TObject_KASIM_PRDE_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	//JUNCTION - CABLEPOLE
	else if (m_pSelect_DNDObj->m_str_psrtype == "JUNCTION" || m_pSelect_DNDObj->m_str_psrtype == "CABLEPOLE")
	{
		pFrm->m_wndSetting_Single.m_TObject_KASIM_JUNCTION_Tap->OnBnClickedDndobjectKasimJunctionDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	//CONSUMER
	else if (m_pSelect_DNDObj->m_str_psrtype == "CONSUMER")
	{
		pFrm->m_wndSetting_Single.m_TObject_KASIM_CONSUMER_Tap->OnBnClickedDndobjectKasimConsumerDlgBtn1();
		pFrm->m_wndSetting_Single.m_TObject_KASIM_PRDE_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	//GENERATEUNIT
	else if (m_pSelect_DNDObj->m_str_psrtype == "GENERATEUNIT" || m_pSelect_DNDObj->m_str_psrtype == "DG" || m_pSelect_DNDObj->m_str_psrtype == "ENERGYSOURCEEQ")
	{
		pFrm->m_wndSetting_Single.m_TObject_KASIM_GENERATEUNIT_Tap->OnBnClickedDndobjectKasimGenDlgBtn1();
		pFrm->m_wndSetting_Single.m_TObject_KASIM_PRDE_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	//TR
	else if (m_pSelect_DNDObj->m_str_psrtype == "SVR")
	{
		pFrm->m_wndSetting_Single.m_TObject_KASIM_TR_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	//CONNECTLINE
	else if (m_pSelect_DNDObj->m_str_psrtype == "CONNECTLINE")
	{
		pFrm->m_wndSetting_Connect.m_TDND_KASIM_Tap->OnBnClickedDndConnectTapKasimDlgBtn1();
		pFrm->m_wndSetting_Connect.OnBnClickedDndConnectDlgCancel();
	}
	else if (m_pSelect_DNDObj->m_str_psrtype == "SUBSTATION")
	{
		pFrm->m_wndSetting_Single.m_TObject_KASIM_SUBS_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	else
	{
		pFrm->m_wndSetting_Single.m_TObject_KASIM_SW_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
}

void CSimulator_EditorView::MsgEsc() //엔터키 입력
{
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	if (m_pSelect_DNDObj->m_str_psrtype == "BREAKER")
	{
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	else if (m_pSelect_DNDObj->m_str_psrtype == "RECLOSER")
	{
//		pFrm->m_wndSetting_Single.m_TObject_KASIM_PRDE_RECLOSER_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	else if (m_pSelect_DNDObj->m_str_psrtype == "CB")
	{
//		pFrm->m_wndSetting_Single.m_TObject_KASIM_CB_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	//JUNCTION - CABLEPOLE
	else if (m_pSelect_DNDObj->m_str_psrtype == "JUNCTION" || m_pSelect_DNDObj->m_str_psrtype == "CABLEPOLE")
	{
//		pFrm->m_wndSetting_Single.m_TObject_KASIM_JUNCTION_Tap->OnBnClickedDndobjectKasimJunctionDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	//CONSUMER
	else if (m_pSelect_DNDObj->m_str_psrtype == "CONSUMER")
	{
//		pFrm->m_wndSetting_Single.m_TObject_KASIM_CONSUMER_Tap->OnBnClickedDndobjectKasimConsumerDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	//GENERATEUNIT
	else if (m_pSelect_DNDObj->m_str_psrtype == "GENERATEUNIT" || m_pSelect_DNDObj->m_str_psrtype == "DG" || m_pSelect_DNDObj->m_str_psrtype == "ENERGYSOURCEEQ")
	{
//		pFrm->m_wndSetting_Single.m_TObject_KASIM_GENERATEUNIT_Tap->OnBnClickedDndobjectKasimGenDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	//TR
	else if (m_pSelect_DNDObj->m_str_psrtype == "SVR")
	{
//		pFrm->m_wndSetting_Single.m_TObject_KASIM_TR_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	//CONNECTLINE
	else if (m_pSelect_DNDObj->m_str_psrtype == "CONNECTLINE")
	{
//		pFrm->m_wndSetting_Connect.m_TDND_KASIM_Tap->OnBnClickedDndConnectTapKasimDlgBtn1();
		pFrm->m_wndSetting_Connect.OnBnClickedDndConnectDlgCancel();
	}
	else if (m_pSelect_DNDObj->m_str_psrtype == "SUBSTATION")
	{
//		pFrm->m_wndSetting_Single.m_TObject_KASIM_SUBS_Tap->OnBnClickedDndConnectTapKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
	else
	{
//		pFrm->m_wndSetting_Single.m_TObject_KASIM_SW_Tap->OnBnClickedDndobjectKasimDlgBtn1();
		pFrm->m_wndSetting_Single.OnBnClickedDndobjectDlgBtn2();
	}
}

LRESULT CSimulator_EditorView::OnFindObjPosition(WPARAM wparam, LPARAM lparam)
{
	CString strID;

	CPoint Find_PT;
	CDND_Object* pDNDObj;

	if ((int)wparam < 0)
	{
		delete m_pFindDlg;
		m_pFindDlg = NULL;

		return TRUE;
	}
	else
	{
		strID.Format(_T("%s"), ((CString*)lparam)->GetBuffer());

		CDND_Manager* pDNDMng = CDND_Manager::Instance();
		pDNDObj = pDNDMng->GetDNDObject2ID(strID);

		if (pDNDObj)
		{
			if (m_dZoomValue <= 1)
			{
				m_dZoomValue = 1;
			}


			CRect r;
			GetClientRect(&r);

			CPoint pt;
			pt.x = r.Width() / 2;
			pt.y = r.Height() / 2;
			OnMouseWheel(TRUE, 0, pt);

			Find_PT.x = (pDNDObj->m_d_x * m_dZoomValue) - (r.Width()/2);
			Find_PT.y = (pDNDObj->m_d_y * m_dZoomValue) - (r.Height()/2);
			ScrollToPosition(Find_PT);

			RedrawWindow(FALSE);
			m_pSelect_DNDObj = pDNDObj;
		}
	}
	//
	return TRUE;
}

CPoint CSimulator_EditorView::GetCurrentPoint(CPoint point, CDND_Connect* pConnect)
{
	CPoint ptP0;
	double dPTTan = 0;
	double dDistance_1 = 0, dDistance_2 = 0;
	int nCheck = 0;

	CPoint ptPMain;
	CPoint ptP1, ptP1_0;
	CPoint ptP2, ptP2_0;
	CRealPoint *ptReal1 = NULL, *ptReal2 = NULL;
	CPoint ptReal;
	//
	//마지막 체크 
	if (pConnect->m_nSelect_Index == 0)
	{
		ptReal1 = pConnect->m_Array_Point.GetAt(pConnect->m_nSelect_Index + 1); //멈추웠던 선로 
		nCheck = 0;
	}
	else if (pConnect->m_Array_Point.GetSize() == pConnect->m_nSelect_Index + 1) // 끝점 이다
	{
		ptReal2 = pConnect->m_Array_Point.GetAt(pConnect->m_nSelect_Index - 1); //멈추웠던 선로 
	}
	else 
	{
		ptReal1 = pConnect->m_Array_Point.GetAt(pConnect->m_nSelect_Index + 1); //멈추웠던 선로 
		ptReal2 = pConnect->m_Array_Point.GetAt(pConnect->m_nSelect_Index - 1); //멈추웠던 선로 
		nCheck = 1;
	}

	if (nCheck == 0)
	{
		//각도 계산
		ptP1.x = double(ptReal1->x);		//멈추웠던 선로 x
		ptP1.y = double(ptReal1->y);		//멈추웠던 선로 y
		ptPMain = GetScreenPoint_Real(ptP1);   //좌표 변환 전체->화면

		//각도 계산기
		ptP0.x = point.x - ptPMain.x;
		ptP0.y = point.y - ptPMain.y;
		dPTTan = atan2(ptP0.y, ptP0.x) * 180 / 3.141592; // 각도 계산
	}
	else
	{
		//각도 계산 1
		ptP1.x = double(ptReal1->x);		//멈추웠던 선로 x
		ptP1.y = double(ptReal1->y);		//멈추웠던 선로 y
		ptP1_0 = GetScreenPoint_Real(ptP1);   //좌표 변환 전체->화면
		//각도 계산 2
		ptP2.x = double(ptReal2->x);		//멈추웠던 선로 x
		ptP2.y = double(ptReal2->y);		//멈추웠던 선로 y
		ptP2_0 = GetScreenPoint_Real(ptP2);  //좌표 변환 전체->화면

		dDistance_1 = sqrt(pow(ptP1_0.x - point.x, 2) + pow(ptP1_0.y - point.y, 2));
		dDistance_2 = sqrt(pow(ptP2_0.x - point.x, 2) + pow(ptP2_0.y - point.y, 2));
		//각도 계산기

		if (dDistance_1 < dDistance_2)
		{
			ptP0.x = point.x - ptP1_0.x;
			ptP0.y = point.y - ptP1_0.y;
			dPTTan = atan2(ptP0.y, ptP0.x) * 180 / 3.141592; // 각도 계산

			ptPMain = ptP1_0;
		}
		else
		{
			ptP0.x = point.x - ptP2_0.x;
			ptP0.y = point.y - ptP2_0.y;
			dPTTan = atan2(ptP0.y, ptP0.x) * 180 / 3.141592; // 각도 계산

			ptPMain = ptP2_0;
		}
	}
	
	//선로 잡기!!
	if ((dPTTan < 45 && dPTTan > -45) || (dPTTan > 135 || dPTTan < -135))
	{
		//X축
		point.x = point.x;
		point.y = ptPMain.y;
	}
	else if ((dPTTan > 45 && dPTTan < 135) || (dPTTan > -135 && dPTTan < -45))
	{
		//Y측 	
		point.x = ptPMain.x;
		point.y = point.y;
	}

	ptReal = GetScreenPoint(point);
	return ptReal;
}

void CSimulator_EditorView::OnConnectmenuCancel() //선로 연결 해지
{
	if (m_pSelect_DNDObj)
	{
		if (m_pSelect_DNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
		{
			m_pSelect_DNDObj_Cancle = m_pSelect_DNDObj;
			
			m_nMouseMode = MOUSE_MODE_OBJ_CANCEL;

			CDND_Connect* pConnect = (CDND_Connect*)m_pSelect_DNDObj;
			CDND_Manager* pDNDMng = CDND_Manager::Instance();
			m_pSelect_DNDObj_Cancle_From = pDNDMng->GetDNDObject2ID(pConnect->m_strID_From);
			m_pSelect_DNDObj_Cancle_TO = pDNDMng->GetDNDObject2ID(pConnect->m_strID_To);

			if (m_pSelect_DNDObj_Cancle_From == NULL && m_pSelect_DNDObj_Cancle_TO == NULL ) // 연결된 선로가 없을 경우
			{
				AfxMessageBox(_T("선로에 연결된 설비가 없습니다."));
				m_pSelect_DNDObj_Cancle = NULL;
				m_nMouseMode = MOUSE_MODE_NORMAL;
			}
		}
		RedrawWindow();
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CSimulator_EditorView::OnConnectmenuCancel_KASIM(CDND_Connect* pConnect, int nSelectND) //선로 연결 해지 KASIM 데이터 삭제 하는 부분 
{
	//BR설정	
	if (nSelectND == 1) //fnd 
	{
		PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_FND"), pConnect->m_st_Kasim_LNsec_Info.m_nBRID, (double)0);
		PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_FGND"), pConnect->m_st_Kasim_LNsec_Info.m_nBRID, (double)0);
	}
	else
	{
		PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_TND"), pConnect->m_st_Kasim_LNsec_Info.m_nBRID, (double)0);
		PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_TGND"), pConnect->m_st_Kasim_LNsec_Info.m_nBRID, (double)0);

	}
}

void CSimulator_EditorView::OnConnectmenuCancel_KASI_ND(int nNDID, int nDataID, int nINDEX) //선로 연결 해지 KASIM 데이터 삭제 하는 부분 
{
	//INDEX 1 = BR 2 CBSW

	CDND_Manager* pDNDMng = CDND_Manager::Instance();
	CKASIM_ND* pNDArray;
	for (int i = 0; i < pDNDMng->m_Array_KASIM_ND.GetSize(); i++)
	{
		pNDArray = pDNDMng->m_Array_KASIM_ND.GetAt(i);
		if (pNDArray->nND_ID == nNDID )
		{
			if (pNDArray->nND_FBRID == nDataID)
			{
				pNDArray->nND_FBRID = 0;
				pNDArray->nND_FSVRID = 0;
				break;
			}
			if (pNDArray->nND_TBRID == nDataID)
			{
				pNDArray->nND_TBRID = 0;
				pNDArray->nND_TSVRID= 0;
				break;
			}
		}
	}
}

void CSimulator_EditorView::OnEditmenuCancel() //설비 연결 해지 부분 
{
	int nBRID = 0;
	if (m_pSelect_DNDObj)
	{
		if (m_pSelect_DNDObj->ObjectType_Get() != DND_OBJTYPE_CONNECT && m_pSelect_DNDObj->ObjectType_Get() != DND_OBJTYPE_TEXT)
		{
			m_pSelect_DNDObj_Cancle = m_pSelect_DNDObj;

			m_nMouseMode = MOUSE_MODE_OBJ_CANCEL;
		}
		RedrawWindow();
	}
}

CString CSimulator_EditorView::MyPath()
{
	CString slmpath;
	WCHAR szDirve[256], szDir[2048];
	WCHAR programpath[2048];

	memset(szDir, 0x00, sizeof(szDir));
	memset(szDirve, 0x00, sizeof(szDirve));
	GetModuleFileName(0, programpath, 2048);
	/*	size_t sz;*/

	_wsplitpath_s(programpath, szDirve, 256, szDir, 2048, NULL, 0, NULL, 0);

	slmpath.Format(_T("%s%s"), szDirve, szDir);
	slmpath.Delete(slmpath.GetLength() - 1, 1);
	return slmpath;

}

void CSimulator_EditorView::PrintImage()
{
	//이름 경로 정하는 부분?
	CString						szRoute, strPath;
	szRoute.Format(_T("\\Editor.png"));
	strPath = (MyPath() + szRoute);

	Makepng(strPath);
}

BOOL CSimulator_EditorView::Makepng(CString szFileNm)
{

	DeleteFile(szFileNm);

	CClientDC dc(this); // device context for painting
	CDC											dcMem;
	CBitmap										bmp, *pOldBmp;
	CPoint										ptComp;
	int											nBottomMargin = 40;

	int nLeft, nTop, nRight, nBottom;

	nLeft = nTop = nRight = nBottom = 0;

	//20211008
	CRect rect_o;
	GetClientRect(&rect_o);

	CPoint pt = GetScreenPoint(rect_o.CenterPoint());

	rect_o.SetRect(pt.x, pt.y, pt.x, pt.y);
	rect_o.InflateRect(1920 + 960, 1080 + 540);	

	dcMem.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rect_o.Width(), rect_o.Height());
	pOldBmp = dcMem.SelectObject(&bmp);

	
	////
	dcMem.Rectangle(CRect(0, 0, rect_o.Width(), rect_o.Height() - (nBottomMargin + 10)));
	dcMem.FillSolidRect(CRect(0, 0, rect_o.Width(), rect_o.Height() - (nBottomMargin + 10)), RGB(0, 0, 0));

	dcMem.SetTextAlign(TA_LEFT);
	dcMem.SetTextColor(DEFALUT_TEXT_COLOR);
	dcMem.SetBkMode(TRANSPARENT);

	
	dcMem.SetWindowOrg(rect_o.left, rect_o.top);
	CFont																			font, *pOldFont;
	font.CreateFont(12, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, _T("굴림체"));
	pOldFont = dcMem.SelectObject(&font);

	
	CDND_Manager* pDNDMng = CDND_Manager::Instance();

	Graphics						graphics(dcMem.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
	pDNDMng->Draw_DND(graphics, rect_o.CenterPoint(), rect_o, 1, 1., 1.);

	dcMem.SelectObject(pOldFont);
	font.DeleteObject();

	CRect r(0, 0, rect_o.Width(), rect_o.Height());
	CImage				_image;
	CWnd*				pWndDesktop = GetDesktopWindow();
	CWindowDC			ScrDC(pWndDesktop);

	_image.Create(rect_o.Width(), rect_o.Height(), ScrDC.GetDeviceCaps(BITSPIXEL));
	CDC* _imgdc = CDC::FromHandle(_image.GetDC());
	_imgdc->Rectangle(r);
	rect_o.InflateRect(-10, -10);
	_imgdc->BitBlt(10, 10, rect_o.Width(), rect_o.Height(), &dcMem, 0,0, SRCCOPY);

	CRect rect;
	font.CreateFont(24, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("맑은 고딕"));
	pOldFont = _imgdc->SelectObject(&font);
	_imgdc->MoveTo(r.left, r.bottom - nBottomMargin);
	_imgdc->LineTo(r.right, r.bottom - nBottomMargin);

	rect.SetRect(r.left + 20, r.bottom - 35, r.right - 20, r.bottom);
	CString szData;
	szData.Format(_T("%s"), pDNDMng->m_strFileName);
//	szData.Format(_T("1234"));//, m_pNodeView->m_szLocNo, m_pNodeView->m_szLoc);
	_imgdc->DrawText(szData, rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);

	rect.SetRect(r.left + 20, r.bottom - 35, r.right - 20, r.bottom);
	_imgdc->DrawText(_T("시뮬레이터 계통도"), rect, DT_RIGHT | DT_VCENTER | DT_WORDBREAK);

	_imgdc->SelectObject(pOldFont);

	_image.ReleaseDC();

	_image.Save(szFileNm, Gdiplus::ImageFormatPNG);

	dcMem.SelectObject(pOldBmp);
	dcMem.DeleteDC();

	AfxMessageBox(_T("이미지 파일 생성 완료"));
	return TRUE;
}


