#define RTU_BUFF		32
#define PDB_SZ_NAME		64
#define COLOR_BUFF		10
#define	MAX_STRING		(64)
#define	POLLING_TIME	10					//���� ���� �ֱ�
#define ALARM_POLLING_TIME			50
#define ASYNC_POLLING_TIME			500
#define	MAX_ALARM_QUEUE_SIZE		5000
#define ASYNC_FAIL_POLLING_TIME		3000

/////�ӽ� �÷� �ڵ�
#define COLOR_CODE_BLACK		0          //1		
#define COLOR_CODE_WHITE		16777215   //2		
#define COLOR_CODE_RED			16711680   //3		
#define COLOR_CODE_BLUE			255		   //4		
#define COLOR_CODE_GREEN		65280	   //5		
#define COLOR_CODE_YELLOW		16776960   //6		
#define COLOR_CODE_MAGENTA		16711935   //7		
#define COLOR_CODE_CYAN			65535	   //8		
#define COLOR_CODE_IVORY		16777164   //9		
#define COLOR_CODE_WHITE_CYAN	13434879   //10		


//TLQ �ּ�
#define NORMAL						0x00000000
#define TLQ_CI							0x00000001	//!< ���� ���� ���� �±�
#define	TLQ_SI							0x00000002	//!< ������ ��� ���� �±�
#define TLQ_AI							0x00000004	//!< �˶� ���� �±�
#define TLQ_EI							0x00000008	//!< �̺�Ʈ ���� �±�
#define TLQ_CS							0x00000010	//!< ������/������ �±�
												  
#define TLQ_MH							0x00000020  //!< �ְ� ����ġ �±�
#define TLQ_ML							0x00000040	//!< ���� ����ġ �±�
#define TLQ_HL							0x00000080  //!< ����ġ �±�
#define TLQ_LL							0x00000100  //!< ����ġ �±�
												   
#define TLQ_CP							0x00000200  //!< ���� ������
#define TLQ_PS							0x00000400  //!< ����Ʈ ������
#define TLQ_MU							0x00000800  //!< ����� �������� �Է�
#define TLQ_NU							0x00001000  //!< ������Ʈ �ҷ�
#define TLQ_ON							0x00002000  //!< ������ ����
#define TLQ_OFF							0x00004000  //!< ����Ʈ Offline

//TLQ �ּ�
//#define NORMAL					0x00000000
//#define COE						0x00000001	//component operator updated
//#define	UAS						0x00000002	//using alternate data source
//#define BS						0x00000004	//bad state estimator value
//#define QD						0x00000008	//questionable quality of the data
//
//#define DC						0x00000010	//drift correction not being performed
//#define NU						0x00000020  //point wasn't updated during last scan
//#define RL						0x00000040	//reasonability limit exceeded
//#define ME						0x00000080  //the value is operator entered
//
//#define AB						0x00000100  //point is in a define abnordmal state
//#define RC						0x00000200  //rate of change limit exceeded
//#define HL						0x00000400  //high/low limit exceeded
//#define WO						0x00000800  //
//
//#define CI						0x00001000  //control inhibit tag
//#define AI						0x00002000  //alarms inhibit tag
//#define EI						0x00004000  //event inhibit tag
//#define SI						0x00008000  //scan inhibit tag
//
//#define UA						0x00010000  //alarms not completely acknowleded
//#define AE						0x00020000  //an alarm exists
//
//#define PS						0x00100000  //point is selected by dispatcher
//#define CIP						0x00200000  //control on point is in progress
//#define SQC						0x00400000  //sequence control for point in progress



// ��� TPCODE ���
enum ENUM_COMM_TPCODE {
	ENUM_COMM_TP_BI	= 0x0001,
	ENUM_COMM_TP_BO,
	ENUM_COMM_TP_AI,
	ENUM_COMM_TP_AO,
	ENUM_COMM_TP_PI,
	ENUM_COMM_TP_DMC,
	ENUM_COMM_TP_RTU,
	ENUM_COMM_TP_DCP,
	ENUM_COMM_TP_CAL,
	ENUM_COMM_TP_LINEST,
};
//-----------------------------------------------------------------------
// Summary:
//     ���� �� �ܼ��� ����Ʈ ����
// members:
//     gID        - ���� id
//     sID        - ���� id
//     fDL        - D/L üũ
//-----------------------------------------------------------------------
typedef struct _tagClassViewItem
{
	long	gID;		// �θ�
	long	sID;		// �ڽ�
	bool	fDL;		// D/L ����
	bool	fPW;		// ������ ����

	TCHAR	szName[MAX_STRING];
} CLASSVIEWITEM, *PCLASSVIEWITM;


//-----------------------------------------------------------------------
// Summary:
//     ���� �� �ܼ��� ����Ʈ ����
// members:
//     item        - Ŭ���� �������
//     file        - �ܼ��� ���ϸ�
//-----------------------------------------------------------------------
typedef struct _tagBLDDATA
{
	CLASSVIEWITEM	item;				// �� ������
	TCHAR			file[MAX_STRING];	// ���� ��
	UINT			itype;				// Ÿ��(�����ҳ� �ܼ���, �ܼ���)

}BDLDATA, *PBDLDATA;

//-----------------------------------------------------------------------
// Summary:
//     �ܼ��� Open List Type
// members:
//-----------------------------------------------------------------------
typedef struct _tagBLDOPENDATA
{
	UINT			itype;				// Ÿ��(�����ҳ� �ܼ���, �ܼ���)
	long			dlid;				// D/L id
	double			textSize;			//�ؽ�Ʈ ������
	double			zoomLevel;			//�� ����		1.0
	double			maxZoom;			//�ִ� �� ����	20     �ִ� 1 - 100
	double			minZoom;			//�ּ� �� ����   0.1    �ּ� 0.1 - 1
	double			zoomStep;			//�� ����		1 - 10
	double			startX;				//������ X��ǥ   �߽���
	double			startY;				//������ Y��ǥ	�߽���
	bool			fiMoving;			//FI �߻� �̵�	false
	unsigned int	layerse;			//!< ���̾� �ɼ� ó��	 PDB_P | PDB_Q | PDB_VA | PDB_VR
	unsigned int	layerpf;			//!< ���̾� �ɼ� ó��	 PDB_P | PDB_Q | PDB_VA | PDB_VR
	unsigned int	popup;				//!< ����� �ɼ� ó��  PDB_P | PDB_Q | PDB_VA | PDB_VR
	unsigned int	layer;				//!< ���̾� �ɼ� ó��  SECTION_MEASURE
	bool			popup_toggle;		//!< ����� ACM SE, PF �ɼ� ó�� false;
	bool			line_toggle;		//!< ���� ACM SE,PF, �ɼ� ó��	false;
	bool			fFlow;				//��������	false;
	bool			fMemo;				//�޸𺸱�	false;

}BLDOPENDATA, *PBLDOPENDATA;

//-----------------------------------------------------------------------
// Summary:
//     ���� Ÿ��
// members:
//-----------------------------------------------------------------------
enum CONDUCTINGEQUIPTYPE
{
	CONDUCTING = 1,				// ����
	COMPOSITE,					// ����ȸ��
	UNDERGROUNDTRNAS,			// ���ߺ��б�
	SVR,						//SVR
	DLINE,						//DTS
	MSUBSTATION,					//������
	SUBGEO,						
	GEO,
	POWER,
	STS,						//��������
	SHUNT,						//Shunt Capacitor
};

//-----------------------------------------------------------------------
// Summary:
//     distribute transformer Ÿ��
// members:
//-----------------------------------------------------------------------
enum DISTRIBUTETRANSFORMERTYPE
{
	DSVR = 1,				// SVR
	DUNDERG,				// ����
};

//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ���� Ÿ��
// members:
//-----------------------------------------------------------------------
enum REMOTEUNITTYPE
{
	MENUAL = 1,					// ����
	FRTU,						// �ڵ�
	FIED						// �ڵ�
};

//-----------------------------------------------------------------------
// Summary:
//     ���� Ÿ��
// members:
//-----------------------------------------------------------------------
enum EQUIPTYPE
{
	BREAKER = 1,				//
	LOADBREAKSWITCH,
	DRUNITS = 8,
};

