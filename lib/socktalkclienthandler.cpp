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
#include "socktalkserver.h"

SockTalkClientHandler::SockTalkClientHandler(int socket, SSL* ssl, SockTalkServer* server) : sock(socket), ssl(ssl) {
	char user[256];
	int bytes = SSL_read(ssl, user, 255);
	user[bytes] = '\0';
	username = std::string(user);
	if (server->usernameTaken(username)){
		SSL_write(ssl, "N", 1);
	}else{
		SSL_write(ssl, "K", 1);
		msgThread = new MsgThread(username, ssl, server);
	}
}

void SockTalkClientHandler::send(const std::string &msg){
	SSL_write(ssl, msg.c_str(), msg.length());
}

void SockTalkClientHandler::stop(){
	if (msgThread != nullpointer){
		msgThread->running = 0;
	}
	close(sock);
}

int SockTalkClientHandler::isRunning(){
	if (msgThread == nullpointer){
		return 0;
	}
	return msgThread->running;
}
