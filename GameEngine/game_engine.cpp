#include "game_engine.hpp"

GameEngine::GameEngine(){
	board = {p1, p1, p1, p1, p1, p1, p1, p1, p1,
		p1, p1, p1, p1, p1, p1, p1, p1, p1,
		p1, p2, p1, p2, none, p1, p2, p1, p2,
		p2, p2, p2, p2, p2, p2, p2, p2, p2,
		p2, p2, p2, p2, p2, p2, p2, p2, p2};
	currentPlayer = p1;
	opponent = p2;
}

unsigned on(unsigned x, unsigned y){
    if(x >= 9 || y >=5) return OFF_BOARD;
    else return y*9+x;
}

unsigned dir_move(unsigned x, unsigned y, Direction dir){
	unsigned n = y*9+x;
	if( (y == 0) && ((dir==ul)|(dir==u)|(dir==ur))) return OFF_BOARD;
	if( (y == 4) && ((dir==dl)|(dir==d)|(dir==dr))) return OFF_BOARD;
	if( (x == 0) && ((dir==ul)|(dir==l)|(dir==dl))) return OFF_BOARD;
	if( (x == 8) && ((dir==ur)|(dir==r)|(dir==dr))) return OFF_BOARD;
	switch(dir){
		case u: return n-9;
		case d: return n+9;
		case l: return n-1;
		case r: return n+1;
		case ul: return n-10;
		case ur: return n-8;
		case dl: return n+8;
		case dr: return n+10;
		case no_dir: return n;
	}
}
unsigned dir_move(unsigned n, Direction dir){
	if(n == OFF_BOARD) return OFF_BOARD;
	unsigned x = n%9;
	unsigned y = (n-x)/9;
	if( (y == 0) && ((dir==ul)|(dir==u)|(dir==ur))) return OFF_BOARD;
	if( (y == 4) && ((dir==dl)|(dir==d)|(dir==dr))) return OFF_BOARD;
	if( (x == 0) && ((dir==ul)|(dir==l)|(dir==dl))) return OFF_BOARD;
	if( (x == 8) && ((dir==ur)|(dir==r)|(dir==dr))) return OFF_BOARD;
	switch(dir){
		case u: return n-9;
		case d: return n+9;
		case l: return n-1;
		case r: return n+1;
		case ul: return n-10;
		case ur: return n-8;
		case dl: return n+8;
		case dr: return n+10;
		case no_dir: return n;
	}
}

Direction opposite(Direction dir){
	switch(dir){
		case u: return d;
		case d: return u;
		case l: return r;
		case r: return l;
		case ul: return dr;
		case ur: return dl;
		case dl: return ur;
		case dr: return ul;
		case no_dir: return no_dir;
	}
}

Direction GameEngine::valid_directions(unsigned x, unsigned y){
	//All intersections are weak by default
	int validDirections = u|d|l|r;
	//Find strong intersections
	if((x+y)%2==0) validDirections |= ul|ur|dl|dr;
	//Deal with edge cases
	if(y==0) validDirections &= ~(ul|ur|u);
	else if(y==4) validDirections &= ~(dl|dr|d);
	if(x==0) validDirections &= ~(l|dl|ul);
	else if (x==8) validDirections &= ~(r|dr|ur);
	return (Direction)validDirections;
}

Direction GameEngine::capturable_directions(unsigned x, unsigned y){
	//Check if there is a piece at that position - if not, return
	Direction movableDirections = movable_directions(x,y);
	unsigned capturableDirections = 0;
	//For all directions
	if(movableDirections & u) capturableDirections |= check_capturable(x,y,u);
	if(movableDirections & d) capturableDirections |= check_capturable(x,y,d);
	if(movableDirections & l) capturableDirections |= check_capturable(x,y,l);
	if(movableDirections & r) capturableDirections |= check_capturable(x,y,r);
	if(movableDirections & ul) capturableDirections |= check_capturable(x,y,ul);
	if(movableDirections & ur) capturableDirections |= check_capturable(x,y,ur);
	if(movableDirections & dl) capturableDirections |= check_capturable(x,y,dl);
	if(movableDirections & dr) capturableDirections |= check_capturable(x,y,dr);
	return (Direction) capturableDirections;
}

