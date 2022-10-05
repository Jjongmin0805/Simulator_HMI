// FaultPosSetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "FaultPosSetDlg.h"
#include "afxdialogex.h"


// CFaultPosSetDlg 대화 상자

IMPLEMENT_DYNAMIC(CFaultPosSetDlg, CPNOCtrl_SkinFrame_POP_Dialog)

CFaultPosSetDlg::CFaultPosSetDlg(CWnd* pParent /*=nullptr*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_FAULT_POS_SET, pParent)
	, m_nOhms(0)
	, m_nFaultType(0)
	, m_bInFault(FALSE)
{

}

CFaultPosSetDlg::~CFaultPosSetDlg()
{
}

void CFaultPosSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nOhms);
	DDV_MinMaxInt(pDX, m_nOhms, 0, 1000);
	DDX_Radio(pDX, IDC_RADIO1, m_nFaultType);
	DDX_Check(pDX, IDC_CHECK_IN_FAULT, m_bInFault);
}


BEGIN_MESSAGE_MAP(CFaultPosSetDlg, CPNOCtrl_SkinFrame_POP_Dialog)
END_MESSAGE_MAP()


// CFaultPosSetDlg 메시지 처리기
