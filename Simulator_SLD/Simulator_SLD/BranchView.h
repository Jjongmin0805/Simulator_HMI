#pragma once
#include "../DPObject/DPoint.h"

// CBranchView 명령 대상입니다.
#define	FLOWLINE_THICK			10
#define SHOW_TEXT_SCALE			0.65//배율이 0.7이하에서는 Text 미출력
#define SHOW_TEXT_SCALE_GIS		15//GIS의 zoomscale이 ~이하면 미출력

class CBranchView : public CObject

{
public:
	CBranchView();
	virtual ~CBranchView();

	void							DBSave( int nOffice, CString sztime, CString szSubstID, int nCBID, int nSLDMode );

	void							RemoveData();
	void							Draw(CDC* BufferDC, double dScale, int nShowOption, BOOL bFirst, BOOL bPrint);
	void							DrawMeasData(CDC* BufferDC, double dScale);
	void							ShowMeasValue( CDC* BufferDC, double dScale );
	void							DrawNavi(CDC* BufferDC, double dRatioX, double dRatioY);
	void							Serialize(CArchive& ar, double dVersion);

	void							DrawFaultDirection( CDC* BufferDC, double dScale, BOOL bReverse );
	void							DrawFlow(CDC* BufferDC, double dScale, CDC* pDC);
	CPoint							RotatePoint( CPoint ptCurrent, double dAngle, CPoint ptAxis );

	int								GetFromCbswIdx(int& nCbswIdx);

	int								m_nDbID;		//일반모드에서는 BR_STA_ID, 그룹모드에서는 GBR_STA_ID
	CString							m_szCeqID;
	int								m_nOverHead;	//0:가공, 1:지중

	int								m_nNode1;		//전원측 개폐기ID
	int								m_nNode2;		//부하측 개폐기ID
	int								m_nPosX1;		//전원측 개폐기 X좌표
	int								m_nPosY1;		//전원측 개폐기 Y좌표
	int								m_nPosX2;		//부하측 개폐기 X좌표
	int								m_nPosY2;		//부하측 개폐기 Y좌표

	double							m_dRp;			//정상분 R
	double							m_dR0;			//영상분 R
	double							m_dXp;			//정상분 X
	double							m_dX0;			//영상분 X

	int								m_nLineTypeCd;	//선종코드
	double							m_dLengthReal;	//실제 구간긍장
	double							m_dLengthDisp;	//단선도에 표시되는 구간의 긍장비
	double							m_dLengthDisp2;	//단선도에 표시되는 구간의 긍장비2(대각분기일때만 사용)
	double							m_dLoad;		//구간부하

	int								m_nDeadLineDepth;//사활선정보(사선 DEPTH)
	BOOL							m_bNaviShow;	//내비게이션에 구간 보이기/숨기기

	int								m_nNDID[2];

// 	int								m_nFlowCount;
// 	CBitmap							m_Icons[3];

	BOOL							m_bFaultArea;

	BOOL							m_bBoundarySelect;
	void							SetBoundarySelect(BOOL bSet) { m_bBoundarySelect = bSet; };
	BOOL							GetBoundarySelect() { return m_bBoundarySelect; };
	void							ClearBoundarySelect(BOOL bAreaMode);
	void							SetChangeVoltLevel(int nTabValue);

	void							IncreaseLengthDisp(int node1, int node2, double dStep = 1.0);
	double							GetLengthDisp(int node1, int node2);
	void							SetLengthDisp(int node1, int node2, double dLen);
	CBranchView*					Add(int nId, int node1, int node2, int nNDIdx1, int nNDIdx2, double lengthreal, int nLineType, int overheadcable, double dload, double dRp, double dR0, double dXp, double dX0, CString szCeqID, int nDeadLineDepth, BOOL bNaviShow );
	void							Add( CBranchView* pBranchView );
	void							SetPosition(int node1, int node2, int posx1, int posy1, int posx2, int posy2);
	void							SetLength(int nID1, int nID2, double dLen);
	
	CBranchView*					GetBranchView(int node1, int node2);
	CBranchView*					GetBranchView2(int node);
	CBranchView*					GetSelectBranchView(CPoint ptPosition, double dZoom);
	void							IncreaseLengthDisp(double dStep = 1.0)		{m_dLengthDisp += dStep;};
	double							GetLengthDisp()								{return m_dLengthDisp;};
	void							SetLengthDisp(double dLen)					{m_dLengthDisp = dLen;};
	void							IncreaseLengthDisp2(double dStep = 1.0)		{m_dLengthDisp2 += dStep;};//대각분기에만 사용
	double							GetLengthDisp2()							{return m_dLengthDisp2;};//대각분기에만 사용
	void							SetLengthDisp2(double dLen)					{m_dLengthDisp2 = dLen;};//대각분기에만 사용
	BOOL							IsSelectArea( CPoint ptPosition, double dZoom );

	CBranchView*					Copy();
	CBranchView*					m_pNext;




	CDPoint							m_pSLDDPoint1;
	CDPoint							m_pGISDPoint1;
	CDPoint							m_pSLDDPoint2;
	CDPoint							m_pGISDPoint2;

	void							SetGISPosition(int node1, int node2, CDPoint& dSLDPoint1, CDPoint& dGISDPoint1, CDPoint& dSLDPoint2, CDPoint& dGISDPoint2);
	void							DrawGIS(CDC* BufferDC, int nSize, double dZoom, double pCenX, double pCenY, CPoint ptCen, int nStep);
	void							DrawGIS2(CDC* BufferDC, int nSize, double dZoom, double pCenX, double pCenY, CPoint ptCen, int nStep2);

	void							SetZipDPArray();
	void							SetZip();
	CDPArray						m_ptArr;		//선로 위치 배열(다중포인터는 콘트롤키로...)
	CZPArray						m_pZPArray;

};

typedef CTypedPtrArray<CObArray, CBranchView*> CBranchViewArray;
