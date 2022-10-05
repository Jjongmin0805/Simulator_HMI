
///��ȯ�� �ʿ��� ���� �Լ��� �����մϴ�.

//�����ڵ� �ѱۺ�ȯ
//void _WCS2MBS(CHAR* pszTarget, TCHAR* pszSource)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//
//	if(pszSource == NULL || pszTarget == NULL)
//		return;
//
//	int iLen = 0;
//	iLen = WideCharToMultiByte(CP_ACP, 0, pszSource, -1, NULL, 0, NULL, NULL);
//	WideCharToMultiByte(CP_ACP, 0, pszSource, -1, pszTarget, iLen, NULL, NULL);
//}
//
//void _MBS2WCS(TCHAR* pszTarget, CHAR* pszSource, UINT iBufSize)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//
//	if(pszSource == NULL || pszTarget == NULL)
//		return;
//
//	MultiByteToWideChar(CP_ACP, 0, pszSource, -1, pszTarget, iBufSize);
//}
typedef short SHORT;
typedef unsigned int UINT;
typedef wchar_t TCHAR;

#define PDB_NAME_SIZE	64
#define RTU_BUFF		32
#define COLOR_BUFF		10
#define PDB_NAME64_SZ	64
#define PDB_MESH22_SZ	22
#define _MAX_EQUIP_AIR_DATA_		28 //24
#define _MAX_LINE_DATA_				15 //8
#define _MAX_FI_DATA_				40 //29
#define _MAX_STATUS_DATA_			10
#define _MAX_SVR_DATA_				15
#define _MAX_CB_DATA_				10
#define _MAX_SUB_DATA_				30
#define _MAX_SE_DATA_				15
#define _MAX_PF_DATA_				17
#define	_MAX_PV_BI_DATA_			275
#define	_MAX_PV_AI_DATA_			104
#define _MAX_PV_A0_DATA_			16
#define	_MAX_PV_BO_DATA_			25
#define _MAX_GEN_DATA_				10

#define	_MAX_BESS_BI_DATA_			275	//96
#define	_MAX_BESS_AI_DATA_			104	//115
#define _MAX_BESS_A0_DATA_			16	//8
#define	_MAX_BESS_BO_DATA_			25	//8
//!< FI ������ Structure
typedef struct _fiData
{
	char   _evtId[32];			//�˶� �̺�Ʈ ���̵�
	int	   _id;					//���̵�
	int    _psr;				//PSR
	int	   _dl_fk;				//DL ���̵�
	bool   _isFaultRage;		//���� ���� ����� ����   
	int    _type;				//0 : �Ͻ�FI, 1 : ����FI
	bool   _faultUse;           // �Ͻ� ������ �ƴҶ�
	int    _Sectiontype;				//0 : �Ͼƿ�, 1 : ��
	long   _point;				// ����Ʈ ���̵�
	double _current[4];			//�������� ABCN
	bool   _status[4];			//����� ABCN
	int	   _FIPoint[10];		//��������Ʈ���
	long   _FITime[10];
	UINT   _time;				//�ð�
	long   _line;				//�����������ۼ���
	bool   _sectionFlag;		//section flag enable/disable
								//Section Flag�� enable�϶��� ����, �����̸� RUN, �����̸� Lockout
} FIDATA, *PFIDATA;

typedef struct _tagDIAGRAMLINEDATA
{
	long	dl_id;
	TCHAR	name[PDB_NAME_SIZE];
	TCHAR	substation[PDB_NAME_SIZE];
} DIAGRAMLINEDATA, *PDIAGRAMLINEDATA;

typedef struct _tagGenData
{
	int				pointType;
	int				mapId;
	int				position;
	float			data;						
	char			name[PDB_NAME_SIZE];
	//char			ptName[10][PDB_NAME_SIZE];
}GENDATA, *PGENDATA;

typedef struct _tagTerminalData
{
	//long			position;
	long			pointid;
	float			data;
	unsigned long	tlq;							

}TERMINALDATA, *PTERMINALDATA;

typedef struct _tagTerminalDataD
{
	int		stateGrpId;
	long	pointid;
	long	abnormal;
	int		data;
	unsigned long	tlq;	

}TERMINALDATAD, *PTERMINALDATAD;

typedef struct _tagSubDataD
{
	int		stateGrpId;
	long	pointId;
	TCHAR	upcName[PDB_NAME_SIZE];
	TCHAR	Name[PDB_NAME_SIZE];
	TCHAR	UnitName[PDB_NAME_SIZE];
	TCHAR	PtName[10][PDB_NAME_SIZE];
	int		data;

}SUBDATAD, *PSUBDATAD;

typedef struct _tagSubDataF
{
	long	pointId;
	TCHAR	upcName[PDB_NAME_SIZE];
	TCHAR	Name[PDB_NAME_SIZE];
	TCHAR	UnitName[PDB_NAME_SIZE];
	float	data;

}SUBDATAF, *PSUBDATAF;

