#pragma once

#ifndef __KASIM_DEFINE__
#define __KASIM_DEFINE__


// Table : AVM_STA, Type : Online
typedef struct _AVM_STA
{
	wchar_t							avm_nm[64];					// Angle violation monitoring group�� ��Ī

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} AVM_STA;
#define								AVM_STA_SIZE						sizeof( AVM_STA )


// Table : AVM_DYN_UIN, Type : Online
typedef struct _AVM_DYN_UIN
{
	int								avm_morflag;					// AVM group�� ���� Ȱ�� ����(1: ����, 0: ���þ���)
	double							avm_lm;					// AVM group�� ������ limit
	double							avm_tol;					// AVM ���ø� ���� tolerance
	double							avm_dband;					// AVM ���ø� ���� dead band

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} AVM_DYN_UIN;
#define								AVM_DYN_UIN_SIZE						sizeof( AVM_DYN_UIN )


// Table : BOF_STA, Type : Online
typedef struct _BOF_STA
{
	wchar_t							bof_nm[64];						// ����(Branch Office) ��
	wchar_t							bof_officeid[64];				// Branch Office�� ID
	int								bof_ii_center;					// BOF�� CENTER���� Indirect index
	int								bof_si_center;					// BOF�� CENTER���� Sibling index
	int								bof_hi_dl;						// BOF���� SS���� head index
	int								bof_AREA_BASE_CODE;

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3

	int								nBOF_OFFICE_TYPE;
} BOF_STA;
#define								BOF_STA_SIZE						sizeof( BOF_STA )


// Table : BR_STA, Type : Online
typedef struct _BR_STA
{
	wchar_t							br_nm[64];					// �б⼱��
	int								br_ii_equ;					// BR���� ���� ����(LNSEC, TR)���� indirect index
	int								br_si_fnd;					// BR���� ND���� sibling index
	int								br_ii_fnd;					// BR���� ND���� indirect index
	int								br_si_tnd;					// BR���� ND���� sibling index
	int								br_ii_tnd;					// BR���� ND���� indirect index
	double							br_posr;					// ����� ����
	double							br_posx;					// ����� �����Ͻ�
	double							br_posg;					// ����� �����Ͻ�
	double							br_posb;					// ����� �����Ͻ�
	double							br_zerr;					// ����� ����
	double							br_zerx;					// ����� �����Ͻ�
	double							br_zerg;					// ����� �����Ͻ�
	double							br_zerb;					// ����� �����Ͻ�
	double							br_norlm;					// ������� �����뷮 ����ġ
	double							br_emrlm;					// ������ �����뷮 ����ġ
	int								br_si_gbr;					// BR���� GBR���� Sibling index
	int								br_ii_gbr;					// BR���� GBR���� Indirect index
	int								br_ii_dl;
	int								br_si_dl;
	int								br_ii_equty;

	wchar_t							br_ceq[64];

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} BR_STA;
#define								BR_STA_SIZE						sizeof( BR_STA )


// Table : CBSW_STA, Type : Online
typedef struct _CBSW_STA
{
	wchar_t							cbsw_nm[64];					// ���ܱ� �� ����� �� 2_node���� �� ���º����� �ִ� ������ ��Ī
	wchar_t							cbsw_ceqid[64];					// CBSW�� CEQID
	int								cbsw_type;					// ����ġ ��� ����(CODE_SWTYPE����)
	int								cbsw_rtutype;					// ����ġ�� RTU ����(CODE_RTUTYPE����)
	int								cbsw_RTUCODE;					// ����ġ�� RTU ��ſ���
	int								cbsw_norstat;					// ����ġ�� �ʱⰳ����� �Է�
	int								cbsw_ii_prde;
	int								cbsw_si_fnd;					// CBSW���� From �� ND���� sibling index
	int								cbsw_ii_fnd;					// CBSW���� From �� ND���� indirect index
	int								cbsw_si_tnd;					// CBSW���� To �� ND���� sibling index
	int								cbsw_ii_tnd;					// CBSW���� To �� ND���� indirect index
	int								cbsw_si_fgnd;					// CBSW���� From �� GND���� sibling index
	int								cbsw_ii_fgnd;					// CBSW���� From �� GND���� indirect index
	int								cbsw_si_tgnd;					// CBSW���� To �� GND���� sibling index
	int								cbsw_ii_tgnd;					// CBSW���� To �� GND���� indirect index
	int								cbsw_ii_dl;					// Indirect index
	int								cbsw_si_dl;					// Sibling Index
	wchar_t							cbsw_multisw_id[64];					// ��ȸ�� ����ġ ID
	int								cbsw_multicir_number;					// ��ȸ�� ���ڹ�ȣ
	int								cbsw_comtype;

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} CBSW_STA;
#define								CBSW_STA_SIZE						sizeof( CBSW_STA )


// Table : CBSW_DYN_UIN, Type : Online
typedef struct _CBSW_DYN_UIN
{
	int								cbsw_meause;					// ������ ��� ���� ǥ����(1 : ���, 0: ��� ����)
	int								cbsw_manf;					// ������ ���� ���� ǥ����(1 : ������ ����, 0: ���� ����)
	int								cbsw_manstat;					// �������� ���� (1: close, 0: open)
	int								cbsw_dnrimpo;					// NR ���� ���ܽ���ġ(��������:1,��������:2)
	int								cbsw_ctdir;					// CT �ؼ������� Device�� ���� ����(Terminal ����)�� ���� ACM���� From/To ������ ��ġ�� ����(��ġ: 1, ����ġ: 2)

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} CBSW_DYN_UIN;
#define								CBSW_DYN_UIN_SIZE						sizeof( CBSW_DYN_UIN )


// Table : CBSW_DYN_MEA, Type : Online
typedef struct _CBSW_DYN_MEA
{
	int								cbsw_odstat;					// ���� ���� ���� (1: close, 0: open)
	int								cbsw_nwstat;					// ���� ���� ���� (1: close, 0: open)
	double							cbsw_pameakv;					// From ��� ������ A�� ���� KV
	double							cbsw_pbmeakv;					// From ��� ������ B�� ���� KV
	double							cbsw_pcmeakv;					// From ��� ������ C�� ���� KV
	double							cbsw_pameaamp;					// A�� ����
	double							cbsw_pbmeaamp;					// B�� ����
	double							cbsw_pcmeaamp;					// C�� ����
	double							cbsw_pameaadiff;					// A�� ����-���� ������
	double							cbsw_pbmeaadiff;					// B�� ����-���� ������
	double							cbsw_pcmeaadiff;					// C�� ����-���� ������
	int								cbsw_comstatser;					// Server���� ��Ż���(���� : 1, ������ : 0) --> CBSW_COMSTASTDE�� 0���� �Ҵ���
	int								cbsw_contstat;					// ����ġ ����ɿ�(1)/��(0) (��� �ҷ��� �ƴ�, �������� �Ұ��� ���¸� ǥ��)

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} CBSW_DYN_MEA;
#define								CBSW_DYN_MEA_SIZE						sizeof( CBSW_DYN_MEA )


// Table : CENTER_STA, Type : Online
typedef struct _CENTER_STA
{
	wchar_t							center_nm[64];					// ��������(Control Center) ��
	wchar_t							center_officeid[64];			// CENTER�� Office ID
	int								center_hi_bof;					// CENTER���� BOF���� head index

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3

	int								nCENTER_HEAD_OFFICE_FK;
	int								nCENTER_II_HDOF;
	int								nCENTER_SI_HDOF;
} CENTER_STA;
#define								CENTER_STA_SIZE						sizeof( CENTER_STA )


