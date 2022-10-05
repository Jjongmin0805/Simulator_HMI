#define RTU_BUFF		32
#define PDB_SZ_NAME		64
#define COLOR_BUFF		10
#define	MAX_STRING		(64)
#define	POLLING_TIME	10					//서비스 폴링 주기
#define ALARM_POLLING_TIME			50
#define ASYNC_POLLING_TIME			500
#define	MAX_ALARM_QUEUE_SIZE		5000
#define ASYNC_FAIL_POLLING_TIME		3000

/////임시 컬러 코드
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


//TLQ 주소
#define NORMAL						0x00000000
#define TLQ_CI							0x00000001	//!< 제어 금지 설정 태그
#define	TLQ_SI							0x00000002	//!< 데이터 취득 금지 태그
#define TLQ_AI							0x00000004	//!< 알람 금지 태그
#define TLQ_EI							0x00000008	//!< 이벤트 금지 태그
#define TLQ_CS							0x00000010	//!< 공사중/점검중 태그
												  
#define TLQ_MH							0x00000020  //!< 최고 상한치 태그
#define TLQ_ML							0x00000040	//!< 최저 하한치 태그
#define TLQ_HL							0x00000080  //!< 상한치 태그
#define TLQ_LL							0x00000100  //!< 하한치 태그
												   
#define TLQ_CP							0x00000200  //!< 제어 진행중
#define TLQ_PS							0x00000400  //!< 포인트 선택중
#define TLQ_MU							0x00000800  //!< 공사용 개폐기수동 입력
#define TLQ_NU							0x00001000  //!< 업데이트 불량
#define TLQ_ON							0x00002000  //!< 비정상 상태
#define TLQ_OFF							0x00004000  //!< 포인트 Offline

//TLQ 주소
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



// 통신 TPCODE 상수
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
//     계통운영 및 단선도 리모트 유닛
// members:
//     gID        - 상위 id
//     sID        - 하위 id
//     fDL        - D/L 체크
//-----------------------------------------------------------------------
typedef struct _tagClassViewItem
{
	long	gID;		// 부모
	long	sID;		// 자식
	bool	fDL;		// D/L 유무
	bool	fPW;		// 변전소 유무

	TCHAR	szName[MAX_STRING];
} CLASSVIEWITEM, *PCLASSVIEWITM;


//-----------------------------------------------------------------------
// Summary:
//     계통운영 및 단선도 리모트 유닛
// members:
//     item        - 클래스 뷰아이템
//     file        - 단선도 파일명
//-----------------------------------------------------------------------
typedef struct _tagBLDDATA
{
	CLASSVIEWITEM	item;				// 뷰 아이템
	TCHAR			file[MAX_STRING];	// 파일 명
	UINT			itype;				// 타입(변전소내 단선도, 단선도)

}BDLDATA, *PBDLDATA;

//-----------------------------------------------------------------------
// Summary:
//     단선도 Open List Type
// members:
//-----------------------------------------------------------------------
typedef struct _tagBLDOPENDATA
{
	UINT			itype;				// 타입(변전소내 단선도, 단선도)
	long			dlid;				// D/L id
	double			textSize;			//텍스트 사이즈
	double			zoomLevel;			//줌 레벨		1.0
	double			maxZoom;			//최대 줌 레벨	20     최대 1 - 100
	double			minZoom;			//최소 줌 레벨   0.1    최소 0.1 - 1
	double			zoomStep;			//줌 간격		1 - 10
	double			startX;				//시작점 X좌표   중심점
	double			startY;				//시작점 Y좌표	중심점
	bool			fiMoving;			//FI 발생 이동	false
	unsigned int	layerse;			//!< 레이어 옵션 처리	 PDB_P | PDB_Q | PDB_VA | PDB_VR
	unsigned int	layerpf;			//!< 레이어 옵션 처리	 PDB_P | PDB_Q | PDB_VA | PDB_VR
	unsigned int	popup;				//!< 개폐기 옵션 처리  PDB_P | PDB_Q | PDB_VA | PDB_VR
	unsigned int	layer;				//!< 레이어 옵션 처리  SECTION_MEASURE
	bool			popup_toggle;		//!< 개폐기 ACM SE, PF 옵션 처리 false;
	bool			line_toggle;		//!< 선로 ACM SE,PF, 옵션 처리	false;
	bool			fFlow;				//조류방향	false;
	bool			fMemo;				//메모보기	false;

}BLDOPENDATA, *PBLDOPENDATA;

//-----------------------------------------------------------------------
// Summary:
//     설비 타입
// members:
//-----------------------------------------------------------------------
enum CONDUCTINGEQUIPTYPE
{
	CONDUCTING = 1,				// 단일
	COMPOSITE,					// 다중회로
	UNDERGROUNDTRNAS,			// 지중변압기
	SVR,						//SVR
	DLINE,						//DTS
	MSUBSTATION,					//변전소
	SUBGEO,						
	GEO,
	POWER,
	STS,						//수배전반
	SHUNT,						//Shunt Capacitor
};

//-----------------------------------------------------------------------
// Summary:
//     distribute transformer 타입
// members:
//-----------------------------------------------------------------------
enum DISTRIBUTETRANSFORMERTYPE
{
	DSVR = 1,				// SVR
	DUNDERG,				// 지중
};

//-----------------------------------------------------------------------
// Summary:
//     리모트유닛 타입
// members:
//-----------------------------------------------------------------------
enum REMOTEUNITTYPE
{
	MENUAL = 1,					// 수동
	FRTU,						// 자동
	FIED						// 자동
};

