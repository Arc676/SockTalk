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

#include "msgthread_s.h"
#include "server.h"

MsgThreadS::MsgThreadS(const std::string &username, int socket, Server* server) : MsgThread(username, socket, server, this) {}

void MsgThreadS::print(const std::string &msg){
	if (msg.length() > 8 && !msg.compare(msg.length() - 8, 8, ": /users")){ //' /users' is 7 chars long, -8 to get the colon and make sure the msg consists ONLY of '/users'
		server->sendTo(server->userList(), username);
	}else{
		server->broadcast(msg, username);
	}
}
