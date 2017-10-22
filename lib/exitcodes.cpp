#include "exitcodes.h"

std::string ExitCodes::errToString(int err) {
	switch (err){
	case SUCCESS:
		return "Success";
	case CREATE_SOCKET_FAILED:
		return "Failed to create socket";
	case BIND_SOCKET_FAILED:
		return "Failed to bind socket";
	case LISTEN_SOCKET_FAILED:
		return "Failed to listen on socket";
	default:
		return "Unknown error";
	}
}
