// SortClass.h: interface for the CSortClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SORTCLASS_H__0C463405_0D7F_4E0E_9E0D_B86C244E32F5__INCLUDED_)
#define AFX_SORTCLASS_H__0C463405_0D7F_4E0E_9E0D_B86C244E32F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSortClass  
{
public:
	enum EDataType {dtNULL, dtINT, dtSTRING, dtDATETIME, dtDEC};
	void Sort(bool _bAsc, EDataType _dtype);

	CSortClass(CListCtrl * _pWnd, const int _iCol);
	virtual ~CSortClass();
protected:
	CListCtrl * pWnd;
	static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	//
	struct CSortItem
	{
		CSortItem(const DWORD _dw, const CString &_txt);
		DWORD dw;
		CString txt;
	};
};

#endif // !defined(AFX_SORTCLASS_H__0C463405_0D7F_4E0E_9E0D_B86C244E32F5__INCLUDED_)
