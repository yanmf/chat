
#ifndef _GLOBAL_H
#define _GLOBAL_H

#include<string>
#include "../tcp/TCPOutPacket.h"
#include "../server.h"

class Global
{
	DECLARE_SINGLETON(Global);

	public:
		TcpOutPacket* MakeTCPOutPacket(int nID, int cmd, string data);//构造消息包

		bool SendData(int fd, TcpOutPacket* tcpOutPacket);
		bool SendData(int fd, int nID,int cmd, string data);

};

#define GLOBAL Global::instance()

#endif
