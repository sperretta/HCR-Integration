#include "debug_output.hpp"

DebugOutput::DebugOutput(){

}

bool DebugOutput::beginDebug(GameEngine* newGameEngine){
	gameEngine = newGameEngine;
	return 1;
}

void DebugOutput::print_game_board(const std::vector<Piece>& gameBoard){
	for(unsigned y=0; y<5; y++){
		for(unsigned x=0; x<9; x++){
			Direction directions = gameEngine->valid_directions(x, y);
			if(directions & ul) std::cerr << "  \\" ;
			if(directions & u) std::cerr << " | " ;
			if(directions & ur) std::cerr << "/  ";
		}
		std::cerr << std::endl;
		for(unsigned x=0; x<9; x++){
			Direction directions = gameEngine->valid_directions(x, y);
			if(directions & l) std::cerr << "--";
			if(gameBoard.at(on(x,y)) == p1) std::cerr << " x";	
			if(gameBoard.at(on(x,y)) == p2) std::cerr << " o";
			if(gameBoard.at(on(x,y)) == none) std::cerr << "  ";
			if(directions & r) std::cerr << "--";
		}
		std::cerr << std::endl;
		for(unsigned x=0; x<9; x++){
			Direction directions = gameEngine->valid_directions(x, y);
			if(directions & dl) std::cerr << "  /";
			if(directions & d) std::cerr << " | ";
			if(directions & dr) std::cerr << "\\  ";
		}
		std::cerr<<std::endl;
	}
}

void DebugOutput::print_game_board(){
	for(unsigned y=0; y<5; y++){
		for(unsigned x=0; x<9; x++){
			Direction directions = gameEngine->valid_directions(x, y);
			if(directions & ul) std::cerr << "  \\" ;
			if(directions & u) std::cerr << " | " ;
			if(directions & ur) std::cerr << "/  ";
		}
		std::cerr << std::endl;
		for(unsigned x=0; x<9; x++){
			Direction directions = gameEngine->valid_directions(x, y);
			if(directions & l) std::cerr << "--";
			if(gameEngine->get_player(x,y) == p1) std::cerr << " x";	
			if(gameEngine->get_player(x,y) == p2) std::cerr << " o";
			if(gameEngine->get_player(x,y) == none) std::cerr << "  ";
			if(directions & r) std::cerr << "--";
		}
		std::cerr << std::endl;
		for(unsigned x=0; x<9; x++){
			Direction directions = gameEngine->valid_directions(x, y);
			if(directions & dl) std::cerr << "  /";
			if(directions & d) std::cerr << " | ";
			if(directions & dr) std::cerr << "\\  ";
		}
		std::cerr<<std::endl;
	}
}


//Not sure if this function works properly anymore
//Avoid using - let me know if you need it fixed 
void DebugOutput::print_valid_moves(){	
	std::cerr << "Valid moves are: " << std::endl;
	for(unsigned x=0; x<9; x++){
		for(unsigned y=0; y<5; y++){
			//replace this with vector of moves for readability?
			for(unsigned dir=0; dir<=ur; dir*=2){
				if(gameEngine->move_valid(x,y,(Direction)dir,(Direction)dir)){
					std::cerr << "x: " << x << " y: " << y << " mov: " << dir << " cap: " << dir << std::endl;
				}
				if(gameEngine->move_valid(x,y,(Direction)dir,opposite((Direction)dir))){
					std::cerr << "x: " << x << " y: " << y << " mov: " << dir << " cap: " << opposite((Direction)dir) << std::endl;
				}
			if(dir==0) dir++;	
			}		
		}
	}
}
