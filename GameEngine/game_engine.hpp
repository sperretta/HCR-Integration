#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <vector>
#include "enum.hpp"
#include "user_io.hpp"
#include "structs.hpp"
#include <fstream>

class GameEngine{
	std::vector < Piece > board;
	Piece currentPlayer;
	Piece opponent;
	std::vector <Move> turnLog;
public:
	std::vector <Move> gameLog;
	GameEngine();
	bool move_piece(unsigned x, unsigned y, Direction mov_dir, Direction cap_dir);
    bool move_piece(Move move);
	Direction valid_directions(unsigned x, unsigned y);
	Direction capturable_directions(unsigned x, unsigned y);
	Direction movable_directions(unsigned x, unsigned y);
	Piece other(Piece player);
	void print_game_board();
	bool can_capture();
	Piece get_player(unsigned x, unsigned y);
	bool offer_move();
    bool make_move(Move move);
	bool move_valid(unsigned x, unsigned y, Direction direction, Direction cap_dir);
    bool move_valid(Move move);
	int remove_captured_pieces(unsigned x, unsigned  y, Direction direction, Direction capture);
    //int remove_captured_pieces(Move move);
	int recursive_remove(unsigned n, Direction dir);
	Direction check_capturable(unsigned x, unsigned y, Direction dir);	
	int change_player();
	unsigned count_pieces(Piece player);
	Piece get_current_player();
    Piece get_opponent();
    bool finished();
	void record_move(unsigned x, unsigned y, Direction mov_dir, Direction cap_dir);
    void record_move(Move move);
	void save_game_log();
	bool return_to_intersection(unsigned x, unsigned y, Direction dir);
    std::vector<Piece> get_board(){return board;};
    void pass_turn();
};


unsigned on(unsigned x, unsigned y);
Direction opposite(Direction dir); 

unsigned dir_move(unsigned x, unsigned y, Direction dir);
#endif

