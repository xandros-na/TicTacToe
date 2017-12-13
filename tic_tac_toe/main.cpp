#include "board.h"
#include "game.h"

int main() {
	
	board::Board my_board = board::Board(3, 3);
	
	game::Player p1;
	game::Player p2;
	position::Position position = { 0, 0 };
	game::show_menu(p1, p2);

	game::TicTacToe tic_tac_toe = game::TicTacToe(my_board, p1, p2);
	tic_tac_toe.start();
	
	while (tic_tac_toe.play_again()) {
		tic_tac_toe.reset();
		tic_tac_toe.start();
	}
	game::thanks();
	
	return 0;
}
