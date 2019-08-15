
#include"redis.h"

#define SETSTRING(key, value) \
	stringstream ss;\
	ss << "SET " << key << " " << value;\
	string s;\
	getline(ss, s);\
	command(s);

Redis::Redis(string ip,int port,string pwd)
{
	m_ip = ip;
	m_port = port;
	m_pwd = pwd;
	_context = nullptr;
	_reply = nullptr;
}

Redis::~Redis(){}

void Redis::Connect()
{
	_context = ::redisConnect(m_ip.c_str(), m_port);
	cout <<m_ip << "-" << m_port << endl;
	if(_context && _context->err)
	{
		cout << "connect redis error" << endl;
		exit(EXIT_FAILURE);    
	}
	command("AUTH "+m_pwd);
}

void Redis::disConnect()
{
	::redisFree(_context);
	cout << "redis disConnect success" << endl;
}

bool Redis::command(const string& data)
{
	freeReply();
	_reply = (redisReply*)::redisCommand(_context, data.c_str());
	if(!isError())
	{
		return true;
		/*
		if (!(_reply->type == REDIS_REPLY_STATUS && strcasecmp(_reply->str,"OK") == 0))
		{
		}
		*/
	}
	return false;
}

void Redis::setString(const string & key, const string & value)
{
	SETSTRING(key, value);
}

void Redis::setString(const string & key, const int & value)
{
	SETSTRING(key, value);
}

void Redis::setString(const string & key, const float & value)
{
	SETSTRING(key, value);
}

void Redis::getString(const string & key)
{
	freeReply();
	_reply = (redisReply*)::redisCommand(_context, "GET %s", key.c_str());
}

void Redis::getString(const string & key, string & value)
{
	getString(key);
	if(!isError() && _reply->type == REDIS_REPLY_STRING)
	{
		value = _reply->str;
	}
}

void Redis::getString(const string & key, int & value)
{
	getString(key);
	if(!isError() && _reply->type == REDIS_REPLY_STRING)
	{
		value = ::atoi(_reply->str);
	}
}

void Redis::getString(const string & key, float & value)
{
	getString(key);
	if(!isError() && _reply->type == REDIS_REPLY_STRING)
	{
		value = ::atof(_reply->str);
	}
}

void Redis::freeReply()
{
	if(_reply)
	{
		::freeReplyObject(_reply);
		_reply = NULL;
	}
}

bool Redis::isError()
{
	if(NULL == _reply)
	{
		freeReply();
		disConnect();
		Connect();
		return true;
	}
	return false;
}

bool Redis::isExists(const string& hash, const string& key)
{
	stringstream ss;
	ss << "HEXISTS " << hash << " "<< key;
	string com;
	getline(ss, com);

	if(!command(com))
	{
		return false;
	}
	if(!isError() && _reply->type == REDIS_REPLY_INTEGER)
	{
		int value = (int)(_reply->integer);
		if(value)
		{
			return true;
		}
	}
	return false;
}

void Redis::hsetString(const string& hash, const string& key, const string& value)
{
	stringstream ss;
	ss << "HSET " << hash << " "<< key <<" "<<value;
	string com;
	getline(ss, com);

	command(com);
}
/*
int main()
{
	Redis* redis = new Redis("127.0.0.1", 4400, "ymf062900");
	redis->Connect();

	string str;
	redis->getString("aaa", str);
	cout<<"get aaa "<<str<<endl;
	delete redis;
	redis = nullptr;
	return 0;
}
*/