//-----------------------------------------------------------------------
// Summary:
//     ���� ��ſ� �Ķ����
// members:
//-----------------------------------------------------------------------
enum 
{
	DIDO_OPERATOR = 1,			// ���������
	AO_OPERATOR,				// �����Ķ��������
	AI_OPERATOR,				// �������
	CO_OPERATOR,				// ���հ���
	WA_OPERATOR,				// ������
	BI_OPERATOR,				// BI'
	BO_OPERATOR					// BO
};

//-----------------------------------------------------------------------
// Summary:
//     ����ȸ�� �� ��������
// members:
//-----------------------------------------------------------------------
typedef struct _tagEXTRADATA
{
	TCHAR name[RTU_BUFF];					// ��� ȸ���̸�
	TCHAR psr[RTU_BUFF];					// ���� psr��

	long equipid;							// ��� id
	long id;								// ���� ����� id
	long psrtype;							// psr

} EXTRADATA, *PEXTRADATA;


#define MAX_EQUIP_IN_CONTINER		6		// �ִ� ��ⰹ��
//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagCONDUCTING
{
	long		ceqid;                         		//  ConductionEquipment ID 
	long		eq_fk;                              //  Equipment ID           
	long		ec_fk;                             	//  Equipment Container ID(Transformer, Composit, etc)  
	long		st_fk;                              //  SubStation ID            
	long		dl_fk;                              //  Distribution Line ID          
	long		link_st_fk;                         //  Link SubStation ID           
	long		link_dl_fk;                         //  Link Distribution Line ID           
	long		psrtype;                            //  PowerSystemResource Type ID             
	char		name[RTU_BUFF];              		//  Equipment Name 
	char		ec_name[RTU_BUFF];              	//  parent Name 
	char		mesh_no[RTU_BUFF];					//	Equipment Mesh Number
	UINT	    sw_type;                           	//  �ܸ�/��ÿ��� ���� ǥ��      
	long		rtu_type;                          	//  Equipment RTU Type(1:NormalEquipment,2:MTR, 3:SVR, 4:Transformer ����, 5:Transformer ����, etc)    
	CHAR		dev_no[RTU_BUFF];					//  Equipment Device Number        
	long		dtr_fk;                          	//  distributionTransformer ID(Transformer ����)        
	long		ptr_fk;                          	//  PowerTransformer ID(���� ����-Busbarsection, Breaker, Disconnect, etc)        
	long		link_cb_fk;                         //  Link Breaker ID(Disconnect)        
	long		link_bbs_fk;                        //  Link BusBarSection ID(Disconnect)
	float		base_voltage;						//  ���� ����
	UINT		phases;								//  �󿬰�����(A,B,C,N)
	UINT		busbar_order;                       //  Busbarsection Order(1����,2����)	 
	UINT		ai_cnt;								// Analog Input Point Count
	long		ai_pid;								// Start Analog Point ID
	UINT		ao_cnt;								// Analog Output Point Count
	long		ao_pid;								// Start SetPoint ID
	UINT		bi_cnt;								// Binary Input Point Count
	long		bi_pid;								// Start Discrete Point ID
	UINT		bo_cnt;								// Binary Output Point Count
	long		bo_pid;								// Start Command Point ID
	UINT		pi_cnt;								// Counter Point Count
	long		pi_pid;								// Start Accumulator Point ID

} CONDUCT, *PCONDUCT;
//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagREMOTEUNIT
{
	long powerid;					// ������ id
	long dlid;						// D/L id
	
	long remoteid;					// RTU id
	long psrid;						// PSR id
	long dmcid;						// DMC id

	long linecnt;					// ȸ�� ����
	long csid;						// composite id
	int map;						// rtu map
	long rtype;						// ����Ʈ ����Ÿ��(����, FRTU, FIED)

	CONDUCTINGEQUIPTYPE type;		// ������� 
	EXTRADATA	data[MAX_EQUIP_IN_CONTINER];				// ����ȸ�� ����

	TCHAR	name[RTU_BUFF];			// �����
	TCHAR	status[RTU_BUFF];		// ����
	TCHAR	method[RTU_BUFF];		// ���(������)
	TCHAR	station[RTU_BUFF];		// �����Ҹ�
	TCHAR	dl[RTU_BUFF];			// D/L��
	TCHAR	proto[RTU_BUFF];		// ��������
	TCHAR	psrname[RTU_BUFF];		// psr

	CONDUCT pequip; // DTS ���踦 ���� EQUIPMENT ����

} REMOTEUNIT, *PREMOTEUNIT;


//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� ���� Ȯ��
// members:
//-----------------------------------------------------------------------
typedef struct _tagREMOTEUNITEX : _tagREMOTEUNIT
{
	UINT	type;

} REMOTEUNITEX, *PREMOTEUNITEX;


//-----------------------------------------------------------------------
// Summary:
//     �л����� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagDRUNIT
{
	long drid;								// �л����� id

	TCHAR	name[MAX_STRING];				// ��������
	TCHAR	turbin[MAX_STRING];				// �����뷮
	TCHAR	curtrubin[MAX_STRING];			// ���������
	TCHAR	volt[MAX_STRING];				// ��������
	TCHAR	arm[MAX_STRING];				// ��������
	TCHAR	prot[MAX_STRING];				// ��������
	TCHAR	comm[MAX_STRING];				// ���Ÿ��
	TCHAR	p[MAX_STRING];					// ��ȿ����
	TCHAR	q[MAX_STRING];					// ��ȿ����
	TCHAR	pf[MAX_STRING];					// ����
	TCHAR	var[MAX_STRING];				// ��ȿ ����
	TCHAR	kvar[MAX_STRING];				// ��ȿ ����

}DRUNIT, *PDRUNIT;


//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� ����(���뵵, �ܼ���)
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITINFO
{
	TCHAR	station[MAX_STRING];		// �����Ҹ�
	TCHAR	name[64];					// �����
	TCHAR	psrName[MAX_STRING];		// ����������
	TCHAR	MeshNo[MAX_STRING];			// ����ȭ��ȣ
	TCHAR	CeqID[64];					// CEQID
	TCHAR	dl[64];						// D/L ��
	//TCHAR	psr[64];					// ����Ÿ��
	TCHAR	type[MAX_STRING];			// ����/ �ڵ�
	TCHAR	istate[MAX_STRING];			// ���°�
	TCHAR	custate[MAX_STRING];		// ��ġ��
	TCHAR	create[MAX_STRING];			// ���ۻ�
	TCHAR	day[MAX_STRING];			// ��������
	TCHAR	proto[MAX_STRING];			// ��������
	TCHAR	commType[MAX_STRING];		// ��Ź��
	TCHAR	mAddress[MAX_STRING];		// Master Addr
	TCHAR	sAddress[MAX_STRING];		// Slave Addr
	TCHAR	Masterfep[MAX_STRING];		// Master dnp Info
	TCHAR	DnpAddress[MAX_STRING];		// ������ DNP �ּ�
	TCHAR	makeNo[MAX_STRING];			// ���� ��ȣ
	TCHAR	makeDate[MAX_STRING];		// ���� ��¥
	TCHAR	version[MAX_STRING];		// FRTU ����
	TCHAR	makeNo2[MAX_STRING];		// ���� ��ȣ2
	TCHAR	man[MAX_STRING];			// ��ġ ����

}UNITINFO, *PUNITINFO;

//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� ���� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITCTRLINFO
{
	long	psr;						// psr type
	long	equipid;					// ���� id
	long	pointid;					// ���� ����Ʈ
	long	eqtype;						// ���� Ÿ��

	TCHAR	name[MAX_STRING];			// �����
	TCHAR	psrname[MAX_STRING];		// psr ��
	TCHAR	point[MAX_STRING];			// ����Ʈ ��
}UNITCTRLINFO, *PUNITCTRLINFO;

