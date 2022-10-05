// MyCtrl.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "MyCtrl.h"


// CMyCtrl

IMPLEMENT_DYNAMIC(CMyCtrl, CWnd)

CMyCtrl::CMyCtrl()
{

}

CMyCtrl::~CMyCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyCtrl, CWnd)
END_MESSAGE_MAP()



// CMyCtrl 메시지 처리기입니다.

BEGIN_MESSAGE_MAP(CMyBrowseEdit, CEdit)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, &CMyBrowseEdit::OnEnKillfocus)
END_MESSAGE_MAP()

void CMyBrowseEdit::OnEnKillfocus()
{
	if(!m_bBrowse)
		GetParent()->SendMessage(WM_LIST2CTRL,GetDlgCtrlID(),VK_RETURN);
}

BOOL CMyBrowseEdit::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN && ( pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN) )	
	{
		GetParent()->SendMessage(WM_LIST2CTRL,GetDlgCtrlID(),pMsg->wParam);
		return TRUE;
	}
	return CEdit::PreTranslateMessage(pMsg);
}
///// 
BEGIN_MESSAGE_MAP(CMyCombo, CComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CMyCombo::OnCbnSelchange)
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, &CMyCombo::OnCbnKillfocus)
END_MESSAGE_MAP()
void CMyCombo::OnCbnKillfocus()
{
	GetParent()->SendMessage(WM_LIST2CTRL,GetDlgCtrlID(),0);
}
void CMyCombo::OnCbnSelchange()
{
	GetParent()->SendMessage(WM_LIST2CTRL,GetDlgCtrlID(),VK_RETURN);
}

BOOL CMyCombo::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) )	
	{
		GetParent()->SendMessage(WM_LIST2CTRL,GetDlgCtrlID(),pMsg->wParam);
		return TRUE;
	}
	return CComboBox::PreTranslateMessage(pMsg);
}
////
CCustomList::CCustomList()
{
	m_pDataArr.RemoveAll();
}
CCustomList::~CCustomList()
{
	for(int i = 0 ; i < m_pDataArr.GetSize(); i++)
		delete m_pDataArr.GetAt(i);
}

BEGIN_MESSAGE_MAP(CCustomList, CMFCListCtrl)
	//{{AFX_MSG_MAP(CCustomList)
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_LIST2CTRL,&CCustomList::OnList2Ctrl)
END_MESSAGE_MAP()

void CCustomList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	LVHITTESTINFO info;
	info.pt = point;

	HitTest(&info);
	SubItemHitTest(&info);
	CListItem* pItem = NULL;
	for(int i = 0 ; i < m_pDataArr.GetSize(); i++)
	{
		pItem =  m_pDataArr.GetAt(i);
		if(pItem->m_nRow != info.iItem || pItem->m_nCol != info.iSubItem)
		{
			pItem = NULL;
			continue;
		}

		break;
	}
	SetFocus();

	if(pItem)
	{

		//// 컨트롤 생성
		CRect r ;
		GetSubItemRect(pItem->m_nRow,pItem->m_nCol,LVIR_LABEL,r);
		CString strTmp = GetItemText(pItem->m_nRow,pItem->m_nCol);
		if(pItem->m_nType == LIST_TYPE_EDIT || pItem->m_nType == LIST_TYPE_BTN)
		{

			m_wndEdit.Create( ES_LEFT | WS_BORDER | WS_CHILD |ES_AUTOHSCROLL |ES_AUTOVSCROLL  ,r,this, 3500,CPoint(pItem->m_nRow,pItem->m_nCol));
			m_wndEdit.SetWindowText(strTmp);
			m_wndEdit.ShowWindow(TRUE); 
			m_wndEdit.SetFocus();
			m_wndEdit.SetSel(0,strTmp.GetLength());
			/*if(pItem->m_nType == LIST_TYPE_BTN)
				m_wndEdit.EnableBrowseButton();
			else
				m_wndEdit.EnableBrowseButton(FALSE);*/
		}
		else if(pItem->m_nType == LIST_TYPE_COMBO)
		{
			r.bottom;
			
			m_wndCombo.Create( CBS_DROPDOWN | WS_BORDER | WS_CHILD ,r,this, 3501,CPoint(pItem->m_nRow,pItem->m_nCol));
			for(int i = 0 ; i < pItem->m_strComboArr.GetSize() ;i++)
			{
				m_wndCombo.AddString(pItem->m_strComboArr.GetAt(i));
			}
			m_wndCombo.SetWindowText(strTmp);
			m_wndCombo.ShowWindow(TRUE); 
			m_wndCombo.ShowDropDown();
			m_wndCombo.SetFocus();
		}
	}
	else
	{
		CMFCListCtrl::OnLButtonDblClk(nFlags,point);
	}
}
void CCustomList::SetItemInfo(int nItem, int nSubItem, int nType, CStringArray *pData)
{
	CListItem* pItem  = new CListItem;
	pItem->m_nType = nType;
	pItem->m_nRow = nItem;
	pItem->m_nCol = nSubItem;
	if(nType == LIST_TYPE_COMBO)
		pItem->m_strComboArr.Copy(*pData);
	else
		pItem->m_strComboArr.RemoveAll();

	m_pDataArr.Add(pItem);
}

LRESULT CCustomList::OnList2Ctrl(WPARAM wp, LPARAM lp)
{
	if(m_wndEdit.GetSafeHwnd())
	{	
		if(wp == m_wndEdit.GetDlgCtrlID())
		{
			CString strTmp;
			if(lp == VK_RETURN)
			{
				m_wndEdit.GetWindowText(strTmp);
				SetItemText(m_wndEdit.m_Pos.x,m_wndEdit.m_Pos.y,strTmp);
			}
			else if(lp == VK_ESCAPE)
			{
			}
			SetSelectionMark(m_wndEdit.m_Pos.x);
			m_wndEdit.DestroyWindow();
		}
	}
	if(m_wndCombo.GetSafeHwnd())
	{
		if(wp == m_wndCombo.GetDlgCtrlID())
		{
			CString strTmp;
			if(lp == VK_RETURN)
			{
				int nPos = m_wndCombo.GetCurSel();
				if(nPos == -1)
					m_wndCombo.GetWindowText(strTmp);
				else
					m_wndCombo.GetLBText(nPos,strTmp);

				if(_wtoi(strTmp) != 0)
				{
					int nEndPos = GetItemCount();
					CString strData[9];
					for(int k = 1 ;k < 9; k++ )
					{
						strData[k] = GetItemText(m_wndCombo.m_Pos.x,k);
					}
					DeleteItem(m_wndCombo.m_Pos.x);
					InsertItem(_wtoi(strTmp)-1,strTmp);
					for(int k = 1 ;k < 9; k++ )
					{
						SetItemText(_wtoi(strTmp)-1,k,strData[k]);
					}
					for(int k = 0 ;k < GetItemCount(); k++ )
					{
						strTmp.Format(_T("%d"),k+1);
						SetItemText(k,0,strTmp);	
					}
				}
			}
			else if(lp == VK_ESCAPE)
			{
			}
			SetSelectionMark(m_wndCombo.m_Pos.x);
			m_wndCombo.DestroyWindow();
		}
	}
	SetFocus();
	return true;
}
