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

#define IDX_PNG_CAPTION_LEFT					 0		//	������ ĸ�� ����
#define IDX_PNG_CAPTION_CENTER					 1		//	������ ĸ�� �߾�
#define IDX_PNG_CAPTION_RIGHT					 2		//	������ ĸ�� ������
#define IDX_PNG_FRAME_LEFT						 3		//	������ ������ ����
#define IDX_PNG_FRAME_LEFT_BOTTOM				 4		//	������ ������ ���ʾƷ�
#define IDX_PNG_FRAME_BOTTOM					 5		//	������ ������ �Ʒ�
#define IDX_PNG_FRAME_RIGHT_BOTTOM				 6		//	������ ������ �����ʾƷ�
#define IDX_PNG_FRAME_RIGHT						 7		//	������ ������ ������
#define IDX_PNG_BOX_MINIMIZE					 8		//	������ ������ �ּ�ȭ��ư
#define IDX_PNG_BOX_MAXMIZE						 9		//	������ ������ �ִ�ȭ��ư
#define IDX_PNG_BOX_RESTORE						10		//	������ ������ ���͹�ư
#define IDX_PNG_BOX_EXIT						11		//	������ ������ �����ư
#define IDX_PNG_BOX_MINIMIZE_DOWN				12		//	������ ������ �ּ�ȭ��ư Ŭ��
#define IDX_PNG_BOX_MAXMIZE_DOWN				13		//	������ ������ �ִ�ȭ��ư Ŭ��
#define IDX_PNG_BOX_RESTORE_DOWN				14		//	������ ������ ���͹�ư Ŭ��
#define IDX_PNG_BOX_EXIT_DOWN					15		//	������ ������ �����ư Ŭ��
#define IDX_PNG_BOX_MINIMIZE_OVER				16		//	������ ������ �ּ�ȭ��ư ���콺����
#define IDX_PNG_BOX_MAXMIZE_OVER				17		//	������ ������ �ִ�ȭ��ư ���콺����
#define IDX_PNG_BOX_RESTORE_OVER				18		//	������ ������ ���͹�ư ���콺����
#define IDX_PNG_BOX_EXIT_OVER					19		//	������ ������ �����ư ���콺����
#define IDX_PNG_TAB_LEFT_ST						20		//  ���õ� TAB ����
#define IDX_PNG_TAB_CENTER_ST					21		//  ���õ� TAB �߾�
#define IDX_PNG_TAB_RIGHT_ST					22		//  ���õ� TAB ������
#define IDX_PNG_TAB_LEFT_NST					23		//  ���þȵ� TAB ����
#define IDX_PNG_TAB_CENTER_NST					24		//  ���þȵ� TAB �߾�
#define IDX_PNG_TAB_RIGHT_NST					25		//  ���þȵ� TAB ������
#define IDX_PNG_POPUP_CAPTION_LEFT				26		//	�˾������� ĸ�� ����
#define IDX_PNG_POPUP_CAPTION_CENTER			27		//	�˾������� ĸ�� �߾�
#define IDX_PNG_POPUP_CAPTION_RIGHT				28		//	�˾������� ĸ�� ������
#define IDX_PNG_POPUP_LEFT						29		//	�˾������� ������ ����
#define IDX_PNG_POPUP_LEFT_BOTTOM				30		//	�˾������� ������ ���ʾƷ�
#define IDX_PNG_POPUP_BOTTOM					31		//	�˾������� ������ �Ʒ�
#define IDX_PNG_POPUP_RIGHT_BOTTOM				32		//	�˾������� ������ �����ʾƷ�
#define IDX_PNG_POPUP_RIGHT						33		//	�˾������� ������ ������
#define IDX_PNG_STC_MSGBOX_ERROR				34		//  �޼����ڽ� ����
#define IDX_PNG_STC_MSGBOX_INFO					35		//  �޼����ڽ� ����
#define IDX_PNG_STC_MSGBOX_QUESTION				36		//  �޼����ڽ� ����
#define IDX_PNG_STC_MSGBOX_WARNING				37		//  �޼����ڽ� ���
#define IDX_PNG_BTN_MSGBOX						38		//  �޼����ڽ� ��ư
#define IDX_PNG_BTN_MSGBOX_DOWN					39		//  �޼����ڽ� ��ư Ŭ��
#define IDX_PNG_BTN_MSGBOX_OVER					40		//  �޼����ڽ� ��ư ���콺����
#define IDX_PNG_CMB_LEFT						41		//  �޺��ڽ� ĸ�� ����
#define IDX_PNG_CMB_TOP							42		//  �޺��ڽ� ĸ�� ����
#define IDX_PNG_CMB_BOTTOM						43		//  �޺��ڽ� ĸ�� �Ʒ���
#define IDX_PNG_CMB_BUTTON						44		//  �޺��ڽ� ĸ�� ��ư
#define IDX_PNG_BTN_SEARCH						45		//  �˻� ��ư
#define IDX_PNG_BTN_SEARCH_DOWN					46		//  �˻� ��ư Ŭ��
#define IDX_PNG_BTN_SEARCH_OVER					47		//  �˻� ��ư ���콺����
#define IDX_PNG_STC_KEPCO						48		//  KEPCO �ΰ�
#define IDX_PNG_BTN_CONFIG						49		//  ȯ�漳�� ��ư
#define IDX_PNG_BTN_CONFIG_DOWN					50		//  ȯ�漳�� ��ư Ŭ��
#define IDX_PNG_BTN_CONFIG_OVER					51		//  ȯ�漳�� ��ư ���콺����
#define IDX_PNG_BTN_INIT						52		//  �ʱ�ȭ ��ư
#define IDX_PNG_BTN_INIT_DOWN					53		//  �ʱ�ȭ ��ư Ŭ��
#define IDX_PNG_BTN_INIT_OVER					54		//  �ʱ�ȭ ��ư ���콺����
#define IDX_PNG_BTN_BUILDER						55		//  �������� ��ư
#define IDX_PNG_BTN_BUILDER_DOWN				56		//  �������� ��ư Ŭ��
#define IDX_PNG_BTN_BUILDER_OVER				57		//  �������� ��ư ���콺����
#define IDX_PNG_BTN_RTUSEARCH					58		//  ����˻� ��ư
#define IDX_PNG_BTN_RTUSEARCH_DOWN				59		//  ����˻� ��ư Ŭ��
#define IDX_PNG_BTN_RTUSEARCH_OVER				60		//  ����˻� ��ư ���콺����
#define IDX_PNG_BTN_PRINT_SC					61		//  ȭ���μ� ��ư
#define IDX_PNG_BTN_PRINT_SC_DOWN				62		//  ȭ���μ� ��ư Ŭ��
#define IDX_PNG_BTN_PRINT_SC_OVER				63		//  ȭ���μ� ��ư ���콺����
#define IDX_PNG_BTN_PRINT_FULL					64		//  ��ü�μ� ��ư
#define IDX_PNG_BTN_PRINT_FULL_DOWN				65		//  ��ü�μ� ��ư Ŭ��
#define IDX_PNG_BTN_PRINT_FULL_OVER				66		//  ��ü�μ� ��ư ���콺����
#define IDX_PNG_BTN_EXCEL						67		//  ������ȯ ��ư
#define IDX_PNG_BTN_EXCEL_DOWN					68		//  ������ȯ ��ư Ŭ��
#define IDX_PNG_BTN_EXCEL_OVER					69		//  ������ȯ ��ư ���콺����
#define IDX_PNG_BTN_PRINT_SETUP					70		//  �μ⼳�� ��ư
#define IDX_PNG_BTN_PRINT_SETUP_DOWN			71		//  �μ⼳�� ��ư Ŭ��
#define IDX_PNG_BTN_PRINT_SETUP_OVER			72		//  �μ⼳�� ��ư ���콺����
#define IDX_PNG_BTN_USER_CHANGE					73		//  ����ں��� ��ư
#define IDX_PNG_BTN_USER_CHANGE_DOWN			74		//  ����ں��� ��ư Ŭ��
#define IDX_PNG_BTN_USER_CHANGE_OVER			75		//  ����ں��� ��ư ���콺����
#define IDX_PNG_BTN_USER_MODIFY					76		//  ����ڰ��� ��ư
#define IDX_PNG_BTN_USER_MODIFY_DOWN			77		//  ����ڰ��� ��ư Ŭ��
#define IDX_PNG_BTN_USER_MODIFY_OVER			78		//  ����ڰ��� ��ư ���콺����
#define IDX_PNG_BTN_USER_MESSAGE				79		//  �۾��޼��� ��ư
#define IDX_PNG_BTN_USER_MESSAGE_DOWN			80		//  �۾��޼��� ��ư Ŭ��
#define IDX_PNG_BTN_USER_MESSAGE_OVER			81		//  �۾��޼��� ��ư ���콺����
#define IDX_PNG_BTN_FI_LIST						82		//  FI��� ��ư
#define IDX_PNG_BTN_FI_LIST_DOWN				83		//  FI��� ��ư Ŭ��
#define IDX_PNG_BTN_FI_LIST_OVER				84		//  FI��� ��ư ���콺����
#define IDX_PNG_CMB_CENTER						85		//  �޺��ڽ� ĸ�� ���
#define IDX_PNG_LOGIN_BASE						86		//  �α��� ��� �̹���
#define IDX_PNG_BTN_LOGIN						87		//  �α��� ��ư
#define IDX_PNG_BTN_LOGIN_DOWN					88		//  �α��� ��ư Ŭ��
#define IDX_PNG_BTN_LOGIN_OVER					89		//  �α��� ��ư ���콺����
#define IDX_PNG_LISTCTRL_HEADER_DIVISION		90		//  ����Ʈ��Ʈ�� ��� ������
#define IDX_PNG_LISTCTRL_HEADER_SHADOW			91		//  ����Ʈ��Ʈ�� ��� �غκ�
#define IDX_PNG_STC_MENUBAR						92		//  ���뵵 �޴��� ���
#define IDX_PNG_BTN_MENUBAR1					93		//  Ȯ�� �޴���ư
#define IDX_PNG_BTN_MENUBAR1_DOWN				94		//  Ȯ�� �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR1_OVER				95		//  Ȯ�� �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR2					96		//  ��� �޴���ư
#define IDX_PNG_BTN_MENUBAR2_DOWN				97		//  ��� �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR2_OVER				98		//  ��� �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR3					99		//  Ȯ��x2 �޴���ư
#define IDX_PNG_BTN_MENUBAR3_DOWN			   100		//  Ȯ��x2 �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR3_OVER			   101		//  Ȯ��x2 �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR4				   102		//  ���x2 �޴���ư
#define IDX_PNG_BTN_MENUBAR4_DOWN			   103		//  ���x2 �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR4_OVER			   104		//  ���x2 �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR5				   105		//  �κ�Ȯ�� �޴���ư
#define IDX_PNG_BTN_MENUBAR5_DOWN			   106		//  �κ�Ȯ�� �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR5_OVER			   107		//  �κ�Ȯ�� �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR6				   108		//  ��üȭ�� �޴���ư
#define IDX_PNG_BTN_MENUBAR6_DOWN			   109		//  ��üȭ�� �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR6_OVER			   110		//  ��üȭ�� �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR7				   111		//  �׺���̼� �޴���ư
#define IDX_PNG_BTN_MENUBAR7_DOWN			   112		//  �׺���̼� �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR7_OVER			   113		//  �׺���̼� �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR8				   114		//  ���� �޴���ư
#define IDX_PNG_BTN_MENUBAR8_DOWN			   115		//  ���� �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR8_OVER			   116		//  ���� �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR9				   117		//  �̵� �޴���ư
#define IDX_PNG_BTN_MENUBAR9_DOWN			   118		//  �̵� �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR9_OVER			   119		//  �̵� �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR10				   120		//  �伳�� �޴���ư
#define IDX_PNG_BTN_MENUBAR10_DOWN			   121		//  �伳�� �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR10_OVER			   122		//  �伳�� �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR11				   123		//  �޸���ȸ �޴���ư
#define IDX_PNG_BTN_MENUBAR11_DOWN			   124		//  �޸���ȸ �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR11_OVER			   125		//  �޸���ȸ �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR12				   126		//  �۾���ȸ �޴���ư
#define IDX_PNG_BTN_MENUBAR12_DOWN			   127		//  �۾���ȸ �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR12_OVER			   128		//  �۾���ȸ �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR13				   129		//  ���� ON �޴���ư
#define IDX_PNG_BTN_MENUBAR13_DOWN			   130		//  ���� ON �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR13_OVER			   131		//  ���� ON �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR14				   132		//  ���������� �޴���ư
#define IDX_PNG_BTN_MENUBAR14_DOWN			   133		//  ���������� �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR14_OVER			   134		//  ���������� �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR15				   135		//  ���� OFF �޴���ư
#define IDX_PNG_BTN_MENUBAR15_DOWN			   136		//  ���� OFF �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR15_OVER			   137		//  ���� OFF �޴���ư ���콺����
#define IDX_PNG_CHK_DEFAULT					   138		//  üũ��ư ����Ʈ	
#define IDX_PNG_CHK_CHECKED					   139		//  üũ��ư üũ����
#define IDX_PNG_CHK_DISABLE					   140		//  üũ��ư ��Ȱ������
#define IDX_PNG_RAD_DEFAULT					   141		//  ������ư ����Ʈ	
#define IDX_PNG_RAD_CHECKED					   142		//  ������ư üũ����
#define IDX_PNG_RAD_DISABLE					   143		//  ������ư ��Ȱ������
#define IDX_PNG_BTN_POPUP_OK				   144		//  �˾� ��Ų���̾�α� Ȯ�ι�ư
#define IDX_PNG_BTN_POPUP_OK_DOWN			   145		//  �˾� ��Ų���̾�α� Ȯ�ι�ư Ŭ��
#define IDX_PNG_BTN_POPUP_OK_OVER			   146		//  �˾� ��Ų���̾�α� Ȯ�ι�ư ���콺����
#define IDX_PNG_BTN_POPUP_CANCEL			   147		//  �˾� ��Ų���̾�α� ��ҹ�ư
#define IDX_PNG_BTN_POPUP_CANCEL_DOWN		   148		//  �˾� ��Ų���̾�α� ��ҹ�ư Ŭ��
#define IDX_PNG_BTN_POPUP_CANCEL_OVER		   149		//  �˾� ��Ų���̾�α� ��ҹ�ư ���콺����
#define IDX_PNG_STC_POPUP_TOP_LEFT			   150		//	�˾� ��Ų���̾�α� ���ʿ���
#define IDX_PNG_STC_POPUP_TOP_CENTER		   151		//	�˾� ��Ų���̾�α� ���ʰ��
#define IDX_PNG_STC_POPUP_TOP_RIGHT			   152		//	�˾� ��Ų���̾�α� ���ʿ�����
#define IDX_PNG_STC_POPUP_LEFT				   153		//	�˾� ��Ų���̾�α� ���ʿ���
#define IDX_PNG_STC_POPUP_RIGHT				   154		//	�˾� ��Ų���̾�α� ���ʿ���
#define IDX_PNG_STC_POPUP_BOTTOM_LEFT		   155		//	�˾� ��Ų���̾�α� �Ʒ��ʿ���
#define IDX_PNG_STC_POPUP_BOTTOM_CENTER		   156		//	�˾� ��Ų���̾�α� �Ʒ��ʰ��
#define IDX_PNG_STC_POPUP_BOTTOM_RIGHT		   157		//	�˾� ��Ų���̾�α� �Ʒ��ʿ�����
#define IDX_PNG_TAB_SMALL_LEFT_ST			   158		//  ���õ� ���� TAB ����
#define IDX_PNG_TAB_SMALL_CENTER_ST			   159		//  ���õ� ���� TAB �߾�
#define IDX_PNG_TAB_SMALL_RIGHT_ST			   160		//  ���õ� ���� TAB ������
#define IDX_PNG_TAB_SMALL_LEFT_NST			   161		//  ���þȵ� ���� TAB ����
#define IDX_PNG_TAB_SMALL_CENTER_NST		   162		//  ���þȵ� ���� TAB �߾�
#define IDX_PNG_TAB_SMALL_RIGHT_NST			   163		//  ���þȵ� ���� TAB ������
#define IDX_PNG_STC_SEPARATOR				   164		//  �����ڼ�
#define IDX_PNG_BTN_SEARCH2					   165		//  ã�� ��ư
#define IDX_PNG_BTN_SEARCH2_DOWN			   166		//  ã�� ��ư Ŭ��
#define IDX_PNG_BTN_SEARCH2_OVER			   167		//  ã�� ��ư ���콺����
#define IDX_PNG_TAB_INFO_LEFT_ST			   168		//  ���õ� ���� TAB ����
#define IDX_PNG_TAB_INFO_CENTER_ST			   169		//  ���õ� ���� TAB �߾�
#define IDX_PNG_TAB_INFO_RIGHT_ST			   170		//  ���õ� ���� TAB ������
#define IDX_PNG_TAB_INFO_LEFT_NST			   171		//  ���þȵ� ���� TAB ����
#define IDX_PNG_TAB_INFO_CENTER_NST		       172		//  ���þȵ� ���� TAB �߾�
#define IDX_PNG_TAB_INFO_RIGHT_NST			   173		//  ���þȵ� ���� TAB ������
#define IDX_PNG_BTN_CTL_SET					   174		//  �޸�â ��ư
#define IDX_PNG_BTN_CTL_SET_DOWN			   175		//  �޸�â ��ư Ŭ��
#define IDX_PNG_BTN_CTL_SET_OVER			   176		//  �޸�â ��ư ���콺����
#define IDX_PNG_BTN_CTL_CLEAR				   177		//  �޸�â ��ư
#define IDX_PNG_BTN_CTL_CLEAR_DOWN			   178		//  �޸�â ��ư Ŭ��
#define IDX_PNG_BTN_CTL_CLEAR_OVER			   179		//  �޸�â ��ư ���콺����
#define IDX_PNG_TREE_LEFT					   180		//  Ʈ����Ʈ�� ĸ�� ����
#define IDX_PNG_TREE_TOP					   181		//  Ʈ����Ʈ�� ĸ�� ����
#define IDX_PNG_TREE_RIGHT					   182		//  Ʈ����Ʈ�� ĸ�� ������
#define IDX_PNG_TREE_BOTTOM					   183		//  Ʈ����Ʈ�� ĸ�� �Ʒ���
#define IDX_PNG_TREE_IMAGES					   184		//  Ʈ����Ʈ�� IMAGE ICON
#define IDX_PNG_BTN_RELOGIN					   185		//  ��α��� ��ư
#define IDX_PNG_BTN_RELOGIN_DOWN			   186		//  ��α��� ��ư Ŭ��
#define IDX_PNG_BTN_RELOGIN_OVER			   187		//  ��α��� ��ư ���콺����
#define IDX_PNG_TAB_RIGHT_ST_CLOSE			   188		//  ���õ� TAB ������ �ݱ��ư
#define IDX_PNG_TAB_RIGHT_ST_CLOSE_DOWN		   189		//  ���õ� TAB ������ �ݱ��ư Ŭ��
#define IDX_PNG_TAB_RIGHT_ST_CLOSE_OVER		   190		//  ���õ� TAB ������ �ݱ��ư ���콺����
#define IDX_PNG_TAB_RIGHT_NST_CLOSE			   191		//  ���þȵ� TAB ������ �ݱ��ư
#define IDX_PNG_TAB_RIGHT_NST_CLOSE_DOWN	   192		//  ���þȵ� TAB ������ �ݱ��ư Ŭ��
#define IDX_PNG_TAB_RIGHT_NST_CLOSE_OVER	   193		//  ���þȵ� TAB ������ �ݱ��ư ���콺����
#define IDX_PNG_STC_SUBTITLE				   194		//  ���� �Ķ�����
#define IDX_PNG_STC_SUBTITLE_LEFT			   195		//  ������ ���ʽ�Ų
#define IDX_PNG_STC_SUBTITLE_CENTER			   196		//  ������ �߾ӽ�Ų
#define IDX_PNG_STC_SUBTITLE_RIGHT			   197		//  ������ �����ʽ�Ų
#define IDX_PNG_STC_DATA_LEFT				   198		//  ����Ÿ���� ���ʽ�Ų
#define IDX_PNG_STC_DATA_CENTER				   199		//  ����Ÿ���� �߾ӽ�Ų
#define IDX_PNG_STC_DATA_RIGHT				   200		//  ����Ÿ���� �����ʽ�Ų
#define IDX_PNG_STC_DATA_SUB				   201		//  ����Ÿ ������
#define IDX_PNG_PRS_BATTERY_BK				   202		//  ���͸� ���α׷����� ���
#define IDX_PNG_PRS_BATTERY_GREEN			   203		//  ���͸� ���α׷����� ���
#define IDX_PNG_STC_DATA_ARROW				   204		//  ����Ÿ���� ������ȭ��ǥ
#define IDX_PNG_STC_DATA_CONTROL_ON			   205		//  ������ �����ġ ON
#define IDX_PNG_STC_DATA_CONTROL_OFF		   206		//  ������ �����ġ OFF
#define IDX_PNG_BTN_DATA_CONTROL			   207		//  ����� ��ư
#define IDX_PNG_BTN_DATA_CONTROL_DOWN		   208		//  ����� ��ư Ŭ��
#define IDX_PNG_BTN_DATA_CONTROL_OVER		   209		//  ����� ��ư ���콺����
#define IDX_PNG_STC_MOVE_TAB				   210		//  �Ǻи��� ��Ÿ���� �̹���
#define IDX_PNG_BOX_RESTORE_TAB				   211		//	�� ���͹�ư
#define IDX_PNG_BOX_RESTORE_TAB_DOWN		   212		//  �� ���͹�ư Ŭ��
#define IDX_PNG_BOX_RESTORE_TAB_OVER		   213		//  �� ���͹�ư ���콺����
#define IDX_PNG_PRS_PROGRESSBAR				   214		//  ���α׷����� ���
#define IDX_PNG_PRS_PROGRESSBAR_RED			   215		//  ���α׷����� ������
#define IDX_PNG_PRS_PROGRESSBAR_GREEN		   216		//  ���α׷����� ���
#define IDX_PNG_PRS_PROGRESSBAR_ORANGE		   217		//  ���α׷����� ��Ȳ��
#define IDX_PNG_PRS_WHITE_PROGRESSBAR		   218		//  ���α׷����� ������
#define IDX_PNG_PRS_WHITE_PROGRESSBAR_GREEN	   219		//  ���α׷����� ������ �����
#define IDX_PNG_BTN_MENUBAR20				   220		//  �ڵ��̵����� �޴���ư
#define IDX_PNG_BTN_MENUBAR20_DOWN			   221		//  �ڵ��̵����� OFF �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR20_OVER			   222		//  �ڵ��̵����� OFF �޴���ư ���콺����

