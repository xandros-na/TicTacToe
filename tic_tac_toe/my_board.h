#pragma once
#include <vector>

#define SQUARE_WIDTH 5
#define SQUARE_LENGTH 7

struct Position {
	int x;
	int y;
};

class Board {
private:
	std::vector<std::vector<char>> _m_board;
	void draw_outer();
	void draw_position(bool, int, int);
	void draw_symbol_mid_sq(int i, int j, int k, int x);
	void bounds_check(Position& position);
public:
	int _m_width;
	int _m_height;
	Board(int width, int height);
	int size();
	std::vector<char>& operator[](int);
	void re_draw(Position& position);
	void re_draw(std::vector<Position>& positions);
	bool is_empty(Position& position);
	bool is_full();
	void make_empty();
};

struct compare {
public:
	compare(Position& pos);
	bool operator()(Position& pos);
private:
	Position _my_pos;
};
std::vector<char>* begin(Board& r);
std::vector<char>* end(Board& r);