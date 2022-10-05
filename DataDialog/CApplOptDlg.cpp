// CApplOptDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CApplOptDlg.h"
#include "afxdialogex.h"
#include "../DataManager/CDataManager.h"


// CApplOptDlg 대화 상자

IMPLEMENT_DYNAMIC(CApplOptDlg, CDialogEx)

CApplOptDlg::CApplOptDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_APPL_OPT_DLG, pParent)
{

}

CApplOptDlg::~CApplOptDlg()
{
}

void CApplOptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_APPL_OPT_DLG_PROP, m_ctrProp);
	DDX_Control(pDX, IDC_APPL_OPT_DLG_COMBO1, m_ctrCombo);
}


BEGIN_MESSAGE_MAP(CApplOptDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_APPL_OPT_DLG_COMBO1, &CApplOptDlg::OnCbnSelchangeApplOptDlgCombo1)
	ON_BN_CLICKED(IDOK, &CApplOptDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CApplOptDlg 메시지 처리기


BOOL CApplOptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect r;
	m_ctrProp.GetClientRect(&r);
	HDITEM item;
	item.cxy = r.Width() * 2 /3;
	item.mask = HDI_WIDTH;
	m_ctrProp.GetHeaderCtrl().SetItem(0, &HDITEM(item));
	
	m_ctrProp.SetVSDotNetLook();
	m_ctrProp.MarkModifiedProperties();
	
	m_ctrCombo.AddString(_T("NCP"));
	m_ctrCombo.AddString(_T("DLE"));
	m_ctrCombo.AddString(_T("RPF"));
	m_ctrCombo.AddString(_T("DNR"));
	m_ctrCombo.AddString(_T("SOP"));
	m_ctrCombo.AddString(_T("PDVR"));
	m_ctrCombo.AddString(_T("PCE"));
	/*m_ctrCombo.AddString(_T("SCA"));
	m_ctrCombo.AddString(_T("DFD"));*/

	Create_Property_NCP();
	m_ctrCombo.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CApplOptDlg::Create_Property_NCP()
{
	int nValue[4] = { 0, };
	CString strValue[1];

	nValue[0] = GETVALUE(int, _T("ncpopt_dyn_uin"), _T("ncpopt_islbs"), 1);
	nValue[1] = GETVALUE(int, _T("ncpopt_dyn_uin"), _T("ncpopt_islgen"), 1);
	nValue[2] = GETVALUE(int, _T("ncpopt_dyn_uin"), _T("ncpopt_islld"), 1);
	nValue[3] = GETVALUE(int, _T("ncpopt_dyn_uin"), _T("ncpopt_init"), 1);
	strValue[0].Format(_T("%s"), (nValue[3] == 1 ? _T("강제수행") : _T("수행안함")) );
	
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("NCPOPT_DYN_UIN"));
	

	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("NCPOPT_ISLBS"), (_variant_t)nValue[0]
		, _T("유효 독립계통 최소 모선수")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("NCPOPT_ISLGEN"), (_variant_t)nValue[1]
		, _T("유효 독립계통 최소 발전기수")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("NCPOPT_ISLLD"), (_variant_t)nValue[2]
		, _T("유효 독립계통 최소 부하수")));
	
	CMFCPropertyGridProperty* pProp_Sub = new CMFCPropertyGridProperty(_T("NCPOPT_INIT"), (_variant_t)strValue[0]
		, _T("NCP Initial Mode 수행 여부 Flag(1: 강제수행, 0: 수행안함)"));
	pProp_Sub->AddOption(_T("강제수행"));
	pProp_Sub->AddOption(_T("수행안함"));
	pGroup->AddSubItem(pProp_Sub);
	
	
	m_ctrProp.AddProperty(pGroup);
	m_ctrProp.AdjustLayout();
}

