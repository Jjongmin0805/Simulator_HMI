#include "pch.h"
#include "CDataManager.h"
#include "tlhelp32.h"
#include "dbexcept.h"
#include "Markup.h"

//#include "../Include/DBContainer/DB_EXTRACT.h"
////#include "../Include/DBContainer/DB_EXTRACT.h"
#include "../Include/DBContainer/DB_QUERY.h"

CDataManager *CDataManager::_instance = NULL;

CDataManager::CDataManager(void)
{
	Read_OleDBConfig();
	ConnectDB_LocalData();
	ConnectDB_OD();
	ConnectDB_SomasInfo();
	ConnectDB_SomasLog();
	

	
	ConnectDB_ADMS();

	m_nExe_ViewID = 0;
}

CDataManager::~CDataManager(void)
{
	theDBContainer->Close();

	EndKASIM();

	KillProcess(_T("Simulator_SLD.exe"));


	m_Session_localData.m_spOpenRowset.Release();
	m_Session_localData.Close();

	m_Session_OD.m_spOpenRowset.Release();
	m_Session_OD.Close();

	m_Session_SomasInfo.m_spOpenRowset.Release();
	m_Session_SomasInfo.Close();

	m_Session_SomasLog.m_spOpenRowset.Release();
	m_Session_SomasLog.Close();

	for (int i = 0; i < m_Array_ApplInfo.GetSize(); i++)
		delete m_Array_ApplInfo.GetAt(i);
	m_Array_ApplInfo.RemoveAll();

	for (int i = 0; i < m_Array_DBInfo.GetSize(); i++)
		delete m_Array_DBInfo.GetAt(i);
	m_Array_DBInfo.RemoveAll();

}



CDataManager* CDataManager::Instance(BOOL bInit )
{
	if (bInit)
	{
		if (_instance != 0)
		{
			delete _instance;
			_instance = 0;
		}
		
	}
	if (_instance == 0)
	{
		_instance = new CDataManager();
	}
	return _instance;
}

///////////////////////
//////////////////////////

void CDataManager::Send_WndMsg(int nProgramID, int nType, CString strData)
{
	if (nProgramID == WNDMSG_PROGRAMID_EDITOR)
	{
		/*HWND																				pHMIWnd;
		pHMIWnd = ::FindWindow(NULL, _T("App-Simulator GIS HMI"));
		if (!pHMIWnd)																		return;

		TCHAR																				szSendMsg[128] = { 0, };
		swprintf_s(szSendMsg, _T("%s"), strData);

		COPYDATASTRUCT																		_cds = { 0, };
		_cds.dwData = (ULONG)nType;
		_cds.cbData = (DWORD)sizeof(szSendMsg);
		_cds.lpData = (BYTE *)szSendMsg;
		::SendMessage(pHMIWnd, WM_COPYDATA, (WPARAM)this, (LPARAM)&_cds);*/
	}
	else if (nProgramID == WNDMSG_PROGRAMID_SLD)
	{
		HWND																				pHMIWnd;
		pHMIWnd = ::FindWindow(NULL, _T("Simulator_SLD"));
		if (!pHMIWnd)																		return;

		TCHAR																				szSendMsg[128] = { 0, };
		swprintf_s(szSendMsg, _T("%s"), strData);

		COPYDATASTRUCT																		_cds = { 0, };
		_cds.dwData = (ULONG)nType;
		_cds.cbData = (DWORD)sizeof(szSendMsg);
		_cds.lpData = (BYTE *)szSendMsg;
		::SendMessage(pHMIWnd, WM_COPYDATA, (WPARAM)this, (LPARAM)&_cds);
	}
}

void CDataManager::LoadKASIM()
{
	CWinApp* pApp = AfxGetApp();
	unsigned int					unOfficeCode(0);

	//TRACE(L"Step 1 : Set Init\n");
	SENDLOGMSG(_T("Step 1 : Set Init"), SENDLOGMSG_COLOR_NOR);
#if _DEBUG
	theAppDataMng->SetKASIM_ASSERT_MODE(true);
#endif
	
	theAppDataMng->ConnectDB();

	theAppDataMng->SetOnlineStudyMode(2);

	theAppDataMng->InitOfficeInfor();
	theAppDataMng->LoadKASIMSTLogID();


//	TRACE(L"Step 2 : MakeOffice KASIM - Topology\n");
	SENDLOGMSG(_T("Step 2 : MakeOffice KASIM - Topology"), SENDLOGMSG_COLOR_NOR);
	// KASIM Topology
	MakeOfficeCodeMMDB(unOfficeCode, 1, 1);

//	TRACE(L"Step 3 : MakeOffice KASIM - Dynamic\n");
	SENDLOGMSG(_T("Step 3 : MakeOffice KASIM - Dynamic"), SENDLOGMSG_COLOR_NOR);
	// KASIM Dynamic
	MakeOfficeCodeMMDB(unOfficeCode, 2, 2);


	TRACE(_T("%s"), theAppDataMng->GetSchemaDataSTA());
}

void CDataManager::EndKASIM()
{
	// Close Processing
	theAppDataMng->CloseDB();
	theAppDataMng->Close();
	theUtil->Close();

}

void CDataManager::MakeOfficeCodeMMDB(unsigned int unOfficeCode, int nRDBType, int nRDBIndex)
{
	theAppDataMng->SetOfficeInforStatus(unOfficeCode, nRDBType, nRDBIndex);
	while (theAppDataMng->GetOfficeInforRDBType(unOfficeCode) != 0)
	{
		Sleep(10);
	}
}

void CDataManager::GetTestKASIMData()
{
	TRACE(_T("\n\n"));

	int					nCount(theAppDataMng->GetTableMaxCount("CBSW_STA"));
	unsigned long long	ullCEQID(0U);
	for (int i = 0; i < nCount; i++)
	{
		ullCEQID = GETVALUE(unsigned long long, "CBSW_STA", "CBSW_CEQID", i + 1);
		if (ullCEQID == 0)
		{
			break;
		}
		TRACE(_T("Get Output Data[ %d ] : Name = %s, CEQID = %I64u\n"), (i + 1), CA2W(GETSTRING("CBSW_STA", "CBSW_NM", i + 1)).m_psz, ullCEQID);
	}

	TRACE(_T("\n\n"));
}

void CDataManager::PutTestKASIMData()
{
	// FLTINFO_DYN_FIO 입력
	PUTSTRING("FLTINFO_DYN_FIO", "FLTINFO_ID", 1, "1");
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_II_DL", 1, (double)13);
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_DL_MRID", 1, (double)1234567890123456);
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_II_CBSW", 1, (double)111);
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_CBSW_CEQID", 1, (double)1234567890123456);
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_TYPE", 1, (double)1);
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_IAOPR", 1, (double)1);
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_IBOPR", 1, (double)1);
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_ICOPR", 1, (double)1);
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_IAOPR", 1, (double)1);
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_HI_FIINFO", 1, (double)1);
	PUTDOUBLE2VALUE("FLTINFO_DYN_FIO", "FLTINFO_HI_ISOCBSW", 1, (double)1);
	PUTSTRING("FLTINFO_DYN_FIO", "FLTINFO_TIME", 1, "2020-01-01 01:01:01");
	printf("KASIM FLTINFO Update.\n");

	// FIINFO_DYN_FIO 입력
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_II_CBSW", 1, (double)13);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_CBSW_CEQID", 1, (double)1234567890123456);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_II_FLTINFO", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_SI_FLTINFO", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_FIKIND", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_FITYPE", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_IAOPR", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_IBOPR", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_ICOPR", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_INOPR", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_IA", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_IB", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_IC", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_IN", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_CHANGEABLE", 1, (double)1);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_COMERR", 1, (double)0);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_IA_TH", 1, (double)1.0);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_IB_TH", 1, (double)1.0);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_IC_TH", 1, (double)1.0);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_IN_TH", 1, (double)1.0);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_VA", 1, (double)1.0);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_VB", 1, (double)1.0);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_VC", 1, (double)1.0);
	PUTDOUBLE2VALUE("FIINFO_DYN_FIO", "FIINFO_FIORER_DIAG", 1, (double)1);

	// write csv
	theAppDataMng->WriteKASIMCSVFile(1,"FLTINFO_DYN_FIO", false, false, false,false);
	theAppDataMng->WriteKASIMCSVFile(1,"FIINFO_DYN_FIO", false, false, false,false);
}


