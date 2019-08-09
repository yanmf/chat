#include "TCPPacket.h"

TCPPacket::TCPPacket()
{
	data = new char[MAX_TCP_IN_SIZE]();
	header_data = new char[TCP_HEADER_SIZE]();
	is_waiting_data = false;
	header_size = 0;
}

TCPPacket:: ~TCPPacket()
{
	delete[] data;
	data = nullptr;
}


bool TCPPacket::WriteData(void*c, char* buffer, int count)
{
	if (!is_waiting_data)
	{
		//第一次收到数据或者包头还没有收到
		int copySize = GET_COPY_SIZE(count);
		
		memcpy(&header_data[header_size], buffer, copySize);
		header_size += copySize;
		if (TCP_HEADER_SIZE > header_size)
		{
			return true;//继续等待
		}
		memcpy(&packet_size, header_data, TCP_SIZE);
		memcpy(&msg_cmd, &header_data[TCP_SIZE], TCP_CMD_SIZE);

		if(packet_size <= 0 || packet_size >= MAX_TCP_IN_SIZE)
		{
			header_size = 0;
			return false;
		}
		packet_size -= TCP_HEADER_SIZE;
		is_waiting_data = true;

		return WriteData(c, &buffer[copySize], count-copySize);
	}
	else
	{
		int copySize = GET_DATA_COPY_SIZE(count);
		if(copySize<=0)
		{
			//继续等待数据
			return true;
		}
		memcpy(&data[data_size], buffer, copySize);
		data_size += copySize;
		if(data_size >= packet_size)
		{
			//处理逻辑
		//	cout<<" len:"<<packet_size<<" cmd:"<<msg_cmd<<endl;
			TCP_CMD_HANDLER->HanderCmdMsg(c, data, data_size, msg_cmd);
		}
		packet_size = 0;
		header_size = 0;
		data_size = 0;
		is_waiting_data = false;
		if(data_size > packet_size)
		{
			return WriteData(c, &buffer[copySize], count-copySize);
		}
	}
	return true;

}
