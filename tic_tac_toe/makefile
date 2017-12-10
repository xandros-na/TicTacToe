CC=g++
CFLAGS=-c -Wall
all: tic_tac_toe

tic_tac_toe: main.o my_board.o game.o
	g++ main.cpp my_board.cpp game.cpp -o tic_tac_toe

main.o: main.cpp
	g++ -c main.cpp

my_board.o: my_board.cpp
	g++ -c my_board.cpp

game.o: game.cpp
	g++ -c game.cpp

clean:
	rm *o tic_tac_toe