/////////////////

void CDataManager::GetSSName_array(CStringArray* pArray, CIntArray* pArray_idx)
{
	pArray->RemoveAll();
	if (pArray_idx != NULL)
	{
		pArray_idx->RemoveAll();
	}


	int					nCount(theAppDataMng->GetTableMaxCount("SS_STA"));

	CPString strName;
	CString strNameW;
	
	for (int i = 1; i <= nCount; i++)
	{
		strName = GETVALUE2STR("SS_STA", "SS_NM", i );

		if (strName.IsEmpty())
			break;

		strNameW = CA2W(strName.GetValue()).m_psz;

		pArray->Add(strNameW);
		if (pArray_idx != NULL)
			pArray_idx->Add( i );
	}

}

void CDataManager::GetSSNames(vector<wstring>* vecString)
{
	if (vecString->size() > 0)																vecString->clear();

	int								nSSCnt(theAppDataMng->GetTableMaxCount(_T("ss_sta")));
	if (nSSCnt == 0)																		return;

	int								i(0);
	for (i = 1; i <= (int)nSSCnt; i++)
	{
		vecString->push_back(GETSTRING(_T("ss_sta"), _T("ss_nm"), i));
	}
	unique(vecString->begin(), vecString->end());
}

void CDataManager::GetMTRName_array(CString strSSName, CStringArray* pArray, CIntArray* pArray_idx)
{
	pArray->RemoveAll();
	if (pArray_idx != NULL)
	{
		pArray_idx->RemoveAll();
	}

	int								nSSCnt(theAppDataMng->GetTableMaxCount(_T("ss_sta")));
	int								nMTRCnt(theAppDataMng->GetTableMaxCount(_T("mtr_sta")));
	if (nSSCnt == 0 || nMTRCnt == 0)														return;

	int								i(0);
	int								nMtrIndex(0);

	CString strSS, strMTR;

	for (i = 1; i <= (int)nMTRCnt; i++)
	{
		nMtrIndex = GETVALUE(int, "mtr_sta", "mtr_ii_ss", i);
		if (nMtrIndex < 1)
		{
			continue;
		}
		
		strSS = CA2W(GETSTRING(("ss_sta"), ("ss_nm"), nMtrIndex)).m_psz;
		if (strSSName != strSS)
		{
			continue;
		}
		strMTR = CA2W(GETSTRING(("mtr_sta"), ("mtr_nm"), i)).m_psz;
		pArray->Add(strMTR);

		if (pArray_idx != NULL)
			pArray_idx->Add( i );

	}

}


void CDataManager::GetDLName_array(CString strSSName, CStringArray* pArray,CString strMTRName, CIntArray* pArray_idx)
{
	pArray->RemoveAll();
	if (pArray_idx != NULL)
	{
		pArray_idx->RemoveAll();
	}

	int								nSSCnt(theAppDataMng->GetTableMaxCount(_T("ss_sta")));
	int								nDLCnt(theAppDataMng->GetTableMaxCount(_T("dl_sta")));
	if (nSSCnt == 0 || nDLCnt == 0)														return;

	int								i(0);
	int								nDlIndex(0), nMtrIndex(0);

	CString strSS, strDL,strMTR;

	for (i = 1; i <= (int)nDLCnt; i++)
	{
		nDlIndex = GETVALUE(int, "dl_sta", "dl_ii_mtr", i);
		if (nDlIndex < 1)
		{
			continue;
		}

		if (!strMTRName.IsEmpty())
		{
			strMTR = CA2W(GETSTRING(("mtr_sta"), ("mtr_nm"), nDlIndex)).m_psz;

			if (strMTRName != strMTR)
			{
				continue;
			}
		}

		nMtrIndex = GETVALUE(int, ("mtr_sta"), ("mtr_ii_ss"), nDlIndex);
		if (nMtrIndex < 1)
		{
			continue;
		}

		strSS = CA2W(GETSTRING(("ss_sta"), ("ss_nm"), nMtrIndex)).m_psz;
		if (strSSName != strSS)
		{
			continue;
		}
		strDL = CA2W(GETSTRING(("dl_sta"), ("dl_nm"), i)).m_psz;
		pArray->Add(strDL);

		if (pArray_idx != NULL)
			pArray_idx->Add(i);
	}

}

void CDataManager::GetDLNames(wstring szSSName, vector<wstring>* vecString)
{
	if (vecString->size() > 0)										vecString->clear();
	
	int								nSSCnt(theAppDataMng->GetTableMaxCount(_T("ss_sta")));
	int								nDLCnt(theAppDataMng->GetTableMaxCount(_T("dl_sta")));
	if (nSSCnt == 0 || nDLCnt == 0)														return;

	int								i(0);
	int								nDlIndex(0), nMtrIndex(0);
	for (i = 1; i <= (int)nDLCnt; i++)
	{
		nDlIndex = GETVALUE(int, _T("dl_sta"), _T("dl_ii_mtr"), i);
		if (nDlIndex < 1)
		{
			continue;
		}
		nMtrIndex = GETVALUE(int, _T("mtr_sta"), _T("mtr_ii_ss"), nDlIndex);
		if (nMtrIndex < 1)
		{
			continue;
		}

		if (szSSName != GETSTRING(_T("ss_sta"), _T("ss_nm"), nMtrIndex))
		{
			continue;
		}
		vecString->push_back(GETSTRING(_T("dl_sta"), _T("dl_nm"), i));
	}

	unique(vecString->begin(), vecString->end());
}

int CDataManager::GetDLIndex(CString strDLName)
{
	int								nDLCnt(theAppDataMng->GetTableMaxCount(_T("dl_sta")));
	if (nDLCnt == 0)														return 0;

	int								i(0);
	int								nDlIndex(0);

	CString strDL;

	for (i = 1; i <= (int)nDLCnt; i++)
	{
		strDL = CA2W(GETSTRING(("dl_sta"), ("dl_nm"), i)).m_psz;
		if (strDLName == strDL)
		{
			return i;
		}
	}

	return 0;
}

CString CDataManager::MyPath()
{
	CString slmpath;
	WCHAR szDirve[256], szDir[2048];
	WCHAR programpath[2048];

	memset(szDir, 0x00, sizeof(szDir));
	memset(szDirve, 0x00, sizeof(szDirve));
	GetModuleFileName(0, programpath, 2048);
	size_t sz;

	_wsplitpath_s(programpath, szDirve,256, szDir,2048, NULL,0, NULL,0);

	slmpath.Format(_T("%s%s"), szDirve, szDir);
	slmpath.Delete(slmpath.GetLength() - 1, 1);
	return slmpath;

}

void CDataManager::MMDB_Restart()
{
	//////////////////////////////////////////////////////////////////////////////
	KillProcess(_T("Simulator_SLD.exe"));
	KillProcess(_T("Simulator_Editor.exe"));

	theAppDataMng->DeleteCategoryData(0);

	SENDLOGMSG(_T("Step 2 : MakeOffice KASIM - Topology"), SENDLOGMSG_COLOR_NOR);
	// KASIM Topology
	MakeOfficeCodeMMDB(0, 1, 1);

	//	TRACE(L"Step 3 : MakeOffice KASIM - Dynamic\n");
	SENDLOGMSG(_T("Step 3 : MakeOffice KASIM - Dynamic"), SENDLOGMSG_COLOR_NOR);
	// KASIM Dynamic
	MakeOfficeCodeMMDB(0, 2, 2);

	SetRelayInfo2DB();

	SENDLOGMSG(_T("File Import : End"), SENDLOGMSG_COLOR_NOR);

	Excute_Appl(_T("1"));

	//Excute_SLD();


}

