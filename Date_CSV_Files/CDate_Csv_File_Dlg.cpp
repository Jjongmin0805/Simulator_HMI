// CDate_Csv_File_Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "CDate_Csv_File_Dlg.h"
//#include "afxdialogex.h"
#include "Resource.h"


// CDate_Csv_File_Dlg 대화 상자

IMPLEMENT_DYNAMIC(CDate_Csv_File_Dlg, CDialog)

CDate_Csv_File_Dlg::CDate_Csv_File_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CSV_FILES_DLG, pParent)
{
	m_nCheck_Gen_upload = 0;
}

CDate_Csv_File_Dlg::~CDate_Csv_File_Dlg()
{
}

void CDate_Csv_File_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDate_Csv_File_Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDate_Csv_File_Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDate_Csv_File_Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDate_Csv_File_Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDate_Csv_File_Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDate_Csv_File_Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDate_Csv_File_Dlg 메시지 처리기


BOOL CDate_Csv_File_Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

CString CDate_Csv_File_Dlg::MyPath()
{
	CString slmpath;
	WCHAR szDirve[256], szDir[2048];
	WCHAR programpath[2048];

	memset(szDir, 0x00, sizeof(szDir));
	memset(szDirve, 0x00, sizeof(szDirve));
	GetModuleFileName(0, programpath, 2048);
	_wsplitpath_s(programpath, szDirve, 256, szDir, 2048, NULL, 0, NULL, 0);

	slmpath.Format(_T("%s%s"), szDirve, szDir);
	slmpath.Delete(slmpath.GetLength() - 1, 1);
	return slmpath;
}


