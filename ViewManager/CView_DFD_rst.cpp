#include "pch.h"
#include "CView_DFD_rst.h"
#include "Define_Ctrl.h"
#include "CView_Manager.h"
#include "../DataManager/CDataManager.h"

CView_DFD_rst::CView_DFD_rst()
{
}

CView_DFD_rst::~CView_DFD_rst()
{

}


BEGIN_MESSAGE_MAP(CView_DFD_rst, CView_Base)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_APP_DFD_BTN_1, &CView_DFD_rst::OnControlbutton_run_DFD)
	ON_BN_CLICKED(ID_APP_DFD_BTN_2, &CView_DFD_rst::OnControlbutton_run_DSR)
	ON_BN_CLICKED(ID_APP_DFD_BTN_3, &CView_DFD_rst::OnControlbutton_DFD)
	ON_BN_CLICKED(ID_APP_DFD_BTN_4, &CView_DFD_rst::OnControlbutton_DSR)
	ON_NOTIFY(NM_CLICK, ID_APP_DFD_LIST_7, &CView_DFD_rst::OnListCtrlClick)
END_MESSAGE_MAP()



void CView_DFD_rst::OnInitialUpdate()
{
	CView_Base::OnInitialUpdate();

	CreateListCtrl();
	CreateButtonCtrl();
}

void CView_DFD_rst::InitData()
{

}

void CView_DFD_rst::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);

	OnPrepareDC(&dc);
	Graphics						graphics(dc.GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	CView_Manager* pViewMng = CView_Manager::Instance();

	//////////////////////////////////////////////////////////////////////
	pViewMng->DrawArea_List(&dc, graphics, m_1st_ListCtrlRect1[0]);
	pViewMng->DrawArea_List(&dc, graphics, m_1st_ListCtrlRect1[1]);
	pViewMng->DrawArea_List(&dc, graphics, m_1st_ListCtrlRect2[0]);
	pViewMng->DrawArea_List(&dc, graphics, m_1st_ListCtrlRect2[1]);
	pViewMng->DrawArea_List(&dc, graphics, m_1st_ListCtrlRect2[2]);
	pViewMng->DrawArea_List(&dc, graphics, m_1st_ListCtrlRect3[0]);
	pViewMng->DrawArea_List(&dc, graphics, m_1st_ListCtrlRect3[1]);
	pViewMng->DrawArea_List(&dc, graphics, m_1st_ListCtrlRect3[2]);


	pViewMng->DrawArea_Title(&dc, graphics, m_1st_TitleRect1[0], m_1st_ListCtrlTitle1[0]);
	pViewMng->DrawArea_Title(&dc, graphics, m_1st_TitleRect1[1], m_1st_ListCtrlTitle1[1]);
	pViewMng->DrawArea_Title(&dc, graphics, m_1st_TitleRect2[0], m_1st_ListCtrlTitle2[0]);
	pViewMng->DrawArea_Title(&dc, graphics, m_1st_TitleRect2[1], m_1st_ListCtrlTitle2[1]);
	pViewMng->DrawArea_Title(&dc, graphics, m_1st_TitleRect2[2], m_1st_ListCtrlTitle2[2]);
	pViewMng->DrawArea_Title(&dc, graphics, m_1st_TitleRect3[0], m_1st_ListCtrlTitle3[0]);
	pViewMng->DrawArea_Title(&dc, graphics, m_1st_TitleRect3[1], m_1st_ListCtrlTitle3[1]);
	pViewMng->DrawArea_Title(&dc, graphics, m_1st_TitleRect3[2], m_1st_ListCtrlTitle3[2]);
																
}

BOOL CView_DFD_rst::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CView_Base::OnEraseBkgnd(pDC);
}


