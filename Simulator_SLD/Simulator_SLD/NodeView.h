#pragma once
#include "BranchView.h"

#define GRID_GAP																	150//�⺻�׸��� 1ĭ�� �ʺ�

#define SELECT_DRAW_COLOR															RGB( 200, 200, 200 )
#define	DEFALUT_TEXT_COLOR															RGB( 255, 255, 255 )
#define	DEFALUT_PRINT_COLOR															RGB( 0, 0, 0 )

// CNodeView ��� ����Դϴ�.

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

	int								m_nDbID;		//���ID
	int								m_nSwKindID;	//����Ÿ��
	int								m_nKCIMType;	//KCIM����Ÿ��
	int								m_nCeqType;		//CEQŸ��
	CString							m_szLoc;		//���ֹ�ȣ(��Ī)
	BOOL							m_bStatus;		//����
	CString							m_szLocNo;		//����ȭ��ȣ(������) -> ������Ÿ��(����, �ܺ�)���� ���. ��, CB�϶��� �����Ҹ�����.
	int								m_nNDID[2];		//�Ϲݸ���϶��� NodeIdx(from-to), �׷����϶��� GNodeIdx(from-to);
													//�����ü�϶��� [1]�� �����η� ���ο���/�ܺο��� ���а���
                                                    //�ܺ�DL�� 0: ������� dlIdx,	1: ����
													//����DL�� 0: ������ND(GND)Idx,	1: ������弳�� m_nDbID -> ���ο���� �ܼ����� 2���� ���� �����ϴϱ�, �ٸ������� ���� ���� [1]�� �ʿ���.

	int								m_nALTSCBSW;	//ALTS�ÿ��� ��� -> �ݴ��� ����(CBSW)�� ������ ����.

	int								m_nTongID;		//��ȸ���϶� TongID
	int								m_nCaption;		//��ȸ���϶� ���ڹ�ȣ

	int								m_nPosX;		//��ü X��ǥ
	int								m_nPosY;		//��ü Y��ǥ
	
	CRect							m_rectObj;		//�ܼ����󿡼��� ������ ����

	int								m_nFromND;		//(��Ƽ)��������϶� �ܼ������� ������ ND����(��ȸ�� ������ ����⸦ ã������)

	CNodeView*						m_pLeft;
	CNodeView*						m_pCenter;
	CNodeView*						m_pRight;
	CNodeView*						m_pLeftTop;
	CNodeView*						m_pRightBottom;

	int								m_nCrossCnt;
	int								m_nReviseLevel;
	int								m_nDirection;
	int								m_nDirection2;//5ȸ���̻� �밢���б�Ȯ�ο�.

	BOOL							m_bBoundarySelect;//�ٱ��� ��������
	void							ClearBoundaryCheck();

	CString							m_szCEQID;		//������ CEQID

	//������� ����
	BOOL							IsProtOperSw( int nCbswIdx );
	int								GetFiInfoIdx( int nCbswIdx );

	CNodeView*						FindUnsetNode(int reviselevel);
	int								SetLongestPathToCenter(double maxlength, double currentlength, CBranchView* pbranchview);
	void							SetShortestPathDiagonal(CBranchView* pranchview);
	void							SetLongestPathToRightTop(int direction, CBranchView* pranchview);//��б⸦ ������/�������� ��ġ��(�������� ���)
	void							SetLongestPathToRightBottom(int direction, CBranchView* pranchview);//��б⸦ ������/�Ʒ������� ��ġ��(�������� �ϴ�)
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
	CNodeView*						GetNextPathNode(int& nDirection);//DirectPath���� �������� ��������� ������ ã�µ��� ����Ұ�!
	CNodeView*						GetNextPathNode();//DirectPath���� ������带 ã�µ��� ����Ұ�!
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