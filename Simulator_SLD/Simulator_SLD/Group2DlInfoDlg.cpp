// Group2DlInfoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "Group2DlInfoDlg.h"
#include "afxdialogex.h"


// CGroup2DlInfoDlg 대화 상자

IMPLEMENT_DYNAMIC(CGroup2DlInfoDlg, CDialog)

CGroup2DlInfoDlg::CGroup2DlInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GROUP2_DLINFO_DLG, pParent)
{

}

CGroup2DlInfoDlg::~CGroup2DlInfoDlg()
{
}

void CGroup2DlInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGroup2DlInfoDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGroup2DlInfoDlg 메시지 처리기
BOOL CGroup2DlInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_fontDef.CreateFont(17, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("맑은 고딕"));
	m_fontBold.CreateFont(21, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("맑은 고딕"));

	GetDlgItem(IDC_GROUP2_1_STC_LOAD)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP2_1_STC_MW)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP2_1_STC_GEN_CAPA)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP2_1_STC_LOSS)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP2_1_STC_VOLT)->SetFont(&m_fontBold);

	GetDlgItem(IDC_GROUP2_1_STC_LOAD_VAL)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP2_1_STC_LOAD_VAL2)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP2_1_STC_MW_VAL)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP2_1_STC_GEN_CAPA_VAL)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP2_1_STC_LOSS_VAL)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP2_1_STC_VOLT_VAL)->SetFont(&m_fontBold);
	GetDlgItem(IDC_GROUP2_1_STC_VOLT_VAL2)->SetFont(&m_fontBold);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CGroup2DlInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

HBRUSH CGroup2DlInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_GROUP2_1_STC_LOAD_VAL:
		case IDC_GROUP2_1_STC_LOAD_VAL2:
		case IDC_GROUP2_1_STC_MW_VAL:
		case IDC_GROUP2_1_STC_GEN_CAPA_VAL:
		case IDC_GROUP2_1_STC_LOSS_VAL:
		case IDC_GROUP2_1_STC_VOLT_VAL:
		case IDC_GROUP2_1_STC_VOLT_VAL2:
		{
			static CBrush s_brush(WND_BG_DIALOG_COLOR);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(DIALOG_VALUE_PEN_COLOR);
			pDC->SetBkColor(WND_BG_DIALOG_COLOR);
			return s_brush;
		}
		}

		static CBrush s_brush(WND_BG_DIALOG_COLOR);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(DIALOG_STATIC_PEN_COLOR);
		pDC->SetBkColor(WND_BG_DIALOG_COLOR);
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

void CGroup2DlInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect																	_rect, rect;
	GetClientRect(&_rect);
	dc.FillSolidRect(_rect, WND_BG_DIALOG_COLOR);
}
