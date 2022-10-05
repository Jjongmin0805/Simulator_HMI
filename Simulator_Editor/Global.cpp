// Global.cpp: implementation of the CGlobal class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "Global.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
CGlobal::CGlobal()
{
	UINT i;

	for( i = 0; i < IDX_PNG_MAX; i++ )
	{
		m_infoBitmap[i].hBitmap = NULL;
		::ZeroMemory( &m_infoBitmap[ i ].bitmap, sizeof( BITMAP ) );
	}

	for( i = 0; i < IDX_FONT_MAX; i++ )
		m_pFont[ i ] = NULL;

	for( i = 0; i < IDX_ICN_MAX; i++ )
	{
		m_hIcon[ i ][ 0 ] = NULL;
		m_hIcon[ i ][ 1 ] = NULL;
		m_hIcon[ i ][ 2 ] = NULL;
	}	

	m_cfRGB[ IDX_RGB_MAIN_BACKGROUND  ] = RGB( 255, 255, 255 );		//	윈도우 배경색상			 : 흰색
	m_cfRGB[ IDX_RGB_MAIN_MENU		  ] = RGB( 227, 226, 226 );		//	윈도우 메인메뉴 배경색상 : 조금옅은회색
	m_cfRGB[ IDX_RGB_MAIN_TAB		  ] = RGB( 204, 204, 204 );		//	윈도우 메인탭 배경색상	 : 옅은회색
	m_cfRGB[ IDX_RGB_FONT_BLACK		  ] = RGB( 0, 0, 0 );			//	폰트 색상				 : 검은색
	m_cfRGB[ IDX_RGB_FONT_WHITE		  ] = RGB( 255, 255, 255 );		//	폰트 색상				 : 흰색
	m_cfRGB[ IDX_RGB_FONT_RED		  ] = RGB( 255, 0, 0 );			//	폰트 색상				 : 빨간색
	m_cfRGB[ IDX_RGB_FONT_GREEN		  ] = RGB( 0, 255, 0 );			//	폰트 색상				 : 녹색
	m_cfRGB[ IDX_RGB_FONT_BLUE		  ] = RGB( 0, 0, 255 );			//	폰트 색상				 : 파란색
	m_cfRGB[ IDX_RGB_FONT_GRAY        ] = RGB( 128, 128, 128 );		//	폰트 색상				 : 회색
	m_cfRGB[ IDX_RGB_FONT_GRAY2       ] = RGB( 166, 166, 166 );		//	폰트 색상				 : 회색2
	m_cfRGB[ IDX_RGB_FONT_GRAY3       ] = RGB(  66,  66,  66 );		//	폰트 색상				 : 회색3
	m_cfRGB[ IDX_RGB_FONT_GRAY4       ] = RGB( 198, 198, 198 );		//	폰트 색상				 : 회색4
	m_cfRGB[ IDX_RGB_FONT_LITE_BLUE   ] = RGB( 236, 246, 255 );		//	폰트 색상				 : 옅은 파란색
	m_cfRGB[ IDX_RGB_FONT_LITE_BLUE2  ] = RGB( 208, 219, 230 );		//	폰트 색상				 : 옅은 파란색2
	m_cfRGB[ IDX_RGB_FONT_LITE_GRAY   ] = RGB( 240, 240, 240 );		//	폰트 색상				 : 옅은회색
	m_cfRGB[ IDX_RGB_FONT_LITE_GRAY2  ] = RGB( 245, 245, 245 );		//	폰트 색상				 : 옅은회색2
	m_cfRGB[ IDX_RGB_FONT_LITE_GRAY3  ] = RGB( 244, 244, 244 );		//	폰트 색상				 : 옅은회색3

	//  get the function pointer for SetLayeredWindowAttributes in User32.dll
    HMODULE hUser32 = GetModuleHandle( _T("USER32.DLL") );
    SetLayeredWindowAttributes = (lpfn)GetProcAddress( hUser32, "SetLayeredWindowAttributes" );    
}


CGlobal::~CGlobal()
{
	DeleteBitmaps();
	DeleteFonts();
	DeleteIcons();
}


void CGlobal::DeleteBitmaps()
{
	UINT i;
	for( i = 0; i < IDX_PNG_MAX; i++ )
	{
		if( m_infoBitmap[i].hBitmap )
		{
			::DeleteObject( m_infoBitmap[ i ].hBitmap );
			m_infoBitmap[ i ].hBitmap = NULL;
		}

		::ZeroMemory( &m_infoBitmap[ i ].bitmap, sizeof(BITMAP) );
	}
}


void CGlobal::DeleteFonts()
{
	UINT i;
	for( i = 0; i < IDX_FONT_MAX; i++ )
	{
		if( m_pFont[ i ] ) 
		{
			m_pFont[ i ]->DeleteObject();
			delete m_pFont[ i ];
			m_pFont[ i ] = NULL;
		}
	}
}