//-----------------------------------------------------------------------
// Summary:
//     설비 타입
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
//     어플 통신용 파라메터
// members:
//-----------------------------------------------------------------------
enum 
{
	DIDO_OPERATOR = 1,			// 설비상세정보
	AO_OPERATOR,				// 설비파라메터정보
	AI_OPERATOR,				// 설비계측
	CO_OPERATOR,				// 통합감시
	WA_OPERATOR,				// 고조파
	BI_OPERATOR,				// BI'
	BO_OPERATOR					// BO
};

//-----------------------------------------------------------------------
// Summary:
//     다중회로 내 설비정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagEXTRADATA
{
	TCHAR name[RTU_BUFF];					// 기기 회로이름
	TCHAR psr[RTU_BUFF];					// 설비 psr명

	long equipid;							// 기기 id
	long id;								// 가상 개폐기 id
	long psrtype;							// psr

} EXTRADATA, *PEXTRADATA;


#define MAX_EQUIP_IN_CONTINER		6		// 최대 기기갯수
//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 정보
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
	UINT	    sw_type;                           	//  단말/상시연계 상태 표시      
	long		rtu_type;                          	//  Equipment RTU Type(1:NormalEquipment,2:MTR, 3:SVR, 4:Transformer 가공, 5:Transformer 지중, etc)    
	CHAR		dev_no[RTU_BUFF];					//  Equipment Device Number        
	long		dtr_fk;                          	//  distributionTransformer ID(Transformer 지중)        
	long		ptr_fk;                          	//  PowerTransformer ID(변전 설비-Busbarsection, Breaker, Disconnect, etc)        
	long		link_cb_fk;                         //  Link Breaker ID(Disconnect)        
	long		link_bbs_fk;                        //  Link BusBarSection ID(Disconnect)
	float		base_voltage;						//  기준 전압
	UINT		phases;								//  상연결정보(A,B,C,N)
	UINT		busbar_order;                       //  Busbarsection Order(1차측,2차측)	 
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
//     리모트 유닛 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagREMOTEUNIT
{
	long powerid;					// 변전소 id
	long dlid;						// D/L id
	
	long remoteid;					// RTU id
	long psrid;						// PSR id
	long dmcid;						// DMC id

	long linecnt;					// 회선 갯수
	long csid;						// composite id
	int map;						// rtu map
	long rtype;						// 리모트 유닛타입(수동, FRTU, FIED)

	CONDUCTINGEQUIPTYPE type;		// 장비종류 
	EXTRADATA	data[MAX_EQUIP_IN_CONTINER];				// 다중회로 정보

	TCHAR	name[RTU_BUFF];			// 설비명
	TCHAR	status[RTU_BUFF];		// 상태
	TCHAR	method[RTU_BUFF];		// 방식(사용안함)
	TCHAR	station[RTU_BUFF];		// 변전소명
	TCHAR	dl[RTU_BUFF];			// D/L명
	TCHAR	proto[RTU_BUFF];		// 프로토콜
	TCHAR	psrname[RTU_BUFF];		// psr

	CONDUCT pequip; // DTS 연계를 위한 EQUIPMENT 연계

} REMOTEUNIT, *PREMOTEUNIT;


//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 정보 확장
// members:
//-----------------------------------------------------------------------
typedef struct _tagREMOTEUNITEX : _tagREMOTEUNIT
{
	UINT	type;

} REMOTEUNITEX, *PREMOTEUNITEX;


//-----------------------------------------------------------------------
// Summary:
//     분산전원 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagDRUNIT
{
	long drid;								// 분산전원 id

	TCHAR	name[MAX_STRING];				// 발전종류
	TCHAR	turbin[MAX_STRING];				// 발전용량
	TCHAR	curtrubin[MAX_STRING];			// 현재발전량
	TCHAR	volt[MAX_STRING];				// 정격전압
	TCHAR	arm[MAX_STRING];				// 정격전류
	TCHAR	prot[MAX_STRING];				// 프로토콜
	TCHAR	comm[MAX_STRING];				// 통신타입
	TCHAR	p[MAX_STRING];					// 유효전력
	TCHAR	q[MAX_STRING];					// 무효전력
	TCHAR	pf[MAX_STRING];					// 역률
	TCHAR	var[MAX_STRING];				// 유효 단위
	TCHAR	kvar[MAX_STRING];				// 무효 단위

}DRUNIT, *PDRUNIT;


//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 정보(계통도, 단선도)
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITINFO
{
	TCHAR	station[MAX_STRING];		// 변전소명
	TCHAR	name[64];					// 설비명
	TCHAR	psrName[MAX_STRING];		// 설비종류명
	TCHAR	MeshNo[MAX_STRING];			// 전산화번호
	TCHAR	CeqID[64];					// CEQID
	TCHAR	dl[64];						// D/L 명
	//TCHAR	psr[64];					// 설비타입
	TCHAR	type[MAX_STRING];			// 수동/ 자동
	TCHAR	istate[MAX_STRING];			// 상태값
	TCHAR	custate[MAX_STRING];		// 설치값
	TCHAR	create[MAX_STRING];			// 제작사
	TCHAR	day[MAX_STRING];			// 제조일자
	TCHAR	proto[MAX_STRING];			// 프로토콜
	TCHAR	commType[MAX_STRING];		// 통신방식
	TCHAR	mAddress[MAX_STRING];		// Master Addr
	TCHAR	sAddress[MAX_STRING];		// Slave Addr
	TCHAR	Masterfep[MAX_STRING];		// Master dnp Info
	TCHAR	DnpAddress[MAX_STRING];		// 현장기기 DNP 주소
	TCHAR	makeNo[MAX_STRING];			// 제작 번호
	TCHAR	makeDate[MAX_STRING];		// 제작 날짜
	TCHAR	version[MAX_STRING];		// FRTU 버전
	TCHAR	makeNo2[MAX_STRING];		// 제작 번호2
	TCHAR	man[MAX_STRING];			// 설치 감독

}UNITINFO, *PUNITINFO;

