// SkinListCtrl.h  Version 1.3
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// This software is released into the public domain.
// You are free to use it in any way you like.
//
// This software is provided "as is" with no expressed
// or implied warranty.  I accept no liability for any
// damage or loss of business that this software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SKINLISTCTRL_H
#define _SKINLISTCTRL_H

#include "SkinHeaderCtrl.h"
#include "./Checkbox/SkinCheckbox.h"

///////////////////////////////////////////////////////////////////////////////
// Style bits for use with SetExtendedStyleX()

// none defined yet

///////////////////////////////////////////////////////////////////////////////
// CSkinListCtrl data

class CCheckData
{
public:
	 CCheckData()
	 {
		 m_pCheckbox = NULL;
		 m_nItem     = -1;
		 m_nSubItem  = -1;
	 };
	
	~CCheckData() {};

	CSkinCheckbox *m_pCheckbox;
	int m_nItem;
	int m_nSubItem;
};

class CSortData
{
public:
    CSortData(CString str, DWORD dw) 
	{
		m_strText = str;
		m_dw = dw;
	};
    ~CSortData(){};

    CString m_strText;
    DWORD m_dw;
};

//
typedef struct tagNMITEM
{
	HWND hwndFrom;
	int	iItem;
	int	iSubItem;
	CString sText;
} NMITEM;
// JCW_+ 2008.04.12 END

// JCW_U 2008.04.12 START
struct SkinListCtrlDATA
{
	// ctor
	SkinListCtrlDATA()
	{
		bEnabled             = TRUE;
		crText               = ::GetSysColor(COLOR_WINDOWTEXT);
		crBackground         = RGB( 240, 240, 240 ); //IDX_RGB_FONT_LITE_GRAY9 );
		bBold                = FALSE;
		nImage               = -1;
		bImageCenter		 = FALSE;
		crBar				 = RGB( 0, 200, 0 );		
		nCheckedState		 = -1;	
		nTextLeftmode		 = HDF_CENTER;

#ifndef NO_SKINLISTCTRL_TOOL_TIPS
		strToolTip           = _T("");
#endif		
		dwItemData           = NULL;
	}

	BOOL			bEnabled;				// TRUE = enabled, FALSE = disabled (gray text)
	BOOL			bBold;					// TRUE = display bold text
	int				nImage;					// index in image list, else -1
	BOOL			bImageCenter;

#ifndef NO_SKINLISTCTRL_TOOL_TIPS
	CString			strToolTip;				// tool tip text for cell
#endif	

	// for color
	COLORREF		crText;
	COLORREF		crBackground;	
	COLORREF		crBar;	
	
	int			    nCheckedState;
	int				nTextLeftmode;
	DWORD			dwItemData;				// pointer to app's data
};

///////////////////////////////////////////////////////////////////////////////
// CSkinListCtrl class

class CSkinListCtrl : public CListCtrl
{
// Construction
public:
	CSkinListCtrl();
	virtual ~CSkinListCtrl();

// Attributes
public:

// Operations
public:	
	void	EnableFocusRect(BOOL bFocusRect=TRUE){m_bFocusRect=bFocusRect;}
	void	EnableResize(BOOL bResize=TRUE){m_bResize=bResize;}

	void	SetNoItemMsg(CString strNoItemMsg)		{	m_strNoItemMsg = strNoItemMsg;	}
	void	SetStatusColumn(int nSubItem)			{	m_nStatusColumn = nSubItem;		}
	void	SetBgColor(COLORREF crBg)				{	m_crWindow = crBg;				}

	void	SetUnderLine(BOOL bUnderLine=TRUE)		{	m_bUnderLine = bUnderLine;		}
	void	SetColorUnderLine(COLORREF crUnderLine) {	m_crUnderLine = crUnderLine;	}	
	void	GetDrawColors( int nItem, int nSubItem, COLORREF& colorText, COLORREF& colorBkgnd );
	void    DeleteAllColumns();
	void	DeleteCheckbox  ();
	void	HideCheckbox    ();
	
	BOOL	DeleteAllItems();
	BOOL	DeleteItem(int nItem);
	BOOL	GetBold(int nItem, int nSubItem);
	int		GetColumns();	
	int		GetCurSel();
	BOOL	GetEnabled(int nItem);
	DWORD	GetExtendedStyleX() { return m_dwExtendedStyleX; }
	int		GetHeaderCheckedState(int nSubItem);
	DWORD	GetItemData(int nItem);
	BOOL	GetSubItemRect(int iItem, int iSubItem, int nArea, CRect& rect);

