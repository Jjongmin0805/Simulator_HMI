// VVMSetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "VVMSetDlg.h"
#include "afxdialogex.h"


// CVVMSetDlg 대화 상자

IMPLEMENT_DYNAMIC(CVVMSetDlg, CPNOCtrl_SkinFrame_POP_Dialog)

CVVMSetDlg::CVVMSetDlg(CWnd* pParent /*=nullptr*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_VVM_SET_DLG, pParent)
	, m_nVoltageLevel(0)
{

}

CVVMSetDlg::~CVVMSetDlg()
{
}

void CVVMSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_VVM_RADIO1, m_nVoltageLevel);
}


BEGIN_MESSAGE_MAP(CVVMSetDlg, CPNOCtrl_SkinFrame_POP_Dialog)
END_MESSAGE_MAP()


// CVVMSetDlg 메시지 처리기