void CApplOptDlg::Create_Property_DLE()
{
	int nValue[3] = { 0, };
	
	nValue[0] = GETVALUE(int, _T("escopt_dyn_uin"), _T("ESCOPT_SMWPRP"), 1);
	nValue[1] = GETVALUE(int, _T("escopt_dyn_uin"), _T("ESCOPT_DMWPRP"), 1);
	nValue[2] = GETVALUE(int, _T("escopt_dyn_uin"), _T("ESCOPT_FSOCTM"), 1);
	
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("ESCOPT_DYN_UIN"));


	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("ESCOPT_SMWPRP"), (_variant_t)nValue[0]
		, _T("시스템 피크 reduction price ($/kW)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("ESCOPT_DMWPRP"), (_variant_t)nValue[1]
		, _T("MG 피크 reduction price ($/kW)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("ESCOPT_FSOCTM"), (_variant_t)nValue[2]
		, _T("Full SOC 제약 시간")));

	m_ctrProp.AddProperty(pGroup);
	m_ctrProp.AdjustLayout();
}


void CApplOptDlg::Create_Property_RPF()
{
	int nValue[4] = { 0, };
	double dValue[11] = { 0., };

	nValue[3]	= GETVALUE(int		, _T("rpfopt_dyn_uin"), _T("rpfopt_mode"), 1);
	nValue[0]	= GETVALUE(int		, _T("rpfopt_dyn_uin"), _T("rpfopt_flat"), 1);
	nValue[1]	= GETVALUE(int		, _T("rpfopt_dyn_uin"), _T("rpfopt_max_iterations"), 1);
	nValue[2]	= GETVALUE(int		, _T("rpfopt_dyn_uin"), _T("rpfopt_svc_adj_limit"), 1);
	dValue[0]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_island_max_voltage_limit"), 1);
	dValue[1]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_island_min_voltage_limit"), 1);
	dValue[2]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_near_convergence_angle_limit"), 1);
	dValue[3]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_near_convergence_voltage_limit"), 1);
	dValue[4]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_near_convergence_mw_limit"), 1);
	dValue[5]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_near_convergence_mvar_limit"), 1);
	dValue[6]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_convergence_angle_limit"), 1);
	dValue[7]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_convergence_voltage_limit"), 1);
	dValue[8]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_convergence_mw_limit"), 1);
	dValue[9]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_convergence_mvar_limit"), 1);
	dValue[10]	= GETVALUE(double	, _T("rpfopt_dyn_uin"), _T("rpfopt_largest_mismatch_limit"), 1);
	
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("RPFOPT_DYN_UIN"));

	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_MODE"), (_variant_t)nValue[3], _T("조류계산 수행모드	(1:뉴턴, 2 : BFS)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_FLAT"), (_variant_t)nValue[0], _T("Flat start 여부")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_MAX_ITERATIONS"), (_variant_t)nValue[1], _T("최대 반복횟수")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_SVC_ADJ_LIMIT"), (_variant_t)nValue[2], _T("SVC 조정횟수")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_ISLAND_MAX_VOLTAGE_LIMIT"), (_variant_t)dValue[0], _T("허용전압 최대")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_ISLAND_MIN_VOLTAGE_LIMIT"), (_variant_t)dValue[1], _T("허용전압 최소")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_NEAR_CONVERGENCE_ANGLE_LIMIT"), (_variant_t)dValue[2], _T("부분수렴 기준(위상)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_NEAR_CONVERGENCE_VOLTAGE_LIMIT"), (_variant_t)dValue[3], _T("부분수렴 기준(전압)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_NEAR_CONVERGENCE_MW_LIMIT"), (_variant_t)dValue[4], _T("부분수렴 기준(MW)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_NEAR_CONVERGENCE_MVAR_LIMIT"), (_variant_t)dValue[5], _T("부분수렴 기준(MVAr)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_CONVERGENCE_ANGLE_LIMIT"), (_variant_t)dValue[6], _T("완전수렴 기준(위상)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_CONVERGENCE_VOLTAGE_LIMIT"), (_variant_t)dValue[7], _T("완전수렴 기준(전압)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_CONVERGENCE_MW_LIMIT"), (_variant_t)dValue[8], _T("완전수렴 기준(MW)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_CONVERGENCE_MVAR_LIMIT"), (_variant_t)dValue[9], _T("완전수렴 기준(MVAr)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("RPFOPT_LARGEST_MISMATCH_LIMIT"), (_variant_t)dValue[10], _T("최대 Mismatch")));

	m_ctrProp.AddProperty(pGroup);
	m_ctrProp.AdjustLayout();
}



