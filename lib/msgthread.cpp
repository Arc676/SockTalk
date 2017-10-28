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

#include "msgthread.h"

#define BUF_SIZE 2048

void run(MsgThread* msgThread) {
	char buffer[BUF_SIZE];
	while (msgThread->running) {
		int bytes = SSL_read(msgThread->socket, buffer, BUF_SIZE - 1);
		if (bytes < 0) {
			msgThread->msgHandler->handleMessage("Failed to read", ERROR);
			msgThread->running = 0;
		} else if (bytes == 0) {
			msgThread->msgHandler->handleMessage(msgThread->username + " disconnected", INFO);
			msgThread->running = 0;
		} else {
			buffer[bytes] = '\0';
			std::string str(buffer);
			msgThread->msgHandler->handleMessage(str, MESSAGE);
		}
		memset(buffer, 0, BUF_SIZE);
	}
}

MsgThread::MsgThread(const std::string &username, SSL* socket, MessageHandler* msgHandler) :
	username(username), socket(socket), msgHandler(msgHandler), running(1),
	msgThread(run, this) {}
