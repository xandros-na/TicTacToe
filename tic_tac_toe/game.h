#pragma once
#include "my_board.h"
#include <string>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27
#define SPACE 32

struct Player {
	std::string name;
	unsigned char symbol;
};

class Game {
private:
	Board _m_board;
	Position _m_position;
	Player _m_p1;
	Player _m_p2;
	bool _m_quit;
	int _m_turn;
	void _re_draw();
	void _draw_winning_position();
	std::vector<Position> _winning_positions;
public:
	Game(Board& board, Position& position, Player& p1, Player& p2);
	void start();
	bool won(Position& position);
	bool play_again();
	void reset();
};

void show_menu(Player& p1, Player& p2);
void thanks();

