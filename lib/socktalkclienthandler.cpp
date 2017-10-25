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

#include "socktalkclienthandler.h"

SockTalkClientHandler::SockTalkClientHandler(int socket, SockTalkServer* server) : sock(socket) {
	char user[256];
	int bytes = read(sock, user, 255);
	user[bytes] = '\0';
	username = std::string(user);
	if (server->usernameTaken(username)){
		write(sock, "N", 1);
	}else{
		write(sock, "K", 1);
		msgThread = new MsgThread(username, sock, server);
	}
}

void SockTalkClientHandler::send(const std::string &msg){
	write(sock, msg.c_str(), msg.length());
}

void SockTalkClientHandler::stop(){
	if (msgThread != nullpointer){
		msgThread->running = 0;
	}
}

int SockTalkClientHandler::isRunning(){
	if (msgThread == nullpointer){
		return 0;
	}
	return msgThread->running;
}
