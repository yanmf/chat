
#ifndef _TCP_OUT_PACKET_H
#define _TCP_OUT_PACKET_H

#include"TCPPacket.h"

class TcpOutPacket
{
	public:
		TcpOutPacket(int nID, int cmd, const char* data);
		virtual ~TcpOutPacket();
		
		char* getPacketBytes();
	private:
		void finalData();
		
	public:
		int _packet_size;

	private:
		char* _packet_data;
		int _n_id;
};

#endif