#define IDX_PNG_STC_POINT_INFO				   223		//  ���� �˾�â-����Ʈ ���
#define IDX_PNG_STC_POINT_SEPARATOR			   224		//  ���� �˾�â-���м�
#define IDX_PNG_STC_USER_INFO				   225		//  ���� �˾�â-��ɿ� ���
#define IDX_PNG_PRS_PROGRESSBAR_CTRL		   226		//  ���α׷����� ����â ���
#define IDX_PNG_PRS_PROGRESSBAR_CTRL_BLUE	   227		//  ���α׷����� ����â �Ķ���
#define IDX_PNG_STC_POINT_RED				   228		//  ����Ʈ���� ������
#define IDX_PNG_STC_POINT_BLUE				   229		//  ����Ʈ���� �Ķ���
#define IDX_PNG_STC_POINT_YELLOW			   230		//  ����Ʈ���� �����
#define IDX_PNG_STC_POINT_GREEN				   231		//  ����Ʈ���� ���
#define IDX_PNG_STC_POINT_ARROW				   232		//  ����Ʈ���� ȭ��ǥ
#define IDX_PNG_STC_POINT_DESC				   233		//  ����Ʈ���� �̸�����
#define IDX_PNG_STC_POINT_CURRENT_VAL		   234		//  ����Ʈ���� AI ���簪
#define IDX_PNG_STC_POINT_INPUT_VAL			   235		//  ����Ʈ���� AI ������

#define IDX_PNG_BTN_MENUBAR23				   236		//  �˶��Ҹ����� �޴���ư
#define IDX_PNG_BTN_MENUBAR23_DOWN			   237		//  �˶��Ҹ����� OFF �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR23_OVER			   238		//  �˶��Ҹ����� OFF �޴���ư ���콺����
#define IDX_PNG_BTN_MENUBAR24				   239		//  �˶��Ҹ��ѱ� �޴���ư
#define IDX_PNG_BTN_MENUBAR24_DOWN			   240		//  �˶��Ҹ��ѱ� OFF �޴���ư Ŭ��
#define IDX_PNG_BTN_MENUBAR24_OVER			   241		//  �˶��Ҹ��ѱ� OFF �޴���ư ���콺����


#define IDX_PNG_ALARAM_ON						242		//	�˶� ��
#define IDX_PNG_ALARAM_ON_OVER					243		//	�˶� ����
#define IDX_PNG_ALARAM_OUT						244		//	�˶� ����
#define IDX_PNG_ALARAM_OUT_OVER					245		//	�˶� ���� ����
#define IDX_PNG_ALARAM_CLICK					246		//	�˶� Ŭ��
#define IDX_PNG_DATA_ON							247		//	������ ��
#define IDX_PNG_DATA_ON_OVER					248		//  ������ �� ����
#define IDX_PNG_DATA_OUT						249		//  ������ ����
#define IDX_PNG_DATA_OUT_OVER					250		//  ������ ���� Ŭ��
#define IDX_PNG_DATA_CLICK						251		//  ������ Ŭ��
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


