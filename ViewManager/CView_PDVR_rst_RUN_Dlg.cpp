// CView_PDVR_rst_RUN_Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "CView_PDVR_rst_RUN_Dlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "../DataManager/CDataManager.h"


// CView_PDVR_rst_RUN_Dlg 대화 상자

IMPLEMENT_DYNAMIC(CView_PDVR_rst_RUN_Dlg, CDialogEx)

CView_PDVR_rst_RUN_Dlg::CView_PDVR_rst_RUN_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PDVR_RUN_DLG, pParent)
{
	m_nMode = 0;
}

CView_PDVR_rst_RUN_Dlg::~CView_PDVR_rst_RUN_Dlg()
{
}

void CView_PDVR_rst_RUN_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PDVR_RUN_DLG_RADIO7, m_ctrRadio_Main[0]);
	DDX_Control(pDX, IDC_PDVR_RUN_DLG_RADIO8, m_ctrRadio_Main[1]);
	DDX_Control(pDX, IDC_PDVR_RUN_DLG_RADIO1, m_ctrRadio_Load[0]);
	DDX_Control(pDX, IDC_PDVR_RUN_DLG_RADIO2, m_ctrRadio_Load[1]);
	DDX_Control(pDX, IDC_PDVR_RUN_DLG_RADIO3, m_ctrRadio_Date[0]);
	DDX_Control(pDX, IDC_PDVR_RUN_DLG_RADIO4, m_ctrRadio_Date[1]);
	DDX_Control(pDX, IDC_PDVR_RUN_DLG_RADIO5, m_ctrRadio_factor[0]);
	DDX_Control(pDX, IDC_PDVR_RUN_DLG_RADIO6, m_ctrRadio_factor[1]);
	DDX_Control(pDX, IDC_PDVR_RUN_DLG_DATE1, m_ctrDate[0]);
	DDX_Control(pDX, IDC_PDVR_RUN_DLG_DATE2, m_ctrDate[1]);
}


BEGIN_MESSAGE_MAP(CView_PDVR_rst_RUN_Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_PDVR_RUN_DLG_RADIO7, &CView_PDVR_rst_RUN_Dlg::OnBnClickedPdvrRunDlgRadio7)
	ON_BN_CLICKED(IDC_PDVR_RUN_DLG_RADIO8, &CView_PDVR_rst_RUN_Dlg::OnBnClickedPdvrRunDlgRadio8)
	ON_BN_CLICKED(IDC_PDVR_RUN_DLG_BTN1, &CView_PDVR_rst_RUN_Dlg::OnBnClickedPdvrRunDlgBtn1)
	ON_EN_CHANGE(IDC_PDVR_RUN_DLG_EDIT1, &CView_PDVR_rst_RUN_Dlg::OnEnChangePdvrRunDlgEdit1)
	ON_EN_CHANGE(IDC_PDVR_RUN_DLG_EDIT8, &CView_PDVR_rst_RUN_Dlg::OnEnChangePdvrRunDlgEdit8)
	ON_BN_CLICKED(IDC_PDVR_RUN_DLG_RADIO1, &CView_PDVR_rst_RUN_Dlg::OnBnClickedPdvrRunDlgRadio1)
	ON_BN_CLICKED(IDC_PDVR_RUN_DLG_RADIO2, &CView_PDVR_rst_RUN_Dlg::OnBnClickedPdvrRunDlgRadio2)
END_MESSAGE_MAP()


// CView_PDVR_rst_RUN_Dlg 메시지 처리기


