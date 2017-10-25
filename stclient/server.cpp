//SockTalk 1.5
//Written by Alessandro Vinciguerra <alesvinciguerra@gmail.com>
//Copyright (C) 2017  Arc676/Alessandro Vinciguerra

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//See README.txt and LICENSE.txt for more details

//Based on work by Matthew Chen and Alessandro Vinciguerra (under MIT license)

#include "server.h"
#include "socktalkclienthandler.h"
#include "acceptthread.h"

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

	std::cout << "Closing server\n";
	closeServer();
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
