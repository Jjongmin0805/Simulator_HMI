// OutputFileOptDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "OutputFileOptDlg.h"
#include "afxdialogex.h"


// COutputFileOptDlg 대화 상자

IMPLEMENT_DYNAMIC(COutputFileOptDlg, CPNOCtrl_SkinFrame_POP_Dialog)

COutputFileOptDlg::COutputFileOptDlg(CWnd* pParent /*=nullptr*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_OUTPUT_RATIOSET_DLG, pParent)
	, m_nRatioOpt(0)
	, m_bReverseColor(FALSE)
	, m_nFontRate(100)
{

}

COutputFileOptDlg::~COutputFileOptDlg()
{
}

void COutputFileOptDlg::DoDataExchange(CDataExchange* pDX)
{
	CPNOCtrl_SkinFrame_POP_Dialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RATIO_RADIO1, m_nRatioOpt);
	DDX_Check(pDX, IDC_CHK_COLOR, m_bReverseColor);
	DDX_Text(pDX, IDC_EDIT_FONT_SET, m_nFontRate);
	DDV_MinMaxInt(pDX, m_nFontRate, 50, 500);
}


BEGIN_MESSAGE_MAP(COutputFileOptDlg, CPNOCtrl_SkinFrame_POP_Dialog)
	ON_BN_CLICKED(IDC_BTN_PATH_OPT, &COutputFileOptDlg::OnBnClickedBtnPathOpt)
	ON_BN_CLICKED(IDOK, &COutputFileOptDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// COutputFileOptDlg 메시지 처리기
BOOL COutputFileOptDlg::OnInitDialog()
{
	CPNOCtrl_SkinFrame_POP_Dialog::OnInitDialog();

	CPNOCtrl_SkinFrame_POP_Dialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_FILE_PATH, m_szPath);

	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_STC_IMAGERATIO);
	pWnd->SetFont(&m_FontBold);
	pWnd = GetDlgItem(IDC_STC_SAVEPATH);
	pWnd->SetFont(&m_FontBold);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COutputFileOptDlg::OnBnClickedBtnPathOpt()
{
	WCHAR szFilter[] = _T("Image|*.png| All Files(*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("png"), m_szPath, OFN_OVERWRITEPROMPT, szFilter);
	if (dlg.DoModal() != IDOK)	return;

	SetDlgItemText(IDC_EDIT_FILE_PATH, dlg.GetPathName());
}

void COutputFileOptDlg::OnBnClickedOk()
{
	UpdateData();
	GetDlgItemText(IDC_EDIT_FILE_PATH, m_szPath);

	CPNOCtrl_SkinFrame_POP_Dialog::OnOK();
}
