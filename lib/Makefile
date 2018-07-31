CC=g++
FLAGS=-std=c++11 -c

ifdef DEBUG
	FLAGS+=-g -O0
endif

lib: messagehandler.o exitcodes.o acceptthread.o socktalkclient.o socktalkclienthandler.o msgthread.o socktalkserver.o
	ar rcs libsocktalk.a *.o

%.o: %.cpp
	$(CC) $(FLAGS) $<

clean:
	rm *.a *.o