void CGlobal::DeleteIcons()
{
	UINT i;
	for( i = 0; i < IDX_ICN_MAX; i++ )
	{
		for( int k = 0; k < 3; k++ )
		{
			if( m_hIcon[ i ][ k ] )
			{
				::DestroyIcon( m_hIcon[i][k] );
				m_hIcon[ i ][ k ] = NULL;
			}
		}
	}
}


CString CGlobal::GetModulePath()
{
	CString sPath;
	GetModuleFileName( AfxGetApp()->m_hInstance, sPath.GetBuffer( MAX_PATH ), MAX_PATH );
	sPath.ReleaseBuffer();

	int nPos = sPath.ReverseFind(_T('\\'));
	if( nPos != -1 )
		sPath = sPath.Left( nPos );

	return sPath;
}


void CGlobal::LoadBitmaps()
{
	DeleteBitmaps();

	CImage cPngImage;
	CString strFileCheck( _T("") );
	CString strFileName ( _T("") );
	CString sModulePath = GetModulePath() + _T("\\");

	UINT i;
	for( i = 0; i < IDX_PNG_MAX; i++ )
	{
		strFileName = GetBitmapFileName( i );
		
		if( strFileName.IsEmpty() )
			continue;

		// BMP 파일과 다른 형식의 파일을 구분해서 HBITMAP으로 올린다
		strFileCheck = strFileName.Right( strFileName.GetLength() -	strFileName.ReverseFind( '.' ) - 1 );
		strFileName = sModulePath + strFileName;

		if( strFileCheck.MakeUpper() == _T("BMP") )
		{			
			m_infoBitmap[i].hBitmap = (HBITMAP)::LoadImage( ::AfxGetInstanceHandle(), 
												(LPCTSTR)strFileName, 
												IMAGE_BITMAP, 
												0, 
												0, 
												LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE );
		}
		else
		{
			cPngImage.Load( strFileName );
			m_infoBitmap[ i ].hBitmap = cPngImage.Detach();
		}

		::GetObject( m_infoBitmap[ i ].hBitmap, sizeof(BITMAP), &m_infoBitmap[ i ].bitmap );
	}
}


