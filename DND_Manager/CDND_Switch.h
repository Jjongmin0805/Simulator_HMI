#pragma once
#include "CDND_Object.h"

struct stKASIM_CBSW
{
	int m_nCBSWID;
	int m_nCBSW_Fnd;
	int m_nCBSW_Tnd;
	int m_nCBSW_PRDE;
	int m_nCBSW_NORSTAT;

	CArray<int, int&> stKASIM_CBSW_BR_Arry;
};

struct stKASIM_GEN
{
	int m_nGENID;
	int m_nGEN_ND;
	int m_nGEN_BR;
	int m_nGEN_IJ;
	int m_nGEN_PRDE;
	int m_nGEN_ESS;

	CArray<CString, CString&> stKASIM_GEN_CUSTNO_Arry;
};


struct stKASIM_HVCUS
{
	int m_nHVCUSID;
	int m_nHVCUS_ND;
	int m_nHVCUS_BR;
	int m_nHVCUS_IJ;
	int m_nHVCUS_PRDE;
	double m_dHVCUS_CON_KVA;

	//CArray<int, int&> stKASIM_HVCUS_BR_Arry;
};

struct stKASIM_ND
{
	int m_nNDID;

	CArray<int, int&> stKASIM_ND_BR_Arry;
};

struct stKASIM_SUBS
{
	int m_nSUBSID;
	int m_nGENID;
	int m_nIJID;
	int m_nNDID;
	//
	int m_nPRDEID;
	int m_nLNSECID;
	int m_nBRID;
	int m_nBRNDID;
	//
};

struct stKASIM_MTR
{
	int m_nMTRID;
	int m_nTRID;
	int m_nNDID;
};

struct stKASIM_DS_CBSW
{
	int m_nCBSWID;
	int m_nCBSW_Fnd;
	int m_nCBSW_PRDE;
};


struct stKASIM_SVR
{
	int m_nSVRID;
	int m_nSVR_Fnd;
	int m_nSVR_Tnd;
	int m_nSVR_BRID;
	int m_nSVR_FBR;
	int m_nSVR_TBR;

	CArray<int, int&> stKASIM_SVR_BR_Arry;

};



