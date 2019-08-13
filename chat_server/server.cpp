#include"server.h"
server::server()
{
	load_config();
	cout<<"ip:"<<m_ip<<" "<<"m_port:"<<m_port<<endl;

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

	if(listen(socket_fd, 100) < 0)
	{
		err_log("fail to listen");
		exit(1);
	}

	if((epoll_fd = epoll_create(65535)) < 0)
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
	vector<client*>::iterator it;
	for (it = client_v.begin(); it!=client_v.end();it++)
	{
		client* c;
		close(c->fd);
		delete c;
		c = nullptr;
	}
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
					handleRecv(events[n].data.ptr);
				}
			}
		}
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
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
		set_non_blocking(wait_fd);
		client *c = new client(wait_fd);
		ev.events = EPOLLIN | EPOLLET;
		//ev.data.fd = wait_fd;
		ev.data.ptr = c;
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, wait_fd,&ev) == -1) {
			err_log("fail to epoll_ctl");
		}
		client_v.push_back(c);
		cout<<"accept fd:"<<wait_fd<<endl;
	}
	catch(exception& e)
	{
		cout<<e.what()<<endl;
	}
}
void server::handleRecv(void *ptr)
{
	try
	{
		client *c=(client *)ptr;
		int handle_fd = c->fd;
		int ret;
		while(1)
		{
			memset(buf, 0, sizeof(buf));
			if((ret = recv(handle_fd, buf, N, 0)) < 0)
			{
				if(EAGAIN == errno)
				{
					break;
				}
				else if(ECONNRESET == errno)
				{
					clientRemove(handle_fd);
					close(handle_fd);
					cout<<"fd:"<<handle_fd<<" close"<<endl;
					break;
				}
				cout<<"recv err errno:"<<errno<<endl;
				return;	
			}
			if(ret == 0)
			{
				if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, handle_fd, NULL)<0)
				{
					err_log("fail to epoll_ctl");
				}
				clientRemove(handle_fd);
				close(handle_fd);
				return;	
			}
			c->tcp_packet->WriteData(c,buf, ret);
			/*
			   buf[ret]='\0';
			   int length;
			   int cmd;
			   memcpy(&length, &buf[0], sizeof(length));           // type [0,4)
			   memcpy(&cmd, &buf[4], sizeof(cmd));       // length [4,8)
			   string str = &buf[8];
			   Data::ClientData data;
			   data.ParseFromString(str);  
			   cout<<"fd:"<<handle_fd<<" len:"<<length<<" cmd:"<<cmd<<" userID: "<<data.user_id()<<" userName: "<<data.user_name()<<endl;


			//		data.set_user_name("闫明飞");
			//		data.set_user_id(111200);
			data.SerializeToString(&str);  
			char bts[str.length()+8];
			//strcpy(bts, str.c_str()); 
			int type = 1000;
			length = 8 + strlen(str.c_str());	
			memcpy(&bts[0], &length, sizeof(type));           // type [0,4)
			memcpy(&bts[4], &type, sizeof(length));       // length [4,8)
			memcpy(&bts[8], str.c_str(), strlen(str.c_str()));

			for(int i=0;i<client_v.size();i++)
			{
			client* ct = client_v[i];
			if(send(ct->fd, bts, sizeof(bts), 0) < 0)
			{
			err_log("fail to send");
			}
			}
			*/
		}
	}
	catch(exception& e)
	{
		cout<<e.what()<<endl;
	}
}

void server::set_non_blocking(int acceptfd)
{
	int flags ;
	flags = fcntl(acceptfd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(acceptfd, F_SETFL, flags);
}

void server::set_blocking(int acceptfd)
{
	int flags ;
	flags = fcntl(acceptfd, F_GETFL, 0);
	flags |= ~O_NONBLOCK;
	fcntl(acceptfd, F_SETFL, flags);
}

bool server::load_config()
{
	try
	{
		char *path = new char[100]; 
		XML_MANAGER->getResPath((char*)"AppConfig.xml", path);

		TiXmlDocument doc = XML_MANAGER->load(path);
		TiXmlElement* ele = XML_MANAGER->getElements(doc,"Config");
		TiXmlElement* server_node = XML_MANAGER->getElementValue(ele,(char*)"Server");

		TiXmlElement* redis_node = XML_MANAGER->getElementValue(ele,(char*)"Redis");
		const char*ser_ip = XML_MANAGER->getAttributeToStr(server_node, (char*)"IP");
		const char* ser_port = XML_MANAGER->getAttributeToStr(server_node, (char*)"Port");

		const char*red_ip = XML_MANAGER->getAttributeToStr(redis_node, (char*)"IP");
		int red_port = XML_MANAGER->getAttributeToInt(redis_node, (char*)"Port");
		const char*red_pass = XML_MANAGER->getAttributeToStr(redis_node, (char*)"Password");
		int red_count = XML_MANAGER->getAttributeToInt(redis_node, (char*)"Count");
		m_ip = ser_ip;
		m_port = ser_port;
		redis_ip = red_ip;
		redis_port = red_port;
		redis_password = red_pass;
		redis_pool_count = red_count;
		cout<<m_ip<<" "<<m_port<<endl;
		cout<<redis_ip<<" "<<redis_port<<" "<<red_pass<<endl;
		REDIS_MANAGER = new RedisPoll();
		REDIS_MANAGER->init(redis_pool_count,redis_ip,redis_port,redis_password);

		delete[] path;
		delete redis_node;
		delete server_node;
		delete ele;
	}
	catch(exception& e)
	{
		cout<<e.what()<<endl;
	}
}