void CApplOptDlg::Create_Property_DNR()
{
	int nValue[14] = { 0, };
	double dValue[1] = { 0., };

	nValue[0]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_nunpop"), 1);
	nValue[1]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_mutation_rate"), 1);
	dValue[0]	= GETVALUE(double	, _T("dnropt_dyn_uin"), _T("dnropt_ratio_lb"), 1);
	nValue[2]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_cben"), 1);
	nValue[3]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_reen"), 1);
	nValue[4]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_gaen"), 1);
	nValue[5]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_maen"), 1);
	nValue[6]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_object"), 1);
	nValue[7]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_max_chgsw"), 1);
	nValue[8]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_penalty_chgsw"), 1);
	nValue[9]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_penalty_volt"), 1);
	nValue[10]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_penalty_mw"), 1);
	nValue[11]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_rc_move_en"), 1);
	nValue[12]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_ss_move_en"), 1);
	nValue[13]	= GETVALUE(int		, _T("dnropt_dyn_uin"), _T("dnropt_load_type"), 1);
	
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("DNROPT_DYN_UIN"));


	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_NUNPOP"), (_variant_t)nValue[0], _T("유전알고리즘 염색체수")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_MUTATION_RATE"), (_variant_t)nValue[1], _T("유전알고리즘 돌연변이발생 비율 (%)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_RATIO_LB"), (_variant_t)dValue[0], _T("복합 목적함수에서 손실의비율(0.1~0.9)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_CBEN"), (_variant_t)nValue[2], _T("NR에 CB의 참여여부")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_REEN"), (_variant_t)nValue[3], _T("NR에 RECLOSER의 참여여부")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_GAEN"), (_variant_t)nValue[4], _T("NR에 자동화 스위치의 참여여부")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_MAEN"), (_variant_t)nValue[5], _T("NR에 수동 스위치의 참여여부")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_OBJECT"), (_variant_t)nValue[6], _T("NR의 목적함수(1.손실저감 2.피더밸런스 3,복합목적함수)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_MAX_CHGSW"), (_variant_t)nValue[7], _T("최대 허용 스위치 변동수(0:제한없음, 1~: 스위치 제한수)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_PENALTY_CHGSW"), (_variant_t)nValue[8], _T("허용 스위치 변동량 초과분에 대한 패널티율")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_PENALTY_VOLT"), (_variant_t)nValue[9], _T("전압 제한치 초과분에 대한 패널티율")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_PENALTY_MW"), (_variant_t)nValue[10], _T("용량제한치 초과분에 대한 패널티율")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_RC_MOVE_EN"), (_variant_t)nValue[11], _T("리클로져 이동 허동")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_SS_MOVE_EN"), (_variant_t)nValue[12], _T("변전소간 상시개방점 이동 허용")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("DNROPT_LOAD_TYPE"), (_variant_t)nValue[13], _T("재구성 기준부하(1: 전일최대, 2 : 월 최대, 3 : 하계피크, 4 : 동계 피크)")));
	
	m_ctrProp.AddProperty(pGroup);
	m_ctrProp.AdjustLayout();
}


void CApplOptDlg::Create_Property_SOP()
{
	int nValue[2] = { 0, };
	double dValue[1] = { 0., };
	dValue[0] = GETVALUE(double , _T("sopopt_dyn_uin"), _T("SOPOPT_TARGET_LOAD"), 1);
	nValue[0] = GETVALUE(int, _T("sopopt_dyn_uin"), _T("SOPOPT_TARGET_CONFIGU"), 1);
	nValue[1] = GETVALUE(int, _T("sopopt_dyn_uin"), _T("SOPOPT_LOAD_LV"), 1);

	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("SOPOPT_DYN_UIN"));


	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("SOPOPT_TARGET_LOAD"), (_variant_t)dValue[0]
		, _T("SOP 생성 기준부하")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("SOPOPT_TARGET_CONFIGU"), (_variant_t)nValue[0]
		, _T("SOP 생성 기준 토폴로지")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("SOPOPT_LOAD_LV"), (_variant_t)nValue[1]
		, _T("SOP")));

	m_ctrProp.AddProperty(pGroup);
	m_ctrProp.AdjustLayout();
}


