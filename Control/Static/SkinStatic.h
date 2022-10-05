#ifndef _SKINSTATIC_H
#define _SKINSTATIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkinStatic :	public CStatic
{
public:
	CSkinStatic(void);
	virtual ~CSkinStatic(void);
		
	void SetTextFont   ( CFont *pFont		)		{	m_pFont		   = pFont;			}
	void SetSizeControl( SIZE sizeStatic    )		{	m_sizeStatic   = sizeStatic;	}	
	void SetTextColor  ( COLORREF cfText    )		{	m_cfText       = cfText;		}
	
	void SetTextStyle  ( DWORD dwStyle, BOOL bCenter = FALSE );
	void SetBkColor	   ( COLORREF cfBackGround );
	void SetText	   ( CString strText, int nWidth = 0, int nHeight = 0 );
	void SetBitmapID   ( UINT uDefaultImage );	
	void SetBitmapID   ( UINT uCapLImage, UINT uCapMImage, UINT uCapRImage );
	void SetTextCenter ( CDC *pDC, CString strText, DWORD dwStyle );

protected:
	HBITMAP		 m_hBmpDefault;		// ��� �̹���
	HBITMAP		 m_hBmpCapL;		// ��� ĸ�� �����̹���
	HBITMAP		 m_hBmpCapM;		// ��� ĸ�� �߾��̹���
	HBITMAP		 m_hBmpCapR;		// ��� ĸ�� �������̹���

	SIZE		 m_sizeDefault;		// ��� ������
	SIZE		 m_sizeCapL;		// ��� ĸ�� ���ʻ�����
	SIZE		 m_sizeCapM;		// ��� ĸ�� �߾ӻ�����
	SIZE		 m_sizeCapR;		// ��� ĸ�� �����ʻ�����
	SIZE		 m_sizeStatic;		// Static ������
	CFont		*m_pFont;			// ���� ��Ʈ

	int			 m_nWidth;			// ���� ��ġ
	int			 m_nHeight;			// ���� ����
	DWORD		 m_dwStyle;			// ���� ��Ÿ��

	BOOL		 m_bBkgColor;		// ���� ����
	BOOL		 m_bCenter;			// ��Ƽ���� �������
	CString		 m_strText;			// ����	
	COLORREF	 m_cfText;			// ���ڻ�
	COLORREF	 m_cfBackGround;	// ����

protected:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

#endif	//_SKINSTATIC_H