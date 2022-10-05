#ifndef _SKINEDIT_H
#define _SKINEDIT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// CSkinEdit

class CSkinEdit : public CEdit
{
	DECLARE_DYNAMIC(CSkinEdit)

public:
	CSkinEdit();
	virtual ~CSkinEdit();

public:
	enum DATA_TYPE : int
	{
		NONE		= 0,
		BIGINT		= -5,
		CHAR		= 1,
		NUMERIC		= 2,
		INTEGER		= 4,
		SMALLINT	= 5,
		FLOAT		= 6,
		REAL		= 7,
		DOUBLE		= 8,
		DATE		= 9,
		VARCHAR		= 12,
	};

public:		
	void	SetTextColor  ( COLORREF cfText    )					{	m_cfText = cfText;  }
	void	SetBitmapPos  ( int nXPos, int nYPos )					{	m_nXPos  = nXPos;  m_nYPos = nYPos;	}
	void	SetLIMIT_TYPE ( int  nLIMIT_TYPE = DATA_TYPE::NONE )	{   m_nLIMIT_TYPE = nLIMIT_TYPE;   }
	void	SetLIMIT_SIZE ( int  nLIMIT_SIZE = 0               )	{   m_nLIMIT_SIZE = nLIMIT_SIZE;   }
	int		GetLIMIT_TYPE ()										{	return m_nLIMIT_TYPE;	}
	int		GetLIMIT_SIZE ()										{	return m_nLIMIT_SIZE;	}

	BOOL    INPUT_NUMBER( WPARAM wParam );
	BOOL    INPUT_FLOAT ( WPARAM wParam );	
	BOOL    INPUT_CHAR  ( WPARAM wParam );

	void	SetBkColor	   ( COLORREF cfBackGround );
	void	SetBitmapID   ( UINT uDefaultImage );

	virtual BOOL PreTranslateMessage( MSG* pMsg );

protected:	
	HBITMAP		 m_hBmpDefault;		// ��� �̹���
	SIZE		 m_sizeDefault;		// ��� ������
	
	BOOL		 m_bBkgColor;		// ���� ����
	COLORREF	 m_cfText;			// ���ڻ�
	COLORREF	 m_cfBackGround;	// ����

	int			 m_nXPos;			// �׸��� ������ġ: X��ǥ
	int			 m_nYPos;			// �׸��� ������ġ: Y��ǥ
	int			 m_nLIMIT_TYPE;
	int			 m_nLIMIT_SIZE;
		
public:
	afx_msg	BOOL OnEnChange  ();
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg BOOL OnSetCursor ( CWnd* pWnd, UINT nHitTest, UINT message );
	afx_msg void OnKeyDown   ( UINT nChar, UINT nRepCnt, UINT nFlags );	

protected:
	DECLARE_MESSAGE_MAP()
};

#endif	//_SKINEDIT_H