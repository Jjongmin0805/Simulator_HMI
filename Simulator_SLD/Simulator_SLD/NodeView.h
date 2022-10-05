#pragma once
#include "BranchView.h"

#define GRID_GAP																	150//기본그리드 1칸의 너비

#define SELECT_DRAW_COLOR															RGB( 200, 200, 200 )
#define	DEFALUT_TEXT_COLOR															RGB( 255, 255, 255 )
#define	DEFALUT_PRINT_COLOR															RGB( 0, 0, 0 )

// CNodeView 명령 대상입니다.

class CNodeView : public CObject
{
public:
	CNodeView();
	virtual ~CNodeView();

	void							DBSave( int nOffice, CString sztime, CString szSubstID, int nCBID, int nSLDMode );

	void							RemoveData();
	void							Draw(CDC* BufferDC, double dScale, int nShowOption, BOOL bPrint, int nFontRate = 100);
	void							DrawNavi(CDC* BufferDC, double dRatioX, double dRatioY);
	void							Serialize(CArchive& ar, double dVersion);

	void							DrawCB( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawDG( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawAutoSw( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawManualSw( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawSVR( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawOH( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawCOS( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawEFI( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawDummy( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawBF( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawCustomer( CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawALTS(CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);
	void							DrawTRCase(CDC* BufferDC, double dScale, BOOL bPrint, int nFontRate);

	void							DrawFIFlag( CDC* BufferDC, double dScale );
	int								GetFaultType( int nCbswIdx );

	int								GetCbswIdx();

	CString							GetSimbolText();
	CRect							GetSimbolRect(double dScale = 1.0);

	void							SetSelectDraw( CDC* BufferDC );

	BOOL							IsAuto();
	
	void							SetCeqID( CString szData )							{m_szCEQID = szData;};
	CString							GetCeqID()											{return m_szCEQID;};

	double							GetDerGenMw(int nCbswIdx);
	double							GetDerRaMw(int nCbswIdx);

	int								m_nDbID;		//노드ID
	int								m_nSwKindID;	//설비타입
	int								m_nKCIMType;	//KCIM설비타입
	int								m_nCeqType;		//CEQ타입
	CString							m_szLoc;		//전주번호(명칭)
	BOOL							m_bStatus;		//상태
	CString							m_szLocNo;		//전산화번호(사용안함) -> 연계점타입(내부, 외부)으로 사용. 단, CB일때는 변전소명으로.
	int								m_nNDID[2];		//일반모드일때는 NodeIdx(from-to), 그룹모드일때는 GNodeIdx(from-to);
													//백업객체일때는 [1]의 값여부로 내부연계/외부연계 구분가능
                                                    //외부DL시 0: 백업선로 dlIdx,	1: 없음
													//내부DL시 0: 연계점ND(GND)Idx,	1: 이전노드설비 m_nDbID -> 내부연계면 단선도에 2개의 설비가 존재하니까, 다른쪽으로 가기 위해 [1]이 필요함.

	int								m_nALTSCBSW;	//ALTS시에만 사용 -> 반대쪽 단자(CBSW)를 가지고 있자.

	int								m_nTongID;		//다회로일때 TongID
	int								m_nCaption;		//다회로일때 단자번호

	int								m_nPosX;		//개체 X좌표
	int								m_nPosY;		//개체 Y좌표
	
	CRect							m_rectObj;		//단선도상에서의 설비의 영역

	int								m_nFromND;		//(멀티)가상더미일때 단선도상의 전원측 ND정보(다회로 전원측 개폐기를 찾기위함)

	CNodeView*						m_pLeft;
	CNodeView*						m_pCenter;
	CNodeView*						m_pRight;
	CNodeView*						m_pLeftTop;
	CNodeView*						m_pRightBottom;

	int								m_nCrossCnt;
	int								m_nReviseLevel;
	int								m_nDirection;
	int								m_nDirection2;//5회로이상 대각선분기확인용.

	BOOL							m_bBoundarySelect;//다구간 영역설정
	void							ClearBoundaryCheck();

	CString							m_szCEQID;		//설비의 CEQID

	//고장관련 정보
	BOOL							IsProtOperSw( int nCbswIdx );
	int								GetFiInfoIdx( int nCbswIdx );

	CNodeView*						FindUnsetNode(int reviselevel);
	int								SetLongestPathToCenter(double maxlength, double currentlength, CBranchView* pbranchview);
	void							SetShortestPathDiagonal(CBranchView* pranchview);
	void							SetLongestPathToRightTop(int direction, CBranchView* pranchview);//긴분기를 오른쪽/위쪽으로 배치함(간선기준 상단)
	void							SetLongestPathToRightBottom(int direction, CBranchView* pranchview);//긴분기를 오른쪽/아래쪽으로 배치함(간선기준 하단)
	double							GetLongestPathLength(CBranchView* pbranchview);
	int								BreakNode(CBranchView* pbranchview);

	void							CalculateAxis(int direction, double length, double length2, int prex, int prey, CBranchView* pbranchviewheader, CNodeView* prevNode );
	void							SetBranchPosition( CBranchView* pbranchview );

	BOOL							CheckPosition( CNodeView* pRootNode, CBranchView* pRootBranch );
	CNodeView*						FindSamePosition( CNodeView* pTargetNode );
	CNodeView*						FindSamePositionRcv( CNodeView* pTargetNode, CNodeView* prevnodeview );
	int								CheckCrossPosition( CNodeView* pNode1, CNodeView* pNode2 );
	CNodeView*						FindCrossNode();
	CNodeView*						FindDirectPathNode( CNodeView* pTargetNode );
	CNodeView*						FindTargetNode( int nDirection );

	int								GetMaxAxisX();
	int								GetMinAxisX();
	int								GetMaxAxisY();
	int								GetMinAxisY();
	void							ShiftPosition( int nPosX, int nPosY );
	void							SetPosition();

	BOOL							IsCBreaker();
	BOOL							IsSwitch();
	CString							GetStrKind();
	CString							GetKindName();

	BOOL							IsProtectSw();

	CNodeView*						Copy();
	CNodeView*						GetNextPathNode(int& nDirection);//DirectPath에서 다음노드와 다음노드의 방향을 찾는데만 사용할것!
	CNodeView*						GetNextPathNode();//DirectPath에서 다음노드를 찾는데만 사용할것!
	BOOL							IsOverlapNode( CNodeView* pRootNode, CBranchView* pRootBranch );

	CNodeView*						GetSelectNodeView( CPoint ptPosition );
	CNodeView*						GetSelectNodeView( int nNDIdx, int nNotDbID );
	CNodeView*						GetNodeView( int nID );


	CDPoint							m_pGISDPoint;
	CDPoint							m_pSLDDPoint;
	void							DrawGIS(CDC* BufferDC, int nSize, double dZoom, double pCenX, double pCenY, CPoint ptCen, int nStep, int nZoomLevel);
	void							DrawGISCB(CDC* BufferDC);
	void							DrawGISDG(CDC* BufferDC);
	void							DrawGISAutoSw(CDC* BufferDC);
	void							DrawGISManualSw(CDC* BufferDC);
	void							DrawGISOH(CDC* BufferDC);
	void							DrawGISCOS(CDC* BufferDC);
	void							DrawGISDummy(CDC* BufferDC);
	void							DrawGISCustomer(CDC* BufferDC);
	void							DrawGISSVR(CDC* BufferDC);
	void							DrawGISEFI(CDC* BufferDC);
	void							DrawGISTR(CDC* BufferDC);
	void							DrawGISALTS(CDC* BufferDC);
	void							DrawGISMulti(CDC* BufferDC);

	CString							GetGISSimbolText();
	CRect							GetGISSimbolRect(double dx, double dy, int nZoomLevel);
	void							SetGISBranchPos(CBranchView* pbranchview);


};

typedef CTypedPtrArray<CObArray, CNodeView*> CNodeViewArray;