//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� ����(����)
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITINFOVIEW
{
	TCHAR		szid[RTU_BUFF];					// ID
	TCHAR		szname[RTU_BUFF];				// �̸�
	TCHAR		szsubgeo[RTU_BUFF];				// �����
	TCHAR		szline[RTU_BUFF];				// ����
	TCHAR		szfinancier[RTU_BUFF];			// ����
	TCHAR		szloca[RTU_BUFF];				// ������ġ
	TCHAR		szrtutype[RTU_BUFF];			// ���������
	TCHAR		szswtype[RTU_BUFF];				// �ʱ����
	TCHAR		szcomm[RTU_BUFF];				// �������
} UNITINFOVIEW, *PUNITINFOVIEW;
//-----------------------------------------------------------------------
// Summary:
//    ����Ʈ �� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagPOINTALIASDATA
{
	long	index;					// ����Ʈ �� index
	short	value;					// ��
	TCHAR	szName[MAX_STRING];		// �� �̸�
	long	color;					// color

}POINTALIASDATA, *PPOINTALIASDATA;
//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� (����Ż)����, ���� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITDIGIINFO
{
	//long			cid;							// di,do id
	//long			cpoint;							// di,do point
	UINT			MapId;							// RTUMap Id
	UINT			DeviceId;						// RTU Device Id
	UINT			Index;							// Map Index
	UINT			linkpoint;						// di,do position
	UINT			CircuitNo;						// ȸ�ι�ȣ
	UINT			value;							// ��
	UINT			measureTypeId;					// ������ �з� id
	TCHAR			upc_name[RTU_BUFF];				// �̵���� �� ��û 
	TCHAR			upc_tlq[RTU_BUFF];				// �̵���� TLQ ��û
	TCHAR			upc_uptime[RTU_BUFF];			// �̵���� �ð� ��û

	UINT			ccnt;							// ī���� Ŀ���
	UINT			ccommand[15];					// Ŀ��尪
	TCHAR			szNames[15][RTU_BUFF];			// Ŀ��� ���� // �ϴ� ���� - valueAlias Name
	SHORT			szColor[COLOR_BUFF];			// ������ ���� ����

	UINT			tlq;							// TLQ

	TCHAR			szName[RTU_BUFF];				// name
	UINT			abnormalValue;					// Abnormal 
	UINT			normalValue;					// normal 
	UINT			colorFk[RTU_BUFF];				//color
	UINT			color[RTU_BUFF];				//colorFK

} UNITDIGIINFO, *PUNITDIGIINFO;


//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� (�Ƴ��α�)���� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITANALOGININFO
{
	UINT		MapId;							// RTU Device ID
	UINT		RTUMapId;						// RTUMap Id
	UINT		Position;						// ai, ao id index
	UINT		MeasureTypeID;					// measuretypeID
	//long		apos;							// ai, ao position
	UINT		CircuitNo;						// ai, ao line
	float		avalue;							// ��
	float		sfactor;						// ��������

	float		aminvalue;						// �ּҰ�
	float		amaxvalue;						// �ִ밪

	float		aminlimitvalue;					// �ּҰ�
	float		amaxlimitvalue;					// �ִ밪

	int			lnsec_ii_br;					// acm br index
	int			cbsw_ii_fnd;					// acm cb_fnd index
	int			cbsw_ii_tnd;					// acm cb_tnd index

	int			acmdataindex;					// acm data array index

	double		sevalue;						// se value
	double		pfvalue;						// pf value

	bool		fvalue;							// se, pf ����

	unsigned int	tlq;						// TLQ

	TCHAR		szName[RTU_BUFF];				// name
	TCHAR		szMeasure[RTU_BUFF];			// ����

	TCHAR			upc_name[RTU_BUFF];				// �̵���� �� ��û 
	TCHAR			upc_tlq[RTU_BUFF];				// �̵���� TLQ ��û
	TCHAR			upc_uptime[RTU_BUFF];			// �̵���� �ð� ��û

}UNITANALOGININFO, PUNITANALOGININFO;


//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� (�Ƴ��α�)����, ���� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagPOINTINFODATA
{
	long		aid;
	long		tlq;

}POINTINFODATA, *PPOINTINFODATA;


//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� ������ ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITWAVEINFO
{
	TCHAR		szpath[MAX_STRING];				// ���
	TCHAR		sztype[MAX_STRING];				// ����
	TCHAR		sztime[MAX_STRING];				// �ð�
	TCHAR		szsamp[MAX_STRING];				// ���ø�
	TCHAR		szFile[MAX_STRING];				// �����̸�

}UNITWAVEINFO, *PUNITWAVEINFO;


//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� (�Ƴ��α�)���� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITANALOGOUTINFO
{
	long		aid;							// ai, ao id
	long		apoint;							// ai, ao point
	long		apos;							// ai, ao position
	long		aline;							// ai, ao line
	float		avalue;							// ��
	float		adefault;						// ����Ʈ ��
	float		ascale;							// scalefator
	
	float		setvalue;						// ���� ��
	float		svrvalue;						// svr ������

	float		aminvalue;						// �ּҰ�
	float		amaxvalue;						// �ִ밪
	float		astepvalue;						// ���ܰ�

	int			groupindex;						// �׷� �ε���
	long		groupid;						// �׷� id
	int			grouptype;						// �׷� Ÿ��
	float		groupvalue;						// �׷� ��


	unsigned int	tlq;						// TLQ

	TCHAR		szName[RTU_BUFF];				// name
	TCHAR		szMeasure[RTU_BUFF];			// ����

}UNITANALOGOUTINFO, PUNITANALOGOUTINFO;


//-----------------------------------------------------------------------
// Summary:
//     ����Ʈ ���� ī��Ʈ ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITACCUMULATORINFO
{
	long		cid;							// ci, co id
	long		cpoint;							// ci, co point
	long		cpos;							// ci, co position
	long		cline;							// ci, co line
	float		cvalue;							// ���� ��

	float		cminvalue;						// limit�ּҰ�
	float		cmaxvalue;						// limit�ִ밪
	float		amaxvalue;						// max��

	float		asetvalue;						// max set��

	TCHAR		szName[RTU_BUFF];				// name
	TCHAR		szMeasure[RTU_BUFF];			// ����

}UNITACCUMULATORINFO, PUNITACCUMULATORINFO;

#define MAX_TAG			128


//-----------------------------------------------------------------------
// Summary:
//    �ܼ��� �˶�����(������� ����)
// members:
//-----------------------------------------------------------------------
typedef struct _tagBDLALARMDATA
{
	char    szEvtId[PDB_SZ_NAME];	//time-key - timestamp(16) + pointno(7)
	UINT	uiStation;				//������ ��ȣ
    UINT    uiDl;					//DL ��ȣ
    UINT    uiPtType;				//Point Type
    UINT    uiPtNo;					//Point Number
    UINT    uiEqNo;					//��� ��ȣ 
    float   fValue;					//Point�� ���� ��
    UINT    uiTlq;					//Point�� Tlq ��

	bool	fAck;
	bool	fReal[MAX_TAG];			// �ǽð�
}BDLALARMDATA, *PBDLALARMDATA;