//
void CDate_Csv_File_Dlg::GenCSV_Insert()
{
	CString		strPath, strTitleName, strFilePath, strFileName;
	FILE*		stream = NULL;
	char		chBuffer[4096] = { 0x00, };
	char		*token = NULL;
	int			count = 0;
	int			nCheck_Point = 0;
	//
	int			nGen_Index;				//발전기csv index
	int			nGen_TREXCL;			//발전기 연계변압기 여부 없으면 기봅값 1 (1:특고압 전용, 2: 저압 전용3: 저압 공용)
	int			nGen_ITR_WDC;			//발전기 연계변압기 결선 기본값2 (1:Ygyg, 2:Ygd 3:Dyg 4: Yd)
	int			nGen_TYPE = 5;			//발전기 종류(1:무한모선, 2 : 디젤, 3 : ESS, 4 : 풍력, 5 : 태양광, 6 : 바이오)
	int			nGen_MACH_TYPE = 1;		//발전기 유형(1:인버터, 2:동기기, 3:유도기, 4:고압동기기)
	double		dGen_CAP_kw;			//발전기용량
	double		dGen_ITR_X = 6;			//발전기용량 연계 변압기 정상분 X(%)
	CString		szGen_Name;				//발전기 이름
	CString		szGEN_Connect_NdName;   //발전기 연계 노드 이름 //이걸로 데이터 연결점 찾는 부분

	CString     szGen_Overlap[200];
	CString     szGen_Overlap_Box;
	//
	CString     szGenunit_NM, szGenunit_NO;
	double		dGenunit_CAP_KW = 0;
	int			nGen_Check = 0;
	CString		szGen_CEQID;
	int			nCEQ_ID_CSV = 0;

	for (int i = 0; i < 200; i++)
	{
		szGen_Overlap[i].Format(_T(""));
	}
	int nIndexGen = 0;

	CFileDialog FileDlg(TRUE, _T("csv"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("KASIM Data File(*.csv)|*.csv| All Files(*.*)|*.*|"));

	CString szRoute;

	szRoute.Format(_T("\\Config"));
	strPath = (MyPath() + szRoute);

	FileDlg.m_pOFN->lpstrInitialDir = (LPCWSTR)strPath;

	if (FileDlg.DoModal() != IDOK)
		return;

	strTitleName = FileDlg.GetFileTitle();
	strFilePath = FileDlg.GetPathName();
	strFileName = FileDlg.GetFileName();

	stream = _wfopen(strFilePath, L"r+");
	// 
	if (stream != NULL)
	{
		fgets(chBuffer, sizeof(chBuffer), stream);
		while (fgets(chBuffer, sizeof(chBuffer), stream))
		{
			count = 0;
			token = strtok(chBuffer, ",");
			while (token != NULL)
			{
				if (count == 0)	nGen_Index = atoi(token);
				else if (count == 1)	nGen_Check = atoi(token);
				else if (count == 2)	szGen_CEQID = CA2W((token)).m_psz;
				else if (count == 3)	szGen_Name = CA2W((token)).m_psz;
				else if (count == 4)	dGen_CAP_kw = atof(token);
				else if (count == 5)	szGenunit_NM = CA2W((token)).m_psz;
				else if (count == 6)	dGenunit_CAP_KW = atof(token);
				else if (count == 7)	szGenunit_NO = CA2W((token)).m_psz;
				else if (count == 8)	szGEN_Connect_NdName = CA2W((token)).m_psz;
				else if (count == 9)	nGen_TREXCL = atoi(token);
				else if (count == 10)	nGen_ITR_WDC = atoi(token);
				else if (count == 11)	nGen_TYPE = atoi(token);
				else if (count == 12)	dGen_ITR_X = atof(token);
				else if (count == 13)	nGen_MACH_TYPE = atoi(token);

				token = strtok(NULL, ",");
				count++;
			}
			//CSV 공백찾기
			nCEQ_ID_CSV = szGen_CEQID.Find(' ');
			if (nCEQ_ID_CSV > -1)
			{
				szGen_CEQID.Replace(_T(" "), _T(""));
			}
			//여기에 데이터 추가 하는 부분 !!!
			if (nGen_TYPE == 0)
			{
				nGen_TYPE = 5;
			}
			if (dGen_ITR_X == 0)
			{
				dGen_ITR_X = 6;
			}
			if (nGen_MACH_TYPE == 0)
			{
				nGen_MACH_TYPE = 1;
			}
			nCheck_Point = GenCSV_Insert_ADD(nGen_Index, szGen_Name, dGen_CAP_kw, szGEN_Connect_NdName, nGen_TREXCL, nGen_ITR_WDC, nGen_TYPE, dGen_ITR_X, nGen_MACH_TYPE, szGenunit_NM, dGenunit_CAP_KW, szGenunit_NO, nGen_Check, szGen_CEQID);

			if (nCheck_Point == 2222)
			{
				szGen_Overlap[nIndexGen].Format(_T("[오류][중복]-%s\n"), szGen_Name);
				szGen_Overlap_Box = szGen_Overlap_Box + szGen_Overlap[nIndexGen];
				nIndexGen++;
			}
			if (nCheck_Point == 9999)
			{
				szGen_Overlap[nIndexGen].Format(_T("[오류][연결없음]-%s\n"), szGen_Name);
				szGen_Overlap_Box.Format(_T("%s%s"), szGen_Overlap_Box, szGen_Overlap[nIndexGen]);
				nIndexGen++;
			}	
			if (nCheck_Point == 8888)
			{
				szGen_Overlap[nIndexGen].Format(_T("[오류][추가/수정]-%s\n"), szGen_Name);
				szGen_Overlap_Box.Format(_T("%s%s"), szGen_Overlap_Box, szGen_Overlap[nIndexGen]);
				nIndexGen++;
			}//이름 확인부터 
			if (nCheck_Point == 1111)
			{
				// 				szGen_Overlap[nIndexGen].Format(_T("[완료]-%s\n"), szGen_Name);
				// 				szGen_Overlap_Box.Format(_T("%s%s"), szGen_Overlap_Box, szGen_Overlap[nIndexGen]);
				// 				nIndexGen++;
			}

			if (nIndexGen == 99)
			{
				break;
			}
		}
		fclose(stream);
		if (nIndexGen == 99)
		{
			AfxMessageBox(_T("[오류] 100개이상 에러가 있습니다."));

		}
		if (nIndexGen != 0 && nIndexGen != 99)
		{

			AfxMessageBox(szGen_Overlap_Box);
		}
		if (nIndexGen == 0)
		{

			AfxMessageBox(_T("[완료]"));
		}

	}
	//여기서 확인 

}

int CDate_Csv_File_Dlg::GenCSV_Insert_ADD(int nGen_Index, CString szGen_Name, double dGen_CAP_kw, CString szGEN_Connect_NdName,
	int nGen_TREXCL, int nGen_ITR_WDC, int nGen_TYPE, double dGen_ITR_X, int nGen_MACH_TYPE, CString szGenunit_NM, double dGenunit_CAP_KW, CString szGenunit_NO,int nGen_Check, CString szGen_CEQID)
{
	int m_nJUNCTION_CSVID = 0;
	int m_nGEN_CSVID = 0;
	int nCheck_Point = 9999;
	CString stKASIM_NM;
	CString strType;	
	CString stGENUNIT_CUSTOMER_NO;
	int nGENuNIT_Check = 0;
	unsigned long long	ullCEQID(0U);
	int nGenNDID;
	//20220928 신규 수정
	int nCount_GENUNIT_table = theAppDataMng->GetTableRealCount(_T("GENUNIT_STA"));
	nCount_GENUNIT_table = nCount_GENUNIT_table + 1;
	CString stGEN_UNIT_CEQID;
	stGEN_UNIT_CEQID.Format(_T("999936%08d"), nCount_GENUNIT_table);

	int i = 0;
	int nCount_ND_table = theAppDataMng->GetTableRealCount(_T("ND_STA"));
	for (i = 1; i <= (int)nCount_ND_table; i++)
	{
		stKASIM_NM = CA2W(GETSTRING(("ND_STA"), ("ND_NM"), i)).m_psz;
		if (stKASIM_NM == szGEN_Connect_NdName)
		{
			m_nJUNCTION_CSVID = i;
			nCheck_Point = 5555;
			break;
		}
	}
	if (nCheck_Point == 9999) //노드가 없다면 이건 연결할수 없다 오류!
	{
		nCheck_Point = 9999;
		return nCheck_Point;
	}
	//일단 5555 은 연결된 ND가 있다!!! //CEQ ID를 통해 설비를 확인하자!!
	if (nCheck_Point == 5555 )
	{
		if (szGen_CEQID == "0")
		{
			int nCount_GEN_table = theAppDataMng->GetTableRealCount(_T("GEN_STA"));
			for (i = 1; i <= (int)nCount_GEN_table; i++)
			{
				stKASIM_NM = CA2W(GETSTRING(("GEN_STA"), ("GEN_NM"), i)).m_psz;
				if (stKASIM_NM == szGen_Name)
				{
					m_nGEN_CSVID = i;
					nGenNDID = GETVALUE(int, _T("GEN_STA"), _T("GEN_II_ND"), i);

					ullCEQID = GETVALUE(unsigned long long, _T("GEN_STA"), _T("GEN_CEQID"), i);
					szGen_CEQID.Format(_T("%lld"), ullCEQID);

					nCheck_Point = 4444;
					break;
				}
				else
				{
					nCheck_Point = 3333;
				}
			}
		}
		else
		{
			int nCount_GEN_table = theAppDataMng->GetTableRealCount(_T("GEN_STA"));
			for (i = 1; i <= (int)nCount_GEN_table; i++)
			{
				ullCEQID = GETVALUE(unsigned long long, _T("GEN_STA"), _T("GEN_CEQID"), i);
				stKASIM_NM.Format(_T("%lld"), ullCEQID);
				if (stKASIM_NM == szGen_CEQID)
				{
					m_nGEN_CSVID = i;
					nGenNDID = GETVALUE(int, _T("GEN_STA"), _T("GEN_II_ND"), i);
					nCheck_Point = 4444;
					break;
				}
				else
				{
					nCheck_Point = 3333;
				}
			}
		}
	}
	//nCheck_Point 3333 이라는건 신규이다!!
	//CEQID를 찾는다!!! 그럼 이건 있는설비이다!
// 	if (nCheck_Point == 4444 && nGen_Check == 0) //신규설비인데? 이건 입력값을잘 못넣은부분
// 	{
// 		nCheck_Point = 8888;
// 		return nCheck_Point;
// 	}
	if (nGen_Check == 1) //검증!
	{

	}

	if(nCheck_Point == 4444) //GEN 중복이 있다
	{
		if (nGen_Check == 1 )
		{
			int nCount_GENUNIT_table = theAppDataMng->GetTableRealCount(_T("GENUNIT_STA"));
			nCount_GENUNIT_table++;
			Set_NEW_InitData_KASIM_GEN_STA_Editor(m_nGEN_CSVID, szGen_Name, dGen_CAP_kw, nGen_TREXCL, nGen_ITR_WDC, nGen_TYPE, dGen_ITR_X, nGen_MACH_TYPE, nGenNDID);
			Set_NEW_InitData_KASIM_GENUNIT_STA(szGenunit_NM, szGenunit_NO, m_nGEN_CSVID, dGenunit_CAP_KW, nCount_GENUNIT_table, stGEN_UNIT_CEQID, szGen_CEQID);
			return nCheck_Point;
		}
		else if (nGen_Check == 0)
		{
			int nCount_GENUNIT_table = theAppDataMng->GetTableRealCount(_T("GENUNIT_STA"));
			for (i = 1; i <= (int)nCount_GENUNIT_table; i++)
			{
				stGENUNIT_CUSTOMER_NO = GETSTRING(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), i);
				if (szGenunit_NO == stGENUNIT_CUSTOMER_NO)
				{
					Set_NEW_InitData_KASIM_GEN_STA_Editor(m_nGEN_CSVID, szGen_Name, dGen_CAP_kw, nGen_TREXCL, nGen_ITR_WDC, nGen_TYPE, dGen_ITR_X, nGen_MACH_TYPE, nGenNDID);
					Set_NEW_InitData_KASIM_GENUNIT_STA(szGenunit_NM, szGenunit_NO, m_nGEN_CSVID, dGenunit_CAP_KW, i, stGEN_UNIT_CEQID, szGen_CEQID);
					nGENuNIT_Check = 9999; //체크 포인트 
					break;
				}
			} 
			if (nGENuNIT_Check = 9999)
			{
				return nCheck_Point;
			}
			else
			{
				nCheck_Point = 8888;
				return nCheck_Point;
			}
		}
		else
		{
			nCheck_Point = 8888;
			return nCheck_Point;
		}


	}

	if (nCheck_Point == 3333 && nGen_Check == 1)//이건 완전 신규 데이터
	{
		int nCount_GEN_table = theAppDataMng->GetTableRealCount(_T("GEN_STA"));
		nCount_GEN_table = nCount_GEN_table + 1;
		CString stCEQID, stNM;
		stCEQID.Format(_T("999937%08d"), nCount_GEN_table);

		//BR부분입력
		int nCount_LNSEC_table = theAppDataMng->GetTableRealCount(_T("LNSEC_STA"));
		int nCount_BR_table = theAppDataMng->GetTableRealCount(_T("BR_STA"));
		int nCount_IJ_table = theAppDataMng->GetTableRealCount(_T("IJ_STA"));
		int nCount_LD_table = theAppDataMng->GetTableRealCount(_T("LD_STA"));
		int nCount_ND_table = theAppDataMng->GetTableRealCount(_T("ND_STA"));

		nCount_LNSEC_table++;
		nCount_BR_table++;
		nCount_IJ_table++;
		nCount_LD_table++;
		nCount_ND_table++;

		Set_NEW_InitData_KASIM(nCount_LNSEC_table, nCount_BR_table, nCount_IJ_table, nCount_LD_table, m_nJUNCTION_CSVID, nCount_ND_table);
		
		//GEN 입력
		int nCount_GENtable = theAppDataMng->GetTableRealCount(_T("GEN_STA"));
		int nCount_GND_table = theAppDataMng->GetTableRealCount(_T("GND_STA"));
		int nCount_PRDE_table = theAppDataMng->GetTableRealCount(_T("PRDE_STA"));
		int nCount_GENUNIT_table = theAppDataMng->GetTableRealCount(_T("GENUNIT_STA"));

		nCount_GENtable++;
		nCount_GND_table++;
		nCount_IJ_table++;
		nCount_PRDE_table++;
		nCount_GENUNIT_table++;

		Set_NEW_InitData_KASIM_GEN_STA(szGen_Name, stCEQID, nCount_GENtable, nCount_ND_table, nCount_IJ_table, nCount_PRDE_table, nGen_TYPE, dGen_CAP_kw, nGen_TREXCL, nCount_GENUNIT_table);
		Set_NEW_InitData_KASIM_GEN_DYN_MEA(nCount_GENtable);
		Set_NEW_InitData_KASIM_GEN_DYN_UIN(nCount_GENtable, dGen_CAP_kw, nGen_ITR_WDC, dGen_ITR_X, nGen_MACH_TYPE);
		Set_NEW_InitData_KASIM_GEN_DYN_VVOO(nCount_GENtable);
		Set_NEW_InitData_KASIM_GEN_DYN_PDVRO(nCount_GENtable);

		Set_NEW_InitData_KASIM_IJ(szGen_Name, nCount_IJ_table, nCount_ND_table, 4);
		Set_NEW_InitData_KASIM_ND(szGen_Name, stCEQID, nCount_GENtable, nCount_ND_table, nCount_ND_table, nCount_IJ_table, 2, 3); //1.cbsw 2.lnsec 3.gen 4.hvcus 5.junction
		Set_NEW_InitData_KASIM_PRDE(szGen_Name, nCount_PRDE_table);
		//GENUNIT_STA
		Set_NEW_InitData_KASIM_GENUNIT_STA(szGenunit_NM, szGenunit_NO, nCount_GENtable, dGenunit_CAP_KW, nCount_GENUNIT_table, stGEN_UNIT_CEQID, stCEQID);

		return nCheck_Point;
	}
	else
	{
		//이건 나오면 안되는 부분인다!!이것도 오류다
		nCheck_Point = 8888;
		return nCheck_Point;
	}
	return nCheck_Point;
}