// Table : DIAINFO_STA, Type : Online
typedef struct _DIAINFO_STA
{
	int								diainfo_ceqtype;					// ���뵵 ���� ����
	int								diainfo_ceqindex;					// ���뵵 ���� �ε���
	int								diainfo_coordiorder;					// ���뵵 ��Ƽ���� ��ǥ ����
	double							diainfo_ceqax;					// ���뵵�� X�� ��ǥ����
	double							diainfo_ceqay;					// ���뵵�� Y�� ��ǥ����

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} DIAINFO_STA;
#define								DIAINFO_STA_SIZE						sizeof( DIAINFO_STA )


// Table : DL_STA, Type : Online
typedef struct _DL_STA
{
	wchar_t							dl_nm[64];					// ����(Feeder)��
	wchar_t							dl_distributionlineid[64];					// DistributionLine�� CEQID
	int								dl_ii_olm;					// DL���� OLM(overload monitoring)������ indirect index
	int								dl_ii_mtr;					// DL���� MTR���� indirect index
	int								dl_si_mtr;					// DL���� MTR���� sibling index
	int								dl_ii_bof;
	int								dl_si_bof;
	int								dl_hi_ij;					// DL���� IJ���� Head index
	int								dl_hi_cbsw;					// DL���� CBSW���� Head index (������ ���� CBSW�� ����)
	int								dl_hi_br;					// DL���� GBR���� Head index
	int								dl_ii_cb;

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3

	wchar_t							stDL_MTRFK[64];
	wchar_t							stDL_CEQFK[64];
	wchar_t							stDL_PVLFK[64];
	wchar_t							stDL_SVLFK[64];
	wchar_t							stDL_SUBFK[64];
} DL_STA;
#define								DL_TA_SIZE						sizeof( DL_STA )


// Table : DL_DYN_UIN, Type : Online
typedef struct _DL_DYN_UIN
{
	int								dl_protecseq;					// �ش� DL���� ����ϴ� ���ú�ȣ���� Ƚ��
	double							dl_cvrfactor;					// �ش� DL�� CVR ���� �� ����Ǵ� ��ȿ���� ���Һ���
	double							dl_peaklim;					// �ִ� ����(Peak Load) ���� ��
	double							dl_oprcapacity;					// ��������
	int								dl_sca_allflag;
	int								dl_sop_flag;

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} DL_DYN_UIN;
#define								DL_DYN_UIN_SIZE						sizeof( DL_DYN_UIN )


// Table : DNROPT_DYN_UIN, Type : Online
typedef struct _DNROPT_DYN_UIN
{
	int								dnropt_max_iterpfo;					// ������� �ִ�ݺ�Ƚ��
	int								dnropt_max_iterga;					// �����˰��� �ִ�ݺ�Ƚ��
	int								dnropt_nunpop;					// �����˰��� ����ü��
	int								dnropt_mutation_rate;					// �����˰��� �������̹߻� ���� (%)
	double							dnropt_ratio_lb;					// ���� �����Լ����� �ս��Ǻ���(0.1~0.9)
	int								dnropt_cben;					// NR�� CB�� ��������
	int								dnropt_reen;					// NR�� RECLOSER�� ��������
	int								dnropt_gaen;					// NR�� �ڵ�ȭ ����ġ�� ��������
	int								dnropt_maen;					// NR�� ���� ����ġ�� ��������
	int								dnropt_object;					// NR�� �����Լ�(1.�ս����� 2.�Ǵ��뷱�� 3,���ո����Լ�)
	int								dnropt_max_chgsw;					// �ִ� ��� ����ġ ������ (0:���Ѿ���, 1~:����ġ ���Ѽ�)
	int								dnropt_penalty_chgsw;					// ��� ����ġ ������ �ʰ��п� ���� �г�Ƽ��
	int								dnropt_penalty_volt;					// ���� ����ġ �ʰ��п� ���� �г�Ƽ��
	int								dnropt_penalty_mw;					// �뷮����ġ �ʰ��п� ���� �г�Ƽ��

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} DNROPT_DYN_UIN;
#define								DNROPT_DYN_UIN_SIZE						sizeof( DNROPT_DYN_UIN )


// Table : EQUTY_STA, Type : Online
typedef struct _EQUTY_STA
{
	wchar_t							equty_nm[64];					// ��������
	int								equty_hi_gbr;					// EQUTY���� GBR���� head index
	int								equty_hi_ij;					// EQUTY���� IJ���� head index

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} EQUTY_STA;
#define								EQUTY_STA_SIZE						sizeof( EQUTY_STA )


// Table : ESCOPT_DYN_UIN, Type : Online
typedef struct _ESCOPT_DYN_UIN
{
	double							escopt_smwprp;					// �ý��� ��ũ reduction price
	double							escopt_dmwprp;					// MG ��ũ reduction price
	int								escopt_fsoctm;					// Full SOC ���� �ð�

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} ESCOPT_DYN_UIN;
#define								ESCOPT_DYN_UIN_SIZE						sizeof( ESCOPT_DYN_UIN )


// Table : ESS_STA, Type : Online
typedef struct _ESS_STA
{
	wchar_t							ess_nm[64];					// Energy Storage System(ESS) ��Ī
	int								ess_chgtm;					// ESS �������� �ð�
	int								ess_dchgtm;					// ESS �������� �ð�
	int								ess_ii_gen;
	int								ess_si_gen;
	int								ess_type;					// ESS�� Battery Type
	double							ess_charmxmw;					// ������ �ִ���°�
	double							ess_charmnmw;					// ������ �ּ���°�
	double							ess_dichmxmw;					// ������ �ִ���°�
	double							ess_dichmnmw;					// ������ �ּ���°�
	double							ess_mxsoc;					// �����翡�� �����ϴ� ����SOC ���Ѱ�
	double							ess_mnsoc;					// �����翡�� �����ϴ� ����SOC ���Ѱ�
	double							ess_chgeff;					// ���� ȿ��
	double							ess_c_ratio;					// ESS�� C_RATIO
	int								ess_hi_pcs;					// ESS���� PCS���� Head Index
	int								ess_noofpcs;					// ESS�� �Ҽӵ� PCS ����
	double							ess_capmwh;					// ESS �ִ� �뷮

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} ESS_STA;
#define								ESS_STA_SIZE						sizeof( ESS_STA )


// Table : ESS_DYN_UIN, Type : Online
typedef struct _ESS_DYN_UIN
{
	double							ess_setmxsoc;					// ���͸� ����SOC ���Ѱ�
	double							ess_setmnsoc;					// ���͸� ����SOC ���Ѱ�
	double							ess_efin;					// ESS�� ���� ������ ��ǥ�� (SOC ���� ��ǥġ)
	double							ess_clrmxsoc;					// SOC ���� ����� �������� SOC ȸ�� ������� �Ǵ� ����
	double							ess_clrmnsoc;					// SOC ���� ����� �������� SOC ȸ�� ������� �Ǵ� ����
	int								ess_cntmode;					// ���� ��� (CVCF/TARGET)
	double							ess_socmxdband;					// �ִ� SOC ���� ���� �̻����� SOC�� �Ѿ ��� �����ؾ� �ϴ� ���·��� ���ϱ� ���� ����
	double							ess_socmndband;					// �ּ� SOC ���� ���� ���Ϸ� SOC�� ������ ��� �����ؾ� �ϴ� ���·��� ���ϱ� ���� ����
	int								ess_soc_ncount_max;					// ESS�� SOC�� �����ð����� �������� ���� �� �̻� �߻� ���θ� �Ǵ��ϴ� ����
	double							ess_soc_dev_absolute_max;					// ESS�� SOC �������� ���밪 ũ���� �Ѱ� ���ذ�
	int								ess_mode;					// PMS�� ���� �ڵ�/���� ���� Flag(0: ����, 1: �ڵ�)
	double							ess_gensche[192];					// PMS�� ���� ���� ��� ������
	int								ess_esschgmode[192];					// PMS�� �������� ��/���� ���  ������
	double							ess_opp;					// ESS ���� ���
	int								ess_outage_time;					// �ð�

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} ESS_DYN_UIN;
#define								ESS_DYN_UIN_SIZE						sizeof( ESS_DYN_UIN )