//-----------------------------------------------------------------------
// Summary:
//    ���뵵, �˶�����͸� �˶�����
// members:
//-----------------------------------------------------------------------
typedef struct _tagALARMDATA
{
	char    szEvtId[PDB_SZ_NAME];	/*time-key - timestamp(16) + pointno(7)							*/
	UINT	uiFc;					/* Function Code : �˶�, �̺�Ʈ, ����, ��������, ��������, �������� */
	UINT	uiRtuTime;				/* ���忡�� ������ RTU �ð� ������ NULL */
	UINT	uiSvrTime;				/* ����ġ �������� �˶�/�̺�Ʈ �߻��� �ð� */
	UINT	uiStation;				/* �˶�/�̺�Ʈ�� �߻��� ������ ID */
	UINT	uiDL;					/* �˶�/�̺�Ʈ�� �߻��� DL ID */
	UINT	uiEqNo;					/* DMS �������� ������ ��� ���� ID */
	UINT	uiMapNo;				/* ��⺰ Index Map ��ȣ */
	UINT	uiPtType;				/* ��⺰ BI, BO, AI, AO, CNT */
	UINT	uiIndexNo;				/* DNP Index MAP ���� ������ ��ȣ SCADA ����� O */
	UINT	uiPid;					/* DMS �������� ������ ���� ��� ����Ʈ�� ���� ID ���� ��� 0 */
	FLOAT	fValue;					/* ���� ���� �� ������ */
	UINT	uiTlq;					/* �ش� PID�� TLQ�� */
	UINT	uiAlarmCode;			/* DMS�������� ���ǵ� �˶� �з� 10��� HMI���� ����, �Ҹ� ���� */
	TCHAR	szDesc[128];			/* �˶����� */
	UINT	uiSeqNo;				/* ������ ���� ID - HMI ��ȣ�� ���ǹ�ȣ�� �����Ͽ� ���� �������� �Ǵ� */
	bool	fAck;
	bool	fBlink;

	TCHAR szStation[PDB_SZ_NAME];	// ������ ��
	TCHAR szWave[MAX_STRING];		// �˶�����
	TCHAR szDL[PDB_SZ_NAME];		// D/L��
	TCHAR szEquip[PDB_SZ_NAME];		// �����
	TCHAR szAlarmCode[PDB_SZ_NAME];	// �˶� �ڵ�
	TCHAR szPointName[PDB_SZ_NAME]; // ����Ʈ ��


	//char    szEvtId[PDB_SZ_NAME]; //time-key - timestamp(16) + pointno(7)
 //   UINT	uiTime;					//�̺�Ʈ �߻� �ð�
 //   UINT	uiStation;				//������ ��ȣ
 //   UINT    uiDl;					//DL ��ȣ
 //   UINT    uiPtType;				//Point Type
 //   UINT    uiPtNo;					//Point Number
 //   UINT    uiEqNo;					//��� ��ȣ 
 //   float   fValue;					//Point�� ���� ��
 //   UINT    uiTlq;					//Point�� Tlq ��
 //   UINT	usCat;					//����Ʈ�� ���� Alarm Category Code
 //   UINT	usPri;					//Alarm Class �켱����
 //   UINT    byCl;					//Alarm Class ����
 //   UINT    byVo;					//Alarm Class �Ҹ� 
 //   UINT	usAC;					//Point�� ���� AcessArea Code
 //   TCHAR   szDesc[128];			//Alarm/Event�� �߻��� ������ ����
	//bool	fAck;
	//bool	fBlink;
	//
	//UINT	uiRtuTime;				//RTU Event �߻��ð� Seconds
	//UINT	uiRtuMics;				//RTU Event �߻��ð� Micro Seconds
	//UINT	uiSVRMics;				//SERVER Event �����ð� Micro Seconds
	//UINT	uiRtuid;				//RTU Id
	//UINT	uiCls;					//Alrm Class Id
	//UINT	uiEqType;				//

	//COLORREF	cfColor;

	//TCHAR szStation[PDB_SZ_NAME];	// ������ ��
	//TCHAR szWave[MAX_STRING];		// �˶�����
	//TCHAR szCate[PDB_SZ_NAME];		// ī�װ���
	//TCHAR szDL[PDB_SZ_NAME];		// D/L��
	//TCHAR szUnit[PDB_SZ_NAME];		// �����
	//TCHAR szPri[PDB_SZ_NAME];		// �˶� ����
	//TCHAR szPointName[PDB_SZ_NAME];

}VIEWALARMDATA, *PVIEWALARMDATA;

/*------------------------------------------------------------------------
 * ALARM QUEUE *
-------------------------------------------------------------------------*/
//typedef struct __stAlarmNode__
//{
//	int nHead;
//	int nTail;
//	ALARMDATA DATA[MAX_ALARM_QUEUE_SIZE];
//} ST_ALARM_NODE, *LPST_ALARM_NODE;

//-----------------------------------------------------------------------
// Summary:
//    �˶� ���͸� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagALARMFILTTER
{
	BOOL			fSET;				// ���͸� üũ
	BOOL			fcontinue;			// �ǽð� �˶� üũ

	bool			ftime;				// ���͸� �ð� üũ
	UINT			iStartTime;			// ���͸� ���۽ð�
	UINT			iEndTime;			// ���͸� ��

	bool			iStation[MAX_TAG];	// ������ ���͸�
	bool			iLevel[MAX_TAG];	// �˶� ���� ���͸�
	bool			iCate[MAX_TAG];		// ī�װ� ���͸�
	bool			iDL[MAX_TAG];		// D/L ���͸�

	UINT			iAck;				// ACK üũ(0 : Ack, 1 : unack, 2 : ��� üũ)
	UINT			iAlarm;				// �˶����� ( 0 : �˶�, 1, �̺�Ʈ,  2: ��� üũ)

// add New UI -----------------------
	time_t			start;
	time_t			end;
	TCHAR			name[MAX_STRING];
	int				index;

}ALARMFILTTER, *PALARMFILTTER;


//-----------------------------------------------------------------------
// Summary:
//    ����˻� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagSEARCHDATA
{
	long equipid;						// ���� id
	long psrid;							// psr id

	TCHAR geo[MAX_STRING];				// ����
	TCHAR sub[MAX_STRING];				// ����
	TCHAR sta[MAX_STRING];				// ������
	TCHAR dl[MAX_STRING];				// D/L
	TCHAR eq[MAX_STRING];				// ����
	TCHAR psr[MAX_STRING];				// psr

}SEARCHDATA, *PSEARCHDATA;


//-----------------------------------------------------------------------
// Summary:
//    ��м��밡 ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagENERGYCON
{
	//TCHAR	count[MAX_STRING];			// ����
	//TCHAR	dlname[MAX_STRING];			// �Ҽ� DL
	//TCHAR	id[MAX_STRING];				// ���밡 ��ȣ
	//TCHAR	name[MAX_STRING];			// ���밡 �̸�
	//TCHAR	power[MAX_STRING];			// �Һ�����
	//TCHAR	pri[MAX_STRING];			// �߿䵵
	//TCHAR	sms[MAX_STRING];			// sms
	//TCHAR	tel[MAX_STRING];			// ��ȭ

	TCHAR	 dlname[MAX_STRING];			// �Ҽ� DL
	TCHAR    Name[MAX_STRING];          /*�̸�                                         */
	TCHAR	 customerCount[MAX_STRING]; /*����(1)                                    */
	TCHAR	 pfixed[MAX_STRING];        /*�������P(100KW)                             */
	TCHAR	 qfixed[MAX_STRING];        /*�������Q(100Kvar)                           */
	TCHAR    Tel[MAX_STRING];           /*��ȭ��ȣ(02-)                                */
	TCHAR    HP[MAX_STRING];           /*�ڵ�����ȣ(010-)                             */
	TCHAR    Customer_key[MAX_STRING];  /*Custermer Key(80-)                           */
	TCHAR    Priority[MAX_STRING];      /*�߿䵵(1)                                    */
	TCHAR    SmsUse[MAX_STRING];        /*SMS(0: ������, 1: ���)                    */
}ENERGYCON, *PENERGYCON;


//-----------------------------------------------------------------------
// Summary:
//    ���� ����(����)
// members:
//-----------------------------------------------------------------------
typedef struct _tagLINESEC
{
	TCHAR	substation[MAX_STRING];		// ������
	TCHAR	dl[MAX_STRING];				// DL
	TCHAR	name[MAX_STRING];			// ���θ�
	TCHAR	front[MAX_STRING];			// ����
	TCHAR	back[MAX_STRING];			// �Ĵ�
	TCHAR	spec1[MAX_STRING];			//
	TCHAR	spec2[MAX_STRING];
	TCHAR	spec3[MAX_STRING];
	TCHAR	spec4[MAX_STRING];
	TCHAR	line[MAX_STRING];
	TCHAR	size[MAX_STRING];			// ũ��
	TCHAR	sang[MAX_STRING];			// ��, ����
	TCHAR	ac[MAX_STRING];				// ac / dc

}LINESEC, *PLINESEC;

//-----------------------------------------------------------------------
// Summary:
//    �޴��� ��������Ʈ ����(base struct)
// members:
//-----------------------------------------------------------------------
typedef struct _tagMENUALDATA
{
	long			id;						// ����Ʈ id
	TCHAR			szName[MAX_STRING];		// ����Ʈ ��
	UINT			uiTlq;					// Point�� Tlq ��
	bool			foverride;				// ��������Ʈ üũ

}MENUALDATA, *PMENUALDATA;

