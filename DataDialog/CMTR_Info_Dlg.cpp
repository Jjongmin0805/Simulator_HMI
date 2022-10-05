// CMTR_Info_Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "CMTR_Info_Dlg.h"
#include "afxdialogex.h"
#include "excel9.h"
#include "../DataManager/CDataManager.h"

// CMTR_Info_Dlg 대화 상자

IMPLEMENT_DYNAMIC(CMTR_Info_Dlg, CDialogEx)

CMTR_Info_Dlg::CMTR_Info_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MTR_INFO_DLG, pParent)
{

}

CMTR_Info_Dlg::~CMTR_Info_Dlg()
{
}

void CMTR_Info_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MTR_INFO_DLG_LIST1, m_ctrList);
}


BEGIN_MESSAGE_MAP(CMTR_Info_Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_MTR_INFO_DLG_BTN1, &CMTR_Info_Dlg::OnBnClickedMtrInfoDlgBtn1)
	ON_BN_CLICKED(IDC_MTR_INFO_DLG_BTN2, &CMTR_Info_Dlg::OnBnClickedMtrInfoDlgBtn2)
	ON_BN_CLICKED(IDC_MTR_INFO_DLG_BTN3, &CMTR_Info_Dlg::OnBnClickedMtrInfoDlgBtn3)
END_MESSAGE_MAP()


// CMTR_Info_Dlg 메시지 처리기


BOOL CMTR_Info_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect r;
	m_ctrList.GetWindowRect(r);
	m_ctrList.InsertColumn(0, _T("변전소"), LVCFMT_CENTER, r.Width() / 33 * 3 - 10);
	m_ctrList.InsertColumn(1, _T("Bank No."), LVCFMT_CENTER, r.Width() / 33 * 2 + 20);
	m_ctrList.InsertColumn(2, _T("송출전압고정"), LVCFMT_CENTER, r.Width() / 33 * 3);
	m_ctrList.InsertColumn(3, _T("선간전압(kV)"), LVCFMT_CENTER, r.Width() / 33 * 3);
	////////////////////// 140708 김상옥 요청
	m_ctrList.InsertColumn(4, _T("FA[MVA]"), LVCFMT_CENTER, r.Width() / 33 * 3);
	m_ctrList.InsertColumn(5, _T("Mtr%imp"), LVCFMT_CENTER,/*r.Width()/33*3*/ 0);
	m_ctrList.InsertColumn(6, _T("NGR[%Ω]"), LVCFMT_CENTER, r.Width() / 33 * 3);
	m_ctrList.InsertColumn(7, _T("Tab(%)"), LVCFMT_CENTER,/*r.Width()/33*3*/ 0);
	m_ctrList.InsertColumn(8, _T("R(+)[%Ω]"), LVCFMT_CENTER, r.Width() / 33 * 3);
	m_ctrList.InsertColumn(9, _T("X(+)[%Ω]"), LVCFMT_CENTER, r.Width() / 33 * 3);
	m_ctrList.InsertColumn(10, _T("R(0)[%Ω]"), LVCFMT_CENTER, r.Width() / 33 * 3);
	m_ctrList.InsertColumn(11, _T("X(0)[%Ω]"), LVCFMT_CENTER, r.Width() / 33 * 3);
	m_ctrList.InsertColumn(12, _T("MTR12_X1[%Ω]"), LVCFMT_CENTER, r.Width() / 33 * 3);

	m_ctrList.InsertColumn(13, _T("CT 1차 전류[A]"), LVCFMT_CENTER, r.Width() / 30 * 3);
	m_ctrList.InsertColumn(14, _T("OCR Type"), LVCFMT_CENTER, r.Width() / 30 * 3);
	m_ctrList.InsertColumn(15, _T("OCR Tap"), LVCFMT_CENTER, r.Width() / 30 * 3);
	m_ctrList.InsertColumn(16, _T("OCR Lever"), LVCFMT_CENTER, r.Width() / 30 * 3);
	m_ctrList.InsertColumn(17, _T("OCGR Type"), LVCFMT_CENTER, r.Width() / 30 * 3);
	m_ctrList.InsertColumn(18, _T("OCGR Tap"), LVCFMT_CENTER, r.Width() / 30 * 3);
	m_ctrList.InsertColumn(19, _T("OCGR Lever"), LVCFMT_CENTER, r.Width() / 30 * 3);
	m_ctrList.InsertColumn(20, _T("ULTC Tap"), LVCFMT_CENTER, r.Width() / 30 * 3);
	m_ctrList.InsertColumn(21, _T("SC용량(Mvar)"), LVCFMT_CENTER, r.Width() / 30 * 3);
	m_ctrList.InsertColumn(22, _T("tr_idx"), LVCFMT_CENTER, 0);
	m_ctrList.InsertColumn(23, _T("gen_idx"), LVCFMT_CENTER, 0);

	m_ctrList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_SHOWSELALWAYS);

	SetData_List();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