class CDND_Switch :
	public CDND_Object
{
public:
	CDND_Switch(void);
	~CDND_Switch(void);

	virtual		void					SetObjectData(CMarkup* pxml);
	virtual		void					GetObjectData(CMarkup* pxml, int&  nDrawOrder);

	virtual		void					Draw_Object(Graphics &graphics, CPoint ptDraw, double dZoomValue
													, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		void					Draw_Object_Select(Graphics &graphics, CPoint ptDraw, double dZoomValue
															, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		void					Draw_Object_Select_Move(Graphics &graphics, CPoint ptDraw, double dZoomValue
										, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));


	virtual		void					Draw_Object_Select_Cancel(Graphics &graphics, CPoint ptDraw, double dZoomValue
										, double dScale_x = 1., double dScale_y = 1., double dAngle = 0., CString strInnerText = _T(""));

	virtual		void					Draw_Object_Move(Graphics &graphics, CPoint ptDraw, double dZoomValue
														, double dScale_x = 1., double dScale_y = 1., double dAngle = 0.) ;

	virtual		BOOL					Check2DwawRect(CRect rDraw, double dZoomValue) ;
	virtual		CDND_Object*			Select2Point(CPoint pt, CDND_Object* pSelect);
	virtual		CDND_Object*			Select2Point_Cancel(CPoint pt, CDND_Object* pSelect);
	virtual		void					SetEdit_Move(CPoint pt) ;

	virtual		void					SetEdit_InitData(int nID, CPoint pt, int nResourceID = -1) ;
	virtual		void					SetEdit_InitData_KASIM_MU_CBSW(int nID, int nNd ,int nINDEX, int nCBSWt_Type, int nPRDEID);
	virtual		void					SetEdit_InitData_KASIM_CBSW(int nCBSWID, int nFNDID, int nTNDID, int nPRDEID, int nSwType);
	virtual		void					SetEdit_InitData_KASIM_ND(int nID);
	//GEN
	virtual		void					SetEdit_InitData_KASIM_GEN(int nGEN_ID, int nND_ID, int nIJ_ID, int nPRDE_ID);
	//
	virtual		void					SetEdit_InitData_KASIM_SVR(int nSVR_ID, int nFNDID, int nTNDID, int nBR_ID);
	virtual		void					SetEdit_InitData_KASIM_HVCUS(int nHVCUS_ID, int nND_ID , int nIJ_ID , int nPRDE_ID);
	virtual		void					SetEdit_InitData_KASIM_SUBS(int nSSID, int nGENID, int nMTRID, int nTRID, int nBRID, int nNDID, int nPRDEID, int nIJID );

	//
	virtual     void					Set_NEW_InitData_KASIM_CBSW(CString stKASIM_NM, CString stCEQID, CString stMUCEQID, int nCBSWID, int nFNDID, int nTNDID, int nMUSWINDEX, int nCBSWt_Type, int nPRDE);
	virtual     void					Set_NEW_InitData_KASIM_CBSW_DL(CString stKASIM_NM, CString stCEQID, CString stMUCEQID, int nCBSWID, int nFNDID, int nTNDID, int nMUSWINDEX, int nCBSWt_Type, int nPRDE, CString stKASIM_DL, int nDLID);
	virtual		void					Set_NEW_InitData_KASIM_ND(CString stKASIM_NM, CString stCEQID, int nID, int nFNDID, int nTNDID, int nIJDID,  int nSNVID, int nType);
	virtual		void					Set_NEW_InitData_KASIM_GND(int nID);
	
	//GEN
	virtual		void					Set_NEW_InitData_KASIM_GEN_STA(CString stKASIM_NM, CString stCEQID, int nID, int nNDID, int nIJID, int nPRDEID, int nGenType, double dGEN_MWLMMX, int nGEN_TREXCL, int nGENUNITID);
	virtual		void					Set_NEW_InitData_KASIM_GEN_DYN_MEA(int nGEN_ID);
	virtual		void					Set_NEW_InitData_KASIM_GEN_DYN_UIN(int nGEN_ID, double dGEN_ITR_CAP, int nGEN_ITR_WDC, double dGEN_ITR_X, int nGEN_MACH_TYPE);
	virtual		void					Set_NEW_InitData_KASIM_GEN_DYN_VVOO(int nGEN_ID);
	virtual		void					Set_NEW_InitData_KASIM_GEN_DYN_PDVRO(int nGEN_ID);

	virtual		void					Set_NEW_InitData_KASIM_SVR(CString stKASIM_NM, CString stCEQID, int nID, int nFNDID, int nTNDID, int nBRID);
	virtual		void					Set_NEW_InitData_KASIM_HVCUS(CString stKASIM_NM, CString stCEQID, int nID, int nNDID, int nIJID, int nPRDEID);
	virtual		void					Set_NEW_InitData_KASIM_PRDE(CString stKASIM_NM, int nID);
	virtual		void					Set_NEW_InitData_KASIM_LD(CString stKASIM_NM, int nID, int nNDID, int nIJID);
	virtual		void					Set_NEW_InitData_KASIM_IJ(CString stKASIM_NM, int nID, int nNDID, int nIJ_II_EQUTY);
	virtual		void					Set_NEW_InitData_KASIM_ESS(int nID);
	virtual		void					Set_NEW_InitData_KASIM_SVR_BR(CString stKASIM_NM, int nBRID, int nFnd, int nTnd);

	virtual		void					Set_NEW_InitData_KASIM_SS_STA(CString stKASIM_NM, CString stCEQID, int nSSID, int nGENID, int nIJID, int nNDID, int nPRDEID);
	virtual		void					Set_NEW_InitData_KASIM_SS_DYN_UIN(int nSSID);
	virtual		void					Set_NEW_InitData_KASIM_SS_DYN_NCPO(int nSSID);
	virtual		void					Set_NEW_InitData_KASIM_SS_DYN_RPFO(int nSSID);
	virtual		void					Set_NEW_InitData_KASIM_SS_DYN_VVOO(int nSSID);
	virtual		void					Set_NEW_InitData_KASIM_SS_DYN_DNRO(int nSSID);


	virtual		void					Set_NEW_InitData_KASIM_MTR(CString stKASIM_NM, CString stCEQID, int nMTRID, int nTRID, int nBRID, int nNDID, int nSSID, int nSSFNDID);



	virtual		void					SetEdit_InitData_Devref(int nID, CPoint pt);

	CRect								GetRect_Real();

	//void							GetDelete_BR_Array(int nID);

public:
	CString							m_strRoundbox;
	CRect							m_rect_Roundbox;

	
	///////////////////////////// MULTI
	CDND_Object*					m_pParent; 
	CDND_ObjectArray				m_Array_Multi;
	CSB_ObjectArray					m_Array_SBObject;


	stKASIM_CBSW					m_st_Kasim_CBSW_Info;
	stKASIM_GEN						m_st_Kasim_GEN_Info;
	stKASIM_HVCUS					m_st_Kasim_HVCUS_Info;
	stKASIM_ND						m_st_Kasim_ND_Info;
	stKASIM_SVR						m_st_Kasim_SVR_Info;
	stKASIM_SUBS					m_st_Kasim_SUBS_Info;
	stKASIM_MTR						m_st_Kasim_MTR_Info;
	stKASIM_DS_CBSW					m_st_Kasim_DS_CBSW_Info;


};