//-----------------------------------------------------------------------
// Summary:
//    �޴��� ��������Ʈ ����(�Ƴ��α�)
// members:
//-----------------------------------------------------------------------
typedef struct _tagAIMENUALDATA : _tagMENUALDATA
{
	float			curvalue;				// ���� ��
	float			setvalue;				// ���� ��
	float			maxvalue;				// �ִ�	��
	float			minvalue;				// �ּ� ��

}AIMENUALDATA, *PAIMENUALDATA;


//-----------------------------------------------------------------------
// Summary:
//    �޴��� ��������Ʈ ����(������)
// members:
//-----------------------------------------------------------------------
typedef struct _tagBIMENUALDATA : _tagMENUALDATA
{
	int				cnt;					// alias ī��Ʈ
	short			curvalue;				// ���� ���°�
	short			setvalue;				// ���氪
	POINTALIASDATA* paliasdata;				// ����Ÿ

	void operator=(const _tagBIMENUALDATA& rhs)
	{
		DataCopy(rhs);						// 
	}

	_tagBIMENUALDATA(const _tagBIMENUALDATA& rhs)
	{
		DataCopy(rhs);
	}
	
	_tagBIMENUALDATA() 
	{
		paliasdata = NULL;
	}

	~_tagBIMENUALDATA()
	{
		if(paliasdata)
			delete [] paliasdata;
	}

	void DataCopy(const _tagBIMENUALDATA& rhs)
	{
		id			= rhs.id;
		uiTlq		= rhs.uiTlq;
		cnt			= rhs.cnt;
		curvalue	= rhs.curvalue;
		setvalue	= rhs.setvalue;
		foverride	= rhs.foverride;

		_tcscpy_s(szName, rhs.szName);

		if(cnt > 0)
		{
			paliasdata = new POINTALIASDATA[cnt];
			memset(paliasdata, 0, sizeof(POINTALIASDATA) * cnt);
			memcpy(paliasdata, rhs.paliasdata, sizeof(POINTALIASDATA) * cnt);
		}
	}

	//-----------------------------------------------------------------------
	// Summary:
	//    ���°����� �ε��� ����
	// members:
	//-----------------------------------------------------------------------
	int GetValueIndex(short value)
	{
		int ret = -1;
	
		if(paliasdata)
		{
			for(int icnt = 0; icnt < cnt; icnt++)
			{
				if(paliasdata[icnt].value == value)
				{
					ret = icnt;
					break;
				}
			}
		}

		return ret;
	}

	//-----------------------------------------------------------------------
	// Summary:
	//    ���°����� ���°� �̸� ����
	// members:
	//-----------------------------------------------------------------------
	TCHAR* GetValueName(short value)
	{
		TCHAR* pVal = NULL;

		if(paliasdata)
		{
			for(int icnt = 0; icnt < cnt; icnt++)
			{
				if(paliasdata[icnt].value == value)
				{
					pVal = paliasdata[icnt].szName;
					break;
				}
			}
		}

		return pVal;
	}

}BIMENUALDATA, *PBIMENUALDATA;

//-----------------------------------------------------------------------
// Summary:
//    �޴��� ��������Ʈ ����(base struct)
// members:
//-----------------------------------------------------------------------
typedef struct _tagOVERRIDEDATA
{
	TCHAR szstation[MAX_STRING];		// ������
	TCHAR szdl[MAX_STRING];				// D/L
	TCHAR szunit[MAX_STRING];			// �����
	TCHAR szname[MAX_STRING];			// ����Ʈ ��
	long point;							// ����Ʈ id
	UINT type;							// ����Ʈ Ÿ��
	long tlq;							// tlq ��

}OVERRIDEDATA, *POVERRIDEDATA;

//-----------------------------------------------------------------------
// Summary:
//    �޴��� ��������Ʈ ����(�Ƴ��α�)
// members:
//-----------------------------------------------------------------------
typedef struct _tagANALOVERRIDEDATA : _tagOVERRIDEDATA
{
	float maxlimit;						// �ִ밪
	float minlimit;						// �ּҰ�
	float value;						// �ǽð� ��

}ANALOVERRIDEDATA, *PANALOVERRIDEDATA;

//-----------------------------------------------------------------------
// Summary:
//    �޴��� ��������Ʈ ����(������)
// members:
//-----------------------------------------------------------------------
typedef struct _tagDIGIOVERRIDEDATA : _tagOVERRIDEDATA
{
	short value;						// �ǽð� ��

}DIGIOVERRIDEDATA, *PDIGIOVERRIDEDATA;


//-----------------------------------------------------------------------
// Summary:
//    �޴��� ��������Ʈ ����(������)
// members:
//-----------------------------------------------------------------------
typedef struct _tagUPDATEBDLVIEWER
{
	bool fdlopen;					// �ܼ��� D/L �ε� üũ
	bool fficheck;					// fi �߻� üũ

	bool fupdate;					// �ܼ��� ������ ���� üũ
	bool fview;						// �ܼ��� �ε� üũ

	bool isactive;					// �ܼ��� Ȱ��ȭ üũ

} UPDATEBDLVIEWER, *PUPDATEBDLVIEWER;


//-----------------------------------------------------------------------
// Summary:
//    �޴��� ��������Ʈ ����(������)
// members:
//-----------------------------------------------------------------------
typedef struct _tagBDLUPDATEPOINT
{
	long	pointid;
	bool	data;

}BDLUPDATEPOINT, *PBDLUPDATEPOINT;


//-----------------------------------------------------------------------
// Summary:
//    �ܼ��� ����Ʈ ����
// members:
//-----------------------------------------------------------------------
typedef struct _taBDLVIEWDATA
{
	long	psrid;			 // psr id
	long	equipid;		 // ���� id
	long	remoteid;		 // ����Ʈ id
	int		in_dl;			 // ����
	int		out_dl;			 // �ܼ�
	bool	switchType;		 // ����ġ Ÿ��
	bool	fauto;			 // �ڵ� / ����

	BDLUPDATEPOINT	data[29]; // fi üũ ��� ����Ʈ

} BDLVIEWDATA, *PBDLVIEWDATA;


//-----------------------------------------------------------------------
// Summary:
//    ���� ����������(�л�����)
// members:
//-----------------------------------------------------------------------
typedef struct _tagHISMDATA
{
	long	point;						// ����Ʈ id
	int		index;						// ����Ʈ index
	float	data;						// ��

	TCHAR	name[MAX_STRING];			// ����Ʈ �̸�

}HISMDATA, *PHISMDATA;


//-----------------------------------------------------------------------
// Summary:
//    �޸�
// members:
//-----------------------------------------------------------------------
typedef struct _tagMEMODATA
{
	long	station;
	long	dl;
	long	equip;
	long	user;

	bool	fread;

	unsigned short status;

	time_t	time_reg;
	time_t	time_limit;

	TCHAR	szname[64];
	TCHAR	sztxt[128];
	TCHAR	szstation[MAX_STRING];
	TCHAR	szequip[MAX_STRING];
	TCHAR	szdl[MAX_STRING];
	TCHAR	szConstruct[MAX_STRING];

}MEMODATA, *PMEMODATA;


//-----------------------------------------------------------------------
// Summary:
//    �޼���
// members:
//-----------------------------------------------------------------------
typedef struct _tagMSGDATA
{	
	TCHAR	szname[64];
	int		type;

	long	id;
	long	user;
	time_t	time_reg;

	TCHAR	sztitle[MAX_STRING];
	TCHAR	sztxt[1000];

	bool	fread;

}MSGDATA, *PMSGDATA;

//-----------------------------------------------------------------------
// Summary:
//    ���б� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagTRANSBIDATA
{
	long	pointId;
	TCHAR  szname[MAX_STRING];
	UINT   data;

}TRANSBIDATA, *PTRANSBIDATA;

typedef struct _tagTRANSAIDATA
{
	long	pointId;
	TCHAR  szname[MAX_STRING];
	float	data;

}TRANSAIDATA, *PTRANSAIDATA;

