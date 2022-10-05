#pragma once

#include "./Dialog/SkinPopupDialog.h"
#include "./Button/SkinButton.h"
#include "./Static/SkinStatic.h"

#define DEFAULT_BUTTON_ID	20000		// 동적으로 생성하는 Button에 부여 할 ID
#define MARGIN_CONTROL		10			// 컨트롤들간, 상하좌우의 여백

// CSkinMsgBox 대화 상자입니다.

class CSkinMsgBox : public CSkinPopupDialog
{
	DECLARE_DYNAMIC(CSkinMsgBox)

public:
	CSkinMsgBox( UINT nResourceID, CWnd* pParent = NULL );   // 표준 생성자입니다.
	virtual ~CSkinMsgBox();

	CFont *SetFont   ( CString strFaceName, UINT nFontSize, BOOL bBold = FALSE );
	void   SetMBStyle( UINT uIconType, UINT uButtonType);							// 아이콘 스타일, 버튼 스타일 지정
	void   SetMessage( CString strMessage)	{	m_strMessage = strMessage;	}		// 화면에 표시해 줄 메세지 지정
	void   SetMsgBoxClose( BOOL bClose )	{	m_bMsgBoxClose = bClose;	}
	UINT   GetReturnValue()					{	return m_nRet;	}					// 선택한 버튼에 해당 하는 값 리턴

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

protected:
	CSkinButton *m_sbtnSelect[ 3 ];										// 동적으로 생성할 버튼
	int  m_nSelectBtn;													// 동적으로 생성할 버튼의 개수
	int  m_nSymbolID;													// Symbol ID 종류
	int	 m_nStep;
	BOOL m_bMsgBoxClose;
	CStringArray m_saBtnNames;											// 버튼 텍스트

	CSkinStatic *m_sstIcon;												// 심볼
	CSkinStatic *m_sstMsg;												// 메세지	
	CFont	    *m_pFontMsg;											// Message 폰트
	CFont	    *m_pFontBtn;											// 버튼 폰트
	CFont	    *m_pFontBtnTooltip;										// 버튼 툴팁 폰트


	CString		 m_strMessage;											// 메인 메세지
	int			 m_nButtonType;											// 버튼 타입
	UINT		 m_nRet;												// Return value

public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer  ( UINT_PTR nIDEvent );
	virtual afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