Direction GameEngine::check_capturable(unsigned x, unsigned y, Direction dir){
	unsigned capturableDirections = 0;
	//Check for capture by approach
	unsigned approachN = dir_move(dir_move(x,y,dir),dir);
	if(approachN != OFF_BOARD){
		if(board.at(approachN) == opponent)capturableDirections |= dir; 
	}
	unsigned retreatN = dir_move(x,y,opposite(dir));
	if(retreatN != OFF_BOARD){
		if(board.at(retreatN) == opponent) capturableDirections |= dir;
	}
	//check that the square has not been visited before
	if(return_to_intersection(x,y,dir)) capturableDirections &= ~dir;
	return (Direction) capturableDirections;
}

Direction GameEngine::movable_directions(unsigned x, unsigned y){
	//If the space is empty or not yours, you can't move any pieces
	if(board.at(on(x,y)) != currentPlayer) return no_dir;

	Direction validDirections = valid_directions(x, y);
	int movableDirections = 0;
    for(unsigned direction=1; direction<=dr; direction*=2){
        Direction dir = (Direction) direction;
        if((validDirections & dir) && (board.at(dir_move(x,y,dir)) == none)) movableDirections |= dir;
    }
	return (Direction) movableDirections;
}

bool GameEngine::move_piece(unsigned x, unsigned y, Direction mov_dir, Direction cap_dir){
	unsigned nextN = dir_move(x,y,mov_dir);	
	if(nextN == OFF_BOARD){
	    //Don't move piece off board
	    std::cerr<<"Can't moved piece off board" << std::endl;
	     return 0; 
	}
	else{
	    record_move(x, y, mov_dir, cap_dir);
        //If pass turn, then change players
	    if(mov_dir == no_dir){
            change_player();
            return 0;  
        }
        //Otherwise move the piece   
        else{
	        board.at(nextN) = board.at(on(x,y));
            board.at(on(x,y)) = none;
        }
        //If pieces were captured, remove them
	    if(check_capturable(x,y,mov_dir)){
	        remove_captured_pieces(x,y,mov_dir,cap_dir);
	        return 1;
	    }
        //If no piece was captured, the turn ends
        else{
            change_player();
            return 0;
        }
	}		
	return 0;
}
bool GameEngine::move_piece(Move move){
    unsigned x=move.x;
    unsigned y=move.y;
    Direction mov_dir = move.mov_dir;
    Direction cap_dir = move.cap_dir;

	unsigned nextN = dir_move(x,y,mov_dir);	
	if(nextN == OFF_BOARD){
	    //Don't move piece off board
	    std::cerr<<"Can't moved piece off board" << std::endl;
	    return 0; 
	}
	else{
        //Save the move
        record_move(move);
        //If the move is a pass, change players
	    if(mov_dir == no_dir){
            change_player();
            return 0;
        }
        //Otherwise the piece
        else{
	    board.at(nextN) = board.at(on(x,y));
        board.at(on(x,y)) = none;
        }
        //Then check to see if capture has been made
        if(check_capturable(x,y,mov_dir)){
	        	remove_captured_pieces(x,y,mov_dir,cap_dir);
	        	return 1;
	    }
        //If no piece was captured, the turn ends
        else{
            change_player();
            return 0;
        }
        
	}		
	return 0;
}

bool GameEngine::can_capture(){
	//if a capture has already been made, only check the active piece
	if(turnLog.size() > 0){
		unsigned preX = turnLog.back().x;
		unsigned preY = turnLog.back().y;
		Direction preMov = turnLog.back().mov_dir;
		unsigned currentN = dir_move(preX, preY, preMov);
		unsigned currentX = currentN % 9;
		unsigned currentY = (currentN-currentX)/9;
		if( capturable_directions(currentX, currentY) != no_dir ){
			return 1;
		}
        else{
            return 0;
        }
	}
	//Otherwise check the whole board
    else{
        for(unsigned x=0; x<9; x++){
	        for(unsigned y=0; y<5; y++){
	        	if((board.at(on(x,y)) == currentPlayer)&&(capturable_directions(x,y) != no_dir)) return 1;
	    	} 
	    }
	    return 0;
    }
}

Piece GameEngine::other(Piece player){
	if(player == p1) return p2;
	else if(player == p2) return p1;
	else{
		std::cerr<<"Piece other(Piece) was called on an empty square"<<std::endl;
	}
	return none;
}

Piece GameEngine::get_player(unsigned x, unsigned y){
	return board.at(on(x,y));
}

