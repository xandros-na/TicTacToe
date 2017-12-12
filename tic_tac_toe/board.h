#pragma once
#include <vector>
#include "position.h"

#define SQUARE_WIDTH 5
#define SQUARE_LENGTH 7

namespace board {

	class Board {
	private:
		std::vector<std::vector<char>> m_board;
		void draw_outer();
		void draw_symbol(int i, int j, int k, int x);
		void bounds_check(position::Position& position);
	public:
		int m_width;
		int m_height;
		Board(int width, int height);
		int size();
		std::vector<char>& operator[](int);
		void re_draw(position::Position& position);
		void re_draw(std::vector<position::Position>& positions);
		bool is_empty(position::Position& position);
		bool is_full();
		void make_empty();
	};

	std::vector<char>* begin(Board& r);
	std::vector<char>* end(Board& r);

}