void CApplOptDlg::Create_Property_PDVR()
{
	int nValue[3] = { 0, };
	double dValue[4] = { 0., };
	dValue[0] = GETVALUE(double , _T("pdvropt_dyn_uin"), _T("PDVROPT_PFVTOL"), 1);
	dValue[1] = GETVALUE(double , _T("pdvropt_dyn_uin"), _T("PDVROPT_PFQTOL"), 1);
	dValue[2] = GETVALUE(double , _T("pdvropt_dyn_uin"), _T("PDVROPT_PFITERMAX"), 1);
	dValue[3] = GETVALUE(double , _T("pdvropt_dyn_uin"), _T("PDVROPT_HISTH"), 1);
	nValue[0] = GETVALUE(int, _T("pdvropt_dyn_uin"), _T("PDVROPT_SRTHIS"), 1);
	nValue[1] = GETVALUE(int, _T("pdvropt_dyn_uin"), _T("PDVROPT_ENDHIS"), 1);
	nValue[2] = GETVALUE(int, _T("pdvropt_dyn_uin"), _T("PDVROPT_TGTTR"), 1);

	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("PDVROPT_DYN_UIN"));

	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PDVROPT_PFVTOL"), (_variant_t)dValue[0], _T("조류계산 수렴 기준 전압 갱신량")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PDVROPT_PFQTOL"), (_variant_t)dValue[1], _T("조류계산 수렴 기준 무효전력 갱신량")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PDVROPT_PFITERMAX"), (_variant_t)dValue[2], _T("조류계산 최대 반복연산 횟수")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PDVROPT_HISTH"), (_variant_t)dValue[3], _T("PDVR에서 사용할 최대/최소 부하 이력 생성시 제거할 상/하위 영역")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PDVROPT_SRTHIS"), (_variant_t)nValue[0], _T("검토 이력의 시작일(2020년 12월 2일 -->20201202)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PDVROPT_ENDHIS"), (_variant_t)nValue[1], _T("검토 이력의 종료일(2020년 12월 2일 -->20201202)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PDVROPT_TGTTR"), (_variant_t)nValue[2], _T("PDVR을 수행할 영역의 MTR을 나타내는 index(TR 테이블 기준 index)")));

	m_ctrProp.AddProperty(pGroup);
	m_ctrProp.AdjustLayout();
}


void CApplOptDlg::Create_Property_PCE()
{
	int nValue[8] = { 0, };
	double dValue[6] = { 0., };
	nValue[0]	= GETVALUE(int		, _T("pceopt_dyn_uin"), _T("PCEOPT_BG1_TM"),1);
	nValue[1]	= GETVALUE(int		, _T("pceopt_dyn_uin"), _T("PCEOPT_BG2_TM"),1);
	nValue[2]	= GETVALUE(int		, _T("pceopt_dyn_uin"), _T("PCEOPT_BG3_TM"),1);
	nValue[3]	= GETVALUE(int		, _T("pceopt_dyn_uin"), _T("PCEOPT_BG4_TM"),1);
	nValue[4]	= GETVALUE(int		, _T("pceopt_dyn_uin"), _T("PCEOPT_BG5_TM"),1);
	dValue[0]	= GETVALUE(double	, _T("pceopt_dyn_uin"), _T("PCEOPT_MX_TMS"),1);
	dValue[1]	= GETVALUE(double	, _T("pceopt_dyn_uin"), _T("PCEOPT_MX_TAS"),1);
	dValue[2]	= GETVALUE(double	, _T("pceopt_dyn_uin"), _T("PCEOPT_MX_MRT"),1);
	dValue[3]	= GETVALUE(double	, _T("pceopt_dyn_uin"), _T("PCEOPT_TMS_STEP"),1);
	dValue[4]	= GETVALUE(double	, _T("pceopt_dyn_uin"), _T("PCEOPT_TAS_STEP"),1);
	dValue[5]	= GETVALUE(double	, _T("pceopt_dyn_uin"), _T("PCEOPT_MRT_STEP"),1);
	nValue[5]	= GETVALUE(int		, _T("pceopt_dyn_uin"), _T("PCEOPT_MN_IIC"),1);
	nValue[6]	= GETVALUE(int		, _T("pceopt_dyn_uin"), _T("PCEOPT_MX_IIC"),1);
	nValue[7]	= GETVALUE(int		, _T("pceopt_dyn_uin"), _T("PCEOPT_IIC_STEP"),1);


	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("PDVROPT_DYN_UIN"));

	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_BG1_TM"), (_variant_t)nValue[0], _T("비 보호기기 Group1과 확보해야 하는 트립 시간차")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_BG2_TM"), (_variant_t)nValue[1], _T("비 보호기기 Group2과 확보해야 하는 트립 시간차")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_BG3_TM"), (_variant_t)nValue[2], _T("비 보호기기 Group3과 확보해야 하는 트립 시간차")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_BG4_TM"), (_variant_t)nValue[3], _T("비 보호기기 Group4과 확보해야 하는 트립 시간차")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_BG5_TM"), (_variant_t)nValue[4], _T("비 보호기기 Group5과 확보해야 하는 트립 시간차")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_MX_TMS"), (_variant_t)dValue[0], _T("간배수 설정 최대값")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_MX_TAS"), (_variant_t)dValue[1], _T("간추가 설정 최대값")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_MX_MRT"), (_variant_t)dValue[2], _T("소응답시간 설정 최댓값")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_TMS_STEP"), (_variant_t)dValue[3], _T("시간배수 단계값")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_TAS_STEP"), (_variant_t)dValue[4], _T("시간추가 단계값")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_MRT_STEP"), (_variant_t)dValue[5], _T("최소응답시간 설정 최대값")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_MN_IIC"), (_variant_t)nValue[5], _T("소 순시동작전환 전류설정값")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_MX_IIC"), (_variant_t)nValue[6], _T("대 순시동작전환 전류설정값")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("PCEOPT_IIC_STEP"), (_variant_t)nValue[7], _T("순시동작전환 전류설정값 단계값")));


	m_ctrProp.AddProperty(pGroup);
	m_ctrProp.AdjustLayout();
}


