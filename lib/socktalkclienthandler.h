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

#ifndef SOCKTALKCLIENTHANDLER_H
#define SOCKTALKCLIENTHANDLER_H

#include <unistd.h>
#include <string>

#include "msgthread.h"

class SockTalkServer;

class SockTalkClientHandler {
	MsgThread* msgThread;
	int sock;

    public:
	std::string username;
	SockTalkClientHandler(int, SockTalkServer*);
	void send(const std::string&);
	void stop();
	int isRunning();
};

#endif
