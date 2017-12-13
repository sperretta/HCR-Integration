#include "game_interface.hpp"

//Returns true if a valid move has been detected, otherwise returns false
ErrorCode GameInterface::detect_move(std::vector<Piece> gameBoard, Move& detectedMove){
    if (gameBoard == gameEngine.get_board()){
        return noMove;
    }
    unsigned oldX=OFF_BOARD, oldY=OFF_BOARD;
    unsigned newX=OFF_BOARD, newY=OFF_BOARD;
    for(unsigned x=0; x<9; x++){
        for(unsigned y=0; y<5; y++){
            if(gameEngine.get_player(x,y)==gameEngine.get_current_player()){
                if(gameBoard.at(on(x,y)) == none){
                    //if oldX has already been set then, an extra piece has gone missing
                    if(oldX != OFF_BOARD){
                        return pieceMissing;
                    }
                    oldX = x;
                    oldY = y;
                }
            }
            else if(gameEngine.get_player(x,y) == none){
                if(gameBoard.at(on(x,y)) == gameEngine.get_current_player()){
                    //If newX has already been set, with found an extra piece that has crept onto the board
                    if(newX != OFF_BOARD){
                        return pieceAdded;
                    }
                    newX = x;
                    newY = y;
                }
            }
        }
    }
    if(oldX == OFF_BOARD){
        return pieceAdded;
    }
    if(newX == OFF_BOARD){
        return pieceMissing;
    }
    Direction mov_dir = no_dir;
    for(unsigned dir=1; dir<=dr; dir*=2){
        Direction direction = (Direction) dir;
        if(dir_move(oldX, oldY, direction) == on(newX, newY)){
            mov_dir = direction;
        }
    }
    if(mov_dir == no_dir){
        return invalidDirection;
    }
    Move approachMove(oldX, oldY, mov_dir, mov_dir);
    Move withdrawMove(oldX, oldY, mov_dir, opposite(mov_dir));
    GameEngine approachGame = gameEngine;
    GameEngine withdrawGame = gameEngine;
    bool withdrawlPartiallyValid = false;
    bool approachPartiallyValid = false;
    if(approachGame.move_valid(approachMove)){
        detectedMove = approachMove;
        approachGame.make_move(approachMove);
        if(approachGame.get_board() == gameBoard){
            return validMove;
        }
        else{
            approachPartiallyValid = true;
            std::cout << "APPROACHGAME START" << std::endl;
            print_board( approachGame.get_board() );
            std::cout << "APPROACHGAME END" << std::endl;
        }
    }
    if(withdrawGame.move_valid(withdrawMove)){
        detectedMove = withdrawMove;
        withdrawGame.make_move(withdrawMove);
        if(withdrawGame.get_board() == gameBoard){
            return validMove;
        }
        else{
            withdrawlPartiallyValid = true;
        }
    }
    if(approachPartiallyValid && withdrawlPartiallyValid){
        return bothPartial;
    }
    else if(approachPartiallyValid){
        return approachPartial;
    }
    else if(withdrawlPartiallyValid){
        return withdrawlPartial;
    }
    return unknownError;
}

GameInfo GameInterface::handle_user_move(std::vector<Piece> gameBoard){
    Move userMove;
    ErrorCode detected;
    GameInfo gameInfo;
    detected = detect_move(gameBoard, userMove);
    if(detected==validMove){
        gameEngine.make_move(userMove);
        gameInfo.moveStatus = success;
        return gameInfo;
    }
    else if(detected==bothPartial){
        //Need to determine whether intended to withdraw or approach
        gameInfo.moveStatus = bothPartial;
        gameInfo.clarificationNeeded = true;
        gameInfo.partialMove = true;
        return gameInfo;
    }
    else if(detected==withdrawlPartial){
        gameInfo.moveStatus = withdrawlPartial;
        return gameInfo;
    }
    else if(detected==approachPartial){
        //Get use to remove correct pieces
        gameInfo.moveStatus = approachPartial;
        return gameInfo;
    }
    else if(detected==noMove){
        gameInfo.moveStatus = noMove;
        //Wait for move
        return gameInfo;
    }
    else{
        gameInfo.moveStatus = invalidMove;
        return gameInfo;
    }

}

