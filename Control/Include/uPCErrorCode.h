#ifndef __UPC_ERRORCODE_H__
#define __UPC_ERRORCODE_H__

const int UPC_OK = 0;						// ����ó��
const int UPC_ERROR = -1;					// ����
const int UPC_POINT_NOT_FOUND = -2;			// ����Ʈ �̸� ã�� ����
const int UPC_DATA_OVERFLOW = -3;			// ������ �����÷ο�
const int UPC_DATA_UNDERFLOW = -4;			// ������ ����÷ο�
const int UPC_POINT_BIND_ERROR = -5;			// ����Ʈ �̸� ���ε� ����
const int UPC_POINT_EXIST = -6;				// ����Ʈ�� �̹� ����
const int UPC_DATA_IS_NULL = -7;				// �����Ͱ� NULL
const int UPC_SERVICE_NOT_FOUND = -8;		// ���� ���ε� �̸� ã�� ����(****)
const int UPC_CORBA_EXCEPTION = -9;			// �ڹ� ���� �߻�
const int UPC_TIME_OUT = -10;				// Ÿ�� �ƿ� �߻�
const int UPC_NAMING_INIT_FAIL = -11;		// ���̹� ���� INIT ���� Ÿ�� �ƿ� �߻�(***)
const int UPC_NOT_ACTIVE = -12;				// ��Ƽ�� ������ �ƴ�(����ġ)
const int UPC_NOT_MODE_SET = -13	;			// ���� ��� ������ �ȵ�
const int UPC_NOT_ONLINE = -14;				// ��Ƽ�������� �¶��� ���°� �ƴ�
const int UPC_POINT_UNBOUND_ERROR = -15;		// ����Ʈ �̸� ��ٿ�� ����
const int UPC_NAMING_COMM_FAIL = -16;		// ���̹� ���񽺰� ������� ����
const int UPC_NAMING_TRANSIENT = -17;		// ���̹� ���񽺰� �������� ����
const int UPC_SERVICE_COMM_FAIL = -18;		// �ش� ���񽺰� ��������
const int UPC_FILE_NOT_FOUND = -19;			// ������ ����
const int UPC_ORB_INVALID_NAME = -20;		// ORB �̸��� �߸���
const int UPC_LIB_TRIAL_FAIL = -21;			// Ʈ���̾� �������� ������ 2014���� ������ ����� ����
const int UPC_LIB_SERIAL_FAIL = -22;		// SERIAL NUMBER FAIL
const int UPC_LIB_NOT_INIT = -23;			// SERIAL NUMBER FAIL
const int UPC_CUBE_ORB_NOT_FOUND = -24;		// ORB������ ã�� ����(Ŭ���̾�Ʈ�ʿ���)
const int UPC_CONFIG_LOAD_FAIL = -25;		// ȯ�漳�� ���� �ε� ����
const int UPC_NAMING_NOT_CONNECT = -26;		// ���̹� ���� ���� �ȵ�
const int UPC_PARAM_ORB_TYPE_ERROR = -27	;	// �Լ� ȣ��� ORB_TYPE�� �߸���(ORB_TYPE�� 0, 1, 2�̾�� ��)



#define WRONGSTUB		2
#define RESTUBFAIL		30001

#endif