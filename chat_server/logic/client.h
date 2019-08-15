#ifndef _CLIENT
#define _CLIENT

#include "../data/ClientData.pb.h"
#include "../tcp/TCPPacket.h"
#include <string>
using namespace std;
using namespace Data;

class TCPPacket;

class client
{
	public:
		int fd;
		client(int fd);
		virtual ~client();
		TCPPacket* tcp_packet;

	public:
		void setUserName(string name)
		{
			user_name = name;
		}
		void setUserPwd(string pwd)
		{
			user_pwd = pwd;
		}
		void r_getUserHash(const string& user_name,string& hash)
		{
			hash = user_name + "_HASH";
		}
		void r_getUserPwd(string& key)
		{
			key = "user_pwd";
		}
	private:
		ClientData* client_data;
		string user_name;
		string user_pwd;
};


#endif
