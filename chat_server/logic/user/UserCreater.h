#ifndef _USER_CREATER_H
#define _USER_CREATER_H

#include "../../data/UserCreate.pb.h"
#include "../../tcp/TCPCmdHandler.h"
#include "../../tcp/HandlerCmd.h"
#include "../../define.h"
#include "../../logic/global.h"
#include "../../manager.h"

class UserCreater:public IHandlerCmd
{
	enum REPLY_ERROR
	{
		SUCCESS = 0,//成功
		REPLY_NAME_LEN_ERR	= 1,//名字长度不够
		REPLY_PWD_LEN_ERR = 2,//密码长度不够
		REPLY_NAME_BE_ERR = 3,//已存在
		REPLY_SYS_ERR = 4,//系统错误
	};
	enum CREATECMDS
	{
		CREATE      =       0x01,//注册用户
	};
	public:
	UserCreater();
	virtual ~UserCreater();
	private:
	bool HandlerCmd(client*, char*,int,int);
	bool IsCreater(client*, const string user_name, const string user_pwd,int& err_code);
	bool CreateHandlerCmd(client*, char*,int,int);

	private:
	MSGCMDS _nID;

};

#endif