//
void CDate_Csv_File_Dlg::GenCSV_Editor_Download()
{
	int i;
	CString strSQL;
	FILE* stream;
	CString szRoute, strPath;

	int m_nGEN_CSVID = 0;
	CString stKASIM_GEN_NM, stKASIM_GEN_CEQ, stKASIM_ND_NM;
	CString strName;
	float fGENUNIT_CAP_KW;
	int nGEN_ND_ID;
	int nGEN_TREXCL, nGEN_ITR_WDC, nGEN_TYPE, nGEN_MACH_TYPE, nGEN_AVR;
	float fGEN_ITR_X, fGEN_DERAVMVUBREF, fGEN_DERAVMVLBREF, fGEN_DERAVMQVRATIO;


	unsigned long long	ullCEQID(0U);

	int nCount = 1;
	int nGENUNIT_STACount = 0;
	//
	int nBR_ID, nDL_ID, nMTR_ID, nSS_ID, nBOF_ID;
	CString szBOF_NM, szSS_NM, szMTR_NM, szDL_NM;
	//
	int nGENUNIT_CAP_KW_Count = 0;
	int nDlIdx = 0;
	CString szGENUNIT_NM, szGENUNIT_CUSTOMER_NO;
	double dGENUNIT_CAP_KW;
	//
	int nBR_Fnd, nBR_Tnd;
	nBR_Fnd = nBR_Tnd = 0;
	int nND_Fbr, nND_Tbr;
	nND_Fbr = nND_Tbr = 0;

	strName.Format(_T("GEN_Download.csv"));
	szRoute.Format(_T("\\Config"));

	CFileDialog FileDlg(FALSE, _T("csv"), strName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("KASIM Data File(*.csv)|*.csv"));

	strPath = MyPath() + szRoute;
	FileDlg.m_pOFN->lpstrInitialDir = (LPCWSTR)strPath;

	if (FileDlg.DoModal() != IDOK)
		return;

	CString strFilePath = FileDlg.GetPathName();
	CString strFileName = FileDlg.GetFileName();

	int nPathLen = strFilePath.GetLength();
	int nFileLen = strFileName.GetLength();
	strFilePath.Delete(nPathLen - nFileLen, nFileLen);

	szRoute.Format(_T("%s%s"), strFilePath, FileDlg.GetFileTitle() + _T(".csv"));

	stream = _wfopen(szRoute, L"w+");
	fwprintf(stream, L"순번,지사,변전소,MTR,선로,GEN_CEQ,발전기명,발전기용량(kW),GENUNIT_NM, GENUNIT_CAP_KW, GENUNIT_CUSTOMER_NO, 연계점(전주 번호),분산전원 연계변압기 전용여부(1:특고압 전용 2: 저압 전용 3: 저압 공용),연계 변압기 결선(1:Ygyg 2:Ygd 3:Dyg 4: Yd),	발전기 종류 (1:무한모선 2: 디젤 3:ESS 4:풍력 5:태양광6:바이오),연계 변압기정상분X(%),발전기유형(1:인버터 2:동기기 3:유도기 4:고압동기기),전압제어가능여부,전압상한(pu),전압하한(pu),QVratio(%/Mvar)\n");

	int nCount_GEN_table = theAppDataMng->GetTableRealCount(_T("GEN_STA"));
	for (int i = 1; i <= (int)nCount_GEN_table; i++)
	{
		m_nGEN_CSVID = i;
		stKASIM_GEN_NM = CA2W(GETSTRING(("GEN_STA"), ("GEN_NM"), m_nGEN_CSVID)).m_psz;



		ullCEQID = GETVALUE(unsigned long long, _T("GEN_STA"), _T("GEN_CEQID"), m_nGEN_CSVID);
		stKASIM_GEN_CEQ.Format(_T("%lld"), ullCEQID);

		fGENUNIT_CAP_KW = GETVALUE(double, _T("GEN_STA"), _T("GEN_MWLMMX"), m_nGEN_CSVID);
		nGEN_ND_ID = GETVALUE(int, _T("GEN_STA"), _T("GEN_II_ND"), m_nGEN_CSVID);
		//
		nND_Fbr = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FBR"), nGEN_ND_ID);
		nND_Tbr = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TBR"), nGEN_ND_ID);
		if (nND_Fbr != 0)
		{
			nBR_Fnd = GETVALUE(int, _T("BR_STA"), _T("BR_II_FND"), nND_Fbr);
			nBR_Tnd = GETVALUE(int, _T("BR_STA"), _T("BR_II_TND"), nND_Fbr);
			if (nGEN_ND_ID == nBR_Fnd) //다른 아이디값
			{
				stKASIM_ND_NM = CA2W(GETSTRING(("nd_sta"), ("nd_nm"), nBR_Tnd)).m_psz;
			}
			if (nGEN_ND_ID == nBR_Tnd) //다른 아이디값
			{
				stKASIM_ND_NM = CA2W(GETSTRING(("nd_sta"), ("nd_nm"), nBR_Fnd)).m_psz;
			}
		}
		if (nND_Tbr != 0)
		{
			nBR_Fnd = GETVALUE(int, _T("BR_STA"), _T("BR_II_FND"), nND_Tbr);
			nBR_Tnd = GETVALUE(int, _T("BR_STA"), _T("BR_II_TND"), nND_Tbr);
			if (nGEN_ND_ID == nBR_Fnd) //다른 아이디값
			{
				stKASIM_ND_NM = CA2W(GETSTRING(("nd_sta"), ("nd_nm"), nBR_Tnd)).m_psz;
			}
			if (nGEN_ND_ID == nBR_Tnd) //다른 아이디값
			{
				stKASIM_ND_NM = CA2W(GETSTRING(("nd_sta"), ("nd_nm"), nBR_Fnd)).m_psz;
			}
		}
		nGEN_TREXCL = GETVALUE(int, _T("GEN_STA"), _T("GEN_TREXCL"), m_nGEN_CSVID);
		nGEN_ITR_WDC = GETVALUE(int, _T("GEN_DYN_UIN"), _T("GEN_ITR_WDC"), m_nGEN_CSVID);
		nGEN_TYPE = GETVALUE(int, _T("GEN_STA"), _T("GEN_TYPE"), m_nGEN_CSVID);
		fGEN_ITR_X = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_ITR_X"), m_nGEN_CSVID);
		nGEN_MACH_TYPE = GETVALUE(int, _T("GEN_DYN_UIN"), _T("GEN_MACH_TYPE"), m_nGEN_CSVID);
		nGEN_AVR = GETVALUE(int, _T("GEN_DYN_UIN"), _T("GEN_AVR"), m_nGEN_CSVID);

		fGEN_DERAVMVUBREF = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_DERAVMVUBREF"), m_nGEN_CSVID);
		fGEN_DERAVMVLBREF = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_DERAVMVLBREF"), m_nGEN_CSVID);
		fGEN_DERAVMQVRATIO = GETVALUE(double, _T("GEN_DYN_UIN"), _T("GEN_DERAVMQVRATIO"), m_nGEN_CSVID);

		//
		nBR_ID = 0;
		nDL_ID = 0;
		nBR_ID = GETVALUE(int, _T("nd_sta"), _T("ND_HI_TBR"), nGEN_ND_ID);
		if (nBR_ID == 0)
		{
			nBR_ID = GETVALUE(int, _T("nd_sta"), _T("ND_HI_FBR"), nGEN_ND_ID);
		}
		if (nBR_ID != 0) //DL찾기
		{
			nDL_ID = GETVALUE(int, _T("BR_STA"), _T("BR_II_DL"), nBR_ID);
		}
		if (nDL_ID != 0)
		{
			szDL_NM = CA2W(GETSTRING(("DL_STA"), ("DL_NM"), nDL_ID)).m_psz;
			nMTR_ID = GETVALUE(int, _T("DL_STA"), _T("DL_II_MTR"), nDL_ID);
			nBOF_ID = GETVALUE(int, _T("DL_STA"), _T("DL_II_BOF"), nDL_ID);
			if (nMTR_ID != 0)
			{
				szMTR_NM = CA2W(GETSTRING(("MTR_STA"), ("MTR_NM"), nMTR_ID)).m_psz;
				nSS_ID = GETVALUE(int, _T("MTR_STA"), _T("MTR_II_SS"), nMTR_ID);

				if (nSS_ID != 0)
				{
					szSS_NM = CA2W(GETSTRING(("SS_STA"), ("SS_NM"), nSS_ID)).m_psz;
				}
			}
			if (nBOF_ID != 0)
			{
				szBOF_NM = CA2W(GETSTRING(("BOF_STA"), ("BOF_NM"), nBOF_ID)).m_psz;
			}
		}
		//
		nDlIdx = 0;
		//
		nGENUNIT_STACount = theAppDataMng->GetTableRealCount(_T("GENUNIT_STA"));
		for (int i = 1; i <= nGENUNIT_STACount; i++)
		{
			nDlIdx = GETVALUE(int, _T("GENUNIT_STA"), _T("GENUNIT_II_GEN"), i);
			if (nDlIdx == 0)											continue;
			if (nDlIdx != m_nGEN_CSVID)									continue;

			szGENUNIT_NM = GETSTRING(_T("GENUNIT_STA"), _T("GENUNIT_NM"), i);
			szGENUNIT_CUSTOMER_NO = GETSTRING(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), i);
			dGENUNIT_CAP_KW = GETVALUE(double, _T("GENUNIT_STA"), _T("GENUNIT_CAP_KW"), i);

			if (szGENUNIT_CUSTOMER_NO.IsEmpty())
			{
				szGENUNIT_CUSTOMER_NO.Format(_T("0"));
			}
			//d입력
			fwprintf(stream, _T("%d,%s,%s,%s,%s,%s,%s,%.4f,%s,%.4f,%s,%s,%d,%d,%d,%.4f,%d,%d,%.4f,%.4f,%.4f\n")
				, nCount
				, szBOF_NM
				, szSS_NM
				, szMTR_NM
				, szDL_NM
				, stKASIM_GEN_CEQ
				, stKASIM_GEN_NM
				, fGENUNIT_CAP_KW * 1000
				, szGENUNIT_NM
				, dGENUNIT_CAP_KW
				, szGENUNIT_CUSTOMER_NO
				, stKASIM_ND_NM
				, nGEN_TREXCL
				, nGEN_ITR_WDC
				, nGEN_TYPE
				, fGEN_ITR_X
				, nGEN_MACH_TYPE
				, nGEN_AVR
				, fGEN_DERAVMVUBREF
				, fGEN_DERAVMVLBREF
				, fGEN_DERAVMQVRATIO
			);
			nCount++;

		}
		//1순번--
		//2지사
		//3변전소
		//4MTR
		//5선로
		// CEQ!!
		//6발전기명--
		//7발전기 용량(kW)	--
		//8연계점(전주 번호)	
		//9분산전원 연계변압기 전용여부(1:특고압 전용 2: 저압 전용 3: 저압 공용)	
		//10연계 변압기 결선(1:Ygyg 2:Ygd 3:Dyg 4: Yd)	
		//11발전기 종류 (1:무한모선 2: 디젤 3:ESS 4:풍력 5:태양광 6:바이오)	
		//12연계 변압기 정상분 X(%)	
		//13발전기 유형(1:인버터 2:동기기 3:유도기 4:고압동기기)	
		//14전압 제어 가능여부	
		//15전압상한(pu)	
		//16전압하한(pu)	
		//17QV ratio(%/Mvar)
	}
	fclose(stream);

	AfxMessageBox(_T("[완료]"));
}

