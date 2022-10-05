// CView_PCE_rst_RelayDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CView_PCE_rst_RelayDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "StyleDef.h"
#include "CView_Manager.h"
#include "Define_Ctrl.h"
#include "../DataManager/CDataManager.h"

// CView_PCE_rst_RelayDlg 대화 상자

IMPLEMENT_DYNAMIC(CView_PCE_rst_RelayDlg, CDialog)

CView_PCE_rst_RelayDlg::CView_PCE_rst_RelayDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PCE_RST_RELAY_DLG, pParent)
{
	m_bEdit = FALSE;
}

CView_PCE_rst_RelayDlg::~CView_PCE_rst_RelayDlg()
{
}

void CView_PCE_rst_RelayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CView_PCE_rst_RelayDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PCE_RST_RELAY_DLG_BTN1, &CView_PCE_rst_RelayDlg::OnBnClickedPceRstRelayDlgBtn1)
	ON_WM_KEYDOWN()
	ON_EN_KILLFOCUS(IDC_PCE_RST_RELAY_DLG_EDIT3, &CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit3)
	ON_EN_KILLFOCUS(IDC_PCE_RST_RELAY_DLG_EDIT7, &CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit7)
	ON_EN_KILLFOCUS(IDC_PCE_RST_RELAY_DLG_EDIT9, &CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit9)
	ON_EN_KILLFOCUS(IDC_PCE_RST_RELAY_DLG_EDIT19, &CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit19)
	ON_EN_KILLFOCUS(IDC_PCE_RST_RELAY_DLG_EDIT23, &CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit23)
	ON_EN_KILLFOCUS(IDC_PCE_RST_RELAY_DLG_EDIT25, &CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit25)
END_MESSAGE_MAP()


// CView_PCE_rst_RelayDlg 메시지 처리기


BOOL CView_PCE_rst_RelayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();




	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CView_PCE_rst_RelayDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect																	_rect, rect;
	GetClientRect(&_rect);
	pDC->FillSolidRect(_rect, RGB(255, 255, 255));


	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	GetDlgItem(IDC_TITLE_PHASE)->GetWindowRect(&rect);
	//ClientToScreen(&rect);
	ScreenToClient(&rect);
	pViewMng->DrawArea_List(pDC, graphics, rect,FALSE);
	pViewMng->Draw_Split(pDC, graphics, rect, DRAW_SPLIT_MODE_TOP);
	pViewMng->Draw_Split(pDC, graphics, rect, DRAW_SPLIT_MODE_BOTTOM);

	GetDlgItem(IDC_TITLE_GROUND)->GetWindowRect(&rect);
	//ClientToScreen(&rect);
	ScreenToClient(&rect);
	pViewMng->DrawArea_List(pDC, graphics, rect, FALSE);
	pViewMng->Draw_Split(pDC, graphics, rect, DRAW_SPLIT_MODE_TOP);
	pViewMng->Draw_Split(pDC, graphics, rect, DRAW_SPLIT_MODE_BOTTOM);

	Draw_EditRound( pDC);

	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

void CView_PCE_rst_RelayDlg::Draw_EditRound(CDC* pDC)
{
	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	SolidBrush						_drawRectbrush(Color(255, 153, 153, 153));
	Gdiplus::Pen					_drawRectpen(&_drawRectbrush, 1.);
	Gdiplus::GraphicsPath gdiPath;
	CRect rect;

	for (int i = 0; i < 36; i++)
	{
		GetDlgItem(IDC_PCE_RST_RELAY_DLG_EDIT1 +i)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.InflateRect(1, 1);
		rect.top -= 2;
		pViewMng->GetRoundRectPath(&gdiPath, rect.left, rect.top, rect.Width(), rect.Height(), 5);
		graphics.DrawPath(&_drawRectpen, &gdiPath);
	}
	

}


