#include "ai.hpp"

void AI::add_child(std::shared_ptr<GameNode> parent, Move move){
    std::shared_ptr<GameNode> childNode = std::make_shared<GameNode>();
    parent->children.push_back(childNode);  
    childNode->parent = parent;
    childNode->depth = parent->depth+1;
    childNode->move = move;
    childNode->game = parent->game;
    childNode->game.move_piece(move);
    unsigned robotPieces =  childNode->game.count_pieces(robotPlayer);
    unsigned opponentPieces =  childNode->game.count_pieces(opponentPlayer);
    float pieceDifference = (float)robotPieces-opponentPieces;
    float totalPieces = (float)robotPieces+opponentPieces;
    childNode->heuristic = pieceDifference/totalPieces;
}

AI::AI(GameEngine *game, Piece aiPlayer){
    mainGame = game;
    robotPlayer = aiPlayer;
    opponentPlayer = game->other(robotPlayer);
    for(unsigned x=0; x<9; x++){
        for(unsigned y=0; y<5; y++){
            //You can pass turn on any square
            Move passTurn(x,y,no_dir,no_dir);
            moves.push_back(passTurn);
            for(unsigned dir=1; dir<=dr; dir*=2){
                Direction direction = (Direction) dir;
                if(game->valid_directions(x,y) & direction){
                    Move approachMove(x,y,direction,direction);
                    moves.push_back(approachMove);
                    if(dir_move(x,y,opposite(direction))!=OFF_BOARD){
                        Move withdrawMove(x,y,direction, opposite(direction));
                        moves.push_back(withdrawMove);
                    }
                }
            }
        }
    }
    return;
}

std::vector<Move> AI::find_move(unsigned maxDepth){
    
    rootNode = std::make_shared<GameNode>();
    rootNode->depth = 0;
    //ideally should be infinity
    rootNode->heuristic = 0;
    rootNode->game=*mainGame;
    bestNode = rootNode;
    for(unsigned i=0; i<maxDepth; i++){
        build_game_tree(i, rootNode);
    }
    //search_game_tree(maxDepth, rootNode);
    minimax_tree_search(maxDepth, rootNode);
    std::vector<Move> moveList;
    fill_move_list(rootNode->bestLeaf,moveList);
    return moveList;
}

void AI::build_game_tree(unsigned maxDepth, std::shared_ptr<GameNode> currentNode){
    if(currentNode->depth < maxDepth){
        for(unsigned i=0; i<currentNode->children.size(); i++){
            build_game_tree(maxDepth, currentNode->children.at(i));
        }
    }
    if(currentNode->depth == maxDepth){
        for(unsigned j=0; j<moves.size(); j++){
            if(currentNode->game.move_valid(moves.at(j))){
                add_child(currentNode, moves.at(j));
            }
        }
    }
}

void AI::search_game_tree(unsigned maxDepth, std::shared_ptr<GameNode> currentNode){
    if(currentNode->depth < maxDepth){
        for(unsigned i=0; i<currentNode->children.size(); i++){
            search_game_tree(maxDepth, currentNode->children.at(i));
        }
    }
    if(currentNode->depth == maxDepth){
        if(currentNode->get_player() == robotPlayer){
            if(currentNode->heuristic > bestNode->heuristic){
                bestNode=currentNode;
            }
        }
        if(currentNode->get_player() == opponentPlayer){
            if(currentNode->heuristic < bestNode->heuristic){
                bestNode=currentNode;
            }
        }
    }
}

void AI::minimax_tree_search(unsigned maxDepth, std::shared_ptr<GameNode> currentNode){
    if(currentNode->depth < maxDepth){
        for(unsigned i=0; i<currentNode->children.size(); i++){
            minimax_tree_search(maxDepth, currentNode->children.at(i));
        }
        if(currentNode->children.size()!=0){
            minimax_propagate(currentNode);
        }
    }
    if(currentNode->depth == maxDepth|| currentNode->children.size()==0){
        minimax_leaves(currentNode);
    }
}

void AI::minimax_propagate(std::shared_ptr<GameNode> currentNode){
    if(currentNode == rootNode) return;
    if(currentNode->parent->bestLeaf){
        //if you are current player, then maximise
        if(currentNode->get_player()==robotPlayer){
            if(currentNode->bestLeaf->heuristic > currentNode->parent->bestLeaf->heuristic){
                currentNode->parent->bestLeaf = currentNode->bestLeaf;
                return;
            }
        }
        //if opponent is current plyaer then minimise
        else if(currentNode->get_player()==opponentPlayer){
            if(currentNode->bestLeaf->heuristic < currentNode->parent->bestLeaf->heuristic){
                currentNode->parent->bestLeaf = currentNode->bestLeaf;
                return;
            }
        }
    }
    //If this the first child inspected there is no comparison to make
    else{
        currentNode->parent->bestLeaf = currentNode->bestLeaf;
    }
}

void AI::minimax_leaves(std::shared_ptr<GameNode> currentNode){
    if(currentNode == rootNode) return;
    if(currentNode->parent->bestLeaf){
        //if you are current player, then maximise
        if(currentNode->get_player()==robotPlayer){
            if(currentNode->heuristic > currentNode->parent->bestLeaf->heuristic){
                currentNode->parent->bestLeaf = currentNode;
                return;
            }
        }
        //if opponent is current plyaer then minimise
        else if(currentNode->get_player()==opponentPlayer){
            if(currentNode->heuristic < currentNode->parent->bestLeaf->heuristic){
                currentNode->parent->bestLeaf = currentNode;
                return;
            }
        }
    }
    //If this the first child inspected there is no comparison to make
    else{
        currentNode->parent->bestLeaf = currentNode;
    }

}

void AI::fill_move_list(std::shared_ptr<GameNode> currentNode, std::vector<Move> &moveList){
    if(currentNode==rootNode){
        std::cerr<<"Cannot return move from rootNode"<<std::endl;
    }
    else if(currentNode->depth == 1){
        moveList.push_back(currentNode->move);
        return;
    }
    else if(currentNode->depth > 1){
        fill_move_list(currentNode->parent, moveList);    
        moveList.push_back(currentNode->move);
    }   
    return;
}

Piece GameNode::get_player(){
    return parent->game.get_current_player();
}

