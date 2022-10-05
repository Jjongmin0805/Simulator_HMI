// SetDFDDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "SetDFDDlg.h"
#include "afxdialogex.h"


// CSetDFDDlg 대화 상자

IMPLEMENT_DYNAMIC(CSetDFDDlg, CDialog)

CSetDFDDlg::CSetDFDDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DFD_SET_DLG, pParent)
{

}

CSetDFDDlg::~CSetDFDDlg()
{
}

void CSetDFDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetDFDDlg, CDialog)
END_MESSAGE_MAP()


// CSetDFDDlg 메시지 처리기
