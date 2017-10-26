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

#ifndef SOCKTALKSERVER_H
#define SOCKTALKSERVER_H

#include <iostream>
#include <string>
#include <sstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <vector>

#ifndef OPENSSL
#define OPENSSL

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#endif

#include "messagehandler.h"
#include "exitcodes.h"

class AcceptThread;
class SockTalkClientHandler;

class SockTalkServer : public MessageHandler {
    protected:
	int serverSock;
	int serverPort;
	AcceptThread* acceptThread;
	std::vector<SockTalkClientHandler*> handlers;

	int status = SUCCESS;

	void checkHandlers();
    public:
	SockTalkServer(int);
	virtual void run() = 0;
	virtual void closeServer();

	std::string userList();

	virtual void addHandler(SockTalkClientHandler*);
	virtual int usernameTaken(const std::string&);

	virtual void broadcast(const std::string&, const std::string&);
	virtual void sendTo(const std::string&, const std::string&);
};

#endif