CString CGlobal::GetBitmapFileName( UINT nBitmapID )
{
	return _T("");
	CString strFilePath, strFolderName; 
//	strFolderName = g_cfg.m_strENGINE_SKIN_PATH;

	switch( nBitmapID )
	{
	case IDX_PNG_CAPTION_LEFT					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("caption_left.png") );									break;
	case IDX_PNG_CAPTION_CENTER					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("caption_center.png") );								break;
	case IDX_PNG_CAPTION_RIGHT					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("caption_right.png") );									break;
	case IDX_PNG_FRAME_LEFT						:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("frame_left.png") );									break;
	case IDX_PNG_FRAME_LEFT_BOTTOM				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("frame_leftbottom.png") );								break;
	case IDX_PNG_FRAME_BOTTOM					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("frame_bottom.png") );									break;
	case IDX_PNG_FRAME_RIGHT_BOTTOM				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("frame_rightbottom.png") );								break;
	case IDX_PNG_FRAME_RIGHT					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("frame_right.png") );									break;
	case IDX_PNG_BOX_MINIMIZE					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_minimize.png") );									break;
	case IDX_PNG_BOX_MAXMIZE					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_maximize.png") );									break;
	case IDX_PNG_BOX_RESTORE					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_restore.png") );									break;
	case IDX_PNG_BOX_EXIT						:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_exit.png") );										break;
	case IDX_PNG_BOX_MINIMIZE_DOWN				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_minimize_down.png") );								break;
	case IDX_PNG_BOX_MAXMIZE_DOWN				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_maximize_down.png") );								break;
	case IDX_PNG_BOX_RESTORE_DOWN				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_restore_down.png") );								break;
	case IDX_PNG_BOX_EXIT_DOWN					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_exit_down.png") );									break;
	case IDX_PNG_BOX_MINIMIZE_OVER				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_minimize_over.png") );								break;
	case IDX_PNG_BOX_MAXMIZE_OVER				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_maximize_over.png") );								break;
	case IDX_PNG_BOX_RESTORE_OVER				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_restore_over.png") );								break;
	case IDX_PNG_BOX_EXIT_OVER					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_exit_over.png") );									break;
	case IDX_PNG_TAB_LEFT_ST					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_left_st.png") );									break;
	case IDX_PNG_TAB_CENTER_ST					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_center_st.png") );									break;
	case IDX_PNG_TAB_RIGHT_ST					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_right_st.png") );									break;
	case IDX_PNG_TAB_LEFT_NST					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_left_nst.png") );									break;
	case IDX_PNG_TAB_CENTER_NST					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_center_nst.png") );								break;
	case IDX_PNG_TAB_RIGHT_NST					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_right_nst.png") );									break;	
	case IDX_PNG_POPUP_CAPTION_LEFT				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("popup_caption_left.png") );							break;
	case IDX_PNG_POPUP_CAPTION_CENTER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("popup_caption_center.png") );							break;
	case IDX_PNG_POPUP_CAPTION_RIGHT			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("popup_caption_right.png") );							break;
	case IDX_PNG_POPUP_LEFT						:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("popup_left.png") );									break;
	case IDX_PNG_POPUP_LEFT_BOTTOM				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("popup_leftbottom.png") );								break;
	case IDX_PNG_POPUP_BOTTOM					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("popup_bottom.png") );									break;
	case IDX_PNG_POPUP_RIGHT_BOTTOM				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("popup_rightbottom.png") );								break;
	case IDX_PNG_POPUP_RIGHT					:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("popup_right.png") );									break;
	case IDX_PNG_STC_MSGBOX_ERROR				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("msgbox_error.png") );									break;
	case IDX_PNG_STC_MSGBOX_INFO				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("msgbox_info.png") );									break;
	case IDX_PNG_STC_MSGBOX_QUESTION			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("msgbox_question.png") );								break;
	case IDX_PNG_STC_MSGBOX_WARNING				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("msgbox_warning.png") );								break;	
	case IDX_PNG_BTN_MSGBOX						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_msgbox.png") );									break;
	case IDX_PNG_BTN_MSGBOX_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_msgbox_down.png") );								break;
	case IDX_PNG_BTN_MSGBOX_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_msgbox_over.png") );								break;
	case IDX_PNG_CMB_LEFT						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("combo_left.png") );									break;
	case IDX_PNG_CMB_TOP						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("combo_width.png") );									break;
	case IDX_PNG_CMB_BOTTOM						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("combo_width.png") );									break;
	case IDX_PNG_CMB_BUTTON						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("combo_btn.png") );										break;
	case IDX_PNG_BTN_SEARCH						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("search_btn.png") );									break;
	case IDX_PNG_BTN_SEARCH_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("search_btn_down.png") );								break;
	case IDX_PNG_BTN_SEARCH_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("search_btn_over.png") );								break;
	case IDX_PNG_STC_KEPCO						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("kepco_logo.png") );									break;
	case IDX_PNG_BTN_CONFIG						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_config.png") );									break;
	case IDX_PNG_BTN_CONFIG_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_config_down.png") );								break;
	case IDX_PNG_BTN_CONFIG_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_config_over.png") );								break;
	case IDX_PNG_BTN_INIT						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_init.png") );										break;
	case IDX_PNG_BTN_INIT_DOWN					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_init_down.png") );									break;
	case IDX_PNG_BTN_INIT_OVER					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_init_over.png") );									break;
	case IDX_PNG_BTN_BUILDER					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_builder.png") );									break;
	case IDX_PNG_BTN_BUILDER_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_builder_down.png") );								break;
	case IDX_PNG_BTN_BUILDER_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_builder_over.png") );								break;
	case IDX_PNG_BTN_RTUSEARCH					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_rtusearch.png") );									break;
	case IDX_PNG_BTN_RTUSEARCH_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_rtusearch_down.png") );							break;
	case IDX_PNG_BTN_RTUSEARCH_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_rtusearch_over.png") );							break;
	case IDX_PNG_BTN_PRINT_SC					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_print_sc.png") );									break;
	case IDX_PNG_BTN_PRINT_SC_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_print_sc_down.png") );								break;
	case IDX_PNG_BTN_PRINT_SC_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_print_sc_over.png") );								break;
	case IDX_PNG_BTN_PRINT_FULL					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_print_full.png") );								break;
	case IDX_PNG_BTN_PRINT_FULL_DOWN			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_print_full_down.png") );							break;
	case IDX_PNG_BTN_PRINT_FULL_OVER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_print_full_over.png") );							break;
	case IDX_PNG_BTN_EXCEL						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_excel.png") );										break;
	case IDX_PNG_BTN_EXCEL_DOWN					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_excel_down.png") );								break;
	case IDX_PNG_BTN_EXCEL_OVER					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_excel_over.png") );								break;
	case IDX_PNG_BTN_PRINT_SETUP				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_print_setup.png") );								break;
	case IDX_PNG_BTN_PRINT_SETUP_DOWN			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_print_setup_down.png") );							break;
	case IDX_PNG_BTN_PRINT_SETUP_OVER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_print_setup_over.png") );							break;
	case IDX_PNG_BTN_USER_CHANGE				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_user_change.png") );								break;
	case IDX_PNG_BTN_USER_CHANGE_DOWN			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_user_change_down.png") );							break;
	case IDX_PNG_BTN_USER_CHANGE_OVER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_user_change_over.png") );							break;
	case IDX_PNG_BTN_USER_MODIFY				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_user_modify.png") );								break;
	case IDX_PNG_BTN_USER_MODIFY_DOWN			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_user_modify_down.png") );							break;
	case IDX_PNG_BTN_USER_MODIFY_OVER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_user_modify_over.png") );							break;
	case IDX_PNG_BTN_USER_MESSAGE				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_user_message.png") );								break;
	case IDX_PNG_BTN_USER_MESSAGE_DOWN			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_user_message_down.png") );							break;
	case IDX_PNG_BTN_USER_MESSAGE_OVER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_user_message_over.png") );							break;	
	case IDX_PNG_BTN_FI_LIST					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_fi_list.png") );									break;
	case IDX_PNG_BTN_FI_LIST_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_fi_list_down.png") );								break;
	case IDX_PNG_BTN_FI_LIST_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_fi_list_over.png") );								break;	
	case IDX_PNG_CMB_CENTER						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("combo_center.png") );									break;
	case IDX_PNG_LOGIN_BASE						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("login_base.png") );									break;
	case IDX_PNG_BTN_LOGIN						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_login.png") );										break;
	case IDX_PNG_BTN_LOGIN_DOWN					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_login_down.png") );								break;
	case IDX_PNG_BTN_LOGIN_OVER					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_login_over.png") );								break;	
	case IDX_PNG_LISTCTRL_HEADER_DIVISION		:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("listctrl_header_division.png") );						break;
	case IDX_PNG_LISTCTRL_HEADER_SHADOW			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("listctrl_header_shadow.png") );						break;
	case IDX_PNG_STC_MENUBAR					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_menubar.png") );									break;	
	case IDX_PNG_BTN_MENUBAR1					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar1.png") );									break;
	case IDX_PNG_BTN_MENUBAR1_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar1_down.png") );								break;
	case IDX_PNG_BTN_MENUBAR1_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar1_over.png") );								break;
	case IDX_PNG_BTN_MENUBAR2					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar2.png") );									break;
	case IDX_PNG_BTN_MENUBAR2_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar2_down.png") );								break;
	case IDX_PNG_BTN_MENUBAR2_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar2_over.png") );								break;
	case IDX_PNG_BTN_MENUBAR3					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar13.png") );									break;
	case IDX_PNG_BTN_MENUBAR3_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar13_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR3_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar13_over.png") );							break;
	case IDX_PNG_BTN_MENUBAR4					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar14.png") );									break;
	case IDX_PNG_BTN_MENUBAR4_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar14_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR4_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar14_over.png") );							break;
	case IDX_PNG_BTN_MENUBAR5					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar3.png") );									break;
	case IDX_PNG_BTN_MENUBAR5_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar3_down.png") );								break;
	case IDX_PNG_BTN_MENUBAR5_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar3_over.png") );								break;
	case IDX_PNG_BTN_MENUBAR6					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar4.png") );									break;
	case IDX_PNG_BTN_MENUBAR6_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar4_down.png") );								break;
	case IDX_PNG_BTN_MENUBAR6_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar4_over.png") );								break;
	case IDX_PNG_BTN_MENUBAR7					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar8.png") );									break;
	case IDX_PNG_BTN_MENUBAR7_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar8_down.png") );								break;
	case IDX_PNG_BTN_MENUBAR7_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar8_over.png") );								break;
	case IDX_PNG_BTN_MENUBAR8					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar9.png") );									break;
	case IDX_PNG_BTN_MENUBAR8_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar9_down.png") );								break;
	case IDX_PNG_BTN_MENUBAR8_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar9_over.png") );								break;	
	case IDX_PNG_BTN_MENUBAR9					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar10.png") );									break;
	case IDX_PNG_BTN_MENUBAR9_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar10_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR9_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar10_over.png") );							break;
	case IDX_PNG_BTN_MENUBAR10					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar11.png") );									break;
	case IDX_PNG_BTN_MENUBAR10_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar11_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR10_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar11_over.png") );							break;
	case IDX_PNG_BTN_MENUBAR11					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar15.png") );									break;
	case IDX_PNG_BTN_MENUBAR11_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar15_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR11_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar15_over.png") );							break;
	case IDX_PNG_BTN_MENUBAR12					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar16.png") );									break;
	case IDX_PNG_BTN_MENUBAR12_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar16_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR12_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar16_over.png") );							break;
	case IDX_PNG_BTN_MENUBAR13					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar17.png") );									break;
	case IDX_PNG_BTN_MENUBAR13_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar17_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR13_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar17_over.png") );							break;
	case IDX_PNG_BTN_MENUBAR14					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar18.png") );									break;
	case IDX_PNG_BTN_MENUBAR14_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar18_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR14_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar18_over.png") );							break;
	case IDX_PNG_BTN_MENUBAR15					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar22.png") );									break;
	case IDX_PNG_BTN_MENUBAR15_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar22_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR15_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar22_over.png") );							break;	
	case IDX_PNG_CHK_DEFAULT					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("chk_default.png") );									break;
	case IDX_PNG_CHK_CHECKED					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("chk_checked.png") );									break;
	case IDX_PNG_CHK_DISABLE					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("chk_disable.png") );									break;
	case IDX_PNG_RAD_DEFAULT					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("rad_default.png") );									break;
	case IDX_PNG_RAD_CHECKED					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("rad_checked.png") );									break;
	case IDX_PNG_RAD_DISABLE					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("rad_disable.png") );									break;
	case IDX_PNG_BTN_POPUP_OK					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_popup_ok.png") );									break;
	case IDX_PNG_BTN_POPUP_OK_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_popup_ok_down.png") );								break;
	case IDX_PNG_BTN_POPUP_OK_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_popup_ok_over.png") );								break;	
	case IDX_PNG_BTN_POPUP_CANCEL				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_popup_cancel.png") );								break;
	case IDX_PNG_BTN_POPUP_CANCEL_DOWN			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_popup_cancel_down.png") );							break;
	case IDX_PNG_BTN_POPUP_CANCEL_OVER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_popup_cancel_over.png") );							break;
	case IDX_PNG_STC_POPUP_TOP_LEFT				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_popup_top_left.png") );							break;
	case IDX_PNG_STC_POPUP_TOP_CENTER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_popup_top_center.png") );							break;
	case IDX_PNG_STC_POPUP_TOP_RIGHT			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_popup_top_right.png") );							break;
	case IDX_PNG_STC_POPUP_LEFT					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_popup_left.png") );								break;
	case IDX_PNG_STC_POPUP_RIGHT				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_popup_right.png") );								break;
	case IDX_PNG_STC_POPUP_BOTTOM_LEFT			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_popup_bottom_left.png") );							break;
	case IDX_PNG_STC_POPUP_BOTTOM_CENTER		:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_popup_bottom_center.png") );						break;
	case IDX_PNG_STC_POPUP_BOTTOM_RIGHT			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_popup_bottom_right.png") );						break;	
	case IDX_PNG_TAB_SMALL_LEFT_ST				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_small_left_st.png") );								break;
	case IDX_PNG_TAB_SMALL_CENTER_ST			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_small_center_st.png") );							break;
	case IDX_PNG_TAB_SMALL_RIGHT_ST				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_small_right_st.png") );							break;
	case IDX_PNG_TAB_SMALL_LEFT_NST				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_small_left_nst.png") );							break;
	case IDX_PNG_TAB_SMALL_CENTER_NST			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_small_center_nst.png") );							break;
	case IDX_PNG_TAB_SMALL_RIGHT_NST			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_small_right_nst.png") );							break;
	case IDX_PNG_STC_SEPARATOR					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_separator.png") );									break;
	case IDX_PNG_BTN_SEARCH2					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_search2.png") );									break;
	case IDX_PNG_BTN_SEARCH2_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_search2_down.png") );								break;
	case IDX_PNG_BTN_SEARCH2_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_search2_over.png") );								break;
	case IDX_PNG_TAB_INFO_LEFT_ST				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_info_left_st.png") );								break;
	case IDX_PNG_TAB_INFO_CENTER_ST				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_info_center_st.png") );							break;
	case IDX_PNG_TAB_INFO_RIGHT_ST				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_info_right_st.png") );								break;
	case IDX_PNG_TAB_INFO_LEFT_NST				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_info_left_nst.png") );								break;
	case IDX_PNG_TAB_INFO_CENTER_NST			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_info_center_nst.png") );							break;
	case IDX_PNG_TAB_INFO_RIGHT_NST				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_info_right_nst.png") );							break;
	case IDX_PNG_BTN_CTL_SET					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_ctl_set.png") );									break;
	case IDX_PNG_BTN_CTL_SET_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_ctl_set_down.png") );								break;
	case IDX_PNG_BTN_CTL_SET_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_ctl_set_over.png") );								break;
	case IDX_PNG_BTN_CTL_CLEAR					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_ctl_clear.png") );									break;
	case IDX_PNG_BTN_CTL_CLEAR_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_ctl_clear_down.png") );							break;
	case IDX_PNG_BTN_CTL_CLEAR_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_ctl_clear_over.png") );							break;
	case IDX_PNG_TREE_LEFT						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tree_left.png") );										break;
	case IDX_PNG_TREE_TOP						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tree_top.png") );										break;
	case IDX_PNG_TREE_RIGHT						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tree_right.png") );									break;
	case IDX_PNG_TREE_BOTTOM					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tree_bottom.png") );									break;	
	case IDX_PNG_TREE_IMAGES					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tree_images.png") );									break;	
	case IDX_PNG_BTN_RELOGIN					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_relogin.png") );									break;	
	case IDX_PNG_BTN_RELOGIN_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_relogin_down.png") );								break;
	case IDX_PNG_BTN_RELOGIN_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_relogin_over.png") );								break;
	case IDX_PNG_TAB_RIGHT_ST_CLOSE				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_right_st_close.png") );							break;
	case IDX_PNG_TAB_RIGHT_ST_CLOSE_DOWN		:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_right_st_close_down.png") );						break;
	case IDX_PNG_TAB_RIGHT_ST_CLOSE_OVER		:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_right_st_close_over.png") );						break;
	case IDX_PNG_TAB_RIGHT_NST_CLOSE			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_right_nst_close.png") );							break;
	case IDX_PNG_TAB_RIGHT_NST_CLOSE_DOWN		:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_right_nst_close_down.png") );						break;
	case IDX_PNG_TAB_RIGHT_NST_CLOSE_OVER		:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("tab_right_nst_close_over.png") );						break;
	case IDX_PNG_STC_SUBTITLE					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("Totalinfo_stc_system_condition_menubar3.png") );		break;
	case IDX_PNG_STC_SUBTITLE_LEFT				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_subtitle_left.png") );								break;
	case IDX_PNG_STC_SUBTITLE_CENTER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_subtitle_center.png") );							break;
	case IDX_PNG_STC_SUBTITLE_RIGHT				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_subtitle_right.png") );							break;
	case IDX_PNG_STC_DATA_LEFT					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_data_left.png") );									break;
	case IDX_PNG_STC_DATA_CENTER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_data_center.png") );								break;
	case IDX_PNG_STC_DATA_RIGHT					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_data_right.png") );								break;
	case IDX_PNG_STC_DATA_SUB					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_data_sub.png") );									break;
	case IDX_PNG_PRS_BATTERY_BK					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("prs_battery_bk.png") );								break;
	case IDX_PNG_PRS_BATTERY_GREEN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("prs_battery_green.png") );								break;
	case IDX_PNG_STC_DATA_ARROW					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_data_arrow.png") );								break;
	case IDX_PNG_STC_DATA_CONTROL_ON			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_data_control_on.png") );							break;
	case IDX_PNG_STC_DATA_CONTROL_OFF			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_data_control_off.png") );							break;
	case IDX_PNG_BTN_DATA_CONTROL				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_data_control.png") );								break;
	case IDX_PNG_BTN_DATA_CONTROL_DOWN			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_data_control_down.png") );							break;
	case IDX_PNG_BTN_DATA_CONTROL_OVER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_data_control_over.png") );							break;
	case IDX_PNG_STC_MOVE_TAB					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_move_tab.png") );								    break;	
	case IDX_PNG_BOX_RESTORE_TAB				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_restore_tab.png") );								break;
	case IDX_PNG_BOX_RESTORE_TAB_DOWN			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_restore_tab_down.png") );							break;
	case IDX_PNG_BOX_RESTORE_TAB_OVER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("box_restore_tab_over.png") );							break;
	case IDX_PNG_PRS_PROGRESSBAR				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_progressbar.png") );								break;
	case IDX_PNG_PRS_PROGRESSBAR_RED			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_progressbar_red.png") );							break;
	case IDX_PNG_PRS_PROGRESSBAR_GREEN			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_progressbar_green.png") );							break;
	case IDX_PNG_PRS_PROGRESSBAR_ORANGE			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_progressbar_orange.png") );						break;
	case IDX_PNG_PRS_WHITE_PROGRESSBAR			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_white_progressbar.png") );							break;
	case IDX_PNG_PRS_WHITE_PROGRESSBAR_GREEN	:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_white_progressbar_green.png") );					break;
	case IDX_PNG_BTN_MENUBAR20					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar20.png") );									break;
	case IDX_PNG_BTN_MENUBAR20_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar20_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR20_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar20_over.png") );							break;
	
	case IDX_PNG_STC_POINT_INFO				    :   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_point_info.png") );								break;
	case IDX_PNG_STC_POINT_SEPARATOR			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_point_separator.png") );							break;
	case IDX_PNG_STC_USER_INFO					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_user_info.png") );									break;
	case IDX_PNG_PRS_PROGRESSBAR_CTRL			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_progressbar_ctrl.png") );							break;
	case IDX_PNG_PRS_PROGRESSBAR_CTRL_BLUE		:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_progressbar_ctrl_blue.png") );						break;
	case IDX_PNG_STC_POINT_RED					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_point_red.png") );									break;
	case IDX_PNG_STC_POINT_BLUE					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_point_blue.png") );								break;
	case IDX_PNG_STC_POINT_YELLOW				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_point_yellow.png") );								break;
	case IDX_PNG_STC_POINT_GREEN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_point_green.png") );								break;
	case IDX_PNG_STC_POINT_ARROW				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_point_arrow.png") );								break;
	case IDX_PNG_STC_POINT_DESC					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_point_desc.png") );								break;							
	case IDX_PNG_STC_POINT_CURRENT_VAL			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_point_current_val.png") );							break;
	case IDX_PNG_STC_POINT_INPUT_VAL			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("stc_point_input_val.png") );							break;

	case IDX_PNG_BTN_MENUBAR23					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar23.png") );									break;
	case IDX_PNG_BTN_MENUBAR23_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar23_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR23_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar23_over.png") );							break;

	case IDX_PNG_BTN_MENUBAR24					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar24.png") );									break;
	case IDX_PNG_BTN_MENUBAR24_DOWN				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar24_down.png") );							break;
	case IDX_PNG_BTN_MENUBAR24_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_menubar24_over.png") );							break;

	case IDX_PNG_ALARAM_ON					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goAlarm_On.png") );									break;
	case IDX_PNG_ALARAM_ON_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goAlarm_On_Over.png") );							break;
	case IDX_PNG_ALARAM_OUT					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goAlarm_Out.png") );								break;
	case IDX_PNG_ALARAM_OUT_OVER			:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goAlarm_Out_Over.png") );							break;
	case IDX_PNG_ALARAM_CLICK				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goAlarm_Click.png") );								break;
	case IDX_PNG_DATA_ON					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goAcmData_On.png") );								break;
	case IDX_PNG_DATA_ON_OVER			    :   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goAcmData_On_Over.png") );							break;
	case IDX_PNG_DATA_OUT				    :   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goAcmData_Out.png") );								break;
	case IDX_PNG_DATA_OUT_OVER			    :   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goAcmData_Out_Over.png") );							break;
	case IDX_PNG_DATA_CLICK					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goAcmData_Click.png") );							break;
	case IDX_PNG_DMS_ON						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goDMS_On.png") );									break;
	case IDX_PNG_DMS_ON_OVER				:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goDMS_On_Over.png") );								break;
	case IDX_PNG_DMS_OUT					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goDMS_Out.png") );									break;
	case IDX_PNG_DMS_OUT_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goDMS_Out_Over.png") );								break;
	case IDX_PNG_DMS_CLICK					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goDMS_Click.png") );								break;
	case IDX_PNG_MG_ON						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goMG_On.png") );									break;
	case IDX_PNG_MG_ON_OVER					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goMG_On_Over.png") );								break;
	case IDX_PNG_MG_OUT						:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goMG_Out.png") );									break;
	case IDX_PNG_MG_OUT_OVER			    :   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goMG_Out_Over.png") );								break;
	case IDX_PNG_MG_CLICK				    :   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goMG_Click.png") );									break;
	case IDX_PNG_TOOLS_ON					:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goTools_On.png") );									break;
	case IDX_PNG_TOOLS_ON_OVER				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goTools_On_Over.png") );							break;
	case IDX_PNG_TOOLS_CLICK				:   strFilePath.Format( _T("%s\\%s"), strFolderName, _T("btn_goTools_Click.png") );								break;

	}

	return strFilePath;
}


