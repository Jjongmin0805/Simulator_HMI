// CLoadflow_Edit_Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "CLoadflow_Edit_Dlg.h"
#include "afxdialogex.h"
#include "Main_LoadFlow_Editor.h"

// CLoadflow_Edit_Dlg 대화 상자

IMPLEMENT_DYNAMIC(CLoadflow_Edit_Dlg, CDialogEx)

CLoadflow_Edit_Dlg::CLoadflow_Edit_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOADFLOW_EDIT_DLG, pParent)
{
	m_pLFEditor = NULL;
}

CLoadflow_Edit_Dlg::~CLoadflow_Edit_Dlg()
{
	if (m_pLFEditor)
	{
		delete m_pLFEditor;
		m_pLFEditor = NULL;
	}

}

void CLoadflow_Edit_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoadflow_Edit_Dlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CLoadflow_Edit_Dlg 메시지 처리기


BOOL CLoadflow_Edit_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect r(0,0,1850, 900);

	

	m_pLFEditor = new CMain_LoadFlow_Editor;
	if (!m_pLFEditor->Create(r, this))
	{
		TRACE0("DBViwer 화면창을 만들지 못했습니다.\n");
	}
	m_pLFEditor->SetFLData_Loading();
	
	m_pLFEditor->SetView();

	m_pLFEditor->ShowWindow(SW_SHOW);

	MoveWindow(r);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CLoadflow_Edit_Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect							rect(0, 0, 0, 0);
	GetClientRect(&rect);

	if (m_pLFEditor)
	{
		CRect						_viwerrect(rect);
		//rect.DeflateRect(CSize(10, 10));
		m_pLFEditor->MoveWindow(_viwerrect);
	}
}
