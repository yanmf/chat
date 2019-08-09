#ifndef _CLIENT
#define _CLIENT

#include "../data/ClientData.pb.h"
#include "../tcp/TCPPacket.h"
using namespace Data;

class TCPPacket;

class client
{
	public:
		int fd;
		client(int fd);
		virtual ~client();
		TCPPacket* tcp_packet;

	private:
		ClientData* client_data;
};


#endif
