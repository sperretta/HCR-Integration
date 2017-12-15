#ifndef GAME_INTERFACE_HPP
#define GAME_INTERFACE_HPP

#include "debug_output.hpp"
#include "game_engine.hpp"
#include "structs.hpp"
#include "enum.hpp"
#include "ai.hpp"
#include <fstream>

class GameInterface{

    private:
        GameEngine gameEngine;
        ErrorCode detect_move(std::vector<Piece> gameBoard, Move& detectedMove);
        Piece human;
        Piece robot;
        unsigned aiDifficulty;
        bool debugEnable = false;
        std::vector<unsigned> capturedPieces;
        AI ai;
        DebugOutput debugOutput;
        GameInfo handle_ai_move(std::vector<Piece> gameBoard);
        GameInfo handle_user_move(std::vector<Piece> gameBoard);
        std::vector<unsigned> find_captures(std::vector<Piece> gameBoard, Move move);

    public:
        GameInterface(Piece _robot, unsigned _aiDifficulty);
        Piece get_current_player();
        bool finished();
        void enable_debug();
        void disable_debug();
        GameInfo run_game(std::vector<Piece> gameBoard);
        void pass_turn();
        void print_board( const std::vector<Piece>& gameBoard );
	void save_log_to_file();

};



#endif

