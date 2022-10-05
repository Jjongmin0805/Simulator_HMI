
// Simulator_Editor.h: Simulator_Editor 응용 프로그램의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 주 기호입니다.


// CSimulatorEditorApp:
// 이 클래스의 구현에 대해서는 Simulator_Editor.cpp을(를) 참조하세요.
//

class CSimulatorEditorApp : public CWinAppEx
{
public:
	CSimulatorEditorApp() noexcept;


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSimulatorEditorApp theApp;
