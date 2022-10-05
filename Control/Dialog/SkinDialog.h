#ifndef _SKINDIALOG_H
#define _SKINDIALOG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkinDialog : public CDialog
{
public:
	CSkinDialog ( UINT nResourceID, CWnd* pParent = NULL );
	~CSkinDialog();	

// Attributes
protected:	
	COLORREF	m_cfBkMain;			// 윈도우 메인 배경색

	// 비트맵 사이즈
	SIZE		m_sizeBkMain;		// 윈도우 배경화면	

	// 비트맵 핸들
	HBITMAP		m_hBmpBkMain;		// 윈도우 배경화면

	// Move Window
	BOOL		m_bMove;			// 다이얼로그 움직일수 있도록

// Operations
public:
	void		 SetMoveDlg ( BOOL bMove )		{	m_bMove = bMove;	}

	void		 SetBkColor ( COLORREF clrBkColor );
	void		 SetBkBitmap( UINT nBitmapID );
	virtual BOOL PreTranslateMessage( MSG* pMsg );

protected:
	virtual void DoDataExchange( CDataExchange* pDX );    // DDX/DDV support	

	afx_msg int  OnCreate     ( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnDestroy    ();
	afx_msg void OnPaint      ();
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point  );
	afx_msg BOOL OnEraseBkgnd ( CDC* pDC );

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif	//_SKINDIALOG_H
