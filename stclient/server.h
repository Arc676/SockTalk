#include <iostream>
#include <string>
#include "socktalkserver.h"

class Server : public SockTalkServer {
public:
	virtual void handleMessage(const std::string&);
}