//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 제어 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITCTRLINFO
{
	long	psr;						// psr type
	long	equipid;					// 설비 id
	long	pointid;					// 제어 포인트
	long	eqtype;						// 설비 타입

	TCHAR	name[MAX_STRING];			// 설비명
	TCHAR	psrname[MAX_STRING];		// psr 명
	TCHAR	point[MAX_STRING];			// 포인트 명
}UNITCTRLINFO, *PUNITCTRLINFO;

//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 정보(계통운영)
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITINFOVIEW
{
	TCHAR		szid[RTU_BUFF];					// ID
	TCHAR		szname[RTU_BUFF];				// 이름
	TCHAR		szsubgeo[RTU_BUFF];				// 사업소
	TCHAR		szline[RTU_BUFF];				// 선로
	TCHAR		szfinancier[RTU_BUFF];			// 전주
	TCHAR		szloca[RTU_BUFF];				// 전주위치
	TCHAR		szrtutype[RTU_BUFF];			// 개폐기종류
	TCHAR		szswtype[RTU_BUFF];				// 초기상태
	TCHAR		szcomm[RTU_BUFF];				// 통신종류
} UNITINFOVIEW, *PUNITINFOVIEW;
//-----------------------------------------------------------------------
// Summary:
//    포인트 값 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagPOINTALIASDATA
{
	long	index;					// 포인트 값 index
	short	value;					// 값
	TCHAR	szName[MAX_STRING];		// 값 이름
	long	color;					// color

}POINTALIASDATA, *PPOINTALIASDATA;
//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 (디지탈)제어, 상태 정보
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
	UINT			CircuitNo;						// 회로번호
	UINT			value;							// 값
	UINT			measureTypeId;					// 데이터 분류 id
	TCHAR			upc_name[RTU_BUFF];				// 미들웨어 값 요청 
	TCHAR			upc_tlq[RTU_BUFF];				// 미들웨어 TLQ 요청
	TCHAR			upc_uptime[RTU_BUFF];			// 미들웨어 시간 요청

	UINT			ccnt;							// 카운터 커멘드
	UINT			ccommand[15];					// 커멘드값
	TCHAR			szNames[15][RTU_BUFF];			// 커멘드 네임 // 일단 넣자 - valueAlias Name
	SHORT			szColor[COLOR_BUFF];			// 아이콘 색상 변경

	UINT			tlq;							// TLQ

	TCHAR			szName[RTU_BUFF];				// name
	UINT			abnormalValue;					// Abnormal 
	UINT			normalValue;					// normal 
	UINT			colorFk[RTU_BUFF];				//color
	UINT			color[RTU_BUFF];				//colorFK

} UNITDIGIINFO, *PUNITDIGIINFO;


//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 (아날로그)상태 정보
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
	float		avalue;							// 값
	float		sfactor;						// 스켈펙터

	float		aminvalue;						// 최소값
	float		amaxvalue;						// 최대값

	float		aminlimitvalue;					// 최소값
	float		amaxlimitvalue;					// 최대값

	int			lnsec_ii_br;					// acm br index
	int			cbsw_ii_fnd;					// acm cb_fnd index
	int			cbsw_ii_tnd;					// acm cb_tnd index

	int			acmdataindex;					// acm data array index

	double		sevalue;						// se value
	double		pfvalue;						// pf value

	bool		fvalue;							// se, pf 유무

	unsigned int	tlq;						// TLQ

	TCHAR		szName[RTU_BUFF];				// name
	TCHAR		szMeasure[RTU_BUFF];			// 단위

	TCHAR			upc_name[RTU_BUFF];				// 미들웨어 값 요청 
	TCHAR			upc_tlq[RTU_BUFF];				// 미들웨어 TLQ 요청
	TCHAR			upc_uptime[RTU_BUFF];			// 미들웨어 시간 요청

}UNITANALOGININFO, PUNITANALOGININFO;


//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 (아날로그)제어, 상태 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagPOINTINFODATA
{
	long		aid;
	long		tlq;

}POINTINFODATA, *PPOINTINFODATA;


//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 고조파 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITWAVEINFO
{
	TCHAR		szpath[MAX_STRING];				// 경로
	TCHAR		sztype[MAX_STRING];				// 종류
	TCHAR		sztime[MAX_STRING];				// 시각
	TCHAR		szsamp[MAX_STRING];				// 샘플링
	TCHAR		szFile[MAX_STRING];				// 파일이름

}UNITWAVEINFO, *PUNITWAVEINFO;


//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 (아날로그)제어 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITANALOGOUTINFO
{
	long		aid;							// ai, ao id
	long		apoint;							// ai, ao point
	long		apos;							// ai, ao position
	long		aline;							// ai, ao line
	float		avalue;							// 값
	float		adefault;						// 디폴트 값
	float		ascale;							// scalefator
	
	float		setvalue;						// 설정 값
	float		svrvalue;						// svr 설정값

	float		aminvalue;						// 최소값
	float		amaxvalue;						// 최대값
	float		astepvalue;						// 스텝값

	int			groupindex;						// 그룹 인덱스
	long		groupid;						// 그룹 id
	int			grouptype;						// 그룹 타입
	float		groupvalue;						// 그룹 값


	unsigned int	tlq;						// TLQ

	TCHAR		szName[RTU_BUFF];				// name
	TCHAR		szMeasure[RTU_BUFF];			// 단위

}UNITANALOGOUTINFO, PUNITANALOGOUTINFO;