	int		InsertItem(int nItem, LPCTSTR lpszItem, int nFmt = HDF_CENTER);
	int		InsertItem(int nItem,
					   LPCTSTR lpszItem,
					   COLORREF crText,
					   COLORREF crBackground,
					   int nFmt = HDF_CENTER);
	int		InsertItem(const LVITEM* pItem);
	BOOL	SetBold(int nItem, int nSubItem, BOOL bBold);	
	void	UpdateDate(int nItem, int nSubItem, CTime time, COLORREF crText, COLORREF crBackground);
	
	BOOL	SetCurSel(int nItem);
	BOOL	SetEnabled(int nItem, BOOL bEnable);
	DWORD	SetExtendedStyleX(DWORD dwNewStyle) 
	{
		DWORD dwOldStyle = m_dwExtendedStyleX;
		m_dwExtendedStyleX = dwNewStyle;
		return dwOldStyle;
	}

	BOOL	SetHeaderCheckedState(int nSubItem, int nCheckedState);
	int		SetItem(const LVITEM* pItem);
	BOOL	SetItemData(int nItem, DWORD dwData);
	
	BOOL	SetItemImage(int nItem, int nSubItem, int nImage, BOOL bImageCenter=FALSE);
	int		GetItemImage(int nItem, int nSubItem);

	BOOL	SetItemText(int nItem, int nSubItem, LPCTSTR lpszText, int nFmt = HDF_CENTER); 
	BOOL	SetItemText(int nItem, 
						int nSubItem, 
						LPCTSTR lpszText,
						COLORREF crText, 
						COLORREF crBackground,
						int nFmt = HDF_CENTER);
	BOOL	SetItemTextColor(int nItem, 
							 int nSubItem, 
							 COLORREF crText, 
							 COLORREF crBackground);	
	void	UpdateSubItem(int nItem, int nSubItem);
	
	virtual void Sort(int nSubItem, BOOL bSort); // bSort = TRUE:내림차순, FALSE:오름차순

	void	SetRowHeight(int nRowHeight);
	void	SetTextFont (CFont *pTextFont) { m_pTextFont = pTextFont; RedrawWindow(); }
	void	SetHeaderColumn( const TCHAR **pszTitle );
	void	SetColumnSize  ( const int *arrWidth, BOOL bAutoSize = TRUE );
	void    SetCheckBox    ( int nItem, int nSubItem, int nCheckedState );
	void	Refresh		   ();
	int     GetCheckBox    ( int nItem, int nSubItem );
	BOOL	CheckSortData  ( int nSubItem );	
	void    SetParentHwd   ( HWND hwdParent )	{ m_hwdParent   = hwdParent;  }
	void	SetRowsHeight  ( int nRowHeight )	{ m_nRowHeight  = nRowHeight; }
	 		
#ifndef NO_SKINLISTCTRL_TOOL_TIPS
	void DeleteAllToolTips();
	BOOL SetItemToolTipText(int nItem, int nSubItem, LPCTSTR lpszToolTipText);
	CString GetItemToolTipText(int nItem, int nSubItem);
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinListCtrl)
	public:
	virtual void PreSubclassWindow();
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	CSkinHeaderCtrl	m_HeaderCtrl;

	BOOL			m_bSort_X; //////// 강제로 막는다

protected:
	CImageList		m_cImageList;		// Image list for the header control	
	BOOL			m_bUnderLine;		// 언더라인 그리기의 유무 설정
	BOOL			m_bVerLine;			// 컬럼라인 그리기의 유무 설정	
	BOOL			m_bResize;			// 마우스 드래그로 헤더 컬럼의 리사이즈 유무 설정
	BOOL			m_bFocusRect;		// Focus Rect 표시 유무
	CString			m_strNoItemMsg;		// 아이템이 없을때 표시 할 텍스트 설정
	int				m_nStatusColumn;	// 상태 컬럼의 Rect(백그라운드 컬러영역)을 재설정할 컬럼 설정	
	COLORREF		m_crUnderLine;		// 언더라인의 색
	BOOL			m_bHeaderTracking;	// 현재 헤더가 트래킹중인지 판단하는 플래그
	BOOL			m_bHeaderDraging;	// 현재 헤더가 드래깅중인지 판단하는 플래그
	BOOL			m_bTracking;
	BOOL			m_bSort;			// HEADER 컬럼정렬 플래그	
	CFont		   *m_pTextFont;
	HWND		    m_hwdParent;		// 부모핸들
	int				m_nRowHeight;		// 리스트컨트롤 높이
	CArray <CCheckData *, CCheckData *>	m_carrCheckData;

