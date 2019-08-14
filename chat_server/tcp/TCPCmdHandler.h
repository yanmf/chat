#ifndef _TCP_CMD_HANDLER
#define _TCP_CMD_HANDLER

#include <iostream>
#include <map>
#include "../logic/client.h"
#include "../define.h"
#include "HandlerCmd.h"

using namespace std;
enum MSGCMDS
{
	CMD_LOGIN		=		0x100,//登录
	CMD_CREATE		=		0x200,//注册
	CMD_CHAT		=		0x300,//聊天
	CMD_FRIEND		=		0x400,//好友
};

class TcpCmdHandler
{
	DECLARE_SINGLETON(TcpCmdHandler);
	public:
		TcpCmdHandler();
		virtual ~TcpCmdHandler();
		void AddMsgListener(MSGCMDS, IHandlerCmd*);
		bool HandlerCmdMsg(void *,char*,int,int);
	
	private:
		map<MSGCMDS, IHandlerCmd*> _HandlerCmdMap;
		IHandlerCmd* FindHandlerCmd(MSGCMDS);
};

#define TCP_CMD_HANDLER TcpCmdHandler::instance()

#endif
