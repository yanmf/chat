#ifndef _REDIS_H
#define _REDIS_H

#include <hiredis/hiredis.h>
#include <string>
#include <strings.h>
#include <iostream>
#include <sstream>

using namespace std;

class Redis
{
	public:
		Redis(string ip, int port, string pwd);
		virtual ~Redis();
		
		void Connect();
		void disConnect();
		void setString(const string & key, const string & value);
		void setString(const string & key, const int & value);
		void setString(const string & key, const float & value);
		
		void getString(const string & key, string & value);
		void getString(const string & key, int & value);
		void getString(const string & key, float & value);


	public:
		/*
		HEXISTS hash field
		判断 哈希表中是否存在hash field字段
		*/
		bool isExists(const string& hash, const string& key);
		/*
		 * HSET hash field value
		 * 添加哈希表键值对
		 * 已存在修改value
		 * */
		void hsetString(const string& hash, const string& key,const string& value);


	private:
		void getString(const string & key);
	private:
		void freeReply();
		bool isError();
		bool command(const string& data);
	private:
		redisContext * _context;
		redisReply * _reply;

		string m_ip;
		string m_pwd;
		int m_port;
};

#endif

