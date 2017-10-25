CC=g++
FLAGS=-std=c++11
LD=-I ../lib -L ../lib
LIB=-l socktalk

all:
	make server
	make client

client:
	$(CC) $(FLAGS) $(LD) client.cpp $(LIB) -o client

server:
	$(CC) $(FLAGS) $(LD) server.cpp $(LIB) -o server

clean:
	rm *.o server client