void CDataManager::KASIM_LoadAs(CString strPath)
{
	CFileDialog FileDlg(TRUE, _T("zip"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("KASIM Data File(*.zip)|*.zip| All Files(*.*)|*.*|"));

	strPath = MyPath();
	FileDlg.m_pOFN->lpstrInitialDir = (LPCWSTR)strPath;

	if (FileDlg.DoModal() != IDOK)
		return;

	CString strDUAL, strST;
	CString strTitleName = FileDlg.GetFileTitle();
	CString strFilePath = FileDlg.GetPathName();
	CString strFileName = FileDlg.GetFileName();

	int nPathLen = strFilePath.GetLength();
	int nFileLen = strFileName.GetLength();
	strFilePath.Delete(nPathLen - nFileLen, nFileLen);

	/*int nPos = strTitleName.Find(_T("_DUAL"));

	if (nPos == -1)
	{
		nPos = strTitleName.Find(_T("_ST"));
		if (nPos == -1)
		{
			AfxMessageBox(_T("KASIM Data File 이 아닙니다."));
			return;
		}

		strTitleName.Delete(nPos, 3);
	}
	else
	{
		strTitleName.Delete(nPos, 5);
	}*/
	CString strZip_DUAL, strZip_ST,strSavePath;
	strSavePath.Format(_T("%s\\%s"), MyPath(), _T("Data\\CSVFile\\Export\\GatherDataFolder\\01"));
	strZip_DUAL.Format(_T("%s\\%s"), strSavePath, _T("_DUAL.zip"));
	strZip_ST.Format(_T("%s\\%s"), strSavePath, _T("_ST.zip"));
	
	strDUAL.Format(_T("%s%s"), strFilePath, strFileName);

	theUtil->doUnzip(strDUAL.GetBuffer(), strSavePath.GetBuffer());

	
	//strST.Format(_T("%s%s"), strFilePath, strTitleName + _T("_ST.zip"));

	CString strSource_DUAL, strSource_ST;
	strSource_DUAL.Format(_T("%s\\%s"), MyPath(), _T("Data\\CSVFile\\0\\DUAL"));
	strSource_ST.Format(_T("%s\\%s"), MyPath(), _T("Data\\CSVFile\\0\\ST"));

	SENDLOGMSG(_T("File Import : Start"), SENDLOGMSG_COLOR_NOR);

	theUtil->DeleteAllFilesInFolder(CW2A(strSource_DUAL).m_psz);
	theUtil->DeleteAllFilesInFolder(CW2A(strSource_ST).m_psz);

	theUtil->doUnzip(strZip_DUAL.GetBuffer(), strSource_DUAL.GetBuffer());
	theUtil->doUnzip(strZip_ST.GetBuffer(), strSource_ST.GetBuffer());


	theUtil->DeleteAllFilesInFolder(CW2A(strSavePath).m_psz);


	MMDB_Restart();

}

void CDataManager::KASIM_SaveAs(CString strPath)
{
	CTime t = CTime::GetCurrentTime();
	CString strName;
	strName.Format(_T("KASIM_DataFile_%s"),t.Format(_T("%Y%m%d%H%M%S")) );

	
	CFileDialog FileDlg(FALSE, _T("zip"), strName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("KASIM Data File(*.zip)|*.zip|"));

	strPath = MyPath();
	FileDlg.m_pOFN->lpstrInitialDir = (LPCWSTR)strPath;

	if (FileDlg.DoModal() != IDOK)
		return;

	CString strDUAL, strST,strZip_DUAL, strZip_ST,strSavePath;
	CString strFilePath = FileDlg.GetPathName();
	CString strFileName = FileDlg.GetFileName();
	CString strOrgPath;

	int nPathLen = strFilePath.GetLength();
	int nFileLen = strFileName.GetLength();
	strFilePath.Delete(nPathLen - nFileLen, nFileLen);
	
	strDUAL.Format(_T("%s%s"), strFilePath, FileDlg.GetFileTitle() + _T(".zip"));
//	strST.Format(_T("%s%s"), strFilePath, FileDlg.GetFileTitle() + _T("_ST.zip"));

	strSavePath.Format(_T("%s\\%s"), MyPath(), _T("Data\\CSVFile\\Export\\GatherDataFolder\\01"));
	strOrgPath.Format(_T("%s\\%s"), MyPath(), _T("Data\\CSVFile\\0\\ST"));



	CString strSource_DUAL, strSource_ST;
	strSource_DUAL.Format(_T("%s\\%s"),  strSavePath,_T("DUAL"));
	strSource_ST.Format(_T("%s\\%s"), strSavePath, _T("ST"));
	strZip_DUAL.Format(_T("%s\\%s"),  strSavePath,_T("_DUAL.zip"));
	strZip_ST.Format(_T("%s\\%s"),  strSavePath, _T("_ST.zip"));

	CFileFind finder;
	BOOL bWorking = finder.FindFile((CString)strOrgPath + _T("/*.xml"));

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
		{
			continue;
		}

		CopyFile(finder.GetFilePath(), strSource_ST+ _T("\\") + finder.GetFileName(), FALSE);
	}
	finder.Close();

	bWorking = finder.FindFile((CString)strOrgPath + _T("/*.svg"));

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
		{
			continue;
		}

		CopyFile(finder.GetFilePath(), strSource_ST + _T("\\") + finder.GetFileName(), FALSE);
	}
	finder.Close();

	
	

	SENDLOGMSG(_T("FileExport : Start"), SENDLOGMSG_COLOR_NOR);

	theAppDataMng->WriteKASIMCSVFile(1, "", false, false, false, true);
	
	theUtil->DeleteAllFilesInFolder(CW2A(strSavePath).m_psz);

	theUtil->doZip(strSource_DUAL.GetBuffer() , strZip_DUAL.GetBuffer());
	theUtil->doZip(strSource_ST.GetBuffer(), strZip_ST.GetBuffer());

	theUtil->doZip(strSavePath.GetBuffer(), strDUAL.GetBuffer());

	theUtil->DeleteAllFilesInFolder(CW2A(strSource_DUAL).m_psz);
	theUtil->DeleteAllFilesInFolder(CW2A(strSource_ST).m_psz);

	theUtil->DeleteAllFilesInFolder(CW2A(strSavePath).m_psz);

	SENDLOGMSG(_T("FileExport : End"), SENDLOGMSG_COLOR_NOR);

	
}

void CDataManager::Excute_Appl(CString strAppl_ID, int nViewID)
{
	m_nExe_ViewID = nViewID;
	////////////////////// 어플별 ID 확인
	////////////////////// Time Out
	////////////////////// Kill
	CString strApplPath = MyPath();
	CString strParam = _T("2 0 1 Simulator_hmi");  //// 
	strParam.Format(_T("2 0 %s Simulator_hmi"), strAppl_ID);

	if (!ShellExecute(NULL, _T("open"), _T("AppWRProject.exe"), strParam, strApplPath, TRUE) )
	//if (!ShellExecute(NULL, _T("open"), _T("AppWRProject.exe"), strParam, strApplPath, FALSE))
	{
		SENDLOGMSG(_T("AppWRProject.exe : Fail"), SENDLOGMSG_COLOR_NOR);
	}
	CString strLog;
	strLog.Format(_T("Application : Run ( %s , %s , %s )"), _T("NCP.exe"), strParam, strApplPath);

	SENDLOGMSG((WPARAM)strLog.GetBuffer(), SENDLOGMSG_COLOR_NOR);
}

void CDataManager::Excute_Appl_test(CString strAppl_ID)
{
	////////////////////// 어플별 ID 확인
	////////////////////// Time Out
	////////////////////// Kill
	CString strApplPath = MyPath();
	CString strParam = _T("2 0 1 Simulator_hmi");  //// 
	strParam.Format(_T("2 0 %s Simulator_hmi"), strAppl_ID);

	if (!ShellExecute(NULL, _T("open"), _T("AppWRProject_.exe"), strParam, strApplPath, TRUE))
	{
		SENDLOGMSG(_T("AppWRProject.exe : Fail"), SENDLOGMSG_COLOR_NOR);
	}
	CString strLog;
	strLog.Format(_T("Application : Run ( %s , %s , %s )"), _T("dnr.exe"), strParam, strApplPath);

	SENDLOGMSG((WPARAM)strLog.GetBuffer(), SENDLOGMSG_COLOR_NOR);
}

