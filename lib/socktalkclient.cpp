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

#include "socktalkclient.h"

SockTalkClient::SockTalkClient(int port, const std::string &host, const std::string &username) :
	username(username) {
	if (username == "server" || username == "global"){
		status = NO_RESERVED_NAMES;
		return;
	}
	status = InitializeSSL("cert.pem", "key.pem", 0);
	if (status != SUCCESS) {
		return;
	}
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0){
		status = CREATE_SOCKET_FAILED;
		return;
	}

	sockaddr_in hostaddr;
	hostaddr.sin_family = AF_INET;
	hostaddr.sin_port = htons(port);
	hostaddr.sin_addr.s_addr = inet_addr(host.c_str());

	if (connect(sock, (sockaddr*)&hostaddr, sizeof(hostaddr)) < 0){
		status = FAILED_TO_CONNECT;
		return;
	}

	ssl = SSL_new(sslctx);
	SSL_set_fd(ssl, sock);
	if (SSL_connect(ssl) <= 0) {
		ERR_print_errors_fp(stderr);
		status = SSL_CONNECT_FAILED;
		ShutdownSSL(ssl);
		return;
	}
	SSL_write(ssl, username.c_str(), username.length());
	char registration[2];
	int bytes = SSL_read(ssl, registration, 1);
	registration[bytes] = '\0';
	if (registration[0] == 'N'){
		status = REGISTRATION_FAILED;
		close(sock);
		return;
	}

	msgThread = new MsgThread(username, ssl, this);
}

void SockTalkClient::closeClient() {
	close(sock);
	ShutdownSSL(ssl);
	DestroySSL();
}

int SockTalkClient::send(const std::string &message) {
	return SSL_write(ssl, message.c_str(), message.length());
}

int SockTalkClient::getStatus() {
	return status;
}
