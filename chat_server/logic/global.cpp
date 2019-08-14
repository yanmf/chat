#include"global.h"

DEFINE_SINGLETON(Global);


TcpOutPacket* Global::MakeTCPOutPacket(int nID, int cmd, string data)
{
	return new TcpOutPacket(nID,cmd,data.c_str());
}

bool Global::SendData(int fd, TcpOutPacket* tcpOutPacket)
{
	if(send(fd, tcpOutPacket->getPacketBytes(), tcpOutPacket->_packet_size, 0)<0)
	{
		err_log("SendData Error");
		return false;
	}
	return true;
}

bool Global::SendData(int fd, int nID, int cmd, string data)
{
	return SendData(fd, MakeTCPOutPacket(nID, cmd, data));
}

