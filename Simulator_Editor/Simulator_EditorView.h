
// Simulator_EditorView.h: CSimulator_EditorView 클래스의 인터페이스
//

#pragma once

#include "../DND_Manager/CDND_Object.h"
#include "../DND_Manager/CKASIM_ND.h"
#include "CDNDObj_DlgBar.h"

#include "CFindObjDlg.h"
#include "MyToolTipCtrl.h"

#include "CDNDObj_KASIM_CONSUMER_TAP.h"

#define    MOUSE_MODE_NORMAL	 0
#define    MOUSE_MODE_SELECT	 1
#define    MOUSE_MODE_SCREEN	 2
#define    MOUSE_MODE_OBJ_MOVE	 3
#define    MOUSE_MODE_OBJ_CANCEL 4

class CSimulator_EditorView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CSimulator_EditorView() noexcept;
	DECLARE_DYNCREATE(CSimulator_EditorView)

// 특성입니다.
public:
//	CSimulatorEditorDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CSimulator_EditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnEditmenuMove();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditmenuDel();
	afx_msg void OnConnectmenuSplitMove();
	afx_msg void OnConnectmenuSplitDel();
	afx_msg void OnConnectmenuDel();
	afx_msg void OnConnectmenuSplitInsert();
	afx_msg void OnEdit_Add_Symbol(UINT id);
	afx_msg void OnEdit_Add_Connect();
	afx_msg void OnEdit_Add_Text();

	afx_msg void Editor_View_Expansion(); //확대
	afx_msg void Editor_View_Reduce();

	afx_msg void MsgEnter();
	afx_msg void MsgEsc();
	//이미지출력
	CString																			MyPath();
	void																			PrintImage();
	BOOL																			Makepng(CString szFileNm);
	//설비찾기
	CMyToolTipCtrl																	m_ToolTip;
	CFindObjDlg*																	m_pFindDlg;

	CDNDObj_KASIM_CONSUMER_TAP*														m_pConsumer_Tap;
	void																			FindObject();

	
	afx_msg LRESULT																	OnFindObjPosition(WPARAM wparam, LPARAM lparam);
	void																			InitTooltip();
	void																			SetToolTip(CString szMessage);
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	afx_msg void OnEditmenuDel_KASIM(CDND_Object* m_pSelect_DNDObj);
	afx_msg void OnConnectmenuDel_KASIM(CDND_Object* m_pSelect_DNDObj);
	afx_msg void OnConnectmenuCancel();
	afx_msg void OnConnectmenuCancel_KASIM(CDND_Connect* pConnect , int nSelectND);
	afx_msg void OnConnectmenuCancel_KASI_ND(int nNDID, int nDataID, int nINDEX);

	//KASIM 파일 삭제 하는 부분
	void Del_KASIM_LNSEC(int nID);
	void Del_KASIM_BR(int nID);
	void Del_KASIM_GBR(int nID);
	void Del_KASIM_DL(int nID);
	void Del_KASIM_CBSW(int nID);
	void Del_KASIM_ND(int nFID, int nTID, int nType, int nCSV_ID);
	void Del_KASIM_GEN(int nID);
	void Del_KASIM_ESS(int nID);
	void Del_KASIM_HVCUS(int nID);
	void Del_KASIM_PRDE(int nID);
	void Del_KASIM_IJ(int nID);
	void Del_KASIM_LD(int nID);
	void Del_KASIM_ND_2(int nID);
	void Del_KASIM_SVR(int nID);
	void Del_KASIM_SUBS(int nSSID);
	void Del_KASIM_MTR(int nMTRID);

	double		m_dZoomValue;
	int			m_nMouseMode;

	CPoint			m_pt_Select;
	CPoint			m_pt_Move;
	
	CDND_Object*	m_pSelect_DNDObj;
	CDND_Object*	m_pSelect_DNDObj_Move;
	CDND_Object*	m_pSelect_DNDObj_Cancle;
	CDND_Object*	m_pSelect_DNDObj_Cancle_From;
	CDND_Object*	m_pSelect_DNDObj_Cancle_TO;
	CDND_Object*	m_pSelect_DNDObj_Cancle_LNSEC;

	int				m_nCheck_Gen_upload;

	int				m_nMTRDELETE_NO;

	//CString m_szGen_Name_ADD[100]; //남궁원차장이 요청 했던 부부 ㄴ20220107 -- 중복 ?된이름 찾기!?

	//CKASIM_ND_Array m_Array_KASIM_ND;

	CPoint										GetScreenPoint(CPoint pt);
	CPoint										GetScreenPoint_Real(CPoint pt);
	CPoint										GetCurrentPoint(CPoint ptReal, CDND_Connect* pConnect);
	

	CDND_Object*								Get_DND_Object2Pt(CPoint pt,BOOL bConnect = TRUE);
	CDND_Object*								Get_DND_Object2Pt_Cancel(CPoint pt, BOOL bConnect = TRUE);
	CDND_Object*								Get_DND_ObjectToINDEX(CString stNDIndex);
	void										SetLink_Connect(CPoint pt);
	void										SetLink_Connect_Inset_ND(CDND_Switch *pSwitch, CDND_Connect *pConnect, int nNdINDEX, int nMultSW);
	void										STA_Inset(CDND_Connect *pConnect, CDND_Switch *pSwitch);
	void										SetLink_Connect_Object(CPoint pt); //선택된 설비에 

	void										Reset();
	afx_msg void OnEditmenuCancel();
};

