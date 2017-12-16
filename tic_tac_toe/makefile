CC=g++
CFLAGS=-c -Wall
all: tic_tac_toe

tic_tac_toe: main.o board.o game.o position.o
	g++ main.cpp board.cpp game.cpp position.cpp -o tic_tac_toe

main.o: main.cpp
	g++ -c main.cpp

my_board.o: board.cpp
	g++ -c board.cpp

game.o: game.cpp
	g++ -c game.cpp

position.o: position.cpp
	g++ -c position.cpp

clean:
	rm *o tic_tac_toe