#define IDX_PNG_MAX							   265		//	PNG �Ѱ���
/////////////////////////////////////////////////////////////////////////////////////////////////
//	ICON SKIN DEFINE
/////////////////////////////////////////////////////////////////////////////////////////////////

#define IDX_ICON_SKIN						0		//	������ ������ ��ǥ������
#define IDX_ICN_MAX							1		//	������ �Ѱ���

#define ICON16								0		//	������ũ�� 16x16
#define ICON24								1		//	������ũ�� 24x24
#define ICON32								2		//	������ũ�� 32x32

/////////////////////////////////////////////////////////////////////////////////////////////////
//	FONT SIZE DEFINE
/////////////////////////////////////////////////////////////////////////////////////////////////

#define IDX_FONT_SIZE_8						0		//	���������Ʈ ������ 8
#define IDX_FONT_SIZE_10					1		//	���������Ʈ ������ 10
#define IDX_FONT_SIZE_12					2		//	���������Ʈ ������ 12
#define IDX_FONT_SIZE_14					3		//	���������Ʈ ������ 14
#define IDX_FONT_SIZE_16					4		//	���������Ʈ ������ 16
#define IDX_FONT_SIZE_18					5		//	���������Ʈ ������ 18
#define IDX_FONT_SIZE_20					6		//	���������Ʈ ������ 20
#define IDX_FONT_MAX						7		//	��Ʈ �Ѱ���

