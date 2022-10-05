// CProgress_bar.cpp: 구현 파일
//

#include "pch.h"
#include "CProgress_bar.h"
#include "afxdialogex.h"
#include "Resource.h"


// CProgress_bar 대화 상자

IMPLEMENT_DYNAMIC(CProgress_bar, CDialog)

CProgress_bar::CProgress_bar(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PROGRESS_BAR_DLG, pParent)
{
	m_nCount = 0;
}

CProgress_bar::~CProgress_bar()
{
}

void CProgress_bar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrProgress);
}


BEGIN_MESSAGE_MAP(CProgress_bar, CDialog)
END_MESSAGE_MAP()


// CProgress_bar 메시지 처리기


BOOL CProgress_bar::OnInitDialog()
{
	CDialog::OnInitDialog();
	CWnd*															pWnd;
	pWnd = GetDlgItem(IDC_STATIC_DESC2);
	CRect															rect;
	GetDlgItem(IDC_STATIC_DESC2)->GetWindowRect(&rect);

	m_ctrProgress.SetRange(0, 20);	 //범위 0~200
	m_ctrProgress.SetPos(0);				 //0으로 초기화
	m_ctrProgress.SetStep(1);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.



	_wsetlocale(LC_ALL, _T("kor"));
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CProgress_bar::ADD_Progress()
{
	CString szStatic;
	szStatic.Format(L"계통도를 읽어오는중입니다.");
	SetDlgItemText(IDC_STATIC, szStatic);

	m_ctrProgress.StepIt();  //1
	CString szCount;
	int nCount = 0;
	m_nCount++;
	nCount = m_nCount * 5;
	szCount.Format(L"%d ％진행중입니다.", nCount);
	
	SetDlgItemText(IDC_STATIC_DESC2, szCount);
}