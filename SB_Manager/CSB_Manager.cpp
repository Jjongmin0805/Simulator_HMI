#include "pch.h"
#include "CSB_Manager.h"
#include "../DND_Manager/CDND_Manager.h"



CSB_Manager *CSB_Manager::_instance = NULL;

CSB_Manager::CSB_Manager(void)
{
	CoInitialize(NULL);
}

CSB_Manager::~CSB_Manager(void)
{
	CoUninitialize();

	for (int i = 0; i < m_Array_SB.GetSize(); i++)
		delete m_Array_SB.GetAt(i);

	m_Array_SB.RemoveAll();
}

CSB_Manager* CSB_Manager::Instance()
{

	if (_instance == 0)
	{
		_instance = new CSB_Manager();
	}
	return _instance;
}


CString CSB_Manager::MyPath()
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

BOOL CSB_Manager::Read_SB_File()
{
	//
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
			if (strExt.CompareNoCase(_T("xml")) == 0)
			{
				nFrinder = 9999;

				strTitleName = finder.GetFileTitle();
				strFilePath = finder.GetFilePath();
				strFileName = finder.GetFileName();
				break;
			}
		}
	}

	if (nFrinder == 0)
	{
		AfxMessageBox(_T("심볼 파일을 찾을수가 없습니다. 프로그램을 자동으로 종료합니다."));
		
		return FALSE;		
		//프로그램 종료
	}

	CMarkup xml;
	if ( !xml.Load(strFilePath) )
	{
		return FALSE;
	}

	//BOOL b = xml.FindElem(_T("CIMDLIB"));
	
	CString strTagName, strpsrType;
	CSB_Object *pSBObj;

	//20211203

	while ( xml.FindChildElem() )
	{
		xml.IntoElem();

		strTagName = xml.GetTagName();

		TRACE(_T("%s\n"), strTagName);
		pSBObj = NULL;

		pSBObj = new CSB_BLOCK();
		m_Array_SB.Add(pSBObj);
		pSBObj->SetObjectData(&xml);

		TRACE(_T("%s : %s\n"), strTagName, ((CSB_BLOCK*)pSBObj)->GetName());
		
		xml.OutOfElem();
	}

	
	CSB_BLOCK* pBlock, *pMulti;
	CSB_BLOCK_M* pBlock_M;
	CSB_Layer* pLayer;

	for (int i = 0; i < m_Array_SB.GetSize(); i++)
	{
		pBlock = (CSB_BLOCK*)m_Array_SB.GetAt(i);

		if (pBlock->ObjType_Get() == SBOBJECT_TYPE_MULTIBLOCK)
		{
			
			for (int k = 0; k < pBlock->m_Array_Layer.GetSize(); k++)
			{
				pLayer = (CSB_Layer*)pBlock->m_Array_Layer.GetAt(k);

				for (int m = 0; m < pLayer->m_Array_DrawObject.GetSize(); m++)
				{
					pSBObj = pLayer->m_Array_DrawObject.GetAt(m);

					if (pSBObj->ObjType_Get() == SBOBJECT_TYPE_BLOCK_M)
					{
						pBlock_M = (CSB_BLOCK_M*)pSBObj;
						pMulti = (CSB_BLOCK*)GetBlock_SB(pBlock_M->GetDevref());
						pLayer->Set_mem_MultiBlock(pMulti);
					}
				}
			}
		}

	}

	Set_MenuID();

	return TRUE;
}

void CSB_Manager::Set_MenuID()
{
	CSB_BLOCK* pBlock;
	int nCount = 0;
	for (int i = 0; i < m_Array_SB.GetSize(); i++)
	{
		pBlock = (CSB_BLOCK*)m_Array_SB.GetAt(i);

		if(pBlock->Usage_Get().Compare(_T("DEVICE") ) != 0)
			continue;

		pBlock->MenuID_Set(SYMBOL_MENU_ID_FIRST + nCount);
		nCount++;

		if (SYMBOL_MENU_ID_FIRST + nCount > SYMBOL_MENU_ID_LAST)
		{
			AfxMessageBox(_T("Symbol overflow !!"));
			break;
		}
	}

}

CSB_Object* CSB_Manager::GetBlock_SB(int nDevref)
{
	CSB_BLOCK* pBlock;
	for (int i = 0; i < m_Array_SB.GetSize(); i++)
	{
		pBlock = (CSB_BLOCK*)m_Array_SB.GetAt(i);

		if (pBlock->GetID() == nDevref)
			return pBlock;
	}

	return NULL;
}

CSB_Object* CSB_Manager::GetBlock_SB2ResourceID(int nResourceID)
{
	CSB_BLOCK* pBlock;
	for (int i = 0; i < m_Array_SB.GetSize(); i++)
	{
		pBlock = (CSB_BLOCK*)m_Array_SB.GetAt(i);

		if (pBlock->MenuID_Get() == nResourceID)
			return pBlock;
	}

	return NULL;
}