typedef struct _tagTRANSFORMERLIST
{
	long	pid;			// ���б� id
	long	id;				// ���б�weding id
	long	station;		// ������ id
	long	dl;				// D/L id
	long	equip;			// ���� id
	long	type;			// ����
	long	dmcid;			// DMC point id
	TCHAR	szsubstation[MAX_STRING];	// ������
	TCHAR	szdl[MAX_STRING];			// D/L
	TCHAR	name[MAX_STRING];			// ���ֹ�ȣ
	TCHAR	szmash[MAX_STRING];			// ����ȭ��ȣ
	
	TRANSBIDATA		transBI[10];
	//TRANSAIDATA		transAI[122];
	short	status;

}TRANSFORMERLIST, *PTRANSFORMERLIST;

//-----------------------------------------------------------------------
// Summary:
//    �����ҳ� �ܼ��� ������ ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagDLSUBSTATION
{
	long	pid;				//������ ���̵�
	int		mtrsize;			//MTR ����
	int		bussize;			//���� ����
	int		dlsize;				//DL ����
	bool	fuse;				//��� ����

	char	szsubstation[MAX_STRING];	// ������ ��
	char	szmash[MAX_STRING];			// ������ ��ȣ
	
}DLSUBSTATION, *PDLSUBSTATION;

//-----------------------------------------------------------------------
// Summary:
//    �����ҳ� �ܼ��� ���б� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagTRANSFORMERINFO
{
	long		pid;					//���б� ���̵�
	long		twdId;					//winding ���̵�
	long		ceqId;					//winding CEQID
	char		szname[MAX_STRING];		//���б� ��
	int			fieldPos;				//���� ���� �켱 ����
	int			sstype;					//���б� Ÿ�� 1:GIS, 2:MCSG, 3:GIS + MCSG
	int			bbs_1fk;				//1�������� ���� ���̵�
	int			bbs_2fk;				//2�������� ���� ���̵�
	bool		checked;				//����� �Ϸ�
	
}TRANSFORMERINFO, *PTRANSFORMERINFO;

//-----------------------------------------------------------------------
// Summary:
//    �����ҳ� �ܼ��� ������ ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagBASBARINFO
{
	int			pid;						//���̵�
	char		szname[MAX_STRING];			//������ ��
	char		szaliasName[MAX_STRING];	//������ ��ȣ
	int			bufNo;						//������ġ 1: ����� ��, 2: ����
	bool		fservice;					//��� ����
	
}BASBARINFO, *PBASBARINFO;

//-----------------------------------------------------------------------
// Summary:
//    �����ҳ� �ܼ��� MTR/CB ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagMTRINFO
{
	int			pid;				//�극��Ŀ ���̵�
	int			pceqId;				//Conduct Equipment ID
	int			psr;				//Psr
	char		szname[MAX_STRING];	//���ܱ� �̸�
	int			ptrFk;				//���б� ���̵�
	char		deviceNo[MAX_STRING];			//��ġ ��ȣ
	bool		service;			//��� ����

	bool		IsOpen;				//����/����
	double		current[3];			//ABC ����
	bool		s43rc;				//43rc ����
	bool		ocrHan;				//�ѽ�
	bool		ocrSun;				//����
	bool		ocgrHan;			//�ѽ�
	bool		ocgrSun;			//����

	int			ds1;				//1�� ���ܱ� ���̵�
	int			ds2;				//2�� ���ܱ� ���̵�
	
}MTRINFO, *PMTRINFO;

//-----------------------------------------------------------------------
// Summary:
//    �����ҳ� �ܼ��� �ܷα� ����
// members:
//-----------------------------------------------------------------------
typedef struct _tagDISCONNECTOR
{
	int			pid;					//���ܱ� ���̵�
	char		szname[MAX_STRING];		//���ܱ� ��
	int			brFk;					//�극��Ŀ ���̵�
	int			bbsFk;					//������ ���̵�
	char		deviceNo[MAX_STRING];	//��ġ ���̵�
	
}DISCONNECTOR, *PDISCONNECTOR;

typedef struct _tagBDLTREND
{
	TCHAR szName[MAX_STRING];
	long equipid;
	long remoteid;

	long voltage_a;
	long voltage_b;
	long voltage_c;

	long curr_a;
	long curr_b;
	long curr_c;
	long curr_n;

	float voltage_va;
	float voltage_vb;
	float voltage_vc;

	float curr_va;
	float curr_vb;
	float curr_vc;
	float curr_vn;

}BDLTREND, *PBDLTREND;

//-----------------------------------------------------------------------
// Summary:
//   DTS ����
// members:
//-----------------------------------------------------------------------
//typedef struct _tagDTSINFO
//{
//	long	SectionId;			// ���� ���� id
//	
//	//TCHAR	szcontent[MAX_STRING];	// ���
//	//TCHAR	szunit[MAX_STRING];		// ����
//	//TCHAR	szvalue[MAX_STRING];	// ��
//
//	//float	DTS_Max_Temp[3];	// DTS �ְ�µ�
//	//float	DTS_Max_Dist[3];	// �Ÿ�
//	//float	CON_Max_Temp[3];	// ��ü �ְ�µ�
//	//float	CON_Max_Dist[3];	// ��ü �ְ� �Ÿ�
//	//float	CCR[3];				// ��� ��� ����
//
//	long   pointId[RTU_BUFF];
//	TCHAR  szname[MAX_STRING];
//	TCHAR  szunit[MAX_STRING];
//	float  Data[RTU_BUFF]; // 0:SectinId, 
//
//
//}DTSINFO, *PDTSINFO;
typedef struct _tagDTSINFO
{
	long   SectionId;			// ���� ���� id
	long   pointId;
	TCHAR  szname[MAX_STRING];
	TCHAR  szdesc[MAX_STRING];
	TCHAR  szunit[MAX_STRING];
	float  Data;
	long   dp_fk;
	long   last_update;

}DTSINFO, *PDTSINFO;

typedef struct _tagDTSINFOEX
{
	long	sectionid;

	long	dtsid_a;
	long	conid_a;

	long	dtsid_b;
	long	conid_b;

	long	dtsid_c;
	long	conid_c;

}DTSINFOEX, *PDTSINFOEX;

typedef struct _tagSTSINFO
{
	long   SectionId;			// ���� ���� id
	long   pointId;
	TCHAR  szname[MAX_STRING];
	TCHAR  szdesc[MAX_STRING];
	TCHAR  szunit[MAX_STRING];
	float  Data;
	long   dp_fk;
	long   last_update;

}STSINFO, *PSTSINFO;

typedef struct _tagMTRDATA
{
	long	pointId;			// ���� ���� id

	TCHAR  szname[MAX_STRING];
	float	data;
	//bool	dataD[5];	//0 : 79RY 1:OCR �ѽ� 2:OCR���� 3:OCGR �ѽ� 4;OCGR����
	//float	dataA[6];	//0 : ����  1: ����  2: ��ȿ���� 3: ��ȿ����  4 : �µ� 5 : OLTC 

}MTRDATA, *PMTRDATA;

//!< FI LIST ������ Structure
typedef struct _fiListData
{
//	char	evtId[32];				//�˶� �̺�Ʈ ���̵�
	long	station;
	long	dl;
    UINT	uiTime;					// �̺�Ʈ �߻� �ð�
	long	Id;						// ���̵�
	long	outpoint;				// bo point
	short	outvalue;				// bo point value
	long    psr;					// PSR
	UINT    type;					// 0 : �Ͻ�FI, 1 : ���� FI 2 : ���� �� = FI
	double  current[4];				// �������� ABCN
	bool	status[4];				// ����� ABCN
	TCHAR	szsubgeo[MAX_STRING];	// ����
	TCHAR	szstation[MAX_STRING];	// ������
	TCHAR	szdl[MAX_STRING];		// D/L
	TCHAR	szunit[MAX_STRING];		// ���ֹ�ȣ
	TCHAR	szPoint[MAX_STRING];	// ����Ʈ ��
	long	point;					// ����Ʈ id - ����Ʈ �ε���
	long	remoteid;				// ����Ʈ id
	bool	fisfi;
	bool	psowner;				// ps�����
	int		state;					// �������

} FILISTDATA, *PFILISTDATA;

