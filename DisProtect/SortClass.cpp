// SortClass.cpp: implementation of the CSortClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SortClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#pragma warning( disable : 4482 )
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSortClass::CSortClass(CListCtrl * _pWnd, const int _iCol)
{
	pWnd = _pWnd;

	ASSERT(pWnd);
	int max = pWnd->GetItemCount();
	DWORD dw;
	CString txt;

	// replace Item data with pointer to CSortItem structure
	for (int t = 0; t < max; t++)
	{
		dw = pWnd->GetItemData(t); // save current data to restore it later
		txt = pWnd->GetItemText(t, _iCol);
		pWnd->SetItemData(t, (DWORD) new CSortItem(dw, txt));
	}
}

CSortClass::~CSortClass()
{
	ASSERT(pWnd);
	int max = pWnd->GetItemCount();
	CSortItem * pItem;
	for (int t = 0; t < max; t++)
	{
		pItem = (CSortItem *) pWnd->GetItemData(t);
		ASSERT(pItem);
		pWnd->SetItemData(t, pItem->dw);
		delete pItem;
	}
}

void CSortClass::Sort(bool _bAsc, EDataType _dtype)
{
	long lParamSort = _dtype;

	// if lParamSort positive - ascending sort order, negative - descending
	if (!_bAsc)
		lParamSort *= -1;

	pWnd->SortItems(Compare, lParamSort);
}

int CALLBACK CSortClass::Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CSortItem * item1 = (CSortItem *) lParam1;
	CSortItem * item2 = (CSortItem *) lParam2;
	ASSERT(item1 && item2);

	// restore data type and sort order from lParamSort
	// if lParamSort positive - ascending sort order, negative - descending
	short   sOrder = lParamSort < 0 ? -1 : 1;
	EDataType dType  = (EDataType) (lParamSort * sOrder); // get rid of sign

	// declare typed buffers
	COleDateTime t1, t2;

	switch (dType)
	{
	case  EDataType::dtINT:
		return (_wtol(item1->txt) - _wtol(item2->txt))*sOrder;
	case  EDataType::dtDEC:
		return (_wtof(item1->txt) < _wtof(item2->txt) ? -1 : 1)*sOrder;
	case  EDataType::dtDATETIME:
		if (t1.ParseDateTime(item1->txt) && t2.ParseDateTime(item2->txt))
			return (t1 < t2 ? -1 : 1 )*sOrder;
		else
			return 0;
	case  EDataType::dtSTRING:
		return item1->txt.CompareNoCase(item2->txt)*sOrder;

	default:
		ASSERT(L"Error: attempt to sort a column without type.");
		return 0;
	}
}

CSortClass::CSortItem::CSortItem(const DWORD _dw, const CString & _txt)
{
	dw  = _dw;
	txt = _txt;
}
