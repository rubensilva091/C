all: exe

exe: Ficheiros/main.o Ficheiros/interpretador.o Ficheiros/parser.o Ficheiros/stack.o Ficheiros/token.o Ficheiros/array.o Ficheiros/string.o Ficheiros/bloco.o
	gcc -g -o exe Ficheiros/main.o Ficheiros/interpretador.o Ficheiros/parser.o Ficheiros/stack.o Ficheiros/token.o Ficheiros/array.o Ficheiros/string.o Ficheiros/bloco.o

Ficheiros/main.o: Ficheiros/main.c Ficheiros/interpretador.h Ficheiros/parser.h Ficheiros/stack.h Ficheiros/token.h
	gcc -g -o Ficheiros/main.o Ficheiros/main.c -c -W -Wall -ansi -pedantic

Ficheiros/interpretador.o: Ficheiros/interpretador.c Ficheiros/interpretador.h
	gcc -g -o Ficheiros/interpretador.o Ficheiros/interpretador.c -c -W -Wall -ansi -pedantic

Ficheiros/parser.o: Ficheiros/parser.c Ficheiros/parser.h
	gcc -g -o Ficheiros/parser.o Ficheiros/parser.c -c -W -Wall -ansi -pedantic

Ficheiros/stack.o: Ficheiros/stack.c Ficheiros/stack.h
	gcc -g -o Ficheiros/stack.o Ficheiros/stack.c -c -W -Wall -ansi -pedantic

Ficheiros/token.o: Ficheiros/token.c Ficheiros/token.h
	gcc -g -o Ficheiros/token.o Ficheiros/token.c -c -W -Wall -ansi -pedantic

Ficheiros/array.o: Ficheiros/array.c Ficheiros/array.h
	gcc -g -o Ficheiros/array.o Ficheiros/array.c -c -W -Wall -ansi -pedantic

Ficheiros/string.o: Ficheiros/string.c Ficheiros/string.h
	gcc -g -o Ficheiros/string.o Ficheiros/string.c -c -W -Wall -ansi -pedantic

Ficheiros/bloco.o: Ficheiros/bloco.c Ficheiros/bloco.h
	gcc -g -o Ficheiros/bloco.o Ficheiros/bloco.c -c -W -Wall -ansi -pedantic

clean:
	del /Q /S *.o *~ exe