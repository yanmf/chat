#ifndef _USER_CREATER_H
#define _USER_CREATER_H

#include "../../data/UserCreate.pb.h"
#include "../../tcp/TCPCmdHandler.h"
#include "../../tcp/HandlerCmd.h"
#include "../../define.h"
#include "../../logic/global.h"

class UserCreater:public IHandlerCmd
{
	public:
		UserCreater();
		virtual ~UserCreater();
	private:
		bool HandlerCmd(client*, char*,int,int);
	private:
		MSGCMDS _nID;

};

#endif
