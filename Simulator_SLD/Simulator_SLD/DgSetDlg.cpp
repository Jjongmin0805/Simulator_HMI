// DgSetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "DgSetDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDgSetDlg 대화 상자

IMPLEMENT_DYNAMIC(CDgSetDlg, CPNOCtrl_SkinFrame_POP_Dialog)

CDgSetDlg::CDgSetDlg(int nDgIdx, CWnd* pParent /*=nullptr*/)
	: CPNOCtrl_SkinFrame_POP_Dialog(IDD_DG_SET_DLG, pParent)
	, m_dGenItrCap(0)
	, m_dGenItrR(0)
	, m_dGenItrX(0)
	, m_dGenItrNgrR(0)
	, m_dGenItrNgrX(0)
	, m_nGenItrWdc(0)
	, m_dGenCap(0)
	, m_nGenMachType(0)
	, m_nGenPdvrFlag(0)
	, m_nGenMvarconmode(0)
	, m_dGenDeravmvubref(0)
	, m_dGenDeravmvlbref(0)
	, m_dGenQvcurvev1(0)
	, m_dGenQvcurvev2(0)
	, m_dGenQvcurvev3(0)
	, m_dGenQvcurvev4(0)
	, m_dIj3pmeamw(0)
	, m_dIj3pmeamvar(0)
	, m_nGenTrexcl(2)
	, m_dQvRatio(0)
{
	m_nGENIdx = nDgIdx;
	m_dQvRatio = 0;
}

CDgSetDlg::~CDgSetDlg()
{
}

void CDgSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dGenItrCap);
	DDX_Text(pDX, IDC_EDIT2, m_dGenItrR);
	DDX_Text(pDX, IDC_EDIT3, m_dGenItrX);
	DDX_Text(pDX, IDC_EDIT4, m_dGenItrNgrR);
	DDX_Text(pDX, IDC_EDIT5, m_dGenItrNgrX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nGenItrWdc);
	DDX_Text(pDX, IDC_EDIT6, m_dGenCap);
	DDX_CBIndex(pDX, IDC_COMBO2, m_nGenMachType);
	DDX_CBIndex(pDX, IDC_COMBO3, m_nGenPdvrFlag);
	DDX_CBIndex(pDX, IDC_COMBO4, m_nGenMvarconmode);
	DDX_Text(pDX, IDC_EDIT_GROUP1_MAX, m_dGenDeravmvubref);
	DDX_Text(pDX, IDC_EDIT_GROUP1_MIN, m_dGenDeravmvlbref);
	DDX_Text(pDX, IDC_EDIT_GROUP2_V1, m_dGenQvcurvev1);
	DDX_Text(pDX, IDC_EDIT_GROUP2_V2, m_dGenQvcurvev2);
	DDX_Text(pDX, IDC_EDIT_GROUP2_V3, m_dGenQvcurvev3);
	DDX_Text(pDX, IDC_EDIT_GROUP2_V4, m_dGenQvcurvev4);
	DDX_Text(pDX, IDC_EDIT7, m_dIj3pmeamw);
	DDX_Text(pDX, IDC_EDIT8, m_dIj3pmeamvar);
	DDX_CBIndex(pDX, IDC_COMBO5, m_nGenTrexcl);
	DDX_Text(pDX, IDC_EDIT9, m_dQvRatio);
}


BEGIN_MESSAGE_MAP(CDgSetDlg, CPNOCtrl_SkinFrame_POP_Dialog)
	ON_BN_CLICKED(IDOK, &CDgSetDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CDgSetDlg::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BTN_DG_CUST_SET, &CDgSetDlg::OnBnClickedBtnDgCustSet)
END_MESSAGE_MAP()


// CDgSetDlg 메시지 처리기


