TSRV=server
TCLI=client

CC=g++
FLAGS=-std=c++11
THREAD=-pthread

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
	$(CC) -c client.cpp $(FLAGS) $(THREAD)

server.o: server.cpp
	$(CC) -c server.cpp $(FLAGS) $(THREAD)

msgthread.o: msgthread.cpp
	$(CC) -c msgthread.cpp $(FLAGS) $(THREAD)

msgthread_s.o: msgthread_s.cpp
	$(CC) -c msgthread_s.cpp $(FLAGS) $(THREAD)

msgthread_c.o: msgthread_c.cpp
	$(CC) -c msgthread_c.cpp $(FLAGS) $(THREAD)

acceptthread.o: acceptthread.cpp
	$(CC) -c acceptthread.cpp $(FLAGS) $(THREAD)

clienthandler.o: clienthandler.cpp
	$(CC) -c clienthandler.cpp $(FLAGS) $(THREAD)

clean:
	rm -f *.o server client