// Table : GBR_STA, Type : Online
typedef struct _GBR_STA
{
	wchar_t							gbr_nm[64];					// �б⼱��
	int								gbr_ii_equ;					// GBR���� ���� ����(LNSEC, TR)���� indirect index
	int								gbr_si_fgnd;					// GBR���� GND���� sibling index
	int								gbr_ii_fgnd;					// GBR���� GND���� indirect index
	int								gbr_si_tgnd;					// GBR���� GND���� sibling index
	int								gbr_ii_tgnd;					// GBR���� GND���� indirect index
	double							gbr_posr;					// ����� ����
	double							gbr_posx;					// ����� �����Ͻ�
	double							gbr_posg;					// ����� �����Ͻ�
	double							gbr_posb;					// ����� �����Ͻ�
	double							gbr_zerr;					// ����� ����
	double							gbr_zerx;					// ����� �����Ͻ�
	double							gbr_zerg;					// ����� �����Ͻ�
	double							gbr_zerb;					// ����� �����Ͻ�
	int								gbr_hi_br;					// GBR���� BR���� Head Index
	int								gbr_si_equty;					// GBR���� EQUTY���� Sibling Index
	int								gbr_ii_equty;					// GBR���� EQUTY���� Indirect Index
	int								gbr_ii_dl;					// DL���� Indirect index
	int								gbr_si_dl;					// DL���� Sibling index

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} GBR_STA;
#define								GBR_STA_SIZE						sizeof( GBR_STA )


// Table : GBR_DYN_UIN, Type : Online
typedef struct _GBR_DYN_UIN
{
	int								gbr_morflag;					// ���� ����/���б��� ������ ���� ����(1: ����, 0: ���þ���)
	int								gbr_scaflag;					// ������� branch ���� ��꿡 ������ ������ ����(1: ����, 0: ���Ծ���)

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} GBR_DYN_UIN;
#define								GBR_DYN_UIN_SIZE						sizeof( GBR_DYN_UIN )

// Table : GEN_STA, Type : Online
typedef struct _GENUNIT_STA
{
	wchar_t							GENUNIT_CEQID[64];					// ������ ��
	wchar_t							GENUNIT_NM[128];					// ������ ��
	int								GENUNIT_II_GEN;					// GEN���� ND���� sibling index
	int								GENUNIT_SI_GEN;					// GEN���� ND���� sibling index
	double							GENUNIT_CAP_KW;					// GEN���� ND���� sibling index
	wchar_t							GENUNIT_LOCATION_NO[64];						// ������ CEQ ID
	wchar_t							GENUNIT_LOCATION_NM[64];						// ������ CEQ ID
	wchar_t							GENUNIT_CUSTOMER_NO[64];						// ������ CEQ ID.
	int								GENUNIT_TYPE;					// GEN���� ND���� sibling index
	wchar_t							GENUNIT_II_EQU_ID[64];					// 20220809
	int								GENUNIT_II_NAME_TYPE_FK;
	int								GENUNIT_INDEX;
	

} GENUNIT_STA;
#define								GENUNIT_STA_SIZE						sizeof( GENUNIT_STA )

// Table : GEN_STA, Type : Online
typedef struct _GEN_STA
{
	wchar_t							gen_nm[64];					// ������ ��
	wchar_t							gen_ceqid[64];						// ������ CEQ ID
	int								gen_si_nd;					// GEN���� ND���� sibling index
	int								gen_ii_nd;					// GEN���� ND���� indirect index
	int								gen_si_gnd;					// GEN���� GND���� sibling index
	int								gen_ii_gnd;					// GEN���� GND���� indirect index
	int								gen_ii_ij;					// GEN���� IJ���� indirect index
	double							gen_namkv;					// Gen�� ��� ��������
	double							gen_mwlmmx;					// �ִ� MW �����뷮(����뷮 ����)
	double							gen_mwlmmn;					// �ּ� MW �����뷮(����뷮 ����)
	double							gen_mvarlmmx;					// �ִ� MVAR ����ġ(����뷮 ����)
	double							gen_mvarlmmn;					// �ּ� MVAR ����ġ(����뷮 ����)
	double							gen_r;					// ������ ����
	double							gen_stx;					// ������ ������ �����Ͻ�
	double							gen_ssx;					// ������ ���� �����Ͻ�
	int								gen_type;					// ������ ���� (1:���Ѹ�, 2: ����, 3:ESS, 4:ǳ��, 5:�¾籤, 6:���п���, 7: ��п���)
	int								gen_vol_cls;
	int								gen_ii_connd;					// control node���� indriect index
	int								gen_conndrep;					// control node�� �������� ���� ������(1:A��,2:B��,3:C��,4:AB,5:BC,6:CA)
	int								gen_contype;					// �л����� ���� ���� (1:A ��, 2:B��, 3:C��, 4:AB��, 5:BC��, 6:CA��, 7:3��)
	int								gen_noofp;					// �ؼ� (defualt 4)
	double							gen_pf;					// ���� (default 0.85)
	double							gen_eff;					// ȿ�� (default 0.85)
	double							gen_pfminlag;					// ������ ����� �ּ� ���� ����
	double							gen_pfminlead;					// ������ ����� �ּ� ���� ����
	int								gen_ii_ess;					// Gen���� ESS���� Indrect Index
	int								gen_mea;					// ���� ���� ����(0: ����, 1: ����)
	int								gen_avr;					// �ڵ����� ���� �������� (1: ����, 0: ��������)
	int								GEN_II_PRDE;
	int								GEN_TREXCL;

	double							fGEN_ITR_CAP;
	double							fGEN_ITR_R;
	double							fGEN_ITR_X;
	double							fGEN_ITR_NGR_R;
	double							fGEN_ITR_NGR_X;
	int								nGEN_ITR_WDC;
	int								nGEN_MACH_TYPE;

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} GEN_STA;
#define								GEN_STA_SIZE						sizeof( GEN_STA )


// Table : GEN_DYN_UIN, Type : Online
typedef struct _GEN_DYN_UIN
{
//	int								gen_avr;					// �ڵ����� ���� �������� (1: ����, 0: ��������)
	double							gen_tbsvl;					// ���� ���� ���� ��ǥġ
	double							gen_dev;					// ���� �� A���� ���� ��ǥġ ����
	double							gen_pf;					// ������� ���� ���� ��ǥġ
	int								gen_vvoflag;					// ������ ��ȿ���� ��� VVO ��������(0: ����, 1: ����)
	int								gen_mvarconmode;					// ��ȿ���� ������(1:����, 2:����, 3: ������ȿ����)
	double							gen_outq;					// ���� ��ȿ���� ���� ����� �������� ��ȿ���� ��ǥġ
	double							gen_pfvvominlag;					// VVO ����� ������ �ּ� ���� ����
	double							gen_pfvvominlead;					// VVO ����� ������ �ּ� ���� ����


	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} GEN_DYN_UIN;
