#ifndef _SKINMAINDIALOG_H
#define _SKINMAINDIALOG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CSkinMainDialog dialog

class CSkinMainDialog : public CDialog
{
public:
	CSkinMainDialog ( UINT nResourceID, CWnd* pParent = NULL );
	~CSkinMainDialog();

	enum	{	CLICKED_BOX_NONE = 0,
				CLICKED_BOX_MINIMIZE,
				CLICKED_BOX_MAXIMIZE,
				CLICKED_BOX_RESTORE,
				CLICKED_BOX_EXIT
			};

// Attributes
protected:		
	BOOL		m_bTracking;		// 현재 마우스 박스위에 있는지 아닌지 상태 플래그
	int			m_nClickedBox;		// 현재 클릭된 박스 정보

	COLORREF	m_cfBkMain;			// 윈도우 메인 배경색
	COLORREF	m_cfBkMenu;			// 윈도우 메뉴 배경색
	COLORREF	m_cfBkSepa;			// 윈도우 메뉴와 탭 구분선
	COLORREF	m_cfBkTab;			// 윈도우 탭   배경색

	// 비트맵 사이즈
	SIZE        m_sizeCapL;			// 윈도우 캡션 왼쪽
	SIZE        m_sizeCapM;	 		// 윈도우 캡션 중앙
	SIZE        m_sizeCapR;		 	// 윈도우 캡션 오른쪽
	SIZE        m_sizeFrmL;			// 윈도우 프레임 왼쪽
	SIZE        m_sizeFrmLB;		// 윈도우 프레임 왼쪽아래 
	SIZE        m_sizeFrmB;			// 윈도우 프레임 아래
	SIZE        m_sizeFrmRB;		// 윈도우 프레임 오른쪽 
	SIZE        m_sizeFrmR;			// 윈도우 프레임 오른쪽아래
	SIZE        m_sizeMin;			// 윈도우 최소 박스
	SIZE        m_sizeMax;			// 윈도우 최대 박스
	SIZE        m_sizeRes;			// 윈도우 복귀 박스
	SIZE        m_sizeExit;			// 윈도우 종료 박스	

	// 비트맵 핸들
	HBITMAP		m_hBmpCapL;			// 윈도우 캡션 왼쪽
	HBITMAP		m_hBmpCapM;			// 윈도우 캡션 중앙
	HBITMAP		m_hBmpCapR;			// 윈도우 캡션 오른쪽
	HBITMAP		m_hBmpFrmL;			// 윈도우 프레임 왼쪽
	HBITMAP		m_hBmpFrmLB;		// 윈도우 프레임 왼쪽아래
	HBITMAP		m_hBmpFrmB;			// 윈도우 프레임 아래
	HBITMAP		m_hBmpFrmR;			// 윈도우 프레임 오른쪽
	HBITMAP		m_hBmpFrmRB;		// 윈도우 프레임 오른쪽 아래
	HBITMAP		m_hBmpMin;			// 윈도우 최소 박스
	HBITMAP		m_hBmpMax;			// 윈도우 최대 박스
	HBITMAP		m_hBmpRes;			// 윈도우 복귀 박스
	HBITMAP		m_hBmpExit;			// 윈도우 종료 박스
	
protected:
	CString		m_strTitle;			// 윈도우 캡션 타이틀	
	CString		m_strLogIn;			// 로그인 표시

// Operations
public:
	void		 DrawBitmap ();	
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
	afx_msg BOOL OnSetCursor	( CWnd* pWnd, UINT nHitTest, UINT message );
	afx_msg void OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI );
	afx_msg void OnTimer		( UINT_PTR nIDEvent );
	afx_msg void OnNcLButtonDblClk( UINT nHitTest, CPoint point );
			
	DECLARE_MESSAGE_MAP()	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif	//_SKINMAINDIALOG_H
