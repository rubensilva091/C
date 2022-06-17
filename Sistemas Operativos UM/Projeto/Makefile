all: server client

server: bin/sdstored

client: bin/sdstore

bin/sdstored: obj/sdstored.o
	gcc obj/sdstored.o -o bin/sdstored

obj/sdstored.o: src/sdstored.c
	gcc -Wall -g -c -o obj/sdstored.o src/sdstored.c

bin/sdstore: obj/sdstore.o
	gcc obj/sdstore.o -o bin/sdstore

obj/sdstore.o: src/sdstore.c
	gcc -Wall -g -c -o obj/sdstore.o src/sdstore.c

clean:
	rm -f obj/* tmp/* bin/*