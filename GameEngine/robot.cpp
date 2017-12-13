#include "game_interface.hpp"
#include <vector>
#include <iostream>
#include <fstream>
/*
int global_counter = 0;

std::vector<Piece> get_camera(){
    std::vector<Piece> gameBoard;
    std::string filename;
    std::cout << "Enter camera filename: ";
    std::getline(std::cin, filename);
    std::ifstream file(filename);
    std::string value;
    if(!file.is_open()){
        std::cerr << "Could not open file " << filename << std::endl;
        return gameBoard;
    }
    int lineNumber =0;
    if(lineNumber == global_counter){

    }
    while(getline(file, value, ',')){
        Piece piece = (Piece) std::atoi(value.c_str());
        gameBoard.push_back(piece);
    }
    global_counter++;
    file.close();
    return gameBoard;
}
*/

int main(){
    unsigned aiDifficulty = 3;
    GameInterface gameInterface(p2, aiDifficulty);
    gameInterface.enable_debug();
    while(1){
        std::vector<Piece> gameBoard;// = get_camera();
        GameInfo gameInfo;
        if(!gameInterface.finished()){
            gameInfo = gameInterface.run_game(gameBoard);
        }
        else{
            std::cerr<< "Game Over!" << std::endl;
            std::cerr<< "Player " << gameInterface.get_current_player() << " wins!" << std::endl;
            break;
        }
    }
    return 0;
}