int CMTR_Info_Dlg::Get_GEN_Index2TR(int nTR_Idx)
{
	int nSS_Index = GETVALUE(int, "tr_sta", "tr_ii_ss", nTR_Idx);

	int nND_idx, nND_ii_ss;
	int nGenType;
	int nGenCount = theAppDataMng->GetTableMaxCount(_T("gen_sta"));
	for (int i = 1; i <= (int)nGenCount; i++)
	{
		nGenType = GETVALUE(int, "gen_sta", "gen_type", i);
		if (nGenType != 1)
			continue;

		nND_idx = GETVALUE(int, "gen_sta", "gen_ii_nd", i);
		nND_ii_ss = GETVALUE(int, "nd_dyn_ncpo", "nd_ii_ss", nND_idx);
		if (nSS_Index != nND_ii_ss)
		{
			continue;
		}


		return  i;
	}
	return -1;
}

void CMTR_Info_Dlg::SetData_List()
{
	CString strName,strTableName;
	int nSS_Idx,nBR_Idx, nGBR_idx,nType;
	double dValue;
	int nGen_Index;
	double dGen_r1, dGen_x1, dMtr_x1, dMtr_r0, dMtr_x0, dPosX;

	CString strData[24];
	CDataManager* pDataMng = CDataManager::Instance();

	strTableName = _T("tr_sta");
	int nCount = theAppDataMng->GetTableRealCount((wchar_t*)_T("TR_STA"));
	for (int i = 1; i <= nCount; i++)
	{
		nType = GETVALUE(int, strTableName.GetBuffer(), _T("tr_type"), i);
		if(!(nType  == 1 || nType == 2))
			continue;

		nGen_Index = Get_GEN_Index2TR(i);
		if (nGen_Index == -1)
			continue;

		nSS_Idx = GETVALUE(int, strTableName.GetBuffer(), _T("tr_ii_ss"), i);
		nBR_Idx = GETVALUE(int, strTableName.GetBuffer(), _T("tr_ii_br"), i);
		

		strData[0]		= GETSTRING(_T("ss_sta"), _T("ss_nm"), nSS_Idx);
		strData[1]		= GETSTRING(strTableName.GetBuffer(), _T("tr_nm"), i);

		dValue			= GETVALUE(double		, strTableName.GetBuffer(), _T("tr_tnorkv"), i);
		strData[3].Format(_T("%g"), dValue);

		dValue = GETVALUE(double, strTableName.GetBuffer(), _T("tr_trmva"), i);
		strData[4].Format(_T("%g"), dValue);

		

		dGen_r1 = GETVALUE(double, "gen_sta", "gen_r", nGen_Index);
		dGen_x1 = GETVALUE(double, "gen_sta", "gen_ssx", nGen_Index);

		nBR_Idx = GETVALUE(int, "tr_sta", "tr_ii_br", i);
		nGBR_idx = GETVALUE(int, "br_sta", "br_ii_gbr", nBR_Idx);
		//dMtr_x1 = GETVALUE(double, "gbr_sta", "gbr_posr", nGBR_idx);
		dMtr_x1 = GETVALUE(double, "gbr_sta", "gbr_posx", nGBR_idx);
		dMtr_r0 = GETVALUE(double, "gbr_sta", "gbr_zerr", nGBR_idx);
		dMtr_x0 = GETVALUE(double, "gbr_sta", "gbr_zerx", nGBR_idx);

		/*dValue = GETVALUE(double, _T("br_sta"), _T("br_posr"), i);
		strData[8].Format(_T("%g"), dValue);
		dValue = GETVALUE(double, _T("br_sta"), _T("br_posx"), i);
		strData[9].Format(_T("%g"), dValue);
		dValue = GETVALUE(double, _T("br_sta"), _T("br_zerr"), i);
		strData[10].Format(_T("%g"), dValue);
		dValue = GETVALUE(double, _T("br_sta"), _T("br_zerx"), i);
		strData[11].Format(_T("%g"), dValue);
		dValue = GETVALUE(double, _T("br_sta"), _T("br_zerx"), i);
		strData[12].Format(_T("%g"), dValue);*/

		dPosX = dGen_x1 + dMtr_x1;

		strData[8].Format(_T("%g"), dGen_r1);
		strData[9].Format(_T("%g"), dPosX);
		strData[10].Format(_T("%g"), dMtr_r0);
		strData[11].Format(_T("%g"), dMtr_x0);
		strData[12].Format(_T("%g"), dMtr_x1);

		strData[22].Format(_T("%d"), i);
		strData[23].Format(_T("%d"), nGen_Index);

		m_ctrList.InsertItem(m_ctrList.GetItemCount(), strData[0]);
		for (int k = 1; k < 24; k++)
		{
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, k, strData[k]);
			if (k > 2 && k < 13)
				m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, k, LIST_TYPE_EDIT, NULL);
		}
	}
	
}