BOOL CDataManager::Excute_SLD()
{
	////////////////////// 어플별 ID 확인
	////////////////////// Time Out
	////////////////////// Kill
	CString strApplPath = MyPath();
	CString strParam = _T("");


	if (!ShellExecute(NULL, _T("open"), _T("Simulator_SLD.exe"), strParam, strApplPath, TRUE))
	{
		SENDLOGMSG(_T("Simulator_SLD.exe : Fail"), SENDLOGMSG_COLOR_NOR);

		return FALSE;
	}
	CString strLog;
	strLog.Format(_T("Process : Excute ( %s , %s , %s )"), _T("Simulator_SLD.exe"), strParam, strApplPath);

	SENDLOGMSG((WPARAM)strLog.GetBuffer(), SENDLOGMSG_COLOR_NOR);

	return TRUE;
}


BOOL CDataManager::GetProcessModule(DWORD dwPID, wstring sProcessName)
{
	MODULEENTRY32									tMe = { 0 };
	HANDLE											hPS = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);

	if (hPS == (HANDLE)-1)															return FALSE;
	tMe.dwSize = sizeof(MODULEENTRY32);
	transform(sProcessName.begin(), sProcessName.end(), sProcessName.begin(), tolower);
	if (Module32First(hPS, &tMe))
	{
		do {
			wstring									szCompareChar(tMe.szModule);
			transform(szCompareChar.begin(), szCompareChar.end(), szCompareChar.begin(), tolower);
			if (szCompareChar == sProcessName)
			{
				CloseHandle(hPS);
				return TRUE;
			}
		} while (Module32Next(hPS, &tMe));
	}
	CloseHandle(hPS);

	return FALSE;
}

BOOL CDataManager::KillProcess(wstring szProcessName)
{
	BOOL											bRet = FALSE;
	PROCESSENTRY32									tPe = { 0 };
	HANDLE											hPS = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hPS == (HANDLE)-1) 															return false;
	tPe.dwSize = sizeof(PROCESSENTRY32);

	//Get Precess
//	CString strName;
	if (Process32First(hPS, &tPe))
	{
		BOOL										bCurrentPM(FALSE);
		do {
			/*	strName.Format(_T("%s"),tPe.szExeFile);
				ASSERT(strName != _T("NCP.exe"));*/
			bCurrentPM = GetProcessModule(tPe.th32ProcessID, szProcessName);
			if (bCurrentPM)
			{
				HANDLE								hProcess(OpenProcess(PROCESS_ALL_ACCESS, FALSE, tPe.th32ProcessID));

				if (hProcess)
				{
					//LOGOUT(_T("schedule,KillProcess,%s,start"), GetName().c_str());
					if (TerminateProcess(hProcess, 0))
					{
						unsigned long						nCode(0);
						GetExitCodeProcess(hProcess, &nCode);

						CString strLog;
						strLog.Format(_T("Process : TerminateProcess ( %s )"), _T("Simulator_SLD.exe"));

						SENDLOGMSG((WPARAM)strLog.GetBuffer(), SENDLOGMSG_COLOR_NOR);
					}
					CloseHandle(hProcess);
					//LOGOUT(_T("schedule,KillProcess,%s,end"), GetName().c_str());
				}
			}
		} while (Process32Next(hPS, &tPe));
	}
	CloseHandle(hPS);
	return true;
}

void CDataManager::Read_OleDBConfig()
{
	CString strFileName;
	strFileName.Format(_T("%s\\Config\\Oledb_config.ini"), MyPath());


	FILE* stream = NULL;
	stream = _wfopen(strFileName, _T("r"));
	wchar_t wch[2048] = { 0, };
	if (stream != NULL)
	{
		fgetws(wch, 2048,stream);
		m_OleDB_Provider.Format(_T("%s"), wch);
		fclose(stream);
	}
	else
	{
		m_OleDB_Provider = _T("Microsoft.ACE.OLEDB.12.0");
	}
	
}


void CDataManager::ConnectDB_LocalData()
{


	if (m_Session_localData.m_spOpenRowset != NULL)
	{
		m_Session_localData.m_spOpenRowset.Release();
		m_Session_localData.Close();
	}
	CString strFile;
	strFile.Format(_T("Provider=%s;Data Source=%s\\local\\LocalData.mdb;Persist Security Info=False"), m_OleDB_Provider, MyPath());

	if (m_Connect_localData.OpenFromInitializationString(strFile.AllocSysString()) != S_OK)
	{
		AfxMessageBox(_T("Unable to connect to data source(DB)"));
		//	AfxMessageBox( strConnect );
		return;
	}
	else
	{
		if (m_Session_localData.Open(m_Connect_localData) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source(DB)"));
			return;
		}
	}


}

void CDataManager::ConnectDB_ADMS()
{

	// 2022.03.17 DB Modify
// 	if (!theDBContainer->ConnectDB())
// 	{
// 		TRACE(L"Err : DB Connect Fail.\n");
// 	}

	if (!theDBContainer->Init())
	{
		TRACE(L"Err : DB Connect Fail.\n");
	}



	/*CString strSQL;

	strSQL.Format(_T("Select id,update_time,file_name,file_type,file_size from adms_simulator_share where id = 1;") );

	CDB_EXTRACT						dbquery(0, strSQL.GetBuffer());
	CString strData;
	if (dbquery.GetRecordCount() > 0)
	{
		if (dbquery.MoveNext())
		{
			strData.Format(_T("%s"), dbquery.GetData_STR(0));
		}
	}
	dbquery.Close();

	CPString						szQueryWhereData;
	szQueryWhereData.Format("id = 1");
	int								nRetValue(0);
	if ((nRetValue = theDBContainer->MariaDB_UploadFile(0, szPathFile.GetValue(), "applogfile_data", "logdata", "logdatasize", szQueryWhereData.GetValue())) != 0)
	{
		LOGOUT("* Err : Upload BuffData Fail.( %d )", nRetValue);
		LOGOUT("DB Write End");
		return 3;
	}*/

}


void CDataManager::ConnectDB_OD()
{
	if (m_Session_OD.m_spOpenRowset != NULL)
	{
		m_Session_OD.m_spOpenRowset.Release();
		m_Session_OD.Close();
	}
	CString strFile;
	strFile.Format(_T("Provider=%s;Data Source=%s\\local\\Offdas.mdb;Persist Security Info=False"), m_OleDB_Provider, MyPath());

	if (m_Connect_OD.OpenFromInitializationString(strFile.AllocSysString()) != S_OK)
	{
		AfxMessageBox(_T("Unable to connect to data source(DB)"));
		//	AfxMessageBox( strConnect );
		return;
	}
	else
	{
		if (m_Session_OD.Open(m_Connect_OD) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source(DB)"));
			return;
		}
	}


}

void CDataManager::ConnectDB_SomasInfo()
{
	if (m_Session_SomasInfo.m_spOpenRowset != NULL)
	{
		m_Session_SomasInfo.m_spOpenRowset.Release();
		m_Session_SomasInfo.Close();
	}
	CString strFile;
	strFile.Format(_T("Provider=%s;Data Source=%s\\local\\Somas.mdb;Persist Security Info=False"), m_OleDB_Provider, MyPath());

	if (m_Connect_SomasInfo.OpenFromInitializationString(strFile.AllocSysString()) != S_OK)
	{
		AfxMessageBox(_T("Unable to connect to data source(DB)"));
		//	AfxMessageBox( strConnect );
		return;
	}
	else
	{
		if (m_Session_SomasInfo.Open(m_Connect_SomasInfo) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source(DB)"));
			return;
		}
	}


}

