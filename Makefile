all : PROJET EXECUTION

fonctions.o : fonctions.c fonctions.h
	gcc -c fonctions.c
main.o : main.c 
	gcc -c -Wall main.c
PROJET : main.o fonctions.o
	gcc -o PROJET main.o fonctions.o

EXECUTION :
	./PROJET