/////////////////////////////////////////////////////////////////////////////////////////////////
//	RGB	DEFINE
/////////////////////////////////////////////////////////////////////////////////////////////////

#define IDX_RGB_MAIN_BACKGROUND				0		//	������ ������
#define	IDX_RGB_MAIN_MENU					1		//  ������ ���θ޴� ������
#define	IDX_RGB_MAIN_TAB					2		//  ������ ������ ������
#define IDX_RGB_FONT_BLACK					3		//	��Ʈ ������
#define IDX_RGB_FONT_WHITE					4		//	��Ʈ ���
#define IDX_RGB_FONT_RED					5		//	��Ʈ ������
#define IDX_RGB_FONT_GREEN					6		//	��Ʈ ���
#define IDX_RGB_FONT_BLUE					7		//	��Ʈ �Ķ���
#define IDX_RGB_FONT_GRAY					8		//	��Ʈ ȸ��
#define IDX_RGB_FONT_GRAY2					9		//	��Ʈ ȸ��2
#define IDX_RGB_FONT_GRAY3				   10		//	��Ʈ ȸ��3
#define IDX_RGB_FONT_GRAY4				   11		//	��Ʈ ȸ��4
#define IDX_RGB_FONT_LITE_BLUE			   12		//	��Ʈ ���� �Ķ���
#define IDX_RGB_FONT_LITE_BLUE2			   13		//	��Ʈ ���� �Ķ���2
#define IDX_RGB_FONT_LITE_GRAY			   14		//	��Ʈ ���� ȸ��
#define IDX_RGB_FONT_LITE_GRAY2			   15		//	��Ʈ ���� ȸ��2
#define IDX_RGB_FONT_LITE_GRAY3			   16		//	��Ʈ ���� ȸ��3
#define IDX_RGB_MAX						   17		//	���� �Ѱ���

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
