// CLine_Type_Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "CLine_Type_Dlg.h"
#include "afxdialogex.h"
#include "dbexcept.h"
#include "../DataManager/CDataManager.h"

// CLine_Type_Dlg 대화 상자

IMPLEMENT_DYNAMIC(CLine_Type_Dlg, CDialogEx)

CLine_Type_Dlg::CLine_Type_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LINETYPE_DLG, pParent)
{
	m_nMax_ID = -1;
}

CLine_Type_Dlg::~CLine_Type_Dlg()
{
}

void CLine_Type_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LINETYPE_DLG_LIST1, m_ctrList);
}


BEGIN_MESSAGE_MAP(CLine_Type_Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_LINETYPE_DLG_BTN1, &CLine_Type_Dlg::OnBnClickedLinetypeDlgBtn1)
	ON_BN_CLICKED(IDC_LINETYPE_DLG_BTN2, &CLine_Type_Dlg::OnBnClickedLinetypeDlgBtn2)
	ON_BN_CLICKED(IDC_LINETYPE_DLG_BTN3, &CLine_Type_Dlg::OnBnClickedLinetypeDlgBtn3)
END_MESSAGE_MAP()


// CLine_Type_Dlg 메시지 처리기


BOOL CLine_Type_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ctrList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_SHOWSELALWAYS);
	//	m_ctrList.m_nEditLimit = 3;
	CString strTmp;
	LV_COLUMN lvcolumn;
	CString strlist[10] = { _T("ID"),_T("선종"),_T("상선"),_T("중성선"),_T("R(+)[%Ω/㎞]")
					,_T("X1(+)[%Ω/㎞]"),_T("X(+)[%Ω/㎞]"),_T("R(0)[%Ω/㎞]"),_T("X(0)[%Ω/㎞]"),_T("허용전류(A)")};
	int width[10] = { 0,55,100,100,92,98,92,92,92,85 };

	CRect r;
	m_ctrList.GetWindowRect(r);
	for(int i = 0 ;i < 10 ; i++)
		m_ctrList.InsertColumn(i, strlist[i], LVCFMT_CENTER, 80);

	SetData_List();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CLine_Type_Dlg::SetData_List()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CCommand<CManualAccessor> rs;
	struct MYBIND* pBind = NULL;
	ULONG   ulFields;

	CString strSQL;
	int nID;

	CString strData[10];

	TRY
	{
		ulFields = 10;
		pBind = new MYBIND[ulFields];
		rs.CreateAccessor(ulFields, pBind, sizeof(MYBIND)*ulFields);
		for (ULONG l = 0; l < ulFields; l++)
			rs.AddBindEntry(l + 1, DBTYPE_WSTR, sizeof(TCHAR) * 50, &pBind[l].szValue,
			NULL, &pBind[l].dwStatus);

		if (rs.Open(pDataMng->m_Session_OD, _T("Select linetype_id,overhead_cable,phase_linetype,neutral_linetype\
												,positive_r,positive_x_1p,positive_x,zero_r,zero_x,thermal_limit from Linetype_code")) != S_OK)
			AfxThrowOLEDBException(rs.m_spCommand, IID_ICommand);
		while (rs.MoveNext() == S_OK)
		{
			if (pBind[0].dwStatus == DBSTATUS_S_ISNULL)
				wcscpy_s(pBind[0].szValue, _T(""));

			strData[0] = pBind[0].szValue;
			nID = _wtoi(pBind[0].szValue);
			if (nID > m_nMax_ID)
			{
				m_nMax_ID = nID;
			}

			strData[1]		= pBind[1].szValue;
			strData[2]		= pBind[2].szValue;
			strData[3]		= pBind[3].szValue;
			strData[4]		= pBind[4].szValue;
			strData[5]		= pBind[5].szValue;
			strData[6]		= pBind[6].szValue;
			strData[7]		= pBind[7].szValue;
			strData[8]		= pBind[8].szValue;
			strData[9]		= pBind[9].szValue;
			/*strData[10]		= pBind[10].szValue;
			strData[11]		= pBind[11].szValue;*/

			m_ctrList.InsertItem(m_ctrList.GetItemCount(), strData[0]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 1		,strData[1]	);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 2		,strData[2]	);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 3		,strData[3]	);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 4		,strData[4]	);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 5		,strData[5]	);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 6		,strData[6]	);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 7		,strData[7]	);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 8		,strData[8]	);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 9		,strData[9]	);
			/*m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 10		,strData[10]);
			m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 11		,strData[11]);*/


			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 1, LIST_TYPE_EDIT, NULL);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 2, LIST_TYPE_EDIT, NULL);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 3, LIST_TYPE_EDIT, NULL);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 4, LIST_TYPE_EDIT, NULL);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 5, LIST_TYPE_EDIT, NULL);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 6, LIST_TYPE_EDIT, NULL);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 7, LIST_TYPE_EDIT, NULL);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 8, LIST_TYPE_EDIT, NULL);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 9, LIST_TYPE_EDIT, NULL);
		/*	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 10, LIST_TYPE_EDIT, NULL);
			m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 11, LIST_TYPE_EDIT, NULL);*/


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

		m_nMax_ID++;
}

