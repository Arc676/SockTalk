#include "server.h"

void Server::handleMessage(const std::string &msg){
	std::cout << msg << '\n';
}

void Server::run(){
	if (status != SUCCESS){
		std::cout << "Failed to set up chat service: " << ExitCodes::errToString(status) << '\n';
		return;
	}
	std::string input;
	while (1){
		std::getline(std::cin, input);
		if (input == "/close"){
			std::cout << "Closing server\n";
			break;
		}else if (input == "/users"){
			checkHandlers();
			std::cout << userList() << "\n";
		}else if (input == "/help"){
			std::cout << "Available commands:\n\t/help - show commands\n\t/users - show connected users\n\t/close - close server\n";
		}else if (input != ""){
			input = "Server: " + input;
			std::cout << input << "\n";
			broadcast(input, "server");
		}
		checkHandlers();
	}

	std::cout << "Closing listener\n";
	close(serverSock);
	acceptThread->running = 0;
	std::cout << "Stopping handlers\n";
	for (int i = 0; i < handlers.size(); i++){
		handlers[i]->stop();
		delete handlers[i];
	}
	std::cout << "Server closed" << std::endl;
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