void CGlobal::LoadIcons()
{
	DeleteIcons();

	CString strFileName(_T(""));
	CString sModulePath = GetModulePath() + _T("\\");

	UINT i;
	for( i = 0; i < IDX_ICN_MAX; i++ )
	{
		strFileName = GetIconFileName( i );
		
		if( strFileName.IsEmpty() )
			continue;
		
		strFileName = sModulePath + strFileName;

		m_hIcon[ i ][ 0 ] = (HICON)::LoadImage( ::AfxGetInstanceHandle(), strFileName, IMAGE_ICON, 16, 16, LR_LOADFROMFILE );
		m_hIcon[ i ][ 1 ] = (HICON)::LoadImage( ::AfxGetInstanceHandle(), strFileName, IMAGE_ICON, 24, 24, LR_LOADFROMFILE );
		m_hIcon[ i ][ 2 ] = (HICON)::LoadImage( ::AfxGetInstanceHandle(), strFileName, IMAGE_ICON, 32, 32, LR_LOADFROMFILE );
	}
}


void CGlobal::LoadFonts( CString strFaceName )
{
	DeleteFonts();

	UINT i, uSize;
	for( i = 0; i < IDX_FONT_MAX; i++ )
	{
		if		( i == IDX_FONT_SIZE_8  )	uSize =  8;
		else if	( i == IDX_FONT_SIZE_10 )	uSize = 10;
		else if	( i == IDX_FONT_SIZE_12 )	uSize = 12;
		else if	( i == IDX_FONT_SIZE_14 )	uSize = 14;
		else if	( i == IDX_FONT_SIZE_16 )	uSize = 16;
		else if	( i == IDX_FONT_SIZE_18 )	uSize = 18;
		else if	( i == IDX_FONT_SIZE_20 )	uSize = 20;
		else								uSize = 10;

		SetFont( i, strFaceName, uSize, FALSE );
	}
}


