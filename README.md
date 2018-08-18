# SockTalk

C++ implementation of the SockTalk protocol (described in `PROTOCOL.md`) as a statically linked library as well as a command line frontend

The SockTalk protocol is a simple, open-source network communication protocol. Communication is optionally encrypted using SSL.

Compiling SockTalk requires that the OpenSSL library be installed.

## Frontend commands
- "/close" from server side closes server socket.
- "/disconnect" from client side disconnects from server.
- "/help" gives a list of commands supported by the server.

## Legal

Source code available under GPLv3, except linking the OpenSSL library is allowed. OpenSSL available under its own license. See LICENSE.txt for more details.

Work is based on a project by Matthew Chen and Arc676/Alessandro Vinciguerra available under MIT license [here](https://github.com/Arc676/Java-Chat)