void CDataManager::ConnectDB_SomasLog()
{
	if (m_Session_SomasLog.m_spOpenRowset != NULL)
	{
		m_Session_SomasLog.m_spOpenRowset.Release();
		m_Session_SomasLog.Close();
	}
	CString strFile;
	strFile.Format(_T("Provider=%s;Data Source=%s\\local\\Somas_Data_Log.mdb;Persist Security Info=False"), m_OleDB_Provider, MyPath());

	if (m_Connect_SomasLog.OpenFromInitializationString(strFile.AllocSysString()) != S_OK)
	{
		AfxMessageBox(_T("Unable to connect to data source(DB)"));
		//	AfxMessageBox( strConnect );
		return;
	}
	else
	{
		if (m_Session_SomasLog.Open(m_Connect_SomasLog) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source(DB)"));
			return;
		}
	}


}


void CDataManager::SQLDBExcute(CSession *pDB, CString szQuery)
{
	if (szQuery.IsEmpty())
		return;

	CDBPropSet propset(DBPROPSET_ROWSET);
	propset.AddProperty(DBPROP_IRowsetChange, true);
	propset.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_INSERT | DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_DELETE);
	CCommand<CManualAccessor> rs;

	TRY
	{
		if (rs.Open(*pDB, szQuery, &propset, NULL, DBGUID_DBSQL, FALSE) != S_OK)
		{
			AfxMessageBox(_T("Couldn't open rowset\n") + szQuery, MB_TOPMOST);
		}

		rs.Close();
	}
	CATCH(COLEDBException, e)
	{
		e->ReportError();

	}
	END_CATCH
}

void CDataManager::Graph_Data_Add(CGraphDataArray* pArray, double dPrev_Len, double dCurr_Len,int nGBR_idx, int nPrevID, int nCurrID, BOOL bAdd)
{
	CGraphData* pData = new CGraphData();
	pArray->Add(pData);
	pData->m_dLen[0] = dPrev_Len;
	pData->m_dLen[1] = dCurr_Len;
	pData->m_nGNDIdx[0] = nPrevID;
	pData->m_nGNDIdx[1] = nCurrID;
	pData->m_nGBRIdx = nGBR_idx;
	pData->m_nTapChange = GETVALUE(int , _T("nd_dyn_uin"), _T("ND_II_VVM"), nCurrID);
	
	if (bAdd)
		pData->m_nAdd = 1;

	if (nGBR_idx == -1)
	{
		if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nCurrID) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nCurrID) > 0)//cbsw와 연결된 노드.
		{
			int																			nCbswIdx;
			if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nCurrID) > 0)		
				nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nCurrID);
			else																	
				nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nCurrID);

			pData->m_nType = 1;
			pData->m_nCBSW_idx = nCbswIdx;
		}
		else if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_gen"), nCurrID) > 0 )
		{
			pData->m_nType = 2;
			pData->m_nGEN_idx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_gen"), nCurrID);
		}
	}
	else
	{
		pData->m_nType = 3;
		pData->m_nTR_idx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equ"), nCurrID);
	}

	if(nPrevID > 0 )
		pData->m_nBS_idx[0] = GETVALUE(int, _T("gnd_dyn_ncpo"), _T("gnd_ii_bs"), nPrevID);

	pData->m_nBS_idx[1] = GETVALUE(int, _T("gnd_dyn_ncpo"), _T("gnd_ii_bs"), nCurrID);

	
	TRACE(_T("%d\t%d\n"), nPrevID, nCurrID);
}

void CDataManager::GetData_Graph(int nDL_idx, CGraphDataArray* pArray)
{
	int nGNDIdx = 0;
	int nCount = theAppDataMng->GetTableRealCount(_T("cbsw_sta"));
	for (int i = 1 ; i <= nCount ; i++)
	{
		if(GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), i)  != 1  ) 
			continue;
		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_dl"), i) != nDL_idx)
			continue;

		nGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tgnd"), i);
		
		break;
	}

	if (nGNDIdx == 0)
		return;
		
	FindGroupCB(pArray , -1, nGNDIdx);
}

int CDataManager::FindGroupCB(CGraphDataArray* pArray, int nPreGBRIdx, int nGNDIdx)
{
	int																				nCount;
	nCount = theAppDataMng->GetTableRealCount(_T("gbr_sta"));
	m_pBRTrace = new BYTE[nCount];
	memset(m_pBRTrace, 0x00, sizeof(BYTE) * nCount);

	int																				nNextGBRIdx, nRet;
	int																				nEq_Count = 0;
	//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)

//	Graph_Data_Add(pArray, 0.,0.,-1, -1, nGNDIdx,FALSE);

	nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nGNDIdx);
	while (nNextGBRIdx)
	{
		if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (nPreGBRIdx != nNextGBRIdx))
		{
			nRet = FindGroupCBRcv(pArray, nNextGBRIdx, nGNDIdx,  nGNDIdx,0.,0.);
			if (nRet)
			{
				delete[] m_pBRTrace;
				return nRet;
			}
		}
		nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGBRIdx);
	}

	//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
	nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nGNDIdx);
	while (nNextGBRIdx)
	{
		if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (nPreGBRIdx != nNextGBRIdx))
		{
			nRet = FindGroupCBRcv(pArray, nNextGBRIdx, nGNDIdx, nGNDIdx,0., 0.);
			if (nRet)
			{
				delete[] m_pBRTrace;
				return nRet;
			}
		}
		nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nNextGBRIdx);
	}

	delete[] m_pBRTrace;
	return 0;
}

