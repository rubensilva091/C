all: exe

exe: main.o Ficheiros/Ex1.o Ficheiros/Ex2.o Ficheiros/Ex3.o Ficheiros/Ex4.o Ficheiros/Ex5.o Ficheiros/Ex6.o Ficheiros/Ex7.o
	gcc -g -o exe main.o Ficheiros/Ex1.o Ficheiros/Ex2.o Ficheiros/Ex3.o Ficheiros/Ex4.o Ficheiros/Ex5.o Ficheiros/Ex6.o Ficheiros/Ex7.o

main.o: main.c header.h
	gcc -g -o main.o main.c -c -W -Wall -ansi -pedantic

Ficheiros/Ex1.o: Ficheiros/Ex1.c header.h
	gcc -g -o Ficheiros/Ex1.o Ficheiros/Ex1.c -c -W -Wall -ansi -pedantic

Ficheiros/Ex2.o: Ficheiros/Ex2.c header.h
	gcc -g -o Ficheiros/Ex2.o Ficheiros/Ex2.c -c -W -Wall -ansi -pedantic

Ficheiros/Ex3.o: Ficheiros/Ex3.c header.h
	gcc -g -o Ficheiros/Ex3.o Ficheiros/Ex3.c -c -W -Wall -ansi -pedantic

Ficheiros/Ex4.o: Ficheiros/Ex4.c header.h
	gcc -g -o Ficheiros/Ex4.o Ficheiros/Ex4.c -c -W -Wall -ansi -pedantic

Ficheiros/Ex5.o: Ficheiros/Ex5.c header.h
	gcc -g -o Ficheiros/Ex5.o Ficheiros/Ex5.c -c -W -Wall -ansi -pedantic

Ficheiros/Ex6.o: Ficheiros/Ex6.c header.h
	gcc -g -o Ficheiros/Ex6.o Ficheiros/Ex6.c -c -W -Wall -ansi -pedantic

Ficheiros/Ex7.o: Ficheiros/Ex7.c header.h
	gcc -g -o Ficheiros/Ex7.o Ficheiros/Ex7.c -c -W -Wall -ansi -pedantic

clean:
	del /Q /S *.o *~ exe