// MessageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MessageDlg.h"
#include "afxdialogex.h"


// CMessageDlg 대화 상자

IMPLEMENT_DYNAMIC(CMessageDlg, CPNOCtrl_SkinFrame_POP_Dialog)

CMessageDlg::CMessageDlg(CString szTitle, int nDlgMode, CWnd* pParent /*=NULL*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_MESSAGE_DLG, pParent)
{
	m_szTitle = szTitle;
	m_nMode = nDlgMode;
}

CMessageDlg::~CMessageDlg()
{
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageDlg, CPNOCtrl_SkinFrame_POP_Dialog)
	ON_BN_CLICKED(ID_OK, &CMessageDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_CANCEL, &CMessageDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMessageDlg 메시지 처리기
BOOL CMessageDlg::OnInitDialog()
{
	CPNOCtrl_SkinFrame_POP_Dialog::OnInitDialog();

	if (m_nMode == MB_OKCANCEL)
	{
		GetDlgItem(ID_OK)->SetWindowText(_T("확인"));
		GetDlgItem(ID_CANCEL)->SetWindowText(_T("취소"));
	}
	else if (m_nMode == MB_YESNO)
	{
		GetDlgItem(ID_OK)->SetWindowText(_T("예"));
		GetDlgItem(ID_CANCEL)->SetWindowText(_T("아니오"));
	}
	else
	{
		GetDlgItem(ID_OK)->ShowWindow(FALSE);
		GetDlgItem(ID_CANCEL)->SetWindowText(_T("닫기"));
	}

	SetWindowText(m_szTitle);
	GetDlgItem(IDC_STC_MSG)->SetWindowText(m_szMessage);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMessageDlg::OnBnClickedOk()
{
	CDialog::OnOK();
}

void CMessageDlg::OnBnClickedCancel()
{
	CDialog::OnCancel();
}
