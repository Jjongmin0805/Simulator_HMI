#pragma once

#include "./Dialog/SkinPopupDialog.h"
#include "./Button/SkinButton.h"
#include "./Static/SkinStatic.h"

#define DEFAULT_BUTTON_ID	20000		// �������� �����ϴ� Button�� �ο� �� ID
#define MARGIN_CONTROL		10			// ��Ʈ�ѵ鰣, �����¿��� ����

// CSkinMsgBox ��ȭ �����Դϴ�.

class CSkinMsgBox : public CSkinPopupDialog
{
	DECLARE_DYNAMIC(CSkinMsgBox)

public:
	CSkinMsgBox( UINT nResourceID, CWnd* pParent = NULL );   // ǥ�� �������Դϴ�.
	virtual ~CSkinMsgBox();

	CFont *SetFont   ( CString strFaceName, UINT nFontSize, BOOL bBold = FALSE );
	void   SetMBStyle( UINT uIconType, UINT uButtonType);							// ������ ��Ÿ��, ��ư ��Ÿ�� ����
	void   SetMessage( CString strMessage)	{	m_strMessage = strMessage;	}		// ȭ�鿡 ǥ���� �� �޼��� ����
	void   SetMsgBoxClose( BOOL bClose )	{	m_bMsgBoxClose = bClose;	}
	UINT   GetReturnValue()					{	return m_nRet;	}					// ������ ��ư�� �ش� �ϴ� �� ����

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

protected:
	CSkinButton *m_sbtnSelect[ 3 ];										// �������� ������ ��ư
	int  m_nSelectBtn;													// �������� ������ ��ư�� ����
	int  m_nSymbolID;													// Symbol ID ����
	int	 m_nStep;
	BOOL m_bMsgBoxClose;
	CStringArray m_saBtnNames;											// ��ư �ؽ�Ʈ

	CSkinStatic *m_sstIcon;												// �ɺ�
	CSkinStatic *m_sstMsg;												// �޼���	
	CFont	    *m_pFontMsg;											// Message ��Ʈ
	CFont	    *m_pFontBtn;											// ��ư ��Ʈ
	CFont	    *m_pFontBtnTooltip;										// ��ư ���� ��Ʈ


	CString		 m_strMessage;											// ���� �޼���
	int			 m_nButtonType;											// ��ư Ÿ��
	UINT		 m_nRet;												// Return value

public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer  ( UINT_PTR nIDEvent );
	virtual afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
