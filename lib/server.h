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

#include <iostream>
#include <string>
#include <sstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <vector>

class ClientHandler;
class AcceptThread;

class Server {
	int serverSock;
	int serverPort;
	int setupSuccessful;
	AcceptThread* acceptThread;
	std::vector<ClientHandler*> handlers;

	void checkHandlers();

    public:
	Server(int);
	void run();

	void addHandler(ClientHandler*);
	int usernameTaken(const std::string&);
	
	void broadcast(const std::string&, const std::string&);
	void sendTo(const std::string&, const std::string&);
	
	std::string userList();
};