void CLine_Type_Dlg::OnBnClickedLinetypeDlgBtn1()
{
	CString strData;
	strData.Format(_T("%d"), m_nMax_ID);
	m_nMax_ID++;

	m_ctrList.InsertItem(m_ctrList.GetItemCount(), strData);
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 1		, _T("0"));
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 2		, _T(""));
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 3		, _T(""));
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 4		, _T("0.0000"));
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 5		, _T("0.0000"));
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 6		, _T("0.0000"));
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 7		, _T("0.0000"));
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 8		, _T("0.0000"));
	m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 9		, _T("0.0000"));
	//m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 10		, _T("0.0000"));
	//m_ctrList.SetItemText(m_ctrList.GetItemCount() - 1, 11		, _T("0.0000"));


	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 1, LIST_TYPE_EDIT, NULL);
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 2, LIST_TYPE_EDIT, NULL);
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 3, LIST_TYPE_EDIT, NULL);
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 4, LIST_TYPE_EDIT, NULL);
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 5, LIST_TYPE_EDIT, NULL);
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 6, LIST_TYPE_EDIT, NULL);
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 7, LIST_TYPE_EDIT, NULL);
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 8, LIST_TYPE_EDIT, NULL);
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 9, LIST_TYPE_EDIT, NULL);
	/*m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 10, LIST_TYPE_EDIT, NULL);
	m_ctrList.SetItemInfo(m_ctrList.GetItemCount() - 1, 11, LIST_TYPE_EDIT, NULL);*/

	
}


void CLine_Type_Dlg::OnBnClickedLinetypeDlgBtn2()
{
	int nPos = m_ctrList.GetSelectionMark();

	if (nPos == -1)
		return;

	m_ctrList.DeleteItem(nPos);
}


void CLine_Type_Dlg::OnBnClickedLinetypeDlgBtn3()
{
	CDataManager* pDataMng = CDataManager::Instance();

	CString strData[12], strSQL;

	strSQL.Format(_T("delete * from LINETYPE_CODE"));

	pDataMng->SQLDBExcute(&pDataMng->m_Session_localData, strSQL);
	for (int i = 0; i < m_ctrList.GetItemCount(); i++)
	{
		strData[0]		= m_ctrList.GetItemText(i, 0);
		strData[1]		= m_ctrList.GetItemText(i, 1);
		strData[2]		= m_ctrList.GetItemText(i, 2);
		strData[3]		= m_ctrList.GetItemText(i, 3);
		strData[4]		= m_ctrList.GetItemText(i, 4);
		strData[5]		= m_ctrList.GetItemText(i, 5);
		strData[6]		= m_ctrList.GetItemText(i, 6);
		strData[7]		= m_ctrList.GetItemText(i, 7);
		strData[8]		= m_ctrList.GetItemText(i, 8);
		strData[9]		= m_ctrList.GetItemText(i, 9);
	/*	strData[10]		= m_ctrList.GetItemText(i, 10);
		strData[11]		= m_ctrList.GetItemText(i, 11);*/


		strSQL.Format(_T("insert into LINETYPE_CODE Values(%d,%d,'%s','%s',%lf,%lf,%lf,%lf,%lf,%lf)"), _wtoi(strData[0])
			, _wtoi(strData[1])
			, strData[2]
			, strData[3]
			, _wtof(strData[4])
			, _wtof(strData[5])
			, _wtof(strData[6])
			, _wtof(strData[7])
			, _wtof(strData[8])
			, _wtof(strData[9]));
		/*	, _wtof(strData[10])
			, _wtof(strData[11]));*/

		pDataMng->SQLDBExcute(&pDataMng->m_Session_localData, strSQL);
	}
}
