#include "game.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <chrono>
#include <thread>
#include <assert.h>

namespace game {

	TicTacToe::TicTacToe(board::Board& board, Player& p1, Player& p2) : m_board{ board }, m_p1{ p1.name, p1.symbol }, m_p2{ p2.name, p2.symbol }
	{
		assert(m_board.get_height() == 3 && m_board.get_width() == 3);

		m_position = { 0, 0 };
		m_turn = 0;
		m_exited = false;
		m_winning_positions = {};
	};

	void TicTacToe::re_draw() {
		std::system("CLS");
		m_board.re_draw(m_position);

		if ((!won(m_position)) && (!m_board.is_full())) {
			std::string turn_msg = m_turn == 0 ? m_p1.name : m_p2.name;
			std::cout << turn_msg << "'s turn";
		}
	}

	void TicTacToe::start() {
		int c = 0;
		re_draw();

		while ((!won(m_position)) && (!m_board.is_full()))
		{
			c = 0;

			switch ((c = _getch())) {
			case KEY_UP:
				m_position.y--;
				re_draw();
				break;
			case KEY_DOWN:
				m_position.y++;
				re_draw();
				break;
			case KEY_LEFT:
				m_position.x--;
				re_draw();
				break;
			case KEY_RIGHT:
				m_position.x++;
				re_draw();
				break;
			case SPACE:
				if (m_turn == 0) {
					if (m_board.is_empty(m_position)) {
						m_board[m_position.x][m_position.y] = m_p1.symbol;
						m_turn = 1;
					}
				}
				else {
					if (m_board.is_empty(m_position)) {
						m_board[m_position.x][m_position.y] = m_p2.symbol;
						m_turn = 0;
					}
				}
				re_draw();
				break;
			case ESC:
				m_exited = true;
				return;
			default:
				break;
			}
		}
	}

	bool TicTacToe::play_again() {

		if (m_exited) {
			return false;
		}

		std::cout << std::endl;
		if (won(m_position)) {
			// turn was flipped on a winning move so print out the other player's name
			draw_winning_combination();
			std::string winner = m_turn == 0 ? m_p2.name : m_p1.name;
			std::cout << winner << " wins!!" << std::endl;
		}
		else {
			std::cout << "It's a tie!" << std::endl;
		}

		std::cout << "Press ESC to quit." << std::endl;
		std::cout << "Press SPACE to play again." << std::endl;

		int c = 0;

		while (true)
		{
			c = 0;

			switch ((c = _getch())) {
			case ESC:
				return false;
			case SPACE:

				return true;
			default:
				break;
			}
		}
	}

	void TicTacToe::reset() {
		m_board.make_empty();
		m_position.x = 0;
		m_position.y = 0;
		m_exited = false;
		m_winning_positions = {};
		m_position = { 0, 0 };
	}

	void TicTacToe::draw_winning_combination() {
		std::system("CLS");
		m_board.re_draw(m_winning_positions);
	}

	bool TicTacToe::won(position::Position& position) {

		if (m_board.is_empty(position)) {
			return false;
		}

		char c = m_board[position.x][position.y];

		// check vertically
		int matches = 0;
		m_winning_positions = {};
		for (int i = 0; i < m_board.size(); i++) {
			if (c == m_board[position.x][i]) {
				matches++;
				position::Position p = { position.x, i };
				m_winning_positions.push_back(p);
			}
		}


		if (matches == 3) {
			return true;
		}

		//check horizontally
		matches = 0;
		m_winning_positions = {};
		for (int i = 0; i < m_board.size(); i++) {
			if (c == m_board[i][position.y]) {
				matches++;
				position::Position p = { i, position.y };
				m_winning_positions.push_back(p);
			}
		}

		if (matches == 3) {
			return true;
		}

		// check diagonal
		/*
		upper left to lower right \
		*/
		matches = 0;
		m_winning_positions = {};
		for (int i = 0; i < m_board.size(); i++) {
			if (c == m_board[i][i]) {
				matches++;
				position::Position p = { i, i };
				m_winning_positions.push_back(p);
			}
		}

		if (matches == 3) {
			return true;
		}

		// check diagonal
		/*
		lower left to upper right /
		*/
		matches = 0;
		m_winning_positions = {};
		int j = 0;
		for (int i = m_board.size() - 1; i > -1; i--) {
			if (c == m_board[j][i]) {
				matches++;
				position::Position p = { j, i };
				m_winning_positions.push_back(p);
			}
			j++;
		}

		if (matches == 3) {
			return true;
		}
		return false;
	}

	void show_menu(Player& p1, Player& p2) {

		std::cout << "TIC TAC TOE" << std::endl;
		std::cout << "Press arrow keys to move around the board." << std::endl;
		std::cout << "Press SPACE to put X and O's on a square." << std::endl;
		std::cout << "Press ESC to quit." << std::endl;
		std::cout << std::endl;

		std::string p1_name;
		std::string p2_name;

		std::cout << "Enter player one's name (X): ";
		std::cin >> p1_name;
		std::cout << "\nEnter player two's name (O): ";
		std::cin >> p2_name;

		std::cin.clear();
		std::cin.ignore();

		p1.name = p1_name;
		p2.name = p2_name;
		p1.symbol = 'X';
		p2.symbol = 'O';

		std::system("CLS");

	}

	void thanks() {
		std::cout << std::endl;
		std::cout << "Thanks for playing!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}

}
