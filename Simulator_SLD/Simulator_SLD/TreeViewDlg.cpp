// TreeViewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Simulator_SLD.h"
#include "TreeViewDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CTreeViewDlg 대화 상자

IMPLEMENT_DYNAMIC(CTreeViewDlg, CDialog)

CTreeViewDlg::CTreeViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TREEVIEW_DLG, pParent)
{
	m_nTreeViewMode = -1;
}

CTreeViewDlg::~CTreeViewDlg()
{
}

void CTreeViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTreeViewDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CTreeViewDlg 메시지 처리기
CString CTreeViewDlg::GetModulePath()
{
	CString sPath;
	GetModuleFileName(AfxGetApp()->m_hInstance, sPath.GetBuffer(MAX_PATH), MAX_PATH);
	sPath.ReleaseBuffer();

	int nPos = sPath.ReverseFind(_T('\\'));
	if (nPos != -1)
		sPath = sPath.Left(nPos);

	return sPath;
}

BOOL CTreeViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateTreeView();
	ShowTree(GROUP_OPTION_MODE1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CTreeViewDlg::CreateTreeView()
{
	CString																			sModulePath = GetModulePath() + _T("\\Skin\\SLD\\SideCtrl\\Tree\\TreeImage.pnoimg");
	if (_waccess(sModulePath, 06) == -1)
	{
		AfxMessageBox(_T("트리 이미지를 불러올수 없습니다.\n"));
		return FALSE;
	}

	HBITMAP																			m_treeImage;
	m_treeImage = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), (LPCTSTR)sModulePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	BITMAP																			m_treeImageInfor;
	::GetObject(m_treeImage, sizeof(BITMAP), &m_treeImageInfor);

	CBitmap*																		bitmapimage;
	bitmapimage = CBitmap::FromHandle(m_treeImage);
	m_TreeImgList.Create(17, 21, ILC_COLOR24, 14, 14);
	m_TreeImgList.Add(bitmapimage, RGB(255, 0, 255));

	const DWORD																		dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS | TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_FULLROWSELECT | TVS_INFOTIP;
	CRect																			rect;

	for (int i = 0; i < 2; i++)
	{
		if (!m_wndViewTree[i].Create(dwViewStyle, CRect(0, 0, 100, 100), this, 0x10000 + i))
		{
			AfxMessageBox(_T("트리뷰을 만들지 못했습니다.\n"));
			return FALSE;      // 만들지 못했습니다.
		}

		m_wndViewTree[i].SetImageList(&m_TreeImgList, LVSIL_NORMAL);
	}

	return TRUE;
}

void CTreeViewDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (m_nTreeViewMode < 0)														return;

	CRect																			_rect;
	GetClientRect(&_rect);

	for (int i = 0; i < 2; i++)
		m_wndViewTree[i].SetWindowPos(NULL, _rect.left, _rect.top, _rect.Width(), _rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}

void CTreeViewDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	GetClientRect(&rc);
	dc.FillSolidRect(rc, WND_BG_GROUP_COLOR);
}

HTREEITEM CTreeViewDlg::InsertTreeItem(int nIdx, CString szName, int nImage, int nSelImage, HTREEITEM hParent, int nMode, int nData/*=-1*/)
{
	HTREEITEM hItem;

	TV_INSERTSTRUCT tvs;
	ZeroMemory(&tvs, sizeof(TV_INSERTSTRUCT));

	tvs.hParent = hParent;

	if (nMode == TREE_ITEM_INSERT_FIRST)											tvs.hInsertAfter = TVI_FIRST;
	else if (nMode == TREE_ITEM_INSERT_ROOT)										tvs.hInsertAfter = TVI_ROOT;
	else if (nMode == TREE_ITEM_INSERT_SORT)										tvs.hInsertAfter = TVI_SORT;
	else																			tvs.hInsertAfter = TVI_LAST;

	tvs.item.pszText = (LPTSTR)(LPCTSTR)szName;
	tvs.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvs.item.iImage = nImage;
	tvs.item.iSelectedImage = nSelImage;
	hItem = m_wndViewTree[nIdx].InsertItem(&tvs);

	m_wndViewTree[nIdx].SetItemData(hItem, nData);

	return hItem;
}

void CTreeViewDlg::RemoveTreeItem()
{
	for (int i = 0; i < 2; i++)
		m_wndViewTree[i].DeleteAllItems();
}

void CTreeViewDlg::ShowTree(int nMode)
{
	m_nTreeViewMode = nMode;
	if (nMode == GROUP_OPTION_MODE1)
	{
		m_wndViewTree[GROUP_OPTION_MODE1].ShowWindow(TRUE);
		m_wndViewTree[GROUP_OPTION_MODE2].ShowWindow(FALSE);
	}
	else
	{
		m_wndViewTree[GROUP_OPTION_MODE1].ShowWindow(FALSE);
		m_wndViewTree[GROUP_OPTION_MODE2].ShowWindow(TRUE);
	}
}

BOOL CTreeViewDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR			hdr;
	LPNMTREEVIEW	ntv;
	HTREEITEM		hItem;
	int				nDLIdx;

	hdr = (LPNMHDR)lParam;
	ntv = (LPNMTREEVIEW)lParam;

	if (hdr->hwndFrom == m_wndViewTree[m_nTreeViewMode].m_hWnd)
	{
		if (m_wndViewTree[m_nTreeViewMode].GetCount() == 0)
			return CDialog::OnNotify(wParam, lParam, pResult);

		TV_HITTESTINFO hit_info;
		GetCursorPos(&hit_info.pt);
		::ScreenToClient(m_wndViewTree[m_nTreeViewMode].m_hWnd, &hit_info.pt);
		hItem = m_wndViewTree[m_nTreeViewMode].HitTest(&hit_info);

		if (hItem == NULL)
			return CDialog::OnNotify(wParam, lParam, pResult);

		nDLIdx = m_wndViewTree[m_nTreeViewMode].GetItemData(hItem);

		if (hdr->code == NM_CLICK)
			TreeClickEvent(nDLIdx);
		else if (hdr->code == NM_DBLCLK)
			TreeDBClickEvent(nDLIdx);
		else if (hdr->code == NM_RCLICK)
			TreeRBClickEvent(nDLIdx);
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CTreeViewDlg::TreeClickEvent(int nDLIdx)
{
	// 	if( nDLIdx <= 0 )	return;
	// 	((CMainFrame *)AfxGetMainWnd())->TreeClickEvent( nDLIdx );
}

void CTreeViewDlg::TreeDBClickEvent(int nDLIdx)
{
	if (nDLIdx <= 0)	return;
	((CMainFrame *)AfxGetMainWnd())->TreeDBClickEvent(nDLIdx);
}

void CTreeViewDlg::TreeRBClickEvent(int nDLIdx)
{
	// 	if( nDLIdx <= 0 )	return;
	// 	((CMainFrame *)AfxGetMainWnd())->TreeRBClickEvent( nDLIdx );
}

BOOL CTreeViewDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			HTREEITEM hItem = m_wndViewTree[m_nTreeViewMode].GetSelectedItem();
			if (hItem != NULL)
			{
				int				nDLIdx;
				nDLIdx = m_wndViewTree[m_nTreeViewMode].GetItemData(hItem);
				TreeDBClickEvent(nDLIdx);
			}
			return TRUE;
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CTreeViewDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialog::OnEraseBkgnd(pDC);
}