typedef struct _tagFdSecList
{
	long	pid;			// ����
	long	id;				// FD �߻� ���� id
	long	psr;			// Fd �߻� ���� psr
	long	dl;				// D/L id

	TCHAR	szdl[MAX_STRING];			// D/L
	TCHAR	name[MAX_STRING];			// ���ֹ�ȣ
	short	status;			//���°�

}FDSECLIST, *PFDSECLIST;

typedef struct _tagSrResultList
{
	long	count;
	long	iSeq;			// ���� ����
	long	id;				// ����� CEQID
	long	dl;				// D/L id
	long	swtype;
	TCHAR	szHowTo[MAX_STRING];		//�������
	TCHAR	szdl[MAX_STRING];			// D/L
	TCHAR	name[MAX_STRING];			// ���ֹ�ȣ
	TCHAR	sname[MAX_STRING];
	TCHAR	sznames[15][MAX_STRING];		// ���ֹ�ȣ	
	short	status;			//���°�
	short	afterStatus;	//������ ���°�

}SRRESULTLIST, *PSRRESULTLIST;

typedef struct _tagDynSrList
{
	char	candidate_scheme_nm[32];				/* �������� �ĺ��� �������� Scheme ��			*/
	int		candidate_scheme_type;					/* �������� �ĺ��� �������� Scheme Ÿ��			*/
	int		candidate_swnum;						/* �������� �ĺ��� ����Ī Ƚ��					*/
	float	candidate_max_ld;						/* ���� ��ü�� �ִ� ���Ϸ�						*/
	int		candidate_fisibility;					/* �������� ���ɿ��� ǥ��						*/
	int		candidate_rank;							/* �������� �ĺ� �� �켱����					*/
	float	candidate_total_index;					/* �������� �ĺ� �� ����						*/
	float	candidate_swn_index;					/* ����Ī Ƚ�� �� ����						*/
	float	candidate_maxld_index;					/* �ִ� ���� �� ����							*/
	int		candidate_sw_sequence[5];				/* ����Ī ���� ������							*/
	int		candidate_sw_type[5];					/* ���� ������� cbsw Ÿ�� (CBSW: 1, TISW:2)	*/
	int		candidate_bf[3];						/* ������ü ����								*/
	float	candidate_lt[3];						/* ���� �� ������ü ��							*/
	float	candidate_bf_ld[3];						/* ������ü �� ���� ���Ϸ�						*/
	float	candidate_bf_magin[3];					/* ������ü �� ���� ���޿����뷮				*/
	float	candidate_bf_max_vdrop[3];				/* ������ü �� ���� �ִ� ���а���				*/
	float	candidate_bf_max_amp[3];				/* ������ü �� ���� �ִ� ����					*/

	int		reserved1;								/* ������1										*/
	int		reserved2;								/* ������2										*/
	int		reserved3;								/* ������3										*/
	int		reserved4;								/* ������4										*/

}DYNSRLINST, *PDYNSRLINST;

typedef struct _tagDMCINFO
{
	TCHAR		szName[PDB_SZ_NAME];
	TCHAR		szIP[PDB_SZ_NAME];
	long		dmc_state_id;
	long		dmc_type_id;
	long		dmc_cpu_id;
	long		dmc_memory_id;
	long		dmc_disk_id;
	long		dmc_nic_id;
	long		dmc_nicback_id;

}	DMCINFO,  *PDMCINFO;

//-----------------------------------------------------------------------
// Summary:
//    DMC RTU LIST
// members:
//-----------------------------------------------------------------------
typedef struct _tagDMCRTUINFO
{
	TCHAR		szSSName[PDB_SZ_NAME];
	TCHAR		szDLName[PDB_SZ_NAME];
	TCHAR		szAliasName[PDB_SZ_NAME];
	TCHAR		szName[PDB_SZ_NAME];
	TCHAR		szJSName[PDB_SZ_NAME];
	TCHAR		szProtocolName[PDB_SZ_NAME];
	TCHAR		szComm[PDB_SZ_NAME];
	TCHAR		szCommType[PDB_SZ_NAME];

	long		rtu_protocol_type;
	long		rtu_type;
	long		rtu_state_id;
	long		rtucommid;
	INT			m_nType;
	long		equipid;
	long		psrtype;
	long		dlid;

	int			state_value;

	unsigned int	colorFk[RTU_BUFF];			//color
	unsigned int	color[RTU_BUFF];			//colorFK

}DMCRTUINFO,  *PDMCRTUINFO;


#define WM_REQ_FIED		(WM_USER + 100)			// FIED ���¿�û
#define WM_REQ_EXIT		(WM_USER + 101)			// NMS ���� ��û

#define WM_RES_STATUS	(WM_USER + 100)			// NMS ��������
	#define RES_STATUS_NORMAL			0x0			// ���� �븻
	#define RES_STATUS_MASTER_ERROR		0x1			// ������ ����
	#define RES_STATUS_SLAVE_ERROR		0x2			// �����̺� ����
	#define RES_STATUS_FIED_ERROR		0x3			// FIED ��ũ����
	#define RES_STATUS_UNKNOW			0x4			// �˼� ����
	#define RES_STATUS_TIMEOUT			0x5			// ���� Ÿ�Ӿƿ�
	#define RES_STATUS_SERVER			0x6			// ���� down
	#define RES_STATUS_DCP				0x7			// dcp

typedef struct _tagNMSRTUINFO
{
	long		rtuid;
	long		equipid;
	long		dmcid;

	TCHAR		szName[MAX_STRING];

}NMSRTUINFO, *PNMSRTUINFO, *LPNMSRTUINFO;

//-----------------------------------------------------------------------
// Summary:
//    �ܼ��� ����ó�� ���α׷� ����Ʈ
// members:
//-----------------------------------------------------------------------
typedef struct _tagBROKENINFO
{
	long		dl; // index
	long		time;
	long		id;
	long		bopoint;
	long		bipoint;

	TCHAR		sztime[MAX_STRING];
	TCHAR		szrec[MAX_STRING];
	TCHAR		szcon[MAX_STRING];

}BROKENINFO, *PBROKENINFO;

typedef struct _tagAREAINFO
{
	

}AREAINFO, *PAREAINFO;

typedef struct _tagACMLINE
{

}ACMLINE, *PACMLINE;

typedef struct _tagDSRSECTION
{

}DSRSECTION, *PDSRSECTION;

typedef struct _tagRECOVERYCTRL
{
	long		dl;
	long		id;
	long		cpoint;
	long		spoint;
	TCHAR		name[MAX_STRING];
	short int	status;
	short int	cstatus;
	TCHAR		res[MAX_STRING];
	TCHAR		tx[MAX_STRING];
	time_t		time;
	short int	result;
	bool		command;
	bool		add;

}RECOVERYCTRL, *PRECOVERYCTRL;

//-----------------------------------------------------------------------
// Summary:
//    DMC Ʈ����Ʈ�� (������ ��)
// members:
//-----------------------------------------------------------------------
typedef struct _tagGeoTreeData
{
	long		count;
	long		depth;
	long		gid;
	long		sid;
	TCHAR		name[MAX_STRING];

}GEOTREEDATA, *PGEOTREEDATA;

//-----------------------------------------------------------------------
// Summary:
//    DMC Ʈ����Ʈ�� (��� ��)
// members:
//-----------------------------------------------------------------------
typedef struct _tagCommTreeData
{
	long		count;
	long		depth;
	long		gid;
	long		sid;
	TCHAR		name[MAX_STRING];
	HTREEITEM	htree;

}COMMTREEDATA, *PCOMMTREEDATA;


//-----------------------------------------------------------------------
// Summary:
//    DMC ����Ʈ��Ʈ�� 
// members:
//-----------------------------------------------------------------------

typedef struct _tagGeoSubListData
{
	long	subgeoid;
	TCHAR	subgeoname[MAX_STRING];

}GEOSUBLISTDATA, *PGEOSUBLISTDATA;


typedef struct _tagStationListData : public _tagGeoSubListData
{
	long	stationid;
	TCHAR	stationname[MAX_STRING];

}STATIONLISTDATA, *PSTATIONLISTDATA;





