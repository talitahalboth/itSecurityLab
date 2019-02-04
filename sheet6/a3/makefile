CC=gcc

all: keygen serial

serial: serial.c
	$(CC) -o serial serial.c

keygen: keygen.c
	$(CC) -o keygen keygen.c

clean:
	rm serial keygen