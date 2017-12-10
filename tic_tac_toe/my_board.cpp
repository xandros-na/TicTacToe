#include "my_board.h"
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <unordered_map>

Board::Board(int width, int height) : _m_width{ width }, _m_height{ height } {

	assert(width > 0 && height > 0);
	
	_m_board.reserve(_m_height);
	for (int i=0; i<_m_height; i++) {
		std::vector<char> rows;
		for (int j = 0; j < _m_width; j++) {
			rows.push_back(' ');
		}
		_m_board.push_back(rows);
	}
}

int Board::size() {
	return _m_height;
}

void Board::draw_outer() {
	std::cout << "+";
	for (int i = 0; i < 8*_m_width; i++) {
		std::cout << "+";
	}
	std::cout << std::endl;
}

void Board::draw_symbol_mid_sq(int i, int j, int k, int x) {

	// if board at current position has the char and current position is middle
	auto ch = ((_m_board[k][x] != ' ') && (i == SQUARE_LENGTH / 2) && (j == SQUARE_WIDTH / 2)) ? _m_board[k][x] : ' ';
	std::cout << ch;
}

void Board::draw_position(bool correct_h, int x, int y) {
	/* draw from left to right:
	   for each row in a square of width 5
			for each vertical column of width + 1
				draw '+'
				if we are in (x, y) provided by user
					draw 10 'o's in the first and last row of the square
					draw 'o' in the first and last column of the square
			    else
					draw 10 spaces
	*/

	for (int j = 0; j < SQUARE_WIDTH; j++) {
		for (int k = 0; k < _m_width; k++) {
			std::cout << "+";
			for (int i = 0; i < SQUARE_LENGTH; i++) {
				if (y == k && correct_h) {
					//if ((j == 0 || j == SQ_WIDTH-1) || (i == 0 || i == SQ_LENGTH-1)) {
					if ((j == 0 || j == SQUARE_WIDTH - 1) || (i == 0 || i == SQUARE_LENGTH - 1)) {
						std::cout << "`";
					}
					else {
						draw_symbol_mid_sq(i, j, k, x);
					}
				}
				else {
					draw_symbol_mid_sq(i, j, k, x);
				}
			}
		}
		std::cout << "+" << std::endl;
	}
}

void Board::bounds_check(Position& position) {
	if (position.x < 0) {
		position.x++;
	}
	else if (position.x > _m_height - 1) {
		position.x--;
	}
	else if (position.y < 0) {
		position.y++;
	}
	else if (position.y > _m_width - 1) {
		position.y--;
	}
}

void Board::re_draw(std::vector<Position>& positions) {
	
	draw_outer();
	
	for (int h = 0; h < _m_height; h++) {

		for (int j = 0; j < SQUARE_WIDTH; j++) {
			for (int k = 0; k < _m_width; k++) {
				std::cout << "+";
				for (int i = 0; i < SQUARE_LENGTH; i++) {
					Position p = { k, h };
					compare _compare_functor = { p };
					if (std::find_if(positions.begin(), positions.end(), _compare_functor) != positions.end()) {
						if ((j == 0 || j == SQUARE_WIDTH - 1) || (i == 0 || i == SQUARE_LENGTH - 1)) {
							std::cout << "`";
						}
						else {
							draw_symbol_mid_sq(i, j, k, h);
						}
					}
					else {
						draw_symbol_mid_sq(i, j, k, h);
					}
				}
			}
			std::cout << "+" << std::endl;
		}
		draw_outer();
	}
}

void Board::re_draw(Position& position) {

	bounds_check(position);

	draw_outer();
	for (int h = 0; h < _m_height; h++) {
		
		for (int j = 0; j < SQUARE_WIDTH; j++) {
			for (int k = 0; k < _m_width; k++) {
				std::cout << "+";
				for (int i = 0; i < SQUARE_LENGTH; i++) {
					if (position.y == k && h == position.x) {
						if ((j == 0 || j == SQUARE_WIDTH - 1) || (i == 0 || i == SQUARE_LENGTH - 1)) {
							std::cout << "`";
						}
						else {
							draw_symbol_mid_sq(i, j, k, h);
						}
					}
					else {
						draw_symbol_mid_sq(i, j, k, h);
					}
				}
			}
			std::cout << "+" << std::endl;
		}
		draw_outer();
	}
}

bool Board::is_empty(Position& position) {
	return (_m_board[position.y][position.x] == ' ');
}

bool Board::is_full() {
	int num_squares = _m_width * _m_height;
	int filled_squares = 0;

	for (int i = 0; i < _m_height; i++) {
		for (int j = 0; j < _m_width; j++) {
			if (_m_board[i][j] != ' ') {
				filled_squares++;
			}
		}
	}
	return filled_squares == num_squares;
}

void Board::make_empty() {
	for (int i = 0; i < _m_height; i++) {
		for (int j = 0; j < _m_width; j++) {
			_m_board[i][j] = ' ';
		}
	}
}

/*
Cool functors!!
*/
compare::compare(Position& pos) : _my_pos {pos.x, pos.y} {}

bool compare::operator()(Position& pos) {
	return _my_pos.x == pos.x && _my_pos.y == pos.y;
}


/*========================== 
	just practicing overloading below
	pretty cool
*/ 
std::vector<char>& Board::operator[](int i) {
	return _m_board[i];
}

std::vector<char>* begin(Board& r) {
	return r.size() ? &r[0] : nullptr;
}

std::vector<char>* end(Board& r) {
	return begin(r) + r.size();
}

