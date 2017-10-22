#include "server.h"

void Server::handleMessage(const std::string &msg){
	std::cout << msg << '\n';
}

int main(int argc, char * argv[]){
	int port;
	if (argc == 2){
		std::string str(argv[1]);
		std::stringstream(str) >> port;
	}else{
		std::cout << "Enter port number: ";
		std::string input;
		getline(std::cin, input);
		std::stringstream(input) >> port;
	}
	Server* server = new Server(port);
	server->run();
}
