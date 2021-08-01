CC=g++

CFLAGS=-lsfml-graphics -lsfml-window -lsfml-system  -Wall

all: game

game: class_Object.o player.o Bot.o Tank2.o Tank3.o Tank4.o main.o
	$(CC) -o game class_Object.o player.o Bot.o Tank2.o Tank3.o Tank4.o main.o $(CFLAGS)
	
class_Object.o: class_Object.cpp
	$(CC) -c class_Object.cpp

player.o: player.cpp
	$(CC) -c player.cpp

Bot.o: Bot.cpp
	$(CC) -c Bot.cpp

Tank2.o: Tank2.cpp
	$(CC) -c Tank2.cpp

Tank3.o: Tank3.cpp
	$(CC) -c Tank3.cpp

Tank4.o: Tank4.cpp
	$(CC) -c Tank4.cpp

main.o: main.cpp
	$(CC) -c main.cpp
	
clear:
	rm -rf *.o
