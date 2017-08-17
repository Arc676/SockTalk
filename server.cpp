//SockTalk 1.0.1
//Written by Alessandro Vinciguerra <alesvinciguerra@gmail.com>
//Copyright (C) 2017  Matthew Chen, Arc676/Alessandro Vinciguerra

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
#include "acceptthread.h"
#include "clienthandler.h"

Server::Server(int port) : serverPort(port), setupSuccessful(0) {
	serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSock < 0){
		std::cerr << "Failed to create socket\nError code: " << errno << std::endl;
		return;
	}

	sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(serverPort);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serverSock, (sockaddr*)&myaddr, sizeof(myaddr)) < 0){
		std::cerr << "Failed to bind socket\nError code: " << errno << std::endl;
		return;
	}

	linger linger_opt = {1,0};
	setsockopt(serverSock, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

	if (listen(serverSock, 5) < 0){
		std::cerr << "Failed to listen on socket\nError code: " << errno << std::endl;
		return;
	}

	setupSuccessful = 1;
	acceptThread = new AcceptThread(this, serverSock);
}

void Server::run(){
	if (!setupSuccessful){
		std::cout << "Failed to set up chat service" << std::endl;
		return;
	}
	std::cout << "Hosting chat on port " << serverPort << std::endl;
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

void Server::broadcast(const std::string &msg, const std::string &source){
	for (int i = 0; i < handlers.size(); i++){
		if (handlers[i]->username != source){
			handlers[i]->send(msg);
		}
	}
	if (source != "server"){
		std::cout << msg << "\n";
	}
}

void Server::sendTo(const std::string &msg, const std::string &recipient){
	for (int i = 0; i < handlers.size(); i++){
		if (handlers[i]->username == recipient){
			handlers[i]->send(msg);
			break;
		}
	}
}

std::string Server::userList(){
	std::string str = "\tConnected users:";
	for (int i = 0; i < handlers.size(); i++){
		str += "\n\t\t" + handlers[i]->username;
	}
	return str;
}

void Server::addHandler(ClientHandler* ch){
	handlers.push_back(ch);
	broadcast(ch->username + " connected", "global");
}

int Server::usernameTaken(const std::string &username){
	checkHandlers();
	for (int i = 0; i < handlers.size(); i++){
		if (handlers[i]->username == username){
			return 1;
		}
	}
	return 0;
}

void Server::checkHandlers(){
	for (int i = 0; i < handlers.size();){
		if (!handlers[i]->isRunning()){
			delete handlers[i];
			handlers.erase(handlers.begin() + i);
		}else{
			i++;
		}
	}
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
