#include <iostream>
#include <string>
#include "socktalk.h"

class Server : public SockTalkServer {
public:
	virtual void handleMessage(const std::string&);
}