void CSB_Manager::test_Draw(Graphics &graphics, CRect rClient)
{
	CRect r;
	CSB_BLOCK* pSBObj;

	CRect rDraw(0, 0, 0, 0);
	int nMx_Y = 0 ;

	for (int i = 0; i < m_Array_SB.GetSize(); i++)
	{
		pSBObj = (CSB_BLOCK*)m_Array_SB.GetAt(i);

		r = pSBObj->GetSBRect();

		rDraw.right = rDraw.left + r.Width();
		rDraw.bottom = rDraw.top + r.Height();

		if (rClient.right < rDraw.right)
		{
			rDraw.left = 0;
			rDraw.right = rDraw.left + r.Width();
			rDraw.top = nMx_Y + 10;
			rDraw.bottom = rDraw.top + r.Height();

		}

		/////////////////////// Draw

		pSBObj->Draw(graphics, rDraw.CenterPoint(),1., _T(""));

		if (nMx_Y < rDraw.bottom)
		{
			nMx_Y = rDraw.bottom;
		}
		
		rDraw.left = rDraw.right + 10;
	
	}

}

void CSB_Manager::SetMenu(CMenu* pMenu)
{
	pMenu->AppendMenu(MF_STRING, SYMBOL_MENU_ID_CONNECT, _T("선로"));
	pMenu->AppendMenu(MF_STRING, SYMBOL_MENU_ID_TEXT, _T("Text"));

	CSB_BLOCK* pBlock;
	
	CMenu	menuBlock, menuMulti;

	menuBlock.CreatePopupMenu();
	for (int i = 0; i < m_Array_SB.GetSize(); i++)
	{
		pBlock = (CSB_BLOCK*)m_Array_SB.GetAt(i);

		if (pBlock->MenuID_Get() < 0)
			continue;

		if (pBlock->ObjType_Get() != SBOBJECT_TYPE_BLOCK)
			continue;
		//심볼 메뉴 수정// 508번 신규 추가내용입니다. 20211018
		if (/*pBlock->GetID() == 103 */
			 pBlock->GetID() == 105
			|| pBlock->GetID() == 405
			|| pBlock->GetID() == 406
			|| pBlock->GetID() == 414
// 			|| pBlock->GetID() == 420
//			|| pBlock->GetID() == 421
			|| pBlock->GetID() == 437
			|| pBlock->GetID() == 438
			|| pBlock->GetID() == 436
			|| pBlock->GetID() == 441
			|| pBlock->GetID() == 473
			|| pBlock->GetID() == 497
			|| pBlock->GetID() == 498
			|| pBlock->GetID() == 499
			|| pBlock->GetID() == 507
			|| pBlock->GetID() == 500
			|| pBlock->GetID() == 501
			|| pBlock->GetID() == 502
			|| pBlock->GetID() == 508
			|| pBlock->GetID() == 510
//			|| pBlock->GetID() == 515
			|| pBlock->GetID() == 516) //변전소 삭제해야함 420
			continue;

		menuBlock.AppendMenu(MF_STRING, pBlock->MenuID_Get(), pBlock->GetName());
	}

	pMenu->AppendMenu(MF_POPUP,(UINT)menuBlock.Detach(),_T("Block"));

	//20210727 - 다회로 추가 X
	menuMulti.CreatePopupMenu();
	for (int i = 0; i < m_Array_SB.GetSize(); i++)
	{
		pBlock = (CSB_BLOCK*)m_Array_SB.GetAt(i);

		if (pBlock->MenuID_Get() < 0)
			continue;

		if (pBlock->ObjType_Get() != SBOBJECT_TYPE_MULTIBLOCK)
			continue;

		//심볼 메뉴 수정
		if (  pBlock->GetID() == 408
			|| pBlock->GetID() == 411
			|| pBlock->GetID() == 416
			|| pBlock->GetID() == 423
			|| pBlock->GetID() == 424
			|| pBlock->GetID() == 428
			|| pBlock->GetID() == 430
			|| pBlock->GetID() == 431
			|| pBlock->GetID() == 452
			|| pBlock->GetID() == 454
			|| pBlock->GetID() == 445
			|| pBlock->GetID() == 456
			|| pBlock->GetID() == 458
			|| pBlock->GetID() == 459
			|| pBlock->GetID() == 460
			|| pBlock->GetID() == 485
			|| pBlock->GetID() == 486
			|| pBlock->GetID() == 487
			|| pBlock->GetID() == 488
			|| pBlock->GetID() == 489
			|| pBlock->GetID() == 492
			|| pBlock->GetID() == 493
			|| pBlock->GetID() == 494
			|| pBlock->GetID() == 495
			|| pBlock->GetID() == 496
			|| pBlock->GetID() == 488
			|| pBlock->GetID() == 518
			|| pBlock->GetID() == 519
			|| pBlock->GetID() == 520
			|| pBlock->GetID() == 521
			) //ALTS 다회로
			continue;

		menuMulti.AppendMenu(MF_STRING, pBlock->MenuID_Get(), pBlock->GetName());
	}
	pMenu->AppendMenu(MF_POPUP, (UINT)menuMulti.Detach(), _T("MultiBlock"));
}