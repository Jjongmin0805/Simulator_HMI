#ifndef _SKINPROGRESSBAR_H
#define _SKINPROGRESSBAR_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkinProgressbar : public CProgressCtrl
{
public:
	CSkinProgressbar();
	virtual ~CSkinProgressbar();

	void SetRange(int nLower, int nUpper);
	int  SetStep (int nStep);
	int  SetPos  (int nPos);
	int  StepIt  ();
		
	void SetTextFont   ( CFont *pFont )		{	m_pFont		   = pFont;   }	
	void SetTextColor  ( COLORREF rgb )		{	m_clrTextOnBar = rgb;	  }
	void SetText       ( CString strText )	{	m_strText      = strText; }
	void SetBitmapID   ( UINT uFrameImage, UINT uBarImage );

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinProgressbar)
	//}}AFX_VIRTUAL

protected:
	virtual void OnDrawText(CDC* pDC, int nPercentage, CRect rcCtrl, CRect rcProgress, BOOL bVertical);

	//{{AFX_MSG(CSkinProgressbar)
	afx_msg void OnPaint();
	//}}AFX_MSG

	int m_nLower;
	int m_nUpper;
	int m_nRange;
	int m_nStep;
	int m_nPos;	

	DWORD		m_dwWidth;
	DWORD		m_dwHeight;

	HBITMAP		m_hBmpBar;	
	HBITMAP		m_hBmpFrame;	
	SIZE		m_sizeFrame;
	COLORREF    m_clrTextOnBar;
	CFont	   *m_pFont;
	CString     m_strText;

private:	
	void CalcRange();
	void TileBitmap( HDC hdcDest, HDC hdcSrc, CRect rect );

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif	//_SKINPROGRESSBAR_H