CString CGlobal::GetIconFileName( UINT nIconID )
{
	return _T("");
	CString strFilePath, strFolderName; 
//	strFolderName = g_cfg.m_strENGINE_SKIN_PATH;

	switch( nIconID )
	{
	case IDX_ICON_SKIN		:	strFilePath.Format( _T("%s\\%s"), strFolderName, _T("argos.ico") );		break;
	}

	return strFilePath;
}


SIZE CGlobal::GetBitmapSize( UINT nBitmapID )
{
	SIZE size;
	
	if( nBitmapID >= IDX_PNG_MAX )
	{
		size.cx = 0;
		size.cy = 0;
		return size;
	}

	size.cx = m_infoBitmap[ nBitmapID ].bitmap.bmWidth;
	size.cy = m_infoBitmap[ nBitmapID ].bitmap.bmHeight;
	return size;
}


HBITMAP CGlobal::GetBitmap( UINT nBitmapID )
{
	if( nBitmapID >= IDX_PNG_MAX )
		return NULL;

	return m_infoBitmap[ nBitmapID ].hBitmap;
}


HICON CGlobal::GetIcon( UINT nIconID, UINT nType )
{
	if( nIconID >= IDX_ICN_MAX || nType > ICON32 )
		return NULL;

	return m_hIcon[ nIconID ][ nType ];
}