BOOL CView_PDVR_rst_RUN_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ctrRadio_Main[0].SetCheck(TRUE);
	m_ctrRadio_Load[0].SetCheck(TRUE);
	m_ctrRadio_Date[1].SetCheck(TRUE);
	m_ctrRadio_factor[0].SetCheck(TRUE);

	/*m_ctrDate[0].SetTime(m_timeData[0]);
	m_ctrDate[1].SetTime(m_timeData[1]);*/
	//////////// 220707 남궁원 요청
	if (m_nMode == 1)
	{
		CTime t = CTime::GetCurrentTime();

		m_timeData[0].SetDate(t.GetYear() - 1, 1, 1);
		m_timeData[1].SetDate(t.GetYear() - 1, 12, 31);
		m_ctrDate[0].SetTime(m_timeData[0]);
		m_ctrDate[1].SetTime(m_timeData[1]);
		m_ctrDate[0].EnableWindow(FALSE);
		m_ctrDate[1].EnableWindow(FALSE);
	}
	else
	{
		m_ctrDate[0].SetTime(m_timeData[0]);
		m_ctrDate[1].SetTime(m_timeData[1]);
		m_ctrDate[0].EnableWindow(TRUE);
		m_ctrDate[1].EnableWindow(TRUE);
	}

	int nCount,nData;
	double dBad;
	CString strCount,strBad;
	
	dBad = GETVALUE(double, _T("PDVROPT_DYN_UIN"), _T("PDVROPT_BADRATE"), 1);
	nCount = GETVALUE(int, _T("PDVROPT_DYN_UIN"), _T("PDVROPT_CANDNUM"), 1);
	nData = GETVALUE(int, _T("PDVROPT_DYN_UIN"), _T("PDVROPT_TERM"), 1);

	strBad.Format(_T("%.2lf"), dBad*100);
	strCount.Format(_T("%d"), nCount);

	SetDlgItemText(IDC_PDVR_RUN_DLG_EDIT7,_T("90"));
	SetDlgItemText(IDC_PDVR_RUN_DLG_EDIT3, strBad);
	SetDlgItemText(IDC_PDVR_RUN_DLG_EDIT4, strCount);

	if (m_nMode == 1)
	{
		m_ctrRadio_Load[0].EnableWindow(TRUE);
		m_ctrRadio_Load[1].EnableWindow(TRUE);
			
	}
	else
	{
		m_ctrRadio_Load[0].SetCheck(FALSE);
		m_ctrRadio_Load[1].SetCheck(TRUE);
	}

	m_ctrRadio_Date[0].EnableWindow(TRUE);
	m_ctrRadio_Date[1].EnableWindow(TRUE);

	if (nData == 1)
	{
		m_ctrRadio_Date[0].SetCheck(TRUE);
		m_ctrRadio_Date[1].SetCheck(FALSE);
	}
	else
	{
		m_ctrRadio_Date[0].SetCheck(FALSE);
		m_ctrRadio_Date[1].SetCheck(TRUE);
	}

	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT3)->EnableWindow(TRUE);
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT4)->EnableWindow(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CView_PDVR_rst_RUN_Dlg::OnBnClickedPdvrRunDlgRadio7()
{
	m_ctrRadio_factor[0].EnableWindow(FALSE);
	m_ctrRadio_factor[1].EnableWindow(FALSE);

	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT6)->EnableWindow(FALSE);
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT7)->EnableWindow(FALSE);
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT8)->EnableWindow(FALSE);
	///////////////
	if (m_ctrRadio_Load[0].GetCheck())
	{
		m_ctrDate[0].EnableWindow(FALSE);
		m_ctrDate[1].EnableWindow(FALSE);
	}
	else
	{
		m_ctrDate[0].EnableWindow(TRUE);
		m_ctrDate[1].EnableWindow(TRUE);
	}
	

	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT1)->EnableWindow(TRUE);

	if (m_nMode == 1)
	{
		m_ctrRadio_Load[0].EnableWindow(TRUE);
		m_ctrRadio_Load[1].EnableWindow(TRUE);
		m_ctrRadio_Date[0].EnableWindow(TRUE);
		m_ctrRadio_Date[1].EnableWindow(TRUE);

		GetDlgItem(IDC_PDVR_RUN_DLG_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_PDVR_RUN_DLG_EDIT4)->EnableWindow(TRUE);
	}
}


void CView_PDVR_rst_RUN_Dlg::OnBnClickedPdvrRunDlgRadio8()
{
	m_ctrRadio_Load[0].EnableWindow(FALSE);
	m_ctrRadio_Load[1].EnableWindow(FALSE);
	m_ctrRadio_Date[0].EnableWindow(FALSE);
	m_ctrRadio_Date[1].EnableWindow(FALSE);

	m_ctrDate[0].EnableWindow(FALSE);
	m_ctrDate[1].EnableWindow(FALSE);

	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT4)->EnableWindow(FALSE);
	///////////////
	m_ctrRadio_factor[0].EnableWindow(TRUE);
	m_ctrRadio_factor[1].EnableWindow(TRUE);

	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT5)->EnableWindow(TRUE);
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT6)->EnableWindow(TRUE);
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT7)->EnableWindow(TRUE);
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT8)->EnableWindow(TRUE);

}


