#pragma once


// CProgress_bar 대화 상자

class CProgress_bar : public CDialog
{
	DECLARE_DYNAMIC(CProgress_bar)

public:
	CProgress_bar(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CProgress_bar();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRESS_BAR_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nCount;

	CProgressCtrl m_ctrProgress;
	virtual BOOL OnInitDialog();

	void ADD_Progress();
};
