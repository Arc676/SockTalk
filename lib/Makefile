CC=g++
FLAGS=-std=c++11 -c

clean:
	rm *.a *.o

lib: messagehandler.o exitcodes.o acceptthread.o socktalkclient.o socktalkclienthandler.o msgthread.o socktalkserver.o
	ar rcs libsocktalk.a *.o

messagehandler.o:
	$(CC) $(FLAGS) messagehandler.cpp
exitcodes.o:
	$(CC) $(FLAGS) exitcodes.cpp
acceptthread.o:
	$(CC) $(FLAGS) acceptthread.cpp
socktalkclient.o:
	$(CC) $(FLAGS) socktalkclient.cpp
socktalkclienthandler.o:
	$(CC) $(FLAGS) socktalkclienthandler.cpp
msgthread.o:
	$(CC) $(FLAGS) msgthread.cpp
socktalkserver.o:
	$(CC) $(FLAGS) socktalkserver.cpp