//-----------------------------------------------------------------------
// Summary:
//     리모트 유닛 카운트 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagUNITACCUMULATORINFO
{
	long		cid;							// ci, co id
	long		cpoint;							// ci, co point
	long		cpos;							// ci, co position
	long		cline;							// ci, co line
	float		cvalue;							// 설정 값

	float		cminvalue;						// limit최소값
	float		cmaxvalue;						// limit최대값
	float		amaxvalue;						// max값

	float		asetvalue;						// max set값

	TCHAR		szName[RTU_BUFF];				// name
	TCHAR		szMeasure[RTU_BUFF];			// 단위

}UNITACCUMULATORINFO, PUNITACCUMULATORINFO;

#define MAX_TAG			128


//-----------------------------------------------------------------------
// Summary:
//    단선도 알람정보(사용하지 않음)
// members:
//-----------------------------------------------------------------------
typedef struct _tagBDLALARMDATA
{
	char    szEvtId[PDB_SZ_NAME];	//time-key - timestamp(16) + pointno(7)
	UINT	uiStation;				//변전소 번호
    UINT    uiDl;					//DL 번호
    UINT    uiPtType;				//Point Type
    UINT    uiPtNo;					//Point Number
    UINT    uiEqNo;					//장비 번호 
    float   fValue;					//Point의 현재 값
    UINT    uiTlq;					//Point의 Tlq 값

	bool	fAck;
	bool	fReal[MAX_TAG];			// 실시간
}BDLALARMDATA, *PBDLALARMDATA;


