
#ifndef _MANAGER_H
#define _MANAGER_H

#include "logic/user/UserCreater.h"
#include "define.h"
#include "server.h"
#include "redis/redisPool.h"

class server;
class UserCreater;
class manager
{
	DECLARE_SINGLETON(manager);

	manager();
	void close();
	void init();
	void start();

	server* m_server;
	RedisPoll* redis_poll;
	UserCreater* user_creater;
};


#define MANAGER manager::instance()
#define SERVER_MANAGER manager::instance()->m_server
#define REDIS_MANAGER manager::instance()->redis_poll

#endif

