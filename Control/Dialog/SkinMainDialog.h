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
	BOOL		m_bTracking;		// ���� ���콺 �ڽ����� �ִ��� �ƴ��� ���� �÷���
	int			m_nClickedBox;		// ���� Ŭ���� �ڽ� ����

	COLORREF	m_cfBkMain;			// ������ ���� ����
	COLORREF	m_cfBkMenu;			// ������ �޴� ����
	COLORREF	m_cfBkSepa;			// ������ �޴��� �� ���м�
	COLORREF	m_cfBkTab;			// ������ ��   ����

	// ��Ʈ�� ������
	SIZE        m_sizeCapL;			// ������ ĸ�� ����
	SIZE        m_sizeCapM;	 		// ������ ĸ�� �߾�
	SIZE        m_sizeCapR;		 	// ������ ĸ�� ������
	SIZE        m_sizeFrmL;			// ������ ������ ����
	SIZE        m_sizeFrmLB;		// ������ ������ ���ʾƷ� 
	SIZE        m_sizeFrmB;			// ������ ������ �Ʒ�
	SIZE        m_sizeFrmRB;		// ������ ������ ������ 
	SIZE        m_sizeFrmR;			// ������ ������ �����ʾƷ�
	SIZE        m_sizeMin;			// ������ �ּ� �ڽ�
	SIZE        m_sizeMax;			// ������ �ִ� �ڽ�
	SIZE        m_sizeRes;			// ������ ���� �ڽ�
	SIZE        m_sizeExit;			// ������ ���� �ڽ�	

	// ��Ʈ�� �ڵ�
	HBITMAP		m_hBmpCapL;			// ������ ĸ�� ����
	HBITMAP		m_hBmpCapM;			// ������ ĸ�� �߾�
	HBITMAP		m_hBmpCapR;			// ������ ĸ�� ������
	HBITMAP		m_hBmpFrmL;			// ������ ������ ����
	HBITMAP		m_hBmpFrmLB;		// ������ ������ ���ʾƷ�
	HBITMAP		m_hBmpFrmB;			// ������ ������ �Ʒ�
	HBITMAP		m_hBmpFrmR;			// ������ ������ ������
	HBITMAP		m_hBmpFrmRB;		// ������ ������ ������ �Ʒ�
	HBITMAP		m_hBmpMin;			// ������ �ּ� �ڽ�
	HBITMAP		m_hBmpMax;			// ������ �ִ� �ڽ�
	HBITMAP		m_hBmpRes;			// ������ ���� �ڽ�
	HBITMAP		m_hBmpExit;			// ������ ���� �ڽ�
	
protected:
	CString		m_strTitle;			// ������ ĸ�� Ÿ��Ʋ	
	CString		m_strLogIn;			// �α��� ǥ��

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
