#pragma once


// CImage_AniPNG_LayerAddDLG ��ȭ �����Դϴ�.

class CImage_AniPNG_LayerAddDLG : public CDialog
{
	DECLARE_DYNAMIC(CImage_AniPNG_LayerAddDLG)

public:
	CImage_AniPNG_LayerAddDLG(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImage_AniPNG_LayerAddDLG();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_IAE_LAYERADD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_szLayerIndex;
	virtual void OnOK();
};
