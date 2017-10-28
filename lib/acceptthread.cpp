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

#include "acceptthread.h"
#include "socktalkserver.h"
#include "socktalkclienthandler.h"

void AcceptThread::run(AcceptThread* accThread) {
	while (accThread->running) {
		int clientSock = accept(accThread->serverSock, (sockaddr*)NULL, (socklen_t*)NULL);
		if (clientSock < 0) {
			accThread->server->handleMessage("Failed to accept", ERROR);
			accThread->running = 0;
		} else {
			SSL *cSSL = SSL_new(accThread->sslctx);
			SSL_set_fd(cSSL, clientSock);
			int err = SSL_accept(cSSL);
			if (err <= 0) {
				accThread->server->handleMessage("Failed to accept with SSL", ERROR);
				accThread->running = 0;
				accThread->server->ShutdownSSL(cSSL);
				return;
			}
			SockTalkClientHandler* ch = new SockTalkClientHandler(clientSock, cSSL, accThread->server);
			if (ch->isRunning()) {
				accThread->server->addHandler(ch);
			} else {
				delete ch;
			}
		}
	}
}

AcceptThread::AcceptThread(SockTalkServer* server, int sock, SSL_CTX* sslctx) :
	serverSock(sock), server(server), sslctx(sslctx), running(1), accThread(&AcceptThread::run, this) {}
