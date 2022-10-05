
// Simulator_SLDView.h: CSimulatorSLDView 클래스의 인터페이스
//

#pragma once
#include "MyToolTipCtrl.h"
#include "NaviDlg.h"
#include "FindObjDlg.h"
#include "NodeView.h"
#include "BranchView.h"
#include "SetDFDDlg.h"
#include "FindObjDlg.h"

#include "GisObj.h"
#include "GisSec.h"

#define SLDVIEW_BACKGROUND_COLOR													RGB( 0, 0, 0 )
#define SLDVIEW_WIDTH_MARGIN														200
#define SLDVIEW_HEIGHT_MARGIN														200

#define CONNECTTYPE_CONTINUE														1
#define CONNECTTYPE_DEAD															2
#define CONNECTTYPE_BACKUP															3

#define SLDVIEW_ZOOM_MAX															1.5
#define SLDVIEW_ZOOM_MIN															0.5
#define SLDVIEW_ZOOM_DEFAULT														1

#define SHOW_SLDMODE_ALL															0
#define SHOW_SLDMODE_AUTO															1
#define SHOW_SLDMODE_PROTECT														2

#define PROGRAM_GISHMI																1
#define PROGRAM_SIMUL_SERVER														2
#define PROGRAM_SIMUL_HMI															3

#define SHOW_VIEWMODE_SINGLE														0
#define SHOW_VIEWMODE_GIS															1

#define SHOW_GISMODE_SINGLE															0
#define SHOW_GISMODE_ALL															1

#define GISVIEW_BACKGROUND_COLOR													RGB( 120, 120, 120 )
#define GIS_IMAGE_CNT_X																9
#define GIS_IMAGE_CNT_Y																5
#define TILEMAP_SIZE																256

#define ZOOM_IN																		1
#define ZOOM_OUT																	-1
#define ZOOM_DEFAULT																0

#define BASE_ZOOMLEVEL																7
#define ZERO_POS_Y																	117	//7레벨의 117 이미지가 Y축 시작점(0)임

#define SIMULATION_SLD_STEP															20.
#define SIMULATION_GIS_STEP															11.

#define TM_BASE_ZOOM																0.03275

#define GIS_MIN_ZOOMLEVEL															12
#define GIS_MAX_ZOOMLEVEL															19

#define ANIMATION_SPEED																50

typedef CArray<int, int&> CIntArray;

class CSimulatorSLDView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSimulatorSLDView() noexcept;
	DECLARE_DYNCREATE(CSimulatorSLDView)

// 특성입니다.
public:
	CSimulatorSLDDoc* GetDocument() const;

// 작업입니다.
public:
	CString																			GetModulePath();

	void																			ClearBoundaryCheck(BOOL bAreaMode);
	void																			SetBoundaryArea(BOOL bAreaMode);
	void																			SetBoundaryAreaRcv(CNodeView* pNodeView, BOOL bArea, BOOL bAreaMode);
	//내비관련////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CNaviDlg*																		m_pNaviDlg;
	void																			SetNaviPosition();
	void																			ShowNavi(BOOL bShow);
	int																				IsShowNavi();
	void																			UpdateNavigator();				//내비게이션 업데이트

	//툴팁관련////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMyToolTipCtrl																	m_ToolTip;
	void																			InitTooltip();
	void																			SetToolTip(CString szMessage);
	CString																			GetTooltipMsg(CNodeView* pNodeView);
	CString																			GetTooltipMsg(CBranchView* pBranchView);

	//단선도관련////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int																				m_nNodeID;						//단선도기준 설비ID;