COLORREF CGlobal::GetRGB( UINT nRGBID )
{
	if( nRGBID >= IDX_RGB_MAX )
		return RGB( 0, 0, 0 );

	return m_cfRGB[ nRGBID ];
}


CFont * CGlobal::GetFont( UINT nFontID ) 
{ 
	if( nFontID >= IDX_FONT_MAX )
		return NULL;

	return m_pFont[ nFontID ]; 
}


CFont * CGlobal::SetFont( UINT nFontID, CString strFaceName, UINT nFontSize, BOOL bBold/*=FALSE*/ )
{	
	if( nFontID >= IDX_FONT_MAX )
		return NULL;

	CWnd *pMain = AfxGetMainWnd();
	
	if( !pMain )
		return NULL;

	// Font Name
	LOGFONT logFont;
	ZeroMemory( &logFont, sizeof(logFont) );
	_tcscpy_s( logFont.lfFaceName, strFaceName );

	// Font Style
	logFont.lfItalic = FALSE;
	
	if( bBold )
		logFont.lfWeight = FW_BOLD;
	else
		logFont.lfWeight = FW_NORMAL;

	// Font Size
	HDC hdc = ::GetDC( pMain->m_hWnd );	
	
	if( !hdc ) 
		logFont.lfHeight = nFontSize;
	else 
		logFont.lfHeight = -MulDiv( nFontSize, GetDeviceCaps( hdc, LOGPIXELSY ), 72 );
	
	::ReleaseDC( pMain->m_hWnd, hdc );

	// New Font
	if( m_pFont[ nFontID ] ) 
	{
		m_pFont[ nFontID ]->DeleteObject();
		delete m_pFont[ nFontID ];
		m_pFont[ nFontID ] = NULL;
	}

	m_pFont[ nFontID ] = (CFont *)new CFont;

	if( !m_pFont[ nFontID ]->CreateFontIndirect( &logFont ) )
	{
		delete m_pFont[ nFontID ];
		m_pFont[ nFontID ] = NULL;
	}

	return m_pFont[ nFontID ];
}