void CApplOptDlg::OnCbnSelchangeApplOptDlgCombo1()
{
	int nPos = m_ctrCombo.GetCurSel();
	if (nPos == -1)
		return;

	m_ctrProp.RemoveAll();
	if (nPos == 1)
	{
		Create_Property_DLE();
	}
	else if (nPos == 2)
	{
		Create_Property_RPF();
	}
	else if (nPos == 3)
	{
		Create_Property_DNR();
	}
	else if (nPos == 4)
	{
		Create_Property_SOP();
	}
	else if (nPos == 5)
	{
		Create_Property_PDVR();
	}
	else if (nPos == 6)
	{
		Create_Property_PCE();
	}
	else
	{
		Create_Property_NCP();
	}

}

void CApplOptDlg::Save_Property_NCP()
{
	CString strValue[4];

	CMFCPropertyGridProperty* pGroup, *pProp;
	pGroup = m_ctrProp.GetProperty(0);
	for (int i = 0; i < pGroup->GetSubItemsCount(); i++)
	{
		pProp = pGroup->GetSubItem(i);
		strValue[i] = pProp->GetValue();
	}
	

	PUTDOUBLE2VALUE(_T("ncpopt_dyn_uin"), _T("ncpopt_islbs"), 1, (double) _wtoi(strValue[0]));
	PUTDOUBLE2VALUE(_T("ncpopt_dyn_uin"), _T("ncpopt_islgen"), 1,(double)_wtoi(strValue[1]));
	PUTDOUBLE2VALUE(_T("ncpopt_dyn_uin"), _T("ncpopt_islld"), 1,(double)_wtoi(strValue[2]));
	PUTDOUBLE2VALUE(_T("ncpopt_dyn_uin"), _T("ncpopt_init"), 1,(double) (strValue[3] == _T("강제수행") ? 1 : 0) );
}