GameInterface::GameInterface(Piece _robot, unsigned _aiDifficulty):ai(&gameEngine, _robot){
    aiDifficulty = _aiDifficulty;
    robot = _robot;
    human = gameEngine.other(robot);
}

void GameInterface::enable_debug(){
    debugEnable =true;
    debugOutput.beginDebug(&gameEngine);
    debugOutput.print_game_board();
    return;
}

void GameInterface::disable_debug(){
    debugEnable = false;
    return;
}

GameInfo GameInterface::run_game(std::vector<Piece> gameBoard){
    GameInfo gameInfo;
    if(gameEngine.get_current_player()==human){
        gameInfo = handle_user_move(gameBoard);
        if(gameInfo.moveStatus==success){
            if(debugEnable)debugOutput.print_game_board();
            return gameInfo;
        }
        else{
            return gameInfo;
        }
    }
    else if(gameEngine.get_current_player()==robot){
        gameInfo = handle_ai_move(gameBoard);
        if(gameInfo.moveStatus==success){
            if(debugEnable)debugOutput.print_game_board();
            return gameInfo;
        } 
        else{
            return gameInfo;
        }
    }
    return gameInfo;
}

GameInfo GameInterface::handle_ai_move(std::vector<Piece> gameBoard){
    GameInfo gameInfo;
    std::vector<Move> moveList;
    moveList = ai.find_move(aiDifficulty);
    if(moveList.at(0).was_pass()){
        gameEngine.make_move(moveList.at(0));
        gameInfo.pass = true;
        return gameInfo;
    }
    Move detectedMove;
    gameInfo.moveStatus = detect_move(gameBoard, detectedMove);
    if(gameInfo.moveStatus==validMove){
        if(detectedMove.equals(moveList.at(0))){
            //all is good we can move on with the game
            gameEngine.make_move(moveList.at(0));
            gameInfo.moveStatus = success;
            return gameInfo;
        }
        else{
        //get them to reset the board
        gameInfo.targetBoard = gameEngine.get_board();
        return gameInfo;
        }
    }
    //If they got the move right then show the ones that need to be deleted
    else if(gameInfo.moveStatus==bothPartial||gameInfo.moveStatus==withdrawlPartial||gameInfo.moveStatus==approachPartial){
        GameEngine tempEngine = gameEngine;
        if(detectedMove.equals(moveList.at(0))){
            tempEngine.make_move(moveList.at(0));
            std::vector<unsigned> captures;
            gameInfo.captures = find_captures(gameBoard);
            return gameInfo;
        }
        else{
        gameInfo.targetBoard = gameEngine.get_board();
            return gameInfo;
        }
    }
    else{
        gameInfo.displayMove = moveList.at(0);
        return gameInfo;
    }
}


bool GameInterface::finished(){
    return gameEngine.finished();
}

Piece GameInterface::get_current_player(){
    return gameEngine.get_current_player();
}

std::vector<unsigned> GameInterface::find_captures(std::vector<Piece> gameBoard){
    std::vector<unsigned> captures;
    for(unsigned x=0; x<9; x++){
        for(unsigned y=0; y<5; y++){
            if(gameEngine.get_player(x,y)==gameEngine.get_opponent()){
                if(gameBoard.at(on(x,y)) == none){
                    captures.push_back(on(x,y));
                }
            }
        }
    } 
    return captures;   
}

void GameInterface::pass_turn(){
    gameEngine.pass_turn();
}

void GameInterface::print_board( const std::vector<Piece>& gameBoard )
{
    if(debugEnable)
    {
        debugOutput.print_game_board( gameBoard );
    }
}
