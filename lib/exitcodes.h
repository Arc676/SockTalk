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

#ifndef EXITCODES_H
#define EXITCODES_H

#include <string>

#define SUCCESS 0
#define CREATE_SOCKET_FAILED 1
#define BIND_SOCKET_FAILED 2
#define LISTEN_SOCKET_FAILED 3
#define NO_RESERVED_NAMES 4
#define FAILED_TO_CONNECT 5
#define FAILED_TO_GET_CERTIFICATE 6
#define FAILED_TO_GET_PRIVATE_KEY 7
#define SSL_ACCEPT_FAILED 8
#define REGISTRATION_FAILED 9

class ExitCodes {
public:
	static std::string errToString(int);
};

#endif
