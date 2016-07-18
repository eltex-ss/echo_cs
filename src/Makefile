objects = server.o client.o

targets = server client

CFLAGS = -Wall -pedantic -ansi -g

all : $(targets) reloc

server : server.o
		$(CC) -o $@ $<

client : client.o
		$(CC) -o $@ $<

$(objects) : %.o : %.c
		$(CC) -c $(CFLAGS) $<

reloc :
		mkdir -p ../build
		mv $(targets) ../build

.PHONY : clean

clean :
		-rm -r *.o ../build
