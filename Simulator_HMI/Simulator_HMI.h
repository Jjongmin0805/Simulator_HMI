
// Simulator_HMI.h : Simulator_HMI ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CSimulator_HMIApp:
// �� Ŭ������ ������ ���ؼ��� Simulator_HMI.cpp�� �����Ͻʽÿ�.
//

class CSimulator_HMIApp : public CWinAppEx
{
public:
	CSimulator_HMIApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSimulator_HMIApp theApp;
