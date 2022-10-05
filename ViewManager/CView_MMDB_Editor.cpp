#include "pch.h"
#include "CView_MMDB_Editor.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"
#include "resource.h"

CView_MMDB_Editor::CView_MMDB_Editor()
{

	m_pGridCtrl = NULL;

}

CView_MMDB_Editor::~CView_MMDB_Editor()
{
	m_font_Combobox.DeleteObject();

	if (m_vecACMSDB.size() > 0)
	{
		for (int i = 0; i < (int)m_vecACMSDB.size(); ++i)
			delete m_vecACMSDB[i];

		m_vecACMSDB.clear();
	}

	if (m_pGridCtrl)
	{
		delete m_pGridCtrl;
		m_pGridCtrl = NULL;
	}

	delete CView_Manager::Instance();
}

BEGIN_MESSAGE_MAP(CView_MMDB_Editor, CView_Base)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(ID_APP_EDITOR_COMBO_1, &CView_MMDB_Editor::OnMMDB_Editor_Combo_SelectChange)
	ON_MESSAGE(GRIDCTRL_SENDMSGDATA, &CView_MMDB_Editor::OnGridCtrlSendMassageData)
END_MESSAGE_MAP()

void CView_MMDB_Editor::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	Create_Combobox();
	Create_ListCtrl();
}


void CView_MMDB_Editor::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);

	OnPrepareDC(&dc);
	Graphics						graphics(dc.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();
	//////////////////////////////////////////////////////////////////////
	
	pViewMng->DrawArea_List(&dc, graphics, m_rectGrid);
	pViewMng->DrawArea_Base(&dc, graphics, m_rectCombo);
	pViewMng->DrawArea_Title(&dc, graphics, m_rectTitle, _T("MMDB Editor"));
}



BOOL CView_MMDB_Editor::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CView_Base::OnEraseBkgnd(pDC);
}


void CView_MMDB_Editor::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);

	ListCtrl_MoveSize();
	Combobox_MoveSize();
}


void CView_MMDB_Editor::InitData()
{
	if (m_vecACMSDB.size() > 0)
		return;

	VECWSTR vecTableName;
	theAppDataMng->GetTableNames(vecTableName);

	CACMTableInfor*					pTableInfor;
	CString strName;

	VECWSTR::iterator				_itertable;

	for (_itertable = vecTableName.begin(); _itertable != vecTableName.end(); ++_itertable)
	{
		pTableInfor													= new CACMTableInfor;
		pTableInfor->m_szName.Format(_T("%s") , ((wstring) *_itertable).c_str() );
		pTableInfor->m_nDataSize									= theAppDataMng->GetTableRealCount((wchar_t*)pTableInfor->m_szName.GetBuffer());
		pTableInfor->SetFieldName();
		m_vecACMSDB.push_back(pTableInfor);
	}

	if (m_vecACMSDB.size() > 0)
	{
		for (int i = 0; i < (int)m_vecACMSDB.size(); i++)
		{
			m_ctrCombo.AddString(m_vecACMSDB[i]->m_szName);
			//m_ctrCombo.SetItemData(nComboIndex, i);
		}
		m_ctrCombo.SetCurSel(0);
		OnMMDB_Editor_Combo_SelectChange();
	}

}

void CView_MMDB_Editor::Create_Combobox()
{
	m_font_Combobox.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	if (!m_ctrCombo.Create(WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_SORT
		, CRect(100, 100, 200, 200), this, ID_APP_EDITOR_COMBO_1))
	{
		AfxMessageBox(_T("Create RPF ComboBox Fail.\n"));
		return;
	}
	

	m_ctrCombo.SetTextFont(&m_font_Combobox);
	m_ctrCombo.SetNormalPositionColor(RGB(255, 255, 255), RGB(0, 0, 0));
	m_ctrCombo.SetBitmapID(IDB_COMBOBOX_LEFT, IDB_COMBOBOX_RIGHT, IDB_COMBOBOX_TOP, IDB_COMBOBOX_BOTTOM);
	m_ctrCombo.SetTextStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_ctrCombo.SetDropDownHeight(10);


}