#define								GEN_DYN_UIN_SIZE						sizeof( GEN_DYN_UIN )


// Table : GND_STA, Type : Online
typedef struct _GND_STA
{
	wchar_t							gnd_nm[64];					// Group ����
	int								gnd_hi_nd;					// Group ND���� ND���� Head index
	int								gnd_hi_fcbsw;					// GND���� From �� CBSW���� head index
	int								gnd_hi_tcbsw;					// GND���� To�� CBSW���� head index
	int								gnd_hi_fgbr;					// GND���� From�� GBR���� head index
	int								gnd_hi_tgbr;					// GND���� To�� GBR���� head index
	int								gnd_hi_gen;					// GND���� GEN���� head index
	int								gnd_hi_shunteq;					// GND���� SHUNTEQ���� head index
	int								gnd_hi_svc;					// GND���� SVC���� head index
	int								gnd_hi_ld;					// GND���� LD���� head index
	int								gnd_hi_ij;					// GND���� IJ���� head index
	int								gnd_hi_hvcus;

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3

	int								nGND_SS;
} GND_STA;
#define								GND_STA_SIZE						sizeof( GND_STA )


// Table : IJ_STA, Type : Online
typedef struct _IJ_STA
{
	wchar_t							ij_nm[64];					// Injection ��
	int								ij_si_equty;					// IJ���� EQUTY���� sibling index
	int								ij_ii_equty;					// IJ���� EQUTY���� indirect index
	int								ij_ii_equ;					// IJ���� ���� ������� indirect index
	int								ij_si_gnd;					// IJ���� GND���� sibling index
	int								ij_ii_gnd;					// IJ���� GND���� indirect index
	int								ij_ii_dl;					// DL���� Indirect index
	int								ij_si_dl;					// DL���� Sibling index

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} IJ_STA;
#define								IJ_STA_SIZE						sizeof( IJ_STA )


// Table : IJ_STA, Type : Online
typedef struct _IJ_DYN_UIN
{
	int								ij_socmaxorder;					// SOC Max ���� �ʰ��� �������
	int								ij_socminorder;					// SOC Min ���� �ʰ��� �������

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} IJ_DYN_UIN;
#define								IJ_DYN_UIN_SIZE					sizeof( IJ_DYN_UIN )


// Table : IJ_DYN_MEA, Type : Online
typedef struct _IJ_DYN_MEA
{
	double							ij_3pmeamw;					// 3�� �ϰ��� MW ������
	double							ij_3pmeamvar;					// 3�� �ϰ��� MVAR ������
	double							ij_pameamw;					// A����  MW ������
	double							ij_pameamvar;					// A���� MVAR ������
	double							ij_pbmeamw;					// B����  MW ������
	double							ij_pbmeamvar;					// B���� MVAR ������
	double							ij_pcmeamw;					// C����  MW ������
	double							ij_pcmeamvar;					// C���� MVAR ������
	int								ij_meaflag;					// AMI Gateway ����ġ ����(1: ����, 0: ���� �Ǵ� �κ�����)

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} IJ_DYN_MEA;
#define								IJ_DYN_MEA_SIZE						sizeof( IJ_DYN_MEA )


// Table : INNERPOLE_STA, Type : Online
typedef struct _INNERPOLE_STA
{
	wchar_t							innerpole_nm[64];					// ���ָ� (���󼳺� ����)
	int								innerpole_ii_lnsec;					// INNERPole �� LNSEC�� from�� ������ Head Index
	int								innerpole_si_lnsec;					// INNERPole �� LNSEC�� to�� ������ Head Index
	double							innerpole_xcoodi;					// ������ ���뵵(or GIS)�� X�� ��ǥ����
	double							innerpole_ycoodi;					// ������ ���뵵(or GIS)�� Y�� ��ǥ����
	//20200320
	int								innerpole_patrtap;
	int								innerpole_pbtrtap;
	int								innerpole_pctrtap;
	wchar_t							innerpole_comnm[64];
	int								innerpole_numcustom;

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} INNERPOLE_STA;
#define								INNERPOLE_STA_SIZE						sizeof( INNERPOLE_STA )


// Table : INNERSEC_STA, Type : Online
typedef struct _INNERSEC_STA
{
	wchar_t							innersec_nm[64];					// ���θ�
	int								innersec_ndissysid;					// NDIS�� ����(HVLINE)�� SYS ID
	int								innersec_ii_lnsec;					// INNERSEC �� LNSEC������ Indirect Index
	int								innersec_si_lnsec;					// INNERSEC �� LNSEC������ sibling Index
	int								innersec_linetype;					// ����

	int								innersec_hvl_seq;
	double							innersec_fx;
	double							innersec_fy;
	double							innersec_tx;
	double							innersec_ty;

	int							innersec_id;


	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} INNERSEC_STA;
#define								INNERSEC_STA_SIZE						sizeof( INNERSEC_STA )


// Table : LD_STA, Type : Online
typedef struct _LD_STA
{
	wchar_t							ld_nm[64];					// ���� ���ϸ�
	int								ld_si_gnd;					// LD���� GND���� sibling index
	int								ld_ii_gnd;					// LD���� GND���� indirect index
	int								ld_ii_ij;					// LD���� IJ���� indirect index

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} LD_STA;
#define								LD_STA_SIZE						sizeof( LD_STA )


// Table : LD_DYN_UIN, Type : Online
typedef struct _LD_DYN_UIN
{
	double							ld_div;					// ���� ���� ���Ұ��

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} LD_DYN_UIN;
#define								LD_DYN_UIN_SIZE						sizeof( LD_DYN_UIN )


// Table : LNSEC_STA, Type : Online
typedef struct _LNSEC_STA
{
	int								lnsec_sta_id;
	 
	wchar_t							lnsec_nm[64];					// ���α���
	wchar_t							lnsec_ceqid[64];					// ACLineSegment�� CEQID
	int								lnsec_ii_br;					// LNSEC���� BR���� indirect index
	int								lnsec_hi_innerpole;					// LNSEC���� INNERPOLE���� HEAD index
	int								lnsec_hi_fpole;					// LNSEC���� from�� POLE���� HEAD index
	int								lnsec_hi_tpole;					// LNSEC���� to�� POLE���� HEAD index
	int								lnsec_hi_innersec;					// LNSEC���� INNERSEC���� HEAD index
	int								lnsec_privat;					// ������ ���뼱�� ����(1:���뼱��, 0:�Ϲݼ���)
	int								lnsec_type_id;					// KASIM_CODE_LINETYPE����
	double							lnsec_length;					// ���� ����(km)
	int								lnsec_constype;					// ���� ����/���� ����


	int								lnsec_SI_FND;					// ���� ����/���� ����
	int								lnsec_II_FND;					// ���� ����/���� ����
	int								lnsec_SI_TND;					// ���� ����/���� ����
	int								lnsec_II_TND;					// ���� ����/���� ����


	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} LNSEC_STA;
#define								LNSEC_STA_SIZE						sizeof( LNSEC_STA )


// Table : MTR_STA, Type : Online
typedef struct _MTR_STA
{
	wchar_t							mtr_nm[64];					// �ֺ��б�(Group ������) ��
	wchar_t							mtr_maintrid[64];					// MainTransformer�� CEQID
	int								mtr_ii_ss;					// MTR���� SS���� indirect index
	int								mtr_si_ss;					// MTR���� SS���� sibling index
	int								mtr_hi_dl;					// MTR���� DL���� head index

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3

	wchar_t							stMTR_PRIMARY_VOLTAGELEVEL[64];
	wchar_t							stMTR_SECONDARY_VOLTAGELEVEL[64];

	int								mtr_hi_tr;					// MTR���� DL���� head index
	int								mtr_bank;					// MTR���� DL���� head index

} MTR_STA;
#define								MTR_STA_SIZE						sizeof( MTR_STA )

