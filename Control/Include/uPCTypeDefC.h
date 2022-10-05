#ifndef __UPC_TYPE_DEF_C_H__
#define __UPC_TYPE_DEF_C_H__

#include <string>
#include <vector>
using namespace std;

typedef enum _eServiceNo
{
	NO_NAMING_SERVICE		= 0x00,
	NO_MANAGER_SERVICE		= 0x01,
	NO_DATATYPE_SERVICE		= 0x02,
	NO_DATAPOINT_SERVICE	= 0x03,
	NO_MESSAGE_SERVICE		= 0x04,
	NO_EVENT_SERVICE		= 0x05,
	NO_CONTROL_SERVICE		= 0x06,
	NO_ACM_SERVICE			= 0x07,	
	NO_FILETRANS_SERVICE	= 0x08,
	NO_ALL_SERVICE			= 0x09,
}eServiceNo;

typedef vector<string> uPCPointNames;

class PowerCubeServerList{
public:
	PowerCubeServerList():nCount(0)
	{

	}
	int		nCount;
	char	pList[16][32];
	//const char*	pList[16];
};

#define TYPE_NAME_SZ						(64)

#endif