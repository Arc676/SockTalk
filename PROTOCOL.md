# SockTalk protocol

The SockTalk protocol is a simple messaging protocol implemented by the SockTalk library.

## Model

The SockTalk protocol is based on the following entities:

- A message handler is any entity that can receive messages. In the simplest case (e.g. the provided CLI program), these are the server and client classes/programs.
- The "accept thread" listens for new connections made to the server socket. Whenever a new connection is made, a new client handler is created and work is delegated to the handler from that point forward.
- The client handler writes to the destination socket and allows the server to interface with the client.
- The "message thread" continuously reads from the source socket until the connection is interrupted. Server side, there is a message thread for each client handler. These wait for the clients to send messages and then relay the messages to the server. Client side, there is a single message thread that reads from the server and relays the messages to the client.

## Registration

When a client connects to the server, it has to register its username so it can be identified. This username is then used when messages sent from the client are broadcasted to other users. The prepending of the client's username to the message is done server side to prevent modified clients from impersonating other users.

Once a successful socket connection is established, the registration process begins. The client sends the desired username to the server. The server checks if the username is allowed:

- The username cannot be one of the three reserved usernames (Server, Error, Info)
- The username cannot be in use by another connected client

If the username can be used, the server replies with `"K"`. Otherwise, it replies with `"N"`. If registration fails, the server drops the connection immediately. Custom clients should terminate or give up connecting at this point. A new connection must be made to re-register.

## Communication

### Server side

The server uses a separate handler for each connected client. These run on dedicated threads. Each handler records the username sent to it during the registration process. When a message is received, the message is relayed to the server along with the associated username so it can be handled appropriately. The server prepends the username to the message for identification and then broadcasts this to all the connected clients.

### Client side

The client only receives data from the server and thus cannot tell which user sent any given message. It is the server's responsibility to identify messages before broadcasting them to clients. The client merely has to display the messages to the user.