HBRUSH CView_PCE_rst_RelayDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_PCE_RST_RELAY_DLG_STC3:
		case IDC_PCE_RST_RELAY_DLG_STC4:
		case IDC_PCE_RST_RELAY_DLG_STC5:
		case IDC_PCE_RST_RELAY_DLG_STC6:
		case IDC_PCE_RST_RELAY_DLG_STC7:
		case IDC_PCE_RST_RELAY_DLG_STC8:
		case IDC_PCE_RST_RELAY_DLG_STC9:
		case IDC_PCE_RST_RELAY_DLG_STC10:
		case IDC_PCE_RST_RELAY_DLG_STC11:
		case IDC_PCE_RST_RELAY_DLG_STC12:
		case IDC_PCE_RST_RELAY_DLG_STC13:
		case IDC_PCE_RST_RELAY_DLG_STC14:
		case IDC_PCE_RST_RELAY_DLG_STC15:
		case IDC_PCE_RST_RELAY_DLG_STC16:
		case IDC_PCE_RST_RELAY_DLG_STC17:
		case IDC_PCE_RST_RELAY_DLG_STC18:
		case IDC_PCE_RST_RELAY_DLG_STC19:
		case IDC_PCE_RST_RELAY_DLG_STC20:
		case IDC_PCE_RST_RELAY_DLG_STC21:
		case IDC_PCE_RST_RELAY_DLG_STC22:
		case IDC_PCE_RST_RELAY_DLG_STC23:
		case IDC_PCE_RST_RELAY_DLG_STC24:
		case IDC_PCE_RST_RELAY_DLG_STC25:
		case IDC_PCE_RST_RELAY_DLG_STC26:
		case IDC_PCE_RST_RELAY_DLG_STC27:
		case IDC_PCE_RST_RELAY_DLG_STC28:
		case IDC_PCE_RST_RELAY_DLG_STC29:
		case IDC_PCE_RST_RELAY_DLG_STC30:
		case IDC_PCE_RST_RELAY_DLG_STC31:
		case IDC_PCE_RST_RELAY_DLG_STC32:
		case IDC_PCE_RST_RELAY_DLG_STC33:
		case IDC_PCE_RST_RELAY_DLG_STC34:
		case IDC_PCE_RST_RELAY_DLG_STC35:
		case IDC_PCE_RST_RELAY_DLG_STC36:
		case IDC_PCE_RST_RELAY_DLG_STC37:
		case IDC_PCE_RST_RELAY_DLG_STC38:
		case IDC_PCE_RST_RELAY_DLG_STC39:
		case IDC_PCE_RST_RELAY_DLG_STC40:
		{
			static CBrush s_brush(RGB( 255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(DIALOG_EDIT_READONLY_PEN_COLOR);
			pDC->SetBkColor(RGB(255, 255, 255));
			return s_brush;
		}
		}

		static CBrush s_brush(RGB(238, 247, 240));
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(DIALOG_EDIT_READONLY_PEN_COLOR);
		pDC->SetBkColor(RGB(238, 247, 240));
		return s_brush;
	}
	else if (nCtlColor == CTLCOLOR_EDIT)
	{
		static CBrush s_brush(DIALOG_EDIT_DEFAULT_COLOR);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(DIALOG_EDIT_DEFAULT_PEN_COLOR);
		pDC->SetBkColor(DIALOG_EDIT_DEFAULT_COLOR);
		return s_brush;
	}

	

	return hbr;
}


void CView_PCE_rst_RelayDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

	


}