void CView_MMDB_Editor::Create_ListCtrl()
{

	m_pGridCtrl = new CGridCtrl(2, 2, 1, 1);

	CRect							_rect(0, 0, 0, 0);
	GetClientRect(&_rect);
	m_pGridCtrl->Create(_rect, this, VIEW_ID_EDITOR_MMDATA);

	m_pGridCtrl->EnableDragAndDrop(FALSE);	
	m_pGridCtrl->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(255,255,255));
	m_pGridCtrl->SetEditable(true);
	m_pGridCtrl->SetAutoSizeStyle();
	m_pGridCtrl->SetFixedColumnSelection(TRUE);
	m_pGridCtrl->SetFixedRowSelection(TRUE);
	m_pGridCtrl->EnableColumnHide();
	m_pGridCtrl->SetCompareFunction(CGridCtrl::pfnCellNumericCompare);


	/*m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	CRect rect[2];
	rect[0] = CRect(10, 50, 350, 500);
	m_ctrList[0].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, rect[0], this, ID_APP_RPF_LIST_1);
	m_ctrList[0].InsertColumn(0, _T("개폐기"), HDF_LEFT, 175);
	m_ctrList[0].InsertColumn(1, _T("전압(측정값)"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(2, _T("전압(추정값)"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(3, _T("유효전력(측정값)"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(4, _T("유효전력(추정값)"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(5, _T("CT극성(설정값)"), HDF_LEFT, 100);
	m_ctrList[0].InsertColumn(6, _T("CT극성 보정"), HDF_LEFT, 80);
	m_ctrList[0].InsertColumn(7, _T("유효3상전력(추정값)"), HDF_LEFT, 140);
	m_ctrList[0].InsertColumn(8, _T("idx"), HDF_LEFT, 0);
	m_ctrList[0].ShowWindow(SW_SHOW);
	m_ctrList[0].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[0].m_HeaderCtrl.SetHeight(27);
	m_ctrList[0].m_HeaderCtrl.SetFlat();
	m_ctrList[0].m_HeaderCtrl.SetFlat();
	m_ctrList[0].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[0].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[0].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[0].SetBgColor(RGB(255, 255, 255));
	m_ctrList[0].SetUnderLine();
	m_ctrList[0].SetColorUnderLine(RGB(210, 210, 210));
	m_ctrList[0].SetTextFont(&m_listfont);
	m_ctrList[0].SetRowHeight(25);


	rect[1] = CRect(10, 50, 350, 500);
	m_ctrList[1].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, rect[1], this, ID_APP_RPF_LIST_2);
	m_ctrList[1].InsertColumn(0, _T("선택"), HDF_LEFT, 0);
	m_ctrList[1].InsertColumn(1, _T("구간 전원측 개폐기"), HDF_LEFT, 250);
	m_ctrList[1].InsertColumn(2, _T("총 부하(L+A+B)"), HDF_LEFT, 120);
	m_ctrList[1].InsertColumn(3, _T("Net 부하(L)"), HDF_LEFT, 120);
	m_ctrList[1].InsertColumn(4, _T("총 발전(A+B)"), HDF_LEFT, 120);
	m_ctrList[1].InsertColumn(5, _T("측정 발전량(A)"), HDF_LEFT, 120);
	m_ctrList[1].InsertColumn(6, _T("추정 발전량(B)"), HDF_LEFT, 120);
	m_ctrList[1].ShowWindow(SW_SHOW);
	m_ctrList[1].SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrList[1].m_HeaderCtrl.SetHeight(27);
	m_ctrList[1].m_HeaderCtrl.SetFlat();
	m_ctrList[1].m_HeaderCtrl.SetFlat();
	m_ctrList[1].m_HeaderCtrl.SetTextFont(&m_headerfont);
	m_ctrList[1].m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	m_ctrList[1].m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	m_ctrList[1].SetBgColor(RGB(255, 255, 255));
	m_ctrList[1].SetUnderLine();
	m_ctrList[1].SetColorUnderLine(RGB(215, 214, 214));
	m_ctrList[1].SetTextFont(&m_listfont);
	m_ctrList[1].SetRowHeight(25);*/



}

void	CView_MMDB_Editor::ListCtrl_MoveSize()
{
	if (m_pGridCtrl == NULL)							return;

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	/////////////////////////////////////////////////////////////////////////// 하단 리스트 
	/////////////////////////////////////////////타이틀  
	m_rectTitle = _rect;
	m_rectTitle.right = m_rectTitle.left + 150;
	m_rectTitle.bottom = m_rectTitle.top + 29;

	/////////////////////////////////////////////타이틀  

	/////////////////////////////////////////////리스트  
	CRect rectList;
	m_rectGrid = _rect;

	rectList = m_rectGrid;
	rectList.left -= 1;
	rectList.right += 1;
	rectList.top += 74;
	rectList.bottom = rectList.bottom - 1;
	m_pGridCtrl->MoveWindow(rectList);
}