void CView_DFD_rst::OnSize(UINT nType, int cx, int cy)
{
	CView_Base::OnSize(nType, cx, cy);

	List_MoveSize();
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void CView_DFD_rst::SetListStyle(CSkinListCtrl& list)
{
	list.ShowWindow(SW_SHOW);
	list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	/*list.m_HeaderCtrl.SetHeight(33);
	list.m_HeaderCtrl.SetFlat();
	list.m_HeaderCtrl.SetFlat();
	list.m_HeaderCtrl.SetTextFont(&m_headerfont);
	list.m_HeaderCtrl.SetBgColor(RGB(191, 191, 191));
	list.m_HeaderCtrl.SetColorHeader(RGB(54, 55, 59));
	list.SetBgColor(RGB(255, 255, 255));
	list.SetUnderLine();
	list.SetColorUnderLine(RGB(215, 214, 214));
	list.SetTextFont(&m_listfont);
	list.SetRowHeight(25);*/

	list.m_HeaderCtrl.SetHeight(27);
	list.m_HeaderCtrl.SetFlat();
	list.m_HeaderCtrl.SetFlat();
	list.m_HeaderCtrl.SetTextFont(&m_headerfont);
	list.m_HeaderCtrl.SetBgColor(RGB(238, 247, 240));
	list.m_HeaderCtrl.SetColorHeader(RGB(0, 0, 0));
	list.SetBgColor(RGB(255, 255, 255));
	list.SetUnderLine();
	list.SetColorUnderLine(RGB(210, 210, 210));
	list.SetTextFont(&m_listfont);
	list.SetRowHeight(25);
	list.m_HeaderCtrl.SetSpacing(0);
	//list.m_HeaderCtrl.m_bdu
}

void CView_DFD_rst::CreateListCtrl()
{
	m_1st_ListCtrlTitle1[0] = _T("���� ����");
	m_1st_ListCtrlTitle1[1] = _T("���� ǥ�ñ�");

	m_1st_ListCtrlTitle2[0] = _T("���� ����");
	m_1st_ListCtrlTitle2[1] = _T("���� ���Ϸ�");
	m_1st_ListCtrlTitle2[2] = _T("����и� ����");

	m_1st_ListCtrlTitle3[0] = _T("���輱��");
	m_1st_ListCtrlTitle3[1] = _T("�������");
	m_1st_ListCtrlTitle3[2] = _T("������ü ����");

	/*vecXmlValue.clear();
	m_1st_ListCtrlRect1[0]					= CRect( 10, 50, 350, 500 );
	m_1st_InforList1[0].Create( m_1st_ListCtrlRect1[0], this, m_1st_ListCtrlTitle1[0], ID_MGAPP_DFD_1_1 );
	const int _1st_colWidthList1_1[]			= {1, 7, 28, 12, 25, 14, 0 };
	vecXmlValue.push_back(_T("hi_fiinfo"));
	vecXmlValue.push_back(_T("ID"));
	vecXmlValue.push_back(_T("�߻��ð�"));
	vecXmlValue.push_back(_T("����"));
	vecXmlValue.push_back(_T("��ȣ���"));
	vecXmlValue.push_back(_T("����"));
	vecXmlValue.push_back(_T("����"));
	m_1st_InforList1[0].AddColumnItemData( vecXmlValue, _1st_colWidthList1_1 );
	m_1st_InforList1[0].Lst_ResizeListColumn();*/
	m_1st_ListCtrlRect1[0] = CRect(10, 50, 350, 500);

	m_1st_InforList1[0].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, m_1st_ListCtrlRect1[0], this, ID_APP_DFD_LIST_1);
	m_1st_InforList1[1].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, m_1st_ListCtrlRect1[0], this, ID_APP_DFD_LIST_2);
	m_1st_InforList2[0].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, m_1st_ListCtrlRect1[0], this, ID_APP_DFD_LIST_3);
	m_1st_InforList2[1].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, m_1st_ListCtrlRect1[0], this, ID_APP_DFD_LIST_4);
	m_1st_InforList2[2].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, m_1st_ListCtrlRect1[0], this, ID_APP_DFD_LIST_5);
	m_1st_InforList3[0].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, m_1st_ListCtrlRect1[0], this, ID_APP_DFD_LIST_6);
	m_1st_InforList3[1].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, m_1st_ListCtrlRect1[0], this, ID_APP_DFD_LIST_7);
	m_1st_InforList3[2].Create(WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER, m_1st_ListCtrlRect1[0], this, ID_APP_DFD_LIST_8);


	m_headerfont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
	m_listfont.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
	//////////////////////////////////////////////////////////////////////////////////////
	m_1st_InforList1[0].InsertColumn(0, _T("hi_fiinfo"), HDF_LEFT, 0);
	m_1st_InforList1[0].InsertColumn(1, _T("ID"), HDF_LEFT, 106);
	m_1st_InforList1[0].InsertColumn(2, _T("�߻��ð�"), HDF_LEFT, 232);
	m_1st_InforList1[0].InsertColumn(3, _T("dl_idx"), HDF_LEFT, 0);
	m_1st_InforList1[0].InsertColumn(4, _T("����"), HDF_LEFT, 116);
	m_1st_InforList1[0].InsertColumn(5, _T("��ȣ���"), HDF_LEFT, 232);
	m_1st_InforList1[0].InsertColumn(6, _T("����"), HDF_LEFT, 116);
	m_1st_InforList1[0].InsertColumn(7, _T("����"), HDF_LEFT, 116);
	SetListStyle(m_1st_InforList1[0]);
	///////////////////////////////////////////////////////////////////////////////////////
	m_1st_InforList1[1].InsertColumn(0, _T("�����"), HDF_LEFT, 112);
	m_1st_InforList1[1].InsertColumn(1, _T("����"), HDF_LEFT, 111);
	m_1st_InforList1[1].InsertColumn(2, _T("���ۼ�"), HDF_LEFT, 111);
	m_1st_InforList1[1].InsertColumn(3, _T("�Ǵ�"), HDF_LEFT, 111);
	m_1st_InforList1[1].InsertColumn(4, _T("idx"), HDF_LEFT, 0);
	SetListStyle(m_1st_InforList1[1]);
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	m_1st_InforList2[0].InsertColumn(0, _T("���������"), HDF_LEFT, 176);
	m_1st_InforList2[0].InsertColumn(1, _T("����"), HDF_LEFT, 135);
	m_1st_InforList2[0].InsertColumn(2, _T("���ܰ��"), HDF_LEFT, 135);
	SetListStyle(m_1st_InforList2[0]);
	///////////////////////////////////////////////////////////////////////////////////////
	m_1st_InforList2[1].InsertColumn(0, _T("idx"), HDF_LEFT, 0);
	m_1st_InforList2[1].InsertColumn(1, _T("��ü"), HDF_LEFT, 112);
	m_1st_InforList2[1].InsertColumn(2, _T("����������"), HDF_LEFT, 111);
	m_1st_InforList2[1].InsertColumn(3, _T("���屸��"), HDF_LEFT, 111);
	m_1st_InforList2[1].InsertColumn(4, _T("����������"), HDF_LEFT, 111);
	SetListStyle(m_1st_InforList2[1]);
	///////////////////////////////////////////////////////////////////////////////////////
	m_1st_InforList2[2].InsertColumn(0, _T("idx"), HDF_LEFT, 0);
	m_1st_InforList2[2].InsertColumn(1, _T("�����"), HDF_LEFT, 281);
	m_1st_InforList2[2].InsertColumn(2, _T("������"), HDF_LEFT, 171);
	m_1st_InforList2[2].InsertColumn(3, _T("������"), HDF_LEFT, 171);
	m_1st_InforList2[2].InsertColumn(4, _T("���"), HDF_LEFT, 171);
	SetListStyle(m_1st_InforList2[2]);
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	m_1st_InforList3[0].InsertColumn(0, _T("���輱��"), HDF_LEFT, 117);
	m_1st_InforList3[0].InsertColumn(1, _T("������"), HDF_LEFT, 224);
	m_1st_InforList3[0].InsertColumn(2, _T("�����뷮"), HDF_LEFT, 105);
	SetListStyle(m_1st_InforList3[0]);
	///////////////////////////////////////////////////////////////////////////////////////const int _1st_colWidthList3_2[]			= { 7, 8,8,13,13,13,13,12,  0 };
	m_1st_InforList3[1].InsertColumn(0, _T("idx"), HDF_LEFT, 0);
	m_1st_InforList3[1].InsertColumn(1, _T("����"), HDF_LEFT, 55);
	m_1st_InforList3[1].InsertColumn(2, _T("����"), HDF_LEFT, 82);
	m_1st_InforList3[1].InsertColumn(3, _T("��Ŵ"), HDF_LEFT, 82);
	m_1st_InforList3[1].InsertColumn(4, _T("L1BF1_idx"), HDF_LEFT, 0);
	m_1st_InforList3[1].InsertColumn(5, _T("L1BF2_idx"), HDF_LEFT, 0);
	m_1st_InforList3[1].InsertColumn(6, _T("L1BF3_idx"), HDF_LEFT, 0);
	m_1st_InforList3[1].InsertColumn(7, _T("L2BF_idx"), HDF_LEFT, 0);
	m_1st_InforList3[1].InsertColumn(8, _T("L1BF1"), HDF_LEFT, 128);
	m_1st_InforList3[1].InsertColumn(9, _T("L1BF2"), HDF_LEFT, 128);
	m_1st_InforList3[1].InsertColumn(10, _T("L1BF3"), HDF_LEFT, 128);
	m_1st_InforList3[1].InsertColumn(11, _T("L2BF"), HDF_LEFT, 128);
	m_1st_InforList3[1].InsertColumn(12, _T("����Ƚ��"), HDF_LEFT, 92);
	m_1st_InforList3[1].InsertColumn(13, _T("�ִ����"), HDF_LEFT, 92);
	SetListStyle(m_1st_InforList3[1]);
	///////////////////////////////////////////////////////////////////////////////////////
	m_1st_InforList3[2].InsertColumn(0, _T("candidate"), HDF_LEFT, 0);
	m_1st_InforList3[2].InsertColumn(1, _T("cbsw_idx"), HDF_LEFT, 0);
	m_1st_InforList3[2].InsertColumn(2, _T("type"), HDF_LEFT, 0);
	m_1st_InforList3[2].InsertColumn(3, _T("�����"), HDF_LEFT, 281);
	m_1st_InforList3[2].InsertColumn(4, _T("������"), HDF_LEFT, 171);
	m_1st_InforList3[2].InsertColumn(5, _T("������"), HDF_LEFT, 171);
	m_1st_InforList3[2].InsertColumn(6, _T("���"), HDF_LEFT, 171);
	SetListStyle(m_1st_InforList3[2]);
	/////////////////////////////////////////////////////////////////////////////


