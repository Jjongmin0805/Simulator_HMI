// CView_PCE_rst_EFIDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CView_PCE_rst_EFIDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "StyleDef.h"
#include "CView_Manager.h"
#include "Define_Ctrl.h"

// CView_PCE_rst_EFIDlg 대화 상자

IMPLEMENT_DYNAMIC(CView_PCE_rst_EFIDlg, CDialogEx)

CView_PCE_rst_EFIDlg::CView_PCE_rst_EFIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PCE_RST_EFI_DLG, pParent)
{
	m_nEndEdit = 0;
}

CView_PCE_rst_EFIDlg::~CView_PCE_rst_EFIDlg()
{
}

void CView_PCE_rst_EFIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CView_PCE_rst_EFIDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//ON_NOTIFY(NM_THEMECHANGED, IDC_PCE_RST_RC_DLG_EDIT1, &CView_PCE_rst_EFIDlg::OnNMThemeChangedPceRstEFIDlgEdit1)
	ON_BN_CLICKED(IDC_PCE_RST_EFI_DLG_BTN1, &CView_PCE_rst_EFIDlg::OnBnClickedPceRstEFIDlgBtn1)
	ON_WM_KEYDOWN()
	ON_EN_CHANGE(IDC_PCE_RST_EFI_DLG_EDIT9, &CView_PCE_rst_EFIDlg::OnEnChangePceRstEFIDlgEdit9)
	ON_EN_CHANGE(IDC_PCE_RST_EFI_DLG_EDIT20, &CView_PCE_rst_EFIDlg::OnEnChangePceRstEFIDlgEdit20)
END_MESSAGE_MAP()


// CView_PCE_rst_EFIDlg 메시지 처리기

BOOL CView_PCE_rst_EFIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CView_PCE_rst_EFIDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect																	_rect, rect;
	GetClientRect(&_rect);
	pDC->FillSolidRect(_rect, RGB(255, 255, 255));


	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	GetDlgItem(IDC_TITLE_PHASE_EFI)->GetWindowRect(&rect);
	//ClientToScreen(&rect);
	ScreenToClient(&rect);
	pViewMng->DrawArea_List(pDC, graphics, rect, FALSE);
	pViewMng->Draw_Split(pDC, graphics, rect, DRAW_SPLIT_MODE_TOP);
	pViewMng->Draw_Split(pDC, graphics, rect, DRAW_SPLIT_MODE_BOTTOM);

	GetDlgItem(IDC_TITLE_GROUND_EFI)->GetWindowRect(&rect);
	//ClientToScreen(&rect);
	ScreenToClient(&rect);
	pViewMng->DrawArea_List(pDC, graphics, rect, FALSE);
	pViewMng->Draw_Split(pDC, graphics, rect, DRAW_SPLIT_MODE_TOP);
	pViewMng->Draw_Split(pDC, graphics, rect, DRAW_SPLIT_MODE_BOTTOM);

	Draw_EditRound(pDC);

	return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}

void CView_PCE_rst_EFIDlg::Draw_EditRound(CDC* pDC)
{
	Graphics						graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	SolidBrush						_drawRectbrush(Color(255, 153, 153, 153));
	Gdiplus::Pen					_drawRectpen(&_drawRectbrush, 1.);
	Gdiplus::GraphicsPath gdiPath;
	CRect rect;

	for (int i = 0; i < 22; i++)
	{
		GetDlgItem(IDC_PCE_RST_EFI_DLG_EDIT1 + i)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.InflateRect(1, 1);
		rect.top -= 2;
		pViewMng->GetRoundRectPath(&gdiPath, rect.left, rect.top, rect.Width(), rect.Height(), 5);
		graphics.DrawPath(&_drawRectpen, &gdiPath);
	}


}

void CView_PCE_rst_EFIDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}