void CDate_Csv_File_Dlg::GenCSV_Editor_Upload()
{
	CString		strPath, strTitleName, strFilePath, strFileName;
	FILE*		stream = NULL;
	char		chBuffer[4096] = { 0x00, };
	char		*token = NULL;
	int			count = 0;
	int			nCheck_Point = 0;
	//
	CString		szGEN_OFFICE_NM;
	int			nGen_Index;				//발전기csv index
	int			nGen_TREXCL;			//발전기 연계변압기 여부 없으면 기봅값 1 (1:특고압 전용, 2: 저압 전용3: 저압 공용)
	int			nGen_ITR_WDC;			//발전기 연계변압기 결선 기본값2 (1:Ygyg, 2:Ygd 3:Dyg 4: Yd)
	int			nGen_TYPE;				//발전기 종류(1:무한모선, 2 : 디젤, 3 : ESS, 4 : 풍력, 5 : 태양광, 6 : 바이오)
	int			nGen_MACH_TYPE;			//발전기 유형(1:인버터, 2:동기기, 3:유도기, 4:고압동기기)
	double		dGen_CAP_kw;			//발전기용량
	double		dGen_ITR_X;				//발전기용량 연계 변압기 정상분 X(%)
	CString		szName;
	CString		szGen_Name;				//발전기 이름
	CString		szGEN_Connect_NdName;   //발전기 연계 노드 이름 //이걸로 데이터 연결점 찾는 부분
	CString		szGen_CEQ;

	int			nGEN_AVR;
	double		dGEN_DERAVMVUBREF;
	double		dGEN_DERAVMVLBREF;
	double		dGEN_DERAVMQVRATIO;

	CString szGENUNIT_NM;
	double dGENUNIT_CAP_KW;
	CString szGENUNIT_CUSTOMER_NO;

	CString     szGen_Overlap[1000];
	CString     szGen_Overlap_Box;

	CString		szGEN_CEQID;
	CString		szBOFNM, szSSNM, szMTRNM, szDLNM;

	int nCEQ_ID_CSV = 0; //CSV 파일 공백 찾기
	int nCUSTOMER_NO_ID_CSV = 0; //CSV 파일 공백 찾기 



	for (int i = 0; i < 1000; i++)
	{
		szGen_Overlap[i].Format(_T(""));
	}
	int nIndexGen = 0;

	CFileDialog FileDlg(TRUE, _T("csv"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("KASIM Data File(*.csv)|*.csv| All Files(*.*)|*.*|"));

	CString szRoute;

	szRoute.Format(_T("\\Config"));
	strPath = (MyPath() + szRoute);

	FileDlg.m_pOFN->lpstrInitialDir = (LPCWSTR)strPath;

	if (FileDlg.DoModal() != IDOK)
		return;

	strTitleName = FileDlg.GetFileTitle();
	strFilePath = FileDlg.GetPathName();
	strFileName = FileDlg.GetFileName();

	stream = _wfopen(strFilePath, L"r+");

	// 
	if (stream != NULL)
	{
		fgets(chBuffer, sizeof(chBuffer), stream);
		while (fgets(chBuffer, sizeof(chBuffer), stream))
		{
			count = 0;
			token = strtok(chBuffer, ",");
			while (token != NULL)
			{
				if (count == 0)	nGen_Index = atoi(token);
				else if (count == 1)	szBOFNM = CA2W((token)).m_psz;
				else if (count == 2)	szSSNM = CA2W((token)).m_psz;
				else if (count == 3)	szMTRNM = CA2W((token)).m_psz;
				else if (count == 4)	szDLNM = CA2W((token)).m_psz;
				else if (count == 5)	szGEN_CEQID = CA2W((token)).m_psz;
				else if (count == 6)	szGen_Name = CA2W((token)).m_psz;
				else if (count == 7)	dGen_CAP_kw = atof(token);
				else if (count == 8)	szGENUNIT_NM = CA2W((token)).m_psz;
				else if (count == 9)	dGENUNIT_CAP_KW = atof(token);
				else if (count == 10)	szGENUNIT_CUSTOMER_NO = CA2W((token)).m_psz;
				else if (count == 11)	szGEN_Connect_NdName = CA2W((token)).m_psz;
				else if (count == 12)	nGen_TREXCL = atoi(token);
				else if (count == 13)	nGen_ITR_WDC = atoi(token);
				else if (count == 14)	nGen_TYPE = atoi(token);
				else if (count == 15)	dGen_ITR_X = atof(token);
				else if (count == 16)	nGen_MACH_TYPE = atoi(token);
				else if (count == 17)	nGEN_AVR = atoi(token);
				else if (count == 18)	dGEN_DERAVMVUBREF = atof(token);
				else if (count == 19)	dGEN_DERAVMVLBREF = atof(token);
				else if (count == 20)	dGEN_DERAVMQVRATIO = atof(token);
				//else if (count == 17)	szGen_CEQ = CA2W((token)).m_psz;

				token = strtok(NULL, ",");
				count++;
			}
			if (nIndexGen == 99)
			{
				break;
			}

 			nCEQ_ID_CSV = szGEN_CEQID.Find(' ');
			if (nCEQ_ID_CSV > -1)
			{
				szGEN_CEQID.Replace(_T(" "), _T(""));
			}
			nCUSTOMER_NO_ID_CSV = szGENUNIT_CUSTOMER_NO.Find(' ');
			if (nCUSTOMER_NO_ID_CSV > -1)
			{
				szGENUNIT_CUSTOMER_NO.Replace(_T(" "), _T(""));
			}

			GenCSV_Insert_Editor(nGen_Index, szGen_Name, dGen_CAP_kw, szGEN_Connect_NdName, nGen_TREXCL, nGen_ITR_WDC, nGen_TYPE, dGen_ITR_X, nGen_MACH_TYPE, dGEN_DERAVMVUBREF, dGEN_DERAVMVLBREF, dGEN_DERAVMQVRATIO, szGen_CEQ, nGEN_AVR , szGEN_CEQID);
			GenUnitCSV_Insert_Editor(szGENUNIT_NM, dGENUNIT_CAP_KW, szGENUNIT_CUSTOMER_NO, szGEN_CEQID , szGEN_Connect_NdName, szBOFNM, szSSNM, szMTRNM, szDLNM);
			if (m_nCheck_Gen_upload == 0)
			{
				szGen_Overlap[nIndexGen].Format(_T("[오류][입력안됨]-%s\n"), szGen_Name);
				szGen_Overlap_Box = szGen_Overlap_Box + szGen_Overlap[nIndexGen];
				nIndexGen++;
			}
		}
		fclose(stream);

		// 		if (count != 20)
		// 		{
		// 			AfxMessageBox(_T("[파읽을 잘못 읽으셨습니다. 미완료]"));
		// 		}
		if (nIndexGen == 99)
		{
			AfxMessageBox(_T("[오류] 100개이상 에러가 있습니다."));
		}
		if (nIndexGen != 0 && nIndexGen != 99)
		{
			AfxMessageBox(szGen_Overlap_Box);
		}
		// 		if (nIndexGen == 0 && count == 20)
		// 		{
		// 			AfxMessageBox(_T("[완료]"));
		// 		}
		if (nIndexGen == 0)
		{
			AfxMessageBox(_T("[완료]"));
		}

	}
	//여기서 확인 

}

void CDate_Csv_File_Dlg::GenCSV_Insert_Editor(int nGen_Index, CString szGen_Name, double dGen_CAP_kw, CString szGEN_Connect_NdName, int nGen_TREXCL, int nGen_ITR_WDC, int nGen_TYPE, double dGen_ITR_X,
	int nGen_MACH_TYPE, double		dGEN_DERAVMVUBRE, double		dGEN_DERAVMVLBREF, double		dGEN_DERAVMQVRATIO, CString szGEN_CEQ, int nGEN_AVR ,CString szGEN_CEQID)
{
	int nGEN_CSVID = 0;
	int nGEN_HI_GENUNIT;
	CString stKASIM_GENCEQ;
	CString stKASIM_CEQ;
	unsigned long long	ullCEQID(0U);
	m_nCheck_Gen_upload = 0;


	int nCount_GEN_table = theAppDataMng->GetTableRealCount(_T("GEN_STA"));
	for (int i = 1; i <= (int)nCount_GEN_table; i++)
	{
		nGEN_CSVID = i;
		ullCEQID = GETVALUE(unsigned long long, _T("GEN_STA"), _T("GEN_CEQID"), nGEN_CSVID);
		stKASIM_GENCEQ.Format(_T("%lld"), ullCEQID);
		if (stKASIM_GENCEQ == szGEN_CEQID)// && stKASIM_CEQ == szGEN_CEQ)
		{
			nGEN_HI_GENUNIT = GETVALUE(int, _T("GEN_STA"), _T("GEN_HI_GENUNIT"), nGEN_CSVID);

			PUTVALUE(_T("GEN_STA"), _T("GEN_NM"), nGEN_CSVID, (wchar_t*)szGen_Name.GetBuffer());
			PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMX"), nGEN_CSVID, (double)dGen_CAP_kw / 1000);
			PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TYPE"), nGEN_CSVID, (int)nGen_TYPE);
			PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TREXCL"), nGEN_CSVID, (int)nGen_TREXCL);

			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_WDC"), nGEN_CSVID, (int)nGen_ITR_WDC);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_X"), nGEN_CSVID, (double)dGen_ITR_X);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MACH_TYPE"), nGEN_CSVID, (int)nGen_MACH_TYPE);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_AVR"), nGEN_CSVID, (int)nGEN_AVR);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMVUBREF"), nGEN_CSVID, (double)dGEN_DERAVMVUBRE);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMVLBREF"), nGEN_CSVID, (double)dGEN_DERAVMVLBREF);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMQVRATIO"), nGEN_CSVID, (double)dGEN_DERAVMQVRATIO);
			PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_CAP"), nGEN_CSVID, (double)dGen_CAP_kw);

			m_nCheck_Gen_upload = 9999;
			break;
		}
	}
}

