//Written by Alessandro Vinciguerra <alesvinciguerra@gmail.com>
//Copyright (C) 2017-8  Arc676/Alessandro Vinciguerra

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3), except using the OpenSSL library is allowed.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

//Based on work by Matthew Chen and Alessandro Vinciguerra under MIT license
//Copyright (c) 2017 Matthew Chen, Arc676/Alessandro Vinciguerra

//Permission is hereby granted, free of charge, to any person obtaining
//a copy of this software and associated documentation files (the "Software"),
//to deal in the Software without restriction, including without limitation the
//rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//sell copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//OpenSSL library available under OpenSSL and SSLeay license
/* ====================================================================
 * Copyright (c) 1998-2017 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#include "socktalkserver.h"
#include "acceptthread.h"
#include "socktalkclienthandler.h"

void SockTalkServer::initialize(int port, const std::string &cert, const std::string &key) {
	serverPort = port;
	if (cert == "" || key == "") {
		useSSL = false;
		status = SUCCESS;
	} else {
		status = InitializeSSL(cert, key, 1);
	}
	if (status != SUCCESS) {
		return;
	}
	serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSock < 0) {
		status = CREATE_SOCKET_FAILED;
		return;
	}

	sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(serverPort);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serverSock, (sockaddr*)&myaddr, sizeof(myaddr)) < 0) {
		status = BIND_SOCKET_FAILED;
		return;
	}

	linger linger_opt = {1,0};
	setsockopt(serverSock, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

	if (listen(serverSock, 5) < 0) {
		status = LISTEN_SOCKET_FAILED;
		return;
	}

	acceptThread = new AcceptThread(this, serverSock, sslctx);
}

void SockTalkServer::closeServer() {
	close(serverSock);
	acceptThread->running = 0;
	broadcast("Server closing", "TERM");
	for (auto const &ch : handlers) {
		ch->stop();
		delete ch;
	}
	handlers.clear();
	if (useSSL) {
		DestroySSL();
	}
}

void SockTalkServer::broadcast(const std::string &msg, const std::string &src) {
	checkHandlers();
	for (auto const &ch : handlers) {
		if (ch->getUsername() != src) {
			ch->send(src + ": " + msg);
		}
	}
}

SockTalkClientHandler* SockTalkServer::sendTo(const std::string &msg, const std::string &recipient) {
	for (auto const &ch : handlers) {
		if (ch->getUsername() == recipient) {
			ch->send(msg);
			return ch;
		}
	}
	return nullpointer;
}

void SockTalkServer::addHandler(SockTalkClientHandler* ch) {
	handlers.push_back(ch);
	handleMessage("Incoming connection...", INFO, "Notice");
}

bool SockTalkServer::isReservedName(const std::string &username) {
	return username == "Server" || username == "Info" || username == "Error" || username == "Notice" || username == "TERM" || username.find(" ") != std::string::npos;
}

bool SockTalkServer::registerName(const std::string &username, const std::string &IP) {
	// erase dropped connections to avoid conflict with previously connected users
	checkHandlers();
	// reserved names fail to register
	if (SockTalkServer::isReservedName(username)) {
		return false;
	}
	// check the banlist for the IP address
	for (auto const &banned : banlist) {
		if (banned.second == IP) {
			return false;
		}
	}
	// check currently connected users
	for (auto const &ch : handlers) {
		if (ch->getUsername() == username) {
			return false;
		}
	}
	return true;
}

void SockTalkServer::checkHandlers() {
	for (int i = 0; i < handlers.size();) {
		if (!handlers[i]->isRunning()) {
			handlers[i]->stop();
			delete handlers[i];
			handlers.erase(handlers.begin() + i);
		} else {
			i++;
		}
	}
}

SockTalkClientHandler* SockTalkServer::kickUser(const std::string &username, const std::string &reason) {
	SockTalkClientHandler* ch = sendTo("TERM: " + reason, username);
	ch->stop();
	return ch;
}

void SockTalkServer::banUser(const std::string &username) {
	SockTalkClientHandler* ch = kickUser(username, "Banned by server");
	banlist.push_back(std::pair<std::string, std::string>(username, ch->getIP()));
}

void SockTalkServer::unbanUser(const std::string &username, const std::string &addr) {
	int idx = 0;
	for (auto const &banned : banlist) {
		if (banned.first == username || banned.second == addr) {
			break;
		}
		idx++;
	}
	banlist.erase(banlist.begin() + idx);
}
