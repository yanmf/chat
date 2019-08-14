#include"TCPOutPacket.h"

TcpOutPacket::TcpOutPacket(int nId, int cmd, const char* data)
{
	_n_id = nId | cmd;
	_packet_size = TCP_HEADER_SIZE;
	int data_size=0;
	if (data)
	{
		data_size = strlen(data);
		_packet_size += data_size;
	}
	_packet_data = new char[_packet_size];

	if (data_size>0)
	{
		memcpy(&_packet_data[TCP_HEADER_SIZE], data, data_size);
	}
	finalData();
}

TcpOutPacket::~TcpOutPacket()
{
	delete[] _packet_data;
	_packet_data = nullptr;
}

void TcpOutPacket::finalData()
{
	memcpy(_packet_data, &_packet_size, sizeof(_packet_size));
	memcpy(&_packet_data[TCP_CMD_SIZE], &_n_id, sizeof(_n_id));
}
char* TcpOutPacket::getPacketBytes()
{
	return _packet_data;
}