void CDate_Csv_File_Dlg::GenUnitCSV_Insert_Editor(CString szGENUNIT_NM, double dGENUNIT_CAP_KW, CString szGENUNIT_CUSTOMER_NO, CString szGEN_CEQID, CString szGEN_Connect_NdName, CString szBOFNM, CString szSSNM, CString szMTRNM, CString szDLNM)
{
	int nGENUNIT_STACount = 0;
	int nDlIdx = 0;
	CString szName;
	CString szCUSTOMER_NO;

	unsigned long long	ullCEQID(0U);

	//GEN 찾자!!
	int nGEN_CSVID = 0;
	CString stKASIM_GENCEQ;
	int nCount_GEN_table = theAppDataMng->GetTableRealCount(_T("GEN_STA"));
	for (int i = 1; i <= (int)nCount_GEN_table; i++)
	{
		nGEN_CSVID = i;
		ullCEQID = GETVALUE(unsigned long long, _T("GEN_STA"), _T("GEN_CEQID"), nGEN_CSVID);
		stKASIM_GENCEQ.Format(_T("%lld"), ullCEQID);

		if (stKASIM_GENCEQ == szGEN_CEQID)// && stKASIM_CEQ == szGEN_CEQ)
		{
			nGEN_CSVID = i;
			break;
		}
	}

	nGENUNIT_STACount = theAppDataMng->GetTableRealCount(_T("GENUNIT_STA"));
	for (int i = 1; i <= nGENUNIT_STACount; i++)
	{
		szCUSTOMER_NO = GETSTRING(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), i);
		if (szCUSTOMER_NO == szGENUNIT_CUSTOMER_NO)
		{
			PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_NM"), i, (wchar_t*)szGENUNIT_NM.GetBuffer());
			PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_CAP_KW"), i, (double)dGENUNIT_CAP_KW);
			//PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), i, (wchar_t*)szGENUNIT_CUSTOMER_NO.GetBuffer());
		}
	}

	//DL 변전소
	int nND_CSV_ID = 0;
	int nND_STACount = 0;
	CString szND_Name;
	int  nBR_ID = 0, nDL_ID = 0;
	int nMTR_ID = 0, nBOF_ID = 0, nSS_ID;
	
	nND_STACount = theAppDataMng->GetTableRealCount(_T("ND_STA"));
	for (int i = 1; i <= nND_STACount; i++)
	{
		nND_CSV_ID = i;
		szND_Name = GETSTRING(_T("ND_STA"), _T("ND_NM"), nND_CSV_ID);
		if (szGEN_Connect_NdName == szND_Name)
		{
			nBR_ID = GETVALUE(int, _T("nd_sta"), _T("ND_HI_TBR"), nND_CSV_ID);
			if (nBR_ID == 0)
			{
				nBR_ID = GETVALUE(int, _T("nd_sta"), _T("ND_HI_FBR"), nND_CSV_ID);
			}
			if (nBR_ID != 0) //DL찾기
			{
				nDL_ID = GETVALUE(int, _T("BR_STA"), _T("BR_II_DL"), nBR_ID);
			}
			if (nDL_ID != 0)
			{
				//
				//입력 DL이름
				PUTVALUE(_T("DL_STA"), _T("DL_NM"), nDL_ID, (wchar_t*)szDLNM.GetBuffer());
				//
				nMTR_ID = GETVALUE(int, _T("DL_STA"), _T("DL_II_MTR"), nDL_ID);
				nBOF_ID = GETVALUE(int, _T("DL_STA"), _T("DL_II_BOF"), nDL_ID);
				if (nMTR_ID != 0)
				{
					//입력 MTR
					PUTVALUE(_T("MTR_STA"), _T("MTR_NM"), nMTR_ID, (wchar_t*)szMTRNM.GetBuffer());

					nSS_ID = GETVALUE(int, _T("MTR_STA"), _T("MTR_II_SS"), nMTR_ID);

					if (nSS_ID != 0)
					{
						//입력SS
						PUTVALUE(_T("SS_STA"), _T("SS_NM"), nSS_ID, (wchar_t*)szSSNM.GetBuffer());
					}
				}
				if (nBOF_ID != 0)
				{
					//입력 BOF
					PUTVALUE(_T("BOF_STA"), _T("BOF_NM"), nBOF_ID, (wchar_t*)szBOFNM.GetBuffer());
				}
			}

		}
	}

}

