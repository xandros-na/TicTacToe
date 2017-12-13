#include "board.h"
#include "position.h"
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>


namespace board {

	Board::Board(int width, int height) : m_width{ width }, m_height{ height } {

		assert(width > 0 && height > 0);

		m_board.reserve(m_height);
		
		for (int i = 0; i < m_height; i++) {
			std::vector<char> rows;
			for (int j = 0; j < m_width; j++) {
				rows.push_back(' ');
			}
			m_board.push_back(rows);
		}
	}

	int Board::size() {
		return m_height;
	}

	int Board::get_height() {
		return m_height;
	}

	int Board::get_width() {
		return m_width;
	}

	void Board::draw_outer() {
		std::cout << "+";
		for (int i = 0; i < 8 * m_width; i++) {
			std::cout << "+";
		}
		std::cout << std::endl;
	}

	void Board::draw_symbol(int i, int j, int x, int y) {

		// if board at current position has the char and current position is middle
		auto ch = ((m_board[x][y] != ' ') && (i == SQUARE_LENGTH / 2) && (j == SQUARE_WIDTH / 2)) ? m_board[x][y] : ' ';
		std::cout << ch;
	}

	void Board::bounds_check(position::Position& position) {
		if (position.x < 0) {
			position.x++;
		}
		else if (position.x > m_height - 1) {
			position.x--;
		}
		else if (position.y < 0) {
			position.y++;
		}
		else if (position.y > m_width - 1) {
			position.y--;
		}
	}

	void Board::re_draw(std::vector<position::Position>& positions) {

		draw_outer();

		for (int h = 0; h < m_height; h++) {

			for (int j = 0; j < SQUARE_WIDTH; j++) {
				for (int k = 0; k < m_width; k++) {
					std::cout << "+";
					for (int i = 0; i < SQUARE_LENGTH; i++) {
						position::Position p = { k, h };
						position::compare _compare_functor = { p };
						if (std::find_if(positions.begin(), positions.end(), _compare_functor) != positions.end()) {
							if ((j == 0 || j == SQUARE_WIDTH - 1) || (i == 0 || i == SQUARE_LENGTH - 1)) {
								std::cout << "`";
							}
							else {
								draw_symbol(i, j, k, h);
							}
						}
						else {
							draw_symbol(i, j, k, h);
						}
					}
				}
				std::cout << "+" << std::endl;
			}
			draw_outer();
		}
	}

	void Board::re_draw(position::Position& position) {

		bounds_check(position);

		draw_outer();
		for (int h = 0; h < m_height; h++) {

			for (int j = 0; j < SQUARE_WIDTH; j++) {
				for (int k = 0; k < m_width; k++) {
					std::cout << "+";
					for (int i = 0; i < SQUARE_LENGTH; i++) {
						if (position.x == k && h == position.y) {
							if ((j == 0 || j == SQUARE_WIDTH - 1) || (i == 0 || i == SQUARE_LENGTH - 1)) {
								std::cout << "`";
							}
							else {
								draw_symbol(i, j, k, h);
							}
						}
						else {
							draw_symbol(i, j, k, h);
						}
					}
				}
				std::cout << "+" << std::endl;
			}
			draw_outer();
		}
	}

	bool Board::is_empty(position::Position& position) {
		return (m_board[position.x][position.y] == ' ');
	}

	bool Board::is_full() {
		int num_squares = m_width * m_height;
		int filled_squares = 0;

		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				if (m_board[i][j] != ' ') {
					filled_squares++;
				}
			}
		}
		return filled_squares == num_squares;
	}

	void Board::make_empty() {
		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				m_board[i][j] = ' ';
			}
		}
	}

	/*==========================
	just practicing overloading below
	pretty cool
	*/
	std::vector<char>& Board::operator[](int i) {
		return m_board[i];
	}

	std::vector<char>* begin(Board& r) {
		return r.size() ? &r[0] : nullptr;
	}

	std::vector<char>* end(Board& r) {
		return begin(r) + r.size();
	}


}