// 	int																				m_nBranchID;					//단선도기준 구간ID;
	CNodeView*																		m_pNodeView;					//단선도 설비
	CBranchView*																	m_pBranchView;					//단선도 구간
	BYTE*																			m_pBRTrace;						//BR탐색 (중복)체크용 메모리
	BYTE*																			m_pBRTrace2;					//BR탐색 (중복) 2차탐색(BF)체크용 메모리
	BYTE*																			m_pNDTrace;						//ND탐색 (중복)체크용 메모리
	int																				m_nSLDMode;						//0:일반, 1:자동화, 2:보호기기

	int																				m_nDeadLineDepthSet;			//사선구간 보이기 DEPTH설정

	void																			MakeSLD(int nDLIdx);			//단선도 생성
	void																			CheckBranchView(CBranchView* pTargetBranch, CNodeView* pNodeView, CBranchView* pBranchView);//단선도  겹침회피 보정

	int																				SetSLDMode(int nMode);
	//단선도 일반모드(&자동화축약)
	void																			MakeAllSLDRcv(int nBRIdx, int nFNDIdx, CNodeView* pnodeview, CBranchView* pbranchview, int nDeadLineDepth);//일반모드 계통탐색.
	int																				SetNodeInfo(int nNDIdx, CNodeView* pNewNodeView);//설비정보설정
	void																			SetMultiCircuitInfo(int nNDIdx, int nCbswidx, int nMultiType, CNodeView* pSubNodeView);//다회로 단자정보 설정(cbsw)
	int																				GetNextNDIdxRcv(int nTargetNDIdx, double& dLen, double& dLoad, double& dRp, double& dR0, double& dXp, double& dX0, CIntArray& nLnSecArr);//다음 대상노드 찾기
	int																				GetNextNDIdx(int nNDIdx, double& dLen, double& dLoad, double& dRp, double& dR0, double& dXp, double& dX0, CIntArray& nLnSecArr);//다음 대상노드 진행
	BOOL																			CheckAutoNode(int nTargetNDIdx);//대상(자동화)노드인지를 체크
	int																				GetCheckNDIdx(int nTargetNDIdx);//다분기인지 확인(다분기라면 수동이어도 확인해야하니까)
	int																				CheckConnectSw(int nNDIdx);//다회로개폐기인지 체크(연결스위치가 2개이상이면 다회로)
	int																				GetToNDIdx(int nNDIdx);//설비기준 전원측노드 -> 부하측노드를 가져온다.
	BOOL																			IsTargetObj(int nNDIdx);//대상(자동화)인지 확인.
	BOOL																			FindNextAutoRcv(int nNDIdx, int nPreBRIdx);//자동화설비를 찾아서 모험을 떠난다~
	BOOL																			FindNextAuto(int nNDIdx, int nPreBRIdx);//다음 대상노드 진행
	int																				GetNDStatus(int nNDIdx);//NODE_ID를 가지고 상태값을 확인한다(개폐기가 아니라면 그냥 CLOSE로 함)
	int																				GetSwStatus(int nCbswIdx);//cbsw_sta_id를 가지고 개폐기 상태값을 확인
	int																				SearchDL(int nNDIdx, int nNoSsarchIdx);
	int																				FindCB(int nPreBRIdx, int nNDIdx);
	int																				FindCBRcv(int nBRIdx, int nFNDIdx);
	int																				GetCbswToNode(int nNDIdx);

	int																				FindBF(int nPreBRIdx, int nNDIdx);
	int																				FindBFRcv(int nBRIdx, int nFNDIdx);

	BOOL																			IsPCA(int nCBSWIdx);//해당스위치가 PCA단자인지를 확인
	BOOL																			IsMultiSw(int nNDIdx);
	//화면관련////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int																				m_nShowOption;

	double																			m_dZoomScale;					//화면 줌인/줌아웃 스케일(0.5~2, 기본값 1)
	CPoint																			m_ptStart;						//화면 드래그시 좌표계산용
	BOOL																			m_bLButtonDown;
	CPoint																			m_ptPosition;					//단선도 기준점에서 이동한 화면의 위치정보
	CSize																			m_sizeMaxSLD;					//단선도 최대배율버퍼 사이즈
	CSize																			m_sizeCurSLD;					//단선도 현재배율버퍼 사이즈
	CDC*																			m_pSLDBuffer;					//실제 단선도를 담고 있을 메모리DC -> 단선도를 선택했을때 처음 한번만 그린다.
	CBitmap*																		m_pSLDBitmap;					//단선도 메모리DC 복귀용
	int																				m_nDLIdx;						//현재 보고있는 단선도 DL;
	CNodeView*																		m_pTooltipNodeView;				//Tooltip표시 설비
	CBranchView*																	m_pTooltipBranchView;			//Tooltip표시 구간
	CNodeView*																		m_pSelectNodeView;				//선택된 설비
	CBranchView*																	m_pSelectBranchView;			//선택된 구간

	CNodeView*																		m_pFaultPosNodeView;			//고장점지정 설비

	int																				GetDLIdx() { return m_nDLIdx; };
	void																			MakeSLDBuffer(BOOL bInit);		//단선도 메모리에 그리기(TRUE: CB를 화면 중앙으로 이동, FALSE는 현재화면 좌표유지->화대축소시 사용)
	void																			DeleteSLDBuffer();				//단선도 메모리 삭제
	void																			SetSDLScale(double dRatio) { m_dZoomScale = dRatio; };
	double																			GetSDLScale() { return m_dZoomScale; };
	int																				GetMaxSizeX(BOOL bDefaultSize);	//단선도 좌표 최대 X축 사이즈 가져오기(bDefaultSize: TRUE=원본배율, FALSE=화면스케일적용)
	int																				GetMaxSizeY(BOOL bDefaultSize);	//단선도 좌표 최대 Y축 사이즈 가져오기(bDefaultSize: TRUE=원본배율, FALSE=화면스케일적용)
	CPoint																			DrawSLD(CDC* BufferDC, BOOL bShow);		//단선도 그리기
	void																			SetShiftPosition(CPoint ptShift);//화면이동시 이동좌표 설정
	void																			SetCenterPosition(CPoint ptCenter);//해당좌표를 화면에 중앙에 배치
	BOOL																			Zoom(int nMode);				//화면 줌 설정 ( -1: 줌아웃, 0: 기본배율, 1: 줌인)
	void																			SetZoomMenuStatus();
	void																			SetSelectDraw(CNodeView* pSelectNodeView);


	int																				m_nViewMode;
	void																			ShowSLDView(int nMode);
	void																			DefaultBaseMap();

	void																			MakeGISBuffer(BOOL bInit);		
	void																			DeleteGISBuffer();				
	void																			ShiftMap(void);
	CDC*																			m_pGISBuffer;					//실제 GIS단선도를 담고 있을 메모리DC
	CBitmap*																		m_pGISBitmap;					//GIS단선도 메모리DC 복귀용
	CImage																			m_pBgImage[GIS_IMAGE_CNT_X][GIS_IMAGE_CNT_Y];
	CString																			m_szImgPath;
	CDPoint																			m_ptOfficeCenter;//
	int																				m_nZoomLevel;
	CDPoint																			m_dpOfficeCenter_utm;//화면중앙의 UTM좌표(내비게이션용)
	double																			m_dZoom;
	CPoint																			m_ptGisPosition;

	//설비찾기
	CFindObjDlg*																	m_pFindDlg;
	void																			FindObject();
	afx_msg LRESULT																	OnFindObjPosition(WPARAM wparam, LPARAM lparam);
	BOOL																			FindNodePosition(int nNDIdx, BOOL bShow);
	void																			MoveFocusNodeView(int nTargetIdx);

	//설비정보확인
	void																			GetBRIdx(CNodeView* pNodeView, int& nCompIdx, int& nType);
	void																			GetComponentType(int nNDIdx, int& nCompIdx, int& nType);

	BOOL																			ModifySLD(int nReDraw);

	//고장처리(DFD)관련
	CBranchView*																	m_pContextBranch;
	CBranchView*																	m_pFaultBranch;
	BOOL																			GetDirectPathRcv(CNodeView* pNodeView, int nTargetID, CNodeViewArray& pPathNodeView);
	BOOL																			FindLoadSideRcv(CNodeView* pNodeView, CNodeViewArray& pLoadSideNodeView);
	int																				GetTargetSwToGNode(int nGNDIdx, int& nType);
	CSetDFDDlg*																		m_pSetDfdDlg;
	afx_msg LRESULT																	OnDfdGeneratorFunc(WPARAM wParam, LPARAM lParam);

	BOOL																			IsFaultDL(int nDLIdx);
	int																				IsFaultOperSw(int nNDIdx);
	int																				IsDSROperSw(int nNDIdx);
	int																				GetCbswIdx(int nNDIdx);

	//시나리오
	void																			Fault_Scenario();
	void																			ReadFLTInfoData(CString szPath);
	void																			ReadFIInfoData(CString szPath);
	void																			ResetFault();

	void																			TransferMessage(int nProgramIdx, int nMessageType, CString szMessage);


	int																				GetBrType(int nBrIdx);



	void																			SetSLDDPoint(CPoint ptShift);
	void																			SetSLDDPointRcv(CNodeView* pNodeView, CPoint ptShift, CRect rect);

	void																			CalculationScale();
	double																			m_dl;
	double																			m_dt;
	double																			m_dr;
	double																			m_db;

	double																			m_dMinZoomScale;//단선도가 한화면에 들어오기위한 배율
	double																			m_dStZoomScale;//현재 단선도배율
	int																				m_nBaseZoomlevel;//GIS 단선도가 한화면에 들어오기위한 배율
	CDPoint																			m_ptBaseCenterPos;//GIS 단선도의 중심좌표.


	int																				m_nSLDStep;
	int																				m_nGISStep;
	void																			DrawGIS(CDC* BufferDC);
	void																			DrawSimulStep1();
	void																			SetGISScale();

	void																			SetBranchPolePos(CBranchView* pBranch, CNodeView* pFNodeView, CNodeView* pTNodeView);

	BOOL																			m_bAction;



	CGisObjArray																	m_pGisObjArr;
	CGisSecArray																	m_pGisSecArr;


	int																				m_nGisMode;//0:단선도, 1:계통도
	void																			ToggleGisMode();
	void																			LoadGis();
	void																			LoadGisObj();
	void																			LoadGisSec();
	void																			DrawGISAll(CDC* BufferDC);

	//이미지출력
	void																			PrintImage();
	BOOL																			Makepng(CString szFileNm, int nRatioOpt, int nFontRate);

	BOOL																			m_bReverseColor;

	BOOL																			SetMenuEnabledCheck(CNodeView* pSelNodeView);

	//루프선로 처리용
	CIntArray																		m_nLoofCBIdArr;
	CStringArray																	m_szLoofCBNmArr;
	int																				GetSelectLoofCB(CPoint point);

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CSimulatorSLDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMovePosition(WPARAM wp, LPARAM lp);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSetFault();
	afx_msg void OnUpdateSetFault(CCmdUI *pCmdUI);
	afx_msg void OnResetFault();
	afx_msg void OnUpdateResetFault(CCmdUI *pCmdUI);

	DECLARE_MESSAGE_MAP()

	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMenuFaultpos();
	afx_msg void OnMenuHide();
	afx_msg void OnMenuPrintImp();
	afx_msg void OnMenuPrdeSet();
	afx_msg void OnUpdateMenuPrdeSet(CCmdUI *pCmdUI);
	afx_msg void OnVvmSet();
};

#ifndef _DEBUG  // Simulator_SLDView.cpp의 디버그 버전
inline CSimulatorSLDDoc* CSimulatorSLDView::GetDocument() const
   { return reinterpret_cast<CSimulatorSLDDoc*>(m_pDocument); }
#endif