//추후 입력
void CDate_Csv_File_Dlg::RECLOSERCSV_Editor_Download()
{

}
//추후 입력
void CDate_Csv_File_Dlg::RECLOSERCSV_Editor_Upload()
{
	
}

//여기는 KASIM 입력하는 부분입니다.
//BR
void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM(int nLNSECID, int nBRID, int nIJID, int nLDID, int nFnd, int nTnd)
{
	//선작업
	CString stCEQID, stKASIM_NM;
	stCEQID.Format(_T("999951%08d"), nLNSECID);
	stKASIM_NM.Format(_T("LNSEC%08d"), nLNSECID);

	int nIJ_WhileID = 0, nBR_II_EQU = 0, nIJEQU = 0, nIJEQUTY = 0;
	//
	int nGBR_II_EQUTY = 0, nBR_WhileID = nBRID;

	while (nBR_II_EQU == 0)
	{
		if (nBRID == 999999)
		{
			break;
		}
		if (nBR_WhileID == 1)
		{
			nBR_II_EQU = 1;
			break;
		}
		nGBR_II_EQUTY = GETVALUE(int, _T("gbr_sta"), _T("GBR_II_EQUTY"), nBR_WhileID - 1);
		if (nGBR_II_EQUTY == 1)
		{
			nBR_II_EQU = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equ"), nBR_WhileID - 1);
			nBR_II_EQU = nBR_II_EQU + 1;
			break;
		}
		else
		{
			nBR_WhileID = nBR_WhileID - 1;
		}
	}
	//
//LNSEC_STA
	PUTVALUE(_T("LNSEC_STA"), _T("LNSEC_NM"), nLNSECID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("LNSEC_STA"), _T("LNSEC_CEQID"), nLNSECID, (unsigned long long)_wtoll(stCEQID));
	PUTVALUE(_T("LNSEC_STA"), _T("LNSEC_II_BR"), nLNSECID, (int)nBRID);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_INNERPOLE"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_FPOLE"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_TPOLE"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_HI_INNERSEC"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_PRIVAT"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_TYPE_ID"), nLNSECID, (int)1);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_LENGTH"), nLNSECID, (double)0.1);
	PUTDOUBLE2VALUE(_T("LNSEC_STA"), _T("LNSEC_CONSTYPE"), nLNSECID, (int)0);
	//LNSEC_DYN_UIN
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_UIN"), _T("LNSEC_SW_FOR_CONST"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_UIN"), _T("LNSEC_HIS_NOTSRCH"), nLNSECID, (int)0);
	//LNSEC_DYN_NCPO
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_NCPO"), _T("LNSEC_DEAD"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_NCPO"), _T("LNSEC_II_ISL"), nLNSECID, (int)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_NCPO"), _T("LNSEC_II_DL"), nLNSECID, (int)0);
	//LNSEC_DYN_RPFO
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PLOADMW"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PLOADMVAR"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PGENMW"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_3PGENMVAR"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PALOADMW"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PBLOADMW"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PCLOADMW"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PALOADMAR"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PBLOADMAR"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PCLOADMAR"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PARPFKV"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PBRPFKV"), nLNSECID, (double)0);
	PUTDOUBLE2VALUE(_T("LNSEC_DYN_RPFO"), _T("LNSEC_PCRPFKV"), nLNSECID, (double)0);
	//BR
	PUTVALUE(_T("BR_STA"), _T("BR_NM"), nBRID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_EQU"), nBRID, (int)nBR_II_EQU);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_FND"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_FND"), nBRID, (int)nFnd);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_TND"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_TND"), nBRID, (int)nTnd);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSR"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSX"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSG"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_POSB"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERR"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERX"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERG"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_ZERB"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_NORLM"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_EMRLM"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_GBR"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_GBR"), nBRID, (int)nBRID);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_II_DL"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("BR_STA"), _T("BR_SI_DL"), nBRID, (int)0);
	//GBR
	PUTVALUE(_T("GBR_STA"), _T("GBR_NM"), nBRID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_EQU"), nBRID, (int)nBR_II_EQU);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_SI_FGND"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_FGND"), nBRID, (int)nFnd);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_SI_TGND"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_TGND"), nBRID, (int)nTnd);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSR"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSX"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSG"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_POSB"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERR"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERX"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERG"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_ZERB"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_HI_BR"), nBRID, (int)nBRID);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_SI_EQUTY"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_STA"), _T("GBR_II_EQUTY"), nBRID, (int)1); //lnsec은 
	//GBR_DYN_UIN
	PUTDOUBLE2VALUE(_T("GBR_DYN_UIN"), _T("GBR_MORFLAG"), nBRID, (int)1);
	PUTDOUBLE2VALUE(_T("GBR_DYN_UIN"), _T("GBR_SCAFLAG"), nBRID, (int)1);
	//GBR_DYN_SCAO
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PA_C"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PB_C"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PC_C"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_SCAO"), _T("GBR_FLT_PN_C"), nBRID, (double)0);
	//GBR_DYN_NCPO
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_SI_FBS"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_SI_TBS"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_II_FBS"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_II_TBS"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_FBSSTAT"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_TBSSTAT"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_DEAD"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAG22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PAB22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBG22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PBB22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCG22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_PCB22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB11"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERG22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_ZERB22"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_NCPO"), _T("GBR_II_OUTCMP"), nBRID, (int)0);
	//GBR_DYN_RPFO
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PARPFMVAR21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PBRPFMVAR21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_RPFO"), _T("GBR_PCRPFMVAR21"), nBRID, (double)0);
	//GBR_DYN_VVOO
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PAVVOMVAR21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PBVVOMVAR21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMW12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMVAR12"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMW21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_PCVVOMVAR21"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_MVA"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFPS"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFMVA"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFMW"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISRPFMVAR"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOPS"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOMVA"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOMW"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOO"), _T("GBR_DISVVOMVAR"), nBRID, (double)0);
	//GBR_DYN_AV
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIONW"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIORECV"), nBRID, (int)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIOLM"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIOMVA"), nBRID, (double)0);
	PUTDOUBLE2VALUE(_T("GBR_DYN_AV"), _T("GBR_VIOPER"), nBRID, (double)0);
	//GBR_DYN_VVOAV
	PUTDOUBLE2VALUE(_T("GBR_DYN_VVOAV"), _T("GBR_VVORECFLAG"), nBRID, (int)0);

	nIJ_WhileID = nIJID; //특별하게 저장
	while (nIJEQU == 0)
	{
		if (nIJID == 999999)
		{
			break;
		}
		if (nIJ_WhileID == 1)
		{
			nIJEQU = 1;
			break;
		}
		nIJEQUTY = GETVALUE(int, _T("IJ_STA"), _T("IJ_II_EQUTY"), nIJ_WhileID - 1);
		if (nIJEQUTY == 6)
		{
			nIJEQU = GETVALUE(int, _T("IJ_STA"), _T("IJ_II_EQU"), nIJ_WhileID - 1);
			nIJEQU = nIJEQU + 1;
			break;
		}
		else
		{
			nIJ_WhileID = nIJ_WhileID - 1;
		}
	}
	//IJ_STA
	PUTVALUE(_T("IJ_STA"), _T("IJ_NM"), nIJID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_EQUTY"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_EQUTY"), nIJID, (int)6);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_EQU"), nIJID, (int)nIJEQU);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_GND"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_GND"), nIJID, (int)nTnd);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_DL"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_DL"), nIJID, (int)0);
	//IJ_DYN_UIN
	PUTDOUBLE2VALUE(_T("IJ_DYN_UIN"), _T("IJ_SOCMAXORDER"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_UIN"), _T("IJ_SOCMINORDER"), nIJID, (int)0);
	//IJ_DYN_NCPO
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_SI_BS"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_II_BS"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_DEAD"), nIJID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_BSSTAT"), nIJID, (int)0);
	//IJ_DYN_MEA
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_3PMEAMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_3PMEAMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PAMEAMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PAMEAMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PBMEAMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PBMEAMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PCMEAMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PCMEAMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_MEAFLAG"), nIJID, (int)0);
	//IJ_DYN_RPFO
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PARPFMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PARPFMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PBRPFMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PBRPFMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PCRPFMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PCRPFMVAR"), nIJID, (double)0);
	//IJ_DYN_VVOO
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PAVVOMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PAVVOMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PBVVOMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PBVVOMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PCVVOMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PCVVOMVAR"), nIJID, (double)0);
	//IJ_DYN_DLEO
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PAGENESTMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PBGENESTMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PCGENESTMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PAGENESTMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PBGENESTMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PCGENESTMVAR"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_3PGENESTMW"), nIJID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_3PGENESTMVAR"), nIJID, (double)0);
	//LD_STA
	PUTVALUE(_T("LD_STA"), _T("LD_NM"), nLDID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_SI_GND"), nLDID, (int)0);
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_GND"), nLDID, (int)nTnd);
	PUTDOUBLE2VALUE(_T("LD_STA"), _T("LD_II_IJ"), nLDID, (int)nIJID);
	//LD_DYN_UIN
	PUTDOUBLE2VALUE(_T("LD_DYN_UIN"), _T("LD_DIV"), nLDID, (double)0);
}


