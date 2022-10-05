// ProgressDlg.cpp: 구현 파일
//
#include "pch.h"
#include "ProgressDlg.h"
#include "afxdialogex.h"


// CProgressDlg 대화 상자

IMPLEMENT_DYNAMIC(CProgressDlg, CPNOCtrl_SkinFrame_POP_Dialog)

CProgressDlg::CProgressDlg(CWnd* pParent /*=nullptr*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_PROGRESS_DLG, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, CG_IDC_PROGDLG_PROGRESS, m_Progress);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CPNOCtrl_SkinFrame_POP_Dialog)
	ON_NOTIFY(NM_CUSTOMDRAW, CG_IDC_PROGDLG_PROGRESS, &CProgressDlg::OnNMCustomdrawIdcProgdlgProgress)
END_MESSAGE_MAP()


// CProgressDlg 메시지 처리기
BOOL CProgressDlg::Create(CWnd *pParent)
{
	m_pParentWnd = CWnd::GetSafeOwner(pParent);

	BOOL bEnabled;
	bEnabled = m_pParentWnd->IsWindowEnabled();
	if ((m_pParentWnd != NULL) && (bEnabled))
	{
		m_pParentWnd->EnableWindow(FALSE);
		m_bParentDisabled = TRUE;
	}
	else
	{
		m_pParentWnd->EnableWindow(TRUE);
	}

	if (!CDialog::Create(IDD_PROGRESS_DLG, pParent))
	{
		ReEnableParent();
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CProgressDlg::DestroyWindow()
{
	ReEnableParent();
	return CPNOCtrl_SkinFrame_POP_Dialog::DestroyWindow();
}

BOOL CProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_szTitle);

	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_STC_PROG);
	pWnd->SetFont(&m_FontBold);

	CRect	rect;
	GetWindowRect(rect);

	int		x, y, l, height;
	x = GetSystemMetrics(SM_CXFULLSCREEN);
	y = GetSystemMetrics(SM_CYFULLSCREEN);

	l = (int)(rect.right - rect.left);
	height = (int)(rect.bottom - rect.top);
	MoveWindow((x - l) / 2, (y - height) / 2, rect.Width(), rect.Height());

	m_Progress.SetRange(m_nLower, m_nUpper);
	m_Progress.SetStep(m_nStep);
	m_Progress.SetPos(m_nLower);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CProgressDlg::SetRange(int nLower, int nUpper)
{
	m_nLower = nLower;
	m_nUpper = nUpper;
	m_Progress.SetRange32(nLower, nUpper);
}

void CProgressDlg::SetStatus(LPCTSTR lpszMessage)
{
	ASSERT(m_hWnd);

	CWnd *pWndStatus = GetDlgItem(IDC_STC_PROG);

	ASSERT(pWndStatus != NULL);
	pWndStatus->SetWindowText(lpszMessage);
}

int CProgressDlg::SetStep(int nStep)
{
	m_nStep = nStep;
	return m_Progress.SetStep(nStep);
}

int CProgressDlg::SetPos(int nPos)
{
	PumpMessages();
	return m_Progress.SetPos(nPos);
}

int CProgressDlg::StepIt()
{
	PumpMessages();
	return m_Progress.StepIt();
}

void CProgressDlg::PumpMessages()
{
	ASSERT(m_hWnd != NULL);

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (!IsDialogMessage(&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

CString CProgressDlg::UpdatePercent(int nNewPos)
{
	int nPercent;

	int nDivisor = m_nUpper - m_nLower;
	ASSERT(nDivisor > 0);

	int nDividend = (nNewPos - m_nLower);
	ASSERT(nDividend >= 0);

	nPercent = nDividend * 100 / nDivisor;

	if (nPercent != 100)
		nPercent %= 100;

	CString strBuf;
	strBuf.Format(_T("%d%%"), nPercent);

	return strBuf;
}

void CProgressDlg::ReEnableParent()
{
	if (m_bParentDisabled && (m_pParentWnd != NULL))
		m_pParentWnd->EnableWindow(TRUE);
	else
		m_pParentWnd->EnableWindow(FALSE);

	m_bParentDisabled = FALSE;
}

int CProgressDlg::OffsetPos(int nPos)
{
	PumpMessages();
	return m_Progress.OffsetPos(nPos);
}

void CProgressDlg::UpdateMessaage(CString szMsg)
{
	CWnd *pWnd = GetDlgItem(IDC_STC_PROG);
	pWnd->SetWindowText(szMsg);
}

void CProgressDlg::OnNMCustomdrawIdcProgdlgProgress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
