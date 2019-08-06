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
//#include <fcntl.h>
//#include <sys/resource.h>
//#include <errno.h>
#include "data/ClientData.pb.h"


using namespace std;
#define MAX_EVENTS 10000
#define N 128

#define  err_log(errlog) cout<<errlog<<endl;
//#define  err_log(errlog) do{perror(errlog); exit(1);}while(0)

class server
{
	public:

		server(string ip, string port);
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
		void start1();
	private:
		string m_ip;
		string m_port;
		int socket_fd;
		int epoll_fd;
		char buf[N];
		struct epoll_event ev, events[MAX_EVENTS];
	   	
		struct sockaddr_in serveraddr, clientaddr;
		socklen_t addrlen = sizeof(struct sockaddr);
		
		vector<int> fd_v;
		vector<int>::iterator fd_it;
		
		
		void fdRemove(int fd)
		{
			for(fd_it = fd_v.begin();fd_it!=fd_v.end();fd_it++)
			{
				if (fd == *fd_it)
				{
					fd_v.erase(fd_it);
					break;
				}
			}
		}

		void handleAccept();
		void handleRecv(int handle_fd);

};
