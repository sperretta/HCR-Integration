#include "game_engine.hpp"
#include "enum.hpp"
#include "debug_output.hpp"
#include "ai.hpp"

int main(){
	std::cerr << "Starting game" << std::endl;
	GameEngine gameEngine;
	std::cerr << "Created game engine" << std::endl;
    Piece human = p1;
    Piece robot = p2;
    AI ai(&gameEngine, robot);
    std::cerr << "Attached AI to game engine as player 2" << std::endl;
	DebugOutput debugOutput;
	if(debugOutput.beginDebug(&gameEngine)){
		std::cerr << "Opened debug interface" << std::endl;
	}
	else std::cerr << "Could not open debug interface" << std::endl;
	debugOutput.print_game_board();

	while(!gameEngine.finished()){
	    //debugOutput.print_valid_moves();
	    while(gameEngine.get_current_player()==human){
            gameEngine.offer_move();
	        debugOutput.print_game_board();
            if(gameEngine.finished()) break;
        }
        if(gameEngine.finished()) break;
        while(gameEngine.get_current_player()==robot){
            std::vector<Move> moveList;
            moveList  = ai.find_move(6);
            for(unsigned j=0; j<moveList.size(); j++){
                gameEngine.make_move(moveList.at(j));
                debugOutput.print_game_board();
                if(gameEngine.get_current_player()!=robot)break;
                if(gameEngine.finished())break;
            }
            if(gameEngine.finished())break;
        }
	}
	std::cerr<< "Game Over!" << std::endl;
    std::cerr<< "Player " << gameEngine.get_current_player() << " wins!" << std::endl;
	return 0;
}




