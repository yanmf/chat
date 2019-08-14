#ifndef _HANDLER_CMD_H
#define _HANDLER_CMD_H
#include "../logic/client.h"

class client;
class IHandlerCmd
{
	public:
		virtual bool HandlerCmd(client*, char*, int, int) = 0;
};

#endif