void	CView_MMDB_Editor::Combobox_MoveSize()
{
	if (m_pGridCtrl == NULL)							return;

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);

	m_rectCombo = _rect;
	m_rectCombo.top = m_rectCombo.top + 29;
	m_rectCombo.bottom = m_rectCombo.top + 45;

	CRect rectCombo = m_rectCombo;

	rectCombo.InflateRect(-8, -10);
	rectCombo.right = rectCombo.left + 281;
	m_ctrCombo.MoveWindow(rectCombo);
}

void CView_MMDB_Editor::OnMMDB_Editor_Combo_SelectChange()
{
	int nSel = m_ctrCombo.GetCurSel();

	if (nSel == -1)
		return;

	CString	strTableName;

	m_ctrCombo.GetLBText(nSel, strTableName);

	CACMTableInfor* pTableInfor = GetTableInfo2Name(strTableName);
	

	if (pTableInfor)
	{
		pTableInfor->m_nDataSize = theAppDataMng->GetTableRealCount((wchar_t*)pTableInfor->m_szName.GetBuffer());
		SetACMdataView(pTableInfor);
	}
	
	Invalidate();

	m_pGridCtrl->SetFocus();
}

CACMTableInfor*	CView_MMDB_Editor::GetTableInfo2Name(CString strName)
{
	CACMTableInfor* pInfo;

	for (int i = 0; i < m_vecACMSDB.size(); i++)
	{
		if (m_vecACMSDB[i]->m_szName.Compare(strName) == 0)
		{
			return m_vecACMSDB[i];
		}
	}

	return NULL;
}

void CView_MMDB_Editor::SetGridCtrlCount(int nRow, int nCol, int nFixRow, int nFixCol)
{
	TRY{
		m_pGridCtrl->SetRowCount(nRow + 1);
		m_pGridCtrl->SetColumnCount(nCol + 1);
		m_pGridCtrl->SetFixedRowCount(nFixRow);
		m_pGridCtrl->SetFixedColumnCount(nFixCol);
	}
	CATCH(CMemoryException, e)
	{
		e->ReportError();
		return;
	}
	END_CATCH
}

void CView_MMDB_Editor::SetGridCtrlTitle(CACMTableInfor* pTableInfor)
{
	if (pTableInfor == NULL)
	{
		return;
	}

	CString							str(_T(""));
	GV_ITEM							ItemMain = { 0, };
	ItemMain.mask = GVIF_TEXT;
	ItemMain.row = 0;
	ItemMain.col = 0;
	ItemMain.strText = _T("▶");
	m_pGridCtrl->SetItem(&ItemMain);

	CString							szColName;
	int								i(0), j(0), nColCnt(1);
	for (i = 0; i < (int)pTableInfor->m_vecField.size(); i++)
	{
		if (pTableInfor->m_vecField[i].nVarID != 1 && pTableInfor->m_vecField[i].nVarCount > 1)
		{
			for (j = 0; j < pTableInfor->m_vecField[i].nVarCount; j++)
			{
				//memset(szColName, 0x00, sizeof(szColName));
				szColName.Format(_T("%s_%d"), CA2W(pTableInfor->m_vecField[i].szName.GetValue()).m_psz, j + 1);
				GV_ITEM						ItemSub = { 0, };
				ItemSub.mask = GVIF_TEXT;
				ItemSub.row = 0;
				ItemSub.col = nColCnt;
				ItemSub.strText = szColName;
				m_pGridCtrl->SetItem(&ItemSub);
				++nColCnt;
			}
		}
		else {
			GV_ITEM						ItemSub = { 0, };
			ItemSub.mask = GVIF_TEXT;
			ItemSub.row = 0;
			ItemSub.col = nColCnt;
			ItemSub.strText = CA2W(pTableInfor->m_vecField[i].szName.GetValue()).m_psz;
			m_pGridCtrl->SetItem(&ItemSub);
			++nColCnt;
		}
	}
}

