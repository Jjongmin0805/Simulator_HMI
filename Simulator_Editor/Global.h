// Global.h: interface for the CGlobal class.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GLOBAL_H
#define _GLOBAL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////////////////////////
//	PNG SKIN DEFINE
/////////////////////////////////////////////////////////////////////////////////////////////////

#define IDX_PNG_CAPTION_LEFT					 0		//	윈도우 캡션 왼쪽
#define IDX_PNG_CAPTION_CENTER					 1		//	윈도우 캡션 중앙
#define IDX_PNG_CAPTION_RIGHT					 2		//	윈도우 캡션 오른쪽
#define IDX_PNG_FRAME_LEFT						 3		//	윈도우 프레임 왼쪽
#define IDX_PNG_FRAME_LEFT_BOTTOM				 4		//	윈도우 프레임 왼쪽아래
#define IDX_PNG_FRAME_BOTTOM					 5		//	윈도우 프레임 아래
#define IDX_PNG_FRAME_RIGHT_BOTTOM				 6		//	윈도우 프레임 오른쪽아래
#define IDX_PNG_FRAME_RIGHT						 7		//	윈도우 프레임 오른쪽
#define IDX_PNG_BOX_MINIMIZE					 8		//	윈도우 프레임 최소화버튼
#define IDX_PNG_BOX_MAXMIZE						 9		//	윈도우 프레임 최대화버튼
#define IDX_PNG_BOX_RESTORE						10		//	윈도우 프레임 복귀버튼
#define IDX_PNG_BOX_EXIT						11		//	윈도우 프레임 종료버튼
#define IDX_PNG_BOX_MINIMIZE_DOWN				12		//	윈도우 프레임 최소화버튼 클릭
#define IDX_PNG_BOX_MAXMIZE_DOWN				13		//	윈도우 프레임 최대화버튼 클릭
#define IDX_PNG_BOX_RESTORE_DOWN				14		//	윈도우 프레임 복귀버튼 클릭
#define IDX_PNG_BOX_EXIT_DOWN					15		//	윈도우 프레임 종료버튼 클릭
#define IDX_PNG_BOX_MINIMIZE_OVER				16		//	윈도우 프레임 최소화버튼 마우스오버
#define IDX_PNG_BOX_MAXMIZE_OVER				17		//	윈도우 프레임 최대화버튼 마우스오버
#define IDX_PNG_BOX_RESTORE_OVER				18		//	윈도우 프레임 복귀버튼 마우스오버
#define IDX_PNG_BOX_EXIT_OVER					19		//	윈도우 프레임 종료버튼 마우스오버
#define IDX_PNG_TAB_LEFT_ST						20		//  선택된 TAB 왼쪽
#define IDX_PNG_TAB_CENTER_ST					21		//  선택된 TAB 중앙
#define IDX_PNG_TAB_RIGHT_ST					22		//  선택된 TAB 오른쪽
#define IDX_PNG_TAB_LEFT_NST					23		//  선택안된 TAB 왼쪽
#define IDX_PNG_TAB_CENTER_NST					24		//  선택안된 TAB 중앙
#define IDX_PNG_TAB_RIGHT_NST					25		//  선택안된 TAB 오른쪽
#define IDX_PNG_POPUP_CAPTION_LEFT				26		//	팝업윈도우 캡션 왼쪽
#define IDX_PNG_POPUP_CAPTION_CENTER			27		//	팝업윈도우 캡션 중앙
#define IDX_PNG_POPUP_CAPTION_RIGHT				28		//	팝업윈도우 캡션 오른쪽
#define IDX_PNG_POPUP_LEFT						29		//	팝업윈도우 프레임 왼쪽
#define IDX_PNG_POPUP_LEFT_BOTTOM				30		//	팝업윈도우 프레임 왼쪽아래
#define IDX_PNG_POPUP_BOTTOM					31		//	팝업윈도우 프레임 아래
#define IDX_PNG_POPUP_RIGHT_BOTTOM				32		//	팝업윈도우 프레임 오른쪽아래
#define IDX_PNG_POPUP_RIGHT						33		//	팝업윈도우 프레임 오른쪽
#define IDX_PNG_STC_MSGBOX_ERROR				34		//  메세지박스 에러
#define IDX_PNG_STC_MSGBOX_INFO					35		//  메세지박스 정보
#define IDX_PNG_STC_MSGBOX_QUESTION				36		//  메세지박스 물음
#define IDX_PNG_STC_MSGBOX_WARNING				37		//  메세지박스 경고
#define IDX_PNG_BTN_MSGBOX						38		//  메세지박스 버튼
#define IDX_PNG_BTN_MSGBOX_DOWN					39		//  메세지박스 버튼 클릭
#define IDX_PNG_BTN_MSGBOX_OVER					40		//  메세지박스 버튼 마우스오버
#define IDX_PNG_CMB_LEFT						41		//  콤보박스 캡션 왼쪽
#define IDX_PNG_CMB_TOP							42		//  콤보박스 캡션 위쪽
#define IDX_PNG_CMB_BOTTOM						43		//  콤보박스 캡션 아래쪽
#define IDX_PNG_CMB_BUTTON						44		//  콤보박스 캡션 버튼
#define IDX_PNG_BTN_SEARCH						45		//  검색 버튼
#define IDX_PNG_BTN_SEARCH_DOWN					46		//  검색 버튼 클릭
#define IDX_PNG_BTN_SEARCH_OVER					47		//  검색 버튼 마우스오버
#define IDX_PNG_STC_KEPCO						48		//  KEPCO 로고
#define IDX_PNG_BTN_CONFIG						49		//  환경설정 버튼
#define IDX_PNG_BTN_CONFIG_DOWN					50		//  환경설정 버튼 클릭
#define IDX_PNG_BTN_CONFIG_OVER					51		//  환경설정 버튼 마우스오버
#define IDX_PNG_BTN_INIT						52		//  초기화 버튼
#define IDX_PNG_BTN_INIT_DOWN					53		//  초기화 버튼 클릭
#define IDX_PNG_BTN_INIT_OVER					54		//  초기화 버튼 마우스오버
#define IDX_PNG_BTN_BUILDER						55		//  빌더실행 버튼
#define IDX_PNG_BTN_BUILDER_DOWN				56		//  빌더실행 버튼 클릭
#define IDX_PNG_BTN_BUILDER_OVER				57		//  빌더실행 버튼 마우스오버
#define IDX_PNG_BTN_RTUSEARCH					58		//  설비검색 버튼
#define IDX_PNG_BTN_RTUSEARCH_DOWN				59		//  설비검색 버튼 클릭
#define IDX_PNG_BTN_RTUSEARCH_OVER				60		//  설비검색 버튼 마우스오버
#define IDX_PNG_BTN_PRINT_SC					61		//  화면인쇄 버튼
#define IDX_PNG_BTN_PRINT_SC_DOWN				62		//  화면인쇄 버튼 클릭
#define IDX_PNG_BTN_PRINT_SC_OVER				63		//  화면인쇄 버튼 마우스오버
#define IDX_PNG_BTN_PRINT_FULL					64		//  전체인쇄 버튼
#define IDX_PNG_BTN_PRINT_FULL_DOWN				65		//  전체인쇄 버튼 클릭
#define IDX_PNG_BTN_PRINT_FULL_OVER				66		//  전체인쇄 버튼 마우스오버
#define IDX_PNG_BTN_EXCEL						67		//  엑셀변환 버튼
#define IDX_PNG_BTN_EXCEL_DOWN					68		//  엑셀변환 버튼 클릭
#define IDX_PNG_BTN_EXCEL_OVER					69		//  엑셀변환 버튼 마우스오버
#define IDX_PNG_BTN_PRINT_SETUP					70		//  인쇄설정 버튼
#define IDX_PNG_BTN_PRINT_SETUP_DOWN			71		//  인쇄설정 버튼 클릭
#define IDX_PNG_BTN_PRINT_SETUP_OVER			72		//  인쇄설정 버튼 마우스오버
#define IDX_PNG_BTN_USER_CHANGE					73		//  사용자변경 버튼
#define IDX_PNG_BTN_USER_CHANGE_DOWN			74		//  사용자변경 버튼 클릭
#define IDX_PNG_BTN_USER_CHANGE_OVER			75		//  사용자변경 버튼 마우스오버
#define IDX_PNG_BTN_USER_MODIFY					76		//  사용자관리 버튼
#define IDX_PNG_BTN_USER_MODIFY_DOWN			77		//  사용자관리 버튼 클릭
#define IDX_PNG_BTN_USER_MODIFY_OVER			78		//  사용자관리 버튼 마우스오버
#define IDX_PNG_BTN_USER_MESSAGE				79		//  작업메세지 버튼
#define IDX_PNG_BTN_USER_MESSAGE_DOWN			80		//  작업메세지 버튼 클릭
#define IDX_PNG_BTN_USER_MESSAGE_OVER			81		//  작업메세지 버튼 마우스오버
#define IDX_PNG_BTN_FI_LIST						82		//  FI목록 버튼
#define IDX_PNG_BTN_FI_LIST_DOWN				83		//  FI목록 버튼 클릭
#define IDX_PNG_BTN_FI_LIST_OVER				84		//  FI목록 버튼 마우스오버
#define IDX_PNG_CMB_CENTER						85		//  콤보박스 캡션 가운데
#define IDX_PNG_LOGIN_BASE						86		//  로그인 배경 이미지
#define IDX_PNG_BTN_LOGIN						87		//  로그인 버튼
#define IDX_PNG_BTN_LOGIN_DOWN					88		//  로그인 버튼 클릭
#define IDX_PNG_BTN_LOGIN_OVER					89		//  로그인 버튼 마우스오버
#define IDX_PNG_LISTCTRL_HEADER_DIVISION		90		//  리스트컨트롤 헤더 구분자
#define IDX_PNG_LISTCTRL_HEADER_SHADOW			91		//  리스트컨트롤 헤더 밑부분
#define IDX_PNG_STC_MENUBAR						92		//  계통도 메뉴바 배경
#define IDX_PNG_BTN_MENUBAR1					93		//  확대 메뉴버튼
#define IDX_PNG_BTN_MENUBAR1_DOWN				94		//  확대 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR1_OVER				95		//  확대 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR2					96		//  축소 메뉴버튼
#define IDX_PNG_BTN_MENUBAR2_DOWN				97		//  축소 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR2_OVER				98		//  축소 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR3					99		//  확대x2 메뉴버튼
#define IDX_PNG_BTN_MENUBAR3_DOWN			   100		//  확대x2 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR3_OVER			   101		//  확대x2 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR4				   102		//  축소x2 메뉴버튼
#define IDX_PNG_BTN_MENUBAR4_DOWN			   103		//  축소x2 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR4_OVER			   104		//  축소x2 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR5				   105		//  부분확대 메뉴버튼
#define IDX_PNG_BTN_MENUBAR5_DOWN			   106		//  부분확대 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR5_OVER			   107		//  부분확대 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR6				   108		//  전체화면 메뉴버튼
#define IDX_PNG_BTN_MENUBAR6_DOWN			   109		//  전체화면 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR6_OVER			   110		//  전체화면 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR7				   111		//  네비게이션 메뉴버튼
#define IDX_PNG_BTN_MENUBAR7_DOWN			   112		//  네비게이션 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR7_OVER			   113		//  네비게이션 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR8				   114		//  선택 메뉴버튼
#define IDX_PNG_BTN_MENUBAR8_DOWN			   115		//  선택 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR8_OVER			   116		//  선택 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR9				   117		//  이동 메뉴버튼
#define IDX_PNG_BTN_MENUBAR9_DOWN			   118		//  이동 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR9_OVER			   119		//  이동 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR10				   120		//  뷰설정 메뉴버튼
#define IDX_PNG_BTN_MENUBAR10_DOWN			   121		//  뷰설정 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR10_OVER			   122		//  뷰설정 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR11				   123		//  메모조회 메뉴버튼
#define IDX_PNG_BTN_MENUBAR11_DOWN			   124		//  메모조회 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR11_OVER			   125		//  메모조회 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR12				   126		//  작업조회 메뉴버튼
#define IDX_PNG_BTN_MENUBAR12_DOWN			   127		//  작업조회 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR12_OVER			   128		//  작업조회 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR13				   129		//  툴팁 ON 메뉴버튼
#define IDX_PNG_BTN_MENUBAR13_DOWN			   130		//  툴팁 ON 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR13_OVER			   131		//  툴팁 ON 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR14				   132		//  깜빡임중지 메뉴버튼
#define IDX_PNG_BTN_MENUBAR14_DOWN			   133		//  깜빡임중지 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR14_OVER			   134		//  깜빡임중지 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR15				   135		//  툴팁 OFF 메뉴버튼
#define IDX_PNG_BTN_MENUBAR15_DOWN			   136		//  툴팁 OFF 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR15_OVER			   137		//  툴팁 OFF 메뉴버튼 마우스오버
#define IDX_PNG_CHK_DEFAULT					   138		//  체크버튼 디폴트	
#define IDX_PNG_CHK_CHECKED					   139		//  체크버튼 체크상태
#define IDX_PNG_CHK_DISABLE					   140		//  체크버튼 비활성상태
#define IDX_PNG_RAD_DEFAULT					   141		//  라디오버튼 디폴트	
#define IDX_PNG_RAD_CHECKED					   142		//  라디오버튼 체크상태
#define IDX_PNG_RAD_DISABLE					   143		//  라디오버튼 비활성상태
#define IDX_PNG_BTN_POPUP_OK				   144		//  팝업 스킨다이얼로그 확인버튼
#define IDX_PNG_BTN_POPUP_OK_DOWN			   145		//  팝업 스킨다이얼로그 확인버튼 클릭
#define IDX_PNG_BTN_POPUP_OK_OVER			   146		//  팝업 스킨다이얼로그 확인버튼 마우스오버
#define IDX_PNG_BTN_POPUP_CANCEL			   147		//  팝업 스킨다이얼로그 취소버튼
#define IDX_PNG_BTN_POPUP_CANCEL_DOWN		   148		//  팝업 스킨다이얼로그 취소버튼 클릭
#define IDX_PNG_BTN_POPUP_CANCEL_OVER		   149		//  팝업 스킨다이얼로그 취소버튼 마우스오버
#define IDX_PNG_STC_POPUP_TOP_LEFT			   150		//	팝업 스킨다이얼로그 위쪽왼쪽
#define IDX_PNG_STC_POPUP_TOP_CENTER		   151		//	팝업 스킨다이얼로그 위쪽가운데
#define IDX_PNG_STC_POPUP_TOP_RIGHT			   152		//	팝업 스킨다이얼로그 위쪽오른쪽
#define IDX_PNG_STC_POPUP_LEFT				   153		//	팝업 스킨다이얼로그 위쪽왼쪽
#define IDX_PNG_STC_POPUP_RIGHT				   154		//	팝업 스킨다이얼로그 위쪽왼쪽
#define IDX_PNG_STC_POPUP_BOTTOM_LEFT		   155		//	팝업 스킨다이얼로그 아래쪽왼쪽
#define IDX_PNG_STC_POPUP_BOTTOM_CENTER		   156		//	팝업 스킨다이얼로그 아래쪽가운데
#define IDX_PNG_STC_POPUP_BOTTOM_RIGHT		   157		//	팝업 스킨다이얼로그 아래쪽오른쪽
#define IDX_PNG_TAB_SMALL_LEFT_ST			   158		//  선택된 작은 TAB 왼쪽
#define IDX_PNG_TAB_SMALL_CENTER_ST			   159		//  선택된 작은 TAB 중앙
#define IDX_PNG_TAB_SMALL_RIGHT_ST			   160		//  선택된 작은 TAB 오른쪽
#define IDX_PNG_TAB_SMALL_LEFT_NST			   161		//  선택안된 작은 TAB 왼쪽
#define IDX_PNG_TAB_SMALL_CENTER_NST		   162		//  선택안된 작은 TAB 중앙
#define IDX_PNG_TAB_SMALL_RIGHT_NST			   163		//  선택안된 작은 TAB 오른쪽
#define IDX_PNG_STC_SEPARATOR				   164		//  구분자선
#define IDX_PNG_BTN_SEARCH2					   165		//  찾기 버튼
#define IDX_PNG_BTN_SEARCH2_DOWN			   166		//  찾기 버튼 클릭
#define IDX_PNG_BTN_SEARCH2_OVER			   167		//  찾기 버튼 마우스오버
#define IDX_PNG_TAB_INFO_LEFT_ST			   168		//  선택된 정보 TAB 왼쪽
#define IDX_PNG_TAB_INFO_CENTER_ST			   169		//  선택된 정보 TAB 중앙
#define IDX_PNG_TAB_INFO_RIGHT_ST			   170		//  선택된 정보 TAB 오른쪽
#define IDX_PNG_TAB_INFO_LEFT_NST			   171		//  선택안된 정보 TAB 왼쪽
#define IDX_PNG_TAB_INFO_CENTER_NST		       172		//  선택안된 정보 TAB 중앙
#define IDX_PNG_TAB_INFO_RIGHT_NST			   173		//  선택안된 정보 TAB 오른쪽
#define IDX_PNG_BTN_CTL_SET					   174		//  메모창 버튼
#define IDX_PNG_BTN_CTL_SET_DOWN			   175		//  메모창 버튼 클릭
#define IDX_PNG_BTN_CTL_SET_OVER			   176		//  메모창 버튼 마우스오버
#define IDX_PNG_BTN_CTL_CLEAR				   177		//  메모창 버튼
#define IDX_PNG_BTN_CTL_CLEAR_DOWN			   178		//  메모창 버튼 클릭
#define IDX_PNG_BTN_CTL_CLEAR_OVER			   179		//  메모창 버튼 마우스오버
#define IDX_PNG_TREE_LEFT					   180		//  트리컨트롤 캡션 왼쪽
#define IDX_PNG_TREE_TOP					   181		//  트리컨트롤 캡션 위쪽
#define IDX_PNG_TREE_RIGHT					   182		//  트리컨트롤 캡션 오른쪽
#define IDX_PNG_TREE_BOTTOM					   183		//  트리컨트롤 캡션 아래쪽
#define IDX_PNG_TREE_IMAGES					   184		//  트리컨트롤 IMAGE ICON
#define IDX_PNG_BTN_RELOGIN					   185		//  재로그인 버튼
#define IDX_PNG_BTN_RELOGIN_DOWN			   186		//  재로그인 버튼 클릭
#define IDX_PNG_BTN_RELOGIN_OVER			   187		//  재로그인 버튼 마우스오버
#define IDX_PNG_TAB_RIGHT_ST_CLOSE			   188		//  선택된 TAB 오른쪽 닫기버튼
#define IDX_PNG_TAB_RIGHT_ST_CLOSE_DOWN		   189		//  선택된 TAB 오른쪽 닫기버튼 클릭
#define IDX_PNG_TAB_RIGHT_ST_CLOSE_OVER		   190		//  선택된 TAB 오른쪽 닫기버튼 마우스오버
#define IDX_PNG_TAB_RIGHT_NST_CLOSE			   191		//  선택안된 TAB 오른쪽 닫기버튼
#define IDX_PNG_TAB_RIGHT_NST_CLOSE_DOWN	   192		//  선택안된 TAB 오른쪽 닫기버튼 클릭
#define IDX_PNG_TAB_RIGHT_NST_CLOSE_OVER	   193		//  선택안된 TAB 오른쪽 닫기버튼 마우스오버
#define IDX_PNG_STC_SUBTITLE				   194		//  제목 파란색줄
#define IDX_PNG_STC_SUBTITLE_LEFT			   195		//  부제목 왼쪽스킨
#define IDX_PNG_STC_SUBTITLE_CENTER			   196		//  부제목 중앙스킨
#define IDX_PNG_STC_SUBTITLE_RIGHT			   197		//  부제목 오른쪽스킨
#define IDX_PNG_STC_DATA_LEFT				   198		//  데이타제목 왼쪽스킨
#define IDX_PNG_STC_DATA_CENTER				   199		//  데이타제목 중앙스킨
#define IDX_PNG_STC_DATA_RIGHT				   200		//  데이타제목 오른쪽스킨
#define IDX_PNG_STC_DATA_SUB				   201		//  데이타 발전량
#define IDX_PNG_PRS_BATTERY_BK				   202		//  배터리 프로그래스바 배경
#define IDX_PNG_PRS_BATTERY_GREEN			   203		//  배터리 프로그래스바 녹색
#define IDX_PNG_STC_DATA_ARROW				   204		//  데이타제목 구분자화살표
#define IDX_PNG_STC_DATA_CONTROL_ON			   205		//  발전기 제어스위치 ON
#define IDX_PNG_STC_DATA_CONTROL_OFF		   206		//  발전기 제어스위치 OFF
#define IDX_PNG_BTN_DATA_CONTROL			   207		//  제어설정 버튼
#define IDX_PNG_BTN_DATA_CONTROL_DOWN		   208		//  제어설정 버튼 클릭
#define IDX_PNG_BTN_DATA_CONTROL_OVER		   209		//  제어설정 버튼 마우스오버
#define IDX_PNG_STC_MOVE_TAB				   210		//  탭분리시 나타나는 이미지
#define IDX_PNG_BOX_RESTORE_TAB				   211		//	탭 복귀버튼
#define IDX_PNG_BOX_RESTORE_TAB_DOWN		   212		//  탭 복귀버튼 클릭
#define IDX_PNG_BOX_RESTORE_TAB_OVER		   213		//  탭 복귀버튼 마우스오버
#define IDX_PNG_PRS_PROGRESSBAR				   214		//  프로그래스바 배경
#define IDX_PNG_PRS_PROGRESSBAR_RED			   215		//  프로그래스바 빨간색
#define IDX_PNG_PRS_PROGRESSBAR_GREEN		   216		//  프로그래스바 녹색
#define IDX_PNG_PRS_PROGRESSBAR_ORANGE		   217		//  프로그래스바 주황색
#define IDX_PNG_PRS_WHITE_PROGRESSBAR		   218		//  프로그래스바 흰색배경
#define IDX_PNG_PRS_WHITE_PROGRESSBAR_GREEN	   219		//  프로그래스바 흰색배경 녹색바
#define IDX_PNG_BTN_MENUBAR20				   220		//  자동이동금지 메뉴버튼
#define IDX_PNG_BTN_MENUBAR20_DOWN			   221		//  자동이동금지 OFF 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR20_OVER			   222		//  자동이동금지 OFF 메뉴버튼 마우스오버

