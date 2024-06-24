CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

all: blackjack

blackjack: src/main.o src/carte.o src/jeu.o src/son.o
	$(CC) $(CFLAGS) -o blackjack src/main.o src/carte.o src/jeu.o src/son.o -lwinmm

src/main.o: src/main.c include/main.h include/jeu.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/carte.o: src/carte.c include/carte.h
	$(CC) $(CFLAGS) -c src/carte.c -o src/carte.o

src/jeu.o: src/jeu.c include/jeu.h include/carte.h include/son.h
	$(CC) $(CFLAGS) -c src/jeu.c -o src/jeu.o

src/son.o: src/son.c include/son.h
	$(CC) $(CFLAGS) -c src/son.c -o src/son.o

clean:
	del src\*.o