void CView_MMDB_Editor::SetGridCtrlData(CACMTableInfor* pTableInfor)
{
	if (pTableInfor == NULL)
	{
		return;
	}

	int								i(0), j(0), k(0), nColCnt(0);
	for (i = 0; i < pTableInfor->GetRecordSize(); i++)
	{
		nColCnt = 0;
		for (j = 0; j < (int)pTableInfor->m_vecField.size(); j++)
		{
			if (pTableInfor->m_vecField[j].nVarID != 1 && pTableInfor->m_vecField[j].nVarCount > 1)
			{
				for (k = 0; k < pTableInfor->m_vecField[j].nVarCount; k++)
				{
					switch (pTableInfor->m_vecField[j].nVarID)
					{
					case 2: { SetGridCtrlItemData(i, nColCnt, GETVALUE_AT(int, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1, k + 1)); }; break;
					case 3: { SetGridCtrlItemData(i, nColCnt, GETVALUE_AT(int, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1, k + 1)); }; break;
					case 4: { SetGridCtrlItemData(i, nColCnt, GETVALUE_AT(long, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1, k + 1)); }; break;
					case 5: { SetGridCtrlItemData(i, nColCnt, GETVALUE_AT(long, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1, k + 1)); }; break;
					case 6: { SetGridCtrlItemData(i, nColCnt, GETVALUE_AT(float, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1, k + 1)); }; break;
					case 7: { SetGridCtrlItemData(i, nColCnt, GETVALUE_AT(double, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1, k + 1)); }; break;
					case 8: { SetGridCtrlItemData(i, nColCnt, GETVALUE_AT(unsigned long long, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1, k + 1)); }; break;
					}
					++nColCnt;
				}
			}
			else {
				switch (pTableInfor->m_vecField[j].nVarID)
				{
				case 1: { SetGridCtrlItemData(i, nColCnt, GETSTRING((wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1)); }; break;
				case 2: { SetGridCtrlItemData(i, nColCnt, GETVALUE(int, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1)); }; break;
				case 3: { SetGridCtrlItemData(i, nColCnt, GETVALUE(int, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1)); }; break;
				case 4: { SetGridCtrlItemData(i, nColCnt, GETVALUE(long, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1)); }; break;
				case 5: { SetGridCtrlItemData(i, nColCnt, GETVALUE(long, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1)); }; break;
				case 6: { SetGridCtrlItemData(i, nColCnt, GETVALUE(float, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1)); }; break;
				case 7: { SetGridCtrlItemData(i, nColCnt, GETVALUE(double, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1)); }; break;
				case 8: { SetGridCtrlItemData(i, nColCnt, GETVALUE(unsigned long long, (wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[j].szName.GetValue()).m_psz, i + 1)); }; break;
				}
				++nColCnt;
			}
		}
	}
}

void CView_MMDB_Editor::SetGridCtrlItemData(int nRow, int nCol, short nValue)
{
	SetGridCtrlItemData(nRow, nCol, (long)nValue);
}

void CView_MMDB_Editor::SetGridCtrlItemData(int nRow, int nCol, int nValue)
{
	SetGridCtrlItemData(nRow, nCol, (long)nValue);
}

void CView_MMDB_Editor::SetGridCtrlItemData(int nRow, int nCol, long nValue)
{
	CString							szValue(_T(""));
	szValue.Format(_T("%d"), nValue);
	SetGridCtrlItemData(nRow, nCol, szValue);
}

void CView_MMDB_Editor::SetGridCtrlItemData(int nRow, int nCol, float fValue)
{
	SetGridCtrlItemData(nRow, nCol, (double)fValue);
}

void CView_MMDB_Editor::SetGridCtrlItemData(int nRow, int nCol, double dValue)
{
	CString							szValue(_T(""));
	szValue.Format(_T("%.4f"), dValue);
	SetGridCtrlItemData(nRow, nCol, szValue);
}

void CView_MMDB_Editor::SetGridCtrlItemData(int nRow, int nCol, unsigned long long ullValue)
{
	CString							szValue(_T(""));
	szValue.Format(_T("%I64u"), ullValue);
	SetGridCtrlItemData(nRow, nCol, szValue);
}

void CView_MMDB_Editor::SetGridCtrlItemData(int nRow, int nCol, char* szValue)
{
	CA2W							szA2Wvalue(szValue);
	CString							szTValue(szA2Wvalue.m_psz);
	SetGridCtrlItemData(nRow, nCol, szTValue);
}

void CView_MMDB_Editor::SetGridCtrlItemData(int nRow, int nCol, CString szValue)
{
	if (m_pGridCtrl->GetRowCount() - 1 < nRow)					return;
	if (m_pGridCtrl->GetColumnCount() - 1 < nCol)				return;

	if (nCol == 0)
	{
		CString						str(_T(""));
		str.Format(_T("%d"), nRow + 1);

		GV_ITEM						ItemMain = { 0, };
		ItemMain.mask = GVIF_TEXT;
		ItemMain.row = nRow + 1;
		ItemMain.col = 0;
		ItemMain.strText = str;
		m_pGridCtrl->SetItem(&ItemMain);
	}

	GV_ITEM							Item = { 0, };
	Item.mask = GVIF_TEXT;
	Item.row = nRow + 1;
	Item.col = nCol + 1;
	Item.crBkClr = RGB(255,255,255);
	Item.crFgClr = RGB(0, 0, 0);
	Item.mask |= (GVIF_BKCLR | GVIF_FGCLR);
	Item.strText = szValue;
	m_pGridCtrl->SetItem(&Item);
}

void CView_MMDB_Editor::SetACMdataView(CACMTableInfor*		pTableInfor)
{

	SetGridCtrlCount(pTableInfor->GetRecordSize(), pTableInfor->GetFieldSize(), 1, 1);
	SetGridCtrlTitle(pTableInfor);
	SetGridCtrlData(pTableInfor);

	//m_szLabelValue = szTableName;
	//InvalidateRect(m_LabelTitleRect);
}

LRESULT CView_MMDB_Editor::OnGridCtrlSendMassageData(WPARAM wParam, LPARAM lParam)
{
	if ((UINT)wParam == VIEW_ID_EDITOR_MMDATA)
	{
		tagCtrl_EditValue					tagMSGdata;
		memcpy(&tagMSGdata, (tagCtrl_EditValue*)lParam, sizeof(tagMSGdata));

		if (tagMSGdata.nUpdate == 1)
		{
			if (m_pGridCtrl)
			{
				CString				szValue(m_pGridCtrl->GetItemText(tagMSGdata.nRow, tagMSGdata.nCol));
				TRACE(_T("Edit Chage ( %03d, %03d ) Value = %s -> %s\n"), tagMSGdata.nRow, tagMSGdata.nCol, m_pGridCtrl->GetOldEditValue(), szValue);

				int								nSelectSel(m_ctrCombo.GetCurSel());
				CString							strTableName;
				m_ctrCombo.GetLBText(nSelectSel, strTableName);
				//int								nTableIndex((int)m_1st_InforCombo1.GetItemData(nSelectSel)), 
				int nFieldIndex(-1);

				CACMTableInfor*		pTableInfor = GetTableInfo2Name(strTableName);

				int								i(0), j(0), nIdx_Field(0), nIdx_Field_Ele(0), nColRecount(tagMSGdata.nCol);
				for (i = 0; i < (int)pTableInfor->m_vecField.size(); i++)
				{
					if (pTableInfor->m_vecField[i].nVarID != 1 && pTableInfor->m_vecField[i].nVarCount > 1)
					{
						if (pTableInfor->m_vecField[i].nVarCount >= nColRecount)
						{
							nIdx_Field_Ele = nColRecount;
							++nIdx_Field;
							nFieldIndex = i;
							break;
						}
						else {
							nColRecount -= (pTableInfor->m_vecField[i].nVarCount);
							++nIdx_Field;
						}
					}
					else {
						--nColRecount;
						++nIdx_Field;
					}
					if (nColRecount == 0)
					{
						nFieldIndex = i;
						break;
					}
				}
				if (nIdx_Field > 0 && nSelectSel > -1 && nFieldIndex > -1)
				{
					if (nIdx_Field_Ele > 0)
					{
						//						PUTVALUE_ELEMENT( (wchar_t*)pTableInfor->m_szName.c_str(), (wchar_t*)pTableInfor->m_vecField[ nFieldIndex ].m_szName.c_str(), tagMSGdata.nRow, nIdx_Field_Ele - 1, (double)_wtof( szValue ) );
						PUTVALUE_AT((wchar_t*)pTableInfor->m_szName.GetBuffer() , (wchar_t*)CA2W(pTableInfor->m_vecField[nFieldIndex].szName.GetValue()).m_psz
										, tagMSGdata.nRow, nIdx_Field_Ele - 1, (double)_wtof(szValue));

					}
					else {
						if (pTableInfor->m_vecField[nFieldIndex].nVarID == 1)
						{
							PUTSTRING((wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[nFieldIndex].szName.GetValue()).m_psz
											, tagMSGdata.nRow, (wchar_t*)szValue.GetBuffer());
						}
						else {
							PUTDOUBLE2VALUE((wchar_t*)pTableInfor->m_szName.GetBuffer(), (wchar_t*)CA2W(pTableInfor->m_vecField[nFieldIndex].szName.GetValue()).m_psz
											, tagMSGdata.nRow, (double)_wtof(szValue));
							//							PUTVALUE( (wchar_t*)pTableInfor->m_szName.c_str(), (wchar_t*)pTableInfor->m_vecField[ nFieldIndex ].m_szName.c_str(), tagMSGdata.nRow, (double)_wtof( szValue ) );
						}
					}
					/*if (!m_bIsUpdate)
					{
						m_bIsUpdate = true;
					}*/
				}
			}
		}
	}

	return S_OK;
}