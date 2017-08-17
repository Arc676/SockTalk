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

#include "acceptthread.h"
#include "server.h"
#include "clienthandler.h"

void run(AcceptThread* accThread){
	while (accThread->running){
		//sockaddr_in client;
		int clientSock = accept(accThread->serverSock, (sockaddr*)NULL, (socklen_t*)NULL);
		if (clientSock < 0){
			std::cerr << "Failed to accept\nError code: " << errno << std::endl;
			accThread->running = 0;
		}else{
			ClientHandler* ch = new ClientHandler(clientSock, accThread->server);
			if (ch->isRunning()){
				accThread->server->addHandler(ch);
			}else{
				delete ch;
			}
		}
	}
}

AcceptThread::AcceptThread(Server* server, int sock) :
	serverSock(sock), server(server), running(1), accThread(run, this) {}