BOOL CDgSetDlg::OnInitDialog()
{
	CPNOCtrl_SkinFrame_POP_Dialog::OnInitDialog();

	m_dGenCap											= GETVALUE(double, _T("gen_sta"), _T("GEN_MWLMMX"), m_nGENIdx) * 1000;
	m_dGenItrCap										= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_ITR_CAP"), m_nGENIdx);
	m_dGenItrR											= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_ITR_R"), m_nGENIdx);
	m_dGenItrX											= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_ITR_X"), m_nGENIdx);
	m_dGenItrNgrR										= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_ITR_NGR_R"), m_nGENIdx);
	m_dGenItrNgrX										= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_ITR_NGR_X"), m_nGENIdx);
	m_nGenItrWdc										= GETVALUE(int, _T("gen_dyn_uin"), _T("GEN_ITR_WDC"), m_nGENIdx) - 1;
	m_nGenMachType										= GETVALUE(int, _T("gen_dyn_uin"), _T("GEN_MACH_TYPE"), m_nGENIdx) - 1;
	m_nGenPdvrFlag										= GETVALUE(int, _T("gen_dyn_uin"), _T("GEN_PDVRFLAG"), m_nGENIdx);
	m_nGenMvarconmode									= GETVALUE(int, _T("gen_dyn_uin"), _T("GEN_MVARCONMODE"), m_nGENIdx) - 4;
	m_dGenDeravmvubref									= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_DERAVMVUBREF"), m_nGENIdx);
	m_dGenDeravmvlbref									= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_DERAVMVLBREF"), m_nGENIdx);
	m_dGenQvcurvev1										= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_QVCURVEV1"), m_nGENIdx);
	m_dGenQvcurvev2										= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_QVCURVEV2"), m_nGENIdx);
	m_dGenQvcurvev3										= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_QVCURVEV3"), m_nGENIdx);
	m_dGenQvcurvev4										= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_QVCURVEV4"), m_nGENIdx);
	m_nGenTrexcl										= GETVALUE(int, _T("gen_sta"), _T("GEN_TREXCL"), m_nGENIdx) - 1;
	m_dQvRatio											= GETVALUE(double, _T("gen_dyn_uin"), _T("GEN_DERAVMQVRATIO"), m_nGENIdx);

	int													nIjIdx;
	nIjIdx												= GETVALUE(int, _T("gen_sta"), _T("GEN_II_IJ"), m_nGENIdx);

	m_dIj3pmeamw										= GETVALUE(double, _T("ij_dyn_mea"), _T("IJ_3PMEAMW"), nIjIdx) * 1000;
	m_dIj3pmeamvar										= GETVALUE(double, _T("ij_dyn_mea"), _T("IJ_3PMEAMVAR"), nIjIdx) * 1000;

	if (m_nGenItrWdc < 0)								m_nGenItrWdc = -1;
	if (m_nGenMachType < 0)								m_nGenMachType = -1;
	if (m_nGenPdvrFlag < 0)								m_nGenPdvrFlag = -1;
	if (m_nGenMvarconmode < 0)							m_nGenMvarconmode = -1;

	UpdateData(FALSE);

	OnCbnSelchangeCombo4();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDgSetDlg::OnCbnSelchangeCombo4()
{
	UpdateData();
	if (m_nGenMvarconmode == 0)
	{
		GetDlgItem(IDC_STC_GROUP1_MAX)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_GROUP1_MAX)->ShowWindow(TRUE);
		GetDlgItem(IDC_STC_GROUP1_MAX_UNIT)->ShowWindow(TRUE);
		GetDlgItem(IDC_STC_GROUP1_MIN)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_GROUP1_MIN)->ShowWindow(TRUE);
		GetDlgItem(IDC_STC_GROUP1_MIN_UNIT)->ShowWindow(TRUE);

		GetDlgItem(IDC_STC_GROUP2_V1)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROUP2_V1)->ShowWindow(FALSE);
		GetDlgItem(IDC_STC_GROUP2_V1_UNIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STC_GROUP2_V2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROUP2_V2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STC_GROUP2_V2_UNIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STC_GROUP2_V3)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROUP2_V3)->ShowWindow(FALSE);
		GetDlgItem(IDC_STC_GROUP2_V3_UNIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STC_GROUP2_V4)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROUP2_V4)->ShowWindow(FALSE);
		GetDlgItem(IDC_STC_GROUP2_V4_UNIT)->ShowWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STC_GROUP1_MAX)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROUP1_MAX)->ShowWindow(FALSE);
		GetDlgItem(IDC_STC_GROUP1_MAX_UNIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STC_GROUP1_MIN)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROUP1_MIN)->ShowWindow(FALSE);
		GetDlgItem(IDC_STC_GROUP1_MIN_UNIT)->ShowWindow(FALSE);

		GetDlgItem(IDC_STC_GROUP2_V1)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_GROUP2_V1)->ShowWindow(TRUE);
		GetDlgItem(IDC_STC_GROUP2_V1_UNIT)->ShowWindow(TRUE);
		GetDlgItem(IDC_STC_GROUP2_V2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_GROUP2_V2)->ShowWindow(TRUE);
		GetDlgItem(IDC_STC_GROUP2_V2_UNIT)->ShowWindow(TRUE);
		GetDlgItem(IDC_STC_GROUP2_V3)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_GROUP2_V3)->ShowWindow(TRUE);
		GetDlgItem(IDC_STC_GROUP2_V3_UNIT)->ShowWindow(TRUE);
		GetDlgItem(IDC_STC_GROUP2_V4)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_GROUP2_V4)->ShowWindow(TRUE);
		GetDlgItem(IDC_STC_GROUP2_V4_UNIT)->ShowWindow(TRUE);
	}
}