void CApplOptDlg::Save_Property_DLE()
{
	CString strValue[3];

	CMFCPropertyGridProperty* pGroup, *pProp;
	pGroup = m_ctrProp.GetProperty(0);
	for (int i = 0; i < pGroup->GetSubItemsCount(); i++)
	{
		pProp = pGroup->GetSubItem(i);
		strValue[i] = pProp->GetValue();
	}


	PUTDOUBLE2VALUE(_T("escopt_dyn_uin"), _T("ESCOPT_SMWPRP"), 1,(double)_wtoi(strValue[0]));
	PUTDOUBLE2VALUE(_T("escopt_dyn_uin"), _T("ESCOPT_DMWPRP"), 1,(double)_wtoi(strValue[1]));
	PUTDOUBLE2VALUE(_T("escopt_dyn_uin"), _T("ESCOPT_FSOCTM"), 1,(double)_wtoi(strValue[2]));

}

void CApplOptDlg::Save_Property_RPF()
{
	CString strValue[15];

	CMFCPropertyGridProperty* pGroup, *pProp;
	pGroup = m_ctrProp.GetProperty(0);
	for (int i = 0; i < pGroup->GetSubItemsCount(); i++)
	{
		pProp = pGroup->GetSubItem(i);
		strValue[i] = pProp->GetValue();
	}

	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_mode"),												1,(double)_wtoi(strValue[0]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_flat"),												1,(double)_wtoi(strValue[1]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_max_iterations"),										1,(double)_wtoi(strValue[2]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_svc_adj_limit"),										1,(double)_wtoi(strValue[3]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_island_max_voltage_limit"),							1,(double)_wtof(strValue[4]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_island_min_voltage_limit"),							1,(double)_wtof(strValue[5]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_near_convergence_angle_limit"),						1,(double)_wtof(strValue[6]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_near_convergence_voltage_limit"),						1,(double)_wtof(strValue[7]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_near_convergence_mw_limit"),							1,(double)_wtof(strValue[8]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_near_convergence_mvar_limit"),						1,(double)_wtof(strValue[9]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_convergence_angle_limit"),							1,(double)_wtof(strValue[10]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_convergence_voltage_limit"),							1,(double)_wtof(strValue[11]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_convergence_mw_limit"),								1,(double)_wtof(strValue[12]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_convergence_mvar_limit"),								1,(double)_wtof(strValue[13]));
	PUTDOUBLE2VALUE( _T("rpfopt_dyn_uin"), _T("rpfopt_largest_mismatch_limit"),								1,(double)_wtof(strValue[14]));

}

void CApplOptDlg::Save_Property_DNR()
{
	CString strValue[15];

	CMFCPropertyGridProperty* pGroup, *pProp;
	pGroup = m_ctrProp.GetProperty(0);
	for (int i = 0; i < pGroup->GetSubItemsCount(); i++)
	{
		pProp = pGroup->GetSubItem(i);
		strValue[i] = pProp->GetValue();
	}


	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_nunpop"),						1,(double)_wtoi(strValue[0]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_mutation_rate"),					1,(double)_wtoi(strValue[1]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_ratio_lb"),						1,(double)_wtof(strValue[2]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_cben"),							1,(double)_wtoi(strValue[3]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_reen"),							1,(double)_wtoi(strValue[4]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_gaen"),							1,(double)_wtoi(strValue[5]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_maen"),							1,(double)_wtoi(strValue[6]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_object"),						1,(double)_wtoi(strValue[7]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_max_chgsw"),						1,(double)_wtoi(strValue[8]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_penalty_chgsw"),					1,(double)_wtoi(strValue[9]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_penalty_volt"),					1,(double)_wtoi(strValue[10]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_penalty_mw"),					1,(double)_wtoi(strValue[11]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_rc_move_en"),					1,(double)_wtoi(strValue[12]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_ss_move_en"),					1,(double)_wtoi(strValue[13]));
	PUTDOUBLE2VALUE( _T("dnropt_dyn_uin"), _T("dnropt_load_type"),						1,(double)_wtoi(strValue[14]));

}

void CApplOptDlg::Save_Property_SOP()
{
	CString strValue[3];

	CMFCPropertyGridProperty* pGroup, *pProp;
	pGroup = m_ctrProp.GetProperty(0);
	for (int i = 0; i < pGroup->GetSubItemsCount(); i++)
	{
		pProp = pGroup->GetSubItem(i);
		strValue[i] = pProp->GetValue();
	}

	PUTDOUBLE2VALUE(_T("sopopt_dyn_uin"), _T("SOPOPT_TARGET_LOAD"), 1, (double)_wtof(strValue[0]));
	PUTDOUBLE2VALUE(_T("sopopt_dyn_uin"), _T("SOPOPT_TARGET_CONFIGU"), 1, (double)_wtoi(strValue[1]));
	PUTDOUBLE2VALUE(_T("sopopt_dyn_uin"), _T("SOPOPT_LOAD_LV"), 1, (double)_wtoi(strValue[2]));


}

