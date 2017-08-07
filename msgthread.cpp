//SockTalk 1.0.1
//Written by Alessandro Vinciguerra <alesvinciguerra@gmail.com>
//Copyright (C) 2017  Matthew Chen, Arc676/Alessandro Vinciguerra

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//See README.txt and LICENSE.txt for more details

//Based on work by Matthew Chen and Alessandro Vinciguerra (under MIT license)

#include "msgthread.h"
#include "server.h"

#define BUF_SIZE 2048

void run(MsgThread* msgThread){
	char buffer[BUF_SIZE];
	while (msgThread->running){
		int bytes = read(msgThread->socket, buffer, BUF_SIZE - 1);
		if (bytes < 0){
			std::cerr << "Failed to read" << std::endl;
			msgThread->running = 0;
		}else if (bytes == 0){
			msgThread->print(msgThread->username + " disconnected");
			msgThread->running = 0;
		}else{
			buffer[bytes] = '\0';
			std::string str(buffer);
			msgThread->print(str);
		}
		memset(buffer, 0, BUF_SIZE);
	}
}

MsgThread::MsgThread(const std::string &username, int socket, Server* server, MsgThread* mthread) :
	username(username), socket(socket), server(server), running(1),
	msgThread(run, mthread) {}

void MsgThread::print(const std::string &msg){}