void CDgSetDlg::OnBnClickedOk()
{
	UpdateData();

	if (m_nGenItrWdc < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[결선방식]"));
		dlg.DoModal();
		return;
	}

	if (m_nGenMachType < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[발전기유형]"));
		dlg.DoModal();
		return;
	}

	if (m_nGenPdvrFlag < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[PDVR정정여부]"));
		dlg.DoModal();
		return;
	}

	if (m_nGenMvarconmode < 0)
	{
		CMessageDlg dlg(_T("경고"), MB_OK);
		dlg.SetMessage(_T("입력데이터를 확인하세요[분산전원제어방식]"));
		dlg.DoModal();
		return;
	}

// 	if (m_dIj3pmeamw < 0)
// 	{
// 		CMessageDlg dlg(_T("경고"), MB_OK);
// 		dlg.SetMessage(_T("입력데이터를 확인하세요[발전기출력-유효전력]"));
// 		dlg.DoModal();
// 		return;
// 	}
// 
// 	if (m_dIj3pmeamvar < 0)
// 	{
// 		CMessageDlg dlg(_T("경고"), MB_OK);
// 		dlg.SetMessage(_T("입력데이터를 확인하세요[발전기출력-무효전력]"));
// 		dlg.DoModal();
// 		return;
// 	}

	PUTVALUE(_T("gen_sta"), _T("GEN_MWLMMX"), m_nGENIdx, m_dGenCap/1000.);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_ITR_CAP"), m_nGENIdx, m_dGenItrCap);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_ITR_R"), m_nGENIdx, m_dGenItrR);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_ITR_X"), m_nGENIdx, m_dGenItrX);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_ITR_NGR_R"), m_nGENIdx, m_dGenItrNgrR);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_ITR_NGR_X"), m_nGENIdx, m_dGenItrNgrX);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_ITR_WDC"), m_nGENIdx, m_nGenItrWdc+1);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_MACH_TYPE"), m_nGENIdx, m_nGenMachType+1);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_PDVRFLAG"), m_nGENIdx, m_nGenPdvrFlag);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_MVARCONMODE"), m_nGENIdx, m_nGenMvarconmode+4);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_DERAVMVUBREF"), m_nGENIdx, m_dGenDeravmvubref);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_DERAVMVLBREF"), m_nGENIdx, m_dGenDeravmvlbref);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_QVCURVEV1"), m_nGENIdx, m_dGenQvcurvev1);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_QVCURVEV2"), m_nGENIdx, m_dGenQvcurvev2);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_QVCURVEV3"), m_nGENIdx, m_dGenQvcurvev3);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_QVCURVEV4"), m_nGENIdx, m_dGenQvcurvev4);
	PUTVALUE(_T("gen_sta"), _T("GEN_TREXCL"), m_nGENIdx, m_nGenTrexcl+1);
	PUTVALUE(_T("gen_dyn_uin"), _T("GEN_DERAVMQVRATIO"), m_nGENIdx, m_dQvRatio);

	int													nIjIdx;
	nIjIdx		= GETVALUE(int, _T("gen_sta"), _T("GEN_II_IJ"), m_nGENIdx);

	PUTVALUE(_T("ij_dyn_mea"), _T("IJ_3PMEAMW"), nIjIdx, m_dIj3pmeamw/1000.);
	PUTVALUE(_T("ij_dyn_mea"), _T("IJ_3PMEAMVAR"), nIjIdx, m_dIj3pmeamvar/1000.);

	((CMainFrame *)AfxGetApp()->GetMainWnd())->ShowDLInfo();

	CPNOCtrl_SkinFrame_POP_Dialog::OnOK();
}

void CDgSetDlg::OnBnClickedBtnDgCustSet()
{
	int nPRDEIdx;
	nPRDEIdx = GETVALUE(int, _T("gen_sta"), _T("gen_ii_prde"), m_nGENIdx);

	if (nPRDEIdx <= 0)
	{
		CString szData;
		CMessageDlg dlg(_T("오류"), MB_OK);
		szData.Format(_T("해당 분산전원에 PRDE 매핑정보가 없습니다\nKasim정보를 확인하세요.\nGEN_STA(Idx = %d) - [GEN_II_PRDE]"), m_nGENIdx);
		dlg.SetMessage(szData);
		dlg.DoModal();
		return;

	}

	CRelaySetDlg dlg(nPRDEIdx, TRUE);
	dlg.DoModal();
}