void CApplOptDlg::Save_Property_PDVR()
{
	CString strValue[7];

	CMFCPropertyGridProperty* pGroup, *pProp;
	pGroup = m_ctrProp.GetProperty(0);
	for (int i = 0; i < pGroup->GetSubItemsCount(); i++)
	{
		pProp = pGroup->GetSubItem(i);
		strValue[i] = pProp->GetValue();
	}


	PUTDOUBLE2VALUE(_T("pdvropt_dyn_uin"), _T("PDVROPT_PFVTOL"),	1,(double)_wtof(strValue[0]));
	PUTDOUBLE2VALUE(_T("pdvropt_dyn_uin"), _T("PDVROPT_PFQTOL"),	1,(double)_wtof(strValue[1]));
	PUTDOUBLE2VALUE(_T("pdvropt_dyn_uin"), _T("PDVROPT_PFITERMAX"), 1,(double)_wtof(strValue[2]));
	PUTDOUBLE2VALUE(_T("pdvropt_dyn_uin"), _T("PDVROPT_HISTH"),		1,(double)_wtof(strValue[3]));
	PUTDOUBLE2VALUE(_T("pdvropt_dyn_uin"), _T("PDVROPT_SRTHIS"),	1,(double)_wtoi(strValue[4]));
	PUTDOUBLE2VALUE(_T("pdvropt_dyn_uin"), _T("PDVROPT_ENDHIS"),	1,(double)_wtoi(strValue[5]));
	PUTDOUBLE2VALUE(_T("pdvropt_dyn_uin"), _T("PDVROPT_TGTTR"),		1,(double)_wtoi(strValue[6]));

}

void CApplOptDlg::Save_Property_PCE()
{
	CString strValue[14];

	CMFCPropertyGridProperty* pGroup, *pProp;
	pGroup = m_ctrProp.GetProperty(0);
	for (int i = 0; i < pGroup->GetSubItemsCount(); i++)
	{
		pProp = pGroup->GetSubItem(i);
		strValue[i] = pProp->GetValue();
	}


	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_BG1_TM"),			1,(double)_wtoi(strValue[0]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_BG2_TM"),			1,(double)_wtoi(strValue[1]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_BG3_TM"),			1,(double)_wtoi(strValue[2]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_BG4_TM"),			1,(double)_wtoi(strValue[3]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_BG5_TM"),			1,(double)_wtoi(strValue[4]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_MX_TMS"),			1,(double)_wtof(strValue[5]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_MX_TAS"),			1,(double)_wtof(strValue[6]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_MX_MRT"),			1,(double)_wtof(strValue[7]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_TMS_STEP"),		1,(double)_wtof(strValue[8]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_TAS_STEP"),		1,(double)_wtof(strValue[9]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_MRT_STEP"),		1,(double)_wtof(strValue[10]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_MN_IIC"),			1,(double)_wtoi(strValue[11]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_MX_IIC"),			1,(double)_wtoi(strValue[12]));
	PUTDOUBLE2VALUE(_T("pceopt_dyn_uin"), _T("PCEOPT_IIC_STEP"),		1,(double)_wtoi(strValue[13]));

}


void CApplOptDlg::OnBnClickedOk()
{
	int nPos = m_ctrCombo.GetCurSel();
	if (nPos == -1)
		return;

	if (nPos == 1)
	{
		Save_Property_DLE();
	}
	else if (nPos == 2)
	{
		Save_Property_RPF();
	}
	else if (nPos == 3)
	{
		Save_Property_DNR();
	}
	else if (nPos == 4)
	{
		Save_Property_SOP();
	}
	else if (nPos == 5)
	{
		Save_Property_PDVR();
	}
	else if (nPos == 6)
	{
		Save_Property_PCE();
	}
	else
	{
		Save_Property_NCP();
	}


	CDialogEx::OnOK();
}
