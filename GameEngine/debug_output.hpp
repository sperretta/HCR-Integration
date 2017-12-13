#ifndef DEBUG_OUTPUT_HPP
#define DEBUG_OUTPUT_HPP

#include <iostream>
#include "game_engine.hpp"

class DebugOutput{
	GameEngine* gameEngine;
public:
	DebugOutput();
	bool beginDebug(GameEngine* gameEngine);
	void print_game_board();
    void print_game_board(const std::vector<Piece>& gameBoard);
	void print_valid_moves();
};



#endif
