#ifndef _REDIS_POLL_H
#define _REDIS_POLL_H

#include <queue>
#include <string>
#include "redis.h"

class RedisPoll
{
	private:
		queue<Redis*> pool;
	public:
		RedisPoll();
		virtual ~RedisPoll();
		void init(const int& count, const string& ip, const int& port, const string& pwd);
		Redis* pop();
		void push(Redis* conn);
};


#endif
