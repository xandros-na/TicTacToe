#pragma once
#include "board.h"
#include "position.h"
#include <string>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27
#define SPACE 32

namespace game {

	struct Player {
		std::string name;
		unsigned char symbol;
	};

	class TicTacToe {
	private:
		board::Board m_board;
		position::Position m_position;
		Player m_p1;
		Player m_p2;
		bool m_exited;
		int m_turn;
		std::vector<position::Position> m_winning_positions;
		void re_draw();
		void draw_winning_combination();
		bool won(position::Position& position);
	public:
		TicTacToe(board::Board& board, Player& p1, Player& p2);
		void start();
		bool play_again();
		void reset();
	};

	void show_menu(Player& p1, Player& p2);
	void thanks();



}
