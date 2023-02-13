#pragma once

#include "../SB_Manager/CSB_Object.h"
#include "CDND_Object.h"
#include "CDND_Switch.h"
#include "CDND_Connect.h"
#include "CDND_Text.h"
#include "CKASIM_ND.h"

#include "CProgress_bar.h"

struct stSVG_Page
{
	int			st_Type;
	CString		st_strName;
};

struct stSVG_G
{
	CString		st_strName;
	
	double		st_dX;
	double		st_dY;
	double		st_dWidth;
	double		st_dHeight;

	CString		st_strBG_Color;
	
};

struct stSVG_Layer
{
	int			st_nID;
	CString		st_strName;

	int			st_nType;
	int			st_nShow;
	int			st_nZoomLevelEnable;

	double		st_dZoom_start;
	double		st_dZoom_end;

	CString		st_strScript;
};

class AFX_EXT_CLASS CDND_Manager
{
public:
	CDND_Manager(void);
	~CDND_Manager(void);

private:
	static CDND_Manager* _instance;// ½Ì±ÛÅæ(Singleton) - ¸Þ¸ð¸®¿¡ ÇÑ¹ø¸¸ ¶ç¿ò
public:
	static CDND_Manager* Instance();

	CString		MyPath();
	CString		m_strFileName;

public:
	CString							m_strSchema_V;
	CString							m_strFile_V;

	stSVG_Page						m_st_SVG_Page;
	stSVG_G							m_st_SVG_G;
	stSVG_Layer						m_st_SVG_Layer;

	CDND_ObjectArray				m_Array_DNDObject;

	CDND_ObjectArray				m_Array_DND_Switch;
	CDND_ObjectArray				m_Array_DND_Connect;
	CDND_ObjectArray				m_Array_DND_Text;

	CKASIM_ND_Array					m_Array_KASIM_ND;
	int								m_nDndMessageBox;

	void							SVG_Delete(); //»èÁ¦?
	void							SVG_SaveAs();
	void							SVG_LoadAs();
	void							SVG_AutoLoadAs();


	CDND_Object*					Create_DND_Object(CString strType);
	CDND_Object*					Add_DND_Obj_Connect(CPoint pt);
	CDND_Object*					Add_DND_Obj_Switch(CPoint pt,int nResourceID);
	CDND_Object*					Add_DND_Obj_Text(CPoint pt);

	void							Check_MaxID();
	void							Check_Connect_CEQID();
	CString							Get_Switch_CEQID(CString szBLOCK);
	CString							Get_Switch_CEQID1(CString szBLOCK);


	void							Read_SVG_Page(CMarkup* pxml);
	void							Read_SVG_G(CMarkup* pxml);
	void							Read_SVG_Layer(CMarkup* pxml);
	BOOL							Read_SVG_File(CMarkup* pxml);

	void							Write_SVG_Page(CMarkup* pxml);
	void							Write_SVG_G(CMarkup* pxml);
	void							Write_SVG_Layer(CMarkup* pxml);
	void							Write_SVG_File(CMarkup* pxml);


	void							Draw_DND(Graphics &graphics, CPoint ptDraw, CRect rectShow, double dZoomValue, double dScale_x = 1., double dScale_y = 1.);

	CDND_Object*					GetDNDObject2Point(CPoint pt, CDND_Object* pSelect, BOOL bConnect);
	CDND_Object*					GetDNDObject2Point_Cancel(CPoint pt, CDND_Object* pSelect, BOOL bConnect);
	CDND_Object*					GetDNDObject2ID(CString strID);
	CDND_Object*					GetDNDObject2_KASIM_ID(int nID); //KASIM BRÀ» Ã£¾Æº¼±î???¤¤
	void							GetDNDObject2NM(CString strNM, CListCtrl *pList);
	void							GetDNDObject2CEQ(CString strNM, CListCtrl *pList);
	void							GetDNDObject2CUSTOMER_NO(CString strNM, CListCtrl *pList);

	CDND_Object*					SVG_KASIM_Association();
	CDND_Object*					SVG_KASIM_Association_Index();

	int								Get_CBSW_TYPE(CDND_Switch* pSwitch);
	void							Get_ND_Array_Insert( CString stCEQID, int nNDID, int nCBSWID, int nINDEX, int nSVRID);
public:
	int								m_nMaxID_Text;
	int								m_nMaxID_Connect;
	int								m_nMaxID_Group;
	int								m_nMaxID_Block;

public:
	int								m_nMax_LNSEC_table;
	int								m_nMax_BR_table;
	int								m_nMax_CBSW_table;
	int								m_nMax_HVCUS_table;
	int								m_nMax_GEN_table;
	int								m_nMax_GND_table;
	int								m_nMax_ND_table;
	int								m_nMax_IJ_table;
	int								m_nMax_LD_table;
	int								m_nMax_ESS_table;
	int								m_nMax_PRDE_table;
	int								m_nMax_SVR_table;
	int								m_nMax_SS_table;
	int								m_nMax_MTR_table;
	int								m_nHold_SNVID;
	int								m_nMax_GENUNIT_table;
	int								m_nMax_DL_table;

	//±èÁ¾¹Î
public:
	CProgress_bar *m_pProgress_barDLG; 
 	CMap<CString, LPCTSTR, CString, LPCTSTR>m_map_Connrct_Switch;


	void	Get_ND_BR_Arry(int nNextNDIdx, CDND_Switch *pSwitch, int Index);
	void	Get_GenUnit(int nNextGENIdx, CDND_Switch *pSwitch);
	int		GetBrType(int nBrIdx);


};