HBRUSH CView_PCE_rst_EFIDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_PCE_RST_EFI_DLG_STC3:
		case IDC_PCE_RST_EFI_DLG_STC4:
		case IDC_PCE_RST_EFI_DLG_STC5:
		case IDC_PCE_RST_EFI_DLG_STC6:
		case IDC_PCE_RST_EFI_DLG_STC7:
		case IDC_PCE_RST_EFI_DLG_STC8:
		case IDC_PCE_RST_EFI_DLG_STC9:
		case IDC_PCE_RST_EFI_DLG_STC10:
		case IDC_PCE_RST_EFI_DLG_STC11:
		case IDC_PCE_RST_EFI_DLG_STC12:
		case IDC_PCE_RST_EFI_DLG_STC13:
		case IDC_PCE_RST_EFI_DLG_STC14:
		case IDC_PCE_RST_EFI_DLG_STC15:
		case IDC_PCE_RST_EFI_DLG_STC16:
		case IDC_PCE_RST_EFI_DLG_STC17:
		case IDC_PCE_RST_EFI_DLG_STC18:
		case IDC_PCE_RST_EFI_DLG_STC19:
		case IDC_PCE_RST_EFI_DLG_STC20:
		case IDC_PCE_RST_EFI_DLG_STC21:
		case IDC_PCE_RST_EFI_DLG_STC22:
		case IDC_PCE_RST_EFI_DLG_STC23:
		case IDC_PCE_RST_EFI_DLG_STC24:
		case IDC_PCE_RST_EFI_DLG_STC25:
		{
			static CBrush s_brush(RGB(255, 255, 255));
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

void CView_PCE_rst_EFIDlg::OnEnChangePceRstEFIDlgEdit9()
{
	if (m_nEndEdit == 1)
		return;


	CString strValue;
	GetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT9, strValue);
	m_nEndEdit = 1;


	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT20, strValue);
	m_nEndEdit = 0;

}
void CView_PCE_rst_EFIDlg::OnEnChangePceRstEFIDlgEdit20()
{
	if (m_nEndEdit == 1)
		return;

	CString strValue;
	GetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT20, strValue);
	m_nEndEdit = 1;

	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT9, strValue);
	m_nEndEdit = 0;
}