typedef struct _MTR_DYN_UIN
{
	int								mtr_sop_flag;					// SOP�������
	int								mtr_sca_allflag;				// ���� �������� �����뼺

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} MTR_DYN_UIN;
#define								MTR_DYN_UIN_SIZE						sizeof( MTR_DYN_UIN )


// Table : NCPOPT_DYN_UIN, Type : Online
typedef struct _NCPOPT_DYN_UIN
{
	int								ncpopt_islbs;					// ��ȿ �������� �ּ� �𼱼�
	int								ncpopt_islgen;					// ��ȿ �������� �ּ� �������
	int								ncpopt_islld;					// ��ȿ �������� �ּ� ���ϼ�
	int								ncpopt_init;					// NCP Initial Mode ���� ���� Flag(1: ��������, 0: �������)

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} NCPOPT_DYN_UIN;
#define								NCPOPT_DYN_UIN_SIZE						sizeof( NCPOPT_DYN_UIN )


// Table : ND_STA, Type : Online
typedef struct _ND_STA
{
	wchar_t							nd_nm[64];					// ����
	wchar_t							nd_ceqid[64];					// BusbarSection�� CEQID
	wchar_t							nd_connectivitynodeid[64];					// BusbarSection�� CEQID
	int								nd_si_snv;					// ND���� SNV���� sibling index
	int								nd_ii_snv;					// ND���� SNV���� indirect index
	int								nd_hi_fcbsw;					// ND���� From �� CBSW���� head index
	int								nd_hi_tcbsw;					// ND���� To�� CBSW���� head index
	int								nd_hi_fbr;					// ND���� From�� BR���� head index
	int								nd_hi_tbr;					// ND���� To�� BR���� head index
	int								nd_hi_gen;					// ND���� GEN���� head index
	int								nd_hi_shunteq;					// ND���� SHUNTEQ���� head index
	int								nd_hi_svc;					// ND���� SVC���� head index
	int								nd_ii_gnd;					// ND���� GND���� Indirect Index
	int								nd_si_gnd;					// ND���� GND���� Sibling Index

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3

	int								nND_DL;
	int								nND_SS;
} ND_STA;
#define								ND_STA_SIZE						sizeof( ND_STA )


// Table : ND_DYN_UIN, Type : Online
typedef struct _ND_DYN_UIN
{
	int								nd_morflag;					// Node�� ���а��� ����(1: ����, 0: ���þ���)
	int								nd_ii_vvm;					// ND���� VVM(voltage violation monitoring)������ indirect index

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} ND_DYN_UIN;
#define								ND_DYN_UIN_SIZE						sizeof( ND_DYN_UIN )


// Table : OLM_STA, Type : Online
typedef struct _OLM_STA
{
	wchar_t							olm_nm[64];					// Overload monitoring group�� ��Ī

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} OLM_STA;
#define								OLM_STA_SIZE						sizeof( OLM_STA )


// Table : OLM_DYN_UIN, Type : Online
typedef struct _OLM_DYN_UIN
{
	int								olm_morflag;					// OLM group�� ���� Ȱ�� ����(1: ����, 0: ���þ���)
	double							olm_tol;					// OLM ���ø� ���� tolerance
	double							olm_dband;					// OLM ���ø� ���� dead band

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} OLM_DYN_UIN;
#define								OLM_DYN_UIN_SIZE						sizeof( OLM_DYN_UIN )


// Table : PFVM_STA, Type : Online
typedef struct _PFVM_STA
{
	wchar_t							pfvm_nm[64];					// Power Factor violation monitoring group�� ��Ī

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} PFVM_STA;
#define								PFVM_STA_SIZE						sizeof( PFVM_STA )


// Table : PFVM_DYN_UIN, Type : Online
typedef struct _PFVM_DYN_UIN
{
	int								pfvm_morflag;					// PFVM group�� ���� Ȱ�� ����(1: ����, 0: ���þ���)
	double							pfvm_lm;					// PFVM group�� ���� limit
	double							pfvm_tol;					// PFVM ���ø� ���� tolerance
	double							pfvm_dband;					// PFVM ���ø� ���� dead band

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} PFVM_DYN_UIN;
#define								PFVM_DYN_UIN_SIZE						sizeof( PFVM_DYN_UIN )


// Table : POLE_STA, Type : Online
typedef struct _POLE_STA
{
	wchar_t							pole_nm[64];					// ���ָ� (���󼳺� ����)
	wchar_t							pole_comnm[64];					// ��������ȭ ��ȣ


	int								pole_sysid;						// Pole���� INNERPOLE���� indirect index
	int								pole_ii_innerpole;				// Pole���� INNERPOLE���� indirect index
	int								pole_ptrflag;					// Pole�� ����� ���б� ����(1:����, 0:����)
	int								pole_numcustom;					// ����� ��ȣ��

	wchar_t							pole_SYSID_ID[64];
	wchar_t							pole_MRID[64];
	int								pole_nseq;
	double							pole_f1EQx;
	double							pole_f1EQy;

	double							pole_f2EQx;
	double							pole_f2EQy;

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} POLE_STA;
#define								POLE_STA_SIZE						sizeof( POLE_STA )


// Table : RPFOPT_DYN_UIN, Type : Online
typedef struct _RPFOPT_DYN_UIN
{
	int								rpfopt_flat;					// Flat start ����
	int								rpfopt_max_iterations;					// �ִ� �ݺ�Ƚ��
	int								rpfopt_svc_adj_limit;					// SVC ����Ƚ��
	double							rpfopt_island_max_voltage_limit;					// ������� �ִ�
	double							rpfopt_island_min_voltage_limit;					// ������� �ּ�
	double							rpfopt_near_convergence_angle_limit;					// �κм��� ����(����)
	double							rpfopt_near_convergence_voltage_limit;					// �κм��� ����(����)
	double							rpfopt_near_convergence_mw_limit;					// �κм��� ����(MW)
	double							rpfopt_near_convergence_mvar_limit;					// �κм��� ����(MVAr)
	double							rpfopt_convergence_angle_limit;					// �������� ����(����)
	double							rpfopt_convergence_voltage_limit;					// �������� ����(����)
	double							rpfopt_convergence_mw_limit;					// �������� ����(MW)
	double							rpfopt_convergence_mvar_limit;					// �������� ����(MVAr)
	double							rpfopt_largest_mismatch_limit;					// �ִ� Mismatch

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} RPFOPT_DYN_UIN;
#define								RPFOPT_DYN_UIN_SIZE						sizeof( RPFOPT_DYN_UIN )


// Table : SCAOPT_DYN_UIN, Type : Online
typedef struct _SCAOPT_DYN_UIN
{
	double							scaopt_fltz;					// ������ ���Ǵ���
	int								scaopt_basemva;					// ���� �뷮
	int								scaopt_basefreq;					// ���� ���ļ�
	int								scaopt_flttype_3p;					// 3����� ��� ���� Flag (1: �����, 0: ������)
	int								scaopt_flttype_2p;					// �����ܶ����� ��� ���� Flag (1: �����, 0: ������)
	int								scaopt_flttype_2g;					// 2���������� ��� ���� Flag (1: �����, 0: ������)
	int								scaopt_flttype_1g;					// 1���������� ��� ���� Flag (1: �����, 0: ������)
	int								scaopt_flttype_p1cir;					// 1����� ���� ��� ���� Flag (1: �����, 0: ������)
	int								scaopt_prev;					// ������� ���� ���� (0: Flat, 1: ���������)
	int								scaopt_allflag;					// ��� �𼱿� ���� ������ ����(0: ������, 1: �Ի���)
	int								scaopt_manbs;					// ������ �� ��ȣ
	int								scaopt_halfflag;					// 1/2 cycle�� ������ ����
	int								scaopt_fiveflag;					// 5 cycle�� ������ ����
	int								scaopt_steadyflag;					// Steady state�� ������ ����

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} SCAOPT_DYN_UIN;
#define								SCAOPT_DYN_UIN_SIZE						sizeof( SCAOPT_DYN_UIN )