typedef struct _tagBankListData : public _tagStationListData
{
	long	bankid;
	TCHAR	bankname[MAX_STRING];
	float	ratefan;
	float	ratenormal;
	
}BANKLISTDATA, *PBANKLISTDATA;


typedef struct _tagDLListData : public _tagBankListData
{
	long	dlid;
	TCHAR	dlname[MAX_STRING];
	long	breakerid;
	long	cbid;
	float	value;

}DLLISTDATA, *PDLLISTDATA;


typedef struct _tagRTUListData : public _tagDLListData
{
	long	ecid;			// ���� id
	long	equipid;		// ���� id
	long	type;			// rtu Ÿ��
	long	status;			// ����/���� ����
	long	comm;			// ���Ÿ��
	long	protocol;		// ��������
	long	point;			// ����/���� point id
	long	dmcid;			// dmcid
	long	commdmcid;		// commdmc

	long	init;			// �ʱⰪ

	TCHAR	szStatus[15][RTU_BUFF];			// Ŀ��� ����
	TCHAR	szcomm[MAX_STRING];
	TCHAR	szprotocol[MAX_STRING];
	TCHAR	szecname[MAX_STRING];
	TCHAR	szrtuname[MAX_STRING];
	TCHAR	sztype[MAX_STRING];

}RTULISTDATA, *PRTULISTDATA;

typedef struct _tagStatusListData : public _tagDLListData
{
	long	ecid;				// ���� id
	long	equipid;			// ���� id
	long	type;				// rtu Ÿ��
	long	openpoint;			// ����/���� ����Ʈ
	long	remotepoint;		// ����/���� ����Ʈ
	long	gaspoint;			// �����Է� ����Ʈ
	long	lockpoint;			// ��ü��� ����Ʈ
	long	vaspoint;			// �ܼ���� ����Ʈ
	long	equpoint;			// �����ġ ����Ʈ
	long	engpoint;			// �����ҷ� ����Ʈ
	long	shopoint;			// ������ ����Ʈ
	long	powpoint;			// �ܺ����� ����Ʈ
	long	twdpoint;			// �ڱ����� ����Ʈ

	short int opval;
	short int reval;
	short int gaval;
	short int loval;
	short int vaval;
	short int eqval;
	short int enval;
	short int shval;
	short int poval;
	short int twval;

	unsigned int	color[RTU_BUFF];			//color

	TCHAR	szopestatus[15][RTU_BUFF];			// Ŀ��� ����
	TCHAR	szremstatus[15][RTU_BUFF];			// Ŀ��� ����
	TCHAR	szgasstatus[15][RTU_BUFF];			// Ŀ��� ����
	TCHAR	szlocstatus[15][RTU_BUFF];			// Ŀ��� ����
	TCHAR	szvasstatus[15][RTU_BUFF];			// Ŀ��� ����
	TCHAR	szequstatus[15][RTU_BUFF];			// Ŀ��� ����
	TCHAR	szengstatus[15][RTU_BUFF];			// Ŀ��� ����
	TCHAR	szhosstatus[15][RTU_BUFF];			// Ŀ��� ����
	TCHAR	szpowstatus[15][RTU_BUFF];			// Ŀ��� ����
	TCHAR	sztwdstatus[15][RTU_BUFF];			// Ŀ��� ����

	TCHAR	szecname[MAX_STRING];
	TCHAR	sztype[MAX_STRING];

}STATUSLISTDATA, *PSTATUSLISTDATA;

typedef struct SORTPARAM{
	int sortColumn;
	bool sortrDirect;
	void* pList;

}SORTPARAM, *PSORTPARAM;

typedef struct _tagSEARCHTIME
{
	time_t	start;
	time_t	end;
	time_t	cur;
	int		counter;
	long	dl;

}SEARCHTIME, *PSEARCHTIME;

//typedef struct _tagVIEWEVENTDATA
//{
//	TCHAR		eventid[24];
//	TCHAR		date[20];
//	int			rtutime;
//	int			rtumics;
//	int			svrtime;
//	int			svrmics;
//	int			station;
//	TCHAR		stationname[32];
//	int			dl;
//	TCHAR		dlname[32];
//	int			eqid;
//	TCHAR		eqname[64];
//	int			rtuid;
//	int			rtutype;
//	int			ptid;
//	TCHAR		ptname[64];
//	double		val;
//	int			tlq;
//	int			cate;
//	int			cla;
//	int			priorite;
//	int			color;
//	int			audio;
//	int			area;
//	TCHAR		desc[128];
//
//	bool		read;
//
//}VIEWEVENTDATA, *PVIEWEVENTDATA;

typedef struct _tagEQUIPHIDATA
{
	long		pid;
	int			value;

}EQUIPHIDATA, *PEQUIPHIDATA;

typedef struct _tagEVENTLISTDATA
{
	TCHAR		eventid[24];
	TCHAR		desc[128];
	TCHAR		eqname[64];
	TCHAR		dlname[32];
	TCHAR		stationname[32];
	TCHAR		ptname[32];

	int			svrtime;
	int			svrmics;

}EVENTLISTDATA, *PEVENTLISTDATA;

//-----------------------------------------------------------------------
// Summary:
//    �ܼ��� TLQ���� ������
// members:
//-----------------------------------------------------------------------
typedef struct _tagTLQINFODATA
{
	long		grid;
	long		stid;
	long		dlid;
	long		ecqid;
	long		ptid;
	int			pttype;

	long		tlq;

	int			state;
	bool		psowner;

	TCHAR		szgrname[MAX_STRING];
	TCHAR		szstname[MAX_STRING];
	TCHAR		szceqname[MAX_STRING];

}TLQINFODATA, *PTLQINFODATA, *LPTLQINFODATA;

//-----------------------------------------------------------------------
// Summary:
//    �ܼ��� TLQ���� 
// members:
//-----------------------------------------------------------------------
typedef struct _tagALLTLQINFO
{
	long		grid;
	long		stid;
	long		dlid;

	TCHAR		grname[MAX_STRING];
	TCHAR		stname[MAX_STRING];
	TCHAR		dlname[MAX_STRING];

}ALLTLQINFO, *PALLTLQINFO, *LPALLTLQINFO;

// ------------------------------------- new ui -----------------------------------------

//-----------------------------------------------------------------------
// Summary:
//    ���뵵, �˶�����͸� �˶�����
// members:
//-----------------------------------------------------------------------
typedef struct _tagVIEWSETUPALARMDATA
{
	bool		checked;
	long		id;
	TCHAR		szname[MAX_STRING];

}VIEWSETUPALARMDATA, *PVIEWSETUPALARMDATA;

//typedef struct _tagASYNCDATA
//{
//	unsigned int pid;
//	unsigned int value;
//	unsigned int tlq;
//	unsigned int ctrlVal;
//	unsigned char	hmiName[32];
//	unsigned char	userName[32];
//
//}ASYNCDATA, *PASYNCDATA;

//enum HMI_APP_CODE
//{
//	HMI_QUEUE	= 0,
//	HMI_APP_TAB1,
//	HMI_APP_TAB2,
//	HMI_APP_TAB3,
//	HMI_APP_TAB4,
//	HMI_APP_TAB5,
//	HMI_APP_TAB6,
//	HMI_APP_TAB7,
//	HMI_APP_COUNT,
//};

typedef struct _tagMWPOINTINFO
{
	int			ceqid;
	int			pointType;
	int			pointid;
	int			rtumapid;
	int			position;
	int			cricuitno;
	int			MeasureTypeID;
	TCHAR		szName[RDB_NAME40_SZ];
	TCHAR		upcName[RDB_NAME40_SZ];
	TCHAR		upcTlq[RDB_NAME40_SZ];
	TCHAR		upcTime[RDB_NAME40_SZ];

} MWPOINTINFO, *PMWPOINTINFO;

typedef struct _tagTIESWICH
{
	int			nCEQID;
	int			nPSRFK;
	int			nInDL;
	int			nOutDL;
	TCHAR		szname[MAX_STRING];
	TCHAR		szInDL[MAX_STRING];
	TCHAR		szOutDL[MAX_STRING];
} TIESWITCH, *PTIESWITCH;