void CView_PCE_rst_RelayDlg::Update_Data()
{
	////////////////////// 210914
	////////////////////// 기기 형식 밑 커브 명 추가
	////////////////////// 범위 설정
	int nPRDE_idx;
	int nCTR;
	int nTCCSET_OCRF_Idx;
	double dTms, dMrt;
	double dSet_Pickup[2];
	double dRecMx, dRecMn, dRec;
	double dTMS_RecMx , dTMS_F;
	double dIIC_RecMn, dIIC_Rec;
	double dFlt_Mx, dFlt_Mn,dTm;
	int nDelay;
	 

	CString strData[17];

	if (m_nEquipType == PCE_STUDY_EQUIP_RELAY)
	{
		nPRDE_idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_PRDE"), m_nIndex);
		if (nPRDE_idx <= 0)
			return;

		m_nMachine_OCR = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_II_MACHINE"), nPRDE_idx);
		m_nMachine_OCGR = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_II_MACHINE"), nPRDE_idx);

		nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nPRDE_idx);
		if (nTCCSET_OCRF_Idx <= 0)
			return;

		nCTR = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_CTR"), nPRDE_idx);
		dTms = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_TMS"), nPRDE_idx);
		dMrt = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_MRT"), nPRDE_idx);
		dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_Pickup_C"), nPRDE_idx) / nCTR;
		dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_IIC"), nPRDE_idx) / nCTR;

		dRecMx = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_RECMX"), nPRDE_idx) / nCTR;
		dRecMn = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_RECMN"), nPRDE_idx) / nCTR;
		dRec = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_REC"), nPRDE_idx) / nCTR;

		dTMS_RecMx = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_TMS_RECMX"), nPRDE_idx) ;
		dTMS_F = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_F_TMS"), nPRDE_idx);

		dIIC_RecMn = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_IIC_RECMN"), nPRDE_idx) / nCTR;
		dIIC_Rec = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_IIC_REC"), nPRDE_idx) / nCTR;

		dFlt_Mx = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_MX_FLT_C"), nPRDE_idx);
		dFlt_Mn = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_MN_FLT_C"), nPRDE_idx);
		dTm = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCRF_TM"), nPRDE_idx);
	
		nDelay = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_S_DELAY_TIME"), nPRDE_idx);
		
		strData[0] = CA2W(GETSTRING(("TCCSET_sta"), ("TCCSET_nm"), nTCCSET_OCRF_Idx)).m_psz;
		strData[16] = CA2W(GETSTRING(("PRDE_DYN_UIN"), ("PRDE_OCR_MACHINE_NM"), nPRDE_idx)).m_psz;

		strData[1].Format(_T("%.2lf"), dRecMx);
		strData[2].Format(_T("%.2lf"), dSet_Pickup[0]);
		strData[3].Format(_T("%.2lf"), dRecMn);
		strData[4].Format(_T("%.2lf"), dRec);

		strData[5].Format(_T("%.2lf"), dTMS_RecMx);
		strData[6].Format(_T("%.2lf"), dTms);
		strData[7].Format(_T("%.2lf"), dTMS_F);

		
		strData[8].Format(_T("%.2lf"), dSet_Pickup[1]);
		strData[9].Format(_T("%.2lf"), dIIC_RecMn);
		strData[10].Format(_T("%.2lf"), dIIC_Rec);

		strData[11].Format(_T("%d"), nDelay);
		strData[12].Format(_T("%d"), nCTR * 5);

		strData[13].Format(_T("%.2lf"), dFlt_Mx);
		strData[14].Format(_T("%.2lf"), dFlt_Mn);
		strData[15].Format(_T("%.2lf"), dTm);


		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT35, strData[0]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT1, strData[16]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT2, strData[1]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT3, strData[2]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT4, strData[3]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT5, strData[4]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT6, strData[5]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT7, strData[6]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT8, strData[7]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT9, strData[8]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT10, strData[9]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT11, strData[10]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT12, strData[11]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT13, strData[12]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT14, strData[13]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT15, strData[14]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT16, strData[15]);

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_II_TCCSET"), nPRDE_idx);
		nCTR = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_CTR"), nPRDE_idx);
		dTms = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_TMS"), nPRDE_idx);
		dMrt = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_MRT"), nPRDE_idx);
		dSet_Pickup[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_Pickup_C"), nPRDE_idx) / nCTR;
		dSet_Pickup[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_IIC"), nPRDE_idx) / nCTR;

		dRecMx = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_RECMX"), nPRDE_idx) / nCTR;
		dRecMn = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_RECMN"), nPRDE_idx) / nCTR;
		dRec = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_REC"), nPRDE_idx) / nCTR;

		dTMS_RecMx = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_TMS_RECMX"), nPRDE_idx);
		dTMS_F = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_F_TMS"), nPRDE_idx);

		dIIC_RecMn = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_IIC_RECMN"), nPRDE_idx) / nCTR;
		dIIC_Rec = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_IIC_REC"), nPRDE_idx) / nCTR;

		dFlt_Mx = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_MX_FLT_C"), nPRDE_idx);
		dFlt_Mn = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_MN_FLT_C"), nPRDE_idx);
		dTm = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGRF_TM"), nPRDE_idx);

		nDelay = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_S_DELAY_TIME"), nPRDE_idx);

		
		strData[0] = CA2W(GETSTRING(("TCCSET_sta"), ("TCCSET_nm"), nTCCSET_OCRF_Idx)).m_psz;
		strData[16] = CA2W(GETSTRING(("PRDE_DYN_UIN"), ("PRDE_OCGR_MACHINE_NM"), nPRDE_idx)).m_psz;

		strData[1].Format(_T("%.2lf"), dRecMx);
		strData[2].Format(_T("%.2lf"), dSet_Pickup[0]);
		strData[3].Format(_T("%.2lf"), dRecMn);
		strData[4].Format(_T("%.2lf"), dRec);

		strData[5].Format(_T("%.2lf"), dTMS_RecMx);
		strData[6].Format(_T("%.2lf"), dTms);
		strData[7].Format(_T("%.2lf"), dTMS_F);


		strData[8].Format(_T("%.2lf"), dSet_Pickup[1]);
		strData[9].Format(_T("%.2lf"), dIIC_RecMn);
		strData[10].Format(_T("%.2lf"), dIIC_Rec);

		strData[11].Format(_T("%d"), nDelay);
		strData[12].Format(_T("%d"), nCTR * 5);

		strData[13].Format(_T("%.2lf"), dFlt_Mx);
		strData[14].Format(_T("%.2lf"), dFlt_Mn);
		strData[15].Format(_T("%.2lf"), dTm);

		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT36, strData[0]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT17, strData[16]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT18, strData[1]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT19, strData[2]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT20, strData[3]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT21, strData[4]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT22, strData[5]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT23, strData[6]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT24, strData[7]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT25, strData[8]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT26, strData[9]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT27, strData[10]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT28, strData[11]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT29, strData[12]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT30, strData[13]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT31, strData[14]);
		SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT32, strData[15]);
		
	}
	m_bEdit = TRUE;
}

