#include"server.h"
server::server(string ip, string port)
{
	m_ip = ip;
	m_port = port;
	cout<<"ip:"<<ip<<" "<<"m_port:"<<m_port<<endl;

	addrlen = sizeof(struct sockaddr);

	if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		err_log("fail to socket");
		exit(1);
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(m_ip.data());
	serveraddr.sin_port = htons(atoi(m_port.data()));

	if(bind(socket_fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
	{
		err_log("fail to bind");
		exit(1);
	}

	if(listen(socket_fd, 10) < 0)
	{
		err_log("fail to listen");
		exit(1);
	}

	if((epoll_fd = epoll_create(10)) < 0)
	{
		err_log("fail to epoll_create");
		exit(1);
	}

	/*定义一个epoll事件，包括读，要监听的文件描述符*/
	ev.events = EPOLLIN;
	ev.data.fd = socket_fd;

	/*控制专用文件描述符，将sockfd 和 ev 添加到专用文件描述符上，完成注册*/
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &ev) == -1) {
		err_log("fail to epoll_ctl");
		exit(1);
	}
	printf("server init end\n");
	



}

server::~server()
{
	close(socket_fd);
	close(epoll_fd);
}

void server::start()
{
	try
	{
		int nfds;
		int ret;
		int n;
		int wait_fd;
		while(1)
		{
			if ((nfds = epoll_wait(epoll_fd,this->events, MAX_EVENTS, -1)) < 0)
			{
				err_log("fail to epoll_wait");
			}
			for (n = 0; n < nfds; ++n)
			{
				if(events[n].data.fd == socket_fd)
				{
					handleAccept();
				}
				else
				{
					handleRecv(events[n].data.fd);
				}
			}
		}
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
	}
}
void server::start1()
{
	
	int nfds, acceptfd;
	for (;;) {
		if((nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1)) < 0)
		{
			err_log("fail to epoll_wait");
		}
		int ret, n;
		for (n = 0; n < nfds; ++n) {
			/* 查看是那个事件发生了*/
			if(events[n].data.fd == socket_fd) {
				if((acceptfd = accept(socket_fd,(struct sockaddr *) &serveraddr, &addrlen)) < 0)
				{
					err_log("fail to accept");
				}
				/*set_non_blocking(acceptfd);  */
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = acceptfd;
				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, acceptfd,&ev) == -1) {
					err_log("fail to epoll_ctl");
				}
				fd_v.push_back(acceptfd);
			} else {
				memset(buf, 0, sizeof(buf));
				acceptfd = events[n].data.fd;
				if((ret = recv(acceptfd, buf, N, 0)) < 0)
				{
					printf("errno = %d \n", errno);
					continue;
				}
				if(ret == 0)
				{
					if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, acceptfd,NULL) < 0) {
						err_log("fail to epoll_ctl");
					}
					fdRemove(acceptfd);
					close(acceptfd);
					continue;
				}
				printf("client:%s\n", buf);
				
				for(fd_it = fd_v.begin();fd_it!=fd_v.end();fd_it++)
				{
					acceptfd = *fd_it;
					if(send(acceptfd, buf, N, 0) < 0)
					{
						err_log("fail to send");
					}
				}
			}
		}
	}
}
void server::handleAccept()
{
	try
	{
		int wait_fd;
		//处理新的连接
		if((wait_fd = accept(socket_fd, (struct sockaddr *)&this->serveraddr, &this->addrlen)) < 0)
		{
			err_log("fail to accept");
			return;
		}
		ev.events = EPOLLIN | EPOLLET;
		ev.data.fd = wait_fd;
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, wait_fd,&ev) == -1) {
			err_log("fail to epoll_ctl");
		}
		fd_v.push_back(wait_fd);
		cout<<"accept fd:"<<wait_fd<<endl;
	}
	catch(exception& e)
	{
		cout<<e.what()<<endl;
	}
}
void server::handleRecv(int handle_fd)
{
	try
	{
		int ret;
		memset(buf, 0, sizeof(buf));
		if((ret = recv(handle_fd, buf, N, 0)) < 0)
		{
			cout<<"recv err errno:"<<errno<<endl;
			return;	
		}
		if(ret == 0)
		{
			if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, handle_fd, NULL)<0)
			{
				err_log("fail to epoll_ctl");
			}
			fdRemove(handle_fd);
			close(handle_fd);
			return;	
		}
		cout<<"client:"<<(char *)buf<<endl;
		string str;
		Data::ClientData data;
		data.set_user_name("闫明飞");
		data.set_user_id(111200);
		data.SerializeToString(&str);  
		char bts[str.length()];
		strcpy(bts, str.c_str());  

		for(int i=0;i<fd_v.size();i++)
		{
			int fd = fd_v[i];
			if(send(fd, bts, sizeof(bts), 0) < 0)
			{
				err_log("fail to send");
			}
		}
	}
	catch(exception& e)
	{
		cout<<e.what()<<endl;
	}
}