// Table : SHUNTEQ_STA, Type : Online
typedef struct _SHUNTEQ_STA
{
	wchar_t							shunteq_nm[64];					// ���� ��ġ
	wchar_t							shunteq_ceqid[64];				// SHUNTEQ�� CEQID
	int								shunteq_si_nd;					// SUNHTEQ���� ND���� sibling index
	int								shunteq_ii_nd;					// SUNHTEQ���� ND���� indirect index
	int								shunteq_si_gnd;					// SUNHTEQ���� GND���� sibling index
	int								shunteq_ii_gnd;					// SUNHTEQ���� GND���� indirect index
	int								shunteq_ii_ij;					// SUNHTEQ���� IJ���� indirect index
	int								shunteq_type;					// Shunt device ����(1: Shunt Capacitor, 2: Shunt Reactor, 3: ��Ÿ)
	double							shunteq_mvar;					// Shunt device�� MVAr �뷮
	int								shunteq_ii_connd;					// Control node���� indriect index
	int								shunteq_repphs;					// control node�� �������� ���� ������(1:A��,2:B��,3:C��,4:AB,5:BC,6:CA)

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} SHUNTEQ_STA;
#define								SHUNTEQ_STA_SIZE						sizeof( SHUNTEQ_STA )


// Table : SHUNTEQ_DYN_UIN, Type : Online
typedef struct _SHUNTEQ_DYN_UIN
{
	int								shunteq_avr;					// �ڵ����� ���� �������� (1: ����, 0: ��������)
	double							shunteq_tbsvl;					// ���� ���� ���� ��ǥġ
	double							shunteq_dev;					// ���� ���� ���� ��ǥġ ����
	int								shunteq_vvoflag;					// Active Voltage Var control ��� ������ ������ ����
	double							shunteq_shcost;					// Shunt Equipment ����
	int								shunteq_opmx;					// �ִ� ���º��� Ƚ��
	int								shunteq_conmxday;					// �Ϸ� �ִ� ����Ƚ��
	int								shunteq_opday;					// �Ϸ� ����Ƚ��

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} SHUNTEQ_DYN_UIN;
#define								SHUNTEQ_DYN_UIN_SIZE						sizeof( SHUNTEQ_DYN_UIN )


// Table : SNV_STA, Type : Online
typedef struct _SNV_STA
{
	wchar_t							snv_nm[64];					// ������ ��Ī���� ��
	double							snv_norkv;					// ��Ī���� kV
	int								snv_si_ss;					// SNV���� SS���� sibling index
	int								snv_ii_ss;					// SNV���� SS���� indirect index
	int								snv_hi_nd;					// SNV���� ND���� head index

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} SNV_STA;
#define								SNV_STA_SIZE						sizeof( SNV_STA )


// Table : SS_STA, Type : Online
typedef struct _SS_STA
{
	wchar_t							ss_nm[64];					// ������ ��
	wchar_t							ss_substationid[64];		// SubStation�� CEQID
	wchar_t							ss_code[64];				// SubStation�� CEQID
	int								ss_ii_bof;					// SS���� BOF���� indirect index
	int								ss_si_bof;					// SS���� BOF���� sibling index
	int								ss_hi_mtr;					// SS���� MTR���� head index
	int								ss_hi_snv;					// SS���� SNV���� head index

	int								ss_nd;
	int								ss_ii_vgen;

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} SS_STA;
#define								SS_STA_SIZE						sizeof( SS_STA )


// Table : SS_DYN_UIN, Type : Online
typedef struct _SS_DYN_UIN
{
	int								ss_dnrflag;					// �ش� SS�� DNR�� ���꿵������ ������(1: ���� ����, 0: ��������)
	double							ss_tieoutkw;					// ���輱�� �������� �Ѱ谪
	double							ss_tieinkw;					// ���輱�� �������� �Ѱ谪

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} SS_DYN_UIN;
#define								SS_DYN_UIN_SIZE						sizeof( SS_DYN_UIN )


// Table : SVC_STA, Type : Online
typedef struct _SVC_STA
{
	wchar_t							svc_nm[64];					// SVC ��
	wchar_t							svc_ceqid[64];				// SVC�� CEQID
	int								svc_si_nd;					// SVC���� ND���� sibling index
	int								svc_ii_nd;					// SVC���� ND���� indirect index
	int								svc_si_gnd;					// SVC���� GND���� sibling index
	int								svc_ii_gnd;					// SVC���� GND���� indirect index
	int								svc_ii_ij;					// SVC���� IJ���� indirect index
	double							svc_shmvar;					// SVC�� ��ȿ���¿뷮(MVAR)
	int								svc_bano;					// SVC�� BANO
	double							svc_mvarlmmn;					// SVC �������� �ּ� MVAR���ѿ뷮
	double							svc_mvarlmmx;					// SVC �������� �ִ� MVAR���ѿ뷮
	int								svc_ii_connd;					// ������
	int								svc_conndrep;					// control node�� �������� ���� ������(1:A��,2:B��,3:C��,4:AB,5:BC,6:CA)

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} SVC_STA;
#define								SVC_STA_SIZE						sizeof( SVC_STA )


// Table : SVC_DYN_UIN, Type : Online
typedef struct _SVC_DYN_UIN
{
	double							svc_tarvol;					// SVC�� ��ǥ���а�
	double							svc_slop;					// SVC Sloop Ư��
	int								svc_vvoflag;					// SVC�� VVO ��������(1:����, 0:������)

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} SVC_DYN_UIN;
#define								SVC_DYN_UIN_SIZE						sizeof( SVC_DYN_UIN )


