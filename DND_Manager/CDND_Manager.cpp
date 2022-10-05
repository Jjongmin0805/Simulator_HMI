#include "pch.h"
#include "CDND_Manager.h"
#include "../SB_Manager/CSB_Manager.h"

#include "CProgress_bar.h"
#include "Resource.h"



CDND_Manager *CDND_Manager::_instance = NULL;

CDND_Manager::CDND_Manager(void)
{
	CoInitialize(NULL);

	m_nMaxID_Text = 0;
	m_nMaxID_Connect = 0;
	m_nMaxID_Group = 0;
	m_nMaxID_Block = 0;
	m_nDndMessageBox = 0; //이건 내가 메시지 확인하려고 만든 부분입 1 자동으로 불러올떄 2 수동으로 불러올때 
}

CDND_Manager::~CDND_Manager(void)
{
	CoUninitialize();

	for (int i = 0; i < m_Array_DNDObject.GetSize(); i++)
		delete m_Array_DNDObject.GetAt(i);
	m_Array_DNDObject.RemoveAll();

	for (int i = 0; i < m_Array_KASIM_ND.GetSize(); i++)
		delete m_Array_KASIM_ND.GetAt(i);
	m_Array_KASIM_ND.RemoveAll();
	//MAP 데이터 삭제
	m_map_Connrct_Switch.RemoveAll();
}

CDND_Manager* CDND_Manager::Instance()
{

	if (_instance == 0)
	{
		_instance = new CDND_Manager();
	}
	return _instance;
}


void CDND_Manager::SVG_Delete()
{
	
	m_Array_DND_Text.RemoveAll();
	
	m_Array_DND_Connect.RemoveAll();
	
	m_Array_DND_Switch.RemoveAll();
	for (int i = 0; i < m_Array_DNDObject.GetSize(); i++)
		delete m_Array_DNDObject.GetAt(i);
	m_Array_DNDObject.RemoveAll();
	   
	//
// 	CString stDate;
// 	POSITION pos = m_map_Connrct_Switch.GetStartPosition();
// 	while (pos)
// 	{
// 		m_map_Connrct_Switch.GetNextAssoc(pos, stDate, stDate);
// 	}
	m_map_Connrct_Switch.RemoveAll();

}

CString CDND_Manager::MyPath()
{
	CString slmpath;
	WCHAR szDirve[256], szDir[2048];
	WCHAR programpath[2048];

	memset(szDir, 0x00, sizeof(szDir));
	memset(szDirve, 0x00, sizeof(szDirve));
	GetModuleFileName(0, programpath, 2048);
/*	size_t sz;*/

	_wsplitpath_s(programpath, szDirve, 256, szDir, 2048, NULL, 0, NULL, 0);

	slmpath.Format(_T("%s%s"), szDirve, szDir);
	slmpath.Delete(slmpath.GetLength() - 1, 1);
	return slmpath;

}

void CDND_Manager::Read_SVG_Page(CMarkup* pxml)
{
	m_pProgress_barDLG->ADD_Progress(); // 3

	pxml->FindChildElem(_T("PAGE"));
	pxml->IntoElem();

	m_st_SVG_Page.st_Type = _wtoi(pxml->GetAttrib(_T("type")) );
	m_st_SVG_Page.st_strName = pxml->GetAttrib(_T("name"));
}

void CDND_Manager::Write_SVG_Page(CMarkup* pxml)
{
	pxml->AddElem(_T("PAGE"));
	pxml->AddAttrib(_T("type"), m_st_SVG_Page.st_Type);
	pxml->AddAttrib(_T("name"), m_st_SVG_Page.st_strName);
	pxml->IntoElem();
}

void CDND_Manager::Read_SVG_G(CMarkup* pxml)
{
	m_pProgress_barDLG->ADD_Progress(); // 4

	pxml->FindChildElem(_T("G"));
	pxml->IntoElem();
	
	m_st_SVG_G.st_strName = pxml->GetAttrib(_T("name"));
	m_st_SVG_G.st_dX = _wtof(pxml->GetAttrib(_T("x")) );
	m_st_SVG_G.st_dY = _wtof(pxml->GetAttrib(_T("y")));
	m_st_SVG_G.st_dWidth = _wtof(pxml->GetAttrib(_T("w")));
	m_st_SVG_G.st_dHeight = _wtof(pxml->GetAttrib(_T("h")));
	m_st_SVG_G.st_strBG_Color = pxml->GetAttrib(_T("bgc"));
}

void CDND_Manager::Write_SVG_G(CMarkup* pxml)
{
	CString strData[4];
	strData[0].Format(_T("%.1lf"), m_st_SVG_G.st_dX);
	strData[1].Format(_T("%.1lf"), m_st_SVG_G.st_dY);
	strData[2].Format(_T("%.0lf"), m_st_SVG_G.st_dWidth);
	strData[3].Format(_T("%.0lf"), m_st_SVG_G.st_dHeight);


	pxml->AddElem(_T("G"));
	pxml->AddAttrib(_T("name"), m_st_SVG_G.st_strName);
	pxml->AddAttrib(_T("x"), strData[0]);
	pxml->AddAttrib(_T("y"), strData[1]);
	pxml->AddAttrib(_T("w"), strData[2]);
	pxml->AddAttrib(_T("h"), strData[3]);
	pxml->AddAttrib(_T("bgc"), m_st_SVG_G.st_strBG_Color);
	pxml->IntoElem();
}

void CDND_Manager::Read_SVG_Layer(CMarkup* pxml)
{
	pxml->FindChildElem(_T("LAYER"));
	
	m_st_SVG_Layer.st_nID = _wtoi(pxml->GetAttrib(_T("id")));
	m_st_SVG_Layer.st_strName = pxml->GetAttrib(_T("name"));
	m_st_SVG_Layer.st_nType = _wtoi(pxml->GetAttrib(_T("type")));
	m_st_SVG_Layer.st_nShow = _wtoi(pxml->GetAttrib(_T("show")));
	m_st_SVG_Layer.st_nZoomLevelEnable = _wtoi(pxml->GetAttrib(_T("zoomlevelenable")));
	m_st_SVG_Layer.st_dZoom_start = _wtof(pxml->GetAttrib(_T("zoomlevelstart")));
	m_st_SVG_Layer.st_dZoom_end = _wtof(pxml->GetAttrib(_T("zoomlevelend")));
	m_st_SVG_Layer.st_strScript = pxml->GetAttrib(_T("script"));
}

void CDND_Manager::Write_SVG_Layer(CMarkup* pxml)
{
	CString strData[6];
	strData[0].Format(_T("%d"), m_st_SVG_Layer.st_nID);
	strData[1].Format(_T("%d"), m_st_SVG_Layer.st_nType);
	strData[2].Format(_T("%d"), m_st_SVG_Layer.st_nShow);
	strData[3].Format(_T("d"), m_st_SVG_Layer.st_nZoomLevelEnable);
	strData[4].Format(_T("%.6lf"), m_st_SVG_Layer.st_dZoom_start);
	strData[5].Format(_T("%.6lf"), m_st_SVG_Layer.st_dZoom_end);


	pxml->AddElem(_T("LAYER"));
	pxml->AddAttrib(_T("id"), strData[0]);
	pxml->AddAttrib(_T("name"), m_st_SVG_Layer.st_strName);
	pxml->AddAttrib(_T("type"), strData[1]);
	pxml->AddAttrib(_T("show"), strData[2]);
	pxml->AddAttrib(_T("zoomlevelenable"), strData[3]);
	pxml->AddAttrib(_T("zoomlevelstart"), strData[4]);
	pxml->AddAttrib(_T("zoomlevelend"), strData[5]);
	pxml->AddAttrib(_T("script"), m_st_SVG_Layer.st_strScript);
	pxml->IntoElem();
}

CDND_Object*		CDND_Manager::Create_DND_Object(CString strType)
{
	CDND_Object *pDNDObj = NULL;

	if(strType == _T("text"))
	{
		pDNDObj = new CDND_Text();
		pDNDObj->ObjectType_Set(DND_OBJTYPE_TEXT);
		m_Array_DNDObject.Add(pDNDObj);
		m_Array_DND_Text.Add(pDNDObj);
	}
	else if (strType == _T("CONNECT"))
	{
		pDNDObj = new CDND_Connect();
		pDNDObj->ObjectType_Set(DND_OBJTYPE_CONNECT);
		m_Array_DNDObject.Add(pDNDObj);
		m_Array_DND_Connect.Add(pDNDObj);
	}
	else if (strType == _T("MULTIBLOCK"))
	{
		pDNDObj = new CDND_Switch();
		pDNDObj->ObjectType_Set(DND_OBJTYPE_MULTIBLOCK);
		m_Array_DNDObject.Add(pDNDObj);
		m_Array_DND_Switch.Add(pDNDObj);
	}
	else
	{
		pDNDObj = new CDND_Switch();
		pDNDObj->ObjectType_Set(DND_OBJTYPE_BLOCK);
		m_Array_DNDObject.Add(pDNDObj);
		m_Array_DND_Switch.Add(pDNDObj);
	}

	return pDNDObj;

}

