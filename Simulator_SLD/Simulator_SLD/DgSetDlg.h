#pragma once
#include "../Ctrl_Object/MessageDlg.h"
#include "../Ctrl_Object/PNOCtrl_SkinFrame_POP_Dialog.h"
#include "RelaySetDlg.h"

// CDgSetDlg 대화 상자

class CDgSetDlg : public CPNOCtrl_SkinFrame_POP_Dialog
{
	DECLARE_DYNAMIC(CDgSetDlg)

public:
	CDgSetDlg(int nDgIdx, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDgSetDlg();

	int														m_nGENIdx;//보호기기정보 인덱스
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DG_SET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	double m_dGenItrCap;
	double m_dGenItrR;
	double m_dGenItrX;
	double m_dGenItrNgrR;
	double m_dGenItrNgrX;
	int m_nGenItrWdc;
	double m_dGenCap;
	int m_nGenMachType;
	int m_nGenPdvrFlag;
	int m_nGenMvarconmode;
	double m_dGenDeravmvubref;
	double m_dGenDeravmvlbref;
	double m_dGenQvcurvev1;
	double m_dGenQvcurvev2;
	double m_dGenQvcurvev3;
	double m_dGenQvcurvev4;
	int m_nGenTrexcl;
	double m_dQvRatio;

	afx_msg void OnCbnSelchangeCombo4();
	double m_dIj3pmeamw;
	double m_dIj3pmeamvar;
	afx_msg void OnBnClickedBtnDgCustSet();
};
