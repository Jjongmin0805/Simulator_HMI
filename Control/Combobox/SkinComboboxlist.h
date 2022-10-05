#ifndef _SKINCOMBOBOXLIST_H
#define _SKINCOMBOBOXLIST_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkinComboboxlist : public CListBox
{
// Construction
public:
	CSkinComboboxlist();
	virtual ~CSkinComboboxlist();

protected:
	COLORREF	 m_cfBackGround;	// ¹è°æ»ö
		
protected:
	afx_msg void OnPaint();
	
	DECLARE_MESSAGE_MAP()
};

#endif // _SKINCOMBOBOXLIST_H