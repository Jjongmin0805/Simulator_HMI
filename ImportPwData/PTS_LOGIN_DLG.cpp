// PTS_LOGIN_DLG.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PTS_LOGIN_DLG.h"
#include "afxdialogex.h"
#include "../DataManager/CDataManager.h"

// CPTS_LOGIN_DLG ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPTS_LOGIN_DLG, CDialogEx)

CPTS_LOGIN_DLG::CPTS_LOGIN_DLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPTS_LOGIN_DLG::IDD, pParent)
{

}

CPTS_LOGIN_DLG::~CPTS_LOGIN_DLG()
{
	m_Session.Close();
	m_Connect.Close();
}

void CPTS_LOGIN_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPTS_LOGIN_DLG, CDialogEx)
	ON_BN_CLICKED(IDC_PTS_LOGIN_DLG_BTN, &CPTS_LOGIN_DLG::OnBnClickedPtsLoginDlgBtn)
END_MESSAGE_MAP()


// CPTS_LOGIN_DLG �޽��� ó�����Դϴ�.


BOOL CPTS_LOGIN_DLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CPTS_LOGIN_DLG::CreateSession()
{
	if (m_Session.m_spOpenRowset != NULL)
	{
		m_Session.m_spOpenRowset.Release();
	}

	CString strID,strPass;
	
	GetDlgItemText(IDC_PTS_LOGIN_DLG_EDIT1 ,strID);
	GetDlgItemText(IDC_PTS_LOGIN_DLG_EDIT2 ,strPass);

	CString strConnect;

	strConnect.Format(_T("Provider=MSDAORA.1;Password=%s;User ID=%s;Data Source=pts;"),strPass,strID);

	if (m_Connect.OpenFromInitializationString(strConnect.AllocSysString(),TRUE) != S_OK)
	{
		AfxMessageBox(_T("Unable to connect to data source(PTS DB)"));
		return FALSE;
	}
	else 
	{
		if (m_Session.Open(m_Connect) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source(PTS DB)"));
			return FALSE ;
		}
	}
	return TRUE;
}

void CPTS_LOGIN_DLG::OnBnClickedPtsLoginDlgBtn()
{

	if(!CreateSession())
	{
		return;
	}
	
	/*CDataAdministrator* pNewDM = CDataAdministrator::Instance();*/
	CDataManager* pData = CDataManager::Instance();
	CString strPath;
	strPath.Format(_T("%s\\config\\config_pts.pas"),pData->MyPath());
	CFile stream;
	if(!stream.Open(strPath,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
	{
		AfxMessageBox(_T("PTS ���������� �����ϴ�."));
		return;
	}

	CArchive ar(&stream,CArchive::store);


	CString strID,strPass;

	GetDlgItemText(IDC_PTS_LOGIN_DLG_EDIT1 ,strID);
	GetDlgItemText(IDC_PTS_LOGIN_DLG_EDIT2 ,strPass);

	ar << strID << strPass;

	ar.Close();
	stream.Close();

	CDialogEx::OnOK();
}
