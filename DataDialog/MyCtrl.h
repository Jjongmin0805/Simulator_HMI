#pragma once


// CMyCtrl

class CMyCtrl : public CWnd
{
	DECLARE_DYNAMIC(CMyCtrl)

public:
	CMyCtrl();
	virtual ~CMyCtrl();

protected:
	DECLARE_MESSAGE_MAP()
};


#define  LIST_TYPE_NULL	 0 
#define  LIST_TYPE_EDIT	 1 
#define  LIST_TYPE_COMBO 2 
#define  LIST_TYPE_BTN	 3	  

#define  WM_LIST2CTRL	WM_USER + 1

class CMyBrowseEdit : public CEdit
{
public:
	bool m_bBrowse;
	CPoint m_Pos;
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,CPoint Pos)
	{
		m_Pos = Pos;
		m_bBrowse = false;
		return CEdit::Create(dwStyle,rect,pParentWnd,nID);
	};
	//virtual void OnBrowse()
	//{
	//	//m_bBrowse = true;
	//	//CStringArray TmpArr;
	//	//CSCLDlg Dlg(&TmpArr);
	//	//Dlg.m_nType = TREE_MODE_FULL;
	//	//if(Dlg.DoModal() != IDOK)
	//	//	return;

	//	//CString strValue,strTmp ;
	//	////	GetWindowText(strValue);
	//	//for(int i = 0 ; i < TmpArr.GetSize() ; i++)
	//	//{
	//	//	if(strValue.IsEmpty())
	//	//		strTmp.Format(L"%s",TmpArr.GetAt(i));
	//	//	else 	
	//	//		strTmp.Format(L",%s",TmpArr.GetAt(i));

	//	//	strValue += strTmp;
	//	//}
	//	//SetWindowText(strValue);
	//	//GetParent()->SendMessage(WM_LIST2CTRL,GetDlgCtrlID(),VK_RETURN);
	//	//m_bBrowse = false;
	//}
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnKillfocus();
};

class CMyCombo : public CComboBox
{
public:
	CPoint m_Pos;
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,CPoint Pos)
	{
		m_Pos = Pos;
		return CComboBox::Create(dwStyle,rect,pParentWnd,nID);
	};
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//	DECLARE_MESSAGE_MAP()
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchange();
	afx_msg void OnCbnKillfocus();
};

class CListItem : public CObject
{
public:
	int m_nType;
	int m_nRow;
	int m_nCol;
	CStringArray m_strComboArr;
};
typedef CTypedPtrArray<CObArray,CListItem*> CItemArray;
class AFX_EXT_CLASS CCustomList : public CMFCListCtrl
{
public:
	CCustomList();
	~CCustomList();

	CMyBrowseEdit m_wndEdit;
	CMyCombo	  m_wndCombo;


	CItemArray m_pDataArr;

	void SetItemInfo(int nItem,int nSubItem,int nType,CStringArray* pData);

	virtual void DeleteAllItems()
	{
		for(int i = 0 ; i < m_pDataArr.GetSize(); i++)
			delete m_pDataArr.GetAt(i);
		m_pDataArr.RemoveAll();
		CMFCListCtrl::DeleteAllItems();
	}
	virtual int InsertItem(int nItem, LPCTSTR lpszItem, int nImage = NULL)
	{
		return CMFCListCtrl::InsertItem(nItem, lpszItem, nImage);
	};
protected:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnList2Ctrl(WPARAM wp,LPARAM lp);
	DECLARE_MESSAGE_MAP()

};