int CDataManager::FindGroupCBRcv(CGraphDataArray* pArray, int nGBRIdx, int nFGNDIdx,  int nGraphND_Prev, double dPrev_Len, double dCurr_Len)
{
	////이미 지나갔던 구간이면 다시 안간다.
	if (m_pBRTrace[nGBRIdx - 1])													return 0;

	//구간 Trace 체크
	m_pBRTrace[nGBRIdx - 1] = TRUE;



	int																				nTGNDIdx, nNextGNDIdx, nNextGBRIdx, nRet;
	int		nPrev_ND = nGraphND_Prev;
	BOOL	bAdd = FALSE;


	//else if( GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGBRIdx ) > 0 || GETVALUE( int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGBRIdx ) > 0 )//t
	//{
	//	bAdd = FALSE;
	//}

	//구간의 다음 노드를 찾는다.
	if (GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nGBRIdx) == nFGNDIdx)	nTGNDIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_tgnd"), nGBRIdx);
	else																			nTGNDIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nGBRIdx);

	if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nTGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nTGNDIdx) > 0)//cbsw와 연결된 노드.
	{
		bAdd = TRUE;
	}

	int nLNSEC_idx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equ"), nGBRIdx);
	dCurr_Len += GETVALUE(double, _T("lnsec_sta"), _T("lnsec_length"), nLNSEC_idx);

	if (GetGroupNDStatus(nTGNDIdx) == SW_OPEN)
	{
		
		nPrev_ND = nTGNDIdx;
		Graph_Data_Add(pArray,dPrev_Len, dCurr_Len,  nGBRIdx, nGraphND_Prev, nTGNDIdx, bAdd);

		return 0;
	}

	//일반모드에서는 구간의 부하측노드가 없을경우 부하측에 가상노드를 하나만들고, 구간까지 생성한 후 종료.
	if (nTGNDIdx <= 0)
	{//축약모드에서는 구간의 부하측노드가 없으면 구간을 안만들고 끝(즉, 축약모드에서는 들어올 일 없음)
		return 0;
	}

	//CB를 찾았다.
	/*int																				nDlIdx;
	nDlIdx																			= GetGroupCbswToNode( nTGNDIdx );
	if( nDlIdx > 0 )																return nDlIdx;*/

	//nTNDIdx는 구간기준의 ToND -> 즉, 설비기준에서는 FND임
	//위에서 추가한 nTNDIdx 기준의 설비의 세부정보를 세팅하고, 설비기준에서의 TND(nNextNDIdx)로 변경.
	//DG, shunt, svc, Dummy등 토폴로지 기준 단일노드인 설비는 같은값이고, cbsw, tisw, svr 등은 설비기준 TND롤 변경
	//설비의 FND = 구간의 TND, 설비의 TND = 구간의 FND!!!!!!!!!!!!!!!!!!
	nNextGNDIdx = GetGroupToNDIdx(pArray, dPrev_Len , dCurr_Len, nGraphND_Prev, nTGNDIdx);

	//if (bAdd)
	
	nPrev_ND = nTGNDIdx;
	dPrev_Len = dCurr_Len;
	
	

	//설비의 부하측 노드와 연결된 cbsw(tisw포함)의 갯수를 체크한다.
	int																				nConnectCount;
	nConnectCount = CheckGroupConnectSw(nNextGNDIdx);

	//현재 설비(들어온쪽 설비)를 포함하여 2개이상 개폐기가 연결되어 있으면 멀티개폐기로 처리.
	//1개이하( 0:더미노드, gen, shunt...svr등, 1:단일개폐기) -> 어차피 동일로직이므로 뭐가되든 상관없다.
	//멀티개폐기 생성 및 토폴로지 진행을 위해 멀티를 구분하는 것임(다분기 더비는 br을 통해 진행하고, 멀티개폐기는 cbsw(tisw)를 통해 진행함) 
	if (nConnectCount >= 2) //다회로개폐기
	{
		//설비의 FND로 상태값을 확인
		//다회로의 전원측 설비가 OPEN이면 그만.
		if (GetGroupNDStatus(nTGNDIdx) == SW_OPEN)								return 0;

		//다회로 단자들을 찾아가면 생성한다.
		int																			nSubSwIdx, nSubGNDIdx;

		nSubSwIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nNextGNDIdx);
		while (nSubSwIdx)
		{
			nSubGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tgnd"), nSubSwIdx);
			if (nSubGNDIdx != nTGNDIdx)
			{
				//설비의 TND로 상태값을 확인
				if (GetSwStatus(nSubSwIdx) == SW_CLOSE)
				{
					//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(pArray, nNextGBRIdx, nSubGNDIdx, nPrev_ND, dPrev_Len,dCurr_Len);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGBRIdx);
					}

					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(pArray, nNextGBRIdx, nSubGNDIdx, nPrev_ND, dPrev_Len, dCurr_Len);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nNextGBRIdx);
					}
				}
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fgnd"), nSubSwIdx);
		}

		nSubSwIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nNextGNDIdx);
		while (nSubSwIdx)
		{
			nSubGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fgnd"), nSubSwIdx);
			if (nSubGNDIdx != nTGNDIdx)
			{
				//설비의 TND로 상태값을 확인
				if (GetSwStatus(nSubSwIdx) == SW_CLOSE)
				{
					//다회로 단자와 연결된 구간을 찾아서 다음구간으로 진행.
					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(pArray, nNextGBRIdx, nSubGNDIdx,  nPrev_ND, dPrev_Len, dCurr_Len);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGBRIdx);
					}

					nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nSubGNDIdx);
					while (nNextGBRIdx)
					{
						//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
						if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace[nNextGBRIdx - 1] == FALSE))
						{
							nRet = FindGroupCBRcv(pArray, nNextGBRIdx, nSubGNDIdx,  nPrev_ND, dPrev_Len, dCurr_Len);
							if (nRet)												return nRet;
						}
						nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nNextGBRIdx);
					}
				}
			}
			nSubSwIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tgnd"), nSubSwIdx);
		}

		
	}
	else
	{
		//설비의 TND로 상태값을 확인
		//설비가 OPEN이면 그만.
		if (GetGroupNDStatus(nNextGNDIdx) == SW_OPEN)							return 0;

		//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nNextGNDIdx);
		while (nNextGBRIdx)
		{
			if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace[nNextGBRIdx - 1] == FALSE))
			{
				nRet = FindGroupCBRcv(pArray, nNextGBRIdx, nNextGNDIdx, nPrev_ND, dPrev_Len, dCurr_Len);
				if (nRet)															return nRet;
			}
			nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nNextGBRIdx);
		}

		//연결된 BR이 구간일때만 진행( 설비의 ToND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		nNextGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nNextGNDIdx);
		while (nNextGBRIdx)
		{
			if ((GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nNextGBRIdx) == 1) && (m_pBRTrace[nNextGBRIdx - 1] == FALSE))
			{
				nRet = FindGroupCBRcv(pArray, nNextGBRIdx, nNextGNDIdx, nPrev_ND, dPrev_Len, dCurr_Len);
				if (nRet)															return nRet;
			}
			nNextGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nNextGBRIdx);
		}
	}

	return 0;
}

int CDataManager::CheckGroupConnectSw(int nGNDIdx)
{
	//하나의 노드의 from, to가 모두 스위치이면 --> 다회로의 가상더미임.
	//이전설비의 부하측노드(nNextNDIdx)가 또다른 switch와 연결되어 있다.(방향은 모르지만, 한쪽은 nNextNDIdx의 전원측 switch일꺼고, 다른쪽으로 switch가 또 있다?!)
	//이전설비가 switch가 아니라면 절대 안들어가겠지.
	//따라서 아래 조건을 만족하면 nNextNDIdx는 다회로의 가상더미임.
	int																		nConnectCnt(0), nSWIdx;

	nSWIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx);
	while (nSWIdx)
	{
		nConnectCnt++;
		nSWIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_fgnd"), nSWIdx);
	}

	nSWIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx);
	while (nSWIdx)
	{
		nConnectCnt++;
		nSWIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_si_tgnd"), nSWIdx);
	}

	//nSWIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx);
	//while (nSWIdx)
	//{
	//	nConnectCnt++;
	//	nSWIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_si_fgnd"), nSWIdx);
	//}

	//nSWIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx);
	//while (nSWIdx)
	//{
	//	nConnectCnt++;
	//	nSWIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_si_tgnd"), nSWIdx);
	//}

	return nConnectCnt;
}

int CDataManager::GetGroupToNDIdx(CGraphDataArray* pArray, double dPrev_Len, double dCurr_Len, int nFGNDIdx, int nGNDIdx)
{
	int																				nNextGNDIdx(-1);
	if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx) > 0)//cbsw와 연결된 노드.
	{
		int																			nCbswIdx;
		if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0)		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx);

		if (GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fgnd"), nCbswIdx) == nGNDIdx)	nNextGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_tgnd"), nCbswIdx);
		else																			nNextGNDIdx = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_ii_fgnd"), nCbswIdx);
	}
	//else if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx) > 0)//tiesw와 연결된 노드.
	//{
	//	int																			nCbswIdx;
	//	if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx) > 0)		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx);
	//	else																		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx);

	//	if (GETVALUE(int, _T("tisw_sta"), _T("tisw_ii_fgnd"), nCbswIdx) == nGNDIdx)	nNextGNDIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_ii_tgnd"), nCbswIdx);
	//	else																			nNextGNDIdx = GETVALUE(int, _T("tisw_sta"), _T("tisw_ii_fgnd"), nCbswIdx);
	//}
	else//br이랑만 연결되어 있음 - Dummy 또는 SVR 임
	{
		int																			nSVRIdx = 0;
		int																			nGBRIdx;

		nGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fgbr"), nGNDIdx);
		while (nGBRIdx)
		{
			if (nGBRIdx && GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nGBRIdx) == 2)
			{
				nSVRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equ"), nGBRIdx);
				break;
			}

			nGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_fgnd"), nGBRIdx);
		}

		if (nSVRIdx == 0)
		{
			nGBRIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tgbr"), nGNDIdx);
			while (nGBRIdx)
			{
				if (nGBRIdx && GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nGBRIdx) == 2)
				{
					nSVRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equ"), nGBRIdx);
					break;
				}
				nGBRIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_si_tgnd"), nGBRIdx);
			}
		}

		if (nSVRIdx)//SVR
		{
			if (GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nGBRIdx) == nGNDIdx)	nNextGNDIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_tgnd"), nGBRIdx);
			else																		nNextGNDIdx = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_fgnd"), nGBRIdx);

			Graph_Data_Add(pArray, dPrev_Len,dCurr_Len, nGBRIdx, nFGNDIdx, nGNDIdx, FALSE);

			return nNextGNDIdx;
		}


		//BR속성의 설비가 아니면 그냥 자신
		nNextGNDIdx = nGNDIdx;
	}
	Graph_Data_Add(pArray, dPrev_Len, dCurr_Len,  -1, nFGNDIdx, nGNDIdx, FALSE);
	return nNextGNDIdx;
}

