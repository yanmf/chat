#include "TCPCmdHandler.h"

DEFINE_SINGLETON(TcpCmdHandler);

TcpCmdHandler::TcpCmdHandler()
{

}

TcpCmdHandler::~TcpCmdHandler()
{

}

void TcpCmdHandler::AddMsgListener(MSGCMDS cmd, HanderCmd hander_cmd)
{
	_HanderCmdMap[cmd] = hander_cmd;
}

HanderCmd TcpCmdHandler::FindHanderCmd(MSGCMDS cmd)
{
	    //查找元素
	map<MSGCMDS, HanderCmd>::iterator iter1;
	iter1 = _HanderCmdMap.find(cmd);
	if(iter1 == _HanderCmdMap.end())
	{
		return nullptr;
	}
	if(iter1->second)
	{
		return iter1->second;
	}
	return nullptr;
}

bool TcpCmdHandler::HanderCmdMsg(void*user, char* buf, int count, int cmd)
{
	client* c = (client*)user;
	MSGCMDS type = MSGCMDS(cmd & 0xFF00);
	HanderCmd handerCmd = FindHanderCmd(type);
	if(!handerCmd)
	{
		std::cout<<"find HanderCmd error cmd:"<<type<<endl;
		return false;
	}
	return handerCmd(c,buf,count,cmd);
}
