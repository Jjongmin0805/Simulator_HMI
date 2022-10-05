
///변환에 필요한 공통 함수를 정의합니다.

//유니코드 한글변환
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
//!< FI 데이터 Structure
typedef struct _fiData
{
	char   _evtId[32];			//알람 이벤트 아이디
	int	   _id;					//아이디
	int    _psr;				//PSR
	int	   _dl_fk;				//DL 아이디
	bool   _isFaultRage;		//고장 구간 개폐기 유무   
	int    _type;				//0 : 일시FI, 1 : 순간FI
	bool   _faultUse;           // 일시 순간이 아닐때
	int    _Sectiontype;				//0 : 록아웃, 1 : 런
	long   _point;				// 포인트 아이디
	double _current[4];			//고장전류 ABCN
	bool   _status[4];			//고장상 ABCN
	int	   _FIPoint[10];		//고장포인트목록
	long   _FITime[10];
	UINT   _time;				//시간
	long   _line;				//정전구역시작선로
	bool   _sectionFlag;		//section flag enable/disable
								//Section Flag가 enable일때만 동작, 닫힘이면 RUN, 열림이면 Lockout
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
	int		LINSEC_ID;			//ACM_DATAF	LINSEC_ID;					//아이디
	float	LINSEC_3PLOADMW;	//ACM_DATAF	LINSEC_3PLOADMW;			//구간부하
	float	LINSEC_3PLOADMVAR;	//ACM_DATAF	LINSEC_3PLOADMVAR;			//구간부하
	int		LINSEC_STATE;		//ACM_DATAD	LINSEC_STATE;				//사활선정보
	int		LINSEC_ISLNO;		//ACM_DATAD	LINSEC_ISLNO;				//독립계통 번호
	int		LINSEC_ISLDL;		//ACM_DATAD	LINSEC_ISLDL;				//독립계통 DL
	float	LINSEC_LOSS;		//ACM_DATAF	LINSEC_LOSS;				//구간 손실
	int		LINSEC_FI;			//ACM_DATAD	LINSEC_FI;					//고장발생 유무
	int		LINSEC_COLOR;		//ACM_DATAD	LINSEC_COLOR;				//실시간 선로 색상
	int		LINSEC_LENTH;		//ACM_DATAD	LINSEC_LENTH;				//섹션긍장
	int		LINSEC_TYPEPH;		//ACM_DATAD	LINSEC_TYPEPH;				//선종(Phase)
	int		LINSEC_TYPEGND;		//ACM_DATAD	LINSEC_TYPEGND;				//선종(Ground)
	int		LINSEC_MAXAMP;		//ACM_DATAD	LINSEC_MAXMAP;				//열적허용전류
	int		LINSEC_ISOVL;		//ACM_DATAD	LINSEC_ISOVL;				//과부하발생여부
	int		LINSEC_ISOVV;		//ACM_DATAD	LINSEC_ISOVV;				//과전압발생여부
	int		LINSEC_ISLOV;		//ACM_DATAD	LINSEC_ISLOV;				//저전압발생여부

}LINEDATA, *PLINEDATA;

