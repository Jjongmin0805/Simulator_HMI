
#include "pch.h"
#include "ViewTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
	m_fontNor.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,0,0,0,0,0,_T("맑은 고딕"));
	m_fontBold.CreateFont(19,0,0,0,FW_BOLD,0,0,0,0,0,0,0,0,_T("맑은 고딕"));
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CViewTree::OnNMCustomdraw)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 메시지 처리기

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CViewTree::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCustomDraw = (LPNMCUSTOMDRAW)pNMHDR;
	HTREEITEM hItem = (HTREEITEM)pNMCustomDraw->dwItemSpec;
	*pResult = CDRF_DODEFAULT;
// 	return;
	CDC dc;
	dc.Attach(pNMCustomDraw->hdc);

	CRect rtemp, _rectItem;
	switch(pNMCustomDraw->dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = (CDRF_NOTIFYPOSTPAINT | CDRF_NOTIFYITEMDRAW);
		break;

	case CDDS_ITEMPREPAINT:
		{
			_rectItem = pNMCustomDraw->rc;
			if (_rectItem.IsRectEmpty())
				*pResult = CDRF_DODEFAULT;
			else
				*pResult = CDRF_NOTIFYPOSTPAINT;
		}
		break;

	case CDDS_ITEMPOSTPAINT:
		{
			GetItemRect(hItem,&_rectItem,TRUE);

			// default로 그려주는 item 삭제 & 배경색

			COLORREF crWnd = WND_BG_TREE_COLOR;
			dc.FillSolidRect(&_rectItem, crWnd);
// 			dc.FillSolidRect(&_rectItem, RGB(255,0,0));

			dc.SetBkMode(TRANSPARENT);

			HFONT hOldFont;

			if(pNMCustomDraw->uItemState & (CDIS_FOCUS | CDIS_SELECTED) )
			{
				dc.SetTextColor( TREE_FONT_COLOR_SEL );
				hOldFont = (HFONT)dc.SelectObject(m_fontBold);
			}
			else
			{
				dc.SetTextColor( TREE_FONT_COLOR_NOR );
				hOldFont = (HFONT)dc.SelectObject(m_fontNor);
			}

			CSize szIcon = dc.GetTextExtent(GetItemText(hItem));
			_rectItem.right = _rectItem.left + szIcon.cx;
			_rectItem.bottom = _rectItem.top + szIcon.cy + 2;
			dc.DrawText(GetItemText(hItem), &_rectItem, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

			dc.SelectObject(hOldFont);
			break;
		}
	}

	dc.Detach();
}

BOOL CViewTree::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect( rect, WND_BG_TREE_COLOR );

	return TRUE;
}

