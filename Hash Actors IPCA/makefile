all: InterMovieData

InterMovieData: main.o Files/actorsInfo.o Files/Functions.o
	gcc -g -o InterMovieData main.o Files/actorsInfo.o Files/Functions.o

main.o: main.c header.h
	gcc -g -o main.o main.c -c -W -Wall -ansi -pedantic

Files/actorsInfo.o: Files/actorsInfo.c header.h
	gcc -g -o Files/actorsInfo.o Files/actorsInfo.c -c -W -Wall -ansi -pedantic
	
Files/Functions.o: Files/Functions.c header.h
	gcc -g -o Files/Functions.o Files/Functions.c -c -W -Wall -ansi -pedantic

clean:
	del /Q /S *.o *~ InterMovieData