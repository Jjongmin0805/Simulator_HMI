#pragma once

class CPWThread;
typedef								vector<CPWThread*>						VECTHREAD;

class CPDSETComm_CNT
{
public:
	CPDSETComm_CNT(void);
	~CPDSETComm_CNT(void);

	bool																	Begin();					// ��� ���� �Լ�
	CPLocker*																GetLockSend();
	CPLocker*																GetLockRecv();
	socket_t*																GetCommSocket();			// ����� �۽� zmq socket�� ��� �Լ�
	bool																	IsBegin();

	bool																	SEND_CommData( const char* szMessage );				// �۽� �����͸� ó���ϴ� �Լ� 1
	bool																	SEND_CommData( unsigned int unBuffSize, const char* pBuff );		// �۽� �����͸� ó���ϴ� �Լ� 1
	void																	SendCloseComm();

protected :
	void																	CloseThread();									// �����带 ���� �Ǵ� �����ϴ� �Լ�
	void																	RunThread();									// �����带 �����ϴ� �Լ�
	void																	CloseComm();									// ��� Socket ���� �Լ�

	void																	SendRegistComm();

	void																	Thread_Run();									// �����带 �����ϴ� �Լ�
	static UINT WINAPI														SENDThread_Process( LPVOID pParam );			// �۽� ������ �Լ�
	static UINT WINAPI														RECVThread_Process( LPVOID pParam );			// ���� ������ �Լ�

	bool																	RECV_CommData( socket_t* pCommSocket );			// ���� �������� header�� �ؼ��ϱ� ���� �Լ�
	bool																	SEND_CommAck( short snSeqNo );					// �۽� �����͸� ó���ϴ� �Լ� 1
	bool																	CheckSendTimeout( short snSeqNo );				// �۽� ���� ó���� ���� �ʵ��� Ÿ�Ӿƿ��� �����ϴ� �Լ�
	void																	GetSeqNo();										// �۽�. ���ſ� ���Ǵ� seq number�� �ο��ϴ� �Լ�

protected : 
	short							m_snSendSeqNo;							// �۽ſ� �ʿ��� seq number�� �ο��ϱ� ���� ����
	context_t						p_context;								// zmq���� ����ϰ� context ����
	socket_t						*m_pCOMMSOCK;							// �۽Ű� ���� �������� ����ϰ��� �ϴ� zmq socket ����
	VECTHREAD						m_vecCommThreads;

	bool							m_bBegin;
	CPLocker						*m_pLock_Send, *m_pLock_Recv;
};