#define IDX_PNG_STC_POINT_INFO				   223		//  제어 팝업창-포인트 배경
#define IDX_PNG_STC_POINT_SEPARATOR			   224		//  제어 팝업창-구분선
#define IDX_PNG_STC_USER_INFO				   225		//  제어 팝업창-사령원 배경
#define IDX_PNG_PRS_PROGRESSBAR_CTRL		   226		//  프로그래스바 제어창 배경
#define IDX_PNG_PRS_PROGRESSBAR_CTRL_BLUE	   227		//  프로그래스바 제어창 파란색
#define IDX_PNG_STC_POINT_RED				   228		//  포인트제어 빨간색
#define IDX_PNG_STC_POINT_BLUE				   229		//  포인트제어 파란색
#define IDX_PNG_STC_POINT_YELLOW			   230		//  포인트제어 노란색
#define IDX_PNG_STC_POINT_GREEN				   231		//  포인트제어 녹색
#define IDX_PNG_STC_POINT_ARROW				   232		//  포인트제어 화살표
#define IDX_PNG_STC_POINT_DESC				   233		//  포인트제어 이름상자
#define IDX_PNG_STC_POINT_CURRENT_VAL		   234		//  포인트제어 AI 현재값
#define IDX_PNG_STC_POINT_INPUT_VAL			   235		//  포인트제어 AI 설정값