typedef struct _tagAcm_DataD
{
	TCHAR	upcName[PDB_NAME_SIZE];
	int		Index;
	int		data;

}ACM_DATAD, *PACM_DATAD;

typedef struct _tagAcm_DataF
{
	TCHAR	upcName[PDB_NAME_SIZE];
	TCHAR	Name[PDB_NAME_SIZE];
	int		Index;
	float	data;

}ACM_DATAF, *PACM_DATAF;

typedef struct _tagLine_Data
{
	int		LINSEC_ID;			//ACM_DATAF	LINSEC_ID;					//���̵�
	float	LINSEC_3PLOADMW;	//ACM_DATAF	LINSEC_3PLOADMW;			//��������
	float	LINSEC_3PLOADMVAR;	//ACM_DATAF	LINSEC_3PLOADMVAR;			//��������
	int		LINSEC_STATE;		//ACM_DATAD	LINSEC_STATE;				//��Ȱ������
	int		LINSEC_ISLNO;		//ACM_DATAD	LINSEC_ISLNO;				//�������� ��ȣ
	int		LINSEC_ISLDL;		//ACM_DATAD	LINSEC_ISLDL;				//�������� DL
	float	LINSEC_LOSS;		//ACM_DATAF	LINSEC_LOSS;				//���� �ս�
	int		LINSEC_FI;			//ACM_DATAD	LINSEC_FI;					//����߻� ����
	int		LINSEC_COLOR;		//ACM_DATAD	LINSEC_COLOR;				//�ǽð� ���� ����
	int		LINSEC_LENTH;		//ACM_DATAD	LINSEC_LENTH;				//���Ǳ���
	int		LINSEC_TYPEPH;		//ACM_DATAD	LINSEC_TYPEPH;				//����(Phase)
	int		LINSEC_TYPEGND;		//ACM_DATAD	LINSEC_TYPEGND;				//����(Ground)
	int		LINSEC_MAXAMP;		//ACM_DATAD	LINSEC_MAXMAP;				//�����������
	int		LINSEC_ISOVL;		//ACM_DATAD	LINSEC_ISOVL;				//�����Ϲ߻�����
	int		LINSEC_ISOVV;		//ACM_DATAD	LINSEC_ISOVV;				//�����й߻�����
	int		LINSEC_ISLOV;		//ACM_DATAD	LINSEC_ISLOV;				//�����й߻�����

}LINEDATA, *PLINEDATA;

typedef struct _tagBLOCKVIEWDATA
{
	UINT	CEQID;                    /*CEQ ID */
	UINT	SSFK;                     /*������ Id*/
	UINT	DLFK;                     /*DL ID */
	UINT	DPCODE;					  /*DP ID */
	TCHAR	DPName[PDB_NAME64_SZ];	  /*DP Name*/
	UINT	PSRTYFK;                  /*PSRTYPE ID  */
	UINT	BVFK;                     /*�������� ID */
	TCHAR	mRIDFK[PDB_NAME64_SZ];    /*m_RID FK */	
	TCHAR	Name[PDB_NAME64_SZ];      /*����� */	
	UINT	Phase;                    /*�󿬰����� */	
	UINT	EQCFK;                    /*EquipmentContainer Id */	
	UINT	DpGrpId;                  /*����������Ʈ ��з�*/
	UINT	CircuitNo;                /*ȸ�� ��ȣ */
	TCHAR	MeshNo[PDB_MESH22_SZ];   /*����ȭ ��ȣ */	
	UINT	RUID;                     /*RTU ID*/	
	UINT	RTUType;				  /*�ڼ��� ���� 1 : ���� 1< :�ڵ� */
	UINT	switchType;				  /* ����ġ ���� Normal, Section, Tie, */
	UINT	RTUMapId;					  /* RTU MAP ID */
	//int		out_dl;
	//int		switchType;
	//bool	fauto;
	//int		rtype;							//!< 1:NOTCONNECT, 2:FRTU 3:FIED
	//long	color[2];
	UINT	ppid;
	//long	linktype;

	/*	���ο�	*/
	float	line;
	TCHAR	linename[PDB_NAME_SIZE];
	//char	loadname[PDB_NAME_SIZE];
	//float	secload;

	long	acmlinepoint;
	long	acmfnpoint;
	long	acmtnpoint;

	ACM_DATAF  acmSedata[_MAX_SE_DATA_];
	ACM_DATAF  acmPfdata[_MAX_PF_DATA_];

	double	linesedata[_MAX_LINE_DATA_];
	double  linepfdata[_MAX_LINE_DATA_];

	TERMINALDATA	data[_MAX_EQUIP_AIR_DATA_];
	TERMINALDATAD	datad[_MAX_FI_DATA_];
	TERMINALDATA	svrData[_MAX_SVR_DATA_];
	//TERMINALDATAD	statusdata[_MAX_STATUS_DATA_];
} BLOCKVIEWDATA, *PBLOCKVIEWDATA;

