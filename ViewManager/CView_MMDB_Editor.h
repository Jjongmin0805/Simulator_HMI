#pragma once
#include "CView_Base.h"
#include "./Combobox/SkinCombobox.h"
#include "./GRID_Ctrl/GridCtrl.h"


class CACMTableInfor
{
public:
	CACMTableInfor() : m_szName(_T("")), m_nDataSize(0)
	{
		//
	};
	~CACMTableInfor()
	{
		if (m_vecField.size() > 0)
		{
			m_vecField.clear();
		}
	};

	int GetRecordSize()
	{
		return m_nDataSize;
	};
	int GetFieldSize()
	{
		int							i(0), nReSize(0);

		for (i = 0; i < (int)m_vecField.size(); ++i)
		{
			if (m_vecField[i].nVarSize != 1 && m_vecField[i].nVarCount > 1)
			{
				nReSize += (m_vecField[i].nVarCount);
			}
			else {
				++nReSize;
			}
		}

		return nReSize;
	};
	void SetFieldName()
	{
		if (m_szName != _T(""))
		{
					
			theAppDataMng->GetTablePosORFieldVarInfor( 1 , false, CW2A(m_szName).m_psz , m_vecField );
		}
	};

	CString								m_szName;
	int									m_nDataSize;
	VECFIELDVARINFOR					m_vecField;
};


class CView_MMDB_Editor :
	public CView_Base
{
public:
	CView_MMDB_Editor();
	~CView_MMDB_Editor();

	virtual void			SetVIewID() { m_nViewID = VIEW_ID_LOADFLOW_RESULT; };
	virtual	void			InitData();

protected:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMMDB_Editor_Combo_SelectChange();
	afx_msg LRESULT OnGridCtrlSendMassageData(WPARAM wParam, LPARAM lParam);

protected:
	void													Create_Combobox();
	void													Create_ListCtrl();

	void													ListCtrl_MoveSize();
	void													Combobox_MoveSize();

	vector<CACMTableInfor*>									m_vecACMSDB;

	CRect													m_rectCombo;
	CRect													m_rectGrid;
	CRect													m_rectTitle;

	CFont													m_font_Combobox;
	
	CSkinCombobox											m_ctrCombo;
	CGridCtrl*												m_pGridCtrl;

	CACMTableInfor*											GetTableInfo2Name(CString strName);
	void													SetGridCtrlCount(int nRow = 1, int nCol = 1, int nFixRow = 1, int nFixCol = 1);
	void													SetGridCtrlTitle(CACMTableInfor* pTableInfor);
	void													SetGridCtrlData(CACMTableInfor* pTableInfor);

	void													SetGridCtrlItemData(int nRow, int nCol, short nValue);
	void													SetGridCtrlItemData(int nRow, int nCol, int nValue);
	void													SetGridCtrlItemData(int nRow, int nCol, long nValue);
	void													SetGridCtrlItemData(int nRow, int nCol, float fValue);
	void													SetGridCtrlItemData(int nRow, int nCol, double dValue);
	void													SetGridCtrlItemData(int nRow, int nCol, unsigned long long ullValue);
	void													SetGridCtrlItemData(int nRow, int nCol, char* szValue);
	void													SetGridCtrlItemData(int nRow, int nCol, CString szValue);
	void													SetACMdataView(CACMTableInfor*	pTableInfor);

public:

};

