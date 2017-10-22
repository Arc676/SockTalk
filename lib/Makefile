CC=g++
FLAGS=-std=c++11 -c

clean:
	rm *.a *.o

lib: exitcodes.o acceptthread.o socktalkclient.o clienthandler.o msgthread_c.o msgthread.o msgthread_s.o socktalkserver.o
	ar rcs socktalk.a *.o

exitcodes.o:
	$(CC) $(FLAGS) exitcodes.app
acceptthread.o:
	$(CC) $(FLAGS) acceptthread.cpp
socktalkclient.o:
	$(CC) $(FLAGS) socktalkclient.cpp
clienthandler.o:
	$(CC) $(FLAGS) clienthandler.cpp
msgthread_c.o:
	$(CC) $(FLAGS) msgthread_c.cpp
msgthread.o:
	$(CC) $(FLAGS) msgthread.cpp
msgthread_s.o:
	$(CC) $(FLAGS) msgthread_s.cpp
socktalkserver.o:
	$(CC) $(FLAGS) socktalkserver.cpp