#define IDX_PNG_BTN_MENUBAR23				   236		//  알람소리중지 메뉴버튼
#define IDX_PNG_BTN_MENUBAR23_DOWN			   237		//  알람소리중지 OFF 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR23_OVER			   238		//  알람소리중지 OFF 메뉴버튼 마우스오버
#define IDX_PNG_BTN_MENUBAR24				   239		//  알람소리켜기 메뉴버튼
#define IDX_PNG_BTN_MENUBAR24_DOWN			   240		//  알람소리켜기 OFF 메뉴버튼 클릭
#define IDX_PNG_BTN_MENUBAR24_OVER			   241		//  알람소리켜기 OFF 메뉴버튼 마우스오버


#define IDX_PNG_ALARAM_ON						242		//	알람 온
#define IDX_PNG_ALARAM_ON_OVER					243		//	알람 오버
#define IDX_PNG_ALARAM_OUT						244		//	알람 오프
#define IDX_PNG_ALARAM_OUT_OVER					245		//	알람 오프 오버
#define IDX_PNG_ALARAM_CLICK					246		//	알람 클릭
#define IDX_PNG_DATA_ON							247		//	데이터 온
#define IDX_PNG_DATA_ON_OVER					248		//  데이터 온 오버
#define IDX_PNG_DATA_OUT						249		//  데이터 오프
#define IDX_PNG_DATA_OUT_OVER					250		//  데이터 오프 클릭
#define IDX_PNG_DATA_CLICK						251		//  데이터 클릭
#define IDX_PNG_DMS_ON							252		//	DMS On
#define IDX_PNG_DMS_ON_OVER						253		//	DMS On over
#define IDX_PNG_DMS_OUT							254		//	DMS Off
#define IDX_PNG_DMS_OUT_OVER					255		//	DMS Off over
#define IDX_PNG_DMS_CLICK						256		//	DMS Click
#define IDX_PNG_MG_ON							257		//	MG On
#define IDX_PNG_MG_ON_OVER						258		//	MG On over
#define IDX_PNG_MG_OUT							259		//	MG Off
#define IDX_PNG_MG_OUT_OVER						260		//	MG Off over
#define IDX_PNG_MG_CLICK						261		//	MG Click
#define IDX_PNG_TOOLS_ON						262		//	Tools On
#define IDX_PNG_TOOLS_ON_OVER					263		//	Tools On over
#define IDX_PNG_TOOLS_CLICK						264		//	Tools Click


