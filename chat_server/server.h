
#ifndef _SERVER_H
#define _SERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <vector>
//#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
//#include <sys/resource.h>
//#include <errno.h>
#include "data/ClientData.pb.h"
#include "tcp/TCPPacket.h"
#include "logic/client.h"
#include "logic/xmlManager.h"
#include "redis/redisPool.h"


using namespace std;
#define MAX_EVENTS 10000
#define N 65535

#define  err_log(errlog) cout<<errlog<<endl;
//#define  err_log(errlog) do{perror(errlog); exit(1);}while(0)

class server
{
	public:

		server();
		~server();
		int getSocketFd()
		{
			return socket_fd;
		}
		int getEpollFd()
		{
			return epoll_fd;
		}
		void start();
		void set_non_blocking(int acceptfd);//设置非阻塞模式
		void set_blocking(int acceptfd);//设置阻塞模式

		bool load_config();

	private:
		string m_ip;
		string m_port;
		int socket_fd;
		int epoll_fd;
		char buf[N];
		struct epoll_event ev, events[MAX_EVENTS];

		struct sockaddr_in serveraddr, clientaddr;
		socklen_t addrlen = sizeof(struct sockaddr);

		vector<client*> client_v;
		vector<client*>::iterator client_it;

		string redis_ip;
		int redis_port;
		string redis_password;
		int redis_pool_count;
		RedisPoll *redis_poll;


		void clientRemove(int fd)
		{
			for(client_it = client_v.begin();client_it!=client_v.end();client_it++)
			{
				client* c = *client_it;
				if (fd == c->fd)
				{
					client_v.erase(client_it);
					break;
				}
			}
		}

		void handleAccept();
		void handleRecv(void *c);

};
#endif
