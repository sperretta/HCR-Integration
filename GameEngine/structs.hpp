#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include "enum.hpp"
#include <vector>

struct Move{
    public:
	    unsigned x;
	    unsigned y;
	    Direction mov_dir;
	    Direction cap_dir;
	    Move(unsigned _x, unsigned _y, Direction _mov_dir, Direction _cap_dir);	
        Move();
        bool was_pass();
        bool equals(Move move2);
};

struct GameInfo{
        Move moveToDisplay; 
        bool finished = false;
        bool pass = false;
        std::vector<Piece> targetBoard;
        Move detectedMove;
        Move displayMove;
        std::vector<unsigned> captures;
        ErrorCode moveStatus = unknownError;
        bool partialMove = false;
        bool moveDetected = false;
        bool clarificationNeeded =false;

};

#endif