typedef struct _tagBLOCKSUBDATA
{
	UINT	CEQID;                    /*CEQ ID */
	UINT	SSFK;                     /*������ Id*/
	UINT	DLFK;                     /*DL ID */
	UINT	DPCODE;					  /*DP ID */
	TCHAR	DPName[PDB_NAME64_SZ];	  /*DP Name*/
	UINT	PSRTYFK;                  /*PSRTYPE ID  */
	TCHAR	Name[PDB_NAME64_SZ];      /*����� */	
	UINT	DpGrpId;                  /*����������Ʈ ��з�*/
	UINT	CircuitNo;                /*ȸ�� ��ȣ */
	TCHAR	MeshNo[PDB_MESH22_SZ];    /*����ȭ ��ȣ */	
	UINT	RUID;                     /*RTU ID*/	
	UINT	RTUType;				  /*�ڼ��� ���� 1 : ���� 1< :�ڵ� */
	UINT	switchType;				  /* ����ġ ���� Normal, Section, Tie, */

	SUBDATAD	discrete[_MAX_SUB_DATA_];
	SUBDATAF	measurement[_MAX_SUB_DATA_];

} BLOCKSUBDATA, *PBLOCKSUBDATA;

typedef struct _tagBLOCKPVDATA
{
	UINT	CEQID;                    /*CEQ ID */
	UINT	SSFK;                     /*������ Id*/
	UINT	DLFK;                     /*DL ID */
	UINT	DPCODE;					  /*DP ID */
	TCHAR	DPName[PDB_NAME64_SZ];	  /*DP Name*/
	UINT	PSRTYFK;                  /*PSRTYPE ID  */
	TCHAR	Name[PDB_NAME64_SZ];      /*����� */	
	UINT	DpGrpId;                  /*����������Ʈ ��з�*/
	UINT	CircuitNo;                /*ȸ�� ��ȣ */
	TCHAR	MeshNo[PDB_MESH22_SZ];    /*����ȭ ��ȣ */	
	UINT	RUID;                     /*RTU ID*/	
	UINT	RTUType;				  /*�ڼ��� ���� 1 : ���� 1< :�ڵ� */
	UINT	switchType;				  /* ����ġ ���� Normal, Section, Tie, */
	UINT	MapID;					  /* RTUMAP ID */
	SUBDATAD	discrete[_MAX_PV_BI_DATA_];
	SUBDATAD	setdiscrete[_MAX_PV_BO_DATA_];
	SUBDATAF	measurement[_MAX_PV_AI_DATA_];
	SUBDATAF	setmeasurement[_MAX_PV_A0_DATA_];


} BLOCKPVDATA, *PBLOCKPVDATA;

typedef struct _tagBLOCKBESSDATA
{
	UINT	CEQID;                    /*CEQ ID */
	UINT	SSFK;                     /*������ Id*/
	UINT	DLFK;                     /*DL ID */
	UINT	DPCODE;					  /*DP ID */
	TCHAR	DPName[PDB_NAME64_SZ];	  /*DP Name*/
	UINT	PSRTYFK;                  /*PSRTYPE ID  */
	TCHAR	Name[PDB_NAME64_SZ];      /*����� */	
	UINT	DpGrpId;                  /*����������Ʈ ��з�*/
	UINT	CircuitNo;                /*ȸ�� ��ȣ */
	TCHAR	MeshNo[PDB_MESH22_SZ];    /*����ȭ ��ȣ */	
	UINT	RUID;                     /*RTU ID*/	
	UINT	RTUType;				  /*�ڼ��� ���� 1 : ���� 1< :�ڵ� */
	UINT	switchType;				  /* ����ġ ���� Normal, Section, Tie, */
	UINT	MapID;					  /* RTUMAP ID */
	SUBDATAD	discrete[_MAX_BESS_BI_DATA_];
	SUBDATAD	setdiscrete[_MAX_BESS_BO_DATA_];
	SUBDATAF	measurement[_MAX_BESS_AI_DATA_];
	SUBDATAF	setmeasurement[_MAX_BESS_A0_DATA_];

} BLOCKBESSDATA, *PBLOCKBESSDATA;

typedef struct _tagTreeData
{
	UINT	CEQID;
	UINT	STATUS;
	UINT	RUID;

}TREEDATA, *PTREEDATA;

typedef struct _tagRTUINFO
{	
	TCHAR	dl[64];				// D/L ��
	TCHAR	CEQID[64];			// CEQID
	TCHAR	name[64];			// �����
	TCHAR	proto[256];			// ��������
	TCHAR	commType[256];		// ��Ź��
	TCHAR	psrName[256];		// ��������
	TCHAR	equipType[256];

}RTUINFO, *PRTUINFO;