#include"UserCreater.h"


UserCreater::UserCreater()
{
	_nID = MSGCMDS::CMD_CREATE;
	TCP_CMD_HANDLER->AddMsgListener(_nID, this);
}

UserCreater::~UserCreater()
{
}

bool UserCreater::CreateHandlerCmd(client* c, char* data, int size, int cmd)
{
	Data::UserCreate userCreate;
	userCreate.ParseFromString(data);
	const string user_name = userCreate.user_name();
	const string user_pwd = userCreate.user_pwd();
	//判断名字跟密码合法性
	//判断是否已经注册

	int err_code;
	if(IsCreater(c, user_name, user_pwd, err_code))
	{
		cout<<"creater success"<<endl;
	}
	cout<<"user_name:"<<user_name<<" user_pwd"<<user_pwd<<endl;
	c->setUserName(user_name);
	c->setUserPwd(user_pwd);

	Data::UserCreateRep reply;
	reply.set_err_code(err_code);
	reply.set_user_name(user_name);
	reply.set_user_pwd(user_pwd);

	string str;
	reply.SerializeToString(&str);

	GLOBAL->SendData(c->fd, _nID, cmd, str);
	
	return true;
}

bool UserCreater::HandlerCmd(client* c,char* data,int size, int cmd)
{
	switch(cmd)
	{
		case CREATECMDS::CREATE:
			return CreateHandlerCmd(c,data,size,cmd);
		default:
			cout<<"未注册的指令 nID:"<<_nID<<" cmd:"<<cmd<<endl;
			break;
	}
	return false;
}	

bool UserCreater::IsCreater(client* c, const string user_name, const string user_pwd, int &err_code)
{
	err_code = REPLY_ERROR::SUCCESS;
	if(user_name.length()<3)
	{
		err_code = REPLY_ERROR::REPLY_NAME_LEN_ERR;
		return false;
	}
	if(user_pwd.length()<6)
	{
		err_code = REPLY_ERROR::REPLY_PWD_LEN_ERR;
		return false;
	}

	Redis* redis = REDIS_MANAGER->pop();
	if(!redis)
	{
		err_code = REPLY_ERROR::REPLY_SYS_ERR;
		return false;
	}
	string hash;
	string pwd_key;
	
	c->r_getUserHash(user_name, hash);
	c->r_getUserPwd(pwd_key);

	if (redis->isExists(hash, pwd_key))
	{
		err_code = REPLY_ERROR::REPLY_NAME_BE_ERR;
		return false;
	}

	redis->hsetString(hash, pwd_key, user_pwd);

	REDIS_MANAGER->push(redis);
	return true;
}