void CDND_Manager::SVG_AutoLoadAs()
{
	m_pProgress_barDLG = new CProgress_bar;
	m_pProgress_barDLG->Create(IDD_PROGRESS_BAR_DLG);
	m_pProgress_barDLG->ShowWindow(SW_SHOW);

	int nFrinder = 0;
	//20211005 김종민 추가 
	CFileFind finder;
	CString strPath;
	CString strExt;
	CString szRoute;
	BOOL bWoking;
	//
	CString strTitleName;
	CString strFilePath;
	CString strFileName;

	m_pProgress_barDLG->ADD_Progress(); // 1

	szRoute.Format(_T("\\Data\\CSVFile\\0\\ST\\*.*"));
	strPath = (MyPath() + szRoute);
	bWoking = finder.FindFile(strPath);
	while (bWoking)
	{
		bWoking = finder.FindNextFile();
		if (!finder.IsDots() && !finder.IsDirectory())
		{
			strPath = finder.GetFileName();
			AfxExtractSubString(strExt, strPath, 1, '.');
			if (strExt.CompareNoCase(_T("svg")) == 0)
			{
				nFrinder = 9999;

				strTitleName = finder.GetFileTitle();
				strFilePath = finder.GetFilePath();
				strFileName = finder.GetFileName();
				m_nDndMessageBox = 1;
				break;
			}
		}
	}
	if (nFrinder == 0)
	{
		CFileDialog FileDlg(TRUE, _T("SVG"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("SVG Data File(*.SVG)|*.SVG| All Files(*.*)|*.*|"));

		FileDlg.m_pOFN->lpstrInitialDir = (LPCWSTR)strPath;

		if (FileDlg.DoModal() != IDOK)
			return;

		strTitleName = FileDlg.GetFileTitle();
		strFilePath = FileDlg.GetPathName();
		strFileName = FileDlg.GetFileName();
	}

	m_strFileName = strFileName;
	CMarkup xml;

	if (!xml.Load(strFilePath))
	{
		return;
	}
	Read_SVG_File(&xml);
}

void CDND_Manager::SVG_LoadAs()
{
	CFileDialog FileDlg(TRUE, _T("SVG"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("SVG Data File(*.SVG)|*.SVG| All Files(*.*)|*.*|"));

	CString strPath;
	strPath = MyPath();
	FileDlg.m_pOFN->lpstrInitialDir = (LPCWSTR)strPath;

	if (FileDlg.DoModal() != IDOK)
		return;

	CString strTitleName = FileDlg.GetFileTitle();
	CString strFilePath = FileDlg.GetPathName();
	CString strFileName = FileDlg.GetFileName();

	m_strFileName = strFileName;

	CMarkup xml;

	if (!xml.Load(strFilePath))
	{
		return;
	}
	Read_SVG_File(&xml);
}

void CDND_Manager::SVG_SaveAs()
{
	CTime t = CTime::GetCurrentTime();
	CString strName;
	strName.Format(_T("KASIM_DataFile_%s"), t.Format(_T("%Y%m%d%H%M%S")));


	CFileDialog FileDlg(FALSE, _T("SVG"), _T("test"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("SVG Data File(*.SVG)|*.SVG|"));

	CString strPath, szRoute;

	szRoute.Format(_T("\\Data\\CSVFile\\0\\ST"));
	strPath = (MyPath() + szRoute);

	//strPath = MyPath();
	FileDlg.m_pOFN->lpstrInitialDir = (LPCWSTR)strPath;

	if (FileDlg.DoModal() != IDOK)
		return;

	CString strFilePath = FileDlg.GetPathName();
	CString strFileName = FileDlg.GetFileName();
	
	CMarkup xml;
	
	Write_SVG_File(&xml);
	
	xml.Save(strFilePath);
}

BOOL CDND_Manager::Read_SVG_File(CMarkup* pxml)
{
	m_pProgress_barDLG->ADD_Progress(); // 2

	BOOL b = pxml->FindElem(_T("CIMDFILE"));
	m_strSchema_V = pxml->GetAttrib(_T("schema-version"));
	m_strFile_V = pxml->GetAttrib(_T("file-version"));

	Read_SVG_Page(pxml);
	Read_SVG_G(pxml);

	CString strTagName;
	CString strSwitID, strKeyID;
	CDND_Object *pDNDObj;
	CDND_Switch* pMulti;
	while (pxml->FindChildElem())  /////////////// 임시처리 201113  레이어별 관리가 필요하다.
	{
		pxml->IntoElem();
		Read_SVG_Layer(pxml);
		while (pxml->FindChildElem())
		{
			pxml->IntoElem();
			strTagName = pxml->GetTagName();

			TRACE(_T("%s\n"), strTagName);

			pDNDObj = Create_DND_Object(strTagName);
			pDNDObj->SetObjectData(pxml);

			//여기서 작업을?
			if (strTagName == "BLOCK")
			{
				strSwitID = pxml->GetAttrib(_T("id"));
				strKeyID = pxml->GetAttrib(_T("keyid"));

				m_map_Connrct_Switch.SetAt(strSwitID, strKeyID);

			}
			if (strTagName == "MULTIBLOCK")
			{
				pMulti = (CDND_Switch*)pDNDObj;
				for (int k = 0; k < pMulti->m_Array_Multi.GetSize(); k++)
				{
					pDNDObj = pMulti->m_Array_Multi.GetAt(k);
					strSwitID = pDNDObj->m_str_id;
					strKeyID = pDNDObj->m_str_keyid;
					m_map_Connrct_Switch.SetAt(strSwitID, strKeyID);
				}
			}

			TRACE(_T("%s : %s\n"), strTagName, pDNDObj->Get_ID_Real());
			pxml->OutOfElem();
		}
		pxml->OutOfElem();
	}
	
	Check_MaxID();
	//20211123 SVG파일 읽어와서 CEQID찾으려고 하는부분
	Check_Connect_CEQID();
	return TRUE;
}

void CDND_Manager::Write_SVG_File(CMarkup* pxml)
{
	pxml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>\r\n"));
	pxml->AddElem(_T("CIMDFILE"));
	pxml->AddAttrib(_T("schema-version"),(MCD_CSTR) m_strSchema_V);
	pxml->AddAttrib(_T("file-version"), (MCD_CSTR)m_strFile_V);
	pxml->IntoElem();

	Write_SVG_Page(pxml);
	Write_SVG_G(pxml);
	Write_SVG_Layer(pxml);

	CDND_Object *pDNDObj;
	int nDrawOrder = 1;
	for (int i = 0; i < m_Array_DND_Text.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Text.GetAt(i);

		if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
			continue;

		pDNDObj->GetObjectData(pxml, nDrawOrder);

		nDrawOrder++;
	}

	for (int i = 0; i < m_Array_DND_Connect.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Connect.GetAt(i);

		if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
			continue;

		pDNDObj->GetObjectData(pxml, nDrawOrder);

		nDrawOrder++;
	}

	for (int i = 0; i < m_Array_DND_Switch.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Switch.GetAt(i);

		if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
			continue;

		pDNDObj->GetObjectData(pxml, nDrawOrder);

		nDrawOrder++;
	}
	pxml->OutOfElem();
	pxml->OutOfElem();
	pxml->OutOfElem();
	pxml->OutOfElem();
}

void CDND_Manager::Check_MaxID()
{
	m_pProgress_barDLG->ADD_Progress(); // 5

	CDND_Object* pDNDObj;
	CDND_Switch* pMulti,*pSub;
	
	CString strID;
	int		nID;
	int nPos,nLen,nCount; 

	for (int i = 0; i < m_Array_DNDObject.GetSize(); i++)
	{
		pDNDObj = m_Array_DNDObject.GetAt(i);

		nLen = pDNDObj->Get_ID_Real().GetLength();
		nPos = pDNDObj->Get_ID_Real().ReverseFind(_T('_')) +1;
		nCount = nLen - nPos;
		if (nPos == -1)
		{
			AfxMessageBox(_T("ID Err"));
			continue;
		}
		if (nCount > 8)
		{
			nCount = 8;
			nPos += 6;
		}
		strID = pDNDObj->Get_ID_Real().Right(nCount);
		nID = _wtoi(strID);

		if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_TEXT)
		{
			if (m_nMaxID_Text < nID)
				m_nMaxID_Text = nID;
		}
		else if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
		{
			if (m_nMaxID_Connect < nID)
				m_nMaxID_Connect = nID;
		}
		else if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
		{
			if (m_nMaxID_Group < nID)
				m_nMaxID_Group = nID;

			pMulti = (CDND_Switch*)pDNDObj;
			for (int k = 0; k < pMulti->m_Array_Multi.GetSize(); k++)
			{
				pSub = (CDND_Switch*)pMulti->m_Array_Multi.GetAt(k);

				nLen = pSub->Get_ID_Real().GetLength();
				nPos = pSub->Get_ID_Real().ReverseFind(_T('_'));
				nCount = nLen - nPos;
				if (nPos == -1)
				{
					AfxMessageBox(_T("ID Err"));
					continue;
				}
				if (nCount > 8)
				{
					nCount = 8;
					nPos += 6;
				}
				strID = pSub->Get_ID_Real().Right(nCount);
				nID = _wtoi(strID);
				
				if (m_nMaxID_Block < nID)
					m_nMaxID_Block = nID;
			}
		}
		else
		{
			if (m_nMaxID_Block < nID)
				m_nMaxID_Block = nID;
		}
	}
	m_nMaxID_Text += 1;
	m_nMaxID_Connect += 1;
	m_nMaxID_Group += 1;
	m_nMaxID_Block += 1;
}

void CDND_Manager::Check_Connect_CEQID()
{
	m_pProgress_barDLG->ADD_Progress(); // 6

	CDND_Connect * pConnect;
	CDND_Object * pDNDObj;

	CString CEQ1, CEQ2, CEQ3, CEQ4;
	for (int i = 0; i < m_Array_DND_Connect.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Connect.GetAt(i);
		pConnect = (CDND_Connect*)pDNDObj;
		
		pConnect->m_strID_CEQ_From = Get_Switch_CEQID(pConnect->m_strID_From);
		pConnect->m_strID_CEQ_To = Get_Switch_CEQID(pConnect->m_strID_To);
	}
}
CString CDND_Manager::Get_Switch_CEQID(CString szBLOCK)
{
	CString szCEQID;
	szCEQID.Format(_T(""));
	m_map_Connrct_Switch.Lookup(szBLOCK, szCEQID);
	if (szCEQID != "")
	{
		return szCEQID;
	}
	return 0;

// 	CDND_Switch * pSwitch;
// 	CDND_Object * pDNDObj;
// 	CDND_Switch * pMulti;
// 	for (int i = 0; i < m_Array_DND_Switch.GetSize(); i++)
// 	{
// 		pDNDObj = m_Array_DND_Switch.GetAt(i);
// 		pSwitch = (CDND_Switch*)pDNDObj;
// 
// 		if (pSwitch->m_str_id == szBLOCK)
// 		{
// 			return pSwitch->m_str_keyid;
// 		}
// 		if (pSwitch->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
// 		{
// 			for (int k = 0; k < pSwitch->m_Array_Multi.GetSize(); k++)
// 			{
// 				pMulti = (CDND_Switch*)pSwitch->m_Array_Multi.GetAt(k);
// 				if (pMulti->m_str_id == szBLOCK)
// 				{
// 					return pMulti->m_str_keyid;
// 				}
// 			}
// 		}
// 	}

}

CString CDND_Manager::Get_Switch_CEQID1(CString szBLOCK)
{
	CString strKeyID;
	strKeyID.Format(_T(""));
	m_map_Connrct_Switch.Lookup(szBLOCK, strKeyID);
	if (strKeyID == "")
	{
		int a = 0;
	}
	return strKeyID;
	
// 	CDND_Switch * pSwitch;
// 	CDND_Object * pDNDObj;
// 	CDND_Switch * pMulti;
// 	for (int i = 0; i < m_Array_DND_Switch.GetSize(); i++)
// 	{
// 		pDNDObj = m_Array_DND_Switch.GetAt(i);
// 		pSwitch = (CDND_Switch*)pDNDObj;
// 
// 		if (pSwitch->m_str_id == szBLOCK)
// 		{
// 			return pSwitch->m_str_keyid;
// 		}
// 		if (pSwitch->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
// 		{
// 			for (int k = 0; k < pSwitch->m_Array_Multi.GetSize(); k++)
// 			{
// 				pMulti = (CDND_Switch*)pSwitch->m_Array_Multi.GetAt(k);
// 				if (pMulti->m_str_id == szBLOCK)
// 				{
// 					return pMulti->m_str_keyid;
// 				}
// 			}
// 		}
// 	}
// 
// 	return 0;
}

void CDND_Manager::Draw_DND(Graphics &graphics, CPoint ptDraw, CRect rectShow, double dZoomValue, double dScale_x /* = 1. */, double dScale_y /* = 1. */)
{
	CDND_Object *pDNDObj;
	for (int i = 0; i < m_Array_DND_Text.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Text.GetAt(i);

		if(pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
			continue;

		if (pDNDObj->Check2DwawRect(rectShow,dZoomValue) )
		{
			pDNDObj->Draw_Object(graphics,ptDraw,dZoomValue,dScale_x,dScale_y);
		}
	}

	for (int i = 0; i < m_Array_DND_Connect.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Connect.GetAt(i);

		if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
			continue;

		if (pDNDObj->Check2DwawRect(rectShow, dZoomValue))
		{
			pDNDObj->Draw_Object(graphics, ptDraw, dZoomValue, dScale_x, dScale_y);
		}
	}

	for (int i = 0; i < m_Array_DND_Switch.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Switch.GetAt(i);

		if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
			continue;

		if (pDNDObj->Check2DwawRect(rectShow, dZoomValue))
		{
			pDNDObj->Draw_Object(graphics, ptDraw, dZoomValue, dScale_x, dScale_y);
		}
	}
}

CDND_Object*	CDND_Manager::GetDNDObject2Point(CPoint pt, CDND_Object* pSelect,BOOL bConnect)
{
	CDND_Object *pDNDObj;
	CDND_Object	*pSelectObj;
	for (int i = 0; i < m_Array_DND_Switch.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Switch.GetAt(i);

		if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
			continue;

		pSelectObj = pDNDObj->Select2Point(pt, pSelect);
		if (pSelectObj)
		{
			return pSelectObj;
		}
	}

	if (bConnect)
	{
		for (int i = 0; i < m_Array_DND_Connect.GetSize(); i++)
		{
			pDNDObj = m_Array_DND_Connect.GetAt(i);

			if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
				continue;

			pSelectObj = pDNDObj->Select2Point(pt, pSelect);
			if (pSelectObj)
			{
				return pSelectObj;
			}
		}
	}	

	for (int i = 0; i < m_Array_DND_Text.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Text.GetAt(i);

		if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
			continue;

		pSelectObj = pDNDObj->Select2Point(pt, pSelect);
		if (pSelectObj)
		{
			return pSelectObj;
		}
	}
	return NULL;
}

CDND_Object*	CDND_Manager::GetDNDObject2Point_Cancel(CPoint pt, CDND_Object* pSelect, BOOL bConnect)
{
	CDND_Object *pDNDObj;
	CDND_Object	*pSelectObj;
	for (int i = 0; i < m_Array_DND_Switch.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Switch.GetAt(i);

		if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
			continue;

		pSelectObj = pDNDObj->Select2Point_Cancel(pt, pSelect);
		if (pSelectObj)
		{
			return pSelectObj;
		}
	}

	if (bConnect)
	{
		for (int i = 0; i < m_Array_DND_Connect.GetSize(); i++)
		{
			pDNDObj = m_Array_DND_Connect.GetAt(i);

			if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
				continue;

			pSelectObj = pDNDObj->Select2Point(pt, pSelect);
			if (pSelectObj)
			{
				return pSelectObj;
			}
		}
	}

	for (int i = 0; i < m_Array_DND_Text.GetSize(); i++)
	{
		pDNDObj = m_Array_DND_Text.GetAt(i);

		if (pDNDObj->GetEditType() == DND_OBJ_EDIT_DELETE)
			continue;

		pSelectObj = pDNDObj->Select2Point(pt, pSelect);
		if (pSelectObj)
		{
			return pSelectObj;
		}
	}
	return NULL;
}

CDND_Object*	CDND_Manager::GetDNDObject2ID(CString strID)
{
	CDND_Object *pDNDObj;
	CDND_Switch* pMulti;

	for (int i = 0; i < m_Array_DNDObject.GetSize(); i++)
	{
		pDNDObj = m_Array_DNDObject.GetAt(i);
		
		if (pDNDObj->Get_ID_Real().Compare(strID) == 0)
		{
			return pDNDObj;
		}

		if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
		{
			pMulti = (CDND_Switch*)pDNDObj;
			for (int k = 0; k < pMulti->m_Array_Multi.GetSize(); k++)
			{
				pDNDObj = pMulti->m_Array_Multi.GetAt(k);
				if (pDNDObj->Get_ID_Real().Compare(strID) == 0)
				{
					return pDNDObj;
				}
			}
		}		
	}
	return NULL;
}

CDND_Object*	CDND_Manager::GetDNDObject2_KASIM_ID(int nID)
{
	CDND_Object *pDNDObj;

	for (int i = 0; i < m_Array_DNDObject.GetSize(); i++)
	{
		pDNDObj = m_Array_DNDObject.GetAt(i);


		if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_CONNECT)
		{
			//노드일떄?
			CDND_Connect* pConnect = (CDND_Connect*)pDNDObj;
			if (pConnect->m_st_Kasim_LNsec_Info.m_nBRID == nID)
			{
				return pDNDObj;
			}
		}

	}
	return NULL;
}

void	CDND_Manager::GetDNDObject2NM(CString strNM, CListCtrl *pList)
{
	CDND_Object *pDNDObj;
	CDND_Switch* pMulti;
	CString strID;

	for (int i = 0; i < m_Array_DNDObject.GetSize(); i++)
	{
		pDNDObj = m_Array_DNDObject.GetAt(i);
		if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_TEXT) continue;

		if (pDNDObj->m_str_keyname.Find(strNM) > -1 )
		{			
			pList->InsertItem(pList->GetItemCount(), pDNDObj->Get_ID_Real());
			pList->SetItemText(pList->GetItemCount() - 1, 1, pDNDObj->m_str_keyname);
		}

		if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
		{
			pMulti = (CDND_Switch*)pDNDObj;
			for (int k = 0; k < pMulti->m_Array_Multi.GetSize(); k++)
			{
				pDNDObj = pMulti->m_Array_Multi.GetAt(k);
				if (pDNDObj->m_str_keyname.Find(strNM) > -1)
				{
					pList->InsertItem(pList->GetItemCount(), pDNDObj->Get_ID_Real());
					pList->SetItemText(pList->GetItemCount() - 1, 1, pDNDObj->m_str_keyname);
				}
			}
		}
	}
}

void	CDND_Manager::GetDNDObject2CEQ(CString strNM, CListCtrl *pList)
{
	CDND_Object *pDNDObj;
	CDND_Switch* pMulti;
	CString strID;

	for (int i = 0; i < m_Array_DNDObject.GetSize(); i++)
	{
		pDNDObj = m_Array_DNDObject.GetAt(i);
		if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_TEXT) continue;

		if (pDNDObj->m_str_keyid.Find(strNM) > -1)
		{
			pList->InsertItem(pList->GetItemCount(), pDNDObj->Get_ID_Real());
			pList->SetItemText(pList->GetItemCount() - 1, 1, pDNDObj->m_str_keyid);
		}

		if (pDNDObj->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
		{
			pMulti = (CDND_Switch*)pDNDObj;
			for (int k = 0; k < pMulti->m_Array_Multi.GetSize(); k++)
			{
				pDNDObj = pMulti->m_Array_Multi.GetAt(k);
				if (pDNDObj->m_str_keyid.Find(strNM) > -1)
				{
					pList->InsertItem(pList->GetItemCount(), pDNDObj->Get_ID_Real());
					pList->SetItemText(pList->GetItemCount() - 1, 1, pDNDObj->m_str_keyid);
				}
			}
		}
	}
}

// CDND_Object*	CDND_Manager::GetDNDObjecttoNDINDEX(int nNDIndex)
// {
// 	CDND_Object *pDNDObj;
// 	for (int i = 0; i < m_Array_DNDObject.GetSize(); i++)
// 	{
// 		pDNDObj = m_Array_DNDObject.GetAt(i);
// 
// 		if (pDNDObj->m_nKASIM_ND_Index == nNDIndex)
// 		{
// 			return pDNDObj;
// 		}
// 	}
// 	return NULL;
// }


CDND_Object*	CDND_Manager::Add_DND_Obj_Switch(CPoint pt, int nResourceID)
{
	CSB_Manager* pSBMng = CSB_Manager::Instance();
	CSB_Object* pSBObj = pSBMng->GetBlock_SB2ResourceID(nResourceID);
	int nCentND = 0;
	int nCBSWt_Type = 0;
	if (pSBObj == NULL)
	{
		AfxMessageBox(_T("Symbol menu ID err !!")); ////////////////// 말이 안되긴 하는데
	}
	CString strType;

	if (pSBObj->ObjType_Get() == SBOBJECT_TYPE_MULTIBLOCK)
	{
		strType = _T("MULTIBLOCK");
	}
	else
	{
		strType = _T("BLOCK");
	}

	//설비 입력 해야 한다!!!!
	CDND_Switch* pDNDObj_New = (CDND_Switch*)Create_DND_Object(strType);
		

	//
	if (pSBObj->ObjType_Get() == SBOBJECT_TYPE_MULTIBLOCK)
	{
		pDNDObj_New->SetEdit_InitData(m_nMaxID_Group, pt, nResourceID);
		m_nMaxID_Group++;
		
		CDND_Switch* pMulti_M;
		for (int i = 0; i < pDNDObj_New->m_Array_Multi.GetSize(); i++)
		{
			pMulti_M = (CDND_Switch*)pDNDObj_New->m_Array_Multi.GetAt(i);

			if (pMulti_M->ObjectType_Get() == DND_OBJTYPE_MULTI_M)
			{
				pMulti_M->SetEdit_InitData_Devref(m_nMaxID_Block, pt);
				m_nMaxID_Block++;

				//설비 타입
				nCBSWt_Type = Get_CBSW_TYPE(pDNDObj_New);

				//FND
				if ( i == 0)
				{
					pMulti_M->SetEdit_InitData_KASIM_MU_CBSW(m_nMax_CBSW_table, m_nMax_ND_table, i, nCBSWt_Type, m_nMax_PRDE_table); //이름 key 추가 
					m_nMax_CBSW_table++;

					pMulti_M->Set_NEW_InitData_KASIM_ND(pMulti_M->m_str_keyname, pMulti_M->m_str_keyid, m_nMax_CBSW_table, m_nMax_ND_table, m_nMax_ND_table + 1, 0, m_nHold_SNVID, 1); //1.cbsw 2.lnsec 3.gen 4.hvcus 5.junction
					Get_ND_Array_Insert(pMulti_M->m_str_keyid,m_nMax_ND_table, m_nMax_CBSW_table, 1, 0);
					m_nMax_ND_table++;
					m_nMax_GND_table++;
					nCentND = m_nMax_ND_table;
				}
				else
				{
					pMulti_M->SetEdit_InitData_KASIM_MU_CBSW(m_nMax_CBSW_table, m_nMax_ND_table +1, i, nCBSWt_Type, m_nMax_PRDE_table); //이름 key 추가 
					m_nMax_CBSW_table++;

					pMulti_M->Set_NEW_InitData_KASIM_ND(pMulti_M->m_str_keyname, pMulti_M->m_str_keyid, m_nMax_CBSW_table, nCentND, m_nMax_ND_table + 1, 0, m_nHold_SNVID, 8); //1.cbsw 2.lnsec 3.gen 4.hvcus 5.junction
					Get_ND_Array_Insert(pMulti_M->m_str_keyid, m_nMax_ND_table + 1, m_nMax_CBSW_table,  2, 0);
					 //TND
					m_nMax_ND_table++;
					m_nMax_GND_table++;
				}

				

				if (nCBSWt_Type == 2 || nCBSWt_Type == 5 || nCBSWt_Type == 6 || nCBSWt_Type == 1)
				{
					pMulti_M->Set_NEW_InitData_KASIM_PRDE(pMulti_M->m_str_keyname, m_nMax_PRDE_table);
					m_nMax_PRDE_table++;
				}

			}
		}
	}
	else
	{
		pDNDObj_New->SetEdit_InitData(m_nMaxID_Block, pt, nResourceID);
		m_nMaxID_Block++;
		
		//설비 타입
		nCBSWt_Type = Get_CBSW_TYPE(pDNDObj_New);

		//KASIM 데이터
		//SWITCH - BREAKER - TR - COMPSWITCH - 
		if (pDNDObj_New->m_str_psrtype == "SWITCH" || pDNDObj_New->m_str_psrtype == "BREAKER" || pDNDObj_New->m_str_psrtype == "RECLOSER" || pDNDObj_New->m_str_psrtype == "CB")
		{
			pDNDObj_New->SetEdit_InitData_KASIM_CBSW(m_nMax_CBSW_table, m_nMax_ND_table, m_nMax_ND_table+1, m_nMax_PRDE_table, nCBSWt_Type); //이름 key 추가 
			
			if(nCBSWt_Type == 2 || nCBSWt_Type == 5 || nCBSWt_Type == 6 )
			{
				pDNDObj_New->Set_NEW_InitData_KASIM_CBSW(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, 0, m_nMax_CBSW_table, m_nMax_ND_table, m_nMax_ND_table + 1, 0, nCBSWt_Type, m_nMax_PRDE_table);
			}
			else if( nCBSWt_Type == 1)
			{
				pDNDObj_New->Set_NEW_InitData_KASIM_CBSW_DL(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, 0, m_nMax_CBSW_table, 0, m_nMax_ND_table , 0, nCBSWt_Type, m_nMax_PRDE_table, pDNDObj_New->m_str_keyid_dl, m_nMax_DL_table);
				m_nMax_DL_table++;
			}
			else
			{
				pDNDObj_New->Set_NEW_InitData_KASIM_CBSW(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, 0, m_nMax_CBSW_table, m_nMax_ND_table, m_nMax_ND_table + 1, 0, nCBSWt_Type, 0);
			}
			pDNDObj_New->Set_NEW_InitData_KASIM_ND(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_CBSW_table, m_nMax_ND_table, m_nMax_ND_table+1,0, m_nHold_SNVID, 1); //1.cbsw 2.lnsec 3.gen 4.hvcus 5.junction

			Get_ND_Array_Insert(pDNDObj_New->m_str_keyid, m_nMax_ND_table, m_nMax_CBSW_table, 3, 0);

			m_nMax_CBSW_table++; 
			//FND
			m_nMax_ND_table++; 
			m_nMax_GND_table++;
			//TND
			m_nMax_ND_table++; 
			m_nMax_GND_table++;
			//if (pDNDObj_New->m_str_psrtype == "RECLOSER" || pDNDObj_New->m_str_psrtype == "CB")
			if (nCBSWt_Type == 2 || nCBSWt_Type == 5 || nCBSWt_Type == 6 || nCBSWt_Type == 1)
			{
				pDNDObj_New->Set_NEW_InitData_KASIM_PRDE(pDNDObj_New->m_str_keyname, m_nMax_PRDE_table);
				m_nMax_PRDE_table++;
			}
		}
		//JUNCTION - CABLEPOLE
		else if (pDNDObj_New->m_str_psrtype == "JUNCTION" || pDNDObj_New->m_str_psrtype == "CABLEPOLE")
		{
			pDNDObj_New->SetEdit_InitData_KASIM_ND(m_nMax_ND_table); //이름 key 추가  
			pDNDObj_New->Set_NEW_InitData_KASIM_ND(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, 0, m_nMax_ND_table, m_nMax_ND_table, 0, m_nHold_SNVID, 5); //1.cbsw 2.lnsec 3.gen 4.hvcus 5.junction
			m_nMax_ND_table++; 
			m_nMax_GND_table++;
		}
		//CONSUMER
		else if (pDNDObj_New->m_str_psrtype == "CONSUMER")
		{
			pDNDObj_New->SetEdit_InitData_KASIM_HVCUS(m_nMax_HVCUS_table, m_nMax_ND_table, m_nMax_IJ_table, m_nMax_PRDE_table); //이름 key 추가 
			//
			pDNDObj_New->Set_NEW_InitData_KASIM_HVCUS(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_HVCUS_table, m_nMax_ND_table, m_nMax_IJ_table, m_nMax_PRDE_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_IJ(pDNDObj_New->m_str_keyname, m_nMax_IJ_table, m_nMax_ND_table, 8);
			pDNDObj_New->Set_NEW_InitData_KASIM_ND(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_HVCUS_table, m_nMax_ND_table, m_nMax_ND_table, m_nMax_IJ_table, m_nHold_SNVID,  4); //1.cbsw 2.lnsec 3.gen 4.hvcus 5.junction
			pDNDObj_New->Set_NEW_InitData_KASIM_PRDE(pDNDObj_New->m_str_keyname, m_nMax_PRDE_table);
			//
			m_nMax_HVCUS_table++;
			m_nMax_ND_table++;
			m_nMax_IJ_table++;
			m_nMax_GND_table++;
			m_nMax_PRDE_table++;
		}
		//GENERATEUNIT
		else if (pDNDObj_New->m_str_psrtype == "GENERATEUNIT" || pDNDObj_New->m_str_psrtype == "DG" || pDNDObj_New->m_str_psrtype == "ENERGYSOURCEEQ")
		{
			pDNDObj_New->SetEdit_InitData_KASIM_GEN(m_nMax_GEN_table, m_nMax_ND_table, m_nMax_IJ_table, m_nMax_PRDE_table); //이름 key 추가 
			//
			pDNDObj_New->Set_NEW_InitData_KASIM_GEN_STA(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_GEN_table, m_nMax_ND_table, m_nMax_IJ_table, m_nMax_PRDE_table, 5 , 0, 2, m_nMax_GENUNIT_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_GEN_DYN_MEA(m_nMax_GEN_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_GEN_DYN_UIN(m_nMax_GEN_table , 0, 1, 0, 1 );
			pDNDObj_New->Set_NEW_InitData_KASIM_GEN_DYN_VVOO(m_nMax_GEN_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_GEN_DYN_PDVRO(m_nMax_GEN_table);

			pDNDObj_New->Set_NEW_InitData_KASIM_IJ(pDNDObj_New->m_str_keyname, m_nMax_IJ_table, m_nMax_ND_table, 4);
			pDNDObj_New->Set_NEW_InitData_KASIM_ND(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_GEN_table, m_nMax_ND_table, m_nMax_ND_table, m_nMax_IJ_table, m_nHold_SNVID, 3); //1.cbsw 2.lnsec 3.gen 4.hvcus 5.junction
			pDNDObj_New->Set_NEW_InitData_KASIM_PRDE(pDNDObj_New->m_str_keyname, m_nMax_PRDE_table);
			//
			m_nMax_GEN_table++;
			m_nMax_ND_table++; 
			m_nMax_GND_table++;
			m_nMax_IJ_table++;
			//m_nMax_ESS_table++;
			m_nMax_PRDE_table++;
			m_nMax_GENUNIT_table++;
		}
		//SVR
		else if (pDNDObj_New->m_str_psrtype == "SVR" )
		{
			pDNDObj_New->SetEdit_InitData_KASIM_SVR(m_nMax_SVR_table, m_nMax_ND_table, m_nMax_ND_table+1 , m_nMax_BR_table); //이름 key 추가 
			//
			pDNDObj_New->Set_NEW_InitData_KASIM_SVR(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_SVR_table, m_nMax_ND_table, m_nMax_ND_table + 1, m_nMax_BR_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_ND(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_SVR_table, m_nMax_ND_table, m_nMax_ND_table + 1, m_nMax_BR_table, m_nHold_SNVID, 6); //1.cbsw 2.lnsec 3.gen 4.hvcus 5.junction 6.
			//BR작업중																																								 
			pDNDObj_New->Set_NEW_InitData_KASIM_SVR_BR(pDNDObj_New->m_str_keyname,  m_nMax_BR_table, m_nMax_ND_table, m_nMax_ND_table + 1);
			//
			Get_ND_Array_Insert(pDNDObj_New->m_str_keyid, m_nMax_ND_table, m_nMax_BR_table, 4 , m_nMax_SVR_table);


			m_nMax_SVR_table++;
			//FND
			m_nMax_ND_table++;
			m_nMax_GND_table++;
			//TND
			m_nMax_ND_table++;
			m_nMax_GND_table++;
			//BR
			m_nMax_BR_table++;
		}
		else if (pDNDObj_New->m_str_psrtype == "SUBSTATION")
		{			
			////////////////////////////////////////////////////////////////////////////////

			//m_nMax_SVR_table > TR입니다.
			// MTR 개수 // SSID // GENID // MTRID // TRID // BRID // NDID // PRDEID 
 			pDNDObj_New->SetEdit_InitData_KASIM_SUBS(m_nMax_SS_table, m_nMax_GEN_table, m_nMax_MTR_table, m_nMax_SVR_table, m_nMax_BR_table, m_nMax_ND_table , m_nMax_PRDE_table , m_nMax_IJ_table );
 			pDNDObj_New->Set_NEW_InitData_KASIM_SS_STA(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_SS_table, m_nMax_GEN_table, m_nMax_IJ_table,  m_nMax_ND_table, m_nMax_PRDE_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_SS_DYN_UIN(m_nMax_SS_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_SS_DYN_NCPO(m_nMax_SS_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_SS_DYN_RPFO(m_nMax_SS_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_SS_DYN_VVOO(m_nMax_SS_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_SS_DYN_DNRO(m_nMax_SS_table);
			//GEN
			pDNDObj_New->Set_NEW_InitData_KASIM_GEN_STA(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_GEN_table, m_nMax_ND_table, m_nMax_IJ_table, m_nMax_PRDE_table, 1 , 0 , 2 , m_nMax_GENUNIT_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_GEN_DYN_MEA(m_nMax_GEN_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_GEN_DYN_UIN(m_nMax_GEN_table , 0, 1, 0, 1);
			pDNDObj_New->Set_NEW_InitData_KASIM_GEN_DYN_VVOO(m_nMax_GEN_table);
			pDNDObj_New->Set_NEW_InitData_KASIM_GEN_DYN_PDVRO(m_nMax_GEN_table);
			//IJ
			pDNDObj_New->Set_NEW_InitData_KASIM_IJ(pDNDObj_New->m_str_keyname, m_nMax_IJ_table, m_nMax_ND_table, 4);
			//ND
			pDNDObj_New->Set_NEW_InitData_KASIM_ND(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_GEN_table, m_nMax_ND_table, m_nMax_ND_table, m_nMax_IJ_table, m_nHold_SNVID, 3); //1.cbsw 2.lnsec 3.gen 4.hvcus 5.junction
			//PRDE
			pDNDObj_New->Set_NEW_InitData_KASIM_PRDE(pDNDObj_New->m_str_keyname, m_nMax_PRDE_table);
			
			int nSSNDID = m_nMax_ND_table;

			m_nMax_GEN_table++;
			m_nMax_IJ_table++;
			m_nMax_PRDE_table++;
			//
			m_nMax_ND_table++;
			m_nMax_GND_table++;
			m_nMax_GENUNIT_table++;
			//변전소에서 기본 MTR1개 씩 추가 
			CString szMTRCEQID, stMTRNM;
			szMTRCEQID.Format(_T("9999179%07d"), m_nMax_MTR_table);
			stMTRNM.Format(_T("MTR%08d"), m_nMax_MTR_table);

			pDNDObj_New->Set_NEW_InitData_KASIM_MTR(stMTRNM, szMTRCEQID, m_nMax_MTR_table, m_nMax_SVR_table, m_nMax_BR_table, m_nMax_ND_table, m_nMax_SS_table, nSSNDID);
			
			m_nMax_SS_table++;
			m_nMax_MTR_table++;
			m_nMax_SVR_table++;
			m_nMax_BR_table++;
			m_nMax_ND_table++;
		}
		else
		{
			pDNDObj_New->SetEdit_InitData_KASIM_CBSW(m_nMax_CBSW_table, m_nMax_ND_table, m_nMax_ND_table + 1, 0, nCBSWt_Type); //이름 key 추가 
			pDNDObj_New->Set_NEW_InitData_KASIM_CBSW(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, 0, m_nMax_CBSW_table, m_nMax_ND_table, m_nMax_ND_table + 1, 0 , nCBSWt_Type, 0);
			pDNDObj_New->Set_NEW_InitData_KASIM_ND(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_CBSW_table, m_nMax_ND_table, m_nMax_ND_table + 1, 0, m_nHold_SNVID, 1 ); //1.cbsw 2.lnsec 3.gen 4.hvcus 5.junction

			m_nMax_CBSW_table++;
			//FND
			m_nMax_ND_table++; 
			m_nMax_GND_table++;
			//TND
			m_nMax_ND_table++; 
			m_nMax_GND_table++;
		}
	}
	return pDNDObj_New;
}

void  CDND_Manager::Get_ND_Array_Insert( CString stCEQID, int nNDID, int nCBSWID, int nINDEX, int nSVRID)
{
	CString stFndFK, stTndFK;

	CKASIM_ND* pND_Arry;
	CKASIM_ND* pND_Arry1;
	if (nINDEX == 1) //다회로 1번 스위치 2개의 노드 입력
	{
		//중심노드
		stFndFK.Format(_T("%s01"), stCEQID);
		pND_Arry = new CKASIM_ND;
		pND_Arry->nND_ID = nNDID;
		pND_Arry->nND_FBRID = 0;
		pND_Arry->nND_TBRID = 0;
		pND_Arry->nND_FCBSWID = nCBSWID;
		pND_Arry->nND_TCBSWID = 0;
		pND_Arry->nND_MUSW = 1111;  //중심노드는 제외 한다.
		pND_Arry->szND_CEQ.Format(_T("%s"), stCEQID);
		pND_Arry->szND_NDKey.Format(_T("%s"), stFndFK);
		m_Array_KASIM_ND.Add(pND_Arry);

		stTndFK.Format(_T("%s02"), stCEQID);
		pND_Arry1 = new CKASIM_ND;
		pND_Arry1->nND_ID = nNDID + 1;
		pND_Arry1->nND_FBRID = 0;
		pND_Arry1->nND_TBRID = 0;
		pND_Arry1->nND_FCBSWID = 0;
		pND_Arry1->nND_TCBSWID = nCBSWID;
		pND_Arry1->nND_MUSW = 9999;
		pND_Arry1->szND_CEQ.Format(_T("%s"), stCEQID);
		pND_Arry1->szND_NDKey.Format(_T("%s"), stTndFK);
		m_Array_KASIM_ND.Add(pND_Arry1);
	}
	else if (nINDEX == 2) //다회로 2번스위치 부터 ~1개 입력 
	{
		stFndFK.Format(_T("%s01"), stCEQID);
		pND_Arry = new CKASIM_ND;
		pND_Arry->nND_ID = nNDID;
		pND_Arry->nND_FBRID = 0;
		pND_Arry->nND_TBRID = 0;
		pND_Arry->nND_FCBSWID = 0;
		pND_Arry->nND_TCBSWID = nCBSWID;
		pND_Arry->nND_MUSW = 1111;  //중심노드는 제외 한다.
		pND_Arry->szND_CEQ.Format(_T("%s"), stCEQID);
		pND_Arry->szND_NDKey.Format(_T("%s"), stFndFK);
		m_Array_KASIM_ND.Add(pND_Arry);
	}
	else if (nINDEX == 3) //일반 스위치 2개 입력 
	{
		stFndFK.Format(_T("%s01"), stCEQID);
		pND_Arry = new CKASIM_ND;
		pND_Arry->nND_ID = nNDID;
		pND_Arry->nND_FBRID = 0;
		pND_Arry->nND_TBRID = 0;
		pND_Arry->nND_FCBSWID = nCBSWID;
		pND_Arry->nND_TCBSWID = 0;
		pND_Arry->nND_MUSW = 0;  //중심노드는 제외 한다.
		pND_Arry->szND_CEQ.Format(_T("%s"), stCEQID);
		pND_Arry->szND_NDKey.Format(_T("%s"), stFndFK);
		m_Array_KASIM_ND.Add(pND_Arry);

		stTndFK.Format(_T("%s02"), stCEQID);
		pND_Arry1 = new CKASIM_ND;
		pND_Arry1->nND_ID = nNDID + 1;
		pND_Arry1->nND_FBRID = 0;
		pND_Arry1->nND_TBRID = 0;
		pND_Arry1->nND_FCBSWID = 0;
		pND_Arry1->nND_TCBSWID = nCBSWID;
		pND_Arry1->nND_MUSW = 0;
		pND_Arry1->szND_CEQ.Format(_T("%s"), stCEQID);
		pND_Arry1->szND_NDKey.Format(_T("%s"), stTndFK);
		m_Array_KASIM_ND.Add(pND_Arry1);
	}
	else if (nINDEX == 4) //일반 스위치 2개 입력 
	{
		stFndFK.Format(_T("%s01"), stCEQID);
		pND_Arry = new CKASIM_ND;
		pND_Arry->nND_ID = nNDID;
		pND_Arry->nND_FBRID = nCBSWID;
		pND_Arry->nND_TBRID = 0;
		pND_Arry->nND_FCBSWID = 0;
		pND_Arry->nND_TCBSWID = 0;
		pND_Arry->nND_FSVRID = 0;
		pND_Arry->nND_TSVRID = 0;
		pND_Arry->nND_MUSW = 0;  //중심노드는 제외 한다.
		pND_Arry->szND_CEQ.Format(_T("%s"), stCEQID);
		pND_Arry->szND_NDKey.Format(_T("%s"), stFndFK);
		m_Array_KASIM_ND.Add(pND_Arry);

		stTndFK.Format(_T("%s02"), stCEQID);
		pND_Arry1 = new CKASIM_ND;
		pND_Arry1->nND_ID = nNDID + 1;
		pND_Arry1->nND_FBRID = 0;
		pND_Arry1->nND_TBRID = nCBSWID;
		pND_Arry1->nND_FCBSWID = 0;
		pND_Arry1->nND_TCBSWID = 0;
		pND_Arry1->nND_MUSW = 0;
		pND_Arry1->nND_FSVRID = 0;
		pND_Arry1->nND_TSVRID = 0;
		pND_Arry1->szND_CEQ.Format(_T("%s"), stCEQID);
		pND_Arry1->szND_NDKey.Format(_T("%s"), stTndFK);
		m_Array_KASIM_ND.Add(pND_Arry1);
	}
}

CDND_Object* CDND_Manager::Add_DND_Obj_Connect(CPoint pt)
{

	CDND_Connect* pDNDObj_New = (CDND_Connect*)Create_DND_Object(_T("CONNECT"));

	pDNDObj_New->SetEdit_InitData(m_nMaxID_Connect, pt);
	pDNDObj_New->SetEdit_InitData_KASIM(m_nMax_LNSEC_table, m_nMax_BR_table, m_nMax_IJ_table, m_nMax_LD_table);
	pDNDObj_New->Set_NEW_InitData_KASIM(pDNDObj_New->m_str_keyname, pDNDObj_New->m_str_keyid, m_nMax_LNSEC_table, m_nMax_BR_table, m_nMax_IJ_table, m_nMax_LD_table , 0, 0);

	m_nMaxID_Connect++;
	m_nMax_LNSEC_table++; //맥스 값 추가
	m_nMax_BR_table++;   //맥스 값 추가 
	m_nMax_IJ_table++;
	m_nMax_LD_table++;
	return pDNDObj_New;
}

CDND_Object*	CDND_Manager::Add_DND_Obj_Text(CPoint pt)
{
	CDND_Text* pDNDObj_New = (CDND_Text*)Create_DND_Object(_T("text"));

	pDNDObj_New->SetEdit_InitData(m_nMaxID_Text, pt);
	m_nMaxID_Text++;
	
	return pDNDObj_New;
}

/////////////////////////////////
CDND_Object* CDND_Manager::SVG_KASIM_Association()
{
	m_pProgress_barDLG->ADD_Progress(); // 6

	CDND_Object *pDNDObj;
	CDND_Switch *pSwitch;
	CDND_Connect *pConnect;

	int i = 0, j = 0;
	CString stKASIM_CEQ;
	CString stKASIM_LNSEC_CEQ;
	unsigned long long	ullCEQID(0U);
	
	//
	int nGenND = 0, nHvcusND = 0;
	int nFnd = 0, nTnd = 0;
	int nFBRID = 0, nTBRID = 0;
	int nKSIM_BRID = 0;
	int nPrdeID = 0;
	int nIJID = 0;
	int nLDID = 0;
	int nESSID = 0;
	int nBR_SI_FND = 0, nBR_SI_TND = 0;
	//
	int nFCBSW, nTCBSW;
	//
	stKASIM_LNsec* pLNsec = NULL;
	stKASIM_CBSW*  pCBSW = NULL;
	stKASIM_GEN*   pGEN = NULL;
	stKASIM_HVCUS* pHVCUS = NULL;
	stKASIM_ND*	   pND = NULL;
	stKASIM_SVR*   pSVR = NULL;
	stKASIM_SUBS*  pSUBS = NULL;
	CKASIM_ND* pND_Arry = NULL;

	CMap<CString, LPCTSTR, stKASIM_LNsec*, stKASIM_LNsec*>map_LNsec;
	CMap<int, int, int, int>map_LN_FND;
	CMap<int, int, int, int>map_LN_TND;
	CMap<CString, LPCTSTR, stKASIM_CBSW*, stKASIM_CBSW*>map_CBSW;
	CMap<CString, LPCTSTR, stKASIM_GEN*, stKASIM_GEN*>map_GEN;
	CMap<CString, LPCTSTR, stKASIM_HVCUS*, stKASIM_HVCUS*>map_HVCUS;
	CMap<CString, LPCTSTR, stKASIM_ND*, stKASIM_ND*>map_ND;
	CMap<CString, LPCTSTR, stKASIM_SVR*, stKASIM_SVR*>map_SVR;
	CMap<CString, LPCTSTR, stKASIM_SUBS*, stKASIM_SUBS*>map_SUBS;


	CString stFnd_CEQID, stTnd_CEQID;

	//LNSEC
	int nCount_LNSEC_table = theAppDataMng->GetTableRealCount(_T("lnsec_sta"));
	for (i = 1; i <= (int)nCount_LNSEC_table; i++)
	{
		//LNSEC
		ullCEQID = GETVALUE(unsigned long long, "lnsec_sta", "lnsec_ceqid", i);
		stKASIM_LNSEC_CEQ.Format(_T("%lld"), ullCEQID);
		nKSIM_BRID = GETVALUE(int, "lnsec_sta", "lnsec_ii_br", i);
		nFnd = GETVALUE(int, _T("br_sta"), _T("BR_II_FND"), nKSIM_BRID);
		nTnd = GETVALUE(int, _T("br_sta"), _T("BR_II_TND"), nKSIM_BRID);

		nBR_SI_FND = GETVALUE(int, _T("br_sta"), _T("BR_SI_FND"), nKSIM_BRID);
		nBR_SI_TND = GETVALUE(int, _T("br_sta"), _T("BR_SI_TND"), nKSIM_BRID);
		if (nFnd != 0)
		{
			ullCEQID = GETVALUE(unsigned long long, "ND_STA", "ND_CEQID", nFnd);
			stFnd_CEQID.Format(_T("%lld"), ullCEQID);
			nLDID = GETVALUE(int, _T("GND_STA"), _T("GND_HI_LD"), nFnd);
			if (nLDID != 0)
			{
				nIJID = GETVALUE(int, _T("LD_STA"), _T("LD_II_IJ"), nLDID);
			}
			//아..
			nFCBSW = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FCBSW"), nFnd);
			nTCBSW = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TCBSW"), nFnd);
			if (nFCBSW != 0 )
			{
				ullCEQID = GETVALUE(unsigned long long, "cbsw_sta", "cbsw_ceqid", nFCBSW);
				stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
				if (stFnd_CEQID != stKASIM_CEQ)
				{
					stFnd_CEQID.Format(_T("%s"), stKASIM_CEQ);
				}
			}
			if (nTCBSW != 0)
			{
				ullCEQID = GETVALUE(unsigned long long, "cbsw_sta", "cbsw_ceqid", nTCBSW);
				stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
				if (stFnd_CEQID != stKASIM_CEQ)
				{
					stFnd_CEQID.Format(_T("%s"), stKASIM_CEQ);
				}
			}
		}
		if (nTnd != 0)
		{
			ullCEQID = GETVALUE(unsigned long long, "ND_STA", "ND_CEQID", nTnd);
			stTnd_CEQID.Format(_T("%lld"), ullCEQID);
			nLDID = GETVALUE(int, _T("GND_STA"), _T("GND_HI_LD"), nTnd);
			if (nLDID != 0)
			{
				nIJID = GETVALUE(int, _T("LD_STA"), _T("LD_II_IJ"), nLDID);
			}
			//아..
			nFCBSW = GETVALUE(int, _T("ND_STA"), _T("ND_HI_FCBSW"), nTnd);
			nTCBSW = GETVALUE(int, _T("ND_STA"), _T("ND_HI_TCBSW"), nTnd);
			if (nFCBSW != 0)
			{
				ullCEQID = GETVALUE(unsigned long long, "cbsw_sta", "cbsw_ceqid", nFCBSW);
				stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
				if (stTnd_CEQID != stKASIM_CEQ)
				{
					stFnd_CEQID.Format(_T("%s"), stKASIM_CEQ);
				}
			}
			if (nTCBSW != 0)
			{
				ullCEQID = GETVALUE(unsigned long long, "cbsw_sta", "cbsw_ceqid", nTCBSW);
				stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
				if (stTnd_CEQID != stKASIM_CEQ)
				{
					stFnd_CEQID.Format(_T("%s"), stKASIM_CEQ);
				}
			}
		}
		pLNsec = new stKASIM_LNsec;
		map_LNsec.SetAt(stKASIM_LNSEC_CEQ, pLNsec);
		pLNsec->m_nLNSECID = i;
		pLNsec->m_nBRID = nKSIM_BRID;
		pLNsec->m_nBR_Fnd = nFnd;
		pLNsec->m_nBR_Tnd = nTnd;
		pLNsec->m_nLDID = nLDID;
		pLNsec->m_nIJID = nIJID;
		pLNsec->m_nFnd_ceq = stFnd_CEQID;
		pLNsec->m_nTnd_ceq = stTnd_CEQID;	
		pLNsec->m_nBR_SI_Fnd = nBR_SI_FND;
		pLNsec->m_nBR_SI_Tnd = nBR_SI_TND;

		map_LN_FND.SetAt(pLNsec->m_nBR_Fnd, nKSIM_BRID);
		map_LN_TND.SetAt(pLNsec->m_nBR_Tnd, nKSIM_BRID);
	}
	m_pProgress_barDLG->ADD_Progress(); // 7
	//CBSW
	int nCount_CBSW_table = theAppDataMng->GetTableRealCount(_T("cbsw_sta"));
	for (i = 1; i <= (int)nCount_CBSW_table; i++)
	{
		ullCEQID = GETVALUE(unsigned long long, "cbsw_sta", "cbsw_ceqid", i);
		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		nFnd = GETVALUE(int, _T("cbsw_sta"), _T("CBSW_II_FND"), i);
		nTnd = GETVALUE(int, _T("cbsw_sta"), _T("CBSW_II_TND"), i);
		nPrdeID = GETVALUE(int, _T("cbsw_sta"), _T("CBSW_II_PRDE"), i);

		map_LN_FND.Lookup(nFnd, nFBRID);
		map_LN_TND.Lookup(nTnd, nTBRID);

		pCBSW = new stKASIM_CBSW;
		map_CBSW.SetAt(stKASIM_CEQ, pCBSW);
		pCBSW->m_nCBSWID = i;
		pCBSW->m_nCBSW_Fnd = nFnd;
		pCBSW->m_nCBSW_Tnd = nTnd;
		pCBSW->m_nCBSW_PRDE = nPrdeID;

	}
	m_pProgress_barDLG->ADD_Progress(); // 8
	//발전기
	int nCount_GEN_table = theAppDataMng->GetTableRealCount(_T("gen_sta"));
	for (i = 1; i <= (int)nCount_GEN_table; i++)
	{
		ullCEQID = GETVALUE(unsigned long long, "gen_sta", "gen_ceqid", i);
		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		nGenND = GETVALUE(int, _T("gen_sta"), _T("GEN_II_ND"), i);
		nPrdeID = GETVALUE(int, _T("GEN_STA"), _T("GEN_II_PRDE"), i);
		nIJID = GETVALUE(int, _T("GEN_STA"), _T("GEN_II_IJ"), i);
		nESSID = GETVALUE(int, _T("GEN_STA"), _T("GEN_II_ESS"), i);

		map_LN_FND.Lookup(nGenND, nKSIM_BRID);
		map_LN_TND.Lookup(nGenND, nKSIM_BRID);

		pGEN = new stKASIM_GEN;
		map_GEN.SetAt(stKASIM_CEQ, pGEN);
		pGEN->m_nGENID = i;
		pGEN->m_nGEN_ND = nGenND;
		pGEN->m_nGEN_BR = nKSIM_BRID;
		pGEN->m_nGEN_IJ = nIJID;
		pGEN->m_nGEN_PRDE = nPrdeID;
		pGEN->m_nGEN_ESS = nESSID;	
	}
	m_pProgress_barDLG->ADD_Progress(); // 9
	//고객
	int nCount_HVCUS_table = theAppDataMng->GetTableRealCount(_T("hvcus_sta"));
	for (i = 1; i <= (int)nCount_HVCUS_table; i++)
	{
		ullCEQID = GETVALUE(unsigned long long, "hvcus_sta", "hvcus_ceqid", i);
		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		nHvcusND = GETVALUE(int, _T("hvcus_sta"), _T("HVCUS_II_GND"), i);
		nPrdeID = GETVALUE(int, _T("hvcus_sta"), _T("HVCUS_II_PRDE"), i);
		nIJID = GETVALUE(int, _T("hvcus_sta"), _T("HVCUS_II_IJ"), i);

		map_LN_FND.Lookup(nHvcusND, nKSIM_BRID);
		map_LN_TND.Lookup(nHvcusND, nKSIM_BRID);

		pHVCUS = new stKASIM_HVCUS;
		map_HVCUS.SetAt(stKASIM_CEQ, pHVCUS);
		pHVCUS->m_nHVCUSID = i;
		pHVCUS->m_nHVCUS_ND = nHvcusND;
		pHVCUS->m_nHVCUS_BR = nKSIM_BRID;
		pHVCUS->m_nHVCUS_IJ = nIJID;
		pHVCUS->m_nHVCUS_PRDE = nPrdeID;
	}
	m_pProgress_barDLG->ADD_Progress(); // 10
	//ND데이터
	int nCount_ND_table = theAppDataMng->GetTableRealCount(_T("nd_sta"));
	int nND_FCBSW, nND_TCBSW, nND_FBR, nND_TBR;
	int nMuswCheck = 0;
	int nMuFnd, nMuTnd;
	int nMuswCent = 0;
	
	for (i = 1; i <= (int)nCount_ND_table; i++)
	{
		pND = NULL;
		pND_Arry = NULL;
		ullCEQID = GETVALUE(unsigned long long, "nd_sta", "ND_CEQID", i);
		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		//20211123
		nND_FCBSW = GETVALUE(int, _T("nd_sta"), _T("ND_HI_FCBSW"), i);
		nND_TCBSW = GETVALUE(int, _T("nd_sta"), _T("ND_HI_TCBSW"), i);
		nND_FBR = GETVALUE(int, _T("nd_sta"), _T("ND_HI_FBR"), i);
		nND_TBR = GETVALUE(int, _T("nd_sta"), _T("ND_HI_TBR"), i);
		
		if (stKASIM_CEQ == "10692909000715" )
		{
			int a = 0;
		}

		map_ND.Lookup(stKASIM_CEQ, pND);
		if ( pND == NULL)
		{
			pND = new stKASIM_ND;
			map_ND.SetAt(stKASIM_CEQ, pND);
			pND->m_nNDID = i;
		}

		   
		if (nND_FCBSW != 0)
		{
			nMuswCheck = GETVALUE(int, _T("cbsw_sta"), _T("CBSW_MULTICIR_NUMBER"), nND_FCBSW);
			if (nMuswCheck != 0)
			{
				nMuFnd = GETVALUE(int, _T("cbsw_sta"), _T("CBSW_II_FND"), nND_FCBSW);
				nMuTnd = GETVALUE(int, _T("cbsw_sta"), _T("CBSW_II_TND"), nND_FCBSW);
				if (nMuFnd == i)
				{
					nMuswCent = 9999;
				}
				if (nMuTnd == i)
				{
					nMuswCent = 1111;
				}
			}
		}
		if (nND_TCBSW != 0)
		{
			nMuswCheck = GETVALUE(int, _T("cbsw_sta"), _T("CBSW_MULTICIR_NUMBER"), nND_TCBSW);
			if (nMuswCheck != 0)
			{
				nMuFnd = GETVALUE(int, _T("cbsw_sta"), _T("CBSW_II_FND"), nND_TCBSW);
				nMuTnd = GETVALUE(int, _T("cbsw_sta"), _T("CBSW_II_TND"), nND_TCBSW);
				if (nMuFnd == i)
				{
					nMuswCent = 9999;
				}
				if (nMuTnd == i)
				{
					nMuswCent = 1111;
				}
			}
		}
		pND_Arry = new CKASIM_ND;
		pND_Arry->nND_ID = i;
		pND_Arry->nND_FBRID = nND_FBR;
		pND_Arry->nND_TBRID = nND_TBR;
		pND_Arry->nND_FCBSWID = nND_FCBSW;
		pND_Arry->nND_TCBSWID = nND_TCBSW;
		pND_Arry->nND_MUSW = nMuswCent;
		m_Array_KASIM_ND.Add(pND_Arry);
	}
	m_pProgress_barDLG->ADD_Progress(); // 11
	int nCount_TR_table = theAppDataMng->GetTableRealCount(_T("tr_sta"));
	for (i = 1; i <= (int)nCount_TR_table; i++)
	{
		ullCEQID = GETVALUE(unsigned long long, "tr_sta", "TR_CEQID", i);
		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		nKSIM_BRID = GETVALUE(int, "tr_sta", "TR_II_BR", i);
		nFnd = GETVALUE(int, _T("br_sta"), _T("BR_II_FND"), nKSIM_BRID);
		nTnd = GETVALUE(int, _T("br_sta"), _T("BR_II_TND"), nKSIM_BRID);

		map_LN_FND.Lookup(nFnd, nFBRID);
		map_LN_TND.Lookup(nTnd, nTBRID);
		
		pSVR = new stKASIM_SVR;
		map_SVR.SetAt(stKASIM_CEQ, pSVR);
		pSVR->m_nSVRID = i;
		pSVR->m_nSVR_BRID = nKSIM_BRID;
		pSVR->m_nSVR_Fnd = nFnd;
		pSVR->m_nSVR_Tnd = nTnd;
	}
	m_pProgress_barDLG->ADD_Progress(); // 12
// 	int nCount_MTR_table = theAppDataMng->GetTableRealCount(_T("mtr_sta"));
// 	for (i = 1; i <= (int)nCount_MTR_table; i++)
// 	{
// 		ullCEQID = GETVALUE(unsigned long long, "tr_sta", "TR_CEQID", i);
// 		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
// 		nKSIM_BRID = GETVALUE(int, "tr_sta", "TR_II_BR", i);
// 		nFnd = GETVALUE(int, _T("br_sta"), _T("BR_II_FND"), nKSIM_BRID);
// 		nTnd = GETVALUE(int, _T("br_sta"), _T("BR_II_TND"), nKSIM_BRID);
// 
// 		map_LN_FND.Lookup(nFnd, nFBRID);
// 		map_LN_TND.Lookup(nTnd, nTBRID);
// 
// 		pSVR = new stKASIM_SVR;
// 		map_SVR.SetAt(stKASIM_CEQ, pSVR);
// 		pSVR->m_nSVRID = i;
// 		pSVR->m_nSVR_BRID = nKSIM_BRID;
// 		pSVR->m_nSVR_Fnd = nFnd;
// 		pSVR->m_nSVR_Tnd = nTnd;
// 	}
	m_pProgress_barDLG->ADD_Progress(); // 13
	int nCount_SS_table = theAppDataMng->GetTableRealCount(_T("ss_sta"));
	for (i = 1; i <= (int)nCount_SS_table; i++)
	{
		ullCEQID = GETVALUE(unsigned long long, "SS_STA", "SS_SUBSTATIONID", i);
		stKASIM_CEQ.Format(_T("%lld"), ullCEQID);
		pSUBS = new stKASIM_SUBS;
		map_SUBS.SetAt(stKASIM_CEQ, pSUBS);
		pSUBS->m_nSUBSID = i;
		pSUBS->m_nGENID = 0;
		pSUBS->m_nNDID = 0;
	}
	m_pProgress_barDLG->ADD_Progress(); // 14
	//20210813 새로운 입력부분
	for (int j = 0; j < m_Array_DND_Connect.GetSize(); j++)
	{
		pLNsec = NULL;
		pDNDObj = m_Array_DND_Connect.GetAt(j);
		pConnect = (CDND_Connect*)pDNDObj;
		map_LNsec.Lookup(pConnect->m_str_keyid, pLNsec);
		if (pLNsec == NULL)
		{
			continue;
		}
		pConnect->m_st_Kasim_LNsec_Info.m_nLNSECID = pLNsec->m_nLNSECID;
		pConnect->m_st_Kasim_LNsec_Info.m_nBRID = pLNsec->m_nBRID;
		pConnect->m_st_Kasim_LNsec_Info.m_nLDID = pLNsec->m_nLDID;
		pConnect->m_st_Kasim_LNsec_Info.m_nIJID = pLNsec->m_nIJID;
		pConnect->m_st_Kasim_LNsec_Info.m_nBR_Connect_Check = 0;
		pConnect->m_st_Kasim_LNsec_Info.m_nBR_SI_Fnd = pLNsec->m_nBR_SI_Fnd;
		pConnect->m_st_Kasim_LNsec_Info.m_nBR_SI_Tnd = pLNsec->m_nBR_SI_Tnd;

		//이게 안맞는게 있는데?흠
		if(pConnect->m_strID_CEQ_From == pLNsec->m_nFnd_ceq)
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pLNsec->m_nBR_Fnd;
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pLNsec->m_nBR_Tnd;
			pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq = pLNsec->m_nFnd_ceq;
			pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq = pLNsec->m_nTnd_ceq;
		}
		else if (pConnect->m_strID_CEQ_From == pLNsec->m_nTnd_ceq)
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pLNsec->m_nBR_Tnd;
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pLNsec->m_nBR_Fnd;
			pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq = pLNsec->m_nTnd_ceq;
			pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq = pLNsec->m_nFnd_ceq;
		}
		else if (pConnect->m_strID_CEQ_To == pLNsec->m_nTnd_ceq)
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pLNsec->m_nBR_Fnd;
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pLNsec->m_nBR_Tnd;
			pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq = pLNsec->m_nFnd_ceq;
			pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq = pLNsec->m_nTnd_ceq;
		}
		else if (pConnect->m_strID_CEQ_To == pLNsec->m_nFnd_ceq)
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pLNsec->m_nBR_Tnd;
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pLNsec->m_nBR_Fnd;
			pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq = pLNsec->m_nTnd_ceq;
			pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq = pLNsec->m_nFnd_ceq;
		}
		else
		{
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Fnd = pLNsec->m_nBR_Fnd;
			pConnect->m_st_Kasim_LNsec_Info.m_nBR_Tnd = pLNsec->m_nBR_Tnd;
			pConnect->m_st_Kasim_LNsec_Info.m_nFnd_ceq = pLNsec->m_nFnd_ceq;
			pConnect->m_st_Kasim_LNsec_Info.m_nTnd_ceq = pLNsec->m_nTnd_ceq;
		}	
	}
	m_pProgress_barDLG->ADD_Progress(); // 15

	int nCount = (int)m_Array_DND_Switch.GetSize();
	for (int j = 0; j < m_Array_DND_Switch.GetSize(); j++)
	{
		pDNDObj = m_Array_DND_Switch.GetAt(j);

		pCBSW = NULL;
		pGEN = NULL;
		pHVCUS = NULL;
		pND = NULL;
		pSVR = NULL;
		pSUBS = NULL;

		if (nCount/4 == j)
		{
			m_pProgress_barDLG->ADD_Progress(); // 16 ?4번?
		}

		pSwitch = (CDND_Switch*)pDNDObj;
		if (pSwitch->m_str_psrtype == "COMPSWITCH" || pSwitch->m_str_psrtype == "TR")
		{
			if (pSwitch->ObjectType_Get() == DND_OBJTYPE_MULTIBLOCK)
			{
				CDND_Switch* pMulti_M;
				for (int i = 0; i < pSwitch->m_Array_Multi.GetSize(); i++)
				{
					pMulti_M = (CDND_Switch*)pSwitch->m_Array_Multi.GetAt(i);
					pCBSW = NULL;
					pND = NULL;
					if (pMulti_M->m_str_psrtype == "SWITCH" )
					{
						map_CBSW.Lookup(pMulti_M->m_str_keyid, pCBSW);
						if (pCBSW == NULL)
						{
							continue;
						}
						if (pCBSW)
						{
							pMulti_M->m_st_Kasim_CBSW_Info.m_nCBSWID = pCBSW->m_nCBSWID;
							pMulti_M->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd = pCBSW->m_nCBSW_Fnd;
							pMulti_M->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd = pCBSW->m_nCBSW_Tnd;
							pMulti_M->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE = pCBSW->m_nCBSW_PRDE;

							Get_ND_BR_Arry(pCBSW->m_nCBSW_Fnd, pMulti_M, 2);
							Get_ND_BR_Arry(pCBSW->m_nCBSW_Tnd, pMulti_M, 2);
						}
					}
					if (pMulti_M->m_str_psrtype == "JUNCTION")
					{
						nFBRID = 0, nTBRID = 0;
						map_ND.Lookup(pMulti_M->m_str_keyid, pND);
						if (pND == NULL)
						{
							continue;
						}
						if (pND)
						{
							pMulti_M->m_st_Kasim_ND_Info.m_nNDID = pND->m_nNDID;
							Get_ND_BR_Arry(pND->m_nNDID, pMulti_M, 1);
						}
					}
					
				}
			}
		}
		else if (pSwitch->m_str_psrtype == "RECLOSER" || pSwitch->m_str_psrtype == "CB" || pSwitch->m_str_psrtype == "BREAKER")
		{
			map_CBSW.Lookup(pSwitch->m_str_keyid, pCBSW);
			if (pCBSW == NULL)
			{
				continue;
			}
			if (pCBSW)
			{
				pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID = pCBSW->m_nCBSWID;
				pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd = pCBSW->m_nCBSW_Fnd;
				pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd = pCBSW->m_nCBSW_Tnd;
				pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE = pCBSW->m_nCBSW_PRDE; 

				Get_ND_BR_Arry(pCBSW->m_nCBSW_Fnd, pSwitch, 2);
				Get_ND_BR_Arry(pCBSW->m_nCBSW_Tnd, pSwitch, 2);
			}
		}
		//JUNCTION - CABLEPOLE
		else if (pSwitch->m_str_psrtype == "JUNCTION" || pSwitch->m_str_psrtype == "CABLEPOLE")
		{
			nFBRID = 0, nTBRID = 0;
			map_ND.Lookup(pSwitch->m_str_keyid, pND);
			if (pND == NULL)
			{
				continue;
			}
			if (pND)
			{
				pSwitch->m_st_Kasim_ND_Info.m_nNDID = pND->m_nNDID;
				Get_ND_BR_Arry(pND->m_nNDID, pSwitch, 1);
			}
		}
		//CONSUMER
		else if (pSwitch->m_str_psrtype == "CONSUMER")
		{
			map_HVCUS.Lookup(pSwitch->m_str_keyid, pHVCUS);
			if (pHVCUS == NULL)
			{
				continue;
			}
			if (pHVCUS)
			{
				pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUSID = pHVCUS->m_nHVCUSID;
				pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_ND = pHVCUS->m_nHVCUS_ND;
				pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_BR = pHVCUS->m_nHVCUS_BR;
				pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_IJ = pHVCUS->m_nHVCUS_IJ;
				pSwitch->m_st_Kasim_HVCUS_Info.m_nHVCUS_PRDE = pHVCUS->m_nHVCUS_PRDE;

				Get_ND_BR_Arry(pHVCUS->m_nHVCUS_ND, pSwitch, 1 );
			}
		}
		//GENERATEUNIT
		else if (pSwitch->m_str_psrtype == "GENERATEUNIT" || pSwitch->m_str_psrtype == "DG" || pSwitch->m_str_psrtype == "ENERGYSOURCEEQ")
		{
			map_GEN.Lookup(pSwitch->m_str_keyid, pGEN);
			if (pGEN == NULL)
			{
				continue;
			}
			if (pGEN)
			{
				pSwitch->m_st_Kasim_GEN_Info.m_nGENID = pGEN->m_nGENID;
				pSwitch->m_st_Kasim_GEN_Info.m_nGEN_ND = pGEN->m_nGEN_ND;
				pSwitch->m_st_Kasim_GEN_Info.m_nGEN_BR = pGEN->m_nGEN_BR;
				pSwitch->m_st_Kasim_GEN_Info.m_nGEN_IJ = pGEN->m_nGEN_IJ;
				pSwitch->m_st_Kasim_GEN_Info.m_nGEN_PRDE = pGEN->m_nGEN_PRDE;
				pSwitch->m_st_Kasim_GEN_Info.m_nGEN_ESS = pGEN->m_nGEN_ESS;

				Get_ND_BR_Arry(pGEN->m_nGEN_ND, pSwitch, 1);
			}
		}
		else if (pSwitch->m_str_psrtype == "SVR")
		{
			map_SVR.Lookup(pSwitch->m_str_keyid, pSVR);
			if (pSVR == NULL)
			{
				continue;
			}
			if (pSVR)
			{
				pSwitch->m_st_Kasim_SVR_Info.m_nSVRID = pSVR->m_nSVRID;
				pSwitch->m_st_Kasim_SVR_Info.m_nSVR_BRID = pSVR->m_nSVR_BRID;
				pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Fnd = pSVR->m_nSVR_Fnd;
				pSwitch->m_st_Kasim_SVR_Info.m_nSVR_Tnd = pSVR->m_nSVR_Tnd;
				Get_ND_BR_Arry(pSVR->m_nSVR_Fnd, pSwitch, 3);
				Get_ND_BR_Arry(pSVR->m_nSVR_Tnd, pSwitch, 3);
			}
		}
		else if (pSwitch->m_str_psrtype == "SUBSTATION")
		{
			map_SUBS.Lookup(pSwitch->m_str_keyid, pSUBS);
			if (pSUBS == NULL)
			{
				continue;
			}
			if (pSUBS)
			{
				pSwitch->m_st_Kasim_SUBS_Info.m_nSUBSID = pSUBS->m_nSUBSID;
				pSwitch->m_st_Kasim_SUBS_Info.m_nGENID = pSUBS->m_nGENID;
				pSwitch->m_st_Kasim_SUBS_Info.m_nNDID = pSUBS->m_nNDID;

				//Get_ND_BR_Arry(pSUBS->m_nNDID, pSwitch);
			}
		}
		else
		{
			map_CBSW.Lookup(pSwitch->m_str_keyid, pCBSW);
			if (pCBSW == NULL)
			{
				continue;
			}
			if (pCBSW)
			{
				pSwitch->m_st_Kasim_CBSW_Info.m_nCBSWID = pCBSW->m_nCBSWID;
				pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Fnd = pCBSW->m_nCBSW_Fnd;
				pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_Tnd = pCBSW->m_nCBSW_Tnd;
				pSwitch->m_st_Kasim_CBSW_Info.m_nCBSW_PRDE = pCBSW->m_nCBSW_PRDE;

				Get_ND_BR_Arry(pCBSW->m_nCBSW_Fnd, pSwitch ,2);
				Get_ND_BR_Arry(pCBSW->m_nCBSW_Tnd, pSwitch ,2);
			}		
		}
	}

	map_LN_FND.RemoveAll();
	map_LN_TND.RemoveAll();

	nCount = 0;
	CString stDate;
	POSITION pos = map_LNsec.GetStartPosition();
	while (pos)
	{
		map_LNsec.GetNextAssoc(pos, stDate, pLNsec);
		delete pLNsec;
		nCount++;
	}
 	map_LNsec.RemoveAll();
	nCount = 0;
	pos = map_CBSW.GetStartPosition();
	while (pos)
	{
		map_CBSW.GetNextAssoc(pos, stDate, pCBSW);
		delete pCBSW;
		nCount++;
	}
	map_CBSW.RemoveAll();
	nCount = 0;
	pos = map_GEN.GetStartPosition();
	while (pos)
	{
		map_GEN.GetNextAssoc(pos, stDate, pGEN);
		delete pGEN;
		nCount++;
	}
	map_GEN.RemoveAll();
	nCount = 0;
	pos = map_HVCUS.GetStartPosition();
	while (pos)
	{
		map_HVCUS.GetNextAssoc(pos, stDate, pHVCUS);
		delete pHVCUS;
		nCount++;
	}
	map_HVCUS.RemoveAll();
	nCount = 0;
	pos = map_ND.GetStartPosition();
	while (pos)
	{
		map_ND.GetNextAssoc(pos, stDate, pND);
		delete pND;
		nCount++;
	}
	map_ND.RemoveAll();
	nCount = 0;
	pos = map_SVR.GetStartPosition();
	while (pos)
	{
		map_SVR.GetNextAssoc(pos, stDate, pSVR);
		delete pSVR;
		nCount++;
	}
	map_SVR.RemoveAll();
	nCount = 0;
	pos = map_SUBS.GetStartPosition();
	while (pos)
	{
		map_SUBS.GetNextAssoc(pos, stDate, pSUBS);
		delete pSUBS;
		nCount++;
	}
	map_SUBS.RemoveAll();
	
	return NULL;
}

void	CDND_Manager::Get_ND_BR_Arry( int nNextNDIdx, CDND_Switch *pSwitch, int Index)
{
	int																		nNextBRIdx;

	nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_fbr"), nNextNDIdx);
	while (nNextBRIdx)
	{
		if (GetBrType(nNextBRIdx) == 1)
		{
			if (Index == 1)
			{
				pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.Add(nNextBRIdx); //ND에 BR정보 입력!!!
			}
			else if (Index == 2)
			{
				pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.Add(nNextBRIdx); //ND에 BR정보 입력!!!
			}
			else if (Index == 3)
			{
				pSwitch->m_st_Kasim_SVR_Info.stKASIM_SVR_BR_Arry.Add(nNextBRIdx); //ND에 BR정보 입력!!!
			}
		}
		nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_fnd"), nNextBRIdx);
	}

	nNextBRIdx = GETVALUE(int, _T("nd_sta"), _T("nd_hi_tbr"), nNextNDIdx);
	while (nNextBRIdx)
	{
		//연결된 BR이 구간일때만 진행( 단자ND는 FromNode가 되고, fromNode와 구간정보를 넘김)
		if (GetBrType(nNextBRIdx) == 1)
		{
			if (Index == 1)
			{
				pSwitch->m_st_Kasim_ND_Info.stKASIM_ND_BR_Arry.Add(nNextBRIdx); //ND에 BR정보 입력!!!
			}
			else if (Index == 2)
			{
				pSwitch->m_st_Kasim_CBSW_Info.stKASIM_CBSW_BR_Arry.Add(nNextBRIdx); //ND에 BR정보 입력!!!
			}
			else if (Index == 3)
			{
				pSwitch->m_st_Kasim_SVR_Info.stKASIM_SVR_BR_Arry.Add(nNextBRIdx); //ND에 BR정보 입력!!!
			}
		}
		nNextBRIdx = GETVALUE(int, _T("br_sta"), _T("br_si_tnd"), nNextBRIdx);
	}
}

int CDND_Manager::GetBrType(int nBrIdx)
{
	int nGbrIdx, nType;
	nGbrIdx = GETVALUE(int, _T("br_sta"), _T("br_ii_gbr"), nBrIdx);
	if (nGbrIdx == 0)													return 0;

	nType = GETVALUE(int, _T("gbr_sta"), _T("gbr_ii_equty"), nGbrIdx);
	return nType;
}



CDND_Object* CDND_Manager::SVG_KASIM_Association_Index()
{
	m_pProgress_barDLG->ADD_Progress(); // 20

	m_nMax_LNSEC_table = theAppDataMng->GetTableRealCount(_T("lnsec_sta"));
	m_nMax_BR_table = theAppDataMng->GetTableRealCount(_T("br_sta"));
	m_nMax_CBSW_table = theAppDataMng->GetTableRealCount(_T("cbsw_sta"));
	m_nMax_HVCUS_table = theAppDataMng->GetTableRealCount(_T("hvcus_sta"));
	m_nMax_GEN_table = theAppDataMng->GetTableRealCount(_T("gen_sta"));
	m_nMax_ND_table = theAppDataMng->GetTableRealCount(_T("nd_sta"));
	m_nMax_GND_table = theAppDataMng->GetTableRealCount(_T("gnd_sta"));
	m_nMax_LD_table = theAppDataMng->GetTableRealCount(_T("ld_sta"));
	m_nMax_IJ_table = theAppDataMng->GetTableRealCount(_T("ij_sta"));
	m_nMax_ESS_table = theAppDataMng->GetTableRealCount(_T("ess_sta"));
	m_nMax_PRDE_table = theAppDataMng->GetTableRealCount(_T("prde_sta"));
	m_nMax_SVR_table = theAppDataMng->GetTableRealCount(_T("tr_sta"));
	m_nMax_SS_table = theAppDataMng->GetTableRealCount(_T("ss_sta"));
	m_nMax_MTR_table = theAppDataMng->GetTableRealCount(_T("mtr_sta"));
	m_nMax_GENUNIT_table = theAppDataMng->GetTableRealCount(_T("GENUNIT_STA"));

	m_nMax_DL_table = theAppDataMng->GetTableRealCount(_T("DL_STA"));
	//
	m_nMax_LNSEC_table  = m_nMax_LNSEC_table + 1;
	m_nMax_BR_table = m_nMax_BR_table + 1;
	m_nMax_CBSW_table = m_nMax_CBSW_table + 1;
	m_nMax_HVCUS_table = m_nMax_HVCUS_table + 1;
	m_nMax_GEN_table = m_nMax_GEN_table + 1;
	m_nMax_ND_table = m_nMax_ND_table + 1;
	m_nMax_GND_table = m_nMax_GND_table + 1;
	m_nMax_LD_table = m_nMax_LD_table + 1;
	m_nMax_IJ_table = m_nMax_IJ_table + 1;
	m_nMax_ESS_table = m_nMax_ESS_table + 1;
	m_nMax_PRDE_table = m_nMax_PRDE_table + 1;
	m_nMax_SVR_table = m_nMax_SVR_table + 1;
	m_nMax_SS_table = m_nMax_SS_table + 1;
	m_nMax_MTR_table = m_nMax_MTR_table + 1;
	m_nMax_GENUNIT_table = m_nMax_GENUNIT_table + 1;
	m_nMax_DL_table = m_nMax_DL_table + 1;
	//
	double fSNVID = 0, fSNV = 22.9;
	int nCount_table = theAppDataMng->GetTableRealCount(_T("SNV_STA"));
	for (int i = 1; i <= (int)nCount_table; i++)
	{
		fSNVID = GETVALUE(double, _T("SNV_STA"), _T("SNV_NORKV"), i);
		if (fSNVID == fSNV)
		{
			m_nHold_SNVID = i;
			break;
		}
	}
	//
	m_pProgress_barDLG->DestroyWindow();
	delete m_pProgress_barDLG;
	m_pProgress_barDLG = NULL;

	return NULL;
}

int	CDND_Manager::Get_CBSW_TYPE(CDND_Switch* pSwitch)
{
	if(pSwitch->m_str_psrtype == "CB")
	{
		return 1;
	}
	else if(pSwitch->m_str_psrtype == "RECLOSER")
	{
		if (pSwitch->m_n_devref == 444 || pSwitch->m_n_devref == 70 ) //자동EFI
		{
			return 5;
		}
		else
		{
			return 2;
		}
	}
	else if (pSwitch->m_str_psrtype == "SWITCH" || pSwitch->m_str_psrtype == "COMPSWITCH")
	{
		if (pSwitch->m_n_devref == 418) //수동개폐기
		{
			return 4;
		}
		else if (pSwitch->m_n_devref == 441) //LV
		{
			return 7;
		}
		else
		{
			return 3;
		}
	}
	else if (pSwitch->m_str_psrtype == "BREAKER")
	{
		return 6;
	}

	return 0;
}

