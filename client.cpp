//SockTalk 1.0.1
//Written by Alessandro Vinciguerra <alesvinciguerra@gmail.com>
//Copyright (C) 2017  Matthew Chen, Arc676/Alessandro Vinciguerra

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//See README.txt and LICENSE.txt for more details

//Based on work by Matthew Chen and Alessandro Vinciguerra (under MIT license)

#include "client.h"
#include "msgthread_c.h"

Client::Client(int port, const std::string &host, const std::string &username) :
	username(username), setupSuccessful(0) {
	if (username == "server" || username == "global"){
		std::cout << "Reserved usernames cannot be used" << std::endl;
		return;
	}
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0){
		std::cerr << "Failed to create socket\nError code: " << errno << std::endl;
		return;
	}

	sockaddr_in hostaddr;
	hostaddr.sin_family = AF_INET;
	hostaddr.sin_port = htons(port);
	hostaddr.sin_addr.s_addr = inet_addr(host.c_str());

	if (connect(sock, (sockaddr*)&hostaddr, sizeof(hostaddr)) < 0){
		std::cerr << "Failed to connect to host\nError code: " << errno << std::endl;
		return;
	}

	std::cout << "Registering with server...\n";
	write(sock, username.c_str(), username.length());
	char registration[2];
	int bytes = read(sock, registration, 1);
	registration[bytes] = '\0';
	if (registration[0] == 'K'){
		std::cout << "Registration successful\n";
	}else{
		std::cout << "Username taken\n";
		close(sock);
		return;
	}

	setupSuccessful = 1;

	msgThread = new MsgThreadC(username, sock);
}

void Client::run(){
	if (!setupSuccessful){
		std::cout << "Failed to set up chat service" << std::endl;
		return;
	}
	std::cout << "Connected\n";
	std::string input;
	while (1){
		std::getline(std::cin, input);
		if (input == "/disconnect"){
			std::cout << "Disconnecting...\n";
			msgThread->running = 0;
			break;
		}else if (input == ""){
			continue;
		}
		input = username + ": " + input;
		if (input.at(0) != '/'){
			std::cout << input << std::endl;
		}
		write(sock, input.c_str(), input.length());
	}
	std::cout << "Closing socket\n";
	close(sock);
	std::cout << "Chat terminated" << std::endl;
}

int main(int argc, char * argv[]){
	int port;
	std::string host;
	std::string username;
	if (argc == 4){
		username = std::string(argv[1]);
		host = std::string(argv[2]);
		std::stringstream(argv[3]) >> port;
	}else{
		std::cout << "Enter username: ";
		std::getline(std::cin, username);

		std::cout << "Enter host: ";
		std::getline(std::cin, host);

		std::string tmp;
		std::cout << "Enter port: ";
		std::getline(std::cin, tmp);
		std::stringstream(tmp) >> port;
	}
	Client* client = new Client(port, host, username);
	client->run();
	return 0;
}
