# SockTalk

SockTalk source code and MakeFile (server and client)

MakeFile may have to be modified to use installed compiler.

The SockTalk protocol is a simple, open-source network communication protocol. Communication is encrypted using SSL (currently requires `cert.pem` and `key.pem` to be in 
the directory of the executables).

SockTalk is a C++ static library. In the `stclient` folder is a pair of command line IM programs (server and client) that use the SockTalk protocol. Certificate and key 
not provided. Compiling SockTalk requires that the OpenSSL library be installed.

Server listens on socket on desired port and multiple clients can connect.
- "/close" from server side closes server socket.
- "/disconnect" from client side disconnects from server.
- "/help" gives a list of commands supported by the server.

SockTalk client-server registration protocol:
1. Client connects to server via socket
2. Server creates a new handler for the client
3. Client sends username over network
4. Handler checks if username is available and replies with "N" (no) or "K" (ok)
5. If username is unavailable, handler memory is deallocated and connection is refused
6. If username is available, handler gets added to handler list and the connection is established

Source code available under GPLv3, except for OpenSSL library. Read LICENSE.txt for more details.

Work is based on a project by Matthew Chen and Arc676/Alessandro Vinciguerra.

Source code for that project is available under MIT license [here](https://github.com/Arc676/Java-Chat)
