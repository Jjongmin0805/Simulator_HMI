#pragma once

class AFX_EXT_CLASS CMP_Object
{
public:
	CMP_Object(void);
	~CMP_Object(void);

	CRect																						GetRectDispBack(){ return m_rectDispBack; };

	void																						SetInit();
	void																						SetPosition( CPoint ptXY1, CPoint ptXY2 );
	void																						SetDisplayLineWidth( int nWidth );
	void																						SetExceptionRect( CRect rectException );
	void																						SetDrawType( int nType );
	int																							GetDrawType();

	void																						MpDraw( CDC* pDC );
//	virtual void																				MpDraw( CDC* pDC ) = 0;
	virtual BOOL																				GetDrawILrect( int nIndex, int nCnt, CRect& rectFirst, CRect& rectLast ) = 0;

protected:
	int								m_nDrawType;												// ����
	CRect							m_rectDispBack;												// ��ü Rect ũ��
	int								m_nDispCycleIndex;											// �����ִ� ��ġ �ε���
	int								m_nAllDispSize;												// ��ü rect-width�� ���� �����ִ� moving picture ����
	int								m_nDispLineWidth;											// Line�� ũ�⸦ ���Ѵ�.
};

typedef								vector< CMP_Object* >										VECMPOBJs;



class AFX_EXT_CLASS CMP_Object_SIDETB : public CMP_Object
{
public:
	CMP_Object_SIDETB(void);
	~CMP_Object_SIDETB(void);

	virtual BOOL																				GetDrawILrect( int nIndex, int nCnt, CRect& rectFirst, CRect& rectLast );
};

class AFX_EXT_CLASS CMP_Object_SIDEBT : public CMP_Object
{
public:
	CMP_Object_SIDEBT(void);
	~CMP_Object_SIDEBT(void);

	virtual BOOL																				GetDrawILrect( int nIndex, int nCnt, CRect& rectFirst, CRect& rectLast );
};

class AFX_EXT_CLASS CMP_Object_SIDELR : public CMP_Object
{
public:
	CMP_Object_SIDELR(void);
	~CMP_Object_SIDELR(void);

	virtual BOOL																				GetDrawILrect( int nIndex, int nCnt, CRect& rectFirst, CRect& rectLast );
};

class AFX_EXT_CLASS CMP_Object_SIDERL : public CMP_Object
{
public:
	CMP_Object_SIDERL(void);
	~CMP_Object_SIDERL(void);

	virtual BOOL																				GetDrawILrect( int nIndex, int nCnt, CRect& rectFirst, CRect& rectLast );
};