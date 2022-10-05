#pragma once
#include "afx.h"

class AFX_EXT_CLASS CKASIM_ND :
	public CObject
{
public:
	CKASIM_ND(void);
	~CKASIM_ND(void);

public:
	int nND_ID;
	int nND_FBRID;
	int nND_TBRID;
	int nND_FCBSWID;
	int nND_TCBSWID;
	int nND_MUSW;
	int nND_FSVRID;
	int nND_TSVRID;
	CString szND_Name;
	CString szND_CEQ;
	CString szND_NDKey;

};

typedef CTypedPtrArray<CObArray, CKASIM_ND*> CKASIM_ND_Array;