//-----------------------------------------------------------------------
// Summary:
//    계통도, 알람모니터링 알람정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagALARMDATA
{
	char    szEvtId[PDB_SZ_NAME];	/*time-key - timestamp(16) + pointno(7)							*/
	UINT	uiFc;					/* Function Code : 알람, 이벤트, 고장, 제어응답, 설정응답, 계측응답 */
	UINT	uiRtuTime;				/* 현장에서 제공된 RTU 시간 없으면 NULL */
	UINT	uiSvrTime;				/* 주장치 서버에서 알람/이벤트 발생한 시간 */
	UINT	uiStation;				/* 알람/이벤트가 발생한 변전소 ID */
	UINT	uiDL;					/* 알람/이벤트가 발생한 DL ID */
	UINT	uiEqNo;					/* DMS 서버에서 정의한 기기 고유 ID */
	UINT	uiMapNo;				/* 기기별 Index Map 번호 */
	UINT	uiPtType;				/* 기기별 BI, BO, AI, AO, CNT */
	UINT	uiIndexNo;				/* DNP Index MAP 에서 정의한 번호 SCADA 연계시 O */
	UINT	uiPid;					/* DMS 서버에서 정의한 제어 대상 포인트의 고유 ID 없는 경우 0 */
	FLOAT	fValue;					/* 현재 상태 및 계측값 */
	UINT	uiTlq;					/* 해당 PID의 TLQ값 */
	UINT	uiAlarmCode;			/* DMS서버에서 정의된 알람 분류 10등급 HMI별로 색상, 소리 변경 */
	TCHAR	szDesc[128];			/* 알람내용 */
	UINT	uiSeqNo;				/* 시퀀스 제어 ID - HMI 번호와 임의번호를 조합하여 제어 성공실패 판단 */
	bool	fAck;
	bool	fBlink;

	TCHAR szStation[PDB_SZ_NAME];	// 변전소 명
	TCHAR szWave[MAX_STRING];		// 알람파일
	TCHAR szDL[PDB_SZ_NAME];		// D/L명
	TCHAR szEquip[PDB_SZ_NAME];		// 설비명
	TCHAR szAlarmCode[PDB_SZ_NAME];	// 알람 코드
	TCHAR szPointName[PDB_SZ_NAME]; // 포인트 명


	//char    szEvtId[PDB_SZ_NAME]; //time-key - timestamp(16) + pointno(7)
 //   UINT	uiTime;					//이벤트 발생 시각
 //   UINT	uiStation;				//변전소 번호
 //   UINT    uiDl;					//DL 번호
 //   UINT    uiPtType;				//Point Type
 //   UINT    uiPtNo;					//Point Number
 //   UINT    uiEqNo;					//장비 번호 
 //   float   fValue;					//Point의 현재 값
 //   UINT    uiTlq;					//Point의 Tlq 값
 //   UINT	usCat;					//포인트가 속한 Alarm Category Code
 //   UINT	usPri;					//Alarm Class 우선순위
 //   UINT    byCl;					//Alarm Class 색상
 //   UINT    byVo;					//Alarm Class 소리 
 //   UINT	usAC;					//Point가 속한 AcessArea Code
 //   TCHAR   szDesc[128];			//Alarm/Event가 발생한 동작을 설명
	//bool	fAck;
	//bool	fBlink;
	//
	//UINT	uiRtuTime;				//RTU Event 발생시간 Seconds
	//UINT	uiRtuMics;				//RTU Event 발생시간 Micro Seconds
	//UINT	uiSVRMics;				//SERVER Event 생성시간 Micro Seconds
	//UINT	uiRtuid;				//RTU Id
	//UINT	uiCls;					//Alrm Class Id
	//UINT	uiEqType;				//

	//COLORREF	cfColor;

	//TCHAR szStation[PDB_SZ_NAME];	// 변전소 명
	//TCHAR szWave[MAX_STRING];		// 알람파일
	//TCHAR szCate[PDB_SZ_NAME];		// 카테고리명
	//TCHAR szDL[PDB_SZ_NAME];		// D/L명
	//TCHAR szUnit[PDB_SZ_NAME];		// 설비명
	//TCHAR szPri[PDB_SZ_NAME];		// 알람 레벨
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
//    알람 필터링 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagALARMFILTTER
{
	BOOL			fSET;				// 필터링 체크
	BOOL			fcontinue;			// 실시간 알람 체크

	bool			ftime;				// 필터링 시간 체크
	UINT			iStartTime;			// 필터링 시작시간
	UINT			iEndTime;			// 필터링 끝

	bool			iStation[MAX_TAG];	// 변전소 필터링
	bool			iLevel[MAX_TAG];	// 알람 레벨 필터링
	bool			iCate[MAX_TAG];		// 카테고리 필터링
	bool			iDL[MAX_TAG];		// D/L 필터링

	UINT			iAck;				// ACK 체크(0 : Ack, 1 : unack, 2 : 모두 체크)
	UINT			iAlarm;				// 알람필터 ( 0 : 알람, 1, 이벤트,  2: 모두 체크)

// add New UI -----------------------
	time_t			start;
	time_t			end;
	TCHAR			name[MAX_STRING];
	int				index;

}ALARMFILTTER, *PALARMFILTTER;


//-----------------------------------------------------------------------
// Summary:
//    설비검색 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagSEARCHDATA
{
	long equipid;						// 설비 id
	long psrid;							// psr id

	TCHAR geo[MAX_STRING];				// 지사
	TCHAR sub[MAX_STRING];				// 지점
	TCHAR sta[MAX_STRING];				// 변전소
	TCHAR dl[MAX_STRING];				// D/L
	TCHAR eq[MAX_STRING];				// 설비
	TCHAR psr[MAX_STRING];				// psr

}SEARCHDATA, *PSEARCHDATA;


//-----------------------------------------------------------------------
// Summary:
//    고압수용가 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagENERGYCON
{
	//TCHAR	count[MAX_STRING];			// 갯수
	//TCHAR	dlname[MAX_STRING];			// 소속 DL
	//TCHAR	id[MAX_STRING];				// 수용가 번호
	//TCHAR	name[MAX_STRING];			// 수용가 이름
	//TCHAR	power[MAX_STRING];			// 소비전력
	//TCHAR	pri[MAX_STRING];			// 중요도
	//TCHAR	sms[MAX_STRING];			// sms
	//TCHAR	tel[MAX_STRING];			// 전화

	TCHAR	 dlname[MAX_STRING];			// 소속 DL
	TCHAR    Name[MAX_STRING];          /*이름                                         */
	TCHAR	 customerCount[MAX_STRING]; /*고객수(1)                                    */
	TCHAR	 pfixed[MAX_STRING];        /*계약전력P(100KW)                             */
	TCHAR	 qfixed[MAX_STRING];        /*계약전력Q(100Kvar)                           */
	TCHAR    Tel[MAX_STRING];           /*전화번호(02-)                                */
	TCHAR    HP[MAX_STRING];           /*핸드폰번호(010-)                             */
	TCHAR    Customer_key[MAX_STRING];  /*Custermer Key(80-)                           */
	TCHAR    Priority[MAX_STRING];      /*중요도(1)                                    */
	TCHAR    SmsUse[MAX_STRING];        /*SMS(0: 사용안함, 1: 사용)                    */
}ENERGYCON, *PENERGYCON;


//-----------------------------------------------------------------------
// Summary:
//    구간 정보(선로)
// members:
//-----------------------------------------------------------------------
typedef struct _tagLINESEC
{
	TCHAR	substation[MAX_STRING];		// 변전소
	TCHAR	dl[MAX_STRING];				// DL
	TCHAR	name[MAX_STRING];			// 선로명
	TCHAR	front[MAX_STRING];			// 전단
	TCHAR	back[MAX_STRING];			// 후단
	TCHAR	spec1[MAX_STRING];			//
	TCHAR	spec2[MAX_STRING];
	TCHAR	spec3[MAX_STRING];
	TCHAR	spec4[MAX_STRING];
	TCHAR	line[MAX_STRING];
	TCHAR	size[MAX_STRING];			// 크기
	TCHAR	sang[MAX_STRING];			// 상, 정보
	TCHAR	ac[MAX_STRING];				// ac / dc

}LINESEC, *PLINESEC;

//-----------------------------------------------------------------------
// Summary:
//    메뉴얼 오버라이트 정보(base struct)
// members:
//-----------------------------------------------------------------------
typedef struct _tagMENUALDATA
{
	long			id;						// 포인트 id
	TCHAR			szName[MAX_STRING];		// 포인트 명
	UINT			uiTlq;					// Point의 Tlq 값
	bool			foverride;				// 오버라이트 체크

}MENUALDATA, *PMENUALDATA;

//-----------------------------------------------------------------------
// Summary:
//    메뉴얼 오버라이트 정보(아날로그)
// members:
//-----------------------------------------------------------------------
typedef struct _tagAIMENUALDATA : _tagMENUALDATA
{
	float			curvalue;				// 현재 값
	float			setvalue;				// 설정 값
	float			maxvalue;				// 최대	값
	float			minvalue;				// 최소 값

}AIMENUALDATA, *PAIMENUALDATA;


//-----------------------------------------------------------------------
// Summary:
//    메뉴얼 오버라이트 정보(디지털)
// members:
//-----------------------------------------------------------------------
typedef struct _tagBIMENUALDATA : _tagMENUALDATA
{
	int				cnt;					// alias 카운트
	short			curvalue;				// 현재 상태값
	short			setvalue;				// 변경값
	POINTALIASDATA* paliasdata;				// 데이타

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
	//    상태값으로 인덱스 참조
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
	//    상태값으로 상태값 이름 참조
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
//    메뉴얼 오버라이트 정보(base struct)
// members:
//-----------------------------------------------------------------------
typedef struct _tagOVERRIDEDATA
{
	TCHAR szstation[MAX_STRING];		// 변전소
	TCHAR szdl[MAX_STRING];				// D/L
	TCHAR szunit[MAX_STRING];			// 설비명
	TCHAR szname[MAX_STRING];			// 포인트 명
	long point;							// 포인트 id
	UINT type;							// 포인트 타입
	long tlq;							// tlq 값

}OVERRIDEDATA, *POVERRIDEDATA;

//-----------------------------------------------------------------------
// Summary:
//    메뉴얼 오버라이트 정보(아날로그)
// members:
//-----------------------------------------------------------------------
typedef struct _tagANALOVERRIDEDATA : _tagOVERRIDEDATA
{
	float maxlimit;						// 최대값
	float minlimit;						// 최소값
	float value;						// 실시간 값

}ANALOVERRIDEDATA, *PANALOVERRIDEDATA;

//-----------------------------------------------------------------------
// Summary:
//    메뉴얼 오버라이트 정보(디지털)
// members:
//-----------------------------------------------------------------------
typedef struct _tagDIGIOVERRIDEDATA : _tagOVERRIDEDATA
{
	short value;						// 실시간 값

}DIGIOVERRIDEDATA, *PDIGIOVERRIDEDATA;


//-----------------------------------------------------------------------
// Summary:
//    메뉴얼 오버라이트 정보(디지털)
// members:
//-----------------------------------------------------------------------
typedef struct _tagUPDATEBDLVIEWER
{
	bool fdlopen;					// 단선도 D/L 로드 체크
	bool fficheck;					// fi 발생 체크

	bool fupdate;					// 단선도 업데잇 상태 체크
	bool fview;						// 단선도 로드 체크

	bool isactive;					// 단선도 활성화 체크

} UPDATEBDLVIEWER, *PUPDATEBDLVIEWER;


//-----------------------------------------------------------------------
// Summary:
//    메뉴얼 오버라이트 정보(디지털)
// members:
//-----------------------------------------------------------------------
typedef struct _tagBDLUPDATEPOINT
{
	long	pointid;
	bool	data;

}BDLUPDATEPOINT, *PBDLUPDATEPOINT;


//-----------------------------------------------------------------------
// Summary:
//    단선도 포인트 정보
// members:
//-----------------------------------------------------------------------
typedef struct _taBDLVIEWDATA
{
	long	psrid;			 // psr id
	long	equipid;		 // 설비 id
	long	remoteid;		 // 리모트 id
	int		in_dl;			 // 내선
	int		out_dl;			 // 외선
	bool	switchType;		 // 스위치 타입
	bool	fauto;			 // 자동 / 수동

	BDLUPDATEPOINT	data[29]; // fi 체크 대상 포인트

} BDLVIEWDATA, *PBDLVIEWDATA;


//-----------------------------------------------------------------------
// Summary:
//    계통운영 고조파정보(분산전원)
// members:
//-----------------------------------------------------------------------
typedef struct _tagHISMDATA
{
	long	point;						// 포인트 id
	int		index;						// 포인트 index
	float	data;						// 값

	TCHAR	name[MAX_STRING];			// 포인트 이름

}HISMDATA, *PHISMDATA;


//-----------------------------------------------------------------------
// Summary:
//    메모
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
//    메세지
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
//    변압기 정보
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
	long	pid;			// 변압기 id
	long	id;				// 변압기weding id
	long	station;		// 변전소 id
	long	dl;				// D/L id
	long	equip;			// 설비 id
	long	type;			// 종류
	long	dmcid;			// DMC point id
	TCHAR	szsubstation[MAX_STRING];	// 변전소
	TCHAR	szdl[MAX_STRING];			// D/L
	TCHAR	name[MAX_STRING];			// 전주번호
	TCHAR	szmash[MAX_STRING];			// 전산화번호
	
	TRANSBIDATA		transBI[10];
	//TRANSAIDATA		transAI[122];
	short	status;

}TRANSFORMERLIST, *PTRANSFORMERLIST;

//-----------------------------------------------------------------------
// Summary:
//    변전소내 단선도 변전소 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagDLSUBSTATION
{
	long	pid;				//변전소 아이디
	int		mtrsize;			//MTR 수량
	int		bussize;			//버스 수량
	int		dlsize;				//DL 수량
	bool	fuse;				//사용 유무

	char	szsubstation[MAX_STRING];	// 변전소 명
	char	szmash[MAX_STRING];			// 변전소 번호
	
}DLSUBSTATION, *PDLSUBSTATION;

//-----------------------------------------------------------------------
// Summary:
//    변전소내 단선도 변압기 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagTRANSFORMERINFO
{
	long		pid;					//변압기 아이디
	long		twdId;					//winding 아이디
	long		ceqId;					//winding CEQID
	char		szname[MAX_STRING];		//변압기 명
	int			fieldPos;				//좌측 부터 우선 순서
	int			sstype;					//변압기 타입 1:GIS, 2:MCSG, 3:GIS + MCSG
	int			bbs_1fk;				//1차버스바 섹션 아이디
	int			bbs_2fk;				//2차버스바 섹션 아이디
	bool		checked;				//드로잉 완료
	
}TRANSFORMERINFO, *PTRANSFORMERINFO;

//-----------------------------------------------------------------------
// Summary:
//    변전소내 단선도 버스바 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagBASBARINFO
{
	int			pid;						//아이디
	char		szname[MAX_STRING];			//버스바 명
	char		szaliasName[MAX_STRING];	//버스바 번호
	int			bufNo;						//버스위치 1: 가까운 쪽, 2: 먼쪽
	bool		fservice;					//사용 여부
	
}BASBARINFO, *PBASBARINFO;

//-----------------------------------------------------------------------
// Summary:
//    변전소내 단선도 MTR/CB 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagMTRINFO
{
	int			pid;				//브레이커 아이디
	int			pceqId;				//Conduct Equipment ID
	int			psr;				//Psr
	char		szname[MAX_STRING];	//차단기 이름
	int			ptrFk;				//변압기 아이디
	char		deviceNo[MAX_STRING];			//장치 번호
	bool		service;			//사용 여부

	bool		IsOpen;				//열림/닫힘
	double		current[3];			//ABC 전류
	bool		s43rc;				//43rc 상태
	bool		ocrHan;				//한시
	bool		ocrSun;				//순시
	bool		ocgrHan;			//한시
	bool		ocgrSun;			//순시

	int			ds1;				//1차 차단기 아이디
	int			ds2;				//2차 차단기 아이디
	
}MTRINFO, *PMTRINFO;

//-----------------------------------------------------------------------
// Summary:
//    변전소내 단선도 단로기 정보
// members:
//-----------------------------------------------------------------------
typedef struct _tagDISCONNECTOR
{
	int			pid;					//차단기 아이디
	char		szname[MAX_STRING];		//차단기 명
	int			brFk;					//브레이커 아이디
	int			bbsFk;					//버스바 아이디
	char		deviceNo[MAX_STRING];	//장치 아이디
	
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
//   DTS 정보
// members:
//-----------------------------------------------------------------------
//typedef struct _tagDTSINFO
//{
//	long	SectionId;			// 구간 선로 id
//	
//	//TCHAR	szcontent[MAX_STRING];	// 목록
//	//TCHAR	szunit[MAX_STRING];		// 단위
//	//TCHAR	szvalue[MAX_STRING];	// 값
//
//	//float	DTS_Max_Temp[3];	// DTS 최고온도
//	//float	DTS_Max_Dist[3];	// 거리
//	//float	CON_Max_Temp[3];	// 도체 최고온도
//	//float	CON_Max_Dist[3];	// 도체 최고 거리
//	//float	CCR[3];				// 상시 허용 전류
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
	long   SectionId;			// 구간 선로 id
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
	long   SectionId;			// 구간 선로 id
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
	long	pointId;			// 구간 선로 id

	TCHAR  szname[MAX_STRING];
	float	data;
	//bool	dataD[5];	//0 : 79RY 1:OCR 한시 2:OCR순시 3:OCGR 한시 4;OCGR순시
	//float	dataA[6];	//0 : 전압  1: 전류  2: 유효전력 3: 무효전력  4 : 온도 5 : OLTC 

}MTRDATA, *PMTRDATA;

//!< FI LIST 데이터 Structure
typedef struct _fiListData
{
//	char	evtId[32];				//알람 이벤트 아이디
	long	station;
	long	dl;
    UINT	uiTime;					// 이벤트 발생 시각
	long	Id;						// 아이디
	long	outpoint;				// bo point
	short	outvalue;				// bo point value
	long    psr;					// PSR
	UINT    type;					// 0 : 일시FI, 1 : 순간 FI 2 : 종류 모름 = FI
	double  current[4];				// 고장전류 ABCN
	bool	status[4];				// 고장상 ABCN
	TCHAR	szsubgeo[MAX_STRING];	// 지사
	TCHAR	szstation[MAX_STRING];	// 변전소
	TCHAR	szdl[MAX_STRING];		// D/L
	TCHAR	szunit[MAX_STRING];		// 전주번호
	TCHAR	szPoint[MAX_STRING];	// 포인트 명
	long	point;					// 포인트 id - 포인트 인덱스
	long	remoteid;				// 리모트 id
	bool	fisfi;
	bool	psowner;				// ps사용자
	int		state;					// 진행상태

} FILISTDATA, *PFILISTDATA;

typedef struct _tagFdSecList
{
	long	pid;			// 순번
	long	id;				// FD 발생 선로 id
	long	psr;			// Fd 발생 선로 psr
	long	dl;				// D/L id

	TCHAR	szdl[MAX_STRING];			// D/L
	TCHAR	name[MAX_STRING];			// 전주번호
	short	status;			//상태값

}FDSECLIST, *PFDSECLIST;

typedef struct _tagSrResultList
{
	long	count;
	long	iSeq;			// 복구 순서
	long	id;				// 개폐기 CEQID
	long	dl;				// D/L id
	long	swtype;
	TCHAR	szHowTo[MAX_STRING];		//복구방안
	TCHAR	szdl[MAX_STRING];			// D/L
	TCHAR	name[MAX_STRING];			// 전주번호
	TCHAR	sname[MAX_STRING];
	TCHAR	sznames[15][MAX_STRING];		// 전주번호	
	short	status;			//상태값
	short	afterStatus;	//조작후 상태값

}SRRESULTLIST, *PSRRESULTLIST;

typedef struct _tagDynSrList
{
	char	candidate_scheme_nm[32];				/* 정전복구 후보의 정전복구 Scheme 명			*/
	int		candidate_scheme_type;					/* 정전복구 후보의 정전복구 Scheme 타입			*/
	int		candidate_swnum;						/* 정전복구 후보의 스위칭 횟수					*/
	float	candidate_max_ld;						/* 부하 절체시 최대 부하량						*/
	int		candidate_fisibility;					/* 정전복구 가능여부 표시						*/
	int		candidate_rank;							/* 정전복구 후보 평가 우선순위					*/
	float	candidate_total_index;					/* 정전복구 후보 평가 점수						*/
	float	candidate_swn_index;					/* 스위칭 횟수 평가 점수						*/
	float	candidate_maxld_index;					/* 최대 부하 평가 점수							*/
	int		candidate_sw_sequence[5];				/* 스위칭 조작 시퀀스							*/
	int		candidate_sw_type[5];					/* 조작 개폐기의 cbsw 타입 (CBSW: 1, TISW:2)	*/
	int		candidate_bf[3];						/* 부하절체 선로								*/
	float	candidate_lt[3];						/* 선로 별 부하절체 량							*/
	float	candidate_bf_ld[3];						/* 부하절체 후 선로 부하량						*/
	float	candidate_bf_magin[3];					/* 부하절체 후 선로 공급여유용량				*/
	float	candidate_bf_max_vdrop[3];				/* 부하절체 후 선로 최대 전압강하				*/
	float	candidate_bf_max_amp[3];				/* 부하절체 후 선로 최대 전류					*/

	int		reserved1;								/* 여유분1										*/
	int		reserved2;								/* 여유분2										*/
	int		reserved3;								/* 여유분3										*/
	int		reserved4;								/* 여유분4										*/

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


#define WM_REQ_FIED		(WM_USER + 100)			// FIED 상태요청
#define WM_REQ_EXIT		(WM_USER + 101)			// NMS 종료 요청

#define WM_RES_STATUS	(WM_USER + 100)			// NMS 상태응답
	#define RES_STATUS_NORMAL			0x0			// 상태 노말
	#define RES_STATUS_MASTER_ERROR		0x1			// 마스터 오류
	#define RES_STATUS_SLAVE_ERROR		0x2			// 슬레이브 오류
	#define RES_STATUS_FIED_ERROR		0x3			// FIED 링크오류
	#define RES_STATUS_UNKNOW			0x4			// 알수 없음
	#define RES_STATUS_TIMEOUT			0x5			// 응답 타임아웃
	#define RES_STATUS_SERVER			0x6			// 서버 down
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
//    단선도 고장처리 프로그램 리스트
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
//    DMC 트리컨트롤 (변전소 별)
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
//    DMC 트리컨트롤 (통신 별)
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
//    DMC 리스트컨트롤 
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
	long	ecid;			// 설비 id
	long	equipid;		// 설비 id
	long	type;			// rtu 타입
	long	status;			// 열림/닫힘 상태
	long	comm;			// 통신타입
	long	protocol;		// 프로토콜
	long	point;			// 열림/닫힘 point id
	long	dmcid;			// dmcid
	long	commdmcid;		// commdmc

	long	init;			// 초기값

	TCHAR	szStatus[15][RTU_BUFF];			// 커멘드 네임
	TCHAR	szcomm[MAX_STRING];
	TCHAR	szprotocol[MAX_STRING];
	TCHAR	szecname[MAX_STRING];
	TCHAR	szrtuname[MAX_STRING];
	TCHAR	sztype[MAX_STRING];

}RTULISTDATA, *PRTULISTDATA;

typedef struct _tagStatusListData : public _tagDLListData
{
	long	ecid;				// 설비 id
	long	equipid;			// 설비 id
	long	type;				// rtu 타입
	long	openpoint;			// 열림/닫힘 포인트
	long	remotepoint;		// 현장/원격 포인트
	long	gaspoint;			// 가스입력 포인트
	long	lockpoint;			// 본체잠금 포인트
	long	vaspoint;			// 단선결상 포인트
	long	equpoint;			// 상불일치 포인트
	long	engpoint;			// 충전불량 포인트
	long	shopoint;			// 과방전 포인트
	long	powpoint;			// 외부전원 포인트
	long	twdpoint;			// 자기진단 포인트

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

	TCHAR	szopestatus[15][RTU_BUFF];			// 커멘드 네임
	TCHAR	szremstatus[15][RTU_BUFF];			// 커멘드 네임
	TCHAR	szgasstatus[15][RTU_BUFF];			// 커멘드 네임
	TCHAR	szlocstatus[15][RTU_BUFF];			// 커멘드 네임
	TCHAR	szvasstatus[15][RTU_BUFF];			// 커멘드 네임
	TCHAR	szequstatus[15][RTU_BUFF];			// 커멘드 네임
	TCHAR	szengstatus[15][RTU_BUFF];			// 커멘드 네임
	TCHAR	szhosstatus[15][RTU_BUFF];			// 커멘드 네임
	TCHAR	szpowstatus[15][RTU_BUFF];			// 커멘드 네임
	TCHAR	sztwdstatus[15][RTU_BUFF];			// 커멘드 네임

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
//    단선도 TLQ제어 데이터
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
//    단선도 TLQ제어 
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
//    계통도, 알람모니터링 알람정보
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