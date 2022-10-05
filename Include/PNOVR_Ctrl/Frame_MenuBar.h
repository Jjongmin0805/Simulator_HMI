#pragma once

// Frame_MenuBar ��ȭ �����Դϴ�.
class CFrame_MenuBar_Ctrl;
class AFX_EXT_CLASS CFrame_MenuBar : public CDialog
{
	DECLARE_DYNAMIC(CFrame_MenuBar)

public:
	CFrame_MenuBar(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFrame_MenuBar();

	void									CreateMenuBarCtrl( UINT nMainResourceID, UINT nSubClassResourceID );
	void									CreateMenuBarCtrl( UINT nResourceID );
	void									DrawMenuDlg();
	CRect									GetWinRect(){ return m_creatRect; };
	CRect									GetControlItemTrect();
	void									SetMoveThisWndReSize();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FRAME_MENUBAR };

protected:
	CFrame_MenuBar_Ctrl*					m_wndMenuBarCtrl;
	CRect									m_creatRect;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
