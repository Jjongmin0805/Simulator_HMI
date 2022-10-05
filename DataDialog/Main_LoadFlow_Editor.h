#pragma once

#include "../include/PNOVR_Ctrl/Ctrl_ColorComboBox.h"
#include "../include/PNOVR_Ctrl/Ctrl_ColorEdit.h"
#include "Main_LoadFlow_Mng.h"
//


//struct PNOVR_EraseObjData
//{
//	template <typename _container> void operator()(_container* pObjdata)
//	{
//		if (pObjdata != NULL)
//		{
//			delete pObjdata;
//			pObjdata = NULL;
//		}
//	}
//};

#define ID_MGLFEDIT_1_1                 20301
#define ID_MGLFEDIT_1_2                 20302
#define ID_MGLFEDIT_1_3                 20303
#define ID_MGLFEDIT_1_4                 20304
#define ID_MGLFEDIT_1_5                 20305
#define ID_MGLFEDIT_2_1                 20311
#define ID_MGLFEDIT_2_2                 20312
#define ID_MGLFEDIT_2_3                 20313
#define ID_MGLFEDIT_2_4                 20314
#define ID_MGLFEDIT_3_1                 20321
#define ID_MGLFEDIT_3_2                 20322
#define ID_MGLFEDIT_3_3                 20323
#define ID_MGLFEDIT_3_4                 20324



//#define								MAINVIEW_BGCOLOR											RGB( 204, 205, 207 )
//
//#define			START_USERMSG							150
//#define			PNOVR_LISTEDITRETURN					( WM_USER + START_USERMSG + 12 )
//
//
//
#define			theMainColorTxt			RGB( 16, 16, 16 )	
#define			theMainColorBgk			RGB(204, 205, 207)

// CMain_LoadFlow_Editor
class CMain_LoadFlow_Editor : public CWnd
{
	DECLARE_DYNAMIC(CMain_LoadFlow_Editor)

public:
	CMain_LoadFlow_Editor();
	virtual ~CMain_LoadFlow_Editor();

	BOOL									Create( const RECT& rect, CWnd* pParentWnd );
	void									SetView();

	void									CalcuCoordinates();
	void									ViewEmptyData( CDC* pDC );
	void									ViewCoordinates( CDC* pDC );
	void									ViewLoadLine( CDC* pDC );
	void									ViewEditContent( CDC* pDC );
	void									Draw_BackLabel( CDC* pDC );
	void									SetFLData_Loading();
	void									Loading_VMLFInfor();
	void									Writing_VMLFInfor();
	void									KeyDown( MSG* pMsg );
	void									KeyUp( MSG* pMsg );
	void									SetOffsetCtrlFocus_Return();
	void									SetOffsetCtrlFocus_Tab();
	void									Writing_VMLFInfor_File();

	CMain_LoadFlow_Mng*						GetLFMng() { return m_pLFMng; };

protected:
	void									ViewChageLFData( CLFData* pLFData );
	void									CreateComboCtrl();
	void									CreateEditCtrl();
	void									CreateButtonCtrl();
	void									SetSSDL_ComboBox();
	int										CalueValuePosition( CLFData* pLFData );
	BOOL									Draw( CDC* pDC );
	void									DrawInvalidate();
	CLFData*								GetLFData( wstring szSSName, wstring szDLName, wstring szGENName, int nType );
	void									CheckRnageMultiSelect( int nStart, int nEnd );
	void									SetOffsetCtrlFocus();
	CRect									ViewRoundLoadLine( CDC* pDC, bool bScreenSizeOn );

	CCtrl_ColorEdit							m_OffsetEdit1, m_OffsetEdit2, m_OffsetEdit3, m_OffsetEdit4;
	CRect									m_OffsetRect1, m_OffsetRect2, m_OffsetRect3, m_OffsetRect4;
	CButton									m_FLOffset_Btn, m_FLWrite_Btn;
	CButton									m_FLAppStart_Btn, m_FLAppStop_Btn;
	CRect									m_FLOffset_BtnRect, m_FLWrite_BtnRect;

	CCtrl_ColorComboBox						m_Combo_FLApp;
	CRect									m_FLAppStart_BtnRect, m_FLAppStop_BtnRect, m_FLAppExe_ComboRect;
	CCtrl_ColorComboBox						m_InforCombo1, m_InforCombo2, m_InforCombo3, m_InforCombo4;
	int										m_nCtrlKey, m_nShiftKey;
	int										m_nOldMultiSelectIndex;
	int										m_nOffsetFocus;					// 상단 Edit 포커스 위치 인덱스
	CString									m_szBBAppFileName;

	vector<CLFData*>						m_vecLFData;
	CLFData*								m_pLFData;

	_tstring								m_szLabelValue;
	CRect									m_LabelRect, m_LabelTitleRect;

	CMain_LoadFlow_Mng*						m_pLFMng;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSDMSLfeditCombo11SelectChange();
	afx_msg void OnSDMSLfeditCombo12SelectChange();
	afx_msg void OnSDMSLfeditCombo13SelectChange();
	afx_msg void OnSDMSLfeditCombo14SelectChange();
	afx_msg void OnSDMSLfeditComboFLAppSelectChange();
	afx_msg void OnSDMSLfeditButton31();
	afx_msg void OnSDMSLfeditButton32();
	afx_msg void OnSDMSLfeditButton33();
	afx_msg void OnSDMSLfeditButton34();
	afx_msg LRESULT OnSendMsgEditReturn( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnSendMsg2LoadFlow( WPARAM wParam, LPARAM lParam );
};

