#include "client.h"

void Client::run(){
	if (status != SUCCESS){
		std::cout << "Failed to set up chat service" << std::endl;
		return;
	}
	std::cout << "Connected\n";
	std::string input;
	while (1){
		std::getline(std::cin, input);
		if (input == "/disconnect"){
			std::cout << "Disconnecting...\n";
			msgThread->running = 0;
			break;
		}else if (input == ""){
			continue;
		}
		input = username + ": " + input;
		if (input.at(0) != '/'){
			std::cout << input << std::endl;
		}
		write(sock, input.c_str(), input.length());
	}
	std::cout << "Closing socket\n";
	close(sock);
	std::cout << "Chat terminated" << std::endl;
}

int main(int argc, char * argv[]){
	int port;
	std::string host;
	std::string username;
	if (argc == 4){
		username = std::string(argv[1]);
		host = std::string(argv[2]);
		std::stringstream(argv[3]) >> port;
	}else{
		std::cout << "Enter username: ";
		std::getline(std::cin, username);

		std::cout << "Enter host: ";
		std::getline(std::cin, host);

		std::string tmp;
		std::cout << "Enter port: ";
		std::getline(std::cin, tmp);
		std::stringstream(tmp) >> port;
	}
	Client* client = new Client(port, host, username);
	client->run();
	return 0;
}
