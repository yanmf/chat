#include "manager.h"


DEFINE_SINGLETON(manager);

manager::manager()
{
	m_server = nullptr;
	redis_poll = nullptr;
}

void manager::init()
{
	m_server = new server();
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
}

void manager::start()
{
	m_server->start();
}