typedef struct _tagBLOCKVIEWDATA
{
	UINT	CEQID;                    /*CEQ ID */
	UINT	SSFK;                     /*변전소 Id*/
	UINT	DLFK;                     /*DL ID */
	UINT	DPCODE;					  /*DP ID */
	TCHAR	DPName[PDB_NAME64_SZ];	  /*DP Name*/
	UINT	PSRTYFK;                  /*PSRTYPE ID  */
	UINT	BVFK;                     /*기준전압 ID */
	TCHAR	mRIDFK[PDB_NAME64_SZ];    /*m_RID FK */	
	TCHAR	Name[PDB_NAME64_SZ];      /*설비명 */	
	UINT	Phase;                    /*상연결정보 */	
	UINT	EQCFK;                    /*EquipmentContainer Id */	
	UINT	DpGrpId;                  /*데이터포인트 대분류*/
	UINT	CircuitNo;                /*회로 번호 */
	TCHAR	MeshNo[PDB_MESH22_SZ];   /*전산화 번호 */	
	UINT	RUID;                     /*RTU ID*/	
	UINT	RTUType;				  /*자수동 구분 1 : 수동 1< :자동 */
	UINT	switchType;				  /* 스위치 구분 Normal, Section, Tie, */
	UINT	RTUMapId;					  /* RTU MAP ID */
	//int		out_dl;
	//int		switchType;
	//bool	fauto;
	//int		rtype;							//!< 1:NOTCONNECT, 2:FRTU 3:FIED
	//long	color[2];
	UINT	ppid;
	//long	linktype;

	/*	선로용	*/
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
	UINT	SSFK;                     /*변전소 Id*/
	UINT	DLFK;                     /*DL ID */
	UINT	DPCODE;					  /*DP ID */
	TCHAR	DPName[PDB_NAME64_SZ];	  /*DP Name*/
	UINT	PSRTYFK;                  /*PSRTYPE ID  */
	TCHAR	Name[PDB_NAME64_SZ];      /*설비명 */	
	UINT	DpGrpId;                  /*데이터포인트 대분류*/
	UINT	CircuitNo;                /*회로 번호 */
	TCHAR	MeshNo[PDB_MESH22_SZ];    /*전산화 번호 */	
	UINT	RUID;                     /*RTU ID*/	
	UINT	RTUType;				  /*자수동 구분 1 : 수동 1< :자동 */
	UINT	switchType;				  /* 스위치 구분 Normal, Section, Tie, */

	SUBDATAD	discrete[_MAX_SUB_DATA_];
	SUBDATAF	measurement[_MAX_SUB_DATA_];

} BLOCKSUBDATA, *PBLOCKSUBDATA;

typedef struct _tagBLOCKPVDATA
{
	UINT	CEQID;                    /*CEQ ID */
	UINT	SSFK;                     /*변전소 Id*/
	UINT	DLFK;                     /*DL ID */
	UINT	DPCODE;					  /*DP ID */
	TCHAR	DPName[PDB_NAME64_SZ];	  /*DP Name*/
	UINT	PSRTYFK;                  /*PSRTYPE ID  */
	TCHAR	Name[PDB_NAME64_SZ];      /*설비명 */	
	UINT	DpGrpId;                  /*데이터포인트 대분류*/
	UINT	CircuitNo;                /*회로 번호 */
	TCHAR	MeshNo[PDB_MESH22_SZ];    /*전산화 번호 */	
	UINT	RUID;                     /*RTU ID*/	
	UINT	RTUType;				  /*자수동 구분 1 : 수동 1< :자동 */
	UINT	switchType;				  /* 스위치 구분 Normal, Section, Tie, */
	UINT	MapID;					  /* RTUMAP ID */
	SUBDATAD	discrete[_MAX_PV_BI_DATA_];
	SUBDATAD	setdiscrete[_MAX_PV_BO_DATA_];
	SUBDATAF	measurement[_MAX_PV_AI_DATA_];
	SUBDATAF	setmeasurement[_MAX_PV_A0_DATA_];


} BLOCKPVDATA, *PBLOCKPVDATA;

typedef struct _tagBLOCKBESSDATA
{
	UINT	CEQID;                    /*CEQ ID */
	UINT	SSFK;                     /*변전소 Id*/
	UINT	DLFK;                     /*DL ID */
	UINT	DPCODE;					  /*DP ID */
	TCHAR	DPName[PDB_NAME64_SZ];	  /*DP Name*/
	UINT	PSRTYFK;                  /*PSRTYPE ID  */
	TCHAR	Name[PDB_NAME64_SZ];      /*설비명 */	
	UINT	DpGrpId;                  /*데이터포인트 대분류*/
	UINT	CircuitNo;                /*회로 번호 */
	TCHAR	MeshNo[PDB_MESH22_SZ];    /*전산화 번호 */	
	UINT	RUID;                     /*RTU ID*/	
	UINT	RTUType;				  /*자수동 구분 1 : 수동 1< :자동 */
	UINT	switchType;				  /* 스위치 구분 Normal, Section, Tie, */
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
	TCHAR	dl[64];				// D/L 명
	TCHAR	CEQID[64];			// CEQID
	TCHAR	name[64];			// 설비명
	TCHAR	proto[256];			// 프로토콜
	TCHAR	commType[256];		// 통신방식
	TCHAR	psrName[256];		// 설비종류
	TCHAR	equipType[256];

}RTUINFO, *PRTUINFO;