protected:
	void DrawCheckbox(int nItem, 
					  int nSubItem, 
					  CDC *pDC, 
					  COLORREF crText,
					  COLORREF crBkgnd,
					  CRect& rect, 
					  SkinListCtrlDATA *pCLD);
	int DrawImage(int nItem, 
				  int nSubItem, 
				  CDC* pDC, 
				  COLORREF crText,
				  COLORREF crBkgnd,
				  CRect rect,
				  SkinListCtrlDATA *pXLCD);	
	void DrawText(int nItem, 
				  int nSubItem, 
				  CDC *pDC, 
				  COLORREF crText,
				  COLORREF crBkgnd,
				  CRect& rect, 
				  SkinListCtrlDATA *pCLD);
	void SubclassHeaderControl();

	BOOL			m_bHeaderIsSubclassed;
	DWORD			m_dwExtendedStyleX;

	COLORREF		m_cr3DFace;
	COLORREF		m_cr3DHighLight;
	COLORREF		m_cr3DShadow;
	COLORREF		m_crBtnFace;
	COLORREF		m_crBtnShadow;
	COLORREF		m_crBtnText;
	COLORREF		m_crGrayText;
	COLORREF		m_crHighLight;
	COLORREF		m_crHighLightText;
	COLORREF		m_crWindow;
	COLORREF		m_crWindowText;

	COLORREF		m_crTracking;		
	int				m_nTrackingItem;	

	int				m_nRes_CheckBox_Nor;
	int				m_nRes_CheckBox_Chk;
	int				m_nRes_CheckBox_Dis;

	CSize			GetCheckBoxSize();

public:
	void			SetHighLightColor(COLORREF clr){m_crHighLight = clr ; }; 
	void			SetTrackingColor(COLORREF clr){m_crTracking = clr ; }; 

	void			SetCheckBox_Bitmap(int nRes_Nor, int nRes_Chk, int nRes_Dis);

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinListCtrl)
	afx_msg BOOL OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);	
	afx_msg void OnDestroy();
	afx_msg void OnSysColorChange();
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	
	afx_msg void OnPaint();	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNcPaint();
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	//}}AFX_MSG
	
	void	SetLButtonDown ( int nStartItem, int nStartSubItem );
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);	

#ifndef NO_SKINLISTCTRL_TOOL_TIPS
	virtual afx_msg BOOL OnToolTipText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
#endif
	DECLARE_MESSAGE_MAP()	
public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);

	afx_msg LRESULT OnCheckbox2Ctrl(WPARAM wp, LPARAM lp);
	void	HideCheckbox2Select(int nRow,int nCol);
	void	ShowCheckbox2Select(int nRow, int nCol);
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#define  LIST_TYPE_NULL	 0 
#define  LIST_TYPE_EDIT	 1 
#define  LIST_TYPE_COMBO 2 
#define  LIST_TYPE_BTN	 3	  

#define  WM_LIST2CTRL	WM_USER + 1

#define				WM_MSG_CTRL_EVENT	WM_USER + 2

class CMyBrowseEdit : public CEdit
{
public:
	bool m_bBrowse;
	CPoint m_Pos;
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CPoint Pos)
	{
		m_Pos = Pos;
		m_bBrowse = false;
		return CEdit::Create(dwStyle, rect, pParentWnd, nID);
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
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CPoint Pos)
	{
		m_Pos = Pos;
		return CComboBox::Create(dwStyle, rect, pParentWnd, nID);
	};
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//	DECLARE_MESSAGE_MAP()
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchange();
	afx_msg void OnCbnKillfocus();
	afx_msg void OnCbnSelCancel();
};

class CListItem : public CObject
{
public:
	int m_nType;
	int m_nRow;
	int m_nCol;
	CStringArray m_strComboArr;
};
typedef CTypedPtrArray<CObArray, CListItem*> CItemArray;

class  CSkinCustomList : public CSkinListCtrl
{
public:
	CSkinCustomList();
	~CSkinCustomList();

	CMyBrowseEdit m_wndEdit;
	CMyCombo	  m_wndCombo;


	CItemArray m_pDataArr;

	void SetItemInfo(int nItem, int nSubItem, int nType, CStringArray* pData);

	virtual void DeleteAllItems()
	{
		for (int i = 0; i < m_pDataArr.GetSize(); i++)
			delete m_pDataArr.GetAt(i);
		m_pDataArr.RemoveAll();
		CSkinListCtrl::DeleteAllItems();
	}
	virtual int InsertItem(int nItem,
		LPCTSTR lpszItem,
		COLORREF crText,
		COLORREF crBackground,
		int nFmt = HDF_CENTER)
	{
		return CSkinListCtrl::InsertItem(nItem, lpszItem, crText, crBackground, nFmt);
	};
protected:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnList2Ctrl(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

};

#endif // _SKINLISTCTRL_H