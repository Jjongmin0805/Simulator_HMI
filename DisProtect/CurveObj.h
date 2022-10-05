// CurveObj.h: interface for the CCurveObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEOBJ_H__AA92F50C_8423_44A1_9315_DAEBC81266A8__INCLUDED_)
#define AFX_CURVEOBJ_H__AA92F50C_8423_44A1_9315_DAEBC81266A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"

typedef struct _rc_data
{
	float m_start;
	float m_end;
	float m_a;
	float m_b;
	float m_c;
	float m_d;
	float m_e;
	float m_n;
} RCDATA;

typedef CArray<RCDATA, RCDATA&> CRcArray;

class AFX_EXT_CLASS CCurveObj : public CObject  
{
public:
	double m_dDGPU;
	int m_nColorType;
	CString m_strName;
	BOOL m_bSecond;
	void SetSecond(BOOL bSecond) {m_bSecond = bSecond;};
	CCurveObj();
	virtual ~CCurveObj();
	virtual void Draw( CDC* pDC, CRect rect, double dTab, BOOL bShowPu = FALSE ) {};
	virtual void ShowValue( CDC* pDC, CRect rect, double dTab, double x, BOOL bShowPu = FALSE ) {};
	COLORREF GetColor();
};


class AFX_EXT_CLASS CCurveRecloser : public CCurveObj  
{
public:
	void SetAt(int nIdx, RCDATA* pdata);
	double m_dOneValue;
	void ShowValue( CDC* pDC, CRect rect, double dTab, double x, BOOL bShowPu = FALSE );
	void Add(RCDATA* pdata);
	void Draw( CDC* pDC, CRect rect, double dTab, BOOL bShowPu = FALSE );
	double GetY(float in);
	double m_dmin, m_dmax;
	CCurveRecloser();
	virtual ~CCurveRecloser();
	double m_dPU;
	double m_dTm;
	double m_dTa;
	CRcArray*	GetRcdata() {return &m_pRcdata;};
	//커브정보추가
	double m_dMaxAmp, m_dAmp;

private:
	CRcArray m_pRcdata;
};

class AFX_EXT_CLASS CCurveRelay : public CCurveObj  
{
public:
	void ShowValue( CDC* pDC, CRect rect, double dTab, double x, BOOL bShowPu = FALSE );
	void Draw( CDC* pDC, CRect rect, double dTab, BOOL bShowPu = FALSE );
	CCurveRelay( double a, double b, double c, double d, double e, double n, double L);
	virtual ~CCurveRelay();
	double GetY(double in);
	double m_dPU, m_L;
	//커브정보추가
	double m_dTab, m_dCT, m_dAmp;

private:
	double m_a, m_b, m_c, m_d, m_e, m_n;
};


class AFX_EXT_CLASS CCurveFuse : public CCurveObj  
{
public:
	void ShowValue( CDC* pDC, CRect rect, double dTab, double x, BOOL bShowPu = FALSE );
	void Draw( CDC* pDC, CRect rect, double dTab, BOOL bShowPu = FALSE );
	CCurveFuse( double start, double end, double a, double b, double n);
	virtual ~CCurveFuse();
	double m_dAmp;

private:
	double GetY( double in );
	double m_start, m_end, m_a, m_b, m_n;

};

#endif // !defined(AFX_CURVEOBJ_H__AA92F50C_8423_44A1_9315_DAEBC81266A8__INCLUDED_)
