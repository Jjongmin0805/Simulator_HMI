#ifndef _SKINPOPUPDIALOG_H
#define _SKINPOPUPDIALOG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CSkinPopupDialog dialog

class CSkinPopupDialog : public CDialog
{
public:
	CSkinPopupDialog ( UINT nResourceID, CWnd* pParent = NULL );
	~CSkinPopupDialog();

	enum	{	CLICKED_BOX_NONE = 0,
				CLICKED_BOX_EXIT
			};

// Attributes
public:
	COLORREF	m_cfBkMain;			// 윈도우 메인 배경색	
	COLORREF	m_cfBkTitle;		// 타이틀 배경색
	BOOL		m_bTracking;		// 현재 마우스 박스위에 있는지 아닌지 상태 플래그
	int			m_nClickedBox;		// 현재 클릭된 박스 정보

	// 비트맵 사이즈
	SIZE		m_sizeCapL;			// 윈도우 캡션 왼쪽
	SIZE		m_sizeCapM;			// 윈도우 캡션 중앙
	SIZE		m_sizeCapR;			// 윈도우 캡션 오른쪽
	SIZE        m_sizeFrmL;			// 윈도우 프레임 왼쪽
	SIZE        m_sizeFrmLB;		// 윈도우 프레임 왼쪽아래 
	SIZE        m_sizeFrmB;			// 윈도우 프레임 아래
	SIZE        m_sizeFrmRB;		// 윈도우 프레임 오른쪽 
	SIZE        m_sizeFrmR;			// 윈도우 프레임 오른쪽아래
	SIZE		m_sizeExit;			// 윈도우 종료 박스 사이즈
	SIZE		m_sizeBkMain;		// 윈도우 배경화면

	// 비트맵 핸들
	HBITMAP		m_hBmpCapL;			// 윈도우 캡션 왼쪽
	HBITMAP		m_hBmpCapM;			// 윈도우 캡션 중앙
	HBITMAP		m_hBmpCapR;			// 윈도우 캡션 오른쪽
	HBITMAP		m_hBmpFrmL;			// 윈도우 프레임 왼쪽
	HBITMAP		m_hBmpFrmLB;		// 윈도우 프레임 왼쪽아래
	HBITMAP		m_hBmpFrmB;			// 윈도우 프레임 아래
	HBITMAP		m_hBmpFrmR;			// 윈도우 프레임 오른쪽
	HBITMAP		m_hBmpFrmRB;		// 윈도우 프레임 오른쪽 아래
	HBITMAP		m_hBmpExit;			// 윈도우 종료 박스
	HBITMAP		m_hBmpBkMain;		// 윈도우 배경화면

	// 아이콘 핸들
	HICON		m_hIcon;
	
protected:
	CString		m_strTitle;			// 윈도우 캡션 타이틀
	int			m_nWidth;			// 윈도우 가로길이
	int			m_nHeight;			// 윈도우 세로길이
	CFont	   *m_pFontText;		// 타이틀 폰트

// Operations
public:
	CFont		*SetFont      ( CString strFaceName, UINT nFontSize, BOOL bBold = FALSE );
	void		 DrawBitmap   ();	
	void		 SetBkBitmap  ( UINT nBitmapID );
	void		 SetBkColor   ( COLORREF clrBkColor )		{	m_cfBkMain  = clrBkColor;					}
	void		 SetBkTitle   ( COLORREF clrBkColor )		{	m_cfBkTitle = clrBkColor;					}
	void		 SetTitle     ( CString strTitle )			{	m_strTitle  = strTitle;						}
	void		 SetWindowSize( int nWidth, int nHeight )	{	m_nWidth = nWidth;	m_nHeight = nHeight;	}
	virtual BOOL PreTranslateMessage( MSG* pMsg );

protected:
	virtual void DoDataExchange( CDataExchange* pDX );    // DDX/DDV support	

	afx_msg int  OnCreate       ( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnDestroy      ();	
	afx_msg void OnNcPaint      ();
	afx_msg void OnPaint        ();
	afx_msg BOOL OnNcActivate   ( BOOL bActive );
	afx_msg void OnNcCalcSize   ( BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp );
	afx_msg void OnNcMouseMove	( UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown( UINT nHitTest, CPoint point);	
	afx_msg void OnNcMouseLeave ();
	afx_msg BOOL OnEraseBkgnd   ( CDC* pDC );
			
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif	//_SKINPOPUPDIALOG_H