#ifndef __UPC_ERRORCODE_H__
#define __UPC_ERRORCODE_H__

const int UPC_OK = 0;						// 정상처리
const int UPC_ERROR = -1;					// 에러
const int UPC_POINT_NOT_FOUND = -2;			// 포인트 이름 찾기 실패
const int UPC_DATA_OVERFLOW = -3;			// 데이터 오버플로우
const int UPC_DATA_UNDERFLOW = -4;			// 데이터 언더플로우
const int UPC_POINT_BIND_ERROR = -5;			// 포인트 이름 바인드 에러
const int UPC_POINT_EXIST = -6;				// 포인트가 이미 존재
const int UPC_DATA_IS_NULL = -7;				// 데이터가 NULL
const int UPC_SERVICE_NOT_FOUND = -8;		// 서비스 바인드 이름 찾기 실패(****)
const int UPC_CORBA_EXCEPTION = -9;			// 코바 예외 발생
const int UPC_TIME_OUT = -10;				// 타임 아웃 발생
const int UPC_NAMING_INIT_FAIL = -11;		// 네이밍 서비스 INIT 실패 타임 아웃 발생(***)
const int UPC_NOT_ACTIVE = -12;				// 액티브 서버가 아님(스위치)
const int UPC_NOT_MODE_SET = -13	;			// 서비스 모드 설정이 안됨
const int UPC_NOT_ONLINE = -14;				// 액티브이지만 온라인 상태가 아님
const int UPC_POINT_UNBOUND_ERROR = -15;		// 포인트 이름 언바운드 에러
const int UPC_NAMING_COMM_FAIL = -16;		// 네이밍 서비스가 연결되지 않음
const int UPC_NAMING_TRANSIENT = -17;		// 네이밍 서비스가 켜져있지 않음
const int UPC_SERVICE_COMM_FAIL = -18;		// 해당 서비스가 꺼져있음
const int UPC_FILE_NOT_FOUND = -19;			// 파일이 없음
const int UPC_ORB_INVALID_NAME = -20;		// ORB 이름이 잘못됨
const int UPC_LIB_TRIAL_FAIL = -21;			// 트라이얼 버젼으로 구동시 2014년이 지나면 생기는 에러
const int UPC_LIB_SERIAL_FAIL = -22;		// SERIAL NUMBER FAIL
const int UPC_LIB_NOT_INIT = -23;			// SERIAL NUMBER FAIL
const int UPC_CUBE_ORB_NOT_FOUND = -24;		// ORB서버를 찾지 못함(클라이언트쪽에서)
const int UPC_CONFIG_LOAD_FAIL = -25;		// 환경설정 파일 로딩 실패
const int UPC_NAMING_NOT_CONNECT = -26;		// 네이밍 서비스 연결 안됨
const int UPC_PARAM_ORB_TYPE_ERROR = -27	;	// 함수 호출시 ORB_TYPE을 잘못줌(ORB_TYPE은 0, 1, 2이어야 함)



#define WRONGSTUB		2
#define RESTUBFAIL		30001

#endif