void CMTR_Info_Dlg::OnBnClickedMtrInfoDlgBtn1()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, L"Mtr Files(*.xls)|*.xls", NULL);
	if (dlg.DoModal() != IDOK)
		return;
	// OLE Variant for Optional.

	COleVariant VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	_Application objApp;
	_Workbook objBook;
	Workbooks objBooks;
	Worksheets objSheets;
	_Worksheet objSheet;
	Range objRange;
	VARIANT ret;
	//CProtection51S* p51S;
	//	if( !pOffDM->GetMtrList()->IsEmpty() )
	//	{
	//		for( POSITION pos = pOffDM->GetMtrList()->GetHeadPosition(); pos; )
	//		{
	//			pmtr = pOffDM->GetMtrList()->GetNext( pos );
	//			delete pmtr;
	//		}
	//		pOffDM->GetMtrList()->RemoveAll();
	//	}

	CString path, strTmp;
	// Instantiate Excel and open an existing workbook.
	if (objApp.CreateDispatch(L"Excel.Application") == NULL) {
		AfxMessageBox(L"엑셀 프로그램을 구동할 수 없습니다! \n설치 확인하십시요.");
		return;
	}
	/////////////////
	CString strSS, strBank, strOA, strImp, strNGR, strR1, strX1, strR0, strX0;
	CString strType1, strTap1, strLever1, strType2, strTap2, strLever2, strCT;
	CString	strLock, strV, strULTC, strSC;
	/////////////////
	objBooks = objApp.GetWorkbooks();
	path.Format(L"%s", dlg.GetPathName());
	if (!path.IsEmpty()) {
		objBook = objBooks.Open(path,
			VOptional, VOptional, VOptional, VOptional,
			VOptional, VOptional, VOptional, VOptional,
			VOptional, VOptional, VOptional, VOptional);
		objSheets = objBook.GetWorksheets();
		short cc = (short)objSheets.GetCount();
		if (cc != 1)
		{
			AfxMessageBox(L"임피던스 파일 형식이 다릅니다.");
			objBook.Close(COleVariant((short)FALSE), VOptional, VOptional);
			objApp.Quit();
			return;
		}
		//objSheet = objSheets.GetItem(COleVariant( (short)1 ));
		//objRange = objSheet.GetRange(COleVariant(L"B2"), COleVariant(L"E1000"));
		//ret = objRange.GetValue();
		//COleSafeArray sa1(ret);
		long lNumRows;
		long lNumCols;
		//sa1.GetUBound(1, &lNumRows);
		//sa1.GetUBound(2, &lNumCols);
		long index[2];
		VARIANT val;
		int r;
		double dVal;
		POSITION pos;
		////Progress Dialog
		//CProgressDlg* pdlg = new CProgressDlg();
		//pdlg->Create();
		/*pdlg->SetStatus("변전소 위상각 정보를 불러오는 중...");
		pdlg->SetRange(0,lNumRows);
		for(r=1;r<=lNumRows;r++)
		{
		index[0]=r,index[1]=1;
		sa1.GetElement(index,&val);
		if( val.vt == VT_NULL )
		break;
		strSS = val.bstrVal;
		index[0]=r,index[1]=3;
		sa1.GetElement(index,&val);
		dVal = val.dblVal;
		for( pos = pOffDM->GetMtrList()->GetHeadPosition(); pos; )
		{
		pMtr = pOffDM->GetMtrList()->GetNext( pos );
		if( pMtr->m_strSS == strSS )
		SetAngle( strSS, dVal );
		}
		pdlg->StepIt();
		}*/

		objSheet = objSheets.GetItem(COleVariant((short)1));
		objRange = objSheet.GetRange(COleVariant(L"A2"), COleVariant(L"S1000"));
		ret = objRange.GetValue();
		COleSafeArray sa(ret);
		sa.GetUBound(1, &lNumRows);
		sa.GetUBound(2, &lNumCols);
		//pdlg->SetInit(lNumRows, L"변전소 모선 등가임피던스 정보를 불러오는 중...");

		CString strData[22];

		for (r = 1; r <= lNumRows; r++)
		{
			index[0] = r, index[1] = 1;
			sa.GetElement(index, &val);
			if (val.vt == VT_NULL)
				break;
			strSS = val.bstrVal;

			

			index[0] = r, index[1] = 2;
			sa.GetElement(index, &val);
			if (val.vt == VT_BSTR)
				strBank = val.bstrVal;
			else
				strBank.Format(L"%g", val.dblVal);

			index[0] = r, index[1] = 3;
			sa.GetElement(index, &val);
			strLock.Format(L"%g", val.dblVal);
			index[0] = r, index[1] = 4;
			sa.GetElement(index, &val);
			strV.Format(L"%g", val.dblVal);
			index[0] = r, index[1] = 5;
			sa.GetElement(index, &val);
			strOA.Format(L"%g", val.dblVal);
			/*index[0]=r,index[1]=5;
			sa.GetElement(index,&val);
			strImp.Format(L"%g", val.dblVal);*/
			index[0] = r, index[1] = 6;
			sa.GetElement(index, &val);
			strNGR.Format(L"%g", val.dblVal);
			index[0] = r, index[1] = 7;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strR1.Format(L"%g", val.dblVal);
			else strR1.Empty();
			index[0] = r, index[1] = 8;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strX1.Format(L"%g", val.dblVal);
			else strX1.Empty();
			index[0] = r, index[1] = 9;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strR0.Format(L"%g", val.dblVal);
			else strR0.Empty();
			index[0] = r, index[1] = 10;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strX0.Format(L"%g", val.dblVal);
			else strX0.Empty();
			index[0] = r, index[1] = 11;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strCT = val.bstrVal;
			else strType1.Empty();
			index[0] = r, index[1] = 12;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strType1 = val.bstrVal;
			else strType1.Empty();
			index[0] = r, index[1] = 13;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strTap1.Format(L"%g", val.dblVal);
			else strTap1.Empty();
			index[0] = r, index[1] = 14;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strLever1.Format(L"%g", val.dblVal);
			else strLever1.Empty();
			index[0] = r, index[1] = 15;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strType2 = val.bstrVal;
			else strType2.Empty();
			index[0] = r, index[1] = 16;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strTap2.Format(L"%g", val.dblVal);
			else strTap2.Empty();
			index[0] = r, index[1] = 17;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strLever2.Format(L"%g", val.dblVal);
			else strLever2.Empty();
			index[0] = r, index[1] = 18;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strULTC.Format(L"%g", val.dblVal);
			else strULTC.Empty();
			index[0] = r, index[1] = 19;
			sa.GetElement(index, &val);
			if (val.vt != VT_EMPTY) strSC.Format(L"%g", val.dblVal);
			else strSC.Empty();


			CString strName, strNo;
			int nID;
			//CInfo_MTR *pMTR;
			for (int i = 0; i < m_ctrList.GetItemCount(); i++)
			{
				strName = m_ctrList.GetItemText(i, 0);
				strNo = m_ctrList.GetItemText(i, 1);
				if (strSS == strName && strNo == strBank)
				{
					//nID = _wtoi(m_ctrList.GetItemText(i, 21));
					//pMTR = m_pData->GetMTR(nID);

					strData[0] = strSS;
					strData[1] = strBank;
				//	strData[2] = strSS;
				//	strData[3] = strSS;
					strData[4] = strOA;
					strData[5] = strImp;
					strData[6] = strNGR;
				//	strData[7] = strULTC;
					strData[8] = strR1;
					strData[9] = strX1;
					strData[10] = strR0;
					strData[11] = strX0;
					strData[12] = strCT;
					strData[13] = strType1;
					strData[14] = strTap1;
					strData[15] = strLever1;
					strData[16] = strType2;
					strData[17] = strTap2;
					strData[18] = strLever2;
					strData[19] = strULTC;
					strData[20] = strSC;
				//	strData[21] = strSS;
			

					//m_ctrList.InsertItem(m_ctrList.GetItemCount(), strData[0]);
					for (int k = 2; k < 22; k++)
					{
						m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, k, strData[k]);
						
					}

					/*if (pMTR)
					{
						pMTR->m_dOA = _wtof(strOA);
						pMTR->m_mtr_imp = _wtof(strImp);
						pMTR->m_ngr = _wtof(strNGR);
						pMTR->m_positive_R = _wtof(strR1);
						pMTR->m_positive_X = _wtof(strX1);
						pMTR->m_zero_R = _wtof(strR0);
						pMTR->m_zero_X = _wtof(strX0);
						pMTR->m_nULTC_Tab = _wtoi(strULTC);
						pMTR->m_dSC_MVar = _wtoi(strSC);

						if (pMTR->m_pProtectionSw)
						{
							p51S = (CProtection51S*)pMTR->m_pProtectionSw;
						}
						else
						{
							p51S = new CProtection51S();
							pMTR->m_pProtectionSw = p51S;
						}

						p51S->m_nCTRatio = _wtoi(strCT);
						p51S->m_nOCRType = p51S->GetProtectionTypeID2STR(strType1);
						p51S->m_dOCRTap = _wtof(strTap1);
						p51S->m_dOCRLever = _wtof(strLever1);
						p51S->m_nOCGRType = p51S->GetProtectionTypeID2STR(strType2);
						p51S->m_dOCGRTap = _wtof(strTap2);
						p51S->m_dOCGRLever = _wtof(strLever2);
					}*/
					break;

				}

			}
			//pdlg->SetStepit();
		}
		//delete pdlg;
		objBook.Close(COleVariant((short)FALSE), VOptional, VOptional);
		objApp.Quit();
	}
}