COLORREF CGlobal::Darker( COLORREF crBase, float fFactor )
{
	ASSERT ( fFactor < 1.0f && fFactor > 0.0f );

	fFactor = min( fFactor, 1.0f );
	fFactor = max( fFactor, 0.0f );

	BYTE bRed, bBlue, bGreen;
	BYTE bRedShadow, bBlueShadow, bGreenShadow;

	bRed = GetRValue(crBase);
	bBlue = GetBValue(crBase);
	bGreen = GetGValue(crBase);

	bRedShadow = (BYTE)(bRed * fFactor);
	bBlueShadow = (BYTE)(bBlue * fFactor);
	bGreenShadow = (BYTE)(bGreen * fFactor);

	return RGB( bRedShadow, bGreenShadow, bBlueShadow );
}

COLORREF CGlobal::Lighter( COLORREF crBase, float fFactor ) 
{
	ASSERT (fFactor > 1.0f);

	fFactor = max( fFactor, 1.0f );

	BYTE bRed, bBlue, bGreen;
	BYTE bRedHilite, bBlueHilite, bGreenHilite;

	bRed = GetRValue(crBase);
	bBlue = GetBValue(crBase);
	bGreen = GetGValue(crBase);

	bRedHilite = (BYTE)min((int)(bRed * fFactor), 255);
	bBlueHilite = (BYTE)min((int)(bBlue * fFactor), 255);
	bGreenHilite = (BYTE)min((int)(bGreen * fFactor), 255);

	return RGB( bRedHilite, bGreenHilite, bBlueHilite );
}