TSRV=server
TCLI=client

CC=g++
FLAGS=-std=c++11 -pthread

SRV=server.o msgthread.o msgthread_s.o acceptthread.o clienthandler.o
CLI=client.o msgthread.o msgthread_c.o

all:
	make server
	make client

server: $(SRV)
	$(CC) -o $(TSRV) $(SRV) $(FLAGS)

client: $(CLI)
	$(CC) -o $(TCLI) $(CLI) $(FLAGS)

client.o: client.cpp
	$(CC) -c client.cpp $(FLAGS)

server.o: server.cpp
	$(CC) -c server.cpp $(FLAGS)

msgthread.o: msgthread.cpp
	$(CC) -c msgthread.cpp $(FLAGS)

msgthread_s.o: msgthread_s.cpp
	$(CC) -c msgthread_s.cpp $(FLAGS)

msgthread_c.o: msgthread_c.cpp
	$(CC) -c msgthread_c.cpp $(FLAGS)

acceptthread.o: acceptthread.cpp
	$(CC) -c acceptthread.cpp $(FLAGS)

clienthandler.o: clienthandler.cpp
	$(CC) -c clienthandler.cpp $(FLAGS)

clean:
	rm -f *.o server client