//GEN
void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_GEN_STA_Editor(int nGen_Index, CString szGen_Name, double dGen_CAP_kw, int nGen_TREXCL, int nGen_ITR_WDC, int nGen_TYPE, int dGen_ITR_X, int nGen_MACH_TYPE, int nNDID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//
	PUTVALUE(_T("ND_STA"), _T("ND_NM"), nNDID, (wchar_t*)szGen_Name.GetBuffer());
	PUTVALUE(_T("GND_STA"), _T("GND_NM"), nNDID, (wchar_t*)szGen_Name.GetBuffer());
	//GEN_STA
	PUTVALUE(_T("GEN_STA"), _T("GEN_NM"), nGen_Index, (wchar_t*)szGen_Name.GetBuffer());
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMX"), nGen_Index, (double)dGen_CAP_kw/1000);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TYPE"), nGen_Index, (int)nGen_TYPE);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TREXCL"), nGen_Index, (int)nGen_TREXCL);

	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_CAP"), nGen_Index, (double)dGen_CAP_kw);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_X"), nGen_Index, (double)dGen_ITR_X);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_WDC"), nGen_Index, (int)nGen_ITR_WDC);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MACH_TYPE"), nGen_Index, (int)nGen_MACH_TYPE);
}

void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_GENUNIT_STA(CString stKASIM_NM, CString stGENUNIT_CUSTOMER_NO, int nID, double dGEN_MWLMMX, int nGENUNITID, CString stGEN_UNIT_CEQID, CString stGEN_CEQID)
{
	CString stNULL;
	stNULL.Format(_T(""));

	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_NM"), nGENUNITID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_II_GEN"), nGENUNITID, (int)nID);
	PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_SI_GEN"), nGENUNITID, (int)0);
	PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_CAP_KW"), nGENUNITID, (double)dGEN_MWLMMX);
	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_CEQID"), nGENUNITID, (unsigned long long)_wtoll(stGEN_UNIT_CEQID));
	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_CONNECT_CEQID"), nGENUNITID, (unsigned long long)_wtoll(stGEN_CEQID));

	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NO"), nGENUNITID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NM"), nGENUNITID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), nGENUNITID, (wchar_t*)stGENUNIT_CUSTOMER_NO.GetBuffer());

}

void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_GEN_STA(CString stKASIM_NM, CString stCEQID, int nID, int nNDID, int nIJID, int nPRDEID, int nGenType, double dGEN_MWLMMX, int nGEN_TREXCL, int nGENUNITID)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//GEN_STA
	PUTVALUE(_T("GEN_STA"), _T("GEN_NM"), nID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTVALUE(_T("GEN_STA"), _T("GEN_CEQID"), nID, (unsigned long long)_wtoll(stCEQID));
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_SI_ND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_ND"), nID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_SI_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_GND"), nID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_IJ"), nID, (int)nIJID);
	if (nGenType == 1) //무한모선이면
	{
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_NAMKV"), nID, (double)154);
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMX"), nID, (double)0.01);
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TYPE"), nID, (int)nGenType);
	}
	else
	{
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_NAMKV"), nID, (double)22.9);
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMX"), nID, (double)dGEN_MWLMMX/1000);
		PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TYPE"), nID, (int)nGenType);
	}

	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MWLMMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MVARLMMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MVARLMMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_R"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_STX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_SSX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_VOL_CLS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_CONND"), nID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_CONNDREP"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_CONTYPE"), nID, (int)7);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_NOOFP"), nID, (int)4);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_PF"), nID, (double)0.95);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_EFF"), nID, (double)0.85);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_PFMINLAG"), nID, (double)-0.95);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_PFMINLEAD"), nID, (double)0.95);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_HI_ESS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_MEA"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_TREXCL"), nID, (int)nGEN_TREXCL);
	PUTDOUBLE2VALUE(_T("GEN_STA"), _T("GEN_II_PRDE"), nID, (int)nPRDEID); //2222222222

	/////
	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_NM"), nGENUNITID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_II_GEN"), nGENUNITID, (int)nID);
	PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_SI_GEN"), nGENUNITID, (int)0);
	PUTDOUBLE2VALUE(_T("GENUNIT_STA"), _T("GENUNIT_CAP_KW"), nGENUNITID, (double)dGEN_MWLMMX);

	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NO"), nGENUNITID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_LOCATION_NM"), nGENUNITID, (wchar_t*)stNULL.GetBuffer());
	PUTVALUE(_T("GENUNIT_STA"), _T("GENUNIT_CUSTOMER_NO"), nGENUNITID, (wchar_t*)stNULL.GetBuffer());
}

void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_GEN_DYN_MEA(int nID)
{
	//GEN_DYN_MEA
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_ONOFF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_OLDESSSOC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_ESSSOC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PAMEAVOLT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PBMEAVOLT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PCMEAVOLT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PAMEACUR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PBMEACUR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PCMEACUR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PAMEAANG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PBMEAANG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PCMEAANG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PAMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PAMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PBMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PBMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PCMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_PCMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_MEAMWDIR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_MEA"), _T("GEN_MEAMVARDIR"), nID, (int)0);
}

void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_GEN_DYN_UIN(int nID, double dGEN_ITR_CAP, int nGEN_ITR_WDC, double dGEN_ITR_X, int nGEN_MACH_TYPE)
{
	CString stNULL;
	stNULL.Format(_T(""));
	//GEN_DYN_UIN
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_AVR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_TBSVL"), nID, (double)1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DEV"), nID, (double)0.02);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PF"), nID, (double)0.95);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_VVOFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MVARCONMODE"), nID, (int)4);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_OUTQ"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PFVVOMINLAG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PFVVOMINLEAD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVMINS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMVUBREF"), nID, (double)1.02);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMVLBREF"), nID, (double)0.96);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_DERAVMQVRATIO"), nID, (double)1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEQMAX"), nID, (double)48);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEQMIN"), nID, (double)-48);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV1"), nID, (double)0.96);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV2"), nID, (double)0.97);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV3"), nID, (double)1.01);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_QVCURVEV4"), nID, (double)1.02);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_CAP"), nID, (double)dGEN_ITR_CAP);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_R"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_X"), nID, (double)dGEN_ITR_X);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_NGR_R"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_NGR_X"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_ITR_WDC"), nID, (int)nGEN_ITR_WDC);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_MACH_TYPE"), nID, (int)nGEN_MACH_TYPE);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_SCA_EXCEPTION"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_PDVRFLAG"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM1"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM2"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM3"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM4"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM5"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_UIN"), _T("GEN_EST_PM6"), nID, (double)0);
	PUTVALUE(_T("GEN_DYN_UIN"), _T("GEN_MDL_TIME"), nID, (wchar_t*)stNULL.GetBuffer());
}

void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_GEN_DYN_VVOO(int nID)
{
	//GEN_DYN_VVOO
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VREFOLD"), nID, (double)1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_PFREFOLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_QREFOLD"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_SI_DPDL"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_BASEKV"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVOVREF"), nID, (double)1);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVOPFREF"), nID, (double)0.95);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVOQREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_VVOO"), _T("GEN_VVORCOMFLAG"), nID, (int)0);
}