int CDataManager::GetGroupNDStatus(int nGNDIdx)
{
	BOOL																			bStatus(TRUE);
	if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx) > 0)//cbsw와 연결된 노드.
	{
		int																			nCbswIdx;
		if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx) > 0)		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_fcbsw"), nGNDIdx);
		else																		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_tcbsw"), nGNDIdx);

		bStatus = GetSwStatus(nCbswIdx);
	}
	//else if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx) > 0 || GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx) > 0)//tiesw와 연결된 노드.
	//{
	//	int																			nCbswIdx;
	//	if (GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx) > 0)		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ftisw"), nGNDIdx);
	//	else																		nCbswIdx = GETVALUE(int, _T("gnd_sta"), _T("gnd_hi_ttisw"), nGNDIdx);

	//	bStatus = GetTieStatus(nCbswIdx);
	//}
	else
	{
		bStatus = SW_CLOSE;
	}

	return bStatus;
}

int CDataManager::GetSwStatus(int nCbswIdx)
{
	return  GETVALUE(int, _T("cbsw_dyn_mea"), _T("cbsw_nwstat"), nCbswIdx);
}




BOOL CDataManager::Read_ApplInfo()
{
	CString strFileName;

	// XML 객체 생성 및 파일 로드

	strFileName.Format(_T("%s\\Config\\%s"), MyPath(), _T("ApplicationGroupInfor.xml"));
	
	CMarkup xml;

	if (!xml.Load(strFileName))
	{
		return FALSE;
	}

	BOOL b = xml.FindElem(_T("applicationinfor_config"));
	xml.IntoElem(); /////////// applicationproperty

	CString strTagName, strpsrType;
	CAppl_Info* pInfo;
	while (xml.FindChildElem())
	{
		xml.IntoElem();

		strTagName = xml.GetTagName();

		pInfo = new CAppl_Info();
		m_Array_ApplInfo.Add(pInfo);
		pInfo->Read_Config(&xml);

		xml.OutOfElem();
	}

	return TRUE;
}

BOOL CDataManager::Read_DBInfo()
{
	CString strFileName;

	// XML 객체 생성 및 파일 로드

	strFileName.Format(_T("%s\\Config\\%s"), MyPath(), _T("dbconfig.xml"));

	CMarkup xml;

	if (!xml.Load(strFileName))
	{
		return FALSE;
	}

	BOOL b = xml.FindElem(_T("dbinfo"));
	
	CString strTagName, strpsrType;
	CDB_Info* pInfo;
	while (xml.FindChildElem())
	{
		xml.IntoElem();

		strTagName = xml.GetTagName();

		pInfo = new CDB_Info();
		m_Array_DBInfo.Add(pInfo);
		pInfo->Read_Config(&xml);

		xml.OutOfElem();
	}

	return TRUE;
}

int CDataManager::GetTCCSET_Index(CString strCOSName)
{
	int								nCnt(theAppDataMng->GetTableMaxCount(_T("tccset_sta")));
	if (nCnt == 0)														return 0;

	int								i(0);
	int								nDlIndex(0);

	CString strName;

	for (i = 1; i <= (int)nCnt; i++)
	{
		strName = CA2W(GETSTRING(("tccset_sta"), ("tccset_nm"), i)).m_psz;
		if (strName == strCOSName)
		{
			return i;
		}
	}

	return 0;
}

void CDataManager::SetRelayInfo2DB()
{
	//////////////////// kacim 데이터 초기화
	int nkacim_Count = theAppDataMng->GetTableRealCount(_T("MACHINE_DYN_UIN"));
	for (int i = 1; i < nkacim_Count; i++)
	{
		PUTSTRING(_T("MACHINE_DYN_UIN"), _T("MACHINE_NM"), i,_T(""));
		PUTSTRING(_T("MACHINE_DYN_UIN"), _T("MACHINE_MANUF_NM"), i, _T(""));
		PUTDOUBLE2VALUE(_T("MACHINE_DYN_UIN"), _T("MACHINE_II_TCCSET"), i, (double)0.);
	}

	nkacim_Count = theAppDataMng->GetTableRealCount(_T("RELAY_TYPE_DYN_UIN"));
	for (int i = 1; i < nkacim_Count; i++)
	{
		PUTDOUBLE2VALUE(_T("RELAY_TYPE_DYN_UIN"), _T("RELAY_II_MACHINE"), i, (double)0);
		PUTDOUBLE2VALUE(_T("RELAY_TYPE_DYN_UIN"), _T("RELAY_AD_SEP"), i, (double)0);
		PUTDOUBLE2VALUE(_T("RELAY_TYPE_DYN_UIN"), _T("RELAY_OG_SEP"), i, (double)0);
		PUTDOUBLE2VALUE(_T("RELAY_TYPE_DYN_UIN"), _T("RELAY_FD_SEP"), i, (double)0);
	}

	nkacim_Count = theAppDataMng->GetTableRealCount(_T("RELAY_A_TAP_DYN_UIN"));
	for (int i = 1; i < nkacim_Count; i++)
	{
		PUTDOUBLE2VALUE(_T("RELAY_A_TAP_DYN_UIN"), _T("RELAY_II_MACHINE"), i, (double)0);
		PUTDOUBLE2VALUE(_T("RELAY_A_TAP_DYN_UIN"), _T("RELAY_OG_SEP"), i, (double)0);
		PUTDOUBLE2VALUE(_T("RELAY_A_TAP_DYN_UIN"), _T("RELAY_FD_SEP"), i, (double)0);
		PUTDOUBLE2VALUE(_T("RELAY_A_TAP_DYN_UIN"), _T("RELAY_TAP_VALUE"), i, (double)0.);
	}

	nkacim_Count = theAppDataMng->GetTableRealCount(_T("RELAY_D_TAP_DYN_UIN"));
	for (int i = 1; i < nkacim_Count; i++)
	{
		PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_II_MACHINE"), i, (double)0);
		PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_OG_SEP"), i, (double)0);
		PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_FD_SEP"), i, (double)0);
		PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_TAP_START"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_TAP_END"), i, (double)0.);
		PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_TAP_STEP"), i, (double)0.);
	}
	////////////////////////////////////////////

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL;
	int nID;

	CString strData[3];
	int nValue[4];
	double dValue[3];
	
	strSQL = _T("SELECT machine_name,machine_manuf,machine_ii_tccset from adms_n_machine_code order by machine_id ");


	int nIndex = 1;
	TRY
	{
		ulFields = 3;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strData[0] = pBind[0].szValue;
			strData[1] = pBind[1].szValue;
			strData[2] = pBind[2].szValue;

			PUTSTRING(_T("MACHINE_DYN_UIN"), _T("MACHINE_NM"), nIndex, strData[0].GetBuffer());
			PUTSTRING(_T("MACHINE_DYN_UIN"), _T("MACHINE_MANUF_NM"), nIndex, strData[1].GetBuffer());
			PUTDOUBLE2VALUE(_T("MACHINE_DYN_UIN"), _T("MACHINE_II_TCCSET"), nIndex, (double)_wtoi(strData[2]));

			nIndex ++;
		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		////////// Subs

	}
	CATCH(COLEDBException, e)
	{
		if (pBind != NULL)
			delete pBind;

		e->ReportError();
	}
	END_CATCH
		////////////////////////////////////////////////////////

	strSQL = _T("SELECT machine_id,ad_sep,ocr_ocgr_sep,fd_sep from ADMS_n_relay_type order by machine_id ");

	nIndex = 1;
	TRY
	{
		ulFields = 4;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nValue[0] = _wtoi(pBind[0].szValue);
			nValue[1] = _wtoi(pBind[1].szValue);
			nValue[2] = _wtoi(pBind[2].szValue);
			nValue[3] = _wtoi(pBind[3].szValue);

			PUTDOUBLE2VALUE(_T("RELAY_TYPE_DYN_UIN"), _T("RELAY_II_MACHINE"), nIndex, (double)nValue[0]);
			PUTDOUBLE2VALUE(_T("RELAY_TYPE_DYN_UIN"), _T("RELAY_AD_SEP"), nIndex, (double)nValue[1]);
			PUTDOUBLE2VALUE(_T("RELAY_TYPE_DYN_UIN"), _T("RELAY_OG_SEP"), nIndex, (double)nValue[2]);
			PUTDOUBLE2VALUE(_T("RELAY_TYPE_DYN_UIN"), _T("RELAY_FD_SEP"), nIndex, (double)nValue[3]);

			nIndex++;
		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		////////// Subs

	}
		CATCH(COLEDBException, e)
	{
		if (pBind != NULL)
			delete pBind;

		e->ReportError();
	}
	END_CATCH
		////////////////////////////////////////////////////////

	strSQL = _T("SELECT machine_id,ocr_ocgr_sep,fd_sep,ty_tap from ADMS_n_relay_A_tap order by machine_id ");

	nIndex = 1;
	TRY
	{
		ulFields = 4;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nValue[0] = _wtoi(pBind[0].szValue);
			nValue[1] = _wtoi(pBind[1].szValue);
			nValue[2] = _wtoi(pBind[2].szValue);
			dValue[0] = _wtof(pBind[3].szValue);

			PUTDOUBLE2VALUE(_T("RELAY_A_TAP_DYN_UIN"), _T("RELAY_II_MACHINE"), nIndex, (double)nValue[0]);
			PUTDOUBLE2VALUE(_T("RELAY_A_TAP_DYN_UIN"), _T("RELAY_OG_SEP"), nIndex, (double)nValue[1]);
			PUTDOUBLE2VALUE(_T("RELAY_A_TAP_DYN_UIN"), _T("RELAY_FD_SEP"), nIndex, (double)nValue[2]);
			PUTDOUBLE2VALUE(_T("RELAY_A_TAP_DYN_UIN"), _T("RELAY_TAP_VALUE"), nIndex, (double)dValue[0]);

			nIndex++;
		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		////////// Subs

	}
		CATCH(COLEDBException, e)
	{
		if (pBind != NULL)
			delete pBind;

		e->ReportError();
	}
	END_CATCH
		////////////////////////////////////////////////////////

	strSQL = _T("SELECT machine_id,ocr_ocgr_sep,fd_sep,tap_start,tap_end,tap_step from ADMS_n_relay_D_tap order by machine_id ");

	nIndex = 1;
	TRY
	{
		ulFields = 6;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nValue[0] = _wtoi(pBind[0].szValue);
			nValue[1] = _wtoi(pBind[1].szValue);
			nValue[2] = _wtoi(pBind[2].szValue);
			dValue[0] = _wtof(pBind[3].szValue);
			dValue[1] = _wtof(pBind[4].szValue);
			dValue[2] = _wtof(pBind[5].szValue);


			PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_II_MACHINE"), nIndex, (double)nValue[0]);
			PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_OG_SEP"), nIndex, (double)nValue[1]);
			PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_FD_SEP"), nIndex, (double)nValue[2]);
			PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_TAP_START"), nIndex, (double)dValue[0]);
			PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_TAP_END"), nIndex, (double)dValue[1]);
			PUTDOUBLE2VALUE(_T("RELAY_D_TAP_DYN_UIN"), _T("RELAY_TAP_STEP"), nIndex, (double)dValue[2]);

			nIndex++;
		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		////////// Subs

	}
		CATCH(COLEDBException, e)
	{
		if (pBind != NULL)
			delete pBind;

		e->ReportError();
	}
	END_CATCH
}

