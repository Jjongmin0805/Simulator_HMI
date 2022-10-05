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
	HBITMAP		 m_hBmpDefault;		// 배경 이미지
	HBITMAP		 m_hBmpCapL;		// 배경 캡션 왼쪽이미지
	HBITMAP		 m_hBmpCapM;		// 배경 캡션 중앙이미지
	HBITMAP		 m_hBmpCapR;		// 배경 캡션 오른쪽이미지

	SIZE		 m_sizeDefault;		// 배경 사이즈
	SIZE		 m_sizeCapL;		// 배경 캡션 왼쪽사이즈
	SIZE		 m_sizeCapM;		// 배경 캡션 중앙사이즈
	SIZE		 m_sizeCapR;		// 배경 캡션 오른쪽사이즈
	SIZE		 m_sizeStatic;		// Static 사이즈
	CFont		*m_pFont;			// 글자 폰트

	int			 m_nWidth;			// 글자 위치
	int			 m_nHeight;			// 글자 높이
	DWORD		 m_dwStyle;			// 글자 스타일

	BOOL		 m_bBkgColor;		// 배경색 유무
	BOOL		 m_bCenter;			// 멀티라인 가운데정렬
	CString		 m_strText;			// 글자	
	COLORREF	 m_cfText;			// 글자색
	COLORREF	 m_cfBackGround;	// 배경색

protected:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

#endif	//_SKINSTATIC_H