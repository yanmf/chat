#include "client.h"

client::client(int fd)
{
	client_data = new ClientData();
	tcp_packet = new TCPPacket();
	this->fd = fd;
}

client::~client()
{
	delete client_data;
	delete tcp_packet;
}