void CView_PCE_rst_EFIDlg::Update_Data()
{
	int nPRDE_idx;
	int nTCCSET_OCRF_Idx;
	double dTms[2], dMrt[2];
	double dSet_Pickup;
	CString strData[11];
	double dRes_Tms[2], dRes_Mrt[2], dRes_Pickup;
	double dRes_Flt[2], dRes_LDC, dRes_TM[2], dRes_TM_REC[2];


	nPRDE_idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_PRDE"), m_nIndex);
	if (nPRDE_idx <= 0)
		return;

	nTCCSET_OCRF_Idx = GETVALUE(int, _T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nPRDE_idx);
	if (nTCCSET_OCRF_Idx <= 0)
		return;

	dSet_Pickup = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCR_Pickup_C"), nPRDE_idx);
	dTms[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRD_TMS"), nPRDE_idx);
	dMrt[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRD_MRT"), nPRDE_idx);
//	dTms[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRD_TMS"), nPRDE_idx);
//	dMrt[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCRD_MRT"), nPRDE_idx);

	dRes_Pickup = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_REC"), nPRDE_idx);
	dRes_Tms[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_D_TMS"), nPRDE_idx);
	dRes_Mrt[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_D_MRT"), nPRDE_idx);
//	dRes_Tms[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_D_TMS"), nPRDE_idx);
//	dRes_Mrt[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_D_MRT"), nPRDE_idx);

	dRes_Flt[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_MX_FLT_C"), nPRDE_idx);
	dRes_Flt[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCR_MN_FLT_C"), nPRDE_idx);
	dRes_LDC = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_MX_LD_C_PHA"), nPRDE_idx);
	dRes_TM[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCRD_TM"), nPRDE_idx);
//	dRes_TM[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCRD_TM"), nPRDE_idx);
	dRes_TM_REC[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCRD_TM_REC"), nPRDE_idx);
//	dRes_TM_REC[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCRD_TM_REC"), nPRDE_idx);


	strData[0].Format(_T("%.2lf"), dSet_Pickup);
	strData[1].Format(_T("%.2lf"), dTms[0]);
	strData[2].Format(_T("%.2lf"), dMrt[0]);

	strData[3].Format(_T("%.2lf"), dRes_Pickup);
	strData[4].Format(_T("%.2lf"), dRes_Tms[0]);
	strData[5].Format(_T("%.2lf"), dRes_Mrt[0]);

	strData[6].Format(_T("%.2lf"), dRes_Flt[0]);
	strData[7].Format(_T("%.2lf"), dRes_Flt[1]);
	strData[8].Format(_T("%.2lf"), dRes_LDC);
	strData[9].Format(_T("%.2lf"), dRes_TM[0]);
	strData[10].Format(_T("%.2lf"), dRes_TM_REC[0]);

	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT1, strData[0]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT3, strData[1]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT5, strData[2]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT2, strData[3]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT4, strData[4]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT6, strData[5]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT7, strData[6]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT8, strData[7]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT9, strData[8]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT10, strData[9]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT11, strData[10]);

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	dSet_Pickup = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGR_Pickup_C"), nPRDE_idx);
	dTms[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_TMS"), nPRDE_idx);
	dMrt[0] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_MRT"), nPRDE_idx);
//	dTms[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_TMS"), nPRDE_idx);
//	dMrt[1] = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_MRT"), nPRDE_idx);

	dRes_Pickup = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_REC"), nPRDE_idx);
	dRes_Tms[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_D_TMS"), nPRDE_idx);
	dRes_Mrt[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_D_MRT"), nPRDE_idx);
//	dRes_Tms[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_D_TMS"), nPRDE_idx);
//	dRes_Mrt[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_D_MRT"), nPRDE_idx);

	dRes_Flt[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_MX_FLT_C"), nPRDE_idx);
	dRes_Flt[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_MN_FLT_C"), nPRDE_idx);
	dRes_LDC = GETVALUE(double, _T("PRDE_DYN_UIN"), _T("PRDE_MX_LD_C_PHA"), nPRDE_idx);
	dRes_TM[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGRD_TM"), nPRDE_idx);
//	dRes_TM[1] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGRD_TM"), nPRDE_idx);
	dRes_TM_REC[0] = GETVALUE(double, _T("PRDE_DYN_PCEO"), _T("PRDE_OCGRD_TM_REC"), nPRDE_idx);

	strData[0].Format(_T("%.2lf"), dSet_Pickup);
	strData[1].Format(_T("%.2lf"), dTms[0]);
	strData[2].Format(_T("%.2lf"), dMrt[0]);

	strData[3].Format(_T("%.2lf"), dRes_Pickup);
	strData[4].Format(_T("%.2lf"), dRes_Tms[0]);
	strData[5].Format(_T("%.2lf"), dRes_Mrt[0]);

	strData[6].Format(_T("%.2lf"), dRes_Flt[0]);
	strData[7].Format(_T("%.2lf"), dRes_Flt[1]);
	strData[8].Format(_T("%.2lf"), dRes_LDC);
	strData[9].Format(_T("%.2lf"), dRes_TM[0]);
	strData[10].Format(_T("%.2lf"), dRes_TM_REC[0]);

	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT12, strData[0]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT14, strData[1]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT16, strData[2]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT13, strData[3]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT15, strData[4]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT17, strData[5]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT18, strData[6]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT19, strData[7]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT20, strData[8]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT21, strData[9]);
	SetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT22, strData[10]);


}

void CView_PCE_rst_EFIDlg::OnBnClickedPceRstEFIDlgBtn1()
{

	int nPRDE_idx = GETVALUE(int, _T("CBSW_STA"), _T("CBSW_II_PRDE"), m_nIndex);
	if (nPRDE_idx <= 0)
		return;

	CString strValue[4];
	double dValue[4];

	GetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT1, strValue[0]);
	GetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT3, strValue[1]);
	GetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT5, strValue[2]);
	GetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT9, strValue[3]);
	dValue[0] = _wtof(strValue[0]);
	dValue[1] = _wtof(strValue[1]);
	dValue[2] = _wtof(strValue[2]);
	dValue[3] = _wtof(strValue[3]);


	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_PICKUP_C"), nPRDE_idx, dValue[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_TMS"), nPRDE_idx, dValue[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_MRT"), nPRDE_idx, dValue[2]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_MX_LD_C_PHA"), nPRDE_idx, dValue[3]);

	GetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT12, strValue[0]);
	GetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT14, strValue[1]);
	GetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT16, strValue[2]);
	GetDlgItemText(IDC_PCE_RST_EFI_DLG_EDIT20, strValue[3]);

	dValue[0] = _wtof(strValue[0]);
	dValue[1] = _wtof(strValue[1]);
	dValue[2] = _wtof(strValue[2]);
	dValue[3] = _wtof(strValue[3]);

	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_PICKUP_C"), nPRDE_idx, dValue[0]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_TMS"), nPRDE_idx, dValue[1]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_MRT"), nPRDE_idx, dValue[2]);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_MX_LD_C_PHA"), nPRDE_idx, dValue[3]);


	m_pMsg_Wnd->SendMessage(WM_MSG_PCE_TAB, 0, 0);
}


void CView_PCE_rst_EFIDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN)
	{
		return;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CView_PCE_rst_EFIDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		if (pMsg->wParam == VK_RETURN)
			OnBnClickedPceRstEFIDlgBtn1();
		else
			Update_Data();

		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
