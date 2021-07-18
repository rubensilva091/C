all: exe

exe: main.o
	gcc -g -o exe header.h auditorias.c dashboard.c Editarauditorias.c Listagem.c estadoResolucao.c atividade.c saveBinario.c main.o

main.o: main.c
	gcc -g -o main.o main.c -c -W -Wall -ansi -pedantic