bool GameEngine::move_valid(unsigned x, unsigned y, Direction direction, Direction cap_dir){
	//Check the piece to be moved belongs to current player
	if (board.at(on(x,y)) != currentPlayer){
		std::cerr << "Piece must belong to current player" << std::endl;
		return 0;
	}
	//Validate the capture direction
	if (!((cap_dir==direction)||(cap_dir==opposite(direction)))){
		std::cerr << "Capture direction must match move direction" << std::endl;
		return 0;
	}
	//Check if a capture was made earlier in the turn
	if( turnLog.size() > 0){
		//Check using same piece as last time
		Move lastMove = turnLog.back();
		if(dir_move(lastMove.x, lastMove.y, lastMove.mov_dir) != on(x,y)){
			std::cerr<< "Must use same piece as last move" << std::endl;
			return 0;
		}
		//Making no move is valid if a capture has taken place
		if(direction == no_dir) return 1;

		//make sure, doesn't return to same square or go same direction
		else if(direction == lastMove.mov_dir){
			std::cerr<< "Can't move in same direction twice" << std::endl;
			return 0;
		}
		else if(return_to_intersection(x,y,direction)) {
			std::cerr<< "Can't return to that square this turn" << std::endl;
			return 0;
		}
	
	}
	//Check that the move is a capturing move
	if( (direction & capturable_directions(x,y)) != no_dir){
		// check that the cap direction kills a piece
		if(direction==cap_dir){
            unsigned targetSquare = dir_move(dir_move(x,y,cap_dir),cap_dir);
            if(targetSquare == OFF_BOARD){
                //can't capture pieces off the board
                return 0;
            }
            else if(board.at(targetSquare) == opponent) return 1;
		}
		else if(direction == opposite(cap_dir)){
            unsigned targetSquare = dir_move(x,y,cap_dir);
            if(targetSquare == OFF_BOARD){
                //cant' capture pieces off the board
                return 0;
            }
            else if(board.at(targetSquare) == opponent) return 1;
		}
		else{
			return 0;
		}
	}
	//If the move isn't capturing check that no capturing move exists
	else{
		if(can_capture()){
			std::cerr << "You must make a capture" <<std:: endl;
			return 0;
		}
		else{
			if( (direction & movable_directions(x,y)) != no_dir){
				//move valid
				return 1;
			}
			else{
				std::cerr << "Not a valid move" << std::endl;
				return 0;
			}
		}
	}
	return 0;
}

bool GameEngine::move_valid(Move move){
    unsigned x = move.x;
    unsigned y = move.y;
    Direction direction = move.mov_dir;
    Direction cap_dir = move.cap_dir;
    if( x > 8 || y > 4 )
    {
        std::cerr << "NO YOU NEEED TO FILL A FORM" << std::endl;
        return false;
    }
	//Check the piece to be moved belongs to current player
	if (board.at(on(x,y)) != currentPlayer){
		return 0;
	}
	//Validate the capture direction
	if (!((cap_dir==direction)||(cap_dir==opposite(direction)))){
		return 0;
	}
	//Check if a capture was made earlier in the turn
	if( turnLog.size() > 0){
		//Check using same piece as last time
		Move lastMove = turnLog.back();
		if(dir_move(lastMove.x, lastMove.y, lastMove.mov_dir) != on(x,y)){
			return 0;
		}
		//Making no move is valid if a capture has taken place
		if(direction == no_dir) return 1;
		//make sure, doesn't return to same square or go same direction
		else if(direction == lastMove.mov_dir){
			return 0;
		}
		else if(return_to_intersection(x,y,direction)) {
			return 0;
		}
	
	}
	//Check that the move is a capturing move
	if( (direction & capturable_directions(x,y)) != no_dir){
		// check that the cap direction kills a piece
		if(direction==cap_dir){
            unsigned targetSquare = dir_move(dir_move(x,y,cap_dir),cap_dir);
            if(targetSquare == OFF_BOARD){
                //can't capture pieces off the board
                return 0;
            }
            else if(board.at(targetSquare) == opponent) return 1;
		}
		else if(direction == opposite(cap_dir)){
            unsigned targetSquare = dir_move(x,y,cap_dir);
            if(targetSquare == OFF_BOARD){
                //cant' capture pieces off the board
                return 0;
            }
            else if(board.at(targetSquare) == opponent) return 1;
		}
		else{
			return 0;
		}
	}
	//If the move isn't capturing check that no capturing move exists
	else{
		if(can_capture()){
			return 0;
		}
		else{
			if( (direction & movable_directions(x,y)) != no_dir){
				//move valid
				return 1;
			}
			else{
				return 0;
			}
		}
	}
	return 0;
}