// Table : TR_STA, Type : Online
typedef struct _TR_STA
{
	wchar_t							tr_nm[64];					// ���б��
	wchar_t							tr_ceqid[64];					// ���б� CEQID
	int								tr_type;					// 2,3�Ǽ�, SVR ������ (1: 2�Ǽ� MTR, 2: 3�Ǽ� MTR, 3: SVR, 4: �Ϲ� 2�Ǽ�, 5: �Ϲ� 3�Ǽ�)
	int								tr_ii_br;					// TR���� GBR���� indirect index
	double							tr_fnorkv;					// From �� ��Ī����
	double							tr_tnorkv;					// To �� ��Ī����	
	double							tr_trmva;					// TR �뷮
	int								tr_conty;					// �ἱ��� (0: From, To ��� ������, 1: From �� ����, 2: To�� ����, 3: From, To ��� ����)
	int								tr_onltc;					// OLTC/NLTC ������ (0: OLTC, 1: NLTC)
	double							tr_posx;					// ����� �����Ͻ�
	double							tr_zerx;					// ����� �����Ͻ�
	int								tr_patapmx;					// A�� Tap ���� �ִ�ġ (�� ������ ���� ��� ���ϰ� ���)
	int								tr_patapmn;					// A�� Tap ���� �ּ�ġ (�� ������ ���� ��� ���ϰ� ���)
	int								tr_patapnor;					// A�� ��Ī Tap ��ġ (�� ������ ���� ��� ���ϰ� ���)
	double							tr_patapstep;					// A�� Tap position �� ��ȭ�� (�� ������ ���� ��� ���ϰ� ���)
	int								tr_pbtapmx;					// B�� Tap ���� �ִ�ġ (�� ������ ���� ��� ���ϰ� ���)
	
	int								tr_pbtapmn;					// B�� Tap ���� �ּ�ġ (�� ������ ���� ��� ���ϰ� ���)
	int								tr_pbtapnor;					// B�� ��Ī Tap ��ġ (�� ������ ���� ��� ���ϰ� ���)
	double							tr_pbtapstep;					// B�� Tap position �� ��ȭ�� (�� ������ ���� ��� ���ϰ� ���)
	int								tr_pctapmx;					// C�� Tap ���� �ִ�ġ (�� ������ ���� ��� ���ϰ� ���)
	int								tr_pctapmn;					// C�� Tap ���� �ּ�ġ (�� ������ ���� ��� ���ϰ� ���)
	int								tr_pctapnor;					// C�� ��Ī Tap ��ġ (�� ������ ���� ��� ���ϰ� ���)
	double							tr_pctapstep;					// C�� Tap position �� ��ȭ�� (�� ������ ���� ��� ���ϰ� ���)
	int								tr_ii_connd;					// ��������� indirect index
	double							tr_pgr;					// 1���� ���� ����
	double							tr_pgx;					// 1���� ���� �����Ͻ�
	int								tr_ii_mtr;
	int								tr_si_mtr;
	double							tr_sgr;					// 2���� ���� ����
	double							tr_sgx;					// 2���� ���� �����Ͻ�
	int								tr_ii_ss;					// TR���� SS���� Indirect index
	int								tr_si_ss;					// TR���� SS���� Sibling index
	int								tr_loctap;					// TR���� SS���� Sibling index

	int								TR_LDCTYPE;
	double							TR_DVMMXV;
	double							TR_DVMMNV;



	int								tr_SI_FND;					// ���� ����/���� ����
	int								tr_II_FND;					// ���� ����/���� ����
	int								tr_SI_TND;					// ���� ����/���� ����
	int								tr_II_TND;					// ���� ����/���� ����
	int								tr_gbr;

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} TR_STA;
#define								TR_STA_SIZE						sizeof( TR_STA )


// Table : TR_DYN_UIN, Type : Online
typedef struct _TR_DYN_UIN
{
	int								tr_avr;					// ���� ���� Mode (1: AVR, 0: Tap ����)
	double							tr_patbsvl;					// ���� ���� A�� ���� ��ǥġ
	double							tr_padev;					// ���� �� A���� ���� ��ǥġ ����
	double							tr_pbtbsvl;					// ���� ���� B�� ���� ��ǥġ
	double							tr_pbdev;					// ���� �� B���� ���� ��ǥġ ����
	double							tr_pctbsvl;					// ���� ���� C�� ���� ��ǥġ
	double							tr_pcdev;					// ���� �� C���� ���� ��ǥġ ����
	int								tr_vvoflag;					// VVO ���� ���� ����(0: ����, 1: ����)
	int								tr_con3p;					// 3�� �ϰ����� ����(0: ������, 1: 3�� �ϰ�����)
	int								tr_ii_pfvm;					// Power Factor Monitoring group������ indirect index
	double							tr_pacompr;					// A�� compensator R (���� �߽��������� � R��)
	double							tr_pacompx;					// A�� compensator X (���� �߽��������� � X��)
	double							tr_pbcompr;					// B�� compensator R (���� �߽��������� � R��)
	double							tr_pbcompx;					// B�� compensator X (���� �߽��������� � X��)
	double							tr_pccompr;					// C�� compensator R (���� �߽��������� � R��)
	double							tr_pccompx;					// C�� compensator X (���� �߽��������� � X��)
	int								tr_3conmeap;					// 3�� ���� TR�� LDC ���� ����(1=A��, 2=B��, 3=C��)
	double							tr_patapcost;					// -
	double							tr_pacontapmx;					// -
	double							tr_pbtapcost;					// -
	double							tr_pbcontapmx;					// -
	double							tr_pctapcost;					// -
	double							tr_pccontapmx;					// -
	int								tr_pacontapmxday;					// A�� �Ϸ� �ִ� ����Ƚ��
	int								tr_patapopday;					// A�� �Ϸ� ����Ƚ��
	int								tr_pbcontapmxday;					// B�� �Ϸ� �ִ� ����Ƚ��
	int								tr_pbtapopday;					// B�� �Ϸ� ����Ƚ��
	int								tr_pccontapmxday;					// C�� �Ϸ� �ִ� ����Ƚ��
	int								tr_pctapopday;					// C�� �Ϸ� ����Ƚ��

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} TR_DYN_UIN;
#define								TR_DYN_UIN_SIZE						sizeof( TR_DYN_UIN )


// Table : VVM_STA, Type : Online
typedef struct _VVM_STA
{
	wchar_t							vvm_nm[64];					// Voltage violation monitoring group�� ��Ī

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} VVM_STA;
#define								VVM_STA_SIZE						sizeof( VVM_STA )


// Table : VVM_DYN_UIN, Type : Online
typedef struct _VVM_DYN_UIN
{
	int								vvm_morflag;					// VVM group�� ���� Ȱ�� ����(1: ����, 0: ���þ���)
	double							vvm_lmhi;					// VVM group�� ���� high limit
	double							vvm_lmlo;					// VVM group�� ���� low limit
	double							vvm_tolhi;					// VVM ���ø� ���� tolerance ����
	double							vvm_tollo;					// VVM ���ø� ���� tolerance ����
	double							vvm_dband;					// VVM ���ø� ���� dead band

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} VVM_DYN_UIN;
#define								VVM_DYN_UIN_SIZE						sizeof( VVM_DYN_UIN )


// Table : VVOOPT_DYN_UIN, Type : Online
typedef struct _VVOOPT_DYN_UIN
{
	double							vvoopt_tolmx;					// �ս��ּ�ȭ tolerance
	double							vvoopt_vemerstep;					// ���� Emergency Step Size
	double							vvoopt_olemerstep;					// Overloading Emergency Step Size
	double							vvoopt_pfemerstep;					// Power factor Emergency Step Size
	int								vvoopt_emerlevelmx;					// �ִ� emergency level
	int								vvoopt_elitermx;					// emergency level determination �ִ� �ݺ� ���� Ƚ��
	int								vvoopt_scmitermx;					// SCM �ִ� �ݺ� ���� Ƚ��
	int								vvoopt_lmitermx;					// LM �ִ� �ݺ� ���� Ƚ��
	double							vvoopt_pfmslm;					// VVC ������� �ִ� mismatch
	int								vvoopt_pfitermx;					// VVC ������� �ִ� �ݺ� ���� Ƚ��
	int								vvoopt_scm;					// SCM ���� ����(1: ����, 0: ���� ����)
	int								vvoopt_lm;					// LM ���� ����(1: ����, 0: ���� ����)
	double							vvoopt_objmn;					// ELD�� SCM���� ���Ǵ� ���� �Ǵ� ����, ���� �������� �����Լ� ���� ���밪�� �� �� ���ϸ� �������� �Ǵ�
	double							vvoopt_minloss;					// �ս��ּ�ȭ ��� �ս� ���ҷ�(kW)�� �� �� �̻��� ��쿡�� ���ɰ� ���
	int								vvoopt_scmobj;					// ����Ī �ڽ�Ʈ �ּ�ȭ�� �����Լ�(1: ���, 2: Ƚ��)
	double							vvoopt_mvarmslm;					// �ΰ��� ��� �� �ִ� ��ȿ���� ���Ź���
	int								vvoopt_cvr;					// CVR���࿩��(1: ����, 0: ���� ����)

	int								var_reser1;						// ���� ����1
	int								var_reser2;						// ���� ����2
	int								var_reser3;						// ���� ����3
} VVOOPT_DYN_UIN;
#define								VVOOPT_DYN_UIN_SIZE						sizeof( VVOOPT_DYN_UIN )