//	_1st_SetListContext( m_1st_InforList1, m_1st_InforList2, m_1st_InforList3 );
}

void CView_DFD_rst::CreateButtonCtrl()
{
	m_btn_control_rect[0] = CRect(10, 20, 90, 250);
	if (!m_btn_control[0].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_control_rect[0], this, ID_APP_DFD_BTN_1))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create DFD Button Fail.\n"));
		return;
	}
	//m_btn_control[0].SetFont( CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) ) );

	m_btn_control[0].SetBitmap(_T("Skin\\View_img\\dfd_btn\\1_button_normal.pnoimg")
		, _T("Skin\\View_img\\dfd_btn\\1_button_click.pnoimg")
		, _T("Skin\\View_img\\dfd_btn\\1_button_over.pnoimg"));


	m_btn_control_rect[1] = CRect(10, 20, 90, 250);
	if (!m_btn_control[1].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_control_rect[1], this, ID_APP_DFD_BTN_2))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create DFD Button Fail.\n"));
		return;
	}

	m_btn_control[1].SetBitmap(_T("Skin\\View_img\\dfd_btn\\2_button_normal.pnoimg")
		, _T("Skin\\View_img\\dfd_btn\\2_button_click.pnoimg")
		, _T("Skin\\View_img\\dfd_btn\\2_button_over.pnoimg"));

	m_btn_control_rect[2] = CRect(10, 20, 90, 250);
	if (!m_btn_control[2].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_control_rect[2], this, ID_APP_DFD_BTN_3))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create DFD Button Fail.\n"));
		return;
	}

	m_btn_control[2].SetBitmap(_T("Skin\\View_img\\dfd_btn\\3_button_normal.pnoimg")
		, _T("Skin\\View_img\\dfd_btn\\3_button_click.pnoimg")
		, _T("Skin\\View_img\\dfd_btn\\3_button_over.pnoimg"));

	m_btn_control_rect[3] = CRect(10, 20, 90, 250);
	if (!m_btn_control[3].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, m_btn_control_rect[3], this, ID_APP_DFD_BTN_4))			// | BS_OWNERDRAW
	{
		AfxMessageBox(_T("Create DFD Button Fail.\n"));
		return;
	}

	m_btn_control[3].SetBitmap(_T("Skin\\View_img\\dfd_btn\\4_button_normal.pnoimg")
		, _T("Skin\\View_img\\dfd_btn\\4_button_click.pnoimg")
		, _T("Skin\\View_img\\dfd_btn\\4_button_over.pnoimg"));
	//	m_btn_control[1].SetFont( CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) ) );

		//	m_change_btn.SetColor( RGB( 255, 255, 255 ), RGB( 0, 0, 0 ) );

	CMFCButton::EnableWindowsTheming(TRUE);
}

