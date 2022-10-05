#pragma once
#include "../DPObject/DPoint.h"

// CBranchView ��� ����Դϴ�.
#define	FLOWLINE_THICK			10
#define SHOW_TEXT_SCALE			0.65//������ 0.7���Ͽ����� Text �����
#define SHOW_TEXT_SCALE_GIS		15//GIS�� zoomscale�� ~���ϸ� �����

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

	int								m_nDbID;		//�Ϲݸ�忡���� BR_STA_ID, �׷��忡���� GBR_STA_ID
	CString							m_szCeqID;
	int								m_nOverHead;	//0:����, 1:����

	int								m_nNode1;		//������ �����ID
	int								m_nNode2;		//������ �����ID
	int								m_nPosX1;		//������ ����� X��ǥ
	int								m_nPosY1;		//������ ����� Y��ǥ
	int								m_nPosX2;		//������ ����� X��ǥ
	int								m_nPosY2;		//������ ����� Y��ǥ

	double							m_dRp;			//����� R
	double							m_dR0;			//����� R
	double							m_dXp;			//����� X
	double							m_dX0;			//����� X

	int								m_nLineTypeCd;	//�����ڵ�
	double							m_dLengthReal;	//���� ��������
	double							m_dLengthDisp;	//�ܼ����� ǥ�õǴ� ������ �����
	double							m_dLengthDisp2;	//�ܼ����� ǥ�õǴ� ������ �����2(�밢�б��϶��� ���)
	double							m_dLoad;		//��������

	int								m_nDeadLineDepth;//��Ȱ������(�缱 DEPTH)
	BOOL							m_bNaviShow;	//������̼ǿ� ���� ���̱�/�����

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
	void							IncreaseLengthDisp2(double dStep = 1.0)		{m_dLengthDisp2 += dStep;};//�밢�б⿡�� ���
	double							GetLengthDisp2()							{return m_dLengthDisp2;};//�밢�б⿡�� ���
	void							SetLengthDisp2(double dLen)					{m_dLengthDisp2 = dLen;};//�밢�б⿡�� ���
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
	CDPArray						m_ptArr;		//���� ��ġ �迭(���������ʹ� ��Ʈ��Ű��...)
	CZPArray						m_pZPArray;

};

typedef CTypedPtrArray<CObArray, CBranchView*> CBranchViewArray;
