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
	InitializeSSL();
	if (username == "server" || username == "global"){
		status = NO_RESERVED_NAMES;
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
	
	SSL_CTX *sslctx = SSL_CTX_new(SSLv23_client_method());
	SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);
	if (SSL_CTX_use_certificate_file(sslctx, "cert.pem", SSL_FILETYPE_PEM) != 1) {
		status = FAILED_TO_GET_CERTIFICATE;
		return;
	}
	if (SSL_CTX_use_PrivateKey_file(sslctx, "key.pem", SSL_FILETYPE_PEM) != 1) {
		status = FAILED_TO_GET_PRIVATE_KEY;
		return;
	}

	ssl = SSL_new(sslctx);
	SSL_set_fd(ssl, sock);
	if (SSL_accept(ssl) <= 0) {
		status = SSL_ACCEPT_FAILED;
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
}