bool GameEngine::return_to_intersection(unsigned x, unsigned y, Direction dir){
	for(unsigned i=0; i<turnLog.size(); i++){
		unsigned prevX = turnLog.at(i).x;
		unsigned prevY = turnLog.at(i).y;
		if(on(prevX,prevY)==dir_move(x,y,dir)){
			return 1;
		}
			
	}
	return 0;
}

bool GameEngine::offer_move(){
	//Get move
	std::cerr << "Player " << currentPlayer << ":" << std::endl;
	unsigned y = get_y();
	unsigned x = get_x();
	Direction mov_dir = get_mov_dir();
	Direction cap_dir = get_cap_dir();
	//check if move is valid
	if(move_valid(x, y, mov_dir, cap_dir)){
		bool captured = move_piece(x, y, mov_dir, cap_dir);
		//if capture, get another turn and save last move
		if(captured){
			std::cerr << "You captured a piece! Move again" << std::endl;
			return 1;
		}
	}
	//Otherwise complain
	else{
		std::cerr<<"Please enter a valid move" << std::endl;
		return 1;
	}
	return 0;
}

bool GameEngine::make_move(Move move){
    	//check if move is valid
	if(move_valid(move)){
		bool captured = move_piece(move);
		//if capture, get another turn and save last move
		if(captured){
			std::cerr << "Player "<< get_current_player() <<" captured a piece and may move again" << std::endl;
			return 1;
		}
	}
	//Otherwise complain
	else{
		std::cerr<< "Player " << get_current_player() << " made a mistake :(" << std::endl;
		return 1;
	}
	return 0;
}

int GameEngine::remove_captured_pieces(unsigned x, unsigned y, Direction direction, Direction capture){
	//approach capture
	if(capture == direction){
		unsigned n = dir_move(dir_move(x,y,direction),direction);
		recursive_remove(n, direction);
	}
	//retreat capture
	if(capture==opposite(direction)){
 		Direction dir = opposite(direction);
		unsigned n = dir_move(x,y,dir);
		recursive_remove(n,dir);
	}
	return 0;
}

int GameEngine::recursive_remove(unsigned n, Direction dir){
	board.at(n) = none;
	unsigned nextN = dir_move(n,dir);
	//Check if next square point is off the board
	if(nextN == OFF_BOARD) return 0;
	//If not recurse to next point to remove
	else if(board.at(nextN) == other(currentPlayer)){
		recursive_remove(nextN, dir);
	}
	//Stop recursing if the next square is empty or yours
	return 0;
}

int GameEngine::change_player(){
	currentPlayer = other(currentPlayer);
	opponent = other(currentPlayer);
	save_game_log();
	return 0;
}

unsigned GameEngine::count_pieces(Piece player){
	unsigned numberPieces = 0;
	for(unsigned x=0; x<9; x++){
		for(unsigned y=0; y<5; y++){
			if(board.at(on(x,y))==player)numberPieces++;
		}
	}
	return numberPieces;
}

Piece GameEngine::get_current_player(){
	return currentPlayer;
}
Piece GameEngine::get_opponent(){
    return opponent;
}

bool GameEngine::finished(){
    if( count_pieces(get_opponent()) == 0) return true;
    else return false;
}

void GameEngine::record_move(unsigned x, unsigned y, Direction mov_dir, Direction cap_dir){
	Move newRecord(x, y, mov_dir, cap_dir);
	turnLog.push_back(newRecord);
	return;
}
void GameEngine::record_move(Move newRecord){
	turnLog.push_back(newRecord);
	return;
}

void GameEngine::save_game_log(){
	gameLog.insert(gameLog.end(), turnLog.begin(), turnLog.end());
    	turnLog.clear();
	return;
}

void GameEngine::pass_turn(){
    change_player();
    //Move move = turnLog.back();
    //unsigned newN = dir_move(move.x,move.y,move.mov_dir);
    //move.y = newN % 9;
    //move.x = newN-move.y;
    //move.mov_dir = no_dir;
    //move.cap_dir = no_dir;
    //make_move(move);
}
