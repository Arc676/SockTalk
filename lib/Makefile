CC=g++
FLAGS=-std=c++11 -c

clean:
	rm *.a *.o

lib: acceptthread.o client.o clienthandler.o msgthread_c.o msgthread.o msgthread_s.o server.o
	ar rcs socktalk.a *.o

acceptthread.o:
	$(CC) $(FLAGS) acceptthread.cpp
client.o:
	$(CC) $(FLAGS) client.cpp
clienthandler.o:
	$(CC) $(FLAGS) clienthandler.cpp
msgthread_c.o:
	$(CC) $(FLAGS) msgthread_c.cpp
msgthread.o:
	$(CC) $(FLAGS) msgthread.cpp
msgthread_s.o:
	$(CC) $(FLAGS) msgthread_s.cpp
server.o:
	$(CC) $(FLAGS) server.cpp