void CView_PCE_rst_RelayDlg::OnBnClickedPceRstRelayDlgBtn1()
{
	int nPRDE_idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_PRDE"), m_nIndex);
	if (nPRDE_idx <= 0)
		return;
	   	
	CString strValue[3];
	double dValue[3];

	//GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT13, strValue[0]);
	//dValue[0] = _wtof(strValue[0]) /5;
	//PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_CTR"), nPRDE_idx, (double)dValue[0]);

	//GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT29, strValue[0]);
	//dValue[0] = _wtof(strValue[0]) / 5;
	//PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_CTR"), nPRDE_idx, (double)dValue[0]);

	///////////////////////////////////////////////

	int nCTR = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_CTR"), nPRDE_idx);

	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT3, strValue[0]);
	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT7, strValue[1]);
	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT9, strValue[2]);
	dValue[0] = _wtof(strValue[0]) * nCTR;
	dValue[1] = _wtof(strValue[1]);
	dValue[2] = _wtof(strValue[2]) * nCTR;

	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_PICKUP_C"), nPRDE_idx, (double)dValue[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_TMS"), nPRDE_idx, (double)dValue[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_IIC"), nPRDE_idx, (double)dValue[2]);

	/*GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT5, strValue[0]); 
	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT8, strValue[1]);
	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT11, strValue[2]);
	dValue[0] = _wtof(strValue[0]) * nCTR;
	dValue[1] = _wtof(strValue[1]);
	dValue[2] = _wtof(strValue[2]) * nCTR;

	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_REC"), nPRDE_idx, (double)dValue[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_F_TMS"), nPRDE_idx, (double)dValue[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_IIC_REC"), nPRDE_idx, (double)dValue[2]);*/

	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT19, strValue[0]);
	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT23, strValue[1]);
	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT25, strValue[2]);
	dValue[0] = _wtof(strValue[0]) * nCTR;
	dValue[1] = _wtof(strValue[1]);
	dValue[2] = _wtof(strValue[2]) * nCTR;

	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_PICKUP_C"), nPRDE_idx, (double)dValue[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_TMS"), nPRDE_idx, (double)dValue[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_IIC"), nPRDE_idx, (double)dValue[2]);

	/*GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT21, strValue[0]);
	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT24, strValue[1]);
	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT27, strValue[2]);
	dValue[0] = _wtof(strValue[0]) * nCTR;
	dValue[1] = _wtof(strValue[1]);
	dValue[2] = _wtof(strValue[2]) * nCTR;

	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_REC"), nPRDE_idx, (double)dValue[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_F_TMS"), nPRDE_idx, (double)dValue[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_IIC_REC"), nPRDE_idx, (double)dValue[2]);*/

	//Update_Data();

	m_pMsg_Wnd->SendMessage(WM_MSG_PCE_TAB, 0, 0);
}