void CView_DFD_rst::List_MoveSize()
{
	if (m_1st_InforList1[3].GetSafeHwnd() == NULL || m_btn_control[3].GetSafeHwnd() == NULL  )
		return;

	CRect								_rect(0, 0, 0, 0);
	GetClientRect(&_rect);
	int nGap = 10;

	m_1st_ListCtrlRect1[0].SetRect(_rect.left, _rect.top, _rect.left + 940, _rect.top + 289);

	m_1st_ListCtrlRect1[1].SetRect(m_1st_ListCtrlRect1[0].right + nGap, _rect.top
									,m_1st_ListCtrlRect1[0].right + nGap + 465, _rect.top + 289);
	////////////////////////////////////////////////////////////////////
	m_1st_ListCtrlRect2[0].SetRect(m_1st_ListCtrlRect1[1].right + nGap, _rect.top
									, m_1st_ListCtrlRect1[1].right + nGap + 465, _rect.top + 289);

	m_1st_ListCtrlRect2[1].SetRect(_rect.left, m_1st_ListCtrlRect1[0].bottom + nGap 
									, _rect.left + 465, m_1st_ListCtrlRect1[0].bottom + nGap + 289);

	m_1st_ListCtrlRect2[2].SetRect(_rect.left, m_1st_ListCtrlRect2[1].bottom + nGap
									, _rect.left + 814, _rect.bottom);
	////////////////////////////////////////////////////////////////////
	m_1st_ListCtrlRect3[0].SetRect(m_1st_ListCtrlRect2[1].right + nGap , m_1st_ListCtrlRect1[0].bottom + nGap
									, m_1st_ListCtrlRect2[1].right + nGap + 465, m_1st_ListCtrlRect1[0].bottom + nGap + 289);

	m_1st_ListCtrlRect3[1].SetRect(m_1st_ListCtrlRect3[0].right + nGap, m_1st_ListCtrlRect1[0].bottom + nGap
									, m_1st_ListCtrlRect3[0].right + nGap + 940, m_1st_ListCtrlRect1[0].bottom + nGap + 289);

	m_1st_ListCtrlRect3[2].SetRect(m_1st_ListCtrlRect2[2].right + nGap , m_1st_ListCtrlRect2[1].bottom + nGap
									, m_1st_ListCtrlRect2[2].right + nGap + 814, _rect.bottom);
	////////////////////////////////////////////////////////////////////

	m_1st_TitleRect1[0] = m_1st_ListCtrlRect1[0];
	m_1st_TitleRect1[0].right  = m_1st_TitleRect1[0].left + 93;
	m_1st_TitleRect1[0].bottom = m_1st_TitleRect1[0].top  + 29;

	m_1st_TitleRect1[1] = m_1st_ListCtrlRect1[1];
	m_1st_TitleRect1[1].right = m_1st_TitleRect1[1].left + 105;
	m_1st_TitleRect1[1].bottom = m_1st_TitleRect1[1].top + 29;

	m_1st_TitleRect2[0] = m_1st_ListCtrlRect2[0];
	m_1st_TitleRect2[0].right = m_1st_TitleRect2[0].left + 93;
	m_1st_TitleRect2[0].bottom = m_1st_TitleRect2[0].top + 29;

	m_1st_TitleRect2[1] = m_1st_ListCtrlRect2[1];
	m_1st_TitleRect2[1].right = m_1st_TitleRect2[1].left + 105;
	m_1st_TitleRect2[1].bottom = m_1st_TitleRect2[1].top + 29;

	m_1st_TitleRect2[2] = m_1st_ListCtrlRect2[2];
	m_1st_TitleRect2[2].right = m_1st_TitleRect2[2].left + 119;
	m_1st_TitleRect2[2].bottom = m_1st_TitleRect2[2].top + 29;


	m_1st_TitleRect3[0] = m_1st_ListCtrlRect3[0];
	m_1st_TitleRect3[0].right = m_1st_TitleRect3[0].left + 89;
	m_1st_TitleRect3[0].bottom = m_1st_TitleRect3[0].top + 29;

	m_1st_TitleRect3[1] = m_1st_ListCtrlRect3[1];
	m_1st_TitleRect3[1].right = m_1st_TitleRect3[1].left + 93;
	m_1st_TitleRect3[1].bottom = m_1st_TitleRect3[1].top + 29;
	
	m_1st_TitleRect3[2] = m_1st_ListCtrlRect3[2];
	m_1st_TitleRect3[2].right = m_1st_TitleRect3[2].left + 119;
	m_1st_TitleRect3[2].bottom = m_1st_TitleRect3[2].top + 29;

	CRect _rectlist;

	for (int i = 0; i < 2; i++)
	{
		_rectlist = m_1st_ListCtrlRect1[i];
		_rectlist.InflateRect(1, -1);
		_rectlist.top += 28;

		m_1st_InforList1[i].MoveWindow(_rectlist);
	}
	
	for (int i = 0; i < 3; i++)
	{
		_rectlist = m_1st_ListCtrlRect2[i];
		_rectlist.InflateRect(1, -1);
		_rectlist.top += 28;

		m_1st_InforList2[i].MoveWindow(_rectlist);
	}

	for (int i = 0; i < 3; i++)
	{
		_rectlist = m_1st_ListCtrlRect3[i];
		_rectlist.InflateRect(1, -1);
		_rectlist.top += 28;

		m_1st_InforList3[i].MoveWindow(_rectlist);
	}

	int nBottom = (_rect.bottom - m_1st_ListCtrlRect3[2].top - 33) /4;

	m_btn_control_rect[0].left = m_1st_ListCtrlRect3[2].right + 10;
	m_btn_control_rect[0].top = m_1st_ListCtrlRect3[2].top ;
	m_btn_control_rect[0].right = m_btn_control_rect[0].left + 242;
	m_btn_control_rect[0].bottom = m_btn_control_rect[0].top + nBottom;
	m_btn_control[0].MoveWindow(m_btn_control_rect[0]);


	m_btn_control_rect[1] = m_btn_control_rect[0];
	m_btn_control_rect[1].top = m_btn_control_rect[0].bottom + 11;
	m_btn_control_rect[1].right = m_btn_control_rect[1].left + 242;
	m_btn_control_rect[1].bottom = m_btn_control_rect[1].top + nBottom;
	m_btn_control[1].MoveWindow(m_btn_control_rect[1]);

	m_btn_control_rect[2] = m_btn_control_rect[1];
	m_btn_control_rect[2].top = m_btn_control_rect[1].bottom + 11;
	m_btn_control_rect[2].right = m_btn_control_rect[2].left + 242;
	m_btn_control_rect[2].bottom = m_btn_control_rect[2].top + nBottom;
	m_btn_control[2].MoveWindow(m_btn_control_rect[2]);

	m_btn_control_rect[3] = m_btn_control_rect[2];
	m_btn_control_rect[3].top = m_btn_control_rect[2].bottom + 11;
	m_btn_control_rect[3].right = m_btn_control_rect[3].left + 242;
	m_btn_control_rect[3].bottom = m_btn_control_rect[3].top + nBottom;
	m_btn_control[3].MoveWindow(m_btn_control_rect[3]);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

void CView_DFD_rst::ClearData()
{
	BeginWaitCursor();
	m_1st_InforList1[0].DeleteAllItems();
	m_1st_InforList1[1].DeleteAllItems();
	m_1st_InforList2[0].DeleteAllItems();
	m_1st_InforList2[1].DeleteAllItems();
	m_1st_InforList2[2].DeleteAllItems();
	m_1st_InforList3[0].DeleteAllItems();
	m_1st_InforList3[1].DeleteAllItems();
	m_1st_InforList3[2].DeleteAllItems();

	EndWaitCursor();
}

void CView_DFD_rst::SendWinMsg(int nType, CString strData)
{
	HWND																				pHMIWnd;
	pHMIWnd = ::FindWindow(NULL, _T("App-Simulator SLD"));
	if (!pHMIWnd)																		return;

	char																				szSendMsg[1000] = { 0, };
	sprintf(szSendMsg, ("%s"), CW2A(strData).m_psz);

	COPYDATASTRUCT																		_cds = { 0, };
	_cds.dwData = (ULONG)nType;
	_cds.cbData = (DWORD)sizeof(szSendMsg);
	_cds.lpData = (BYTE *)szSendMsg;
	::SendMessage(pHMIWnd, WM_COPYDATA, (WPARAM)this, (LPARAM)&_cds);

}

void CView_DFD_rst::SetData_Alarm()
{
	ClearData();
	BeginWaitCursor();

	int							i(0), nCount(0);
	int							nSize(0);
	COLORREF					pColor(RGB(54, 55, 59)), pBKColor(RGB(247, 247, 247));
	CString						strID, strTime, strDL, strSW, strPhase, strType, szTemp, strhi, strdlidx;
	int							nID, nDL_idx, nCBSW_idx, nType;
	CTime t = CTime::GetCurrentTime();
	int		nhi_fiinfo, nT;
	DWORD	dw;

	int nCount_table = theAppDataMng->GetTableRealCount(_T("fltinfo_dyn_fio"));
	for (i = 1; i <= (int)nCount_table ; i++)
	{
		if (GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_ii_dl"), i) == 0
			&& GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_ii_cbsw"), i) == 0)
			break;

		//nID =  GETTEXT( _T("fltinfo_dyn_fio"), _T("fltinfo_id"), i );
		strID.Format(_T("%s"), GETSTRING(_T("fltinfo_dyn_fio"), _T("fltinfo_id"), i));

		//	strTime.Format(_T("%s"), GETVALUE( char , _T("fltinfo_dyn_fio"), _T("FLTINFO_TIME"), i ));
		strTime.Format(_T("%s"), t.Format(_T("%Y-%m-%d %H:%M:%S")));

		nDL_idx = GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_ii_dl"), i);
		strDL.Format(_T("%s"), GETSTRING(_T("dl_sta"), _T("dl_nm"), nDL_idx));

		nCBSW_idx = GETVALUE(int, _T("fltinfo_dyn_fio"), _T("FLTINFO_II_CBSW"), i);
		strSW.Format(_T("%s"), GETSTRING(_T("cbsw_sta"), _T("cbsw_nm"), nCBSW_idx));

		szTemp = _T("");
		if (GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_iaopr"), i) == 1) { szTemp = szTemp + _T("A/"); };
		if (GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_ibopr"), i) == 1) { szTemp = szTemp + _T("B/"); };
		if (GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_icopr"), i) == 1) { szTemp = szTemp + _T("C/"); };
		if (GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_inopr"), i) == 1)
		{
			szTemp = szTemp + _T("N/");
			szTemp = szTemp.Left(szTemp.GetLength() - 1);
			strPhase.Format(_T("����(%s)"), szTemp);
		}
		else
		{
			szTemp = szTemp.Left(szTemp.GetLength() - 1);
			strPhase.Format(_T("�ܶ�(%s)"), szTemp);
		}

		nType = GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_type"), i);
		strType.Format(_T("%s"), (nType == 2 ? _T("�Ͻ�") : _T("����")));

		nhi_fiinfo = GETVALUE(int, _T("fltinfo_dyn_fio"), _T("fltinfo_hi_fiinfo"), i);
		strhi.Format(_T("%d"), nhi_fiinfo);

		strdlidx.Format(_T("%d"), nDL_idx);

		m_1st_InforList1[0].InsertItem(nCount, strhi, pColor, pBKColor);
		m_1st_InforList1[0].SetItemText(nCount, 1, strID, pColor, pBKColor);
		m_1st_InforList1[0].SetItemText(nCount, 2, strTime, pColor, pBKColor);
		m_1st_InforList1[0].SetItemText(nCount, 3, strdlidx, pColor, pBKColor);
		m_1st_InforList1[0].SetItemText(nCount, 4, strDL, pColor, pBKColor);
		m_1st_InforList1[0].SetItemText(nCount, 5, strSW, pColor, pBKColor);
		m_1st_InforList1[0].SetItemText(nCount, 6, strPhase, pColor, pBKColor);
		m_1st_InforList1[0].SetItemText(nCount, 7, strType, pColor, pBKColor);

		nCount += 1;
	}

	if (nCount > 0)
	{
		nhi_fiinfo = _wtoi(m_1st_InforList1[0].GetItemText(0, 0));
		if (nhi_fiinfo > 0)
		{
			SetData_Alarm_fiinfo(nhi_fiinfo);
		}
	}


	EndWaitCursor();
}

void CView_DFD_rst::SetData_Alarm_fiinfo(int nfltinfo_hi_fiinfo)
{

	int							i(0), nCount(0);
	int							nSize(0);
	COLORREF					pColor(RGB(54, 55, 59)), pBKColor(RGB(247, 247, 247));
	CString						strSW, strSWType, strPhase, strOper, szTemp, strIndex;
	CString						strDiag[4] = { _T("������"),_T("������"),_T("���ε���"),_T("���ε���") };
	int nType, nDiag;

	nCount = 0;
	int							nNextIdx(nfltinfo_hi_fiinfo), nFiinfoCBSWIdx(0);
	while (nNextIdx > 0)
	{
		nFiinfoCBSWIdx = GETVALUE(int, _T("fiinfo_dyn_fio"), _T("fiinfo_ii_cbsw"), nNextIdx);
		if (nFiinfoCBSWIdx == 0)																break;

		strSW.Format(_T("%s"), GETSTRING(_T("cbsw_sta"), _T("cbsw_nm"), nFiinfoCBSWIdx));

		nType = GETVALUE(int, _T("cbsw_sta"), _T("cbsw_type"), nFiinfoCBSWIdx);
		if (nType == 1) strSWType = _T("CB");
		else if (nType == 2) strSWType = _T("��Ŭ����");
		//else if(nType == 3 ) strSWType = _T("��Ŭ����");
		else if (nType == 4) strSWType = _T("���������");
		else if (nType == 5) strSWType = _T("ǻ��");
		else if (nType == 6) strSWType = _T("��ȸ�ΰ����");
		else if (nType == 7) strSWType = _T("����DG");
		else if (nType == 8) strSWType = _T("���DG�����");
		else  strSWType = _T("�����");

		szTemp = _T("");
		if (GETVALUE(int, _T("fiinfo_dyn_fio"), _T("fiinfo_iaopr"), nNextIdx) == 1) { szTemp = szTemp + _T("A,"); };
		if (GETVALUE(int, _T("fiinfo_dyn_fio"), _T("fiinfo_ibopr"), nNextIdx) == 1) { szTemp = szTemp + _T("B,"); };
		if (GETVALUE(int, _T("fiinfo_dyn_fio"), _T("fiinfo_icopr"), nNextIdx) == 1) { szTemp = szTemp + _T("C,"); };
		if (GETVALUE(int, _T("fiinfo_dyn_fio"), _T("fiinfo_inopr"), nNextIdx) == 1) { szTemp = szTemp + _T("N,"); };
		strPhase.Format(_T("%s"), szTemp.Left(szTemp.GetLength() - 1));


		nDiag = GETVALUE(int, _T("fiinfo_dyn_fio"), _T("fiinfo_fiorer_diag"), nNextIdx);

		strIndex.Format(_T("%d"), nNextIdx);

		m_1st_InforList1[1].InsertItem(nCount, strSW, pColor, pBKColor);
		m_1st_InforList1[1].SetItemText(nCount, 1, strSWType, pColor, pBKColor);
		m_1st_InforList1[1].SetItemText(nCount, 2, strPhase, pColor, pBKColor);
		m_1st_InforList1[1].SetItemText(nCount, 4, strIndex, pColor, pBKColor);

		if (nDiag > 0 && nDiag <= 4)
		{
			m_1st_InforList1[1].SetItemText(nCount, 3, strDiag[nDiag - 1], pColor, pBKColor);
		}

		nCount += 1;

		if (nNextIdx == GETVALUE(int, _T("fiinfo_dyn_fio"), _T("fiinfo_si_fltinfo"), nNextIdx))
		{
			break;
		}
		nNextIdx = GETVALUE(int, _T("fiinfo_dyn_fio"), _T("fiinfo_si_fltinfo"), nNextIdx);
	}
}

void CView_DFD_rst::SetData_DFD()
{
	BeginWaitCursor();
	////	int nSel = m_1st_InforList1[0].LSt; 

	int							i(0), nCount(0);
	int							nSize(0);
	COLORREF					pColor(RGB(54, 55, 59)), pBKColor(RGB(247, 247, 247));
	int						ncbsw_idx, nid, nMax, nState_O, nState_C;
	CString					strIdx, strSW, strResult, strState[2];
	double					dResult, dMax = 0.;

	int nFLT_ID = _wtoi(m_1st_InforList1[0].GetItemText(0, 1));
	

	nMax = -1;
	nCount = 0;
	int nCount_table = (int)theAppDataMng->GetTableRealCount(_T("credibility_dyn_dfdo"));
	for (i = 1; i <= (int)nCount_table ; i++)
	{
		nid = GETVALUE(int, _T("credibility_dyn_dfdo"), _T("credibility_ii_fltinfo"), i);

		if (nid != nFLT_ID)
			continue;

		ncbsw_idx = GETVALUE(int, _T("credibility_dyn_dfdo"), _T("credibility_ii_cbsw"), i);
		strSW.Format(_T("%s"), GETSTRING(_T("cbsw_sta"), _T("cbsw_nm"), ncbsw_idx));

		dResult = GETVALUE(double, _T("credibility_dyn_dfdo"), _T("credibility_secfuzzy"), i);
		strResult.Format(_T("%g"), dResult);

		if (dMax < dResult)
		{
			dMax = dResult;
			nMax = nCount;
		}

		m_1st_InforList2[0].InsertItem(nCount, strSW, pColor, pBKColor);
		m_1st_InforList2[0].SetItemText(nCount, 1, strResult, pColor, pBKColor);

		nCount += 1;
	}

	if (nMax == -1)
		return;

	m_1st_InforList2[0].SetItemText(nMax, 2, _T("���� ����"), pColor, pBKColor);
	/////////////////////////////////////////////////////////////////////////////////////////// ��������

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	nCount = (int)GETCOUNT(_T("isocbsw_dyn_dfdo"));

	nCount = 0;
	nCount_table = (int)theAppDataMng->GetTableRealCount(_T("isocbsw_dyn_dfdo"));
	for (i = 1; i <= (int)nCount_table; i++)
	{
		nid = GETVALUE(int, _T("isocbsw_dyn_dfdo"), _T("isocbsw_ii_fltinfo"), i);

		if (nid != nFLT_ID)
			continue;

		ncbsw_idx = GETVALUE(int, _T("isocbsw_dyn_dfdo"), _T("isocbsw_ii_cbsw"), i);
		strIdx.Format(_T("%d"), ncbsw_idx);
		strSW.Format(_T("%s"), GETSTRING(_T("cbsw_sta"), _T("cbsw_nm"), ncbsw_idx));

		nState_O = GETVALUE(int, _T("isocbsw_dyn_dfdo"), _T("isocbsw_old_state"), i);
		strState[0].Format(_T("%s"), (nState_O == 1 ? _T("����") : _T("����")));

		nState_O = GETVALUE(int, _T("isocbsw_dyn_dfdo"), _T("isocbsw_control_state"), i);
		strState[1].Format(_T("%s"), (nState_O == 1 ? _T("����") : _T("����")));



		m_1st_InforList2[2].InsertItem(nCount, strIdx, pColor, pBKColor);
		m_1st_InforList2[2].SetItemText(nCount, 1, strSW, pColor, pBKColor);
		m_1st_InforList2[2].SetItemText(nCount, 2, strState[0], pColor, pBKColor);
		m_1st_InforList2[2].SetItemText(nCount, 3, strState[1], pColor, pBKColor);

		nCount += 1;
	}



	CString						strDiag[4] = { _T("������"),_T("������"),_T("���ε���"),_T("���ε���") };
	CString strIndex;
	int nDiag;

	for (int i = 0; i < m_1st_InforList1[1].GetItemCount(); i++)
	{
		strIndex = m_1st_InforList1[1].GetItemText(i, 4);
		nDiag = GETVALUE(int, _T("fiinfo_dyn_fio"), _T("fiinfo_fiorer_diag"), _wtoi(strIndex));

		if (nDiag > 0 && nDiag <= 4)
		{
			m_1st_InforList1[1].SetItemText(i, 3, strDiag[nDiag - 1], pColor, pBKColor);
		}
	}


	EndWaitCursor();

	SendWinMsg(2, _T(""));
}

void CView_DFD_rst::SetData_DFD_OA()
{
	int							i(0), nCount(0);
	int							nSize(0);
	COLORREF					pColor(RGB(54, 55, 59)), pBKColor(RGB(247, 247, 247));
	int nid, nState_O;
	int nChk = 0;
	double dValue[3], dResult;
	CString strValue[4], strIdx;
	nCount = 0;
	int nCount_table = theAppDataMng->GetTableRealCount(_T("oa_dyn_dfdo"));
	for (i = 1; i <= (int)nCount_table ; i++)
	{
		nid = GETVALUE(int, _T("oa_dyn_dfdo"), _T("oa_oano"), i);

		if (nid == 0)
			break;

		/*nCount = 0;
		for(int k = 0 ; k < m_1st_InforList2[1].GetItemCount() ;k++ )
		{
			strIdx = m_1st_InforList2[1].GetItemText(k , 0);
			if(_wtoi(strIdx) == nid)
			{
				nCount = k;
				break;
			}
		}*/



		nState_O = GETVALUE(int, _T("oa_dyn_dfdo"), _T("oa_zonetype"), i);
		strIdx.Format(_T("%d"), nid);

		dResult = GETVALUE(double, _T("oa_dyn_dfdo"), _T("oa_ld_3psmw"), i);

		if (nState_O == 2)
		{
			nChk++;
			dValue[0] = dResult;
		}
		else if (nState_O == 1)
		{
			nChk++;
			dValue[1] = dResult;
		}
		else if (nState_O == 3)
		{
			nChk++;
			dValue[2] = dResult;
		}

		if (nChk == 3)
		{
			nChk = 0;
			dResult = dValue[0] + dValue[1] + dValue[2];

			strValue[0].Format(_T("%.1lf"), dResult * 1000);
			strValue[1].Format(_T("%.1lf"), dValue[0] * 1000);
			strValue[2].Format(_T("%.1lf"), dValue[1] * 1000);
			strValue[3].Format(_T("%.1lf"), dValue[2] * 1000);

			m_1st_InforList2[1].InsertItem(nCount, strIdx, pColor, pBKColor);
			m_1st_InforList2[1].SetItemText(nCount, 1, strValue[0], pColor, pBKColor);
			m_1st_InforList2[1].SetItemText(nCount, 2, strValue[1], pColor, pBKColor);
			m_1st_InforList2[1].SetItemText(nCount, 3, strValue[2], pColor, pBKColor);
			m_1st_InforList2[1].SetItemText(nCount, 4, strValue[3], pColor, pBKColor);
			nCount++;
		}
	}
}

void CView_DFD_rst::SetData_DSR()
{
	int							i(0), nCount(0);
	int							nSize(0);
	COLORREF					pColor(RGB(54, 55, 59)), pBKColor(RGB(247, 247, 247));
	int						ncbsw_idx, nRank, nDL_idx[4], nCtrl_cnt, nState_Bf, nState_Af, nType;
	double					dResult, dMax_Load = 0.;
	CString strIdx, strScheme, strDL_idx[4], strDL_name[4], strCount, strResult, strLoad, strSW, strState[2], strCBSWidx, strType, strRank;
	int nFirst_Rank = 0, nFirst_idx = 0;

	nCount = 0;
	int nCount_table = theAppDataMng->GetTableRealCount(_T("candidate_dyn_dsro"));
	for (i = 1; i <= (int)nCount_table; i++)
	{
		nRank = GETVALUE(int, _T("candidate_dyn_dsro"), _T("candidate_rank"), i);
		if (nRank == 0)
			break;

		if (nFirst_idx == 0)
		{
			nFirst_idx = i;
			nFirst_Rank = nRank;
		}
		/*if(nRank == 1)
			continue;*/
		strRank.Format(_T("%d"), nRank);

		dResult = GETVALUE(double, _T("candidate_dyn_dsro"), _T("candidate_total_index"), i);
		strScheme = GETSTRING(_T("candidate_dyn_dsro"), _T("candidate_scheme_nm"), i);
		nDL_idx[0] = GETVALUE_AT(int, _T("candidate_dyn_dsro"), _T("candidatel1bf_ii_dl"), i, 1);
		nDL_idx[1] = GETVALUE_AT(int, _T("candidate_dyn_dsro"), _T("candidatel1bf_ii_dl"), i, 2);
		nDL_idx[2] = GETVALUE_AT(int, _T("candidate_dyn_dsro"), _T("candidatel1bf_ii_dl"), i, 3);
		nDL_idx[3] = GETVALUE(int, _T("candidate_dyn_dsro"), _T("candidatel2bf_ii_dl"), i);
		nCtrl_cnt = GETVALUE(int, _T("candidate_dyn_dsro"), _T("candidate_swnum"), i);
		dMax_Load = GETVALUE(double, _T("candidate_dyn_dsro"), _T("candidate_max_ld"), i);

		strIdx.Format(_T("%d"), i);
		strDL_idx[0].Format(_T("%d"), nDL_idx[0]);
		strDL_idx[1].Format(_T("%d"), nDL_idx[1]);
		strDL_idx[2].Format(_T("%d"), nDL_idx[2]);
		strDL_idx[3].Format(_T("%d"), nDL_idx[3]);
		strCount.Format(_T("%d"), nCtrl_cnt);
		strResult.Format(_T("%.4lf"), dResult);
		strLoad.Format(_T("%.4lf"), dMax_Load);

		strDL_name[0].Format(_T("%s"), GETSTRING(_T("dl_sta"), _T("dl_nm"), nDL_idx[0]));
		strDL_name[1].Empty();
		if (nDL_idx[1] > 0)
		{
			strDL_name[1].Format(_T("%s"), GETSTRING(_T("dl_sta"), _T("dl_nm"), nDL_idx[1]));
		}
		strDL_name[2].Empty();
		if (nDL_idx[2] > 0)
		{
			strDL_name[2].Format(_T("%s"), GETSTRING(_T("dl_sta"), _T("dl_nm"), nDL_idx[2]));
		}
		strDL_name[3].Empty();
		if (nDL_idx[3] > 0)
		{
			strDL_name[3].Format(_T("%s"), GETSTRING(_T("dl_sta"), _T("dl_nm"), nDL_idx[3]));
		}

		m_1st_InforList3[1].InsertItem(nCount, strIdx, pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 1, strRank, pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 2, strResult, pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 3, strScheme, pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 4, strDL_idx[0], pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 5, strDL_idx[1], pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 6, strDL_idx[2], pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 7, strDL_idx[3], pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 8, strDL_name[0], pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 9, strDL_name[1], pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 10, strDL_name[2], pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 11, strDL_name[3], pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 12, strCount, pColor, pBKColor);
		m_1st_InforList3[1].SetItemText(nCount, 13, strLoad, pColor, pBKColor);

		nCount += 1;
	}
	SetData_DFD_OA();
	SetData_DSR_Sub_1(nFirst_idx, nFirst_Rank);
	SetData_DSR_Sub_2(nFirst_idx);
	SendWinMsg(3, _T(""));
}

void CView_DFD_rst::SetData_DSR_Sub_1(int nidx, int nRank_main)
{
	m_1st_InforList3[0].DeleteAllItems();
	m_1st_InforList3[2].DeleteAllItems();

	COLORREF					pColor(RGB(54, 55, 59)), pBKColor(RGB(247, 247, 247));
	int						ncbsw_idx, nRank, nDL_idx[4], nCtrl_cnt, nState_Bf, nState_Af, nType, nCandidate;
	CString strIdx, strCBSWidx, strType, strSW, strState[2];

	BOOL bFind = FALSE;
	int nCount = 0;
	int nCount_table = theAppDataMng->GetTableRealCount(_T("dsrseq_dyn_dsro"));
	for (int i = 1; i <= (int)nCount_table ; i++)
	{
		nCandidate = GETVALUE(int, _T("dsrseq_dyn_dsro"), _T("dsrseq_ii_candidate"), i);

		//nRank = GETVALUE( int, _T("dsrseq_dyn_dsro"), _T("dsrseq_ii_candidate"), i );

		if (nidx != nCandidate)
			continue;

		/*bFind = FALSE;
		for(int k = 0 ; k < m_1st_InforList3[1].GetItemCount() ;k++ )
		{
			strIdx = m_1st_InforList3[1].GetItemText(k , 0);
			if(_wtoi(strIdx) == nRank)
			{
				bFind = TRUE;
				break;
			}
		}

		if(!bFind )
			continue;*/

		ncbsw_idx = GETVALUE(int, _T("dsrseq_dyn_dsro"), _T("dsrseq_ii_cbsw"), i);
		nState_Bf = GETVALUE(int, _T("dsrseq_dyn_dsro"), _T("dsrseq_before_state"), i);
		nState_Af = GETVALUE(int, _T("dsrseq_dyn_dsro"), _T("dsrseq_after_state"), i);
		nType = GETVALUE(int, _T("dsrseq_dyn_dsro"), _T("dsrseq_after_state_result"), i);

		strIdx.Format(_T("%d"), nCandidate);
		strCBSWidx.Format(_T("%d"), ncbsw_idx);
		strType.Format(_T("%d"), nType);
		if (nType == 2)
			strSW.Format(_T("%s"), GETSTRING(_T("tisw_sta"), _T("tisw_nm"), ncbsw_idx));
		else
			strSW.Format(_T("%s"), GETSTRING(_T("cbsw_sta"), _T("cbsw_nm"), ncbsw_idx));

		strState[0].Format(_T("%s"), (nState_Bf == 1 ? _T("����") : _T("����")));
		strState[1].Format(_T("%s"), (nState_Af == 1 ? _T("����") : _T("����")));

		m_1st_InforList3[2].InsertItem(nCount, strIdx, pColor, pBKColor);
		m_1st_InforList3[2].SetItemText(nCount, 1, strCBSWidx, pColor, pBKColor);
		m_1st_InforList3[2].SetItemText(nCount, 2, strType, pColor, pBKColor);
		m_1st_InforList3[2].SetItemText(nCount, 3, strSW, pColor, pBKColor);
		m_1st_InforList3[2].SetItemText(nCount, 4, strState[0], pColor, pBKColor);
		m_1st_InforList3[2].SetItemText(nCount, 5, strState[1], pColor, pBKColor);
		nCount++;
	}

	/*nType = 1;
	for(int i = 0 ;i < m_1st_InforList3[2].GetItemCount() ; i++)
	{
		strCBSWidx = m_1st_InforList3[2].GetItemText(i , 1 );

		bFind = FALSE;
		for( int k = 1 ; k <= (int)GETCOUNT( _T("l1bf_dyn_dsro") ) ; k++ )
		{
			ncbsw_idx	= GETVALUE( int, _T("l1bf_dyn_dsro") , _T("l1bf_ii_cbsw"), k );
			if(ncbsw_idx == 0)
				break;

			if(ncbsw_idx == _wtoi(strCBSWidx))
			{
				bFind = TRUE;
				break;
			}
		}

		if(bFind)
		{
			strSW.Format(_T("%s"), GETTEXT( _T("tisw_sta"), _T("tisw_nm"), _wtoi(strCBSWidx) ) );
			m_1st_InforList3[2].SetItemText( i, 3	, strSW			,	pColor, pBKColor );
			m_1st_InforList3[2].SetItemText( i, 2	, _T("2")		,	pColor, pBKColor );
		}
		else
		{
			strSW.Format(_T("%s"), GETTEXT( _T("cbsw_sta"), _T("cbsw_nm"), _wtoi(strCBSWidx) ) );
			m_1st_InforList3[2].SetItemText( i, 3	, strSW			,	pColor, pBKColor );
			m_1st_InforList3[2].SetItemText( i, 2	, _T("1")		,	pColor, pBKColor );
		}

	}*/
}

void CView_DFD_rst::SetData_DSR_Sub_2(int nIdx)
{
	m_1st_InforList3[0].DeleteAllItems();

	COLORREF					pColor(RGB(54, 55, 59)), pBKColor(RGB(247, 247, 247));
	int						ncbsw_idx, nCandidate, nDL_idx, nType;
	double					dResult;
	CString  strDL_name, strResult, strSW;
	int nCount = 0;
	int nCount_table = theAppDataMng->GetTableRealCount(_T("l1bf_dyn_dsro"));
	for (int k = 1; k <= (int)nCount_table; k++)
	{
		nDL_idx = GETVALUE(int, _T("l1bf_dyn_dsro"), _T("l1bf_ii_dl"), k);

		if (nDL_idx == 0)
			break;

		nCandidate = GETVALUE(int, _T("l1bf_dyn_dsro"), _T("l1bf_ii_candidate"), k);
		if (nIdx != nCandidate)
			continue;

		ncbsw_idx = GETVALUE(int, _T("l1bf_dyn_dsro"), _T("l1bf_ii_cbsw"), k);

		strDL_name = GETSTRING(_T("dl_sta"), _T("dl_nm"), nDL_idx);
		dResult = GETVALUE(double, _T("l1bf_dyn_dsro"), _T("l1bf_margin_3psmw"), k);
		strResult.Format(_T("%.2lf"), dResult);

		nType = GETVALUE(int, _T("l1bf_dyn_dsro"), _T("l1bf_si_candidate"), k);
		if (nType == 2)
			strSW.Format(_T("%s"), GETSTRING(_T("tisw_sta"), _T("tisw_nm"), ncbsw_idx));
		else
			strSW.Format(_T("%s"), GETSTRING(_T("cbsw_sta"), _T("cbsw_nm"), ncbsw_idx));

		m_1st_InforList3[0].InsertItem(nCount, strDL_name, pColor, pBKColor);
		m_1st_InforList3[0].SetItemText(nCount, 1, strSW, pColor, pBKColor);
		m_1st_InforList3[0].SetItemText(nCount, 2, strResult, pColor, pBKColor);
		nCount++;
	}
}


void CView_DFD_rst::OnControlbutton_run_DFD()
{
//	AfxGetApp()->GetMainWnd()->SendMessage(DFD_GUIDE_OK, (WPARAM)1L, (LPARAM)0L);
}

void CView_DFD_rst::OnControlbutton_run_DSR()
{
//	AfxGetApp()->GetMainWnd()->SendMessage(DFD_GUIDE_OK, (WPARAM)2L, (LPARAM)0L);
}

void CView_DFD_rst::OnControlbutton_DFD()
{
	/*SetData_Alarm();
	SetData_DFD();*/

	CString strSend, strCBSWidx, strDL, strState;
	strDL = m_1st_InforList1[0].GetItemText(0, 3);
	strSend.Format(_T("%d,"), m_1st_InforList2[2].GetItemCount());

	for (int i = 0; i < m_1st_InforList2[2].GetItemCount(); i++)
	{
		strCBSWidx = m_1st_InforList2[2].GetItemText(i, 0);
		strState = m_1st_InforList2[2].GetItemText(i, 3);

		strSend.Format(_T("%s,%s,1,%d,"), strDL, strCBSWidx, (strState == _T("����") ? 0 : 1));
		SendWinMsg(99, strSend);
		Sleep(2000);
	}

	//SendWinMsg(99 , strSend);
}

void CView_DFD_rst::OnControlbutton_DSR()
{
	//SetData_Alarm();
	//SetData_DSR();
	CString strSend, strCBSWidx, strType, strDL, strState;
	strDL = m_1st_InforList1[0].GetItemText(0, 3);
	strSend.Format(_T("%d,"), m_1st_InforList3[2].GetItemCount());

	for (int i = 0; i < m_1st_InforList3[2].GetItemCount(); i++)
	{
		strCBSWidx = m_1st_InforList3[2].GetItemText(i, 1);
		strType = m_1st_InforList3[2].GetItemText(i, 2);
		strState = m_1st_InforList3[2].GetItemText(i, 5);

		strSend.Format(_T("%s,%s,%d,%d,"), strDL, strCBSWidx, _wtoi(strType), (strState == _T("����") ? 0 : 1));
		SendWinMsg(99, strSend);
		Sleep(2000);
	}

}

void CView_DFD_rst::OnListCtrlClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	//TRACE( _T("CSDMS_Appl_NCP_Wnd::OnListCtrlDBClick - Move SLD and DAS GIS.(%d, %d)\n"), (int)wParam, (int)lParam );

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;

	CString strIdx, strRank;

	if (nRow > -1)
	{
		strIdx = m_1st_InforList3[1].GetItemText(nRow, 0);
		strRank = m_1st_InforList3[1].GetItemText(nRow, 1);

		SetData_DSR_Sub_1(_wtoi(strIdx), _wtoi(strRank));
		SetData_DSR_Sub_2(_wtoi(strIdx));
	}




}
