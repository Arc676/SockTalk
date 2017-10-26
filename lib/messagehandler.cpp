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

#include "messagehandler.h"

void MessageHandler::handleMessage(const std::string &msg){}

int MessageHandler::InitializeSSL(const std::string &cert, const std::string &priv, int isServer) {
	SSL_load_error_strings();
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	if (isServer) {
		sslctx = SSL_CTX_new(SSLv23_server_method());
	} else {
		sslctx = SSL_CTX_new(SSLv23_client_method());
	}
	SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);
	if (SSL_CTX_use_certificate_file(sslctx, cert.c_str(), SSL_FILETYPE_PEM) != 1) {
		return FAILED_TO_GET_CERTIFICATE;
	}
	if (SSL_CTX_use_PrivateKey_file(sslctx, priv.c_str(), SSL_FILETYPE_PEM) != 1) {
		return FAILED_TO_GET_PRIVATE_KEY;;
	}
	return SUCCESS;
}

void MessageHandler::DestroySSL() {
	ERR_free_strings();
	EVP_cleanup();
}

void MessageHandler::ShutdownSSL(SSL *ssl) {
	SSL_shutdown(ssl);
	SSL_free(ssl);
}