void CView_PDVR_rst_RUN_Dlg::OnBnClickedPdvrRunDlgBtn1()
{
	m_ctrDate[0].GetTime(m_timeData[0]);
	m_ctrDate[1].GetTime(m_timeData[1]);

	if (m_timeData[0] > m_timeData[1])
	{
		AfxMessageBox(_T("기간 범위 설정 오류"));
		return;
	}


	CString strPU, strBad, strCount;
	GetDlgItemText(IDC_PDVR_RUN_DLG_EDIT1, strPU);
	double dPU = _wtof(strPU);
	if (dPU > 0)
	{
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("pdvropt_oltcmodel"), 1, (double)4.);
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("pdvropt_oltcv"), 1, (double)dPU);
	}
	else
	{
		if (m_nMode == 1)
		{
			CDataManager* pDataMng = CDataManager::Instance();
			pDataMng->Set_PDVR_Voltage2ADMS(m_nTrIndex, m_nGenType, m_timeData[0], m_timeData[1]);
		}
		else
		{
			int nOltcType = GETVALUE(int, _T("PDVROPT_DYN_UIN"), _T("pdvropt_oltcmodel"), 1);
			if (nOltcType == 4)
			{
				AfxMessageBox(_T("OLTC 동작 설정이 송출전압고정 입니다. 송출전압의 설정값이 필요합니다."));
				return;
			}
		}
	}

	


	int nRunMode = m_ctrRadio_Main[0].GetCheck();
	if (nRunMode == TRUE)
	{
		nRunMode = m_ctrRadio_Load[1].GetCheck();
		if (nRunMode == 0)
			nRunMode = 2;


		GetDlgItemText(IDC_PDVR_RUN_DLG_EDIT3, strBad);
		GetDlgItemText(IDC_PDVR_RUN_DLG_EDIT4, strCount);

		int nCount = _wtoi(strCount);
		double dBad = _wtof(strBad) / 100;
		int nDate = m_ctrRadio_Date[0].GetCheck();
		if (nDate == 0)
			nDate = 2;

		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_BADRATE"), 1, (double)dBad);
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_CANDNUM"), 1, (double)nCount);
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_TERM"), 1, (double)nDate);
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_HISOPT"), 1, (double)nRunMode);

	}
	else  ///////////// 수동
	{
		nRunMode = 3;
		CString strPU, strMW, strMVar,strGen;
		GetDlgItemText(IDC_PDVR_RUN_DLG_EDIT8, strPU);
		double dPU = _wtof(strPU);
		if (dPU > 0)
		{
			PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("pdvropt_oltcmodel"), 1, (double)4.);
			PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("pdvropt_oltcv"), 1, (double)dPU);
		}

		GetDlgItemText(IDC_PDVR_RUN_DLG_EDIT5, strMW);
		GetDlgItemText(IDC_PDVR_RUN_DLG_EDIT6, strGen);
		GetDlgItemText(IDC_PDVR_RUN_DLG_EDIT7, strMVar);

		int nPhase = m_ctrRadio_factor[0].GetCheck();
		double dMW, dMVar, dGen,dResult;

		dMW = _wtof(strMW);
		dMVar = _wtof(strMVar)/100;
		dGen = _wtof(strGen);

		dResult = sqrt(pow(dMW / dMVar, 2.) - pow(dMW, 2.));
		strMVar.Format(_T("%.2lf"), dResult);
		dResult = _wtof(strMVar);

		dResult *= 100000;
		dResult += dGen;

		if (nPhase == 1)
			dResult *= -1;

		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_UINMW"), 1, (double)dMW);
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_UINMVAR"), 1, (double)dResult);
		PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("PDVROPT_HISOPT"), 1, (double)nRunMode);

	}
	CDialogEx::OnOK();
}


void CView_PDVR_rst_RUN_Dlg::OnEnChangePdvrRunDlgEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	CString strPU,strKV;

	GetDlgItemText(IDC_PDVR_RUN_DLG_EDIT1, strPU);

	if (strPU.IsEmpty())
		strKV.Empty();
	else
		strKV.Format(_T("%.3lf"), 22.9*_wtof(strPU));

	SetDlgItemText(IDC_PDVR_RUN_DLG_EDIT2, strKV);
}


void CView_PDVR_rst_RUN_Dlg::OnEnChangePdvrRunDlgEdit8()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	CString strPU, strKV;

	GetDlgItemText(IDC_PDVR_RUN_DLG_EDIT8, strPU);

	if (strPU.IsEmpty())
		strKV.Empty();
	else
		strKV.Format(_T("%.3lf"), 22.9*_wtof(strPU));

	SetDlgItemText(IDC_PDVR_RUN_DLG_EDIT9, strKV);
}


void CView_PDVR_rst_RUN_Dlg::OnBnClickedPdvrRunDlgRadio1()
{
	SetDlgItemText(IDC_PDVR_RUN_DLG_EDIT1, _T(""));
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT1)->EnableWindow(FALSE);

	/////////////////////// 221221 남구원 요청
	CTime t = CTime::GetCurrentTime();

	m_timeData[0].SetDate(t.GetYear() - 1, 1, 1);
	m_timeData[1].SetDate(t.GetYear() - 1, 12, 31);

	m_ctrDate[0].SetTime(m_timeData[0]);
	m_ctrDate[1].SetTime(m_timeData[1]);
	m_ctrDate[0].EnableWindow(FALSE);
	m_ctrDate[1].EnableWindow(FALSE);
}


void CView_PDVR_rst_RUN_Dlg::OnBnClickedPdvrRunDlgRadio2()
{
	SetDlgItemText(IDC_PDVR_RUN_DLG_EDIT1, _T(""));
	GetDlgItem(IDC_PDVR_RUN_DLG_EDIT1)->EnableWindow(TRUE);

	/*m_timeData[0].SetDate(2021, 1, 1);
	m_timeData[1].SetDate(2021, 12, 31);
	m_ctrDate[0].SetTime(m_timeData[0]);
	m_ctrDate[1].SetTime(m_timeData[1]);*/
	m_ctrDate[0].EnableWindow(TRUE);
	m_ctrDate[1].EnableWindow(TRUE);
}