double CDataManager::GetRelayTabValue(int nMachine_ID, int nOGType, int nFDType,double dInput_value)
{

	int nAD_Type = GetMachineType_AD(nMachine_ID);
	if (nMachine_ID == -1)
		return 0.;
	

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL;
	double dVal_s, dVal_e, dStep = 0.;

	if (nAD_Type == 0)
	{
		strSQL.Format(_T("SELECT tap_start,tap_end,tap_step from ADMS_n_relay_D_tap \
							where machine_id = %d and ocr_ocgr_sep = %d and fd_sep = %d"), nMachine_ID,nOGType,nFDType);
	}
	else
	{
		return 0.;
	}


	TRY
	{
		ulFields = 3;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		if (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			dVal_s = _wtof(pBind[0].szValue);
			dVal_e = _wtof(pBind[1].szValue);
			dStep = _wtof(pBind[2].szValue);
		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		////////// Subs

	}
		CATCH(COLEDBException, e)
	{
		if (pBind != NULL)
			delete pBind;

		e->ReportError();
	}
	END_CATCH

	if (dStep > 0)
	{
		double dResult = dVal_s;
		while (1)
		{
			if (dResult > dVal_e)
			{
				return dVal_e;
			}

			if (dInput_value <= dResult)
			{
				return dResult;
			}

			dResult += dStep;
		}
	}

	

	return 0.;
}

int CDataManager::GetMachineType_AD(int nMachine_ID)
{
	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL;
	int nType = -1;


	strSQL.Format(_T("SELECT ad_sep from ADMS_n_relay_type where machine_id = %d") , nMachine_ID);


	TRY
	{
		ulFields = 1;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(m_Session_OD,strSQL) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		if (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			nType = _wtoi( pBind[0].szValue);
		}
		rs.Close();
		delete pBind;
		pBind = NULL;

		////////// Subs

	}
		CATCH(COLEDBException, e)
	{
		if (pBind != NULL)
			delete pBind;

		e->ReportError();
	}
	END_CATCH


	return nType;
}

void CDataManager::Set_PDVR_Voltage2ADMS(int nTR_Idx, int nMode, COleDateTime tFrom, COleDateTime tTo)
{
	CString strColName[2][4];

	strColName[0][0] = _T("1Q_Volt");
	strColName[0][1] = _T("2Q_Volt");
	strColName[0][2] = _T("3Q_Volt");
	strColName[0][3] = _T("4Q_Volt");
	strColName[1][0] = _T("1QPV_Volt");
	strColName[1][1] = _T("2QPV_Volt");
	strColName[1][2] = _T("3QPV_Volt");
	strColName[1][3] = _T("4QPV_Volt");

	int nFrom, nTo;
	BOOL bCheck[4];
	for (int i = 0; i < 4; i++)
		bCheck[i] = FALSE;

	COleDateTimeSpan tSpan(1, 0, 0, 0);
	COleDateTime tCurrent = tFrom;
	int nMonth;
	while (1)
	{
		nMonth = tCurrent.GetMonth()/4;
		bCheck[nMonth] = TRUE;

		if(tCurrent == tTo)
			break;;

		tCurrent += tSpan;
	}
	


	
	

	unsigned long long ullCEQID;

	ullCEQID = GETVALUE(unsigned long long, _T("tr_sta"), _T("tr_ceqid"), nTR_Idx);

	int nCount = 0 ;
	double dValue[4] ;
	double dTotal = 0;
	CString strSQL;

	for (int i = 0; i < 4; i++)
	{
		if (bCheck[i])
		{
			strSQL.Format(_T("Select %s from app_his_mtrv where  MTR_MRFK =  %lld"), strColName[nMode][i], ullCEQID);

			CDB_QUERY							dbquery(strSQL.GetBuffer(), 0);
			if (dbquery.GetRecordCount() > 0)
			{
				if (dbquery.MoveNext())
				{
					dValue[nCount] = dbquery.GetData_FLT(0);

					dTotal += dValue[nCount];

					nCount++;
				}
			}

			dbquery.Close();
		}
		
	}

	dTotal /= nCount;
	dTotal /= 22.9;

	PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("pdvropt_oltcmodel"), 1, (double)4.);
	PUTDOUBLE2VALUE(_T("PDVROPT_DYN_UIN"), _T("pdvropt_oltcv"), 1, (double)dTotal);
}