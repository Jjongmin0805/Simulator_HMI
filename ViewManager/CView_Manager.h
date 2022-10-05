#pragma once

#define			PCE_STUDY_EQUIP_RELAY					1
#define			PCE_STUDY_EQUIP_RC						2
#define			PCE_STUDY_EQUIP_EFI						3
#define			PCE_STUDY_EQUIP_CUSTOMER				4
#define			PCE_STUDY_EQUIP_GEN						5

#define			DRAW_SPLIT_MODE_TOP						0
#define			DRAW_SPLIT_MODE_BOTTOM					1
#define			DRAW_SPLIT_MODE_LEFT					2
#define			DRAW_SPLIT_MODE_RIGHT					3


class CView_Manager
{
public:
	CView_Manager(void);
	~CView_Manager(void);

private:
	static CView_Manager* _instance;// ½Ì±ÛÅæ(Singleton) - ¸Þ¸ð¸®¿¡ ÇÑ¹ø¸¸ ¶ç¿ò
public:
	static CView_Manager* Instance();

	void									DrawArea_Base(CDC* pDC, Graphics &graphics, CRect rectArea, BOOL bBottom = TRUE);
	void									DrawArea_List(CDC* pDC, Graphics &graphics, CRect rectArea, BOOL bBottom = TRUE);;
	void									DrawArea_Title(CDC* pDC, Graphics &graphics, CRect rectArea, CString strTitle, BOOL bMain = FALSE,CRect rectBack = CRect(0,0,0,0));
	void									DrawArea_Unit(CDC* pDC, Graphics &graphics, CRect rectArea, CString strUnit);
	void									Draw_Split(CDC* pDC, Graphics &graphics, CRect rectArea, int nMode);  ////////////// »óÇÏ ÁÂ¿ì 

	void									Draw_Setting_Tag(CDC* pDC, Graphics &graphics, CRect rectArea, int nType ,CString strTagName);  ////////////// »óÇÏ ÁÂ¿ì 

	//////////////////////
	void									GetRoundRectPath(Gdiplus::GraphicsPath* gp, int x, int y, int width, int height, int radius);




};

