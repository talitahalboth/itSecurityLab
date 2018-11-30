
CFLAGS = -Wall -g -shared -fPIC
CC = gcc


all: hook.so

hook.so: hook.c
	$(CC) $(CFLAGS) -o hook.so hook.c -ldl


clean:
	-rm -f *.so
	-rm -f *.o