void CView_PCE_rst_RelayDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN)
	{
		return;
	}

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CView_PCE_rst_RelayDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		if (pMsg->wParam == VK_RETURN)
			OnBnClickedPceRstRelayDlgBtn1();
		else
			Update_Data();

		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit3()
{
	if (!m_bEdit || m_nMachine_OCR < 1)
		return;

	double dValue;
	CString strValue;

	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT3, strValue);
	dValue = _wtof(strValue);

	CDataManager* pDataMng = CDataManager::Instance();

	dValue = pDataMng->GetRelayTabValue(m_nMachine_OCR, RELAY_OG_TYPE_OCR, RELAY_FD_TYPE_DELAY, dValue);

	strValue.Format(_T("%.2lf"), dValue);

	m_bEdit = FALSE;
	SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT3, strValue);
	m_bEdit = TRUE;
}


void CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit7()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit9()
{
	if (!m_bEdit)
		return;

	double dValue;
	CString strValue;

	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT9, strValue);
	dValue = _wtof(strValue);

	CDataManager* pDataMng = CDataManager::Instance();

	dValue = pDataMng->GetRelayTabValue(m_nMachine_OCR, RELAY_OG_TYPE_OCR, RELAY_FD_TYPE_FAST, dValue);

	strValue.Format(_T("%.2lf"), dValue);

	m_bEdit = FALSE;
	SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT9, strValue);
	m_bEdit = TRUE;
}


void CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit19()
{
	if (!m_bEdit || m_nMachine_OCGR < 1)
		return;

	double dValue;
	CString strValue;

	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT19, strValue);
	dValue = _wtof(strValue);

	CDataManager* pDataMng = CDataManager::Instance();

	dValue = pDataMng->GetRelayTabValue(m_nMachine_OCGR, RELAY_OG_TYPE_OCGR, RELAY_FD_TYPE_DELAY, dValue);

	strValue.Format(_T("%.2lf"), dValue);

	m_bEdit = FALSE;
	SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT19, strValue);
	m_bEdit = TRUE;
}


void CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit23()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CView_PCE_rst_RelayDlg::OnEnChangePceRstRelayDlgEdit25()
{
	if (!m_bEdit || m_nMachine_OCGR < 1)
		return;

	double dValue;
	CString strValue;

	GetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT25, strValue);
	dValue = _wtof(strValue);

	CDataManager* pDataMng = CDataManager::Instance();

	dValue = pDataMng->GetRelayTabValue(m_nMachine_OCGR, RELAY_OG_TYPE_OCGR, RELAY_FD_TYPE_FAST, dValue);

	strValue.Format(_T("%.2lf"), dValue);

	m_bEdit = FALSE;
	SetDlgItemText(IDC_PCE_RST_RELAY_DLG_EDIT25, strValue);
	m_bEdit = TRUE;
}



void CView_PCE_rst_RelayDlg::OnEnKillfocusPceRstRelayDlgEdit3()
{
	int n = 0;
}
