#include "pch.h"
#include "CPNOVR_Manager.h"


CPNOVR_Manager *CPNOVR_Manager::_instance = NULL;

CPNOVR_Manager::CPNOVR_Manager(void)
{
	
}

CPNOVR_Manager::~CPNOVR_Manager(void)
{
	
	delete thePNO_Ctrlmng;
	delete thePNO_UTILmng;
}

CPNOVR_Manager* CPNOVR_Manager::Instance()
{
	if (_instance == 0)
	{
		_instance = new CPNOVR_Manager();
	}
	return _instance;
}