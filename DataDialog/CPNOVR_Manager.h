#pragma once
class  AFX_EXT_CLASS CPNOVR_Manager
{
public:
	CPNOVR_Manager(void);
	~CPNOVR_Manager(void);

private:
	static CPNOVR_Manager* _instance;// �̱���(Singleton) - �޸𸮿� �ѹ��� ���
public:
	static CPNOVR_Manager* Instance();
};

