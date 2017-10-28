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

#ifndef SOCKTALKCLIENT_H
#define SOCKTALKCLIENT_H

#include <iostream>
#include <string>
#include <sstream>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "messagehandler.h"
#include "exitcodes.h"
#include "msgthread.h"

class SockTalkClient : public MessageHandler {
    protected:
	int sock;
	SSL* ssl;
	std::string username;
	MsgThread* msgThread;

	int status = SUCCESS;

	int send(const std::string&);
	void closeClient();
    public:
	SockTalkClient(int, const std::string&, const std::string&);
	int getStatus();
};

#endif
