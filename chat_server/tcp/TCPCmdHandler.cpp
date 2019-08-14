#include "TCPCmdHandler.h"

DEFINE_SINGLETON(TcpCmdHandler);

TcpCmdHandler::TcpCmdHandler()
{

}

TcpCmdHandler::~TcpCmdHandler()
{

}

void TcpCmdHandler::AddMsgListener(MSGCMDS cmd, IHandlerCmd* handler_cmd)
{
	_HandlerCmdMap[cmd] = handler_cmd;
}

IHandlerCmd *TcpCmdHandler::FindHandlerCmd(MSGCMDS cmd)
{
	    //查找元素
	map<MSGCMDS, IHandlerCmd*>::iterator iter1;
	iter1 = _HandlerCmdMap.find(cmd);
	if(iter1 == _HandlerCmdMap.end())
	{
		return nullptr;
	}
	if(iter1->second)
	{
		return iter1->second;
	}
	return nullptr;
}

bool TcpCmdHandler::HandlerCmdMsg(void*user, char* buf, int count, int cmd)
{
	client* c = (client*)user;
	MSGCMDS type = MSGCMDS(cmd & 0xFF00);
	IHandlerCmd* handlerCmd = FindHandlerCmd(type);
	if(!handlerCmd)
	{
		std::cout<<"find HandlerCmd error cmd:"<<type<<endl;
		return false;
	}
	return handlerCmd->HandlerCmd(c,buf,count,cmd & 0x00FF);
}