#define IDX_PNG_MAX							   265		//	PNG 총개수
/////////////////////////////////////////////////////////////////////////////////////////////////
//	ICON SKIN DEFINE
/////////////////////////////////////////////////////////////////////////////////////////////////

#define IDX_ICON_SKIN						0		//	윈도우 프레임 대표아이콘
#define IDX_ICN_MAX							1		//	아이콘 총개수

#define ICON16								0		//	아이콘크기 16x16
#define ICON24								1		//	아이콘크기 24x24
#define ICON32								2		//	아이콘크기 32x32

/////////////////////////////////////////////////////////////////////////////////////////////////
//	FONT SIZE DEFINE
/////////////////////////////////////////////////////////////////////////////////////////////////

#define IDX_FONT_SIZE_8						0		//	나눔고딕폰트 사이즈 8
#define IDX_FONT_SIZE_10					1		//	나눔고딕폰트 사이즈 10
#define IDX_FONT_SIZE_12					2		//	나눔고딕폰트 사이즈 12
#define IDX_FONT_SIZE_14					3		//	나눔고딕폰트 사이즈 14
#define IDX_FONT_SIZE_16					4		//	나눔고딕폰트 사이즈 16
#define IDX_FONT_SIZE_18					5		//	나눔고딕폰트 사이즈 18
#define IDX_FONT_SIZE_20					6		//	나눔고딕폰트 사이즈 20
#define IDX_FONT_MAX						7		//	폰트 총개수

