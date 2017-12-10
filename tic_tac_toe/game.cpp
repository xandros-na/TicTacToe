#include "game.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <chrono>
#include <thread>

Game::Game(Board& board, Position& position, Player& p1, Player& p2) : _m_board{ board }, _m_position{ position.x, position.y }, _m_p1{p1.name, p1.symbol}, _m_p2{ p2.name, p2.symbol } 
{
	_m_turn = 0;
	_m_quit = false;
	_winning_positions = {};
};

void Game::_re_draw() {
	std::system("CLS");
	_m_board.re_draw(_m_position);
	
	if ((!won(_m_position)) && (!_m_board.is_full())) {
		std::string turn_msg = _m_turn == 0 ? _m_p1.name : _m_p2.name;
		std::cout << turn_msg << "'s turn";
	}
}

void Game::start() {
	int c = 0;
	_re_draw();

	while ((!won(_m_position)) && (!_m_board.is_full()))
	{
		c = 0;

		switch ((c = _getch())) {
		case KEY_UP:
			_m_position.x--;
			_re_draw();
			break;
		case KEY_DOWN:
			_m_position.x++;
			_re_draw();
			break;
		case KEY_LEFT:
			_m_position.y--;
			_re_draw();
			break;
		case KEY_RIGHT:
			_m_position.y++;
			_re_draw();
			break;
		case SPACE:
			if (_m_turn == 0) {
				if (_m_board.is_empty(_m_position)) {
					_m_board[_m_position.y][_m_position.x] = _m_p1.symbol;
					_m_turn = 1;
				}
			}
			else {
				if (_m_board.is_empty(_m_position)) {
					_m_board[_m_position.y][_m_position.x] = _m_p2.symbol;
					_m_turn = 0;
				}
			}
			_re_draw();
			break;
		case ESC:
			_m_quit = true;
			return;
		default:
			break;
		}
	}
}

bool Game::play_again() {

	if (_m_quit) {
		return false;
	}

	std::cout << std::endl;
	if (won(_m_position)) {
		// turn was flipped on a winning move so print out the other player's name
		_draw_winning_position();
		std::string winner = _m_turn == 0 ? _m_p2.name : _m_p1.name;
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

void Game::reset() {
	_m_board.make_empty();
	_m_position.x = 0;
	_m_position.y = 0;
	_m_quit = false;
	_winning_positions = {};
}

void Game::_draw_winning_position() {
	std::system("CLS");
	_m_board.re_draw(_winning_positions);
}

bool Game::won(Position& position) {

	if (_m_board.is_empty(position)) {
		return false;
	}

	char c = _m_board[position.y][position.x];

	// check vertically
	int matches = 0;
	_winning_positions = {};
	for (int i = 0; i < _m_board._m_height; i++) {
		if (c == _m_board[position.y][i]) {
			matches++;
			Position p = { position.y, i };
			_winning_positions.push_back(p);
		}
	}


	if (matches == 3) {
		return true;
	}

	//check horizontally
	matches = 0;
	_winning_positions = {};
	for (int i = 0; i < _m_board._m_width; i++) {
		if (c == _m_board[i][position.x]) {
			matches++;
			Position p = { i, position.x };
			_winning_positions.push_back(p);
		}
	}

	if (matches == 3) {
		return true;
	}

	// check diagonal
	/*
	\
	*/
	matches = 0;
	_winning_positions = {};
	for (int i = 0; i < _m_board._m_width; i++) {
		if (c == _m_board[i][i]) {
			matches++;
			Position p = { i, i };
			_winning_positions.push_back(p);
		}
	}

	if (matches == 3) {
		return true;
	}

	// check diagonal
	/*
	/
	*/
	matches = 0;
	_winning_positions = {};
	int j = 0;
	for (int i = _m_board._m_width-1; i > -1; i--) {
		if (c == _m_board[j][i]) {
			matches++;
			Position p = { j, i };
			_winning_positions.push_back(p);
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