//////////////������ �߰� 
typedef	struct	_TERMINAL
{
	wchar_t	terminal_id[64];
	wchar_t	terminal_ceqfk[64];
	wchar_t	terminal_cnfk[64];
	int		terminal_ceqtype;
	wchar_t	terminal_original_eqcfk[64];
	wchar_t	terminal_change_eqcfk[64];
	wchar_t	terminal_nm[64];
	int		terminal_nametype;
} TERMINAL;
#define								TERMINAL_SIZE						sizeof( TERMINAL )

typedef	struct	_BI_VALUE
{
	wchar_t	BI_CEQ_MRFK[ 32 ];
	int		BI_MASTER_CODE_FK;
	int		BI_VALUE_DATE;
} BI_VALUE;
#define								BI_VALUE_SIZE						sizeof( BI_VALUE )


typedef	struct	_NAME_TYPE
{
	wchar_t	NAME_MRID[64];
	int		NAME_TYPE_DATE;
	wchar_t	NAME_NAME[128];
	wchar_t	ALIAS_NAME[128];
} NAME_TYPE;
#define								NAME_TYPE_SIZE						sizeof( NAME_TYPE )


typedef struct _IDENTIFIEDOBJECT
{
	wchar_t		IDTER_MRID[64];
	int			IDTER_NAME_TYPE_FK;
	wchar_t		IDTER_NAME[64];
	wchar_t		IDTER_ALIAS_NAME[64];
	wchar_t		IDTER_TERMINAL_ID[64];
	wchar_t		IDTER_CEQ_MRFK[64];
	wchar_t		IDTER_CONNECTIVITYNODE_FK[64];

} IDENTIFIEDOBJECT;
#define								IDENTIFIEDOBJECT_SIZE						sizeof( IDENTIFIEDOBJECT )

typedef struct _conductingequipment
{
	wchar_t		MRID[64];
	int			CEQ_TYPE_FK;
	wchar_t		ORIGINAL_EQC_MRFK[64];
	wchar_t		CHANGE_EQC_MRFK[64];
	int			SEQ;

} conductingequipment;
#define								conductingequipment_SIZE						sizeof( conductingequipment )

typedef struct _LINESEGMENT_TYPE
{
	int			LINESEGMENT_TYPE_ID;
	int			OVERHEAD_CABLE;
	wchar_t		PHASE_LINE_TYPE[64];
	wchar_t		NEUTRAL_LINE_TYPE[64];
	double		POSITIVE_R;
	double		POSITIVE_X_1P;
	double		POSITIVE_X;
	double		ZERO_R;
	double		ZERO_X;
	double		THERMAL_LIMIT;
	double		R_KM;
	double		X_KM;

} LINESEGMENT_TYPE;
#define								LINESEGMENT_TYPE_SIZE						sizeof( LINESEGMENT_TYPE )

//Table : INNERPOLE_STA, Type : Online
typedef struct _LINESEGMENT_DETAIL
{
	int								LINESEGMENT_DETAIL_ID;
	wchar_t							LINE_MRID[64];
	int								HVL_SEQ;
	int								HVL_SYSID;
	int								HVL_DIRECTION;
	double							F_LONGITUDE;
	double							F_LATITUDE;
	double							B_LONGITUDE;
	double							B_LATITUDE;
} LINESEGMENT_DETAIL;
#define								LINESEGMENT_DETAIL_SIZE					sizeof( LINESEGMENT_DETAIL )

//Table : INNERPOLE_STA, Type : Online
typedef struct _GLINESEGMENT
{
	int								GLINESEGMENT_ID;
	wchar_t							GLINESEGMENT_MRID[64];
	int								GLINESEGMENT_TYPE;
	double							F_LONGITUDE[7100];
	double							F_LATITUDE[7100];
	double							F_x;
	double							F_y;
	int								INNERPOLE_II_LNSEC;
	double							LENGTH;
} GLINESEGMENT;
#define								GLINESEGMENT_SIZE					sizeof( GLINESEGMENT )

typedef struct _LINESYSID
{
	wchar_t							LINESYSID_ID[64];
	wchar_t							LINESYSID_COMNO[64];
	wchar_t							LINESYSID_POLENO[64];
	int								LINESYSID_CUSTOMER;
} LINESYSID;
#define								LINESYSID_SIZE					sizeof( LINESYSID )

//20210126
typedef struct _HVCUS_STA
{
	int								HVCUS_STA_ID;
	wchar_t							HVCUS_NM[64];
	wchar_t							HVCUS_CEQID[64];
	int								HVCUS_II_GND;
	int								HVCUS_SI_GND;
	double							HVCUS_CON_KVA;
	double							HVCUS_ITR_KVA;
	double							HVCUS_ITR_PZ;
	int								HVCUS_II_PRDE;
	int								HVCUS_II_IJ;

} HVCUS_STA;
#define								HVCUS_STA_SIZE					sizeof( HVCUS_STA )


////////////////
typedef struct _PRDE_STA
{
	wchar_t							PRDE_STA_NM[64];

	int								PRDE_OCRF_II_TCCSET	  ;
	int								PRDE_OCRD_II_TCCSET	  ;
	double							PRDE_OCR_Pickup_C	  ;
	double							PRDE_OCR_IIC		  ;
	int								PRDE_OCGRF_II_TCCSET  ;
	int								PRDE_OCGRD_II_TCCSET  ;
	double							PRDE_OCGR_Pickup_C	  ;
	double							PRDE_OCGR_IIC		  ;
	int								PRDE_TYPE			  ;
	int								PRDE_SET_GTYPE		  ;
	int								PRDE_OCR_NOF		  ;
	int								PRDE_OCR_NOD		  ;
	int								PRDE_OCGR_NOF		  ;
	int								PRDE_OCGR_NOD		  ;
	double							PRDE_OCRF_TMS		  ;
	double							PRDE_OCRF_TAS		  ;
	double							PRDE_OCRF_MRT		  ;
	double							PRDE_OCRD_TMS		  ;
	double							PRDE_OCRD_TAS		  ;
	double							PRDE_OCRD_MRT		  ;
	double							PRDE_OCGRF_TMS		  ;
	double							PRDE_OCGRF_TAS		  ;
	double							PRDE_OCGRF_MRT		  ;
	double							PRDE_OCGRD_TMS		  ;
	double							PRDE_OCGRD_TAS		  ;
	double							PRDE_OCGRD_MRT		  ;
	int								PRDE_OCR_CTR		  ;
	int								PRDE_OCGR_CTR		  ;
	double							PRDE_MX_LD_C_PHA	  ;

} PRDE_STA;
#define								PRDE_STA_SIZE					sizeof( PRDE_STA )
//20220530
typedef struct _HDOF_STA
{
	wchar_t							HDOF_NM[64];
	int								HDOF_CODE;
	int								HDOF_HI_CENTER;
	int								CENTER_HI_BOF;

} HDOF_STA;
#define								HDOF_STA_SIZE					sizeof( HDOF_STA )



//////////////////////////////////////////////////////////////////////////
#endif