/////////////////////////////////////////////////////////////////////////////////////////////////
//	RGB	DEFINE
/////////////////////////////////////////////////////////////////////////////////////////////////

#define IDX_RGB_MAIN_BACKGROUND				0		//	윈도우 배경색상
#define	IDX_RGB_MAIN_MENU					1		//  윈도우 메인메뉴 배경색상
#define	IDX_RGB_MAIN_TAB					2		//  윈도우 메인탭 배경색상
#define IDX_RGB_FONT_BLACK					3		//	폰트 검은색
#define IDX_RGB_FONT_WHITE					4		//	폰트 흰색
#define IDX_RGB_FONT_RED					5		//	폰트 빨간색
#define IDX_RGB_FONT_GREEN					6		//	폰트 녹색
#define IDX_RGB_FONT_BLUE					7		//	폰트 파란색
#define IDX_RGB_FONT_GRAY					8		//	폰트 회색
#define IDX_RGB_FONT_GRAY2					9		//	폰트 회색2
#define IDX_RGB_FONT_GRAY3				   10		//	폰트 회색3
#define IDX_RGB_FONT_GRAY4				   11		//	폰트 회색4
#define IDX_RGB_FONT_LITE_BLUE			   12		//	폰트 옅은 파란색
#define IDX_RGB_FONT_LITE_BLUE2			   13		//	폰트 옅은 파란색2
#define IDX_RGB_FONT_LITE_GRAY			   14		//	폰트 옅은 회색
#define IDX_RGB_FONT_LITE_GRAY2			   15		//	폰트 옅은 회색2
#define IDX_RGB_FONT_LITE_GRAY3			   16		//	폰트 옅은 회색3
#define IDX_RGB_MAX						   17		//	색상 총개수

