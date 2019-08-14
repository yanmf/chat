#include"UserCreater.h"

UserCreater::UserCreater()
{
	_nID = MSGCMDS::CMD_CREATE;
	TCP_CMD_HANDLER->AddMsgListener(_nID, this);
}

UserCreater::~UserCreater()
{
}

bool UserCreater::HandlerCmd(client* c,char* data,int size, int cmd)
{
	Data::UserCreate userCreate;
	userCreate.ParseFromString(data);
	const string user_name = userCreate.user_name();
	const string user_pwd = userCreate.user_pwd();
	//判断名字跟密码合法性
	//判断是否已经注册

	cout<<"user_name:"<<user_name<<" user_pwd"<<user_pwd<<endl;

	Data::UserCreateRep reply;
	reply.set_err_code(1);
	reply.set_user_name(user_name);
	reply.set_user_pwd(user_pwd);

	string str;
	reply.SerializeToString(&str);

	GLOBAL->SendData(c->fd, _nID, cmd, str);
	
	return true;
}	
