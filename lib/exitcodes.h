#ifndef EXITCODES_H
#define EXITCODES_H

#include <string>

#define SUCCESS 0
#define CREATE_SOCKET_FAILED 1
#define BIND_SOCKET_FAILED 2
#define LISTEN_SOCKET_FAILED 3

class ExitCodes {
public:
	static std::string errToString(int);
}

#endif
