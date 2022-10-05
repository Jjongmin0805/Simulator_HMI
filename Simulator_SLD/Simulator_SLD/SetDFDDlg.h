#pragma once


// CSetDFDDlg 대화 상자

class CSetDFDDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetDFDDlg)

public:
	CSetDFDDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSetDFDDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DFD_SET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
