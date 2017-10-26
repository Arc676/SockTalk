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

#include "socktalkserver.h"
#include "acceptthread.h"
#include "socktalkclienthandler.h"

SockTalkServer::SockTalkServer(int port) : serverPort(port) {
	InitializeSSL();
	serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSock < 0){
		status = CREATE_SOCKET_FAILED;
		return;
	}

	sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(serverPort);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serverSock, (sockaddr*)&myaddr, sizeof(myaddr)) < 0){
		status = BIND_SOCKET_FAILED;
		return;
	}

	linger linger_opt = {1,0};
	setsockopt(serverSock, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

	if (listen(serverSock, 5) < 0){
		status = LISTEN_SOCKET_FAILED;
		return;
	}

	acceptThread = new AcceptThread(this, serverSock);
}

void SockTalkServer::closeServer() {
	close(serverSock);
	acceptThread->running = 0;
	for (int i = 0; i < handlers.size(); i++){
		handlers[i]->stop();
		delete handlers[i];
	}
	DestroySSL();
}

void SockTalkServer::broadcast(const std::string &msg, const std::string &source){
	for (int i = 0; i < handlers.size(); i++){
		if (handlers[i]->username != source){
			handlers[i]->send(msg);
		}
	}
	if (source != "server"){
		handleMessage(msg);
	}
}

void SockTalkServer::sendTo(const std::string &msg, const std::string &recipient){
	for (int i = 0; i < handlers.size(); i++){
		if (handlers[i]->username == recipient){
			handlers[i]->send(msg);
			break;
		}
	}
}

std::string SockTalkServer::userList(){
	std::string str = "\tConnected users:";
	for (int i = 0; i < handlers.size(); i++){
		str += "\n\t\t" + handlers[i]->username;
	}
	return str;
}

void SockTalkServer::addHandler(SockTalkClientHandler* ch){
	handlers.push_back(ch);
	broadcast(ch->username + " connected", "global");
}

int SockTalkServer::usernameTaken(const std::string &username){
	checkHandlers();
	for (int i = 0; i < handlers.size(); i++){
		if (handlers[i]->username == username){
			return 1;
		}
	}
	return 0;
}

void SockTalkServer::checkHandlers(){
	for (int i = 0; i < handlers.size();){
		if (!handlers[i]->isRunning()){
			delete handlers[i];
			handlers.erase(handlers.begin() + i);
		}else{
			i++;
		}
	}
}
