#include "manager.h"


DEFINE_SINGLETON(manager);

manager::manager()
{
	m_server = nullptr;
	redis_poll = nullptr;
	user_creater = nullptr;
}

void manager::init()
{
	m_server = new server();
	redis_poll = new RedisPoll();
	user_creater = new UserCreater();
}

void manager::close()
{
	if(m_server)
	{
		delete m_server;
		m_server = nullptr;
	}
	if(redis_poll)
	{
		delete redis_poll;
		redis_poll = nullptr;
	}
	if(user_creater)
	{
		delete user_creater;
		user_creater=nullptr;
	}
}

void manager::start()
{
	m_server->start();
}