void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_GEN_DYN_PDVRO(int nID)
{

	//GEN_DYN_PDVRO
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_DERAVMPFREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_DERAVMVREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_DERAVMVUBREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_DERAVMVLBREF"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_DERAVMQVRATIO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_QVCURVEV1"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_QVCURVEV2"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_QVCURVEV3"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GEN_DYN_PDVRO"), _T("GEN_QVCURVEV4"), nID, (double)0);
}

void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_IJ(CString stKASIM_NM, int nID, int nNDID, int nIJ_II_EQUTY)
{
	int nIJ_WhileID = 0, nIJEQU = 0, nIJEQUTY = 0;
	nIJ_WhileID = nID; //특별하게 저장
	while (nIJEQU == 0)
	{
		if (nID == 999999)
		{
			break;
		}
		if (nIJ_WhileID == 1)
		{
			nIJEQUTY = 1;
			break;
		}
		nIJEQUTY = GETVALUE(int, _T("IJ_STA"), _T("IJ_II_EQUTY"), nIJ_WhileID - 1);
		if (nIJEQUTY == nIJ_II_EQUTY) //4-gen,6-선로,8수용가입니다.
		{
			nIJEQU = GETVALUE(int, _T("IJ_STA"), _T("IJ_II_EQU"), nIJ_WhileID - 1);
			nIJEQU = nIJEQU + 1;
			break;
		}
		else
		{
			nIJ_WhileID = nIJ_WhileID - 1;
		}
	}

	//IJ_STA
	PUTVALUE(_T("IJ_STA"), _T("IJ_NM"), nID, (wchar_t*)stKASIM_NM.GetBuffer());
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_EQUTY"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_EQUTY"), nID, (int)nIJ_II_EQUTY);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_EQU"), nID, (int)nIJEQU);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_GND"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_GND"), nID, (int)nNDID);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_II_DL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_STA"), _T("IJ_SI_DL"), nID, (int)0);
	//IJ_DYN_UIN
	PUTDOUBLE2VALUE(_T("IJ_DYN_UIN"), _T("IJ_SOCMAXORDER"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_UIN"), _T("IJ_SOCMINORDER"), nID, (int)0);
	//IJ_DYN_NCPO
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_SI_BS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_II_BS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_DEAD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_NCPO"), _T("IJ_BSSTAT"), nID, (int)0);
	//IJ_DYN_MEA
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_3PMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_3PMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PAMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PAMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PBMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PBMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PCMEAMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_PCMEAMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_MEA"), _T("IJ_MEAFLAG"), nID, (int)0);
	//IJ_DYN_RPFO
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PARPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PARPFMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PBRPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PBRPFMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PCRPFMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_RPFO"), _T("IJ_PCRPFMVAR"), nID, (double)0);
	//IJ_DYN_VVOO
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PAVVOMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PAVVOMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PBVVOMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PBVVOMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PCVVOMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_VVOO"), _T("IJ_PCVVOMVAR"), nID, (double)0);
	//IJ_DYN_DLEO
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PAGENESTMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PBGENESTMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PCGENESTMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PAGENESTMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PBGENESTMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_PCGENESTMVAR"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_3PGENESTMW"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("IJ_DYN_DLEO"), _T("IJ_3PGENESTMVAR"), nID, (double)0);
}

void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_ND(CString stKASIM_NM, CString stCEQID, int nID, int nFNDID, int nTNDID, int nIJDID, int nSNVID, int nType)
{
	CString stFndFK, stTndFK;
	int nNDID = 0;
	if (!(nFNDID == 0 || nFNDID == 999999)) { nNDID = nFNDID; }
	if (!(nTNDID == 0 || nTNDID == 999999)) { nNDID = nFNDID; }

	if (nNDID != 0)
	{
		//FND	
		stFndFK.Format(_T("%s01"), stCEQID);
		PUTVALUE(_T("ND_STA"), _T("ND_NM"), nNDID, (wchar_t*)stKASIM_NM.GetBuffer());
		PUTVALUE(_T("ND_STA"), _T("ND_CEQID"), nNDID, (unsigned long long)_wtoll(stCEQID));
		PUTVALUE(_T("ND_STA"), _T("ND_ConnectivityNodeID"), nNDID, (unsigned long long)_wtoll(stFndFK));
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_SI_SNV"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_SNV"), nNDID, (int)nSNVID);
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FCBSW"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TCBSW"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_FBR"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_TBR"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_GEN"), nNDID, (int)nID);
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SHUNTEQ"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_HI_SVC"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("ND_STA"), _T("ND_II_GND"), nNDID, (int)nNDID);
		//ND_DYN_UIN
		PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_MORFLAG"), nNDID, (int)1);
		PUTDOUBLE2VALUE(_T("ND_DYN_UIN"), _T("ND_II_VVM"), nNDID, (int)1);
		//FGND
		PUTVALUE(_T("GND_STA"), _T("GND_NM"), nNDID, (wchar_t*)stKASIM_NM.GetBuffer());
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_ND"), nNDID, (int)nNDID);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FCBSW"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TCBSW"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_FGBR"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_TGBR"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_GEN"), nNDID, (int)nID);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SHUNTEQ"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_SVC"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_LD"), nNDID, (int)0);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_IJ"), nNDID, (int)nIJDID);
		PUTDOUBLE2VALUE(_T("GND_STA"), _T("GND_HI_HVCUS"), nNDID, (int)0);

		Set_NEW_InitData_KASIM_GND(nNDID);
	}

}

void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_GND(int nID)
{
	//ND_DYN_NCPO
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_DL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_DL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_MTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_MTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_SI_SS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("ND_DYN_NCPO"), _T("ND_II_SS"), nID, (int)0);
	//GND_DYN_NCPO
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_SI_ISL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_II_ISL"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_DEAD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_SI_BS"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_NCPO"), _T("GND_II_BS"), nID, (int)0);
	//GND_DYN_RPFO
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIONW"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIORECV"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIOLMHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIOLMLO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_VIOFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PHSFLAG"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PAVIOKVHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PAVIOPERHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PAVIOKVLO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PAVIOPERLO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOKVHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOPERHI"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOKVLO"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PBVIOPERLO"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOKVHI"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOPERHI"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOKVLO"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_RPFO"), _T("GND_PCVIOPERLO"), nID, (double)0);
	//GND_DYN_SCAO
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FC_3LL"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FC_2LL"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FC_1LG"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FC_1LG_30ohm"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FLT_PA_V"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FLT_PB_V"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("GND_DYN_SCAO"), _T("GND_FLT_PC_V"), nID, (double)0);

}

void CDate_Csv_File_Dlg::Set_NEW_InitData_KASIM_PRDE(CString stKASIM_NM, int nID)
{
	//PRDE_STA
	PUTVALUE(_T("PRDE_STA"), _T("PRDE_NM"), nID, (wchar_t*)stKASIM_NM.GetBuffer());
	//PRDE_DYN_UIN
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_Pickup_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_IIC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_II_TCCSET"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_Pickup_C"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_IIC"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_TYPE"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_SET_GTYPE"), nID, (int)1);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_NOF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_NOD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_NOF"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_NOD"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_TAS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRF_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_TAS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCRD_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_TAS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRF_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_TAS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGRD_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCR_CTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_OCGR_CTR"), nID, (int)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_UIN"), _T("PRDE_MX_LD_C_PHA"), nID, (double)0);
	//PRDE_DYN_PCEO
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCRF_TM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCRD_TM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGRF_TM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGRD_TM"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_F_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_F_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_D_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_D_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_IIC_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_RECMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_PICKUP_C_RECMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_IIC_RECMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_TMS_RECMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_MX_FLT_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCR_MN_FLT_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_F_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_F_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_D_TMS"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_D_MRT"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_IIC_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_RECMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_PICKUP_C_RECMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_IIC_RECMN"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_TMS_RECMX"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_MX_FLT_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGR_MN_FLT_C"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCRF_TM_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCRD_TM_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGRF_TM_REC"), nID, (double)0);
	PUTDOUBLE2VALUE(_T("PRDE_DYN_PCEO"), _T("PRDE_OCGRD_TM_REC"), nID, (double)0);
}

//발전기 추가 
void CDate_Csv_File_Dlg::OnBnClickedButton1()
{
	GenCSV_Insert();
}

//발전기 다운
void CDate_Csv_File_Dlg::OnBnClickedButton2()
{
	GenCSV_Editor_Download();
}

//발전기 업로드 ()수정
void CDate_Csv_File_Dlg::OnBnClickedButton3()
{
	GenCSV_Editor_Upload();
}


void CDate_Csv_File_Dlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDate_Csv_File_Dlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
