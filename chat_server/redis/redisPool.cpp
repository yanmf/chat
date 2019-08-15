#include"redisPool.h"

RedisPoll::RedisPoll()
{}

RedisPoll::~RedisPoll()
{
	do
	{
		Redis *redis = pop();
		if(!redis)
		{
			break;
		}
		delete redis;
		redis = nullptr;
	}
	while(1);
}

void RedisPoll::init(const int& count, const string& ip, const int& port, const string& pwd)
{
	for(int i=0;i<count;i++)
	{
		Redis *redis = new Redis(ip,port,pwd);
		redis->Connect();
		pool.push(redis);
	}
}

Redis* RedisPoll::pop()
{
	if(pool.size() <= 0)
	{
		return nullptr;
	}
	Redis* redis = pool.front();
	pool.pop();

	return redis;
}

void RedisPoll::push(Redis* conn)
{
	if (conn)
	{
		pool.push(conn);
	}
}

int RedisPoll::size()
{
	return pool.size();
}
