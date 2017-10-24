//SockTalk 2.0
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

#include <iostream>
#include <string>
#include <sstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <vector>

#include "exitcodes.h"

class ClientHandler;
class AcceptThread;

class SockTalkServer : public MessageHandler {
	int serverSock;
	int serverPort;
	AcceptThread* acceptThread;
	std::vector<ClientHandler*> handlers;

	int status = SUCCESS;

	void checkHandlers();

    public:
	SockTalkServer(int);
	virtual void run();

	std::string userList();

	virtual void addHandler(ClientHandler*);
	virtual int usernameTaken(const std::string&);

	virtual void broadcast(const std::string&, const std::string&);
	virtual void sendTo(const std::string&, const std::string&);
};