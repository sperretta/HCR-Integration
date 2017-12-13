#ifndef AI_HPP
#define AI_HPP

#include <memory>
#include <ostream>
#include "game_engine.hpp"
#include "enum.hpp"
#include "structs.hpp"

class GameNode;
class AI;

class GameNode{
    friend class AI;
    private:
        float heuristic;    
        std::vector<std::shared_ptr<GameNode> > children;
        std::shared_ptr <GameNode> parent;
        std::shared_ptr <GameNode> bestLeaf;
        Move move;
        unsigned depth;
        GameEngine game;
        Piece get_player();
};

class AI{
    private:

        void add_child(std::shared_ptr<GameNode> parent, Move move);
        std::vector<Move> moves;
        std::shared_ptr<GameNode> rootNode;
        std::shared_ptr<GameNode> bestNode;
        Piece robotPlayer;
        Piece opponentPlayer;
        GameEngine *mainGame;
        void search_game_tree(
                unsigned maxDepth, 
                std::shared_ptr<GameNode> currentNode);
      
        void minimax_tree_search(
                unsigned maxDepth, 
                std::shared_ptr<GameNode> currentNode);
       
        void minimax_propagate(
                std::shared_ptr<GameNode> currentNode);
     
        void minimax_leaves(
                std::shared_ptr<GameNode> currentNode);
        
        void build_game_tree(
                unsigned maxDepth, 
                std::shared_ptr<GameNode> currentNode);
        
        void fill_move_list(
                std::shared_ptr<GameNode> currentNode, 
                std::vector<Move> &moveList);


    public:
        std::vector<Move> find_move(unsigned maxDepth);
        AI(GameEngine *game, Piece aiPlayer);
};

#endif
