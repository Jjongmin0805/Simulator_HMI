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
	COLORREF	m_cfBkMain;			// ������ ���� ����	
	COLORREF	m_cfBkTitle;		// Ÿ��Ʋ ����
	BOOL		m_bTracking;		// ���� ���콺 �ڽ����� �ִ��� �ƴ��� ���� �÷���
	int			m_nClickedBox;		// ���� Ŭ���� �ڽ� ����

	// ��Ʈ�� ������
	SIZE		m_sizeCapL;			// ������ ĸ�� ����
	SIZE		m_sizeCapM;			// ������ ĸ�� �߾�
	SIZE		m_sizeCapR;			// ������ ĸ�� ������
	SIZE        m_sizeFrmL;			// ������ ������ ����
	SIZE        m_sizeFrmLB;		// ������ ������ ���ʾƷ� 
	SIZE        m_sizeFrmB;			// ������ ������ �Ʒ�
	SIZE        m_sizeFrmRB;		// ������ ������ ������ 
	SIZE        m_sizeFrmR;			// ������ ������ �����ʾƷ�
	SIZE		m_sizeExit;			// ������ ���� �ڽ� ������
	SIZE		m_sizeBkMain;		// ������ ���ȭ��

	// ��Ʈ�� �ڵ�
	HBITMAP		m_hBmpCapL;			// ������ ĸ�� ����
	HBITMAP		m_hBmpCapM;			// ������ ĸ�� �߾�
	HBITMAP		m_hBmpCapR;			// ������ ĸ�� ������
	HBITMAP		m_hBmpFrmL;			// ������ ������ ����
	HBITMAP		m_hBmpFrmLB;		// ������ ������ ���ʾƷ�
	HBITMAP		m_hBmpFrmB;			// ������ ������ �Ʒ�
	HBITMAP		m_hBmpFrmR;			// ������ ������ ������
	HBITMAP		m_hBmpFrmRB;		// ������ ������ ������ �Ʒ�
	HBITMAP		m_hBmpExit;			// ������ ���� �ڽ�
	HBITMAP		m_hBmpBkMain;		// ������ ���ȭ��

	// ������ �ڵ�
	HICON		m_hIcon;
	
protected:
	CString		m_strTitle;			// ������ ĸ�� Ÿ��Ʋ
	int			m_nWidth;			// ������ ���α���
	int			m_nHeight;			// ������ ���α���
	CFont	   *m_pFontText;		// Ÿ��Ʋ ��Ʈ

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