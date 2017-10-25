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

#ifndef MSGTHREAD_H
#define MSGTHREAD_H

#include <iostream>
#include <string>
#include <thread>

#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "messagehandler.h"

#if __cplusplus >= 201103L
	#define nullpointer nullptr
#else
	#define nullpointer 0
#endif

class MsgThread {
    protected:
	std::thread msgThread;

    public:
	MessageHandler* msgHandler;
	std::string username;
	int socket;
	int running;

	MsgThread(const std::string&, int, MessageHandler*);
};

void run(MsgThread*);

#endif