/////////////////////////////////////////////////////////////////////////////////////////////////
//	KEYBOARD CONTROL STATE
/////////////////////////////////////////////////////////////////////////////////////////////////

#define KEYDOWN(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP  (vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

//===========================================================================
// function pointer definitions for SetLayeredWindowAttributes in User32.dll
//===========================================================================
typedef BOOL (WINAPI *lpfn) (HWND hWnd, COLORREF cr, BYTE bAlpha, DWORD dwFlags);

typedef struct tagBITMAP_INFO
{
	HBITMAP hBitmap;
	BITMAP	bitmap;

} BITMAP_INFO;

class CGlobal
{
public:
	CGlobal();
	virtual ~CGlobal();

// Attributes
public:
	CFont		   *m_pFont		[ IDX_FONT_MAX ];
	BITMAP_INFO		m_infoBitmap[ IDX_PNG_MAX  ];
	HICON			m_hIcon	    [ IDX_ICN_MAX  ][ 3 ];
	COLORREF		m_cfRGB		[ IDX_RGB_MAX  ];	

// Operations
public:
	lpfn			SetLayeredWindowAttributes;

	void			DeleteBitmaps    ();	
	void			LoadBitmaps      ();	
	HBITMAP			GetBitmap        ( UINT nBitmapID );
	SIZE			GetBitmapSize    ( UINT nBitmapID );
	CString			GetBitmapFileName( UINT nBitmapID );
	CString			GetModulePath    ();

	void			DeleteIcons      ();
	void			LoadIcons        ();
	CString			GetIconFileName  ( UINT nIconID );
	HICON			GetIcon			 ( UINT nIconID, UINT nType );	
	COLORREF		GetRGB( UINT nRGBID );
	
	void			DeleteFonts();
	void			LoadFonts  ( CString strFaceName );
	CFont		   *SetFont    ( UINT nFontID, CString strFaceName, UINT nFontSize, BOOL bBold = FALSE );
	CFont		   *GetFont    ( UINT nFontID );

	COLORREF		Darker ( COLORREF crBase, float fFactor );
	COLORREF		Lighter( COLORREF crBase, float fFactor );
};

#endif //_GLOBAL_H
