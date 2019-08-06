#include "server.h"

int main()
{
	server * server_p = new server("172.19.123.155", "4402");

	server_p->start();

	delete server_p;
	server_p = nullptr;
	return 0;
}