void CMTR_Info_Dlg::OnBnClickedMtrInfoDlgBtn2()
{
	CString strIdx,strData[7];
	int nBR_Idx, nGBR_idx,nIdx,nGen_Index;
	double dGen_r1, dGen_x1, dMtr_x1, dMtr_r0, dMtr_x0, dPosX;

	for (int i = 0; i < m_ctrList.GetItemCount(); i++)
	{
		strIdx = m_ctrList.GetItemText(i,22);
		nIdx = _wtoi(strIdx);
		nBR_Idx = GETVALUE(int, _T("tr_sta"), _T("tr_ii_br"), nIdx);

		strData[0] = m_ctrList.GetItemText(i, 3);
		strData[1] = m_ctrList.GetItemText(i, 4);
		strData[2] = m_ctrList.GetItemText(i, 8);
		strData[3] = m_ctrList.GetItemText(i, 9);
		strData[4] = m_ctrList.GetItemText(i, 10);
		strData[5] = m_ctrList.GetItemText(i, 11);
		strData[6] = m_ctrList.GetItemText(i, 12);

		

		dGen_r1 = _wtof(strData[2]);
		dPosX = _wtof(strData[3]);
		dMtr_r0 = _wtof(strData[4]);
		dMtr_x0 = _wtof(strData[5]);
		dMtr_x1 = _wtof(strData[6]);

		strIdx = m_ctrList.GetItemText(i, 23);
		nGen_Index = _wtoi(strIdx);

		nGBR_idx = GETVALUE(int, _T("br_sta"), _T("br_ii_gbr"), nBR_Idx);

		dGen_x1 = dPosX - dMtr_x1;

		if (dGen_x1 < 0)
			dGen_x1 = 0;

		PUTDOUBLE2VALUE(_T("gen_sta"), _T("gen_r"), nGen_Index, (double)dGen_r1);
		PUTDOUBLE2VALUE(_T("gen_sta"), _T("gen_ssx"), nGen_Index, (double)dGen_x1);

		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_posx"), nGBR_idx, (double)dMtr_x1);
		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_zerr"), nGBR_idx, (double)dMtr_r0);
		PUTDOUBLE2VALUE(_T("gbr_sta"), _T("gbr_zerx"), nGBR_idx, (double)dMtr_x0);

		PUTDOUBLE2VALUE(_T("tr_sta"), _T("tr_tnorkv"), nIdx, (double)_wtof(strData[0]));
		PUTDOUBLE2VALUE(_T("tr_sta"), _T("tr_trmva"), nIdx, (double)_wtof(strData[1]));

	/*
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_posr"), nBR_Idx, (double)_wtof(strData[2]));
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_posx"), nBR_Idx, (double)_wtof(strData[3]));
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_zerr"), nBR_Idx, (double)_wtof(strData[4]));
		PUTDOUBLE2VALUE(_T("br_sta"), _T("br_zerx"), nBR_Idx, (double)_wtof(strData[5]));*/
	}

}


void CMTR_Info_Dlg::OnBnClickedMtrInfoDlgBtn3()
{
	CDialogEx::OnOK();
}
