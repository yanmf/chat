#include "server.h"

int main()
{
	server * server_p = new server();

	server_p->start();

	delete server_p;
	server_p = nullptr;
	return 0;
}
