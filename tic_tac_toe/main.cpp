#include "my_board.h"
#include "game.h"

bool compare(Position& p1, Position& p2) {
	if (p1.x == p2.x) {
		return p1.y < p2.y;
	}
	return p1.x < p2.x;
}

int main() {
	
	Board board = Board(3, 3);
	
	Player p1;
	Player p2;
	Position position = { 0, 0 };
	show_menu(p1, p2);

	Game game = Game(board, position, p1, p2);
	game.start();
	
	while (game.play_again()) {
		game.reset();
		game.start();
	}
	thanks();
	
	return 0;
}
