#ifndef _TCPPACKET
#define _TCPPACKET

#define MAX_TCP_IN_SIZE  65535
#define TCP_SIZE 4
#define TCP_CMD_SIZE 4
#define TCP_HEADER_SIZE TCP_SIZE + TCP_CMD_SIZE


#define GET_COPY_SIZE(count) count>(TCP_HEADER_SIZE - header_size)?(TCP_HEADER_SIZE - header_size):count 

#define GET_DATA_COPY_SIZE(count) count>(packet_size - data_size)?(packet_size - data_size):count 


#include <stdio.h>
#include <string.h>
#include <iostream>

#include "TCPCmdHandler.h"
using namespace std;

class TCPPacket
{
	public:
		TCPPacket();
		virtual ~TCPPacket();
		bool WriteData(void* c, char* buffer, int count);
	private:
		int msg_cmd;//协议号
		int packet_size;//包的大小
		char* data;//协议数据
		int header_size;//已经收到的包头大小
		int data_size;//已经收到的包体大小
		char* header_data;//收到的包头数据
		bool is_waiting_data;//是否在收包头
};


#endif
